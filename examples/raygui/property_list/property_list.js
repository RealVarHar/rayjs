/*******************************************************************************************
*
*   raygui - custom property list control
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
*   Copyright (c) 2020-2024 Vlad Adrian (@Demizdor) and Ramon Santamaria (@raysan5)
*
**********************************************************************************************/

import * as dpl from "./dm_property_list.js";
import {BeginDrawing, ClearBackground,
    CloseWindow,
    DrawText, EndDrawing, GetColor, GetFPS, InitWindow, Rectangle, SetTargetFPS, TextFormat, Vector2, WindowShouldClose } from 'rayjs:raylib';
import {BACKGROUND_COLOR, DEFAULT, GuiGetStyle,
    GuiGrid, GuiLoadStyleDefault, GuiSetStyle, LISTVIEW, LIST_ITEMS_HEIGHT, SCROLLBAR_WIDTH } from 'rayjs:raygui';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //---------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "raygui - property list");
    
    let prop = [
        dpl.PBOOL("Bool", 0, true),
        dpl.PSECTION("#102#SECTION", 0, 2),
        dpl.PINT("Int", 0, 123),
        dpl.PFLOAT("Float", 0, 0.99),
        dpl.PTEXT("Text", 0, "Hello!", 30),
        dpl.PSELECT("Select", 0, "ONE;TWO;THREE;FOUR", 0),
        dpl.PINT_RANGE("Int Range", 0, 32, 1, 0, 100),
        dpl.PRECT("Rect", 0, 0, 0, 100, 200),
        dpl.PVEC2("Vec2", 0, 20, 20),
        dpl.PVEC3("Vec3", 0, 12, 13, 14),
        dpl.PVEC4("Vec4", 0, 12, 13, 14, 15),
        dpl.PCOLOR("Color", 0, 0, 255, 0, 255)
    ];
    
    let focus = 0, scroll = 0; // Needed by GuiDMPropertyList()

    GuiLoadStyleDefault();
    
    // Tweak the default raygui style a bit
    GuiSetStyle(LISTVIEW, LIST_ITEMS_HEIGHT, 24);
    GuiSetStyle(LISTVIEW, SCROLLBAR_WIDTH, 12);

    let gridMouseCell = new Vector2();
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
            let gridMouseCellptr = [gridMouseCell];
            let focusptr = [focus];
            let scrollptr = [scroll];
        
            GuiGrid(new Rectangle( 0, 0, screenWidth, screenHeight), "Property List", 20, 2, gridMouseCellptr); // Draw a fancy grid

            dpl.GuiDMPropertyList(new Rectangle((screenWidth - 180)/2, (screenHeight - 280)/2, 180, 280), prop, prop.length, focusptr, scrollptr);
            gridMouseCell = gridMouseCellptr[0];
            focus = focusptr[0];
            scroll = scrollptr[0];
        
            if (prop[0].value.vbool >= 1) {
                DrawText(TextFormat("FOCUS:%i | SCROLL:%i | FPS:%i", focus, scroll, GetFPS()), prop[8].value.v2.x, prop[8].value.v2.y, 20, prop[11].value.vcolor);
            }
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    dpl.GuiDMSaveProperties("test.props", prop, prop.length);  // Save properties to `test.props` file at exit
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}

