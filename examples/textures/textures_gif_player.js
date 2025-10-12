/*******************************************************************************************
*
*   raylib [textures] example - gif playing
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing, ClearBackground, CloseWindow, DARKGRAY, DrawRectangle, DrawRectangleLines, DrawText,
    DrawTexture, EndDrawing, GRAY, GetScreenWidth, InitWindow, IsKeyPressed,
    KEY_LEFT,
    KEY_RIGHT,
    LIGHTGRAY, LoadImageAnim, LoadTextureFromImage, MAROON, RAYWHITE,
    RED, SetTargetFPS, TextFormat, UnloadImage, UnloadTexture, UpdateTexture, WHITE, WindowShouldClose } from "rayjs:raylib";

const MAX_FRAME_DELAY = 20;
const MIN_FRAME_DELAY =  1;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - gif playing");

    let animFrames = [0];

    // Load all GIF animation frames into a single Image
    // NOTE: GIF data is always loaded as RGBA (32bit) by default
    // NOTE: Frames are just appended one after another in image.data memory
    let imScarfyAnim = LoadImageAnim("resources/scarfy_run.gif", animFrames);

    // Load texture from image
    // NOTE: We will update this texture when required with next frame data
    // WARNING: It's not recommended to use this technique for sprites animation,
    // use spritesheets instead, like illustrated in textures_sprite_anim example
    let texScarfyAnim = LoadTextureFromImage(imScarfyAnim);

    let nextFrameDataOffset = 0;  // Current byte offset to next frame in image.data

    let currentAnimFrame = 0;     // Current animation frame to load and draw
    let frameDelay = 8;           // Frame delay to switch between animation frames
    let frameCounter = 0;         // General frames counter

    SetTargetFPS(60);             // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        frameCounter++;
        if (frameCounter >= frameDelay) {
            // Move to next frame
            // NOTE: If final frame is reached we return to first frame
            currentAnimFrame++;
            if (currentAnimFrame >= animFrames[0]) currentAnimFrame = 0;

            // Get memory offset position for next frame data in image.data
            nextFrameDataOffset = imScarfyAnim.width*imScarfyAnim.height*4*currentAnimFrame;

            // Update GPU texture data with next frame image data
            // WARNING: Data size (frame size) and pixel format must match already created texture
            // WARNING: imScarfyAnim.data will in the future contain appropirate typed array instead of ArrayBuffer and this will change syntax for offsets
            let buffer=(new Uint8Array(new Uint8Array(imScarfyAnim.data, nextFrameDataOffset))).buffer;
            UpdateTexture(texScarfyAnim, buffer);

            frameCounter = 0;
        }

        // Control frames delay
        if (IsKeyPressed(KEY_RIGHT)) frameDelay++;
        else if (IsKeyPressed(KEY_LEFT)) frameDelay--;

        if (frameDelay > MAX_FRAME_DELAY) frameDelay = MAX_FRAME_DELAY;
        else if (frameDelay < MIN_FRAME_DELAY) frameDelay = MIN_FRAME_DELAY;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(TextFormat("TOTAL GIF FRAMES:  %02i", animFrames[0]), 50, 30, 20, LIGHTGRAY);
            DrawText(TextFormat("CURRENT FRAME: %02i", currentAnimFrame), 50, 60, 20, GRAY);
            DrawText(TextFormat("CURRENT FRAME IMAGE.DATA OFFSET: %02i", nextFrameDataOffset), 50, 90, 20, GRAY);

            DrawText("FRAMES DELAY: ", 100, 305, 10, DARKGRAY);
            DrawText(TextFormat("%02i frames", frameDelay), 620, 305, 10, DARKGRAY);
            DrawText("PRESS RIGHT/LEFT KEYS to CHANGE SPEED!", 290, 350, 10, DARKGRAY);

            for (let i = 0; i < MAX_FRAME_DELAY; i++) {
                if (i < frameDelay) DrawRectangle(190 + 21*i, 300, 20, 20, RED);
                DrawRectangleLines(190 + 21*i, 300, 20, 20, MAROON);
            }

            DrawTexture(texScarfyAnim, GetScreenWidth()/2 - texScarfyAnim.width/2, 140, WHITE);

            DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texScarfyAnim);   // Unload texture
    UnloadImage(imScarfyAnim);      // Unload image (contains all frames)

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}