/*******************************************************************************************
*
*   raylib [shaders] example - Texture drawing
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   NOTE: This example illustrates how to draw into a blank texture using a shader
*
*   Example originally created with raylib 2.0, last time updated with raylib 3.7
*
*   Example contributed by Michał Ciesielski (@ciessielski) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Michał Ciesielski (@ciessielski) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {BLANK, BeginDrawing,
    BeginShaderMode,
    ClearBackground,
    CloseWindow,
    DrawText,
    DrawTexture,
    EndDrawing, EndShaderMode, GenImageColor, GetShaderLocation, GetTime, InitWindow, LoadShader, LoadTextureFromImage,
    MAROON,
    RAYWHITE,
    SHADER_UNIFORM_FLOAT,
    SetShaderValue, SetTargetFPS, TextFormat, UnloadImage, UnloadShader, UnloadTexture, WHITE, WindowShouldClose } from 'rayjs:raylib';

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - texture drawing");

    let imBlank = GenImageColor(1024, 1024, BLANK);
    let texture = LoadTextureFromImage(imBlank);  // Load blank texture to fill on shader
    UnloadImage(imBlank);

    // NOTE: Using GLSL 330 shader version, on OpenGL ES 2.0 use GLSL 100 shader version
    let shader = LoadShader(null, TextFormat("resources/shaders/glsl%i/cubes_panning.fs", GLSL_VERSION));

    let time = 0;
    let timeLoc = GetShaderLocation(shader, "uTime");
    SetShaderValue(shader, timeLoc, time, SHADER_UNIFORM_FLOAT);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // -------------------------------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        time = GetTime();
        SetShaderValue(shader, timeLoc, time, SHADER_UNIFORM_FLOAT);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginShaderMode(shader);    // Enable our custom shader for next shapes/textures drawings
                DrawTexture(texture, 0, 0, WHITE);  // Drawing BLANK texture, all magic happens on shader
            EndShaderMode();            // Disable our custom shader, return to default shader

            DrawText("BACKGROUND is PAINTED and ANIMATED on SHADER!", 10, 10, 20, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);
    UnloadTexture(texture);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
