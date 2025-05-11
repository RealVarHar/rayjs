/*******************************************************************************************
*
*   raylib [textures] example - Retrive image channel (mask)
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 5.1-dev, last time updated with raylib 5.1-dev
*
*   Example contributed by Bruno Cabral (@brccabral) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024-2025 Bruno Cabral (@brccabral) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BLUE, BeginDrawing,
    CloseWindow,
    DrawTexture,
    DrawTexturePro,
    EndDrawing,
    GREEN, GenImageChecked, ImageAlphaMask, ImageFromChannel, InitWindow, LoadImage, LoadTextureFromImage, ORANGE,
    RED,
    Rectangle,
    SetTargetFPS,
    UnloadImage, UnloadTexture, Vector2, WHITE, WindowShouldClose, YELLOW } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - extract channel from image");

    let fudesumiImage = LoadImage("resources/fudesumi.png");

    let imageAlpha = ImageFromChannel(fudesumiImage, 3);
    ImageAlphaMask(imageAlpha, imageAlpha);

    let imageRed = ImageFromChannel(fudesumiImage, 0);
    ImageAlphaMask(imageRed, imageAlpha);

    let imageGreen = ImageFromChannel(fudesumiImage, 1);
    ImageAlphaMask(imageGreen, imageAlpha);

    let imageBlue = ImageFromChannel(fudesumiImage, 2);
    ImageAlphaMask(imageBlue, imageAlpha);

    let backgroundImage = GenImageChecked(screenWidth, screenHeight, screenWidth/20, screenHeight/20, ORANGE, YELLOW);

    let fudesumiTexture = LoadTextureFromImage(fudesumiImage);
    let textureAlpha = LoadTextureFromImage(imageAlpha);
    let textureRed = LoadTextureFromImage(imageRed);
    let textureGreen = LoadTextureFromImage(imageGreen);
    let textureBlue = LoadTextureFromImage(imageBlue);
    let backgroundTexture = LoadTextureFromImage(backgroundImage);

    UnloadImage(fudesumiImage);
    UnloadImage(imageAlpha);
    UnloadImage(imageRed);
    UnloadImage(imageGreen);
    UnloadImage(imageBlue);
    UnloadImage(backgroundImage);

    let fudesumiRec = new Rectangle(0, 0, fudesumiImage.width, fudesumiImage.height);

    let fudesumiPos = new Rectangle(50, 10, fudesumiImage.width*0.8, fudesumiImage.height*0.8);
    let redPos = new Rectangle( 410, 10, fudesumiPos.width / 2, fudesumiPos.height / 2 );
    let greenPos = new Rectangle( 600, 10, fudesumiPos.width / 2, fudesumiPos.height / 2 );
    let bluePos = new Rectangle( 410, 230, fudesumiPos.width / 2, fudesumiPos.height / 2 );
    let alphaPos = new Rectangle( 600, 230, fudesumiPos.width / 2, fudesumiPos.height / 2 );

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Draw
        //----------------------------------------------------------------------------------
        // TODO...
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            DrawTexture(backgroundTexture, 0, 0, WHITE);
            DrawTexturePro(fudesumiTexture, fudesumiRec, fudesumiPos, new Vector2(0, 0), 0, WHITE);

            DrawTexturePro(textureRed, fudesumiRec, redPos, new Vector2(0, 0), 0, RED);
            DrawTexturePro(textureGreen, fudesumiRec, greenPos, new Vector2(0, 0), 0, GREEN);
            DrawTexturePro(textureBlue, fudesumiRec, bluePos, new Vector2(0, 0), 0, BLUE);
            DrawTexturePro(textureAlpha, fudesumiRec, alphaPos, new Vector2(0, 0), 0, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(backgroundTexture);
    UnloadTexture(fudesumiTexture);
    UnloadTexture(textureRed);
    UnloadTexture(textureGreen);
    UnloadTexture(textureBlue);
    UnloadTexture(textureAlpha);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
