declare module "rayjs:rlightmapper" {
    import type {Mesh,Color,Material,Image} from 'rayjs:raylib';
    interface Lightmapper {
        data: number[],
        w: number,
        h: number,
        progress: number,
    }
    var Lightmapper: {
        prototype: Lightmapper;
        new(data?: number[], w?: number, h?: number, progress?: number): Lightmapper;
    }
    interface LightmapperConfig {
        hemisphereSize: number,
        zNear: number,
        zFar: number,
        backgroundColor: Color,
        interpolationPasses: number,
        interpolationThreshold: number,
        cameraToSurfaceDistanceModifier: number,
    }
    var LightmapperConfig: {
        prototype: LightmapperConfig;
        new(hemisphereSize?: number, zNear?: number, zFar?: number, backgroundColor?: Color, interpolationPasses?: number, interpolationThreshold?: number, cameraToSurfaceDistanceModifier?: number): LightmapperConfig;
    }
    /** undefined */
    function GetDefaultLightmapperConfig(): LightmapperConfig;
    /** undefined */
    function LoadLightmapper(w: number, h: number, mesh: Mesh, cfg: LightmapperConfig): Lightmapper;
    /** undefined */
    function LoadMaterialLightmapper(emissiveColor: Color, intensity: number): Material;
    /** undefined */
    function UnloadLightmapper(lm: Lightmapper): void;
    /** undefined */
    function BeginLightmap(): void;
    /** undefined */
    function EndLightmap(): void;
    /** undefined */
    function BeginLightmapFragment(lm: Lightmapper): boolean;
    /** undefined */
    function EndLightmapFragment(lm: Lightmapper): void;
    /** undefined */
    function LoadImageFromLightmapper(lm: Lightmapper): Image;
}
