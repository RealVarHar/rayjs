/*******************************************************************************************
*
*   raylib [models] example - Plane rotations (yaw, pitch, roll)
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.8, last time updated with raylib 4.0
*
*   Example contributed by Berni (@Berni8k) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2025 Berni (@Berni8k) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadModel, LoadTexture, MATERIAL_MAP_DIFFUSE, SetTargetFPS, WindowShouldClose, IsKeyDown, KEY_DOWN, KEY_UP, KEY_S, KEY_A, KEY_LEFT, KEY_RIGHT, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawModel, DrawGrid, WHITE, EndMode3D, DrawRectangle, Fade, GREEN, DrawRectangleLines, DARKGREEN, DrawText, DARKGRAY, EndDrawing, UnloadModel, UnloadTexture, CloseWindow } from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    const DEG2RAD = Math.PI/180;

    //SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "raylib [models] example - plane rotations (yaw, pitch, roll)");

    let camera = new Camera();
    camera.position = new Vector3( 0, 50, -120 );// Camera position perspective
    camera.target = new Vector3( 0, 0, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 30;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;      // Camera type

    let model = LoadModel("resources/models/obj/plane.obj");              // Load model
    let texture = LoadTexture("resources/models/obj/plane_diffuse.png");  // Load model texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;      // Set map diffuse texture

    let pitch = 0;
    let roll = 0;
    let yaw = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Plane pitch (x-axis) controls
        if (IsKeyDown(KEY_DOWN)) pitch += 0.6;
        else if (IsKeyDown(KEY_UP)) pitch -= 0.6;
        else {
            if (pitch > 0.3) pitch -= 0.3;
            else if (pitch < -0.3) pitch += 0.3;
        }

        // Plane yaw (y-axis) controls
        if (IsKeyDown(KEY_S)) yaw -= 1;
        else if (IsKeyDown(KEY_A)) yaw += 1;
        else {
            if (yaw > 0) yaw -= 0.5;
            else if (yaw < 0) yaw += 0.5;
        }

        // Plane roll (z-axis) controls
        if (IsKeyDown(KEY_LEFT)) roll -= 1;
        else if (IsKeyDown(KEY_RIGHT)) roll += 1;
        else {
            if (roll > 0) roll -= 0.5;
            else if (roll < 0) roll += 0.5;
        }

        // Tranformation matrix for rotations
        model.transform = rm.MatrixRotateXYZ( new Vector3( DEG2RAD*pitch, DEG2RAD*yaw, DEG2RAD*roll ));
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw 3D model (recomended to draw 3D always before 2D)
            BeginMode3D(camera);

                DrawModel(model, new Vector3( 0, -8, 0 ), 1, WHITE);   // Draw 3d model with texture
                DrawGrid(10, 10);

            EndMode3D();

            // Draw controls info
            DrawRectangle(30, 370, 260, 70, Fade(GREEN, 0.5));
            DrawRectangleLines(30, 370, 260, 70, Fade(DARKGREEN, 0.5));
            DrawText("Pitch controlled with: KEY_UP / KEY_DOWN", 40, 380, 10, DARKGRAY);
            DrawText("Roll controlled with: KEY_LEFT / KEY_RIGHT", 40, 400, 10, DARKGRAY);
            DrawText("Yaw controlled with: KEY_A / KEY_S", 40, 420, 10, DARKGRAY);

            DrawText("(c) WWI Plane Model created by GiaHanLam", screenWidth - 240, screenHeight - 20, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model);     // Unload model data
    UnloadTexture(texture); // Unload texture data

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
