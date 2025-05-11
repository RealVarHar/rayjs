/*******************************************************************************************
*
*   raylib [textures] example - Background scrolling
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 2.0, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BeginDrawing, ClearBackground,
    CloseWindow, DrawText, DrawTextureEx, EndDrawing, GetColor, InitWindow, LoadTexture,
    RAYWHITE, RED, SetTargetFPS,
    UnloadTexture,
    Vector2, WHITE, WindowShouldClose } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - background scrolling");

    // NOTE: Be careful, background width must be equal or bigger than screen width
    // if not, texture should be draw more than two times for scrolling effect
    let background = LoadTexture("resources/cyberpunk_street_background.png");
    let midground = LoadTexture("resources/cyberpunk_street_midground.png");
    let foreground = LoadTexture("resources/cyberpunk_street_foreground.png");

    let scrollingBack = 0;
    let scrollingMid = 0;
    let scrollingFore = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        scrollingBack -= 0.1;
        scrollingMid -= 0.5;
        scrollingFore -= 1;

        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;
        if (scrollingFore <= -foreground.width*2) scrollingFore = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(0x052c46ff));

            // Draw background image twice
            // NOTE: Texture is scaled twice its size
            DrawTextureEx(background, new Vector2( scrollingBack, 20 ), 0, 2, WHITE);
            DrawTextureEx(background, new Vector2( background.width*2 + scrollingBack, 20 ), 0, 2, WHITE);

            // Draw midground image twice
            DrawTextureEx(midground, new Vector2( scrollingMid, 20 ), 0, 2, WHITE);
            DrawTextureEx(midground, new Vector2( midground.width*2 + scrollingMid, 20 ), 0, 2, WHITE);

            // Draw foreground image twice
            DrawTextureEx(foreground, new Vector2( scrollingFore, 70 ), 0, 2, WHITE);
            DrawTextureEx(foreground, new Vector2( foreground.width*2 + scrollingFore, 70 ), 0, 2, WHITE);

            DrawText("BACKGROUND SCROLLING & PARALLAX", 10, 10, 20, RED);
            DrawText("(c) Cyberpunk Street Environment by Luis Zuno (@ansimuz)", screenWidth - 330, screenHeight - 20, 10, RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);  // Unload background texture
    UnloadTexture(midground);   // Unload midground texture
    UnloadTexture(foreground);  // Unload foreground texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}