/*******************************************************************************************
*
*   raylib [shaders] example - fog
*
*   Example complexity rating: [★★★☆] 3/4
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3).
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.7
*
*   Example contributed by Chris Camacho (@chriscamacho) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Chris Camacho (@chriscamacho) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {FLAG_MSAA_4X_HINT, InitWindow, SetConfigFlags, Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadModelFromMesh, GenMeshTorus, LoadTexture, GenMeshCube, GenMeshSphere, MATERIAL_MAP_DIFFUSE, LoadShader, TextFormat, SHADER_LOC_MATRIX_MODEL, SHADER_LOC_VECTOR_VIEW, GetShaderLocation, SetShaderValue, SHADER_UNIFORM_VEC4, SHADER_UNIFORM_FLOAT, WHITE, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_ORBITAL, IsKeyDown, KEY_UP, KEY_DOWN, SHADER_UNIFORM_VEC3, BeginDrawing, ClearBackground, GRAY, BeginMode3D, DrawModel, RAYWHITE, EndMode3D, DrawText, EndDrawing, UnloadModel, UnloadTexture, UnloadShader, CloseWindow } from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';
import * as rli from 'rayjs:rlights';

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

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - fog");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 2, 2, 6 );    // Camera position
    camera.target = new Vector3( 0, 0.5, 0 );    // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;      // Camera projection type

    // Load models and texture
    let modelA = LoadModelFromMesh(GenMeshTorus(0.4, 1, 16, 32));
    let modelB = LoadModelFromMesh(GenMeshCube(1, 1, 1));
    let modelC = LoadModelFromMesh(GenMeshSphere(0.5, 32, 32));
    let texture = LoadTexture("resources/texel_checker.png");

    // Assign texture to default model material
    modelA.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    modelB.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    modelC.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    // Load shader and set up some uniforms
    let shader = LoadShader(TextFormat("resources/shaders/glsl%i/lighting.vs", GLSL_VERSION),
                            TextFormat("resources/shaders/glsl%i/fog.fs", GLSL_VERSION));
    shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // Ambient light level
    let ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, [ 0.2, 0.2, 0.2, 1 ], SHADER_UNIFORM_VEC4);

    let fogDensity = 0.15;
    let fogDensityLoc = GetShaderLocation(shader, "fogDensity");
    SetShaderValue(shader, fogDensityLoc, fogDensity, SHADER_UNIFORM_FLOAT);

    // NOTE: All models share the same shader
    modelA.materials[0].shader = shader;
    modelB.materials[0].shader = shader;
    modelC.materials[0].shader = shader;

    // Using just 1 point lights
    rli.CreateLight(rli.LIGHT_POINT, new Vector3( 0, 2, 6 ), rm.Vector3Zero(), WHITE, shader);

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);

        if (IsKeyDown(KEY_UP)) {
            fogDensity += 0.001;
            if (fogDensity > 1) fogDensity = 1;
        }

        if (IsKeyDown(KEY_DOWN)) {
            fogDensity -= 0.001;
            if (fogDensity < 0) fogDensity = 0;
        }

        SetShaderValue(shader, fogDensityLoc, fogDensity, SHADER_UNIFORM_FLOAT);

        // Rotate the torus
        modelA.transform = rm.MatrixMultiply(modelA.transform, rm.MatrixRotateX(-0.025));
        modelA.transform = rm.MatrixMultiply(modelA.transform, rm.MatrixRotateZ(0.012));

        // Update the light shader with the camera view position
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], camera.position.x, SHADER_UNIFORM_VEC3);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GRAY);

            BeginMode3D(camera);

                // Draw the three models
                DrawModel(modelA, rm.Vector3Zero(), 1, WHITE);
                DrawModel(modelB, new Vector3( -2.6, 0, 0 ), 1, WHITE);
                DrawModel(modelC, new Vector3( 2.6, 0, 0 ), 1, WHITE);

                for (let i = -20; i < 20; i += 2) DrawModel(modelA,new Vector3( i, 0, 2 ), 1, WHITE);

            EndMode3D();

            DrawText(TextFormat("Use KEY_UP/KEY_DOWN to change fog density [%.2f]", fogDensity), 10, 10, 20, RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(modelA);        // Unload the model A
    UnloadModel(modelB);        // Unload the model B
    UnloadModel(modelC);        // Unload the model C
    UnloadTexture(texture);     // Unload the texture
    UnloadShader(shader);       // Unload shader

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
