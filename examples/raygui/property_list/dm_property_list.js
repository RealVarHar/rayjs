/*******************************************************************************************
*
*   PropertyListControl v1.0.1 - A custom control that displays a set of properties as a list
*
*   UPDATES: last updated - 10 march 2020 (v1.0.1)
*       v1.0.1 - Made it work with latest raygui version
*              - Added `GuiDMSaveProperties()` for saving properties to a text file
*              - A `GuiDMLoadProperties()` is planed but not implemented yet
*              - Added a section property that can work as a way to group multiple properties
*              - Fixed issue with section not having the correct height
*       v1.0.0 - Initial release
*
*
*   MODULE USAGE:
*       #define GUI_PROPERTY_LIST_IMPLEMENTATION
*       #include "dm_property_list.h"
*
*       INIT: GuiDMProperty props[] = { // initialize a set of properties first
                   PCOLOR(),
                   PINT(),
                   PFLOAT(),
                   ...
              };
*       DRAW: GuiDMPropertyList(bounds, props, sizeof(props)/sizeof(props[0]), ...);
*   
*       
*   NOTE: This module also contains 2 extra controls used internally by the property list
*       - GuiDMValueBox() - a value box that supports displaying float values
*       - GuiDMSpinner() - a `better` GuiSpinner()
*       
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2020 Vlad Adrian (@Demizdor - https://github.com/Demizdor).
*
**********************************************************************************************/

import std from "qjs:std";
import {ARROWS_VISIBLE, BACKGROUND_COLOR, BASE_COLOR_DISABLED, BASE_COLOR_PRESSED,
    BORDER_COLOR_DISABLED,
    BORDER_COLOR_PRESSED, BORDER_WIDTH, BUTTON, DEFAULT, GuiButton, GuiCheckBox, GuiGetState, GuiGetStyle,
    GuiIconText,
    GuiLock,
    GuiSetState,
    GuiSetStyle,
    GuiUnlock,
    LISTVIEW,
    LIST_ITEMS_HEIGHT,
    LIST_ITEMS_SPACING,
    SCROLLBAR,
    SCROLLBAR_LEFT_SIDE,
    SCROLLBAR_SIDE,
    SCROLLBAR_WIDTH,
    SCROLL_PADDING,
    SCROLL_SLIDER_PADDING,
    SCROLL_SLIDER_SIZE,
    SPINNER_BUTTON_SPACING,
    SPINNER_BUTTON_WIDTH, STATE_DISABLED, STATE_FOCUSED, STATE_NORMAL, STATE_PRESSED,
    TEXT_ALIGNMENT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_LEFT, TEXT_COLOR_DISABLED, TEXT_COLOR_FOCUSED, TEXT_COLOR_NORMAL, TEXT_COLOR_PRESSED, VALUEBOX } from "rayjs:raygui";
import {BeginScissorMode, CheckCollisionPointRec, Color,
    ColorToInt,
    DrawLineEx,
    DrawRectangle,
    DrawRectangleLinesEx, DrawRectangleRec,
    EndScissorMode, Fade, GetClipboardText, GetColor, GetKeyPressed, GetMousePosition,
    GetMouseWheelMove, IsKeyDown, IsKeyPressed,
    IsMouseButtonDown,
    IsMouseButtonPressed,
    KEY_BACKSPACE, KEY_C, KEY_DELETE, KEY_END, KEY_HOME, KEY_LEFT,
    KEY_LEFT_CONTROL, KEY_RIGHT, KEY_V, KEY_X,
    MOUSE_LEFT_BUTTON, Rectangle, SetClipboardText, TextFormat, Vector2, Vector3, Vector4 } from "rayjs:raylib";

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
const GUI_PROP_BOOL = 0;
const GUI_PROP_INT = 1;
const GUI_PROP_FLOAT = 2;
const GUI_PROP_TEXT = 3;
const GUI_PROP_SELECT = 4;
const GUI_PROP_VECTOR2 = 5;
const GUI_PROP_VECTOR3 = 6;
const GUI_PROP_VECTOR4 = 7;
const GUI_PROP_RECT = 8;
const GUI_PROP_COLOR = 9;
const GUI_PROP_SECTION = 10;


//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------

// A bunch of usefull macros for modifying the flags of each property 

// Set flag `F` of property `P`.
function PROP_SET_FLAG(P, F) { P.flags |= F;}
// Clear flag `F` of property `P`.
function PROP_CLEAR_FLAG(P, F) { P.flags &= ~F;}
// Toggles flag `F` of property `P`.
function PROP_TOGGLE_FLAG(P, F) { P.flags ^= F;};
// Checks if flag `F` of property `P` is set .
function PROP_CHECK_FLAG(P, F) {return P.flags & F;}


const GUI_PFLAG_COLLAPSED = 1 << 0; // is the property expanded or collapsed?
const GUI_PFLAG_DISABLED = 1 << 1; // is this property disabled or enabled?

// Some usefull macros for creating properties

