/*******************************************************************************************
*
*   raygui - custom file dialog to load image
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
for (const key in rg) { globalThis[key] = rg[key] };
import {
    BeginDrawing, BLACK, ClearBackground, CloseWindow, DrawRectangleLines, DrawText, DrawTexture, EndDrawing, GetColor, GetScreenHeight, GetScreenWidth, GetWorkingDirectory, GRAY, InitWindow, IsFileExtension, LoadTexture, Rectangle, SetExitKey, SetTargetFPS, TextFormat, Texture, UnloadTexture, WHITE, WindowShouldClose
} from "rayjs:raylib";
import {InitGuiWindowFileDialog, GuiWindowFileDialog} from "./gui_window_file_dialog.js";
import {
    BACKGROUND_COLOR, DEFAULT, GuiButton, GuiGetStyle, GuiIconText, GuiLock, GuiUnlock, ICON_FILE_OPEN
} from "rayjs:raygui";
import * as os from "qjs:os";


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //---------------------------------------------------------------------------------------
    let screenWidth = 800;
    let screenHeight = 560;

    InitWindow(screenWidth, screenHeight, "raygui - custom modal dialog");
    SetExitKey(0);

    // Custom file dialog
    let fileDialogState = InitGuiWindowFileDialog(GetWorkingDirectory());

    let exitWindow = false;

    let fileNameToLoad = "";

    let texture = new Texture();

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    let PATH_SEPERATOR = "/";
    if(os.platform == "win32"){
        PATH_SEPERATOR = "\\";
    }

    // Main game loop
    while (!exitWindow) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        exitWindow = WindowShouldClose();

        if (fileDialogState.SelectFilePressed) {
            // Load image file (if supported extension)
            if (IsFileExtension(fileDialogState.fileNameText, ".png")) {
                fileNameToLoad = TextFormat(`%s${PATH_SEPERATOR}%s`, fileDialogState.dirPathText, fileDialogState.fileNameText);
                UnloadTexture(texture);
                texture = LoadTexture(fileNameToLoad);
            }

            fileDialogState.SelectFilePressed = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            DrawTexture(texture, GetScreenWidth()/2 - texture.width/2, GetScreenHeight()/2 - texture.height/2 - 5, WHITE);
            DrawRectangleLines(GetScreenWidth()/2 - texture.width/2, GetScreenHeight()/2 - texture.height/2 - 5, texture.width, texture.height, BLACK);

            DrawText(fileNameToLoad, 208, GetScreenHeight() - 20, 10, GRAY);

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (fileDialogState.windowActive) GuiLock();

            if (GuiButton(new Rectangle( 20, 20, 140, 30 ), GuiIconText(ICON_FILE_OPEN, "Open Image"))) fileDialogState.windowActive = true;

            GuiUnlock();

            // GUI: Dialog Window
            //--------------------------------------------------------------------------------
            GuiWindowFileDialog(fileDialogState);
            //--------------------------------------------------------------------------------

            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);     // Unload texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
