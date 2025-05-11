/*******************************************************************************************
*
*   raylib [shaders] example - Simple shader mask
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.7
*
*   Example contributed by Chris Camacho (@chriscamacho) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Chris Camacho (@chriscamacho) and Ramon Santamaria (@raysan5)
*
********************************************************************************************
*
*   The shader makes alpha holes in the forground to give the appearance of a top
*   down look at a spotlight casting a pool of light...
*
*   The right hand side of the screen there is just enough light to see whats
*   going on without the spot light, great for a stealth type game where you
*   have to avoid the spotlights.
*
*   The left hand side of the screen is in pitch dark except for where the spotlights are.
*
*   Although this example doesn't scale like the letterbox example, you could integrate
*   the two techniques, but by scaling the actual colour of the render texture rather
*   than using alpha as a mask.
*
********************************************************************************************/

import * as os from 'qjs:os';
import {BeginDrawing, BeginShaderMode, ClearBackground, CloseWindow, DARKBLUE,
    DrawFPS,
    DrawRectangle,
    DrawText, DrawTexture,
    EndDrawing, EndShaderMode, GREEN, GetMousePosition, GetRandomValue, GetScreenHeight, GetScreenWidth,
    GetShaderLocation, HideCursor, InitWindow, LoadShader, LoadTexture,
    SHADER_UNIFORM_FLOAT,
    SHADER_UNIFORM_VEC2,
    SetShaderValue,
    SetTargetFPS,
    TextFormat, UnloadShader, UnloadTexture, Vector2, WHITE, WindowShouldClose } from 'rayjs:raylib';
import * as rm from 'rayjs:raymath';

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}

const MAX_SPOTS = 3;        // NOTE: It must be the same as define in shader
const MAX_STARS = 400;

// Stars in the star field have a position and velocity
class Star{
    ResetStar() {
        this.position = new Vector2( GetScreenWidth()/2, GetScreenHeight()/2 );

        this.speed.x = GetRandomValue(-1000, 1000)/100;
        this.speed.y = GetRandomValue(-1000, 1000)/100;
        do {
            this.speed.x = GetRandomValue(-1000, 1000)/100;
            this.speed.y = GetRandomValue(-1000, 1000)/100;

        } while ((Math.abs(this.speed.x) + (Math.abs(this.speed.y))) <= 1);

        this.position = rm.Vector2Add(this.position, rm.Vector2Multiply(this.speed, new Vector2( 8, 8 )));
    }
    UpdateStar() {
        this.position = rm.Vector2Add(this.position, this.speed);

        //If a star goes off-screen, recycle it
        if ((this.position.x < 0) || (this.position.x > GetScreenWidth()) ||
            (this.position.y < 0) || (this.position.y > GetScreenHeight())) {
            this.ResetStar();
        }
    }

