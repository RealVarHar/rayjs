import * as rl from 'rayjs:raylib';
import * as raymath from 'rayjs:raymath';
for (const key in rl) { globalThis[key] = rl[key] };
for (const key in raymath) { globalThis[key] = raymath[key] };

// Initialization
//--------------------------------------------------------------------------------------
const screenWidth = 800;
const screenHeight = 450;

InitWindow(screenWidth, screenHeight, "raylib [core] example - javascript mesh generation");

const mesh = new Mesh()
mesh.vertexCount = 3
mesh.triangleCount = 1
const v1 = new Vector3(screenWidth/2, 0, 0)
const v2 = new Vector3(0, screenHeight, 0 )
const v3 = new Vector3(screenWidth, screenHeight, 0)
mesh.indices = new Uint16Array([0,1,2]).buffer
mesh.vertices = new Float32Array([
    v1.x, v1.y, v1.z,
    v2.x, v2.y, v2.z,
    v3.x, v3.y, v3.z
]).buffer
UploadMesh(mesh, false) // If your forget to upload to GPU, drawMesh will segfault
const material = LoadMaterialDefault()
const matrix = MatrixIdentity()

SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawMesh(mesh, material, matrix)
        DrawText("Mesh created from Javascript ArrayBuffers", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
// De-Initialization
//--------------------------------------------------------------------------------------
UnloadMaterial(material)
UnloadMesh(mesh)
CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
