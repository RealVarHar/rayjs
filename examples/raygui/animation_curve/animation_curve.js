/*******************************************************************************************
*
*   Animation curves - An example demo for animation curves
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
*   Copyright (c) 2023 Pierre Jaffuer (@smallcluster)
*
**********************************************************************************************/

import * as rl from 'rayjs:raylib';
import * as rg from 'rayjs:raygui';

const RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT = 24;

// raygui embedded styles
import {GuiLoadStyleCyber} from "../styles/style_cyber.js";       // raygui style: cyber
import {GuiLoadStyleJungle} from "../styles/style_jungle.js";      // raygui style: jungle
import {GuiLoadStyleLavanda} from "../styles/style_lavanda.js";     // raygui style: lavanda
import {GuiLoadStyleDark} from "../styles/style_dark.js";        // raygui style: dark
import {GuiLoadStyleBluish} from "../styles/style_bluish.js";      // raygui style: bluish
import {GuiLoadStyleTerminal} from "../styles/style_terminal.js";    // raygui style: terminal

import {GuiCurveEval, GuiCurveEditor} from ".//gui_curve_editor.js";

//------------------------------------------------------------------------------------
// Helper function
//------------------------------------------------------------------------------------
function LoadCurveDefaults(curves) {
    // X pos
    curves[0].start = 28;
    curves[0].end = 506;
    curves[0].numPoints = 4;
    curves[0].selectedIndex = 0;
    curves[0].editLeftTangent = false;
    curves[0].editRightTangent = false;
    curves[0].points = new Array(4);
    curves[0].points[0] = {position: new rl.Vector2(0.000000, 0.000000), tangents: new rl.Vector2(0.000000,  1.515101), leftLinear: 1, rightLinear: 1};
    curves[0].points[1] = {position: new rl.Vector2(0.422414, 0.640000), tangents: new rl.Vector2(-2.824348,-4.494999), leftLinear: 0, rightLinear: 0};
    curves[0].points[2] = {position: new rl.Vector2(0.732759, 0.210000), tangents: new rl.Vector2(0.000000,  2.956133), leftLinear: 0, rightLinear: 1};
    curves[0].points[3] = {position: new rl.Vector2(1.000000, 1.000000), tangents: new rl.Vector2(2.956133,  0.000000), leftLinear: 1, rightLinear: 1};

    // Y pos
    curves[1].start = 405;
    curves[1].end = 135;
    curves[1].numPoints = 7;
    curves[1].selectedIndex = 0;
    curves[1].editLeftTangent = false;
    curves[1].editRightTangent = false;
    curves[1].points = new Array(7);
    curves[1].points[0] = {position: new rl.Vector2(0.000000, 1.000000), tangents: new rl.Vector2( 0.000000  , 0.000000), leftLinear: 0, rightLinear: 0};
    curves[1].points[1] = {position: new rl.Vector2(0.140000, 0.000000), tangents: new rl.Vector2(-10.000000 ,10.000000), leftLinear: 0, rightLinear: 0};
    curves[1].points[2] = {position: new rl.Vector2(0.450000, 0.000000), tangents: new rl.Vector2(-10.000000 ,10.000000), leftLinear: 0, rightLinear: 0};
    curves[1].points[3] = {position: new rl.Vector2(0.670000, 0.000000), tangents: new rl.Vector2(-10.000000 ,10.000000), leftLinear: 0, rightLinear: 0};
    curves[1].points[4] = {position: new rl.Vector2(0.830000, 0.000000), tangents: new rl.Vector2(-10.000000 ,10.000000), leftLinear: 0, rightLinear: 0};
    curves[1].points[5] = {position: new rl.Vector2(0.940000, 0.000000), tangents: new rl.Vector2(-10.000000 ,10.000000), leftLinear: 0, rightLinear: 0};
    curves[1].points[6] = {position: new rl.Vector2(1.000000, 0.000000), tangents: new rl.Vector2(-10.000000 , 0.000000), leftLinear: 0, rightLinear: 0};

    // X size
    curves[2].start = 1;
    curves[2].end = 64;
    curves[2].numPoints = 16;
    curves[2].selectedIndex = 0;
    curves[2].editLeftTangent = false;
    curves[2].editRightTangent = false;
    curves[2].points = new Array(16);
    curves[2].points[0]  = {position: new rl.Vector2(0.000000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[1]  = {position: new rl.Vector2(0.130000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[2]  = {position: new rl.Vector2(0.140000, 0.746032), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[3]  = {position: new rl.Vector2(0.150000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[4]  = {position: new rl.Vector2(0.440000, 0.490000), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[5]  = {position: new rl.Vector2(0.450000, 0.682540), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[6]  = {position: new rl.Vector2(0.460000, 0.480000), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[7]  = {position: new rl.Vector2(0.660000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[8]  = {position: new rl.Vector2(0.670000, 0.619048), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[9]  = {position: new rl.Vector2(0.680000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[10] = {position: new rl.Vector2(0.820000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[11] = {position: new rl.Vector2(0.830000, 0.619048), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[12] = {position: new rl.Vector2(0.840000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[13] = {position: new rl.Vector2(0.930000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[14] = {position: new rl.Vector2(0.940000, 0.619048), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[2].points[15] = {position: new rl.Vector2(0.950000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};

    // Y Size
    curves[3].start = 1;
    curves[3].end = 64;
    curves[3].numPoints = 16;
    curves[3].selectedIndex = 0;
    curves[3].editLeftTangent = false;
    curves[3].editRightTangent = false;
    curves[3].points = new Array(16);
    curves[3].points[0]  = {position: new rl.Vector2(0.000000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[1]  = {position: new rl.Vector2(0.130000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[2]  = {position: new rl.Vector2(0.140000, 0.238095), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[3]  = {position: new rl.Vector2(0.150000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[4]  = {position: new rl.Vector2(0.440000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[5]  = {position: new rl.Vector2(0.450000, 0.301587), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[6]  = {position: new rl.Vector2(0.460000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[7]  = {position: new rl.Vector2(0.660000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[8]  = {position: new rl.Vector2(0.670000, 0.365079), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[9]  = {position: new rl.Vector2(0.680000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[10] = {position: new rl.Vector2(0.820000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[11] = {position: new rl.Vector2(0.830000, 0.365079), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[12] = {position: new rl.Vector2(0.840000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[13] = {position: new rl.Vector2(0.930000, 0.492063), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[14] = {position: new rl.Vector2(0.940000, 0.365079), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[3].points[15] = {position: new rl.Vector2(0.950000, 0.507937), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};

    // Rotation
    curves[4].start = -360;
    curves[4].end = 360;
    curves[4].numPoints = 9;
    curves[4].selectedIndex = 0;
    curves[4].editLeftTangent = false;
    curves[4].editRightTangent = false;
    curves[4].points = new Array(9);
    curves[4].points[0] = {position: new rl.Vector2(0.140000, 0.500000), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[4].points[1] = {position: new rl.Vector2(0.450000, 0.500000), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[4].points[2] = {position: new rl.Vector2(0.670000, 0.500000), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[4].points[3] = {position: new rl.Vector2(0.830000, 0.500000), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[4].points[4] = {position: new rl.Vector2(0.940000, 0.500000), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[4].points[5] = {position: new rl.Vector2(1.000000, 0.500000), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[4].points[6] = {position: new rl.Vector2(0.000000, 0.472222), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[4].points[7] = {position: new rl.Vector2(0.302752, 0.527778), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
    curves[4].points[8] = {position: new rl.Vector2(0.577982, 0.472222), tangents: new rl.Vector2(0,0), leftLinear: 0, rightLinear: 0};
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //---------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 540;
    const DEG2RAD = Math.PI/180;

    rl.InitWindow(screenWidth, screenHeight, "raygui - animation curves");
    rl.SetTargetFPS(60);

    // Gui style
    rg.GuiLoadStyleDefault();
    let visualStyleActive = 0;
    let prevVisualStyleActive = 0;

    let fontSize = rg.GuiGetStyle(rg.DEFAULT, rg.TEXT_SIZE);
    const margin = 8;

    // Gui states
    let scrollOffset = new rl.Vector2( 0, 0 );
    let contentRect = new rl.Rectangle( 0, 0, 0, 0 );
    let moveSlider = false;
    let sectionActive = new Array(5);
    sectionActive[0] = true;
    const sectionNames = [ "X Position", "Y Position", "Width", "Height", "Rotation" ];
    let editValueBox = new Array(5);
    for(let i=0;i<5;i++){
        editValueBox[i] = new Uint8Array(4);
    }
    let valTextBox = new Array(5);
    for(let i=0;i<5;i++){
        valTextBox[0] = new Array(4).fill(" ".repeat(20));
    }
    let playAnimation = true;
    let showHelp = true;

    let settingsRect = new rl.Rectangle( screenWidth - screenWidth/3, 0, screenWidth/3, screenHeight );

    // Animation curves
    // 0 -> Ball X position
    // 1 -> Ball Y position
    // 2 -> Ball Width
    // 3 -> Ball Height
    // 4 -> Ball rotation
    let curves = new Array(5);
    LoadCurveDefaults(curves);

    // Animation time
    let time = 0;
    let animationTime = 4;

    //SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!rl.WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (playAnimation) time += rl.GetFrameTime();

        // Reset timer
        if (time > animationTime) time = 0;

        // Ball animation
        const t = time/animationTime;
        let ballPos = new rl.Vector2( GuiCurveEval(curves[0], t), GuiCurveEval(curves[1], t) );
        let ballSize= new rl.Vector2( GuiCurveEval(curves[2], t), GuiCurveEval(curves[3], t) );
        let ballRotation = GuiCurveEval(curves[4], t);

        // Update style
        if (visualStyleActive != prevVisualStyleActive) {
            switch (visualStyleActive) {
                case 0: rg.GuiLoadStyleDefault(); break;
                case 1: GuiLoadStyleJungle(); break;
                case 2: GuiLoadStyleLavanda(); break;
                case 3: GuiLoadStyleDark(); break;
                case 4: GuiLoadStyleBluish(); break;
                case 5: GuiLoadStyleCyber(); break;
                case 6: GuiLoadStyleTerminal(); break;
                default: break;
            }

            fontSize = rg.GuiGetStyle(rg.DEFAULT, rg.TEXT_SIZE);
            prevVisualStyleActive = visualStyleActive;
        }

        // Update settings panel rect
        let sliderRect = new rl.Rectangle( settingsRect.x - 4, settingsRect.y, 4, settingsRect.height );
        if (rl.CheckCollisionPointRec(rl.GetMousePosition(), sliderRect) && rl.IsMouseButtonPressed(rl.MOUSE_BUTTON_LEFT)) moveSlider = true;
        if (rl.IsMouseButtonUp(rl.MOUSE_BUTTON_LEFT)) moveSlider = false;

        if (moveSlider) {
            settingsRect.x = rl.GetMouseX();

            // Minimum-Maximum size
            if (settingsRect.x > (screenWidth - 4)) settingsRect.x = screenWidth - 4;
            else if (settingsRect.x < 4) settingsRect.x = 4;

            settingsRect.width = screenWidth - settingsRect.x;
        }


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        rl.BeginDrawing();
            rl.ClearBackground(rl.GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.BACKGROUND_COLOR)));

            // Scene
            //----------------------------------------------------------------------------------
            rl.DrawRectangle(curves[0].start, curves[1].end, curves[0].end-curves[0].start, curves[1].start-curves[1].end, rl.BLUE);  // Sky

            rl.DrawRectangle(curves[0].start, curves[1].start, curves[0].end-curves[0].start, 32, rl.DARKGREEN);  // Ground

            rl.BeginScissorMode(curves[0].start, curves[1].end, curves[0].end-curves[0].start, curves[1].start-curves[1].end+32);

                rl.DrawRectanglePro(new rl.Rectangle(ballPos.x, ballPos.y, ballSize.x, ballSize.y), new rl.Vector2(ballSize.x/2,ballSize.y/2), ballRotation, rl.PINK);  // Ball

                rl.DrawLine(ballPos.x, ballPos.y, ballPos.x + Math.cos(ballRotation*DEG2RAD)*ballSize.x, ballPos.y +Math.sin(ballRotation*DEG2RAD)*ballSize.y, rl.RED);
                rl.DrawLine(ballPos.x, ballPos.y, ballPos.x + Math.cos((ballRotation+90)*DEG2RAD)*ballSize.x, ballPos.y +Math.sin((ballRotation+90)*DEG2RAD)*ballSize.y, rl.GREEN);

            rl.EndScissorMode();

            // Bounds
            rl.DrawRectangleLines(curves[0].start, curves[1].end, curves[0].end-curves[0].start, curves[1].start-curves[1].end+32, rl.GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.BORDER_COLOR_NORMAL)));
            //----------------------------------------------------------------------------------

            // GUI
            //----------------------------------------------------------------------------------
            if (showHelp) {
                if (rg.GuiWindowBox(new rl.Rectangle(margin, margin, settingsRect.x-2*margin, curves[1].end-2*margin), "help")) showHelp = false;

                let helpTextRect = new rl.Rectangle( 2*margin, 2*margin+RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT, settingsRect.x - 4 - 4*margin, 0 );
                rg.GuiLabel( new rl.Rectangle(helpTextRect.x, helpTextRect.y+helpTextRect.height, helpTextRect.width, fontSize), "Curve widget controls:");
                helpTextRect.height += fontSize+margin;
                rg.GuiLabel( new rl.Rectangle(helpTextRect.x, helpTextRect.y+helpTextRect.height, helpTextRect.width, fontSize), "- Left click to move/add point or move tangents");
                helpTextRect.height += fontSize+margin/2;
                rg.GuiLabel( new rl.Rectangle(helpTextRect.x, helpTextRect.y+helpTextRect.height, helpTextRect.width, fontSize), "- While moving a tangent, hold SHIFT to disable tangent symetry");
                helpTextRect.height += fontSize+margin/2;
                rg.GuiLabel( new rl.Rectangle(helpTextRect.x, helpTextRect.y+helpTextRect.height, helpTextRect.width, fontSize), "- Right click to remove a point");
                helpTextRect.height += fontSize+margin/2;
                rl.DrawRectangleGradientV(margin, margin+curves[1].end - 2*margin, settingsRect.x - 2*margin, 12, new rl.Color( 0,0,0,100 ), rl.BLANK);
            }

            // Settings panel
            rg.GuiScrollPanel(settingsRect, "Settings", contentRect, scrollOffset, null);

            rl.BeginScissorMode(settingsRect.x, settingsRect.y+RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT, settingsRect.width, settingsRect.height);

            // Rebuild the content Rect
            contentRect = new rl.Rectangle( settingsRect.x + margin, RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT+margin, settingsRect.width - 2*margin - rg.GuiGetStyle(rg.LISTVIEW, rg.SCROLLBAR_WIDTH), 0 );

            // Help button
            if (rg.GuiButton( new rl.Rectangle( contentRect.x, contentRect.y + contentRect.height + scrollOffset.y, contentRect.width, 1.5*fontSize ), rg.GuiIconText(showHelp? rg.ICON_EYE_ON : rg.ICON_EYE_OFF, "Curve controls help"))) showHelp = !showHelp;

            contentRect.height += 1.5*fontSize + margin;

            // Animation Time slider
            rg.GuiSlider(new rl.Rectangle( contentRect.x, contentRect.y+contentRect.height+scrollOffset.y, contentRect.width/2, fontSize ), null, rl.TextFormat("Animation Time: %.2fs", animationTime), animationTime, 1, 8);
            contentRect.height += fontSize + margin;

            // Load default curves
            if (rg.GuiButton( new rl.Rectangle( contentRect.x, contentRect.y+contentRect.height+scrollOffset.y, contentRect.width, 1.5*fontSize ), "Load default")) {
                LoadCurveDefaults(curves);
                animationTime = 4;
                time = 0;
            }
            contentRect.height += 1.5*fontSize + margin;

            // Styles
            rg.GuiLabel(new rl.Rectangle( contentRect.x, contentRect.y + contentRect.height + scrollOffset.y, contentRect.width, fontSize ), "Style:");
            contentRect.height += fontSize;
            rg.GuiComboBox(new rl.Rectangle(contentRect.x, contentRect.y+contentRect.height+scrollOffset.y, contentRect.width, 1.5*fontSize ), "default;Jungle;Lavanda;Dark;Bluish;Cyber;Terminal", visualStyleActive);
            contentRect.height += 1.5*fontSize + margin;

            // Draw curves with their controls
            //----------------------------------------------------------------------------------
            for (let i = 0; i < 5; i++) {
                // Collapsing section
                let headerRect = new rl.Rectangle( contentRect.x, contentRect.y + contentRect.height+scrollOffset.y, contentRect.width, 1.5*fontSize );
                rg.GuiStatusBar(headerRect, null);

                if (rg.GuiLabelButton(headerRect, rg.GuiIconText(sectionActive[i] ? rg.ICON_ARROW_DOWN_FILL : rg.ICON_ARROW_RIGHT_FILL, sectionNames[i]))) sectionActive[i] = !sectionActive[i];

                contentRect.height += 1.5*fontSize + margin;

                // Skip this section
                if (!sectionActive[i]) continue;

                // Draw curve control
                let curveRect = new rl.Rectangle( contentRect.x, contentRect.y+contentRect.height + scrollOffset.y, contentRect.width, fontSize*12 );
                rl.EndScissorMode(); // Stop clipping from setting rect

                // Curves can leaks from control boundary... scissor it !
                rl.BeginScissorMode(curveRect.x, curveRect.y, curveRect.width, curveRect.height);
                    GuiCurveEditor(curves[i], curveRect);
                rl.EndScissorMode();

                // Resume clipping from setting rect
                rl.BeginScissorMode(settingsRect.x, settingsRect.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT, settingsRect.width, settingsRect.height);
                contentRect.height += fontSize*12 + margin;

                // Draw selected point controls
                let p = curves[i].points[curves[i].selectedIndex];
                rg.GuiCheckBox(new rl.Rectangle( contentRect.x, contentRect.y + contentRect.height + scrollOffset.y, 1.5*fontSize, 1.5*fontSize ), "Left Linear", p.leftLinear);
                rg.GuiCheckBox(new rl.Rectangle( contentRect.x+contentRect.width/2, contentRect.y + contentRect.height + scrollOffset.y, 1.5*fontSize, 1.5*fontSize ), "Right Linear", p.rightLinear);
                contentRect.height += 1.5*fontSize + margin;

                // Positions
                rg.GuiLabel(new rl.Rectangle( contentRect.x, contentRect.y + contentRect.height + scrollOffset.y, contentRect.width, fontSize ), "Position");
                contentRect.height += fontSize;

                if (!editValueBox[i][0]) valTextBox[i][0] = String(p.position.x);  // Transform x position to string

                if (!editValueBox[i][1]) valTextBox[i][1] = String(curves[i].start + (curves[i].end-curves[i].start)*p.position.y); // Transform y position to string

                // X pos
                if (rg.GuiTextBox(new rl.Rectangle( contentRect.x, contentRect.y + contentRect.height + scrollOffset.y, contentRect.width/2-margin, 1.5*fontSize ), valTextBox[i][0], 20, editValueBox[i][0])) {
                    editValueBox[i][0] = !editValueBox[i][0];

                    // Input ended
                    if (!editValueBox[i][0]) {
                        // Try to convert text to float and assign it to the point
                        let value = parseFloat(valTextBox[i][0]);
                        if (!isNaN(value) ) p.position.x = (value < 0)? 0 : (value > 1)? 1 : value;
                    }
                }

                // Y pos
                if (rg.GuiTextBox(new rl.Rectangle( contentRect.x + contentRect.width/2, contentRect.y + contentRect.height + scrollOffset.y, contentRect.width/2, 1.5*fontSize ), valTextBox[i][1], 20, editValueBox[i][1])) {
                    editValueBox[i][1] = !editValueBox[i][1];

                    // Input ended
                    if (!editValueBox[i][1]) {
                        // Try to convert text to float and assign it to the point
                        let value = parseFloat(valTextBox[i][0]);
                        if ( !isNaN(value) ){
                            let normalizedVal = (value - curves[i].start)/(curves[i].end - curves[i].start);
                            p.position.y = (normalizedVal < 0)? 0 : (normalizedVal > 1)? 1 : normalizedVal;
                        }
                    }

                }

                contentRect.height += 1.5*fontSize + margin;

                // Tangents
                rg.GuiLabel(new rl.Rectangle( contentRect.x, contentRect.y + contentRect.height + scrollOffset.y, contentRect.width, fontSize ), "Tangents");
                contentRect.height += fontSize;

                if (!editValueBox[i][2]) valTextBox[i][2] = rl.TextFormat("%.6g", p.tangents.x); // Transform left tangent to string

                if (!editValueBox[i][3]) valTextBox[i][2] = rl.TextFormat("%.6g", p.tangents.y); // Transform right tangent to string

                // Left tan
                if (rg.GuiTextBox(new rl.Rectangle( contentRect.x, contentRect.y + contentRect.height + scrollOffset.y, contentRect.width/2 - margin, 1.5*fontSize ), valTextBox[i][2], 20, editValueBox[i][2])) {
                    editValueBox[i][2] = !editValueBox[i][2];

                    // Input ended
                    if (!editValueBox[i][2]) {
                        // Try to convert text to float and assign it to the point
                        let value = parseFloat(valTextBox[i][2]);
                        if ( !isNaN(value) ) p.tangents.x = value;
                    }
                }

                // Right tan
                if (rg.GuiTextBox(new rl.Rectangle( contentRect.x + contentRect.width/2, contentRect.y + contentRect.height + scrollOffset.y, contentRect.width/2, 1.5*fontSize ), valTextBox[i][3], 20, editValueBox[i][3])) {
                    editValueBox[i][3] = !editValueBox[i][3];

                    // Input ended
                    if (!editValueBox[i][3]) {
                        // Try to convert text to float and assign it to the point
                        let value = parseFloat(valTextBox[i][3]);
                        if ( !isNaN(value) ) p.tangents.y = value;
                    }
                }

                contentRect.height += 1.5*fontSize + margin;
            }

            contentRect.height += margin;

            rl.EndScissorMode();

            // Settings panel shadow
            rl.DrawRectangleGradientH(settingsRect.x - 12, 0, 12, settingsRect.height, rl.BLANK, new rl.Color( 0, 0, 0, 100 ));

            // Slider
            if (moveSlider) rl.DrawRectangle(sliderRect.x, sliderRect.y, sliderRect.width, sliderRect.height, rl.GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.BASE_COLOR_PRESSED)));
            else if(rl.CheckCollisionPointRec(rl.GetMousePosition(), sliderRect)) rl.DrawRectangle(sliderRect.x, sliderRect.y, sliderRect.width, sliderRect.height, rl.GetColor(rg.GuiGetStyle(rg.DEFAULT, rg.BASE_COLOR_FOCUSED)));

            // Draw Time controls
            //----------------------------------------------------------------------------------
            let timeLineRect = new rl.Rectangle( 0, screenHeight-4*fontSize, settingsRect.x, 4*fontSize );
            rg.GuiPanel(new rl.Rectangle( timeLineRect.x, timeLineRect.y, timeLineRect.width, 2*fontSize ), null);
            rg.GuiLabel(new rl.Rectangle( timeLineRect.x, timeLineRect.y, timeLineRect.width, 2*fontSize ), rl.TextFormat("Normalized Time: %.3f", time/animationTime));
            if (rg.GuiButton(new rl.Rectangle( timeLineRect.x+timeLineRect.width/2 - 2*fontSize - margin/4, timeLineRect.y, 2*fontSize, 2*fontSize ), rg.GuiIconText((playAnimation? rg.ICON_PLAYER_PAUSE : rg.ICON_PLAYER_PLAY), ""))) playAnimation = !playAnimation;

            if (rg.GuiButton(new rl.Rectangle( timeLineRect.x+timeLineRect.width/2 + margin/4, timeLineRect.y, 2*fontSize, 2*fontSize ), rg.GuiIconText(rg.ICON_PLAYER_STOP, ""))) {
                playAnimation = false;
                time = 0;
            }

            let animTime = time/animationTime;
            rg.GuiSlider(new rl.Rectangle(timeLineRect.x, timeLineRect.y + 2*fontSize, timeLineRect.width, timeLineRect.height - 2*fontSize ), null, null, animTime, 0, 1);
            time = animationTime*animTime;

            // Time panel shadow
            rl.DrawRectangleGradientV(timeLineRect.x, timeLineRect.y - 12, timeLineRect.width, 12, rl.BLANK, new rl.Color( 0, 0, 0, 100 ));

        rl.EndDrawing();
        //----------------------------------------------------------------------------------
    }

    rl.CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}