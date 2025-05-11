/*******************************************************************************************
*
*   raylib [textures] example - Mouse painting
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 3.0, last time updated with raylib 3.0
*
*   Example contributed by Chris Dill (@MysteriousSpace) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Chris Dill (@MysteriousSpace) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow,RAYWHITE, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN,
    SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN,
    LIGHTGRAY, GRAY, DARKGRAY, BLACK, Rectangle, LoadRenderTexture, BeginTextureMode, ClearBackground, EndTextureMode, SetTargetFPS, WindowShouldClose, GetMousePosition, IsKeyPressed, KEY_RIGHT, KEY_LEFT, CheckCollisionPointRec, IsMouseButtonPressed, MOUSE_BUTTON_LEFT, GetMouseWheelMove, KEY_C, IsMouseButtonDown, GetGestureDetected, GESTURE_DRAG, DrawCircle, MOUSE_BUTTON_RIGHT, IsMouseButtonReleased, LoadImageFromTexture, ImageFlipVertical, UnloadImage, ExportImage, BeginDrawing, DrawTextureRec, Vector2, WHITE, DrawCircleLines, GetMouseX, GetMouseY, DrawRectangle, GetScreenWidth, DrawLine, DrawRectangleLines, DrawRectangleRec, Fade, DrawRectangleLinesEx, DrawText, GetScreenHeight, EndDrawing, UnloadRenderTexture, CloseWindow, KEY_S } from "rayjs:raylib";


const MAX_COLORS_COUNT = 23;          // Number of colors available

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - mouse painting");

    // Colors to choose from
    let colors = [
        RAYWHITE, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN,
        SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN,
        LIGHTGRAY, GRAY, DARKGRAY, BLACK ];

    // Define colorsRecs data (for every rectangle)
    let colorsRecs = new Array(MAX_COLORS_COUNT);

    for (let i = 0; i < MAX_COLORS_COUNT; i++) {
        colorsRecs[i] = new Rectangle();
        colorsRecs[i].x = 10 + 30*i + 2*i;
        colorsRecs[i].y = 10;
        colorsRecs[i].width = 30;
        colorsRecs[i].height = 30;
    }

    let colorSelected = 0;
    let colorSelectedPrev = colorSelected;
    let colorMouseHover = 0;
    let brushSize = 20;
    let mouseWasPressed = false;

    let btnSaveRec = new Rectangle( 750, 10, 40, 30 );
    let btnSaveMouseHover = false;
    let showSaveMessage = false;
    let saveMessageCounter = 0;

    // Create a RenderTexture2D to use as a canvas
    let target = LoadRenderTexture(screenWidth, screenHeight);

    // Clear render texture before entering the game loop
    BeginTextureMode(target);
    ClearBackground(colors[0]);
    EndTextureMode();

    SetTargetFPS(120);              // Set our game to run at 120 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        let mousePos = GetMousePosition();

        // Move between colors with keys
        if (IsKeyPressed(KEY_RIGHT)) colorSelected++;
        else if (IsKeyPressed(KEY_LEFT)) colorSelected--;

        if (colorSelected >= MAX_COLORS_COUNT) colorSelected = MAX_COLORS_COUNT - 1;
        else if (colorSelected < 0) colorSelected = 0;

        // Choose color with mouse
        for (let i = 0; i < MAX_COLORS_COUNT; i++) {
            if (CheckCollisionPointRec(mousePos, colorsRecs[i])) {
                colorMouseHover = i;
                break;
            }
            else colorMouseHover = -1;
        }

        if ((colorMouseHover >= 0) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            colorSelected = colorMouseHover;
            colorSelectedPrev = colorSelected;
        }

        // Change brush size
        brushSize += GetMouseWheelMove()*5;
        if (brushSize < 2) brushSize = 2;
        if (brushSize > 50) brushSize = 50;

        if (IsKeyPressed(KEY_C)) {
            // Clear render texture to clear color
            BeginTextureMode(target);
            ClearBackground(colors[0]);
            EndTextureMode();
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || (GetGestureDetected() == GESTURE_DRAG)) {
            // Paint circle into render texture
            // NOTE: To avoid discontinuous circles, we could store
            // previous-next mouse points and just draw a line using brush size
            BeginTextureMode(target);
            if (mousePos.y > 50) DrawCircle(Math.floor(mousePos.x), Math.floor(mousePos.y), brushSize, colors[colorSelected]);
            EndTextureMode();
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            if (!mouseWasPressed) {
                colorSelectedPrev = colorSelected;
                colorSelected = 0;
            }

            mouseWasPressed = true;

            // Erase circle from render texture
            BeginTextureMode(target);
            if (mousePos.y > 50) DrawCircle(Math.floor(mousePos.x), Math.floor(mousePos.y), brushSize, colors[0]);
            EndTextureMode();
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && mouseWasPressed) {
            colorSelected = colorSelectedPrev;
            mouseWasPressed = false;
        }

        // Check mouse hover save button
        if(CheckCollisionPointRec(mousePos, btnSaveRec)) btnSaveMouseHover = true;
        else btnSaveMouseHover = false;

        // Image saving logic
        // NOTE: Saving painted texture to a default named image
        if ((btnSaveMouseHover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_S)) {
            let image = LoadImageFromTexture(target.texture);
            ImageFlipVertical(image);
            ExportImage(image, "my_amazing_texture_painting.png");
            UnloadImage(image);
            showSaveMessage = true;
        }

        if (showSaveMessage) {
            // On saving, show a full screen message for 2 seconds
            saveMessageCounter++;
            if (saveMessageCounter > 240) {
                showSaveMessage = false;
                saveMessageCounter = 0;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
        DrawTextureRec(target.texture, new Rectangle( 0, 0, target.texture.width, -target.texture.height ), new Vector2( 0, 0 ), WHITE);

        // Draw drawing circle for reference
        if (mousePos.y > 50) {
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) DrawCircleLines(Math.floor(mousePos.x), Math.floor(mousePos.y), brushSize, GRAY);
            else DrawCircle(GetMouseX(), GetMouseY(), brushSize, colors[colorSelected]);
        }

        // Draw top panel
        DrawRectangle(0, 0, GetScreenWidth(), 50, RAYWHITE);
        DrawLine(0, 50, GetScreenWidth(), 50, LIGHTGRAY);

        // Draw color selection rectangles
        for (let i = 0; i < MAX_COLORS_COUNT; i++) DrawRectangleRec(colorsRecs[i], colors[i]);
        DrawRectangleLines(10, 10, 30, 30, LIGHTGRAY);

        if (colorMouseHover >= 0) DrawRectangleRec(colorsRecs[colorMouseHover], Fade(WHITE, 0.6));

        DrawRectangleLinesEx(new Rectangle( colorsRecs[colorSelected].x - 2, colorsRecs[colorSelected].y - 2,
                             colorsRecs[colorSelected].width + 4, colorsRecs[colorSelected].height + 4 ), 2, BLACK);

        // Draw save image button
        DrawRectangleLinesEx(btnSaveRec, 2, btnSaveMouseHover ? RED : BLACK);
        DrawText("SAVE!", 755, 20, 10, btnSaveMouseHover ? RED : BLACK);

        // Draw save image message
        if (showSaveMessage) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8));
            DrawRectangle(0, 150, GetScreenWidth(), 80, BLACK);
            DrawText("IMAGE SAVED:  my_amazing_texture_painting.png", 150, 180, 20, RAYWHITE);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target);    // Unload render texture

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
