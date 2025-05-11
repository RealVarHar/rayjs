import {
    BeginDrawing, BeginMode3D, Camera3D, CAMERA_PERSPECTIVE, ClearBackground, CloseWindow, DARKGRAY, DrawCube, DrawCubeWires, DrawFPS, DrawGrid, DrawText, EndDrawing, EndMode3D, InitWindow, MAROON, RAYWHITE, RED, SetTargetFPS, Vector3, WindowShouldClose
} from "rayjs:raylib";
{

    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

    // Define the camera to look into our 3d world
    const position = new Vector3(0,10,10);
    const target = new Vector3(0,0,0);
    const up = new Vector3(0,1,0);
    const camera = new Camera3D(position,target,up, 45, CAMERA_PERSPECTIVE);

    const cubePosition = new Vector3(0,0,0);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawCube(cubePosition, 2.0, 2.0, 2.0, RED);
                DrawCubeWires(cubePosition, 2.0, 2.0, 2.0, MAROON);

                DrawGrid(10, 1.0);

            EndMode3D();

            DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}