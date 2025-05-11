/*******************************************************************************************
*
*   raylib [core] example - 2d camera split screen
*
*   Example complexity rating: [★★★★] 4/4
*
*   Addapted from the core_3d_camera_split_screen example: 
*       https://github.com/raysan5/raylib/blob/master/examples/core/core_3d_camera_split_screen.c
*
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by Gabriel dos Santos Sanches (@gabrielssanches) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2025 Gabriel dos Santos Sanches (@gabrielssanches)
*
********************************************************************************************/

import * as rl from 'rayjs:raylib';

const PLAYER_SIZE = 40;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 440;

    rl.InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera split screen");

    let player1 = new rl.Rectangle( 200, 200, PLAYER_SIZE, PLAYER_SIZE );
    let player2 = new rl.Rectangle( 250, 200, PLAYER_SIZE, PLAYER_SIZE );

    let camera1 = new rl.Camera2D();
    camera1.target = new rl.Vector2( player1.x, player1.y );
    camera1.offset = new rl.Vector2( 200, 200 );
    camera1.rotation = 0;
    camera1.zoom = 1;

    let camera2 = new rl.Camera2D();
    camera2.target = new rl.Vector2( player2.x, player2.y );
    camera2.offset = new rl.Vector2( 200, 200 );
    camera2.rotation = 0;
    camera2.zoom = 1;

    let screenCamera1 = rl.LoadRenderTexture(screenWidth/2, screenHeight);
    let screenCamera2 = rl.LoadRenderTexture(screenWidth/2, screenHeight);

    // Build a flipped rectangle the size of the split view to use for drawing later
    let splitScreenRect = new rl.Rectangle( 0, 0, screenCamera1.texture.width, -screenCamera1.texture.height );

    rl.SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!rl.WindowShouldClose()){    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (rl.IsKeyDown(rl.KEY_S)) player1.y += 3;
        else if (rl.IsKeyDown(rl.KEY_W)) player1.y -= 3;
        if (rl.IsKeyDown(rl.KEY_D)) player1.x += 3;
        else if (rl.IsKeyDown(rl.KEY_A)) player1.x -= 3;

        if (rl.IsKeyDown(rl.KEY_UP)) player2.y -= 3;
        else if (rl.IsKeyDown(rl.KEY_DOWN)) player2.y += 3;
        if (rl.IsKeyDown(rl.KEY_RIGHT)) player2.x += 3;
        else if (rl.IsKeyDown(rl.KEY_LEFT)) player2.x -= 3;

        camera1.target = new rl.Vector2( player1.x, player1.y );
        camera2.target = new rl.Vector2( player2.x, player2.y );
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        rl.BeginTextureMode(screenCamera1);
        rl.ClearBackground(rl.RAYWHITE);

        rl.BeginMode2D(camera1);
            
            // Draw full scene with first camera
            for (let i = 0; i < screenWidth/PLAYER_SIZE + 1; i++){
                rl.DrawLineV(new rl.Vector2(PLAYER_SIZE*i, 0), new rl.Vector2( PLAYER_SIZE*i, screenHeight), rl.LIGHTGRAY);
            }

            for (let i = 0; i < screenHeight/PLAYER_SIZE + 1; i++){
                rl.DrawLineV(new rl.Vector2(0, PLAYER_SIZE*i), new rl.Vector2( screenWidth, PLAYER_SIZE*i), rl.LIGHTGRAY);
            }

            for (let i = 0; i < screenWidth/PLAYER_SIZE; i++){
                for (let j = 0; j < screenHeight/PLAYER_SIZE; j++){
                    rl.DrawText(rl.TextFormat("[%i,%i]", i, j), 10 + PLAYER_SIZE*i, 15 + PLAYER_SIZE*j, 10, rl.LIGHTGRAY);
                }
            }

            rl.DrawRectangleRec(player1, rl.RED);
            rl.DrawRectangleRec(player2, rl.BLUE);
        rl.EndMode2D();

        rl.DrawRectangle(0, 0, rl.GetScreenWidth()/2, 30, rl.Fade(rl.RAYWHITE, 0.6));
        rl.DrawText("PLAYER1: W/S/A/D to move", 10, 10, 10, rl.MAROON);

        rl.EndTextureMode();

        rl.BeginTextureMode(screenCamera2);
            rl.ClearBackground(rl.RAYWHITE);

            rl.BeginMode2D(camera2);
            
                // Draw full scene with second camera
                for (let i = 0; i < screenWidth/PLAYER_SIZE + 1; i++){
                    rl.DrawLineV(new rl.Vector2( PLAYER_SIZE*i, 0), new rl.Vector2( PLAYER_SIZE*i, screenHeight), rl.LIGHTGRAY);
                }

                for (let i = 0; i < screenHeight/PLAYER_SIZE + 1; i++){
                    rl.DrawLineV(new rl.Vector2(0, PLAYER_SIZE*i), new rl.Vector2( screenWidth, PLAYER_SIZE*i), rl.LIGHTGRAY);
                }

                for (let i = 0; i < screenWidth/PLAYER_SIZE; i++){
                    for (let j = 0; j < screenHeight/PLAYER_SIZE; j++){
                        rl.DrawText(rl.TextFormat("[%i,%i]", i, j), 10 + PLAYER_SIZE*i, 15 + PLAYER_SIZE*j, 10, rl.LIGHTGRAY);
                    }
                }

                rl.DrawRectangleRec(player1, rl.RED);
                rl.DrawRectangleRec(player2, rl.BLUE);

            rl.EndMode2D();

            rl.DrawRectangle(0, 0, rl.GetScreenWidth()/2, 30, rl.Fade(rl.RAYWHITE, 0.6));
            rl.DrawText("PLAYER2: UP/DOWN/LEFT/RIGHT to move", 10, 10, 10, rl.DARKBLUE);

        rl.EndTextureMode();

        // Draw both views render textures to the screen side by side
        rl.BeginDrawing();
            rl.ClearBackground(rl.BLACK);

            rl.DrawTextureRec(screenCamera1.texture, splitScreenRect, new rl.Vector2(0, 0), rl.WHITE);
            rl.DrawTextureRec(screenCamera2.texture, splitScreenRect, new rl.Vector2(screenWidth/2, 0), rl.WHITE);

            rl.DrawRectangle(rl.GetScreenWidth()/2 - 2, 0, 4, rl.GetScreenHeight(), rl.LIGHTGRAY);
        rl.EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    rl.UnloadRenderTexture(screenCamera1); // Unload render texture
    rl.UnloadRenderTexture(screenCamera2); // Unload render texture

    rl.CloseWindow();                      // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
