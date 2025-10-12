/*******************************************************************************************
*
*   raylib [shapes] example - top down lights
*
*   Example complexity rating: [★★★★] 4/4
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example contributed by Jeffery Myers (@JeffM2501) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2025 Jeffery Myers (@JeffM2501)
*
********************************************************************************************/

import {BLACK, BLEND_ALPHA, BLEND_CUSTOM,
    BeginDrawing, BeginTextureMode, CheckCollisionPointRec, CheckCollisionRecs, ClearBackground,
    CloseWindow,
    ColorAlpha, DARKBLUE, DARKBROWN, DARKGRAY,
    DARKGREEN,
    DARKPURPLE, DrawCircle, DrawCircleGradient,
    DrawFPS,
    DrawRectangleLines, DrawRectangleRec, DrawText, DrawTextureRec, DrawTriangleFan, EndDrawing, EndTextureMode,
    GREEN,
    GenImageChecked,
    GetMousePosition,
    GetRandomValue,
    GetScreenHeight,
    GetScreenWidth,
    InitWindow,
    IsKeyPressed,
    IsMouseButtonDown,
    IsMouseButtonPressed,
    KEY_F1,
    LoadRenderTexture, LoadTextureFromImage,
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    PURPLE, Rectangle, RenderTexture, SetTargetFPS, UnloadImage,
    UnloadRenderTexture,
    UnloadTexture, Vector2, WHITE, WindowShouldClose, YELLOW } from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';
import * as rg from 'rayjs:rlgl';

// Custom Blend Modes
const RLGL_SRC_ALPHA = 0x0302;
const RLGL_MIN = 0x8007;
const RLGL_MAX = 0x8008;

const MAX_BOXES = 20;
const MAX_SHADOWS = MAX_BOXES*3;         // MAX_BOXES *3. Each box can cast up to two shadow volumes for the edges it is away from, and one for the box itself
const MAX_LIGHTS = 16;

// Light info type
class LightInfo{
    constructor(){
        this.active = false;                // Is this light slot active?
        this.dirty = false;                 // Does this light need to be updated?
        this.valid = false;                 // Is this light in a valid position?

        this.position = new Vector2();           // Light position
        this.mask = new RenderTexture();         // Alpha mask for the light
        this.outerRadius=0;                      // The distance the light touches
        this.bounds = new Rectangle();           // A cached rectangle of the light bounds to help with culling

        // Shadow geometry
        this.shadows =new Array(MAX_SHADOWS).fill(undefined).map(()=> [new Vector2(),new Vector2(),new Vector2(),new Vector2()]);
        this.shadowCount = 0;
    }
}

let lights = new Array(MAX_LIGHTS);
for(let key=0;key<MAX_LIGHTS;key++){
    lights[key] = new LightInfo();
}

// Move a light and mark it as dirty so that we update it's mask next frame
function MoveLight(slot, x, y) {
    lights[slot].dirty = true;
    lights[slot].position.x = x; 
    lights[slot].position.y = y;

    // update the cached bounds
    lights[slot].bounds.x = x - lights[slot].outerRadius;
    lights[slot].bounds.y = y - lights[slot].outerRadius;
}

// Compute a shadow volume for the edge
// It takes the edge and projects it back by the light radius and turns it into a quad
function ComputeShadowVolumeForEdge(slot, sp, ep) {
    if (lights[slot].shadowCount >= MAX_SHADOWS) return;

    let extension = lights[slot].outerRadius*2;

    let spVector = rm.Vector2Normalize(rm.Vector2Subtract(sp, lights[slot].position));
    let spProjection = rm.Vector2Add(sp, rm.Vector2Scale(spVector, extension));

    let epVector = rm.Vector2Normalize(rm.Vector2Subtract(ep, lights[slot].position));
    let epProjection = rm.Vector2Add(ep, rm.Vector2Scale(epVector, extension));

    let shadow;
    shadow = lights[slot].shadows[lights[slot].shadowCount][0];
    shadow.x = sp.x;
    shadow.y = sp.y;
    shadow = lights[slot].shadows[lights[slot].shadowCount][1];
    shadow.x = ep.x;
    shadow.y = ep.y;
    shadow = lights[slot].shadows[lights[slot].shadowCount][2];
    shadow.x = epProjection.x;
    shadow.y = epProjection.y;
    shadow = lights[slot].shadows[lights[slot].shadowCount][3];
    shadow.x = spProjection.x;
    shadow.y = spProjection.y;

    lights[slot].shadowCount++;
}

