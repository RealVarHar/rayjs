/*******************************************************************************************
*
*   raylib [core] example - input gestures testbed
*
*   Example complexity rating: [★★★☆] 3/4
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.6-dev
*
*   Example contributed by ubkp (@ubkp) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2025 ubkp (@ubkp)
*
********************************************************************************************/

import {
    BeginDrawing,
    BLACK,
    BLUE,
    CheckCollisionPointRec,
    ClearBackground, CloseWindow,
    Color, DrawCircle, DrawCircleV, DrawLineEx,
    DrawRectangle, DrawRectangleRec, DrawRing,
    DrawText, DrawTriangle, EndDrawing, Fade, GESTURE_DOUBLETAP, GESTURE_DRAG,
    GESTURE_NONE, GESTURE_PINCH_IN, GESTURE_PINCH_OUT,
    GESTURE_SWIPE_DOWN,
    GESTURE_SWIPE_LEFT,
    GESTURE_SWIPE_RIGHT,
    GESTURE_SWIPE_UP, GESTURE_TAP,
    GetGestureDetected,
    GetGestureDragAngle,
    GetGesturePinchAngle,
    GetMousePosition,
    GetTouchPointCount,
    GetTouchPosition, GRAY, GREEN, InitWindow,
    IsMouseButtonReleased,
    LIGHTGRAY,
    LIME, MAROON,
    MOUSE_BUTTON_LEFT,
    ORANGE,
    PI,
    RAYWHITE,
    Rectangle,
    RED, SetTargetFPS,
    SKYBLUE, TextFindIndex, TextFormat, TextSubtext,
    Vector2,
    VIOLET, WHITE, WindowShouldClose
} from "rayjs:raylib";

const GESTURE_LOG_SIZE=20;
const MAX_TOUCH_COUNT=32;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
const GestureNames = {
    0: "None",
    1: "Tap",
    2: "Double Tap",
    4: "Hold",
    8: "Drag",
    16: "Swipe Right",
    32: "Swipe Left",
    64: "Swipe Up",
    128: "Swipe Down",
    256: "Pinch In",
    512: "Pinch Out"
}
function GetGestureName(i){
    return GestureNames[i] || "Unknown";
}

const GestureColors = {
    0: BLACK,
    1: BLUE,
    2: SKYBLUE,
    4: BLACK,
    8: LIME,
    16: RED,
    32: RED,
    64: RED,
    128: RED,
    256: VIOLET,
    512: ORANGE
}

