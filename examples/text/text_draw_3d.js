/*******************************************************************************************
*
*   raylib [text] example - Draw 3d
*
*   Example complexity rating: [★★★★] 4/4
*
*   NOTE: Draw a 2D text in 3D space, each letter is drawn in a quad (or 2 quads if backface is set)
*   where the texture coodinates of each quad map to the texture coordinates of the glyphs
*   inside the font texture.
*
*   A more efficient approach, i believe, would be to render the text in a render texture and
*   map that texture to a plane and render that, or maybe a shader but my method allows more
*   flexibility...for example to change position of each letter individually to make somethink
*   like a wavy text effect.
*    
*   Special thanks to:
*        @Nighten for the DrawTextStyle() code https://github.com/NightenDushi/Raylib_DrawTextStyle
*        Chris Camacho (codifies - http://bedroomcoders.co.uk/) for the alpha discard shader
*
*   Example originally created with raylib 3.5, last time updated with raylib 4.0
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2025 Vlad Adrian (@demizdor)
*
********************************************************************************************/

import {BLACK, BLUE, BeginDrawing, BeginMode3D,
    BeginShaderMode, BoundingBox, CAMERA_FREE, CAMERA_ORBITAL, CAMERA_PERSPECTIVE, Camera3D,
    ClearBackground, CloseWindow, ColorFromHSV,
    DARKBLUE,
    DARKGRAY, DARKGREEN, DARKPURPLE, DisableCursor, DrawCubeV, DrawCubeWires, DrawCubeWiresV, DrawFPS, DrawGrid,
    DrawText,
    EndDrawing,
    EndMode3D,
    EndShaderMode, FLAG_MSAA_4X_HINT,
    FLAG_VSYNC_HINT,
    GetCharPressed, GetCodepoint, GetFontDefault,
    GetFrameTime, GetGlyphIndex,
    GetMousePosition, GetRandomValue,
    GetRayCollisionBox,
    GetScreenToWorldRay, InitWindow,
    IsFileDropped,
    IsFileExtension,
    IsKeyDown,
    IsKeyPressed,
    IsMouseButtonPressed,
    KEY_BACKSPACE,
    KEY_DELETE,
    KEY_DOWN,
    KEY_END,
    KEY_ENTER,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_HOME,
    KEY_INSERT,
    KEY_LEFT,
    KEY_PAGE_DOWN,
    KEY_PAGE_UP,
    KEY_RIGHT,
    KEY_TAB,
    KEY_UP,
    LoadDroppedFiles,
    LoadFont,
    LoadFontEx,
    LoadShader, MAROON,
    MOUSE_BUTTON_LEFT, MeasureText, RAYWHITE, RED, Rectangle,
    SetConfigFlags, SetTargetFPS, TextFormat, TextLength, UnloadFont, UpdateCamera, VIOLET, Vector3, WindowShouldClose } from 'rayjs:raylib';
import * as rg from 'rayjs:rlgl';

//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
const LETTER_BOUNDRY_SIZE = 0.25;
const TEXT_MAX_LAYERS = 32;
const LETTER_BOUNDRY_COLOR = VIOLET;

let SHOW_LETTER_BOUNDRY = false;
let SHOW_TEXT_BOUNDRY = false;

class WaveTextConfig{
    constructor() {
        this.waveRange=new Vector3();
        this.waveSpeed=new Vector3();
        this.waveOffset=new Vector3();
    }
}

//--------------------------------------------------------------------------------------
// Module Functions
//--------------------------------------------------------------------------------------

