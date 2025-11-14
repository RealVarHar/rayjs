declare module "rayjs:rcamera" {
import type {Camera,Vector3,Matrix} from 'rayjs:raylib';
/**  */
function GetCameraForward(camera: Camera): Vector3/**  */
function GetCameraUp(camera: Camera): Vector3/**  */
function GetCameraRight(camera: Camera): Vector3/** Camera movement */
function CameraMoveForward(camera: Camera, distance: number, moveInWorldPlane: boolean): void/**  */
function CameraMoveUp(camera: Camera, distance: number): void/**  */
function CameraMoveRight(camera: Camera, distance: number, moveInWorldPlane: boolean): void/**  */
function CameraMoveToTarget(camera: Camera, delta: number): void/** Camera rotation */
function CameraYaw(camera: Camera, angle: number, rotateAroundTarget: boolean): void/**  */
function CameraPitch(camera: Camera, angle: number, lockView: boolean, rotateAroundTarget: boolean, rotateUp: boolean): void/**  */
function CameraRoll(camera: Camera, angle: number): void/**  */
function GetCameraViewMatrix(camera: Camera): Matrix/**  */
function GetCameraProjectionMatrix(camera: Camera, aspect: number): Matrix}
