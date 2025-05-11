/*******************************************************************************************
*
*   CurveEdit v1.0 - A cubic Hermite editor for making animation curves
*
*   MODULE USAGE:
*       #define GUI_CURVE_EDITOR_IMPLEMENTATION
*       #include "gui_curve_edit.h"
*
*       INIT: GuiCurveEditState state = InitCurveEdit();
*       EVALUATE: float y = EvalGuiCurve(&state, t); // 0 <= t <= 1
*       DRAW: BeginScissorMode(bounds.x,bounds.y,bounds.width,bounds.height);
*               GuiCurveEdit(&state, bounds, pointSize);
*             EndScissorMode();
*
*   NOTE: See 'Module Structures Declaration' section for more informations.
*
*   NOTE: This module uses functions of the stdlib:
*       - qsort
*
*   NOTE: Built-in interactions:
*       - Left click to move/add point or move tangents
*       - While moving a tangent, hold (left/right) SHIFT to disable tangent symetry
*       - Right click to remove a point
*
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2023 Pierre Jaffuer (@smallcluster)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

import {BACKGROUND_COLOR,
    BASE_COLOR_FOCUSED,
    BASE_COLOR_NORMAL,
    BASE_COLOR_PRESSED,
    BORDER_COLOR_FOCUSED, BORDER_COLOR_NORMAL, BUTTON, DEFAULT, GuiGetFont, GuiGetStyle, LABEL,
    TEXT_COLOR_FOCUSED, TEXT_SIZE, TEXT_SPACING } from "rayjs:raygui";
import {CheckCollisionPointRec,
    Color, DrawLine, DrawRectangle, DrawRectangleLines,
    DrawSplineSegmentBezierCubic, DrawTextEx, GetColor, GetMousePosition,
    IsKeyDown,
    IsMouseButtonDown,
    IsMouseButtonPressed, IsMouseButtonReleased, KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT, MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT, Rectangle, TextFormat, Vector2 } from "rayjs:raylib";

const GUI_CURVE_EDITOR_MAX_POINTS = 30;

/***********************************************************************************
*
*   GUI_CURVE_EDITOR IMPLEMENTATION
*
************************************************************************************/

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
function InitGuiCurveEditor() {
    let state = {};

    state.start = 0; // Value at y = 0
    state.end = 1;   // Value at y = 1

    // Always valid (unless you manualy change state's point array). Make sure to set it to -1 before init
    state.selectedIndex = 0;
    state.mouseOffset = new Vector2( 0, 0 );

    // At least one point (AVG by default)
    state.numPoints = 1;
    // Unsorted array with at least one point (constant curve)
    state.points = new Array(1);
    state.points[0] = {
        position: new Vector2( 0.5, 0.5 ),
        tangents: new Vector2( 0.0, 0.0 ),
        leftLinear: false,
        rightLinear: false
    }

    // Private variables
    state.editLeftTangent = false;
    state.editRightTangent = false;

    return state;
}

function CompareGuiCurveEditPointPtr(a, b) {
    const fa = a.position.x;
    const fb = b.position.x;

    if(fa < fb){
        return -1;
    }else if(fa > fb){
        return 1;
    }
    return 0;
}

export function GuiCurveEval(state, t) {

    if (state.numPoints == 0) return state.start;

    // Sort points
    let sortedPoints = new Array(state.numPoints);

    for (let i=0; i < state.numPoints; i++) {
        sortedPoints[i] = state.points[i];
    };

    sortedPoints.sort(CompareGuiCurveEditPointPtr);

    // Constants part on edges
    if (t <= sortedPoints[0].position.x) return state.start + (state.end-state.start)*sortedPoints[0].position.y;
    if (t >= sortedPoints[state.numPoints-1].position.x) return state.start + (state.end-state.start)*sortedPoints[state.numPoints-1].position.y;

    // Find curve portion
    for (let i=0; i < state.numPoints-1; i++) {
        const p1 = sortedPoints[i];
        const p2 = sortedPoints[i+1];

        // Skip this range
        if (!((t >= p1.position.x) && (t < p2.position.x)) || (p1.position.x == p2.position.x)) continue;

        let scale = (p2.position.x-p1.position.x);
        let T = (t-p1.position.x)/scale;
        let startTangent = scale*p1.tangents.y;
        let endTangent = scale*p2.tangents.x;
        let T2 = T*T;
        let T3 = T*T*T;

        return (state.start + (state.end-state.start)*((2*T3 - 3*T2 + 1)*p1.position.y + (T3 - 2*T2 + T)*startTangent + (3*T2 - 2*T3)*p2.position.y + (T3 - T2)*endTangent));
    }

    return state.start;
}

