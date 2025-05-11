/*******************************************************************************************
*
*   raylib [textures] example - Draw part of the texture tiled
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 3.0, last time updated with raylib 4.2
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2025 Vlad Adrian (@demizdor) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    DrawTexturePro, FLAG_WINDOW_RESIZABLE, InitWindow, LoadTexture, Rectangle, SetConfigFlags, SetTextureFilter, TEXTURE_FILTER_TRILINEAR,
    BLACK, MAROON, ORANGE, BLUE, PURPLE, BEIGE, LIME, RED, DARKGRAY, SKYBLUE, SetTargetFPS, WindowShouldClose, IsMouseButtonPressed, MOUSE_BUTTON_LEFT, GetMousePosition, CheckCollisionPointRec, IsKeyPressed, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, BeginDrawing, ClearBackground, RAYWHITE, Vector2, GetScreenWidth, GetScreenHeight, ColorAlpha, LIGHTGRAY, DrawRectangle, DrawText, DrawTexture, DARKBLUE, DrawRectangleRec, CloseWindow, UnloadTexture, EndDrawing, TextFormat, GetFPS, DrawRectangleLinesEx, WHITE
} from "rayjs:raylib";


let OPT_WIDTH   = 220;       // Max width for the options container
let MARGIN_SIZE =   8;       // Size for the margins
let COLOR_SIZE  =  16;       // Size of the color select buttons

// Draw part of a texture (defined by a rectangle) with rotation and scale tiled into dest.
function DrawTextureTiled(texture, source, dest, origin, rotation, scale, tint) {
    if ((texture.id <= 0) || (scale <= 0)) return;
    if ((source.width == 0) || (source.height == 0)) return;

    let tileWidth = Math.floor(source.width*scale), tileHeight = Math.floor(source.height*scale);
    if ((dest.width < tileWidth) && (dest.height < tileHeight)) {
        // Can fit only one tile
        DrawTexturePro(texture, new Rectangle( source.x, source.y, dest.width/tileWidth*source.width, dest.height/tileHeight*source.height),
        new Rectangle(dest.x, dest.y, dest.width, dest.height), origin, rotation, tint);
    } else if (dest.width <= tileWidth) {
        // Tiled vertically (one column)
        let dy = 0;
        for (;dy+tileHeight < dest.height; dy += tileHeight) {
            DrawTexturePro(texture, new Rectangle( source.x, source.y, dest.width/tileWidth*source.width, source.height), new Rectangle( dest.x, dest.y + dy, dest.width, tileHeight), origin, rotation, tint);
        }

        // Fit last tile
        if (dy < dest.height) {
            DrawTexturePro(texture, new Rectangle( source.x, source.y, dest.width/tileWidth*source.width, (dest.height - dy)/tileHeight*source.height),
            new Rectangle(dest.x, dest.y + dy, dest.width, dest.height - dy), origin, rotation, tint);
        }
    } else if (dest.height <= tileHeight) {
        // Tiled horizontally (one row)
        let dx = 0;
        for (;dx+tileWidth < dest.width; dx += tileWidth) {
            DrawTexturePro(texture, new Rectangle(source.x, source.y, source.width, dest.height/tileHeight*source.height), new Rectangle(dest.x + dx, dest.y, tileWidth, dest.height), origin, rotation, tint);
        }

        // Fit last tile
        if (dx < dest.width) {
            DrawTexturePro(texture, new Rectangle(source.x, source.y, (dest.width - dx)/tileWidth*source.width, dest.height/tileHeight*source.height),
            new Rectangle(dest.x + dx, dest.y, dest.width - dx, dest.height), origin, rotation, tint);
        }
    } else {
        // Tiled both horizontally and vertically (rows and columns)
        let dx = 0;
        for (;dx+tileWidth < dest.width; dx += tileWidth) {
            let dy = 0;
            for (;dy+tileHeight < dest.height; dy += tileHeight) {
                DrawTexturePro(texture, source, new Rectangle(dest.x + dx, dest.y + dy, tileWidth, tileHeight), origin, rotation, tint);
            }

            if (dy < dest.height) {
                DrawTexturePro(texture, new Rectangle(source.x, source.y, source.width, ((dest.height - dy)/tileHeight)*source.height),
                new Rectangle(dest.x + dx, dest.y + dy, tileWidth, dest.height - dy), origin, rotation, tint);
            }
        }

        // Fit last column of tiles
        if (dx < dest.width) {
            let dy = 0;
            for (;dy+tileHeight < dest.height; dy += tileHeight) {
                DrawTexturePro(texture, new Rectangle(source.x, source.y, (dest.width - dx)/tileWidth*source.width, source.height),
                new Rectangle(dest.x + dx, dest.y + dy, dest.width - dx, tileHeight), origin, rotation, tint);
            }

            // Draw final tile in the bottom right corner
            if (dy < dest.height) {
                DrawTexturePro(texture, new Rectangle(source.x, source.y, (dest.width - dx)/tileWidth*source.width, (dest.height - dy)/tileHeight*source.height),
                new Rectangle(dest.x + dx, dest.y + dy, dest.width - dx, dest.height - dy), origin, rotation, tint);
            }
        }
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

    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Make the window resizable
    InitWindow(screenWidth, screenHeight, "raylib [textures] example - Draw part of a texture tiled");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    let texPattern = LoadTexture("resources/patterns.png");
    SetTextureFilter(texPattern, TEXTURE_FILTER_TRILINEAR); // Makes the texture smoother when upscaled

    // Coordinates for all patterns inside the texture
    const recPattern = [
        new Rectangle( 3, 3, 66, 66 ),
        new Rectangle( 75, 3, 100, 100 ),
        new Rectangle( 3, 75, 66, 66 ),
        new Rectangle( 7, 156, 50, 50 ),
        new Rectangle( 85, 106, 90, 45 ),
        new Rectangle( 75, 154, 100, 60)
    ];

    // Setup colors
    const colors = [ BLACK, MAROON, ORANGE, BLUE, PURPLE, BEIGE, LIME, RED, DARKGRAY, SKYBLUE ];
    const MAX_COLORS = colors.length;
    let colorRec = new Array(MAX_COLORS);

    // Calculate rectangle for each color
    for (let i = 0, x = 0, y = 0; i < MAX_COLORS; i++) {
        colorRec[i] = new Rectangle();
        colorRec[i].x = 2 + MARGIN_SIZE + x;
        colorRec[i].y = 22 + 256 + MARGIN_SIZE + y;
        colorRec[i].width = COLOR_SIZE*2;
        colorRec[i].height = COLOR_SIZE;

        if (i == (MAX_COLORS/2 - 1)) {
            x = 0;
            y += COLOR_SIZE + MARGIN_SIZE;
        }
        else x += (COLOR_SIZE*2 + MARGIN_SIZE);
    }

    let activePattern = 0, activeCol = 0;
    let scale = 1, rotation = 0;

    SetTargetFPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Handle mouse
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            const mouse = GetMousePosition();

            // Check which pattern was clicked and set it as the active pattern
            for (let i = 0; i < recPattern.length; i++){
                if (CheckCollisionPointRec(mouse, new Rectangle( 2 + MARGIN_SIZE + recPattern[i].x, 40 + MARGIN_SIZE + recPattern[i].y, recPattern[i].width, recPattern[i].height ))) {
                    activePattern = i;
                    break;
                }
            }

            // Check to see which color was clicked and set it as the active color
            for (let i = 0; i < MAX_COLORS; ++i) {
                if (CheckCollisionPointRec(mouse, colorRec[i])) {
                    activeCol = i;
                    break;
                }
            }
        }

        // Handle keys

        // Change scale
        if (IsKeyPressed(KEY_UP)) scale += 0.25;
        if (IsKeyPressed(KEY_DOWN)) scale -= 0.25;
        if (scale > 10) scale = 10;
        else if ( scale <= 0) scale = 0.25;

        // Change rotation
        if (IsKeyPressed(KEY_LEFT)) rotation -= 25;
        if (IsKeyPressed(KEY_RIGHT)) rotation += 25;

        // Reset
        if (IsKeyPressed(KEY_SPACE)) { rotation = 0; scale = 1; }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Draw the tiled area
            DrawTextureTiled(texPattern, recPattern[activePattern], new Rectangle(OPT_WIDTH+MARGIN_SIZE, MARGIN_SIZE, GetScreenWidth() - OPT_WIDTH - 2*MARGIN_SIZE, GetScreenHeight() - 2*MARGIN_SIZE),
                new Vector2(0, 0), rotation, scale, colors[activeCol]);

            // Draw options
            DrawRectangle(MARGIN_SIZE, MARGIN_SIZE, OPT_WIDTH - MARGIN_SIZE, GetScreenHeight() - 2*MARGIN_SIZE, ColorAlpha(LIGHTGRAY, 0.5));

            DrawText("Select Pattern", 2 + MARGIN_SIZE, 30 + MARGIN_SIZE, 10, BLACK);
            DrawTexture(texPattern, 2 + MARGIN_SIZE, 40 + MARGIN_SIZE, BLACK);
            DrawRectangle(2 + MARGIN_SIZE + Math.floor(recPattern[activePattern].x), 40 + MARGIN_SIZE + Math.floor(recPattern[activePattern].y), Math.floor(recPattern[activePattern].width), Math.floor(recPattern[activePattern].height), ColorAlpha(DARKBLUE, 0.3));

            DrawText("Select Color", 2+MARGIN_SIZE, 10+256+MARGIN_SIZE, 10, BLACK);
            for (let i = 0; i < MAX_COLORS; i++) {
                DrawRectangleRec(colorRec[i], colors[i]);
                if (activeCol == i) DrawRectangleLinesEx(colorRec[i], 3, ColorAlpha(WHITE, 0.5));
            }

            DrawText("Scale (UP/DOWN to change)", 2 + MARGIN_SIZE, 80 + 256 + MARGIN_SIZE, 10, BLACK);
            DrawText(TextFormat("%.2fx", scale), 2 + MARGIN_SIZE, 92 + 256 + MARGIN_SIZE, 20, BLACK);

            DrawText("Rotation (LEFT/RIGHT to change)", 2 + MARGIN_SIZE, 122 + 256 + MARGIN_SIZE, 10, BLACK);
            DrawText(TextFormat("%.0f degrees", rotation), 2 + MARGIN_SIZE, 134 + 256 + MARGIN_SIZE, 20, BLACK);

            DrawText("Press [SPACE] to reset", 2 + MARGIN_SIZE, 164 + 256 + MARGIN_SIZE, 10, DARKBLUE);

            // Draw FPS
            DrawText(TextFormat("%i FPS", GetFPS()), 2 + MARGIN_SIZE, 2 + MARGIN_SIZE, 20, BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texPattern);        // Unload texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}