import * as rl from 'rayjs:raylib';
for (const key in rl) { globalThis[key] = rl[key] };

const screenWidth = 800;
const screenHeight = 450;

InitWindow(screenWidth, screenHeight, "raylib [js] example - project folder");

const logo = LoadTexture("assets/raylib_512x512.png")

SetTargetFPS(60);
while (!WindowShouldClose())
{
    const offset = Math.sin(GetTime())*50
    BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(logo, (screenWidth/2) - (logo.width/2), (screenHeight/2) - (logo.height/2) + offset, WHITE)

        DrawText("This is an example for loading a folder!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}
UnloadTexture(logo)
CloseWindow();
