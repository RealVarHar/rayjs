/*******************************************************************************************
*
*   raylib [core] example - Smooth Pixel-perfect camera
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 3.7, last time updated with raylib 4.0
*   
*   Example contributed by Giancamillo Alessandroni (@NotManyIdeasDev) and
*   reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2025 Giancamillo Alessandroni (@NotManyIdeasDev) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing, BeginMode2D, BeginTextureMode, BLACK, BLUE, Camera2D, ClearBackground, CloseWindow, DARKBLUE, DARKGREEN, DrawFPS, DrawRectanglePro, DrawText, DrawTexturePro, EndDrawing, EndMode2D, EndTextureMode, GetFrameTime, GetScreenWidth, GetTime, InitWindow, LoadRenderTexture, RAYWHITE, Rectangle, RED, SetTargetFPS, TextFormat, UnloadRenderTexture, Vector2, WHITE, WindowShouldClose
} from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    const virtualScreenWidth = 160;
    const virtualScreenHeight = 90;

    const virtualRatio = screenWidth/virtualScreenWidth;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - smooth pixel-perfect camera");

    let worldSpaceCamera = new Camera2D();  // Game world camera
    worldSpaceCamera.zoom = 1;

    let screenSpaceCamera = new Camera2D(); // Smoothing camera
    screenSpaceCamera.zoom = 1;

    let target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight); // This is where we'll draw all our objects.

    let rec01 = new Rectangle( 70, 35, 20, 20 );
    let rec02 = new Rectangle( 90, 55, 30, 10 );
    let rec03 = new Rectangle( 80, 65, 15, 25 );

    // The target's height is flipped (in the source Rectangle), due to OpenGL reasons
    let sourceRec = new Rectangle( 0, 0, target.texture.width, -target.texture.height );
    let destRec = new Rectangle( -virtualRatio, -virtualRatio, screenWidth + (virtualRatio*2), screenHeight + (virtualRatio*2) );

    let origin = new Vector2( 0, 0 );

    let rotation = 0;

    let cameraX = 0;
    let cameraY = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        rotation += 60*GetFrameTime();   // Rotate the rectangles, 60 degrees per second

        // Make the camera move to demonstrate the effect
        cameraX = Math.sin(GetTime())*50 - 10;
        cameraY = Math.cos(GetTime())*30;

        // Set the camera's target to the values computed above
        screenSpaceCamera.target = new Vector2( cameraX, cameraY );

        // Round worldSpace coordinates, keep decimals into screenSpace coordinates
        worldSpaceCamera.target.x = Math.floor(screenSpaceCamera.target.x);
        screenSpaceCamera.target.x -= worldSpaceCamera.target.x;
        screenSpaceCamera.target.x *= virtualRatio;

        worldSpaceCamera.target.y = Math.floor(screenSpaceCamera.target.y);
        screenSpaceCamera.target.y -= worldSpaceCamera.target.y;
        screenSpaceCamera.target.y *= virtualRatio;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);

            BeginMode2D(worldSpaceCamera);
                DrawRectanglePro(rec01, origin, rotation, BLACK);
                DrawRectanglePro(rec02, origin, -rotation, RED);
                DrawRectanglePro(rec03, origin, rotation + 45, BLUE);
            EndMode2D();
        EndTextureMode();

        BeginDrawing();
            ClearBackground(RED);

            BeginMode2D(screenSpaceCamera);
                DrawTexturePro(target.texture, sourceRec, destRec, origin, 0, WHITE);
            EndMode2D();

            DrawText(TextFormat("Screen resolution: %ix%i", screenWidth, screenHeight), 10, 10, 20, DARKBLUE);
            DrawText(TextFormat("World resolution: %ix%i", virtualScreenWidth, virtualScreenHeight), 10, 40, 20, DARKGREEN);
            DrawFPS(GetScreenWidth() - 95, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target);    // Unload render texture

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}