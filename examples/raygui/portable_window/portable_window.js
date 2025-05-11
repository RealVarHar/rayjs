/*******************************************************************************************
*
*   raygui - portable window
*
*   DEPENDENCIES:
*       raylib 4.0  - Windowing/input management and drawing.
*       raygui 3.0  - Immediate-mode GUI controls.
*
*   COMPILATION (Windows - MinGW):
*       gcc -o $(NAME_PART).exe $(FILE_NAME) -I../../src -lraylib -lopengl32 -lgdi32 -std=c99
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2016-2024 Ramon Santamaria (@raysan5)
*
**********************************************************************************************/

import * as rg from 'rayjs:raygui';
import {BeginDrawing, CheckCollisionPointRec, ClearBackground,
    CloseWindow, DARKGRAY, DrawText, EndDrawing, FLAG_WINDOW_UNDECORATED,
    GetMousePosition, GetWindowPosition, InitWindow,
    IsMouseButtonPressed, IsMouseButtonReleased, MOUSE_LEFT_BUTTON,
    RAYWHITE,
    Rectangle, SetConfigFlags, SetTargetFPS, SetWindowPosition, TextFormat, Vector2, WindowShouldClose } from 'rayjs:raylib';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //---------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 600;
    
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(screenWidth, screenHeight, "raygui - portable window");

    // General variables
    let mousePosition = new Vector2();
    let windowPosition = new Vector2( 500, 200 );
    let panOffset = mousePosition;
    let dragWindow = false;
    
    SetWindowPosition(windowPosition.x, windowPosition.y);
    
    let exitWindow = false;
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!exitWindow && !WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        mousePosition = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !dragWindow) {
            if (CheckCollisionPointRec(mousePosition, new Rectangle( 0, 0, screenWidth, 20 ))) {
                windowPosition = GetWindowPosition();
                dragWindow = true;
                panOffset = mousePosition;
            }
        }

        if (dragWindow) {
            windowPosition.x += (mousePosition.x - panOffset.x);
            windowPosition.y += (mousePosition.y - panOffset.y);

            SetWindowPosition(Math.floor(windowPosition.x), Math.floor(windowPosition.y));
            
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragWindow = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            exitWindow = 1 == rg.GuiWindowBox(new Rectangle( 0, 0, screenWidth, screenHeight ), "#198# PORTABLE WINDOW");
            
            DrawText(TextFormat("Mouse Position: [ %.0f, %.0f ]", mousePosition.x, mousePosition.y), 10, 40, 10, DARKGRAY);
            DrawText(TextFormat("Window Position: [ %.0f, %.0f ]", windowPosition.x, windowPosition.y), 10, 60, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
