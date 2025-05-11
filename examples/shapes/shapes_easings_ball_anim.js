/*******************************************************************************************
*
*   raylib [shapes] example - easings ball anim
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BLACK, BeginDrawing, ClearBackground,
    CloseWindow,
    DrawCircle, DrawRectangle, DrawText, EndDrawing, Fade, GREEN, InitWindow, IsKeyPressed, KEY_ENTER, KEY_R,
    RAYWHITE, RED, SetTargetFPS, WindowShouldClose } from 'rayjs:raylib';
import * as re from 'rayjs:reasings';// Required for easing functions

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - easings ball anim");

    // Ball variable value to be animated with easings
    let ballPositionX = -100;
    let ballRadius = 20;
    let ballAlpha = 0;

    let state = 0;
    let framesCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (state == 0) {            // Move ball position X with easing
            framesCounter++;
            ballPositionX = Math.floor(re.EaseElasticOut(framesCounter, -100, screenWidth/2 + 100, 120));

            if (framesCounter >= 120) {
                framesCounter = 0;
                state = 1;
            }
        } else if (state == 1) {       // Increase ball radius with easing
            framesCounter++;
            ballRadius = Math.floor(re.EaseElasticIn(framesCounter, 20, 500, 200));

            if (framesCounter >= 200) {
                framesCounter = 0;
                state = 2;
            }
        } else if (state == 2) {       // Change ball alpha with easing (background color blending)
            framesCounter++;
            ballAlpha = re.EaseCubicOut(framesCounter, 0, 1, 200);

            if (framesCounter >= 200) {
                framesCounter = 0;
                state = 3;
            }
        } else if (state == 3) {       // Reset state to play again
            if (IsKeyPressed(KEY_ENTER)) {
                // Reset required variables to play again
                ballPositionX = -100;
                ballRadius = 20;
                ballAlpha = 0;
                state = 0;
            }
        }

        if (IsKeyPressed(KEY_R)) framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (state >= 2) DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            DrawCircle(ballPositionX, 200, ballRadius, Fade(RED, 1 - ballAlpha));

            if (state == 3) DrawText("PRESS [ENTER] TO PLAY AGAIN!", 240, 200, 20, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}