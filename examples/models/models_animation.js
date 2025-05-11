/*******************************************************************************************
*
*   raylib [models] example - Load 3d model with animations and play them
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.5
*
*   Example contributed by Culacant (@culacant) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Culacant (@culacant) and Ramon Santamaria (@raysan5)
*
********************************************************************************************
*
*   NOTE: To import a model from blender, make sure it is not posed, the vertices need to be
*         in the same position as they would be in edit mode and the scale of your models is 
*         set to 0. Scaling can be done from the export menu.
*
********************************************************************************************/

import { InitWindow, Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadModel, LoadTexture, SetMaterialTexture, MATERIAL_MAP_DIFFUSE, LoadModelAnimations, DisableCursor, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_FIRST_PERSON, IsKeyDown, KEY_SPACE, UpdateModelAnimation, BeginDrawing, ClearBackground, BeginMode3D, DrawModelEx, RAYWHITE, DrawCube, DrawGrid, EndMode3D, DrawText, EndDrawing, UnloadTexture, UnloadModelAnimations, UnloadModel, CloseWindow, MAROON, GRAY, RED, WHITE } from 'rayjs:raylib';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - model animation");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 10, 10, 10 ); // Camera position
    camera.target = new Vector3( 0, 0, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    let model = LoadModel("resources/models/iqm/guy.iqm");                    // Load the animated model mesh and basic data
    let texture = LoadTexture("resources/models/iqm/guytex.png");         // Load model texture and set material
    SetMaterialTexture(model.materials[0], MATERIAL_MAP_DIFFUSE, texture);     // Set model material map texture

    let position = new Vector3( 0, 0, 0 );            // Set model position

    // Load animation data
    let animsCount = [0];
    let anims = LoadModelAnimations("resources/models/iqm/guyanim.iqm", animsCount);
    let animFrameCounter = 0;

    DisableCursor();                    // Catch cursor
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_FIRST_PERSON);

        // Play animation when spacebar is held down
        if (IsKeyDown(KEY_SPACE)) {
            animFrameCounter++;
            UpdateModelAnimation(model, anims[0], animFrameCounter);
            if (animFrameCounter >= anims[0].frameCount) animFrameCounter = 0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawModelEx(model, position, new Vector3( 1, 0, 0 ), -90, new Vector3( 1, 1, 1 ), WHITE);

                for (let i = 0; i < model.boneCount; i++) {
                    DrawCube(anims[0].framePoses[animFrameCounter][i].translation, 0.2, 0.2, 0.2, RED);
                }

                DrawGrid(10, 1);         // Draw a grid

            EndMode3D();

            DrawText("PRESS SPACE to PLAY MODEL ANIMATION", 10, 10, 20, MAROON);
            DrawText("(c) Guy IQM 3D model by @culacant", screenWidth - 200, screenHeight - 20, 10, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);                     // Unload texture
    UnloadModelAnimations(anims, animsCount[0]);   // Unload model animations data
    UnloadModel(model);                         // Unload model

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
