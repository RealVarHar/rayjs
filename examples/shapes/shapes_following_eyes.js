/*******************************************************************************************
*
*   raylib [shapes] example - following eyes
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BLACK, BROWN, BeginDrawing, CheckCollisionPointCircle, ClearBackground, CloseWindow, DARKGREEN, DrawCircleV, DrawFPS, EndDrawing, GetMousePosition, GetScreenHeight, GetScreenWidth, InitWindow, LIGHTGRAY, RAYWHITE, SetTargetFPS, Vector2, WindowShouldClose } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - following eyes");

    let scleraLeftPosition  = new Vector2( GetScreenWidth()/2 - 100, GetScreenHeight()/2 );
    let scleraRightPosition = new Vector2( GetScreenWidth()/2 + 100, GetScreenHeight()/2 );
    let scleraRadius = 80;

    let irisLeftPosition  = new Vector2( GetScreenWidth()/2 - 100, GetScreenHeight()/2 );
    let irisRightPosition = new Vector2( GetScreenWidth()/2 + 100, GetScreenHeight()/2 );
    let irisRadius = 24;

    let angle = 0;
    let dx = 0, dy = 0, dxx = 0, dyy = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        irisLeftPosition = GetMousePosition();
        irisRightPosition = GetMousePosition();

        // Check not inside the left eye sclera
        if (!CheckCollisionPointCircle(irisLeftPosition, scleraLeftPosition, scleraRadius - irisRadius)) {
            dx = irisLeftPosition.x - scleraLeftPosition.x;
            dy = irisLeftPosition.y - scleraLeftPosition.y;

            angle = Math.atan2(dy, dx);

            dxx = (scleraRadius - irisRadius)*Math.cos(angle);
            dyy = (scleraRadius - irisRadius)*Math.sin(angle);

            irisLeftPosition.x = scleraLeftPosition.x + dxx;
            irisLeftPosition.y = scleraLeftPosition.y + dyy;
        }

        // Check not inside the right eye sclera
        if (!CheckCollisionPointCircle(irisRightPosition, scleraRightPosition, scleraRadius - irisRadius)) {
            dx = irisRightPosition.x - scleraRightPosition.x;
            dy = irisRightPosition.y - scleraRightPosition.y;

            angle = Math.atan2(dy, dx);

            dxx = (scleraRadius - irisRadius)*Math.cos(angle);
            dyy = (scleraRadius - irisRadius)*Math.sin(angle);

            irisRightPosition.x = scleraRightPosition.x + dxx;
            irisRightPosition.y = scleraRightPosition.y + dyy;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircleV(scleraLeftPosition, scleraRadius, LIGHTGRAY);
            DrawCircleV(irisLeftPosition, irisRadius, BROWN);
            DrawCircleV(irisLeftPosition, 10, BLACK);

            DrawCircleV(scleraRightPosition, scleraRadius, LIGHTGRAY);
            DrawCircleV(irisRightPosition, irisRadius, DARKGREEN);
            DrawCircleV(irisRightPosition, 10, BLACK);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}