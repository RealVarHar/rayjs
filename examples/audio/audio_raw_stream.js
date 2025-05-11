/*******************************************************************************************
*
*   raylib [audio] example - Raw audio streaming
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 1.6, last time updated with raylib 4.2
*
*   Example created by Ramon Santamaria (@raysan5) and reviewed by James Hofmann (@triplefox)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5) and James Hofmann (@triplefox)
*
********************************************************************************************/

import {
    BeginDrawing, ClearBackground, CloseAudioDevice, CloseWindow, DARKGRAY, DrawPixelV, DrawText, EndDrawing, GetMousePosition, GetScreenWidth, InitAudioDevice, InitWindow, IsMouseButtonDown, LoadAudioStream, MOUSE_BUTTON_LEFT, PI, PlayAudioStream, RAYWHITE, RED, SetAudioStreamBufferSizeDefault, SetAudioStreamPan, SetTargetFPS, TextFormat, UnloadAudioStream, Vector2, WindowShouldClose
} from "rayjs:raylib";

const MAX_SAMPLES = 512;
const MAX_SAMPLES_PER_UPDATE = 4096;

// Cycles per second (hz)
let frequency = 440;

// Audio frequency, for smoothing
let audioFrequency = 440;

// Previous value, used to test if sine needs to be rewritten, and to smoothly modulate frequency
let oldFrequency = 1;

// Index for audio rendering
let sineIdx = 0;

// Audio input processing callback
//TODO: does this need a worker thread?
function AudioInputCallback(buffer, frames) {
    audioFrequency = frequency + (audioFrequency - frequency)*0.95;

    let incr = audioFrequency/44100;
    let d = new Int16Array(buffer);

    for (let i = 0; i < frames; i++) {
        d[i] = 32000*Math.sin(2*PI*sineIdx);
        sineIdx += incr;
        if (sineIdx > 1) sineIdx -= 1;
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

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - raw audio streaming");

    InitAudioDevice();              // Initialize audio device

    SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);

    // Init raw audio stream (sample rate: 44100, sample size: 16bit-short, channels: 1-mono)
    let stream = LoadAudioStream(44100, 16, 1);

    SetAudioStreamCallback(stream, AudioInputCallback);

    // Buffer for the single cycle waveform we are synthesizing
    let data = new Int16Array(MAX_SAMPLES);

    PlayAudioStream(stream);        // Start processing stream buffer (no data loaded currently)

    // Position read in to determine next frequency
    let mousePosition = new Vector2( -100, -100 );

    // Computed size in samples of the sine wave
    let waveLength = 1;

    let position = new Vector2( 0, 0 );

    SetTargetFPS(30);               // Set our game to run at 30 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------

        // Sample mouse input.
        mousePosition = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            frequency = 40 + mousePosition.y;

            const pan = mousePosition.x / screenWidth;
            SetAudioStreamPan(stream, pan);
        }

        // Rewrite the sine wave
        // Compute two cycles to allow the buffer padding, simplifying any modulation, resampling, etc.
        if (frequency != oldFrequency) {
            // Compute wavelength. Limit size in both directions.
            //int oldWavelength = waveLength;
            waveLength = Math.floor(22050/frequency);
            if (waveLength > MAX_SAMPLES/2) waveLength = MAX_SAMPLES/2;
            if (waveLength < 1) waveLength = 1;

            // Write sine wave
            for (let i = 0; i < waveLength*2; i++) {
                data[i] = Math.floor(Math.sin(2*Math.PI*i/waveLength)*32000);
            }
            // Make sure the rest of the line is flat
            for (let j = waveLength*2; j < MAX_SAMPLES; j++) {
                data[j] = 0;
            }

            // Scale read cursor's position to minimize transition artifacts
            //readCursor = (int)(readCursor * ((float)waveLength / (float)oldWavelength));
            oldFrequency = frequency;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(TextFormat("sine frequency: %i",Math.floor(frequency)), GetScreenWidth() - 220, 10, 20, RED);
            DrawText("click mouse button to change frequency or pan", 10, 10, 20, DARKGRAY);

            // Draw the current buffer state proportionate to the screen
            for (let i = 0; i < screenWidth; i++) {
                position.x = i;
                position.y = 250 + 50*data[i*MAX_SAMPLES/screenWidth]/32000;

                DrawPixelV(position, RED);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadAudioStream(stream);   // Close raw audio stream and delete buffers from RAM
    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
