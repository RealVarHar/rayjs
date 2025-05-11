import {
    BeginDrawing, ClearBackground, CloseAudioDevice, CloseWindow, DrawRectangle, DrawRectangleLines, DrawText, EndDrawing, GetMusicTimeLength, GetMusicTimePlayed, GRAY, InitAudioDevice, InitWindow, IsKeyPressed, KEY_P, KEY_SPACE, LIGHTGRAY, LoadMusicStream, MAROON, PauseMusicStream, PlayMusicStream, RAYWHITE, ResumeMusicStream, SetTargetFPS, StopMusicStream, UnloadMusicStream, UpdateMusicStream, WindowShouldClose
} from "rayjs:raylib";
{

    /*******************************************************************************************
    *
    *   raylib [audio] example - Music playing (streaming)
    *
    *   Example originally created with raylib 1.3, last time updated with raylib 4.0
    *
    *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
    *   BSD-like license that allows static linking with closed source software
    *
    *   Copyright (c) 2015-2023 Ramon Santamaria (@raysan5)
    *
    ********************************************************************************************/
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - music playing (streaming)");

    InitAudioDevice();              // Initialize audio device

    const music = LoadMusicStream("resources/country.mp3");

    PlayMusicStream(music);

    let timePlayed = 0.0;        // Time played normalized [0.0..1.0]
    let pause = false;             // Music playing paused

    SetTargetFPS(30);               // Set our game to run at 30 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music);   // Update music buffer with new stream data

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

        // Get normalized time played for current music stream
        timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);

        if (timePlayed > 1.0) timePlayed = 1.0;   // Make sure time played is no longer than music
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("MUSIC SHOULD BE PLAYING!", 255, 150, 20, LIGHTGRAY);

            DrawRectangle(200, 200, 400, 12, LIGHTGRAY);
            DrawRectangle(200, 200, (timePlayed*400.0), 12, MAROON);
            DrawRectangleLines(200, 200, 400, 12, GRAY);

            DrawText("PRESS SPACE TO RESTART MUSIC", 215, 250, 20, LIGHTGRAY);
            DrawText("PRESS P TO PAUSE/RESUME MUSIC", 208, 280, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadMusicStream(music);   // Unload music stream buffers from RAM

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}