// Draw codepoint at specified position in 3D space
function DrawTextCodepoint3D(font, codepoint, position, fontSize, backface, tint) {
    // Character index position in sprite font
    // NOTE: In case a codepoint is not available in the font, index returned points to '?'
    let index = GetGlyphIndex(font, codepoint);
    let scale = fontSize/font.baseSize;

    // Character destination rectangle on screen
    // NOTE: We consider charsPadding on drawing
    position.x += (font.glyphs[index].offsetX - font.glyphPadding)/font.baseSize*scale;
    position.z += (font.glyphs[index].offsetY - font.glyphPadding)/font.baseSize*scale;

    // Character source rectangle from font texture atlas
    // NOTE: We consider chars padding when drawing, it could be required for outline/glow shader effects
    let srcRec = new Rectangle( font.recs[index].x - font.glyphPadding, font.recs[index].y - font.glyphPadding,
    font.recs[index].width + 2*font.glyphPadding, font.recs[index].height + 2*font.glyphPadding );

    let width =  (font.recs[index].width + 2*font.glyphPadding)/font.baseSize*scale;
    let height = (font.recs[index].height + 2*font.glyphPadding)/font.baseSize*scale;

    if (font.texture.id > 0) {
        const x = 0;
        const y = 0;
        const z = 0;

        // normalized texture coordinates of the glyph inside the font texture (0.0f -> 1.0f)
        const tx = srcRec.x/font.texture.width;
        const ty = srcRec.y/font.texture.height;
        const tw = (srcRec.x+srcRec.width)/font.texture.width;
        const th = (srcRec.y+srcRec.height)/font.texture.height;

        if (SHOW_LETTER_BOUNDRY) DrawCubeWiresV(new Vector3( position.x + width/2, position.y, position.z + height/2), new Vector3( width, LETTER_BOUNDRY_SIZE, height ), LETTER_BOUNDRY_COLOR);

        rg.rlCheckRenderBatchLimit(4 + 4*backface);
        rg.rlSetTexture(font.texture.id);

        rg.rlPushMatrix();
        rg.rlTranslatef(position.x, position.y, position.z);

        rg.rlBegin(rg.RL_QUADS);
        rg.rlColor4ub(tint.r, tint.g, tint.b, tint.a);

        // Front Face
        rg.rlNormal3f(0, 1, 0);                                   // Normal Pointing Up
        rg.rlTexCoord2f(tx, ty); rg.rlVertex3f(x,         y, z);              // Top Left Of The Texture and Quad
        rg.rlTexCoord2f(tx, th); rg.rlVertex3f(x,         y, z + height);     // Bottom Left Of The Texture and Quad
        rg.rlTexCoord2f(tw, th); rg.rlVertex3f(x + width, y, z + height);     // Bottom Right Of The Texture and Quad
        rg.rlTexCoord2f(tw, ty); rg.rlVertex3f(x + width, y, z);              // Top Right Of The Texture and Quad

        if (backface) {
            // Back Face
            rg.rlNormal3f(0, -1, 0);                              // Normal Pointing Down
            rg.rlTexCoord2f(tx, ty); rg.rlVertex3f(x,         y, z);          // Top Right Of The Texture and Quad
            rg.rlTexCoord2f(tw, ty); rg.rlVertex3f(x + width, y, z);          // Top Left Of The Texture and Quad
            rg.rlTexCoord2f(tw, th); rg.rlVertex3f(x + width, y, z + height); // Bottom Left Of The Texture and Quad
            rg.rlTexCoord2f(tx, th); rg.rlVertex3f(x,         y, z + height); // Bottom Right Of The Texture and Quad
        }
        rg.rlEnd();
        rg.rlPopMatrix();

        rg.rlSetTexture(0);
    }
}

// Draw a 2D text in 3D space
function DrawText3D(font, text, position, fontSize, fontSpacing, lineSpacing, backface, tint) {
    let length = TextLength(text);          // Total length in bytes of the text, scanned by codepoints in loop

    let textOffsetY = 0;               // Offset between lines (on line break '\n')
    let textOffsetX = 0;               // Offset X to next character to draw

    let scale = fontSize/font.baseSize;

    for (let i = 0; i < length;) {
        // Get next codepoint from byte string and glyph index in font
        let codepointByteCount = [0];
        let codepoint = GetCodepoint(text.substring(i), codepointByteCount);
        let index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount[0] = 1;

        if (codepoint == '\n'.codePointAt(0)) {
            // NOTE: Fixed line spacing of 1.5 line-height
            // TODO: Support custom line spacing defined by user
            textOffsetY += scale + lineSpacing/font.baseSize*scale;
            textOffsetX = 0;
        } else {
            if ((codepoint != ' '.codePointAt(0)) && (codepoint != '\t'.codePointAt(0))) {
                DrawTextCodepoint3D(font, codepoint, new Vector3( position.x + textOffsetX, position.y, position.z + textOffsetY ), fontSize, backface, tint);
            }

            if (font.glyphs[index].advanceX == 0) textOffsetX += (font.recs[index].width + fontSpacing)/font.baseSize*scale;
            else textOffsetX += (font.glyphs[index].advanceX + fontSpacing)/font.baseSize*scale;
        }

        i += codepointByteCount[0];   // Move text bytes counter to next codepoint
    }
}

