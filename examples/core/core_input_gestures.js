/*******************************************************************************************
*
*   raylib [core] example - Input Gestures Detection
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.4, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing,
    CheckCollisionPointRec, ClearBackground, CloseWindow, DARKGRAY,
    DrawCircleV, DrawRectangle, DrawRectangleLines, DrawRectangleRec, DrawText, EndDrawing, Fade,
    GESTURE_DOUBLETAP,
    GESTURE_DRAG,
    GESTURE_HOLD,
    GESTURE_NONE,
    GESTURE_PINCH_IN, GESTURE_PINCH_OUT,
    GESTURE_SWIPE_DOWN,
    GESTURE_SWIPE_LEFT,
    GESTURE_SWIPE_RIGHT,
    GESTURE_SWIPE_UP,
    GESTURE_TAP,
    GetGestureDetected,
    GetTouchPosition, GRAY,
    InitWindow, LIGHTGRAY, MAROON, RAYWHITE,
    Rectangle,
    SetTargetFPS,
    Vector2,
    WindowShouldClose
} from "rayjs:raylib";

const MAX_GESTURE_STRINGS = 20;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input gestures");

    let touchPosition = new Vector2( 0, 0 );
    let touchArea = new Rectangle( 220, 10, screenWidth - 230, screenHeight - 20 );

    let gestureStrings = [];

    let currentGesture = GESTURE_NONE;
    let lastGesture = GESTURE_NONE;

    //SetGesturesEnabled(0b0000000000001001);   // Enable only some gestures to be detected

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        lastGesture = currentGesture;
        currentGesture = GetGestureDetected();
        touchPosition = GetTouchPosition(0);

        if (CheckCollisionPointRec(touchPosition, touchArea) && (currentGesture != GESTURE_NONE)) {
            if (currentGesture != lastGesture) {
                // Store gesture string
                switch (currentGesture) {
                    case GESTURE_TAP: gestureStrings.push("GESTURE TAP"); break;
                    case GESTURE_DOUBLETAP: gestureStrings.push("GESTURE DOUBLETAP"); break;
                    case GESTURE_HOLD: gestureStrings.push("GESTURE HOLD"); break;
                    case GESTURE_DRAG: gestureStrings.push("GESTURE DRAG"); break;
                    case GESTURE_SWIPE_RIGHT: gestureStrings.push("GESTURE SWIPE RIGHT"); break;
                    case GESTURE_SWIPE_LEFT: gestureStrings.push("GESTURE SWIPE LEFT"); break;
                    case GESTURE_SWIPE_UP: gestureStrings.push("GESTURE SWIPE UP"); break;
                    case GESTURE_SWIPE_DOWN: gestureStrings.push("GESTURE SWIPE DOWN"); break;
                    case GESTURE_PINCH_IN: gestureStrings.push("GESTURE PINCH IN"); break;
                    case GESTURE_PINCH_OUT: gestureStrings.push("GESTURE PINCH OUT"); break;
                    default: break;
                }

                // Reset gestures strings
                if (gestureStrings.length >= MAX_GESTURE_STRINGS) {
                    gestureStrings = [];
                }
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangleRec(touchArea, GRAY);
            DrawRectangle(225, 15, screenWidth - 240, screenHeight - 30, RAYWHITE);

            DrawText("GESTURES TEST AREA", screenWidth - 270, screenHeight - 40, 20, Fade(GRAY, 0.5));

            for (let i = 0; i < gestureStrings.length; i++){

                if (i%2 == 0) DrawRectangle(10, 30 + 20*i, 200, 20, Fade(LIGHTGRAY, 0.5));
                else DrawRectangle(10, 30 + 20*i, 200, 20, Fade(LIGHTGRAY, 0.3));

                if (i < gestureStrings.length - 1) DrawText(gestureStrings[i], 35, 36 + 20*i, 10, DARKGRAY);
                else DrawText(gestureStrings[i], 35, 36 + 20*i, 10, MAROON);
            }

            DrawRectangleLines(10, 29, 200, screenHeight - 50, GRAY);
            DrawText("DETECTED GESTURES", 50, 15, 10, GRAY);

            if (currentGesture != GESTURE_NONE) DrawCircleV(touchPosition, 30, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}