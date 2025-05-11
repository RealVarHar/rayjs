/*******************************************************************************************
*
*   raylib [shapes] example - Cubic-bezier lines
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 1.7, last time updated with raylib 1.7
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BLUE, BeginDrawing, CheckCollisionPointCircle, ClearBackground,
    CloseWindow,
    DrawCircleV,
    DrawLineBezier,
    DrawText, EndDrawing, FLAG_MSAA_4X_HINT, GRAY, GetMousePosition, InitWindow,
    IsMouseButtonDown,
    IsMouseButtonReleased, MOUSE_BUTTON_LEFT, RAYWHITE, RED, SetConfigFlags, SetTargetFPS, Vector2, WindowShouldClose } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - cubic-bezier lines");

    let startPoint = new Vector2( 30, 30 );
    let endPoint = new Vector2( screenWidth - 30, screenHeight - 30 );
    let moveStartPoint = false;
    let moveEndPoint = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        let mouse = GetMousePosition();

        if (CheckCollisionPointCircle(mouse, startPoint, 10) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) moveStartPoint = true;
        else if (CheckCollisionPointCircle(mouse, endPoint, 10) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) moveEndPoint = true;

        if (moveStartPoint) {
            startPoint = mouse;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) moveStartPoint = false;
        }

        if (moveEndPoint) {
            endPoint = mouse;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) moveEndPoint = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("MOVE START-END POINTS WITH MOUSE", 15, 20, 20, GRAY);

            // Draw line Cubic Bezier, in-out interpolation (easing), no control points
            DrawLineBezier(startPoint, endPoint, 4, BLUE);
            
            // Draw start-end spline circles with some details
            DrawCircleV(startPoint, CheckCollisionPointCircle(mouse, startPoint, 10)? 14 : 8, moveStartPoint? RED : BLUE);
            DrawCircleV(endPoint, CheckCollisionPointCircle(mouse, endPoint, 10)? 14 : 8, moveEndPoint? RED : BLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
