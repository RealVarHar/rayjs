/*******************************************************************************************
*
*   raylib [models] example - Waving cubes
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.7
*
*   Example contributed by Codecat (@codecat) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Codecat (@codecat) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BeginDrawing, BeginMode3D, CAMERA_PERSPECTIVE, Camera3D,
    ClearBackground, CloseWindow, ColorFromHSV,
    DrawCube, DrawFPS, DrawGrid,
    EndDrawing, EndMode3D, GetTime, InitWindow, RAYWHITE, SetTargetFPS, Vector3, WindowShouldClose } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - waving cubes");

    // Initialize the camera
    let camera = new Camera3D();
    camera.position = new Vector3( 30, 20, 30 ); // Camera position
    camera.target = new Vector3( 0, 0, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 70;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Specify the amount of blocks in each direction
    const numBlocks = 15;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        let time = GetTime();

        // Calculate time scale for cube position and size
        let scale = (2.0 + Math.sin(time))*0.7;

        // Move camera around the scene
        let cameraTime = time*0.3;
        camera.position.x = Math.cos(cameraTime)*40;
        camera.position.z = Math.sin(cameraTime)*40;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawGrid(10, 5);

                for (let x = 0; x < numBlocks; x++) {
                    for (let y = 0; y < numBlocks; y++) {
                        for (let z = 0; z < numBlocks; z++) {
                            // Scale of the blocks depends on x/y/z positions
                            let blockScale = (x + y + z)/30;

                            // Scatter makes the waving effect by adding blockScale over time
                            let scatter = Math.sin(blockScale*20 + time*4);

                            // Calculate the cube position
                            let cubePos = new Vector3(
                                (x - numBlocks/2)*(scale*3) + scatter,
                                (y - numBlocks/2)*(scale*2) + scatter,
                                (z - numBlocks/2)*(scale*3) + scatter
                            );

                            // Pick a color with a hue depending on cube position for the rainbow color effect
                            // NOTE: This function is quite costly to be done per cube and frame, 
                            // pre-catching the results into a separate array could improve performance
                            let cubeColor = ColorFromHSV((((x + y + z)*18)%360), 0.75, 0.9);

                            // Calculate cube size
                            let cubeSize = (2.4 - scale)*blockScale;

                            // And finally, draw the cube!
                            DrawCube(cubePos, cubeSize, cubeSize, cubeSize, cubeColor);
                        }
                    }
                }

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
