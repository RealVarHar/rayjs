/*******************************************************************************************
*
*   raylib [core] example - Generate random values
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 1.1, last time updated with raylib 1.1
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing, ClearBackground, CloseWindow, DrawText, EndDrawing, GetRandomValue, InitWindow, LIGHTGRAY, MAROON, RAYWHITE, SetTargetFPS, TextFormat, WindowShouldClose
} from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - generate random values");

    // SetRandomSeed(0xaabbccff);   // Set a custom random seed if desired, by default: "time(NULL)"

    let randValue = GetRandomValue(-8, 5);   // Get a random integer number between -8 and 5 (both included)

    let framesCounter = 0; // Variable used to count frames
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        framesCounter++;

        // Every two seconds (120 frames) a new random value is generated
        if (((framesCounter/120)%2) == 1) {
            randValue = GetRandomValue(-8, 5);
            framesCounter = 0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Every 2 seconds a new random value is generated:", 130, 100, 20, MAROON);

            DrawText(TextFormat("%i", randValue), 360, 180, 80, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}