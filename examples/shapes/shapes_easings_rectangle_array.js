/*******************************************************************************************
*
*   raylib [shapes] example - easings rectangle array
*
*   Example complexity rating: [★★★☆] 3/4
*
*   NOTE: This example requires 'easings.h' library, provided on raylib/src. Just copy
*   the library to same directory as example or make sure it's available on include path.
*
*   Example originally created with raylib 2.0, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BeginDrawing, ClearBackground,
    CloseWindow, DrawRectanglePro, DrawText, EndDrawing, GRAY, InitWindow, IsKeyPressed, KEY_SPACE,
    RAYWHITE, RED, Rectangle, SetTargetFPS, Vector2, WindowShouldClose } from 'rayjs:raylib';
import * as re from 'rayjs:reasings';// Required for easing functions

const RECS_WIDTH = 50;
const RECS_HEIGHT = 50;

const MAX_RECS_X = 800/RECS_WIDTH;
const MAX_RECS_Y = 450/RECS_HEIGHT;

const PLAY_TIME_IN_FRAMES = 240;                 // At 60 fps = 4 seconds

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - easings rectangle array");

    let recs = new Array(MAX_RECS_X*MAX_RECS_Y);

    for (let y = 0; y < MAX_RECS_Y; y++) {
        for (let x = 0; x < MAX_RECS_X; x++) {
            recs[y*MAX_RECS_X + x] = new Rectangle();
            recs[y*MAX_RECS_X + x].x = RECS_WIDTH/2 + RECS_WIDTH*x;
            recs[y*MAX_RECS_X + x].y = RECS_HEIGHT/2 + RECS_HEIGHT*y;
            recs[y*MAX_RECS_X + x].width = RECS_WIDTH;
            recs[y*MAX_RECS_X + x].height = RECS_HEIGHT;
        }
    }

    let rotation = 0;
    let framesCounter = 0;
    let state = 0;                  // Rectangles animation state: 0-Playing, 1-Finished

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (state == 0) {
            framesCounter++;

            for (let i = 0; i < MAX_RECS_X*MAX_RECS_Y; i++) {
                recs[i].height = re.EaseCircOut(framesCounter, RECS_HEIGHT, -RECS_HEIGHT, PLAY_TIME_IN_FRAMES);
                recs[i].width = re.EaseCircOut(framesCounter, RECS_WIDTH, -RECS_WIDTH, PLAY_TIME_IN_FRAMES);

                if (recs[i].height < 0) recs[i].height = 0;
                if (recs[i].width < 0) recs[i].width = 0;

                if ((recs[i].height == 0) && (recs[i].width == 0)) state = 1;   // Finish playing

                rotation = re.EaseLinearIn(framesCounter, 0, 360, PLAY_TIME_IN_FRAMES);
            }
        } else if ((state == 1) && IsKeyPressed(KEY_SPACE)) {
            // When animation has finished, press space to restart
            framesCounter = 0;

            for (let i = 0; i < MAX_RECS_X*MAX_RECS_Y; i++) {
                recs[i].height = RECS_HEIGHT;
                recs[i].width = RECS_WIDTH;
            }

            state = 0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (state == 0) {
                for (let i = 0; i < MAX_RECS_X*MAX_RECS_Y; i++) {
                    DrawRectanglePro(recs[i], new Vector2( recs[i].width/2, recs[i].height/2 ), rotation, RED);
                }
            }
            else if (state == 1) DrawText("PRESS [SPACE] TO PLAY AGAIN!", 240, 200, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}