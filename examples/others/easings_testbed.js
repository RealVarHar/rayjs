/*******************************************************************************************
*
*   raylib [easings] example - Easings Testbed
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example contributed by Juan Miguel López (@flashback-fx) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2025 Juan Miguel López (@flashback-fx) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import * as rl from 'rayjs:raylib';
import {
    EaseBackIn, EaseBackInOut, EaseBackOut, EaseBounceIn, EaseBounceInOut, EaseBounceOut, EaseCircIn, EaseCircInOut, EaseCircOut, EaseCubicIn, EaseCubicInOut, EaseCubicOut, EaseElasticIn, EaseElasticInOut, EaseElasticOut, EaseExpoIn, EaseExpoInOut, EaseExpoOut, EaseLinearIn, EaseLinearInOut, EaseLinearNone, EaseLinearOut, EaseQuadIn, EaseQuadInOut, EaseQuadOut, EaseSineIn, EaseSineInOut, EaseSineOut
} from 'rayjs:reasings';
import {
    BeginDrawing, ClearBackground, CloseWindow, DrawCircleV, DrawText, EndDrawing, GetScreenHeight,
    InitWindow, IsKeyDown,
    IsKeyPressed, KEY_A, KEY_DOWN, KEY_ENTER,
    KEY_LEFT, KEY_Q,
    KEY_RIGHT, KEY_S, KEY_SPACE,
    KEY_T, KEY_UP, KEY_W, LIGHTGRAY, MAROON, RAYWHITE,
    SetTargetFPS, TextFormat,
    Vector2,
    WindowShouldClose
} from "rayjs:raylib";
for (const key in rl) { globalThis[key] = rl[key] };

const FONT_SIZE = 20;

const D_STEP = 20;
const D_STEP_FINE = 2;
const D_MIN = 1;
const D_MAX = 10000;

// Easing types
const EASE_LINEAR_NONE = 0;
const EASE_LINEAR_IN = 1;
const EASE_LINEAR_OUT = 2;
const EASE_LINEAR_IN_OUT = 3;
const EASE_SINE_IN = 4;
const EASE_SINE_OUT = 5;
const EASE_SINE_IN_OUT = 6;
const EASE_CIRC_IN = 7;
const EASE_CIRC_OUT = 8;
const EASE_CIRC_IN_OUT = 9;
const EASE_CUBIC_IN = 10;
const EASE_CUBIC_OUT = 11;
const EASE_CUBIC_IN_OUT = 12;
const EASE_QUAD_IN = 13;
const EASE_QUAD_OUT = 14;
const EASE_QUAD_IN_OUT = 15;
const EASE_EXPO_IN = 16;
const EASE_EXPO_OUT = 17;
const EASE_EXPO_IN_OUT = 18;
const EASE_BACK_IN = 19;
const EASE_BACK_OUT = 20;
const EASE_BACK_IN_OUT = 21;
const EASE_BOUNCE_OUT = 22;
const EASE_BOUNCE_IN = 23;
const EASE_BOUNCE_IN_OUT = 24;
const EASE_ELASTIC_IN = 25;
const EASE_ELASTIC_OUT = 26;
const EASE_ELASTIC_IN_OUT = 27;
const NUM_EASING_TYPES = 28;
const EASING_NONE = NUM_EASING_TYPES;

// NoEase function, used when "no easing" is selected for any axis. It just ignores all parameters besides b.
function NoEase(t, b, c, d) {
    return b;
}

// Easing functions reference data
const Easings = [//Note: Oryginal indicates an object but since it is non-sparce, an array is used here
    { name: "EaseLinearNone",   func: EaseLinearNone },
    { name: "EaseLinearIn",     func: EaseLinearIn },
    { name: "EaseLinearOut",    func: EaseLinearOut },
    { name: "EaseLinearInOut",  func: EaseLinearInOut },
    { name: "EaseSineIn",       func: EaseSineIn },
    { name: "EaseSineOut",      func: EaseSineOut },
    { name: "EaseSineInOut",    func: EaseSineInOut },
    { name: "EaseCircIn",       func: EaseCircIn },
    { name: "EaseCircOut",      func: EaseCircOut },
    { name: "EaseCircInOut",    func: EaseCircInOut },
    { name: "EaseCubicIn",      func: EaseCubicIn },
    { name: "EaseCubicOut",     func: EaseCubicOut },
    { name: "EaseCubicInOut",   func: EaseCubicInOut },
    { name: "EaseQuadIn",       func: EaseQuadIn },
    { name: "EaseQuadOut",      func: EaseQuadOut },
    { name: "EaseQuadInOut",    func: EaseQuadInOut },
    { name: "EaseExpoIn",       func: EaseExpoIn },
    { name: "EaseExpoOut",      func: EaseExpoOut },
    { name: "EaseExpoInOut",    func: EaseExpoInOut },
    { name: "EaseBackIn",       func: EaseBackIn },
    { name: "EaseBackOut",      func: EaseBackOut },
    { name: "EaseBackInOut",    func: EaseBackInOut },
    { name: "EaseBounceOut",    func: EaseBounceOut },
    { name: "EaseBounceIn",     func: EaseBounceIn },
    { name: "EaseBounceInOut",  func: EaseBounceInOut },
    { name: "EaseElasticIn",    func: EaseElasticIn },
    { name: "EaseElasticOut",   func: EaseElasticOut },
    { name: "EaseElasticInOut", func: EaseElasticInOut },
    { name: "None",             func: NoEase }
];

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [easings] example - easings testbed");

    let ballPosition = new Vector2( 100, 100 );

    let t = 0;             // Current time (in any unit measure, but same unit as duration)
    let d = 300;           // Total time it should take to complete (duration)
    let paused = true;
    let boundedT = true;       // If true, t will stop when d >= td, otherwise t will keep adding td to its value every loop

    let easingX = EASING_NONE;  // Easing selected for x axis
    let easingY = EASING_NONE;  // Easing selected for y axis

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_T)) boundedT = !boundedT;

        // Choose easing for the X axis
        if (IsKeyPressed(KEY_RIGHT)) {
            easingX++;
            if (easingX > EASING_NONE) easingX = 0;
        } else if (IsKeyPressed(KEY_LEFT)) {
            if (easingX == 0) easingX = EASING_NONE;
            else easingX--;
        }

        // Choose easing for the Y axis
        if (IsKeyPressed(KEY_DOWN)) {
            easingY++;

            if (easingY > EASING_NONE) easingY = 0;
        } else if (IsKeyPressed(KEY_UP)) {
            if (easingY == 0) easingY = EASING_NONE;
            else easingY--;
        }

        // Change d (duration) value
        if (IsKeyPressed(KEY_W) && d < D_MAX - D_STEP) d += D_STEP;
        else if (IsKeyPressed(KEY_Q) && d > D_MIN + D_STEP) d -= D_STEP;

        if (IsKeyDown(KEY_S) && d < D_MAX - D_STEP_FINE) d += D_STEP_FINE;
        else if (IsKeyDown(KEY_A) && d > D_MIN + D_STEP_FINE) d -= D_STEP_FINE;

        // Play, pause and restart controls
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_T) ||
            IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT) ||
            IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP) ||
            IsKeyPressed(KEY_W) || IsKeyPressed(KEY_Q) ||
            IsKeyDown(KEY_S)  || IsKeyDown(KEY_A) ||
            (IsKeyPressed(KEY_ENTER) && (boundedT == true) && (t >= d)))
        {
            t = 0;
            ballPosition.x = 100;
            ballPosition.y = 100;
            paused = true;
        }

        if (IsKeyPressed(KEY_ENTER)) paused = !paused;

        // Movement computation
        if (!paused && ((boundedT && t < d) || !boundedT)) {
            ballPosition.x = Easings[easingX].func(t, 100, 700 - 170, d);
            ballPosition.y = Easings[easingY].func(t, 100, 400 - 170, d);
            t += 1;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw information text
            DrawText(TextFormat("Easing x: %s", Easings[easingX].name), 20, FONT_SIZE, FONT_SIZE, LIGHTGRAY);
            DrawText(TextFormat("Easing y: %s", Easings[easingY].name), 20, FONT_SIZE*2, FONT_SIZE, LIGHTGRAY);
            DrawText(TextFormat("t (%c) = %.2f d = %.2f", (boundedT == true)? 'b' : 'u', t, d), 20, FONT_SIZE*3, FONT_SIZE, LIGHTGRAY);

            // Draw instructions text
            DrawText("Use ENTER to play or pause movement, use SPACE to restart", 20, GetScreenHeight() - FONT_SIZE*2, FONT_SIZE, LIGHTGRAY);
            DrawText("Use Q and W or A and S keys to change duration", 20, GetScreenHeight() - FONT_SIZE*3, FONT_SIZE, LIGHTGRAY);
            DrawText("Use LEFT or RIGHT keys to choose easing for the x axis", 20, GetScreenHeight() - FONT_SIZE*4, FONT_SIZE, LIGHTGRAY);
            DrawText("Use UP or DOWN keys to choose easing for the y axis", 20, GetScreenHeight() - FONT_SIZE*5, FONT_SIZE, LIGHTGRAY);

            // Draw ball
            DrawCircleV(ballPosition, 16, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
    //--------------------------------------------------------------------------------------
}