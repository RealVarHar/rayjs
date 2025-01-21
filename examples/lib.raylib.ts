interface Vector2 {
    /** Vector x component */
    x: number,
    /** Vector y component */
    y: number,
}
declare var Vector2: {
    prototype: Vector2;
    new(x: number, y: number): Vector2;
}
interface Vector3 {
    /** Vector x component */
    x: number,
    /** Vector y component */
    y: number,
    /** Vector z component */
    z: number,
}
declare var Vector3: {
    prototype: Vector3;
    new(x: number, y: number, z: number): Vector3;
}
interface Vector4 {
    /** Vector x component */
    x: number,
    /** Vector y component */
    y: number,
    /** Vector z component */
    z: number,
    /** Vector w component */
    w: number,
}
declare var Vector4: {
    prototype: Vector4;
    new(x: number, y: number, z: number, w: number): Vector4;
}
interface Matrix {
}
declare var Matrix: {
    prototype: Matrix;
}
interface Color {
    /** Color red value */
    r: number,
    /** Color green value */
    g: number,
    /** Color blue value */
    b: number,
    /** Color alpha value */
    a: number,
}
declare var Color: {
    prototype: Color;
    new(r: number, g: number, b: number, a: number): Color;
}
interface Rectangle {
    /** Rectangle top-left corner position x */
    x: number,
    /** Rectangle top-left corner position y */
    y: number,
    /** Rectangle width */
    width: number,
    /** Rectangle height */
    height: number,
}
declare var Rectangle: {
    prototype: Rectangle;
    new(x: number, y: number, width: number, height: number): Rectangle;
}
interface Image {
    /** Image raw data */
    data: any,
    /** Image base width */
    width: number,
    /** Image base height */
    height: number,
    /** Mipmap levels, 1 by default */
    mipmaps: number,
    /** Data format (PixelFormat type) */
    format: number,
}
declare var Image: {
    prototype: Image;
    new(): Image;
}
interface Texture {
    /** Texture base width */
    width: number,
    /** Texture base height */
    height: number,
    /** Mipmap levels, 1 by default */
    mipmaps: number,
    /** Data format (PixelFormat type) */
    format: number,
}
declare var Texture: {
    prototype: Texture;
}
interface RenderTexture {
    /** OpenGL framebuffer object id */
    id: number,
    /** Color buffer attachment texture */
    texture: Texture,
    /** Depth buffer attachment texture */
    depth: Texture,
}
declare var RenderTexture: {
    prototype: RenderTexture;
}
interface NPatchInfo {
    /** Texture source rectangle */
    source: Rectangle,
    /** Left border offset */
    left: number,
    /** Top border offset */
    top: number,
    /** Right border offset */
    right: number,
    /** Bottom border offset */
    bottom: number,
    /** Layout of the n-patch: 3x3, 1x3 or 3x1 */
    layout: number,
}
declare var NPatchInfo: {
    prototype: NPatchInfo;
    new(source: Rectangle, left: number, top: number, right: number, bottom: number, layout: number): NPatchInfo;
}
interface GlyphInfo {
}
declare var GlyphInfo: {
    prototype: GlyphInfo;
}
interface Font {
    /** Base size (default chars height) */
    baseSize: number,
    /** Number of glyph characters */
    glyphCount: number,
    /** Padding around the glyph characters */
    glyphPadding: number,
    /** Texture atlas containing the glyphs */
    texture: Texture,
}
declare var Font: {
    prototype: Font;
}
interface Camera3D {
    /** Camera position */
    position: Vector3,
    /** Camera target it looks-at */
    target: Vector3,
    /** Camera up vector (rotation over its axis) */
    up: Vector3,
    /** Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic */
    fovy: number,
    /** Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC */
    projection: number,
}
declare var Camera3D: {
    prototype: Camera3D;
    new(position: Vector3, target: Vector3, up: Vector3, fovy: number, projection: number): Camera3D;
}
interface Camera2D {
    /** Camera offset (displacement from target) */
    offset: Vector2,
    /** Camera target (rotation and zoom origin) */
    target: Vector2,
    /** Camera rotation in degrees */
    rotation: number,
    /** Camera zoom (scaling), should be 1.0f by default */
    zoom: number,
}
declare var Camera2D: {
    prototype: Camera2D;
    new(offset: Vector2, target: Vector2, rotation: number, zoom: number): Camera2D;
}
interface Mesh {
    /** Number of vertices stored in arrays */
    vertexCount: number,
    /** Number of triangles stored (indexed or not) */
    triangleCount: number,
    /** Vertex position (XYZ - 3 components per vertex) (shader-location = 0) */
    vertices: ArrayBuffer,
    /** Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1) */
    texcoords: ArrayBuffer,
    /** Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5) */
    texcoords2: ArrayBuffer,
    /** Vertex normals (XYZ - 3 components per vertex) (shader-location = 2) */
    normals: ArrayBuffer,
    /** Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4) */
    tangents: ArrayBuffer,
    /** Vertex colors (RGBA - 4 components per vertex) (shader-location = 3) */
    colors: ArrayBuffer,
    /** Vertex indices (in case vertex data comes indexed) */
    indices: ArrayBuffer,
    /** Animated vertex positions (after bones transformations) */
    animVertices: ArrayBuffer,
    /** Animated normals (after bones transformations) */
    animNormals: ArrayBuffer,
    /** Vertex bone ids, max 255 bone ids, up to 4 bones influence by vertex (skinning) (shader-location = 6) */
    boneIds: ArrayBuffer,
    /** Vertex bone weight, up to 4 bones influence by vertex (skinning) (shader-location = 7) */
    boneWeights: ArrayBuffer,
}
declare var Mesh: {
    prototype: Mesh;
    new(): Mesh;
}
interface Shader {
    /** Shader program id */
    id: number,
}
declare var Shader: {
    prototype: Shader;
}
interface MaterialMap {
    /** Material map texture */
    texture: Texture,
    /** Material map color */
    color: Color,
    /** Material map value */
    value: number,
}
declare var MaterialMap: {
    prototype: MaterialMap;
}
interface Material {
    /** Material shader */
    shader: Shader,
    /** Material maps array (MAX_MATERIAL_MAPS) */
    maps: MaterialMap,
}
declare var Material: {
    prototype: Material;
}
interface Transform {
}
declare var Transform: {
    prototype: Transform;
}
interface BoneInfo {
}
declare var BoneInfo: {
    prototype: BoneInfo;
}
interface Model {
    /** Local transform matrix */
    transform: Matrix,
    /** Number of meshes */
    meshCount: number,
    /** Number of materials */
    materialCount: number,
    /** Meshes array */
    meshes: Mesh,
    /** Materials array */
    materials: Material,
    /** Mesh material number */
    meshMaterial: int,
    /** Number of bones */
    boneCount: number,
    /** Bones information (skeleton) */
    bones: BoneInfo,
    /** Bones base transformation (pose) */
    bindPose: Transform,
}
declare var Model: {
    prototype: Model;
}
interface ModelAnimation {
}
declare var ModelAnimation: {
    prototype: ModelAnimation;
}
interface Ray {
    /** Ray position (origin) */
    position: Vector3,
    /** Ray direction (normalized) */
    direction: Vector3,
}
declare var Ray: {
    prototype: Ray;
    new(position: Vector3, direction: Vector3): Ray;
}
interface RayCollision {
    /** Did the ray hit something? */
    hit: boolean,
    /** Distance to the nearest hit */
    distance: number,
    /** Point of the nearest hit */
    point: Vector3,
    /** Surface normal of hit */
    normal: Vector3,
}
declare var RayCollision: {
    prototype: RayCollision;
}
interface BoundingBox {
    /** Minimum vertex box-corner */
    min: Vector3,
    /** Maximum vertex box-corner */
    max: Vector3,
}
declare var BoundingBox: {
    prototype: BoundingBox;
    new(min: Vector3, max: Vector3): BoundingBox;
}
interface Wave {
    /** Total number of frames (considering channels) */
    frameCount: number,
    /** Frequency (samples per second) */
    sampleRate: number,
    /** Bit depth (bits per sample): 8, 16, 32 (24 not supported) */
    sampleSize: number,
    /** Number of channels (1-mono, 2-stereo, ...) */
    channels: number,
}
declare var Wave: {
    prototype: Wave;
}
interface AudioStream {
}
declare var AudioStream: {
    prototype: AudioStream;
}
interface Sound {
    /** Total number of frames (considering channels) */
    frameCount: number,
}
declare var Sound: {
    prototype: Sound;
}
interface Music {
    /** Total number of frames (considering channels) */
    frameCount: number,
    /** Music looping enable */
    looping: boolean,
    /** Type of music context (audio filetype) */
    ctxType: number,
}
declare var Music: {
    prototype: Music;
}
interface VrDeviceInfo {
    /** Horizontal resolution in pixels */
    hResolution: number,
    /** Vertical resolution in pixels */
    vResolution: number,
    /** Horizontal size in meters */
    hScreenSize: number,
    /** Vertical size in meters */
    vScreenSize: number,
    /** Distance between eye and display in meters */
    eyeToScreenDistance: number,
    /** Lens separation distance in meters */
    lensSeparationDistance: number,
    /** IPD (distance between pupils) in meters */
    interpupillaryDistance: number,
    /** Lens distortion constant parameters */
    lensDistortionValues: float [4],
    /** Chromatic aberration correction parameters */
    chromaAbCorrection: float [4],
}
declare var VrDeviceInfo: {
    prototype: VrDeviceInfo;
    new(): VrDeviceInfo;
}
interface VrStereoConfig {
}
declare var VrStereoConfig: {
    prototype: VrStereoConfig;
}
interface FilePathList {
}
declare var FilePathList: {
    prototype: FilePathList;
}
interface AutomationEvent {
}
declare var AutomationEvent: {
    prototype: AutomationEvent;
}
interface AutomationEventList {
}
declare var AutomationEventList: {
    prototype: AutomationEventList;
}
/** Initialize window and OpenGL context */
declare function initWindow(width: number, height: number, title: string | undefined | null): void;
/** Close window and unload OpenGL context */
declare function closeWindow(): void;
/** Check if application should close (KEY_ESCAPE pressed or windows close icon clicked) */
declare function windowShouldClose(): boolean;
/** Check if window has been initialized successfully */
declare function isWindowReady(): boolean;
/** Check if window is currently fullscreen */
declare function isWindowFullscreen(): boolean;
/** Check if window is currently hidden */
declare function isWindowHidden(): boolean;
/** Check if window is currently minimized */
declare function isWindowMinimized(): boolean;
/** Check if window is currently maximized */
declare function isWindowMaximized(): boolean;
/** Check if window is currently focused */
declare function isWindowFocused(): boolean;
/** Check if window has been resized last frame */
declare function isWindowResized(): boolean;
/** Check if one specific window flag is enabled */
declare function isWindowState(flag: number): boolean;
/** Set window configuration state using flags */
declare function setWindowState(flags: number): void;
/** Clear window configuration state flags */
declare function clearWindowState(flags: number): void;
/** Toggle window state: fullscreen/windowed, resizes monitor to match window resolution */
declare function toggleFullscreen(): void;
/** Toggle window state: borderless windowed, resizes window to match monitor resolution */
declare function toggleBorderlessWindowed(): void;
/** Set window state: maximized, if resizable */
declare function maximizeWindow(): void;
/** Set window state: minimized, if resizable */
declare function minimizeWindow(): void;
/** Set window state: not minimized/maximized */
declare function restoreWindow(): void;
/** Set icon for window (single image, RGBA 32bit) */
declare function setWindowIcon(image: Image): void;
/** Set title for window */
declare function setWindowTitle(title: string | undefined | null): void;
/** Set window position on screen */
declare function setWindowPosition(x: number, y: number): void;
/** Set monitor for the current window */
declare function setWindowMonitor(monitor: number): void;
/** Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE) */
declare function setWindowMinSize(width: number, height: number): void;
/** Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE) */
declare function setWindowMaxSize(width: number, height: number): void;
/** Set window dimensions */
declare function setWindowSize(width: number, height: number): void;
/** Set window opacity [0.0f..1.0f] */
declare function setWindowOpacity(opacity: number): void;
/** Set window focused */
declare function setWindowFocused(): void;
/** Get current screen width */
declare function getScreenWidth(): number;
/** Get current screen height */
declare function getScreenHeight(): number;
/** Get current render width (it considers HiDPI) */
declare function getRenderWidth(): number;
/** Get current render height (it considers HiDPI) */
declare function getRenderHeight(): number;
/** Get number of connected monitors */
declare function getMonitorCount(): number;
/** Get current monitor where window is placed */
declare function getCurrentMonitor(): number;
/** Get specified monitor position */
declare function getMonitorPosition(monitor: number): Vector2;
/** Get specified monitor width (current video mode used by monitor) */
declare function getMonitorWidth(monitor: number): number;
/** Get specified monitor height (current video mode used by monitor) */
declare function getMonitorHeight(monitor: number): number;
/** Get specified monitor physical width in millimetres */
declare function getMonitorPhysicalWidth(monitor: number): number;
/** Get specified monitor physical height in millimetres */
declare function getMonitorPhysicalHeight(monitor: number): number;
/** Get specified monitor refresh rate */
declare function getMonitorRefreshRate(monitor: number): number;
/** Get window position XY on monitor */
declare function getWindowPosition(): Vector2;
/** Get window scale DPI factor */
declare function getWindowScaleDPI(): Vector2;
/** Get the human-readable, UTF-8 encoded name of the specified monitor */
declare function getMonitorName(monitor: number): string | undefined | null;
/** Set clipboard text content */
declare function setClipboardText(text: string | undefined | null): void;
/** Get clipboard text content */
declare function getClipboardText(): string | undefined | null;
/** Get clipboard image content */
declare function getClipboardImage(): Image;
/** Enable waiting for events on EndDrawing(), no automatic event polling */
declare function enableEventWaiting(): void;
/** Disable waiting for events on EndDrawing(), automatic events polling */
declare function disableEventWaiting(): void;
/** Shows cursor */
declare function showCursor(): void;
/** Hides cursor */
declare function hideCursor(): void;
/** Check if cursor is not visible */
declare function isCursorHidden(): boolean;
/** Enables cursor (unlock cursor) */
declare function enableCursor(): void;
/** Disables cursor (lock cursor) */
declare function disableCursor(): void;
/** Check if cursor is on the screen */
declare function isCursorOnScreen(): boolean;
/** Set background color (framebuffer clear color) */
declare function clearBackground(color: Color): void;
/** Setup canvas (framebuffer) to start drawing */
declare function beginDrawing(): void;
/** End canvas drawing and swap buffers (double buffering) */
declare function endDrawing(): void;
/** Begin 2D mode with custom camera (2D) */
declare function beginMode2D(camera: Camera2D): void;
/** Ends 2D mode with custom camera */
declare function endMode2D(): void;
/** Begin 3D mode with custom camera (3D) */
declare function beginMode3D(camera: Camera3D): void;
/** Ends 3D mode and returns to default 2D orthographic mode */
declare function endMode3D(): void;
/** Begin drawing to render texture */
declare function beginTextureMode(target: RenderTexture): void;
/** Ends drawing to render texture */
declare function endTextureMode(): void;
/** Begin custom shader drawing */
declare function beginShaderMode(shader: Shader): void;
/** End custom shader drawing (use default shader) */
declare function endShaderMode(): void;
/** Begin blending mode (alpha, additive, multiplied, subtract, custom) */
declare function beginBlendMode(mode: number): void;
/** End blending mode (reset to default: alpha blending) */
declare function endBlendMode(): void;
/** Begin scissor mode (define screen area for following drawing) */
declare function beginScissorMode(x: number, y: number, width: number, height: number): void;
/** End scissor mode */
declare function endScissorMode(): void;
/** Begin stereo rendering (requires VR simulator) */
declare function beginVrStereoMode(config: VrStereoConfig): void;
/** End stereo rendering (requires VR simulator) */
declare function endVrStereoMode(): void;
/** Load VR stereo config for VR simulator device parameters */
declare function loadVrStereoConfig(device: VrDeviceInfo): VrStereoConfig;
/** Unload VR stereo config */
declare function unloadVrStereoConfig(config: VrStereoConfig): void;
/** Load shader from files and bind default locations */
declare function loadShader(vsFileName: string | undefined | null, fsFileName: string | undefined | null): Shader;
/** Load shader from code strings and bind default locations */
declare function loadShaderFromMemory(vsCode: string | undefined | null, fsCode: string | undefined | null): Shader;
/** Check if a shader is valid (loaded on GPU) */
declare function isShaderValid(shader: Shader): boolean;
/** Get shader uniform location */
declare function getShaderLocation(shader: Shader, uniformName: string | undefined | null): number;
/** Get shader attribute location */
declare function getShaderLocationAttrib(shader: Shader, attribName: string | undefined | null): number;
/** Set shader uniform value */
declare function setShaderValue(shader: Shader, locIndex: number, value: void &, uniformType: number): void;
/** Set shader uniform value vector */
declare function setShaderValueV(shader: Shader, locIndex: number, values: any, uniformType: number, count: number): void;
/** Set shader uniform value (matrix 4x4) */
declare function setShaderValueMatrix(shader: Shader, locIndex: number, mat: Matrix): void;
/** Set shader uniform value for texture (sampler2d) */
declare function setShaderValueTexture(shader: Shader, locIndex: number, texture: Texture): void;
/** Unload shader from GPU memory (VRAM) */
declare function unloadShader(shader: Shader): void;
/** Get a ray trace from screen position (i.e mouse) */
declare function getScreenToWorldRay(position: Vector2, camera: Camera3D): Ray;
/** Get a ray trace from screen position (i.e mouse) in a viewport */
declare function getScreenToWorldRayEx(position: Vector2, camera: Camera3D, width: number, height: number): Ray;
/** Get the screen space position for a 3d world space position */
declare function getWorldToScreen(position: Vector3, camera: Camera3D): Vector2;
/** Get size position for a 3d world space position */
declare function getWorldToScreenEx(position: Vector3, camera: Camera3D, width: number, height: number): Vector2;
/** Get the screen space position for a 2d camera world space position */
declare function getWorldToScreen2D(position: Vector2, camera: Camera2D): Vector2;
/** Get the world space position for a 2d camera screen space position */
declare function getScreenToWorld2D(position: Vector2, camera: Camera2D): Vector2;
/** Get camera transform matrix (view matrix) */
declare function getCameraMatrix(camera: Camera3D): Matrix;
/** Get camera 2d transform matrix */
declare function getCameraMatrix2D(camera: Camera2D): Matrix;
/** Set target FPS (maximum) */
declare function setTargetFPS(fps: number): void;
/** Get time in seconds for last frame drawn (delta time) */
declare function getFrameTime(): number;
/** Get elapsed time in seconds since InitWindow() */
declare function getTime(): number;
/** Get current FPS */
declare function getFPS(): number;
/** Set the seed for the random number generator */
declare function setRandomSeed(seed: number): void;
/** Get a random value between min and max (both included) */
declare function getRandomValue(min: number, max: number): number;
/** Load random values sequence, no values repeated */
declare function loadRandomSequence(count: number, min: number, max: number): int;
/** Takes a screenshot of current screen (filename extension defines format) */
declare function takeScreenshot(fileName: string | undefined | null): void;
/** Setup init configuration flags (view FLAGS) */
declare function setConfigFlags(flags: number): void;
/** Open URL with default system browser (if available) */
declare function openURL(url: string | undefined | null): void;
/** Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...) */
declare function traceLog(logLevel: number): void;
/** Set the current threshold (minimum) log level */
declare function setTraceLogLevel(logLevel: number): void;
/** Set custom file binary data loader */
declare function setLoadFileDataCallback(callback: LoadFileDataCallback): void;
/** Set custom file binary data saver */
declare function setSaveFileDataCallback(callback: SaveFileDataCallback): void;
/** Set custom file text data loader */
declare function setLoadFileTextCallback(callback: LoadFileTextCallback): void;
/** Set custom file text data saver */
declare function setSaveFileTextCallback(callback: SaveFileTextCallback): void;
/** Load file data as byte array (read) */
declare function loadFileData(fileName: string | undefined | null, dataSize: int &): ArrayBuffer;
/** Save data to file from byte array (write), returns true on success */
declare function saveFileData(fileName: string | undefined | null, data: any, dataSize: number): boolean;
/** Load text data from file (read), returns a '\0' terminated string */
declare function loadFileText(fileName: string | undefined | null): string | undefined | null;
/** Save text data to file (write), string must be '\0' terminated, returns true on success */
declare function saveFileText(fileName: string | undefined | null, text: string | undefined | null): boolean;
/** Check if file exists */
declare function fileExists(fileName: string | undefined | null): boolean;
/** Check if a directory path exists */
declare function directoryExists(dirPath: string | undefined | null): boolean;
/** Check file extension (including point: .png, .wav) */
declare function isFileExtension(fileName: string | undefined | null, ext: string | undefined | null): boolean;
/** Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h) */
declare function getFileLength(fileName: string | undefined | null): number;
/** Get pointer to extension for a filename string (includes dot: '.png') */
declare function getFileExtension(fileName: string | undefined | null): string | undefined | null;
/** Get pointer to filename for a path string */
declare function getFileName(filePath: string | undefined | null): string | undefined | null;
/** Get filename string without extension (uses static string) */
declare function getFileNameWithoutExt(filePath: string | undefined | null): string | undefined | null;
/** Get full path for a given fileName with path (uses static string) */
declare function getDirectoryPath(filePath: string | undefined | null): string | undefined | null;
/** Get previous directory path for a given path (uses static string) */
declare function getPrevDirectoryPath(dirPath: string | undefined | null): string | undefined | null;
/** Get current working directory (uses static string) */
declare function getWorkingDirectory(): string | undefined | null;
/** Get the directory of the running application (uses static string) */
declare function getApplicationDirectory(): string | undefined | null;
/** Create directories (including full path requested), returns 0 on success */
declare function makeDirectory(dirPath: string | undefined | null): number;
/** Change working directory, return true on success */
declare function changeDirectory(dir: string | undefined | null): boolean;
/** Check if a given path is a file or a directory */
declare function isPathFile(path: string | undefined | null): boolean;
/** Check if fileName is valid for the platform/OS */
declare function isFileNameValid(fileName: string | undefined | null): boolean;
/** Load directory filepaths */
declare function loadDirectoryFiles(dirPath: string | undefined | null): string[];
/** Load directory filepaths with extension filtering and recursive directory scan. Use 'DIR' in the filter string to include directories in the result */
declare function loadDirectoryFilesEx(basePath: string | undefined | null, filter: string | undefined | null, scanSubdirs: boolean): string[];
/** Check if a file has been dropped into window */
declare function isFileDropped(): boolean;
/** Load dropped filepaths */
declare function loadDroppedFiles(): string[];
/** Get file modification time (last write time) */
declare function getFileModTime(fileName: string | undefined | null): number;
/** Compute CRC32 hash code */
declare function computeCRC32(data: ArrayBuffer, dataSize: number): number;
/** Compute MD5 hash code, returns static int[4] (16 bytes) */
declare function computeMD5(data: ArrayBuffer, dataSize: number): unsigned int;
/** Compute SHA1 hash code, returns static int[5] (20 bytes) */
declare function computeSHA1(data: ArrayBuffer, dataSize: number): unsigned int;
/** Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS */
declare function loadAutomationEventList(fileName: string | undefined | null): AutomationEventList;
/** Unload automation events list from file */
declare function unloadAutomationEventList(list: AutomationEventList): void;
/** Export automation events list as text file */
declare function exportAutomationEventList(list: AutomationEventList, fileName: string | undefined | null): boolean;
/** Set automation event list to record to */
declare function setAutomationEventList(list: AutomationEventList &): void;
/** Set automation event internal base frame to start recording */
declare function setAutomationEventBaseFrame(frame: number): void;
/** Start recording automation events (AutomationEventList must be set) */
declare function startAutomationEventRecording(): void;
/** Stop recording automation events */
declare function stopAutomationEventRecording(): void;
/** Play a recorded automation event */
declare function playAutomationEvent(event: AutomationEvent): void;
/** Check if a key has been pressed once */
declare function isKeyPressed(key: number): boolean;
/** Check if a key has been pressed again */
declare function isKeyPressedRepeat(key: number): boolean;
/** Check if a key is being pressed */
declare function isKeyDown(key: number): boolean;
/** Check if a key has been released once */
declare function isKeyReleased(key: number): boolean;
/** Check if a key is NOT being pressed */
declare function isKeyUp(key: number): boolean;
/** Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty */
declare function getKeyPressed(): number;
/** Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty */
declare function getCharPressed(): number;
/** Get name of a QWERTY key on the current keyboard layout (eg returns string 'q' for KEY_A on an AZERTY keyboard) */
declare function getKeyName(key: number): string | undefined | null;
/** Set a custom key to exit program (default is ESC) */
declare function setExitKey(key: number): void;
/** Check if a gamepad is available */
declare function isGamepadAvailable(gamepad: number): boolean;
/** Get gamepad internal name id */
declare function getGamepadName(gamepad: number): string | undefined | null;
/** Check if a gamepad button has been pressed once */
declare function isGamepadButtonPressed(gamepad: number, button: number): boolean;
/** Check if a gamepad button is being pressed */
declare function isGamepadButtonDown(gamepad: number, button: number): boolean;
/** Check if a gamepad button has been released once */
declare function isGamepadButtonReleased(gamepad: number, button: number): boolean;
/** Check if a gamepad button is NOT being pressed */
declare function isGamepadButtonUp(gamepad: number, button: number): boolean;
/** Get the last gamepad button pressed */
declare function getGamepadButtonPressed(): number;
/** Get gamepad axis count for a gamepad */
declare function getGamepadAxisCount(gamepad: number): number;
/** Get axis movement value for a gamepad axis */
declare function getGamepadAxisMovement(gamepad: number, axis: number): number;
/** Set internal gamepad mappings (SDL_GameControllerDB) */
declare function setGamepadMappings(mappings: string | undefined | null): number;
/** Set gamepad vibration for both motors (duration in seconds) */
declare function setGamepadVibration(gamepad: number, leftMotor: number, rightMotor: number, duration: number): void;
/** Check if a mouse button has been pressed once */
declare function isMouseButtonPressed(button: number): boolean;
/** Check if a mouse button is being pressed */
declare function isMouseButtonDown(button: number): boolean;
/** Check if a mouse button has been released once */
declare function isMouseButtonReleased(button: number): boolean;
/** Check if a mouse button is NOT being pressed */
declare function isMouseButtonUp(button: number): boolean;
/** Get mouse position X */
declare function getMouseX(): number;
/** Get mouse position Y */
declare function getMouseY(): number;
/** Get mouse position XY */
declare function getMousePosition(): Vector2;
/** Get mouse delta between frames */
declare function getMouseDelta(): Vector2;
/** Set mouse position XY */
declare function setMousePosition(x: number, y: number): void;
/** Set mouse offset */
declare function setMouseOffset(offsetX: number, offsetY: number): void;
/** Set mouse scaling */
declare function setMouseScale(scaleX: number, scaleY: number): void;
/** Get mouse wheel movement for X or Y, whichever is larger */
declare function getMouseWheelMove(): number;
/** Get mouse wheel movement for both X and Y */
declare function getMouseWheelMoveV(): Vector2;
/** Set mouse cursor */
declare function setMouseCursor(cursor: number): void;
/** Get touch position X for touch point 0 (relative to screen size) */
declare function getTouchX(): number;
/** Get touch position Y for touch point 0 (relative to screen size) */
declare function getTouchY(): number;
/** Get touch position XY for a touch point index (relative to screen size) */
declare function getTouchPosition(index: number): Vector2;
/** Get touch point identifier for given index */
declare function getTouchPointId(index: number): number;
/** Get number of touch points */
declare function getTouchPointCount(): number;
/** Enable a set of gestures using flags */
declare function setGesturesEnabled(flags: number): void;
/** Check if a gesture have been detected */
declare function isGestureDetected(gesture: number): boolean;
/** Get latest detected gesture */
declare function getGestureDetected(): number;
/** Get gesture hold time in seconds */
declare function getGestureHoldDuration(): number;
/** Get gesture drag vector */
declare function getGestureDragVector(): Vector2;
/** Get gesture drag angle */
declare function getGestureDragAngle(): number;
/** Get gesture pinch delta */
declare function getGesturePinchVector(): Vector2;
/** Get gesture pinch angle */
declare function getGesturePinchAngle(): number;
/** Update camera position for selected mode */
declare function updateCamera(camera: Camera &, mode: number): void;
/** Update camera movement/rotation */
declare function updateCameraPro(camera: Camera &, movement: Vector3, rotation: Vector3, zoom: number): void;
/** Set texture and rectangle to be used on shapes drawing */
declare function setShapesTexture(texture: Texture, source: Rectangle): void;
/** Get texture that is used for shapes drawing */
declare function getShapesTexture(): Texture;
/** Get texture source rectangle that is used for shapes drawing */
declare function getShapesTextureRectangle(): Rectangle;
/** Draw a pixel using geometry [Can be slow, use with care] */
declare function drawPixel(posX: number, posY: number, color: Color): void;
/** Draw a pixel using geometry (Vector version) [Can be slow, use with care] */
declare function drawPixelV(position: Vector2, color: Color): void;
/** Draw a line */
declare function drawLine(startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void;
/** Draw a line (using gl lines) */
declare function drawLineV(startPos: Vector2, endPos: Vector2, color: Color): void;
/** Draw a line (using triangles/quads) */
declare function drawLineEx(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void;
/** Draw line segment cubic-bezier in-out interpolation */
declare function drawLineBezier(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void;
/** Draw a color-filled circle */
declare function drawCircle(centerX: number, centerY: number, radius: number, color: Color): void;
/** Draw a piece of a circle */
declare function drawCircleSector(center: Vector2, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** Draw circle sector outline */
declare function drawCircleSectorLines(center: Vector2, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** Draw a gradient-filled circle */
declare function drawCircleGradient(centerX: number, centerY: number, radius: number, inner: Color, outer: Color): void;
/** Draw a color-filled circle (Vector version) */
declare function drawCircleV(center: Vector2, radius: number, color: Color): void;
/** Draw circle outline */
declare function drawCircleLines(centerX: number, centerY: number, radius: number, color: Color): void;
/** Draw circle outline (Vector version) */
declare function drawCircleLinesV(center: Vector2, radius: number, color: Color): void;
/** Draw ellipse */
declare function drawEllipse(centerX: number, centerY: number, radiusH: number, radiusV: number, color: Color): void;
/** Draw ellipse outline */
declare function drawEllipseLines(centerX: number, centerY: number, radiusH: number, radiusV: number, color: Color): void;
/** Draw ring */
declare function drawRing(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** Draw ring outline */
declare function drawRingLines(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** Draw a color-filled rectangle */
declare function drawRectangle(posX: number, posY: number, width: number, height: number, color: Color): void;
/** Draw a color-filled rectangle (Vector version) */
declare function drawRectangleV(position: Vector2, size: Vector2, color: Color): void;
/** Draw a color-filled rectangle */
declare function drawRectangleRec(rec: Rectangle, color: Color): void;
/** Draw a color-filled rectangle with pro parameters */
declare function drawRectanglePro(rec: Rectangle, origin: Vector2, rotation: number, color: Color): void;
/** Draw a vertical-gradient-filled rectangle */
declare function drawRectangleGradientV(posX: number, posY: number, width: number, height: number, top: Color, bottom: Color): void;
/** Draw a horizontal-gradient-filled rectangle */
declare function drawRectangleGradientH(posX: number, posY: number, width: number, height: number, left: Color, right: Color): void;
/** Draw a gradient-filled rectangle with custom vertex colors */
declare function drawRectangleGradientEx(rec: Rectangle, topLeft: Color, bottomLeft: Color, topRight: Color, bottomRight: Color): void;
/** Draw rectangle outline */
declare function drawRectangleLines(posX: number, posY: number, width: number, height: number, color: Color): void;
/** Draw rectangle outline with extended parameters */
declare function drawRectangleLinesEx(rec: Rectangle, lineThick: number, color: Color): void;
/** Draw rectangle with rounded edges */
declare function drawRectangleRounded(rec: Rectangle, roundness: number, segments: number, color: Color): void;
/** Draw rectangle lines with rounded edges */
declare function drawRectangleRoundedLines(rec: Rectangle, roundness: number, segments: number, color: Color): void;
/** Draw rectangle with rounded edges outline */
declare function drawRectangleRoundedLinesEx(rec: Rectangle, roundness: number, segments: number, lineThick: number, color: Color): void;
/** Draw a color-filled triangle (vertex in counter-clockwise order!) */
declare function drawTriangle(v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** Draw triangle outline (vertex in counter-clockwise order!) */
declare function drawTriangleLines(v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** Draw a regular polygon (Vector version) */
declare function drawPoly(center: Vector2, sides: number, radius: number, rotation: number, color: Color): void;
/** Draw a polygon outline of n sides */
declare function drawPolyLines(center: Vector2, sides: number, radius: number, rotation: number, color: Color): void;
/** Draw a polygon outline of n sides with extended parameters */
declare function drawPolyLinesEx(center: Vector2, sides: number, radius: number, rotation: number, lineThick: number, color: Color): void;
/** Draw spline: Linear, minimum 2 points */
declare function drawSplineLinear(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** Draw spline: B-Spline, minimum 4 points */
declare function drawSplineBasis(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** Draw spline: Catmull-Rom, minimum 4 points */
declare function drawSplineCatmullRom(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...] */
declare function drawSplineBezierQuadratic(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...] */
declare function drawSplineBezierCubic(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** Draw spline segment: Linear, 2 points */
declare function drawSplineSegmentLinear(p1: Vector2, p2: Vector2, thick: number, color: Color): void;
/** Draw spline segment: B-Spline, 4 points */
declare function drawSplineSegmentBasis(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, thick: number, color: Color): void;
/** Draw spline segment: Catmull-Rom, 4 points */
declare function drawSplineSegmentCatmullRom(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, thick: number, color: Color): void;
/** Draw spline segment: Quadratic Bezier, 2 points, 1 control point */
declare function drawSplineSegmentBezierQuadratic(p1: Vector2, c2: Vector2, p3: Vector2, thick: number, color: Color): void;
/** Draw spline segment: Cubic Bezier, 2 points, 2 control points */
declare function drawSplineSegmentBezierCubic(p1: Vector2, c2: Vector2, c3: Vector2, p4: Vector2, thick: number, color: Color): void;
/** Get (evaluate) spline point: Linear */
declare function getSplinePointLinear(startPos: Vector2, endPos: Vector2, t: number): Vector2;
/** Get (evaluate) spline point: B-Spline */
declare function getSplinePointBasis(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, t: number): Vector2;
/** Get (evaluate) spline point: Catmull-Rom */
declare function getSplinePointCatmullRom(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, t: number): Vector2;
/** Get (evaluate) spline point: Quadratic Bezier */
declare function getSplinePointBezierQuad(p1: Vector2, c2: Vector2, p3: Vector2, t: number): Vector2;
/** Get (evaluate) spline point: Cubic Bezier */
declare function getSplinePointBezierCubic(p1: Vector2, c2: Vector2, c3: Vector2, p4: Vector2, t: number): Vector2;
/** Check collision between two rectangles */
declare function checkCollisionRecs(rec1: Rectangle, rec2: Rectangle): boolean;
/** Check collision between two circles */
declare function checkCollisionCircles(center1: Vector2, radius1: number, center2: Vector2, radius2: number): boolean;
/** Check collision between circle and rectangle */
declare function checkCollisionCircleRec(center: Vector2, radius: number, rec: Rectangle): boolean;
/** Check if circle collides with a line created betweeen two points [p1] and [p2] */
declare function checkCollisionCircleLine(center: Vector2, radius: number, p1: Vector2, p2: Vector2): boolean;
/** Check if point is inside rectangle */
declare function checkCollisionPointRec(point: Vector2, rec: Rectangle): boolean;
/** Check if point is inside circle */
declare function checkCollisionPointCircle(point: Vector2, center: Vector2, radius: number): boolean;
/** Check if point is inside a triangle */
declare function checkCollisionPointTriangle(point: Vector2, p1: Vector2, p2: Vector2, p3: Vector2): boolean;
/** Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold] */
declare function checkCollisionPointLine(point: Vector2, p1: Vector2, p2: Vector2, threshold: number): boolean;
/** Get collision rectangle for two rectangles collision */
declare function getCollisionRec(rec1: Rectangle, rec2: Rectangle): Rectangle;
/** Load image from file into CPU memory (RAM) */
declare function loadImage(fileName: string | undefined | null): Image;
/** Load image from RAW file data */
declare function loadImageRaw(fileName: string | undefined | null, width: number, height: number, format: number, headerSize: number): Image;
/** Load image sequence from memory buffer */
declare function loadImageAnimFromMemory(fileType: string | undefined | null, fileData: ArrayBuffer, dataSize: number, frames: int &): Image;
/** Load image from memory buffer, fileType refers to extension: i.e. '.png' */
declare function loadImageFromMemory(fileType: string | undefined | null, fileData: ArrayBuffer, dataSize: number): Image;
/** Load image from GPU texture data */
declare function loadImageFromTexture(texture: Texture): Image;
/** Load image from screen buffer and (screenshot) */
declare function loadImageFromScreen(): Image;
/** Check if an image is valid (data and parameters) */
declare function isImageValid(image: Image): boolean;
/** Unload image from CPU memory (RAM) */
declare function unloadImage(image: Image): void;
/** Export image data to file, returns true on success */
declare function exportImage(image: Image, fileName: string | undefined | null): boolean;
/** Export image to memory buffer */
declare function exportImageToMemory(image: Image, fileType: string | undefined | null, fileSize: int &): ArrayBuffer;
/** Generate image: plain color */
declare function genImageColor(width: number, height: number, color: Color): Image;
/** Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient */
declare function genImageGradientLinear(width: number, height: number, direction: number, start: Color, end: Color): Image;
/** Generate image: radial gradient */
declare function genImageGradientRadial(width: number, height: number, density: number, inner: Color, outer: Color): Image;
/** Generate image: square gradient */
declare function genImageGradientSquare(width: number, height: number, density: number, inner: Color, outer: Color): Image;
/** Generate image: checked */
declare function genImageChecked(width: number, height: number, checksX: number, checksY: number, col1: Color, col2: Color): Image;
/** Generate image: white noise */
declare function genImageWhiteNoise(width: number, height: number, factor: number): Image;
/** Generate image: perlin noise */
declare function genImagePerlinNoise(width: number, height: number, offsetX: number, offsetY: number, scale: number): Image;
/** Generate image: cellular algorithm, bigger tileSize means bigger cells */
declare function genImageCellular(width: number, height: number, tileSize: number): Image;
/** Generate image: grayscale image from text data */
declare function genImageText(width: number, height: number, text: string | undefined | null): Image;
/** Create an image duplicate (useful for transformations) */
declare function imageCopy(image: Image): Image;
/** Create an image from another image piece */
declare function imageFromImage(image: Image, rec: Rectangle): Image;
/** Create an image from a selected channel of another image (GRAYSCALE) */
declare function imageFromChannel(image: Image, selectedChannel: number): Image;
/** Create an image from text (default font) */
declare function imageText(text: string | undefined | null, fontSize: number, color: Color): Image;
/** Create an image from text (custom sprite font) */
declare function imageTextEx(font: Font, text: string | undefined | null, fontSize: number, spacing: number, tint: Color): Image;
/** Convert image data to desired format */
declare function imageFormat(image: Image &, newFormat: number): void;
/** Convert image to POT (power-of-two) */
declare function imageToPOT(image: Image &, fill: Color): void;
/** Crop an image to a defined rectangle */
declare function imageCrop(image: Image &, crop: Rectangle): void;
/** Crop image depending on alpha value */
declare function imageAlphaCrop(image: Image &, threshold: number): void;
/** Clear alpha channel to desired color */
declare function imageAlphaClear(image: Image &, color: Color, threshold: number): void;
/** Apply alpha mask to image */
declare function imageAlphaMask(image: Image &, alphaMask: Image): void;
/** Premultiply alpha channel */
declare function imageAlphaPremultiply(image: Image &): void;
/** Apply Gaussian blur using a box blur approximation */
declare function imageBlurGaussian(image: Image &, blurSize: number): void;
/** Apply custom square convolution kernel to image */
declare function imageKernelConvolution(image: Image &, kernel: float, kernelSize: number): void;
/** Resize image (Bicubic scaling algorithm) */
declare function imageResize(image: Image &, newWidth: number, newHeight: number): void;
/** Resize image (Nearest-Neighbor scaling algorithm) */
declare function imageResizeNN(image: Image &, newWidth: number, newHeight: number): void;
/** Resize canvas and fill with color */
declare function imageResizeCanvas(image: Image &, newWidth: number, newHeight: number, offsetX: number, offsetY: number, fill: Color): void;
/** Compute all mipmap levels for a provided image */
declare function imageMipmaps(image: Image &): void;
/** Dither image data to 16bpp or lower (Floyd-Steinberg dithering) */
declare function imageDither(image: Image &, rBpp: number, gBpp: number, bBpp: number, aBpp: number): void;
/** Flip image vertically */
declare function imageFlipVertical(image: Image &): void;
/** Flip image horizontally */
declare function imageFlipHorizontal(image: Image &): void;
/** Rotate image by input angle in degrees (-359 to 359) */
declare function imageRotate(image: Image &, degrees: number): void;
/** Rotate image clockwise 90deg */
declare function imageRotateCW(image: Image &): void;
/** Rotate image counter-clockwise 90deg */
declare function imageRotateCCW(image: Image &): void;
/** Modify image color: tint */
declare function imageColorTint(image: Image &, color: Color): void;
/** Modify image color: invert */
declare function imageColorInvert(image: Image &): void;
/** Modify image color: grayscale */
declare function imageColorGrayscale(image: Image &): void;
/** Modify image color: contrast (-100 to 100) */
declare function imageColorContrast(image: Image &, contrast: number): void;
/** Modify image color: brightness (-255 to 255) */
declare function imageColorBrightness(image: Image &, brightness: number): void;
/** Modify image color: replace color */
declare function imageColorReplace(image: Image &, color: Color, replace: Color): void;
/** Load color data from image as a Color array (RGBA - 32bit) */
declare function loadImageColors(image: Image): ArrayBuffer;
/** Get image alpha border rectangle */
declare function getImageAlphaBorder(image: Image, threshold: number): Rectangle;
/** Get image pixel color at (x, y) position */
declare function getImageColor(image: Image, x: number, y: number): Color;
/** Clear image background with given color */
declare function imageClearBackground(dst: Image &, color: Color): void;
/** Draw pixel within an image */
declare function imageDrawPixel(dst: Image &, posX: number, posY: number, color: Color): void;
/** Draw pixel within an image (Vector version) */
declare function imageDrawPixelV(dst: Image &, position: Vector2, color: Color): void;
/** Draw line within an image */
declare function imageDrawLine(dst: Image &, startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void;
/** Draw line within an image (Vector version) */
declare function imageDrawLineV(dst: Image &, start: Vector2, end: Vector2, color: Color): void;
/** Draw a line defining thickness within an image */
declare function imageDrawLineEx(dst: Image &, start: Vector2, end: Vector2, thick: number, color: Color): void;
/** Draw a filled circle within an image */
declare function imageDrawCircle(dst: Image &, centerX: number, centerY: number, radius: number, color: Color): void;
/** Draw a filled circle within an image (Vector version) */
declare function imageDrawCircleV(dst: Image &, center: Vector2, radius: number, color: Color): void;
/** Draw circle outline within an image */
declare function imageDrawCircleLines(dst: Image &, centerX: number, centerY: number, radius: number, color: Color): void;
/** Draw circle outline within an image (Vector version) */
declare function imageDrawCircleLinesV(dst: Image &, center: Vector2, radius: number, color: Color): void;
/** Draw rectangle within an image */
declare function imageDrawRectangle(dst: Image &, posX: number, posY: number, width: number, height: number, color: Color): void;
/** Draw rectangle within an image (Vector version) */
declare function imageDrawRectangleV(dst: Image &, position: Vector2, size: Vector2, color: Color): void;
/** Draw rectangle within an image */
declare function imageDrawRectangleRec(dst: Image &, rec: Rectangle, color: Color): void;
/** Draw rectangle lines within an image */
declare function imageDrawRectangleLines(dst: Image &, rec: Rectangle, thick: number, color: Color): void;
/** Draw triangle within an image */
declare function imageDrawTriangle(dst: Image &, v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** Draw triangle with interpolated colors within an image */
declare function imageDrawTriangleEx(dst: Image &, v1: Vector2, v2: Vector2, v3: Vector2, c1: Color, c2: Color, c3: Color): void;
/** Draw triangle outline within an image */
declare function imageDrawTriangleLines(dst: Image &, v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** Draw a triangle fan defined by points within an image (first vertex is the center) */
declare function imageDrawTriangleFan(dst: Image &, points: Vector2, pointCount: number, color: Color): void;
/** Draw a triangle strip defined by points within an image */
declare function imageDrawTriangleStrip(dst: Image &, points: Vector2, pointCount: number, color: Color): void;
/** Draw a source image within a destination image (tint applied to source) */
declare function imageDraw(dst: Image &, src: Image, srcRec: Rectangle, dstRec: Rectangle, tint: Color): void;
/** Draw text (using default font) within an image (destination) */
declare function imageDrawText(dst: Image &, text: string | undefined | null, posX: number, posY: number, fontSize: number, color: Color): void;
/** Draw text (custom sprite font) within an image (destination) */
declare function imageDrawTextEx(dst: Image &, font: Font, text: string | undefined | null, position: Vector2, fontSize: number, spacing: number, tint: Color): void;
/** Load texture from file into GPU memory (VRAM) */
declare function loadTexture(fileName: string | undefined | null): Texture;
/** Load texture from image data */
declare function loadTextureFromImage(image: Image): Texture;
/** Load cubemap from image, multiple image cubemap layouts supported */
declare function loadTextureCubemap(image: Image, layout: number): Texture;
/** Load texture for rendering (framebuffer) */
declare function loadRenderTexture(width: number, height: number): RenderTexture;
/** Check if a texture is valid (loaded in GPU) */
declare function isTextureValid(texture: Texture): boolean;
/** Unload texture from GPU memory (VRAM) */
declare function unloadTexture(texture: Texture): void;
/** Check if a render texture is valid (loaded in GPU) */
declare function isRenderTextureValid(target: RenderTexture): boolean;
/** Unload render texture from GPU memory (VRAM) */
declare function unloadRenderTexture(target: RenderTexture): void;
/** Update GPU texture with new data */
declare function updateTexture(texture: Texture, pixels: any): void;
/** Update GPU texture rectangle with new data */
declare function updateTextureRec(texture: Texture, rec: Rectangle, pixels: any): void;
/** Generate GPU mipmaps for a texture */
declare function genTextureMipmaps(texture: Texture2D &): void;
/** Set texture scaling filter mode */
declare function setTextureFilter(texture: Texture, filter: number): void;
/** Set texture wrapping mode */
declare function setTextureWrap(texture: Texture, wrap: number): void;
/** Draw a Texture2D */
declare function drawTexture(texture: Texture, posX: number, posY: number, tint: Color): void;
/** Draw a Texture2D with position defined as Vector2 */
declare function drawTextureV(texture: Texture, position: Vector2, tint: Color): void;
/** Draw a Texture2D with extended parameters */
declare function drawTextureEx(texture: Texture, position: Vector2, rotation: number, scale: number, tint: Color): void;
/** Draw a part of a texture defined by a rectangle */
declare function drawTextureRec(texture: Texture, source: Rectangle, position: Vector2, tint: Color): void;
/** Draw a part of a texture defined by a rectangle with 'pro' parameters */
declare function drawTexturePro(texture: Texture, source: Rectangle, dest: Rectangle, origin: Vector2, rotation: number, tint: Color): void;
/** Draws a texture (or part of it) that stretches or shrinks nicely */
declare function drawTextureNPatch(texture: Texture, nPatchInfo: NPatchInfo, dest: Rectangle, origin: Vector2, rotation: number, tint: Color): void;
/** Check if two colors are equal */
declare function colorIsEqual(col1: Color, col2: Color): boolean;
/** Get color with alpha applied, alpha goes from 0.0f to 1.0f */
declare function fade(color: Color, alpha: number): Color;
/** Get hexadecimal value for a Color (0xRRGGBBAA) */
declare function colorToInt(color: Color): number;
/** Get Color normalized as float [0..1] */
declare function colorNormalize(color: Color): Vector4;
/** Get Color from normalized values [0..1] */
declare function colorFromNormalized(normalized: Vector4): Color;
/** Get HSV values for a Color, hue [0..360], saturation/value [0..1] */
declare function colorToHSV(color: Color): Vector3;
/** Get a Color from HSV values, hue [0..360], saturation/value [0..1] */
declare function colorFromHSV(hue: number, saturation: number, value: number): Color;
/** Get color multiplied with another color */
declare function colorTint(color: Color, tint: Color): Color;
/** Get color with brightness correction, brightness factor goes from -1.0f to 1.0f */
declare function colorBrightness(color: Color, factor: number): Color;
/** Get color with contrast correction, contrast values between -1.0f and 1.0f */
declare function colorContrast(color: Color, contrast: number): Color;
/** Get color with alpha applied, alpha goes from 0.0f to 1.0f */
declare function colorAlpha(color: Color, alpha: number): Color;
/** Get src alpha-blended into dst color with tint */
declare function colorAlphaBlend(dst: Color, src: Color, tint: Color): Color;
/** Get color lerp interpolation between two colors, factor [0.0f..1.0f] */
declare function colorLerp(color1: Color, color2: Color, factor: number): Color;
/** Get Color structure from hexadecimal value */
declare function getColor(hexValue: number): Color;
/** Get pixel data size in bytes for certain format */
declare function getPixelDataSize(width: number, height: number, format: number): number;
/** Get the default Font */
declare function getFontDefault(): Font;
/** Load font from file into GPU memory (VRAM) */
declare function loadFont(fileName: string | undefined | null): Font;
/** Load font from file with extended parameters, use NULL for codepoints and 0 for codepointCount to load the default character set, font size is provided in pixels height */
declare function loadFontEx(fileName: string | undefined | null, fontSize: number, codepoints: int, codepointCount: number): Font;
/** Load font from Image (XNA style) */
declare function loadFontFromImage(image: Image, key: Color, firstChar: number): Font;
/** Check if a font is valid (font data loaded, WARNING: GPU texture not checked) */
declare function isFontValid(font: Font): boolean;
/** Unload font from GPU memory (VRAM) */
declare function unloadFont(font: Font): void;
/** Draw current FPS */
declare function drawFPS(posX: number, posY: number): void;
/** Draw text (using default font) */
declare function drawText(text: string | undefined | null, posX: number, posY: number, fontSize: number, color: Color): void;
/** Draw text using font and additional parameters */
declare function drawTextEx(font: Font, text: string | undefined | null, position: Vector2, fontSize: number, spacing: number, tint: Color): void;
/** Draw text using Font and pro parameters (rotation) */
declare function drawTextPro(font: Font, text: string | undefined | null, position: Vector2, origin: Vector2, rotation: number, fontSize: number, spacing: number, tint: Color): void;
/** Draw one character (codepoint) */
declare function drawTextCodepoint(font: Font, codepoint: number, position: Vector2, fontSize: number, tint: Color): void;
/** Set vertical line spacing when drawing with line-breaks */
declare function setTextLineSpacing(spacing: number): void;
/** Measure string width for default font */
declare function measureText(text: string | undefined | null, fontSize: number): number;
/** Measure string size for Font */
declare function measureTextEx(font: Font, text: string | undefined | null, fontSize: number, spacing: number): Vector2;
/** Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found */
declare function getGlyphIndex(font: Font, codepoint: number): number;
/** Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found */
declare function getGlyphAtlasRec(font: Font, codepoint: number): Rectangle;
/** Copy one string to another, returns bytes copied */
declare function textCopy(dst: char &, src: string | undefined | null): number;
/** Check if two text string are equal */
declare function textIsEqual(text1: string | undefined | null, text2: string | undefined | null): boolean;
/** Get text length, checks for '\0' ending */
declare function textLength(text: string | undefined | null): number;
/** Text formatting with variables (sprintf() style) */
declare function textFormat(text: string | undefined | null, args: ...): string | undefined | null;
/** Get a piece of a text string */
declare function textSubtext(text: string | undefined | null, position: number, length: number): string | undefined | null;
/** Replace text string (WARNING: memory must be freed!) */
declare function textReplace(text: string | undefined | null, replace: string | undefined | null, by: string | undefined | null): string | undefined | null;
/** Insert text in a position (WARNING: memory must be freed!) */
declare function textInsert(text: string | undefined | null, insert: string | undefined | null, position: number): string | undefined | null;
/** Join text strings with delimiter */
declare function textJoin(textList: char *, count: number, delimiter: string | undefined | null): string | undefined | null;
/** Split text into multiple strings */
declare function textSplit(text: string | undefined | null, delimiter: char, count: int &): char *;
/** Append text at specific position and move cursor! */
declare function textAppend(text: string | undefined | null, append: string | undefined | null, position: int &): void;
/** Find first text occurrence within a string */
declare function textFindIndex(text: string | undefined | null, find: string | undefined | null): number;
/** Get upper case version of provided string */
declare function textToUpper(text: string | undefined | null): string | undefined | null;
/** Get lower case version of provided string */
declare function textToLower(text: string | undefined | null): string | undefined | null;
/** Get Pascal case notation version of provided string */
declare function textToPascal(text: string | undefined | null): string | undefined | null;
/** Get Snake case notation version of provided string */
declare function textToSnake(text: string | undefined | null): string | undefined | null;
/** Get Camel case notation version of provided string */
declare function textToCamel(text: string | undefined | null): string | undefined | null;
/** Get integer value from text */
declare function textToInteger(text: string | undefined | null): number;
/** Get float value from text */
declare function textToFloat(text: string | undefined | null): number;
/** Draw a line in 3D world space */
declare function drawLine3D(startPos: Vector3, endPos: Vector3, color: Color): void;
/** Draw a point in 3D space, actually a small line */
declare function drawPoint3D(position: Vector3, color: Color): void;
/** Draw a circle in 3D world space */
declare function drawCircle3D(center: Vector3, radius: number, rotationAxis: Vector3, rotationAngle: number, color: Color): void;
/** Draw a color-filled triangle (vertex in counter-clockwise order!) */
declare function drawTriangle3D(v1: Vector3, v2: Vector3, v3: Vector3, color: Color): void;
/** Draw cube */
declare function drawCube(position: Vector3, width: number, height: number, length: number, color: Color): void;
/** Draw cube (Vector version) */
declare function drawCubeV(position: Vector3, size: Vector3, color: Color): void;
/** Draw cube wires */
declare function drawCubeWires(position: Vector3, width: number, height: number, length: number, color: Color): void;
/** Draw cube wires (Vector version) */
declare function drawCubeWiresV(position: Vector3, size: Vector3, color: Color): void;
/** Draw sphere */
declare function drawSphere(centerPos: Vector3, radius: number, color: Color): void;
/** Draw sphere with extended parameters */
declare function drawSphereEx(centerPos: Vector3, radius: number, rings: number, slices: number, color: Color): void;
/** Draw sphere wires */
declare function drawSphereWires(centerPos: Vector3, radius: number, rings: number, slices: number, color: Color): void;
/** Draw a cylinder/cone */
declare function drawCylinder(position: Vector3, radiusTop: number, radiusBottom: number, height: number, slices: number, color: Color): void;
/** Draw a cylinder with base at startPos and top at endPos */
declare function drawCylinderEx(startPos: Vector3, endPos: Vector3, startRadius: number, endRadius: number, sides: number, color: Color): void;
/** Draw a cylinder/cone wires */
declare function drawCylinderWires(position: Vector3, radiusTop: number, radiusBottom: number, height: number, slices: number, color: Color): void;
/** Draw a cylinder wires with base at startPos and top at endPos */
declare function drawCylinderWiresEx(startPos: Vector3, endPos: Vector3, startRadius: number, endRadius: number, sides: number, color: Color): void;
/** Draw a capsule with the center of its sphere caps at startPos and endPos */
declare function drawCapsule(startPos: Vector3, endPos: Vector3, radius: number, slices: number, rings: number, color: Color): void;
/** Draw capsule wireframe with the center of its sphere caps at startPos and endPos */
declare function drawCapsuleWires(startPos: Vector3, endPos: Vector3, radius: number, slices: number, rings: number, color: Color): void;
/** Draw a plane XZ */
declare function drawPlane(centerPos: Vector3, size: Vector2, color: Color): void;
/** Draw a ray line */
declare function drawRay(ray: Ray, color: Color): void;
/** Draw a grid (centered at (0, 0, 0)) */
declare function drawGrid(slices: number, spacing: number): void;
/** Load model from files (meshes and materials) */
declare function loadModel(fileName: string | undefined | null): Model;
/** Load model from generated mesh (default material) */
declare function loadModelFromMesh(mesh: Mesh): Model;
/** Check if a model is valid (loaded in GPU, VAO/VBOs) */
declare function isModelValid(model: Model): boolean;
/** Unload model (including meshes) from memory (RAM and/or VRAM) */
declare function unloadModel(model: Model): void;
/** Compute model bounding box limits (considers all meshes) */
declare function getModelBoundingBox(model: Model): BoundingBox;
/** Draw a model (with texture if set) */
declare function drawModel(model: Model, position: Vector3, scale: number, tint: Color): void;
/** Draw a model with extended parameters */
declare function drawModelEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
/** Draw a model wires (with texture if set) */
declare function drawModelWires(model: Model, position: Vector3, scale: number, tint: Color): void;
/** Draw a model wires (with texture if set) with extended parameters */
declare function drawModelWiresEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
/** Draw a model as points */
declare function drawModelPoints(model: Model, position: Vector3, scale: number, tint: Color): void;
/** Draw a model as points with extended parameters */
declare function drawModelPointsEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
/** Draw bounding box (wires) */
declare function drawBoundingBox(box: BoundingBox, color: Color): void;
/** Draw a billboard texture */
declare function drawBillboard(camera: Camera3D, texture: Texture, position: Vector3, scale: number, tint: Color): void;
/** Draw a billboard texture defined by source */
declare function drawBillboardRec(camera: Camera3D, texture: Texture, source: Rectangle, position: Vector3, size: Vector2, tint: Color): void;
/** Draw a billboard texture defined by source and rotation */
declare function drawBillboardPro(camera: Camera3D, texture: Texture, source: Rectangle, position: Vector3, up: Vector3, size: Vector2, origin: Vector2, rotation: number, tint: Color): void;
/** Upload mesh vertex data in GPU and provide VAO/VBO ids */
declare function uploadMesh(mesh: Mesh &, dynamic: boolean): void;
/** Update mesh vertex data in GPU for a specific buffer index */
declare function updateMeshBuffer(mesh: Mesh, index: number, data: any, dataSize: number, offset: number): void;
/** Unload mesh data from CPU and GPU */
declare function unloadMesh(mesh: Mesh): void;
/** Draw a 3d mesh with material and transform */
declare function drawMesh(mesh: Mesh, material: Material, transform: Matrix): void;
/** Draw multiple mesh instances with material and different transforms */
declare function drawMeshInstanced(mesh: Mesh, material: Material, transforms: Matrix, instances: number): void;
/** Compute mesh bounding box limits */
declare function getMeshBoundingBox(mesh: Mesh): BoundingBox;
/** Compute mesh tangents */
declare function genMeshTangents(mesh: Mesh &): void;
/** Export mesh data to file, returns true on success */
declare function exportMesh(mesh: Mesh, fileName: string | undefined | null): boolean;
/** Export mesh as code file (.h) defining multiple arrays of vertex attributes */
declare function exportMeshAsCode(mesh: Mesh, fileName: string | undefined | null): boolean;
/** Generate polygonal mesh */
declare function genMeshPoly(sides: number, radius: number): Mesh;
/** Generate plane mesh (with subdivisions) */
declare function genMeshPlane(width: number, length: number, resX: number, resZ: number): Mesh;
/** Generate cuboid mesh */
declare function genMeshCube(width: number, height: number, length: number): Mesh;
/** Generate sphere mesh (standard sphere) */
declare function genMeshSphere(radius: number, rings: number, slices: number): Mesh;
/** Generate half-sphere mesh (no bottom cap) */
declare function genMeshHemiSphere(radius: number, rings: number, slices: number): Mesh;
/** Generate cylinder mesh */
declare function genMeshCylinder(radius: number, height: number, slices: number): Mesh;
/** Generate cone/pyramid mesh */
declare function genMeshCone(radius: number, height: number, slices: number): Mesh;
/** Generate torus mesh */
declare function genMeshTorus(radius: number, size: number, radSeg: number, sides: number): Mesh;
/** Generate trefoil knot mesh */
declare function genMeshKnot(radius: number, size: number, radSeg: number, sides: number): Mesh;
/** Generate heightmap mesh from image data */
declare function genMeshHeightmap(heightmap: Image, size: Vector3): Mesh;
/** Generate cubes-based map mesh from image data */
declare function genMeshCubicmap(cubicmap: Image, cubeSize: Vector3): Mesh;
/** Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps) */
declare function loadMaterialDefault(): Material;
/** Check if a material is valid (shader assigned, map textures loaded in GPU) */
declare function isMaterialValid(material: Material): boolean;
/** Unload material from GPU memory (VRAM) */
declare function unloadMaterial(material: Material): void;
/** Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...) */
declare function setMaterialTexture(material: Material &, mapType: number, texture: Texture): void;
/** Set material for a mesh */
declare function setModelMeshMaterial(model: Model &, meshId: number, materialId: number): void;
/** Update model animation mesh bone matrices (GPU skinning) */
declare function updateModelAnimationBones(model: Model, anim: ModelAnimation, frame: number): void;
/** Check collision between two spheres */
declare function checkCollisionSpheres(center1: Vector3, radius1: number, center2: Vector3, radius2: number): boolean;
/** Check collision between two bounding boxes */
declare function checkCollisionBoxes(box1: BoundingBox, box2: BoundingBox): boolean;
/** Check collision between box and sphere */
declare function checkCollisionBoxSphere(box: BoundingBox, center: Vector3, radius: number): boolean;
/** Get collision info between ray and sphere */
declare function getRayCollisionSphere(ray: Ray, center: Vector3, radius: number): RayCollision;
/** Get collision info between ray and box */
declare function getRayCollisionBox(ray: Ray, box: BoundingBox): RayCollision;
/** Get collision info between ray and mesh */
declare function getRayCollisionMesh(ray: Ray, mesh: Mesh, transform: Matrix): RayCollision;
/** Get collision info between ray and triangle */
declare function getRayCollisionTriangle(ray: Ray, p1: Vector3, p2: Vector3, p3: Vector3): RayCollision;
/** Get collision info between ray and quad */
declare function getRayCollisionQuad(ray: Ray, p1: Vector3, p2: Vector3, p3: Vector3, p4: Vector3): RayCollision;
/** Initialize audio device and context */
declare function initAudioDevice(): void;
/** Close the audio device and context */
declare function closeAudioDevice(): void;
/** Check if audio device has been initialized successfully */
declare function isAudioDeviceReady(): boolean;
/** Set master volume (listener) */
declare function setMasterVolume(volume: number): void;
/** Get master volume (listener) */
declare function getMasterVolume(): number;
/** Load wave data from file */
declare function loadWave(fileName: string | undefined | null): Wave;
/** Load wave from memory buffer, fileType refers to extension: i.e. '.wav' */
declare function loadWaveFromMemory(fileType: string | undefined | null, fileData: ArrayBuffer, dataSize: number): Wave;
/** Checks if wave data is valid (data loaded and parameters) */
declare function isWaveValid(wave: Wave): boolean;
/** Load sound from file */
declare function loadSound(fileName: string | undefined | null): Sound;
/** Load sound from wave data */
declare function loadSoundFromWave(wave: Wave): Sound;
/** Create a new sound that shares the same sample data as the source sound, does not own the sound data */
declare function loadSoundAlias(source: Sound): Sound;
/** Checks if a sound is valid (data loaded and buffers initialized) */
declare function isSoundValid(sound: Sound): boolean;
/** Update sound buffer with new data */
declare function updateSound(sound: Sound, data: any, sampleCount: number): void;
/** Unload wave data */
declare function unloadWave(wave: Wave): void;
/** Unload sound */
declare function unloadSound(sound: Sound): void;
/** Unload a sound alias (does not deallocate sample data) */
declare function unloadSoundAlias(alias: Sound): void;
/** Export wave data to file, returns true on success */
declare function exportWave(wave: Wave, fileName: string | undefined | null): boolean;
/** Play a sound */
declare function playSound(sound: Sound): void;
/** Stop playing a sound */
declare function stopSound(sound: Sound): void;
/** Pause a sound */
declare function pauseSound(sound: Sound): void;
/** Resume a paused sound */
declare function resumeSound(sound: Sound): void;
/** Check if a sound is currently playing */
declare function isSoundPlaying(sound: Sound): boolean;
/** Set volume for a sound (1.0 is max level) */
declare function setSoundVolume(sound: Sound, volume: number): void;
/** Set pitch for a sound (1.0 is base level) */
declare function setSoundPitch(sound: Sound, pitch: number): void;
/** Set pan for a sound (0.5 is center) */
declare function setSoundPan(sound: Sound, pan: number): void;
/** Copy a wave to a new wave */
declare function waveCopy(wave: Wave): Wave;
/** Crop a wave to defined frames range */
declare function waveCrop(wave: Wave &, initFrame: number, finalFrame: number): void;
/** Convert wave data to desired format */
declare function waveFormat(wave: Wave &, sampleRate: number, sampleSize: number, channels: number): void;
/** Load samples data from wave as a 32bit float data array */
declare function loadWaveSamples(wave: Wave): ArrayBuffer;
/** Unload samples data loaded with LoadWaveSamples() */
declare function unloadWaveSamples(samples: float &): void;
/** Load music stream from file */
declare function loadMusicStream(fileName: string | undefined | null): Music;
/** Load music stream from data */
declare function loadMusicStreamFromMemory(fileType: string | undefined | null, data: ArrayBuffer, dataSize: number): Music;
/** Checks if a music stream is valid (context and buffers initialized) */
declare function isMusicValid(music: Music): boolean;
/** Unload music stream */
declare function unloadMusicStream(music: Music): void;
/** Start music playing */
declare function playMusicStream(music: Music): void;
/** Check if music is playing */
declare function isMusicStreamPlaying(music: Music): boolean;
/** Updates buffers for music streaming */
declare function updateMusicStream(music: Music): void;
/** Stop music playing */
declare function stopMusicStream(music: Music): void;
/** Pause music playing */
declare function pauseMusicStream(music: Music): void;
/** Resume playing paused music */
declare function resumeMusicStream(music: Music): void;
/** Seek music to a position (in seconds) */
declare function seekMusicStream(music: Music, position: number): void;
/** Set volume for music (1.0 is max level) */
declare function setMusicVolume(music: Music, volume: number): void;
/** Set pitch for a music (1.0 is base level) */
declare function setMusicPitch(music: Music, pitch: number): void;
/** Set pan for a music (0.5 is center) */
declare function setMusicPan(music: Music, pan: number): void;
/** Get music time length (in seconds) */
declare function getMusicTimeLength(music: Music): number;
/** Get current music time played (in seconds) */
declare function getMusicTimePlayed(music: Music): number;
/** Load audio stream (to stream raw audio pcm data) */
declare function loadAudioStream(sampleRate: number, sampleSize: number, channels: number): AudioStream;
/** Checks if an audio stream is valid (buffers initialized) */
declare function isAudioStreamValid(stream: AudioStream): boolean;
/** Unload audio stream and free memory */
declare function unloadAudioStream(stream: AudioStream): void;
/** Update audio stream buffers with data */
declare function updateAudioStream(stream: AudioStream, data: any, frameCount: number): void;
/** Check if any audio stream buffers requires refill */
declare function isAudioStreamProcessed(stream: AudioStream): boolean;
/** Play audio stream */
declare function playAudioStream(stream: AudioStream): void;
/** Pause audio stream */
declare function pauseAudioStream(stream: AudioStream): void;
/** Resume audio stream */
declare function resumeAudioStream(stream: AudioStream): void;
/** Check if audio stream is playing */
declare function isAudioStreamPlaying(stream: AudioStream): boolean;
/** Stop audio stream */
declare function stopAudioStream(stream: AudioStream): void;
/** Set volume for audio stream (1.0 is max level) */
declare function setAudioStreamVolume(stream: AudioStream, volume: number): void;
/** Set pitch for audio stream (1.0 is base level) */
declare function setAudioStreamPitch(stream: AudioStream, pitch: number): void;
/** Set pan for audio stream (0.5 is centered) */
declare function setAudioStreamPan(stream: AudioStream, pan: number): void;
/** Default size for new audio streams */
declare function setAudioStreamBufferSizeDefault(size: number): void;
/** Attach audio stream processor to the entire audio pipeline, receives the samples as 'float' */
declare function attachAudioMixedProcessor(processor: AudioMixedProcessor): void;
/** Detach audio stream processor from the entire audio pipeline */
declare function detachAudioMixedProcessor(processor: AudioCallback): void;
/** Set to try enabling V-Sync on GPU */
declare var FLAG_VSYNC_HINT: number;
/** Set to run program in fullscreen */
declare var FLAG_FULLSCREEN_MODE: number;
/** Set to allow resizable window */
declare var FLAG_WINDOW_RESIZABLE: number;
/** Set to disable window decoration (frame and buttons) */
declare var FLAG_WINDOW_UNDECORATED: number;
/** Set to hide window */
declare var FLAG_WINDOW_HIDDEN: number;
/** Set to minimize window (iconify) */
declare var FLAG_WINDOW_MINIMIZED: number;
/** Set to maximize window (expanded to monitor) */
declare var FLAG_WINDOW_MAXIMIZED: number;
/** Set to window non focused */
declare var FLAG_WINDOW_UNFOCUSED: number;
/** Set to window always on top */
declare var FLAG_WINDOW_TOPMOST: number;
/** Set to allow windows running while minimized */
declare var FLAG_WINDOW_ALWAYS_RUN: number;
/** Set to allow transparent framebuffer */
declare var FLAG_WINDOW_TRANSPARENT: number;
/** Set to support HighDPI */
declare var FLAG_WINDOW_HIGHDPI: number;
/** Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED */
declare var FLAG_WINDOW_MOUSE_PASSTHROUGH: number;
/** Set to run program in borderless windowed mode */
declare var FLAG_BORDERLESS_WINDOWED_MODE: number;
/** Set to try enabling MSAA 4X */
declare var FLAG_MSAA_4X_HINT: number;
/** Set to try enabling interlaced video format (for V3D) */
declare var FLAG_INTERLACED_HINT: number;
/** Display all logs */
declare var LOG_ALL: number;
/** Trace logging, intended for internal use only */
declare var LOG_TRACE: number;
/** Debug logging, used for internal debugging, it should be disabled on release builds */
declare var LOG_DEBUG: number;
/** Info logging, used for program execution info */
declare var LOG_INFO: number;
/** Warning logging, used on recoverable failures */
declare var LOG_WARNING: number;
/** Error logging, used on unrecoverable failures */
declare var LOG_ERROR: number;
/** Fatal logging, used to abort program: exit(EXIT_FAILURE) */
declare var LOG_FATAL: number;
/** Disable logging */
declare var LOG_NONE: number;
/** Key: NULL, used for no key pressed */
declare var KEY_NULL: number;
/** Key: ' */
declare var KEY_APOSTROPHE: number;
/** Key: , */
declare var KEY_COMMA: number;
/** Key: - */
declare var KEY_MINUS: number;
/** Key: . */
declare var KEY_PERIOD: number;
/** Key: / */
declare var KEY_SLASH: number;
/** Key: 0 */
declare var KEY_ZERO: number;
/** Key: 1 */
declare var KEY_ONE: number;
/** Key: 2 */
declare var KEY_TWO: number;
/** Key: 3 */
declare var KEY_THREE: number;
/** Key: 4 */
declare var KEY_FOUR: number;
/** Key: 5 */
declare var KEY_FIVE: number;
/** Key: 6 */
declare var KEY_SIX: number;
/** Key: 7 */
declare var KEY_SEVEN: number;
/** Key: 8 */
declare var KEY_EIGHT: number;
/** Key: 9 */
declare var KEY_NINE: number;
/** Key: ; */
declare var KEY_SEMICOLON: number;
/** Key: = */
declare var KEY_EQUAL: number;
/** Key: A | a */
declare var KEY_A: number;
/** Key: B | b */
declare var KEY_B: number;
/** Key: C | c */
declare var KEY_C: number;
/** Key: D | d */
declare var KEY_D: number;
/** Key: E | e */
declare var KEY_E: number;
/** Key: F | f */
declare var KEY_F: number;
/** Key: G | g */
declare var KEY_G: number;
/** Key: H | h */
declare var KEY_H: number;
/** Key: I | i */
declare var KEY_I: number;
/** Key: J | j */
declare var KEY_J: number;
/** Key: K | k */
declare var KEY_K: number;
/** Key: L | l */
declare var KEY_L: number;
/** Key: M | m */
declare var KEY_M: number;
/** Key: N | n */
declare var KEY_N: number;
/** Key: O | o */
declare var KEY_O: number;
/** Key: P | p */
declare var KEY_P: number;
/** Key: Q | q */
declare var KEY_Q: number;
/** Key: R | r */
declare var KEY_R: number;
/** Key: S | s */
declare var KEY_S: number;
/** Key: T | t */
declare var KEY_T: number;
/** Key: U | u */
declare var KEY_U: number;
/** Key: V | v */
declare var KEY_V: number;
/** Key: W | w */
declare var KEY_W: number;
/** Key: X | x */
declare var KEY_X: number;
/** Key: Y | y */
declare var KEY_Y: number;
/** Key: Z | z */
declare var KEY_Z: number;
/** Key: [ */
declare var KEY_LEFT_BRACKET: number;
/** Key: '\' */
declare var KEY_BACKSLASH: number;
/** Key: ] */
declare var KEY_RIGHT_BRACKET: number;
/** Key: ` */
declare var KEY_GRAVE: number;
/** Key: Space */
declare var KEY_SPACE: number;
/** Key: Esc */
declare var KEY_ESCAPE: number;
/** Key: Enter */
declare var KEY_ENTER: number;
/** Key: Tab */
declare var KEY_TAB: number;
/** Key: Backspace */
declare var KEY_BACKSPACE: number;
/** Key: Ins */
declare var KEY_INSERT: number;
/** Key: Del */
declare var KEY_DELETE: number;
/** Key: Cursor right */
declare var KEY_RIGHT: number;
/** Key: Cursor left */
declare var KEY_LEFT: number;
/** Key: Cursor down */
declare var KEY_DOWN: number;
/** Key: Cursor up */
declare var KEY_UP: number;
/** Key: Page up */
declare var KEY_PAGE_UP: number;
/** Key: Page down */
declare var KEY_PAGE_DOWN: number;
/** Key: Home */
declare var KEY_HOME: number;
/** Key: End */
declare var KEY_END: number;
/** Key: Caps lock */
declare var KEY_CAPS_LOCK: number;
/** Key: Scroll down */
declare var KEY_SCROLL_LOCK: number;
/** Key: Num lock */
declare var KEY_NUM_LOCK: number;
/** Key: Print screen */
declare var KEY_PRINT_SCREEN: number;
/** Key: Pause */
declare var KEY_PAUSE: number;
/** Key: F1 */
declare var KEY_F1: number;
/** Key: F2 */
declare var KEY_F2: number;
/** Key: F3 */
declare var KEY_F3: number;
/** Key: F4 */
declare var KEY_F4: number;
/** Key: F5 */
declare var KEY_F5: number;
/** Key: F6 */
declare var KEY_F6: number;
/** Key: F7 */
declare var KEY_F7: number;
/** Key: F8 */
declare var KEY_F8: number;
/** Key: F9 */
declare var KEY_F9: number;
/** Key: F10 */
declare var KEY_F10: number;
/** Key: F11 */
declare var KEY_F11: number;
/** Key: F12 */
declare var KEY_F12: number;
/** Key: Shift left */
declare var KEY_LEFT_SHIFT: number;
/** Key: Control left */
declare var KEY_LEFT_CONTROL: number;
/** Key: Alt left */
declare var KEY_LEFT_ALT: number;
/** Key: Super left */
declare var KEY_LEFT_SUPER: number;
/** Key: Shift right */
declare var KEY_RIGHT_SHIFT: number;
/** Key: Control right */
declare var KEY_RIGHT_CONTROL: number;
/** Key: Alt right */
declare var KEY_RIGHT_ALT: number;
/** Key: Super right */
declare var KEY_RIGHT_SUPER: number;
/** Key: KB menu */
declare var KEY_KB_MENU: number;
/** Key: Keypad 0 */
declare var KEY_KP_0: number;
/** Key: Keypad 1 */
declare var KEY_KP_1: number;
/** Key: Keypad 2 */
declare var KEY_KP_2: number;
/** Key: Keypad 3 */
declare var KEY_KP_3: number;
/** Key: Keypad 4 */
declare var KEY_KP_4: number;
/** Key: Keypad 5 */
declare var KEY_KP_5: number;
/** Key: Keypad 6 */
declare var KEY_KP_6: number;
/** Key: Keypad 7 */
declare var KEY_KP_7: number;
/** Key: Keypad 8 */
declare var KEY_KP_8: number;
/** Key: Keypad 9 */
declare var KEY_KP_9: number;
/** Key: Keypad . */
declare var KEY_KP_DECIMAL: number;
/** Key: Keypad / */
declare var KEY_KP_DIVIDE: number;
/** Key: Keypad * */
declare var KEY_KP_MULTIPLY: number;
/** Key: Keypad - */
declare var KEY_KP_SUBTRACT: number;
/** Key: Keypad + */
declare var KEY_KP_ADD: number;
/** Key: Keypad Enter */
declare var KEY_KP_ENTER: number;
/** Key: Keypad = */
declare var KEY_KP_EQUAL: number;
/** Key: Android back button */
declare var KEY_BACK: number;
/** Key: Android menu button */
declare var KEY_MENU: number;
/** Key: Android volume up button */
declare var KEY_VOLUME_UP: number;
/** Key: Android volume down button */
declare var KEY_VOLUME_DOWN: number;
/** Mouse button left */
declare var MOUSE_BUTTON_LEFT: number;
/** Mouse button right */
declare var MOUSE_BUTTON_RIGHT: number;
/** Mouse button middle (pressed wheel) */
declare var MOUSE_BUTTON_MIDDLE: number;
/** Mouse button side (advanced mouse device) */
declare var MOUSE_BUTTON_SIDE: number;
/** Mouse button extra (advanced mouse device) */
declare var MOUSE_BUTTON_EXTRA: number;
/** Mouse button forward (advanced mouse device) */
declare var MOUSE_BUTTON_FORWARD: number;
/** Mouse button back (advanced mouse device) */
declare var MOUSE_BUTTON_BACK: number;
/** Default pointer shape */
declare var MOUSE_CURSOR_DEFAULT: number;
/** Arrow shape */
declare var MOUSE_CURSOR_ARROW: number;
/** Text writing cursor shape */
declare var MOUSE_CURSOR_IBEAM: number;
/** Cross shape */
declare var MOUSE_CURSOR_CROSSHAIR: number;
/** Pointing hand cursor */
declare var MOUSE_CURSOR_POINTING_HAND: number;
/** Horizontal resize/move arrow shape */
declare var MOUSE_CURSOR_RESIZE_EW: number;
/** Vertical resize/move arrow shape */
declare var MOUSE_CURSOR_RESIZE_NS: number;
/** Top-left to bottom-right diagonal resize/move arrow shape */
declare var MOUSE_CURSOR_RESIZE_NWSE: number;
/** The top-right to bottom-left diagonal resize/move arrow shape */
declare var MOUSE_CURSOR_RESIZE_NESW: number;
/** The omnidirectional resize/move cursor shape */
declare var MOUSE_CURSOR_RESIZE_ALL: number;
/** The operation-not-allowed shape */
declare var MOUSE_CURSOR_NOT_ALLOWED: number;
/** Unknown button, just for error checking */
declare var GAMEPAD_BUTTON_UNKNOWN: number;
/** Gamepad left DPAD up button */
declare var GAMEPAD_BUTTON_LEFT_FACE_UP: number;
/** Gamepad left DPAD right button */
declare var GAMEPAD_BUTTON_LEFT_FACE_RIGHT: number;
/** Gamepad left DPAD down button */
declare var GAMEPAD_BUTTON_LEFT_FACE_DOWN: number;
/** Gamepad left DPAD left button */
declare var GAMEPAD_BUTTON_LEFT_FACE_LEFT: number;
/** Gamepad right button up (i.e. PS3: Triangle, Xbox: Y) */
declare var GAMEPAD_BUTTON_RIGHT_FACE_UP: number;
/** Gamepad right button right (i.e. PS3: Circle, Xbox: B) */
declare var GAMEPAD_BUTTON_RIGHT_FACE_RIGHT: number;
/** Gamepad right button down (i.e. PS3: Cross, Xbox: A) */
declare var GAMEPAD_BUTTON_RIGHT_FACE_DOWN: number;
/** Gamepad right button left (i.e. PS3: Square, Xbox: X) */
declare var GAMEPAD_BUTTON_RIGHT_FACE_LEFT: number;
/** Gamepad top/back trigger left (first), it could be a trailing button */
declare var GAMEPAD_BUTTON_LEFT_TRIGGER_1: number;
/** Gamepad top/back trigger left (second), it could be a trailing button */
declare var GAMEPAD_BUTTON_LEFT_TRIGGER_2: number;
/** Gamepad top/back trigger right (first), it could be a trailing button */
declare var GAMEPAD_BUTTON_RIGHT_TRIGGER_1: number;
/** Gamepad top/back trigger right (second), it could be a trailing button */
declare var GAMEPAD_BUTTON_RIGHT_TRIGGER_2: number;
/** Gamepad center buttons, left one (i.e. PS3: Select) */
declare var GAMEPAD_BUTTON_MIDDLE_LEFT: number;
/** Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX) */
declare var GAMEPAD_BUTTON_MIDDLE: number;
/** Gamepad center buttons, right one (i.e. PS3: Start) */
declare var GAMEPAD_BUTTON_MIDDLE_RIGHT: number;
/** Gamepad joystick pressed button left */
declare var GAMEPAD_BUTTON_LEFT_THUMB: number;
/** Gamepad joystick pressed button right */
declare var GAMEPAD_BUTTON_RIGHT_THUMB: number;
/** Gamepad left stick X axis */
declare var GAMEPAD_AXIS_LEFT_X: number;
/** Gamepad left stick Y axis */
declare var GAMEPAD_AXIS_LEFT_Y: number;
/** Gamepad right stick X axis */
declare var GAMEPAD_AXIS_RIGHT_X: number;
/** Gamepad right stick Y axis */
declare var GAMEPAD_AXIS_RIGHT_Y: number;
/** Gamepad back trigger left, pressure level: [1..-1] */
declare var GAMEPAD_AXIS_LEFT_TRIGGER: number;
/** Gamepad back trigger right, pressure level: [1..-1] */
declare var GAMEPAD_AXIS_RIGHT_TRIGGER: number;
/** Albedo material (same as: MATERIAL_MAP_DIFFUSE) */
declare var MATERIAL_MAP_ALBEDO: number;
/** Metalness material (same as: MATERIAL_MAP_SPECULAR) */
declare var MATERIAL_MAP_METALNESS: number;
/** Normal material */
declare var MATERIAL_MAP_NORMAL: number;
/** Roughness material */
declare var MATERIAL_MAP_ROUGHNESS: number;
/** Ambient occlusion material */
declare var MATERIAL_MAP_OCCLUSION: number;
/** Emission material */
declare var MATERIAL_MAP_EMISSION: number;
/** Heightmap material */
declare var MATERIAL_MAP_HEIGHT: number;
/** Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP) */
declare var MATERIAL_MAP_CUBEMAP: number;
/** Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP) */
declare var MATERIAL_MAP_IRRADIANCE: number;
/** Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP) */
declare var MATERIAL_MAP_PREFILTER: number;
/** Brdf material */
declare var MATERIAL_MAP_BRDF: number;
/** Shader location: vertex attribute: position */
declare var SHADER_LOC_VERTEX_POSITION: number;
/** Shader location: vertex attribute: texcoord01 */
declare var SHADER_LOC_VERTEX_TEXCOORD01: number;
/** Shader location: vertex attribute: texcoord02 */
declare var SHADER_LOC_VERTEX_TEXCOORD02: number;
/** Shader location: vertex attribute: normal */
declare var SHADER_LOC_VERTEX_NORMAL: number;
/** Shader location: vertex attribute: tangent */
declare var SHADER_LOC_VERTEX_TANGENT: number;
/** Shader location: vertex attribute: color */
declare var SHADER_LOC_VERTEX_COLOR: number;
/** Shader location: matrix uniform: model-view-projection */
declare var SHADER_LOC_MATRIX_MVP: number;
/** Shader location: matrix uniform: view (camera transform) */
declare var SHADER_LOC_MATRIX_VIEW: number;
/** Shader location: matrix uniform: projection */
declare var SHADER_LOC_MATRIX_PROJECTION: number;
/** Shader location: matrix uniform: model (transform) */
declare var SHADER_LOC_MATRIX_MODEL: number;
/** Shader location: matrix uniform: normal */
declare var SHADER_LOC_MATRIX_NORMAL: number;
/** Shader location: vector uniform: view */
declare var SHADER_LOC_VECTOR_VIEW: number;
/** Shader location: vector uniform: diffuse color */
declare var SHADER_LOC_COLOR_DIFFUSE: number;
/** Shader location: vector uniform: specular color */
declare var SHADER_LOC_COLOR_SPECULAR: number;
/** Shader location: vector uniform: ambient color */
declare var SHADER_LOC_COLOR_AMBIENT: number;
/** Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE) */
declare var SHADER_LOC_MAP_ALBEDO: number;
/** Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR) */
declare var SHADER_LOC_MAP_METALNESS: number;
/** Shader location: sampler2d texture: normal */
declare var SHADER_LOC_MAP_NORMAL: number;
/** Shader location: sampler2d texture: roughness */
declare var SHADER_LOC_MAP_ROUGHNESS: number;
/** Shader location: sampler2d texture: occlusion */
declare var SHADER_LOC_MAP_OCCLUSION: number;
/** Shader location: sampler2d texture: emission */
declare var SHADER_LOC_MAP_EMISSION: number;
/** Shader location: sampler2d texture: height */
declare var SHADER_LOC_MAP_HEIGHT: number;
/** Shader location: samplerCube texture: cubemap */
declare var SHADER_LOC_MAP_CUBEMAP: number;
/** Shader location: samplerCube texture: irradiance */
declare var SHADER_LOC_MAP_IRRADIANCE: number;
/** Shader location: samplerCube texture: prefilter */
declare var SHADER_LOC_MAP_PREFILTER: number;
/** Shader location: sampler2d texture: brdf */
declare var SHADER_LOC_MAP_BRDF: number;
/** Shader location: vertex attribute: boneIds */
declare var SHADER_LOC_VERTEX_BONEIDS: number;
/** Shader location: vertex attribute: boneWeights */
declare var SHADER_LOC_VERTEX_BONEWEIGHTS: number;
/** Shader location: array of matrices uniform: boneMatrices */
declare var SHADER_LOC_BONE_MATRICES: number;
/** Shader location: vertex attribute: instanceTransform */
declare var SHADER_LOC_VERTEX_INSTANCE_TX: number;
/** Shader uniform type: float */
declare var SHADER_UNIFORM_FLOAT: number;
/** Shader uniform type: vec2 (2 float) */
declare var SHADER_UNIFORM_VEC2: number;
/** Shader uniform type: vec3 (3 float) */
declare var SHADER_UNIFORM_VEC3: number;
/** Shader uniform type: vec4 (4 float) */
declare var SHADER_UNIFORM_VEC4: number;
/** Shader uniform type: int */
declare var SHADER_UNIFORM_INT: number;
/** Shader uniform type: ivec2 (2 int) */
declare var SHADER_UNIFORM_IVEC2: number;
/** Shader uniform type: ivec3 (3 int) */
declare var SHADER_UNIFORM_IVEC3: number;
/** Shader uniform type: ivec4 (4 int) */
declare var SHADER_UNIFORM_IVEC4: number;
/** Shader uniform type: unsigned int */
declare var SHADER_UNIFORM_UINT: number;
/** Shader uniform type: uivec2 (2 unsigned int) */
declare var SHADER_UNIFORM_UIVEC2: number;
/** Shader uniform type: uivec3 (3 unsigned int) */
declare var SHADER_UNIFORM_UIVEC3: number;
/** Shader uniform type: uivec4 (4 unsigned int) */
declare var SHADER_UNIFORM_UIVEC4: number;
/** Shader uniform type: sampler2d */
declare var SHADER_UNIFORM_SAMPLER2D: number;
/** Shader attribute type: float */
declare var SHADER_ATTRIB_FLOAT: number;
/** Shader attribute type: vec2 (2 float) */
declare var SHADER_ATTRIB_VEC2: number;
/** Shader attribute type: vec3 (3 float) */
declare var SHADER_ATTRIB_VEC3: number;
/** Shader attribute type: vec4 (4 float) */
declare var SHADER_ATTRIB_VEC4: number;
/** 8 bit per pixel (no alpha) */
declare var PIXELFORMAT_UNCOMPRESSED_GRAYSCALE: number;
/** 8*2 bpp (2 channels) */
declare var PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA: number;
/** 16 bpp */
declare var PIXELFORMAT_UNCOMPRESSED_R5G6B5: number;
/** 24 bpp */
declare var PIXELFORMAT_UNCOMPRESSED_R8G8B8: number;
/** 16 bpp (1 bit alpha) */
declare var PIXELFORMAT_UNCOMPRESSED_R5G5B5A1: number;
/** 16 bpp (4 bit alpha) */
declare var PIXELFORMAT_UNCOMPRESSED_R4G4B4A4: number;
/** 32 bpp */
declare var PIXELFORMAT_UNCOMPRESSED_R8G8B8A8: number;
/** 32 bpp (1 channel - float) */
declare var PIXELFORMAT_UNCOMPRESSED_R32: number;
/** 32*3 bpp (3 channels - float) */
declare var PIXELFORMAT_UNCOMPRESSED_R32G32B32: number;
/** 32*4 bpp (4 channels - float) */
declare var PIXELFORMAT_UNCOMPRESSED_R32G32B32A32: number;
/** 16 bpp (1 channel - half float) */
declare var PIXELFORMAT_UNCOMPRESSED_R16: number;
/** 16*3 bpp (3 channels - half float) */
declare var PIXELFORMAT_UNCOMPRESSED_R16G16B16: number;
/** 16*4 bpp (4 channels - half float) */
declare var PIXELFORMAT_UNCOMPRESSED_R16G16B16A16: number;
/** 4 bpp (no alpha) */
declare var PIXELFORMAT_COMPRESSED_DXT1_RGB: number;
/** 4 bpp (1 bit alpha) */
declare var PIXELFORMAT_COMPRESSED_DXT1_RGBA: number;
/** 8 bpp */
declare var PIXELFORMAT_COMPRESSED_DXT3_RGBA: number;
/** 8 bpp */
declare var PIXELFORMAT_COMPRESSED_DXT5_RGBA: number;
/** 4 bpp */
declare var PIXELFORMAT_COMPRESSED_ETC1_RGB: number;
/** 4 bpp */
declare var PIXELFORMAT_COMPRESSED_ETC2_RGB: number;
/** 8 bpp */
declare var PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA: number;
/** 4 bpp */
declare var PIXELFORMAT_COMPRESSED_PVRT_RGB: number;
/** 4 bpp */
declare var PIXELFORMAT_COMPRESSED_PVRT_RGBA: number;
/** 8 bpp */
declare var PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA: number;
/** 2 bpp */
declare var PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA: number;
/** No filter, just pixel approximation */
declare var TEXTURE_FILTER_POINT: number;
/** Linear filtering */
declare var TEXTURE_FILTER_BILINEAR: number;
/** Trilinear filtering (linear with mipmaps) */
declare var TEXTURE_FILTER_TRILINEAR: number;
/** Anisotropic filtering 4x */
declare var TEXTURE_FILTER_ANISOTROPIC_4X: number;
/** Anisotropic filtering 8x */
declare var TEXTURE_FILTER_ANISOTROPIC_8X: number;
/** Anisotropic filtering 16x */
declare var TEXTURE_FILTER_ANISOTROPIC_16X: number;
/** Repeats texture in tiled mode */
declare var TEXTURE_WRAP_REPEAT: number;
/** Clamps texture to edge pixel in tiled mode */
declare var TEXTURE_WRAP_CLAMP: number;
/** Mirrors and repeats the texture in tiled mode */
declare var TEXTURE_WRAP_MIRROR_REPEAT: number;
/** Mirrors and clamps to border the texture in tiled mode */
declare var TEXTURE_WRAP_MIRROR_CLAMP: number;
/** Automatically detect layout type */
declare var CUBEMAP_LAYOUT_AUTO_DETECT: number;
/** Layout is defined by a vertical line with faces */
declare var CUBEMAP_LAYOUT_LINE_VERTICAL: number;
/** Layout is defined by a horizontal line with faces */
declare var CUBEMAP_LAYOUT_LINE_HORIZONTAL: number;
/** Layout is defined by a 3x4 cross with cubemap faces */
declare var CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR: number;
/** Layout is defined by a 4x3 cross with cubemap faces */
declare var CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE: number;
/** Default font generation, anti-aliased */
declare var FONT_DEFAULT: number;
/** Bitmap font generation, no anti-aliasing */
declare var FONT_BITMAP: number;
/** SDF font generation, requires external shader */
declare var FONT_SDF: number;
/** Blend textures considering alpha (default) */
declare var BLEND_ALPHA: number;
/** Blend textures adding colors */
declare var BLEND_ADDITIVE: number;
/** Blend textures multiplying colors */
declare var BLEND_MULTIPLIED: number;
/** Blend textures adding colors (alternative) */
declare var BLEND_ADD_COLORS: number;
/** Blend textures subtracting colors (alternative) */
declare var BLEND_SUBTRACT_COLORS: number;
/** Blend premultiplied textures considering alpha */
declare var BLEND_ALPHA_PREMULTIPLY: number;
/** Blend textures using custom src/dst factors (use rlSetBlendFactors()) */
declare var BLEND_CUSTOM: number;
/** Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate()) */
declare var BLEND_CUSTOM_SEPARATE: number;
/** No gesture */
declare var GESTURE_NONE: number;
/** Tap gesture */
declare var GESTURE_TAP: number;
/** Double tap gesture */
declare var GESTURE_DOUBLETAP: number;
/** Hold gesture */
declare var GESTURE_HOLD: number;
/** Drag gesture */
declare var GESTURE_DRAG: number;
/** Swipe right gesture */
declare var GESTURE_SWIPE_RIGHT: number;
/** Swipe left gesture */
declare var GESTURE_SWIPE_LEFT: number;
/** Swipe up gesture */
declare var GESTURE_SWIPE_UP: number;
/** Swipe down gesture */
declare var GESTURE_SWIPE_DOWN: number;
/** Pinch in gesture */
declare var GESTURE_PINCH_IN: number;
/** Pinch out gesture */
declare var GESTURE_PINCH_OUT: number;
/** Camera custom, controlled by user (UpdateCamera() does nothing) */
declare var CAMERA_CUSTOM: number;
/** Camera free mode */
declare var CAMERA_FREE: number;
/** Camera orbital, around target, zoom supported */
declare var CAMERA_ORBITAL: number;
/** Camera first person */
declare var CAMERA_FIRST_PERSON: number;
/** Camera third person */
declare var CAMERA_THIRD_PERSON: number;
/** Perspective projection */
declare var CAMERA_PERSPECTIVE: number;
/** Orthographic projection */
declare var CAMERA_ORTHOGRAPHIC: number;
/** Npatch layout: 3x3 tiles */
declare var NPATCH_NINE_PATCH: number;
/** Npatch layout: 1x3 tiles */
declare var NPATCH_THREE_PATCH_VERTICAL: number;
/** Npatch layout: 3x1 tiles */
declare var NPATCH_THREE_PATCH_HORIZONTAL: number;
