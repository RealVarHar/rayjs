/*******************************************************************************************
*
*   raylib [shaders] example - Postprocessing with custom uniform variable
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
*         on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
*         raylib comes with shaders ready for both versions, check raylib/shaders install folder
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {FLAG_MSAA_4X_HINT, InitWindow, SetConfigFlags,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadModel, LoadTexture, MATERIAL_MAP_DIFFUSE, LoadShader, TextFormat, GetShaderLocation, LoadRenderTexture, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_ORBITAL, GetMousePosition, SetShaderValue, SHADER_UNIFORM_VEC2, BeginTextureMode, ClearBackground, RAYWHITE, BeginMode3D, DrawModel, WHITE, DrawGrid, EndMode3D, DrawText, RED, EndTextureMode, BeginDrawing, BeginShaderMode, Rectangle, DrawTextureRec, EndShaderMode, DrawFPS, GRAY, Vector2, EndDrawing, UnloadShader, UnloadTexture, UnloadModel, UnloadRenderTexture, CloseWindow } from 'rayjs:raylib';

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - custom uniform variable");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 8, 8, 8 );    // Camera position
    camera.target = new Vector3( 0, 1.5, 0 );    // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;      // Camera projection type

    let model = LoadModel("resources/models/barracks.obj");               // Load OBJ model
    let texture = LoadTexture("resources/models/barracks_diffuse.png");   // Load model texture (diffuse map)
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;      // Set model diffuse texture

    let position = new Vector3( 0, 0, 0 );                                    // Set model position

    // Load postprocessing shader
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    let shader = LoadShader(null, TextFormat("resources/shaders/glsl%i/swirl.fs", GLSL_VERSION));

    // Get variable (uniform) location on the shader to connect with the program
    // NOTE: If uniform variable could not be found in the shader, function returns -1
    let swirlCenterLoc = GetShaderLocation(shader, "center");

    let swirlCenter = [ screenWidth/2, screenHeight/2 ];

    // Create a RenderTexture2D to be used for render to texture
    let target = LoadRenderTexture(screenWidth, screenHeight);

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);
        
        let mousePosition = GetMousePosition();

        swirlCenter[0] = mousePosition.x;
        swirlCenter[1] = screenHeight - mousePosition.y;

        // Send new value to the shader to be used on drawing
        SetShaderValue(shader, swirlCenterLoc, swirlCenter, SHADER_UNIFORM_VEC2);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginTextureMode(target);       // Enable drawing to texture
            ClearBackground(RAYWHITE);  // Clear texture background

            BeginMode3D(camera);        // Begin 3d mode drawing
                DrawModel(model, position, 0.5, WHITE);   // Draw 3d model with texture
                DrawGrid(10, 1);        // Draw a grid
            EndMode3D();                // End 3d mode drawing, returns to orthographic 2d mode

            DrawText("TEXT DRAWN IN RENDER TEXTURE", 200, 10, 30, RED);
        EndTextureMode();               // End drawing to texture (now we have a texture available for next passes)

        BeginDrawing();
            ClearBackground(RAYWHITE);  // Clear screen background

            // Enable shader using the custom uniform
            BeginShaderMode(shader);
                // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
                DrawTextureRec(target.texture, new Rectangle( 0, 0, target.texture.width, -target.texture.height ), new Vector2( 0, 0 ), WHITE);
            EndShaderMode();

            // Draw some 2d text over drawn texture
            DrawText("(c) Barracks 3D model by Alberto Cano", screenWidth - 220, screenHeight - 20, 10, GRAY);
            DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);               // Unload shader
    UnloadTexture(texture);             // Unload texture
    UnloadModel(model);                 // Unload model
    UnloadRenderTexture(target);        // Unload render texture

    CloseWindow();                      // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}