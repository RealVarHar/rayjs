/*******************************************************************************************
*
*   raylib [shaders] example - Multiple sample2D with default batch system
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
*   Example originally created with raylib 3.5, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
import * as os from 'qjs:os';
import {BeginDrawing, BeginShaderMode, ClearBackground, CloseWindow, Color,
    DrawText,
    DrawTexture, EndDrawing, EndShaderMode, GenImageColor, GetScreenHeight, GetShaderLocation, InitWindow, IsKeyDown,
    KEY_LEFT, KEY_RIGHT, LoadShader, LoadTextureFromImage,
    RAYWHITE,
    SHADER_UNIFORM_FLOAT,
    SetShaderValue,
    SetShaderValueTexture,
    SetTargetFPS, TextFormat, UnloadImage, UnloadShader, UnloadTexture, WHITE, WindowShouldClose } from 'rayjs:raylib';

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

    InitWindow(screenWidth, screenHeight, "raylib - multiple sample2D");

    let imRed = GenImageColor(800, 450, new Color( 255, 0, 0, 255 ));
    let texRed = LoadTextureFromImage(imRed);
    UnloadImage(imRed);

    let imBlue = GenImageColor(800, 450, new Color( 0, 0, 255, 255 ));
    let texBlue = LoadTextureFromImage(imBlue);
    UnloadImage(imBlue);

    let shader = LoadShader(null, TextFormat("resources/shaders/glsl%i/color_mix.fs", GLSL_VERSION));

    // Get an additional sampler2D location to be enabled on drawing
    let texBlueLoc = GetShaderLocation(shader, "texture1");

    // Get shader uniform for divider
    let dividerLoc = GetShaderLocation(shader, "divider");
    let dividerValue = 0.5;

    SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {               // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) dividerValue += 0.01;
        else if (IsKeyDown(KEY_LEFT)) dividerValue -= 0.01;

        if (dividerValue < 0) dividerValue = 0;
        else if (dividerValue > 1) dividerValue = 1;

        SetShaderValue(shader, dividerLoc, dividerValue, SHADER_UNIFORM_FLOAT);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginShaderMode(shader);

                // WARNING: Additional samplers are enabled for all draw calls in the batch,
                // EndShaderMode() forces batch drawing and consequently resets active textures
                // to let other sampler2D to be activated on consequent drawings (if required)
                SetShaderValueTexture(shader, texBlueLoc, texBlue);

                // We are drawing texRed using default sampler2D texture0 but
                // an additional texture units is enabled for texBlue (sampler2D texture1)
                DrawTexture(texRed, 0, 0, WHITE);

            EndShaderMode();

            DrawText("Use KEY_LEFT/KEY_RIGHT to move texture mixing in shader!", 80, GetScreenHeight() - 40, 20, RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);       // Unload shader
    UnloadTexture(texRed);      // Unload texture
    UnloadTexture(texBlue);     // Unload texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}