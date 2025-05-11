/*******************************************************************************************
*
*   raylib [shaders] example - Texture Waves
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
*         on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
*         raylib comes with shaders ready for both versions, check raylib/shaders install folder
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.7
*
*   Example contributed by Anata (@anatagawa) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Anata (@anatagawa) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {BeginDrawing,
    BeginShaderMode,
    ClearBackground,
    CloseWindow,
    DrawTexture,
    EndDrawing,
    EndShaderMode, GetFrameTime, GetScreenHeight, GetScreenWidth, GetShaderLocation, InitWindow, LoadShader, LoadTexture,
    RAYWHITE,
    SHADER_UNIFORM_FLOAT,
    SHADER_UNIFORM_VEC2,
    SetShaderValue, SetTargetFPS, TextFormat, UnloadShader, UnloadTexture, WHITE, WindowShouldClose } from 'rayjs:raylib';

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

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - texture waves");

    // Load texture texture to apply shaders
    let texture = LoadTexture("resources/space.png");

    // Load shader and setup location points and values
    let shader = LoadShader(null, TextFormat("resources/shaders/glsl%i/wave.fs", GLSL_VERSION));

    let secondsLoc = GetShaderLocation(shader, "seconds");
    let freqXLoc = GetShaderLocation(shader, "freqX");
    let freqYLoc = GetShaderLocation(shader, "freqY");
    let ampXLoc = GetShaderLocation(shader, "ampX");
    let ampYLoc = GetShaderLocation(shader, "ampY");
    let speedXLoc = GetShaderLocation(shader, "speedX");
    let speedYLoc = GetShaderLocation(shader, "speedY");

    // Shader uniform values that can be updated at any time
    let freqX = 25;
    let freqY = 25;
    let ampX = 5;
    let ampY = 5;
    let speedX = 8;
    let speedY = 8;

    let screenSize = [ GetScreenWidth(), GetScreenHeight() ];
    SetShaderValue(shader, GetShaderLocation(shader, "size"), screenSize, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, freqXLoc, freqX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, freqYLoc, freqY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, ampXLoc, ampX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, ampYLoc, ampY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, speedXLoc, speedX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, speedYLoc, speedY, SHADER_UNIFORM_FLOAT);

    let seconds = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // -------------------------------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        seconds += GetFrameTime();

        SetShaderValue(shader, secondsLoc, seconds, SHADER_UNIFORM_FLOAT);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginShaderMode(shader);

                DrawTexture(texture, 0, 0, WHITE);
                DrawTexture(texture, texture.width, 0, WHITE);

            EndShaderMode();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);         // Unload shader
    UnloadTexture(texture);       // Unload texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
