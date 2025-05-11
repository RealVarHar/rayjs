/*******************************************************************************************
*
*   raylib [textures] example - Draw a texture along a segmented curve
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by Jeffery Myers (@JeffM2501) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2025 Jeffery Myers (@JeffM2501) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing, BLUE, CheckCollisionPointCircle, ClearBackground, CloseWindow, DARKGRAY, DARKGREEN, DrawCircleV, DrawLineV, DrawSplineSegmentBezierCubic, DrawText, EndDrawing, Fade, FLAG_MSAA_4X_HINT, FLAG_VSYNC_HINT, GetMouseDelta, GetMousePosition, GREEN, InitWindow, IsKeyPressed, IsMouseButtonDown, KEY_EQUAL, KEY_LEFT, KEY_MINUS, KEY_RIGHT, KEY_SPACE, LIGHTGRAY, LoadTexture, MAROON, MOUSE_LEFT_BUTTON, PURPLE, RAYWHITE, RED, SetConfigFlags, SetTargetFPS, SetTextureFilter, SKYBLUE, TextFormat, Texture, TEXTURE_FILTER_BILINEAR, UnloadTexture, Vector2, WindowShouldClose, YELLOW
} from 'rayjs:raylib';
import {Vector2Add, Vector2Length, Vector2Normalize, Vector2Scale} from "rayjs:raymath";
import {RL_QUADS, rlBegin, rlColor4ub, rlEnd, rlNormal3f, rlSetTexture, rlTexCoord2f, rlVertex2f} from "rayjs:rlgl";

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
var texRoad = new Texture();

var showCurve = false;

var curveWidth = 50;
var curveSegments = 24;

var curveStartPosition = new Vector2();
var curveStartPositionTangent = new Vector2();

var curveEndPosition = new Vector2();
var curveEndPositionTangent = new Vector2();

var curveSelectedPoint = null;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
// Draw textured curve using Spline Cubic Bezier
function DrawTexturedCurve() {
    const step = 1/curveSegments;

    let previous = curveStartPosition;
    let previousTangent = new Vector2();
    let previousV = 0;

    // We can't compute a tangent for the first point, so we need to reuse the tangent from the first segment
    let tangentSet = false;

    let current = new Vector2();
    let t = 0;

    for (let i = 1; i <= curveSegments; i++) {
        t = step*i;

        let a = Math.pow(1 - t, 3);
        let b = 3*Math.pow(1 - t, 2)*t;
        let c = 3*(1 - t)*Math.pow(t, 2);
        let d = Math.pow(t, 3);

        // Compute the endpoint for this segment
        current.y = a*curveStartPosition.y + b*curveStartPositionTangent.y + c*curveEndPositionTangent.y + d*curveEndPosition.y;
        current.x = a*curveStartPosition.x + b*curveStartPositionTangent.x + c*curveEndPositionTangent.x + d*curveEndPosition.x;

        // Vector from previous to current
        let delta = new Vector2( current.x - previous.x, current.y - previous.y );

        // The right hand normal to the delta vector
        let normal = Vector2Normalize(new Vector2( -delta.y, delta.x ));

        // The v texture coordinate of the segment (add up the length of all the segments so far)
        let v = previousV + Vector2Length(delta);

        // Make sure the start point has a normal
        if (!tangentSet) {
            previousTangent = normal;
            tangentSet = true;
        }

        // Extend out the normals from the previous and current points to get the quad for this segment
        let prevPosNormal = Vector2Add(previous, Vector2Scale(previousTangent, curveWidth));
        let prevNegNormal = Vector2Add(previous, Vector2Scale(previousTangent, -curveWidth));

        let currentPosNormal = Vector2Add(current, Vector2Scale(normal, curveWidth));
        let currentNegNormal = Vector2Add(current, Vector2Scale(normal, -curveWidth));

        // Draw the segment as a quad
        rlSetTexture(texRoad.id);
        rlBegin(RL_QUADS);
        rlColor4ub(255,255,255,255);
        rlNormal3f(0, 0, 1);

        rlTexCoord2f(0, previousV);
        rlVertex2f(prevNegNormal.x, prevNegNormal.y);

        rlTexCoord2f(1, previousV);
        rlVertex2f(prevPosNormal.x, prevPosNormal.y);

        rlTexCoord2f(1, v);
        rlVertex2f(currentPosNormal.x, currentPosNormal.y);

        rlTexCoord2f(0, v);
        rlVertex2f(currentNegNormal.x, currentNegNormal.y);
        rlEnd();

        // The current step is the start of the next step
        previous = current;
        previousTangent = normal;
        previousV = v;
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [textures] examples - textured curve");

    // Load the road texture
    texRoad = LoadTexture("resources/road.png");
    SetTextureFilter(texRoad, TEXTURE_FILTER_BILINEAR);

    // Setup the curve
    curveStartPosition = new Vector2( 80, 100 );
    curveStartPositionTangent = new Vector2( 100, 300 );

    curveEndPosition = new Vector2( 700, 350 );
    curveEndPositionTangent = new Vector2( 600, 100 );

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Curve config options
        if (IsKeyPressed(KEY_SPACE)) showCurve = !showCurve;
        if (IsKeyPressed(KEY_EQUAL)) curveWidth += 2;
        if (IsKeyPressed(KEY_MINUS)) curveWidth -= 2;
        if (curveWidth < 2) curveWidth = 2;

        // Update segments
        if (IsKeyPressed(KEY_LEFT)) curveSegments -= 2;
        if (IsKeyPressed(KEY_RIGHT)) curveSegments += 2;

        if (curveSegments < 2) curveSegments = 2;

        // Update curve logic
        // If the mouse is not down, we are not editing the curve so clear the selection
        if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON))  curveSelectedPoint = null;

        // If a point was selected, move it
        if (curveSelectedPoint) curveSelectedPoint = Vector2Add(curveSelectedPoint, GetMouseDelta());

        // The mouse is down, and nothing was selected, so see if anything was picked
        let mouse = GetMousePosition();
        if (CheckCollisionPointCircle(mouse, curveStartPosition, 6)) curveSelectedPoint = curveStartPosition;
        else if (CheckCollisionPointCircle(mouse, curveStartPositionTangent, 6)) curveSelectedPoint = curveStartPositionTangent;
        else if (CheckCollisionPointCircle(mouse, curveEndPosition, 6)) curveSelectedPoint = curveEndPosition;
        else if (CheckCollisionPointCircle(mouse, curveEndPositionTangent, 6)) curveSelectedPoint = curveEndPositionTangent;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexturedCurve();    // Draw a textured Spline Cubic Bezier
            
            // Draw spline for reference
            if (showCurve) DrawSplineSegmentBezierCubic(curveStartPosition, curveEndPosition, curveStartPositionTangent, curveEndPositionTangent, 2, BLUE);

            // Draw the various control points and highlight where the mouse is
            DrawLineV(curveStartPosition, curveStartPositionTangent, SKYBLUE);
            DrawLineV(curveStartPositionTangent, curveEndPositionTangent, Fade(LIGHTGRAY, 0.4));
            DrawLineV(curveEndPosition, curveEndPositionTangent, PURPLE);
            
            if (CheckCollisionPointCircle(mouse, curveStartPosition, 6)) DrawCircleV(curveStartPosition, 7, YELLOW);
            DrawCircleV(curveStartPosition, 5, RED);

            if (CheckCollisionPointCircle(mouse, curveStartPositionTangent, 6)) DrawCircleV(curveStartPositionTangent, 7, YELLOW);
            DrawCircleV(curveStartPositionTangent, 5, MAROON);

            if (CheckCollisionPointCircle(mouse, curveEndPosition, 6)) DrawCircleV(curveEndPosition, 7, YELLOW);
            DrawCircleV(curveEndPosition, 5, GREEN);

            if (CheckCollisionPointCircle(mouse, curveEndPositionTangent, 6)) DrawCircleV(curveEndPositionTangent, 7, YELLOW);
            DrawCircleV(curveEndPositionTangent, 5, DARKGREEN);

            // Draw usage info
            DrawText("Drag points to move curve, press SPACE to show/hide base curve", 10, 10, 10, DARKGRAY);
            DrawText(TextFormat("Curve width: %2.0f (Use + and - to adjust)", curveWidth), 10, 30, 10, DARKGRAY);
            DrawText(TextFormat("Curve segments: %d (Use LEFT and RIGHT to adjust)", curveSegments), 10, 50, 10, DARKGRAY);
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texRoad);
    
    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}