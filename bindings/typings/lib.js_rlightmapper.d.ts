declare module "rayjs:rlightmapper" {
import type {Mesh,Color,Material,Image} from 'rayjs:raylib';
interface Lightmapper {
data: number[],
w: number,
h: number,
progress: number,
}
var Lightmapper: {
prototype: Lightmapper
new(data?: number[], w?: number, h?: number, progress?: number): Lightmapper
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
prototype: LightmapperConfig
new(hemisphereSize?: number, zNear?: number, zFar?: number, backgroundColor?: Color, interpolationPasses?: number, interpolationThreshold?: number, cameraToSurfaceDistanceModifier?: number): LightmapperConfig
}
/** ... */
function GetDefaultLightmapperConfig(): LightmapperConfig/** ... */
function LoadLightmapper(w: number, h: number, mesh: Mesh, cfg: LightmapperConfig): Lightmapper/** ... */
function LoadMaterialLightmapper(emissiveColor: Color, intensity: number): Material/** ... */
function UnloadLightmapper(lm: Lightmapper): void/** ... */
function BeginLightmap(): void/** ... */
function EndLightmap(): void/** .. */
function BeginLightmapFragment(lm: Lightmapper): boolean/** ... */
function EndLightmapFragment(lm: Lightmapper): void/** ... */
function LoadImageFromLightmapper(lm: Lightmapper): Image}
