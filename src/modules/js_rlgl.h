#ifndef JS_js_rlgl_GUARD
	#define JS_js_rlgl_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <rayjs_generated.h>
	#include <raylib.h>
	#include <rlgl.h>
	
	static void js_rlVertexBuffer_finalizer(JSRuntime * rt,JSValue val){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque(val,js_rlVertexBuffer_class_id);
		if(ptr){
			js_free_rt(rt,(void *)ptr);
		}
	}
	
	static JSValue js_rlVertexBuffer_get_elementCount(JSContext * ctx,JSValue this_val){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		int elementCount=ptr[0].elementCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)elementCount));
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_elementCount(JSContext * ctx,JSValue this_val,JSValue v){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].elementCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_vertices_values(JSContext * ctx,void * ptr,int property,bool as_sting){
		JSValue ret;
		ret =JS_NewArray(ctx);
		int i;
		for(i=0;i<((rlVertexBuffer *)ptr)[0].elementCount*3*4;i++){
			JSValue js_ret=JS_NewFloat64(ctx,((double)((rlVertexBuffer *)ptr)[0].vertices[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_vertices_keys(JSContext * ctx,void * ptr,JSPropertyEnum * * keys){
		int length=(int)((rlVertexBuffer *)ptr)[0].elementCount*3*4;
		keys[0] =(JSPropertyEnum *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		int i;
		for(i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_vertices_get(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((rlVertexBuffer *)ptr)[0].elementCount*3*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<((rlVertexBuffer *)ptr)[0].elementCount*3*4){
				float src=((rlVertexBuffer *)ptr)[0].vertices[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_vertices_set(JSContext * ctx,void * ptr,JSValue set_to,int property,bool as_sting){
		if(as_sting==true){
			return false;
		}else{
			double double_ret;
			int err_ret=JS_ToFloat64(ctx,&double_ret,set_to);
			if(err_ret<0){
				JS_ThrowTypeError(ctx,(const char *)"set_to is not numeric");
				return -1;
			}
			float ret=((float)double_ret);
			((rlVertexBuffer *)ptr)[0].vertices[property] =ret;
		}
		return true;
	}
	
	static int js_rlVertexBuffer_vertices_has(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<((rlVertexBuffer *)ptr)[0].elementCount*3*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlVertexBuffer_get_vertices(JSContext * ctx,JSValue this_val){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = this_val,.opaque = ptr,.values = js_rlVertexBuffer_vertices_values,.keys = js_rlVertexBuffer_vertices_keys,.get = js_rlVertexBuffer_vertices_get,.set = js_rlVertexBuffer_vertices_set,.has = js_rlVertexBuffer_vertices_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_vertices(JSContext * ctx,JSValue this_val,JSValue v){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		float * value;
		bool freesrc_value=(bool)false;
		JSValue da_value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(v);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(v,js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			v =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}else if(JS_IsArray(v)==1){
			if(JS_GetLength(ctx,v,&size_value)==-1){
				return JS_EXCEPTION;
			}
			value =(float *)jsc_malloc(ctx,size_value*sizeof(float));
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,v,(uint32_t)i);
				double double_valuei;
				int err_valuei=JS_ToFloat64(ctx,&double_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((float)double_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else if(JS_IsArrayBuffer(v)==1){
			float * js_value=(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,v);
			value =(float *)jsc_malloc(ctx,size_value*sizeof(float *));
			memcpy((void *)value,(const void *)js_value,(size_t)size_value);
		}else{
			JSClassID classid_value=JS_GetClassID(v);
			if(classid_value==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_value;
				da_value =JS_GetTypedArrayBuffer(ctx,v,&offset_value,(size_t *)&size_value,NULL);
				float * js_value=(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,da_value);
				js_value +=offset_value;
				size_value -=offset_value;
				value =(float *)jsc_malloc(ctx,size_value*sizeof(float *));
				memcpy((void *)value,(const void *)js_value,(size_t)size_value);
				JS_FreeValuePtr(ctx,&da_value);
			}else{
				if(freesrc_value){
					JS_FreeValue(ctx,v);
				}
				JS_ThrowTypeError(ctx,(const char *)"v does not match type float *");
				return JS_EXCEPTION;
			}
		}
		if(ptr[0].vertices!=NULL){
			jsc_free(ctx,(void *)ptr[0].vertices);
		}
		ptr[0].vertices=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_texcoords_values(JSContext * ctx,void * ptr,int property,bool as_sting){
		JSValue ret;
		ret =JS_NewArray(ctx);
		int i;
		for(i=0;i<((rlVertexBuffer *)ptr)[0].elementCount*2*4;i++){
			JSValue js_ret=JS_NewFloat64(ctx,((double)((rlVertexBuffer *)ptr)[0].texcoords[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_texcoords_keys(JSContext * ctx,void * ptr,JSPropertyEnum * * keys){
		int length=(int)((rlVertexBuffer *)ptr)[0].elementCount*2*4;
		keys[0] =(JSPropertyEnum *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		int i;
		for(i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_texcoords_get(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((rlVertexBuffer *)ptr)[0].elementCount*2*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<((rlVertexBuffer *)ptr)[0].elementCount*2*4){
				float src=((rlVertexBuffer *)ptr)[0].texcoords[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_texcoords_set(JSContext * ctx,void * ptr,JSValue set_to,int property,bool as_sting){
		if(as_sting==true){
			return false;
		}else{
			double double_ret;
			int err_ret=JS_ToFloat64(ctx,&double_ret,set_to);
			if(err_ret<0){
				JS_ThrowTypeError(ctx,(const char *)"set_to is not numeric");
				return -1;
			}
			float ret=((float)double_ret);
			((rlVertexBuffer *)ptr)[0].texcoords[property] =ret;
		}
		return true;
	}
	
	static int js_rlVertexBuffer_texcoords_has(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<((rlVertexBuffer *)ptr)[0].elementCount*2*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlVertexBuffer_get_texcoords(JSContext * ctx,JSValue this_val){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = this_val,.opaque = ptr,.values = js_rlVertexBuffer_texcoords_values,.keys = js_rlVertexBuffer_texcoords_keys,.get = js_rlVertexBuffer_texcoords_get,.set = js_rlVertexBuffer_texcoords_set,.has = js_rlVertexBuffer_texcoords_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_texcoords(JSContext * ctx,JSValue this_val,JSValue v){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		float * value;
		bool freesrc_value=(bool)false;
		JSValue da_value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(v);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(v,js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			v =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}else if(JS_IsArray(v)==1){
			if(JS_GetLength(ctx,v,&size_value)==-1){
				return JS_EXCEPTION;
			}
			value =(float *)jsc_malloc(ctx,size_value*sizeof(float));
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,v,(uint32_t)i);
				double double_valuei;
				int err_valuei=JS_ToFloat64(ctx,&double_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((float)double_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else if(JS_IsArrayBuffer(v)==1){
			float * js_value=(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,v);
			value =(float *)jsc_malloc(ctx,size_value*sizeof(float *));
			memcpy((void *)value,(const void *)js_value,(size_t)size_value);
		}else{
			JSClassID classid_value=JS_GetClassID(v);
			if(classid_value==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_value;
				da_value =JS_GetTypedArrayBuffer(ctx,v,&offset_value,(size_t *)&size_value,NULL);
				float * js_value=(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,da_value);
				js_value +=offset_value;
				size_value -=offset_value;
				value =(float *)jsc_malloc(ctx,size_value*sizeof(float *));
				memcpy((void *)value,(const void *)js_value,(size_t)size_value);
				JS_FreeValuePtr(ctx,&da_value);
			}else{
				if(freesrc_value){
					JS_FreeValue(ctx,v);
				}
				JS_ThrowTypeError(ctx,(const char *)"v does not match type float *");
				return JS_EXCEPTION;
			}
		}
		if(ptr[0].texcoords!=NULL){
			jsc_free(ctx,(void *)ptr[0].texcoords);
		}
		ptr[0].texcoords=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_normals_values(JSContext * ctx,void * ptr,int property,bool as_sting){
		JSValue ret;
		ret =JS_NewArray(ctx);
		int i;
		for(i=0;i<((rlVertexBuffer *)ptr)[0].elementCount*3*4;i++){
			JSValue js_ret=JS_NewFloat64(ctx,((double)((rlVertexBuffer *)ptr)[0].normals[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_normals_keys(JSContext * ctx,void * ptr,JSPropertyEnum * * keys){
		int length=(int)((rlVertexBuffer *)ptr)[0].elementCount*3*4;
		keys[0] =(JSPropertyEnum *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		int i;
		for(i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_normals_get(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((rlVertexBuffer *)ptr)[0].elementCount*3*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<((rlVertexBuffer *)ptr)[0].elementCount*3*4){
				float src=((rlVertexBuffer *)ptr)[0].normals[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_normals_set(JSContext * ctx,void * ptr,JSValue set_to,int property,bool as_sting){
		if(as_sting==true){
			return false;
		}else{
			double double_ret;
			int err_ret=JS_ToFloat64(ctx,&double_ret,set_to);
			if(err_ret<0){
				JS_ThrowTypeError(ctx,(const char *)"set_to is not numeric");
				return -1;
			}
			float ret=((float)double_ret);
			((rlVertexBuffer *)ptr)[0].normals[property] =ret;
		}
		return true;
	}
	
	static int js_rlVertexBuffer_normals_has(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<((rlVertexBuffer *)ptr)[0].elementCount*3*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlVertexBuffer_get_normals(JSContext * ctx,JSValue this_val){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = this_val,.opaque = ptr,.values = js_rlVertexBuffer_normals_values,.keys = js_rlVertexBuffer_normals_keys,.get = js_rlVertexBuffer_normals_get,.set = js_rlVertexBuffer_normals_set,.has = js_rlVertexBuffer_normals_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_normals(JSContext * ctx,JSValue this_val,JSValue v){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		float * value;
		bool freesrc_value=(bool)false;
		JSValue da_value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(v);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(v,js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			v =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}else if(JS_IsArray(v)==1){
			if(JS_GetLength(ctx,v,&size_value)==-1){
				return JS_EXCEPTION;
			}
			value =(float *)jsc_malloc(ctx,size_value*sizeof(float));
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,v,(uint32_t)i);
				double double_valuei;
				int err_valuei=JS_ToFloat64(ctx,&double_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((float)double_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else if(JS_IsArrayBuffer(v)==1){
			float * js_value=(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,v);
			value =(float *)jsc_malloc(ctx,size_value*sizeof(float *));
			memcpy((void *)value,(const void *)js_value,(size_t)size_value);
		}else{
			JSClassID classid_value=JS_GetClassID(v);
			if(classid_value==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_value;
				da_value =JS_GetTypedArrayBuffer(ctx,v,&offset_value,(size_t *)&size_value,NULL);
				float * js_value=(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,da_value);
				js_value +=offset_value;
				size_value -=offset_value;
				value =(float *)jsc_malloc(ctx,size_value*sizeof(float *));
				memcpy((void *)value,(const void *)js_value,(size_t)size_value);
				JS_FreeValuePtr(ctx,&da_value);
			}else{
				if(freesrc_value){
					JS_FreeValue(ctx,v);
				}
				JS_ThrowTypeError(ctx,(const char *)"v does not match type float *");
				return JS_EXCEPTION;
			}
		}
		if(ptr[0].normals!=NULL){
			jsc_free(ctx,(void *)ptr[0].normals);
		}
		ptr[0].normals=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_colors_values(JSContext * ctx,void * ptr,int property,bool as_sting){
		JSValue ret;
		ret =JS_NewArray(ctx);
		int i;
		for(i=0;i<((rlVertexBuffer *)ptr)[0].elementCount*4*4;i++){
			JSValue js_ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)((rlVertexBuffer *)ptr)[0].colors[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_colors_keys(JSContext * ctx,void * ptr,JSPropertyEnum * * keys){
		int length=(int)((rlVertexBuffer *)ptr)[0].elementCount*4*4;
		keys[0] =(JSPropertyEnum *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		int i;
		for(i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_colors_get(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((rlVertexBuffer *)ptr)[0].elementCount*4*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<((rlVertexBuffer *)ptr)[0].elementCount*4*4){
				unsigned char src=((rlVertexBuffer *)ptr)[0].colors[property];
				JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_colors_set(JSContext * ctx,void * ptr,JSValue set_to,int property,bool as_sting){
		if(as_sting==true){
			return false;
		}else{
			uint32_t long_ret;
			int err_ret=JS_ToUint32(ctx,&long_ret,set_to);
			if(err_ret<0){
				JS_ThrowTypeError(ctx,(const char *)"set_to is not numeric");
				return -1;
			}
			unsigned char ret=((unsigned char)long_ret);
			((rlVertexBuffer *)ptr)[0].colors[property] =ret;
		}
		return true;
	}
	
	static int js_rlVertexBuffer_colors_has(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<((rlVertexBuffer *)ptr)[0].elementCount*4*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlVertexBuffer_get_colors(JSContext * ctx,JSValue this_val){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = this_val,.opaque = ptr,.values = js_rlVertexBuffer_colors_values,.keys = js_rlVertexBuffer_colors_keys,.get = js_rlVertexBuffer_colors_get,.set = js_rlVertexBuffer_colors_set,.has = js_rlVertexBuffer_colors_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_colors(JSContext * ctx,JSValue this_val,JSValue v){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		unsigned char * value;
		bool freesrc_value=(bool)false;
		JSValue da_value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(v);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(v,js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			v =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}else if(JS_IsArray(v)==1){
			if(JS_GetLength(ctx,v,&size_value)==-1){
				return JS_EXCEPTION;
			}
			value =(unsigned char *)jsc_malloc(ctx,size_value*sizeof(unsigned char));
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,v,(uint32_t)i);
				uint32_t long_valuei;
				int err_valuei=JS_ToUint32(ctx,&long_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((unsigned char)long_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else if(JS_IsArrayBuffer(v)==1){
			unsigned char * js_value=(unsigned char *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,v);
			value =(unsigned char *)jsc_malloc(ctx,size_value*sizeof(unsigned char *));
			memcpy((void *)value,(const void *)js_value,(size_t)size_value);
		}else{
			JSClassID classid_value=JS_GetClassID(v);
			if(classid_value==JS_CLASS_UINT8_ARRAY||classid_value==JS_CLASS_UINT8C_ARRAY){
				size_t offset_value;
				da_value =JS_GetTypedArrayBuffer(ctx,v,&offset_value,(size_t *)&size_value,NULL);
				unsigned char * js_value=(unsigned char *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,da_value);
				js_value +=offset_value;
				size_value -=offset_value;
				value =(unsigned char *)jsc_malloc(ctx,size_value*sizeof(unsigned char *));
				memcpy((void *)value,(const void *)js_value,(size_t)size_value);
				JS_FreeValuePtr(ctx,&da_value);
			}else{
				if(freesrc_value){
					JS_FreeValue(ctx,v);
				}
				JS_ThrowTypeError(ctx,(const char *)"v does not match type unsigned char *");
				return JS_EXCEPTION;
			}
		}
		if(ptr[0].colors!=NULL){
			jsc_free(ctx,(void *)ptr[0].colors);
		}
		ptr[0].colors=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_indices_values(JSContext * ctx,void * ptr,int property,bool as_sting){
		JSValue ret;
		ret =JS_NewArray(ctx);
		int i;
		for(i=0;i<((rlVertexBuffer *)ptr)[0].elementCount*6;i++){
			JSValue js_ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)((rlVertexBuffer *)ptr)[0].indices[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_indices_keys(JSContext * ctx,void * ptr,JSPropertyEnum * * keys){
		int length=(int)((rlVertexBuffer *)ptr)[0].elementCount*6;
		keys[0] =(JSPropertyEnum *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		int i;
		for(i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_indices_get(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((rlVertexBuffer *)ptr)[0].elementCount*((long)6));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<((rlVertexBuffer *)ptr)[0].elementCount*6){
				unsigned int src=((rlVertexBuffer *)ptr)[0].indices[property];
				JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_indices_set(JSContext * ctx,void * ptr,JSValue set_to,int property,bool as_sting){
		if(as_sting==true){
			return false;
		}else{
			uint32_t long_ret;
			int err_ret=JS_ToUint32(ctx,&long_ret,set_to);
			if(err_ret<0){
				JS_ThrowTypeError(ctx,(const char *)"set_to is not numeric");
				return -1;
			}
			unsigned int ret=((unsigned int)long_ret);
			((rlVertexBuffer *)ptr)[0].indices[property] =ret;
		}
		return true;
	}
	
	static int js_rlVertexBuffer_indices_has(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<((rlVertexBuffer *)ptr)[0].elementCount*6){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlVertexBuffer_get_indices(JSContext * ctx,JSValue this_val){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = this_val,.opaque = ptr,.values = js_rlVertexBuffer_indices_values,.keys = js_rlVertexBuffer_indices_keys,.get = js_rlVertexBuffer_indices_get,.set = js_rlVertexBuffer_indices_set,.has = js_rlVertexBuffer_indices_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_indices(JSContext * ctx,JSValue this_val,JSValue v){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		unsigned int * value;
		bool freesrc_value=(bool)false;
		JSValue da_value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(v);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(v,js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			v =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}else if(JS_IsArray(v)==1){
			if(JS_GetLength(ctx,v,&size_value)==-1){
				return JS_EXCEPTION;
			}
			value =(unsigned int *)jsc_malloc(ctx,size_value*sizeof(unsigned int));
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,v,(uint32_t)i);
				uint32_t long_valuei;
				int err_valuei=JS_ToUint32(ctx,&long_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((unsigned int)long_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else if(JS_IsArrayBuffer(v)==1){
			unsigned int * js_value=(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,v);
			value =(unsigned int *)jsc_malloc(ctx,size_value*sizeof(unsigned int *));
			memcpy((void *)value,(const void *)js_value,(size_t)size_value);
		}else{
			JSClassID classid_value=JS_GetClassID(v);
			if(classid_value==JS_CLASS_UINT16_ARRAY){
				size_t offset_value;
				da_value =JS_GetTypedArrayBuffer(ctx,v,&offset_value,(size_t *)&size_value,NULL);
				unsigned int * js_value=(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,da_value);
				js_value +=offset_value;
				size_value -=offset_value;
				value =(unsigned int *)jsc_malloc(ctx,size_value*sizeof(unsigned int *));
				memcpy((void *)value,(const void *)js_value,(size_t)size_value);
				JS_FreeValuePtr(ctx,&da_value);
			}else{
				if(freesrc_value){
					JS_FreeValue(ctx,v);
				}
				JS_ThrowTypeError(ctx,(const char *)"v does not match type unsigned int *");
				return JS_EXCEPTION;
			}
		}
		if(ptr[0].indices!=NULL){
			jsc_free(ctx,(void *)ptr[0].indices);
		}
		ptr[0].indices=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_get_vaoId(JSContext * ctx,JSValue this_val){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		unsigned int vaoId=ptr[0].vaoId;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)vaoId));
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_vaoId(JSContext * ctx,JSValue this_val,JSValue v){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		uint32_t long_value;
		int err_value=JS_ToUint32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int value=((unsigned int)long_value);
		ptr[0].vaoId=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_vboId_values(JSContext * ctx,void * ptr,int property,bool as_sting){
		JSValue ret;
		ret =JS_NewArray(ctx);
		int i;
		for(i=0;i<5;i++){
			JSValue js_ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)((rlVertexBuffer *)ptr)[0].vboId[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_vboId_keys(JSContext * ctx,void * ptr,JSPropertyEnum * * keys){
		int length=(int)5;
		keys[0] =(JSPropertyEnum *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		int i;
		for(i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_vboId_get(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)5));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<5){
				unsigned int src=((rlVertexBuffer *)ptr)[0].vboId[property];
				JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_vboId_set(JSContext * ctx,void * ptr,JSValue set_to,int property,bool as_sting){
		if(as_sting==true){
			return false;
		}else{
			uint32_t long_ret;
			int err_ret=JS_ToUint32(ctx,&long_ret,set_to);
			if(err_ret<0){
				JS_ThrowTypeError(ctx,(const char *)"set_to is not numeric");
				return -1;
			}
			unsigned int ret=((unsigned int)long_ret);
			((rlVertexBuffer *)ptr)[0].vboId[property] =ret;
		}
		return true;
	}
	
	static int js_rlVertexBuffer_vboId_has(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<5){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlVertexBuffer_get_vboId(JSContext * ctx,JSValue this_val){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = this_val,.opaque = ptr,.values = js_rlVertexBuffer_vboId_values,.keys = js_rlVertexBuffer_vboId_keys,.get = js_rlVertexBuffer_vboId_get,.set = js_rlVertexBuffer_vboId_set,.has = js_rlVertexBuffer_vboId_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_vboId(JSContext * ctx,JSValue this_val,JSValue v){
		rlVertexBuffer * ptr=(rlVertexBuffer *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		unsigned int * value;
		bool freesrc_value=(bool)false;
		JSValue da_value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(v);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(v,js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			v =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}else if(JS_IsArray(v)==1){
			value =(unsigned int *)jsc_malloc(ctx,5*sizeof(unsigned int));
			int i;
			for(i=0;i<5;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,v,(uint32_t)i);
				uint32_t long_valuei;
				int err_valuei=JS_ToUint32(ctx,&long_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((unsigned int)long_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else if(JS_IsArrayBuffer(v)==1){
			unsigned int * js_value=(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,v);
			value =(unsigned int *)jsc_malloc(ctx,size_value*sizeof(unsigned int *));
			memcpy((void *)value,(const void *)js_value,(size_t)size_value);
		}else{
			JSClassID classid_value=JS_GetClassID(v);
			if(classid_value==JS_CLASS_UINT16_ARRAY){
				size_t offset_value;
				da_value =JS_GetTypedArrayBuffer(ctx,v,&offset_value,(size_t *)&size_value,NULL);
				unsigned int * js_value=(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,da_value);
				js_value +=offset_value;
				size_value -=offset_value;
				value =(unsigned int *)jsc_malloc(ctx,size_value*sizeof(unsigned int *));
				memcpy((void *)value,(const void *)js_value,(size_t)size_value);
				JS_FreeValuePtr(ctx,&da_value);
			}else{
				if(freesrc_value){
					JS_FreeValue(ctx,v);
				}
				JS_ThrowTypeError(ctx,(const char *)"v does not match type unsigned int *");
				return JS_EXCEPTION;
			}
		}
		memcpy((void *)ptr[0].vboId,(const void *)value,5*sizeof(unsigned int));
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_rlVertexBuffer_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","rlVertexBuffer", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("elementCount",js_rlVertexBuffer_get_elementCount,js_rlVertexBuffer_set_elementCount),
		JS_CGETSET_DEF("vertices",js_rlVertexBuffer_get_vertices,js_rlVertexBuffer_set_vertices),
		JS_CGETSET_DEF("texcoords",js_rlVertexBuffer_get_texcoords,js_rlVertexBuffer_set_texcoords),
		JS_CGETSET_DEF("normals",js_rlVertexBuffer_get_normals,js_rlVertexBuffer_set_normals),
		JS_CGETSET_DEF("colors",js_rlVertexBuffer_get_colors,js_rlVertexBuffer_set_colors),
		JS_CGETSET_DEF("indices",js_rlVertexBuffer_get_indices,js_rlVertexBuffer_set_indices),
		JS_CGETSET_DEF("vaoId",js_rlVertexBuffer_get_vaoId,js_rlVertexBuffer_set_vaoId),
		JS_CGETSET_DEF("vboId",js_rlVertexBuffer_get_vboId,js_rlVertexBuffer_set_vboId)
	};
	
	static int js_declare_rlVertexBuffer(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_rlVertexBuffer_class_id);
		JSClassDef js_rlVertexBuffer_def={ .class_name = "rlVertexBuffer", .finalizer = js_rlVertexBuffer_finalizer };
		JS_NewClass(rt,js_rlVertexBuffer_class_id,(const JSClassDef *)&js_rlVertexBuffer_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_rlVertexBuffer_proto_funcs,(int)countof(js_rlVertexBuffer_proto_funcs));
		JS_SetClassProto(ctx,js_rlVertexBuffer_class_id,proto);
		return 0;
	}
	
	static void js_rlDrawCall_finalizer(JSRuntime * rt,JSValue val){
		rlDrawCall * ptr=(rlDrawCall *)JS_GetOpaque(val,js_rlDrawCall_class_id);
		if(ptr){
			js_free_rt(rt,(void *)ptr);
		}
	}
	
	static JSValue js_rlDrawCall_get_mode(JSContext * ctx,JSValue this_val){
		rlDrawCall * ptr=(rlDrawCall *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		int mode=ptr[0].mode;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)mode));
		return ret;
	}
	
	static JSValue js_rlDrawCall_set_mode(JSContext * ctx,JSValue this_val,JSValue v){
		rlDrawCall * ptr=(rlDrawCall *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].mode=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawCall_get_vertexCount(JSContext * ctx,JSValue this_val){
		rlDrawCall * ptr=(rlDrawCall *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		int vertexCount=ptr[0].vertexCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)vertexCount));
		return ret;
	}
	
	static JSValue js_rlDrawCall_set_vertexCount(JSContext * ctx,JSValue this_val,JSValue v){
		rlDrawCall * ptr=(rlDrawCall *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].vertexCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawCall_get_vertexAlignment(JSContext * ctx,JSValue this_val){
		rlDrawCall * ptr=(rlDrawCall *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		int vertexAlignment=ptr[0].vertexAlignment;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)vertexAlignment));
		return ret;
	}
	
	static JSValue js_rlDrawCall_set_vertexAlignment(JSContext * ctx,JSValue this_val,JSValue v){
		rlDrawCall * ptr=(rlDrawCall *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].vertexAlignment=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawCall_get_textureId(JSContext * ctx,JSValue this_val){
		rlDrawCall * ptr=(rlDrawCall *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		unsigned int textureId=ptr[0].textureId;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)textureId));
		return ret;
	}
	
	static JSValue js_rlDrawCall_set_textureId(JSContext * ctx,JSValue this_val,JSValue v){
		rlDrawCall * ptr=(rlDrawCall *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		uint32_t long_value;
		int err_value=JS_ToUint32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int value=((unsigned int)long_value);
		ptr[0].textureId=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_rlDrawCall_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","rlDrawCall", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("mode",js_rlDrawCall_get_mode,js_rlDrawCall_set_mode),
		JS_CGETSET_DEF("vertexCount",js_rlDrawCall_get_vertexCount,js_rlDrawCall_set_vertexCount),
		JS_CGETSET_DEF("vertexAlignment",js_rlDrawCall_get_vertexAlignment,js_rlDrawCall_set_vertexAlignment),
		JS_CGETSET_DEF("textureId",js_rlDrawCall_get_textureId,js_rlDrawCall_set_textureId)
	};
	
	static int js_declare_rlDrawCall(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_rlDrawCall_class_id);
		JSClassDef js_rlDrawCall_def={ .class_name = "rlDrawCall", .finalizer = js_rlDrawCall_finalizer };
		JS_NewClass(rt,js_rlDrawCall_class_id,(const JSClassDef *)&js_rlDrawCall_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_rlDrawCall_proto_funcs,(int)countof(js_rlDrawCall_proto_funcs));
		JS_SetClassProto(ctx,js_rlDrawCall_class_id,proto);
		return 0;
	}
	
	static void js_rlRenderBatch_finalizer(JSRuntime * rt,JSValue val){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque(val,js_rlRenderBatch_class_id);
		if(ptr){
			js_free_rt(rt,(void *)ptr);
		}
	}
	
	static JSValue js_rlRenderBatch_get_bufferCount(JSContext * ctx,JSValue this_val){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		int bufferCount=ptr[0].bufferCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)bufferCount));
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_bufferCount(JSContext * ctx,JSValue this_val,JSValue v){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].bufferCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRenderBatch_get_currentBuffer(JSContext * ctx,JSValue this_val){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		int currentBuffer=ptr[0].currentBuffer;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)currentBuffer));
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_currentBuffer(JSContext * ctx,JSValue this_val,JSValue v){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].currentBuffer=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRenderBatch_vertexBuffer_values(JSContext * ctx,void * ptr,int property,bool as_sting){
		JSValue ret;
		ret =JS_NewArray(ctx);
		int i;
		for(i=0;i<((rlRenderBatch *)ptr)[0].bufferCount;i++){
			rlVertexBuffer * ptr_js_ret=(rlVertexBuffer *)js_malloc(ctx,sizeof(rlVertexBuffer));
			ptr_js_ret[0]=((rlRenderBatch *)ptr)[0].vertexBuffer[i];
			JSValue js_ret=JS_NewObjectClass(ctx,(int)js_rlVertexBuffer_class_id);
			JS_SetOpaque(js_ret,(void *)ptr_js_ret);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlRenderBatch_vertexBuffer_keys(JSContext * ctx,void * ptr,JSPropertyEnum * * keys){
		int length=((rlRenderBatch *)ptr)[0].bufferCount;
		keys[0] =(JSPropertyEnum *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		int i;
		for(i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlRenderBatch_vertexBuffer_get(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)((rlRenderBatch *)ptr)[0].bufferCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<((rlRenderBatch *)ptr)[0].bufferCount){
				rlVertexBuffer src=((rlRenderBatch *)ptr)[0].vertexBuffer[property];
				rlVertexBuffer * ptr_ret=(rlVertexBuffer *)js_malloc(ctx,sizeof(rlVertexBuffer));
				ptr_ret[0]=src;
				JSValue ret=JS_NewObjectClass(ctx,(int)js_rlVertexBuffer_class_id);
				JS_SetOpaque(ret,(void *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlRenderBatch_vertexBuffer_set(JSContext * ctx,void * ptr,JSValue set_to,int property,bool as_sting){
		if(as_sting==true){
			return false;
		}else{
			rlVertexBuffer * ptr_ret=(rlVertexBuffer *)JS_GetOpaque(set_to,js_rlVertexBuffer_class_id);
			if(ptr_ret==NULL){
				JS_ThrowTypeError(ctx,(const char *)"set_to does not allow null");
				return -1;
			}
			rlVertexBuffer ret=*ptr_ret;
			((rlRenderBatch *)ptr)[0].vertexBuffer[property] =ret;
		}
		return true;
	}
	
	static int js_rlRenderBatch_vertexBuffer_has(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<((rlRenderBatch *)ptr)[0].bufferCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlRenderBatch_get_vertexBuffer(JSContext * ctx,JSValue this_val){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = this_val,.opaque = ptr,.values = js_rlRenderBatch_vertexBuffer_values,.keys = js_rlRenderBatch_vertexBuffer_keys,.get = js_rlRenderBatch_vertexBuffer_get,.set = js_rlRenderBatch_vertexBuffer_set,.has = js_rlRenderBatch_vertexBuffer_has});
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_vertexBuffer(JSContext * ctx,JSValue this_val,JSValue v){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlVertexBuffer * value;
		bool freesrc_value=(bool)false;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(v);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(v,js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			v =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}else if(JS_IsArray(v)==1){
			if(JS_GetLength(ctx,v,&size_value)==-1){
				return JS_EXCEPTION;
			}
			value =(rlVertexBuffer *)jsc_malloc(ctx,size_value*sizeof(rlVertexBuffer));
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,v,(uint32_t)i);
				rlVertexBuffer * ptr_valuei=(rlVertexBuffer *)JS_GetOpaque(js_value,js_rlVertexBuffer_class_id);
				if(ptr_valuei==NULL){
					JS_ThrowTypeError(ctx,(const char *)"js_value does not allow null");
					return JS_EXCEPTION;
				}
				value[i] =*ptr_valuei;
				JS_FreeValue(ctx,js_value);
			}
		}else if(JS_IsArrayBuffer(v)==1){
			rlVertexBuffer * js_value=(rlVertexBuffer *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,v);
			value =(rlVertexBuffer *)jsc_malloc(ctx,size_value*sizeof(rlVertexBuffer *));
			memcpy((void *)value,(const void *)js_value,(size_t)size_value);
		}else{
			if(freesrc_value){
				JS_FreeValue(ctx,v);
			}
			JS_ThrowTypeError(ctx,(const char *)"v does not match type rlVertexBuffer *");
			return JS_EXCEPTION;
		}
		if(ptr[0].vertexBuffer!=NULL){
			jsc_free(ctx,(void *)ptr[0].vertexBuffer);
		}
		ptr[0].vertexBuffer=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRenderBatch_draws_values(JSContext * ctx,void * ptr,int property,bool as_sting){
		JSValue ret;
		ret =JS_NewArray(ctx);
		int i;
		for(i=0;i<RL_DEFAULT_BATCH_DRAWCALLS;i++){
			rlDrawCall * ptr_js_ret=(rlDrawCall *)js_malloc(ctx,sizeof(rlDrawCall));
			ptr_js_ret[0]=((rlRenderBatch *)ptr)[0].draws[i];
			JSValue js_ret=JS_NewObjectClass(ctx,(int)js_rlDrawCall_class_id);
			JS_SetOpaque(js_ret,(void *)ptr_js_ret);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlRenderBatch_draws_keys(JSContext * ctx,void * ptr,JSPropertyEnum * * keys){
		int length=RL_DEFAULT_BATCH_DRAWCALLS;
		keys[0] =(JSPropertyEnum *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		int i;
		for(i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlRenderBatch_draws_get(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)RL_DEFAULT_BATCH_DRAWCALLS));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<RL_DEFAULT_BATCH_DRAWCALLS){
				rlDrawCall src=((rlRenderBatch *)ptr)[0].draws[property];
				rlDrawCall * ptr_ret=(rlDrawCall *)js_malloc(ctx,sizeof(rlDrawCall));
				ptr_ret[0]=src;
				JSValue ret=JS_NewObjectClass(ctx,(int)js_rlDrawCall_class_id);
				JS_SetOpaque(ret,(void *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlRenderBatch_draws_set(JSContext * ctx,void * ptr,JSValue set_to,int property,bool as_sting){
		if(as_sting==true){
			return false;
		}else{
			rlDrawCall * ptr_ret=(rlDrawCall *)JS_GetOpaque(set_to,js_rlDrawCall_class_id);
			if(ptr_ret==NULL){
				JS_ThrowTypeError(ctx,(const char *)"set_to does not allow null");
				return -1;
			}
			rlDrawCall ret=*ptr_ret;
			((rlRenderBatch *)ptr)[0].draws[property] =ret;
		}
		return true;
	}
	
	static int js_rlRenderBatch_draws_has(JSContext * ctx,void * ptr,int property,bool as_sting){
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<RL_DEFAULT_BATCH_DRAWCALLS){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlRenderBatch_get_draws(JSContext * ctx,JSValue this_val){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = this_val,.opaque = ptr,.values = js_rlRenderBatch_draws_values,.keys = js_rlRenderBatch_draws_keys,.get = js_rlRenderBatch_draws_get,.set = js_rlRenderBatch_draws_set,.has = js_rlRenderBatch_draws_has});
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_draws(JSContext * ctx,JSValue this_val,JSValue v){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlDrawCall * value;
		bool freesrc_value=(bool)false;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(v);
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(v,js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			v =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}else if(JS_IsArray(v)==1){
			if(JS_GetLength(ctx,v,&size_value)==-1){
				return JS_EXCEPTION;
			}
			value =(rlDrawCall *)jsc_malloc(ctx,size_value*sizeof(rlDrawCall));
			int i;
			for(i=0;i<size_value;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,v,(uint32_t)i);
				rlDrawCall * ptr_valuei=(rlDrawCall *)JS_GetOpaque(js_value,js_rlDrawCall_class_id);
				if(ptr_valuei==NULL){
					JS_ThrowTypeError(ctx,(const char *)"js_value does not allow null");
					return JS_EXCEPTION;
				}
				value[i] =*ptr_valuei;
				JS_FreeValue(ctx,js_value);
			}
		}else if(JS_IsArrayBuffer(v)==1){
			rlDrawCall * js_value=(rlDrawCall *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,v);
			value =(rlDrawCall *)jsc_malloc(ctx,size_value*sizeof(rlDrawCall *));
			memcpy((void *)value,(const void *)js_value,(size_t)size_value);
		}else{
			if(freesrc_value){
				JS_FreeValue(ctx,v);
			}
			JS_ThrowTypeError(ctx,(const char *)"v does not match type rlDrawCall *");
			return JS_EXCEPTION;
		}
		if(ptr[0].draws!=NULL){
			jsc_free(ctx,(void *)ptr[0].draws);
		}
		ptr[0].draws=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRenderBatch_get_drawCounter(JSContext * ctx,JSValue this_val){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		int drawCounter=ptr[0].drawCounter;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)drawCounter));
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_drawCounter(JSContext * ctx,JSValue this_val,JSValue v){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].drawCounter=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRenderBatch_get_currentDepth(JSContext * ctx,JSValue this_val){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		float currentDepth=ptr[0].currentDepth;
		JSValue ret=JS_NewFloat64(ctx,((double)currentDepth));
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_currentDepth(JSContext * ctx,JSValue this_val,JSValue v){
		rlRenderBatch * ptr=(rlRenderBatch *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		double double_value;
		int err_value=JS_ToFloat64(ctx,&double_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		float value=((float)double_value);
		ptr[0].currentDepth=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_rlRenderBatch_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","rlRenderBatch", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("bufferCount",js_rlRenderBatch_get_bufferCount,js_rlRenderBatch_set_bufferCount),
		JS_CGETSET_DEF("currentBuffer",js_rlRenderBatch_get_currentBuffer,js_rlRenderBatch_set_currentBuffer),
		JS_CGETSET_DEF("vertexBuffer",js_rlRenderBatch_get_vertexBuffer,js_rlRenderBatch_set_vertexBuffer),
		JS_CGETSET_DEF("draws",js_rlRenderBatch_get_draws,js_rlRenderBatch_set_draws),
		JS_CGETSET_DEF("drawCounter",js_rlRenderBatch_get_drawCounter,js_rlRenderBatch_set_drawCounter),
		JS_CGETSET_DEF("currentDepth",js_rlRenderBatch_get_currentDepth,js_rlRenderBatch_set_currentDepth)
	};
	
	static int js_declare_rlRenderBatch(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_rlRenderBatch_class_id);
		JSClassDef js_rlRenderBatch_def={ .class_name = "rlRenderBatch", .finalizer = js_rlRenderBatch_finalizer };
		JS_NewClass(rt,js_rlRenderBatch_class_id,(const JSClassDef *)&js_rlRenderBatch_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_rlRenderBatch_proto_funcs,(int)countof(js_rlRenderBatch_proto_funcs));
		JS_SetClassProto(ctx,js_rlRenderBatch_class_id,proto);
		return 0;
	}
	
	static JSValue js_rlVertexBuffer_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			rlVertexBuffer * ptr__return=(rlVertexBuffer *)js_calloc(ctx,(size_t)1,sizeof(rlVertexBuffer));
			JSValue _return=JS_NewObjectClass(ctx,(int)js_rlVertexBuffer_class_id);
			JS_SetOpaque(_return,(void *)ptr__return);
			return _return;
		}
		int32_t long_elementCount;
		int err_elementCount=JS_ToInt32(ctx,&long_elementCount,argv[0]);
		if(err_elementCount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int elementCount=((int)long_elementCount);
		float * vertices;
		bool freesrc_vertices=(bool)false;
		JSValue da_vertices;
		int64_t size_vertices;
		JSClassID vertices_class=JS_GetClassID(argv[1]);
		if(vertices_class==js_ArrayProxy_class_id){
			void * opaque_vertices=JS_GetOpaque(argv[1],js_ArrayProxy_class_id);
			ArrayProxy_class AP_vertices=((ArrayProxy_class *)opaque_vertices)[0];
			argv[1] =AP_vertices.values(ctx,AP_vertices.opaque,(int)0,(bool)false);
			freesrc_vertices =(bool)true;
		}else if(JS_IsArray(argv[1])==1){
			if(JS_GetLength(ctx,argv[1],&size_vertices)==-1){
				return JS_EXCEPTION;
			}
			vertices =(float *)js_malloc(ctx,size_vertices*sizeof(float));
			int i;
			for(i=0;i<size_vertices;i++){
				JSValue js_vertices=JS_GetPropertyUint32(ctx,argv[1],(uint32_t)i);
				double double_verticesi;
				int err_verticesi=JS_ToFloat64(ctx,&double_verticesi,js_vertices);
				if(err_verticesi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_vertices is not numeric");
					return JS_EXCEPTION;
				}
				vertices[i] =((float)double_verticesi);
				JS_FreeValue(ctx,js_vertices);
			}
		}else if(JS_IsArrayBuffer(argv[1])==1){
			vertices =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_vertices,argv[1]);
		}else{
			JSClassID classid_vertices=JS_GetClassID(argv[1]);
			if(classid_vertices==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_vertices;
				da_vertices =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_vertices,(size_t *)&size_vertices,NULL);
				vertices =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_vertices,da_vertices);
				vertices +=offset_vertices;
				size_vertices -=offset_vertices;
			}else{
				if(freesrc_vertices){
					JS_FreeValue(ctx,argv[1]);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type float *");
				return JS_EXCEPTION;
			}
		}
		float * texcoords;
		bool freesrc_texcoords=(bool)false;
		JSValue da_texcoords;
		int64_t size_texcoords;
		JSClassID texcoords_class=JS_GetClassID(argv[2]);
		if(texcoords_class==js_ArrayProxy_class_id){
			void * opaque_texcoords=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_texcoords=((ArrayProxy_class *)opaque_texcoords)[0];
			argv[2] =AP_texcoords.values(ctx,AP_texcoords.opaque,(int)0,(bool)false);
			freesrc_texcoords =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_texcoords)==-1){
				return JS_EXCEPTION;
			}
			texcoords =(float *)js_malloc(ctx,size_texcoords*sizeof(float));
			int i;
			for(i=0;i<size_texcoords;i++){
				JSValue js_texcoords=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				double double_texcoordsi;
				int err_texcoordsi=JS_ToFloat64(ctx,&double_texcoordsi,js_texcoords);
				if(err_texcoordsi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_texcoords is not numeric");
					return JS_EXCEPTION;
				}
				texcoords[i] =((float)double_texcoordsi);
				JS_FreeValue(ctx,js_texcoords);
			}
		}else if(JS_IsArrayBuffer(argv[2])==1){
			texcoords =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_texcoords,argv[2]);
		}else{
			JSClassID classid_texcoords=JS_GetClassID(argv[2]);
			if(classid_texcoords==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_texcoords;
				da_texcoords =JS_GetTypedArrayBuffer(ctx,argv[2],&offset_texcoords,(size_t *)&size_texcoords,NULL);
				texcoords =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_texcoords,da_texcoords);
				texcoords +=offset_texcoords;
				size_texcoords -=offset_texcoords;
			}else{
				if(freesrc_texcoords){
					JS_FreeValue(ctx,argv[2]);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type float *");
				return JS_EXCEPTION;
			}
		}
		float * normals;
		bool freesrc_normals=(bool)false;
		JSValue da_normals;
		int64_t size_normals;
		JSClassID normals_class=JS_GetClassID(argv[3]);
		if(normals_class==js_ArrayProxy_class_id){
			void * opaque_normals=JS_GetOpaque(argv[3],js_ArrayProxy_class_id);
			ArrayProxy_class AP_normals=((ArrayProxy_class *)opaque_normals)[0];
			argv[3] =AP_normals.values(ctx,AP_normals.opaque,(int)0,(bool)false);
			freesrc_normals =(bool)true;
		}else if(JS_IsArray(argv[3])==1){
			if(JS_GetLength(ctx,argv[3],&size_normals)==-1){
				return JS_EXCEPTION;
			}
			normals =(float *)js_malloc(ctx,size_normals*sizeof(float));
			int i;
			for(i=0;i<size_normals;i++){
				JSValue js_normals=JS_GetPropertyUint32(ctx,argv[3],(uint32_t)i);
				double double_normalsi;
				int err_normalsi=JS_ToFloat64(ctx,&double_normalsi,js_normals);
				if(err_normalsi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_normals is not numeric");
					return JS_EXCEPTION;
				}
				normals[i] =((float)double_normalsi);
				JS_FreeValue(ctx,js_normals);
			}
		}else if(JS_IsArrayBuffer(argv[3])==1){
			normals =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_normals,argv[3]);
		}else{
			JSClassID classid_normals=JS_GetClassID(argv[3]);
			if(classid_normals==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_normals;
				da_normals =JS_GetTypedArrayBuffer(ctx,argv[3],&offset_normals,(size_t *)&size_normals,NULL);
				normals =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_normals,da_normals);
				normals +=offset_normals;
				size_normals -=offset_normals;
			}else{
				if(freesrc_normals){
					JS_FreeValue(ctx,argv[3]);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[3] does not match type float *");
				return JS_EXCEPTION;
			}
		}
		unsigned char * colors;
		bool freesrc_colors=(bool)false;
		JSValue da_colors;
		int64_t size_colors;
		JSClassID colors_class=JS_GetClassID(argv[4]);
		if(colors_class==js_ArrayProxy_class_id){
			void * opaque_colors=JS_GetOpaque(argv[4],js_ArrayProxy_class_id);
			ArrayProxy_class AP_colors=((ArrayProxy_class *)opaque_colors)[0];
			argv[4] =AP_colors.values(ctx,AP_colors.opaque,(int)0,(bool)false);
			freesrc_colors =(bool)true;
		}else if(JS_IsArray(argv[4])==1){
			if(JS_GetLength(ctx,argv[4],&size_colors)==-1){
				return JS_EXCEPTION;
			}
			colors =(unsigned char *)js_malloc(ctx,size_colors*sizeof(unsigned char));
			int i;
			for(i=0;i<size_colors;i++){
				JSValue js_colors=JS_GetPropertyUint32(ctx,argv[4],(uint32_t)i);
				uint32_t long_colorsi;
				int err_colorsi=JS_ToUint32(ctx,&long_colorsi,js_colors);
				if(err_colorsi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_colors is not numeric");
					return JS_EXCEPTION;
				}
				colors[i] =((unsigned char)long_colorsi);
				JS_FreeValue(ctx,js_colors);
			}
		}else if(JS_IsArrayBuffer(argv[4])==1){
			colors =(unsigned char *)JS_GetArrayBuffer(ctx,(size_t *)&size_colors,argv[4]);
		}else{
			JSClassID classid_colors=JS_GetClassID(argv[4]);
			if(classid_colors==JS_CLASS_UINT8_ARRAY||classid_colors==JS_CLASS_UINT8C_ARRAY){
				size_t offset_colors;
				da_colors =JS_GetTypedArrayBuffer(ctx,argv[4],&offset_colors,(size_t *)&size_colors,NULL);
				colors =(unsigned char *)JS_GetArrayBuffer(ctx,(size_t *)&size_colors,da_colors);
				colors +=offset_colors;
				size_colors -=offset_colors;
			}else{
				if(freesrc_colors){
					JS_FreeValue(ctx,argv[4]);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[4] does not match type unsigned char *");
				return JS_EXCEPTION;
			}
		}
		unsigned int * indices;
		bool freesrc_indices=(bool)false;
		JSValue da_indices;
		int64_t size_indices;
		JSClassID indices_class=JS_GetClassID(argv[5]);
		if(indices_class==js_ArrayProxy_class_id){
			void * opaque_indices=JS_GetOpaque(argv[5],js_ArrayProxy_class_id);
			ArrayProxy_class AP_indices=((ArrayProxy_class *)opaque_indices)[0];
			argv[5] =AP_indices.values(ctx,AP_indices.opaque,(int)0,(bool)false);
			freesrc_indices =(bool)true;
		}else if(JS_IsArray(argv[5])==1){
			if(JS_GetLength(ctx,argv[5],&size_indices)==-1){
				return JS_EXCEPTION;
			}
			indices =(unsigned int *)js_malloc(ctx,size_indices*sizeof(unsigned int));
			int i;
			for(i=0;i<size_indices;i++){
				JSValue js_indices=JS_GetPropertyUint32(ctx,argv[5],(uint32_t)i);
				uint32_t long_indicesi;
				int err_indicesi=JS_ToUint32(ctx,&long_indicesi,js_indices);
				if(err_indicesi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_indices is not numeric");
					return JS_EXCEPTION;
				}
				indices[i] =((unsigned int)long_indicesi);
				JS_FreeValue(ctx,js_indices);
			}
		}else if(JS_IsArrayBuffer(argv[5])==1){
			indices =(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_indices,argv[5]);
		}else{
			JSClassID classid_indices=JS_GetClassID(argv[5]);
			if(classid_indices==JS_CLASS_UINT16_ARRAY){
				size_t offset_indices;
				da_indices =JS_GetTypedArrayBuffer(ctx,argv[5],&offset_indices,(size_t *)&size_indices,NULL);
				indices =(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_indices,da_indices);
				indices +=offset_indices;
				size_indices -=offset_indices;
			}else{
				if(freesrc_indices){
					JS_FreeValue(ctx,argv[5]);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[5] does not match type unsigned int *");
				return JS_EXCEPTION;
			}
		}
		uint32_t long_vaoId;
		int err_vaoId=JS_ToUint32(ctx,&long_vaoId,argv[6]);
		if(err_vaoId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[6] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int vaoId=((unsigned int)long_vaoId);
		unsigned int * vboId;
		bool freesrc_vboId=(bool)false;
		JSValue da_vboId;
		int64_t size_vboId;
		JSClassID vboId_class=JS_GetClassID(argv[7]);
		if(vboId_class==js_ArrayProxy_class_id){
			void * opaque_vboId=JS_GetOpaque(argv[7],js_ArrayProxy_class_id);
			ArrayProxy_class AP_vboId=((ArrayProxy_class *)opaque_vboId)[0];
			argv[7] =AP_vboId.values(ctx,AP_vboId.opaque,(int)0,(bool)false);
			freesrc_vboId =(bool)true;
		}else if(JS_IsArray(argv[7])==1){
			vboId =(unsigned int *)js_malloc(ctx,5*sizeof(unsigned int));
			int i;
			for(i=0;i<5;i++){
				JSValue js_vboId=JS_GetPropertyUint32(ctx,argv[7],(uint32_t)i);
				uint32_t long_vboIdi;
				int err_vboIdi=JS_ToUint32(ctx,&long_vboIdi,js_vboId);
				if(err_vboIdi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_vboId is not numeric");
					return JS_EXCEPTION;
				}
				vboId[i] =((unsigned int)long_vboIdi);
				JS_FreeValue(ctx,js_vboId);
			}
		}else if(JS_IsArrayBuffer(argv[7])==1){
			vboId =(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_vboId,argv[7]);
		}else{
			JSClassID classid_vboId=JS_GetClassID(argv[7]);
			if(classid_vboId==JS_CLASS_UINT16_ARRAY){
				size_t offset_vboId;
				da_vboId =JS_GetTypedArrayBuffer(ctx,argv[7],&offset_vboId,(size_t *)&size_vboId,NULL);
				vboId =(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_vboId,da_vboId);
				vboId +=offset_vboId;
				size_vboId -=offset_vboId;
			}else{
				if(freesrc_vboId){
					JS_FreeValue(ctx,argv[7]);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[7] does not match type unsigned int *");
				return JS_EXCEPTION;
			}
		}
		rlVertexBuffer _struct={
			elementCount,
			vertices,
			texcoords,
			normals,
			colors,
			indices,
			vaoId,
			{vboId[0],vboId[1],vboId[2],vboId[3],vboId[4]}
		};
		rlVertexBuffer * ptr__return=(rlVertexBuffer *)js_malloc(ctx,sizeof(rlVertexBuffer));
		ptr__return[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,(int)js_rlVertexBuffer_class_id);
		JS_SetOpaque(_return,(void *)ptr__return);
		return _return;
	}
	
	static JSValue js_rlDrawCall_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			rlDrawCall * ptr__return=(rlDrawCall *)js_calloc(ctx,(size_t)1,sizeof(rlDrawCall));
			JSValue _return=JS_NewObjectClass(ctx,(int)js_rlDrawCall_class_id);
			JS_SetOpaque(_return,(void *)ptr__return);
			return _return;
		}
		int32_t long_mode;
		int err_mode=JS_ToInt32(ctx,&long_mode,argv[0]);
		if(err_mode<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int mode=((int)long_mode);
		int32_t long_vertexCount;
		int err_vertexCount=JS_ToInt32(ctx,&long_vertexCount,argv[1]);
		if(err_vertexCount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int vertexCount=((int)long_vertexCount);
		int32_t long_vertexAlignment;
		int err_vertexAlignment=JS_ToInt32(ctx,&long_vertexAlignment,argv[2]);
		if(err_vertexAlignment<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int vertexAlignment=((int)long_vertexAlignment);
		uint32_t long_textureId;
		int err_textureId=JS_ToUint32(ctx,&long_textureId,argv[3]);
		if(err_textureId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int textureId=((unsigned int)long_textureId);
		rlDrawCall _struct={
			mode,
			vertexCount,
			vertexAlignment,
			textureId
		};
		rlDrawCall * ptr__return=(rlDrawCall *)js_malloc(ctx,sizeof(rlDrawCall));
		ptr__return[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,(int)js_rlDrawCall_class_id);
		JS_SetOpaque(_return,(void *)ptr__return);
		return _return;
	}
	
	static JSValue js_rlRenderBatch_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			rlRenderBatch * ptr__return=(rlRenderBatch *)js_calloc(ctx,(size_t)1,sizeof(rlRenderBatch));
			JSValue _return=JS_NewObjectClass(ctx,(int)js_rlRenderBatch_class_id);
			JS_SetOpaque(_return,(void *)ptr__return);
			return _return;
		}
		int32_t long_bufferCount;
		int err_bufferCount=JS_ToInt32(ctx,&long_bufferCount,argv[0]);
		if(err_bufferCount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int bufferCount=((int)long_bufferCount);
		int32_t long_currentBuffer;
		int err_currentBuffer=JS_ToInt32(ctx,&long_currentBuffer,argv[1]);
		if(err_currentBuffer<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int currentBuffer=((int)long_currentBuffer);
		rlVertexBuffer * vertexBuffer;
		bool freesrc_vertexBuffer=(bool)false;
		int64_t size_vertexBuffer;
		JSClassID vertexBuffer_class=JS_GetClassID(argv[2]);
		if(vertexBuffer_class==js_ArrayProxy_class_id){
			void * opaque_vertexBuffer=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_vertexBuffer=((ArrayProxy_class *)opaque_vertexBuffer)[0];
			argv[2] =AP_vertexBuffer.values(ctx,AP_vertexBuffer.opaque,(int)0,(bool)false);
			freesrc_vertexBuffer =(bool)true;
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_vertexBuffer)==-1){
				return JS_EXCEPTION;
			}
			vertexBuffer =(rlVertexBuffer *)js_malloc(ctx,size_vertexBuffer*sizeof(rlVertexBuffer));
			int i;
			for(i=0;i<size_vertexBuffer;i++){
				JSValue js_vertexBuffer=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				rlVertexBuffer * ptr_vertexBufferi=(rlVertexBuffer *)JS_GetOpaque(js_vertexBuffer,js_rlVertexBuffer_class_id);
				if(ptr_vertexBufferi==NULL){
					JS_ThrowTypeError(ctx,(const char *)"js_vertexBuffer does not allow null");
					return JS_EXCEPTION;
				}
				vertexBuffer[i] =*ptr_vertexBufferi;
				JS_FreeValue(ctx,js_vertexBuffer);
			}
		}else if(JS_IsArrayBuffer(argv[2])==1){
			vertexBuffer =(rlVertexBuffer *)JS_GetArrayBuffer(ctx,(size_t *)&size_vertexBuffer,argv[2]);
		}else{
			if(freesrc_vertexBuffer){
				JS_FreeValue(ctx,argv[2]);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type rlVertexBuffer *");
			return JS_EXCEPTION;
		}
		rlDrawCall * draws;
		bool freesrc_draws=(bool)false;
		int64_t size_draws;
		JSClassID draws_class=JS_GetClassID(argv[3]);
		if(draws_class==js_ArrayProxy_class_id){
			void * opaque_draws=JS_GetOpaque(argv[3],js_ArrayProxy_class_id);
			ArrayProxy_class AP_draws=((ArrayProxy_class *)opaque_draws)[0];
			argv[3] =AP_draws.values(ctx,AP_draws.opaque,(int)0,(bool)false);
			freesrc_draws =(bool)true;
		}else if(JS_IsArray(argv[3])==1){
			if(JS_GetLength(ctx,argv[3],&size_draws)==-1){
				return JS_EXCEPTION;
			}
			draws =(rlDrawCall *)js_malloc(ctx,size_draws*sizeof(rlDrawCall));
			int i;
			for(i=0;i<size_draws;i++){
				JSValue js_draws=JS_GetPropertyUint32(ctx,argv[3],(uint32_t)i);
				rlDrawCall * ptr_drawsi=(rlDrawCall *)JS_GetOpaque(js_draws,js_rlDrawCall_class_id);
				if(ptr_drawsi==NULL){
					JS_ThrowTypeError(ctx,(const char *)"js_draws does not allow null");
					return JS_EXCEPTION;
				}
				draws[i] =*ptr_drawsi;
				JS_FreeValue(ctx,js_draws);
			}
		}else if(JS_IsArrayBuffer(argv[3])==1){
			draws =(rlDrawCall *)JS_GetArrayBuffer(ctx,(size_t *)&size_draws,argv[3]);
		}else{
			if(freesrc_draws){
				JS_FreeValue(ctx,argv[3]);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[3] does not match type rlDrawCall *");
			return JS_EXCEPTION;
		}
		int32_t long_drawCounter;
		int err_drawCounter=JS_ToInt32(ctx,&long_drawCounter,argv[4]);
		if(err_drawCounter<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		int drawCounter=((int)long_drawCounter);
		double double_currentDepth;
		int err_currentDepth=JS_ToFloat64(ctx,&double_currentDepth,argv[5]);
		if(err_currentDepth<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		float currentDepth=((float)double_currentDepth);
		rlRenderBatch _struct={
			bufferCount,
			currentBuffer,
			vertexBuffer,
			draws,
			drawCounter,
			currentDepth
		};
		rlRenderBatch * ptr__return=(rlRenderBatch *)js_malloc(ctx,sizeof(rlRenderBatch));
		ptr__return[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,(int)js_rlRenderBatch_class_id);
		JS_SetOpaque(_return,(void *)ptr__return);
		return _return;
	}
	
	static JSValue js_rlMatrixMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_mode;
		int err_mode=JS_ToInt32(ctx,&long_mode,argv[0]);
		if(err_mode<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int mode=((int)long_mode);
		rlMatrixMode(mode);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlPushMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlPushMatrix();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlPopMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlPopMatrix();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadIdentity(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlLoadIdentity();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlTranslatef(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_x;
		int err_x=JS_ToFloat64(ctx,&double_x,argv[0]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float x=((float)double_x);
		double double_y;
		int err_y=JS_ToFloat64(ctx,&double_y,argv[1]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float y=((float)double_y);
		double double_z;
		int err_z=JS_ToFloat64(ctx,&double_z,argv[2]);
		if(err_z<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float z=((float)double_z);
		rlTranslatef(x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRotatef(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_angle;
		int err_angle=JS_ToFloat64(ctx,&double_angle,argv[0]);
		if(err_angle<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float angle=((float)double_angle);
		double double_x;
		int err_x=JS_ToFloat64(ctx,&double_x,argv[1]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float x=((float)double_x);
		double double_y;
		int err_y=JS_ToFloat64(ctx,&double_y,argv[2]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float y=((float)double_y);
		double double_z;
		int err_z=JS_ToFloat64(ctx,&double_z,argv[3]);
		if(err_z<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		float z=((float)double_z);
		rlRotatef(angle,x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlScalef(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_x;
		int err_x=JS_ToFloat64(ctx,&double_x,argv[0]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float x=((float)double_x);
		double double_y;
		int err_y=JS_ToFloat64(ctx,&double_y,argv[1]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float y=((float)double_y);
		double double_z;
		int err_z=JS_ToFloat64(ctx,&double_z,argv[2]);
		if(err_z<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float z=((float)double_z);
		rlScalef(x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlMultMatrixf(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		float * matf;
		bool freesrc_matf=(bool)false;
		int64_t size_matf;
		JSClassID matf_class=JS_GetClassID(argv[0]);
		if(matf_class==js_ArrayProxy_class_id){
			void * opaque_matf=JS_GetOpaque(argv[0],js_ArrayProxy_class_id);
			ArrayProxy_class AP_matf=((ArrayProxy_class *)opaque_matf)[0];
			argv[0] =AP_matf.values(ctx,AP_matf.opaque,(int)0,(bool)false);
			freesrc_matf =(bool)true;
		}else if(JS_IsArray(argv[0])==1){
			if(JS_GetLength(ctx,argv[0],&size_matf)==-1){
				return JS_EXCEPTION;
			}
			matf =(float *)js_malloc(ctx,size_matf*sizeof(float));
			int i;
			for(i=0;i<size_matf;i++){
				JSValue js_matf=JS_GetPropertyUint32(ctx,argv[0],(uint32_t)i);
				double double_matfi;
				int err_matfi=JS_ToFloat64(ctx,&double_matfi,js_matf);
				if(err_matfi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_matf is not numeric");
					return JS_EXCEPTION;
				}
				matf[i] =((float)double_matfi);
				JS_FreeValue(ctx,js_matf);
			}
		}else{
			double double_js_matf;
			int err_js_matf=JS_ToFloat64(ctx,&double_js_matf,argv[0]);
			if(err_js_matf<0){
				JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
				return JS_EXCEPTION;
			}
			float js_matf=((float)double_js_matf);
			matf =&js_matf;
		}
		rlMultMatrixf((const float *)matf);
		if(JS_IsArray(argv[0])==1){
			JSValue js_argv0=JS_NewFloat64(ctx,((double)matf[0]));
			JS_DefinePropertyValueUint32(ctx,argv[0],(uint32_t)0,js_argv0,JS_PROP_C_W_E);
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlFrustum(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double left;
		int err_left=JS_ToFloat64(ctx,&left,argv[0]);
		if(err_left<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		double right;
		int err_right=JS_ToFloat64(ctx,&right,argv[1]);
		if(err_right<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		double bottom;
		int err_bottom=JS_ToFloat64(ctx,&bottom,argv[2]);
		if(err_bottom<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		double top;
		int err_top=JS_ToFloat64(ctx,&top,argv[3]);
		if(err_top<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		double znear;
		int err_znear=JS_ToFloat64(ctx,&znear,argv[4]);
		if(err_znear<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		double zfar;
		int err_zfar=JS_ToFloat64(ctx,&zfar,argv[5]);
		if(err_zfar<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		rlFrustum(left,right,bottom,top,znear,zfar);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlOrtho(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double left;
		int err_left=JS_ToFloat64(ctx,&left,argv[0]);
		if(err_left<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		double right;
		int err_right=JS_ToFloat64(ctx,&right,argv[1]);
		if(err_right<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		double bottom;
		int err_bottom=JS_ToFloat64(ctx,&bottom,argv[2]);
		if(err_bottom<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		double top;
		int err_top=JS_ToFloat64(ctx,&top,argv[3]);
		if(err_top<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		double znear;
		int err_znear=JS_ToFloat64(ctx,&znear,argv[4]);
		if(err_znear<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		double zfar;
		int err_zfar=JS_ToFloat64(ctx,&zfar,argv[5]);
		if(err_zfar<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		rlOrtho(left,right,bottom,top,znear,zfar);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlViewport(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_x;
		int err_x=JS_ToInt32(ctx,&long_x,argv[0]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int x=((int)long_x);
		int32_t long_y;
		int err_y=JS_ToInt32(ctx,&long_y,argv[1]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int y=((int)long_y);
		int32_t long_width;
		int err_width=JS_ToInt32(ctx,&long_width,argv[2]);
		if(err_width<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int width=((int)long_width);
		int32_t long_height;
		int err_height=JS_ToInt32(ctx,&long_height,argv[3]);
		if(err_height<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int height=((int)long_height);
		rlViewport(x,y,width,height);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetClipPlanes(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double nearPlane;
		int err_nearPlane=JS_ToFloat64(ctx,&nearPlane,argv[0]);
		if(err_nearPlane<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		double farPlane;
		int err_farPlane=JS_ToFloat64(ctx,&farPlane,argv[1]);
		if(err_farPlane<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		rlSetClipPlanes(nearPlane,farPlane);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetCullDistanceNear(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double returnVal=rlGetCullDistanceNear();
		JSValue ret=JS_NewFloat64(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_rlGetCullDistanceFar(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double returnVal=rlGetCullDistanceFar();
		JSValue ret=JS_NewFloat64(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_rlBegin(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_mode;
		int err_mode=JS_ToInt32(ctx,&long_mode,argv[0]);
		if(err_mode<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int mode=((int)long_mode);
		rlBegin(mode);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnd(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlEnd();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertex2i(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_x;
		int err_x=JS_ToInt32(ctx,&long_x,argv[0]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int x=((int)long_x);
		int32_t long_y;
		int err_y=JS_ToInt32(ctx,&long_y,argv[1]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int y=((int)long_y);
		rlVertex2i(x,y);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertex2f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_x;
		int err_x=JS_ToFloat64(ctx,&double_x,argv[0]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float x=((float)double_x);
		double double_y;
		int err_y=JS_ToFloat64(ctx,&double_y,argv[1]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float y=((float)double_y);
		rlVertex2f(x,y);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertex3f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_x;
		int err_x=JS_ToFloat64(ctx,&double_x,argv[0]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float x=((float)double_x);
		double double_y;
		int err_y=JS_ToFloat64(ctx,&double_y,argv[1]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float y=((float)double_y);
		double double_z;
		int err_z=JS_ToFloat64(ctx,&double_z,argv[2]);
		if(err_z<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float z=((float)double_z);
		rlVertex3f(x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlTexCoord2f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_x;
		int err_x=JS_ToFloat64(ctx,&double_x,argv[0]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float x=((float)double_x);
		double double_y;
		int err_y=JS_ToFloat64(ctx,&double_y,argv[1]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float y=((float)double_y);
		rlTexCoord2f(x,y);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlNormal3f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_x;
		int err_x=JS_ToFloat64(ctx,&double_x,argv[0]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float x=((float)double_x);
		double double_y;
		int err_y=JS_ToFloat64(ctx,&double_y,argv[1]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float y=((float)double_y);
		double double_z;
		int err_z=JS_ToFloat64(ctx,&double_z,argv[2]);
		if(err_z<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float z=((float)double_z);
		rlNormal3f(x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlColor4ub(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_r;
		int err_r=JS_ToUint32(ctx,&long_r,argv[0]);
		if(err_r<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned char r=((unsigned char)long_r);
		uint32_t long_g;
		int err_g=JS_ToUint32(ctx,&long_g,argv[1]);
		if(err_g<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned char g=((unsigned char)long_g);
		uint32_t long_b;
		int err_b=JS_ToUint32(ctx,&long_b,argv[2]);
		if(err_b<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned char b=((unsigned char)long_b);
		uint32_t long_a;
		int err_a=JS_ToUint32(ctx,&long_a,argv[3]);
		if(err_a<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned char a=((unsigned char)long_a);
		rlColor4ub(r,g,b,a);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlColor3f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_x;
		int err_x=JS_ToFloat64(ctx,&double_x,argv[0]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float x=((float)double_x);
		double double_y;
		int err_y=JS_ToFloat64(ctx,&double_y,argv[1]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float y=((float)double_y);
		double double_z;
		int err_z=JS_ToFloat64(ctx,&double_z,argv[2]);
		if(err_z<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float z=((float)double_z);
		rlColor3f(x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlColor4f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_x;
		int err_x=JS_ToFloat64(ctx,&double_x,argv[0]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float x=((float)double_x);
		double double_y;
		int err_y=JS_ToFloat64(ctx,&double_y,argv[1]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float y=((float)double_y);
		double double_z;
		int err_z=JS_ToFloat64(ctx,&double_z,argv[2]);
		if(err_z<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float z=((float)double_z);
		double double_w;
		int err_w=JS_ToFloat64(ctx,&double_w,argv[3]);
		if(err_w<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		float w=((float)double_w);
		rlColor4f(x,y,z,w);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableVertexArray(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_vaoId;
		int err_vaoId=JS_ToUint32(ctx,&long_vaoId,argv[0]);
		if(err_vaoId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int vaoId=((unsigned int)long_vaoId);
		bool returnVal=rlEnableVertexArray(vaoId);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_rlDisableVertexArray(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableVertexArray();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableVertexBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		rlEnableVertexBuffer(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableVertexBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableVertexBuffer();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableVertexBufferElement(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		rlEnableVertexBufferElement(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableVertexBufferElement(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableVertexBufferElement();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableVertexAttribute(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_index;
		int err_index=JS_ToUint32(ctx,&long_index,argv[0]);
		if(err_index<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int index=((unsigned int)long_index);
		rlEnableVertexAttribute(index);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableVertexAttribute(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_index;
		int err_index=JS_ToUint32(ctx,&long_index,argv[0]);
		if(err_index<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int index=((unsigned int)long_index);
		rlDisableVertexAttribute(index);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlActiveTextureSlot(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_slot;
		int err_slot=JS_ToInt32(ctx,&long_slot,argv[0]);
		if(err_slot<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int slot=((int)long_slot);
		rlActiveTextureSlot(slot);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		rlEnableTexture(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableTexture();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableTextureCubemap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		rlEnableTextureCubemap(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableTextureCubemap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableTextureCubemap();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlTextureParameters(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		int32_t long_param;
		int err_param=JS_ToInt32(ctx,&long_param,argv[1]);
		if(err_param<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int param=((int)long_param);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,argv[2]);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		rlTextureParameters(id,param,value);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlCubemapParameters(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		int32_t long_param;
		int err_param=JS_ToInt32(ctx,&long_param,argv[1]);
		if(err_param<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int param=((int)long_param);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,argv[2]);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		rlCubemapParameters(id,param,value);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableShader(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		rlEnableShader(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableShader(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableShader();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		rlEnableFramebuffer(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableFramebuffer();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetActiveFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=rlGetActiveFramebuffer();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlActiveDrawBuffers(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_count;
		int err_count=JS_ToInt32(ctx,&long_count,argv[0]);
		if(err_count<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int count=((int)long_count);
		rlActiveDrawBuffers(count);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlBlitFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_srcX;
		int err_srcX=JS_ToInt32(ctx,&long_srcX,argv[0]);
		if(err_srcX<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int srcX=((int)long_srcX);
		int32_t long_srcY;
		int err_srcY=JS_ToInt32(ctx,&long_srcY,argv[1]);
		if(err_srcY<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int srcY=((int)long_srcY);
		int32_t long_srcWidth;
		int err_srcWidth=JS_ToInt32(ctx,&long_srcWidth,argv[2]);
		if(err_srcWidth<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int srcWidth=((int)long_srcWidth);
		int32_t long_srcHeight;
		int err_srcHeight=JS_ToInt32(ctx,&long_srcHeight,argv[3]);
		if(err_srcHeight<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int srcHeight=((int)long_srcHeight);
		int32_t long_dstX;
		int err_dstX=JS_ToInt32(ctx,&long_dstX,argv[4]);
		if(err_dstX<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		int dstX=((int)long_dstX);
		int32_t long_dstY;
		int err_dstY=JS_ToInt32(ctx,&long_dstY,argv[5]);
		if(err_dstY<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		int dstY=((int)long_dstY);
		int32_t long_dstWidth;
		int err_dstWidth=JS_ToInt32(ctx,&long_dstWidth,argv[6]);
		if(err_dstWidth<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[6] is not numeric");
			return JS_EXCEPTION;
		}
		int dstWidth=((int)long_dstWidth);
		int32_t long_dstHeight;
		int err_dstHeight=JS_ToInt32(ctx,&long_dstHeight,argv[7]);
		if(err_dstHeight<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[7] is not numeric");
			return JS_EXCEPTION;
		}
		int dstHeight=((int)long_dstHeight);
		int32_t long_bufferMask;
		int err_bufferMask=JS_ToInt32(ctx,&long_bufferMask,argv[8]);
		if(err_bufferMask<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[8] is not numeric");
			return JS_EXCEPTION;
		}
		int bufferMask=((int)long_bufferMask);
		rlBlitFramebuffer(srcX,srcY,srcWidth,srcHeight,dstX,dstY,dstWidth,dstHeight,bufferMask);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlBindFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_target;
		int err_target=JS_ToUint32(ctx,&long_target,argv[0]);
		if(err_target<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int target=((unsigned int)long_target);
		uint32_t long_framebuffer;
		int err_framebuffer=JS_ToUint32(ctx,&long_framebuffer,argv[1]);
		if(err_framebuffer<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int framebuffer=((unsigned int)long_framebuffer);
		rlBindFramebuffer(target,framebuffer);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableColorBlend(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlEnableColorBlend();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableColorBlend(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableColorBlend();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableDepthTest(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlEnableDepthTest();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableDepthTest(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableDepthTest();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableDepthMask(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlEnableDepthMask();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableDepthMask(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableDepthMask();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableBackfaceCulling(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlEnableBackfaceCulling();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableBackfaceCulling(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableBackfaceCulling();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlColorMask(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int js_r=JS_ToBool(ctx,argv[0]);
		if(js_r<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not a bool");
			return JS_EXCEPTION;
		}
		bool r=(bool)js_r;
		int js_g=JS_ToBool(ctx,argv[1]);
		if(js_g<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not a bool");
			return JS_EXCEPTION;
		}
		bool g=(bool)js_g;
		int js_b=JS_ToBool(ctx,argv[2]);
		if(js_b<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not a bool");
			return JS_EXCEPTION;
		}
		bool b=(bool)js_b;
		int js_a=JS_ToBool(ctx,argv[3]);
		if(js_a<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not a bool");
			return JS_EXCEPTION;
		}
		bool a=(bool)js_a;
		rlColorMask(r,g,b,a);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetCullFace(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_mode;
		int err_mode=JS_ToInt32(ctx,&long_mode,argv[0]);
		if(err_mode<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int mode=((int)long_mode);
		rlSetCullFace(mode);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableScissorTest(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlEnableScissorTest();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableScissorTest(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableScissorTest();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlScissor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_x;
		int err_x=JS_ToInt32(ctx,&long_x,argv[0]);
		if(err_x<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int x=((int)long_x);
		int32_t long_y;
		int err_y=JS_ToInt32(ctx,&long_y,argv[1]);
		if(err_y<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int y=((int)long_y);
		int32_t long_width;
		int err_width=JS_ToInt32(ctx,&long_width,argv[2]);
		if(err_width<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int width=((int)long_width);
		int32_t long_height;
		int err_height=JS_ToInt32(ctx,&long_height,argv[3]);
		if(err_height<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int height=((int)long_height);
		rlScissor(x,y,width,height);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnablePointMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlEnablePointMode();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisablePointMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisablePointMode();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableWireMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlEnableWireMode();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableWireMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableWireMode();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetLineWidth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_width;
		int err_width=JS_ToFloat64(ctx,&double_width,argv[0]);
		if(err_width<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float width=((float)double_width);
		rlSetLineWidth(width);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetLineWidth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		float returnVal=rlGetLineWidth();
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_rlEnableSmoothLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlEnableSmoothLines();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableSmoothLines(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableSmoothLines();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableStereoRender(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlEnableStereoRender();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableStereoRender(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableStereoRender();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlIsStereoRenderEnabled(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool returnVal=rlIsStereoRenderEnabled();
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_rlClearColor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_r;
		int err_r=JS_ToUint32(ctx,&long_r,argv[0]);
		if(err_r<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned char r=((unsigned char)long_r);
		uint32_t long_g;
		int err_g=JS_ToUint32(ctx,&long_g,argv[1]);
		if(err_g<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned char g=((unsigned char)long_g);
		uint32_t long_b;
		int err_b=JS_ToUint32(ctx,&long_b,argv[2]);
		if(err_b<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned char b=((unsigned char)long_b);
		uint32_t long_a;
		int err_a=JS_ToUint32(ctx,&long_a,argv[3]);
		if(err_a<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned char a=((unsigned char)long_a);
		rlClearColor(r,g,b,a);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlClearScreenBuffers(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlClearScreenBuffers();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlCheckErrors(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlCheckErrors();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetBlendMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_mode;
		int err_mode=JS_ToInt32(ctx,&long_mode,argv[0]);
		if(err_mode<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int mode=((int)long_mode);
		rlSetBlendMode(mode);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetBlendFactors(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_glSrcFactor;
		int err_glSrcFactor=JS_ToInt32(ctx,&long_glSrcFactor,argv[0]);
		if(err_glSrcFactor<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int glSrcFactor=((int)long_glSrcFactor);
		int32_t long_glDstFactor;
		int err_glDstFactor=JS_ToInt32(ctx,&long_glDstFactor,argv[1]);
		if(err_glDstFactor<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int glDstFactor=((int)long_glDstFactor);
		int32_t long_glEquation;
		int err_glEquation=JS_ToInt32(ctx,&long_glEquation,argv[2]);
		if(err_glEquation<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int glEquation=((int)long_glEquation);
		rlSetBlendFactors(glSrcFactor,glDstFactor,glEquation);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetBlendFactorsSeparate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_glSrcRGB;
		int err_glSrcRGB=JS_ToInt32(ctx,&long_glSrcRGB,argv[0]);
		if(err_glSrcRGB<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int glSrcRGB=((int)long_glSrcRGB);
		int32_t long_glDstRGB;
		int err_glDstRGB=JS_ToInt32(ctx,&long_glDstRGB,argv[1]);
		if(err_glDstRGB<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int glDstRGB=((int)long_glDstRGB);
		int32_t long_glSrcAlpha;
		int err_glSrcAlpha=JS_ToInt32(ctx,&long_glSrcAlpha,argv[2]);
		if(err_glSrcAlpha<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int glSrcAlpha=((int)long_glSrcAlpha);
		int32_t long_glDstAlpha;
		int err_glDstAlpha=JS_ToInt32(ctx,&long_glDstAlpha,argv[3]);
		if(err_glDstAlpha<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int glDstAlpha=((int)long_glDstAlpha);
		int32_t long_glEqRGB;
		int err_glEqRGB=JS_ToInt32(ctx,&long_glEqRGB,argv[4]);
		if(err_glEqRGB<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		int glEqRGB=((int)long_glEqRGB);
		int32_t long_glEqAlpha;
		int err_glEqAlpha=JS_ToInt32(ctx,&long_glEqAlpha,argv[5]);
		if(err_glEqAlpha<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		int glEqAlpha=((int)long_glEqAlpha);
		rlSetBlendFactorsSeparate(glSrcRGB,glDstRGB,glSrcAlpha,glDstAlpha,glEqRGB,glEqAlpha);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlglInit(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_width;
		int err_width=JS_ToInt32(ctx,&long_width,argv[0]);
		if(err_width<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int width=((int)long_width);
		int32_t long_height;
		int err_height=JS_ToInt32(ctx,&long_height,argv[1]);
		if(err_height<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int height=((int)long_height);
		rlglInit(width,height);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlglClose(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlglClose();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetVersion(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=rlGetVersion();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlSetFramebufferWidth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_width;
		int err_width=JS_ToInt32(ctx,&long_width,argv[0]);
		if(err_width<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int width=((int)long_width);
		rlSetFramebufferWidth(width);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetFramebufferWidth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=rlGetFramebufferWidth();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlSetFramebufferHeight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_height;
		int err_height=JS_ToInt32(ctx,&long_height,argv[0]);
		if(err_height<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int height=((int)long_height);
		rlSetFramebufferHeight(height);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetFramebufferHeight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=rlGetFramebufferHeight();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlGetTextureIdDefault(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=rlGetTextureIdDefault();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlGetShaderIdDefault(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=rlGetShaderIdDefault();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlGetShaderLocsDefault(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int * returnVal=rlGetShaderLocsDefault();
		JSValue ret;
		ret =JS_NewArray(ctx);
		int i;
		for(i=0;i<32;i++){
			JSValue js_ret=JS_NewInt32(ctx,(int32_t)((long)returnVal[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		return ret;
	}
	
	static JSValue js_rlLoadRenderBatch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_numBuffers;
		int err_numBuffers=JS_ToInt32(ctx,&long_numBuffers,argv[0]);
		if(err_numBuffers<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int numBuffers=((int)long_numBuffers);
		int32_t long_bufferElements;
		int err_bufferElements=JS_ToInt32(ctx,&long_bufferElements,argv[1]);
		if(err_bufferElements<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int bufferElements=((int)long_bufferElements);
		rlRenderBatch returnVal=rlLoadRenderBatch(numBuffers,bufferElements);
		rlRenderBatch * ptr_ret=(rlRenderBatch *)js_malloc(ctx,sizeof(rlRenderBatch));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_rlRenderBatch_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlUnloadRenderBatch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlRenderBatch * ptr_batch=(rlRenderBatch *)JS_GetOpaque(argv[0],js_rlRenderBatch_class_id);
		if(ptr_batch==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		rlRenderBatch batch=*ptr_batch;
		rlUnloadRenderBatch(batch);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawRenderBatch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlRenderBatch * batch=(rlRenderBatch *)JS_GetOpaque(argv[0],js_rlRenderBatch_class_id);
		if(batch==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type rlRenderBatch");
			return JS_EXCEPTION;
		}
		rlDrawRenderBatch(batch);
		JS_SetOpaque(argv[0],(void *)batch);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetRenderBatchActive(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlRenderBatch * batch=(rlRenderBatch *)JS_GetOpaque(argv[0],js_rlRenderBatch_class_id);
		if(batch==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type rlRenderBatch");
			return JS_EXCEPTION;
		}
		rlSetRenderBatchActive(batch);
		JS_SetOpaque(argv[0],(void *)batch);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawRenderBatchActive(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDrawRenderBatchActive();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlCheckRenderBatchLimit(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_vCount;
		int err_vCount=JS_ToInt32(ctx,&long_vCount,argv[0]);
		if(err_vCount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int vCount=((int)long_vCount);
		bool returnVal=rlCheckRenderBatchLimit(vCount);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_rlSetTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		rlSetTexture(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadVertexArray(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=rlLoadVertexArray();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlLoadVertexBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		void * buffer;
		int64_t size_buffer;
		if(JS_IsArrayBuffer(argv[0])==1){
			buffer =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_buffer,argv[0]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type void *");
			return JS_EXCEPTION;
		}
		int32_t long_size;
		int err_size=JS_ToInt32(ctx,&long_size,argv[1]);
		if(err_size<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int size=((int)long_size);
		int js_dynamic=JS_ToBool(ctx,argv[2]);
		if(js_dynamic<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not a bool");
			return JS_EXCEPTION;
		}
		bool dynamic=(bool)js_dynamic;
		int returnVal=rlLoadVertexBuffer((const void *)buffer,size,dynamic);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlLoadVertexBufferElement(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		void * buffer;
		int64_t size_buffer;
		if(JS_IsArrayBuffer(argv[0])==1){
			buffer =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_buffer,argv[0]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type void *");
			return JS_EXCEPTION;
		}
		int32_t long_size;
		int err_size=JS_ToInt32(ctx,&long_size,argv[1]);
		if(err_size<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int size=((int)long_size);
		int js_dynamic=JS_ToBool(ctx,argv[2]);
		if(js_dynamic<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not a bool");
			return JS_EXCEPTION;
		}
		bool dynamic=(bool)js_dynamic;
		int returnVal=rlLoadVertexBufferElement((const void *)buffer,size,dynamic);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlUpdateVertexBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_bufferId;
		int err_bufferId=JS_ToUint32(ctx,&long_bufferId,argv[0]);
		if(err_bufferId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int bufferId=((unsigned int)long_bufferId);
		void * data;
		int64_t size_data;
		if(JS_IsArrayBuffer(argv[1])==1){
			data =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_data,argv[1]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type void *");
			return JS_EXCEPTION;
		}
		int32_t long_dataSize;
		int err_dataSize=JS_ToInt32(ctx,&long_dataSize,argv[2]);
		if(err_dataSize<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int dataSize=((int)long_dataSize);
		int32_t long_offset;
		int err_offset=JS_ToInt32(ctx,&long_offset,argv[3]);
		if(err_offset<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int offset=((int)long_offset);
		rlUpdateVertexBuffer(bufferId,(const void *)data,dataSize,offset);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlUpdateVertexBufferElements(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		void * data;
		int64_t size_data;
		if(JS_IsArrayBuffer(argv[1])==1){
			data =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_data,argv[1]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type void *");
			return JS_EXCEPTION;
		}
		int32_t long_dataSize;
		int err_dataSize=JS_ToInt32(ctx,&long_dataSize,argv[2]);
		if(err_dataSize<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int dataSize=((int)long_dataSize);
		int32_t long_offset;
		int err_offset=JS_ToInt32(ctx,&long_offset,argv[3]);
		if(err_offset<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int offset=((int)long_offset);
		rlUpdateVertexBufferElements(id,(const void *)data,dataSize,offset);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlUnloadVertexArray(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_vaoId;
		int err_vaoId=JS_ToUint32(ctx,&long_vaoId,argv[0]);
		if(err_vaoId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int vaoId=((unsigned int)long_vaoId);
		rlUnloadVertexArray(vaoId);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlUnloadVertexBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_vboId;
		int err_vboId=JS_ToUint32(ctx,&long_vboId,argv[0]);
		if(err_vboId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int vboId=((unsigned int)long_vboId);
		rlUnloadVertexBuffer(vboId);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetVertexAttribute(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_index;
		int err_index=JS_ToUint32(ctx,&long_index,argv[0]);
		if(err_index<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int index=((unsigned int)long_index);
		int32_t long_compSize;
		int err_compSize=JS_ToInt32(ctx,&long_compSize,argv[1]);
		if(err_compSize<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int compSize=((int)long_compSize);
		int32_t long_type;
		int err_type=JS_ToInt32(ctx,&long_type,argv[2]);
		if(err_type<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int type=((int)long_type);
		int js_normalized=JS_ToBool(ctx,argv[3]);
		if(js_normalized<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not a bool");
			return JS_EXCEPTION;
		}
		bool normalized=(bool)js_normalized;
		int32_t long_stride;
		int err_stride=JS_ToInt32(ctx,&long_stride,argv[4]);
		if(err_stride<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		int stride=((int)long_stride);
		int32_t long_offset;
		int err_offset=JS_ToInt32(ctx,&long_offset,argv[5]);
		if(err_offset<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		int offset=((int)long_offset);
		rlSetVertexAttribute(index,compSize,type,normalized,stride,offset);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetVertexAttributeDivisor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_index;
		int err_index=JS_ToUint32(ctx,&long_index,argv[0]);
		if(err_index<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int index=((unsigned int)long_index);
		int32_t long_divisor;
		int err_divisor=JS_ToInt32(ctx,&long_divisor,argv[1]);
		if(err_divisor<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int divisor=((int)long_divisor);
		rlSetVertexAttributeDivisor(index,divisor);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawVertexArray(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_offset;
		int err_offset=JS_ToInt32(ctx,&long_offset,argv[0]);
		if(err_offset<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int offset=((int)long_offset);
		int32_t long_count;
		int err_count=JS_ToInt32(ctx,&long_count,argv[1]);
		if(err_count<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int count=((int)long_count);
		rlDrawVertexArray(offset,count);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawVertexArrayElements(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_offset;
		int err_offset=JS_ToInt32(ctx,&long_offset,argv[0]);
		if(err_offset<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int offset=((int)long_offset);
		int32_t long_count;
		int err_count=JS_ToInt32(ctx,&long_count,argv[1]);
		if(err_count<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int count=((int)long_count);
		void * buffer;
		int64_t size_buffer;
		if(JS_IsArrayBuffer(argv[2])==1){
			buffer =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_buffer,argv[2]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type void *");
			return JS_EXCEPTION;
		}
		rlDrawVertexArrayElements(offset,count,(const void *)buffer);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawVertexArrayInstanced(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_offset;
		int err_offset=JS_ToInt32(ctx,&long_offset,argv[0]);
		if(err_offset<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int offset=((int)long_offset);
		int32_t long_count;
		int err_count=JS_ToInt32(ctx,&long_count,argv[1]);
		if(err_count<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int count=((int)long_count);
		int32_t long_instances;
		int err_instances=JS_ToInt32(ctx,&long_instances,argv[2]);
		if(err_instances<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int instances=((int)long_instances);
		rlDrawVertexArrayInstanced(offset,count,instances);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawVertexArrayElementsInstanced(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_offset;
		int err_offset=JS_ToInt32(ctx,&long_offset,argv[0]);
		if(err_offset<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int offset=((int)long_offset);
		int32_t long_count;
		int err_count=JS_ToInt32(ctx,&long_count,argv[1]);
		if(err_count<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int count=((int)long_count);
		void * buffer;
		int64_t size_buffer;
		if(JS_IsArrayBuffer(argv[2])==1){
			buffer =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_buffer,argv[2]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type void *");
			return JS_EXCEPTION;
		}
		int32_t long_instances;
		int err_instances=JS_ToInt32(ctx,&long_instances,argv[3]);
		if(err_instances<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int instances=((int)long_instances);
		rlDrawVertexArrayElementsInstanced(offset,count,(const void *)buffer,instances);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		void * data;
		int64_t size_data;
		if(JS_IsArrayBuffer(argv[0])==1){
			data =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_data,argv[0]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type void *");
			return JS_EXCEPTION;
		}
		int32_t long_width;
		int err_width=JS_ToInt32(ctx,&long_width,argv[1]);
		if(err_width<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int width=((int)long_width);
		int32_t long_height;
		int err_height=JS_ToInt32(ctx,&long_height,argv[2]);
		if(err_height<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int height=((int)long_height);
		int32_t long_format;
		int err_format=JS_ToInt32(ctx,&long_format,argv[3]);
		if(err_format<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int format=((int)long_format);
		int32_t long_mipmapCount;
		int err_mipmapCount=JS_ToInt32(ctx,&long_mipmapCount,argv[4]);
		if(err_mipmapCount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		int mipmapCount=((int)long_mipmapCount);
		int returnVal=rlLoadTexture((const void *)data,width,height,format,mipmapCount);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlLoadTextureDepth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_width;
		int err_width=JS_ToInt32(ctx,&long_width,argv[0]);
		if(err_width<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int width=((int)long_width);
		int32_t long_height;
		int err_height=JS_ToInt32(ctx,&long_height,argv[1]);
		if(err_height<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int height=((int)long_height);
		int js_useRenderBuffer=JS_ToBool(ctx,argv[2]);
		if(js_useRenderBuffer<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not a bool");
			return JS_EXCEPTION;
		}
		bool useRenderBuffer=(bool)js_useRenderBuffer;
		int returnVal=rlLoadTextureDepth(width,height,useRenderBuffer);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlLoadTextureCubemap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		void * data;
		int64_t size_data;
		if(JS_IsArrayBuffer(argv[0])==1){
			data =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_data,argv[0]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type void *");
			return JS_EXCEPTION;
		}
		int32_t long_size;
		int err_size=JS_ToInt32(ctx,&long_size,argv[1]);
		if(err_size<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int size=((int)long_size);
		int32_t long_format;
		int err_format=JS_ToInt32(ctx,&long_format,argv[2]);
		if(err_format<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int format=((int)long_format);
		int32_t long_mipmapCount;
		int err_mipmapCount=JS_ToInt32(ctx,&long_mipmapCount,argv[3]);
		if(err_mipmapCount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int mipmapCount=((int)long_mipmapCount);
		int returnVal=rlLoadTextureCubemap((const void *)data,size,format,mipmapCount);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlUpdateTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		int32_t long_offsetX;
		int err_offsetX=JS_ToInt32(ctx,&long_offsetX,argv[1]);
		if(err_offsetX<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int offsetX=((int)long_offsetX);
		int32_t long_offsetY;
		int err_offsetY=JS_ToInt32(ctx,&long_offsetY,argv[2]);
		if(err_offsetY<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int offsetY=((int)long_offsetY);
		int32_t long_width;
		int err_width=JS_ToInt32(ctx,&long_width,argv[3]);
		if(err_width<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int width=((int)long_width);
		int32_t long_height;
		int err_height=JS_ToInt32(ctx,&long_height,argv[4]);
		if(err_height<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		int height=((int)long_height);
		int32_t long_format;
		int err_format=JS_ToInt32(ctx,&long_format,argv[5]);
		if(err_format<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		int format=((int)long_format);
		void * data;
		int64_t size_data;
		if(JS_IsArrayBuffer(argv[6])==1){
			data =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_data,argv[6]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[6] does not match type void *");
			return JS_EXCEPTION;
		}
		rlUpdateTexture(id,offsetX,offsetY,width,height,format,(const void *)data);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetGlTextureFormats(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		int32_t long_format;
		int err_format=JS_ToInt32(ctx,&long_format,argv[0]);
		if(err_format<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int format=((int)long_format);
		unsigned int * glInternalFormat;
		int64_t size_glInternalFormat;
		JSClassID glInternalFormat_class=JS_GetClassID(argv[1]);
		if(glInternalFormat_class==js_ArrayProxy_class_id){
			void * opaque_glInternalFormat=JS_GetOpaque(argv[1],js_ArrayProxy_class_id);
			ArrayProxy_class AP_glInternalFormat=((ArrayProxy_class *)opaque_glInternalFormat)[0];
			argv[1] =AP_glInternalFormat.values(ctx,AP_glInternalFormat.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[1]);
		}else if(JS_IsArray(argv[1])==1){
			if(JS_GetLength(ctx,argv[1],&size_glInternalFormat)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			glInternalFormat =(unsigned int *)js_malloc(ctx,size_glInternalFormat*sizeof(unsigned int));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)glInternalFormat);
			int i;
			for(i=0;i<size_glInternalFormat;i++){
				JSValue js_glInternalFormat=JS_GetPropertyUint32(ctx,argv[1],(uint32_t)i);
				uint32_t long_glInternalFormati;
				int err_glInternalFormati=JS_ToUint32(ctx,&long_glInternalFormati,js_glInternalFormat);
				if(err_glInternalFormati<0){
					JS_ThrowTypeError(ctx,(const char *)"js_glInternalFormat is not numeric");
					return JS_EXCEPTION;
				}
				glInternalFormat[i] =((unsigned int)long_glInternalFormati);
				JS_FreeValue(ctx,js_glInternalFormat);
			}
		}else if(JS_IsArrayBuffer(argv[1])==1){
			glInternalFormat =(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_glInternalFormat,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)glInternalFormat);
		}else{
			JSClassID classid_glInternalFormat=JS_GetClassID(argv[1]);
			if(classid_glInternalFormat==JS_CLASS_UINT16_ARRAY){
				size_t offset_glInternalFormat;
				JSValue da_glInternalFormat=JS_GetTypedArrayBuffer(ctx,argv[1],&offset_glInternalFormat,(size_t *)&size_glInternalFormat,NULL);
				glInternalFormat =(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_glInternalFormat,da_glInternalFormat);
				glInternalFormat +=offset_glInternalFormat;
				size_glInternalFormat -=offset_glInternalFormat;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_glInternalFormat);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type unsigned int *");
				return JS_EXCEPTION;
			}
		}
		unsigned int * glFormat;
		int64_t size_glFormat;
		JSClassID glFormat_class=JS_GetClassID(argv[2]);
		if(glFormat_class==js_ArrayProxy_class_id){
			void * opaque_glFormat=JS_GetOpaque(argv[2],js_ArrayProxy_class_id);
			ArrayProxy_class AP_glFormat=((ArrayProxy_class *)opaque_glFormat)[0];
			argv[2] =AP_glFormat.values(ctx,AP_glFormat.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[2]);
		}else if(JS_IsArray(argv[2])==1){
			if(JS_GetLength(ctx,argv[2],&size_glFormat)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			glFormat =(unsigned int *)js_malloc(ctx,size_glFormat*sizeof(unsigned int));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)glFormat);
			int i;
			for(i=0;i<size_glFormat;i++){
				JSValue js_glFormat=JS_GetPropertyUint32(ctx,argv[2],(uint32_t)i);
				uint32_t long_glFormati;
				int err_glFormati=JS_ToUint32(ctx,&long_glFormati,js_glFormat);
				if(err_glFormati<0){
					JS_ThrowTypeError(ctx,(const char *)"js_glFormat is not numeric");
					return JS_EXCEPTION;
				}
				glFormat[i] =((unsigned int)long_glFormati);
				JS_FreeValue(ctx,js_glFormat);
			}
		}else if(JS_IsArrayBuffer(argv[2])==1){
			glFormat =(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_glFormat,argv[2]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)glFormat);
		}else{
			JSClassID classid_glFormat=JS_GetClassID(argv[2]);
			if(classid_glFormat==JS_CLASS_UINT16_ARRAY){
				size_t offset_glFormat;
				JSValue da_glFormat=JS_GetTypedArrayBuffer(ctx,argv[2],&offset_glFormat,(size_t *)&size_glFormat,NULL);
				glFormat =(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_glFormat,da_glFormat);
				glFormat +=offset_glFormat;
				size_glFormat -=offset_glFormat;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_glFormat);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type unsigned int *");
				return JS_EXCEPTION;
			}
		}
		unsigned int * glType;
		int64_t size_glType;
		JSClassID glType_class=JS_GetClassID(argv[3]);
		if(glType_class==js_ArrayProxy_class_id){
			void * opaque_glType=JS_GetOpaque(argv[3],js_ArrayProxy_class_id);
			ArrayProxy_class AP_glType=((ArrayProxy_class *)opaque_glType)[0];
			argv[3] =AP_glType.values(ctx,AP_glType.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&argv[3]);
		}else if(JS_IsArray(argv[3])==1){
			if(JS_GetLength(ctx,argv[3],&size_glType)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			glType =(unsigned int *)js_malloc(ctx,size_glType*sizeof(unsigned int));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)glType);
			int i;
			for(i=0;i<size_glType;i++){
				JSValue js_glType=JS_GetPropertyUint32(ctx,argv[3],(uint32_t)i);
				uint32_t long_glTypei;
				int err_glTypei=JS_ToUint32(ctx,&long_glTypei,js_glType);
				if(err_glTypei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_glType is not numeric");
					return JS_EXCEPTION;
				}
				glType[i] =((unsigned int)long_glTypei);
				JS_FreeValue(ctx,js_glType);
			}
		}else if(JS_IsArrayBuffer(argv[3])==1){
			glType =(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_glType,argv[3]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)glType);
		}else{
			JSClassID classid_glType=JS_GetClassID(argv[3]);
			if(classid_glType==JS_CLASS_UINT16_ARRAY){
				size_t offset_glType;
				JSValue da_glType=JS_GetTypedArrayBuffer(ctx,argv[3],&offset_glType,(size_t *)&size_glType,NULL);
				glType =(unsigned int *)JS_GetArrayBuffer(ctx,(size_t *)&size_glType,da_glType);
				glType +=offset_glType;
				size_glType -=offset_glType;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_glType);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[3] does not match type unsigned int *");
				return JS_EXCEPTION;
			}
		}
		rlGetGlTextureFormats(format,glInternalFormat,glFormat,glType);
		memoryClear(ctx,memoryHead);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetPixelFormatName(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_format;
		int err_format=JS_ToUint32(ctx,&long_format,argv[0]);
		if(err_format<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int format=((unsigned int)long_format);
		char * returnVal=(char *)rlGetPixelFormatName(format);
		JSValue ret;
		ret =JS_NewString(ctx,(const char *)returnVal);
		return ret;
	}
	
	static JSValue js_rlUnloadTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		rlUnloadTexture(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGenTextureMipmaps(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		int32_t long_width;
		int err_width=JS_ToInt32(ctx,&long_width,argv[1]);
		if(err_width<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int width=((int)long_width);
		int32_t long_height;
		int err_height=JS_ToInt32(ctx,&long_height,argv[2]);
		if(err_height<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int height=((int)long_height);
		int32_t long_format;
		int err_format=JS_ToInt32(ctx,&long_format,argv[3]);
		if(err_format<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int format=((int)long_format);
		int * mipmaps;
		bool freesrc_mipmaps=(bool)false;
		JSValue da_mipmaps;
		int64_t size_mipmaps;
		JSClassID mipmaps_class=JS_GetClassID(argv[4]);
		if(mipmaps_class==js_ArrayProxy_class_id){
			void * opaque_mipmaps=JS_GetOpaque(argv[4],js_ArrayProxy_class_id);
			ArrayProxy_class AP_mipmaps=((ArrayProxy_class *)opaque_mipmaps)[0];
			argv[4] =AP_mipmaps.values(ctx,AP_mipmaps.opaque,(int)0,(bool)false);
			freesrc_mipmaps =(bool)true;
		}else if(JS_IsArray(argv[4])==1){
			if(JS_GetLength(ctx,argv[4],&size_mipmaps)==-1){
				return JS_EXCEPTION;
			}
			mipmaps =(int *)js_malloc(ctx,size_mipmaps*sizeof(int));
			int i;
			for(i=0;i<size_mipmaps;i++){
				JSValue js_mipmaps=JS_GetPropertyUint32(ctx,argv[4],(uint32_t)i);
				int32_t long_mipmapsi;
				int err_mipmapsi=JS_ToInt32(ctx,&long_mipmapsi,js_mipmaps);
				if(err_mipmapsi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_mipmaps is not numeric");
					return JS_EXCEPTION;
				}
				mipmaps[i] =((int)long_mipmapsi);
				JS_FreeValue(ctx,js_mipmaps);
			}
		}else if(JS_IsArrayBuffer(argv[4])==1){
			mipmaps =(int *)JS_GetArrayBuffer(ctx,(size_t *)&size_mipmaps,argv[4]);
		}else{
			JSClassID classid_mipmaps=JS_GetClassID(argv[4]);
			if(classid_mipmaps==JS_CLASS_INT16_ARRAY){
				size_t offset_mipmaps;
				da_mipmaps =JS_GetTypedArrayBuffer(ctx,argv[4],&offset_mipmaps,(size_t *)&size_mipmaps,NULL);
				mipmaps =(int *)JS_GetArrayBuffer(ctx,(size_t *)&size_mipmaps,da_mipmaps);
				mipmaps +=offset_mipmaps;
				size_mipmaps -=offset_mipmaps;
			}else{
				if(freesrc_mipmaps){
					JS_FreeValue(ctx,argv[4]);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[4] does not match type int *");
				return JS_EXCEPTION;
			}
		}
		rlGenTextureMipmaps(id,width,height,format,mipmaps);
		if(JS_IsArray(argv[4])==1){
			js_free(ctx,(void *)mipmaps);
		}else{
			JSClassID classid_mipmaps=JS_GetClassID(argv[4]);
			if(classid_mipmaps==JS_CLASS_INT16_ARRAY){
				js_free(ctx,(void *)&da_mipmaps);
			}
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlReadTexturePixels(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		int32_t long_width;
		int err_width=JS_ToInt32(ctx,&long_width,argv[1]);
		if(err_width<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int width=((int)long_width);
		int32_t long_height;
		int err_height=JS_ToInt32(ctx,&long_height,argv[2]);
		if(err_height<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int height=((int)long_height);
		int32_t long_format;
		int err_format=JS_ToInt32(ctx,&long_format,argv[3]);
		if(err_format<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int format=((int)long_format);
		void * returnVal=rlReadTexturePixels(id,width,height,format);
		JSValue ret;
		ret =JS_NewArrayBufferCopy(ctx,(const uint8_t *)returnVal,(size_t)GetPixelDataSize(width,height,format));
		return ret;
	}
	
	static JSValue js_rlReadScreenPixels(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_width;
		int err_width=JS_ToInt32(ctx,&long_width,argv[0]);
		if(err_width<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int width=((int)long_width);
		int32_t long_height;
		int err_height=JS_ToInt32(ctx,&long_height,argv[1]);
		if(err_height<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int height=((int)long_height);
		char * returnVal=rlReadScreenPixels(width,height);
		JSValue ret;
		ret =JS_NewString(ctx,(const char *)returnVal);
		return ret;
	}
	
	static JSValue js_rlLoadFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=rlLoadFramebuffer();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlFramebufferAttach(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_fboId;
		int err_fboId=JS_ToUint32(ctx,&long_fboId,argv[0]);
		if(err_fboId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int fboId=((unsigned int)long_fboId);
		uint32_t long_texId;
		int err_texId=JS_ToUint32(ctx,&long_texId,argv[1]);
		if(err_texId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int texId=((unsigned int)long_texId);
		int32_t long_attachType;
		int err_attachType=JS_ToInt32(ctx,&long_attachType,argv[2]);
		if(err_attachType<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int attachType=((int)long_attachType);
		int32_t long_texType;
		int err_texType=JS_ToInt32(ctx,&long_texType,argv[3]);
		if(err_texType<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int texType=((int)long_texType);
		int32_t long_mipLevel;
		int err_mipLevel=JS_ToInt32(ctx,&long_mipLevel,argv[4]);
		if(err_mipLevel<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		int mipLevel=((int)long_mipLevel);
		rlFramebufferAttach(fboId,texId,attachType,texType,mipLevel);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlFramebufferComplete(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		bool returnVal=rlFramebufferComplete(id);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_rlUnloadFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		rlUnloadFramebuffer(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadShaderCode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		char * vsCode;
		int64_t size_vsCode;
		if(JS_IsString(argv[0])==1){
			vsCode =(char *)JS_ToCStringLen(ctx,(size_t *)&size_vsCode,argv[0]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)vsCode);
		}else if(JS_IsArrayBuffer(argv[0])==1){
			vsCode =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_vsCode,argv[0]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)vsCode);
		}else{
			JSClassID classid_vsCode=JS_GetClassID(argv[0]);
			if(classid_vsCode==JS_CLASS_INT8_ARRAY){
				size_t offset_vsCode;
				JSValue da_vsCode=JS_GetTypedArrayBuffer(ctx,argv[0],&offset_vsCode,(size_t *)&size_vsCode,NULL);
				vsCode =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_vsCode,da_vsCode);
				vsCode +=offset_vsCode;
				size_vsCode -=offset_vsCode;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_vsCode);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		char * fsCode;
		int64_t size_fsCode;
		if(JS_IsString(argv[1])==1){
			fsCode =(char *)JS_ToCStringLen(ctx,(size_t *)&size_fsCode,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeCString,(void *)fsCode);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			fsCode =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_fsCode,argv[1]);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)fsCode);
		}else{
			JSClassID classid_fsCode=JS_GetClassID(argv[1]);
			if(classid_fsCode==JS_CLASS_INT8_ARRAY){
				size_t offset_fsCode;
				JSValue da_fsCode=JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fsCode,(size_t *)&size_fsCode,NULL);
				fsCode =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_fsCode,da_fsCode);
				fsCode +=offset_fsCode;
				size_fsCode -=offset_fsCode;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_fsCode);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=rlLoadShaderCode((const char *)vsCode,(const char *)fsCode);
		memoryClear(ctx,memoryHead);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlCompileShader(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		char * shaderCode;
		JSValue da_shaderCode;
		int64_t size_shaderCode;
		if(JS_IsString(argv[0])==1){
			shaderCode =(char *)JS_ToCStringLen(ctx,(size_t *)&size_shaderCode,argv[0]);
		}else if(JS_IsArrayBuffer(argv[0])==1){
			shaderCode =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_shaderCode,argv[0]);
		}else{
			JSClassID classid_shaderCode=JS_GetClassID(argv[0]);
			if(classid_shaderCode==JS_CLASS_INT8_ARRAY){
				size_t offset_shaderCode;
				da_shaderCode =JS_GetTypedArrayBuffer(ctx,argv[0],&offset_shaderCode,(size_t *)&size_shaderCode,NULL);
				shaderCode =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_shaderCode,da_shaderCode);
				shaderCode +=offset_shaderCode;
				size_shaderCode -=offset_shaderCode;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int32_t long_type;
		int err_type=JS_ToInt32(ctx,&long_type,argv[1]);
		if(err_type<0){
			if(JS_IsArray(argv[0])==1){
				js_free(ctx,(void *)shaderCode);
			}else if(JS_IsString(argv[0])==1){
				JS_FreeCString(ctx,(const char *)shaderCode);
			}else{
				JSClassID classid_shaderCode=JS_GetClassID(argv[0]);
				if(classid_shaderCode==JS_CLASS_INT8_ARRAY){
					js_free(ctx,(void *)&da_shaderCode);
				}
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int type=((int)long_type);
		int returnVal=rlCompileShader((const char *)shaderCode,type);
		if(JS_IsArray(argv[0])==1){
			js_free(ctx,(void *)shaderCode);
		}else if(JS_IsString(argv[0])==1){
			JS_FreeCString(ctx,(const char *)shaderCode);
		}else{
			JSClassID classid_shaderCode=JS_GetClassID(argv[0]);
			if(classid_shaderCode==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_shaderCode);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlLoadShaderProgram(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_vShaderId;
		int err_vShaderId=JS_ToUint32(ctx,&long_vShaderId,argv[0]);
		if(err_vShaderId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int vShaderId=((unsigned int)long_vShaderId);
		uint32_t long_fShaderId;
		int err_fShaderId=JS_ToUint32(ctx,&long_fShaderId,argv[1]);
		if(err_fShaderId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int fShaderId=((unsigned int)long_fShaderId);
		int returnVal=rlLoadShaderProgram(vShaderId,fShaderId);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlUnloadShaderProgram(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		rlUnloadShaderProgram(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetLocationUniform(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_shaderId;
		int err_shaderId=JS_ToUint32(ctx,&long_shaderId,argv[0]);
		if(err_shaderId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int shaderId=((unsigned int)long_shaderId);
		char * uniformName;
		JSValue da_uniformName;
		int64_t size_uniformName;
		if(JS_IsString(argv[1])==1){
			uniformName =(char *)JS_ToCStringLen(ctx,(size_t *)&size_uniformName,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			uniformName =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_uniformName,argv[1]);
		}else{
			JSClassID classid_uniformName=JS_GetClassID(argv[1]);
			if(classid_uniformName==JS_CLASS_INT8_ARRAY){
				size_t offset_uniformName;
				da_uniformName =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_uniformName,(size_t *)&size_uniformName,NULL);
				uniformName =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_uniformName,da_uniformName);
				uniformName +=offset_uniformName;
				size_uniformName -=offset_uniformName;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=rlGetLocationUniform(shaderId,(const char *)uniformName);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)uniformName);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)uniformName);
		}else{
			JSClassID classid_uniformName=JS_GetClassID(argv[1]);
			if(classid_uniformName==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_uniformName);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlGetLocationAttrib(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_shaderId;
		int err_shaderId=JS_ToUint32(ctx,&long_shaderId,argv[0]);
		if(err_shaderId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int shaderId=((unsigned int)long_shaderId);
		char * attribName;
		JSValue da_attribName;
		int64_t size_attribName;
		if(JS_IsString(argv[1])==1){
			attribName =(char *)JS_ToCStringLen(ctx,(size_t *)&size_attribName,argv[1]);
		}else if(JS_IsArrayBuffer(argv[1])==1){
			attribName =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_attribName,argv[1]);
		}else{
			JSClassID classid_attribName=JS_GetClassID(argv[1]);
			if(classid_attribName==JS_CLASS_INT8_ARRAY){
				size_t offset_attribName;
				da_attribName =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_attribName,(size_t *)&size_attribName,NULL);
				attribName =(char *)JS_GetArrayBuffer(ctx,(size_t *)&size_attribName,da_attribName);
				attribName +=offset_attribName;
				size_attribName -=offset_attribName;
			}else{
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type char *");
				return JS_EXCEPTION;
			}
		}
		int returnVal=rlGetLocationAttrib(shaderId,(const char *)attribName);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)attribName);
		}else if(JS_IsString(argv[1])==1){
			JS_FreeCString(ctx,(const char *)attribName);
		}else{
			JSClassID classid_attribName=JS_GetClassID(argv[1]);
			if(classid_attribName==JS_CLASS_INT8_ARRAY){
				js_free(ctx,(void *)&da_attribName);
			}
		}
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlSetUniformMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_locIndex;
		int err_locIndex=JS_ToInt32(ctx,&long_locIndex,argv[0]);
		if(err_locIndex<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int locIndex=((int)long_locIndex);
		Matrix * ptr_mat=(Matrix *)JS_GetOpaque(argv[1],js_Matrix_class_id);
		if(ptr_mat==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix mat=*ptr_mat;
		rlSetUniformMatrix(locIndex,mat);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetUniformMatrices(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_locIndex;
		int err_locIndex=JS_ToInt32(ctx,&long_locIndex,argv[0]);
		if(err_locIndex<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int locIndex=((int)long_locIndex);
		Matrix * mat;
		bool freesrc_mat=(bool)false;
		int64_t size_mat;
		JSClassID mat_class=JS_GetClassID(argv[1]);
		if(mat_class==js_ArrayProxy_class_id){
			void * opaque_mat=JS_GetOpaque(argv[1],js_ArrayProxy_class_id);
			ArrayProxy_class AP_mat=((ArrayProxy_class *)opaque_mat)[0];
			argv[1] =AP_mat.values(ctx,AP_mat.opaque,(int)0,(bool)false);
			freesrc_mat =(bool)true;
		}else if(JS_IsArray(argv[1])==1){
			if(JS_GetLength(ctx,argv[1],&size_mat)==-1){
				return JS_EXCEPTION;
			}
			mat =(Matrix *)js_malloc(ctx,size_mat*sizeof(Matrix));
			int i;
			for(i=0;i<size_mat;i++){
				JSValue js_mat=JS_GetPropertyUint32(ctx,argv[1],(uint32_t)i);
				Matrix * ptr_mati=(Matrix *)JS_GetOpaque(js_mat,js_Matrix_class_id);
				if(ptr_mati==NULL){
					JS_ThrowTypeError(ctx,(const char *)"js_mat does not allow null");
					return JS_EXCEPTION;
				}
				mat[i] =*ptr_mati;
				JS_FreeValue(ctx,js_mat);
			}
		}else if(JS_IsArrayBuffer(argv[1])==1){
			mat =(Matrix *)JS_GetArrayBuffer(ctx,(size_t *)&size_mat,argv[1]);
		}else{
			if(freesrc_mat){
				JS_FreeValue(ctx,argv[1]);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type Matrix *");
			return JS_EXCEPTION;
		}
		int32_t long_count;
		int err_count=JS_ToInt32(ctx,&long_count,argv[2]);
		if(err_count<0){
			if(JS_IsArray(argv[1])==1){
				js_free(ctx,(void *)mat);
			}
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int count=((int)long_count);
		rlSetUniformMatrices(locIndex,(const Matrix *)mat,count);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)mat);
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetUniformSampler(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_locIndex;
		int err_locIndex=JS_ToInt32(ctx,&long_locIndex,argv[0]);
		if(err_locIndex<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int locIndex=((int)long_locIndex);
		uint32_t long_textureId;
		int err_textureId=JS_ToUint32(ctx,&long_textureId,argv[1]);
		if(err_textureId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int textureId=((unsigned int)long_textureId);
		rlSetUniformSampler(locIndex,textureId);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetShader(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		int * locs;
		bool freesrc_locs=(bool)false;
		JSValue da_locs;
		int64_t size_locs;
		JSClassID locs_class=JS_GetClassID(argv[1]);
		if(locs_class==js_ArrayProxy_class_id){
			void * opaque_locs=JS_GetOpaque(argv[1],js_ArrayProxy_class_id);
			ArrayProxy_class AP_locs=((ArrayProxy_class *)opaque_locs)[0];
			argv[1] =AP_locs.values(ctx,AP_locs.opaque,(int)0,(bool)false);
			freesrc_locs =(bool)true;
		}else if(JS_IsArray(argv[1])==1){
			if(JS_GetLength(ctx,argv[1],&size_locs)==-1){
				return JS_EXCEPTION;
			}
			locs =(int *)js_malloc(ctx,size_locs*sizeof(int));
			int i;
			for(i=0;i<size_locs;i++){
				JSValue js_locs=JS_GetPropertyUint32(ctx,argv[1],(uint32_t)i);
				int32_t long_locsi;
				int err_locsi=JS_ToInt32(ctx,&long_locsi,js_locs);
				if(err_locsi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_locs is not numeric");
					return JS_EXCEPTION;
				}
				locs[i] =((int)long_locsi);
				JS_FreeValue(ctx,js_locs);
			}
		}else if(JS_IsArrayBuffer(argv[1])==1){
			locs =(int *)JS_GetArrayBuffer(ctx,(size_t *)&size_locs,argv[1]);
		}else{
			JSClassID classid_locs=JS_GetClassID(argv[1]);
			if(classid_locs==JS_CLASS_INT16_ARRAY){
				size_t offset_locs;
				da_locs =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_locs,(size_t *)&size_locs,NULL);
				locs =(int *)JS_GetArrayBuffer(ctx,(size_t *)&size_locs,da_locs);
				locs +=offset_locs;
				size_locs -=offset_locs;
			}else{
				if(freesrc_locs){
					JS_FreeValue(ctx,argv[1]);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type int *");
				return JS_EXCEPTION;
			}
		}
		rlSetShader(id,locs);
		if(JS_IsArray(argv[1])==1){
			js_free(ctx,(void *)locs);
		}else{
			JSClassID classid_locs=JS_GetClassID(argv[1]);
			if(classid_locs==JS_CLASS_INT16_ARRAY){
				js_free(ctx,(void *)&da_locs);
			}
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadComputeShaderProgram(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_shaderId;
		int err_shaderId=JS_ToUint32(ctx,&long_shaderId,argv[0]);
		if(err_shaderId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int shaderId=((unsigned int)long_shaderId);
		int returnVal=rlLoadComputeShaderProgram(shaderId);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlComputeShaderDispatch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_groupX;
		int err_groupX=JS_ToUint32(ctx,&long_groupX,argv[0]);
		if(err_groupX<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int groupX=((unsigned int)long_groupX);
		uint32_t long_groupY;
		int err_groupY=JS_ToUint32(ctx,&long_groupY,argv[1]);
		if(err_groupY<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int groupY=((unsigned int)long_groupY);
		uint32_t long_groupZ;
		int err_groupZ=JS_ToUint32(ctx,&long_groupZ,argv[2]);
		if(err_groupZ<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int groupZ=((unsigned int)long_groupZ);
		rlComputeShaderDispatch(groupX,groupY,groupZ);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_size;
		int err_size=JS_ToUint32(ctx,&long_size,argv[0]);
		if(err_size<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int size=((unsigned int)long_size);
		void * data;
		int64_t size_data;
		if(JS_IsArrayBuffer(argv[1])==1){
			data =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_data,argv[1]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type void *");
			return JS_EXCEPTION;
		}
		int32_t long_usageHint;
		int err_usageHint=JS_ToInt32(ctx,&long_usageHint,argv[2]);
		if(err_usageHint<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int usageHint=((int)long_usageHint);
		int returnVal=rlLoadShaderBuffer(size,(const void *)data,usageHint);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlUnloadShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_ssboId;
		int err_ssboId=JS_ToUint32(ctx,&long_ssboId,argv[0]);
		if(err_ssboId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int ssboId=((unsigned int)long_ssboId);
		rlUnloadShaderBuffer(ssboId);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlUpdateShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		void * data;
		int64_t size_data;
		if(JS_IsArrayBuffer(argv[1])==1){
			data =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_data,argv[1]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type void *");
			return JS_EXCEPTION;
		}
		uint32_t long_dataSize;
		int err_dataSize=JS_ToUint32(ctx,&long_dataSize,argv[2]);
		if(err_dataSize<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int dataSize=((unsigned int)long_dataSize);
		uint32_t long_offset;
		int err_offset=JS_ToUint32(ctx,&long_offset,argv[3]);
		if(err_offset<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int offset=((unsigned int)long_offset);
		rlUpdateShaderBuffer(id,(const void *)data,dataSize,offset);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlBindShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		uint32_t long_index;
		int err_index=JS_ToUint32(ctx,&long_index,argv[1]);
		if(err_index<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int index=((unsigned int)long_index);
		rlBindShaderBuffer(id,index);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlReadShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		void * dest;
		int64_t size_dest;
		if(JS_IsArrayBuffer(argv[1])==1){
			dest =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_dest,argv[1]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type void *");
			return JS_EXCEPTION;
		}
		uint32_t long_count;
		int err_count=JS_ToUint32(ctx,&long_count,argv[2]);
		if(err_count<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int count=((unsigned int)long_count);
		uint32_t long_offset;
		int err_offset=JS_ToUint32(ctx,&long_offset,argv[3]);
		if(err_offset<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int offset=((unsigned int)long_offset);
		rlReadShaderBuffer(id,dest,count,offset);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlCopyShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_destId;
		int err_destId=JS_ToUint32(ctx,&long_destId,argv[0]);
		if(err_destId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int destId=((unsigned int)long_destId);
		uint32_t long_srcId;
		int err_srcId=JS_ToUint32(ctx,&long_srcId,argv[1]);
		if(err_srcId<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int srcId=((unsigned int)long_srcId);
		uint32_t long_destOffset;
		int err_destOffset=JS_ToUint32(ctx,&long_destOffset,argv[2]);
		if(err_destOffset<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int destOffset=((unsigned int)long_destOffset);
		uint32_t long_srcOffset;
		int err_srcOffset=JS_ToUint32(ctx,&long_srcOffset,argv[3]);
		if(err_srcOffset<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int srcOffset=((unsigned int)long_srcOffset);
		uint32_t long_count;
		int err_count=JS_ToUint32(ctx,&long_count,argv[4]);
		if(err_count<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int count=((unsigned int)long_count);
		rlCopyShaderBuffer(destId,srcId,destOffset,srcOffset,count);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetShaderBufferSize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		int returnVal=rlGetShaderBufferSize(id);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlBindImageTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		uint32_t long_id;
		int err_id=JS_ToUint32(ctx,&long_id,argv[0]);
		if(err_id<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int id=((unsigned int)long_id);
		uint32_t long_index;
		int err_index=JS_ToUint32(ctx,&long_index,argv[1]);
		if(err_index<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		unsigned int index=((unsigned int)long_index);
		int32_t long_format;
		int err_format=JS_ToInt32(ctx,&long_format,argv[2]);
		if(err_format<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int format=((int)long_format);
		int js_readonly=JS_ToBool(ctx,argv[3]);
		if(js_readonly<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not a bool");
			return JS_EXCEPTION;
		}
		bool readonly=(bool)js_readonly;
		rlBindImageTexture(id,index,format,readonly);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetMatrixModelview(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix returnVal=rlGetMatrixModelview();
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlGetMatrixProjection(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix returnVal=rlGetMatrixProjection();
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlGetMatrixTransform(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix returnVal=rlGetMatrixTransform();
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlGetMatrixProjectionStereo(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_eye;
		int err_eye=JS_ToInt32(ctx,&long_eye,argv[0]);
		if(err_eye<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int eye=((int)long_eye);
		Matrix returnVal=rlGetMatrixProjectionStereo(eye);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlGetMatrixViewOffsetStereo(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_eye;
		int err_eye=JS_ToInt32(ctx,&long_eye,argv[0]);
		if(err_eye<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int eye=((int)long_eye);
		Matrix returnVal=rlGetMatrixViewOffsetStereo(eye);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlSetMatrixProjection(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_proj=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_proj==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix proj=*ptr_proj;
		rlSetMatrixProjection(proj);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetMatrixModelview(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_view=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_view==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix view=*ptr_view;
		rlSetMatrixModelview(view);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetMatrixProjectionStereo(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_right=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_right==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix right=*ptr_right;
		Matrix * ptr_left=(Matrix *)JS_GetOpaque(argv[1],js_Matrix_class_id);
		if(ptr_left==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix left=*ptr_left;
		rlSetMatrixProjectionStereo(right,left);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetMatrixViewOffsetStereo(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_right=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_right==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix right=*ptr_right;
		Matrix * ptr_left=(Matrix *)JS_GetOpaque(argv[1],js_Matrix_class_id);
		if(ptr_left==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix left=*ptr_left;
		rlSetMatrixViewOffsetStereo(right,left);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadDrawCube(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlLoadDrawCube();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadDrawQuad(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlLoadDrawQuad();
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry jsrlgl_funcs[]={
		JS_CFUNC_DEF("rlMatrixMode",1,js_rlMatrixMode),
		JS_CFUNC_DEF("rlPushMatrix",0,js_rlPushMatrix),
		JS_CFUNC_DEF("rlPopMatrix",0,js_rlPopMatrix),
		JS_CFUNC_DEF("rlLoadIdentity",0,js_rlLoadIdentity),
		JS_CFUNC_DEF("rlTranslatef",3,js_rlTranslatef),
		JS_CFUNC_DEF("rlRotatef",4,js_rlRotatef),
		JS_CFUNC_DEF("rlScalef",3,js_rlScalef),
		JS_CFUNC_DEF("rlMultMatrixf",1,js_rlMultMatrixf),
		JS_CFUNC_DEF("rlFrustum",6,js_rlFrustum),
		JS_CFUNC_DEF("rlOrtho",6,js_rlOrtho),
		JS_CFUNC_DEF("rlViewport",4,js_rlViewport),
		JS_CFUNC_DEF("rlSetClipPlanes",2,js_rlSetClipPlanes),
		JS_CFUNC_DEF("rlGetCullDistanceNear",0,js_rlGetCullDistanceNear),
		JS_CFUNC_DEF("rlGetCullDistanceFar",0,js_rlGetCullDistanceFar),
		JS_CFUNC_DEF("rlBegin",1,js_rlBegin),
		JS_CFUNC_DEF("rlEnd",0,js_rlEnd),
		JS_CFUNC_DEF("rlVertex2i",2,js_rlVertex2i),
		JS_CFUNC_DEF("rlVertex2f",2,js_rlVertex2f),
		JS_CFUNC_DEF("rlVertex3f",3,js_rlVertex3f),
		JS_CFUNC_DEF("rlTexCoord2f",2,js_rlTexCoord2f),
		JS_CFUNC_DEF("rlNormal3f",3,js_rlNormal3f),
		JS_CFUNC_DEF("rlColor4ub",4,js_rlColor4ub),
		JS_CFUNC_DEF("rlColor3f",3,js_rlColor3f),
		JS_CFUNC_DEF("rlColor4f",4,js_rlColor4f),
		JS_CFUNC_DEF("rlEnableVertexArray",1,js_rlEnableVertexArray),
		JS_CFUNC_DEF("rlDisableVertexArray",0,js_rlDisableVertexArray),
		JS_CFUNC_DEF("rlEnableVertexBuffer",1,js_rlEnableVertexBuffer),
		JS_CFUNC_DEF("rlDisableVertexBuffer",0,js_rlDisableVertexBuffer),
		JS_CFUNC_DEF("rlEnableVertexBufferElement",1,js_rlEnableVertexBufferElement),
		JS_CFUNC_DEF("rlDisableVertexBufferElement",0,js_rlDisableVertexBufferElement),
		JS_CFUNC_DEF("rlEnableVertexAttribute",1,js_rlEnableVertexAttribute),
		JS_CFUNC_DEF("rlDisableVertexAttribute",1,js_rlDisableVertexAttribute),
		JS_CFUNC_DEF("rlActiveTextureSlot",1,js_rlActiveTextureSlot),
		JS_CFUNC_DEF("rlEnableTexture",1,js_rlEnableTexture),
		JS_CFUNC_DEF("rlDisableTexture",0,js_rlDisableTexture),
		JS_CFUNC_DEF("rlEnableTextureCubemap",1,js_rlEnableTextureCubemap),
		JS_CFUNC_DEF("rlDisableTextureCubemap",0,js_rlDisableTextureCubemap),
		JS_CFUNC_DEF("rlTextureParameters",3,js_rlTextureParameters),
		JS_CFUNC_DEF("rlCubemapParameters",3,js_rlCubemapParameters),
		JS_CFUNC_DEF("rlEnableShader",1,js_rlEnableShader),
		JS_CFUNC_DEF("rlDisableShader",0,js_rlDisableShader),
		JS_CFUNC_DEF("rlEnableFramebuffer",1,js_rlEnableFramebuffer),
		JS_CFUNC_DEF("rlDisableFramebuffer",0,js_rlDisableFramebuffer),
		JS_CFUNC_DEF("rlGetActiveFramebuffer",0,js_rlGetActiveFramebuffer),
		JS_CFUNC_DEF("rlActiveDrawBuffers",1,js_rlActiveDrawBuffers),
		JS_CFUNC_DEF("rlBlitFramebuffer",9,js_rlBlitFramebuffer),
		JS_CFUNC_DEF("rlBindFramebuffer",2,js_rlBindFramebuffer),
		JS_CFUNC_DEF("rlEnableColorBlend",0,js_rlEnableColorBlend),
		JS_CFUNC_DEF("rlDisableColorBlend",0,js_rlDisableColorBlend),
		JS_CFUNC_DEF("rlEnableDepthTest",0,js_rlEnableDepthTest),
		JS_CFUNC_DEF("rlDisableDepthTest",0,js_rlDisableDepthTest),
		JS_CFUNC_DEF("rlEnableDepthMask",0,js_rlEnableDepthMask),
		JS_CFUNC_DEF("rlDisableDepthMask",0,js_rlDisableDepthMask),
		JS_CFUNC_DEF("rlEnableBackfaceCulling",0,js_rlEnableBackfaceCulling),
		JS_CFUNC_DEF("rlDisableBackfaceCulling",0,js_rlDisableBackfaceCulling),
		JS_CFUNC_DEF("rlColorMask",4,js_rlColorMask),
		JS_CFUNC_DEF("rlSetCullFace",1,js_rlSetCullFace),
		JS_CFUNC_DEF("rlEnableScissorTest",0,js_rlEnableScissorTest),
		JS_CFUNC_DEF("rlDisableScissorTest",0,js_rlDisableScissorTest),
		JS_CFUNC_DEF("rlScissor",4,js_rlScissor),
		JS_CFUNC_DEF("rlEnablePointMode",0,js_rlEnablePointMode),
		JS_CFUNC_DEF("rlDisablePointMode",0,js_rlDisablePointMode),
		JS_CFUNC_DEF("rlEnableWireMode",0,js_rlEnableWireMode),
		JS_CFUNC_DEF("rlDisableWireMode",0,js_rlDisableWireMode),
		JS_CFUNC_DEF("rlSetLineWidth",1,js_rlSetLineWidth),
		JS_CFUNC_DEF("rlGetLineWidth",0,js_rlGetLineWidth),
		JS_CFUNC_DEF("rlEnableSmoothLines",0,js_rlEnableSmoothLines),
		JS_CFUNC_DEF("rlDisableSmoothLines",0,js_rlDisableSmoothLines),
		JS_CFUNC_DEF("rlEnableStereoRender",0,js_rlEnableStereoRender),
		JS_CFUNC_DEF("rlDisableStereoRender",0,js_rlDisableStereoRender),
		JS_CFUNC_DEF("rlIsStereoRenderEnabled",0,js_rlIsStereoRenderEnabled),
		JS_CFUNC_DEF("rlClearColor",4,js_rlClearColor),
		JS_CFUNC_DEF("rlClearScreenBuffers",0,js_rlClearScreenBuffers),
		JS_CFUNC_DEF("rlCheckErrors",0,js_rlCheckErrors),
		JS_CFUNC_DEF("rlSetBlendMode",1,js_rlSetBlendMode),
		JS_CFUNC_DEF("rlSetBlendFactors",3,js_rlSetBlendFactors),
		JS_CFUNC_DEF("rlSetBlendFactorsSeparate",6,js_rlSetBlendFactorsSeparate),
		JS_CFUNC_DEF("rlglInit",2,js_rlglInit),
		JS_CFUNC_DEF("rlglClose",0,js_rlglClose),
		JS_CFUNC_DEF("rlGetVersion",0,js_rlGetVersion),
		JS_CFUNC_DEF("rlSetFramebufferWidth",1,js_rlSetFramebufferWidth),
		JS_CFUNC_DEF("rlGetFramebufferWidth",0,js_rlGetFramebufferWidth),
		JS_CFUNC_DEF("rlSetFramebufferHeight",1,js_rlSetFramebufferHeight),
		JS_CFUNC_DEF("rlGetFramebufferHeight",0,js_rlGetFramebufferHeight),
		JS_CFUNC_DEF("rlGetTextureIdDefault",0,js_rlGetTextureIdDefault),
		JS_CFUNC_DEF("rlGetShaderIdDefault",0,js_rlGetShaderIdDefault),
		JS_CFUNC_DEF("rlGetShaderLocsDefault",0,js_rlGetShaderLocsDefault),
		JS_CFUNC_DEF("rlLoadRenderBatch",2,js_rlLoadRenderBatch),
		JS_CFUNC_DEF("rlUnloadRenderBatch",1,js_rlUnloadRenderBatch),
		JS_CFUNC_DEF("rlDrawRenderBatch",1,js_rlDrawRenderBatch),
		JS_CFUNC_DEF("rlSetRenderBatchActive",1,js_rlSetRenderBatchActive),
		JS_CFUNC_DEF("rlDrawRenderBatchActive",0,js_rlDrawRenderBatchActive),
		JS_CFUNC_DEF("rlCheckRenderBatchLimit",1,js_rlCheckRenderBatchLimit),
		JS_CFUNC_DEF("rlSetTexture",1,js_rlSetTexture),
		JS_CFUNC_DEF("rlLoadVertexArray",0,js_rlLoadVertexArray),
		JS_CFUNC_DEF("rlLoadVertexBuffer",3,js_rlLoadVertexBuffer),
		JS_CFUNC_DEF("rlLoadVertexBufferElement",3,js_rlLoadVertexBufferElement),
		JS_CFUNC_DEF("rlUpdateVertexBuffer",4,js_rlUpdateVertexBuffer),
		JS_CFUNC_DEF("rlUpdateVertexBufferElements",4,js_rlUpdateVertexBufferElements),
		JS_CFUNC_DEF("rlUnloadVertexArray",1,js_rlUnloadVertexArray),
		JS_CFUNC_DEF("rlUnloadVertexBuffer",1,js_rlUnloadVertexBuffer),
		JS_CFUNC_DEF("rlSetVertexAttribute",6,js_rlSetVertexAttribute),
		JS_CFUNC_DEF("rlSetVertexAttributeDivisor",2,js_rlSetVertexAttributeDivisor),
		JS_CFUNC_DEF("rlDrawVertexArray",2,js_rlDrawVertexArray),
		JS_CFUNC_DEF("rlDrawVertexArrayElements",3,js_rlDrawVertexArrayElements),
		JS_CFUNC_DEF("rlDrawVertexArrayInstanced",3,js_rlDrawVertexArrayInstanced),
		JS_CFUNC_DEF("rlDrawVertexArrayElementsInstanced",4,js_rlDrawVertexArrayElementsInstanced),
		JS_CFUNC_DEF("rlLoadTexture",5,js_rlLoadTexture),
		JS_CFUNC_DEF("rlLoadTextureDepth",3,js_rlLoadTextureDepth),
		JS_CFUNC_DEF("rlLoadTextureCubemap",4,js_rlLoadTextureCubemap),
		JS_CFUNC_DEF("rlUpdateTexture",7,js_rlUpdateTexture),
		JS_CFUNC_DEF("rlGetGlTextureFormats",4,js_rlGetGlTextureFormats),
		JS_CFUNC_DEF("rlGetPixelFormatName",1,js_rlGetPixelFormatName),
		JS_CFUNC_DEF("rlUnloadTexture",1,js_rlUnloadTexture),
		JS_CFUNC_DEF("rlGenTextureMipmaps",5,js_rlGenTextureMipmaps),
		JS_CFUNC_DEF("rlReadTexturePixels",4,js_rlReadTexturePixels),
		JS_CFUNC_DEF("rlReadScreenPixels",2,js_rlReadScreenPixels),
		JS_CFUNC_DEF("rlLoadFramebuffer",0,js_rlLoadFramebuffer),
		JS_CFUNC_DEF("rlFramebufferAttach",5,js_rlFramebufferAttach),
		JS_CFUNC_DEF("rlFramebufferComplete",1,js_rlFramebufferComplete),
		JS_CFUNC_DEF("rlUnloadFramebuffer",1,js_rlUnloadFramebuffer),
		JS_CFUNC_DEF("rlLoadShaderCode",2,js_rlLoadShaderCode),
		JS_CFUNC_DEF("rlCompileShader",2,js_rlCompileShader),
		JS_CFUNC_DEF("rlLoadShaderProgram",2,js_rlLoadShaderProgram),
		JS_CFUNC_DEF("rlUnloadShaderProgram",1,js_rlUnloadShaderProgram),
		JS_CFUNC_DEF("rlGetLocationUniform",2,js_rlGetLocationUniform),
		JS_CFUNC_DEF("rlGetLocationAttrib",2,js_rlGetLocationAttrib),
		JS_CFUNC_DEF("rlSetUniformMatrix",2,js_rlSetUniformMatrix),
		JS_CFUNC_DEF("rlSetUniformMatrices",3,js_rlSetUniformMatrices),
		JS_CFUNC_DEF("rlSetUniformSampler",2,js_rlSetUniformSampler),
		JS_CFUNC_DEF("rlSetShader",2,js_rlSetShader),
		JS_CFUNC_DEF("rlLoadComputeShaderProgram",1,js_rlLoadComputeShaderProgram),
		JS_CFUNC_DEF("rlComputeShaderDispatch",3,js_rlComputeShaderDispatch),
		JS_CFUNC_DEF("rlLoadShaderBuffer",3,js_rlLoadShaderBuffer),
		JS_CFUNC_DEF("rlUnloadShaderBuffer",1,js_rlUnloadShaderBuffer),
		JS_CFUNC_DEF("rlUpdateShaderBuffer",4,js_rlUpdateShaderBuffer),
		JS_CFUNC_DEF("rlBindShaderBuffer",2,js_rlBindShaderBuffer),
		JS_CFUNC_DEF("rlReadShaderBuffer",4,js_rlReadShaderBuffer),
		JS_CFUNC_DEF("rlCopyShaderBuffer",5,js_rlCopyShaderBuffer),
		JS_CFUNC_DEF("rlGetShaderBufferSize",1,js_rlGetShaderBufferSize),
		JS_CFUNC_DEF("rlBindImageTexture",4,js_rlBindImageTexture),
		JS_CFUNC_DEF("rlGetMatrixModelview",0,js_rlGetMatrixModelview),
		JS_CFUNC_DEF("rlGetMatrixProjection",0,js_rlGetMatrixProjection),
		JS_CFUNC_DEF("rlGetMatrixTransform",0,js_rlGetMatrixTransform),
		JS_CFUNC_DEF("rlGetMatrixProjectionStereo",1,js_rlGetMatrixProjectionStereo),
		JS_CFUNC_DEF("rlGetMatrixViewOffsetStereo",1,js_rlGetMatrixViewOffsetStereo),
		JS_CFUNC_DEF("rlSetMatrixProjection",1,js_rlSetMatrixProjection),
		JS_CFUNC_DEF("rlSetMatrixModelview",1,js_rlSetMatrixModelview),
		JS_CFUNC_DEF("rlSetMatrixProjectionStereo",2,js_rlSetMatrixProjectionStereo),
		JS_CFUNC_DEF("rlSetMatrixViewOffsetStereo",2,js_rlSetMatrixViewOffsetStereo),
		JS_CFUNC_DEF("rlLoadDrawCube",0,js_rlLoadDrawCube),
		JS_CFUNC_DEF("rlLoadDrawQuad",0,js_rlLoadDrawQuad)
	};
	
	static int js_js_rlgl_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsrlgl_funcs);
		JS_SetModuleExportList(ctx,m,jsrlgl_funcs,(int)listcount);
		js_declare_rlVertexBuffer(ctx,m);
		JSValue rlVertexBuffer_constr=JS_NewCFunction2(ctx,js_rlVertexBuffer_constructor,(const char *)"rlVertexBuffer",(int)8,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char *)"rlVertexBuffer",rlVertexBuffer_constr);
		js_declare_rlDrawCall(ctx,m);
		JSValue rlDrawCall_constr=JS_NewCFunction2(ctx,js_rlDrawCall_constructor,(const char *)"rlDrawCall",(int)4,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char *)"rlDrawCall",rlDrawCall_constr);
		js_declare_rlRenderBatch(ctx,m);
		JSValue rlRenderBatch_constr=JS_NewCFunction2(ctx,js_rlRenderBatch_constructor,(const char *)"rlRenderBatch",(int)6,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char *)"rlRenderBatch",rlRenderBatch_constr);
		JS_SetModuleExport(ctx,m,(const char *)"RL_OPENGL_11",JS_NewInt32(ctx,(int32_t)RL_OPENGL_11));
		JS_SetModuleExport(ctx,m,(const char *)"RL_OPENGL_21",JS_NewInt32(ctx,(int32_t)RL_OPENGL_21));
		JS_SetModuleExport(ctx,m,(const char *)"RL_OPENGL_33",JS_NewInt32(ctx,(int32_t)RL_OPENGL_33));
		JS_SetModuleExport(ctx,m,(const char *)"RL_OPENGL_43",JS_NewInt32(ctx,(int32_t)RL_OPENGL_43));
		JS_SetModuleExport(ctx,m,(const char *)"RL_OPENGL_ES_20",JS_NewInt32(ctx,(int32_t)RL_OPENGL_ES_20));
		JS_SetModuleExport(ctx,m,(const char *)"RL_OPENGL_ES_30",JS_NewInt32(ctx,(int32_t)RL_OPENGL_ES_30));
		JS_SetModuleExport(ctx,m,(const char *)"RL_LOG_ALL",JS_NewInt32(ctx,(int32_t)RL_LOG_ALL));
		JS_SetModuleExport(ctx,m,(const char *)"RL_LOG_TRACE",JS_NewInt32(ctx,(int32_t)RL_LOG_TRACE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_LOG_DEBUG",JS_NewInt32(ctx,(int32_t)RL_LOG_DEBUG));
		JS_SetModuleExport(ctx,m,(const char *)"RL_LOG_INFO",JS_NewInt32(ctx,(int32_t)RL_LOG_INFO));
		JS_SetModuleExport(ctx,m,(const char *)"RL_LOG_WARNING",JS_NewInt32(ctx,(int32_t)RL_LOG_WARNING));
		JS_SetModuleExport(ctx,m,(const char *)"RL_LOG_ERROR",JS_NewInt32(ctx,(int32_t)RL_LOG_ERROR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_LOG_FATAL",JS_NewInt32(ctx,(int32_t)RL_LOG_FATAL));
		JS_SetModuleExport(ctx,m,(const char *)"RL_LOG_NONE",JS_NewInt32(ctx,(int32_t)RL_LOG_NONE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R5G6B5",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R5G6B5));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R5G5B5A1",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R5G5B5A1));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R4G4B4A4",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R4G4B4A4));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R32",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R32));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32A32",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32A32));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R16",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R16));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16A16",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16A16));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_DXT1_RGB",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_DXT1_RGB));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_DXT1_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_DXT1_RGBA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_DXT3_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_DXT3_RGBA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_DXT5_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_DXT5_RGBA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_ETC1_RGB",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_ETC1_RGB));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_ETC2_RGB",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_ETC2_RGB));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_PVRT_RGB",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_PVRT_RGB));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_PVRT_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_PVRT_RGBA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_POINT",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_POINT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_BILINEAR",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_BILINEAR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_TRILINEAR",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_TRILINEAR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_ANISOTROPIC_4X",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_ANISOTROPIC_4X));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_ANISOTROPIC_8X",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_ANISOTROPIC_8X));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_ANISOTROPIC_16X",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_ANISOTROPIC_16X));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_ALPHA",JS_NewInt32(ctx,(int32_t)RL_BLEND_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_ADDITIVE",JS_NewInt32(ctx,(int32_t)RL_BLEND_ADDITIVE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_MULTIPLIED",JS_NewInt32(ctx,(int32_t)RL_BLEND_MULTIPLIED));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_ADD_COLORS",JS_NewInt32(ctx,(int32_t)RL_BLEND_ADD_COLORS));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_SUBTRACT_COLORS",JS_NewInt32(ctx,(int32_t)RL_BLEND_SUBTRACT_COLORS));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_ALPHA_PREMULTIPLY",JS_NewInt32(ctx,(int32_t)RL_BLEND_ALPHA_PREMULTIPLY));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_CUSTOM",JS_NewInt32(ctx,(int32_t)RL_BLEND_CUSTOM));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_CUSTOM_SEPARATE",JS_NewInt32(ctx,(int32_t)RL_BLEND_CUSTOM_SEPARATE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_POSITION",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_POSITION));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_TEXCOORD01",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_TEXCOORD01));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_TEXCOORD02",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_TEXCOORD02));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_NORMAL",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_TANGENT",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_TANGENT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_COLOR",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MATRIX_MVP",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MATRIX_MVP));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MATRIX_VIEW",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MATRIX_VIEW));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MATRIX_PROJECTION",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MATRIX_PROJECTION));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MATRIX_MODEL",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MATRIX_MODEL));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MATRIX_NORMAL",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MATRIX_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VECTOR_VIEW",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VECTOR_VIEW));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_COLOR_DIFFUSE",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_COLOR_DIFFUSE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_COLOR_SPECULAR",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_COLOR_SPECULAR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_COLOR_AMBIENT",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_COLOR_AMBIENT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_ALBEDO",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_ALBEDO));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_METALNESS",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_METALNESS));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_NORMAL",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_NORMAL));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_ROUGHNESS",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_ROUGHNESS));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_OCCLUSION",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_OCCLUSION));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_EMISSION",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_EMISSION));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_HEIGHT",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_HEIGHT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_CUBEMAP",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_CUBEMAP));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_IRRADIANCE",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_IRRADIANCE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_PREFILTER",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_PREFILTER));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_BRDF",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_BRDF));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_DIFFUSE",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_DIFFUSE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_SPECULAR",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_SPECULAR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_FLOAT",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_FLOAT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_VEC2",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_VEC2));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_VEC3",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_VEC3));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_VEC4",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_VEC4));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_INT",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_INT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_IVEC2",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_IVEC2));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_IVEC3",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_IVEC3));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_IVEC4",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_IVEC4));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_UINT",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_UINT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_UIVEC2",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_UIVEC2));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_UIVEC3",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_UIVEC3));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_UIVEC4",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_UIVEC4));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_SAMPLER2D",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_SAMPLER2D));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_ATTRIB_FLOAT",JS_NewInt32(ctx,(int32_t)RL_SHADER_ATTRIB_FLOAT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_ATTRIB_VEC2",JS_NewInt32(ctx,(int32_t)RL_SHADER_ATTRIB_VEC2));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_ATTRIB_VEC3",JS_NewInt32(ctx,(int32_t)RL_SHADER_ATTRIB_VEC3));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SHADER_ATTRIB_VEC4",JS_NewInt32(ctx,(int32_t)RL_SHADER_ATTRIB_VEC4));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL0",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL0));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL1",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL1));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL2",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL2));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL3",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL3));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL4",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL4));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL5",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL5));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL6",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL6));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL7",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL7));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_DEPTH",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_DEPTH));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_STENCIL",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_STENCIL));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_X",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_POSITIVE_X));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_X",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_NEGATIVE_X));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_Y",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_POSITIVE_Y));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_Z",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_POSITIVE_Z));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_TEXTURE2D",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_TEXTURE2D));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_RENDERBUFFER",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_RENDERBUFFER));
		JS_SetModuleExport(ctx,m,(const char *)"RL_CULL_FACE_FRONT",JS_NewInt32(ctx,(int32_t)RL_CULL_FACE_FRONT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_CULL_FACE_BACK",JS_NewInt32(ctx,(int32_t)RL_CULL_FACE_BACK));
		JS_SetModuleExport(ctx,m,(const char *)"RL_DEFAULT_BATCH_BUFFER_ELEMENTS",JS_NewInt32(ctx,(int32_t)RL_DEFAULT_BATCH_BUFFER_ELEMENTS));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_S",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_S));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_T",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_T));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_MAG_FILTER",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_MAG_FILTER));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_MIN_FILTER",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_MIN_FILTER));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_NEAREST",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_NEAREST));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_LINEAR",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_LINEAR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_MIP_NEAREST",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_MIP_NEAREST));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_MIP_LINEAR",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_MIP_LINEAR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_ANISOTROPIC",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_ANISOTROPIC));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_MIPMAP_BIAS_RATIO",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_MIPMAP_BIAS_RATIO));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_REPEAT",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_REPEAT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_CLAMP",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_CLAMP));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_MIRROR_REPEAT",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_MIRROR_REPEAT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_MIRROR_CLAMP",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_MIRROR_CLAMP));
		JS_SetModuleExport(ctx,m,(const char *)"RL_MODELVIEW",JS_NewInt32(ctx,(int32_t)RL_MODELVIEW));
		JS_SetModuleExport(ctx,m,(const char *)"RL_PROJECTION",JS_NewInt32(ctx,(int32_t)RL_PROJECTION));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TEXTURE",JS_NewInt32(ctx,(int32_t)RL_TEXTURE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_LINES",JS_NewInt32(ctx,(int32_t)RL_LINES));
		JS_SetModuleExport(ctx,m,(const char *)"RL_TRIANGLES",JS_NewInt32(ctx,(int32_t)RL_TRIANGLES));
		JS_SetModuleExport(ctx,m,(const char *)"RL_QUADS",JS_NewInt32(ctx,(int32_t)RL_QUADS));
		JS_SetModuleExport(ctx,m,(const char *)"RL_UNSIGNED_BYTE",JS_NewInt32(ctx,(int32_t)RL_UNSIGNED_BYTE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_FLOAT",JS_NewInt32(ctx,(int32_t)RL_FLOAT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_STREAM_DRAW",JS_NewInt32(ctx,(int32_t)RL_STREAM_DRAW));
		JS_SetModuleExport(ctx,m,(const char *)"RL_STREAM_READ",JS_NewInt32(ctx,(int32_t)RL_STREAM_READ));
		JS_SetModuleExport(ctx,m,(const char *)"RL_STREAM_COPY",JS_NewInt32(ctx,(int32_t)RL_STREAM_COPY));
		JS_SetModuleExport(ctx,m,(const char *)"RL_STATIC_DRAW",JS_NewInt32(ctx,(int32_t)RL_STATIC_DRAW));
		JS_SetModuleExport(ctx,m,(const char *)"RL_STATIC_READ",JS_NewInt32(ctx,(int32_t)RL_STATIC_READ));
		JS_SetModuleExport(ctx,m,(const char *)"RL_STATIC_COPY",JS_NewInt32(ctx,(int32_t)RL_STATIC_COPY));
		JS_SetModuleExport(ctx,m,(const char *)"RL_DYNAMIC_DRAW",JS_NewInt32(ctx,(int32_t)RL_DYNAMIC_DRAW));
		JS_SetModuleExport(ctx,m,(const char *)"RL_DYNAMIC_READ",JS_NewInt32(ctx,(int32_t)RL_DYNAMIC_READ));
		JS_SetModuleExport(ctx,m,(const char *)"RL_DYNAMIC_COPY",JS_NewInt32(ctx,(int32_t)RL_DYNAMIC_COPY));
		JS_SetModuleExport(ctx,m,(const char *)"RL_FRAGMENT_SHADER",JS_NewInt32(ctx,(int32_t)RL_FRAGMENT_SHADER));
		JS_SetModuleExport(ctx,m,(const char *)"RL_VERTEX_SHADER",JS_NewInt32(ctx,(int32_t)RL_VERTEX_SHADER));
		JS_SetModuleExport(ctx,m,(const char *)"RL_COMPUTE_SHADER",JS_NewInt32(ctx,(int32_t)RL_COMPUTE_SHADER));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ZERO",JS_NewInt32(ctx,(int32_t)RL_ZERO));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ONE",JS_NewInt32(ctx,(int32_t)RL_ONE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SRC_COLOR",JS_NewInt32(ctx,(int32_t)RL_SRC_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_SRC_COLOR",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_SRC_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SRC_ALPHA",JS_NewInt32(ctx,(int32_t)RL_SRC_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_SRC_ALPHA",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_SRC_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_DST_ALPHA",JS_NewInt32(ctx,(int32_t)RL_DST_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_DST_ALPHA",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_DST_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_DST_COLOR",JS_NewInt32(ctx,(int32_t)RL_DST_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_DST_COLOR",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_DST_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_SRC_ALPHA_SATURATE",JS_NewInt32(ctx,(int32_t)RL_SRC_ALPHA_SATURATE));
		JS_SetModuleExport(ctx,m,(const char *)"RL_CONSTANT_COLOR",JS_NewInt32(ctx,(int32_t)RL_CONSTANT_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_CONSTANT_COLOR",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_CONSTANT_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_CONSTANT_ALPHA",JS_NewInt32(ctx,(int32_t)RL_CONSTANT_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_CONSTANT_ALPHA",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_CONSTANT_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_FUNC_ADD",JS_NewInt32(ctx,(int32_t)RL_FUNC_ADD));
		JS_SetModuleExport(ctx,m,(const char *)"RL_MIN",JS_NewInt32(ctx,(int32_t)RL_MIN));
		JS_SetModuleExport(ctx,m,(const char *)"RL_MAX",JS_NewInt32(ctx,(int32_t)RL_MAX));
		JS_SetModuleExport(ctx,m,(const char *)"RL_FUNC_SUBTRACT",JS_NewInt32(ctx,(int32_t)RL_FUNC_SUBTRACT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_FUNC_REVERSE_SUBTRACT",JS_NewInt32(ctx,(int32_t)RL_FUNC_REVERSE_SUBTRACT));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_EQUATION",JS_NewInt32(ctx,(int32_t)RL_BLEND_EQUATION));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_EQUATION_RGB",JS_NewInt32(ctx,(int32_t)RL_BLEND_EQUATION_RGB));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_EQUATION_ALPHA",JS_NewInt32(ctx,(int32_t)RL_BLEND_EQUATION_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_DST_RGB",JS_NewInt32(ctx,(int32_t)RL_BLEND_DST_RGB));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_SRC_RGB",JS_NewInt32(ctx,(int32_t)RL_BLEND_SRC_RGB));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_DST_ALPHA",JS_NewInt32(ctx,(int32_t)RL_BLEND_DST_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_SRC_ALPHA",JS_NewInt32(ctx,(int32_t)RL_BLEND_SRC_ALPHA));
		JS_SetModuleExport(ctx,m,(const char *)"RL_BLEND_COLOR",JS_NewInt32(ctx,(int32_t)RL_BLEND_COLOR));
		JS_SetModuleExport(ctx,m,(const char *)"RL_READ_FRAMEBUFFER",JS_NewInt32(ctx,(int32_t)RL_READ_FRAMEBUFFER));
		JS_SetModuleExport(ctx,m,(const char *)"RL_DRAW_FRAMEBUFFER",JS_NewInt32(ctx,(int32_t)RL_DRAW_FRAMEBUFFER));
		return 0;
	}
	
	JSModuleDef * js_init_module_js_rlgl(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_js_rlgl_init);
		if(!m){
			return NULL;
		}
		size_t listcount=countof(jsrlgl_funcs);
		JS_AddModuleExportList(ctx,m,jsrlgl_funcs,(int)listcount);
		JS_AddModuleExport(ctx,m,(const char *)"rlVertexBuffer");
		JS_AddModuleExport(ctx,m,(const char *)"rlDrawCall");
		JS_AddModuleExport(ctx,m,(const char *)"rlRenderBatch");
		JS_AddModuleExport(ctx,m,(const char *)"RL_OPENGL_11");
		JS_AddModuleExport(ctx,m,(const char *)"RL_OPENGL_21");
		JS_AddModuleExport(ctx,m,(const char *)"RL_OPENGL_33");
		JS_AddModuleExport(ctx,m,(const char *)"RL_OPENGL_43");
		JS_AddModuleExport(ctx,m,(const char *)"RL_OPENGL_ES_20");
		JS_AddModuleExport(ctx,m,(const char *)"RL_OPENGL_ES_30");
		JS_AddModuleExport(ctx,m,(const char *)"RL_LOG_ALL");
		JS_AddModuleExport(ctx,m,(const char *)"RL_LOG_TRACE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_LOG_DEBUG");
		JS_AddModuleExport(ctx,m,(const char *)"RL_LOG_INFO");
		JS_AddModuleExport(ctx,m,(const char *)"RL_LOG_WARNING");
		JS_AddModuleExport(ctx,m,(const char *)"RL_LOG_ERROR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_LOG_FATAL");
		JS_AddModuleExport(ctx,m,(const char *)"RL_LOG_NONE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R5G6B5");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R5G5B5A1");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R4G4B4A4");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R32");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32A32");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R16");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16A16");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_DXT1_RGB");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_DXT1_RGBA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_DXT3_RGBA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_DXT5_RGBA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_ETC1_RGB");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_ETC2_RGB");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_PVRT_RGB");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_PVRT_RGBA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_POINT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_BILINEAR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_TRILINEAR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_ANISOTROPIC_4X");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_ANISOTROPIC_8X");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_ANISOTROPIC_16X");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_ADDITIVE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_MULTIPLIED");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_ADD_COLORS");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_SUBTRACT_COLORS");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_ALPHA_PREMULTIPLY");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_CUSTOM");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_CUSTOM_SEPARATE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_POSITION");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_TEXCOORD01");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_TEXCOORD02");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_TANGENT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VERTEX_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MATRIX_MVP");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MATRIX_VIEW");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MATRIX_PROJECTION");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MATRIX_MODEL");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MATRIX_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_VECTOR_VIEW");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_COLOR_DIFFUSE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_COLOR_SPECULAR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_COLOR_AMBIENT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_ALBEDO");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_METALNESS");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_NORMAL");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_ROUGHNESS");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_OCCLUSION");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_EMISSION");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_HEIGHT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_CUBEMAP");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_IRRADIANCE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_PREFILTER");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_BRDF");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_DIFFUSE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_LOC_MAP_SPECULAR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_FLOAT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_VEC2");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_VEC3");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_VEC4");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_INT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_IVEC2");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_IVEC3");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_IVEC4");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_UINT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_UIVEC2");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_UIVEC3");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_UIVEC4");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_UNIFORM_SAMPLER2D");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_ATTRIB_FLOAT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_ATTRIB_VEC2");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_ATTRIB_VEC3");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SHADER_ATTRIB_VEC4");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL0");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL1");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL2");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL3");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL4");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL5");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL6");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_COLOR_CHANNEL7");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_DEPTH");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_STENCIL");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_X");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_X");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_Y");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_Z");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_TEXTURE2D");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ATTACHMENT_RENDERBUFFER");
		JS_AddModuleExport(ctx,m,(const char *)"RL_CULL_FACE_FRONT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_CULL_FACE_BACK");
		JS_AddModuleExport(ctx,m,(const char *)"RL_DEFAULT_BATCH_BUFFER_ELEMENTS");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_S");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_T");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_MAG_FILTER");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_MIN_FILTER");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_NEAREST");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_LINEAR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_MIP_NEAREST");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_MIP_LINEAR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_FILTER_ANISOTROPIC");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_MIPMAP_BIAS_RATIO");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_REPEAT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_CLAMP");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_MIRROR_REPEAT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE_WRAP_MIRROR_CLAMP");
		JS_AddModuleExport(ctx,m,(const char *)"RL_MODELVIEW");
		JS_AddModuleExport(ctx,m,(const char *)"RL_PROJECTION");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TEXTURE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_LINES");
		JS_AddModuleExport(ctx,m,(const char *)"RL_TRIANGLES");
		JS_AddModuleExport(ctx,m,(const char *)"RL_QUADS");
		JS_AddModuleExport(ctx,m,(const char *)"RL_UNSIGNED_BYTE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_FLOAT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_STREAM_DRAW");
		JS_AddModuleExport(ctx,m,(const char *)"RL_STREAM_READ");
		JS_AddModuleExport(ctx,m,(const char *)"RL_STREAM_COPY");
		JS_AddModuleExport(ctx,m,(const char *)"RL_STATIC_DRAW");
		JS_AddModuleExport(ctx,m,(const char *)"RL_STATIC_READ");
		JS_AddModuleExport(ctx,m,(const char *)"RL_STATIC_COPY");
		JS_AddModuleExport(ctx,m,(const char *)"RL_DYNAMIC_DRAW");
		JS_AddModuleExport(ctx,m,(const char *)"RL_DYNAMIC_READ");
		JS_AddModuleExport(ctx,m,(const char *)"RL_DYNAMIC_COPY");
		JS_AddModuleExport(ctx,m,(const char *)"RL_FRAGMENT_SHADER");
		JS_AddModuleExport(ctx,m,(const char *)"RL_VERTEX_SHADER");
		JS_AddModuleExport(ctx,m,(const char *)"RL_COMPUTE_SHADER");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ZERO");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ONE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SRC_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_SRC_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SRC_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_SRC_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_DST_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_DST_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_DST_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_DST_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_SRC_ALPHA_SATURATE");
		JS_AddModuleExport(ctx,m,(const char *)"RL_CONSTANT_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_CONSTANT_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_CONSTANT_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_ONE_MINUS_CONSTANT_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_FUNC_ADD");
		JS_AddModuleExport(ctx,m,(const char *)"RL_MIN");
		JS_AddModuleExport(ctx,m,(const char *)"RL_MAX");
		JS_AddModuleExport(ctx,m,(const char *)"RL_FUNC_SUBTRACT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_FUNC_REVERSE_SUBTRACT");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_EQUATION");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_EQUATION_RGB");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_EQUATION_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_DST_RGB");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_SRC_RGB");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_DST_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_SRC_ALPHA");
		JS_AddModuleExport(ctx,m,(const char *)"RL_BLEND_COLOR");
		JS_AddModuleExport(ctx,m,(const char *)"RL_READ_FRAMEBUFFER");
		JS_AddModuleExport(ctx,m,(const char *)"RL_DRAW_FRAMEBUFFER");
		return m;
	}

#endif //JS_js_rlgl_GUARD