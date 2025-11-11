/*******************************************************************************************
*
*   Window File Dialog v1.2 - Modal file dialog to open/save files
*
*   MODULE USAGE:
*       #define GUI_WINDOW_FILE_DIALOG_IMPLEMENTATION
*       #include "gui_window_file_dialog.h"
*
*       INIT: GuiWindowFileDialogState state = GuiInitWindowFileDialog();
*       DRAW: GuiWindowFileDialog(&state);
*
*   NOTE: This module depends on some raylib file system functions:
*       - LoadDirectoryFiles()
*       - UnloadDirectoryFiles()
*       - GetWorkingDirectory()
*       - DirectoryExists()
*       - FileExists()
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2019-2024 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

import * as os from "qjs:os";
import {BACKGROUND_COLOR,
    BASE_COLOR_DISABLED,
    BORDER_COLOR_DISABLED, BORDER_WIDTH, DEFAULT,
    GuiButton,
    GuiComboBox, GuiGetStyle,
    GuiLabel,
    GuiListViewEx, GuiSetStyle, GuiTextBox, GuiWindowBox, LISTVIEW, LIST_ITEMS_HEIGHT,
    SCROLLBAR, SCROLLBAR_WIDTH, SLIDER_WIDTH, TEXT_ALIGNMENT,
    TEXT_ALIGN_LEFT, TEXT_COLOR_DISABLED,
    TEXT_COLOR_FOCUSED,
    TEXT_COLOR_NORMAL, TEXT_COLOR_PRESSED } from "rayjs:raygui";
import {CheckCollisionPointRec, DirectoryExists,
    DrawRectangleLinesEx,
    DrawRectangleRec, Fade, FileExists, GetColor, GetDirectoryPath, GetFileName, GetMousePosition,
    GetMouseWheelMove, GetPrevDirectoryPath, GetScreenHeight, GetScreenWidth,
    GetWorkingDirectory,
    IsFileExtension,
    IsMouseButtonPressed,
    IsMouseButtonReleased,
    IsPathFile,
    LoadDirectoryFilesEx,
    MOUSE_LEFT_BUTTON, Rectangle, TextFormat, TextIsEqual, Vector2 } from "rayjs:raylib";

/***********************************************************************************
*
*   GUI_WINDOW_FILE_DIALOG IMPLEMENTATION
*
************************************************************************************/

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
const MAX_DIRECTORY_FILES = 2048;
const MAX_ICON_PATH_LENGTH = 512;
let PATH_SEPERATOR = "/";
if(os.platform == "win32"){
    PATH_SEPERATOR = "\\";
}

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
var dirFilesIcons = null;      // Path string + icon (for fancy drawing)

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
export function InitGuiWindowFileDialog(initPath) {
    let state = {
        windowActive: false,
        windowBounds: new Rectangle( GetScreenWidth()/2 - 440/2, GetScreenHeight()/2 - 310/2, 440, 310 ),
        panOffset: new Vector2( 0, 0 ),
        dragMode: false,
        supportDrag: true,

        // UI variables
        dirPathEditMode: false,
        dirPathText: "",
        filesListScrollIndex: 0,
        filesListEditMode: false,
        filesListActive: -1,
        prevFilesListActive: -1,

        fileNameEditMode: false,
        fileNameText: "",
        SelectFilePressed: false,
        CancelFilePressed: false,
        fileTypeActive: 0,
        itemFocused: 0,

        // Custom state variables
        dirFiles: null,
        filterExt: "",
        dirPathTextCopy: "",
        fileNameTextCopy: "",
        saveFileMode: false
    };

    // Custom variables initialization
    if (initPath && DirectoryExists(initPath)) {
        state.dirPathText = initPath;
    } else if (initPath && FileExists(initPath)) {
        state.dirPathText = GetDirectoryPath(initPath);
        state.fileNameText = GetFileName(initPath);
    }
    else {
        state.dirPathText = GetWorkingDirectory();
    }
    state.fileNameTextCopy = state.fileNameText;

    return state;
}

