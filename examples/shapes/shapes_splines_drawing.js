/*******************************************************************************************
*
*   raylib [shapes] example - splines drawing
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as rg from 'rayjs:raygui';
import {BLACK, BLUE, BeginDrawing, CheckCollisionPointCircle, ClearBackground,
    CloseWindow,
    DARKBLUE,
    DrawCircleLinesV,
    DrawCircleV,
    DrawLineEx,
    DrawLineV,
    DrawSplineBasis,
    DrawSplineBezierCubic,
    DrawSplineCatmullRom,
    DrawSplineLinear, DrawText, EndDrawing, FLAG_MSAA_4X_HINT, GOLD, GRAY, GREEN, GetMousePosition, InitWindow,
    IsKeyPressed,
    IsMouseButtonDown,
    IsMouseButtonPressed,
    IsMouseButtonReleased,
    KEY_FOUR,
    KEY_ONE,
    KEY_THREE,
    KEY_TWO,
    LIGHTGRAY,
    MOUSE_LEFT_BUTTON, MOUSE_RIGHT_BUTTON,
    RAYWHITE, RED, Rectangle, SetConfigFlags, SetTargetFPS, TextFormat, Vector2, WindowShouldClose } from 'rayjs:raylib';

const MAX_SPLINE_POINTS = 32;

// Spline types
const SPLINE_LINEAR = 0;      // Linear
const SPLINE_BASIS = 1;       // B-Spline
const SPLINE_CATMULLROM = 2;  // Catmull-Rom
const SPLINE_BEZIER = 3;      // Cubic Bezier

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - splines drawing");

    let points = [
        new Vector2( 50 , 400 ),
        new Vector2( 160, 220 ),
        new Vector2( 340, 380 ),
        new Vector2( 520, 60  ),
        new Vector2( 710, 260 )
    ];
    
    // Array required for spline bezier-cubic, 
    // including control points interleaved with start-end segment points
    let pointsInterleaved = new Array(3*(MAX_SPLINE_POINTS - 1) + 1);
    
    let pointCount = 5;
    let selectedPoint = -1;
    let focusedPoint = -1;
    let selectedControlPoint = null;
    let focusedControlPoint = null;
    
    // Cubic Bezier control points initialization
    let control = new Array(MAX_SPLINE_POINTS-1);
    for (let i = 0; i < pointCount - 1; i++) {
        control[i] = {};
        control[i].start = new Vector2( points[i].x + 50, points[i].y );
        control[i].end = new Vector2( points[i + 1].x - 50, points[i + 1].y );
    }

    // Spline config variables
    let splineThickness = [8];
    let splineTypeActive = [SPLINE_LINEAR]; // 0-Linear, 1-BSpline, 2-CatmullRom, 3-Bezier
    let splineTypeEditMode = false;
    let splineHelpersActive = [true];
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Spline points creation logic (at the end of spline)
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && (pointCount < MAX_SPLINE_POINTS)) {
            points[pointCount] = GetMousePosition();
            let i = pointCount - 1;
            control[i].start = new Vector2( points[i].x + 50, points[i].y );
            control[i].end = new Vector2( points[i + 1].x - 50, points[i + 1].y );
            pointCount++;
        }

        // Spline point focus and selection logic
        for (let i = 0; i < pointCount; i++) {
            if (CheckCollisionPointCircle(GetMousePosition(), points[i], 8)) {
                focusedPoint = i;
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) selectedPoint = i; 
                break;
            }
            else focusedPoint = -1;
        }
        
        // Spline point movement logic
        if (selectedPoint >= 0) {
            points[selectedPoint] = GetMousePosition();
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) selectedPoint = -1;
        }
        
        // Cubic Bezier spline control points logic
        if ((splineTypeActive[0] == SPLINE_BEZIER) && (focusedPoint == -1)) {
            // Spline control point focus and selection logic
            for (let i = 0; i < pointCount - 1; i++) {
                if (CheckCollisionPointCircle(GetMousePosition(), control[i].start, 6)) {
                    focusedControlPoint = control[i].start;
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) selectedControlPoint = control[i].start;
                    break;
                } else if (CheckCollisionPointCircle(GetMousePosition(), control[i].end, 6)) {
                    focusedControlPoint = control[i].end;
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) selectedControlPoint = control[i].end;
                    break;
                }
                else focusedControlPoint = null;
            }
            
            // Spline control point movement logic
            if (selectedControlPoint != null) {
                selectedControlPoint = GetMousePosition();
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) selectedControlPoint = null;
            }
        }
        
        // Spline selection logic
        if (IsKeyPressed(KEY_ONE)) splineTypeActive[0] = 0;
        else if (IsKeyPressed(KEY_TWO)) splineTypeActive[0] = 1;
        else if (IsKeyPressed(KEY_THREE)) splineTypeActive[0] = 2;
        else if (IsKeyPressed(KEY_FOUR)) splineTypeActive[0] = 3;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
        
            if (splineTypeActive[0] == SPLINE_LINEAR) {
                // Draw spline: linear
                DrawSplineLinear(points, pointCount, splineThickness[0], RED);
            } else if (splineTypeActive[0] == SPLINE_BASIS) {
                // Draw spline: basis
                DrawSplineBasis(points, pointCount, splineThickness[0], RED);  // Provide connected points array

                /*
                for (int i = 0; i < (pointCount - 3); i++)
                {
                    // Drawing individual segments, not considering thickness connection compensation
                    DrawSplineSegmentBasis(points[i], points[i + 1], points[i + 2], points[i + 3], splineThickness, MAROON);
                }
                */
            } else if (splineTypeActive[0] == SPLINE_CATMULLROM) {
                // Draw spline: catmull-rom
                DrawSplineCatmullRom(points, pointCount, splineThickness[0], RED); // Provide connected points array
                
                /*
                for (int i = 0; i < (pointCount - 3); i++)
                {
                    // Drawing individual segments, not considering thickness connection compensation
                    DrawSplineSegmentCatmullRom(points[i], points[i + 1], points[i + 2], points[i + 3], splineThickness, MAROON);
                }
                */
            } else if (splineTypeActive[0] == SPLINE_BEZIER) {
                // NOTE: Cubic-bezier spline requires the 2 control points of each segnment to be 
                // provided interleaved with the start and end point of every segment
                for (let i = 0; i < (pointCount - 1); i++) {
                    pointsInterleaved[3*i] = points[i];
                    pointsInterleaved[3*i + 1] = control[i].start;
                    pointsInterleaved[3*i + 2] = control[i].end;
                }
                
                pointsInterleaved[3*(pointCount - 1)] = points[pointCount - 1];

                // Draw spline: cubic-bezier (with control points)
                DrawSplineBezierCubic(pointsInterleaved, 3*(pointCount - 1) + 1, splineThickness[0], RED);
                
                /*
                for (int i = 0; i < 3*(pointCount - 1); i += 3)
                {
                    // Drawing individual segments, not considering thickness connection compensation
                    DrawSplineSegmentBezierCubic(pointsInterleaved[i], pointsInterleaved[i + 1], pointsInterleaved[i + 2], pointsInterleaved[i + 3], splineThickness, MAROON);
                }
                */

                // Draw spline control points
                for (let i = 0; i < pointCount - 1; i++) {
                    // Every cubic bezier point have two control points
                    DrawCircleV(control[i].start, 6, GOLD);
                    DrawCircleV(control[i].end, 6, GOLD);
                    if (focusedControlPoint == control[i].start) DrawCircleV(control[i].start, 8, GREEN);
                    else if (focusedControlPoint == control[i].end) DrawCircleV(control[i].end, 8, GREEN);
                    DrawLineEx(points[i], control[i].start, 1, LIGHTGRAY);
                    DrawLineEx(points[i + 1], control[i].end, 1, LIGHTGRAY);
                
                    // Draw spline control lines
                    DrawLineV(points[i], control[i].start, GRAY);
                    //DrawLineV(control[i].start, control[i].end, LIGHTGRAY);
                    DrawLineV(control[i].end, points[i + 1], GRAY);
                }
            }

            if (splineHelpersActive[0]) {
                // Draw spline point helpers
                for (let i = 0; i < pointCount; i++) {
                    DrawCircleLinesV(points[i], (focusedPoint == i)? 12 : 8, (focusedPoint == i)? BLUE: DARKBLUE);
                    if ((splineTypeActive[0] != SPLINE_LINEAR) &&
                        (splineTypeActive[0] != SPLINE_BEZIER) &&
                        (i < pointCount - 1)) DrawLineV(points[i], points[i + 1], GRAY);

                    DrawText(TextFormat("[%.0f, %.0f]", points[i].x, points[i].y), Math.floor(points[i].x), Math.floor(points[i].y) + 10, 10, BLACK);
                }
            }

            // Check all possible UI states that require controls lock
            if (splineTypeEditMode) rg.GuiLock();
            
            // Draw spline config
            rg.GuiLabel(new Rectangle( 12, 62, 140, 24 ), TextFormat("Spline thickness: %i", Math.floor(splineThickness[0])));
            rg.GuiSliderBar(new Rectangle( 12, 60 + 24, 140, 16 ), null, null, splineThickness, 1, 40);

            rg.GuiCheckBox(new Rectangle( 12, 110, 20, 20 ), "Show point helpers", splineHelpersActive);

            rg.GuiUnlock();

            rg.GuiLabel(new Rectangle( 12, 10, 140, 24 ), "Spline type:");
            if (rg.GuiDropdownBox(new Rectangle( 12, 8 + 24, 140, 28 ), "LINEAR;BSPLINE;CATMULLROM;BEZIER", splineTypeActive, splineTypeEditMode)) splineTypeEditMode = !splineTypeEditMode;

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
