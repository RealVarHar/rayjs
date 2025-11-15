declare module "rayjs:rlgl" {
import type {Matrix} from 'rayjs:raylib';
interface rlVertexBuffer {
/** Number of elements in the buffer (QUADS) */
elementCount: number,
/** Vertex position (XYZ - 3 components per vertex) (shader-location = 0) */
vertices: number[],
/** Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1) */
texcoords: number[],
/** Vertex normal (XYZ - 3 components per vertex) (shader-location = 2) */
normals: number[],
/** Vertex colors (RGBA - 4 components per vertex) (shader-location = 3) */
colors: number[],
/** Vertex indices (in case vertex data comes indexed) (6 indices per quad) */
indices: number[],
/** Vertex indices (in case vertex data comes indexed) (6 indices per quad) */
vaoId: number,
vboId: [number,number,number,number,number],
}
var rlVertexBuffer: {
prototype: rlVertexBuffer
new(elementCount?: number, vertices?: number[], texcoords?: number[], normals?: number[], colors?: number[], indices?: number[], vaoId?: number, vboId?: [number,number,number,number,number]): rlVertexBuffer
}
interface rlDrawCall {
/** Drawing mode: LINES, TRIANGLES, QUADS */
mode: number,
/** Number of vertex of the draw */
vertexCount: number,
/** Number of vertex required for index alignment (LINES, TRIANGLES) */
vertexAlignment: number,
/** Texture id to be used on the draw -> Use to create new draw call if changes */
textureId: number,
}
var rlDrawCall: {
prototype: rlDrawCall
new(mode?: number, vertexCount?: number, vertexAlignment?: number, textureId?: number): rlDrawCall
}
interface rlRenderBatch {
/** Number of vertex buffers (multi-buffering support) */
bufferCount: number,
/** Current buffer tracking in case of multi-buffering */
currentBuffer: number,
/** Dynamic buffer(s) for vertex data */
vertexBuffer: rlVertexBuffer[],
/** Draw calls array, depends on textureId */
draws: rlDrawCall[],
/** Draw calls counter */
drawCounter: number,
/** Current depth value for next draw */
currentDepth: number,
}
var rlRenderBatch: {
prototype: rlRenderBatch
new(bufferCount?: number, currentBuffer?: number, vertexBuffer?: rlVertexBuffer[], draws?: rlDrawCall[], drawCounter?: number, currentDepth?: number): rlRenderBatch
}
/** Choose the current matrix to be transformed */
function rlMatrixMode(mode: number): void/** Push the current matrix to stack */
function rlPushMatrix(): void/** Pop latest inserted matrix from stack */
function rlPopMatrix(): void/** Reset current matrix to identity matrix */
function rlLoadIdentity(): void/** Multiply the current matrix by a translation matrix */
function rlTranslatef(x: number, y: number, z: number): void/** Multiply the current matrix by a rotation matrix */
function rlRotatef(angle: number, x: number, y: number, z: number): void/** Multiply the current matrix by a scaling matrix */
function rlScalef(x: number, y: number, z: number): void/** Multiply the current matrix by another matrix */
function rlMultMatrixf(matf: number[]): void/**  */
function rlFrustum(left: number, right: number, bottom: number, top: number, znear: number, zfar: number): void/**  */
function rlOrtho(left: number, right: number, bottom: number, top: number, znear: number, zfar: number): void/** Set the viewport area */
function rlViewport(x: number, y: number, width: number, height: number): void/** Set clip planes distances */
function rlSetClipPlanes(nearPlane: number, farPlane: number): void/** Get cull plane distance near */
function rlGetCullDistanceNear(): number/** Get cull plane distance far */
function rlGetCullDistanceFar(): number/** Initialize drawing mode (how to organize vertex) */
function rlBegin(mode: number): void/** Finish vertex providing */
function rlEnd(): void/** Define one vertex (position) - 2 int */
function rlVertex2i(x: number, y: number): void/** Define one vertex (position) - 2 float */
function rlVertex2f(x: number, y: number): void/** Define one vertex (position) - 3 float */
function rlVertex3f(x: number, y: number, z: number): void/** Define one vertex (texture coordinate) - 2 float */
function rlTexCoord2f(x: number, y: number): void/** Define one vertex (normal) - 3 float */
function rlNormal3f(x: number, y: number, z: number): void/** Define one vertex (color) - 4 byte */
function rlColor4ub(r: number, g: number, b: number, a: number): void/** Define one vertex (color) - 3 float */
function rlColor3f(x: number, y: number, z: number): void/** Define one vertex (color) - 4 float */
function rlColor4f(x: number, y: number, z: number, w: number): void/** Enable vertex array (VAO, if supported) */
function rlEnableVertexArray(vaoId: number): boolean/** Disable vertex array (VAO, if supported) */
function rlDisableVertexArray(): void/** Enable vertex buffer (VBO) */
function rlEnableVertexBuffer(id: number): void/** Disable vertex buffer (VBO) */
function rlDisableVertexBuffer(): void/** Enable vertex buffer element (VBO element) */
function rlEnableVertexBufferElement(id: number): void/** Disable vertex buffer element (VBO element) */
function rlDisableVertexBufferElement(): void/** Enable vertex attribute index */
function rlEnableVertexAttribute(index: number): void/** Disable vertex attribute index */
function rlDisableVertexAttribute(index: number): void/** Enable attribute state pointer */
function rlEnableStatePointer(vertexAttribType: number, buffer: ArrayBuffer): void/** Disable attribute state pointer */
function rlDisableStatePointer(vertexAttribType: number): void/** Select and active a texture slot */
function rlActiveTextureSlot(slot: number): void/** Enable texture */
function rlEnableTexture(id: number): void/** Disable texture */
function rlDisableTexture(): void/** Enable texture cubemap */
function rlEnableTextureCubemap(id: number): void/** Disable texture cubemap */
function rlDisableTextureCubemap(): void/** Set texture parameters (filter, wrap) */
function rlTextureParameters(id: number, param: number, value: number): void/** Set cubemap parameters (filter, wrap) */
function rlCubemapParameters(id: number, param: number, value: number): void/** Enable shader program */
function rlEnableShader(id: number): void/** Disable shader program */
function rlDisableShader(): void/** Enable render texture (fbo) */
function rlEnableFramebuffer(id: number): void/** Disable render texture (fbo), return to default framebuffer */
function rlDisableFramebuffer(): void/** Get the currently active render texture (fbo), 0 for default framebuffer */
function rlGetActiveFramebuffer(): number/** Activate multiple draw color buffers */
function rlActiveDrawBuffers(count: number): void/** Blit active framebuffer to main framebuffer */
function rlBlitFramebuffer(srcX: number, srcY: number, srcWidth: number, srcHeight: number, dstX: number, dstY: number, dstWidth: number, dstHeight: number, bufferMask: number): void/** Bind framebuffer (FBO) */
function rlBindFramebuffer(target: number, framebuffer: number): void/** Enable color blending */
function rlEnableColorBlend(): void/** Disable color blending */
function rlDisableColorBlend(): void/** Enable depth test */
function rlEnableDepthTest(): void/** Disable depth test */
function rlDisableDepthTest(): void/** Enable depth write */
function rlEnableDepthMask(): void/** Disable depth write */
function rlDisableDepthMask(): void/** Enable backface culling */
function rlEnableBackfaceCulling(): void/** Disable backface culling */
function rlDisableBackfaceCulling(): void/** Color mask control */
function rlColorMask(r: boolean, g: boolean, b: boolean, a: boolean): void/** Set face culling mode */
function rlSetCullFace(mode: number): void/** Enable scissor test */
function rlEnableScissorTest(): void/** Disable scissor test */
function rlDisableScissorTest(): void/** Scissor test */
function rlScissor(x: number, y: number, width: number, height: number): void/** Enable point mode */
function rlEnablePointMode(): void/** Disable point mode */
function rlDisablePointMode(): void/** Set the point drawing size */
function rlSetPointSize(size: number): void/** Get the point drawing size */
function rlGetPointSize(): number/** Enable wire mode */
function rlEnableWireMode(): void/** Disable wire mode */
function rlDisableWireMode(): void/** Set the line drawing width */
function rlSetLineWidth(width: number): void/** Get the line drawing width */
function rlGetLineWidth(): number/** Enable line aliasing */
function rlEnableSmoothLines(): void/** Disable line aliasing */
function rlDisableSmoothLines(): void/** Enable stereo rendering */
function rlEnableStereoRender(): void/** Disable stereo rendering */
function rlDisableStereoRender(): void/** Check if stereo render is enabled */
function rlIsStereoRenderEnabled(): boolean/** Clear color buffer with color */
function rlClearColor(r: number, g: number, b: number, a: number): void/** Clear used screen buffers (color and depth) */
function rlClearScreenBuffers(): void/** Check and log OpenGL error codes */
function rlCheckErrors(): void/** Set blending mode */
function rlSetBlendMode(mode: number): void/** Set blending mode factor and equation (using OpenGL factors) */
function rlSetBlendFactors(glSrcFactor: number, glDstFactor: number, glEquation: number): void/** Set blending mode factors and equations separately (using OpenGL factors) */
function rlSetBlendFactorsSeparate(glSrcRGB: number, glDstRGB: number, glSrcAlpha: number, glDstAlpha: number, glEqRGB: number, glEqAlpha: number): void/** Initialize rlgl (buffers, shaders, textures, states) */
function rlglInit(width: number, height: number): void/** De-initialize rlgl (buffers, shaders, textures) */
function rlglClose(): void/** Get current OpenGL version */
function rlGetVersion(): number/** Set current framebuffer width */
function rlSetFramebufferWidth(width: number): void/** Get default framebuffer width */
function rlGetFramebufferWidth(): number/** Set current framebuffer height */
function rlSetFramebufferHeight(height: number): void/** Get default framebuffer height */
function rlGetFramebufferHeight(): number/** Get default texture id */
function rlGetTextureIdDefault(): number/** Get default shader id */
function rlGetShaderIdDefault(): number/** Get default shader locations */
function rlGetShaderLocsDefault(): number[]/** Load a render batch system */
function rlLoadRenderBatch(numBuffers: number, bufferElements: number): rlRenderBatch/** Unload render batch system */
function rlUnloadRenderBatch(batch: rlRenderBatch): void/** Draw render batch data (Update->Draw->Reset) */
function rlDrawRenderBatch(batch: rlRenderBatch[]): void/** Set the active render batch for rlgl (NULL for default internal) */
function rlSetRenderBatchActive(batch: rlRenderBatch[]): void/** Update and draw internal render batch */
function rlDrawRenderBatchActive(): void/** Check internal buffer overflow for a given number of vertex */
function rlCheckRenderBatchLimit(vCount: number): boolean/** Set current texture for render batch and check buffers limits */
function rlSetTexture(id: number): void/** Load vertex array (vao) if supported */
function rlLoadVertexArray(): number/** Load a vertex buffer object */
function rlLoadVertexBuffer(buffer: ArrayBuffer, size: number, dynamic: boolean): number/** Load vertex buffer elements object */
function rlLoadVertexBufferElement(buffer: ArrayBuffer, size: number, dynamic: boolean): number/** Update vertex buffer object data on GPU buffer */
function rlUpdateVertexBuffer(bufferId: number, data: ArrayBuffer, dataSize: number, offset: number): void/** Update vertex buffer elements data on GPU buffer */
function rlUpdateVertexBufferElements(id: number, data: ArrayBuffer, dataSize: number, offset: number): void/** Unload vertex array (vao) */
function rlUnloadVertexArray(vaoId: number): void/** Unload vertex buffer object */
function rlUnloadVertexBuffer(vboId: number): void/** Set vertex attribute data configuration */
function rlSetVertexAttribute(index: number, compSize: number, type: number, normalized: boolean, stride: number, offset: number): void/** Set vertex attribute data divisor */
function rlSetVertexAttributeDivisor(index: number, divisor: number): void/** Draw vertex array (currently active vao) */
function rlDrawVertexArray(offset: number, count: number): void/** Draw vertex array elements */
function rlDrawVertexArrayElements(offset: number, count: number, buffer: ArrayBuffer): void/** Draw vertex array (currently active vao) with instancing */
function rlDrawVertexArrayInstanced(offset: number, count: number, instances: number): void/** Draw vertex array elements with instancing */
function rlDrawVertexArrayElementsInstanced(offset: number, count: number, buffer: ArrayBuffer, instances: number): void/** Load texture data */
function rlLoadTexture(data: ArrayBuffer, width: number, height: number, format: number, mipmapCount: number): number/** Load depth texture/renderbuffer (to be attached to fbo) */
function rlLoadTextureDepth(width: number, height: number, useRenderBuffer: boolean): number/** Load texture cubemap data */
function rlLoadTextureCubemap(data: ArrayBuffer, size: number, format: number, mipmapCount: number): number/** Update texture with new data on GPU */
function rlUpdateTexture(id: number, offsetX: number, offsetY: number, width: number, height: number, format: number, data: ArrayBuffer): void/** Get OpenGL internal formats */
function rlGetGlTextureFormats(format: number, glInternalFormat: number[], glFormat: number[], glType: number[]): void/** Get name string for pixel format */
function rlGetPixelFormatName(format: number): string/** Unload texture from GPU memory */
function rlUnloadTexture(id: number): void/** Generate mipmap data for selected texture */
function rlGenTextureMipmaps(id: number, width: number, height: number, format: number, mipmaps: number[]): void/** Read texture pixel data */
function rlReadTexturePixels(id: number, width: number, height: number, format: number): number[]/** Read screen pixel data (color buffer) */
function rlReadScreenPixels(width: number, height: number): string/** Load an empty framebuffer */
function rlLoadFramebuffer(): number/** Attach texture/renderbuffer to a framebuffer */
function rlFramebufferAttach(fboId: number, texId: number, attachType: number, texType: number, mipLevel: number): void/** Verify framebuffer is complete */
function rlFramebufferComplete(id: number): boolean/** Delete framebuffer from GPU */
function rlUnloadFramebuffer(id: number): void/** Load shader from code strings */
function rlLoadShaderCode(vsCode: string, fsCode: string): number/** Compile custom shader and return shader id (type: RL_VERTEX_SHADER, RL_FRAGMENT_SHADER, RL_COMPUTE_SHADER) */
function rlCompileShader(shaderCode: string, type: number): number/** Load custom shader program */
function rlLoadShaderProgram(vShaderId: number, fShaderId: number): number/** Unload shader program */
function rlUnloadShaderProgram(id: number): void/** Get shader location uniform, requires shader program id */
function rlGetLocationUniform(shaderId: number, uniformName: string): number/** Get shader location attribute, requires shader program id */
function rlGetLocationAttrib(shaderId: number, attribName: string): number/** Set shader value uniform */
function rlSetUniform(locIndex: number, value: ArrayBuffer, uniformType: number, count: number): void/** Set shader value matrix */
function rlSetUniformMatrix(locIndex: number, mat: Matrix): void/** Set shader value matrices */
function rlSetUniformMatrices(locIndex: number, mat: Matrix[], count: number): void/** Set shader value sampler */
function rlSetUniformSampler(locIndex: number, textureId: number): void/** Set shader currently active (id and locations) */
function rlSetShader(id: number, locs: number[]): void/** Load compute shader program */
function rlLoadComputeShaderProgram(shaderId: number): number/** Dispatch compute shader (equivalent to *draw* for graphics pipeline) */
function rlComputeShaderDispatch(groupX: number, groupY: number, groupZ: number): void/** Load shader storage buffer object (SSBO) */
function rlLoadShaderBuffer(size: number, data: ArrayBuffer, usageHint: number): number/** Unload shader storage buffer object (SSBO) */
function rlUnloadShaderBuffer(ssboId: number): void/** Update SSBO buffer data */
function rlUpdateShaderBuffer(id: number, data: ArrayBuffer, dataSize: number, offset: number): void/** Bind SSBO buffer */
function rlBindShaderBuffer(id: number, index: number): void/** Read SSBO buffer data (GPU->CPU) */
function rlReadShaderBuffer(id: number, dest: ArrayBuffer, count: number, offset: number): void/** Copy SSBO data between buffers */
function rlCopyShaderBuffer(destId: number, srcId: number, destOffset: number, srcOffset: number, count: number): void/** Get SSBO buffer size */
function rlGetShaderBufferSize(id: number): number/** Bind image texture */
function rlBindImageTexture(id: number, index: number, format: number, readonly: boolean): void/** Get internal modelview matrix */
function rlGetMatrixModelview(): Matrix/** Get internal projection matrix */
function rlGetMatrixProjection(): Matrix/** Get internal accumulated transform matrix */
function rlGetMatrixTransform(): Matrix/** Get internal projection matrix for stereo render (selected eye) */
function rlGetMatrixProjectionStereo(eye: number): Matrix/** Get internal view offset matrix for stereo render (selected eye) */
function rlGetMatrixViewOffsetStereo(eye: number): Matrix/** Set a custom projection matrix (replaces internal projection matrix) */
function rlSetMatrixProjection(proj: Matrix): void/** Set a custom modelview matrix (replaces internal modelview matrix) */
function rlSetMatrixModelview(view: Matrix): void/** Set eyes projection matrices for stereo rendering */
function rlSetMatrixProjectionStereo(right: Matrix, left: Matrix): void/** Set eyes view offsets matrices for stereo rendering */
function rlSetMatrixViewOffsetStereo(right: Matrix, left: Matrix): void/** Load and draw a cube */
function rlLoadDrawCube(): void/** Load and draw a quad */
function rlLoadDrawQuad(): void/** Software rendering */
var RL_OPENGL_11_SOFTWARE: number/** OpenGL 1.1 */
var RL_OPENGL_11: number/** OpenGL 2.1 (GLSL 120) */
var RL_OPENGL_21: number/** OpenGL 3.3 (GLSL 330) */
var RL_OPENGL_33: number/** OpenGL 4.3 (using GLSL 330) */
var RL_OPENGL_43: number/** OpenGL ES 2.0 (GLSL 100) */
var RL_OPENGL_ES_20: number/**  */
var RL_OPENGL_ES_30: number/** Display all logs */
var RL_LOG_ALL: number/** Trace logging, intended for internal use only */
var RL_LOG_TRACE: number/** Debug logging, used for internal debugging, it should be disabled on release builds */
var RL_LOG_DEBUG: number/** Info logging, used for program execution info */
var RL_LOG_INFO: number/** Warning logging, used on recoverable failures */
var RL_LOG_WARNING: number/** Error logging, used on unrecoverable failures */
var RL_LOG_ERROR: number/** Fatal logging, used to abort program: exit(EXIT_FAILURE) */
var RL_LOG_FATAL: number/**  */
var RL_LOG_NONE: number/** 8 bit per pixel (no alpha) */
var RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE: number/** 8*2 bpp (2 channels) */
var RL_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA: number/** 16 bpp */
var RL_PIXELFORMAT_UNCOMPRESSED_R5G6B5: number/** 24 bpp */
var RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8: number/** 16 bpp (1 bit alpha) */
var RL_PIXELFORMAT_UNCOMPRESSED_R5G5B5A1: number/** 16 bpp (4 bit alpha) */
var RL_PIXELFORMAT_UNCOMPRESSED_R4G4B4A4: number/** 32 bpp */
var RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8: number/** 32 bpp (1 channel - float) */
var RL_PIXELFORMAT_UNCOMPRESSED_R32: number/** 32*3 bpp (3 channels - float) */
var RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32: number/** 32*4 bpp (4 channels - float) */
var RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32A32: number/** 16 bpp (1 channel - half float) */
var RL_PIXELFORMAT_UNCOMPRESSED_R16: number/** 16*3 bpp (3 channels - half float) */
var RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16: number/** 16*4 bpp (4 channels - half float) */
var RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16A16: number/** 4 bpp (no alpha) */
var RL_PIXELFORMAT_COMPRESSED_DXT1_RGB: number/** 4 bpp (1 bit alpha) */
var RL_PIXELFORMAT_COMPRESSED_DXT1_RGBA: number/** 8 bpp */
var RL_PIXELFORMAT_COMPRESSED_DXT3_RGBA: number/** 8 bpp */
var RL_PIXELFORMAT_COMPRESSED_DXT5_RGBA: number/** 4 bpp */
var RL_PIXELFORMAT_COMPRESSED_ETC1_RGB: number/** 4 bpp */
var RL_PIXELFORMAT_COMPRESSED_ETC2_RGB: number/** 8 bpp */
var RL_PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA: number/** 4 bpp */
var RL_PIXELFORMAT_COMPRESSED_PVRT_RGB: number/** 4 bpp */
var RL_PIXELFORMAT_COMPRESSED_PVRT_RGBA: number/** 8 bpp */
var RL_PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA: number/**  */
var RL_PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA: number/** No filter, just pixel approximation */
var RL_TEXTURE_FILTER_POINT: number/** Linear filtering */
var RL_TEXTURE_FILTER_BILINEAR: number/** Trilinear filtering (linear with mipmaps) */
var RL_TEXTURE_FILTER_TRILINEAR: number/** Anisotropic filtering 4x */
var RL_TEXTURE_FILTER_ANISOTROPIC_4X: number/** Anisotropic filtering 8x */
var RL_TEXTURE_FILTER_ANISOTROPIC_8X: number/** Anisotropic filtering 16x */
var RL_TEXTURE_FILTER_ANISOTROPIC_16X: number/** Blend textures considering alpha (default) */
var RL_BLEND_ALPHA: number/** Blend textures adding colors */
var RL_BLEND_ADDITIVE: number/** Blend textures multiplying colors */
var RL_BLEND_MULTIPLIED: number/** Blend textures adding colors (alternative) */
var RL_BLEND_ADD_COLORS: number/** Blend textures subtracting colors (alternative) */
var RL_BLEND_SUBTRACT_COLORS: number/** Blend premultiplied textures considering alpha */
var RL_BLEND_ALPHA_PREMULTIPLY: number/** Blend textures using custom src/dst factors (use rlSetBlendFactors()) */
var RL_BLEND_CUSTOM: number/**  */
var RL_BLEND_CUSTOM_SEPARATE: number/** Shader location: vertex attribute: position */
var RL_SHADER_LOC_VERTEX_POSITION: number/** Shader location: vertex attribute: texcoord01 */
var RL_SHADER_LOC_VERTEX_TEXCOORD01: number/** Shader location: vertex attribute: texcoord02 */
var RL_SHADER_LOC_VERTEX_TEXCOORD02: number/** Shader location: vertex attribute: normal */
var RL_SHADER_LOC_VERTEX_NORMAL: number/** Shader location: vertex attribute: tangent */
var RL_SHADER_LOC_VERTEX_TANGENT: number/** Shader location: vertex attribute: color */
var RL_SHADER_LOC_VERTEX_COLOR: number/** Shader location: matrix uniform: model-view-projection */
var RL_SHADER_LOC_MATRIX_MVP: number/** Shader location: matrix uniform: view (camera transform) */
var RL_SHADER_LOC_MATRIX_VIEW: number/** Shader location: matrix uniform: projection */
var RL_SHADER_LOC_MATRIX_PROJECTION: number/** Shader location: matrix uniform: model (transform) */
var RL_SHADER_LOC_MATRIX_MODEL: number/** Shader location: matrix uniform: normal */
var RL_SHADER_LOC_MATRIX_NORMAL: number/** Shader location: vector uniform: view */
var RL_SHADER_LOC_VECTOR_VIEW: number/** Shader location: vector uniform: diffuse color */
var RL_SHADER_LOC_COLOR_DIFFUSE: number/** Shader location: vector uniform: specular color */
var RL_SHADER_LOC_COLOR_SPECULAR: number/** Shader location: vector uniform: ambient color */
var RL_SHADER_LOC_COLOR_AMBIENT: number/** Shader location: sampler2d texture: albedo (same as: RL_SHADER_LOC_MAP_DIFFUSE) */
var RL_SHADER_LOC_MAP_ALBEDO: number/** Shader location: sampler2d texture: metalness (same as: RL_SHADER_LOC_MAP_SPECULAR) */
var RL_SHADER_LOC_MAP_METALNESS: number/** Shader location: sampler2d texture: normal */
var RL_SHADER_LOC_MAP_NORMAL: number/** Shader location: sampler2d texture: roughness */
var RL_SHADER_LOC_MAP_ROUGHNESS: number/** Shader location: sampler2d texture: occlusion */
var RL_SHADER_LOC_MAP_OCCLUSION: number/** Shader location: sampler2d texture: emission */
var RL_SHADER_LOC_MAP_EMISSION: number/** Shader location: sampler2d texture: height */
var RL_SHADER_LOC_MAP_HEIGHT: number/** Shader location: samplerCube texture: cubemap */
var RL_SHADER_LOC_MAP_CUBEMAP: number/** Shader location: samplerCube texture: irradiance */
var RL_SHADER_LOC_MAP_IRRADIANCE: number/** Shader location: samplerCube texture: prefilter */
var RL_SHADER_LOC_MAP_PREFILTER: number/**  */
var RL_SHADER_LOC_MAP_BRDF: number/** Shader location: sampler2d texture: albedo (same as: RL_SHADER_LOC_MAP_DIFFUSE) */
var RL_SHADER_LOC_MAP_DIFFUSE: number/** Shader location: sampler2d texture: metalness (same as: RL_SHADER_LOC_MAP_SPECULAR) */
var RL_SHADER_LOC_MAP_SPECULAR: number/** Shader uniform type: float */
var RL_SHADER_UNIFORM_FLOAT: number/** Shader uniform type: vec2 (2 float) */
var RL_SHADER_UNIFORM_VEC2: number/** Shader uniform type: vec3 (3 float) */
var RL_SHADER_UNIFORM_VEC3: number/** Shader uniform type: vec4 (4 float) */
var RL_SHADER_UNIFORM_VEC4: number/** Shader uniform type: int */
var RL_SHADER_UNIFORM_INT: number/** Shader uniform type: ivec2 (2 int) */
var RL_SHADER_UNIFORM_IVEC2: number/** Shader uniform type: ivec3 (3 int) */
var RL_SHADER_UNIFORM_IVEC3: number/** Shader uniform type: ivec4 (4 int) */
var RL_SHADER_UNIFORM_IVEC4: number/** Shader uniform type: unsigned int */
var RL_SHADER_UNIFORM_UINT: number/** Shader uniform type: uivec2 (2 unsigned int) */
var RL_SHADER_UNIFORM_UIVEC2: number/** Shader uniform type: uivec3 (3 unsigned int) */
var RL_SHADER_UNIFORM_UIVEC3: number/** Shader uniform type: uivec4 (4 unsigned int) */
var RL_SHADER_UNIFORM_UIVEC4: number/**  */
var RL_SHADER_UNIFORM_SAMPLER2D: number/** Shader attribute type: float */
var RL_SHADER_ATTRIB_FLOAT: number/** Shader attribute type: vec2 (2 float) */
var RL_SHADER_ATTRIB_VEC2: number/** Shader attribute type: vec3 (3 float) */
var RL_SHADER_ATTRIB_VEC3: number/**  */
var RL_SHADER_ATTRIB_VEC4: number/** Framebuffer attachment type: color 0 */
var RL_ATTACHMENT_COLOR_CHANNEL0: number/** Framebuffer attachment type: color 1 */
var RL_ATTACHMENT_COLOR_CHANNEL1: number/** Framebuffer attachment type: color 2 */
var RL_ATTACHMENT_COLOR_CHANNEL2: number/** Framebuffer attachment type: color 3 */
var RL_ATTACHMENT_COLOR_CHANNEL3: number/** Framebuffer attachment type: color 4 */
var RL_ATTACHMENT_COLOR_CHANNEL4: number/** Framebuffer attachment type: color 5 */
var RL_ATTACHMENT_COLOR_CHANNEL5: number/** Framebuffer attachment type: color 6 */
var RL_ATTACHMENT_COLOR_CHANNEL6: number/** Framebuffer attachment type: color 7 */
var RL_ATTACHMENT_COLOR_CHANNEL7: number/** Framebuffer attachment type: depth */
var RL_ATTACHMENT_DEPTH: number/** Framebuffer attachment type: stencil */
var RL_ATTACHMENT_STENCIL: number/** Framebuffer texture attachment type: cubemap, +X side */
var RL_ATTACHMENT_CUBEMAP_POSITIVE_X: number/** Framebuffer texture attachment type: cubemap, -X side */
var RL_ATTACHMENT_CUBEMAP_NEGATIVE_X: number/** Framebuffer texture attachment type: cubemap, +Y side */
var RL_ATTACHMENT_CUBEMAP_POSITIVE_Y: number/** Framebuffer texture attachment type: cubemap, -Y side */
var RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y: number/** Framebuffer texture attachment type: cubemap, +Z side */
var RL_ATTACHMENT_CUBEMAP_POSITIVE_Z: number/** Framebuffer texture attachment type: cubemap, -Z side */
var RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z: number/** Framebuffer texture attachment type: texture2d */
var RL_ATTACHMENT_TEXTURE2D: number/** Framebuffer texture attachment type: renderbuffer */
var RL_ATTACHMENT_RENDERBUFFER: number/**  */
var RL_CULL_FACE_FRONT: number/**  */
var RL_CULL_FACE_BACK: number/** NOTE: Be careful with text, every letter maps to a quad */
var RL_DEFAULT_BATCH_BUFFER_ELEMENTS: number/** GL_TEXTURE_WRAP_S */
var RL_TEXTURE_WRAP_S: number/** GL_TEXTURE_WRAP_T */
var RL_TEXTURE_WRAP_T: number/** GL_TEXTURE_MAG_FILTER */
var RL_TEXTURE_MAG_FILTER: number/** GL_TEXTURE_MIN_FILTER */
var RL_TEXTURE_MIN_FILTER: number/** GL_NEAREST */
var RL_TEXTURE_FILTER_NEAREST: number/** GL_LINEAR */
var RL_TEXTURE_FILTER_LINEAR: number/** GL_NEAREST_MIPMAP_NEAREST */
var RL_TEXTURE_FILTER_MIP_NEAREST: number/** GL_NEAREST_MIPMAP_LINEAR */
var RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR: number/** GL_LINEAR_MIPMAP_NEAREST */
var RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST: number/** GL_LINEAR_MIPMAP_LINEAR */
var RL_TEXTURE_FILTER_MIP_LINEAR: number/** Anisotropic filter (custom identifier) */
var RL_TEXTURE_FILTER_ANISOTROPIC: number/** Texture mipmap bias, percentage ratio (custom identifier) */
var RL_TEXTURE_MIPMAP_BIAS_RATIO: number/** GL_REPEAT */
var RL_TEXTURE_WRAP_REPEAT: number/** GL_CLAMP_TO_EDGE */
var RL_TEXTURE_WRAP_CLAMP: number/** GL_MIRRORED_REPEAT */
var RL_TEXTURE_WRAP_MIRROR_REPEAT: number/** GL_MIRROR_CLAMP_EXT */
var RL_TEXTURE_WRAP_MIRROR_CLAMP: number/** GL_MODELVIEW */
var RL_MODELVIEW: number/** GL_PROJECTION */
var RL_PROJECTION: number/** GL_TEXTURE */
var RL_TEXTURE: number/** GL_LINES */
var RL_LINES: number/** GL_TRIANGLES */
var RL_TRIANGLES: number/** GL_QUADS */
var RL_QUADS: number/** GL_UNSIGNED_BYTE */
var RL_UNSIGNED_BYTE: number/** GL_FLOAT */
var RL_FLOAT: number/** GL_STREAM_DRAW */
var RL_STREAM_DRAW: number/** GL_STREAM_READ */
var RL_STREAM_READ: number/** GL_STREAM_COPY */
var RL_STREAM_COPY: number/** GL_STATIC_DRAW */
var RL_STATIC_DRAW: number/** GL_STATIC_READ */
var RL_STATIC_READ: number/** GL_STATIC_COPY */
var RL_STATIC_COPY: number/** GL_DYNAMIC_DRAW */
var RL_DYNAMIC_DRAW: number/** GL_DYNAMIC_READ */
var RL_DYNAMIC_READ: number/** GL_DYNAMIC_COPY */
var RL_DYNAMIC_COPY: number/** GL_FRAGMENT_SHADER */
var RL_FRAGMENT_SHADER: number/** GL_VERTEX_SHADER */
var RL_VERTEX_SHADER: number/** GL_COMPUTE_SHADER */
var RL_COMPUTE_SHADER: number/** GL_ZERO */
var RL_ZERO: number/** GL_ONE */
var RL_ONE: number/** GL_SRC_COLOR */
var RL_SRC_COLOR: number/** GL_ONE_MINUS_SRC_COLOR */
var RL_ONE_MINUS_SRC_COLOR: number/** GL_SRC_ALPHA */
var RL_SRC_ALPHA: number/** GL_ONE_MINUS_SRC_ALPHA */
var RL_ONE_MINUS_SRC_ALPHA: number/** GL_DST_ALPHA */
var RL_DST_ALPHA: number/** GL_ONE_MINUS_DST_ALPHA */
var RL_ONE_MINUS_DST_ALPHA: number/** GL_DST_COLOR */
var RL_DST_COLOR: number/** GL_ONE_MINUS_DST_COLOR */
var RL_ONE_MINUS_DST_COLOR: number/** GL_SRC_ALPHA_SATURATE */
var RL_SRC_ALPHA_SATURATE: number/** GL_CONSTANT_COLOR */
var RL_CONSTANT_COLOR: number/** GL_ONE_MINUS_CONSTANT_COLOR */
var RL_ONE_MINUS_CONSTANT_COLOR: number/** GL_CONSTANT_ALPHA */
var RL_CONSTANT_ALPHA: number/** GL_ONE_MINUS_CONSTANT_ALPHA */
var RL_ONE_MINUS_CONSTANT_ALPHA: number/** GL_FUNC_ADD */
var RL_FUNC_ADD: number/** GL_MIN */
var RL_MIN: number/** GL_MAX */
var RL_MAX: number/** GL_FUNC_SUBTRACT */
var RL_FUNC_SUBTRACT: number/** GL_FUNC_REVERSE_SUBTRACT */
var RL_FUNC_REVERSE_SUBTRACT: number/** GL_BLEND_EQUATION */
var RL_BLEND_EQUATION: number/** GL_BLEND_EQUATION_RGB   // (Same as BLEND_EQUATION) */
var RL_BLEND_EQUATION_RGB: number/** GL_BLEND_EQUATION_ALPHA */
var RL_BLEND_EQUATION_ALPHA: number/** GL_BLEND_DST_RGB */
var RL_BLEND_DST_RGB: number/** GL_BLEND_SRC_RGB */
var RL_BLEND_SRC_RGB: number/** GL_BLEND_DST_ALPHA */
var RL_BLEND_DST_ALPHA: number/** GL_BLEND_SRC_ALPHA */
var RL_BLEND_SRC_ALPHA: number/** GL_BLEND_COLOR */
var RL_BLEND_COLOR: number/** GL_READ_FRAMEBUFFER */
var RL_READ_FRAMEBUFFER: number/** GL_DRAW_FRAMEBUFFER */
var RL_DRAW_FRAMEBUFFER: number}
