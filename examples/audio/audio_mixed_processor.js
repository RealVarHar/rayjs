import * as rl from 'rayjs:raylib';
for (const key in rl) { globalThis[key] = rl[key] };

/*******************************************************************************************
*
*   raylib [audio] example - Mixed audio processing
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example contributed by hkc (@hatkidchan) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 hkc (@hatkidchan)
*
********************************************************************************************/

var exponent = 1;                 // Audio exponentiation value
var averageVolume = new Float32Array(400);   // Average volume history

//------------------------------------------------------------------------------------
// Audio processing function
//------------------------------------------------------------------------------------
function ProcessAudio(buffer, frames){
    let samples = buffer;   // Samples internally stored as <float>s
    let average = 0;               // Temporary average volume

    for (let frame = 0; frame < frames; frame++){
        let left = samples[frame * 2 + 0], right = samples[frame * 2 + 1];

        left = Math.pow(Math.abs(left), exponent) * ( (left < 0)? -1 : 1 );
        right = Math.pow(Math.abs(right), exponent) * ( (right < 0)? -1 : 1 );

        average += Math.abs(left) / frames;   // accumulating average volume
        average += Math.abs(right) / frames;
    }

    // Moving history to the left
    for (let i = 0; i < 399; i++) averageVolume[i] = averageVolume[i + 1];

    averageVolume[399] = average;         // Adding last average value
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

// Initialization
//--------------------------------------------------------------------------------------
const screenWidth = 800;
const screenHeight = 450;

initWindow(screenWidth, screenHeight, "raylib [audio] example - processing mixed output");

initAudioDevice();              // Initialize audio device

attachAudioMixedProcessor(ProcessAudio);

let music = loadMusicStream("resources/country.mp3");
let sound = loadSound("resources/coin.wav");

playMusicStream(music);

setTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!windowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    updateMusicStream(music);   // Update music buffer with new stream data

    // Modify processing variables
    //----------------------------------------------------------------------------------
    if (isKeyPressed(KEY_LEFT)) exponent -= 0.05;
    if (isKeyPressed(KEY_RIGHT)) exponent += 0.05;

    if (exponent <= 0.5) exponent = 0.5;
    if (exponent >= 3) exponent = 3;

    if (isKeyPressed(KEY_SPACE)) playSound(sound);

    // Draw
    //----------------------------------------------------------------------------------
    beginDrawing();

        clearBackground(RAYWHITE);

        drawText("MUSIC SHOULD BE PLAYING!", 255, 150, 20, LIGHTGRAY);

        drawText(textFormat("EXPONENT = %.2f", exponent), 215, 180, 20, LIGHTGRAY);

        drawRectangle(199, 199, 402, 34, LIGHTGRAY);
        for (let i = 0; i < 400; i++){
            drawLine(201 + i, 232 - Math.floor(averageVolume[i] * 32), 201 + i, 232, MAROON);
        }
        drawRectangleLines(199, 199, 402, 34, GRAY);

        drawText("PRESS SPACE TO PLAY OTHER SOUND", 200, 250, 20, LIGHTGRAY);
        drawText("USE LEFT AND RIGHT ARROWS TO ALTER DISTORTION", 140, 280, 20, LIGHTGRAY);

    endDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
unloadMusicStream(music);   // Unload music stream buffers from RAM

detachAudioMixedProcessor(ProcessAudio);  // Disconnect audio processor

closeAudioDevice();         // Close audio device (music streaming is automatically stopped)

closeWindow();              // Close window and OpenGL context
//--------------------------------------------------------------------------------------*/