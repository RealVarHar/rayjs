declare module "rayjs:rlightmapper" {
import type {LightmapperConfig,Mesh,Lightmapper,Color,Material,Image} from '[object Object]'interface Lightmapper {
}
var Lightmapper: {
prototype: Lightmappernew(): Lightmapper}
interface LightmapperConfig {
}
var LightmapperConfig: {
prototype: LightmapperConfignew(): LightmapperConfig}
/** undefined */
function GetDefaultLightmapperConfig(): LightmapperConfig/** undefined */
function LoadLightmapper(w: number, h: number, mesh: Mesh, cfg: LightmapperConfig): Lightmapper/** undefined */
function LoadMaterialLightmapper(emissiveColor: Color, intensity: number): Material/** undefined */
function UnloadLightmapper(lm: Lightmapper): void/** undefined */
function BeginLightmap(): void/** undefined */
function EndLightmap(): void/** undefined */
function BeginLightmapFragment(lm: Lightmapper): boolean/** undefined */
function EndLightmapFragment(lm: Lightmapper): void/** undefined */
function LoadImageFromLightmapper(lm: Lightmapper): Image}
