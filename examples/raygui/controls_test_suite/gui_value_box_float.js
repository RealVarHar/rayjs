/*******************************************************************************************
*
*   raygui - controls test suite
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
import {BeginDrawing, ClearBackground,
    CloseWindow, EndDrawing, GetColor, InitWindow, Rectangle, SetTargetFPS, WindowShouldClose } from 'rayjs:raylib';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //---------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raygui - controls test suite");

    let valueBoxValue = [0];
    let valueBoxEditMode = false;
    let valueBoxTextValue = "1";

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.BACKGROUND_COLOR)));

            if (rg.GuiValueBoxFloat(new Rectangle( 25, 175, 125, 30 ), null, valueBoxTextValue, valueBoxValue, valueBoxEditMode)) {
                valueBoxEditMode = !valueBoxEditMode;
                
                console.log(`Value: ${valueBoxValue[0]}`);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
