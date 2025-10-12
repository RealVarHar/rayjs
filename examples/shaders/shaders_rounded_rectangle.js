/*******************************************************************************************
*
*   raylib [shaders] example - Rounded Rectangle
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 5.5, last time updated with raylib 5.5
*
*   Example contributed by Anstro Pleuton (@anstropleuton) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2025-2025 Anstro Pleuton (@anstropleuton)
*
********************************************************************************************/

import * as os from 'qjs:os';
import {BLACK, BLUE,
    BeginDrawing,
    BeginShaderMode,
    ClearBackground,
    CloseWindow,
    DARKBLUE, DARKGRAY, DrawRectangle, DrawRectangleLines, DrawText, EndDrawing, EndShaderMode, GetShaderLocation,
    InitWindow, LoadShader,
    RAYWHITE, Rectangle, SHADER_UNIFORM_FLOAT, SHADER_UNIFORM_VEC2, SHADER_UNIFORM_VEC4, SKYBLUE, SetShaderValue,
    SetTargetFPS, TextFormat,
    UnloadShader,
    Vector2, Vector4, WHITE, WindowShouldClose } from 'rayjs:raylib';

let GLSL_VERSION;
if(['Andriod','iOS'].includes(os.platform)){
    GLSL_VERSION = 100;
}else{
    GLSL_VERSION = 330;
}

//------------------------------------------------------------------------------------
// Declare custom Structs
//------------------------------------------------------------------------------------

// Rounded rectangle data
class RoundedRectangle{
    // Update rounded rectangle uniforms
    UpdateRoundedRectangle(shader) {
        SetShaderValue(shader, this.radiusLoc, [ this.cornerRadius.x, this.cornerRadius.y, this.cornerRadius.z, this.cornerRadius.w ], SHADER_UNIFORM_VEC4);
        SetShaderValue(shader, this.shadowRadiusLoc, this.shadowRadius, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, this.shadowOffsetLoc, [ this.shadowOffset.x, this.shadowOffset.y ], SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, this.shadowScaleLoc, this.shadowScale, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, this.borderThicknessLoc, this.borderThickness, SHADER_UNIFORM_FLOAT);
    }

