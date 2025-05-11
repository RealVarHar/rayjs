 /*******************************************************************************************
 *
 *   raylib [models] example - Cubicmap loading and drawing
 *
 *   Example originally created with raylib 1.8, last time updated with raylib 3.5
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2015-2023 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

 import {BeginDrawing, BeginMode3D, CAMERA_ORBITAL, CAMERA_PERSPECTIVE, Camera3D,
     ClearBackground,
     CloseWindow, DrawFPS, DrawModel, DrawRectangleLines, DrawText, DrawTextureEx, EndDrawing, EndMode3D,
     GRAY,
     GREEN, GenMeshCubicmap, InitWindow, LoadImage,
     LoadMaterialDefault,
     LoadModelFromMesh, LoadTexture, LoadTextureFromImage, MATERIAL_MAP_DIFFUSE, RAYWHITE, SetMaterialTexture,
     SetTargetFPS,
     UnloadImage, UnloadModel, UnloadTexture, UpdateCamera, Vector2, Vector3, WHITE, WindowShouldClose } from "rayjs:raylib";

{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - cubesmap loading and drawing");

    // Define the camera to look into our 3d world
    const position = new Vector3(16.0, 14.0, 16.0);     // Camera position
    const target = new Vector3(0.0, 0.0, 0.0);          // Camera looking at point
    const up = new Vector3(0.0, 1.0, 0.0);                  // Camera up vector (rotation towards target)
    const fovy = 45.0;                                  // Camera field-of-view Y
    const projection = CAMERA_PERSPECTIVE;              // Camera projection type
    const camera = new Camera3D(position, target, up, fovy, projection)

    let image = LoadImage("resources/cubicmap.png");      // Load cubicmap image (RAM)
    let cubicmap = LoadTextureFromImage(image);       // Convert image to texture to display (VRAM)

    const mesh = GenMeshCubicmap(image, new Vector3(1.0, 1.0, 1.0));
    const floor = LoadModelFromMesh(mesh);

    // NOTE: By default each cube is mapped to one part of texture atlas
    let texture = LoadTexture("resources/cubicmap_atlas.png");    // Load map texture

    //model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;    // Set map diffuse texture
    const mat = LoadMaterialDefault()
    SetMaterialTexture(mat, MATERIAL_MAP_DIFFUSE, texture);
    let materials = floor.materials;
    materials[0] = mat;
    floor.materials = materials;

    const mapPosition = new Vector3(-16.0, 0.0, -8.0);          // Set model position

    UnloadImage(image);  // Unload cubesmap image from RAM, already uploaded to VRAM

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawModel(floor, mapPosition, 1.0, WHITE);

            EndMode3D();

            DrawTextureEx(cubicmap, new Vector2(screenWidth - cubicmap.width*4.0 - 20, 20.0), 0.0, 4.0, WHITE);
            DrawRectangleLines(screenWidth - cubicmap.width*4 - 20, 20, cubicmap.width*4, cubicmap.height*4, GREEN);

            DrawText("cubicmap image used to", 658, 90, 10, GRAY);
            DrawText("generate map 3d model", 658, 104, 10, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(cubicmap);
    UnloadTexture(texture);
    UnloadModel(floor);

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}