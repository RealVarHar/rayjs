import * as rl from 'rayjs:raylib';
for (const key in rl) { globalThis[key] = rl[key] };

/*******************************************************************************************
*
*   raylib [shapes] example - draw circle sector (with gui options)
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2023 Vlad Adrian (@demizdor) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/
// Initialization
//--------------------------------------------------------------------------------------
const screenWidth = 800;
const screenHeight = 450;

initWindow(screenWidth, screenHeight, "raylib [shapes] example - draw circle sector");

const center = new Vector2((getScreenWidth() - 300)/2.0, getScreenHeight()/2.0);

let outerRadius = [180.0];
let startAngle = [0.0];
let endAngle = [180.0];
let segments = [0];
let minSegments = 4;

setTargetFPS(60);               // Set our game to run at 60 frames-per-second
//--------------------------------------------------------------------------------------

// Main game loop
while (!windowShouldClose())    // Detect window close button or ESC key
{
    // Update
    //----------------------------------------------------------------------------------
    // NOTE: All variables update happens inside GUI control functions
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    beginDrawing();

        clearBackground(RAYWHITE);

        drawLine(500, 0, 500, getScreenHeight(), fade(LIGHTGRAY, 0.6));
        drawRectangle(500, 0, getScreenWidth() - 500, getScreenHeight(), fade(LIGHTGRAY, 0.3));

        drawCircleSector(center, outerRadius[0], startAngle[0], endAngle[0], segments[0], fade(MAROON, 0.3));
        drawCircleSectorLines(center, outerRadius[0], startAngle[0], endAngle[0], segments[0], fade(MAROON, 0.6));

        // Draw GUI controls
        //------------------------------------------------------------------------------
		try{
		let r=new Rectangle(600, 40, 120, 20);
        guiSliderBar(new Rectangle(600, 40, 120, 20), "StartAngle", textFormat("%.2f", startAngle[0]), startAngle, 0, 720);
        guiSliderBar(new Rectangle(600, 70, 120, 20), "EndAngle", textFormat("%.2f", endAngle[0]), endAngle, 0, 720);

        guiSliderBar(new Rectangle(600, 140, 120, 20), "Radius", textFormat("%.2f", outerRadius[0]), outerRadius, 0, 200);
        guiSliderBar(new Rectangle(600, 170, 120, 20), "Segments", textFormat("%.2f", segments[0]), segments, 0, 100);
        //------------------------------------------------------------------------------

        minSegments = Math.ceil((endAngle[0] - startAngle[0]) / 90);
        drawText("MODE: " + (segments[0] >= minSegments) ? "MANUAL" : "AUTO", 600, 200, 10, (segments[0] >= minSegments)? MAROON : DARKGRAY);
		}catch(e){
			console.log(e);
		}
        drawFPS(10, 10);

    endDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
closeWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------