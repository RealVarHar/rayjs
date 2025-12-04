import * as rlm from 'rayjs:rlightmapper';
import * as rm from 'rayjs:raymath';
import {
    BLACK, BLUE, BeginDrawing, BeginMode3D, CAMERA_PERSPECTIVE,
    CAMERA_THIRD_PERSON, Camera3D,
    ClearBackground, CloseWindow, DrawMesh, DrawModel,
    DrawRectangle, EndDrawing, EndMode3D, FLAG_MSAA_4X_HINT, FLAG_VSYNC_HINT, FLAG_WINDOW_HIGHDPI,
    Fade,
    GREEN,
    GenImageColor, GenMeshCube, GetModelBoundingBox,
    GetMouseWheelMove, GetScreenWidth, GetTime, InitWindow,
    IsMouseButtonDown,
    LoadMaterialDefault,
    LoadModel, LoadTextureFromImage, MATERIAL_MAP_ALBEDO,
    MATERIAL_MAP_DIFFUSE,
    MOUSE_BUTTON_LEFT, ORANGE, SetConfigFlags, SetMaterialTexture,
    SetTextureFilter, TEXTURE_FILTER_TRILINEAR,
    UnloadModel, UnloadTexture, UpdateCamera, Vector3, WHITE, WindowShouldClose } from 'rayjs:raylib';
{


function DrawScene(scene){
	DrawModel(scene.raylib_model, new Vector3(0,0,0), 1, WHITE);
}

SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI | FLAG_VSYNC_HINT);

InitWindow(1024,768,"Test");

const scene = {}

scene.raylib_model = LoadModel("../../assets/models/gazebo.obj");

// Demonstration how to merge models into a single mesh
// let m = loadModel("../assets/models/untitled_no_lm.obj");
// if(m.meshCount > 1){
//     traceLog(LOG_INFO, "Starting merge of "+ m.meshCount + " meshes")
//     let currentMesh = getModelMesh(m, 0);
//     for (let i = 1; i < m.meshCount; i++) {
//         const mesh = getModelMesh(m, i)
//         const merged = meshMerge(mesh, currentMesh);
//         if(i > 1) unloadMesh(currentMesh)
//         currentMesh = merged
//     }
//     unloadModel(m)
//     uploadMesh(currentMesh)
//     traceLog(LOG_INFO, "Mesh successfully merged")
//     m = loadModelFromMesh(currentMesh)
// }

const bbox = GetModelBoundingBox(scene.raylib_model)

scene.w = 256;
scene.h = 256;
scene.raylib_texture = LoadTextureFromImage(GenImageColor(1,1,BLACK));
const defMat = LoadMaterialDefault();
SetMaterialTexture(defMat, MATERIAL_MAP_ALBEDO, scene.raylib_texture);
let materials = scene.raylib_model.materials;
materials[0] = defMat;
scene.raylib_model.materials = materials;//setModelMaterial

const position = new Vector3( 0, bbox.min.y + ((bbox.max.y - bbox.min.y) / 2), bbox.max.z - bbox.min.z ); // Camera position
const target = new Vector3( 0.0, bbox.min.y + ((bbox.max.y - bbox.min.y) / 2), 0.0);     // Camera looking at point
const up = new Vector3(0.0, 1.0, 0.0);          // Camera up vector (rotation towards target)
const fovy = 45.0;                                // Camera field-of-view Y
const projection = CAMERA_PERSPECTIVE;                   // Camera mode type
scene.camera = new Camera3D(position, target, up, fovy, projection);
const config = rlm.GetDefaultLightmapperConfig();
//config.backgroundColor = new Color(10,10,10);
//config.hemisphereSize = 512;
const mesh = scene.raylib_model.meshes[0];//GetModelMesh
const lm = rlm.LoadLightmapper(scene.w, scene.h, mesh, config);
const lmMat = rlm.LoadMaterialLightmapper(BLACK, 0);
const light = GenMeshCube(0.2,0.2,0.2);
const lightMaterial = rlm.LoadMaterialLightmapper(ORANGE, .1);

while (!WindowShouldClose())
{
    const wm = GetMouseWheelMove();
    if(wm !== 0){
        const camPos = scene.camera.position;
        const fac = 1 + (wm * -0.1);
        scene.camera.position = rm.Vector3Multiply(camPos, new Vector3(fac, fac, fac));
    }

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        UpdateCamera(scene.camera, CAMERA_THIRD_PERSON);

    if(lm.progress < 1.0){
        let startTime = GetTime();
        rlm.BeginLightmap();
        while(rlm.BeginLightmapFragment(lm)){
            DrawMesh(mesh, lmMat, rm.MatrixIdentity());
            // drawMesh(light, lightMaterial, matrixTranslate(0.0,0.3,0.5));
            // drawMesh(light, lightMaterial, matrixTranslate(0.0,0.3,-0.5));
            //drawMesh(light, lightMaterial, matrixMultiply(matrixScale(60,60,60), matrixTranslate(0.0,150,0)));
            // drawMesh(light, lightMaterial, matrixTranslate(0.5,0.3,0));
            // drawMesh(light, lightMaterial, matrixTranslate(-0.5,0.3,0));
            rlm.EndLightmapFragment(lm);
            // display progress every second (printf is expensive)
            let time = GetTime();
            if (GetTime() - startTime > 0.03) break;
        }
        rlm.EndLightmap();
        if(lm.progress == 1.0){
            const img = rlm.LoadImageFromLightmapper(lm);
            //exportImage(img, "my_result.png");
            const old = scene.raylib_texture;
            scene.raylib_texture = LoadTextureFromImage(img);
            SetTextureFilter(scene.raylib_texture, TEXTURE_FILTER_TRILINEAR);
            UnloadTexture(old);
            let mat = LoadMaterialDefault();
            SetMaterialTexture(mat, MATERIAL_MAP_DIFFUSE, scene.raylib_texture);
            let materials=scene.raylib_model.materials;
            materials[0] = mat
            scene.raylib_model.materials= materials;//setModelMaterial
            rlm.UnloadLightmapper(lm);
        }
    }

    BeginDrawing();
        ClearBackground(BLUE);
        
            BeginMode3D(scene.camera);
            DrawScene(scene);
            EndMode3D();
        
        // printf("%d\n",(int)(lm.progress*GetScreenWidth()));
        if(lm.progress < 1.0){
            DrawRectangle(0,0,GetScreenWidth(),20, Fade(GREEN,0.5));
            DrawRectangle(0,0,GetScreenWidth()*lm.progress,20, GREEN);
        }
    EndDrawing();
}

UnloadModel(scene.raylib_model);
UnloadTexture(scene.raylib_texture);
CloseWindow();
}