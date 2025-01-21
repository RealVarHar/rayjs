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

import * as rl from 'rayjs:raylib';
import * as raygui from 'rayjs:raygui';
for (const key in rl) { globalThis[key] = rl[key] };
for (const key in raygui) { globalThis[key] = raygui[key] };

// Initialization
//---------------------------------------------------------------------------------------
let screenWidth = 690;
let screenHeight = 560;

initWindow(screenWidth, screenHeight, "raygui - controls test suite");
setExitKey(0);

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

let textBoxText = "Text box";
let textBoxEditMode = false;

let textBoxMultiText = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\n\nThisisastringlongerthanexpectedwithoutspacestotestcharbreaksforthosecases,checkingifworkingasexpected.\n\nExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
let textBoxMultiEditMode = false;

let listViewScrollIndex = [0];
let listViewActive = [-1];

let listViewExScrollIndex = [0];
let listViewExActive = [2];
let listViewExFocus = [-1];
let listViewExList = [ "This", "is", "a", "list view", "with", "disable", "elements", "amazing!" ];

let colorPickerValue = RED;

let sliderValue = [50];
let sliderBarValue = [60];
let progressValue = 0.4;

let forceSquaredChecked = [false];

let alphaValue = [0.5];

//let comboBoxActive = 1;
let visualStyleActive = [0];
let prevVisualStyleActive = 0;

let toggleGroupActive = [0];
let toggleSliderActive = [0];

let viewScroll = new Vector2(0,0);
//----------------------------------------------------------------------------------

// Custom GUI font loading
//let font = loadFontEx("fonts/rainyhearts16.ttf", 12, 0, 0);
//guiSetFont(font);

let exitWindow = false;
let showMessageBox = false;

let textInput = "";
let textInputFileName = "";
let showTextInputBox = false;

let alpha  = 1;

setTargetFPS(60);
//--------------------------------------------------------------------------------------

