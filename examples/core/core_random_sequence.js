/*******************************************************************************************
*
*   raylib [core] example - Generates a random sequence
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example contributed by Dalton Overmyer (@REDl3east) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2025 Dalton Overmyer (@REDl3east)
*
********************************************************************************************/

import {
    BeginDrawing, BLACK, ClearBackground, CloseWindow,
    Color, DrawFPS,
    DrawRectangle, DrawRectangleRec,
    DrawText, EndDrawing,
    GetRandomValue, InitWindow, IsKeyPressed, KEY_DOWN, KEY_SPACE, KEY_UP,
    LoadRandomSequence,
    MeasureText, RAYWHITE,
    Rectangle,
    RED, SetTargetFPS, TextFormat, WindowShouldClose
} from "rayjs:raylib";
import {Remap} from "rayjs:raymath";

//------------------------------------------------------------------------------------
// Module functions declaration
//------------------------------------------------------------------------------------
function GenerateRandomColor(){
    return new Color(
        GetRandomValue(0, 255),
        GetRandomValue(0, 255),
        GetRandomValue(0, 255),
        255
    );
}
function GenerateRandomColorRectSequence(rectCount, rectWidth, screenWidth, screenHeight) {
    let rectangles = new Array(rectCount).fill().map(()=>{
        return {
            c: new Color(),
            r: new Rectangle()
        }
    });
    let seq = LoadRandomSequence(rectCount, 0, rectCount - 1);
    let rectSeqWidth = rectCount*rectWidth;
    let startX = (screenWidth - rectSeqWidth)*0.5;

    for (let i = 0; i < rectCount; i++) {
        let rectHeight = Math.floor(Remap(seq[i], 0, rectCount - 1, 0, screenHeight));

        rectangles[i].c = GenerateRandomColor();
        rectangles[i].r = new Rectangle( startX + i*rectWidth, screenHeight - rectHeight, rectWidth, rectHeight );
    }

    return rectangles;
}
function ShuffleColorRectSequence(rectangles, rectCount) {
    let seq = LoadRandomSequence(rectCount, 0, rectCount -  1);

    for (let i1 = 0; i1 < rectCount; i1++) {
        let r1 = rectangles[i1];
        let r2 = rectangles[seq[i1]];

        // Swap only the color and height
        let tmp = r1;
        r1.c = r2.c;
        r1.r.height = r2.r.height;
        r1.r.y = r2.r.y;
        r2.c = tmp.c;
        r2.r.height = tmp.r.height;
        r2.r.y = tmp.r.y;
    }
}
function DrawTextCenterKeyHelp( key, text, posX, posY, fontSize, color ) {
    let spaceSize = MeasureText(" ", fontSize);
    let pressSize = MeasureText("Press", fontSize);
    let keySize = MeasureText(key, fontSize);
    let textSize = MeasureText(text, fontSize);
    let textSizeCurrent = 0;

    DrawText("Press", posX, posY, fontSize, color);
    textSizeCurrent += pressSize + 2*spaceSize;
    DrawText(key, posX + textSizeCurrent, posY, fontSize, RED);
    DrawRectangle(posX + textSizeCurrent, posY + fontSize, keySize, 3, RED);
    textSizeCurrent += keySize + 2*spaceSize;
    DrawText(text, posX + textSizeCurrent, posY, fontSize, color);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    let screenWidth = 800;
    let screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - Generates a random sequence");

    let rectCount = 20;
    let rectSize = screenWidth/rectCount;
    let rectangles = GenerateRandomColorRectSequence(rectCount, rectSize, screenWidth, 0.75*screenHeight);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_SPACE)) ShuffleColorRectSequence(rectangles, rectCount);

        if (IsKeyPressed(KEY_UP)) {
            rectCount++;
            rectSize = screenWidth/rectCount;
            rectangles = GenerateRandomColorRectSequence(rectCount, rectSize, screenWidth, 0.75*screenHeight);
        }

        if (IsKeyPressed(KEY_DOWN)) {
            if (rectCount >= 4) {
                rectCount--;
                rectSize = screenWidth/rectCount;
                rectangles = GenerateRandomColorRectSequence(rectCount, rectSize, screenWidth, 0.75*screenHeight);
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            let fontSize = 20;
            for (let i = 0; i < rectCount; i++) {
                DrawRectangleRec(rectangles[i].r, rectangles[i].c);
                DrawTextCenterKeyHelp("SPACE", "to shuffle the sequence.", 10, screenHeight - 96, fontSize, BLACK);
                DrawTextCenterKeyHelp("UP", "to add a rectangle and generate a new sequence.", 10, screenHeight - 64, fontSize, BLACK);
                DrawTextCenterKeyHelp("DOWN", "to remove a rectangle and generate a new sequence.", 10, screenHeight - 32, fontSize, BLACK);
            }

            const rectCountText = TextFormat("%d rectangles", rectCount);
            let rectCountTextSize = MeasureText(rectCountText, fontSize);
            DrawText(rectCountText, screenWidth - rectCountTextSize - 10, 10, fontSize, BLACK);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}