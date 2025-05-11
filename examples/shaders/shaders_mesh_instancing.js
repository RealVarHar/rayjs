/*******************************************************************************************
*
*   raylib [shaders] example - Mesh instancing
*
*   Example complexity rating: [★★★★] 4/4
*
*   Example originally created with raylib 3.7, last time updated with raylib 4.2
*
*   Example contributed by seanpringle (@seanpringle) and reviewed by Max (@moliad) and Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2025 seanpringle (@seanpringle), Max (@moliad) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from 'qjs:os';
import { InitWindow, Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, GenMeshCube, GetRandomValue, LoadShader, TextFormat, SHADER_LOC_MATRIX_MVP, SHADER_LOC_VECTOR_VIEW, GetShaderLocation, SHADER_UNIFORM_VEC4, WHITE, SetShaderValue, LoadMaterialDefault, MATERIAL_MAP_DIFFUSE, RED, BLUE, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_ORBITAL, SHADER_UNIFORM_VEC3, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawMesh, DrawMeshInstanced, EndMode3D, DrawFPS, EndDrawing, CloseWindow, Vector4 } from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';
import * as rli from 'rayjs:rlights';

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}

const MAX_INSTANCES = 10000;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    const DEG2RAD = Math.PI/180;

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - mesh instancing");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( -125, 125, -125 );    // Camera position
    camera.target = new Vector3( 0, 0, 0 );              // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );                  // Camera up vector (rotation towards target)
    camera.fovy = 45;                                        // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                     // Camera projection type

    // Define mesh to be instanced
    let cube = GenMeshCube(1, 1, 1);

    // Define transforms to be uploaded to GPU for instances
    let transforms = new Array(MAX_INSTANCES);   // Pre-multiplied transformations passed to rlgl

    // Translate and rotate cubes randomly
    for (let i = 0; i < MAX_INSTANCES; i++) {
        let translation = rm.MatrixTranslate(GetRandomValue(-50, 50), GetRandomValue(-50, 50), GetRandomValue(-50, 50));
        let axis = rm.Vector3Normalize(new Vector3( GetRandomValue(0, 360), GetRandomValue(0, 360), GetRandomValue(0, 360) ));
        let angle = GetRandomValue(0, 180)*DEG2RAD;
        let rotation = rm.MatrixRotate(axis, angle);
        
        transforms[i] = rm.MatrixMultiply(rotation, translation);
    }

    // Load lighting shader
    let shader = LoadShader(TextFormat("resources/shaders/glsl%i/lighting_instancing.vs", GLSL_VERSION),
                            TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));
    // Get shader locations
    shader.locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(shader, "mvp");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // Set shader value: ambient light level
    let ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, new Vector4( 0.2, 0.2, 0.2, 1 ), SHADER_UNIFORM_VEC4);

    // Create one light
    rli.CreateLight(rli.LIGHT_DIRECTIONAL, new Vector3( 50, 50, 0 ), rm.Vector3Zero(), WHITE, shader);

    // NOTE: We are assigning the intancing shader to material.shader
    // to be used on mesh drawing with DrawMeshInstanced()
    let matInstances = LoadMaterialDefault();
    matInstances.shader = shader;
    matInstances.maps[MATERIAL_MAP_DIFFUSE].color = RED;

    // Load default material (using raylib intenral default shader) for non-instanced mesh drawing
    // WARNING: Default shader enables vertex color attribute BUT GenMeshCube() does not generate vertex colors, so,
    // when drawing the color attribute is disabled and a default color value is provided as input for thevertex attribute
    let matDefault = LoadMaterialDefault();
    matDefault.maps[MATERIAL_MAP_DIFFUSE].color = BLUE;

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);

        // Update the light shader with the camera view position
        let cameraPos = [ camera.position.x, camera.position.y, camera.position.z ];
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                // Draw cube mesh with default material (BLUE)
                DrawMesh(cube, matDefault, rm.MatrixTranslate(-10, 0, 0));

                // Draw meshes instanced using material containing instancing shader (RED + lighting),
                // transforms[] for the instances should be provided, they are dynamically
                // updated in GPU every frame, so we can animate the different mesh instances
                DrawMeshInstanced(cube, matInstances, transforms, MAX_INSTANCES);

                // Draw cube mesh with default material (BLUE)
                DrawMesh(cube, matDefault, rm.MatrixTranslate(10, 0, 0));

            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
