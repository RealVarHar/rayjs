declare module "rayjs:rlights" {
    import type {Vector3,Color,Shader} from 'rayjs:raylib';
    interface Light {
        type: number,
        enabled: boolean,
        position: Vector3,
        target: Vector3,
        color: Color,
        attenuation: number,
    }
    var Light: {
        prototype: Light;
        new(type?: number, enabled?: boolean, position?: Vector3, target?: Vector3, color?: Color, attenuation?: number): Light;
    }
    /** undefined */
    function CreateLight(type: number, position: Vector3, target: Vector3, color: Color, shader: Shader): Light;
    /** undefined */
    function UpdateLightValues(shader: Shader, light: Light): void;
    /**  */
    var LIGHT_DIRECTIONAL: number;
    /**  */
    var LIGHT_POINT: number;
    /**  */
    var MAX_LIGHTS: number;
}
