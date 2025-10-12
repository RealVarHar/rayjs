/*******************************************************************************************
*
*   raylib [shaders] example - deferred rendering
*
*   Example complexity rating: [★★★★] 4/4
*
*   NOTE: This example requires raylib OpenGL 3.3 or OpenGL ES 3.0
*
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by Justin Andreas Lacoste (@27justin) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2025 Justin Andreas Lacoste (@27justin)
*
********************************************************************************************/

import { InitWindow, Camera3D as Camera,Texture as Texture2D, Vector3, CAMERA_PERSPECTIVE, LoadModelFromMesh, GenMeshPlane, LoadShader, TextFormat, SHADER_LOC_VECTOR_VIEW, GetShaderLocation, TraceLog, LOG_WARNING, SetShaderValue, YELLOW, RED, GREEN, BLUE, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_ORBITAL, SHADER_UNIFORM_VEC3, IsKeyPressed, KEY_Y, KEY_R, KEY_G, KEY_B, KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, BeginDrawing, BeginMode3D, DrawModel, WHITE, DrawModelEx, EndMode3D, DrawSphereWires, DrawSphereEx, ColorAlpha, DrawText, DARKGREEN, DrawTextureRec, Rectangle, DARKGRAY, DrawFPS, EndDrawing, UnloadModel, UnloadShader, CloseWindow, GenMeshCube, RAYWHITE } from 'rayjs:raylib';
import * as os from 'qjs:os';
import * as rg from 'rayjs:rlgl';
import * as rm from 'rayjs:raymath';
import * as rli from 'rayjs:rlights';

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}

const MAX_CUBES = 30;

