import * as rl from 'raylib';
for (const key in rl) { globalThis[key] = rl[key] };

// Initialization
//--------------------------------------------------------------------------------------
const screenWidth = [800];
const screenHeight = [450];

setConfigFlags(FLAG_WINDOW_RESIZABLE);
initWindow(screenWidth, screenHeight, "raylib [shaders] example - raymarching shapes");

const position = new Vector3(2.5, 2.5, 3.0);        // Camera position
const target = new Vector3(0.0, 0.0, 0.7);          // Camera looking at point
const up = new Vector3(0.0, 1.0, 0.0);              // Camera up vector (rotation towards target)
const fovy = 65.0;                                  // Camera field-of-view Y
const projection = CAMERA_PERSPECTIVE;              // Camera projection type
const camera = new Camera3D(position,target, up, fovy, projection);

// Load raymarching shader
// NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
const shader = loadShader(null, "resources/shaders/glsl330/raymarching.fs");

// Get shader locations for required uniforms
const viewEyeLoc = getShaderLocation(shader, "viewEye");
const viewCenterLoc = getShaderLocation(shader, "viewCenter");
const runTimeLoc = getShaderLocation(shader, "runTime");
const resolutionLoc = getShaderLocation(shader, "resolution");

const scale = getWindowScaleDPI()
let resolution = [screenWidth[0], screenHeight[0]];
setShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

let runTime = 0.0;

disableCursor();                    // Limit cursor to relative movement inside the window
setTargetFPS(60);                   // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!windowShouldClose())        // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    updateCamera(camera, CAMERA_FIRST_PERSON);
	let cameraPos=[ camera.position.x, camera.position.y, camera.position.z ];
	let cameraTarget=[ camera.target.x, camera.target.y, camera.target.z ];

    const deltaTime = getFrameTime();
    runTime += deltaTime;

    // Set shader required uniform values
    setShaderValue(shader, viewEyeLoc, cameraPos, SHADER_UNIFORM_VEC3);
    setShaderValue(shader, viewCenterLoc, cameraTarget, SHADER_UNIFORM_VEC3);
    setShaderValue(shader, runTimeLoc, runTime, SHADER_UNIFORM_FLOAT);

    // Check if screen is resized
    if (isWindowResized())
    {
		resolution[0]=GetScreenWidth();
		resolution[1]=GetScreenHeight();
        setShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    beginDrawing();

        clearBackground(RAYWHITE);

        // We only draw a white full-screen rectangle,
        // frame is generated in shader using raymarching
        beginShaderMode(shader);
            drawRectangle(0, 0, getScreenWidth(), getScreenHeight(), WHITE);
        endShaderMode();

        drawText("(c) Raymarching shader by Iñigo Quilez. MIT License.", getScreenWidth() - 280, getScreenHeight() - 20, 10, BLACK);

    endDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
unloadShader(shader)
closeWindow();                  // Close window and OpenGL context
//--------------------------------------------------------------------------------------
