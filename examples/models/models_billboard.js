/*******************************************************************************************
*
*   raylib [models] example - Drawing billboards
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 1.3, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadTexture, Rectangle, Vector2, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_ORBITAL, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawGrid, DrawBillboard, WHITE, DrawBillboardPro, EndMode3D, DrawFPS, EndDrawing, UnloadTexture, CloseWindow } from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - drawing billboards");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 5, 4, 5 );    // Camera position
    camera.target = new Vector3( 0, 2, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    let bill = LoadTexture("resources/billboard.png");    // Our billboard texture
    let billPositionStatic = new Vector3( 0, 2, 0 );          // Position of static billboard
    let billPositionRotating = new Vector3( 1, 2, 1 );        // Position of rotating billboard

    // Entire billboard texture, source is used to take a segment from a larger texture.
    let source = new Rectangle( 0, 0, bill.width, bill.height );

    // NOTE: Billboard locked on axis-Y
    let billUp = new Vector3( 0, 1, 0 );

    // Set the height of the rotating billboard to 1.0 with the aspect ratio fixed
    let size = new Vector2( source.width/source.height, 1 );

    // Rotate around origin
    // Here we choose to rotate around the image center
    let origin = rm.Vector2Scale(size, 0.5);

    // Distance is needed for the correct billboard draw order
    // Larger distance (further away from the camera) should be drawn prior to smaller distance.
    let distanceStatic;
    let distanceRotating;
    let rotation = 0;

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);

        rotation += 0.4;
        distanceStatic = rm.Vector3Distance(camera.position, billPositionStatic);
        distanceRotating = rm.Vector3Distance(camera.position, billPositionRotating);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawGrid(10, 1);        // Draw a grid

                // Draw order matters!
                if (distanceStatic > distanceRotating) {
                    DrawBillboard(camera, bill, billPositionStatic, 2, WHITE);
                    DrawBillboardPro(camera, bill, source, billPositionRotating, billUp, size, origin, rotation, WHITE);
                } else {
                    DrawBillboardPro(camera, bill, source, billPositionRotating, billUp, size, origin, rotation, WHITE);
                    DrawBillboard(camera, bill, billPositionStatic, 2, WHITE);
                }
                
            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(bill);        // Unload texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
