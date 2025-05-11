/*******************************************************************************************
*
*   raylib [shaders] example - Shadowmap
*
*   Example complexity rating: [★★★★] 4/4
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example contributed by TheManTheMythTheGameDev (@TheManTheMythTheGameDev) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2025 TheManTheMythTheGameDev (@TheManTheMythTheGameDev)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {BLUE,
    BeginDrawing,
    BeginMode3D,
    RenderTexture as RenderTexture2D,
    BeginTextureMode,
    CAMERA_ORBITAL,
    CAMERA_ORTHOGRAPHIC,
    CAMERA_PERSPECTIVE,
    Camera3D, ClearBackground, CloseWindow, ColorNormalize, DrawModelEx, DrawText,
    EndDrawing, EndMode3D, EndTextureMode, FLAG_MSAA_4X_HINT,
    GRAY,
    GenMeshCube,
    GetFrameTime, GetShaderLocation, InitWindow, IsKeyDown,
    IsKeyPressed, KEY_DOWN, KEY_F, KEY_LEFT, KEY_RIGHT, KEY_UP, LOG_INFO, LOG_WARNING,
    LoadModel,
    LoadModelAnimations,
    LoadModelFromMesh,
    LoadShader, RAYWHITE, RED, SHADER_LOC_VECTOR_VIEW,
    SHADER_UNIFORM_INT,
    SHADER_UNIFORM_VEC3, SHADER_UNIFORM_VEC4, SetConfigFlags, SetShaderValue,
    SetShaderValueMatrix, SetTargetFPS, TakeScreenshot, TextFormat,
    TraceLog,
    UnloadModel,
    UnloadModelAnimations,
    UnloadShader,
    UpdateCamera, UpdateModelAnimation, Vector3, WHITE, WindowShouldClose} from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';
import * as rg from 'rayjs:rlgl';

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}

const SHADOWMAP_RESOLUTION = 1024;

function LoadShadowmapRenderTexture(width, height) {
    let target = new RenderTexture2D();

    target.id = rg.rlLoadFramebuffer(); // Load an empty framebuffer
    target.texture.width = width;
    target.texture.height = height;

    if (target.id > 0) {
        rg.rlEnableFramebuffer(target.id);

        // Create depth texture
        // We don't need a color texture for the shadowmap
        target.depth.id = rg.rlLoadTextureDepth(width, height, false);
        target.depth.width = width;
        target.depth.height = height;
        target.depth.format = 19;       //DEPTH_COMPONENT_24BIT?
        target.depth.mipmaps = 1;

        // Attach depth texture to FBO
        rg.rlFramebufferAttach(target.id, target.depth.id, rg.RL_ATTACHMENT_DEPTH, rg.RL_ATTACHMENT_TEXTURE2D, 0);

        // Check if fbo is complete with attachments (valid)
        if (rg.rlFramebufferComplete(target.id)) TraceLog(LOG_INFO, "FBO: [ID "+target.id+"] Framebuffer object created successfully");

        rg.rlDisableFramebuffer();
    }
    else TraceLog(LOG_WARNING, "FBO: Framebuffer object can not be created");

    return target;
}

// Unload shadowmap render texture from GPU memory (VRAM)
function UnloadShadowmapRenderTexture(target) {
    if (target.id > 0) {
        // NOTE: Depth texture/renderbuffer is automatically
        // queried and deleted before deleting framebuffer
        rg.rlUnloadFramebuffer(target.id);
    }
}

function DrawScene(cube, robot) {
    DrawModelEx(cube, rm.Vector3Zero(), new Vector3( 0, 1, 0 ), 0, new Vector3( 10, 1, 10 ), BLUE);
    DrawModelEx(cube, new Vector3( 1.5, 1, -1.5 ), new Vector3( 0, 1, 0 ), 0, rm.Vector3One(), WHITE);
    DrawModelEx(robot, new Vector3( 0, 0.5, 0 ), new Vector3( 0, 1, 0 ), 0, new Vector3( 1, 1, 1 ), RED);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    // Shadows are a HUGE topic, and this example shows an extremely simple implementation of the shadowmapping algorithm,
    // which is the industry standard for shadows. This algorithm can be extended in a ridiculous number of ways to improve
    // realism and also adapt it for different scenes. This is pretty much the simplest possible implementation.
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - shadowmap");

    let cam = new Camera3D();
    cam.position = new Vector3( 10, 10, 10 );
    cam.target = rm.Vector3Zero();
    cam.projection = CAMERA_PERSPECTIVE;
    cam.up = new Vector3( 0, 1, 0 );
    cam.fovy = 45;

    let shadowShader = LoadShader(TextFormat("resources/shaders/glsl%i/shadowmap.vs", GLSL_VERSION),
                                  TextFormat("resources/shaders/glsl%i/shadowmap.fs", GLSL_VERSION));
    shadowShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shadowShader, "viewPos");
    let lightDir = rm.Vector3Normalize(new Vector3( 0.35, -1, -0.35 ));
    let lightColor = WHITE;
    let lightColorNormalized = ColorNormalize(lightColor);
    let lightDirLoc = GetShaderLocation(shadowShader, "lightDir");
    let lightColLoc = GetShaderLocation(shadowShader, "lightColor");
    SetShaderValue(shadowShader, lightDirLoc, lightDir, SHADER_UNIFORM_VEC3);
    SetShaderValue(shadowShader, lightColLoc, lightColorNormalized, SHADER_UNIFORM_VEC4);
    let ambientLoc = GetShaderLocation(shadowShader, "ambient");
    let ambient = [0.1, 0.1, 0.1, 1];
    SetShaderValue(shadowShader, ambientLoc, ambient, SHADER_UNIFORM_VEC4);
    let lightVPLoc = GetShaderLocation(shadowShader, "lightVP");
    let shadowMapLoc = GetShaderLocation(shadowShader, "shadowMap");
    let shadowMapResolution = SHADOWMAP_RESOLUTION;
    SetShaderValue(shadowShader, GetShaderLocation(shadowShader, "shadowMapResolution"), shadowMapResolution, SHADER_UNIFORM_INT);

    let cube = LoadModelFromMesh(GenMeshCube(1, 1, 1));
    cube.materials[0].shader = shadowShader;
    let robot = LoadModel("resources/models/robot.glb");
    for (let i = 0; i < robot.materialCount; i++) {
        robot.materials[i].shader = shadowShader;
    }
    let animCount = [0];
    let robotAnimations = LoadModelAnimations("resources/models/robot.glb", animCount);
    animCount=animCount[0];

    let shadowMap = LoadShadowmapRenderTexture(SHADOWMAP_RESOLUTION, SHADOWMAP_RESOLUTION);
    // For the shadowmapping algorithm, we will be rendering everything from the light's point of view
    let lightCam = new Camera3D();
    lightCam.position = rm.Vector3Scale(lightDir, -15);
    lightCam.target = rm.Vector3Zero();
    // Use an orthographic projection for directional lights
    lightCam.projection = CAMERA_ORTHOGRAPHIC;
    lightCam.up = new Vector3( 0, 1, 0 );
    lightCam.fovy = 20;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    let fc = 0;

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        let dt = GetFrameTime();

        let cameraPos = cam.position;
        SetShaderValue(shadowShader, shadowShader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        UpdateCamera(cam, CAMERA_ORBITAL);

        fc++;
        fc %= (robotAnimations[0].frameCount);
        UpdateModelAnimation(robot, robotAnimations[0], fc);

        const cameraSpeed = 0.05;
        if (IsKeyDown(KEY_LEFT)) {
            if (lightDir.x < 0.6)
                lightDir.x += cameraSpeed * 60 * dt;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            if (lightDir.x > -0.6)
                lightDir.x -= cameraSpeed * 60 * dt;
        }
        if (IsKeyDown(KEY_UP)) {
            if (lightDir.z < 0.6)
                lightDir.z += cameraSpeed * 60 * dt;
        }
        if (IsKeyDown(KEY_DOWN)) {
            if (lightDir.z > -0.6)
                lightDir.z -= cameraSpeed * 60 * dt;
        }
        lightDir = rm.Vector3Normalize(lightDir);
        lightCam.position = rm.Vector3Scale(lightDir, -15);
        SetShaderValue(shadowShader, lightDirLoc, lightDir, SHADER_UNIFORM_VEC3);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        // First, render all objects into the shadowmap
        // The idea is, we record all the objects' depths (as rendered from the light source's point of view) in a buffer
        // Anything that is "visible" to the light is in light, anything that isn't is in shadow
        // We can later use the depth buffer when rendering everything from the player's point of view
        // to determine whether a given point is "visible" to the light

        // Record the light matrices for future use!
        let lightView;
        let lightProj;
        BeginTextureMode(shadowMap);
        ClearBackground(WHITE);
        BeginMode3D(lightCam);
            lightView = rg.rlGetMatrixModelview();
            lightProj = rg.rlGetMatrixProjection();
            DrawScene(cube, robot);
        EndMode3D();
        EndTextureMode();
        let lightViewProj = rm.MatrixMultiply(lightView, lightProj);

        ClearBackground(RAYWHITE);

        SetShaderValueMatrix(shadowShader, lightVPLoc, lightViewProj);

        rg.rlEnableShader(shadowShader.id);
        let slot = 10; // Can be anything 0 to 15, but 0 will probably be taken up
        rg.rlActiveTextureSlot(10);
        rg.rlEnableTexture(shadowMap.depth.id);
        rg.rlSetUniform(shadowMapLoc, slot, SHADER_UNIFORM_INT, 1);

        BeginMode3D(cam);

            // Draw the same exact things as we drew in the shadowmap!
            DrawScene(cube, robot);
        
        EndMode3D();

        DrawText("Shadows in raylib using the shadowmapping algorithm!", screenWidth - 320, screenHeight - 20, 10, GRAY);
        DrawText("Use the arrow keys to rotate the light!", 10, 10, 30, RED);

        EndDrawing();

        if (IsKeyPressed(KEY_F)) {
            TakeScreenshot("shaders_shadowmap.png");
        }
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadShader(shadowShader);
    UnloadModel(cube);
    UnloadModel(robot);
    UnloadModelAnimations(robotAnimations, animCount);
    UnloadShadowmapRenderTexture(shadowMap);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
