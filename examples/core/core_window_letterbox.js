/*******************************************************************************************
*
*   raylib [core] example - window scale letterbox (and virtual mouse)
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example contributed by Anata (@anatagawa) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Anata (@anatagawa) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as rm from 'rayjs:raymath';
import {
    BeginDrawing, BeginTextureMode, BLACK, ClearBackground, CloseWindow, Color, DrawRectangle, DrawText, DrawTexturePro, EndDrawing, EndTextureMode, FLAG_VSYNC_HINT, FLAG_WINDOW_RESIZABLE, GetMousePosition, GetRandomValue, GetScreenHeight, GetScreenWidth, GREEN, InitWindow, IsKeyPressed, KEY_SPACE, LoadRenderTexture, RAYWHITE, Rectangle, SetConfigFlags, SetTargetFPS, SetTextureFilter, SetWindowMinSize, TextFormat, TEXTURE_FILTER_BILINEAR, UnloadRenderTexture, Vector2, WHITE, WindowShouldClose, YELLOW
} from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    const windowWidth = 800;
    const windowHeight = 450;

    // Enable config flags for resizable window and vertical synchro
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(windowWidth, windowHeight, "raylib [core] example - window scale letterbox");
    SetWindowMinSize(320, 240);

    let gameScreenWidth = 640;
    let gameScreenHeight = 480;

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    let target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // Texture scale filter to use

    let colors = new Array(10);
    for (let i = 0; i < 10; i++) colors[i] = new Color( GetRandomValue(100, 250), GetRandomValue(50, 150), GetRandomValue(10, 100), 255 );

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key

        // Update
        //----------------------------------------------------------------------------------
        // Compute required framebuffer scaling
        let scale = Math.min(GetScreenWidth()/gameScreenWidth, GetScreenHeight()/gameScreenHeight);

        if (IsKeyPressed(KEY_SPACE)) {
            // Recalculate random colors for the bars
            for (let i = 0; i < 10; i++) colors[i] = new Color( GetRandomValue(100, 250), GetRandomValue(50, 150), GetRandomValue(10, 100), 255 );
        }

        // Update virtual mouse (clamped mouse value behind game screen)
        let mouse = GetMousePosition();
        let virtualMouse = new Vector2();
        virtualMouse.x = (mouse.x - (GetScreenWidth() - (gameScreenWidth*scale))*0.5)/scale;
        virtualMouse.y = (mouse.y - (GetScreenHeight() - (gameScreenHeight*scale))*0.5)/scale;
        virtualMouse = rm.Vector2Clamp(virtualMouse, new Vector2( 0, 0 ), new Vector2( gameScreenWidth, gameScreenHeight ));

        // Apply the same transformation as the virtual mouse to the real mouse (i.e. to work with raygui)
        //SetMouseOffset(-(GetScreenWidth() - (gameScreenWidth*scale))*0.5, -(GetScreenHeight() - (gameScreenHeight*scale))*0.5);
        //SetMouseScale(1/scale, 1/scale);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        // Draw everything in the render texture, note this will not be rendered on screen, yet
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);  // Clear render texture background color

            for (let i = 0; i < 10; i++) DrawRectangle(0, (gameScreenHeight/10)*i, gameScreenWidth, gameScreenHeight/10, colors[i]);

            DrawText("If executed inside a window,\nyou can resize the window,\nand see the screen scaling!", 10, 25, 20, WHITE);
            DrawText(TextFormat("Default Mouse: [%i , %i]", Math.floor(mouse.x), Math.floor(mouse.y)), 350, 25, 20, GREEN);
            DrawText(TextFormat("Virtual Mouse: [%i , %i]", Math.floor(virtualMouse.x), Math.floor(virtualMouse.y)), 350, 55, 20, YELLOW);
        EndTextureMode();
        
        BeginDrawing();
            ClearBackground(BLACK);     // Clear screen background

            // Draw render texture to screen, properly scaled
            DrawTexturePro(target.texture, new Rectangle( 0, 0, target.texture.width, -target.texture.height ),
                           new Rectangle( (GetScreenWidth() - gameScreenWidth*scale)*0.5, (GetScreenHeight() - gameScreenHeight*scale)*0.5,
                           gameScreenWidth*scale, gameScreenHeight*scale ), new Vector2( 0, 0 ), 0, WHITE);
        EndDrawing();
        //--------------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target);        // Unload render texture

    CloseWindow();                      // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
