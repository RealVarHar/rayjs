/*******************************************************************************************
*
*   raygui - Controls test
*
*   TEST CONTROLS:
*       - GuiScrollPanel()
*
*   DEPENDENCIES:
*       raylib 4.0  - Windowing/input management and drawing.
*       raygui 3.0  - Immediate-mode GUI controls.
*
*   COMPILATION (Windows - MinGW):
*       gcc -o $(NAME_PART).exe $(FILE_NAME) -I../../src -lraylib -lopengl32 -lgdi32 -std=c99
*
*   COMPILATION (Linux - gcc):
*       gcc -o $(NAME_PART) $(FILE_NAME) -I../../src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -std=c99
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2019-2024 Vlad Adrian (@Demizdor) and Ramon Santamaria (@raysan5)
*
**********************************************************************************************/

import {ARROWS_SIZE,
    ARROWS_VISIBLE, BORDER_WIDTH,
    DEFAULT,
    GuiCheckBox, GuiGetStyle, GuiGrid, GuiGroupBox, GuiLabel, GuiScrollPanel, GuiSetStyle, GuiSliderBar, GuiSpinner,
    GuiToggle,
    LISTVIEW, SCROLLBAR, SCROLLBAR_LEFT_SIDE, SCROLLBAR_SIDE, SCROLLBAR_WIDTH, SLIDER_PADDING, SLIDER_WIDTH } from "rayjs:raygui";
import {BeginDrawing, BeginScissorMode, ClearBackground,
    CloseWindow,
    DrawRectangle,
    DrawText, EndDrawing, EndScissorMode,
    Fade, InitWindow, RAYWHITE, RED, Rectangle, SetTargetFPS, TextFormat, Vector2, WindowShouldClose } from "rayjs:raylib";