export function GuiCurveEditor(state, bounds) {
    // CONST
    //----------------------------------------------------------------------------------
    const pointSize = 10;
    const fontSize = GuiGetStyle(DEFAULT, TEXT_SIZE);
    const handleLength = pointSize*2.5;
    const handleSize = pointSize/1.5;

    const innerBounds = new Rectangle( bounds.x + fontSize, bounds.y + fontSize, bounds.width - 2*fontSize, bounds.height - 2*fontSize );
    const mouse = GetMousePosition();
    const mouseLocal = new Vector2( (mouse.x - innerBounds.x)/innerBounds.width, (innerBounds.y + innerBounds.height-mouse.y)/innerBounds.height);
    //----------------------------------------------------------------------------------

    // UPDATE STATE
    //----------------------------------------------------------------------------------
    // Find first point under mouse (-1 if not found)
    let hoveredPointIndex = -1;
    for (let i = 0; i < state.numPoints; i++) {
        const p = state.points[i];
        const screenPos = new Vector2( p.position.x*innerBounds.width + innerBounds.x, innerBounds.y + innerBounds.height-p.position.y*innerBounds.height );
        const pointRect = new Rectangle( screenPos.x - pointSize/2, screenPos.y - pointSize/2, pointSize, pointSize );

        if (CheckCollisionPointRec(mouse, pointRect)) {
            hoveredPointIndex = i;
            break;
        }
    }

    // Unselect tangents
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        state.editLeftTangent = false;
        state.editRightTangent = false;
    }

    // Select a tangent if possible
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (state.selectedIndex != -1) && CheckCollisionPointRec(mouse, bounds)) {
        const p = state.points[state.selectedIndex];
        const screenPos = new Vector2( p.position.x*innerBounds.width+innerBounds.x, innerBounds.y+innerBounds.height-p.position.y*innerBounds.height );

        // Left control
        let target = new Vector2( (p.position.x-1)*innerBounds.width + innerBounds.x, innerBounds.y + innerBounds.height - (p.position.y-p.tangents.x)*innerBounds.height );
        let dir = new Vector2( target.x-screenPos.x, target.y-screenPos.y );
        let d = Math.sqrt(dir.x*dir.x + dir.y*dir.y);
        let control = new Vector2( screenPos.x + dir.x/d*handleLength, screenPos.y + dir.y/d*handleLength );
        let controlRect = new Rectangle( control.x - handleSize/2, control.y - handleSize/2, handleSize, handleSize );

        // Edit left tangent
        if (CheckCollisionPointRec(mouse, controlRect)) state.editLeftTangent = true;

        // Right control
        target = new Vector2( (p.position.x + 1)*innerBounds.width + innerBounds.x, innerBounds.y + innerBounds.height - (p.position.y + p.tangents.y)*innerBounds.height );
        dir = new Vector2( target.x-screenPos.x, target.y-screenPos.y );
        d = Math.sqrt(dir.x*dir.x + dir.y*dir.y);
        control = new Vector2( screenPos.x + dir.x/d*handleLength, screenPos.y + dir.y/d*handleLength );
        controlRect = new Rectangle( control.x - handleSize/2, control.y - handleSize/2, handleSize, handleSize );

        // Edit right tangent
        if (CheckCollisionPointRec(mouse, controlRect)) state.editRightTangent = true;
    }

    // Move tangents
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && state.editRightTangent) {
        // editRightTangent == true implies selectedIndex != -1
        const p = state.points[state.selectedIndex];
        const dir = new Vector2( mouseLocal.x - p.position.x, mouseLocal.y - p.position.y);

        // Calculate right tangent slope
        p.tangents.y = (dir.x < 0.001)? dir.y/0.001 : dir.y/dir.x;
        p.rightLinear = false; // Stop right linearization update

        // Tangents are symetric by default unless SHIFT is pressed
        if (!(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))) {
            p.tangents.x = p.tangents.y;
            p.leftLinear = false; // Stop left linearization update
        }

    }else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && state.editLeftTangent) {
        // editLeftTangent == true implies selectedIndex != -1
        const p = state.points[state.selectedIndex];
        const dir = new Vector2( mouseLocal.x - p.position.x, mouseLocal.y - p.position.y );

        // Calculate left tangent slope
        p.tangents.x = (dir.x > -0.001)? dir.y/(-0.001) : dir.y/dir.x;
        p.leftLinear = false; // Stop left linearization update

        // Tangents are symetric by default unless SHIFT is pressed
        if (!(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))) {
            p.tangents.y = p.tangents.x;
            p.rightLinear = false; // Stop right linearization update
        }
    }
    // Select a point
    else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (hoveredPointIndex != -1) && CheckCollisionPointRec(mouse, bounds)) {
        state.selectedIndex = hoveredPointIndex;
        const p = state.points[state.selectedIndex];
        state.mouseOffset = new Vector2( p.position.x - mouseLocal.x, p.position.y - mouseLocal.y );
    }
    // Remove a point (check against bounds)
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && (hoveredPointIndex != -1) && CheckCollisionPointRec(mouse, bounds) && (state.numPoints > 1)) {
        // Deselect everything
        state.selectedIndex = 0; // select first point by default
        state.editLeftTangent = false;
        state.editRightTangent = false;

        // Remove point
        state.numPoints -= 1;
        for (let i = hoveredPointIndex; i < state.numPoints; i++) state.points[i] = state.points[i+1];
    }
    // Add a point (check against innerBounds)
    else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, innerBounds) && (state.numPoints < GUI_CURVE_EDITOR_MAX_POINTS)) {
        state.editLeftTangent = false;
        state.editRightTangent = false;

        // Create new point
        let p ={
            tangents: new Vector2(),
            position: mouseLocal,
            leftLinear: false,
            rightLinear: false
        };

        // Append point
        state.points[state.numPoints] = p;
        state.selectedIndex = state.numPoints; // select new point
        state.numPoints += 1;

        // Point is add on mouse pos
        state.mouseOffset = new Vector2();
    }
    // Move selected point
    else if ((state.selectedIndex != -1) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, bounds)) {
        let p = state.points[state.selectedIndex];

        // use mouse offset on click to prevent point teleporting to mouse
        const newLocalPos = new Vector2( mouseLocal.x + state.mouseOffset.x, mouseLocal.y + state.mouseOffset.y );

        // Clamp to innerbounds
        p.position.x = (newLocalPos.x < 0)? 0 : ((newLocalPos.x > 1)? 1 : newLocalPos.x);
        p.position.y = (newLocalPos.y < 0)? 0 : ((newLocalPos.y > 1)? 1 : newLocalPos.y);
    }

    // Sort points
    let sortedPoints = new Array(state.numPoints);
    for (let i = 0; i < state.numPoints; i++) sortedPoints[i] = state.points[i];
    sortedPoints.sort(CompareGuiCurveEditPointPtr);

    // Update linear tangents
    for (let i = 0; i < state.numPoints; i++) {
        let p = sortedPoints[i];

        // Left tangent
        if ((i > 0) && p.leftLinear){
            const p2 = sortedPoints[i - 1];
            let dir = new Vector2( p2.position.x - p.position.x, p2.position.y - p.position.y );
            p.tangents.x = (dir.x == 0)? 0 : dir.y/dir.x;
        }

        // Right tangent
        if ((i < state.numPoints - 1) && p.rightLinear){
            const p2 = sortedPoints[i + 1];
            let dir = new Vector2( p2.position.x - p.position.x, p2.position.y - p.position.y );
            p.tangents.y = (dir.x == 0)? 0 : dir.y/dir.x;
        }
    }
    //----------------------------------------------------------------------------------

    // DRAWING
    //----------------------------------------------------------------------------------
    DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height, GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    // Draw grid
    // H lines
    const lineColor = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_NORMAL));
    DrawLine(bounds.x, innerBounds.y, bounds.x+bounds.width, innerBounds.y, lineColor); // end
    DrawLine(bounds.x, innerBounds.y+innerBounds.height/2, bounds.x+bounds.width, innerBounds.y+innerBounds.height/2, lineColor); // avg
    DrawLine(bounds.x, innerBounds.y+innerBounds.height, bounds.x+bounds.width, innerBounds.y+innerBounds.height, lineColor); // start

    // V lines
    DrawLine(innerBounds.x, bounds.y, innerBounds.x, bounds.y+bounds.height, lineColor); // 0
    DrawLine(innerBounds.x + innerBounds.width/4, bounds.y, innerBounds.x + innerBounds.width/4, bounds.y + bounds.height, lineColor); // 0.25
    DrawLine(innerBounds.x + innerBounds.width/2, bounds.y, innerBounds.x + innerBounds.width/2, bounds.y + bounds.height, lineColor); // 0.5
    DrawLine(innerBounds.x + 3*innerBounds.width/4, bounds.y, innerBounds.x + 3*innerBounds.width/4, bounds.y + bounds.height, lineColor); // 0.75
    DrawLine(innerBounds.x + innerBounds.width, bounds.y, innerBounds.x + innerBounds.width, bounds.y + bounds.height, lineColor); // 1

    let font = GuiGetFont();
    // V labels
    DrawTextEx(font, "0", new Vector2( innerBounds.x, bounds.y + bounds.height-fontSize), fontSize, GuiGetStyle(DEFAULT, TEXT_SPACING), lineColor);
    DrawTextEx(font, "0.25", new Vector2( innerBounds.x + innerBounds.width/4, bounds.y + bounds.height - fontSize), fontSize, GuiGetStyle(DEFAULT, TEXT_SPACING), lineColor);
    DrawTextEx(font, "0.5", new Vector2( innerBounds.x + innerBounds.width/2, bounds.y + bounds.height - fontSize), fontSize, GuiGetStyle(DEFAULT, TEXT_SPACING), lineColor);
    DrawTextEx(font, "0.75", new Vector2( innerBounds.x + 3*innerBounds.width/4, bounds.y + bounds.height-fontSize), fontSize, GuiGetStyle(DEFAULT, TEXT_SPACING), lineColor);
    DrawTextEx(font, "1", new Vector2( innerBounds.x + innerBounds.width, bounds.y+bounds.height - fontSize), fontSize, GuiGetStyle(DEFAULT, TEXT_SPACING), lineColor);

    // H labels
    DrawTextEx(font, TextFormat("%.2f", state.start), new Vector2( innerBounds.x, innerBounds.y - fontSize+innerBounds.height ), fontSize, GuiGetStyle(DEFAULT, TEXT_SPACING), lineColor);
    DrawTextEx(font, TextFormat("%.2f", state.start + (state.end-state.start)/2), new Vector2( innerBounds.x, innerBounds.y - fontSize + innerBounds.height/2 ), fontSize, GuiGetStyle(DEFAULT, TEXT_SPACING), lineColor);
    DrawTextEx(font, TextFormat("%.2f", state.end), new Vector2( innerBounds.x, innerBounds.y ), fontSize, GuiGetStyle(DEFAULT, TEXT_SPACING), lineColor);

    // Draw contours
    if (CheckCollisionPointRec(mouse, bounds)) DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_FOCUSED)));
    else DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_NORMAL)));

    // Draw points
    for (let i = 0; i < state.numPoints; i++) {
        const p = sortedPoints[i];

        const screenPos = new Vector2( p.position.x*innerBounds.width + innerBounds.x, innerBounds.y + innerBounds.height - p.position.y*innerBounds.height );
        const pointRect = new Rectangle( screenPos.x - pointSize/2, screenPos.y - pointSize/2, pointSize, pointSize );

        let pointColor = new Color();
        let pointBorderColor = new Color();

        // Draw point
        if (state.points[state.selectedIndex] == p) {
            // Draw left handle
            if (i > 0) {
                const target = new Vector2( (p.position.x - 1)*innerBounds.width + innerBounds.x, innerBounds.y + innerBounds.height - (p.position.y - p.tangents.x)*innerBounds.height );
                const dir = new Vector2( target.x - screenPos.x, target.y - screenPos.y );
                const d = Math.sqrt(dir.x*dir.x + dir.y*dir.y);
                const control = new Vector2( screenPos.x + dir.x/d*handleLength, screenPos.y + dir.y/d*handleLength );
                const controlRect = new Rectangle( control.x - handleSize/2, control.y - handleSize/2, handleSize, handleSize );

                let controlColor = new Color();

                if (state.editLeftTangent) {
                    controlColor = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_PRESSED));
                } else if (CheckCollisionPointRec(mouse, controlRect)) {
                    controlColor = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_FOCUSED));
                } else {
                    controlColor = GetColor(GuiGetStyle(BUTTON, BASE_COLOR_NORMAL));
                }

                DrawLine(screenPos.x,screenPos.y, control.x, control.y, controlColor);
                DrawRectangle(controlRect.x, controlRect.y, controlRect.width, controlRect.height, controlColor);
                DrawRectangleLines(controlRect.x, controlRect.y, controlRect.width, controlRect.height, controlColor);
            }

            // Draw right handle
            if (i < state.numPoints - 1) {
                const target = new Vector2( (p.position.x + 1)*innerBounds.width + innerBounds.x, innerBounds.y + innerBounds.height - (p.position.y + p.tangents.y)*innerBounds.height );
                const dir = new Vector2( target.x - screenPos.x, target.y - screenPos.y );
                const d = Math.sqrt(dir.x*dir.x + dir.y*dir.y);
                const control = new Vector2( screenPos.x + dir.x/d*handleLength, screenPos.y + dir.y/d*handleLength );
                const controlRect = new Rectangle( control.x - handleSize/2, control.y - handleSize/2, handleSize, handleSize );

                let controlColor = new Color();

                if (state.editRightTangent) {
                    controlColor = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_PRESSED));
                } else if (CheckCollisionPointRec(mouse, controlRect)) {
                    controlColor = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_FOCUSED));
                } else {
                    controlColor = GetColor(GuiGetStyle(BUTTON, BASE_COLOR_NORMAL));
                }

                DrawLine(screenPos.x,screenPos.y, control.x, control.y, controlColor);
                DrawRectangle(controlRect.x, controlRect.y, controlRect.width, controlRect.height, controlColor);
                DrawRectangleLines(controlRect.x, controlRect.y, controlRect.width, controlRect.height, controlColor);
            }

            pointColor = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_PRESSED));
            pointBorderColor = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_NORMAL));

        } else if (state.points[hoveredPointIndex] == p) {
            pointColor = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_FOCUSED));
            pointBorderColor = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_NORMAL));
        } else{
            pointColor = GetColor(GuiGetStyle(BUTTON, BASE_COLOR_NORMAL));
            pointBorderColor = GetColor(GuiGetStyle(BUTTON, BORDER_COLOR_NORMAL));
        }

        DrawRectangle(pointRect.x, pointRect.y, pointRect.width, pointRect.height, pointColor);
        DrawRectangleLines(pointRect.x, pointRect.y, pointRect.width, pointRect.height, pointBorderColor);
    }

    // Draw curve
    let curveColor = GetColor(GuiGetStyle(LABEL,  TEXT_COLOR_FOCUSED));

    if (state.numPoints == 1) {
        const p = sortedPoints[0];
        const screenPos = new Vector2( p.position.x*innerBounds.width + innerBounds.x, innerBounds.y + innerBounds.height - p.position.y*innerBounds.height );
        DrawLine(innerBounds.x, screenPos.y, innerBounds.x+innerBounds.width, screenPos.y, curveColor);
    } else {
        for (let i = 0; i < state.numPoints - 1; i++) {
            const p1 = sortedPoints[i];
            const p2 = sortedPoints[i + 1];
            const screenPos1 = new Vector2( p1.position.x*innerBounds.width + innerBounds.x, innerBounds.y + innerBounds.height - p1.position.y*innerBounds.height );
            const screenPos2 = new Vector2( p2.position.x*innerBounds.width + innerBounds.x, innerBounds.y + innerBounds.height - p2.position.y*innerBounds.height );

            // Constant on edge
            if ((screenPos1.x > innerBounds.x) && (i == 0)) {
                DrawLine(innerBounds.x, screenPos1.y, screenPos1.x, screenPos1.y, curveColor);
            }
            if ((screenPos2.x < innerBounds.x + innerBounds.width) && (i == (state.numPoints - 2))) {
                DrawLine(screenPos2.x, screenPos2.y, innerBounds.x+innerBounds.width, screenPos2.y, curveColor);
            }

            // Draw cubic Hermite curve
            const scale = (p2.position.x - p1.position.x)/3;
            const offset1 = new Vector2( scale, scale*p1.tangents.y );
            // negative endTangent => top part => need to invert value to calculate offset
            const offset2 = new Vector2( -scale, -scale*p2.tangents.x );

            const c1 = new Vector2( p1.position.x + offset1.x, p1.position.y + offset1.y );
            const c2 = new Vector2( p2.position.x + offset2.x, p2.position.y + offset2.y );

            const screenC1 = new Vector2( c1.x*innerBounds.width + innerBounds.x, innerBounds.y + innerBounds.height - c1.y*innerBounds.height );
            const screenC2 = new Vector2( c2.x*innerBounds.width + innerBounds.x, innerBounds.y + innerBounds.height - c2.y*innerBounds.height );

            DrawSplineSegmentBezierCubic(screenPos1, screenC1, screenC2, screenPos2, 1, curveColor);
        }
    }
}