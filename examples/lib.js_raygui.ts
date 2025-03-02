interface GuiStyleProp {
}
declare var GuiStyleProp: {
    prototype: GuiStyleProp;
}
/** undefined */
declare function GuiEnable(): void;
/** undefined */
declare function GuiDisable(): void;
/** undefined */
declare function GuiLock(): void;
/** undefined */
declare function GuiUnlock(): void;
/** undefined */
declare function GuiIsLocked(): boolean;
/** undefined */
declare function GuiSetAlpha(alpha: number): void;
/** undefined */
declare function GuiSetState(state: number): void;
/** undefined */
declare function GuiGetState(): number;
/** undefined */
declare function GuiSetFont(font: Font): void;
/** undefined */
declare function GuiGetFont(): Font;
/** undefined */
declare function GuiSetStyle(control: number, property: number, value: number): void;
/** undefined */
declare function GuiGetStyle(control: number, property: number): number;
/** undefined */
declare function GuiLoadStyle(fileName: string | undefined | null): void;
/** undefined */
declare function GuiLoadStyleDefault(): void;
/** undefined */
declare function GuiEnableTooltip(): void;
/** undefined */
declare function GuiDisableTooltip(): void;
/** undefined */
declare function GuiSetTooltip(tooltip: string | undefined | null): void;
/** undefined */
declare function GuiIconText(iconId: number, text: string | undefined | null): string | undefined | null;
/** undefined */
declare function GuiSetIconScale(scale: number): void;
/** undefined */
declare function GuiDrawIcon(iconId: number, posX: number, posY: number, pixelSize: number, color: Color): void;
/** undefined */
declare function GuiWindowBox(bounds: Rectangle, title: string | undefined | null): number;
/** undefined */
declare function GuiGroupBox(bounds: Rectangle, text: string | undefined | null): number;
/** undefined */
declare function GuiLine(bounds: Rectangle, text: string | undefined | null): number;
/** undefined */
declare function GuiPanel(bounds: Rectangle, text: string | undefined | null): number;
/** undefined */
declare function GuiScrollPanel(bounds: Rectangle, text: string | undefined | null, content: Rectangle, scroll: Vector2 &, view: Rectangle &): number;
/** undefined */
declare function GuiLabel(bounds: Rectangle, text: string | undefined | null): number;
/** undefined */
declare function GuiButton(bounds: Rectangle, text: string | undefined | null): number;
/** undefined */
declare function GuiLabelButton(bounds: Rectangle, text: string | undefined | null): number;
/** undefined */
declare function GuiToggle(bounds: Rectangle, text: string | undefined | null, active: bool &): number;
/** undefined */
declare function GuiToggleGroup(bounds: Rectangle, text: string | undefined | null, active: int &): number;
/** undefined */
declare function GuiToggleSlider(bounds: Rectangle, text: string | undefined | null, active: int &): number;
/** undefined */
declare function GuiCheckBox(bounds: Rectangle, text: string | undefined | null, checked: bool &): number;
/** undefined */
declare function GuiComboBox(bounds: Rectangle, text: string | undefined | null, active: int &): number;
/** undefined */
declare function GuiDropdownBox(bounds: Rectangle, text: string | undefined | null, active: int &, editMode: boolean): number;
/** undefined */
declare function GuiSpinner(bounds: Rectangle, text: string | undefined | null, value: int &, minValue: number, maxValue: number, editMode: boolean): number;
/** undefined */
declare function GuiValueBox(bounds: Rectangle, text: string | undefined | null, value: int &, minValue: number, maxValue: number, editMode: boolean): number;
/** undefined */
declare function GuiValueBoxFloat(bounds: Rectangle, text: string | undefined | null, textValue: string | undefined | null, value: float &, editMode: boolean): number;
/** undefined */
declare function GuiTextBox(bounds: Rectangle, text: string | undefined | null, textSize: number, editMode: boolean): number;
/** undefined */
declare function GuiSlider(bounds: Rectangle, textLeft: string | undefined | null, textRight: string | undefined | null, value: float &, minValue: number, maxValue: number): number;
/** undefined */
declare function GuiSliderBar(bounds: Rectangle, textLeft: string | undefined | null, textRight: string | undefined | null, value: float &, minValue: number, maxValue: number): number;
/** undefined */
declare function GuiProgressBar(bounds: Rectangle, textLeft: string | undefined | null, textRight: string | undefined | null, value: float &, minValue: number, maxValue: number): number;
/** undefined */
declare function GuiStatusBar(bounds: Rectangle, text: string | undefined | null): number;
/** undefined */
declare function GuiDummyRec(bounds: Rectangle, text: string | undefined | null): number;
/** undefined */
declare function GuiGrid(bounds: Rectangle, text: string | undefined | null, spacing: number, subdivs: number, mouseCell: Vector2 &): number;
/** undefined */
declare function GuiListView(bounds: Rectangle, text: string | undefined | null, scrollIndex: int &, active: int &): number;
/** undefined */
declare function GuiListViewEx(bounds: Rectangle, text: char *, count: number, scrollIndex: int &, active: int &, focus: int): number;
/** undefined */
declare function GuiMessageBox(bounds: Rectangle, title: string | undefined | null, message: string | undefined | null, buttons: string | undefined | null): number;
/** undefined */
declare function GuiTextInputBox(bounds: Rectangle, title: string | undefined | null, message: string | undefined | null, buttons: string | undefined | null, text: string | undefined | null, textMaxSize: number, secretViewActive: bool): number;
/** undefined */
declare function GuiColorPicker(bounds: Rectangle, text: string | undefined | null, color: Color &): number;
/** undefined */
declare function GuiColorPanel(bounds: Rectangle, text: string | undefined | null, color: Color &): number;
/** undefined */
declare function GuiColorBarAlpha(bounds: Rectangle, text: string | undefined | null, alpha: float &): number;
/** undefined */
declare function GuiColorBarHue(bounds: Rectangle, text: string | undefined | null, value: float &): number;
/** undefined */
declare function GuiColorPickerHSV(bounds: Rectangle, text: string | undefined | null, colorHsv: Vector3 &): number;
/** undefined */
declare function GuiColorPanelHSV(bounds: Rectangle, text: string | undefined | null, colorHsv: Vector3 &): number;
/**  */
declare var STATE_NORMAL: number;
/**  */
declare var STATE_FOCUSED: number;
/**  */
declare var STATE_PRESSED: number;
/**  */
declare var STATE_DISABLED: number;
/**  */
declare var TEXT_ALIGN_LEFT: number;
/**  */
declare var TEXT_ALIGN_CENTER: number;
/**  */
declare var TEXT_ALIGN_RIGHT: number;
/**  */
declare var TEXT_ALIGN_TOP: number;
/**  */
declare var TEXT_ALIGN_MIDDLE: number;
/**  */
declare var TEXT_ALIGN_BOTTOM: number;
/**  */
declare var TEXT_WRAP_NONE: number;
/**  */
declare var TEXT_WRAP_CHAR: number;
/**  */
declare var TEXT_WRAP_WORD: number;
/**  */
declare var DEFAULT: number;
/**  */
declare var LABEL: number;
/**  */
declare var BUTTON: number;
/**  */
declare var TOGGLE: number;
/**  */
declare var SLIDER: number;
/**  */
declare var PROGRESSBAR: number;
/**  */
declare var CHECKBOX: number;
/**  */
declare var COMBOBOX: number;
/**  */
declare var DROPDOWNBOX: number;
/**  */
declare var TEXTBOX: number;
/**  */
declare var VALUEBOX: number;
/**  */
declare var CONTROL11: number;
/**  */
declare var LISTVIEW: number;
/**  */
declare var COLORPICKER: number;
/**  */
declare var SCROLLBAR: number;
/**  */
declare var STATUSBAR: number;
/**  */
declare var BORDER_COLOR_NORMAL: number;
/**  */
declare var BASE_COLOR_NORMAL: number;
/**  */
declare var TEXT_COLOR_NORMAL: number;
/**  */
declare var BORDER_COLOR_FOCUSED: number;
/**  */
declare var BASE_COLOR_FOCUSED: number;
/**  */
declare var TEXT_COLOR_FOCUSED: number;
/**  */
declare var BORDER_COLOR_PRESSED: number;
/**  */
declare var BASE_COLOR_PRESSED: number;
/**  */
declare var TEXT_COLOR_PRESSED: number;
/**  */
declare var BORDER_COLOR_DISABLED: number;
/**  */
declare var BASE_COLOR_DISABLED: number;
/**  */
declare var TEXT_COLOR_DISABLED: number;
/**  */
declare var BORDER_WIDTH: number;
/**  */
declare var TEXT_PADDING: number;
/**  */
declare var TEXT_ALIGNMENT: number;
/**  */
declare var TEXT_SIZE: number;
/**  */
declare var TEXT_SPACING: number;
/**  */
declare var LINE_COLOR: number;
/**  */
declare var BACKGROUND_COLOR: number;
/**  */
declare var TEXT_LINE_SPACING: number;
/**  */
declare var TEXT_ALIGNMENT_VERTICAL: number;
/**  */
declare var TEXT_WRAP_MODE: number;
/**  */
declare var GROUP_PADDING: number;
/**  */
declare var SLIDER_WIDTH: number;
/**  */
declare var SLIDER_PADDING: number;
/**  */
declare var PROGRESS_PADDING: number;
/**  */
declare var ARROWS_SIZE: number;
/**  */
declare var ARROWS_VISIBLE: number;
/**  */
declare var SCROLL_SLIDER_PADDING: number;
/**  */
declare var SCROLL_SLIDER_SIZE: number;
/**  */
declare var SCROLL_PADDING: number;
/**  */
declare var SCROLL_SPEED: number;
/**  */
declare var CHECK_PADDING: number;
/**  */
declare var COMBO_BUTTON_WIDTH: number;
/**  */
declare var COMBO_BUTTON_SPACING: number;
/**  */
declare var ARROW_PADDING: number;
/**  */
declare var DROPDOWN_ITEMS_SPACING: number;
/**  */
declare var DROPDOWN_ARROW_HIDDEN: number;
/**  */
declare var DROPDOWN_ROLL_UP: number;
/**  */
declare var TEXT_READONLY: number;
/**  */
declare var SPINNER_BUTTON_WIDTH: number;
/**  */
declare var SPINNER_BUTTON_SPACING: number;
/**  */
declare var LIST_ITEMS_HEIGHT: number;
/**  */
declare var LIST_ITEMS_SPACING: number;
/**  */
declare var SCROLLBAR_WIDTH: number;
/**  */
declare var SCROLLBAR_SIDE: number;
/**  */
declare var LIST_ITEMS_BORDER_NORMAL: number;
/**  */
declare var LIST_ITEMS_BORDER_WIDTH: number;
/**  */
declare var COLOR_SELECTOR_SIZE: number;
/**  */
declare var HUEBAR_WIDTH: number;
/**  */
declare var HUEBAR_PADDING: number;
/**  */
declare var HUEBAR_SELECTOR_HEIGHT: number;
/**  */
declare var HUEBAR_SELECTOR_OVERFLOW: number;
/**  */
declare var ICON_NONE: number;
/**  */
declare var ICON_FOLDER_FILE_OPEN: number;
/**  */
declare var ICON_FILE_SAVE_CLASSIC: number;
/**  */
declare var ICON_FOLDER_OPEN: number;
/**  */
declare var ICON_FOLDER_SAVE: number;
/**  */
declare var ICON_FILE_OPEN: number;
/**  */
declare var ICON_FILE_SAVE: number;
/**  */
declare var ICON_FILE_EXPORT: number;
/**  */
declare var ICON_FILE_ADD: number;
/**  */
declare var ICON_FILE_DELETE: number;
/**  */
declare var ICON_FILETYPE_TEXT: number;
/**  */
declare var ICON_FILETYPE_AUDIO: number;
/**  */
declare var ICON_FILETYPE_IMAGE: number;
/**  */
declare var ICON_FILETYPE_PLAY: number;
/**  */
declare var ICON_FILETYPE_VIDEO: number;
/**  */
declare var ICON_FILETYPE_INFO: number;
/**  */
declare var ICON_FILE_COPY: number;
/**  */
declare var ICON_FILE_CUT: number;
/**  */
declare var ICON_FILE_PASTE: number;
/**  */
declare var ICON_CURSOR_HAND: number;
/**  */
declare var ICON_CURSOR_POINTER: number;
/**  */
declare var ICON_CURSOR_CLASSIC: number;
/**  */
declare var ICON_PENCIL: number;
/**  */
declare var ICON_PENCIL_BIG: number;
/**  */
declare var ICON_BRUSH_CLASSIC: number;
/**  */
declare var ICON_BRUSH_PAINTER: number;
/**  */
declare var ICON_WATER_DROP: number;
/**  */
declare var ICON_COLOR_PICKER: number;
/**  */
declare var ICON_RUBBER: number;
/**  */
declare var ICON_COLOR_BUCKET: number;
/**  */
declare var ICON_TEXT_T: number;
/**  */
declare var ICON_TEXT_A: number;
/**  */
declare var ICON_SCALE: number;
/**  */
declare var ICON_RESIZE: number;
/**  */
declare var ICON_FILTER_POINT: number;
/**  */
declare var ICON_FILTER_BILINEAR: number;
/**  */
declare var ICON_CROP: number;
/**  */
declare var ICON_CROP_ALPHA: number;
/**  */
declare var ICON_SQUARE_TOGGLE: number;
/**  */
declare var ICON_SYMMETRY: number;
/**  */
declare var ICON_SYMMETRY_HORIZONTAL: number;
/**  */
declare var ICON_SYMMETRY_VERTICAL: number;
/**  */
declare var ICON_LENS: number;
/**  */
declare var ICON_LENS_BIG: number;
/**  */
declare var ICON_EYE_ON: number;
/**  */
declare var ICON_EYE_OFF: number;
/**  */
declare var ICON_FILTER_TOP: number;
/**  */
declare var ICON_FILTER: number;
/**  */
declare var ICON_TARGET_POINT: number;
/**  */
declare var ICON_TARGET_SMALL: number;
/**  */
declare var ICON_TARGET_BIG: number;
/**  */
declare var ICON_TARGET_MOVE: number;
/**  */
declare var ICON_CURSOR_MOVE: number;
/**  */
declare var ICON_CURSOR_SCALE: number;
/**  */
declare var ICON_CURSOR_SCALE_RIGHT: number;
/**  */
declare var ICON_CURSOR_SCALE_LEFT: number;
/**  */
declare var ICON_UNDO: number;
/**  */
declare var ICON_REDO: number;
/**  */
declare var ICON_REREDO: number;
/**  */
declare var ICON_MUTATE: number;
/**  */
declare var ICON_ROTATE: number;
/**  */
declare var ICON_REPEAT: number;
/**  */
declare var ICON_SHUFFLE: number;
/**  */
declare var ICON_EMPTYBOX: number;
/**  */
declare var ICON_TARGET: number;
/**  */
declare var ICON_TARGET_SMALL_FILL: number;
/**  */
declare var ICON_TARGET_BIG_FILL: number;
/**  */
declare var ICON_TARGET_MOVE_FILL: number;
/**  */
declare var ICON_CURSOR_MOVE_FILL: number;
/**  */
declare var ICON_CURSOR_SCALE_FILL: number;
/**  */
declare var ICON_CURSOR_SCALE_RIGHT_FILL: number;
/**  */
declare var ICON_CURSOR_SCALE_LEFT_FILL: number;
/**  */
declare var ICON_UNDO_FILL: number;
/**  */
declare var ICON_REDO_FILL: number;
/**  */
declare var ICON_REREDO_FILL: number;
/**  */
declare var ICON_MUTATE_FILL: number;
/**  */
declare var ICON_ROTATE_FILL: number;
/**  */
declare var ICON_REPEAT_FILL: number;
/**  */
declare var ICON_SHUFFLE_FILL: number;
/**  */
declare var ICON_EMPTYBOX_SMALL: number;
/**  */
declare var ICON_BOX: number;
/**  */
declare var ICON_BOX_TOP: number;
/**  */
declare var ICON_BOX_TOP_RIGHT: number;
/**  */
declare var ICON_BOX_RIGHT: number;
/**  */
declare var ICON_BOX_BOTTOM_RIGHT: number;
/**  */
declare var ICON_BOX_BOTTOM: number;
/**  */
declare var ICON_BOX_BOTTOM_LEFT: number;
/**  */
declare var ICON_BOX_LEFT: number;
/**  */
declare var ICON_BOX_TOP_LEFT: number;
/**  */
declare var ICON_BOX_CENTER: number;
/**  */
declare var ICON_BOX_CIRCLE_MASK: number;
/**  */
declare var ICON_POT: number;
/**  */
declare var ICON_ALPHA_MULTIPLY: number;
/**  */
declare var ICON_ALPHA_CLEAR: number;
/**  */
declare var ICON_DITHERING: number;
/**  */
declare var ICON_MIPMAPS: number;
/**  */
declare var ICON_BOX_GRID: number;
/**  */
declare var ICON_GRID: number;
/**  */
declare var ICON_BOX_CORNERS_SMALL: number;
/**  */
declare var ICON_BOX_CORNERS_BIG: number;
/**  */
declare var ICON_FOUR_BOXES: number;
/**  */
declare var ICON_GRID_FILL: number;
/**  */
declare var ICON_BOX_MULTISIZE: number;
/**  */
declare var ICON_ZOOM_SMALL: number;
/**  */
declare var ICON_ZOOM_MEDIUM: number;
/**  */
declare var ICON_ZOOM_BIG: number;
/**  */
declare var ICON_ZOOM_ALL: number;
/**  */
declare var ICON_ZOOM_CENTER: number;
/**  */
declare var ICON_BOX_DOTS_SMALL: number;
/**  */
declare var ICON_BOX_DOTS_BIG: number;
/**  */
declare var ICON_BOX_CONCENTRIC: number;
/**  */
declare var ICON_BOX_GRID_BIG: number;
/**  */
declare var ICON_OK_TICK: number;
/**  */
declare var ICON_CROSS: number;
/**  */
declare var ICON_ARROW_LEFT: number;
/**  */
declare var ICON_ARROW_RIGHT: number;
/**  */
declare var ICON_ARROW_DOWN: number;
/**  */
declare var ICON_ARROW_UP: number;
/**  */
declare var ICON_ARROW_LEFT_FILL: number;
/**  */
declare var ICON_ARROW_RIGHT_FILL: number;
/**  */
declare var ICON_ARROW_DOWN_FILL: number;
/**  */
declare var ICON_ARROW_UP_FILL: number;
/**  */
declare var ICON_AUDIO: number;
/**  */
declare var ICON_FX: number;
/**  */
declare var ICON_WAVE: number;
/**  */
declare var ICON_WAVE_SINUS: number;
/**  */
declare var ICON_WAVE_SQUARE: number;
/**  */
declare var ICON_WAVE_TRIANGULAR: number;
/**  */
declare var ICON_CROSS_SMALL: number;
/**  */
declare var ICON_PLAYER_PREVIOUS: number;
/**  */
declare var ICON_PLAYER_PLAY_BACK: number;
/**  */
declare var ICON_PLAYER_PLAY: number;
/**  */
declare var ICON_PLAYER_PAUSE: number;
/**  */
declare var ICON_PLAYER_STOP: number;
/**  */
declare var ICON_PLAYER_NEXT: number;
/**  */
declare var ICON_PLAYER_RECORD: number;
/**  */
declare var ICON_MAGNET: number;
/**  */
declare var ICON_LOCK_CLOSE: number;
/**  */
declare var ICON_LOCK_OPEN: number;
/**  */
declare var ICON_CLOCK: number;
/**  */
declare var ICON_TOOLS: number;
/**  */
declare var ICON_GEAR: number;
/**  */
declare var ICON_GEAR_BIG: number;
/**  */
declare var ICON_BIN: number;
/**  */
declare var ICON_HAND_POINTER: number;
/**  */
declare var ICON_LASER: number;
/**  */
declare var ICON_COIN: number;
/**  */
declare var ICON_EXPLOSION: number;
/**  */
declare var ICON_1UP: number;
/**  */
declare var ICON_PLAYER: number;
/**  */
declare var ICON_PLAYER_JUMP: number;
/**  */
declare var ICON_KEY: number;
/**  */
declare var ICON_DEMON: number;
/**  */
declare var ICON_TEXT_POPUP: number;
/**  */
declare var ICON_GEAR_EX: number;
/**  */
declare var ICON_CRACK: number;
/**  */
declare var ICON_CRACK_POINTS: number;
/**  */
declare var ICON_STAR: number;
/**  */
declare var ICON_DOOR: number;
/**  */
declare var ICON_EXIT: number;
/**  */
declare var ICON_MODE_2D: number;
/**  */
declare var ICON_MODE_3D: number;
/**  */
declare var ICON_CUBE: number;
/**  */
declare var ICON_CUBE_FACE_TOP: number;
/**  */
declare var ICON_CUBE_FACE_LEFT: number;
/**  */
declare var ICON_CUBE_FACE_FRONT: number;
/**  */
declare var ICON_CUBE_FACE_BOTTOM: number;
/**  */
declare var ICON_CUBE_FACE_RIGHT: number;
/**  */
declare var ICON_CUBE_FACE_BACK: number;
/**  */
declare var ICON_CAMERA: number;
/**  */
declare var ICON_SPECIAL: number;
/**  */
declare var ICON_LINK_NET: number;
/**  */
declare var ICON_LINK_BOXES: number;
/**  */
declare var ICON_LINK_MULTI: number;
/**  */
declare var ICON_LINK: number;
/**  */
declare var ICON_LINK_BROKE: number;
/**  */
declare var ICON_TEXT_NOTES: number;
/**  */
declare var ICON_NOTEBOOK: number;
/**  */
declare var ICON_SUITCASE: number;
/**  */
declare var ICON_SUITCASE_ZIP: number;
/**  */
declare var ICON_MAILBOX: number;
/**  */
declare var ICON_MONITOR: number;
/**  */
declare var ICON_PRINTER: number;
/**  */
declare var ICON_PHOTO_CAMERA: number;
/**  */
declare var ICON_PHOTO_CAMERA_FLASH: number;
/**  */
declare var ICON_HOUSE: number;
/**  */
declare var ICON_HEART: number;
/**  */
declare var ICON_CORNER: number;
/**  */
declare var ICON_VERTICAL_BARS: number;
/**  */
declare var ICON_VERTICAL_BARS_FILL: number;
/**  */
declare var ICON_LIFE_BARS: number;
/**  */
declare var ICON_INFO: number;
/**  */
declare var ICON_CROSSLINE: number;
/**  */
declare var ICON_HELP: number;
/**  */
declare var ICON_FILETYPE_ALPHA: number;
/**  */
declare var ICON_FILETYPE_HOME: number;
/**  */
declare var ICON_LAYERS_VISIBLE: number;
/**  */
declare var ICON_LAYERS: number;
/**  */
declare var ICON_WINDOW: number;
/**  */
declare var ICON_HIDPI: number;
/**  */
declare var ICON_FILETYPE_BINARY: number;
/**  */
declare var ICON_HEX: number;
/**  */
declare var ICON_SHIELD: number;
/**  */
declare var ICON_FILE_NEW: number;
/**  */
declare var ICON_FOLDER_ADD: number;
/**  */
declare var ICON_ALARM: number;
/**  */
declare var ICON_CPU: number;
/**  */
declare var ICON_ROM: number;
/**  */
declare var ICON_STEP_OVER: number;
/**  */
declare var ICON_STEP_INTO: number;
/**  */
declare var ICON_STEP_OUT: number;
/**  */
declare var ICON_RESTART: number;
/**  */
declare var ICON_BREAKPOINT_ON: number;
/**  */
declare var ICON_BREAKPOINT_OFF: number;
/**  */
declare var ICON_BURGER_MENU: number;
/**  */
declare var ICON_CASE_SENSITIVE: number;
/**  */
declare var ICON_REG_EXP: number;
/**  */
declare var ICON_FOLDER: number;
/**  */
declare var ICON_FILE: number;
/**  */
declare var ICON_SAND_TIMER: number;
/**  */
declare var ICON_WARNING: number;
/**  */
declare var ICON_HELP_BOX: number;
/**  */
declare var ICON_INFO_BOX: number;
/**  */
declare var ICON_PRIORITY: number;
/**  */
declare var ICON_LAYERS_ISO: number;
/**  */
declare var ICON_LAYERS2: number;
/**  */
declare var ICON_MLAYERS: number;
/**  */
declare var ICON_MAPS: number;
/**  */
declare var ICON_HOT: number;
/**  */
declare var ICON_229: number;
/**  */
declare var ICON_230: number;
/**  */
declare var ICON_231: number;
/**  */
declare var ICON_232: number;
/**  */
declare var ICON_233: number;
/**  */
declare var ICON_234: number;
/**  */
declare var ICON_235: number;
/**  */
declare var ICON_236: number;
/**  */
declare var ICON_237: number;
/**  */
declare var ICON_238: number;
/**  */
declare var ICON_239: number;
/**  */
declare var ICON_240: number;
/**  */
declare var ICON_241: number;
/**  */
declare var ICON_242: number;
/**  */
declare var ICON_243: number;
/**  */
declare var ICON_244: number;
/**  */
declare var ICON_245: number;
/**  */
declare var ICON_246: number;
/**  */
declare var ICON_247: number;
/**  */
declare var ICON_248: number;
/**  */
declare var ICON_249: number;
/**  */
declare var ICON_250: number;
/**  */
declare var ICON_251: number;
/**  */
declare var ICON_252: number;
/**  */
declare var ICON_253: number;
/**  */
declare var ICON_254: number;
/**  */
declare var ICON_255: number;
/**  */
declare var RAYGUI_VERSION_MAJOR: number;
/**  */
declare var RAYGUI_VERSION_MINOR: number;
/**  */
declare var RAYGUI_VERSION_PATCH: number;
/**  */
declare var SCROLLBAR_LEFT_SIDE: number;
/**  */
declare var SCROLLBAR_RIGHT_SIDE: number;