    constructor(){
        this.speed = new Vector2();
        this.ResetStar();
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

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - shader spotlight");
    HideCursor();

    let texRay = LoadTexture("resources/raysan.png");

    let stars = new Array(MAX_STARS);

    for (let n = 0; n < MAX_STARS; n++) stars[n] = new Star();

    // Progress all the stars on, so they don't all start in the centre
    for (let m = 0; m < screenWidth/2.0; m++) {
        for (let n = 0; n < MAX_STARS; n++) stars[n].UpdateStar();
    }

    let frameCounter = 0;

    // Use default vert shader
    let shdrSpot = LoadShader(null, TextFormat("resources/shaders/glsl%i/spotlight.fs", GLSL_VERSION));

    // Get the locations of spots in the shader
    let spots = new Array(MAX_SPOTS);

    for (let i = 0; i < MAX_SPOTS; i++) {
        let posName = "spots[x].pos".replace('[x]','['+i+']');
        let innerName = "spots[x].inner".replace('[x]','['+i+']');
        let radiusName = "spots[x].radius".replace('[x]','['+i+']');

        spots[i].positionLoc = GetShaderLocation(shdrSpot, posName);
        spots[i].innerLoc = GetShaderLocation(shdrSpot, innerName);
        spots[i].radiusLoc = GetShaderLocation(shdrSpot, radiusName);

    }

    // Tell the shader how wide the screen is so we can have
    // a pitch black half and a dimly lit half.
    let wLoc = GetShaderLocation(shdrSpot, "screenWidth");
    let sw = GetScreenWidth();
    SetShaderValue(shdrSpot, wLoc, sw, SHADER_UNIFORM_FLOAT);

    // Randomize the locations and velocities of the spotlights
    // and initialize the shader locations
    for (let i = 0; i < MAX_SPOTS; i++) {
        spots[i].position.x = GetRandomValue(64, screenWidth - 64);
        spots[i].position.y = GetRandomValue(64, screenHeight - 64);
        spots[i].speed = new Vector2( 0, 0 );

        while ((Math.abs(spots[i].speed.x) + Math.abs(spots[i].speed.y)) < 2) {
            spots[i].speed.x = GetRandomValue(-400, 40) / 10;
            spots[i].speed.y = GetRandomValue(-400, 40) / 10;
        }

        spots[i].inner = 28 * (i + 1);
        spots[i].radius = 48 * (i + 1);

        SetShaderValue(shdrSpot, spots[i].positionLoc, spots[i].position.x, SHADER_UNIFORM_VEC2);
        SetShaderValue(shdrSpot, spots[i].innerLoc, spots[i].inner, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shdrSpot, spots[i].radiusLoc, spots[i].radius, SHADER_UNIFORM_FLOAT);
    }

    SetTargetFPS(60);               // Set  to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        frameCounter++;

        // Move the stars, resetting them if the go offscreen
        for (let n = 0; n < MAX_STARS; n++) stars[n].UpdateStar();

        // Update the spots, send them to the shader
        for (let i = 0; i < MAX_SPOTS; i++) {
            if (i == 0) {
                let mp = GetMousePosition();
                spots[i].position.x = mp.x;
                spots[i].position.y = screenHeight - mp.y;
            } else {
                spots[i].position.x += spots[i].speed.x;
                spots[i].position.y += spots[i].speed.y;

                if (spots[i].position.x < 64) spots[i].speed.x = -spots[i].speed.x;
                if (spots[i].position.x > (screenWidth - 64)) spots[i].speed.x = -spots[i].speed.x;
                if (spots[i].position.y < 64) spots[i].speed.y = -spots[i].speed.y;
                if (spots[i].position.y > (screenHeight - 64)) spots[i].speed.y = -spots[i].speed.y;
            }

            SetShaderValue(shdrSpot, spots[i].positionLoc, spots[i].position.x, SHADER_UNIFORM_VEC2);
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKBLUE);

            // Draw stars and bobs
            for (let n = 0; n < MAX_STARS; n++) {
                // Single pixel is just too small these days!
                DrawRectangle(Math.floor(stars[n].position.x), Math.floor(stars[n].position.y), 2, 2, WHITE);
            }

            for (let i = 0; i < 16; i++) {
                DrawTexture(texRay,
                    Math.floor((screenWidth/2) + Math.cos((frameCounter + i*8)/51.45)*(screenWidth/2.2) - 32),
                    Math.floor((screenHeight/2) + Math.sin((frameCounter + i*8)/17.87)*(screenHeight/4.2)), WHITE
                );
            }

            // Draw spot lights
            BeginShaderMode(shdrSpot);
                // Instead of a blank rectangle you could render here
                // a render texture of the full screen used to do screen
                // scaling (slight adjustment to shader would be required
                // to actually pay attention to the colour!)
                DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
            EndShaderMode();

            DrawFPS(10, 10);

            DrawText("Move the mouse!", 10, 30, 20, GREEN);
            DrawText("Pitch Black", Math.floor(screenWidth*0.2), screenHeight/2, 20, GREEN);
            DrawText("Dark", Math.floor(screenWidth*0.66), screenHeight/2, 20, GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texRay);
    UnloadShader(shdrSpot);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}