// Deferred mode passes
const DEFERRED_POSITION = 0;
const DEFERRED_NORMAL = 1;
const DEFERRED_ALBEDO = 2;
const DEFERRED_SHADING = 3;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    // -------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - deferred render");

    let camera = new Camera();
    camera.position = new Vector3( 5, 4, 5 );    // Camera position
    camera.target = new Vector3( 0, 1, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 60;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;      // Camera projection type

    // Load plane model from a generated mesh
    let model = LoadModelFromMesh(GenMeshPlane(10, 10, 3, 3));
    let cube = LoadModelFromMesh(GenMeshCube(2, 2, 2));

    // Load geometry buffer (G-buffer) shader and deferred shader
    let gbufferShader = LoadShader(TextFormat("resources/shaders/glsl%i/gbuffer.vs", GLSL_VERSION),
                        TextFormat("resources/shaders/glsl%i/gbuffer.fs", GLSL_VERSION));

    let deferredShader = LoadShader(TextFormat("resources/shaders/glsl%i/deferred_shading.vs", GLSL_VERSION),
                         TextFormat("resources/shaders/glsl%i/deferred_shading.fs", GLSL_VERSION));
    deferredShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(deferredShader, "viewPosition");

    // Initialize the G-buffer
    let gBuffer = {};
    gBuffer.framebuffer = rg.rlLoadFramebuffer();

    if (!gBuffer.framebuffer) {
        throw new Error("Failed to create framebuffer");
    }

    rg.rlEnableFramebuffer(gBuffer.framebuffer);

    // NOTE: Vertex positions are stored in a texture for simplicity. A better approach would use a depth texture
    // (instead of a detph renderbuffer) to reconstruct world positions in the final render shader via clip-space position, 
    // depth, and the inverse view/projection matrices.

    // 16-bit precision ensures OpenGL ES 3 compatibility, though it may lack precision for real scenarios. 
    // But as mentioned above, the positions could be reconstructed instead of stored. If not targeting OpenGL ES
    // and you wish to maintain this approach, consider using `RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32`.
    gBuffer.positionTexture = rg.rlLoadTexture(null, screenWidth, screenHeight, rg.RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16, 1);

    // Similarly, 16-bit precision is used for normals ensures OpenGL ES 3 compatibility.
    // This is generally sufficient, but a 16-bit fixed-point format offer a better uniform precision in all orientations.
    gBuffer.normalTexture = rg.rlLoadTexture(null, screenWidth, screenHeight, rg.RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16, 1);

    // Albedo (diffuse color) and specular strength can be combined into one texture.
    // The color in RGB, and the specular strength in the alpha channel.
    gBuffer.albedoSpecTexture = rg.rlLoadTexture(null, screenWidth, screenHeight, rg.RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);

    // Activate the draw buffers for our framebuffer
    rg.rlActiveDrawBuffers(3);

    // Now we attach our textures to the framebuffer.
    rg.rlFramebufferAttach(gBuffer.framebuffer, gBuffer.positionTexture, rg.RL_ATTACHMENT_COLOR_CHANNEL0, rg.RL_ATTACHMENT_TEXTURE2D, 0);
    rg.rlFramebufferAttach(gBuffer.framebuffer, gBuffer.normalTexture, rg.RL_ATTACHMENT_COLOR_CHANNEL1, rg.RL_ATTACHMENT_TEXTURE2D, 0);
    rg.rlFramebufferAttach(gBuffer.framebuffer, gBuffer.albedoSpecTexture, rg.RL_ATTACHMENT_COLOR_CHANNEL2, rg.RL_ATTACHMENT_TEXTURE2D, 0);

    // Finally we attach the depth buffer.
    gBuffer.depthRenderbuffer = rg.rlLoadTextureDepth(screenWidth, screenHeight, true);
    rg.rlFramebufferAttach(gBuffer.framebuffer, gBuffer.depthRenderbuffer, rg.RL_ATTACHMENT_DEPTH, rg.RL_ATTACHMENT_RENDERBUFFER, 0);

    // Make sure our framebuffer is complete.
    // NOTE: rlFramebufferComplete() automatically unbinds the framebuffer, so we don't have
    // to rlDisableFramebuffer() here.
    if (!rg.rlFramebufferComplete(gBuffer.framebuffer)) {
        TraceLog(LOG_WARNING, "Framebuffer is not complete");
    }

    // Now we initialize the sampler2D uniform's in the deferred shader.
    // We do this by setting the uniform's values to the texture units that
    // we later bind our g-buffer textures to.
    rg.rlEnableShader(deferredShader.id);
        let texUnitPosition = 0;
        let texUnitNormal = 1;
        let texUnitAlbedoSpec = 2;
        SetShaderValue(deferredShader, rg.rlGetLocationUniform(deferredShader.id, "gPosition"), [texUnitPosition], rg.RL_SHADER_UNIFORM_SAMPLER2D);
        SetShaderValue(deferredShader, rg.rlGetLocationUniform(deferredShader.id, "gNormal"), [texUnitNormal], rg.RL_SHADER_UNIFORM_SAMPLER2D);
        SetShaderValue(deferredShader, rg.rlGetLocationUniform(deferredShader.id, "gAlbedoSpec"), [texUnitAlbedoSpec], rg.RL_SHADER_UNIFORM_SAMPLER2D);
    rg.rlDisableShader();

    // Assign out lighting shader to model
    model.materials[0].shader = gbufferShader;
    cube.materials[0].shader = gbufferShader;

    // Create lights
    //--------------------------------------------------------------------------------------
    let lights = new Array(rli.MAX_LIGHTS);
    lights[0] = rli.CreateLight(rli.LIGHT_POINT, new Vector3( -2, 1, -2 ), rm.Vector3Zero(), YELLOW, deferredShader);
    lights[1] = rli.CreateLight(rli.LIGHT_POINT, new Vector3(  2, 1,  2 ), rm.Vector3Zero(), RED, deferredShader);
    lights[2] = rli.CreateLight(rli.LIGHT_POINT, new Vector3( -2, 1,  2 ), rm.Vector3Zero(), GREEN, deferredShader);
    lights[3] = rli.CreateLight(rli.LIGHT_POINT, new Vector3(  2, 1, -2 ), rm.Vector3Zero(), BLUE, deferredShader);

    const CUBE_SCALE = 0.25;
    let cubePositions = new Array(MAX_CUBES);
    let cubeRotations = new Array(MAX_CUBES);
    
    for (let i = 0; i < MAX_CUBES; i++) {
        cubePositions[i] = new Vector3( Math.random()*10 - 5, Math.random()*5, Math.random()*10 - 5 );
        
        cubeRotations[i] = Math.random()*360;
    }

    let mode = DEFERRED_SHADING;

    rg.rlEnableDepthTest();

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);

        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        let cameraPos = [ camera.position.x, camera.position.y, camera.position.z ];
        SetShaderValue(deferredShader, deferredShader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        
        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_Y)) { lights[0].enabled = !lights[0].enabled; }
        if (IsKeyPressed(KEY_R)) { lights[1].enabled = !lights[1].enabled; }
        if (IsKeyPressed(KEY_G)) { lights[2].enabled = !lights[2].enabled; }
        if (IsKeyPressed(KEY_B)) { lights[3].enabled = !lights[3].enabled; }

        // Check key inputs to switch between G-buffer textures
        if (IsKeyPressed(KEY_ONE)) mode = DEFERRED_POSITION;
        if (IsKeyPressed(KEY_TWO)) mode = DEFERRED_NORMAL;
        if (IsKeyPressed(KEY_THREE)) mode = DEFERRED_ALBEDO;
        if (IsKeyPressed(KEY_FOUR)) mode = DEFERRED_SHADING;

        // Update light values (actually, only enable/disable them)
        for (let i = 0; i < rli.MAX_LIGHTS; i++) rli.UpdateLightValues(deferredShader, lights[i]);
        //----------------------------------------------------------------------------------

        // Draw
        // ---------------------------------------------------------------------------------
        BeginDrawing();

            // Draw to the geometry buffer by first activating it
            rg.rlEnableFramebuffer(gBuffer.framebuffer);
            rg.rlClearColor(0, 0, 0, 0);
            rg.rlClearScreenBuffers();  // Clear color and depth buffer

            rg.rlDisableColorBlend();
            BeginMode3D(camera);
                // NOTE: We have to use rlEnableShader here. `BeginShaderMode` or thus `rlSetShader`
                // will not work, as they won't immediately load the shader program.
                rg.rlEnableShader(gbufferShader.id);
                    // When drawing a model here, make sure that the material's shaders
                    // are set to the gbuffer shader!
                    DrawModel(model, rm.Vector3Zero(), 1, WHITE);
                    DrawModel(cube, new Vector3( 0.0, 1, 0.0 ), 1, WHITE);

                    for (let i = 0; i < MAX_CUBES; i++) {
                        let position = cubePositions[i];
                        DrawModelEx(cube, position, new Vector3( 1, 1, 1 ), cubeRotations[i], new Vector3( CUBE_SCALE, CUBE_SCALE, CUBE_SCALE ), WHITE);
                    }

            rg.rlDisableShader();
            EndMode3D();
            rg.rlEnableColorBlend();

            // Go back to the default framebuffer (0) and draw our deferred shading.
            rg.rlDisableFramebuffer();
            rg.rlClearScreenBuffers(); // Clear color & depth buffer

            switch (mode) {
                case DEFERRED_SHADING: {
                    BeginMode3D(camera);
                        rg.rlDisableColorBlend();
                        rg.rlEnableShader(deferredShader.id);
                            // Bind our g-buffer textures
                            // We are binding them to locations that we earlier set in sampler2D uniforms `gPosition`, `gNormal`,
                            // and `gAlbedoSpec`
                            rg.rlActiveTextureSlot(texUnitPosition);
                            rg.rlEnableTexture(gBuffer.positionTexture);
                            rg.rlActiveTextureSlot(texUnitNormal);
                            rg.rlEnableTexture(gBuffer.normalTexture);
                            rg.rlActiveTextureSlot(texUnitAlbedoSpec);
                            rg.rlEnableTexture(gBuffer.albedoSpecTexture);

                            // Finally, we draw a fullscreen quad to our default framebuffer
                            // This will now be shaded using our deferred shader
                            rg.rlLoadDrawQuad();
                        rg.rlDisableShader();
                        rg.rlEnableColorBlend();
                    EndMode3D();

                    // As a last step, we now copy over the depth buffer from our g-buffer to the default framebuffer.
                    rg.rlBindFramebuffer(rg.RL_READ_FRAMEBUFFER, gBuffer.framebuffer);
                    rg.rlBindFramebuffer(rg.RL_DRAW_FRAMEBUFFER, 0);
                    rg.rlBlitFramebuffer(0, 0, screenWidth, screenHeight, 0, 0, screenWidth, screenHeight, 0x00000100);    // GL_DEPTH_BUFFER_BIT
                    rg.rlDisableFramebuffer();

                    // Since our shader is now done and disabled, we can draw spheres
                    // that represent light positions in default forward rendering
                    BeginMode3D(camera);
                        rg.rlEnableShader(rg.rlGetShaderIdDefault());
                            for (let i = 0; i < rli.MAX_LIGHTS; i++) {
                                if (lights[i].enabled) DrawSphereEx(lights[i].position, 0.2, 8, 8, lights[i].color);
                                else DrawSphereWires(lights[i].position, 0.2, 8, 8, ColorAlpha(lights[i].color, 0.3));
                            }
                        rg.rlDisableShader();
                    EndMode3D();
                    
                    DrawText("FINAL RESULT", 10, screenHeight - 30, 20, DARKGREEN);
                } break;
                case DEFERRED_POSITION: {
                    let texture = new Texture2D();
                    texture.id = gBuffer.positionTexture;
                    texture.width = screenWidth;
                    texture.height = screenHeight;
                    DrawTextureRec(texture, new Rectangle( 0, 0, screenWidth, -screenHeight ), rm.Vector2Zero(), RAYWHITE);
                    
                    DrawText("POSITION TEXTURE", 10, screenHeight - 30, 20, DARKGREEN);
                } break;
                case DEFERRED_NORMAL: {
                    let texture = new Texture2D();
                    texture.id = gBuffer.normalTexture;
                    texture.width = screenWidth;
                    texture.height = screenHeight;
                    DrawTextureRec(texture, new Rectangle( 0, 0, screenWidth, -screenHeight ), rm.Vector2Zero(), RAYWHITE);
                    
                    DrawText("NORMAL TEXTURE", 10, screenHeight - 30, 20, DARKGREEN);
                } break;
                case DEFERRED_ALBEDO: {
                    let texture = new Texture2D();
                    texture.id = gBuffer.albedoSpecTexture;
                    texture.width = screenWidth;
                    texture.height = screenHeight;
                    DrawTextureRec(texture, new Rectangle( 0, 0, screenWidth, -screenHeight ), rm.Vector2Zero(), RAYWHITE);
                    
                    DrawText("ALBEDO TEXTURE", 10, screenHeight - 30, 20, DARKGREEN);
                } break;
                default: break;
            }

            DrawText("Toggle lights keys: [Y][R][G][B]", 10, 40, 20, DARKGRAY);
            DrawText("Switch G-buffer textures: [1][2][3][4]", 10, 70, 20, DARKGRAY);

            DrawFPS(10, 10);
            
        EndDrawing();
        // -----------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model);     // Unload the models
    UnloadModel(cube);

    UnloadShader(deferredShader); // Unload shaders
    UnloadShader(gbufferShader);

    // Unload geometry buffer and all attached textures
    rg.rlUnloadFramebuffer(gBuffer.framebuffer);
    rg.rlUnloadTexture(gBuffer.positionTexture);
    rg.rlUnloadTexture(gBuffer.normalTexture);
    rg.rlUnloadTexture(gBuffer.albedoSpecTexture);
    rg.rlUnloadTexture(gBuffer.depthRenderbuffer);

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
