import * as rl from 'rayjs:raylib';
for (const key in rl) { globalThis[key] = rl[key] };

// Initialization
//--------------------------------------------------------------------------------------
const screenWidth = 800;
const screenHeight = 450;

InitWindow(screenWidth, screenHeight, "raylib [core] example - input mouse wheel");

let boxPositionY = screenHeight/2 - 40;
let scrollSpeed = 4;            // Scrolling speed in pixels

SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    boxPositionY -= (GetMouseWheelMove()*scrollSpeed);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(screenWidth/2 - 40, boxPositionY, 80, 80, MAROON);

        DrawText("Use mouse wheel to move the cube up and down!", 10, 10, 20, GRAY);
        DrawText("Box position Y: " + boxPositionY, 10, 40, 20, LIGHTGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
