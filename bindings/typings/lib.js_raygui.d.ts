declare module "rayjs:raygui" {
import type {Font,Color,Rectangle,Vector2,Vector3} from 'rayjs:raylib';
interface GuiStyleProp {
controlId: number,
propertyId: number,
propertyValue: number,
}
var GuiStyleProp: {
prototype: GuiStyleProp
new(controlId?: number, propertyId?: number, propertyValue?: number): GuiStyleProp
}
/** undefined */
function GuiEnable(): void/** undefined */
function GuiDisable(): void/** undefined */
function GuiLock(): void/** undefined */
function GuiUnlock(): void/** undefined */
function GuiIsLocked(): boolean/** undefined */
function GuiSetAlpha(alpha: number): void/** undefined */
function GuiSetState(state: number): void/** undefined */
function GuiGetState(): number/** undefined */
function GuiSetFont(font: Font): void/** undefined */
function GuiGetFont(): Font/** undefined */
function GuiSetStyle(control: number, property: number, value: number): void/** undefined */
function GuiGetStyle(control: number, property: number): number/** undefined */
function GuiLoadStyle(fileName: string): void/** undefined */
function GuiLoadStyleDefault(): void/** undefined */
function GuiEnableTooltip(): void/** undefined */
function GuiDisableTooltip(): void/** undefined */
function GuiSetTooltip(tooltip: string): void/** undefined */
function GuiIconText(iconId: number, text: string): string/** undefined */
function GuiSetIconScale(scale: number): void/** undefined */
function GuiGetIcons(): number[]/** undefined */
function GuiLoadIcons(fileName: string, loadIconsName: boolean): string[]/** undefined */
function GuiDrawIcon(iconId: number, posX: number, posY: number, pixelSize: number, color: Color): void/** undefined */
function GuiGetTextWidth(text: string): number/** undefined */
function GuiWindowBox(bounds: Rectangle, title: string): number/** undefined */
function GuiGroupBox(bounds: Rectangle, text: string): number/** undefined */
function GuiLine(bounds: Rectangle, text: string): number/** undefined */
function GuiPanel(bounds: Rectangle, text: string): number/** undefined */
function GuiTabBar(bounds: Rectangle, text: string[], count: number, active: number | number[]): number/** undefined */
function GuiScrollPanel(bounds: Rectangle, text: string, content: Rectangle, scroll: Vector2, view: Rectangle): number/** undefined */
function GuiLabel(bounds: Rectangle, text: string): number/** undefined */
function GuiButton(bounds: Rectangle, text: string): number/** undefined */
function GuiLabelButton(bounds: Rectangle, text: string): number/** undefined */
function GuiToggle(bounds: Rectangle, text: string, active: boolean | boolean[]): number/** undefined */
function GuiToggleGroup(bounds: Rectangle, text: string, active: number | number[]): number/** undefined */
function GuiToggleSlider(bounds: Rectangle, text: string, active: number | number[]): number/** undefined */
function GuiCheckBox(bounds: Rectangle, text: string, checked: boolean | boolean[]): number/** undefined */
function GuiComboBox(bounds: Rectangle, text: string, active: number | number[]): number/** undefined */
function GuiDropdownBox(bounds: Rectangle, text: string, active: number | number[], editMode: boolean): number/** undefined */
function GuiSpinner(bounds: Rectangle, text: string, value: number[], minValue: number, maxValue: number, editMode: boolean): number/** undefined */
function GuiValueBox(bounds: Rectangle, text: string, value: number[], minValue: number, maxValue: number, editMode: boolean): number/** undefined */
function GuiValueBoxFloat(bounds: Rectangle, text: string, textValue: string, value: number[], editMode: boolean): number/** undefined */
function GuiTextBox(bounds: Rectangle, text: string | string[], textSize: number, editMode: boolean): number/** undefined */
function GuiSlider(bounds: Rectangle, textLeft: string, textRight: string, value: number[], minValue: number, maxValue: number): number/** undefined */
function GuiSliderBar(bounds: Rectangle, textLeft: string, textRight: string, value: number[], minValue: number, maxValue: number): number/** undefined */
function GuiProgressBar(bounds: Rectangle, textLeft: string, textRight: string, value: number[], minValue: number, maxValue: number): number/** undefined */
function GuiStatusBar(bounds: Rectangle, text: string): number/** undefined */
function GuiDummyRec(bounds: Rectangle, text: string): number/** undefined */
function GuiGrid(bounds: Rectangle, text: string, spacing: number, subdivs: number, mouseCell: Vector2): number/** undefined */
function GuiListView(bounds: Rectangle, text: string, scrollIndex: number | number[], active: number | number[]): number/** undefined */
function GuiListViewEx(bounds: Rectangle, text: string[], count: number, scrollIndex: number | number[], active: number | number[], focus: number[]): number/** undefined */
function GuiMessageBox(bounds: Rectangle, title: string, message: string, buttons: string): number/** undefined */
function GuiTextInputBox(bounds: Rectangle, title: string, message: string, buttons: string, text: string, textMaxSize: number, secretViewActive: boolean[]): number/** undefined */
function GuiColorPicker(bounds: Rectangle, text: string, color: Color): number/** undefined */
function GuiColorPanel(bounds: Rectangle, text: string, color: Color): number/** undefined */
function GuiColorBarAlpha(bounds: Rectangle, text: string, alpha: number | number[]): number/** undefined */
function GuiColorBarHue(bounds: Rectangle, text: string, value: number[]): number/** undefined */
function GuiColorPickerHSV(bounds: Rectangle, text: string, colorHsv: Vector3): number/** undefined */
function GuiColorPanelHSV(bounds: Rectangle, text: string, colorHsv: Vector3): number/**  */
var STATE_NORMAL: number/**  */
var STATE_FOCUSED: number/**  */
var STATE_PRESSED: number/**  */
var STATE_DISABLED: number/**  */
var TEXT_ALIGN_LEFT: number/**  */
var TEXT_ALIGN_CENTER: number/**  */
var TEXT_ALIGN_RIGHT: number/**  */
var TEXT_ALIGN_TOP: number/**  */
var TEXT_ALIGN_MIDDLE: number/**  */
var TEXT_ALIGN_BOTTOM: number/**  */
var TEXT_WRAP_NONE: number/**  */
var TEXT_WRAP_CHAR: number/**  */
var TEXT_WRAP_WORD: number/**  */
var DEFAULT: number/**  */
var LABEL: number/**  */
var BUTTON: number/**  */
var TOGGLE: number/**  */
var SLIDER: number/**  */
var PROGRESSBAR: number/**  */
var CHECKBOX: number/**  */
var COMBOBOX: number/**  */
var DROPDOWNBOX: number/**  */
var TEXTBOX: number/**  */
var VALUEBOX: number/**  */
var CONTROL11: number/**  */
var LISTVIEW: number/**  */
var COLORPICKER: number/**  */
var SCROLLBAR: number/**  */
var STATUSBAR: number/**  */
var BORDER_COLOR_NORMAL: number/**  */
var BASE_COLOR_NORMAL: number/**  */
var TEXT_COLOR_NORMAL: number/**  */
var BORDER_COLOR_FOCUSED: number/**  */
var BASE_COLOR_FOCUSED: number/**  */
var TEXT_COLOR_FOCUSED: number/**  */
var BORDER_COLOR_PRESSED: number/**  */
var BASE_COLOR_PRESSED: number/**  */
var TEXT_COLOR_PRESSED: number/**  */
var BORDER_COLOR_DISABLED: number/**  */
var BASE_COLOR_DISABLED: number/**  */
var TEXT_COLOR_DISABLED: number/**  */
var BORDER_WIDTH: number/**  */
var TEXT_PADDING: number/**  */
var TEXT_ALIGNMENT: number/**  */
var TEXT_SIZE: number/**  */
var TEXT_SPACING: number/**  */
var LINE_COLOR: number/**  */
var BACKGROUND_COLOR: number/**  */
var TEXT_LINE_SPACING: number/**  */
var TEXT_ALIGNMENT_VERTICAL: number/**  */
var TEXT_WRAP_MODE: number/**  */
var GROUP_PADDING: number/**  */
var SLIDER_WIDTH: number/**  */
var SLIDER_PADDING: number/**  */
var PROGRESS_PADDING: number/**  */
var ARROWS_SIZE: number/**  */
var ARROWS_VISIBLE: number/**  */
var SCROLL_SLIDER_PADDING: number/**  */
var SCROLL_SLIDER_SIZE: number/**  */
var SCROLL_PADDING: number/**  */
var SCROLL_SPEED: number/**  */
var CHECK_PADDING: number/**  */
var COMBO_BUTTON_WIDTH: number/**  */
var COMBO_BUTTON_SPACING: number/**  */
var ARROW_PADDING: number/**  */
var DROPDOWN_ITEMS_SPACING: number/**  */
var DROPDOWN_ARROW_HIDDEN: number/**  */
var DROPDOWN_ROLL_UP: number/**  */
var TEXT_READONLY: number/**  */
var SPINNER_BUTTON_WIDTH: number/**  */
var SPINNER_BUTTON_SPACING: number/**  */
var LIST_ITEMS_HEIGHT: number/**  */
var LIST_ITEMS_SPACING: number/**  */
var SCROLLBAR_WIDTH: number/**  */
var SCROLLBAR_SIDE: number/**  */
var LIST_ITEMS_BORDER_NORMAL: number/**  */
var LIST_ITEMS_BORDER_WIDTH: number/**  */
var COLOR_SELECTOR_SIZE: number/**  */
var HUEBAR_WIDTH: number/**  */
var HUEBAR_PADDING: number/**  */
var HUEBAR_SELECTOR_HEIGHT: number/**  */
var HUEBAR_SELECTOR_OVERFLOW: number/**  */
var ICON_NONE: number/**  */
var ICON_FOLDER_FILE_OPEN: number/**  */
var ICON_FILE_SAVE_CLASSIC: number/**  */
var ICON_FOLDER_OPEN: number/**  */
var ICON_FOLDER_SAVE: number/**  */
var ICON_FILE_OPEN: number/**  */
var ICON_FILE_SAVE: number/**  */
var ICON_FILE_EXPORT: number/**  */
var ICON_FILE_ADD: number/**  */
var ICON_FILE_DELETE: number/**  */
var ICON_FILETYPE_TEXT: number/**  */
var ICON_FILETYPE_AUDIO: number/**  */
var ICON_FILETYPE_IMAGE: number/**  */
var ICON_FILETYPE_PLAY: number/**  */
var ICON_FILETYPE_VIDEO: number/**  */
var ICON_FILETYPE_INFO: number/**  */
var ICON_FILE_COPY: number/**  */
var ICON_FILE_CUT: number/**  */
var ICON_FILE_PASTE: number/**  */
var ICON_CURSOR_HAND: number/**  */
var ICON_CURSOR_POINTER: number/**  */
var ICON_CURSOR_CLASSIC: number/**  */
var ICON_PENCIL: number/**  */
var ICON_PENCIL_BIG: number/**  */
var ICON_BRUSH_CLASSIC: number/**  */
var ICON_BRUSH_PAINTER: number/**  */
var ICON_WATER_DROP: number/**  */
var ICON_COLOR_PICKER: number/**  */
var ICON_RUBBER: number/**  */
var ICON_COLOR_BUCKET: number/**  */
var ICON_TEXT_T: number/**  */
var ICON_TEXT_A: number/**  */
var ICON_SCALE: number/**  */
var ICON_RESIZE: number/**  */
var ICON_FILTER_POINT: number/**  */
var ICON_FILTER_BILINEAR: number/**  */
var ICON_CROP: number/**  */
var ICON_CROP_ALPHA: number/**  */
var ICON_SQUARE_TOGGLE: number/**  */
var ICON_SYMMETRY: number/**  */
var ICON_SYMMETRY_HORIZONTAL: number/**  */
var ICON_SYMMETRY_VERTICAL: number/**  */
var ICON_LENS: number/**  */
var ICON_LENS_BIG: number/**  */
var ICON_EYE_ON: number/**  */
var ICON_EYE_OFF: number/**  */
var ICON_FILTER_TOP: number/**  */
var ICON_FILTER: number/**  */
var ICON_TARGET_POINT: number/**  */
var ICON_TARGET_SMALL: number/**  */
var ICON_TARGET_BIG: number/**  */
var ICON_TARGET_MOVE: number/**  */
var ICON_CURSOR_MOVE: number/**  */
var ICON_CURSOR_SCALE: number/**  */
var ICON_CURSOR_SCALE_RIGHT: number/**  */
var ICON_CURSOR_SCALE_LEFT: number/**  */
var ICON_UNDO: number/**  */
var ICON_REDO: number/**  */
var ICON_REREDO: number/**  */
var ICON_MUTATE: number/**  */
var ICON_ROTATE: number/**  */
var ICON_REPEAT: number/**  */
var ICON_SHUFFLE: number/**  */
var ICON_EMPTYBOX: number/**  */
var ICON_TARGET: number/**  */
var ICON_TARGET_SMALL_FILL: number/**  */
var ICON_TARGET_BIG_FILL: number/**  */
var ICON_TARGET_MOVE_FILL: number/**  */
var ICON_CURSOR_MOVE_FILL: number/**  */
var ICON_CURSOR_SCALE_FILL: number/**  */
var ICON_CURSOR_SCALE_RIGHT_FILL: number/**  */
var ICON_CURSOR_SCALE_LEFT_FILL: number/**  */
var ICON_UNDO_FILL: number/**  */
var ICON_REDO_FILL: number/**  */
var ICON_REREDO_FILL: number/**  */
var ICON_MUTATE_FILL: number/**  */
var ICON_ROTATE_FILL: number/**  */
var ICON_REPEAT_FILL: number/**  */
var ICON_SHUFFLE_FILL: number/**  */
var ICON_EMPTYBOX_SMALL: number/**  */
var ICON_BOX: number/**  */
var ICON_BOX_TOP: number/**  */
var ICON_BOX_TOP_RIGHT: number/**  */
var ICON_BOX_RIGHT: number/**  */
var ICON_BOX_BOTTOM_RIGHT: number/**  */
var ICON_BOX_BOTTOM: number/**  */
var ICON_BOX_BOTTOM_LEFT: number/**  */
var ICON_BOX_LEFT: number/**  */
var ICON_BOX_TOP_LEFT: number/**  */
var ICON_BOX_CENTER: number/**  */
var ICON_BOX_CIRCLE_MASK: number/**  */
var ICON_POT: number/**  */
var ICON_ALPHA_MULTIPLY: number/**  */
var ICON_ALPHA_CLEAR: number/**  */
var ICON_DITHERING: number/**  */
var ICON_MIPMAPS: number/**  */
var ICON_BOX_GRID: number/**  */
var ICON_GRID: number/**  */
var ICON_BOX_CORNERS_SMALL: number/**  */
var ICON_BOX_CORNERS_BIG: number/**  */
var ICON_FOUR_BOXES: number/**  */
var ICON_GRID_FILL: number/**  */
var ICON_BOX_MULTISIZE: number/**  */
var ICON_ZOOM_SMALL: number/**  */
var ICON_ZOOM_MEDIUM: number/**  */
var ICON_ZOOM_BIG: number/**  */
var ICON_ZOOM_ALL: number/**  */
var ICON_ZOOM_CENTER: number/**  */
var ICON_BOX_DOTS_SMALL: number/**  */
var ICON_BOX_DOTS_BIG: number/**  */
var ICON_BOX_CONCENTRIC: number/**  */
var ICON_BOX_GRID_BIG: number/**  */
var ICON_OK_TICK: number/**  */
var ICON_CROSS: number/**  */
var ICON_ARROW_LEFT: number/**  */
var ICON_ARROW_RIGHT: number/**  */
var ICON_ARROW_DOWN: number/**  */
var ICON_ARROW_UP: number/**  */
var ICON_ARROW_LEFT_FILL: number/**  */
var ICON_ARROW_RIGHT_FILL: number/**  */
var ICON_ARROW_DOWN_FILL: number/**  */
var ICON_ARROW_UP_FILL: number/**  */
var ICON_AUDIO: number/**  */
var ICON_FX: number/**  */
var ICON_WAVE: number/**  */
var ICON_WAVE_SINUS: number/**  */
var ICON_WAVE_SQUARE: number/**  */
var ICON_WAVE_TRIANGULAR: number/**  */
var ICON_CROSS_SMALL: number/**  */
var ICON_PLAYER_PREVIOUS: number/**  */
var ICON_PLAYER_PLAY_BACK: number/**  */
var ICON_PLAYER_PLAY: number/**  */
var ICON_PLAYER_PAUSE: number/**  */
var ICON_PLAYER_STOP: number/**  */
var ICON_PLAYER_NEXT: number/**  */
var ICON_PLAYER_RECORD: number/**  */
var ICON_MAGNET: number/**  */
var ICON_LOCK_CLOSE: number/**  */
var ICON_LOCK_OPEN: number/**  */
var ICON_CLOCK: number/**  */
var ICON_TOOLS: number/**  */
var ICON_GEAR: number/**  */
var ICON_GEAR_BIG: number/**  */
var ICON_BIN: number/**  */
var ICON_HAND_POINTER: number/**  */
var ICON_LASER: number/**  */
var ICON_COIN: number/**  */
var ICON_EXPLOSION: number/**  */
var ICON_1UP: number/**  */
var ICON_PLAYER: number/**  */
var ICON_PLAYER_JUMP: number/**  */
var ICON_KEY: number/**  */
var ICON_DEMON: number/**  */
var ICON_TEXT_POPUP: number/**  */
var ICON_GEAR_EX: number/**  */
var ICON_CRACK: number/**  */
var ICON_CRACK_POINTS: number/**  */
var ICON_STAR: number/**  */
var ICON_DOOR: number/**  */
var ICON_EXIT: number/**  */
var ICON_MODE_2D: number/**  */
var ICON_MODE_3D: number/**  */
var ICON_CUBE: number/**  */
var ICON_CUBE_FACE_TOP: number/**  */
var ICON_CUBE_FACE_LEFT: number/**  */
var ICON_CUBE_FACE_FRONT: number/**  */
var ICON_CUBE_FACE_BOTTOM: number/**  */
var ICON_CUBE_FACE_RIGHT: number/**  */
var ICON_CUBE_FACE_BACK: number/**  */
var ICON_CAMERA: number/**  */
var ICON_SPECIAL: number/**  */
var ICON_LINK_NET: number/**  */
var ICON_LINK_BOXES: number/**  */
var ICON_LINK_MULTI: number/**  */
var ICON_LINK: number/**  */
var ICON_LINK_BROKE: number/**  */
var ICON_TEXT_NOTES: number/**  */
var ICON_NOTEBOOK: number/**  */
var ICON_SUITCASE: number/**  */
var ICON_SUITCASE_ZIP: number/**  */
var ICON_MAILBOX: number/**  */
var ICON_MONITOR: number/**  */
var ICON_PRINTER: number/**  */
var ICON_PHOTO_CAMERA: number/**  */
var ICON_PHOTO_CAMERA_FLASH: number/**  */
var ICON_HOUSE: number/**  */
var ICON_HEART: number/**  */
var ICON_CORNER: number/**  */
var ICON_VERTICAL_BARS: number/**  */
var ICON_VERTICAL_BARS_FILL: number/**  */
var ICON_LIFE_BARS: number/**  */
var ICON_INFO: number/**  */
var ICON_CROSSLINE: number/**  */
var ICON_HELP: number/**  */
var ICON_FILETYPE_ALPHA: number/**  */
var ICON_FILETYPE_HOME: number/**  */
var ICON_LAYERS_VISIBLE: number/**  */
var ICON_LAYERS: number/**  */
var ICON_WINDOW: number/**  */
var ICON_HIDPI: number/**  */
var ICON_FILETYPE_BINARY: number/**  */
var ICON_HEX: number/**  */
var ICON_SHIELD: number/**  */
var ICON_FILE_NEW: number/**  */
var ICON_FOLDER_ADD: number/**  */
var ICON_ALARM: number/**  */
var ICON_CPU: number/**  */
var ICON_ROM: number/**  */
var ICON_STEP_OVER: number/**  */
var ICON_STEP_INTO: number/**  */
var ICON_STEP_OUT: number/**  */
var ICON_RESTART: number/**  */
var ICON_BREAKPOINT_ON: number/**  */
var ICON_BREAKPOINT_OFF: number/**  */
var ICON_BURGER_MENU: number/**  */
var ICON_CASE_SENSITIVE: number/**  */
var ICON_REG_EXP: number/**  */
var ICON_FOLDER: number/**  */
var ICON_FILE: number/**  */
var ICON_SAND_TIMER: number/**  */
var ICON_WARNING: number/**  */
var ICON_HELP_BOX: number/**  */
var ICON_INFO_BOX: number/**  */
var ICON_PRIORITY: number/**  */
var ICON_LAYERS_ISO: number/**  */
var ICON_LAYERS2: number/**  */
var ICON_MLAYERS: number/**  */
var ICON_MAPS: number/**  */
var ICON_HOT: number/**  */
var ICON_LABEL: number/**  */
var ICON_NAME_ID: number/**  */
var ICON_SLICING: number/**  */
var ICON_MANUAL_CONTROL: number/**  */
var ICON_COLLISION: number/**  */
var ICON_234: number/**  */
var ICON_235: number/**  */
var ICON_236: number/**  */
var ICON_237: number/**  */
var ICON_238: number/**  */
var ICON_239: number/**  */
var ICON_240: number/**  */
var ICON_241: number/**  */
var ICON_242: number/**  */
var ICON_243: number/**  */
var ICON_244: number/**  */
var ICON_245: number/**  */
var ICON_246: number/**  */
var ICON_247: number/**  */
var ICON_248: number/**  */
var ICON_249: number/**  */
var ICON_250: number/**  */
var ICON_251: number/**  */
var ICON_252: number/**  */
var ICON_253: number/**  */
var ICON_254: number/**  */
var ICON_255: number/**  */
var RAYGUI_VERSION_MAJOR: number/**  */
var RAYGUI_VERSION_MINOR: number/**  */
var RAYGUI_VERSION_PATCH: number/**  */
var SCROLLBAR_LEFT_SIDE: number/**  */
var SCROLLBAR_RIGHT_SIDE: number}
