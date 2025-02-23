interface Lightmapper {
    w: number,
    h: number,
    progress: number,
}
declare var Lightmapper: {
    prototype: Lightmapper;
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
declare var LightmapperConfig: {
    prototype: LightmapperConfig;
}
/** undefined */
declare function GetDefaultLightmapperConfig(): LightmapperConfig;
/** undefined */
declare function LoadLightmapper(w: number, h: number, mesh: Mesh, cfg: LightmapperConfig): Lightmapper;
/** undefined */
declare function LoadMaterialLightmapper(emissiveColor: Color, intensity: number): Material;
/** undefined */
declare function UnloadLightmapper(lm: Lightmapper): void;
/** undefined */
declare function BeginLightmap(): void;
/** undefined */
declare function EndLightmap(): void;
/** undefined */
declare function BeginLightmapFragment(lm: Lightmapper &): boolean;
/** undefined */
declare function EndLightmapFragment(lm: Lightmapper &): void;
/** undefined */
declare function LoadImageFromLightmapper(lm: Lightmapper): Image;
