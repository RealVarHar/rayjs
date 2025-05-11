/*******************************************************************************************
*
*   raygui - image exporter
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
********************************************************************************************/

import * as rg from 'rayjs:raygui';
import std from "qjs:std";
import {BeginDrawing,
    CheckCollisionPointRec,
    ClearBackground,
    CloseWindow,
    DARKGRAY,
    DrawRectangle,
    DrawRectangleLinesEx,
    DrawText,
    DrawTextureEx, EndDrawing, ExportImage, ExportImageAsCode, Fade, GetColor, GetFileExtension,
    GetMousePosition, GetMouseWheelMove, GetPixelDataSize, Image,
    ImageFormat, InitWindow, IsFileDropped,
    IsFileExtension, LoadDroppedFiles, LoadImage, LoadTextureFromImage, RAYWHITE, RED, Rectangle, SetTargetFPS,
    TextFormat,
    TextJoin,
    UnloadImage, UnloadTexture, Vector2, WHITE, WindowShouldClose } from 'rayjs:raylib';

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "raygui - image exporter");
    
    // GUI controls initialization
    //----------------------------------------------------------------------------------
    let windowBoxRec = new Rectangle( screenWidth/2 - 110, screenHeight/2 - 100, 220, 190 );
    let windowBoxActive = false;
    
    let fileFormatActive = 0;
    let fileFormatTextList = [ "IMAGE (.png)", "DATA (.raw)", "CODE (.h)" ];

    let pixelFormatActive = 0;
    let pixelFormatTextList = [ "GRAYSCALE", "GRAY ALPHA", "R5G6B5", "R8G8B8", "R5G5B5A1", "R4G4B4A4", "R8G8B8A8" ];

    let textBoxEditMode = false;
    let fileName = "untitled";
    //--------------------------------------------------------------------------------------
    
    let image = new Image();
    let texture = new Texture2D();
    
    let imageLoaded = false;
    let imageScale = 1;
    let imageRec = new Rectangle();

    let btnExportPressed = false;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsFileDropped()) {
            let droppedFiles = LoadDroppedFiles();

            if (droppedFiles.length == 1) {
                let imTemp = LoadImage(droppedFiles[0]);
                
                if (imTemp.data != null) {
                    UnloadImage(image);
                    image = imTemp;
                    
                    UnloadTexture(texture);
                    texture = LoadTextureFromImage(image);
                    
                    imageLoaded = true;
                    pixelFormatActive = image.format - 1;
                    
                    if (texture.height > texture.width) imageScale = (screenHeight - 100)/texture.height;
                    else imageScale = (screenWidth - 100)/texture.width;
                }
            }
        }
    
        if (btnExportPressed) {
            if (imageLoaded) {
                let imageptr = [image];
                ImageFormat(imageptr, pixelFormatActive + 1);
                image = imageptr[0];
                
                if (fileFormatActive == 0) {       // PNG
                    if ((GetFileExtension(fileName) == null) || (!IsFileExtension(fileName, ".png"))){
                        fileName+= ".png"; // No extension provided
                    }
                    ExportImage(image, fileName);
                } else if (fileFormatActive == 1) {  // RAW
                    if ((GetFileExtension(fileName) == null) || (!IsFileExtension(fileName, ".raw"))) {
                        fileName+= ".raw"; // No extension provided
                    }
                    
                    let dataSize = GetPixelDataSize(image.width, image.height, image.format);
                    
                    let rawFile = std.open(fileName, "wb");
                    rawFile.write(image.data, 1, dataSize);
                    rawFile.close();
                } else if (fileFormatActive == 2) {  // CODE

                    ExportImageAsCode(image, fileName);
                }
            }
            
            windowBoxActive = false;
        }
        
        if (imageLoaded) {
            imageScale += GetMouseWheelMove()*0.05;   // Image scale control
            if (imageScale <= 0.1) {
                imageScale = 0.1;
            } else if (imageScale >= 5) {
                imageScale = 5;
            }
            
            imageRec = new Rectangle( screenWidth/2 - image.width*imageScale/2, screenHeight/2 - image.height*imageScale/2, image.width*imageScale, image.height*imageScale );
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (texture.id > 0) {
                DrawTextureEx(texture, new Vector2( screenWidth/2 - texture.width*imageScale/2, screenHeight/2 - texture.height*imageScale/2 ), 0, imageScale, WHITE);
                
                DrawRectangleLinesEx(imageRec, 1, CheckCollisionPointRec(GetMousePosition(), imageRec) ? RED : DARKGRAY); 
                DrawText(TextFormat("SCALE: %.2f%%", imageScale*100), 20, screenHeight - 40, 20, GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.LINE_COLOR)));
            } else {
                DrawText("DRAG & DROP YOUR IMAGE!", 350, 200, 10, DARKGRAY);
                rg.GuiDisable();
            }
            
            if (rg.GuiButton(new Rectangle( screenWidth - 170, screenHeight - 50, 150, 30 ), "Image Export")) windowBoxActive = true;
            rg.GuiEnable();
            
            // Draw window box: windowBoxName
            //-----------------------------------------------------------------------------
            if (windowBoxActive) {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.BACKGROUND_COLOR)), 0.7));
                windowBoxActive = !rg.GuiWindowBox(new Rectangle( windowBoxRec.x, windowBoxRec.y, 220, 190 ), "Image Export Options");

                rg.GuiLabel(new Rectangle( windowBoxRec.x + 10, windowBoxRec.y + 35, 60, 25 ), "File format:");
                let fileFormatActiveptr =[fileFormatActive];
                let pixelFormatActiveptr = [pixelFormatActive];
                rg.GuiComboBox(new Rectangle( windowBoxRec.x + 80, windowBoxRec.y + 35, 130, 25 ), TextJoin(fileFormatTextList, 3, ";"), fileFormatActiveptr);
                rg.GuiLabel(new Rectangle( windowBoxRec.x + 10, windowBoxRec.y + 70, 63, 25 ), "Pixel format:");
                rg.GuiComboBox(new Rectangle( windowBoxRec.x + 80, windowBoxRec.y + 70, 130, 25 ), TextJoin(pixelFormatTextList, 7, ";"), pixelFormatActiveptr);
                fileFormatActive = fileFormatActiveptr[0];
                pixelFormatActive = pixelFormatActiveptr[0];
                rg.GuiLabel(new Rectangle( windowBoxRec.x + 10, windowBoxRec.y + 105, 50, 25 ), "File name:");
                if (rg.GuiTextBox(new Rectangle( windowBoxRec.x + 80, windowBoxRec.y + 105, 130, 25 ), fileName, 64, textBoxEditMode)) textBoxEditMode = !textBoxEditMode;

                btnExportPressed = 1 == rg.GuiButton(new Rectangle( windowBoxRec.x + 10, windowBoxRec.y + 145, 200, 30 ), "Export Image");
            } else {
                btnExportPressed = false;
            }
            
            if (btnExportPressed) DrawText("Image exported!", 20, screenHeight - 20, 20, RED);
            //-----------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadImage(image);
    UnloadTexture(texture);
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