// Create a bool property with name `N`, flags `F` and value `V`
export function PBOOL(name, flags, V) {return {name, type:GUI_PROP_BOOL, flags, vbool: V};};
// Create a int property with name `N`, flags `F` and value `V`
export function PINT(name, flags, V) {return {name, type:GUI_PROP_BOOL, flags, vint: {val:V,min:0,max:0,step:1}};}
// Create a ranged int property within `MIN` and `MAX` with name `N`, flags `F` value `V`. 
// Pressing the spinner buttons will increase/decrease the value by `S`.
export function PINT_RANGE(name, flags, V, S, min, max) {return {name, type:GUI_PROP_BOOL, flags, vint: {val:V,min,max,step:S}};}
// Create a float property with name `N`, flags `F` and value `V`
export function PFLOAT(name, flags, V) {return {name, type:GUI_PROP_FLOAT, flags, vfloat: {val:V,min:0,max:0,step:1,precision:3}};};
// Create a ranged float property within `MIN` and `MAX` with name `N`, flags `F` value `V` with `P` decimal digits to show. 
// Pressing the spinner buttons will increase/decrease the value by `S`.
export function PFLOAT_RANGE(name, flags, V, S, P, min, max) {return {name, type:GUI_PROP_FLOAT, flags, vfloat: {val:V,min,max,step:S,precision:P}};}
// Create a text property with name `N`, flags `F` value `V` and max text size `S`
export function PTEXT(name, flags, val, size) {return {name, type:GUI_PROP_TEXT, flags, vtext: {val, size} };}
// Create a text property with name `N`, flags `F` value `V` and max text size `S`
export function PSELECT(name, flags, val, active) {return {name, type:GUI_PROP_SELECT, flags, vselect: {val, active} };}
// Create a 2D vector property with name `N`, flags `F` and the `X`, `Y` coordinates
export function PVEC2(name, flags, X, Y) {return {name, type:GUI_PROP_VECTOR2, flags, v2: new Vector2(X, Y) };}
// Create a 3D vector property with name `N`, flags `F` and the `X`, `Y`, `Z` coordinates
export function PVEC3(name, flags, X, Y, Z) {return {name, type:GUI_PROP_VECTOR3, flags, v3: new Vector3(X, Y, Z) };}
// Create a 4D vector property with name `N`, flags `F` and the `X`, `Y`, `Z`, `W` coordinates
export function PVEC4(name, flags, X, Y, Z, W) {return {name, type:GUI_PROP_VECTOR4, flags, v4: new Vector4(X, Y, Z, W) };}
// Create a rectangle property with name `N`, flags `F`, `X`, `Y` coordinates and `W` and `H` size
export function PRECT(name, flags, X, Y, W, H) {return {name, type:GUI_PROP_RECT, flags, vrect: new Rectangle(X, Y, W, H) };}
// Create a 3D vector property with name `N`, flags `F` and the `R`, `G`, `B`, `A` channel values
export function PCOLOR(name, flags, R, G, B, A) {return {name, type:GUI_PROP_COLOR, flags, vcolor: new Color(R, G, B, A) };}
// Create a collapsable section named `N` with `F` flags and the next `C` properties as children.
// !! A section cannot hold another section as a child !!
export function PSECTION(name, flags, vsection) {return {name, type:GUI_PROP_SECTION, flags, vsection};}

//----------------------------------------------------------------------------------
// Module Functions IMPLEMENTATION
//----------------------------------------------------------------------------------

// A more advanced `GuiValueBox()` supporting float/int values with specified `precision`, cursor movements, cut/copy/paste and
// other keybord shortcuts. Needed by `GuiDMSpinner()` !!
// `precision` should be between 1-7 for float values and 0 for int values (maybe 15 for doubles but that was not tested)
// WARNING: The bounds should be set big enough else the text will overflow and things will break
// WARNING: Sometimes the last decimal value could differ, this is probably due to rounding
var framesCounter = 0; // Required for blinking cursor
var cursor = 0; // Required for tracking the cursor position (only for a single active valuebox)
function GuiDMValueBox(bounds, value, minValue, maxValue, precision, editMode) {
    const cursorTimer = 6, maxChars = 31, textPadding = 2;

    let state = GuiGetState();

    // Make sure value is in range
    if(maxValue != minValue){
        if(value < minValue) value = minValue;
        if(value > maxValue) value = maxValue;
    }

    let textValue = "";
    console.log(TextFormat("%.*f", precision, value));

    let valueHasChanged = false;

    // Update control
    //--------------------------------------------------------------------
    if ((state != STATE_DISABLED) && !guiLocked) {
        if (editMode) {
            // Make sure cursor position is correct
            if(cursor > textValue.length) cursor = textValue.length;
            if(cursor < 0) cursor = 0;

            state = STATE_PRESSED;
            framesCounter++;

            if(IsKeyPressed(KEY_RIGHT) || (IsKeyDown(KEY_RIGHT) && (framesCounter%cursorTimer == 0))) {
                // MOVE CURSOR TO RIGHT
                cursor++;
                framesCounter = 0;
            } else if(IsKeyPressed(KEY_LEFT) || (IsKeyDown(KEY_LEFT) && (framesCounter%cursorTimer == 0))) {
                // MOVE CURSOR TO LEFT
                cursor--;
                framesCounter = 0;
            } else if (IsKeyPressed(KEY_BACKSPACE) || (IsKeyDown(KEY_BACKSPACE) && (framesCounter%cursorTimer) == 0)) {
                // HANDLE BACKSPACE
                if(cursor > 0) {
                    if(textValue[cursor-1] != '.') {
                        if(cursor < textValue.length ){
                            textValue = textValue.substring(0,cursor-1)+textValue.substring(cursor);
                        }
                        valueHasChanged = true;
                    }
                    cursor--;
                }
                framesCounter = 0;
            } else if (IsKeyPressed(KEY_DELETE) || (IsKeyDown(KEY_DELETE) && (framesCounter%cursorTimer) == 0)) {
                // HANDLE DEL
                if(textValue.length > 0 && cursor < textValue.length && textValue[cursor] != '.') {
                    textValue = textValue.substring(0,cursor)+textValue.substring(cursor+1);
                    valueHasChanged = true;
                }
            } else if (IsKeyPressed(KEY_HOME)) {
                // MOVE CURSOR TO START
                cursor = 0;
            } else if (IsKeyPressed(KEY_END)) {
                // MOVE CURSOR TO END
                cursor = textValue.length;
            }  else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
                // COPY
                SetClipboardText(textValue);
            } else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_X)) {
                // CUT
                SetClipboardText(textValue);
                textValue = "";
                cursor = 0;
                value = 0.0; // set it to 0 and pretend the value didn't change
            } else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_V)) {
                // PASTE
                let clip = GetClipboardText();
                let clipLen = clip.length;
                clipLen = clipLen > maxChars ? maxChars : clipLen;
                textValue = clip;
                valueHasChanged = true;
            } else {
                // HANDLE KEY PRESS
                let key = GetKeyPressed();
                if( ((textValue.length < maxChars) && (key >= 48) && (key <= 57)) || (key == 46) || (key == 45)  ) { // only allow 0..9, minus(-) and dot(.)

                    if(precision != 0 && cursor < textValue.length) { // insert
                        textValue = textValue.substring(0,cursor)+textValue.substring(cursor);
                        valueHasChanged = true;
                    }
                    else if(precision == 0) {
                        //cursor can not be bigger than len
                        if(cursor < textValue.length) {
                            textValue = textValue.substring(0,cursor)+String.fromCodePoint(key)+textValue.substring(cursor+1);
                        }else{
                            textValue += String.fromCodePoint(key);
                        }
                        cursor++;
                        valueHasChanged = true;
                    }
                }
            }

            // Make sure cursor position is correct
            if(cursor > textValue.length) cursor = textValue.length;
            if(cursor < 0) cursor = 0;
        } else {
            if (CheckCollisionPointRec(GetMousePosition(), bounds)) {
                state = STATE_FOCUSED;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) framesCounter = 0;
            }
        }
    }
    //--------------------------------------------------------------------

    // Draw control
    //--------------------------------------------------------------------
    DrawRectangleLinesEx(bounds, GuiGetStyle(VALUEBOX, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(VALUEBOX, BORDER + (state*3))), guiAlpha));

    let textBounds = new Rectangle(bounds.x + GuiGetStyle(VALUEBOX, BORDER_WIDTH) + textPadding, bounds.y + GuiGetStyle(VALUEBOX, BORDER_WIDTH),
        bounds.width - 2*(GuiGetStyle(VALUEBOX, BORDER_WIDTH) + textPadding), bounds.height - 2*GuiGetStyle(VALUEBOX, BORDER_WIDTH));

    let textWidth = GetTextWidth(textValue);
    if(textWidth > textBounds.width) textBounds.width = textWidth;

    if (state == STATE_PRESSED) {
        DrawRectangle(bounds.x + GuiGetStyle(VALUEBOX, BORDER_WIDTH), bounds.y + GuiGetStyle(VALUEBOX, BORDER_WIDTH), bounds.width - 2*GuiGetStyle(VALUEBOX, BORDER_WIDTH), bounds.height - 2*GuiGetStyle(VALUEBOX, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(VALUEBOX, BASE_COLOR_PRESSED)), guiAlpha));

        // Draw blinking cursor
        // NOTE: ValueBox internal text is always centered
        if (editMode && ((framesCounter/20)%2 == 0)) {
            // Measure text until the cursor
            let textWidthCursor = -2;
            if(cursor > 0) {
                textWidthCursor = GetTextWidth(textValue.substring(0,cursor));
            }
            //DrawRectangle(bounds.x + textWidthCursor + textPadding + 2, bounds.y + 2*GuiGetStyle(VALUEBOX, BORDER_WIDTH), 1, bounds.height - 4*GuiGetStyle(VALUEBOX, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(VALUEBOX, BORDER_COLOR_PRESSED)), guiAlpha));
            DrawRectangle(bounds.x + textWidthCursor + Math.floor((bounds.width - textWidth - textPadding)/2) + 2, bounds.y + 2*GuiGetStyle(VALUEBOX, BORDER_WIDTH), 1, bounds.height - 4*GuiGetStyle(VALUEBOX, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(VALUEBOX, BORDER_COLOR_PRESSED)), guiAlpha));
        }
    } else if (state == STATE_DISABLED) {
        DrawRectangle(bounds.x + GuiGetStyle(VALUEBOX, BORDER_WIDTH), bounds.y + GuiGetStyle(VALUEBOX, BORDER_WIDTH), bounds.width - 2*GuiGetStyle(VALUEBOX, BORDER_WIDTH), bounds.height - 2*GuiGetStyle(VALUEBOX, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(VALUEBOX, BASE_COLOR_DISABLED)), guiAlpha));
    }

    GuiDrawText(textValue, textBounds, TEXT_ALIGN_CENTER, Fade(GetColor(GuiGetStyle(VALUEBOX, TEXT + (state*3))), guiAlpha));

    value = valueHasChanged ? Number(textValue) : value;

    // Make sure value is in range
    if(maxValue != minValue){
        if(value < minValue) value = minValue;
        if(value > maxValue) value = maxValue;
    }

    return value;
}

