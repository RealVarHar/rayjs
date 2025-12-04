/*******************************************************************************************
*
*   raygui - controls test suite
*
*   TEST CONTROLS:
*       - GuiDropdownBox()
*       - GuiCheckBox()
*       - GuiSpinner()
*       - GuiValueBox()
*       - GuiTextBox()
*       - GuiButton()
*       - GuiComboBox()
*       - GuiListView()
*       - GuiToggleGroup()
*       - GuiColorPicker()
*       - GuiSlider()
*       - GuiSliderBar()
*       - GuiProgressBar()
*       - GuiColorBarAlpha()
*       - GuiScrollPanel()
*
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

import {
    BeginDrawing, ClearBackground,
    CloseWindow,
    Color,
    DrawRectangle,
    EndDrawing,
    Fade,
    GetColor, GetScreenHeight,
    GetScreenWidth, InitWindow, IsFileDropped, IsFileExtension, IsKeyDown, IsKeyPressed, KEY_ESCAPE,
    KEY_LEFT,
    KEY_LEFT_CONTROL,
    KEY_RIGHT, KEY_S, KEY_SPACE, LoadDroppedFiles, RAYWHITE, RED, Rectangle, SetExitKey, SetTargetFPS,
    TextFormat, Vector2, WindowShouldClose } from 'rayjs:raylib';
import {BACKGROUND_COLOR, BUTTON, DEFAULT,
    DROPDOWNBOX,
    GuiButton, GuiCheckBox,
    GuiColorBarAlpha,
    GuiColorPicker, GuiComboBox,
    GuiDropdownBox,
    GuiEnable, GuiGetStyle,
    GuiGrid, GuiGroupBox, GuiIconText,
    GuiListView,
    GuiListViewEx, GuiLoadStyle, GuiLoadStyleDefault,
    GuiLock,
    GuiMessageBox,
    GuiPanel,
    GuiProgressBar,
    GuiScrollPanel, GuiSetAlpha, GuiSetState, GuiSetStyle,
    GuiSlider,
    GuiSliderBar, GuiSpinner,
    GuiStatusBar,
    GuiTextBox,
    GuiTextInputBox,
    GuiToggleGroup,
    GuiToggleSlider,
    GuiUnlock,
    GuiValueBox, ICON_EXIT, ICON_FILE_SAVE, LABEL,
    LISTVIEW,
    LIST_ITEMS_BORDER_NORMAL,
    SLIDER,
    SLIDER_PADDING,
    STATE_DISABLED,
    STATE_FOCUSED, STATE_NORMAL, STATE_PRESSED, TEXTBOX, TEXT_ALIGNMENT,
    TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_CENTER, TEXT_ALIGN_LEFT,
    TEXT_ALIGN_MIDDLE, TEXT_ALIGN_TOP, TEXT_PADDING, TEXT_WRAP_MODE,
    TEXT_WRAP_NONE, TEXT_WRAP_WORD } from 'rayjs:raygui';
//#include "gui_icons.h"          // External icons data provided, it can be generated with rGuiIcons tool

// raygui embedded styles
import {GuiLoadStyleCyber}    from "../styles/_style_cyber.js";       // raygui style: cyber
import {GuiLoadStyleJungle}   from "../styles/_style_jungle.js";      // raygui style: jungle
import {GuiLoadStyleLavanda}  from "../styles/_style_lavanda.js";     // raygui style: lavanda
import {GuiLoadStyleDark}     from "../styles/_style_dark.js";        // raygui style: dark
import {GuiLoadStyleBluish}   from "../styles/_style_bluish.js";      // raygui style: bluish
import {GuiLoadStyleTerminal} from "../styles/_style_terminal.js";    // raygui style: terminal
import {GuiLoadStyleCandy}    from "../styles/_style_candy.js";
import {GuiLoadStyleCherry}   from "../styles/_style_cherry.js";
import {GuiLoadStyleAshes}    from "../styles/_style_ashes.js";
import {GuiLoadStyleEnefete}  from "../styles/_style_enefete.js";
import {GuiLoadStyleSunny}    from "../styles/_style_sunny.js";
import {GuiLoadStyleAmber}    from "../styles/_style_amber.js";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //---------------------------------------------------------------------------------------
    const screenWidth = 960;
    const screenHeight = 560;

    InitWindow(screenWidth, screenHeight, "raygui - controls test suite");
    SetExitKey(0);

    // GUI controls initialization
    //----------------------------------------------------------------------------------
    let dropdownBox000Active = [0];
    let dropDown000EditMode = false;

    let dropdownBox001Active = [0];
    let dropDown001EditMode = false;

    let spinner001Value = [0];
    let spinnerEditMode = false;

    let valueBox002Value = [0];
    let valueBoxEditMode = false;

    let textBoxText = ["Text box"];
    let textBoxEditMode = false;

    let textBoxMultiText = ["Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\n\nThisisastringlongerthanexpectedwithoutspacestotestcharbreaksforthosecases,checkingifworkingasexpected.\n\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."];
    let textBoxMultiEditMode = false;

    let listViewScrollIndex = [0];
    let listViewActive = [-1];

    let listViewExScrollIndex = [0];
    let listViewExActive = [2];
    let listViewExFocus = [-1];
    let listViewExList = [ "This", "is", "a", "list view", "with", "disable", "elements", "amazing!" ];

    let colorPickerValue = new Color(RED.r,RED.g,RED.b,RED.a);

    let sliderValue = [50];
    let sliderBarValue = [60];
    let progressValue = [0.1];

    let forceSquaredChecked = [false];

    let alphaValue = [0.5];

    //int comboBoxActive = 1;
    let visualStyleActive = [0];
    let prevVisualStyleActive = 0;

    let toggleGroupActive = [0];
    let toggleSliderActive = [0];

    let viewScroll = new Vector2( 0, 0 );
    //----------------------------------------------------------------------------------

    // Custom GUI font loading
    //Font font = LoadFontEx("fonts/rainyhearts16.ttf", 12, 0, 0);
    //GuiSetFont(font);

    let exitWindow = false;
    let showMessageBox = false;

    let textInput = "";
    let textInputFileName = "";
    let showTextInputBox = false;

    let alpha = 1;

    // DEBUG: Testing how those two properties affect all controls!
    //GuiSetStyle(DEFAULT, TEXT_PADDING, 0);
    //GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!exitWindow) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        exitWindow = WindowShouldClose();

        if (IsKeyPressed(KEY_ESCAPE)) showMessageBox = !showMessageBox;

        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) showTextInputBox = true;

        if (IsFileDropped()) {
            let droppedFiles = LoadDroppedFiles();

            if ((droppedFiles.length > 0) && IsFileExtension(droppedFiles[0], ".rgs")) GuiLoadStyle(droppedFiles[0]);
        }

        //alpha -= 0.002;
        if (alpha < 0) alpha = 0;
        if (IsKeyPressed(KEY_SPACE)) alpha = 1;

        GuiSetAlpha(alpha);

        //progressValue += 0.002f;
        if (IsKeyPressed(KEY_LEFT)) progressValue[0] -= 0.1;
        else if (IsKeyPressed(KEY_RIGHT)) progressValue[0] += 0.1;
        if (progressValue[0] > 1) progressValue[0] = 1;
        else if (progressValue[0] < 0) progressValue[0] = 0;

        if (visualStyleActive[0] != prevVisualStyleActive) {
            GuiLoadStyleDefault();

            switch (visualStyleActive[0]) {
                case 0: break;      // Default style
                case 1: GuiLoadStyleJungle(); break;
                case 2: GuiLoadStyleLavanda(); break;
                case 3: GuiLoadStyleDark(); break;
                case 4: GuiLoadStyleBluish(); break;
                case 5: GuiLoadStyleCyber(); break;
                case 6: GuiLoadStyleTerminal(); break;
                case 7: GuiLoadStyleCandy(); break;
                case 8: GuiLoadStyleCherry(); break;
                case 9: GuiLoadStyleAshes(); break;
                case 10: GuiLoadStyleEnefete(); break;
                case 11: GuiLoadStyleSunny(); break;
                case 12: GuiLoadStyleAmber(); break;
                default: break;
            }

            GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

            prevVisualStyleActive = visualStyleActive[0];
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            // Check all possible events that require GuiLock
            if (dropDown000EditMode || dropDown001EditMode) GuiLock();

            // First GUI column
            //GuiSetStyle(CHECKBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
            GuiCheckBox(new Rectangle( 25, 108, 15, 15 ), "FORCE CHECK!", forceSquaredChecked);

            GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
            //GuiSetStyle(VALUEBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
            if (GuiSpinner(new Rectangle( 25, 135, 125, 30 ), null, spinner001Value, 0, 100, spinnerEditMode)) spinnerEditMode = !spinnerEditMode;
            if (GuiValueBox(new Rectangle( 25, 175, 125, 30 ), null, valueBox002Value, 0, 100, valueBoxEditMode)) valueBoxEditMode = !valueBoxEditMode;
            GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
            //TODO: GuiTextBox should alloc additional padding to allow character insertion
            if (GuiTextBox(new Rectangle( 25, 215, 125, 30 ), textBoxText, 64, textBoxEditMode)) textBoxEditMode = !textBoxEditMode;
            GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

            if (GuiButton(new Rectangle( 25, 255, 125, 30 ), GuiIconText(ICON_FILE_SAVE, "Save File"))) showTextInputBox = true;
            GuiGroupBox(new Rectangle( 25, 310, 125, 150 ), "STATES");
            //GuiLock();
            GuiSetState(STATE_NORMAL);  if (GuiButton(new Rectangle( 30, 320, 115, 30 ), "NORMAL")) { }
            GuiSetState(STATE_FOCUSED); if (GuiButton(new Rectangle( 30, 355, 115, 30 ), "FOCUSED")) { }
            GuiSetState(STATE_PRESSED); if (GuiButton(new Rectangle( 30, 390, 115, 30 ), "#15#PRESSED")) { }
            GuiSetState(STATE_DISABLED);if (GuiButton(new Rectangle( 30, 425, 115, 30 ), "DISABLED")) { }
            GuiSetState(STATE_NORMAL);
            //GuiUnlock();

            GuiComboBox(new Rectangle( 25, 480, 125, 30 ), "default;Jungle;Lavanda;Dark;Bluish;Cyber;Terminal;Candy;Cherry;Ashes;Enefete;Sunny;Amber", visualStyleActive);
            // NOTE: GuiDropdownBox must draw after any other control that can be covered on unfolding
            GuiUnlock();
            GuiSetStyle(DROPDOWNBOX, TEXT_PADDING, 4);
            GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
            if (GuiDropdownBox(new Rectangle( 25, 65, 125, 30 ), "#01#ONE;#02#TWO;#03#THREE;#04#FOUR", dropdownBox001Active, dropDown001EditMode)) dropDown001EditMode = !dropDown001EditMode;
            GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
            GuiSetStyle(DROPDOWNBOX, TEXT_PADDING, 0);

            if (GuiDropdownBox(new Rectangle( 25, 25, 125, 30 ), "ONE;TWO;THREE", dropdownBox000Active, dropDown000EditMode)) dropDown000EditMode = !dropDown000EditMode;
            // Second GUI column
            //GuiSetStyle(LISTVIEW, LIST_ITEMS_BORDER_NORMAL, 1);
            GuiListView(new Rectangle( 165, 25, 140, 124 ), "Charmander;Bulbasaur;#18#Squirtel;Pikachu;Eevee;Pidgey", listViewScrollIndex, listViewActive);
            GuiListViewEx(new Rectangle( 165, 162, 140, 184 ), listViewExList, 8, listViewExScrollIndex, listViewExActive, listViewExFocus);
            GuiSetStyle(LISTVIEW, LIST_ITEMS_BORDER_NORMAL, 0);

            //GuiToggle((Rectangle){ 165, 400, 140, 25 }, "#1#ONE", &toggleGroupActive);
            GuiToggleGroup(new Rectangle( 165, 360, 140, 24 ), "#1#ONE\n#3#TWO\n#8#THREE\n#23#", toggleGroupActive);
            //GuiDisable();
            GuiSetStyle(SLIDER, SLIDER_PADDING, 2);
            GuiToggleSlider(new Rectangle( 165, 480, 140, 30 ), "ON;OFF", toggleSliderActive);
            GuiSetStyle(SLIDER, SLIDER_PADDING, 0);
            // Third GUI column
            GuiPanel(new Rectangle( 320, 25, 225, 140 ), "Panel Info");
            GuiColorPicker(new Rectangle( 320, 185, 196, 192 ), null, colorPickerValue);

            //GuiDisable();
            GuiSlider(new Rectangle( 355, 400, 165, 20 ), "TEST", TextFormat("%2.2f", sliderValue[0]), sliderValue, -50, 100);
            GuiSliderBar(new Rectangle( 320, 430, 200, 20 ), null, TextFormat("%i", sliderBarValue[0]), sliderBarValue, 0, 100);
            
            GuiProgressBar(new Rectangle( 320, 460, 200, 20 ), null, TextFormat("%i%%", Math.floor(progressValue[0]*100)), progressValue, 0, 1);
            GuiEnable();

            // NOTE: View rectangle could be used to perform some scissor test
            let view = new Rectangle();
            GuiScrollPanel(new Rectangle( 560, 25, 102, 354 ), null, new Rectangle( 560, 25, 300, 1200 ), viewScroll, view);

            let mouseCell = new Vector2();
            GuiGrid(new Rectangle( 560, 25 + 180 + 195, 100, 120 ), null, 20, 3, mouseCell);

            GuiColorBarAlpha(new Rectangle( 320, 490, 200, 30 ), null, alphaValue);

            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_TOP);   // WARNING: Word-wrap does not work as expected in case of no-top alignment
            GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_WORD);            // WARNING: If wrap mode enabled, text editing is not supported
            if (GuiTextBox(new Rectangle( 678, 25, 258, 492 ), textBoxMultiText, 1024, textBoxMultiEditMode)) textBoxMultiEditMode = !textBoxMultiEditMode;
            GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_NONE);
            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_MIDDLE);

            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
            GuiStatusBar(new Rectangle( 0, GetScreenHeight() - 20, GetScreenWidth(), 20 ), "This is a status bar");
            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
            //GuiSetStyle(STATUSBAR, TEXT_INDENTATION, 20);

            if (showMessageBox) {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8));
                let result = GuiMessageBox(new Rectangle( GetScreenWidth()/2 - 125, GetScreenHeight()/2 - 50, 250, 100 ), GuiIconText(ICON_EXIT, "Close Window"), "Do you really want to exit?", "Yes;No");

                if ((result == 0) || (result == 2)) showMessageBox = false;
                else if (result == 1) exitWindow = true;
            }

            if (showTextInputBox) {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8));
                let result = GuiTextInputBox(new Rectangle( GetScreenWidth()/2 - 120, GetScreenHeight()/2 - 60, 240, 140 ), GuiIconText(ICON_FILE_SAVE, "Save file as..."), "Introduce output file name:", "Ok;Cancel", textInput, 255, null);

                if (result == 1) {
                    // TODO: Validate textInput value and save
                    textInputFileName = textInput;
                }

                if ((result == 0) || (result == 1) || (result == 2)) {
                    showTextInputBox = false;
                    textInput = "";
                }
            }
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
