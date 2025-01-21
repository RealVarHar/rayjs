/*******************************************************************************************
*
*   raylib example - procedural mesh generation
*
*   Example originally created with raylib 1.8, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
import * as rl from 'rayjs:raylib';
for (const key in rl) { globalThis[key] = rl[key] };

// Generate a simple triangle mesh from code
function genMeshCustom()
{
    const mesh = new Mesh();
    mesh.triangleCount = 1;
    mesh.vertexCount = mesh.triangleCount*3;
    let vertices = new Array(mesh.vertexCount*3).fill(0);    // 3 vertices, 3 coordinates each (x, y, z)
    let texcoords = new Array(mesh.vertexCount*2).fill(0);   // 3 vertices, 2 coordinates each (x, y)
    let normals = new Array(mesh.vertexCount*3).fill(0);     // 3 vertices, 3 coordinates each (x, y, z)

    // Vertex at (0, 0, 0)
    vertices[0] = 0;
    vertices[1] = 0;
    vertices[2] = 0;
    normals[0] = 0;
    normals[1] = 1;
    normals[2] = 0;
    texcoords[0] = 0;
    texcoords[1] = 0;

    // Vertex at (1, 0, 2)
    vertices[3] = 1;
    vertices[4] = 0;
    vertices[5] = 2;
    normals[3] = 0;
    normals[4] = 1;
    normals[5] = 0;
    texcoords[2] = 0.5;
    texcoords[3] = 1.0;

    // Vertex at (2, 0, 0)
    vertices[6] = 2;
    vertices[7] = 0;
    vertices[8] = 0;
    normals[6] = 0;
    normals[7] = 1;
    normals[8] = 0;
    texcoords[4] = 1;
    texcoords[5] =0;
	
	mesh.vertices=vertices;
	mesh.texcoords=texcoords;
	mesh.normals=normals;

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    uploadMesh(mesh, false);

    return mesh;
}

var NUM_MODELS = 9;

// Initialization
//--------------------------------------------------------------------------------------
const screenWidth = 800;
const screenHeight = 450;

initWindow(screenWidth, screenHeight, "raylib [core] example - javascript mesh generation");

// We generate a checked image for texturing
let checked = genImageChecked(2, 2, 1, 1, RED, GREEN);
let texture = loadTextureFromImage(checked);
unloadImage(checked);

let models=new Array(NUM_MODELS);

models[0] = loadModelFromMesh(genMeshPlane(2, 2, 4, 3));
models[1] = loadModelFromMesh(genMeshCube(2, 1, 2));
models[2] = loadModelFromMesh(genMeshSphere(2, 32, 32));
models[3] = loadModelFromMesh(genMeshHemiSphere(2, 16, 16));
models[4] = loadModelFromMesh(genMeshCylinder(1, 2, 16));
models[5] = loadModelFromMesh(genMeshTorus(0.25, 4, 16, 32));
models[6] = loadModelFromMesh(genMeshKnot(1, 2, 16, 128));
models[7] = loadModelFromMesh(genMeshPoly(5, 2.0));
models[8] = loadModelFromMesh(genMeshCustom());

// Generated meshes could be exported as .obj files
//ExportMesh(models[0].meshes[0], "plane.obj");
//ExportMesh(models[1].meshes[0], "cube.obj");
//ExportMesh(models[2].meshes[0], "sphere.obj");
//ExportMesh(models[3].meshes[0], "hemisphere.obj");
//ExportMesh(models[4].meshes[0], "cylinder.obj");
//ExportMesh(models[5].meshes[0], "torus.obj");
//ExportMesh(models[6].meshes[0], "knot.obj");
//ExportMesh(models[7].meshes[0], "poly.obj");
//ExportMesh(models[8].meshes[0], "custom.obj");

// Set checked texture as default diffuse component for all models material
for (let i = 0; i < NUM_MODELS; i++) {
	let mats=models[i].materials;
	let maps=mats[0].maps;
	maps[MATERIAL_MAP_DIFFUSE].texture = texture
}

// Define the camera to look into our 3d world
let camera = new Camera3D( new Vector3( 5.0, 5.0, 5.0 ), new Vector3( 0.0, 0.0, 0.0 ), new Vector3( 0.0, 1.0, 0.0 ), 45, 0 );

// Model drawing position
let position = new Vector3( 0.0, 0.0, 0.0 );

let currentModel = 0;

setTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!windowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
	updateCamera(camera, CAMERA_ORBITAL);
	
	if (isMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        currentModel = (currentModel + 1)%NUM_MODELS; // Cycle between the textures
    }

    if (isKeyPressed(KEY_RIGHT))
    {
        currentModel++;
        if (currentModel >= NUM_MODELS) currentModel = 0;
    }
    else if (isKeyPressed(KEY_LEFT))
    {
        currentModel--;
        if (currentModel < 0) currentModel = NUM_MODELS - 1;
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    beginDrawing();

        clearBackground(RAYWHITE);
		
		beginMode3D(camera);
		
			drawModel(models[currentModel], position, 1.0, WHITE);
			drawGrid(10, 1.0);
			
		endMode3D();
		
		drawRectangle(30, 400, 310, 30, fade(SKYBLUE, 0.5));
        drawRectangleLines(30, 400, 310, 30, fade(DARKBLUE, 0.5));
        drawText("MOUSE LEFT BUTTON to CYCLE PROCEDURAL MODELS", 40, 410, 10, BLUE);
		
        switch(currentModel)
        {
            case 0: drawText("PLANE", 680, 10, 20, DARKBLUE); break;
            case 1: drawText("CUBE", 680, 10, 20, DARKBLUE); break;
            case 2: drawText("SPHERE", 680, 10, 20, DARKBLUE); break;
            case 3: drawText("HEMISPHERE", 640, 10, 20, DARKBLUE); break;
            case 4: drawText("CYLINDER", 680, 10, 20, DARKBLUE); break;
            case 5: drawText("TORUS", 680, 10, 20, DARKBLUE); break;
            case 6: drawText("KNOT", 680, 10, 20, DARKBLUE); break;
            case 7: drawText("POLY", 680, 10, 20, DARKBLUE); break;
            case 8: drawText("Custom (triangle)", 580, 10, 20, DARKBLUE); break;
            default: break;
        }

    endDrawing();
    //----------------------------------------------------------------------------------
}
// De-Initialization
//--------------------------------------------------------------------------------------
unloadTexture(texture); // Unload texture

// Unload models data (GPU VRAM)
for (let i = 0; i < NUM_MODELS; i++){
	unloadModel(models[i]);
}

closeWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
