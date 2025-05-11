/*******************************************************************************************
*
*   raylib [textures] example - N-patch drawing
*
*   Example complexity rating: [★★★☆] 3/4
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 2.0, last time updated with raylib 2.5
*
*   Example contributed by Jorge A. Gomes (@overdev) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2025 Jorge A. Gomes (@overdev) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    BeginDrawing,
    BLUE,
    ClearBackground, CloseWindow,
    DARKGRAY,
    DrawRectangleLines,
    DrawText,
    DrawTexture,
    DrawTextureNPatch,
    EndDrawing,
    GetMousePosition,
    InitWindow,
    LoadTexture,
    NPATCH_NINE_PATCH,
    NPATCH_THREE_PATCH_HORIZONTAL,
    NPATCH_THREE_PATCH_VERTICAL,
    NPatchInfo,
    RAYWHITE,
    Rectangle,
    SetTargetFPS, UnloadTexture,
    Vector2,
    WHITE,
    WindowShouldClose
} from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - N-patch drawing");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    let nPatchTexture = LoadTexture("resources/ninepatch_button.png");

    let mousePosition = new Vector2();
    let origin = new Vector2( 0, 0 );

    // Position and size of the n-patches
    let dstRec1 = new Rectangle( 480, 160, 32, 32 );
    let dstRec2 = new Rectangle( 160, 160, 32, 32 );
    let dstRecH = new Rectangle( 160, 93 , 32, 32 );
    let dstRecV = new Rectangle( 92 , 160, 32, 32 );

    // A 9-patch (NPATCH_NINE_PATCH) changes its sizes in both axis
    let ninePatchInfo1 = new NPatchInfo( new Rectangle( 0, 0  , 64, 64 ), 12, 40, 12, 12, NPATCH_NINE_PATCH );
    let ninePatchInfo2 = new NPatchInfo( new Rectangle( 0, 128, 64, 64 ), 16, 16, 16, 16, NPATCH_NINE_PATCH );

    // A horizontal 3-patch (NPATCH_THREE_PATCH_HORIZONTAL) changes its sizes along the x axis only
    let h3PatchInfo = new NPatchInfo( new Rectangle( 0,  64, 64, 64 ), 8, 8, 8, 8, NPATCH_THREE_PATCH_HORIZONTAL );

    // A vertical 3-patch (NPATCH_THREE_PATCH_VERTICAL) changes its sizes along the y axis only
    let v3PatchInfo = new NPatchInfo( new Rectangle( 0, 192, 64, 64 ), 6, 6, 6, 6, NPATCH_THREE_PATCH_VERTICAL );

    SetTargetFPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        mousePosition = GetMousePosition();

        // Resize the n-patches based on mouse position
        dstRec1.width = mousePosition.x - dstRec1.x;
        dstRec1.height = mousePosition.y - dstRec1.y;
        dstRec2.width = mousePosition.x - dstRec2.x;
        dstRec2.height = mousePosition.y - dstRec2.y;
        dstRecH.width = mousePosition.x - dstRecH.x;
        dstRecV.height = mousePosition.y - dstRecV.y;

        // Set a minimum width and/or height
        if (dstRec1.width < 1) dstRec1.width = 1;
        if (dstRec1.width > 300) dstRec1.width = 300;
        if (dstRec1.height < 1) dstRec1.height = 1;
        if (dstRec2.width < 1) dstRec2.width = 1;
        if (dstRec2.width > 300) dstRec2.width = 300;
        if (dstRec2.height < 1) dstRec2.height = 1;
        if (dstRecH.width < 1) dstRecH.width = 1;
        if (dstRecV.height < 1) dstRecV.height = 1;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw the n-patches
            DrawTextureNPatch(nPatchTexture, ninePatchInfo2, dstRec2, origin, 0, WHITE);
            DrawTextureNPatch(nPatchTexture, ninePatchInfo1, dstRec1, origin, 0, WHITE);
            DrawTextureNPatch(nPatchTexture, h3PatchInfo, dstRecH, origin, 0, WHITE);
            DrawTextureNPatch(nPatchTexture, v3PatchInfo, dstRecV, origin, 0, WHITE);

            // Draw the source texture
            DrawRectangleLines(5, 88, 74, 266, BLUE);
            DrawTexture(nPatchTexture, 10, 93, WHITE);
            DrawText("TEXTURE", 15, 360, 10, DARKGRAY);

            DrawText("Move the mouse to stretch or shrink the n-patches", 10, 20, 20, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(nPatchTexture);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
