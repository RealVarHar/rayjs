/*******************************************************************************************
*
*   raylib [core] example - Input multitouch
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 2.1, last time updated with raylib 2.5
*
*   Example contributed by Berni (@Berni8k) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Berni (@Berni8k) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing, BLACK, ClearBackground, CloseWindow, DARKGRAY, DrawCircleV, DrawText, EndDrawing, GetTouchPointCount, GetTouchPosition, InitWindow, ORANGE, RAYWHITE, SetTargetFPS, TextFormat, WindowShouldClose
} from "rayjs:raylib";

const MAX_TOUCH_POINTS = 10;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input multitouch");

    let touchPositions = [];

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Get the touch point count ( how many fingers are touching the screen )
        let tCount = GetTouchPointCount();
        // Clamp touch points available ( set the maximum touch points allowed )
        if (tCount > MAX_TOUCH_POINTS) tCount = MAX_TOUCH_POINTS;
        // Get touch points positions
        for (let i = 0; i < tCount; ++i) touchPositions[i] = GetTouchPosition(i);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            for (let i = 0; i < tCount; i++) {
                // Make sure point is not (0, 0) as this means there is no touch for it
                if ((touchPositions[i].x > 0) && (touchPositions[i].y > 0)) {
                    // Draw circle and touch index number
                    DrawCircleV(touchPositions[i], 34, ORANGE);
                    DrawText(TextFormat("%d", i), Math.floor(touchPositions[i].x) - 10, Math.floor(touchPositions[i].y) - 70, 40, BLACK);
                }
            }

            DrawText("touch the screen at multiple locations to get multiple balls", 10, 10, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
