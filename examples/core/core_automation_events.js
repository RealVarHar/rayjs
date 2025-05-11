/*******************************************************************************************
*
*   raylib [core] example - automation events
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example based on 2d_camera_platformer example by arvyy (@arvyy)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing,
    BeginMode2D,
    BLACK,
    BLUE,
    Camera2D,
    ClearBackground, CloseWindow,
    DARKGRAY, DARKGREEN,
    DrawCircle,
    DrawRectangle,
    DrawRectangleLines,
    DrawRectangleRec,
    DrawText, DrawTriangle, EndDrawing,
    EndMode2D,
    ExportAutomationEventList,
    Fade,
    GetMouseWheelMove,
    GetWorldToScreen2D,
    GRAY,
    InitWindow,
    IsFileDropped,
    IsFileExtension,
    IsKeyDown,
    IsKeyPressed,
    KEY_A,
    KEY_LEFT,
    KEY_R,
    KEY_RIGHT,
    KEY_S,
    KEY_SPACE,
    LIGHTGRAY, LIME,
    LoadAutomationEventList,
    LoadDroppedFiles,
    LOG_INFO,
    MAROON,
    PlayAutomationEvent,
    Rectangle,
    RED,
    SetAutomationEventBaseFrame,
    SetAutomationEventList,
    SetTargetFPS,
    SKYBLUE,
    StartAutomationEventRecording,
    StopAutomationEventRecording, TextFormat,
    TraceLog,
    UnloadAutomationEventList,
    Vector2,
    WindowShouldClose
} from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';

const GRAVITY = 400;
const PLAYER_JUMP_SPD = 350;
const PLAYER_HOR_SPD = 200;

const MAX_ENVIRONMENT_ELEMENTS = 5;

class Player{
    position;speed;canJump;
}

class EnvElement{
    rect;blocking;color;
    constructor(rect,blocking,color){
        this.rect=new Rectangle(...rect);
        this.blocking=blocking;
        this.color=color;
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - automation events");

    // Define player
    let player = new Player();
    player.position = new Vector2( 400, 280 );
    player.speed = 0;
    player.canJump = false;
    
    // Define environment elements (platforms)
    let envElements = [
        new EnvElement([ 0, 0, 1000, 400 ], 0, LIGHTGRAY ),
        new EnvElement([ 0, 400, 1000, 200 ], 1, GRAY ),
        new EnvElement([ 300, 200, 400, 10 ], 1, GRAY ),
        new EnvElement([ 250, 300, 100, 10 ], 1, GRAY ),
        new EnvElement([ 650, 300, 100, 10 ], 1, GRAY )
    ];

    // Define camera
    let camera = new Camera2D();
    camera.target = player.position;
    camera.offset = new Vector2( screenWidth/2, screenHeight/2 );
    camera.rotation = 0;
    camera.zoom = 1;
    
    // Automation events
    let aelist = LoadAutomationEventList(null);  // Initialize list of automation events to record new events
    SetAutomationEventList(aelist);
    let eventRecording = false;
    let eventPlaying = false;
    
    let frameCounter = 0;
    let playFrameCounter = 0;
    let currentPlayFrame = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){
        // Update
        //----------------------------------------------------------------------------------
        let deltaTime = 0.015;//GetFrameTime();
       
        // Dropped files logic
        //----------------------------------------------------------------------------------
        if (IsFileDropped()) {
            let droppedFiles = LoadDroppedFiles();

            // Supports loading .rgs style files (text or binary) and .png style palette images
            if (IsFileExtension(droppedFiles[0], ".txt;.rae")) {
                UnloadAutomationEventList(aelist);
                aelist = LoadAutomationEventList(droppedFiles[0]);
                
                eventRecording = false;
                
                // Reset scene state to play
                eventPlaying = true;
                playFrameCounter = 0;
                currentPlayFrame = 0;
                
                player.position = new Vector2( 400, 280 );
                player.speed = 0;
                player.canJump = false;

                camera.target = player.position;
                camera.offset = new Vector2( screenWidth/2, screenHeight/2 );
                camera.rotation = 0;
                camera.zoom = 1;
            }
        }
        //----------------------------------------------------------------------------------

        // Update player
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_LEFT)) player.position.x -= PLAYER_HOR_SPD*deltaTime;
        if (IsKeyDown(KEY_RIGHT)) player.position.x += PLAYER_HOR_SPD*deltaTime;
        if (IsKeyDown(KEY_SPACE) && player.canJump) {
            player.speed = -PLAYER_JUMP_SPD;
            player.canJump = false;
        }

        let hitObstacle = 0;
        for (let i = 0; i < MAX_ENVIRONMENT_ELEMENTS; i++) {
            const element = envElements[i];
            let p = player.position;
            if (element.blocking &&
                element.rect.x <= p.x &&
                element.rect.x + element.rect.width >= p.x &&
                element.rect.y >= p.y &&
                element.rect.y <= p.y + player.speed*deltaTime){
                hitObstacle = 1;
                player.speed = 0;
                p.y = element.rect.y;
            }
        }

        if (!hitObstacle) {
            player.position.y += player.speed*deltaTime;
            player.speed += GRAVITY*deltaTime;
            player.canJump = false;
        }
        else player.canJump = true;

        if (IsKeyPressed(KEY_R)) {
            // Reset game state
            player.position = new Vector2( 400, 280 );
            player.speed = 0;
            player.canJump = false;

            camera.target = player.position;
            camera.offset = new Vector2( screenWidth/2, screenHeight/2 );
            camera.rotation = 0;
            camera.zoom = 1;
        }
        //----------------------------------------------------------------------------------

        // Events playing
        // NOTE: Logic must be before Camera update because it depends on mouse-wheel value, 
        // that can be set by the played event... but some other inputs could be affected
        //----------------------------------------------------------------------------------
        if (eventPlaying) {
            // NOTE: Multiple events could be executed in a single frame
            while (playFrameCounter == aelist.events[currentPlayFrame].frame) {
                PlayAutomationEvent(aelist.events[currentPlayFrame]);
                currentPlayFrame++;

                if (currentPlayFrame == aelist.count) {
                    eventPlaying = false;
                    currentPlayFrame = 0;
                    playFrameCounter = 0;

                    TraceLog(LOG_INFO, "FINISH PLAYING!");
                    break;
                }
            }

            playFrameCounter++;
        }
        //----------------------------------------------------------------------------------

        // Update camera
        //----------------------------------------------------------------------------------
        camera.target = player.position;
        camera.offset = new Vector2( screenWidth/2, screenHeight/2 );
        let minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

        // WARNING: On event replay, mouse-wheel internal value is set
        camera.zoom += (GetMouseWheelMove()*0.05);
        if (camera.zoom > 3) camera.zoom = 3;
        else if (camera.zoom < 0.25) camera.zoom = 0.25;

        for (let i = 0; i < MAX_ENVIRONMENT_ELEMENTS; i++) {
            let element = envElements[i];
            minX = Math.min(element.rect.x, minX);
            maxX = Math.max(element.rect.x + element.rect.width, maxX);
            minY = Math.min(element.rect.y, minY);
            maxY = Math.max(element.rect.y + element.rect.height, maxY);
        }

        let max = GetWorldToScreen2D(new Vector2( maxX, maxY ), camera);
        let min = GetWorldToScreen2D(new Vector2( minX, minY ), camera);

        if (max.x < screenWidth) camera.offset.x = screenWidth - (max.x - screenWidth/2);
        if (max.y < screenHeight) camera.offset.y = screenHeight - (max.y - screenHeight/2);
        if (min.x > 0) camera.offset.x = screenWidth/2 - min.x;
        if (min.y > 0) camera.offset.y = screenHeight/2 - min.y;
        //----------------------------------------------------------------------------------
        
        // Events management
        if (IsKeyPressed(KEY_S)){   // Toggle events recording

            if (!eventPlaying) {
                if (eventRecording) {
                    StopAutomationEventRecording();
                    eventRecording = false;
                    
                    ExportAutomationEventList(aelist, "automation.rae");
                    
                    TraceLog(LOG_INFO, "RECORDED FRAMES: "+aelist.count);
                } else {
                    SetAutomationEventBaseFrame(180);
                    StartAutomationEventRecording();
                    eventRecording = true;
                }
            }
        }
        else if (IsKeyPressed(KEY_A)){ // Toggle events playing (WARNING: Starts next frame)
            if (!eventRecording && (aelist.count > 0)) {
                // Reset scene state to play
                eventPlaying = true;
                playFrameCounter = 0;
                currentPlayFrame = 0;

                player.position = new Vector2( 400, 280 );
                player.speed = 0;
                player.canJump = false;

                camera.target = player.position;
                camera.offset = new Vector2( screenWidth/2, screenHeight/2 );
                camera.rotation = 0;
                camera.zoom = 1;
            }
        }

        if (eventRecording || eventPlaying) frameCounter++;
        else frameCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            BeginMode2D(camera);

                // Draw environment elements
                for (let i = 0; i < MAX_ENVIRONMENT_ELEMENTS; i++) {
                    DrawRectangleRec(envElements[i].rect, envElements[i].color);
                }

                // Draw player rectangle
                DrawRectangleRec(new Rectangle( player.position.x - 20, player.position.y - 40, 40, 40 ), RED);

            EndMode2D();
            
            // Draw game controls
            DrawRectangle(10, 10, 290, 145, Fade(SKYBLUE, 0.5));
            DrawRectangleLines(10, 10, 290, 145, Fade(BLUE, 0.8));

            DrawText("Controls:", 20, 20, 10, BLACK);
            DrawText("- RIGHT | LEFT: Player movement", 30, 40, 10, DARKGRAY);
            DrawText("- SPACE: Player jump", 30, 60, 10, DARKGRAY);
            DrawText("- R: Reset game state", 30, 80, 10, DARKGRAY);

            DrawText("- S: START/STOP RECORDING INPUT EVENTS", 30, 110, 10, BLACK);
            DrawText("- A: REPLAY LAST RECORDED INPUT EVENTS", 30, 130, 10, BLACK);

            // Draw automation events recording indicator
            if (eventRecording) {
                DrawRectangle(10, 160, 290, 30, Fade(RED, 0.3));
                DrawRectangleLines(10, 160, 290, 30, Fade(MAROON, 0.8));
                DrawCircle(30, 175, 10, MAROON);

                if (((frameCounter/15)%2) == 1) DrawText(TextFormat("RECORDING EVENTS... [%i]", aelist.count), 50, 170, 10, MAROON);
            } else if (eventPlaying) {
                DrawRectangle(10, 160, 290, 30, Fade(LIME, 0.3));
                DrawRectangleLines(10, 160, 290, 30, Fade(DARKGREEN, 0.8));
                DrawTriangle( new Vector2( 20, 155 + 10 ), new Vector2( 20, 155 + 30 ), new Vector2( 40, 155 + 20 ), DARKGREEN);

                if (((frameCounter/15)%2) == 1) DrawText(TextFormat("PLAYING RECORDED EVENTS... [%i]", currentPlayFrame), 50, 170, 10, DARKGREEN);
            }
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
