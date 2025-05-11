/*******************************************************************************************
*
*   raylib [core] example - World to screen
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.4
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing, BeginMode3D, BLACK, CAMERA_PERSPECTIVE, CAMERA_THIRD_PERSON, ClearBackground, CloseWindow, DisableCursor, DrawCube, DrawCubeWires, DrawGrid, DrawText, EndDrawing, EndMode3D, GetWorldToScreen, GRAY, InitWindow, LIME, MAROON, MeasureText, RAYWHITE, RED, SetTargetFPS, TextFormat, UpdateCamera, Vector2, Vector3, WindowShouldClose, Camera3D as Camera
} from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - core world screen");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 10, 10, 10 ); // Camera position
    camera.target = new Vector3( 0, 0, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    let cubePosition = new Vector3( 0, 0, 0 );
    let cubeScreenPosition = new Vector2( 0, 0 );

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_THIRD_PERSON);

        // Calculate cube screen space position (with a little offset to be in top)
        cubeScreenPosition = GetWorldToScreen(new Vector3(cubePosition.x, cubePosition.y + 2.5, cubePosition.z), camera);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawCube(cubePosition, 2, 2, 2, RED);
                DrawCubeWires(cubePosition, 2, 2, 2, MAROON);

                DrawGrid(10, 1);

            EndMode3D();

            DrawText("Enemy: 100 / 100", Math.floor(cubeScreenPosition.x) - MeasureText("Enemy: 100/100", 20)/2, Math.floor(cubeScreenPosition.y), 20, BLACK);
            
            DrawText(TextFormat("Cube position in screen space coordinates: [%i, %i]", Math.floor(cubeScreenPosition.x), Math.floor(cubeScreenPosition.y)), 10, 10, 20, LIME);
            DrawText("Text 2d should be always on top of the cube", 10, 40, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}