// A more advanced `GuiSpinner()` using `GuiDMValueBox()` for displaying the values.
// This was needed because `GuiSpinner()` can't display float values and editing values is somewhat hard. 
// This is by no means perfect but should be more user friendly than the default control provided by raygui.
function GuiDMSpinner(bounds, value, minValue, maxValue, step, precision, editMode) {
    let state = GuiGetState();

    let spinner = new Rectangle( bounds.x + GuiGetStyle(VALUEBOX, SPINNER_BUTTON_WIDTH) + GuiGetStyle(VALUEBOX, SPINNER_BUTTON_SPACING), bounds.y,
        bounds.width - 2*(GuiGetStyle(VALUEBOX, SPINNER_BUTTON_WIDTH) + GuiGetStyle(VALUEBOX, SPINNER_BUTTON_SPACING)), bounds.height );
    let leftButtonBound = new Rectangle( bounds.x, bounds.y, GuiGetStyle(VALUEBOX, SPINNER_BUTTON_WIDTH), bounds.height );
    let rightButtonBound = new Rectangle( bounds.x + bounds.width - GuiGetStyle(VALUEBOX, SPINNER_BUTTON_WIDTH),
        bounds.y, GuiGetStyle(VALUEBOX, SPINNER_BUTTON_WIDTH), bounds.height );

    // Update control
    //--------------------------------------------------------------------
    if ((state != STATE_DISABLED) && !guiLocked) {
        let mousePoint = GetMousePosition();

        // Check spinner state
        if (CheckCollisionPointRec(mousePoint, bounds)) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) state = STATE_PRESSED;
            else state = STATE_FOCUSED;
        }
    }
    //--------------------------------------------------------------------


    // Draw control
    //--------------------------------------------------------------------
    // Draw value selector custom buttons
    // NOTE: BORDER_WIDTH and TEXT_ALIGNMENT forced values
    let tempBorderWidth = GuiGetStyle(BUTTON, BORDER_WIDTH);
    let tempTextAlign = GuiGetStyle(BUTTON, TEXT_ALIGNMENT);
    GuiSetStyle(BUTTON, BORDER_WIDTH, GuiGetStyle(VALUEBOX, BORDER_WIDTH));
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    if (GuiButton(leftButtonBound, GuiIconText(RICON_ARROW_LEFT_FILL, null))) value -= step;
    if (GuiButton(rightButtonBound, GuiIconText(RICON_ARROW_RIGHT_FILL, null))) value += step;

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, tempTextAlign);
    GuiSetStyle(BUTTON, BORDER_WIDTH, tempBorderWidth);

    value = GuiDMValueBox(spinner, value, minValue, maxValue, precision, editMode);

    return value;
}

