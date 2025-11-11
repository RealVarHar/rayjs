/*******************************************************************************************
*
*   raygui - basic calculator app with custom input box for float values
*
*   DEPENDENCIES:
*       raylib 4.5  - Windowing/input management and drawing.
*       raygui 3.5  - Immediate-mode GUI controls.
*
*   COMPILATION (Windows - MinGW):
*       gcc -o $(NAME_PART).exe $(FILE_NAME) -I../../src -lraylib -lopengl32 -lgdi32 -std=c99
*
**********************************************************************************************/

import {
    BASE_COLOR_DISABLED,
    BASE_COLOR_PRESSED,
    BORDER_COLOR_PRESSED,
    BORDER_WIDTH,
    DEFAULT,
    GuiButton,
    GuiGetStyle,
    GuiGetTextWidth,
    LABEL,
    STATE_DISABLED,
    STATE_FOCUSED,
    STATE_PRESSED,
    TEXT_ALIGNMENT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_RIGHT,
    TEXT_PADDING,
    TEXT_SIZE,
    VALUEBOX,
    STATE_NORMAL,
    GuiIsLocked,
    GuiIsExclusive,
    GuiDrawRectangle,
    GuiDrawText,
    GetTextBounds,
    BORDER, GuiGetAlpha, TEXT
} from 'rayjs:raygui';
import {BLANK,
    BeginDrawing, CheckCollisionPointRec,
    ClearBackground, CloseWindow, DARKGRAY, DrawText,
    EndDrawing, Fade, GetCharPressed, GetColor, GetMousePosition, InitWindow, IsKeyPressed,
    IsMouseButtonPressed, KEY_BACKSPACE, KEY_COMMA, KEY_ENTER, KEY_MINUS,
    KEY_PERIOD, MOUSE_LEFT_BUTTON, RAYWHITE, Rectangle, SetTargetFPS, TextFormat, WindowShouldClose } from 'rayjs:raylib';

let guiFloatingPointIndex = 0;      // Global variable shared by all GuiFloatBox()


