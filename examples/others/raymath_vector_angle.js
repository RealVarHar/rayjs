/*******************************************************************************************
*
*   raylib [shapes] example - Vector Angle
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.0, last time updated with raylib 4.6
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BLACK, BeginDrawing, ClearBackground, CloseWindow, DARKGRAY,
    DrawCircleSector, DrawLine, DrawLineEx, DrawText,
    EndDrawing, Fade, GREEN, GetMousePosition, InitWindow, IsKeyPressed,
    IsMouseButtonDown, KEY_SPACE, LIGHTGRAY, LIME, MOUSE_BUTTON_RIGHT, RAYWHITE, RED, SetTargetFPS,
    TextFormat, Vector2, WindowShouldClose } from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    const RAD2DEG = 180.0/Math.PI;

    InitWindow(screenWidth, screenHeight, "raylib [math] example - vector angle");

    let v0 = new Vector2( screenWidth/2, screenHeight/2 );
    let v1 = rm.Vector2Add(v0, new Vector2( 100, 80 ));
    let v2 = new Vector2();             // Updated with mouse position
    
    let angle = 0;             // Angle in degrees
    let angleMode = 0;              // 0-Vector2Angle(), 1-rm.Vector2LineAngle()

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        let startangle = 0;

        if (angleMode == 0) startangle = -rm.Vector2LineAngle(v0, v1)*RAD2DEG;
        if (angleMode == 1) startangle = 0;

        v2 = GetMousePosition();

        if (IsKeyPressed(KEY_SPACE)) angleMode = -angleMode+1;
        
        if ((angleMode == 0) && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) v1 = GetMousePosition();

        if (angleMode == 0) {
            // Calculate angle between two vectors, considering a common origin (v0)
            let v1Normal = rm.Vector2Normalize(rm.Vector2Subtract(v1, v0));
            let v2Normal = rm.Vector2Normalize(rm.Vector2Subtract(v2, v0));

            angle = rm.Vector2Angle(v1Normal, v2Normal)*RAD2DEG;
        } else if (angleMode == 1) {
            // Calculate angle defined by a two vectors line, in reference to horizontal line
            angle = rm.Vector2LineAngle(v0, v2)*RAD2DEG;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            if (angleMode == 0) {
                DrawText("MODE 0: Angle between V1 and V2", 10, 10, 20, BLACK);
                DrawText("Right Click to Move V2", 10, 30, 20, DARKGRAY);
                
                DrawLineEx(v0, v1, 2, BLACK);
                DrawLineEx(v0, v2, 2, RED);

                DrawCircleSector(v0, 40, startangle, startangle + angle, 32, Fade(GREEN, 0.6));
            } else if (angleMode == 1) {
                DrawText("MODE 1: Angle formed by line V1 to V2", 10, 10, 20, BLACK);
                
                DrawLine(0, screenHeight/2, screenWidth, screenHeight/2, LIGHTGRAY);
                DrawLineEx(v0, v2, 2, RED);

                DrawCircleSector(v0, 40, startangle, startangle - angle, 32, Fade(GREEN, 0.6));
            }
            
            DrawText("v0", v0.x, v0.y, 10, DARKGRAY);

            // If the line from v0 to v1 would overlap the text, move it's position up 10
            if (angleMode == 0 && rm.Vector2Subtract(v0, v1).y > 0) DrawText("v1", v1.x, v1.y-10, 10, DARKGRAY);
            if (angleMode == 0 && rm.Vector2Subtract(v0, v1).y < 0) DrawText("v1", v1.x, v1.y, 10, DARKGRAY);

            // If angle mode 1, use v1 to emphasize the horizontal line
            if (angleMode == 1) DrawText("v1", v0.x + 40, v0.y, 10, DARKGRAY);

            // position adjusted by -10 so it isn't hidden by cursor
            DrawText("v2", v2.x-10, v2.y-10, 10, DARKGRAY);

            DrawText("Press SPACE to change MODE", 460, 10, 20, DARKGRAY);
            DrawText(TextFormat("ANGLE: %2.2f", angle), 10, 70, 20, LIME);
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
