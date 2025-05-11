/*******************************************************************************************
*
*   raylib [models] example - Skybox loading and drawing
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.8, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {InitWindow, LOG_INFO, SHADER_LOC_MATRIX_PROJECTION, SHADER_LOC_MATRIX_VIEW,Texture as TextureCubemap, TraceLog, Vector3, Camera3D as Camera, CAMERA_PERSPECTIVE, GenMeshCube, LoadModelFromMesh, LoadShader, TextFormat, SetShaderValue, GetShaderLocation, MATERIAL_MAP_CUBEMAP, SHADER_UNIFORM_INT, LoadTexture, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, UnloadTexture, LoadImage, LoadTextureCubemap, CUBEMAP_LAYOUT_AUTO_DETECT, UnloadImage, DisableCursor, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_FIRST_PERSON, IsFileDropped, LoadDroppedFiles, IsFileExtension, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawModel, WHITE, DrawGrid, EndMode3D, DrawText, GetFileName, GetScreenHeight, BLACK, DrawFPS, EndDrawing, UnloadShader, UnloadModel, CloseWindow } from 'rayjs:raylib';
import * as rg from 'rayjs:rlgl';
import * as rm from 'rayjs:raymath'; // Required for: MatrixPerspective(), MatrixLookAt()

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}
const DEG2RAD = Math.PI/180;

// Generate cubemap (6 faces) from equirectangular (panorama) HDR texture
function GenTextureCubemap(shader, panorama, size, format) {
    let cubemap = new TextureCubemap();

    rg.rlDisableBackfaceCulling();     // Disable backface culling to render inside the cube

    // STEP 1: Setup framebuffer
    //------------------------------------------------------------------------------------------
    let rbo = rg.rlLoadTextureDepth(size, size, true);
    cubemap.id = rg.rlLoadTextureCubemap(null, size, format, 1);

    let fbo = rg.rlLoadFramebuffer();
    rg.rlFramebufferAttach(fbo, rbo, rg.RL_ATTACHMENT_DEPTH, rg.RL_ATTACHMENT_RENDERBUFFER, 0);
    rg.rlFramebufferAttach(fbo, cubemap.id, rg.RL_ATTACHMENT_COLOR_CHANNEL0, rg.RL_ATTACHMENT_CUBEMAP_POSITIVE_X, 0);

    // Check if framebuffer is complete with attachments (valid)
    if (rg.rlFramebufferComplete(fbo)) TraceLog(LOG_INFO, "FBO: [ID "+fbo+"] Framebuffer object created successfully");
    //------------------------------------------------------------------------------------------

    // STEP 2: Draw to framebuffer
    //------------------------------------------------------------------------------------------
    // NOTE: Shader is used to convert HDR equirectangular environment map to cubemap equivalent (6 faces)
    rg.rlEnableShader(shader.id);

    // Define projection matrix and send it to shader
    let matFboProjection = rm.MatrixPerspective(90.0*DEG2RAD, 1.0, rg.rlGetCullDistanceNear(), rg.rlGetCullDistanceFar());
    rg.rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_PROJECTION], matFboProjection);

    // Define view matrix for every side of the cubemap
    let fboViews = [
        rm.MatrixLookAt(new Vector3( 0, 0, 0 ), new Vector3(  1,  0,  0 ), new Vector3( 0, -1,  0 )),
        rm.MatrixLookAt(new Vector3( 0, 0, 0 ), new Vector3( -1,  0,  0 ), new Vector3( 0, -1,  0 )),
        rm.MatrixLookAt(new Vector3( 0, 0, 0 ), new Vector3(  0,  1,  0 ), new Vector3( 0,  0,  1 )),
        rm.MatrixLookAt(new Vector3( 0, 0, 0 ), new Vector3(  0, -1,  0 ), new Vector3( 0,  0, -1 )),
        rm.MatrixLookAt(new Vector3( 0, 0, 0 ), new Vector3(  0,  0,  1 ), new Vector3( 0, -1,  0 )),
        rm.MatrixLookAt(new Vector3( 0, 0, 0 ), new Vector3(  0,  0, -1 ), new Vector3( 0, -1,  0 ))
    ];

    rg.rlViewport(0, 0, size, size);   // Set viewport to current fbo dimensions

    // Activate and enable texture for drawing to cubemap faces
    rg.rlActiveTextureSlot(0);
    rg.rlEnableTexture(panorama.id);

    for (let i = 0; i < 6; i++) {
        // Set the view matrix for the current cube face
        rg.rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_VIEW], fboViews[i]);

        // Select the current cubemap face attachment for the fbo
        // WARNING: This function by default enables->attach->disables fbo!!!
        rg.rlFramebufferAttach(fbo, cubemap.id, rg.RL_ATTACHMENT_COLOR_CHANNEL0, rg.RL_ATTACHMENT_CUBEMAP_POSITIVE_X + i, 0);
        rg.rlEnableFramebuffer(fbo);

        // Load and draw a cube, it uses the current enabled texture
        rg.rlClearScreenBuffers();
        rg.rlLoadDrawCube();

        // ALTERNATIVE: Try to use internal batch system to draw the cube instead of rlLoadDrawCube
        // for some reason this method does not work, maybe due to cube triangles definition? normals pointing out?
        // TODO: Investigate this issue...
        //rlSetTexture(panorama.id); // WARNING: It must be called after enabling current framebuffer if using internal batch system!
        //rlClearScreenBuffers();
        //DrawCubeV(Vector3Zero(), Vector3One(), WHITE);
        //rlDrawRenderBatchActive();
    }
    //------------------------------------------------------------------------------------------

    // STEP 3: Unload framebuffer and reset state
    //------------------------------------------------------------------------------------------
    rg.rlDisableShader();          // Unbind shader
    rg.rlDisableTexture();         // Unbind texture
    rg.rlDisableFramebuffer();     // Unbind framebuffer
    rg.rlUnloadFramebuffer(fbo);   // Unload framebuffer (and automatically attached depth texture/renderbuffer)

    // Reset viewport dimensions to default
    rg.rlViewport(0, 0, rg.rlGetFramebufferWidth(), rg.rlGetFramebufferHeight());
    rg.rlEnableBackfaceCulling();
    //------------------------------------------------------------------------------------------

    cubemap.width = size;
    cubemap.height = size;
    cubemap.mipmaps = 1;
    cubemap.format = format;

    return cubemap;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - skybox loading and drawing");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 1, 1, 1 );    // Camera position
    camera.target = new Vector3( 4, 1, 4 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Load skybox model
    let cube = GenMeshCube(1, 1, 1);
    let skybox = LoadModelFromMesh(cube);

    // Set this to true to use an HDR Texture, Note that raylib must be built with HDR Support for this to work SUPPORT_FILEFORMAT_HDR
    let useHDR = false;

    // Load skybox shader and set required locations
    // NOTE: Some locations are automatically set at shader loading
    skybox.materials[0].shader = LoadShader(TextFormat("resources/shaders/glsl%i/skybox.vs", GLSL_VERSION),
                                            TextFormat("resources/shaders/glsl%i/skybox.fs", GLSL_VERSION));

    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "environmentMap"), MATERIAL_MAP_CUBEMAP, SHADER_UNIFORM_INT);
    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "doGamma"), useHDR ? 1 : 0, SHADER_UNIFORM_INT);
    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "vflipped"), useHDR ? 1 : 0, SHADER_UNIFORM_INT);

    // Load cubemap shader and setup required shader locations
    let shdrCubemap = LoadShader(TextFormat("resources/shaders/glsl%i/cubemap.vs", GLSL_VERSION),
                                 TextFormat("resources/shaders/glsl%i/cubemap.fs", GLSL_VERSION));

    SetShaderValue(shdrCubemap, GetShaderLocation(shdrCubemap, "equirectangularMap"), 0, SHADER_UNIFORM_INT);

    let skyboxFileName = "";
    
    if (useHDR) {
        skyboxFileName = "resources/dresden_square_2k.hdr";

        // Load HDR panorama (sphere) texture
        let panorama = LoadTexture(skyboxFileName);

        // Generate cubemap (texture with 6 quads-cube-mapping) from panorama HDR texture
        // NOTE 1: New texture is generated rendering to texture, shader calculates the sphere->cube coordinates mapping
        // NOTE 2: It seems on some Android devices WebGL, fbo does not properly support a FLOAT-based attachment,
        // despite texture can be successfully created.. so using PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 instead of PIXELFORMAT_UNCOMPRESSED_R32G32B32A32
        skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = GenTextureCubemap(shdrCubemap, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

        UnloadTexture(panorama);        // Texture not required anymore, cubemap already generated
    } else {
        let img = LoadImage("resources/skybox.png");
        skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);    // CUBEMAP_LAYOUT_PANORAMA
        UnloadImage(img);
    }

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_FIRST_PERSON);

        // Load new cubemap texture on drag&drop
        if (IsFileDropped()) {
            let droppedFiles = LoadDroppedFiles();

            if (droppedFiles.length == 1) {        // Only support one file dropped
                if (IsFileExtension(droppedFiles[0], ".png;.jpg;.hdr;.bmp;.tga")) {
                    // Unload current cubemap texture to load new one
                    UnloadTexture(skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
                    
                    if (useHDR) {
                        // Load HDR panorama (sphere) texture
                        let panorama = LoadTexture(droppedFiles[0]);

                        // Generate cubemap from panorama texture
                        skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = GenTextureCubemap(shdrCubemap, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
                        
                        UnloadTexture(panorama);    // Texture not required anymore, cubemap already generated
                    } else {
                        let img = LoadImage(droppedFiles[0]);
                        skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
                        UnloadImage(img);
                    }

                    skyboxFileName = droppedFiles[0];
                }
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                // We are inside the cube, we need to disable backface culling!
                rg.rlDisableBackfaceCulling();
                rg.rlDisableDepthMask();
                    DrawModel(skybox, new Vector3(0, 0, 0), 1, WHITE);
                rg.rlEnableBackfaceCulling();
                rg.rlEnableDepthMask();

                DrawGrid(10, 1);

            EndMode3D();

            if (useHDR) DrawText(TextFormat("Panorama image from hdrihaven.com: %s", GetFileName(skyboxFileName)), 10, GetScreenHeight() - 20, 10, BLACK);
            else DrawText(TextFormat(": %s", GetFileName(skyboxFileName)), 10, GetScreenHeight() - 20, 10, BLACK);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(skybox.materials[0].shader);
    UnloadTexture(skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);

    UnloadModel(skybox);        // Unload skybox model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
