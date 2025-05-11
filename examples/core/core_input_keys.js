import {
    BeginDrawing, ClearBackground, CloseWindow, DARKGRAY, DrawCircleV, DrawText, EndDrawing, InitWindow, IsKeyDown, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_UP, MAROON, RAYWHITE, SetTargetFPS, Vector2, WindowShouldClose
} from "rayjs:raylib";
{

    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    const ballPosition = new Vector2(screenWidth/2, screenHeight/2);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

            DrawCircleV(ballPosition, 50, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}