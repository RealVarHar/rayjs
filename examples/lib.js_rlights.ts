interface Light {
    type: number,
    enabled: boolean,
    position: Vector3,
    target: Vector3,
    color: Color,
    attenuation: number,
}
declare var Light: {
    prototype: Light;
}
/** undefined */
declare function CreateLight(type: number, position: Vector3, target: Vector3, color: Color, shader: Shader): Light;
/** undefined */
declare function UpdateLightValues(shader: Shader, light: Light): void;
/**  */
declare var LIGHT_DIRECTIONAL: number;
/**  */
declare var LIGHT_POINT: number;
/**  */
declare var MAX_LIGHTS: number;
