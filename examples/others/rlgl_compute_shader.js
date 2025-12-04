/*******************************************************************************************
*
*   raylib [rlgl] example - compute shader - Conway's Game of Life
*
*   NOTE: This example requires raylib OpenGL 4.3 versions for compute shaders support,
*         shaders used in this example are #version 430 (OpenGL 4.3)
*
*   Example complexity rating: [★★★★] 4/4
*
*   Example originally created with raylib 4.0, last time updated with raylib 2.5
*
*   Example contributed by Teddy Astie (@tsnake41) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2025 Teddy Astie (@tsnake41)
*
********************************************************************************************/
import {BLANK, BeginDrawing,
    BeginShaderMode,
    ClearBackground, CloseWindow, DrawFPS, DrawRectangleLines, DrawText, DrawTexture,
    EndDrawing,
    EndShaderMode, GenImageColor, GetMouseWheelMove, GetMouseX, GetMouseY, GetScreenWidth, GetShaderLocation, InitWindow,
    IsMouseButtonDown, LoadFileText, LoadShader, LoadTextureFromImage,
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    RED,
    SHADER_UNIFORM_VEC2,
    SetShaderValue,
    SetTargetFPS,
    UnloadImage, UnloadShader, UnloadTexture, Vector2, WHITE, WindowShouldClose } from 'rayjs:raylib';
import * as rg from 'rayjs:rlgl';

// IMPORTANT: This must match gol*.glsl GOL_WIDTH constant.
// This must be a multiple of 16 (check golLogic compute dispatch).
const GOL_WIDTH = 768;

// Maximum amount of queued draw commands (squares draw from mouse down events).
const MAX_BUFFERED_TRANSFERTS = 48;

