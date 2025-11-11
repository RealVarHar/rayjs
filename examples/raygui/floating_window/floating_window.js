import {GuiLoadStyleDark} from "../styles/_style_dark.js";
import {BeginDrawing,
    BeginScissorMode, CheckCollisionPointRec,
    ClearBackground,
    CloseWindow,
    DARKGREEN,
    EndDrawing,
    EndScissorMode,
    GetMouseDelta, GetMousePosition,
    GetScreenHeight,
    GetScreenWidth,
    InitWindow, IsMouseButtonPressed, IsMouseButtonReleased, MOUSE_LEFT_BUTTON, Rectangle, SetTargetFPS, Vector2, WHITE, WindowShouldClose } from 'rayjs:raylib';
import {GuiButton, GuiDrawIcon, GuiLabel, GuiScrollPanel, GuiStatusBar, GuiWindowBox } from 'rayjs:raygui';

var window_position = new Vector2( 10, 10 );
var window_size = new Vector2( 200, 400 );
var minimized = [false];
var moving = [false];
var resizing = [false];
var scroll = new Vector2();

var window2_position = new Vector2( 250, 10 );
var window2_size = new Vector2( 200, 400 );
var minimized2 = [false];
var moving2 = [false];
var resizing2 = [false];
var scroll2 = new Vector2();

function GuiWindowFloating(position, size, minimized, moving, resizing, draw_content, content_size, scroll, title) {
    const RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT = 24;
    const RAYGUI_WINDOW_CLOSEBUTTON_SIZE = 18;

    let close_title_size_delta_half = Math.floor((RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - RAYGUI_WINDOW_CLOSEBUTTON_SIZE) / 2);

    // window movement and resize input and collision check
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !moving[0] && !resizing[0]) {
        let mouse_position = GetMousePosition();

        let title_collision_rect = new Rectangle( position.x, position.y, size.x - (RAYGUI_WINDOW_CLOSEBUTTON_SIZE + close_title_size_delta_half), RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT );
        let resize_collision_rect = new Rectangle( position.x + size.x - 20, position.y + size.y - 20, 20, 20 );

        if(CheckCollisionPointRec(mouse_position, title_collision_rect)) {
            moving[0] = true;
        } else if(!minimized[0] && CheckCollisionPointRec(mouse_position, resize_collision_rect)) {
            resizing[0] = true;
        }
    }

    // window movement and resize update
    if(moving[0]) {
        let mouse_delta = GetMouseDelta();
        position.x += mouse_delta.x;
        position.y += mouse_delta.y;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            moving[0] = false;

            // clamp window position keep it inside the application area
            if(position.x < 0) {
                position.x = 0;
            } else if(position.x > GetScreenWidth() - size.x) {
                position.x = GetScreenWidth() - size.x;
            }
            if(position.y < 0) {
                position.y = 0;
            } else if(position.y > GetScreenHeight()) {
                position.y = GetScreenHeight() - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT;
            }
        }

    } else if(resizing[0]) {
        let mouse = GetMousePosition();
        if (mouse.x > position.x)
            size.x = mouse.x - position.x;
        if (mouse.y > position.y)
            size.y = mouse.y - position.y;

        // clamp window size to an arbitrary minimum value and the window size as the maximum
        if(size.x < 100) size.x = 100;
        else if(size.x > GetScreenWidth()) size.x = GetScreenWidth();
        if(size.y < 100) size.y = 100;
        else if(size.y > GetScreenHeight()) size.y = GetScreenHeight();

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            resizing[0] = false;
        }
    }

    // window and content drawing with scissor and scroll area
    if(minimized[0]) {
        GuiStatusBar(new Rectangle( position.x, position.y, size.x, RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT ), title);

        if (GuiButton(
            new Rectangle( position.x + size.x - RAYGUI_WINDOW_CLOSEBUTTON_SIZE - close_title_size_delta_half,
                position.y + close_title_size_delta_half,
                RAYGUI_WINDOW_CLOSEBUTTON_SIZE,
                RAYGUI_WINDOW_CLOSEBUTTON_SIZE ),
                "#120#")) {
            minimized[0] = false;
        }

    } else {
        minimized[0] = GuiWindowBox(new Rectangle( position.x, position.y, size.x, size.y ), title);

        // scissor and draw content within a scroll panel
        if(draw_content != null) {
            let scissor = new Rectangle();
            GuiScrollPanel(new Rectangle( position.x, position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT, size.x, size.y - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT ),
                null, new Rectangle( position.x, position.y, content_size.x, content_size.y ),
                scroll, scissor[0]);

            let require_scissor = size.x < content_size.x || size.y < content_size.y;

            if(require_scissor) {
                BeginScissorMode(scissor.x, scissor.y, scissor.width, scissor.height);
            }

            draw_content(position, scroll);

            if(require_scissor) {
                EndScissorMode();
            }
        }

        // draw the resize button/icon
        GuiDrawIcon(71, position.x + size.x - 20, position.y + size.y - 20, 1, WHITE);
    }
}

function DrawContent(position, scroll) {
    GuiButton(new Rectangle( position.x + 20 + scroll.x, position.y + 50  + scroll.y, 100, 25 ), "Button 1");
    GuiButton(new Rectangle( position.x + 20 + scroll.x, position.y + 100 + scroll.y, 100, 25 ), "Button 2");
    GuiButton(new Rectangle( position.x + 20 + scroll.x, position.y + 150 + scroll.y, 100, 25 ), "Button 3");
    GuiLabel(new Rectangle( position.x + 20 + scroll.x, position.y + 200 + scroll.y, 250, 25 ), "A Label");
    GuiLabel(new Rectangle( position.x + 20 + scroll.x, position.y + 250 + scroll.y, 250, 25 ), "Another Label");
    GuiLabel(new Rectangle( position.x + 20 + scroll.x, position.y + 300 + scroll.y, 250, 25 ), "Yet Another Label");
}

{
    InitWindow(960, 560, "raygui - floating window example");
    SetTargetFPS(60);
    GuiLoadStyleDark();

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(DARKGREEN);
            GuiWindowFloating(window_position, window_size, minimized, moving, resizing, DrawContent, new Vector2( 140, 320 ), scroll, "Movable & Scalable Window");
            GuiWindowFloating(window2_position, window2_size, minimized2, moving2, resizing2, DrawContent, new Vector2( 140, 320 ), scroll2, "Another window");
        EndDrawing();
    }

    CloseWindow();
}
