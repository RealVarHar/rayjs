/*******************************************************************************************
*
*   raylib [shaders] example - Simple shader mask
*
*   Example complexity rating: [★★☆☆] 2/4
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
********************************************************************************************
*
*   After a model is loaded it has a default material, this material can be
*   modified in place rather than creating one from scratch...
*   While all of the maps have particular names, they can be used for any purpose
*   except for three maps that are applied as cubic maps (see below)
*
********************************************************************************************/

import * as os from 'qjs:os';
import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, GenMeshTorus, LoadModelFromMesh, GenMeshCube, GenMeshSphere, LoadShader, TextFormat, LoadTexture, MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_EMISSION, SHADER_LOC_MAP_EMISSION, GetShaderLocation, DisableCursor, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_FIRST_PERSON, SetShaderValue, SHADER_UNIFORM_INT, BeginDrawing, ClearBackground, DARKBLUE, BeginMode3D, DrawModel, DrawModelEx, WHITE, DrawGrid, EndMode3D, DrawRectangle, MeasureText, BLUE, DrawText, DrawFPS, EndDrawing, UnloadModel, UnloadTexture, UnloadShader, CloseWindow } from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';

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

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - simple shader mask");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 0, 1, 2 );    // Camera position
    camera.target = new Vector3( 0, 0, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;      // Camera projection type

    // Define our three models to show the shader on
    let torus = GenMeshTorus(0.3, 1, 16, 32);
    let model1 = LoadModelFromMesh(torus);

    let cube = GenMeshCube(0.8,0.8,0.8);
    let model2 = LoadModelFromMesh(cube);

    // Generate model to be shaded just to see the gaps in the other two
    let sphere = GenMeshSphere(1, 16, 16);
    let model3 = LoadModelFromMesh(sphere);

    // Load the shader
    let shader = LoadShader(null, TextFormat("resources/shaders/glsl%i/mask.fs", GLSL_VERSION));

    // Load and apply the diffuse texture (colour map)
    let texDiffuse = LoadTexture("resources/plasma.png");
    model1.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texDiffuse;
    model2.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texDiffuse;

    // Using MATERIAL_MAP_EMISSION as a spare slot to use for 2nd texture
    // NOTE: Don't use MATERIAL_MAP_IRRADIANCE, MATERIAL_MAP_PREFILTER or  MATERIAL_MAP_CUBEMAP as they are bound as cube maps
    let texMask = LoadTexture("resources/mask.png");
    model1.materials[0].maps[MATERIAL_MAP_EMISSION].texture = texMask;
    model2.materials[0].maps[MATERIAL_MAP_EMISSION].texture = texMask;
    shader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(shader, "mask");

    // Frame is incremented each frame to animate the shader
    let shaderFrame = GetShaderLocation(shader, "frame");

    // Apply the shader to the two models
    model1.materials[0].shader = shader;
    model2.materials[0].shader = shader;

    let framesCounter = 0;
    let rotation = new Vector3();           // Model rotation angles

    DisableCursor();                    // Limit cursor to relative movement inside the window
    SetTargetFPS(60);                   // Set  to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_FIRST_PERSON);
        
        framesCounter++;
        rotation.x += 0.01;
        rotation.y += 0.005;
        rotation.z -= 0.0025;

        // Send frames counter to shader for animation
        SetShaderValue(shader, shaderFrame, framesCounter, SHADER_UNIFORM_INT);

        // Rotate one of the models
        model1.transform = rm.MatrixRotateXYZ(rotation);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKBLUE);

            BeginMode3D(camera);

                DrawModel(model1, new Vector3( 0.5, 0, 0 ), 1, WHITE);
                DrawModelEx(model2, new Vector3( -0.5, 0, 0 ), new Vector3( 1, 1, 0 ), 50, new Vector3( 1, 1, 1 ), WHITE);
                DrawModel(model3,new Vector3( 0, 0, -1.5 ), 1, WHITE);
                DrawGrid(10, 1.0);        // Draw a grid

            EndMode3D();

            DrawRectangle(16, 698, MeasureText(TextFormat("Frame: %i", framesCounter), 20) + 8, 42, BLUE);
            DrawText(TextFormat("Frame: %i", framesCounter), 20, 700, 20, WHITE);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model1);
    UnloadModel(model2);
    UnloadModel(model3);

    UnloadTexture(texDiffuse);  // Unload default diffuse texture
    UnloadTexture(texMask);     // Unload texture mask

    UnloadShader(shader);       // Unload shader

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
