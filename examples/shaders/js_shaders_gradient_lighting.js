import * as rl from 'rayjs:raylib';
import * as rlights from 'rayjs:rlights';
import * as raymath from 'rayjs:raymath';
for (const key in rl) { globalThis[key] = rl[key] };
for (const key in rlights) { globalThis[key] = rlights[key] };
for (const key in raymath) { globalThis[key] = raymath[key] };

/*******************************************************************************************
*
*   raylib [shaders] example - basic lighting
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3).
*
*   Example originally created with raylib 3.0, last time updated with raylib 4.2
*
*   Example contributed by Chris Camacho (@codifies) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2023 Chris Camacho (@codifies) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

const GLSL_VERSION = "330"

// Initialization
//--------------------------------------------------------------------------------------
const screenWidth = 800;
const screenHeight = 450;

SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
InitWindow(screenWidth, screenHeight, "raylib [shaders] example - basic lighting");

// Define the camera to look into our 3d world
const position = new Vector3(2.0,4.0,6.0);    // Camera position
const target = new Vector3(0.0,0.5,0.0);      // Camera looking at point
const up = new Vector3(0.0,1.0,0.0);          // Camera up vector (rotation towards target)
const fovy = 45.0;                                // Camera field-of-view Y
const projection = CAMERA_PERSPECTIVE;             // Camera projection type
const camera = new Camera3D(position,target,up,fovy,projection)

// Load plane model from a generated mesh
const floor = LoadModelFromMesh(GenMeshPlane(100.0, 100.0, 3, 3));
//const cube = loadModelFromMesh(genMeshCube(2.0, 4.0, 2.0));
const cube = LoadModel("resources/models/icosphere.glb")

const g1 = GenImageGradientLinear(128, 1, 90, YELLOW, DARKBLUE)
const g2 = GenImageGradientLinear(128, 1, 90, DARKBLUE, PURPLE)
const image = GenImageColor(256,1,WHITE)
const src = new Rectangle(0,0,128,1)
ImageDraw(image,g1,src,src,WHITE)
ImageDraw(image,g2,src,new Rectangle(128,0,128,1),WHITE)
const texture = LoadTextureFromImage(image)
UnloadImage(image)
UnloadImage(g1)
UnloadImage(g2)

// Load basic lighting shader
const shader = LoadShader(`resources/shaders/glsl${GLSL_VERSION}/lighting.vs`,
                            `resources/shaders/glsl${GLSL_VERSION}/lighting2.fs`);
// Get some required shader locations
const viewLoc = GetShaderLocation(shader, "viewPos")
// NOTE: "matModel" location name is automatically assigned on shader loading, 
// no need to get the location again if using that uniform name
//shader.locs[SHADER_LOC_MATRIX_MODEL] = getShaderLocation(shader, "matModel");

// Ambient light level (some basic lighting)
const ambientLoc = GetShaderLocation(shader, "ambient");
SetShaderValue(shader, ambientLoc, [0.1, 0.1, 0.1, 1.0], SHADER_UNIFORM_VEC4);

// Assign out lighting shader to model
const matModel = LoadMaterialDefault()
matModel.shader = shader
let materials = floor.materials;
materials[0]=matModel;
floor.materials=materials;
SetMaterialTexture(matModel, MATERIAL_MAP_DIFFUSE, texture)
const matCube = LoadMaterialDefault()
matCube.shader = shader
SetMaterialTexture(matCube, MATERIAL_MAP_DIFFUSE, texture);
materials = cube.materials;
materials[0]=matCube;
cube.materials=materials;

// Create lights
const light = CreateLight(LIGHT_POINT, new Vector3(-2,1,-2), Vector3Zero(), WHITE, shader)
light.attenuation *= 2 

SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())        // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(camera, CAMERA_ORBITAL);

    // Update the shader with the camera view vector (points towards { 0.0, 0.0, 0.0 })
    const cameraPos = [camera.position.x, camera.position.y, camera.position.z];
    SetShaderValue(shader, viewLoc, cameraPos, SHADER_UNIFORM_VEC3);
    
    // Check key inputs to enable/disable lights
    if (IsKeyPressed(KEY_Y)) { light.enabled = !light.enabled; }
    
    // Update light values (actually, only enable/disable them)
    UpdateLightValues(shader, light);
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

            DrawModel(floor, Vector3Zero(), 1.0, WHITE);
            DrawModel(cube, new Vector3(0,1,0), 1.0, WHITE);

            if (light.enabled) DrawSphereEx(light.position, 0.2, 8, 8, light.color);
            else DrawSphereWires(light.position, 0.2, 8, 8, ColorAlpha(light.color, 0.3));

            DrawGrid(10, 1.0);

        EndMode3D();

        DrawFPS(10, 10);

        DrawText("Use keys [Y] to toggle lights", 10, 40, 20, DARKGRAY);
        DrawTexturePro(texture, new Rectangle(0,0,256,1), new Rectangle(0,0,screenWidth, 32), Vector2Zero(), 0, WHITE)

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
UnloadModel(floor);     // Unload the model
UnloadModel(cube);      // Unload the model
UnloadShader(shader);   // Unload shader

CloseWindow();          // Close window and OpenGL context
//--------------------------------------------------------------------------------------