    // Create a rounded rectangle and set uniform locations
    constructor(cornerRadius, shadowRadius, shadowOffset, shadowScale, borderThickness, shader) {
        this.cornerRadius = cornerRadius;
        this.shadowRadius = shadowRadius;
        this.shadowOffset = shadowOffset;
        this.shadowScale = shadowScale;

        // Border variables
        this.borderThickness = borderThickness;

        // Get shader uniform locations
        this.rectangleLoc = GetShaderLocation(shader, "rectangle");
        this.radiusLoc = GetShaderLocation(shader, "radius");
        this.colorLoc = GetShaderLocation(shader, "color");
        this.shadowRadiusLoc = GetShaderLocation(shader, "shadowRadius");
        this.shadowOffsetLoc = GetShaderLocation(shader, "shadowOffset");
        this.shadowScaleLoc = GetShaderLocation(shader, "shadowScale");
        this.shadowColorLoc = GetShaderLocation(shader, "shadowColor");
        this.borderThicknessLoc = GetShaderLocation(shader, "borderThickness");
        this.borderColorLoc = GetShaderLocation(shader, "borderColor");

        // Update shader uniforms
        this.UpdateRoundedRectangle(shader);
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

    const rectangleColor = BLUE;
    const shadowColor = DARKBLUE;
    const borderColor = SKYBLUE;

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - Rounded Rectangle");

    // Load the shader
    let shader = LoadShader(TextFormat("resources/shaders/glsl%i/base.vs", GLSL_VERSION),
                            TextFormat("resources/shaders/glsl%i/rounded_rectangle.fs", GLSL_VERSION));

    // Create a rounded rectangle
    let roundedRectangle = new RoundedRectangle(
        new Vector4( 5, 10, 15, 20 ), // Corner radius
        20,                           // Shadow radius
        new Vector2( 0, -5 ),         // Shadow offset
        0.95,                         // Shadow scale
        5,                            // Border thickness
        shader                        // Shader
    );

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw rectangle box with rounded corners using shader
            let rec = new Rectangle( 50, 70, 110, 60 );
            DrawRectangleLines(rec.x - 20, rec.y - 20, rec.width + 40, rec.height + 40, DARKGRAY);
            DrawText("Rounded rectangle", rec.x - 20, rec.y - 35, 10, DARKGRAY);

            // Flip Y axis to match shader coordinate system
            rec.y = screenHeight - rec.y - rec.height;
            SetShaderValue(shader, roundedRectangle.rectangleLoc, [ rec.x, rec.y, rec.width, rec.height ], SHADER_UNIFORM_VEC4);

            // Only rectangle color
            SetShaderValue(shader, roundedRectangle.colorLoc, [ rectangleColor.r/255, rectangleColor.g/255, rectangleColor.b/255, rectangleColor.a/255 ], SHADER_UNIFORM_VEC4);
            SetShaderValue(shader, roundedRectangle.shadowColorLoc, [ 0, 0, 0, 0 ], SHADER_UNIFORM_VEC4);
            SetShaderValue(shader, roundedRectangle.borderColorLoc, [ 0, 0, 0, 0 ], SHADER_UNIFORM_VEC4);

            BeginShaderMode(shader);
                DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
            EndShaderMode();



            // Draw rectangle shadow using shader
            rec = new Rectangle( 50, 200, 110, 60 );
            DrawRectangleLines(rec.x - 20, rec.y - 20, rec.width + 40, rec.height + 40, DARKGRAY);
            DrawText("Rounded rectangle shadow", rec.x - 20, rec.y - 35, 10, DARKGRAY);

            rec.y = screenHeight - rec.y - rec.height;
            SetShaderValue(shader, roundedRectangle.rectangleLoc, [ rec.x, rec.y, rec.width, rec.height ], SHADER_UNIFORM_VEC4);

            // Only shadow color
            SetShaderValue(shader, roundedRectangle.colorLoc, [ 0, 0, 0, 0 ], SHADER_UNIFORM_VEC4);
            SetShaderValue(shader, roundedRectangle.shadowColorLoc, [ shadowColor.r/255, shadowColor.g/255, shadowColor.b/255, shadowColor.a/255 ], SHADER_UNIFORM_VEC4);
            SetShaderValue(shader, roundedRectangle.borderColorLoc, [ 0, 0, 0, 0 ], SHADER_UNIFORM_VEC4);

            BeginShaderMode(shader);
                DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
            EndShaderMode();



            // Draw rectangle's border using shader
            rec = new Rectangle( 50, 330, 110, 60 );
            DrawRectangleLines(rec.x - 20, rec.y - 20, rec.width + 40, rec.height + 40, DARKGRAY);
            DrawText("Rounded rectangle border", rec.x - 20, rec.y - 35, 10, DARKGRAY);

            rec.y = screenHeight - rec.y - rec.height;
            SetShaderValue(shader, roundedRectangle.rectangleLoc, [ rec.x, rec.y, rec.width, rec.height ], SHADER_UNIFORM_VEC4);

            // Only border color
            SetShaderValue(shader, roundedRectangle.colorLoc, [ 0, 0, 0, 0 ], SHADER_UNIFORM_VEC4);
            SetShaderValue(shader, roundedRectangle.shadowColorLoc, [ 0, 0, 0, 0 ], SHADER_UNIFORM_VEC4);
            SetShaderValue(shader, roundedRectangle.borderColorLoc, [ borderColor.r/255, borderColor.g/255, borderColor.b/255, borderColor.a/255 ], SHADER_UNIFORM_VEC4);

            BeginShaderMode(shader);
                DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
            EndShaderMode();



            // Draw one more rectangle with all three colors
            rec = new Rectangle( 240, 80, 500, 300 );
            DrawRectangleLines(rec.x - 30, rec.y - 30, rec.width + 60, rec.height + 60, DARKGRAY);
            DrawText("Rectangle with all three combined", rec.x - 30, rec.y - 45, 10, DARKGRAY);

            rec.y = screenHeight - rec.y - rec.height;
            SetShaderValue(shader, roundedRectangle.rectangleLoc, [ rec.x, rec.y, rec.width, rec.height ], SHADER_UNIFORM_VEC4);

            // All three colors
            SetShaderValue(shader, roundedRectangle.colorLoc, [ rectangleColor.r/255, rectangleColor.g/255, rectangleColor.b/255, rectangleColor.a/255 ], SHADER_UNIFORM_VEC4);
            SetShaderValue(shader, roundedRectangle.shadowColorLoc, [ shadowColor.r/255, shadowColor.g/255, shadowColor.b/255, shadowColor.a/255 ], SHADER_UNIFORM_VEC4);
            SetShaderValue(shader, roundedRectangle.borderColorLoc, [ borderColor.r/255, borderColor.g/255, borderColor.b/255, borderColor.a/255 ], SHADER_UNIFORM_VEC4);

            BeginShaderMode(shader);
                DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
            EndShaderMode();

            DrawText("(c) Rounded rectangle SDF by Iñigo Quilez. MIT License.", screenWidth - 300, screenHeight - 20, 10, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader); // Unload shader

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}