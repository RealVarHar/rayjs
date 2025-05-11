/*******************************************************************************************
*
*   raylib [shaders] example - Basic PBR
*
*   Example complexity rating: [★★★★] 4/4
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.1-dev
*
*   Example contributed by Afan OLOVCIC (@_DevDad) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2025 Afan OLOVCIC (@_DevDad)
*
*   Model: "Old Rusty Car" (https://skfb.ly/LxRy) by Renafox, 
*   licensed under Creative Commons Attribution-NonCommercial 
*   (http://creativecommons.org/licenses/by-nc/4.0/)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {
    FLAG_MSAA_4X_HINT, GetShaderLocation,
    InitWindow,
    SHADER_UNIFORM_FLOAT, SHADER_UNIFORM_INT, SHADER_UNIFORM_VEC3, SHADER_UNIFORM_VEC4,
    SetConfigFlags, SetShaderValue, TextFormat,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadShader, SHADER_LOC_MAP_ALBEDO, SHADER_LOC_MAP_METALNESS, SHADER_LOC_MAP_NORMAL, SHADER_LOC_MAP_EMISSION, SHADER_LOC_COLOR_DIFFUSE, SHADER_LOC_VECTOR_VIEW, Color, LoadModel, WHITE, MATERIAL_MAP_ALBEDO, MATERIAL_MAP_METALNESS, MATERIAL_MAP_ROUGHNESS, MATERIAL_MAP_OCCLUSION, MATERIAL_MAP_EMISSION, LoadTexture, MATERIAL_MAP_NORMAL, BLACK, Vector2, YELLOW, GREEN, RED, BLUE, SetTargetFPS, WindowShouldClose, CAMERA_ORBITAL, UpdateCamera, IsKeyPressed, KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, BeginDrawing, ClearBackground, BeginMode3D, ColorNormalize, SHADER_UNIFORM_VEC2, DrawModel, DrawSphereEx, DrawSphereWires, ColorAlpha, EndMode3D, DrawText, LIGHTGRAY, DrawFPS, EndDrawing, UnloadMaterial, Shader, UnloadModel, UnloadShader, CloseWindow } from 'rayjs:raylib';

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}

const MAX_LIGHTS = 4;           // Max dynamic lights supported by shader

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

// Light type
const LIGHT_DIRECTIONAL = 0;
const LIGHT_POINT = 1;
const LIGHT_SPOT = 1;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
let lightCount = 0;     // Current number of dynamic lights that have been created

//----------------------------------------------------------------------------------
// Module specific Functions Declaration
//----------------------------------------------------------------------------------
// Create a light and get shader locations
// NOTE: It updated the global lightCount and it's limited to MAX_LIGHTS
function CreateLight(type, position, target, color, intensity, shader) {
    let light = {};

    if (lightCount < MAX_LIGHTS) {
        light.enabled = 1;
        light.type = type;
        light.position = position;
        light.target = target;
        light.color[0] = color.r/255;
        light.color[1] = color.g/255;
        light.color[2] = color.b/255;
        light.color[3] = color.a/255;
        light.intensity = intensity;

        // NOTE: Shader parameters names for lights must match the requested ones
        light.enabledLoc = GetShaderLocation(shader, TextFormat("lights[%i].enabled", lightCount));
        light.typeLoc = GetShaderLocation(shader, TextFormat("lights[%i].type", lightCount));
        light.positionLoc = GetShaderLocation(shader, TextFormat("lights[%i].position", lightCount));
        light.targetLoc = GetShaderLocation(shader, TextFormat("lights[%i].target", lightCount));
        light.colorLoc = GetShaderLocation(shader, TextFormat("lights[%i].color", lightCount));
        light.intensityLoc = GetShaderLocation(shader, TextFormat("lights[%i].intensity", lightCount));

        UpdateLight(shader, light);

        lightCount++;
    }

    return light;
}

// Update light properties on shader
// NOTE: Light shader locations should be available
function UpdateLight(shader, light) {
    SetShaderValue(shader, light.enabledLoc, light.enabled, SHADER_UNIFORM_INT);
    SetShaderValue(shader, light.typeLoc, light.type, SHADER_UNIFORM_INT);

    // Send to shader light position values
    let position = [ light.position.x, light.position.y, light.position.z ];
    SetShaderValue(shader, light.positionLoc, position, SHADER_UNIFORM_VEC3);

    // Send to shader light target position values
    let target = [ light.target.x, light.target.y, light.target.z ];
    SetShaderValue(shader, light.targetLoc, target, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, light.colorLoc, light.color, SHADER_UNIFORM_VEC4);
    SetShaderValue(shader, light.intensityLoc, light.intensity, SHADER_UNIFORM_FLOAT);
}

//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - basic pbr");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 2, 2, 6 );    // Camera position
    camera.target = new Vector3( 0, 0.5, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Load PBR shader and setup all required locations
    let shader = LoadShader(TextFormat("resources/shaders/glsl%i/pbr.vs", GLSL_VERSION),
                            TextFormat("resources/shaders/glsl%i/pbr.fs", GLSL_VERSION));
    shader.locs[SHADER_LOC_MAP_ALBEDO] = GetShaderLocation(shader, "albedoMap");
    // WARNING: Metalness, roughness, and ambient occlusion are all packed into a MRA texture
    // They are passed as to the SHADER_LOC_MAP_METALNESS location for convenience,
    // shader already takes care of it accordingly
    shader.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(shader, "mraMap");
    shader.locs[SHADER_LOC_MAP_NORMAL] = GetShaderLocation(shader, "normalMap");
    // WARNING: Similar to the MRA map, the emissive map packs different information 
    // into a single texture: it stores height and emission data
    // It is binded to SHADER_LOC_MAP_EMISSION location an properly processed on shader
    shader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(shader, "emissiveMap");
    shader.locs[SHADER_LOC_COLOR_DIFFUSE] = GetShaderLocation(shader, "albedoColor");

    // Setup additional required shader locations, including lights data
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    let lightCountLoc = GetShaderLocation(shader, "numOfLights");
    SetShaderValue(shader, lightCountLoc, MAX_LIGHTS, SHADER_UNIFORM_INT);

    // Setup ambient color and intensity parameters
    let ambientIntensity = 0.02;
    let ambientColor = new Color( 26, 32, 135, 255 );
    let ambientColorNormalized = new Vector3( ambientColor.r/255, ambientColor.g/255, ambientColor.b/255 );
    SetShaderValue(shader, GetShaderLocation(shader, "ambientColor"), ambientColorNormalized, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, GetShaderLocation(shader, "ambient"), ambientIntensity, SHADER_UNIFORM_FLOAT);

    // Get location for shader parameters that can be modified in real time
    let emissiveIntensityLoc = GetShaderLocation(shader, "emissivePower");
    let emissiveColorLoc = GetShaderLocation(shader, "emissiveColor");
    let textureTilingLoc = GetShaderLocation(shader, "tiling");

    // Load old car model using PBR maps and shader
    // WARNING: We know this model consists of a single model.meshes[0] and
    // that model.materials[0] is by default assigned to that mesh
    // There could be more complex models consisting of multiple meshes and
    // multiple materials defined for those meshes... but always 1 mesh = 1 material
    let car = LoadModel("resources/models/old_car_new.glb");

    // Assign already setup PBR shader to model.materials[0], used by models.meshes[0]
    car.materials[0].shader = shader;

    // Setup materials[0].maps default parameters
    car.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
    car.materials[0].maps[MATERIAL_MAP_METALNESS].value = 0;
    car.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0;
    car.materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1;
    car.materials[0].maps[MATERIAL_MAP_EMISSION].color = new Color( 255, 162, 0, 255 );

    // Setup materials[0].maps default textures
    car.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = LoadTexture("resources/old_car_d.png");
    car.materials[0].maps[MATERIAL_MAP_METALNESS].texture = LoadTexture("resources/old_car_mra.png");
    car.materials[0].maps[MATERIAL_MAP_NORMAL].texture = LoadTexture("resources/old_car_n.png");
    car.materials[0].maps[MATERIAL_MAP_EMISSION].texture = LoadTexture("resources/old_car_e.png");
    
    // Load floor model mesh and assign material parameters
    // NOTE: A basic plane shape can be generated instead of being loaded from a model file
    let floor = LoadModel("resources/models/plane.glb");
    //Mesh floorMesh = GenMeshPlane(10, 10, 10, 10);
    //GenMeshTangents(&floorMesh);      // TODO: Review tangents generation
    //Model floor = LoadModelFromMesh(floorMesh);

    // Assign material shader for our floor model, same PBR shader 
    floor.materials[0].shader = shader;
    
    floor.materials[0].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
    floor.materials[0].maps[MATERIAL_MAP_METALNESS].value = 0;
    floor.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0;
    floor.materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1;
    floor.materials[0].maps[MATERIAL_MAP_EMISSION].color = BLACK;

    floor.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = LoadTexture("resources/road_a.png");
    floor.materials[0].maps[MATERIAL_MAP_METALNESS].texture = LoadTexture("resources/road_mra.png");
    floor.materials[0].maps[MATERIAL_MAP_NORMAL].texture = LoadTexture("resources/road_n.png");

    // Models texture tiling parameter can be stored in the Material struct if required (CURRENTLY NOT USED)
    // NOTE: Material.params[4] are available for generic parameters storage (float)
    let carTextureTiling = new Vector2( 0.5, 0.5 );
    let floorTextureTiling = new Vector2( 0.5, 0.5 );

    // Create some lights
    let lights = new Array(MAX_LIGHTS);
    lights[0] = CreateLight(LIGHT_POINT, new Vector3( -1, 1, -2 ), new Vector3( 0, 0, 0 ), YELLOW, 4, shader);
    lights[1] = CreateLight(LIGHT_POINT, new Vector3(  2, 1,  1 ), new Vector3( 0, 0, 0 ), GREEN, 3.3, shader);
    lights[2] = CreateLight(LIGHT_POINT, new Vector3( -2, 1,  1 ), new Vector3( 0, 0, 0 ), RED, 8.3, shader);
    lights[3] = CreateLight(LIGHT_POINT, new Vector3(  1, 1, -2 ), new Vector3( 0, 0, 0 ), BLUE, 2, shader);

    // Setup material texture maps usage in shader
    // NOTE: By default, the texture maps are always used
    let usage = [1];
    SetShaderValue(shader, GetShaderLocation(shader, "useTexAlbedo"), usage, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "useTexNormal"), usage, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "useTexMRA"), usage, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "useTexEmissive"), usage, SHADER_UNIFORM_INT);
    
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);

        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        let cameraPos = [camera.position.x, camera.position.y, camera.position.z];
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_ONE)) { lights[2].enabled = !lights[2].enabled; }
        if (IsKeyPressed(KEY_TWO)) { lights[1].enabled = !lights[1].enabled; }
        if (IsKeyPressed(KEY_THREE)) { lights[3].enabled = !lights[3].enabled; }
        if (IsKeyPressed(KEY_FOUR)) { lights[0].enabled = !lights[0].enabled; }

        // Update light values on shader (actually, only enable/disable them)
        for (let i = 0; i < MAX_LIGHTS; i++) UpdateLight(shader, lights[i]);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
            ClearBackground(BLACK);
            
            BeginMode3D(camera);
                
                // Set floor model texture tiling and emissive color parameters on shader
                SetShaderValue(shader, textureTilingLoc, floorTextureTiling, SHADER_UNIFORM_VEC2);
                let floorEmissiveColor = ColorNormalize(floor.materials[0].maps[MATERIAL_MAP_EMISSION].color);
                SetShaderValue(shader, emissiveColorLoc, floorEmissiveColor, SHADER_UNIFORM_VEC4);
                
                DrawModel(floor, new Vector3( 0, 0, 0 ), 5, WHITE);   // Draw floor model

                // Set old car model texture tiling, emissive color and emissive intensity parameters on shader
                SetShaderValue(shader, textureTilingLoc, carTextureTiling, SHADER_UNIFORM_VEC2);
                let carEmissiveColor = ColorNormalize(car.materials[0].maps[MATERIAL_MAP_EMISSION].color);
                SetShaderValue(shader, emissiveColorLoc, carEmissiveColor, SHADER_UNIFORM_VEC4);
                let emissiveIntensity = 0.01;
                SetShaderValue(shader, emissiveIntensityLoc, emissiveIntensity, SHADER_UNIFORM_FLOAT);
                
                DrawModel(car, new Vector3( 0, 0, 0 ), 0.25, WHITE);   // Draw car model

                // Draw spheres to show the lights positions
                for (let i = 0; i < MAX_LIGHTS; i++) {
                    let lightColor = new Color( lights[i].color[0]*255, lights[i].color[1]*255, lights[i].color[2]*255, lights[i].color[3]*255 );
                    
                    if (lights[i].enabled) DrawSphereEx(lights[i].position, 0.2, 8, 8, lightColor);
                    else DrawSphereWires(lights[i].position, 0.2, 8, 8, ColorAlpha(lightColor, 0.3));
                }
                
            EndMode3D();
            
            DrawText("Toggle lights: [1][2][3][4]", 10, 40, 20, LIGHTGRAY);

            DrawText("(c) Old Rusty Car model by Renafox (https://skfb.ly/LxRy)", screenWidth - 320, screenHeight - 20, 10, LIGHTGRAY);
            
            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unbind (disconnect) shader from car.material[0] 
    // to avoid UnloadMaterial() trying to unload it automatically
    car.materials[0].shader = new Shader();
    UnloadMaterial(car.materials[0]);
    car.materials[0].maps = null;
    UnloadModel(car);
    
    floor.materials[0].shader = new Shader();
    UnloadMaterial(floor.materials[0]);
    floor.materials[0].maps = null;
    UnloadModel(floor);
    
    UnloadShader(shader);       // Unload Shader
    
    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}