/*******************************************************************************************
*
*   raylib [textures] example - Draw Textured Polygon
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 3.7, last time updated with raylib 3.7
*
*   Example contributed by Chris Camacho (@chriscamacho) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2025 Chris Camacho (@chriscamacho) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {RL_TRIANGLES, rlBegin, rlColor4ub, rlEnd, rlSetTexture, rlTexCoord2f, rlVertex2f} from "rayjs:rlgl";
import {
    BeginDrawing,
    ClearBackground, CloseWindow, DARKGRAY, DrawText, EndDrawing, GetScreenHeight, GetScreenWidth,
    InitWindow,
    LoadTexture, RAYWHITE,
    SetTargetFPS, UnloadTexture,
    Vector2, WHITE,
    WindowShouldClose
} from "rayjs:raylib";
import {Vector2Rotate} from "rayjs:raymath";

const MAX_POINTS = 11;      // 10 points and back to the start

// Draw textured polygon, defined by vertex and texture coordinates
// NOTE: Polygon center must have straight line path to all points
// without crossing perimeter, points must be in anticlockwise order
function DrawTexturePoly(texture, center, points, texcoords, pointCount, tint) {

    rlBegin(RL_TRIANGLES);

    rlSetTexture(texture.id);

    rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    for (let i = 0; i < pointCount - 1; i++) {
        rlTexCoord2f(0.5, 0.5);
        rlVertex2f(center.x, center.y);

        rlTexCoord2f(texcoords[i].x, texcoords[i].y);
        rlVertex2f(points[i].x + center.x, points[i].y + center.y);

        rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
        rlVertex2f(points[i + 1].x + center.x, points[i + 1].y + center.y);
    }
    rlEnd();

    rlSetTexture(0);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    const DEG2RAD = Math.PI/180;
    
    InitWindow(screenWidth, screenHeight, "raylib [textures] example - textured polygon");

    // Define texture coordinates to map our texture to poly
    let texcoords = [
        new Vector2( 0.75, 0 ),
        new Vector2( 0.25, 0 ),
        new Vector2( 0, 0.5 ),
        new Vector2( 0, 0.75 ),
        new Vector2( 0.25, 1.0),
        new Vector2( 0.375, 0.875),
        new Vector2( 0.625, 0.875),
        new Vector2( 0.75, 1),
        new Vector2( 1, 0.75),
        new Vector2( 1, 0.5),
        new Vector2( 0.75, 0)  // Close the poly
    ];

    // Define the base poly vertices from the UV's
    // NOTE: They can be specified in any other way
    let points = new Array(MAX_POINTS);
    for (let i = 0; i < MAX_POINTS; i++) {
        points[i] = new Vector2((texcoords[i].x - 0.5)*256, (texcoords[i].y - 0.5)*256);
    }
    
    // Define the vertices drawing position
    // NOTE: Initially same as points but updated every frame
    let positions = new Array(MAX_POINTS);
    for (let i = 0; i < MAX_POINTS; i++) positions[i] = points[i];

    // Load texture to be mapped to poly
    let texture = LoadTexture("resources/cat.png");

    let angle = 0;             // Rotation angle (in degrees)

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Update points rotation with an angle transform
        // NOTE: Base points position are not modified
        angle++;
        for (let i = 0; i < MAX_POINTS; i++) positions[i] = Vector2Rotate(points[i], angle*DEG2RAD);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("textured polygon", 20, 20, 20, DARKGRAY);

            DrawTexturePoly(texture, new Vector2( GetScreenWidth()/2, GetScreenHeight()/2 ),
                            positions, texcoords, MAX_POINTS, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture); // Unload texture

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
