/*******************************************************************************************
*
*   raylib [shapes] example - Rectangle advanced
*
*   Example complexity rating: [★★★★] 4/4
*
*   Example originally created with raylib 5.5, last time updated with raylib 5.5
*
*   Example contributed by Everton Jr. (@evertonse) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024-2025 Everton Jr. (@evertonse) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BLACK, BLUE, BeginDrawing, ClearBackground, CloseWindow, Color, DrawRectangleGradientEx,
    EndDrawing,
    GetScreenHeight, Texture as Texture2D,
    GetScreenWidth, GetShapesTexture, GetShapesTextureRectangle, InitWindow,
    PINK,
    RAYWHITE,
    RED,
    Rectangle, SetTargetFPS, Vector2, WindowShouldClose } from 'rayjs:raylib';
import * as rg from 'rayjs:rlgl';
const DEG2RAD = Math.PI/180;
//@texShapes since this is an indirectly exposed (in .c) static texture it is outside of rayjs design to expose this as export
const texShapes = new Texture2D(1,1,1,1,7);

// Draw rectangle with rounded edges and horizontal gradient, with options to choose side of roundness
// NOTE: Adapted from both 'DrawRectangleRounded()' and 'DrawRectangleGradientH()' raylib [rshapes] implementations
function DrawRectangleRoundedGradientH(rec, roundnessLeft, roundnessRight, segments, left, right) {
    // Neither side is rounded
    if ((roundnessLeft <= 0 && roundnessRight <= 0) || (rec.width < 1) || (rec.height < 1 )) {
        DrawRectangleGradientEx(rec, left, left, right, right);
        return;
    }

    if (roundnessLeft  >= 1) roundnessLeft  = 1;
    if (roundnessRight >= 1) roundnessRight = 1;

    // Calculate corner radius both from right and left
    let recSize = rec.width > rec.height ? rec.height : rec.width;
    let radiusLeft  = (recSize*roundnessLeft)/2;
    let radiusRight = (recSize*roundnessRight)/2;

    if (radiusLeft  <= 0) radiusLeft  = 0;
    if (radiusRight <= 0) radiusRight = 0;

    if (radiusRight <= 0 && radiusLeft <= 0) return;

    let stepLength = 90/segments;

    /*
    Diagram Copied here for reference, original at 'DrawRectangleRounded()' source code

          P0____________________P1
          /|                    |\
         /1|          2         |3\
     P7 /__|____________________|__\ P2
       |   |P8                P9|   |
       | 8 |          9         | 4 |
       | __|____________________|__ |
     P6 \  |P11              P10|  / P3
         \7|          6         |5/
          \|____________________|/
          P5                    P4
    */

    // Coordinates of the 12 points also apdated from `DrawRectangleRounded`
    const point = [
        // PO, P1, P2
        new Vector2(rec.x + radiusLeft, rec.y), new Vector2(rec.x + rec.width - radiusRight, rec.y), new Vector2(rec.x + rec.width, rec.y + radiusRight),
        // P3, P4
        new Vector2(rec.x + rec.width, rec.y + rec.height - radiusRight), new Vector2(rec.x + rec.width - radiusRight, rec.y + rec.height),
        // P5, P6, P7
        new Vector2(rec.x + radiusLeft, rec.y + rec.height), new Vector2(rec.x, rec.y + rec.height - radiusLeft), new Vector2(rec.x, rec.y + radiusLeft),
        // P8, P9
        new Vector2(rec.x + radiusLeft, rec.y + radiusLeft), new Vector2(rec.x + rec.width - radiusRight, rec.y + radiusRight),
        // P10, P11
        new Vector2(rec.x + rec.width - radiusRight, rec.y + rec.height - radiusRight), new Vector2(rec.x + radiusLeft, rec.y + rec.height - radiusLeft)
    ];

    const centers = [ point[8], point[9], point[10], point[11] ];
    const angles = [ 180, 270, 0, 90 ];

    // SUPPORT_QUADS_DRAW_MODE is always 1 from config.h, also for this reason this #def is not exposed in modules yet
    // #if defined(SUPPORT_QUADS_DRAW_MODE)


    rg.rlSetTexture(GetShapesTexture().id);
    let shapeRect = GetShapesTextureRectangle();

    rg.rlBegin(rg.RL_QUADS);
    // Draw all the 4 corners: [1] Upper Left Corner, [3] Upper Right Corner, [5] Lower Right Corner, [7] Lower Left Corner
    for (let k = 0; k < 4; k++) {
        let color;
        let radius;
        if (k == 0) {color = left;  radius = radiusLeft; }  // [1] Upper Left Corner
        if (k == 1) {color = right; radius = radiusRight;}  // [3] Upper Right Corner
        if (k == 2) {color = right; radius = radiusRight;}  // [5] Lower Right Corner
        if (k == 3) {color = left;  radius = radiusLeft; }  // [7] Lower Left Corner
        let angle = angles[k];
        const center = centers[k];

        //texShapes is a static from rshapes

        for (let i = 0; i < segments/2; i++) {
            rg.rlColor4ub(color.r, color.g, color.b, color.a);
            rg.rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
            rg.rlVertex2f(center.x, center.y);

            rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
            rg.rlVertex2f(center.x + Math.cos(DEG2RAD*(angle + stepLength*2))*radius, center.y + Math.sin(DEG2RAD*(angle + stepLength*2))*radius);

            rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
            rg.rlVertex2f(center.x + Math.cos(DEG2RAD*(angle + stepLength))*radius, center.y + Math.sin(DEG2RAD*(angle + stepLength))*radius);

            rg.rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
            rg.rlVertex2f(center.x + Math.cos(DEG2RAD*angle)*radius, center.y + Math.sin(DEG2RAD*angle)*radius);

            angle += (stepLength*2);
        }

        // End one even segments
        if ( segments % 2) {
            rg.rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
            rg.rlVertex2f(center.x, center.y);

            rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
            rg.rlVertex2f(center.x + Math.cos(DEG2RAD*(angle + stepLength))*radius, center.y + Math.sin(DEG2RAD*(angle + stepLength))*radius);

            rg.rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
            rg.rlVertex2f(center.x + Math.cos(DEG2RAD*angle)*radius, center.y + Math.sin(DEG2RAD*angle)*radius);

            rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
            rg.rlVertex2f(center.x, center.y);
        }
    }

    // Here we use the 'Diagram' to guide ourselves to which point receives what color
    // By choosing the color correctly associated with a pointe the gradient effect
    // will naturally come from OpenGL interpolation

    // [2] Upper Rectangle
    rg.rlColor4ub(left.r, left.g, left.b, left.a);
    rg.rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
    rg.rlVertex2f(point[0].x, point[0].y);
    rg.rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
    rg.rlVertex2f(point[8].x, point[8].y);

    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
    rg.rlVertex2f(point[9].x, point[9].y);

    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
    rg.rlVertex2f(point[1].x, point[1].y);

    // [4] Left Rectangle
    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
    rg.rlVertex2f(point[2].x, point[2].y);
    rg.rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
    rg.rlVertex2f(point[9].x, point[9].y);
    rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
    rg.rlVertex2f(point[10].x, point[10].y);
    rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
    rg.rlVertex2f(point[3].x, point[3].y);

    // [6] Bottom Rectangle
    rg.rlColor4ub(left.r, left.g, left.b, left.a);
    rg.rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
    rg.rlVertex2f(point[11].x, point[11].y);
    rg.rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
    rg.rlVertex2f(point[5].x, point[5].y);

    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
    rg.rlVertex2f(point[4].x, point[4].y);
    rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
    rg.rlVertex2f(point[10].x, point[10].y);

    // [8] left Rectangle
    rg.rlColor4ub(left.r, left.g, left.b, left.a);
    rg.rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
    rg.rlVertex2f(point[7].x, point[7].y);
    rg.rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
    rg.rlVertex2f(point[6].x, point[6].y);
    rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
    rg.rlVertex2f(point[11].x, point[11].y);
    rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
    rg.rlVertex2f(point[8].x, point[8].y);

    // [9] Middle Rectangle
    rg.rlColor4ub(left.r, left.g, left.b, left.a);
    rg.rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
    rg.rlVertex2f(point[8].x, point[8].y);
    rg.rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
    rg.rlVertex2f(point[11].x, point[11].y);

    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
    rg.rlVertex2f(point[10].x, point[10].y);
    rg.rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
    rg.rlVertex2f(point[9].x, point[9].y);

    rg.rlEnd();
    rg.rlSetTexture(0);

    // Here we use the 'Diagram' to guide ourselves to which point receives what color.
    // By choosing the color correctly associated with a pointe the gradient effect
    // will naturally come from OpenGL interpolation.
    // But this time instead of Quad, we think in triangles.

    rg.rlBegin(rg.RL_TRIANGLES);
    // Draw all of the 4 corners: [1] Upper Left Corner, [3] Upper Right Corner, [5] Lower Right Corner, [7] Lower Left Corner
    for (let k = 0; k < 4; k++) {
        let color = new Color();
        let radius = 0;
        if(k == 0){color =  left; radius = radiusLeft; }    // [1] Upper Left Corner
        if(k == 1){color = right; radius = radiusRight;}    // [3] Upper Right Corner
        if(k == 2){color = right; radius = radiusRight;}    // [5] Lower Right Corner
        if(k == 3){color =  left; radius = radiusLeft; }    // [7] Lower Left Corner

        let angle = angles[k];
        const center = centers[k];

        for (let i = 0; i < segments; i++) {
            rg.rlColor4ub(color.r, color.g, color.b, color.a);
            rg.rlVertex2f(center.x, center.y);
            rg.rlVertex2f(center.x + Math.cos(DEG2RAD*(angle + stepLength))*radius, center.y + Math.sin(DEG2RAD*(angle + stepLength))*radius);
            rg.rlVertex2f(center.x + Math.cos(DEG2RAD*angle)*radius, center.y + Math.sin(DEG2RAD*angle)*radius);
            angle += stepLength;
        }
    }

    // [2] Upper Rectangle
    rg.rlColor4ub(left.r, left.g, left.b, left.a);
    rg.rlVertex2f(point[0].x, point[0].y);
    rg.rlVertex2f(point[8].x, point[8].y);
    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlVertex2f(point[9].x, point[9].y);
    rg.rlVertex2f(point[1].x, point[1].y);
    rg.rlColor4ub(left.r, left.g, left.b, left.a);
    rg.rlVertex2f(point[0].x, point[0].y);
    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlVertex2f(point[9].x, point[9].y);

    // [4] Right Rectangle
    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlVertex2f(point[9].x, point[9].y);
    rg.rlVertex2f(point[10].x, point[10].y);
    rg.rlVertex2f(point[3].x, point[3].y);
    rg.rlVertex2f(point[2].x, point[2].y);
    rg.rlVertex2f(point[9].x, point[9].y);
    rg.rlVertex2f(point[3].x, point[3].y);

    // [6] Bottom Rectangle
    rg.rlColor4ub(left.r, left.g, left.b, left.a);
    rg.rlVertex2f(point[11].x, point[11].y);
    rg.rlVertex2f(point[5].x, point[5].y);
    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlVertex2f(point[4].x, point[4].y);
    rg.rlVertex2f(point[10].x, point[10].y);
    rg.rlColor4ub(left.r, left.g, left.b, left.a);
    rg.rlVertex2f(point[11].x, point[11].y);
    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlVertex2f(point[4].x, point[4].y);

    // [8] Left Rectangle
    rg.rlColor4ub(left.r, left.g, left.b, left.a);
    rg.rlVertex2f(point[7].x, point[7].y);
    rg.rlVertex2f(point[6].x, point[6].y);
    rg.rlVertex2f(point[11].x, point[11].y);
    rg.rlVertex2f(point[8].x, point[8].y);
    rg.rlVertex2f(point[7].x, point[7].y);
    rg.rlVertex2f(point[11].x, point[11].y);

    // [9] Middle Rectangle
    rg.rlColor4ub(left.r, left.g, left.b, left.a);
    rg.rlVertex2f(point[8].x, point[8].y);
    rg.rlVertex2f(point[11].x, point[11].y);
    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlVertex2f(point[10].x, point[10].y);
    rg.rlVertex2f(point[9].x, point[9].y);
    rg.rlColor4ub(left.r, left.g, left.b, left.a);
    rg.rlVertex2f(point[8].x, point[8].y);
    rg.rlColor4ub(right.r, right.g, right.b, right.a);
    rg.rlVertex2f(point[10].x, point[10].y);
    rg.rlEnd();
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - rectangle avanced");
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update rectangle bounds
        //----------------------------------------------------------------------------------
        let width = GetScreenWidth()/2, height = GetScreenHeight()/6;
        let rec = new Rectangle(
            GetScreenWidth()  / 2 - width/2,
            GetScreenHeight() / 2 - 5*(height/2),
            width, height
        );
        //--------------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Draw All Rectangles with different roundess  for each side and different gradients
            DrawRectangleRoundedGradientH(rec, 0.8, 0.8, 36, BLUE, RED);

            rec.y += rec.height + 1;
            DrawRectangleRoundedGradientH(rec, 0.5, 1, 36, RED, PINK);

            rec.y += rec.height + 1;
            DrawRectangleRoundedGradientH(rec, 1, 0.5, 36, RED, BLUE);

            rec.y += rec.height + 1;
            DrawRectangleRoundedGradientH(rec, 0, 1, 36, BLUE, BLACK);

            rec.y += rec.height + 1;
            DrawRectangleRoundedGradientH(rec, 1, 0, 36, BLUE, PINK);
        EndDrawing();
        //--------------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}