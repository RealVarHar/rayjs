declare module "rayjs:rcamera" {
import type {Camera,Vector3,Matrix} from '[object Object]'/** undefined */
function GetCameraForward(camera: Camera): Vector3/** undefined */
function GetCameraUp(camera: Camera): Vector3/** undefined */
function GetCameraRight(camera: Camera): Vector3/** undefined */
function CameraMoveForward(camera: Camera, distance: number, moveInWorldPlane: boolean): void/** undefined */
function CameraMoveUp(camera: Camera, distance: number): void/** undefined */
function CameraMoveRight(camera: Camera, distance: number, moveInWorldPlane: boolean): void/** undefined */
function CameraMoveToTarget(camera: Camera, delta: number): void/** undefined */
function CameraYaw(camera: Camera, angle: number, rotateAroundTarget: boolean): void/** undefined */
function CameraPitch(camera: Camera, angle: number, lockView: boolean, rotateAroundTarget: boolean, rotateUp: boolean): void/** undefined */
function CameraRoll(camera: Camera, angle: number): void/** undefined */
function GetCameraViewMatrix(camera: Camera): Matrix/** undefined */
function GetCameraProjectionMatrix(camera: Camera, aspect: number): Matrix}
