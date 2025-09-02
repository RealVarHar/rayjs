// @ts-nocheck
/*******************************************************************************************
*
*   raylib [text] example - Rectangle bounds
*
*   Example complexity rating: [★★★★] 4/4
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2025 Vlad Adrian (@demizdor) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {
    DrawRectangleRec,
    DrawTextCodepoint,
    GetCodepoint,
    GetFontDefault,
    GetGlyphIndex,
    GetMousePosition,
    CheckCollisionPointRec,
    IsMouseButtonDown,
    MOUSE_BUTTON_LEFT,
    BeginDrawing,
    ClearBackground,
    DrawRectangleLinesEx,
    GRAY,
    InitWindow,
    IsKeyPressed,
    KEY_SPACE,
    MAROON,
    Rectangle,
    SetTargetFPS,
    TextLength,
    Vector2,
    RAYWHITE,
    WHITE,
    WindowShouldClose,
    IsMouseButtonReleased, Fade, DrawRectangle, DrawText, BLACK, RED, EndDrawing, CloseWindow
} from "rayjs:raylib";

// Draw text using font inside rectangle limits
function DrawTextBoxed(font, text, rec, fontSize, spacing, wordWrap, tint) {
    DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0, 0, WHITE, WHITE);
}

// Draw text using font inside rectangle limits with support for text selection
function DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, selectStart, selectLength, selectTint, selectBackTint) {
    let length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    let textOffsetY = 0;       // Offset between lines (on line break '\n')
    let textOffsetX = 0;       // Offset X to next character to draw

    let scaleFactor = fontSize/font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    const MEASURE_STATE = 0, DRAW_STATE = 1;
    let state = wordWrap? MEASURE_STATE : DRAW_STATE;

    let startLine = -1;         // Index where to begin drawing (where a line begins)
    let endLine = -1;           // Index where to stop drawing (where a line ends)
    let lastk = -1;             // Holds last value of the character position

    for (let i = 0, k = 0; i < length; i++, k++) {
        // Get next codepoint from byte string and glyph index in font
        let codepointByteCount = [0];
        let codepoint = GetCodepoint(text.substring(i), codepointByteCount);
        let index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount[0] = 1;
        i += (codepointByteCount[0] - 1);

        let glyphWidth = 0;
        if (codepoint != '\n'.codePointAt(0)) {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE) {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' '.codePointAt(0)) || (codepoint == '\t'.codePointAt(0)) || (codepoint == '\n'.codePointAt(0))) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width) {
                endLine = (endLine < 1)? i : endLine;
                if (i == endLine) endLine -= codepointByteCount[0];
                if ((startLine + codepointByteCount[0]) == endLine) endLine = (i - codepointByteCount[0]);

                state = -state+1;
            } else if ((i + 1) == length) {
                endLine = i;
                state = -state+1;
            }
            else if (codepoint == '\n'.codePointAt(0)) state = -state+1;

            if (state == DRAW_STATE) {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                const tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        } else {
            if (codepoint == '\n'.codePointAt(0)) {
                if (!wordWrap) {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            } else {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width)) {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize*scaleFactor) > rec.height) break;

                // Draw selection background
                let isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength))) {
                    DrawRectangleRec( new Rectangle( rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, font.baseSize*scaleFactor ), selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' '.codePointAt(0)) && (codepoint != '\t'.codePointAt(0))) {
                    DrawTextCodepoint(font, codepoint, new Vector2( rec.x + textOffsetX, rec.y + textOffsetY ), fontSize, isGlyphSelected? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine)) {
                textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = -state+1;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' '.codePointAt(0))) textOffsetX += glyphWidth;  // avoid leading spaces
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

    InitWindow(screenWidth, screenHeight, "raylib [text] example - draw text inside a rectangle");

    const text = "Text cannot escape\tthis container\t...word wrap also works when active so here's \
a long text for testing.\n\nLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod \
tempor incididunt ut labore et dolore magna aliqua. Nec ullamcorper sit amet risus nullam eget felis eget.";

    let resizing = false;
    let wordWrap = true;

    let container = new Rectangle( 25, 25, screenWidth - 50, screenHeight - 250 );
    let resizer = new Rectangle( container.x + container.width - 17, container.y + container.height - 17, 14, 14 );

    // Minimum width and heigh for the container rectangle
    const minWidth = 60;
    const minHeight = 60;
    const maxWidth = screenWidth - 50;
    const maxHeight = screenHeight - 160;

    let lastMouse = new Vector2( 0, 0 ); // Stores last mouse coordinates
    let borderColor = MAROON;         // Container border color
    let font = GetFontDefault();       // Get default system font

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {       // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_SPACE)) wordWrap = !wordWrap;

        let mouse = GetMousePosition();

        // Check if the mouse is inside the container and toggle border color
        if (CheckCollisionPointRec(mouse, container)) borderColor = Fade(MAROON, 0.4);
        else if (!resizing) borderColor = MAROON;

        // Container resizing logic
        if (resizing) {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) resizing = false;

            let width = container.width + (mouse.x - lastMouse.x);
            container.width = (width > minWidth)? ((width < maxWidth)? width : maxWidth) : minWidth;

            let height = container.height + (mouse.y - lastMouse.y);
            container.height = (height > minHeight)? ((height < maxHeight)? height : maxHeight) : minHeight;
        } else {
            // Check if we're resizing
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, resizer)) resizing = true;
        }

        // Move resizer rectangle properly
        resizer.x = container.x + container.width - 17;
        resizer.y = container.y + container.height - 17;

        lastMouse = mouse; // Update mouse
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangleLinesEx(container, 3, borderColor);    // Draw container border

            // Draw text in container (add some padding)
            DrawTextBoxed(font, text, new Rectangle( container.x + 4, container.y + 4, container.width - 4, container.height - 4 ), 20, 2, wordWrap, GRAY);

            DrawRectangleRec(resizer, borderColor);             // Draw the resize box

            // Draw bottom info
            DrawRectangle(0, screenHeight - 54, screenWidth, 54, GRAY);
            DrawRectangleRec( new Rectangle( 382, screenHeight - 34, 12, 12 ), MAROON);

            DrawText("Word Wrap: ", 313, screenHeight-115, 20, BLACK);
            if (wordWrap) DrawText("ON", 447, screenHeight - 115, 20, RED);
            else DrawText("OFF", 447, screenHeight - 115, 20, BLACK);

            DrawText("Press [SPACE] to toggle word wrap", 218, screenHeight - 86, 20, GRAY);

            DrawText("Click hold & drag the    to resize the container", 155, screenHeight - 38, 20, RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}