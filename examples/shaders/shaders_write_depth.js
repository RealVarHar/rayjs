/*******************************************************************************************
*
*   raylib [shaders] example - Depth buffer writing
*
*   Example complexity rating: [★★☆☆] 2/4
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
import {InitWindow, LOG_INFO, LOG_WARNING, LoadShader, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, TextFormat, TraceLog, Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_ORBITAL, BeginTextureMode, ClearBackground, WHITE, BeginMode3D, BeginShaderMode, DrawCubeWiresV, DrawCubeV, DrawGrid, RED, PURPLE, DARKGREEN, YELLOW, EndShaderMode, EndMode3D, EndTextureMode, BeginDrawing, RAYWHITE, DrawTextureRec, Rectangle, Vector2, DrawFPS, EndDrawing, UnloadShader, CloseWindow
    ,RenderTexture as RenderTexture2D
} from 'rayjs:raylib';
import * as rg from 'rayjs:rlgl';

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
        console.log(1);
        rg.rlFramebufferAttach(target.id, target.texture.id, rg.RL_ATTACHMENT_COLOR_CHANNEL0, rg.RL_ATTACHMENT_TEXTURE2D, 0);
        console.log(2);
        rg.rlFramebufferAttach(target.id, target.depth.id, rg.RL_ATTACHMENT_DEPTH, rg.RL_ATTACHMENT_TEXTURE2D, 0);
        console.log(3);

        // Check if fbo is complete with attachments (valid)
        if (rg.rlFramebufferComplete(target.id)) TraceLog(LOG_INFO, "FBO: [ID "+target.id+"] Framebuffer object created successfully");
        console.log(4);
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

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - write depth buffer");

    // The shader inverts the depth buffer by writing into it by `gl_FragDepth = 1 - gl_FragCoord.z;`
    let shader = LoadShader(null, TextFormat("resources/shaders/glsl%i/write_depth.fs", GLSL_VERSION));

    // Use Customized function to create writable depth texture buffer
    let target = LoadRenderTextureDepthTex(screenWidth, screenHeight);

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 2, 2, 3 ),    // Camera position
    camera.target = new Vector3( 0, 0.5, 0 ),    // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 ),          // Camera up vector (rotation towards target)
    camera.fovy = 45,                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE       // Camera projection type
    
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        
        // Draw into our custom render texture (framebuffer)
        BeginTextureMode(target);
            ClearBackground(WHITE);
            
            BeginMode3D(camera);
                BeginShaderMode(shader);
                    DrawCubeWiresV( new Vector3( 0, 0.5, 1 ), new Vector3( 1, 1, 1 ), RED);
                    DrawCubeV( new Vector3( 0, 0.5, 1 ), new Vector3( 1, 1, 1 ), PURPLE);
                    DrawCubeWiresV( new Vector3( 0, 0.5, -1 ), new Vector3( 1, 1, 1 ), DARKGREEN);
                    DrawCubeV( new Vector3( 0, 0.5, -1 ), new Vector3( 1, 1, 1 ), YELLOW);
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
    UnloadShader(shader);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}