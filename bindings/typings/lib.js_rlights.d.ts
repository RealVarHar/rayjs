declare module "rayjs:rlights" {
import type {Vector3,Color,Shader} from 'rayjs:raylib';
interface Light {
type: number,
enabled: boolean,
position: Vector3,
target: Vector3,
color: Color,
attenuation: number,
enabledLoc: number,
typeLoc: number,
positionLoc: number,
targetLoc: number,
colorLoc: number,
attenuationLoc: number,
}
var Light: {
prototype: Light
new(type?: number, enabled?: boolean, position?: Vector3, target?: Vector3, color?: Color, attenuation?: number, enabledLoc?: number, typeLoc?: number, positionLoc?: number, targetLoc?: number, colorLoc?: number, attenuationLoc?: number): Light
}
/** Create a light and get shader locations */
function CreateLight(type: number, position: Vector3, target: Vector3, color: Color, shader: Shader): Light/** NOTE: Light shader locations should be available */
function UpdateLightValues(shader: Shader, light: Light): void/**  */
var LIGHT_DIRECTIONAL: number/**  */
var LIGHT_POINT: number/** Max dynamic lights supported by shader */
var MAX_LIGHTS: number}
