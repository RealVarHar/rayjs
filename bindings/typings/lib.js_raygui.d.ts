declare module "rayjs:raygui" {
import type {Font,Color,Rectangle,Vector2,Vector3} from 'rayjs:raylib';
interface GuiStyleProp {
/** Control identifier */
controlId: number,
/** Property identifier */
propertyId: number,
/** Property value */
propertyValue: number,
}
var GuiStyleProp: {
prototype: GuiStyleProp
new(controlId?: number, propertyId?: number, propertyValue?: number): GuiStyleProp
}
/** NOTE: We check for STATE_DISABLED to avoid messing custom global state setups */
function GuiEnable(): void/** NOTE: We check for STATE_NORMAL to avoid messing custom global state setups */
function GuiDisable(): void/** Lock gui global state */
function GuiLock(): void/** Unlock gui global state */
function GuiUnlock(): void/** Check if gui is locked (global state) */
function GuiIsLocked(): boolean/** Set gui controls alpha global state */
function GuiSetAlpha(alpha: number): void/** Set gui state (global state) */
function GuiSetState(state: number): void/** Get gui state (global state) */
function GuiGetState(): number/** NOTE: Font loading/unloading is external to raygui */
function GuiSetFont(font: Font): void/** Get custom gui font */
function GuiGetFont(): Font/** Set control style property value */
function GuiSetStyle(control: number, property: number, value: number): void/** Get control style property value */
function GuiGetStyle(control: number, property: number): number/** in that case, custom font image atlas is GRAY+ALPHA and pixel data can be compressed (DEFLATE) */
function GuiLoadStyle(fileName: string): void/** Load style default over global style */
function GuiLoadStyleDefault(): void/** Enable gui tooltips (global state) */
function GuiEnableTooltip(): void/** Disable gui tooltips (global state) */
function GuiDisableTooltip(): void/** Set tooltip string */
function GuiSetTooltip(tooltip: string): void/** a number that can change between ricon versions */
function GuiIconText(iconId: number, text: string): string/** Set icon drawing size */
function GuiSetIconScale(scale: number): void/** Get full icons data pointer */
function GuiGetIcons(): number[]/** WARNING: guiIconsName[]][] memory should be manually freed! */
function GuiLoadIcons(fileName: string, loadIconsName: boolean): void/** Draw selected icon using rectangles pixel-by-pixel */
function GuiDrawIcon(iconId: number, posX: number, posY: number, pixelSize: number, color: Color): void/** Get text width considering gui style and icon size (if required) */
function GuiGetTextWidth(text: string): number/** Window Box control */
function GuiWindowBox(bounds: Rectangle, title: string): number/** Group Box control with text name */
function GuiGroupBox(bounds: Rectangle, text: string): number/** Line control */
function GuiLine(bounds: Rectangle, text: string): number/** Panel control */
function GuiPanel(bounds: Rectangle, text: string): number/** NOTE: Using GuiToggle() for the TABS */
function GuiTabBar(bounds: Rectangle, text: string[], count: number, active: number | number[]): number/** Scroll Panel control */
function GuiScrollPanel(bounds: Rectangle, text: string, content: Rectangle, scroll: Vector2, view: Rectangle): number/** Label control */
function GuiLabel(bounds: Rectangle, text: string): number/** Button control, returns true when clicked */
function GuiButton(bounds: Rectangle, text: string): number/** Label button control */
function GuiLabelButton(bounds: Rectangle, text: string): number/** Toggle Button control */
function GuiToggle(bounds: Rectangle, text: string, active: boolean | boolean[]): number/** Toggle Group control */
function GuiToggleGroup(bounds: Rectangle, text: string, active: number | number[]): number/** Toggle Slider control extended */
function GuiToggleSlider(bounds: Rectangle, text: string, active: number | number[]): number/** Check Box control, returns 1 when state changed */
function GuiCheckBox(bounds: Rectangle, text: string, checked: boolean | boolean[]): number/** Combo Box control */
function GuiComboBox(bounds: Rectangle, text: string, active: number | number[]): number/** NOTE: Returns mouse click */
function GuiDropdownBox(bounds: Rectangle, text: string, active: number | number[], editMode: boolean): number/** Spinner control, returns selected value */
function GuiSpinner(bounds: Rectangle, text: string, value: number | number[], minValue: number, maxValue: number, editMode: boolean): number/** NOTE: Requires static variables: frameCounter */
function GuiValueBox(bounds: Rectangle, text: string, value: number | number[], minValue: number, maxValue: number, editMode: boolean): number/** NOTE: Requires static variables: frameCounter */
function GuiValueBoxFloat(bounds: Rectangle, text: string, textValue: string, value: number | number[], editMode: boolean): number/** NOTE: Returns true on ENTER pressed (useful for data validation) */
function GuiTextBox(bounds: Rectangle, text: string | string[], textSize: number, editMode: boolean): number/** NOTE: Other GuiSlider*() controls use this one */
function GuiSlider(bounds: Rectangle, textLeft: string, textRight: string, value: number | number[], minValue: number, maxValue: number): number/** Slider Bar control extended, returns selected value */
function GuiSliderBar(bounds: Rectangle, textLeft: string, textRight: string, value: number | number[], minValue: number, maxValue: number): number/** Progress Bar control extended, shows current progress value */
function GuiProgressBar(bounds: Rectangle, textLeft: string, textRight: string, value: number | number[], minValue: number, maxValue: number): number/** Status Bar control */
function GuiStatusBar(bounds: Rectangle, text: string): number/** Dummy rectangle control, intended for placeholding */
function GuiDummyRec(bounds: Rectangle, text: string): number/** https://stackoverflow.com/questions/4435450/2d-opengl-drawing-lines-that-dont-exactly-fit-pixel-raster */
function GuiGrid(bounds: Rectangle, text: string, spacing: number, subdivs: number, mouseCell: Vector2): number/** List View control */
function GuiListView(bounds: Rectangle, text: string, scrollIndex: number | number[], active: number | number[]): number/** List View control with extended parameters */
function GuiListViewEx(bounds: Rectangle, text: string[], count: number, scrollIndex: number | number[], active: number | number[], focus: number[]): number/** Message Box control */
function GuiMessageBox(bounds: Rectangle, title: string, message: string, buttons: string): number/** Text Input Box control, ask for text */
function GuiTextInputBox(bounds: Rectangle, title: string, message: string, buttons: string, text: string, textMaxSize: number, secretViewActive: boolean[]): number/** NOTE: this picker converts RGB to HSV, which can cause the Hue control to jump. If you have this problem, consider using the HSV variant instead */
function GuiColorPicker(bounds: Rectangle, text: string, color: Color): number/** Color Panel control - Color (RGBA) variant */
function GuiColorPanel(bounds: Rectangle, text: string, color: Color): number/** NOTE: Returns alpha value normalized [0..1] */
function GuiColorBarAlpha(bounds: Rectangle, text: string, alpha: number | number[]): number/** float GuiColorBarLuminance() [BLACK->WHITE] */
function GuiColorBarHue(bounds: Rectangle, text: string, hue: number[]): number/** NOTE: bounds define GuiColorPanelHSV() size */
function GuiColorPickerHSV(bounds: Rectangle, text: string, colorHsv: Vector3): number/** Color Panel control - HSV variant */
function GuiColorPanelHSV(bounds: Rectangle, text: string, colorHsv: Vector3): number/** WARNING: Binary files only */
function GuiLoadStyleFromMemory(fileData: number[], dataSize: number): void/** Get text bounds considering control bounds */
function GetTextBounds(control: number, bounds: Rectangle): Rectangle/** NOTE: We support up to 999 values for iconId */
function GetTextIcon(text: string, iconId: number[]): string/** Gui draw text using default font */
function GuiDrawText(text: string, textBounds: Rectangle, alignment: number, tint: Color): void/** Gui draw rectangle using default raygui plain style with borders */
function GuiDrawRectangle(rec: Rectangle, borderWidth: number, borderColor: Color, color: Color): void/** Also check for multiple columns (required by GuiToggleGroup()) */
function GuiTextSplit(text: string, delimiter: string, count: number | number[], textRow: number[]): string[]/** NOTE: Color data should be passed normalized */
function ConvertHSVtoRGB(hsv: Vector3): Vector3/** NOTE: Color data should be passed normalized */
function ConvertRGBtoHSV(rgb: Vector3): Vector3/** Scroll bar control (used by GuiScrollPanel()) */
function GuiScrollBar(bounds: Rectangle, value: number, minValue: number, maxValue: number): number/** Draw tooltip using control bounds */
function GuiTooltip(controlRec: Rectangle): void/** WARNING: It multiplies current alpha by alpha scale factor */
function GuiFade(color: Color, alpha: number): Color/** WARNING: Binary files only */
function GuiLoadIconsFromMemory(fileData: number[], dataSize: number, loadIconsName: boolean): void/** Get text width to next space for provided string */
function GetNextSpaceWidth(text: string, nextSpaceIndex: number[]): number/** undefined */
function GuiGetAlpha(): number/** undefined */
function GuiIsExclusive(): boolean/**  */
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
var DEFAULT: number/** Used also for: LABELBUTTON */
var LABEL: number/**  */
var BUTTON: number/** Used also for: TOGGLEGROUP */
var TOGGLE: number/** Used also for: SLIDERBAR, TOGGLESLIDER */
var SLIDER: number/**  */
var PROGRESSBAR: number/**  */
var CHECKBOX: number/**  */
var COMBOBOX: number/**  */
var DROPDOWNBOX: number/** Used also for: TEXTBOXMULTI */
var TEXTBOX: number/**  */
var VALUEBOX: number/**  */
var CONTROL11: number/**  */
var LISTVIEW: number/**  */
var COLORPICKER: number/**  */
var SCROLLBAR: number/**  */
var STATUSBAR: number/** Control border color in STATE_NORMAL */
var BORDER_COLOR_NORMAL: number/** Control base color in STATE_NORMAL */
var BASE_COLOR_NORMAL: number/** Control text color in STATE_NORMAL */
var TEXT_COLOR_NORMAL: number/** Control border color in STATE_FOCUSED */
var BORDER_COLOR_FOCUSED: number/** Control base color in STATE_FOCUSED */
var BASE_COLOR_FOCUSED: number/** Control text color in STATE_FOCUSED */
var TEXT_COLOR_FOCUSED: number/** Control border color in STATE_PRESSED */
var BORDER_COLOR_PRESSED: number/** Control base color in STATE_PRESSED */
var BASE_COLOR_PRESSED: number/** Control text color in STATE_PRESSED */
var TEXT_COLOR_PRESSED: number/** Control border color in STATE_DISABLED */
var BORDER_COLOR_DISABLED: number/** Control base color in STATE_DISABLED */
var BASE_COLOR_DISABLED: number/** Control text color in STATE_DISABLED */
var TEXT_COLOR_DISABLED: number/** Control border size, 0 for no border */
var BORDER_WIDTH: number/** Control text padding, not considering border */
var TEXT_PADDING: number/** Control text horizontal alignment inside control text bound (after border and padding) */
var TEXT_ALIGNMENT: number/** Text size (glyphs max height) */
var TEXT_SIZE: number/** Text spacing between glyphs */
var TEXT_SPACING: number/** Line control color */
var LINE_COLOR: number/** Background color */
var BACKGROUND_COLOR: number/** Text spacing between lines */
var TEXT_LINE_SPACING: number/** Text vertical alignment inside text bounds (after border and padding) */
var TEXT_ALIGNMENT_VERTICAL: number/**  */
var TEXT_WRAP_MODE: number/** ToggleGroup separation between toggles */
var GROUP_PADDING: number/** Slider size of internal bar */
var SLIDER_WIDTH: number/**  */
var SLIDER_PADDING: number/** ProgressBar internal padding */
var PROGRESS_PADDING: number/** ScrollBar arrows size */
var ARROWS_SIZE: number/** ScrollBar arrows visible */
var ARROWS_VISIBLE: number/** ScrollBar slider internal padding */
var SCROLL_SLIDER_PADDING: number/** ScrollBar slider size */
var SCROLL_SLIDER_SIZE: number/** ScrollBar scroll padding from arrows */
var SCROLL_PADDING: number/** ScrollBar scrolling speed */
var SCROLL_SPEED: number/**  */
var CHECK_PADDING: number/** ComboBox right button width */
var COMBO_BUTTON_WIDTH: number/**  */
var COMBO_BUTTON_SPACING: number/** DropdownBox arrow separation from border and items */
var ARROW_PADDING: number/** DropdownBox items separation */
var DROPDOWN_ITEMS_SPACING: number/** DropdownBox arrow hidden */
var DROPDOWN_ARROW_HIDDEN: number/**  */
var DROPDOWN_ROLL_UP: number/** TextBox in read-only mode: 0-text editable, 1-text no-editable */
var TEXT_READONLY: number/** Spinner left/right buttons width */
var SPINNER_BUTTON_WIDTH: number/** Spinner buttons separation */
var SPINNER_BUTTON_SPACING: number/** ListView items height */
var LIST_ITEMS_HEIGHT: number/** ListView items separation */
var LIST_ITEMS_SPACING: number/** ListView scrollbar size (usually width) */
var SCROLLBAR_WIDTH: number/** ListView scrollbar side (0-SCROLLBAR_LEFT_SIDE, 1-SCROLLBAR_RIGHT_SIDE) */
var SCROLLBAR_SIDE: number/** ListView items border enabled in normal state */
var LIST_ITEMS_BORDER_NORMAL: number/**  */
var LIST_ITEMS_BORDER_WIDTH: number/**  */
var COLOR_SELECTOR_SIZE: number/** ColorPicker right hue bar width */
var HUEBAR_WIDTH: number/** ColorPicker right hue bar separation from panel */
var HUEBAR_PADDING: number/** ColorPicker right hue bar selector height */
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
var ICON_CIRCLE_ADD: number/**  */
var ICON_CIRCLE_ADD_FILL: number/**  */
var ICON_CIRCLE_WARNING: number/**  */
var ICON_CIRCLE_WARNING_FILL: number/**  */
var ICON_BOX_MORE: number/**  */
var ICON_BOX_MORE_FILL: number/**  */
var ICON_BOX_MINUS: number/**  */
var ICON_BOX_MINUS_FILL: number/**  */
var ICON_UNION: number/**  */
var ICON_INTERSECTION: number/**  */
var ICON_DIFFERENCE: number/**  */
var ICON_SPHERE: number/**  */
var ICON_CYLINDER: number/**  */
var ICON_CONE: number/**  */
var ICON_ELLIPSOID: number/**  */
var ICON_CAPSULE: number/**  */
var ICON_250: number/**  */
var ICON_251: number/**  */
var ICON_252: number/**  */
var ICON_253: number/**  */
var ICON_254: number/**  */
var ICON_255: number/**  */
var BORDER: number/**  */
var BASE: number/**  */
var TEXT: number/**  */
var OTHER: number/**  */
var RAYGUI_VERSION_MAJOR: number/**  */
var RAYGUI_VERSION_MINOR: number/**  */
var RAYGUI_VERSION_PATCH: number/**  */
var SCROLLBAR_LEFT_SIDE: number/**  */
var SCROLLBAR_RIGHT_SIDE: number/** Size of icons in pixels (squared) */
var RAYGUI_ICON_SIZE: number/** Maximum number of icons */
var RAYGUI_ICON_MAX_ICONS: number/** Maximum length of icon name id */
var RAYGUI_ICON_MAX_NAME_LENGTH: number/** Maximum number of controls */
var RAYGUI_MAX_CONTROLS: number/** Maximum number of base properties */
var RAYGUI_MAX_PROPS_BASE: number/** Maximum number of extended properties */
var RAYGUI_MAX_PROPS_EXTENDED: number}