// Main game loop
while (!exitWindow)    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    exitWindow = windowShouldClose();

    if (isKeyPressed(KEY_ESCAPE)) showMessageBox = !showMessageBox;

    if (isKeyDown(KEY_LEFT_CONTROL) && isKeyPressed(KEY_S)) showTextInputBox = true;

    if (isFileDropped())
    {
        let droppedFiles = loadDroppedFiles();

        if ((droppedFiles.length > 0) && isFileExtension(droppedFiles[0], ".rgs")) guiLoadStyle(droppedFiles[0]);
		
		//UnloadDroppedFiles(droppedFiles);    // called automatically
    }
	
	//alpha -= 0.002f;
	if (alpha < 0) alpha = 0;
	if (isKeyPressed(KEY_SPACE)) alpha = 1;
	
	guiSetAlpha(alpha);
	
	//progressValue += 0.002f;
	if (isKeyPressed(KEY_LEFT)) progressValue -= 0.1;
	else if (isKeyPressed(KEY_RIGHT)) progressValue += 0.1;
	if (progressValue > 1) progressValue = 1;
    else if (progressValue < 0) progressValue = 0;
	
	if (visualStyleActive != prevVisualStyleActive)
    {
        guiLoadStyleDefault();

        switch (visualStyleActive)
        {
            case 0: break;      // Default style
            case 1: guiLoadStyleJungle(); break;
            case 2: guiLoadStyleLavanda(); break;
            case 3: guiLoadStyleDark(); break;
            case 4: guiLoadStyleBluish(); break;
            case 5: guiLoadStyleCyber(); break;
            case 6: guiLoadStyleTerminal(); break;
            default: break;
        }

        guiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

        prevVisualStyleActive = visualStyleActive;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    beginDrawing();

        clearBackground(getColor(guiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        // raygui: controls drawing
        //----------------------------------------------------------------------------------
        // Check all possible events that require GuiLock
        if (dropDown000EditMode || dropDown001EditMode) guiLock();

        // First GUI column
        //guiSetStyle(CHECKBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        guiCheckBox(new Rectangle(25, 108, 15, 15), "FORCE CHECK!", forceSquaredChecked);

        guiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        //guiSetStyle(VALUEBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (guiSpinner(new Rectangle(25, 135, 125, 30), null, spinner001Value, 0, 100, spinnerEditMode)) spinnerEditMode = !spinnerEditMode;
        if (guiValueBox(new Rectangle(25, 175, 125, 30), null, valueBox002Value, 0, 100, valueBoxEditMode)) valueBoxEditMode = !valueBoxEditMode;
        guiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (guiTextBox(new Rectangle(25, 215, 125, 30), textBoxText, textBoxEditMode)) textBoxEditMode = !textBoxEditMode;

        guiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

        if (guiButton(new Rectangle(25, 255, 125, 30), guiIconText(ICON_FILE_SAVE, "Save File"))) showTextInputBox = true;

        guiGroupBox(new Rectangle(25, 310, 125, 150), "STATES");
        //guiLock();
        guiSetState(STATE_NORMAL); if (guiButton(new Rectangle(30, 320, 115, 30), "NORMAL")) { }
        guiSetState(STATE_FOCUSED); if (guiButton(new Rectangle(30, 355, 115, 30), "FOCUSED")) { }
        guiSetState(STATE_PRESSED); if (guiButton(new Rectangle(30, 390, 115, 30), "#15#PRESSED")) { }
        guiSetState(STATE_DISABLED); if (guiButton(new Rectangle(30, 425, 115, 30), "DISABLED")) { }
        guiSetState(STATE_NORMAL);
        //guiUnlock();

        guiComboBox(new Rectangle(25, 470, 125, 30), "default;Jungle;Lavanda;Dark;Bluish;Cyber;Terminal", visualStyleActive);

        // NOTE: GuiDropdownBox must draw after any other control that can be covered on unfolding
        guiUnlock();
        guiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (guiDropdownBox(new Rectangle(25, 65, 125, 30), "#01#ONE;#02#TWO;#03#THREE;#04#FOUR", dropdownBox001Active, dropDown001EditMode)) dropDown001EditMode = !dropDown001EditMode;
		guiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        guiSetStyle(DROPDOWNBOX, TEXT_PADDING, 0);

        if (guiDropdownBox(new Rectangle(25, 25, 125, 30), "ONE;TWO;THREE", dropdownBox000Active, dropDown000EditMode)) dropDown000EditMode = !dropDown000EditMode;

        // Second GUI column
        guiListView(new Rectangle(165, 25, 140, 140), "Charmander;Bulbasaur;#18#Squirtel;Pikachu;Eevee;Pidgey", listViewScrollIndex, listViewActive);
        //guiListViewEx(new Rectangle(165, 180, 140, 200), listViewExList, 8, listViewExScrollIndex, listViewExActive, listViewExFocus);//rayjs: unimplemented

		//GuiToggle((Rectangle){ 165, 400, 140, 25 }, "#1#ONE", &toggleGroupActive);
        guiToggleGroup(new Rectangle(165, 400, 140, 25), "#1#ONE\n#3#TWO\n#8#THREE\n#23#", toggleGroupActive);
		//GuiDisable();
        guiSetStyle(SLIDER, SLIDER_PADDING, 2);
        guiToggleSlider(new Rectangle(165, 480, 140, 30), "ON;OFF", toggleSliderActive);
        guiSetStyle(SLIDER, SLIDER_PADDING, 0);

        // Third GUI column
        guiPanel(new Rectangle(320, 25, 225, 140), "Panel Info");
        guiColorPicker(new Rectangle(320, 185, 196, 192), null, colorPickerValue);

		//GuiDisable();
        guiSlider(new Rectangle(355, 400, 165, 20), "TEST", textFormat("%2.2f", sliderValue[0]), sliderValue, -50, 100);
        guiSliderBar(new Rectangle(320, 430, 200, 20), null, textFormat("%i", sliderBarValue[0]), sliderBarValue, 0, 100);
        
		guiProgressBar(new Rectangle(320, 460, 200, 20), null, textFormat("%i%%", progressValue[0]*100), progressValue, 0, 1);
		guiEnable();

        // NOTE: View rectangle could be used to perform some scissor test
        let view = new Rectangle(0, 0, 0, 0);
		guiScrollPanel(new Rectangle(560, 25, 102, 354), null, new Rectangle(560, 25, 300, 1200), viewScroll, view);

		let mouseCell = new Vector2(0, 0);
        guiGrid(new Rectangle(560, 25 + 180 + 195, 100, 120), null, 20, 2, mouseCell);

        guiColorBarAlpha(new Rectangle(320, 490, 200, 30), null, alphaValue);

        if (showMessageBox)
        {
            drawRectangle(0, 0, getScreenWidth(), getScreenHeight(), fade(RAYWHITE, 0.8));
            let result = guiMessageBox(new Rectangle(getScreenWidth()/2 - 125, getScreenHeight()/2 - 50, 250, 100), guiIconText(ICON_EXIT, "Close Window"), "Do you really want to exit?", "Yes;No");

            if ((result == 0) || (result == 2)) showMessageBox = false;
            else if (result == 1) exitWindow = true;
        }

        if (showTextInputBox)
        {
            drawRectangle(0, 0, getScreenWidth(), getScreenHeight(), fade(RAYWHITE, 0.8));
            let result = guiTextInputBox(new Rectangle(getScreenWidth()/2 - 120, getScreenHeight()/2 - 60, 240, 140), "Save", guiIconText(ICON_FILE_SAVE, "Save file as..."), "Ok;Cancel", textInput, 255, null);

            if (result == 1)
            {
                // TODO: Validate textInput value and save
				
                textInputFileName = textInput
            }

            if ((result == 0) || (result == 1) || (result == 2))
            {
                showTextInputBox = false;
                textInput = ""
            }
        }
        //----------------------------------------------------------------------------------

    endDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
closeWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------

