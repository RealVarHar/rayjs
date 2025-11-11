/*******************************************************************************************
*
*   raygui - custom sliders
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

import {
    BACKGROUND_COLOR, BASE_COLOR_DISABLED, BASE_COLOR_NORMAL,
    BASE_COLOR_PRESSED, BORDER, BORDER_WIDTH,
    DEFAULT, GuiDrawRectangle, GuiDrawText, GuiGetAlpha, GuiGetState, GuiGetStyle,
    GuiGetTextWidth,
    GuiGroupBox, GuiIsLocked,
    GuiLock, GuiSlider, GuiUnlock, SLIDER, SLIDER_PADDING, SLIDER_WIDTH, STATE_DISABLED, STATE_FOCUSED,
    STATE_NORMAL, STATE_PRESSED, TEXT, TEXT_ALIGN_LEFT, TEXT_ALIGN_RIGHT, TEXT_COLOR_FOCUSED, TEXT_PADDING, TEXT_SIZE
} from 'rayjs:raygui';
import {BLANK, BeginDrawing, CheckCollisionPointRec,
    ClearBackground, CloseWindow, EndDrawing, Fade, GetColor, GetMousePosition, InitWindow, IsMouseButtonDown,
    IsMouseButtonPressed, IsMouseButtonReleased, MOUSE_LEFT_BUTTON, Rectangle, SetTargetFPS,
    TextFormat, WindowShouldClose } from 'rayjs:raylib';

let guiAlpha=GuiGetAlpha();

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
function GuiVerticalSliderPro(bounds, textTop, textBottom, value, minValue, maxValue, sliderHeight) {
    let state = GuiGetState();

    let sliderValue = Math.floor(((value - minValue)/(maxValue - minValue)) * (bounds.height - 2 * GuiGetStyle(SLIDER, BORDER_WIDTH)));

    let slider = new Rectangle(
        bounds.x + GuiGetStyle(SLIDER, BORDER_WIDTH) + GuiGetStyle(SLIDER, SLIDER_PADDING),
        bounds.y + bounds.height - sliderValue,
        bounds.width - 2*GuiGetStyle(SLIDER, BORDER_WIDTH) - 2*GuiGetStyle(SLIDER, SLIDER_PADDING),
        0
    );

    if (sliderHeight > 0)        // Slider
    {
        slider.y -= sliderHeight/2;
        slider.height = sliderHeight;
    }
    else if (sliderHeight == 0)  // SliderBar
    {
        slider.y -= GuiGetStyle(SLIDER, BORDER_WIDTH);
        slider.height = sliderValue;
    }
    let guiLocked=GuiIsLocked();
    // Update control
    //--------------------------------------------------------------------
    if ((state != STATE_DISABLED) && !guiLocked) {
        let mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, bounds)) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                state = STATE_PRESSED;

                // Get equivalent value and slider position from mousePoint.x
                let normalizedValue = (bounds.y + bounds.height - mousePoint.y - (sliderHeight / 2)) / (bounds.height - sliderHeight);
                value = (maxValue - minValue) * normalizedValue + minValue;

                if (sliderHeight > 0) {
                    slider.y = mousePoint.y - slider.height / 2; // Slider
                } else if (sliderHeight == 0) {
                    slider.y = mousePoint.y;// SliderBar
                    slider.height = bounds.y + bounds.height - slider.y - GuiGetStyle(SLIDER, BORDER_WIDTH);
                }
            } else {
                state = STATE_FOCUSED;
            }
        }

        if (value > maxValue) value = maxValue;
        else if (value < minValue) value = minValue;
    }


    // Bar limits check
    if (sliderHeight > 0) {       // Slider
        if (slider.y < (bounds.y + GuiGetStyle(SLIDER, BORDER_WIDTH))) slider.y = bounds.y + GuiGetStyle(SLIDER, BORDER_WIDTH);
        else if ((slider.y + slider.height) >= (bounds.y + bounds.height)) slider.y = bounds.y + bounds.height - slider.height - GuiGetStyle(SLIDER, BORDER_WIDTH);
    }
    else if (sliderHeight == 0) { // SliderBar
        if (slider.y < (bounds.y + GuiGetStyle(SLIDER, BORDER_WIDTH))) {
            slider.y = bounds.y + GuiGetStyle(SLIDER, BORDER_WIDTH);
            slider.height = bounds.height - 2*GuiGetStyle(SLIDER, BORDER_WIDTH);
        }
    }

    //--------------------------------------------------------------------
    // Draw control
    //--------------------------------------------------------------------
    GuiDrawRectangle(bounds, GuiGetStyle(SLIDER, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(SLIDER, BORDER + (state*3))), guiAlpha), Fade(GetColor(GuiGetStyle(SLIDER, (state != STATE_DISABLED)?  BASE_COLOR_NORMAL : BASE_COLOR_DISABLED)), guiAlpha));

    // Draw slider internal bar (depends on state)
    if ((state == STATE_NORMAL) || (state == STATE_PRESSED)) GuiDrawRectangle(slider, 0, BLANK, Fade(GetColor(GuiGetStyle(SLIDER, BASE_COLOR_PRESSED)), guiAlpha));
    else if (state == STATE_FOCUSED) GuiDrawRectangle(slider, 0, BLANK, Fade(GetColor(GuiGetStyle(SLIDER, TEXT_COLOR_FOCUSED)), guiAlpha));

    // Draw top/bottom text if provided
    if (textTop != null) {
        let textBounds = new Rectangle();
        textBounds.width = GuiGetTextWidth(textTop);
        textBounds.height = GuiGetStyle(DEFAULT, TEXT_SIZE);
        textBounds.x = bounds.x + bounds.width/2 - textBounds.width/2;
        textBounds.y = bounds.y - textBounds.height - GuiGetStyle(SLIDER, TEXT_PADDING);

        GuiDrawText(textTop, textBounds, TEXT_ALIGN_RIGHT, Fade(GetColor(GuiGetStyle(SLIDER, TEXT + (state*3))), guiAlpha));
    }

    if (textBottom != null) {
        let textBounds = new Rectangle();
        textBounds.width = GuiGetTextWidth(textBottom);
        textBounds.height = GuiGetStyle(DEFAULT, TEXT_SIZE);
        textBounds.x = bounds.x + bounds.width/2 - textBounds.width/2;
        textBounds.y = bounds.y + bounds.height + GuiGetStyle(SLIDER, TEXT_PADDING);

        GuiDrawText(textBottom, textBounds, TEXT_ALIGN_LEFT, Fade(GetColor(GuiGetStyle(SLIDER, TEXT + (state*3))), guiAlpha));
    }
    //--------------------------------------------------------------------

    return value;
}

function GuiVerticalSlider(bounds, textTop, textBottom, value, minValue, maxValue) {
    return GuiVerticalSliderPro(bounds, textTop, textBottom, value, minValue, maxValue, GuiGetStyle(SLIDER, SLIDER_WIDTH));
}

function GuiVerticalSliderBar(bounds, textTop, textBottom, value, minValue, maxValue) {
    return GuiVerticalSliderPro(bounds, textTop, textBottom, value, minValue, maxValue, 0);
}

function GuiSliderProOwning(bounds, textLeft, textRight, value, minValue, maxValue, sliderWidth, editMode) {
    let state = GuiGetState();

    let tempValue = value[0];
    let pressed = false;

    let sliderValue = Math.floor(((tempValue - minValue)/(maxValue - minValue))*(bounds.width - 2*GuiGetStyle(SLIDER, BORDER_WIDTH)));

    let slider = new Rectangle(
        bounds.x,
        bounds.y + GuiGetStyle(SLIDER, BORDER_WIDTH) + GuiGetStyle(SLIDER, SLIDER_PADDING),
        0,
        bounds.height - 2*GuiGetStyle(SLIDER, BORDER_WIDTH) - 2*GuiGetStyle(SLIDER, SLIDER_PADDING)
    );

    if (sliderWidth > 0) {       // Slider
        slider.x += (sliderValue - sliderWidth/2);
        slider.width = sliderWidth;
    } else if (sliderWidth == 0) { // SliderBar
        slider.x += GuiGetStyle(SLIDER, BORDER_WIDTH);
        slider.width = sliderValue;
    }
    let guiLocked=GuiIsLocked();

    // Update control
    //--------------------------------------------------------------------
    if ((state != STATE_DISABLED) && (editMode || !guiLocked)) {
        let mousePoint = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousePoint, bounds)) {
                pressed = true;
            }
        } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && editMode) {
            pressed = true;
        }
        if (editMode) {
            state = STATE_PRESSED;
            tempValue = ((maxValue - minValue)*(mousePoint.x - (bounds.x + sliderWidth/2)))/(bounds.width - sliderWidth) + minValue;

            if (sliderWidth > 0) slider.x = mousePoint.x - slider.width/2;  // Slider
            else if (sliderWidth == 0) slider.width = sliderValue;          // SliderBar

        } else if (CheckCollisionPointRec(mousePoint, bounds)) {
            state = STATE_FOCUSED;
        }

        if (tempValue > maxValue) {
            tempValue = maxValue;
        }
        else if (tempValue < minValue) {
            tempValue = minValue;
        }
    }


    // Bar limits check
    if (sliderWidth > 0) {       // Slider
        if (slider.x <= (bounds.x + GuiGetStyle(SLIDER, BORDER_WIDTH))) {
            slider.x = bounds.x + GuiGetStyle(SLIDER, BORDER_WIDTH);
        } else if ((slider.x + slider.width) >= (bounds.x + bounds.width)) {
            slider.x = bounds.x + bounds.width - slider.width - GuiGetStyle(SLIDER, BORDER_WIDTH);
        }
    } else if (sliderWidth == 0) { // SliderBar
        if (slider.width > bounds.width) {
            slider.width = bounds.width - 2*GuiGetStyle(SLIDER, BORDER_WIDTH);
        }
    }

    //--------------------------------------------------------------------
    // Draw control
    //--------------------------------------------------------------------
    GuiDrawRectangle(bounds, GuiGetStyle(SLIDER, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(SLIDER, BORDER + (state*3))), guiAlpha), Fade(GetColor(GuiGetStyle(SLIDER, (state != STATE_DISABLED)?  BASE_COLOR_NORMAL : BASE_COLOR_DISABLED)), guiAlpha));

    // Draw slider internal bar (depends on state)
    if ((state == STATE_NORMAL) || (state == STATE_PRESSED)) {
        GuiDrawRectangle(slider, 0, BLANK, Fade(GetColor(GuiGetStyle(SLIDER, BASE_COLOR_PRESSED)), guiAlpha));
    }else if (state == STATE_FOCUSED) {
        GuiDrawRectangle(slider, 0, BLANK, Fade(GetColor(GuiGetStyle(SLIDER, TEXT_COLOR_FOCUSED)), guiAlpha));
    }

    // Draw left/right text if provided
    if (textLeft != null) {
        let textBounds = new Rectangle();
        textBounds.width = GuiGetTextWidth(textLeft);
        textBounds.height = GuiGetStyle(DEFAULT, TEXT_SIZE);
        textBounds.x = bounds.x - textBounds.width - GuiGetStyle(SLIDER, TEXT_PADDING);
        textBounds.y = bounds.y + bounds.height/2 - GuiGetStyle(DEFAULT, TEXT_SIZE)/2;

        GuiDrawText(textLeft, textBounds, TEXT_ALIGN_RIGHT, Fade(GetColor(GuiGetStyle(SLIDER, TEXT + (state*3))), guiAlpha));
    }

    if (textRight != null) {
        let textBounds = new Rectangle();
        textBounds.width = GuiGetTextWidth(textRight);
        textBounds.height = GuiGetStyle(DEFAULT, TEXT_SIZE);
        textBounds.x = bounds.x + bounds.width + GuiGetStyle(SLIDER, TEXT_PADDING);
        textBounds.y = bounds.y + bounds.height/2 - GuiGetStyle(DEFAULT, TEXT_SIZE)/2;

        GuiDrawText(textRight, textBounds, TEXT_ALIGN_LEFT, Fade(GetColor(GuiGetStyle(SLIDER, TEXT + (state*3))), guiAlpha));
    }
    //--------------------------------------------------------------------

    value[0] = tempValue;
    return pressed;
}

function GuiSliderOwning(bounds, textLeft, textRight, value, minValue, maxValue, editMode) {
    return GuiSliderProOwning(bounds, textLeft, textRight, value, minValue, maxValue, GuiGetStyle(SLIDER, SLIDER_WIDTH), editMode);
}

function GuiSliderBarOwning(bounds, textLeft, textRight, value, minValue, maxValue, editMode) {
    return GuiSliderProOwning(bounds, textLeft, textRight, value, minValue, maxValue, 0, editMode);
}

function GuiVerticalSliderProOwning(bounds, textTop, textBottom, value, minValue, maxValue, sliderHeight, editMode) {
    let state = GuiGetState();

    let tempValue = value[0];
    let pressed = false;

    let sliderValue = Math.floor(((tempValue - minValue)/(maxValue - minValue)) * (bounds.height - 2 * GuiGetStyle(SLIDER, BORDER_WIDTH)));

    let slider = new Rectangle(
        bounds.x + GuiGetStyle(SLIDER, BORDER_WIDTH) + GuiGetStyle(SLIDER, SLIDER_PADDING),
        bounds.y + bounds.height - sliderValue,
        bounds.width - 2*GuiGetStyle(SLIDER, BORDER_WIDTH) - 2*GuiGetStyle(SLIDER, SLIDER_PADDING),
        0
    );

    if (sliderHeight > 0) {       // Slider
        slider.y -= sliderHeight/2;
        slider.height = sliderHeight;
    } else if (sliderHeight == 0) { // SliderBar
        slider.y -= GuiGetStyle(SLIDER, BORDER_WIDTH);
        slider.height = sliderValue;
    }
    let guiLocked=GuiIsLocked();
    // Update control
    //--------------------------------------------------------------------
    if ((state != STATE_DISABLED) && (editMode || !guiLocked)) {
        let mousePoint = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousePoint, bounds)) {
                pressed = true;
            }
        } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && editMode) {
            pressed = true;
        }
        if (editMode) {
            state = STATE_PRESSED;

            let normalizedValue = (bounds.y + bounds.height - mousePoint.y - (sliderHeight/2)) / (bounds.height - sliderHeight);
            tempValue = (maxValue - minValue) * normalizedValue + minValue;

            if (sliderHeight > 0) {  // Slider
                slider.y = mousePoint.y - slider.height / 2;
            } else if (sliderHeight == 0) {  // SliderBar
                slider.y = mousePoint.y;
                slider.height = bounds.y + bounds.height - slider.y - GuiGetStyle(SLIDER, BORDER_WIDTH);
            }
        } else if (CheckCollisionPointRec(mousePoint, bounds)) {
            state = STATE_FOCUSED;
        }

        if (tempValue > maxValue) {
            tempValue = maxValue;
        } else if (tempValue < minValue) {
            tempValue = minValue;
        }
    }


    // Bar limits check
    if (sliderHeight > 0) {  // Slider
        if (slider.y < (bounds.y + GuiGetStyle(SLIDER, BORDER_WIDTH))) slider.y = bounds.y + GuiGetStyle(SLIDER, BORDER_WIDTH);
        else if ((slider.y + slider.height) >= (bounds.y + bounds.height)) slider.y = bounds.y + bounds.height - slider.height - GuiGetStyle(SLIDER, BORDER_WIDTH);
    } else if (sliderHeight == 0) { // SliderBar
        if (slider.y < (bounds.y + GuiGetStyle(SLIDER, BORDER_WIDTH))) {
            slider.y = bounds.y + GuiGetStyle(SLIDER, BORDER_WIDTH);
            slider.height = bounds.height - 2*GuiGetStyle(SLIDER, BORDER_WIDTH);
        }
    }

    //--------------------------------------------------------------------
    // Draw control
    //--------------------------------------------------------------------
    GuiDrawRectangle(bounds, GuiGetStyle(SLIDER, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(SLIDER, BORDER + (state*3))), guiAlpha), Fade(GetColor(GuiGetStyle(SLIDER, (state != STATE_DISABLED)?  BASE_COLOR_NORMAL : BASE_COLOR_DISABLED)), guiAlpha));

    // Draw slider internal bar (depends on state)
    if ((state == STATE_NORMAL) || (state == STATE_PRESSED))
        GuiDrawRectangle(slider, 0, BLANK, Fade(GetColor(GuiGetStyle(SLIDER, BASE_COLOR_PRESSED)), guiAlpha));
    else if (state == STATE_FOCUSED)
        GuiDrawRectangle(slider, 0, BLANK, Fade(GetColor(GuiGetStyle(SLIDER, TEXT_COLOR_FOCUSED)), guiAlpha));

    // Draw top/bottom text if provided
    if (textTop != null) {
        let textBounds = new Rectangle();
        textBounds.width = GuiGetTextWidth(textTop);
        textBounds.height = GuiGetStyle(DEFAULT, TEXT_SIZE);
        textBounds.x = bounds.x + bounds.width/2 - textBounds.width/2;
        textBounds.y = bounds.y - textBounds.height - GuiGetStyle(SLIDER, TEXT_PADDING);

        GuiDrawText(textTop, textBounds, TEXT_ALIGN_RIGHT, Fade(GetColor(GuiGetStyle(SLIDER, TEXT + (state*3))), guiAlpha));
    }

    if (textBottom != null) {
        let textBounds = new Rectangle();
        textBounds.width = GuiGetTextWidth(textBottom);
        textBounds.height = GuiGetStyle(DEFAULT, TEXT_SIZE);
        textBounds.x = bounds.x + bounds.width/2 - textBounds.width/2;
        textBounds.y = bounds.y + bounds.height + GuiGetStyle(SLIDER, TEXT_PADDING);

        GuiDrawText(textBottom, textBounds, TEXT_ALIGN_LEFT, Fade(GetColor(GuiGetStyle(SLIDER, TEXT + (state*3))), guiAlpha));
    }
    //--------------------------------------------------------------------
    value[0] = tempValue;
    return pressed;
}

function GuiVerticalSliderOwning(bounds, textTop, textBottom, value, minValue, maxValue, editMode) {
    return GuiVerticalSliderProOwning(bounds, textTop, textBottom, value, minValue, maxValue, GuiGetStyle(SLIDER, SLIDER_WIDTH), editMode);
}

function GuiVerticalSliderBarOwning(bounds, textTop, textBottom, value, minValue, maxValue, editMode) {
    return GuiVerticalSliderProOwning(bounds, textTop, textBottom, value, minValue, maxValue, 0, editMode);
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //---------------------------------------------------------------------------------------
    let screenWidth = 800;
    let screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raygui - custom sliders");

    let value = [0.5];
    let sliderEditMode = false;
    let vSliderEditMode = false;
    let vSliderBarEditMode = false;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            if (vSliderEditMode || vSliderBarEditMode) GuiLock();
            else GuiUnlock();

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            GuiGroupBox(new Rectangle( 66, 24, 276, 312 ), "STANDARD");
            GuiSlider(new Rectangle( 96, 48, 216, 16 ), TextFormat("%0.2f", value[0]), null, value, 0, 1);
            value[0] = GuiVerticalSlider(new Rectangle( 120, 120, 24, 192 ), TextFormat("%0.2f", value[0]), null, value[0], 0, 1);
            value[0] = GuiVerticalSliderBar(new Rectangle( 264, 120, 24, 192 ), TextFormat("%0.2f", value[0]), null, value[0], 0, 1);

            GuiGroupBox(new Rectangle( 378, 24, 276, 312 ), "OWNING");
            if (GuiSliderOwning(new Rectangle( 408, 48, 216, 16 ), null, TextFormat("%0.2f", value[0]), value, 0, 1, sliderEditMode)) sliderEditMode = !sliderEditMode;
            if (GuiVerticalSliderOwning(new Rectangle( 432, 120, 24, 192 ), null, TextFormat("%0.2f", value[0]), value, 0, 1, vSliderEditMode)) vSliderEditMode = !vSliderEditMode;
            if (GuiVerticalSliderBarOwning(new Rectangle( 576, 120, 24, 192 ), null, TextFormat("%0.2f", value[0]), value, 0, 1, vSliderBarEditMode)) vSliderBarEditMode = !vSliderBarEditMode;
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}