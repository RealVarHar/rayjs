/*******************************************************************************************
*
*   raylib [core] example - 2d camera mouse zoom
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2024 Jeffery Myers (@JeffM2501)
*
********************************************************************************************/

import * as rl from 'rayjs:raylib';
import * as rlgl from 'rayjs:rlgl';
import * as raymath from 'rayjs:raymath';
for (const key in rl) { globalThis[key] = rl[key] };
for (const key in rlgl) { globalThis[key] = rlgl[key] };
for (const key in raymath) { globalThis[key] = raymath[key] };

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

// Initialization
//--------------------------------------------------------------------------------------
var screenWidth = 800;
var screenHeight = 450;

initWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera mouse zoom");

var camera = new Camera2D();
camera.zoom = 1;

let zoomMode = 0;   // 0-Mouse Wheel, 1-Mouse Move

setTargetFPS(60);                   // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!windowShouldClose())        // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    if (isKeyPressed(KEY_ONE)) zoomMode = 0;
    else if (isKeyPressed(KEY_TWO)) zoomMode = 1;
    
    // Translate based on mouse right click
    if (isMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        let delta = getMouseDelta();
        delta = vector2Scale(delta, -1/camera.zoom);
        camera.target = vector2Add(camera.target, delta);
    }

    if (zoomMode == 0)
    {
        // Zoom based on mouse wheel
        let wheel = getMouseWheelMove();
        if (wheel != 0)
        {
            // Get the world point that is under the mouse
            let mouseWorldPos = getScreenToWorld2D(getMousePosition(), camera);

            // Set the offset to where the mouse is
            camera.offset = getMousePosition();

            // Set the target to match, so that the camera maps the world space point 
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            let scaleFactor = 1 + (0.25*Math.abs(wheel));
            if (wheel < 0) scaleFactor = 1.0/scaleFactor;
            camera.zoom = clamp(camera.zoom*scaleFactor, 0.125, 64);
        }
    }
    else
    {
        // Zoom based on mouse left click
        if (isMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Get the world point that is under the mouse
            let mouseWorldPos = getScreenToWorld2D(getMousePosition(), camera);

            // Set the offset to where the mouse is
            camera.offset = getMousePosition();

            // Set the target to match, so that the camera maps the world space point 
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;
        }
        if (isMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            // Zoom increment
            let deltaX = getMouseDelta().x;
            let scaleFactor = 1 + (0.01*Math.abs(deltaX));
            if (deltaX < 0) scaleFactor = 1/scaleFactor;
            camera.zoom = clamp(camera.zoom*scaleFactor, 0.125, 64);
        }
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    beginDrawing();
        clearBackground(RAYWHITE);

        beginMode2D(camera);

            // Draw the 3d grid, rotated 90 degrees and centered around 0,0 
            // just so we have something in the XY plane
            rlPushMatrix();
                rlTranslatef(0, 25*50, 0);
                rlRotatef(90, 1, 0, 0);
                drawGrid(100, 50);
            rlPopMatrix();

            // Draw a reference circle
            drawCircle(getScreenWidth()/2, getScreenHeight()/2, 50, MAROON);
            
        endMode2D();

        drawText("[1][2] Select mouse zoom mode (Wheel or Move)", 20, 20, 20, DARKGRAY);
        if (zoomMode == 0) drawText("Mouse right button drag to move, mouse wheel to zoom", 20, 50, 20, DARKGRAY);
        else drawText("Mouse right button drag to move, mouse press and move to zoom", 20, 50, 20, DARKGRAY);
    
    endDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
closeWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------