// List View control for files info with extended parameters
function GuiListViewFiles(bounds, files, count, focus=[], scrollIndex=[], active=[]) {
    let result = 0;
    let state = guiState;
    let itemFocused = (focus.length==0)? -1 : focus[0];
    let itemSelected = active[0];

    // Check if we need a scroll bar
    let useScrollBar = false;
    // @ts-ignore
    if ((GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING))*count > bounds.height) useScrollBar = true;

    // Define base item rectangle [0]
    let itemBounds = new Rectangle();
    itemBounds.x = bounds.x + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING);
    itemBounds.y = bounds.y + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING) + GuiGetStyle(DEFAULT, BORDER_WIDTH);
    itemBounds.width = bounds.width - 2*GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING) - GuiGetStyle(DEFAULT, BORDER_WIDTH);
    itemBounds.height = GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
    if (useScrollBar) itemBounds.width -= GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH);

    // Get items on the list
    let visibleItems = bounds.height/(GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING));
    if (visibleItems > count) visibleItems = count;

    let startIndex = (scrollIndex.length==0)? 0 : scrollIndex[0];
    if ((startIndex < 0) || (startIndex > (count - visibleItems))) startIndex = 0;
    let endIndex = startIndex + visibleItems;

    // Update control
    //--------------------------------------------------------------------
    if ((state != GUI_STATE_DISABLED) && !guiLocked) {
        let mousePoint = GetMousePosition();

        // Check mouse inside list view
        if (CheckCollisionPointRec(mousePoint, bounds)) {
            state = GUI_STATE_FOCUSED;

            // Check focused and selected item
            for (let i = 0; i < visibleItems; i++) {
                if (CheckCollisionPointRec(mousePoint, itemBounds)) {
                    itemFocused = startIndex + i;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) itemSelected = startIndex + i;
                    break;
                }

                // Update item rectangle y position for next item
                itemBounds.y += (GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING));
            }

            if (useScrollBar) {
                let wheelMove = GetMouseWheelMove();
                startIndex -= wheelMove;

                if (startIndex < 0) startIndex = 0;
                else if (startIndex > (count - visibleItems)) startIndex = count - visibleItems;

                endIndex = startIndex + visibleItems;
                if (endIndex > count) endIndex = count;
            }
        } else {
            itemFocused = -1;
        }

        // Reset item rectangle y to [0]
        itemBounds.y = bounds.y + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING) + GuiGetStyle(DEFAULT, BORDER_WIDTH);
    }
    //--------------------------------------------------------------------

    // Draw control
    //--------------------------------------------------------------------
    DrawRectangleRec(bounds, GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));     // Draw background
    DrawRectangleLinesEx(bounds, GuiGetStyle(DEFAULT, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(LISTVIEW, BORDER + state*3)), guiAlpha));

    // TODO: Draw list view header with file sections: icon+name | size | type | modTime

    // Draw visible items
    for (let i = 0; i < visibleItems; i++) {
        if (state == GUI_STATE_DISABLED) {
            if ((startIndex + i) == itemSelected) {
                DrawRectangleRec(itemBounds, Fade(GetColor(GuiGetStyle(LISTVIEW, BASE_COLOR_DISABLED)), guiAlpha));
                DrawRectangleLinesEx(itemBounds, GuiGetStyle(LISTVIEW, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(LISTVIEW, BORDER_COLOR_DISABLED)), guiAlpha));
            }

            // TODO: Draw full file info line: icon+name | size | type | modTime

            GuiDrawText(files[startIndex + i].name, GetTextBounds(DEFAULT, itemBounds), GuiGetStyle(LISTVIEW, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_DISABLED)), guiAlpha));
        } else {
            if ((startIndex + i) == itemSelected) {
                // Draw item selected
                DrawRectangleRec(itemBounds, Fade(GetColor(GuiGetStyle(LISTVIEW, BASE_COLOR_PRESSED)), guiAlpha));
                DrawRectangleLinesEx(itemBounds, GuiGetStyle(LISTVIEW, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(LISTVIEW, BORDER_COLOR_PRESSED)), guiAlpha));

                GuiDrawText(files[startIndex + i].name, GetTextBounds(DEFAULT, itemBounds), GuiGetStyle(LISTVIEW, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_PRESSED)), guiAlpha));
            } else if ((startIndex + i) == itemFocused) {
                // Draw item focused
                DrawRectangleRec(itemBounds, Fade(GetColor(GuiGetStyle(LISTVIEW, BASE_COLOR_FOCUSED)), guiAlpha));
                DrawRectangleLinesEx(itemBounds, GuiGetStyle(LISTVIEW, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(LISTVIEW, BORDER_COLOR_FOCUSED)), guiAlpha));

                GuiDrawText(files[startIndex + i].name, GetTextBounds(DEFAULT, itemBounds), GuiGetStyle(LISTVIEW, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_FOCUSED)), guiAlpha));
            }
            else
            {
                // Draw item normal
                GuiDrawText(files[startIndex + i].name, GetTextBounds(DEFAULT, itemBounds), GuiGetStyle(LISTVIEW, TEXT_ALIGNMENT), Fade(GetColor(GuiGetStyle(LISTVIEW, TEXT_COLOR_NORMAL)), guiAlpha));
            }
        }

        // Update item rectangle y position for next item
        itemBounds.y += (GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT) + GuiGetStyle(LISTVIEW, LIST_ITEMS_PADDING));
    }

    if (useScrollBar) {
        let scrollBarBounds = new Rectangle(
            bounds.x + bounds.width - GuiGetStyle(LISTVIEW, BORDER_WIDTH) - GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH),
            bounds.y + GuiGetStyle(LISTVIEW, BORDER_WIDTH),
            GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH),
            bounds.height - 2*GuiGetStyle(DEFAULT, BORDER_WIDTH)
        );

        // Calculate percentage of visible items and apply same percentage to scrollbar
        let percentVisible = (endIndex - startIndex)/count;
        let sliderSize = bounds.height*percentVisible;

        let prevSliderSize = GuiGetStyle(SCROLLBAR, SLIDER_WIDTH);  // Save default slider size
        let prevScrollSpeed = GuiGetStyle(SCROLLBAR, SCROLL_SPEED); // Save default scroll speed
        GuiSetStyle(SCROLLBAR, SLIDER_WIDTH, sliderSize);           // Change slider size
        GuiSetStyle(SCROLLBAR, SCROLL_SPEED, count - visibleItems); // Change scroll speed

        startIndex = GuiScrollBar(scrollBarBounds, startIndex, 0, count - visibleItems);

        GuiSetStyle(SCROLLBAR, SCROLL_SPEED, prevScrollSpeed); // Reset scroll speed to default
        GuiSetStyle(SCROLLBAR, SLIDER_WIDTH, prevSliderSize);  // Reset slider size to default
    }
    //--------------------------------------------------------------------

    if (focus != null) focus[0] = itemFocused;
    if (scrollIndex != null) scrollIndex[0] = startIndex;

    active[0] = itemSelected;
    return result;
}


