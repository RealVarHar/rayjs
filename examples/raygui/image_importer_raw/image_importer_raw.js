/*******************************************************************************************
*
*   raygui - image raw importer
*
*   DEPENDENCIES:
*       raylib 4.0  - Windowing/input management and drawing.
*       raygui 3.0  - Immediate-mode GUI controls.
*
*   COMPILATION (Windows - MinGW):
*       gcc -o $(NAME_PART).exe $(FILE_NAME) -I../../src -lraylib -lopengl32 -lgdi32 -std=c99
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
**********************************************************************************************/

import * as rg from 'rayjs:raygui';
import std from "qjs:std";
import {
    BeginDrawing,
    ClearBackground,
    CloseWindow,
    DrawText,
    DrawTextureEx,
    EndDrawing,
    GetColor,
    GetFileName,
    GetMouseWheelMove, InitWindow,IsFileDropped,IsFileExtension,LOG_WARNING,LoadDroppedFiles,LoadImageRaw,LoadTextureFromImage,PIXELFORMAT_UNCOMPRESSED_GRAYSCALE,PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA,PIXELFORMAT_UNCOMPRESSED_R32,PIXELFORMAT_UNCOMPRESSED_R32G32B32,PIXELFORMAT_UNCOMPRESSED_R32G32B32A32,PIXELFORMAT_UNCOMPRESSED_R8G8B8,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,Rectangle,SetTargetFPS,TextFormat,TextJoin,Texture2D,
    TraceLog,
    UnloadImage,
    UnloadTexture, Vector2,
    WHITE, WindowShouldClose } from 'rayjs:raylib';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //---------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raygui - image raw importer");
    
    let texture = new Texture2D();

    // GUI controls initialization
    //----------------------------------------------------------------------------------
    let windowOffset = new Vector2( screenWidth/2 - 200/2, screenHeight/2 - 465/2 );

    let importWindowActive = false;

    let widthValue = 0;
    let widthEditMode = false;
    let heightValue = 0;
    let heightEditMode = false;

    let pixelFormatActive = 0;
    let pixelFormatTextList = [ "CUSTOM", "GRAYSCALE", "GRAY ALPHA", "R5G6B5", "R8G8B8", "R5G5B5A1", "R4G4B4A4", "R8G8B8A8" ];

    let channelsActive = 3;
    let channelsTextList = [ "1", "2", "3", "4" ];
    let bitDepthActive = 0;
    let bitDepthTextList = [ "8", "16", "32" ];
    
    let headerSizeValue = 0;
    let headerSizeEditMode = false;
    //----------------------------------------------------------------------------------
    
    // Image file info
    let dataSize = 0;
    let fileNamePath = "";
    let fileName = "";
    
    let btnLoadPressed = false;
    
    let imageLoaded = false;
    let imageScale = 1;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Check if a file is dropped
        if (IsFileDropped()) {
            let droppedFiles = LoadDroppedFiles();

            // Check file extensions for drag-and-drop
            if ((droppedFiles.length == 1) && IsFileExtension(droppedFiles[0], ".raw")) {
                let imageFile = std.open(droppedFiles[0], "rb");
                imageFile.seek(0, std.SEEK_END);
                dataSize = imageFile.tell();
                imageFile.close();
                
                // NOTE: Returned string is just a pointer to droppedFiles[0],
                // we need to make a copy of that data somewhere else: fileName
                fileNamePath = droppedFiles[0];
                fileName = GetFileName(droppedFiles[0]);
                
                // Try to guess possible raw values
                // Let's assume image is square, RGBA, 8 bit per channel
                widthValue = Math.round(Math.sqrt(dataSize/4));
                heightValue = widthValue;
                headerSizeValue = dataSize - widthValue*heightValue*4;
                if (headerSizeValue < 0) headerSizeValue = 0;

                importWindowActive = true;
            }
        }
        
        // Check if load button has been pressed
        if (btnLoadPressed) {
            // Depending on channels and bit depth, select correct pixel format
            if ((widthValue != 0) && (heightValue != 0)) {
                let format = -1;

                if (pixelFormatActive == 0) {
                    let channels = Number(channelsTextList[channelsActive]);
                    let bpp = Number(bitDepthTextList[bitDepthActive]);
            
                    // Select correct format depending on channels and bpp
                    if (bpp == 8) {
                        if (channels == 1) format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
                        else if (channels == 2) format = PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA;
                        else if (channels == 3) format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
                        else if (channels == 4) format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
                    } else if (bpp == 32) {
                        if (channels == 1) format = PIXELFORMAT_UNCOMPRESSED_R32;
                        else if (channels == 2) TraceLog(LOG_WARNING, "Channel bit-depth not supported!");
                        else if (channels == 3) format = PIXELFORMAT_UNCOMPRESSED_R32G32B32;
                        else if (channels == 4) format = PIXELFORMAT_UNCOMPRESSED_R32G32B32A32;
                    } else if (bpp == 16) {
                        TraceLog(LOG_WARNING, "Channel bit-depth not supported!");
                    }
                } else {
                    format = pixelFormatActive;
                }
                
                if (format != -1) {
                    let image = LoadImageRaw(fileNamePath, widthValue, heightValue, format, headerSizeValue);
                    texture = LoadTextureFromImage(image);
                    UnloadImage(image);
                    
                    importWindowActive = false;
                    btnLoadPressed = false;
                    
                    if (texture.id > 0) {
                        imageLoaded = true;
                        imageScale = (screenHeight - 100)/texture.height;
                    }
                }
            }
        }
        
        if (imageLoaded) imageScale += GetMouseWheelMove();   // Image scale control
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.BACKGROUND_COLOR)));
            
            if (texture.id != 0) {
                DrawTextureEx(texture, new Vector2( screenWidth/2 - texture.width*imageScale/2, screenHeight/2 - texture.height*imageScale/2 ), 0, imageScale, WHITE);
                DrawText(TextFormat("SCALE x%.0f", imageScale), 20, screenHeight - 40, 20, GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.LINE_COLOR)));
            } else {
                DrawText("drag & drop RAW image file", 320, 180, 10, GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.LINE_COLOR)));
            }

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (importWindowActive) {
                importWindowActive = !rg.GuiWindowBox(new Rectangle( windowOffset.x + 0, windowOffset.y + 0, 200, 465 ), "Image RAW Import Options");

                rg.GuiLabel(new Rectangle( windowOffset.x + 10, windowOffset.y + 30, 65, 20 ), "Import file:");
                rg.GuiLabel(new Rectangle( windowOffset.x + 85, windowOffset.y + 30, 75, 20 ), fileName);
                rg.GuiLabel(new Rectangle( windowOffset.x + 10, windowOffset.y + 50, 65, 20 ), "File size:");
                rg.GuiLabel(new Rectangle( windowOffset.x + 85, windowOffset.y + 50, 75, 20 ), TextFormat("%i bytes", dataSize));
                rg.GuiGroupBox(new Rectangle( windowOffset.x + 10, windowOffset.y + 85, 180, 80 ), "Resolution");
                rg.GuiLabel(new Rectangle( windowOffset.x + 20, windowOffset.y + 100, 33, 25 ), "Width:");

                let widthValueptr = [widthValue];
                let heightValueptr = [heightValue];
                let pixelFormatActiveptr = [pixelFormatActive];
                let channelsActiveptr = [channelsActive];
                let bitDepthActiveptr = [bitDepthActive];
                let headerSizeValueptr = [headerSizeValue];

                if (rg.GuiValueBox(new Rectangle( windowOffset.x + 60, windowOffset.y + 100, 80, 25 ), null, widthValueptr, 0, 8192, widthEditMode)) widthEditMode = !widthEditMode;
                rg.GuiLabel(new Rectangle( windowOffset.x + 145, windowOffset.y + 100, 30, 25 ), "pixels");
                rg.GuiLabel(new Rectangle( windowOffset.x + 20, windowOffset.y + 130, 33, 25 ), "Height:");
                if (rg.GuiValueBox(new Rectangle( windowOffset.x + 60, windowOffset.y + 130, 80, 25 ), null, heightValueptr, 0, 8192, heightEditMode)) heightEditMode = !heightEditMode;
                rg.GuiLabel(new Rectangle( windowOffset.x + 145, windowOffset.y + 130, 30, 25 ), "pixels");
                rg.GuiGroupBox(new Rectangle( windowOffset.x + 10, windowOffset.y + 180, 180, 160 ), "Pixel Format");
                rg.GuiComboBox(new Rectangle( windowOffset.x + 20, windowOffset.y + 195, 160, 25 ), TextJoin(pixelFormatTextList, 8, ";"), pixelFormatActiveptr);
                rg.GuiLine(new Rectangle( windowOffset.x + 20, windowOffset.y + 220, 160, 20 ), null);
                
                if (pixelFormatActive != 0) rg.GuiDisable();
                rg.GuiLabel(new Rectangle( windowOffset.x + 20, windowOffset.y + 235, 50, 20 ), "Channels:");
                rg.GuiToggleGroup(new Rectangle( windowOffset.x + 20, windowOffset.y + 255, 156/4, 25 ), TextJoin(channelsTextList, 4, ";"), channelsActiveptr);
                rg.GuiLabel(new Rectangle( windowOffset.x + 20, windowOffset.y + 285, 50, 20 ), "Bit Depth:");
                rg.GuiToggleGroup(new Rectangle( windowOffset.x + 20, windowOffset.y + 305, 160/3, 25 ), TextJoin(bitDepthTextList, 3, ";"), bitDepthActiveptr);
                rg.GuiEnable();

                rg.GuiGroupBox(new Rectangle( windowOffset.x + 10, windowOffset.y + 355, 180, 50 ), "Header");
                rg.GuiLabel(new Rectangle( windowOffset.x + 25, windowOffset.y + 370, 27, 25 ), "Size:");
                if (rg.GuiValueBox(new Rectangle( windowOffset.x + 55, windowOffset.y + 370, 85, 25 ), null, headerSizeValueptr, 0, 10000, headerSizeEditMode)) headerSizeEditMode = !headerSizeEditMode;
                rg.GuiLabel(new Rectangle( windowOffset.x + 145, windowOffset.y + 370, 30, 25 ), "bytes");

                widthValue = widthValueptr[0];
                heightValue = heightValueptr[0];
                pixelFormatActive = pixelFormatActiveptr[0];
                channelsActive = channelsActiveptr[0];
                bitDepthActive = bitDepthActive[0];
                headerSizeValue = headerSizeValueptr[0];
                
                btnLoadPressed = 1 == rg.GuiButton(new Rectangle( windowOffset.x + 10, windowOffset.y + 420, 180, 30 ), "Import RAW");
            }
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    if (texture.id != 0) UnloadTexture(texture);
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
