/*******************************************************************************************
*
*   raylib [shapes] example - Draw basic shapes 2d (rectangle, circle, line...)
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 1.0, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BEIGE, BLACK, BROWN, BeginDrawing, ClearBackground,
    CloseWindow,
    DARKBLUE,
    DARKGRAY, DrawCircle,
    DrawCircleGradient, DrawCircleLines,
    DrawLine,
    DrawPoly,
    DrawPolyLines,
    DrawPolyLinesEx,
    DrawRectangle,
    DrawRectangleGradientH, DrawRectangleLines, DrawText,
    DrawTriangle,
    DrawTriangleLines,
    EndDrawing,
    GOLD, GREEN, InitWindow, MAROON, ORANGE, RAYWHITE, RED, SKYBLUE, SetTargetFPS, VIOLET, Vector2, WindowShouldClose } from 'rayjs:raylib';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing");

    let rotation = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        rotation += 0.2;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("some basic shapes available on raylib", 20, 20, 20, DARKGRAY);

            // Circle shapes and lines
            DrawCircle(screenWidth/5, 120, 35, DARKBLUE);
            DrawCircleGradient(screenWidth/5, 220, 60, GREEN, SKYBLUE);
            DrawCircleLines(screenWidth/5, 340, 80, DARKBLUE);

            // Rectangle shapes and lines
            DrawRectangle(screenWidth/4*2 - 60, 100, 120, 60, RED);
            DrawRectangleGradientH(screenWidth/4*2 - 90, 170, 180, 130, MAROON, GOLD);
            DrawRectangleLines(screenWidth/4*2 - 40, 320, 80, 60, ORANGE);  // NOTE: Uses QUADS internally, not lines

            // Triangle shapes and lines
            DrawTriangle( new Vector2( screenWidth/4 *3,  80 ),
                          new Vector2( screenWidth/4 *3 - 60, 150 ),
                          new Vector2( screenWidth/4 *3 + 60, 150 ), VIOLET);

            DrawTriangleLines(new Vector2( screenWidth/4*3, 160 ),
                              new Vector2( screenWidth/4*3 - 20, 230 ),
                              new Vector2( screenWidth/4*3 + 20, 230 ), DARKBLUE);

            // Polygon shapes and lines
            DrawPoly( new Vector2( screenWidth/4*3, 330 ), 6, 80, rotation, BROWN);
            DrawPolyLines( new Vector2( screenWidth/4*3, 330 ), 6, 90, rotation, BROWN);
            DrawPolyLinesEx( new Vector2( screenWidth/4*3, 330 ), 6, 85, rotation, 6, BEIGE);

            // NOTE: We draw all LINES based shapes together to optimize internal drawing,
            // this way, all LINES are rendered in a single draw pass
            DrawLine(18, 42, screenWidth - 18, 42, BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
