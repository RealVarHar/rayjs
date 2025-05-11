/*******************************************************************************************
*
*   raylib [models] example - Draw some basic geometric shapes (cube, sphere, cylinder...)
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 1.0, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow, Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, SetTargetFPS, WindowShouldClose, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawCube, DrawCubeWires, RED, GOLD, MAROON, GREEN, DrawSphere, DrawSphereWires, LIME, DrawCylinder, DrawCylinderWires, SKYBLUE, DARKBLUE, BROWN, DrawCapsule, DrawCapsuleWires, PINK, VIOLET, PURPLE, DrawGrid, EndMode3D, DrawFPS, EndDrawing, CloseWindow } from 'rayjs:raylib';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - geometric shapes");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 0, 10, 10 );
    camera.target = new Vector3( 0, 0, 0 );
    camera.up = new Vector3( 0, 1, 0 );
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawCube(new Vector3(-4, 0, 2), 2, 5, 2, RED);
                DrawCubeWires(new Vector3(-4, 0, 2), 2, 5, 2, GOLD);
                DrawCubeWires(new Vector3(-4, 0, -2), 3, 6, 2, MAROON);

                DrawSphere(new Vector3(-1, 0, -2), 1, GREEN);
                DrawSphereWires(new Vector3(1, 0, 2), 2, 16, 16, LIME);

                DrawCylinder(new Vector3(4, 0, -2), 1, 2, 3, 4, SKYBLUE);
                DrawCylinderWires(new Vector3(4, 0, -2), 1, 2, 3, 4, DARKBLUE);
                DrawCylinderWires(new Vector3(4, -1, 2), 1, 1, 2, 6, BROWN);

                DrawCylinder(new Vector3(1, 0, -4), 0, 1.5, 3, 8, GOLD);
                DrawCylinderWires(new Vector3(1, 0, -4), 0, 1.5, 3, 8, PINK);

                DrawCapsule(new Vector3(-3, 1.5, -4), new Vector3(-4, -1, -4), 1.2, 8, 8, VIOLET);
                DrawCapsuleWires(new Vector3(-3, 1.5, -4), new Vector3(-4, -1, -4), 1.2, 8, 8, PURPLE);

                DrawGrid(10, 1);        // Draw a grid

            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}