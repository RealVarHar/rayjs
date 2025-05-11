/*******************************************************************************************
*
*   raylib [models] example - Draw textured cube
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import { InitWindow,Camera3D as Camera, Vector3, CAMERA_PERSPECTIVE, LoadTexture, SetTargetFPS, WindowShouldClose, BeginDrawing, ClearBackground, RAYWHITE, BeginMode3D, WHITE, Rectangle, DrawGrid, EndMode3D, DrawFPS, EndDrawing, UnloadTexture, CloseWindow } from 'rayjs:raylib';
import * as rg from 'rayjs:rlgl';

//------------------------------------------------------------------------------------
// Custom Functions Declaration
//------------------------------------------------------------------------------------
// Draw cube textured
// NOTE: Cube position is the center position
function DrawCubeTexture(texture, position, width, height, length, color) {
    let x = position.x;
    let y = position.y;
    let z = position.z;

    // Set desired texture to be enabled while drawing following vertex data
    rg.rlSetTexture(texture.id);

    // Vertex data transformation can be defined with the commented lines,
    // but in this example we calculate the transformed vertex data directly when calling rlVertex3f()
    //rlPushMatrix();
    // NOTE: Transformation is applied in inverse order (scale -> rotate -> translate)
    //rlTranslatef(2.0f, 0.0f, 0.0f);
    //rlRotatef(45, 0, 1, 0);
    //rlScalef(2.0f, 2.0f, 2.0f);

    rg.rlBegin(rg.RL_QUADS);
    rg.rlColor4ub(color.r, color.g, color.b, color.a);
    // Front Face
    rg.rlNormal3f(0, 0, 1);       // Normal Pointing Towards Viewer
    rg.rlTexCoord2f(0, 0); rg.rlVertex3f(x - width/2, y - height/2, z + length/2);  // Bottom Left Of The Texture and Quad
    rg.rlTexCoord2f(1, 0); rg.rlVertex3f(x + width/2, y - height/2, z + length/2);  // Bottom Right Of The Texture and Quad
    rg.rlTexCoord2f(1, 1); rg.rlVertex3f(x + width/2, y + height/2, z + length/2);  // Top Right Of The Texture and Quad
    rg.rlTexCoord2f(0, 1); rg.rlVertex3f(x - width/2, y + height/2, z + length/2);  // Top Left Of The Texture and Quad
    // Back Face
    rg.rlNormal3f(0, 0, -1);     // Normal Pointing Away From Viewer
    rg.rlTexCoord2f(1, 0); rg.rlVertex3f(x - width/2, y - height/2, z - length/2);  // Bottom Right Of The Texture and Quad
    rg.rlTexCoord2f(1, 1); rg.rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
    rg.rlTexCoord2f(0, 1); rg.rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
    rg.rlTexCoord2f(0, 0); rg.rlVertex3f(x + width/2, y - height/2, z - length/2);  // Bottom Left Of The Texture and Quad
    // Top Face
    rg.rlNormal3f(0, 1, 0);       // Normal Pointing Up
    rg.rlTexCoord2f(0, 1); rg.rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
    rg.rlTexCoord2f(0, 0); rg.rlVertex3f(x - width/2, y + height/2, z + length/2);  // Bottom Left Of The Texture and Quad
    rg.rlTexCoord2f(1, 0); rg.rlVertex3f(x + width/2, y + height/2, z + length/2);  // Bottom Right Of The Texture and Quad
    rg.rlTexCoord2f(1, 1); rg.rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
    // Bottom Face
    rg.rlNormal3f(0, -1, 0);     // Normal Pointing Down
    rg.rlTexCoord2f(1, 1); rg.rlVertex3f(x - width/2, y - height/2, z - length/2);  // Top Right Of The Texture and Quad
    rg.rlTexCoord2f(0, 1); rg.rlVertex3f(x + width/2, y - height/2, z - length/2);  // Top Left Of The Texture and Quad
    rg.rlTexCoord2f(0, 0); rg.rlVertex3f(x + width/2, y - height/2, z + length/2);  // Bottom Left Of The Texture and Quad
    rg.rlTexCoord2f(1, 0); rg.rlVertex3f(x - width/2, y - height/2, z + length/2);  // Bottom Right Of The Texture and Quad
    // Right face
    rg.rlNormal3f(1, 0, 0);       // Normal Pointing Right
    rg.rlTexCoord2f(1, 0); rg.rlVertex3f(x + width/2, y - height/2, z - length/2);  // Bottom Right Of The Texture and Quad
    rg.rlTexCoord2f(1, 1); rg.rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
    rg.rlTexCoord2f(0, 1); rg.rlVertex3f(x + width/2, y + height/2, z + length/2);  // Top Left Of The Texture and Quad
    rg.rlTexCoord2f(0, 0); rg.rlVertex3f(x + width/2, y - height/2, z + length/2);  // Bottom Left Of The Texture and Quad
    // Left Face
    rg.rlNormal3f( -1, 0, 0);    // Normal Pointing Left
    rg.rlTexCoord2f(0, 0); rg.rlVertex3f(x - width/2, y - height/2, z - length/2);  // Bottom Left Of The Texture and Quad
    rg.rlTexCoord2f(1, 0); rg.rlVertex3f(x - width/2, y - height/2, z + length/2);  // Bottom Right Of The Texture and Quad
    rg.rlTexCoord2f(1, 1); rg.rlVertex3f(x - width/2, y + height/2, z + length/2);  // Top Right Of The Texture and Quad
    rg.rlTexCoord2f(0, 1); rg.rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
    rg.rlEnd();
    //rlPopMatrix();

    rg.rlSetTexture(0);
}
// Draw cube with texture piece applied to all faces
function DrawCubeTextureRec(texture, source, position, width, height, length, color) {
    let x = position.x;
    let y = position.y;
    let z = position.z;
    let texWidth = texture.width;
    let texHeight = texture.height;

    // Set desired texture to be enabled while drawing following vertex data
    rg.rlSetTexture(texture.id);

    // We calculate the normalized texture coordinates for the desired texture-source-rectangle
    // It means converting from (tex.width, tex.height) coordinates to [0.0f, 1.0f] equivalent
    rg.rlBegin(rg.RL_QUADS);
    rg.rlColor4ub(color.r, color.g, color.b, color.a);

    // Front face
    rg.rlNormal3f(0, 0, 1);
    rg.rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x - width/2, y - height/2, z + length/2);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x + width/2, y - height/2, z + length/2);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
    rg.rlVertex3f(x + width/2, y + height/2, z + length/2);
    rg.rlTexCoord2f(source.x/texWidth, source.y/texHeight);
    rg.rlVertex3f(x - width/2, y + height/2, z + length/2);

    // Back face
    rg.rlNormal3f(0, 0, -1);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x - width/2, y - height/2, z - length/2);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
    rg.rlVertex3f(x - width/2, y + height/2, z - length/2);
    rg.rlTexCoord2f(source.x/texWidth, source.y/texHeight);
    rg.rlVertex3f(x + width/2, y + height/2, z - length/2);
    rg.rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x + width/2, y - height/2, z - length/2);

    // Top face
    rg.rlNormal3f(0, 1, 0);
    rg.rlTexCoord2f(source.x/texWidth, source.y/texHeight);
    rg.rlVertex3f(x - width/2, y + height/2, z - length/2);
    rg.rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x - width/2, y + height/2, z + length/2);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x + width/2, y + height/2, z + length/2);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
    rg.rlVertex3f(x + width/2, y + height/2, z - length/2);

    // Bottom face
    rg.rlNormal3f(0, -1, 0);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
    rg.rlVertex3f(x - width/2, y - height/2, z - length/2);
    rg.rlTexCoord2f(source.x/texWidth, source.y/texHeight);
    rg.rlVertex3f(x + width/2, y - height/2, z - length/2);
    rg.rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x + width/2, y - height/2, z + length/2);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x - width/2, y - height/2, z + length/2);

    // Right face
    rg.rlNormal3f(1, 0, 0);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x + width/2, y - height/2, z - length/2);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
    rg.rlVertex3f(x + width/2, y + height/2, z - length/2);
    rg.rlTexCoord2f(source.x/texWidth, source.y/texHeight);
    rg.rlVertex3f(x + width/2, y + height/2, z + length/2);
    rg.rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x + width/2, y - height/2, z + length/2);

    // Left face
    rg.rlNormal3f( -1, 0, 0);
    rg.rlTexCoord2f(source.x/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x - width/2, y - height/2, z - length/2);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, (source.y + source.height)/texHeight);
    rg.rlVertex3f(x - width/2, y - height/2, z + length/2);
    rg.rlTexCoord2f((source.x + source.width)/texWidth, source.y/texHeight);
    rg.rlVertex3f(x - width/2, y + height/2, z + length/2);
    rg.rlTexCoord2f(source.x/texWidth, source.y/texHeight);
    rg.rlVertex3f(x - width/2, y + height/2, z - length/2);

    rg.rlEnd();

    rg.rlSetTexture(0);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - draw cube texture");

    // Define the camera to look into our 3d world
    let camera = new Camera();
    camera.position = new Vector3( 0, 10, 10 );
    camera.target = new Vector3( 0, 0, 0 );
    camera.up = new Vector3( 0, 1, 0 );
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;
    
    // Load texture to be applied to the cubes sides
    let texture = LoadTexture("resources/cubicmap_atlas.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                // Draw cube with an applied texture
                DrawCubeTexture(texture, new Vector3( -2, 2, 0 ), 2, 4, 2, WHITE);

                // Draw cube with an applied texture, but only a defined rectangle piece of the texture
                DrawCubeTextureRec(texture, new Rectangle( 0, texture.height/2, texture.width/2, texture.height/2 ),
                    new Vector3( 2, 1, 0 ), 2, 2, 2, WHITE);

                DrawGrid(10, 1);        // Draw a grid

            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture); // Unload texture
    
    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}