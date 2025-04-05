import * as rl from 'rayjs:raylib';
{
    for (const key in rl) { globalThis[key] = rl[key] };

    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = [800];
    const screenHeight = [450];

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - raymarching shapes");

    const position = new Vector3(2.5, 2.5, 3.0);        // Camera position
    const target = new Vector3(0.0, 0.0, 0.7);          // Camera looking at point
    const up = new Vector3(0.0, 1.0, 0.0);              // Camera up vector (rotation towards target)
    const fovy = 65.0;                                  // Camera field-of-view Y
    const projection = CAMERA_PERSPECTIVE;              // Camera projection type
    const camera = new Camera3D(position,target, up, fovy, projection);

    // Load raymarching shader
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    const shader = LoadShader(null, "resources/shaders/glsl330/raymarching.fs");

    // Get shader locations for required uniforms
    const viewEyeLoc = GetShaderLocation(shader, "viewEye");
    const viewCenterLoc = GetShaderLocation(shader, "viewCenter");
    const runTimeLoc = GetShaderLocation(shader, "runTime");
    const resolutionLoc = GetShaderLocation(shader, "resolution");

    const scale = GetWindowScaleDPI()
    let resolution = [screenWidth[0], screenHeight[0]];
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    let runTime = 0.0;

    DisableCursor();                    // Limit cursor to relative movement inside the window
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_FIRST_PERSON);
    	let cameraPos=[ camera.position.x, camera.position.y, camera.position.z ];
    	let cameraTarget=[ camera.target.x, camera.target.y, camera.target.z ];

        const deltaTime = GetFrameTime();
        runTime += deltaTime;

        // Set shader required uniform values
        SetShaderValue(shader, viewEyeLoc, cameraPos, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, viewCenterLoc, cameraTarget, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, runTimeLoc, runTime, SHADER_UNIFORM_FLOAT);

        // Check if screen is resized
        if (IsWindowResized())
        {
    		resolution[0]=GetScreenWidth();
    		resolution[1]=GetScreenHeight();
            SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // We only draw a white full-screen rectangle,
            // frame is generated in shader using raymarching
            BeginShaderMode(shader);
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            EndShaderMode();

            DrawText("(c) Raymarching shader by Iñigo Quilez. MIT License.", GetScreenWidth() - 280, GetScreenHeight() - 20, 10, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader)
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}