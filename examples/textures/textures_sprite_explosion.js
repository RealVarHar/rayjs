/*******************************************************************************************
*
*   raylib [textures] example - sprite explosion
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing, ClearBackground, CloseAudioDevice, CloseWindow, DrawTextureRec, EndDrawing,
    GetMousePosition,
    InitAudioDevice,
    InitWindow, IsMouseButtonPressed,
    LoadSound,
    LoadTexture, MOUSE_BUTTON_LEFT, PlaySound, RAYWHITE,
    Rectangle,
    SetTargetFPS, UnloadSound, UnloadTexture,
    Vector2, WHITE,
    WindowShouldClose
} from "rayjs:raylib";

const NUM_FRAMES_PER_LINE = 5;
const NUM_LINES = 5;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - sprite explosion");

    InitAudioDevice();

    // Load explosion sound
    let fxBoom = LoadSound("resources/boom.wav");

    // Load explosion texture
    let explosion = LoadTexture("resources/explosion.png");

    // Init variables for animation
    let frameWidth = explosion.width/NUM_FRAMES_PER_LINE;   // Sprite one frame rectangle width
    let frameHeight = explosion.height/NUM_LINES;           // Sprite one frame rectangle height
    let currentFrame = 0;
    let currentLine = 0;

    let frameRec = new Rectangle( 0, 0, frameWidth, frameHeight );
    let position = new Vector2( 0, 0 );

    let active = false;
    let framesCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------

        // Check for mouse button pressed and activate explosion (if not active)
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !active) {
            position = GetMousePosition();
            active = true;

            position.x -= frameWidth/2;
            position.y -= frameHeight/2;

            PlaySound(fxBoom);
        }

        // Compute explosion animation frames
        if (active) {
            framesCounter++;

            if (framesCounter > 2) {
                currentFrame++;

                if (currentFrame >= NUM_FRAMES_PER_LINE) {
                    currentFrame = 0;
                    currentLine++;

                    if (currentLine >= NUM_LINES) {
                        currentLine = 0;
                        active = false;
                    }
                }

                framesCounter = 0;
            }
        }

        frameRec.x = frameWidth*currentFrame;
        frameRec.y = frameHeight*currentLine;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw explosion required frame rectangle
            if (active) DrawTextureRec(explosion, frameRec, position, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(explosion);   // Unload texture
    UnloadSound(fxBoom);        // Unload sound

    CloseAudioDevice();

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}