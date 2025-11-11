declare module "rayjs:rlgl" {
import type {Matrix} from 'rayjs:raylib';
interface rlVertexBuffer {
elementCount: number,
vertices: number[],
texcoords: number[],
normals: number[],
colors: number[],
indices: number[],
vaoId: number,
vboId: [number,number,number,number,number],
}
var rlVertexBuffer: {
prototype: rlVertexBuffer
new(elementCount?: number, vertices?: number[], texcoords?: number[], normals?: number[], colors?: number[], indices?: number[], vaoId?: number, vboId?: [number,number,number,number,number]): rlVertexBuffer
}
interface rlDrawCall {
mode: number,
vertexCount: number,
vertexAlignment: number,
textureId: number,
}
var rlDrawCall: {
prototype: rlDrawCall
new(mode?: number, vertexCount?: number, vertexAlignment?: number, textureId?: number): rlDrawCall
}
interface rlRenderBatch {
bufferCount: number,
currentBuffer: number,
vertexBuffer: rlVertexBuffer[],
draws: rlDrawCall[],
drawCounter: number,
currentDepth: number,
}
var rlRenderBatch: {
prototype: rlRenderBatch
new(bufferCount?: number, currentBuffer?: number, vertexBuffer?: rlVertexBuffer[], draws?: rlDrawCall[], drawCounter?: number, currentDepth?: number): rlRenderBatch
}
/** undefined */
function rlMatrixMode(mode: number): void/** undefined */
function rlPushMatrix(): void/** undefined */
function rlPopMatrix(): void/** undefined */
function rlLoadIdentity(): void/** undefined */
function rlTranslatef(x: number, y: number, z: number): void/** undefined */
function rlRotatef(angle: number, x: number, y: number, z: number): void/** undefined */
function rlScalef(x: number, y: number, z: number): void/** undefined */
function rlMultMatrixf(matf: number[]): void/** undefined */
function rlFrustum(left: number, right: number, bottom: number, top: number, znear: number, zfar: number): void/** undefined */
function rlOrtho(left: number, right: number, bottom: number, top: number, znear: number, zfar: number): void/** undefined */
function rlViewport(x: number, y: number, width: number, height: number): void/** undefined */
function rlSetClipPlanes(nearPlane: number, farPlane: number): void/** undefined */
function rlGetCullDistanceNear(): number/** undefined */
function rlGetCullDistanceFar(): number/** undefined */
function rlBegin(mode: number): void/** undefined */
function rlEnd(): void/** undefined */
function rlVertex2i(x: number, y: number): void/** undefined */
function rlVertex2f(x: number, y: number): void/** undefined */
function rlVertex3f(x: number, y: number, z: number): void/** undefined */
function rlTexCoord2f(x: number, y: number): void/** undefined */
function rlNormal3f(x: number, y: number, z: number): void/** undefined */
function rlColor4ub(r: number, g: number, b: number, a: number): void/** undefined */
function rlColor3f(x: number, y: number, z: number): void/** undefined */
function rlColor4f(x: number, y: number, z: number, w: number): void/** undefined */
function rlEnableVertexArray(vaoId: number): boolean/** undefined */
function rlDisableVertexArray(): void/** undefined */
function rlEnableVertexBuffer(id: number): void/** undefined */
function rlDisableVertexBuffer(): void/** undefined */
function rlEnableVertexBufferElement(id: number): void/** undefined */
function rlDisableVertexBufferElement(): void/** undefined */
function rlEnableVertexAttribute(index: number): void/** undefined */
function rlDisableVertexAttribute(index: number): void/** undefined */
function rlActiveTextureSlot(slot: number): void/** undefined */
function rlEnableTexture(id: number): void/** undefined */
function rlDisableTexture(): void/** undefined */
function rlEnableTextureCubemap(id: number): void/** undefined */
function rlDisableTextureCubemap(): void/** undefined */
function rlTextureParameters(id: number, param: number, value: number): void/** undefined */
function rlCubemapParameters(id: number, param: number, value: number): void/** undefined */
function rlEnableShader(id: number): void/** undefined */
function rlDisableShader(): void/** undefined */
function rlEnableFramebuffer(id: number): void/** undefined */
function rlDisableFramebuffer(): void/** undefined */
function rlGetActiveFramebuffer(): number/** undefined */
function rlActiveDrawBuffers(count: number): void/** undefined */
function rlBlitFramebuffer(srcX: number, srcY: number, srcWidth: number, srcHeight: number, dstX: number, dstY: number, dstWidth: number, dstHeight: number, bufferMask: number): void/** undefined */
function rlBindFramebuffer(target: number, framebuffer: number): void/** undefined */
function rlEnableColorBlend(): void/** undefined */
function rlDisableColorBlend(): void/** undefined */
function rlEnableDepthTest(): void/** undefined */
function rlDisableDepthTest(): void/** undefined */
function rlEnableDepthMask(): void/** undefined */
function rlDisableDepthMask(): void/** undefined */
function rlEnableBackfaceCulling(): void/** undefined */
function rlDisableBackfaceCulling(): void/** undefined */
function rlColorMask(r: boolean, g: boolean, b: boolean, a: boolean): void/** undefined */
function rlSetCullFace(mode: number): void/** undefined */
function rlEnableScissorTest(): void/** undefined */
function rlDisableScissorTest(): void/** undefined */
function rlScissor(x: number, y: number, width: number, height: number): void/** undefined */
function rlEnablePointMode(): void/** undefined */
function rlDisablePointMode(): void/** undefined */
function rlEnableWireMode(): void/** undefined */
function rlDisableWireMode(): void/** undefined */
function rlSetLineWidth(width: number): void/** undefined */
function rlGetLineWidth(): number/** undefined */
function rlEnableSmoothLines(): void/** undefined */
function rlDisableSmoothLines(): void/** undefined */
function rlEnableStereoRender(): void/** undefined */
function rlDisableStereoRender(): void/** undefined */
function rlIsStereoRenderEnabled(): boolean/** undefined */
function rlClearColor(r: number, g: number, b: number, a: number): void/** undefined */
function rlClearScreenBuffers(): void/** undefined */
function rlCheckErrors(): void/** undefined */
function rlSetBlendMode(mode: number): void/** undefined */
function rlSetBlendFactors(glSrcFactor: number, glDstFactor: number, glEquation: number): void/** undefined */
function rlSetBlendFactorsSeparate(glSrcRGB: number, glDstRGB: number, glSrcAlpha: number, glDstAlpha: number, glEqRGB: number, glEqAlpha: number): void/** undefined */
function rlglInit(width: number, height: number): void/** undefined */
function rlglClose(): void/** undefined */
function rlGetVersion(): number/** undefined */
function rlSetFramebufferWidth(width: number): void/** undefined */
function rlGetFramebufferWidth(): number/** undefined */
function rlSetFramebufferHeight(height: number): void/** undefined */
function rlGetFramebufferHeight(): number/** undefined */
function rlGetTextureIdDefault(): number/** undefined */
function rlGetShaderIdDefault(): number/** undefined */
function rlGetShaderLocsDefault(): number[]/** undefined */
function rlLoadRenderBatch(numBuffers: number, bufferElements: number): rlRenderBatch/** undefined */
function rlUnloadRenderBatch(batch: rlRenderBatch): void/** undefined */
function rlDrawRenderBatch(batch: rlRenderBatch[]): void/** undefined */
function rlSetRenderBatchActive(batch: rlRenderBatch[]): void/** undefined */
function rlDrawRenderBatchActive(): void/** undefined */
function rlCheckRenderBatchLimit(vCount: number): boolean/** undefined */
function rlSetTexture(id: number): void/** undefined */
function rlLoadVertexArray(): number/** undefined */
function rlLoadVertexBuffer(buffer: ArrayBuffer, size: number, dynamic: boolean): number/** undefined */
function rlLoadVertexBufferElement(buffer: ArrayBuffer, size: number, dynamic: boolean): number/** undefined */
function rlUpdateVertexBuffer(bufferId: number, data: ArrayBuffer, dataSize: number, offset: number): void/** undefined */
function rlUpdateVertexBufferElements(id: number, data: ArrayBuffer, dataSize: number, offset: number): void/** undefined */
function rlUnloadVertexArray(vaoId: number): void/** undefined */
function rlUnloadVertexBuffer(vboId: number): void/** undefined */
function rlSetVertexAttribute(index: number, compSize: number, type: number, normalized: boolean, stride: number, offset: number): void/** undefined */
function rlSetVertexAttributeDivisor(index: number, divisor: number): void/** undefined */
function rlDrawVertexArray(offset: number, count: number): void/** undefined */
function rlDrawVertexArrayElements(offset: number, count: number, buffer: ArrayBuffer): void/** undefined */
function rlDrawVertexArrayInstanced(offset: number, count: number, instances: number): void/** undefined */
function rlDrawVertexArrayElementsInstanced(offset: number, count: number, buffer: ArrayBuffer, instances: number): void/** undefined */
function rlLoadTexture(data: ArrayBuffer, width: number, height: number, format: number, mipmapCount: number): number/** undefined */
function rlLoadTextureDepth(width: number, height: number, useRenderBuffer: boolean): number/** undefined */
function rlLoadTextureCubemap(data: ArrayBuffer, size: number, format: number, mipmapCount: number): number/** undefined */
function rlUpdateTexture(id: number, offsetX: number, offsetY: number, width: number, height: number, format: number, data: ArrayBuffer): void/** undefined */
function rlGetGlTextureFormats(format: number, glInternalFormat: number[], glFormat: number[], glType: number[]): void/** undefined */
function rlGetPixelFormatName(format: number): string/** undefined */
function rlUnloadTexture(id: number): void/** undefined */
function rlGenTextureMipmaps(id: number, width: number, height: number, format: number, mipmaps: number[]): void/** undefined */
function rlReadTexturePixels(id: number, width: number, height: number, format: number): number[]/** undefined */
function rlReadScreenPixels(width: number, height: number): string/** undefined */
function rlLoadFramebuffer(): number/** undefined */
function rlFramebufferAttach(fboId: number, texId: number, attachType: number, texType: number, mipLevel: number): void/** undefined */
function rlFramebufferComplete(id: number): boolean/** undefined */
function rlUnloadFramebuffer(id: number): void/** undefined */
function rlLoadShaderCode(vsCode: string, fsCode: string): number/** undefined */
function rlCompileShader(shaderCode: string, type: number): number/** undefined */
function rlLoadShaderProgram(vShaderId: number, fShaderId: number): number/** undefined */
function rlUnloadShaderProgram(id: number): void/** undefined */
function rlGetLocationUniform(shaderId: number, uniformName: string): number/** undefined */
function rlGetLocationAttrib(shaderId: number, attribName: string): number/** undefined */
function rlSetUniform(locIndex: number, value: ArrayBuffer, uniformType: number, count: number): void/** undefined */
function rlSetUniformMatrix(locIndex: number, mat: Matrix): void/** undefined */
function rlSetUniformMatrices(locIndex: number, mat: Matrix[], count: number): void/** undefined */
function rlSetUniformSampler(locIndex: number, textureId: number): void/** undefined */
function rlSetShader(id: number, locs: number[]): void/** undefined */
function rlLoadComputeShaderProgram(shaderId: number): number/** undefined */
function rlComputeShaderDispatch(groupX: number, groupY: number, groupZ: number): void/** undefined */
function rlLoadShaderBuffer(size: number, data: ArrayBuffer, usageHint: number): number/** undefined */
function rlUnloadShaderBuffer(ssboId: number): void/** undefined */
function rlUpdateShaderBuffer(id: number, data: ArrayBuffer, dataSize: number, offset: number): void/** undefined */
function rlBindShaderBuffer(id: number, index: number): void/** undefined */
function rlReadShaderBuffer(id: number, dest: ArrayBuffer, count: number, offset: number): void/** undefined */
function rlCopyShaderBuffer(destId: number, srcId: number, destOffset: number, srcOffset: number, count: number): void/** undefined */
function rlGetShaderBufferSize(id: number): number/** undefined */
function rlBindImageTexture(id: number, index: number, format: number, readonly: boolean): void/** undefined */
function rlGetMatrixModelview(): Matrix/** undefined */
function rlGetMatrixProjection(): Matrix/** undefined */
function rlGetMatrixTransform(): Matrix/** undefined */
function rlGetMatrixProjectionStereo(eye: number): Matrix/** undefined */
function rlGetMatrixViewOffsetStereo(eye: number): Matrix/** undefined */
function rlSetMatrixProjection(proj: Matrix): void/** undefined */
function rlSetMatrixModelview(view: Matrix): void/** undefined */
function rlSetMatrixProjectionStereo(right: Matrix, left: Matrix): void/** undefined */
function rlSetMatrixViewOffsetStereo(right: Matrix, left: Matrix): void/** undefined */
function rlLoadDrawCube(): void/** undefined */
function rlLoadDrawQuad(): void/**  */
var RL_OPENGL_11: number/**  */
var RL_OPENGL_21: number/**  */
var RL_OPENGL_33: number/**  */
var RL_OPENGL_43: number/**  */
var RL_OPENGL_ES_20: number/**  */
var RL_OPENGL_ES_30: number/**  */
var RL_LOG_ALL: number/**  */
var RL_LOG_TRACE: number/**  */
var RL_LOG_DEBUG: number/**  */
var RL_LOG_INFO: number/**  */
var RL_LOG_WARNING: number/**  */
var RL_LOG_ERROR: number/**  */
var RL_LOG_FATAL: number/**  */
var RL_LOG_NONE: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_R5G6B5: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_R5G5B5A1: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_R4G4B4A4: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_R32: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32A32: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_R16: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16: number/**  */
var RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16A16: number/**  */
var RL_PIXELFORMAT_COMPRESSED_DXT1_RGB: number/**  */
var RL_PIXELFORMAT_COMPRESSED_DXT1_RGBA: number/**  */
var RL_PIXELFORMAT_COMPRESSED_DXT3_RGBA: number/**  */
var RL_PIXELFORMAT_COMPRESSED_DXT5_RGBA: number/**  */
var RL_PIXELFORMAT_COMPRESSED_ETC1_RGB: number/**  */
var RL_PIXELFORMAT_COMPRESSED_ETC2_RGB: number/**  */
var RL_PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA: number/**  */
var RL_PIXELFORMAT_COMPRESSED_PVRT_RGB: number/**  */
var RL_PIXELFORMAT_COMPRESSED_PVRT_RGBA: number/**  */
var RL_PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA: number/**  */
var RL_PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA: number/**  */
var RL_TEXTURE_FILTER_POINT: number/**  */
var RL_TEXTURE_FILTER_BILINEAR: number/**  */
var RL_TEXTURE_FILTER_TRILINEAR: number/**  */
var RL_TEXTURE_FILTER_ANISOTROPIC_4X: number/**  */
var RL_TEXTURE_FILTER_ANISOTROPIC_8X: number/**  */
var RL_TEXTURE_FILTER_ANISOTROPIC_16X: number/**  */
var RL_BLEND_ALPHA: number/**  */
var RL_BLEND_ADDITIVE: number/**  */
var RL_BLEND_MULTIPLIED: number/**  */
var RL_BLEND_ADD_COLORS: number/**  */
var RL_BLEND_SUBTRACT_COLORS: number/**  */
var RL_BLEND_ALPHA_PREMULTIPLY: number/**  */
var RL_BLEND_CUSTOM: number/**  */
var RL_BLEND_CUSTOM_SEPARATE: number/**  */
var RL_SHADER_LOC_VERTEX_POSITION: number/**  */
var RL_SHADER_LOC_VERTEX_TEXCOORD01: number/**  */
var RL_SHADER_LOC_VERTEX_TEXCOORD02: number/**  */
var RL_SHADER_LOC_VERTEX_NORMAL: number/**  */
var RL_SHADER_LOC_VERTEX_TANGENT: number/**  */
var RL_SHADER_LOC_VERTEX_COLOR: number/**  */
var RL_SHADER_LOC_MATRIX_MVP: number/**  */
var RL_SHADER_LOC_MATRIX_VIEW: number/**  */
var RL_SHADER_LOC_MATRIX_PROJECTION: number/**  */
var RL_SHADER_LOC_MATRIX_MODEL: number/**  */
var RL_SHADER_LOC_MATRIX_NORMAL: number/**  */
var RL_SHADER_LOC_VECTOR_VIEW: number/**  */
var RL_SHADER_LOC_COLOR_DIFFUSE: number/**  */
var RL_SHADER_LOC_COLOR_SPECULAR: number/**  */
var RL_SHADER_LOC_COLOR_AMBIENT: number/**  */
var RL_SHADER_LOC_MAP_ALBEDO: number/**  */
var RL_SHADER_LOC_MAP_METALNESS: number/**  */
var RL_SHADER_LOC_MAP_NORMAL: number/**  */
var RL_SHADER_LOC_MAP_ROUGHNESS: number/**  */
var RL_SHADER_LOC_MAP_OCCLUSION: number/**  */
var RL_SHADER_LOC_MAP_EMISSION: number/**  */
var RL_SHADER_LOC_MAP_HEIGHT: number/**  */
var RL_SHADER_LOC_MAP_CUBEMAP: number/**  */
var RL_SHADER_LOC_MAP_IRRADIANCE: number/**  */
var RL_SHADER_LOC_MAP_PREFILTER: number/**  */
var RL_SHADER_LOC_MAP_BRDF: number/**  */
var RL_SHADER_LOC_MAP_DIFFUSE: number/**  */
var RL_SHADER_LOC_MAP_SPECULAR: number/**  */
var RL_SHADER_UNIFORM_FLOAT: number/**  */
var RL_SHADER_UNIFORM_VEC2: number/**  */
var RL_SHADER_UNIFORM_VEC3: number/**  */
var RL_SHADER_UNIFORM_VEC4: number/**  */
var RL_SHADER_UNIFORM_INT: number/**  */
var RL_SHADER_UNIFORM_IVEC2: number/**  */
var RL_SHADER_UNIFORM_IVEC3: number/**  */
var RL_SHADER_UNIFORM_IVEC4: number/**  */
var RL_SHADER_UNIFORM_UINT: number/**  */
var RL_SHADER_UNIFORM_UIVEC2: number/**  */
var RL_SHADER_UNIFORM_UIVEC3: number/**  */
var RL_SHADER_UNIFORM_UIVEC4: number/**  */
var RL_SHADER_UNIFORM_SAMPLER2D: number/**  */
var RL_SHADER_ATTRIB_FLOAT: number/**  */
var RL_SHADER_ATTRIB_VEC2: number/**  */
var RL_SHADER_ATTRIB_VEC3: number/**  */
var RL_SHADER_ATTRIB_VEC4: number/**  */
var RL_ATTACHMENT_COLOR_CHANNEL0: number/**  */
var RL_ATTACHMENT_COLOR_CHANNEL1: number/**  */
var RL_ATTACHMENT_COLOR_CHANNEL2: number/**  */
var RL_ATTACHMENT_COLOR_CHANNEL3: number/**  */
var RL_ATTACHMENT_COLOR_CHANNEL4: number/**  */
var RL_ATTACHMENT_COLOR_CHANNEL5: number/**  */
var RL_ATTACHMENT_COLOR_CHANNEL6: number/**  */
var RL_ATTACHMENT_COLOR_CHANNEL7: number/**  */
var RL_ATTACHMENT_DEPTH: number/**  */
var RL_ATTACHMENT_STENCIL: number/**  */
var RL_ATTACHMENT_CUBEMAP_POSITIVE_X: number/**  */
var RL_ATTACHMENT_CUBEMAP_NEGATIVE_X: number/**  */
var RL_ATTACHMENT_CUBEMAP_POSITIVE_Y: number/**  */
var RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y: number/**  */
var RL_ATTACHMENT_CUBEMAP_POSITIVE_Z: number/**  */
var RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z: number/**  */
var RL_ATTACHMENT_TEXTURE2D: number/**  */
var RL_ATTACHMENT_RENDERBUFFER: number/**  */
var RL_CULL_FACE_FRONT: number/**  */
var RL_CULL_FACE_BACK: number/**  */
var RL_DEFAULT_BATCH_BUFFER_ELEMENTS: number/**  */
var RL_TEXTURE_WRAP_S: number/**  */
var RL_TEXTURE_WRAP_T: number/**  */
var RL_TEXTURE_MAG_FILTER: number/**  */
var RL_TEXTURE_MIN_FILTER: number/**  */
var RL_TEXTURE_FILTER_NEAREST: number/**  */
var RL_TEXTURE_FILTER_LINEAR: number/**  */
var RL_TEXTURE_FILTER_MIP_NEAREST: number/**  */
var RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR: number/**  */
var RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST: number/**  */
var RL_TEXTURE_FILTER_MIP_LINEAR: number/**  */
var RL_TEXTURE_FILTER_ANISOTROPIC: number/**  */
var RL_TEXTURE_MIPMAP_BIAS_RATIO: number/**  */
var RL_TEXTURE_WRAP_REPEAT: number/**  */
var RL_TEXTURE_WRAP_CLAMP: number/**  */
var RL_TEXTURE_WRAP_MIRROR_REPEAT: number/**  */
var RL_TEXTURE_WRAP_MIRROR_CLAMP: number/**  */
var RL_MODELVIEW: number/**  */
var RL_PROJECTION: number/**  */
var RL_TEXTURE: number/**  */
var RL_LINES: number/**  */
var RL_TRIANGLES: number/**  */
var RL_QUADS: number/**  */
var RL_UNSIGNED_BYTE: number/**  */
var RL_FLOAT: number/**  */
var RL_STREAM_DRAW: number/**  */
var RL_STREAM_READ: number/**  */
var RL_STREAM_COPY: number/**  */
var RL_STATIC_DRAW: number/**  */
var RL_STATIC_READ: number/**  */
var RL_STATIC_COPY: number/**  */
var RL_DYNAMIC_DRAW: number/**  */
var RL_DYNAMIC_READ: number/**  */
var RL_DYNAMIC_COPY: number/**  */
var RL_FRAGMENT_SHADER: number/**  */
var RL_VERTEX_SHADER: number/**  */
var RL_COMPUTE_SHADER: number/**  */
var RL_ZERO: number/**  */
var RL_ONE: number/**  */
var RL_SRC_COLOR: number/**  */
var RL_ONE_MINUS_SRC_COLOR: number/**  */
var RL_SRC_ALPHA: number/**  */
var RL_ONE_MINUS_SRC_ALPHA: number/**  */
var RL_DST_ALPHA: number/**  */
var RL_ONE_MINUS_DST_ALPHA: number/**  */
var RL_DST_COLOR: number/**  */
var RL_ONE_MINUS_DST_COLOR: number/**  */
var RL_SRC_ALPHA_SATURATE: number/**  */
var RL_CONSTANT_COLOR: number/**  */
var RL_ONE_MINUS_CONSTANT_COLOR: number/**  */
var RL_CONSTANT_ALPHA: number/**  */
var RL_ONE_MINUS_CONSTANT_ALPHA: number/**  */
var RL_FUNC_ADD: number/**  */
var RL_MIN: number/**  */
var RL_MAX: number/**  */
var RL_FUNC_SUBTRACT: number/**  */
var RL_FUNC_REVERSE_SUBTRACT: number/**  */
var RL_BLEND_EQUATION: number/**  */
var RL_BLEND_EQUATION_RGB: number/**  */
var RL_BLEND_EQUATION_ALPHA: number/**  */
var RL_BLEND_DST_RGB: number/**  */
var RL_BLEND_SRC_RGB: number/**  */
var RL_BLEND_DST_ALPHA: number/**  */
var RL_BLEND_SRC_ALPHA: number/**  */
var RL_BLEND_COLOR: number/**  */
var RL_READ_FRAMEBUFFER: number/**  */
var RL_DRAW_FRAMEBUFFER: number}
