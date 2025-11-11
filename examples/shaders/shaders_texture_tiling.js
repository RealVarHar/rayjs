/*******************************************************************************************
*
*   raylib [shaders] example - texture tiling
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example demonstrates how to tile a texture on a 3D model using raylib.
*
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by Luis Almeida (@luis605) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2025 Luis Almeida (@luis605)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {BeginDrawing,
    BeginMode3D, BeginShaderMode, CAMERA_FREE, CAMERA_PERSPECTIVE, Camera3D, ClearBackground,
    CloseWindow, DARKGRAY, DisableCursor,
    DrawGrid,
    DrawModel, DrawText, EndDrawing, EndMode3D, EndShaderMode, GenMeshCube,
    GetShaderLocation, InitWindow, IsKeyPressed, LoadModelFromMesh, LoadShader, LoadTexture,
    MATERIAL_MAP_DIFFUSE, RAYWHITE, SHADER_UNIFORM_VEC2, SetShaderValue, SetTargetFPS, TextFormat,
    UnloadModel,
    UnloadShader,
    UnloadTexture,
    UpdateCamera, Vector3, WHITE, WindowShouldClose } from 'rayjs:raylib';

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

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - texture tiling");

    // Define the camera to look into our 3d world
    let camera = new Camera3D();
    camera.position = new Vector3( 4, 4, 4 ); // Camera position
    camera.target = new Vector3( 0, 0.5, 0 ); // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );       // Camera up vector (rotation towards target)
    camera.fovy = 45;                         // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;   // Camera projection type

    // Load a cube model
    let cube = GenMeshCube(1, 1, 1);
    let model = LoadModelFromMesh(cube);
    
    // Load a texture and assign to cube model
    let texture = LoadTexture("resources/cubicmap_atlas.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    // Set the texture tiling using a shader
    let tiling = [ 3, 3 ];
    let shader = LoadShader(null, TextFormat("resources/shaders/glsl%i/tiling.fs", GLSL_VERSION));
    SetShaderValue(shader, GetShaderLocation(shader, "tiling"), tiling, SHADER_UNIFORM_VEC2);
    model.materials[0].shader = shader;

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_FREE);

        if (IsKeyPressed('Z'.codePointAt(0))) camera.target = new Vector3( 0, 0.5, 0 );
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            
                BeginShaderMode(shader);
                    DrawModel(model, new Vector3( 0, 0, 0 ), 2, WHITE);
                EndShaderMode();

                DrawGrid(10, 1);
                
            EndMode3D();

            DrawText("Use mouse to rotate the camera", 10, 10, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model);         // Unload model
    UnloadShader(shader);       // Unload shader
    UnloadTexture(texture);     // Unload texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
