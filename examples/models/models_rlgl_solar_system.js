/*******************************************************************************************
*
*   raylib [models] example - rlgl module usage with push/pop matrix transformations
*
*   Example complexity rating: [★★★★] 4/4
*
*   NOTE: This example uses [rlgl] module functionality (pseudo-OpenGL 1.1 style coding)
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, SetTargetFPS, WindowShouldClose, UpdateCamera, CAMERA_ORBITAL, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, GOLD, BLUE, LIGHTGRAY, DrawCircle3D, Fade, RED, DrawGrid, EndMode3D, DrawText, MAROON, DrawFPS, EndDrawing, CloseWindow } from 'rayjs:raylib';
import * as rg from 'rayjs:rlgl';
const DEG2RAD = Math.PI/180;
//------------------------------------------------------------------------------------
// Module Functions Declaration
//------------------------------------------------------------------------------------
// Draw sphere without any matrix transformation
// NOTE: Sphere is drawn in world position ( 0, 0, 0 ) with radius 1.0f
function DrawSphereBasic(color) {
    const rings = 16;
    const slices = 16;

    // Make sure there is enough space in the internal render batch
    // buffer to store all required vertex, batch is reseted if required
    rg.rlCheckRenderBatchLimit((rings + 2)*slices*6);

    rg.rlBegin(rg.RL_TRIANGLES);
    rg.rlColor4ub(color.r, color.g, color.b, color.a);

    for (let i = 0; i < (rings + 2); i++) {
        for (let j = 0; j < slices; j++) {
            rg.rlVertex3f(Math.cos(DEG2RAD*(270+(180/(rings + 1))*i))*Math.sin(DEG2RAD*(j*360/slices)),
                Math.sin(DEG2RAD*(270+(180/(rings + 1))*i)),
                Math.cos(DEG2RAD*(270+(180/(rings + 1))*i))*Math.cos(DEG2RAD*(j*360/slices)));
            rg.rlVertex3f(Math.cos(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*Math.sin(DEG2RAD*((j+1)*360/slices)),
                Math.sin(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                Math.cos(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*Math.cos(DEG2RAD*((j+1)*360/slices)));
            rg.rlVertex3f(Math.cos(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*Math.sin(DEG2RAD*(j*360/slices)),
                Math.sin(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                Math.cos(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*Math.cos(DEG2RAD*(j*360/slices)));

            rg.rlVertex3f(Math.cos(DEG2RAD*(270+(180/(rings + 1))*i))*Math.sin(DEG2RAD*(j*360/slices)),
                Math.sin(DEG2RAD*(270+(180/(rings + 1))*i)),
                Math.cos(DEG2RAD*(270+(180/(rings + 1))*i))*Math.cos(DEG2RAD*(j*360/slices)));
            rg.rlVertex3f(Math.cos(DEG2RAD*(270+(180/(rings + 1))*(i)))*Math.sin(DEG2RAD*((j+1)*360/slices)),
                Math.sin(DEG2RAD*(270+(180/(rings + 1))*(i))),
                Math.cos(DEG2RAD*(270+(180/(rings + 1))*(i)))*Math.cos(DEG2RAD*((j+1)*360/slices)));
            rg.rlVertex3f(Math.cos(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*Math.sin(DEG2RAD*((j+1)*360/slices)),
                Math.sin(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                Math.cos(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*Math.cos(DEG2RAD*((j+1)*360/slices)));
        }
    }
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

    const sunRadius = 4;
    const earthRadius = 0.6;
    const earthOrbitRadius = 8;
    const moonRadius = 0.16;
    const moonOrbitRadius = 1.5;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - rlgl module usage with push/pop matrix transformations");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 16, 16, 16 ); // Camera position
    camera.target = new Vector3( 0, 0, 0 );      // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );          // Camera up vector (rotation towards target)
    camera.fovy = 45;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    let rotationSpeed = 0.2;         // General system rotation speed

    let earthRotation = 0;         // Rotation of earth around itself (days) in degrees
    let earthOrbitRotation = 0;    // Rotation of earth around the Sun (years) in degrees
    let moonRotation = 0;          // Rotation of moon around itself
    let moonOrbitRotation = 0;     // Rotation of moon around earth in degrees

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, CAMERA_ORBITAL);

        earthRotation += (5*rotationSpeed);
        earthOrbitRotation += (365/360*(5*rotationSpeed)*rotationSpeed);
        moonRotation += (2*rotationSpeed);
        moonOrbitRotation += (8*rotationSpeed);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                rg.rlPushMatrix();
                    rg.rlScalef(sunRadius, sunRadius, sunRadius);          // Scale Sun
                    DrawSphereBasic(GOLD);                              // Draw the Sun
                rg.rlPopMatrix();

                rg.rlPushMatrix();
                    rg.rlRotatef(earthOrbitRotation, 0, 1, 0);    // Rotation for Earth orbit around Sun
                    rg.rlTranslatef(earthOrbitRadius, 0, 0);         // Translation for Earth orbit

                    rg.rlPushMatrix();
                        rg.rlRotatef(earthRotation, 0.25, 1.0, 0.0);       // Rotation for Earth itself
                        rg.rlScalef(earthRadius, earthRadius, earthRadius);// Scale Earth

                        DrawSphereBasic(BLUE);                          // Draw the Earth
                    rg.rlPopMatrix();

                    rg.rlRotatef(moonOrbitRotation, 0, 1, 0);     // Rotation for Moon orbit around Earth
                    rg.rlTranslatef(moonOrbitRadius, 0, 0);          // Translation for Moon orbit
                    rg.rlRotatef(moonRotation, 0, 1, 0);          // Rotation for Moon itself
                    rg.rlScalef(moonRadius, moonRadius, moonRadius);       // Scale Moon

                    DrawSphereBasic(LIGHTGRAY);                         // Draw the Moon
                rg.rlPopMatrix();

                // Some reference elements (not affected by previous matrix transformations)
                DrawCircle3D(new Vector3( 0, 0, 0 ), earthOrbitRadius, new Vector3( 1, 0, 0 ), 90, Fade(RED, 0.5));
                DrawGrid(20, 1);

            EndMode3D();

            DrawText("EARTH ORBITING AROUND THE SUN!", 400, 10, 20, MAROON);
            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
}