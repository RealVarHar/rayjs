/*******************************************************************************************
*
*   raylib [text] example - raylib fonts loading
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   NOTE: raylib is distributed with some free to use fonts (even for commercial pourposes!)
*         To view details and credits for those fonts, check raylib license file
*
*   Example originally created with raylib 1.7, last time updated with raylib 3.7
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow, LoadFont, MeasureTextEx, Vector2, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, LIME, GOLD, RED, WindowShouldClose, BeginDrawing, ClearBackground, RAYWHITE, DrawText, DARKGRAY, DrawLine, DrawTextEx, EndDrawing, UnloadFont, CloseWindow, SetTargetFPS } from "rayjs:raylib";

const MAX_FONTS = 8;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - raylib fonts");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    let fonts = new Array(MAX_FONTS);

    fonts[0] = LoadFont("resources/fonts/alagard.png");
    fonts[1] = LoadFont("resources/fonts/pixelplay.png");
    fonts[2] = LoadFont("resources/fonts/mecha.png");
    fonts[3] = LoadFont("resources/fonts/setback.png");
    fonts[4] = LoadFont("resources/fonts/romulus.png");
    fonts[5] = LoadFont("resources/fonts/pixantiqua.png");
    fonts[6] = LoadFont("resources/fonts/alpha_beta.png");
    fonts[7] = LoadFont("resources/fonts/jupiter_crash.png");

    const messages = ["ALAGARD FONT designed by Hewett Tsoi",
                      "PIXELPLAY FONT designed by Aleksander Shevchuk",
                      "MECHA FONT designed by Captain Falcon",
                      "SETBACK FONT designed by Brian Kent (AEnigma)",
                      "ROMULUS FONT designed by Hewett Tsoi",
                      "PIXANTIQUA FONT designed by Gerhard Grossmann",
                      "ALPHA_BETA FONT designed by Brian Kent (AEnigma)",
                      "JUPITER_CRASH FONT designed by Brian Kent (AEnigma)" ];

    const spacings = [ 2, 4, 8, 4, 3, 4, 4, 1 ];

    let positions = new Array(MAX_FONTS);

    for (let i = 0; i < MAX_FONTS; i++) {
        positions[i] = new Vector2();
        positions[i].x = screenWidth/2 - MeasureTextEx(fonts[i], messages[i], fonts[i].baseSize*2, spacings[i]).x/2;
        positions[i].y = 60 + fonts[i].baseSize + 45*i;
    }

    // Small Y position corrections
    positions[3].y += 8;
    positions[4].y += 2;
    positions[7].y -= 8;

    let colors = [ MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, LIME, GOLD, RED ];

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

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

            DrawText("free fonts included with raylib", 250, 20, 20, DARKGRAY);
            DrawLine(220, 50, 590, 50, DARKGRAY);

            for (let i = 0; i < MAX_FONTS; i++) {
                DrawTextEx(fonts[i], messages[i], positions[i], fonts[i].baseSize*2, spacings[i], colors[i]);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // Fonts unloading
    for (let i = 0; i < MAX_FONTS; i++) UnloadFont(fonts[i]);

    CloseWindow();                 // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}