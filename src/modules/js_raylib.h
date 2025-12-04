#ifndef JS_raylib_GUARD
	#define JS_raylib_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <raylib.h>
	
	static float js_getfloat(JSContext * ctx,JSValue src,bool * error){
		float ret;
		if(JS_IsNumber(src)){
			double double_ret;
			JS_ToFloat64(ctx,&double_ret,src);
			ret =((float)double_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type float");
			error[0]=(bool)1;
			return 0.0f;
		}
		return ret;
	}
	
	static Vector2 js_getVector2(JSContext * ctx,JSValue src,bool * error){
		Vector2 ret;
		if(JS_GetClassID(src)==js_Vector2_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Vector2_class_id);
			ret =*(Vector2 *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector2");
			error[0]=(bool)1;
			return (Vector2){0};
		}
		return ret;
	}
	
	static Vector3 js_getVector3(JSContext * ctx,JSValue src,bool * error){
		Vector3 ret;
		if(JS_GetClassID(src)==js_Vector3_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Vector3_class_id);
			ret =*(Vector3 *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector3");
			error[0]=(bool)1;
			return (Vector3){0};
		}
		return ret;
	}
	
	static Vector4 js_getVector4(JSContext * ctx,JSValue src,bool * error){
		Vector4 ret;
		if(JS_GetClassID(src)==js_Vector4_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Vector4_class_id);
			ret =*(Vector4 *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector4");
			error[0]=(bool)1;
			return (Vector4){0};
		}
		return ret;
	}
	
	static Matrix js_getMatrix(JSContext * ctx,JSValue src,bool * error){
		Matrix ret;
		if(JS_GetClassID(src)==js_Matrix_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Matrix_class_id);
			ret =*(Matrix *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Matrix");
			error[0]=(bool)1;
			return (Matrix){0};
		}
		return ret;
	}
	
	static unsigned char js_getunsignedchar(JSContext * ctx,JSValue src,bool * error){
		unsigned char ret;
		if(JS_IsNumber(src)){
			uint32_t long_ret;
			JS_ToUint32(ctx,&long_ret,src);
			ret =((unsigned char)long_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned char");
			error[0]=(bool)1;
			return 0;
		}
		return ret;
	}
	
	static Color js_getColor(JSContext * ctx,JSValue src,bool * error){
		Color ret;
		if(JS_GetClassID(src)==js_Color_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Color_class_id);
			ret =*(Color *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Color");
			error[0]=(bool)1;
			return (Color){0};
		}
		return ret;
	}
	
	static Rectangle js_getRectangle(JSContext * ctx,JSValue src,bool * error){
		Rectangle ret;
		if(JS_GetClassID(src)==js_Rectangle_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Rectangle_class_id);
			ret =*(Rectangle *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Rectangle");
			error[0]=(bool)1;
			return (Rectangle){0};
		}
		return ret;
	}
	
	static void * js_getvoid_arr(JSContext * ctx,JSValue src,bool * error){
		void * ret;
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			void * js_ret=(void  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =jsc_malloc(ctx,(size_t)size_ret);
			memcpy(ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,ret);
		}else if(JS_IsString(src)){
			int64_t size_ret;
			char * js_ret=(char  *)JS_ToCStringLen(ctx,(size_t  *)&size_ret,src);
			char * js2_ret=(char  *)jsc_malloc(ctx,size_ret+1);
			memcpy((void  *)js2_ret,(const void  *)js_ret,(size_t)size_ret);
			js2_ret[size_ret]=(char)0;
			ret=(void  *)js2_ret;
			JS_FreeCString(ctx,(const char  *)js_ret);
		}else if(JS_GetTypedArrayType(src)!=-1){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			void * js_ret=(void  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =jsc_malloc(ctx,size_ret);
			memcpy(ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type void *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static int js_getint(JSContext * ctx,JSValue src,bool * error){
		int ret;
		if(JS_IsNumber(src)){
			int32_t long_ret;
			JS_ToInt32(ctx,&long_ret,src);
			ret =((int)long_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type int");
			error[0]=(bool)1;
			return 0;
		}
		return ret;
	}
	
	static Image js_getImage(JSContext * ctx,JSValue src,bool * error){
		Image ret;
		if(JS_GetClassID(src)==js_Image_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Image_class_id);
			ret =*(Image *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Image");
			error[0]=(bool)1;
			return (Image){0};
		}
		return ret;
	}
	
	static unsigned int js_getunsignedint(JSContext * ctx,JSValue src,bool * error){
		unsigned int ret;
		if(JS_IsNumber(src)){
			uint32_t long_ret;
			JS_ToUint32(ctx,&long_ret,src);
			ret =((unsigned int)long_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned int");
			error[0]=(bool)1;
			return 0;
		}
		return ret;
	}
	
	static Texture js_getTexture(JSContext * ctx,JSValue src,bool * error){
		Texture ret;
		if(JS_GetClassID(src)==js_Texture_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Texture_class_id);
			ret =*(Texture *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Texture");
			error[0]=(bool)1;
			return (Texture){0};
		}
		return ret;
	}
	
	static RenderTexture js_getRenderTexture(JSContext * ctx,JSValue src,bool * error){
		RenderTexture ret;
		if(JS_GetClassID(src)==js_RenderTexture_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_RenderTexture_class_id);
			ret =*(RenderTexture *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type RenderTexture");
			error[0]=(bool)1;
			return (RenderTexture){0};
		}
		return ret;
	}
	
	static NPatchInfo js_getNPatchInfo(JSContext * ctx,JSValue src,bool * error){
		NPatchInfo ret;
		if(JS_GetClassID(src)==js_NPatchInfo_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_NPatchInfo_class_id);
			ret =*(NPatchInfo *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type NPatchInfo");
			error[0]=(bool)1;
			return (NPatchInfo){0};
		}
		return ret;
	}
	
	static GlyphInfo js_getGlyphInfo(JSContext * ctx,JSValue src,bool * error){
		GlyphInfo ret;
		if(JS_GetClassID(src)==js_GlyphInfo_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_GlyphInfo_class_id);
			ret =*(GlyphInfo *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type GlyphInfo");
			error[0]=(bool)1;
			return (GlyphInfo){0};
		}
		return ret;
	}
	
	static Texture2D js_getTexture2D(JSContext * ctx,JSValue src,bool * error){
		Texture2D ret;
		if(JS_GetClassID(src)==js_Texture_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Texture_class_id);
			ret =*(Texture2D *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Texture2D");
			error[0]=(bool)1;
			return (Texture2D){0};
		}
		return ret;
	}
	
	static Rectangle * js_getRectangle_arrnc(JSContext * ctx,JSValue src,bool * error){
		Rectangle * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Rectangle_class_id){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Rectangle  *)jsc_malloc(ctx,size_ret*sizeof(Rectangle));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==js_Rectangle_class_id){
						opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Rectangle_class_id);
						ret[i] =*(Rectangle *)tmpshadow[0].ptr;
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Rectangle *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(jsc_free,(void  *)ret);
			}else if(JS_IsNumber(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				size_ret -=size_ret%4;
				ret =(Rectangle  *)jsc_malloc(ctx,size_ret*sizeof(float));
				for(int i=0;i<size_ret;i++){
					float * tmp_obj=(float  *)ret;
					for(int i0=0;i0<4;i0++){
						src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
						JS_FreeValue(ctx,src0);
						if(JS_IsNumber(src0)){
							double double_tmp_objii0;
							JS_ToFloat64(ctx,&double_tmp_objii0,src0);
							tmp_obj[i+i0] =((float)double_tmp_objii0);
						}else{
							JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Rectangle *");
							error[0]=(bool)1;
							return NULL;
						}
					}
					i +=3;
				}
				memoryStore(jsc_free,(void  *)ret);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Rectangle *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			Rectangle * js_ret=(Rectangle  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(Rectangle  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			Rectangle * js_ret=(Rectangle  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(Rectangle  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_Rectangle_class_id){
			if(JS_GetClassID(src)==js_Rectangle_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Rectangle_class_id);
				ret =(Rectangle  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Rectangle *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Rectangle *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static GlyphInfo * js_getGlyphInfo_arrnc(JSContext * ctx,JSValue src,bool * error){
		GlyphInfo * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(GlyphInfo  *)jsc_malloc(ctx,size_ret*sizeof(GlyphInfo));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_GlyphInfo_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_GlyphInfo_class_id);
					ret[i] =*(GlyphInfo *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type GlyphInfo *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_GlyphInfo_class_id){
			if(JS_GetClassID(src)==js_GlyphInfo_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_GlyphInfo_class_id);
				ret =(GlyphInfo  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type GlyphInfo *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type GlyphInfo *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Font js_getFont(JSContext * ctx,JSValue src,bool * error){
		Font ret;
		if(JS_GetClassID(src)==js_Font_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Font_class_id);
			ret =*(Font *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Font");
			error[0]=(bool)1;
			return (Font){0};
		}
		return ret;
	}
	
	static Font Font_copy(JSContext * ctx,Font ptr){
		Font ret=ptr;
		ret.recs =(Rectangle  *)jsc_malloc(ctx,sizeof(Rectangle *)*ptr.glyphCount);
		for(int i=0;i<ptr.glyphCount;i++){
			ret.recs[i] =ptr.recs[i];
		}
		ret.glyphs =(GlyphInfo  *)jsc_malloc(ctx,sizeof(GlyphInfo *)*ptr.glyphCount);
		for(int i0=0;i0<ptr.glyphCount;i0++){
			ret.glyphs[i0] =ptr.glyphs[i0];
		}
		return ret;
	}
	
	static Camera3D js_getCamera3D(JSContext * ctx,JSValue src,bool * error){
		Camera3D ret;
		if(JS_GetClassID(src)==js_Camera3D_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Camera3D_class_id);
			ret =*(Camera3D *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Camera3D");
			error[0]=(bool)1;
			return (Camera3D){0};
		}
		return ret;
	}
	
	static Camera2D js_getCamera2D(JSContext * ctx,JSValue src,bool * error){
		Camera2D ret;
		if(JS_GetClassID(src)==js_Camera2D_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Camera2D_class_id);
			ret =*(Camera2D *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Camera2D");
			error[0]=(bool)1;
			return (Camera2D){0};
		}
		return ret;
	}
	
	static float * js_getfloat_arrnc(JSContext * ctx,JSValue src,bool * error){
		float * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			float * js_ret=(float  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(float  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(float  *)jsc_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					double double_reti;
					JS_ToFloat64(ctx,&double_reti,src0);
					ret[i] =((float)double_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type float *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			float * js_ret=(float  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(float  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type float *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static unsigned char * js_getunsignedchar_arrnc(JSContext * ctx,JSValue src,bool * error){
		unsigned char * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			unsigned char * js_ret=(unsigned char  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(unsigned char  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(unsigned char  *)jsc_malloc(ctx,size_ret*sizeof(unsigned char));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					uint32_t long_reti;
					JS_ToUint32(ctx,&long_reti,src0);
					ret[i] =((unsigned char)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type unsigned char *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_UINT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			unsigned char * js_ret=(unsigned char  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(unsigned char  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned char *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static unsigned short js_getunsignedshort(JSContext * ctx,JSValue src,bool * error){
		unsigned short ret;
		if(JS_IsNumber(src)){
			uint32_t long_ret;
			JS_ToUint32(ctx,&long_ret,src);
			ret =((unsigned short)long_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned short");
			error[0]=(bool)1;
			return 0;
		}
		return ret;
	}
	
	static unsigned short * js_getunsignedshort_arrnc(JSContext * ctx,JSValue src,bool * error){
		unsigned short * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			unsigned short * js_ret=(unsigned short  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(unsigned short  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(unsigned short  *)jsc_malloc(ctx,size_ret*sizeof(unsigned short));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					uint32_t long_reti;
					JS_ToUint32(ctx,&long_reti,src0);
					ret[i] =((unsigned short)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type unsigned short *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_UINT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			unsigned short * js_ret=(unsigned short  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(unsigned short  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned short *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Matrix * js_getMatrix_arrnc(JSContext * ctx,JSValue src,bool * error){
		Matrix * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Matrix_class_id){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Matrix  *)jsc_malloc(ctx,size_ret*sizeof(Matrix));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==js_Matrix_class_id){
						opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Matrix_class_id);
						ret[i] =*(Matrix *)tmpshadow[0].ptr;
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Matrix *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(jsc_free,(void  *)ret);
			}else if(JS_IsNumber(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				size_ret -=size_ret%16;
				ret =(Matrix  *)jsc_malloc(ctx,size_ret*sizeof(float));
				for(int i=0;i<size_ret;i++){
					float * tmp_obj=(float  *)ret;
					for(int i0=0;i0<16;i0++){
						src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
						JS_FreeValue(ctx,src0);
						if(JS_IsNumber(src0)){
							double double_tmp_objii0;
							JS_ToFloat64(ctx,&double_tmp_objii0,src0);
							tmp_obj[i+i0] =((float)double_tmp_objii0);
						}else{
							JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Matrix *");
							error[0]=(bool)1;
							return NULL;
						}
					}
					i +=15;
				}
				memoryStore(jsc_free,(void  *)ret);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Matrix *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			Matrix * js_ret=(Matrix  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(Matrix  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			Matrix * js_ret=(Matrix  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(Matrix  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_Matrix_class_id){
			if(JS_GetClassID(src)==js_Matrix_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Matrix_class_id);
				ret =(Matrix  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Matrix *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Matrix *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static unsigned int * js_getunsignedint_arrnc(JSContext * ctx,JSValue src,bool * error){
		unsigned int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			unsigned int * js_ret=(unsigned int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(unsigned int  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(unsigned int  *)jsc_malloc(ctx,size_ret*sizeof(unsigned int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					uint32_t long_reti;
					JS_ToUint32(ctx,&long_reti,src0);
					ret[i] =((unsigned int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type unsigned int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_UINT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			unsigned int * js_ret=(unsigned int  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(unsigned int  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Mesh js_getMesh(JSContext * ctx,JSValue src,bool * error){
		Mesh ret;
		if(JS_GetClassID(src)==js_Mesh_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Mesh_class_id);
			ret =*(Mesh *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Mesh");
			error[0]=(bool)1;
			return (Mesh){0};
		}
		return ret;
	}
	
	static Mesh Mesh_copy(JSContext * ctx,Mesh ptr){
		Mesh ret=ptr;
		ret.vertices =(float  *)jsc_malloc(ctx,sizeof(float *)*ptr.vertexCount*3);
		for(int i=0;i<ptr.vertexCount*3;i++){
		}
		ret.texcoords =(float  *)jsc_malloc(ctx,sizeof(float *)*ptr.vertexCount*2);
		for(int i0=0;i0<ptr.vertexCount*2;i0++){
		}
		ret.texcoords2 =(float  *)jsc_malloc(ctx,sizeof(float *)*ptr.vertexCount*2);
		for(int i1=0;i1<ptr.vertexCount*2;i1++){
		}
		ret.normals =(float  *)jsc_malloc(ctx,sizeof(float *)*ptr.vertexCount*3);
		for(int i2=0;i2<ptr.vertexCount*3;i2++){
		}
		ret.tangents =(float  *)jsc_malloc(ctx,sizeof(float *)*ptr.vertexCount*4);
		for(int i3=0;i3<ptr.vertexCount*4;i3++){
		}
		ret.colors =(unsigned char  *)jsc_malloc(ctx,sizeof(unsigned char *)*ptr.vertexCount*4);
		for(int i4=0;i4<ptr.vertexCount*4;i4++){
		}
		ret.indices =(unsigned short  *)jsc_malloc(ctx,sizeof(unsigned short *)*ptr.vertexCount);
		for(int i5=0;i5<ptr.vertexCount;i5++){
		}
		ret.animVertices =(float  *)jsc_malloc(ctx,sizeof(float *)*ptr.vertexCount*3);
		for(int i6=0;i6<ptr.vertexCount*3;i6++){
		}
		ret.animNormals =(float  *)jsc_malloc(ctx,sizeof(float *)*ptr.vertexCount*3);
		for(int i7=0;i7<ptr.vertexCount*3;i7++){
		}
		ret.boneIds =(unsigned char  *)jsc_malloc(ctx,sizeof(unsigned char *)*ptr.vertexCount*4);
		for(int i8=0;i8<ptr.vertexCount*4;i8++){
		}
		ret.boneWeights =(float  *)jsc_malloc(ctx,sizeof(float *)*ptr.vertexCount*4);
		for(int i9=0;i9<ptr.vertexCount*4;i9++){
		}
		ret.boneMatrices =(Matrix  *)jsc_malloc(ctx,sizeof(Matrix *)*ptr.boneCount);
		for(int i10=0;i10<ptr.boneCount;i10++){
			ret.boneMatrices[i10] =ptr.boneMatrices[i10];
		}
		ret.vboId =(unsigned int  *)jsc_malloc(ctx,sizeof(unsigned int *)*MAX_MESH_VERTEX_BUFFERS);
		for(int i11=0;i11<MAX_MESH_VERTEX_BUFFERS;i11++){
		}
		return ret;
	}
	
	static int * js_getint_arrnc(JSContext * ctx,JSValue src,bool * error){
		int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			int * js_ret=(int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(int  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(int  *)jsc_malloc(ctx,size_ret*sizeof(int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					int32_t long_reti;
					JS_ToInt32(ctx,&long_reti,src0);
					ret[i] =((int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_INT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			int * js_ret=(int  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(int  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Shader js_getShader(JSContext * ctx,JSValue src,bool * error){
		Shader ret;
		if(JS_GetClassID(src)==js_Shader_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Shader_class_id);
			ret =*(Shader *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Shader");
			error[0]=(bool)1;
			return (Shader){0};
		}
		return ret;
	}
	
	static Shader Shader_copy(JSContext * ctx,Shader ptr){
		Shader ret=ptr;
		ret.locs =(int  *)jsc_malloc(ctx,sizeof(int *)*RL_MAX_SHADER_LOCATIONS);
		for(int i=0;i<RL_MAX_SHADER_LOCATIONS;i++){
		}
		return ret;
	}
	
	static MaterialMap js_getMaterialMap(JSContext * ctx,JSValue src,bool * error){
		MaterialMap ret;
		if(JS_GetClassID(src)==js_MaterialMap_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_MaterialMap_class_id);
			ret =*(MaterialMap *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type MaterialMap");
			error[0]=(bool)1;
			return (MaterialMap){0};
		}
		return ret;
	}
	
	static MaterialMap * js_getMaterialMap_arrnc(JSContext * ctx,JSValue src,bool * error){
		MaterialMap * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(MaterialMap  *)jsc_malloc(ctx,size_ret*sizeof(MaterialMap));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_MaterialMap_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_MaterialMap_class_id);
					ret[i] =*(MaterialMap *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type MaterialMap *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_MaterialMap_class_id){
			if(JS_GetClassID(src)==js_MaterialMap_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_MaterialMap_class_id);
				ret =(MaterialMap  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type MaterialMap *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type MaterialMap *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static float * js_getfloat_arr4nc(JSContext * ctx,JSValue src,bool * error){
		float * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			float * js_ret=(float  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(float  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else if(js_IsArrayLength(ctx,src,(int64_t)4)){
			int64_t size_ret=(int64_t)4;
			size_ret =(int64_t)4;
			ret =(float  *)jsc_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					double double_reti;
					JS_ToFloat64(ctx,&double_reti,src0);
					ret[i] =((float)double_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type float *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			float * js_ret=(float  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(float  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type float *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Material js_getMaterial(JSContext * ctx,JSValue src,bool * error){
		Material ret;
		if(JS_GetClassID(src)==js_Material_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Material_class_id);
			ret =*(Material *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Material");
			error[0]=(bool)1;
			return (Material){0};
		}
		return ret;
	}
	
	static Material Material_copy(JSContext * ctx,Material ptr){
		Material ret=ptr;
		ret.maps =(MaterialMap  *)jsc_malloc(ctx,sizeof(MaterialMap *)*12);
		for(int i=0;i<12;i++){
			ret.maps[i] =ptr.maps[i];
		}
		return ret;
	}
	
	static Quaternion js_getQuaternion(JSContext * ctx,JSValue src,bool * error){
		Quaternion ret;
		if(JS_GetClassID(src)==js_Vector4_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Vector4_class_id);
			ret =*(Quaternion *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Quaternion");
			error[0]=(bool)1;
			return (Quaternion){0};
		}
		return ret;
	}
	
	static Transform js_getTransform(JSContext * ctx,JSValue src,bool * error){
		Transform ret;
		if(JS_GetClassID(src)==js_Transform_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Transform_class_id);
			ret =*(Transform *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Transform");
			error[0]=(bool)1;
			return (Transform){0};
		}
		return ret;
	}
	
	static char js_getchar(JSContext * ctx,JSValue src,bool * error){
		char ret;
		if(JS_IsString(src)){
			char * js_ret=(char  *)JS_ToCString(ctx,src);
			ret =((char)js_ret[0]);
			JS_FreeCString(ctx,(const char  *)js_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type char");
			error[0]=(bool)1;
			return ' ';
		}
		return ret;
	}
	
	static char * js_getchar_arr32nc(JSContext * ctx,JSValue src,bool * error){
		char * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			char * js_ret=(char  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(char  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else if(js_IsArrayLength(ctx,src,(int64_t)32)){
			int64_t size_ret=(int64_t)32;
			size_ret =(int64_t)32;
			ret =(char  *)jsc_malloc(ctx,size_ret*sizeof(char));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsString(src0)){
					char * js_reti=(char  *)JS_ToCString(ctx,src0);
					ret[i] =((char)js_reti[0]);
					JS_FreeCString(ctx,(const char  *)js_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_INT8_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			char * js_ret=(char  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(char  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsString(src)){
			int64_t size_ret;
			char * js_ret=(char  *)JS_ToCStringLen(ctx,(size_t  *)&size_ret,src);
			char * js2_ret=(char  *)jsc_malloc(ctx,size_ret+1);
			memcpy((void  *)js2_ret,(const void  *)js_ret,(size_t)size_ret);
			js2_ret[size_ret]=(char)0;
			ret=js2_ret;
			JS_FreeCString(ctx,(const char  *)js_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type char *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static BoneInfo js_getBoneInfo(JSContext * ctx,JSValue src,bool * error){
		BoneInfo ret;
		if(JS_GetClassID(src)==js_BoneInfo_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_BoneInfo_class_id);
			ret =*(BoneInfo *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type BoneInfo");
			error[0]=(bool)1;
			return (BoneInfo){0};
		}
		return ret;
	}
	
	static Mesh * js_getMesh_arrnc(JSContext * ctx,JSValue src,bool * error){
		Mesh * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(Mesh  *)jsc_malloc(ctx,size_ret*sizeof(Mesh));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_Mesh_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Mesh_class_id);
					ret[i] =*(Mesh *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Mesh *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_Mesh_class_id){
			if(JS_GetClassID(src)==js_Mesh_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Mesh_class_id);
				ret =(Mesh  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Mesh *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Mesh *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Material * js_getMaterial_arrnc(JSContext * ctx,JSValue src,bool * error){
		Material * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(Material  *)jsc_malloc(ctx,size_ret*sizeof(Material));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_Material_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Material_class_id);
					ret[i] =*(Material *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Material *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_Material_class_id){
			if(JS_GetClassID(src)==js_Material_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Material_class_id);
				ret =(Material  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Material *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Material *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static BoneInfo * js_getBoneInfo_arrnc(JSContext * ctx,JSValue src,bool * error){
		BoneInfo * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(BoneInfo  *)jsc_malloc(ctx,size_ret*sizeof(BoneInfo));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_BoneInfo_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_BoneInfo_class_id);
					ret[i] =*(BoneInfo *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type BoneInfo *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_BoneInfo_class_id){
			if(JS_GetClassID(src)==js_BoneInfo_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_BoneInfo_class_id);
				ret =(BoneInfo  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type BoneInfo *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type BoneInfo *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Transform * js_getTransform_arrnc(JSContext * ctx,JSValue src,bool * error){
		Transform * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(Transform  *)jsc_malloc(ctx,size_ret*sizeof(Transform));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_Transform_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Transform_class_id);
					ret[i] =*(Transform *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Transform *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_Transform_class_id){
			if(JS_GetClassID(src)==js_Transform_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Transform_class_id);
				ret =(Transform  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Transform *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Transform *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Model js_getModel(JSContext * ctx,JSValue src,bool * error){
		Model ret;
		if(JS_GetClassID(src)==js_Model_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Model_class_id);
			ret =*(Model *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Model");
			error[0]=(bool)1;
			return (Model){0};
		}
		return ret;
	}
	
	static Model Model_copy(JSContext * ctx,Model ptr){
		Model ret=ptr;
		ret.meshes =(Mesh  *)jsc_malloc(ctx,sizeof(Mesh *)*ptr.meshCount);
		for(int i=0;i<ptr.meshCount;i++){
			ret.meshes[i] =Mesh_copy(ctx,ptr.meshes[i]);
		}
		ret.materials =(Material  *)jsc_malloc(ctx,sizeof(Material *)*ptr.materialCount);
		for(int i0=0;i0<ptr.materialCount;i0++){
			ret.materials[i0] =Material_copy(ctx,ptr.materials[i0]);
		}
		ret.meshMaterial =(int  *)jsc_malloc(ctx,sizeof(int *)*ptr.meshCount);
		for(int i1=0;i1<ptr.meshCount;i1++){
		}
		ret.bones =(BoneInfo  *)jsc_malloc(ctx,sizeof(BoneInfo *)*ptr.boneCount);
		for(int i2=0;i2<ptr.boneCount;i2++){
			ret.bones[i2] =ptr.bones[i2];
		}
		ret.bindPose =(Transform  *)jsc_malloc(ctx,sizeof(Transform *)*ptr.boneCount);
		for(int i3=0;i3<ptr.boneCount;i3++){
			ret.bindPose[i3] =ptr.bindPose[i3];
		}
		return ret;
	}
	
	static Transform * js_getTransform_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0){
		Transform * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(Transform  *)js_malloc(ctx,size_ret*sizeof(Transform));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_Transform_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Transform_class_id);
					ret[i] =*(Transform *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Transform *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_Transform_class_id){
			if(JS_GetClassID(src)==js_Transform_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Transform_class_id);
				ret =(Transform  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Transform *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Transform *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Transform * * js_getTransform_arr_arrnc(JSContext * ctx,JSValue src,bool * error){
		Transform * * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_ArrayProxy_class_id){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Transform  * *)jsc_malloc(ctx,size_ret*sizeof(Transform *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					bool is_arrayProxy0=(bool)0;
					if(JS_GetClassID(src0)==js_ArrayProxy_class_id){
						is_arrayProxy0 =(bool)1;
						void * AP_opaque=JS_GetOpaque(src0,js_ArrayProxy_class_id);
						ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
						src0 =AP_fn.values(ctx,src0,AP_fn.opaque,(int)0,(bool)false);
					}
					if(JS_IsArray(src0)){
						int64_t size_reti;
						if(JS_GetLength(ctx,src0,&size_reti)==-1){
							error[0]=(bool)1;
							return NULL;
						}
						if(size_reti==0){
							JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
							error[0]=(bool)1;
							return NULL;
						}
						ret[i] =(Transform  *)jsc_malloc(ctx,size_reti*sizeof(Transform));
						for(int i0=0;i0<size_reti;i0++){
							JSValue src00=JS_GetPropertyUint32(ctx,src0,(uint32_t)i0);
							JS_FreeValue(ctx,src00);
							if(JS_GetClassID(src00)==js_Transform_class_id){
								opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src00,js_Transform_class_id);
								ret[i][i0] =*(Transform *)tmpshadow[0].ptr;
							}else{
								JS_ThrowTypeError(ctx,(const char  *)"src00 does not match type Transform * *");
								error[0]=(bool)1;
								return NULL;
							}
						}
						memoryStore(jsc_free,(void  *)ret[i]);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Transform * *");
						error[0]=(bool)1;
						return NULL;
					}
					if(is_arrayProxy0)JS_FreeValue(ctx,src0);
				}
				memoryStore(jsc_free,(void  *)*ret);
			}else if(JS_IsArray(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Transform  * *)jsc_malloc(ctx,size_ret*sizeof(Transform *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_IsArray(src0)){
						int64_t size_reti;
						if(JS_GetLength(ctx,src0,&size_reti)==-1){
							error[0]=(bool)1;
							return NULL;
						}
						if(size_reti==0){
							JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
							error[0]=(bool)1;
							return NULL;
						}
						ret[i] =(Transform  *)jsc_malloc(ctx,size_reti*sizeof(Transform));
						for(int i0=0;i0<size_reti;i0++){
							JSValue src00=JS_GetPropertyUint32(ctx,src0,(uint32_t)i0);
							JS_FreeValue(ctx,src00);
							if(JS_GetClassID(src00)==js_Transform_class_id){
								opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src00,js_Transform_class_id);
								ret[i][i0] =*(Transform *)tmpshadow[0].ptr;
							}else{
								JS_ThrowTypeError(ctx,(const char  *)"src00 does not match type Transform * *");
								error[0]=(bool)1;
								return NULL;
							}
						}
						memoryStore(jsc_free,(void  *)ret[i]);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Transform * *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(jsc_free,(void  *)*ret);
			}else if(JS_GetClassID(src0)==js_Transform_class_id){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Transform  * *)jsc_malloc(ctx,size_ret*sizeof(Transform *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==js_Transform_class_id){
						if(JS_GetClassID(src0)==js_Transform_class_id){
							opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Transform_class_id);
							ret[i] =(Transform  *)tmpshadow[0].ptr;
						}else{
							JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Transform * *");
							error[0]=(bool)1;
							return NULL;
						}
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Transform * *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(jsc_free,(void  *)*ret);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Transform * *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Transform * *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static ModelAnimation js_getModelAnimation(JSContext * ctx,JSValue src,bool * error){
		ModelAnimation ret;
		if(JS_GetClassID(src)==js_ModelAnimation_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_ModelAnimation_class_id);
			ret =*(ModelAnimation *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type ModelAnimation");
			error[0]=(bool)1;
			return (ModelAnimation){0};
		}
		return ret;
	}
	
	static ModelAnimation ModelAnimation_copy(JSContext * ctx,ModelAnimation ptr){
		ModelAnimation ret=ptr;
		ret.bones =(BoneInfo  *)jsc_malloc(ctx,sizeof(BoneInfo *)*ptr.boneCount);
		for(int i=0;i<ptr.boneCount;i++){
			ret.bones[i] =ptr.bones[i];
		}
		ret.framePoses =(Transform  * *)jsc_malloc(ctx,sizeof(Transform * *)*ptr.frameCount);
		for(int i0=0;i0<ptr.frameCount;i0++){
			Transform * framePoses_src1=ptr.framePoses[i0];
			Transform * framePoses_target1=ret.framePoses[i0];
			framePoses_target1 =(Transform  *)jsc_malloc(ctx,sizeof(Transform *)*ptr.boneCount);
			for(int i1=0;i1<ptr.boneCount;i1++){
				framePoses_target1[i1] =framePoses_src1[i1];
			}
		}
		return ret;
	}
	
	static Ray js_getRay(JSContext * ctx,JSValue src,bool * error){
		Ray ret;
		if(JS_GetClassID(src)==js_Ray_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Ray_class_id);
			ret =*(Ray *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Ray");
			error[0]=(bool)1;
			return (Ray){0};
		}
		return ret;
	}
	
	static bool js_getbool(JSContext * ctx,JSValue src,bool * error){
		bool ret;
		if(JS_IsBool(src)){
			int js_ret=JS_ToBool(ctx,src);
			ret =(bool)js_ret;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type bool");
			error[0]=(bool)1;
			return false;
		}
		return ret;
	}
	
	static RayCollision js_getRayCollision(JSContext * ctx,JSValue src,bool * error){
		RayCollision ret;
		if(JS_GetClassID(src)==js_RayCollision_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_RayCollision_class_id);
			ret =*(RayCollision *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type RayCollision");
			error[0]=(bool)1;
			return (RayCollision){0};
		}
		return ret;
	}
	
	static BoundingBox js_getBoundingBox(JSContext * ctx,JSValue src,bool * error){
		BoundingBox ret;
		if(JS_GetClassID(src)==js_BoundingBox_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_BoundingBox_class_id);
			ret =*(BoundingBox *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type BoundingBox");
			error[0]=(bool)1;
			return (BoundingBox){0};
		}
		return ret;
	}
	
	static short js_getshort(JSContext * ctx,JSValue src,bool * error){
		short ret;
		if(JS_IsNumber(src)){
			int32_t long_ret;
			JS_ToInt32(ctx,&long_ret,src);
			ret =((short)long_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type short");
			error[0]=(bool)1;
			return 0;
		}
		return ret;
	}
	
	static Wave js_getWave(JSContext * ctx,JSValue src,bool * error){
		Wave ret;
		if(JS_GetClassID(src)==js_Wave_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Wave_class_id);
			ret =*(Wave *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Wave");
			error[0]=(bool)1;
			return (Wave){0};
		}
		return ret;
	}
	
	static Wave Wave_copy(JSContext * ctx,Wave ptr){
		Wave ret=ptr;
		ret.data =jsc_malloc(ctx,sizeof(void *)*ptr.frameCount*ptr.channels);
		for(int i=0;i<ptr.frameCount*ptr.channels;i++){
		}
		return ret;
	}
	
	static AudioStream js_getAudioStream(JSContext * ctx,JSValue src,bool * error){
		AudioStream ret;
		if(JS_GetClassID(src)==js_AudioStream_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_AudioStream_class_id);
			ret =*(AudioStream *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type AudioStream");
			error[0]=(bool)1;
			return (AudioStream){0};
		}
		return ret;
	}
	
	static rAudioBuffer * js_getrAudioBuffer_ptrnc(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		rAudioBuffer * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_rAudioBuffer_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_rAudioBuffer_class_id);
				ret =(rAudioBuffer  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type rAudioBuffer *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_rAudioBuffer_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_rAudioBuffer_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_rAudioBuffer_class_id);
				ret =(rAudioBuffer  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type rAudioBuffer *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type rAudioBuffer *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static rAudioProcessor * js_getrAudioProcessor_ptrnc(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		rAudioProcessor * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_rAudioProcessor_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_rAudioProcessor_class_id);
				ret =(rAudioProcessor  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type rAudioProcessor *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_rAudioProcessor_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_rAudioProcessor_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_rAudioProcessor_class_id);
				ret =(rAudioProcessor  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type rAudioProcessor *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type rAudioProcessor *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static Sound js_getSound(JSContext * ctx,JSValue src,bool * error){
		Sound ret;
		if(JS_GetClassID(src)==js_Sound_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Sound_class_id);
			ret =*(Sound *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Sound");
			error[0]=(bool)1;
			return (Sound){0};
		}
		return ret;
	}
	
	static Music js_getMusic(JSContext * ctx,JSValue src,bool * error){
		Music ret;
		if(JS_GetClassID(src)==js_Music_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Music_class_id);
			ret =*(Music *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Music");
			error[0]=(bool)1;
			return (Music){0};
		}
		return ret;
	}
	
	static VrDeviceInfo js_getVrDeviceInfo(JSContext * ctx,JSValue src,bool * error){
		VrDeviceInfo ret;
		if(JS_GetClassID(src)==js_VrDeviceInfo_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_VrDeviceInfo_class_id);
			ret =*(VrDeviceInfo *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type VrDeviceInfo");
			error[0]=(bool)1;
			return (VrDeviceInfo){0};
		}
		return ret;
	}
	
	static Matrix * js_getMatrix_arr2nc(JSContext * ctx,JSValue src,bool * error){
		Matrix * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(js_IsArrayLength(ctx,src,(int64_t)2)){
			int64_t size_ret=(int64_t)32;
			size_ret =(int64_t)2;
			ret =(Matrix  *)jsc_malloc(ctx,size_ret*sizeof(Matrix));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_Matrix_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Matrix_class_id);
					ret[i] =*(Matrix *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Matrix *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(js_IsArrayLength(ctx,src,(int64_t)32)){
			int64_t size_ret=(int64_t)32;
			size_ret =(int64_t)32;
			size_ret -=size_ret%16;
			ret =(Matrix  *)jsc_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				float * tmp_obj=(float  *)ret;
				for(int i0=0;i0<16;i0++){
					JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
					JS_FreeValue(ctx,src0);
					if(JS_IsNumber(src0)){
						double double_tmp_objii0;
						JS_ToFloat64(ctx,&double_tmp_objii0,src0);
						tmp_obj[i+i0] =((float)double_tmp_objii0);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Matrix *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				i +=15;
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			Matrix * js_ret=(Matrix  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(Matrix  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			Matrix * js_ret=(Matrix  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(Matrix  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Matrix *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static float * js_getfloat_arr2nc(JSContext * ctx,JSValue src,bool * error){
		float * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			float * js_ret=(float  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(float  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else if(js_IsArrayLength(ctx,src,(int64_t)2)){
			int64_t size_ret=(int64_t)2;
			size_ret =(int64_t)2;
			ret =(float  *)jsc_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					double double_reti;
					JS_ToFloat64(ctx,&double_reti,src0);
					ret[i] =((float)double_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type float *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			float * js_ret=(float  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(float  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type float *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static VrStereoConfig js_getVrStereoConfig(JSContext * ctx,JSValue src,bool * error){
		VrStereoConfig ret;
		if(JS_GetClassID(src)==js_VrStereoConfig_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_VrStereoConfig_class_id);
			ret =*(VrStereoConfig *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type VrStereoConfig");
			error[0]=(bool)1;
			return (VrStereoConfig){0};
		}
		return ret;
	}
	
	static char * js_getchar_arr(JSContext * ctx,JSValue src,bool * error){
		char * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(char  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(char  *)js_malloc(ctx,size_ret*sizeof(char));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsString(src0)){
					char * js_reti=(char  *)JS_ToCString(ctx,src0);
					ret[i] =((char)js_reti[0]);
					JS_FreeCString(ctx,(const char  *)js_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_INT8_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(char  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsString(src)){
			char * js_ret=(char  *)JS_ToCStringLen(ctx,NULL,src);
			memoryStore(JS_FreeCString,(void  *)js_ret);
			ret=js_ret;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type char *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static char * * js_getchar_arr_arrnc(JSContext * ctx,JSValue src,bool * error){
		char * * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_IsArrayBuffer(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char  * *)jsc_malloc(ctx,size_ret*sizeof(char *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_IsArrayBuffer(src0)){
						int64_t size_reti;
						char * js_reti=(char  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_reti,src0);
						ret[i] =(char  *)jsc_malloc(ctx,(size_t)size_reti);
						memcpy((void  *)ret[i],(const void  *)js_reti,(size_t)size_reti);
						memoryStore(jsc_free,(void  *)ret[i]);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char * *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(jsc_free,(void  *)*ret);
			}else if(JS_GetClassID(src0)==js_ArrayProxy_class_id){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char  * *)jsc_malloc(ctx,size_ret*sizeof(char *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					bool is_arrayProxy0=(bool)0;
					if(JS_GetClassID(src0)==js_ArrayProxy_class_id){
						is_arrayProxy0 =(bool)1;
						void * AP_opaque=JS_GetOpaque(src0,js_ArrayProxy_class_id);
						ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
						src0 =AP_fn.values(ctx,src0,AP_fn.opaque,(int)0,(bool)false);
					}
					if(JS_IsArray(src0)){
						int64_t size_reti;
						if(JS_GetLength(ctx,src0,&size_reti)==-1){
							error[0]=(bool)1;
							return NULL;
						}
						if(size_reti==0){
							JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
							error[0]=(bool)1;
							return NULL;
						}
						ret[i] =(char  *)jsc_malloc(ctx,size_reti*sizeof(char));
						for(int i0=0;i0<size_reti;i0++){
							JSValue src00=JS_GetPropertyUint32(ctx,src0,(uint32_t)i0);
							JS_FreeValue(ctx,src00);
							if(JS_IsString(src00)){
								char * js_retii0=(char  *)JS_ToCString(ctx,src00);
								ret[i][i0] =((char)js_retii0[0]);
								JS_FreeCString(ctx,(const char  *)js_retii0);
							}else{
								JS_ThrowTypeError(ctx,(const char  *)"src00 does not match type char * *");
								error[0]=(bool)1;
								return NULL;
							}
						}
						memoryStore(jsc_free,(void  *)ret[i]);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char * *");
						error[0]=(bool)1;
						return NULL;
					}
					if(is_arrayProxy0)JS_FreeValue(ctx,src0);
				}
				memoryStore(jsc_free,(void  *)*ret);
			}else if(JS_IsArray(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char  * *)jsc_malloc(ctx,size_ret*sizeof(char *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_IsArray(src0)){
						int64_t size_reti;
						if(JS_GetLength(ctx,src0,&size_reti)==-1){
							error[0]=(bool)1;
							return NULL;
						}
						if(size_reti==0){
							JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
							error[0]=(bool)1;
							return NULL;
						}
						ret[i] =(char  *)jsc_malloc(ctx,size_reti*sizeof(char));
						for(int i0=0;i0<size_reti;i0++){
							JSValue src00=JS_GetPropertyUint32(ctx,src0,(uint32_t)i0);
							JS_FreeValue(ctx,src00);
							if(JS_IsString(src00)){
								char * js_retii0=(char  *)JS_ToCString(ctx,src00);
								ret[i][i0] =((char)js_retii0[0]);
								JS_FreeCString(ctx,(const char  *)js_retii0);
							}else{
								JS_ThrowTypeError(ctx,(const char  *)"src00 does not match type char * *");
								error[0]=(bool)1;
								return NULL;
							}
						}
						memoryStore(jsc_free,(void  *)ret[i]);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char * *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(jsc_free,(void  *)*ret);
			}else if(JS_GetClassID(src0)==JS_CLASS_INT8_ARRAY){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char  * *)jsc_malloc(ctx,size_ret*sizeof(char *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==JS_CLASS_INT8_ARRAY){
						size_t offset_reti;
						size_t size_reti;
						JSValue da_reti=JS_GetTypedArrayBuffer(ctx,src0,&offset_reti,&size_reti,NULL);
						char * js_reti=(char  *)JS_GetArrayBuffer(ctx,&size_reti,da_reti);
						ret[i] =(char  *)jsc_malloc(ctx,size_reti);
						memcpy((void  *)ret[i],(const void  *)js_reti,size_reti);
						memoryStore(jsc_free,(void  *)ret[i]);
						ret[i] +=offset_reti;
						size_reti -=offset_reti;
						JS_FreeValuePtr(ctx,&da_reti);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char * *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(jsc_free,(void  *)*ret);
			}else if(JS_IsString(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char  * *)jsc_malloc(ctx,size_ret*sizeof(char *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_IsString(src0)){
						int64_t size_reti;
						char * js_reti=(char  *)JS_ToCStringLen(ctx,(size_t  *)&size_reti,src0);
						char * js2_reti=(char  *)jsc_malloc(ctx,size_reti+1);
						memcpy((void  *)js2_reti,(const void  *)js_reti,(size_t)size_reti);
						js2_reti[size_reti]=(char)0;
						ret[i]=js2_reti;
						JS_FreeCString(ctx,(const char  *)js_reti);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char * *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(jsc_free,(void  *)*ret);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type char * *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type char * *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static FilePathList js_getFilePathList(JSContext * ctx,JSValue src,bool * error){
		FilePathList ret;
		if(JS_GetClassID(src)==js_FilePathList_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_FilePathList_class_id);
			ret =*(FilePathList *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type FilePathList");
			error[0]=(bool)1;
			return (FilePathList){0};
		}
		return ret;
	}
	
	static FilePathList FilePathList_copy(JSContext * ctx,FilePathList ptr){
		FilePathList ret=ptr;
		ret.paths =(char  * *)jsc_malloc(ctx,sizeof(char * *)*ptr.count);
		for(int i=0;i<ptr.count;i++){
		}
		return ret;
	}
	
	static int * js_getint_arr4nc(JSContext * ctx,JSValue src,bool * error){
		int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			int * js_ret=(int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
			ret =(int  *)jsc_malloc(ctx,(size_t)size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,(size_t)size_ret);
			memoryStore(jsc_free,(void  *)ret);
		}else if(js_IsArrayLength(ctx,src,(int64_t)4)){
			int64_t size_ret=(int64_t)4;
			size_ret =(int64_t)4;
			ret =(int  *)jsc_malloc(ctx,size_ret*sizeof(int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					int32_t long_reti;
					JS_ToInt32(ctx,&long_reti,src0);
					ret[i] =((int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_INT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			int * js_ret=(int  *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret =(int  *)jsc_malloc(ctx,size_ret);
			memcpy((void  *)ret,(const void  *)js_ret,size_ret);
			memoryStore(jsc_free,(void  *)ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static AutomationEvent js_getAutomationEvent(JSContext * ctx,JSValue src,bool * error){
		AutomationEvent ret;
		if(JS_GetClassID(src)==js_AutomationEvent_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_AutomationEvent_class_id);
			ret =*(AutomationEvent *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type AutomationEvent");
			error[0]=(bool)1;
			return (AutomationEvent){0};
		}
		return ret;
	}
	
	static AutomationEvent * js_getAutomationEvent_arrnc(JSContext * ctx,JSValue src,bool * error){
		AutomationEvent * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(AutomationEvent  *)jsc_malloc(ctx,size_ret*sizeof(AutomationEvent));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_AutomationEvent_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_AutomationEvent_class_id);
					ret[i] =*(AutomationEvent *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type AutomationEvent *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_AutomationEvent_class_id){
			if(JS_GetClassID(src)==js_AutomationEvent_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_AutomationEvent_class_id);
				ret =(AutomationEvent  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type AutomationEvent *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type AutomationEvent *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static AutomationEventList js_getAutomationEventList(JSContext * ctx,JSValue src,bool * error){
		AutomationEventList ret;
		if(JS_GetClassID(src)==js_AutomationEventList_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_AutomationEventList_class_id);
			ret =*(AutomationEventList *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type AutomationEventList");
			error[0]=(bool)1;
			return (AutomationEventList){0};
		}
		return ret;
	}
	
	static AutomationEventList AutomationEventList_copy(JSContext * ctx,AutomationEventList ptr){
		AutomationEventList ret=ptr;
		ret.events =(AutomationEvent  *)jsc_malloc(ctx,sizeof(AutomationEvent *)*ptr.count);
		for(int i=0;i<ptr.count;i++){
			ret.events[i] =ptr.events[i];
		}
		return ret;
	}
	
	static int * js_getint_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		int * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			ret =(int  *)js_malloc(ctx,sizeof(int));
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_IsNumber(src0)){
				int32_t long_ret0;
				JS_ToInt32(ctx,&long_ret0,src0);
				ret[0] =((int)long_ret0);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type int *");
				error[0]=(bool)1;
				return NULL;
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_IsNumber(src)){
			isptr[0]=(bool)true;
			ret =(int  *)js_malloc(ctx,sizeof(int));
			memoryStore(js_free,(void  *)ret);
			if(JS_IsNumber(src)){
				int32_t long_ret0;
				JS_ToInt32(ctx,&long_ret0,src);
				ret[0] =((int)long_ret0);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type int *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type int *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static unsigned char * js_getunsignedchar_arr(JSContext * ctx,JSValue src,bool * error){
		unsigned char * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(unsigned char  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(unsigned char  *)js_malloc(ctx,size_ret*sizeof(unsigned char));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					uint32_t long_reti;
					JS_ToUint32(ctx,&long_reti,src0);
					ret[i] =((unsigned char)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type unsigned char *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_UINT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(unsigned char  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned char *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Image * js_getImage_arr(JSContext * ctx,JSValue src,bool * error){
		Image * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(Image  *)js_malloc(ctx,size_ret*sizeof(Image));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_Image_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Image_class_id);
					ret[i] =*(Image *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Image *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_Image_class_id){
			if(JS_GetClassID(src)==js_Image_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Image_class_id);
				ret =(Image  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Image *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Image *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static RenderTexture2D js_getRenderTexture2D(JSContext * ctx,JSValue src,bool * error){
		RenderTexture2D ret;
		if(JS_GetClassID(src)==js_RenderTexture_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_RenderTexture_class_id);
			ret =*(RenderTexture2D *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type RenderTexture2D");
			error[0]=(bool)1;
			return (RenderTexture2D){0};
		}
		return ret;
	}
	
	static char * js_getchar_arrnull(JSContext * ctx,JSValue src,bool * error){
		char * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(char  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0)return NULL;
			ret =(char  *)js_malloc(ctx,size_ret*sizeof(char));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsString(src0)){
					char * js_reti=(char  *)JS_ToCString(ctx,src0);
					ret[i] =((char)js_reti[0]);
					JS_FreeCString(ctx,(const char  *)js_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_INT8_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(char  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsString(src)){
			char * js_ret=(char  *)JS_ToCStringLen(ctx,NULL,src);
			memoryStore(JS_FreeCString,(void  *)js_ret);
			ret=js_ret;
		}else if(JS_IsNull(src)||JS_IsUndefined(src)){
			ret =NULL;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type char *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static float * js_getfloat_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		float * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			ret =(float  *)js_malloc(ctx,sizeof(float));
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_IsNumber(src0)){
				double double_ret0;
				JS_ToFloat64(ctx,&double_ret0,src0);
				ret[0] =((float)double_ret0);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type float *");
				error[0]=(bool)1;
				return NULL;
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_IsNumber(src)){
			isptr[0]=(bool)true;
			ret =(float  *)js_malloc(ctx,sizeof(float));
			memoryStore(js_free,(void  *)ret);
			if(JS_IsNumber(src)){
				double double_ret0;
				JS_ToFloat64(ctx,&double_ret0,src);
				ret[0] =((float)double_ret0);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type float *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type float *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static Vector2 * js_getVector2_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		Vector2 * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)2;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Vector2_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Vector2_class_id);
				ret =(Vector2  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector2 *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(js_IsArrayLength(ctx,src,(int64_t)2)){
			int64_t size_ret=(int64_t)2;
			size_ret =(int64_t)2;
			size_ret -=size_ret%2;
			ret =(Vector2  *)js_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				float * tmp_obj=(float  *)ret;
				for(int i0=0;i0<2;i0++){
					JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
					JS_FreeValue(ctx,src0);
					if(JS_IsNumber(src0)){
						double double_tmp_objii0;
						JS_ToFloat64(ctx,&double_tmp_objii0,src0);
						tmp_obj[i+i0] =((float)double_tmp_objii0);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector2 *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				i +=1;
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_Vector2_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_Vector2_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Vector2_class_id);
				ret =(Vector2  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector2 *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector2 *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static Vector3 * js_getVector3_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		Vector3 * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)3;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Vector3_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Vector3_class_id);
				ret =(Vector3  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector3 *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(js_IsArrayLength(ctx,src,(int64_t)3)){
			int64_t size_ret=(int64_t)3;
			size_ret =(int64_t)3;
			size_ret -=size_ret%3;
			ret =(Vector3  *)js_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				float * tmp_obj=(float  *)ret;
				for(int i0=0;i0<3;i0++){
					JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
					JS_FreeValue(ctx,src0);
					if(JS_IsNumber(src0)){
						double double_tmp_objii0;
						JS_ToFloat64(ctx,&double_tmp_objii0,src0);
						tmp_obj[i+i0] =((float)double_tmp_objii0);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector3 *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				i +=2;
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_Vector3_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_Vector3_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Vector3_class_id);
				ret =(Vector3  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector3 *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector3 *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static Vector4 * js_getVector4_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		Vector4 * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)4;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Vector4_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Vector4_class_id);
				ret =(Vector4  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector4 *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(js_IsArrayLength(ctx,src,(int64_t)4)){
			int64_t size_ret=(int64_t)4;
			size_ret =(int64_t)4;
			size_ret -=size_ret%4;
			ret =(Vector4  *)js_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				float * tmp_obj=(float  *)ret;
				for(int i0=0;i0<4;i0++){
					JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
					JS_FreeValue(ctx,src0);
					if(JS_IsNumber(src0)){
						double double_tmp_objii0;
						JS_ToFloat64(ctx,&double_tmp_objii0,src0);
						tmp_obj[i+i0] =((float)double_tmp_objii0);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector4 *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				i +=3;
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_Vector4_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_Vector4_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Vector4_class_id);
				ret =(Vector4  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector4 *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector4 *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static int * js_getint_arr2(JSContext * ctx,JSValue src,bool * error){
		int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(js_IsArrayLength(ctx,src,(int64_t)2)){
			int64_t size_ret=(int64_t)2;
			size_ret =(int64_t)2;
			ret =(int  *)js_malloc(ctx,size_ret*sizeof(int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					int32_t long_reti;
					JS_ToInt32(ctx,&long_reti,src0);
					ret[i] =((int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_INT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(int  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static int * js_getint_arr3(JSContext * ctx,JSValue src,bool * error){
		int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(js_IsArrayLength(ctx,src,(int64_t)3)){
			int64_t size_ret=(int64_t)3;
			size_ret =(int64_t)3;
			ret =(int  *)js_malloc(ctx,size_ret*sizeof(int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					int32_t long_reti;
					JS_ToInt32(ctx,&long_reti,src0);
					ret[i] =((int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_INT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(int  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static int * js_getint_arr4(JSContext * ctx,JSValue src,bool * error){
		int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(js_IsArrayLength(ctx,src,(int64_t)4)){
			int64_t size_ret=(int64_t)4;
			size_ret =(int64_t)4;
			ret =(int  *)js_malloc(ctx,size_ret*sizeof(int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					int32_t long_reti;
					JS_ToInt32(ctx,&long_reti,src0);
					ret[i] =((int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_INT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(int  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static unsigned int * js_getunsignedint_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		unsigned int * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			ret =(unsigned int  *)js_malloc(ctx,sizeof(unsigned int));
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_IsNumber(src0)){
				uint32_t long_ret0;
				JS_ToUint32(ctx,&long_ret0,src0);
				ret[0] =((unsigned int)long_ret0);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type unsigned int *");
				error[0]=(bool)1;
				return NULL;
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_IsNumber(src)){
			isptr[0]=(bool)true;
			ret =(unsigned int  *)js_malloc(ctx,sizeof(unsigned int));
			memoryStore(js_free,(void  *)ret);
			if(JS_IsNumber(src)){
				uint32_t long_ret0;
				JS_ToUint32(ctx,&long_ret0,src);
				ret[0] =((unsigned int)long_ret0);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned int *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned int *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static unsigned int * js_getunsignedint_arr2(JSContext * ctx,JSValue src,bool * error){
		unsigned int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(unsigned int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(js_IsArrayLength(ctx,src,(int64_t)2)){
			int64_t size_ret=(int64_t)2;
			size_ret =(int64_t)2;
			ret =(unsigned int  *)js_malloc(ctx,size_ret*sizeof(unsigned int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					uint32_t long_reti;
					JS_ToUint32(ctx,&long_reti,src0);
					ret[i] =((unsigned int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type unsigned int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_UINT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(unsigned int  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static unsigned int * js_getunsignedint_arr3(JSContext * ctx,JSValue src,bool * error){
		unsigned int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(unsigned int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(js_IsArrayLength(ctx,src,(int64_t)3)){
			int64_t size_ret=(int64_t)3;
			size_ret =(int64_t)3;
			ret =(unsigned int  *)js_malloc(ctx,size_ret*sizeof(unsigned int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					uint32_t long_reti;
					JS_ToUint32(ctx,&long_reti,src0);
					ret[i] =((unsigned int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type unsigned int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_UINT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(unsigned int  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static unsigned int * js_getunsignedint_arr4(JSContext * ctx,JSValue src,bool * error){
		unsigned int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(unsigned int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(js_IsArrayLength(ctx,src,(int64_t)4)){
			int64_t size_ret=(int64_t)4;
			size_ret =(int64_t)4;
			ret =(unsigned int  *)js_malloc(ctx,size_ret*sizeof(unsigned int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					uint32_t long_reti;
					JS_ToUint32(ctx,&long_reti,src0);
					ret[i] =((unsigned int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type unsigned int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_UINT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(unsigned int  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static float * js_getfloat_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0){
		float * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(float  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(js_IsArrayLength(ctx,src,(int64_t)size0)){
			int64_t size_ret=(int64_t)size0;
			ret =(float  *)js_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					double double_reti;
					JS_ToFloat64(ctx,&double_reti,src0);
					ret[i] =((float)double_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type float *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(float  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type float *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Vector2 * js_getVector2_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0){
		Vector2 * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(js_IsArrayLength(ctx,src,(int64_t)size0)){
			int64_t size_ret=(int64_t)size0*2;
			ret =(Vector2  *)js_malloc(ctx,size_ret*sizeof(Vector2));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_Vector2_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Vector2_class_id);
					ret[i] =*(Vector2 *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector2 *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(js_IsArrayLength(ctx,src,(int64_t)size0*2)){
			int64_t size_ret=(int64_t)size0*2;
			size_ret -=size_ret%2;
			ret =(Vector2  *)js_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				float * tmp_obj=(float  *)ret;
				for(int i0=0;i0<2;i0++){
					JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
					JS_FreeValue(ctx,src0);
					if(JS_IsNumber(src0)){
						double double_tmp_objii0;
						JS_ToFloat64(ctx,&double_tmp_objii0,src0);
						tmp_obj[i+i0] =((float)double_tmp_objii0);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector2 *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				i +=1;
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(Vector2  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(Vector2  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector2 *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Vector3 * js_getVector3_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0){
		Vector3 * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(js_IsArrayLength(ctx,src,(int64_t)size0)){
			int64_t size_ret=(int64_t)size0*3;
			ret =(Vector3  *)js_malloc(ctx,size_ret*sizeof(Vector3));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_Vector3_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Vector3_class_id);
					ret[i] =*(Vector3 *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector3 *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(js_IsArrayLength(ctx,src,(int64_t)size0*3)){
			int64_t size_ret=(int64_t)size0*3;
			size_ret -=size_ret%3;
			ret =(Vector3  *)js_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				float * tmp_obj=(float  *)ret;
				for(int i0=0;i0<3;i0++){
					JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
					JS_FreeValue(ctx,src0);
					if(JS_IsNumber(src0)){
						double double_tmp_objii0;
						JS_ToFloat64(ctx,&double_tmp_objii0,src0);
						tmp_obj[i+i0] =((float)double_tmp_objii0);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector3 *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				i +=2;
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(Vector3  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(Vector3  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector3 *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Vector4 * js_getVector4_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0){
		Vector4 * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(js_IsArrayLength(ctx,src,(int64_t)size0)){
			int64_t size_ret=(int64_t)size0*4;
			ret =(Vector4  *)js_malloc(ctx,size_ret*sizeof(Vector4));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_Vector4_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Vector4_class_id);
					ret[i] =*(Vector4 *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector4 *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(js_IsArrayLength(ctx,src,(int64_t)size0*4)){
			int64_t size_ret=(int64_t)size0*4;
			size_ret -=size_ret%4;
			ret =(Vector4  *)js_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				float * tmp_obj=(float  *)ret;
				for(int i0=0;i0<4;i0++){
					JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
					JS_FreeValue(ctx,src0);
					if(JS_IsNumber(src0)){
						double double_tmp_objii0;
						JS_ToFloat64(ctx,&double_tmp_objii0,src0);
						tmp_obj[i+i0] =((float)double_tmp_objii0);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector4 *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				i +=3;
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(Vector4  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(Vector4  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector4 *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static int * js_getint_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0){
		int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(js_IsArrayLength(ctx,src,(int64_t)size0)){
			int64_t size_ret=(int64_t)size0;
			ret =(int  *)js_malloc(ctx,size_ret*sizeof(int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					int32_t long_reti;
					JS_ToInt32(ctx,&long_reti,src0);
					ret[i] =((int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_INT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(int  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static unsigned int * js_getunsignedint_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0){
		unsigned int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(unsigned int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(js_IsArrayLength(ctx,src,(int64_t)size0)){
			int64_t size_ret=(int64_t)size0;
			ret =(unsigned int  *)js_malloc(ctx,size_ret*sizeof(unsigned int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					uint32_t long_reti;
					JS_ToUint32(ctx,&long_reti,src0);
					ret[i] =((unsigned int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type unsigned int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_UINT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(unsigned int  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type unsigned int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Camera js_getCamera(JSContext * ctx,JSValue src,bool * error){
		Camera ret;
		if(JS_GetClassID(src)==js_Camera3D_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Camera3D_class_id);
			ret =*(Camera *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Camera");
			error[0]=(bool)1;
			return (Camera){0};
		}
		return ret;
	}
	
	static int * js_getint_arr(JSContext * ctx,JSValue src,bool * error){
		int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(int  *)js_malloc(ctx,size_ret*sizeof(int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					int32_t long_reti;
					JS_ToInt32(ctx,&long_reti,src0);
					ret[i] =((int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_INT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(int  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static AutomationEventList * js_getAutomationEventList_arr(JSContext * ctx,JSValue src,bool * error){
		AutomationEventList * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(AutomationEventList  *)js_malloc(ctx,size_ret*sizeof(AutomationEventList));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_AutomationEventList_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_AutomationEventList_class_id);
					ret[i] =*(AutomationEventList *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type AutomationEventList *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_AutomationEventList_class_id){
			if(JS_GetClassID(src)==js_AutomationEventList_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_AutomationEventList_class_id);
				ret =(AutomationEventList  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type AutomationEventList *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type AutomationEventList *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Camera * js_getCamera_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		Camera * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Camera3D_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Camera3D_class_id);
				ret =(Camera  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Camera *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_Camera3D_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_Camera3D_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Camera3D_class_id);
				ret =(Camera  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Camera *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Camera *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static Vector2 * js_getVector2_arr(JSContext * ctx,JSValue src,bool * error){
		Vector2 * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Vector2_class_id){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Vector2  *)js_malloc(ctx,size_ret*sizeof(Vector2));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==js_Vector2_class_id){
						opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Vector2_class_id);
						ret[i] =*(Vector2 *)tmpshadow[0].ptr;
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector2 *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(js_free,(void  *)ret);
			}else if(JS_IsNumber(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				size_ret -=size_ret%2;
				ret =(Vector2  *)js_malloc(ctx,size_ret*sizeof(float));
				for(int i=0;i<size_ret;i++){
					float * tmp_obj=(float  *)ret;
					for(int i0=0;i0<2;i0++){
						src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
						JS_FreeValue(ctx,src0);
						if(JS_IsNumber(src0)){
							double double_tmp_objii0;
							JS_ToFloat64(ctx,&double_tmp_objii0,src0);
							tmp_obj[i+i0] =((float)double_tmp_objii0);
						}else{
							JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector2 *");
							error[0]=(bool)1;
							return NULL;
						}
					}
					i +=1;
				}
				memoryStore(js_free,(void  *)ret);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector2 *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(Vector2  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(Vector2  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_GetClassID(src)==js_Vector2_class_id){
			if(JS_GetClassID(src)==js_Vector2_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Vector2_class_id);
				ret =(Vector2  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector2 *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector2 *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Image * js_getImage_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		Image * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Image_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Image_class_id);
				ret =(Image  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Image *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_Image_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_Image_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Image_class_id);
				ret =(Image  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Image *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Image *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static float * js_getfloat_arr(JSContext * ctx,JSValue src,bool * error){
		float * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(float  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(float  *)js_malloc(ctx,size_ret*sizeof(float));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					double double_reti;
					JS_ToFloat64(ctx,&double_reti,src0);
					ret[i] =((float)double_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type float *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(float  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type float *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Color * js_getColor_arr(JSContext * ctx,JSValue src,bool * error){
		Color * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Color_class_id){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Color  *)js_malloc(ctx,size_ret*sizeof(Color));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==js_Color_class_id){
						opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Color_class_id);
						ret[i] =*(Color *)tmpshadow[0].ptr;
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Color *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(js_free,(void  *)ret);
			}else if(JS_IsNumber(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				size_ret -=size_ret%4;
				ret =(Color  *)js_malloc(ctx,size_ret*sizeof(unsigned char));
				for(int i=0;i<size_ret;i++){
					unsigned char * tmp_obj=(unsigned char  *)ret;
					for(int i0=0;i0<4;i0++){
						src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
						JS_FreeValue(ctx,src0);
						if(JS_IsNumber(src0)){
							uint32_t long_tmp_objii0;
							JS_ToUint32(ctx,&long_tmp_objii0,src0);
							tmp_obj[i+i0] =((unsigned char)long_tmp_objii0);
						}else{
							JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Color *");
							error[0]=(bool)1;
							return NULL;
						}
					}
					i +=3;
				}
				memoryStore(js_free,(void  *)ret);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Color *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==JS_CLASS_UINT8_ARRAY||JS_GetClassID(src)==JS_CLASS_UINT8C_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(Color  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(Color  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_GetClassID(src)==js_Color_class_id){
			if(JS_GetClassID(src)==js_Color_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Color_class_id);
				ret =(Color  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Color *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Color *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Texture2D * js_getTexture2D_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		Texture2D * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Texture_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Texture_class_id);
				ret =(Texture2D  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Texture2D *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_Texture_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_Texture_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Texture_class_id);
				ret =(Texture2D  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Texture2D *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Texture2D *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static int * js_getint_arrnull(JSContext * ctx,JSValue src,bool * error){
		int * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(int  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0)return NULL;
			ret =(int  *)js_malloc(ctx,size_ret*sizeof(int));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					int32_t long_reti;
					JS_ToInt32(ctx,&long_reti,src0);
					ret[i] =((int)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type int *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_INT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(int  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsNull(src)||JS_IsUndefined(src)){
			ret =NULL;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type int *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static GlyphInfo * js_getGlyphInfo_arr(JSContext * ctx,JSValue src,bool * error){
		GlyphInfo * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(GlyphInfo  *)js_malloc(ctx,size_ret*sizeof(GlyphInfo));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_GlyphInfo_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_GlyphInfo_class_id);
					ret[i] =*(GlyphInfo *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type GlyphInfo *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_GlyphInfo_class_id){
			if(JS_GetClassID(src)==js_GlyphInfo_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_GlyphInfo_class_id);
				ret =(GlyphInfo  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type GlyphInfo *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type GlyphInfo *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static char * * js_getchar_arr_arr(JSContext * ctx,JSValue src,bool * error){
		char * * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_IsArrayBuffer(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char  * *)js_malloc(ctx,size_ret*sizeof(char *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_IsArrayBuffer(src0)){
						int64_t size_reti;
						ret[i] =(char  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_reti,src0);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char * *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(js_free,(void  *)*ret);
			}else if(JS_GetClassID(src0)==js_ArrayProxy_class_id){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char  * *)js_malloc(ctx,size_ret*sizeof(char *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					bool is_arrayProxy0=(bool)0;
					if(JS_GetClassID(src0)==js_ArrayProxy_class_id){
						is_arrayProxy0 =(bool)1;
						void * AP_opaque=JS_GetOpaque(src0,js_ArrayProxy_class_id);
						ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
						src0 =AP_fn.values(ctx,src0,AP_fn.opaque,(int)0,(bool)false);
					}
					if(JS_IsArray(src0)){
						int64_t size_reti;
						if(JS_GetLength(ctx,src0,&size_reti)==-1){
							error[0]=(bool)1;
							return NULL;
						}
						if(size_reti==0){
							JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
							error[0]=(bool)1;
							return NULL;
						}
						ret[i] =(char  *)js_malloc(ctx,size_reti*sizeof(char));
						for(int i0=0;i0<size_reti;i0++){
							JSValue src00=JS_GetPropertyUint32(ctx,src0,(uint32_t)i0);
							JS_FreeValue(ctx,src00);
							if(JS_IsString(src00)){
								char * js_retii0=(char  *)JS_ToCString(ctx,src00);
								ret[i][i0] =((char)js_retii0[0]);
								JS_FreeCString(ctx,(const char  *)js_retii0);
							}else{
								JS_ThrowTypeError(ctx,(const char  *)"src00 does not match type char * *");
								error[0]=(bool)1;
								return NULL;
							}
						}
						memoryStore(js_free,(void  *)ret[i]);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char * *");
						error[0]=(bool)1;
						return NULL;
					}
					if(is_arrayProxy0)JS_FreeValue(ctx,src0);
				}
				memoryStore(js_free,(void  *)*ret);
			}else if(JS_IsArray(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char  * *)js_malloc(ctx,size_ret*sizeof(char *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_IsArray(src0)){
						int64_t size_reti;
						if(JS_GetLength(ctx,src0,&size_reti)==-1){
							error[0]=(bool)1;
							return NULL;
						}
						if(size_reti==0){
							JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
							error[0]=(bool)1;
							return NULL;
						}
						ret[i] =(char  *)js_malloc(ctx,size_reti*sizeof(char));
						for(int i0=0;i0<size_reti;i0++){
							JSValue src00=JS_GetPropertyUint32(ctx,src0,(uint32_t)i0);
							JS_FreeValue(ctx,src00);
							if(JS_IsString(src00)){
								char * js_retii0=(char  *)JS_ToCString(ctx,src00);
								ret[i][i0] =((char)js_retii0[0]);
								JS_FreeCString(ctx,(const char  *)js_retii0);
							}else{
								JS_ThrowTypeError(ctx,(const char  *)"src00 does not match type char * *");
								error[0]=(bool)1;
								return NULL;
							}
						}
						memoryStore(js_free,(void  *)ret[i]);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char * *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(js_free,(void  *)*ret);
			}else if(JS_GetClassID(src0)==JS_CLASS_INT8_ARRAY){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char  * *)js_malloc(ctx,size_ret*sizeof(char *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==JS_CLASS_INT8_ARRAY){
						size_t offset_reti;
						size_t size_reti;
						JSValue da_reti=JS_GetTypedArrayBuffer(ctx,src0,&offset_reti,&size_reti,NULL);
						ret[i] =(char  *)JS_GetArrayBuffer(ctx,&size_reti,src0);
						ret[i] +=offset_reti;
						size_reti -=offset_reti;
						JS_FreeValuePtr(ctx,&da_reti);
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char * *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(js_free,(void  *)*ret);
			}else if(JS_IsString(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char  * *)js_malloc(ctx,size_ret*sizeof(char *));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_IsString(src0)){
						char * js_reti=(char  *)JS_ToCStringLen(ctx,NULL,src0);
						memoryStore(JS_FreeCString,(void  *)js_reti);
						ret[i]=js_reti;
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type char * *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(js_free,(void  *)*ret);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type char * *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type char * *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static int64_t js_getint64_t(JSContext * ctx,JSValue src,bool * error){
		int64_t ret;
		if(JS_IsNumber(src)){
			JS_ToInt64(ctx,&ret,src);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type int64_t");
			error[0]=(bool)1;
			return (int64_t){0};
		}
		return ret;
	}
	
	static uint32_t js_getuint32_t(JSContext * ctx,JSValue src,bool * error){
		uint32_t ret;
		if(JS_IsNumber(src)){
			JS_ToUint32(ctx,&ret,src);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type uint32_t");
			error[0]=(bool)1;
			return (uint32_t){0};
		}
		return ret;
	}
	
	static double js_getdouble(JSContext * ctx,JSValue src,bool * error){
		double ret;
		if(JS_IsNumber(src)){
			int err_ret=JS_ToFloat64(ctx,&ret,src);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type double");
			error[0]=(bool)1;
			return 0.0d;
		}
		return ret;
	}
	
	static wchar_t * js_getwchar_t_arr(JSContext * ctx,JSValue src,bool * error){
		wchar_t * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(wchar_t  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(wchar_t  *)js_malloc(ctx,size_ret*sizeof(wchar_t));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					uint32_t long_reti;
					JS_ToUint32(ctx,&long_reti,src0);
					ret[i] =((wchar_t)long_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type wchar_t *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==JS_CLASS_UINT16_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(wchar_t  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type wchar_t *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Vector3 * js_getVector3_arr(JSContext * ctx,JSValue src,bool * error){
		Vector3 * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Vector3_class_id){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Vector3  *)js_malloc(ctx,size_ret*sizeof(Vector3));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==js_Vector3_class_id){
						opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Vector3_class_id);
						ret[i] =*(Vector3 *)tmpshadow[0].ptr;
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector3 *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(js_free,(void  *)ret);
			}else if(JS_IsNumber(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				size_ret -=size_ret%3;
				ret =(Vector3  *)js_malloc(ctx,size_ret*sizeof(float));
				for(int i=0;i<size_ret;i++){
					float * tmp_obj=(float  *)ret;
					for(int i0=0;i0<3;i0++){
						src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
						JS_FreeValue(ctx,src0);
						if(JS_IsNumber(src0)){
							double double_tmp_objii0;
							JS_ToFloat64(ctx,&double_tmp_objii0,src0);
							tmp_obj[i+i0] =((float)double_tmp_objii0);
						}else{
							JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Vector3 *");
							error[0]=(bool)1;
							return NULL;
						}
					}
					i +=2;
				}
				memoryStore(js_free,(void  *)ret);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector3 *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(Vector3  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(Vector3  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_GetClassID(src)==js_Vector3_class_id){
			if(JS_GetClassID(src)==js_Vector3_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Vector3_class_id);
				ret =(Vector3  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector3 *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Vector3 *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Mesh * js_getMesh_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		Mesh * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Mesh_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Mesh_class_id);
				ret =(Mesh  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Mesh *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_Mesh_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_Mesh_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Mesh_class_id);
				ret =(Mesh  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Mesh *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Mesh *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static Matrix * js_getMatrix_arr(JSContext * ctx,JSValue src,bool * error){
		Matrix * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Matrix_class_id){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Matrix  *)js_malloc(ctx,size_ret*sizeof(Matrix));
				for(int i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==js_Matrix_class_id){
						opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Matrix_class_id);
						ret[i] =*(Matrix *)tmpshadow[0].ptr;
					}else{
						JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Matrix *");
						error[0]=(bool)1;
						return NULL;
					}
				}
				memoryStore(js_free,(void  *)ret);
			}else if(JS_IsNumber(src0)){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				size_ret -=size_ret%16;
				ret =(Matrix  *)js_malloc(ctx,size_ret*sizeof(float));
				for(int i=0;i<size_ret;i++){
					float * tmp_obj=(float  *)ret;
					for(int i0=0;i0<16;i0++){
						src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
						JS_FreeValue(ctx,src0);
						if(JS_IsNumber(src0)){
							double double_tmp_objii0;
							JS_ToFloat64(ctx,&double_tmp_objii0,src0);
							tmp_obj[i+i0] =((float)double_tmp_objii0);
						}else{
							JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Matrix *");
							error[0]=(bool)1;
							return NULL;
						}
					}
					i +=15;
				}
				memoryStore(js_free,(void  *)ret);
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Matrix *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(Matrix  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(Matrix  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_GetClassID(src)==js_Matrix_class_id){
			if(JS_GetClassID(src)==js_Matrix_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Matrix_class_id);
				ret =(Matrix  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Matrix *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Matrix *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Material * js_getMaterial_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		Material * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Material_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Material_class_id);
				ret =(Material  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Material *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_Material_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_Material_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Material_class_id);
				ret =(Material  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Material *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Material *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static Model * js_getModel_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		Model * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Model_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Model_class_id);
				ret =(Model  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Model *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_Model_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_Model_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Model_class_id);
				ret =(Model  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Model *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Model *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static ModelAnimation * js_getModelAnimation_arr(JSContext * ctx,JSValue src,bool * error){
		ModelAnimation * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,src,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char  *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(ModelAnimation  *)js_malloc(ctx,size_ret*sizeof(ModelAnimation));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_ModelAnimation_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_ModelAnimation_class_id);
					ret[i] =*(ModelAnimation *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type ModelAnimation *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_ModelAnimation_class_id){
			if(JS_GetClassID(src)==js_ModelAnimation_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_ModelAnimation_class_id);
				ret =(ModelAnimation  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type ModelAnimation *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type ModelAnimation *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Wave * js_getWave_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		Wave * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Wave_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Wave_class_id);
				ret =(Wave  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Wave *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_Wave_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_Wave_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Wave_class_id);
				ret =(Wave  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Wave *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Wave *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static void js_Vector2_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Vector2_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Vector2_get_x(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector2_class_id);
		Vector2 * ptr=(Vector2  *)shadow[0].ptr;
		float x=ptr[0].x;
		JSValue ret=JS_NewFloat64(ctx,((double)x));
		return ret;
	}
	
	static JSValue js_Vector2_set_x(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector2_class_id);
		Vector2 * ptr=(Vector2  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].x=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Vector2_get_y(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector2_class_id);
		Vector2 * ptr=(Vector2  *)shadow[0].ptr;
		float y=ptr[0].y;
		JSValue ret=JS_NewFloat64(ctx,((double)y));
		return ret;
	}
	
	static JSValue js_Vector2_set_y(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector2_class_id);
		Vector2 * ptr=(Vector2  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].y=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Vector2_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Vector2", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("x",js_Vector2_get_x,js_Vector2_set_x),
		JS_CGETSET_DEF("y",js_Vector2_get_y,js_Vector2_set_y)
	};
	
	static int js_declare_Vector2(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Vector2_class_id);
		JSClassDef js_Vector2_def={ .class_name = "Vector2", .finalizer = js_Vector2_finalizer };
		JS_NewClass(rt,js_Vector2_class_id,(const JSClassDef  *)&js_Vector2_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Vector2_proto_funcs,(int)countof(js_Vector2_proto_funcs));
		JS_SetClassProto(ctx,js_Vector2_class_id,proto);
		return 0;
	}
	
	static void js_Vector3_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Vector3_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Vector3_get_x(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector3_class_id);
		Vector3 * ptr=(Vector3  *)shadow[0].ptr;
		float x=ptr[0].x;
		JSValue ret=JS_NewFloat64(ctx,((double)x));
		return ret;
	}
	
	static JSValue js_Vector3_set_x(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector3_class_id);
		Vector3 * ptr=(Vector3  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].x=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Vector3_get_y(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector3_class_id);
		Vector3 * ptr=(Vector3  *)shadow[0].ptr;
		float y=ptr[0].y;
		JSValue ret=JS_NewFloat64(ctx,((double)y));
		return ret;
	}
	
	static JSValue js_Vector3_set_y(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector3_class_id);
		Vector3 * ptr=(Vector3  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].y=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Vector3_get_z(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector3_class_id);
		Vector3 * ptr=(Vector3  *)shadow[0].ptr;
		float z=ptr[0].z;
		JSValue ret=JS_NewFloat64(ctx,((double)z));
		return ret;
	}
	
	static JSValue js_Vector3_set_z(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector3_class_id);
		Vector3 * ptr=(Vector3  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].z=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Vector3_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Vector3", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("x",js_Vector3_get_x,js_Vector3_set_x),
		JS_CGETSET_DEF("y",js_Vector3_get_y,js_Vector3_set_y),
		JS_CGETSET_DEF("z",js_Vector3_get_z,js_Vector3_set_z)
	};
	
	static int js_declare_Vector3(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Vector3_class_id);
		JSClassDef js_Vector3_def={ .class_name = "Vector3", .finalizer = js_Vector3_finalizer };
		JS_NewClass(rt,js_Vector3_class_id,(const JSClassDef  *)&js_Vector3_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Vector3_proto_funcs,(int)countof(js_Vector3_proto_funcs));
		JS_SetClassProto(ctx,js_Vector3_class_id,proto);
		return 0;
	}
	
	static void js_Vector4_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Vector4_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Vector4_get_x(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector4_class_id);
		Vector4 * ptr=(Vector4  *)shadow[0].ptr;
		float x=ptr[0].x;
		JSValue ret=JS_NewFloat64(ctx,((double)x));
		return ret;
	}
	
	static JSValue js_Vector4_set_x(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector4_class_id);
		Vector4 * ptr=(Vector4  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].x=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Vector4_get_y(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector4_class_id);
		Vector4 * ptr=(Vector4  *)shadow[0].ptr;
		float y=ptr[0].y;
		JSValue ret=JS_NewFloat64(ctx,((double)y));
		return ret;
	}
	
	static JSValue js_Vector4_set_y(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector4_class_id);
		Vector4 * ptr=(Vector4  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].y=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Vector4_get_z(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector4_class_id);
		Vector4 * ptr=(Vector4  *)shadow[0].ptr;
		float z=ptr[0].z;
		JSValue ret=JS_NewFloat64(ctx,((double)z));
		return ret;
	}
	
	static JSValue js_Vector4_set_z(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector4_class_id);
		Vector4 * ptr=(Vector4  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].z=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Vector4_get_w(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector4_class_id);
		Vector4 * ptr=(Vector4  *)shadow[0].ptr;
		float w=ptr[0].w;
		JSValue ret=JS_NewFloat64(ctx,((double)w));
		return ret;
	}
	
	static JSValue js_Vector4_set_w(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Vector4_class_id);
		Vector4 * ptr=(Vector4  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].w=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Vector4_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Vector4", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("x",js_Vector4_get_x,js_Vector4_set_x),
		JS_CGETSET_DEF("y",js_Vector4_get_y,js_Vector4_set_y),
		JS_CGETSET_DEF("z",js_Vector4_get_z,js_Vector4_set_z),
		JS_CGETSET_DEF("w",js_Vector4_get_w,js_Vector4_set_w)
	};
	
	static int js_declare_Vector4(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Vector4_class_id);
		JSClassDef js_Vector4_def={ .class_name = "Vector4", .finalizer = js_Vector4_finalizer };
		JS_NewClass(rt,js_Vector4_class_id,(const JSClassDef  *)&js_Vector4_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Vector4_proto_funcs,(int)countof(js_Vector4_proto_funcs));
		JS_SetClassProto(ctx,js_Vector4_class_id,proto);
		return 0;
	}
	
	static void js_Matrix_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Matrix_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Matrix_get_m0(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m0=ptr[0].m0;
		JSValue ret=JS_NewFloat64(ctx,((double)m0));
		return ret;
	}
	
	static JSValue js_Matrix_set_m0(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m0=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m4(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m4=ptr[0].m4;
		JSValue ret=JS_NewFloat64(ctx,((double)m4));
		return ret;
	}
	
	static JSValue js_Matrix_set_m4(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m4=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m8(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m8=ptr[0].m8;
		JSValue ret=JS_NewFloat64(ctx,((double)m8));
		return ret;
	}
	
	static JSValue js_Matrix_set_m8(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m8=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m12(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m12=ptr[0].m12;
		JSValue ret=JS_NewFloat64(ctx,((double)m12));
		return ret;
	}
	
	static JSValue js_Matrix_set_m12(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m12=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m1(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m1=ptr[0].m1;
		JSValue ret=JS_NewFloat64(ctx,((double)m1));
		return ret;
	}
	
	static JSValue js_Matrix_set_m1(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m1=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m5(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m5=ptr[0].m5;
		JSValue ret=JS_NewFloat64(ctx,((double)m5));
		return ret;
	}
	
	static JSValue js_Matrix_set_m5(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m5=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m9(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m9=ptr[0].m9;
		JSValue ret=JS_NewFloat64(ctx,((double)m9));
		return ret;
	}
	
	static JSValue js_Matrix_set_m9(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m9=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m13(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m13=ptr[0].m13;
		JSValue ret=JS_NewFloat64(ctx,((double)m13));
		return ret;
	}
	
	static JSValue js_Matrix_set_m13(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m13=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m2(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m2=ptr[0].m2;
		JSValue ret=JS_NewFloat64(ctx,((double)m2));
		return ret;
	}
	
	static JSValue js_Matrix_set_m2(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m2=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m6(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m6=ptr[0].m6;
		JSValue ret=JS_NewFloat64(ctx,((double)m6));
		return ret;
	}
	
	static JSValue js_Matrix_set_m6(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m6=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m10(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m10=ptr[0].m10;
		JSValue ret=JS_NewFloat64(ctx,((double)m10));
		return ret;
	}
	
	static JSValue js_Matrix_set_m10(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m10=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m14(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m14=ptr[0].m14;
		JSValue ret=JS_NewFloat64(ctx,((double)m14));
		return ret;
	}
	
	static JSValue js_Matrix_set_m14(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m14=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m3(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m3=ptr[0].m3;
		JSValue ret=JS_NewFloat64(ctx,((double)m3));
		return ret;
	}
	
	static JSValue js_Matrix_set_m3(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m3=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m7(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m7=ptr[0].m7;
		JSValue ret=JS_NewFloat64(ctx,((double)m7));
		return ret;
	}
	
	static JSValue js_Matrix_set_m7(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m7=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m11(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m11=ptr[0].m11;
		JSValue ret=JS_NewFloat64(ctx,((double)m11));
		return ret;
	}
	
	static JSValue js_Matrix_set_m11(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m11=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Matrix_get_m15(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		float m15=ptr[0].m15;
		JSValue ret=JS_NewFloat64(ctx,((double)m15));
		return ret;
	}
	
	static JSValue js_Matrix_set_m15(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Matrix_class_id);
		Matrix * ptr=(Matrix  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].m15=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Matrix_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Matrix", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("m0",js_Matrix_get_m0,js_Matrix_set_m0),
		JS_CGETSET_DEF("m4",js_Matrix_get_m4,js_Matrix_set_m4),
		JS_CGETSET_DEF("m8",js_Matrix_get_m8,js_Matrix_set_m8),
		JS_CGETSET_DEF("m12",js_Matrix_get_m12,js_Matrix_set_m12),
		JS_CGETSET_DEF("m1",js_Matrix_get_m1,js_Matrix_set_m1),
		JS_CGETSET_DEF("m5",js_Matrix_get_m5,js_Matrix_set_m5),
		JS_CGETSET_DEF("m9",js_Matrix_get_m9,js_Matrix_set_m9),
		JS_CGETSET_DEF("m13",js_Matrix_get_m13,js_Matrix_set_m13),
		JS_CGETSET_DEF("m2",js_Matrix_get_m2,js_Matrix_set_m2),
		JS_CGETSET_DEF("m6",js_Matrix_get_m6,js_Matrix_set_m6),
		JS_CGETSET_DEF("m10",js_Matrix_get_m10,js_Matrix_set_m10),
		JS_CGETSET_DEF("m14",js_Matrix_get_m14,js_Matrix_set_m14),
		JS_CGETSET_DEF("m3",js_Matrix_get_m3,js_Matrix_set_m3),
		JS_CGETSET_DEF("m7",js_Matrix_get_m7,js_Matrix_set_m7),
		JS_CGETSET_DEF("m11",js_Matrix_get_m11,js_Matrix_set_m11),
		JS_CGETSET_DEF("m15",js_Matrix_get_m15,js_Matrix_set_m15)
	};
	
	static int js_declare_Matrix(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Matrix_class_id);
		JSClassDef js_Matrix_def={ .class_name = "Matrix", .finalizer = js_Matrix_finalizer };
		JS_NewClass(rt,js_Matrix_class_id,(const JSClassDef  *)&js_Matrix_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Matrix_proto_funcs,(int)countof(js_Matrix_proto_funcs));
		JS_SetClassProto(ctx,js_Matrix_class_id,proto);
		return 0;
	}
	
	static void js_Color_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Color_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Color_get_r(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Color_class_id);
		Color * ptr=(Color  *)shadow[0].ptr;
		unsigned char r=ptr[0].r;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)r));
		return ret;
	}
	
	static JSValue js_Color_set_r(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Color_class_id);
		Color * ptr=(Color  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned char value=js_getunsignedchar(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].r=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Color_get_g(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Color_class_id);
		Color * ptr=(Color  *)shadow[0].ptr;
		unsigned char g=ptr[0].g;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)g));
		return ret;
	}
	
	static JSValue js_Color_set_g(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Color_class_id);
		Color * ptr=(Color  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned char value=js_getunsignedchar(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].g=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Color_get_b(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Color_class_id);
		Color * ptr=(Color  *)shadow[0].ptr;
		unsigned char b=ptr[0].b;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)b));
		return ret;
	}
	
	static JSValue js_Color_set_b(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Color_class_id);
		Color * ptr=(Color  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned char value=js_getunsignedchar(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].b=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Color_get_a(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Color_class_id);
		Color * ptr=(Color  *)shadow[0].ptr;
		unsigned char a=ptr[0].a;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)a));
		return ret;
	}
	
	static JSValue js_Color_set_a(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Color_class_id);
		Color * ptr=(Color  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned char value=js_getunsignedchar(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].a=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Color_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Color", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("r",js_Color_get_r,js_Color_set_r),
		JS_CGETSET_DEF("g",js_Color_get_g,js_Color_set_g),
		JS_CGETSET_DEF("b",js_Color_get_b,js_Color_set_b),
		JS_CGETSET_DEF("a",js_Color_get_a,js_Color_set_a)
	};
	
	static int js_declare_Color(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Color_class_id);
		JSClassDef js_Color_def={ .class_name = "Color", .finalizer = js_Color_finalizer };
		JS_NewClass(rt,js_Color_class_id,(const JSClassDef  *)&js_Color_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Color_proto_funcs,(int)countof(js_Color_proto_funcs));
		JS_SetClassProto(ctx,js_Color_class_id,proto);
		return 0;
	}
	
	static void js_Rectangle_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Rectangle_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Rectangle_get_x(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Rectangle_class_id);
		Rectangle * ptr=(Rectangle  *)shadow[0].ptr;
		float x=ptr[0].x;
		JSValue ret=JS_NewFloat64(ctx,((double)x));
		return ret;
	}
	
	static JSValue js_Rectangle_set_x(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Rectangle_class_id);
		Rectangle * ptr=(Rectangle  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].x=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Rectangle_get_y(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Rectangle_class_id);
		Rectangle * ptr=(Rectangle  *)shadow[0].ptr;
		float y=ptr[0].y;
		JSValue ret=JS_NewFloat64(ctx,((double)y));
		return ret;
	}
	
	static JSValue js_Rectangle_set_y(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Rectangle_class_id);
		Rectangle * ptr=(Rectangle  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].y=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Rectangle_get_width(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Rectangle_class_id);
		Rectangle * ptr=(Rectangle  *)shadow[0].ptr;
		float width=ptr[0].width;
		JSValue ret=JS_NewFloat64(ctx,((double)width));
		return ret;
	}
	
	static JSValue js_Rectangle_set_width(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Rectangle_class_id);
		Rectangle * ptr=(Rectangle  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].width=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Rectangle_get_height(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Rectangle_class_id);
		Rectangle * ptr=(Rectangle  *)shadow[0].ptr;
		float height=ptr[0].height;
		JSValue ret=JS_NewFloat64(ctx,((double)height));
		return ret;
	}
	
	static JSValue js_Rectangle_set_height(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Rectangle_class_id);
		Rectangle * ptr=(Rectangle  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].height=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Rectangle_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Rectangle", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("x",js_Rectangle_get_x,js_Rectangle_set_x),
		JS_CGETSET_DEF("y",js_Rectangle_get_y,js_Rectangle_set_y),
		JS_CGETSET_DEF("width",js_Rectangle_get_width,js_Rectangle_set_width),
		JS_CGETSET_DEF("height",js_Rectangle_get_height,js_Rectangle_set_height)
	};
	
	static int js_declare_Rectangle(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Rectangle_class_id);
		JSClassDef js_Rectangle_def={ .class_name = "Rectangle", .finalizer = js_Rectangle_finalizer };
		JS_NewClass(rt,js_Rectangle_class_id,(const JSClassDef  *)&js_Rectangle_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Rectangle_proto_funcs,(int)countof(js_Rectangle_proto_funcs));
		JS_SetClassProto(ctx,js_Rectangle_class_id,proto);
		return 0;
	}
	
	static void js_Image_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Image_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Image_data_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Image * ptr=(Image  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<GetPixelDataSize(ptr[0].width,ptr[0].height,ptr[0].format);i++){
			unsigned char src0=((unsigned char *)ptr[0].data)[i];
			JSValue ret1=JS_NewUint32(ctx,(uint32_t)((unsigned long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Image_data_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Image * ptr=(Image  *)ptr_u;
		int length=GetPixelDataSize(ptr[0].width,ptr[0].height,ptr[0].format);
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Image_data_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Image * ptr=(Image  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)GetPixelDataSize(ptr[0].width,ptr[0].height,ptr[0].format)));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<GetPixelDataSize(ptr[0].width,ptr[0].height,ptr[0].format)){
				unsigned char * ptrcast=(unsigned char  *)ptr[0].data;
				unsigned char src=ptrcast[property];
				JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Image_data_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Image * ptr=(Image  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<GetPixelDataSize(ptr[0].width,ptr[0].height,ptr[0].format)){
				bool error=(bool)0;
				local_memlock=(bool)true;
				unsigned char ret=js_getunsignedchar(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				((unsigned char *)ptr[0].data)[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Image_data_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Image * ptr=(Image  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<GetPixelDataSize(ptr[0].width,ptr[0].height,ptr[0].format)){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Image_get_data(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Image_class_id);
		Image * ptr=(Image  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Image_data_values,.keys = js_Image_data_keys,.get = js_Image_data_get,.set = js_Image_data_set,.has = js_Image_data_has});
		return ret;
	}
	
	static JSValue js_Image_set_data(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Image_class_id);
		Image * ptr=(Image  *)shadow[0].ptr;
		local_memlock=(bool)true;
		void * value=js_getvoid_arr(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].data!=NULL)jsc_free(ctx,ptr[0].data);
		ptr[0].data =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Image_get_width(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Image_class_id);
		Image * ptr=(Image  *)shadow[0].ptr;
		int width=ptr[0].width;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)width));
		return ret;
	}
	
	static JSValue js_Image_set_width(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Image_class_id);
		Image * ptr=(Image  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].width=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Image_get_height(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Image_class_id);
		Image * ptr=(Image  *)shadow[0].ptr;
		int height=ptr[0].height;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)height));
		return ret;
	}
	
	static JSValue js_Image_set_height(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Image_class_id);
		Image * ptr=(Image  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].height=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Image_get_mipmaps(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Image_class_id);
		Image * ptr=(Image  *)shadow[0].ptr;
		int mipmaps=ptr[0].mipmaps;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)mipmaps));
		return ret;
	}
	
	static JSValue js_Image_set_mipmaps(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Image_class_id);
		Image * ptr=(Image  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].mipmaps=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Image_get_format(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Image_class_id);
		Image * ptr=(Image  *)shadow[0].ptr;
		int format=ptr[0].format;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)format));
		return ret;
	}
	
	static JSValue js_Image_set_format(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Image_class_id);
		Image * ptr=(Image  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].format=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Image_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Image", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("data",js_Image_get_data,js_Image_set_data),
		JS_CGETSET_DEF("width",js_Image_get_width,js_Image_set_width),
		JS_CGETSET_DEF("height",js_Image_get_height,js_Image_set_height),
		JS_CGETSET_DEF("mipmaps",js_Image_get_mipmaps,js_Image_set_mipmaps),
		JS_CGETSET_DEF("format",js_Image_get_format,js_Image_set_format)
	};
	
	static int js_declare_Image(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Image_class_id);
		JSClassDef js_Image_def={ .class_name = "Image", .finalizer = js_Image_finalizer };
		JS_NewClass(rt,js_Image_class_id,(const JSClassDef  *)&js_Image_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Image_proto_funcs,(int)countof(js_Image_proto_funcs));
		JS_SetClassProto(ctx,js_Image_class_id,proto);
		return 0;
	}
	
	static void js_Texture_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Texture_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Texture_get_id(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Texture_class_id);
		Texture * ptr=(Texture  *)shadow[0].ptr;
		unsigned int id=ptr[0].id;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)id));
		return ret;
	}
	
	static JSValue js_Texture_set_id(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Texture_class_id);
		Texture * ptr=(Texture  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].id=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Texture_get_width(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Texture_class_id);
		Texture * ptr=(Texture  *)shadow[0].ptr;
		int width=ptr[0].width;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)width));
		return ret;
	}
	
	static JSValue js_Texture_set_width(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Texture_class_id);
		Texture * ptr=(Texture  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].width=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Texture_get_height(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Texture_class_id);
		Texture * ptr=(Texture  *)shadow[0].ptr;
		int height=ptr[0].height;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)height));
		return ret;
	}
	
	static JSValue js_Texture_set_height(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Texture_class_id);
		Texture * ptr=(Texture  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].height=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Texture_get_mipmaps(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Texture_class_id);
		Texture * ptr=(Texture  *)shadow[0].ptr;
		int mipmaps=ptr[0].mipmaps;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)mipmaps));
		return ret;
	}
	
	static JSValue js_Texture_set_mipmaps(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Texture_class_id);
		Texture * ptr=(Texture  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].mipmaps=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Texture_get_format(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Texture_class_id);
		Texture * ptr=(Texture  *)shadow[0].ptr;
		int format=ptr[0].format;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)format));
		return ret;
	}
	
	static JSValue js_Texture_set_format(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Texture_class_id);
		Texture * ptr=(Texture  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].format=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Texture_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Texture", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("id",js_Texture_get_id,js_Texture_set_id),
		JS_CGETSET_DEF("width",js_Texture_get_width,js_Texture_set_width),
		JS_CGETSET_DEF("height",js_Texture_get_height,js_Texture_set_height),
		JS_CGETSET_DEF("mipmaps",js_Texture_get_mipmaps,js_Texture_set_mipmaps),
		JS_CGETSET_DEF("format",js_Texture_get_format,js_Texture_set_format)
	};
	
	static int js_declare_Texture(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Texture_class_id);
		JSClassDef js_Texture_def={ .class_name = "Texture", .finalizer = js_Texture_finalizer };
		JS_NewClass(rt,js_Texture_class_id,(const JSClassDef  *)&js_Texture_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Texture_proto_funcs,(int)countof(js_Texture_proto_funcs));
		JS_SetClassProto(ctx,js_Texture_class_id,proto);
		return 0;
	}
	
	static void js_RenderTexture_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_RenderTexture_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_RenderTexture_get_id(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RenderTexture_class_id);
		RenderTexture * ptr=(RenderTexture  *)shadow[0].ptr;
		unsigned int id=ptr[0].id;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)id));
		return ret;
	}
	
	static JSValue js_RenderTexture_set_id(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RenderTexture_class_id);
		RenderTexture * ptr=(RenderTexture  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].id=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_RenderTexture_get_texture(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RenderTexture_class_id);
		RenderTexture * ptr=(RenderTexture  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Texture * texture=&ptr[0].texture;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)texture,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Texture_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_RenderTexture_set_texture(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RenderTexture_class_id);
		RenderTexture * ptr=(RenderTexture  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Texture value=js_getTexture(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].texture=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_RenderTexture_get_depth(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RenderTexture_class_id);
		RenderTexture * ptr=(RenderTexture  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Texture * depth=&ptr[0].depth;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)depth,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Texture_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_RenderTexture_set_depth(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RenderTexture_class_id);
		RenderTexture * ptr=(RenderTexture  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Texture value=js_getTexture(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].depth=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_RenderTexture_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","RenderTexture", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("id",js_RenderTexture_get_id,js_RenderTexture_set_id),
		JS_CGETSET_DEF("texture",js_RenderTexture_get_texture,js_RenderTexture_set_texture),
		JS_CGETSET_DEF("depth",js_RenderTexture_get_depth,js_RenderTexture_set_depth)
	};
	
	static int js_declare_RenderTexture(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_RenderTexture_class_id);
		JSClassDef js_RenderTexture_def={ .class_name = "RenderTexture", .finalizer = js_RenderTexture_finalizer };
		JS_NewClass(rt,js_RenderTexture_class_id,(const JSClassDef  *)&js_RenderTexture_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_RenderTexture_proto_funcs,(int)countof(js_RenderTexture_proto_funcs));
		JS_SetClassProto(ctx,js_RenderTexture_class_id,proto);
		return 0;
	}
	
	static void js_NPatchInfo_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_NPatchInfo_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_NPatchInfo_get_source(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Rectangle * source=&ptr[0].source;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)source,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Rectangle_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_NPatchInfo_set_source(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Rectangle value=js_getRectangle(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].source=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_NPatchInfo_get_left(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		int left=ptr[0].left;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)left));
		return ret;
	}
	
	static JSValue js_NPatchInfo_set_left(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].left=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_NPatchInfo_get_top(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		int top=ptr[0].top;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)top));
		return ret;
	}
	
	static JSValue js_NPatchInfo_set_top(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].top=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_NPatchInfo_get_right(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		int right=ptr[0].right;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)right));
		return ret;
	}
	
	static JSValue js_NPatchInfo_set_right(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].right=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_NPatchInfo_get_bottom(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		int bottom=ptr[0].bottom;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)bottom));
		return ret;
	}
	
	static JSValue js_NPatchInfo_set_bottom(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].bottom=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_NPatchInfo_get_layout(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		int layout=ptr[0].layout;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)layout));
		return ret;
	}
	
	static JSValue js_NPatchInfo_set_layout(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_NPatchInfo_class_id);
		NPatchInfo * ptr=(NPatchInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].layout=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_NPatchInfo_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","NPatchInfo", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("source",js_NPatchInfo_get_source,js_NPatchInfo_set_source),
		JS_CGETSET_DEF("left",js_NPatchInfo_get_left,js_NPatchInfo_set_left),
		JS_CGETSET_DEF("top",js_NPatchInfo_get_top,js_NPatchInfo_set_top),
		JS_CGETSET_DEF("right",js_NPatchInfo_get_right,js_NPatchInfo_set_right),
		JS_CGETSET_DEF("bottom",js_NPatchInfo_get_bottom,js_NPatchInfo_set_bottom),
		JS_CGETSET_DEF("layout",js_NPatchInfo_get_layout,js_NPatchInfo_set_layout)
	};
	
	static int js_declare_NPatchInfo(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_NPatchInfo_class_id);
		JSClassDef js_NPatchInfo_def={ .class_name = "NPatchInfo", .finalizer = js_NPatchInfo_finalizer };
		JS_NewClass(rt,js_NPatchInfo_class_id,(const JSClassDef  *)&js_NPatchInfo_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_NPatchInfo_proto_funcs,(int)countof(js_NPatchInfo_proto_funcs));
		JS_SetClassProto(ctx,js_NPatchInfo_class_id,proto);
		return 0;
	}
	
	static void js_GlyphInfo_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_GlyphInfo_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_GlyphInfo_get_value(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_GlyphInfo_class_id);
		GlyphInfo * ptr=(GlyphInfo  *)shadow[0].ptr;
		int value=ptr[0].value;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)value));
		return ret;
	}
	
	static JSValue js_GlyphInfo_set_value(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_GlyphInfo_class_id);
		GlyphInfo * ptr=(GlyphInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].value=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_GlyphInfo_get_offsetX(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_GlyphInfo_class_id);
		GlyphInfo * ptr=(GlyphInfo  *)shadow[0].ptr;
		int offsetX=ptr[0].offsetX;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)offsetX));
		return ret;
	}
	
	static JSValue js_GlyphInfo_set_offsetX(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_GlyphInfo_class_id);
		GlyphInfo * ptr=(GlyphInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].offsetX=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_GlyphInfo_get_offsetY(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_GlyphInfo_class_id);
		GlyphInfo * ptr=(GlyphInfo  *)shadow[0].ptr;
		int offsetY=ptr[0].offsetY;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)offsetY));
		return ret;
	}
	
	static JSValue js_GlyphInfo_set_offsetY(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_GlyphInfo_class_id);
		GlyphInfo * ptr=(GlyphInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].offsetY=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_GlyphInfo_get_advanceX(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_GlyphInfo_class_id);
		GlyphInfo * ptr=(GlyphInfo  *)shadow[0].ptr;
		int advanceX=ptr[0].advanceX;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)advanceX));
		return ret;
	}
	
	static JSValue js_GlyphInfo_set_advanceX(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_GlyphInfo_class_id);
		GlyphInfo * ptr=(GlyphInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].advanceX=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_GlyphInfo_get_image(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_GlyphInfo_class_id);
		GlyphInfo * ptr=(GlyphInfo  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Image * image=&ptr[0].image;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)image,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GlyphInfo_set_image(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_GlyphInfo_class_id);
		GlyphInfo * ptr=(GlyphInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Image value=js_getImage(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].image=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_GlyphInfo_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","GlyphInfo", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("value",js_GlyphInfo_get_value,js_GlyphInfo_set_value),
		JS_CGETSET_DEF("offsetX",js_GlyphInfo_get_offsetX,js_GlyphInfo_set_offsetX),
		JS_CGETSET_DEF("offsetY",js_GlyphInfo_get_offsetY,js_GlyphInfo_set_offsetY),
		JS_CGETSET_DEF("advanceX",js_GlyphInfo_get_advanceX,js_GlyphInfo_set_advanceX),
		JS_CGETSET_DEF("image",js_GlyphInfo_get_image,js_GlyphInfo_set_image)
	};
	
	static int js_declare_GlyphInfo(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_GlyphInfo_class_id);
		JSClassDef js_GlyphInfo_def={ .class_name = "GlyphInfo", .finalizer = js_GlyphInfo_finalizer };
		JS_NewClass(rt,js_GlyphInfo_class_id,(const JSClassDef  *)&js_GlyphInfo_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_GlyphInfo_proto_funcs,(int)countof(js_GlyphInfo_proto_funcs));
		JS_SetClassProto(ctx,js_GlyphInfo_class_id,proto);
		return 0;
	}
	
	static void js_Font_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Font_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Font_get_baseSize(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		int baseSize=ptr[0].baseSize;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)baseSize));
		return ret;
	}
	
	static JSValue js_Font_set_baseSize(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].baseSize=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Font_get_glyphCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		int glyphCount=ptr[0].glyphCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)glyphCount));
		return ret;
	}
	
	static JSValue js_Font_set_glyphCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].glyphCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Font_get_glyphPadding(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		int glyphPadding=ptr[0].glyphPadding;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)glyphPadding));
		return ret;
	}
	
	static JSValue js_Font_set_glyphPadding(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].glyphPadding=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Font_get_texture(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Texture2D * texture=&ptr[0].texture;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)texture,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Texture_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Font_set_texture(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Texture2D value=js_getTexture2D(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].texture=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Font_recs_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Font * ptr=(Font  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].glyphCount;i++){
			Rectangle * src0=(ptr[0].recs+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_Rectangle_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Font_recs_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Font * ptr=(Font  *)ptr_u;
		int length=ptr[0].glyphCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Font_recs_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Font * ptr=(Font  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].glyphCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].glyphCount){
				Rectangle * src=(ptr[0].recs+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_Rectangle_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Font_recs_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Font * ptr=(Font  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].glyphCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				Rectangle ret=js_getRectangle(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].recs[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Font_recs_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Font * ptr=(Font  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].glyphCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Font_get_recs(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Font_recs_values,.keys = js_Font_recs_keys,.get = js_Font_recs_get,.set = js_Font_recs_set,.has = js_Font_recs_has});
		return ret;
	}
	
	static JSValue js_Font_set_recs(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Rectangle * value=js_getRectangle_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].recs!=NULL)jsc_free(ctx,(void  *)ptr[0].recs);
		ptr[0].recs =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Font_glyphs_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Font * ptr=(Font  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].glyphCount;i++){
			GlyphInfo * src0=(ptr[0].glyphs+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_GlyphInfo_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Font_glyphs_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Font * ptr=(Font  *)ptr_u;
		int length=ptr[0].glyphCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Font_glyphs_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Font * ptr=(Font  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].glyphCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].glyphCount){
				GlyphInfo * src=(ptr[0].glyphs+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_GlyphInfo_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Font_glyphs_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Font * ptr=(Font  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].glyphCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				GlyphInfo ret=js_getGlyphInfo(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].glyphs[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Font_glyphs_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Font * ptr=(Font  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].glyphCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Font_get_glyphs(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Font_glyphs_values,.keys = js_Font_glyphs_keys,.get = js_Font_glyphs_get,.set = js_Font_glyphs_set,.has = js_Font_glyphs_has});
		return ret;
	}
	
	static JSValue js_Font_set_glyphs(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Font_class_id);
		Font * ptr=(Font  *)shadow[0].ptr;
		local_memlock=(bool)true;
		GlyphInfo * value=js_getGlyphInfo_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].glyphs!=NULL)jsc_free(ctx,(void  *)ptr[0].glyphs);
		ptr[0].glyphs =value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Font_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Font", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("baseSize",js_Font_get_baseSize,js_Font_set_baseSize),
		JS_CGETSET_DEF("glyphCount",js_Font_get_glyphCount,js_Font_set_glyphCount),
		JS_CGETSET_DEF("glyphPadding",js_Font_get_glyphPadding,js_Font_set_glyphPadding),
		JS_CGETSET_DEF("texture",js_Font_get_texture,js_Font_set_texture),
		JS_CGETSET_DEF("recs",js_Font_get_recs,js_Font_set_recs),
		JS_CGETSET_DEF("glyphs",js_Font_get_glyphs,js_Font_set_glyphs)
	};
	
	static int js_declare_Font(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Font_class_id);
		JSClassDef js_Font_def={ .class_name = "Font", .finalizer = js_Font_finalizer };
		JS_NewClass(rt,js_Font_class_id,(const JSClassDef  *)&js_Font_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Font_proto_funcs,(int)countof(js_Font_proto_funcs));
		JS_SetClassProto(ctx,js_Font_class_id,proto);
		return 0;
	}
	
	static void js_Camera3D_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Camera3D_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Camera3D_get_position(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera3D_class_id);
		Camera3D * ptr=(Camera3D  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector3 * position=&ptr[0].position;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)position,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Camera3D_set_position(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera3D_class_id);
		Camera3D * ptr=(Camera3D  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].position=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Camera3D_get_target(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera3D_class_id);
		Camera3D * ptr=(Camera3D  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector3 * target=&ptr[0].target;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)target,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Camera3D_set_target(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera3D_class_id);
		Camera3D * ptr=(Camera3D  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].target=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Camera3D_get_up(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera3D_class_id);
		Camera3D * ptr=(Camera3D  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector3 * up=&ptr[0].up;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)up,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Camera3D_set_up(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera3D_class_id);
		Camera3D * ptr=(Camera3D  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].up=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Camera3D_get_fovy(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera3D_class_id);
		Camera3D * ptr=(Camera3D  *)shadow[0].ptr;
		float fovy=ptr[0].fovy;
		JSValue ret=JS_NewFloat64(ctx,((double)fovy));
		return ret;
	}
	
	static JSValue js_Camera3D_set_fovy(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera3D_class_id);
		Camera3D * ptr=(Camera3D  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].fovy=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Camera3D_get_projection(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera3D_class_id);
		Camera3D * ptr=(Camera3D  *)shadow[0].ptr;
		int projection=ptr[0].projection;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)projection));
		return ret;
	}
	
	static JSValue js_Camera3D_set_projection(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera3D_class_id);
		Camera3D * ptr=(Camera3D  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].projection=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Camera3D_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Camera3D", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("position",js_Camera3D_get_position,js_Camera3D_set_position),
		JS_CGETSET_DEF("target",js_Camera3D_get_target,js_Camera3D_set_target),
		JS_CGETSET_DEF("up",js_Camera3D_get_up,js_Camera3D_set_up),
		JS_CGETSET_DEF("fovy",js_Camera3D_get_fovy,js_Camera3D_set_fovy),
		JS_CGETSET_DEF("projection",js_Camera3D_get_projection,js_Camera3D_set_projection)
	};
	
	static int js_declare_Camera3D(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Camera3D_class_id);
		JSClassDef js_Camera3D_def={ .class_name = "Camera3D", .finalizer = js_Camera3D_finalizer };
		JS_NewClass(rt,js_Camera3D_class_id,(const JSClassDef  *)&js_Camera3D_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Camera3D_proto_funcs,(int)countof(js_Camera3D_proto_funcs));
		JS_SetClassProto(ctx,js_Camera3D_class_id,proto);
		return 0;
	}
	
	static void js_Camera2D_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Camera2D_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Camera2D_get_offset(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera2D_class_id);
		Camera2D * ptr=(Camera2D  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector2 * offset=&ptr[0].offset;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)offset,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Camera2D_set_offset(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera2D_class_id);
		Camera2D * ptr=(Camera2D  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector2 value=js_getVector2(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].offset=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Camera2D_get_target(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera2D_class_id);
		Camera2D * ptr=(Camera2D  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector2 * target=&ptr[0].target;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)target,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Camera2D_set_target(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera2D_class_id);
		Camera2D * ptr=(Camera2D  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector2 value=js_getVector2(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].target=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Camera2D_get_rotation(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera2D_class_id);
		Camera2D * ptr=(Camera2D  *)shadow[0].ptr;
		float rotation=ptr[0].rotation;
		JSValue ret=JS_NewFloat64(ctx,((double)rotation));
		return ret;
	}
	
	static JSValue js_Camera2D_set_rotation(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera2D_class_id);
		Camera2D * ptr=(Camera2D  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].rotation=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Camera2D_get_zoom(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera2D_class_id);
		Camera2D * ptr=(Camera2D  *)shadow[0].ptr;
		float zoom=ptr[0].zoom;
		JSValue ret=JS_NewFloat64(ctx,((double)zoom));
		return ret;
	}
	
	static JSValue js_Camera2D_set_zoom(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Camera2D_class_id);
		Camera2D * ptr=(Camera2D  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].zoom=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Camera2D_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Camera2D", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("offset",js_Camera2D_get_offset,js_Camera2D_set_offset),
		JS_CGETSET_DEF("target",js_Camera2D_get_target,js_Camera2D_set_target),
		JS_CGETSET_DEF("rotation",js_Camera2D_get_rotation,js_Camera2D_set_rotation),
		JS_CGETSET_DEF("zoom",js_Camera2D_get_zoom,js_Camera2D_set_zoom)
	};
	
	static int js_declare_Camera2D(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Camera2D_class_id);
		JSClassDef js_Camera2D_def={ .class_name = "Camera2D", .finalizer = js_Camera2D_finalizer };
		JS_NewClass(rt,js_Camera2D_class_id,(const JSClassDef  *)&js_Camera2D_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Camera2D_proto_funcs,(int)countof(js_Camera2D_proto_funcs));
		JS_SetClassProto(ctx,js_Camera2D_class_id,proto);
		return 0;
	}
	
	static void js_Mesh_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Mesh_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Mesh_get_vertexCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		int vertexCount=ptr[0].vertexCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)vertexCount));
		return ret;
	}
	
	static JSValue js_Mesh_set_vertexCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].vertexCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_get_triangleCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		int triangleCount=ptr[0].triangleCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)triangleCount));
		return ret;
	}
	
	static JSValue js_Mesh_set_triangleCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].triangleCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_vertices_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].vertexCount*3;i++){
			float src0=ptr[0].vertices[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_vertices_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=(int)ptr[0].vertexCount*3;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_vertices_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].vertexCount*((long)3));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				float src=ptr[0].vertices[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_vertices_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].vertices[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_vertices_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_vertices(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_vertices_values,.keys = js_Mesh_vertices_keys,.get = js_Mesh_vertices_get,.set = js_Mesh_vertices_set,.has = js_Mesh_vertices_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_vertices(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].vertices!=NULL)jsc_free(ctx,(void  *)ptr[0].vertices);
		ptr[0].vertices =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_texcoords_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].vertexCount*2;i++){
			float src0=ptr[0].texcoords[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_texcoords_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=(int)ptr[0].vertexCount*2;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_texcoords_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].vertexCount*((long)2));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*2){
				float src=ptr[0].texcoords[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_texcoords_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].vertexCount*2){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].texcoords[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_texcoords_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*2){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_texcoords(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_texcoords_values,.keys = js_Mesh_texcoords_keys,.get = js_Mesh_texcoords_get,.set = js_Mesh_texcoords_set,.has = js_Mesh_texcoords_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_texcoords(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].texcoords!=NULL)jsc_free(ctx,(void  *)ptr[0].texcoords);
		ptr[0].texcoords =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_texcoords2_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].vertexCount*2;i++){
			float src0=ptr[0].texcoords2[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_texcoords2_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=(int)ptr[0].vertexCount*2;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_texcoords2_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].vertexCount*((long)2));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*2){
				float src=ptr[0].texcoords2[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_texcoords2_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].vertexCount*2){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].texcoords2[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_texcoords2_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*2){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_texcoords2(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_texcoords2_values,.keys = js_Mesh_texcoords2_keys,.get = js_Mesh_texcoords2_get,.set = js_Mesh_texcoords2_set,.has = js_Mesh_texcoords2_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_texcoords2(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].texcoords2!=NULL)jsc_free(ctx,(void  *)ptr[0].texcoords2);
		ptr[0].texcoords2 =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_normals_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].vertexCount*3;i++){
			float src0=ptr[0].normals[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_normals_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=(int)ptr[0].vertexCount*3;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_normals_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].vertexCount*((long)3));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				float src=ptr[0].normals[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_normals_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].normals[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_normals_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_normals(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_normals_values,.keys = js_Mesh_normals_keys,.get = js_Mesh_normals_get,.set = js_Mesh_normals_set,.has = js_Mesh_normals_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_normals(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].normals!=NULL)jsc_free(ctx,(void  *)ptr[0].normals);
		ptr[0].normals =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_tangents_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].vertexCount*4;i++){
			float src0=ptr[0].tangents[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_tangents_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=(int)ptr[0].vertexCount*4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_tangents_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].vertexCount*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				float src=ptr[0].tangents[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_tangents_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].tangents[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_tangents_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_tangents(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_tangents_values,.keys = js_Mesh_tangents_keys,.get = js_Mesh_tangents_get,.set = js_Mesh_tangents_set,.has = js_Mesh_tangents_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_tangents(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].tangents!=NULL)jsc_free(ctx,(void  *)ptr[0].tangents);
		ptr[0].tangents =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_colors_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].vertexCount*4;i++){
			unsigned char src0=ptr[0].colors[i];
			JSValue ret1=JS_NewUint32(ctx,(uint32_t)((unsigned long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_colors_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=(int)ptr[0].vertexCount*4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_colors_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].vertexCount*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				unsigned char src=ptr[0].colors[property];
				JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_colors_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				bool error=(bool)0;
				local_memlock=(bool)true;
				unsigned char ret=js_getunsignedchar(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].colors[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_colors_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_colors(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_colors_values,.keys = js_Mesh_colors_keys,.get = js_Mesh_colors_get,.set = js_Mesh_colors_set,.has = js_Mesh_colors_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_colors(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned char * value=js_getunsignedchar_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].colors!=NULL)jsc_free(ctx,(void  *)ptr[0].colors);
		ptr[0].colors =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_indices_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].vertexCount;i++){
			unsigned short src0=ptr[0].indices[i];
			JSValue ret1=JS_NewUint32(ctx,(uint32_t)((unsigned long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_indices_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=ptr[0].vertexCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_indices_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].vertexCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount){
				unsigned short src=ptr[0].indices[property];
				JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_indices_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].vertexCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				unsigned short ret=js_getunsignedshort(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].indices[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_indices_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_indices(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_indices_values,.keys = js_Mesh_indices_keys,.get = js_Mesh_indices_get,.set = js_Mesh_indices_set,.has = js_Mesh_indices_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_indices(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned short * value=js_getunsignedshort_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].indices!=NULL)jsc_free(ctx,(void  *)ptr[0].indices);
		ptr[0].indices =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_animVertices_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].vertexCount*3;i++){
			float src0=ptr[0].animVertices[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_animVertices_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=(int)ptr[0].vertexCount*3;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_animVertices_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].vertexCount*((long)3));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				float src=ptr[0].animVertices[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_animVertices_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].animVertices[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_animVertices_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_animVertices(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_animVertices_values,.keys = js_Mesh_animVertices_keys,.get = js_Mesh_animVertices_get,.set = js_Mesh_animVertices_set,.has = js_Mesh_animVertices_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_animVertices(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].animVertices!=NULL)jsc_free(ctx,(void  *)ptr[0].animVertices);
		ptr[0].animVertices =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_animNormals_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].vertexCount*3;i++){
			float src0=ptr[0].animNormals[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_animNormals_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=(int)ptr[0].vertexCount*3;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_animNormals_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].vertexCount*((long)3));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				float src=ptr[0].animNormals[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_animNormals_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].animNormals[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_animNormals_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*3){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_animNormals(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_animNormals_values,.keys = js_Mesh_animNormals_keys,.get = js_Mesh_animNormals_get,.set = js_Mesh_animNormals_set,.has = js_Mesh_animNormals_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_animNormals(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].animNormals!=NULL)jsc_free(ctx,(void  *)ptr[0].animNormals);
		ptr[0].animNormals =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_boneIds_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].vertexCount*4;i++){
			unsigned char src0=ptr[0].boneIds[i];
			JSValue ret1=JS_NewUint32(ctx,(uint32_t)((unsigned long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_boneIds_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=(int)ptr[0].vertexCount*4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_boneIds_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].vertexCount*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				unsigned char src=ptr[0].boneIds[property];
				JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_boneIds_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				bool error=(bool)0;
				local_memlock=(bool)true;
				unsigned char ret=js_getunsignedchar(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].boneIds[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_boneIds_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_boneIds(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_boneIds_values,.keys = js_Mesh_boneIds_keys,.get = js_Mesh_boneIds_get,.set = js_Mesh_boneIds_set,.has = js_Mesh_boneIds_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_boneIds(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned char * value=js_getunsignedchar_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].boneIds!=NULL)jsc_free(ctx,(void  *)ptr[0].boneIds);
		ptr[0].boneIds =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_boneWeights_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].vertexCount*4;i++){
			float src0=ptr[0].boneWeights[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_boneWeights_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=(int)ptr[0].vertexCount*4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_boneWeights_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].vertexCount*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				float src=ptr[0].boneWeights[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_boneWeights_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].boneWeights[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_boneWeights_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].vertexCount*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_boneWeights(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_boneWeights_values,.keys = js_Mesh_boneWeights_keys,.get = js_Mesh_boneWeights_get,.set = js_Mesh_boneWeights_set,.has = js_Mesh_boneWeights_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_boneWeights(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].boneWeights!=NULL)jsc_free(ctx,(void  *)ptr[0].boneWeights);
		ptr[0].boneWeights =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_boneMatrices_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].boneCount;i++){
			Matrix * src0=(ptr[0].boneMatrices+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_Matrix_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_boneMatrices_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=ptr[0].boneCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_boneMatrices_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].boneCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				Matrix * src=(ptr[0].boneMatrices+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_boneMatrices_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				Matrix ret=js_getMatrix(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].boneMatrices[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_boneMatrices_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_boneMatrices(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_boneMatrices_values,.keys = js_Mesh_boneMatrices_keys,.get = js_Mesh_boneMatrices_get,.set = js_Mesh_boneMatrices_set,.has = js_Mesh_boneMatrices_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_boneMatrices(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Matrix * value=js_getMatrix_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].boneMatrices!=NULL)jsc_free(ctx,(void  *)ptr[0].boneMatrices);
		ptr[0].boneMatrices =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_get_boneCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		int boneCount=ptr[0].boneCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)boneCount));
		return ret;
	}
	
	static JSValue js_Mesh_set_boneCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].boneCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_get_vaoId(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		unsigned int vaoId=ptr[0].vaoId;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)vaoId));
		return ret;
	}
	
	static JSValue js_Mesh_set_vaoId(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].vaoId=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Mesh_vboId_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<MAX_MESH_VERTEX_BUFFERS;i++){
			unsigned int src0=ptr[0].vboId[i];
			JSValue ret1=JS_NewUint32(ctx,(uint32_t)((unsigned long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Mesh_vboId_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Mesh * ptr=(Mesh  *)ptr_u;
		int length=MAX_MESH_VERTEX_BUFFERS;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Mesh_vboId_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)MAX_MESH_VERTEX_BUFFERS));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<MAX_MESH_VERTEX_BUFFERS){
				unsigned int src=ptr[0].vboId[property];
				JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Mesh_vboId_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<MAX_MESH_VERTEX_BUFFERS){
				bool error=(bool)0;
				local_memlock=(bool)true;
				unsigned int ret=js_getunsignedint(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].vboId[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Mesh_vboId_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Mesh * ptr=(Mesh  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<MAX_MESH_VERTEX_BUFFERS){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Mesh_get_vboId(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Mesh_vboId_values,.keys = js_Mesh_vboId_keys,.get = js_Mesh_vboId_get,.set = js_Mesh_vboId_set,.has = js_Mesh_vboId_has});
		return ret;
	}
	
	static JSValue js_Mesh_set_vboId(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Mesh_class_id);
		Mesh * ptr=(Mesh  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int * value=js_getunsignedint_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].vboId!=NULL)jsc_free(ctx,(void  *)ptr[0].vboId);
		ptr[0].vboId =value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Mesh_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Mesh", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("vertexCount",js_Mesh_get_vertexCount,js_Mesh_set_vertexCount),
		JS_CGETSET_DEF("triangleCount",js_Mesh_get_triangleCount,js_Mesh_set_triangleCount),
		JS_CGETSET_DEF("vertices",js_Mesh_get_vertices,js_Mesh_set_vertices),
		JS_CGETSET_DEF("texcoords",js_Mesh_get_texcoords,js_Mesh_set_texcoords),
		JS_CGETSET_DEF("texcoords2",js_Mesh_get_texcoords2,js_Mesh_set_texcoords2),
		JS_CGETSET_DEF("normals",js_Mesh_get_normals,js_Mesh_set_normals),
		JS_CGETSET_DEF("tangents",js_Mesh_get_tangents,js_Mesh_set_tangents),
		JS_CGETSET_DEF("colors",js_Mesh_get_colors,js_Mesh_set_colors),
		JS_CGETSET_DEF("indices",js_Mesh_get_indices,js_Mesh_set_indices),
		JS_CGETSET_DEF("animVertices",js_Mesh_get_animVertices,js_Mesh_set_animVertices),
		JS_CGETSET_DEF("animNormals",js_Mesh_get_animNormals,js_Mesh_set_animNormals),
		JS_CGETSET_DEF("boneIds",js_Mesh_get_boneIds,js_Mesh_set_boneIds),
		JS_CGETSET_DEF("boneWeights",js_Mesh_get_boneWeights,js_Mesh_set_boneWeights),
		JS_CGETSET_DEF("boneMatrices",js_Mesh_get_boneMatrices,js_Mesh_set_boneMatrices),
		JS_CGETSET_DEF("boneCount",js_Mesh_get_boneCount,js_Mesh_set_boneCount),
		JS_CGETSET_DEF("vaoId",js_Mesh_get_vaoId,js_Mesh_set_vaoId),
		JS_CGETSET_DEF("vboId",js_Mesh_get_vboId,js_Mesh_set_vboId)
	};
	
	static int js_declare_Mesh(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Mesh_class_id);
		JSClassDef js_Mesh_def={ .class_name = "Mesh", .finalizer = js_Mesh_finalizer };
		JS_NewClass(rt,js_Mesh_class_id,(const JSClassDef  *)&js_Mesh_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Mesh_proto_funcs,(int)countof(js_Mesh_proto_funcs));
		JS_SetClassProto(ctx,js_Mesh_class_id,proto);
		return 0;
	}
	
	static void js_Shader_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Shader_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Shader_get_id(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Shader_class_id);
		Shader * ptr=(Shader  *)shadow[0].ptr;
		unsigned int id=ptr[0].id;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)id));
		return ret;
	}
	
	static JSValue js_Shader_set_id(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Shader_class_id);
		Shader * ptr=(Shader  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].id=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Shader_locs_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Shader * ptr=(Shader  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<RL_MAX_SHADER_LOCATIONS;i++){
			int src0=ptr[0].locs[i];
			JSValue ret1=JS_NewInt32(ctx,(int32_t)((long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Shader_locs_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Shader * ptr=(Shader  *)ptr_u;
		int length=RL_MAX_SHADER_LOCATIONS;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Shader_locs_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Shader * ptr=(Shader  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)RL_MAX_SHADER_LOCATIONS));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<RL_MAX_SHADER_LOCATIONS){
				int src=ptr[0].locs[property];
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Shader_locs_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Shader * ptr=(Shader  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<RL_MAX_SHADER_LOCATIONS){
				bool error=(bool)0;
				local_memlock=(bool)true;
				int ret=js_getint(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].locs[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Shader_locs_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Shader * ptr=(Shader  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<RL_MAX_SHADER_LOCATIONS){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Shader_get_locs(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Shader_class_id);
		Shader * ptr=(Shader  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Shader_locs_values,.keys = js_Shader_locs_keys,.get = js_Shader_locs_get,.set = js_Shader_locs_set,.has = js_Shader_locs_has});
		return ret;
	}
	
	static JSValue js_Shader_set_locs(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Shader_class_id);
		Shader * ptr=(Shader  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int * value=js_getint_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].locs!=NULL)jsc_free(ctx,(void  *)ptr[0].locs);
		ptr[0].locs =value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Shader_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Shader", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("id",js_Shader_get_id,js_Shader_set_id),
		JS_CGETSET_DEF("locs",js_Shader_get_locs,js_Shader_set_locs)
	};
	
	static int js_declare_Shader(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Shader_class_id);
		JSClassDef js_Shader_def={ .class_name = "Shader", .finalizer = js_Shader_finalizer };
		JS_NewClass(rt,js_Shader_class_id,(const JSClassDef  *)&js_Shader_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Shader_proto_funcs,(int)countof(js_Shader_proto_funcs));
		JS_SetClassProto(ctx,js_Shader_class_id,proto);
		return 0;
	}
	
	static void js_MaterialMap_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_MaterialMap_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_MaterialMap_get_texture(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_MaterialMap_class_id);
		MaterialMap * ptr=(MaterialMap  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Texture2D * texture=&ptr[0].texture;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)texture,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Texture_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MaterialMap_set_texture(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_MaterialMap_class_id);
		MaterialMap * ptr=(MaterialMap  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Texture2D value=js_getTexture2D(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].texture=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_MaterialMap_get_color(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_MaterialMap_class_id);
		MaterialMap * ptr=(MaterialMap  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Color * color=&ptr[0].color;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)color,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MaterialMap_set_color(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_MaterialMap_class_id);
		MaterialMap * ptr=(MaterialMap  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Color value=js_getColor(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].color=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_MaterialMap_get_value(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_MaterialMap_class_id);
		MaterialMap * ptr=(MaterialMap  *)shadow[0].ptr;
		float value=ptr[0].value;
		JSValue ret=JS_NewFloat64(ctx,((double)value));
		return ret;
	}
	
	static JSValue js_MaterialMap_set_value(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_MaterialMap_class_id);
		MaterialMap * ptr=(MaterialMap  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].value=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_MaterialMap_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","MaterialMap", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("texture",js_MaterialMap_get_texture,js_MaterialMap_set_texture),
		JS_CGETSET_DEF("color",js_MaterialMap_get_color,js_MaterialMap_set_color),
		JS_CGETSET_DEF("value",js_MaterialMap_get_value,js_MaterialMap_set_value)
	};
	
	static int js_declare_MaterialMap(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_MaterialMap_class_id);
		JSClassDef js_MaterialMap_def={ .class_name = "MaterialMap", .finalizer = js_MaterialMap_finalizer };
		JS_NewClass(rt,js_MaterialMap_class_id,(const JSClassDef  *)&js_MaterialMap_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_MaterialMap_proto_funcs,(int)countof(js_MaterialMap_proto_funcs));
		JS_SetClassProto(ctx,js_MaterialMap_class_id,proto);
		return 0;
	}
	
	static void js_Material_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Material_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Material_get_shader(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Material_class_id);
		Material * ptr=(Material  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Shader * shader=&ptr[0].shader;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)shader,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Shader_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Material_set_shader(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Material_class_id);
		Material * ptr=(Material  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Shader value=js_getShader(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].shader=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Material_maps_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Material * ptr=(Material  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<12;i++){
			MaterialMap * src0=(ptr[0].maps+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_MaterialMap_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Material_maps_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Material * ptr=(Material  *)ptr_u;
		int length=(int)12;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Material_maps_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Material * ptr=(Material  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)12));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<12){
				MaterialMap * src=(ptr[0].maps+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_MaterialMap_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Material_maps_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Material * ptr=(Material  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<12){
				bool error=(bool)0;
				local_memlock=(bool)true;
				MaterialMap ret=js_getMaterialMap(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].maps[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Material_maps_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Material * ptr=(Material  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<12){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Material_get_maps(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Material_class_id);
		Material * ptr=(Material  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Material_maps_values,.keys = js_Material_maps_keys,.get = js_Material_maps_get,.set = js_Material_maps_set,.has = js_Material_maps_has});
		return ret;
	}
	
	static JSValue js_Material_set_maps(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Material_class_id);
		Material * ptr=(Material  *)shadow[0].ptr;
		local_memlock=(bool)true;
		MaterialMap * value=js_getMaterialMap_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].maps!=NULL)jsc_free(ctx,(void  *)ptr[0].maps);
		ptr[0].maps =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Material_params_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Material * ptr=(Material  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<4;i++){
			float src0=ptr[0].params[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Material_params_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Material * ptr=(Material  *)ptr_u;
		int length=(int)4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Material_params_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Material * ptr=(Material  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<4){
				float src=ptr[0].params[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Material_params_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Material * ptr=(Material  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<4){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].params[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Material_params_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Material * ptr=(Material  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Material_get_params(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Material_class_id);
		Material * ptr=(Material  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Material_params_values,.keys = js_Material_params_keys,.get = js_Material_params_get,.set = js_Material_params_set,.has = js_Material_params_has});
		return ret;
	}
	
	static JSValue js_Material_set_params(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Material_class_id);
		Material * ptr=(Material  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arr4nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].params,(const void  *)value,4*sizeof(float));
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Material_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Material", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("shader",js_Material_get_shader,js_Material_set_shader),
		JS_CGETSET_DEF("maps",js_Material_get_maps,js_Material_set_maps),
		JS_CGETSET_DEF("params",js_Material_get_params,js_Material_set_params)
	};
	
	static int js_declare_Material(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Material_class_id);
		JSClassDef js_Material_def={ .class_name = "Material", .finalizer = js_Material_finalizer };
		JS_NewClass(rt,js_Material_class_id,(const JSClassDef  *)&js_Material_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Material_proto_funcs,(int)countof(js_Material_proto_funcs));
		JS_SetClassProto(ctx,js_Material_class_id,proto);
		return 0;
	}
	
	static void js_Transform_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Transform_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Transform_get_translation(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Transform_class_id);
		Transform * ptr=(Transform  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector3 * translation=&ptr[0].translation;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)translation,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Transform_set_translation(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Transform_class_id);
		Transform * ptr=(Transform  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].translation=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Transform_get_rotation(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Transform_class_id);
		Transform * ptr=(Transform  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Quaternion * rotation=&ptr[0].rotation;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)rotation,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector4_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Transform_set_rotation(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Transform_class_id);
		Transform * ptr=(Transform  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Quaternion value=js_getQuaternion(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].rotation=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Transform_get_scale(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Transform_class_id);
		Transform * ptr=(Transform  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector3 * scale=&ptr[0].scale;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)scale,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Transform_set_scale(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Transform_class_id);
		Transform * ptr=(Transform  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].scale=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Transform_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Transform", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("translation",js_Transform_get_translation,js_Transform_set_translation),
		JS_CGETSET_DEF("rotation",js_Transform_get_rotation,js_Transform_set_rotation),
		JS_CGETSET_DEF("scale",js_Transform_get_scale,js_Transform_set_scale)
	};
	
	static int js_declare_Transform(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Transform_class_id);
		JSClassDef js_Transform_def={ .class_name = "Transform", .finalizer = js_Transform_finalizer };
		JS_NewClass(rt,js_Transform_class_id,(const JSClassDef  *)&js_Transform_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Transform_proto_funcs,(int)countof(js_Transform_proto_funcs));
		JS_SetClassProto(ctx,js_Transform_class_id,proto);
		return 0;
	}
	
	static void js_BoneInfo_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_BoneInfo_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_BoneInfo_name_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		BoneInfo * ptr=(BoneInfo  *)ptr_u;
		JSValue ret=JS_NewString(ctx,(const char  *)ptr[0].name);
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_BoneInfo_name_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		BoneInfo * ptr=(BoneInfo  *)ptr_u;
		int length=(int)32;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_BoneInfo_name_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		BoneInfo * ptr=(BoneInfo  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)32));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<32){
				char src=ptr[0].name[property];
				JSValue ret=JS_NewStringLen(ctx,(const char  *)&src,(size_t)1);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_BoneInfo_name_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		BoneInfo * ptr=(BoneInfo  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<32){
				bool error=(bool)0;
				local_memlock=(bool)true;
				char ret=js_getchar(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].name[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_BoneInfo_name_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		BoneInfo * ptr=(BoneInfo  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<32){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_BoneInfo_get_name(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_BoneInfo_class_id);
		BoneInfo * ptr=(BoneInfo  *)shadow[0].ptr;
		char * name=ptr[0].name;
		JSValue ret=JS_NewString(ctx,(const char  *)name);
		return ret;
	}
	
	static JSValue js_BoneInfo_set_name(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_BoneInfo_class_id);
		BoneInfo * ptr=(BoneInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		char * value=js_getchar_arr32nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].name,(const void  *)value,32*sizeof(char));
		return JS_UNDEFINED;
	}
	
	static JSValue js_BoneInfo_get_parent(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_BoneInfo_class_id);
		BoneInfo * ptr=(BoneInfo  *)shadow[0].ptr;
		int parent=ptr[0].parent;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)parent));
		return ret;
	}
	
	static JSValue js_BoneInfo_set_parent(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_BoneInfo_class_id);
		BoneInfo * ptr=(BoneInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].parent=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_BoneInfo_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","BoneInfo", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("name",js_BoneInfo_get_name,js_BoneInfo_set_name),
		JS_CGETSET_DEF("parent",js_BoneInfo_get_parent,js_BoneInfo_set_parent)
	};
	
	static int js_declare_BoneInfo(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_BoneInfo_class_id);
		JSClassDef js_BoneInfo_def={ .class_name = "BoneInfo", .finalizer = js_BoneInfo_finalizer };
		JS_NewClass(rt,js_BoneInfo_class_id,(const JSClassDef  *)&js_BoneInfo_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_BoneInfo_proto_funcs,(int)countof(js_BoneInfo_proto_funcs));
		JS_SetClassProto(ctx,js_BoneInfo_class_id,proto);
		return 0;
	}
	
	static void js_Model_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Model_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Model_get_transform(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Matrix * transform=&ptr[0].transform;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)transform,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Model_set_transform(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Matrix value=js_getMatrix(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].transform=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Model_get_meshCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		int meshCount=ptr[0].meshCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)meshCount));
		return ret;
	}
	
	static JSValue js_Model_set_meshCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].meshCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Model_get_materialCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		int materialCount=ptr[0].materialCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)materialCount));
		return ret;
	}
	
	static JSValue js_Model_set_materialCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].materialCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Model_meshes_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].meshCount;i++){
			Mesh * src0=(ptr[0].meshes+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_Mesh_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Model_meshes_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Model * ptr=(Model  *)ptr_u;
		int length=ptr[0].meshCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Model_meshes_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].meshCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].meshCount){
				Mesh * src=(ptr[0].meshes+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Model_meshes_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].meshCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				Mesh ret=js_getMesh(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].meshes[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Model_meshes_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].meshCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Model_get_meshes(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Model_meshes_values,.keys = js_Model_meshes_keys,.get = js_Model_meshes_get,.set = js_Model_meshes_set,.has = js_Model_meshes_has});
		return ret;
	}
	
	static JSValue js_Model_set_meshes(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Mesh * value=js_getMesh_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].meshes!=NULL)jsc_free(ctx,(void  *)ptr[0].meshes);
		ptr[0].meshes =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Model_materials_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].materialCount;i++){
			Material * src0=(ptr[0].materials+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_Material_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Model_materials_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Model * ptr=(Model  *)ptr_u;
		int length=ptr[0].materialCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Model_materials_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].materialCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].materialCount){
				Material * src=(ptr[0].materials+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_Material_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Model_materials_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].materialCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				Material ret=js_getMaterial(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].materials[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Model_materials_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].materialCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Model_get_materials(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Model_materials_values,.keys = js_Model_materials_keys,.get = js_Model_materials_get,.set = js_Model_materials_set,.has = js_Model_materials_has});
		return ret;
	}
	
	static JSValue js_Model_set_materials(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Material * value=js_getMaterial_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].materials!=NULL)jsc_free(ctx,(void  *)ptr[0].materials);
		ptr[0].materials =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Model_meshMaterial_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].meshCount;i++){
			int src0=ptr[0].meshMaterial[i];
			JSValue ret1=JS_NewInt32(ctx,(int32_t)((long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Model_meshMaterial_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Model * ptr=(Model  *)ptr_u;
		int length=ptr[0].meshCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Model_meshMaterial_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].meshCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].meshCount){
				int src=ptr[0].meshMaterial[property];
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Model_meshMaterial_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].meshCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				int ret=js_getint(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].meshMaterial[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Model_meshMaterial_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].meshCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Model_get_meshMaterial(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Model_meshMaterial_values,.keys = js_Model_meshMaterial_keys,.get = js_Model_meshMaterial_get,.set = js_Model_meshMaterial_set,.has = js_Model_meshMaterial_has});
		return ret;
	}
	
	static JSValue js_Model_set_meshMaterial(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int * value=js_getint_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].meshMaterial!=NULL)jsc_free(ctx,(void  *)ptr[0].meshMaterial);
		ptr[0].meshMaterial =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Model_get_boneCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		int boneCount=ptr[0].boneCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)boneCount));
		return ret;
	}
	
	static JSValue js_Model_set_boneCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].boneCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Model_bones_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].boneCount;i++){
			BoneInfo * src0=(ptr[0].bones+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_BoneInfo_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Model_bones_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Model * ptr=(Model  *)ptr_u;
		int length=ptr[0].boneCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Model_bones_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].boneCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				BoneInfo * src=(ptr[0].bones+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_BoneInfo_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Model_bones_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				BoneInfo ret=js_getBoneInfo(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].bones[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Model_bones_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Model_get_bones(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Model_bones_values,.keys = js_Model_bones_keys,.get = js_Model_bones_get,.set = js_Model_bones_set,.has = js_Model_bones_has});
		return ret;
	}
	
	static JSValue js_Model_set_bones(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		local_memlock=(bool)true;
		BoneInfo * value=js_getBoneInfo_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].bones!=NULL)jsc_free(ctx,(void  *)ptr[0].bones);
		ptr[0].bones =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Model_bindPose_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].boneCount;i++){
			Transform * src0=(ptr[0].bindPose+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_Transform_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Model_bindPose_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Model * ptr=(Model  *)ptr_u;
		int length=ptr[0].boneCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Model_bindPose_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].boneCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				Transform * src=(ptr[0].bindPose+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_Transform_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Model_bindPose_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				Transform ret=js_getTransform(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].bindPose[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Model_bindPose_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Model * ptr=(Model  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Model_get_bindPose(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Model_bindPose_values,.keys = js_Model_bindPose_keys,.get = js_Model_bindPose_get,.set = js_Model_bindPose_set,.has = js_Model_bindPose_has});
		return ret;
	}
	
	static JSValue js_Model_set_bindPose(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Model_class_id);
		Model * ptr=(Model  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Transform * value=js_getTransform_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].bindPose!=NULL)jsc_free(ctx,(void  *)ptr[0].bindPose);
		ptr[0].bindPose =value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Model_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Model", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("transform",js_Model_get_transform,js_Model_set_transform),
		JS_CGETSET_DEF("meshCount",js_Model_get_meshCount,js_Model_set_meshCount),
		JS_CGETSET_DEF("materialCount",js_Model_get_materialCount,js_Model_set_materialCount),
		JS_CGETSET_DEF("meshes",js_Model_get_meshes,js_Model_set_meshes),
		JS_CGETSET_DEF("materials",js_Model_get_materials,js_Model_set_materials),
		JS_CGETSET_DEF("meshMaterial",js_Model_get_meshMaterial,js_Model_set_meshMaterial),
		JS_CGETSET_DEF("boneCount",js_Model_get_boneCount,js_Model_set_boneCount),
		JS_CGETSET_DEF("bones",js_Model_get_bones,js_Model_set_bones),
		JS_CGETSET_DEF("bindPose",js_Model_get_bindPose,js_Model_set_bindPose)
	};
	
	static int js_declare_Model(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Model_class_id);
		JSClassDef js_Model_def={ .class_name = "Model", .finalizer = js_Model_finalizer };
		JS_NewClass(rt,js_Model_class_id,(const JSClassDef  *)&js_Model_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Model_proto_funcs,(int)countof(js_Model_proto_funcs));
		JS_SetClassProto(ctx,js_Model_class_id,proto);
		return 0;
	}
	
	static void js_ModelAnimation_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_ModelAnimation_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_ModelAnimation_get_boneCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_ModelAnimation_class_id);
		ModelAnimation * ptr=(ModelAnimation  *)shadow[0].ptr;
		int boneCount=ptr[0].boneCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)boneCount));
		return ret;
	}
	
	static JSValue js_ModelAnimation_set_boneCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_ModelAnimation_class_id);
		ModelAnimation * ptr=(ModelAnimation  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].boneCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_ModelAnimation_get_frameCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_ModelAnimation_class_id);
		ModelAnimation * ptr=(ModelAnimation  *)shadow[0].ptr;
		int frameCount=ptr[0].frameCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)frameCount));
		return ret;
	}
	
	static JSValue js_ModelAnimation_set_frameCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_ModelAnimation_class_id);
		ModelAnimation * ptr=(ModelAnimation  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].frameCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_ModelAnimation_bones_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].boneCount;i++){
			BoneInfo * src0=(ptr[0].bones+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_BoneInfo_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_ModelAnimation_bones_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		int length=ptr[0].boneCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_ModelAnimation_bones_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].boneCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				BoneInfo * src=(ptr[0].bones+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_BoneInfo_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_ModelAnimation_bones_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				BoneInfo ret=js_getBoneInfo(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].bones[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_ModelAnimation_bones_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].boneCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_ModelAnimation_get_bones(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_ModelAnimation_class_id);
		ModelAnimation * ptr=(ModelAnimation  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_ModelAnimation_bones_values,.keys = js_ModelAnimation_bones_keys,.get = js_ModelAnimation_bones_get,.set = js_ModelAnimation_bones_set,.has = js_ModelAnimation_bones_has});
		return ret;
	}
	
	static JSValue js_ModelAnimation_set_bones(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_ModelAnimation_class_id);
		ModelAnimation * ptr=(ModelAnimation  *)shadow[0].ptr;
		local_memlock=(bool)true;
		BoneInfo * value=js_getBoneInfo_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].bones!=NULL)jsc_free(ctx,(void  *)ptr[0].bones);
		ptr[0].bones =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_ModelAnimation_framePoses_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].frameCount;i++){
			Transform * src0=ptr[0].framePoses[i];
			JSValue ret1=JS_NewArray(ctx);
			for(int i0=0;i0<ptr[0].boneCount;i0++){
				Transform * src1=(src0+i0);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret2=create_shadow_with_external((void  *)src1,anchor);
				JSValue ret2=JS_NewObjectClass(ctx,js_Transform_class_id);
				JS_SetOpaque(ret2,(void  *)ptr_ret2);
				JS_DefinePropertyValueUint32(ctx,ret1,(uint32_t)i0,ret2,JS_PROP_C_W_E);
			}
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_ModelAnimation_framePoses_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		int length=ptr[0].frameCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_ModelAnimation_framePoses_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].frameCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].frameCount){
				Transform * src=ptr[0].framePoses[property];
				JSValue ret=JS_NewArray(ctx);
				for(int i=0;i<ptr[0].boneCount;i++){
					Transform * src0=(src+i);
					JS_DupValue(ctx,anchor);
					opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
					JSValue ret1=JS_NewObjectClass(ctx,js_Transform_class_id);
					JS_SetOpaque(ret1,(void  *)ptr_ret1);
					JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
				}
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_ModelAnimation_framePoses_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].frameCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				Transform * ret=js_getTransform_arr_arg1(ctx,set_to,&error,ptr[0].boneCount);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].framePoses[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_ModelAnimation_framePoses_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].frameCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_ModelAnimation_get_framePoses(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_ModelAnimation_class_id);
		ModelAnimation * ptr=(ModelAnimation  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_ModelAnimation_framePoses_values,.keys = js_ModelAnimation_framePoses_keys,.get = js_ModelAnimation_framePoses_get,.set = js_ModelAnimation_framePoses_set,.has = js_ModelAnimation_framePoses_has});
		return ret;
	}
	
	static JSValue js_ModelAnimation_set_framePoses(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_ModelAnimation_class_id);
		ModelAnimation * ptr=(ModelAnimation  *)shadow[0].ptr;
		memoryNode * memoryHead=(memoryNode  *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		local_memlock=(bool)true;
		Transform * * value=js_getTransform_arr_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].framePoses!=NULL)jsc_free(ctx,(void  *)*ptr[0].framePoses);
		ptr[0].framePoses =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_ModelAnimation_name_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		JSValue ret=JS_NewString(ctx,(const char  *)ptr[0].name);
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_ModelAnimation_name_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		int length=(int)32;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_ModelAnimation_name_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)32));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<32){
				char src=ptr[0].name[property];
				JSValue ret=JS_NewStringLen(ctx,(const char  *)&src,(size_t)1);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_ModelAnimation_name_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<32){
				bool error=(bool)0;
				local_memlock=(bool)true;
				char ret=js_getchar(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].name[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_ModelAnimation_name_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		ModelAnimation * ptr=(ModelAnimation  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<32){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_ModelAnimation_get_name(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_ModelAnimation_class_id);
		ModelAnimation * ptr=(ModelAnimation  *)shadow[0].ptr;
		char * name=ptr[0].name;
		JSValue ret=JS_NewString(ctx,(const char  *)name);
		return ret;
	}
	
	static JSValue js_ModelAnimation_set_name(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_ModelAnimation_class_id);
		ModelAnimation * ptr=(ModelAnimation  *)shadow[0].ptr;
		local_memlock=(bool)true;
		char * value=js_getchar_arr32nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].name,(const void  *)value,32*sizeof(char));
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_ModelAnimation_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","ModelAnimation", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("boneCount",js_ModelAnimation_get_boneCount,js_ModelAnimation_set_boneCount),
		JS_CGETSET_DEF("frameCount",js_ModelAnimation_get_frameCount,js_ModelAnimation_set_frameCount),
		JS_CGETSET_DEF("bones",js_ModelAnimation_get_bones,js_ModelAnimation_set_bones),
		JS_CGETSET_DEF("framePoses",js_ModelAnimation_get_framePoses,js_ModelAnimation_set_framePoses),
		JS_CGETSET_DEF("name",js_ModelAnimation_get_name,js_ModelAnimation_set_name)
	};
	
	static int js_declare_ModelAnimation(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_ModelAnimation_class_id);
		JSClassDef js_ModelAnimation_def={ .class_name = "ModelAnimation", .finalizer = js_ModelAnimation_finalizer };
		JS_NewClass(rt,js_ModelAnimation_class_id,(const JSClassDef  *)&js_ModelAnimation_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_ModelAnimation_proto_funcs,(int)countof(js_ModelAnimation_proto_funcs));
		JS_SetClassProto(ctx,js_ModelAnimation_class_id,proto);
		return 0;
	}
	
	static void js_Ray_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Ray_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Ray_get_position(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Ray_class_id);
		Ray * ptr=(Ray  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector3 * position=&ptr[0].position;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)position,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Ray_set_position(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Ray_class_id);
		Ray * ptr=(Ray  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].position=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Ray_get_direction(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Ray_class_id);
		Ray * ptr=(Ray  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector3 * direction=&ptr[0].direction;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)direction,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Ray_set_direction(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Ray_class_id);
		Ray * ptr=(Ray  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].direction=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Ray_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Ray", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("position",js_Ray_get_position,js_Ray_set_position),
		JS_CGETSET_DEF("direction",js_Ray_get_direction,js_Ray_set_direction)
	};
	
	static int js_declare_Ray(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Ray_class_id);
		JSClassDef js_Ray_def={ .class_name = "Ray", .finalizer = js_Ray_finalizer };
		JS_NewClass(rt,js_Ray_class_id,(const JSClassDef  *)&js_Ray_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Ray_proto_funcs,(int)countof(js_Ray_proto_funcs));
		JS_SetClassProto(ctx,js_Ray_class_id,proto);
		return 0;
	}
	
	static void js_RayCollision_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_RayCollision_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_RayCollision_get_hit(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RayCollision_class_id);
		RayCollision * ptr=(RayCollision  *)shadow[0].ptr;
		bool hit=ptr[0].hit;
		JSValue ret=JS_NewBool(ctx,hit);
		return ret;
	}
	
	static JSValue js_RayCollision_set_hit(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RayCollision_class_id);
		RayCollision * ptr=(RayCollision  *)shadow[0].ptr;
		local_memlock=(bool)true;
		bool value=js_getbool(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].hit=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_RayCollision_get_distance(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RayCollision_class_id);
		RayCollision * ptr=(RayCollision  *)shadow[0].ptr;
		float distance=ptr[0].distance;
		JSValue ret=JS_NewFloat64(ctx,((double)distance));
		return ret;
	}
	
	static JSValue js_RayCollision_set_distance(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RayCollision_class_id);
		RayCollision * ptr=(RayCollision  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].distance=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_RayCollision_get_point(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RayCollision_class_id);
		RayCollision * ptr=(RayCollision  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector3 * point=&ptr[0].point;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)point,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_RayCollision_set_point(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RayCollision_class_id);
		RayCollision * ptr=(RayCollision  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].point=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_RayCollision_get_normal(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RayCollision_class_id);
		RayCollision * ptr=(RayCollision  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector3 * normal=&ptr[0].normal;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)normal,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_RayCollision_set_normal(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_RayCollision_class_id);
		RayCollision * ptr=(RayCollision  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].normal=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_RayCollision_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","RayCollision", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("hit",js_RayCollision_get_hit,js_RayCollision_set_hit),
		JS_CGETSET_DEF("distance",js_RayCollision_get_distance,js_RayCollision_set_distance),
		JS_CGETSET_DEF("point",js_RayCollision_get_point,js_RayCollision_set_point),
		JS_CGETSET_DEF("normal",js_RayCollision_get_normal,js_RayCollision_set_normal)
	};
	
	static int js_declare_RayCollision(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_RayCollision_class_id);
		JSClassDef js_RayCollision_def={ .class_name = "RayCollision", .finalizer = js_RayCollision_finalizer };
		JS_NewClass(rt,js_RayCollision_class_id,(const JSClassDef  *)&js_RayCollision_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_RayCollision_proto_funcs,(int)countof(js_RayCollision_proto_funcs));
		JS_SetClassProto(ctx,js_RayCollision_class_id,proto);
		return 0;
	}
	
	static void js_BoundingBox_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_BoundingBox_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_BoundingBox_get_min(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_BoundingBox_class_id);
		BoundingBox * ptr=(BoundingBox  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector3 * min=&ptr[0].min;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)min,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_BoundingBox_set_min(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_BoundingBox_class_id);
		BoundingBox * ptr=(BoundingBox  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].min=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_BoundingBox_get_max(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_BoundingBox_class_id);
		BoundingBox * ptr=(BoundingBox  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Vector3 * max=&ptr[0].max;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)max,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_BoundingBox_set_max(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_BoundingBox_class_id);
		BoundingBox * ptr=(BoundingBox  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].max=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_BoundingBox_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","BoundingBox", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("min",js_BoundingBox_get_min,js_BoundingBox_set_min),
		JS_CGETSET_DEF("max",js_BoundingBox_get_max,js_BoundingBox_set_max)
	};
	
	static int js_declare_BoundingBox(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_BoundingBox_class_id);
		JSClassDef js_BoundingBox_def={ .class_name = "BoundingBox", .finalizer = js_BoundingBox_finalizer };
		JS_NewClass(rt,js_BoundingBox_class_id,(const JSClassDef  *)&js_BoundingBox_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_BoundingBox_proto_funcs,(int)countof(js_BoundingBox_proto_funcs));
		JS_SetClassProto(ctx,js_BoundingBox_class_id,proto);
		return 0;
	}
	
	static void js_Wave_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Wave_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Wave_get_frameCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Wave_class_id);
		Wave * ptr=(Wave  *)shadow[0].ptr;
		unsigned int frameCount=ptr[0].frameCount;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)frameCount));
		return ret;
	}
	
	static JSValue js_Wave_set_frameCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Wave_class_id);
		Wave * ptr=(Wave  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].frameCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Wave_get_sampleRate(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Wave_class_id);
		Wave * ptr=(Wave  *)shadow[0].ptr;
		unsigned int sampleRate=ptr[0].sampleRate;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)sampleRate));
		return ret;
	}
	
	static JSValue js_Wave_set_sampleRate(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Wave_class_id);
		Wave * ptr=(Wave  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].sampleRate=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Wave_get_sampleSize(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Wave_class_id);
		Wave * ptr=(Wave  *)shadow[0].ptr;
		unsigned int sampleSize=ptr[0].sampleSize;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)sampleSize));
		return ret;
	}
	
	static JSValue js_Wave_set_sampleSize(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Wave_class_id);
		Wave * ptr=(Wave  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].sampleSize=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Wave_get_channels(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Wave_class_id);
		Wave * ptr=(Wave  *)shadow[0].ptr;
		unsigned int channels=ptr[0].channels;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)channels));
		return ret;
	}
	
	static JSValue js_Wave_set_channels(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Wave_class_id);
		Wave * ptr=(Wave  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].channels=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Wave_data_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Wave * ptr=(Wave  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].frameCount*ptr[0].channels;i++){
			short src0=((short *)ptr[0].data)[i];
			JSValue ret1=JS_NewInt32(ctx,(int32_t)((long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Wave_data_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Wave * ptr=(Wave  *)ptr_u;
		int length=ptr[0].frameCount*ptr[0].channels;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Wave_data_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Wave * ptr=(Wave  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].frameCount*((long)ptr[0].channels));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].frameCount*ptr[0].channels){
				short * ptrcast=(short  *)ptr[0].data;
				short src=ptrcast[property];
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Wave_data_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Wave * ptr=(Wave  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].frameCount*ptr[0].channels){
				bool error=(bool)0;
				local_memlock=(bool)true;
				short ret=js_getshort(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				((short *)ptr[0].data)[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Wave_data_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Wave * ptr=(Wave  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].frameCount*ptr[0].channels){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Wave_get_data(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Wave_class_id);
		Wave * ptr=(Wave  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Wave_data_values,.keys = js_Wave_data_keys,.get = js_Wave_data_get,.set = js_Wave_data_set,.has = js_Wave_data_has});
		return ret;
	}
	
	static JSValue js_Wave_set_data(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Wave_class_id);
		Wave * ptr=(Wave  *)shadow[0].ptr;
		local_memlock=(bool)true;
		void * value=js_getvoid_arr(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].data!=NULL)jsc_free(ctx,ptr[0].data);
		ptr[0].data =value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Wave_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Wave", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("frameCount",js_Wave_get_frameCount,js_Wave_set_frameCount),
		JS_CGETSET_DEF("sampleRate",js_Wave_get_sampleRate,js_Wave_set_sampleRate),
		JS_CGETSET_DEF("sampleSize",js_Wave_get_sampleSize,js_Wave_set_sampleSize),
		JS_CGETSET_DEF("channels",js_Wave_get_channels,js_Wave_set_channels),
		JS_CGETSET_DEF("data",js_Wave_get_data,js_Wave_set_data)
	};
	
	static int js_declare_Wave(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Wave_class_id);
		JSClassDef js_Wave_def={ .class_name = "Wave", .finalizer = js_Wave_finalizer };
		JS_NewClass(rt,js_Wave_class_id,(const JSClassDef  *)&js_Wave_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Wave_proto_funcs,(int)countof(js_Wave_proto_funcs));
		JS_SetClassProto(ctx,js_Wave_class_id,proto);
		return 0;
	}
	
	static void js_rAudioBuffer_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_rAudioBuffer_class_id);
		deallocate_shadow(rt,shadow);
	}
	static const JSCFunctionListEntry js_rAudioBuffer_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","rAudioBuffer", JS_PROP_CONFIGURABLE)
	};
	
	static int js_declare_rAudioBuffer(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_rAudioBuffer_class_id);
		JSClassDef js_rAudioBuffer_def={ .class_name = "rAudioBuffer", .finalizer = js_rAudioBuffer_finalizer };
		JS_NewClass(rt,js_rAudioBuffer_class_id,(const JSClassDef  *)&js_rAudioBuffer_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_rAudioBuffer_proto_funcs,(int)countof(js_rAudioBuffer_proto_funcs));
		JS_SetClassProto(ctx,js_rAudioBuffer_class_id,proto);
		return 0;
	}
	
	static void js_rAudioProcessor_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_rAudioProcessor_class_id);
		deallocate_shadow(rt,shadow);
	}
	static const JSCFunctionListEntry js_rAudioProcessor_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","rAudioProcessor", JS_PROP_CONFIGURABLE)
	};
	
	static int js_declare_rAudioProcessor(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_rAudioProcessor_class_id);
		JSClassDef js_rAudioProcessor_def={ .class_name = "rAudioProcessor", .finalizer = js_rAudioProcessor_finalizer };
		JS_NewClass(rt,js_rAudioProcessor_class_id,(const JSClassDef  *)&js_rAudioProcessor_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_rAudioProcessor_proto_funcs,(int)countof(js_rAudioProcessor_proto_funcs));
		JS_SetClassProto(ctx,js_rAudioProcessor_class_id,proto);
		return 0;
	}
	
	static void js_AudioStream_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_AudioStream_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_AudioStream_get_sampleRate(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AudioStream_class_id);
		AudioStream * ptr=(AudioStream  *)shadow[0].ptr;
		unsigned int sampleRate=ptr[0].sampleRate;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)sampleRate));
		return ret;
	}
	
	static JSValue js_AudioStream_set_sampleRate(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AudioStream_class_id);
		AudioStream * ptr=(AudioStream  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].sampleRate=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_AudioStream_get_sampleSize(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AudioStream_class_id);
		AudioStream * ptr=(AudioStream  *)shadow[0].ptr;
		unsigned int sampleSize=ptr[0].sampleSize;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)sampleSize));
		return ret;
	}
	
	static JSValue js_AudioStream_set_sampleSize(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AudioStream_class_id);
		AudioStream * ptr=(AudioStream  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].sampleSize=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_AudioStream_get_channels(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AudioStream_class_id);
		AudioStream * ptr=(AudioStream  *)shadow[0].ptr;
		unsigned int channels=ptr[0].channels;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)channels));
		return ret;
	}
	
	static JSValue js_AudioStream_set_channels(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AudioStream_class_id);
		AudioStream * ptr=(AudioStream  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].channels=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_AudioStream_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","AudioStream", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("buffer",NULL,NULL),
		JS_CGETSET_DEF("processor",NULL,NULL),
		JS_CGETSET_DEF("sampleRate",js_AudioStream_get_sampleRate,js_AudioStream_set_sampleRate),
		JS_CGETSET_DEF("sampleSize",js_AudioStream_get_sampleSize,js_AudioStream_set_sampleSize),
		JS_CGETSET_DEF("channels",js_AudioStream_get_channels,js_AudioStream_set_channels)
	};
	
	static int js_declare_AudioStream(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_AudioStream_class_id);
		JSClassDef js_AudioStream_def={ .class_name = "AudioStream", .finalizer = js_AudioStream_finalizer };
		JS_NewClass(rt,js_AudioStream_class_id,(const JSClassDef  *)&js_AudioStream_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_AudioStream_proto_funcs,(int)countof(js_AudioStream_proto_funcs));
		JS_SetClassProto(ctx,js_AudioStream_class_id,proto);
		return 0;
	}
	
	static void js_Sound_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Sound_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Sound_get_stream(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Sound_class_id);
		Sound * ptr=(Sound  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		AudioStream * stream=&ptr[0].stream;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)stream,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_AudioStream_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Sound_set_stream(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Sound_class_id);
		Sound * ptr=(Sound  *)shadow[0].ptr;
		local_memlock=(bool)true;
		AudioStream value=js_getAudioStream(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].stream=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Sound_get_frameCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Sound_class_id);
		Sound * ptr=(Sound  *)shadow[0].ptr;
		unsigned int frameCount=ptr[0].frameCount;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)frameCount));
		return ret;
	}
	
	static JSValue js_Sound_set_frameCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Sound_class_id);
		Sound * ptr=(Sound  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].frameCount=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Sound_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Sound", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("stream",js_Sound_get_stream,js_Sound_set_stream),
		JS_CGETSET_DEF("frameCount",js_Sound_get_frameCount,js_Sound_set_frameCount)
	};
	
	static int js_declare_Sound(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Sound_class_id);
		JSClassDef js_Sound_def={ .class_name = "Sound", .finalizer = js_Sound_finalizer };
		JS_NewClass(rt,js_Sound_class_id,(const JSClassDef  *)&js_Sound_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Sound_proto_funcs,(int)countof(js_Sound_proto_funcs));
		JS_SetClassProto(ctx,js_Sound_class_id,proto);
		return 0;
	}
	
	static void js_Music_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Music_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Music_get_stream(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Music_class_id);
		Music * ptr=(Music  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		AudioStream * stream=&ptr[0].stream;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)stream,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_AudioStream_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Music_set_stream(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Music_class_id);
		Music * ptr=(Music  *)shadow[0].ptr;
		local_memlock=(bool)true;
		AudioStream value=js_getAudioStream(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].stream=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Music_get_frameCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Music_class_id);
		Music * ptr=(Music  *)shadow[0].ptr;
		unsigned int frameCount=ptr[0].frameCount;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)frameCount));
		return ret;
	}
	
	static JSValue js_Music_set_frameCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Music_class_id);
		Music * ptr=(Music  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].frameCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Music_get_looping(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Music_class_id);
		Music * ptr=(Music  *)shadow[0].ptr;
		bool looping=ptr[0].looping;
		JSValue ret=JS_NewBool(ctx,looping);
		return ret;
	}
	
	static JSValue js_Music_set_looping(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Music_class_id);
		Music * ptr=(Music  *)shadow[0].ptr;
		local_memlock=(bool)true;
		bool value=js_getbool(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].looping=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Music_get_ctxType(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Music_class_id);
		Music * ptr=(Music  *)shadow[0].ptr;
		int ctxType=ptr[0].ctxType;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ctxType));
		return ret;
	}
	
	static JSValue js_Music_set_ctxType(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Music_class_id);
		Music * ptr=(Music  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].ctxType=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Music_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Music", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("stream",js_Music_get_stream,js_Music_set_stream),
		JS_CGETSET_DEF("frameCount",js_Music_get_frameCount,js_Music_set_frameCount),
		JS_CGETSET_DEF("looping",js_Music_get_looping,js_Music_set_looping),
		JS_CGETSET_DEF("ctxType",js_Music_get_ctxType,js_Music_set_ctxType),
		JS_CGETSET_DEF("ctxData",NULL,NULL)
	};
	
	static int js_declare_Music(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Music_class_id);
		JSClassDef js_Music_def={ .class_name = "Music", .finalizer = js_Music_finalizer };
		JS_NewClass(rt,js_Music_class_id,(const JSClassDef  *)&js_Music_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Music_proto_funcs,(int)countof(js_Music_proto_funcs));
		JS_SetClassProto(ctx,js_Music_class_id,proto);
		return 0;
	}
	
	static void js_VrDeviceInfo_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_VrDeviceInfo_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_VrDeviceInfo_get_hResolution(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		int hResolution=ptr[0].hResolution;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)hResolution));
		return ret;
	}
	
	static JSValue js_VrDeviceInfo_set_hResolution(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].hResolution=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrDeviceInfo_get_vResolution(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		int vResolution=ptr[0].vResolution;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)vResolution));
		return ret;
	}
	
	static JSValue js_VrDeviceInfo_set_vResolution(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].vResolution=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrDeviceInfo_get_hScreenSize(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		float hScreenSize=ptr[0].hScreenSize;
		JSValue ret=JS_NewFloat64(ctx,((double)hScreenSize));
		return ret;
	}
	
	static JSValue js_VrDeviceInfo_set_hScreenSize(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].hScreenSize=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrDeviceInfo_get_vScreenSize(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		float vScreenSize=ptr[0].vScreenSize;
		JSValue ret=JS_NewFloat64(ctx,((double)vScreenSize));
		return ret;
	}
	
	static JSValue js_VrDeviceInfo_set_vScreenSize(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].vScreenSize=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrDeviceInfo_get_eyeToScreenDistance(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		float eyeToScreenDistance=ptr[0].eyeToScreenDistance;
		JSValue ret=JS_NewFloat64(ctx,((double)eyeToScreenDistance));
		return ret;
	}
	
	static JSValue js_VrDeviceInfo_set_eyeToScreenDistance(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].eyeToScreenDistance=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrDeviceInfo_get_lensSeparationDistance(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		float lensSeparationDistance=ptr[0].lensSeparationDistance;
		JSValue ret=JS_NewFloat64(ctx,((double)lensSeparationDistance));
		return ret;
	}
	
	static JSValue js_VrDeviceInfo_set_lensSeparationDistance(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].lensSeparationDistance=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrDeviceInfo_get_interpupillaryDistance(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		float interpupillaryDistance=ptr[0].interpupillaryDistance;
		JSValue ret=JS_NewFloat64(ctx,((double)interpupillaryDistance));
		return ret;
	}
	
	static JSValue js_VrDeviceInfo_set_interpupillaryDistance(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].interpupillaryDistance=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrDeviceInfo_lensDistortionValues_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrDeviceInfo * ptr=(VrDeviceInfo  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<4;i++){
			float src0=ptr[0].lensDistortionValues[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_VrDeviceInfo_lensDistortionValues_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		VrDeviceInfo * ptr=(VrDeviceInfo  *)ptr_u;
		int length=(int)4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_VrDeviceInfo_lensDistortionValues_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrDeviceInfo * ptr=(VrDeviceInfo  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<4){
				float src=ptr[0].lensDistortionValues[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_VrDeviceInfo_lensDistortionValues_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		VrDeviceInfo * ptr=(VrDeviceInfo  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<4){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].lensDistortionValues[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_VrDeviceInfo_lensDistortionValues_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		VrDeviceInfo * ptr=(VrDeviceInfo  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_VrDeviceInfo_get_lensDistortionValues(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_VrDeviceInfo_lensDistortionValues_values,.keys = js_VrDeviceInfo_lensDistortionValues_keys,.get = js_VrDeviceInfo_lensDistortionValues_get,.set = js_VrDeviceInfo_lensDistortionValues_set,.has = js_VrDeviceInfo_lensDistortionValues_has});
		return ret;
	}
	
	static JSValue js_VrDeviceInfo_set_lensDistortionValues(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arr4nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].lensDistortionValues,(const void  *)value,4*sizeof(float));
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrDeviceInfo_chromaAbCorrection_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrDeviceInfo * ptr=(VrDeviceInfo  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<4;i++){
			float src0=ptr[0].chromaAbCorrection[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_VrDeviceInfo_chromaAbCorrection_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		VrDeviceInfo * ptr=(VrDeviceInfo  *)ptr_u;
		int length=(int)4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_VrDeviceInfo_chromaAbCorrection_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrDeviceInfo * ptr=(VrDeviceInfo  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<4){
				float src=ptr[0].chromaAbCorrection[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_VrDeviceInfo_chromaAbCorrection_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		VrDeviceInfo * ptr=(VrDeviceInfo  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<4){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].chromaAbCorrection[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_VrDeviceInfo_chromaAbCorrection_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		VrDeviceInfo * ptr=(VrDeviceInfo  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_VrDeviceInfo_get_chromaAbCorrection(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_VrDeviceInfo_chromaAbCorrection_values,.keys = js_VrDeviceInfo_chromaAbCorrection_keys,.get = js_VrDeviceInfo_chromaAbCorrection_get,.set = js_VrDeviceInfo_chromaAbCorrection_set,.has = js_VrDeviceInfo_chromaAbCorrection_has});
		return ret;
	}
	
	static JSValue js_VrDeviceInfo_set_chromaAbCorrection(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrDeviceInfo_class_id);
		VrDeviceInfo * ptr=(VrDeviceInfo  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arr4nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].chromaAbCorrection,(const void  *)value,4*sizeof(float));
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_VrDeviceInfo_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","VrDeviceInfo", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("hResolution",js_VrDeviceInfo_get_hResolution,js_VrDeviceInfo_set_hResolution),
		JS_CGETSET_DEF("vResolution",js_VrDeviceInfo_get_vResolution,js_VrDeviceInfo_set_vResolution),
		JS_CGETSET_DEF("hScreenSize",js_VrDeviceInfo_get_hScreenSize,js_VrDeviceInfo_set_hScreenSize),
		JS_CGETSET_DEF("vScreenSize",js_VrDeviceInfo_get_vScreenSize,js_VrDeviceInfo_set_vScreenSize),
		JS_CGETSET_DEF("eyeToScreenDistance",js_VrDeviceInfo_get_eyeToScreenDistance,js_VrDeviceInfo_set_eyeToScreenDistance),
		JS_CGETSET_DEF("lensSeparationDistance",js_VrDeviceInfo_get_lensSeparationDistance,js_VrDeviceInfo_set_lensSeparationDistance),
		JS_CGETSET_DEF("interpupillaryDistance",js_VrDeviceInfo_get_interpupillaryDistance,js_VrDeviceInfo_set_interpupillaryDistance),
		JS_CGETSET_DEF("lensDistortionValues",js_VrDeviceInfo_get_lensDistortionValues,js_VrDeviceInfo_set_lensDistortionValues),
		JS_CGETSET_DEF("chromaAbCorrection",js_VrDeviceInfo_get_chromaAbCorrection,js_VrDeviceInfo_set_chromaAbCorrection)
	};
	
	static int js_declare_VrDeviceInfo(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_VrDeviceInfo_class_id);
		JSClassDef js_VrDeviceInfo_def={ .class_name = "VrDeviceInfo", .finalizer = js_VrDeviceInfo_finalizer };
		JS_NewClass(rt,js_VrDeviceInfo_class_id,(const JSClassDef  *)&js_VrDeviceInfo_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_VrDeviceInfo_proto_funcs,(int)countof(js_VrDeviceInfo_proto_funcs));
		JS_SetClassProto(ctx,js_VrDeviceInfo_class_id,proto);
		return 0;
	}
	
	static void js_VrStereoConfig_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_VrStereoConfig_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_VrStereoConfig_projection_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<2;i++){
			Matrix * src0=(ptr[0].projection+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_Matrix_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_VrStereoConfig_projection_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		int length=(int)2;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_VrStereoConfig_projection_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)2));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<2){
				Matrix * src=(ptr[0].projection+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_VrStereoConfig_projection_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<2){
				bool error=(bool)0;
				local_memlock=(bool)true;
				Matrix ret=js_getMatrix(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].projection[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_VrStereoConfig_projection_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<2){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_VrStereoConfig_get_projection(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_VrStereoConfig_projection_values,.keys = js_VrStereoConfig_projection_keys,.get = js_VrStereoConfig_projection_get,.set = js_VrStereoConfig_projection_set,.has = js_VrStereoConfig_projection_has});
		return ret;
	}
	
	static JSValue js_VrStereoConfig_set_projection(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Matrix * value=js_getMatrix_arr2nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].projection,(const void  *)value,2*sizeof(Matrix));
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrStereoConfig_viewOffset_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<2;i++){
			Matrix * src0=(ptr[0].viewOffset+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_Matrix_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_VrStereoConfig_viewOffset_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		int length=(int)2;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_VrStereoConfig_viewOffset_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)2));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<2){
				Matrix * src=(ptr[0].viewOffset+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_VrStereoConfig_viewOffset_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<2){
				bool error=(bool)0;
				local_memlock=(bool)true;
				Matrix ret=js_getMatrix(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].viewOffset[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_VrStereoConfig_viewOffset_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<2){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_VrStereoConfig_get_viewOffset(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_VrStereoConfig_viewOffset_values,.keys = js_VrStereoConfig_viewOffset_keys,.get = js_VrStereoConfig_viewOffset_get,.set = js_VrStereoConfig_viewOffset_set,.has = js_VrStereoConfig_viewOffset_has});
		return ret;
	}
	
	static JSValue js_VrStereoConfig_set_viewOffset(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Matrix * value=js_getMatrix_arr2nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].viewOffset,(const void  *)value,2*sizeof(Matrix));
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrStereoConfig_leftLensCenter_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<2;i++){
			float src0=ptr[0].leftLensCenter[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_VrStereoConfig_leftLensCenter_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		int length=(int)2;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_VrStereoConfig_leftLensCenter_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)2));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<2){
				float src=ptr[0].leftLensCenter[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_VrStereoConfig_leftLensCenter_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<2){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].leftLensCenter[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_VrStereoConfig_leftLensCenter_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<2){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_VrStereoConfig_get_leftLensCenter(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_VrStereoConfig_leftLensCenter_values,.keys = js_VrStereoConfig_leftLensCenter_keys,.get = js_VrStereoConfig_leftLensCenter_get,.set = js_VrStereoConfig_leftLensCenter_set,.has = js_VrStereoConfig_leftLensCenter_has});
		return ret;
	}
	
	static JSValue js_VrStereoConfig_set_leftLensCenter(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arr2nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].leftLensCenter,(const void  *)value,2*sizeof(float));
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrStereoConfig_rightLensCenter_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<2;i++){
			float src0=ptr[0].rightLensCenter[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_VrStereoConfig_rightLensCenter_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		int length=(int)2;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_VrStereoConfig_rightLensCenter_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)2));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<2){
				float src=ptr[0].rightLensCenter[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_VrStereoConfig_rightLensCenter_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<2){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].rightLensCenter[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_VrStereoConfig_rightLensCenter_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<2){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_VrStereoConfig_get_rightLensCenter(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_VrStereoConfig_rightLensCenter_values,.keys = js_VrStereoConfig_rightLensCenter_keys,.get = js_VrStereoConfig_rightLensCenter_get,.set = js_VrStereoConfig_rightLensCenter_set,.has = js_VrStereoConfig_rightLensCenter_has});
		return ret;
	}
	
	static JSValue js_VrStereoConfig_set_rightLensCenter(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arr2nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].rightLensCenter,(const void  *)value,2*sizeof(float));
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrStereoConfig_leftScreenCenter_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<2;i++){
			float src0=ptr[0].leftScreenCenter[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_VrStereoConfig_leftScreenCenter_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		int length=(int)2;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_VrStereoConfig_leftScreenCenter_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)2));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<2){
				float src=ptr[0].leftScreenCenter[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_VrStereoConfig_leftScreenCenter_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<2){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].leftScreenCenter[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_VrStereoConfig_leftScreenCenter_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<2){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_VrStereoConfig_get_leftScreenCenter(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_VrStereoConfig_leftScreenCenter_values,.keys = js_VrStereoConfig_leftScreenCenter_keys,.get = js_VrStereoConfig_leftScreenCenter_get,.set = js_VrStereoConfig_leftScreenCenter_set,.has = js_VrStereoConfig_leftScreenCenter_has});
		return ret;
	}
	
	static JSValue js_VrStereoConfig_set_leftScreenCenter(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arr2nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].leftScreenCenter,(const void  *)value,2*sizeof(float));
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrStereoConfig_rightScreenCenter_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<2;i++){
			float src0=ptr[0].rightScreenCenter[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_VrStereoConfig_rightScreenCenter_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		int length=(int)2;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_VrStereoConfig_rightScreenCenter_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)2));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<2){
				float src=ptr[0].rightScreenCenter[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_VrStereoConfig_rightScreenCenter_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<2){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].rightScreenCenter[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_VrStereoConfig_rightScreenCenter_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<2){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_VrStereoConfig_get_rightScreenCenter(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_VrStereoConfig_rightScreenCenter_values,.keys = js_VrStereoConfig_rightScreenCenter_keys,.get = js_VrStereoConfig_rightScreenCenter_get,.set = js_VrStereoConfig_rightScreenCenter_set,.has = js_VrStereoConfig_rightScreenCenter_has});
		return ret;
	}
	
	static JSValue js_VrStereoConfig_set_rightScreenCenter(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arr2nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].rightScreenCenter,(const void  *)value,2*sizeof(float));
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrStereoConfig_scale_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<2;i++){
			float src0=ptr[0].scale[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_VrStereoConfig_scale_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		int length=(int)2;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_VrStereoConfig_scale_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)2));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<2){
				float src=ptr[0].scale[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_VrStereoConfig_scale_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<2){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].scale[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_VrStereoConfig_scale_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<2){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_VrStereoConfig_get_scale(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_VrStereoConfig_scale_values,.keys = js_VrStereoConfig_scale_keys,.get = js_VrStereoConfig_scale_get,.set = js_VrStereoConfig_scale_set,.has = js_VrStereoConfig_scale_has});
		return ret;
	}
	
	static JSValue js_VrStereoConfig_set_scale(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arr2nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].scale,(const void  *)value,2*sizeof(float));
		return JS_UNDEFINED;
	}
	
	static JSValue js_VrStereoConfig_scaleIn_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<2;i++){
			float src0=ptr[0].scaleIn[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_VrStereoConfig_scaleIn_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		int length=(int)2;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_VrStereoConfig_scaleIn_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)2));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<2){
				float src=ptr[0].scaleIn[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_VrStereoConfig_scaleIn_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<2){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].scaleIn[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_VrStereoConfig_scaleIn_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		VrStereoConfig * ptr=(VrStereoConfig  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<2){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_VrStereoConfig_get_scaleIn(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_VrStereoConfig_scaleIn_values,.keys = js_VrStereoConfig_scaleIn_keys,.get = js_VrStereoConfig_scaleIn_get,.set = js_VrStereoConfig_scaleIn_set,.has = js_VrStereoConfig_scaleIn_has});
		return ret;
	}
	
	static JSValue js_VrStereoConfig_set_scaleIn(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_VrStereoConfig_class_id);
		VrStereoConfig * ptr=(VrStereoConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arr2nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].scaleIn,(const void  *)value,2*sizeof(float));
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_VrStereoConfig_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","VrStereoConfig", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("projection",js_VrStereoConfig_get_projection,js_VrStereoConfig_set_projection),
		JS_CGETSET_DEF("viewOffset",js_VrStereoConfig_get_viewOffset,js_VrStereoConfig_set_viewOffset),
		JS_CGETSET_DEF("leftLensCenter",js_VrStereoConfig_get_leftLensCenter,js_VrStereoConfig_set_leftLensCenter),
		JS_CGETSET_DEF("rightLensCenter",js_VrStereoConfig_get_rightLensCenter,js_VrStereoConfig_set_rightLensCenter),
		JS_CGETSET_DEF("leftScreenCenter",js_VrStereoConfig_get_leftScreenCenter,js_VrStereoConfig_set_leftScreenCenter),
		JS_CGETSET_DEF("rightScreenCenter",js_VrStereoConfig_get_rightScreenCenter,js_VrStereoConfig_set_rightScreenCenter),
		JS_CGETSET_DEF("scale",js_VrStereoConfig_get_scale,js_VrStereoConfig_set_scale),
		JS_CGETSET_DEF("scaleIn",js_VrStereoConfig_get_scaleIn,js_VrStereoConfig_set_scaleIn)
	};
	
	static int js_declare_VrStereoConfig(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_VrStereoConfig_class_id);
		JSClassDef js_VrStereoConfig_def={ .class_name = "VrStereoConfig", .finalizer = js_VrStereoConfig_finalizer };
		JS_NewClass(rt,js_VrStereoConfig_class_id,(const JSClassDef  *)&js_VrStereoConfig_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_VrStereoConfig_proto_funcs,(int)countof(js_VrStereoConfig_proto_funcs));
		JS_SetClassProto(ctx,js_VrStereoConfig_class_id,proto);
		return 0;
	}
	
	static void js_FilePathList_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_FilePathList_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_FilePathList_get_capacity(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_FilePathList_class_id);
		FilePathList * ptr=(FilePathList  *)shadow[0].ptr;
		unsigned int capacity=ptr[0].capacity;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)capacity));
		return ret;
	}
	
	static JSValue js_FilePathList_set_capacity(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_FilePathList_class_id);
		FilePathList * ptr=(FilePathList  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].capacity=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_FilePathList_get_count(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_FilePathList_class_id);
		FilePathList * ptr=(FilePathList  *)shadow[0].ptr;
		unsigned int count=ptr[0].count;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)count));
		return ret;
	}
	
	static JSValue js_FilePathList_set_count(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_FilePathList_class_id);
		FilePathList * ptr=(FilePathList  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].count=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_FilePathList_paths_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		FilePathList * ptr=(FilePathList  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].count;i++){
			char * src0=ptr[0].paths[i];
			JSValue ret1=JS_NewString(ctx,(const char  *)src0);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_FilePathList_paths_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		FilePathList * ptr=(FilePathList  *)ptr_u;
		int length=(int)ptr[0].count;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_FilePathList_paths_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		FilePathList * ptr=(FilePathList  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].count));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].count){
				char * src=ptr[0].paths[property];
				JSValue ret=JS_NewString(ctx,(const char  *)src);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_FilePathList_paths_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		FilePathList * ptr=(FilePathList  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].count){
				bool error=(bool)0;
				local_memlock=(bool)true;
				char * ret=js_getchar_arr(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].paths[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_FilePathList_paths_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		FilePathList * ptr=(FilePathList  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].count){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_FilePathList_get_paths(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_FilePathList_class_id);
		FilePathList * ptr=(FilePathList  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_FilePathList_paths_values,.keys = js_FilePathList_paths_keys,.get = js_FilePathList_paths_get,.set = js_FilePathList_paths_set,.has = js_FilePathList_paths_has});
		return ret;
	}
	
	static JSValue js_FilePathList_set_paths(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_FilePathList_class_id);
		FilePathList * ptr=(FilePathList  *)shadow[0].ptr;
		memoryNode * memoryHead=(memoryNode  *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		local_memlock=(bool)true;
		char * * value=js_getchar_arr_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].paths!=NULL)jsc_free(ctx,(void  *)*ptr[0].paths);
		ptr[0].paths =value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_FilePathList_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","FilePathList", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("capacity",js_FilePathList_get_capacity,js_FilePathList_set_capacity),
		JS_CGETSET_DEF("count",js_FilePathList_get_count,js_FilePathList_set_count),
		JS_CGETSET_DEF("paths",js_FilePathList_get_paths,js_FilePathList_set_paths)
	};
	
	static int js_declare_FilePathList(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_FilePathList_class_id);
		JSClassDef js_FilePathList_def={ .class_name = "FilePathList", .finalizer = js_FilePathList_finalizer };
		JS_NewClass(rt,js_FilePathList_class_id,(const JSClassDef  *)&js_FilePathList_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_FilePathList_proto_funcs,(int)countof(js_FilePathList_proto_funcs));
		JS_SetClassProto(ctx,js_FilePathList_class_id,proto);
		return 0;
	}
	
	static void js_AutomationEvent_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_AutomationEvent_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_AutomationEvent_get_frame(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEvent_class_id);
		AutomationEvent * ptr=(AutomationEvent  *)shadow[0].ptr;
		unsigned int frame=ptr[0].frame;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)frame));
		return ret;
	}
	
	static JSValue js_AutomationEvent_set_frame(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEvent_class_id);
		AutomationEvent * ptr=(AutomationEvent  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].frame=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_AutomationEvent_get_type(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEvent_class_id);
		AutomationEvent * ptr=(AutomationEvent  *)shadow[0].ptr;
		unsigned int type=ptr[0].type;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)type));
		return ret;
	}
	
	static JSValue js_AutomationEvent_set_type(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEvent_class_id);
		AutomationEvent * ptr=(AutomationEvent  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].type=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_AutomationEvent_params_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		AutomationEvent * ptr=(AutomationEvent  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<4;i++){
			int src0=ptr[0].params[i];
			JSValue ret1=JS_NewInt32(ctx,(int32_t)((long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_AutomationEvent_params_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		AutomationEvent * ptr=(AutomationEvent  *)ptr_u;
		int length=(int)4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_AutomationEvent_params_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		AutomationEvent * ptr=(AutomationEvent  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<4){
				int src=ptr[0].params[property];
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_AutomationEvent_params_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		AutomationEvent * ptr=(AutomationEvent  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<4){
				bool error=(bool)0;
				local_memlock=(bool)true;
				int ret=js_getint(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].params[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_AutomationEvent_params_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		AutomationEvent * ptr=(AutomationEvent  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_AutomationEvent_get_params(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEvent_class_id);
		AutomationEvent * ptr=(AutomationEvent  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_AutomationEvent_params_values,.keys = js_AutomationEvent_params_keys,.get = js_AutomationEvent_params_get,.set = js_AutomationEvent_params_set,.has = js_AutomationEvent_params_has});
		return ret;
	}
	
	static JSValue js_AutomationEvent_set_params(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEvent_class_id);
		AutomationEvent * ptr=(AutomationEvent  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int * value=js_getint_arr4nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].params,(const void  *)value,4*sizeof(int));
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_AutomationEvent_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","AutomationEvent", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("frame",js_AutomationEvent_get_frame,js_AutomationEvent_set_frame),
		JS_CGETSET_DEF("type",js_AutomationEvent_get_type,js_AutomationEvent_set_type),
		JS_CGETSET_DEF("params",js_AutomationEvent_get_params,js_AutomationEvent_set_params)
	};
	
	static int js_declare_AutomationEvent(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_AutomationEvent_class_id);
		JSClassDef js_AutomationEvent_def={ .class_name = "AutomationEvent", .finalizer = js_AutomationEvent_finalizer };
		JS_NewClass(rt,js_AutomationEvent_class_id,(const JSClassDef  *)&js_AutomationEvent_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_AutomationEvent_proto_funcs,(int)countof(js_AutomationEvent_proto_funcs));
		JS_SetClassProto(ctx,js_AutomationEvent_class_id,proto);
		return 0;
	}
	
	static void js_AutomationEventList_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_AutomationEventList_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_AutomationEventList_get_capacity(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEventList_class_id);
		AutomationEventList * ptr=(AutomationEventList  *)shadow[0].ptr;
		unsigned int capacity=ptr[0].capacity;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)capacity));
		return ret;
	}
	
	static JSValue js_AutomationEventList_set_capacity(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEventList_class_id);
		AutomationEventList * ptr=(AutomationEventList  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].capacity=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_AutomationEventList_get_count(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEventList_class_id);
		AutomationEventList * ptr=(AutomationEventList  *)shadow[0].ptr;
		unsigned int count=ptr[0].count;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)count));
		return ret;
	}
	
	static JSValue js_AutomationEventList_set_count(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEventList_class_id);
		AutomationEventList * ptr=(AutomationEventList  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].count=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_AutomationEventList_events_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		AutomationEventList * ptr=(AutomationEventList  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].count;i++){
			AutomationEvent * src0=(ptr[0].events+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_AutomationEvent_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_AutomationEventList_events_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		AutomationEventList * ptr=(AutomationEventList  *)ptr_u;
		int length=(int)ptr[0].count;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_AutomationEventList_events_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		AutomationEventList * ptr=(AutomationEventList  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].count));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].count){
				AutomationEvent * src=(ptr[0].events+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_AutomationEvent_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_AutomationEventList_events_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		AutomationEventList * ptr=(AutomationEventList  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].count){
				bool error=(bool)0;
				local_memlock=(bool)true;
				AutomationEvent ret=js_getAutomationEvent(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].events[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_AutomationEventList_events_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		AutomationEventList * ptr=(AutomationEventList  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].count){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_AutomationEventList_get_events(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEventList_class_id);
		AutomationEventList * ptr=(AutomationEventList  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_AutomationEventList_events_values,.keys = js_AutomationEventList_events_keys,.get = js_AutomationEventList_events_get,.set = js_AutomationEventList_events_set,.has = js_AutomationEventList_events_has});
		return ret;
	}
	
	static JSValue js_AutomationEventList_set_events(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_AutomationEventList_class_id);
		AutomationEventList * ptr=(AutomationEventList  *)shadow[0].ptr;
		local_memlock=(bool)true;
		AutomationEvent * value=js_getAutomationEvent_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].events!=NULL)jsc_free(ctx,(void  *)ptr[0].events);
		ptr[0].events =value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_AutomationEventList_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","AutomationEventList", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("capacity",js_AutomationEventList_get_capacity,js_AutomationEventList_set_capacity),
		JS_CGETSET_DEF("count",js_AutomationEventList_get_count,js_AutomationEventList_set_count),
		JS_CGETSET_DEF("events",js_AutomationEventList_get_events,js_AutomationEventList_set_events)
	};
	
	static int js_declare_AutomationEventList(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_AutomationEventList_class_id);
		JSClassDef js_AutomationEventList_def={ .class_name = "AutomationEventList", .finalizer = js_AutomationEventList_finalizer };
		JS_NewClass(rt,js_AutomationEventList_class_id,(const JSClassDef  *)&js_AutomationEventList_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_AutomationEventList_proto_funcs,(int)countof(js_AutomationEventList_proto_funcs));
		JS_SetClassProto(ctx,js_AutomationEventList_class_id,proto);
		return 0;
	}
	static trampolineContext * LoadFileDataCallback_arr=NULL;
	
	static unsigned char * callback_LoadFileDataCallback(const char * fileName,int dataSize[1]){
		JSValue func1;
		bool error=(bool)0;
		trampolineContext tctx=*LoadFileDataCallback_arr;
		JSContext * ctx=tctx.ctx;
		JSValue js0=JS_NewString(ctx,fileName);
		JSValue js1=JS_NewArray(ctx);
		int * sizeref_js1=dataSize;
		size_t size_js1=sizeof(sizeref_js1);
		size_t size1_js1=sizeof(int);
		size_js1 =size_js1/size1_js1;
		for(int i=0;i<size_js1;i++){
			JSValue js_js1=JS_NewInt32(ctx,(int32_t)((long)dataSize[i]));
			JS_DefinePropertyValueUint32(ctx,js1,(uint32_t)i,js_js1,JS_PROP_C_W_E);
		}
		JSValue argv[2]={
			js0,
			js1
		};
		JS_DupContext(ctx);
		JS_DupValue(ctx,tctx.func_obj);
		JSValue js_ret=JS_Call(ctx,tctx.func_obj,JS_UNDEFINED,(int)2,argv);
		JS_FreeValue(ctx,tctx.func_obj);
		JS_FreeContext(ctx);
		JS_FreeValue(ctx,argv[0]);
		local_memlock=(bool)true;
		bool dataSize_isptr=(bool)false;
		dataSize =js_getint_ptr(ctx,js0,&error,&dataSize_isptr);
		if(error==1)return NULL;
		local_memlock=(bool)false;
		unsigned char * resp=js_getunsignedchar_arr(ctx,js_ret,&error);
		if(error==1)return NULL;
		JS_FreeValue(ctx,js_ret);
		JS_FreeValue(ctx,argv[1]);
		return resp;
	}
	static trampolineContext * SaveFileDataCallback_arr=NULL;
	
	static bool callback_SaveFileDataCallback(const char * fileName,unsigned char * data,int dataSize){
		JSValue func1;
		bool error=(bool)0;
		trampolineContext tctx=*SaveFileDataCallback_arr;
		JSContext * ctx=tctx.ctx;
		JSValue js0=JS_NewString(ctx,fileName);
		JSValue js1=JS_NewArray(ctx);
		for(int i=0;i<dataSize;i++){
			JSValue js_js1=JS_NewUint32(ctx,(uint32_t)((unsigned long)data[i]));
			JS_DefinePropertyValueUint32(ctx,js1,(uint32_t)i,js_js1,JS_PROP_C_W_E);
		}
		JSValue js2=JS_NewInt32(ctx,(int32_t)((long)dataSize));
		JSValue argv[3]={
			js0,
			js1,
			js2
		};
		JS_DupContext(ctx);
		JS_DupValue(ctx,tctx.func_obj);
		JSValue js_ret=JS_Call(ctx,tctx.func_obj,JS_UNDEFINED,(int)3,argv);
		JS_FreeValue(ctx,tctx.func_obj);
		JS_FreeContext(ctx);
		JS_FreeValue(ctx,argv[0]);
		JS_FreeValue(ctx,argv[1]);
		JS_FreeValue(ctx,argv[2]);
		bool resp=js_getbool(ctx,js_ret,&error);
		if(error==1)return false;
		JS_FreeValue(ctx,js_ret);
		return resp;
	}
	static trampolineContext * LoadFileTextCallback_arr=NULL;
	
	static char * callback_LoadFileTextCallback(const char * fileName){
		JSValue func1;
		bool error=(bool)0;
		trampolineContext tctx=*LoadFileTextCallback_arr;
		JSContext * ctx=tctx.ctx;
		JSValue js0=JS_NewString(ctx,fileName);
		JSValue argv[1]={
			js0
		};
		JS_DupContext(ctx);
		JS_DupValue(ctx,tctx.func_obj);
		JSValue js_ret=JS_Call(ctx,tctx.func_obj,JS_UNDEFINED,(int)1,argv);
		JS_FreeValue(ctx,tctx.func_obj);
		JS_FreeContext(ctx);
		JS_FreeValue(ctx,argv[0]);
		char * resp=js_getchar_arr(ctx,js_ret,&error);
		if(error==1)return NULL;
		JS_FreeValue(ctx,js_ret);
		return resp;
	}
	static trampolineContext * SaveFileTextCallback_arr=NULL;
	
	static bool callback_SaveFileTextCallback(const char * fileName,const char * text){
		JSValue func1;
		bool error=(bool)0;
		trampolineContext tctx=*SaveFileTextCallback_arr;
		JSContext * ctx=tctx.ctx;
		JSValue js0=JS_NewString(ctx,fileName);
		JSValue js1=JS_NewString(ctx,text);
		JSValue argv[2]={
			js0,
			js1
		};
		JS_DupContext(ctx);
		JS_DupValue(ctx,tctx.func_obj);
		JSValue js_ret=JS_Call(ctx,tctx.func_obj,JS_UNDEFINED,(int)2,argv);
		JS_FreeValue(ctx,tctx.func_obj);
		JS_FreeContext(ctx);
		JS_FreeValue(ctx,argv[0]);
		JS_FreeValue(ctx,argv[1]);
		bool resp=js_getbool(ctx,js_ret,&error);
		if(error==1)return false;
		JS_FreeValue(ctx,js_ret);
		return resp;
	}
	static trampolineContext * AudioStreamCallback_arr=NULL;
	static JSContext * AudioStreamCallback_ctx=NULL;
	
	static void callback_AudioStreamCallback(float * bufferData,unsigned int frames){
		JSValue func1;
		bool error=(bool)0;
		trampolineContext tctx=*AudioStreamCallback_arr;
		JSContext * ctx=AudioStreamCallback_ctx;
		JSValue js0=JS_NewArray(ctx);
		for(int i=0;i<frames*2;i++){
			JSValue js_js0=JS_NewFloat64(ctx,((double)bufferData[i]));
			JS_DefinePropertyValueUint32(ctx,js0,(uint32_t)i,js_js0,JS_PROP_C_W_E);
		}
		JSValue js1=JS_NewUint32(ctx,(uint32_t)((unsigned long)frames));
		JSValue argv[3]={
			tctx.func_obj,
			js0,
			js1
		};
		JSValue js_ret=js_postMessage(ctx,tctx.thread_id,(int)3,argv);
		JS_FreeValue(ctx,argv[1]);
		JS_FreeValue(ctx,argv[2]);
		JS_FreeValue(ctx,js_ret);
	}
	static trampolineContext * AudioCallback_arr=NULL;
	static JSContext * AudioCallback_ctx=NULL;
	static size_t AudioCallback_size=(size_t)0;
	
	static void callback_AudioCallback(float * bufferData,unsigned int frames){
		JSValue func1;
		for(int i=0;i<AudioCallback_size;i++){
			bool error=(bool)0;
			trampolineContext tctx=AudioCallback_arr[i];
			JSContext * ctx=AudioCallback_ctx;
			JSValue js0=JS_NewArray(ctx);
			float * sizeref_js0=bufferData;
			size_t size_js0=sizeof(sizeref_js0);
			size_t size1_js0=sizeof(float);
			size_js0 =size_js0/size1_js0;
			for(int i0=0;i0<size_js0;i0++){
				JSValue js_js0=JS_NewFloat64(ctx,((double)bufferData[i0]));
				JS_DefinePropertyValueUint32(ctx,js0,(uint32_t)i0,js_js0,JS_PROP_C_W_E);
			}
			JSValue js1=JS_NewUint32(ctx,(uint32_t)((unsigned long)frames));
			JSValue argv[3]={
				tctx.func_obj,
				js0,
				js1
			};
			JSValue js_ret=js_postMessage(ctx,tctx.thread_id,(int)3,argv);
			JS_FreeValue(ctx,argv[1]);
			JS_FreeValue(ctx,argv[2]);
			if(i==AudioCallback_size-1)JS_FreeValue(ctx,js_ret);
		}
	}
	static trampolineContext * AudioMixedProcessor_arr=NULL;
	static JSContext * AudioMixedProcessor_ctx=NULL;
	static size_t AudioMixedProcessor_size=(size_t)0;
	
	static void callback_AudioMixedProcessor(float * bufferData,unsigned int frames){
		JSValue func1;
		for(int i=0;i<AudioMixedProcessor_size;i++){
			bool error=(bool)0;
			trampolineContext tctx=AudioMixedProcessor_arr[i];
			JSContext * ctx=AudioMixedProcessor_ctx;
			JSValue js0=JS_NewArray(ctx);
			for(int i0=0;i0<frames*2;i0++){
				JSValue js_js0=JS_NewFloat64(ctx,((double)bufferData[i0]));
				JS_DefinePropertyValueUint32(ctx,js0,(uint32_t)i0,js_js0,JS_PROP_C_W_E);
			}
			JSValue js1=JS_NewUint32(ctx,(uint32_t)((unsigned long)frames));
			JSValue argv[3]={
				tctx.func_obj,
				js0,
				js1
			};
			JSValue js_ret=js_postMessage(ctx,tctx.thread_id,(int)3,argv);
			JS_FreeValue(ctx,argv[1]);
			JS_FreeValue(ctx,argv[2]);
			if(i==AudioMixedProcessor_size-1)JS_FreeValue(ctx,js_ret);
		}
	}
	
	static JSValue js_Vector2_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Vector2));
			JSValue _return=JS_NewObjectClass(ctx,js_Vector2_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Vector2 _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Vector2_class_id){
			Vector2 ptr=js_getVector2(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			float x=js_getfloat(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			float y=js_getfloat(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Vector2){
				x,
				y
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Vector2));
		Vector2 * _returnptr=((Vector2 *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Vector3_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Vector3));
			JSValue _return=JS_NewObjectClass(ctx,js_Vector3_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Vector3 _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Vector3_class_id){
			Vector3 ptr=js_getVector3(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			float x=js_getfloat(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			float y=js_getfloat(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float z=js_getfloat(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Vector3){
				x,
				y,
				z
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Vector3));
		Vector3 * _returnptr=((Vector3 *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Vector4_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Vector4));
			JSValue _return=JS_NewObjectClass(ctx,js_Vector4_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Vector4 _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Vector4_class_id){
			Vector4 ptr=js_getVector4(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			float x=js_getfloat(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			float y=js_getfloat(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float z=js_getfloat(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			float w=js_getfloat(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Vector4){
				x,
				y,
				z,
				w
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Vector4));
		Vector4 * _returnptr=((Vector4 *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Vector4_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Matrix_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Matrix));
			JSValue _return=JS_NewObjectClass(ctx,js_Matrix_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Matrix _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Matrix_class_id){
			Matrix ptr=js_getMatrix(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			float m0=js_getfloat(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			float m4=js_getfloat(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float m8=js_getfloat(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			float m12=js_getfloat(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			float m1=js_getfloat(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			float m5=js_getfloat(ctx,argv[5],&error);
			if(error==1)return JS_EXCEPTION;
			float m9=js_getfloat(ctx,argv[6],&error);
			if(error==1)return JS_EXCEPTION;
			float m13=js_getfloat(ctx,argv[7],&error);
			if(error==1)return JS_EXCEPTION;
			float m2=js_getfloat(ctx,argv[8],&error);
			if(error==1)return JS_EXCEPTION;
			float m6=js_getfloat(ctx,argv[9],&error);
			if(error==1)return JS_EXCEPTION;
			float m10=js_getfloat(ctx,argv[10],&error);
			if(error==1)return JS_EXCEPTION;
			float m14=js_getfloat(ctx,argv[11],&error);
			if(error==1)return JS_EXCEPTION;
			float m3=js_getfloat(ctx,argv[12],&error);
			if(error==1)return JS_EXCEPTION;
			float m7=js_getfloat(ctx,argv[13],&error);
			if(error==1)return JS_EXCEPTION;
			float m11=js_getfloat(ctx,argv[14],&error);
			if(error==1)return JS_EXCEPTION;
			float m15=js_getfloat(ctx,argv[15],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Matrix){
				m0,
				m4,
				m8,
				m12,
				m1,
				m5,
				m9,
				m13,
				m2,
				m6,
				m10,
				m14,
				m3,
				m7,
				m11,
				m15
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Matrix));
		Matrix * _returnptr=((Matrix *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Matrix_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Color_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Color));
			JSValue _return=JS_NewObjectClass(ctx,js_Color_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Color _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Color_class_id){
			Color ptr=js_getColor(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			unsigned char r=js_getunsignedchar(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned char g=js_getunsignedchar(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned char b=js_getunsignedchar(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned char a=js_getunsignedchar(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Color){
				r,
				g,
				b,
				a
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Color));
		Color * _returnptr=((Color *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Rectangle_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Rectangle));
			JSValue _return=JS_NewObjectClass(ctx,js_Rectangle_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Rectangle _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Rectangle_class_id){
			Rectangle ptr=js_getRectangle(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			float x=js_getfloat(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			float y=js_getfloat(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float width=js_getfloat(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			float height=js_getfloat(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Rectangle){
				x,
				y,
				width,
				height
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Rectangle));
		Rectangle * _returnptr=((Rectangle *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Rectangle_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Image_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Image));
			JSValue _return=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Image _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Image_class_id){
			Image ptr=js_getImage(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ImageCopy(ptr);
		}else{
			void * data=js_getvoid_arr(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int width=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			int height=js_getint(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			int mipmaps=js_getint(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			int format=js_getint(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Image){
				data,
				width,
				height,
				mipmaps,
				format
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Image));
		Image * _returnptr=((Image *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Texture_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Texture));
			JSValue _return=JS_NewObjectClass(ctx,js_Texture_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Texture _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Texture_class_id){
			Texture ptr=js_getTexture(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			unsigned int id=js_getunsignedint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int width=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			int height=js_getint(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			int mipmaps=js_getint(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			int format=js_getint(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Texture){
				id,
				width,
				height,
				mipmaps,
				format
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Texture));
		Texture * _returnptr=((Texture *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Texture_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_RenderTexture_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(RenderTexture));
			JSValue _return=JS_NewObjectClass(ctx,js_RenderTexture_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		RenderTexture _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_RenderTexture_class_id){
			RenderTexture ptr=js_getRenderTexture(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			unsigned int id=js_getunsignedint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			Texture texture=js_getTexture(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			Texture depth=js_getTexture(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(RenderTexture){
				id,
				texture,
				depth
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(RenderTexture));
		RenderTexture * _returnptr=((RenderTexture *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_RenderTexture_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_NPatchInfo_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(NPatchInfo));
			JSValue _return=JS_NewObjectClass(ctx,js_NPatchInfo_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		NPatchInfo _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_NPatchInfo_class_id){
			NPatchInfo ptr=js_getNPatchInfo(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			Rectangle source=js_getRectangle(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int left=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			int top=js_getint(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			int right=js_getint(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			int bottom=js_getint(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			int layout=js_getint(ctx,argv[5],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(NPatchInfo){
				source,
				left,
				top,
				right,
				bottom,
				layout
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(NPatchInfo));
		NPatchInfo * _returnptr=((NPatchInfo *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_NPatchInfo_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_GlyphInfo_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(GlyphInfo));
			JSValue _return=JS_NewObjectClass(ctx,js_GlyphInfo_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		GlyphInfo _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_GlyphInfo_class_id){
			GlyphInfo ptr=js_getGlyphInfo(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			int value=js_getint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int offsetX=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			int offsetY=js_getint(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			int advanceX=js_getint(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			Image image=js_getImage(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(GlyphInfo){
				value,
				offsetX,
				offsetY,
				advanceX,
				image
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(GlyphInfo));
		GlyphInfo * _returnptr=((GlyphInfo *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_GlyphInfo_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Font_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Font));
			JSValue _return=JS_NewObjectClass(ctx,js_Font_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Font _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Font_class_id){
			Font ptr=js_getFont(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =Font_copy(ctx,ptr);
		}else{
			int baseSize=js_getint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int glyphCount=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			int glyphPadding=js_getint(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			Texture2D texture=js_getTexture2D(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			Rectangle * recs=js_getRectangle_arrnc(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			GlyphInfo * glyphs=js_getGlyphInfo_arrnc(ctx,argv[5],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Font){
				baseSize,
				glyphCount,
				glyphPadding,
				texture,
				recs,
				glyphs
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Font));
		Font * _returnptr=((Font *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Font_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Camera3D_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Camera3D));
			JSValue _return=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Camera3D _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Camera3D_class_id){
			Camera3D ptr=js_getCamera3D(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			Vector3 position=js_getVector3(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			Vector3 target=js_getVector3(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			Vector3 up=js_getVector3(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			float fovy=js_getfloat(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			int projection=js_getint(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Camera3D){
				position,
				target,
				up,
				fovy,
				projection
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Camera3D));
		Camera3D * _returnptr=((Camera3D *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Camera3D_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Camera2D_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Camera2D));
			JSValue _return=JS_NewObjectClass(ctx,js_Camera2D_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Camera2D _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Camera2D_class_id){
			Camera2D ptr=js_getCamera2D(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			Vector2 offset=js_getVector2(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			Vector2 target=js_getVector2(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float rotation=js_getfloat(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			float zoom=js_getfloat(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Camera2D){
				offset,
				target,
				rotation,
				zoom
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Camera2D));
		Camera2D * _returnptr=((Camera2D *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Camera2D_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Mesh_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Mesh));
			JSValue _return=JS_NewObjectClass(ctx,js_Mesh_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Mesh _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Mesh_class_id){
			Mesh ptr=js_getMesh(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =Mesh_copy(ctx,ptr);
		}else{
			int vertexCount=js_getint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int triangleCount=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float * vertices=js_getfloat_arrnc(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			float * texcoords=js_getfloat_arrnc(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			float * texcoords2=js_getfloat_arrnc(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			float * normals=js_getfloat_arrnc(ctx,argv[5],&error);
			if(error==1)return JS_EXCEPTION;
			float * tangents=js_getfloat_arrnc(ctx,argv[6],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned char * colors=js_getunsignedchar_arrnc(ctx,argv[7],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned short * indices=js_getunsignedshort_arrnc(ctx,argv[8],&error);
			if(error==1)return JS_EXCEPTION;
			float * animVertices=js_getfloat_arrnc(ctx,argv[9],&error);
			if(error==1)return JS_EXCEPTION;
			float * animNormals=js_getfloat_arrnc(ctx,argv[10],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned char * boneIds=js_getunsignedchar_arrnc(ctx,argv[11],&error);
			if(error==1)return JS_EXCEPTION;
			float * boneWeights=js_getfloat_arrnc(ctx,argv[12],&error);
			if(error==1)return JS_EXCEPTION;
			Matrix * boneMatrices=js_getMatrix_arrnc(ctx,argv[13],&error);
			if(error==1)return JS_EXCEPTION;
			int boneCount=js_getint(ctx,argv[14],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int vaoId=js_getunsignedint(ctx,argv[15],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int * vboId=js_getunsignedint_arrnc(ctx,argv[16],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Mesh){
				vertexCount,
				triangleCount,
				vertices,
				texcoords,
				texcoords2,
				normals,
				tangents,
				colors,
				indices,
				animVertices,
				animNormals,
				boneIds,
				boneWeights,
				boneMatrices,
				boneCount,
				vaoId,
				vboId
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Mesh));
		Mesh * _returnptr=((Mesh *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Shader_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Shader));
			JSValue _return=JS_NewObjectClass(ctx,js_Shader_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Shader _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Shader_class_id){
			Shader ptr=js_getShader(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =Shader_copy(ctx,ptr);
		}else{
			unsigned int id=js_getunsignedint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int * locs=js_getint_arrnc(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Shader){
				id,
				locs
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Shader));
		Shader * _returnptr=((Shader *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Shader_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_MaterialMap_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(MaterialMap));
			JSValue _return=JS_NewObjectClass(ctx,js_MaterialMap_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		MaterialMap _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_MaterialMap_class_id){
			MaterialMap ptr=js_getMaterialMap(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			Color color=js_getColor(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float value=js_getfloat(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(MaterialMap){
				texture,
				color,
				value
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(MaterialMap));
		MaterialMap * _returnptr=((MaterialMap *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_MaterialMap_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Material_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Material));
			JSValue _return=JS_NewObjectClass(ctx,js_Material_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Material _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Material_class_id){
			Material ptr=js_getMaterial(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =Material_copy(ctx,ptr);
		}else{
			Shader shader=js_getShader(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			MaterialMap * maps=js_getMaterialMap_arrnc(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float * params=js_getfloat_arr4nc(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Material){
				shader,
				maps,
				{params[0],params[1],params[2],params[3]}
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Material));
		Material * _returnptr=((Material *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Material_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Transform_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Transform));
			JSValue _return=JS_NewObjectClass(ctx,js_Transform_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Transform _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Transform_class_id){
			Transform ptr=js_getTransform(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			Vector3 translation=js_getVector3(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			Quaternion rotation=js_getQuaternion(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			Vector3 scale=js_getVector3(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Transform){
				translation,
				rotation,
				scale
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Transform));
		Transform * _returnptr=((Transform *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Transform_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_BoneInfo_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(BoneInfo));
			JSValue _return=JS_NewObjectClass(ctx,js_BoneInfo_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		BoneInfo _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_BoneInfo_class_id){
			BoneInfo ptr=js_getBoneInfo(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			char * name=js_getchar_arr32nc(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int parent=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(BoneInfo){
				{name[0],name[1],name[2],name[3],name[4],name[5],name[6],name[7],name[8],name[9],name[10],name[11],name[12],name[13],name[14],name[15],name[16],name[17],name[18],name[19],name[20],name[21],name[22],name[23],name[24],name[25],name[26],name[27],name[28],name[29],name[30],name[31]},
				parent
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(BoneInfo));
		BoneInfo * _returnptr=((BoneInfo *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_BoneInfo_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Model_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Model));
			JSValue _return=JS_NewObjectClass(ctx,js_Model_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Model _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Model_class_id){
			Model ptr=js_getModel(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =Model_copy(ctx,ptr);
		}else{
			Matrix transform=js_getMatrix(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int meshCount=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			int materialCount=js_getint(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			Mesh * meshes=js_getMesh_arrnc(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			Material * materials=js_getMaterial_arrnc(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			int * meshMaterial=js_getint_arrnc(ctx,argv[5],&error);
			if(error==1)return JS_EXCEPTION;
			int boneCount=js_getint(ctx,argv[6],&error);
			if(error==1)return JS_EXCEPTION;
			BoneInfo * bones=js_getBoneInfo_arrnc(ctx,argv[7],&error);
			if(error==1)return JS_EXCEPTION;
			Transform * bindPose=js_getTransform_arrnc(ctx,argv[8],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Model){
				transform,
				meshCount,
				materialCount,
				meshes,
				materials,
				meshMaterial,
				boneCount,
				bones,
				bindPose
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Model));
		Model * _returnptr=((Model *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Model_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_ModelAnimation_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(ModelAnimation));
			JSValue _return=JS_NewObjectClass(ctx,js_ModelAnimation_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		ModelAnimation _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_ModelAnimation_class_id){
			ModelAnimation ptr=js_getModelAnimation(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ModelAnimation_copy(ctx,ptr);
		}else{
			int boneCount=js_getint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int frameCount=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			BoneInfo * bones=js_getBoneInfo_arrnc(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			Transform * * framePoses=js_getTransform_arr_arrnc(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			char * name=js_getchar_arr32nc(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(ModelAnimation){
				boneCount,
				frameCount,
				bones,
				framePoses,
				{name[0],name[1],name[2],name[3],name[4],name[5],name[6],name[7],name[8],name[9],name[10],name[11],name[12],name[13],name[14],name[15],name[16],name[17],name[18],name[19],name[20],name[21],name[22],name[23],name[24],name[25],name[26],name[27],name[28],name[29],name[30],name[31]}
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(ModelAnimation));
		ModelAnimation * _returnptr=((ModelAnimation *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_ModelAnimation_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Ray_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Ray));
			JSValue _return=JS_NewObjectClass(ctx,js_Ray_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Ray _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Ray_class_id){
			Ray ptr=js_getRay(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			Vector3 position=js_getVector3(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			Vector3 direction=js_getVector3(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Ray){
				position,
				direction
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Ray));
		Ray * _returnptr=((Ray *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Ray_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_RayCollision_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(RayCollision));
			JSValue _return=JS_NewObjectClass(ctx,js_RayCollision_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		RayCollision _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_RayCollision_class_id){
			RayCollision ptr=js_getRayCollision(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			bool hit=js_getbool(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			float distance=js_getfloat(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			Vector3 point=js_getVector3(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			Vector3 normal=js_getVector3(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(RayCollision){
				hit,
				distance,
				point,
				normal
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(RayCollision));
		RayCollision * _returnptr=((RayCollision *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_RayCollision_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_BoundingBox_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(BoundingBox));
			JSValue _return=JS_NewObjectClass(ctx,js_BoundingBox_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		BoundingBox _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_BoundingBox_class_id){
			BoundingBox ptr=js_getBoundingBox(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			Vector3 min=js_getVector3(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			Vector3 max=js_getVector3(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(BoundingBox){
				min,
				max
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(BoundingBox));
		BoundingBox * _returnptr=((BoundingBox *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_BoundingBox_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Wave_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Wave));
			JSValue _return=JS_NewObjectClass(ctx,js_Wave_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Wave _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Wave_class_id){
			Wave ptr=js_getWave(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =Wave_copy(ctx,ptr);
		}else{
			unsigned int frameCount=js_getunsignedint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int sampleRate=js_getunsignedint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int sampleSize=js_getunsignedint(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int channels=js_getunsignedint(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			void * data=js_getvoid_arr(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Wave){
				frameCount,
				sampleRate,
				sampleSize,
				channels,
				data
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Wave));
		Wave * _returnptr=((Wave *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Wave_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_AudioStream_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(AudioStream));
			JSValue _return=JS_NewObjectClass(ctx,js_AudioStream_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		AudioStream _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_AudioStream_class_id){
			AudioStream ptr=js_getAudioStream(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			bool buffer_isptr=(bool)false;
			rAudioBuffer * buffer=js_getrAudioBuffer_ptrnc(ctx,argv[0],&error,&buffer_isptr);
			if(error==1)return JS_EXCEPTION;
			bool processor_isptr=(bool)false;
			rAudioProcessor * processor=js_getrAudioProcessor_ptrnc(ctx,argv[1],&error,&processor_isptr);
			if(error==1)return JS_EXCEPTION;
			unsigned int sampleRate=js_getunsignedint(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int sampleSize=js_getunsignedint(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int channels=js_getunsignedint(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(AudioStream){
				buffer,
				processor,
				sampleRate,
				sampleSize,
				channels
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(AudioStream));
		AudioStream * _returnptr=((AudioStream *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_AudioStream_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Sound_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Sound));
			JSValue _return=JS_NewObjectClass(ctx,js_Sound_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Sound _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Sound_class_id){
			Sound ptr=js_getSound(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int frameCount=js_getunsignedint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Sound){
				stream,
				frameCount
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Sound));
		Sound * _returnptr=((Sound *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Sound_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_Music_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Music));
			JSValue _return=JS_NewObjectClass(ctx,js_Music_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Music _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Music_class_id){
			Music ptr=js_getMusic(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
		}else{
			AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int frameCount=js_getunsignedint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			bool looping=js_getbool(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			int ctxType=js_getint(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			void * ctxData=js_getvoid_arr(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Music){
				stream,
				frameCount,
				looping,
				ctxType,
				ctxData
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Music));
		Music * _returnptr=((Music *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Music_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_VrDeviceInfo_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(VrDeviceInfo));
			JSValue _return=JS_NewObjectClass(ctx,js_VrDeviceInfo_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		VrDeviceInfo _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_VrDeviceInfo_class_id){
			VrDeviceInfo ptr=js_getVrDeviceInfo(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			int hResolution=js_getint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int vResolution=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float hScreenSize=js_getfloat(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			float vScreenSize=js_getfloat(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			float eyeToScreenDistance=js_getfloat(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			float lensSeparationDistance=js_getfloat(ctx,argv[5],&error);
			if(error==1)return JS_EXCEPTION;
			float interpupillaryDistance=js_getfloat(ctx,argv[6],&error);
			if(error==1)return JS_EXCEPTION;
			float * lensDistortionValues=js_getfloat_arr4nc(ctx,argv[7],&error);
			if(error==1)return JS_EXCEPTION;
			float * chromaAbCorrection=js_getfloat_arr4nc(ctx,argv[8],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(VrDeviceInfo){
				hResolution,
				vResolution,
				hScreenSize,
				vScreenSize,
				eyeToScreenDistance,
				lensSeparationDistance,
				interpupillaryDistance,
				{lensDistortionValues[0],lensDistortionValues[1],lensDistortionValues[2],lensDistortionValues[3]},
				{chromaAbCorrection[0],chromaAbCorrection[1],chromaAbCorrection[2],chromaAbCorrection[3]}
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(VrDeviceInfo));
		VrDeviceInfo * _returnptr=((VrDeviceInfo *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_VrDeviceInfo_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_VrStereoConfig_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(VrStereoConfig));
			JSValue _return=JS_NewObjectClass(ctx,js_VrStereoConfig_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		VrStereoConfig _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_VrStereoConfig_class_id){
			VrStereoConfig ptr=js_getVrStereoConfig(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			Matrix * projection=js_getMatrix_arr2nc(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			Matrix * viewOffset=js_getMatrix_arr2nc(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float * leftLensCenter=js_getfloat_arr2nc(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			float * rightLensCenter=js_getfloat_arr2nc(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			float * leftScreenCenter=js_getfloat_arr2nc(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			float * rightScreenCenter=js_getfloat_arr2nc(ctx,argv[5],&error);
			if(error==1)return JS_EXCEPTION;
			float * scale=js_getfloat_arr2nc(ctx,argv[6],&error);
			if(error==1)return JS_EXCEPTION;
			float * scaleIn=js_getfloat_arr2nc(ctx,argv[7],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(VrStereoConfig){
				{projection[0],projection[1]},
				{viewOffset[0],viewOffset[1]},
				{leftLensCenter[0],leftLensCenter[1]},
				{rightLensCenter[0],rightLensCenter[1]},
				{leftScreenCenter[0],leftScreenCenter[1]},
				{rightScreenCenter[0],rightScreenCenter[1]},
				{scale[0],scale[1]},
				{scaleIn[0],scaleIn[1]}
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(VrStereoConfig));
		VrStereoConfig * _returnptr=((VrStereoConfig *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_VrStereoConfig_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_FilePathList_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(FilePathList));
			JSValue _return=JS_NewObjectClass(ctx,js_FilePathList_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		FilePathList _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_FilePathList_class_id){
			FilePathList ptr=js_getFilePathList(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =FilePathList_copy(ctx,ptr);
		}else{
			unsigned int capacity=js_getunsignedint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int count=js_getunsignedint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			char * * paths=js_getchar_arr_arrnc(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(FilePathList){
				capacity,
				count,
				paths
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(FilePathList));
		FilePathList * _returnptr=((FilePathList *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_FilePathList_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_AutomationEvent_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(AutomationEvent));
			JSValue _return=JS_NewObjectClass(ctx,js_AutomationEvent_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		AutomationEvent _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_AutomationEvent_class_id){
			AutomationEvent ptr=js_getAutomationEvent(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			unsigned int frame=js_getunsignedint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int type=js_getunsignedint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			int * params=js_getint_arr4nc(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(AutomationEvent){
				frame,
				type,
				{params[0],params[1],params[2],params[3]}
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(AutomationEvent));
		AutomationEvent * _returnptr=((AutomationEvent *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_AutomationEvent_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_AutomationEventList_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(AutomationEventList));
			JSValue _return=JS_NewObjectClass(ctx,js_AutomationEventList_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		AutomationEventList _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_AutomationEventList_class_id){
			AutomationEventList ptr=js_getAutomationEventList(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =AutomationEventList_copy(ctx,ptr);
		}else{
			unsigned int capacity=js_getunsignedint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int count=js_getunsignedint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			AutomationEvent * events=js_getAutomationEvent_arrnc(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(AutomationEventList){
				capacity,
				count,
				events
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(AutomationEventList));
		AutomationEventList * _returnptr=((AutomationEventList *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_AutomationEventList_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_InitWindow(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * title=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		InitWindow(width,height,(const char  *)title);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CloseWindow(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		CloseWindow();
		return JS_UNDEFINED;
	}
	
	static JSValue js_WindowShouldClose(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=WindowShouldClose();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsWindowReady(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=IsWindowReady();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsWindowFullscreen(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=IsWindowFullscreen();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsWindowHidden(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=IsWindowHidden();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsWindowMinimized(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=IsWindowMinimized();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsWindowMaximized(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=IsWindowMaximized();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsWindowFocused(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=IsWindowFocused();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsWindowResized(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=IsWindowResized();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsWindowState(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int flag=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsWindowState(flag);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_SetWindowState(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int flags=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetWindowState(flags);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ClearWindowState(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int flags=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		ClearWindowState(flags);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ToggleFullscreen(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		ToggleFullscreen();
		return JS_UNDEFINED;
	}
	
	static JSValue js_ToggleBorderlessWindowed(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		ToggleBorderlessWindowed();
		return JS_UNDEFINED;
	}
	
	static JSValue js_MaximizeWindow(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		MaximizeWindow();
		return JS_UNDEFINED;
	}
	
	static JSValue js_MinimizeWindow(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		MinimizeWindow();
		return JS_UNDEFINED;
	}
	
	static JSValue js_RestoreWindow(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		RestoreWindow();
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetWindowIcon(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetWindowIcon(image);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetWindowIcons(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image * images=js_getImage_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int count=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetWindowIcons(images,count);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetWindowTitle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * title=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetWindowTitle((const char  *)title);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetWindowPosition(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int x=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int y=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetWindowPosition(x,y);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetWindowMonitor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int monitor=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetWindowMonitor(monitor);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetWindowMinSize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetWindowMinSize(width,height);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetWindowMaxSize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetWindowMaxSize(width,height);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetWindowSize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetWindowSize(width,height);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetWindowOpacity(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float opacity=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetWindowOpacity(opacity);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetWindowFocused(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		SetWindowFocused();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetScreenWidth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetScreenWidth();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetScreenHeight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetScreenHeight();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetRenderWidth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetRenderWidth();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetRenderHeight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetRenderHeight();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetMonitorCount(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetMonitorCount();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetCurrentMonitor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetCurrentMonitor();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetMonitorPosition(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int monitor=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=GetMonitorPosition(monitor);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetMonitorWidth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int monitor=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetMonitorWidth(monitor);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetMonitorHeight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int monitor=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetMonitorHeight(monitor);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetMonitorPhysicalWidth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int monitor=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetMonitorPhysicalWidth(monitor);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetMonitorPhysicalHeight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int monitor=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetMonitorPhysicalHeight(monitor);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetMonitorRefreshRate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int monitor=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetMonitorRefreshRate(monitor);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetWindowPosition(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 returnVal=GetWindowPosition();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetWindowScaleDPI(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 returnVal=GetWindowScaleDPI();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetMonitorName(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int monitor=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)GetMonitorName(monitor);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		return ret;
	}
	
	static JSValue js_SetClipboardText(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetClipboardText((const char  *)text);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetClipboardText(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		char * returnVal=(char  *)GetClipboardText();
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		return ret;
	}
	
	static JSValue js_GetClipboardImage(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Image returnVal=GetClipboardImage();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_EnableEventWaiting(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		EnableEventWaiting();
		return JS_UNDEFINED;
	}
	
	static JSValue js_DisableEventWaiting(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		DisableEventWaiting();
		return JS_UNDEFINED;
	}
	
	static JSValue js_ShowCursor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		ShowCursor();
		return JS_UNDEFINED;
	}
	
	static JSValue js_HideCursor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		HideCursor();
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsCursorHidden(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=IsCursorHidden();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_EnableCursor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		EnableCursor();
		return JS_UNDEFINED;
	}
	
	static JSValue js_DisableCursor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		DisableCursor();
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsCursorOnScreen(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=IsCursorOnScreen();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_ClearBackground(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color color=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		ClearBackground(color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_BeginDrawing(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		BeginDrawing();
		return JS_UNDEFINED;
	}
	
	static JSValue js_EndDrawing(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		EndDrawing();
		app_update_quickjs(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_BeginMode2D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera2D camera=js_getCamera2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		BeginMode2D(camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_EndMode2D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		EndMode2D();
		return JS_UNDEFINED;
	}
	
	static JSValue js_BeginMode3D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera3D camera=js_getCamera3D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		BeginMode3D(camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_EndMode3D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		EndMode3D();
		return JS_UNDEFINED;
	}
	
	static JSValue js_BeginTextureMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		RenderTexture2D target=js_getRenderTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		BeginTextureMode(target);
		return JS_UNDEFINED;
	}
	
	static JSValue js_EndTextureMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		EndTextureMode();
		return JS_UNDEFINED;
	}
	
	static JSValue js_BeginShaderMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Shader shader=js_getShader(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		BeginShaderMode(shader);
		return JS_UNDEFINED;
	}
	
	static JSValue js_EndShaderMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		EndShaderMode();
		return JS_UNDEFINED;
	}
	
	static JSValue js_BeginBlendMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int mode=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		BeginBlendMode(mode);
		return JS_UNDEFINED;
	}
	
	static JSValue js_EndBlendMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		EndBlendMode();
		return JS_UNDEFINED;
	}
	
	static JSValue js_BeginScissorMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int x=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int y=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		BeginScissorMode(x,y,width,height);
		return JS_UNDEFINED;
	}
	
	static JSValue js_EndScissorMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		EndScissorMode();
		return JS_UNDEFINED;
	}
	
	static JSValue js_BeginVrStereoMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		VrStereoConfig config=js_getVrStereoConfig(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		BeginVrStereoMode(config);
		return JS_UNDEFINED;
	}
	
	static JSValue js_EndVrStereoMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		EndVrStereoMode();
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadVrStereoConfig(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		VrDeviceInfo device=js_getVrDeviceInfo(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		VrStereoConfig returnVal=LoadVrStereoConfig(device);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(VrStereoConfig));
		VrStereoConfig * ptr2_ret=((VrStereoConfig *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_VrStereoConfig_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_UnloadVrStereoConfig(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		VrStereoConfig config=js_getVrStereoConfig(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadVrStereoConfig(config);
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadShader(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * vsFileName=js_getchar_arrnull(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fsFileName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Shader returnVal=LoadShader((const char  *)vsFileName,(const char  *)fsFileName);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Shader));
		Shader * ptr2_ret=((Shader *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Shader_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadShaderFromMemory(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * vsCode=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fsCode=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Shader returnVal=LoadShaderFromMemory((const char  *)vsCode,(const char  *)fsCode);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Shader));
		Shader * ptr2_ret=((Shader *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Shader_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_IsShaderValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Shader shader=js_getShader(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsShaderValid(shader);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_GetShaderLocation(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Shader shader=js_getShader(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * uniformName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetShaderLocation(shader,(const char  *)uniformName);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetShaderLocationAttrib(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Shader shader=js_getShader(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * attribName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetShaderLocationAttrib(shader,(const char  *)attribName);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_SetShaderValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		error =(bool)0;
		void * value=NULL;
		Shader shader=js_getShader(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int locIndex=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int uniformType=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		memoryClear(ctx);
		if(uniformType==SHADER_UNIFORM_FLOAT){
			bool val_isptr=(bool)false;
			float * val=js_getfloat_ptr(ctx,argv[2],&error,&val_isptr);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_VEC2){
			bool val_isptr=(bool)false;
			Vector2 * val=js_getVector2_ptr(ctx,argv[2],&error,&val_isptr);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_VEC3){
			bool val_isptr=(bool)false;
			Vector3 * val=js_getVector3_ptr(ctx,argv[2],&error,&val_isptr);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_VEC4){
			bool val_isptr=(bool)false;
			Vector4 * val=js_getVector4_ptr(ctx,argv[2],&error,&val_isptr);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_INT||uniformType==SHADER_UNIFORM_SAMPLER2D){
			bool val_isptr=(bool)false;
			int * val=js_getint_ptr(ctx,argv[2],&error,&val_isptr);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_IVEC2){
			int * val=js_getint_arr2(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_IVEC3){
			int * val=js_getint_arr3(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_IVEC4){
			int * val=js_getint_arr4(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UINT){
			bool val_isptr=(bool)false;
			unsigned int * val=js_getunsignedint_ptr(ctx,argv[2],&error,&val_isptr);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UIVEC2){
			unsigned int * val=js_getunsignedint_arr2(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UIVEC3){
			unsigned int * val=js_getunsignedint_arr3(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UIVEC4){
			unsigned int * val=js_getunsignedint_arr4(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"unknown uniformType");
			return JS_EXCEPTION;
		}
		SetShaderValue(shader,locIndex,(const void  *)value,uniformType);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetShaderValueV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int count=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		error =(bool)0;
		void * value=NULL;
		Shader shader=js_getShader(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int locIndex=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int uniformType=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		if(uniformType==SHADER_UNIFORM_FLOAT){
			float * val=js_getfloat_arr_arg1(ctx,argv[2],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_VEC2){
			Vector2 * val=js_getVector2_arr_arg1(ctx,argv[2],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_VEC3){
			Vector3 * val=js_getVector3_arr_arg1(ctx,argv[2],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_VEC4){
			Vector4 * val=js_getVector4_arr_arg1(ctx,argv[2],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_INT||uniformType==SHADER_UNIFORM_SAMPLER2D){
			int * val=js_getint_arr_arg1(ctx,argv[2],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_IVEC2){
			int * val=js_getint_arr_arg1(ctx,argv[2],&error,(int)2*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_IVEC3){
			int * val=js_getint_arr_arg1(ctx,argv[2],&error,(int)3*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_IVEC4){
			int * val=js_getint_arr_arg1(ctx,argv[2],&error,(int)4*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UINT){
			unsigned int * val=js_getunsignedint_arr_arg1(ctx,argv[2],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UIVEC2){
			unsigned int * val=js_getunsignedint_arr_arg1(ctx,argv[2],&error,(int)2*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UIVEC3){
			unsigned int * val=js_getunsignedint_arr_arg1(ctx,argv[2],&error,(int)3*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UIVEC4){
			unsigned int * val=js_getunsignedint_arr_arg1(ctx,argv[2],&error,(int)4*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"unknown uniformType");
			return JS_EXCEPTION;
		}
		SetShaderValueV(shader,locIndex,(const void  *)value,uniformType,count);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetShaderValueMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Shader shader=js_getShader(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int locIndex=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix mat=js_getMatrix(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		SetShaderValueMatrix(shader,locIndex,mat);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetShaderValueTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Shader shader=js_getShader(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int locIndex=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Texture2D texture=js_getTexture2D(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		SetShaderValueTexture(shader,locIndex,texture);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UnloadShader(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Shader shader=js_getShader(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadShader(shader);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetScreenToWorldRay(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 position=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Camera camera=js_getCamera(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Ray returnVal=GetScreenToWorldRay(position,camera);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Ray));
		Ray * ptr2_ret=((Ray *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Ray_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetScreenToWorldRayEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 position=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Camera camera=js_getCamera(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Ray returnVal=GetScreenToWorldRayEx(position,camera,width,height);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Ray));
		Ray * ptr2_ret=((Ray *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Ray_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetWorldToScreen(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 position=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Camera camera=js_getCamera(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=GetWorldToScreen(position,camera);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetWorldToScreenEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 position=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Camera camera=js_getCamera(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=GetWorldToScreenEx(position,camera,width,height);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetWorldToScreen2D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 position=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Camera2D camera=js_getCamera2D(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=GetWorldToScreen2D(position,camera);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetScreenToWorld2D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 position=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Camera2D camera=js_getCamera2D(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=GetScreenToWorld2D(position,camera);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetCameraMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera camera=js_getCamera(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=GetCameraMatrix(camera);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Matrix));
		Matrix * ptr2_ret=((Matrix *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetCameraMatrix2D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera2D camera=js_getCamera2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=GetCameraMatrix2D(camera);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Matrix));
		Matrix * ptr2_ret=((Matrix *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_SetTargetFPS(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int fps=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetTargetFPS(fps);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetFrameTime(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		float returnVal=GetFrameTime();
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_GetTime(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double returnVal=GetTime();
		JSValue ret=JS_NewFloat64(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_GetFPS(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetFPS();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_SetRandomSeed(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int seed=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetRandomSeed(seed);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetRandomValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int min=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int max=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetRandomValue(min,max);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_LoadRandomSequence(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int count=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int min=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int max=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int * returnVal=LoadRandomSequence(count,min,max);
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<count;i++){
			int src0=returnVal[i];
			JSValue ret1=JS_NewInt32(ctx,(int32_t)((long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		UnloadRandomSequence(returnVal);
		return ret;
	}
	
	static JSValue js_UnloadRandomSequence(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int * sequence=js_getint_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadRandomSequence(sequence);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_TakeScreenshot(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		TakeScreenshot((const char  *)fileName);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetConfigFlags(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int flags=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetConfigFlags(flags);
		return JS_UNDEFINED;
	}
	
	static JSValue js_OpenURL(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * url=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		OpenURL((const char  *)url);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_TraceLog(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int logLevel=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		size_t size_text=argc-1;
		if(size_text>4)size_text=(size_t)4;
		const char * * text=(const char  * *)js_malloc(ctx,size_text*sizeof(const char *));
		memoryStore(js_free,(void  *)*text);
		for(int i=0;i<size_text;i++){
			text[i] =(const char  *)js_getchar_arr(ctx,argv[i+1],&error);
			if(error==1)return JS_EXCEPTION;
		}
		if(size_text==0){
			return JS_EXCEPTION;
		}else if(size_text==1){
			TraceLog(logLevel,text[0]);
		}else if(size_text==2){
			TraceLog(logLevel,text[0],text[1]);
		}else if(size_text==3)TraceLog(logLevel,text[0],text[1],text[2]);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetTraceLogLevel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int logLevel=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetTraceLogLevel(logLevel);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetLoadFileDataCallback(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * callback;
		trampolineContext ctx_callback;
		ctx_callback.ctx=ctx;
		ctx_callback.func_obj=argv[0];
		if(JS_IsUndefined(argv[0])||JS_IsNull(argv[0])){
			JS_FreeValue(LoadFileDataCallback_arr[0].ctx,LoadFileDataCallback_arr[0].func_obj);
			JS_FreeContext(LoadFileDataCallback_arr[0].ctx);
			LoadFileDataCallback_arr =NULL;
		}else if(JS_IsFunction(ctx,argv[0])==1){
			if(LoadFileDataCallback_arr!=NULL){
				JS_FreeValue(LoadFileDataCallback_arr[0].ctx,LoadFileDataCallback_arr[0].func_obj);
				JS_FreeContext(LoadFileDataCallback_arr[0].ctx);
			}
			LoadFileDataCallback_arr =&ctx_callback;
		}else{
			return JS_EXCEPTION;
		}
		if(LoadFileDataCallback_arr==NULL){
			callback =NULL;
		}else{
			callback =callback_LoadFileDataCallback;
		}
		JS_DupValue(ctx,argv[0]);
		SetLoadFileDataCallback(callback);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetSaveFileDataCallback(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * callback;
		trampolineContext ctx_callback;
		ctx_callback.ctx=ctx;
		ctx_callback.func_obj=argv[0];
		if(JS_IsUndefined(argv[0])||JS_IsNull(argv[0])){
			JS_FreeValue(SaveFileDataCallback_arr[0].ctx,SaveFileDataCallback_arr[0].func_obj);
			JS_FreeContext(SaveFileDataCallback_arr[0].ctx);
			SaveFileDataCallback_arr =NULL;
		}else if(JS_IsFunction(ctx,argv[0])==1){
			if(SaveFileDataCallback_arr!=NULL){
				JS_FreeValue(SaveFileDataCallback_arr[0].ctx,SaveFileDataCallback_arr[0].func_obj);
				JS_FreeContext(SaveFileDataCallback_arr[0].ctx);
			}
			SaveFileDataCallback_arr =&ctx_callback;
		}else{
			return JS_EXCEPTION;
		}
		if(SaveFileDataCallback_arr==NULL){
			callback =NULL;
		}else{
			callback =callback_SaveFileDataCallback;
		}
		JS_DupValue(ctx,argv[0]);
		SetSaveFileDataCallback(callback);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetLoadFileTextCallback(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * callback;
		trampolineContext ctx_callback;
		ctx_callback.ctx=ctx;
		ctx_callback.func_obj=argv[0];
		if(JS_IsUndefined(argv[0])||JS_IsNull(argv[0])){
			JS_FreeValue(LoadFileTextCallback_arr[0].ctx,LoadFileTextCallback_arr[0].func_obj);
			JS_FreeContext(LoadFileTextCallback_arr[0].ctx);
			LoadFileTextCallback_arr =NULL;
		}else if(JS_IsFunction(ctx,argv[0])==1){
			if(LoadFileTextCallback_arr!=NULL){
				JS_FreeValue(LoadFileTextCallback_arr[0].ctx,LoadFileTextCallback_arr[0].func_obj);
				JS_FreeContext(LoadFileTextCallback_arr[0].ctx);
			}
			LoadFileTextCallback_arr =&ctx_callback;
		}else{
			return JS_EXCEPTION;
		}
		if(LoadFileTextCallback_arr==NULL){
			callback =NULL;
		}else{
			callback =callback_LoadFileTextCallback;
		}
		JS_DupValue(ctx,argv[0]);
		SetLoadFileTextCallback(callback);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetSaveFileTextCallback(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * callback;
		trampolineContext ctx_callback;
		ctx_callback.ctx=ctx;
		ctx_callback.func_obj=argv[0];
		if(JS_IsUndefined(argv[0])||JS_IsNull(argv[0])){
			JS_FreeValue(SaveFileTextCallback_arr[0].ctx,SaveFileTextCallback_arr[0].func_obj);
			JS_FreeContext(SaveFileTextCallback_arr[0].ctx);
			SaveFileTextCallback_arr =NULL;
		}else if(JS_IsFunction(ctx,argv[0])==1){
			if(SaveFileTextCallback_arr!=NULL){
				JS_FreeValue(SaveFileTextCallback_arr[0].ctx,SaveFileTextCallback_arr[0].func_obj);
				JS_FreeContext(SaveFileTextCallback_arr[0].ctx);
			}
			SaveFileTextCallback_arr =&ctx_callback;
		}else{
			return JS_EXCEPTION;
		}
		if(SaveFileTextCallback_arr==NULL){
			callback =NULL;
		}else{
			callback =callback_SaveFileTextCallback;
		}
		JS_DupValue(ctx,argv[0]);
		SetSaveFileTextCallback(callback);
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadFileData(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool dataSize_isptr=(bool)false;
		int * dataSize=js_getint_ptr(ctx,argv[1],&error,&dataSize_isptr);
		if(error==1)return JS_EXCEPTION;
		unsigned char * returnVal=(unsigned char  *)LoadFileData((const char  *)fileName,dataSize);
		if(dataSize_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)dataSize[0]));
			JS_SetPropertyUint32(ctx,argv[1],(uint32_t)0,src);
		}
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<dataSize[0];i++){
			unsigned char src0=returnVal[i];
			JSValue ret1=JS_NewUint32(ctx,(uint32_t)((unsigned long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		UnloadFileData(returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_SaveFileData(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		void * data=js_getvoid_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=SaveFileData((const char  *)fileName,data,dataSize);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ExportDataAsCode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned char * data=js_getunsignedchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * fileName=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=ExportDataAsCode((const unsigned char  *)data,dataSize,(const char  *)fileName);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadFileText(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=LoadFileText((const char  *)fileName);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		UnloadFileText(returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_SaveFileText(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=SaveFileText((const char  *)fileName,(const char  *)text);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_FileRename(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fileRename=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=FileRename((const char  *)fileName,(const char  *)fileRename);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_FileRemove(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=FileRemove((const char  *)fileName);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_FileCopy(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * srcPath=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * dstPath=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=FileCopy((const char  *)srcPath,(const char  *)dstPath);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_FileMove(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * srcPath=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * dstPath=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=FileMove((const char  *)srcPath,(const char  *)dstPath);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_FileTextReplace(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * search=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * replacement=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=FileTextReplace((const char  *)fileName,(const char  *)search,(const char  *)replacement);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_FileTextFindIndex(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * search=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=FileTextFindIndex((const char  *)fileName,(const char  *)search);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_FileExists(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=FileExists((const char  *)fileName);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_DirectoryExists(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * dirPath=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=DirectoryExists((const char  *)dirPath);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_IsFileExtension(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * ext=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsFileExtension((const char  *)fileName,(const char  *)ext);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetFileLength(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetFileLength((const char  *)fileName);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetFileModTime(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		long returnVal=GetFileModTime((const char  *)fileName);
		JSValue ret=JS_NewInt32(ctx,(int32_t)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetFileExtension(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)GetFileExtension((const char  *)fileName);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetFileName(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * filePath=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)GetFileName((const char  *)filePath);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetFileNameWithoutExt(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * filePath=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)GetFileNameWithoutExt((const char  *)filePath);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetDirectoryPath(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * filePath=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)GetDirectoryPath((const char  *)filePath);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetPrevDirectoryPath(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * dirPath=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)GetPrevDirectoryPath((const char  *)dirPath);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetWorkingDirectory(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		char * returnVal=(char  *)GetWorkingDirectory();
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		return ret;
	}
	
	static JSValue js_GetApplicationDirectory(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		char * returnVal=(char  *)GetApplicationDirectory();
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		return ret;
	}
	
	static JSValue js_MakeDirectory(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * dirPath=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=MakeDirectory((const char  *)dirPath);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ChangeDirectory(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * dir=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=ChangeDirectory((const char  *)dir);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_IsPathFile(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * path=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsPathFile((const char  *)path);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_IsFileNameValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsFileNameValid((const char  *)fileName);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadDirectoryFiles(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * dirPath=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		FilePathList files=LoadDirectoryFiles((const char  *)dirPath);
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<files.count;i++){
			JSValue str=JS_NewString(ctx,(const char  *)files.paths[i]);
			JS_SetPropertyUint32(ctx,ret,(uint32_t)i,str);
		}
		UnloadDirectoryFiles(files);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadDirectoryFilesEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * basePath=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * filter=js_getchar_arrnull(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool scanSubdirs=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		FilePathList files=LoadDirectoryFilesEx((const char  *)basePath,(const char  *)filter,scanSubdirs);
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<files.count;i++){
			JSValue str=JS_NewString(ctx,(const char  *)files.paths[i]);
			JS_SetPropertyUint32(ctx,ret,(uint32_t)i,str);
		}
		UnloadDirectoryFiles(files);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_IsFileDropped(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=IsFileDropped();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_LoadDroppedFiles(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		FilePathList files=LoadDroppedFiles();
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<files.count;i++){
			JSValue str=JS_NewString(ctx,(const char  *)files.paths[i]);
			JS_SetPropertyUint32(ctx,ret,(uint32_t)i,str);
		}
		UnloadDroppedFiles(files);
		return ret;
	}
	
	static JSValue js_CompressData(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned char * data=js_getunsignedchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * compDataSize=js_getint_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=CompressData((const unsigned char  *)data,dataSize,compDataSize);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_DecompressData(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned char * compData=js_getunsignedchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int compDataSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool dataSize_isptr=(bool)false;
		int * dataSize=js_getint_ptr(ctx,argv[2],&error,&dataSize_isptr);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=DecompressData((const unsigned char  *)compData,compDataSize,dataSize);
		if(dataSize_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)dataSize[0]));
			JS_SetPropertyUint32(ctx,argv[2],(uint32_t)0,src);
		}
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_EncodeDataBase64(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned char * data=js_getunsignedchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * outputSize=js_getint_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=EncodeDataBase64((const unsigned char  *)data,dataSize,outputSize);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_DecodeDataBase64(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int * outputSize=js_getint_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=DecodeDataBase64((const char  *)text,outputSize);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ComputeCRC32(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned char * data=js_getunsignedchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=ComputeCRC32(data,dataSize);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ComputeMD5(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned char * data=js_getunsignedchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * returnVal=ComputeMD5(data,dataSize);
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<4;i++){
			int src0=returnVal[i];
			JSValue ret1=JS_NewInt32(ctx,(int32_t)((long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ComputeSHA1(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned char * data=js_getunsignedchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * returnVal=ComputeSHA1(data,dataSize);
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<5;i++){
			int src0=returnVal[i];
			JSValue ret1=JS_NewInt32(ctx,(int32_t)((long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ComputeSHA256(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned char * data=js_getunsignedchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * returnVal=ComputeSHA256(data,dataSize);
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<8;i++){
			int src0=returnVal[i];
			JSValue ret1=JS_NewInt32(ctx,(int32_t)((long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadAutomationEventList(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arrnull(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		AutomationEventList returnVal=LoadAutomationEventList((const char  *)fileName);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(AutomationEventList));
		AutomationEventList * ptr2_ret=((AutomationEventList *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_AutomationEventList_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_UnloadAutomationEventList(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AutomationEventList list=js_getAutomationEventList(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadAutomationEventList(list);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ExportAutomationEventList(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AutomationEventList list=js_getAutomationEventList(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fileName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=ExportAutomationEventList(list,(const char  *)fileName);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_SetAutomationEventList(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AutomationEventList * list=js_getAutomationEventList_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetAutomationEventList(list);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetAutomationEventBaseFrame(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int frame=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetAutomationEventBaseFrame(frame);
		return JS_UNDEFINED;
	}
	
	static JSValue js_StartAutomationEventRecording(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		StartAutomationEventRecording();
		return JS_UNDEFINED;
	}
	
	static JSValue js_StopAutomationEventRecording(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		StopAutomationEventRecording();
		return JS_UNDEFINED;
	}
	
	static JSValue js_PlayAutomationEvent(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AutomationEvent event=js_getAutomationEvent(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		PlayAutomationEvent(event);
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsKeyPressed(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int key=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsKeyPressed(key);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsKeyPressedRepeat(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int key=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsKeyPressedRepeat(key);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsKeyDown(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int key=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsKeyDown(key);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsKeyReleased(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int key=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsKeyReleased(key);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsKeyUp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int key=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsKeyUp(key);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_GetKeyPressed(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetKeyPressed();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetCharPressed(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetCharPressed();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetKeyName(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int key=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)GetKeyName(key);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		return ret;
	}
	
	static JSValue js_SetExitKey(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int key=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetExitKey(key);
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsGamepadAvailable(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int gamepad=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsGamepadAvailable(gamepad);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_GetGamepadName(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int gamepad=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)GetGamepadName(gamepad);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		return ret;
	}
	
	static JSValue js_IsGamepadButtonPressed(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int gamepad=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int button=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsGamepadButtonPressed(gamepad,button);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsGamepadButtonDown(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int gamepad=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int button=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsGamepadButtonDown(gamepad,button);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsGamepadButtonReleased(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int gamepad=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int button=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsGamepadButtonReleased(gamepad,button);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsGamepadButtonUp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int gamepad=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int button=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsGamepadButtonUp(gamepad,button);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_GetGamepadButtonPressed(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetGamepadButtonPressed();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetGamepadAxisCount(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int gamepad=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetGamepadAxisCount(gamepad);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetGamepadAxisMovement(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int gamepad=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int axis=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=GetGamepadAxisMovement(gamepad,axis);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_SetGamepadMappings(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * mappings=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=SetGamepadMappings((const char  *)mappings);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_SetGamepadVibration(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int gamepad=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float leftMotor=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float rightMotor=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float duration=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		SetGamepadVibration(gamepad,leftMotor,rightMotor,duration);
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsMouseButtonPressed(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int button=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsMouseButtonPressed(button);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsMouseButtonDown(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int button=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsMouseButtonDown(button);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsMouseButtonReleased(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int button=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsMouseButtonReleased(button);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_IsMouseButtonUp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int button=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsMouseButtonUp(button);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_GetMouseX(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetMouseX();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetMouseY(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetMouseY();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetMousePosition(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 returnVal=GetMousePosition();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetMouseDelta(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 returnVal=GetMouseDelta();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_SetMousePosition(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int x=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int y=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetMousePosition(x,y);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetMouseOffset(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int offsetX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int offsetY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetMouseOffset(offsetX,offsetY);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetMouseScale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float scaleX=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float scaleY=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetMouseScale(scaleX,scaleY);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetMouseWheelMove(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		float returnVal=GetMouseWheelMove();
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_GetMouseWheelMoveV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 returnVal=GetMouseWheelMoveV();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_SetMouseCursor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int cursor=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetMouseCursor(cursor);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetTouchX(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetTouchX();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetTouchY(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetTouchY();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetTouchPosition(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int index=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=GetTouchPosition(index);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetTouchPointId(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int index=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetTouchPointId(index);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetTouchPointCount(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetTouchPointCount();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_SetGesturesEnabled(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int flags=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetGesturesEnabled(flags);
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsGestureDetected(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int gesture=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsGestureDetected(gesture);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_GetGestureDetected(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=GetGestureDetected();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetGestureHoldDuration(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		float returnVal=GetGestureHoldDuration();
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_GetGestureDragVector(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 returnVal=GetGestureDragVector();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetGestureDragAngle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		float returnVal=GetGestureDragAngle();
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_GetGesturePinchVector(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 returnVal=GetGesturePinchVector();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetGesturePinchAngle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		float returnVal=GetGesturePinchAngle();
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_UpdateCamera(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		int mode=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		UpdateCamera(camera,mode);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UpdateCameraPro(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector3 movement=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 rotation=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float zoom=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		UpdateCameraPro(camera,movement,rotation,zoom);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetShapesTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle source=js_getRectangle(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetShapesTexture(texture,source);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetShapesTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Texture2D returnVal=GetShapesTexture();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Texture2D));
		Texture2D * ptr2_ret=((Texture2D *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Texture_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetShapesTextureRectangle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Rectangle returnVal=GetShapesTextureRectangle();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Rectangle));
		Rectangle * ptr2_ret=((Rectangle *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Rectangle_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_DrawPixel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int posX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawPixel(posX,posY,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawPixelV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 position=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		DrawPixelV(position,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawLine(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int startPosX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int startPosY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int endPosX=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int endPosY=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawLine(startPosX,startPosY,endPosX,endPosY,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawLineV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 startPos=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 endPos=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawLineV(startPos,endPos,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawLineEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 startPos=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 endPos=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawLineEx(startPos,endPos,thick,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawLineStrip(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 * points=js_getVector2_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawLineStrip((const Vector2  *)points,pointCount,color);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawLineBezier(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 startPos=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 endPos=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawLineBezier(startPos,endPos,thick,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawLineDashed(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 startPos=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 endPos=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int dashSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int spaceSize=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawLineDashed(startPos,endPos,dashSize,spaceSize,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCircle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int centerX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int centerY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCircle(centerX,centerY,radius,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCircleSector(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float startAngle=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float endAngle=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int segments=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCircleSector(center,radius,startAngle,endAngle,segments,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCircleSectorLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float startAngle=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float endAngle=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int segments=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCircleSectorLines(center,radius,startAngle,endAngle,segments,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCircleGradient(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int centerX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int centerY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color inner=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color outer=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCircleGradient(centerX,centerY,radius,inner,outer);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCircleV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCircleV(center,radius,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCircleLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int centerX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int centerY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCircleLines(centerX,centerY,radius,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCircleLinesV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCircleLinesV(center,radius,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawEllipse(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int centerX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int centerY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusH=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusV=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawEllipse(centerX,centerY,radiusH,radiusV,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawEllipseV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusH=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusV=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawEllipseV(center,radiusH,radiusV,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawEllipseLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int centerX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int centerY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusH=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusV=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawEllipseLines(centerX,centerY,radiusH,radiusV,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawEllipseLinesV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusH=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusV=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawEllipseLinesV(center,radiusH,radiusV,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRing(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float innerRadius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float outerRadius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float startAngle=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float endAngle=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int segments=js_getint(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[6],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRing(center,innerRadius,outerRadius,startAngle,endAngle,segments,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRingLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float innerRadius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float outerRadius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float startAngle=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float endAngle=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int segments=js_getint(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[6],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRingLines(center,innerRadius,outerRadius,startAngle,endAngle,segments,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectangle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int posX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectangle(posX,posY,width,height,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectangleV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 position=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 size=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectangleV(position,size,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectangleRec(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle rec=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectangleRec(rec,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectanglePro(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle rec=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 origin=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float rotation=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectanglePro(rec,origin,rotation,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectangleGradientV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int posX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color top=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color bottom=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectangleGradientV(posX,posY,width,height,top,bottom);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectangleGradientH(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int posX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color left=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color right=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectangleGradientH(posX,posY,width,height,left,right);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectangleGradientEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle rec=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color topLeft=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color bottomLeft=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color bottomRight=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color topRight=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectangleGradientEx(rec,topLeft,bottomLeft,bottomRight,topRight);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectangleLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int posX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectangleLines(posX,posY,width,height,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectangleLinesEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle rec=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float lineThick=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectangleLinesEx(rec,lineThick,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectangleRounded(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle rec=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float roundness=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int segments=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectangleRounded(rec,roundness,segments,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectangleRoundedLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle rec=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float roundness=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int segments=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectangleRoundedLines(rec,roundness,segments,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRectangleRoundedLinesEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle rec=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float roundness=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int segments=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float lineThick=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRectangleRoundedLinesEx(rec,roundness,segments,lineThick,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTriangle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v3=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTriangle(v1,v2,v3,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTriangleLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v3=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTriangleLines(v1,v2,v3,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTriangleFan(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 * points=js_getVector2_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTriangleFan((const Vector2  *)points,pointCount,color);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTriangleStrip(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 * points=js_getVector2_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTriangleStrip((const Vector2  *)points,pointCount,color);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawPoly(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int sides=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float rotation=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawPoly(center,sides,radius,rotation,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawPolyLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int sides=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float rotation=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawPolyLines(center,sides,radius,rotation,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawPolyLinesEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int sides=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float rotation=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float lineThick=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawPolyLinesEx(center,sides,radius,rotation,lineThick,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSplineLinear(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 * points=js_getVector2_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSplineLinear((const Vector2  *)points,pointCount,thick,color);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSplineBasis(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 * points=js_getVector2_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSplineBasis((const Vector2  *)points,pointCount,thick,color);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSplineCatmullRom(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 * points=js_getVector2_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSplineCatmullRom((const Vector2  *)points,pointCount,thick,color);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSplineBezierQuadratic(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 * points=js_getVector2_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSplineBezierQuadratic((const Vector2  *)points,pointCount,thick,color);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSplineBezierCubic(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 * points=js_getVector2_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSplineBezierCubic((const Vector2  *)points,pointCount,thick,color);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSplineSegmentLinear(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 p1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSplineSegmentLinear(p1,p2,thick,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSplineSegmentBasis(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 p1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p3=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p4=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSplineSegmentBasis(p1,p2,p3,p4,thick,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSplineSegmentCatmullRom(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 p1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p3=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p4=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSplineSegmentCatmullRom(p1,p2,p3,p4,thick,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSplineSegmentBezierQuadratic(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 p1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 c2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p3=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSplineSegmentBezierQuadratic(p1,c2,p3,thick,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSplineSegmentBezierCubic(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 p1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 c2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 c3=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p4=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float thick=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSplineSegmentBezierCubic(p1,c2,c3,p4,thick,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetSplinePointLinear(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 startPos=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 endPos=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float t=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=GetSplinePointLinear(startPos,endPos,t);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetSplinePointBasis(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 p1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p3=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p4=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float t=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=GetSplinePointBasis(p1,p2,p3,p4,t);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetSplinePointCatmullRom(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 p1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p3=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p4=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float t=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=GetSplinePointCatmullRom(p1,p2,p3,p4,t);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetSplinePointBezierQuad(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 p1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 c2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p3=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float t=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=GetSplinePointBezierQuad(p1,c2,p3,t);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetSplinePointBezierCubic(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 p1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 c2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 c3=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p4=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float t=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=GetSplinePointBezierCubic(p1,c2,c3,p4,t);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_CheckCollisionRecs(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle rec1=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle rec2=js_getRectangle(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionRecs(rec1,rec2);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_CheckCollisionCircles(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius1=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 center2=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float radius2=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionCircles(center1,radius1,center2,radius2);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_CheckCollisionCircleRec(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle rec=js_getRectangle(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionCircleRec(center,radius,rec);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_CheckCollisionCircleLine(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 center=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p1=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p2=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionCircleLine(center,radius,p1,p2);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_CheckCollisionPointRec(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 point=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle rec=js_getRectangle(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionPointRec(point,rec);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_CheckCollisionPointCircle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 point=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 center=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionPointCircle(point,center,radius);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_CheckCollisionPointTriangle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 point=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p1=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p2=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p3=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionPointTriangle(point,p1,p2,p3);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_CheckCollisionPointLine(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 point=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p1=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 p2=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int threshold=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionPointLine(point,p1,p2,threshold);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_CheckCollisionPointPoly(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 point=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 * points=js_getVector2_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionPointPoly(point,(const Vector2  *)points,pointCount);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_CheckCollisionLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 startPos1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 endPos1=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 startPos2=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 endPos2=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		bool collisionPoint_isptr=(bool)false;
		Vector2 * collisionPoint=js_getVector2_ptr(ctx,argv[4],&error,&collisionPoint_isptr);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionLines(startPos1,endPos1,startPos2,endPos2,collisionPoint);
		if(collisionPoint_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Vector2));
			Vector2 * ptr2_src=((Vector2 *)(ptr_src+1));
			ptr2_src[0]=collisionPoint[0];
			JSValue src=JS_NewObjectClass(ctx,js_Vector2_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[4],(uint32_t)0,src);
		}
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetCollisionRec(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle rec1=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle rec2=js_getRectangle(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle returnVal=GetCollisionRec(rec1,rec2);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Rectangle));
		Rectangle * ptr2_ret=((Rectangle *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Rectangle_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadImage(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=LoadImage((const char  *)fileName);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadImageRaw(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int format=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int headerSize=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=LoadImageRaw((const char  *)fileName,width,height,format,headerSize);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadImageAnim(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool frames_isptr=(bool)false;
		int * frames=js_getint_ptr(ctx,argv[1],&error,&frames_isptr);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=LoadImageAnim((const char  *)fileName,frames);
		if(frames_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)frames[0]));
			JS_SetPropertyUint32(ctx,argv[1],(uint32_t)0,src);
		}
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadImageAnimFromMemory(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileType=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char * fileData=js_getunsignedchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool frames_isptr=(bool)false;
		int * frames=js_getint_ptr(ctx,argv[3],&error,&frames_isptr);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=LoadImageAnimFromMemory((const char  *)fileType,(const unsigned char  *)fileData,dataSize,frames);
		if(frames_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)frames[0]));
			JS_SetPropertyUint32(ctx,argv[3],(uint32_t)0,src);
		}
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadImageFromMemory(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileType=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char * fileData=js_getunsignedchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=LoadImageFromMemory((const char  *)fileType,(const unsigned char  *)fileData,dataSize);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadImageFromTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=LoadImageFromTexture(texture);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadImageFromScreen(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Image returnVal=LoadImageFromScreen();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_IsImageValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsImageValid(image);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_UnloadImage(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadImage(image);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ExportImage(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fileName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=ExportImage(image,(const char  *)fileName);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ExportImageToMemory(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fileType=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool fileSize_isptr=(bool)false;
		int * fileSize=js_getint_ptr(ctx,argv[2],&error,&fileSize_isptr);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=ExportImageToMemory(image,(const char  *)fileType,fileSize);
		if(fileSize_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)fileSize[0]));
			JS_SetPropertyUint32(ctx,argv[2],(uint32_t)0,src);
		}
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ExportImageAsCode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fileName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=ExportImageAsCode(image,(const char  *)fileName);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GenImageColor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=GenImageColor(width,height,color);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenImageGradientLinear(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int direction=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color start=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color end=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=GenImageGradientLinear(width,height,direction,start,end);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenImageGradientRadial(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float density=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color inner=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color outer=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=GenImageGradientRadial(width,height,density,inner,outer);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenImageGradientSquare(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float density=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color inner=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color outer=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=GenImageGradientSquare(width,height,density,inner,outer);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenImageChecked(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int checksX=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int checksY=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color col1=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color col2=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=GenImageChecked(width,height,checksX,checksY,col1,col2);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenImageWhiteNoise(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float factor=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=GenImageWhiteNoise(width,height,factor);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenImagePerlinNoise(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int offsetX=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int offsetY=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float scale=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=GenImagePerlinNoise(width,height,offsetX,offsetY,scale);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenImageCellular(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int tileSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=GenImageCellular(width,height,tileSize);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenImageText(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=GenImageText(width,height,(const char  *)text);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ImageCopy(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=ImageCopy(image);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ImageFromImage(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle rec=js_getRectangle(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=ImageFromImage(image,rec);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ImageFromChannel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int selectedChannel=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=ImageFromChannel(image,selectedChannel);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ImageText(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int fontSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=ImageText((const char  *)text,fontSize,color);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ImageTextEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float fontSize=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float spacing=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=ImageTextEx(font,(const char  *)text,fontSize,spacing,tint);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ImageFormat(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		int newFormat=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		ImageFormat(image,newFormat);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageToPOT(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		Color fill=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		ImageToPOT(image,fill);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageCrop(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		Rectangle crop=js_getRectangle(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		ImageCrop(image,crop);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageAlphaCrop(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		float threshold=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		ImageAlphaCrop(image,threshold);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageAlphaClear(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float threshold=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		ImageAlphaClear(image,color,threshold);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageAlphaMask(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		Image alphaMask=js_getImage(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		ImageAlphaMask(image,alphaMask);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageAlphaPremultiply(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		ImageAlphaPremultiply(image);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageBlurGaussian(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		int blurSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		ImageBlurGaussian(image,blurSize);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageKernelConvolution(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		float * kernel=js_getfloat_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int kernelSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		ImageKernelConvolution(image,(const float  *)kernel,kernelSize);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageResize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		int newWidth=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int newHeight=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		ImageResize(image,newWidth,newHeight);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageResizeNN(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		int newWidth=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int newHeight=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		ImageResizeNN(image,newWidth,newHeight);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageResizeCanvas(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		int newWidth=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int newHeight=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int offsetX=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int offsetY=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color fill=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		ImageResizeCanvas(image,newWidth,newHeight,offsetX,offsetY,fill);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageMipmaps(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		ImageMipmaps(image);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDither(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		int rBpp=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int gBpp=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int bBpp=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int aBpp=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDither(image,rBpp,gBpp,bBpp,aBpp);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageFlipVertical(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		ImageFlipVertical(image);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageFlipHorizontal(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		ImageFlipHorizontal(image);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageRotate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		int degrees=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		ImageRotate(image,degrees);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageRotateCW(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		ImageRotateCW(image);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageRotateCCW(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		ImageRotateCCW(image);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageColorTint(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		ImageColorTint(image,color);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageColorInvert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		ImageColorInvert(image);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageColorGrayscale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		ImageColorGrayscale(image);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageColorContrast(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		float contrast=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		ImageColorContrast(image,contrast);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageColorBrightness(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		int brightness=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		ImageColorBrightness(image,brightness);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageColorReplace(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool image_isptr=(bool)false;
		Image * image=js_getImage_ptr(ctx,argv[0],&error,&image_isptr);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color replace=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		ImageColorReplace(image,color,replace);
		if(image_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=image[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadImageColors(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color * colors=LoadImageColors(image);
		JSValue retVal=JS_NewArrayBufferCopy(ctx,(const uint8_t  *)colors,image.width*image.height*sizeof(Color));
		UnloadImageColors(colors);
		memoryClear(ctx);
		return retVal;
	}
	
	static JSValue js_LoadImagePalette(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int maxPaletteSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * colorCount=js_getint_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color * returnVal=LoadImagePalette(image,maxPaletteSize,colorCount);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color *));
		Color * * ptr2_ret=((Color * *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_UnloadImageColors(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color * colors=js_getColor_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadImageColors(colors);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UnloadImagePalette(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color * colors=js_getColor_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadImagePalette(colors);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetImageAlphaBorder(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float threshold=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle returnVal=GetImageAlphaBorder(image,threshold);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Rectangle));
		Rectangle * ptr2_ret=((Rectangle *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Rectangle_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetImageColor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int x=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int y=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=GetImageColor(image,x,y);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ImageClearBackground(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		ImageClearBackground(dst,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawPixel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		int posX=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawPixel(dst,posX,posY,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawPixelV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector2 position=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawPixelV(dst,position,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawLine(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		int startPosX=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int startPosY=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int endPosX=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int endPosY=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawLine(dst,startPosX,startPosY,endPosX,endPosY,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawLineV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector2 start=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 end=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawLineV(dst,start,end,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawLineEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector2 start=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 end=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int thick=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawLineEx(dst,start,end,thick,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawCircle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		int centerX=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int centerY=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int radius=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawCircle(dst,centerX,centerY,radius,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawCircleV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector2 center=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int radius=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawCircleV(dst,center,radius,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawCircleLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		int centerX=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int centerY=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int radius=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawCircleLines(dst,centerX,centerY,radius,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawCircleLinesV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector2 center=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int radius=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawCircleLinesV(dst,center,radius,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawRectangle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		int posX=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawRectangle(dst,posX,posY,width,height,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawRectangleV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector2 position=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 size=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawRectangleV(dst,position,size,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawRectangleRec(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Rectangle rec=js_getRectangle(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawRectangleRec(dst,rec,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawRectangleLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Rectangle rec=js_getRectangle(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int thick=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawRectangleLines(dst,rec,thick,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawTriangle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector2 v1=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v3=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawTriangle(dst,v1,v2,v3,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawTriangleEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector2 v1=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v3=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color c1=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color c2=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		Color c3=js_getColor(ctx,argv[6],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawTriangleEx(dst,v1,v2,v3,c1,c2,c3);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawTriangleLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector2 v1=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v3=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawTriangleLines(dst,v1,v2,v3,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawTriangleFan(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector2 * points=js_getVector2_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawTriangleFan(dst,(const Vector2  *)points,pointCount,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawTriangleStrip(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector2 * points=js_getVector2_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawTriangleStrip(dst,(const Vector2  *)points,pointCount,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDraw(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Image src=js_getImage(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle srcRec=js_getRectangle(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle dstRec=js_getRectangle(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDraw(dst,src,srcRec,dstRec,tint);
		if(dst_isptr==0){
			opaqueShadow * ptr_src0=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src0=((Image *)(ptr_src0+1));
			ptr2_src0[0]=dst[0];
			JSValue src0=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src0,(void  *)ptr_src0);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src0);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawText(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int posX=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int fontSize=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawText(dst,(const char  *)text,posX,posY,fontSize,color);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ImageDrawTextEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool dst_isptr=(bool)false;
		Image * dst=js_getImage_ptr(ctx,argv[0],&error,&dst_isptr);
		if(error==1)return JS_EXCEPTION;
		Font font=js_getFont(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 position=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float fontSize=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		float spacing=js_getfloat(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[6],&error);
		if(error==1)return JS_EXCEPTION;
		ImageDrawTextEx(dst,font,(const char  *)text,position,fontSize,spacing,tint);
		if(dst_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Image));
			Image * ptr2_src=((Image *)(ptr_src+1));
			ptr2_src[0]=dst[0];
			JSValue src=JS_NewObjectClass(ctx,js_Image_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Texture2D returnVal=LoadTexture((const char  *)fileName);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Texture2D));
		Texture2D * ptr2_ret=((Texture2D *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Texture_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadTextureFromImage(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Texture2D returnVal=LoadTextureFromImage(image);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Texture2D));
		Texture2D * ptr2_ret=((Texture2D *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Texture_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadTextureCubemap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int layout=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		TextureCubemap returnVal=LoadTextureCubemap(image,layout);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(TextureCubemap));
		TextureCubemap * ptr2_ret=((TextureCubemap *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Texture_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadRenderTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		RenderTexture2D returnVal=LoadRenderTexture(width,height);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(RenderTexture2D));
		RenderTexture2D * ptr2_ret=((RenderTexture2D *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_RenderTexture_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_IsTextureValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsTextureValid(texture);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_UnloadTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadTexture(texture);
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsRenderTextureValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		RenderTexture2D target=js_getRenderTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsRenderTextureValid(target);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_UnloadRenderTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		RenderTexture2D target=js_getRenderTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadRenderTexture(target);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UpdateTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		void * pixels=js_getvoid_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		UpdateTexture(texture,(const void  *)pixels);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UpdateTextureRec(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle rec=js_getRectangle(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		void * pixels=js_getvoid_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		UpdateTextureRec(texture,rec,(const void  *)pixels);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GenTextureMipmaps(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool texture_isptr=(bool)false;
		Texture2D * texture=js_getTexture2D_ptr(ctx,argv[0],&error,&texture_isptr);
		if(error==1)return JS_EXCEPTION;
		GenTextureMipmaps(texture);
		if(texture_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Texture2D));
			Texture2D * ptr2_src=((Texture2D *)(ptr_src+1));
			ptr2_src[0]=texture[0];
			JSValue src=JS_NewObjectClass(ctx,js_Texture_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetTextureFilter(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int filter=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetTextureFilter(texture,filter);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetTextureWrap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int wrap=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetTextureWrap(texture,wrap);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int posX=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTexture(texture,posX,posY,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTextureV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 position=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTextureV(texture,position,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTextureEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 position=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float rotation=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float scale=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTextureEx(texture,position,rotation,scale,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTextureRec(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle source=js_getRectangle(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 position=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTextureRec(texture,source,position,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTexturePro(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle source=js_getRectangle(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle dest=js_getRectangle(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 origin=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float rotation=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTexturePro(texture,source,dest,origin,rotation,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTextureNPatch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Texture2D texture=js_getTexture2D(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		NPatchInfo nPatchInfo=js_getNPatchInfo(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle dest=js_getRectangle(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 origin=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float rotation=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTextureNPatch(texture,nPatchInfo,dest,origin,rotation,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ColorIsEqual(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color col1=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color col2=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=ColorIsEqual(col1,col2);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_Fade(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color color=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float alpha=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=Fade(color,alpha);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ColorToInt(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color color=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=ColorToInt(color);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_ColorNormalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color color=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=ColorNormalize(color);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector4));
		Vector4 * ptr2_ret=((Vector4 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector4_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ColorFromNormalized(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 normalized=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=ColorFromNormalized(normalized);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ColorToHSV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color color=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=ColorToHSV(color);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector3));
		Vector3 * ptr2_ret=((Vector3 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ColorFromHSV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float hue=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float saturation=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float value=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=ColorFromHSV(hue,saturation,value);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ColorTint(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color color=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=ColorTint(color,tint);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ColorBrightness(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color color=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float factor=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=ColorBrightness(color,factor);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ColorContrast(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color color=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float contrast=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=ColorContrast(color,contrast);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ColorAlpha(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color color=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float alpha=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=ColorAlpha(color,alpha);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ColorAlphaBlend(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color dst=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color src=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=ColorAlphaBlend(dst,src,tint);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_ColorLerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color color1=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color color2=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float factor=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=ColorLerp(color1,color2,factor);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetColor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int hexValue=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=GetColor(hexValue);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetPixelColor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * srcPtr=js_getvoid_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int format=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color returnVal=GetPixelColor(srcPtr,format);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ret=((Color *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_SetPixelColor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * dstPtr=js_getvoid_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int format=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		SetPixelColor(dstPtr,color,format);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetPixelDataSize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int format=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetPixelDataSize(width,height,format);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetFontDefault(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Font returnVal=GetFontDefault();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Font));
		Font * ptr2_ret=((Font *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Font_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadFont(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Font returnVal=LoadFont((const char  *)fileName);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Font));
		Font * ptr2_ret=((Font *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Font_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadFontEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int fontSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * codepoints=js_getint_arrnull(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int codepointCount=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Font returnVal=LoadFontEx((const char  *)fileName,fontSize,(const int  *)codepoints,codepointCount);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Font));
		Font * ptr2_ret=((Font *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Font_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadFontFromImage(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image image=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color key=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int firstChar=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Font returnVal=LoadFontFromImage(image,key,firstChar);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Font));
		Font * ptr2_ret=((Font *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Font_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadFontFromMemory(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileType=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char * fileData=js_getunsignedchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int fontSize=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int * codepoints=js_getint_arr(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int codepointCount=js_getint(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		Font returnVal=LoadFontFromMemory((const char  *)fileType,(const unsigned char  *)fileData,dataSize,fontSize,(const int  *)codepoints,codepointCount);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Font));
		Font * ptr2_ret=((Font *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Font_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_IsFontValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsFontValid(font);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_LoadFontData(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned char * fileData=js_getunsignedchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int fontSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int * codepoints=js_getint_arrnull(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int codepointCount=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int type=js_getint(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		int * glyphCount=js_getint_arr(ctx,argv[6],&error);
		if(error==1)return JS_EXCEPTION;
		GlyphInfo * returnVal=LoadFontData((const unsigned char  *)fileData,dataSize,fontSize,(const int  *)codepoints,codepointCount,type,glyphCount);
		JSValue ret=JS_NewArray(ctx);
		size_t size0;
		if(codepointCount>0){
			size0=(size_t)codepointCount;
		}else{
			size0=(size_t)95;
		}
		for(int i=0;i<size0;i++){
			GlyphInfo src0=returnVal[i];
			opaqueShadow * ptr_ret1=create_shadow_with_data(sizeof(GlyphInfo));
			GlyphInfo * ptr2_ret1=((GlyphInfo *)(ptr_ret1+1));
			ptr2_ret1[0]=src0;
			JSValue ret1=JS_NewObjectClass(ctx,js_GlyphInfo_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GenImageFontAtlas(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		GlyphInfo * glyphs=js_getGlyphInfo_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle * * glyphRecs;
		void * target;
		glyphRecs=(Rectangle  * *)&target;
		int glyphCount=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int fontSize=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int padding=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int packMethod=js_getint(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=GenImageFontAtlas((const GlyphInfo  *)glyphs,glyphRecs,glyphCount,fontSize,padding,packMethod);
		for(int i=0;i<glyphCount;i++){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Rectangle));
			Rectangle * ptr2_src=((Rectangle *)(ptr_src+1));
			ptr2_src[0]=glyphRecs[0][i];
			JSValue src=JS_NewObjectClass(ctx,js_Rectangle_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[1],(uint32_t)i,src);
		}
		jsc_free(ctx,(void  *)glyphRecs[0]);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_UnloadFontData(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		GlyphInfo * glyphs=js_getGlyphInfo_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int glyphCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadFontData(glyphs,glyphCount);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UnloadFont(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadFont(font);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ExportFontAsCode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fileName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=ExportFontAsCode(font,(const char  *)fileName);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_DrawFPS(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int posX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		DrawFPS(posX,posY);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawText(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int posX=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int fontSize=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawText((const char  *)text,posX,posY,fontSize,color);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTextEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 position=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float fontSize=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float spacing=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTextEx(font,(const char  *)text,position,fontSize,spacing,tint);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTextPro(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 position=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 origin=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float rotation=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		float fontSize=js_getfloat(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		float spacing=js_getfloat(ctx,argv[6],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[7],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTextPro(font,(const char  *)text,position,origin,rotation,fontSize,spacing,tint);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTextCodepoint(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int codepoint=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 position=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float fontSize=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTextCodepoint(font,codepoint,position,fontSize,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTextCodepoints(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int * codepoints=js_getint_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int codepointCount=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 position=js_getVector2(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float fontSize=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		float spacing=js_getfloat(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[6],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTextCodepoints(font,(const int  *)codepoints,codepointCount,position,fontSize,spacing,tint);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetTextLineSpacing(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int spacing=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetTextLineSpacing(spacing);
		return JS_UNDEFINED;
	}
	
	static JSValue js_MeasureText(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int fontSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=MeasureText((const char  *)text,fontSize);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_MeasureTextEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float fontSize=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float spacing=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=MeasureTextEx(font,(const char  *)text,fontSize,spacing);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector2));
		Vector2 * ptr2_ret=((Vector2 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector2_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetGlyphIndex(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int codepoint=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetGlyphIndex(font,codepoint);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GetGlyphInfo(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int codepoint=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		GlyphInfo returnVal=GetGlyphInfo(font,codepoint);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(GlyphInfo));
		GlyphInfo * ptr2_ret=((GlyphInfo *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_GlyphInfo_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetGlyphAtlasRec(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int codepoint=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle returnVal=GetGlyphAtlasRec(font,codepoint);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Rectangle));
		Rectangle * ptr2_ret=((Rectangle *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Rectangle_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadUTF8(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int * codepoints=js_getint_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int length=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=LoadUTF8((const int  *)codepoints,length);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_UnloadUTF8(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadUTF8(text);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadCodepoints(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool count_isptr=(bool)false;
		int * count=js_getint_ptr(ctx,argv[1],&error,&count_isptr);
		if(error==1)return JS_EXCEPTION;
		int * returnVal=LoadCodepoints((const char  *)text,count);
		if(count_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)count[0]));
			JS_SetPropertyUint32(ctx,argv[1],(uint32_t)0,src);
		}
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<count[0];i++){
			int src0=returnVal[i];
			JSValue ret1=JS_NewInt32(ctx,(int32_t)((long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetCodepointCount(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetCodepointCount((const char  *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetCodepoint(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool codepointSize_isptr=(bool)false;
		int * codepointSize=js_getint_ptr(ctx,argv[1],&error,&codepointSize_isptr);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetCodepoint((const char  *)text,codepointSize);
		if(codepointSize_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)codepointSize[0]));
			JS_SetPropertyUint32(ctx,argv[1],(uint32_t)0,src);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetCodepointNext(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool codepointSize_isptr=(bool)false;
		int * codepointSize=js_getint_ptr(ctx,argv[1],&error,&codepointSize_isptr);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetCodepointNext((const char  *)text,codepointSize);
		if(codepointSize_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)codepointSize[0]));
			JS_SetPropertyUint32(ctx,argv[1],(uint32_t)0,src);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetCodepointPrevious(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool codepointSize_isptr=(bool)false;
		int * codepointSize=js_getint_ptr(ctx,argv[1],&error,&codepointSize_isptr);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GetCodepointPrevious((const char  *)text,codepointSize);
		if(codepointSize_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)codepointSize[0]));
			JS_SetPropertyUint32(ctx,argv[1],(uint32_t)0,src);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_CodepointToUTF8(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int codepoint=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int * utf8Size=js_getint_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)CodepointToUTF8(codepoint,utf8Size);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadTextLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool count_isptr=(bool)false;
		int * count=js_getint_ptr(ctx,argv[1],&error,&count_isptr);
		if(error==1)return JS_EXCEPTION;
		char * * returnVal=LoadTextLines((const char  *)text,count);
		if(count_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)count[0]));
			JS_SetPropertyUint32(ctx,argv[1],(uint32_t)0,src);
		}
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<count[0];i++){
			char * src0=returnVal[i];
			JSValue ret1=JS_NewString(ctx,(const char  *)src0);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_UnloadTextLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * * text=js_getchar_arr_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int lineCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadTextLines(text,lineCount);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_TextIsEqual(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text1=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text2=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=TextIsEqual((const char  *)text1,(const char  *)text2);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextLength(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=TextLength((const char  *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextFormat(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		size_t char_ptrlen=(size_t)10;
		char * char_ptr=(char  *)js_calloc(ctx,char_ptrlen,sizeof(char));
		int64_t formatlen;
		if(JS_GetLength(ctx,argv[0],&formatlen)==-1){
			memoryClear(ctx);
			js_free(ctx,(void  *)char_ptr);
			return JS_EXCEPTION;
		}
		char * format=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * subformat=format;
		size_t subformatlen=(size_t)0;
		char subformatlenh;
		size_t bufferlen=formatlen*2;
		char * buffer=(char  *)js_calloc(ctx,bufferlen,sizeof(char));
		int l=(int)0;
		int c=(int)1;
		int ilen=(int)0;
		for(int i=0;i<formatlen;i++){
			if(format[i]!='%'){
				buffer[l]=format[i];
				l +=1;
			}else{
				int n=(int)2;
				int w=(int)0;
				int p=(int)0;
				int firsth=(int)i+1;
				char har=format[firsth];
				if(har==0){
					JSValue ret=JS_NewString(ctx,(const char  *)buffer);
					memoryClear(ctx);
					js_free(ctx,(void  *)char_ptr);
					js_free(ctx,(void  *)buffer);
					return ret;
				}
				while(!(har>=97&&har<=122)&&!(har>=65&&har<=90)&&har!='%'){
					firsth +=1;
					har =format[firsth];
					if(har==0){
						JSValue ret=JS_NewString(ctx,(const char  *)buffer);
						memoryClear(ctx);
						js_free(ctx,(void  *)char_ptr);
						js_free(ctx,(void  *)buffer);
						return ret;
					}
				}
				int lasth=firsth;
				har=format[lasth];
				while(strchr("diuoxXfFeEfFeEgGaAcspn%", har)==NULL){
					if(har=='*'){
						if(n==1){
							w =p;
						}
						p =js_getint(ctx,argv[c],&error);
						if(error==1)return JS_EXCEPTION;
						c +=1;
						n -=1;
					}
					lasth +=1;
					har =format[lasth];
					if(har==0){
						JSValue ret=JS_NewString(ctx,(const char  *)buffer);
						memoryClear(ctx);
						js_free(ctx,(void  *)char_ptr);
						js_free(ctx,(void  *)buffer);
						return ret;
					}
				}
				subformatlen =lasth-i+1;
				subformatlenh =format[lasth+1];
				subformat =format+i;
				subformat[subformatlen]=(char)0;
				if(format[lasth]=='%'){
					i =lasth;
					buffer[l]='%';
					l +=1;
					continue;
				}
				memset((void  *)char_ptr,(int)0,ilen*sizeof(char));
				if(har=='d'||har=='i'){
					int64_t a=js_getint64_t(ctx,argv[c],&error);
					if(error==1)return JS_EXCEPTION;
					if(firsth==lasth){
						char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(int)a);
					}else{
						if(format[lasth-1]=='h'){
							if(subformat[lasth-i-2]=='h'){
								char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(signed char)a);
							}else{
								char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(short int)a);
							}
						}else if(format[lasth-1]=='l'){
							if(subformat[lasth-i-2]=='l'){
								char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(long long int)a);
							}else{
								char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(long int)a);
							}
						}else if(format[lasth-1]=='j'){
							char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(intmax_t)a);
						}else if(format[lasth-1]=='z'){
							char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(size_t)a);
						}else if(format[lasth-1]=='t'){
							char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(ptrdiff_t)a);
						}
					}
				}else if(har=='u'||har=='o'||har=='x'||har=='X'){
					uint32_t a=js_getuint32_t(ctx,argv[c],&error);
					if(error==1)return JS_EXCEPTION;
					if(firsth==lasth){
						char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(unsigned int)a);
					}else{
						if(subformat[lasth-i-1]=='h'){
							if(subformat[lasth-i-2]=='h'){
								char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(unsigned char)a);
							}else{
								char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(unsigned short int)a);
							}
						}else if(subformat[lasth-i-1]=='l'){
							if(subformat[lasth-i-2]=='l'){
								char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(unsigned long long int)a);
							}else{
								char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(unsigned long int)a);
							}
						}else if(subformat[lasth-i-1]=='j'){
							char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(uintmax_t)a);
						}else if(subformat[lasth-i-1]=='z'){
							char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(size_t)a);
						}else if(subformat[lasth-i-1]=='t'){
							char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(ptrdiff_t)a);
						}
					}
				}else if(har=='f'||har=='F'||har=='e'||har=='E'||har=='g'||har=='G'||har=='a'||har=='A'){
					double a=js_getdouble(ctx,argv[c],&error);
					if(error==1)return JS_EXCEPTION;
					if(firsth==lasth){
						char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(double)a);
					}else{
						char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(long double)a);
					}
				}else if(har=='c'){
					char a=js_getchar(ctx,argv[c],&error);
					if(error==1)return JS_EXCEPTION;
					if(firsth==lasth){
						char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(int)a);
					}else{
						char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(wint_t)a);
					}
				}else if(har=='s'){
					if(firsth==lasth){
						char * a=js_getchar_arr(ctx,argv[c],&error);
						if(error==1)return JS_EXCEPTION;
						char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,a);
					}else{
						wchar_t * a=js_getwchar_t_arr(ctx,argv[c],&error);
						if(error==1)return JS_EXCEPTION;
						char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,a);
					}
				}else if(har=='p'){
					char_ptr =asnprintf(ctx,char_ptr,&char_ptrlen,(const char  *)subformat,n,w,p,(void *)&argv[c]);
				}else if(har=='n'){
					argv[c] =JS_NewInt32(ctx,(int32_t)((long)l));
				}
				subformat[subformatlen]=subformatlenh;
				c +=1;
				ilen =(int)strlen((const char  *)char_ptr);
				int maxstrlen=(int)formatlen+l+ilen-lasth;
				if(bufferlen<maxstrlen){
					buffer =(char  *)js_realloc(ctx,(void  *)buffer,(size_t)maxstrlen);
					memset((void  *)buffer+bufferlen,(int)0,maxstrlen-bufferlen);
					bufferlen =(size_t)maxstrlen;
				}
				strncpy(buffer+l,(const char  *)char_ptr,(size_t)ilen);
				l +=ilen;
				i =lasth;
			}
		}
		JSValue js_buffer=JS_NewString(ctx,(const char  *)buffer);
		memoryClear(ctx);
		js_free(ctx,(void  *)char_ptr);
		js_free(ctx,(void  *)buffer);
		return js_buffer;
	}
	
	static JSValue js_TextSubtext(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int position=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int length=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)TextSubtext((const char  *)text,position,length);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextRemoveSpaces(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)TextRemoveSpaces((const char  *)text);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GetTextBetween(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * begin=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * end=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=GetTextBetween((const char  *)text,(const char  *)begin,(const char  *)end);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextReplace(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * search=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * replacement=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=TextReplace((const char  *)text,(const char  *)search,(const char  *)replacement);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextReplaceBetween(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * begin=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * end=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		char * replacement=js_getchar_arr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=TextReplaceBetween((const char  *)text,(const char  *)begin,(const char  *)end,(const char  *)replacement);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextInsert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * insert=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int position=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=TextInsert((const char  *)text,(const char  *)insert,position);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextJoin(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * * textList=js_getchar_arr_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int count=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * delimiter=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=TextJoin(textList,count,(const char  *)delimiter);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextSplit(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char delimiter=js_getchar(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool count_isptr=(bool)false;
		int * count=js_getint_ptr(ctx,argv[2],&error,&count_isptr);
		if(error==1)return JS_EXCEPTION;
		char * * returnVal=TextSplit((const char  *)text,delimiter,count);
		if(count_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)count[0]));
			JS_SetPropertyUint32(ctx,argv[2],(uint32_t)0,src);
		}
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<count[0];i++){
			char * src0=returnVal[i];
			JSValue ret1=JS_NewString(ctx,(const char  *)src0);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextAppend(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * append=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool position_isptr=(bool)false;
		int * position=js_getint_ptr(ctx,argv[2],&error,&position_isptr);
		if(error==1)return JS_EXCEPTION;
		TextAppend(text,(const char  *)append,position);
		if(position_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)position[0]));
			JS_SetPropertyUint32(ctx,argv[2],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_TextFindIndex(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * search=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=TextFindIndex((const char  *)text,(const char  *)search);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextToUpper(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=TextToUpper((const char  *)text);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextToLower(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=TextToLower((const char  *)text);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextToPascal(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=TextToPascal((const char  *)text);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextToSnake(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=TextToSnake((const char  *)text);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextToCamel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=TextToCamel((const char  *)text);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextToInteger(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=TextToInteger((const char  *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_TextToFloat(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=TextToFloat((const char  *)text);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_DrawLine3D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 startPos=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 endPos=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawLine3D(startPos,endPos,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawPoint3D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 position=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		DrawPoint3D(position,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCircle3D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 center=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 rotationAxis=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float rotationAngle=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCircle3D(center,radius,rotationAxis,rotationAngle,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTriangle3D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v3=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTriangle3D(v1,v2,v3,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawTriangleStrip3D(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 * points=js_getVector3_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int pointCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawTriangleStrip3D((const Vector3  *)points,pointCount,color);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCube(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 position=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float width=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float height=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float length=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCube(position,width,height,length,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCubeV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 position=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 size=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCubeV(position,size,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCubeWires(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 position=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float width=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float height=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float length=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCubeWires(position,width,height,length,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCubeWiresV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 position=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 size=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCubeWiresV(position,size,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSphere(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 centerPos=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSphere(centerPos,radius,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSphereEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 centerPos=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int rings=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int slices=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSphereEx(centerPos,radius,rings,slices,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawSphereWires(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 centerPos=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int rings=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int slices=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawSphereWires(centerPos,radius,rings,slices,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCylinder(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 position=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusTop=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusBottom=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float height=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int slices=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCylinder(position,radiusTop,radiusBottom,height,slices,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCylinderEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 startPos=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 endPos=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float startRadius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float endRadius=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int sides=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCylinderEx(startPos,endPos,startRadius,endRadius,sides,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCylinderWires(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 position=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusTop=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radiusBottom=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float height=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int slices=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCylinderWires(position,radiusTop,radiusBottom,height,slices,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCylinderWiresEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 startPos=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 endPos=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float startRadius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float endRadius=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int sides=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCylinderWiresEx(startPos,endPos,startRadius,endRadius,sides,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCapsule(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 startPos=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 endPos=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int slices=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int rings=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCapsule(startPos,endPos,radius,slices,rings,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawCapsuleWires(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 startPos=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 endPos=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int slices=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int rings=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawCapsuleWires(startPos,endPos,radius,slices,rings,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawPlane(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 centerPos=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 size=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawPlane(centerPos,size,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawRay(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Ray ray=js_getRay(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		DrawRay(ray,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawGrid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int slices=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float spacing=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		DrawGrid(slices,spacing);
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadModel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Model returnVal=LoadModel((const char  *)fileName);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Model));
		Model * ptr2_ret=((Model *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Model_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadModelFromMesh(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Mesh mesh=js_getMesh(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Model returnVal=LoadModelFromMesh(mesh);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Model));
		Model * ptr2_ret=((Model *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Model_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_IsModelValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsModelValid(model);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_UnloadModel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadModel(model);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetModelBoundingBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		BoundingBox returnVal=GetModelBoundingBox(model);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(BoundingBox));
		BoundingBox * ptr2_ret=((BoundingBox *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_BoundingBox_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_DrawModel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 position=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float scale=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawModel(model,position,scale,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawModelEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 position=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 rotationAxis=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float rotationAngle=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 scale=js_getVector3(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawModelEx(model,position,rotationAxis,rotationAngle,scale,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawModelWires(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 position=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float scale=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawModelWires(model,position,scale,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawModelWiresEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 position=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 rotationAxis=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float rotationAngle=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 scale=js_getVector3(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawModelWiresEx(model,position,rotationAxis,rotationAngle,scale,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawModelPoints(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 position=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float scale=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawModelPoints(model,position,scale,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawModelPointsEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 position=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 rotationAxis=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float rotationAngle=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 scale=js_getVector3(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawModelPointsEx(model,position,rotationAxis,rotationAngle,scale,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawBoundingBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		BoundingBox box=js_getBoundingBox(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		DrawBoundingBox(box,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawBillboard(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera camera=js_getCamera(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Texture2D texture=js_getTexture2D(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 position=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float scale=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		DrawBillboard(camera,texture,position,scale,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawBillboardRec(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera camera=js_getCamera(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Texture2D texture=js_getTexture2D(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle source=js_getRectangle(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 position=js_getVector3(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 size=js_getVector2(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		DrawBillboardRec(camera,texture,source,position,size,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawBillboardPro(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera camera=js_getCamera(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Texture2D texture=js_getTexture2D(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle source=js_getRectangle(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 position=js_getVector3(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 up=js_getVector3(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 size=js_getVector2(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 origin=js_getVector2(ctx,argv[6],&error);
		if(error==1)return JS_EXCEPTION;
		float rotation=js_getfloat(ctx,argv[7],&error);
		if(error==1)return JS_EXCEPTION;
		Color tint=js_getColor(ctx,argv[8],&error);
		if(error==1)return JS_EXCEPTION;
		DrawBillboardPro(camera,texture,source,position,up,size,origin,rotation,tint);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UploadMesh(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool mesh_isptr=(bool)false;
		Mesh * mesh=js_getMesh_ptr(ctx,argv[0],&error,&mesh_isptr);
		if(error==1)return JS_EXCEPTION;
		bool dynamic=js_getbool(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		UploadMesh(mesh,dynamic);
		if(mesh_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Mesh));
			Mesh * ptr2_src=((Mesh *)(ptr_src+1));
			ptr2_src[0]=mesh[0];
			JSValue src=JS_NewObjectClass(ctx,js_Mesh_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UpdateMeshBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Mesh mesh=js_getMesh(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int index=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		void * data=js_getvoid_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int offset=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		UpdateMeshBuffer(mesh,index,(const void  *)data,dataSize,offset);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UnloadMesh(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Mesh mesh=js_getMesh(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadMesh(mesh);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawMesh(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Mesh mesh=js_getMesh(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Material material=js_getMaterial(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix transform=js_getMatrix(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		DrawMesh(mesh,material,transform);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DrawMeshInstanced(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Mesh mesh=js_getMesh(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Material material=js_getMaterial(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix * transforms=js_getMatrix_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int instances=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		DrawMeshInstanced(mesh,material,(const Matrix  *)transforms,instances);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetMeshBoundingBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Mesh mesh=js_getMesh(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		BoundingBox returnVal=GetMeshBoundingBox(mesh);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(BoundingBox));
		BoundingBox * ptr2_ret=((BoundingBox *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_BoundingBox_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenMeshTangents(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool mesh_isptr=(bool)false;
		Mesh * mesh=js_getMesh_ptr(ctx,argv[0],&error,&mesh_isptr);
		if(error==1)return JS_EXCEPTION;
		GenMeshTangents(mesh);
		if(mesh_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Mesh));
			Mesh * ptr2_src=((Mesh *)(ptr_src+1));
			ptr2_src[0]=mesh[0];
			JSValue src=JS_NewObjectClass(ctx,js_Mesh_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ExportMesh(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Mesh mesh=js_getMesh(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fileName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=ExportMesh(mesh,(const char  *)fileName);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ExportMeshAsCode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Mesh mesh=js_getMesh(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fileName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=ExportMeshAsCode(mesh,(const char  *)fileName);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_GenMeshPoly(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int sides=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh returnVal=GenMeshPoly(sides,radius);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Mesh));
		Mesh * ptr2_ret=((Mesh *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenMeshPlane(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float width=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float length=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int resX=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int resZ=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh returnVal=GenMeshPlane(width,length,resX,resZ);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Mesh));
		Mesh * ptr2_ret=((Mesh *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenMeshCube(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float width=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float height=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float length=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh returnVal=GenMeshCube(width,height,length);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Mesh));
		Mesh * ptr2_ret=((Mesh *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenMeshSphere(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float radius=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int rings=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int slices=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh returnVal=GenMeshSphere(radius,rings,slices);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Mesh));
		Mesh * ptr2_ret=((Mesh *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenMeshHemiSphere(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float radius=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int rings=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int slices=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh returnVal=GenMeshHemiSphere(radius,rings,slices);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Mesh));
		Mesh * ptr2_ret=((Mesh *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenMeshCylinder(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float radius=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float height=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int slices=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh returnVal=GenMeshCylinder(radius,height,slices);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Mesh));
		Mesh * ptr2_ret=((Mesh *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenMeshCone(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float radius=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float height=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int slices=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh returnVal=GenMeshCone(radius,height,slices);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Mesh));
		Mesh * ptr2_ret=((Mesh *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenMeshTorus(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float radius=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float size=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int radSeg=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int sides=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh returnVal=GenMeshTorus(radius,size,radSeg,sides);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Mesh));
		Mesh * ptr2_ret=((Mesh *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenMeshKnot(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float radius=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float size=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int radSeg=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int sides=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh returnVal=GenMeshKnot(radius,size,radSeg,sides);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Mesh));
		Mesh * ptr2_ret=((Mesh *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenMeshHeightmap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image heightmap=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 size=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh returnVal=GenMeshHeightmap(heightmap,size);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Mesh));
		Mesh * ptr2_ret=((Mesh *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GenMeshCubicmap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Image cubicmap=js_getImage(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 cubeSize=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh returnVal=GenMeshCubicmap(cubicmap,cubeSize);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Mesh));
		Mesh * ptr2_ret=((Mesh *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Mesh_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadMaterials(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int * materialCount=js_getint_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Material * returnVal=LoadMaterials((const char  *)fileName,materialCount);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Material *));
		Material * * ptr2_ret=((Material * *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Material_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadMaterialDefault(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Material returnVal=LoadMaterialDefault();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Material));
		Material * ptr2_ret=((Material *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Material_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_IsMaterialValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Material material=js_getMaterial(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsMaterialValid(material);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_UnloadMaterial(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Material material=js_getMaterial(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadMaterial(material);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetMaterialTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool material_isptr=(bool)false;
		Material * material=js_getMaterial_ptr(ctx,argv[0],&error,&material_isptr);
		if(error==1)return JS_EXCEPTION;
		int mapType=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Texture2D texture=js_getTexture2D(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		SetMaterialTexture(material,mapType,texture);
		if(material_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Material));
			Material * ptr2_src=((Material *)(ptr_src+1));
			ptr2_src[0]=material[0];
			JSValue src=JS_NewObjectClass(ctx,js_Material_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetModelMeshMaterial(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool model_isptr=(bool)false;
		Model * model=js_getModel_ptr(ctx,argv[0],&error,&model_isptr);
		if(error==1)return JS_EXCEPTION;
		int meshId=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int materialId=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		SetModelMeshMaterial(model,meshId,materialId);
		if(model_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Model));
			Model * ptr2_src=((Model *)(ptr_src+1));
			ptr2_src[0]=model[0];
			JSValue src=JS_NewObjectClass(ctx,js_Model_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadModelAnimations(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool animCount_isptr=(bool)false;
		int * animCount=js_getint_ptr(ctx,argv[1],&error,&animCount_isptr);
		if(error==1)return JS_EXCEPTION;
		ModelAnimation * returnVal=LoadModelAnimations((const char  *)fileName,animCount);
		if(animCount_isptr==0){
			JSValue src=JS_NewInt32(ctx,(int32_t)((long)animCount[0]));
			JS_SetPropertyUint32(ctx,argv[1],(uint32_t)0,src);
		}
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<animCount[0];i++){
			ModelAnimation src0=returnVal[i];
			opaqueShadow * ptr_ret1=create_shadow_with_data(sizeof(ModelAnimation));
			ModelAnimation * ptr2_ret1=((ModelAnimation *)(ptr_ret1+1));
			ptr2_ret1[0]=src0;
			JSValue ret1=JS_NewObjectClass(ctx,js_ModelAnimation_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_UpdateModelAnimation(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		ModelAnimation anim=js_getModelAnimation(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int frame=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		UpdateModelAnimation(model,anim,frame);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UpdateModelAnimationBones(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		ModelAnimation anim=js_getModelAnimation(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int frame=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		UpdateModelAnimationBones(model,anim,frame);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UnloadModelAnimation(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		ModelAnimation anim=js_getModelAnimation(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadModelAnimation(anim);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UnloadModelAnimations(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		ModelAnimation * animations=js_getModelAnimation_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int animCount=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadModelAnimations(animations,animCount);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsModelAnimationValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Model model=js_getModel(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		ModelAnimation anim=js_getModelAnimation(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsModelAnimationValid(model,anim);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_CheckCollisionSpheres(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 center1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float radius1=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 center2=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float radius2=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionSpheres(center1,radius1,center2,radius2);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_CheckCollisionBoxes(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		BoundingBox box1=js_getBoundingBox(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		BoundingBox box2=js_getBoundingBox(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionBoxes(box1,box2);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_CheckCollisionBoxSphere(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		BoundingBox box=js_getBoundingBox(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 center=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=CheckCollisionBoxSphere(box,center,radius);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_GetRayCollisionSphere(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Ray ray=js_getRay(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 center=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float radius=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		RayCollision returnVal=GetRayCollisionSphere(ray,center,radius);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(RayCollision));
		RayCollision * ptr2_ret=((RayCollision *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_RayCollision_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetRayCollisionBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Ray ray=js_getRay(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		BoundingBox box=js_getBoundingBox(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		RayCollision returnVal=GetRayCollisionBox(ray,box);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(RayCollision));
		RayCollision * ptr2_ret=((RayCollision *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_RayCollision_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetRayCollisionMesh(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Ray ray=js_getRay(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh mesh=js_getMesh(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix transform=js_getMatrix(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		RayCollision returnVal=GetRayCollisionMesh(ray,mesh,transform);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(RayCollision));
		RayCollision * ptr2_ret=((RayCollision *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_RayCollision_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetRayCollisionTriangle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Ray ray=js_getRay(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 p1=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 p2=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 p3=js_getVector3(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		RayCollision returnVal=GetRayCollisionTriangle(ray,p1,p2,p3);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(RayCollision));
		RayCollision * ptr2_ret=((RayCollision *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_RayCollision_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetRayCollisionQuad(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Ray ray=js_getRay(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 p1=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 p2=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 p3=js_getVector3(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 p4=js_getVector3(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		RayCollision returnVal=GetRayCollisionQuad(ray,p1,p2,p3,p4);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(RayCollision));
		RayCollision * ptr2_ret=((RayCollision *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_RayCollision_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_InitAudioDevice(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		InitAudioDevice();
		return JS_UNDEFINED;
	}
	
	static JSValue js_CloseAudioDevice(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		CloseAudioDevice();
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsAudioDeviceReady(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=IsAudioDeviceReady();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_SetMasterVolume(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float volume=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetMasterVolume(volume);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetMasterVolume(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		float returnVal=GetMasterVolume();
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_LoadWave(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Wave returnVal=LoadWave((const char  *)fileName);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Wave));
		Wave * ptr2_ret=((Wave *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Wave_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadWaveFromMemory(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileType=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char * fileData=js_getunsignedchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Wave returnVal=LoadWaveFromMemory((const char  *)fileType,(const unsigned char  *)fileData,dataSize);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Wave));
		Wave * ptr2_ret=((Wave *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Wave_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_IsWaveValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Wave wave=js_getWave(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsWaveValid(wave);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_LoadSound(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Sound returnVal=LoadSound((const char  *)fileName);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Sound));
		Sound * ptr2_ret=((Sound *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Sound_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadSoundFromWave(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Wave wave=js_getWave(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Sound returnVal=LoadSoundFromWave(wave);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Sound));
		Sound * ptr2_ret=((Sound *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Sound_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadSoundAlias(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound source=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Sound returnVal=LoadSoundAlias(source);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Sound));
		Sound * ptr2_ret=((Sound *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Sound_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_IsSoundValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound sound=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsSoundValid(sound);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_UpdateSound(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound sound=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		void * data=js_getvoid_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int sampleCount=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		UpdateSound(sound,(const void  *)data,sampleCount);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UnloadWave(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Wave wave=js_getWave(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadWave(wave);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UnloadSound(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound sound=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadSound(sound);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UnloadSoundAlias(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound alias=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadSoundAlias(alias);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ExportWave(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Wave wave=js_getWave(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fileName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=ExportWave(wave,(const char  *)fileName);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_ExportWaveAsCode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Wave wave=js_getWave(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fileName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=ExportWaveAsCode(wave,(const char  *)fileName);
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_PlaySound(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound sound=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		PlaySound(sound);
		return JS_UNDEFINED;
	}
	
	static JSValue js_StopSound(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound sound=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		StopSound(sound);
		return JS_UNDEFINED;
	}
	
	static JSValue js_PauseSound(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound sound=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		PauseSound(sound);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ResumeSound(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound sound=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		ResumeSound(sound);
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsSoundPlaying(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound sound=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsSoundPlaying(sound);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_SetSoundVolume(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound sound=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float volume=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetSoundVolume(sound,volume);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetSoundPitch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound sound=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float pitch=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetSoundPitch(sound,pitch);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetSoundPan(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Sound sound=js_getSound(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float pan=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetSoundPan(sound,pan);
		return JS_UNDEFINED;
	}
	
	static JSValue js_WaveCopy(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Wave wave=js_getWave(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Wave returnVal=WaveCopy(wave);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Wave));
		Wave * ptr2_ret=((Wave *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Wave_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_WaveCrop(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool wave_isptr=(bool)false;
		Wave * wave=js_getWave_ptr(ctx,argv[0],&error,&wave_isptr);
		if(error==1)return JS_EXCEPTION;
		int initFrame=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int finalFrame=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		WaveCrop(wave,initFrame,finalFrame);
		if(wave_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Wave));
			Wave * ptr2_src=((Wave *)(ptr_src+1));
			ptr2_src[0]=wave[0];
			JSValue src=JS_NewObjectClass(ctx,js_Wave_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_WaveFormat(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool wave_isptr=(bool)false;
		Wave * wave=js_getWave_ptr(ctx,argv[0],&error,&wave_isptr);
		if(error==1)return JS_EXCEPTION;
		int sampleRate=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int sampleSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int channels=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		WaveFormat(wave,sampleRate,sampleSize,channels);
		if(wave_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Wave));
			Wave * ptr2_src=((Wave *)(ptr_src+1));
			ptr2_src[0]=wave[0];
			JSValue src=JS_NewObjectClass(ctx,js_Wave_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadWaveSamples(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Wave wave=js_getWave(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float * returnVal=LoadWaveSamples(wave);
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<wave.frameCount*wave.channels;i++){
			float src0=returnVal[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		UnloadWaveSamples(returnVal);
		return ret;
	}
	
	static JSValue js_UnloadWaveSamples(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float * samples=js_getfloat_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadWaveSamples(samples);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadMusicStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Music returnVal=LoadMusicStream((const char  *)fileName);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Music));
		Music * ptr2_ret=((Music *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Music_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_LoadMusicStreamFromMemory(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileType=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char * data=js_getunsignedchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Music returnVal=LoadMusicStreamFromMemory((const char  *)fileType,(const unsigned char  *)data,dataSize);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Music));
		Music * ptr2_ret=((Music *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Music_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_IsMusicValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsMusicValid(music);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_UnloadMusicStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadMusicStream(music);
		return JS_UNDEFINED;
	}
	
	static JSValue js_PlayMusicStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		PlayMusicStream(music);
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsMusicStreamPlaying(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsMusicStreamPlaying(music);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_UpdateMusicStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UpdateMusicStream(music);
		return JS_UNDEFINED;
	}
	
	static JSValue js_StopMusicStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		StopMusicStream(music);
		return JS_UNDEFINED;
	}
	
	static JSValue js_PauseMusicStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		PauseMusicStream(music);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ResumeMusicStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		ResumeMusicStream(music);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SeekMusicStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float position=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SeekMusicStream(music,position);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetMusicVolume(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float volume=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetMusicVolume(music,volume);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetMusicPitch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float pitch=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetMusicPitch(music,pitch);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetMusicPan(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float pan=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetMusicPan(music,pan);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetMusicTimeLength(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=GetMusicTimeLength(music);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_GetMusicTimePlayed(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Music music=js_getMusic(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=GetMusicTimePlayed(music);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_LoadAudioStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int sampleRate=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int sampleSize=js_getunsignedint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int channels=js_getunsignedint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		AudioStream returnVal=LoadAudioStream(sampleRate,sampleSize,channels);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(AudioStream));
		AudioStream * ptr2_ret=((AudioStream *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_AudioStream_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_IsAudioStreamValid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsAudioStreamValid(stream);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_UnloadAudioStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		UnloadAudioStream(stream);
		return JS_UNDEFINED;
	}
	
	static JSValue js_UpdateAudioStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		void * data=js_getvoid_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int frameCount=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		UpdateAudioStream(stream,(const void  *)data,frameCount);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsAudioStreamProcessed(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsAudioStreamProcessed(stream);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_PlayAudioStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		PlayAudioStream(stream);
		return JS_UNDEFINED;
	}
	
	static JSValue js_PauseAudioStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		PauseAudioStream(stream);
		return JS_UNDEFINED;
	}
	
	static JSValue js_ResumeAudioStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		ResumeAudioStream(stream);
		return JS_UNDEFINED;
	}
	
	static JSValue js_IsAudioStreamPlaying(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=IsAudioStreamPlaying(stream);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_StopAudioStream(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		StopAudioStream(stream);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetAudioStreamVolume(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float volume=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetAudioStreamVolume(stream,volume);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetAudioStreamPitch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float pitch=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetAudioStreamPitch(stream,pitch);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetAudioStreamPan(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		AudioStream stream=js_getAudioStream(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float pan=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		SetAudioStreamPan(stream,pan);
		return JS_UNDEFINED;
	}
	
	static JSValue js_SetAudioStreamBufferSizeDefault(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int size=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		SetAudioStreamBufferSizeDefault(size);
		return JS_UNDEFINED;
	}
	
	static JSValue js_AttachAudioMixedProcessor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * processor;
		trampolineContext ctx_processor;
		ctx_processor.ctx=ctx;
		ctx_processor.func_obj=argv[0];
		processor =callback_AudioMixedProcessor;
		if(JS_IsFunction(ctx,argv[0])==0){
			JS_ThrowTypeError(ctx,(const char  *)"argv[0] must be a function");
			return JS_EXCEPTION;
		}
		if(AudioMixedProcessor_size==0){
			AudioMixedProcessor_arr =(trampolineContext  *)js_malloc(ctx,sizeof(trampolineContext));
		}else{
			AudioMixedProcessor_arr =(trampolineContext  *)js_realloc(ctx,(void  *)AudioMixedProcessor_arr,sizeof(trampolineContext)*AudioMixedProcessor_size);
		}
		JS_DupValue(ctx,argv[0]);
		AudioMixedProcessor_arr[AudioMixedProcessor_size] =ctx_processor;
		AudioMixedProcessor_size +=1;
		if(AudioMixedProcessor_size>1)return JS_UNDEFINED;
		AttachAudioMixedProcessor(processor);
		return JS_UNDEFINED;
	}
	
	static JSValue js_DetachAudioMixedProcessor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * processor;
		int processor_pos;
		processor =callback_AudioCallback;
		for(int i=0;i<AudioCallback_size;i++){
			if(JS_IsEqual(AudioCallback_arr[i].ctx,AudioCallback_arr[i].func_obj,argv[0])){
				JS_FreeValue(ctx,AudioCallback_arr[i].func_obj);
				JS_FreeValue(AudioCallback_arr[i].ctx,AudioCallback_arr[i].func_obj);
				JS_FreeContext(AudioCallback_arr[i].ctx);
				for(int i0=i;i0<AudioCallback_size-1;i0++){
					AudioCallback_arr[i0]=AudioCallback_arr[i0+1];
				}
			}
			AudioCallback_size -=1;
			AudioCallback_arr =(trampolineContext  *)js_realloc(ctx,(void  *)AudioCallback_arr,sizeof(void *)*AudioCallback_size);
			break;
		}
		if(AudioCallback_size!=0)return JS_UNDEFINED;
		DetachAudioMixedProcessor(processor);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetMouseRay(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 position=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Camera camera=js_getCamera(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Ray returnVal=GetMouseRay(position,camera);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Ray));
		Ray * ptr2_ret=((Ray *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Ray_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	static const JSCFunctionListEntry jsraylib_funcs[]={
		JS_CFUNC_DEF("InitWindow",3,js_InitWindow),
		JS_CFUNC_DEF("CloseWindow",0,js_CloseWindow),
		JS_CFUNC_DEF("WindowShouldClose",0,js_WindowShouldClose),
		JS_CFUNC_DEF("IsWindowReady",0,js_IsWindowReady),
		JS_CFUNC_DEF("IsWindowFullscreen",0,js_IsWindowFullscreen),
		JS_CFUNC_DEF("IsWindowHidden",0,js_IsWindowHidden),
		JS_CFUNC_DEF("IsWindowMinimized",0,js_IsWindowMinimized),
		JS_CFUNC_DEF("IsWindowMaximized",0,js_IsWindowMaximized),
		JS_CFUNC_DEF("IsWindowFocused",0,js_IsWindowFocused),
		JS_CFUNC_DEF("IsWindowResized",0,js_IsWindowResized),
		JS_CFUNC_DEF("IsWindowState",1,js_IsWindowState),
		JS_CFUNC_DEF("SetWindowState",1,js_SetWindowState),
		JS_CFUNC_DEF("ClearWindowState",1,js_ClearWindowState),
		JS_CFUNC_DEF("ToggleFullscreen",0,js_ToggleFullscreen),
		JS_CFUNC_DEF("ToggleBorderlessWindowed",0,js_ToggleBorderlessWindowed),
		JS_CFUNC_DEF("MaximizeWindow",0,js_MaximizeWindow),
		JS_CFUNC_DEF("MinimizeWindow",0,js_MinimizeWindow),
		JS_CFUNC_DEF("RestoreWindow",0,js_RestoreWindow),
		JS_CFUNC_DEF("SetWindowIcon",1,js_SetWindowIcon),
		JS_CFUNC_DEF("SetWindowIcons",2,js_SetWindowIcons),
		JS_CFUNC_DEF("SetWindowTitle",1,js_SetWindowTitle),
		JS_CFUNC_DEF("SetWindowPosition",2,js_SetWindowPosition),
		JS_CFUNC_DEF("SetWindowMonitor",1,js_SetWindowMonitor),
		JS_CFUNC_DEF("SetWindowMinSize",2,js_SetWindowMinSize),
		JS_CFUNC_DEF("SetWindowMaxSize",2,js_SetWindowMaxSize),
		JS_CFUNC_DEF("SetWindowSize",2,js_SetWindowSize),
		JS_CFUNC_DEF("SetWindowOpacity",1,js_SetWindowOpacity),
		JS_CFUNC_DEF("SetWindowFocused",0,js_SetWindowFocused),
		JS_CFUNC_DEF("GetScreenWidth",0,js_GetScreenWidth),
		JS_CFUNC_DEF("GetScreenHeight",0,js_GetScreenHeight),
		JS_CFUNC_DEF("GetRenderWidth",0,js_GetRenderWidth),
		JS_CFUNC_DEF("GetRenderHeight",0,js_GetRenderHeight),
		JS_CFUNC_DEF("GetMonitorCount",0,js_GetMonitorCount),
		JS_CFUNC_DEF("GetCurrentMonitor",0,js_GetCurrentMonitor),
		JS_CFUNC_DEF("GetMonitorPosition",1,js_GetMonitorPosition),
		JS_CFUNC_DEF("GetMonitorWidth",1,js_GetMonitorWidth),
		JS_CFUNC_DEF("GetMonitorHeight",1,js_GetMonitorHeight),
		JS_CFUNC_DEF("GetMonitorPhysicalWidth",1,js_GetMonitorPhysicalWidth),
		JS_CFUNC_DEF("GetMonitorPhysicalHeight",1,js_GetMonitorPhysicalHeight),
		JS_CFUNC_DEF("GetMonitorRefreshRate",1,js_GetMonitorRefreshRate),
		JS_CFUNC_DEF("GetWindowPosition",0,js_GetWindowPosition),
		JS_CFUNC_DEF("GetWindowScaleDPI",0,js_GetWindowScaleDPI),
		JS_CFUNC_DEF("GetMonitorName",1,js_GetMonitorName),
		JS_CFUNC_DEF("SetClipboardText",1,js_SetClipboardText),
		JS_CFUNC_DEF("GetClipboardText",0,js_GetClipboardText),
		JS_CFUNC_DEF("GetClipboardImage",0,js_GetClipboardImage),
		JS_CFUNC_DEF("EnableEventWaiting",0,js_EnableEventWaiting),
		JS_CFUNC_DEF("DisableEventWaiting",0,js_DisableEventWaiting),
		JS_CFUNC_DEF("ShowCursor",0,js_ShowCursor),
		JS_CFUNC_DEF("HideCursor",0,js_HideCursor),
		JS_CFUNC_DEF("IsCursorHidden",0,js_IsCursorHidden),
		JS_CFUNC_DEF("EnableCursor",0,js_EnableCursor),
		JS_CFUNC_DEF("DisableCursor",0,js_DisableCursor),
		JS_CFUNC_DEF("IsCursorOnScreen",0,js_IsCursorOnScreen),
		JS_CFUNC_DEF("ClearBackground",1,js_ClearBackground),
		JS_CFUNC_DEF("BeginDrawing",0,js_BeginDrawing),
		JS_CFUNC_DEF("EndDrawing",0,js_EndDrawing),
		JS_CFUNC_DEF("BeginMode2D",1,js_BeginMode2D),
		JS_CFUNC_DEF("EndMode2D",0,js_EndMode2D),
		JS_CFUNC_DEF("BeginMode3D",1,js_BeginMode3D),
		JS_CFUNC_DEF("EndMode3D",0,js_EndMode3D),
		JS_CFUNC_DEF("BeginTextureMode",1,js_BeginTextureMode),
		JS_CFUNC_DEF("EndTextureMode",0,js_EndTextureMode),
		JS_CFUNC_DEF("BeginShaderMode",1,js_BeginShaderMode),
		JS_CFUNC_DEF("EndShaderMode",0,js_EndShaderMode),
		JS_CFUNC_DEF("BeginBlendMode",1,js_BeginBlendMode),
		JS_CFUNC_DEF("EndBlendMode",0,js_EndBlendMode),
		JS_CFUNC_DEF("BeginScissorMode",4,js_BeginScissorMode),
		JS_CFUNC_DEF("EndScissorMode",0,js_EndScissorMode),
		JS_CFUNC_DEF("BeginVrStereoMode",1,js_BeginVrStereoMode),
		JS_CFUNC_DEF("EndVrStereoMode",0,js_EndVrStereoMode),
		JS_CFUNC_DEF("LoadVrStereoConfig",1,js_LoadVrStereoConfig),
		JS_CFUNC_DEF("UnloadVrStereoConfig",1,js_UnloadVrStereoConfig),
		JS_CFUNC_DEF("LoadShader",2,js_LoadShader),
		JS_CFUNC_DEF("LoadShaderFromMemory",2,js_LoadShaderFromMemory),
		JS_CFUNC_DEF("IsShaderValid",1,js_IsShaderValid),
		JS_CFUNC_DEF("GetShaderLocation",2,js_GetShaderLocation),
		JS_CFUNC_DEF("GetShaderLocationAttrib",2,js_GetShaderLocationAttrib),
		JS_CFUNC_DEF("SetShaderValue",4,js_SetShaderValue),
		JS_CFUNC_DEF("SetShaderValueV",5,js_SetShaderValueV),
		JS_CFUNC_DEF("SetShaderValueMatrix",3,js_SetShaderValueMatrix),
		JS_CFUNC_DEF("SetShaderValueTexture",3,js_SetShaderValueTexture),
		JS_CFUNC_DEF("UnloadShader",1,js_UnloadShader),
		JS_CFUNC_DEF("GetScreenToWorldRay",2,js_GetScreenToWorldRay),
		JS_CFUNC_DEF("GetScreenToWorldRayEx",4,js_GetScreenToWorldRayEx),
		JS_CFUNC_DEF("GetWorldToScreen",2,js_GetWorldToScreen),
		JS_CFUNC_DEF("GetWorldToScreenEx",4,js_GetWorldToScreenEx),
		JS_CFUNC_DEF("GetWorldToScreen2D",2,js_GetWorldToScreen2D),
		JS_CFUNC_DEF("GetScreenToWorld2D",2,js_GetScreenToWorld2D),
		JS_CFUNC_DEF("GetCameraMatrix",1,js_GetCameraMatrix),
		JS_CFUNC_DEF("GetCameraMatrix2D",1,js_GetCameraMatrix2D),
		JS_CFUNC_DEF("SetTargetFPS",1,js_SetTargetFPS),
		JS_CFUNC_DEF("GetFrameTime",0,js_GetFrameTime),
		JS_CFUNC_DEF("GetTime",0,js_GetTime),
		JS_CFUNC_DEF("GetFPS",0,js_GetFPS),
		JS_CFUNC_DEF("SetRandomSeed",1,js_SetRandomSeed),
		JS_CFUNC_DEF("GetRandomValue",2,js_GetRandomValue),
		JS_CFUNC_DEF("LoadRandomSequence",3,js_LoadRandomSequence),
		JS_CFUNC_DEF("UnloadRandomSequence",1,js_UnloadRandomSequence),
		JS_CFUNC_DEF("TakeScreenshot",1,js_TakeScreenshot),
		JS_CFUNC_DEF("SetConfigFlags",1,js_SetConfigFlags),
		JS_CFUNC_DEF("OpenURL",1,js_OpenURL),
		JS_CFUNC_DEF("TraceLog",3,js_TraceLog),
		JS_CFUNC_DEF("SetTraceLogLevel",1,js_SetTraceLogLevel),
		JS_CFUNC_DEF("SetLoadFileDataCallback",1,js_SetLoadFileDataCallback),
		JS_CFUNC_DEF("SetSaveFileDataCallback",1,js_SetSaveFileDataCallback),
		JS_CFUNC_DEF("SetLoadFileTextCallback",1,js_SetLoadFileTextCallback),
		JS_CFUNC_DEF("SetSaveFileTextCallback",1,js_SetSaveFileTextCallback),
		JS_CFUNC_DEF("LoadFileData",2,js_LoadFileData),
		JS_CFUNC_DEF("SaveFileData",3,js_SaveFileData),
		JS_CFUNC_DEF("ExportDataAsCode",3,js_ExportDataAsCode),
		JS_CFUNC_DEF("LoadFileText",1,js_LoadFileText),
		JS_CFUNC_DEF("SaveFileText",2,js_SaveFileText),
		JS_CFUNC_DEF("FileRename",2,js_FileRename),
		JS_CFUNC_DEF("FileRemove",1,js_FileRemove),
		JS_CFUNC_DEF("FileCopy",2,js_FileCopy),
		JS_CFUNC_DEF("FileMove",2,js_FileMove),
		JS_CFUNC_DEF("FileTextReplace",3,js_FileTextReplace),
		JS_CFUNC_DEF("FileTextFindIndex",2,js_FileTextFindIndex),
		JS_CFUNC_DEF("FileExists",1,js_FileExists),
		JS_CFUNC_DEF("DirectoryExists",1,js_DirectoryExists),
		JS_CFUNC_DEF("IsFileExtension",2,js_IsFileExtension),
		JS_CFUNC_DEF("GetFileLength",1,js_GetFileLength),
		JS_CFUNC_DEF("GetFileModTime",1,js_GetFileModTime),
		JS_CFUNC_DEF("GetFileExtension",1,js_GetFileExtension),
		JS_CFUNC_DEF("GetFileName",1,js_GetFileName),
		JS_CFUNC_DEF("GetFileNameWithoutExt",1,js_GetFileNameWithoutExt),
		JS_CFUNC_DEF("GetDirectoryPath",1,js_GetDirectoryPath),
		JS_CFUNC_DEF("GetPrevDirectoryPath",1,js_GetPrevDirectoryPath),
		JS_CFUNC_DEF("GetWorkingDirectory",0,js_GetWorkingDirectory),
		JS_CFUNC_DEF("GetApplicationDirectory",0,js_GetApplicationDirectory),
		JS_CFUNC_DEF("MakeDirectory",1,js_MakeDirectory),
		JS_CFUNC_DEF("ChangeDirectory",1,js_ChangeDirectory),
		JS_CFUNC_DEF("IsPathFile",1,js_IsPathFile),
		JS_CFUNC_DEF("IsFileNameValid",1,js_IsFileNameValid),
		JS_CFUNC_DEF("LoadDirectoryFiles",1,js_LoadDirectoryFiles),
		JS_CFUNC_DEF("LoadDirectoryFilesEx",3,js_LoadDirectoryFilesEx),
		JS_CFUNC_DEF("IsFileDropped",0,js_IsFileDropped),
		JS_CFUNC_DEF("LoadDroppedFiles",0,js_LoadDroppedFiles),
		JS_CFUNC_DEF("CompressData",3,js_CompressData),
		JS_CFUNC_DEF("DecompressData",3,js_DecompressData),
		JS_CFUNC_DEF("EncodeDataBase64",3,js_EncodeDataBase64),
		JS_CFUNC_DEF("DecodeDataBase64",2,js_DecodeDataBase64),
		JS_CFUNC_DEF("ComputeCRC32",2,js_ComputeCRC32),
		JS_CFUNC_DEF("ComputeMD5",2,js_ComputeMD5),
		JS_CFUNC_DEF("ComputeSHA1",2,js_ComputeSHA1),
		JS_CFUNC_DEF("ComputeSHA256",2,js_ComputeSHA256),
		JS_CFUNC_DEF("LoadAutomationEventList",1,js_LoadAutomationEventList),
		JS_CFUNC_DEF("UnloadAutomationEventList",1,js_UnloadAutomationEventList),
		JS_CFUNC_DEF("ExportAutomationEventList",2,js_ExportAutomationEventList),
		JS_CFUNC_DEF("SetAutomationEventList",1,js_SetAutomationEventList),
		JS_CFUNC_DEF("SetAutomationEventBaseFrame",1,js_SetAutomationEventBaseFrame),
		JS_CFUNC_DEF("StartAutomationEventRecording",0,js_StartAutomationEventRecording),
		JS_CFUNC_DEF("StopAutomationEventRecording",0,js_StopAutomationEventRecording),
		JS_CFUNC_DEF("PlayAutomationEvent",1,js_PlayAutomationEvent),
		JS_CFUNC_DEF("IsKeyPressed",1,js_IsKeyPressed),
		JS_CFUNC_DEF("IsKeyPressedRepeat",1,js_IsKeyPressedRepeat),
		JS_CFUNC_DEF("IsKeyDown",1,js_IsKeyDown),
		JS_CFUNC_DEF("IsKeyReleased",1,js_IsKeyReleased),
		JS_CFUNC_DEF("IsKeyUp",1,js_IsKeyUp),
		JS_CFUNC_DEF("GetKeyPressed",0,js_GetKeyPressed),
		JS_CFUNC_DEF("GetCharPressed",0,js_GetCharPressed),
		JS_CFUNC_DEF("GetKeyName",1,js_GetKeyName),
		JS_CFUNC_DEF("SetExitKey",1,js_SetExitKey),
		JS_CFUNC_DEF("IsGamepadAvailable",1,js_IsGamepadAvailable),
		JS_CFUNC_DEF("GetGamepadName",1,js_GetGamepadName),
		JS_CFUNC_DEF("IsGamepadButtonPressed",2,js_IsGamepadButtonPressed),
		JS_CFUNC_DEF("IsGamepadButtonDown",2,js_IsGamepadButtonDown),
		JS_CFUNC_DEF("IsGamepadButtonReleased",2,js_IsGamepadButtonReleased),
		JS_CFUNC_DEF("IsGamepadButtonUp",2,js_IsGamepadButtonUp),
		JS_CFUNC_DEF("GetGamepadButtonPressed",0,js_GetGamepadButtonPressed),
		JS_CFUNC_DEF("GetGamepadAxisCount",1,js_GetGamepadAxisCount),
		JS_CFUNC_DEF("GetGamepadAxisMovement",2,js_GetGamepadAxisMovement),
		JS_CFUNC_DEF("SetGamepadMappings",1,js_SetGamepadMappings),
		JS_CFUNC_DEF("SetGamepadVibration",4,js_SetGamepadVibration),
		JS_CFUNC_DEF("IsMouseButtonPressed",1,js_IsMouseButtonPressed),
		JS_CFUNC_DEF("IsMouseButtonDown",1,js_IsMouseButtonDown),
		JS_CFUNC_DEF("IsMouseButtonReleased",1,js_IsMouseButtonReleased),
		JS_CFUNC_DEF("IsMouseButtonUp",1,js_IsMouseButtonUp),
		JS_CFUNC_DEF("GetMouseX",0,js_GetMouseX),
		JS_CFUNC_DEF("GetMouseY",0,js_GetMouseY),
		JS_CFUNC_DEF("GetMousePosition",0,js_GetMousePosition),
		JS_CFUNC_DEF("GetMouseDelta",0,js_GetMouseDelta),
		JS_CFUNC_DEF("SetMousePosition",2,js_SetMousePosition),
		JS_CFUNC_DEF("SetMouseOffset",2,js_SetMouseOffset),
		JS_CFUNC_DEF("SetMouseScale",2,js_SetMouseScale),
		JS_CFUNC_DEF("GetMouseWheelMove",0,js_GetMouseWheelMove),
		JS_CFUNC_DEF("GetMouseWheelMoveV",0,js_GetMouseWheelMoveV),
		JS_CFUNC_DEF("SetMouseCursor",1,js_SetMouseCursor),
		JS_CFUNC_DEF("GetTouchX",0,js_GetTouchX),
		JS_CFUNC_DEF("GetTouchY",0,js_GetTouchY),
		JS_CFUNC_DEF("GetTouchPosition",1,js_GetTouchPosition),
		JS_CFUNC_DEF("GetTouchPointId",1,js_GetTouchPointId),
		JS_CFUNC_DEF("GetTouchPointCount",0,js_GetTouchPointCount),
		JS_CFUNC_DEF("SetGesturesEnabled",1,js_SetGesturesEnabled),
		JS_CFUNC_DEF("IsGestureDetected",1,js_IsGestureDetected),
		JS_CFUNC_DEF("GetGestureDetected",0,js_GetGestureDetected),
		JS_CFUNC_DEF("GetGestureHoldDuration",0,js_GetGestureHoldDuration),
		JS_CFUNC_DEF("GetGestureDragVector",0,js_GetGestureDragVector),
		JS_CFUNC_DEF("GetGestureDragAngle",0,js_GetGestureDragAngle),
		JS_CFUNC_DEF("GetGesturePinchVector",0,js_GetGesturePinchVector),
		JS_CFUNC_DEF("GetGesturePinchAngle",0,js_GetGesturePinchAngle),
		JS_CFUNC_DEF("UpdateCamera",2,js_UpdateCamera),
		JS_CFUNC_DEF("UpdateCameraPro",4,js_UpdateCameraPro),
		JS_CFUNC_DEF("SetShapesTexture",2,js_SetShapesTexture),
		JS_CFUNC_DEF("GetShapesTexture",0,js_GetShapesTexture),
		JS_CFUNC_DEF("GetShapesTextureRectangle",0,js_GetShapesTextureRectangle),
		JS_CFUNC_DEF("DrawPixel",3,js_DrawPixel),
		JS_CFUNC_DEF("DrawPixelV",2,js_DrawPixelV),
		JS_CFUNC_DEF("DrawLine",5,js_DrawLine),
		JS_CFUNC_DEF("DrawLineV",3,js_DrawLineV),
		JS_CFUNC_DEF("DrawLineEx",4,js_DrawLineEx),
		JS_CFUNC_DEF("DrawLineStrip",3,js_DrawLineStrip),
		JS_CFUNC_DEF("DrawLineBezier",4,js_DrawLineBezier),
		JS_CFUNC_DEF("DrawLineDashed",5,js_DrawLineDashed),
		JS_CFUNC_DEF("DrawCircle",4,js_DrawCircle),
		JS_CFUNC_DEF("DrawCircleSector",6,js_DrawCircleSector),
		JS_CFUNC_DEF("DrawCircleSectorLines",6,js_DrawCircleSectorLines),
		JS_CFUNC_DEF("DrawCircleGradient",5,js_DrawCircleGradient),
		JS_CFUNC_DEF("DrawCircleV",3,js_DrawCircleV),
		JS_CFUNC_DEF("DrawCircleLines",4,js_DrawCircleLines),
		JS_CFUNC_DEF("DrawCircleLinesV",3,js_DrawCircleLinesV),
		JS_CFUNC_DEF("DrawEllipse",5,js_DrawEllipse),
		JS_CFUNC_DEF("DrawEllipseV",4,js_DrawEllipseV),
		JS_CFUNC_DEF("DrawEllipseLines",5,js_DrawEllipseLines),
		JS_CFUNC_DEF("DrawEllipseLinesV",4,js_DrawEllipseLinesV),
		JS_CFUNC_DEF("DrawRing",7,js_DrawRing),
		JS_CFUNC_DEF("DrawRingLines",7,js_DrawRingLines),
		JS_CFUNC_DEF("DrawRectangle",5,js_DrawRectangle),
		JS_CFUNC_DEF("DrawRectangleV",3,js_DrawRectangleV),
		JS_CFUNC_DEF("DrawRectangleRec",2,js_DrawRectangleRec),
		JS_CFUNC_DEF("DrawRectanglePro",4,js_DrawRectanglePro),
		JS_CFUNC_DEF("DrawRectangleGradientV",6,js_DrawRectangleGradientV),
		JS_CFUNC_DEF("DrawRectangleGradientH",6,js_DrawRectangleGradientH),
		JS_CFUNC_DEF("DrawRectangleGradientEx",5,js_DrawRectangleGradientEx),
		JS_CFUNC_DEF("DrawRectangleLines",5,js_DrawRectangleLines),
		JS_CFUNC_DEF("DrawRectangleLinesEx",3,js_DrawRectangleLinesEx),
		JS_CFUNC_DEF("DrawRectangleRounded",4,js_DrawRectangleRounded),
		JS_CFUNC_DEF("DrawRectangleRoundedLines",4,js_DrawRectangleRoundedLines),
		JS_CFUNC_DEF("DrawRectangleRoundedLinesEx",5,js_DrawRectangleRoundedLinesEx),
		JS_CFUNC_DEF("DrawTriangle",4,js_DrawTriangle),
		JS_CFUNC_DEF("DrawTriangleLines",4,js_DrawTriangleLines),
		JS_CFUNC_DEF("DrawTriangleFan",3,js_DrawTriangleFan),
		JS_CFUNC_DEF("DrawTriangleStrip",3,js_DrawTriangleStrip),
		JS_CFUNC_DEF("DrawPoly",5,js_DrawPoly),
		JS_CFUNC_DEF("DrawPolyLines",5,js_DrawPolyLines),
		JS_CFUNC_DEF("DrawPolyLinesEx",6,js_DrawPolyLinesEx),
		JS_CFUNC_DEF("DrawSplineLinear",4,js_DrawSplineLinear),
		JS_CFUNC_DEF("DrawSplineBasis",4,js_DrawSplineBasis),
		JS_CFUNC_DEF("DrawSplineCatmullRom",4,js_DrawSplineCatmullRom),
		JS_CFUNC_DEF("DrawSplineBezierQuadratic",4,js_DrawSplineBezierQuadratic),
		JS_CFUNC_DEF("DrawSplineBezierCubic",4,js_DrawSplineBezierCubic),
		JS_CFUNC_DEF("DrawSplineSegmentLinear",4,js_DrawSplineSegmentLinear),
		JS_CFUNC_DEF("DrawSplineSegmentBasis",6,js_DrawSplineSegmentBasis),
		JS_CFUNC_DEF("DrawSplineSegmentCatmullRom",6,js_DrawSplineSegmentCatmullRom),
		JS_CFUNC_DEF("DrawSplineSegmentBezierQuadratic",5,js_DrawSplineSegmentBezierQuadratic),
		JS_CFUNC_DEF("DrawSplineSegmentBezierCubic",6,js_DrawSplineSegmentBezierCubic),
		JS_CFUNC_DEF("GetSplinePointLinear",3,js_GetSplinePointLinear),
		JS_CFUNC_DEF("GetSplinePointBasis",5,js_GetSplinePointBasis),
		JS_CFUNC_DEF("GetSplinePointCatmullRom",5,js_GetSplinePointCatmullRom),
		JS_CFUNC_DEF("GetSplinePointBezierQuad",4,js_GetSplinePointBezierQuad),
		JS_CFUNC_DEF("GetSplinePointBezierCubic",5,js_GetSplinePointBezierCubic),
		JS_CFUNC_DEF("CheckCollisionRecs",2,js_CheckCollisionRecs),
		JS_CFUNC_DEF("CheckCollisionCircles",4,js_CheckCollisionCircles),
		JS_CFUNC_DEF("CheckCollisionCircleRec",3,js_CheckCollisionCircleRec),
		JS_CFUNC_DEF("CheckCollisionCircleLine",4,js_CheckCollisionCircleLine),
		JS_CFUNC_DEF("CheckCollisionPointRec",2,js_CheckCollisionPointRec),
		JS_CFUNC_DEF("CheckCollisionPointCircle",3,js_CheckCollisionPointCircle),
		JS_CFUNC_DEF("CheckCollisionPointTriangle",4,js_CheckCollisionPointTriangle),
		JS_CFUNC_DEF("CheckCollisionPointLine",4,js_CheckCollisionPointLine),
		JS_CFUNC_DEF("CheckCollisionPointPoly",3,js_CheckCollisionPointPoly),
		JS_CFUNC_DEF("CheckCollisionLines",5,js_CheckCollisionLines),
		JS_CFUNC_DEF("GetCollisionRec",2,js_GetCollisionRec),
		JS_CFUNC_DEF("LoadImage",1,js_LoadImage),
		JS_CFUNC_DEF("LoadImageRaw",5,js_LoadImageRaw),
		JS_CFUNC_DEF("LoadImageAnim",2,js_LoadImageAnim),
		JS_CFUNC_DEF("LoadImageAnimFromMemory",4,js_LoadImageAnimFromMemory),
		JS_CFUNC_DEF("LoadImageFromMemory",3,js_LoadImageFromMemory),
		JS_CFUNC_DEF("LoadImageFromTexture",1,js_LoadImageFromTexture),
		JS_CFUNC_DEF("LoadImageFromScreen",0,js_LoadImageFromScreen),
		JS_CFUNC_DEF("IsImageValid",1,js_IsImageValid),
		JS_CFUNC_DEF("UnloadImage",1,js_UnloadImage),
		JS_CFUNC_DEF("ExportImage",2,js_ExportImage),
		JS_CFUNC_DEF("ExportImageToMemory",3,js_ExportImageToMemory),
		JS_CFUNC_DEF("ExportImageAsCode",2,js_ExportImageAsCode),
		JS_CFUNC_DEF("GenImageColor",3,js_GenImageColor),
		JS_CFUNC_DEF("GenImageGradientLinear",5,js_GenImageGradientLinear),
		JS_CFUNC_DEF("GenImageGradientRadial",5,js_GenImageGradientRadial),
		JS_CFUNC_DEF("GenImageGradientSquare",5,js_GenImageGradientSquare),
		JS_CFUNC_DEF("GenImageChecked",6,js_GenImageChecked),
		JS_CFUNC_DEF("GenImageWhiteNoise",3,js_GenImageWhiteNoise),
		JS_CFUNC_DEF("GenImagePerlinNoise",5,js_GenImagePerlinNoise),
		JS_CFUNC_DEF("GenImageCellular",3,js_GenImageCellular),
		JS_CFUNC_DEF("GenImageText",3,js_GenImageText),
		JS_CFUNC_DEF("ImageCopy",1,js_ImageCopy),
		JS_CFUNC_DEF("ImageFromImage",2,js_ImageFromImage),
		JS_CFUNC_DEF("ImageFromChannel",2,js_ImageFromChannel),
		JS_CFUNC_DEF("ImageText",3,js_ImageText),
		JS_CFUNC_DEF("ImageTextEx",5,js_ImageTextEx),
		JS_CFUNC_DEF("ImageFormat",2,js_ImageFormat),
		JS_CFUNC_DEF("ImageToPOT",2,js_ImageToPOT),
		JS_CFUNC_DEF("ImageCrop",2,js_ImageCrop),
		JS_CFUNC_DEF("ImageAlphaCrop",2,js_ImageAlphaCrop),
		JS_CFUNC_DEF("ImageAlphaClear",3,js_ImageAlphaClear),
		JS_CFUNC_DEF("ImageAlphaMask",2,js_ImageAlphaMask),
		JS_CFUNC_DEF("ImageAlphaPremultiply",1,js_ImageAlphaPremultiply),
		JS_CFUNC_DEF("ImageBlurGaussian",2,js_ImageBlurGaussian),
		JS_CFUNC_DEF("ImageKernelConvolution",3,js_ImageKernelConvolution),
		JS_CFUNC_DEF("ImageResize",3,js_ImageResize),
		JS_CFUNC_DEF("ImageResizeNN",3,js_ImageResizeNN),
		JS_CFUNC_DEF("ImageResizeCanvas",6,js_ImageResizeCanvas),
		JS_CFUNC_DEF("ImageMipmaps",1,js_ImageMipmaps),
		JS_CFUNC_DEF("ImageDither",5,js_ImageDither),
		JS_CFUNC_DEF("ImageFlipVertical",1,js_ImageFlipVertical),
		JS_CFUNC_DEF("ImageFlipHorizontal",1,js_ImageFlipHorizontal),
		JS_CFUNC_DEF("ImageRotate",2,js_ImageRotate),
		JS_CFUNC_DEF("ImageRotateCW",1,js_ImageRotateCW),
		JS_CFUNC_DEF("ImageRotateCCW",1,js_ImageRotateCCW),
		JS_CFUNC_DEF("ImageColorTint",2,js_ImageColorTint),
		JS_CFUNC_DEF("ImageColorInvert",1,js_ImageColorInvert),
		JS_CFUNC_DEF("ImageColorGrayscale",1,js_ImageColorGrayscale),
		JS_CFUNC_DEF("ImageColorContrast",2,js_ImageColorContrast),
		JS_CFUNC_DEF("ImageColorBrightness",2,js_ImageColorBrightness),
		JS_CFUNC_DEF("ImageColorReplace",3,js_ImageColorReplace),
		JS_CFUNC_DEF("LoadImageColors",1,js_LoadImageColors),
		JS_CFUNC_DEF("LoadImagePalette",3,js_LoadImagePalette),
		JS_CFUNC_DEF("UnloadImageColors",1,js_UnloadImageColors),
		JS_CFUNC_DEF("UnloadImagePalette",1,js_UnloadImagePalette),
		JS_CFUNC_DEF("GetImageAlphaBorder",2,js_GetImageAlphaBorder),
		JS_CFUNC_DEF("GetImageColor",3,js_GetImageColor),
		JS_CFUNC_DEF("ImageClearBackground",2,js_ImageClearBackground),
		JS_CFUNC_DEF("ImageDrawPixel",4,js_ImageDrawPixel),
		JS_CFUNC_DEF("ImageDrawPixelV",3,js_ImageDrawPixelV),
		JS_CFUNC_DEF("ImageDrawLine",6,js_ImageDrawLine),
		JS_CFUNC_DEF("ImageDrawLineV",4,js_ImageDrawLineV),
		JS_CFUNC_DEF("ImageDrawLineEx",5,js_ImageDrawLineEx),
		JS_CFUNC_DEF("ImageDrawCircle",5,js_ImageDrawCircle),
		JS_CFUNC_DEF("ImageDrawCircleV",4,js_ImageDrawCircleV),
		JS_CFUNC_DEF("ImageDrawCircleLines",5,js_ImageDrawCircleLines),
		JS_CFUNC_DEF("ImageDrawCircleLinesV",4,js_ImageDrawCircleLinesV),
		JS_CFUNC_DEF("ImageDrawRectangle",6,js_ImageDrawRectangle),
		JS_CFUNC_DEF("ImageDrawRectangleV",4,js_ImageDrawRectangleV),
		JS_CFUNC_DEF("ImageDrawRectangleRec",3,js_ImageDrawRectangleRec),
		JS_CFUNC_DEF("ImageDrawRectangleLines",4,js_ImageDrawRectangleLines),
		JS_CFUNC_DEF("ImageDrawTriangle",5,js_ImageDrawTriangle),
		JS_CFUNC_DEF("ImageDrawTriangleEx",7,js_ImageDrawTriangleEx),
		JS_CFUNC_DEF("ImageDrawTriangleLines",5,js_ImageDrawTriangleLines),
		JS_CFUNC_DEF("ImageDrawTriangleFan",4,js_ImageDrawTriangleFan),
		JS_CFUNC_DEF("ImageDrawTriangleStrip",4,js_ImageDrawTriangleStrip),
		JS_CFUNC_DEF("ImageDraw",5,js_ImageDraw),
		JS_CFUNC_DEF("ImageDrawText",6,js_ImageDrawText),
		JS_CFUNC_DEF("ImageDrawTextEx",7,js_ImageDrawTextEx),
		JS_CFUNC_DEF("LoadTexture",1,js_LoadTexture),
		JS_CFUNC_DEF("LoadTextureFromImage",1,js_LoadTextureFromImage),
		JS_CFUNC_DEF("LoadTextureCubemap",2,js_LoadTextureCubemap),
		JS_CFUNC_DEF("LoadRenderTexture",2,js_LoadRenderTexture),
		JS_CFUNC_DEF("IsTextureValid",1,js_IsTextureValid),
		JS_CFUNC_DEF("UnloadTexture",1,js_UnloadTexture),
		JS_CFUNC_DEF("IsRenderTextureValid",1,js_IsRenderTextureValid),
		JS_CFUNC_DEF("UnloadRenderTexture",1,js_UnloadRenderTexture),
		JS_CFUNC_DEF("UpdateTexture",2,js_UpdateTexture),
		JS_CFUNC_DEF("UpdateTextureRec",3,js_UpdateTextureRec),
		JS_CFUNC_DEF("GenTextureMipmaps",1,js_GenTextureMipmaps),
		JS_CFUNC_DEF("SetTextureFilter",2,js_SetTextureFilter),
		JS_CFUNC_DEF("SetTextureWrap",2,js_SetTextureWrap),
		JS_CFUNC_DEF("DrawTexture",4,js_DrawTexture),
		JS_CFUNC_DEF("DrawTextureV",3,js_DrawTextureV),
		JS_CFUNC_DEF("DrawTextureEx",5,js_DrawTextureEx),
		JS_CFUNC_DEF("DrawTextureRec",4,js_DrawTextureRec),
		JS_CFUNC_DEF("DrawTexturePro",6,js_DrawTexturePro),
		JS_CFUNC_DEF("DrawTextureNPatch",6,js_DrawTextureNPatch),
		JS_CFUNC_DEF("ColorIsEqual",2,js_ColorIsEqual),
		JS_CFUNC_DEF("Fade",2,js_Fade),
		JS_CFUNC_DEF("ColorToInt",1,js_ColorToInt),
		JS_CFUNC_DEF("ColorNormalize",1,js_ColorNormalize),
		JS_CFUNC_DEF("ColorFromNormalized",1,js_ColorFromNormalized),
		JS_CFUNC_DEF("ColorToHSV",1,js_ColorToHSV),
		JS_CFUNC_DEF("ColorFromHSV",3,js_ColorFromHSV),
		JS_CFUNC_DEF("ColorTint",2,js_ColorTint),
		JS_CFUNC_DEF("ColorBrightness",2,js_ColorBrightness),
		JS_CFUNC_DEF("ColorContrast",2,js_ColorContrast),
		JS_CFUNC_DEF("ColorAlpha",2,js_ColorAlpha),
		JS_CFUNC_DEF("ColorAlphaBlend",3,js_ColorAlphaBlend),
		JS_CFUNC_DEF("ColorLerp",3,js_ColorLerp),
		JS_CFUNC_DEF("GetColor",1,js_GetColor),
		JS_CFUNC_DEF("GetPixelColor",2,js_GetPixelColor),
		JS_CFUNC_DEF("SetPixelColor",3,js_SetPixelColor),
		JS_CFUNC_DEF("GetPixelDataSize",3,js_GetPixelDataSize),
		JS_CFUNC_DEF("GetFontDefault",0,js_GetFontDefault),
		JS_CFUNC_DEF("LoadFont",1,js_LoadFont),
		JS_CFUNC_DEF("LoadFontEx",4,js_LoadFontEx),
		JS_CFUNC_DEF("LoadFontFromImage",3,js_LoadFontFromImage),
		JS_CFUNC_DEF("LoadFontFromMemory",6,js_LoadFontFromMemory),
		JS_CFUNC_DEF("IsFontValid",1,js_IsFontValid),
		JS_CFUNC_DEF("LoadFontData",7,js_LoadFontData),
		JS_CFUNC_DEF("GenImageFontAtlas",6,js_GenImageFontAtlas),
		JS_CFUNC_DEF("UnloadFontData",2,js_UnloadFontData),
		JS_CFUNC_DEF("UnloadFont",1,js_UnloadFont),
		JS_CFUNC_DEF("ExportFontAsCode",2,js_ExportFontAsCode),
		JS_CFUNC_DEF("DrawFPS",2,js_DrawFPS),
		JS_CFUNC_DEF("DrawText",5,js_DrawText),
		JS_CFUNC_DEF("DrawTextEx",6,js_DrawTextEx),
		JS_CFUNC_DEF("DrawTextPro",8,js_DrawTextPro),
		JS_CFUNC_DEF("DrawTextCodepoint",5,js_DrawTextCodepoint),
		JS_CFUNC_DEF("DrawTextCodepoints",7,js_DrawTextCodepoints),
		JS_CFUNC_DEF("SetTextLineSpacing",1,js_SetTextLineSpacing),
		JS_CFUNC_DEF("MeasureText",2,js_MeasureText),
		JS_CFUNC_DEF("MeasureTextEx",4,js_MeasureTextEx),
		JS_CFUNC_DEF("GetGlyphIndex",2,js_GetGlyphIndex),
		JS_CFUNC_DEF("GetGlyphInfo",2,js_GetGlyphInfo),
		JS_CFUNC_DEF("GetGlyphAtlasRec",2,js_GetGlyphAtlasRec),
		JS_CFUNC_DEF("LoadUTF8",2,js_LoadUTF8),
		JS_CFUNC_DEF("UnloadUTF8",1,js_UnloadUTF8),
		JS_CFUNC_DEF("LoadCodepoints",2,js_LoadCodepoints),
		JS_CFUNC_DEF("GetCodepointCount",1,js_GetCodepointCount),
		JS_CFUNC_DEF("GetCodepoint",2,js_GetCodepoint),
		JS_CFUNC_DEF("GetCodepointNext",2,js_GetCodepointNext),
		JS_CFUNC_DEF("GetCodepointPrevious",2,js_GetCodepointPrevious),
		JS_CFUNC_DEF("CodepointToUTF8",2,js_CodepointToUTF8),
		JS_CFUNC_DEF("LoadTextLines",2,js_LoadTextLines),
		JS_CFUNC_DEF("UnloadTextLines",2,js_UnloadTextLines),
		JS_CFUNC_DEF("TextIsEqual",2,js_TextIsEqual),
		JS_CFUNC_DEF("TextLength",1,js_TextLength),
		JS_CFUNC_DEF("TextFormat",2,js_TextFormat),
		JS_CFUNC_DEF("TextSubtext",3,js_TextSubtext),
		JS_CFUNC_DEF("TextRemoveSpaces",1,js_TextRemoveSpaces),
		JS_CFUNC_DEF("GetTextBetween",3,js_GetTextBetween),
		JS_CFUNC_DEF("TextReplace",3,js_TextReplace),
		JS_CFUNC_DEF("TextReplaceBetween",4,js_TextReplaceBetween),
		JS_CFUNC_DEF("TextInsert",3,js_TextInsert),
		JS_CFUNC_DEF("TextJoin",3,js_TextJoin),
		JS_CFUNC_DEF("TextSplit",3,js_TextSplit),
		JS_CFUNC_DEF("TextAppend",3,js_TextAppend),
		JS_CFUNC_DEF("TextFindIndex",2,js_TextFindIndex),
		JS_CFUNC_DEF("TextToUpper",1,js_TextToUpper),
		JS_CFUNC_DEF("TextToLower",1,js_TextToLower),
		JS_CFUNC_DEF("TextToPascal",1,js_TextToPascal),
		JS_CFUNC_DEF("TextToSnake",1,js_TextToSnake),
		JS_CFUNC_DEF("TextToCamel",1,js_TextToCamel),
		JS_CFUNC_DEF("TextToInteger",1,js_TextToInteger),
		JS_CFUNC_DEF("TextToFloat",1,js_TextToFloat),
		JS_CFUNC_DEF("DrawLine3D",3,js_DrawLine3D),
		JS_CFUNC_DEF("DrawPoint3D",2,js_DrawPoint3D),
		JS_CFUNC_DEF("DrawCircle3D",5,js_DrawCircle3D),
		JS_CFUNC_DEF("DrawTriangle3D",4,js_DrawTriangle3D),
		JS_CFUNC_DEF("DrawTriangleStrip3D",3,js_DrawTriangleStrip3D),
		JS_CFUNC_DEF("DrawCube",5,js_DrawCube),
		JS_CFUNC_DEF("DrawCubeV",3,js_DrawCubeV),
		JS_CFUNC_DEF("DrawCubeWires",5,js_DrawCubeWires),
		JS_CFUNC_DEF("DrawCubeWiresV",3,js_DrawCubeWiresV),
		JS_CFUNC_DEF("DrawSphere",3,js_DrawSphere),
		JS_CFUNC_DEF("DrawSphereEx",5,js_DrawSphereEx),
		JS_CFUNC_DEF("DrawSphereWires",5,js_DrawSphereWires),
		JS_CFUNC_DEF("DrawCylinder",6,js_DrawCylinder),
		JS_CFUNC_DEF("DrawCylinderEx",6,js_DrawCylinderEx),
		JS_CFUNC_DEF("DrawCylinderWires",6,js_DrawCylinderWires),
		JS_CFUNC_DEF("DrawCylinderWiresEx",6,js_DrawCylinderWiresEx),
		JS_CFUNC_DEF("DrawCapsule",6,js_DrawCapsule),
		JS_CFUNC_DEF("DrawCapsuleWires",6,js_DrawCapsuleWires),
		JS_CFUNC_DEF("DrawPlane",3,js_DrawPlane),
		JS_CFUNC_DEF("DrawRay",2,js_DrawRay),
		JS_CFUNC_DEF("DrawGrid",2,js_DrawGrid),
		JS_CFUNC_DEF("LoadModel",1,js_LoadModel),
		JS_CFUNC_DEF("LoadModelFromMesh",1,js_LoadModelFromMesh),
		JS_CFUNC_DEF("IsModelValid",1,js_IsModelValid),
		JS_CFUNC_DEF("UnloadModel",1,js_UnloadModel),
		JS_CFUNC_DEF("GetModelBoundingBox",1,js_GetModelBoundingBox),
		JS_CFUNC_DEF("DrawModel",4,js_DrawModel),
		JS_CFUNC_DEF("DrawModelEx",6,js_DrawModelEx),
		JS_CFUNC_DEF("DrawModelWires",4,js_DrawModelWires),
		JS_CFUNC_DEF("DrawModelWiresEx",6,js_DrawModelWiresEx),
		JS_CFUNC_DEF("DrawModelPoints",4,js_DrawModelPoints),
		JS_CFUNC_DEF("DrawModelPointsEx",6,js_DrawModelPointsEx),
		JS_CFUNC_DEF("DrawBoundingBox",2,js_DrawBoundingBox),
		JS_CFUNC_DEF("DrawBillboard",5,js_DrawBillboard),
		JS_CFUNC_DEF("DrawBillboardRec",6,js_DrawBillboardRec),
		JS_CFUNC_DEF("DrawBillboardPro",9,js_DrawBillboardPro),
		JS_CFUNC_DEF("UploadMesh",2,js_UploadMesh),
		JS_CFUNC_DEF("UpdateMeshBuffer",5,js_UpdateMeshBuffer),
		JS_CFUNC_DEF("UnloadMesh",1,js_UnloadMesh),
		JS_CFUNC_DEF("DrawMesh",3,js_DrawMesh),
		JS_CFUNC_DEF("DrawMeshInstanced",4,js_DrawMeshInstanced),
		JS_CFUNC_DEF("GetMeshBoundingBox",1,js_GetMeshBoundingBox),
		JS_CFUNC_DEF("GenMeshTangents",1,js_GenMeshTangents),
		JS_CFUNC_DEF("ExportMesh",2,js_ExportMesh),
		JS_CFUNC_DEF("ExportMeshAsCode",2,js_ExportMeshAsCode),
		JS_CFUNC_DEF("GenMeshPoly",2,js_GenMeshPoly),
		JS_CFUNC_DEF("GenMeshPlane",4,js_GenMeshPlane),
		JS_CFUNC_DEF("GenMeshCube",3,js_GenMeshCube),
		JS_CFUNC_DEF("GenMeshSphere",3,js_GenMeshSphere),
		JS_CFUNC_DEF("GenMeshHemiSphere",3,js_GenMeshHemiSphere),
		JS_CFUNC_DEF("GenMeshCylinder",3,js_GenMeshCylinder),
		JS_CFUNC_DEF("GenMeshCone",3,js_GenMeshCone),
		JS_CFUNC_DEF("GenMeshTorus",4,js_GenMeshTorus),
		JS_CFUNC_DEF("GenMeshKnot",4,js_GenMeshKnot),
		JS_CFUNC_DEF("GenMeshHeightmap",2,js_GenMeshHeightmap),
		JS_CFUNC_DEF("GenMeshCubicmap",2,js_GenMeshCubicmap),
		JS_CFUNC_DEF("LoadMaterials",2,js_LoadMaterials),
		JS_CFUNC_DEF("LoadMaterialDefault",0,js_LoadMaterialDefault),
		JS_CFUNC_DEF("IsMaterialValid",1,js_IsMaterialValid),
		JS_CFUNC_DEF("UnloadMaterial",1,js_UnloadMaterial),
		JS_CFUNC_DEF("SetMaterialTexture",3,js_SetMaterialTexture),
		JS_CFUNC_DEF("SetModelMeshMaterial",3,js_SetModelMeshMaterial),
		JS_CFUNC_DEF("LoadModelAnimations",2,js_LoadModelAnimations),
		JS_CFUNC_DEF("UpdateModelAnimation",3,js_UpdateModelAnimation),
		JS_CFUNC_DEF("UpdateModelAnimationBones",3,js_UpdateModelAnimationBones),
		JS_CFUNC_DEF("UnloadModelAnimation",1,js_UnloadModelAnimation),
		JS_CFUNC_DEF("UnloadModelAnimations",2,js_UnloadModelAnimations),
		JS_CFUNC_DEF("IsModelAnimationValid",2,js_IsModelAnimationValid),
		JS_CFUNC_DEF("CheckCollisionSpheres",4,js_CheckCollisionSpheres),
		JS_CFUNC_DEF("CheckCollisionBoxes",2,js_CheckCollisionBoxes),
		JS_CFUNC_DEF("CheckCollisionBoxSphere",3,js_CheckCollisionBoxSphere),
		JS_CFUNC_DEF("GetRayCollisionSphere",3,js_GetRayCollisionSphere),
		JS_CFUNC_DEF("GetRayCollisionBox",2,js_GetRayCollisionBox),
		JS_CFUNC_DEF("GetRayCollisionMesh",3,js_GetRayCollisionMesh),
		JS_CFUNC_DEF("GetRayCollisionTriangle",4,js_GetRayCollisionTriangle),
		JS_CFUNC_DEF("GetRayCollisionQuad",5,js_GetRayCollisionQuad),
		JS_CFUNC_DEF("InitAudioDevice",0,js_InitAudioDevice),
		JS_CFUNC_DEF("CloseAudioDevice",0,js_CloseAudioDevice),
		JS_CFUNC_DEF("IsAudioDeviceReady",0,js_IsAudioDeviceReady),
		JS_CFUNC_DEF("SetMasterVolume",1,js_SetMasterVolume),
		JS_CFUNC_DEF("GetMasterVolume",0,js_GetMasterVolume),
		JS_CFUNC_DEF("LoadWave",1,js_LoadWave),
		JS_CFUNC_DEF("LoadWaveFromMemory",3,js_LoadWaveFromMemory),
		JS_CFUNC_DEF("IsWaveValid",1,js_IsWaveValid),
		JS_CFUNC_DEF("LoadSound",1,js_LoadSound),
		JS_CFUNC_DEF("LoadSoundFromWave",1,js_LoadSoundFromWave),
		JS_CFUNC_DEF("LoadSoundAlias",1,js_LoadSoundAlias),
		JS_CFUNC_DEF("IsSoundValid",1,js_IsSoundValid),
		JS_CFUNC_DEF("UpdateSound",3,js_UpdateSound),
		JS_CFUNC_DEF("UnloadWave",1,js_UnloadWave),
		JS_CFUNC_DEF("UnloadSound",1,js_UnloadSound),
		JS_CFUNC_DEF("UnloadSoundAlias",1,js_UnloadSoundAlias),
		JS_CFUNC_DEF("ExportWave",2,js_ExportWave),
		JS_CFUNC_DEF("ExportWaveAsCode",2,js_ExportWaveAsCode),
		JS_CFUNC_DEF("PlaySound",1,js_PlaySound),
		JS_CFUNC_DEF("StopSound",1,js_StopSound),
		JS_CFUNC_DEF("PauseSound",1,js_PauseSound),
		JS_CFUNC_DEF("ResumeSound",1,js_ResumeSound),
		JS_CFUNC_DEF("IsSoundPlaying",1,js_IsSoundPlaying),
		JS_CFUNC_DEF("SetSoundVolume",2,js_SetSoundVolume),
		JS_CFUNC_DEF("SetSoundPitch",2,js_SetSoundPitch),
		JS_CFUNC_DEF("SetSoundPan",2,js_SetSoundPan),
		JS_CFUNC_DEF("WaveCopy",1,js_WaveCopy),
		JS_CFUNC_DEF("WaveCrop",3,js_WaveCrop),
		JS_CFUNC_DEF("WaveFormat",4,js_WaveFormat),
		JS_CFUNC_DEF("LoadWaveSamples",1,js_LoadWaveSamples),
		JS_CFUNC_DEF("UnloadWaveSamples",1,js_UnloadWaveSamples),
		JS_CFUNC_DEF("LoadMusicStream",1,js_LoadMusicStream),
		JS_CFUNC_DEF("LoadMusicStreamFromMemory",3,js_LoadMusicStreamFromMemory),
		JS_CFUNC_DEF("IsMusicValid",1,js_IsMusicValid),
		JS_CFUNC_DEF("UnloadMusicStream",1,js_UnloadMusicStream),
		JS_CFUNC_DEF("PlayMusicStream",1,js_PlayMusicStream),
		JS_CFUNC_DEF("IsMusicStreamPlaying",1,js_IsMusicStreamPlaying),
		JS_CFUNC_DEF("UpdateMusicStream",1,js_UpdateMusicStream),
		JS_CFUNC_DEF("StopMusicStream",1,js_StopMusicStream),
		JS_CFUNC_DEF("PauseMusicStream",1,js_PauseMusicStream),
		JS_CFUNC_DEF("ResumeMusicStream",1,js_ResumeMusicStream),
		JS_CFUNC_DEF("SeekMusicStream",2,js_SeekMusicStream),
		JS_CFUNC_DEF("SetMusicVolume",2,js_SetMusicVolume),
		JS_CFUNC_DEF("SetMusicPitch",2,js_SetMusicPitch),
		JS_CFUNC_DEF("SetMusicPan",2,js_SetMusicPan),
		JS_CFUNC_DEF("GetMusicTimeLength",1,js_GetMusicTimeLength),
		JS_CFUNC_DEF("GetMusicTimePlayed",1,js_GetMusicTimePlayed),
		JS_CFUNC_DEF("LoadAudioStream",3,js_LoadAudioStream),
		JS_CFUNC_DEF("IsAudioStreamValid",1,js_IsAudioStreamValid),
		JS_CFUNC_DEF("UnloadAudioStream",1,js_UnloadAudioStream),
		JS_CFUNC_DEF("UpdateAudioStream",3,js_UpdateAudioStream),
		JS_CFUNC_DEF("IsAudioStreamProcessed",1,js_IsAudioStreamProcessed),
		JS_CFUNC_DEF("PlayAudioStream",1,js_PlayAudioStream),
		JS_CFUNC_DEF("PauseAudioStream",1,js_PauseAudioStream),
		JS_CFUNC_DEF("ResumeAudioStream",1,js_ResumeAudioStream),
		JS_CFUNC_DEF("IsAudioStreamPlaying",1,js_IsAudioStreamPlaying),
		JS_CFUNC_DEF("StopAudioStream",1,js_StopAudioStream),
		JS_CFUNC_DEF("SetAudioStreamVolume",2,js_SetAudioStreamVolume),
		JS_CFUNC_DEF("SetAudioStreamPitch",2,js_SetAudioStreamPitch),
		JS_CFUNC_DEF("SetAudioStreamPan",2,js_SetAudioStreamPan),
		JS_CFUNC_DEF("SetAudioStreamBufferSizeDefault",1,js_SetAudioStreamBufferSizeDefault),
		JS_CFUNC_DEF("AttachAudioMixedProcessor",1,js_AttachAudioMixedProcessor),
		JS_CFUNC_DEF("DetachAudioMixedProcessor",1,js_DetachAudioMixedProcessor),
		JS_CFUNC_DEF("GetMouseRay",2,js_GetMouseRay)
	};
	
	static int js_raylib_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsraylib_funcs);
		JS_SetModuleExportList(ctx,m,jsraylib_funcs,(int)listcount);
		js_declare_Vector2(ctx,m);
		JSValue Vector2_constr=JS_NewCFunction2(ctx,js_Vector2_constructor,(const char  *)"Vector2",(int)2,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Vector2",Vector2_constr);
		js_declare_Vector3(ctx,m);
		JSValue Vector3_constr=JS_NewCFunction2(ctx,js_Vector3_constructor,(const char  *)"Vector3",(int)3,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Vector3",Vector3_constr);
		js_declare_Vector4(ctx,m);
		JSValue Vector4_constr=JS_NewCFunction2(ctx,js_Vector4_constructor,(const char  *)"Vector4",(int)4,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Vector4",Vector4_constr);
		js_declare_Matrix(ctx,m);
		JSValue Matrix_constr=JS_NewCFunction2(ctx,js_Matrix_constructor,(const char  *)"Matrix",(int)16,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Matrix",Matrix_constr);
		js_declare_Color(ctx,m);
		JSValue Color_constr=JS_NewCFunction2(ctx,js_Color_constructor,(const char  *)"Color",(int)4,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Color",Color_constr);
		js_declare_Rectangle(ctx,m);
		JSValue Rectangle_constr=JS_NewCFunction2(ctx,js_Rectangle_constructor,(const char  *)"Rectangle",(int)4,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Rectangle",Rectangle_constr);
		js_declare_Image(ctx,m);
		JSValue Image_constr=JS_NewCFunction2(ctx,js_Image_constructor,(const char  *)"Image",(int)5,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Image",Image_constr);
		js_declare_Texture(ctx,m);
		JSValue Texture_constr=JS_NewCFunction2(ctx,js_Texture_constructor,(const char  *)"Texture",(int)5,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Texture",Texture_constr);
		js_declare_RenderTexture(ctx,m);
		JSValue RenderTexture_constr=JS_NewCFunction2(ctx,js_RenderTexture_constructor,(const char  *)"RenderTexture",(int)3,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"RenderTexture",RenderTexture_constr);
		js_declare_NPatchInfo(ctx,m);
		JSValue NPatchInfo_constr=JS_NewCFunction2(ctx,js_NPatchInfo_constructor,(const char  *)"NPatchInfo",(int)6,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"NPatchInfo",NPatchInfo_constr);
		js_declare_GlyphInfo(ctx,m);
		JSValue GlyphInfo_constr=JS_NewCFunction2(ctx,js_GlyphInfo_constructor,(const char  *)"GlyphInfo",(int)5,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"GlyphInfo",GlyphInfo_constr);
		js_declare_Font(ctx,m);
		JSValue Font_constr=JS_NewCFunction2(ctx,js_Font_constructor,(const char  *)"Font",(int)6,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Font",Font_constr);
		js_declare_Camera3D(ctx,m);
		JSValue Camera3D_constr=JS_NewCFunction2(ctx,js_Camera3D_constructor,(const char  *)"Camera3D",(int)5,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Camera3D",Camera3D_constr);
		js_declare_Camera2D(ctx,m);
		JSValue Camera2D_constr=JS_NewCFunction2(ctx,js_Camera2D_constructor,(const char  *)"Camera2D",(int)4,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Camera2D",Camera2D_constr);
		js_declare_Mesh(ctx,m);
		JSValue Mesh_constr=JS_NewCFunction2(ctx,js_Mesh_constructor,(const char  *)"Mesh",(int)17,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Mesh",Mesh_constr);
		js_declare_Shader(ctx,m);
		JSValue Shader_constr=JS_NewCFunction2(ctx,js_Shader_constructor,(const char  *)"Shader",(int)2,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Shader",Shader_constr);
		js_declare_MaterialMap(ctx,m);
		JSValue MaterialMap_constr=JS_NewCFunction2(ctx,js_MaterialMap_constructor,(const char  *)"MaterialMap",(int)3,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"MaterialMap",MaterialMap_constr);
		js_declare_Material(ctx,m);
		JSValue Material_constr=JS_NewCFunction2(ctx,js_Material_constructor,(const char  *)"Material",(int)3,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Material",Material_constr);
		js_declare_Transform(ctx,m);
		JSValue Transform_constr=JS_NewCFunction2(ctx,js_Transform_constructor,(const char  *)"Transform",(int)3,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Transform",Transform_constr);
		js_declare_BoneInfo(ctx,m);
		JSValue BoneInfo_constr=JS_NewCFunction2(ctx,js_BoneInfo_constructor,(const char  *)"BoneInfo",(int)2,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"BoneInfo",BoneInfo_constr);
		js_declare_Model(ctx,m);
		JSValue Model_constr=JS_NewCFunction2(ctx,js_Model_constructor,(const char  *)"Model",(int)9,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Model",Model_constr);
		js_declare_ModelAnimation(ctx,m);
		JSValue ModelAnimation_constr=JS_NewCFunction2(ctx,js_ModelAnimation_constructor,(const char  *)"ModelAnimation",(int)5,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"ModelAnimation",ModelAnimation_constr);
		js_declare_Ray(ctx,m);
		JSValue Ray_constr=JS_NewCFunction2(ctx,js_Ray_constructor,(const char  *)"Ray",(int)2,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Ray",Ray_constr);
		js_declare_RayCollision(ctx,m);
		JSValue RayCollision_constr=JS_NewCFunction2(ctx,js_RayCollision_constructor,(const char  *)"RayCollision",(int)4,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"RayCollision",RayCollision_constr);
		js_declare_BoundingBox(ctx,m);
		JSValue BoundingBox_constr=JS_NewCFunction2(ctx,js_BoundingBox_constructor,(const char  *)"BoundingBox",(int)2,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"BoundingBox",BoundingBox_constr);
		js_declare_Wave(ctx,m);
		JSValue Wave_constr=JS_NewCFunction2(ctx,js_Wave_constructor,(const char  *)"Wave",(int)5,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Wave",Wave_constr);
		js_declare_rAudioBuffer(ctx,m);
		js_declare_rAudioProcessor(ctx,m);
		js_declare_AudioStream(ctx,m);
		JSValue AudioStream_constr=JS_NewCFunction2(ctx,js_AudioStream_constructor,(const char  *)"AudioStream",(int)5,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"AudioStream",AudioStream_constr);
		js_declare_Sound(ctx,m);
		JSValue Sound_constr=JS_NewCFunction2(ctx,js_Sound_constructor,(const char  *)"Sound",(int)2,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Sound",Sound_constr);
		js_declare_Music(ctx,m);
		JSValue Music_constr=JS_NewCFunction2(ctx,js_Music_constructor,(const char  *)"Music",(int)5,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Music",Music_constr);
		js_declare_VrDeviceInfo(ctx,m);
		JSValue VrDeviceInfo_constr=JS_NewCFunction2(ctx,js_VrDeviceInfo_constructor,(const char  *)"VrDeviceInfo",(int)9,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"VrDeviceInfo",VrDeviceInfo_constr);
		js_declare_VrStereoConfig(ctx,m);
		JSValue VrStereoConfig_constr=JS_NewCFunction2(ctx,js_VrStereoConfig_constructor,(const char  *)"VrStereoConfig",(int)8,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"VrStereoConfig",VrStereoConfig_constr);
		js_declare_FilePathList(ctx,m);
		JSValue FilePathList_constr=JS_NewCFunction2(ctx,js_FilePathList_constructor,(const char  *)"FilePathList",(int)3,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"FilePathList",FilePathList_constr);
		js_declare_AutomationEvent(ctx,m);
		JSValue AutomationEvent_constr=JS_NewCFunction2(ctx,js_AutomationEvent_constructor,(const char  *)"AutomationEvent",(int)3,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"AutomationEvent",AutomationEvent_constr);
		js_declare_AutomationEventList(ctx,m);
		JSValue AutomationEventList_constr=JS_NewCFunction2(ctx,js_AutomationEventList_constructor,(const char  *)"AutomationEventList",(int)3,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"AutomationEventList",AutomationEventList_constr);
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_VSYNC_HINT",JS_NewInt32(ctx,(int32_t)FLAG_VSYNC_HINT));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_FULLSCREEN_MODE",JS_NewInt32(ctx,(int32_t)FLAG_FULLSCREEN_MODE));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_RESIZABLE",JS_NewInt32(ctx,(int32_t)FLAG_WINDOW_RESIZABLE));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_UNDECORATED",JS_NewInt32(ctx,(int32_t)FLAG_WINDOW_UNDECORATED));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_HIDDEN",JS_NewInt32(ctx,(int32_t)FLAG_WINDOW_HIDDEN));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_MINIMIZED",JS_NewInt32(ctx,(int32_t)FLAG_WINDOW_MINIMIZED));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_MAXIMIZED",JS_NewInt32(ctx,(int32_t)FLAG_WINDOW_MAXIMIZED));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_UNFOCUSED",JS_NewInt32(ctx,(int32_t)FLAG_WINDOW_UNFOCUSED));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_TOPMOST",JS_NewInt32(ctx,(int32_t)FLAG_WINDOW_TOPMOST));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_ALWAYS_RUN",JS_NewInt32(ctx,(int32_t)FLAG_WINDOW_ALWAYS_RUN));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_TRANSPARENT",JS_NewInt32(ctx,(int32_t)FLAG_WINDOW_TRANSPARENT));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_HIGHDPI",JS_NewInt32(ctx,(int32_t)FLAG_WINDOW_HIGHDPI));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_MOUSE_PASSTHROUGH",JS_NewInt32(ctx,(int32_t)FLAG_WINDOW_MOUSE_PASSTHROUGH));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_BORDERLESS_WINDOWED_MODE",JS_NewInt32(ctx,(int32_t)FLAG_BORDERLESS_WINDOWED_MODE));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_MSAA_4X_HINT",JS_NewInt32(ctx,(int32_t)FLAG_MSAA_4X_HINT));
		JS_SetModuleExport(ctx,m,(const char  *)"FLAG_INTERLACED_HINT",JS_NewInt32(ctx,(int32_t)FLAG_INTERLACED_HINT));
		JS_SetModuleExport(ctx,m,(const char  *)"LOG_ALL",JS_NewInt32(ctx,(int32_t)LOG_ALL));
		JS_SetModuleExport(ctx,m,(const char  *)"LOG_TRACE",JS_NewInt32(ctx,(int32_t)LOG_TRACE));
		JS_SetModuleExport(ctx,m,(const char  *)"LOG_DEBUG",JS_NewInt32(ctx,(int32_t)LOG_DEBUG));
		JS_SetModuleExport(ctx,m,(const char  *)"LOG_INFO",JS_NewInt32(ctx,(int32_t)LOG_INFO));
		JS_SetModuleExport(ctx,m,(const char  *)"LOG_WARNING",JS_NewInt32(ctx,(int32_t)LOG_WARNING));
		JS_SetModuleExport(ctx,m,(const char  *)"LOG_ERROR",JS_NewInt32(ctx,(int32_t)LOG_ERROR));
		JS_SetModuleExport(ctx,m,(const char  *)"LOG_FATAL",JS_NewInt32(ctx,(int32_t)LOG_FATAL));
		JS_SetModuleExport(ctx,m,(const char  *)"LOG_NONE",JS_NewInt32(ctx,(int32_t)LOG_NONE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_NULL",JS_NewInt32(ctx,(int32_t)KEY_NULL));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_APOSTROPHE",JS_NewInt32(ctx,(int32_t)KEY_APOSTROPHE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_COMMA",JS_NewInt32(ctx,(int32_t)KEY_COMMA));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_MINUS",JS_NewInt32(ctx,(int32_t)KEY_MINUS));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_PERIOD",JS_NewInt32(ctx,(int32_t)KEY_PERIOD));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_SLASH",JS_NewInt32(ctx,(int32_t)KEY_SLASH));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_ZERO",JS_NewInt32(ctx,(int32_t)KEY_ZERO));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_ONE",JS_NewInt32(ctx,(int32_t)KEY_ONE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_TWO",JS_NewInt32(ctx,(int32_t)KEY_TWO));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_THREE",JS_NewInt32(ctx,(int32_t)KEY_THREE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_FOUR",JS_NewInt32(ctx,(int32_t)KEY_FOUR));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_FIVE",JS_NewInt32(ctx,(int32_t)KEY_FIVE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_SIX",JS_NewInt32(ctx,(int32_t)KEY_SIX));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_SEVEN",JS_NewInt32(ctx,(int32_t)KEY_SEVEN));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_EIGHT",JS_NewInt32(ctx,(int32_t)KEY_EIGHT));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_NINE",JS_NewInt32(ctx,(int32_t)KEY_NINE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_SEMICOLON",JS_NewInt32(ctx,(int32_t)KEY_SEMICOLON));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_EQUAL",JS_NewInt32(ctx,(int32_t)KEY_EQUAL));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_A",JS_NewInt32(ctx,(int32_t)KEY_A));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_B",JS_NewInt32(ctx,(int32_t)KEY_B));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_C",JS_NewInt32(ctx,(int32_t)KEY_C));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_D",JS_NewInt32(ctx,(int32_t)KEY_D));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_E",JS_NewInt32(ctx,(int32_t)KEY_E));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F",JS_NewInt32(ctx,(int32_t)KEY_F));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_G",JS_NewInt32(ctx,(int32_t)KEY_G));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_H",JS_NewInt32(ctx,(int32_t)KEY_H));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_I",JS_NewInt32(ctx,(int32_t)KEY_I));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_J",JS_NewInt32(ctx,(int32_t)KEY_J));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_K",JS_NewInt32(ctx,(int32_t)KEY_K));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_L",JS_NewInt32(ctx,(int32_t)KEY_L));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_M",JS_NewInt32(ctx,(int32_t)KEY_M));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_N",JS_NewInt32(ctx,(int32_t)KEY_N));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_O",JS_NewInt32(ctx,(int32_t)KEY_O));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_P",JS_NewInt32(ctx,(int32_t)KEY_P));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_Q",JS_NewInt32(ctx,(int32_t)KEY_Q));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_R",JS_NewInt32(ctx,(int32_t)KEY_R));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_S",JS_NewInt32(ctx,(int32_t)KEY_S));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_T",JS_NewInt32(ctx,(int32_t)KEY_T));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_U",JS_NewInt32(ctx,(int32_t)KEY_U));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_V",JS_NewInt32(ctx,(int32_t)KEY_V));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_W",JS_NewInt32(ctx,(int32_t)KEY_W));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_X",JS_NewInt32(ctx,(int32_t)KEY_X));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_Y",JS_NewInt32(ctx,(int32_t)KEY_Y));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_Z",JS_NewInt32(ctx,(int32_t)KEY_Z));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_LEFT_BRACKET",JS_NewInt32(ctx,(int32_t)KEY_LEFT_BRACKET));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_BACKSLASH",JS_NewInt32(ctx,(int32_t)KEY_BACKSLASH));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_RIGHT_BRACKET",JS_NewInt32(ctx,(int32_t)KEY_RIGHT_BRACKET));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_GRAVE",JS_NewInt32(ctx,(int32_t)KEY_GRAVE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_SPACE",JS_NewInt32(ctx,(int32_t)KEY_SPACE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_ESCAPE",JS_NewInt32(ctx,(int32_t)KEY_ESCAPE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_ENTER",JS_NewInt32(ctx,(int32_t)KEY_ENTER));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_TAB",JS_NewInt32(ctx,(int32_t)KEY_TAB));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_BACKSPACE",JS_NewInt32(ctx,(int32_t)KEY_BACKSPACE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_INSERT",JS_NewInt32(ctx,(int32_t)KEY_INSERT));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_DELETE",JS_NewInt32(ctx,(int32_t)KEY_DELETE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_RIGHT",JS_NewInt32(ctx,(int32_t)KEY_RIGHT));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_LEFT",JS_NewInt32(ctx,(int32_t)KEY_LEFT));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_DOWN",JS_NewInt32(ctx,(int32_t)KEY_DOWN));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_UP",JS_NewInt32(ctx,(int32_t)KEY_UP));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_PAGE_UP",JS_NewInt32(ctx,(int32_t)KEY_PAGE_UP));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_PAGE_DOWN",JS_NewInt32(ctx,(int32_t)KEY_PAGE_DOWN));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_HOME",JS_NewInt32(ctx,(int32_t)KEY_HOME));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_END",JS_NewInt32(ctx,(int32_t)KEY_END));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_CAPS_LOCK",JS_NewInt32(ctx,(int32_t)KEY_CAPS_LOCK));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_SCROLL_LOCK",JS_NewInt32(ctx,(int32_t)KEY_SCROLL_LOCK));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_NUM_LOCK",JS_NewInt32(ctx,(int32_t)KEY_NUM_LOCK));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_PRINT_SCREEN",JS_NewInt32(ctx,(int32_t)KEY_PRINT_SCREEN));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_PAUSE",JS_NewInt32(ctx,(int32_t)KEY_PAUSE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F1",JS_NewInt32(ctx,(int32_t)KEY_F1));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F2",JS_NewInt32(ctx,(int32_t)KEY_F2));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F3",JS_NewInt32(ctx,(int32_t)KEY_F3));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F4",JS_NewInt32(ctx,(int32_t)KEY_F4));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F5",JS_NewInt32(ctx,(int32_t)KEY_F5));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F6",JS_NewInt32(ctx,(int32_t)KEY_F6));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F7",JS_NewInt32(ctx,(int32_t)KEY_F7));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F8",JS_NewInt32(ctx,(int32_t)KEY_F8));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F9",JS_NewInt32(ctx,(int32_t)KEY_F9));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F10",JS_NewInt32(ctx,(int32_t)KEY_F10));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F11",JS_NewInt32(ctx,(int32_t)KEY_F11));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_F12",JS_NewInt32(ctx,(int32_t)KEY_F12));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_LEFT_SHIFT",JS_NewInt32(ctx,(int32_t)KEY_LEFT_SHIFT));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_LEFT_CONTROL",JS_NewInt32(ctx,(int32_t)KEY_LEFT_CONTROL));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_LEFT_ALT",JS_NewInt32(ctx,(int32_t)KEY_LEFT_ALT));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_LEFT_SUPER",JS_NewInt32(ctx,(int32_t)KEY_LEFT_SUPER));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_RIGHT_SHIFT",JS_NewInt32(ctx,(int32_t)KEY_RIGHT_SHIFT));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_RIGHT_CONTROL",JS_NewInt32(ctx,(int32_t)KEY_RIGHT_CONTROL));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_RIGHT_ALT",JS_NewInt32(ctx,(int32_t)KEY_RIGHT_ALT));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_RIGHT_SUPER",JS_NewInt32(ctx,(int32_t)KEY_RIGHT_SUPER));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KB_MENU",JS_NewInt32(ctx,(int32_t)KEY_KB_MENU));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_0",JS_NewInt32(ctx,(int32_t)KEY_KP_0));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_1",JS_NewInt32(ctx,(int32_t)KEY_KP_1));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_2",JS_NewInt32(ctx,(int32_t)KEY_KP_2));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_3",JS_NewInt32(ctx,(int32_t)KEY_KP_3));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_4",JS_NewInt32(ctx,(int32_t)KEY_KP_4));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_5",JS_NewInt32(ctx,(int32_t)KEY_KP_5));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_6",JS_NewInt32(ctx,(int32_t)KEY_KP_6));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_7",JS_NewInt32(ctx,(int32_t)KEY_KP_7));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_8",JS_NewInt32(ctx,(int32_t)KEY_KP_8));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_9",JS_NewInt32(ctx,(int32_t)KEY_KP_9));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_DECIMAL",JS_NewInt32(ctx,(int32_t)KEY_KP_DECIMAL));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_DIVIDE",JS_NewInt32(ctx,(int32_t)KEY_KP_DIVIDE));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_MULTIPLY",JS_NewInt32(ctx,(int32_t)KEY_KP_MULTIPLY));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_SUBTRACT",JS_NewInt32(ctx,(int32_t)KEY_KP_SUBTRACT));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_ADD",JS_NewInt32(ctx,(int32_t)KEY_KP_ADD));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_ENTER",JS_NewInt32(ctx,(int32_t)KEY_KP_ENTER));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_KP_EQUAL",JS_NewInt32(ctx,(int32_t)KEY_KP_EQUAL));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_BACK",JS_NewInt32(ctx,(int32_t)KEY_BACK));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_MENU",JS_NewInt32(ctx,(int32_t)KEY_MENU));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_VOLUME_UP",JS_NewInt32(ctx,(int32_t)KEY_VOLUME_UP));
		JS_SetModuleExport(ctx,m,(const char  *)"KEY_VOLUME_DOWN",JS_NewInt32(ctx,(int32_t)KEY_VOLUME_DOWN));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_LEFT",JS_NewInt32(ctx,(int32_t)MOUSE_BUTTON_LEFT));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_RIGHT",JS_NewInt32(ctx,(int32_t)MOUSE_BUTTON_RIGHT));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_MIDDLE",JS_NewInt32(ctx,(int32_t)MOUSE_BUTTON_MIDDLE));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_SIDE",JS_NewInt32(ctx,(int32_t)MOUSE_BUTTON_SIDE));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_EXTRA",JS_NewInt32(ctx,(int32_t)MOUSE_BUTTON_EXTRA));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_FORWARD",JS_NewInt32(ctx,(int32_t)MOUSE_BUTTON_FORWARD));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_BACK",JS_NewInt32(ctx,(int32_t)MOUSE_BUTTON_BACK));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_LEFT_BUTTON",JS_NewInt32(ctx,(int32_t)MOUSE_LEFT_BUTTON));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_RIGHT_BUTTON",JS_NewInt32(ctx,(int32_t)MOUSE_RIGHT_BUTTON));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_MIDDLE_BUTTON",JS_NewInt32(ctx,(int32_t)MOUSE_MIDDLE_BUTTON));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_DEFAULT",JS_NewInt32(ctx,(int32_t)MOUSE_CURSOR_DEFAULT));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_ARROW",JS_NewInt32(ctx,(int32_t)MOUSE_CURSOR_ARROW));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_IBEAM",JS_NewInt32(ctx,(int32_t)MOUSE_CURSOR_IBEAM));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_CROSSHAIR",JS_NewInt32(ctx,(int32_t)MOUSE_CURSOR_CROSSHAIR));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_POINTING_HAND",JS_NewInt32(ctx,(int32_t)MOUSE_CURSOR_POINTING_HAND));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_RESIZE_EW",JS_NewInt32(ctx,(int32_t)MOUSE_CURSOR_RESIZE_EW));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_RESIZE_NS",JS_NewInt32(ctx,(int32_t)MOUSE_CURSOR_RESIZE_NS));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_RESIZE_NWSE",JS_NewInt32(ctx,(int32_t)MOUSE_CURSOR_RESIZE_NWSE));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_RESIZE_NESW",JS_NewInt32(ctx,(int32_t)MOUSE_CURSOR_RESIZE_NESW));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_RESIZE_ALL",JS_NewInt32(ctx,(int32_t)MOUSE_CURSOR_RESIZE_ALL));
		JS_SetModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_NOT_ALLOWED",JS_NewInt32(ctx,(int32_t)MOUSE_CURSOR_NOT_ALLOWED));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_UNKNOWN",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_UNKNOWN));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_FACE_UP",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_LEFT_FACE_UP));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_FACE_RIGHT",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_LEFT_FACE_RIGHT));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_FACE_DOWN",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_LEFT_FACE_DOWN));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_FACE_LEFT",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_LEFT_FACE_LEFT));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_FACE_UP",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_RIGHT_FACE_UP));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_FACE_RIGHT",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_RIGHT_FACE_RIGHT));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_FACE_DOWN",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_RIGHT_FACE_DOWN));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_FACE_LEFT",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_RIGHT_FACE_LEFT));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_TRIGGER_1",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_LEFT_TRIGGER_1));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_TRIGGER_2",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_LEFT_TRIGGER_2));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_TRIGGER_1",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_RIGHT_TRIGGER_1));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_TRIGGER_2",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_RIGHT_TRIGGER_2));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_MIDDLE_LEFT",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_MIDDLE_LEFT));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_MIDDLE",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_MIDDLE));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_MIDDLE_RIGHT",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_MIDDLE_RIGHT));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_THUMB",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_LEFT_THUMB));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_THUMB",JS_NewInt32(ctx,(int32_t)GAMEPAD_BUTTON_RIGHT_THUMB));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_LEFT_X",JS_NewInt32(ctx,(int32_t)GAMEPAD_AXIS_LEFT_X));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_LEFT_Y",JS_NewInt32(ctx,(int32_t)GAMEPAD_AXIS_LEFT_Y));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_RIGHT_X",JS_NewInt32(ctx,(int32_t)GAMEPAD_AXIS_RIGHT_X));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_RIGHT_Y",JS_NewInt32(ctx,(int32_t)GAMEPAD_AXIS_RIGHT_Y));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_LEFT_TRIGGER",JS_NewInt32(ctx,(int32_t)GAMEPAD_AXIS_LEFT_TRIGGER));
		JS_SetModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_RIGHT_TRIGGER",JS_NewInt32(ctx,(int32_t)GAMEPAD_AXIS_RIGHT_TRIGGER));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_ALBEDO",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_ALBEDO));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_METALNESS",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_METALNESS));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_NORMAL",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_NORMAL));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_ROUGHNESS",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_ROUGHNESS));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_OCCLUSION",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_OCCLUSION));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_EMISSION",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_EMISSION));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_HEIGHT",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_HEIGHT));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_CUBEMAP",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_CUBEMAP));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_IRRADIANCE",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_IRRADIANCE));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_PREFILTER",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_PREFILTER));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_BRDF",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_BRDF));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_DIFFUSE",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_DIFFUSE));
		JS_SetModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_SPECULAR",JS_NewInt32(ctx,(int32_t)MATERIAL_MAP_SPECULAR));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_POSITION",JS_NewInt32(ctx,(int32_t)SHADER_LOC_VERTEX_POSITION));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_TEXCOORD01",JS_NewInt32(ctx,(int32_t)SHADER_LOC_VERTEX_TEXCOORD01));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_TEXCOORD02",JS_NewInt32(ctx,(int32_t)SHADER_LOC_VERTEX_TEXCOORD02));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_NORMAL",JS_NewInt32(ctx,(int32_t)SHADER_LOC_VERTEX_NORMAL));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_TANGENT",JS_NewInt32(ctx,(int32_t)SHADER_LOC_VERTEX_TANGENT));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_COLOR",JS_NewInt32(ctx,(int32_t)SHADER_LOC_VERTEX_COLOR));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MATRIX_MVP",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MATRIX_MVP));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MATRIX_VIEW",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MATRIX_VIEW));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MATRIX_PROJECTION",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MATRIX_PROJECTION));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MATRIX_MODEL",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MATRIX_MODEL));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MATRIX_NORMAL",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MATRIX_NORMAL));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_VECTOR_VIEW",JS_NewInt32(ctx,(int32_t)SHADER_LOC_VECTOR_VIEW));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_COLOR_DIFFUSE",JS_NewInt32(ctx,(int32_t)SHADER_LOC_COLOR_DIFFUSE));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_COLOR_SPECULAR",JS_NewInt32(ctx,(int32_t)SHADER_LOC_COLOR_SPECULAR));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_COLOR_AMBIENT",JS_NewInt32(ctx,(int32_t)SHADER_LOC_COLOR_AMBIENT));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_ALBEDO",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_ALBEDO));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_METALNESS",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_METALNESS));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_NORMAL",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_NORMAL));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_ROUGHNESS",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_ROUGHNESS));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_OCCLUSION",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_OCCLUSION));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_EMISSION",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_EMISSION));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_HEIGHT",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_HEIGHT));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_CUBEMAP",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_CUBEMAP));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_IRRADIANCE",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_IRRADIANCE));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_PREFILTER",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_PREFILTER));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_BRDF",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_BRDF));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_BONEIDS",JS_NewInt32(ctx,(int32_t)SHADER_LOC_VERTEX_BONEIDS));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_BONEWEIGHTS",JS_NewInt32(ctx,(int32_t)SHADER_LOC_VERTEX_BONEWEIGHTS));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_BONE_MATRICES",JS_NewInt32(ctx,(int32_t)SHADER_LOC_BONE_MATRICES));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_INSTANCE_TX",JS_NewInt32(ctx,(int32_t)SHADER_LOC_VERTEX_INSTANCE_TX));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_DIFFUSE",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_DIFFUSE));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_SPECULAR",JS_NewInt32(ctx,(int32_t)SHADER_LOC_MAP_SPECULAR));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_FLOAT",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_FLOAT));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_VEC2",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_VEC2));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_VEC3",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_VEC3));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_VEC4",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_VEC4));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_INT",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_INT));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_IVEC2",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_IVEC2));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_IVEC3",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_IVEC3));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_IVEC4",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_IVEC4));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_UINT",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_UINT));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_UIVEC2",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_UIVEC2));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_UIVEC3",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_UIVEC3));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_UIVEC4",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_UIVEC4));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_SAMPLER2D",JS_NewInt32(ctx,(int32_t)SHADER_UNIFORM_SAMPLER2D));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_ATTRIB_FLOAT",JS_NewInt32(ctx,(int32_t)SHADER_ATTRIB_FLOAT));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_ATTRIB_VEC2",JS_NewInt32(ctx,(int32_t)SHADER_ATTRIB_VEC2));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_ATTRIB_VEC3",JS_NewInt32(ctx,(int32_t)SHADER_ATTRIB_VEC3));
		JS_SetModuleExport(ctx,m,(const char  *)"SHADER_ATTRIB_VEC4",JS_NewInt32(ctx,(int32_t)SHADER_ATTRIB_VEC4));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_GRAYSCALE",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_GRAYSCALE));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R5G6B5",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_R5G6B5));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R8G8B8",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_R8G8B8));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R5G5B5A1",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_R5G5B5A1));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R4G4B4A4",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_R4G4B4A4));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R8G8B8A8",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_R8G8B8A8));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R32",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_R32));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R32G32B32",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_R32G32B32));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R32G32B32A32",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_R32G32B32A32));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R16",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_R16));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R16G16B16",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_R16G16B16));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R16G16B16A16",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_UNCOMPRESSED_R16G16B16A16));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_DXT1_RGB",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_COMPRESSED_DXT1_RGB));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_DXT1_RGBA",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_COMPRESSED_DXT1_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_DXT3_RGBA",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_COMPRESSED_DXT3_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_DXT5_RGBA",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_COMPRESSED_DXT5_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_ETC1_RGB",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_COMPRESSED_ETC1_RGB));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_ETC2_RGB",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_COMPRESSED_ETC2_RGB));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_PVRT_RGB",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_COMPRESSED_PVRT_RGB));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_PVRT_RGBA",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_COMPRESSED_PVRT_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA",JS_NewInt32(ctx,(int32_t)PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_POINT",JS_NewInt32(ctx,(int32_t)TEXTURE_FILTER_POINT));
		JS_SetModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_BILINEAR",JS_NewInt32(ctx,(int32_t)TEXTURE_FILTER_BILINEAR));
		JS_SetModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_TRILINEAR",JS_NewInt32(ctx,(int32_t)TEXTURE_FILTER_TRILINEAR));
		JS_SetModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_ANISOTROPIC_4X",JS_NewInt32(ctx,(int32_t)TEXTURE_FILTER_ANISOTROPIC_4X));
		JS_SetModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_ANISOTROPIC_8X",JS_NewInt32(ctx,(int32_t)TEXTURE_FILTER_ANISOTROPIC_8X));
		JS_SetModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_ANISOTROPIC_16X",JS_NewInt32(ctx,(int32_t)TEXTURE_FILTER_ANISOTROPIC_16X));
		JS_SetModuleExport(ctx,m,(const char  *)"TEXTURE_WRAP_REPEAT",JS_NewInt32(ctx,(int32_t)TEXTURE_WRAP_REPEAT));
		JS_SetModuleExport(ctx,m,(const char  *)"TEXTURE_WRAP_CLAMP",JS_NewInt32(ctx,(int32_t)TEXTURE_WRAP_CLAMP));
		JS_SetModuleExport(ctx,m,(const char  *)"TEXTURE_WRAP_MIRROR_REPEAT",JS_NewInt32(ctx,(int32_t)TEXTURE_WRAP_MIRROR_REPEAT));
		JS_SetModuleExport(ctx,m,(const char  *)"TEXTURE_WRAP_MIRROR_CLAMP",JS_NewInt32(ctx,(int32_t)TEXTURE_WRAP_MIRROR_CLAMP));
		JS_SetModuleExport(ctx,m,(const char  *)"CUBEMAP_LAYOUT_AUTO_DETECT",JS_NewInt32(ctx,(int32_t)CUBEMAP_LAYOUT_AUTO_DETECT));
		JS_SetModuleExport(ctx,m,(const char  *)"CUBEMAP_LAYOUT_LINE_VERTICAL",JS_NewInt32(ctx,(int32_t)CUBEMAP_LAYOUT_LINE_VERTICAL));
		JS_SetModuleExport(ctx,m,(const char  *)"CUBEMAP_LAYOUT_LINE_HORIZONTAL",JS_NewInt32(ctx,(int32_t)CUBEMAP_LAYOUT_LINE_HORIZONTAL));
		JS_SetModuleExport(ctx,m,(const char  *)"CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR",JS_NewInt32(ctx,(int32_t)CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR));
		JS_SetModuleExport(ctx,m,(const char  *)"CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE",JS_NewInt32(ctx,(int32_t)CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE));
		JS_SetModuleExport(ctx,m,(const char  *)"FONT_DEFAULT",JS_NewInt32(ctx,(int32_t)FONT_DEFAULT));
		JS_SetModuleExport(ctx,m,(const char  *)"FONT_BITMAP",JS_NewInt32(ctx,(int32_t)FONT_BITMAP));
		JS_SetModuleExport(ctx,m,(const char  *)"FONT_SDF",JS_NewInt32(ctx,(int32_t)FONT_SDF));
		JS_SetModuleExport(ctx,m,(const char  *)"BLEND_ALPHA",JS_NewInt32(ctx,(int32_t)BLEND_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"BLEND_ADDITIVE",JS_NewInt32(ctx,(int32_t)BLEND_ADDITIVE));
		JS_SetModuleExport(ctx,m,(const char  *)"BLEND_MULTIPLIED",JS_NewInt32(ctx,(int32_t)BLEND_MULTIPLIED));
		JS_SetModuleExport(ctx,m,(const char  *)"BLEND_ADD_COLORS",JS_NewInt32(ctx,(int32_t)BLEND_ADD_COLORS));
		JS_SetModuleExport(ctx,m,(const char  *)"BLEND_SUBTRACT_COLORS",JS_NewInt32(ctx,(int32_t)BLEND_SUBTRACT_COLORS));
		JS_SetModuleExport(ctx,m,(const char  *)"BLEND_ALPHA_PREMULTIPLY",JS_NewInt32(ctx,(int32_t)BLEND_ALPHA_PREMULTIPLY));
		JS_SetModuleExport(ctx,m,(const char  *)"BLEND_CUSTOM",JS_NewInt32(ctx,(int32_t)BLEND_CUSTOM));
		JS_SetModuleExport(ctx,m,(const char  *)"BLEND_CUSTOM_SEPARATE",JS_NewInt32(ctx,(int32_t)BLEND_CUSTOM_SEPARATE));
		JS_SetModuleExport(ctx,m,(const char  *)"GESTURE_NONE",JS_NewInt32(ctx,(int32_t)GESTURE_NONE));
		JS_SetModuleExport(ctx,m,(const char  *)"GESTURE_TAP",JS_NewInt32(ctx,(int32_t)GESTURE_TAP));
		JS_SetModuleExport(ctx,m,(const char  *)"GESTURE_DOUBLETAP",JS_NewInt32(ctx,(int32_t)GESTURE_DOUBLETAP));
		JS_SetModuleExport(ctx,m,(const char  *)"GESTURE_HOLD",JS_NewInt32(ctx,(int32_t)GESTURE_HOLD));
		JS_SetModuleExport(ctx,m,(const char  *)"GESTURE_DRAG",JS_NewInt32(ctx,(int32_t)GESTURE_DRAG));
		JS_SetModuleExport(ctx,m,(const char  *)"GESTURE_SWIPE_RIGHT",JS_NewInt32(ctx,(int32_t)GESTURE_SWIPE_RIGHT));
		JS_SetModuleExport(ctx,m,(const char  *)"GESTURE_SWIPE_LEFT",JS_NewInt32(ctx,(int32_t)GESTURE_SWIPE_LEFT));
		JS_SetModuleExport(ctx,m,(const char  *)"GESTURE_SWIPE_UP",JS_NewInt32(ctx,(int32_t)GESTURE_SWIPE_UP));
		JS_SetModuleExport(ctx,m,(const char  *)"GESTURE_SWIPE_DOWN",JS_NewInt32(ctx,(int32_t)GESTURE_SWIPE_DOWN));
		JS_SetModuleExport(ctx,m,(const char  *)"GESTURE_PINCH_IN",JS_NewInt32(ctx,(int32_t)GESTURE_PINCH_IN));
		JS_SetModuleExport(ctx,m,(const char  *)"GESTURE_PINCH_OUT",JS_NewInt32(ctx,(int32_t)GESTURE_PINCH_OUT));
		JS_SetModuleExport(ctx,m,(const char  *)"CAMERA_CUSTOM",JS_NewInt32(ctx,(int32_t)CAMERA_CUSTOM));
		JS_SetModuleExport(ctx,m,(const char  *)"CAMERA_FREE",JS_NewInt32(ctx,(int32_t)CAMERA_FREE));
		JS_SetModuleExport(ctx,m,(const char  *)"CAMERA_ORBITAL",JS_NewInt32(ctx,(int32_t)CAMERA_ORBITAL));
		JS_SetModuleExport(ctx,m,(const char  *)"CAMERA_FIRST_PERSON",JS_NewInt32(ctx,(int32_t)CAMERA_FIRST_PERSON));
		JS_SetModuleExport(ctx,m,(const char  *)"CAMERA_THIRD_PERSON",JS_NewInt32(ctx,(int32_t)CAMERA_THIRD_PERSON));
		JS_SetModuleExport(ctx,m,(const char  *)"CAMERA_PERSPECTIVE",JS_NewInt32(ctx,(int32_t)CAMERA_PERSPECTIVE));
		JS_SetModuleExport(ctx,m,(const char  *)"CAMERA_ORTHOGRAPHIC",JS_NewInt32(ctx,(int32_t)CAMERA_ORTHOGRAPHIC));
		JS_SetModuleExport(ctx,m,(const char  *)"NPATCH_NINE_PATCH",JS_NewInt32(ctx,(int32_t)NPATCH_NINE_PATCH));
		JS_SetModuleExport(ctx,m,(const char  *)"NPATCH_THREE_PATCH_VERTICAL",JS_NewInt32(ctx,(int32_t)NPATCH_THREE_PATCH_VERTICAL));
		JS_SetModuleExport(ctx,m,(const char  *)"NPATCH_THREE_PATCH_HORIZONTAL",JS_NewInt32(ctx,(int32_t)NPATCH_THREE_PATCH_HORIZONTAL));
		JS_SetModuleExport(ctx,m,(const char  *)"RAYLIB_VERSION_MAJOR",JS_NewInt32(ctx,(int32_t)RAYLIB_VERSION_MAJOR));
		JS_SetModuleExport(ctx,m,(const char  *)"RAYLIB_VERSION_MINOR",JS_NewInt32(ctx,(int32_t)RAYLIB_VERSION_MINOR));
		JS_SetModuleExport(ctx,m,(const char  *)"RAYLIB_VERSION_PATCH",JS_NewInt32(ctx,(int32_t)RAYLIB_VERSION_PATCH));
		JS_SetModuleExport(ctx,m,(const char  *)"PI",JS_NewFloat64(ctx,(double)PI));
		JS_SetModuleExport(ctx,m,(const char  *)"DEG2RAD",JS_NewFloat64(ctx,(double)DEG2RAD));
		JS_SetModuleExport(ctx,m,(const char  *)"RAD2DEG",JS_NewFloat64(ctx,(double)RAD2DEG));
		Color LIGHTGRAY_struct={
			200,
			200,
			200,
			255
		};
		opaqueShadow * ptr_LIGHTGRAY_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_LIGHTGRAY_js=((Color *)(ptr_LIGHTGRAY_js+1));
		ptr2_LIGHTGRAY_js[0]=LIGHTGRAY_struct;
		JSValue LIGHTGRAY_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(LIGHTGRAY_js,(void  *)ptr_LIGHTGRAY_js);
		JS_SetModuleExport(ctx,m,(const char  *)"LIGHTGRAY",LIGHTGRAY_js);
		Color GRAY_struct={
			130,
			130,
			130,
			255
		};
		opaqueShadow * ptr_GRAY_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_GRAY_js=((Color *)(ptr_GRAY_js+1));
		ptr2_GRAY_js[0]=GRAY_struct;
		JSValue GRAY_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(GRAY_js,(void  *)ptr_GRAY_js);
		JS_SetModuleExport(ctx,m,(const char  *)"GRAY",GRAY_js);
		Color DARKGRAY_struct={
			80,
			80,
			80,
			255
		};
		opaqueShadow * ptr_DARKGRAY_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_DARKGRAY_js=((Color *)(ptr_DARKGRAY_js+1));
		ptr2_DARKGRAY_js[0]=DARKGRAY_struct;
		JSValue DARKGRAY_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(DARKGRAY_js,(void  *)ptr_DARKGRAY_js);
		JS_SetModuleExport(ctx,m,(const char  *)"DARKGRAY",DARKGRAY_js);
		Color YELLOW_struct={
			253,
			249,
			0,
			255
		};
		opaqueShadow * ptr_YELLOW_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_YELLOW_js=((Color *)(ptr_YELLOW_js+1));
		ptr2_YELLOW_js[0]=YELLOW_struct;
		JSValue YELLOW_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(YELLOW_js,(void  *)ptr_YELLOW_js);
		JS_SetModuleExport(ctx,m,(const char  *)"YELLOW",YELLOW_js);
		Color GOLD_struct={
			255,
			203,
			0,
			255
		};
		opaqueShadow * ptr_GOLD_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_GOLD_js=((Color *)(ptr_GOLD_js+1));
		ptr2_GOLD_js[0]=GOLD_struct;
		JSValue GOLD_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(GOLD_js,(void  *)ptr_GOLD_js);
		JS_SetModuleExport(ctx,m,(const char  *)"GOLD",GOLD_js);
		Color ORANGE_struct={
			255,
			161,
			0,
			255
		};
		opaqueShadow * ptr_ORANGE_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_ORANGE_js=((Color *)(ptr_ORANGE_js+1));
		ptr2_ORANGE_js[0]=ORANGE_struct;
		JSValue ORANGE_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ORANGE_js,(void  *)ptr_ORANGE_js);
		JS_SetModuleExport(ctx,m,(const char  *)"ORANGE",ORANGE_js);
		Color PINK_struct={
			255,
			109,
			194,
			255
		};
		opaqueShadow * ptr_PINK_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_PINK_js=((Color *)(ptr_PINK_js+1));
		ptr2_PINK_js[0]=PINK_struct;
		JSValue PINK_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(PINK_js,(void  *)ptr_PINK_js);
		JS_SetModuleExport(ctx,m,(const char  *)"PINK",PINK_js);
		Color RED_struct={
			230,
			41,
			55,
			255
		};
		opaqueShadow * ptr_RED_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_RED_js=((Color *)(ptr_RED_js+1));
		ptr2_RED_js[0]=RED_struct;
		JSValue RED_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(RED_js,(void  *)ptr_RED_js);
		JS_SetModuleExport(ctx,m,(const char  *)"RED",RED_js);
		Color MAROON_struct={
			190,
			33,
			55,
			255
		};
		opaqueShadow * ptr_MAROON_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_MAROON_js=((Color *)(ptr_MAROON_js+1));
		ptr2_MAROON_js[0]=MAROON_struct;
		JSValue MAROON_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(MAROON_js,(void  *)ptr_MAROON_js);
		JS_SetModuleExport(ctx,m,(const char  *)"MAROON",MAROON_js);
		Color GREEN_struct={
			0,
			228,
			48,
			255
		};
		opaqueShadow * ptr_GREEN_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_GREEN_js=((Color *)(ptr_GREEN_js+1));
		ptr2_GREEN_js[0]=GREEN_struct;
		JSValue GREEN_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(GREEN_js,(void  *)ptr_GREEN_js);
		JS_SetModuleExport(ctx,m,(const char  *)"GREEN",GREEN_js);
		Color LIME_struct={
			0,
			158,
			47,
			255
		};
		opaqueShadow * ptr_LIME_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_LIME_js=((Color *)(ptr_LIME_js+1));
		ptr2_LIME_js[0]=LIME_struct;
		JSValue LIME_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(LIME_js,(void  *)ptr_LIME_js);
		JS_SetModuleExport(ctx,m,(const char  *)"LIME",LIME_js);
		Color DARKGREEN_struct={
			0,
			117,
			44,
			255
		};
		opaqueShadow * ptr_DARKGREEN_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_DARKGREEN_js=((Color *)(ptr_DARKGREEN_js+1));
		ptr2_DARKGREEN_js[0]=DARKGREEN_struct;
		JSValue DARKGREEN_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(DARKGREEN_js,(void  *)ptr_DARKGREEN_js);
		JS_SetModuleExport(ctx,m,(const char  *)"DARKGREEN",DARKGREEN_js);
		Color SKYBLUE_struct={
			102,
			191,
			255,
			255
		};
		opaqueShadow * ptr_SKYBLUE_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_SKYBLUE_js=((Color *)(ptr_SKYBLUE_js+1));
		ptr2_SKYBLUE_js[0]=SKYBLUE_struct;
		JSValue SKYBLUE_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(SKYBLUE_js,(void  *)ptr_SKYBLUE_js);
		JS_SetModuleExport(ctx,m,(const char  *)"SKYBLUE",SKYBLUE_js);
		Color BLUE_struct={
			0,
			121,
			241,
			255
		};
		opaqueShadow * ptr_BLUE_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_BLUE_js=((Color *)(ptr_BLUE_js+1));
		ptr2_BLUE_js[0]=BLUE_struct;
		JSValue BLUE_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(BLUE_js,(void  *)ptr_BLUE_js);
		JS_SetModuleExport(ctx,m,(const char  *)"BLUE",BLUE_js);
		Color DARKBLUE_struct={
			0,
			82,
			172,
			255
		};
		opaqueShadow * ptr_DARKBLUE_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_DARKBLUE_js=((Color *)(ptr_DARKBLUE_js+1));
		ptr2_DARKBLUE_js[0]=DARKBLUE_struct;
		JSValue DARKBLUE_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(DARKBLUE_js,(void  *)ptr_DARKBLUE_js);
		JS_SetModuleExport(ctx,m,(const char  *)"DARKBLUE",DARKBLUE_js);
		Color PURPLE_struct={
			200,
			122,
			255,
			255
		};
		opaqueShadow * ptr_PURPLE_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_PURPLE_js=((Color *)(ptr_PURPLE_js+1));
		ptr2_PURPLE_js[0]=PURPLE_struct;
		JSValue PURPLE_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(PURPLE_js,(void  *)ptr_PURPLE_js);
		JS_SetModuleExport(ctx,m,(const char  *)"PURPLE",PURPLE_js);
		Color VIOLET_struct={
			135,
			60,
			190,
			255
		};
		opaqueShadow * ptr_VIOLET_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_VIOLET_js=((Color *)(ptr_VIOLET_js+1));
		ptr2_VIOLET_js[0]=VIOLET_struct;
		JSValue VIOLET_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(VIOLET_js,(void  *)ptr_VIOLET_js);
		JS_SetModuleExport(ctx,m,(const char  *)"VIOLET",VIOLET_js);
		Color DARKPURPLE_struct={
			112,
			31,
			126,
			255
		};
		opaqueShadow * ptr_DARKPURPLE_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_DARKPURPLE_js=((Color *)(ptr_DARKPURPLE_js+1));
		ptr2_DARKPURPLE_js[0]=DARKPURPLE_struct;
		JSValue DARKPURPLE_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(DARKPURPLE_js,(void  *)ptr_DARKPURPLE_js);
		JS_SetModuleExport(ctx,m,(const char  *)"DARKPURPLE",DARKPURPLE_js);
		Color BEIGE_struct={
			211,
			176,
			131,
			255
		};
		opaqueShadow * ptr_BEIGE_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_BEIGE_js=((Color *)(ptr_BEIGE_js+1));
		ptr2_BEIGE_js[0]=BEIGE_struct;
		JSValue BEIGE_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(BEIGE_js,(void  *)ptr_BEIGE_js);
		JS_SetModuleExport(ctx,m,(const char  *)"BEIGE",BEIGE_js);
		Color BROWN_struct={
			127,
			106,
			79,
			255
		};
		opaqueShadow * ptr_BROWN_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_BROWN_js=((Color *)(ptr_BROWN_js+1));
		ptr2_BROWN_js[0]=BROWN_struct;
		JSValue BROWN_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(BROWN_js,(void  *)ptr_BROWN_js);
		JS_SetModuleExport(ctx,m,(const char  *)"BROWN",BROWN_js);
		Color DARKBROWN_struct={
			76,
			63,
			47,
			255
		};
		opaqueShadow * ptr_DARKBROWN_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_DARKBROWN_js=((Color *)(ptr_DARKBROWN_js+1));
		ptr2_DARKBROWN_js[0]=DARKBROWN_struct;
		JSValue DARKBROWN_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(DARKBROWN_js,(void  *)ptr_DARKBROWN_js);
		JS_SetModuleExport(ctx,m,(const char  *)"DARKBROWN",DARKBROWN_js);
		Color WHITE_struct={
			255,
			255,
			255,
			255
		};
		opaqueShadow * ptr_WHITE_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_WHITE_js=((Color *)(ptr_WHITE_js+1));
		ptr2_WHITE_js[0]=WHITE_struct;
		JSValue WHITE_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(WHITE_js,(void  *)ptr_WHITE_js);
		JS_SetModuleExport(ctx,m,(const char  *)"WHITE",WHITE_js);
		Color BLACK_struct={
			0,
			0,
			0,
			255
		};
		opaqueShadow * ptr_BLACK_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_BLACK_js=((Color *)(ptr_BLACK_js+1));
		ptr2_BLACK_js[0]=BLACK_struct;
		JSValue BLACK_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(BLACK_js,(void  *)ptr_BLACK_js);
		JS_SetModuleExport(ctx,m,(const char  *)"BLACK",BLACK_js);
		Color BLANK_struct={
			0,
			0,
			0,
			0
		};
		opaqueShadow * ptr_BLANK_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_BLANK_js=((Color *)(ptr_BLANK_js+1));
		ptr2_BLANK_js[0]=BLANK_struct;
		JSValue BLANK_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(BLANK_js,(void  *)ptr_BLANK_js);
		JS_SetModuleExport(ctx,m,(const char  *)"BLANK",BLANK_js);
		Color MAGENTA_struct={
			255,
			0,
			255,
			255
		};
		opaqueShadow * ptr_MAGENTA_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_MAGENTA_js=((Color *)(ptr_MAGENTA_js+1));
		ptr2_MAGENTA_js[0]=MAGENTA_struct;
		JSValue MAGENTA_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(MAGENTA_js,(void  *)ptr_MAGENTA_js);
		JS_SetModuleExport(ctx,m,(const char  *)"MAGENTA",MAGENTA_js);
		Color RAYWHITE_struct={
			245,
			245,
			245,
			255
		};
		opaqueShadow * ptr_RAYWHITE_js=create_shadow_with_data(sizeof(Color));
		Color * ptr2_RAYWHITE_js=((Color *)(ptr_RAYWHITE_js+1));
		ptr2_RAYWHITE_js[0]=RAYWHITE_struct;
		JSValue RAYWHITE_js=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(RAYWHITE_js,(void  *)ptr_RAYWHITE_js);
		JS_SetModuleExport(ctx,m,(const char  *)"RAYWHITE",RAYWHITE_js);
		return 0;
	}
	
	JSModuleDef * js_init_module_raylib(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_raylib_init);
		if(!m)return NULL;
		size_t listcount=countof(jsraylib_funcs);
		JS_AddModuleExportList(ctx,m,jsraylib_funcs,(int)listcount);
		JS_AddModuleExport(ctx,m,(const char  *)"Vector2");
		JS_AddModuleExport(ctx,m,(const char  *)"Vector3");
		JS_AddModuleExport(ctx,m,(const char  *)"Vector4");
		JS_AddModuleExport(ctx,m,(const char  *)"Matrix");
		JS_AddModuleExport(ctx,m,(const char  *)"Color");
		JS_AddModuleExport(ctx,m,(const char  *)"Rectangle");
		JS_AddModuleExport(ctx,m,(const char  *)"Image");
		JS_AddModuleExport(ctx,m,(const char  *)"Texture");
		JS_AddModuleExport(ctx,m,(const char  *)"RenderTexture");
		JS_AddModuleExport(ctx,m,(const char  *)"NPatchInfo");
		JS_AddModuleExport(ctx,m,(const char  *)"GlyphInfo");
		JS_AddModuleExport(ctx,m,(const char  *)"Font");
		JS_AddModuleExport(ctx,m,(const char  *)"Camera3D");
		JS_AddModuleExport(ctx,m,(const char  *)"Camera2D");
		JS_AddModuleExport(ctx,m,(const char  *)"Mesh");
		JS_AddModuleExport(ctx,m,(const char  *)"Shader");
		JS_AddModuleExport(ctx,m,(const char  *)"MaterialMap");
		JS_AddModuleExport(ctx,m,(const char  *)"Material");
		JS_AddModuleExport(ctx,m,(const char  *)"Transform");
		JS_AddModuleExport(ctx,m,(const char  *)"BoneInfo");
		JS_AddModuleExport(ctx,m,(const char  *)"Model");
		JS_AddModuleExport(ctx,m,(const char  *)"ModelAnimation");
		JS_AddModuleExport(ctx,m,(const char  *)"Ray");
		JS_AddModuleExport(ctx,m,(const char  *)"RayCollision");
		JS_AddModuleExport(ctx,m,(const char  *)"BoundingBox");
		JS_AddModuleExport(ctx,m,(const char  *)"Wave");
		JS_AddModuleExport(ctx,m,(const char  *)"AudioStream");
		JS_AddModuleExport(ctx,m,(const char  *)"Sound");
		JS_AddModuleExport(ctx,m,(const char  *)"Music");
		JS_AddModuleExport(ctx,m,(const char  *)"VrDeviceInfo");
		JS_AddModuleExport(ctx,m,(const char  *)"VrStereoConfig");
		JS_AddModuleExport(ctx,m,(const char  *)"FilePathList");
		JS_AddModuleExport(ctx,m,(const char  *)"AutomationEvent");
		JS_AddModuleExport(ctx,m,(const char  *)"AutomationEventList");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_VSYNC_HINT");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_FULLSCREEN_MODE");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_RESIZABLE");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_UNDECORATED");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_HIDDEN");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_MINIMIZED");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_MAXIMIZED");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_UNFOCUSED");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_TOPMOST");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_ALWAYS_RUN");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_TRANSPARENT");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_HIGHDPI");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_WINDOW_MOUSE_PASSTHROUGH");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_BORDERLESS_WINDOWED_MODE");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_MSAA_4X_HINT");
		JS_AddModuleExport(ctx,m,(const char  *)"FLAG_INTERLACED_HINT");
		JS_AddModuleExport(ctx,m,(const char  *)"LOG_ALL");
		JS_AddModuleExport(ctx,m,(const char  *)"LOG_TRACE");
		JS_AddModuleExport(ctx,m,(const char  *)"LOG_DEBUG");
		JS_AddModuleExport(ctx,m,(const char  *)"LOG_INFO");
		JS_AddModuleExport(ctx,m,(const char  *)"LOG_WARNING");
		JS_AddModuleExport(ctx,m,(const char  *)"LOG_ERROR");
		JS_AddModuleExport(ctx,m,(const char  *)"LOG_FATAL");
		JS_AddModuleExport(ctx,m,(const char  *)"LOG_NONE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_NULL");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_APOSTROPHE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_COMMA");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_MINUS");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_PERIOD");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_SLASH");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_ZERO");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_ONE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_TWO");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_THREE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_FOUR");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_FIVE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_SIX");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_SEVEN");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_EIGHT");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_NINE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_SEMICOLON");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_EQUAL");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_A");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_B");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_C");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_D");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_E");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_G");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_H");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_I");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_J");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_K");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_L");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_M");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_N");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_O");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_P");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_Q");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_R");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_S");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_T");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_U");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_V");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_W");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_X");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_Y");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_Z");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_LEFT_BRACKET");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_BACKSLASH");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_RIGHT_BRACKET");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_GRAVE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_SPACE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_ESCAPE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_ENTER");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_TAB");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_BACKSPACE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_INSERT");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_DELETE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_RIGHT");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_LEFT");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_DOWN");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_UP");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_PAGE_UP");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_PAGE_DOWN");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_HOME");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_END");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_CAPS_LOCK");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_SCROLL_LOCK");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_NUM_LOCK");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_PRINT_SCREEN");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_PAUSE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F1");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F2");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F3");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F4");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F5");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F6");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F7");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F8");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F9");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F10");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F11");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_F12");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_LEFT_SHIFT");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_LEFT_CONTROL");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_LEFT_ALT");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_LEFT_SUPER");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_RIGHT_SHIFT");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_RIGHT_CONTROL");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_RIGHT_ALT");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_RIGHT_SUPER");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KB_MENU");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_0");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_1");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_2");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_3");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_4");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_5");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_6");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_7");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_8");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_9");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_DECIMAL");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_DIVIDE");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_MULTIPLY");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_SUBTRACT");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_ADD");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_ENTER");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_KP_EQUAL");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_BACK");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_MENU");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_VOLUME_UP");
		JS_AddModuleExport(ctx,m,(const char  *)"KEY_VOLUME_DOWN");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_LEFT");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_RIGHT");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_MIDDLE");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_SIDE");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_EXTRA");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_FORWARD");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_BUTTON_BACK");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_LEFT_BUTTON");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_RIGHT_BUTTON");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_MIDDLE_BUTTON");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_DEFAULT");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_ARROW");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_IBEAM");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_CROSSHAIR");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_POINTING_HAND");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_RESIZE_EW");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_RESIZE_NS");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_RESIZE_NWSE");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_RESIZE_NESW");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_RESIZE_ALL");
		JS_AddModuleExport(ctx,m,(const char  *)"MOUSE_CURSOR_NOT_ALLOWED");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_UNKNOWN");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_FACE_UP");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_FACE_RIGHT");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_FACE_DOWN");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_FACE_LEFT");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_FACE_UP");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_FACE_RIGHT");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_FACE_DOWN");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_FACE_LEFT");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_TRIGGER_1");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_TRIGGER_2");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_TRIGGER_1");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_TRIGGER_2");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_MIDDLE_LEFT");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_MIDDLE");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_MIDDLE_RIGHT");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_LEFT_THUMB");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_BUTTON_RIGHT_THUMB");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_LEFT_X");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_LEFT_Y");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_RIGHT_X");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_RIGHT_Y");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_LEFT_TRIGGER");
		JS_AddModuleExport(ctx,m,(const char  *)"GAMEPAD_AXIS_RIGHT_TRIGGER");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_ALBEDO");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_METALNESS");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_NORMAL");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_ROUGHNESS");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_OCCLUSION");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_EMISSION");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_HEIGHT");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_CUBEMAP");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_IRRADIANCE");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_PREFILTER");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_BRDF");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_DIFFUSE");
		JS_AddModuleExport(ctx,m,(const char  *)"MATERIAL_MAP_SPECULAR");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_POSITION");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_TEXCOORD01");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_TEXCOORD02");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_NORMAL");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_TANGENT");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_COLOR");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MATRIX_MVP");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MATRIX_VIEW");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MATRIX_PROJECTION");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MATRIX_MODEL");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MATRIX_NORMAL");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_VECTOR_VIEW");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_COLOR_DIFFUSE");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_COLOR_SPECULAR");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_COLOR_AMBIENT");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_ALBEDO");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_METALNESS");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_NORMAL");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_ROUGHNESS");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_OCCLUSION");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_EMISSION");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_HEIGHT");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_CUBEMAP");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_IRRADIANCE");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_PREFILTER");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_BRDF");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_BONEIDS");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_BONEWEIGHTS");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_BONE_MATRICES");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_VERTEX_INSTANCE_TX");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_DIFFUSE");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_LOC_MAP_SPECULAR");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_FLOAT");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_VEC2");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_VEC3");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_VEC4");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_INT");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_IVEC2");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_IVEC3");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_IVEC4");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_UINT");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_UIVEC2");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_UIVEC3");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_UIVEC4");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_UNIFORM_SAMPLER2D");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_ATTRIB_FLOAT");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_ATTRIB_VEC2");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_ATTRIB_VEC3");
		JS_AddModuleExport(ctx,m,(const char  *)"SHADER_ATTRIB_VEC4");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_GRAYSCALE");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R5G6B5");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R8G8B8");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R5G5B5A1");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R4G4B4A4");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R8G8B8A8");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R32");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R32G32B32");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R32G32B32A32");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R16");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R16G16B16");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_UNCOMPRESSED_R16G16B16A16");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_DXT1_RGB");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_DXT1_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_DXT3_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_DXT5_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_ETC1_RGB");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_ETC2_RGB");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_PVRT_RGB");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_PVRT_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_POINT");
		JS_AddModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_BILINEAR");
		JS_AddModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_TRILINEAR");
		JS_AddModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_ANISOTROPIC_4X");
		JS_AddModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_ANISOTROPIC_8X");
		JS_AddModuleExport(ctx,m,(const char  *)"TEXTURE_FILTER_ANISOTROPIC_16X");
		JS_AddModuleExport(ctx,m,(const char  *)"TEXTURE_WRAP_REPEAT");
		JS_AddModuleExport(ctx,m,(const char  *)"TEXTURE_WRAP_CLAMP");
		JS_AddModuleExport(ctx,m,(const char  *)"TEXTURE_WRAP_MIRROR_REPEAT");
		JS_AddModuleExport(ctx,m,(const char  *)"TEXTURE_WRAP_MIRROR_CLAMP");
		JS_AddModuleExport(ctx,m,(const char  *)"CUBEMAP_LAYOUT_AUTO_DETECT");
		JS_AddModuleExport(ctx,m,(const char  *)"CUBEMAP_LAYOUT_LINE_VERTICAL");
		JS_AddModuleExport(ctx,m,(const char  *)"CUBEMAP_LAYOUT_LINE_HORIZONTAL");
		JS_AddModuleExport(ctx,m,(const char  *)"CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR");
		JS_AddModuleExport(ctx,m,(const char  *)"CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE");
		JS_AddModuleExport(ctx,m,(const char  *)"FONT_DEFAULT");
		JS_AddModuleExport(ctx,m,(const char  *)"FONT_BITMAP");
		JS_AddModuleExport(ctx,m,(const char  *)"FONT_SDF");
		JS_AddModuleExport(ctx,m,(const char  *)"BLEND_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"BLEND_ADDITIVE");
		JS_AddModuleExport(ctx,m,(const char  *)"BLEND_MULTIPLIED");
		JS_AddModuleExport(ctx,m,(const char  *)"BLEND_ADD_COLORS");
		JS_AddModuleExport(ctx,m,(const char  *)"BLEND_SUBTRACT_COLORS");
		JS_AddModuleExport(ctx,m,(const char  *)"BLEND_ALPHA_PREMULTIPLY");
		JS_AddModuleExport(ctx,m,(const char  *)"BLEND_CUSTOM");
		JS_AddModuleExport(ctx,m,(const char  *)"BLEND_CUSTOM_SEPARATE");
		JS_AddModuleExport(ctx,m,(const char  *)"GESTURE_NONE");
		JS_AddModuleExport(ctx,m,(const char  *)"GESTURE_TAP");
		JS_AddModuleExport(ctx,m,(const char  *)"GESTURE_DOUBLETAP");
		JS_AddModuleExport(ctx,m,(const char  *)"GESTURE_HOLD");
		JS_AddModuleExport(ctx,m,(const char  *)"GESTURE_DRAG");
		JS_AddModuleExport(ctx,m,(const char  *)"GESTURE_SWIPE_RIGHT");
		JS_AddModuleExport(ctx,m,(const char  *)"GESTURE_SWIPE_LEFT");
		JS_AddModuleExport(ctx,m,(const char  *)"GESTURE_SWIPE_UP");
		JS_AddModuleExport(ctx,m,(const char  *)"GESTURE_SWIPE_DOWN");
		JS_AddModuleExport(ctx,m,(const char  *)"GESTURE_PINCH_IN");
		JS_AddModuleExport(ctx,m,(const char  *)"GESTURE_PINCH_OUT");
		JS_AddModuleExport(ctx,m,(const char  *)"CAMERA_CUSTOM");
		JS_AddModuleExport(ctx,m,(const char  *)"CAMERA_FREE");
		JS_AddModuleExport(ctx,m,(const char  *)"CAMERA_ORBITAL");
		JS_AddModuleExport(ctx,m,(const char  *)"CAMERA_FIRST_PERSON");
		JS_AddModuleExport(ctx,m,(const char  *)"CAMERA_THIRD_PERSON");
		JS_AddModuleExport(ctx,m,(const char  *)"CAMERA_PERSPECTIVE");
		JS_AddModuleExport(ctx,m,(const char  *)"CAMERA_ORTHOGRAPHIC");
		JS_AddModuleExport(ctx,m,(const char  *)"NPATCH_NINE_PATCH");
		JS_AddModuleExport(ctx,m,(const char  *)"NPATCH_THREE_PATCH_VERTICAL");
		JS_AddModuleExport(ctx,m,(const char  *)"NPATCH_THREE_PATCH_HORIZONTAL");
		JS_AddModuleExport(ctx,m,(const char  *)"RAYLIB_VERSION_MAJOR");
		JS_AddModuleExport(ctx,m,(const char  *)"RAYLIB_VERSION_MINOR");
		JS_AddModuleExport(ctx,m,(const char  *)"RAYLIB_VERSION_PATCH");
		JS_AddModuleExport(ctx,m,(const char  *)"PI");
		JS_AddModuleExport(ctx,m,(const char  *)"DEG2RAD");
		JS_AddModuleExport(ctx,m,(const char  *)"RAD2DEG");
		JS_AddModuleExport(ctx,m,(const char  *)"LIGHTGRAY");
		JS_AddModuleExport(ctx,m,(const char  *)"GRAY");
		JS_AddModuleExport(ctx,m,(const char  *)"DARKGRAY");
		JS_AddModuleExport(ctx,m,(const char  *)"YELLOW");
		JS_AddModuleExport(ctx,m,(const char  *)"GOLD");
		JS_AddModuleExport(ctx,m,(const char  *)"ORANGE");
		JS_AddModuleExport(ctx,m,(const char  *)"PINK");
		JS_AddModuleExport(ctx,m,(const char  *)"RED");
		JS_AddModuleExport(ctx,m,(const char  *)"MAROON");
		JS_AddModuleExport(ctx,m,(const char  *)"GREEN");
		JS_AddModuleExport(ctx,m,(const char  *)"LIME");
		JS_AddModuleExport(ctx,m,(const char  *)"DARKGREEN");
		JS_AddModuleExport(ctx,m,(const char  *)"SKYBLUE");
		JS_AddModuleExport(ctx,m,(const char  *)"BLUE");
		JS_AddModuleExport(ctx,m,(const char  *)"DARKBLUE");
		JS_AddModuleExport(ctx,m,(const char  *)"PURPLE");
		JS_AddModuleExport(ctx,m,(const char  *)"VIOLET");
		JS_AddModuleExport(ctx,m,(const char  *)"DARKPURPLE");
		JS_AddModuleExport(ctx,m,(const char  *)"BEIGE");
		JS_AddModuleExport(ctx,m,(const char  *)"BROWN");
		JS_AddModuleExport(ctx,m,(const char  *)"DARKBROWN");
		JS_AddModuleExport(ctx,m,(const char  *)"WHITE");
		JS_AddModuleExport(ctx,m,(const char  *)"BLACK");
		JS_AddModuleExport(ctx,m,(const char  *)"BLANK");
		JS_AddModuleExport(ctx,m,(const char  *)"MAGENTA");
		JS_AddModuleExport(ctx,m,(const char  *)"RAYWHITE");
		return m;
	}

#endif //JS_raylib_GUARD