/*******************************************************************************************
*
*   raylib [core] example - Using bones as socket for calculating the positioning of something
*
*   Example complexity rating: [★★★★] 4/4
* 
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by iP (@ipzaur) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024-2025 iP (@ipzaur)
*
********************************************************************************************/
import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadModel, LoadModelAnimations, DisableCursor, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_THIRD_PERSON, IsKeyDown, KEY_F, KEY_H, IsKeyPressed, KEY_T, KEY_G, KEY_ONE, KEY_TWO, KEY_THREE, UpdateModelAnimation, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, DrawMesh, DrawGrid, EndMode3D, DrawText, GRAY, EndDrawing, UnloadModelAnimations, UnloadModel, CloseWindow } from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';

const BONE_SOCKETS = 3;
const BONE_SOCKET_HAT = 0;
const BONE_SOCKET_HAND_R = 1;
const BONE_SOCKET_HAND_L = 2;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    const DEG2RAD = Math.PI/180;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - bone socket");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 5, 5, 5 ); // Camera position
    camera.target = new Vector3( 0, 2, 0 );  // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );      // Camera up vector (rotation towards target)
    camera.fovy = 45;                            // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;         // Camera projection type

    // Load gltf model
    let characterModel = LoadModel("resources/models/gltf/greenman.glb"); // Load character model
    let equipModel = [
        LoadModel("resources/models/gltf/greenman_hat.glb"),    // Index for the hat model is the same as BONE_SOCKET_HAT
        LoadModel("resources/models/gltf/greenman_sword.glb"),  // Index for the sword model is the same as BONE_SOCKET_HAND_R
        LoadModel("resources/models/gltf/greenman_shield.glb")  // Index for the shield model is the same as BONE_SOCKET_HAND_L
    ];
    
    let showEquip = [ true, true, true ];   // Toggle on/off equip

    // Load gltf model animations
    let animsCount = [0];
    let animIndex = 0;
    let animCurrentFrame = 0;
    let modelAnimations = LoadModelAnimations("resources/models/gltf/greenman.glb", animsCount);

    // indices of bones for sockets
    let boneSocketIndex = [ -1, -1, -1 ];

    // search bones for sockets 
    for (let i = 0; i < characterModel.boneCount; i++) {
        if (characterModel.bones[i].name == "socket_hat") {
            boneSocketIndex[BONE_SOCKET_HAT] = i;
            continue;
        }
        
        if (characterModel.bones[i].name == "socket_hand_R") {
            boneSocketIndex[BONE_SOCKET_HAND_R] = i;
            continue;
        }
        
        if (characterModel.bones[i].name == "socket_hand_L") {
            boneSocketIndex[BONE_SOCKET_HAND_L] = i;
            continue;
        }
    }

    let position = new Vector3( 0, 0, 0 ); // Set model position
    let angle = 0;           // Set angle for rotate character

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_THIRD_PERSON);
        
        // Rotate character
        if (IsKeyDown(KEY_F)) angle = (angle + 1)%360;
        else if (IsKeyDown(KEY_H)) angle = (360 + angle - 1)%360;

        // Select current animation
        if (IsKeyPressed(KEY_T)) animIndex = (animIndex + 1)%animsCount[0];
        else if (IsKeyPressed(KEY_G)) animIndex = (animIndex + animsCount[0] - 1)%animsCount[0];

        // Toggle shown of equip
        if (IsKeyPressed(KEY_ONE)) showEquip[BONE_SOCKET_HAT] = !showEquip[BONE_SOCKET_HAT];
        if (IsKeyPressed(KEY_TWO)) showEquip[BONE_SOCKET_HAND_R] = !showEquip[BONE_SOCKET_HAND_R];
        if (IsKeyPressed(KEY_THREE)) showEquip[BONE_SOCKET_HAND_L] = !showEquip[BONE_SOCKET_HAND_L];
        
        // Update model animation
        let anim = modelAnimations[animIndex];
        animCurrentFrame = (animCurrentFrame + 1) % anim.frameCount;
        UpdateModelAnimation(characterModel, anim, animCurrentFrame);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                // Draw character
                let characterRotate = rm.QuaternionFromAxisAngle( new Vector3( 0, 1, 0 ), angle*DEG2RAD);
                characterModel.transform = rm.MatrixMultiply(rm.QuaternionToMatrix(characterRotate), rm.MatrixTranslate(position.x, position.y, position.z));
                UpdateModelAnimation(characterModel, anim, animCurrentFrame);
                DrawMesh(characterModel.meshes[0], characterModel.materials[1], characterModel.transform);

                // Draw equipments (hat, sword, shield)
                for (let i = 0; i < BONE_SOCKETS; i++) {
                    if (!showEquip[i]) continue;

                    let transform = anim.framePoses[animCurrentFrame][boneSocketIndex[i]];
                    let inRotation = characterModel.bindPose[boneSocketIndex[i]].rotation;
                    let outRotation = transform.rotation;
                    
                    // Calculate socket rotation (angle between bone in initial pose and same bone in current animation frame)
                    let rotate = rm.QuaternionMultiply(outRotation, rm.QuaternionInvert(inRotation));
                    let matrixTransform = rm.QuaternionToMatrix(rotate);
                    // Translate socket to its position in the current animation
                    matrixTransform = rm.MatrixMultiply(matrixTransform, rm.MatrixTranslate(transform.translation.x, transform.translation.y, transform.translation.z));
                    // Transform the socket using the transform of the character (angle and translate)
                    matrixTransform = rm.MatrixMultiply(matrixTransform, characterModel.transform);
                    
                    // Draw mesh at socket position with socket angle rotation
                    DrawMesh(equipModel[i].meshes[0], equipModel[i].materials[1], matrixTransform);
                }

                DrawGrid(10, 1);
            EndMode3D();

            DrawText("Use the T/G to switch animation", 10, 10, 20, GRAY);
            DrawText("Use the F/H to rotate character left/right", 10, 35, 20, GRAY);
            DrawText("Use the 1,2,3 to toggle shown of hat, sword and shield", 10, 60, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModelAnimations(modelAnimations, animsCount[0]);
    UnloadModel(characterModel);         // Unload character model and meshes/material
    
    // Unload equipment model and meshes/material
    for (let i = 0; i < BONE_SOCKETS; i++) UnloadModel(equipModel[i]);

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}