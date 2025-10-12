/*******************************************************************************************
*
*   raylib [text] example - Input Box
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.7, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BeginDrawing, CheckCollisionPointRec,
    ClearBackground,
    CloseWindow,
    DARKGRAY,
    DrawRectangleLines,
    DrawRectangleRec,
    DrawText,
    EndDrawing,
    GRAY,
    GetCharPressed, GetKeyPressed, GetMousePosition, InitWindow, IsKeyPressed,
    KEY_BACKSPACE, LIGHTGRAY, MAROON, MOUSE_CURSOR_DEFAULT, MOUSE_CURSOR_IBEAM, MeasureText, RAYWHITE, RED, Rectangle,
    SetMouseCursor, SetTargetFPS, TextFormat, WindowShouldClose } from "rayjs:raylib";

const MAX_INPUT_CHARS = 9;

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
function IsAnyKeyPressed() {
    let keyPressed = false;
    let key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - input box");

    let name = "";      // NOTE: One extra space required for null terminator char '\0'
    let letterCount = 0;

    let textBox = new Rectangle( screenWidth/2 - 100, 180, 225, 50 );
    let mouseOnText = false;

    let framesCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText) {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            let key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0) {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
                    name += String.fromCodePoint(key);// Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name = name.substring(0,letterCount);
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY);

            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText) DrawRectangleLines(Math.floor(textBox.x), Math.floor(textBox.y), Math.floor(textBox.width), Math.floor(textBox.height), RED);
            else DrawRectangleLines(Math.floor(textBox.x), Math.floor(textBox.y), Math.floor(textBox.width), Math.floor(textBox.height), DARKGRAY);

            DrawText(name, Math.floor(textBox.x) + 5, Math.floor(textBox.y) + 8, 40, MAROON);

            DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

            if (mouseOnText) {
                if (letterCount < MAX_INPUT_CHARS) {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", Math.floor(textBox.x) + 8 + MeasureText(name, 40), Math.floor(textBox.y) + 12, 40, MAROON);
                }
                else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}