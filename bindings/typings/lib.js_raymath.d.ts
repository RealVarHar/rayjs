declare module "rayjs:raymath" {
import type {Vector2,Matrix,Vector3,Quaternion,Vector4} from 'rayjs:raylib';
interface float3 {
v: [number,number,number],
}
var float3: {
prototype: float3
new(v?: [number,number,number]): float3
}
interface float16 {
v: [number,number,number,number,number,number,number,number,number,number,number,number,number,number,number,number],
}
var float16: {
prototype: float16
new(v?: [number,number,number,number,number,number,number,number,number,number,number,number,number,number,number,number]): float16
}
/** undefined */
function Clamp(value: number, min: number, max: number): number/** undefined */
function Lerp(start: number, end: number, amount: number): number/** undefined */
function Normalize(value: number, start: number, end: number): number/** undefined */
function Remap(value: number, inputStart: number, inputEnd: number, outputStart: number, outputEnd: number): number/** undefined */
function Wrap(value: number, min: number, max: number): number/** undefined */
function FloatEquals(x: number, y: number): number/** undefined */
function Vector2Zero(): Vector2/** undefined */
function Vector2One(): Vector2/** undefined */
function Vector2Add(v1: Vector2, v2: Vector2): Vector2/** undefined */
function Vector2AddValue(v: Vector2, add: number): Vector2/** undefined */
function Vector2Subtract(v1: Vector2, v2: Vector2): Vector2/** undefined */
function Vector2SubtractValue(v: Vector2, sub: number): Vector2/** undefined */
function Vector2Length(v: Vector2): number/** undefined */
function Vector2LengthSqr(v: Vector2): number/** undefined */
function Vector2DotProduct(v1: Vector2, v2: Vector2): number/** undefined */
function Vector2CrossProduct(v1: Vector2, v2: Vector2): number/** undefined */
function Vector2Distance(v1: Vector2, v2: Vector2): number/** undefined */
function Vector2DistanceSqr(v1: Vector2, v2: Vector2): number/** undefined */
function Vector2Angle(v1: Vector2, v2: Vector2): number/** undefined */
function Vector2LineAngle(start: Vector2, end: Vector2): number/** undefined */
function Vector2Scale(v: Vector2, scale: number): Vector2/** undefined */
function Vector2Multiply(v1: Vector2, v2: Vector2): Vector2/** undefined */
function Vector2Negate(v: Vector2): Vector2/** undefined */
function Vector2Divide(v1: Vector2, v2: Vector2): Vector2/** undefined */
function Vector2Normalize(v: Vector2): Vector2/** undefined */
function Vector2Transform(v: Vector2, mat: Matrix): Vector2/** undefined */
function Vector2Lerp(v1: Vector2, v2: Vector2, amount: number): Vector2/** undefined */
function Vector2Reflect(v: Vector2, normal: Vector2): Vector2/** undefined */
function Vector2Min(v1: Vector2, v2: Vector2): Vector2/** undefined */
function Vector2Max(v1: Vector2, v2: Vector2): Vector2/** undefined */
function Vector2Rotate(v: Vector2, angle: number): Vector2/** undefined */
function Vector2MoveTowards(v: Vector2, target: Vector2, maxDistance: number): Vector2/** undefined */
function Vector2Invert(v: Vector2): Vector2/** undefined */
function Vector2Clamp(v: Vector2, min: Vector2, max: Vector2): Vector2/** undefined */
function Vector2ClampValue(v: Vector2, min: number, max: number): Vector2/** undefined */
function Vector2Equals(p: Vector2, q: Vector2): number/** undefined */
function Vector2Refract(v: Vector2, n: Vector2, r: number): Vector2/** undefined */
function Vector3Zero(): Vector3/** undefined */
function Vector3One(): Vector3/** undefined */
function Vector3Add(v1: Vector3, v2: Vector3): Vector3/** undefined */
function Vector3AddValue(v: Vector3, add: number): Vector3/** undefined */
function Vector3Subtract(v1: Vector3, v2: Vector3): Vector3/** undefined */
function Vector3SubtractValue(v: Vector3, sub: number): Vector3/** undefined */
function Vector3Scale(v: Vector3, scalar: number): Vector3/** undefined */
function Vector3Multiply(v1: Vector3, v2: Vector3): Vector3/** undefined */
function Vector3CrossProduct(v1: Vector3, v2: Vector3): Vector3/** undefined */
function Vector3Perpendicular(v: Vector3): Vector3/** undefined */
function Vector3Length(v: Vector3): number/** undefined */
function Vector3LengthSqr(v: Vector3): number/** undefined */
function Vector3DotProduct(v1: Vector3, v2: Vector3): number/** undefined */
function Vector3Distance(v1: Vector3, v2: Vector3): number/** undefined */
function Vector3DistanceSqr(v1: Vector3, v2: Vector3): number/** undefined */
function Vector3Angle(v1: Vector3, v2: Vector3): number/** undefined */
function Vector3Negate(v: Vector3): Vector3/** undefined */
function Vector3Divide(v1: Vector3, v2: Vector3): Vector3/** undefined */
function Vector3Normalize(v: Vector3): Vector3/** undefined */
function Vector3Project(v1: Vector3, v2: Vector3): Vector3/** undefined */
function Vector3Reject(v1: Vector3, v2: Vector3): Vector3/** undefined */
function Vector3OrthoNormalize(v1: Vector3, v2: Vector3): void/** undefined */
function Vector3Transform(v: Vector3, mat: Matrix): Vector3/** undefined */
function Vector3RotateByQuaternion(v: Vector3, q: Quaternion): Vector3/** undefined */
function Vector3RotateByAxisAngle(v: Vector3, axis: Vector3, angle: number): Vector3/** undefined */
function Vector3MoveTowards(v: Vector3, target: Vector3, maxDistance: number): Vector3/** undefined */
function Vector3Lerp(v1: Vector3, v2: Vector3, amount: number): Vector3/** undefined */
function Vector3CubicHermite(v1: Vector3, tangent1: Vector3, v2: Vector3, tangent2: Vector3, amount: number): Vector3/** undefined */
function Vector3Reflect(v: Vector3, normal: Vector3): Vector3/** undefined */
function Vector3Min(v1: Vector3, v2: Vector3): Vector3/** undefined */
function Vector3Max(v1: Vector3, v2: Vector3): Vector3/** undefined */
function Vector3Barycenter(p: Vector3, a: Vector3, b: Vector3, c: Vector3): Vector3/** undefined */
function Vector3Unproject(source: Vector3, projection: Matrix, view: Matrix): Vector3/** undefined */
function Vector3ToFloatV(v: Vector3): float3/** undefined */
function Vector3Invert(v: Vector3): Vector3/** undefined */
function Vector3Clamp(v: Vector3, min: Vector3, max: Vector3): Vector3/** undefined */
function Vector3ClampValue(v: Vector3, min: number, max: number): Vector3/** undefined */
function Vector3Equals(p: Vector3, q: Vector3): number/** undefined */
function Vector3Refract(v: Vector3, n: Vector3, r: number): Vector3/** undefined */
function Vector4Zero(): Vector4/** undefined */
function Vector4One(): Vector4/** undefined */
function Vector4Add(v1: Vector4, v2: Vector4): Vector4/** undefined */
function Vector4AddValue(v: Vector4, add: number): Vector4/** undefined */
function Vector4Subtract(v1: Vector4, v2: Vector4): Vector4/** undefined */
function Vector4SubtractValue(v: Vector4, add: number): Vector4/** undefined */
function Vector4Length(v: Vector4): number/** undefined */
function Vector4LengthSqr(v: Vector4): number/** undefined */
function Vector4DotProduct(v1: Vector4, v2: Vector4): number/** undefined */
function Vector4Distance(v1: Vector4, v2: Vector4): number/** undefined */
function Vector4DistanceSqr(v1: Vector4, v2: Vector4): number/** undefined */
function Vector4Scale(v: Vector4, scale: number): Vector4/** undefined */
function Vector4Multiply(v1: Vector4, v2: Vector4): Vector4/** undefined */
function Vector4Negate(v: Vector4): Vector4/** undefined */
function Vector4Divide(v1: Vector4, v2: Vector4): Vector4/** undefined */
function Vector4Normalize(v: Vector4): Vector4/** undefined */
function Vector4Min(v1: Vector4, v2: Vector4): Vector4/** undefined */
function Vector4Max(v1: Vector4, v2: Vector4): Vector4/** undefined */
function Vector4Lerp(v1: Vector4, v2: Vector4, amount: number): Vector4/** undefined */
function Vector4MoveTowards(v: Vector4, target: Vector4, maxDistance: number): Vector4/** undefined */
function Vector4Invert(v: Vector4): Vector4/** undefined */
function Vector4Equals(p: Vector4, q: Vector4): number/** undefined */
function MatrixDeterminant(mat: Matrix): number/** undefined */
function MatrixTrace(mat: Matrix): number/** undefined */
function MatrixTranspose(mat: Matrix): Matrix/** undefined */
function MatrixInvert(mat: Matrix): Matrix/** undefined */
function MatrixIdentity(): Matrix/** undefined */
function MatrixAdd(left: Matrix, right: Matrix): Matrix/** undefined */
function MatrixSubtract(left: Matrix, right: Matrix): Matrix/** undefined */
function MatrixMultiply(left: Matrix, right: Matrix): Matrix/** undefined */
function MatrixTranslate(x: number, y: number, z: number): Matrix/** undefined */
function MatrixRotate(axis: Vector3, angle: number): Matrix/** undefined */
function MatrixRotateX(angle: number): Matrix/** undefined */
function MatrixRotateY(angle: number): Matrix/** undefined */
function MatrixRotateZ(angle: number): Matrix/** undefined */
function MatrixRotateXYZ(angle: Vector3): Matrix/** undefined */
function MatrixRotateZYX(angle: Vector3): Matrix/** undefined */
function MatrixScale(x: number, y: number, z: number): Matrix/** undefined */
function MatrixFrustum(left: number, right: number, bottom: number, top: number, nearPlane: number, farPlane: number): Matrix/** undefined */
function MatrixPerspective(fovY: number, aspect: number, nearPlane: number, farPlane: number): Matrix/** undefined */
function MatrixOrtho(left: number, right: number, bottom: number, top: number, nearPlane: number, farPlane: number): Matrix/** undefined */
function MatrixLookAt(eye: Vector3, target: Vector3, up: Vector3): Matrix/** undefined */
function MatrixToFloatV(mat: Matrix): float16/** undefined */
function QuaternionAdd(q1: Quaternion, q2: Quaternion): Quaternion/** undefined */
function QuaternionAddValue(q: Quaternion, add: number): Quaternion/** undefined */
function QuaternionSubtract(q1: Quaternion, q2: Quaternion): Quaternion/** undefined */
function QuaternionSubtractValue(q: Quaternion, sub: number): Quaternion/** undefined */
function QuaternionIdentity(): Quaternion/** undefined */
function QuaternionLength(q: Quaternion): number/** undefined */
function QuaternionNormalize(q: Quaternion): Quaternion/** undefined */
function QuaternionInvert(q: Quaternion): Quaternion/** undefined */
function QuaternionMultiply(q1: Quaternion, q2: Quaternion): Quaternion/** undefined */
function QuaternionScale(q: Quaternion, mul: number): Quaternion/** undefined */
function QuaternionDivide(q1: Quaternion, q2: Quaternion): Quaternion/** undefined */
function QuaternionLerp(q1: Quaternion, q2: Quaternion, amount: number): Quaternion/** undefined */
function QuaternionNlerp(q1: Quaternion, q2: Quaternion, amount: number): Quaternion/** undefined */
function QuaternionSlerp(q1: Quaternion, q2: Quaternion, amount: number): Quaternion/** undefined */
function QuaternionCubicHermiteSpline(q1: Quaternion, outTangent1: Quaternion, q2: Quaternion, inTangent2: Quaternion, t: number): Quaternion/** undefined */
function QuaternionFromVector3ToVector3(from: Vector3, to: Vector3): Quaternion/** undefined */
function QuaternionFromMatrix(mat: Matrix): Quaternion/** undefined */
function QuaternionToMatrix(q: Quaternion): Matrix/** undefined */
function QuaternionFromAxisAngle(axis: Vector3, angle: number): Quaternion/** undefined */
function QuaternionToAxisAngle(q: Quaternion, outAxis: Vector3[], outAngle: number[]): void/** undefined */
function QuaternionFromEuler(pitch: number, yaw: number, roll: number): Quaternion/** undefined */
function QuaternionToEuler(q: Quaternion): Vector3/** undefined */
function QuaternionTransform(q: Quaternion, mat: Matrix): Quaternion/** undefined */
function QuaternionEquals(p: Quaternion, q: Quaternion): number/** undefined */
function MatrixDecompose(mat: Matrix, translation: Vector3, rotation: Quaternion, scale: Vector3): void/**  */
var EPSILON: number}
