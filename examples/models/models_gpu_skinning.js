/*******************************************************************************************
*
*   raylib [core] example - Doing skinning on the gpu using a vertex shader
*
*   Example complexity rating: [★★★☆] 3/4
* 
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by Daniel Holden (@orangeduck) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024-2025 Daniel Holden (@orangeduck)
* 
*   Note: Due to limitations in the Apple OpenGL driver, this feature does not work on MacOS
*
********************************************************************************************/

import * as os from 'qjs:os';
import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadModel, LoadShader, TextFormat, LoadModelAnimations, DisableCursor, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_THIRD_PERSON, IsKeyPressed, KEY_T, KEY_G, UpdateModelAnimationBones, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawMesh, DrawGrid, EndMode3D, DrawText, GRAY, EndDrawing, UnloadModelAnimations, UnloadModel, UnloadShader, CloseWindow } from 'rayjs:raylib';
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

    InitWindow(screenWidth, screenHeight, "raylib [models] example - GPU skinning");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 5, 5, 5 ); // Camera position
    camera.target = new Vector3( 0, 2, 0 );  // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );      // Camera up vector (rotation towards target)
    camera.fovy = 45;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;         // Camera projection type

    // Load gltf model
    let characterModel = LoadModel("resources/models/gltf/greenman.glb"); // Load character model
    
    // Load skinning shader
    let skinningShader = LoadShader(TextFormat("resources/shaders/glsl%i/skinning.vs", GLSL_VERSION), TextFormat("resources/shaders/glsl%i/skinning.fs", GLSL_VERSION));
    
    characterModel.materials[1].shader = skinningShader;
    
    // Load gltf model animations
    let animsCount = [0];
    let animIndex = 0;
    let animCurrentFrame = 0;
    let modelAnimations = LoadModelAnimations("resources/models/gltf/greenman.glb", animsCount);

    let position = new Vector3( 0, 0, 0 ); // Set model position

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_THIRD_PERSON);
        
        // Select current animation
        if (IsKeyPressed(KEY_T)) animIndex = (animIndex + 1)%animsCount[0];
        else if (IsKeyPressed(KEY_G)) animIndex = (animIndex + animsCount[0] - 1)%animsCount[0];

        // Update model animation
        let anim = modelAnimations[animIndex];
        animCurrentFrame = (animCurrentFrame + 1)%anim.frameCount;
        characterModel.transform = rm.MatrixTranslate(position.x, position.y, position.z);
        UpdateModelAnimationBones(characterModel, anim, animCurrentFrame);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            
                // Draw character mesh, pose calculation is done in shader (GPU skinning)
                DrawMesh(characterModel.meshes[0], characterModel.materials[1], characterModel.transform);

                DrawGrid(10, 1);
                
            EndMode3D();

            DrawText("Use the T/G to switch animation", 10, 10, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModelAnimations(modelAnimations, animsCount[0]); // Unload model animation
    UnloadModel(characterModel);    // Unload model and meshes/material
    UnloadShader(skinningShader);   // Unload GPU skinning shader
    
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}