#ifndef JS_raygui_GUARD
	#define JS_raygui_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <raylib.h>
#define RAYGUI_IMPLEMENTATION ;
	#include <raygui.h>
	
	static unsigned short js_getunsignedshort(JSContext * ctx,JSValue src,bool * error);
	
	static int js_getint(JSContext * ctx,JSValue src,bool * error);
	
	static float js_getfloat(JSContext * ctx,JSValue src,bool * error);
	
	static Font js_getFont(JSContext * ctx,JSValue src,bool * error);
	
	static char * js_getchar_arr(JSContext * ctx,JSValue src,bool * error);
	
	static bool js_getbool(JSContext * ctx,JSValue src,bool * error);
	
	static Color js_getColor(JSContext * ctx,JSValue src,bool * error);
	
	static Rectangle js_getRectangle(JSContext * ctx,JSValue src,bool * error);
	
	static char * * js_getchar_arr_arr(JSContext * ctx,JSValue src,bool * error);
	
	static int * js_getint_ptr(JSContext * ctx,JSValue src,bool * error);
	
	static Vector2 * js_getVector2_ptr(JSContext * ctx,JSValue src,bool * error);
	
	static Rectangle * js_getRectangle_ptr(JSContext * ctx,JSValue src,bool * error){
		Rectangle * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,AP_fn.opaque,(int)0,(bool)false);
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
					JS_ThrowTypeError(ctx,(const char *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Rectangle *)js_malloc(ctx,size_ret*sizeof(Rectangle));
				int i;
				for(i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==js_Rectangle_class_id){
						ret[i] =*(Rectangle *)JS_GetOpaque(src0,js_Rectangle_class_id);
					}else{
						JS_ThrowTypeError(ctx,(const char *)"src0 does not match type Rectangle *");
						error[0]=(bool)1;
						return NULL;
					}
				}
			}else if(JS_IsNumber(src0)){
				size_ret -=size_ret%4;
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Rectangle *)js_malloc(ctx,size_ret*sizeof(float));
				int i;
				for(i=0;i<size_ret;i++){
					float * tmp_obj=(float *)ret;
					int i0;
					for(i0=0;i0<4;i0++){
						src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
						JS_FreeValue(ctx,src0);
						if(JS_IsNumber(src0)){
							double double_tmp_objii0;
							JS_ToFloat64(ctx,&double_tmp_objii0,src0);
							tmp_obj[i+i0] =((float)double_tmp_objii0);
						}else{
							JS_ThrowTypeError(ctx,(const char *)"src0 does not match type Rectangle *");
							error[0]=(bool)1;
							return NULL;
						}
					}
					i +=3;
				}
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type Rectangle *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_Rectangle_class_id){
			if(JS_GetClassID(src)==js_Rectangle_class_id){
				ret =(Rectangle *)JS_GetOpaque(src,js_Rectangle_class_id);
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type Rectangle *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char *)"src does not match type Rectangle *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static bool * js_getbool_ptr(JSContext * ctx,JSValue src,bool * error){
		bool * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,AP_fn.opaque,(int)0,(bool)false);
		}
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret<1){
				JS_ThrowTypeError(ctx,(const char *)"src too short (1)");
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(bool *)js_malloc(ctx,sizeof(bool));
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_IsBool(src0)){
				int js_ret0=JS_ToBool(ctx,src0);
				ret[0] =(bool)js_ret0;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src0 does not match type bool *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_IsBool(src)){
			ret =(bool *)js_malloc(ctx,sizeof(bool));
			if(JS_IsBool(src)){
				int js_ret0=JS_ToBool(ctx,src);
				ret[0] =(bool)js_ret0;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type bool *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char *)"src does not match type bool *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static int * js_getint_arr(JSContext * ctx,JSValue src,bool * error);
	
	static float * js_getfloat_arr(JSContext * ctx,JSValue src,bool * error);
	
	static char * * js_getchar_arr_ptr(JSContext * ctx,JSValue src,bool * error){
		char * * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,AP_fn.opaque,(int)0,(bool)false);
		}
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_IsArrayBuffer(src0)){
				if(size_ret<1){
					JS_ThrowTypeError(ctx,(const char *)"src too short (1)");
					error[0]=(bool)1;
					return NULL;
				}
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char * *)js_malloc(ctx,sizeof(char *));
				src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)0);
				JS_FreeValue(ctx,src0);
				if(JS_IsArrayBuffer(src0)){
					int64_t size_ret0;
					ret[0] =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_ret0,src0);
				}else{
					JS_ThrowTypeError(ctx,(const char *)"src0 does not match type char * *");
					error[0]=(bool)1;
					return NULL;
				}
			}else if(JS_GetClassID(src0)==js_ArrayProxy_class_id){
				if(size_ret<1){
					JS_ThrowTypeError(ctx,(const char *)"src too short (1)");
					error[0]=(bool)1;
					return NULL;
				}
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char * *)js_malloc(ctx,sizeof(char *));
				src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)0);
				JS_FreeValue(ctx,src0);
				bool is_arrayProxy0=(bool)0;
				if(JS_GetClassID(src0)==js_ArrayProxy_class_id){
					is_arrayProxy0 =(bool)1;
					void * AP_opaque=JS_GetOpaque(src0,js_ArrayProxy_class_id);
					ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
					src0 =AP_fn.values(ctx,AP_fn.opaque,(int)0,(bool)false);
				}
				if(JS_IsArray(src0)){
					int64_t size_ret0;
					if(JS_GetLength(ctx,src0,&size_ret0)==-1){
						error[0]=(bool)1;
						return NULL;
					}
					if(size_ret0==0){
						JS_ThrowTypeError(ctx,(const char *)"Received empty array");
						error[0]=(bool)1;
						return NULL;
					}
					ret[0] =(char *)js_malloc(ctx,size_ret0*sizeof(char));
					int i;
					for(i=0;i<size_ret0;i++){
						JSValue src00=JS_GetPropertyUint32(ctx,src0,(uint32_t)i);
						JS_FreeValue(ctx,src00);
						if(JS_IsString(src00)){
							char * js_ret0i=(char *)JS_ToCString(ctx,src00);
							ret[0][i] =((char)js_ret0i[0]);
							JS_FreeCString(ctx,(const char *)js_ret0i);
						}else{
							JS_ThrowTypeError(ctx,(const char *)"src00 does not match type char * *");
							error[0]=(bool)1;
							return NULL;
						}
					}
				}else{
					JS_ThrowTypeError(ctx,(const char *)"src0 does not match type char * *");
					error[0]=(bool)1;
					return NULL;
				}
				if(is_arrayProxy0)JS_FreeValue(ctx,src0);
			}else if(JS_IsArray(src0)){
				if(size_ret<1){
					JS_ThrowTypeError(ctx,(const char *)"src too short (1)");
					error[0]=(bool)1;
					return NULL;
				}
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char * *)js_malloc(ctx,sizeof(char *));
				src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)0);
				JS_FreeValue(ctx,src0);
				if(JS_IsArray(src0)){
					int64_t size_ret0;
					if(JS_GetLength(ctx,src0,&size_ret0)==-1){
						error[0]=(bool)1;
						return NULL;
					}
					if(size_ret0==0){
						JS_ThrowTypeError(ctx,(const char *)"Received empty array");
						error[0]=(bool)1;
						return NULL;
					}
					ret[0] =(char *)js_malloc(ctx,size_ret0*sizeof(char));
					int i;
					for(i=0;i<size_ret0;i++){
						JSValue src00=JS_GetPropertyUint32(ctx,src0,(uint32_t)i);
						JS_FreeValue(ctx,src00);
						if(JS_IsString(src00)){
							char * js_ret0i=(char *)JS_ToCString(ctx,src00);
							ret[0][i] =((char)js_ret0i[0]);
							JS_FreeCString(ctx,(const char *)js_ret0i);
						}else{
							JS_ThrowTypeError(ctx,(const char *)"src00 does not match type char * *");
							error[0]=(bool)1;
							return NULL;
						}
					}
				}else{
					JS_ThrowTypeError(ctx,(const char *)"src0 does not match type char * *");
					error[0]=(bool)1;
					return NULL;
				}
			}else if(JS_GetClassID(src0)==JS_CLASS_INT8_ARRAY){
				if(size_ret<1){
					JS_ThrowTypeError(ctx,(const char *)"src too short (1)");
					error[0]=(bool)1;
					return NULL;
				}
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char * *)js_malloc(ctx,sizeof(char *));
				src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)0);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==JS_CLASS_INT8_ARRAY){
					size_t offset_ret0;
					size_t size_ret0;
					JSValue da_ret0=JS_GetTypedArrayBuffer(ctx,src0,&offset_ret0,&size_ret0,NULL);
					ret[0] =(char *)JS_GetArrayBuffer(ctx,&size_ret0,da_ret0);
					ret[0] +=offset_ret0;
					size_ret0 -=offset_ret0;
					ret[0] =(char *)js_malloc(ctx,size_ret0);
					memcpy((void *)ret[0],(const void *)ret[0],size_ret0);
					JS_FreeValuePtr(ctx,&da_ret0);
				}else{
					JS_ThrowTypeError(ctx,(const char *)"src0 does not match type char * *");
					error[0]=(bool)1;
					return NULL;
				}
			}else if(JS_IsString(src0)){
				if(size_ret<1){
					JS_ThrowTypeError(ctx,(const char *)"src too short (1)");
					error[0]=(bool)1;
					return NULL;
				}
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(char * *)js_malloc(ctx,sizeof(char *));
				src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)0);
				JS_FreeValue(ctx,src0);
				if(JS_IsString(src0)){
					int64_t size_ret0;
					char * js_ret0=(char *)JS_ToCStringLen(ctx,(size_t *)&size_ret0,src0);
					ret[0] =(char *)js_malloc(ctx,size_ret0+1);
					memcpy((void *)ret[0],(const void *)js_ret0,(size_t)size_ret0);
					ret[0][size_ret0]=(char)0;
					JS_FreeCString(ctx,(const char *)js_ret0);
				}else{
					JS_ThrowTypeError(ctx,(const char *)"src0 does not match type char * *");
					error[0]=(bool)1;
					return NULL;
				}
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type char * *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_IsArrayBuffer(src)||JS_GetClassID(src)==js_ArrayProxy_class_id||JS_IsArray(src)||JS_GetClassID(src)==JS_CLASS_INT8_ARRAY||JS_IsString(src)){
			ret =(char * *)js_malloc(ctx,sizeof(char *));
			if(JS_IsString(src)){
				int64_t size_ret0;
				char * js_ret0=(char *)JS_ToCStringLen(ctx,(size_t *)&size_ret0,src);
				ret[0] =(char *)js_malloc(ctx,size_ret0+1);
				memcpy((void *)ret[0],(const void *)js_ret0,(size_t)size_ret0);
				ret[0][size_ret0]=(char)0;
				JS_FreeCString(ctx,(const char *)js_ret0);
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type char * *");
				error[0]=(bool)1;
				return NULL;
			}
			if(JS_GetClassID(src)==JS_CLASS_INT8_ARRAY){
				size_t offset_ret0;
				size_t size_ret0;
				JSValue da_ret0=JS_GetTypedArrayBuffer(ctx,src,&offset_ret0,&size_ret0,NULL);
				ret[0] =(char *)JS_GetArrayBuffer(ctx,&size_ret0,da_ret0);
				ret[0] +=offset_ret0;
				size_ret0 -=offset_ret0;
				ret[0] =(char *)js_malloc(ctx,size_ret0);
				memcpy((void *)ret[0],(const void *)ret[0],size_ret0);
				JS_FreeValuePtr(ctx,&da_ret0);
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type char * *");
				error[0]=(bool)1;
				return NULL;
			}
			if(JS_IsArray(src)){
				int64_t size_ret0;
				if(JS_GetLength(ctx,src,&size_ret0)==-1){
					error[0]=(bool)1;
					return NULL;
				}
				if(size_ret0==0){
					JS_ThrowTypeError(ctx,(const char *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret[0] =(char *)js_malloc(ctx,size_ret0*sizeof(char));
				int i;
				for(i=0;i<size_ret0;i++){
					JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_IsString(src0)){
						char * js_ret0i=(char *)JS_ToCString(ctx,src0);
						ret[0][i] =((char)js_ret0i[0]);
						JS_FreeCString(ctx,(const char *)js_ret0i);
					}else{
						JS_ThrowTypeError(ctx,(const char *)"src0 does not match type char * *");
						error[0]=(bool)1;
						return NULL;
					}
				}
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type char * *");
				error[0]=(bool)1;
				return NULL;
			}
			bool is_arrayProxy0=(bool)0;
			if(JS_GetClassID(src)==js_ArrayProxy_class_id){
				is_arrayProxy0 =(bool)1;
				void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
				ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
				src =AP_fn.values(ctx,AP_fn.opaque,(int)0,(bool)false);
			}
else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type char * *");
				error[0]=(bool)1;
				return NULL;
			}
			if(is_arrayProxy0)JS_FreeValue(ctx,src);
			if(JS_IsArrayBuffer(src)){
				int64_t size_ret0;
				ret[0] =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_ret0,src);
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type char * *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char *)"src does not match type char * *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static bool * js_getbool_arr(JSContext * ctx,JSValue src,bool * error){
		bool * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,AP_fn.opaque,(int)0,(bool)false);
		}
		if(JS_IsNull(src)||JS_IsUndefined(src)){
			ret =NULL;
		}else if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(bool *)JS_GetArrayBuffer(ctx,(size_t *)&size_ret,src);
		}else if(JS_IsArray(src)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(bool *)js_malloc(ctx,size_ret*sizeof(bool));
			int i;
			for(i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsBool(src0)){
					int js_reti=JS_ToBool(ctx,src0);
					ret[i] =(bool)js_reti;
				}else{
					JS_ThrowTypeError(ctx,(const char *)"src0 does not match type bool *");
					error[0]=(bool)1;
					return NULL;
				}
			}
		}else{
			JS_ThrowTypeError(ctx,(const char *)"src does not match type bool *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Color * js_getColor_ptr(JSContext * ctx,JSValue src,bool * error){
		Color * ret;
		bool is_arrayProxy=(bool)0;
		if(JS_GetClassID(src)==js_ArrayProxy_class_id){
			is_arrayProxy =(bool)1;
			void * AP_opaque=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_fn=((ArrayProxy_class *)AP_opaque)[0];
			src =AP_fn.values(ctx,AP_fn.opaque,(int)0,(bool)false);
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
					JS_ThrowTypeError(ctx,(const char *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Color *)js_malloc(ctx,size_ret*sizeof(Color));
				int i;
				for(i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==js_Color_class_id){
						ret[i] =*(Color *)JS_GetOpaque(src0,js_Color_class_id);
					}else{
						JS_ThrowTypeError(ctx,(const char *)"src0 does not match type Color *");
						error[0]=(bool)1;
						return NULL;
					}
				}
			}else if(JS_IsNumber(src0)){
				size_ret -=size_ret%4;
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Color *)js_malloc(ctx,size_ret*sizeof(unsigned char));
				int i;
				for(i=0;i<size_ret;i++){
					unsigned char * tmp_obj=(unsigned char *)ret;
					int i0;
					for(i0=0;i0<4;i0++){
						src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i+i0);
						JS_FreeValue(ctx,src0);
						if(JS_IsNumber(src0)){
							uint32_t long_tmp_objii0;
							JS_ToUint32(ctx,&long_tmp_objii0,src0);
							tmp_obj[i+i0] =((unsigned char)long_tmp_objii0);
						}else{
							JS_ThrowTypeError(ctx,(const char *)"src0 does not match type Color *");
							error[0]=(bool)1;
							return NULL;
						}
					}
					i +=3;
				}
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type Color *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_Color_class_id){
			if(JS_GetClassID(src)==js_Color_class_id){
				ret =(Color *)JS_GetOpaque(src,js_Color_class_id);
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type Color *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char *)"src does not match type Color *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static float * js_getfloat_ptr(JSContext * ctx,JSValue src,bool * error);
	
	static Vector3 * js_getVector3_ptr(JSContext * ctx,JSValue src,bool * error);
	
	static void js_GuiStyleProp_finalizer(JSRuntime * rt,JSValue val){
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque(val,js_GuiStyleProp_class_id);
		if(ptr)js_free_rt(rt,(void *)ptr);
	}
	
	static JSValue js_GuiStyleProp_get_controlId(JSContext * ctx,JSValue this_val){
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		unsigned short controlId=ptr[0].controlId;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)controlId));
		return ret;
	}
	
	static JSValue js_GuiStyleProp_set_controlId(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		unsigned short value=js_getunsignedshort(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		ptr[0].controlId=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiStyleProp_get_propertyId(JSContext * ctx,JSValue this_val){
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		unsigned short propertyId=ptr[0].propertyId;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)propertyId));
		return ret;
	}
	
	static JSValue js_GuiStyleProp_set_propertyId(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		unsigned short value=js_getunsignedshort(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		ptr[0].propertyId=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiStyleProp_get_propertyValue(JSContext * ctx,JSValue this_val){
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		int propertyValue=ptr[0].propertyValue;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)propertyValue));
		return ret;
	}
	
	static JSValue js_GuiStyleProp_set_propertyValue(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		GuiStyleProp * ptr=(GuiStyleProp *)JS_GetOpaque2(ctx,this_val,js_GuiStyleProp_class_id);
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		ptr[0].propertyValue=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_GuiStyleProp_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","GuiStyleProp", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("controlId",js_GuiStyleProp_get_controlId,js_GuiStyleProp_set_controlId),
		JS_CGETSET_DEF("propertyId",js_GuiStyleProp_get_propertyId,js_GuiStyleProp_set_propertyId),
		JS_CGETSET_DEF("propertyValue",js_GuiStyleProp_get_propertyValue,js_GuiStyleProp_set_propertyValue)
	};
	
	static int js_declare_GuiStyleProp(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_GuiStyleProp_class_id);
		JSClassDef js_GuiStyleProp_def={ .class_name = "GuiStyleProp", .finalizer = js_GuiStyleProp_finalizer };
		JS_NewClass(rt,js_GuiStyleProp_class_id,(const JSClassDef *)&js_GuiStyleProp_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_GuiStyleProp_proto_funcs,(int)countof(js_GuiStyleProp_proto_funcs));
		JS_SetClassProto(ctx,js_GuiStyleProp_class_id,proto);
		return 0;
	}
	
	static JSValue js_GuiStyleProp_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			GuiStyleProp * ptr__return=(GuiStyleProp *)js_calloc(ctx,(size_t)1,sizeof(GuiStyleProp));
			JSValue _return=JS_NewObjectClass(ctx,(int)js_GuiStyleProp_class_id);
			JS_SetOpaque(_return,(void *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		unsigned short controlId=js_getunsignedshort(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned short propertyId=js_getunsignedshort(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int propertyValue=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		GuiStyleProp _struct={
			controlId,
			propertyId,
			propertyValue
		};
		GuiStyleProp * ptr__return=(GuiStyleProp *)js_malloc(ctx,sizeof(GuiStyleProp));
		ptr__return[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,(int)js_GuiStyleProp_class_id);
		JS_SetOpaque(_return,(void *)ptr__return);
		return _return;
	}
	
	static JSValue js_GuiEnable(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		GuiEnable();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiDisable(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		GuiDisable();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiLock(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		GuiLock();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiUnlock(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		GuiUnlock();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiIsLocked(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool returnVal=GuiIsLocked();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_GuiSetAlpha(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float alpha=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		GuiSetAlpha(alpha);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiSetState(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int state=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		GuiSetState(state);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiGetState(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int returnVal=GuiGetState();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiSetFont(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font font=js_getFont(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		GuiSetFont(font);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiGetFont(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Font returnVal=GuiGetFont();
		Font * ptr_ret=(Font *)js_malloc(ctx,sizeof(Font));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Font_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GuiSetStyle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int control=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int property=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int value=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		GuiSetStyle(control,property,value);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiGetStyle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int control=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int property=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiGetStyle(control,property);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiLoadStyle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		GuiLoadStyle((const char *)fileName);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiLoadStyleDefault(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		GuiLoadStyleDefault();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiEnableTooltip(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		GuiEnableTooltip();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiDisableTooltip(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		GuiDisableTooltip();
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiSetTooltip(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * tooltip=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		GuiSetTooltip((const char *)tooltip);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiIconText(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int iconId=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char *)GuiIconText(iconId,(const char *)text);
		JSValue ret=JS_NewString(ctx,(const char *)returnVal);
		return ret;
	}
	
	static JSValue js_GuiSetIconScale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int scale=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		GuiSetIconScale(scale);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiGetIcons(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int * returnVal=GuiGetIcons();
		JSValue ret=JS_NewArray(ctx);
		int * sizeref_ret=returnVal;
		size_t size_ret=sizeof(sizeref_ret);
		size_t size1_ret=sizeof(int);
		size_ret =size_ret/size1_ret;
		int i;
		for(i=0;i<size_ret;i++){
			JSValue js_ret=JS_NewInt32(ctx,(int32_t)((long)returnVal[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		return ret;
	}
	
	static JSValue js_GuiLoadIcons(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * fileName=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool loadIconsName=js_getbool(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * * returnVal=GuiLoadIcons((const char *)fileName,loadIconsName);
		JSValue ret=JS_NewArray(ctx);
		char * * sizeref_ret=returnVal;
		size_t size_ret=sizeof(sizeref_ret);
		size_t size1_ret=sizeof(char *);
		size_ret =size_ret/size1_ret;
		int i;
		for(i=0;i<size_ret;i++){
			JSValue js_ret=JS_NewString(ctx,(const char *)returnVal[i]);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		return ret;
	}
	
	static JSValue js_GuiDrawIcon(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int iconId=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int posX=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int posY=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int pixelSize=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		GuiDrawIcon(iconId,posX,posY,pixelSize,color);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GuiGetTextWidth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * text=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiGetTextWidth((const char *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiWindowBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * title=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiWindowBox(bounds,(const char *)title);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiGroupBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiGroupBox(bounds,(const char *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiLine(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiLine(bounds,(const char *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiPanel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiPanel(bounds,(const char *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiTabBar(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * * text=js_getchar_arr_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int count=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int * active=js_getint_ptr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiTabBar(bounds,(const char * *)text,count,active);
		if(JS_IsArray(argv[3])==1){
			JSValue js_argv30=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[3],(uint32_t)0,js_argv30,JS_PROP_C_W_E);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx,memoryHead);
		return ret;
	}
	
	static JSValue js_GuiScrollPanel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle content=js_getRectangle(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 * scroll=js_getVector2_ptr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Rectangle * view=js_getRectangle_ptr(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiScrollPanel(bounds,(const char *)text,content,scroll,view);
		JS_SetOpaque(argv[3],(void *)scroll);
		JS_SetOpaque(argv[4],(void *)view);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiLabel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiLabel(bounds,(const char *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiButton(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiButton(bounds,(const char *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiLabelButton(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiLabelButton(bounds,(const char *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiToggle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool * active=js_getbool_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiToggle(bounds,(const char *)text,active);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv20=JS_NewBool(ctx,active[0]);
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv20,JS_PROP_C_W_E);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiToggleGroup(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * active=js_getint_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiToggleGroup(bounds,(const char *)text,active);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv20=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv20,JS_PROP_C_W_E);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiToggleSlider(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * active=js_getint_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiToggleSlider(bounds,(const char *)text,active);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv20=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv20,JS_PROP_C_W_E);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiCheckBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool * checked=js_getbool_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiCheckBox(bounds,(const char *)text,checked);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv20=JS_NewBool(ctx,checked[0]);
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv20,JS_PROP_C_W_E);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiComboBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * active=js_getint_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiComboBox(bounds,(const char *)text,active);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv20=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv20,JS_PROP_C_W_E);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiDropdownBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * active=js_getint_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool editMode=js_getbool(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiDropdownBox(bounds,(const char *)text,active,editMode);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv20=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv20,JS_PROP_C_W_E);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiSpinner(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * value=js_getint_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int minValue=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int maxValue=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		bool editMode=js_getbool(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiSpinner(bounds,(const char *)text,value,minValue,maxValue,editMode);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx,memoryHead);
		return ret;
	}
	
	static JSValue js_GuiValueBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * value=js_getint_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int minValue=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int maxValue=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		bool editMode=js_getbool(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiValueBox(bounds,(const char *)text,value,minValue,maxValue,editMode);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx,memoryHead);
		return ret;
	}
	
	static JSValue js_GuiValueBoxFloat(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * textValue=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float * value=js_getfloat_arr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		bool editMode=js_getbool(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiValueBoxFloat(bounds,(const char *)text,textValue,value,editMode);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx,memoryHead);
		return ret;
	}
	
	static JSValue js_GuiTextBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * * text=js_getchar_arr_ptr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int textSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool editMode=js_getbool(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiTextBox(bounds,*text,textSize,editMode);
		if(JS_IsArray(argv[1])==1){
			argv[1] =JS_NewString(ctx,(const char *)text[0]);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiSlider(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * textLeft=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * textRight=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float * value=js_getfloat_arr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float minValue=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		float maxValue=js_getfloat(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiSlider(bounds,(const char *)textLeft,(const char *)textRight,value,minValue,maxValue);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx,memoryHead);
		return ret;
	}
	
	static JSValue js_GuiSliderBar(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * textLeft=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * textRight=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float * value=js_getfloat_arr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float minValue=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		float maxValue=js_getfloat(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiSliderBar(bounds,(const char *)textLeft,(const char *)textRight,value,minValue,maxValue);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx,memoryHead);
		return ret;
	}
	
	static JSValue js_GuiProgressBar(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * textLeft=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * textRight=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float * value=js_getfloat_arr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float minValue=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		float maxValue=js_getfloat(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiProgressBar(bounds,(const char *)textLeft,(const char *)textRight,value,minValue,maxValue);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx,memoryHead);
		return ret;
	}
	
	static JSValue js_GuiStatusBar(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiStatusBar(bounds,(const char *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiDummyRec(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiDummyRec(bounds,(const char *)text);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiGrid(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float spacing=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int subdivs=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 * mouseCell=js_getVector2_ptr(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiGrid(bounds,(const char *)text,spacing,subdivs,mouseCell);
		JS_SetOpaque(argv[4],(void *)mouseCell);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiListView(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int * scrollIndex=js_getint_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int * active=js_getint_ptr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiListView(bounds,(const char *)text,scrollIndex,active);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv20=JS_NewInt32(ctx,(int32_t)((long)scrollIndex[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv20,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[3])==1){
			JSValue js_argv30=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[3],(uint32_t)0,js_argv30,JS_PROP_C_W_E);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiListViewEx(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * * text=js_getchar_arr_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int count=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int * scrollIndex=js_getint_ptr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int * active=js_getint_ptr(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int * focus=js_getint_arr(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiListViewEx(bounds,(const char * *)text,count,scrollIndex,active,focus);
		if(JS_IsArray(argv[3])==1){
			JSValue js_argv30=JS_NewInt32(ctx,(int32_t)((long)scrollIndex[0]));
			JS_DefinePropertyValueUint32(ctx,argv[3],(uint32_t)0,js_argv30,JS_PROP_C_W_E);
		}
		if(JS_IsArray(argv[4])==1){
			JSValue js_argv40=JS_NewInt32(ctx,(int32_t)((long)active[0]));
			JS_DefinePropertyValueUint32(ctx,argv[4],(uint32_t)0,js_argv40,JS_PROP_C_W_E);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx,memoryHead);
		return ret;
	}
	
	static JSValue js_GuiMessageBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * title=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * message=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		char * buttons=js_getchar_arr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiMessageBox(bounds,(const char *)title,(const char *)message,(const char *)buttons);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx,memoryHead);
		return ret;
	}
	
	static JSValue js_GuiTextInputBox(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * title=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * message=js_getchar_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		char * buttons=js_getchar_arr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int textMaxSize=js_getint(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		bool * secretViewActive=js_getbool_arr(ctx,argv[6],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiTextInputBox(bounds,(const char *)title,(const char *)message,(const char *)buttons,text,textMaxSize,secretViewActive);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx,memoryHead);
		return ret;
	}
	
	static JSValue js_GuiColorPicker(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color * color=js_getColor_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiColorPicker(bounds,(const char *)text,color);
		JS_SetOpaque(argv[2],(void *)color);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiColorPanel(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Color * color=js_getColor_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiColorPanel(bounds,(const char *)text,color);
		JS_SetOpaque(argv[2],(void *)color);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiColorBarAlpha(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float * alpha=js_getfloat_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiColorBarAlpha(bounds,(const char *)text,alpha);
		if(JS_IsArray(argv[2])==1){
			JSValue js_argv20=JS_NewFloat64(ctx,((double)alpha[0]));
			JS_DefinePropertyValueUint32(ctx,argv[2],(uint32_t)0,js_argv20,JS_PROP_C_W_E);
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiColorBarHue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float * value=js_getfloat_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiColorBarHue(bounds,(const char *)text,value);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx,memoryHead);
		return ret;
	}
	
	static JSValue js_GuiColorPickerHSV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 * colorHsv=js_getVector3_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiColorPickerHSV(bounds,(const char *)text,colorHsv);
		JS_SetOpaque(argv[2],(void *)colorHsv);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_GuiColorPanelHSV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Rectangle bounds=js_getRectangle(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * text=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 * colorHsv=js_getVector3_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=GuiColorPanelHSV(bounds,(const char *)text,colorHsv);
		JS_SetOpaque(argv[2],(void *)colorHsv);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	static const JSCFunctionListEntry jsraygui_funcs[]={
		JS_CFUNC_DEF("GuiEnable",0,js_GuiEnable),
		JS_CFUNC_DEF("GuiDisable",0,js_GuiDisable),
		JS_CFUNC_DEF("GuiLock",0,js_GuiLock),
		JS_CFUNC_DEF("GuiUnlock",0,js_GuiUnlock),
		JS_CFUNC_DEF("GuiIsLocked",0,js_GuiIsLocked),
		JS_CFUNC_DEF("GuiSetAlpha",1,js_GuiSetAlpha),
		JS_CFUNC_DEF("GuiSetState",1,js_GuiSetState),
		JS_CFUNC_DEF("GuiGetState",0,js_GuiGetState),
		JS_CFUNC_DEF("GuiSetFont",1,js_GuiSetFont),
		JS_CFUNC_DEF("GuiGetFont",0,js_GuiGetFont),
		JS_CFUNC_DEF("GuiSetStyle",3,js_GuiSetStyle),
		JS_CFUNC_DEF("GuiGetStyle",2,js_GuiGetStyle),
		JS_CFUNC_DEF("GuiLoadStyle",1,js_GuiLoadStyle),
		JS_CFUNC_DEF("GuiLoadStyleDefault",0,js_GuiLoadStyleDefault),
		JS_CFUNC_DEF("GuiEnableTooltip",0,js_GuiEnableTooltip),
		JS_CFUNC_DEF("GuiDisableTooltip",0,js_GuiDisableTooltip),
		JS_CFUNC_DEF("GuiSetTooltip",1,js_GuiSetTooltip),
		JS_CFUNC_DEF("GuiIconText",2,js_GuiIconText),
		JS_CFUNC_DEF("GuiSetIconScale",1,js_GuiSetIconScale),
		JS_CFUNC_DEF("GuiGetIcons",0,js_GuiGetIcons),
		JS_CFUNC_DEF("GuiLoadIcons",2,js_GuiLoadIcons),
		JS_CFUNC_DEF("GuiDrawIcon",5,js_GuiDrawIcon),
		JS_CFUNC_DEF("GuiGetTextWidth",1,js_GuiGetTextWidth),
		JS_CFUNC_DEF("GuiWindowBox",2,js_GuiWindowBox),
		JS_CFUNC_DEF("GuiGroupBox",2,js_GuiGroupBox),
		JS_CFUNC_DEF("GuiLine",2,js_GuiLine),
		JS_CFUNC_DEF("GuiPanel",2,js_GuiPanel),
		JS_CFUNC_DEF("GuiTabBar",4,js_GuiTabBar),
		JS_CFUNC_DEF("GuiScrollPanel",5,js_GuiScrollPanel),
		JS_CFUNC_DEF("GuiLabel",2,js_GuiLabel),
		JS_CFUNC_DEF("GuiButton",2,js_GuiButton),
		JS_CFUNC_DEF("GuiLabelButton",2,js_GuiLabelButton),
		JS_CFUNC_DEF("GuiToggle",3,js_GuiToggle),
		JS_CFUNC_DEF("GuiToggleGroup",3,js_GuiToggleGroup),
		JS_CFUNC_DEF("GuiToggleSlider",3,js_GuiToggleSlider),
		JS_CFUNC_DEF("GuiCheckBox",3,js_GuiCheckBox),
		JS_CFUNC_DEF("GuiComboBox",3,js_GuiComboBox),
		JS_CFUNC_DEF("GuiDropdownBox",4,js_GuiDropdownBox),
		JS_CFUNC_DEF("GuiSpinner",6,js_GuiSpinner),
		JS_CFUNC_DEF("GuiValueBox",6,js_GuiValueBox),
		JS_CFUNC_DEF("GuiValueBoxFloat",5,js_GuiValueBoxFloat),
		JS_CFUNC_DEF("GuiTextBox",4,js_GuiTextBox),
		JS_CFUNC_DEF("GuiSlider",6,js_GuiSlider),
		JS_CFUNC_DEF("GuiSliderBar",6,js_GuiSliderBar),
		JS_CFUNC_DEF("GuiProgressBar",6,js_GuiProgressBar),
		JS_CFUNC_DEF("GuiStatusBar",2,js_GuiStatusBar),
		JS_CFUNC_DEF("GuiDummyRec",2,js_GuiDummyRec),
		JS_CFUNC_DEF("GuiGrid",5,js_GuiGrid),
		JS_CFUNC_DEF("GuiListView",4,js_GuiListView),
		JS_CFUNC_DEF("GuiListViewEx",6,js_GuiListViewEx),
		JS_CFUNC_DEF("GuiMessageBox",4,js_GuiMessageBox),
		JS_CFUNC_DEF("GuiTextInputBox",7,js_GuiTextInputBox),
		JS_CFUNC_DEF("GuiColorPicker",3,js_GuiColorPicker),
		JS_CFUNC_DEF("GuiColorPanel",3,js_GuiColorPanel),
		JS_CFUNC_DEF("GuiColorBarAlpha",3,js_GuiColorBarAlpha),
		JS_CFUNC_DEF("GuiColorBarHue",3,js_GuiColorBarHue),
		JS_CFUNC_DEF("GuiColorPickerHSV",3,js_GuiColorPickerHSV),
		JS_CFUNC_DEF("GuiColorPanelHSV",3,js_GuiColorPanelHSV)
	};
	
	static int js_raygui_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsraygui_funcs);
		JS_SetModuleExportList(ctx,m,jsraygui_funcs,(int)listcount);
		js_declare_GuiStyleProp(ctx,m);
		JSValue GuiStyleProp_constr=JS_NewCFunction2(ctx,js_GuiStyleProp_constructor,(const char *)"GuiStyleProp",(int)3,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char *)"GuiStyleProp",GuiStyleProp_constr);
		JS_SetModuleExport(ctx,m,(const char *)"STATE_NORMAL",JS_NewInt32(ctx,(int32_t)STATE_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"STATE_FOCUSED",JS_NewInt32(ctx,(int32_t)STATE_FOCUSED));
		JS_SetModuleExport(ctx,m,(const char *)"STATE_PRESSED",JS_NewInt32(ctx,(int32_t)STATE_PRESSED));
		JS_SetModuleExport(ctx,m,(const char *)"STATE_DISABLED",JS_NewInt32(ctx,(int32_t)STATE_DISABLED));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_LEFT",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_CENTER",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_CENTER));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_RIGHT",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_TOP",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_TOP));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_MIDDLE",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_MIDDLE));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGN_BOTTOM",JS_NewInt32(ctx,(int32_t)TEXT_ALIGN_BOTTOM));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_WRAP_NONE",JS_NewInt32(ctx,(int32_t)TEXT_WRAP_NONE));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_WRAP_CHAR",JS_NewInt32(ctx,(int32_t)TEXT_WRAP_CHAR));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_WRAP_WORD",JS_NewInt32(ctx,(int32_t)TEXT_WRAP_WORD));
		JS_SetModuleExport(ctx,m,(const char *)"DEFAULT",JS_NewInt32(ctx,(int32_t)DEFAULT));
		JS_SetModuleExport(ctx,m,(const char *)"LABEL",JS_NewInt32(ctx,(int32_t)LABEL));
		JS_SetModuleExport(ctx,m,(const char *)"BUTTON",JS_NewInt32(ctx,(int32_t)BUTTON));
		JS_SetModuleExport(ctx,m,(const char *)"TOGGLE",JS_NewInt32(ctx,(int32_t)TOGGLE));
		JS_SetModuleExport(ctx,m,(const char *)"SLIDER",JS_NewInt32(ctx,(int32_t)SLIDER));
		JS_SetModuleExport(ctx,m,(const char *)"PROGRESSBAR",JS_NewInt32(ctx,(int32_t)PROGRESSBAR));
		JS_SetModuleExport(ctx,m,(const char *)"CHECKBOX",JS_NewInt32(ctx,(int32_t)CHECKBOX));
		JS_SetModuleExport(ctx,m,(const char *)"COMBOBOX",JS_NewInt32(ctx,(int32_t)COMBOBOX));
		JS_SetModuleExport(ctx,m,(const char *)"DROPDOWNBOX",JS_NewInt32(ctx,(int32_t)DROPDOWNBOX));
		JS_SetModuleExport(ctx,m,(const char *)"TEXTBOX",JS_NewInt32(ctx,(int32_t)TEXTBOX));
		JS_SetModuleExport(ctx,m,(const char *)"VALUEBOX",JS_NewInt32(ctx,(int32_t)VALUEBOX));
		JS_SetModuleExport(ctx,m,(const char *)"CONTROL11",JS_NewInt32(ctx,(int32_t)CONTROL11));
		JS_SetModuleExport(ctx,m,(const char *)"LISTVIEW",JS_NewInt32(ctx,(int32_t)LISTVIEW));
		JS_SetModuleExport(ctx,m,(const char *)"COLORPICKER",JS_NewInt32(ctx,(int32_t)COLORPICKER));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLLBAR",JS_NewInt32(ctx,(int32_t)SCROLLBAR));
		JS_SetModuleExport(ctx,m,(const char *)"STATUSBAR",JS_NewInt32(ctx,(int32_t)STATUSBAR));
		JS_SetModuleExport(ctx,m,(const char *)"BORDER_COLOR_NORMAL",JS_NewInt32(ctx,(int32_t)BORDER_COLOR_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"BASE_COLOR_NORMAL",JS_NewInt32(ctx,(int32_t)BASE_COLOR_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_COLOR_NORMAL",JS_NewInt32(ctx,(int32_t)TEXT_COLOR_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"BORDER_COLOR_FOCUSED",JS_NewInt32(ctx,(int32_t)BORDER_COLOR_FOCUSED));
		JS_SetModuleExport(ctx,m,(const char *)"BASE_COLOR_FOCUSED",JS_NewInt32(ctx,(int32_t)BASE_COLOR_FOCUSED));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_COLOR_FOCUSED",JS_NewInt32(ctx,(int32_t)TEXT_COLOR_FOCUSED));
		JS_SetModuleExport(ctx,m,(const char *)"BORDER_COLOR_PRESSED",JS_NewInt32(ctx,(int32_t)BORDER_COLOR_PRESSED));
		JS_SetModuleExport(ctx,m,(const char *)"BASE_COLOR_PRESSED",JS_NewInt32(ctx,(int32_t)BASE_COLOR_PRESSED));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_COLOR_PRESSED",JS_NewInt32(ctx,(int32_t)TEXT_COLOR_PRESSED));
		JS_SetModuleExport(ctx,m,(const char *)"BORDER_COLOR_DISABLED",JS_NewInt32(ctx,(int32_t)BORDER_COLOR_DISABLED));
		JS_SetModuleExport(ctx,m,(const char *)"BASE_COLOR_DISABLED",JS_NewInt32(ctx,(int32_t)BASE_COLOR_DISABLED));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_COLOR_DISABLED",JS_NewInt32(ctx,(int32_t)TEXT_COLOR_DISABLED));
		JS_SetModuleExport(ctx,m,(const char *)"BORDER_WIDTH",JS_NewInt32(ctx,(int32_t)BORDER_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_PADDING",JS_NewInt32(ctx,(int32_t)TEXT_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGNMENT",JS_NewInt32(ctx,(int32_t)TEXT_ALIGNMENT));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_SIZE",JS_NewInt32(ctx,(int32_t)TEXT_SIZE));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_SPACING",JS_NewInt32(ctx,(int32_t)TEXT_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"LINE_COLOR",JS_NewInt32(ctx,(int32_t)LINE_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"BACKGROUND_COLOR",JS_NewInt32(ctx,(int32_t)BACKGROUND_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_LINE_SPACING",JS_NewInt32(ctx,(int32_t)TEXT_LINE_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_ALIGNMENT_VERTICAL",JS_NewInt32(ctx,(int32_t)TEXT_ALIGNMENT_VERTICAL));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_WRAP_MODE",JS_NewInt32(ctx,(int32_t)TEXT_WRAP_MODE));
		JS_SetModuleExport(ctx,m,(const char *)"GROUP_PADDING",JS_NewInt32(ctx,(int32_t)GROUP_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"SLIDER_WIDTH",JS_NewInt32(ctx,(int32_t)SLIDER_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"SLIDER_PADDING",JS_NewInt32(ctx,(int32_t)SLIDER_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"PROGRESS_PADDING",JS_NewInt32(ctx,(int32_t)PROGRESS_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"ARROWS_SIZE",JS_NewInt32(ctx,(int32_t)ARROWS_SIZE));
		JS_SetModuleExport(ctx,m,(const char *)"ARROWS_VISIBLE",JS_NewInt32(ctx,(int32_t)ARROWS_VISIBLE));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLL_SLIDER_PADDING",JS_NewInt32(ctx,(int32_t)SCROLL_SLIDER_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLL_SLIDER_SIZE",JS_NewInt32(ctx,(int32_t)SCROLL_SLIDER_SIZE));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLL_PADDING",JS_NewInt32(ctx,(int32_t)SCROLL_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLL_SPEED",JS_NewInt32(ctx,(int32_t)SCROLL_SPEED));
		JS_SetModuleExport(ctx,m,(const char *)"CHECK_PADDING",JS_NewInt32(ctx,(int32_t)CHECK_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"COMBO_BUTTON_WIDTH",JS_NewInt32(ctx,(int32_t)COMBO_BUTTON_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"COMBO_BUTTON_SPACING",JS_NewInt32(ctx,(int32_t)COMBO_BUTTON_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"ARROW_PADDING",JS_NewInt32(ctx,(int32_t)ARROW_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"DROPDOWN_ITEMS_SPACING",JS_NewInt32(ctx,(int32_t)DROPDOWN_ITEMS_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"DROPDOWN_ARROW_HIDDEN",JS_NewInt32(ctx,(int32_t)DROPDOWN_ARROW_HIDDEN));
		JS_SetModuleExport(ctx,m,(const char *)"DROPDOWN_ROLL_UP",JS_NewInt32(ctx,(int32_t)DROPDOWN_ROLL_UP));
		JS_SetModuleExport(ctx,m,(const char *)"TEXT_READONLY",JS_NewInt32(ctx,(int32_t)TEXT_READONLY));
		JS_SetModuleExport(ctx,m,(const char *)"SPINNER_BUTTON_WIDTH",JS_NewInt32(ctx,(int32_t)SPINNER_BUTTON_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"SPINNER_BUTTON_SPACING",JS_NewInt32(ctx,(int32_t)SPINNER_BUTTON_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"LIST_ITEMS_HEIGHT",JS_NewInt32(ctx,(int32_t)LIST_ITEMS_HEIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"LIST_ITEMS_SPACING",JS_NewInt32(ctx,(int32_t)LIST_ITEMS_SPACING));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLLBAR_WIDTH",JS_NewInt32(ctx,(int32_t)SCROLLBAR_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLLBAR_SIDE",JS_NewInt32(ctx,(int32_t)SCROLLBAR_SIDE));
		JS_SetModuleExport(ctx,m,(const char *)"LIST_ITEMS_BORDER_NORMAL",JS_NewInt32(ctx,(int32_t)LIST_ITEMS_BORDER_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"LIST_ITEMS_BORDER_WIDTH",JS_NewInt32(ctx,(int32_t)LIST_ITEMS_BORDER_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"COLOR_SELECTOR_SIZE",JS_NewInt32(ctx,(int32_t)COLOR_SELECTOR_SIZE));
		JS_SetModuleExport(ctx,m,(const char *)"HUEBAR_WIDTH",JS_NewInt32(ctx,(int32_t)HUEBAR_WIDTH));
		JS_SetModuleExport(ctx,m,(const char *)"HUEBAR_PADDING",JS_NewInt32(ctx,(int32_t)HUEBAR_PADDING));
		JS_SetModuleExport(ctx,m,(const char *)"HUEBAR_SELECTOR_HEIGHT",JS_NewInt32(ctx,(int32_t)HUEBAR_SELECTOR_HEIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"HUEBAR_SELECTOR_OVERFLOW",JS_NewInt32(ctx,(int32_t)HUEBAR_SELECTOR_OVERFLOW));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_NONE",JS_NewInt32(ctx,(int32_t)ICON_NONE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOLDER_FILE_OPEN",JS_NewInt32(ctx,(int32_t)ICON_FOLDER_FILE_OPEN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_SAVE_CLASSIC",JS_NewInt32(ctx,(int32_t)ICON_FILE_SAVE_CLASSIC));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOLDER_OPEN",JS_NewInt32(ctx,(int32_t)ICON_FOLDER_OPEN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOLDER_SAVE",JS_NewInt32(ctx,(int32_t)ICON_FOLDER_SAVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_OPEN",JS_NewInt32(ctx,(int32_t)ICON_FILE_OPEN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_SAVE",JS_NewInt32(ctx,(int32_t)ICON_FILE_SAVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_EXPORT",JS_NewInt32(ctx,(int32_t)ICON_FILE_EXPORT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_ADD",JS_NewInt32(ctx,(int32_t)ICON_FILE_ADD));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_DELETE",JS_NewInt32(ctx,(int32_t)ICON_FILE_DELETE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_TEXT",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_TEXT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_AUDIO",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_AUDIO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_IMAGE",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_IMAGE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_PLAY",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_PLAY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_VIDEO",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_VIDEO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_INFO",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_INFO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_COPY",JS_NewInt32(ctx,(int32_t)ICON_FILE_COPY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_CUT",JS_NewInt32(ctx,(int32_t)ICON_FILE_CUT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_PASTE",JS_NewInt32(ctx,(int32_t)ICON_FILE_PASTE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_HAND",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_HAND));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_POINTER",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_POINTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_CLASSIC",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_CLASSIC));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PENCIL",JS_NewInt32(ctx,(int32_t)ICON_PENCIL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PENCIL_BIG",JS_NewInt32(ctx,(int32_t)ICON_PENCIL_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BRUSH_CLASSIC",JS_NewInt32(ctx,(int32_t)ICON_BRUSH_CLASSIC));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BRUSH_PAINTER",JS_NewInt32(ctx,(int32_t)ICON_BRUSH_PAINTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WATER_DROP",JS_NewInt32(ctx,(int32_t)ICON_WATER_DROP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_COLOR_PICKER",JS_NewInt32(ctx,(int32_t)ICON_COLOR_PICKER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_RUBBER",JS_NewInt32(ctx,(int32_t)ICON_RUBBER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_COLOR_BUCKET",JS_NewInt32(ctx,(int32_t)ICON_COLOR_BUCKET));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TEXT_T",JS_NewInt32(ctx,(int32_t)ICON_TEXT_T));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TEXT_A",JS_NewInt32(ctx,(int32_t)ICON_TEXT_A));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SCALE",JS_NewInt32(ctx,(int32_t)ICON_SCALE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_RESIZE",JS_NewInt32(ctx,(int32_t)ICON_RESIZE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILTER_POINT",JS_NewInt32(ctx,(int32_t)ICON_FILTER_POINT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILTER_BILINEAR",JS_NewInt32(ctx,(int32_t)ICON_FILTER_BILINEAR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CROP",JS_NewInt32(ctx,(int32_t)ICON_CROP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CROP_ALPHA",JS_NewInt32(ctx,(int32_t)ICON_CROP_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SQUARE_TOGGLE",JS_NewInt32(ctx,(int32_t)ICON_SQUARE_TOGGLE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SYMMETRY",JS_NewInt32(ctx,(int32_t)ICON_SYMMETRY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SYMMETRY_HORIZONTAL",JS_NewInt32(ctx,(int32_t)ICON_SYMMETRY_HORIZONTAL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SYMMETRY_VERTICAL",JS_NewInt32(ctx,(int32_t)ICON_SYMMETRY_VERTICAL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LENS",JS_NewInt32(ctx,(int32_t)ICON_LENS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LENS_BIG",JS_NewInt32(ctx,(int32_t)ICON_LENS_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EYE_ON",JS_NewInt32(ctx,(int32_t)ICON_EYE_ON));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EYE_OFF",JS_NewInt32(ctx,(int32_t)ICON_EYE_OFF));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILTER_TOP",JS_NewInt32(ctx,(int32_t)ICON_FILTER_TOP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILTER",JS_NewInt32(ctx,(int32_t)ICON_FILTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_POINT",JS_NewInt32(ctx,(int32_t)ICON_TARGET_POINT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_SMALL",JS_NewInt32(ctx,(int32_t)ICON_TARGET_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_BIG",JS_NewInt32(ctx,(int32_t)ICON_TARGET_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_MOVE",JS_NewInt32(ctx,(int32_t)ICON_TARGET_MOVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_MOVE",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_MOVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_LEFT",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_UNDO",JS_NewInt32(ctx,(int32_t)ICON_UNDO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REDO",JS_NewInt32(ctx,(int32_t)ICON_REDO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REREDO",JS_NewInt32(ctx,(int32_t)ICON_REREDO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MUTATE",JS_NewInt32(ctx,(int32_t)ICON_MUTATE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ROTATE",JS_NewInt32(ctx,(int32_t)ICON_ROTATE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REPEAT",JS_NewInt32(ctx,(int32_t)ICON_REPEAT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SHUFFLE",JS_NewInt32(ctx,(int32_t)ICON_SHUFFLE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EMPTYBOX",JS_NewInt32(ctx,(int32_t)ICON_EMPTYBOX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET",JS_NewInt32(ctx,(int32_t)ICON_TARGET));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_SMALL_FILL",JS_NewInt32(ctx,(int32_t)ICON_TARGET_SMALL_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_BIG_FILL",JS_NewInt32(ctx,(int32_t)ICON_TARGET_BIG_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TARGET_MOVE_FILL",JS_NewInt32(ctx,(int32_t)ICON_TARGET_MOVE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_MOVE_FILL",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_MOVE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_FILL",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_RIGHT_FILL",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE_RIGHT_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_LEFT_FILL",JS_NewInt32(ctx,(int32_t)ICON_CURSOR_SCALE_LEFT_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_UNDO_FILL",JS_NewInt32(ctx,(int32_t)ICON_UNDO_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REDO_FILL",JS_NewInt32(ctx,(int32_t)ICON_REDO_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REREDO_FILL",JS_NewInt32(ctx,(int32_t)ICON_REREDO_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MUTATE_FILL",JS_NewInt32(ctx,(int32_t)ICON_MUTATE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ROTATE_FILL",JS_NewInt32(ctx,(int32_t)ICON_ROTATE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REPEAT_FILL",JS_NewInt32(ctx,(int32_t)ICON_REPEAT_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SHUFFLE_FILL",JS_NewInt32(ctx,(int32_t)ICON_SHUFFLE_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EMPTYBOX_SMALL",JS_NewInt32(ctx,(int32_t)ICON_EMPTYBOX_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX",JS_NewInt32(ctx,(int32_t)ICON_BOX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_TOP",JS_NewInt32(ctx,(int32_t)ICON_BOX_TOP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_TOP_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_BOX_TOP_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_BOX_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_BOX_BOTTOM_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM",JS_NewInt32(ctx,(int32_t)ICON_BOX_BOTTOM));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM_LEFT",JS_NewInt32(ctx,(int32_t)ICON_BOX_BOTTOM_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_LEFT",JS_NewInt32(ctx,(int32_t)ICON_BOX_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_TOP_LEFT",JS_NewInt32(ctx,(int32_t)ICON_BOX_TOP_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_CENTER",JS_NewInt32(ctx,(int32_t)ICON_BOX_CENTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_CIRCLE_MASK",JS_NewInt32(ctx,(int32_t)ICON_BOX_CIRCLE_MASK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_POT",JS_NewInt32(ctx,(int32_t)ICON_POT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ALPHA_MULTIPLY",JS_NewInt32(ctx,(int32_t)ICON_ALPHA_MULTIPLY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ALPHA_CLEAR",JS_NewInt32(ctx,(int32_t)ICON_ALPHA_CLEAR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_DITHERING",JS_NewInt32(ctx,(int32_t)ICON_DITHERING));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MIPMAPS",JS_NewInt32(ctx,(int32_t)ICON_MIPMAPS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_GRID",JS_NewInt32(ctx,(int32_t)ICON_BOX_GRID));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_GRID",JS_NewInt32(ctx,(int32_t)ICON_GRID));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_CORNERS_SMALL",JS_NewInt32(ctx,(int32_t)ICON_BOX_CORNERS_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_CORNERS_BIG",JS_NewInt32(ctx,(int32_t)ICON_BOX_CORNERS_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOUR_BOXES",JS_NewInt32(ctx,(int32_t)ICON_FOUR_BOXES));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_GRID_FILL",JS_NewInt32(ctx,(int32_t)ICON_GRID_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_MULTISIZE",JS_NewInt32(ctx,(int32_t)ICON_BOX_MULTISIZE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ZOOM_SMALL",JS_NewInt32(ctx,(int32_t)ICON_ZOOM_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ZOOM_MEDIUM",JS_NewInt32(ctx,(int32_t)ICON_ZOOM_MEDIUM));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ZOOM_BIG",JS_NewInt32(ctx,(int32_t)ICON_ZOOM_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ZOOM_ALL",JS_NewInt32(ctx,(int32_t)ICON_ZOOM_ALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ZOOM_CENTER",JS_NewInt32(ctx,(int32_t)ICON_ZOOM_CENTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_DOTS_SMALL",JS_NewInt32(ctx,(int32_t)ICON_BOX_DOTS_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_DOTS_BIG",JS_NewInt32(ctx,(int32_t)ICON_BOX_DOTS_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_CONCENTRIC",JS_NewInt32(ctx,(int32_t)ICON_BOX_CONCENTRIC));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BOX_GRID_BIG",JS_NewInt32(ctx,(int32_t)ICON_BOX_GRID_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_OK_TICK",JS_NewInt32(ctx,(int32_t)ICON_OK_TICK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CROSS",JS_NewInt32(ctx,(int32_t)ICON_CROSS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_LEFT",JS_NewInt32(ctx,(int32_t)ICON_ARROW_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_ARROW_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_DOWN",JS_NewInt32(ctx,(int32_t)ICON_ARROW_DOWN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_UP",JS_NewInt32(ctx,(int32_t)ICON_ARROW_UP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_LEFT_FILL",JS_NewInt32(ctx,(int32_t)ICON_ARROW_LEFT_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_RIGHT_FILL",JS_NewInt32(ctx,(int32_t)ICON_ARROW_RIGHT_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_DOWN_FILL",JS_NewInt32(ctx,(int32_t)ICON_ARROW_DOWN_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ARROW_UP_FILL",JS_NewInt32(ctx,(int32_t)ICON_ARROW_UP_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_AUDIO",JS_NewInt32(ctx,(int32_t)ICON_AUDIO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FX",JS_NewInt32(ctx,(int32_t)ICON_FX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WAVE",JS_NewInt32(ctx,(int32_t)ICON_WAVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WAVE_SINUS",JS_NewInt32(ctx,(int32_t)ICON_WAVE_SINUS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WAVE_SQUARE",JS_NewInt32(ctx,(int32_t)ICON_WAVE_SQUARE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WAVE_TRIANGULAR",JS_NewInt32(ctx,(int32_t)ICON_WAVE_TRIANGULAR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CROSS_SMALL",JS_NewInt32(ctx,(int32_t)ICON_CROSS_SMALL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_PREVIOUS",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_PREVIOUS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_PLAY_BACK",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_PLAY_BACK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_PLAY",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_PLAY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_PAUSE",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_PAUSE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_STOP",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_STOP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_NEXT",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_NEXT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_RECORD",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_RECORD));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MAGNET",JS_NewInt32(ctx,(int32_t)ICON_MAGNET));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LOCK_CLOSE",JS_NewInt32(ctx,(int32_t)ICON_LOCK_CLOSE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LOCK_OPEN",JS_NewInt32(ctx,(int32_t)ICON_LOCK_OPEN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CLOCK",JS_NewInt32(ctx,(int32_t)ICON_CLOCK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TOOLS",JS_NewInt32(ctx,(int32_t)ICON_TOOLS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_GEAR",JS_NewInt32(ctx,(int32_t)ICON_GEAR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_GEAR_BIG",JS_NewInt32(ctx,(int32_t)ICON_GEAR_BIG));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BIN",JS_NewInt32(ctx,(int32_t)ICON_BIN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HAND_POINTER",JS_NewInt32(ctx,(int32_t)ICON_HAND_POINTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LASER",JS_NewInt32(ctx,(int32_t)ICON_LASER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_COIN",JS_NewInt32(ctx,(int32_t)ICON_COIN));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EXPLOSION",JS_NewInt32(ctx,(int32_t)ICON_EXPLOSION));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_1UP",JS_NewInt32(ctx,(int32_t)ICON_1UP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER",JS_NewInt32(ctx,(int32_t)ICON_PLAYER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PLAYER_JUMP",JS_NewInt32(ctx,(int32_t)ICON_PLAYER_JUMP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_KEY",JS_NewInt32(ctx,(int32_t)ICON_KEY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_DEMON",JS_NewInt32(ctx,(int32_t)ICON_DEMON));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TEXT_POPUP",JS_NewInt32(ctx,(int32_t)ICON_TEXT_POPUP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_GEAR_EX",JS_NewInt32(ctx,(int32_t)ICON_GEAR_EX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CRACK",JS_NewInt32(ctx,(int32_t)ICON_CRACK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CRACK_POINTS",JS_NewInt32(ctx,(int32_t)ICON_CRACK_POINTS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_STAR",JS_NewInt32(ctx,(int32_t)ICON_STAR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_DOOR",JS_NewInt32(ctx,(int32_t)ICON_DOOR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_EXIT",JS_NewInt32(ctx,(int32_t)ICON_EXIT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MODE_2D",JS_NewInt32(ctx,(int32_t)ICON_MODE_2D));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MODE_3D",JS_NewInt32(ctx,(int32_t)ICON_MODE_3D));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE",JS_NewInt32(ctx,(int32_t)ICON_CUBE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_TOP",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_TOP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_LEFT",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_LEFT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_FRONT",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_FRONT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_BOTTOM",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_BOTTOM));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_RIGHT",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_RIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_BACK",JS_NewInt32(ctx,(int32_t)ICON_CUBE_FACE_BACK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CAMERA",JS_NewInt32(ctx,(int32_t)ICON_CAMERA));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SPECIAL",JS_NewInt32(ctx,(int32_t)ICON_SPECIAL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LINK_NET",JS_NewInt32(ctx,(int32_t)ICON_LINK_NET));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LINK_BOXES",JS_NewInt32(ctx,(int32_t)ICON_LINK_BOXES));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LINK_MULTI",JS_NewInt32(ctx,(int32_t)ICON_LINK_MULTI));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LINK",JS_NewInt32(ctx,(int32_t)ICON_LINK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LINK_BROKE",JS_NewInt32(ctx,(int32_t)ICON_LINK_BROKE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_TEXT_NOTES",JS_NewInt32(ctx,(int32_t)ICON_TEXT_NOTES));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_NOTEBOOK",JS_NewInt32(ctx,(int32_t)ICON_NOTEBOOK));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SUITCASE",JS_NewInt32(ctx,(int32_t)ICON_SUITCASE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SUITCASE_ZIP",JS_NewInt32(ctx,(int32_t)ICON_SUITCASE_ZIP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MAILBOX",JS_NewInt32(ctx,(int32_t)ICON_MAILBOX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MONITOR",JS_NewInt32(ctx,(int32_t)ICON_MONITOR));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PRINTER",JS_NewInt32(ctx,(int32_t)ICON_PRINTER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PHOTO_CAMERA",JS_NewInt32(ctx,(int32_t)ICON_PHOTO_CAMERA));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PHOTO_CAMERA_FLASH",JS_NewInt32(ctx,(int32_t)ICON_PHOTO_CAMERA_FLASH));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HOUSE",JS_NewInt32(ctx,(int32_t)ICON_HOUSE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HEART",JS_NewInt32(ctx,(int32_t)ICON_HEART));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CORNER",JS_NewInt32(ctx,(int32_t)ICON_CORNER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_VERTICAL_BARS",JS_NewInt32(ctx,(int32_t)ICON_VERTICAL_BARS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_VERTICAL_BARS_FILL",JS_NewInt32(ctx,(int32_t)ICON_VERTICAL_BARS_FILL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LIFE_BARS",JS_NewInt32(ctx,(int32_t)ICON_LIFE_BARS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_INFO",JS_NewInt32(ctx,(int32_t)ICON_INFO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CROSSLINE",JS_NewInt32(ctx,(int32_t)ICON_CROSSLINE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HELP",JS_NewInt32(ctx,(int32_t)ICON_HELP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_ALPHA",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_HOME",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_HOME));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LAYERS_VISIBLE",JS_NewInt32(ctx,(int32_t)ICON_LAYERS_VISIBLE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LAYERS",JS_NewInt32(ctx,(int32_t)ICON_LAYERS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WINDOW",JS_NewInt32(ctx,(int32_t)ICON_WINDOW));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HIDPI",JS_NewInt32(ctx,(int32_t)ICON_HIDPI));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILETYPE_BINARY",JS_NewInt32(ctx,(int32_t)ICON_FILETYPE_BINARY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HEX",JS_NewInt32(ctx,(int32_t)ICON_HEX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SHIELD",JS_NewInt32(ctx,(int32_t)ICON_SHIELD));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE_NEW",JS_NewInt32(ctx,(int32_t)ICON_FILE_NEW));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOLDER_ADD",JS_NewInt32(ctx,(int32_t)ICON_FOLDER_ADD));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ALARM",JS_NewInt32(ctx,(int32_t)ICON_ALARM));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CPU",JS_NewInt32(ctx,(int32_t)ICON_CPU));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_ROM",JS_NewInt32(ctx,(int32_t)ICON_ROM));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_STEP_OVER",JS_NewInt32(ctx,(int32_t)ICON_STEP_OVER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_STEP_INTO",JS_NewInt32(ctx,(int32_t)ICON_STEP_INTO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_STEP_OUT",JS_NewInt32(ctx,(int32_t)ICON_STEP_OUT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_RESTART",JS_NewInt32(ctx,(int32_t)ICON_RESTART));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BREAKPOINT_ON",JS_NewInt32(ctx,(int32_t)ICON_BREAKPOINT_ON));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BREAKPOINT_OFF",JS_NewInt32(ctx,(int32_t)ICON_BREAKPOINT_OFF));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_BURGER_MENU",JS_NewInt32(ctx,(int32_t)ICON_BURGER_MENU));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_CASE_SENSITIVE",JS_NewInt32(ctx,(int32_t)ICON_CASE_SENSITIVE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_REG_EXP",JS_NewInt32(ctx,(int32_t)ICON_REG_EXP));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FOLDER",JS_NewInt32(ctx,(int32_t)ICON_FOLDER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_FILE",JS_NewInt32(ctx,(int32_t)ICON_FILE));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SAND_TIMER",JS_NewInt32(ctx,(int32_t)ICON_SAND_TIMER));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_WARNING",JS_NewInt32(ctx,(int32_t)ICON_WARNING));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HELP_BOX",JS_NewInt32(ctx,(int32_t)ICON_HELP_BOX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_INFO_BOX",JS_NewInt32(ctx,(int32_t)ICON_INFO_BOX));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_PRIORITY",JS_NewInt32(ctx,(int32_t)ICON_PRIORITY));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LAYERS_ISO",JS_NewInt32(ctx,(int32_t)ICON_LAYERS_ISO));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LAYERS2",JS_NewInt32(ctx,(int32_t)ICON_LAYERS2));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MLAYERS",JS_NewInt32(ctx,(int32_t)ICON_MLAYERS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MAPS",JS_NewInt32(ctx,(int32_t)ICON_MAPS));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_HOT",JS_NewInt32(ctx,(int32_t)ICON_HOT));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_LABEL",JS_NewInt32(ctx,(int32_t)ICON_LABEL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_NAME_ID",JS_NewInt32(ctx,(int32_t)ICON_NAME_ID));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_SLICING",JS_NewInt32(ctx,(int32_t)ICON_SLICING));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_MANUAL_CONTROL",JS_NewInt32(ctx,(int32_t)ICON_MANUAL_CONTROL));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_COLLISION",JS_NewInt32(ctx,(int32_t)ICON_COLLISION));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_234",JS_NewInt32(ctx,(int32_t)ICON_234));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_235",JS_NewInt32(ctx,(int32_t)ICON_235));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_236",JS_NewInt32(ctx,(int32_t)ICON_236));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_237",JS_NewInt32(ctx,(int32_t)ICON_237));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_238",JS_NewInt32(ctx,(int32_t)ICON_238));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_239",JS_NewInt32(ctx,(int32_t)ICON_239));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_240",JS_NewInt32(ctx,(int32_t)ICON_240));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_241",JS_NewInt32(ctx,(int32_t)ICON_241));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_242",JS_NewInt32(ctx,(int32_t)ICON_242));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_243",JS_NewInt32(ctx,(int32_t)ICON_243));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_244",JS_NewInt32(ctx,(int32_t)ICON_244));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_245",JS_NewInt32(ctx,(int32_t)ICON_245));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_246",JS_NewInt32(ctx,(int32_t)ICON_246));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_247",JS_NewInt32(ctx,(int32_t)ICON_247));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_248",JS_NewInt32(ctx,(int32_t)ICON_248));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_249",JS_NewInt32(ctx,(int32_t)ICON_249));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_250",JS_NewInt32(ctx,(int32_t)ICON_250));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_251",JS_NewInt32(ctx,(int32_t)ICON_251));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_252",JS_NewInt32(ctx,(int32_t)ICON_252));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_253",JS_NewInt32(ctx,(int32_t)ICON_253));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_254",JS_NewInt32(ctx,(int32_t)ICON_254));
		JS_SetModuleExport(ctx,m,(const char *)"ICON_255",JS_NewInt32(ctx,(int32_t)ICON_255));
		JS_SetModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_MAJOR",JS_NewInt32(ctx,(int32_t)RAYGUI_VERSION_MAJOR));
		JS_SetModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_MINOR",JS_NewInt32(ctx,(int32_t)RAYGUI_VERSION_MINOR));
		JS_SetModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_PATCH",JS_NewInt32(ctx,(int32_t)RAYGUI_VERSION_PATCH));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLLBAR_LEFT_SIDE",JS_NewInt32(ctx,(int32_t)SCROLLBAR_LEFT_SIDE));
		JS_SetModuleExport(ctx,m,(const char *)"SCROLLBAR_RIGHT_SIDE",JS_NewInt32(ctx,(int32_t)SCROLLBAR_RIGHT_SIDE));
		return 0;
	}
	
	JSModuleDef * js_init_module_raygui(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_raygui_init);
		if(!m)return NULL;
		size_t listcount=countof(jsraygui_funcs);
		JS_AddModuleExportList(ctx,m,jsraygui_funcs,(int)listcount);
		JS_AddModuleExport(ctx,m,(const char *)"GuiStyleProp");
		JS_AddModuleExport(ctx,m,(const char *)"STATE_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"STATE_FOCUSED");
		JS_AddModuleExport(ctx,m,(const char *)"STATE_PRESSED");
		JS_AddModuleExport(ctx,m,(const char *)"STATE_DISABLED");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_CENTER");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_TOP");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_MIDDLE");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGN_BOTTOM");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_WRAP_NONE");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_WRAP_CHAR");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_WRAP_WORD");
		JS_AddModuleExport(ctx,m,(const char *)"DEFAULT");
		JS_AddModuleExport(ctx,m,(const char *)"LABEL");
		JS_AddModuleExport(ctx,m,(const char *)"BUTTON");
		JS_AddModuleExport(ctx,m,(const char *)"TOGGLE");
		JS_AddModuleExport(ctx,m,(const char *)"SLIDER");
		JS_AddModuleExport(ctx,m,(const char *)"PROGRESSBAR");
		JS_AddModuleExport(ctx,m,(const char *)"CHECKBOX");
		JS_AddModuleExport(ctx,m,(const char *)"COMBOBOX");
		JS_AddModuleExport(ctx,m,(const char *)"DROPDOWNBOX");
		JS_AddModuleExport(ctx,m,(const char *)"TEXTBOX");
		JS_AddModuleExport(ctx,m,(const char *)"VALUEBOX");
		JS_AddModuleExport(ctx,m,(const char *)"CONTROL11");
		JS_AddModuleExport(ctx,m,(const char *)"LISTVIEW");
		JS_AddModuleExport(ctx,m,(const char *)"COLORPICKER");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLLBAR");
		JS_AddModuleExport(ctx,m,(const char *)"STATUSBAR");
		JS_AddModuleExport(ctx,m,(const char *)"BORDER_COLOR_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"BASE_COLOR_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_COLOR_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"BORDER_COLOR_FOCUSED");
		JS_AddModuleExport(ctx,m,(const char *)"BASE_COLOR_FOCUSED");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_COLOR_FOCUSED");
		JS_AddModuleExport(ctx,m,(const char *)"BORDER_COLOR_PRESSED");
		JS_AddModuleExport(ctx,m,(const char *)"BASE_COLOR_PRESSED");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_COLOR_PRESSED");
		JS_AddModuleExport(ctx,m,(const char *)"BORDER_COLOR_DISABLED");
		JS_AddModuleExport(ctx,m,(const char *)"BASE_COLOR_DISABLED");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_COLOR_DISABLED");
		JS_AddModuleExport(ctx,m,(const char *)"BORDER_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGNMENT");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_SIZE");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"LINE_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"BACKGROUND_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_LINE_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_ALIGNMENT_VERTICAL");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_WRAP_MODE");
		JS_AddModuleExport(ctx,m,(const char *)"GROUP_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"SLIDER_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"SLIDER_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"PROGRESS_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"ARROWS_SIZE");
		JS_AddModuleExport(ctx,m,(const char *)"ARROWS_VISIBLE");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLL_SLIDER_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLL_SLIDER_SIZE");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLL_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLL_SPEED");
		JS_AddModuleExport(ctx,m,(const char *)"CHECK_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"COMBO_BUTTON_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"COMBO_BUTTON_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"ARROW_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"DROPDOWN_ITEMS_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"DROPDOWN_ARROW_HIDDEN");
		JS_AddModuleExport(ctx,m,(const char *)"DROPDOWN_ROLL_UP");
		JS_AddModuleExport(ctx,m,(const char *)"TEXT_READONLY");
		JS_AddModuleExport(ctx,m,(const char *)"SPINNER_BUTTON_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"SPINNER_BUTTON_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"LIST_ITEMS_HEIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"LIST_ITEMS_SPACING");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLLBAR_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLLBAR_SIDE");
		JS_AddModuleExport(ctx,m,(const char *)"LIST_ITEMS_BORDER_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"LIST_ITEMS_BORDER_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"COLOR_SELECTOR_SIZE");
		JS_AddModuleExport(ctx,m,(const char *)"HUEBAR_WIDTH");
		JS_AddModuleExport(ctx,m,(const char *)"HUEBAR_PADDING");
		JS_AddModuleExport(ctx,m,(const char *)"HUEBAR_SELECTOR_HEIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"HUEBAR_SELECTOR_OVERFLOW");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_NONE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOLDER_FILE_OPEN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_SAVE_CLASSIC");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOLDER_OPEN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOLDER_SAVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_OPEN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_SAVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_EXPORT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_ADD");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_DELETE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_TEXT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_AUDIO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_IMAGE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_PLAY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_VIDEO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_INFO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_COPY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_CUT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_PASTE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_HAND");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_POINTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_CLASSIC");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PENCIL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PENCIL_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BRUSH_CLASSIC");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BRUSH_PAINTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WATER_DROP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_COLOR_PICKER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_RUBBER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_COLOR_BUCKET");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TEXT_T");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TEXT_A");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SCALE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_RESIZE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILTER_POINT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILTER_BILINEAR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CROP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CROP_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SQUARE_TOGGLE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SYMMETRY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SYMMETRY_HORIZONTAL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SYMMETRY_VERTICAL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LENS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LENS_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EYE_ON");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EYE_OFF");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILTER_TOP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_POINT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_MOVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_MOVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_UNDO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REDO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REREDO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MUTATE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ROTATE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REPEAT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SHUFFLE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EMPTYBOX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_SMALL_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_BIG_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TARGET_MOVE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_MOVE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_RIGHT_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CURSOR_SCALE_LEFT_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_UNDO_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REDO_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REREDO_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MUTATE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ROTATE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REPEAT_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SHUFFLE_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EMPTYBOX_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_TOP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_TOP_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_BOTTOM_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_TOP_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_CENTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_CIRCLE_MASK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_POT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ALPHA_MULTIPLY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ALPHA_CLEAR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_DITHERING");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MIPMAPS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_GRID");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_GRID");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_CORNERS_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_CORNERS_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOUR_BOXES");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_GRID_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_MULTISIZE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ZOOM_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ZOOM_MEDIUM");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ZOOM_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ZOOM_ALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ZOOM_CENTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_DOTS_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_DOTS_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_CONCENTRIC");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BOX_GRID_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_OK_TICK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CROSS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_DOWN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_UP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_LEFT_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_RIGHT_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_DOWN_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ARROW_UP_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_AUDIO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WAVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WAVE_SINUS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WAVE_SQUARE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WAVE_TRIANGULAR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CROSS_SMALL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_PREVIOUS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_PLAY_BACK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_PLAY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_PAUSE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_STOP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_NEXT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_RECORD");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MAGNET");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LOCK_CLOSE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LOCK_OPEN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CLOCK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TOOLS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_GEAR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_GEAR_BIG");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BIN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HAND_POINTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LASER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_COIN");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EXPLOSION");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_1UP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PLAYER_JUMP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_KEY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_DEMON");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TEXT_POPUP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_GEAR_EX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CRACK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CRACK_POINTS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_STAR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_DOOR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_EXIT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MODE_2D");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MODE_3D");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_TOP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_LEFT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_FRONT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_BOTTOM");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_RIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CUBE_FACE_BACK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CAMERA");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SPECIAL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LINK_NET");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LINK_BOXES");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LINK_MULTI");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LINK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LINK_BROKE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_TEXT_NOTES");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_NOTEBOOK");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SUITCASE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SUITCASE_ZIP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MAILBOX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MONITOR");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PRINTER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PHOTO_CAMERA");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PHOTO_CAMERA_FLASH");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HOUSE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HEART");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CORNER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_VERTICAL_BARS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_VERTICAL_BARS_FILL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LIFE_BARS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_INFO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CROSSLINE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HELP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_HOME");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LAYERS_VISIBLE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LAYERS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WINDOW");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HIDPI");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILETYPE_BINARY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HEX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SHIELD");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE_NEW");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOLDER_ADD");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ALARM");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CPU");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_ROM");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_STEP_OVER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_STEP_INTO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_STEP_OUT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_RESTART");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BREAKPOINT_ON");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BREAKPOINT_OFF");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_BURGER_MENU");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_CASE_SENSITIVE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_REG_EXP");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FOLDER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_FILE");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SAND_TIMER");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_WARNING");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HELP_BOX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_INFO_BOX");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_PRIORITY");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LAYERS_ISO");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LAYERS2");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MLAYERS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MAPS");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_HOT");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_LABEL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_NAME_ID");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_SLICING");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_MANUAL_CONTROL");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_COLLISION");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_234");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_235");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_236");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_237");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_238");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_239");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_240");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_241");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_242");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_243");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_244");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_245");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_246");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_247");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_248");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_249");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_250");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_251");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_252");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_253");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_254");
		JS_AddModuleExport(ctx,m,(const char *)"ICON_255");
		JS_AddModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_MAJOR");
		JS_AddModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_MINOR");
		JS_AddModuleExport(ctx,m,(const char *)"RAYGUI_VERSION_PATCH");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLLBAR_LEFT_SIDE");
		JS_AddModuleExport(ctx,m,(const char *)"SCROLLBAR_RIGHT_SIDE");
		return m;
	}

#endif //JS_raygui_GUARD