// Read files in new path
function ReloadDirectoryFiles(state) {

    state.dirFiles = LoadDirectoryFilesEx(state.dirPathText, (state.filterExt[0] == '\0')? null : state.filterExt, false);
    state.itemFocused = 0;

    // Reset dirFilesIcons memory
    dirFilesIcons = [];

    // Copy paths as icon + fileNames into dirFilesIcons
    for (let i = 0; i < state.dirFiles.length; i++) {
        if (IsPathFile(state.dirFiles[i])) {
            // Path is a file, a file icon for convenience (for some recognized extensions)
            if (IsFileExtension(state.dirFiles[i], ".png;.bmp;.tga;.gif;.jpg;.jpeg;.psd;.hdr;.qoi;.dds;.pkm;.ktx;.pvr;.astc")) {
                dirFilesIcons[i] = TextFormat("#12#%s", GetFileName(state.dirFiles[i]));
            } else if (IsFileExtension(state.dirFiles[i], ".wav;.mp3;.ogg;.flac;.xm;.mod;.it;.wma;.aiff")) {
                dirFilesIcons[i] = TextFormat("#11#%s", GetFileName(state.dirFiles[i]));
            } else if (IsFileExtension(state.dirFiles[i], ".txt;.info;.md;.nfo;.xml;.json;.c;.cpp;.cs;.lua;.py;.glsl;.vs;.fs")) {
                dirFilesIcons[i] = TextFormat("#10#%s", GetFileName(state.dirFiles[i]));
            } else if (IsFileExtension(state.dirFiles[i], ".exe;.bin;.raw;.msi")) {
                dirFilesIcons[i] = TextFormat("#200#%s", GetFileName(state.dirFiles[i]));
            } else {
                dirFilesIcons[i] = TextFormat("#218#%s", GetFileName(state.dirFiles[i]));
            }
        } else {
            // Path is a directory, add a directory icon
            dirFilesIcons[i] = TextFormat("#1#%s", GetFileName(state.dirFiles[i]));
        }
    }
}

