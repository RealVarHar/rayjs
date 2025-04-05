import * as rl from 'rayjs:raylib';
{
    for (const key in rl) { globalThis[key] = rl[key] };

    /*******************************************************************************************
    *
    *   raylib [audio] example - Module playing (streaming)
    *
    *   Example originally created with raylib 1.5, last time updated with raylib 3.5
    *
    *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
    *   BSD-like license that allows static linking with closed source software
    *
    *   Copyright (c) 2016-2023 Ramon Santamaria (@raysan5)
    *
    ********************************************************************************************/
    const MAX_CIRCLES = 64

    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // NOTE: Try to enable MSAA 4X

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - module playing (streaming)");

    InitAudioDevice();                  // Initialize audio device

    const colors = [ORANGE, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, PINK,
                            YELLOW, GREEN, SKYBLUE, PURPLE, BEIGE];

    // Creates some circles for visual effect
    const circles = new Array(MAX_CIRCLES).fill({});

    for (let i = MAX_CIRCLES - 1; i >= 0; i--)
    {
        circles[i].alpha = 0.0;
        circles[i].radius = GetRandomValue(10, 40);
        circles[i].position = new Vector2(0,0)
        circles[i].position.x = GetRandomValue(circles[i].radius, (screenWidth - circles[i].radius));
        circles[i].position.y = GetRandomValue(circles[i].radius, (screenHeight - circles[i].radius));
        circles[i].speed = GetRandomValue(1, 100)/2000.0;
        circles[i].color = colors[GetRandomValue(0, 13)];
    }

    const music = LoadMusicStream("resources/mini1111.xm");
    music.looping = false;
    const pitch = 1.0;

    PlayMusicStream(music);

    let timePlayed = 0.0;
    let pause = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music);      // Update music buffer with new stream data

        // Restart music playing (stop and play)
        if (IsKeyPressed(KEY_SPACE))
        {
            StopMusicStream(music);
            PlayMusicStream(music);
        }

        // Pause/Resume music playing
        if (IsKeyPressed(KEY_P))
        {
            pause = !pause;

            if (pause) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }

        if (IsKeyDown(KEY_DOWN)) pitch -= 0.01;
        else if (IsKeyDown(KEY_UP)) pitch += 0.01;

        SetMusicPitch(music, pitch);

        // Get timePlayed scaled to bar dimensions
        timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music) * (screenWidth - 40);

        // Color circles animation
        for (let i = MAX_CIRCLES - 1; (i >= 0) && !pause; i--)
        {
            circles[i].alpha += circles[i].speed;
            circles[i].radius += circles[i].speed*10.0;

            if (circles[i].alpha > 1.0) circles[i].speed *= -1;

            if (circles[i].alpha <= 0.0)
            {
                circles[i].alpha = 0.0;
                circles[i].radius = GetRandomValue(10, 40);
                circles[i].position.x = GetRandomValue(circles[i].radius, (screenWidth - circles[i].radius));
                circles[i].position.y = GetRandomValue(circles[i].radius, (screenHeight - circles[i].radius));
                circles[i].color = colors[GetRandomValue(0, 13)];
                circles[i].speed = GetRandomValue(1, 100) / 2000.0;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            for (let i = MAX_CIRCLES - 1; i >= 0; i--)
            {
                DrawCircleV(circles[i].position, circles[i].radius, Fade(circles[i].color, circles[i].alpha));
            }

            // Draw time bar
            DrawRectangle(20, screenHeight - 20 - 12, screenWidth - 40, 12, LIGHTGRAY);
            DrawRectangle(20, screenHeight - 20 - 12, timePlayed, 12, MAROON);
            DrawRectangleLines(20, screenHeight - 20 - 12, screenWidth - 40, 12, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadMusicStream(music);          // Unload music stream buffers from RAM

    CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}