// Measure a text in 3D. For some reason `MeasureTextEx()` just doesn't seem to work so i had to use this instead.
function MeasureText3D(font, text, fontSize, fontSpacing, lineSpacing) {
    let len = TextLength(text);
    let tempLen = 0;                // Used to count longer text line num chars
    let lenCounter = 0;

    let tempTextWidth = 0;     // Used to count longer text line width

    let scale = fontSize/font.baseSize;
    let textHeight = scale;
    let textWidth = 0;

    let letter = 0;                 // Current character
    let index = 0;                  // Index position in sprite font

    for (let i = 0; i < len; i++) {
        lenCounter++;

        let next = [0];
        letter = GetCodepoint(text.substring(i), next);
        index = GetGlyphIndex(font, letter);

        // NOTE: normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol so to not skip any we set next = 1
        if (letter == 0x3f) next[0] = 1;
        i += next[0] - 1;

        if (letter != '\n'.codePointAt(0)) {
            if (font.glyphs[index].advanceX != 0) textWidth += (font.glyphs[index].advanceX+fontSpacing)/font.baseSize*scale;
            else textWidth += (font.recs[index].width + font.glyphs[index].offsetX)/font.baseSize*scale;
        } else {
            if (tempTextWidth < textWidth) tempTextWidth = textWidth;
            lenCounter = 0;
            textWidth = 0;
            textHeight += scale + lineSpacing/font.baseSize*scale;
        }

        if (tempLen < lenCounter) tempLen = lenCounter;
    }

    if (tempTextWidth < textWidth) tempTextWidth = textWidth;

    let vec = new Vector3();
    vec.x = tempTextWidth + ((tempLen - 1)*fontSpacing/font.baseSize*scale); // Adds chars spacing to measure
    vec.y = 0.25;
    vec.z = textHeight;

    return vec;
}

// Draw a 2D text in 3D space and wave the parts that start with `~~` and end with `~~`.
// This is a modified version of the original code by @Nighten found here https://github.com/NightenDushi/Raylib_DrawTextStyle
function DrawTextWave3D(font, text, position, fontSize, fontSpacing, lineSpacing, backface, config, time, tint) {
    let length = TextLength(text);          // Total length in bytes of the text, scanned by codepoints in loop

    let textOffsetY = 0;               // Offset between lines (on line break '\n')
    let textOffsetX = 0;               // Offset X to next character to draw

    let scale = fontSize/font.baseSize;

    let wave = false;

    for (let i = 0, k = 0; i < length; ++k) {
        // Get next codepoint from byte string and glyph index in font
        let codepointByteCount = [0];
        let codepoint = GetCodepoint(text.substring(i), codepointByteCount);
        let index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount[0] = 1;

        if (codepoint == '\n'.codePointAt(0)) {
            // NOTE: Fixed line spacing of 1.5 line-height
            // TODO: Support custom line spacing defined by user
            textOffsetY += scale + lineSpacing/font.baseSize*scale;
            textOffsetX = 0;
            k = 0;
        } else if (codepoint == '~'.codePointAt(0)) {
            if (GetCodepoint(text.substring(i+1), codepointByteCount) == '~'.codePointAt(0)) {
                codepointByteCount[0] += 1;
                wave = !wave;
            }
        } else {
            if ((codepoint != ' '.codePointAt(0)) && (codepoint != '\t'.codePointAt(0))) {
                let pos = position;
                if (wave) { // Apply the wave effect
                    pos.x += Math.sin(time*config.waveSpeed.x-k*config.waveOffset.x)*config.waveRange.x;
                    pos.y += Math.sin(time*config.waveSpeed.y-k*config.waveOffset.y)*config.waveRange.y;
                    pos.z += Math.sin(time*config.waveSpeed.z-k*config.waveOffset.z)*config.waveRange.z;
                }

                DrawTextCodepoint3D(font, codepoint, new Vector3( pos.x + textOffsetX, pos.y, pos.z + textOffsetY ), fontSize, backface, tint);
            }

            if (font.glyphs[index].advanceX == 0) textOffsetX += (font.recs[index].width + fontSpacing)/font.baseSize*scale;
            else textOffsetX += (font.glyphs[index].advanceX + fontSpacing)/font.baseSize*scale;
        }

        i += codepointByteCount[0];   // Move text bytes counter to next codepoint
    }
}

