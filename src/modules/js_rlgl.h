#ifndef JS_rlgl_GUARD
	#define JS_rlgl_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <raylib.h>
	#include <rlgl.h>
	
	static int js_getint(JSContext * ctx,JSValue src,bool * error);
	
	static float js_getfloat(JSContext * ctx,JSValue src,bool * error);
	
	static float * js_getfloat_arrnc(JSContext * ctx,JSValue src,bool * error);
	
	static unsigned char js_getunsignedchar(JSContext * ctx,JSValue src,bool * error);
	
	static unsigned char * js_getunsignedchar_arrnc(JSContext * ctx,JSValue src,bool * error);
	
	static unsigned int js_getunsignedint(JSContext * ctx,JSValue src,bool * error);
	
	static unsigned int * js_getunsignedint_arrnc(JSContext * ctx,JSValue src,bool * error);
	
	static unsigned int * js_getunsignedint_arr5nc(JSContext * ctx,JSValue src,bool * error){
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
		}else if(js_IsArrayLength(ctx,src,(int64_t)5)){
			int64_t size_ret=(int64_t)5;
			size_ret =(int64_t)5;
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
	
	static rlVertexBuffer js_getrlVertexBuffer(JSContext * ctx,JSValue src,bool * error){
		rlVertexBuffer ret;
		if(JS_GetClassID(src)==js_rlVertexBuffer_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_rlVertexBuffer_class_id);
			ret =*(rlVertexBuffer *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type rlVertexBuffer");
			error[0]=(bool)1;
			return (rlVertexBuffer){0};
		}
		return ret;
	}
	
	static rlVertexBuffer rlVertexBuffer_copy(JSContext * ctx,rlVertexBuffer ptr){
		rlVertexBuffer ret=ptr;
		ret.vertices =(float  *)jsc_malloc(ctx,sizeof(float *)*ptr.elementCount*3*4);
		for(int i=0;i<ptr.elementCount*3*4;i++){
		}
		ret.texcoords =(float  *)jsc_malloc(ctx,sizeof(float *)*ptr.elementCount*2*4);
		for(int i0=0;i0<ptr.elementCount*2*4;i0++){
		}
		ret.normals =(float  *)jsc_malloc(ctx,sizeof(float *)*ptr.elementCount*3*4);
		for(int i1=0;i1<ptr.elementCount*3*4;i1++){
		}
		ret.colors =(unsigned char  *)jsc_malloc(ctx,sizeof(unsigned char *)*ptr.elementCount*4*4);
		for(int i2=0;i2<ptr.elementCount*4*4;i2++){
		}
		ret.indices =(unsigned int  *)jsc_malloc(ctx,sizeof(unsigned int *)*ptr.elementCount*6);
		for(int i3=0;i3<ptr.elementCount*6;i3++){
		}
		return ret;
	}
	
	static rlDrawCall js_getrlDrawCall(JSContext * ctx,JSValue src,bool * error){
		rlDrawCall ret;
		if(JS_GetClassID(src)==js_rlDrawCall_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_rlDrawCall_class_id);
			ret =*(rlDrawCall *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type rlDrawCall");
			error[0]=(bool)1;
			return (rlDrawCall){0};
		}
		return ret;
	}
	
	static rlVertexBuffer * js_getrlVertexBuffer_arrnc(JSContext * ctx,JSValue src,bool * error){
		rlVertexBuffer * ret;
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
			ret =(rlVertexBuffer  *)jsc_malloc(ctx,size_ret*sizeof(rlVertexBuffer));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_rlVertexBuffer_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_rlVertexBuffer_class_id);
					ret[i] =*(rlVertexBuffer *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type rlVertexBuffer *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_rlVertexBuffer_class_id){
			if(JS_GetClassID(src)==js_rlVertexBuffer_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_rlVertexBuffer_class_id);
				ret =(rlVertexBuffer  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type rlVertexBuffer *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type rlVertexBuffer *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static rlDrawCall * js_getrlDrawCall_arrnc(JSContext * ctx,JSValue src,bool * error){
		rlDrawCall * ret;
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
			ret =(rlDrawCall  *)jsc_malloc(ctx,size_ret*sizeof(rlDrawCall));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_rlDrawCall_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_rlDrawCall_class_id);
					ret[i] =*(rlDrawCall *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type rlDrawCall *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(jsc_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_rlDrawCall_class_id){
			if(JS_GetClassID(src)==js_rlDrawCall_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_rlDrawCall_class_id);
				ret =(rlDrawCall  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type rlDrawCall *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type rlDrawCall *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static rlRenderBatch js_getrlRenderBatch(JSContext * ctx,JSValue src,bool * error){
		rlRenderBatch ret;
		if(JS_GetClassID(src)==js_rlRenderBatch_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_rlRenderBatch_class_id);
			ret =*(rlRenderBatch *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type rlRenderBatch");
			error[0]=(bool)1;
			return (rlRenderBatch){0};
		}
		return ret;
	}
	
	static rlRenderBatch rlRenderBatch_copy(JSContext * ctx,rlRenderBatch ptr){
		rlRenderBatch ret=ptr;
		ret.vertexBuffer =(rlVertexBuffer  *)jsc_malloc(ctx,sizeof(rlVertexBuffer *)*ptr.bufferCount);
		for(int i=0;i<ptr.bufferCount;i++){
			ret.vertexBuffer[i] =rlVertexBuffer_copy(ctx,ptr.vertexBuffer[i]);
		}
		ret.draws =(rlDrawCall  *)jsc_malloc(ctx,sizeof(rlDrawCall *)*RL_DEFAULT_BATCH_DRAWCALLS);
		for(int i0=0;i0<RL_DEFAULT_BATCH_DRAWCALLS;i0++){
			ret.draws[i0] =ptr.draws[i0];
		}
		return ret;
	}
	
	static float * js_getfloat_arr(JSContext * ctx,JSValue src,bool * error);
	
	static double js_getdouble(JSContext * ctx,JSValue src,bool * error);
	
	static void * js_getvoid_arr(JSContext * ctx,JSValue src,bool * error);
	
	static bool js_getbool(JSContext * ctx,JSValue src,bool * error);
	
	static rlRenderBatch * js_getrlRenderBatch_arr(JSContext * ctx,JSValue src,bool * error){
		rlRenderBatch * ret;
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
			ret =(rlRenderBatch  *)js_malloc(ctx,size_ret*sizeof(rlRenderBatch));
			for(int i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_GetClassID(src0)==js_rlRenderBatch_class_id){
					opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_rlRenderBatch_class_id);
					ret[i] =*(rlRenderBatch *)tmpshadow[0].ptr;
				}else{
					JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type rlRenderBatch *");
					error[0]=(bool)1;
					return NULL;
				}
			}
			memoryStore(js_free,(void  *)ret);
		}else if(JS_GetClassID(src)==js_rlRenderBatch_class_id){
			if(JS_GetClassID(src)==js_rlRenderBatch_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_rlRenderBatch_class_id);
				ret =(rlRenderBatch  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type rlRenderBatch *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type rlRenderBatch *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static void * js_getvoid_arrnull(JSContext * ctx,JSValue src,bool * error){
		void * ret;
		if(JS_IsArrayBuffer(src)){
			int64_t size_ret;
			ret =(void  *)JS_GetArrayBuffer(ctx,(size_t  *)&size_ret,src);
		}else if(JS_IsString(src)){
			ret =(void  *)JS_ToCStringLen(ctx,NULL,src);
			memoryStore(JS_FreeCString,ret);
		}else if(JS_GetTypedArrayType(src)!=-1){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(void  *)JS_GetArrayBuffer(ctx,&size_ret,src);
			ret +=offset_ret;
			size_ret -=offset_ret;
			JS_FreeValuePtr(ctx,&da_ret);
		}else if(JS_IsNull(src)||JS_IsUndefined(src)){
			ret =NULL;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type void *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static unsigned int * js_getunsignedint_arr(JSContext * ctx,JSValue src,bool * error){
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
	
	static int * js_getint_arr(JSContext * ctx,JSValue src,bool * error);
	
	static char * js_getchar_arr(JSContext * ctx,JSValue src,bool * error);
	
	static float * js_getfloat_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0);
	
	static Vector2 * js_getVector2_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0);
	
	static Vector3 * js_getVector3_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0);
	
	static Vector4 * js_getVector4_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0);
	
	static int * js_getint_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0);
	
	static unsigned int * js_getunsignedint_arr_arg1(JSContext * ctx,JSValue src,bool * error,int size0);
	
	static Matrix js_getMatrix(JSContext * ctx,JSValue src,bool * error);
	
	static Matrix * js_getMatrix_arr(JSContext * ctx,JSValue src,bool * error);
	
	static void js_rlVertexBuffer_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_rlVertexBuffer_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_rlVertexBuffer_get_elementCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		int elementCount=ptr[0].elementCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)elementCount));
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_elementCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].elementCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_vertices_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].elementCount*3*4;i++){
			float src0=ptr[0].vertices[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_vertices_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		int length=(int)ptr[0].elementCount*3*4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_vertices_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].elementCount*3*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].elementCount*3*4){
				float src=ptr[0].vertices[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_vertices_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].elementCount*3*4){
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
	
	static int js_rlVertexBuffer_vertices_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].elementCount*3*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlVertexBuffer_get_vertices(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_rlVertexBuffer_vertices_values,.keys = js_rlVertexBuffer_vertices_keys,.get = js_rlVertexBuffer_vertices_get,.set = js_rlVertexBuffer_vertices_set,.has = js_rlVertexBuffer_vertices_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_vertices(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].vertices!=NULL)jsc_free(ctx,(void  *)ptr[0].vertices);
		ptr[0].vertices =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_texcoords_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].elementCount*2*4;i++){
			float src0=ptr[0].texcoords[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_texcoords_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		int length=(int)ptr[0].elementCount*2*4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_texcoords_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].elementCount*2*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].elementCount*2*4){
				float src=ptr[0].texcoords[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_texcoords_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].elementCount*2*4){
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
	
	static int js_rlVertexBuffer_texcoords_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].elementCount*2*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlVertexBuffer_get_texcoords(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_rlVertexBuffer_texcoords_values,.keys = js_rlVertexBuffer_texcoords_keys,.get = js_rlVertexBuffer_texcoords_get,.set = js_rlVertexBuffer_texcoords_set,.has = js_rlVertexBuffer_texcoords_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_texcoords(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].texcoords!=NULL)jsc_free(ctx,(void  *)ptr[0].texcoords);
		ptr[0].texcoords =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_normals_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].elementCount*3*4;i++){
			float src0=ptr[0].normals[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_normals_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		int length=(int)ptr[0].elementCount*3*4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_normals_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].elementCount*3*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].elementCount*3*4){
				float src=ptr[0].normals[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_normals_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].elementCount*3*4){
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
	
	static int js_rlVertexBuffer_normals_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].elementCount*3*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlVertexBuffer_get_normals(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_rlVertexBuffer_normals_values,.keys = js_rlVertexBuffer_normals_keys,.get = js_rlVertexBuffer_normals_get,.set = js_rlVertexBuffer_normals_set,.has = js_rlVertexBuffer_normals_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_normals(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].normals!=NULL)jsc_free(ctx,(void  *)ptr[0].normals);
		ptr[0].normals =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_colors_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].elementCount*4*4;i++){
			unsigned char src0=ptr[0].colors[i];
			JSValue ret1=JS_NewUint32(ctx,(uint32_t)((unsigned long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_colors_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		int length=(int)ptr[0].elementCount*4*4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_colors_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].elementCount*4*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].elementCount*4*4){
				unsigned char src=ptr[0].colors[property];
				JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_colors_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].elementCount*4*4){
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
	
	static int js_rlVertexBuffer_colors_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].elementCount*4*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlVertexBuffer_get_colors(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_rlVertexBuffer_colors_values,.keys = js_rlVertexBuffer_colors_keys,.get = js_rlVertexBuffer_colors_get,.set = js_rlVertexBuffer_colors_set,.has = js_rlVertexBuffer_colors_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_colors(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned char * value=js_getunsignedchar_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].colors!=NULL)jsc_free(ctx,(void  *)ptr[0].colors);
		ptr[0].colors =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_indices_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].elementCount*6;i++){
			unsigned int src0=ptr[0].indices[i];
			JSValue ret1=JS_NewUint32(ctx,(uint32_t)((unsigned long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_indices_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		int length=(int)ptr[0].elementCount*6;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_indices_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].elementCount*((long)6));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].elementCount*6){
				unsigned int src=ptr[0].indices[property];
				JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_indices_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].elementCount*6){
				bool error=(bool)0;
				local_memlock=(bool)true;
				unsigned int ret=js_getunsignedint(ctx,set_to,&error);
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
	
	static int js_rlVertexBuffer_indices_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].elementCount*6){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlVertexBuffer_get_indices(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_rlVertexBuffer_indices_values,.keys = js_rlVertexBuffer_indices_keys,.get = js_rlVertexBuffer_indices_get,.set = js_rlVertexBuffer_indices_set,.has = js_rlVertexBuffer_indices_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_indices(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int * value=js_getunsignedint_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].indices!=NULL)jsc_free(ctx,(void  *)ptr[0].indices);
		ptr[0].indices =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_get_vaoId(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		unsigned int vaoId=ptr[0].vaoId;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)vaoId));
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_vaoId(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].vaoId=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertexBuffer_vboId_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<5;i++){
			unsigned int src0=ptr[0].vboId[i];
			JSValue ret1=JS_NewUint32(ctx,(uint32_t)((unsigned long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlVertexBuffer_vboId_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		int length=(int)5;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlVertexBuffer_vboId_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)5));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<5){
				unsigned int src=ptr[0].vboId[property];
				JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlVertexBuffer_vboId_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<5){
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
	
	static int js_rlVertexBuffer_vboId_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		rlVertexBuffer * ptr=(rlVertexBuffer  *)ptr_u;
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
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_rlVertexBuffer_vboId_values,.keys = js_rlVertexBuffer_vboId_keys,.get = js_rlVertexBuffer_vboId_get,.set = js_rlVertexBuffer_vboId_set,.has = js_rlVertexBuffer_vboId_has});
		return ret;
	}
	
	static JSValue js_rlVertexBuffer_set_vboId(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlVertexBuffer_class_id);
		rlVertexBuffer * ptr=(rlVertexBuffer  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int * value=js_getunsignedint_arr5nc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		memcpy((void  *)ptr[0].vboId,(const void  *)value,5*sizeof(unsigned int));
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
		JS_NewClass(rt,js_rlVertexBuffer_class_id,(const JSClassDef  *)&js_rlVertexBuffer_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_rlVertexBuffer_proto_funcs,(int)countof(js_rlVertexBuffer_proto_funcs));
		JS_SetClassProto(ctx,js_rlVertexBuffer_class_id,proto);
		return 0;
	}
	
	static void js_rlDrawCall_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_rlDrawCall_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_rlDrawCall_get_mode(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		rlDrawCall * ptr=(rlDrawCall  *)shadow[0].ptr;
		int mode=ptr[0].mode;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)mode));
		return ret;
	}
	
	static JSValue js_rlDrawCall_set_mode(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		rlDrawCall * ptr=(rlDrawCall  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].mode=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawCall_get_vertexCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		rlDrawCall * ptr=(rlDrawCall  *)shadow[0].ptr;
		int vertexCount=ptr[0].vertexCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)vertexCount));
		return ret;
	}
	
	static JSValue js_rlDrawCall_set_vertexCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		rlDrawCall * ptr=(rlDrawCall  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].vertexCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawCall_get_vertexAlignment(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		rlDrawCall * ptr=(rlDrawCall  *)shadow[0].ptr;
		int vertexAlignment=ptr[0].vertexAlignment;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)vertexAlignment));
		return ret;
	}
	
	static JSValue js_rlDrawCall_set_vertexAlignment(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		rlDrawCall * ptr=(rlDrawCall  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].vertexAlignment=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawCall_get_textureId(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		rlDrawCall * ptr=(rlDrawCall  *)shadow[0].ptr;
		unsigned int textureId=ptr[0].textureId;
		JSValue ret=JS_NewUint32(ctx,(uint32_t)((unsigned long)textureId));
		return ret;
	}
	
	static JSValue js_rlDrawCall_set_textureId(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlDrawCall_class_id);
		rlDrawCall * ptr=(rlDrawCall  *)shadow[0].ptr;
		local_memlock=(bool)true;
		unsigned int value=js_getunsignedint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
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
		JS_NewClass(rt,js_rlDrawCall_class_id,(const JSClassDef  *)&js_rlDrawCall_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_rlDrawCall_proto_funcs,(int)countof(js_rlDrawCall_proto_funcs));
		JS_SetClassProto(ctx,js_rlDrawCall_class_id,proto);
		return 0;
	}
	
	static void js_rlRenderBatch_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_rlRenderBatch_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_rlRenderBatch_get_bufferCount(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		int bufferCount=ptr[0].bufferCount;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)bufferCount));
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_bufferCount(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].bufferCount=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRenderBatch_get_currentBuffer(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		int currentBuffer=ptr[0].currentBuffer;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)currentBuffer));
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_currentBuffer(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].currentBuffer=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRenderBatch_vertexBuffer_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlRenderBatch * ptr=(rlRenderBatch  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].bufferCount;i++){
			rlVertexBuffer * src0=(ptr[0].vertexBuffer+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_rlVertexBuffer_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlRenderBatch_vertexBuffer_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		rlRenderBatch * ptr=(rlRenderBatch  *)ptr_u;
		int length=ptr[0].bufferCount;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlRenderBatch_vertexBuffer_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlRenderBatch * ptr=(rlRenderBatch  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)ptr[0].bufferCount));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].bufferCount){
				rlVertexBuffer * src=(ptr[0].vertexBuffer+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_rlVertexBuffer_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlRenderBatch_vertexBuffer_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		rlRenderBatch * ptr=(rlRenderBatch  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].bufferCount){
				bool error=(bool)0;
				local_memlock=(bool)true;
				rlVertexBuffer ret=js_getrlVertexBuffer(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].vertexBuffer[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_rlRenderBatch_vertexBuffer_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		rlRenderBatch * ptr=(rlRenderBatch  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].bufferCount){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_rlRenderBatch_get_vertexBuffer(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_rlRenderBatch_vertexBuffer_values,.keys = js_rlRenderBatch_vertexBuffer_keys,.get = js_rlRenderBatch_vertexBuffer_get,.set = js_rlRenderBatch_vertexBuffer_set,.has = js_rlRenderBatch_vertexBuffer_has});
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_vertexBuffer(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		local_memlock=(bool)true;
		rlVertexBuffer * value=js_getrlVertexBuffer_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].vertexBuffer!=NULL)jsc_free(ctx,(void  *)ptr[0].vertexBuffer);
		ptr[0].vertexBuffer =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRenderBatch_draws_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlRenderBatch * ptr=(rlRenderBatch  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<RL_DEFAULT_BATCH_DRAWCALLS;i++){
			rlDrawCall * src0=(ptr[0].draws+i);
			JS_DupValue(ctx,anchor);
			opaqueShadow * ptr_ret1=create_shadow_with_external((void  *)src0,anchor);
			JSValue ret1=JS_NewObjectClass(ctx,js_rlDrawCall_class_id);
			JS_SetOpaque(ret1,(void  *)ptr_ret1);
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_rlRenderBatch_draws_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		rlRenderBatch * ptr=(rlRenderBatch  *)ptr_u;
		int length=RL_DEFAULT_BATCH_DRAWCALLS;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_rlRenderBatch_draws_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		rlRenderBatch * ptr=(rlRenderBatch  *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)RL_DEFAULT_BATCH_DRAWCALLS));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<RL_DEFAULT_BATCH_DRAWCALLS){
				rlDrawCall * src=(ptr[0].draws+property);
				JS_DupValue(ctx,anchor);
				opaqueShadow * ptr_ret=create_shadow_with_external((void  *)src,anchor);
				JSValue ret=JS_NewObjectClass(ctx,js_rlDrawCall_class_id);
				JS_SetOpaque(ret,(void  *)ptr_ret);
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_rlRenderBatch_draws_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		rlRenderBatch * ptr=(rlRenderBatch  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<RL_DEFAULT_BATCH_DRAWCALLS){
				bool error=(bool)0;
				local_memlock=(bool)true;
				rlDrawCall ret=js_getrlDrawCall(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].draws[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_rlRenderBatch_draws_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		rlRenderBatch * ptr=(rlRenderBatch  *)ptr_u;
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
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_rlRenderBatch_draws_values,.keys = js_rlRenderBatch_draws_keys,.get = js_rlRenderBatch_draws_get,.set = js_rlRenderBatch_draws_set,.has = js_rlRenderBatch_draws_has});
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_draws(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		local_memlock=(bool)true;
		rlDrawCall * value=js_getrlDrawCall_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].draws!=NULL)jsc_free(ctx,(void  *)ptr[0].draws);
		ptr[0].draws =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRenderBatch_get_drawCounter(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		int drawCounter=ptr[0].drawCounter;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)drawCounter));
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_drawCounter(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].drawCounter=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRenderBatch_get_currentDepth(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		float currentDepth=ptr[0].currentDepth;
		JSValue ret=JS_NewFloat64(ctx,((double)currentDepth));
		return ret;
	}
	
	static JSValue js_rlRenderBatch_set_currentDepth(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_rlRenderBatch_class_id);
		rlRenderBatch * ptr=(rlRenderBatch  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
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
		JS_NewClass(rt,js_rlRenderBatch_class_id,(const JSClassDef  *)&js_rlRenderBatch_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_rlRenderBatch_proto_funcs,(int)countof(js_rlRenderBatch_proto_funcs));
		JS_SetClassProto(ctx,js_rlRenderBatch_class_id,proto);
		return 0;
	}
	
	static JSValue js_rlVertexBuffer_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(rlVertexBuffer));
			JSValue _return=JS_NewObjectClass(ctx,js_rlVertexBuffer_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		rlVertexBuffer _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_rlVertexBuffer_class_id){
			rlVertexBuffer ptr=js_getrlVertexBuffer(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =rlVertexBuffer_copy(ctx,ptr);
		}else{
			int elementCount=js_getint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			float * vertices=js_getfloat_arrnc(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float * texcoords=js_getfloat_arrnc(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			float * normals=js_getfloat_arrnc(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned char * colors=js_getunsignedchar_arrnc(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int * indices=js_getunsignedint_arrnc(ctx,argv[5],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int vaoId=js_getunsignedint(ctx,argv[6],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int * vboId=js_getunsignedint_arr5nc(ctx,argv[7],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(rlVertexBuffer){
				elementCount,
				vertices,
				texcoords,
				normals,
				colors,
				indices,
				vaoId,
				{vboId[0],vboId[1],vboId[2],vboId[3],vboId[4]}
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(rlVertexBuffer));
		rlVertexBuffer * _returnptr=((rlVertexBuffer *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_rlVertexBuffer_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_rlDrawCall_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(rlDrawCall));
			JSValue _return=JS_NewObjectClass(ctx,js_rlDrawCall_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		rlDrawCall _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_rlDrawCall_class_id){
			rlDrawCall ptr=js_getrlDrawCall(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			int mode=js_getint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int vertexCount=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			int vertexAlignment=js_getint(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			unsigned int textureId=js_getunsignedint(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(rlDrawCall){
				mode,
				vertexCount,
				vertexAlignment,
				textureId
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(rlDrawCall));
		rlDrawCall * _returnptr=((rlDrawCall *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_rlDrawCall_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_rlRenderBatch_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(rlRenderBatch));
			JSValue _return=JS_NewObjectClass(ctx,js_rlRenderBatch_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		rlRenderBatch _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_rlRenderBatch_class_id){
			rlRenderBatch ptr=js_getrlRenderBatch(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =rlRenderBatch_copy(ctx,ptr);
		}else{
			int bufferCount=js_getint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			int currentBuffer=js_getint(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			rlVertexBuffer * vertexBuffer=js_getrlVertexBuffer_arrnc(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			rlDrawCall * draws=js_getrlDrawCall_arrnc(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			int drawCounter=js_getint(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			float currentDepth=js_getfloat(ctx,argv[5],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(rlRenderBatch){
				bufferCount,
				currentBuffer,
				vertexBuffer,
				draws,
				drawCounter,
				currentDepth
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(rlRenderBatch));
		rlRenderBatch * _returnptr=((rlRenderBatch *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_rlRenderBatch_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_rlMatrixMode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int mode=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
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
		bool error=(bool)0;
		float x=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float z=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlTranslatef(x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlRotatef(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float angle=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float x=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float z=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlRotatef(angle,x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlScalef(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float x=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float z=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlScalef(x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlMultMatrixf(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float * matf=js_getfloat_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlMultMatrixf((const float  *)matf);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlFrustum(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		double left=js_getdouble(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		double right=js_getdouble(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		double bottom=js_getdouble(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		double top=js_getdouble(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		double znear=js_getdouble(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		double zfar=js_getdouble(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		rlFrustum(left,right,bottom,top,znear,zfar);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlOrtho(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		double left=js_getdouble(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		double right=js_getdouble(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		double bottom=js_getdouble(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		double top=js_getdouble(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		double znear=js_getdouble(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		double zfar=js_getdouble(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		rlOrtho(left,right,bottom,top,znear,zfar);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlViewport(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int x=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int y=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlViewport(x,y,width,height);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetClipPlanes(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		double nearPlane=js_getdouble(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		double farPlane=js_getdouble(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
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
		bool error=(bool)0;
		int mode=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlBegin(mode);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnd(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlEnd();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertex2i(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int x=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int y=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlVertex2i(x,y);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertex2f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float x=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlVertex2f(x,y);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlVertex3f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float x=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float z=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlVertex3f(x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlTexCoord2f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float x=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlTexCoord2f(x,y);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlNormal3f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float x=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float z=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlNormal3f(x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlColor4ub(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned char r=js_getunsignedchar(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char g=js_getunsignedchar(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char b=js_getunsignedchar(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char a=js_getunsignedchar(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlColor4ub(r,g,b,a);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlColor3f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float x=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float z=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlColor3f(x,y,z);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlColor4f(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float x=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float z=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float w=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlColor4f(x,y,z,w);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableVertexArray(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int vaoId=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=rlEnableVertexArray(vaoId);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_rlDisableVertexArray(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableVertexArray();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableVertexBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlEnableVertexBuffer(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableVertexBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableVertexBuffer();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableVertexBufferElement(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlEnableVertexBufferElement(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableVertexBufferElement(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableVertexBufferElement();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableVertexAttribute(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int index=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlEnableVertexAttribute(index);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableVertexAttribute(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int index=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlDisableVertexAttribute(index);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableStatePointer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int vertexAttribType=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		void * buffer=js_getvoid_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlEnableStatePointer(vertexAttribType,buffer);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableStatePointer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int vertexAttribType=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlDisableStatePointer(vertexAttribType);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlActiveTextureSlot(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int slot=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlActiveTextureSlot(slot);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlEnableTexture(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableTexture();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableTextureCubemap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlEnableTextureCubemap(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableTextureCubemap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableTextureCubemap();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlTextureParameters(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int param=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int value=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlTextureParameters(id,param,value);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlCubemapParameters(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int param=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int value=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlCubemapParameters(id,param,value);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableShader(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlEnableShader(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDisableShader(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDisableShader();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlEnableFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
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
		bool error=(bool)0;
		int count=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlActiveDrawBuffers(count);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlBlitFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int srcX=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int srcY=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int srcWidth=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int srcHeight=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int dstX=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int dstY=js_getint(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		int dstWidth=js_getint(ctx,argv[6],&error);
		if(error==1)return JS_EXCEPTION;
		int dstHeight=js_getint(ctx,argv[7],&error);
		if(error==1)return JS_EXCEPTION;
		int bufferMask=js_getint(ctx,argv[8],&error);
		if(error==1)return JS_EXCEPTION;
		rlBlitFramebuffer(srcX,srcY,srcWidth,srcHeight,dstX,dstY,dstWidth,dstHeight,bufferMask);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlBindFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int target=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int framebuffer=js_getunsignedint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
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
		bool error=(bool)0;
		bool r=js_getbool(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool g=js_getbool(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool b=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool a=js_getbool(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlColorMask(r,g,b,a);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetCullFace(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int mode=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
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
		bool error=(bool)0;
		int x=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int y=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
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
	
	static JSValue js_rlSetPointSize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float size=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetPointSize(size);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetPointSize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		float returnVal=rlGetPointSize();
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
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
		bool error=(bool)0;
		float width=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
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
		bool error=(bool)0;
		unsigned char r=js_getunsignedchar(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char g=js_getunsignedchar(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char b=js_getunsignedchar(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char a=js_getunsignedchar(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
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
		bool error=(bool)0;
		int mode=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetBlendMode(mode);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetBlendFactors(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int glSrcFactor=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int glDstFactor=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int glEquation=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetBlendFactors(glSrcFactor,glDstFactor,glEquation);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetBlendFactorsSeparate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int glSrcRGB=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int glDstRGB=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int glSrcAlpha=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int glDstAlpha=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int glEqRGB=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int glEqAlpha=js_getint(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetBlendFactorsSeparate(glSrcRGB,glDstRGB,glSrcAlpha,glDstAlpha,glEqRGB,glEqAlpha);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlglInit(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
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
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetFramebufferWidth(width);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetFramebufferWidth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=rlGetFramebufferWidth();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlSetFramebufferHeight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int height=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
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
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<32;i++){
			int src0=returnVal[i];
			JSValue ret1=JS_NewInt32(ctx,(int32_t)((long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		return ret;
	}
	
	static JSValue js_rlLoadRenderBatch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int numBuffers=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int bufferElements=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlRenderBatch returnVal=rlLoadRenderBatch(numBuffers,bufferElements);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(rlRenderBatch));
		rlRenderBatch * ptr2_ret=((rlRenderBatch *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_rlRenderBatch_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlUnloadRenderBatch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		rlRenderBatch batch=js_getrlRenderBatch(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlUnloadRenderBatch(batch);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawRenderBatch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		rlRenderBatch * batch=js_getrlRenderBatch_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlDrawRenderBatch(batch);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetRenderBatchActive(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		rlRenderBatch * batch=js_getrlRenderBatch_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetRenderBatchActive(batch);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawRenderBatchActive(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		rlDrawRenderBatchActive();
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlCheckRenderBatchLimit(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int vCount=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=rlCheckRenderBatchLimit(vCount);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_rlSetTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetTexture(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadVertexArray(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=rlLoadVertexArray();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlLoadVertexBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * buffer=js_getvoid_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int size=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool dynamic=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlLoadVertexBuffer((const void  *)buffer,size,dynamic);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlLoadVertexBufferElement(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * buffer=js_getvoid_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int size=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool dynamic=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlLoadVertexBufferElement((const void  *)buffer,size,dynamic);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlUpdateVertexBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int bufferId=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		void * data=js_getvoid_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int offset=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlUpdateVertexBuffer(bufferId,(const void  *)data,dataSize,offset);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlUpdateVertexBufferElements(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		void * data=js_getvoid_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int dataSize=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int offset=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlUpdateVertexBufferElements(id,(const void  *)data,dataSize,offset);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlUnloadVertexArray(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int vaoId=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlUnloadVertexArray(vaoId);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlUnloadVertexBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int vboId=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlUnloadVertexBuffer(vboId);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetVertexAttribute(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int index=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int compSize=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int type=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool normalized=js_getbool(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int stride=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int offset=js_getint(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetVertexAttribute(index,compSize,type,normalized,stride,offset);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetVertexAttributeDivisor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int index=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int divisor=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetVertexAttributeDivisor(index,divisor);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawVertexArray(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int offset=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int count=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlDrawVertexArray(offset,count);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawVertexArrayElements(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int offset=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int count=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		void * buffer=js_getvoid_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlDrawVertexArrayElements(offset,count,(const void  *)buffer);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawVertexArrayInstanced(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int offset=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int count=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int instances=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlDrawVertexArrayInstanced(offset,count,instances);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlDrawVertexArrayElementsInstanced(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int offset=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int count=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		void * buffer=js_getvoid_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int instances=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlDrawVertexArrayElementsInstanced(offset,count,(const void  *)buffer,instances);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * data=js_getvoid_arrnull(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int format=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int mipmapCount=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlLoadTexture((const void  *)data,width,height,format,mipmapCount);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_rlLoadTextureDepth(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool useRenderBuffer=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlLoadTextureDepth(width,height,useRenderBuffer);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlLoadTextureCubemap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		void * data=js_getvoid_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int size=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int format=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int mipmapCount=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlLoadTextureCubemap((const void  *)data,size,format,mipmapCount);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlUpdateTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int offsetX=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int offsetY=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		int format=js_getint(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		void * data=js_getvoid_arr(ctx,argv[6],&error);
		if(error==1)return JS_EXCEPTION;
		rlUpdateTexture(id,offsetX,offsetY,width,height,format,(const void  *)data);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetGlTextureFormats(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int format=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int * glInternalFormat=js_getunsignedint_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int * glFormat=js_getunsignedint_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int * glType=js_getunsignedint_arr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlGetGlTextureFormats(format,glInternalFormat,glFormat,glType);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetPixelFormatName(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int format=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=(char  *)rlGetPixelFormatName(format);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		return ret;
	}
	
	static JSValue js_rlUnloadTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlUnloadTexture(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGenTextureMipmaps(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int format=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int * mipmaps=js_getint_arr(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		rlGenTextureMipmaps(id,width,height,format,mipmaps);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlReadTexturePixels(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int width=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int format=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned char * returnVal=(unsigned char  *)rlReadTexturePixels(id,width,height,format);
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<GetPixelDataSize(width,height,format);i++){
			unsigned char src0=returnVal[i];
			JSValue ret1=JS_NewUint32(ctx,(uint32_t)((unsigned long)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		return ret;
	}
	
	static JSValue js_rlReadScreenPixels(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int width=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int height=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		char * returnVal=rlReadScreenPixels(width,height);
		JSValue ret=JS_NewString(ctx,(const char  *)returnVal);
		return ret;
	}
	
	static JSValue js_rlLoadFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int returnVal=rlLoadFramebuffer();
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlFramebufferAttach(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int fboId=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int texId=js_getunsignedint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int attachType=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int texType=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		int mipLevel=js_getint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		rlFramebufferAttach(fboId,texId,attachType,texType,mipLevel);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlFramebufferComplete(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=rlFramebufferComplete(id);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_rlUnloadFramebuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlUnloadFramebuffer(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadShaderCode(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * vsCode=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * fsCode=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlLoadShaderCode((const char  *)vsCode,(const char  *)fsCode);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlCompileShader(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		char * shaderCode=js_getchar_arr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int type=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlCompileShader((const char  *)shaderCode,type);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlLoadShaderProgram(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int vShaderId=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int fShaderId=js_getunsignedint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlLoadShaderProgram(vShaderId,fShaderId);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlUnloadShaderProgram(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlUnloadShaderProgram(id);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetLocationUniform(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int shaderId=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * uniformName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlGetLocationUniform(shaderId,(const char  *)uniformName);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlGetLocationAttrib(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int shaderId=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		char * attribName=js_getchar_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlGetLocationAttrib(shaderId,(const char  *)attribName);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlSetUniform(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int count=js_getint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		void * value=NULL;
		int locIndex=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int uniformType=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		if(uniformType==SHADER_UNIFORM_FLOAT){
			float * val=js_getfloat_arr_arg1(ctx,argv[1],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_VEC2){
			Vector2 * val=js_getVector2_arr_arg1(ctx,argv[1],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_VEC3){
			Vector3 * val=js_getVector3_arr_arg1(ctx,argv[1],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_VEC4){
			Vector4 * val=js_getVector4_arr_arg1(ctx,argv[1],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_INT||uniformType==SHADER_UNIFORM_SAMPLER2D){
			int * val=js_getint_arr_arg1(ctx,argv[1],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_IVEC2){
			int * val=js_getint_arr_arg1(ctx,argv[1],&error,(int)2*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_IVEC3){
			int * val=js_getint_arr_arg1(ctx,argv[1],&error,(int)3*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_IVEC4){
			int * val=js_getint_arr_arg1(ctx,argv[1],&error,(int)4*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UINT){
			unsigned int * val=js_getunsignedint_arr_arg1(ctx,argv[1],&error,count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UIVEC2){
			unsigned int * val=js_getunsignedint_arr_arg1(ctx,argv[1],&error,(int)2*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UIVEC3){
			unsigned int * val=js_getunsignedint_arr_arg1(ctx,argv[1],&error,(int)3*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else if(uniformType==SHADER_UNIFORM_UIVEC4){
			unsigned int * val=js_getunsignedint_arr_arg1(ctx,argv[1],&error,(int)4*count);
			if(error==1)return JS_EXCEPTION;
			value=((void *)val);
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"unknown uniformType");
			return JS_EXCEPTION;
		}
		rlSetUniform(locIndex,(const void  *)value,uniformType,count);
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetUniformMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int locIndex=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix mat=js_getMatrix(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetUniformMatrix(locIndex,mat);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetUniformMatrices(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int locIndex=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix * mat=js_getMatrix_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int count=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetUniformMatrices(locIndex,(const Matrix  *)mat,count);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetUniformSampler(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int locIndex=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int textureId=js_getunsignedint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetUniformSampler(locIndex,textureId);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetShader(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int * locs=js_getint_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetShader(id,locs);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadComputeShaderProgram(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int shaderId=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlLoadComputeShaderProgram(shaderId);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlComputeShaderDispatch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int groupX=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int groupY=js_getunsignedint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int groupZ=js_getunsignedint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		rlComputeShaderDispatch(groupX,groupY,groupZ);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlLoadShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int size=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		void * data=js_getvoid_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int usageHint=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlLoadShaderBuffer(size,(const void  *)data,usageHint);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlUnloadShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int ssboId=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlUnloadShaderBuffer(ssboId);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlUpdateShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		void * data=js_getvoid_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int dataSize=js_getunsignedint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int offset=js_getunsignedint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlUpdateShaderBuffer(id,(const void  *)data,dataSize,offset);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlBindShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int index=js_getunsignedint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlBindShaderBuffer(id,index);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlReadShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		void * dest=js_getvoid_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int count=js_getunsignedint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int offset=js_getunsignedint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlReadShaderBuffer(id,dest,count,offset);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlCopyShaderBuffer(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int destId=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int srcId=js_getunsignedint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int destOffset=js_getunsignedint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int srcOffset=js_getunsignedint(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int count=js_getunsignedint(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		rlCopyShaderBuffer(destId,srcId,destOffset,srcOffset,count);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetShaderBufferSize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=rlGetShaderBufferSize(id);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_rlBindImageTexture(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		unsigned int id=js_getunsignedint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		unsigned int index=js_getunsignedint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int format=js_getint(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool readonly=js_getbool(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		rlBindImageTexture(id,index,format,readonly);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlGetMatrixModelview(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix returnVal=rlGetMatrixModelview();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Matrix));
		Matrix * ptr2_ret=((Matrix *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlGetMatrixProjection(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix returnVal=rlGetMatrixProjection();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Matrix));
		Matrix * ptr2_ret=((Matrix *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlGetMatrixTransform(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix returnVal=rlGetMatrixTransform();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Matrix));
		Matrix * ptr2_ret=((Matrix *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlGetMatrixProjectionStereo(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int eye=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=rlGetMatrixProjectionStereo(eye);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Matrix));
		Matrix * ptr2_ret=((Matrix *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlGetMatrixViewOffsetStereo(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int eye=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=rlGetMatrixViewOffsetStereo(eye);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Matrix));
		Matrix * ptr2_ret=((Matrix *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_rlSetMatrixProjection(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix proj=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetMatrixProjection(proj);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetMatrixModelview(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix view=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetMatrixModelview(view);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetMatrixProjectionStereo(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix right=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix left=js_getMatrix(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		rlSetMatrixProjectionStereo(right,left);
		return JS_UNDEFINED;
	}
	
	static JSValue js_rlSetMatrixViewOffsetStereo(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix right=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix left=js_getMatrix(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
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
		JS_CFUNC_DEF("rlEnableStatePointer",2,js_rlEnableStatePointer),
		JS_CFUNC_DEF("rlDisableStatePointer",1,js_rlDisableStatePointer),
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
		JS_CFUNC_DEF("rlSetPointSize",1,js_rlSetPointSize),
		JS_CFUNC_DEF("rlGetPointSize",0,js_rlGetPointSize),
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
		JS_CFUNC_DEF("rlSetUniform",4,js_rlSetUniform),
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
	
	static int js_rlgl_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsrlgl_funcs);
		JS_SetModuleExportList(ctx,m,jsrlgl_funcs,(int)listcount);
		js_declare_rlVertexBuffer(ctx,m);
		JSValue rlVertexBuffer_constr=JS_NewCFunction2(ctx,js_rlVertexBuffer_constructor,(const char  *)"rlVertexBuffer",(int)8,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"rlVertexBuffer",rlVertexBuffer_constr);
		js_declare_rlDrawCall(ctx,m);
		JSValue rlDrawCall_constr=JS_NewCFunction2(ctx,js_rlDrawCall_constructor,(const char  *)"rlDrawCall",(int)4,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"rlDrawCall",rlDrawCall_constr);
		js_declare_rlRenderBatch(ctx,m);
		JSValue rlRenderBatch_constr=JS_NewCFunction2(ctx,js_rlRenderBatch_constructor,(const char  *)"rlRenderBatch",(int)6,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"rlRenderBatch",rlRenderBatch_constr);
		JS_SetModuleExport(ctx,m,(const char  *)"RL_OPENGL_11_SOFTWARE",JS_NewInt32(ctx,(int32_t)RL_OPENGL_11_SOFTWARE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_OPENGL_11",JS_NewInt32(ctx,(int32_t)RL_OPENGL_11));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_OPENGL_21",JS_NewInt32(ctx,(int32_t)RL_OPENGL_21));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_OPENGL_33",JS_NewInt32(ctx,(int32_t)RL_OPENGL_33));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_OPENGL_43",JS_NewInt32(ctx,(int32_t)RL_OPENGL_43));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_OPENGL_ES_20",JS_NewInt32(ctx,(int32_t)RL_OPENGL_ES_20));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_OPENGL_ES_30",JS_NewInt32(ctx,(int32_t)RL_OPENGL_ES_30));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_LOG_ALL",JS_NewInt32(ctx,(int32_t)RL_LOG_ALL));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_LOG_TRACE",JS_NewInt32(ctx,(int32_t)RL_LOG_TRACE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_LOG_DEBUG",JS_NewInt32(ctx,(int32_t)RL_LOG_DEBUG));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_LOG_INFO",JS_NewInt32(ctx,(int32_t)RL_LOG_INFO));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_LOG_WARNING",JS_NewInt32(ctx,(int32_t)RL_LOG_WARNING));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_LOG_ERROR",JS_NewInt32(ctx,(int32_t)RL_LOG_ERROR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_LOG_FATAL",JS_NewInt32(ctx,(int32_t)RL_LOG_FATAL));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_LOG_NONE",JS_NewInt32(ctx,(int32_t)RL_LOG_NONE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R5G6B5",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R5G6B5));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R5G5B5A1",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R5G5B5A1));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R4G4B4A4",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R4G4B4A4));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R32",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R32));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32A32",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32A32));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R16",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R16));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16A16",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16A16));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_DXT1_RGB",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_DXT1_RGB));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_DXT1_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_DXT1_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_DXT3_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_DXT3_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_DXT5_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_DXT5_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_ETC1_RGB",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_ETC1_RGB));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_ETC2_RGB",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_ETC2_RGB));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_PVRT_RGB",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_PVRT_RGB));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_PVRT_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_PVRT_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA",JS_NewInt32(ctx,(int32_t)RL_PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_POINT",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_POINT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_BILINEAR",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_BILINEAR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_TRILINEAR",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_TRILINEAR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_ANISOTROPIC_4X",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_ANISOTROPIC_4X));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_ANISOTROPIC_8X",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_ANISOTROPIC_8X));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_ANISOTROPIC_16X",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_ANISOTROPIC_16X));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_ALPHA",JS_NewInt32(ctx,(int32_t)RL_BLEND_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_ADDITIVE",JS_NewInt32(ctx,(int32_t)RL_BLEND_ADDITIVE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_MULTIPLIED",JS_NewInt32(ctx,(int32_t)RL_BLEND_MULTIPLIED));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_ADD_COLORS",JS_NewInt32(ctx,(int32_t)RL_BLEND_ADD_COLORS));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_SUBTRACT_COLORS",JS_NewInt32(ctx,(int32_t)RL_BLEND_SUBTRACT_COLORS));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_ALPHA_PREMULTIPLY",JS_NewInt32(ctx,(int32_t)RL_BLEND_ALPHA_PREMULTIPLY));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_CUSTOM",JS_NewInt32(ctx,(int32_t)RL_BLEND_CUSTOM));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_CUSTOM_SEPARATE",JS_NewInt32(ctx,(int32_t)RL_BLEND_CUSTOM_SEPARATE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_POSITION",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_POSITION));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_TEXCOORD01",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_TEXCOORD01));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_TEXCOORD02",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_TEXCOORD02));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_NORMAL",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_NORMAL));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_TANGENT",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_TANGENT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_COLOR",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VERTEX_COLOR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MATRIX_MVP",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MATRIX_MVP));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MATRIX_VIEW",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MATRIX_VIEW));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MATRIX_PROJECTION",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MATRIX_PROJECTION));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MATRIX_MODEL",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MATRIX_MODEL));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MATRIX_NORMAL",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MATRIX_NORMAL));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VECTOR_VIEW",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_VECTOR_VIEW));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_COLOR_DIFFUSE",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_COLOR_DIFFUSE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_COLOR_SPECULAR",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_COLOR_SPECULAR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_COLOR_AMBIENT",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_COLOR_AMBIENT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_ALBEDO",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_ALBEDO));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_METALNESS",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_METALNESS));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_NORMAL",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_NORMAL));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_ROUGHNESS",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_ROUGHNESS));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_OCCLUSION",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_OCCLUSION));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_EMISSION",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_EMISSION));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_HEIGHT",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_HEIGHT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_CUBEMAP",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_CUBEMAP));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_IRRADIANCE",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_IRRADIANCE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_PREFILTER",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_PREFILTER));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_BRDF",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_BRDF));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_DIFFUSE",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_DIFFUSE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_SPECULAR",JS_NewInt32(ctx,(int32_t)RL_SHADER_LOC_MAP_SPECULAR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_FLOAT",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_FLOAT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_VEC2",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_VEC2));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_VEC3",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_VEC3));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_VEC4",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_VEC4));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_INT",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_INT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_IVEC2",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_IVEC2));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_IVEC3",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_IVEC3));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_IVEC4",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_IVEC4));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_UINT",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_UINT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_UIVEC2",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_UIVEC2));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_UIVEC3",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_UIVEC3));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_UIVEC4",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_UIVEC4));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_SAMPLER2D",JS_NewInt32(ctx,(int32_t)RL_SHADER_UNIFORM_SAMPLER2D));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_ATTRIB_FLOAT",JS_NewInt32(ctx,(int32_t)RL_SHADER_ATTRIB_FLOAT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_ATTRIB_VEC2",JS_NewInt32(ctx,(int32_t)RL_SHADER_ATTRIB_VEC2));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_ATTRIB_VEC3",JS_NewInt32(ctx,(int32_t)RL_SHADER_ATTRIB_VEC3));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SHADER_ATTRIB_VEC4",JS_NewInt32(ctx,(int32_t)RL_SHADER_ATTRIB_VEC4));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL0",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL0));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL1",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL1));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL2",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL2));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL3",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL3));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL4",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL4));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL5",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL5));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL6",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL6));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL7",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_COLOR_CHANNEL7));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_DEPTH",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_DEPTH));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_STENCIL",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_STENCIL));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_X",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_POSITIVE_X));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_X",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_NEGATIVE_X));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_Y",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_POSITIVE_Y));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_Z",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_POSITIVE_Z));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_TEXTURE2D",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_TEXTURE2D));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_RENDERBUFFER",JS_NewInt32(ctx,(int32_t)RL_ATTACHMENT_RENDERBUFFER));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_CULL_FACE_FRONT",JS_NewInt32(ctx,(int32_t)RL_CULL_FACE_FRONT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_CULL_FACE_BACK",JS_NewInt32(ctx,(int32_t)RL_CULL_FACE_BACK));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_DEFAULT_BATCH_BUFFER_ELEMENTS",JS_NewInt32(ctx,(int32_t)RL_DEFAULT_BATCH_BUFFER_ELEMENTS));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_S",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_S));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_T",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_T));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_MAG_FILTER",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_MAG_FILTER));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_MIN_FILTER",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_MIN_FILTER));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_NEAREST",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_NEAREST));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_LINEAR",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_LINEAR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_MIP_NEAREST",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_MIP_NEAREST));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_MIP_LINEAR",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_MIP_LINEAR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_ANISOTROPIC",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_FILTER_ANISOTROPIC));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_MIPMAP_BIAS_RATIO",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_MIPMAP_BIAS_RATIO));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_REPEAT",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_REPEAT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_CLAMP",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_CLAMP));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_MIRROR_REPEAT",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_MIRROR_REPEAT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_MIRROR_CLAMP",JS_NewInt32(ctx,(int32_t)RL_TEXTURE_WRAP_MIRROR_CLAMP));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_MODELVIEW",JS_NewInt32(ctx,(int32_t)RL_MODELVIEW));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_PROJECTION",JS_NewInt32(ctx,(int32_t)RL_PROJECTION));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TEXTURE",JS_NewInt32(ctx,(int32_t)RL_TEXTURE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_LINES",JS_NewInt32(ctx,(int32_t)RL_LINES));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_TRIANGLES",JS_NewInt32(ctx,(int32_t)RL_TRIANGLES));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_QUADS",JS_NewInt32(ctx,(int32_t)RL_QUADS));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_UNSIGNED_BYTE",JS_NewInt32(ctx,(int32_t)RL_UNSIGNED_BYTE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_FLOAT",JS_NewInt32(ctx,(int32_t)RL_FLOAT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_STREAM_DRAW",JS_NewInt32(ctx,(int32_t)RL_STREAM_DRAW));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_STREAM_READ",JS_NewInt32(ctx,(int32_t)RL_STREAM_READ));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_STREAM_COPY",JS_NewInt32(ctx,(int32_t)RL_STREAM_COPY));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_STATIC_DRAW",JS_NewInt32(ctx,(int32_t)RL_STATIC_DRAW));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_STATIC_READ",JS_NewInt32(ctx,(int32_t)RL_STATIC_READ));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_STATIC_COPY",JS_NewInt32(ctx,(int32_t)RL_STATIC_COPY));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_DYNAMIC_DRAW",JS_NewInt32(ctx,(int32_t)RL_DYNAMIC_DRAW));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_DYNAMIC_READ",JS_NewInt32(ctx,(int32_t)RL_DYNAMIC_READ));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_DYNAMIC_COPY",JS_NewInt32(ctx,(int32_t)RL_DYNAMIC_COPY));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_FRAGMENT_SHADER",JS_NewInt32(ctx,(int32_t)RL_FRAGMENT_SHADER));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_VERTEX_SHADER",JS_NewInt32(ctx,(int32_t)RL_VERTEX_SHADER));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_COMPUTE_SHADER",JS_NewInt32(ctx,(int32_t)RL_COMPUTE_SHADER));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ZERO",JS_NewInt32(ctx,(int32_t)RL_ZERO));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ONE",JS_NewInt32(ctx,(int32_t)RL_ONE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SRC_COLOR",JS_NewInt32(ctx,(int32_t)RL_SRC_COLOR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_SRC_COLOR",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_SRC_COLOR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SRC_ALPHA",JS_NewInt32(ctx,(int32_t)RL_SRC_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_SRC_ALPHA",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_SRC_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_DST_ALPHA",JS_NewInt32(ctx,(int32_t)RL_DST_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_DST_ALPHA",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_DST_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_DST_COLOR",JS_NewInt32(ctx,(int32_t)RL_DST_COLOR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_DST_COLOR",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_DST_COLOR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_SRC_ALPHA_SATURATE",JS_NewInt32(ctx,(int32_t)RL_SRC_ALPHA_SATURATE));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_CONSTANT_COLOR",JS_NewInt32(ctx,(int32_t)RL_CONSTANT_COLOR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_CONSTANT_COLOR",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_CONSTANT_COLOR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_CONSTANT_ALPHA",JS_NewInt32(ctx,(int32_t)RL_CONSTANT_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_CONSTANT_ALPHA",JS_NewInt32(ctx,(int32_t)RL_ONE_MINUS_CONSTANT_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_FUNC_ADD",JS_NewInt32(ctx,(int32_t)RL_FUNC_ADD));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_MIN",JS_NewInt32(ctx,(int32_t)RL_MIN));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_MAX",JS_NewInt32(ctx,(int32_t)RL_MAX));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_FUNC_SUBTRACT",JS_NewInt32(ctx,(int32_t)RL_FUNC_SUBTRACT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_FUNC_REVERSE_SUBTRACT",JS_NewInt32(ctx,(int32_t)RL_FUNC_REVERSE_SUBTRACT));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_EQUATION",JS_NewInt32(ctx,(int32_t)RL_BLEND_EQUATION));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_EQUATION_RGB",JS_NewInt32(ctx,(int32_t)RL_BLEND_EQUATION_RGB));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_EQUATION_ALPHA",JS_NewInt32(ctx,(int32_t)RL_BLEND_EQUATION_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_DST_RGB",JS_NewInt32(ctx,(int32_t)RL_BLEND_DST_RGB));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_SRC_RGB",JS_NewInt32(ctx,(int32_t)RL_BLEND_SRC_RGB));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_DST_ALPHA",JS_NewInt32(ctx,(int32_t)RL_BLEND_DST_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_SRC_ALPHA",JS_NewInt32(ctx,(int32_t)RL_BLEND_SRC_ALPHA));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_BLEND_COLOR",JS_NewInt32(ctx,(int32_t)RL_BLEND_COLOR));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_READ_FRAMEBUFFER",JS_NewInt32(ctx,(int32_t)RL_READ_FRAMEBUFFER));
		JS_SetModuleExport(ctx,m,(const char  *)"RL_DRAW_FRAMEBUFFER",JS_NewInt32(ctx,(int32_t)RL_DRAW_FRAMEBUFFER));
		return 0;
	}
	
	JSModuleDef * js_init_module_rlgl(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_rlgl_init);
		if(!m)return NULL;
		size_t listcount=countof(jsrlgl_funcs);
		JS_AddModuleExportList(ctx,m,jsrlgl_funcs,(int)listcount);
		JS_AddModuleExport(ctx,m,(const char  *)"rlVertexBuffer");
		JS_AddModuleExport(ctx,m,(const char  *)"rlDrawCall");
		JS_AddModuleExport(ctx,m,(const char  *)"rlRenderBatch");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_OPENGL_11_SOFTWARE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_OPENGL_11");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_OPENGL_21");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_OPENGL_33");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_OPENGL_43");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_OPENGL_ES_20");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_OPENGL_ES_30");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_LOG_ALL");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_LOG_TRACE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_LOG_DEBUG");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_LOG_INFO");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_LOG_WARNING");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_LOG_ERROR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_LOG_FATAL");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_LOG_NONE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R5G6B5");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R5G5B5A1");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R4G4B4A4");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R32");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32A32");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R16");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16A16");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_DXT1_RGB");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_DXT1_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_DXT3_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_DXT5_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_ETC1_RGB");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_ETC2_RGB");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_PVRT_RGB");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_PVRT_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_POINT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_BILINEAR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_TRILINEAR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_ANISOTROPIC_4X");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_ANISOTROPIC_8X");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_ANISOTROPIC_16X");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_ADDITIVE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_MULTIPLIED");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_ADD_COLORS");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_SUBTRACT_COLORS");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_ALPHA_PREMULTIPLY");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_CUSTOM");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_CUSTOM_SEPARATE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_POSITION");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_TEXCOORD01");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_TEXCOORD02");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_NORMAL");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_TANGENT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VERTEX_COLOR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MATRIX_MVP");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MATRIX_VIEW");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MATRIX_PROJECTION");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MATRIX_MODEL");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MATRIX_NORMAL");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_VECTOR_VIEW");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_COLOR_DIFFUSE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_COLOR_SPECULAR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_COLOR_AMBIENT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_ALBEDO");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_METALNESS");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_NORMAL");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_ROUGHNESS");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_OCCLUSION");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_EMISSION");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_HEIGHT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_CUBEMAP");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_IRRADIANCE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_PREFILTER");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_BRDF");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_DIFFUSE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_LOC_MAP_SPECULAR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_FLOAT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_VEC2");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_VEC3");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_VEC4");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_INT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_IVEC2");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_IVEC3");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_IVEC4");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_UINT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_UIVEC2");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_UIVEC3");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_UIVEC4");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_UNIFORM_SAMPLER2D");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_ATTRIB_FLOAT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_ATTRIB_VEC2");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_ATTRIB_VEC3");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SHADER_ATTRIB_VEC4");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL0");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL1");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL2");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL3");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL4");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL5");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL6");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_COLOR_CHANNEL7");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_DEPTH");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_STENCIL");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_X");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_X");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_Y");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_Y");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_POSITIVE_Z");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_CUBEMAP_NEGATIVE_Z");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_TEXTURE2D");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ATTACHMENT_RENDERBUFFER");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_CULL_FACE_FRONT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_CULL_FACE_BACK");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_DEFAULT_BATCH_BUFFER_ELEMENTS");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_S");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_T");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_MAG_FILTER");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_MIN_FILTER");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_NEAREST");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_LINEAR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_MIP_NEAREST");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_NEAREST_MIP_LINEAR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_LINEAR_MIP_NEAREST");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_MIP_LINEAR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_FILTER_ANISOTROPIC");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_MIPMAP_BIAS_RATIO");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_REPEAT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_CLAMP");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_MIRROR_REPEAT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE_WRAP_MIRROR_CLAMP");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_MODELVIEW");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_PROJECTION");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TEXTURE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_LINES");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_TRIANGLES");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_QUADS");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_UNSIGNED_BYTE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_FLOAT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_STREAM_DRAW");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_STREAM_READ");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_STREAM_COPY");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_STATIC_DRAW");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_STATIC_READ");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_STATIC_COPY");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_DYNAMIC_DRAW");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_DYNAMIC_READ");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_DYNAMIC_COPY");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_FRAGMENT_SHADER");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_VERTEX_SHADER");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_COMPUTE_SHADER");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ZERO");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ONE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SRC_COLOR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_SRC_COLOR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SRC_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_SRC_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_DST_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_DST_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_DST_COLOR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_DST_COLOR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_SRC_ALPHA_SATURATE");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_CONSTANT_COLOR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_CONSTANT_COLOR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_CONSTANT_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_ONE_MINUS_CONSTANT_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_FUNC_ADD");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_MIN");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_MAX");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_FUNC_SUBTRACT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_FUNC_REVERSE_SUBTRACT");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_EQUATION");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_EQUATION_RGB");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_EQUATION_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_DST_RGB");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_SRC_RGB");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_DST_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_SRC_ALPHA");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_BLEND_COLOR");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_READ_FRAMEBUFFER");
		JS_AddModuleExport(ctx,m,(const char  *)"RL_DRAW_FRAMEBUFFER");
		return m;
	}

#endif //JS_rlgl_GUARD