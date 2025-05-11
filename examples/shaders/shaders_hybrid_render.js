/*******************************************************************************************
*
*   raylib [shaders] example - Hybrid Rendering
*
*   Example complexity rating: [★★★★] 4/4
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example contributed by Buğra Alptekin Sarı (@BugraAlptekinSari) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2025 Buğra Alptekin Sarı (@BugraAlptekinSari)
*
********************************************************************************************/

import * as os from 'qjs:os';
import * as rg from 'rayjs:rlgl';
import * as rm from 'rayjs:raymath';
import {GetShaderLocation, InitWindow, LOG_INFO, LOG_WARNING, LoadShader, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
    SHADER_UNIFORM_VEC2, Camera3D as Camera,
    SetShaderValue, TextFormat, TraceLog, Vector2, Vector3, CAMERA_PERSPECTIVE, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_ORBITAL, BeginTextureMode, ClearBackground, WHITE, BeginShaderMode, DrawRectangleRec, Rectangle, EndShaderMode, BeginMode3D, DrawCubeWiresV, RED, PURPLE, DARKGREEN, YELLOW, DrawCubeV, DrawGrid, EndMode3D, EndTextureMode, BeginDrawing, RAYWHITE, DrawTextureRec, DrawFPS, EndDrawing, UnloadShader, CloseWindow } from 'rayjs:raylib';

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}

//------------------------------------------------------------------------------------
// Declare custom functions required for the example
//------------------------------------------------------------------------------------
// Load custom render texture, create a writable depth texture buffer
function LoadRenderTextureDepthTex(width, height) {
    let target = new RenderTexture2D();

    target.id = rg.rlLoadFramebuffer(); // Load an empty framebuffer

    if (target.id > 0) {
        rg.rlEnableFramebuffer(target.id);

        // Create color texture (default to RGBA)
        target.texture.id = rg.rlLoadTexture(null, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
        target.texture.width = width;
        target.texture.height = height;
        target.texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
        target.texture.mipmaps = 1;

        // Create depth texture buffer (instead of raylib default renderbuffer)
        target.depth.id = rg.rlLoadTextureDepth(width, height, false);
        target.depth.width = width;
        target.depth.height = height;
        target.depth.format = 19;       //DEPTH_COMPONENT_24BIT?
        target.depth.mipmaps = 1;

        // Attach color texture and depth texture to FBO
        rg.rlFramebufferAttach(target.id, target.texture.id, rg.RL_ATTACHMENT_COLOR_CHANNEL0, rg.RL_ATTACHMENT_TEXTURE2D, 0);
        rg.rlFramebufferAttach(target.id, target.depth.id, rg.RL_ATTACHMENT_DEPTH, rg.RL_ATTACHMENT_TEXTURE2D, 0);

        // Check if fbo is complete with attachments (valid)
        if (rg.rlFramebufferComplete(target.id)) TraceLog(LOG_INFO, "FBO: [ID "+target.id+"] Framebuffer object created successfully");

        rg.rlDisableFramebuffer();
    }
    else TraceLog(LOG_WARNING, "FBO: Framebuffer object can not be created");

    return target;
}
// Unload render texture from GPU memory (VRAM)
function UnloadRenderTextureDepthTex(target) {
    if (target.id > 0) {
        // Color texture attached to FBO is deleted
        rg.rlUnloadTexture(target.texture.id);
        rg.rlUnloadTexture(target.depth.id);

        // NOTE: Depth texture is automatically
        // queried and deleted before deleting framebuffer
        rg.rlUnloadFramebuffer(target.id);
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    const DEG2RAD = Math.PI/180;

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - write depth buffer");

    // This Shader calculates pixel depth and color using raymarch
    let shdrRaymarch = LoadShader(null, TextFormat("resources/shaders/glsl%i/hybrid_raymarch.fs", GLSL_VERSION));

    // This Shader is a standard rasterization fragment shader with the addition of depth writing
    // You are required to write depth for all shaders if one shader does it
    let shdrRaster = LoadShader(null, TextFormat("resources/shaders/glsl%i/hybrid_raster.fs", GLSL_VERSION));

    // Declare Struct used to store camera locs.
    let marchLocs = new RayLocs();

    // Fill the struct with shader locs.
    marchLocs.camPos = GetShaderLocation(shdrRaymarch, "camPos");
    marchLocs.camDir = GetShaderLocation(shdrRaymarch, "camDir");
    marchLocs.screenCenter = GetShaderLocation(shdrRaymarch, "screenCenter");

    // Transfer screenCenter position to shader. Which is used to calculate ray direction. 
    let screenCenter = new Vector2( screenWidth/2, screenHeight/2);
    SetShaderValue(shdrRaymarch, marchLocs.screenCenter , screenCenter , SHADER_UNIFORM_VEC2);

    // Use Customized function to create writable depth texture buffer
    let target = LoadRenderTextureDepthTex(screenWidth, screenHeight);

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 0.5, 1, 1.5 );    // Camera position
    camera.target = new Vector3( 0, 0.5, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;              // Camera projection type
    
    // Camera FOV is pre-calculated in the camera Distance.
    let camDist = 1/(Math.tan(camera.fovy*0.5*DEG2RAD));
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);

        // Update Camera Postion in the ray march shader.
        SetShaderValue(shdrRaymarch, marchLocs.camPos, camera.position, rg.RL_SHADER_UNIFORM_VEC3);
        
        // Update Camera Looking Vector. Vector length determines FOV.
        let camDir = rm.Vector3Scale(rm.Vector3Normalize(rm.Vector3Subtract(camera.target, camera.position)) , camDist);
        SetShaderValue(shdrRaymarch, marchLocs.camDir, camDir, rg.RL_SHADER_UNIFORM_VEC3);
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        // Draw into our custom render texture (framebuffer)
        BeginTextureMode(target);
            ClearBackground(WHITE);

            // Raymarch Scene
            rg.rlEnableDepthTest(); //Manually enable Depth Test to handle multiple rendering methods.
            BeginShaderMode(shdrRaymarch);
                DrawRectangleRec(new Rectangle(0,0, screenWidth, screenHeight),WHITE);
            EndShaderMode();
            
            // Rasterize Scene
            BeginMode3D(camera);
                BeginShaderMode(shdrRaster);
                    DrawCubeWiresV(new Vector3( 0, 0.5, 1 ), new Vector3( 1, 1, 1 ), RED);
                    DrawCubeV(new Vector3( 0, 0.5, 1 ), new Vector3( 1, 1, 1 ), PURPLE);
                    DrawCubeWiresV(new Vector3( 0, 0.5, -1 ), new Vector3( 1, 1, 1 ), DARKGREEN);
                    DrawCubeV(new Vector3( 0, 0.5, -1 ), new Vector3( 1, 1, 1 ), YELLOW);
                    DrawGrid(10, 1);
                EndShaderMode();
            EndMode3D();
        EndTextureMode();

        // Draw into screen our custom render texture 
        BeginDrawing();
            ClearBackground(RAYWHITE);
        
            DrawTextureRec(target.texture, new Rectangle( 0, 0, screenWidth, -screenHeight ), new Vector2( 0, 0 ), WHITE);
            DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTextureDepthTex(target);
    UnloadShader(shdrRaymarch);
    UnloadShader(shdrRaster);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}