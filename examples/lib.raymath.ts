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
declare function clamp(value: number, min: number, max: number): number;
/** undefined */
declare function lerp(start: number, end: number, amount: number): number;
/** undefined */
declare function normalize(value: number, start: number, end: number): number;
/** undefined */
declare function remap(value: number, inputStart: number, inputEnd: number, outputStart: number, outputEnd: number): number;
/** undefined */
declare function wrap(value: number, min: number, max: number): number;
/** undefined */
declare function floatEquals(x: number, y: number): number;
/** undefined */
declare function vector2Zero(): Vector2;
/** undefined */
declare function vector2One(): Vector2;
/** undefined */
declare function vector2Add(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function vector2AddValue(v: Vector2, add: number): Vector2;
/** undefined */
declare function vector2Subtract(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function vector2SubtractValue(v: Vector2, sub: number): Vector2;
/** undefined */
declare function vector2Length(v: Vector2): number;
/** undefined */
declare function vector2LengthSqr(v: Vector2): number;
/** undefined */
declare function vector2DotProduct(v1: Vector2, v2: Vector2): number;
/** undefined */
declare function vector2CrossProduct(v1: Vector2, v2: Vector2): number;
/** undefined */
declare function vector2Distance(v1: Vector2, v2: Vector2): number;
/** undefined */
declare function vector2DistanceSqr(v1: Vector2, v2: Vector2): number;
/** undefined */
declare function vector2Angle(v1: Vector2, v2: Vector2): number;
/** undefined */
declare function vector2LineAngle(start: Vector2, end: Vector2): number;
/** undefined */
declare function vector2Scale(v: Vector2, scale: number): Vector2;
/** undefined */
declare function vector2Multiply(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function vector2Negate(v: Vector2): Vector2;
/** undefined */
declare function vector2Divide(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function vector2Normalize(v: Vector2): Vector2;
/** undefined */
declare function vector2Transform(v: Vector2, mat: Matrix): Vector2;
/** undefined */
declare function vector2Lerp(v1: Vector2, v2: Vector2, amount: number): Vector2;
/** undefined */
declare function vector2Reflect(v: Vector2, normal: Vector2): Vector2;
/** undefined */
declare function vector2Min(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function vector2Max(v1: Vector2, v2: Vector2): Vector2;
/** undefined */
declare function vector2Rotate(v: Vector2, angle: number): Vector2;
/** undefined */
declare function vector2MoveTowards(v: Vector2, target: Vector2, maxDistance: number): Vector2;
/** undefined */
declare function vector2Invert(v: Vector2): Vector2;
/** undefined */
declare function vector2Clamp(v: Vector2, min: Vector2, max: Vector2): Vector2;
/** undefined */
declare function vector2ClampValue(v: Vector2, min: number, max: number): Vector2;
/** undefined */
declare function vector2Equals(p: Vector2, q: Vector2): number;
/** undefined */
declare function vector2Refract(v: Vector2, n: Vector2, r: number): Vector2;
/** undefined */
declare function vector3Zero(): Vector3;
/** undefined */
declare function vector3One(): Vector3;
/** undefined */
declare function vector3Add(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function vector3AddValue(v: Vector3, add: number): Vector3;
/** undefined */
declare function vector3Subtract(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function vector3SubtractValue(v: Vector3, sub: number): Vector3;
/** undefined */
declare function vector3Scale(v: Vector3, scalar: number): Vector3;
/** undefined */
declare function vector3Multiply(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function vector3CrossProduct(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function vector3Perpendicular(v: Vector3): Vector3;
/** undefined */
declare function vector3Length(v: Vector3): number;
/** undefined */
declare function vector3LengthSqr(v: Vector3): number;
/** undefined */
declare function vector3DotProduct(v1: Vector3, v2: Vector3): number;
/** undefined */
declare function vector3Distance(v1: Vector3, v2: Vector3): number;
/** undefined */
declare function vector3DistanceSqr(v1: Vector3, v2: Vector3): number;
/** undefined */
declare function vector3Angle(v1: Vector3, v2: Vector3): number;
/** undefined */
declare function vector3Negate(v: Vector3): Vector3;
/** undefined */
declare function vector3Divide(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function vector3Normalize(v: Vector3): Vector3;
/** undefined */
declare function vector3Project(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function vector3Reject(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function vector3OrthoNormalize(v1: Vector3 &, v2: Vector3 &): void;
/** undefined */
declare function vector3Transform(v: Vector3, mat: Matrix): Vector3;
/** undefined */
declare function vector3RotateByQuaternion(v: Vector3, q: Vector4): Vector3;
/** undefined */
declare function vector3RotateByAxisAngle(v: Vector3, axis: Vector3, angle: number): Vector3;
/** undefined */
declare function vector3MoveTowards(v: Vector3, target: Vector3, maxDistance: number): Vector3;
/** undefined */
declare function vector3Lerp(v1: Vector3, v2: Vector3, amount: number): Vector3;
/** undefined */
declare function vector3CubicHermite(v1: Vector3, tangent1: Vector3, v2: Vector3, tangent2: Vector3, amount: number): Vector3;
/** undefined */
declare function vector3Reflect(v: Vector3, normal: Vector3): Vector3;
/** undefined */
declare function vector3Min(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function vector3Max(v1: Vector3, v2: Vector3): Vector3;
/** undefined */
declare function vector3Barycenter(p: Vector3, a: Vector3, b: Vector3, c: Vector3): Vector3;
/** undefined */
declare function vector3Unproject(source: Vector3, projection: Matrix, view: Matrix): Vector3;
/** undefined */
declare function vector3Invert(v: Vector3): Vector3;
/** undefined */
declare function vector3Clamp(v: Vector3, min: Vector3, max: Vector3): Vector3;
/** undefined */
declare function vector3ClampValue(v: Vector3, min: number, max: number): Vector3;
/** undefined */
declare function vector3Equals(p: Vector3, q: Vector3): number;
/** undefined */
declare function vector3Refract(v: Vector3, n: Vector3, r: number): Vector3;
/** undefined */
declare function vector4Zero(): Vector4;
/** undefined */
declare function vector4One(): Vector4;
/** undefined */
declare function vector4Add(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function vector4AddValue(v: Vector4, add: number): Vector4;
/** undefined */
declare function vector4Subtract(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function vector4SubtractValue(v: Vector4, add: number): Vector4;
/** undefined */
declare function vector4Length(v: Vector4): number;
/** undefined */
declare function vector4LengthSqr(v: Vector4): number;
/** undefined */
declare function vector4DotProduct(v1: Vector4, v2: Vector4): number;
/** undefined */
declare function vector4Distance(v1: Vector4, v2: Vector4): number;
/** undefined */
declare function vector4DistanceSqr(v1: Vector4, v2: Vector4): number;
/** undefined */
declare function vector4Scale(v: Vector4, scale: number): Vector4;
/** undefined */
declare function vector4Multiply(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function vector4Negate(v: Vector4): Vector4;
/** undefined */
declare function vector4Divide(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function vector4Normalize(v: Vector4): Vector4;
/** undefined */
declare function vector4Min(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function vector4Max(v1: Vector4, v2: Vector4): Vector4;
/** undefined */
declare function vector4Lerp(v1: Vector4, v2: Vector4, amount: number): Vector4;
/** undefined */
declare function vector4MoveTowards(v: Vector4, target: Vector4, maxDistance: number): Vector4;
/** undefined */
declare function vector4Invert(v: Vector4): Vector4;
/** undefined */
declare function vector4Equals(p: Vector4, q: Vector4): number;
/** undefined */
declare function matrixDeterminant(mat: Matrix): number;
/** undefined */
declare function matrixTrace(mat: Matrix): number;
/** undefined */
declare function matrixTranspose(mat: Matrix): Matrix;
/** undefined */
declare function matrixInvert(mat: Matrix): Matrix;
/** undefined */
declare function matrixIdentity(): Matrix;
/** undefined */
declare function matrixAdd(left: Matrix, right: Matrix): Matrix;
/** undefined */
declare function matrixSubtract(left: Matrix, right: Matrix): Matrix;
/** undefined */
declare function matrixMultiply(left: Matrix, right: Matrix): Matrix;
/** undefined */
declare function matrixTranslate(x: number, y: number, z: number): Matrix;
/** undefined */
declare function matrixRotate(axis: Vector3, angle: number): Matrix;
/** undefined */
declare function matrixRotateX(angle: number): Matrix;
/** undefined */
declare function matrixRotateY(angle: number): Matrix;
/** undefined */
declare function matrixRotateZ(angle: number): Matrix;
/** undefined */
declare function matrixRotateXYZ(angle: Vector3): Matrix;
/** undefined */
declare function matrixRotateZYX(angle: Vector3): Matrix;
/** undefined */
declare function matrixScale(x: number, y: number, z: number): Matrix;
/** undefined */
declare function matrixFrustum(left: number, right: number, bottom: number, top: number, nearPlane: number, farPlane: number): Matrix;
/** undefined */
declare function matrixPerspective(fovY: number, aspect: number, nearPlane: number, farPlane: number): Matrix;
/** undefined */
declare function matrixOrtho(left: number, right: number, bottom: number, top: number, nearPlane: number, farPlane: number): Matrix;
/** undefined */
declare function matrixLookAt(eye: Vector3, target: Vector3, up: Vector3): Matrix;
/** undefined */
declare function quaternionAdd(q1: Vector4, q2: Vector4): Vector4;
/** undefined */
declare function quaternionAddValue(q: Vector4, add: number): Vector4;
/** undefined */
declare function quaternionSubtract(q1: Vector4, q2: Vector4): Vector4;
/** undefined */
declare function quaternionSubtractValue(q: Vector4, sub: number): Vector4;
/** undefined */
declare function quaternionIdentity(): Vector4;
/** undefined */
declare function quaternionLength(q: Vector4): number;
/** undefined */
declare function quaternionNormalize(q: Vector4): Vector4;
/** undefined */
declare function quaternionInvert(q: Vector4): Vector4;
/** undefined */
declare function quaternionMultiply(q1: Vector4, q2: Vector4): Vector4;
/** undefined */
declare function quaternionScale(q: Vector4, mul: number): Vector4;
/** undefined */
declare function quaternionDivide(q1: Vector4, q2: Vector4): Vector4;
/** undefined */
declare function quaternionLerp(q1: Vector4, q2: Vector4, amount: number): Vector4;
/** undefined */
declare function quaternionNlerp(q1: Vector4, q2: Vector4, amount: number): Vector4;
/** undefined */
declare function quaternionSlerp(q1: Vector4, q2: Vector4, amount: number): Vector4;
/** undefined */
declare function quaternionCubicHermiteSpline(q1: Vector4, outTangent1: Vector4, q2: Vector4, inTangent2: Vector4, t: number): Vector4;
/** undefined */
declare function quaternionFromVector3ToVector3(from: Vector3, to: Vector3): Vector4;
/** undefined */
declare function quaternionFromMatrix(mat: Matrix): Vector4;
/** undefined */
declare function quaternionToMatrix(q: Vector4): Matrix;
/** undefined */
declare function quaternionFromAxisAngle(axis: Vector3, angle: number): Vector4;
/** undefined */
declare function quaternionToAxisAngle(q: Vector4, outAxis: Vector3, outAngle: ArrayBuffer): void;
/** undefined */
declare function quaternionFromEuler(pitch: number, yaw: number, roll: number): Vector4;
/** undefined */
declare function quaternionToEuler(q: Vector4): Vector3;
/** undefined */
declare function quaternionTransform(q: Vector4, mat: Matrix): Vector4;
/** undefined */
declare function quaternionEquals(p: Vector4, q: Vector4): number;
/** undefined */
declare function matrixDecompose(mat: Matrix, translation: Vector3 &, rotation: Quaternion &, scale: Vector3 &): void;
