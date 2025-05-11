/*******************************************************************************************
*
*   raylib [shapes] example - draw ring (with gui options)
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
import {BLACK, BeginDrawing,
    ClearBackground,
    CloseWindow,
    DARKGRAY,
    DrawCircleSectorLines,
    DrawFPS,
    DrawLine, DrawRectangle, DrawRing, DrawRingLines, DrawText,
    EndDrawing, Fade, GetScreenHeight, GetScreenWidth, InitWindow,
    LIGHTGRAY, MAROON, RAYWHITE, Rectangle, SetTargetFPS, TextFormat, Vector2, WindowShouldClose } from 'rayjs:raylib';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - draw ring");

    let center = new Vector2((GetScreenWidth() - 300)/2, GetScreenHeight()/2 );

    let innerRadius = [80];
    let outerRadius = [190];

    let startAngle = [0];
    let endAngle = [360];
    let segments = [0];

    let drawRing = [true];
    let drawRingLines = [false];
    let drawCircleLines = [false];

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // NOTE: All variables update happens inside GUI control functions
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawLine(500, 0, 500, GetScreenHeight(), Fade(LIGHTGRAY, 0.6));
            DrawRectangle(500, 0, GetScreenWidth() - 500, GetScreenHeight(), Fade(LIGHTGRAY, 0.3));

            if (drawRing[0]) DrawRing(center, innerRadius[0], outerRadius[0], startAngle[0], endAngle[0], Math.floor(segments[0]), Fade(MAROON, 0.3));
            if (drawRingLines[0]) DrawRingLines(center, innerRadius[0], outerRadius[0], startAngle[0], endAngle[0], Math.floor(segments[0]), Fade(BLACK, 0.4));
            if (drawCircleLines[0]) DrawCircleSectorLines(center, outerRadius[0], startAngle[0], endAngle[0], Math.floor(segments[0]), Fade(BLACK, 0.4));

            // Draw GUI controls
            //------------------------------------------------------------------------------
            rg.GuiSliderBar(new Rectangle( 600, 40, 120,  20 ), "StartAngle", TextFormat("%.2f", startAngle[0]), startAngle, -450, 450);
            rg.GuiSliderBar(new Rectangle( 600, 70, 120,  20 ), "EndAngle", TextFormat("%.2f", endAngle[0]), endAngle, -450, 450);
            rg.GuiSliderBar(new Rectangle( 600, 140, 120, 20 ), "InnerRadius", TextFormat("%.2f", innerRadius[0]), innerRadius, 0, 100);
            rg.GuiSliderBar(new Rectangle( 600, 170, 120, 20 ), "OuterRadius", TextFormat("%.2f", outerRadius[0]), outerRadius, 0, 200);
            rg.GuiSliderBar(new Rectangle( 600, 240, 120, 20 ), "Segments", TextFormat("%.2f", segments[0]), segments, 0, 100);

            rg.GuiCheckBox(new Rectangle( 600, 320, 20, 20 ), "Draw Ring", drawRing);
            rg.GuiCheckBox(new Rectangle( 600, 350, 20, 20 ), "Draw RingLines", drawRingLines);
            rg.GuiCheckBox(new Rectangle( 600, 380, 20, 20 ), "Draw CircleLines", drawCircleLines);
            //------------------------------------------------------------------------------

            let minSegments = Math.ceil((endAngle[0] - startAngle[0])/90);
            DrawText(TextFormat("MODE: %s", (segments[0] >= minSegments)? "MANUAL" : "AUTO"), 600, 270, 10, (segments[0] >= minSegments)? MAROON : DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}