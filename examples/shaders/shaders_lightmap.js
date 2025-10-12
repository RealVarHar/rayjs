/*******************************************************************************************
*
*   raylib [shaders] example - lightmap
*
*   Example complexity rating: [★★★☆] 3/4
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3).
*
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by Jussi Viitala (@nullstare) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Jussi Viitala (@nullstare) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {FLAG_MSAA_4X_HINT, InitWindow, SetConfigFlags, Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, GenMeshPlane, SHADER_LOC_VERTEX_TEXCOORD02, LoadShader, TextFormat, LoadTexture, GenTextureMipmaps, SetTextureFilter, TEXTURE_FILTER_TRILINEAR, LoadRenderTexture, LoadMaterialDefault, MATERIAL_MAP_ALBEDO, MATERIAL_MAP_METALNESS, BeginTextureMode, ClearBackground, BLACK, BeginBlendMode, BLEND_ADDITIVE, DrawTexturePro, Rectangle, Vector2, RED, BLUE, GREEN, BLEND_ALPHA, EndTextureMode, SetTargetFPS, WindowShouldClose, CAMERA_ORBITAL, UpdateCamera, BeginDrawing, RAYWHITE, BeginMode3D, DrawMesh, EndMode3D, DrawFPS, GetRenderWidth, WHITE, GRAY, DrawText, EndDrawing, UnloadMesh, UnloadShader, UnloadTexture, CloseWindow } from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';
import * as rg from 'rayjs:rlgl';

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}

const MAP_SIZE = 10;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - lightmap");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 4, 6, 8 );    // Camera position
    camera.target = new Vector3( 0, 0, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    let mesh = GenMeshPlane(MAP_SIZE, MAP_SIZE, 1, 1);

    // GenMeshPlane doesn't generate texcoords2 so we will upload them separately
    mesh.texcoords2 = new Float32Array(mesh.vertexCount*2);

    // X                       // Y
    mesh.texcoords2[0] = 0;    mesh.texcoords2[1] = 0;
    mesh.texcoords2[2] = 1;    mesh.texcoords2[3] = 0;
    mesh.texcoords2[4] = 0;    mesh.texcoords2[5] = 1;
    mesh.texcoords2[6] = 1;    mesh.texcoords2[7] = 1;

    // Load a new texcoords2 attributes buffer
    mesh.vboId[SHADER_LOC_VERTEX_TEXCOORD02] = rg.rlLoadVertexBuffer(new Float32Array(mesh.texcoords2),mesh.vertexCount*2*Float32Array.BYTES_PER_ELEMENT, false);
    rg.rlEnableVertexArray(mesh.vaoId);
    
    // Index 5 is for texcoords2
    rg.rlSetVertexAttribute(5, 2, rg.RL_FLOAT, false, 0, 0);
    rg.rlEnableVertexAttribute(5);
    rg.rlDisableVertexArray();

    // Load lightmap shader
    let shader = LoadShader(TextFormat("resources/shaders/glsl%i/lightmap.vs", GLSL_VERSION),
                            TextFormat("resources/shaders/glsl%i/lightmap.fs", GLSL_VERSION));

    let texture = LoadTexture("resources/cubicmap_atlas.png");
    let light = LoadTexture("resources/spark_flame.png");

    GenTextureMipmaps(texture);
    SetTextureFilter(texture, TEXTURE_FILTER_TRILINEAR);

    let lightmap = LoadRenderTexture(MAP_SIZE, MAP_SIZE);

    SetTextureFilter(lightmap.texture, TEXTURE_FILTER_TRILINEAR);

    let material = LoadMaterialDefault();
    material.shader = shader;
    material.maps[MATERIAL_MAP_ALBEDO].texture = texture;
    material.maps[MATERIAL_MAP_METALNESS].texture = lightmap.texture;

    // Drawing to lightmap
    BeginTextureMode(lightmap);
        ClearBackground(BLACK);

        BeginBlendMode(BLEND_ADDITIVE);
            DrawTexturePro(
                light,
                new Rectangle( 0, 0, light.width, light.height ),
                new Rectangle( 0, 0, 20, 20 ),
                new Vector2( 10.0, 10.0 ),
                0.0,
                RED
            );
            DrawTexturePro(
                light,
                new Rectangle( 0, 0, light.width, light.height ),
                new Rectangle( 8, 4, 20, 20 ),
                new Vector2( 10.0, 10.0 ),
                0.0,
                BLUE
            );
            DrawTexturePro(
                light,
                new Rectangle( 0, 0, light.width, light.height ),
                new Rectangle( 8, 8, 10, 10 ),
                new Vector2( 5.0, 5.0 ),
                0.0,
                GREEN
            );
        BeginBlendMode(BLEND_ALPHA);
    EndTextureMode();

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
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawMesh(mesh, material, rm.MatrixIdentity());
            EndMode3D();

            DrawFPS(10, 10);

            DrawTexturePro(
                lightmap.texture,
                new Rectangle( 0, 0, -MAP_SIZE, -MAP_SIZE ),
                new Rectangle( GetRenderWidth() - MAP_SIZE*8 - 10, 10, MAP_SIZE*8, MAP_SIZE*8 ),
                new Vector2( 0.0, 0.0 ),
                0.0,
                WHITE);
                
            DrawText("lightmap", GetRenderWidth() - 66, 16 + MAP_SIZE*8, 10, GRAY);
            DrawText("10x10 pixels", GetRenderWidth() - 76, 30 + MAP_SIZE*8, 10, GRAY);
                
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadMesh(mesh);       // Unload the mesh
    UnloadShader(shader);   // Unload shader
    UnloadTexture(texture); // Unload texture
    UnloadTexture(light);   // Unload texture

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
