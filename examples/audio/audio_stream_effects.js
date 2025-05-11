/*******************************************************************************************
*
*   raylib [audio] example - Music stream processing effects
*
*   Example complexity rating: [★★★★] 4/4
*
*   Example originally created with raylib 4.2, last time updated with raylib 5.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing, ClearBackground, CloseAudioDevice, CloseWindow, DrawRectangle, DrawRectangleLines, DrawText, EndDrawing, GetMusicTimeLength, GetMusicTimePlayed, GRAY, InitAudioDevice, InitWindow, IsKeyPressed, KEY_D, KEY_F, KEY_P, KEY_SPACE, LIGHTGRAY, LoadMusicStream, MAROON, PauseMusicStream, PlayMusicStream, RAYWHITE, ResumeMusicStream, SetTargetFPS, StopMusicStream, TextFormat, UnloadMusicStream, UpdateMusicStream, WindowShouldClose
} from "rayjs:raylib";

// Required delay effect variables
let delayBufferSize = 48000*2;// 1 second delay (device sampleRate*channels)
let delayBuffer = new Float32Array(delayBufferSize);
let delayReadIndex = 2;
let delayWriteIndex = 0;

//------------------------------------------------------------------------------------
// Module Functions Declaration
//------------------------------------------------------------------------------------
// Audio effect: lowpass filter
var low = [0,0];
function AudioProcessEffectLPF(buffer, frames) {
    const cutoff = 70 / 44100; // 70 Hz lowpass filter
    const k = cutoff / (cutoff + 0.1591549431); // RC filter formula

    // Converts the buffer data before using it
    let bufferData = new Float32Array(buffer);
    for (let i = 0; i < frames*2; i += 2) {
        const l = bufferData[i];
        const r = bufferData[i + 1];

        low[0] += k * (l - low[0]);
        low[1] += k * (r - low[1]);
        bufferData[i] = low[0];
        bufferData[i + 1] = low[1];
    }
}

// Audio effect: delay
function AudioProcessEffectDelay(buffer, frames) {

    let bufferData = new Float32Array(buffer);
    for (let i = 0; i < frames*2; i += 2) {
        let leftDelay = delayBuffer[delayReadIndex++];
        let rightDelay = delayBuffer[delayReadIndex++];

        if (delayReadIndex == delayBufferSize) delayReadIndex = 0;

        bufferData[i] = 0.5*bufferData[i] + 0.5*leftDelay;
        bufferData[i + 1] = 0.5*bufferData[i + 1] + 0.5*rightDelay;

        delayBuffer[delayWriteIndex++] = bufferData[i];
        delayBuffer[delayWriteIndex++] = bufferData[i + 1];
        if (delayWriteIndex == delayBufferSize) delayWriteIndex = 0;
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - stream effects");

    InitAudioDevice();              // Initialize audio device

    let music = LoadMusicStream("resources/country.mp3");

    PlayMusicStream(music);

    let timePlayed = 0;        // Time played normalized [0.0f..1.0f]
    let pause = false;             // Music playing paused

    let enableEffectLPF = false;   // Enable effect low-pass-filter
    let enableEffectDelay = false; // Enable effect delay (1 second)

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music);   // Update music buffer with new stream data

        // Restart music playing (stop and play)
        if (IsKeyPressed(KEY_SPACE)) {
            StopMusicStream(music);
            PlayMusicStream(music);
        }

        // Pause/Resume music playing
        if (IsKeyPressed(KEY_P)) {
            pause = !pause;

            if (pause) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }

        // Add/Remove effect: lowpass filter
        if (IsKeyPressed(KEY_F)) {
            enableEffectLPF = !enableEffectLPF;
            if (enableEffectLPF) AttachAudioStreamProcessor(music.stream, AudioProcessEffectLPF);
            else DetachAudioStreamProcessor(music.stream, AudioProcessEffectLPF);
        }

        // Add/Remove effect: delay
        if (IsKeyPressed(KEY_D)) {
            enableEffectDelay = !enableEffectDelay;
            if (enableEffectDelay) AttachAudioStreamProcessor(music.stream, AudioProcessEffectDelay);
            else DetachAudioStreamProcessor(music.stream, AudioProcessEffectDelay);
        }
        
        // Get normalized time played for current music stream
        timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);

        if (timePlayed > 1) timePlayed = 1;   // Make sure time played is no longer than music
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("MUSIC SHOULD BE PLAYING!", 245, 150, 20, LIGHTGRAY);

            DrawRectangle(200, 180, 400, 12, LIGHTGRAY);
            DrawRectangle(200, 180, Math.floor(timePlayed*400.0), 12, MAROON);
            DrawRectangleLines(200, 180, 400, 12, GRAY);

            DrawText("PRESS SPACE TO RESTART MUSIC", 215, 230, 20, LIGHTGRAY);
            DrawText("PRESS P TO PAUSE/RESUME MUSIC", 208, 260, 20, LIGHTGRAY);
            
            DrawText(TextFormat("PRESS F TO TOGGLE LPF EFFECT: %s", enableEffectLPF? "ON" : "OFF"), 200, 320, 20, GRAY);
            DrawText(TextFormat("PRESS D TO TOGGLE DELAY EFFECT: %s", enableEffectDelay? "ON" : "OFF"), 180, 350, 20, GRAY);

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