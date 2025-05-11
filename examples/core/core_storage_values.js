/*******************************************************************************************
*
*   raylib [core] example - Storage save/load values
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.4, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
//Note: LoadFileData, SaveFileData normally save void* binary data, so they expect Buffer

import {
    BeginDrawing, BLACK, ClearBackground, CloseWindow, DrawText, EndDrawing,
    GetRandomValue,
    InitWindow, IsKeyPressed, KEY_ENTER, KEY_R, KEY_SPACE, LIGHTGRAY, LIME,
    LoadFileData,
    LOG_INFO,
    LOG_WARNING, MAROON, RAYWHITE,
    SaveFileData,
    SetTargetFPS, TextFormat,
    TraceLog,
    WindowShouldClose
} from "rayjs:raylib";

const STORAGE_DATA_FILE = "storage.data";   // Storage file

// NOTE: Storage positions must start with 0, directly related to file memory layout
const STORAGE_POSITION_SCORE = 0;
const STORAGE_POSITION_HISCORE = 1;

// Persistent storage functions
// Save integer value to storage file (to defined position)
// NOTE: Storage positions is directly related to file memory layout (4 bytes each integer)
function SaveStorageValue( position, value ) {
    let success = false;
    let dataSize = [0];
    let fileData = new Int32Array(LoadFileData(STORAGE_DATA_FILE, dataSize));
    let newFileData = null;

    if (fileData != null) {
        if (fileData.length <= position) {
            // Increase data size up to position and store value
            let newFileData = new Int32Array(position + 1);
            for(let i=0;i<fileData.length;i++){
                newFileData[i]=fileData[i];
            }
            newFileData[position] = value;
        } else {
            // Store the old size of the file
            newFileData = fileData;
            newFileData[position] = value;
        }

        success = SaveFileData(STORAGE_DATA_FILE, newFileData.buffer, newFileData.buffer.byteLength);
        newFileData = null;

        TraceLog(LOG_INFO, `FILEIO: [${STORAGE_DATA_FILE}] Saved storage value: ${value}`);
    } else {
        TraceLog(LOG_INFO, `FILEIO: [${STORAGE_DATA_FILE}] File created successfully`);

        fileData = new Int32Array(position + 1);
        fileData[position] = value;

        success = SaveFileData(STORAGE_DATA_FILE, fileData, fileData.buffer.byteLength);

        TraceLog(LOG_INFO, `FILEIO: [${STORAGE_DATA_FILE}}] Saved storage value: ${value}`);
    }

    return success;
}

// Load integer value from storage file (from defined position)
// NOTE: If requested position could not be found, value 0 is returned
function LoadStorageValue(position) {
    let value = 0;
    let dataSize = [0];
    let fileData = new Int32Array(LoadFileData(STORAGE_DATA_FILE, dataSize));

    if (fileData != null) {
        if (fileData.length < position) {
            TraceLog(LOG_WARNING, `FILEIO: [${STORAGE_DATA_FILE}}] Failed to find storage position: ${position}`);
        } else {
            value = fileData[position];
        }

        TraceLog(LOG_INFO, `FILEIO: [${STORAGE_DATA_FILE}}] Loaded storage value: ${value}`);
    }

    return value;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - storage save/load values");

    let score = 0;
    let hiscore = 0;
    let framesCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_R)) {
            score = GetRandomValue(1000, 2000);
            hiscore = GetRandomValue(2000, 4000);
        }

        if (IsKeyPressed(KEY_ENTER)) {
            SaveStorageValue(STORAGE_POSITION_SCORE, score);
            SaveStorageValue(STORAGE_POSITION_HISCORE, hiscore);

        } else if (IsKeyPressed(KEY_SPACE)) {
            // NOTE: If requested position could not be found, value 0 is returned
            score = LoadStorageValue(STORAGE_POSITION_SCORE);
            hiscore = LoadStorageValue(STORAGE_POSITION_HISCORE);
        }

        framesCounter++;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText(TextFormat("SCORE: %i", score), 280, 130, 40, MAROON);
            DrawText(TextFormat("HI-SCORE: %i", hiscore), 210, 200, 50, BLACK);

            DrawText(TextFormat("frames: %i", framesCounter), 10, 10, 20, LIME);

            DrawText("Press R to generate random numbers", 220, 40, 20, LIGHTGRAY);
            DrawText("Press ENTER to SAVE values", 250, 310, 20, LIGHTGRAY);
            DrawText("Press SPACE to LOAD values", 252, 350, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}