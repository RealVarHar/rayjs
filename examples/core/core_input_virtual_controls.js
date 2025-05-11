/*******************************************************************************************
*
*   raylib [core] example - input virtual controls
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example create by GreenSnakeLinux (@GreenSnakeLinux),
*   lighter by oblerion (@oblerion) and 
*   reviewed by Ramon Santamaria (@raysan5) and
*   improved by danilwhale (@danilwhale)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024-2025 oblerion (@oblerion) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing, BLACK, BLUE, ClearBackground, CloseWindow, DARKGRAY, DrawCircleV, DrawText, EndDrawing, GetFrameTime, GetMousePosition, GetTouchPointCount, GetTouchPosition, GREEN, InitWindow, IsMouseButtonDown, MAROON, MOUSE_BUTTON_LEFT, RAYWHITE, RED, SetTargetFPS, Vector2, WindowShouldClose, YELLOW
} from "rayjs:raylib";

const BUTTON_NONE = -1;
const BUTTON_UP = 0;
const BUTTON_LEFT = 1;
const BUTTON_RIGHT = 2;
const BUTTON_DOWN = 3;
const BUTTON_MAX = 4;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input virtual controls");

    let padPosition = new Vector2( 100, 350 );
    let buttonRadius = 30;

    let buttonPositions = [
        new Vector2( padPosition.x,padPosition.y - buttonRadius*1.5 ),  // Up
        new Vector2( padPosition.x - buttonRadius*1.5, padPosition.y ), // Left
        new Vector2( padPosition.x + buttonRadius*1.5, padPosition.y ), // Right
        new Vector2( padPosition.x, padPosition.y + buttonRadius*1.5 )  // Down
    ];

    const buttonLabels = [
        "Y",    // Up
        "X",    // Left
        "B",    // Right
        "A"     // Down
    ];

    let buttonLabelColors = [
        YELLOW, // Up
        BLUE,   // Left
        RED,    // Right
        GREEN   // Down
    ];

    let pressedButton = BUTTON_NONE;
    let inputPosition = new Vector2( 0, 0 );

    let playerPosition = new Vector2( screenWidth/2, screenHeight/2 );
    let playerSpeed = 75;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){    // Detect window close button or ESC key
        // Update
        //--------------------------------------------------------------------------
        if ((GetTouchPointCount() > 0)){
            // Use touch position
            inputPosition = GetTouchPosition(0);
        } else {
            // Use mouse position
            inputPosition = GetMousePosition();
        }

        // Reset pressed button to none
        pressedButton = BUTTON_NONE;

        // Make sure user is pressing left mouse button if they're from desktop
        if ((GetTouchPointCount() > 0) || ((GetTouchPointCount() == 0) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))) {
            // Find nearest D-Pad button to the input position
            for (let i = 0; i < BUTTON_MAX; i++) {
                let distX = Math.abs(buttonPositions[i].x - inputPosition.x);
                let distY = Math.abs(buttonPositions[i].y - inputPosition.y);

                if ((distX + distY < buttonRadius)) {
                    pressedButton = i;
                    break;
                }
            }
        }

        // Move player according to pressed button
        switch (pressedButton) {
            case BUTTON_UP: playerPosition.y -= playerSpeed*GetFrameTime(); break;
            case BUTTON_LEFT: playerPosition.x -= playerSpeed*GetFrameTime(); break;
            case BUTTON_RIGHT: playerPosition.x += playerSpeed*GetFrameTime(); break;
            case BUTTON_DOWN: playerPosition.y += playerSpeed*GetFrameTime(); break;
            default: break;
        };

        //--------------------------------------------------------------------------
        // Draw
        //--------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw world
            DrawCircleV(playerPosition, 50, MAROON);

            // Draw GUI
            for (let i = 0; i < BUTTON_MAX; i++) {
                DrawCircleV(buttonPositions[i], buttonRadius, (i == pressedButton)? DARKGRAY : BLACK);

                DrawText(buttonLabels[i],
                    Math.floor(buttonPositions[i].x) - 7, Math.floor(buttonPositions[i].y) - 8,
                    20, buttonLabelColors[i]);
            }

            DrawText("move the player with D-Pad buttons", 10, 10, 20, DARKGRAY);

        EndDrawing();
        //--------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}

