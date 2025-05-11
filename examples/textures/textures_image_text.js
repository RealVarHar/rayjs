/*******************************************************************************************
*
*   raylib [textures] example - Image text drawing using TTF generated font
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.8, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BLACK, BeginDrawing,
    ClearBackground,
    CloseWindow,
    DARKGRAY,
    DrawText,
    DrawTextEx,
    DrawTexture,
    DrawTextureV,
    EndDrawing, ImageDrawTextEx, InitWindow, IsKeyDown, KEY_SPACE, LoadFontEx, LoadImage, LoadTextureFromImage,
    RAYWHITE, RED,
    SetTargetFPS, UnloadFont, UnloadImage, UnloadTexture, Vector2, WHITE, WindowShouldClose } from 'rayjs:raylib';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - image text drawing");

    let parrots = LoadImage("resources/parrots.png"); // Load image in CPU memory (RAM)

    // TTF Font loading with custom generation parameters
    let font = LoadFontEx("resources/KAISG.ttf", 64, null, 0);

    // Draw over image using custom font
    ImageDrawTextEx(parrots, font, "[Parrots font drawing]", new Vector2( 20, 20 ), font.baseSize, 0, RED);

    let texture = LoadTextureFromImage(parrots);  // Image converted to texture, uploaded to GPU memory (VRAM)
    UnloadImage(parrots);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    let position = new Vector2( screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 20 );

    let showFont = false;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_SPACE)) showFont = true;
        else showFont = false;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (!showFont) {
                // Draw texture with text already drawn inside
                DrawTextureV(texture, position, WHITE);

                // Draw text directly using sprite font
                DrawTextEx(font, "[Parrots font drawing]", new Vector2(position.x + 20, position.y + 20 + 280 ), font.baseSize, 0, WHITE);
            }
            else DrawTexture(font.texture, screenWidth/2 - font.texture.width/2, 50, BLACK);

            DrawText("PRESS SPACE to SHOW FONT ATLAS USED", 290, 420, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);     // Texture unloading

    UnloadFont(font);           // Unload custom font

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}