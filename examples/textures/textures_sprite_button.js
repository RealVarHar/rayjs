/*******************************************************************************************
*
*   raylib [textures] example - sprite button
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as rl from 'rayjs:raylib';
import {
    BeginDrawing, CheckCollisionPointRec, ClearBackground, CloseAudioDevice, CloseWindow, DrawTextureRec, EndDrawing, GetMousePosition, InitAudioDevice, InitWindow, IsMouseButtonDown, IsMouseButtonReleased, LoadSound, LoadTexture, MOUSE_BUTTON_LEFT, PlaySound, RAYWHITE, Rectangle, SetTargetFPS, UnloadSound, UnloadTexture, Vector2, WHITE, WindowShouldClose
} from "rayjs:raylib";
for (const key in rl) { globalThis[key] = rl[key] };

const NUM_FRAMES = 3;       // Number of frames (rectangles) for the button sprite texture

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - sprite button");

    InitAudioDevice();      // Initialize audio device

    let fxButton = LoadSound("resources/buttonfx.wav");   // Load button sound
    let button = LoadTexture("resources/button.png"); // Load button texture

    // Define frame rectangle for drawing
    let frameHeight = button.height/NUM_FRAMES;
    let sourceRec = new Rectangle( 0, 0, button.width, frameHeight );

    // Define button bounds on screen
    let btnBounds = new Rectangle( screenWidth/2 - button.width/2, screenHeight/2 - button.height/NUM_FRAMES/2, button.width, frameHeight );

    let btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    let btnAction = false;         // Button action should be activated

    let mousePoint = new Vector2( 0, 0 );

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePoint = GetMousePosition();
        btnAction = false;

        // Check button state
        if (CheckCollisionPointRec(mousePoint, btnBounds)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
            else btnState = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
        }
        else btnState = 0;

        if (btnAction) {
            PlaySound(fxButton);

            // TODO: Any desired action
        }

        // Calculate button frame rectangle to draw depending on button state
        sourceRec.y = btnState*frameHeight;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTextureRec(button, sourceRec, new Vector2( btnBounds.x, btnBounds.y ), WHITE); // Draw button frame

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(button);  // Unload button texture
    UnloadSound(fxButton);  // Unload sound

    CloseAudioDevice();     // Close audio device

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}