// Float Box control, updates input text with numbers
function GuiFloatBox(bounds, text, value, minValue, maxValue, editMode) {
    const RAYGUI_VALUEBOX_MAX_CHARS = 32;

    let result = 0;
    let state = STATE_NORMAL;

    let textValue = "";

    let textBounds = new Rectangle();
    if (text != null) {
        textBounds.width = GuiGetTextWidth(text) + 2;
        textBounds.height = GuiGetStyle(DEFAULT, TEXT_SIZE);
        textBounds.x = bounds.x + bounds.width + GuiGetStyle(VALUEBOX, TEXT_PADDING);
        textBounds.y = bounds.y + bounds.height / 2 - GuiGetStyle(DEFAULT, TEXT_SIZE) / 2;
        if (GuiGetStyle(VALUEBOX, TEXT_ALIGNMENT) == TEXT_ALIGN_LEFT) textBounds.x = bounds.x - textBounds.width - GuiGetStyle(VALUEBOX, TEXT_PADDING);
    }
    let guiLocked=GuiIsLocked();
    let guiControlExclusiveMode = GuiIsExclusive();
    let guiAlpha = GuiGetAlpha();

    // Update control
    //--------------------------------------------------------------------
    if ((state != STATE_DISABLED) && !guiLocked && !guiControlExclusiveMode) {
        let mousePoint = GetMousePosition();

        if (value[0] >= 0) {
            textValue = TextFormat("%.3f", value[0]);
        } else {
            textValue = TextFormat("-%.3f", value[0]);
        }

        let valueHasChanged = false;

        let keyCount = Math.floor(textValue.length - guiFloatingPointIndex);

        if (editMode) {
            state = STATE_PRESSED;

            // Only allow keys in range [48..57]
            if (keyCount < RAYGUI_VALUEBOX_MAX_CHARS) {
                if (GuiGetTextWidth(textValue) < bounds.width) {
                    let key = GetCharPressed();
                    if ((key >= 48) && (key <= 57) && guiFloatingPointIndex) {
                        console.log(key,guiFloatingPointIndex,textValue);
                        if (guiFloatingPointIndex && guiFloatingPointIndex != 4) guiFloatingPointIndex--;

                        textValue = textValue.substring(0,keyCount)+String.fromCharCode(key);
                        keyCount++;
                        valueHasChanged = true;
                    }
                }
            }

            // Delete text
            if (keyCount > 0) {
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (guiFloatingPointIndex < 5) guiFloatingPointIndex++;
                    textValue = textValue.substring(0,keyCount-1);
                    keyCount--;
                    valueHasChanged = true;
                }
            }

            // Change sign
            if (IsKeyPressed(KEY_MINUS)) {
                if (textValue[0] == '+') {
                    textValue = '-'+textValue.substring(1);
                } else if (textValue[0] == '-') {
                    textValue = '+'+textValue.substring(1);
                }
                valueHasChanged = true;
            }

            // Add decimal separator
            if ((IsKeyPressed(KEY_COMMA) || IsKeyPressed(KEY_PERIOD)) && guiFloatingPointIndex == 4) {
                guiFloatingPointIndex--;
                valueHasChanged = true;
            }

            if (valueHasChanged) {
                value[0] = Number(textValue);
            }

            if (IsKeyPressed(KEY_ENTER) || (!CheckCollisionPointRec(mousePoint, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
                guiFloatingPointIndex = 0;
                result = 1;
            }
        } else {
            if (value[0] > maxValue){
                value[0] = maxValue;
            } else if (value[0] < minValue){
                value[0] = minValue;
            }

            if (CheckCollisionPointRec(mousePoint, bounds)) {
                state = STATE_FOCUSED;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) result = 1;
            }
        }
    }
    //--------------------------------------------------------------------

    // Draw control
    //--------------------------------------------------------------------
    let baseColor = BLANK;
    textValue = TextFormat("%.3f", value[0]);

    if (state == STATE_PRESSED) {
        baseColor = GetColor(GuiGetStyle(VALUEBOX, BASE_COLOR_PRESSED));
        textValue = textValue.substring(0,textValue.length - guiFloatingPointIndex);
    } else if (state == STATE_DISABLED) {
        baseColor = GetColor(GuiGetStyle(VALUEBOX, BASE_COLOR_DISABLED));
    }
    //NOTE: BORDER, BASE, TEXT, OTHER are a random enum from raygui.h that was not exposed by rayjs yet

    // WARNING: BLANK color does not work properly with Fade()
    GuiDrawRectangle(bounds, GuiGetStyle(VALUEBOX, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(VALUEBOX, BORDER + (state * 3))), guiAlpha), baseColor);
    GuiDrawText(textValue, GetTextBounds(VALUEBOX, bounds), TEXT_ALIGN_CENTER, Fade(GetColor(GuiGetStyle(VALUEBOX, TEXT + (state * 3))), guiAlpha));

    // Draw cursor
    if (editMode) {
        // NOTE: ValueBox internal text is always centered
        let cursor = new Rectangle( bounds.x + GuiGetTextWidth(textValue) / 2 + bounds.width / 2 + 1, bounds.y + 2 * GuiGetStyle(VALUEBOX, BORDER_WIDTH), 4, bounds.height - 4 * GuiGetStyle(VALUEBOX, BORDER_WIDTH) );
        GuiDrawRectangle(cursor, 0, BLANK, Fade(GetColor(GuiGetStyle(VALUEBOX, BORDER_COLOR_PRESSED)), guiAlpha));
    }

    // Draw text label if provided
    GuiDrawText(text, textBounds, (GuiGetStyle(VALUEBOX, TEXT_ALIGNMENT) == TEXT_ALIGN_RIGHT) ? TEXT_ALIGN_LEFT : TEXT_ALIGN_RIGHT, Fade(GetColor(GuiGetStyle(LABEL, TEXT + (state * 3))), guiAlpha));
    //--------------------------------------------------------------------

    return result;
}


{
	InitWindow(250, 100, "Basic calculator");

	// General variables
	SetTargetFPS(60);

	let variableA = [0];
	let variableB = [0];
	let result = 0;
    let operation = "+";

	let variableAMode = false;
	let variableBMode = false;
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose()) {
		// Draw 
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if (GuiFloatBox(new Rectangle( 10, 10, 100, 20 ), null, variableA, -1000000.0, 1000000.0, variableAMode)) variableAMode = !variableAMode;
		if (GuiFloatBox(new Rectangle( 140, 10, 100, 20 ), null, variableB, -1000000.0, 1000000.0, variableBMode)) variableBMode = !variableBMode;
		
		if (GuiButton(new Rectangle( 10, 70, 50, 20 ), "+")) {
			result = variableA[0] + variableB[0];
			operation = '+';
		}
		if (GuiButton(new Rectangle( 70, 70, 50, 20 ), "-")) {
			result = variableA[0] - variableB[0];
			operation = '-';
		}
		if (GuiButton(new Rectangle( 130, 70, 50, 20 ), "*")) {
			result = variableA[0] * variableB[0];
			operation = '*';
		}
		if (GuiButton(new Rectangle( 190, 70, 50, 20 ), "/")) {
			result = variableA[0] / variableB[0];
			operation = '/';
		}

		DrawText(operation, 123, 15, 10, DARKGRAY);

        let aresult=[result];
		GuiFloatBox(new Rectangle( 55, 40, 135, 20 ), "= ", aresult, -2000000.0, 2000000.0, false);
        result=aresult[0];
		
		EndDrawing();
        //----------------------------------------------------------------------------------
	}

	CloseWindow();
}