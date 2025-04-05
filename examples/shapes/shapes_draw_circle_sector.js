import * as rl from 'rayjs:raylib';
import * as rgui from 'rayjs:raygui';
{
    for (const key in rl) { globalThis[key] = rl[key] };
    for (const key in rgui) { globalThis[key] = rgui[key] };

    /*******************************************************************************************
    *
    *   raylib [shapes] example - draw circle sector (with gui options)
    *
    *   Example originally created with raylib 2.5, last time updated with raylib 2.5
    *
    *   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
    *
    *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
    *   BSD-like license that allows static linking with closed source software
    *
    *   Copyright (c) 2018-2023 Vlad Adrian (@demizdor) and Ramon Santamaria (@raysan5)
    *
    ********************************************************************************************/
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - draw circle sector");

    const center = new Vector2((GetScreenWidth() - 300)/2.0, GetScreenHeight()/2.0);

    let outerRadius = [180.0];
    let startAngle = [0.0];
    let endAngle = [180.0];
    let segments = [0];
    let minSegments = 4;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
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

            DrawCircleSector(center, outerRadius[0], startAngle[0], endAngle[0], segments[0], Fade(MAROON, 0.3));
            DrawCircleSectorLines(center, outerRadius[0], startAngle[0], endAngle[0], segments[0], Fade(MAROON, 0.6));

            // Draw GUI controls
            //------------------------------------------------------------------------------
            GuiSliderBar(new Rectangle(600, 40, 120, 20), "StartAngle", TextFormat("%.2f", startAngle[0]), startAngle, 0, 720);
            GuiSliderBar(new Rectangle(600, 70, 120, 20), "EndAngle", TextFormat("%.2f", endAngle[0]), endAngle, 0, 720);

            GuiSliderBar(new Rectangle(600, 140, 120, 20), "Radius", TextFormat("%.2f", outerRadius[0]), outerRadius, 0, 200);
            GuiSliderBar(new Rectangle(600, 170, 120, 20), "Segments", TextFormat("%.2f", segments[0]), segments, 0, 100);
            //------------------------------------------------------------------------------

            minSegments = Math.ceil((endAngle[0] - startAngle[0]) / 90);
            DrawText("MODE: " + (segments[0] >= minSegments) ? "MANUAL" : "AUTO", 600, 200, 10, (segments[0] >= minSegments)? MAROON : DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}