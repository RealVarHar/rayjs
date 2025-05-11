/*******************************************************************************************
*
*   raylib [textures] example - Image Rotation
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BeginDrawing,
    ClearBackground,
    CloseWindow,
    DARKGRAY,
    DrawText,
    DrawTexture,
    EndDrawing, ImageRotate, InitWindow, IsKeyPressed, IsMouseButtonPressed, KEY_RIGHT, LoadImage, LoadTextureFromImage,
    MOUSE_BUTTON_LEFT,
    RAYWHITE, SetTargetFPS, UnloadTexture, WHITE, WindowShouldClose } from "rayjs:raylib";

const NUM_TEXTURES = 3;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - texture rotation");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    let image45 = LoadImage("resources/raylib_logo.png");
    let image90 = LoadImage("resources/raylib_logo.png");
    let imageNeg90 = LoadImage("resources/raylib_logo.png");

    ImageRotate(image45, 45);
    ImageRotate(image90, 90);
    ImageRotate(imageNeg90, -90);

    let textures = new Array(NUM_TEXTURES);

    textures[0] = LoadTextureFromImage(image45);
    textures[1] = LoadTextureFromImage(image90);
    textures[2] = LoadTextureFromImage(imageNeg90);

    let currentTexture = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_RIGHT)) {
            currentTexture = (currentTexture + 1)%NUM_TEXTURES; // Cycle between the textures
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(textures[currentTexture], screenWidth/2 - textures[currentTexture].width/2, screenHeight/2 - textures[currentTexture].height/2, WHITE);

            DrawText("Press LEFT MOUSE BUTTON to rotate the image clockwise", 250, 420, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    for (let i = 0; i < NUM_TEXTURES; i++) UnloadTexture(textures[i]);

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
