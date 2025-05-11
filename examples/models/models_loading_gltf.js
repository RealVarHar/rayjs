/*******************************************************************************************
*
*   raylib [models] example - loading gltf with animations
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   LIMITATIONS:
*     - Only supports 1 armature per file, and skips loading it if there are multiple armatures
*     - Only supports linear interpolation (default method in Blender when checked
*       "Always Sample Animations" when exporting a GLTF file)
*     - Only supports translation/rotation/scale animation channel.path,
*       weights not considered (i.e. morph targets)
*
*   Example originally created with raylib 3.7, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadModel, LoadModelAnimations, SetTargetFPS, WindowShouldClose, CAMERA_ORBITAL, UpdateCamera, IsMouseButtonPressed, MOUSE_BUTTON_RIGHT, MOUSE_BUTTON_LEFT, UpdateModelAnimation, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawModel, WHITE, DrawGrid, EndMode3D, DrawText, GRAY, TextFormat, GetScreenHeight, DARKGRAY, EndDrawing, UnloadModel, CloseWindow } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - loading gltf animations");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 6, 6, 6 );    // Camera position
    camera.target = new Vector3( 0, 2, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Load gltf model
    let model = LoadModel("resources/models/gltf/robot.glb");
    let position = new Vector3( 0, 0, 0 ); // Set model position
    
    // Load gltf model animations
    let animsCount = [0];
    let animIndex = 0;
    let animCurrentFrame = 0;
    let modelAnimations = LoadModelAnimations("resources/models/gltf/robot.glb", animsCount);

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);

        // Select current animation
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) animIndex = (animIndex + 1)%animsCount[0];
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) animIndex = (animIndex + animsCount[0] - 1)%animsCount[0];

        // Update model animation
        let anim = modelAnimations[animIndex];
        animCurrentFrame = (animCurrentFrame + 1)%anim.frameCount;
        UpdateModelAnimation(model, anim, animCurrentFrame);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawModel(model, position, 1, WHITE);    // Draw animated model
                DrawGrid(10, 1);
            EndMode3D();

            DrawText("Use the LEFT/RIGHT mouse buttons to switch animation", 10, 10, 20, GRAY);
            DrawText(TextFormat("Animation: %s", anim.name), 10, GetScreenHeight() - 20, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model);         // Unload model and meshes/material

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}