// Draw and process scroll bar style edition controls
function DrawStyleEditControls() {
    // ScrollPanel style controls
    //----------------------------------------------------------
    GuiGroupBox(new Rectangle( 550, 170, 220, 205 ), "SCROLLBAR STYLE");

    let style = [GuiGetStyle(SCROLLBAR, BORDER_WIDTH)];
    GuiLabel(new Rectangle( 555, 195, 110, 10 ), "BORDER_WIDTH");
    GuiSpinner(new Rectangle( 670, 190, 90, 20 ), null, style, 0, 6, false);
    GuiSetStyle(SCROLLBAR, BORDER_WIDTH, style[0]);

    style = [GuiGetStyle(SCROLLBAR, ARROWS_SIZE)];
    GuiLabel(new Rectangle( 555, 220, 110, 10 ), "ARROWS_SIZE");
    GuiSpinner(new Rectangle( 670, 215, 90, 20 ), null, style, 4, 14, false);
    GuiSetStyle(SCROLLBAR, ARROWS_SIZE, style[0]);

    style = [GuiGetStyle(SCROLLBAR, SLIDER_PADDING)];
    GuiLabel(new Rectangle( 555, 245, 110, 10 ), "SLIDER_PADDING");
    GuiSpinner(new Rectangle( 670, 240, 90, 20 ), null, style, 0, 14, false);
    GuiSetStyle(SCROLLBAR, SLIDER_PADDING, style[0]);

    let scrollBarArrows = [GuiGetStyle(SCROLLBAR, ARROWS_VISIBLE)==1];
    GuiCheckBox(new Rectangle( 565, 280, 20, 20 ), "ARROWS_VISIBLE", scrollBarArrows);
    GuiSetStyle(SCROLLBAR, ARROWS_VISIBLE, scrollBarArrows[0]?1:0);

    style = [GuiGetStyle(SCROLLBAR, SLIDER_PADDING)];
    GuiLabel(new Rectangle( 555, 325, 110, 10 ), "SLIDER_PADDING");
    GuiSpinner(new Rectangle( 670, 320, 90, 20 ), null, style, 0, 14, false);
    GuiSetStyle(SCROLLBAR, SLIDER_PADDING, style[0]);

    style = [GuiGetStyle(SCROLLBAR, SLIDER_WIDTH)];
    GuiLabel(new Rectangle( 555, 350, 110, 10 ), "SLIDER_WIDTH");
    GuiSpinner(new Rectangle( 670, 345, 90, 20 ), null, style, 2, 100, false);
    GuiSetStyle(SCROLLBAR, SLIDER_WIDTH, style[0]);

    const text = GuiGetStyle(LISTVIEW, SCROLLBAR_SIDE) == SCROLLBAR_LEFT_SIDE? "SCROLLBAR: LEFT" : "SCROLLBAR: RIGHT";
    let toggleScrollBarSide = [GuiGetStyle(LISTVIEW, SCROLLBAR_SIDE)==1];
    GuiToggle(new Rectangle( 560, 110, 200, 35 ), text, toggleScrollBarSide);
    GuiSetStyle(LISTVIEW, SCROLLBAR_SIDE, toggleScrollBarSide[0]?1:0);
    //----------------------------------------------------------

    // ScrollBar style controls
    //----------------------------------------------------------
    GuiGroupBox(new Rectangle( 550, 20, 220, 135 ), "SCROLLPANEL STYLE");

    style = [GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH)];
    GuiLabel(new Rectangle( 555, 35, 110, 10 ), "SCROLLBAR_WIDTH");
    GuiSpinner(new Rectangle( 670, 30, 90, 20 ), null, style, 6, 30, false);
    GuiSetStyle(LISTVIEW, SCROLLBAR_WIDTH, style[0]);

    style = [GuiGetStyle(DEFAULT, BORDER_WIDTH)];
    GuiLabel(new Rectangle( 555, 60, 110, 10 ), "BORDER_WIDTH");
    GuiSpinner(new Rectangle( 670, 55, 90, 20 ), null, style, 0, 20, false);
    GuiSetStyle(DEFAULT, BORDER_WIDTH, style[0]);
    //----------------------------------------------------------
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //---------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raygui - GuiScrollPanel()");

    let panelRec = new Rectangle( 20, 40, 200, 150 );
    let panelContentRec = new Rectangle( 0, 0, 340, 340 );
    let panelView = new Rectangle();
    let panelScroll = new Vector2( 99, -20 );

    let showContentArea = true;

    SetTargetFPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(TextFormat("[%f, %f]", panelScroll.x, panelScroll.y), 4, 4, 20, RED);

            GuiScrollPanel(panelRec, null, panelContentRec, panelScroll, panelView);

            BeginScissorMode(panelView.x, panelView.y, panelView.width, panelView.height);
                GuiGrid(new Rectangle( panelRec.x + panelScroll.x, panelRec.y + panelScroll.y, panelContentRec.width, panelContentRec.height), null, 16, 3, null);
            EndScissorMode();

            if (showContentArea) DrawRectangle(panelRec.x + panelScroll.x, panelRec.y + panelScroll.y, panelContentRec.width, panelContentRec.height, Fade(RED, 0.1));

            DrawStyleEditControls();

            let showContentAreaptr = [showContentArea];
            let widthptr=[panelContentRec.width];
            let heightptr=[panelContentRec.height];
            GuiCheckBox(new Rectangle( 565, 80, 20, 20 ), "SHOW CONTENT AREA", showContentAreaptr);
            showContentArea = showContentAreaptr[0];

            GuiSliderBar(new Rectangle( 590, 385, 145, 15 ), "WIDTH", TextFormat("%i", Math.floor(panelContentRec.width) ), widthptr, 1, 600);
            GuiSliderBar(new Rectangle( 590, 410, 145, 15 ), "HEIGHT", TextFormat("%i", Math.floor(panelContentRec.height) ), heightptr, 1, 400);
            panelContentRec.width = widthptr[0];
            panelContentRec.height = heightptr[0];

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