// Works just like `GuiListViewEx()` but with an array of properties instead of text.
export function GuiDMPropertyList( bounds, props, count, focus, scrollIndex) {
    const PROPERTY_COLLAPSED_ICON = "#120#";
    const PROPERTY_EXPANDED_ICON = "#121#";

    const PROPERTY_PADDING = 6;
    const PROPERTY_ICON_SIZE = 16;
    const PROPERTY_DECIMAL_DIGITS = 3;  //how many digits to show (used only for the vector properties)

    // NOTE: Using ListView style for everything !!
    let state = GuiGetState();
    let propFocused = (focus == null)? -1 : focus[0];
    let scroll = scrollIndex[0] > 0 ? 0 : scrollIndex[0]; // NOTE: scroll should always be negative or 0

    // Each property occupies a certain number of slots, highly synchronized with the properties enum (GUI_PROP_BOOL ... GUI_PROP_SECTION)
    // NOTE: If you add a custom property type make sure to add the number of slots it occupies here !!
    const propSlots = [1,1,1,2,1,3,4,5,5,5,1];

    let absoluteBounds = new Rectangle(); // total bounds for all of the properties (unclipped)
    // We need to loop over all the properties to get total height so we can see if we need a scrollbar or not
    for(let p=0; p<count; p++) {
        // Calculate height of this property (properties can occupy 1 or more slots)
        let height = GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
        if(props[p].type < propSlots.length) {
            if(!PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED)) height = propSlots[props[p].type]*GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
            if(props[p].type == GUI_PROP_SECTION && (PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED))) p += props[p].vsection; // skip slots for collapsed section
        }
        absoluteBounds.height += height+1;
    }

    // Check if we need a scrollbar and adjust bounds when necesary
    let useScrollBar = absoluteBounds.height > bounds.height - 2*GuiGetStyle(DEFAULT, BORDER_WIDTH) ? true : false;
    if(!useScrollBar && scroll != 0) scroll = 0; // make sure scroll is 0 when there's no scrollbar

    let scrollBarBounds = new Rectangle(bounds.x + GuiGetStyle(LISTVIEW, BORDER_WIDTH), bounds.y + GuiGetStyle(LISTVIEW, BORDER_WIDTH),
        GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH),  bounds.height - 2*GuiGetStyle(DEFAULT, BORDER_WIDTH));

    absoluteBounds.x = bounds.x + GuiGetStyle(LISTVIEW, LIST_ITEMS_SPACING) + GuiGetStyle(DEFAULT, BORDER_WIDTH);
    absoluteBounds.y = bounds.y + GuiGetStyle(LISTVIEW, LIST_ITEMS_SPACING) + GuiGetStyle(DEFAULT, BORDER_WIDTH) + scroll;
    absoluteBounds.width = bounds.width - 2*(GuiGetStyle(LISTVIEW, LIST_ITEMS_SPACING) + GuiGetStyle(DEFAULT, BORDER_WIDTH));

    if(useScrollBar) {
        if(GuiGetStyle(LISTVIEW, SCROLLBAR_SIDE) == SCROLLBAR_LEFT_SIDE) {
            absoluteBounds.x += GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH); // scrollbar is on the LEFT, adjust bounds
        } else {
            scrollBarBounds.x = bounds.x + bounds.width - GuiGetStyle(LISTVIEW, BORDER_WIDTH) - GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH); // scrollbar is on the RIGHT
        }
        absoluteBounds.width -= GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH); // adjust width to fit the scrollbar
    }

    let maxScroll = absoluteBounds.height + 2*(GuiGetStyle(LISTVIEW, LIST_ITEMS_SPACING) + GuiGetStyle(DEFAULT, BORDER_WIDTH))-bounds.height;

    // Update control
    //--------------------------------------------------------------------
    let mousePos = GetMousePosition();
    // NOTE: most of the update code is actually done in the draw control section
    if ((state != STATE_DISABLED) && !guiLocked) {
        if(!CheckCollisionPointRec(mousePos, bounds)) {
            propFocused = -1;
        }

        if (useScrollBar) {
            let wheelMove = GetMouseWheelMove();
            scroll += wheelMove*count;
            if(-scroll > maxScroll) scroll = -maxScroll;
        }
    }
    //--------------------------------------------------------------------


    // Draw control
    //--------------------------------------------------------------------
    DrawRectangleRec(bounds, Fade(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)), guiAlpha) );     // Draw background
    DrawRectangleLinesEx(bounds, GuiGetStyle(DEFAULT, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(LISTVIEW, BORDER + state*3)), guiAlpha)); // Draw border

    BeginScissorMode(absoluteBounds.x, bounds.y + GuiGetStyle(DEFAULT, BORDER_WIDTH), absoluteBounds.width, bounds.height - 2*GuiGetStyle(DEFAULT, BORDER_WIDTH));
    let currentHeight = 0;
    for(let p=0; p<count; ++p) {
        let height = GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
        if(props[p].type < propSlots.length && !PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED) ) {
            height = propSlots[props[p].type]*GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT); // get property height based on how many slots it occupies
        }

        // Even with scissor mode on, draw only properties that we can see (comment out both BeginScissorMode() / EndScissorMode() to see this)
        if(absoluteBounds.y + currentHeight + height >= bounds.y && absoluteBounds.y + currentHeight <= bounds.y + bounds.height) {
            let propBounds = new Rectangle(absoluteBounds.x, absoluteBounds.y + currentHeight, absoluteBounds.width, height);
            let textColor = Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_NORMAL)), guiAlpha);
            let propState = STATE_NORMAL;

            // Get the state of this property and do some initial drawing
            if(PROP_CHECK_FLAG(props[p], GUI_PFLAG_DISABLED)) {
                propState = STATE_DISABLED;
                propBounds.height += 1;
                DrawRectangleRec(propBounds, Fade(GetColor(GuiGetStyle(LISTVIEW, BASE_COLOR_DISABLED)), guiAlpha));
                propBounds.height -= 1;
                textColor = Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_DISABLED)), guiAlpha);
            } else if(CheckCollisionPointRec(mousePos, propBounds) && !guiLocked) {
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    propState = STATE_PRESSED;
                    //DrawRectangleRec(propRect, Fade(GetColor(GuiGetStyle(LISTVIEW, BASE_COLOR_PRESSED)), guiAlpha));
                    textColor = Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_PRESSED)), guiAlpha);
                } else {
                    propState = STATE_FOCUSED;
                    propFocused = p;
                    //DrawRectangleRec(propRect, Fade(GetColor(GuiGetStyle(LISTVIEW, BASE_COLOR_FOCUSED)), guiAlpha));
                    textColor = Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_FOCUSED)), guiAlpha);
                }
            } else {
                propState = STATE_NORMAL;
            }

            if(propState == STATE_DISABLED) GuiSetState(propState);
            switch(props[p].type) {
                case GUI_PROP_BOOL: {
                    // draw property name
                    GuiDrawText(props[p].name, new Rectangle(propBounds.x + PROPERTY_PADDING, propBounds.y, propBounds.width/2-PROPERTY_PADDING, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)), TEXT_ALIGN_LEFT, textColor);
                    if(propState == STATE_PRESSED) props[p].vbool = !props[p].vbool; // toggle the property value when clicked

                    // draw property value
                    const locked = guiLocked;
                    GuiLock(); // lock the checkbox since we changed the value manually
                    GuiCheckBox(new Rectangle(propBounds.x+propBounds.width/2, propBounds.y + height/4, height/2, height/2), props[p].vbool? "Yes" : "No", props[p].vbool);
                    if(!locked) GuiUnlock(); // only unlock when needed
                } break;

                case GUI_PROP_INT:
                    // draw property name
                    GuiDrawText(props[p].name, new Rectangle(propBounds.x + PROPERTY_PADDING, propBounds.y, propBounds.width/2-PROPERTY_PADDING, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)), TEXT_ALIGN_LEFT, textColor);
                    // draw property value
                    props[p].vint.val = GuiDMSpinner(new Rectangle(propBounds.x+propBounds.width/2, propBounds.y + 1, propBounds.width/2, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) - 2),
                    props[p].vint.val, props[p].vint.min, props[p].vint.max, props[p].vint.step, 0, (propState == STATE_FOCUSED) );
                    break;

                case GUI_PROP_FLOAT:
                    // draw property name
                    GuiDrawText(props[p].name, new Rectangle(propBounds.x + PROPERTY_PADDING, propBounds.y, propBounds.width/2-PROPERTY_PADDING, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)), TEXT_ALIGN_LEFT, textColor);
                    // draw property value
                    props[p].vfloat.val = GuiDMSpinner(new Rectangle(propBounds.x+propBounds.width/2, propBounds.y + 1, propBounds.width/2, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) - 2),
                    props[p].vfloat.val, props[p].vfloat.min, props[p].vfloat.max, props[p].vfloat.step, props[p].vfloat.precision, (propState == STATE_FOCUSED) );
                    break;

                case GUI_PROP_TEXT: {
                    let titleBounds = new Rectangle( propBounds.x, propBounds.y, propBounds.width, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) );
                    // Collapse/Expand property on click
                    if((propState == STATE_PRESSED) && CheckCollisionPointRec(mousePos, titleBounds)) {
                        PROP_TOGGLE_FLAG(props[p], GUI_PFLAG_COLLAPSED);
                    }

                    // draw property name
                    GuiDrawText(PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED) ? PROPERTY_COLLAPSED_ICON : PROPERTY_EXPANDED_ICON, titleBounds, TEXT_ALIGN_LEFT, textColor);
                    GuiDrawText(props[p].name, new Rectangle(propBounds.x+PROPERTY_ICON_SIZE+PROPERTY_PADDING, propBounds.y, propBounds.width-PROPERTY_ICON_SIZE-PROPERTY_PADDING, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)), TEXT_ALIGN_LEFT, textColor);
                    GuiDrawText(TextFormat("%i/%i", props[p].vtext.val.length, props[p].vtext.size), new Rectangle(propBounds.x+propBounds.width/2, propBounds.y + 1, propBounds.width/2, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) - 2), TEXT_ALIGN_LEFT, textColor);

                    // draw property value
                    if(!PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED)) {
                        GuiTextBox(new Rectangle(propBounds.x, propBounds.y + GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)+1, propBounds.width, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)-2), props[p].vtext.val, props[p].vtext.size, (propState == STATE_FOCUSED));
                    }
                } break;

                case GUI_PROP_SELECT: {
                    // TODO: Create a custom dropdownbox control instead of using the raygui combobox
                    // draw property name
                    GuiDrawText(props[p].name, new Rectangle(propBounds.x + PROPERTY_PADDING, propBounds.y, propBounds.width/2-PROPERTY_PADDING, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)), TEXT_ALIGN_LEFT, textColor);
                    // draw property value
                    GuiComboBox(new Rectangle(propBounds.x+propBounds.width/2, propBounds.y + 1, propBounds.width/2, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) - 2),
                    props[p].vselect.val, props[p].vselect.active);
                } break;

                case GUI_PROP_VECTOR2: case GUI_PROP_VECTOR3: case GUI_PROP_VECTOR4: {
                let titleBounds = new Rectangle( propBounds.x, propBounds.y, propBounds.width, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) );
                // Collapse/Expand property on click
                if((propState == STATE_PRESSED) && CheckCollisionPointRec(mousePos, titleBounds))
                    PROP_TOGGLE_FLAG(props[p], GUI_PFLAG_COLLAPSED);

                let fmt = "";
                if(props[p].type == GUI_PROP_VECTOR2) fmt = TextFormat("[%.0f, %.0f]", props[p].v2.x, props[p].v2.y);
                else if(props[p].type == GUI_PROP_VECTOR3) fmt = TextFormat("[%.0f, %.0f, %.0f]", props[p].v3.x, props[p].v3.y, props[p].v3.z);
                else fmt = TextFormat("[%.0f, %.0f, %.0f, %.0f]", props[p].v4.x, props[p].v4.y, props[p].v4.z, props[p].v4.w);

                // draw property name
                GuiDrawText(PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED) ? PROPERTY_COLLAPSED_ICON : PROPERTY_EXPANDED_ICON, titleBounds, TEXT_ALIGN_LEFT, textColor);
                GuiDrawText(props[p].name, new Rectangle( propBounds.x+PROPERTY_ICON_SIZE+PROPERTY_PADDING, propBounds.y, propBounds.width-PROPERTY_ICON_SIZE-PROPERTY_PADDING, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)), TEXT_ALIGN_LEFT, textColor);
                GuiDrawText(fmt, new Rectangle(propBounds.x+propBounds.width/2, propBounds.y + 1, propBounds.width/2, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) - 2), TEXT_ALIGN_LEFT, textColor);

                // draw X, Y, Z, W values (only when expanded)
                if(!PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED)) {
                    let slotBounds = new Rectangle( propBounds.x, propBounds.y+GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)+1, propBounds.width, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)-2);
                    let lblBounds = new Rectangle( propBounds.x+PROPERTY_PADDING, slotBounds.y, GetTextWidth("A"), slotBounds.height);
                    let valBounds = new Rectangle( lblBounds.x+lblBounds.width+PROPERTY_PADDING, slotBounds.y, propBounds.width-lblBounds.width-2*PROPERTY_PADDING, slotBounds.height);
                    GuiDrawText("X", lblBounds, TEXT_ALIGN_LEFT, textColor);
                    props[p].v2.x = GuiDMSpinner(valBounds, props[p].v2.x, 0.0, 0.0, 1.0, PROPERTY_DECIMAL_DIGITS, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                    slotBounds.y += GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
                    lblBounds.y = valBounds.y = slotBounds.y;
                    GuiDrawText("Y", lblBounds, TEXT_ALIGN_LEFT, textColor);
                    props[p].v2.y = GuiDMSpinner(valBounds, props[p].v2.y, 0.0, 0.0, 1.0, PROPERTY_DECIMAL_DIGITS, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                    slotBounds.y += GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
                    lblBounds.y = valBounds.y = slotBounds.y;
                    if(props[p].type >= GUI_PROP_VECTOR3) {
                        GuiDrawText("Z", lblBounds, TEXT_ALIGN_LEFT, textColor);
                        props[p].v3.z = GuiDMSpinner(valBounds, props[p].v3.z, 0.0, 0.0, 1.0, PROPERTY_DECIMAL_DIGITS, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                        slotBounds.y += GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
                        lblBounds.y = valBounds.y = slotBounds.y;
                    }

                    if(props[p].type >= GUI_PROP_VECTOR4) {
                        GuiDrawText("W", lblBounds, TEXT_ALIGN_LEFT, textColor);
                        props[p].v4.w = GuiDMSpinner(valBounds, props[p].v4.w, 0.0, 0.0, 1.0, PROPERTY_DECIMAL_DIGITS, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                    }
                }
            }   break;

                case GUI_PROP_RECT:{
                    let titleBounds = new Rectangle( propBounds.x, propBounds.y, propBounds.width, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) );
                    // Collapse/Expand property on click
                    if((propState == STATE_PRESSED) && CheckCollisionPointRec(mousePos, titleBounds))
                        PROP_TOGGLE_FLAG(props[p], GUI_PFLAG_COLLAPSED);

                    // draw property name
                    GuiDrawText(PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED) ? PROPERTY_COLLAPSED_ICON : PROPERTY_EXPANDED_ICON, titleBounds, TEXT_ALIGN_LEFT, textColor);
                    GuiDrawText(props[p].name, new Rectangle(propBounds.x+PROPERTY_ICON_SIZE+PROPERTY_PADDING, propBounds.y, propBounds.width-PROPERTY_ICON_SIZE-PROPERTY_PADDING, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)), TEXT_ALIGN_LEFT, textColor);
                    GuiDrawText(TextFormat("[%.0f, %.0f, %.0f, %.0f]", props[p].vrect.x, props[p].vrect.y, props[p].vrect.width, props[p].vrect.height),
                        new Rectangle(propBounds.x+propBounds.width/2, propBounds.y + 1, propBounds.width/2, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) - 2), TEXT_ALIGN_LEFT, textColor);

                    // draw X, Y, Width, Height values (only when expanded)
                    if(!PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED)) {
                        let slotBounds = new Rectangle( propBounds.x, propBounds.y+GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)+1, propBounds.width, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)-2);
                        let lblBounds = new Rectangle( propBounds.x+PROPERTY_PADDING, slotBounds.y, GetTextWidth("Height"), slotBounds.height);
                        let valBounds = new Rectangle( lblBounds.x+lblBounds.width+PROPERTY_PADDING, slotBounds.y, propBounds.width-lblBounds.width-2*PROPERTY_PADDING, slotBounds.height);
                        GuiDrawText("X", lblBounds, TEXT_ALIGN_LEFT, textColor);
                        props[p].vrect.x = GuiDMSpinner(valBounds, props[p].vrect.x, 0.0, 0.0, 1.0, 0, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                        slotBounds.y += GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
                        lblBounds.y = valBounds.y = slotBounds.y;
                        GuiDrawText("Y", lblBounds, TEXT_ALIGN_LEFT, textColor);
                        props[p].vrect.y = GuiDMSpinner(valBounds, props[p].vrect.y, 0.0, 0.0, 1.0, 0, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                        slotBounds.y += GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
                        lblBounds.y = valBounds.y = slotBounds.y;
                        GuiDrawText("Width", lblBounds, TEXT_ALIGN_LEFT, textColor);
                        props[p].vrect.width = GuiDMSpinner(valBounds, props[p].vrect.width, 0.0, 0.0, 1.0, 0, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                        slotBounds.y += GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
                        lblBounds.y = valBounds.y = slotBounds.y;
                        GuiDrawText("Height", lblBounds, TEXT_ALIGN_LEFT, textColor);
                        props[p].vrect.height = GuiDMSpinner(valBounds, props[p].vrect.height, 0.0, 0.0, 1.0, 0, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                    }
                } break;


                case GUI_PROP_COLOR: {
                    let titleBounds = new Rectangle( propBounds.x, propBounds.y, propBounds.width, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) );
                    // Collapse/Expand property on click
                    if((propState == STATE_PRESSED) && CheckCollisionPointRec(mousePos, titleBounds)){
                        PROP_TOGGLE_FLAG(props[p], GUI_PFLAG_COLLAPSED);
                    }

                    // draw property name
                    GuiDrawText(PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED) ? PROPERTY_COLLAPSED_ICON : PROPERTY_EXPANDED_ICON, titleBounds, TEXT_ALIGN_LEFT, textColor);
                    GuiDrawText(props[p].name, new Rectangle(propBounds.x+PROPERTY_ICON_SIZE+PROPERTY_PADDING, propBounds.y+1, propBounds.width-PROPERTY_ICON_SIZE-PROPERTY_PADDING, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)-2), TEXT_ALIGN_LEFT, textColor);
                    DrawLineEx( new Vector2(propBounds.x+propBounds.width/2, propBounds.y + GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) - 5), new Vector2(propBounds.x+propBounds.width, propBounds.y + GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) - 5), 6, props[p].vcolor);
                    const fmt = TextFormat("#%02X%02X%02X%02X", props[p].vcolor.r, props[p].vcolor.g, props[p].vcolor.b, props[p].vcolor.a);
                    GuiDrawText(fmt, new Rectangle(propBounds.x+propBounds.width/2, propBounds.y + 1, propBounds.width/2, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) - 2), TEXT_ALIGN_LEFT, textColor);

                    // draw R, G, B, A values (only when expanded)
                    if(!PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED)) {
                        let slotBounds = new Rectangle( propBounds.x, propBounds.y+GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)+1, propBounds.width, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)-2);
                        let lblBounds = new Rectangle( propBounds.x+PROPERTY_PADDING, slotBounds.y, GetTextWidth("A"), slotBounds.height);
                        let valBounds = new Rectangle( lblBounds.x+lblBounds.width+PROPERTY_PADDING, slotBounds.y, GetTextWidth("000000"), slotBounds.height);
                        let sbarBounds = new Rectangle( valBounds.x + valBounds.width + PROPERTY_PADDING, slotBounds.y, slotBounds.width - 3*PROPERTY_PADDING - lblBounds.width - valBounds.width, slotBounds.height );

                        if(sbarBounds.width <= GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)-2) valBounds.width = propBounds.width-lblBounds.width-2*PROPERTY_PADDING; // hide slider when no space
                        // save current scrollbar style
                        let tmpSliderPadding = GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_PADDING);
                        let tmpPadding = GuiGetStyle(SCROLLBAR, SCROLL_PADDING);
                        let tmpBorder = GuiGetStyle(SCROLLBAR, BORDER_WIDTH);
                        let tmpSliderSize = GuiGetStyle(SCROLLBAR, SCROLL_SLIDER_SIZE);
                        let tmpArrows =  GuiGetStyle(SCROLLBAR, ARROWS_VISIBLE);
                        let tmpBG1 = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_DISABLED));
                        // set a custom scrollbar style
                        GuiSetStyle(SCROLLBAR, SCROLL_SLIDER_PADDING, 3);
                        GuiSetStyle(SCROLLBAR, SCROLL_PADDING, 10);
                        GuiSetStyle(SCROLLBAR, BORDER_WIDTH, 0);
                        GuiSetStyle(SCROLLBAR, SCROLL_SLIDER_SIZE, 6);
                        GuiSetStyle(SCROLLBAR, ARROWS_VISIBLE, 0);
                        GuiSetStyle(DEFAULT, BORDER_COLOR_DISABLED, GuiGetStyle(DEFAULT, BACKGROUND_COLOR)); // disable scrollbar background

                        GuiDrawText("R", lblBounds, TEXT_ALIGN_LEFT, textColor);
                        props[p].vcolor.r = GuiDMValueBox(valBounds, props[p].vcolor.r, 0.0, 255.0, 0, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                        if(sbarBounds.width > GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)-2)
                            props[p].vcolor.r = GuiScrollBar(sbarBounds, props[p].vcolor.r, 0, 255);
                        slotBounds.y += GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
                        lblBounds.y = valBounds.y = sbarBounds.y = slotBounds.y;

                        GuiDrawText("G", lblBounds, TEXT_ALIGN_LEFT, textColor);
                        props[p].vcolor.g = GuiDMValueBox(valBounds, props[p].vcolor.g, 0.0, 255.0, 0, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                        if(sbarBounds.width > GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)-2)
                            props[p].vcolor.g = GuiScrollBar(sbarBounds, props[p].vcolor.g, 0, 255);
                        slotBounds.y += GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
                        lblBounds.y = valBounds.y = sbarBounds.y = slotBounds.y;

                        GuiDrawText("B", lblBounds, TEXT_ALIGN_LEFT, textColor);
                        props[p].vcolor.b = GuiDMValueBox(valBounds, props[p].vcolor.b, 0.0, 255.0, 0, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                        if(sbarBounds.width > GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)-2)
                            props[p].vcolor.b = GuiScrollBar(sbarBounds, props[p].vcolor.b, 0, 255);
                        slotBounds.y += GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
                        lblBounds.y = valBounds.y = sbarBounds.y = slotBounds.y;

                        GuiDrawText("A", lblBounds, TEXT_ALIGN_LEFT, textColor);
                        props[p].vcolor.a = GuiDMValueBox(valBounds, props[p].vcolor.a, 0.0, 255.0, 0, (propState == STATE_FOCUSED) && CheckCollisionPointRec(mousePos, slotBounds) );
                        if(sbarBounds.width > GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)-2)
                            props[p].vcolor.a = GuiScrollBar(sbarBounds, props[p].vcolor.a, 0, 255);

                        // load saved scrollbar style
                        GuiSetStyle(SCROLLBAR, SCROLL_SLIDER_PADDING, tmpSliderPadding);
                        GuiSetStyle(SCROLLBAR, SCROLL_PADDING, tmpPadding);
                        GuiSetStyle(SCROLLBAR, BORDER_WIDTH, tmpBorder);
                        GuiSetStyle(SCROLLBAR, SCROLL_SLIDER_SIZE, tmpSliderSize);
                        GuiSetStyle(SCROLLBAR, ARROWS_VISIBLE, tmpArrows);
                        GuiSetStyle(DEFAULT, BORDER_COLOR_DISABLED, ColorToInt(tmpBG1));
                    }

                    // support COPY/PASTE (need to do this here since GuiDMValueBox() also has COPY/PASTE so we need to overwrite it)
                    if((propState == STATE_FOCUSED)) {
                        if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C))
                            SetClipboardText(fmt);
                        else if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_V)){
                            let a = props[p].vcolor.a, r = props[p].vcolor.r, g=props[p].vcolor.g, b=props[p].vcolor.b;
                            let clip = GetClipboardText();
                            //read format "#%02X%02X%02X%02X"
                            [r,g,b,a] = [Number(clip.substring(1,3)),Number(clip.substring(3,5)),Number(clip.substring(5,7)),Number(clip.substring(7,9))];
                            props[p].vcolor.r=r; props[p].vcolor.g=g; props[p].vcolor.b=b; props[p].vcolor.a=a;
                        }
                    }
                } break;

                case GUI_PROP_SECTION: {
                    let titleBounds = new Rectangle( propBounds.x, propBounds.y, propBounds.width, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) );
                    // Collapse/Expand section on click
                    if( (propState == STATE_PRESSED) && CheckCollisionPointRec(mousePos, titleBounds) )
                        PROP_TOGGLE_FLAG(props[p], GUI_PFLAG_COLLAPSED);

                    if(!PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED)) {
                        GuiDrawText(PROPERTY_EXPANDED_ICON, titleBounds, TEXT_ALIGN_LEFT, textColor);
                        GuiDrawText(props[p].name, new Rectangle(propBounds.x+PROPERTY_ICON_SIZE+PROPERTY_PADDING, propBounds.y, propBounds.width-PROPERTY_ICON_SIZE-PROPERTY_PADDING, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)), TEXT_ALIGN_CENTER, textColor);
                    } else {
                        GuiDrawText(PROPERTY_COLLAPSED_ICON, titleBounds, TEXT_ALIGN_LEFT, textColor);
                        GuiDrawText(TextFormat("%s [%i]", props[p].name, props[p].vsection), new Rectangle(propBounds.x+PROPERTY_ICON_SIZE+PROPERTY_PADDING, propBounds.y, propBounds.width-PROPERTY_ICON_SIZE-PROPERTY_PADDING, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)), TEXT_ALIGN_CENTER, textColor);
                    }
                } break;


                // NOTE: Add your custom property here !!
                default: {
                    // draw property name
                    GuiDrawText(props[p].name, new Rectangle(propBounds.x + PROPERTY_PADDING, propBounds.y, propBounds.width/2-PROPERTY_PADDING, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT)), TEXT_ALIGN_LEFT, textColor);
                    // draw property type
                    GuiDrawText(TextFormat("TYPE %i", props[p].type), new Rectangle(propBounds.x+propBounds.width/2, propBounds.y + 1, propBounds.width/2, GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) - 2), TEXT_ALIGN_LEFT, textColor);
                } break;

            } // end of switch()

            GuiSetState(state);
        }

        currentHeight += height + 1;

        // Skip collapsed section. Don't put this code inside the switch !!
        if(props[p].type == GUI_PROP_SECTION && (PROP_CHECK_FLAG(props[p], GUI_PFLAG_COLLAPSED))) p += props[p].vsection;
    } // end for
    EndScissorMode();

    if(useScrollBar) {
        scroll = -GuiScrollBar(scrollBarBounds, -scroll, 0, maxScroll);
        scrollIndex[0] = scroll;
    }
    //--------------------------------------------------------------------

    if(focus != null) focus[0] = propFocused;
}

