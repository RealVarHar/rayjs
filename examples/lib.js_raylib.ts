interface Vector2 {
    x: number,
    y: number,
}
declare var Vector2: {
    prototype: Vector2;
    new(x: number, y: number): Vector2;
}
interface Vector3 {
    x: number,
    y: number,
    z: number,
}
declare var Vector3: {
    prototype: Vector3;
    new(x: number, y: number, z: number): Vector3;
}
interface Vector4 {
    x: number,
    y: number,
    z: number,
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
    r: number,
    g: number,
    b: number,
    a: number,
}
declare var Color: {
    prototype: Color;
    new(r: number, g: number, b: number, a: number): Color;
}
interface Rectangle {
    x: number,
    y: number,
    width: number,
    height: number,
}
declare var Rectangle: {
    prototype: Rectangle;
    new(x: number, y: number, width: number, height: number): Rectangle;
}
interface Image {
    data: any,
    width: number,
    height: number,
    mipmaps: number,
    format: number,
}
declare var Image: {
    prototype: Image;
    new(): Image;
}
interface Texture {
    width: number,
    height: number,
    mipmaps: number,
    format: number,
}
declare var Texture: {
    prototype: Texture;
}
interface RenderTexture {
    id: number,
    texture: Texture,
    depth: Texture,
}
declare var RenderTexture: {
    prototype: RenderTexture;
}
interface NPatchInfo {
    source: Rectangle,
    left: number,
    top: number,
    right: number,
    bottom: number,
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
    baseSize: number,
    glyphCount: number,
    glyphPadding: number,
    texture: Texture,
}
declare var Font: {
    prototype: Font;
}
interface Camera3D {
    position: Vector3,
    target: Vector3,
    up: Vector3,
    fovy: number,
    projection: number,
}
declare var Camera3D: {
    prototype: Camera3D;
    new(position: Vector3, target: Vector3, up: Vector3, fovy: number, projection: number): Camera3D;
}
interface Camera2D {
    offset: Vector2,
    target: Vector2,
    rotation: number,
    zoom: number,
}
declare var Camera2D: {
    prototype: Camera2D;
    new(offset: Vector2, target: Vector2, rotation: number, zoom: number): Camera2D;
}
interface Mesh {
    vertexCount: number,
    triangleCount: number,
    vertices: ArrayBuffer,
    texcoords: ArrayBuffer,
    texcoords2: ArrayBuffer,
    normals: ArrayBuffer,
    tangents: ArrayBuffer,
    colors: ArrayBuffer,
    indices: ArrayBuffer,
    animVertices: ArrayBuffer,
    animNormals: ArrayBuffer,
    boneIds: ArrayBuffer,
    boneWeights: ArrayBuffer,
}
declare var Mesh: {
    prototype: Mesh;
    new(): Mesh;
}
interface Shader {
    id: number,
}
declare var Shader: {
    prototype: Shader;
}
interface MaterialMap {
    texture: Texture,
    color: Color,
    value: number,
}
declare var MaterialMap: {
    prototype: MaterialMap;
}
interface Material {
    shader: Shader,
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
    transform: Matrix,
    meshCount: number,
    materialCount: number,
    meshes: Mesh,
    materials: Material,
    meshMaterial: int,
    boneCount: number,
    bones: BoneInfo,
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
    position: Vector3,
    direction: Vector3,
}
declare var Ray: {
    prototype: Ray;
    new(position: Vector3, direction: Vector3): Ray;
}
interface RayCollision {
    hit: boolean,
    distance: number,
    point: Vector3,
    normal: Vector3,
}
declare var RayCollision: {
    prototype: RayCollision;
}
interface BoundingBox {
    min: Vector3,
    max: Vector3,
}
declare var BoundingBox: {
    prototype: BoundingBox;
    new(min: Vector3, max: Vector3): BoundingBox;
}
interface Wave {
    frameCount: number,
    sampleRate: number,
    sampleSize: number,
    channels: number,
}
declare var Wave: {
    prototype: Wave;
}
interface rAudioBuffer {
}
declare var rAudioBuffer: {
    prototype: rAudioBuffer;
}
interface rAudioProcessor {
}
declare var rAudioProcessor: {
    prototype: rAudioProcessor;
}
interface AudioStream {
}
declare var AudioStream: {
    prototype: AudioStream;
}
interface Sound {
    frameCount: number,
}
declare var Sound: {
    prototype: Sound;
}
interface Music {
    frameCount: number,
    looping: boolean,
    ctxType: number,
}
declare var Music: {
    prototype: Music;
}
interface VrDeviceInfo {
    hResolution: number,
    vResolution: number,
    hScreenSize: number,
    vScreenSize: number,
    eyeToScreenDistance: number,
    lensSeparationDistance: number,
    interpupillaryDistance: number,
    lensDistortionValues: float [4],
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
/** undefined */
declare function InitWindow(width: number, height: number, title: string | undefined | null): void;
/** undefined */
declare function CloseWindow(): void;
/** undefined */
declare function WindowShouldClose(): boolean;
/** undefined */
declare function IsWindowReady(): boolean;
/** undefined */
declare function IsWindowFullscreen(): boolean;
/** undefined */
declare function IsWindowHidden(): boolean;
/** undefined */
declare function IsWindowMinimized(): boolean;
/** undefined */
declare function IsWindowMaximized(): boolean;
/** undefined */
declare function IsWindowFocused(): boolean;
/** undefined */
declare function IsWindowResized(): boolean;
/** undefined */
declare function IsWindowState(flag: number): boolean;
/** undefined */
declare function SetWindowState(flags: number): void;
/** undefined */
declare function ClearWindowState(flags: number): void;
/** undefined */
declare function ToggleFullscreen(): void;
/** undefined */
declare function ToggleBorderlessWindowed(): void;
/** undefined */
declare function MaximizeWindow(): void;
/** undefined */
declare function MinimizeWindow(): void;
/** undefined */
declare function RestoreWindow(): void;
/** undefined */
declare function SetWindowIcon(image: Image): void;
/** undefined */
declare function SetWindowTitle(title: string | undefined | null): void;
/** undefined */
declare function SetWindowPosition(x: number, y: number): void;
/** undefined */
declare function SetWindowMonitor(monitor: number): void;
/** undefined */
declare function SetWindowMinSize(width: number, height: number): void;
/** undefined */
declare function SetWindowMaxSize(width: number, height: number): void;
/** undefined */
declare function SetWindowSize(width: number, height: number): void;
/** undefined */
declare function SetWindowOpacity(opacity: number): void;
/** undefined */
declare function SetWindowFocused(): void;
/** undefined */
declare function GetScreenWidth(): number;
/** undefined */
declare function GetScreenHeight(): number;
/** undefined */
declare function GetRenderWidth(): number;
/** undefined */
declare function GetRenderHeight(): number;
/** undefined */
declare function GetMonitorCount(): number;
/** undefined */
declare function GetCurrentMonitor(): number;
/** undefined */
declare function GetMonitorPosition(monitor: number): Vector2;
/** undefined */
declare function GetMonitorWidth(monitor: number): number;
/** undefined */
declare function GetMonitorHeight(monitor: number): number;
/** undefined */
declare function GetMonitorPhysicalWidth(monitor: number): number;
/** undefined */
declare function GetMonitorPhysicalHeight(monitor: number): number;
/** undefined */
declare function GetMonitorRefreshRate(monitor: number): number;
/** undefined */
declare function GetWindowPosition(): Vector2;
/** undefined */
declare function GetWindowScaleDPI(): Vector2;
/** undefined */
declare function GetMonitorName(monitor: number): string | undefined | null;
/** undefined */
declare function SetClipboardText(text: string | undefined | null): void;
/** undefined */
declare function GetClipboardText(): string | undefined | null;
/** undefined */
declare function GetClipboardImage(): Image;
/** undefined */
declare function EnableEventWaiting(): void;
/** undefined */
declare function DisableEventWaiting(): void;
/** undefined */
declare function ShowCursor(): void;
/** undefined */
declare function HideCursor(): void;
/** undefined */
declare function IsCursorHidden(): boolean;
/** undefined */
declare function EnableCursor(): void;
/** undefined */
declare function DisableCursor(): void;
/** undefined */
declare function IsCursorOnScreen(): boolean;
/** undefined */
declare function ClearBackground(color: Color): void;
/** undefined */
declare function BeginDrawing(): void;
/** undefined */
declare function EndDrawing(): void;
/** undefined */
declare function BeginMode2D(camera: Camera2D): void;
/** undefined */
declare function EndMode2D(): void;
/** undefined */
declare function BeginMode3D(camera: Camera3D): void;
/** undefined */
declare function EndMode3D(): void;
/** undefined */
declare function BeginTextureMode(target: RenderTexture): void;
/** undefined */
declare function EndTextureMode(): void;
/** undefined */
declare function BeginShaderMode(shader: Shader): void;
/** undefined */
declare function EndShaderMode(): void;
/** undefined */
declare function BeginBlendMode(mode: number): void;
/** undefined */
declare function EndBlendMode(): void;
/** undefined */
declare function BeginScissorMode(x: number, y: number, width: number, height: number): void;
/** undefined */
declare function EndScissorMode(): void;
/** undefined */
declare function BeginVrStereoMode(config: VrStereoConfig): void;
/** undefined */
declare function EndVrStereoMode(): void;
/** undefined */
declare function LoadVrStereoConfig(device: VrDeviceInfo): VrStereoConfig;
/** undefined */
declare function UnloadVrStereoConfig(config: VrStereoConfig): void;
/** undefined */
declare function LoadShader(vsFileName: string | undefined | null, fsFileName: string | undefined | null): Shader;
/** undefined */
declare function LoadShaderFromMemory(vsCode: string | undefined | null, fsCode: string | undefined | null): Shader;
/** undefined */
declare function IsShaderValid(shader: Shader): boolean;
/** undefined */
declare function GetShaderLocation(shader: Shader, uniformName: string | undefined | null): number;
/** undefined */
declare function GetShaderLocationAttrib(shader: Shader, attribName: string | undefined | null): number;
/** undefined */
declare function SetShaderValue(shader: Shader, locIndex: number, value: void &, uniformType: number): void;
/** undefined */
declare function SetShaderValueV(shader: Shader, locIndex: number, values: any, uniformType: number, count: number): void;
/** undefined */
declare function SetShaderValueMatrix(shader: Shader, locIndex: number, mat: Matrix): void;
/** undefined */
declare function SetShaderValueTexture(shader: Shader, locIndex: number, texture: Texture): void;
/** undefined */
declare function UnloadShader(shader: Shader): void;
/** undefined */
declare function GetScreenToWorldRay(position: Vector2, camera: Camera3D): Ray;
/** undefined */
declare function GetScreenToWorldRayEx(position: Vector2, camera: Camera3D, width: number, height: number): Ray;
/** undefined */
declare function GetWorldToScreen(position: Vector3, camera: Camera3D): Vector2;
/** undefined */
declare function GetWorldToScreenEx(position: Vector3, camera: Camera3D, width: number, height: number): Vector2;
/** undefined */
declare function GetWorldToScreen2D(position: Vector2, camera: Camera2D): Vector2;
/** undefined */
declare function GetScreenToWorld2D(position: Vector2, camera: Camera2D): Vector2;
/** undefined */
declare function GetCameraMatrix(camera: Camera3D): Matrix;
/** undefined */
declare function GetCameraMatrix2D(camera: Camera2D): Matrix;
/** undefined */
declare function SetTargetFPS(fps: number): void;
/** undefined */
declare function GetFrameTime(): number;
/** undefined */
declare function GetTime(): number;
/** undefined */
declare function GetFPS(): number;
/** undefined */
declare function SetRandomSeed(seed: number): void;
/** undefined */
declare function GetRandomValue(min: number, max: number): number;
/** undefined */
declare function LoadRandomSequence(count: number, min: number, max: number): int;
/** undefined */
declare function TakeScreenshot(fileName: string | undefined | null): void;
/** undefined */
declare function SetConfigFlags(flags: number): void;
/** undefined */
declare function OpenURL(url: string | undefined | null): void;
/** undefined */
declare function TraceLog(logLevel: number): void;
/** undefined */
declare function SetTraceLogLevel(logLevel: number): void;
/** undefined */
declare function SetLoadFileDataCallback(callback: LoadFileDataCallback): void;
/** undefined */
declare function SetSaveFileDataCallback(callback: SaveFileDataCallback): void;
/** undefined */
declare function SetLoadFileTextCallback(callback: LoadFileTextCallback): void;
/** undefined */
declare function SetSaveFileTextCallback(callback: SaveFileTextCallback): void;
/** undefined */
declare function LoadFileData(fileName: string | undefined | null, dataSize: int &): ArrayBuffer;
/** undefined */
declare function SaveFileData(fileName: string | undefined | null, data: any, dataSize: number): boolean;
/** undefined */
declare function LoadFileText(fileName: string | undefined | null): string | undefined | null;
/** undefined */
declare function SaveFileText(fileName: string | undefined | null, text: string | undefined | null): boolean;
/** undefined */
declare function FileExists(fileName: string | undefined | null): boolean;
/** undefined */
declare function DirectoryExists(dirPath: string | undefined | null): boolean;
/** undefined */
declare function IsFileExtension(fileName: string | undefined | null, ext: string | undefined | null): boolean;
/** undefined */
declare function GetFileLength(fileName: string | undefined | null): number;
/** undefined */
declare function GetFileExtension(fileName: string | undefined | null): string | undefined | null;
/** undefined */
declare function GetFileName(filePath: string | undefined | null): string | undefined | null;
/** undefined */
declare function GetFileNameWithoutExt(filePath: string | undefined | null): string | undefined | null;
/** undefined */
declare function GetDirectoryPath(filePath: string | undefined | null): string | undefined | null;
/** undefined */
declare function GetPrevDirectoryPath(dirPath: string | undefined | null): string | undefined | null;
/** undefined */
declare function GetWorkingDirectory(): string | undefined | null;
/** undefined */
declare function GetApplicationDirectory(): string | undefined | null;
/** undefined */
declare function MakeDirectory(dirPath: string | undefined | null): number;
/** undefined */
declare function ChangeDirectory(dir: string | undefined | null): boolean;
/** undefined */
declare function IsPathFile(path: string | undefined | null): boolean;
/** undefined */
declare function IsFileNameValid(fileName: string | undefined | null): boolean;
/** undefined */
declare function LoadDirectoryFiles(dirPath: string | undefined | null): string[];
/** undefined */
declare function LoadDirectoryFilesEx(basePath: string | undefined | null, filter: string | undefined | null, scanSubdirs: boolean): string[];
/** undefined */
declare function IsFileDropped(): boolean;
/** undefined */
declare function LoadDroppedFiles(): string[];
/** undefined */
declare function GetFileModTime(fileName: string | undefined | null): number;
/** undefined */
declare function ComputeCRC32(data: ArrayBuffer, dataSize: number): number;
/** undefined */
declare function ComputeMD5(data: ArrayBuffer, dataSize: number): unsigned int;
/** undefined */
declare function ComputeSHA1(data: ArrayBuffer, dataSize: number): unsigned int;
/** undefined */
declare function LoadAutomationEventList(fileName: string | undefined | null): AutomationEventList;
/** undefined */
declare function UnloadAutomationEventList(list: AutomationEventList): void;
/** undefined */
declare function ExportAutomationEventList(list: AutomationEventList, fileName: string | undefined | null): boolean;
/** undefined */
declare function SetAutomationEventList(list: AutomationEventList &): void;
/** undefined */
declare function SetAutomationEventBaseFrame(frame: number): void;
/** undefined */
declare function StartAutomationEventRecording(): void;
/** undefined */
declare function StopAutomationEventRecording(): void;
/** undefined */
declare function PlayAutomationEvent(event: AutomationEvent): void;
/** undefined */
declare function IsKeyPressed(key: number): boolean;
/** undefined */
declare function IsKeyPressedRepeat(key: number): boolean;
/** undefined */
declare function IsKeyDown(key: number): boolean;
/** undefined */
declare function IsKeyReleased(key: number): boolean;
/** undefined */
declare function IsKeyUp(key: number): boolean;
/** undefined */
declare function GetKeyPressed(): number;
/** undefined */
declare function GetCharPressed(): number;
/** undefined */
declare function GetKeyName(key: number): string | undefined | null;
/** undefined */
declare function SetExitKey(key: number): void;
/** undefined */
declare function IsGamepadAvailable(gamepad: number): boolean;
/** undefined */
declare function GetGamepadName(gamepad: number): string | undefined | null;
/** undefined */
declare function IsGamepadButtonPressed(gamepad: number, button: number): boolean;
/** undefined */
declare function IsGamepadButtonDown(gamepad: number, button: number): boolean;
/** undefined */
declare function IsGamepadButtonReleased(gamepad: number, button: number): boolean;
/** undefined */
declare function IsGamepadButtonUp(gamepad: number, button: number): boolean;
/** undefined */
declare function GetGamepadButtonPressed(): number;
/** undefined */
declare function GetGamepadAxisCount(gamepad: number): number;
/** undefined */
declare function GetGamepadAxisMovement(gamepad: number, axis: number): number;
/** undefined */
declare function SetGamepadMappings(mappings: string | undefined | null): number;
/** undefined */
declare function SetGamepadVibration(gamepad: number, leftMotor: number, rightMotor: number, duration: number): void;
/** undefined */
declare function IsMouseButtonPressed(button: number): boolean;
/** undefined */
declare function IsMouseButtonDown(button: number): boolean;
/** undefined */
declare function IsMouseButtonReleased(button: number): boolean;
/** undefined */
declare function IsMouseButtonUp(button: number): boolean;
/** undefined */
declare function GetMouseX(): number;
/** undefined */
declare function GetMouseY(): number;
/** undefined */
declare function GetMousePosition(): Vector2;
/** undefined */
declare function GetMouseDelta(): Vector2;
/** undefined */
declare function SetMousePosition(x: number, y: number): void;
/** undefined */
declare function SetMouseOffset(offsetX: number, offsetY: number): void;
/** undefined */
declare function SetMouseScale(scaleX: number, scaleY: number): void;
/** undefined */
declare function GetMouseWheelMove(): number;
/** undefined */
declare function GetMouseWheelMoveV(): Vector2;
/** undefined */
declare function SetMouseCursor(cursor: number): void;
/** undefined */
declare function GetTouchX(): number;
/** undefined */
declare function GetTouchY(): number;
/** undefined */
declare function GetTouchPosition(index: number): Vector2;
/** undefined */
declare function GetTouchPointId(index: number): number;
/** undefined */
declare function GetTouchPointCount(): number;
/** undefined */
declare function SetGesturesEnabled(flags: number): void;
/** undefined */
declare function IsGestureDetected(gesture: number): boolean;
/** undefined */
declare function GetGestureDetected(): number;
/** undefined */
declare function GetGestureHoldDuration(): number;
/** undefined */
declare function GetGestureDragVector(): Vector2;
/** undefined */
declare function GetGestureDragAngle(): number;
/** undefined */
declare function GetGesturePinchVector(): Vector2;
/** undefined */
declare function GetGesturePinchAngle(): number;
/** undefined */
declare function UpdateCamera(camera: Camera &, mode: number): void;
/** undefined */
declare function UpdateCameraPro(camera: Camera &, movement: Vector3, rotation: Vector3, zoom: number): void;
/** undefined */
declare function SetShapesTexture(texture: Texture, source: Rectangle): void;
/** undefined */
declare function GetShapesTexture(): Texture;
/** undefined */
declare function GetShapesTextureRectangle(): Rectangle;
/** undefined */
declare function DrawPixel(posX: number, posY: number, color: Color): void;
/** undefined */
declare function DrawPixelV(position: Vector2, color: Color): void;
/** undefined */
declare function DrawLine(startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void;
/** undefined */
declare function DrawLineV(startPos: Vector2, endPos: Vector2, color: Color): void;
/** undefined */
declare function DrawLineEx(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void;
/** undefined */
declare function DrawLineBezier(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void;
/** undefined */
declare function DrawCircle(centerX: number, centerY: number, radius: number, color: Color): void;
/** undefined */
declare function DrawCircleSector(center: Vector2, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** undefined */
declare function DrawCircleSectorLines(center: Vector2, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** undefined */
declare function DrawCircleGradient(centerX: number, centerY: number, radius: number, inner: Color, outer: Color): void;
/** undefined */
declare function DrawCircleV(center: Vector2, radius: number, color: Color): void;
/** undefined */
declare function DrawCircleLines(centerX: number, centerY: number, radius: number, color: Color): void;
/** undefined */
declare function DrawCircleLinesV(center: Vector2, radius: number, color: Color): void;
/** undefined */
declare function DrawEllipse(centerX: number, centerY: number, radiusH: number, radiusV: number, color: Color): void;
/** undefined */
declare function DrawEllipseLines(centerX: number, centerY: number, radiusH: number, radiusV: number, color: Color): void;
/** undefined */
declare function DrawRing(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** undefined */
declare function DrawRingLines(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** undefined */
declare function DrawRectangle(posX: number, posY: number, width: number, height: number, color: Color): void;
/** undefined */
declare function DrawRectangleV(position: Vector2, size: Vector2, color: Color): void;
/** undefined */
declare function DrawRectangleRec(rec: Rectangle, color: Color): void;
/** undefined */
declare function DrawRectanglePro(rec: Rectangle, origin: Vector2, rotation: number, color: Color): void;
/** undefined */
declare function DrawRectangleGradientV(posX: number, posY: number, width: number, height: number, top: Color, bottom: Color): void;
/** undefined */
declare function DrawRectangleGradientH(posX: number, posY: number, width: number, height: number, left: Color, right: Color): void;
/** undefined */
declare function DrawRectangleGradientEx(rec: Rectangle, topLeft: Color, bottomLeft: Color, topRight: Color, bottomRight: Color): void;
/** undefined */
declare function DrawRectangleLines(posX: number, posY: number, width: number, height: number, color: Color): void;
/** undefined */
declare function DrawRectangleLinesEx(rec: Rectangle, lineThick: number, color: Color): void;
/** undefined */
declare function DrawRectangleRounded(rec: Rectangle, roundness: number, segments: number, color: Color): void;
/** undefined */
declare function DrawRectangleRoundedLines(rec: Rectangle, roundness: number, segments: number, color: Color): void;
/** undefined */
declare function DrawRectangleRoundedLinesEx(rec: Rectangle, roundness: number, segments: number, lineThick: number, color: Color): void;
/** undefined */
declare function DrawTriangle(v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** undefined */
declare function DrawTriangleLines(v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** undefined */
declare function DrawPoly(center: Vector2, sides: number, radius: number, rotation: number, color: Color): void;
/** undefined */
declare function DrawPolyLines(center: Vector2, sides: number, radius: number, rotation: number, color: Color): void;
/** undefined */
declare function DrawPolyLinesEx(center: Vector2, sides: number, radius: number, rotation: number, lineThick: number, color: Color): void;
/** undefined */
declare function DrawSplineLinear(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** undefined */
declare function DrawSplineBasis(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** undefined */
declare function DrawSplineCatmullRom(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** undefined */
declare function DrawSplineBezierQuadratic(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** undefined */
declare function DrawSplineBezierCubic(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** undefined */
declare function DrawSplineSegmentLinear(p1: Vector2, p2: Vector2, thick: number, color: Color): void;
/** undefined */
declare function DrawSplineSegmentBasis(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, thick: number, color: Color): void;
/** undefined */
declare function DrawSplineSegmentCatmullRom(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, thick: number, color: Color): void;
/** undefined */
declare function DrawSplineSegmentBezierQuadratic(p1: Vector2, c2: Vector2, p3: Vector2, thick: number, color: Color): void;
/** undefined */
declare function DrawSplineSegmentBezierCubic(p1: Vector2, c2: Vector2, c3: Vector2, p4: Vector2, thick: number, color: Color): void;
/** undefined */
declare function GetSplinePointLinear(startPos: Vector2, endPos: Vector2, t: number): Vector2;
/** undefined */
declare function GetSplinePointBasis(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, t: number): Vector2;
/** undefined */
declare function GetSplinePointCatmullRom(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, t: number): Vector2;
/** undefined */
declare function GetSplinePointBezierQuad(p1: Vector2, c2: Vector2, p3: Vector2, t: number): Vector2;
/** undefined */
declare function GetSplinePointBezierCubic(p1: Vector2, c2: Vector2, c3: Vector2, p4: Vector2, t: number): Vector2;
/** undefined */
declare function CheckCollisionRecs(rec1: Rectangle, rec2: Rectangle): boolean;
/** undefined */
declare function CheckCollisionCircles(center1: Vector2, radius1: number, center2: Vector2, radius2: number): boolean;
/** undefined */
declare function CheckCollisionCircleRec(center: Vector2, radius: number, rec: Rectangle): boolean;
/** undefined */
declare function CheckCollisionCircleLine(center: Vector2, radius: number, p1: Vector2, p2: Vector2): boolean;
/** undefined */
declare function CheckCollisionPointRec(point: Vector2, rec: Rectangle): boolean;
/** undefined */
declare function CheckCollisionPointCircle(point: Vector2, center: Vector2, radius: number): boolean;
/** undefined */
declare function CheckCollisionPointTriangle(point: Vector2, p1: Vector2, p2: Vector2, p3: Vector2): boolean;
/** undefined */
declare function CheckCollisionPointLine(point: Vector2, p1: Vector2, p2: Vector2, threshold: number): boolean;
/** undefined */
declare function GetCollisionRec(rec1: Rectangle, rec2: Rectangle): Rectangle;
/** undefined */
declare function LoadImage(fileName: string | undefined | null): Image;
/** undefined */
declare function LoadImageRaw(fileName: string | undefined | null, width: number, height: number, format: number, headerSize: number): Image;
/** undefined */
declare function LoadImageAnimFromMemory(fileType: string | undefined | null, fileData: ArrayBuffer, dataSize: number, frames: int &): Image;
/** undefined */
declare function LoadImageFromMemory(fileType: string | undefined | null, fileData: ArrayBuffer, dataSize: number): Image;
/** undefined */
declare function LoadImageFromTexture(texture: Texture): Image;
/** undefined */
declare function LoadImageFromScreen(): Image;
/** undefined */
declare function IsImageValid(image: Image): boolean;
/** undefined */
declare function UnloadImage(image: Image): void;
/** undefined */
declare function ExportImage(image: Image, fileName: string | undefined | null): boolean;
/** undefined */
declare function ExportImageToMemory(image: Image, fileType: string | undefined | null, fileSize: int &): ArrayBuffer;
/** undefined */
declare function GenImageColor(width: number, height: number, color: Color): Image;
/** undefined */
declare function GenImageGradientLinear(width: number, height: number, direction: number, start: Color, end: Color): Image;
/** undefined */
declare function GenImageGradientRadial(width: number, height: number, density: number, inner: Color, outer: Color): Image;
/** undefined */
declare function GenImageGradientSquare(width: number, height: number, density: number, inner: Color, outer: Color): Image;
/** undefined */
declare function GenImageChecked(width: number, height: number, checksX: number, checksY: number, col1: Color, col2: Color): Image;
/** undefined */
declare function GenImageWhiteNoise(width: number, height: number, factor: number): Image;
/** undefined */
declare function GenImagePerlinNoise(width: number, height: number, offsetX: number, offsetY: number, scale: number): Image;
/** undefined */
declare function GenImageCellular(width: number, height: number, tileSize: number): Image;
/** undefined */
declare function GenImageText(width: number, height: number, text: string | undefined | null): Image;
/** undefined */
declare function ImageCopy(image: Image): Image;
/** undefined */
declare function ImageFromImage(image: Image, rec: Rectangle): Image;
/** undefined */
declare function ImageFromChannel(image: Image, selectedChannel: number): Image;
/** undefined */
declare function ImageText(text: string | undefined | null, fontSize: number, color: Color): Image;
/** undefined */
declare function ImageTextEx(font: Font, text: string | undefined | null, fontSize: number, spacing: number, tint: Color): Image;
/** undefined */
declare function ImageFormat(image: Image &, newFormat: number): void;
/** undefined */
declare function ImageToPOT(image: Image &, fill: Color): void;
/** undefined */
declare function ImageCrop(image: Image &, crop: Rectangle): void;
/** undefined */
declare function ImageAlphaCrop(image: Image &, threshold: number): void;
/** undefined */
declare function ImageAlphaClear(image: Image &, color: Color, threshold: number): void;
/** undefined */
declare function ImageAlphaMask(image: Image &, alphaMask: Image): void;
/** undefined */
declare function ImageAlphaPremultiply(image: Image &): void;
/** undefined */
declare function ImageBlurGaussian(image: Image &, blurSize: number): void;
/** undefined */
declare function ImageKernelConvolution(image: Image &, kernel: float, kernelSize: number): void;
/** undefined */
declare function ImageResize(image: Image &, newWidth: number, newHeight: number): void;
/** undefined */
declare function ImageResizeNN(image: Image &, newWidth: number, newHeight: number): void;
/** undefined */
declare function ImageResizeCanvas(image: Image &, newWidth: number, newHeight: number, offsetX: number, offsetY: number, fill: Color): void;
/** undefined */
declare function ImageMipmaps(image: Image &): void;
/** undefined */
declare function ImageDither(image: Image &, rBpp: number, gBpp: number, bBpp: number, aBpp: number): void;
/** undefined */
declare function ImageFlipVertical(image: Image &): void;
/** undefined */
declare function ImageFlipHorizontal(image: Image &): void;
/** undefined */
declare function ImageRotate(image: Image &, degrees: number): void;
/** undefined */
declare function ImageRotateCW(image: Image &): void;
/** undefined */
declare function ImageRotateCCW(image: Image &): void;
/** undefined */
declare function ImageColorTint(image: Image &, color: Color): void;
/** undefined */
declare function ImageColorInvert(image: Image &): void;
/** undefined */
declare function ImageColorGrayscale(image: Image &): void;
/** undefined */
declare function ImageColorContrast(image: Image &, contrast: number): void;
/** undefined */
declare function ImageColorBrightness(image: Image &, brightness: number): void;
/** undefined */
declare function ImageColorReplace(image: Image &, color: Color, replace: Color): void;
/** undefined */
declare function LoadImageColors(image: Image): ArrayBuffer;
/** undefined */
declare function GetImageAlphaBorder(image: Image, threshold: number): Rectangle;
/** undefined */
declare function GetImageColor(image: Image, x: number, y: number): Color;
/** undefined */
declare function ImageClearBackground(dst: Image &, color: Color): void;
/** undefined */
declare function ImageDrawPixel(dst: Image &, posX: number, posY: number, color: Color): void;
/** undefined */
declare function ImageDrawPixelV(dst: Image &, position: Vector2, color: Color): void;
/** undefined */
declare function ImageDrawLine(dst: Image &, startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void;
/** undefined */
declare function ImageDrawLineV(dst: Image &, start: Vector2, end: Vector2, color: Color): void;
/** undefined */
declare function ImageDrawLineEx(dst: Image &, start: Vector2, end: Vector2, thick: number, color: Color): void;
/** undefined */
declare function ImageDrawCircle(dst: Image &, centerX: number, centerY: number, radius: number, color: Color): void;
/** undefined */
declare function ImageDrawCircleV(dst: Image &, center: Vector2, radius: number, color: Color): void;
/** undefined */
declare function ImageDrawCircleLines(dst: Image &, centerX: number, centerY: number, radius: number, color: Color): void;
/** undefined */
declare function ImageDrawCircleLinesV(dst: Image &, center: Vector2, radius: number, color: Color): void;
/** undefined */
declare function ImageDrawRectangle(dst: Image &, posX: number, posY: number, width: number, height: number, color: Color): void;
/** undefined */
declare function ImageDrawRectangleV(dst: Image &, position: Vector2, size: Vector2, color: Color): void;
/** undefined */
declare function ImageDrawRectangleRec(dst: Image &, rec: Rectangle, color: Color): void;
/** undefined */
declare function ImageDrawRectangleLines(dst: Image &, rec: Rectangle, thick: number, color: Color): void;
/** undefined */
declare function ImageDrawTriangle(dst: Image &, v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** undefined */
declare function ImageDrawTriangleEx(dst: Image &, v1: Vector2, v2: Vector2, v3: Vector2, c1: Color, c2: Color, c3: Color): void;
/** undefined */
declare function ImageDrawTriangleLines(dst: Image &, v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** undefined */
declare function ImageDrawTriangleFan(dst: Image &, points: Vector2, pointCount: number, color: Color): void;
/** undefined */
declare function ImageDrawTriangleStrip(dst: Image &, points: Vector2, pointCount: number, color: Color): void;
/** undefined */
declare function ImageDraw(dst: Image &, src: Image, srcRec: Rectangle, dstRec: Rectangle, tint: Color): void;
/** undefined */
declare function ImageDrawText(dst: Image &, text: string | undefined | null, posX: number, posY: number, fontSize: number, color: Color): void;
/** undefined */
declare function ImageDrawTextEx(dst: Image &, font: Font, text: string | undefined | null, position: Vector2, fontSize: number, spacing: number, tint: Color): void;
/** undefined */
declare function LoadTexture(fileName: string | undefined | null): Texture;
/** undefined */
declare function LoadTextureFromImage(image: Image): Texture;
/** undefined */
declare function LoadTextureCubemap(image: Image, layout: number): Texture;
/** undefined */
declare function LoadRenderTexture(width: number, height: number): RenderTexture;
/** undefined */
declare function IsTextureValid(texture: Texture): boolean;
/** undefined */
declare function UnloadTexture(texture: Texture): void;
/** undefined */
declare function IsRenderTextureValid(target: RenderTexture): boolean;
/** undefined */
declare function UnloadRenderTexture(target: RenderTexture): void;
/** undefined */
declare function UpdateTexture(texture: Texture, pixels: any): void;
/** undefined */
declare function UpdateTextureRec(texture: Texture, rec: Rectangle, pixels: any): void;
/** undefined */
declare function GenTextureMipmaps(texture: Texture2D &): void;
/** undefined */
declare function SetTextureFilter(texture: Texture, filter: number): void;
/** undefined */
declare function SetTextureWrap(texture: Texture, wrap: number): void;
/** undefined */
declare function DrawTexture(texture: Texture, posX: number, posY: number, tint: Color): void;
/** undefined */
declare function DrawTextureV(texture: Texture, position: Vector2, tint: Color): void;
/** undefined */
declare function DrawTextureEx(texture: Texture, position: Vector2, rotation: number, scale: number, tint: Color): void;
/** undefined */
declare function DrawTextureRec(texture: Texture, source: Rectangle, position: Vector2, tint: Color): void;
/** undefined */
declare function DrawTexturePro(texture: Texture, source: Rectangle, dest: Rectangle, origin: Vector2, rotation: number, tint: Color): void;
/** undefined */
declare function DrawTextureNPatch(texture: Texture, nPatchInfo: NPatchInfo, dest: Rectangle, origin: Vector2, rotation: number, tint: Color): void;
/** undefined */
declare function ColorIsEqual(col1: Color, col2: Color): boolean;
/** undefined */
declare function Fade(color: Color, alpha: number): Color;
/** undefined */
declare function ColorToInt(color: Color): number;
/** undefined */
declare function ColorNormalize(color: Color): Vector4;
/** undefined */
declare function ColorFromNormalized(normalized: Vector4): Color;
/** undefined */
declare function ColorToHSV(color: Color): Vector3;
/** undefined */
declare function ColorFromHSV(hue: number, saturation: number, value: number): Color;
/** undefined */
declare function ColorTint(color: Color, tint: Color): Color;
/** undefined */
declare function ColorBrightness(color: Color, factor: number): Color;
/** undefined */
declare function ColorContrast(color: Color, contrast: number): Color;
/** undefined */
declare function ColorAlpha(color: Color, alpha: number): Color;
/** undefined */
declare function ColorAlphaBlend(dst: Color, src: Color, tint: Color): Color;
/** undefined */
declare function ColorLerp(color1: Color, color2: Color, factor: number): Color;
/** undefined */
declare function GetColor(hexValue: number): Color;
/** undefined */
declare function GetPixelDataSize(width: number, height: number, format: number): number;
/** undefined */
declare function GetFontDefault(): Font;
/** undefined */
declare function LoadFont(fileName: string | undefined | null): Font;
/** undefined */
declare function LoadFontEx(fileName: string | undefined | null, fontSize: number, codepoints: int, codepointCount: number): Font;
/** undefined */
declare function LoadFontFromImage(image: Image, key: Color, firstChar: number): Font;
/** undefined */
declare function IsFontValid(font: Font): boolean;
/** undefined */
declare function UnloadFont(font: Font): void;
/** undefined */
declare function DrawFPS(posX: number, posY: number): void;
/** undefined */
declare function DrawText(text: string | undefined | null, posX: number, posY: number, fontSize: number, color: Color): void;
/** undefined */
declare function DrawTextEx(font: Font, text: string | undefined | null, position: Vector2, fontSize: number, spacing: number, tint: Color): void;
/** undefined */
declare function DrawTextPro(font: Font, text: string | undefined | null, position: Vector2, origin: Vector2, rotation: number, fontSize: number, spacing: number, tint: Color): void;
/** undefined */
declare function DrawTextCodepoint(font: Font, codepoint: number, position: Vector2, fontSize: number, tint: Color): void;
/** undefined */
declare function SetTextLineSpacing(spacing: number): void;
/** undefined */
declare function MeasureText(text: string | undefined | null, fontSize: number): number;
/** undefined */
declare function MeasureTextEx(font: Font, text: string | undefined | null, fontSize: number, spacing: number): Vector2;
/** undefined */
declare function GetGlyphIndex(font: Font, codepoint: number): number;
/** undefined */
declare function GetGlyphAtlasRec(font: Font, codepoint: number): Rectangle;
/** undefined */
declare function TextCopy(dst: char &, src: string | undefined | null): number;
/** undefined */
declare function TextIsEqual(text1: string | undefined | null, text2: string | undefined | null): boolean;
/** undefined */
declare function TextLength(text: string | undefined | null): number;
/** undefined */
declare function TextFormat(text: string | undefined | null, args: ...): string | undefined | null;
/** undefined */
declare function TextSubtext(text: string | undefined | null, position: number, length: number): string | undefined | null;
/** undefined */
declare function TextReplace(text: string | undefined | null, replace: string | undefined | null, by: string | undefined | null): string | undefined | null;
/** undefined */
declare function TextInsert(text: string | undefined | null, insert: string | undefined | null, position: number): string | undefined | null;
/** undefined */
declare function TextJoin(textList: char *, count: number, delimiter: string | undefined | null): string | undefined | null;
/** undefined */
declare function TextSplit(text: string | undefined | null, delimiter: char, count: int &): char *;
/** undefined */
declare function TextAppend(text: string | undefined | null, append: string | undefined | null, position: int &): void;
/** undefined */
declare function TextFindIndex(text: string | undefined | null, find: string | undefined | null): number;
/** undefined */
declare function TextToUpper(text: string | undefined | null): string | undefined | null;
/** undefined */
declare function TextToLower(text: string | undefined | null): string | undefined | null;
/** undefined */
declare function TextToPascal(text: string | undefined | null): string | undefined | null;
/** undefined */
declare function TextToSnake(text: string | undefined | null): string | undefined | null;
/** undefined */
declare function TextToCamel(text: string | undefined | null): string | undefined | null;
/** undefined */
declare function TextToInteger(text: string | undefined | null): number;
/** undefined */
declare function TextToFloat(text: string | undefined | null): number;
/** undefined */
declare function DrawLine3D(startPos: Vector3, endPos: Vector3, color: Color): void;
/** undefined */
declare function DrawPoint3D(position: Vector3, color: Color): void;
/** undefined */
declare function DrawCircle3D(center: Vector3, radius: number, rotationAxis: Vector3, rotationAngle: number, color: Color): void;
/** undefined */
declare function DrawTriangle3D(v1: Vector3, v2: Vector3, v3: Vector3, color: Color): void;
/** undefined */
declare function DrawCube(position: Vector3, width: number, height: number, length: number, color: Color): void;
/** undefined */
declare function DrawCubeV(position: Vector3, size: Vector3, color: Color): void;
/** undefined */
declare function DrawCubeWires(position: Vector3, width: number, height: number, length: number, color: Color): void;
/** undefined */
declare function DrawCubeWiresV(position: Vector3, size: Vector3, color: Color): void;
/** undefined */
declare function DrawSphere(centerPos: Vector3, radius: number, color: Color): void;
/** undefined */
declare function DrawSphereEx(centerPos: Vector3, radius: number, rings: number, slices: number, color: Color): void;
/** undefined */
declare function DrawSphereWires(centerPos: Vector3, radius: number, rings: number, slices: number, color: Color): void;
/** undefined */
declare function DrawCylinder(position: Vector3, radiusTop: number, radiusBottom: number, height: number, slices: number, color: Color): void;
/** undefined */
declare function DrawCylinderEx(startPos: Vector3, endPos: Vector3, startRadius: number, endRadius: number, sides: number, color: Color): void;
/** undefined */
declare function DrawCylinderWires(position: Vector3, radiusTop: number, radiusBottom: number, height: number, slices: number, color: Color): void;
/** undefined */
declare function DrawCylinderWiresEx(startPos: Vector3, endPos: Vector3, startRadius: number, endRadius: number, sides: number, color: Color): void;
/** undefined */
declare function DrawCapsule(startPos: Vector3, endPos: Vector3, radius: number, slices: number, rings: number, color: Color): void;
/** undefined */
declare function DrawCapsuleWires(startPos: Vector3, endPos: Vector3, radius: number, slices: number, rings: number, color: Color): void;
/** undefined */
declare function DrawPlane(centerPos: Vector3, size: Vector2, color: Color): void;
/** undefined */
declare function DrawRay(ray: Ray, color: Color): void;
/** undefined */
declare function DrawGrid(slices: number, spacing: number): void;
/** undefined */
declare function LoadModel(fileName: string | undefined | null): Model;
/** undefined */
declare function LoadModelFromMesh(mesh: Mesh): Model;
/** undefined */
declare function IsModelValid(model: Model): boolean;
/** undefined */
declare function UnloadModel(model: Model): void;
/** undefined */
declare function GetModelBoundingBox(model: Model): BoundingBox;
/** undefined */
declare function DrawModel(model: Model, position: Vector3, scale: number, tint: Color): void;
/** undefined */
declare function DrawModelEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
/** undefined */
declare function DrawModelWires(model: Model, position: Vector3, scale: number, tint: Color): void;
/** undefined */
declare function DrawModelWiresEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
/** undefined */
declare function DrawModelPoints(model: Model, position: Vector3, scale: number, tint: Color): void;
/** undefined */
declare function DrawModelPointsEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
/** undefined */
declare function DrawBoundingBox(box: BoundingBox, color: Color): void;
/** undefined */
declare function DrawBillboard(camera: Camera3D, texture: Texture, position: Vector3, scale: number, tint: Color): void;
/** undefined */
declare function DrawBillboardRec(camera: Camera3D, texture: Texture, source: Rectangle, position: Vector3, size: Vector2, tint: Color): void;
/** undefined */
declare function DrawBillboardPro(camera: Camera3D, texture: Texture, source: Rectangle, position: Vector3, up: Vector3, size: Vector2, origin: Vector2, rotation: number, tint: Color): void;
/** undefined */
declare function UploadMesh(mesh: Mesh &, dynamic: boolean): void;
/** undefined */
declare function UpdateMeshBuffer(mesh: Mesh, index: number, data: any, dataSize: number, offset: number): void;
/** undefined */
declare function UnloadMesh(mesh: Mesh): void;
/** undefined */
declare function DrawMesh(mesh: Mesh, material: Material, transform: Matrix): void;
/** undefined */
declare function DrawMeshInstanced(mesh: Mesh, material: Material, transforms: Matrix, instances: number): void;
/** undefined */
declare function GetMeshBoundingBox(mesh: Mesh): BoundingBox;
/** undefined */
declare function GenMeshTangents(mesh: Mesh &): void;
/** undefined */
declare function ExportMesh(mesh: Mesh, fileName: string | undefined | null): boolean;
/** undefined */
declare function ExportMeshAsCode(mesh: Mesh, fileName: string | undefined | null): boolean;
/** undefined */
declare function GenMeshPoly(sides: number, radius: number): Mesh;
/** undefined */
declare function GenMeshPlane(width: number, length: number, resX: number, resZ: number): Mesh;
/** undefined */
declare function GenMeshCube(width: number, height: number, length: number): Mesh;
/** undefined */
declare function GenMeshSphere(radius: number, rings: number, slices: number): Mesh;
/** undefined */
declare function GenMeshHemiSphere(radius: number, rings: number, slices: number): Mesh;
/** undefined */
declare function GenMeshCylinder(radius: number, height: number, slices: number): Mesh;
/** undefined */
declare function GenMeshCone(radius: number, height: number, slices: number): Mesh;
/** undefined */
declare function GenMeshTorus(radius: number, size: number, radSeg: number, sides: number): Mesh;
/** undefined */
declare function GenMeshKnot(radius: number, size: number, radSeg: number, sides: number): Mesh;
/** undefined */
declare function GenMeshHeightmap(heightmap: Image, size: Vector3): Mesh;
/** undefined */
declare function GenMeshCubicmap(cubicmap: Image, cubeSize: Vector3): Mesh;
/** undefined */
declare function LoadMaterialDefault(): Material;
/** undefined */
declare function IsMaterialValid(material: Material): boolean;
/** undefined */
declare function UnloadMaterial(material: Material): void;
/** undefined */
declare function SetMaterialTexture(material: Material &, mapType: number, texture: Texture): void;
/** undefined */
declare function SetModelMeshMaterial(model: Model &, meshId: number, materialId: number): void;
/** undefined */
declare function UpdateModelAnimationBones(model: Model, anim: ModelAnimation, frame: number): void;
/** undefined */
declare function CheckCollisionSpheres(center1: Vector3, radius1: number, center2: Vector3, radius2: number): boolean;
/** undefined */
declare function CheckCollisionBoxes(box1: BoundingBox, box2: BoundingBox): boolean;
/** undefined */
declare function CheckCollisionBoxSphere(box: BoundingBox, center: Vector3, radius: number): boolean;
/** undefined */
declare function GetRayCollisionSphere(ray: Ray, center: Vector3, radius: number): RayCollision;
/** undefined */
declare function GetRayCollisionBox(ray: Ray, box: BoundingBox): RayCollision;
/** undefined */
declare function GetRayCollisionMesh(ray: Ray, mesh: Mesh, transform: Matrix): RayCollision;
/** undefined */
declare function GetRayCollisionTriangle(ray: Ray, p1: Vector3, p2: Vector3, p3: Vector3): RayCollision;
/** undefined */
declare function GetRayCollisionQuad(ray: Ray, p1: Vector3, p2: Vector3, p3: Vector3, p4: Vector3): RayCollision;
/** undefined */
declare function InitAudioDevice(): void;
/** undefined */
declare function CloseAudioDevice(): void;
/** undefined */
declare function IsAudioDeviceReady(): boolean;
/** undefined */
declare function SetMasterVolume(volume: number): void;
/** undefined */
declare function GetMasterVolume(): number;
/** undefined */
declare function LoadWave(fileName: string | undefined | null): Wave;
/** undefined */
declare function LoadWaveFromMemory(fileType: string | undefined | null, fileData: ArrayBuffer, dataSize: number): Wave;
/** undefined */
declare function IsWaveValid(wave: Wave): boolean;
/** undefined */
declare function LoadSound(fileName: string | undefined | null): Sound;
/** undefined */
declare function LoadSoundFromWave(wave: Wave): Sound;
/** undefined */
declare function LoadSoundAlias(source: Sound): Sound;
/** undefined */
declare function IsSoundValid(sound: Sound): boolean;
/** undefined */
declare function UpdateSound(sound: Sound, data: any, sampleCount: number): void;
/** undefined */
declare function UnloadWave(wave: Wave): void;
/** undefined */
declare function UnloadSound(sound: Sound): void;
/** undefined */
declare function UnloadSoundAlias(alias: Sound): void;
/** undefined */
declare function ExportWave(wave: Wave, fileName: string | undefined | null): boolean;
/** undefined */
declare function PlaySound(sound: Sound): void;
/** undefined */
declare function StopSound(sound: Sound): void;
/** undefined */
declare function PauseSound(sound: Sound): void;
/** undefined */
declare function ResumeSound(sound: Sound): void;
/** undefined */
declare function IsSoundPlaying(sound: Sound): boolean;
/** undefined */
declare function SetSoundVolume(sound: Sound, volume: number): void;
/** undefined */
declare function SetSoundPitch(sound: Sound, pitch: number): void;
/** undefined */
declare function SetSoundPan(sound: Sound, pan: number): void;
/** undefined */
declare function WaveCopy(wave: Wave): Wave;
/** undefined */
declare function WaveCrop(wave: Wave &, initFrame: number, finalFrame: number): void;
/** undefined */
declare function WaveFormat(wave: Wave &, sampleRate: number, sampleSize: number, channels: number): void;
/** undefined */
declare function LoadWaveSamples(wave: Wave): ArrayBuffer;
/** undefined */
declare function UnloadWaveSamples(samples: float &): void;
/** undefined */
declare function LoadMusicStream(fileName: string | undefined | null): Music;
/** undefined */
declare function LoadMusicStreamFromMemory(fileType: string | undefined | null, data: ArrayBuffer, dataSize: number): Music;
/** undefined */
declare function IsMusicValid(music: Music): boolean;
/** undefined */
declare function UnloadMusicStream(music: Music): void;
/** undefined */
declare function PlayMusicStream(music: Music): void;
/** undefined */
declare function IsMusicStreamPlaying(music: Music): boolean;
/** undefined */
declare function UpdateMusicStream(music: Music): void;
/** undefined */
declare function StopMusicStream(music: Music): void;
/** undefined */
declare function PauseMusicStream(music: Music): void;
/** undefined */
declare function ResumeMusicStream(music: Music): void;
/** undefined */
declare function SeekMusicStream(music: Music, position: number): void;
/** undefined */
declare function SetMusicVolume(music: Music, volume: number): void;
/** undefined */
declare function SetMusicPitch(music: Music, pitch: number): void;
/** undefined */
declare function SetMusicPan(music: Music, pan: number): void;
/** undefined */
declare function GetMusicTimeLength(music: Music): number;
/** undefined */
declare function GetMusicTimePlayed(music: Music): number;
/** undefined */
declare function LoadAudioStream(sampleRate: number, sampleSize: number, channels: number): AudioStream;
/** undefined */
declare function IsAudioStreamValid(stream: AudioStream): boolean;
/** undefined */
declare function UnloadAudioStream(stream: AudioStream): void;
/** undefined */
declare function UpdateAudioStream(stream: AudioStream, data: any, frameCount: number): void;
/** undefined */
declare function IsAudioStreamProcessed(stream: AudioStream): boolean;
/** undefined */
declare function PlayAudioStream(stream: AudioStream): void;
/** undefined */
declare function PauseAudioStream(stream: AudioStream): void;
/** undefined */
declare function ResumeAudioStream(stream: AudioStream): void;
/** undefined */
declare function IsAudioStreamPlaying(stream: AudioStream): boolean;
/** undefined */
declare function StopAudioStream(stream: AudioStream): void;
/** undefined */
declare function SetAudioStreamVolume(stream: AudioStream, volume: number): void;
/** undefined */
declare function SetAudioStreamPitch(stream: AudioStream, pitch: number): void;
/** undefined */
declare function SetAudioStreamPan(stream: AudioStream, pan: number): void;
/** undefined */
declare function SetAudioStreamBufferSizeDefault(size: number): void;
/** undefined */
declare function AttachAudioMixedProcessor(processor: AudioMixedProcessor): void;
/** undefined */
declare function DetachAudioMixedProcessor(processor: AudioCallback): void;
/**  */
declare var false: number;
/**  */
declare var true: number;
/**  */
declare var FLAG_VSYNC_HINT: number;
/**  */
declare var FLAG_FULLSCREEN_MODE: number;
/**  */
declare var FLAG_WINDOW_RESIZABLE: number;
/**  */
declare var FLAG_WINDOW_UNDECORATED: number;
/**  */
declare var FLAG_WINDOW_HIDDEN: number;
/**  */
declare var FLAG_WINDOW_MINIMIZED: number;
/**  */
declare var FLAG_WINDOW_MAXIMIZED: number;
/**  */
declare var FLAG_WINDOW_UNFOCUSED: number;
/**  */
declare var FLAG_WINDOW_TOPMOST: number;
/**  */
declare var FLAG_WINDOW_ALWAYS_RUN: number;
/**  */
declare var FLAG_WINDOW_TRANSPARENT: number;
/**  */
declare var FLAG_WINDOW_HIGHDPI: number;
/**  */
declare var FLAG_WINDOW_MOUSE_PASSTHROUGH: number;
/**  */
declare var FLAG_BORDERLESS_WINDOWED_MODE: number;
/**  */
declare var FLAG_MSAA_4X_HINT: number;
/**  */
declare var FLAG_INTERLACED_HINT: number;
/**  */
declare var LOG_ALL: number;
/**  */
declare var LOG_TRACE: number;
/**  */
declare var LOG_DEBUG: number;
/**  */
declare var LOG_INFO: number;
/**  */
declare var LOG_WARNING: number;
/**  */
declare var LOG_ERROR: number;
/**  */
declare var LOG_FATAL: number;
/**  */
declare var LOG_NONE: number;
/**  */
declare var KEY_NULL: number;
/**  */
declare var KEY_APOSTROPHE: number;
/**  */
declare var KEY_COMMA: number;
/**  */
declare var KEY_MINUS: number;
/**  */
declare var KEY_PERIOD: number;
/**  */
declare var KEY_SLASH: number;
/**  */
declare var KEY_ZERO: number;
/**  */
declare var KEY_ONE: number;
/**  */
declare var KEY_TWO: number;
/**  */
declare var KEY_THREE: number;
/**  */
declare var KEY_FOUR: number;
/**  */
declare var KEY_FIVE: number;
/**  */
declare var KEY_SIX: number;
/**  */
declare var KEY_SEVEN: number;
/**  */
declare var KEY_EIGHT: number;
/**  */
declare var KEY_NINE: number;
/**  */
declare var KEY_SEMICOLON: number;
/**  */
declare var KEY_EQUAL: number;
/**  */
declare var KEY_A: number;
/**  */
declare var KEY_B: number;
/**  */
declare var KEY_C: number;
/**  */
declare var KEY_D: number;
/**  */
declare var KEY_E: number;
/**  */
declare var KEY_F: number;
/**  */
declare var KEY_G: number;
/**  */
declare var KEY_H: number;
/**  */
declare var KEY_I: number;
/**  */
declare var KEY_J: number;
/**  */
declare var KEY_K: number;
/**  */
declare var KEY_L: number;
/**  */
declare var KEY_M: number;
/**  */
declare var KEY_N: number;
/**  */
declare var KEY_O: number;
/**  */
declare var KEY_P: number;
/**  */
declare var KEY_Q: number;
/**  */
declare var KEY_R: number;
/**  */
declare var KEY_S: number;
/**  */
declare var KEY_T: number;
/**  */
declare var KEY_U: number;
/**  */
declare var KEY_V: number;
/**  */
declare var KEY_W: number;
/**  */
declare var KEY_X: number;
/**  */
declare var KEY_Y: number;
/**  */
declare var KEY_Z: number;
/**  */
declare var KEY_LEFT_BRACKET: number;
/**  */
declare var KEY_BACKSLASH: number;
/**  */
declare var KEY_RIGHT_BRACKET: number;
/**  */
declare var KEY_GRAVE: number;
/**  */
declare var KEY_SPACE: number;
/**  */
declare var KEY_ESCAPE: number;
/**  */
declare var KEY_ENTER: number;
/**  */
declare var KEY_TAB: number;
/**  */
declare var KEY_BACKSPACE: number;
/**  */
declare var KEY_INSERT: number;
/**  */
declare var KEY_DELETE: number;
/**  */
declare var KEY_RIGHT: number;
/**  */
declare var KEY_LEFT: number;
/**  */
declare var KEY_DOWN: number;
/**  */
declare var KEY_UP: number;
/**  */
declare var KEY_PAGE_UP: number;
/**  */
declare var KEY_PAGE_DOWN: number;
/**  */
declare var KEY_HOME: number;
/**  */
declare var KEY_END: number;
/**  */
declare var KEY_CAPS_LOCK: number;
/**  */
declare var KEY_SCROLL_LOCK: number;
/**  */
declare var KEY_NUM_LOCK: number;
/**  */
declare var KEY_PRINT_SCREEN: number;
/**  */
declare var KEY_PAUSE: number;
/**  */
declare var KEY_F1: number;
/**  */
declare var KEY_F2: number;
/**  */
declare var KEY_F3: number;
/**  */
declare var KEY_F4: number;
/**  */
declare var KEY_F5: number;
/**  */
declare var KEY_F6: number;
/**  */
declare var KEY_F7: number;
/**  */
declare var KEY_F8: number;
/**  */
declare var KEY_F9: number;
/**  */
declare var KEY_F10: number;
/**  */
declare var KEY_F11: number;
/**  */
declare var KEY_F12: number;
/**  */
declare var KEY_LEFT_SHIFT: number;
/**  */
declare var KEY_LEFT_CONTROL: number;
/**  */
declare var KEY_LEFT_ALT: number;
/**  */
declare var KEY_LEFT_SUPER: number;
/**  */
declare var KEY_RIGHT_SHIFT: number;
/**  */
declare var KEY_RIGHT_CONTROL: number;
/**  */
declare var KEY_RIGHT_ALT: number;
/**  */
declare var KEY_RIGHT_SUPER: number;
/**  */
declare var KEY_KB_MENU: number;
/**  */
declare var KEY_KP_0: number;
/**  */
declare var KEY_KP_1: number;
/**  */
declare var KEY_KP_2: number;
/**  */
declare var KEY_KP_3: number;
/**  */
declare var KEY_KP_4: number;
/**  */
declare var KEY_KP_5: number;
/**  */
declare var KEY_KP_6: number;
/**  */
declare var KEY_KP_7: number;
/**  */
declare var KEY_KP_8: number;
/**  */
declare var KEY_KP_9: number;
/**  */
declare var KEY_KP_DECIMAL: number;
/**  */
declare var KEY_KP_DIVIDE: number;
/**  */
declare var KEY_KP_MULTIPLY: number;
/**  */
declare var KEY_KP_SUBTRACT: number;
/**  */
declare var KEY_KP_ADD: number;
/**  */
declare var KEY_KP_ENTER: number;
/**  */
declare var KEY_KP_EQUAL: number;
/**  */
declare var KEY_BACK: number;
/**  */
declare var KEY_MENU: number;
/**  */
declare var KEY_VOLUME_UP: number;
/**  */
declare var KEY_VOLUME_DOWN: number;
/**  */
declare var MOUSE_BUTTON_LEFT: number;
/**  */
declare var MOUSE_BUTTON_RIGHT: number;
/**  */
declare var MOUSE_BUTTON_MIDDLE: number;
/**  */
declare var MOUSE_BUTTON_SIDE: number;
/**  */
declare var MOUSE_BUTTON_EXTRA: number;
/**  */
declare var MOUSE_BUTTON_FORWARD: number;
/**  */
declare var MOUSE_BUTTON_BACK: number;
/**  */
declare var MOUSE_CURSOR_DEFAULT: number;
/**  */
declare var MOUSE_CURSOR_ARROW: number;
/**  */
declare var MOUSE_CURSOR_IBEAM: number;
/**  */
declare var MOUSE_CURSOR_CROSSHAIR: number;
/**  */
declare var MOUSE_CURSOR_POINTING_HAND: number;
/**  */
declare var MOUSE_CURSOR_RESIZE_EW: number;
/**  */
declare var MOUSE_CURSOR_RESIZE_NS: number;
/**  */
declare var MOUSE_CURSOR_RESIZE_NWSE: number;
/**  */
declare var MOUSE_CURSOR_RESIZE_NESW: number;
/**  */
declare var MOUSE_CURSOR_RESIZE_ALL: number;
/**  */
declare var MOUSE_CURSOR_NOT_ALLOWED: number;
/**  */
declare var GAMEPAD_BUTTON_UNKNOWN: number;
/**  */
declare var GAMEPAD_BUTTON_LEFT_FACE_UP: number;
/**  */
declare var GAMEPAD_BUTTON_LEFT_FACE_RIGHT: number;
/**  */
declare var GAMEPAD_BUTTON_LEFT_FACE_DOWN: number;
/**  */
declare var GAMEPAD_BUTTON_LEFT_FACE_LEFT: number;
/**  */
declare var GAMEPAD_BUTTON_RIGHT_FACE_UP: number;
/**  */
declare var GAMEPAD_BUTTON_RIGHT_FACE_RIGHT: number;
/**  */
declare var GAMEPAD_BUTTON_RIGHT_FACE_DOWN: number;
/**  */
declare var GAMEPAD_BUTTON_RIGHT_FACE_LEFT: number;
/**  */
declare var GAMEPAD_BUTTON_LEFT_TRIGGER_1: number;
/**  */
declare var GAMEPAD_BUTTON_LEFT_TRIGGER_2: number;
/**  */
declare var GAMEPAD_BUTTON_RIGHT_TRIGGER_1: number;
/**  */
declare var GAMEPAD_BUTTON_RIGHT_TRIGGER_2: number;
/**  */
declare var GAMEPAD_BUTTON_MIDDLE_LEFT: number;
/**  */
declare var GAMEPAD_BUTTON_MIDDLE: number;
/**  */
declare var GAMEPAD_BUTTON_MIDDLE_RIGHT: number;
/**  */
declare var GAMEPAD_BUTTON_LEFT_THUMB: number;
/**  */
declare var GAMEPAD_BUTTON_RIGHT_THUMB: number;
/**  */
declare var GAMEPAD_AXIS_LEFT_X: number;
/**  */
declare var GAMEPAD_AXIS_LEFT_Y: number;
/**  */
declare var GAMEPAD_AXIS_RIGHT_X: number;
/**  */
declare var GAMEPAD_AXIS_RIGHT_Y: number;
/**  */
declare var GAMEPAD_AXIS_LEFT_TRIGGER: number;
/**  */
declare var GAMEPAD_AXIS_RIGHT_TRIGGER: number;
/**  */
declare var MATERIAL_MAP_ALBEDO: number;
/**  */
declare var MATERIAL_MAP_METALNESS: number;
/**  */
declare var MATERIAL_MAP_NORMAL: number;
/**  */
declare var MATERIAL_MAP_ROUGHNESS: number;
/**  */
declare var MATERIAL_MAP_OCCLUSION: number;
/**  */
declare var MATERIAL_MAP_EMISSION: number;
/**  */
declare var MATERIAL_MAP_HEIGHT: number;
/**  */
declare var MATERIAL_MAP_CUBEMAP: number;
/**  */
declare var MATERIAL_MAP_IRRADIANCE: number;
/**  */
declare var MATERIAL_MAP_PREFILTER: number;
/**  */
declare var MATERIAL_MAP_BRDF: number;
/**  */
declare var SHADER_LOC_VERTEX_POSITION: number;
/**  */
declare var SHADER_LOC_VERTEX_TEXCOORD01: number;
/**  */
declare var SHADER_LOC_VERTEX_TEXCOORD02: number;
/**  */
declare var SHADER_LOC_VERTEX_NORMAL: number;
/**  */
declare var SHADER_LOC_VERTEX_TANGENT: number;
/**  */
declare var SHADER_LOC_VERTEX_COLOR: number;
/**  */
declare var SHADER_LOC_MATRIX_MVP: number;
/**  */
declare var SHADER_LOC_MATRIX_VIEW: number;
/**  */
declare var SHADER_LOC_MATRIX_PROJECTION: number;
/**  */
declare var SHADER_LOC_MATRIX_MODEL: number;
/**  */
declare var SHADER_LOC_MATRIX_NORMAL: number;
/**  */
declare var SHADER_LOC_VECTOR_VIEW: number;
/**  */
declare var SHADER_LOC_COLOR_DIFFUSE: number;
/**  */
declare var SHADER_LOC_COLOR_SPECULAR: number;
/**  */
declare var SHADER_LOC_COLOR_AMBIENT: number;
/**  */
declare var SHADER_LOC_MAP_ALBEDO: number;
/**  */
declare var SHADER_LOC_MAP_METALNESS: number;
/**  */
declare var SHADER_LOC_MAP_NORMAL: number;
/**  */
declare var SHADER_LOC_MAP_ROUGHNESS: number;
/**  */
declare var SHADER_LOC_MAP_OCCLUSION: number;
/**  */
declare var SHADER_LOC_MAP_EMISSION: number;
/**  */
declare var SHADER_LOC_MAP_HEIGHT: number;
/**  */
declare var SHADER_LOC_MAP_CUBEMAP: number;
/**  */
declare var SHADER_LOC_MAP_IRRADIANCE: number;
/**  */
declare var SHADER_LOC_MAP_PREFILTER: number;
/**  */
declare var SHADER_LOC_MAP_BRDF: number;
/**  */
declare var SHADER_LOC_VERTEX_BONEIDS: number;
/**  */
declare var SHADER_LOC_VERTEX_BONEWEIGHTS: number;
/**  */
declare var SHADER_LOC_BONE_MATRICES: number;
/**  */
declare var SHADER_LOC_VERTEX_INSTANCE_TX: number;
/**  */
declare var SHADER_UNIFORM_FLOAT: number;
/**  */
declare var SHADER_UNIFORM_VEC2: number;
/**  */
declare var SHADER_UNIFORM_VEC3: number;
/**  */
declare var SHADER_UNIFORM_VEC4: number;
/**  */
declare var SHADER_UNIFORM_INT: number;
/**  */
declare var SHADER_UNIFORM_IVEC2: number;
/**  */
declare var SHADER_UNIFORM_IVEC3: number;
/**  */
declare var SHADER_UNIFORM_IVEC4: number;
/**  */
declare var SHADER_UNIFORM_UINT: number;
/**  */
declare var SHADER_UNIFORM_UIVEC2: number;
/**  */
declare var SHADER_UNIFORM_UIVEC3: number;
/**  */
declare var SHADER_UNIFORM_UIVEC4: number;
/**  */
declare var SHADER_UNIFORM_SAMPLER2D: number;
/**  */
declare var SHADER_ATTRIB_FLOAT: number;
/**  */
declare var SHADER_ATTRIB_VEC2: number;
/**  */
declare var SHADER_ATTRIB_VEC3: number;
/**  */
declare var SHADER_ATTRIB_VEC4: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_GRAYSCALE: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_R5G6B5: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_R8G8B8: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_R5G5B5A1: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_R4G4B4A4: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_R8G8B8A8: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_R32: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_R32G32B32: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_R32G32B32A32: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_R16: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_R16G16B16: number;
/**  */
declare var PIXELFORMAT_UNCOMPRESSED_R16G16B16A16: number;
/**  */
declare var PIXELFORMAT_COMPRESSED_DXT1_RGB: number;
/**  */
declare var PIXELFORMAT_COMPRESSED_DXT1_RGBA: number;
/**  */
declare var PIXELFORMAT_COMPRESSED_DXT3_RGBA: number;
/**  */
declare var PIXELFORMAT_COMPRESSED_DXT5_RGBA: number;
/**  */
declare var PIXELFORMAT_COMPRESSED_ETC1_RGB: number;
/**  */
declare var PIXELFORMAT_COMPRESSED_ETC2_RGB: number;
/**  */
declare var PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA: number;
/**  */
declare var PIXELFORMAT_COMPRESSED_PVRT_RGB: number;
/**  */
declare var PIXELFORMAT_COMPRESSED_PVRT_RGBA: number;
/**  */
declare var PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA: number;
/**  */
declare var PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA: number;
/**  */
declare var TEXTURE_FILTER_POINT: number;
/**  */
declare var TEXTURE_FILTER_BILINEAR: number;
/**  */
declare var TEXTURE_FILTER_TRILINEAR: number;
/**  */
declare var TEXTURE_FILTER_ANISOTROPIC_4X: number;
/**  */
declare var TEXTURE_FILTER_ANISOTROPIC_8X: number;
/**  */
declare var TEXTURE_FILTER_ANISOTROPIC_16X: number;
/**  */
declare var TEXTURE_WRAP_REPEAT: number;
/**  */
declare var TEXTURE_WRAP_CLAMP: number;
/**  */
declare var TEXTURE_WRAP_MIRROR_REPEAT: number;
/**  */
declare var TEXTURE_WRAP_MIRROR_CLAMP: number;
/**  */
declare var CUBEMAP_LAYOUT_AUTO_DETECT: number;
/**  */
declare var CUBEMAP_LAYOUT_LINE_VERTICAL: number;
/**  */
declare var CUBEMAP_LAYOUT_LINE_HORIZONTAL: number;
/**  */
declare var CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR: number;
/**  */
declare var CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE: number;
/**  */
declare var FONT_DEFAULT: number;
/**  */
declare var FONT_BITMAP: number;
/**  */
declare var FONT_SDF: number;
/**  */
declare var BLEND_ALPHA: number;
/**  */
declare var BLEND_ADDITIVE: number;
/**  */
declare var BLEND_MULTIPLIED: number;
/**  */
declare var BLEND_ADD_COLORS: number;
/**  */
declare var BLEND_SUBTRACT_COLORS: number;
/**  */
declare var BLEND_ALPHA_PREMULTIPLY: number;
/**  */
declare var BLEND_CUSTOM: number;
/**  */
declare var BLEND_CUSTOM_SEPARATE: number;
/**  */
declare var GESTURE_NONE: number;
/**  */
declare var GESTURE_TAP: number;
/**  */
declare var GESTURE_DOUBLETAP: number;
/**  */
declare var GESTURE_HOLD: number;
/**  */
declare var GESTURE_DRAG: number;
/**  */
declare var GESTURE_SWIPE_RIGHT: number;
/**  */
declare var GESTURE_SWIPE_LEFT: number;
/**  */
declare var GESTURE_SWIPE_UP: number;
/**  */
declare var GESTURE_SWIPE_DOWN: number;
/**  */
declare var GESTURE_PINCH_IN: number;
/**  */
declare var GESTURE_PINCH_OUT: number;
/**  */
declare var CAMERA_CUSTOM: number;
/**  */
declare var CAMERA_FREE: number;
/**  */
declare var CAMERA_ORBITAL: number;
/**  */
declare var CAMERA_FIRST_PERSON: number;
/**  */
declare var CAMERA_THIRD_PERSON: number;
/**  */
declare var CAMERA_PERSPECTIVE: number;
/**  */
declare var CAMERA_ORTHOGRAPHIC: number;
/**  */
declare var NPATCH_NINE_PATCH: number;
/**  */
declare var NPATCH_THREE_PATCH_VERTICAL: number;
/**  */
declare var NPATCH_THREE_PATCH_HORIZONTAL: number;
/**  */
declare var RAYLIB_VERSION_MAJOR: number;
/**  */
declare var RAYLIB_VERSION_MINOR: number;
/**  */
declare var RAYLIB_VERSION_PATCH: number;
/**  */
declare var PI: number;
/** undefined */
declare var LIGHTGRAY: Color;
/** undefined */
declare var GRAY: Color;
/** undefined */
declare var DARKGRAY: Color;
/** undefined */
declare var YELLOW: Color;
/** undefined */
declare var GOLD: Color;
/** undefined */
declare var ORANGE: Color;
/** undefined */
declare var PINK: Color;
/** undefined */
declare var RED: Color;
/** undefined */
declare var MAROON: Color;
/** undefined */
declare var GREEN: Color;
/** undefined */
declare var LIME: Color;
/** undefined */
declare var DARKGREEN: Color;
/** undefined */
declare var SKYBLUE: Color;
/** undefined */
declare var BLUE: Color;
/** undefined */
declare var DARKBLUE: Color;
/** undefined */
declare var PURPLE: Color;
/** undefined */
declare var VIOLET: Color;
/** undefined */
declare var DARKPURPLE: Color;
/** undefined */
declare var BEIGE: Color;
/** undefined */
declare var BROWN: Color;
/** undefined */
declare var DARKBROWN: Color;
/** undefined */
declare var WHITE: Color;
/** undefined */
declare var BLACK: Color;
/** undefined */
declare var BLANK: Color;
/** undefined */
declare var MAGENTA: Color;
/** undefined */
declare var RAYWHITE: Color;
/**  */
declare var MOUSE_LEFT_BUTTON: number;
/**  */
declare var MOUSE_RIGHT_BUTTON: number;
/**  */
declare var MOUSE_MIDDLE_BUTTON: number;
/**  */
declare var MATERIAL_MAP_DIFFUSE: number;
/**  */
declare var MATERIAL_MAP_SPECULAR: number;
/**  */
declare var SHADER_LOC_MAP_DIFFUSE: number;
/**  */
declare var SHADER_LOC_MAP_SPECULAR: number;
