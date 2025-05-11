/*******************************************************************************************
*
*   raylib [core] example - 3d cmaera split screen
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 3.7, last time updated with raylib 4.0
*
*   Example contributed by Jeffery Myers (@JeffM2501) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2025 Jeffery Myers (@JeffM2501)
*
********************************************************************************************/

import {
    BeginDrawing, BeginMode3D, BeginTextureMode, BEIGE, BLACK, BLUE, BROWN, ClearBackground, CloseWindow, DARKBLUE, DrawCube, DrawPlane, DrawRectangle, DrawText, DrawTextureRec, EndDrawing, EndMode3D, EndTextureMode, Fade, GetFrameTime, GetScreenHeight, GetScreenWidth, InitWindow, IsKeyDown, KEY_DOWN, KEY_S, KEY_UP, KEY_W, LIGHTGRAY, LIME, LoadRenderTexture, MAROON, RAYWHITE, Rectangle, RED, SetTargetFPS, SKYBLUE, UnloadRenderTexture, Vector2, Vector3, WHITE, WindowShouldClose, Camera3D as Camera
} from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera split screen");

    // Setup player 1 camera and screen
    let cameraPlayer1 = new Camera();
    cameraPlayer1.fovy = 45;
    cameraPlayer1.up.y = 1;
    cameraPlayer1.target.y = 1;
    cameraPlayer1.position.z = -3;
    cameraPlayer1.position.y = 1;

    let screenPlayer1 = LoadRenderTexture(screenWidth/2, screenHeight);

    // Setup player two camera and screen
    let cameraPlayer2 = new Camera();
    cameraPlayer2.fovy = 45;
    cameraPlayer2.up.y = 1;
    cameraPlayer2.target.y = 3;
    cameraPlayer2.position.x = -3;
    cameraPlayer2.position.y = 3;

    let screenPlayer2 = LoadRenderTexture(screenWidth / 2, screenHeight);

    // Build a flipped rectangle the size of the split view to use for drawing later
    let splitScreenRect = new Rectangle(0, 0, screenPlayer1.texture.width, -screenPlayer1.texture.height);
    
    // Grid data
    let count = 5;
    let spacing = 4;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // If anyone moves this frame, how far will they move based on the time since the last frame
        // this moves things at 10 world units per second, regardless of the actual FPS
        let offsetThisFrame = 10*GetFrameTime();

        // Move Player1 forward and backwards (no turning)
        if (IsKeyDown(KEY_W)) {
            cameraPlayer1.position.z += offsetThisFrame;
            cameraPlayer1.target.z += offsetThisFrame;
        } else if (IsKeyDown(KEY_S)) {
            cameraPlayer1.position.z -= offsetThisFrame;
            cameraPlayer1.target.z -= offsetThisFrame;
        }

        // Move Player2 forward and backwards (no turning)
        if (IsKeyDown(KEY_UP)) {
            cameraPlayer2.position.x += offsetThisFrame;
            cameraPlayer2.target.x += offsetThisFrame;
        } else if (IsKeyDown(KEY_DOWN)) {
            cameraPlayer2.position.x -= offsetThisFrame;
            cameraPlayer2.target.x -= offsetThisFrame;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        // Draw Player1 view to the render texture
        BeginTextureMode(screenPlayer1);
            ClearBackground(SKYBLUE);
            
            BeginMode3D(cameraPlayer1);
            
                // Draw scene: grid of cube trees on a plane to make a "world"
                DrawPlane(new Vector3(0, 0, 0), new Vector2(50, 50), BEIGE); // Simple world plane

                for (let x = -count*spacing; x <= count*spacing; x += spacing) {
                    for (let z = -count*spacing; z <= count*spacing; z += spacing) {
                        DrawCube( new Vector3(x, 1.5, z), 1, 1, 1, LIME);
                        DrawCube( new Vector3(x, 0.5, z ), 0.25, 1, 0.25, BROWN);
                    }
                }

                // Draw a cube at each player's position
                DrawCube(cameraPlayer1.position, 1, 1, 1, RED);
                DrawCube(cameraPlayer2.position, 1, 1, 1, BLUE);
                
            EndMode3D();
            
            DrawRectangle(0, 0, GetScreenWidth()/2, 40, Fade(RAYWHITE, 0.8));
            DrawText("PLAYER1: W/S to move", 10, 10, 20, MAROON);
            
        EndTextureMode();

        // Draw Player2 view to the render texture
        BeginTextureMode(screenPlayer2);
            ClearBackground(SKYBLUE);
            
            BeginMode3D(cameraPlayer2);
            
                // Draw scene: grid of cube trees on a plane to make a "world"
                DrawPlane(new Vector3( 0, 0, 0 ), new Vector2( 50, 50 ), BEIGE); // Simple world plane

                for (let x = -count*spacing; x <= count*spacing; x += spacing) {
                    for (let z = -count*spacing; z <= count*spacing; z += spacing) {
                        DrawCube(new Vector3( x, 1.5, z ), 1, 1, 1, LIME);
                        DrawCube(new Vector3( x, 0.5, z ), 0.25, 1, 0.25, BROWN);
                    }
                }

                // Draw a cube at each player's position
                DrawCube(cameraPlayer1.position, 1, 1, 1, RED);
                DrawCube(cameraPlayer2.position, 1, 1, 1, BLUE);
                
            EndMode3D();
            
            DrawRectangle(0, 0, GetScreenWidth()/2, 40, Fade(RAYWHITE, 0.8));
            DrawText("PLAYER2: UP/DOWN to move", 10, 10, 20, DARKBLUE);
            
        EndTextureMode();

        // Draw both views render textures to the screen side by side
        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawTextureRec(screenPlayer1.texture, splitScreenRect, new Vector2( 0, 0 ), WHITE);
            DrawTextureRec(screenPlayer2.texture, splitScreenRect, new Vector2( screenWidth/2, 0 ), WHITE);
            
            DrawRectangle(GetScreenWidth()/2 - 2, 0, 4, GetScreenHeight(), LIGHTGRAY);
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(screenPlayer1); // Unload render texture
    UnloadRenderTexture(screenPlayer2); // Unload render texture

    CloseWindow();                      // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
