/*******************************************************************************************
*
*   raylib [shapes] example - rectangle scaling by mouse
*
*   Example complexity rating: [★★☆☆] 2/4
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

import {BeginDrawing, CheckCollisionPointRec,
    ClearBackground, CloseWindow, DrawRectangleLinesEx, DrawRectangleRec, DrawText,
    DrawTriangle,
    EndDrawing,
    Fade, GRAY, GREEN, GetMousePosition, GetScreenHeight, GetScreenWidth, InitWindow,
    IsMouseButtonPressed, IsMouseButtonReleased, MOUSE_BUTTON_LEFT,
    RAYWHITE, RED, Rectangle, SetTargetFPS, Vector2, WindowShouldClose } from "rayjs:raylib";

const MOUSE_SCALE_MARK_SIZE = 12;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - rectangle scaling mouse");

    let rec = new Rectangle( 100, 100, 200, 80 );

    let mousePosition = new Vector2();

    let mouseScaleReady = false;
    let mouseScaleMode = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        mousePosition = GetMousePosition();

        if (CheckCollisionPointRec(mousePosition, new Rectangle( rec.x + rec.width - MOUSE_SCALE_MARK_SIZE, rec.y + rec.height - MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE ))) {
            mouseScaleReady = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseScaleMode = true;
        }
        else mouseScaleReady = false;

        if (mouseScaleMode) {
            mouseScaleReady = true;

            rec.width = (mousePosition.x - rec.x);
            rec.height = (mousePosition.y - rec.y);

            // Check minimum rec size
            if (rec.width < MOUSE_SCALE_MARK_SIZE) rec.width = MOUSE_SCALE_MARK_SIZE;
            if (rec.height < MOUSE_SCALE_MARK_SIZE) rec.height = MOUSE_SCALE_MARK_SIZE;
            
            // Check maximum rec size
            if (rec.width > (GetScreenWidth() - rec.x)) rec.width = GetScreenWidth() - rec.x;
            if (rec.height > (GetScreenHeight() - rec.y)) rec.height = GetScreenHeight() - rec.y;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) mouseScaleMode = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Scale rectangle dragging from bottom-right corner!", 10, 10, 20, GRAY);

            DrawRectangleRec(rec, Fade(GREEN, 0.5));

            if (mouseScaleReady) {
                DrawRectangleLinesEx(rec, 1, RED);
                DrawTriangle(new Vector2( rec.x + rec.width - MOUSE_SCALE_MARK_SIZE, rec.y + rec.height ),
                             new Vector2( rec.x + rec.width, rec.y + rec.height ),
                             new Vector2( rec.x + rec.width, rec.y + rec.height - MOUSE_SCALE_MARK_SIZE ), RED);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}