/*******************************************************************************************
*
*   raylib [models] example - Models loading
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   NOTE: raylib supports multiple models file formats:
*
*     - OBJ  > Text file format. Must include vertex position-texcoords-normals information,
*              if files references some .mtl materials file, it will be loaded (or try to).
*     - GLTF > Text/binary file format. Includes lot of information and it could
*              also reference external files, raylib will try loading mesh and materials data.
*     - IQM  > Binary file format. Includes mesh vertex data but also animation data,
*              raylib can load .iqm animations.
*     - VOX  > Binary file format. MagikaVoxel mesh format:
*              https://github.com/ephtracy/voxel-model/blob/master/MagicaVoxel-file-format-vox.txt
*     - M3D  > Binary file format. Model 3D format:
*              https://bztsrc.gitlab.io/model3d
*
*   Example originally created with raylib 2.0, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow, Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadModel, LoadTexture, MATERIAL_MAP_DIFFUSE, GetMeshBoundingBox, DisableCursor, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_FIRST_PERSON, IsFileDropped, LoadDroppedFiles, IsFileExtension, UnloadModel, UnloadTexture, IsMouseButtonPressed, MOUSE_BUTTON_LEFT, GetRayCollisionBox, GetScreenToWorldRay, GetMousePosition, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawModel, WHITE, DrawGrid, DrawBoundingBox, GREEN, EndMode3D, DrawText, GetScreenHeight, DARKGRAY, GetScreenWidth, GRAY, DrawFPS, EndDrawing, CloseWindow } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - models loading");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 50, 50, 50 ); // Camera position
    camera.target = new Vector3( 0, 10, 0 );     // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    let model = LoadModel("resources/models/obj/castle.obj");                 // Load model
    let texture = LoadTexture("resources/models/obj/castle_diffuse.png"); // Load model texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;            // Set map diffuse texture

    let position = new Vector3( 0, 0, 0 );                    // Set model position

    let bounds = GetMeshBoundingBox(model.meshes[0]);   // Set model bounds

    // NOTE: bounds are calculated from the original size of the model,
    // if model is scaled on drawing, bounds must be also scaled

    let selected = false;          // Selected object flag

    DisableCursor();                // Limit cursor to relative movement inside the window

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_FIRST_PERSON);

        // Load new models/textures on drag&drop
        if (IsFileDropped()) {
            let droppedFiles = LoadDroppedFiles();

            if (droppedFiles.length == 1) {// Only support one file dropped
                if (IsFileExtension(droppedFiles[0], ".obj") ||
                    IsFileExtension(droppedFiles[0], ".gltf") ||
                    IsFileExtension(droppedFiles[0], ".glb") ||
                    IsFileExtension(droppedFiles[0], ".vox") ||
                    IsFileExtension(droppedFiles[0], ".iqm") ||
                    IsFileExtension(droppedFiles[0], ".m3d")) {      // Model file formats supported

                    UnloadModel(model);                         // Unload previous model
                    model = LoadModel(droppedFiles.paths[0]);   // Load new model
                    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set current map diffuse texture

                    bounds = GetMeshBoundingBox(model.meshes[0]);

                    // TODO: Move camera position from target enough distance to visualize model properly
                } else if (IsFileExtension(droppedFiles[0], ".png")) { // Texture file formats supported
                    // Unload current model texture and load new one
                    UnloadTexture(texture);
                    texture = LoadTexture(droppedFiles[0]);
                    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
                }
            }
        }

        // Select model on mouse click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // Check collision between ray and box
            if (GetRayCollisionBox(GetScreenToWorldRay(GetMousePosition(), camera), bounds).hit) selected = !selected;
            else selected = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawModel(model, position, 1, WHITE);        // Draw 3d model with texture

                DrawGrid(20, 10);         // Draw a grid

                if (selected) DrawBoundingBox(bounds, GREEN);   // Draw selection box

            EndMode3D();

            DrawText("Drag & drop model to load mesh/texture.", 10, GetScreenHeight() - 20, 10, DARKGRAY);
            if (selected) DrawText("MODEL SELECTED", GetScreenWidth() - 110, 10, 10, GREEN);

            DrawText("(c) Castle 3D model by Alberto Cano", screenWidth - 200, screenHeight - 20, 10, GRAY);

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