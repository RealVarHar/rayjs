/*******************************************************************************************
*
*   raylib [shaders] example - Apply an shdrOutline to a texture
*
*   Example complexity rating: [★★★☆] 3/4
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   Example originally created with raylib 4.0, last time updated with raylib 4.0
*
*   Example contributed by Samuel Skiff (@GoldenThumbs) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2025 Samuel SKiff (@GoldenThumbs) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {BeginDrawing,
    BeginShaderMode,
    ClearBackground, CloseWindow, DrawFPS, DrawText, DrawTexture,
    EndDrawing,
    EndShaderMode, GRAY, GetMouseWheelMove, GetScreenWidth, GetShaderLocation, InitWindow, LoadShader, LoadTexture,
    MAROON,
    RAYWHITE, SHADER_UNIFORM_FLOAT,
    SHADER_UNIFORM_VEC2,
    SHADER_UNIFORM_VEC4, SetShaderValue, SetTargetFPS, TextFormat, UnloadShader, UnloadTexture, WHITE, WindowShouldClose } from 'rayjs:raylib';

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

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - Apply an outline to a texture");

    let texture = LoadTexture("resources/fudesumi.png");

    let shdrOutline = LoadShader(null, TextFormat("resources/shaders/glsl%i/outline.fs", GLSL_VERSION));

    let outlineSize = 2;
    let outlineColor = [ 1, 0, 0, 1 ];     // Normalized RED color
    let textureSize = [ texture.width, texture.height ];

    // Get shader locations
    let outlineSizeLoc = GetShaderLocation(shdrOutline, "outlineSize");
    let outlineColorLoc = GetShaderLocation(shdrOutline, "outlineColor");
    let textureSizeLoc = GetShaderLocation(shdrOutline, "textureSize");

    // Set shader values (they can be changed later)
    SetShaderValue(shdrOutline, outlineSizeLoc, outlineSize, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shdrOutline, outlineColorLoc, outlineColor, SHADER_UNIFORM_VEC4);
    SetShaderValue(shdrOutline, textureSizeLoc, textureSize, SHADER_UNIFORM_VEC2);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        outlineSize += GetMouseWheelMove();
        if (outlineSize < 1) outlineSize = 1;

        SetShaderValue(shdrOutline, outlineSizeLoc, outlineSize, SHADER_UNIFORM_FLOAT);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginShaderMode(shdrOutline);

                DrawTexture(texture, GetScreenWidth()/2 - texture.width/2, -30, WHITE);

            EndShaderMode();

            DrawText("Shader-based\ntexture\noutline", 10, 10, 20, GRAY);
            DrawText("Scroll mouse wheel to\nchange outline size", 10, 72, 20, GRAY);
            DrawText(TextFormat("Outline size: %i px", Math.floor(outlineSize)), 10, 120, 20, MAROON);

            DrawFPS(710, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);
    UnloadShader(shdrOutline);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