// Measure a text in 3D ignoring the `~~` chars.
function MeasureTextWave3D(font, text, fontSize, fontSpacing, lineSpacing) {
    let len = TextLength(text);
    let tempLen = 0;                // Used to count longer text line num chars
    let lenCounter = 0;

    let tempTextWidth = 0;     // Used to count longer text line width

    let scale = fontSize/font.baseSize;
    let textHeight = scale;
    let textWidth = 0;

    let letter = 0;                 // Current character
    let index = 0;                  // Index position in sprite font

    for (let i = 0; i < len; i++) {
        lenCounter++;
        let next = [0];
        letter = GetCodepoint(text.substring(i), next);
        index = GetGlyphIndex(font, letter);

        // NOTE: normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol so to not skip any we set next = 1
        if (letter == 0x3f) next[0] = 1;
        i += next[0] - 1;
        if (letter != '\n'.codePointAt(0)) {
            if (letter == '~'.codePointAt(0) && GetCodepoint(text.substring(i+1), next) == '~'.codePointAt(0)) {
                i++;
            } else {
                if (font.glyphs[index].advanceX != 0) textWidth += (font.glyphs[index].advanceX+fontSpacing)/font.baseSize*scale;
                else textWidth += (font.recs[index].width + font.glyphs[index].offsetX)/font.baseSize*scale;
            }
        } else {
            if (tempTextWidth < textWidth) tempTextWidth = textWidth;
            lenCounter = 0;
            textWidth = 0;
            textHeight += scale + lineSpacing/font.baseSize*scale;
        }

        if (tempLen < lenCounter) tempLen = lenCounter;
    }
    if (tempTextWidth < textWidth) tempTextWidth = textWidth;

    let vec = new Vector3();
    vec.x = tempTextWidth + ((tempLen - 1)*fontSpacing/font.baseSize*scale); // Adds chars spacing to measure
    vec.y = 0.25;
    vec.z = textHeight;

    return vec;
}

