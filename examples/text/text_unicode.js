/*******************************************************************************************
*
*   raylib [text] example - Unicode
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
*   Copyright (c) 2019-2025 Vlad Adrian (@demizdor) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

import {BeginDrawing, CheckCollisionPointRec, ClearBackground, CloseWindow, ColorFromHSV, DrawRectangleRec,
    DrawText,
    DrawTextCodepoint, DrawTextEx, DrawTriangle, EndDrawing, FLAG_MSAA_4X_HINT, FLAG_VSYNC_HINT, Fade,
    GRAY, GetCodepoint,
    GetCodepointCount, GetFontDefault, GetGlyphIndex,
    GetMousePosition, GetRandomValue,
    InitWindow, IsKeyPressed, IsMouseButtonPressed, KEY_SPACE, LIGHTGRAY, LoadFont, MOUSE_BUTTON_LEFT,
    MeasureTextEx, RAYWHITE, Rectangle,
    SetConfigFlags, SetTargetFPS, TextFormat, TextIsEqual, TextLength, UnloadFont, Vector2, WHITE, WindowShouldClose } from "rayjs:raylib";


const EMOJI_PER_WIDTH = 8;
const EMOJI_PER_HEIGHT = 4;

function decodehextext(txt){
    let uritext='';
    for(let i=0;i<txt.length;i+=2){
        uritext+='%'+txt.substring(i,i+2);
    }
    return decodeURIComponent(uritext);
}

//NOTE: in js utf-16 is native, and utf8 files will be read correctly, so it is recommended to just store these characters decoded
//here, we can still see original c hex data, but without \x prefix and \0 delimiter to make the decoder simpler
//considered: oryginal: \xF0\x9F\x8C\x80\x00, trimmed: F09F8C80, unicode: \uD83C\uDF00, utf-8: 🌀

// String containing 180 emoji codepoints
const emojiCodepoints = ["F09F8C80","F09F9880","F09F9882","F09FA4A3","F09F9883","F09F9886","F09F9889",
    "F09F988B","F09F988E","F09F988D","F09F9898","F09F9897","F09F9899","F09F989A","F09F9982",
    "F09FA497","F09FA4A9","F09FA494","F09FA4A8","F09F9890","F09F9891","F09F98B6","F09F9984",
    "F09F988F","F09F98A3","F09F98A5","F09F98AE","F09FA490","F09F98AF","F09F98AA","F09F98AB",
    "F09F98B4","F09F988C","F09F989B","F09F989D","F09FA4A4","F09F9892","F09F9895","F09F9983",
    "F09FA491","F09F98B2","F09F9981","F09F9896","F09F989E","F09F989F","F09F98A4","F09F98A2",
    "F09F98AD","F09F98A6","F09F98A9","F09FA4AF","F09F98AC","F09F98B0","F09F98B1","F09F98B3",
    "F09FA4AA","F09F98B5","F09F98A1","F09F98A0","F09FA4AC","F09F98B7","F09FA492","F09FA495",
    "F09FA4A2","F09FA4AE","F09FA4A7","F09F9887","F09FA4A0","F09FA4AB","F09FA4AD","F09FA790",
    "F09FA493","F09F9888","F09F91BF","F09F91B9","F09F91BA","F09F9280","F09F91BB","F09F91BD",
    "F09F91BE","F09FA496","F09F92A9","F09F98BA","F09F98B8","F09F98B9","F09F98BB","F09F98BD",
    "F09F9980","F09F98BF","F09F8CBE","F09F8CBF","F09F8D80","F09F8D83","F09F8D87","F09F8D93",
    "F09FA59D","F09F8D85","F09FA5A5","F09FA591","F09F8D86","F09FA594","F09FA595","F09F8CBD",
    "F09F8CB6","F09FA592","F09FA5A6","F09F8D84","F09FA59C","F09F8CB0","F09F8D9E","F09FA590",
    "F09FA596","F09FA5A8","F09FA59E","F09FA780","F09F8D96","F09F8D97","F09FA5A9","F09FA593",
    "F09F8D94","F09F8D9F","F09F8D95","F09F8CAD","F09FA5AA","F09F8CAE","F09F8CAF","F09FA599",
    "F09FA59A","F09F8DB3","F09FA598","F09F8DB2","F09FA5A3","F09FA597","F09F8DBF","F09FA5AB",
    "F09F8DB1","F09F8D98","F09F8D9D","F09F8DA0","F09F8DA2","F09F8DA5","F09F8DA1","F09FA59F",
    "F09FA5A1","F09F8DA6","F09F8DAA","F09F8E82","F09F8DB0","F09FA5A7","F09F8DAB","F09F8DAF",
    "F09F8DBC","F09FA59B","F09F8DB5","F09F8DB6","F09F8DBE","F09F8DB7","F09F8DBB","F09FA582",
    "F09FA583","F09FA5A4","F09FA5A2","F09F9181","F09F9185","F09F9184","F09F928B","F09F9298",
    "F09F9293","F09F9297","F09F9299","F09F929B","F09FA7A1","F09F929C","F09F96A4","F09F929D",
    "F09F929F","F09F928C","F09F92A4","F09F92A2","F09F92A3"].map(a=>decodehextext(a)).join('');


const messages = [ // Array containing all of the emojis messages
    ["46616C736368657320C39C62656E20766F6E2058796C6F70686F6E6D7573696B207175C3A46C74206A6564656E206772C3B6C39F6572656E205A77657267", "German"],
    ["426569C39F206E6963687420696E206469652048616E642C2064696520646963682066C3BC74746572742E", "German"],
    ["4175C39F65726F7264656E746C6963686520C39C62656C206572666F726465726E206175C39F65726F7264656E746C69636865204D697474656C2E", "German"],
    ["D4BFD680D5B6D5A1D5B420D5A1D5BAD5A1D5AFD5AB20D5B8D682D5BFD5A5D5AC20D68720D5ABD5B6D5AED5AB20D5A1D5B6D5B0D5A1D5B6D5A3D5ABD5BDD5BF20D5B9D5A8D5B6D5A5D680", "Armenian"],
    ["D4B5D680D5A220D5B8D68020D5AFD5A1D681D5ABD5B6D5A820D5A5D5AFD5A1D68220D5A1D5B6D5BFD5A1D5BC2C20D5AED5A1D5BCD5A5D680D5A820D5A1D5BDD5A1D681D5ABD5B62E2E2E20C2ABD4BFD5B8D5BFD5A820D5B4D5A5D680D5B8D5B6D681D5ABD68120D5A73AC2BB", "Armenian"],
    ["D4B3D5A1D5BCD5A8D59D20D5A3D5A1D680D5B6D5A1D5B62C20D5B1D5ABD682D5B6D5A8D59D20D5B1D5B4D5BCD5A1D5B6", "Armenian"],
    ["4A65C5BC75206B6CC48574772C207370C582C3B364C5BA2046696E6F6D20637AC499C59BC48720677279206861C5846221", "Polish"],
    ["446F6272796D69206368C4996369616D69206A657374207069656BC5826F2077796272756B6F77616E652E", "Polish"],
    ["C38EC89B69206D756CC89B756D6573632063C48320616920616C6573207261796C69622E0AC8986920737065722073C483206169206F207A692062756EC48321", "Romanian"],
    ["D0ADD1852C20D187D183D0B6D0B0D0BA2C20D0BED0B1D189D0B8D0B920D181D18AD191D0BC20D186D0B5D0BD20D188D0BBD18FD0BF2028D18ED184D182D18C2920D0B2D0B4D180D18BD0B7D0B321", "Russian"],
    ["D0AF20D0BBD18ED0B1D0BBD18E207261796C696221", "Russian"],
    ["D09CD0BED0BBD187D0B82C20D181D0BAD180D18BD0B2D0B0D0B9D181D18F20D0B820D182D0B0D0B80AD09820D187D183D0B2D181D182D0B2D0B020D0B820D0BCD0B5D187D182D18B20D181D0B2D0BED0B820E280930AD09FD183D181D0BAD0B0D0B920D0B220D0B4D183D188D0B5D0B2D0BDD0BED0B920D0B3D0BBD183D0B1D0B8D0BDD0B50AD09820D0B2D181D185D0BED0B4D18FD18220D0B820D0B7D0B0D0B9D0B4D183D18220D0BED0BDD0B50AD09AD0B0D0BA20D0B7D0B2D0B5D0B7D0B4D18B20D18FD181D0BDD18BD0B520D0B220D0BDD0BED187D0B82D0AD09BD18ED0B1D183D0B9D181D18F20D0B8D0BCD0B820E2809320D0B820D0BCD0BED0BBD187D0B82E", "Russian"],
    ["566F697820616D62696775C3AB2064E28099756E2063C593757220717569206175207AC3A970687972207072C3A966C3A87265206C6573206A6174746573206465206B697769", "French"],
    ["42656E6A616DC3AD6E2070696469C3B320756E6120626562696461206465206B69776920792066726573613B204E6FC3A92C2073696E2076657267C3BC656E7A612C206C61206DC3A17320657871756973697461206368616D7061C3B1612064656C206D656EC3BA2E", "Spanish"],
    ["CEA4CEB1CF87CEAFCF83CF84CEB720CEB1CEBBCF8ECF80CEB7CEBE20CEB2CEB1CF86CEAECF8220CF88CEB7CEBCCEADCEBDCEB720CEB3CEB72C20CEB4CF81CEB1CF83CEBACEB5CEBBCEAFCEB6CEB5CEB920CF85CF80CEADCF8120CEBDCF89CEB8CF81CEBFCF8D20CEBACF85CEBDCF8CCF82", "Greek"],
    ["CE9720CEBACEB1CEBBCF8DCF84CEB5CF81CEB720CEACCEBCCF85CEBDCEB120CEB5CEAFCEBDCEB1CEB920CEB720CEB5CF80CEAFCEB8CEB5CF83CEB72E", "Greek"],
    ["CEA7CF81CF8CCEBDCEB9CEB120CEBACEB1CEB920CEB6CEB1CEBCCEACCEBDCEB9CEB121", "Greek"],
    ["CEA0CF8ECF8220CF84CEB120CF80CEB1CF8220CF83CEAECEBCCEB5CF81CEB13B", "Greek"],
    ["E68891E883BDE5909EE4B88BE78EBBE79283E8808CE4B88DE4BCA4E8BAABE4BD93E38082", "Chinese"],
    ["E4BDA0E59083E4BA86E59097EFBC9F", "Chinese"],
    ["E4B88DE4BD9CE4B88DE6ADBBE38082", "Chinese"],
    ["E69C80E8BF91E5A5BDE59097EFBC9F", "Chinese"],
    ["E5A19EE7BF81E5A4B1E9A9ACEFBC8CE78489E79FA5E99D9EE7A68FE38082", "Chinese"],
    ["E58D83E5869BE69893E5BE972C20E4B880E5B086E99ABEE6B182", "Chinese"],
    ["E4B887E4BA8BE5BC80E5A4B4E99ABEE38082", "Chinese"],
    ["E9A38EE697A0E5B8B8E9A1BAEFBC8CE585B5E697A0E5B8B8E8839CE38082", "Chinese"],
    ["E6B4BBE588B0E88081EFBC8CE5ADA6E588B0E88081E38082", "Chinese"],
    ["E4B880E8A880E697A2E587BAEFBC8CE9A9B7E9A9ACE99ABEE8BFBDE38082", "Chinese"],
    ["E8B7AFE981A5E79FA5E9A9ACE58A9BEFBC8CE697A5E4B985E8A781E4BABAE5BF83", "Chinese"],
    ["E69C89E79086E8B5B0E9818DE5A4A9E4B88BEFBC8CE697A0E79086E5AFB8E6ADA5E99ABEE8A18CE38082", "Chinese"],
    ["E78CBFE38282E69CA8E3818BE38289E890BDE381A1E3828B", "Japanese"],
    ["E4BA80E381AEE794B2E38288E3828AE5B9B4E381AEE58A9F", "Japanese"],
    ["E38186E38289E38284E381BEE381972020E6809DE381B2E58887E3828BE699822020E78CABE381AEE6818B", "Japanese"],
    ["E8998EE7A9B4E381ABE585A5E38289E3819AE38293E381B0E8998EE5AD90E38292E5BE97E3819AE38082", "Japanese"],
    ["E4BA8CE5858EE38292E8BFBDE38186E88085E381AFE4B880E5858EE38292E38282E5BE97E3819AE38082", "Japanese"],
    ["E9A6ACE9B9BFE381AFE6ADBBE381AAE381AAE3818DE38283E6B2BBE38289E381AAE38184E38082", "Japanese"],
    ["E69EAFE9878EE8B7AFE381ABE38080E5BDB1E3818BE38195E381AAE3828AE381A6E38080E3828FE3818BE3828CE38191E3828A", "Japanese"],
    ["E7B9B0E3828AE8BF94E38197E9BAA6E381AEE7959DE7B8ABE381B5E883A1E89DB6E59389", "Japanese"],
    ["EC9584EB939DED959C20EBB094EB8BA420EC9C84EC979020EAB088EBA7A4EAB8B020EB9190EC978720EB82A0EC958420EB8F88EB8BA42E0AEB8488ED9B8CEB8488ED9B8C20EC8B9CEBA5BC20EC93B4EB8BA42E20EBAAA8EBA5B4EB8A9420EB8298EB9DBC20EAB880EC9E90EB8BA42E0AEB8490EB94B0EB9E8020ED9598EB8A9820EBB3B5ED8C90EC979020EB8298EB8F8420EAB099EC9DB420EC8B9CEBA5BC20EC93B4EB8BA42E", "Korean"],
    ["ECA09C20EB8888EC979020EC9588EAB2BDEC9DB4EB8BA4", "Korean"],
    ["EABFA920EBA8B9EAB3A020EC958C20EBA8B9EB8A94EB8BA4", "Korean"],
    ["EBA19CEBA788EB8A9420ED9598EBA3A8EC9584ECB9A8EC979020EC9DB4EBA3A8EC96B4ECA78420EAB283EC9DB420EC9584EB8B88EB8BA4", "Korean"],
    ["EAB3A0EC839D20EB819DEC979020EB8299EC9DB420EC98A8EB8BA4", "Korean"],
    ["EAB09CECB29CEC9790EC849C20EC9AA920EB829CEB8BA4", "Korean"],
    ["EC9588EB8595ED9598EC84B8EC9A943F", "Korean"],
    ["EBA78CEB8298EC849C20EBB098EAB091EC8AB5EB8B88EB8BA4", "Korean"],
    ["ED959CEAB5ADEBA79020ED9598EC8BA420ECA48420EC9584EC84B8EC9A943F", "Korean"]
].map(a=>{return {text:decodehextext(a[0]),language:a[1]};});

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
// Arrays that holds the random emojis
let emoji = new Array(EMOJI_PER_WIDTH*EMOJI_PER_HEIGHT);
for (let i = 0; i < emoji.length; i++) {
    emoji[i]={};
}

let hovered = -1, selected = -1;

//--------------------------------------------------------------------------------------
// Module functions
//--------------------------------------------------------------------------------------
// Fills the emoji array with random emoji (only those emojis present in fontEmoji)
function RandomizeEmoji() {
    hovered = selected = -1;
    let start = GetRandomValue(45, 360);

    for (let i = 0; i < emoji.length; ++i) {
        // 0-179 emoji codepoints (from emoji char array) each 4bytes + null char
        emoji[i].index = GetRandomValue(0, 179)*2;// Index inside `emojiCodepoints`

        // Generate a random color for this emoji
        emoji[i].color = Fade(ColorFromHSV((start*(i + 1))%360, 0.6, 0.85), 0.8);// Emoji color

        // Set a random message for this emoji
        emoji[i].message = GetRandomValue(0, messages.length - 1);// Message index
    }
}

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
            } else if (codepoint == '\n'.codePointAt(0)) {
                state = -state+1;
            }

            if (state == DRAW_STATE) {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                let tmp = lastk;
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
                    DrawRectangleRec(new Rectangle( rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, font.baseSize*scaleFactor ), selectBackTint);
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

        textOffsetX += glyphWidth;
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

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [text] example - unicode");

    // Load the font resources
    // NOTE: fontAsian is for asian languages,
    // fontEmoji is the emojis and fontDefault is used for everything else
    let fontDefault = LoadFont("resources/dejavu.fnt");
    let fontAsian = LoadFont("resources/noto_cjk.fnt");
    let fontEmoji = LoadFont("resources/symbola.fnt");

    let hoveredPos = new Vector2( 0, 0 );
    let selectedPos = new Vector2( 0, 0 );

    // Set a random set of emojis when starting up
    RandomizeEmoji();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // Add a new set of emojis when SPACE is pressed
        if (IsKeyPressed(KEY_SPACE)) RandomizeEmoji();

        // Set the selected emoji
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (hovered != -1) && (hovered != selected)) {
            selected = hovered;
            selectedPos = hoveredPos;
        }

        let mouse = GetMousePosition();
        let position = new Vector2( 28, 10 );
        hovered = -1;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw random emojis in the background
            //------------------------------------------------------------------------------
            for (let i = 0; i < emoji.length; ++i) {
                const txt = emojiCodepoints.substring(emoji[i].index,emoji[i].index+2);
                let emojiRect = new Rectangle( position.x, position.y, fontEmoji.baseSize, fontEmoji.baseSize );

                if (!CheckCollisionPointRec(mouse, emojiRect)) {
                    DrawTextEx(fontEmoji, txt, position, fontEmoji.baseSize, 1, selected == i ? emoji[i].color : Fade(LIGHTGRAY, 0.4));
                } else {
                    DrawTextEx(fontEmoji, txt, position, fontEmoji.baseSize, 1, emoji[i].color );
                    hovered = i;
                    hoveredPos = position;
                }

                if ((i != 0) && (i%EMOJI_PER_WIDTH == 0)) {
                    position.y += fontEmoji.baseSize + 24.25; position.x = 28.8;
                } else {
                    position.x += fontEmoji.baseSize + 28.8;
                }
            }
            //------------------------------------------------------------------------------

            // Draw the message when a emoji is selected
            //------------------------------------------------------------------------------
            if (selected != -1) {
                const message = emoji[selected].message;
                const horizontalPadding = 20, verticalPadding = 30;
                let font = fontDefault;

                // Set correct font for asian languages
                if (TextIsEqual(messages[message].language, "Chinese") ||
                    TextIsEqual(messages[message].language, "Korean") ||
                    TextIsEqual(messages[message].language, "Japanese")) font = fontAsian;

                // Calculate size for the message box (approximate the height and width)
                let sz = MeasureTextEx(font, messages[message].text, font.baseSize, 1);
                if (sz.x > 300) {
                    sz.y *= sz.x/300; sz.x = 300;
                } else if (sz.x < 160) {
                    sz.x = 160
                };

                let msgRect = new Rectangle( selectedPos.x - 38.8, selectedPos.y, 2 * horizontalPadding + sz.x, 2 * verticalPadding + sz.y );
                msgRect.y -= msgRect.height;

                // Coordinates for the chat bubble triangle
                let a = new Vector2( selectedPos.x, msgRect.y + msgRect.height ), b = new Vector2(a.x + 8, a.y + 10), c= new Vector2( a.x + 10, a.y );

                // Don't go outside the screen
                if (msgRect.x < 10) msgRect.x += 28;
                if (msgRect.y < 10) {
                    msgRect.y = selectedPos.y + 84;
                    a.y = msgRect.y;
                    c.y = a.y;
                    b.y = a.y - 10;

                    // Swap values so we can actually render the triangle :(
                    let tmp = a;
                    a = b;
                    b = tmp;
                }

                if (msgRect.x + msgRect.width > screenWidth) msgRect.x -= (msgRect.x + msgRect.width) - screenWidth + 10;

                // Draw chat bubble
                DrawRectangleRec(msgRect, emoji[selected].color);
                DrawTriangle(a, b, c, emoji[selected].color);

                // Draw the main text message
                let textRect = new Rectangle( msgRect.x + horizontalPadding/2, msgRect.y + verticalPadding/2, msgRect.width - horizontalPadding, msgRect.height );
                DrawTextBoxed(font, messages[message].text, textRect, font.baseSize, 1, true, WHITE);//TODO: requres special handing from rayjs to display properly

                // Draw the info text below the main message
                let size = messages[message].text.length;
                let length = GetCodepointCount(messages[message].text);
                const info = TextFormat("%s %u characters %i bytes", messages[message].language, length, size);
                sz = MeasureTextEx(GetFontDefault(), info, 10, 1);
                
                DrawText(info, Math.floor(textRect.x + textRect.width - sz.x), Math.floor(msgRect.y + msgRect.height - sz.y - 2), 10, RAYWHITE);
            }
            //------------------------------------------------------------------------------

            // Draw the info text
            DrawText("These emojis have something to tell you, click each to find out!", (screenWidth - 650)/2, screenHeight - 40, 20, GRAY);
            DrawText("Each emoji is a unicode character from a font, not a texture... Press [SPACEBAR] to refresh", (screenWidth - 484)/2, screenHeight - 16, 10, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadFont(fontDefault);    // Unload font resource
    UnloadFont(fontAsian);      // Unload font resource
    UnloadFont(fontEmoji);      // Unload font resource

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}