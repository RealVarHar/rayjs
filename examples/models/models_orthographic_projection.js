/*******************************************************************************************
*
*   raylib [models] example - Show the difference between perspective and orthographic projection
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 2.0, last time updated with raylib 3.7
*
*   Example contributed by Max Danielsson (@autious) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2025 Max Danielsson (@autious) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, SetTargetFPS, WindowShouldClose, IsKeyPressed, KEY_SPACE, CAMERA_ORTHOGRAPHIC, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawCube, RED, DrawCubeWires, GOLD, MAROON, DrawSphere, GREEN, DrawSphereWires, LIME, SKYBLUE, DARKBLUE, DrawCylinder, DrawCylinderWires, BROWN, PINK, DrawGrid, EndMode3D, DrawText, GetScreenHeight, DARKGRAY, BLACK, DrawFPS, EndDrawing, CloseWindow } from "rayjs:raylib";

const FOVY_PERSPECTIVE = 45;
const WIDTH_ORTHOGRAPHIC = 10;

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
    let camera = new Camera( new Vector3( 0, 10, 10 ), new Vector3( 0, 0, 0 ), new Vector3( 0, 1, 0 ), FOVY_PERSPECTIVE, CAMERA_PERSPECTIVE );

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_SPACE)) {
            if (camera.projection == CAMERA_PERSPECTIVE) {
                camera.fovy = WIDTH_ORTHOGRAPHIC;
                camera.projection = CAMERA_ORTHOGRAPHIC;
            } else {
                camera.fovy = FOVY_PERSPECTIVE;
                camera.projection = CAMERA_PERSPECTIVE;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawCube(new Vector3(-4, 0, 2), 2, 5, 2, RED);
                DrawCubeWires(new Vector3(-4, 0,  2), 2, 5, 2, GOLD);
                DrawCubeWires(new Vector3(-4, 0, -2), 3, 6, 2, MAROON);

                DrawSphere(new Vector3(-1, 0, -2), 1, GREEN);
                DrawSphereWires(new Vector3(1, 0, 2), 2, 16, 16, LIME);

                DrawCylinder(new Vector3(4, 0, -2), 1, 2, 3, 4, SKYBLUE);
                DrawCylinderWires(new Vector3(4, 0, -2), 1, 2, 3, 4, DARKBLUE);
                DrawCylinderWires(new Vector3(4.5, -1, 2), 1, 1, 2, 6, BROWN);

                DrawCylinder(new Vector3(1, 0, -4), 0, 1.5, 3, 8, GOLD);
                DrawCylinderWires(new Vector3(1, 0, -4), 0, 1.5, 3, 8, PINK);

                DrawGrid(10, 1);        // Draw a grid

            EndMode3D();

            DrawText("Press Spacebar to switch camera type", 10, GetScreenHeight() - 30, 20, DARKGRAY);

            if (camera.projection == CAMERA_ORTHOGRAPHIC) DrawText("ORTHOGRAPHIC", 10, 40, 20, BLACK);
            else if (camera.projection == CAMERA_PERSPECTIVE) DrawText("PERSPECTIVE", 10, 40, 20, BLACK);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
