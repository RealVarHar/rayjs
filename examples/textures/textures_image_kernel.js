/*******************************************************************************************
*
*   raylib [textures] example - Image loading and texture creation
*
*   Example complexity rating: [★★★★] 4/4
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example contributed by Karim Salem (@kimo-s) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Karim Salem (@kimo-s)
*
********************************************************************************************/

import {BeginDrawing,
    ClearBackground,
    CloseWindow,
    DrawTexture, EndDrawing, ImageCopy, ImageCrop, ImageKernelConvolution, InitWindow, LoadImage, LoadTextureFromImage,
    RAYWHITE, Rectangle,
    SetTargetFPS, UnloadImage, UnloadTexture, WHITE, WindowShouldClose } from "rayjs:raylib";

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
function NormalizeKernel(kernel, size) {
    let sum = 0;
    for (let i = 0; i < size; i++) sum += kernel[i];

    if (sum != 0) {
        for (let i = 0; i < size; i++) kernel[i] /= sum;
    }
}

{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - image convolution");
        
    let image = LoadImage("resources/cat.png");     // Loaded in CPU memory (RAM)

    let gaussiankernel = [
        1, 2, 1,
        2, 4, 2,
        1, 2, 1
    ];

    let sobelkernel = [
        1, 0,-1,
        2, 0,-2,
        1, 0,-1
    ];

    let sharpenkernel = [
        0,-1, 0,
       -1, 5,-1,
        0,-1, 0
    ];

    NormalizeKernel(gaussiankernel, 9);
    NormalizeKernel(sharpenkernel, 9);
    NormalizeKernel(sobelkernel, 9);

    let catSharpend = ImageCopy(image);
    ImageKernelConvolution(catSharpend, sharpenkernel, 9);

    let catSobel = ImageCopy(image);
    ImageKernelConvolution(catSobel, sobelkernel, 9);

    let catGaussian = ImageCopy(image);
    
    for (let i = 0; i < 6; i++) {
        ImageKernelConvolution(catGaussian, gaussiankernel, 9);
    }

    ImageCrop(image, new Rectangle( 0, 0, 200, 450 ));
    ImageCrop(catGaussian, new Rectangle( 0, 0, 200, 450 ));
    ImageCrop(catSobel, new Rectangle( 0, 0, 200, 450 ));
    ImageCrop(catSharpend, new Rectangle( 0, 0, 200, 450 ));
    
    // Images converted to texture, GPU memory (VRAM)
    let texture = LoadTextureFromImage(image);
    let catSharpendTexture = LoadTextureFromImage(catSharpend);
    let catSobelTexture = LoadTextureFromImage(catSobel);
    let catGaussianTexture = LoadTextureFromImage(catGaussian);
    
    // Once images have been converted to texture and uploaded to VRAM, 
    // they can be unloaded from RAM
    UnloadImage(image);
    UnloadImage(catGaussian);
    UnloadImage(catSobel);
    UnloadImage(catSharpend);

    SetTargetFPS(60);     // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

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

            DrawTexture(catSharpendTexture, 0, 0, WHITE);
            DrawTexture(catSobelTexture, 200, 0, WHITE);
            DrawTexture(catGaussianTexture, 400, 0, WHITE);
            DrawTexture(texture, 600, 0, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);
    UnloadTexture(catGaussianTexture);
    UnloadTexture(catSobelTexture);
    UnloadTexture(catSharpendTexture);

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
