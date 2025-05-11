/*******************************************************************************************
*
*   raylib [textures] example - Texture source and destination rectangles
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing,
    ClearBackground, CloseWindow, DrawLine, DrawText, DrawTexturePro, EndDrawing, GRAY,
    InitWindow,
    LoadTexture, RAYWHITE,
    Rectangle,
    SetTargetFPS, UnloadTexture,
    Vector2, WHITE,
    WindowShouldClose
} from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] examples - texture source and destination rectangles");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    let scarfy = LoadTexture("resources/scarfy.png");        // Texture loading

    let frameWidth = scarfy.width/6;
    let frameHeight = scarfy.height;

    // Source rectangle (part of the texture to use for drawing)
    let sourceRec = new Rectangle( 0, 0, frameWidth, frameHeight );

    // Destination rectangle (screen rectangle where drawing part of texture)
    let destRec = new Rectangle( screenWidth/2, screenHeight/2, frameWidth*2, frameHeight*2 );

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    let origin = new Vector2( frameWidth, frameHeight );

    let rotation = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        rotation++;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // NOTE: Using DrawTexturePro() we can easily rotate and scale the part of the texture we draw
            // sourceRec defines the part of the texture we use for drawing
            // destRec defines the rectangle where our texture part will fit (scaling it to fit)
            // origin defines the point of the texture used as reference for rotation and scaling
            // rotation defines the texture rotation (using origin as rotation point)
            DrawTexturePro(scarfy, sourceRec, destRec, origin, rotation, WHITE);

            DrawLine(destRec.x, 0, destRec.x, screenHeight, GRAY);
            DrawLine(0, destRec.y, screenWidth, destRec.y, GRAY);

            DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(scarfy);        // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}