/*******************************************************************************************
*
*   raylib [shapes] example - draw rectangle rounded (with gui options)
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2025 Vlad Adrian (@demizdor) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as rg from 'rayjs:raygui'; // Required for GUI controls
import {BeginDrawing,
    ClearBackground,
    CloseWindow,
    DARKGRAY,
    DrawFPS,
    DrawLine, DrawRectangle, DrawRectangleRec,
    DrawRectangleRounded, DrawRectangleRoundedLinesEx, DrawText,
    EndDrawing, Fade, GOLD, GetScreenHeight, GetScreenWidth, InitWindow,
    LIGHTGRAY, MAROON, RAYWHITE, Rectangle, SetTargetFPS, TextFormat, WindowShouldClose } from 'rayjs:raylib';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - draw rectangle rounded");

    let width = [200];
    let height = [100];
    let roundness = [0.2];
    let segments = [0];
    let lineThick = [1];

    let drawRect = [false];
    let drawRoundedRect = [true];
    let drawRoundedLines = [false];

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        let rec = new Rectangle( (GetScreenWidth() - width[0] - 250)/2, (GetScreenHeight() - height[0])/2, width[0], height[0] );
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawLine(560, 0, 560, GetScreenHeight(), Fade(LIGHTGRAY, 0.6));
            DrawRectangle(560, 0, GetScreenWidth() - 500, GetScreenHeight(), Fade(LIGHTGRAY, 0.3));

            if (drawRect[0]) DrawRectangleRec(rec, Fade(GOLD, 0.6));
            if (drawRoundedRect[0]) DrawRectangleRounded(rec, roundness[0], Math.floor(segments[0]), Fade(MAROON, 0.2));
            if (drawRoundedLines[0]) DrawRectangleRoundedLinesEx(rec, roundness[0], Math.floor(segments[0]), lineThick[0], Fade(MAROON, 0.4));

            // Draw GUI controls
            //------------------------------------------------------------------------------
            rg.GuiSliderBar(new Rectangle( 640, 40, 105,  20 ), "Width", TextFormat("%.2f", width[0]), width, 0, GetScreenWidth() - 300);
            rg.GuiSliderBar(new Rectangle( 640, 70, 105,  20 ), "Height", TextFormat("%.2f", height[0]), height, 0, GetScreenHeight() - 50);
            rg.GuiSliderBar(new Rectangle( 640, 140, 105, 20 ), "Roundness", TextFormat("%.2f", roundness[0]), roundness, 0.0, 1.0);
            rg.GuiSliderBar(new Rectangle( 640, 170, 105, 20 ), "Thickness", TextFormat("%.2f", lineThick[0]), lineThick, 0, 20);
            rg.GuiSliderBar(new Rectangle( 640, 240, 105, 20 ), "Segments", TextFormat("%.2f", segments[0]), segments, 0, 60);

            rg.GuiCheckBox(new Rectangle( 640, 320, 20, 20 ), "DrawRoundedRect", drawRoundedRect);
            rg.GuiCheckBox(new Rectangle( 640, 350, 20, 20 ), "DrawRoundedLines", drawRoundedLines);
            rg.GuiCheckBox(new Rectangle( 640, 380, 20, 20 ), "DrawRect", drawRect);
            //------------------------------------------------------------------------------

            DrawText(TextFormat("MODE: %s", (segments[0] >= 4)? "MANUAL" : "AUTO"), 640, 280, 10, (segments[0] >= 4)? MAROON : DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
