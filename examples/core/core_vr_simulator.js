/*******************************************************************************************
*
*   raylib [core] example - VR Simulator (Oculus Rift CV1 parameters)
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from "qjs:os";
import {
    BeginDrawing, BeginMode3D, BeginShaderMode, BeginTextureMode, BeginVrStereoMode, CAMERA_FIRST_PERSON, CAMERA_PERSPECTIVE, ClearBackground, CloseWindow, DisableCursor, DrawCube, DrawCubeWires, DrawFPS, DrawGrid, DrawTexturePro, EndDrawing, EndMode3D, EndShaderMode, EndTextureMode, EndVrStereoMode, GetScreenHeight, GetScreenWidth, GetShaderLocation, InitWindow, LoadRenderTexture, LoadShader, LoadVrStereoConfig, MAROON, RAYWHITE, Rectangle, RED, SetShaderValue, SetTargetFPS, SHADER_UNIFORM_VEC2, SHADER_UNIFORM_VEC4, TextFormat, UnloadRenderTexture, UnloadShader, UnloadVrStereoConfig, UpdateCamera, Vector2, Vector3, VrDeviceInfo, WHITE, WindowShouldClose, Camera3D as Camera
} from "rayjs:raylib";

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    // NOTE: screenWidth/screenHeight should match VR device aspect ratio
    InitWindow(screenWidth, screenHeight, "raylib [core] example - vr simulator");

    // VR device parameters definition
    let device = new VrDeviceInfo(// Oculus Rift CV1 parameters for simulator
        2160,     // Horizontal resolution in pixels
        1200,     // Vertical resolution in pixels
        0.133793, // Horizontal size in meters
        0.0669,   // Vertical size in meters
        0.041,    // Distance between eye and display in meters
        0.07,     // Lens separation distance in meters
        0.07,     // IPD (distance between pupils) in meters

        // NOTE: CV1 uses fresnel-hybrid-asymmetric lenses with specific compute shaders
        // Following parameters are just an approximation to CV1 distortion stereo rendering
        [1,0.22,0.24,0],      // Lens distortion constant parameters
        [0.996,-0.004,1.014,0]// Chromatic aberration correction parameters
    );

    // Load VR stereo config for VR device parameteres (Oculus Rift CV1 parameters)
    let config = LoadVrStereoConfig(device);

    // Distortion shader (uses device lens distortion and chroma)
    let distortion = LoadShader(null, TextFormat("resources/distortion%i.fs", GLSL_VERSION));

    // Update distortion shader with lens and distortion-scale parameters
    SetShaderValue(distortion, GetShaderLocation(distortion, "leftLensCenter"),
                   config.leftLensCenter, SHADER_UNIFORM_VEC2);
    SetShaderValue(distortion, GetShaderLocation(distortion, "rightLensCenter"),
                   config.rightLensCenter, SHADER_UNIFORM_VEC2);
    SetShaderValue(distortion, GetShaderLocation(distortion, "leftScreenCenter"),
                   config.leftScreenCenter, SHADER_UNIFORM_VEC2);
    SetShaderValue(distortion, GetShaderLocation(distortion, "rightScreenCenter"),
                   config.rightScreenCenter, SHADER_UNIFORM_VEC2);

    SetShaderValue(distortion, GetShaderLocation(distortion, "scale"),
                   config.scale, SHADER_UNIFORM_VEC2);
    SetShaderValue(distortion, GetShaderLocation(distortion, "scaleIn"),
                   config.scaleIn, SHADER_UNIFORM_VEC2);
    SetShaderValue(distortion, GetShaderLocation(distortion, "deviceWarpParam"),
                   device.lensDistortionValues, SHADER_UNIFORM_VEC4);
    SetShaderValue(distortion, GetShaderLocation(distortion, "chromaAbParam"),
                   device.chromaAbCorrection, SHADER_UNIFORM_VEC4);

    // Initialize framebuffer for stereo rendering
    // NOTE: Screen size should match HMD aspect ratio
    let target = LoadRenderTexture(device.hResolution, device.vResolution);

    // The target's height is flipped (in the source Rectangle), due to OpenGL reasons
    let sourceRec = new Rectangle( 0, 0, target.texture.width, -target.texture.height );
    let destRec = new Rectangle( 0, 0, GetScreenWidth(), GetScreenHeight() );

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 5, 2, 5 );    // Camera position
    camera.target = new Vector3( 0, 2, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector
    camera.fovy = 60;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;      // Camera projection type

    let cubePosition = new Vector3( 0, 0, 0 );

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_FIRST_PERSON);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            BeginVrStereoMode(config);
                BeginMode3D(camera);

                    DrawCube(cubePosition, 2, 2, 2, RED);
                    DrawCubeWires(cubePosition, 2, 2, 2, MAROON);
                    DrawGrid(40, 1);

                EndMode3D();
            EndVrStereoMode();
        EndTextureMode();
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginShaderMode(distortion);
                DrawTexturePro(target.texture, sourceRec, destRec, new Vector2( 0, 0 ), 0, WHITE);
            EndShaderMode();
            DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadVrStereoConfig(config);   // Unload stereo config

    UnloadRenderTexture(target);    // Unload stereo render fbo
    UnloadShader(distortion);       // Unload distortion shader

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}