// Draw the light and shadows to the mask for a light
function DrawLightMask(slot) {
    // Use the light mask
    BeginTextureMode(lights[slot].mask);

        ClearBackground(WHITE);

        // Force the blend mode to only set the alpha of the destination
        rg.rlSetBlendFactors(RLGL_SRC_ALPHA, RLGL_SRC_ALPHA, RLGL_MIN);
        rg.rlSetBlendMode(BLEND_CUSTOM);

        // If we are valid, then draw the light radius to the alpha mask
        if (lights[slot].valid) DrawCircleGradient(Math.floor(lights[slot].position.x), Math.floor(lights[slot].position.y), lights[slot].outerRadius, ColorAlpha(WHITE, 0), WHITE);

        rg.rlDrawRenderBatchActive();

        // Cut out the shadows from the light radius by forcing the alpha to maximum
        rg.rlSetBlendMode(BLEND_ALPHA);
        rg.rlSetBlendFactors(RLGL_SRC_ALPHA, RLGL_SRC_ALPHA, RLGL_MAX);
        rg.rlSetBlendMode(BLEND_CUSTOM);

        // Draw the shadows to the alpha mask
        for (let i = 0; i < lights[slot].shadowCount; i++) {
            DrawTriangleFan(lights[slot].shadows[i], 4, WHITE);
        }

        rg.rlDrawRenderBatchActive();
        
        // Go back to normal blend mode
        rg.rlSetBlendMode(BLEND_ALPHA);

    EndTextureMode();
}

// Setup a light
function SetupLight(slot, x, y, radius) {
    lights[slot].active = true;
    lights[slot].valid = false;  // The light must prove it is valid
    lights[slot].mask = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    lights[slot].outerRadius = radius;

    lights[slot].bounds.width = radius * 2;
    lights[slot].bounds.height = radius * 2;

    MoveLight(slot, x, y);

    // Force the render texture to have something in it
    DrawLightMask(slot);
}

// See if a light needs to update it's mask
function UpdateLight(slot, boxes,count) {
    if (!lights[slot].active || !lights[slot].dirty) return false;

    lights[slot].dirty = false;
    lights[slot].shadowCount = 0;
    lights[slot].valid = false;

    for (let i = 0; i < count; i++) {
        // Are we in a box? if so we are not valid
        if (CheckCollisionPointRec(lights[slot].position, boxes[i])) return false;

        // If this box is outside our bounds, we can skip it
        if (!CheckCollisionRecs(lights[slot].bounds, boxes[i])) continue;

        // Check the edges that are on the same side we are, and cast shadow volumes out from them
        
        // Top
        let sp = new Vector2( boxes[i].x, boxes[i].y );
        let ep = new Vector2( boxes[i].x + boxes[i].width, boxes[i].y );

        if (lights[slot].position.y > ep.y) ComputeShadowVolumeForEdge(slot, sp, ep);

        // Right
        sp.x=ep.x; sp.y=ep.y;
        ep.y += boxes[i].height;
        if (lights[slot].position.x < ep.x) ComputeShadowVolumeForEdge(slot, sp, ep);

        // Bottom
        sp.x=ep.x; sp.y=ep.y;
        ep.x -= boxes[i].width;
        if (lights[slot].position.y < ep.y) ComputeShadowVolumeForEdge(slot, sp, ep);

        // Left
        sp.x=ep.x; sp.y=ep.y;
        ep.y -= boxes[i].height;
        if (lights[slot].position.x > ep.x) ComputeShadowVolumeForEdge(slot, sp, ep);

        // The box itself
        lights[slot].shadows[lights[slot].shadowCount][0] = new Vector2( boxes[i].x, boxes[i].y );
        lights[slot].shadows[lights[slot].shadowCount][1] = new Vector2( boxes[i].x, boxes[i].y + boxes[i].height );
        lights[slot].shadows[lights[slot].shadowCount][2] = new Vector2( boxes[i].x + boxes[i].width, boxes[i].y + boxes[i].height );
        lights[slot].shadows[lights[slot].shadowCount][3] = new Vector2( boxes[i].x + boxes[i].width, boxes[i].y );
        lights[slot].shadowCount++;
    }

    lights[slot].valid = true;

    DrawLightMask(slot);

    return true;
}

