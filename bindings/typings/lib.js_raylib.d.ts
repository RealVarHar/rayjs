declare module "rayjs:raylib" {
    type LoadFileDataCallback = (arg_fileName:string,arg_dataSize:number[])=>number[];
    type SaveFileDataCallback = (arg_fileName:string,arg_data:number[],arg_dataSize:number)=>boolean;
    type LoadFileTextCallback = (arg_fileName:string)=>string;
    type SaveFileTextCallback = (arg_fileName:string,arg_text:string)=>boolean;
    type AudioCallback = string | number;
    type AudioStreamCallback = string | number;
    type AudioMixedProcessor = string | number;
    type Quaternion = Vector4;
    type Texture2D = Texture;
    type TextureCubemap = Texture;
    type RenderTexture2D = RenderTexture;
    type Camera = Camera3D;
    interface Vector2 {
        x: number,
        y: number,
    }
    var Vector2: {
        prototype: Vector2;
        new(x?: number, y?: number): Vector2;
    }
    interface Vector3 {
        x: number,
        y: number,
        z: number,
    }
    var Vector3: {
        prototype: Vector3;
        new(x?: number, y?: number, z?: number): Vector3;
    }
    interface Vector4 {
        x: number,
        y: number,
        z: number,
        w: number,
    }
    var Vector4: {
        prototype: Vector4;
        new(x?: number, y?: number, z?: number, w?: number): Vector4;
    }
    interface Matrix {
    }
    var Matrix: {
        prototype: Matrix;
    }
    interface Color {
        r: number,
        g: number,
        b: number,
        a: number,
    }
    var Color: {
        prototype: Color;
        new(r?: number, g?: number, b?: number, a?: number): Color;
    }
    interface Rectangle {
        x: number,
        y: number,
        width: number,
        height: number,
    }
    var Rectangle: {
        prototype: Rectangle;
        new(x?: number, y?: number, width?: number, height?: number): Rectangle;
    }
    interface Image {
        data: ArrayBuffer,
        width: number,
        height: number,
        mipmaps: number,
        format: number,
    }
    var Image: {
        prototype: Image;
        new(data?: ArrayBuffer, width?: number, height?: number, mipmaps?: number, format?: number): Image;
    }
    interface Texture {
        width: number,
        height: number,
        mipmaps: number,
        format: number,
    }
    var Texture: {
        prototype: Texture;
        new(width?: number, height?: number, mipmaps?: number, format?: number): Texture;
    }
    interface RenderTexture {
        id: number,
        texture: Texture,
        depth: Texture,
    }
    var RenderTexture: {
        prototype: RenderTexture;
        new(id?: number, texture?: Texture, depth?: Texture): RenderTexture;
    }
    interface NPatchInfo {
        source: Rectangle,
        left: number,
        top: number,
        right: number,
        bottom: number,
        layout: number,
    }
    var NPatchInfo: {
        prototype: NPatchInfo;
        new(source?: Rectangle, left?: number, top?: number, right?: number, bottom?: number, layout?: number): NPatchInfo;
    }
    interface GlyphInfo {
        value: number,
        offsetX: number,
        offsetY: number,
        advanceX: number,
        image: Image,
    }
    var GlyphInfo: {
        prototype: GlyphInfo;
        new(value?: number, offsetX?: number, offsetY?: number, advanceX?: number, image?: Image): GlyphInfo;
    }
    interface Font {
        baseSize: number,
        glyphCount: number,
        glyphPadding: number,
        texture: Texture2D,
    }
    var Font: {
        prototype: Font;
        new(baseSize?: number, glyphCount?: number, glyphPadding?: number, texture?: Texture2D): Font;
    }
    interface Camera3D {
        position: Vector3,
        target: Vector3,
        up: Vector3,
        fovy: number,
        projection: number,
    }
    var Camera3D: {
        prototype: Camera3D;
        new(position?: Vector3, target?: Vector3, up?: Vector3, fovy?: number, projection?: number): Camera3D;
    }
    interface Camera2D {
        offset: Vector2,
        target: Vector2,
        rotation: number,
        zoom: number,
    }
    var Camera2D: {
        prototype: Camera2D;
        new(offset?: Vector2, target?: Vector2, rotation?: number, zoom?: number): Camera2D;
    }
    interface Mesh {
        vertexCount: number,
        triangleCount: number,
        vertices: number[],
        texcoords: number[],
        texcoords2: number[],
        normals: number[],
        tangents: number[],
        colors: number[],
        indices: number[],
        animVertices: number[],
        animNormals: number[],
        boneIds: number[],
        boneWeights: number[],
    }
    var Mesh: {
        prototype: Mesh;
        new(vertexCount?: number, triangleCount?: number, vertices?: number[], texcoords?: number[], texcoords2?: number[], normals?: number[], tangents?: number[], colors?: number[], indices?: number[], animVertices?: number[], animNormals?: number[], boneIds?: number[], boneWeights?: number[]): Mesh;
    }
    interface Shader {
        id: number,
    }
    var Shader: {
        prototype: Shader;
        new(id?: number): Shader;
    }
    interface MaterialMap {
        texture: Texture2D,
        color: Color,
        value: number,
    }
    var MaterialMap: {
        prototype: MaterialMap;
        new(texture?: Texture2D, color?: Color, value?: number): MaterialMap;
    }
    interface Material {
        shader: Shader,
        maps: MaterialMap[],
    }
    var Material: {
        prototype: Material;
        new(shader?: Shader, maps?: MaterialMap[]): Material;
    }
    interface Transform {
        translation: Vector3,
        rotation: Quaternion,
        scale: Vector3,
    }
    var Transform: {
        prototype: Transform;
        new(translation?: Vector3, rotation?: Quaternion, scale?: Vector3): Transform;
    }
    interface BoneInfo {
        name: string,
        parent: number,
    }
    var BoneInfo: {
        prototype: BoneInfo;
        new(name?: string, parent?: number): BoneInfo;
    }
    interface Model {
        transform: Matrix,
        meshCount: number,
        materialCount: number,
        meshes: Mesh[],
        materials: Material[],
        meshMaterial: number[],
        boneCount: number,
        bones: BoneInfo[],
        bindPose: Transform[],
    }
    var Model: {
        prototype: Model;
        new(transform?: Matrix, meshCount?: number, materialCount?: number, meshes?: Mesh[], materials?: Material[], meshMaterial?: number[], boneCount?: number, bones?: BoneInfo[], bindPose?: Transform[]): Model;
    }
    interface ModelAnimation {
        boneCount: number,
        frameCount: number,
        bones: BoneInfo[],
        framePoses: Transform[][],
        name: string,
    }
    var ModelAnimation: {
        prototype: ModelAnimation;
        new(boneCount?: number, frameCount?: number, bones?: BoneInfo[], framePoses?: Transform[][], name?: string): ModelAnimation;
    }
    interface Ray {
        position: Vector3,
        direction: Vector3,
    }
    var Ray: {
        prototype: Ray;
        new(position?: Vector3, direction?: Vector3): Ray;
    }
    interface RayCollision {
        hit: boolean,
        distance: number,
        point: Vector3,
        normal: Vector3,
    }
    var RayCollision: {
        prototype: RayCollision;
        new(hit?: boolean, distance?: number, point?: Vector3, normal?: Vector3): RayCollision;
    }
    interface BoundingBox {
        min: Vector3,
        max: Vector3,
    }
    var BoundingBox: {
        prototype: BoundingBox;
        new(min?: Vector3, max?: Vector3): BoundingBox;
    }
    interface Wave {
        frameCount: number,
        sampleRate: number,
        sampleSize: number,
        channels: number,
    }
    var Wave: {
        prototype: Wave;
        new(frameCount?: number, sampleRate?: number, sampleSize?: number, channels?: number): Wave;
    }
    interface rAudioBuffer {
    }
    var rAudioBuffer: {
        prototype: rAudioBuffer;
        new(): rAudioBuffer;
    }
    interface rAudioProcessor {
    }
    var rAudioProcessor: {
        prototype: rAudioProcessor;
        new(): rAudioProcessor;
    }
    interface AudioStream {
        buffer: rAudioBuffer[],
        processor: rAudioProcessor[],
        sampleRate: number,
        sampleSize: number,
        channels: number,
    }
    var AudioStream: {
        prototype: AudioStream;
        new(buffer?: rAudioBuffer[], processor?: rAudioProcessor[], sampleRate?: number, sampleSize?: number, channels?: number): AudioStream;
    }
    interface Sound {
        frameCount: number,
    }
    var Sound: {
        prototype: Sound;
        new(frameCount?: number): Sound;
    }
    interface Music {
        stream: AudioStream,
        frameCount: number,
        looping: boolean,
        ctxType: number,
    }
    var Music: {
        prototype: Music;
        new(stream?: AudioStream, frameCount?: number, looping?: boolean, ctxType?: number): Music;
    }
    interface VrDeviceInfo {
        hResolution: number,
        vResolution: number,
        hScreenSize: number,
        vScreenSize: number,
        eyeToScreenDistance: number,
        lensSeparationDistance: number,
        interpupillaryDistance: number,
        lensDistortionValues: [number,number,number,number],
        chromaAbCorrection: [number,number,number,number],
    }
    var VrDeviceInfo: {
        prototype: VrDeviceInfo;
        new(hResolution?: number, vResolution?: number, hScreenSize?: number, vScreenSize?: number, eyeToScreenDistance?: number, lensSeparationDistance?: number, interpupillaryDistance?: number, lensDistortionValues?: [number,number,number,number], chromaAbCorrection?: [number,number,number,number]): VrDeviceInfo;
    }
    interface VrStereoConfig {
        projection: [Matrix,Matrix],
        viewOffset: [Matrix,Matrix],
        leftLensCenter: [number,number],
        rightLensCenter: [number,number],
        leftScreenCenter: [number,number],
        rightScreenCenter: [number,number],
        scale: [number,number],
        scaleIn: [number,number],
    }
    var VrStereoConfig: {
        prototype: VrStereoConfig;
        new(projection?: [Matrix,Matrix], viewOffset?: [Matrix,Matrix], leftLensCenter?: [number,number], rightLensCenter?: [number,number], leftScreenCenter?: [number,number], rightScreenCenter?: [number,number], scale?: [number,number], scaleIn?: [number,number]): VrStereoConfig;
    }
    interface FilePathList {
        capacity: number,
        count: number,
        paths: string[],
    }
    var FilePathList: {
        prototype: FilePathList;
        new(capacity?: number, count?: number, paths?: string[]): FilePathList;
    }
    interface AutomationEvent {
        frame: number,
        type: number,
        params: [number,number,number,number],
    }
    var AutomationEvent: {
        prototype: AutomationEvent;
        new(frame?: number, type?: number, params?: [number,number,number,number]): AutomationEvent;
    }
    interface AutomationEventList {
        capacity: number,
        count: number,
        events: AutomationEvent[],
    }
    var AutomationEventList: {
        prototype: AutomationEventList;
        new(capacity?: number, count?: number, events?: AutomationEvent[]): AutomationEventList;
    }
    /** undefined */
    function InitWindow(width: number, height: number, title: string): void;
    /** undefined */
    function CloseWindow(): void;
    /** undefined */
    function WindowShouldClose(): boolean;
    /** undefined */
    function IsWindowReady(): boolean;
    /** undefined */
    function IsWindowFullscreen(): boolean;
    /** undefined */
    function IsWindowHidden(): boolean;
    /** undefined */
    function IsWindowMinimized(): boolean;
    /** undefined */
    function IsWindowMaximized(): boolean;
    /** undefined */
    function IsWindowFocused(): boolean;
    /** undefined */
    function IsWindowResized(): boolean;
    /** undefined */
    function IsWindowState(flag: number): boolean;
    /** undefined */
    function SetWindowState(flags: number): void;
    /** undefined */
    function ClearWindowState(flags: number): void;
    /** undefined */
    function ToggleFullscreen(): void;
    /** undefined */
    function ToggleBorderlessWindowed(): void;
    /** undefined */
    function MaximizeWindow(): void;
    /** undefined */
    function MinimizeWindow(): void;
    /** undefined */
    function RestoreWindow(): void;
    /** undefined */
    function SetWindowIcon(image: Image): void;
    /** undefined */
    function SetWindowIcons(images: Image[], count: number): void;
    /** undefined */
    function SetWindowTitle(title: string): void;
    /** undefined */
    function SetWindowPosition(x: number, y: number): void;
    /** undefined */
    function SetWindowMonitor(monitor: number): void;
    /** undefined */
    function SetWindowMinSize(width: number, height: number): void;
    /** undefined */
    function SetWindowMaxSize(width: number, height: number): void;
    /** undefined */
    function SetWindowSize(width: number, height: number): void;
    /** undefined */
    function SetWindowOpacity(opacity: number): void;
    /** undefined */
    function SetWindowFocused(): void;
    /** undefined */
    function GetScreenWidth(): number;
    /** undefined */
    function GetScreenHeight(): number;
    /** undefined */
    function GetRenderWidth(): number;
    /** undefined */
    function GetRenderHeight(): number;
    /** undefined */
    function GetMonitorCount(): number;
    /** undefined */
    function GetCurrentMonitor(): number;
    /** undefined */
    function GetMonitorPosition(monitor: number): Vector2;
    /** undefined */
    function GetMonitorWidth(monitor: number): number;
    /** undefined */
    function GetMonitorHeight(monitor: number): number;
    /** undefined */
    function GetMonitorPhysicalWidth(monitor: number): number;
    /** undefined */
    function GetMonitorPhysicalHeight(monitor: number): number;
    /** undefined */
    function GetMonitorRefreshRate(monitor: number): number;
    /** undefined */
    function GetWindowPosition(): Vector2;
    /** undefined */
    function GetWindowScaleDPI(): Vector2;
    /** undefined */
    function GetMonitorName(monitor: number): string;
    /** undefined */
    function SetClipboardText(text: string): void;
    /** undefined */
    function GetClipboardText(): string;
    /** undefined */
    function GetClipboardImage(): Image;
    /** undefined */
    function EnableEventWaiting(): void;
    /** undefined */
    function DisableEventWaiting(): void;
    /** undefined */
    function ShowCursor(): void;
    /** undefined */
    function HideCursor(): void;
    /** undefined */
    function IsCursorHidden(): boolean;
    /** undefined */
    function EnableCursor(): void;
    /** undefined */
    function DisableCursor(): void;
    /** undefined */
    function IsCursorOnScreen(): boolean;
    /** undefined */
    function ClearBackground(color: Color): void;
    /** undefined */
    function BeginDrawing(): void;
    /** undefined */
    function EndDrawing(): void;
    /** undefined */
    function BeginMode2D(camera: Camera2D): void;
    /** undefined */
    function EndMode2D(): void;
    /** undefined */
    function BeginMode3D(camera: Camera3D): void;
    /** undefined */
    function EndMode3D(): void;
    /** undefined */
    function BeginTextureMode(target: RenderTexture2D): void;
    /** undefined */
    function EndTextureMode(): void;
    /** undefined */
    function BeginShaderMode(shader: Shader): void;
    /** undefined */
    function EndShaderMode(): void;
    /** undefined */
    function BeginBlendMode(mode: number): void;
    /** undefined */
    function EndBlendMode(): void;
    /** undefined */
    function BeginScissorMode(x: number, y: number, width: number, height: number): void;
    /** undefined */
    function EndScissorMode(): void;
    /** undefined */
    function BeginVrStereoMode(config: VrStereoConfig): void;
    /** undefined */
    function EndVrStereoMode(): void;
    /** undefined */
    function LoadVrStereoConfig(device: VrDeviceInfo): VrStereoConfig;
    /** undefined */
    function UnloadVrStereoConfig(config: VrStereoConfig): void;
    /** undefined */
    function LoadShader(vsFileName: string, fsFileName: string): Shader;
    /** undefined */
    function LoadShaderFromMemory(vsCode: string, fsCode: string): Shader;
    /** undefined */
    function IsShaderValid(shader: Shader): boolean;
    /** undefined */
    function GetShaderLocation(shader: Shader, uniformName: string): number;
    /** undefined */
    function GetShaderLocationAttrib(shader: Shader, attribName: string): number;
    /** undefined */
    function SetShaderValue(shader: Shader, locIndex: number, value: void | void[], uniformType: number): void;
    /** undefined */
    function SetShaderValueV(shader: Shader, locIndex: number, values: ArrayBuffer, uniformType: number, count: number): void;
    /** undefined */
    function SetShaderValueMatrix(shader: Shader, locIndex: number, mat: Matrix): void;
    /** undefined */
    function SetShaderValueTexture(shader: Shader, locIndex: number, texture: Texture2D): void;
    /** undefined */
    function UnloadShader(shader: Shader): void;
    /** undefined */
    function GetScreenToWorldRay(position: Vector2, camera: Camera): Ray;
    /** undefined */
    function GetScreenToWorldRayEx(position: Vector2, camera: Camera, width: number, height: number): Ray;
    /** undefined */
    function GetWorldToScreen(position: Vector3, camera: Camera): Vector2;
    /** undefined */
    function GetWorldToScreenEx(position: Vector3, camera: Camera, width: number, height: number): Vector2;
    /** undefined */
    function GetWorldToScreen2D(position: Vector2, camera: Camera2D): Vector2;
    /** undefined */
    function GetScreenToWorld2D(position: Vector2, camera: Camera2D): Vector2;
    /** undefined */
    function GetCameraMatrix(camera: Camera): Matrix;
    /** undefined */
    function GetCameraMatrix2D(camera: Camera2D): Matrix;
    /** undefined */
    function SetTargetFPS(fps: number): void;
    /** undefined */
    function GetFrameTime(): number;
    /** undefined */
    function GetTime(): number;
    /** undefined */
    function GetFPS(): number;
    /** undefined */
    function SetRandomSeed(seed: number): void;
    /** undefined */
    function GetRandomValue(min: number, max: number): number;
    /** undefined */
    function LoadRandomSequence(count: number, min: number, max: number): number[];
    /** undefined */
    function UnloadRandomSequence(sequence: number | number[]): void;
    /** undefined */
    function TakeScreenshot(fileName: string): void;
    /** undefined */
    function SetConfigFlags(flags: number): void;
    /** undefined */
    function OpenURL(url: string): void;
    /** undefined */
    function TraceLog(logLevel: number, text: string): void;
    /** undefined */
    function SetTraceLogLevel(logLevel: number): void;
    /** undefined */
    function SetLoadFileDataCallback(callback: LoadFileDataCallback): void;
    /** undefined */
    function SetSaveFileDataCallback(callback: SaveFileDataCallback): void;
    /** undefined */
    function SetLoadFileTextCallback(callback: LoadFileTextCallback): void;
    /** undefined */
    function SetSaveFileTextCallback(callback: SaveFileTextCallback): void;
    /** undefined */
    function LoadFileData(fileName: string, dataSize: number | number[]): ArrayBuffer;
    /** undefined */
    function SaveFileData(fileName: string, data: ArrayBuffer, dataSize: number): boolean;
    /** undefined */
    function ExportDataAsCode(data: number[], dataSize: number, fileName: string): boolean;
    /** undefined */
    function LoadFileText(fileName: string): string;
    /** undefined */
    function SaveFileText(fileName: string, text: string): boolean;
    /** undefined */
    function FileExists(fileName: string): boolean;
    /** undefined */
    function DirectoryExists(dirPath: string): boolean;
    /** undefined */
    function IsFileExtension(fileName: string, ext: string): boolean;
    /** undefined */
    function GetFileLength(fileName: string): number;
    /** undefined */
    function GetFileExtension(fileName: string): string;
    /** undefined */
    function GetFileName(filePath: string): string;
    /** undefined */
    function GetFileNameWithoutExt(filePath: string): string;
    /** undefined */
    function GetDirectoryPath(filePath: string): string;
    /** undefined */
    function GetPrevDirectoryPath(dirPath: string): string;
    /** undefined */
    function GetWorkingDirectory(): string;
    /** undefined */
    function GetApplicationDirectory(): string;
    /** undefined */
    function MakeDirectory(dirPath: string): number;
    /** undefined */
    function ChangeDirectory(dir: string): boolean;
    /** undefined */
    function IsPathFile(path: string): boolean;
    /** undefined */
    function IsFileNameValid(fileName: string): boolean;
    /** undefined */
    function LoadDirectoryFiles(dirPath: string): string[];
    /** undefined */
    function LoadDirectoryFilesEx(basePath: string, filter: string, scanSubdirs: boolean): string[];
    /** undefined */
    function IsFileDropped(): boolean;
    /** undefined */
    function LoadDroppedFiles(): string[];
    /** undefined */
    function GetFileModTime(fileName: string): number;
    /** undefined */
    function CompressData(data: number[], dataSize: number, compDataSize: number[]): number[];
    /** undefined */
    function DecompressData(compData: number[], compDataSize: number, dataSize: number | number[]): number[];
    /** undefined */
    function EncodeDataBase64(data: number[], dataSize: number, outputSize: number[]): string;
    /** undefined */
    function DecodeDataBase64(data: number[], outputSize: number[]): number[];
    /** undefined */
    function ComputeCRC32(data: number[], dataSize: number): number;
    /** undefined */
    function ComputeMD5(data: number[], dataSize: number): number[];
    /** undefined */
    function ComputeSHA1(data: number[], dataSize: number): number[];
    /** undefined */
    function LoadAutomationEventList(fileName: string): AutomationEventList;
    /** undefined */
    function UnloadAutomationEventList(list: AutomationEventList): void;
    /** undefined */
    function ExportAutomationEventList(list: AutomationEventList, fileName: string): boolean;
    /** undefined */
    function SetAutomationEventList(list: AutomationEventList): void;
    /** undefined */
    function SetAutomationEventBaseFrame(frame: number): void;
    /** undefined */
    function StartAutomationEventRecording(): void;
    /** undefined */
    function StopAutomationEventRecording(): void;
    /** undefined */
    function PlayAutomationEvent(event: AutomationEvent): void;
    /** undefined */
    function IsKeyPressed(key: number): boolean;
    /** undefined */
    function IsKeyPressedRepeat(key: number): boolean;
    /** undefined */
    function IsKeyDown(key: number): boolean;
    /** undefined */
    function IsKeyReleased(key: number): boolean;
    /** undefined */
    function IsKeyUp(key: number): boolean;
    /** undefined */
    function GetKeyPressed(): number;
    /** undefined */
    function GetCharPressed(): number;
    /** undefined */
    function GetKeyName(key: number): string;
    /** undefined */
    function SetExitKey(key: number): void;
    /** undefined */
    function IsGamepadAvailable(gamepad: number): boolean;
    /** undefined */
    function GetGamepadName(gamepad: number): string;
    /** undefined */
    function IsGamepadButtonPressed(gamepad: number, button: number): boolean;
    /** undefined */
    function IsGamepadButtonDown(gamepad: number, button: number): boolean;
    /** undefined */
    function IsGamepadButtonReleased(gamepad: number, button: number): boolean;
    /** undefined */
    function IsGamepadButtonUp(gamepad: number, button: number): boolean;
    /** undefined */
    function GetGamepadButtonPressed(): number;
    /** undefined */
    function GetGamepadAxisCount(gamepad: number): number;
    /** undefined */
    function GetGamepadAxisMovement(gamepad: number, axis: number): number;
    /** undefined */
    function SetGamepadMappings(mappings: string): number;
    /** undefined */
    function SetGamepadVibration(gamepad: number, leftMotor: number, rightMotor: number, duration: number): void;
    /** undefined */
    function IsMouseButtonPressed(button: number): boolean;
    /** undefined */
    function IsMouseButtonDown(button: number): boolean;
    /** undefined */
    function IsMouseButtonReleased(button: number): boolean;
    /** undefined */
    function IsMouseButtonUp(button: number): boolean;
    /** undefined */
    function GetMouseX(): number;
    /** undefined */
    function GetMouseY(): number;
    /** undefined */
    function GetMousePosition(): Vector2;
    /** undefined */
    function GetMouseDelta(): Vector2;
    /** undefined */
    function SetMousePosition(x: number, y: number): void;
    /** undefined */
    function SetMouseOffset(offsetX: number, offsetY: number): void;
    /** undefined */
    function SetMouseScale(scaleX: number, scaleY: number): void;
    /** undefined */
    function GetMouseWheelMove(): number;
    /** undefined */
    function GetMouseWheelMoveV(): Vector2;
    /** undefined */
    function SetMouseCursor(cursor: number): void;
    /** undefined */
    function GetTouchX(): number;
    /** undefined */
    function GetTouchY(): number;
    /** undefined */
    function GetTouchPosition(index: number): Vector2;
    /** undefined */
    function GetTouchPointId(index: number): number;
    /** undefined */
    function GetTouchPointCount(): number;
    /** undefined */
    function SetGesturesEnabled(flags: number): void;
    /** undefined */
    function IsGestureDetected(gesture: number): boolean;
    /** undefined */
    function GetGestureDetected(): number;
    /** undefined */
    function GetGestureHoldDuration(): number;
    /** undefined */
    function GetGestureDragVector(): Vector2;
    /** undefined */
    function GetGestureDragAngle(): number;
    /** undefined */
    function GetGesturePinchVector(): Vector2;
    /** undefined */
    function GetGesturePinchAngle(): number;
    /** undefined */
    function UpdateCamera(camera: Camera, mode: number): void;
    /** undefined */
    function UpdateCameraPro(camera: Camera, movement: Vector3, rotation: Vector3, zoom: number): void;
    /** undefined */
    function SetShapesTexture(texture: Texture2D, source: Rectangle): void;
    /** undefined */
    function GetShapesTexture(): Texture2D;
    /** undefined */
    function GetShapesTextureRectangle(): Rectangle;
    /** undefined */
    function DrawPixel(posX: number, posY: number, color: Color): void;
    /** undefined */
    function DrawPixelV(position: Vector2, color: Color): void;
    /** undefined */
    function DrawLine(startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void;
    /** undefined */
    function DrawLineV(startPos: Vector2, endPos: Vector2, color: Color): void;
    /** undefined */
    function DrawLineEx(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void;
    /** undefined */
    function DrawLineStrip(points: Vector2[], pointCount: number, color: Color): void;
    /** undefined */
    function DrawLineBezier(startPos: Vector2, endPos: Vector2, thick: number, color: Color): void;
    /** undefined */
    function DrawCircle(centerX: number, centerY: number, radius: number, color: Color): void;
    /** undefined */
    function DrawCircleSector(center: Vector2, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
    /** undefined */
    function DrawCircleSectorLines(center: Vector2, radius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
    /** undefined */
    function DrawCircleGradient(centerX: number, centerY: number, radius: number, inner: Color, outer: Color): void;
    /** undefined */
    function DrawCircleV(center: Vector2, radius: number, color: Color): void;
    /** undefined */
    function DrawCircleLines(centerX: number, centerY: number, radius: number, color: Color): void;
    /** undefined */
    function DrawCircleLinesV(center: Vector2, radius: number, color: Color): void;
    /** undefined */
    function DrawEllipse(centerX: number, centerY: number, radiusH: number, radiusV: number, color: Color): void;
    /** undefined */
    function DrawEllipseLines(centerX: number, centerY: number, radiusH: number, radiusV: number, color: Color): void;
    /** undefined */
    function DrawRing(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
    /** undefined */
    function DrawRingLines(center: Vector2, innerRadius: number, outerRadius: number, startAngle: number, endAngle: number, segments: number, color: Color): void;
    /** undefined */
    function DrawRectangle(posX: number, posY: number, width: number, height: number, color: Color): void;
    /** undefined */
    function DrawRectangleV(position: Vector2, size: Vector2, color: Color): void;
    /** undefined */
    function DrawRectangleRec(rec: Rectangle, color: Color): void;
    /** undefined */
    function DrawRectanglePro(rec: Rectangle, origin: Vector2, rotation: number, color: Color): void;
    /** undefined */
    function DrawRectangleGradientV(posX: number, posY: number, width: number, height: number, top: Color, bottom: Color): void;
    /** undefined */
    function DrawRectangleGradientH(posX: number, posY: number, width: number, height: number, left: Color, right: Color): void;
    /** undefined */
    function DrawRectangleGradientEx(rec: Rectangle, topLeft: Color, bottomLeft: Color, topRight: Color, bottomRight: Color): void;
    /** undefined */
    function DrawRectangleLines(posX: number, posY: number, width: number, height: number, color: Color): void;
    /** undefined */
    function DrawRectangleLinesEx(rec: Rectangle, lineThick: number, color: Color): void;
    /** undefined */
    function DrawRectangleRounded(rec: Rectangle, roundness: number, segments: number, color: Color): void;
    /** undefined */
    function DrawRectangleRoundedLines(rec: Rectangle, roundness: number, segments: number, color: Color): void;
    /** undefined */
    function DrawRectangleRoundedLinesEx(rec: Rectangle, roundness: number, segments: number, lineThick: number, color: Color): void;
    /** undefined */
    function DrawTriangle(v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
    /** undefined */
    function DrawTriangleLines(v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
    /** undefined */
    function DrawTriangleFan(points: Vector2[], pointCount: number, color: Color): void;
    /** undefined */
    function DrawTriangleStrip(points: Vector2[], pointCount: number, color: Color): void;
    /** undefined */
    function DrawPoly(center: Vector2, sides: number, radius: number, rotation: number, color: Color): void;
    /** undefined */
    function DrawPolyLines(center: Vector2, sides: number, radius: number, rotation: number, color: Color): void;
    /** undefined */
    function DrawPolyLinesEx(center: Vector2, sides: number, radius: number, rotation: number, lineThick: number, color: Color): void;
    /** undefined */
    function DrawSplineLinear(points: Vector2[], pointCount: number, thick: number, color: Color): void;
    /** undefined */
    function DrawSplineBasis(points: Vector2[], pointCount: number, thick: number, color: Color): void;
    /** undefined */
    function DrawSplineCatmullRom(points: Vector2[], pointCount: number, thick: number, color: Color): void;
    /** undefined */
    function DrawSplineBezierQuadratic(points: Vector2[], pointCount: number, thick: number, color: Color): void;
    /** undefined */
    function DrawSplineBezierCubic(points: Vector2[], pointCount: number, thick: number, color: Color): void;
    /** undefined */
    function DrawSplineSegmentLinear(p1: Vector2, p2: Vector2, thick: number, color: Color): void;
    /** undefined */
    function DrawSplineSegmentBasis(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, thick: number, color: Color): void;
    /** undefined */
    function DrawSplineSegmentCatmullRom(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, thick: number, color: Color): void;
    /** undefined */
    function DrawSplineSegmentBezierQuadratic(p1: Vector2, c2: Vector2, p3: Vector2, thick: number, color: Color): void;
    /** undefined */
    function DrawSplineSegmentBezierCubic(p1: Vector2, c2: Vector2, c3: Vector2, p4: Vector2, thick: number, color: Color): void;
    /** undefined */
    function GetSplinePointLinear(startPos: Vector2, endPos: Vector2, t: number): Vector2;
    /** undefined */
    function GetSplinePointBasis(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, t: number): Vector2;
    /** undefined */
    function GetSplinePointCatmullRom(p1: Vector2, p2: Vector2, p3: Vector2, p4: Vector2, t: number): Vector2;
    /** undefined */
    function GetSplinePointBezierQuad(p1: Vector2, c2: Vector2, p3: Vector2, t: number): Vector2;
    /** undefined */
    function GetSplinePointBezierCubic(p1: Vector2, c2: Vector2, c3: Vector2, p4: Vector2, t: number): Vector2;
    /** undefined */
    function CheckCollisionRecs(rec1: Rectangle, rec2: Rectangle): boolean;
    /** undefined */
    function CheckCollisionCircles(center1: Vector2, radius1: number, center2: Vector2, radius2: number): boolean;
    /** undefined */
    function CheckCollisionCircleRec(center: Vector2, radius: number, rec: Rectangle): boolean;
    /** undefined */
    function CheckCollisionCircleLine(center: Vector2, radius: number, p1: Vector2, p2: Vector2): boolean;
    /** undefined */
    function CheckCollisionPointRec(point: Vector2, rec: Rectangle): boolean;
    /** undefined */
    function CheckCollisionPointCircle(point: Vector2, center: Vector2, radius: number): boolean;
    /** undefined */
    function CheckCollisionPointTriangle(point: Vector2, p1: Vector2, p2: Vector2, p3: Vector2): boolean;
    /** undefined */
    function CheckCollisionPointLine(point: Vector2, p1: Vector2, p2: Vector2, threshold: number): boolean;
    /** undefined */
    function CheckCollisionPointPoly(point: Vector2, points: Vector2[], pointCount: number): boolean;
    /** undefined */
    function CheckCollisionLines(startPos1: Vector2, endPos1: Vector2, startPos2: Vector2, endPos2: Vector2, collisionPoint: Vector2): boolean;
    /** undefined */
    function GetCollisionRec(rec1: Rectangle, rec2: Rectangle): Rectangle;
    /** undefined */
    function LoadImage(fileName: string): Image;
    /** undefined */
    function LoadImageRaw(fileName: string, width: number, height: number, format: number, headerSize: number): Image;
    /** undefined */
    function LoadImageAnim(fileName: string, frames: number | number[]): Image;
    /** undefined */
    function LoadImageAnimFromMemory(fileType: string, fileData: number[], dataSize: number, frames: number | number[]): Image;
    /** undefined */
    function LoadImageFromMemory(fileType: string, fileData: number[], dataSize: number): Image;
    /** undefined */
    function LoadImageFromTexture(texture: Texture2D): Image;
    /** undefined */
    function LoadImageFromScreen(): Image;
    /** undefined */
    function IsImageValid(image: Image): boolean;
    /** undefined */
    function UnloadImage(image: Image): void;
    /** undefined */
    function ExportImage(image: Image, fileName: string): boolean;
    /** undefined */
    function ExportImageToMemory(image: Image, fileType: string, fileSize: number | number[]): number[];
    /** undefined */
    function ExportImageAsCode(image: Image, fileName: string): boolean;
    /** undefined */
    function GenImageColor(width: number, height: number, color: Color): Image;
    /** undefined */
    function GenImageGradientLinear(width: number, height: number, direction: number, start: Color, end: Color): Image;
    /** undefined */
    function GenImageGradientRadial(width: number, height: number, density: number, inner: Color, outer: Color): Image;
    /** undefined */
    function GenImageGradientSquare(width: number, height: number, density: number, inner: Color, outer: Color): Image;
    /** undefined */
    function GenImageChecked(width: number, height: number, checksX: number, checksY: number, col1: Color, col2: Color): Image;
    /** undefined */
    function GenImageWhiteNoise(width: number, height: number, factor: number): Image;
    /** undefined */
    function GenImagePerlinNoise(width: number, height: number, offsetX: number, offsetY: number, scale: number): Image;
    /** undefined */
    function GenImageCellular(width: number, height: number, tileSize: number): Image;
    /** undefined */
    function GenImageText(width: number, height: number, text: string): Image;
    /** undefined */
    function ImageCopy(image: Image): Image;
    /** undefined */
    function ImageFromImage(image: Image, rec: Rectangle): Image;
    /** undefined */
    function ImageFromChannel(image: Image, selectedChannel: number): Image;
    /** undefined */
    function ImageText(text: string, fontSize: number, color: Color): Image;
    /** undefined */
    function ImageTextEx(font: Font, text: string, fontSize: number, spacing: number, tint: Color): Image;
    /** undefined */
    function ImageFormat(image: Image, newFormat: number): void;
    /** undefined */
    function ImageToPOT(image: Image, fill: Color): void;
    /** undefined */
    function ImageCrop(image: Image, crop: Rectangle): void;
    /** undefined */
    function ImageAlphaCrop(image: Image, threshold: number): void;
    /** undefined */
    function ImageAlphaClear(image: Image, color: Color, threshold: number): void;
    /** undefined */
    function ImageAlphaMask(image: Image, alphaMask: Image): void;
    /** undefined */
    function ImageAlphaPremultiply(image: Image): void;
    /** undefined */
    function ImageBlurGaussian(image: Image, blurSize: number): void;
    /** undefined */
    function ImageKernelConvolution(image: Image, kernel: number[], kernelSize: number): void;
    /** undefined */
    function ImageResize(image: Image, newWidth: number, newHeight: number): void;
    /** undefined */
    function ImageResizeNN(image: Image, newWidth: number, newHeight: number): void;
    /** undefined */
    function ImageResizeCanvas(image: Image, newWidth: number, newHeight: number, offsetX: number, offsetY: number, fill: Color): void;
    /** undefined */
    function ImageMipmaps(image: Image): void;
    /** undefined */
    function ImageDither(image: Image, rBpp: number, gBpp: number, bBpp: number, aBpp: number): void;
    /** undefined */
    function ImageFlipVertical(image: Image): void;
    /** undefined */
    function ImageFlipHorizontal(image: Image): void;
    /** undefined */
    function ImageRotate(image: Image, degrees: number): void;
    /** undefined */
    function ImageRotateCW(image: Image): void;
    /** undefined */
    function ImageRotateCCW(image: Image): void;
    /** undefined */
    function ImageColorTint(image: Image, color: Color): void;
    /** undefined */
    function ImageColorInvert(image: Image): void;
    /** undefined */
    function ImageColorGrayscale(image: Image): void;
    /** undefined */
    function ImageColorContrast(image: Image, contrast: number): void;
    /** undefined */
    function ImageColorBrightness(image: Image, brightness: number): void;
    /** undefined */
    function ImageColorReplace(image: Image, color: Color, replace: Color): void;
    /** undefined */
    function LoadImageColors(image: Image): ArrayBuffer;
    /** undefined */
    function LoadImagePalette(image: Image, maxPaletteSize: number, colorCount: number[]): Color[];
    /** undefined */
    function UnloadImageColors(colors: Color): void;
    /** undefined */
    function UnloadImagePalette(colors: Color): void;
    /** undefined */
    function GetImageAlphaBorder(image: Image, threshold: number): Rectangle;
    /** undefined */
    function GetImageColor(image: Image, x: number, y: number): Color;
    /** undefined */
    function ImageClearBackground(dst: Image, color: Color): void;
    /** undefined */
    function ImageDrawPixel(dst: Image, posX: number, posY: number, color: Color): void;
    /** undefined */
    function ImageDrawPixelV(dst: Image, position: Vector2, color: Color): void;
    /** undefined */
    function ImageDrawLine(dst: Image, startPosX: number, startPosY: number, endPosX: number, endPosY: number, color: Color): void;
    /** undefined */
    function ImageDrawLineV(dst: Image, start: Vector2, end: Vector2, color: Color): void;
    /** undefined */
    function ImageDrawLineEx(dst: Image, start: Vector2, end: Vector2, thick: number, color: Color): void;
    /** undefined */
    function ImageDrawCircle(dst: Image, centerX: number, centerY: number, radius: number, color: Color): void;
    /** undefined */
    function ImageDrawCircleV(dst: Image, center: Vector2, radius: number, color: Color): void;
    /** undefined */
    function ImageDrawCircleLines(dst: Image, centerX: number, centerY: number, radius: number, color: Color): void;
    /** undefined */
    function ImageDrawCircleLinesV(dst: Image, center: Vector2, radius: number, color: Color): void;
    /** undefined */
    function ImageDrawRectangle(dst: Image, posX: number, posY: number, width: number, height: number, color: Color): void;
    /** undefined */
    function ImageDrawRectangleV(dst: Image, position: Vector2, size: Vector2, color: Color): void;
    /** undefined */
    function ImageDrawRectangleRec(dst: Image, rec: Rectangle, color: Color): void;
    /** undefined */
    function ImageDrawRectangleLines(dst: Image, rec: Rectangle, thick: number, color: Color): void;
    /** undefined */
    function ImageDrawTriangle(dst: Image, v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
    /** undefined */
    function ImageDrawTriangleEx(dst: Image, v1: Vector2, v2: Vector2, v3: Vector2, c1: Color, c2: Color, c3: Color): void;
    /** undefined */
    function ImageDrawTriangleLines(dst: Image, v1: Vector2, v2: Vector2, v3: Vector2, color: Color): void;
    /** undefined */
    function ImageDrawTriangleFan(dst: Image, points: Vector2[], pointCount: number, color: Color): void;
    /** undefined */
    function ImageDrawTriangleStrip(dst: Image, points: Vector2[], pointCount: number, color: Color): void;
    /** undefined */
    function ImageDraw(dst: Image, src: Image, srcRec: Rectangle, dstRec: Rectangle, tint: Color): void;
    /** undefined */
    function ImageDrawText(dst: Image, text: string, posX: number, posY: number, fontSize: number, color: Color): void;
    /** undefined */
    function ImageDrawTextEx(dst: Image, font: Font, text: string, position: Vector2, fontSize: number, spacing: number, tint: Color): void;
    /** undefined */
    function LoadTexture(fileName: string): Texture2D;
    /** undefined */
    function LoadTextureFromImage(image: Image): Texture2D;
    /** undefined */
    function LoadTextureCubemap(image: Image, layout: number): TextureCubemap;
    /** undefined */
    function LoadRenderTexture(width: number, height: number): RenderTexture2D;
    /** undefined */
    function IsTextureValid(texture: Texture2D): boolean;
    /** undefined */
    function UnloadTexture(texture: Texture2D): void;
    /** undefined */
    function IsRenderTextureValid(target: RenderTexture2D): boolean;
    /** undefined */
    function UnloadRenderTexture(target: RenderTexture2D): void;
    /** undefined */
    function UpdateTexture(texture: Texture2D, pixels: ArrayBuffer): void;
    /** undefined */
    function UpdateTextureRec(texture: Texture2D, rec: Rectangle, pixels: ArrayBuffer): void;
    /** undefined */
    function GenTextureMipmaps(texture: Texture2D): void;
    /** undefined */
    function SetTextureFilter(texture: Texture2D, filter: number): void;
    /** undefined */
    function SetTextureWrap(texture: Texture2D, wrap: number): void;
    /** undefined */
    function DrawTexture(texture: Texture2D, posX: number, posY: number, tint: Color): void;
    /** undefined */
    function DrawTextureV(texture: Texture2D, position: Vector2, tint: Color): void;
    /** undefined */
    function DrawTextureEx(texture: Texture2D, position: Vector2, rotation: number, scale: number, tint: Color): void;
    /** undefined */
    function DrawTextureRec(texture: Texture2D, source: Rectangle, position: Vector2, tint: Color): void;
    /** undefined */
    function DrawTexturePro(texture: Texture2D, source: Rectangle, dest: Rectangle, origin: Vector2, rotation: number, tint: Color): void;
    /** undefined */
    function DrawTextureNPatch(texture: Texture2D, nPatchInfo: NPatchInfo, dest: Rectangle, origin: Vector2, rotation: number, tint: Color): void;
    /** undefined */
    function ColorIsEqual(col1: Color, col2: Color): boolean;
    /** undefined */
    function Fade(color: Color, alpha: number): Color;
    /** undefined */
    function ColorToInt(color: Color): number;
    /** undefined */
    function ColorNormalize(color: Color): Vector4;
    /** undefined */
    function ColorFromNormalized(normalized: Vector4): Color;
    /** undefined */
    function ColorToHSV(color: Color): Vector3;
    /** undefined */
    function ColorFromHSV(hue: number, saturation: number, value: number): Color;
    /** undefined */
    function ColorTint(color: Color, tint: Color): Color;
    /** undefined */
    function ColorBrightness(color: Color, factor: number): Color;
    /** undefined */
    function ColorContrast(color: Color, contrast: number): Color;
    /** undefined */
    function ColorAlpha(color: Color, alpha: number): Color;
    /** undefined */
    function ColorAlphaBlend(dst: Color, src: Color, tint: Color): Color;
    /** undefined */
    function ColorLerp(color1: Color, color2: Color, factor: number): Color;
    /** undefined */
    function GetColor(hexValue: number): Color;
    /** undefined */
    function GetPixelColor(srcPtr: ArrayBuffer, format: number): Color;
    /** undefined */
    function SetPixelColor(dstPtr: ArrayBuffer, color: Color, format: number): void;
    /** undefined */
    function GetPixelDataSize(width: number, height: number, format: number): number;
    /** undefined */
    function GetFontDefault(): Font;
    /** undefined */
    function LoadFont(fileName: string): Font;
    /** undefined */
    function LoadFontEx(fileName: string, fontSize: number, codepoints: number[], codepointCount: number): Font;
    /** undefined */
    function LoadFontFromImage(image: Image, key: Color, firstChar: number): Font;
    /** undefined */
    function LoadFontFromMemory(fileType: string, fileData: number[], dataSize: number, fontSize: number, codepoints: number[], codepointCount: number): Font;
    /** undefined */
    function IsFontValid(font: Font): boolean;
    /** undefined */
    function LoadFontData(fileData: number[], dataSize: number, fontSize: number, codepoints: number[], codepointCount: number, type: number): GlyphInfo[];
    /** undefined */
    function GenImageFontAtlas(glyphs: GlyphInfo[], glyphRecs: Rectangle[][], glyphCount: number, fontSize: number, padding: number, packMethod: number): Image;
    /** undefined */
    function UnloadFontData(glyphs: GlyphInfo[], glyphCount: number): void;
    /** undefined */
    function UnloadFont(font: Font): void;
    /** undefined */
    function ExportFontAsCode(font: Font, fileName: string): boolean;
    /** undefined */
    function DrawFPS(posX: number, posY: number): void;
    /** undefined */
    function DrawText(text: string, posX: number, posY: number, fontSize: number, color: Color): void;
    /** undefined */
    function DrawTextEx(font: Font, text: string, position: Vector2, fontSize: number, spacing: number, tint: Color): void;
    /** undefined */
    function DrawTextPro(font: Font, text: string, position: Vector2, origin: Vector2, rotation: number, fontSize: number, spacing: number, tint: Color): void;
    /** undefined */
    function DrawTextCodepoint(font: Font, codepoint: number, position: Vector2, fontSize: number, tint: Color): void;
    /** undefined */
    function DrawTextCodepoints(font: Font, codepoints: number[], codepointCount: number, position: Vector2, fontSize: number, spacing: number, tint: Color): void;
    /** undefined */
    function SetTextLineSpacing(spacing: number): void;
    /** undefined */
    function MeasureText(text: string, fontSize: number): number;
    /** undefined */
    function MeasureTextEx(font: Font, text: string, fontSize: number, spacing: number): Vector2;
    /** undefined */
    function GetGlyphIndex(font: Font, codepoint: number): number;
    /** undefined */
    function GetGlyphInfo(font: Font, codepoint: number): GlyphInfo;
    /** undefined */
    function GetGlyphAtlasRec(font: Font, codepoint: number): Rectangle;
    /** undefined */
    function LoadUTF8(codepoints: number[], length: number): string;
    /** undefined */
    function UnloadUTF8(text: string): void;
    /** undefined */
    function LoadCodepoints(text: string, count: number | number[]): number[];
    /** undefined */
    function UnloadCodepoints(codepoints: number | number[]): void;
    /** undefined */
    function GetCodepointCount(text: string): number;
    /** undefined */
    function GetCodepoint(text: string, codepointSize: number[]): number;
    /** undefined */
    function GetCodepointNext(text: string, codepointSize: number[]): number;
    /** undefined */
    function GetCodepointPrevious(text: string, codepointSize: number[]): number;
    /** undefined */
    function CodepointToUTF8(codepoint: number, utf8Size: number[]): string;
    /** undefined */
    function TextIsEqual(text1: string, text2: string): boolean;
    /** undefined */
    function TextLength(text: string): number;
    /** undefined */
    function TextFormat(text: string, ...args: any): string;
    /** undefined */
    function TextSubtext(text: string, position: number, length: number): string;
    /** undefined */
    function TextReplace(text: string, replace: string, by: string): string;
    /** undefined */
    function TextInsert(text: string, insert: string, position: number): string;
    /** undefined */
    function TextJoin(textList: string[], count: number, delimiter: string): string;
    /** undefined */
    function TextSplit(text: string, delimiter: string, count: number | number[]): string[];
    /** undefined */
    function TextAppend(text: string, append: string, position: number | number[]): void;
    /** undefined */
    function TextFindIndex(text: string, find: string): number;
    /** undefined */
    function TextToUpper(text: string): string;
    /** undefined */
    function TextToLower(text: string): string;
    /** undefined */
    function TextToPascal(text: string): string;
    /** undefined */
    function TextToSnake(text: string): string;
    /** undefined */
    function TextToCamel(text: string): string;
    /** undefined */
    function TextToInteger(text: string): number;
    /** undefined */
    function TextToFloat(text: string): number;
    /** undefined */
    function DrawLine3D(startPos: Vector3, endPos: Vector3, color: Color): void;
    /** undefined */
    function DrawPoint3D(position: Vector3, color: Color): void;
    /** undefined */
    function DrawCircle3D(center: Vector3, radius: number, rotationAxis: Vector3, rotationAngle: number, color: Color): void;
    /** undefined */
    function DrawTriangle3D(v1: Vector3, v2: Vector3, v3: Vector3, color: Color): void;
    /** undefined */
    function DrawTriangleStrip3D(points: Vector3[], pointCount: number, color: Color): void;
    /** undefined */
    function DrawCube(position: Vector3, width: number, height: number, length: number, color: Color): void;
    /** undefined */
    function DrawCubeV(position: Vector3, size: Vector3, color: Color): void;
    /** undefined */
    function DrawCubeWires(position: Vector3, width: number, height: number, length: number, color: Color): void;
    /** undefined */
    function DrawCubeWiresV(position: Vector3, size: Vector3, color: Color): void;
    /** undefined */
    function DrawSphere(centerPos: Vector3, radius: number, color: Color): void;
    /** undefined */
    function DrawSphereEx(centerPos: Vector3, radius: number, rings: number, slices: number, color: Color): void;
    /** undefined */
    function DrawSphereWires(centerPos: Vector3, radius: number, rings: number, slices: number, color: Color): void;
    /** undefined */
    function DrawCylinder(position: Vector3, radiusTop: number, radiusBottom: number, height: number, slices: number, color: Color): void;
    /** undefined */
    function DrawCylinderEx(startPos: Vector3, endPos: Vector3, startRadius: number, endRadius: number, sides: number, color: Color): void;
    /** undefined */
    function DrawCylinderWires(position: Vector3, radiusTop: number, radiusBottom: number, height: number, slices: number, color: Color): void;
    /** undefined */
    function DrawCylinderWiresEx(startPos: Vector3, endPos: Vector3, startRadius: number, endRadius: number, sides: number, color: Color): void;
    /** undefined */
    function DrawCapsule(startPos: Vector3, endPos: Vector3, radius: number, slices: number, rings: number, color: Color): void;
    /** undefined */
    function DrawCapsuleWires(startPos: Vector3, endPos: Vector3, radius: number, slices: number, rings: number, color: Color): void;
    /** undefined */
    function DrawPlane(centerPos: Vector3, size: Vector2, color: Color): void;
    /** undefined */
    function DrawRay(ray: Ray, color: Color): void;
    /** undefined */
    function DrawGrid(slices: number, spacing: number): void;
    /** undefined */
    function LoadModel(fileName: string): Model;
    /** undefined */
    function LoadModelFromMesh(mesh: Mesh): Model;
    /** undefined */
    function IsModelValid(model: Model): boolean;
    /** undefined */
    function UnloadModel(model: Model): void;
    /** undefined */
    function GetModelBoundingBox(model: Model): BoundingBox;
    /** undefined */
    function DrawModel(model: Model, position: Vector3, scale: number, tint: Color): void;
    /** undefined */
    function DrawModelEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
    /** undefined */
    function DrawModelWires(model: Model, position: Vector3, scale: number, tint: Color): void;
    /** undefined */
    function DrawModelWiresEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
    /** undefined */
    function DrawModelPoints(model: Model, position: Vector3, scale: number, tint: Color): void;
    /** undefined */
    function DrawModelPointsEx(model: Model, position: Vector3, rotationAxis: Vector3, rotationAngle: number, scale: Vector3, tint: Color): void;
    /** undefined */
    function DrawBoundingBox(box: BoundingBox, color: Color): void;
    /** undefined */
    function DrawBillboard(camera: Camera, texture: Texture2D, position: Vector3, scale: number, tint: Color): void;
    /** undefined */
    function DrawBillboardRec(camera: Camera, texture: Texture2D, source: Rectangle, position: Vector3, size: Vector2, tint: Color): void;
    /** undefined */
    function DrawBillboardPro(camera: Camera, texture: Texture2D, source: Rectangle, position: Vector3, up: Vector3, size: Vector2, origin: Vector2, rotation: number, tint: Color): void;
    /** undefined */
    function UploadMesh(mesh: Mesh, dynamic: boolean): void;
    /** undefined */
    function UpdateMeshBuffer(mesh: Mesh, index: number, data: ArrayBuffer, dataSize: number, offset: number): void;
    /** undefined */
    function UnloadMesh(mesh: Mesh): void;
    /** undefined */
    function DrawMesh(mesh: Mesh, material: Material, transform: Matrix): void;
    /** undefined */
    function DrawMeshInstanced(mesh: Mesh, material: Material, transforms: Matrix[], instances: number): void;
    /** undefined */
    function GetMeshBoundingBox(mesh: Mesh): BoundingBox;
    /** undefined */
    function GenMeshTangents(mesh: Mesh): void;
    /** undefined */
    function ExportMesh(mesh: Mesh, fileName: string): boolean;
    /** undefined */
    function ExportMeshAsCode(mesh: Mesh, fileName: string): boolean;
    /** undefined */
    function GenMeshPoly(sides: number, radius: number): Mesh;
    /** undefined */
    function GenMeshPlane(width: number, length: number, resX: number, resZ: number): Mesh;
    /** undefined */
    function GenMeshCube(width: number, height: number, length: number): Mesh;
    /** undefined */
    function GenMeshSphere(radius: number, rings: number, slices: number): Mesh;
    /** undefined */
    function GenMeshHemiSphere(radius: number, rings: number, slices: number): Mesh;
    /** undefined */
    function GenMeshCylinder(radius: number, height: number, slices: number): Mesh;
    /** undefined */
    function GenMeshCone(radius: number, height: number, slices: number): Mesh;
    /** undefined */
    function GenMeshTorus(radius: number, size: number, radSeg: number, sides: number): Mesh;
    /** undefined */
    function GenMeshKnot(radius: number, size: number, radSeg: number, sides: number): Mesh;
    /** undefined */
    function GenMeshHeightmap(heightmap: Image, size: Vector3): Mesh;
    /** undefined */
    function GenMeshCubicmap(cubicmap: Image, cubeSize: Vector3): Mesh;
    /** undefined */
    function LoadMaterials(fileName: string, materialCount: number[]): Material[];
    /** undefined */
    function LoadMaterialDefault(): Material;
    /** undefined */
    function IsMaterialValid(material: Material): boolean;
    /** undefined */
    function UnloadMaterial(material: Material): void;
    /** undefined */
    function SetMaterialTexture(material: Material, mapType: number, texture: Texture2D): void;
    /** undefined */
    function SetModelMeshMaterial(model: Model, meshId: number, materialId: number): void;
    /** undefined */
    function LoadModelAnimations(fileName: string, animCount: number[]): ModelAnimation[];
    /** undefined */
    function UpdateModelAnimation(model: Model, anim: ModelAnimation, frame: number): void;
    /** undefined */
    function UpdateModelAnimationBones(model: Model, anim: ModelAnimation, frame: number): void;
    /** undefined */
    function UnloadModelAnimation(anim: ModelAnimation): void;
    /** undefined */
    function UnloadModelAnimations(animations: ModelAnimation[], animCount: number): void;
    /** undefined */
    function IsModelAnimationValid(model: Model, anim: ModelAnimation): boolean;
    /** undefined */
    function CheckCollisionSpheres(center1: Vector3, radius1: number, center2: Vector3, radius2: number): boolean;
    /** undefined */
    function CheckCollisionBoxes(box1: BoundingBox, box2: BoundingBox): boolean;
    /** undefined */
    function CheckCollisionBoxSphere(box: BoundingBox, center: Vector3, radius: number): boolean;
    /** undefined */
    function GetRayCollisionSphere(ray: Ray, center: Vector3, radius: number): RayCollision;
    /** undefined */
    function GetRayCollisionBox(ray: Ray, box: BoundingBox): RayCollision;
    /** undefined */
    function GetRayCollisionMesh(ray: Ray, mesh: Mesh, transform: Matrix): RayCollision;
    /** undefined */
    function GetRayCollisionTriangle(ray: Ray, p1: Vector3, p2: Vector3, p3: Vector3): RayCollision;
    /** undefined */
    function GetRayCollisionQuad(ray: Ray, p1: Vector3, p2: Vector3, p3: Vector3, p4: Vector3): RayCollision;
    /** undefined */
    function InitAudioDevice(): void;
    /** undefined */
    function CloseAudioDevice(): void;
    /** undefined */
    function IsAudioDeviceReady(): boolean;
    /** undefined */
    function SetMasterVolume(volume: number): void;
    /** undefined */
    function GetMasterVolume(): number;
    /** undefined */
    function LoadWave(fileName: string): Wave;
    /** undefined */
    function LoadWaveFromMemory(fileType: string, fileData: number[], dataSize: number): Wave;
    /** undefined */
    function IsWaveValid(wave: Wave): boolean;
    /** undefined */
    function LoadSound(fileName: string): Sound;
    /** undefined */
    function LoadSoundFromWave(wave: Wave): Sound;
    /** undefined */
    function LoadSoundAlias(source: Sound): Sound;
    /** undefined */
    function IsSoundValid(sound: Sound): boolean;
    /** undefined */
    function UpdateSound(sound: Sound, data: ArrayBuffer, sampleCount: number): void;
    /** undefined */
    function UnloadWave(wave: Wave): void;
    /** undefined */
    function UnloadSound(sound: Sound): void;
    /** undefined */
    function UnloadSoundAlias(alias: Sound): void;
    /** undefined */
    function ExportWave(wave: Wave, fileName: string): boolean;
    /** undefined */
    function ExportWaveAsCode(wave: Wave, fileName: string): boolean;
    /** undefined */
    function PlaySound(sound: Sound): void;
    /** undefined */
    function StopSound(sound: Sound): void;
    /** undefined */
    function PauseSound(sound: Sound): void;
    /** undefined */
    function ResumeSound(sound: Sound): void;
    /** undefined */
    function IsSoundPlaying(sound: Sound): boolean;
    /** undefined */
    function SetSoundVolume(sound: Sound, volume: number): void;
    /** undefined */
    function SetSoundPitch(sound: Sound, pitch: number): void;
    /** undefined */
    function SetSoundPan(sound: Sound, pan: number): void;
    /** undefined */
    function WaveCopy(wave: Wave): Wave;
    /** undefined */
    function WaveCrop(wave: Wave, initFrame: number, finalFrame: number): void;
    /** undefined */
    function WaveFormat(wave: Wave, sampleRate: number, sampleSize: number, channels: number): void;
    /** undefined */
    function LoadWaveSamples(wave: Wave): number[];
    /** undefined */
    function UnloadWaveSamples(samples: number | number[]): void;
    /** undefined */
    function LoadMusicStream(fileName: string): Music;
    /** undefined */
    function LoadMusicStreamFromMemory(fileType: string, data: number[], dataSize: number): Music;
    /** undefined */
    function IsMusicValid(music: Music): boolean;
    /** undefined */
    function UnloadMusicStream(music: Music): void;
    /** undefined */
    function PlayMusicStream(music: Music): void;
    /** undefined */
    function IsMusicStreamPlaying(music: Music): boolean;
    /** undefined */
    function UpdateMusicStream(music: Music): void;
    /** undefined */
    function StopMusicStream(music: Music): void;
    /** undefined */
    function PauseMusicStream(music: Music): void;
    /** undefined */
    function ResumeMusicStream(music: Music): void;
    /** undefined */
    function SeekMusicStream(music: Music, position: number): void;
    /** undefined */
    function SetMusicVolume(music: Music, volume: number): void;
    /** undefined */
    function SetMusicPitch(music: Music, pitch: number): void;
    /** undefined */
    function SetMusicPan(music: Music, pan: number): void;
    /** undefined */
    function GetMusicTimeLength(music: Music): number;
    /** undefined */
    function GetMusicTimePlayed(music: Music): number;
    /** undefined */
    function LoadAudioStream(sampleRate: number, sampleSize: number, channels: number): AudioStream;
    /** undefined */
    function IsAudioStreamValid(stream: AudioStream): boolean;
    /** undefined */
    function UnloadAudioStream(stream: AudioStream): void;
    /** undefined */
    function UpdateAudioStream(stream: AudioStream, data: ArrayBuffer, frameCount: number): void;
    /** undefined */
    function IsAudioStreamProcessed(stream: AudioStream): boolean;
    /** undefined */
    function PlayAudioStream(stream: AudioStream): void;
    /** undefined */
    function PauseAudioStream(stream: AudioStream): void;
    /** undefined */
    function ResumeAudioStream(stream: AudioStream): void;
    /** undefined */
    function IsAudioStreamPlaying(stream: AudioStream): boolean;
    /** undefined */
    function StopAudioStream(stream: AudioStream): void;
    /** undefined */
    function SetAudioStreamVolume(stream: AudioStream, volume: number): void;
    /** undefined */
    function SetAudioStreamPitch(stream: AudioStream, pitch: number): void;
    /** undefined */
    function SetAudioStreamPan(stream: AudioStream, pan: number): void;
    /** undefined */
    function SetAudioStreamBufferSizeDefault(size: number): void;
    /** undefined */
    function AttachAudioMixedProcessor(processor: AudioMixedProcessor): void;
    /** undefined */
    function DetachAudioMixedProcessor(processor: AudioCallback): void;
    /**  */
    var FLAG_VSYNC_HINT: number;
    /**  */
    var FLAG_FULLSCREEN_MODE: number;
    /**  */
    var FLAG_WINDOW_RESIZABLE: number;
    /**  */
    var FLAG_WINDOW_UNDECORATED: number;
    /**  */
    var FLAG_WINDOW_HIDDEN: number;
    /**  */
    var FLAG_WINDOW_MINIMIZED: number;
    /**  */
    var FLAG_WINDOW_MAXIMIZED: number;
    /**  */
    var FLAG_WINDOW_UNFOCUSED: number;
    /**  */
    var FLAG_WINDOW_TOPMOST: number;
    /**  */
    var FLAG_WINDOW_ALWAYS_RUN: number;
    /**  */
    var FLAG_WINDOW_TRANSPARENT: number;
    /**  */
    var FLAG_WINDOW_HIGHDPI: number;
    /**  */
    var FLAG_WINDOW_MOUSE_PASSTHROUGH: number;
    /**  */
    var FLAG_BORDERLESS_WINDOWED_MODE: number;
    /**  */
    var FLAG_MSAA_4X_HINT: number;
    /**  */
    var FLAG_INTERLACED_HINT: number;
    /**  */
    var LOG_ALL: number;
    /**  */
    var LOG_TRACE: number;
    /**  */
    var LOG_DEBUG: number;
    /**  */
    var LOG_INFO: number;
    /**  */
    var LOG_WARNING: number;
    /**  */
    var LOG_ERROR: number;
    /**  */
    var LOG_FATAL: number;
    /**  */
    var LOG_NONE: number;
    /**  */
    var KEY_NULL: number;
    /**  */
    var KEY_APOSTROPHE: number;
    /**  */
    var KEY_COMMA: number;
    /**  */
    var KEY_MINUS: number;
    /**  */
    var KEY_PERIOD: number;
    /**  */
    var KEY_SLASH: number;
    /**  */
    var KEY_ZERO: number;
    /**  */
    var KEY_ONE: number;
    /**  */
    var KEY_TWO: number;
    /**  */
    var KEY_THREE: number;
    /**  */
    var KEY_FOUR: number;
    /**  */
    var KEY_FIVE: number;
    /**  */
    var KEY_SIX: number;
    /**  */
    var KEY_SEVEN: number;
    /**  */
    var KEY_EIGHT: number;
    /**  */
    var KEY_NINE: number;
    /**  */
    var KEY_SEMICOLON: number;
    /**  */
    var KEY_EQUAL: number;
    /**  */
    var KEY_A: number;
    /**  */
    var KEY_B: number;
    /**  */
    var KEY_C: number;
    /**  */
    var KEY_D: number;
    /**  */
    var KEY_E: number;
    /**  */
    var KEY_F: number;
    /**  */
    var KEY_G: number;
    /**  */
    var KEY_H: number;
    /**  */
    var KEY_I: number;
    /**  */
    var KEY_J: number;
    /**  */
    var KEY_K: number;
    /**  */
    var KEY_L: number;
    /**  */
    var KEY_M: number;
    /**  */
    var KEY_N: number;
    /**  */
    var KEY_O: number;
    /**  */
    var KEY_P: number;
    /**  */
    var KEY_Q: number;
    /**  */
    var KEY_R: number;
    /**  */
    var KEY_S: number;
    /**  */
    var KEY_T: number;
    /**  */
    var KEY_U: number;
    /**  */
    var KEY_V: number;
    /**  */
    var KEY_W: number;
    /**  */
    var KEY_X: number;
    /**  */
    var KEY_Y: number;
    /**  */
    var KEY_Z: number;
    /**  */
    var KEY_LEFT_BRACKET: number;
    /**  */
    var KEY_BACKSLASH: number;
    /**  */
    var KEY_RIGHT_BRACKET: number;
    /**  */
    var KEY_GRAVE: number;
    /**  */
    var KEY_SPACE: number;
    /**  */
    var KEY_ESCAPE: number;
    /**  */
    var KEY_ENTER: number;
    /**  */
    var KEY_TAB: number;
    /**  */
    var KEY_BACKSPACE: number;
    /**  */
    var KEY_INSERT: number;
    /**  */
    var KEY_DELETE: number;
    /**  */
    var KEY_RIGHT: number;
    /**  */
    var KEY_LEFT: number;
    /**  */
    var KEY_DOWN: number;
    /**  */
    var KEY_UP: number;
    /**  */
    var KEY_PAGE_UP: number;
    /**  */
    var KEY_PAGE_DOWN: number;
    /**  */
    var KEY_HOME: number;
    /**  */
    var KEY_END: number;
    /**  */
    var KEY_CAPS_LOCK: number;
    /**  */
    var KEY_SCROLL_LOCK: number;
    /**  */
    var KEY_NUM_LOCK: number;
    /**  */
    var KEY_PRINT_SCREEN: number;
    /**  */
    var KEY_PAUSE: number;
    /**  */
    var KEY_F1: number;
    /**  */
    var KEY_F2: number;
    /**  */
    var KEY_F3: number;
    /**  */
    var KEY_F4: number;
    /**  */
    var KEY_F5: number;
    /**  */
    var KEY_F6: number;
    /**  */
    var KEY_F7: number;
    /**  */
    var KEY_F8: number;
    /**  */
    var KEY_F9: number;
    /**  */
    var KEY_F10: number;
    /**  */
    var KEY_F11: number;
    /**  */
    var KEY_F12: number;
    /**  */
    var KEY_LEFT_SHIFT: number;
    /**  */
    var KEY_LEFT_CONTROL: number;
    /**  */
    var KEY_LEFT_ALT: number;
    /**  */
    var KEY_LEFT_SUPER: number;
    /**  */
    var KEY_RIGHT_SHIFT: number;
    /**  */
    var KEY_RIGHT_CONTROL: number;
    /**  */
    var KEY_RIGHT_ALT: number;
    /**  */
    var KEY_RIGHT_SUPER: number;
    /**  */
    var KEY_KB_MENU: number;
    /**  */
    var KEY_KP_0: number;
    /**  */
    var KEY_KP_1: number;
    /**  */
    var KEY_KP_2: number;
    /**  */
    var KEY_KP_3: number;
    /**  */
    var KEY_KP_4: number;
    /**  */
    var KEY_KP_5: number;
    /**  */
    var KEY_KP_6: number;
    /**  */
    var KEY_KP_7: number;
    /**  */
    var KEY_KP_8: number;
    /**  */
    var KEY_KP_9: number;
    /**  */
    var KEY_KP_DECIMAL: number;
    /**  */
    var KEY_KP_DIVIDE: number;
    /**  */
    var KEY_KP_MULTIPLY: number;
    /**  */
    var KEY_KP_SUBTRACT: number;
    /**  */
    var KEY_KP_ADD: number;
    /**  */
    var KEY_KP_ENTER: number;
    /**  */
    var KEY_KP_EQUAL: number;
    /**  */
    var KEY_BACK: number;
    /**  */
    var KEY_MENU: number;
    /**  */
    var KEY_VOLUME_UP: number;
    /**  */
    var KEY_VOLUME_DOWN: number;
    /**  */
    var MOUSE_BUTTON_LEFT: number;
    /**  */
    var MOUSE_BUTTON_RIGHT: number;
    /**  */
    var MOUSE_BUTTON_MIDDLE: number;
    /**  */
    var MOUSE_BUTTON_SIDE: number;
    /**  */
    var MOUSE_BUTTON_EXTRA: number;
    /**  */
    var MOUSE_BUTTON_FORWARD: number;
    /**  */
    var MOUSE_BUTTON_BACK: number;
    /**  */
    var MOUSE_CURSOR_DEFAULT: number;
    /**  */
    var MOUSE_CURSOR_ARROW: number;
    /**  */
    var MOUSE_CURSOR_IBEAM: number;
    /**  */
    var MOUSE_CURSOR_CROSSHAIR: number;
    /**  */
    var MOUSE_CURSOR_POINTING_HAND: number;
    /**  */
    var MOUSE_CURSOR_RESIZE_EW: number;
    /**  */
    var MOUSE_CURSOR_RESIZE_NS: number;
    /**  */
    var MOUSE_CURSOR_RESIZE_NWSE: number;
    /**  */
    var MOUSE_CURSOR_RESIZE_NESW: number;
    /**  */
    var MOUSE_CURSOR_RESIZE_ALL: number;
    /**  */
    var MOUSE_CURSOR_NOT_ALLOWED: number;
    /**  */
    var GAMEPAD_BUTTON_UNKNOWN: number;
    /**  */
    var GAMEPAD_BUTTON_LEFT_FACE_UP: number;
    /**  */
    var GAMEPAD_BUTTON_LEFT_FACE_RIGHT: number;
    /**  */
    var GAMEPAD_BUTTON_LEFT_FACE_DOWN: number;
    /**  */
    var GAMEPAD_BUTTON_LEFT_FACE_LEFT: number;
    /**  */
    var GAMEPAD_BUTTON_RIGHT_FACE_UP: number;
    /**  */
    var GAMEPAD_BUTTON_RIGHT_FACE_RIGHT: number;
    /**  */
    var GAMEPAD_BUTTON_RIGHT_FACE_DOWN: number;
    /**  */
    var GAMEPAD_BUTTON_RIGHT_FACE_LEFT: number;
    /**  */
    var GAMEPAD_BUTTON_LEFT_TRIGGER_1: number;
    /**  */
    var GAMEPAD_BUTTON_LEFT_TRIGGER_2: number;
    /**  */
    var GAMEPAD_BUTTON_RIGHT_TRIGGER_1: number;
    /**  */
    var GAMEPAD_BUTTON_RIGHT_TRIGGER_2: number;
    /**  */
    var GAMEPAD_BUTTON_MIDDLE_LEFT: number;
    /**  */
    var GAMEPAD_BUTTON_MIDDLE: number;
    /**  */
    var GAMEPAD_BUTTON_MIDDLE_RIGHT: number;
    /**  */
    var GAMEPAD_BUTTON_LEFT_THUMB: number;
    /**  */
    var GAMEPAD_BUTTON_RIGHT_THUMB: number;
    /**  */
    var GAMEPAD_AXIS_LEFT_X: number;
    /**  */
    var GAMEPAD_AXIS_LEFT_Y: number;
    /**  */
    var GAMEPAD_AXIS_RIGHT_X: number;
    /**  */
    var GAMEPAD_AXIS_RIGHT_Y: number;
    /**  */
    var GAMEPAD_AXIS_LEFT_TRIGGER: number;
    /**  */
    var GAMEPAD_AXIS_RIGHT_TRIGGER: number;
    /**  */
    var MATERIAL_MAP_ALBEDO: number;
    /**  */
    var MATERIAL_MAP_METALNESS: number;
    /**  */
    var MATERIAL_MAP_NORMAL: number;
    /**  */
    var MATERIAL_MAP_ROUGHNESS: number;
    /**  */
    var MATERIAL_MAP_OCCLUSION: number;
    /**  */
    var MATERIAL_MAP_EMISSION: number;
    /**  */
    var MATERIAL_MAP_HEIGHT: number;
    /**  */
    var MATERIAL_MAP_CUBEMAP: number;
    /**  */
    var MATERIAL_MAP_IRRADIANCE: number;
    /**  */
    var MATERIAL_MAP_PREFILTER: number;
    /**  */
    var MATERIAL_MAP_BRDF: number;
    /**  */
    var SHADER_LOC_VERTEX_POSITION: number;
    /**  */
    var SHADER_LOC_VERTEX_TEXCOORD01: number;
    /**  */
    var SHADER_LOC_VERTEX_TEXCOORD02: number;
    /**  */
    var SHADER_LOC_VERTEX_NORMAL: number;
    /**  */
    var SHADER_LOC_VERTEX_TANGENT: number;
    /**  */
    var SHADER_LOC_VERTEX_COLOR: number;
    /**  */
    var SHADER_LOC_MATRIX_MVP: number;
    /**  */
    var SHADER_LOC_MATRIX_VIEW: number;
    /**  */
    var SHADER_LOC_MATRIX_PROJECTION: number;
    /**  */
    var SHADER_LOC_MATRIX_MODEL: number;
    /**  */
    var SHADER_LOC_MATRIX_NORMAL: number;
    /**  */
    var SHADER_LOC_VECTOR_VIEW: number;
    /**  */
    var SHADER_LOC_COLOR_DIFFUSE: number;
    /**  */
    var SHADER_LOC_COLOR_SPECULAR: number;
    /**  */
    var SHADER_LOC_COLOR_AMBIENT: number;
    /**  */
    var SHADER_LOC_MAP_ALBEDO: number;
    /**  */
    var SHADER_LOC_MAP_METALNESS: number;
    /**  */
    var SHADER_LOC_MAP_NORMAL: number;
    /**  */
    var SHADER_LOC_MAP_ROUGHNESS: number;
    /**  */
    var SHADER_LOC_MAP_OCCLUSION: number;
    /**  */
    var SHADER_LOC_MAP_EMISSION: number;
    /**  */
    var SHADER_LOC_MAP_HEIGHT: number;
    /**  */
    var SHADER_LOC_MAP_CUBEMAP: number;
    /**  */
    var SHADER_LOC_MAP_IRRADIANCE: number;
    /**  */
    var SHADER_LOC_MAP_PREFILTER: number;
    /**  */
    var SHADER_LOC_MAP_BRDF: number;
    /**  */
    var SHADER_LOC_VERTEX_BONEIDS: number;
    /**  */
    var SHADER_LOC_VERTEX_BONEWEIGHTS: number;
    /**  */
    var SHADER_LOC_BONE_MATRICES: number;
    /**  */
    var SHADER_LOC_VERTEX_INSTANCE_TX: number;
    /**  */
    var SHADER_UNIFORM_FLOAT: number;
    /**  */
    var SHADER_UNIFORM_VEC2: number;
    /**  */
    var SHADER_UNIFORM_VEC3: number;
    /**  */
    var SHADER_UNIFORM_VEC4: number;
    /**  */
    var SHADER_UNIFORM_INT: number;
    /**  */
    var SHADER_UNIFORM_IVEC2: number;
    /**  */
    var SHADER_UNIFORM_IVEC3: number;
    /**  */
    var SHADER_UNIFORM_IVEC4: number;
    /**  */
    var SHADER_UNIFORM_UINT: number;
    /**  */
    var SHADER_UNIFORM_UIVEC2: number;
    /**  */
    var SHADER_UNIFORM_UIVEC3: number;
    /**  */
    var SHADER_UNIFORM_UIVEC4: number;
    /**  */
    var SHADER_UNIFORM_SAMPLER2D: number;
    /**  */
    var SHADER_ATTRIB_FLOAT: number;
    /**  */
    var SHADER_ATTRIB_VEC2: number;
    /**  */
    var SHADER_ATTRIB_VEC3: number;
    /**  */
    var SHADER_ATTRIB_VEC4: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_GRAYSCALE: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_R5G6B5: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_R8G8B8: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_R5G5B5A1: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_R4G4B4A4: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_R8G8B8A8: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_R32: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_R32G32B32: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_R32G32B32A32: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_R16: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_R16G16B16: number;
    /**  */
    var PIXELFORMAT_UNCOMPRESSED_R16G16B16A16: number;
    /**  */
    var PIXELFORMAT_COMPRESSED_DXT1_RGB: number;
    /**  */
    var PIXELFORMAT_COMPRESSED_DXT1_RGBA: number;
    /**  */
    var PIXELFORMAT_COMPRESSED_DXT3_RGBA: number;
    /**  */
    var PIXELFORMAT_COMPRESSED_DXT5_RGBA: number;
    /**  */
    var PIXELFORMAT_COMPRESSED_ETC1_RGB: number;
    /**  */
    var PIXELFORMAT_COMPRESSED_ETC2_RGB: number;
    /**  */
    var PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA: number;
    /**  */
    var PIXELFORMAT_COMPRESSED_PVRT_RGB: number;
    /**  */
    var PIXELFORMAT_COMPRESSED_PVRT_RGBA: number;
    /**  */
    var PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA: number;
    /**  */
    var PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA: number;
    /**  */
    var TEXTURE_FILTER_POINT: number;
    /**  */
    var TEXTURE_FILTER_BILINEAR: number;
    /**  */
    var TEXTURE_FILTER_TRILINEAR: number;
    /**  */
    var TEXTURE_FILTER_ANISOTROPIC_4X: number;
    /**  */
    var TEXTURE_FILTER_ANISOTROPIC_8X: number;
    /**  */
    var TEXTURE_FILTER_ANISOTROPIC_16X: number;
    /**  */
    var TEXTURE_WRAP_REPEAT: number;
    /**  */
    var TEXTURE_WRAP_CLAMP: number;
    /**  */
    var TEXTURE_WRAP_MIRROR_REPEAT: number;
    /**  */
    var TEXTURE_WRAP_MIRROR_CLAMP: number;
    /**  */
    var CUBEMAP_LAYOUT_AUTO_DETECT: number;
    /**  */
    var CUBEMAP_LAYOUT_LINE_VERTICAL: number;
    /**  */
    var CUBEMAP_LAYOUT_LINE_HORIZONTAL: number;
    /**  */
    var CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR: number;
    /**  */
    var CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE: number;
    /**  */
    var FONT_DEFAULT: number;
    /**  */
    var FONT_BITMAP: number;
    /**  */
    var FONT_SDF: number;
    /**  */
    var BLEND_ALPHA: number;
    /**  */
    var BLEND_ADDITIVE: number;
    /**  */
    var BLEND_MULTIPLIED: number;
    /**  */
    var BLEND_ADD_COLORS: number;
    /**  */
    var BLEND_SUBTRACT_COLORS: number;
    /**  */
    var BLEND_ALPHA_PREMULTIPLY: number;
    /**  */
    var BLEND_CUSTOM: number;
    /**  */
    var BLEND_CUSTOM_SEPARATE: number;
    /**  */
    var GESTURE_NONE: number;
    /**  */
    var GESTURE_TAP: number;
    /**  */
    var GESTURE_DOUBLETAP: number;
    /**  */
    var GESTURE_HOLD: number;
    /**  */
    var GESTURE_DRAG: number;
    /**  */
    var GESTURE_SWIPE_RIGHT: number;
    /**  */
    var GESTURE_SWIPE_LEFT: number;
    /**  */
    var GESTURE_SWIPE_UP: number;
    /**  */
    var GESTURE_SWIPE_DOWN: number;
    /**  */
    var GESTURE_PINCH_IN: number;
    /**  */
    var GESTURE_PINCH_OUT: number;
    /**  */
    var CAMERA_CUSTOM: number;
    /**  */
    var CAMERA_FREE: number;
    /**  */
    var CAMERA_ORBITAL: number;
    /**  */
    var CAMERA_FIRST_PERSON: number;
    /**  */
    var CAMERA_THIRD_PERSON: number;
    /**  */
    var CAMERA_PERSPECTIVE: number;
    /**  */
    var CAMERA_ORTHOGRAPHIC: number;
    /**  */
    var NPATCH_NINE_PATCH: number;
    /**  */
    var NPATCH_THREE_PATCH_VERTICAL: number;
    /**  */
    var NPATCH_THREE_PATCH_HORIZONTAL: number;
    /**  */
    var RAYLIB_VERSION_MAJOR: number;
    /**  */
    var RAYLIB_VERSION_MINOR: number;
    /**  */
    var RAYLIB_VERSION_PATCH: number;
    /**  */
    var PI: number;
    /** undefined */
    var LIGHTGRAY: Color;
    /** undefined */
    var GRAY: Color;
    /** undefined */
    var DARKGRAY: Color;
    /** undefined */
    var YELLOW: Color;
    /** undefined */
    var GOLD: Color;
    /** undefined */
    var ORANGE: Color;
    /** undefined */
    var PINK: Color;
    /** undefined */
    var RED: Color;
    /** undefined */
    var MAROON: Color;
    /** undefined */
    var GREEN: Color;
    /** undefined */
    var LIME: Color;
    /** undefined */
    var DARKGREEN: Color;
    /** undefined */
    var SKYBLUE: Color;
    /** undefined */
    var BLUE: Color;
    /** undefined */
    var DARKBLUE: Color;
    /** undefined */
    var PURPLE: Color;
    /** undefined */
    var VIOLET: Color;
    /** undefined */
    var DARKPURPLE: Color;
    /** undefined */
    var BEIGE: Color;
    /** undefined */
    var BROWN: Color;
    /** undefined */
    var DARKBROWN: Color;
    /** undefined */
    var WHITE: Color;
    /** undefined */
    var BLACK: Color;
    /** undefined */
    var BLANK: Color;
    /** undefined */
    var MAGENTA: Color;
    /** undefined */
    var RAYWHITE: Color;
    /**  */
    var MOUSE_LEFT_BUTTON: number;
    /**  */
    var MOUSE_RIGHT_BUTTON: number;
    /**  */
    var MOUSE_MIDDLE_BUTTON: number;
    /**  */
    var MATERIAL_MAP_DIFFUSE: number;
    /**  */
    var MATERIAL_MAP_SPECULAR: number;
    /**  */
    var SHADER_LOC_MAP_DIFFUSE: number;
    /**  */
    var SHADER_LOC_MAP_SPECULAR: number;
}
