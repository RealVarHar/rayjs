/*******************************************************************************************
*
*   raylib [shapes] example - Colors palette
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.0, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow,DARKGRAY, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN,
    GRAY, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, PINK, YELLOW,
    GREEN, SKYBLUE, PURPLE, BEIGE, Rectangle, Vector2, SetTargetFPS, WindowShouldClose, GetMousePosition, CheckCollisionPointRec, BeginDrawing, ClearBackground, BLACK, GetScreenWidth, GetScreenHeight, RAYWHITE, DrawText, IsKeyDown, DrawRectangleRec, Fade, KEY_SPACE, DrawRectangle, DrawRectangleLinesEx, MeasureText, EndDrawing, CloseWindow } from "rayjs:raylib";

const MAX_COLORS_COUNT = 21;          // Number of colors available

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - colors palette");

    let colors = [
        DARKGRAY, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN,
        GRAY, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, PINK, YELLOW,
        GREEN, SKYBLUE, PURPLE, BEIGE ];

    const colorNames = [
        "DARKGRAY", "MAROON", "ORANGE", "DARKGREEN", "DARKBLUE", "DARKPURPLE",
        "DARKBROWN", "GRAY", "RED", "GOLD", "LIME", "BLUE", "VIOLET", "BROWN",
        "LIGHTGRAY", "PINK", "YELLOW", "GREEN", "SKYBLUE", "PURPLE", "BEIGE" ];

    let colorsRecs = new Array(MAX_COLORS_COUNT);     // Rectangles array

    // Fills colorsRecs data (for every rectangle)
    for (let i = 0; i < MAX_COLORS_COUNT; i++) {
        colorsRecs[i] = new Rectangle();
        colorsRecs[i].x = 20 + 100 *(i%7) + 10 *(i%7);
        colorsRecs[i].y = 80 + 100 *(i/7) + 10 *(i/7);
        colorsRecs[i].width = 100;
        colorsRecs[i].height = 100;
    }

    let colorState = new Array(MAX_COLORS_COUNT);           // Color state: 0-DEFAULT, 1-MOUSE_HOVER

    let mousePoint = new Vector2( 0, 0 );

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        mousePoint = GetMousePosition();

        for (let i = 0; i < MAX_COLORS_COUNT; i++) {
            if (CheckCollisionPointRec(mousePoint, colorsRecs[i])) colorState[i] = 1;
            else colorState[i] = 0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("raylib colors palette", 28, 42, 20, BLACK);
            DrawText("press SPACE to see all colors", GetScreenWidth() - 180, GetScreenHeight() - 40, 10, GRAY);

            for (let i = 0; i < MAX_COLORS_COUNT; i++) {   // Draw all rectangles
                DrawRectangleRec(colorsRecs[i], Fade(colors[i], colorState[i]? 0.6 : 1));

                if (IsKeyDown(KEY_SPACE) || colorState[i]) {
                    DrawRectangle(Math.floor(colorsRecs[i].x), Math.floor(colorsRecs[i].y + colorsRecs[i].height - 26), Math.floor(colorsRecs[i].width), 20, BLACK);
                    DrawRectangleLinesEx(colorsRecs[i], 6, Fade(BLACK, 0.3));
                    DrawText(colorNames[i], Math.floor(colorsRecs[i].x + colorsRecs[i].width - MeasureText(colorNames[i], 10) - 12),
                        Math.floor(colorsRecs[i].y + colorsRecs[i].height - 20), 10, colors[i]);
                }
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}