// Generates a nice color with a random hue
function GenerateRandomColor(s, v) {
    const Phi = 0.618033988749895; // Golden ratio conjugate
    let h = GetRandomValue(0, 360);
    h = (h + h*Phi)% 360;
    return ColorFromHSV(h, s, v);
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const screenWidth = 800;
    const screenHeight = 450;
    let logId=1;

    SetConfigFlags(FLAG_MSAA_4X_HINT|FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [text] example - draw 2D text in 3D");

    let spin = true;        // Spin the camera?
    let multicolor = false; // Multicolor mode

    // Define the camera to look into our 3d world
    let camera = new Camera3D();
    camera.position = new Vector3( -10, 15, -10 );   // Camera position
    camera.target = new Vector3( 0, 0, 0 );          // Camera looking at point
    camera.up = new Vector3( 0, 1, 0 );              // Camera up vector (rotation towards target)
    camera.fovy = 45;                                    // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                 // Camera projection type

    let camera_mode = CAMERA_ORBITAL;

    let cubePosition = new Vector3( 0, 1, 0 );
    let cubeSize = new Vector3( 2, 2, 2 );

    // Use the default font
    let font = GetFontDefault();
    let fontSize = 8;
    let fontSpacing = 0.5;
    let lineSpacing = -1;

    // Set the text (using markdown!)
    let text = "Hello ~~World~~ in 3D!";
    let tbox = new Vector3();
    let layers = 1;
    let quads = 0;
    let layerDistance = 0.01;

    let wcfg = new WaveTextConfig();
    wcfg.waveSpeed.x = wcfg.waveSpeed.y = 3; wcfg.waveSpeed.z = 0.5;
    wcfg.waveOffset.x = wcfg.waveOffset.y = wcfg.waveOffset.z = 0.35;
    wcfg.waveRange.x = wcfg.waveRange.y = wcfg.waveRange.z = 0.45;

    let time = 0;

    // Setup a light and dark color
    let light = MAROON;
    let dark = RED;

    // Load the alpha discard shader
    let alphaDiscard = LoadShader(null, "resources/shaders/glsl330/alpha_discard.fs");

    // Array filled with multiple random colors (when multicolor mode is set)
    let multi = new Array(TEXT_MAX_LAYERS);

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(camera, camera_mode);
        // Handle font files dropped
        if (IsFileDropped()) {
            let droppedFiles = LoadDroppedFiles();

            // NOTE: We only support first ttf file dropped
            if (IsFileExtension(droppedFiles[0], ".ttf")) {
                UnloadFont(font);
                font = LoadFontEx(droppedFiles[0], fontSize, 0, 0);
            } else if (IsFileExtension(droppedFiles[0], ".fnt")) {
                UnloadFont(font);
                font = LoadFont(droppedFiles[0]);
                fontSize = font.baseSize;
            }
        }
        // Handle Events
        if (IsKeyPressed(KEY_F1)) SHOW_LETTER_BOUNDRY = !SHOW_LETTER_BOUNDRY;
        if (IsKeyPressed(KEY_F2)) SHOW_TEXT_BOUNDRY = !SHOW_TEXT_BOUNDRY;
        if (IsKeyPressed(KEY_F3)) {
            // Handle camera change
            spin = !spin;
            // we need to reset the camera when changing modes
            camera = new Camera3D();
            camera.target = new Vector3( 0, 0, 0 );          // Camera looking at point
            camera.up = new Vector3( 0, 1, 0 );              // Camera up vector (rotation towards target)
            camera.fovy = 45;                                    // Camera field-of-view Y
            camera.projection = CAMERA_PERSPECTIVE;                 // Camera mode type

            if (spin) {
                camera.position = new Vector3( -10, 15, -10 );   // Camera position
                camera_mode = CAMERA_ORBITAL;
            } else {
                camera.position = new Vector3( 10, 10, -10 );   // Camera position
                camera_mode = CAMERA_FREE;
            }
        }
        // Handle clicking the cube
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            let ray = GetScreenToWorldRay(GetMousePosition(), camera);

            // Check collision between ray and box
            let collision = GetRayCollisionBox(ray,
                            new BoundingBox(new Vector3( cubePosition.x - cubeSize.x/2, cubePosition.y - cubeSize.y/2, cubePosition.z - cubeSize.z/2 ),
                                            new Vector3( cubePosition.x + cubeSize.x/2, cubePosition.y + cubeSize.y/2, cubePosition.z + cubeSize.z/2 )
                            )
            );
            if (collision.hit) {
                // Generate new random colors
                light = GenerateRandomColor(0.5, 0.78);
                dark = GenerateRandomColor(0.4, 0.58);
            }
        }
        // Handle text layers changes
        if (IsKeyPressed(KEY_HOME)) { if (layers > 1) --layers; }
        else if (IsKeyPressed(KEY_END)) { if (layers < TEXT_MAX_LAYERS) ++layers; }

        // Handle text changes
        if (IsKeyPressed(KEY_LEFT)) fontSize -= 0.5;
        else if (IsKeyPressed(KEY_RIGHT)) fontSize += 0.5;
        else if (IsKeyPressed(KEY_UP)) fontSpacing -= 0.1;
        else if (IsKeyPressed(KEY_DOWN)) fontSpacing += 0.1;
        else if (IsKeyPressed(KEY_PAGE_UP)) lineSpacing -= 0.1;
        else if (IsKeyPressed(KEY_PAGE_DOWN)) lineSpacing += 0.1;
        else if (IsKeyDown(KEY_INSERT)) layerDistance -= 0.001;
        else if (IsKeyDown(KEY_DELETE)) layerDistance += 0.001;
        else if (IsKeyPressed(KEY_TAB)) {
            multicolor = !multicolor;   // Enable /disable multicolor mode

            if (multicolor) {
                // Fill color array with random colors
                for (let i = 0; i < TEXT_MAX_LAYERS; ++i) {
                    multi[i] = GenerateRandomColor(0.5, 0.8);
                    multi[i].a = GetRandomValue(0, 255);
                }
            }
        }
        // Handle text input
        let ch = GetCharPressed();
        if (IsKeyPressed(KEY_BACKSPACE)) {
            // Remove last char
            let len = TextLength(text);
            if (len > 0) text = text.substring(0,len-1);
        } else if (IsKeyPressed(KEY_ENTER)) {
            // handle newline
            text=text+'\n';
        } else {
            // append only printable chars
            text=text+ch;
        }

        // Measure 3D text so we can center it
        tbox = MeasureTextWave3D(font, text, fontSize, fontSpacing, lineSpacing);
        quads = 0;                      // Reset quad counter
        time += GetFrameTime();         // Update timer needed by `DrawTextWave3D()`
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawCubeV(cubePosition, cubeSize, dark);
                DrawCubeWires(cubePosition, 2.1, 2.1, 2.1, light);

                DrawGrid(10, 2);
                // Use a shader to handle the depth buffer issue with transparent textures
                // NOTE: more info at https://bedroomcoders.co.uk/posts/198
                BeginShaderMode(alphaDiscard);

                    // Draw the 3D text above the red cube
                    rg.rlPushMatrix();
                        rg.rlRotatef(90, 1, 0, 0);
                        rg.rlRotatef(90, 0, 0, -1);

                        for (let i = 0; i < layers; ++i) {
                            let clr = light;
                            if (multicolor) clr = multi[i];
                            DrawTextWave3D(font, text, new Vector3( -tbox.x/2, layerDistance*i, -4.5 ), fontSize, fontSpacing, lineSpacing, true, wcfg, time, clr);
                        }

                        // Draw the text boundry if set
                        if (SHOW_TEXT_BOUNDRY) DrawCubeWiresV(new Vector3( 0, 0, -4.5 + tbox.z/2 ), tbox, dark);
                    rg.rlPopMatrix();

                    // Don't draw the letter boundries for the 3D text below
                    let slb = SHOW_LETTER_BOUNDRY;
                    SHOW_LETTER_BOUNDRY = false;
                    // Draw 3D options (use default font)
                    //-------------------------------------------------------------------------
                    rg.rlPushMatrix();
                        rg.rlRotatef(180, 0, 1, 0);
                        let opt = TextFormat("< SIZE: %2.1f >", fontSize);
                        quads += TextLength(opt);
                        let m = MeasureText3D(GetFontDefault(), opt, 8, 1, 0);
                        let pos = new Vector3( -m.x/2, 0.01, 2);
                        DrawText3D(GetFontDefault(), opt, pos, 8, 1, 0, false, BLUE);
                        pos.z += 0.5 + m.z;

                        opt = TextFormat("< SPACING: %2.1f >", fontSpacing);
                        quads += TextLength(opt);
                        m = MeasureText3D(GetFontDefault(), opt, 8, 1, 0);
                        pos.x = -m.x/2;
                        DrawText3D(GetFontDefault(), opt, pos, 8, 1, 0, false, BLUE);
                        pos.z += 0.5 + m.z;

                        opt = TextFormat("< LINE: %2.1f >", lineSpacing);
                        quads += TextLength(opt);
                        m = MeasureText3D(GetFontDefault(), opt, 8, 1, 0);
                        pos.x = -m.x/2;
                        DrawText3D(GetFontDefault(), opt, pos, 8, 1, 0, false, BLUE);
                        pos.z += 1 + m.z;

                        opt = TextFormat("< LBOX: %3s >", slb? "ON" : "OFF");
                        quads += TextLength(opt);
                        m = MeasureText3D(GetFontDefault(), opt, 8, 1, 0);
                        pos.x = -m.x/2;
                        DrawText3D(GetFontDefault(), opt, pos, 8, 1, 0, false, RED);
                        pos.z += 0.5 + m.z;

                        opt = TextFormat("< TBOX: %3s >", SHOW_TEXT_BOUNDRY? "ON" : "OFF");
                        quads += TextLength(opt);
                        m = MeasureText3D(GetFontDefault(), opt, 8, 1, 0);
                        pos.x = -m.x/2;
                        DrawText3D(GetFontDefault(), opt, pos, 8, 1, 0, false, RED);
                        pos.z += 0.5 + m.z;

                        opt = TextFormat("< LAYER DISTANCE: %.3f >", layerDistance);
                        quads += TextLength(opt);
                        m = MeasureText3D(GetFontDefault(), opt, 8, 1, 0);
                        pos.x = -m.x/2;
                        DrawText3D(GetFontDefault(), opt, pos, 8, 1, 0, false, DARKPURPLE);
                    rg.rlPopMatrix();
                    //-------------------------------------------------------------------------

                    // Draw 3D info text (use default font)
                    //-------------------------------------------------------------------------
                    opt = "All the text displayed here is in 3D";
                    quads += 36;
                    m = MeasureText3D(GetFontDefault(), opt, 10, 0.5, 0);
                    pos = new Vector3(-m.x/2, 0.01, 2);
                    DrawText3D(GetFontDefault(), opt, pos, 10, 0.5, 0, false, DARKBLUE);
                    pos.z += 1.5 + m.z;

                    opt = "press [Left]/[Right] to change the font size";
                    quads += 44;
                    m = MeasureText3D(GetFontDefault(), opt, 6, 0.5, 0);
                    pos.x = -m.x/2;
                    DrawText3D(GetFontDefault(), opt, pos, 6, 0.5, 0, false, DARKBLUE);
                    pos.z += 0.5 + m.z;

                    opt = "press [Up]/[Down] to change the font spacing";
                    quads += 44;
                    m = MeasureText3D(GetFontDefault(), opt, 6, 0.5, 0);
                    pos.x = -m.x/2;
                    DrawText3D(GetFontDefault(), opt, pos, 6, 0.5, 0, false, DARKBLUE);
                    pos.z += 0.5 + m.z;
                    opt = "press [PgUp]/[PgDown] to change the line spacing";
                    quads += 48;
                    m = MeasureText3D(GetFontDefault(), opt, 6, 0.5, 0);
                    pos.x = -m.x/2;
                    DrawText3D(GetFontDefault(), opt, pos, 6, 0.5, 0, false, DARKBLUE);
                    pos.z += 0.5 + m.z;

                    opt = "press [F1] to toggle the letter boundry";
                    quads += 39;
                    m = MeasureText3D(GetFontDefault(), opt, 6, 0.5, 0);
                    pos.x = -m.x/2;
                    DrawText3D(GetFontDefault(), opt, pos, 6, 0.5, 0, false, DARKBLUE);
                    pos.z += 0.5 + m.z;

                    opt = "press [F2] to toggle the text boundry";
                    quads += 37;
                    m = MeasureText3D(GetFontDefault(), opt, 6, 0.5, 0);
                    pos.x = -m.x/2;
                    DrawText3D(GetFontDefault(), opt, pos, 6, 0.5, 0, false, DARKBLUE);
                    //-------------------------------------------------------------------------

                    SHOW_LETTER_BOUNDRY = slb;
                EndShaderMode();

            EndMode3D();
            // Draw 2D info text & stats
            //-------------------------------------------------------------------------
            DrawText("Drag & drop a font file to change the font!\nType something, see what happens!\n\n"+
            "Press [F3] to toggle the camera", 10, 35, 10, BLACK);

            quads += TextLength(text)*2*layers;
            let tmp = TextFormat("%2i layer(s) | %s camera | %4i quads (%4i verts)", layers, spin? "ORBITAL" : "FREE", quads, quads*4);
            let width = MeasureText(tmp, 10);
            DrawText(tmp, screenWidth - 20 - width, 10, 10, DARKGREEN);

            tmp = "[Home]/[End] to add/remove 3D text layers";
            width = MeasureText(tmp, 10);
            DrawText(tmp, screenWidth - 20 - width, 25, 10, DARKGRAY);

            tmp = "[Insert]/[Delete] to increase/decrease distance between layers";
            width = MeasureText(tmp, 10);
            DrawText(tmp, screenWidth - 20 - width, 40, 10, DARKGRAY);

            tmp = "click the [CUBE] for a random color";
            width = MeasureText(tmp, 10);
            DrawText(tmp, screenWidth - 20 - width, 55, 10, DARKGRAY);
            tmp = "[Tab] to toggle multicolor mode";
            width = MeasureText(tmp, 10);
            DrawText(tmp, screenWidth - 20 - width, 70, 10, DARKGRAY);
            //-------------------------------------------------------------------------

            DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadFont(font);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}