/** undefined */
declare function getCameraForward(camera: Camera &): Vector3;
/** undefined */
declare function getCameraUp(camera: Camera &): Vector3;
/** undefined */
declare function getCameraRight(camera: Camera &): Vector3;
/** undefined */
declare function cameraMoveForward(camera: Camera &, distance: number, moveInWorldPlane: boolean): void;
/** undefined */
declare function cameraMoveUp(camera: Camera &, distance: number): void;
/** undefined */
declare function cameraMoveRight(camera: Camera &, distance: number, moveInWorldPlane: boolean): void;
/** undefined */
declare function cameraMoveToTarget(camera: Camera &, delta: number): void;
/** undefined */
declare function cameraYaw(camera: Camera &, angle: number, rotateAroundTarget: boolean): void;
/** undefined */
declare function cameraPitch(camera: Camera &, angle: number, lockView: boolean, rotateAroundTarget: boolean, rotateUp: boolean): void;
/** undefined */
declare function cameraRoll(camera: Camera &, angle: number): void;
/** undefined */
declare function getCameraViewMatrix(camera: Camera &): Matrix;
/** undefined */
declare function getCameraProjectionMatrix(camera: Camera &, aspect: number): Matrix;
