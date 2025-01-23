interface rlVertexBuffer {
}
declare var rlVertexBuffer: {
    prototype: rlVertexBuffer;
}
interface rlDrawCall {
}
declare var rlDrawCall: {
    prototype: rlDrawCall;
}
interface rlRenderBatch {
}
declare var rlRenderBatch: {
    prototype: rlRenderBatch;
}
/** undefined */
declare function rlMatrixMode(mode: number): void;
/** undefined */
declare function rlPushMatrix(): void;
/** undefined */
declare function rlPopMatrix(): void;
/** undefined */
declare function rlLoadIdentity(): void;
/** undefined */
declare function rlTranslatef(x: number, y: number, z: number): void;
/** undefined */
declare function rlRotatef(angle: number, x: number, y: number, z: number): void;
/** undefined */
declare function rlScalef(x: number, y: number, z: number): void;
/** undefined */
declare function rlMultMatrixf(matf: float &): void;
/** undefined */
declare function rlFrustum(left: number, right: number, bottom: number, top: number, znear: number, zfar: number): void;
/** undefined */
declare function rlOrtho(left: number, right: number, bottom: number, top: number, znear: number, zfar: number): void;
/** undefined */
declare function rlViewport(x: number, y: number, width: number, height: number): void;
/** undefined */
declare function rlSetClipPlanes(nearPlane: number, farPlane: number): void;
/** undefined */
declare function rlGetCullDistanceNear(): number;
/** undefined */
declare function rlGetCullDistanceFar(): number;
/** undefined */
declare function rlBegin(mode: number): void;
/** undefined */
declare function rlEnd(): void;
/** undefined */
declare function rlVertex2i(x: number, y: number): void;
/** undefined */
declare function rlVertex2f(x: number, y: number): void;
/** undefined */
declare function rlVertex3f(x: number, y: number, z: number): void;
/** undefined */
declare function rlTexCoord2f(x: number, y: number): void;
/** undefined */
declare function rlNormal3f(x: number, y: number, z: number): void;
/** undefined */
declare function rlColor4ub(r: number, g: number, b: number, a: number): void;
/** undefined */
declare function rlColor3f(x: number, y: number, z: number): void;
/** undefined */
declare function rlColor4f(x: number, y: number, z: number, w: number): void;
/** undefined */
declare function rlEnableVertexArray(vaoId: number): boolean;
/** undefined */
declare function rlDisableVertexArray(): void;
/** undefined */
declare function rlEnableVertexBuffer(id: number): void;
/** undefined */
declare function rlDisableVertexBuffer(): void;
/** undefined */
declare function rlEnableVertexBufferElement(id: number): void;
/** undefined */
declare function rlDisableVertexBufferElement(): void;
/** undefined */
declare function rlEnableVertexAttribute(index: number): void;
/** undefined */
declare function rlDisableVertexAttribute(index: number): void;
/** undefined */
declare function rlActiveTextureSlot(slot: number): void;
/** undefined */
declare function rlEnableTexture(id: number): void;
/** undefined */
declare function rlDisableTexture(): void;
/** undefined */
declare function rlEnableTextureCubemap(id: number): void;
/** undefined */
declare function rlDisableTextureCubemap(): void;
/** undefined */
declare function rlTextureParameters(id: number, param: number, value: number): void;
/** undefined */
declare function rlCubemapParameters(id: number, param: number, value: number): void;
/** undefined */
declare function rlEnableShader(id: number): void;
/** undefined */
declare function rlDisableShader(): void;
/** undefined */
declare function rlEnableFramebuffer(id: number): void;
/** undefined */
declare function rlDisableFramebuffer(): void;
/** undefined */
declare function rlGetActiveFramebuffer(): number;
/** undefined */
declare function rlActiveDrawBuffers(count: number): void;
/** undefined */
declare function rlBlitFramebuffer(srcX: number, srcY: number, srcWidth: number, srcHeight: number, dstX: number, dstY: number, dstWidth: number, dstHeight: number, bufferMask: number): void;
/** undefined */
declare function rlBindFramebuffer(target: number, framebuffer: number): void;
/** undefined */
declare function rlEnableColorBlend(): void;
/** undefined */
declare function rlDisableColorBlend(): void;
/** undefined */
declare function rlEnableDepthTest(): void;
/** undefined */
declare function rlDisableDepthTest(): void;
/** undefined */
declare function rlEnableDepthMask(): void;
/** undefined */
declare function rlDisableDepthMask(): void;
/** undefined */
declare function rlEnableBackfaceCulling(): void;
/** undefined */
declare function rlDisableBackfaceCulling(): void;
/** undefined */
declare function rlColorMask(r: boolean, g: boolean, b: boolean, a: boolean): void;
/** undefined */
declare function rlSetCullFace(mode: number): void;
/** undefined */
declare function rlEnableScissorTest(): void;
/** undefined */
declare function rlDisableScissorTest(): void;
/** undefined */
declare function rlScissor(x: number, y: number, width: number, height: number): void;
/** undefined */
declare function rlEnablePointMode(): void;
/** undefined */
declare function rlDisablePointMode(): void;
/** undefined */
declare function rlEnableWireMode(): void;
/** undefined */
declare function rlDisableWireMode(): void;
/** undefined */
declare function rlSetLineWidth(width: number): void;
/** undefined */
declare function rlGetLineWidth(): number;
/** undefined */
declare function rlEnableSmoothLines(): void;
/** undefined */
declare function rlDisableSmoothLines(): void;
/** undefined */
declare function rlEnableStereoRender(): void;
/** undefined */
declare function rlDisableStereoRender(): void;
/** undefined */
declare function rlIsStereoRenderEnabled(): boolean;
/** undefined */
declare function rlClearColor(r: number, g: number, b: number, a: number): void;
/** undefined */
declare function rlClearScreenBuffers(): void;
/** undefined */
declare function rlCheckErrors(): void;
/** undefined */
declare function rlSetBlendMode(mode: number): void;
/** undefined */
declare function rlSetBlendFactors(glSrcFactor: number, glDstFactor: number, glEquation: number): void;
/** undefined */
declare function rlSetBlendFactorsSeparate(glSrcRGB: number, glDstRGB: number, glSrcAlpha: number, glDstAlpha: number, glEqRGB: number, glEqAlpha: number): void;
/** undefined */
declare function rlglInit(width: number, height: number): void;
/** undefined */
declare function rlglClose(): void;
/** undefined */
declare function rlGetVersion(): number;
/** undefined */
declare function rlSetFramebufferWidth(width: number): void;
/** undefined */
declare function rlGetFramebufferWidth(): number;
/** undefined */
declare function rlSetFramebufferHeight(height: number): void;
/** undefined */
declare function rlGetFramebufferHeight(): number;
/** undefined */
declare function rlGetTextureIdDefault(): number;
/** undefined */
declare function rlGetShaderIdDefault(): number;
/** undefined */
declare function rlGetShaderLocsDefault(): int;
/** undefined */
declare function rlLoadRenderBatch(numBuffers: number, bufferElements: number): rlRenderBatch;
/** undefined */
declare function rlUnloadRenderBatch(batch: rlRenderBatch): void;
/** undefined */
declare function rlDrawRenderBatch(batch: rlRenderBatch &): void;
/** undefined */
declare function rlSetRenderBatchActive(batch: rlRenderBatch &): void;
/** undefined */
declare function rlDrawRenderBatchActive(): void;
/** undefined */
declare function rlCheckRenderBatchLimit(vCount: number): boolean;
/** undefined */
declare function rlSetTexture(id: number): void;
/** undefined */
declare function rlLoadVertexArray(): number;
/** undefined */
declare function rlLoadVertexBuffer(buffer: any, size: number, dynamic: boolean): number;
/** undefined */
declare function rlLoadVertexBufferElement(buffer: any, size: number, dynamic: boolean): number;
/** undefined */
declare function rlUpdateVertexBuffer(bufferId: number, data: any, dataSize: number, offset: number): void;
/** undefined */
declare function rlUpdateVertexBufferElements(id: number, data: any, dataSize: number, offset: number): void;
/** undefined */
declare function rlUnloadVertexArray(vaoId: number): void;
/** undefined */
declare function rlUnloadVertexBuffer(vboId: number): void;
/** undefined */
declare function rlSetVertexAttribute(index: number, compSize: number, type: number, normalized: boolean, stride: number, offset: number): void;
/** undefined */
declare function rlSetVertexAttributeDivisor(index: number, divisor: number): void;
/** undefined */
declare function rlDrawVertexArray(offset: number, count: number): void;
/** undefined */
declare function rlDrawVertexArrayElements(offset: number, count: number, buffer: any): void;
/** undefined */
declare function rlDrawVertexArrayInstanced(offset: number, count: number, instances: number): void;
/** undefined */
declare function rlDrawVertexArrayElementsInstanced(offset: number, count: number, buffer: any, instances: number): void;
/** undefined */
declare function rlLoadTexture(data: any, width: number, height: number, format: number, mipmapCount: number): number;
/** undefined */
declare function rlLoadTextureDepth(width: number, height: number, useRenderBuffer: boolean): number;
/** undefined */
declare function rlLoadTextureCubemap(data: any, size: number, format: number, mipmapCount: number): number;
/** undefined */
declare function rlUpdateTexture(id: number, offsetX: number, offsetY: number, width: number, height: number, format: number, data: any): void;
/** undefined */
declare function rlGetGlTextureFormats(format: number, glInternalFormat: unsigned int, glFormat: unsigned int, glType: unsigned int): void;
/** undefined */
declare function rlGetPixelFormatName(format: number): string | undefined | null;
/** undefined */
declare function rlUnloadTexture(id: number): void;
/** undefined */
declare function rlGenTextureMipmaps(id: number, width: number, height: number, format: number, mipmaps: int): void;
/** undefined */
declare function rlReadScreenPixels(width: number, height: number): ArrayBuffer;
/** undefined */
declare function rlLoadFramebuffer(): number;
/** undefined */
declare function rlFramebufferAttach(fboId: number, texId: number, attachType: number, texType: number, mipLevel: number): void;
/** undefined */
declare function rlFramebufferComplete(id: number): boolean;
/** undefined */
declare function rlUnloadFramebuffer(id: number): void;
/** undefined */
declare function rlLoadShaderCode(vsCode: string | undefined | null, fsCode: string | undefined | null): number;
/** undefined */
declare function rlCompileShader(shaderCode: string | undefined | null, type: number): number;
/** undefined */
declare function rlLoadShaderProgram(vShaderId: number, fShaderId: number): number;
/** undefined */
declare function rlUnloadShaderProgram(id: number): void;
/** undefined */
declare function rlGetLocationUniform(shaderId: number, uniformName: string | undefined | null): number;
/** undefined */
declare function rlGetLocationAttrib(shaderId: number, attribName: string | undefined | null): number;
/** undefined */
declare function rlSetUniformMatrix(locIndex: number, mat: Matrix): void;
/** undefined */
declare function rlSetUniformMatrices(locIndex: number, mat: Matrix, count: number): void;
/** undefined */
declare function rlSetUniformSampler(locIndex: number, textureId: number): void;
/** undefined */
declare function rlSetShader(id: number, locs: int): void;
/** undefined */
declare function rlLoadComputeShaderProgram(shaderId: number): number;
/** undefined */
declare function rlComputeShaderDispatch(groupX: number, groupY: number, groupZ: number): void;
/** undefined */
declare function rlLoadShaderBuffer(size: number, data: any, usageHint: number): number;
/** undefined */
declare function rlUnloadShaderBuffer(ssboId: number): void;
/** undefined */
declare function rlUpdateShaderBuffer(id: number, data: any, dataSize: number, offset: number): void;
/** undefined */
declare function rlBindShaderBuffer(id: number, index: number): void;
/** undefined */
declare function rlReadShaderBuffer(id: number, dest: any, count: number, offset: number): void;
/** undefined */
declare function rlCopyShaderBuffer(destId: number, srcId: number, destOffset: number, srcOffset: number, count: number): void;
/** undefined */
declare function rlGetShaderBufferSize(id: number): number;
/** undefined */
declare function rlBindImageTexture(id: number, index: number, format: number, readonly: boolean): void;
/** undefined */
declare function rlGetMatrixModelview(): Matrix;
/** undefined */
declare function rlGetMatrixProjection(): Matrix;
/** undefined */
declare function rlGetMatrixTransform(): Matrix;
/** undefined */
declare function rlGetMatrixProjectionStereo(eye: number): Matrix;
/** undefined */
declare function rlGetMatrixViewOffsetStereo(eye: number): Matrix;
/** undefined */
declare function rlSetMatrixProjection(proj: Matrix): void;
/** undefined */
declare function rlSetMatrixModelview(view: Matrix): void;
/** undefined */
declare function rlSetMatrixProjectionStereo(right: Matrix, left: Matrix): void;
/** undefined */
declare function rlSetMatrixViewOffsetStereo(right: Matrix, left: Matrix): void;
/** undefined */
declare function rlLoadDrawCube(): void;
/** undefined */
declare function rlLoadDrawQuad(): void;
/**  */
declare var RL_OPENGL_11: number;
/**  */
declare var RL_OPENGL_21: number;
/**  */
declare var RL_OPENGL_33: number;
/**  */
declare var RL_OPENGL_43: number;
/**  */
declare var RL_OPENGL_ES_20: number;
/**  */
declare var RL_OPENGL_ES_30: number;
/**  */
declare var RL_LOG_ALL: number;
/**  */
declare var RL_LOG_TRACE: number;
/**  */
declare var RL_LOG_DEBUG: number;
/**  */
declare var RL_LOG_INFO: number;
/**  */
declare var RL_LOG_WARNING: number;
/**  */
declare var RL_LOG_ERROR: number;
/**  */
declare var RL_LOG_FATAL: number;
/**  */
declare var RL_LOG_NONE: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_R5G6B5: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_R5G5B5A1: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_R4G4B4A4: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_R32: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32A32: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_R16: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16: number;
/**  */
declare var RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16A16: number;
/**  */
declare var RL_PIXELFORMAT_COMPRESSED_DXT1_RGB: number;
/**  */
declare var RL_PIXELFORMAT_COMPRESSED_DXT1_RGBA: number;
/**  */
declare var RL_PIXELFORMAT_COMPRESSED_DXT3_RGBA: number;
/**  */
declare var RL_PIXELFORMAT_COMPRESSED_DXT5_RGBA: number;
/**  */
declare var RL_PIXELFORMAT_COMPRESSED_ETC1_RGB: number;
/**  */
declare var RL_PIXELFORMAT_COMPRESSED_ETC2_RGB: number;
/**  */
declare var RL_PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA: number;
/**  */
declare var RL_PIXELFORMAT_COMPRESSED_PVRT_RGB: number;
/**  */
declare var RL_PIXELFORMAT_COMPRESSED_PVRT_RGBA: number;
/**  */
declare var RL_PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA: number;
/**  */
declare var RL_PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA: number;
/**  */
declare var RL_TEXTURE_FILTER_POINT: number;
/**  */
declare var RL_TEXTURE_FILTER_BILINEAR: number;
/**  */
declare var RL_TEXTURE_FILTER_TRILINEAR: number;
/**  */
declare var RL_TEXTURE_FILTER_ANISOTROPIC_4X: number;
/**  */
declare var RL_TEXTURE_FILTER_ANISOTROPIC_8X: number;
/**  */
declare var RL_TEXTURE_FILTER_ANISOTROPIC_16X: number;
/**  */
declare var RL_BLEND_ALPHA: number;
/**  */
declare var RL_BLEND_ADDITIVE: number;
/**  */
declare var RL_BLEND_MULTIPLIED: number;
/**  */
declare var RL_BLEND_ADD_COLORS: number;
/**  */
declare var RL_BLEND_SUBTRACT_COLORS: number;
/**  */
declare var RL_BLEND_ALPHA_PREMULTIPLY: number;
/**  */
declare var RL_BLEND_CUSTOM: number;
/**  */
declare var RL_BLEND_CUSTOM_SEPARATE: number;
/**  */
declare var RL_SHADER_LOC_VERTEX_POSITION: number;
/**  */
declare var RL_SHADER_LOC_VERTEX_TEXCOORD01: number;
/**  */
declare var RL_SHADER_LOC_VERTEX_TEXCOORD02: number;
/**  */
declare var RL_SHADER_LOC_VERTEX_NORMAL: number;
/**  */
declare var RL_SHADER_LOC_VERTEX_TANGENT: number;
/**  */
declare var RL_SHADER_LOC_VERTEX_COLOR: number;
/**  */
declare var RL_SHADER_LOC_MATRIX_MVP: number;
/**  */
declare var RL_SHADER_LOC_MATRIX_VIEW: number;
/**  */
declare var RL_SHADER_LOC_MATRIX_PROJECTION: number;
/**  */
declare var RL_SHADER_LOC_MATRIX_MODEL: number;
/**  */
declare var RL_SHADER_LOC_MATRIX_NORMAL: number;
/**  */
declare var RL_SHADER_LOC_VECTOR_VIEW: number;
/**  */
declare var RL_SHADER_LOC_COLOR_DIFFUSE: number;
/**  */
declare var RL_SHADER_LOC_COLOR_SPECULAR: number;
/**  */
declare var RL_SHADER_LOC_COLOR_AMBIENT: number;
/**  */
declare var RL_SHADER_LOC_MAP_ALBEDO: number;
/**  */
declare var RL_SHADER_LOC_MAP_METALNESS: number;
/**  */
declare var RL_SHADER_LOC_MAP_NORMAL: number;
/**  */
declare var RL_SHADER_LOC_MAP_ROUGHNESS: number;
/**  */
declare var RL_SHADER_LOC_MAP_OCCLUSION: number;
/**  */
declare var RL_SHADER_LOC_MAP_EMISSION: number;
/**  */
declare var RL_SHADER_LOC_MAP_HEIGHT: number;
/**  */
declare var RL_SHADER_LOC_MAP_CUBEMAP: number;
/**  */
declare var RL_SHADER_LOC_MAP_IRRADIANCE: number;
/**  */
declare var RL_SHADER_LOC_MAP_PREFILTER: number;
/**  */
declare var RL_SHADER_LOC_MAP_BRDF: number;
/**  */
declare var RL_SHADER_UNIFORM_FLOAT: number;
/**  */
declare var RL_SHADER_UNIFORM_VEC2: number;
/**  */
declare var RL_SHADER_UNIFORM_VEC3: number;
/**  */
declare var RL_SHADER_UNIFORM_VEC4: number;
/**  */
declare var RL_SHADER_UNIFORM_INT: number;
/**  */
declare var RL_SHADER_UNIFORM_IVEC2: number;
/**  */
declare var RL_SHADER_UNIFORM_IVEC3: number;
/**  */
declare var RL_SHADER_UNIFORM_IVEC4: number;
/**  */
declare var RL_SHADER_UNIFORM_UINT: number;
/**  */
declare var RL_SHADER_UNIFORM_UIVEC2: number;
/**  */
declare var RL_SHADER_UNIFORM_UIVEC3: number;
/**  */
declare var RL_SHADER_UNIFORM_UIVEC4: number;
/**  */
declare var RL_SHADER_UNIFORM_SAMPLER2D: number;
/**  */
declare var RL_SHADER_ATTRIB_FLOAT: number;
/**  */
declare var RL_SHADER_ATTRIB_VEC2: number;
/**  */
declare var RL_SHADER_ATTRIB_VEC3: number;
/**  */
declare var RL_SHADER_ATTRIB_VEC4: number;
/**  */
declare var RL_ATTACHMENT_COLOR_CHANNEL0: number;
/**  */
declare var RL_ATTACHMENT_COLOR_CHANNEL1: number;
/**  */
declare var RL_ATTACHMENT_COLOR_CHANNEL2: number;
/**  */
declare var RL_ATTACHMENT_COLOR_CHANNEL3: number;
/**  */
declare var RL_ATTACHMENT_COLOR_CHANNEL4: number;
/**  */
declare var RL_ATTACHMENT_COLOR_CHANNEL5: number;
/**  */
declare var RL_ATTACHMENT_COLOR_CHANNEL6: number;
/**  */
declare var RL_ATTACHMENT_COLOR_CHANNEL7: number;
/**  */
declare var RL_ATTACHMENT_DEPTH: number;
/**  */
declare var RL_ATTACHMENT_STENCIL: number;
/**  */
declare var RL_ATTACHMENT_CUBEMAP_POSITIVE_X: number;
/**  */
declare var RL_ATTACHMENT_CUBEMAP_NEGATIVE_X: number;
/**  */
declare var RL_ATTACHMENT_CUBEMAP_POSITIVE_Y: number;
/**  */
declare var RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y: number;
/**  */
declare var RL_ATTACHMENT_CUBEMAP_POSITIVE_Z: number;
/**  */
declare var RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z: number;
/**  */
declare var RL_ATTACHMENT_TEXTURE2D: number;
/**  */
declare var RL_ATTACHMENT_RENDERBUFFER: number;
/**  */
declare var RL_CULL_FACE_FRONT: number;
/**  */
declare var RL_CULL_FACE_BACK: number;
/**  */
declare var RL_DEFAULT_BATCH_BUFFER_ELEMENTS: number;
/**  */
declare var RL_DEFAULT_BATCH_BUFFERS: number;
/**  */
declare var RL_DEFAULT_BATCH_DRAWCALLS: number;
/**  */
declare var RL_DEFAULT_BATCH_MAX_TEXTURE_UNITS: number;
/**  */
declare var RL_MAX_MATRIX_STACK_SIZE: number;
/**  */
declare var RL_MAX_SHADER_LOCATIONS: number;
/**  */
declare var RL_CULL_DISTANCE_NEAR: number;
/**  */
declare var RL_CULL_DISTANCE_FAR: number;
/**  */
declare var RL_TEXTURE_WRAP_S: number;
/**  */
declare var RL_TEXTURE_WRAP_T: number;
/**  */
declare var RL_TEXTURE_MAG_FILTER: number;
/**  */
declare var RL_TEXTURE_MIN_FILTER: number;
/**  */
declare var RL_TEXTURE_FILTER_NEAREST: number;
/**  */
declare var RL_TEXTURE_FILTER_LINEAR: number;
/**  */
declare var RL_TEXTURE_FILTER_MIP_NEAREST: number;
/**  */
declare var RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR: number;
/**  */
declare var RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST: number;
/**  */
declare var RL_TEXTURE_FILTER_MIP_LINEAR: number;
/**  */
declare var RL_TEXTURE_FILTER_ANISOTROPIC: number;
/**  */
declare var RL_TEXTURE_MIPMAP_BIAS_RATIO: number;
/**  */
declare var RL_TEXTURE_WRAP_REPEAT: number;
/**  */
declare var RL_TEXTURE_WRAP_CLAMP: number;
/**  */
declare var RL_TEXTURE_WRAP_MIRROR_REPEAT: number;
/**  */
declare var RL_TEXTURE_WRAP_MIRROR_CLAMP: number;
/**  */
declare var RL_MODELVIEW: number;
/**  */
declare var RL_PROJECTION: number;
/**  */
declare var RL_TEXTURE: number;
/**  */
declare var RL_LINES: number;
/**  */
declare var RL_TRIANGLES: number;
/**  */
declare var RL_QUADS: number;
/**  */
declare var RL_UNSIGNED_BYTE: number;
/**  */
declare var RL_FLOAT: number;
/**  */
declare var RL_STREAM_DRAW: number;
/**  */
declare var RL_STREAM_READ: number;
/**  */
declare var RL_STREAM_COPY: number;
/**  */
declare var RL_STATIC_DRAW: number;
/**  */
declare var RL_STATIC_READ: number;
/**  */
declare var RL_STATIC_COPY: number;
/**  */
declare var RL_DYNAMIC_DRAW: number;
/**  */
declare var RL_DYNAMIC_READ: number;
/**  */
declare var RL_DYNAMIC_COPY: number;
/**  */
declare var RL_FRAGMENT_SHADER: number;
/**  */
declare var RL_VERTEX_SHADER: number;
/**  */
declare var RL_COMPUTE_SHADER: number;
/**  */
declare var RL_ZERO: number;
/**  */
declare var RL_ONE: number;
/**  */
declare var RL_SRC_COLOR: number;
/**  */
declare var RL_ONE_MINUS_SRC_COLOR: number;
/**  */
declare var RL_SRC_ALPHA: number;
/**  */
declare var RL_ONE_MINUS_SRC_ALPHA: number;
/**  */
declare var RL_DST_ALPHA: number;
/**  */
declare var RL_ONE_MINUS_DST_ALPHA: number;
/**  */
declare var RL_DST_COLOR: number;
/**  */
declare var RL_ONE_MINUS_DST_COLOR: number;
/**  */
declare var RL_SRC_ALPHA_SATURATE: number;
/**  */
declare var RL_CONSTANT_COLOR: number;
/**  */
declare var RL_ONE_MINUS_CONSTANT_COLOR: number;
/**  */
declare var RL_CONSTANT_ALPHA: number;
/**  */
declare var RL_ONE_MINUS_CONSTANT_ALPHA: number;
/**  */
declare var RL_FUNC_ADD: number;
/**  */
declare var RL_MIN: number;
/**  */
declare var RL_MAX: number;
/**  */
declare var RL_FUNC_SUBTRACT: number;
/**  */
declare var RL_FUNC_REVERSE_SUBTRACT: number;
/**  */
declare var RL_BLEND_EQUATION: number;
/**  */
declare var RL_BLEND_EQUATION_RGB: number;
/**  */
declare var RL_BLEND_EQUATION_ALPHA: number;
/**  */
declare var RL_BLEND_DST_RGB: number;
/**  */
declare var RL_BLEND_SRC_RGB: number;
/**  */
declare var RL_BLEND_DST_ALPHA: number;
/**  */
declare var RL_BLEND_SRC_ALPHA: number;
/**  */
declare var RL_BLEND_COLOR: number;
/**  */
declare var RL_READ_FRAMEBUFFER: number;
/**  */
declare var RL_DRAW_FRAMEBUFFER: number;
/**  */
declare var RL_DEFAULT_SHADER_ATTRIB_LOCATION_POSITION: number;
/**  */
declare var RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD: number;
/**  */
declare var RL_DEFAULT_SHADER_ATTRIB_LOCATION_NORMAL: number;
/**  */
declare var RL_DEFAULT_SHADER_ATTRIB_LOCATION_COLOR: number;
/**  */
declare var RL_DEFAULT_SHADER_ATTRIB_LOCATION_TANGENT: number;
/**  */
declare var RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD2: number;
/**  */
declare var RL_DEFAULT_SHADER_ATTRIB_LOCATION_INDICES: number;
/**  */
declare var RL_DEFAULT_SHADER_ATTRIB_LOCATION_INSTANCE_TX: number;
/**  */
declare var RL_SHADER_LOC_MAP_DIFFUSE: number;
/**  */
declare var RL_SHADER_LOC_MAP_SPECULAR: number;
