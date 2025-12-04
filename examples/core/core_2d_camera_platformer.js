/*******************************************************************************************
 *
 *   raylib [core] example - 2D Camera platformer
 *
 *   Example complexity rating: [★★★☆] 3/4
 *
 *   Example originally created with raylib 2.5, last time updated with raylib 3.0
 *
 *   Example contributed by arvyy (@arvyy) and reviewed by Ramon Santamaria (@raysan5)
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2019-2025 arvyy (@arvyy)
 *
 ********************************************************************************************/

import {
    BeginDrawing, BeginMode2D, BLACK, Camera2D, ClearBackground, CloseWindow, DARKGRAY, DrawCircleV, DrawRectangleRec, DrawText, EndDrawing, EndMode2D, GetFrameTime, GetMouseWheelMove, GetScreenToWorld2D, GetWorldToScreen2D, GOLD, GRAY, InitWindow, IsKeyDown, IsKeyPressed, KEY_C, KEY_LEFT, KEY_R, KEY_RIGHT, KEY_SPACE, LIGHTGRAY, Rectangle, RED, SetTargetFPS, Vector2, WindowShouldClose
} from "rayjs:raylib";
import {Vector2Add, Vector2Length, Vector2Scale, Vector2Subtract} from "rayjs:raymath";
{

    const G=400;
    const PLAYER_JUMP_SPD=350;
    const PLAYER_HOR_SPD=200;

    class Player{
        constructor(position,speed,canJump){
            this.position=position;
            this.speed=speed;
            this.canJump=canJump;
        }
    }
    class EnvItem{
        constructor(rect,blocking,color){
            this.rect=rect;
            this.blocking=blocking;
            this.color=color;
        }
    }

    //----------------------------------------------------------------------------------
    // Module functions declaration
    //----------------------------------------------------------------------------------
    function UpdatePlayer(player,envItems,delta){
        if (IsKeyDown(KEY_LEFT)) player.position.x -= PLAYER_HOR_SPD*delta;
        if (IsKeyDown(KEY_RIGHT)) player.position.x += PLAYER_HOR_SPD*delta;
        if (IsKeyDown(KEY_SPACE) && player.canJump) {
            player.speed = -PLAYER_JUMP_SPD;
            player.canJump = false;
        }

        let hitObstacle = false;
        for (let i = 0; i < envItems.length; i++){
            const ei = envItems[i];
            const p = player.position;
            if (ei.blocking &&
                ei.rect.x <= p.x &&
                ei.rect.x + ei.rect.width >= p.x &&
                ei.rect.y >= p.y &&
                ei.rect.y <= p.y + player.speed*delta)
            {
                hitObstacle = true;
                player.speed = 0;
                p.y = ei.rect.y;
                break;
            }
        }

        if (!hitObstacle) {
            player.position.y += player.speed*delta;
            player.speed += G*delta;
            player.canJump = false;
        }
        else player.canJump = true;
    }
    function UpdateCameraCenter(camera, player, envItems, delta, width, height){
        camera.offset = new Vector2(width/2, height/2);
        camera.target = player.position;
    }

    function UpdateCameraCenterInsideMap(camera, player, envItems, delta, width, height){
        camera.target = player.position;
        camera.offset = new Vector2(width/2, height/2);
        let minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

        for (let i = 0; i < envItems.length; i++){
            let ei = envItems[i];
            minX = Math.min(ei.rect.x, minX);
            maxX = Math.max(ei.rect.x + ei.rect.width, maxX);
            minY = Math.min(ei.rect.y, minY);
            maxY = Math.max(ei.rect.y + ei.rect.height, maxY);
        }

        const max = GetWorldToScreen2D(new Vector2(maxX, maxY), camera);
        const min = GetWorldToScreen2D(new Vector2(minX, minY), camera);

        if (max.x < width) camera.offset.x = width - (max.x - width/2);
        if (max.y < height) camera.offset.y = height - (max.y - height/2);
        if (min.x > 0) camera.offset.x = width/2 - min.x;
        if (min.y > 0) camera.offset.y = height/2 - min.y;
    }

    function UpdateCameraCenterSmoothFollow(camera, player, envItems, delta, width, height){
        const minSpeed = 30;
        const minEffectLength = 10;
        const fractionSpeed = 0.8;
        try{
            camera.offset = new Vector2(width/2, height/2);
            const diff = Vector2Subtract(player.position, camera.target);
            const length = Vector2Length(diff);
            if (length > minEffectLength) {
                const speed = Math.max(fractionSpeed*length, minSpeed);
                camera.target = Vector2Add(camera.target, Vector2Scale(diff, speed*delta/length));
            }
        }catch(e){
            console.log("ERROR");
        }
    }

    let eveningOut = false;
    let evenOutTarget;
    function UpdateCameraEvenOutOnLanding(camera, player, envItems, delta, width, height){
        const evenOutSpeed = 700;

        camera.offset = new Vector2(width/2, height/2);
        camera.target.x = player.position.x;

        if (eveningOut) {
            if (evenOutTarget > camera.target.y){
                camera.target.y += evenOutSpeed*delta;
                if (camera.target.y > evenOutTarget) {
                    camera.target.y = evenOutTarget;
                    eveningOut = false;
                }
            }else{
                camera.target.y -= evenOutSpeed*delta;
                if (camera.target.y < evenOutTarget) {
                    camera.target.y = evenOutTarget;
                    eveningOut = false;
                }
            }
        }else {
            if (player.canJump && (player.speed === 0) && (player.position.y !== camera.target.y)){
                eveningOut = true;
                evenOutTarget = player.position.y;
            }
        }
    }

    function UpdateCameraPlayerBoundsPush(camera, player, envItems, delta, width, height){
        const bbox = { x: 0.2,y: 0.2 };

        const bboxWorldMin = GetScreenToWorld2D(new Vector2((1 - bbox.x)*0.5*width, (1 - bbox.y)*0.5*height), camera);
        const bboxWorldMax = GetScreenToWorld2D(new Vector2((1 + bbox.x)*0.5*width, (1 + bbox.y)*0.5*height), camera);
        camera.offset = new Vector2((1 - bbox.x)*0.5 * width, (1 - bbox.y)*0.5*height);
        console.log(player.position.x,bboxWorldMin.x,camera.target.x);
        try{
            console.log("1");
            if (player.position.x < bboxWorldMin.x) camera.target.x = player.position.x;//not working, fix bindings
            console.log("2");
            if (player.position.y < bboxWorldMin.y) camera.target.y = player.position.y;
            console.log("3");
            if (player.position.x > bboxWorldMax.x) camera.target.x = bboxWorldMin.x + (player.position.x - bboxWorldMax.x);
            console.log("4");
            if (player.position.y > bboxWorldMax.y) camera.target.y = bboxWorldMin.y + (player.position.y - bboxWorldMax.y);
            console.log("5");
        }catch(e){
            console.log("ERROR");
        }
    }

    //------------------------------------------------------------------------------------
    // Program main entry point
    //------------------------------------------------------------------------------------
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");

    const player = new Player(new Vector2(400, 280), 0 ,false);
    const envItems = [
        new EnvItem(new Rectangle(0, 0, 1000, 400), 0, LIGHTGRAY ),
        new EnvItem(new Rectangle(0, 400, 1000, 200), 1, GRAY ),
        new EnvItem(new Rectangle(300, 200, 400, 10), 1, GRAY ),
        new EnvItem(new Rectangle(250, 300, 100, 10), 1, GRAY ),
        new EnvItem(new Rectangle(650, 300, 100, 10), 1, GRAY )
    ];

    const camera = new Camera2D();
    camera.target = player.position;
    camera.offset = new Vector2(screenWidth/2, screenHeight/2 );
    camera.rotation = 0;
    camera.zoom = 1;

    // Store pointers to the multiple update camera functions
    const cameraUpdaters=[
        UpdateCameraCenter,
        UpdateCameraCenterInsideMap,
        UpdateCameraCenterSmoothFollow,
        UpdateCameraEvenOutOnLanding,
        UpdateCameraPlayerBoundsPush
    ];

    let cameraOption = 0;

    const cameraDescriptions = [
        "Follow player center",
        "Follow player center, but clamp to map edges",
        "Follow player center; smoothed",
        "Follow player center horizontally; update player center vertically after landing",
        "Player push camera on getting too close to screen edge"
    ];

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        let deltaTime = GetFrameTime();

        UpdatePlayer(player, envItems, deltaTime);

        camera.zoom += (GetMouseWheelMove()*0.05);

        if (camera.zoom > 3) {
            camera.zoom = 3;
        }else if (camera.zoom < 0.25){
            camera.zoom = 0.25;
        }

        if (IsKeyPressed(KEY_R)) {
            camera.zoom = 1;
            player.position = new Vector2(400, 280);
        }

        if (IsKeyPressed(KEY_C)) {
            cameraOption = (cameraOption + 1)%cameraUpdaters.length;
        }

        // Call update camera function by its pointer
        cameraUpdaters[cameraOption](camera, player, envItems, deltaTime, screenWidth, screenHeight);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        BeginMode2D(camera);

        for (let i = 0; i < envItems.length; i++) {
            DrawRectangleRec(envItems[i].rect, envItems[i].color);
        }

        const playerRect = new Rectangle(player.position.x - 20, player.position.y - 40, 40, 40);
        DrawRectangleRec(playerRect, RED);

        DrawCircleV(player.position, 5, GOLD);

        EndMode2D();

        DrawText("Controls:", 20, 20, 10, BLACK);
        DrawText("- Right/Left to move", 40, 40, 10, DARKGRAY);
        DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
        DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 80, 10, DARKGRAY);
        DrawText("- C to change camera mode", 40, 100, 10, DARKGRAY);
        DrawText("Current camera mode:", 20, 120, 10, BLACK);
        DrawText(cameraDescriptions[cameraOption], 40, 140, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}