class GolUpdateSSBO{
    constructor(count,commands){
        if(count==undefined){
            count = MAX_BUFFERED_TRANSFERTS;
            this.count=0;
        }
        if(commands == undefined){
            this.commands=new Array(count);
            for(let i=0; i<count;i++){
                this.commands[i]={x:0,y:0,w:0,enabled:0};
            }
        }
    }
    getBuffer(){
        //we happen to use only uint, otherwise, use DataView
        let bufferArray = new Uint32Array(MAX_BUFFERED_TRANSFERTS*4 + 1);
        bufferArray[0] = this.count;

        for(let i=0; i<this.count;i++){
            const command= this.commands[i];
            const offset=i*4+1;
            bufferArray[offset]=  command.x;        // x coordinate of the gol command
            bufferArray[offset+1]=command.y;        // y coordinate of the gol command
            bufferArray[offset+2]=command.w;        // width of the filled zone
            bufferArray[offset+3]=command.enabled;  // whether to enable or disable zone
        }
        return bufferArray.buffer;
    }
    setFromBuffer(buffer){
        let bufferArray = new Uint32Array(buffer);
        const count = bufferArray[0];
        if(count!= this.count){
            this.commands=new Array(count);
        }
        this.count = count;
        for(let i=0; i<count;i++){
            const offset=i*4+1;
            this.commands[i]={
                x:bufferArray[offset],
                y:bufferArray[offset+1],
                w:bufferArray[offset+2],
                enabled:bufferArray[offset+3]
            };
        }
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(GOL_WIDTH, GOL_WIDTH, "raylib [rlgl] example - compute shader - game of life");
    SetTargetFPS(60);

    const resolution = new Vector2( GOL_WIDTH, GOL_WIDTH );//{x = 768, y = 768}
    let brushSize = 8;

    // Game of Life logic compute shader
    let golLogicCode = LoadFileText("resources/shaders/glsl430/gol.glsl");
    let golLogicShader = rg.rlCompileShader(golLogicCode, rg.RL_COMPUTE_SHADER);//"#version 430\n\n// Game of Life logic shader\n\n#define GOL_
    let golLogicProgram = rg.rlLoadComputeShaderProgram(golLogicShader);//(4)

    // Game of Life logic render shader
    let golRenderShader = LoadShader(null, "resources/shaders/glsl430/gol_render.glsl");
    let resUniformLoc = GetShaderLocation(golRenderShader, "resolution");//{id = 7, locs = 0x200000808c0} where locs is [0,1,-1,-1,-1,3...0@50...0@500]

    // Game of Life transfert shader (CPU<->GPU download and upload)
    let golTransfertCode = LoadFileText("resources/shaders/glsl430/gol_transfert.glsl");
    let golTransfertShader = rg.rlCompileShader(golTransfertCode, rg.RL_COMPUTE_SHADER); //"#version 430\n\n// Game of life transfert shader\n\n#define GOL_WIDTH 768\n\n// Game Of Life Update Command\n// NOTE: matches the structure defined on main p
    let golTransfertProgram = rg.rlLoadComputeShaderProgram(golTransfertShader); //(6)

    // Load shader storage buffer object (SSBO), id returned
    let ssboA = rg.rlLoadShaderBuffer(GOL_WIDTH*GOL_WIDTH*Uint32Array.BYTES_PER_ELEMENT, null, rg.RL_DYNAMIC_COPY);
    let ssboB = rg.rlLoadShaderBuffer(GOL_WIDTH*GOL_WIDTH*Uint32Array.BYTES_PER_ELEMENT, null, rg.RL_DYNAMIC_COPY);
    let transfertBuffer = new GolUpdateSSBO();
    let ssboTransfert = rg.rlLoadShaderBuffer(transfertBuffer.getBuffer().byteLength, null, rg.RL_DYNAMIC_COPY);

    // Create a white texture of the size of the window to update
    // each pixel of the window using the fragment shader: golRenderShader
    let whiteImage = GenImageColor(GOL_WIDTH, GOL_WIDTH, WHITE);
    let whiteTex = LoadTextureFromImage(whiteImage);//{data = 0x20001c00200, width = 768, height = 768, mipmaps = 1, format = 7}
    UnloadImage(whiteImage);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        brushSize += Math.floor(GetMouseWheelMove());

        if ((IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) && (transfertBuffer.count < MAX_BUFFERED_TRANSFERTS)) {
            // Buffer a new command
            transfertBuffer.commands[transfertBuffer.count].x = GetMouseX() - brushSize/2;
            transfertBuffer.commands[transfertBuffer.count].y = GetMouseY() - brushSize/2;
            transfertBuffer.commands[transfertBuffer.count].w = brushSize;
            transfertBuffer.commands[transfertBuffer.count].enabled = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
            transfertBuffer.count++;
        } else if (transfertBuffer.count > 0) { // Process transfert buffer
            // Send SSBO buffer to GPU
            let buffer =transfertBuffer.getBuffer();
            rg.rlUpdateShaderBuffer(ssboTransfert, buffer, buffer.byteLength, 0);
            //rlUpdateShaderBuffer does not modify buffers contents

            // Process SSBO commands on GPU
            rg.rlEnableShader(golTransfertProgram);
            rg.rlBindShaderBuffer(ssboA, 1);
            rg.rlBindShaderBuffer(ssboTransfert, 3);
            rg.rlComputeShaderDispatch(transfertBuffer.count, 1, 1); // Each GPU unit will process a command!
            rg.rlDisableShader();

            transfertBuffer.count = 0;
        } else {
            // Process game of life logic
            rg.rlEnableShader(golLogicProgram);//(5)
            rg.rlBindShaderBuffer(ssboA, 1);//6
            rg.rlBindShaderBuffer(ssboB, 2);//7
            rg.rlComputeShaderDispatch(GOL_WIDTH/16, GOL_WIDTH/16, 1);
            rg.rlDisableShader();

            // ssboA <-> ssboB
            let temp = ssboA;
            ssboA = ssboB;
            ssboB = temp;
        }

        rg.rlBindShaderBuffer(ssboA, 1);
        SetShaderValue(golRenderShader, resUniformLoc, resolution, SHADER_UNIFORM_VEC2);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLANK);

            BeginShaderMode(golRenderShader);
                DrawTexture(whiteTex, 0, 0, WHITE);
            EndShaderMode();

            DrawRectangleLines(GetMouseX() - brushSize/2, GetMouseY() - brushSize/2, brushSize, brushSize, RED);

            DrawText("Use Mouse wheel to increase/decrease brush size", 10, 10, 20, WHITE);
            DrawFPS(GetScreenWidth() - 100, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload shader buffers objects.
    rg.rlUnloadShaderBuffer(ssboA);
    rg.rlUnloadShaderBuffer(ssboB);
    rg.rlUnloadShaderBuffer(ssboTransfert);

    // Unload compute shader programs
    rg.rlUnloadShaderProgram(golTransfertProgram);
    rg.rlUnloadShaderProgram(golLogicProgram);

    UnloadTexture(whiteTex);            // Unload white texture
    UnloadShader(golRenderShader);      // Unload rendering fragment shader

    CloseWindow();                      // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}