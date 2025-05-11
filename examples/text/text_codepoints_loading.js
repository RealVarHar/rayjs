/*******************************************************************************************
*
*   raylib [text] example - Codepoints loading
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 4.2, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BLACK,
    BeginDrawing, ClearBackground, CloseWindow, DrawRectangle,
    DrawRectangleLines,
    DrawText,
    DrawTextEx,
    DrawTexture,
    EndDrawing,
    GRAY,
    GREEN,
    GetScreenHeight,
    GetScreenWidth, InitWindow, IsKeyPressed, KEY_SPACE, LoadCodepoints, LoadFontEx,
    RAYWHITE,
    SetTargetFPS,
    SetTextLineSpacing, SetTextureFilter, TEXTURE_FILTER_BILINEAR, TextFormat, UnloadCodepoints,
    UnloadFont,
    Vector2, WindowShouldClose } from "rayjs:raylib";

// Text to be displayed, must be UTF-8 (save this code file as UTF-8)
// NOTE: It can contain all the required text for the game,
// this text will be scanned to get all the required codepoints
const text = "いろはにほへと　ちりぬるを\nわかよたれそ　つねならむ\nうゐのおくやま　けふこえて\nあさきゆめみし　ゑひもせす";

// Remove codepoint duplicates if requested
// WARNING: This process could be a bit slow if there text to process is very long
function CodepointRemoveDuplicates(codepoints, codepointCount, codepointsResultCount) {
    let codepointsNoDupsCount = codepointCount;
    let codepointsNoDups = structuredClone(codepoints);

    // Remove duplicates
    for (let i = 0; i < codepointsNoDupsCount; i++) {
        for (let j = i + 1; j < codepointsNoDupsCount; j++) {
            if (codepointsNoDups[i] == codepointsNoDups[j]) {
                for (let k = j; k < codepointsNoDupsCount; k++) codepointsNoDups[k] = codepointsNoDups[k + 1];

                codepointsNoDupsCount--;
                j--;
            }
        }
    }

    // NOTE: The size of codepointsNoDups is the same as original array but
    // only required positions are filled (codepointsNoDupsCount)

    codepointsResultCount[0] = codepointsNoDupsCount;
    return codepointsNoDups;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - codepoints loading");

    // Convert each utf-8 character into its
    // corresponding codepoint in the font file.
    let codepointCount = [0];
    let codepoints = LoadCodepoints(text, codepointCount);

    // Removed duplicate codepoints to generate smaller font atlas
    let codepointsNoDupsCount = [0];
    let codepointsNoDups = CodepointRemoveDuplicates(codepoints, codepointCount[0], codepointsNoDupsCount);
    UnloadCodepoints(codepoints);
    codepoints = undefined;

    // Load font containing all the provided codepoint glyphs
    // A texture font atlas is automatically generated
    let font = LoadFontEx("resources/DotGothic16-Regular.ttf", 36, codepointsNoDups, codepointsNoDupsCount[0]);

    // Set bilinear scale filter for better font scaling
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    SetTextLineSpacing(20);         // Set line spacing for multiline text (when line breaks are included '\n')

    // Free codepoints, atlas has already been generated
    codepointsNoDups = undefined;

    let showFontAtlas = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_SPACE)) showFontAtlas = !showFontAtlas;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangle(0, 0, GetScreenWidth(), 70, BLACK);
            DrawText(TextFormat("Total codepoints contained in provided text: %i", codepointCount), 10, 10, 20, GREEN);
            DrawText(TextFormat("Total codepoints required for font atlas (duplicates excluded): %i", codepointsNoDupsCount), 10, 40, 20, GREEN);

            if (showFontAtlas) {
                // Draw generated font texture atlas containing provided codepoints
                DrawTexture(font.texture, 150, 100, BLACK);
                DrawRectangleLines(150, 100, font.texture.width, font.texture.height, BLACK);
            } else {
                // Draw provided text with laoded font, containing all required codepoint glyphs
                DrawTextEx(font, text, new Vector2( 160, 110 ), 48, 5, BLACK);
            }

            DrawText("Press SPACE to toggle font atlas view!", 10, GetScreenHeight() - 30, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadFont(font);     // Unload font

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
