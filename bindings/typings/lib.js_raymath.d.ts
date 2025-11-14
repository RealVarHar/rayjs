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
/** Clamp float value */
function Clamp(value: number, min: number, max: number): number/** Calculate linear interpolation between two floats */
function Lerp(start: number, end: number, amount: number): number/** Normalize input value within input range */
function Normalize(value: number, start: number, end: number): number/** Remap input value within input range to output range */
function Remap(value: number, inputStart: number, inputEnd: number, outputStart: number, outputEnd: number): number/** Wrap input value from min to max */
function Wrap(value: number, min: number, max: number): number/** Check whether two given floats are almost equal */
function FloatEquals(x: number, y: number): number/** Vector with components value 0.0f */
function Vector2Zero(): Vector2/** Vector with components value 1.0f */
function Vector2One(): Vector2/** Add two vectors (v1 + v2) */
function Vector2Add(v1: Vector2, v2: Vector2): Vector2/** Add vector and float value */
function Vector2AddValue(v: Vector2, add: number): Vector2/** Subtract two vectors (v1 - v2) */
function Vector2Subtract(v1: Vector2, v2: Vector2): Vector2/** Subtract vector by float value */
function Vector2SubtractValue(v: Vector2, sub: number): Vector2/** Calculate vector length */
function Vector2Length(v: Vector2): number/** Calculate vector square length */
function Vector2LengthSqr(v: Vector2): number/** Calculate two vectors dot product */
function Vector2DotProduct(v1: Vector2, v2: Vector2): number/** Calculate two vectors cross product */
function Vector2CrossProduct(v1: Vector2, v2: Vector2): number/** Calculate distance between two vectors */
function Vector2Distance(v1: Vector2, v2: Vector2): number/** Calculate square distance between two vectors */
function Vector2DistanceSqr(v1: Vector2, v2: Vector2): number/** positive angles appear clockwise, and negative angles appear counterclockwise */
function Vector2Angle(v1: Vector2, v2: Vector2): number/** Current implementation should be aligned with glm::angle */
function Vector2LineAngle(start: Vector2, end: Vector2): number/** Scale vector (multiply by value) */
function Vector2Scale(v: Vector2, scale: number): Vector2/** Multiply vector by vector */
function Vector2Multiply(v1: Vector2, v2: Vector2): Vector2/** Negate vector */
function Vector2Negate(v: Vector2): Vector2/** Divide vector by vector */
function Vector2Divide(v1: Vector2, v2: Vector2): Vector2/** Normalize provided vector */
function Vector2Normalize(v: Vector2): Vector2/** Transforms a Vector2 by a given Matrix */
function Vector2Transform(v: Vector2, mat: Matrix): Vector2/** Calculate linear interpolation between two vectors */
function Vector2Lerp(v1: Vector2, v2: Vector2, amount: number): Vector2/** Calculate reflected vector to normal */
function Vector2Reflect(v: Vector2, normal: Vector2): Vector2/** Get min value for each pair of components */
function Vector2Min(v1: Vector2, v2: Vector2): Vector2/** Get max value for each pair of components */
function Vector2Max(v1: Vector2, v2: Vector2): Vector2/** Rotate vector by angle */
function Vector2Rotate(v: Vector2, angle: number): Vector2/** Move Vector towards target */
function Vector2MoveTowards(v: Vector2, target: Vector2, maxDistance: number): Vector2/** Invert the given vector */
function Vector2Invert(v: Vector2): Vector2/** min and max values specified by the given vectors */
function Vector2Clamp(v: Vector2, min: Vector2, max: Vector2): Vector2/** Clamp the magnitude of the vector between two min and max values */
function Vector2ClampValue(v: Vector2, min: number, max: number): Vector2/** Check whether two given vectors are almost equal */
function Vector2Equals(p: Vector2, q: Vector2): number/** to the refractive index of the medium on the other side of the surface */
function Vector2Refract(v: Vector2, n: Vector2, r: number): Vector2/** Vector with components value 0.0f */
function Vector3Zero(): Vector3/** Vector with components value 1.0f */
function Vector3One(): Vector3/** Add two vectors */
function Vector3Add(v1: Vector3, v2: Vector3): Vector3/** Add vector and float value */
function Vector3AddValue(v: Vector3, add: number): Vector3/** Subtract two vectors */
function Vector3Subtract(v1: Vector3, v2: Vector3): Vector3/** Subtract vector by float value */
function Vector3SubtractValue(v: Vector3, sub: number): Vector3/** Multiply vector by scalar */
function Vector3Scale(v: Vector3, scalar: number): Vector3/** Multiply vector by vector */
function Vector3Multiply(v1: Vector3, v2: Vector3): Vector3/** Calculate two vectors cross product */
function Vector3CrossProduct(v1: Vector3, v2: Vector3): Vector3/** Calculate one vector perpendicular vector */
function Vector3Perpendicular(v: Vector3): Vector3/** Calculate vector length */
function Vector3Length(v: Vector3): number/** Calculate vector square length */
function Vector3LengthSqr(v: Vector3): number/** Calculate two vectors dot product */
function Vector3DotProduct(v1: Vector3, v2: Vector3): number/** Calculate distance between two vectors */
function Vector3Distance(v1: Vector3, v2: Vector3): number/** Calculate square distance between two vectors */
function Vector3DistanceSqr(v1: Vector3, v2: Vector3): number/** Calculate angle between two vectors */
function Vector3Angle(v1: Vector3, v2: Vector3): number/** Negate provided vector (invert direction) */
function Vector3Negate(v: Vector3): Vector3/** Divide vector by vector */
function Vector3Divide(v1: Vector3, v2: Vector3): Vector3/** Normalize provided vector */
function Vector3Normalize(v: Vector3): Vector3/** Calculate the projection of the vector v1 on to v2 */
function Vector3Project(v1: Vector3, v2: Vector3): Vector3/** Calculate the rejection of the vector v1 on to v2 */
function Vector3Reject(v1: Vector3, v2: Vector3): Vector3/** Gram-Schmidt function implementation */
function Vector3OrthoNormalize(v1: Vector3, v2: Vector3): void/** Transforms a Vector3 by a given Matrix */
function Vector3Transform(v: Vector3, mat: Matrix): Vector3/** Transform a vector by quaternion rotation */
function Vector3RotateByQuaternion(v: Vector3, q: Quaternion): Vector3/** Rotates a vector around an axis */
function Vector3RotateByAxisAngle(v: Vector3, axis: Vector3, angle: number): Vector3/** Move Vector towards target */
function Vector3MoveTowards(v: Vector3, target: Vector3, maxDistance: number): Vector3/** Calculate linear interpolation between two vectors */
function Vector3Lerp(v1: Vector3, v2: Vector3, amount: number): Vector3/** as described in the GLTF 2.0 specification: https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#interpolation-cubic */
function Vector3CubicHermite(v1: Vector3, tangent1: Vector3, v2: Vector3, tangent2: Vector3, amount: number): Vector3/** Calculate reflected vector to normal */
function Vector3Reflect(v: Vector3, normal: Vector3): Vector3/** Get min value for each pair of components */
function Vector3Min(v1: Vector3, v2: Vector3): Vector3/** Get max value for each pair of components */
function Vector3Max(v1: Vector3, v2: Vector3): Vector3/** NOTE: Assumes P is on the plane of the triangle */
function Vector3Barycenter(p: Vector3, a: Vector3, b: Vector3, c: Vector3): Vector3/** NOTE: We are avoiding calling other raymath functions despite available */
function Vector3Unproject(source: Vector3, projection: Matrix, view: Matrix): Vector3/** Get Vector3 as float array */
function Vector3ToFloatV(v: Vector3): float3/** Invert the given vector */
function Vector3Invert(v: Vector3): Vector3/** min and max values specified by the given vectors */
function Vector3Clamp(v: Vector3, min: Vector3, max: Vector3): Vector3/** Clamp the magnitude of the vector between two values */
function Vector3ClampValue(v: Vector3, min: number, max: number): Vector3/** Check whether two given vectors are almost equal */
function Vector3Equals(p: Vector3, q: Vector3): number/** to the refractive index of the medium on the other side of the surface */
function Vector3Refract(v: Vector3, n: Vector3, r: number): Vector3/**  */
function Vector4Zero(): Vector4/**  */
function Vector4One(): Vector4/**  */
function Vector4Add(v1: Vector4, v2: Vector4): Vector4/**  */
function Vector4AddValue(v: Vector4, add: number): Vector4/**  */
function Vector4Subtract(v1: Vector4, v2: Vector4): Vector4/**  */
function Vector4SubtractValue(v: Vector4, add: number): Vector4/**  */
function Vector4Length(v: Vector4): number/**  */
function Vector4LengthSqr(v: Vector4): number/**  */
function Vector4DotProduct(v1: Vector4, v2: Vector4): number/** Calculate distance between two vectors */
function Vector4Distance(v1: Vector4, v2: Vector4): number/** Calculate square distance between two vectors */
function Vector4DistanceSqr(v1: Vector4, v2: Vector4): number/**  */
function Vector4Scale(v: Vector4, scale: number): Vector4/** Multiply vector by vector */
function Vector4Multiply(v1: Vector4, v2: Vector4): Vector4/** Negate vector */
function Vector4Negate(v: Vector4): Vector4/** Divide vector by vector */
function Vector4Divide(v1: Vector4, v2: Vector4): Vector4/** Normalize provided vector */
function Vector4Normalize(v: Vector4): Vector4/** Get min value for each pair of components */
function Vector4Min(v1: Vector4, v2: Vector4): Vector4/** Get max value for each pair of components */
function Vector4Max(v1: Vector4, v2: Vector4): Vector4/** Calculate linear interpolation between two vectors */
function Vector4Lerp(v1: Vector4, v2: Vector4, amount: number): Vector4/** Move Vector towards target */
function Vector4MoveTowards(v: Vector4, target: Vector4, maxDistance: number): Vector4/** Invert the given vector */
function Vector4Invert(v: Vector4): Vector4/** Check whether two given vectors are almost equal */
function Vector4Equals(p: Vector4, q: Vector4): number/** Compute matrix determinant */
function MatrixDeterminant(mat: Matrix): number/** Get the trace of the matrix (sum of the values along the diagonal) */
function MatrixTrace(mat: Matrix): number/** Transposes provided matrix */
function MatrixTranspose(mat: Matrix): Matrix/** Invert provided matrix */
function MatrixInvert(mat: Matrix): Matrix/** Get identity matrix */
function MatrixIdentity(): Matrix/** Add two matrices */
function MatrixAdd(left: Matrix, right: Matrix): Matrix/** Subtract two matrices (left - right) */
function MatrixSubtract(left: Matrix, right: Matrix): Matrix/** NOTE: When multiplying matrices... the order matters! */
function MatrixMultiply(left: Matrix, right: Matrix): Matrix/** Get translation matrix */
function MatrixTranslate(x: number, y: number, z: number): Matrix/** NOTE: Angle should be provided in radians */
function MatrixRotate(axis: Vector3, angle: number): Matrix/** NOTE: Angle must be provided in radians */
function MatrixRotateX(angle: number): Matrix/** NOTE: Angle must be provided in radians */
function MatrixRotateY(angle: number): Matrix/** NOTE: Angle must be provided in radians */
function MatrixRotateZ(angle: number): Matrix/** NOTE: Angle must be provided in radians */
function MatrixRotateXYZ(angle: Vector3): Matrix/** NOTE: Angle must be provided in radians */
function MatrixRotateZYX(angle: Vector3): Matrix/** Get scaling matrix */
function MatrixScale(x: number, y: number, z: number): Matrix/** Get perspective projection matrix */
function MatrixFrustum(left: number, right: number, bottom: number, top: number, nearPlane: number, farPlane: number): Matrix/** NOTE: Fovy angle must be provided in radians */
function MatrixPerspective(fovY: number, aspect: number, nearPlane: number, farPlane: number): Matrix/** Get orthographic projection matrix */
function MatrixOrtho(left: number, right: number, bottom: number, top: number, nearPlane: number, farPlane: number): Matrix/** Get camera look-at matrix (view matrix) */
function MatrixLookAt(eye: Vector3, target: Vector3, up: Vector3): Matrix/** Get float array of matrix data */
function MatrixToFloatV(mat: Matrix): float16/** Add two quaternions */
function QuaternionAdd(q1: Quaternion, q2: Quaternion): Quaternion/** Add quaternion and float value */
function QuaternionAddValue(q: Quaternion, add: number): Quaternion/** Subtract two quaternions */
function QuaternionSubtract(q1: Quaternion, q2: Quaternion): Quaternion/** Subtract quaternion and float value */
function QuaternionSubtractValue(q: Quaternion, sub: number): Quaternion/** Get identity quaternion */
function QuaternionIdentity(): Quaternion/** Computes the length of a quaternion */
function QuaternionLength(q: Quaternion): number/** Normalize provided quaternion */
function QuaternionNormalize(q: Quaternion): Quaternion/** Invert provided quaternion */
function QuaternionInvert(q: Quaternion): Quaternion/** Calculate two quaternion multiplication */
function QuaternionMultiply(q1: Quaternion, q2: Quaternion): Quaternion/** Scale quaternion by float value */
function QuaternionScale(q: Quaternion, mul: number): Quaternion/** Divide two quaternions */
function QuaternionDivide(q1: Quaternion, q2: Quaternion): Quaternion/** Calculate linear interpolation between two quaternions */
function QuaternionLerp(q1: Quaternion, q2: Quaternion, amount: number): Quaternion/** Calculate slerp-optimized interpolation between two quaternions */
function QuaternionNlerp(q1: Quaternion, q2: Quaternion, amount: number): Quaternion/** Calculates spherical linear interpolation between two quaternions */
function QuaternionSlerp(q1: Quaternion, q2: Quaternion, amount: number): Quaternion/** as described in the GLTF 2.0 specification: https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#interpolation-cubic */
function QuaternionCubicHermiteSpline(q1: Quaternion, outTangent1: Quaternion, q2: Quaternion, inTangent2: Quaternion, t: number): Quaternion/** Calculate quaternion based on the rotation from one vector to another */
function QuaternionFromVector3ToVector3(from: Vector3, to: Vector3): Quaternion/** Get a quaternion for a given rotation matrix */
function QuaternionFromMatrix(mat: Matrix): Quaternion/** Get a matrix for a given quaternion */
function QuaternionToMatrix(q: Quaternion): Matrix/** NOTE: Angle must be provided in radians */
function QuaternionFromAxisAngle(axis: Vector3, angle: number): Quaternion/** Get the rotation angle and axis for a given quaternion */
function QuaternionToAxisAngle(q: Quaternion, outAxis: Vector3[], outAngle: number[]): void/** NOTE: Rotation order is ZYX */
function QuaternionFromEuler(pitch: number, yaw: number, roll: number): Quaternion/** NOTE: Angles are returned in a Vector3 struct in radians */
function QuaternionToEuler(q: Quaternion): Vector3/** Transform a quaternion given a transformation matrix */
function QuaternionTransform(q: Quaternion, mat: Matrix): Quaternion/** Check whether two given quaternions are almost equal */
function QuaternionEquals(p: Quaternion, q: Quaternion): number/** Decompose a transformation matrix into its rotational, translational and scaling components */
function MatrixDecompose(mat: Matrix, translation: Vector3, rotation: Quaternion, scale: Vector3): void/**  */
var EPSILON: number}
