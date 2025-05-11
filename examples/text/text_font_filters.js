/*******************************************************************************************
*
*   raylib [text] example - Font filters
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   NOTE: After font loading, font texture atlas filter could be configured for a softer
*   display of the font when scaling it to different sizes, that way, it's not required
*   to generate multiple fonts at multiple sizes (as long as the scaling is not very different)
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BLACK, BeginDrawing, ClearBackground, CloseWindow, DARKGRAY, DrawRectangle, DrawText, DrawTextEx,
    EndDrawing, GRAY, GenTextureMipmaps,
    GetMouseWheelMove, InitWindow,
    IsFileDropped,
    IsFileExtension,
    IsKeyDown,
    IsKeyPressed, KEY_LEFT, KEY_ONE,
    KEY_RIGHT,
    KEY_THREE,
    KEY_TWO, LIGHTGRAY, LoadDroppedFiles, LoadFontEx, MeasureTextEx, RAYWHITE, SetTargetFPS, SetTextureFilter,
    TEXTURE_FILTER_BILINEAR, TEXTURE_FILTER_POINT, TEXTURE_FILTER_TRILINEAR,
    TextFormat, UnloadFont, Vector2, WindowShouldClose } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - font filters");

    const msg = "Loaded Font";

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)

    // TTF Font loading with custom generation parameters
    let font = LoadFontEx("resources/KAISG.ttf", 96, null, 0);

    // Generate mipmap levels to use trilinear filtering
    // NOTE: On 2D drawing it won't be noticeable, it looks like FILTER_BILINEAR
    GenTextureMipmaps(font.texture);

    let fontSize = font.baseSize;
    let fontPosition = new Vector2( 40, screenHeight/2 - 80 );
    let textSize = new Vector2( 0, 0 );

    // Setup texture scaling filter
    SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
    let currentFontFilter = 0;      // TEXTURE_FILTER_POINT

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        fontSize += GetMouseWheelMove()*4;

        // Choose font texture filter method
        if (IsKeyPressed(KEY_ONE)) {
            SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
            currentFontFilter = 0;
        } else if (IsKeyPressed(KEY_TWO)) {
            SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
            currentFontFilter = 1;
        } else if (IsKeyPressed(KEY_THREE)) {
            // NOTE: Trilinear filter won't be noticed on 2D drawing
            SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);
            currentFontFilter = 2;
        }

        textSize = MeasureTextEx(font, msg, fontSize, 0);

        if (IsKeyDown(KEY_LEFT)) fontPosition.x -= 10;
        else if (IsKeyDown(KEY_RIGHT)) fontPosition.x += 10;

        // Load a dropped TTF file dynamically (at current fontSize)
        if (IsFileDropped()) {
            let droppedFiles = LoadDroppedFiles();

            // NOTE: We only support first ttf file dropped
            if (IsFileExtension(droppedFiles[0], ".ttf")) {
                UnloadFont(font);
                font = LoadFontEx(droppedFiles[0], Math.floor(fontSize), null, 0);
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Use mouse wheel to change font size", 20, 20, 10, GRAY);
            DrawText("Use KEY_RIGHT and KEY_LEFT to move text", 20, 40, 10, GRAY);
            DrawText("Use 1, 2, 3 to change texture filter", 20, 60, 10, GRAY);
            DrawText("Drop a new TTF font for dynamic loading", 20, 80, 10, DARKGRAY);

            DrawTextEx(font, msg, fontPosition, fontSize, 0, BLACK);

            // TODO: It seems texSize measurement is not accurate due to chars offsets...
            //DrawRectangleLines(fontPosition.x, fontPosition.y, textSize.x, textSize.y, RED);

            DrawRectangle(0, screenHeight - 80, screenWidth, 80, LIGHTGRAY);
            DrawText(TextFormat("Font size: %02.02f", fontSize), 20, screenHeight - 50, 10, DARKGRAY);
            DrawText(TextFormat("Text size: [%02.02f, %02.02f]", textSize.x, textSize.y), 20, screenHeight - 30, 10, DARKGRAY);
            DrawText("CURRENT TEXTURE FILTER:", 250, 400, 20, GRAY);

            if (currentFontFilter == 0) DrawText("POINT", 570, 400, 20, BLACK);
            else if (currentFontFilter == 1) DrawText("BILINEAR", 570, 400, 20, BLACK);
            else if (currentFontFilter == 2) DrawText("TRILINEAR", 570, 400, 20, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadFont(font);           // Font unloading

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}