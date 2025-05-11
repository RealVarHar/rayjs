/*******************************************************************************************
*
*   raylib [textures] example - particles blending
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 1.7, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginBlendMode,
    BeginDrawing, BLACK,
    BLEND_ADDITIVE,
    BLEND_ALPHA, ClearBackground,
    CloseWindow,
    Color, DARKGRAY, DrawText, DrawTexturePro, EndBlendMode, EndDrawing, Fade,
    GetMousePosition,
    GetRandomValue,
    InitWindow, IsKeyPressed, KEY_SPACE,
    LoadTexture, RAYWHITE, Rectangle,
    SetTargetFPS,
    UnloadTexture,
    Vector2,
    WindowShouldClose
} from "rayjs:raylib";

const MAX_PARTICLES = 200;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - particles blending");

    // Particles pool, reuse them!
    let mouseTail = new Array(MAX_PARTICLES);

    // Initialize particles
    for (let i = 0; i < MAX_PARTICLES; i++) {
        mouseTail[i] = {
            position: new Vector2( 0, 0 ),
            color: new Color( GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 ),
            alpha: 1,
            size: GetRandomValue(1, 30)/20,
            rotation: GetRandomValue(0, 360),
            active: false
        }
    }

    let gravity = 3;

    let smoke = LoadTexture("resources/spark_flame.png");

    let blending = BLEND_ALPHA;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------

        // Activate one particle every frame and Update active particles
        // NOTE: Particles initial position should be mouse position when activated
        // NOTE: Particles fall down with gravity and rotation... and disappear after 2 seconds (alpha = 0)
        // NOTE: When a particle disappears, active = false and it can be reused.
        for (let i = 0; i < MAX_PARTICLES; i++) {
            if (!mouseTail[i].active) {
                mouseTail[i].active = true;
                mouseTail[i].alpha = 1;
                mouseTail[i].position = GetMousePosition();
                i = MAX_PARTICLES;
            }
        }

        for (let i = 0; i < MAX_PARTICLES; i++) {
            if (mouseTail[i].active) {
                mouseTail[i].position.y += gravity/2;
                mouseTail[i].alpha -= 0.005;

                if (mouseTail[i].alpha <= 0) mouseTail[i].active = false;

                mouseTail[i].rotation += 2;
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            if (blending == BLEND_ALPHA) blending = BLEND_ADDITIVE;
            else blending = BLEND_ALPHA;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginBlendMode(blending);

                // Draw active particles
                for (let i = 0; i < MAX_PARTICLES; i++) {
                    if (mouseTail[i].active) {
                        DrawTexturePro(smoke, new Rectangle( 0, 0, smoke.width, smoke.height ),
                            new Rectangle( mouseTail[i].position.x, mouseTail[i].position.y, smoke.width*mouseTail[i].size, smoke.height*mouseTail[i].size ),
                            new Vector2( smoke.width*mouseTail[i].size/2, smoke.height*mouseTail[i].size/2 ), mouseTail[i].rotation,
                            Fade(mouseTail[i].color, mouseTail[i].alpha));
                    }
                }

            EndBlendMode();

            DrawText("PRESS SPACE to CHANGE BLENDING MODE", 180, 20, 20, BLACK);

            if (blending == BLEND_ALPHA) DrawText("ALPHA BLENDING", 290, screenHeight - 40, 20, BLACK);
            else DrawText("ADDITIVE BLENDING", 280, screenHeight - 40, 20, RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(smoke);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}