function GetGestureColor(i){
    return GestureColors[i] || BLACK;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    const screenWidth = 800;
    const screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input gestures testbed");

    let messagePosition = new Vector2(160,7);

    // Last gesture variables definitions
    let lastGesture = 0;
    let lastGesturePosition = new Vector2( 165, 130 );

    // Gesture log variables definitions and functions declarations
    // NOTE: The gesture log uses an array (as an inverted circular queue) to store the performed gestures
    let gestureLog = new Array(GESTURE_LOG_SIZE).fill("");
    // NOTE: The index for the inverted circular queue (moving from last to first direction, then looping around)
    let gestureLogIndex = GESTURE_LOG_SIZE;
    let previousGesture = 0;

    // Log mode values:
    // - 0 shows repeated events
    // - 1 hides repeated events
    // - 2 shows repeated events but hide hold events
    // - 3 hides repeated events and hide hold events
    let logMode = 1; // Log mode values: 0 shows repeated events; 1 hides repeated events; 2 shows repeated events but hide hold events; 3 hides repeated events and hide hold events
    let gestureColor = new Color( 0, 0, 0, 255 );
    let logButton1 = new Rectangle( 53, 7, 48, 26 );
    let logButton2 = new Rectangle( 108, 7, 36, 26 );
    let gestureLogPosition = new Vector2( 10, 10 );

    // Protractor variables definitions
    let angleLength = 90;
    let currentAngleDegrees = 0;
    let finalVector = new Vector2( 0, 0 );
    let currentAngleStr = "";
    let protractorPosition = new Vector2( 266, 315 );

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){    // Detect window close button or ESC key
        // Update
        //--------------------------------------------------------------------------------------
        // Handle common gestures data
        let i, ii; // Iterators that will be reused by all for loops
        const currentGesture = GetGestureDetected();
        const currentDragDegrees = GetGestureDragAngle();
        const currentPitchDegrees = GetGesturePinchAngle();
        const touchCount = GetTouchPointCount();

        // Handle last gesture
        if ((currentGesture != 0) && (currentGesture != 4) && (currentGesture != previousGesture)){
            lastGesture = currentGesture; // Filter the meaningful gestures (1, 2, 8 to 512) for the display
        }

        // Handle gesture log
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(GetMousePosition(), logButton1)) {
                switch (logMode) {
                    case 3:  logMode=2; break;
                    case 2:  logMode=3; break;
                    case 1:  logMode=0; break;
                    default: logMode=1; break;
                }
            } else if (CheckCollisionPointRec(GetMousePosition(), logButton2)) {
                switch (logMode) {
                    case 3:  logMode=1; break;
                    case 2:  logMode=0; break;
                    case 1:  logMode=3; break;
                    default: logMode=2; break;
                }
            }
        }

        let fillLog = 0; // Gate variable to be used to allow or not the gesture log to be filled
        if (currentGesture !=0) {
            if (logMode == 3) {// 3 hides repeated events and hide hold events
                if (((currentGesture != 4) && (currentGesture != previousGesture)) || (currentGesture < 3)) fillLog = 1;
            } else if (logMode == 2) { // 2 shows repeated events but hide hold events
                if (currentGesture != 4) fillLog = 1;
            } else if (logMode == 1) { // 1 hides repeated events
                if (currentGesture != previousGesture) fillLog = 1;
            } else { // 0 shows repeated events
                fillLog = 1;
            }
        }

        if (fillLog) {// If one of the conditions from logMode was met, fill the gesture log
            previousGesture = currentGesture;
            gestureColor = GetGestureColor(currentGesture);
            if (gestureLogIndex <= 0) gestureLogIndex = GESTURE_LOG_SIZE;
            gestureLogIndex--;

            // Copy the gesture respective name to the gesture log array
            gestureLog[gestureLogIndex] = GetGestureName(currentGesture);
        }

        // Handle protractor
        if (currentGesture > 255) {// Pinch In and Pinch Out
            currentAngleDegrees = currentPitchDegrees;
        } else if (currentGesture > 15) {// Swipe Right, Swipe Left, Swipe Up and Swipe Down
            currentAngleDegrees = currentDragDegrees;
        } else if (currentGesture > 0) {// Tap, Doubletap, Hold and Grab
            currentAngleDegrees = 0.0;
        }

        let currentAngleRadians = ((currentAngleDegrees +90)*PI/180); // Convert the current angle to Radians
        // Calculate the final vector for display
        finalVector = new Vector2( (angleLength*Math.sin(currentAngleRadians)) + protractorPosition.x, (angleLength*Math.sin(currentAngleRadians)) + protractorPosition.y );

        // Handle touch and mouse pointer points
        let touchPosition = new Array(MAX_TOUCH_COUNT).fill(0).map(a=>{return new Vector2()});
        let mousePosition = new Vector2();
        if (currentGesture != GESTURE_NONE) {
            if (touchCount != 0) {
                for (i = 0; i < touchCount; i++) touchPosition[i] = GetTouchPosition(i); // Fill the touch positions
            }
            else mousePosition = GetMousePosition();
        }
        //--------------------------------------------------------------------------------------

        // Draw
        //--------------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw common
            //--------------------------------------------------------------------------------------
            DrawText("*", messagePosition.x + 5, messagePosition.y + 5, 10, BLACK);
            DrawText("Example optimized for Web/HTML5\non Smartphones with Touch Screen.", messagePosition.x + 15, messagePosition.y + 5, 10, BLACK);
            DrawText("*", messagePosition.x + 5, messagePosition.y + 35, 10, BLACK);
            DrawText("While running on Desktop Web Browsers,\ninspect and turn on Touch Emulation.", messagePosition.x + 15,  messagePosition.y + 35, 10, BLACK);

            // Draw last gesture
            //--------------------------------------------------------------------------------------
            DrawText("Last gesture", lastGesturePosition.x + 33, lastGesturePosition.y - 47, 20, BLACK);
            DrawText("Swipe         Tap       Pinch  Touch", lastGesturePosition.x + 17, lastGesturePosition.y - 18, 10, BLACK);
            DrawRectangle(lastGesturePosition.x + 20, lastGesturePosition.y, 20, 20, lastGesture == GESTURE_SWIPE_UP ? RED : LIGHTGRAY);
            DrawRectangle(lastGesturePosition.x, lastGesturePosition.y + 20, 20, 20, lastGesture == GESTURE_SWIPE_LEFT ? RED : LIGHTGRAY);
            DrawRectangle(lastGesturePosition.x + 40, lastGesturePosition.y + 20, 20, 20, lastGesture == GESTURE_SWIPE_RIGHT ? RED : LIGHTGRAY);
            DrawRectangle(lastGesturePosition.x + 20, lastGesturePosition.y + 40, 20, 20, lastGesture == GESTURE_SWIPE_DOWN ? RED : LIGHTGRAY);
            DrawCircle(lastGesturePosition.x + 80, lastGesturePosition.y + 16, 10, lastGesture == GESTURE_TAP ? BLUE : LIGHTGRAY);
            DrawRing( new Vector2(lastGesturePosition.x + 103, lastGesturePosition.y + 16), 6, 11, 0, 360, 0, lastGesture == GESTURE_DRAG ? LIME : LIGHTGRAY);
            DrawCircle(lastGesturePosition.x + 80, lastGesturePosition.y + 43, 10, lastGesture == GESTURE_DOUBLETAP ? SKYBLUE : LIGHTGRAY);
            DrawCircle(lastGesturePosition.x + 103, lastGesturePosition.y + 43, 10, lastGesture == GESTURE_DOUBLETAP ? SKYBLUE : LIGHTGRAY);
            DrawTriangle(new Vector2( lastGesturePosition.x + 122, lastGesturePosition.y + 16 ), new Vector2( lastGesturePosition.x + 137, lastGesturePosition.y + 26 ), new Vector2( lastGesturePosition.x + 137, lastGesturePosition.y + 6 ), lastGesture == GESTURE_PINCH_OUT? ORANGE : LIGHTGRAY);
            DrawTriangle(new Vector2( lastGesturePosition.x + 147, lastGesturePosition.y + 6 ), new Vector2( lastGesturePosition.x + 147, lastGesturePosition.y + 26 ), new Vector2( lastGesturePosition.x + 162, lastGesturePosition.y + 16 ), lastGesture == GESTURE_PINCH_OUT? ORANGE : LIGHTGRAY);
            DrawTriangle(new Vector2( lastGesturePosition.x + 125, lastGesturePosition.y + 33 ), new Vector2( lastGesturePosition.x + 125, lastGesturePosition.y + 53 ), new Vector2( lastGesturePosition.x + 140, lastGesturePosition.y + 43 ), lastGesture == GESTURE_PINCH_IN? VIOLET : LIGHTGRAY);
            DrawTriangle(new Vector2( lastGesturePosition.x + 144, lastGesturePosition.y + 43 ), new Vector2( lastGesturePosition.x + 159, lastGesturePosition.y + 53 ), new Vector2( lastGesturePosition.x + 159, lastGesturePosition.y + 33 ), lastGesture == GESTURE_PINCH_IN? VIOLET : LIGHTGRAY);
            for (i = 0; i < 4; i++) DrawCircle(lastGesturePosition.x + 180, lastGesturePosition.y + 7 + i*15, 5, touchCount <= i? LIGHTGRAY : gestureColor);

            // Draw gesture log
            //--------------------------------------------------------------------------------------
            DrawText("Log", gestureLogPosition.x, gestureLogPosition.y, 20, BLACK);

            // Loop in both directions to print the gesture log array in the inverted order (and looping around if the index started somewhere in the middle)
            for (i = 0, ii = gestureLogIndex; i < GESTURE_LOG_SIZE; i++) {
                ii = (ii + 1) % GESTURE_LOG_SIZE;
                DrawText(gestureLog[ii], gestureLogPosition.x, gestureLogPosition.y + 410 - i*20, 20, (i == 0 ? gestureColor : LIGHTGRAY));
            }
            let logButton1Color, logButton2Color;
            switch (logMode) {
                case 3:  logButton1Color=MAROON; logButton2Color=MAROON; break;
                case 2:  logButton1Color=GRAY;   logButton2Color=MAROON; break;
                case 1:  logButton1Color=MAROON; logButton2Color=GRAY;   break;
                default: logButton1Color=GRAY;   logButton2Color=GRAY;   break;
            }
            DrawRectangleRec(logButton1, logButton1Color);
            DrawText("Hide", logButton1.x + 7, logButton1.y + 3, 10, WHITE);
            DrawText("Repeat", logButton1.x + 7, logButton1.y + 13, 10, WHITE);
            DrawRectangleRec(logButton2, logButton2Color);
            DrawText("Hide", logButton1.x + 62, logButton1.y + 3, 10, WHITE);
            DrawText("Hold", logButton1.x + 62, logButton1.y + 13, 10, WHITE);

            // Draw protractor
            //--------------------------------------------------------------------------------------
            DrawText("Angle", protractorPosition.x + 55, protractorPosition.y + 76, 10, BLACK);
            const angleString = TextFormat("%f", currentAngleDegrees);
            const angleStringDot = TextFindIndex(angleString, ".");
            const angleStringTrim = TextSubtext(angleString, 0, angleStringDot + 3);
            DrawText( angleStringTrim, protractorPosition.x + 55, protractorPosition.y + 92, 20, gestureColor);
            DrawCircle(protractorPosition.x, protractorPosition.y, 80, WHITE);
            DrawLineEx(new Vector2( protractorPosition.x - 90, protractorPosition.y ), new Vector2( protractorPosition.x + 90, protractorPosition.y ), 3, LIGHTGRAY);
            DrawLineEx(new Vector2( protractorPosition.x, protractorPosition.y - 90 ), new Vector2( protractorPosition.x, protractorPosition.y + 90 ), 3, LIGHTGRAY);
            DrawLineEx(new Vector2( protractorPosition.x - 80, protractorPosition.y - 45 ), new Vector2( protractorPosition.x + 80, protractorPosition.y + 45 ), 3, GREEN);
            DrawLineEx(new Vector2( protractorPosition.x - 80, protractorPosition.y + 45 ), new Vector2( protractorPosition.x + 80, protractorPosition.y - 45 ), 3, GREEN);
            DrawText("0", protractorPosition.x + 96, protractorPosition.y - 9, 20, BLACK);
            DrawText("30", protractorPosition.x + 74, protractorPosition.y - 68, 20, BLACK);
            DrawText("90", protractorPosition.x - 11, protractorPosition.y - 110, 20, BLACK);
            DrawText("150", protractorPosition.x - 100, protractorPosition.y - 68, 20, BLACK);
            DrawText("180", protractorPosition.x - 124, protractorPosition.y - 9, 20, BLACK);
            DrawText("210", protractorPosition.x - 100, protractorPosition.y + 50, 20, BLACK);
            DrawText("270", protractorPosition.x - 18, protractorPosition.y + 92, 20, BLACK);
            DrawText("330", protractorPosition.x + 72, protractorPosition.y + 50, 20, BLACK);
            if (currentAngleDegrees != 0) DrawLineEx(protractorPosition, finalVector, 3, gestureColor);

            // Draw touch and mouse pointer points
            //--------------------------------------------------------------------------------------
            if (currentGesture != GESTURE_NONE) {
                if ( touchCount != 0 ) {
                    for (i = 0; i < touchCount; i++) {
                        DrawCircleV(touchPosition[i], 50, Fade(gestureColor, 0.5));
                        DrawCircleV(touchPosition[i], 5, gestureColor);
                    }

                    if (touchCount == 2) DrawLineEx(touchPosition[0], touchPosition[1], ((currentGesture == 512)? 8 : 12), gestureColor);
                } else {
                    DrawCircleV(mousePosition, 35, Fade(gestureColor, 0.5));
                    DrawCircleV(mousePosition, 5, gestureColor);
                }
            }

        EndDrawing();
        //--------------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}

const messagePosition = new Vector2( 160, 7 );