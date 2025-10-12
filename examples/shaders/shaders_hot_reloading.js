/*******************************************************************************************
*
*   raylib [shaders] example - Hot reloading
*
*   Example complexity rating: [★★★☆] 3/4
*
*   NOTE: This example requires raylib OpenGL 3.3 for shaders support and only #version 330
*         is currently supported. OpenGL ES 2.0 platforms are not supported at the moment.
*
*   Example originally created with raylib 3.0, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {
    BeginDrawing, BeginShaderMode, BLACK, ClearBackground, CloseWindow, DrawRectangle, DrawText, EndDrawing, EndShaderMode, GetFileModTime, GetFrameTime, GetMousePosition, GetShaderLocation, InitWindow, IsKeyPressed, IsMouseButtonPressed, KEY_A, LoadShader, MOUSE_BUTTON_LEFT, RAYWHITE, RED, SetShaderValue, SetTargetFPS, SHADER_UNIFORM_FLOAT, SHADER_UNIFORM_VEC2, TextFormat, UnloadShader, WHITE, WindowShouldClose
} from "rayjs:raylib";
import {rlGetShaderIdDefault} from "rayjs:rlgl";

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

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - hot reloading");

    const fragShaderFileName = "resources/shaders/glsl%i/reload.fs";
    let fragShaderFileModTime = GetFileModTime(TextFormat(fragShaderFileName, GLSL_VERSION));

    // Load raymarching shader
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    let shader = LoadShader(null, TextFormat(fragShaderFileName, GLSL_VERSION));

    // Get shader locations for required uniforms
    let resolutionLoc = GetShaderLocation(shader, "resolution");
    let mouseLoc = GetShaderLocation(shader, "mouse");
    let timeLoc = GetShaderLocation(shader, "time");

    let resolution = [ screenWidth, screenHeight ];
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    let totalTime = 0;
    let shaderAutoReloading = false;

    SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {           // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        totalTime += GetFrameTime();
        let mouse = GetMousePosition();
        let mousePos = [ mouse.x, mouse.y ];

        // Set shader required uniform values
        SetShaderValue(shader, timeLoc, totalTime, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, mouseLoc, mousePos, SHADER_UNIFORM_VEC2);

        // Hot shader reloading
        if (shaderAutoReloading || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
            let currentFragShaderModTime = GetFileModTime(TextFormat(fragShaderFileName, GLSL_VERSION));

            // Check if shader file has been modified
            if (currentFragShaderModTime != fragShaderFileModTime) {
                // Try reloading updated shader
                let updatedShader = LoadShader(0, TextFormat(fragShaderFileName, GLSL_VERSION));

                if (updatedShader.id != rlGetShaderIdDefault()) {     // It was correctly loaded
                    UnloadShader(shader);
                    shader = updatedShader;

                    // Get shader locations for required uniforms
                    resolutionLoc = GetShaderLocation(shader, "resolution");
                    mouseLoc = GetShaderLocation(shader, "mouse");
                    timeLoc = GetShaderLocation(shader, "time");

                    // Reset required uniforms
                    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
                }

                fragShaderFileModTime = currentFragShaderModTime;
            }
        }

        if (IsKeyPressed(KEY_A)) shaderAutoReloading = !shaderAutoReloading;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // We only draw a white full-screen rectangle, frame is generated in shader
            BeginShaderMode(shader);
                DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
            EndShaderMode();

            DrawText(TextFormat("PRESS [A] to TOGGLE SHADER AUTOLOADING: %s",
                     shaderAutoReloading? "AUTO" : "MANUAL"), 10, 10, 10, shaderAutoReloading? RED : BLACK);
            if (!shaderAutoReloading) DrawText("MOUSE CLICK to SHADER RE-LOADING", 10, 30, 10, BLACK);

            //Note: in c spec, time_t is not always a timestamp
            DrawText(TextFormat("Shader last modification: %s", String(new Date(fragShaderFileModTime))), 10, 430, 10, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);           // Unload shader

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
