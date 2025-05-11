/*******************************************************************************************
*
*   raylib [shaders] example - Vertex displacement
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 5.0, last time updated with raylib 4.5
*
*   Example contributed by Alex ZH (@ZzzhHe) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2025 Alex ZH (@ZzzhHe)
*
********************************************************************************************/

import * as os from 'qjs:os';
import { InitWindow, Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadShader, TextFormat, GenImagePerlinNoise, LoadTextureFromImage, UnloadImage, GetShaderLocation, GenMeshPlane, LoadModelFromMesh, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_FREE, GetFrameTime, SetShaderValue, SHADER_UNIFORM_FLOAT, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, BeginShaderMode, DrawModel, Color, EndShaderMode, EndMode3D, DrawText, DARKGRAY, DrawFPS, UnloadShader, UnloadModel, UnloadTexture, CloseWindow, EndDrawing } from 'rayjs:raylib';
import * as rg from 'rayjs:rlgl';
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

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - vertex displacement");

    // set up camera
    let camera = new Camera();
    camera.position = new Vector3(20, 5, -20);
    camera.target = new Vector3(0, 0, 0);
    camera.up = new Vector3(0, 1, 0);
    camera.fovy = 60;
    camera.projection = CAMERA_PERSPECTIVE;

    // Load vertex and fragment shaders
    let shader = LoadShader(
        TextFormat("resources/shaders/glsl%i/vertex_displacement.vs", GLSL_VERSION),
        TextFormat("resources/shaders/glsl%i/vertex_displacement.fs", GLSL_VERSION)
    );
    
    // Load perlin noise texture
    let perlinNoiseImage = GenImagePerlinNoise(512, 512, 0, 0, 1);
    let perlinNoiseMap = LoadTextureFromImage(perlinNoiseImage);
    UnloadImage(perlinNoiseImage);

    // Set shader uniform location
    let perlinNoiseMapLoc = GetShaderLocation(shader, "perlinNoiseMap");
    rg.rlEnableShader(shader.id);
    rg.rlActiveTextureSlot(1);
    rg.rlEnableTexture(perlinNoiseMap.id);
    rg.rlSetUniformSampler(perlinNoiseMapLoc, 1);
    
    // Create a plane mesh and model
    let planeMesh = GenMeshPlane(50, 50, 50, 50);
    let planeModel = LoadModelFromMesh(planeMesh);
    // Set plane model material
    planeModel.materials[0].shader = shader;

    let time = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_FREE); // Update camera

        time += GetFrameTime(); // Update time variable
        SetShaderValue(shader, GetShaderLocation(shader, "time"), time, SHADER_UNIFORM_FLOAT); // Send time value to shader

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                BeginShaderMode(shader);
                    // Draw plane model
                    DrawModel(planeModel, new Vector3( 0, 0, 0 ), 1, new Color( 255, 255, 255, 255) );
                EndShaderMode();

            EndMode3D();

            DrawText("Vertex displacement", 10, 10, 20, DARKGRAY);
            DrawFPS(10, 40);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);
    UnloadModel(planeModel);
    UnloadTexture(perlinNoiseMap);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
