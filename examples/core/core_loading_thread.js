/*******************************************************************************************
*
*   raylib [core] example - loading thread
*
*   Example complexity rating: [★★★☆] 3/4
*
*   NOTE: This example requires linking with pthreads library on MinGW, 
*   it can be accomplished passing -static parameter to compiler
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from "qjs:os";
import {
    BeginDrawing, ClearBackground, CloseWindow, DARKBLUE, DARKGRAY, DrawRectangle, DrawRectangleLines, DrawText, EndDrawing, GREEN, InitWindow, IsKeyPressed, KEY_ENTER, LIME, RAYWHITE, SetTargetFPS, SKYBLUE, WindowShouldClose
} from "rayjs:raylib";

// Using C11 atomics for synchronization
// NOTE: A plain bool (or any plain data type for that matter) can't be used for inter-thread synchronization
const sharedProgressBuffer = new SharedArrayBuffer(4); // 4 bytes for an Int32
const sharedProgress = new Int32Array(sharedProgressBuffer); // We will simply interpret 1000 as 100% (done)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - loading thread");

    let thread;

    const STATE_WAITING = 0;
    const STATE_LOADING = 1;
    const STATE_FINISHED = 2;
    let state = STATE_WAITING;
    let framesCounter = 0;
    let dataLoaded = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        switch (state) {
            case STATE_WAITING: {
                if (IsKeyPressed(KEY_ENTER)){
                    thread = new os.Worker("./_core_loading_thread_worker.js");
                    thread.postMessage(sharedProgressBuffer);//sharedProgressBuffer will be changed asynchroniously in another thread
                    state = STATE_LOADING;
                }
            } break;
            case STATE_LOADING: {
                framesCounter++;
                dataLoaded = Atomics.load(sharedProgress, 0);
                if (dataLoaded == 1000) {
                    framesCounter = 0;
                    thread = undefined; //frees thread
                    state = STATE_FINISHED;
                }
            } break;
            case STATE_FINISHED: {
                if (IsKeyPressed(KEY_ENTER)) {
                    // Reset everything to launch again
                    Atomics.store(sharedProgress, 0, 0);
                    dataLoaded = 0;
                    state = STATE_WAITING;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch (state) {
                case STATE_WAITING: DrawText("PRESS ENTER to START LOADING DATA", 150, 170, 20, DARKGRAY); break;
                case STATE_LOADING: {
                    DrawRectangle(150, 200, dataLoaded, 60, SKYBLUE);
                    if ((framesCounter/15)%2) DrawText("LOADING DATA...", 240, 210, 40, DARKBLUE);

                } break;
                case STATE_FINISHED: {
                    DrawRectangle(150, 200, 500, 60, LIME);
                    DrawText("DATA LOADED!", 250, 210, 40, GREEN);

                } break;
                default: break;
            }

            DrawRectangleLines(150, 200, 500, 60, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}