// Update and draw file dialog
export function GuiWindowFileDialog( state, USE_CUSTOM_LISTVIEW_FILEINFO = false) {
    if (state.windowActive) {
        // Update window dragging
        //----------------------------------------------------------------------------------------
        if (state.supportDrag) {
            let mousePosition = GetMousePosition();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Window can be dragged from the top window bar
                if (CheckCollisionPointRec(mousePosition, new Rectangle( state.windowBounds.x, state.windowBounds.y, state.windowBounds.width, RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT ))){
                    state.dragMode = true;
                    state.panOffset.x = mousePosition.x - state.windowBounds.x;
                    state.panOffset.y = mousePosition.y - state.windowBounds.y;
                }
            }

            if (state.dragMode) {
                state.windowBounds.x = (mousePosition.x - state.panOffset.x);
                state.windowBounds.y = (mousePosition.y - state.panOffset.y);

                // Check screen limits to avoid moving out of screen
                if (state.windowBounds.x < 0) {
                    state.windowBounds.x = 0;
                } else if (state.windowBounds.x > (GetScreenWidth() - state.windowBounds.width)) {
                    state.windowBounds.x = GetScreenWidth() - state.windowBounds.width
                };

                if (state.windowBounds.y < 0) state.windowBounds.y = 0;
                else if (state.windowBounds.y > (GetScreenHeight() - state.windowBounds.height)) state.windowBounds.y = GetScreenHeight() - state.windowBounds.height;

                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) state.dragMode = false;
            }
        }
        //----------------------------------------------------------------------------------------

        // Load dirFilesIcons and state->dirFiles lazily on windows open
        // NOTE: They are automatically unloaded at fileDialog closing
        //----------------------------------------------------------------------------------------
        if (dirFilesIcons == null) {
            dirFilesIcons = new Array(MAX_DIRECTORY_FILES);    // Max files to read
            for (let i = 0; i < MAX_DIRECTORY_FILES; i++){
                dirFilesIcons[i] = "";
            }
        }

        // Load current directory files
        if (state.dirFiles == null) ReloadDirectoryFiles(state);
        console.log(JSON.stringify([dirFilesIcons]));
        //----------------------------------------------------------------------------------------

        // Draw window and controls
        //----------------------------------------------------------------------------------------
        state.windowActive = !GuiWindowBox(state.windowBounds, "#198# Select File Dialog");

        // Draw previous directory button + logic
        if (GuiButton(new Rectangle( state.windowBounds.x + state.windowBounds.width - 48, state.windowBounds.y + 24 + 12, 40, 24 ), "< ..")) {
            // Move dir path one level up
            state.dirPathText= GetPrevDirectoryPath(state.dirPathText);

            // Reload directory files (frees previous list)
            ReloadDirectoryFiles(state);

            state.filesListActive = -1;
            memset(state.fileNameText, 0, 1024);
            memset(state.fileNameTextCopy, 0, 1024);
        }

        // Draw current directory text box info + path editing logic
        if (GuiTextBox(new Rectangle( state.windowBounds.x + 8, state.windowBounds.y + 24 + 12, state.windowBounds.width - 48 - 16, 24 ), [state.dirPathText], 1024, state.dirPathEditMode)){
            if (state.dirPathEditMode) {
                // Verify if a valid path has been introduced
                if (DirectoryExists(state.dirPathText)) {
                    // Reload directory files (frees previous list)
                    ReloadDirectoryFiles(state);

                    state.dirPathTextCopy= state.dirPathText;
                }
                else state.dirPathText= state.dirPathTextCopy;
            }

            state.dirPathEditMode = !state.dirPathEditMode;
        }

        // List view elements are aligned left
        let prevTextAlignment = GuiGetStyle(LISTVIEW, TEXT_ALIGNMENT);
        let prevElementsHeight = GuiGetStyle(LISTVIEW, LIST_ITEMS_HEIGHT);
        GuiSetStyle(LISTVIEW, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        GuiSetStyle(LISTVIEW, LIST_ITEMS_HEIGHT, 24);
        if(USE_CUSTOM_LISTVIEW_FILEINFO){
            let itemFocused = state.itemFocused;
            let filesListScrollIndex = state.filesListScrollIndex
            state.filesListActive = GuiListViewFiles(new Rectangle( state.position.x + 8, state.position.y + 48 + 20, state.windowBounds.width - 16, state.windowBounds.height - 60 - 16 - 68 ), fileInfo, state.dirFiles.length, itemFocused, filesListScrollIndex, state.filesListActive);
        }else{
            let filesListScrollIndex = [state.filesListScrollIndex];
            let filesListActive = [state.filesListActive];
            let itemFocused = [state.itemFocused];
            console.log(JSON.stringify([dirFilesIcons]));
            GuiListViewEx(new Rectangle( state.windowBounds.x + 8, state.windowBounds.y + 48 + 20, state.windowBounds.width - 16, state.windowBounds.height - 60 - 16 - 68 ),
            [dirFilesIcons], state.dirFiles.length, filesListScrollIndex, filesListActive, itemFocused);
            state.filesListScrollIndex = filesListScrollIndex[0];
            state.filesListActive = filesListActive[0];
            state.itemFocused = itemFocused[0];
        }
        GuiSetStyle(LISTVIEW, TEXT_ALIGNMENT, prevTextAlignment);
        GuiSetStyle(LISTVIEW, LIST_ITEMS_HEIGHT, prevElementsHeight);

        // Check if a path has been selected, if it is a directory, move to that directory (and reload paths)
        if ((state.filesListActive >= 0) && (state.filesListActive != state.prevFilesListActive))
            //&& (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_DPAD_A)))
        {
            state.fileNameText= GetFileName(state.dirFiles[state.filesListActive]);

            if (DirectoryExists(TextFormat("%s/%s", state.dirPathText, state.fileNameText))) {
                if (TextIsEqual(state.fileNameText, "..")) state.dirPathText= GetPrevDirectoryPath(state.dirPathText);
                else state.dirPathText= TextFormat("%s/%s", (state.dirPathText != "/")? "" : state.dirPathText, state.fileNameText);

                state.dirPathTextCopy= state.dirPathText;

                // Reload directory files (frees previous list)
                ReloadDirectoryFiles(state);

                state.dirPathTextCopy= state.dirPathText;

                state.filesListActive = -1;
                state.fileNameText = '';
                state.fileNameTextCopy= state.fileNameText;
            }

            state.prevFilesListActive = state.filesListActive;
        }

        // Draw bottom controls
        //--------------------------------------------------------------------------------------
        GuiLabel(new Rectangle( state.windowBounds.x + 8, state.windowBounds.y + state.windowBounds.height - 68, 60, 24 ), "File name:");
        let fileNameText = [state.fileNameText];
        if (GuiTextBox(new Rectangle( state.windowBounds.x + 72, state.windowBounds.y + state.windowBounds.height - 68, state.windowBounds.width - 184, 24 ), fileNameText, 128, state.fileNameEditMode)) {
            state.fileNameText = fileNameText[0];
            if (state.fileNameText) {
                // Verify if a valid filename has been introduced
                if (FileExists(TextFormat("%s/%s", state.dirPathText, state.fileNameText))) {
                    // Select filename from list view
                    for (let i = 0; i < state.dirFiles.length; i++) {
                        if (TextIsEqual(state.fileNameText, state.dirFiles[i])) {
                            state.filesListActive = i;
                            state.fileNameTextCopy = state.fileNameText;
                            break;
                        }
                    }
                } else if (!state.saveFileMode) {
                    state.fileName = state.fileNameTextCopy;
                }
            }

            state.fileNameEditMode = !state.fileNameEditMode;
        }

        GuiLabel(new Rectangle( state.windowBounds.x + 8, state.windowBounds.y + state.windowBounds.height - 24 - 12, 68, 24 ), "File filter:");
        let fileTypeActive = [state.fileTypeActive];
        GuiComboBox(new Rectangle( state.windowBounds.x + 72, state.windowBounds.y + state.windowBounds.height - 24 - 12, state.windowBounds.width - 184, 24 ), "All files", fileTypeActive);
        state.fileTypeActive = fileTypeActive[0];

        state.SelectFilePressed = GuiButton(new Rectangle( state.windowBounds.x + state.windowBounds.width - 96 - 8, state.windowBounds.y + state.windowBounds.height - 68, 96, 24 ), "Select");

        if (GuiButton(new Rectangle( state.windowBounds.x + state.windowBounds.width - 96 - 8, state.windowBounds.y + state.windowBounds.height - 24 - 12, 96, 24 ), "Cancel")) state.windowActive = false;
        //--------------------------------------------------------------------------------------

        // Exit on file selected
        if (state.SelectFilePressed) state.windowActive = false;

        // File dialog has been closed, free all memory before exit
        if (!state.windowActive) {
            // Free dirFilesIcons memory
            dirFilesIcons = null;

            // Reset state variables
            state.dirFiles = null;
        }
    }
}

// Compare two files from a directory
export function FileCompare(d1, d2, dir) {
    const b1 = DirectoryExists(TextFormat("%s/%s", dir, d1));
    const b2 = DirectoryExists(TextFormat("%s/%s", dir, d2));

    if (b1 && !b2) return -1;
    if (!b1 && b2) return 1;

    if (!FileExists(TextFormat("%s/%s", dir, d1))) return 1;
    if (!FileExists(TextFormat("%s/%s", dir, d2))) return -1;

    return d1 == d2;
}