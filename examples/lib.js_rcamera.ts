/** undefined */
declare function GetCameraForward(camera: Camera &): Vector3;
/** undefined */
declare function GetCameraUp(camera: Camera &): Vector3;
/** undefined */
declare function GetCameraRight(camera: Camera &): Vector3;
/** undefined */
declare function CameraMoveForward(camera: Camera &, distance: number, moveInWorldPlane: boolean): void;
/** undefined */
declare function CameraMoveUp(camera: Camera &, distance: number): void;
/** undefined */
declare function CameraMoveRight(camera: Camera &, distance: number, moveInWorldPlane: boolean): void;
/** undefined */
declare function CameraMoveToTarget(camera: Camera &, delta: number): void;
/** undefined */
declare function CameraYaw(camera: Camera &, angle: number, rotateAroundTarget: boolean): void;
/** undefined */
declare function CameraPitch(camera: Camera &, angle: number, lockView: boolean, rotateAroundTarget: boolean, rotateUp: boolean): void;
/** undefined */
declare function CameraRoll(camera: Camera &, angle: number): void;
/** undefined */
declare function GetCameraViewMatrix(camera: Camera &): Matrix;
/** undefined */
declare function GetCameraProjectionMatrix(camera: Camera &, aspect: number): Matrix;
