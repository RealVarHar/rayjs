import * as rl from 'rayjs:raylib';

{
    for (const key in rl) {
        globalThis[key] = rl[key]
    }
    /*******************************************************************************************
     *
     *   raylib [shapes] example - Draw raylib logo using basic shapes
     *
     *   Example originally created with raylib 1.0, last time updated with raylib 1.0
     *
     *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
     *   BSD-like license that allows static linking with closed source software
     *
     *   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
     *
     ********************************************************************************************/
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - raylib logo using shapes");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(screenWidth / 2 - 128, screenHeight / 2 - 128, 256, 256, BLACK);
        DrawRectangle(screenWidth / 2 - 112, screenHeight / 2 - 112, 224, 224, GOLD);
        DrawText("rayjs", screenWidth / 2 - 38, screenHeight / 2 + 48, 50, BLACK);

        DrawText("this is NOT a texture!", 350, 370, 10, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}