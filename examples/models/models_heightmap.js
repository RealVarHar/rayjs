/*******************************************************************************************
*
*   raylib [models] example - Heightmap loading and drawing
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 1.8, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadImage, LoadTextureFromImage, GenMeshHeightmap, LoadModelFromMesh, MATERIAL_MAP_DIFFUSE, UnloadImage, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_ORBITAL, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawModel, RED, DrawGrid, EndMode3D, DrawTexture, WHITE, DrawRectangleLines, GREEN, DrawFPS, EndDrawing, UnloadTexture, UnloadModel, CloseWindow } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - heightmap loading and drawing");

    // Define our custom camera to look into our 3d world
    const camera = new Camera();
    camera.position = new Vector3( 18, 21, 18 );     // Camera position
    camera.target = new Vector3( 0, 0, 0 );          // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );              // Camera up vector (rotation towards target)
    camera.fovy = 45;                                    // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                 // Camera projection type

    let image = LoadImage("resources/heightmap.png");     // Load heightmap image (RAM)
    let texture = LoadTextureFromImage(image);        // Convert image to texture (VRAM)

    let mesh = GenMeshHeightmap(image, new Vector3( 16, 8, 16 )); // Generate heightmap mesh (RAM and VRAM)
    let model = LoadModelFromMesh(mesh);                  // Load model from generated mesh

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set map diffuse texture
    let mapPosition = new Vector3( -8, 0, -8 );           // Define model position

    UnloadImage(image);             // Unload heightmap image from RAM, already uploaded to VRAM

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawModel(model, mapPosition, 1, RED);

                DrawGrid(20, 1);

            EndMode3D();

            DrawTexture(texture, screenWidth - texture.width - 20, 20, WHITE);
            DrawRectangleLines(screenWidth - texture.width - 20, 20, texture.width, texture.height, GREEN);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);     // Unload texture
    UnloadModel(model);         // Unload model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}