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
declare function getDefaultLightmapperConfig(): LightmapperConfig;
/** undefined */
declare function loadLightmapper(w: number, h: number, mesh: Mesh, cfg: LightmapperConfig): Lightmapper;
/** undefined */
declare function loadMaterialLightmapper(emissiveColor: Color, intensity: number): Material;
/** undefined */
declare function unloadLightmapper(lm: Lightmapper): void;
/** undefined */
declare function beginLightmap(): void;
/** undefined */
declare function endLightmap(): void;
/** undefined */
declare function beginLightmapFragment(lm: Lightmapper &): boolean;
/** undefined */
declare function endLightmapFragment(lm: Lightmapper &): void;
/** undefined */
declare function loadImageFromLightmapper(lm: Lightmapper): Image;
