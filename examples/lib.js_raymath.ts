interface float3 {
}
declare var float3: {
    prototype: float3;
}
interface float16 {
}
declare var float16: {
    prototype: float16;
}
/** undefined */
declare function Clamp(value: number, min: number, max: number): number;
/** undefined */
declare function Lerp(start: number, end: number, amount: number): number;
/** undefined */
declare function Normalize(value: number, start: number, end: number): number;
/** undefined */
declare function Remap(value: number, inputStart: number, inputEnd: number, outputStart: number, outputEnd: number): number;
/** undefined */
declare function Wrap(value: number, min: number, max: number): number;
/** undefined */
declare function FloatEquals(x: number, y: number): number;
/** undefined */
declare function Vector2Zero(): Vector2;
/** undefined */
declare function Vector2One(): Vector2;
/** undefined */
declare function Vector2Add(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function Vector2AddValue(v: Vector2, add: number): Vector2;
/** undefined */
declare function Vector2Subtract(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function Vector2SubtractValue(v: Vector2, sub: number): Vector2;
/** undefined */
declare function Vector2Length(v: Vector2): number;
/** undefined */
declare function Vector2LengthSqr(v: Vector2): number;
/** undefined */
declare function Vector2DotProduct(v1: Vector2, v2: Vector2): number;
/** undefined */
declare function Vector2CrossProduct(v1: Vector2, v2: Vector2): number;
/** undefined */
declare function Vector2Distance(v1: Vector2, v2: Vector2): number;
/** undefined */
declare function Vector2DistanceSqr(v1: Vector2, v2: Vector2): number;
/** undefined */
declare function Vector2Angle(v1: Vector2, v2: Vector2): number;
/** undefined */
declare function Vector2LineAngle(start: Vector2, end: Vector2): number;
/** undefined */
declare function Vector2Scale(v: Vector2, scale: number): Vector2;
/** undefined */
declare function Vector2Multiply(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function Vector2Negate(v: Vector2): Vector2;
/** undefined */
declare function Vector2Divide(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function Vector2Normalize(v: Vector2): Vector2;
/** undefined */
declare function Vector2Transform(v: Vector2, mat: Matrix): Vector2;
/** undefined */
declare function Vector2Lerp(v1: Vector2, v2: Vector2, amount: number): Vector2;
/** undefined */
declare function Vector2Reflect(v: Vector2, normal: Vector2): Vector2;
/** undefined */
declare function Vector2Min(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function Vector2Max(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function Vector2Rotate(v: Vector2, angle: number): Vector2;
/** undefined */
declare function Vector2MoveTowards(v: Vector2, target: Vector2, maxDistance: number): Vector2;
/** undefined */
declare function Vector2Invert(v: Vector2): Vector2;
/** undefined */
declare function Vector2Clamp(v: Vector2, min: Vector2, max: Vector2): Vector2;
/** undefined */
declare function Vector2ClampValue(v: Vector2, min: number, max: number): Vector2;
/** undefined */
declare function Vector2Equals(p: Vector2, q: Vector2): number;
/** undefined */
declare function Vector2Refract(v: Vector2, n: Vector2, r: number): Vector2;
/** undefined */
declare function Vector3Zero(): Vector3;
/** undefined */
declare function Vector3One(): Vector3;
/** undefined */
declare function Vector3Add(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function Vector3AddValue(v: Vector3, add: number): Vector3;
/** undefined */
declare function Vector3Subtract(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function Vector3SubtractValue(v: Vector3, sub: number): Vector3;
/** undefined */
declare function Vector3Scale(v: Vector3, scalar: number): Vector3;
/** undefined */
declare function Vector3Multiply(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function Vector3CrossProduct(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function Vector3Perpendicular(v: Vector3): Vector3;
/** undefined */
declare function Vector3Length(v: Vector3): number;
/** undefined */
declare function Vector3LengthSqr(v: Vector3): number;
/** undefined */
declare function Vector3DotProduct(v1: Vector3, v2: Vector3): number;
/** undefined */
declare function Vector3Distance(v1: Vector3, v2: Vector3): number;
/** undefined */
declare function Vector3DistanceSqr(v1: Vector3, v2: Vector3): number;
/** undefined */
declare function Vector3Angle(v1: Vector3, v2: Vector3): number;
/** undefined */
declare function Vector3Negate(v: Vector3): Vector3;
/** undefined */
declare function Vector3Divide(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function Vector3Normalize(v: Vector3): Vector3;
/** undefined */
declare function Vector3Project(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function Vector3Reject(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function Vector3OrthoNormalize(v1: Vector3 &, v2: Vector3 &): void;
/** undefined */
declare function Vector3Transform(v: Vector3, mat: Matrix): Vector3;
/** undefined */
declare function Vector3RotateByQuaternion(v: Vector3, q: Vector4): Vector3;
/** undefined */
declare function Vector3RotateByAxisAngle(v: Vector3, axis: Vector3, angle: number): Vector3;
/** undefined */
declare function Vector3MoveTowards(v: Vector3, target: Vector3, maxDistance: number): Vector3;
/** undefined */
declare function Vector3Lerp(v1: Vector3, v2: Vector3, amount: number): Vector3;
/** undefined */
declare function Vector3CubicHermite(v1: Vector3, tangent1: Vector3, v2: Vector3, tangent2: Vector3, amount: number): Vector3;
/** undefined */
declare function Vector3Reflect(v: Vector3, normal: Vector3): Vector3;
/** undefined */
declare function Vector3Min(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function Vector3Max(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function Vector3Barycenter(p: Vector3, a: Vector3, b: Vector3, c: Vector3): Vector3;
/** undefined */
declare function Vector3Unproject(source: Vector3, projection: Matrix, view: Matrix): Vector3;
/** undefined */
declare function Vector3Invert(v: Vector3): Vector3;
/** undefined */
declare function Vector3Clamp(v: Vector3, min: Vector3, max: Vector3): Vector3;
/** undefined */
declare function Vector3ClampValue(v: Vector3, min: number, max: number): Vector3;
/** undefined */
declare function Vector3Equals(p: Vector3, q: Vector3): number;
/** undefined */
declare function Vector3Refract(v: Vector3, n: Vector3, r: number): Vector3;
/** undefined */
declare function Vector4Zero(): Vector4;
/** undefined */
declare function Vector4One(): Vector4;
/** undefined */
declare function Vector4Add(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function Vector4AddValue(v: Vector4, add: number): Vector4;
/** undefined */
declare function Vector4Subtract(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function Vector4SubtractValue(v: Vector4, add: number): Vector4;
/** undefined */
declare function Vector4Length(v: Vector4): number;
/** undefined */
declare function Vector4LengthSqr(v: Vector4): number;
/** undefined */
declare function Vector4DotProduct(v1: Vector4, v2: Vector4): number;
/** undefined */
declare function Vector4Distance(v1: Vector4, v2: Vector4): number;
/** undefined */
declare function Vector4DistanceSqr(v1: Vector4, v2: Vector4): number;
/** undefined */
declare function Vector4Scale(v: Vector4, scale: number): Vector4;
/** undefined */
declare function Vector4Multiply(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function Vector4Negate(v: Vector4): Vector4;
/** undefined */
declare function Vector4Divide(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function Vector4Normalize(v: Vector4): Vector4;
/** undefined */
declare function Vector4Min(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function Vector4Max(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function Vector4Lerp(v1: Vector4, v2: Vector4, amount: number): Vector4;
/** undefined */
declare function Vector4MoveTowards(v: Vector4, target: Vector4, maxDistance: number): Vector4;
/** undefined */
declare function Vector4Invert(v: Vector4): Vector4;
/** undefined */
declare function Vector4Equals(p: Vector4, q: Vector4): number;
/** undefined */
declare function MatrixDeterminant(mat: Matrix): number;
/** undefined */
declare function MatrixTrace(mat: Matrix): number;
/** undefined */
declare function MatrixTranspose(mat: Matrix): Matrix;
/** undefined */
declare function MatrixInvert(mat: Matrix): Matrix;
/** undefined */
declare function MatrixIdentity(): Matrix;
/** undefined */
declare function MatrixAdd(left: Matrix, right: Matrix): Matrix;
/** undefined */
declare function MatrixSubtract(left: Matrix, right: Matrix): Matrix;
/** undefined */
declare function MatrixMultiply(left: Matrix, right: Matrix): Matrix;
/** undefined */
declare function MatrixTranslate(x: number, y: number, z: number): Matrix;
/** undefined */
declare function MatrixRotate(axis: Vector3, angle: number): Matrix;
/** undefined */
declare function MatrixRotateX(angle: number): Matrix;
/** undefined */
declare function MatrixRotateY(angle: number): Matrix;
/** undefined */
declare function MatrixRotateZ(angle: number): Matrix;
/** undefined */
declare function MatrixRotateXYZ(angle: Vector3): Matrix;
/** undefined */
declare function MatrixRotateZYX(angle: Vector3): Matrix;
/** undefined */
declare function MatrixScale(x: number, y: number, z: number): Matrix;
/** undefined */
declare function MatrixFrustum(left: number, right: number, bottom: number, top: number, nearPlane: number, farPlane: number): Matrix;
/** undefined */
declare function MatrixPerspective(fovY: number, aspect: number, nearPlane: number, farPlane: number): Matrix;
/** undefined */
declare function MatrixOrtho(left: number, right: number, bottom: number, top: number, nearPlane: number, farPlane: number): Matrix;
/** undefined */
declare function MatrixLookAt(eye: Vector3, target: Vector3, up: Vector3): Matrix;
/** undefined */
declare function QuaternionAdd(q1: Vector4, q2: Vector4): Vector4;
/** undefined */
declare function QuaternionAddValue(q: Vector4, add: number): Vector4;
/** undefined */
declare function QuaternionSubtract(q1: Vector4, q2: Vector4): Vector4;
/** undefined */
declare function QuaternionSubtractValue(q: Vector4, sub: number): Vector4;
/** undefined */
declare function QuaternionIdentity(): Vector4;
/** undefined */
declare function QuaternionLength(q: Vector4): number;
/** undefined */
declare function QuaternionNormalize(q: Vector4): Vector4;
/** undefined */
declare function QuaternionInvert(q: Vector4): Vector4;
/** undefined */
declare function QuaternionMultiply(q1: Vector4, q2: Vector4): Vector4;
/** undefined */
declare function QuaternionScale(q: Vector4, mul: number): Vector4;
/** undefined */
declare function QuaternionDivide(q1: Vector4, q2: Vector4): Vector4;
/** undefined */
declare function QuaternionLerp(q1: Vector4, q2: Vector4, amount: number): Vector4;
/** undefined */
declare function QuaternionNlerp(q1: Vector4, q2: Vector4, amount: number): Vector4;
/** undefined */
declare function QuaternionSlerp(q1: Vector4, q2: Vector4, amount: number): Vector4;
/** undefined */
declare function QuaternionCubicHermiteSpline(q1: Vector4, outTangent1: Vector4, q2: Vector4, inTangent2: Vector4, t: number): Vector4;
/** undefined */
declare function QuaternionFromVector3ToVector3(from: Vector3, to: Vector3): Vector4;
/** undefined */
declare function QuaternionFromMatrix(mat: Matrix): Vector4;
/** undefined */
declare function QuaternionToMatrix(q: Vector4): Matrix;
/** undefined */
declare function QuaternionFromAxisAngle(axis: Vector3, angle: number): Vector4;
/** undefined */
declare function QuaternionToAxisAngle(q: Vector4, outAxis: Vector3, outAngle: ArrayBuffer): void;
/** undefined */
declare function QuaternionFromEuler(pitch: number, yaw: number, roll: number): Vector4;
/** undefined */
declare function QuaternionToEuler(q: Vector4): Vector3;
/** undefined */
declare function QuaternionTransform(q: Vector4, mat: Matrix): Vector4;
/** undefined */
declare function QuaternionEquals(p: Vector4, q: Vector4): number;
/** undefined */
declare function MatrixDecompose(mat: Matrix, translation: Vector3 &, rotation: Quaternion &, scale: Vector3 &): void;
/**  */
declare var EPSILON: number;