// Handy function to save properties to a file. Returns false on failure or true otherwise.
export function GuiDMSaveProperties(file, props, count) {
    if(file == null || props == null) return false;
    if(count == 0) return true;

    let f = std.open(file, "w");
    if(f == null) return false;

    // write header
    f.printf("#\n# Property types:\n"+
    "#   b  <name> <flags> <value>                                    // Bool\n"+
    "#   i  <name> <flags> <value> <min> <max> <step>                 // Int\n"+
    "#   f  <name> <flags> <value> <min> <max> <step> <precision>     // Float\n"+
    "#   t  <name> <flags> <value> <edit_length>                      // Text\n"+
    "#   l  <name> <flags> <value> <active>                           // Select\n"+
    "#   g  <name> <flags> <value>                                    // Section (Group)\n"+
    "#   v2 <name> <flags> <x> <y>                                    // Vector 2D\n"+
    "#   v3 <name> <flags> <x> <y> <z>                                // Vector 3D\n"+
    "#   v4 <name> <flags> <x> <y> <z> <w>                            // Vector 4D\n"+
    "#   r  <name> <flags> <x> <y> <width> <height>                   // Rectangle\n"+
    "#   c  <name> <flags> <r> <g> <b> <a>                            // Color\n"+
    "#\n\n");
    for(let p=0; p<count; p++) {
        switch(props[p].type) {
            case GUI_PROP_BOOL:
                f.printf("b  %s %i %i\n", props[p].name, props[p].flags, props[p].vbool);
                break;
            case GUI_PROP_INT:
                f.printf("i  %s %i %i %i %i %i\n", props[p].name, props[p].flags, props[p].vint.val, props[p].vint.min,
                props[p].vint.max, props[p].vint.step);
                break;
            case GUI_PROP_FLOAT:
                f.printf("f  %s %i %f %f %f %f %i\n", props[p].name, props[p].flags, props[p].vfloat.val, props[p].vfloat.min,
                props[p].vfloat.max, props[p].vfloat.step, props[p].vfloat.precision);
                break;
            case GUI_PROP_TEXT:
                f.printf("t  %s %i %s %i\n", props[p].name, props[p].flags, props[p].vtext.val, props[p].vtext.size);
                break;
            case GUI_PROP_SELECT:
                f.printf("l  %s %i %s %i\n", props[p].name, props[p].flags, props[p].vselect.val, props[p].vselect.active);
                break;
            case GUI_PROP_SECTION:
                f.printf("g  %s %i %i\n", props[p].name, props[p].flags, props[p].vsection);
                break;
            case GUI_PROP_VECTOR2:
                f.printf("v2 %s %i %f %f\n", props[p].name, props[p].flags, props[p].v2.x, props[p].v2.y);
                break;
            case GUI_PROP_VECTOR3:
                f.printf("v3 %s %i %f %f %f\n", props[p].name, props[p].flags, props[p].v3.x, props[p].v3.y, props[p].v3.z);
                break;
            case GUI_PROP_VECTOR4:
                f.printf("v4 %s %i %f %f %f %f\n", props[p].name, props[p].flags, props[p].v4.x, props[p].v4.y,
                props[p].v4.z, props[p].v4.w);
                break;
            case GUI_PROP_RECT:
                f.printf("r  %s %i %i %i %i %i\n", props[p].name, props[p].flags, props[p].vrect.x, props[p].vrect.y,
                props[p].vrect.width, props[p].vrect.height);
                break;
            case GUI_PROP_COLOR:
                f.printf("c  %s %i %i %i %i %i\n", props[p].name, props[p].flags, props[p].vcolor.r, props[p].vcolor.g,
                props[p].vcolor.b, props[p].vcolor.a);
                break;
        }
    }

    f.close();
    return true;
}