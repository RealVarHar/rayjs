/*******************************************************************************************
*
*   raylib [shaders] example - Raymarching shapes generation
*
*   Example complexity rating: [★★★★] 4/4
*
*   NOTE: This example requires raylib OpenGL 3.3 for shaders support and only #version 330
*         is currently supported. OpenGL ES 2.0 platforms are not supported at the moment.
*
*   Example originally created with raylib 2.0, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {FLAG_WINDOW_RESIZABLE, InitWindow, SetConfigFlags, Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadShader, TextFormat, GetShaderLocation, SetShaderValue, SHADER_UNIFORM_VEC2, DisableCursor, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_FIRST_PERSON, GetFrameTime, SHADER_UNIFORM_VEC3, SHADER_UNIFORM_FLOAT, IsWindowResized, GetScreenWidth, GetScreenHeight, BeginDrawing, ClearBackground, RAYWHITE, BeginShaderMode, DrawRectangle, WHITE, EndShaderMode, DrawText, BLACK, EndDrawing, UnloadShader, CloseWindow } from 'rayjs:raylib';

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

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - raymarching shapes");

    let camera = new Camera();
    camera.position = new Vector3( 2.5, 2.5, 3 );// Camera position
    camera.target = new Vector3( 0, 0, 0.7 );    // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 65;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;      // Camera projection type

    // Load raymarching shader
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    let shader = LoadShader(null, TextFormat("resources/shaders/glsl%i/raymarching.fs", GLSL_VERSION));

    // Get shader locations for required uniforms
    let viewEyeLoc = GetShaderLocation(shader, "viewEye");
    let viewCenterLoc = GetShaderLocation(shader, "viewCenter");
    let runTimeLoc = GetShaderLocation(shader, "runTime");
    let resolutionLoc = GetShaderLocation(shader, "resolution");

    let resolution = [ screenWidth, screenHeight ];
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    let runTime = 0;

    DisableCursor();                    // Limit cursor to relative movement inside the window
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_FIRST_PERSON);

        let cameraPos = [ camera.position.x, camera.position.y, camera.position.z ];
        let cameraTarget = [ camera.target.x, camera.target.y, camera.target.z ];

        let deltaTime = GetFrameTime();
        runTime += deltaTime;

        // Set shader required uniform values
        SetShaderValue(shader, viewEyeLoc, cameraPos, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, viewCenterLoc, cameraTarget, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, runTimeLoc, runTime, SHADER_UNIFORM_FLOAT);

        // Check if screen is resized
        if (IsWindowResized()) {
            resolution[0] = GetScreenWidth();
            resolution[1] = GetScreenHeight();
            SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // We only draw a white full-screen rectangle,
            // frame is generated in shader using raymarching
            BeginShaderMode(shader);
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            EndShaderMode();

            DrawText("(c) Raymarching shader by Iñigo Quilez. MIT License.", GetScreenWidth() - 280, GetScreenHeight() - 20, 10, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);           // Unload shader

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
