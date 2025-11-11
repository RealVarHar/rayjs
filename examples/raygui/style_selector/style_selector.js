/*******************************************************************************************
*
*   raygui - style selector
*
*   DEPENDENCIES:
*       raylib 4.5          - Windowing/input management and drawing
*       raygui 3.5          - Immediate-mode GUI controls with custom styling and icons
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

//#define RAYGUI_CUSTOM_ICONS     // It requires providing gui_icons.h in the same directory
//#include "gui_icons.h"          // External icons data provided, it can be generated with rGuiIcons tool

// raygui embedded styles
// NOTE: Included in the same order as selector
const MAX_GUI_STYLES_AVAILABLE = 12;          // NOTE: Included light style
import {GuiLoadStyleJungle}   from "../styles/_style_jungle.js";   // raygui style: jungle
import {GuiLoadStyleCandy}    from "../styles/_style_candy.js";    // raygui style: candy
import {GuiLoadStyleLavanda}  from "../styles/_style_lavanda.js";  // raygui style: lavanda
import {GuiLoadStyleCyber}    from "../styles/_style_cyber.js";    // raygui style: cyber
import {GuiLoadStyleTerminal} from "../styles/_style_terminal.js" ; // raygui style: terminal
import {GuiLoadStyleAshes}    from "../styles/_style_ashes.js";    // raygui style: ashes
import {GuiLoadStyleBluish}   from "../styles/_style_bluish.js";   // raygui style: bluish
import {GuiLoadStyleDark}     from "../styles/_style_dark.js";     // raygui style: dark
import {GuiLoadStyleCherry}   from "../styles/_style_cherry.js";   // raygui style: cherry
import {GuiLoadStyleSunny}    from "../styles/_style_sunny.js";    // raygui style: sunny
import {GuiLoadStyleEnefete}  from "../styles/_style_enefete.js";  // raygui style: enefete
import {
    BLACK,
    BeginDrawing, ClearBackground,
    CloseWindow,
    DrawRectangle,
    DrawRectangleLines, DrawTexture,
    EndDrawing, GetColor, InitWindow, IsFileDropped, IsFileExtension, IsKeyPressed, KEY_ESCAPE,
    LoadDroppedFiles, Rectangle, SetExitKey, SetTargetFPS, WHITE, WindowShouldClose } from 'rayjs:raylib';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //---------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "raygui - styles selector");
    SetExitKey(0);

    // Custom GUI font loading
    //Font font = LoadFontEx("fonts/custom_font.ttf", 12, 0, 0);
    //GuiSetFont(font);

    let exitWindow = false;
    let showMessageBox = false;

    // Load default style
    GuiLoadStyleCyber();
    let visualStyleActive = 4;
    let prevVisualStyleActive = 4;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!exitWindow) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        exitWindow = WindowShouldClose();

        if (IsKeyPressed(KEY_ESCAPE)) showMessageBox = !showMessageBox;

        if (IsFileDropped()) {
            let droppedFiles = LoadDroppedFiles();

            if ((droppedFiles.length > 0) && IsFileExtension(droppedFiles[0], ".rgs")) rg.GuiLoadStyle(droppedFiles[0]);
        }

        if (visualStyleActive != prevVisualStyleActive) {
            // Reset to default internal style
            // NOTE: Required to unload any previously loaded font texture
            rg.GuiLoadStyleDefault();

            switch (visualStyleActive) {
                case 1: GuiLoadStyleJungle(); break;
                case 2: GuiLoadStyleCandy(); break;
                case 3: GuiLoadStyleLavanda(); break;
                case 4: GuiLoadStyleCyber(); break;
                case 5: GuiLoadStyleTerminal(); break;
                case 6: GuiLoadStyleAshes(); break;
                case 7: GuiLoadStyleBluish(); break;
                case 8: GuiLoadStyleDark(); break;
                case 9: GuiLoadStyleCherry(); break;
                case 10: GuiLoadStyleSunny(); break;
                case 11: GuiLoadStyleEnefete(); break;
                default: break;
            }

            prevVisualStyleActive = visualStyleActive;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.BACKGROUND_COLOR)));

            // Visuals options
            rg.GuiLabel(new Rectangle( 10, 10, 60, 24 ), "Style:");
            let visualStyleActiveptr = [visualStyleActive];
            rg.GuiComboBox(new Rectangle( 60,10, 120, 24 ), "default;Jungle;Candy;Lavanda;Cyber;Terminal;Ashes;Bluish;Dark;Cherry;Sunny;Enefete", visualStyleActiveptr);
            visualStyleActive = visualStyleActiveptr[0];

            DrawRectangle(10, 44, rg.GuiGetFont().texture.width, rg.GuiGetFont().texture.height, BLACK);
            DrawTexture(rg.GuiGetFont().texture, 10, 44, WHITE);
            DrawRectangleLines(10, 44, rg.GuiGetFont().texture.width, rg.GuiGetFont().texture.height,
            GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.LINE_COLOR)));

            //GuiSetIconScale(2);
            //GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_RIGHT);
            //GuiButton((Rectangle){ 25, 255, 300, 30 }, GuiIconText(ICON_FILE_SAVE, "Save File"));
            //GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