// Set up some boxes
function SetupBoxes(boxes, count) {
    boxes[0] = new Rectangle( 150,80, 40, 40 );
    boxes[1] = new Rectangle( 1200, 700, 40, 40 );
    boxes[2] = new Rectangle( 200, 600, 40, 40 );
    boxes[3] = new Rectangle( 1000, 50, 40, 40 );
    boxes[4] = new Rectangle( 500, 350, 40, 40 );

    for (let i = 5; i < MAX_BOXES; i++){
        boxes[i] = new Rectangle(GetRandomValue(0,GetScreenWidth()), GetRandomValue(0,GetScreenHeight()), GetRandomValue(10,100), GetRandomValue(10,100) );
    }

    count[0] = MAX_BOXES;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - top down lights");

    // Initialize our 'world' of boxes
    let boxCount = [0];
    let boxes = new Array(MAX_BOXES);
    SetupBoxes(boxes, boxCount);

    // Create a checkerboard ground texture
    let img = GenImageChecked(64, 64, 32, 32, DARKBROWN, DARKGRAY);
    let backgroundTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    // Create a global light mask to hold all the blended lights
    let lightMask = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    // Setup initial light
    SetupLight(0, 600, 400, 300);
    let nextLight = 1;

    let showLines = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Drag light 0
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) MoveLight(0, GetMousePosition().x, GetMousePosition().y);

        // Make a new light
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && (nextLight < MAX_LIGHTS)) {
            SetupLight(nextLight, GetMousePosition().x, GetMousePosition().y, 200);
            nextLight++;
        }

        // Toggle debug info
        if (IsKeyPressed(KEY_F1)) showLines = !showLines;

        // Update the lights and keep track if any were dirty so we know if we need to update the master light mask
        let dirtyLights = false;
        for (let i = 0; i < MAX_LIGHTS; i++){
            if (UpdateLight(i, boxes, boxCount)) dirtyLights = true;
        }

        // Update the light mask
        if (dirtyLights) {
            // Build up the light mask
            BeginTextureMode(lightMask);
            
                ClearBackground(BLACK);

                // Force the blend mode to only set the alpha of the destination
                rg.rlSetBlendFactors(RLGL_SRC_ALPHA, RLGL_SRC_ALPHA, RLGL_MIN);
                rg.rlSetBlendMode(BLEND_CUSTOM);

                // Merge in all the light masks
                for (let i = 0; i < MAX_LIGHTS; i++) {
                    if (lights[i].active) DrawTextureRec(lights[i].mask.texture, new Rectangle( 0, 0, GetScreenWidth(), -GetScreenHeight() ), rm.Vector2Zero(), WHITE);
                }

                rg.rlDrawRenderBatchActive();

                // Go back to normal blend
                rg.rlSetBlendMode(BLEND_ALPHA);
            EndTextureMode();
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
            // Draw the tile background
            DrawTextureRec(backgroundTexture, new Rectangle( 0, 0, GetScreenWidth(), GetScreenHeight() ), rm.Vector2Zero(), WHITE);
            
            // Overlay the shadows from all the lights
            DrawTextureRec(lightMask.texture, new Rectangle( 0, 0, GetScreenWidth(), -GetScreenHeight() ), rm.Vector2Zero(), ColorAlpha(WHITE, showLines? 0.75 : 1));

            // Draw the lights
            for (let i = 0; i < MAX_LIGHTS; i++) {
                if (lights[i].active) DrawCircle(Math.floor(lights[i].position.x), Math.floor(lights[i].position.y), 10, (i == 0)? YELLOW : WHITE);
            }

            if (showLines) {
                for (let s = 0; s < lights[0].shadowCount; s++) {
                    DrawTriangleFan(lights[0].shadows[s], 4, DARKPURPLE);
                }

                for (let b = 0; b < boxCount[0]; b++) {
                    if (CheckCollisionRecs(boxes[b],lights[0].bounds)) DrawRectangleRec(boxes[b], PURPLE);

                    DrawRectangleLines(boxes[b].x, Math.floor(boxes[b].y), Math.floor(boxes[b].width), Math.floor(boxes[b].height), DARKBLUE);
                }

                DrawText("(F1) Hide Shadow Volumes", 10, 50, 10, GREEN);
            } else {
                DrawText("(F1) Show Shadow Volumes", 10, 50, 10, GREEN);
            }

            DrawFPS(screenWidth - 80, 10);
            DrawText("Drag to move light #1", 10, 10, 10, DARKGREEN);
            DrawText("Right click to add new light", 10, 30, 10, DARKGREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(backgroundTexture);
    UnloadRenderTexture(lightMask);
    for (let i = 0; i < MAX_LIGHTS; i++) {
        if (lights[i].active) UnloadRenderTexture(lights[i].mask);
    }

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}