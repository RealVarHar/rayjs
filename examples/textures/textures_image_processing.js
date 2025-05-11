/*******************************************************************************************
*
*   raylib [textures] example - Image processing
*
*   Example complexity rating: [★★★☆] 3/4
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 1.4, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {CheckCollisionPointRec,
    GetMousePosition, ImageCopy, ImageFormat, InitWindow,
    IsMouseButtonReleased, LoadImage, LoadTextureFromImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
    Rectangle, SetTargetFPS, WindowShouldClose, MOUSE_BUTTON_LEFT, IsKeyPressed, KEY_DOWN, KEY_UP, UnloadImage, ImageColorGrayscale, ImageColorTint, GREEN, ImageColorInvert, ImageColorContrast, ImageColorBrightness, ImageBlurGaussian, ImageFlipVertical, ImageFlipHorizontal, LoadImageColors, UpdateTexture, BeginDrawing, ClearBackground, RAYWHITE, DrawText, DARKGRAY, DrawRectangleRec, SKYBLUE, LIGHTGRAY, DrawRectangleLines, MeasureText, BLUE, GRAY, DARKBLUE, DrawTexture, EndDrawing, UnloadTexture, CloseWindow, WHITE, BLACK } from "rayjs:raylib";


const NUM_PROCESSES = 9;

const NONE = 0;
const COLOR_GRAYSCALE = 1;
const COLOR_TINT = 2;
const COLOR_INVERT = 3;
const COLOR_CONTRAST = 4;
const COLOR_BRIGHTNESS = 5;
const GAUSSIAN_BLUR = 6;
const FLIP_VERTICAL = 7;
const FLIP_HORIZONTAL = 8;

const processText = [
    "NO PROCESSING",
    "COLOR GRAYSCALE",
    "COLOR TINT",
    "COLOR INVERT",
    "COLOR CONTRAST",
    "COLOR BRIGHTNESS",
    "GAUSSIAN BLUR",
    "FLIP VERTICAL",
    "FLIP HORIZONTAL"
];

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - image processing");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    let imOrigin = LoadImage("resources/parrots.png");   // Loaded in CPU memory (RAM)
    ImageFormat(imOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);         // Format image to RGBA 32bit (required for texture update) <-- ISSUE
    let texture = LoadTextureFromImage(imOrigin);    // Image converted to texture, GPU memory (VRAM)

    let imCopy = ImageCopy(imOrigin);

    let currentProcess = NONE;
    let textureReload = false;

    let toggleRecs = new Array(NUM_PROCESSES);
    let mouseHoverRec = -1;

    for (let i = 0; i < NUM_PROCESSES; i++) toggleRecs[i] = new Rectangle( 40, 50 + 32*i, 150, 30 );

    SetTargetFPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------

        // Mouse toggle group logic
        for (let i = 0; i < NUM_PROCESSES; i++) {
            if (CheckCollisionPointRec(GetMousePosition(), toggleRecs[i])) {
                mouseHoverRec = i;

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    currentProcess = i;
                    textureReload = true;
                }
                break;
            }
            else mouseHoverRec = -1;
        }

        // Keyboard toggle group logic
        if (IsKeyPressed(KEY_DOWN)) {
            currentProcess++;
            if (currentProcess > (NUM_PROCESSES - 1)) currentProcess = 0;
            textureReload = true;
        } else if (IsKeyPressed(KEY_UP)) {
            currentProcess--;
            if (currentProcess < 0) currentProcess = 7;
            textureReload = true;
        }

        // Reload texture when required
        if (textureReload) {
            UnloadImage(imCopy);                // Unload image-copy data
            imCopy = ImageCopy(imOrigin);     // Restore image-copy from image-origin

            // NOTE: Image processing is a costly CPU process to be done every frame,
            // If image processing is required in a frame-basis, it should be done
            // with a texture and by shaders
            switch (currentProcess) {
                case COLOR_GRAYSCALE: ImageColorGrayscale(imCopy); break;
                case COLOR_TINT: ImageColorTint(imCopy, GREEN); break;
                case COLOR_INVERT: ImageColorInvert(imCopy); break;
                case COLOR_CONTRAST: ImageColorContrast(imCopy, -40); break;
                case COLOR_BRIGHTNESS: ImageColorBrightness(imCopy, -80); break;
                case GAUSSIAN_BLUR: ImageBlurGaussian(imCopy, 10); break;
                case FLIP_VERTICAL: ImageFlipVertical(imCopy); break;
                case FLIP_HORIZONTAL: ImageFlipHorizontal(imCopy); break;
                default: break;
            }

            let pixels = LoadImageColors(imCopy);    // Load pixel data from image (RGBA 32bit)
            UpdateTexture(texture, pixels);             // Update texture with new image data
            //UnloadImageColors(pixels) is called automatically

            textureReload = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("IMAGE PROCESSING:", 40, 30, 10, DARKGRAY);

            // Draw rectangles
            for (let i = 0; i < NUM_PROCESSES; i++) {
                DrawRectangleRec(toggleRecs[i], ((i == currentProcess) || (i == mouseHoverRec)) ? SKYBLUE : LIGHTGRAY);
                DrawRectangleLines( Math.floor( toggleRecs[i].x ), Math.floor( toggleRecs[i].y ), Math.floor(toggleRecs[i].width), Math.floor( toggleRecs[i].height), ((i == currentProcess) || (i == mouseHoverRec)) ? BLUE : GRAY);
                DrawText( processText[i], Math.floor( toggleRecs[i].x + toggleRecs[i].width/2 - MeasureText(processText[i], 10)/2), Math.floor( toggleRecs[i].y ) + 11, 10, ((i == currentProcess) || (i == mouseHoverRec)) ? DARKBLUE : DARKGRAY);
            }

            DrawTexture(texture, screenWidth - texture.width - 60, screenHeight/2 - texture.height/2, WHITE);
            DrawRectangleLines(screenWidth - texture.width - 60, screenHeight/2 - texture.height/2, texture.width, texture.height, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);       // Unload texture from VRAM
    UnloadImage(imOrigin);        // Unload image-origin from RAM
    UnloadImage(imCopy);          // Unload image-copy from RAM

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}