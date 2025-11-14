declare module "rayjs:raylib" {
interface Vector2 {
/** Vector x component */
x: number,
/** Vector y component */
y: number,
}
var Vector2: {
prototype: Vector2
new(x?: number, y?: number): Vector2
}
interface Vector3 {
/** Vector x component */
x: number,
/** Vector y component */
y: number,
/** Vector z component */
z: number,
}
var Vector3: {
prototype: Vector3
new(x?: number, y?: number, z?: number): Vector3
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
var Vector4: {
prototype: Vector4
new(x?: number, y?: number, z?: number, w?: number): Vector4
}
interface Matrix {
/** Matrix first row (4 components) */
m0: number,
m4: number,
m8: number,
m12: number,
/** Matrix second row (4 components) */
m1: number,
m5: number,
m9: number,
m13: number,
/** Matrix third row (4 components) */
m2: number,
m6: number,
m10: number,
m14: number,
/** Matrix fourth row (4 components) */
m3: number,
m7: number,
m11: number,
m15: number,
}
var Matrix: {
prototype: Matrix
new(m0?: number, m4?: number, m8?: number, m12?: number, m1?: number, m5?: number, m9?: number, m13?: number, m2?: number, m6?: number, m10?: number, m14?: number, m3?: number, m7?: number, m11?: number, m15?: number): Matrix
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
var Color: {
prototype: Color
new(r?: number, g?: number, b?: number, a?: number): Color
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
var Rectangle: {
prototype: Rectangle
new(x?: number, y?: number, width?: number, height?: number): Rectangle
}
interface Image {
/** Image raw data */
data: ArrayBuffer,
/** Image base width */
width: number,
/** Image base height */
height: number,
/** Mipmap levels, 1 by default */
mipmaps: number,
/** Data format (PixelFormat type) */
format: number,
}
var Image: {
prototype: Image
new(data?: ArrayBuffer, width?: number, height?: number, mipmaps?: number, format?: number): Image
}
interface Texture {
/** OpenGL texture id */
id: number,
/** Texture base width */
width: number,
/** Texture base height */
height: number,
/** Mipmap levels, 1 by default */
mipmaps: number,
/** Data format (PixelFormat type) */
format: number,
}
var Texture: {
prototype: Texture
new(id?: number, width?: number, height?: number, mipmaps?: number, format?: number): Texture
}
interface RenderTexture {
/** OpenGL framebuffer object id */
id: number,
/** Color buffer attachment texture */
texture: Texture,
/** Depth buffer attachment texture */
depth: Texture,
}
var RenderTexture: {
prototype: RenderTexture
new(id?: number, texture?: Texture, depth?: Texture): RenderTexture
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
var NPatchInfo: {
prototype: NPatchInfo
new(source?: Rectangle, left?: number, top?: number, right?: number, bottom?: number, layout?: number): NPatchInfo
}
interface GlyphInfo {
/** Character value (Unicode) */
value: number,
/** Character offset X when drawing */
offsetX: number,
/** Character offset Y when drawing */
offsetY: number,
/** Character advance position X */
advanceX: number,
/** Character image data */
image: Image,
}
var GlyphInfo: {
prototype: GlyphInfo
new(value?: number, offsetX?: number, offsetY?: number, advanceX?: number, image?: Image): GlyphInfo
}
interface Font {
/** Base size (default chars height) */
baseSize: number,
/** Number of glyph characters */
glyphCount: number,
/** Padding around the glyph characters */
glyphPadding: number,
/** Texture atlas containing the glyphs */
texture: Texture2D,
/** Rectangles in texture for the glyphs */
recs: Rectangle[],
/** Glyphs info data */
glyphs: GlyphInfo[],
}
var Font: {
prototype: Font
new(baseSize?: number, glyphCount?: number, glyphPadding?: number, texture?: Texture2D, recs?: Rectangle[], glyphs?: GlyphInfo[]): Font
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
var Camera3D: {
prototype: Camera3D
new(position?: Vector3, target?: Vector3, up?: Vector3, fovy?: number, projection?: number): Camera3D
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
var Camera2D: {
prototype: Camera2D
new(offset?: Vector2, target?: Vector2, rotation?: number, zoom?: number): Camera2D
}
interface Mesh {
/** Number of vertices stored in arrays */
vertexCount: number,
/** Number of triangles stored (indexed or not) */
triangleCount: number,
/** Vertex position (XYZ - 3 components per vertex) (shader-location = 0) */
vertices: number[],
/** Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1) */
texcoords: number[],
/** Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5) */
texcoords2: number[],
/** Vertex normals (XYZ - 3 components per vertex) (shader-location = 2) */
normals: number[],
/** Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4) */
tangents: number[],
/** Vertex colors (RGBA - 4 components per vertex) (shader-location = 3) */
colors: number[],
/** Vertex indices (in case vertex data comes indexed) */
indices: number[],
/** Animated vertex positions (after bones transformations) */
animVertices: number[],
/** Animated normals (after bones transformations) */
animNormals: number[],
/** Vertex bone ids, max 255 bone ids, up to 4 bones influence by vertex (skinning) (shader-location = 6) */
boneIds: number[],
/** Vertex bone weight, up to 4 bones influence by vertex (skinning) (shader-location = 7) */
boneWeights: number[],
/** Bones animated transformation matrices */
boneMatrices: Matrix[],
/** Number of bones */
boneCount: number,
/** OpenGL Vertex Array Object id */
vaoId: number,
/** OpenGL Vertex Buffer Objects id (default vertex data) */
vboId: number[],
}
var Mesh: {
prototype: Mesh
new(vertexCount?: number, triangleCount?: number, vertices?: number[], texcoords?: number[], texcoords2?: number[], normals?: number[], tangents?: number[], colors?: number[], indices?: number[], animVertices?: number[], animNormals?: number[], boneIds?: number[], boneWeights?: number[], boneMatrices?: Matrix[], boneCount?: number, vaoId?: number, vboId?: number[]): Mesh
}
interface Shader {
/** Shader program id */
id: number,
/** Shader locations array (RL_MAX_SHADER_LOCATIONS) */
locs: number[],
}
var Shader: {
prototype: Shader
new(id?: number, locs?: number[]): Shader
}
interface MaterialMap {
/** Material map texture */
texture: Texture2D,
/** Material map color */
color: Color,
/** Material map value */
value: number,
}
var MaterialMap: {
prototype: MaterialMap
new(texture?: Texture2D, color?: Color, value?: number): MaterialMap
}
interface Material {
/** Material shader */
shader: Shader,
/** Material maps array (MAX_MATERIAL_MAPS) */
maps: MaterialMap[],
/** Material generic parameters (if required) */
params: [number,number,number,number],
}
var Material: {
prototype: Material
new(shader?: Shader, maps?: MaterialMap[], params?: [number,number,number,number]): Material
}
interface Transform {
/** Translation */
translation: Vector3,
/** Rotation */
rotation: Quaternion,
/** Scale */
scale: Vector3,
}
var Transform: {
prototype: Transform
new(translation?: Vector3, rotation?: Quaternion, scale?: Vector3): Transform
}
interface BoneInfo {
/** Bone name */
name: string,
/** Bone parent */
parent: number,
}
var BoneInfo: {
prototype: BoneInfo
new(name?: string, parent?: number): BoneInfo
}
interface Model {
/** Local transform matrix */
transform: Matrix,
/** Number of meshes */
meshCount: number,
/** Number of materials */
materialCount: number,
/** Meshes array */
meshes: Mesh[],
/** Materials array */
materials: Material[],
/** Mesh material number */
meshMaterial: number[],
/** Number of bones */
boneCount: number,
/** Bones information (skeleton) */
bones: BoneInfo[],
/** Bones base transformation (pose) */
bindPose: Transform[],
}
var Model: {
prototype: Model
new(transform?: Matrix, meshCount?: number, materialCount?: number, meshes?: Mesh[], materials?: Material[], meshMaterial?: number[], boneCount?: number, bones?: BoneInfo[], bindPose?: Transform[]): Model
}
interface ModelAnimation {
/** Number of bones */
boneCount: number,
/** Number of animation frames */
frameCount: number,
/** Bones information (skeleton) */
bones: BoneInfo[],
/** Poses array by frame */
framePoses: Transform[][],
/** Animation name */
name: string,
}
var ModelAnimation: {
prototype: ModelAnimation
new(boneCount?: number, frameCount?: number, bones?: BoneInfo[], framePoses?: Transform[][], name?: string): ModelAnimation
}
interface Ray {
/** Ray position (origin) */
position: Vector3,
/** Ray direction (normalized) */
direction: Vector3,
}
var Ray: {
prototype: Ray
new(position?: Vector3, direction?: Vector3): Ray
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
var RayCollision: {
prototype: RayCollision
new(hit?: boolean, distance?: number, point?: Vector3, normal?: Vector3): RayCollision
}
interface BoundingBox {
/** Minimum vertex box-corner */
min: Vector3,
/** Maximum vertex box-corner */
max: Vector3,
}
var BoundingBox: {
prototype: BoundingBox
new(min?: Vector3, max?: Vector3): BoundingBox
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
/** Buffer data pointer */
data: ArrayBuffer,
}
var Wave: {
prototype: Wave
new(frameCount?: number, sampleRate?: number, sampleSize?: number, channels?: number, data?: ArrayBuffer): Wave
}
interface rAudioBuffer {
}
var rAudioBuffer: {
prototype: rAudioBuffer
}
interface rAudioProcessor {
}
var rAudioProcessor: {
prototype: rAudioProcessor
}
interface AudioStream {
/** Frequency (samples per second) */
sampleRate: number,
/** Bit depth (bits per sample): 8, 16, 32 (24 not supported) */
sampleSize: number,
/** Number of channels (1-mono, 2-stereo, ...) */
channels: number,
}
var AudioStream: {
prototype: AudioStream
new(sampleRate?: number, sampleSize?: number, channels?: number): AudioStream
}
interface Sound {
/** Audio stream */
stream: AudioStream,
/** Total number of frames (considering channels) */
frameCount: number,
}
var Sound: {
prototype: Sound
new(stream?: AudioStream, frameCount?: number): Sound
}
interface Music {
/** Audio stream */
stream: AudioStream,
/** Total number of frames (considering channels) */
frameCount: number,
/** Music looping enable */
looping: boolean,
/** Type of music context (audio filetype) */
ctxType: number,
}
var Music: {
prototype: Music
new(stream?: AudioStream, frameCount?: number, looping?: boolean, ctxType?: number): Music
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
lensDistortionValues: [number,number,number,number],
/** Chromatic aberration correction parameters */
chromaAbCorrection: [number,number,number,number],
}
var VrDeviceInfo: {
prototype: VrDeviceInfo
new(hResolution?: number, vResolution?: number, hScreenSize?: number, vScreenSize?: number, eyeToScreenDistance?: number, lensSeparationDistance?: number, interpupillaryDistance?: number, lensDistortionValues?: [number,number,number,number], chromaAbCorrection?: [number,number,number,number]): VrDeviceInfo
}
interface VrStereoConfig {
/** VR projection matrices (per eye) */
projection: [Matrix,Matrix],
/** VR view offset matrices (per eye) */
viewOffset: [Matrix,Matrix],
/** VR left lens center */
leftLensCenter: [number,number],
/** VR right lens center */
rightLensCenter: [number,number],
/** VR left screen center */
leftScreenCenter: [number,number],
/** VR right screen center */
rightScreenCenter: [number,number],
/** VR distortion scale */
scale: [number,number],
/** VR distortion scale in */
scaleIn: [number,number],
}
var VrStereoConfig: {
prototype: VrStereoConfig
new(projection?: [Matrix,Matrix], viewOffset?: [Matrix,Matrix], leftLensCenter?: [number,number], rightLensCenter?: [number,number], leftScreenCenter?: [number,number], rightScreenCenter?: [number,number], scale?: [number,number], scaleIn?: [number,number]): VrStereoConfig
}
interface FilePathList {
/** Filepaths max entries */
capacity: number,
/** Filepaths entries count */
count: number,
/** Filepaths entries */
paths: string[],
}
var FilePathList: {
prototype: FilePathList
new(capacity?: number, count?: number, paths?: string[]): FilePathList
}
interface AutomationEvent {
/** Event frame */
frame: number,
/** Event type (AutomationEventType) */
type: number,
/** Event parameters (if required) */
params: [number,number,number,number],
}
var AutomationEvent: {
prototype: AutomationEvent
new(frame?: number, type?: number, params?: [number,number,number,number]): AutomationEvent
}
interface AutomationEventList {
/** Events max entries (MAX_AUTOMATION_EVENTS) */
capacity: number,
/** Events entries count */
count: number,
/** Events entries */
events: AutomationEvent[],
}
var AutomationEventList: {
prototype: AutomationEventList
new(capacity?: number, count?: number, events?: AutomationEvent[]): AutomationEventList
}
/** FileIO: Load binary data */
type LoadFileDataCallback = (arg_fileName:string,arg_dataSize:number[])=>number[];
/** FileIO: Save binary data */
type SaveFileDataCallback = (arg_fileName:string,arg_data:number[],arg_dataSize:number)=>boolean;
/** FileIO: Load text data */
type LoadFileTextCallback = (arg_fileName:string)=>string;
/** FileIO: Save text data */
type SaveFileTextCallback = (arg_fileName:string,arg_text:string)=>boolean;
/** ------------------------------------------------------------------------------------ */
type AudioStreamCallback = (arg_bufferData:number[],arg_frames:number)=>void;
/** ------------------------------------------------------------------------------------ */
type AudioCallback = (arg_bufferData:number[],arg_frames:number)=>void;
/** ------------------------------------------------------------------------------------ */
type AudioMixedProcessor = (arg_bufferData:number[],arg_frames:number)=>void;
type Quaternion = Vector4;
type Texture2D = Texture;
type TextureCubemap = Texture;
type RenderTexture2D = RenderTexture;
type Camera = Camera3D;
/** Initialize window and OpenGL context */
function InitWindow(width: number, height: number, title: string): void/** Close window and unload OpenGL context */
function CloseWindow(): void/** Check if application should close (KEY_ESCAPE pressed or windows close icon clicked) */
function WindowShouldClose(): boolean/** Check if window has been initialized successfully */
function IsWindowReady(): boolean/** Check if window is currently fullscreen */
function IsWindowFullscreen(): boolean/** Check if window is currently hidden */
function IsWindowHidden(): boolean/** Check if window is currently minimized */
function IsWindowMinimized(): boolean/** Check if window is currently maximized */
function IsWindowMaximized(): boolean/** Check if window is currently focused */
function IsWindowFocused(): boolean/** Check if window has been resized last frame */
function IsWindowResized(): boolean/** Check if one specific window flag is enabled */
function IsWindowState(flag: number): boolean/** Set window configuration state using flags */
function SetWindowState(flags: number): void/** Clear window configuration state flags */
function ClearWindowState(flags: number): void/** Toggle window state: fullscreen/windowed, resizes monitor to match window resolution */
function ToggleFullscreen(): void/** Toggle window state: borderless windowed, resizes window to match monitor resolution */
function ToggleBorderlessWindowed(): void/** Set window state: maximized, if resizable */
function MaximizeWindow(): void/** Set window state: minimized, if resizable */
function MinimizeWindow(): void/** Restore window from being minimized/maximized */
function RestoreWindow(): void/** Set icon for window (single image, RGBA 32bit) */
function SetWindowIcon(image: Image): void/** Set icon for window (multiple images, RGBA 32bit) */
function SetWindowIcons(images: Image[], count: number): void/** Set title for window */
function SetWindowTitle(title: string): void/** Set window position on screen */
function SetWindowPosition(x: number, y: number): void/** Set monitor for the current window */
function SetWindowMonitor(monitor: number): void/** Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE) */
function SetWindowMinSize(width: number, height: number): void/** Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE) */
function SetWindowMaxSize(width: number, height: number): void/** Set window dimensions */
function SetWindowSize(width: number, height: number): void/** Set window opacity [0.0f..1.0f] */
function SetWindowOpacity(opacity: number): void/** Set window focused */
function SetWindowFocused(): void/** Get current screen width */
function GetScreenWidth(): number/** Get current screen height */
function GetScreenHeight(): number/** Get current render width (it considers HiDPI) */
function GetRenderWidth(): number/** Get current render height (it considers HiDPI) */
function GetRenderHeight(): number/** Get number of connected monitors */
function GetMonitorCount(): number/** Get current monitor where window is placed */
function GetCurrentMonitor(): number/** Get specified monitor position */
function GetMonitorPosition(monitor: number): Vector2/** Get specified monitor width (current video mode used by monitor) */
function GetMonitorWidth(monitor: number): number/** Get specified monitor height (current video mode used by monitor) */
function GetMonitorHeight(monitor: number): number/** Get specified monitor physical width in millimetres */
function GetMonitorPhysicalWidth(monitor: number): number/** Get specified monitor physical height in millimetres */
function GetMonitorPhysicalHeight(monitor: number): number/** Get specified monitor refresh rate */
function GetMonitorRefreshRate(monitor: number): number/** Get window position XY on monitor */
function GetWindowPosition(): Vector2/** Get window scale DPI factor */
function GetWindowScaleDPI(): Vector2/** Get the human-readable, UTF-8 encoded name of the specified monitor */
function GetMonitorName(monitor: number): string/** Set clipboard text content */
function SetClipboardText(text: string): void/** Get clipboard text content */
function GetClipboardText(): string/** Get clipboard image content */
function GetClipboardImage(): Image/** Enable waiting for events on EndDrawing(), no automatic event polling */
function EnableEventWaiting(): void/** Disable waiting for events on EndDrawing(), automatic events polling */
function DisableEventWaiting(): void/** Shows cursor */
function ShowCursor(): void/** Hides cursor */
function HideCursor(): void/** Check if cursor is not visible */
function IsCursorHidden(): boolean/** Enables cursor (unlock cursor) */
function EnableCursor(): void/** Disables cursor (lock cursor) */
function DisableCursor(): void/** Check if cursor is on the screen */
function IsCursorOnScreen(): boolean/** Set background color (framebuffer clear color) */
function ClearBackground(color: Color): void/** Setup canvas (framebuffer) to start drawing */
function BeginDrawing(): void/** undefined */
function EndDrawing(): void/** Begin 2D mode with custom camera (2D) */
function BeginMode2D(camera: Camera2D): void/** Ends 2D mode with custom camera */
function EndMode2D(): void/** Begin 3D mode with custom camera (3D) */
function BeginMode3D(camera: Camera3D): void/** Ends 3D mode and returns to default 2D orthographic mode */
function EndMode3D(): void/** Begin drawing to render texture */
function BeginTextureMode(target: RenderTexture2D): void/** Ends drawing to render texture */
function EndTextureMode(): void/** Begin custom shader drawing */
function BeginShaderMode(shader: Shader): void/** End custom shader drawing (use default shader) */
function EndShaderMode(): void/** Begin blending mode (alpha, additive, multiplied, subtract, custom) */
function BeginBlendMode(mode: number): void/** End blending mode (reset to default: alpha blending) */
function EndBlendMode(): void/** Begin scissor mode (define screen area for following drawing) */
function BeginScissorMode(x: number, y: number, width: number, height: number): void/** End scissor mode */
function EndScissorMode(): void/** Begin stereo rendering (requires VR simulator) */
function BeginVrStereoMode(config: VrStereoConfig): void/** End stereo rendering (requires VR simulator) */
function EndVrStereoMode(): void/** Load VR stereo config for VR simulator device parameters */
function LoadVrStereoConfig(device: VrDeviceInfo): VrStereoConfig/** Unload VR stereo config */
function UnloadVrStereoConfig(config: VrStereoConfig): void/** Load shader from files and bind default locations */
function LoadShader(vsFileName: string, fsFileName: string): Shader/** Load shader from code strings and bind default locations */
function LoadShaderFromMemory(vsCode: string, fsCode: string): Shader/** Check if a shader is valid (loaded on GPU) */
function IsShaderValid(shader: Shader): boolean/** Get shader uniform location */
function GetShaderLocation(shader: Shader, uniformName: string): number/** Get shader attribute location */
function GetShaderLocationAttrib(shader: Shader, attribName: string): number/** Set shader uniform value */
function SetShaderValue(shader: Shader, locIndex: number, value: ArrayBuffer, uniformType: number): void/** Set shader uniform value vector */
function SetShaderValueV(shader: Shader, locIndex: number, values: ArrayBuffer, uniformType: number, count: number): void/** Set shader uniform value (matrix 4x4) */
function SetShaderValueMatrix(shader: Shader, locIndex: number, mat: Matrix): void/** Set shader uniform value and bind the texture (sampler2d) */
function SetShaderValueTexture(shader: Shader, locIndex: number, texture: Texture2D): void/** Unload shader from GPU memory (VRAM) */
function UnloadShader(shader: Shader): void/** Get a ray trace from screen position (i.e mouse) */
function GetScreenToWorldRay(position: Vector2, camera: Camera): Ray/** Get a ray trace from screen position (i.e mouse) in a viewport */
function GetScreenToWorldRayEx(position: Vector2, camera: Camera, width: number, height: number): Ray/** Get the screen space position for a 3d world space position */
function GetWorldToScreen(position: Vector3, camera: Camera): Vector2/** Get size position for a 3d world space position */
function GetWorldToScreenEx(position: Vector3, camera: Camera, width: number, height: number): Vector2/** Get the screen space position for a 2d camera world space position */
function GetWorldToScreen2D(position: Vector2, camera: Camera2D): Vector2/** Get the world space position for a 2d camera screen space position */
function GetScreenToWorld2D(position: Vector2, camera: Camera2D): Vector2/** Get camera transform matrix (view matrix) */
function GetCameraMatrix(camera: Camera): Matrix/** Get camera 2d transform matrix */
function GetCameraMatrix2D(camera: Camera2D): Matrix/** Set target FPS (maximum) */
function SetTargetFPS(fps: number): void/** Get time in seconds for last frame drawn (delta time) */
function GetFrameTime(): number/** Get elapsed time in seconds since InitWindow() */
function GetTime(): number/** Get current FPS */
function GetFPS(): number/** Set the seed for the random number generator */
function SetRandomSeed(seed: number): void/** Get a random value between min and max (both included) */
function GetRandomValue(min: number, max: number): number/** undefined */
function LoadRandomSequence(count: number, min: number, max: number): number[]/** Unload random values sequence */
function UnloadRandomSequence(sequence: number[]): void/** Takes a screenshot of current screen (filename extension defines format) */
function TakeScreenshot(fileName: string): void/** Setup init configuration flags (view FLAGS) */
function SetConfigFlags(flags: number): void/** Open URL with default system browser (if available) */
function OpenURL(url: string): void/** Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...) */
function TraceLog(logLevel: number, text: string, ...args: any): void/** Set the current threshold (minimum) log level */
function SetTraceLogLevel(logLevel: number): void/** Set custom file binary data loader */
function SetLoadFileDataCallback(callback: LoadFileDataCallback): void/** Set custom file binary data saver */
function SetSaveFileDataCallback(callback: SaveFileDataCallback): void/** Set custom file text data loader */
function SetLoadFileTextCallback(callback: LoadFileTextCallback): void/** Set custom file text data saver */
function SetSaveFileTextCallback(callback: SaveFileTextCallback): void/** Load file data as byte array (read) */
function LoadFileData(fileName: string, dataSize: number | number[]): number[]/** undefined */
function SaveFileData(fileName: string, data: ArrayBuffer, dataSize: number): boolean/** Export data to code (.h), returns true on success */
function ExportDataAsCode(data: number[], dataSize: number, fileName: string): boolean/** Load text data from file (read), returns a '\0' terminated string */
function LoadFileText(fileName: string): string/** Save text data to file (write), string must be '\0' terminated, returns true on success */
function SaveFileText(fileName: string, text: string): boolean/** Check if file exists */
function FileExists(fileName: string): boolean/** Check if a directory path exists */
function DirectoryExists(dirPath: string): boolean/** Check file extension (recommended include point: .png, .wav) */
function IsFileExtension(fileName: string, ext: string): boolean/** Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h) */
function GetFileLength(fileName: string): number/** Get pointer to extension for a filename string (includes dot: '.png') */
function GetFileExtension(fileName: string): string/** Get pointer to filename for a path string */
function GetFileName(filePath: string): string/** Get filename string without extension (uses static string) */
function GetFileNameWithoutExt(filePath: string): string/** Get full path for a given fileName with path (uses static string) */
function GetDirectoryPath(filePath: string): string/** Get previous directory path for a given path (uses static string) */
function GetPrevDirectoryPath(dirPath: string): string/** Get current working directory (uses static string) */
function GetWorkingDirectory(): string/** Get the directory of the running application (uses static string) */
function GetApplicationDirectory(): string/** Create directories (including full path requested), returns 0 on success */
function MakeDirectory(dirPath: string): number/** Change working directory, return true on success */
function ChangeDirectory(dir: string): boolean/** Check if a given path is a file or a directory */
function IsPathFile(path: string): boolean/** Check if fileName is valid for the platform/OS */
function IsFileNameValid(fileName: string): boolean/** undefined */
function LoadDirectoryFiles(dirPath: string): string[]/** undefined */
function LoadDirectoryFilesEx(basePath: string, filter: string, scanSubdirs: boolean): string[]/** Check if a file has been dropped into window */
function IsFileDropped(): boolean/** undefined */
function LoadDroppedFiles(): string[]/** Get file modification time (last write time) */
function GetFileModTime(fileName: string): number/** Compress data (DEFLATE algorithm), memory must be MemFree() */
function CompressData(data: number[], dataSize: number, compDataSize: number[]): string/** Decompress data (DEFLATE algorithm), memory must be MemFree() */
function DecompressData(compData: number[], compDataSize: number, dataSize: number | number[]): string/** Encode data to Base64 string (includes NULL terminator), memory must be MemFree() */
function EncodeDataBase64(data: number[], dataSize: number, outputSize: number[]): string/** Decode Base64 string (expected NULL terminated), memory must be MemFree() */
function DecodeDataBase64(text: string, outputSize: number[]): string/** Compute CRC32 hash code */
function ComputeCRC32(data: number[], dataSize: number): number/** Compute MD5 hash code, returns static int[4] (16 bytes) */
function ComputeMD5(data: number[], dataSize: number): number[]/** Compute SHA1 hash code, returns static int[5] (20 bytes) */
function ComputeSHA1(data: number[], dataSize: number): number[]/** Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS */
function LoadAutomationEventList(fileName: string): AutomationEventList/** Unload automation events list from file */
function UnloadAutomationEventList(list: AutomationEventList): void/** Export automation events list as text file */
function ExportAutomationEventList(list: AutomationEventList, fileName: string): boolean/** Set automation event list to record to */
function SetAutomationEventList(list: AutomationEventList[]): void/** Set automation event internal base frame to start recording */
function SetAutomationEventBaseFrame(frame: number): void/** Start recording automation events (AutomationEventList must be set) */
function StartAutomationEventRecording(): void/** Stop recording automation events */
function StopAutomationEventRecording(): void/** Play a recorded automation event */
function PlayAutomationEvent(event: AutomationEvent): void/** Check if a key has been pressed once */
function IsKeyPressed(key: number): boolean/** Check if a key has been pressed again */
function IsKeyPressedRepeat(key: number): boolean/** Check if a key is being pressed */
function IsKeyDown(key: number): boolean/** Check if a key has been released once */
function IsKeyReleased(key: number): boolean/** Check if a key is NOT being pressed */
function IsKeyUp(key: number): boolean/** Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty */
function GetKeyPressed(): number/** Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty */
function GetCharPressed(): number/** Get name of a QWERTY key on the current keyboard layout (eg returns string 'q' for KEY_A on an AZERTY keyboard) */
function GetKeyName(key: number): string/** Set a custom key to exit program (default is ESC) */
function SetExitKey(key: number): void/** Check if a gamepad is available */
function IsGamepadAvailable(gamepad: number): boolean/** Get gamepad internal name id */
function GetGamepadName(gamepad: number): string/** Check if a gamepad button has been pressed once */
function IsGamepadButtonPressed(gamepad: number, button: number): boolean/** Check if a gamepad button is being pressed */
function IsGamepadButtonDown(gamepad: number, button: number): boolean/** Check if a gamepad button has been released once */
function IsGamepadButtonReleased(gamepad: number, button: number): boolean/** Check if a gamepad button is NOT being pressed */
function IsGamepadButtonUp(gamepad: number, button: number): boolean/** Get the last gamepad button pressed */
function GetGamepadButtonPressed(): number/** Get axis count for a gamepad */
function GetGamepadAxisCount(gamepad: number): number/** Get movement value for a gamepad axis */
function GetGamepadAxisMovement(gamepad: number, axis: number): number/** Set internal gamepad mappings (SDL_GameControllerDB) */
function SetGamepadMappings(mappings: string): number/** Set gamepad vibration for both motors (duration in seconds) */
function SetGamepadVibration(gamepad: number, leftMotor: number, rightMotor: number, duration: number): void/** Check if a mouse button has been pressed once */
function IsMouseButtonPressed(button: number): boolean/** Check if a mouse button is being pressed */
function IsMouseButtonDown(button: number): boolean/** Check if a mouse button has been released once */
function IsMouseButtonReleased(button: number): boolean/** Check if a mouse button is NOT being pressed */
function IsMouseButtonUp(button: number): boolean/** Get mouse position X */
function GetMouseX(): number/** Get mouse position Y */
function GetMouseY(): number/** Get mouse position XY */
function GetMousePosition(): Vector2/** Get mouse delta between frames */
function GetMouseDelta(): Vector2/** Set mouse position XY */
function SetMousePosition(x: number, y: number): void/** Set mouse offset */
function SetMouseOffset(offsetX: number, offsetY: number): void/** Set mouse scaling */
function SetMouseScale(scaleX: number, scaleY: number): void/** Get mouse wheel movement for X or Y, whichever is larger */
function GetMouseWheelMove(): number/** Get mouse wheel movement for both X and Y */
function GetMouseWheelMoveV(): Vector2/** Set mouse cursor */
function SetMouseCursor(cursor: number): void/** Get touch position X for touch point 0 (relative to screen size) */
function GetTouchX(): number/** Get touch position Y for touch point 0 (relative to screen size) */
function GetTouchY(): number/** Get touch position XY for a touch point index (relative to screen size) */
function GetTouchPosition(index: number): Vector2/** Get touch point identifier for given index */
function GetTouchPointId(index: number): number/** Get number of touch points */
function GetTouchPointCount(): number/** Enable a set of gestures using flags */
function SetGesturesEnabled(flags: number): void/** Check if a gesture have been detected */
function IsGestureDetected(gesture: number): boolean/** Get latest detected gesture */
function GetGestureDetected(): number/** Get gesture hold time in seconds */
function GetGestureHoldDuration(): number/** Get gesture drag vector */
function GetGestureDragVector(): Vector2/** Get gesture drag angle */
function GetGestureDragAngle(): number/** Get gesture pinch delta */
function GetGesturePinchVector(): Vector2/** Get gesture pinch angle */
function GetGesturePinchAngle(): number/** Update camera position for selected mode */
function UpdateCamera(camera: Camera, mode: number): void/** Update camera movement/rotation */
function UpdateCameraPro(camera: Camera, movement: Vector3, rotation: Vector3, zoom: number): void/** Set texture and rectangle to be used on shapes drawing */
function SetShapesTexture(texture: Texture2D, source: Rectangle): void/** Get texture that is used for shapes drawing */
function GetShapesTexture(): Texture2D/** Get texture source rectangle that is used for shapes drawing */
function GetShapesTextureRectangle(): Rectangle/** Draw a pixel using geometry [Can be slow, use with care] */
function DrawPixel(posX: number, posY: number, color: Color): void/** Draw a pixel using geometry (Vector version) [Can be slow, use with care] */
function DrawPixelV(position: Vector2, color: Color): void/** Draw a line */
function DrawLine(startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void/** Draw a line (using gl lines) */
function DrawLineV(startPos: Vector2, endPos: Vector2, color: Color): void/** Draw a line (using triangles/quads) */
function DrawLineEx(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void/** Draw lines sequence (using gl lines) */
function DrawLineStrip(points: Vector2[], pointCount: number, color: Color): void/** Draw line segment cubic-bezier in-out interpolation */
function DrawLineBezier(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void/** Draw a color-filled circle */
function DrawCircle(centerX: number, centerY: number, radius: number, color: Color): void/** Draw a piece of a circle */
function DrawCircleSector(center: Vector2, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void/** Draw circle sector outline */
function DrawCircleSectorLines(center: Vector2, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void/** Draw a gradient-filled circle */
function DrawCircleGradient(centerX: number, centerY: number, radius: number, inner: Color, outer: Color): void/** Draw a color-filled circle (Vector version) */
function DrawCircleV(center: Vector2, radius: number, color: Color): void/** Draw circle outline */
function DrawCircleLines(centerX: number, centerY: number, radius: number, color: Color): void/** Draw circle outline (Vector version) */
function DrawCircleLinesV(center: Vector2, radius: number, color: Color): void/** Draw ellipse */
function DrawEllipse(centerX: number, centerY: number, radiusH: number, radiusV: number, color: Color): void/** Draw ellipse (Vector version) */
function DrawEllipseV(center: Vector2, radiusH: number, radiusV: number, color: Color): void/** Draw ellipse outline */
function DrawEllipseLines(centerX: number, centerY: number, radiusH: number, radiusV: number, color: Color): void/** Draw ellipse outline (Vector version) */
function DrawEllipseLinesV(center: Vector2, radiusH: number, radiusV: number, color: Color): void/** Draw ring */
function DrawRing(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void/** Draw ring outline */
function DrawRingLines(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void/** Draw a color-filled rectangle */
function DrawRectangle(posX: number, posY: number, width: number, height: number, color: Color): void/** Draw a color-filled rectangle (Vector version) */
function DrawRectangleV(position: Vector2, size: Vector2, color: Color): void/** Draw a color-filled rectangle */
function DrawRectangleRec(rec: Rectangle, color: Color): void/** Draw a color-filled rectangle with pro parameters */
function DrawRectanglePro(rec: Rectangle, origin: Vector2, rotation: number, color: Color): void/** Draw a vertical-gradient-filled rectangle */
function DrawRectangleGradientV(posX: number, posY: number, width: number, height: number, top: Color, bottom: Color): void/** Draw a horizontal-gradient-filled rectangle */
function DrawRectangleGradientH(posX: number, posY: number, width: number, height: number, left: Color, right: Color): void/** Draw a gradient-filled rectangle with custom vertex colors */
function DrawRectangleGradientEx(rec: Rectangle, topLeft: Color, bottomLeft: Color, bottomRight: Color, topRight: Color): void/** Draw rectangle outline */
function DrawRectangleLines(posX: number, posY: number, width: number, height: number, color: Color): void/** Draw rectangle outline with extended parameters */
function DrawRectangleLinesEx(rec: Rectangle, lineThick: number, color: Color): void/** Draw rectangle with rounded edges */
function DrawRectangleRounded(rec: Rectangle, roundness: number, segments: number, color: Color): void/** Draw rectangle lines with rounded edges */
function DrawRectangleRoundedLines(rec: Rectangle, roundness: number, segments: number, color: Color): void/** Draw rectangle with rounded edges outline */
function DrawRectangleRoundedLinesEx(rec: Rectangle, roundness: number, segments: number, lineThick: number, color: Color): void/** Draw a color-filled triangle (vertex in counter-clockwise order!) */
function DrawTriangle(v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void/** Draw triangle outline (vertex in counter-clockwise order!) */
function DrawTriangleLines(v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void/** Draw a triangle fan defined by points (first vertex is the center) */
function DrawTriangleFan(points: Vector2[], pointCount: number, color: Color): void/** Draw a triangle strip defined by points */
function DrawTriangleStrip(points: Vector2[], pointCount: number, color: Color): void/** Draw a regular polygon (Vector version) */
function DrawPoly(center: Vector2, sides: number, radius: number, rotation: number, color: Color): void/** Draw a polygon outline of n sides */
function DrawPolyLines(center: Vector2, sides: number, radius: number, rotation: number, color: Color): void/** Draw a polygon outline of n sides with extended parameters */
function DrawPolyLinesEx(center: Vector2, sides: number, radius: number, rotation: number, lineThick: number, color: Color): void/** Draw spline: Linear, minimum 2 points */
function DrawSplineLinear(points: Vector2[], pointCount: number, thick: number, color: Color): void/** Draw spline: B-Spline, minimum 4 points */
function DrawSplineBasis(points: Vector2[], pointCount: number, thick: number, color: Color): void/** Draw spline: Catmull-Rom, minimum 4 points */
function DrawSplineCatmullRom(points: Vector2[], pointCount: number, thick: number, color: Color): void/** Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...] */
function DrawSplineBezierQuadratic(points: Vector2[], pointCount: number, thick: number, color: Color): void/** Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...] */
function DrawSplineBezierCubic(points: Vector2[], pointCount: number, thick: number, color: Color): void/** Draw spline segment: Linear, 2 points */
function DrawSplineSegmentLinear(p1: Vector2, p2: Vector2, thick: number, color: Color): void/** Draw spline segment: B-Spline, 4 points */
function DrawSplineSegmentBasis(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, thick: number, color: Color): void/** Draw spline segment: Catmull-Rom, 4 points */
function DrawSplineSegmentCatmullRom(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, thick: number, color: Color): void/** Draw spline segment: Quadratic Bezier, 2 points, 1 control point */
function DrawSplineSegmentBezierQuadratic(p1: Vector2, c2: Vector2, p3: Vector2, thick: number, color: Color): void/** Draw spline segment: Cubic Bezier, 2 points, 2 control points */
function DrawSplineSegmentBezierCubic(p1: Vector2, c2: Vector2, c3: Vector2, p4: Vector2, thick: number, color: Color): void/** Get (evaluate) spline point: Linear */
function GetSplinePointLinear(startPos: Vector2, endPos: Vector2, t: number): Vector2/** Get (evaluate) spline point: B-Spline */
function GetSplinePointBasis(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, t: number): Vector2/** Get (evaluate) spline point: Catmull-Rom */
function GetSplinePointCatmullRom(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, t: number): Vector2/** Get (evaluate) spline point: Quadratic Bezier */
function GetSplinePointBezierQuad(p1: Vector2, c2: Vector2, p3: Vector2, t: number): Vector2/** Get (evaluate) spline point: Cubic Bezier */
function GetSplinePointBezierCubic(p1: Vector2, c2: Vector2, c3: Vector2, p4: Vector2, t: number): Vector2/** Check collision between two rectangles */
function CheckCollisionRecs(rec1: Rectangle, rec2: Rectangle): boolean/** Check collision between two circles */
function CheckCollisionCircles(center1: Vector2, radius1: number, center2: Vector2, radius2: number): boolean/** Check collision between circle and rectangle */
function CheckCollisionCircleRec(center: Vector2, radius: number, rec: Rectangle): boolean/** Check if circle collides with a line created betweeen two points [p1] and [p2] */
function CheckCollisionCircleLine(center: Vector2, radius: number, p1: Vector2, p2: Vector2): boolean/** Check if point is inside rectangle */
function CheckCollisionPointRec(point: Vector2, rec: Rectangle): boolean/** Check if point is inside circle */
function CheckCollisionPointCircle(point: Vector2, center: Vector2, radius: number): boolean/** Check if point is inside a triangle */
function CheckCollisionPointTriangle(point: Vector2, p1: Vector2, p2: Vector2, p3: Vector2): boolean/** Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold] */
function CheckCollisionPointLine(point: Vector2, p1: Vector2, p2: Vector2, threshold: number): boolean/** Check if point is within a polygon described by array of vertices */
function CheckCollisionPointPoly(point: Vector2, points: Vector2[], pointCount: number): boolean/** Check the collision between two lines defined by two points each, returns collision point by reference */
function CheckCollisionLines(startPos1: Vector2, endPos1: Vector2, startPos2: Vector2, endPos2: Vector2, collisionPoint: Vector2): boolean/** Get collision rectangle for two rectangles collision */
function GetCollisionRec(rec1: Rectangle, rec2: Rectangle): Rectangle/** Load image from file into CPU memory (RAM) */
function LoadImage(fileName: string): Image/** Load image from RAW file data */
function LoadImageRaw(fileName: string, width: number, height: number, format: number, headerSize: number): Image/** Load image sequence from file (frames appended to image.data) */
function LoadImageAnim(fileName: string, frames: number | number[]): Image/** Load image sequence from memory buffer */
function LoadImageAnimFromMemory(fileType: string, fileData: number[], dataSize: number, frames: number | number[]): Image/** Load image from memory buffer, fileType refers to extension: i.e. '.png' */
function LoadImageFromMemory(fileType: string, fileData: number[], dataSize: number): Image/** Load image from GPU texture data */
function LoadImageFromTexture(texture: Texture2D): Image/** Load image from screen buffer and (screenshot) */
function LoadImageFromScreen(): Image/** Check if an image is valid (data and parameters) */
function IsImageValid(image: Image): boolean/** Unload image from CPU memory (RAM) */
function UnloadImage(image: Image): void/** Export image data to file, returns true on success */
function ExportImage(image: Image, fileName: string): boolean/** Export image to memory buffer */
function ExportImageToMemory(image: Image, fileType: string, fileSize: number | number[]): string/** Export image as code file defining an array of bytes, returns true on success */
function ExportImageAsCode(image: Image, fileName: string): boolean/** Generate image: plain color */
function GenImageColor(width: number, height: number, color: Color): Image/** Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient */
function GenImageGradientLinear(width: number, height: number, direction: number, start: Color, end: Color): Image/** Generate image: radial gradient */
function GenImageGradientRadial(width: number, height: number, density: number, inner: Color, outer: Color): Image/** Generate image: square gradient */
function GenImageGradientSquare(width: number, height: number, density: number, inner: Color, outer: Color): Image/** Generate image: checked */
function GenImageChecked(width: number, height: number, checksX: number, checksY: number, col1: Color, col2: Color): Image/** Generate image: white noise */
function GenImageWhiteNoise(width: number, height: number, factor: number): Image/** Generate image: perlin noise */
function GenImagePerlinNoise(width: number, height: number, offsetX: number, offsetY: number, scale: number): Image/** Generate image: cellular algorithm, bigger tileSize means bigger cells */
function GenImageCellular(width: number, height: number, tileSize: number): Image/** Generate image: grayscale image from text data */
function GenImageText(width: number, height: number, text: string): Image/** Create an image duplicate (useful for transformations) */
function ImageCopy(image: Image): Image/** Create an image from another image piece */
function ImageFromImage(image: Image, rec: Rectangle): Image/** Create an image from a selected channel of another image (GRAYSCALE) */
function ImageFromChannel(image: Image, selectedChannel: number): Image/** Create an image from text (default font) */
function ImageText(text: string, fontSize: number, color: Color): Image/** Create an image from text (custom sprite font) */
function ImageTextEx(font: Font, text: string, fontSize: number, spacing: number, tint: Color): Image/** Convert image data to desired format */
function ImageFormat(image: Image, newFormat: number): void/** Convert image to POT (power-of-two) */
function ImageToPOT(image: Image, fill: Color): void/** Crop an image to a defined rectangle */
function ImageCrop(image: Image, crop: Rectangle): void/** Crop image depending on alpha value */
function ImageAlphaCrop(image: Image, threshold: number): void/** Clear alpha channel to desired color */
function ImageAlphaClear(image: Image, color: Color, threshold: number): void/** Apply alpha mask to image */
function ImageAlphaMask(image: Image, alphaMask: Image): void/** Premultiply alpha channel */
function ImageAlphaPremultiply(image: Image): void/** Apply Gaussian blur using a box blur approximation */
function ImageBlurGaussian(image: Image, blurSize: number): void/** Apply custom square convolution kernel to image */
function ImageKernelConvolution(image: Image, kernel: number[], kernelSize: number): void/** Resize image (Bicubic scaling algorithm) */
function ImageResize(image: Image, newWidth: number, newHeight: number): void/** Resize image (Nearest-Neighbor scaling algorithm) */
function ImageResizeNN(image: Image, newWidth: number, newHeight: number): void/** Resize canvas and fill with color */
function ImageResizeCanvas(image: Image, newWidth: number, newHeight: number, offsetX: number, offsetY: number, fill: Color): void/** Compute all mipmap levels for a provided image */
function ImageMipmaps(image: Image): void/** Dither image data to 16bpp or lower (Floyd-Steinberg dithering) */
function ImageDither(image: Image, rBpp: number, gBpp: number, bBpp: number, aBpp: number): void/** Flip image vertically */
function ImageFlipVertical(image: Image): void/** Flip image horizontally */
function ImageFlipHorizontal(image: Image): void/** Rotate image by input angle in degrees (-359 to 359) */
function ImageRotate(image: Image, degrees: number): void/** Rotate image clockwise 90deg */
function ImageRotateCW(image: Image): void/** Rotate image counter-clockwise 90deg */
function ImageRotateCCW(image: Image): void/** Modify image color: tint */
function ImageColorTint(image: Image, color: Color): void/** Modify image color: invert */
function ImageColorInvert(image: Image): void/** Modify image color: grayscale */
function ImageColorGrayscale(image: Image): void/** Modify image color: contrast (-100 to 100) */
function ImageColorContrast(image: Image, contrast: number): void/** Modify image color: brightness (-255 to 255) */
function ImageColorBrightness(image: Image, brightness: number): void/** Modify image color: replace color */
function ImageColorReplace(image: Image, color: Color, replace: Color): void/** undefined */
function LoadImageColors(image: Image): ArrayBuffer/** Load colors palette from image as a Color array (RGBA - 32bit) */
function LoadImagePalette(image: Image, maxPaletteSize: number, colorCount: number[]): Color[]/** Unload color data loaded with LoadImageColors() */
function UnloadImageColors(colors: Color[]): void/** Unload colors palette loaded with LoadImagePalette() */
function UnloadImagePalette(colors: Color[]): void/** Get image alpha border rectangle */
function GetImageAlphaBorder(image: Image, threshold: number): Rectangle/** Get image pixel color at (x, y) position */
function GetImageColor(image: Image, x: number, y: number): Color/** Clear image background with given color */
function ImageClearBackground(dst: Image, color: Color): void/** Draw pixel within an image */
function ImageDrawPixel(dst: Image, posX: number, posY: number, color: Color): void/** Draw pixel within an image (Vector version) */
function ImageDrawPixelV(dst: Image, position: Vector2, color: Color): void/** Draw line within an image */
function ImageDrawLine(dst: Image, startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void/** Draw line within an image (Vector version) */
function ImageDrawLineV(dst: Image, start: Vector2, end: Vector2, color: Color): void/** Draw a line defining thickness within an image */
function ImageDrawLineEx(dst: Image, start: Vector2, end: Vector2, thick: number, color: Color): void/** Draw a filled circle within an image */
function ImageDrawCircle(dst: Image, centerX: number, centerY: number, radius: number, color: Color): void/** Draw a filled circle within an image (Vector version) */
function ImageDrawCircleV(dst: Image, center: Vector2, radius: number, color: Color): void/** Draw circle outline within an image */
function ImageDrawCircleLines(dst: Image, centerX: number, centerY: number, radius: number, color: Color): void/** Draw circle outline within an image (Vector version) */
function ImageDrawCircleLinesV(dst: Image, center: Vector2, radius: number, color: Color): void/** Draw rectangle within an image */
function ImageDrawRectangle(dst: Image, posX: number, posY: number, width: number, height: number, color: Color): void/** Draw rectangle within an image (Vector version) */
function ImageDrawRectangleV(dst: Image, position: Vector2, size: Vector2, color: Color): void/** Draw rectangle within an image */
function ImageDrawRectangleRec(dst: Image, rec: Rectangle, color: Color): void/** Draw rectangle lines within an image */
function ImageDrawRectangleLines(dst: Image, rec: Rectangle, thick: number, color: Color): void/** Draw triangle within an image */
function ImageDrawTriangle(dst: Image, v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void/** Draw triangle with interpolated colors within an image */
function ImageDrawTriangleEx(dst: Image, v1: Vector2, v2: Vector2, v3: Vector2, c1: Color, c2: Color, c3: Color): void/** Draw triangle outline within an image */
function ImageDrawTriangleLines(dst: Image, v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void/** Draw a triangle fan defined by points within an image (first vertex is the center) */
function ImageDrawTriangleFan(dst: Image, points: Vector2[], pointCount: number, color: Color): void/** Draw a triangle strip defined by points within an image */
function ImageDrawTriangleStrip(dst: Image, points: Vector2[], pointCount: number, color: Color): void/** Draw a source image within a destination image (tint applied to source) */
function ImageDraw(dst: Image, src: Image, srcRec: Rectangle, dstRec: Rectangle, tint: Color): void/** Draw text (using default font) within an image (destination) */
function ImageDrawText(dst: Image, text: string, posX: number, posY: number, fontSize: number, color: Color): void/** Draw text (custom sprite font) within an image (destination) */
function ImageDrawTextEx(dst: Image, font: Font, text: string, position: Vector2, fontSize: number, spacing: number, tint: Color): void/** Load texture from file into GPU memory (VRAM) */
function LoadTexture(fileName: string): Texture2D/** Load texture from image data */
function LoadTextureFromImage(image: Image): Texture2D/** Load cubemap from image, multiple image cubemap layouts supported */
function LoadTextureCubemap(image: Image, layout: number): TextureCubemap/** Load texture for rendering (framebuffer) */
function LoadRenderTexture(width: number, height: number): RenderTexture2D/** Check if a texture is valid (loaded in GPU) */
function IsTextureValid(texture: Texture2D): boolean/** Unload texture from GPU memory (VRAM) */
function UnloadTexture(texture: Texture2D): void/** Check if a render texture is valid (loaded in GPU) */
function IsRenderTextureValid(target: RenderTexture2D): boolean/** Unload render texture from GPU memory (VRAM) */
function UnloadRenderTexture(target: RenderTexture2D): void/** Update GPU texture with new data (pixels should be able to fill texture) */
function UpdateTexture(texture: Texture2D, pixels: ArrayBuffer): void/** Update GPU texture rectangle with new data (pixels and rec should fit in texture) */
function UpdateTextureRec(texture: Texture2D, rec: Rectangle, pixels: ArrayBuffer): void/** Generate GPU mipmaps for a texture */
function GenTextureMipmaps(texture: Texture2D): void/** Set texture scaling filter mode */
function SetTextureFilter(texture: Texture2D, filter: number): void/** Set texture wrapping mode */
function SetTextureWrap(texture: Texture2D, wrap: number): void/** Draw a Texture2D */
function DrawTexture(texture: Texture2D, posX: number, posY: number, tint: Color): void/** Draw a Texture2D with position defined as Vector2 */
function DrawTextureV(texture: Texture2D, position: Vector2, tint: Color): void/** Draw a Texture2D with extended parameters */
function DrawTextureEx(texture: Texture2D, position: Vector2, rotation: number, scale: number, tint: Color): void/** Draw a part of a texture defined by a rectangle */
function DrawTextureRec(texture: Texture2D, source: Rectangle, position: Vector2, tint: Color): void/** Draw a part of a texture defined by a rectangle with 'pro' parameters */
function DrawTexturePro(texture: Texture2D, source: Rectangle, dest: Rectangle, origin: Vector2, rotation: number, tint: Color): void/** Draws a texture (or part of it) that stretches or shrinks nicely */
function DrawTextureNPatch(texture: Texture2D, nPatchInfo: NPatchInfo, dest: Rectangle, origin: Vector2, rotation: number, tint: Color): void/** Check if two colors are equal */
function ColorIsEqual(col1: Color, col2: Color): boolean/** Get color with alpha applied, alpha goes from 0.0f to 1.0f */
function Fade(color: Color, alpha: number): Color/** Get hexadecimal value for a Color (0xRRGGBBAA) */
function ColorToInt(color: Color): number/** Get Color normalized as float [0..1] */
function ColorNormalize(color: Color): Vector4/** Get Color from normalized values [0..1] */
function ColorFromNormalized(normalized: Vector4): Color/** Get HSV values for a Color, hue [0..360], saturation/value [0..1] */
function ColorToHSV(color: Color): Vector3/** Get a Color from HSV values, hue [0..360], saturation/value [0..1] */
function ColorFromHSV(hue: number, saturation: number, value: number): Color/** Get color multiplied with another color */
function ColorTint(color: Color, tint: Color): Color/** Get color with brightness correction, brightness factor goes from -1.0f to 1.0f */
function ColorBrightness(color: Color, factor: number): Color/** Get color with contrast correction, contrast values between -1.0f and 1.0f */
function ColorContrast(color: Color, contrast: number): Color/** Get color with alpha applied, alpha goes from 0.0f to 1.0f */
function ColorAlpha(color: Color, alpha: number): Color/** Get src alpha-blended into dst color with tint */
function ColorAlphaBlend(dst: Color, src: Color, tint: Color): Color/** Get color lerp interpolation between two colors, factor [0.0f..1.0f] */
function ColorLerp(color1: Color, color2: Color, factor: number): Color/** Get Color structure from hexadecimal value */
function GetColor(hexValue: number): Color/** Get Color from a source pixel pointer of certain format */
function GetPixelColor(srcPtr: ArrayBuffer, format: number): Color/** Set color formatted into destination pixel pointer */
function SetPixelColor(dstPtr: ArrayBuffer, color: Color, format: number): void/** Get pixel data size in bytes for certain format */
function GetPixelDataSize(width: number, height: number, format: number): number/** Get the default Font */
function GetFontDefault(): Font/** Load font from file into GPU memory (VRAM) */
function LoadFont(fileName: string): Font/** Load font from file with extended parameters, use NULL for codepoints and 0 for codepointCount to load the default character set, font size is provided in pixels height */
function LoadFontEx(fileName: string, fontSize: number, codepoints: number[], codepointCount: number): Font/** Load font from Image (XNA style) */
function LoadFontFromImage(image: Image, key: Color, firstChar: number): Font/** Load font from memory buffer, fileType refers to extension: i.e. '.ttf' */
function LoadFontFromMemory(fileType: string, fileData: number[], dataSize: number, fontSize: number, codepoints: number[], codepointCount: number): Font/** Check if a font is valid (font data loaded, WARNING: GPU texture not checked) */
function IsFontValid(font: Font): boolean/** Load font data for further use */
function LoadFontData(fileData: number[], dataSize: number, fontSize: number, codepoints: number[], codepointCount: number, type: number): GlyphInfo[]/** Generate image font atlas using chars info */
function GenImageFontAtlas(glyphs: GlyphInfo[], glyphRecs: Rectangle[] | Rectangle[][], glyphCount: number, fontSize: number, padding: number, packMethod: number): Image/** Unload font chars info data (RAM) */
function UnloadFontData(glyphs: GlyphInfo[], glyphCount: number): void/** Unload font from GPU memory (VRAM) */
function UnloadFont(font: Font): void/** Export font as code file, returns true on success */
function ExportFontAsCode(font: Font, fileName: string): boolean/** Draw current FPS */
function DrawFPS(posX: number, posY: number): void/** Draw text (using default font) */
function DrawText(text: string, posX: number, posY: number, fontSize: number, color: Color): void/** Draw text using font and additional parameters */
function DrawTextEx(font: Font, text: string, position: Vector2, fontSize: number, spacing: number, tint: Color): void/** Draw text using Font and pro parameters (rotation) */
function DrawTextPro(font: Font, text: string, position: Vector2, origin: Vector2, rotation: number, fontSize: number, spacing: number, tint: Color): void/** Draw one character (codepoint) */
function DrawTextCodepoint(font: Font, codepoint: number, position: Vector2, fontSize: number, tint: Color): void/** Draw multiple character (codepoint) */
function DrawTextCodepoints(font: Font, codepoints: number[], codepointCount: number, position: Vector2, fontSize: number, spacing: number, tint: Color): void/** Set vertical line spacing when drawing with line-breaks */
function SetTextLineSpacing(spacing: number): void/** Measure string width for default font */
function MeasureText(text: string, fontSize: number): number/** Measure string size for Font */
function MeasureTextEx(font: Font, text: string, fontSize: number, spacing: number): Vector2/** Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found */
function GetGlyphIndex(font: Font, codepoint: number): number/** Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found */
function GetGlyphInfo(font: Font, codepoint: number): GlyphInfo/** Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found */
function GetGlyphAtlasRec(font: Font, codepoint: number): Rectangle/** Load UTF-8 text encoded from codepoints array */
function LoadUTF8(codepoints: number[], length: number): string/** Unload UTF-8 text encoded from codepoints array */
function UnloadUTF8(text: string): void/** Load all codepoints from a UTF-8 text string, codepoints count returned by parameter */
function LoadCodepoints(text: string, count: number | number[]): number[]/** Get total number of codepoints in a UTF-8 encoded string */
function GetCodepointCount(text: string): number/** Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure */
function GetCodepoint(text: string, codepointSize: number | number[]): number/** Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure */
function GetCodepointNext(text: string, codepointSize: number | number[]): number/** Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure */
function GetCodepointPrevious(text: string, codepointSize: number | number[]): number/** Encode one codepoint into UTF-8 byte array (array length returned as parameter) */
function CodepointToUTF8(codepoint: number, utf8Size: number[]): string/** Load text as separate lines ('\n') */
function LoadTextLines(text: string, count: number | number[]): string[]/** Unload text lines */
function UnloadTextLines(text: string[]): void/** Check if two text string are equal */
function TextIsEqual(text1: string, text2: string): boolean/** Get text length, checks for '\0' ending */
function TextLength(text: string): number/** Text formatting with variables (sprintf() style) */
function TextFormat(text: string, ...args: any): string/** Get a piece of a text string */
function TextSubtext(text: string, position: number, length: number): string/** Replace text string (WARNING: memory must be freed!) */
function TextReplace(text: string, replace: string, by: string): string/** Insert text in a position (WARNING: memory must be freed!) */
function TextInsert(text: string, insert: string, position: number): string/** Join text strings with delimiter */
function TextJoin(textList: string[], count: number, delimiter: string): string/** Split text into multiple strings, using MAX_TEXTSPLIT_COUNT static strings */
function TextSplit(text: string, delimiter: string, count: number | number[]): string[]/** Append text at specific position and move cursor! */
function TextAppend(text: string, append: string, position: number | number[]): void/** Find first text occurrence within a string, -1 if not found */
function TextFindIndex(text: string, find: string): number/** Get upper case version of provided string */
function TextToUpper(text: string): string/** Get lower case version of provided string */
function TextToLower(text: string): string/** Get Pascal case notation version of provided string */
function TextToPascal(text: string): string/** Get Snake case notation version of provided string */
function TextToSnake(text: string): string/** Get Camel case notation version of provided string */
function TextToCamel(text: string): string/** Get integer value from text */
function TextToInteger(text: string): number/** Get float value from text */
function TextToFloat(text: string): number/** Draw a line in 3D world space */
function DrawLine3D(startPos: Vector3, endPos: Vector3, color: Color): void/** Draw a point in 3D space, actually a small line */
function DrawPoint3D(position: Vector3, color: Color): void/** Draw a circle in 3D world space */
function DrawCircle3D(center: Vector3, radius: number, rotationAxis: Vector3, rotationAngle: number, color: Color): void/** Draw a color-filled triangle (vertex in counter-clockwise order!) */
function DrawTriangle3D(v1: Vector3, v2: Vector3, v3: Vector3, color: Color): void/** Draw a triangle strip defined by points */
function DrawTriangleStrip3D(points: Vector3[], pointCount: number, color: Color): void/** Draw cube */
function DrawCube(position: Vector3, width: number, height: number, length: number, color: Color): void/** Draw cube (Vector version) */
function DrawCubeV(position: Vector3, size: Vector3, color: Color): void/** Draw cube wires */
function DrawCubeWires(position: Vector3, width: number, height: number, length: number, color: Color): void/** Draw cube wires (Vector version) */
function DrawCubeWiresV(position: Vector3, size: Vector3, color: Color): void/** Draw sphere */
function DrawSphere(centerPos: Vector3, radius: number, color: Color): void/** Draw sphere with extended parameters */
function DrawSphereEx(centerPos: Vector3, radius: number, rings: number, slices: number, color: Color): void/** Draw sphere wires */
function DrawSphereWires(centerPos: Vector3, radius: number, rings: number, slices: number, color: Color): void/** Draw a cylinder/cone */
function DrawCylinder(position: Vector3, radiusTop: number, radiusBottom: number, height: number, slices: number, color: Color): void/** Draw a cylinder with base at startPos and top at endPos */
function DrawCylinderEx(startPos: Vector3, endPos: Vector3, startRadius: number, endRadius: number, sides: number, color: Color): void/** Draw a cylinder/cone wires */
function DrawCylinderWires(position: Vector3, radiusTop: number, radiusBottom: number, height: number, slices: number, color: Color): void/** Draw a cylinder wires with base at startPos and top at endPos */
function DrawCylinderWiresEx(startPos: Vector3, endPos: Vector3, startRadius: number, endRadius: number, sides: number, color: Color): void/** Draw a capsule with the center of its sphere caps at startPos and endPos */
function DrawCapsule(startPos: Vector3, endPos: Vector3, radius: number, slices: number, rings: number, color: Color): void/** Draw capsule wireframe with the center of its sphere caps at startPos and endPos */
function DrawCapsuleWires(startPos: Vector3, endPos: Vector3, radius: number, slices: number, rings: number, color: Color): void/** Draw a plane XZ */
function DrawPlane(centerPos: Vector3, size: Vector2, color: Color): void/** Draw a ray line */
function DrawRay(ray: Ray, color: Color): void/** Draw a grid (centered at (0, 0, 0)) */
function DrawGrid(slices: number, spacing: number): void/** Load model from files (meshes and materials) */
function LoadModel(fileName: string): Model/** Load model from generated mesh (default material) */
function LoadModelFromMesh(mesh: Mesh): Model/** Check if a model is valid (loaded in GPU, VAO/VBOs) */
function IsModelValid(model: Model): boolean/** Unload model (including meshes) from memory (RAM and/or VRAM) */
function UnloadModel(model: Model): void/** Compute model bounding box limits (considers all meshes) */
function GetModelBoundingBox(model: Model): BoundingBox/** Draw a model (with texture if set) */
function DrawModel(model: Model, position: Vector3, scale: number, tint: Color): void/** Draw a model with extended parameters */
function DrawModelEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void/** Draw a model wires (with texture if set) */
function DrawModelWires(model: Model, position: Vector3, scale: number, tint: Color): void/** Draw a model wires (with texture if set) with extended parameters */
function DrawModelWiresEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void/** Draw a model as points */
function DrawModelPoints(model: Model, position: Vector3, scale: number, tint: Color): void/** Draw a model as points with extended parameters */
function DrawModelPointsEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void/** Draw bounding box (wires) */
function DrawBoundingBox(box: BoundingBox, color: Color): void/** Draw a billboard texture */
function DrawBillboard(camera: Camera, texture: Texture2D, position: Vector3, scale: number, tint: Color): void/** Draw a billboard texture defined by source */
function DrawBillboardRec(camera: Camera, texture: Texture2D, source: Rectangle, position: Vector3, size: Vector2, tint: Color): void/** Draw a billboard texture defined by source and rotation */
function DrawBillboardPro(camera: Camera, texture: Texture2D, source: Rectangle, position: Vector3, up: Vector3, size: Vector2, origin: Vector2, rotation: number, tint: Color): void/** Upload mesh vertex data in GPU and provide VAO/VBO ids */
function UploadMesh(mesh: Mesh, dynamic: boolean): void/** Update mesh vertex data in GPU for a specific buffer index */
function UpdateMeshBuffer(mesh: Mesh, index: number, data: ArrayBuffer, dataSize: number, offset: number): void/** Unload mesh data from CPU and GPU */
function UnloadMesh(mesh: Mesh): void/** Draw a 3d mesh with material and transform */
function DrawMesh(mesh: Mesh, material: Material, transform: Matrix): void/** Draw multiple mesh instances with material and different transforms */
function DrawMeshInstanced(mesh: Mesh, material: Material, transforms: Matrix[], instances: number): void/** Compute mesh bounding box limits */
function GetMeshBoundingBox(mesh: Mesh): BoundingBox/** Compute mesh tangents */
function GenMeshTangents(mesh: Mesh): void/** Export mesh data to file, returns true on success */
function ExportMesh(mesh: Mesh, fileName: string): boolean/** Export mesh as code file (.h) defining multiple arrays of vertex attributes */
function ExportMeshAsCode(mesh: Mesh, fileName: string): boolean/** Generate polygonal mesh */
function GenMeshPoly(sides: number, radius: number): Mesh/** Generate plane mesh (with subdivisions) */
function GenMeshPlane(width: number, length: number, resX: number, resZ: number): Mesh/** Generate cuboid mesh */
function GenMeshCube(width: number, height: number, length: number): Mesh/** Generate sphere mesh (standard sphere) */
function GenMeshSphere(radius: number, rings: number, slices: number): Mesh/** Generate half-sphere mesh (no bottom cap) */
function GenMeshHemiSphere(radius: number, rings: number, slices: number): Mesh/** Generate cylinder mesh */
function GenMeshCylinder(radius: number, height: number, slices: number): Mesh/** Generate cone/pyramid mesh */
function GenMeshCone(radius: number, height: number, slices: number): Mesh/** Generate torus mesh */
function GenMeshTorus(radius: number, size: number, radSeg: number, sides: number): Mesh/** Generate trefoil knot mesh */
function GenMeshKnot(radius: number, size: number, radSeg: number, sides: number): Mesh/** Generate heightmap mesh from image data */
function GenMeshHeightmap(heightmap: Image, size: Vector3): Mesh/** Generate cubes-based map mesh from image data */
function GenMeshCubicmap(cubicmap: Image, cubeSize: Vector3): Mesh/** Load materials from model file */
function LoadMaterials(fileName: string, materialCount: number[]): Material[]/** Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps) */
function LoadMaterialDefault(): Material/** Check if a material is valid (shader assigned, map textures loaded in GPU) */
function IsMaterialValid(material: Material): boolean/** Unload material from GPU memory (VRAM) */
function UnloadMaterial(material: Material): void/** Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...) */
function SetMaterialTexture(material: Material, mapType: number, texture: Texture2D): void/** Set material for a mesh */
function SetModelMeshMaterial(model: Model, meshId: number, materialId: number): void/** Load model animations from file */
function LoadModelAnimations(fileName: string, animCount: number | number[]): ModelAnimation[]/** Update model animation pose (CPU) */
function UpdateModelAnimation(model: Model, anim: ModelAnimation, frame: number): void/** Update model animation mesh bone matrices (GPU skinning) */
function UpdateModelAnimationBones(model: Model, anim: ModelAnimation, frame: number): void/** Unload animation data */
function UnloadModelAnimation(anim: ModelAnimation): void/** Unload animation array data */
function UnloadModelAnimations(animations: ModelAnimation[], animCount: number): void/** Check model animation skeleton match */
function IsModelAnimationValid(model: Model, anim: ModelAnimation): boolean/** Check collision between two spheres */
function CheckCollisionSpheres(center1: Vector3, radius1: number, center2: Vector3, radius2: number): boolean/** Check collision between two bounding boxes */
function CheckCollisionBoxes(box1: BoundingBox, box2: BoundingBox): boolean/** Check collision between box and sphere */
function CheckCollisionBoxSphere(box: BoundingBox, center: Vector3, radius: number): boolean/** Get collision info between ray and sphere */
function GetRayCollisionSphere(ray: Ray, center: Vector3, radius: number): RayCollision/** Get collision info between ray and box */
function GetRayCollisionBox(ray: Ray, box: BoundingBox): RayCollision/** Get collision info between ray and mesh */
function GetRayCollisionMesh(ray: Ray, mesh: Mesh, transform: Matrix): RayCollision/** Get collision info between ray and triangle */
function GetRayCollisionTriangle(ray: Ray, p1: Vector3, p2: Vector3, p3: Vector3): RayCollision/** Get collision info between ray and quad */
function GetRayCollisionQuad(ray: Ray, p1: Vector3, p2: Vector3, p3: Vector3, p4: Vector3): RayCollision/** Initialize audio device and context */
function InitAudioDevice(): void/** Close the audio device and context */
function CloseAudioDevice(): void/** Check if audio device has been initialized successfully */
function IsAudioDeviceReady(): boolean/** Set master volume (listener) */
function SetMasterVolume(volume: number): void/** Get master volume (listener) */
function GetMasterVolume(): number/** Load wave data from file */
function LoadWave(fileName: string): Wave/** Load wave from memory buffer, fileType refers to extension: i.e. '.wav' */
function LoadWaveFromMemory(fileType: string, fileData: number[], dataSize: number): Wave/** Checks if wave data is valid (data loaded and parameters) */
function IsWaveValid(wave: Wave): boolean/** Load sound from file */
function LoadSound(fileName: string): Sound/** Load sound from wave data */
function LoadSoundFromWave(wave: Wave): Sound/** Create a new sound that shares the same sample data as the source sound, does not own the sound data */
function LoadSoundAlias(source: Sound): Sound/** Checks if a sound is valid (data loaded and buffers initialized) */
function IsSoundValid(sound: Sound): boolean/** Update sound buffer with new data (data and frame count should fit in sound) */
function UpdateSound(sound: Sound, data: ArrayBuffer, sampleCount: number): void/** Unload wave data */
function UnloadWave(wave: Wave): void/** Unload sound */
function UnloadSound(sound: Sound): void/** Unload a sound alias (does not deallocate sample data) */
function UnloadSoundAlias(alias: Sound): void/** Export wave data to file, returns true on success */
function ExportWave(wave: Wave, fileName: string): boolean/** Export wave sample data to code (.h), returns true on success */
function ExportWaveAsCode(wave: Wave, fileName: string): boolean/** Play a sound */
function PlaySound(sound: Sound): void/** Stop playing a sound */
function StopSound(sound: Sound): void/** Pause a sound */
function PauseSound(sound: Sound): void/** Resume a paused sound */
function ResumeSound(sound: Sound): void/** Check if a sound is currently playing */
function IsSoundPlaying(sound: Sound): boolean/** Set volume for a sound (1.0 is max level) */
function SetSoundVolume(sound: Sound, volume: number): void/** Set pitch for a sound (1.0 is base level) */
function SetSoundPitch(sound: Sound, pitch: number): void/** Set pan for a sound (0.5 is center) */
function SetSoundPan(sound: Sound, pan: number): void/** Copy a wave to a new wave */
function WaveCopy(wave: Wave): Wave/** Crop a wave to defined frames range */
function WaveCrop(wave: Wave, initFrame: number, finalFrame: number): void/** Convert wave data to desired format */
function WaveFormat(wave: Wave, sampleRate: number, sampleSize: number, channels: number): void/** Load samples data from wave as a 32bit float data array */
function LoadWaveSamples(wave: Wave): number[]/** Unload samples data loaded with LoadWaveSamples() */
function UnloadWaveSamples(samples: number[]): void/** Load music stream from file */
function LoadMusicStream(fileName: string): Music/** Load music stream from data */
function LoadMusicStreamFromMemory(fileType: string, data: number[], dataSize: number): Music/** Checks if a music stream is valid (context and buffers initialized) */
function IsMusicValid(music: Music): boolean/** Unload music stream */
function UnloadMusicStream(music: Music): void/** Start music playing */
function PlayMusicStream(music: Music): void/** Check if music is playing */
function IsMusicStreamPlaying(music: Music): boolean/** Updates buffers for music streaming */
function UpdateMusicStream(music: Music): void/** Stop music playing */
function StopMusicStream(music: Music): void/** Pause music playing */
function PauseMusicStream(music: Music): void/** Resume playing paused music */
function ResumeMusicStream(music: Music): void/** Seek music to a position (in seconds) */
function SeekMusicStream(music: Music, position: number): void/** Set volume for music (1.0 is max level) */
function SetMusicVolume(music: Music, volume: number): void/** Set pitch for a music (1.0 is base level) */
function SetMusicPitch(music: Music, pitch: number): void/** Set pan for a music (0.5 is center) */
function SetMusicPan(music: Music, pan: number): void/** Get music time length (in seconds) */
function GetMusicTimeLength(music: Music): number/** Get current music time played (in seconds) */
function GetMusicTimePlayed(music: Music): number/** Load audio stream (to stream raw audio pcm data) */
function LoadAudioStream(sampleRate: number, sampleSize: number, channels: number): AudioStream/** Checks if an audio stream is valid (buffers initialized) */
function IsAudioStreamValid(stream: AudioStream): boolean/** Unload audio stream and free memory */
function UnloadAudioStream(stream: AudioStream): void/** Update audio stream buffers with data */
function UpdateAudioStream(stream: AudioStream, data: ArrayBuffer, frameCount: number): void/** Check if any audio stream buffers requires refill */
function IsAudioStreamProcessed(stream: AudioStream): boolean/** Play audio stream */
function PlayAudioStream(stream: AudioStream): void/** Pause audio stream */
function PauseAudioStream(stream: AudioStream): void/** Resume audio stream */
function ResumeAudioStream(stream: AudioStream): void/** Check if audio stream is playing */
function IsAudioStreamPlaying(stream: AudioStream): boolean/** Stop audio stream */
function StopAudioStream(stream: AudioStream): void/** Set volume for audio stream (1.0 is max level) */
function SetAudioStreamVolume(stream: AudioStream, volume: number): void/** Set pitch for audio stream (1.0 is base level) */
function SetAudioStreamPitch(stream: AudioStream, pitch: number): void/** Set pan for audio stream (0.5 is centered) */
function SetAudioStreamPan(stream: AudioStream, pan: number): void/** Default size for new audio streams */
function SetAudioStreamBufferSizeDefault(size: number): void/** Attach audio stream processor to the entire audio pipeline, receives frames x 2 samples as 'float' (stereo) */
function AttachAudioMixedProcessor(processor: AudioMixedProcessor): void/** Detach audio stream processor from the entire audio pipeline */
function DetachAudioMixedProcessor(processor: AudioCallback): void/** Get a ray trace from screen position (i.e mouse) */
function GetMouseRay(position: Vector2, camera: Camera): Ray/** Set to try enabling V-Sync on GPU */
var FLAG_VSYNC_HINT: number/** Set to run program in fullscreen */
var FLAG_FULLSCREEN_MODE: number/** Set to allow resizable window */
var FLAG_WINDOW_RESIZABLE: number/** Set to disable window decoration (frame and buttons) */
var FLAG_WINDOW_UNDECORATED: number/** Set to hide window */
var FLAG_WINDOW_HIDDEN: number/** Set to minimize window (iconify) */
var FLAG_WINDOW_MINIMIZED: number/** Set to maximize window (expanded to monitor) */
var FLAG_WINDOW_MAXIMIZED: number/** Set to window non focused */
var FLAG_WINDOW_UNFOCUSED: number/** Set to window always on top */
var FLAG_WINDOW_TOPMOST: number/** Set to allow windows running while minimized */
var FLAG_WINDOW_ALWAYS_RUN: number/** Set to allow transparent framebuffer */
var FLAG_WINDOW_TRANSPARENT: number/** Set to support HighDPI */
var FLAG_WINDOW_HIGHDPI: number/** Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED */
var FLAG_WINDOW_MOUSE_PASSTHROUGH: number/** Set to run program in borderless windowed mode */
var FLAG_BORDERLESS_WINDOWED_MODE: number/** Set to try enabling MSAA 4X */
var FLAG_MSAA_4X_HINT: number/**  */
var FLAG_INTERLACED_HINT: number/** Display all logs */
var LOG_ALL: number/** Trace logging, intended for internal use only */
var LOG_TRACE: number/** Debug logging, used for internal debugging, it should be disabled on release builds */
var LOG_DEBUG: number/** Info logging, used for program execution info */
var LOG_INFO: number/** Warning logging, used on recoverable failures */
var LOG_WARNING: number/** Error logging, used on unrecoverable failures */
var LOG_ERROR: number/** Fatal logging, used to abort program: exit(EXIT_FAILURE) */
var LOG_FATAL: number/**  */
var LOG_NONE: number/** Key: NULL, used for no key pressed */
var KEY_NULL: number/** Key: ' */
var KEY_APOSTROPHE: number/** Key: , */
var KEY_COMMA: number/** Key: - */
var KEY_MINUS: number/** Key: . */
var KEY_PERIOD: number/** Key: / */
var KEY_SLASH: number/** Key: 0 */
var KEY_ZERO: number/** Key: 1 */
var KEY_ONE: number/** Key: 2 */
var KEY_TWO: number/** Key: 3 */
var KEY_THREE: number/** Key: 4 */
var KEY_FOUR: number/** Key: 5 */
var KEY_FIVE: number/** Key: 6 */
var KEY_SIX: number/** Key: 7 */
var KEY_SEVEN: number/** Key: 8 */
var KEY_EIGHT: number/** Key: 9 */
var KEY_NINE: number/** Key: ; */
var KEY_SEMICOLON: number/** Key: = */
var KEY_EQUAL: number/** Key: A | a */
var KEY_A: number/** Key: B | b */
var KEY_B: number/** Key: C | c */
var KEY_C: number/** Key: D | d */
var KEY_D: number/** Key: E | e */
var KEY_E: number/** Key: F | f */
var KEY_F: number/** Key: G | g */
var KEY_G: number/** Key: H | h */
var KEY_H: number/** Key: I | i */
var KEY_I: number/** Key: J | j */
var KEY_J: number/** Key: K | k */
var KEY_K: number/** Key: L | l */
var KEY_L: number/** Key: M | m */
var KEY_M: number/** Key: N | n */
var KEY_N: number/** Key: O | o */
var KEY_O: number/** Key: P | p */
var KEY_P: number/** Key: Q | q */
var KEY_Q: number/** Key: R | r */
var KEY_R: number/** Key: S | s */
var KEY_S: number/** Key: T | t */
var KEY_T: number/** Key: U | u */
var KEY_U: number/** Key: V | v */
var KEY_V: number/** Key: W | w */
var KEY_W: number/** Key: X | x */
var KEY_X: number/** Key: Y | y */
var KEY_Y: number/** Key: Z | z */
var KEY_Z: number/** Key: [ */
var KEY_LEFT_BRACKET: number/** Key: '\' */
var KEY_BACKSLASH: number/** Key: ] */
var KEY_RIGHT_BRACKET: number/** Key: ` */
var KEY_GRAVE: number/** Key: Space */
var KEY_SPACE: number/** Key: Esc */
var KEY_ESCAPE: number/** Key: Enter */
var KEY_ENTER: number/** Key: Tab */
var KEY_TAB: number/** Key: Backspace */
var KEY_BACKSPACE: number/** Key: Ins */
var KEY_INSERT: number/** Key: Del */
var KEY_DELETE: number/** Key: Cursor right */
var KEY_RIGHT: number/** Key: Cursor left */
var KEY_LEFT: number/** Key: Cursor down */
var KEY_DOWN: number/** Key: Cursor up */
var KEY_UP: number/** Key: Page up */
var KEY_PAGE_UP: number/** Key: Page down */
var KEY_PAGE_DOWN: number/** Key: Home */
var KEY_HOME: number/** Key: End */
var KEY_END: number/** Key: Caps lock */
var KEY_CAPS_LOCK: number/** Key: Scroll down */
var KEY_SCROLL_LOCK: number/** Key: Num lock */
var KEY_NUM_LOCK: number/** Key: Print screen */
var KEY_PRINT_SCREEN: number/** Key: Pause */
var KEY_PAUSE: number/** Key: F1 */
var KEY_F1: number/** Key: F2 */
var KEY_F2: number/** Key: F3 */
var KEY_F3: number/** Key: F4 */
var KEY_F4: number/** Key: F5 */
var KEY_F5: number/** Key: F6 */
var KEY_F6: number/** Key: F7 */
var KEY_F7: number/** Key: F8 */
var KEY_F8: number/** Key: F9 */
var KEY_F9: number/** Key: F10 */
var KEY_F10: number/** Key: F11 */
var KEY_F11: number/** Key: F12 */
var KEY_F12: number/** Key: Shift left */
var KEY_LEFT_SHIFT: number/** Key: Control left */
var KEY_LEFT_CONTROL: number/** Key: Alt left */
var KEY_LEFT_ALT: number/** Key: Super left */
var KEY_LEFT_SUPER: number/** Key: Shift right */
var KEY_RIGHT_SHIFT: number/** Key: Control right */
var KEY_RIGHT_CONTROL: number/** Key: Alt right */
var KEY_RIGHT_ALT: number/** Key: Super right */
var KEY_RIGHT_SUPER: number/** Key: KB menu */
var KEY_KB_MENU: number/** Key: Keypad 0 */
var KEY_KP_0: number/** Key: Keypad 1 */
var KEY_KP_1: number/** Key: Keypad 2 */
var KEY_KP_2: number/** Key: Keypad 3 */
var KEY_KP_3: number/** Key: Keypad 4 */
var KEY_KP_4: number/** Key: Keypad 5 */
var KEY_KP_5: number/** Key: Keypad 6 */
var KEY_KP_6: number/** Key: Keypad 7 */
var KEY_KP_7: number/** Key: Keypad 8 */
var KEY_KP_8: number/** Key: Keypad 9 */
var KEY_KP_9: number/** Key: Keypad . */
var KEY_KP_DECIMAL: number/** Key: Keypad / */
var KEY_KP_DIVIDE: number/** Key: Keypad * */
var KEY_KP_MULTIPLY: number/** Key: Keypad - */
var KEY_KP_SUBTRACT: number/** Key: Keypad + */
var KEY_KP_ADD: number/** Key: Keypad Enter */
var KEY_KP_ENTER: number/** Key: Keypad = */
var KEY_KP_EQUAL: number/** Key: Android back button */
var KEY_BACK: number/** Key: Android menu button */
var KEY_MENU: number/** Key: Android volume up button */
var KEY_VOLUME_UP: number/**  */
var KEY_VOLUME_DOWN: number/** Mouse button left */
var MOUSE_BUTTON_LEFT: number/** Mouse button right */
var MOUSE_BUTTON_RIGHT: number/** Mouse button middle (pressed wheel) */
var MOUSE_BUTTON_MIDDLE: number/** Mouse button side (advanced mouse device) */
var MOUSE_BUTTON_SIDE: number/** Mouse button extra (advanced mouse device) */
var MOUSE_BUTTON_EXTRA: number/** Mouse button forward (advanced mouse device) */
var MOUSE_BUTTON_FORWARD: number/** Mouse button back (advanced mouse device) */
var MOUSE_BUTTON_BACK: number/** Mouse button left */
var MOUSE_LEFT_BUTTON: number/** Mouse button right */
var MOUSE_RIGHT_BUTTON: number/** Mouse button middle (pressed wheel) */
var MOUSE_MIDDLE_BUTTON: number/** Default pointer shape */
var MOUSE_CURSOR_DEFAULT: number/** Arrow shape */
var MOUSE_CURSOR_ARROW: number/** Text writing cursor shape */
var MOUSE_CURSOR_IBEAM: number/** Cross shape */
var MOUSE_CURSOR_CROSSHAIR: number/** Pointing hand cursor */
var MOUSE_CURSOR_POINTING_HAND: number/** Horizontal resize/move arrow shape */
var MOUSE_CURSOR_RESIZE_EW: number/** Vertical resize/move arrow shape */
var MOUSE_CURSOR_RESIZE_NS: number/** Top-left to bottom-right diagonal resize/move arrow shape */
var MOUSE_CURSOR_RESIZE_NWSE: number/** The top-right to bottom-left diagonal resize/move arrow shape */
var MOUSE_CURSOR_RESIZE_NESW: number/** The omnidirectional resize/move cursor shape */
var MOUSE_CURSOR_RESIZE_ALL: number/**  */
var MOUSE_CURSOR_NOT_ALLOWED: number/** Unknown button, just for error checking */
var GAMEPAD_BUTTON_UNKNOWN: number/** Gamepad left DPAD up button */
var GAMEPAD_BUTTON_LEFT_FACE_UP: number/** Gamepad left DPAD right button */
var GAMEPAD_BUTTON_LEFT_FACE_RIGHT: number/** Gamepad left DPAD down button */
var GAMEPAD_BUTTON_LEFT_FACE_DOWN: number/** Gamepad left DPAD left button */
var GAMEPAD_BUTTON_LEFT_FACE_LEFT: number/** Gamepad right button up (i.e. PS3: Triangle, Xbox: Y) */
var GAMEPAD_BUTTON_RIGHT_FACE_UP: number/** Gamepad right button right (i.e. PS3: Circle, Xbox: B) */
var GAMEPAD_BUTTON_RIGHT_FACE_RIGHT: number/** Gamepad right button down (i.e. PS3: Cross, Xbox: A) */
var GAMEPAD_BUTTON_RIGHT_FACE_DOWN: number/** Gamepad right button left (i.e. PS3: Square, Xbox: X) */
var GAMEPAD_BUTTON_RIGHT_FACE_LEFT: number/** Gamepad top/back trigger left (first), it could be a trailing button */
var GAMEPAD_BUTTON_LEFT_TRIGGER_1: number/** Gamepad top/back trigger left (second), it could be a trailing button */
var GAMEPAD_BUTTON_LEFT_TRIGGER_2: number/** Gamepad top/back trigger right (first), it could be a trailing button */
var GAMEPAD_BUTTON_RIGHT_TRIGGER_1: number/** Gamepad top/back trigger right (second), it could be a trailing button */
var GAMEPAD_BUTTON_RIGHT_TRIGGER_2: number/** Gamepad center buttons, left one (i.e. PS3: Select) */
var GAMEPAD_BUTTON_MIDDLE_LEFT: number/** Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX) */
var GAMEPAD_BUTTON_MIDDLE: number/** Gamepad center buttons, right one (i.e. PS3: Start) */
var GAMEPAD_BUTTON_MIDDLE_RIGHT: number/** Gamepad joystick pressed button left */
var GAMEPAD_BUTTON_LEFT_THUMB: number/**  */
var GAMEPAD_BUTTON_RIGHT_THUMB: number/** Gamepad left stick X axis */
var GAMEPAD_AXIS_LEFT_X: number/** Gamepad left stick Y axis */
var GAMEPAD_AXIS_LEFT_Y: number/** Gamepad right stick X axis */
var GAMEPAD_AXIS_RIGHT_X: number/** Gamepad right stick Y axis */
var GAMEPAD_AXIS_RIGHT_Y: number/** Gamepad back trigger left, pressure level: [1..-1] */
var GAMEPAD_AXIS_LEFT_TRIGGER: number/**  */
var GAMEPAD_AXIS_RIGHT_TRIGGER: number/** Albedo material (same as: MATERIAL_MAP_DIFFUSE) */
var MATERIAL_MAP_ALBEDO: number/** Metalness material (same as: MATERIAL_MAP_SPECULAR) */
var MATERIAL_MAP_METALNESS: number/** Normal material */
var MATERIAL_MAP_NORMAL: number/** Roughness material */
var MATERIAL_MAP_ROUGHNESS: number/** Ambient occlusion material */
var MATERIAL_MAP_OCCLUSION: number/** Emission material */
var MATERIAL_MAP_EMISSION: number/** Heightmap material */
var MATERIAL_MAP_HEIGHT: number/** Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP) */
var MATERIAL_MAP_CUBEMAP: number/** Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP) */
var MATERIAL_MAP_IRRADIANCE: number/** Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP) */
var MATERIAL_MAP_PREFILTER: number/**  */
var MATERIAL_MAP_BRDF: number/** Albedo material (same as: MATERIAL_MAP_DIFFUSE) */
var MATERIAL_MAP_DIFFUSE: number/** Metalness material (same as: MATERIAL_MAP_SPECULAR) */
var MATERIAL_MAP_SPECULAR: number/** Shader location: vertex attribute: position */
var SHADER_LOC_VERTEX_POSITION: number/** Shader location: vertex attribute: texcoord01 */
var SHADER_LOC_VERTEX_TEXCOORD01: number/** Shader location: vertex attribute: texcoord02 */
var SHADER_LOC_VERTEX_TEXCOORD02: number/** Shader location: vertex attribute: normal */
var SHADER_LOC_VERTEX_NORMAL: number/** Shader location: vertex attribute: tangent */
var SHADER_LOC_VERTEX_TANGENT: number/** Shader location: vertex attribute: color */
var SHADER_LOC_VERTEX_COLOR: number/** Shader location: matrix uniform: model-view-projection */
var SHADER_LOC_MATRIX_MVP: number/** Shader location: matrix uniform: view (camera transform) */
var SHADER_LOC_MATRIX_VIEW: number/** Shader location: matrix uniform: projection */
var SHADER_LOC_MATRIX_PROJECTION: number/** Shader location: matrix uniform: model (transform) */
var SHADER_LOC_MATRIX_MODEL: number/** Shader location: matrix uniform: normal */
var SHADER_LOC_MATRIX_NORMAL: number/** Shader location: vector uniform: view */
var SHADER_LOC_VECTOR_VIEW: number/** Shader location: vector uniform: diffuse color */
var SHADER_LOC_COLOR_DIFFUSE: number/** Shader location: vector uniform: specular color */
var SHADER_LOC_COLOR_SPECULAR: number/** Shader location: vector uniform: ambient color */
var SHADER_LOC_COLOR_AMBIENT: number/** Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE) */
var SHADER_LOC_MAP_ALBEDO: number/** Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR) */
var SHADER_LOC_MAP_METALNESS: number/** Shader location: sampler2d texture: normal */
var SHADER_LOC_MAP_NORMAL: number/** Shader location: sampler2d texture: roughness */
var SHADER_LOC_MAP_ROUGHNESS: number/** Shader location: sampler2d texture: occlusion */
var SHADER_LOC_MAP_OCCLUSION: number/** Shader location: sampler2d texture: emission */
var SHADER_LOC_MAP_EMISSION: number/** Shader location: sampler2d texture: height */
var SHADER_LOC_MAP_HEIGHT: number/** Shader location: samplerCube texture: cubemap */
var SHADER_LOC_MAP_CUBEMAP: number/** Shader location: samplerCube texture: irradiance */
var SHADER_LOC_MAP_IRRADIANCE: number/** Shader location: samplerCube texture: prefilter */
var SHADER_LOC_MAP_PREFILTER: number/** Shader location: sampler2d texture: brdf */
var SHADER_LOC_MAP_BRDF: number/** Shader location: vertex attribute: boneIds */
var SHADER_LOC_VERTEX_BONEIDS: number/** Shader location: vertex attribute: boneWeights */
var SHADER_LOC_VERTEX_BONEWEIGHTS: number/** Shader location: array of matrices uniform: boneMatrices */
var SHADER_LOC_BONE_MATRICES: number/**  */
var SHADER_LOC_VERTEX_INSTANCE_TX: number/** Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE) */
var SHADER_LOC_MAP_DIFFUSE: number/** Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR) */
var SHADER_LOC_MAP_SPECULAR: number/** Shader uniform type: float */
var SHADER_UNIFORM_FLOAT: number/** Shader uniform type: vec2 (2 float) */
var SHADER_UNIFORM_VEC2: number/** Shader uniform type: vec3 (3 float) */
var SHADER_UNIFORM_VEC3: number/** Shader uniform type: vec4 (4 float) */
var SHADER_UNIFORM_VEC4: number/** Shader uniform type: int */
var SHADER_UNIFORM_INT: number/** Shader uniform type: ivec2 (2 int) */
var SHADER_UNIFORM_IVEC2: number/** Shader uniform type: ivec3 (3 int) */
var SHADER_UNIFORM_IVEC3: number/** Shader uniform type: ivec4 (4 int) */
var SHADER_UNIFORM_IVEC4: number/** Shader uniform type: unsigned int */
var SHADER_UNIFORM_UINT: number/** Shader uniform type: uivec2 (2 unsigned int) */
var SHADER_UNIFORM_UIVEC2: number/** Shader uniform type: uivec3 (3 unsigned int) */
var SHADER_UNIFORM_UIVEC3: number/** Shader uniform type: uivec4 (4 unsigned int) */
var SHADER_UNIFORM_UIVEC4: number/**  */
var SHADER_UNIFORM_SAMPLER2D: number/** Shader attribute type: float */
var SHADER_ATTRIB_FLOAT: number/** Shader attribute type: vec2 (2 float) */
var SHADER_ATTRIB_VEC2: number/** Shader attribute type: vec3 (3 float) */
var SHADER_ATTRIB_VEC3: number/**  */
var SHADER_ATTRIB_VEC4: number/** 8 bit per pixel (no alpha) */
var PIXELFORMAT_UNCOMPRESSED_GRAYSCALE: number/** 8*2 bpp (2 channels) */
var PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA: number/** 16 bpp */
var PIXELFORMAT_UNCOMPRESSED_R5G6B5: number/** 24 bpp */
var PIXELFORMAT_UNCOMPRESSED_R8G8B8: number/** 16 bpp (1 bit alpha) */
var PIXELFORMAT_UNCOMPRESSED_R5G5B5A1: number/** 16 bpp (4 bit alpha) */
var PIXELFORMAT_UNCOMPRESSED_R4G4B4A4: number/** 32 bpp */
var PIXELFORMAT_UNCOMPRESSED_R8G8B8A8: number/** 32 bpp (1 channel - float) */
var PIXELFORMAT_UNCOMPRESSED_R32: number/** 32*3 bpp (3 channels - float) */
var PIXELFORMAT_UNCOMPRESSED_R32G32B32: number/** 32*4 bpp (4 channels - float) */
var PIXELFORMAT_UNCOMPRESSED_R32G32B32A32: number/** 16 bpp (1 channel - half float) */
var PIXELFORMAT_UNCOMPRESSED_R16: number/** 16*3 bpp (3 channels - half float) */
var PIXELFORMAT_UNCOMPRESSED_R16G16B16: number/** 16*4 bpp (4 channels - half float) */
var PIXELFORMAT_UNCOMPRESSED_R16G16B16A16: number/** 4 bpp (no alpha) */
var PIXELFORMAT_COMPRESSED_DXT1_RGB: number/** 4 bpp (1 bit alpha) */
var PIXELFORMAT_COMPRESSED_DXT1_RGBA: number/** 8 bpp */
var PIXELFORMAT_COMPRESSED_DXT3_RGBA: number/** 8 bpp */
var PIXELFORMAT_COMPRESSED_DXT5_RGBA: number/** 4 bpp */
var PIXELFORMAT_COMPRESSED_ETC1_RGB: number/** 4 bpp */
var PIXELFORMAT_COMPRESSED_ETC2_RGB: number/** 8 bpp */
var PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA: number/** 4 bpp */
var PIXELFORMAT_COMPRESSED_PVRT_RGB: number/** 4 bpp */
var PIXELFORMAT_COMPRESSED_PVRT_RGBA: number/** 8 bpp */
var PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA: number/**  */
var PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA: number/** No filter, just pixel approximation */
var TEXTURE_FILTER_POINT: number/** Linear filtering */
var TEXTURE_FILTER_BILINEAR: number/** Trilinear filtering (linear with mipmaps) */
var TEXTURE_FILTER_TRILINEAR: number/** Anisotropic filtering 4x */
var TEXTURE_FILTER_ANISOTROPIC_4X: number/** Anisotropic filtering 8x */
var TEXTURE_FILTER_ANISOTROPIC_8X: number/** Anisotropic filtering 16x */
var TEXTURE_FILTER_ANISOTROPIC_16X: number/** Repeats texture in tiled mode */
var TEXTURE_WRAP_REPEAT: number/** Clamps texture to edge pixel in tiled mode */
var TEXTURE_WRAP_CLAMP: number/** Mirrors and repeats the texture in tiled mode */
var TEXTURE_WRAP_MIRROR_REPEAT: number/**  */
var TEXTURE_WRAP_MIRROR_CLAMP: number/** Automatically detect layout type */
var CUBEMAP_LAYOUT_AUTO_DETECT: number/** Layout is defined by a vertical line with faces */
var CUBEMAP_LAYOUT_LINE_VERTICAL: number/** Layout is defined by a horizontal line with faces */
var CUBEMAP_LAYOUT_LINE_HORIZONTAL: number/** Layout is defined by a 3x4 cross with cubemap faces */
var CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR: number/**  */
var CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE: number/** Default font generation, anti-aliased */
var FONT_DEFAULT: number/** Bitmap font generation, no anti-aliasing */
var FONT_BITMAP: number/**  */
var FONT_SDF: number/** Blend textures considering alpha (default) */
var BLEND_ALPHA: number/** Blend textures adding colors */
var BLEND_ADDITIVE: number/** Blend textures multiplying colors */
var BLEND_MULTIPLIED: number/** Blend textures adding colors (alternative) */
var BLEND_ADD_COLORS: number/** Blend textures subtracting colors (alternative) */
var BLEND_SUBTRACT_COLORS: number/** Blend premultiplied textures considering alpha */
var BLEND_ALPHA_PREMULTIPLY: number/** Blend textures using custom src/dst factors (use rlSetBlendFactors()) */
var BLEND_CUSTOM: number/**  */
var BLEND_CUSTOM_SEPARATE: number/** No gesture */
var GESTURE_NONE: number/** Tap gesture */
var GESTURE_TAP: number/** Double tap gesture */
var GESTURE_DOUBLETAP: number/** Hold gesture */
var GESTURE_HOLD: number/** Drag gesture */
var GESTURE_DRAG: number/** Swipe right gesture */
var GESTURE_SWIPE_RIGHT: number/** Swipe left gesture */
var GESTURE_SWIPE_LEFT: number/** Swipe up gesture */
var GESTURE_SWIPE_UP: number/** Swipe down gesture */
var GESTURE_SWIPE_DOWN: number/** Pinch in gesture */
var GESTURE_PINCH_IN: number/**  */
var GESTURE_PINCH_OUT: number/** Camera custom, controlled by user (UpdateCamera() does nothing) */
var CAMERA_CUSTOM: number/** Camera free mode */
var CAMERA_FREE: number/** Camera orbital, around target, zoom supported */
var CAMERA_ORBITAL: number/** Camera first person */
var CAMERA_FIRST_PERSON: number/**  */
var CAMERA_THIRD_PERSON: number/** Perspective projection */
var CAMERA_PERSPECTIVE: number/**  */
var CAMERA_ORTHOGRAPHIC: number/** Npatch layout: 3x3 tiles */
var NPATCH_NINE_PATCH: number/** Npatch layout: 1x3 tiles */
var NPATCH_THREE_PATCH_VERTICAL: number/**  */
var NPATCH_THREE_PATCH_HORIZONTAL: number/**  */
var RAYLIB_VERSION_MAJOR: number/**  */
var RAYLIB_VERSION_MINOR: number/**  */
var RAYLIB_VERSION_PATCH: number/**  */
var PI: number/**  */
var DEG2RAD: number/**  */
var RAD2DEG: number/** Light Gray */
var LIGHTGRAY: Color/** Gray */
var GRAY: Color/** Dark Gray */
var DARKGRAY: Color/** Yellow */
var YELLOW: Color/** Gold */
var GOLD: Color/** Orange */
var ORANGE: Color/** Pink */
var PINK: Color/** Red */
var RED: Color/** Maroon */
var MAROON: Color/** Green */
var GREEN: Color/** Lime */
var LIME: Color/** Dark Green */
var DARKGREEN: Color/** Sky Blue */
var SKYBLUE: Color/** Blue */
var BLUE: Color/** Dark Blue */
var DARKBLUE: Color/** Purple */
var PURPLE: Color/** Violet */
var VIOLET: Color/** Dark Purple */
var DARKPURPLE: Color/** Beige */
var BEIGE: Color/** Brown */
var BROWN: Color/** Dark Brown */
var DARKBROWN: Color/** White */
var WHITE: Color/** Black */
var BLACK: Color/** Blank (Transparent) */
var BLANK: Color/** Magenta */
var MAGENTA: Color/** My own White (raylib logo) */
var RAYWHITE: Color}
