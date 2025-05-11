/*******************************************************************************************
*
*   raylib example - point rendering
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example contributed by Reese Gallagher (@satchelfrost) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024-2025 Reese Gallagher (@satchelfrost)
*
********************************************************************************************/

import { ColorFromHSV, InitWindow, Mesh, UploadMesh, Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadModelFromMesh, WindowShouldClose, UpdateCamera, CAMERA_ORBITAL, IsKeyPressed, KEY_SPACE, KEY_UP, KEY_DOWN, UnloadModel, BeginDrawing, ClearBackground, BLACK, BeginMode3D, DrawModelPoints, WHITE, Color, DrawPoint3D, DrawSphereWires, YELLOW, EndMode3D, DrawText, TextFormat, GREEN, RED, DrawFPS, EndDrawing, CloseWindow } from "rayjs:raylib";


const MAX_POINTS = 10000000;     // 10 million
const MIN_POINTS = 1000;         // 1 thousand

// Generate a spherical point cloud
function GenMeshPoints(numPoints){
    let mesh = new Mesh();
    mesh.triangleCount=1;
    mesh.vertexCount = numPoints;
    mesh.vertices = new Float32Array(numPoints*3);
    mesh.colors = new Uint8Array(numPoints*4);

    // https://en.wikipedia.org/wiki/Spherical_coordinate_system
    for (let i = 0; i < numPoints; i++){
        let theta = Math.PI*Math.random();
        let phi = 2*Math.PI*Math.random();
        let r = 10*Math.random();

        mesh.vertices[i*3    ] = r*Math.sin(theta)*Math.cos(phi);
        mesh.vertices[i*3 + 1] = r*Math.sin(theta)*Math.sin(phi);
        mesh.vertices[i*3 + 2] = r*Math.cos(theta);

        let color = ColorFromHSV(r*360, 1, 1);

        mesh.colors[i*4    ] = color.r;
        mesh.colors[i*4 + 1] = color.g;
        mesh.colors[i*4 + 2] = color.b;
        mesh.colors[i*4 + 3] = color.a;
    }

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(mesh, false);

    return mesh;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "raylib [models] example - point rendering");

    let camera = new Camera();
    camera.position = new Vector3( 3, 3, 3 );
    camera.target = new Vector3( 0, 0, 0 );
    camera.up = new Vector3( 0, 1, 0 );
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;

    let position = new Vector3( 0, 0, 0 );
    let useDrawModelPoints = true;
    let numPointsChanged = false;
    let numPoints = 1000;
    
    let mesh = GenMeshPoints(numPoints);
    let model = LoadModelFromMesh(mesh);
    
    //SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);

        if (IsKeyPressed(KEY_SPACE)) useDrawModelPoints = !useDrawModelPoints;
        if (IsKeyPressed(KEY_UP)) {
            numPoints = (numPoints*10 > MAX_POINTS)? MAX_POINTS : numPoints*10;
            numPointsChanged = true;
        }
        if (IsKeyPressed(KEY_DOWN)) {
            numPoints = (numPoints/10 < MIN_POINTS)? MIN_POINTS : numPoints/10;
            numPointsChanged = true;
        }

        // Upload a different point cloud size
        if (numPointsChanged) {
            UnloadModel(model);
            mesh = GenMeshPoints(numPoints);
            model = LoadModelFromMesh(mesh);
            numPointsChanged = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode3D(camera);

                // The new method only uploads the points once to the GPU
                if (useDrawModelPoints) {
                    DrawModelPoints(model, position, 1, WHITE);
                } else {
                    // The old method must continually draw the "points" (lines)
                    for (let i = 0; i < numPoints; i++) {
                        let pos = new Vector3( mesh.vertices[i*3], mesh.vertices[i*3 + 1], mesh.vertices[i*3 + 2]);
                        let color = new Color( mesh.colors[i*4], mesh.colors[i*4 + 1], mesh.colors[i*4 + 2], mesh.colors[i*4 + 3]);
                        
                        DrawPoint3D(pos, color);
                    }
                }

                // Draw a unit sphere for reference
                DrawSphereWires(position, 1, 10, 10, YELLOW);
                
            EndMode3D();

            // Draw UI text
            DrawText(TextFormat("Point Count: %d", numPoints), 20, screenHeight - 50, 40, WHITE);
            DrawText("Up - increase points", 20, 70, 20, WHITE);
            DrawText("Down - decrease points", 20, 100, 20, WHITE);
            DrawText("Space - drawing function", 20, 130, 20, WHITE);
            
            if (useDrawModelPoints) DrawText("Using: DrawModelPoints()", 20, 160, 20, GREEN);
            else DrawText("Using: DrawPoint3D()", 20, 160, 20, RED);
            
            DrawFPS(10, 10);
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model);

    CloseWindow();
}
