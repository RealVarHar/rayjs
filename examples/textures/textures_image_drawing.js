/*******************************************************************************************
*
*   raylib [textures] example - Image loading and drawing on it
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 1.4, last time updated with raylib 1.4
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BeginDrawing, ClearBackground, CloseWindow, DARKGRAY, DrawRectangleLines, DrawText, DrawTexture,
    EndDrawing, ImageCrop, ImageDraw,
    ImageDrawCircleLines,
    ImageDrawPixel,
    ImageDrawRectangle, ImageDrawTextEx, ImageFlipHorizontal, ImageResize, InitWindow,
    LoadFont, LoadImage, LoadTextureFromImage, RAYWHITE, Rectangle,
    SetTargetFPS, UnloadFont, UnloadImage, UnloadTexture, Vector2, WHITE, WindowShouldClose } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - image drawing");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    let cat = LoadImage("resources/cat.png");             // Load image in CPU memory (RAM)
    ImageCrop(cat, new Rectangle( 100, 10, 280, 380 ));      // Crop an image piece
    ImageFlipHorizontal(cat);                              // Flip cropped image horizontally
    ImageResize(cat, 150, 200);                            // Resize flipped-cropped image

    let parrots = LoadImage("resources/parrots.png");     // Load image in CPU memory (RAM)

    // Draw one image over the other with a scaling of 1.5f
    ImageDraw(parrots, cat, new Rectangle( 0, 0, cat.width, cat.height ), new Rectangle( 30, 40, cat.width*1.5, cat.height*1.5 ), WHITE);
    ImageCrop(parrots, new Rectangle( 0, 50, parrots.width, parrots.height - 100 )); // Crop resulting image

    // Draw on the image with a few image draw methods
    ImageDrawPixel(parrots, 10, 10, RAYWHITE);
    ImageDrawCircleLines(parrots, 10, 10, 5, RAYWHITE);
    ImageDrawRectangle(parrots, 5, 20, 10, 10, RAYWHITE);

    UnloadImage(cat);       // Unload image from RAM

    // Load custom font for drawing on image
    let font = LoadFont("resources/custom_jupiter_crash.png");

    // Draw over image using custom font
    ImageDrawTextEx(parrots, font, "PARROTS & CAT", new Vector2( 300, 230 ), font.baseSize, -2, WHITE);

    UnloadFont(font);       // Unload custom font (already drawn used on image)

    let texture = LoadTextureFromImage(parrots);      // Image converted to texture, uploaded to GPU memory (VRAM)
    UnloadImage(parrots);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    SetTargetFPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, WHITE);
            DrawRectangleLines(screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, texture.width, texture.height, DARKGRAY);

            DrawText("We are drawing only one texture from various images composed!", 240, 350, 10, DARKGRAY);
            DrawText("Source images have been cropped, scaled, flipped and copied one over the other.", 190, 370, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
