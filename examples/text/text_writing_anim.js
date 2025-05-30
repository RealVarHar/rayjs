/*******************************************************************************************
*
*   raylib [text] example - Text Writing Animation
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.4, last time updated with raylib 1.4
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BeginDrawing,
    ClearBackground, CloseWindow, DrawText, EndDrawing, InitWindow, IsKeyDown, IsKeyPressed, KEY_ENTER, KEY_SPACE,
    LIGHTGRAY,
    MAROON,
    RAYWHITE, SetTargetFPS, TextSubtext, WindowShouldClose } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - text writing anim");

    const message = "This sample illustrates a text writing\nanimation effect! Check it out! ;)";

    let framesCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_SPACE)) framesCounter += 8;
        else framesCounter++;

        if (IsKeyPressed(KEY_ENTER)) framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(TextSubtext(message, 0, framesCounter/10), 210, 160, 20, MAROON);

            DrawText("PRESS [ENTER] to RESTART!", 240, 260, 20, LIGHTGRAY);
            DrawText("HOLD [SPACE] to SPEED UP!", 239, 300, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}