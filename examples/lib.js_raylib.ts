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
declare function initWindow(width: number, height: number, title: string | undefined | null): void;
/** undefined */
declare function closeWindow(): void;
/** undefined */
declare function windowShouldClose(): boolean;
/** undefined */
declare function isWindowReady(): boolean;
/** undefined */
declare function isWindowFullscreen(): boolean;
/** undefined */
declare function isWindowHidden(): boolean;
/** undefined */
declare function isWindowMinimized(): boolean;
/** undefined */
declare function isWindowMaximized(): boolean;
/** undefined */
declare function isWindowFocused(): boolean;
/** undefined */
declare function isWindowResized(): boolean;
/** undefined */
declare function isWindowState(flag: number): boolean;
/** undefined */
declare function setWindowState(flags: number): void;
/** undefined */
declare function clearWindowState(flags: number): void;
/** undefined */
declare function toggleFullscreen(): void;
/** undefined */
declare function toggleBorderlessWindowed(): void;
/** undefined */
declare function maximizeWindow(): void;
/** undefined */
declare function minimizeWindow(): void;
/** undefined */
declare function restoreWindow(): void;
/** undefined */
declare function setWindowIcon(image: Image): void;
/** undefined */
declare function setWindowTitle(title: string | undefined | null): void;
/** undefined */
declare function setWindowPosition(x: number, y: number): void;
/** undefined */
declare function setWindowMonitor(monitor: number): void;
/** undefined */
declare function setWindowMinSize(width: number, height: number): void;
/** undefined */
declare function setWindowMaxSize(width: number, height: number): void;
/** undefined */
declare function setWindowSize(width: number, height: number): void;
/** undefined */
declare function setWindowOpacity(opacity: number): void;
/** undefined */
declare function setWindowFocused(): void;
/** undefined */
declare function getScreenWidth(): number;
/** undefined */
declare function getScreenHeight(): number;
/** undefined */
declare function getRenderWidth(): number;
/** undefined */
declare function getRenderHeight(): number;
/** undefined */
declare function getMonitorCount(): number;
/** undefined */
declare function getCurrentMonitor(): number;
/** undefined */
declare function getMonitorPosition(monitor: number): Vector2;
/** undefined */
declare function getMonitorWidth(monitor: number): number;
/** undefined */
declare function getMonitorHeight(monitor: number): number;
/** undefined */
declare function getMonitorPhysicalWidth(monitor: number): number;
/** undefined */
declare function getMonitorPhysicalHeight(monitor: number): number;
/** undefined */
declare function getMonitorRefreshRate(monitor: number): number;
/** undefined */
declare function getWindowPosition(): Vector2;
/** undefined */
declare function getWindowScaleDPI(): Vector2;
/** undefined */
declare function getMonitorName(monitor: number): string | undefined | null;
/** undefined */
declare function setClipboardText(text: string | undefined | null): void;
/** undefined */
declare function getClipboardText(): string | undefined | null;
/** undefined */
declare function getClipboardImage(): Image;
/** undefined */
declare function enableEventWaiting(): void;
/** undefined */
declare function disableEventWaiting(): void;
/** undefined */
declare function showCursor(): void;
/** undefined */
declare function hideCursor(): void;
/** undefined */
declare function isCursorHidden(): boolean;
/** undefined */
declare function enableCursor(): void;
/** undefined */
declare function disableCursor(): void;
/** undefined */
declare function isCursorOnScreen(): boolean;
/** undefined */
declare function clearBackground(color: Color): void;
/** undefined */
declare function beginDrawing(): void;
/** undefined */
declare function endDrawing(): void;
/** undefined */
declare function beginMode2D(camera: Camera2D): void;
/** undefined */
declare function endMode2D(): void;
/** undefined */
declare function beginMode3D(camera: Camera3D): void;
/** undefined */
declare function endMode3D(): void;
/** undefined */
declare function beginTextureMode(target: RenderTexture): void;
/** undefined */
declare function endTextureMode(): void;
/** undefined */
declare function beginShaderMode(shader: Shader): void;
/** undefined */
declare function endShaderMode(): void;
/** undefined */
declare function beginBlendMode(mode: number): void;
/** undefined */
declare function endBlendMode(): void;
/** undefined */
declare function beginScissorMode(x: number, y: number, width: number, height: number): void;
/** undefined */
declare function endScissorMode(): void;
/** undefined */
declare function beginVrStereoMode(config: VrStereoConfig): void;
/** undefined */
declare function endVrStereoMode(): void;
/** undefined */
declare function loadVrStereoConfig(device: VrDeviceInfo): VrStereoConfig;
/** undefined */
declare function unloadVrStereoConfig(config: VrStereoConfig): void;
/** undefined */
declare function loadShader(vsFileName: string | undefined | null, fsFileName: string | undefined | null): Shader;
/** undefined */
declare function loadShaderFromMemory(vsCode: string | undefined | null, fsCode: string | undefined | null): Shader;
/** undefined */
declare function isShaderValid(shader: Shader): boolean;
/** undefined */
declare function getShaderLocation(shader: Shader, uniformName: string | undefined | null): number;
/** undefined */
declare function getShaderLocationAttrib(shader: Shader, attribName: string | undefined | null): number;
/** undefined */
declare function setShaderValue(shader: Shader, locIndex: number, value: void &, uniformType: number): void;
/** undefined */
declare function setShaderValueV(shader: Shader, locIndex: number, values: any, uniformType: number, count: number): void;
/** undefined */
declare function setShaderValueMatrix(shader: Shader, locIndex: number, mat: Matrix): void;
/** undefined */
declare function setShaderValueTexture(shader: Shader, locIndex: number, texture: Texture): void;
/** undefined */
declare function unloadShader(shader: Shader): void;
/** undefined */
declare function getScreenToWorldRay(position: Vector2, camera: Camera3D): Ray;
/** undefined */
declare function getScreenToWorldRayEx(position: Vector2, camera: Camera3D, width: number, height: number): Ray;
/** undefined */
declare function getWorldToScreen(position: Vector3, camera: Camera3D): Vector2;
/** undefined */
declare function getWorldToScreenEx(position: Vector3, camera: Camera3D, width: number, height: number): Vector2;
/** undefined */
declare function getWorldToScreen2D(position: Vector2, camera: Camera2D): Vector2;
/** undefined */
declare function getScreenToWorld2D(position: Vector2, camera: Camera2D): Vector2;
/** undefined */
declare function getCameraMatrix(camera: Camera3D): Matrix;
/** undefined */
declare function getCameraMatrix2D(camera: Camera2D): Matrix;
/** undefined */
declare function setTargetFPS(fps: number): void;
/** undefined */
declare function getFrameTime(): number;
/** undefined */
declare function getTime(): number;
/** undefined */
declare function getFPS(): number;
/** undefined */
declare function setRandomSeed(seed: number): void;
/** undefined */
declare function getRandomValue(min: number, max: number): number;
/** undefined */
declare function loadRandomSequence(count: number, min: number, max: number): int;
/** undefined */
declare function takeScreenshot(fileName: string | undefined | null): void;
/** undefined */
declare function setConfigFlags(flags: number): void;
/** undefined */
declare function openURL(url: string | undefined | null): void;
/** undefined */
declare function traceLog(logLevel: number): void;
/** undefined */
declare function setTraceLogLevel(logLevel: number): void;
/** undefined */
declare function setLoadFileDataCallback(callback: LoadFileDataCallback): void;
/** undefined */
declare function setSaveFileDataCallback(callback: SaveFileDataCallback): void;
/** undefined */
declare function setLoadFileTextCallback(callback: LoadFileTextCallback): void;
/** undefined */
declare function setSaveFileTextCallback(callback: SaveFileTextCallback): void;
/** undefined */
declare function loadFileData(fileName: string | undefined | null, dataSize: int &): ArrayBuffer;
/** undefined */
declare function saveFileData(fileName: string | undefined | null, data: any, dataSize: number): boolean;
/** undefined */
declare function loadFileText(fileName: string | undefined | null): string | undefined | null;
/** undefined */
declare function saveFileText(fileName: string | undefined | null, text: string | undefined | null): boolean;
/** undefined */
declare function fileExists(fileName: string | undefined | null): boolean;
/** undefined */
declare function directoryExists(dirPath: string | undefined | null): boolean;
/** undefined */
declare function isFileExtension(fileName: string | undefined | null, ext: string | undefined | null): boolean;
/** undefined */
declare function getFileLength(fileName: string | undefined | null): number;
/** undefined */
declare function getFileExtension(fileName: string | undefined | null): string | undefined | null;
/** undefined */
declare function getFileName(filePath: string | undefined | null): string | undefined | null;
/** undefined */
declare function getFileNameWithoutExt(filePath: string | undefined | null): string | undefined | null;
/** undefined */
declare function getDirectoryPath(filePath: string | undefined | null): string | undefined | null;
/** undefined */
declare function getPrevDirectoryPath(dirPath: string | undefined | null): string | undefined | null;
/** undefined */
declare function getWorkingDirectory(): string | undefined | null;
/** undefined */
declare function getApplicationDirectory(): string | undefined | null;
/** undefined */
declare function makeDirectory(dirPath: string | undefined | null): number;
/** undefined */
declare function changeDirectory(dir: string | undefined | null): boolean;
/** undefined */
declare function isPathFile(path: string | undefined | null): boolean;
/** undefined */
declare function isFileNameValid(fileName: string | undefined | null): boolean;
/** undefined */
declare function loadDirectoryFiles(dirPath: string | undefined | null): string[];
/** undefined */
declare function loadDirectoryFilesEx(basePath: string | undefined | null, filter: string | undefined | null, scanSubdirs: boolean): string[];
/** undefined */
declare function isFileDropped(): boolean;
/** undefined */
declare function loadDroppedFiles(): string[];
/** undefined */
declare function getFileModTime(fileName: string | undefined | null): number;
/** undefined */
declare function computeCRC32(data: ArrayBuffer, dataSize: number): number;
/** undefined */
declare function computeMD5(data: ArrayBuffer, dataSize: number): unsigned int;
/** undefined */
declare function computeSHA1(data: ArrayBuffer, dataSize: number): unsigned int;
/** undefined */
declare function loadAutomationEventList(fileName: string | undefined | null): AutomationEventList;
/** undefined */
declare function unloadAutomationEventList(list: AutomationEventList): void;
/** undefined */
declare function exportAutomationEventList(list: AutomationEventList, fileName: string | undefined | null): boolean;
/** undefined */
declare function setAutomationEventList(list: AutomationEventList &): void;
/** undefined */
declare function setAutomationEventBaseFrame(frame: number): void;
/** undefined */
declare function startAutomationEventRecording(): void;
/** undefined */
declare function stopAutomationEventRecording(): void;
/** undefined */
declare function playAutomationEvent(event: AutomationEvent): void;
/** undefined */
declare function isKeyPressed(key: number): boolean;
/** undefined */
declare function isKeyPressedRepeat(key: number): boolean;
/** undefined */
declare function isKeyDown(key: number): boolean;
/** undefined */
declare function isKeyReleased(key: number): boolean;
/** undefined */
declare function isKeyUp(key: number): boolean;
/** undefined */
declare function getKeyPressed(): number;
/** undefined */
declare function getCharPressed(): number;
/** undefined */
declare function getKeyName(key: number): string | undefined | null;
/** undefined */
declare function setExitKey(key: number): void;
/** undefined */
declare function isGamepadAvailable(gamepad: number): boolean;
/** undefined */
declare function getGamepadName(gamepad: number): string | undefined | null;
/** undefined */
declare function isGamepadButtonPressed(gamepad: number, button: number): boolean;
/** undefined */
declare function isGamepadButtonDown(gamepad: number, button: number): boolean;
/** undefined */
declare function isGamepadButtonReleased(gamepad: number, button: number): boolean;
/** undefined */
declare function isGamepadButtonUp(gamepad: number, button: number): boolean;
/** undefined */
declare function getGamepadButtonPressed(): number;
/** undefined */
declare function getGamepadAxisCount(gamepad: number): number;
/** undefined */
declare function getGamepadAxisMovement(gamepad: number, axis: number): number;
/** undefined */
declare function setGamepadMappings(mappings: string | undefined | null): number;
/** undefined */
declare function setGamepadVibration(gamepad: number, leftMotor: number, rightMotor: number, duration: number): void;
/** undefined */
declare function isMouseButtonPressed(button: number): boolean;
/** undefined */
declare function isMouseButtonDown(button: number): boolean;
/** undefined */
declare function isMouseButtonReleased(button: number): boolean;
/** undefined */
declare function isMouseButtonUp(button: number): boolean;
/** undefined */
declare function getMouseX(): number;
/** undefined */
declare function getMouseY(): number;
/** undefined */
declare function getMousePosition(): Vector2;
/** undefined */
declare function getMouseDelta(): Vector2;
/** undefined */
declare function setMousePosition(x: number, y: number): void;
/** undefined */
declare function setMouseOffset(offsetX: number, offsetY: number): void;
/** undefined */
declare function setMouseScale(scaleX: number, scaleY: number): void;
/** undefined */
declare function getMouseWheelMove(): number;
/** undefined */
declare function getMouseWheelMoveV(): Vector2;
/** undefined */
declare function setMouseCursor(cursor: number): void;
/** undefined */
declare function getTouchX(): number;
/** undefined */
declare function getTouchY(): number;
/** undefined */
declare function getTouchPosition(index: number): Vector2;
/** undefined */
declare function getTouchPointId(index: number): number;
/** undefined */
declare function getTouchPointCount(): number;
/** undefined */
declare function setGesturesEnabled(flags: number): void;
/** undefined */
declare function isGestureDetected(gesture: number): boolean;
/** undefined */
declare function getGestureDetected(): number;
/** undefined */
declare function getGestureHoldDuration(): number;
/** undefined */
declare function getGestureDragVector(): Vector2;
/** undefined */
declare function getGestureDragAngle(): number;
/** undefined */
declare function getGesturePinchVector(): Vector2;
/** undefined */
declare function getGesturePinchAngle(): number;
/** undefined */
declare function updateCamera(camera: Camera &, mode: number): void;
/** undefined */
declare function updateCameraPro(camera: Camera &, movement: Vector3, rotation: Vector3, zoom: number): void;
/** undefined */
declare function setShapesTexture(texture: Texture, source: Rectangle): void;
/** undefined */
declare function getShapesTexture(): Texture;
/** undefined */
declare function getShapesTextureRectangle(): Rectangle;
/** undefined */
declare function drawPixel(posX: number, posY: number, color: Color): void;
/** undefined */
declare function drawPixelV(position: Vector2, color: Color): void;
/** undefined */
declare function drawLine(startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void;
/** undefined */
declare function drawLineV(startPos: Vector2, endPos: Vector2, color: Color): void;
/** undefined */
declare function drawLineEx(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void;
/** undefined */
declare function drawLineBezier(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void;
/** undefined */
declare function drawCircle(centerX: number, centerY: number, radius: number, color: Color): void;
/** undefined */
declare function drawCircleSector(center: Vector2, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** undefined */
declare function drawCircleSectorLines(center: Vector2, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** undefined */
declare function drawCircleGradient(centerX: number, centerY: number, radius: number, inner: Color, outer: Color): void;
/** undefined */
declare function drawCircleV(center: Vector2, radius: number, color: Color): void;
/** undefined */
declare function drawCircleLines(centerX: number, centerY: number, radius: number, color: Color): void;
/** undefined */
declare function drawCircleLinesV(center: Vector2, radius: number, color: Color): void;
/** undefined */
declare function drawEllipse(centerX: number, centerY: number, radiusH: number, radiusV: number, color: Color): void;
/** undefined */
declare function drawEllipseLines(centerX: number, centerY: number, radiusH: number, radiusV: number, color: Color): void;
/** undefined */
declare function drawRing(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** undefined */
declare function drawRingLines(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
/** undefined */
declare function drawRectangle(posX: number, posY: number, width: number, height: number, color: Color): void;
/** undefined */
declare function drawRectangleV(position: Vector2, size: Vector2, color: Color): void;
/** undefined */
declare function drawRectangleRec(rec: Rectangle, color: Color): void;
/** undefined */
declare function drawRectanglePro(rec: Rectangle, origin: Vector2, rotation: number, color: Color): void;
/** undefined */
declare function drawRectangleGradientV(posX: number, posY: number, width: number, height: number, top: Color, bottom: Color): void;
/** undefined */
declare function drawRectangleGradientH(posX: number, posY: number, width: number, height: number, left: Color, right: Color): void;
/** undefined */
declare function drawRectangleGradientEx(rec: Rectangle, topLeft: Color, bottomLeft: Color, topRight: Color, bottomRight: Color): void;
/** undefined */
declare function drawRectangleLines(posX: number, posY: number, width: number, height: number, color: Color): void;
/** undefined */
declare function drawRectangleLinesEx(rec: Rectangle, lineThick: number, color: Color): void;
/** undefined */
declare function drawRectangleRounded(rec: Rectangle, roundness: number, segments: number, color: Color): void;
/** undefined */
declare function drawRectangleRoundedLines(rec: Rectangle, roundness: number, segments: number, color: Color): void;
/** undefined */
declare function drawRectangleRoundedLinesEx(rec: Rectangle, roundness: number, segments: number, lineThick: number, color: Color): void;
/** undefined */
declare function drawTriangle(v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** undefined */
declare function drawTriangleLines(v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** undefined */
declare function drawPoly(center: Vector2, sides: number, radius: number, rotation: number, color: Color): void;
/** undefined */
declare function drawPolyLines(center: Vector2, sides: number, radius: number, rotation: number, color: Color): void;
/** undefined */
declare function drawPolyLinesEx(center: Vector2, sides: number, radius: number, rotation: number, lineThick: number, color: Color): void;
/** undefined */
declare function drawSplineLinear(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** undefined */
declare function drawSplineBasis(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** undefined */
declare function drawSplineCatmullRom(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** undefined */
declare function drawSplineBezierQuadratic(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** undefined */
declare function drawSplineBezierCubic(points: Vector2, pointCount: number, thick: number, color: Color): void;
/** undefined */
declare function drawSplineSegmentLinear(p1: Vector2, p2: Vector2, thick: number, color: Color): void;
/** undefined */
declare function drawSplineSegmentBasis(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, thick: number, color: Color): void;
/** undefined */
declare function drawSplineSegmentCatmullRom(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, thick: number, color: Color): void;
/** undefined */
declare function drawSplineSegmentBezierQuadratic(p1: Vector2, c2: Vector2, p3: Vector2, thick: number, color: Color): void;
/** undefined */
declare function drawSplineSegmentBezierCubic(p1: Vector2, c2: Vector2, c3: Vector2, p4: Vector2, thick: number, color: Color): void;
/** undefined */
declare function getSplinePointLinear(startPos: Vector2, endPos: Vector2, t: number): Vector2;
/** undefined */
declare function getSplinePointBasis(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, t: number): Vector2;
/** undefined */
declare function getSplinePointCatmullRom(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, t: number): Vector2;
/** undefined */
declare function getSplinePointBezierQuad(p1: Vector2, c2: Vector2, p3: Vector2, t: number): Vector2;
/** undefined */
declare function getSplinePointBezierCubic(p1: Vector2, c2: Vector2, c3: Vector2, p4: Vector2, t: number): Vector2;
/** undefined */
declare function checkCollisionRecs(rec1: Rectangle, rec2: Rectangle): boolean;
/** undefined */
declare function checkCollisionCircles(center1: Vector2, radius1: number, center2: Vector2, radius2: number): boolean;
/** undefined */
declare function checkCollisionCircleRec(center: Vector2, radius: number, rec: Rectangle): boolean;
/** undefined */
declare function checkCollisionCircleLine(center: Vector2, radius: number, p1: Vector2, p2: Vector2): boolean;
/** undefined */
declare function checkCollisionPointRec(point: Vector2, rec: Rectangle): boolean;
/** undefined */
declare function checkCollisionPointCircle(point: Vector2, center: Vector2, radius: number): boolean;
/** undefined */
declare function checkCollisionPointTriangle(point: Vector2, p1: Vector2, p2: Vector2, p3: Vector2): boolean;
/** undefined */
declare function checkCollisionPointLine(point: Vector2, p1: Vector2, p2: Vector2, threshold: number): boolean;
/** undefined */
declare function getCollisionRec(rec1: Rectangle, rec2: Rectangle): Rectangle;
/** undefined */
declare function loadImage(fileName: string | undefined | null): Image;
/** undefined */
declare function loadImageRaw(fileName: string | undefined | null, width: number, height: number, format: number, headerSize: number): Image;
/** undefined */
declare function loadImageAnimFromMemory(fileType: string | undefined | null, fileData: ArrayBuffer, dataSize: number, frames: int &): Image;
/** undefined */
declare function loadImageFromMemory(fileType: string | undefined | null, fileData: ArrayBuffer, dataSize: number): Image;
/** undefined */
declare function loadImageFromTexture(texture: Texture): Image;
/** undefined */
declare function loadImageFromScreen(): Image;
/** undefined */
declare function isImageValid(image: Image): boolean;
/** undefined */
declare function unloadImage(image: Image): void;
/** undefined */
declare function exportImage(image: Image, fileName: string | undefined | null): boolean;
/** undefined */
declare function exportImageToMemory(image: Image, fileType: string | undefined | null, fileSize: int &): ArrayBuffer;
/** undefined */
declare function genImageColor(width: number, height: number, color: Color): Image;
/** undefined */
declare function genImageGradientLinear(width: number, height: number, direction: number, start: Color, end: Color): Image;
/** undefined */
declare function genImageGradientRadial(width: number, height: number, density: number, inner: Color, outer: Color): Image;
/** undefined */
declare function genImageGradientSquare(width: number, height: number, density: number, inner: Color, outer: Color): Image;
/** undefined */
declare function genImageChecked(width: number, height: number, checksX: number, checksY: number, col1: Color, col2: Color): Image;
/** undefined */
declare function genImageWhiteNoise(width: number, height: number, factor: number): Image;
/** undefined */
declare function genImagePerlinNoise(width: number, height: number, offsetX: number, offsetY: number, scale: number): Image;
/** undefined */
declare function genImageCellular(width: number, height: number, tileSize: number): Image;
/** undefined */
declare function genImageText(width: number, height: number, text: string | undefined | null): Image;
/** undefined */
declare function imageCopy(image: Image): Image;
/** undefined */
declare function imageFromImage(image: Image, rec: Rectangle): Image;
/** undefined */
declare function imageFromChannel(image: Image, selectedChannel: number): Image;
/** undefined */
declare function imageText(text: string | undefined | null, fontSize: number, color: Color): Image;
/** undefined */
declare function imageTextEx(font: Font, text: string | undefined | null, fontSize: number, spacing: number, tint: Color): Image;
/** undefined */
declare function imageFormat(image: Image &, newFormat: number): void;
/** undefined */
declare function imageToPOT(image: Image &, fill: Color): void;
/** undefined */
declare function imageCrop(image: Image &, crop: Rectangle): void;
/** undefined */
declare function imageAlphaCrop(image: Image &, threshold: number): void;
/** undefined */
declare function imageAlphaClear(image: Image &, color: Color, threshold: number): void;
/** undefined */
declare function imageAlphaMask(image: Image &, alphaMask: Image): void;
/** undefined */
declare function imageAlphaPremultiply(image: Image &): void;
/** undefined */
declare function imageBlurGaussian(image: Image &, blurSize: number): void;
/** undefined */
declare function imageKernelConvolution(image: Image &, kernel: float, kernelSize: number): void;
/** undefined */
declare function imageResize(image: Image &, newWidth: number, newHeight: number): void;
/** undefined */
declare function imageResizeNN(image: Image &, newWidth: number, newHeight: number): void;
/** undefined */
declare function imageResizeCanvas(image: Image &, newWidth: number, newHeight: number, offsetX: number, offsetY: number, fill: Color): void;
/** undefined */
declare function imageMipmaps(image: Image &): void;
/** undefined */
declare function imageDither(image: Image &, rBpp: number, gBpp: number, bBpp: number, aBpp: number): void;
/** undefined */
declare function imageFlipVertical(image: Image &): void;
/** undefined */
declare function imageFlipHorizontal(image: Image &): void;
/** undefined */
declare function imageRotate(image: Image &, degrees: number): void;
/** undefined */
declare function imageRotateCW(image: Image &): void;
/** undefined */
declare function imageRotateCCW(image: Image &): void;
/** undefined */
declare function imageColorTint(image: Image &, color: Color): void;
/** undefined */
declare function imageColorInvert(image: Image &): void;
/** undefined */
declare function imageColorGrayscale(image: Image &): void;
/** undefined */
declare function imageColorContrast(image: Image &, contrast: number): void;
/** undefined */
declare function imageColorBrightness(image: Image &, brightness: number): void;
/** undefined */
declare function imageColorReplace(image: Image &, color: Color, replace: Color): void;
/** undefined */
declare function loadImageColors(image: Image): ArrayBuffer;
/** undefined */
declare function getImageAlphaBorder(image: Image, threshold: number): Rectangle;
/** undefined */
declare function getImageColor(image: Image, x: number, y: number): Color;
/** undefined */
declare function imageClearBackground(dst: Image &, color: Color): void;
/** undefined */
declare function imageDrawPixel(dst: Image &, posX: number, posY: number, color: Color): void;
/** undefined */
declare function imageDrawPixelV(dst: Image &, position: Vector2, color: Color): void;
/** undefined */
declare function imageDrawLine(dst: Image &, startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void;
/** undefined */
declare function imageDrawLineV(dst: Image &, start: Vector2, end: Vector2, color: Color): void;
/** undefined */
declare function imageDrawLineEx(dst: Image &, start: Vector2, end: Vector2, thick: number, color: Color): void;
/** undefined */
declare function imageDrawCircle(dst: Image &, centerX: number, centerY: number, radius: number, color: Color): void;
/** undefined */
declare function imageDrawCircleV(dst: Image &, center: Vector2, radius: number, color: Color): void;
/** undefined */
declare function imageDrawCircleLines(dst: Image &, centerX: number, centerY: number, radius: number, color: Color): void;
/** undefined */
declare function imageDrawCircleLinesV(dst: Image &, center: Vector2, radius: number, color: Color): void;
/** undefined */
declare function imageDrawRectangle(dst: Image &, posX: number, posY: number, width: number, height: number, color: Color): void;
/** undefined */
declare function imageDrawRectangleV(dst: Image &, position: Vector2, size: Vector2, color: Color): void;
/** undefined */
declare function imageDrawRectangleRec(dst: Image &, rec: Rectangle, color: Color): void;
/** undefined */
declare function imageDrawRectangleLines(dst: Image &, rec: Rectangle, thick: number, color: Color): void;
/** undefined */
declare function imageDrawTriangle(dst: Image &, v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** undefined */
declare function imageDrawTriangleEx(dst: Image &, v1: Vector2, v2: Vector2, v3: Vector2, c1: Color, c2: Color, c3: Color): void;
/** undefined */
declare function imageDrawTriangleLines(dst: Image &, v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
/** undefined */
declare function imageDrawTriangleFan(dst: Image &, points: Vector2, pointCount: number, color: Color): void;
/** undefined */
declare function imageDrawTriangleStrip(dst: Image &, points: Vector2, pointCount: number, color: Color): void;
/** undefined */
declare function imageDraw(dst: Image &, src: Image, srcRec: Rectangle, dstRec: Rectangle, tint: Color): void;
/** undefined */
declare function imageDrawText(dst: Image &, text: string | undefined | null, posX: number, posY: number, fontSize: number, color: Color): void;
/** undefined */
declare function imageDrawTextEx(dst: Image &, font: Font, text: string | undefined | null, position: Vector2, fontSize: number, spacing: number, tint: Color): void;
/** undefined */
declare function loadTexture(fileName: string | undefined | null): Texture;
/** undefined */
declare function loadTextureFromImage(image: Image): Texture;
/** undefined */
declare function loadTextureCubemap(image: Image, layout: number): Texture;
/** undefined */
declare function loadRenderTexture(width: number, height: number): RenderTexture;
/** undefined */
declare function isTextureValid(texture: Texture): boolean;
/** undefined */
declare function unloadTexture(texture: Texture): void;
/** undefined */
declare function isRenderTextureValid(target: RenderTexture): boolean;
/** undefined */
declare function unloadRenderTexture(target: RenderTexture): void;
/** undefined */
declare function updateTexture(texture: Texture, pixels: any): void;
/** undefined */
declare function updateTextureRec(texture: Texture, rec: Rectangle, pixels: any): void;
/** undefined */
declare function genTextureMipmaps(texture: Texture2D &): void;
/** undefined */
declare function setTextureFilter(texture: Texture, filter: number): void;
/** undefined */
declare function setTextureWrap(texture: Texture, wrap: number): void;
/** undefined */
declare function drawTexture(texture: Texture, posX: number, posY: number, tint: Color): void;
/** undefined */
declare function drawTextureV(texture: Texture, position: Vector2, tint: Color): void;
/** undefined */
declare function drawTextureEx(texture: Texture, position: Vector2, rotation: number, scale: number, tint: Color): void;
/** undefined */
declare function drawTextureRec(texture: Texture, source: Rectangle, position: Vector2, tint: Color): void;
/** undefined */
declare function drawTexturePro(texture: Texture, source: Rectangle, dest: Rectangle, origin: Vector2, rotation: number, tint: Color): void;
/** undefined */
declare function drawTextureNPatch(texture: Texture, nPatchInfo: NPatchInfo, dest: Rectangle, origin: Vector2, rotation: number, tint: Color): void;
/** undefined */
declare function colorIsEqual(col1: Color, col2: Color): boolean;
/** undefined */
declare function fade(color: Color, alpha: number): Color;
/** undefined */
declare function colorToInt(color: Color): number;
/** undefined */
declare function colorNormalize(color: Color): Vector4;
/** undefined */
declare function colorFromNormalized(normalized: Vector4): Color;
/** undefined */
declare function colorToHSV(color: Color): Vector3;
/** undefined */
declare function colorFromHSV(hue: number, saturation: number, value: number): Color;
/** undefined */
declare function colorTint(color: Color, tint: Color): Color;
/** undefined */
declare function colorBrightness(color: Color, factor: number): Color;
/** undefined */
declare function colorContrast(color: Color, contrast: number): Color;
/** undefined */
declare function colorAlpha(color: Color, alpha: number): Color;
/** undefined */
declare function colorAlphaBlend(dst: Color, src: Color, tint: Color): Color;
/** undefined */
declare function colorLerp(color1: Color, color2: Color, factor: number): Color;
/** undefined */
declare function getColor(hexValue: number): Color;
/** undefined */
declare function getPixelDataSize(width: number, height: number, format: number): number;
/** undefined */
declare function getFontDefault(): Font;
/** undefined */
declare function loadFont(fileName: string | undefined | null): Font;
/** undefined */
declare function loadFontEx(fileName: string | undefined | null, fontSize: number, codepoints: int, codepointCount: number): Font;
/** undefined */
declare function loadFontFromImage(image: Image, key: Color, firstChar: number): Font;
/** undefined */
declare function isFontValid(font: Font): boolean;
/** undefined */
declare function unloadFont(font: Font): void;
/** undefined */
declare function drawFPS(posX: number, posY: number): void;
/** undefined */
declare function drawText(text: string | undefined | null, posX: number, posY: number, fontSize: number, color: Color): void;
/** undefined */
declare function drawTextEx(font: Font, text: string | undefined | null, position: Vector2, fontSize: number, spacing: number, tint: Color): void;
/** undefined */
declare function drawTextPro(font: Font, text: string | undefined | null, position: Vector2, origin: Vector2, rotation: number, fontSize: number, spacing: number, tint: Color): void;
/** undefined */
declare function drawTextCodepoint(font: Font, codepoint: number, position: Vector2, fontSize: number, tint: Color): void;
/** undefined */
declare function setTextLineSpacing(spacing: number): void;
/** undefined */
declare function measureText(text: string | undefined | null, fontSize: number): number;
/** undefined */
declare function measureTextEx(font: Font, text: string | undefined | null, fontSize: number, spacing: number): Vector2;
/** undefined */
declare function getGlyphIndex(font: Font, codepoint: number): number;
/** undefined */
declare function getGlyphAtlasRec(font: Font, codepoint: number): Rectangle;
/** undefined */
declare function textCopy(dst: char &, src: string | undefined | null): number;
/** undefined */
declare function textIsEqual(text1: string | undefined | null, text2: string | undefined | null): boolean;
/** undefined */
declare function textLength(text: string | undefined | null): number;
/** undefined */
declare function textFormat(text: string | undefined | null, args: ...): string | undefined | null;
/** undefined */
declare function textSubtext(text: string | undefined | null, position: number, length: number): string | undefined | null;
/** undefined */
declare function textReplace(text: string | undefined | null, replace: string | undefined | null, by: string | undefined | null): string | undefined | null;
/** undefined */
declare function textInsert(text: string | undefined | null, insert: string | undefined | null, position: number): string | undefined | null;
/** undefined */
declare function textJoin(textList: char *, count: number, delimiter: string | undefined | null): string | undefined | null;
/** undefined */
declare function textSplit(text: string | undefined | null, delimiter: char, count: int &): char *;
/** undefined */
declare function textAppend(text: string | undefined | null, append: string | undefined | null, position: int &): void;
/** undefined */
declare function textFindIndex(text: string | undefined | null, find: string | undefined | null): number;
/** undefined */
declare function textToUpper(text: string | undefined | null): string | undefined | null;
/** undefined */
declare function textToLower(text: string | undefined | null): string | undefined | null;
/** undefined */
declare function textToPascal(text: string | undefined | null): string | undefined | null;
/** undefined */
declare function textToSnake(text: string | undefined | null): string | undefined | null;
/** undefined */
declare function textToCamel(text: string | undefined | null): string | undefined | null;
/** undefined */
declare function textToInteger(text: string | undefined | null): number;
/** undefined */
declare function textToFloat(text: string | undefined | null): number;
/** undefined */
declare function drawLine3D(startPos: Vector3, endPos: Vector3, color: Color): void;
/** undefined */
declare function drawPoint3D(position: Vector3, color: Color): void;
/** undefined */
declare function drawCircle3D(center: Vector3, radius: number, rotationAxis: Vector3, rotationAngle: number, color: Color): void;
/** undefined */
declare function drawTriangle3D(v1: Vector3, v2: Vector3, v3: Vector3, color: Color): void;
/** undefined */
declare function drawCube(position: Vector3, width: number, height: number, length: number, color: Color): void;
/** undefined */
declare function drawCubeV(position: Vector3, size: Vector3, color: Color): void;
/** undefined */
declare function drawCubeWires(position: Vector3, width: number, height: number, length: number, color: Color): void;
/** undefined */
declare function drawCubeWiresV(position: Vector3, size: Vector3, color: Color): void;
/** undefined */
declare function drawSphere(centerPos: Vector3, radius: number, color: Color): void;
/** undefined */
declare function drawSphereEx(centerPos: Vector3, radius: number, rings: number, slices: number, color: Color): void;
/** undefined */
declare function drawSphereWires(centerPos: Vector3, radius: number, rings: number, slices: number, color: Color): void;
/** undefined */
declare function drawCylinder(position: Vector3, radiusTop: number, radiusBottom: number, height: number, slices: number, color: Color): void;
/** undefined */
declare function drawCylinderEx(startPos: Vector3, endPos: Vector3, startRadius: number, endRadius: number, sides: number, color: Color): void;
/** undefined */
declare function drawCylinderWires(position: Vector3, radiusTop: number, radiusBottom: number, height: number, slices: number, color: Color): void;
/** undefined */
declare function drawCylinderWiresEx(startPos: Vector3, endPos: Vector3, startRadius: number, endRadius: number, sides: number, color: Color): void;
/** undefined */
declare function drawCapsule(startPos: Vector3, endPos: Vector3, radius: number, slices: number, rings: number, color: Color): void;
/** undefined */
declare function drawCapsuleWires(startPos: Vector3, endPos: Vector3, radius: number, slices: number, rings: number, color: Color): void;
/** undefined */
declare function drawPlane(centerPos: Vector3, size: Vector2, color: Color): void;
/** undefined */
declare function drawRay(ray: Ray, color: Color): void;
/** undefined */
declare function drawGrid(slices: number, spacing: number): void;
/** undefined */
declare function loadModel(fileName: string | undefined | null): Model;
/** undefined */
declare function loadModelFromMesh(mesh: Mesh): Model;
/** undefined */
declare function isModelValid(model: Model): boolean;
/** undefined */
declare function unloadModel(model: Model): void;
/** undefined */
declare function getModelBoundingBox(model: Model): BoundingBox;
/** undefined */
declare function drawModel(model: Model, position: Vector3, scale: number, tint: Color): void;
/** undefined */
declare function drawModelEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
/** undefined */
declare function drawModelWires(model: Model, position: Vector3, scale: number, tint: Color): void;
/** undefined */
declare function drawModelWiresEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
/** undefined */
declare function drawModelPoints(model: Model, position: Vector3, scale: number, tint: Color): void;
/** undefined */
declare function drawModelPointsEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
/** undefined */
declare function drawBoundingBox(box: BoundingBox, color: Color): void;
/** undefined */
declare function drawBillboard(camera: Camera3D, texture: Texture, position: Vector3, scale: number, tint: Color): void;
/** undefined */
declare function drawBillboardRec(camera: Camera3D, texture: Texture, source: Rectangle, position: Vector3, size: Vector2, tint: Color): void;
/** undefined */
declare function drawBillboardPro(camera: Camera3D, texture: Texture, source: Rectangle, position: Vector3, up: Vector3, size: Vector2, origin: Vector2, rotation: number, tint: Color): void;
/** undefined */
declare function uploadMesh(mesh: Mesh &, dynamic: boolean): void;
/** undefined */
declare function updateMeshBuffer(mesh: Mesh, index: number, data: any, dataSize: number, offset: number): void;
/** undefined */
declare function unloadMesh(mesh: Mesh): void;
/** undefined */
declare function drawMesh(mesh: Mesh, material: Material, transform: Matrix): void;
/** undefined */
declare function drawMeshInstanced(mesh: Mesh, material: Material, transforms: Matrix, instances: number): void;
/** undefined */
declare function getMeshBoundingBox(mesh: Mesh): BoundingBox;
/** undefined */
declare function genMeshTangents(mesh: Mesh &): void;
/** undefined */
declare function exportMesh(mesh: Mesh, fileName: string | undefined | null): boolean;
/** undefined */
declare function exportMeshAsCode(mesh: Mesh, fileName: string | undefined | null): boolean;
/** undefined */
declare function genMeshPoly(sides: number, radius: number): Mesh;
/** undefined */
declare function genMeshPlane(width: number, length: number, resX: number, resZ: number): Mesh;
/** undefined */
declare function genMeshCube(width: number, height: number, length: number): Mesh;
/** undefined */
declare function genMeshSphere(radius: number, rings: number, slices: number): Mesh;
/** undefined */
declare function genMeshHemiSphere(radius: number, rings: number, slices: number): Mesh;
/** undefined */
declare function genMeshCylinder(radius: number, height: number, slices: number): Mesh;
/** undefined */
declare function genMeshCone(radius: number, height: number, slices: number): Mesh;
/** undefined */
declare function genMeshTorus(radius: number, size: number, radSeg: number, sides: number): Mesh;
/** undefined */
declare function genMeshKnot(radius: number, size: number, radSeg: number, sides: number): Mesh;
/** undefined */
declare function genMeshHeightmap(heightmap: Image, size: Vector3): Mesh;
/** undefined */
declare function genMeshCubicmap(cubicmap: Image, cubeSize: Vector3): Mesh;
/** undefined */
declare function loadMaterialDefault(): Material;
/** undefined */
declare function isMaterialValid(material: Material): boolean;
/** undefined */
declare function unloadMaterial(material: Material): void;
/** undefined */
declare function setMaterialTexture(material: Material &, mapType: number, texture: Texture): void;
/** undefined */
declare function setModelMeshMaterial(model: Model &, meshId: number, materialId: number): void;
/** undefined */
declare function updateModelAnimationBones(model: Model, anim: ModelAnimation, frame: number): void;
/** undefined */
declare function checkCollisionSpheres(center1: Vector3, radius1: number, center2: Vector3, radius2: number): boolean;
/** undefined */
declare function checkCollisionBoxes(box1: BoundingBox, box2: BoundingBox): boolean;
/** undefined */
declare function checkCollisionBoxSphere(box: BoundingBox, center: Vector3, radius: number): boolean;
/** undefined */
declare function getRayCollisionSphere(ray: Ray, center: Vector3, radius: number): RayCollision;
/** undefined */
declare function getRayCollisionBox(ray: Ray, box: BoundingBox): RayCollision;
/** undefined */
declare function getRayCollisionMesh(ray: Ray, mesh: Mesh, transform: Matrix): RayCollision;
/** undefined */
declare function getRayCollisionTriangle(ray: Ray, p1: Vector3, p2: Vector3, p3: Vector3): RayCollision;
/** undefined */
declare function getRayCollisionQuad(ray: Ray, p1: Vector3, p2: Vector3, p3: Vector3, p4: Vector3): RayCollision;
/** undefined */
declare function initAudioDevice(): void;
/** undefined */
declare function closeAudioDevice(): void;
/** undefined */
declare function isAudioDeviceReady(): boolean;
/** undefined */
declare function setMasterVolume(volume: number): void;
/** undefined */
declare function getMasterVolume(): number;
/** undefined */
declare function loadWave(fileName: string | undefined | null): Wave;
/** undefined */
declare function loadWaveFromMemory(fileType: string | undefined | null, fileData: ArrayBuffer, dataSize: number): Wave;
/** undefined */
declare function isWaveValid(wave: Wave): boolean;
/** undefined */
declare function loadSound(fileName: string | undefined | null): Sound;
/** undefined */
declare function loadSoundFromWave(wave: Wave): Sound;
/** undefined */
declare function loadSoundAlias(source: Sound): Sound;
/** undefined */
declare function isSoundValid(sound: Sound): boolean;
/** undefined */
declare function updateSound(sound: Sound, data: any, sampleCount: number): void;
/** undefined */
declare function unloadWave(wave: Wave): void;
/** undefined */
declare function unloadSound(sound: Sound): void;
/** undefined */
declare function unloadSoundAlias(alias: Sound): void;
/** undefined */
declare function exportWave(wave: Wave, fileName: string | undefined | null): boolean;
/** undefined */
declare function playSound(sound: Sound): void;
/** undefined */
declare function stopSound(sound: Sound): void;
/** undefined */
declare function pauseSound(sound: Sound): void;
/** undefined */
declare function resumeSound(sound: Sound): void;
/** undefined */
declare function isSoundPlaying(sound: Sound): boolean;
/** undefined */
declare function setSoundVolume(sound: Sound, volume: number): void;
/** undefined */
declare function setSoundPitch(sound: Sound, pitch: number): void;
/** undefined */
declare function setSoundPan(sound: Sound, pan: number): void;
/** undefined */
declare function waveCopy(wave: Wave): Wave;
/** undefined */
declare function waveCrop(wave: Wave &, initFrame: number, finalFrame: number): void;
/** undefined */
declare function waveFormat(wave: Wave &, sampleRate: number, sampleSize: number, channels: number): void;
/** undefined */
declare function loadWaveSamples(wave: Wave): ArrayBuffer;
/** undefined */
declare function unloadWaveSamples(samples: float &): void;
/** undefined */
declare function loadMusicStream(fileName: string | undefined | null): Music;
/** undefined */
declare function loadMusicStreamFromMemory(fileType: string | undefined | null, data: ArrayBuffer, dataSize: number): Music;
/** undefined */
declare function isMusicValid(music: Music): boolean;
/** undefined */
declare function unloadMusicStream(music: Music): void;
/** undefined */
declare function playMusicStream(music: Music): void;
/** undefined */
declare function isMusicStreamPlaying(music: Music): boolean;
/** undefined */
declare function updateMusicStream(music: Music): void;
/** undefined */
declare function stopMusicStream(music: Music): void;
/** undefined */
declare function pauseMusicStream(music: Music): void;
/** undefined */
declare function resumeMusicStream(music: Music): void;
/** undefined */
declare function seekMusicStream(music: Music, position: number): void;
/** undefined */
declare function setMusicVolume(music: Music, volume: number): void;
/** undefined */
declare function setMusicPitch(music: Music, pitch: number): void;
/** undefined */
declare function setMusicPan(music: Music, pan: number): void;
/** undefined */
declare function getMusicTimeLength(music: Music): number;
/** undefined */
declare function getMusicTimePlayed(music: Music): number;
/** undefined */
declare function loadAudioStream(sampleRate: number, sampleSize: number, channels: number): AudioStream;
/** undefined */
declare function isAudioStreamValid(stream: AudioStream): boolean;
/** undefined */
declare function unloadAudioStream(stream: AudioStream): void;
/** undefined */
declare function updateAudioStream(stream: AudioStream, data: any, frameCount: number): void;
/** undefined */
declare function isAudioStreamProcessed(stream: AudioStream): boolean;
/** undefined */
declare function playAudioStream(stream: AudioStream): void;
/** undefined */
declare function pauseAudioStream(stream: AudioStream): void;
/** undefined */
declare function resumeAudioStream(stream: AudioStream): void;
/** undefined */
declare function isAudioStreamPlaying(stream: AudioStream): boolean;
/** undefined */
declare function stopAudioStream(stream: AudioStream): void;
/** undefined */
declare function setAudioStreamVolume(stream: AudioStream, volume: number): void;
/** undefined */
declare function setAudioStreamPitch(stream: AudioStream, pitch: number): void;
/** undefined */
declare function setAudioStreamPan(stream: AudioStream, pan: number): void;
/** undefined */
declare function setAudioStreamBufferSizeDefault(size: number): void;
/** undefined */
declare function attachAudioMixedProcessor(processor: AudioMixedProcessor): void;
/** undefined */
declare function detachAudioMixedProcessor(processor: AudioCallback): void;
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
