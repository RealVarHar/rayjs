/*******************************************************************************************
*
*   raylib [models] example - Tesseract view
*
*   NOTE: This example only works on platforms that support drag & drop (Windows, Linux, OSX, Html5?)
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 5.6-dev, last time updated with raylib 5.6-dev
*
*   Example contributed by Timothy van der Valk (@arceryz) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024-2025 Timothy van der Valk (@arceryz) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, Vector4, SetTargetFPS, WindowShouldClose, GetTime, Vector2, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawSphere, RED, DrawLine3D, MAROON, EndMode3D, EndDrawing, CloseWindow } from 'rayjs:raylib';
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

    InitWindow(screenWidth, screenHeight, "raylib [models] example - tesseract view");
    
    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 4, 4, 4 );    // Camera position
    camera.target = new Vector3( 0, 0, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 0, 1 );          // Camera up vector (rotation towards target)
    camera.fovy = 50;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;      // Camera mode type

    // Find the coordinates by setting XYZW to +-1
    let tesseract = [
        new Vector4(  1,  1,  1, 1 ), new Vector4(  1,  1,  1, -1 ),
        new Vector4(  1,  1, -1, 1 ), new Vector4(  1,  1, -1, -1 ),
        new Vector4(  1, -1,  1, 1 ), new Vector4(  1, -1,  1, -1 ),
        new Vector4(  1, -1, -1, 1 ), new Vector4(  1, -1, -1, -1 ),
        new Vector4( -1,  1,  1, 1 ), new Vector4( -1,  1,  1, -1 ),
        new Vector4( -1,  1, -1, 1 ), new Vector4( -1,  1, -1, -1 ),
        new Vector4( -1, -1,  1, 1 ), new Vector4( -1, -1,  1, -1 ),
        new Vector4( -1, -1, -1, 1 ), new Vector4( -1, -1, -1, -1 )
    ];
    
    let rotation = 0;
    let transformed = new Array(16);//of Vector3
    let wValues = new Array(16);//of Vector3

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        rotation = DEG2RAD*45*GetTime();
        
        for (let i = 0; i < 16; i++) {
            let p = tesseract[i];

            // Rotate the XW part of the vector
            let rotXW = rm.Vector2Rotate(new Vector2( p.x, p.w ), rotation);
            p.x = rotXW.x;
            p.w = rotXW.y;

            // Projection from XYZW to XYZ from perspective point (0, 0, 0, 3)
            // NOTE: Trace a ray from (0, 0, 0, 3) > p and continue until W = 0
            const c = 3/(3 - p.w);
            p.x = c * p.x;
            p.y = c * p.y;
            p.z = c * p.z;

            // Split XYZ coordinate and W values later for drawing
            transformed[i] = new Vector3( p.x, p.y, p.z );
            wValues[i] = p.w;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            
            BeginMode3D(camera);
                for (let i = 0; i < 16; i++) {
                    // Draw spheres to indicate the W value
                    DrawSphere(transformed[i], Math.abs(wValues[i]*0.1), RED);

                    for (let j = 0; j < 16; j++) {
                        // Two lines are connected if they differ by 1 coordinate
                        // This way we don't have to keep an edge list
                        let v1 = tesseract[i];
                        let v2 = tesseract[j];
                        let diff = (v1.x == v2.x?1:0) + (v1.y == v2.y?1:0) + (v1.z == v2.z?1:0) + (v1.w == v2.w?1:0);

                        // Draw only differing by 1 coordinate and the lower index only (duplicate lines)
                        if (diff == 3 && i < j) DrawLine3D(transformed[i], transformed[j], MAROON);
                    }
                }
            EndMode3D();
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}