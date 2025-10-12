#ifndef JS_raymath_GUARD
	#define JS_raymath_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <raylib.h>
	#include <raymath.h>
	
	static float js_getfloat(JSContext * ctx,JSValue src,bool * error);
	
	static float * js_getfloat_arr3(JSContext * ctx,JSValue src,bool * error){
		float * ret;
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
			ret =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_ret,src);
		}else if(js_IsArrayLength(ctx,src,(int64_t)3)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret<3){
				JS_ThrowTypeError(ctx,(const char *)"src too short (3)");
				error[0]=(bool)1;
				return NULL;
			}
			size_ret =(int64_t)3;
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(float *)js_malloc(ctx,size_ret*sizeof(float));
			int i;
			for(i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					double double_reti;
					JS_ToFloat64(ctx,&double_reti,src0);
					ret[i] =((float)double_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char *)"src0 does not match type float *");
					error[0]=(bool)1;
					return NULL;
				}
			}
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(float *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			ret =(float *)js_malloc(ctx,size_ret);
			memcpy((void *)ret,(const void *)ret,size_ret);
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"src does not match type float *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static float * js_getfloat_arr16(JSContext * ctx,JSValue src,bool * error){
		float * ret;
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
			ret =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_ret,src);
		}else if(js_IsArrayLength(ctx,src,(int64_t)16)){
			int64_t size_ret;
			if(JS_GetLength(ctx,src,&size_ret)==-1){
				error[0]=(bool)1;
				return NULL;
			}
			if(size_ret<16){
				JS_ThrowTypeError(ctx,(const char *)"src too short (16)");
				error[0]=(bool)1;
				return NULL;
			}
			size_ret =(int64_t)16;
			if(size_ret==0){
				JS_ThrowTypeError(ctx,(const char *)"Received empty array");
				error[0]=(bool)1;
				return NULL;
			}
			ret =(float *)js_malloc(ctx,size_ret*sizeof(float));
			int i;
			for(i=0;i<size_ret;i++){
				JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				JS_FreeValue(ctx,src0);
				if(JS_IsNumber(src0)){
					double double_reti;
					JS_ToFloat64(ctx,&double_reti,src0);
					ret[i] =((float)double_reti);
				}else{
					JS_ThrowTypeError(ctx,(const char *)"src0 does not match type float *");
					error[0]=(bool)1;
					return NULL;
				}
			}
		}else if(JS_GetClassID(src)==JS_CLASS_FLOAT32_ARRAY){
			size_t offset_ret;
			size_t size_ret;
			JSValue da_ret=JS_GetTypedArrayBuffer(ctx,src,&offset_ret,&size_ret,NULL);
			ret =(float *)JS_GetArrayBuffer(ctx,&size_ret,da_ret);
			ret +=offset_ret;
			size_ret -=offset_ret;
			ret =(float *)js_malloc(ctx,size_ret);
			memcpy((void *)ret,(const void *)ret,size_ret);
			JS_FreeValuePtr(ctx,&da_ret);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"src does not match type float *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static Vector2 js_getVector2(JSContext * ctx,JSValue src,bool * error);
	
	static Matrix js_getMatrix(JSContext * ctx,JSValue src,bool * error);
	
	static Vector3 js_getVector3(JSContext * ctx,JSValue src,bool * error);
	
	static Vector3 * js_getVector3_ptr(JSContext * ctx,JSValue src,bool * error);
	
	static Quaternion js_getQuaternion(JSContext * ctx,JSValue src,bool * error);
	
	static Vector4 js_getVector4(JSContext * ctx,JSValue src,bool * error);
	
	static double js_getdouble(JSContext * ctx,JSValue src,bool * error);
	
	static Vector3 * js_getVector3_arr(JSContext * ctx,JSValue src,bool * error);
	
	static float * js_getfloat_arr(JSContext * ctx,JSValue src,bool * error);
	
	static Quaternion * js_getQuaternion_ptr(JSContext * ctx,JSValue src,bool * error){
		Quaternion * ret;
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
			if(JS_GetClassID(src0)==js_Vector4_class_id){
				if(size_ret==0){
					JS_ThrowTypeError(ctx,(const char *)"Received empty array");
					error[0]=(bool)1;
					return NULL;
				}
				ret =(Quaternion *)js_malloc(ctx,size_ret*sizeof(Vector4));
				int i;
				for(i=0;i<size_ret;i++){
					src0 =JS_GetPropertyUint32(ctx,src,(uint32_t)i);
					JS_FreeValue(ctx,src0);
					if(JS_GetClassID(src0)==js_Vector4_class_id){
						ret[i] =*(Quaternion *)JS_GetOpaque(src0,js_Vector4_class_id);
					}else{
						JS_ThrowTypeError(ctx,(const char *)"src0 does not match type Quaternion *");
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
				ret =(Quaternion *)js_malloc(ctx,size_ret*sizeof(float));
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
							JS_ThrowTypeError(ctx,(const char *)"src0 does not match type Quaternion *");
							error[0]=(bool)1;
							return NULL;
						}
					}
					i +=3;
				}
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type Quaternion *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_Vector4_class_id){
			if(JS_GetClassID(src)==js_Vector4_class_id){
				ret =(Quaternion *)JS_GetOpaque(src,js_Vector4_class_id);
			}else{
				JS_ThrowTypeError(ctx,(const char *)"src does not match type Quaternion *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char *)"src does not match type Quaternion *");
			error[0]=(bool)1;
			return NULL;
		}
		if(is_arrayProxy)JS_FreeValue(ctx,src);
		return ret;
	}
	
	static void js_float3_finalizer(JSRuntime * rt,JSValue val){
		float3 * ptr=(float3 *)JS_GetOpaque(val,js_float3_class_id);
		if(ptr)js_free_rt(rt,(void *)ptr);
	}
	
	static JSValue js_float3_v_values(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		float3 * ptr=(float3 *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		int i;
		for(i=0;i<3;i++){
			JSValue js_ret=JS_NewFloat64(ctx,((double)ptr[0].v[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_float3_v_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		float3 * ptr=(float3 *)ptr_u;
		int length=(int)3;
		keys[0] =(JSPropertyEnum *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		int i;
		for(i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_float3_v_get(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		float3 * ptr=(float3 *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)3));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<3){
				float src=ptr[0].v[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_float3_v_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		float3 * ptr=(float3 *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			bool error=(bool)0;
			float ret=js_getfloat(ctx,set_to,&error);
			if(error==1)return 0;
			ptr[0].v[property] =ret;
		}
		return true;
	}
	
	static int js_float3_v_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		float3 * ptr=(float3 *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<3){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_float3_get_v(JSContext * ctx,JSValue this_val){
		float3 * ptr=(float3 *)JS_GetOpaque2(ctx,this_val,js_float3_class_id);
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = this_val,.opaque = ptr,.values = js_float3_v_values,.keys = js_float3_v_keys,.get = js_float3_v_get,.set = js_float3_v_set,.has = js_float3_v_has});
		return ret;
	}
	
	static JSValue js_float3_set_v(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		float3 * ptr=(float3 *)JS_GetOpaque2(ctx,this_val,js_float3_class_id);
		float * value=js_getfloat_arr3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		memcpy((void *)ptr[0].v,(const void *)value,3*sizeof(float));
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_float3_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","float3", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("v",js_float3_get_v,js_float3_set_v)
	};
	
	static int js_declare_float3(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_float3_class_id);
		JSClassDef js_float3_def={ .class_name = "float3", .finalizer = js_float3_finalizer };
		JS_NewClass(rt,js_float3_class_id,(const JSClassDef *)&js_float3_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_float3_proto_funcs,(int)countof(js_float3_proto_funcs));
		JS_SetClassProto(ctx,js_float3_class_id,proto);
		return 0;
	}
	
	static void js_float16_finalizer(JSRuntime * rt,JSValue val){
		float16 * ptr=(float16 *)JS_GetOpaque(val,js_float16_class_id);
		if(ptr)js_free_rt(rt,(void *)ptr);
	}
	
	static JSValue js_float16_v_values(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		float16 * ptr=(float16 *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		int i;
		for(i=0;i<16;i++){
			JSValue js_ret=JS_NewFloat64(ctx,((double)ptr[0].v[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_float16_v_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		float16 * ptr=(float16 *)ptr_u;
		int length=(int)16;
		keys[0] =(JSPropertyEnum *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		int i;
		for(i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_float16_v_get(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		float16 * ptr=(float16 *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)((long)16));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<16){
				float src=ptr[0].v[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_float16_v_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		float16 * ptr=(float16 *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			bool error=(bool)0;
			float ret=js_getfloat(ctx,set_to,&error);
			if(error==1)return 0;
			ptr[0].v[property] =ret;
		}
		return true;
	}
	
	static int js_float16_v_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		float16 * ptr=(float16 *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<16){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_float16_get_v(JSContext * ctx,JSValue this_val){
		float16 * ptr=(float16 *)JS_GetOpaque2(ctx,this_val,js_float16_class_id);
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = this_val,.opaque = ptr,.values = js_float16_v_values,.keys = js_float16_v_keys,.get = js_float16_v_get,.set = js_float16_v_set,.has = js_float16_v_has});
		return ret;
	}
	
	static JSValue js_float16_set_v(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		float16 * ptr=(float16 *)JS_GetOpaque2(ctx,this_val,js_float16_class_id);
		float * value=js_getfloat_arr16(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		memcpy((void *)ptr[0].v,(const void *)value,16*sizeof(float));
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_float16_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","float16", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("v",js_float16_get_v,js_float16_set_v)
	};
	
	static int js_declare_float16(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_float16_class_id);
		JSClassDef js_float16_def={ .class_name = "float16", .finalizer = js_float16_finalizer };
		JS_NewClass(rt,js_float16_class_id,(const JSClassDef *)&js_float16_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_float16_proto_funcs,(int)countof(js_float16_proto_funcs));
		JS_SetClassProto(ctx,js_float16_class_id,proto);
		return 0;
	}
	
	static JSValue js_float3_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			float3 * ptr__return=(float3 *)js_calloc(ctx,(size_t)1,sizeof(float3));
			JSValue _return=JS_NewObjectClass(ctx,(int)js_float3_class_id);
			JS_SetOpaque(_return,(void *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		float * v=js_getfloat_arr3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float3 _struct={
			{v[0],v[1],v[2]}
		};
		float3 * ptr__return=(float3 *)js_malloc(ctx,sizeof(float3));
		ptr__return[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,(int)js_float3_class_id);
		JS_SetOpaque(_return,(void *)ptr__return);
		return _return;
	}
	
	static JSValue js_float16_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			float16 * ptr__return=(float16 *)js_calloc(ctx,(size_t)1,sizeof(float16));
			JSValue _return=JS_NewObjectClass(ctx,(int)js_float16_class_id);
			JS_SetOpaque(_return,(void *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		float * v=js_getfloat_arr16(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float16 _struct={
			{v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],v[10],v[11],v[12],v[13],v[14],v[15]}
		};
		float16 * ptr__return=(float16 *)js_malloc(ctx,sizeof(float16));
		ptr__return[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,(int)js_float16_class_id);
		JS_SetOpaque(_return,(void *)ptr__return);
		return _return;
	}
	
	static JSValue js_Clamp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float value=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float min=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float max=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Clamp(value,min,max);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Lerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float start=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float end=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float amount=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Lerp(start,end,amount);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Normalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float value=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float start=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float end=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Normalize(value,start,end);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Remap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float value=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float inputStart=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float inputEnd=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float outputStart=js_getfloat(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float outputEnd=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Remap(value,inputStart,inputEnd,outputStart,outputEnd);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Wrap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float value=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float min=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float max=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Wrap(value,min,max);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_FloatEquals(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float x=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=FloatEquals(x,y);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2Zero(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 returnVal=Vector2Zero();
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2One(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 returnVal=Vector2One();
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Add(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Add(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2AddValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float add=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2AddValue(v,add);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Subtract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Subtract(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2SubtractValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float sub=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2SubtractValue(v,sub);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Length(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector2Length(v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2LengthSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector2LengthSqr(v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2DotProduct(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector2DotProduct(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2CrossProduct(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector2CrossProduct(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2Distance(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector2Distance(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2DistanceSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector2DistanceSqr(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2Angle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector2Angle(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2LineAngle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 start=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 end=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector2LineAngle(start,end);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2Scale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float scale=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Scale(v,scale);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Multiply(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Multiply(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Negate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Negate(v);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Divide(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Divide(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Normalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Normalize(v);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Transform(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix mat=js_getMatrix(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Transform(v,mat);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Lerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float amount=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Lerp(v1,v2,amount);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Reflect(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 normal=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Reflect(v,normal);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Min(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Min(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Max(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v1=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 v2=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Max(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Rotate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float angle=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Rotate(v,angle);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2MoveTowards(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 target=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float maxDistance=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2MoveTowards(v,target,maxDistance);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Invert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Invert(v);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Clamp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 min=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 max=js_getVector2(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Clamp(v,min,max);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2ClampValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float min=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float max=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2ClampValue(v,min,max);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Equals(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 p=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 q=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=Vector2Equals(p,q);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2Refract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector2 v=js_getVector2(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 n=js_getVector2(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float r=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector2 returnVal=Vector2Refract(v,n,r);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Zero(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 returnVal=Vector3Zero();
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3One(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 returnVal=Vector3One();
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Add(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Add(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3AddValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float add=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3AddValue(v,add);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Subtract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Subtract(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3SubtractValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float sub=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3SubtractValue(v,sub);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Scale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float scalar=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Scale(v,scalar);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Multiply(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Multiply(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3CrossProduct(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3CrossProduct(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Perpendicular(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Perpendicular(v);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Length(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector3Length((const Vector3)v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3LengthSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector3LengthSqr((const Vector3)v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3DotProduct(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector3DotProduct(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3Distance(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector3Distance(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3DistanceSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector3DistanceSqr(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3Angle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector3Angle(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3Negate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Negate(v);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Divide(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Divide(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Normalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Normalize(v);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Project(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Project(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Reject(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Reject(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3OrthoNormalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 * v1=js_getVector3_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 * v2=js_getVector3_ptr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3OrthoNormalize(v1,v2);
		JS_SetOpaque(argv[0],(void *)v1);
		JS_SetOpaque(argv[1],(void *)v2);
		return JS_UNDEFINED;
	}
	
	static JSValue js_Vector3Transform(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix mat=js_getMatrix(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Transform(v,mat);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3RotateByQuaternion(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion q=js_getQuaternion(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3RotateByQuaternion(v,q);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3RotateByAxisAngle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 axis=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float angle=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3RotateByAxisAngle(v,axis,angle);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3MoveTowards(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 target=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float maxDistance=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3MoveTowards(v,target,maxDistance);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Lerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float amount=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Lerp(v1,v2,amount);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3CubicHermite(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 tangent1=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 tangent2=js_getVector3(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float amount=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3CubicHermite(v1,tangent1,v2,tangent2,amount);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Reflect(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 normal=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Reflect(v,normal);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Min(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Min(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Max(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v1=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 v2=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Max(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Barycenter(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 p=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 a=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 b=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 c=js_getVector3(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Barycenter(p,a,b,c);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Unproject(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 source=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix projection=js_getMatrix(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix view=js_getMatrix(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Unproject(source,projection,view);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3ToFloatV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float3 returnVal=Vector3ToFloatV(v);
		float3 * ptr_ret=(float3 *)js_malloc(ctx,sizeof(float3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_float3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Invert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Invert(v);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Clamp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 min=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 max=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Clamp(v,min,max);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3ClampValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float min=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float max=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3ClampValue(v,min,max);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Equals(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 p=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 q=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=Vector3Equals(p,q);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3Refract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 v=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 n=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float r=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=Vector3Refract(v,n,r);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Zero(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 returnVal=Vector4Zero();
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4One(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 returnVal=Vector4One();
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Add(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v1=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 v2=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4Add(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4AddValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float add=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4AddValue(v,add);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Subtract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v1=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 v2=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4Subtract(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4SubtractValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float add=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4SubtractValue(v,add);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Length(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector4Length(v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector4LengthSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector4LengthSqr(v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector4DotProduct(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v1=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 v2=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector4DotProduct(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector4Distance(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v1=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 v2=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector4Distance(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector4DistanceSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v1=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 v2=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=Vector4DistanceSqr(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector4Scale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float scale=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4Scale(v,scale);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Multiply(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v1=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 v2=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4Multiply(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Negate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4Negate(v);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Divide(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v1=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 v2=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4Divide(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Normalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4Normalize(v);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Min(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v1=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 v2=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4Min(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Max(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v1=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 v2=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4Max(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Lerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v1=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 v2=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float amount=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4Lerp(v1,v2,amount);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4MoveTowards(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 target=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float maxDistance=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4MoveTowards(v,target,maxDistance);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Invert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 v=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 returnVal=Vector4Invert(v);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Equals(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector4 p=js_getVector4(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector4 q=js_getVector4(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=Vector4Equals(p,q);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_MatrixDeterminant(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix mat=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=MatrixDeterminant(mat);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_MatrixTrace(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix mat=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=MatrixTrace(mat);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_MatrixTranspose(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix mat=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixTranspose(mat);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixInvert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix mat=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixInvert(mat);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixIdentity(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix returnVal=MatrixIdentity();
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixAdd(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix left=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix right=js_getMatrix(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixAdd(left,right);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixSubtract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix left=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix right=js_getMatrix(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixSubtract(left,right);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixMultiply(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix left=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix right=js_getMatrix(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixMultiply(left,right);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixTranslate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float x=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float z=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixTranslate(x,y,z);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 axis=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float angle=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixRotate(axis,angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotateX(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float angle=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixRotateX(angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotateY(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float angle=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixRotateY(angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotateZ(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float angle=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixRotateZ(angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotateXYZ(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 angle=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixRotateXYZ(angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotateZYX(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 angle=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixRotateZYX(angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixScale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float x=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float y=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float z=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixScale(x,y,z);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixFrustum(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		double left=js_getdouble(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		double right=js_getdouble(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		double bottom=js_getdouble(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		double top=js_getdouble(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		double nearPlane=js_getdouble(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		double farPlane=js_getdouble(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixFrustum(left,right,bottom,top,nearPlane,farPlane);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixPerspective(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		double fovY=js_getdouble(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		double aspect=js_getdouble(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		double nearPlane=js_getdouble(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		double farPlane=js_getdouble(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixPerspective(fovY,aspect,nearPlane,farPlane);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixOrtho(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		double left=js_getdouble(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		double right=js_getdouble(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		double bottom=js_getdouble(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		double top=js_getdouble(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		double nearPlane=js_getdouble(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		double farPlane=js_getdouble(ctx,argv[5],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixOrtho(left,right,bottom,top,nearPlane,farPlane);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixLookAt(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 eye=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 target=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 up=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=MatrixLookAt(eye,target,up);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixToFloatV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix mat=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float16 returnVal=MatrixToFloatV(mat);
		float16 * ptr_ret=(float16 *)js_malloc(ctx,sizeof(float16));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_float16_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionAdd(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q1=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion q2=js_getQuaternion(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionAdd(q1,q2);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionAddValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float add=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionAddValue(q,add);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionSubtract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q1=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion q2=js_getQuaternion(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionSubtract(q1,q2);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionSubtractValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float sub=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionSubtractValue(q,sub);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionIdentity(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion returnVal=QuaternionIdentity();
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionLength(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float returnVal=QuaternionLength(q);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_QuaternionNormalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionNormalize(q);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionInvert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionInvert(q);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionMultiply(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q1=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion q2=js_getQuaternion(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionMultiply(q1,q2);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionScale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float mul=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionScale(q,mul);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionDivide(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q1=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion q2=js_getQuaternion(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionDivide(q1,q2);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionLerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q1=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion q2=js_getQuaternion(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float amount=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionLerp(q1,q2,amount);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionNlerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q1=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion q2=js_getQuaternion(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float amount=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionNlerp(q1,q2,amount);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionSlerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q1=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion q2=js_getQuaternion(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float amount=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionSlerp(q1,q2,amount);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionCubicHermiteSpline(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q1=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion outTangent1=js_getQuaternion(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion q2=js_getQuaternion(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion inTangent2=js_getQuaternion(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		float t=js_getfloat(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionCubicHermiteSpline(q1,outTangent1,q2,inTangent2,t);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionFromVector3ToVector3(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 from=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 to=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionFromVector3ToVector3(from,to);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionFromMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix mat=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionFromMatrix(mat);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionToMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=QuaternionToMatrix(q);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionFromAxisAngle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Vector3 axis=js_getVector3(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float angle=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionFromAxisAngle(axis,angle);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionToAxisAngle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Quaternion q=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 * outAxis=js_getVector3_arr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float * outAngle=js_getfloat_arr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		QuaternionToAxisAngle(q,outAxis,outAngle);
		memoryClear(ctx,memoryHead);
		return JS_UNDEFINED;
	}
	
	static JSValue js_QuaternionFromEuler(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		float pitch=js_getfloat(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float yaw=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		float roll=js_getfloat(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionFromEuler(pitch,yaw,roll);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionToEuler(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=QuaternionToEuler(q);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionTransform(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion q=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix mat=js_getMatrix(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion returnVal=QuaternionTransform(q,mat);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionEquals(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Quaternion p=js_getQuaternion(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion q=js_getQuaternion(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		int returnVal=QuaternionEquals(p,q);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_MatrixDecompose(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Matrix mat=js_getMatrix(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 * translation=js_getVector3_ptr(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Quaternion * rotation=js_getQuaternion_ptr(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 * scale=js_getVector3_ptr(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		MatrixDecompose(mat,translation,rotation,scale);
		JS_SetOpaque(argv[1],(void *)translation);
		JS_SetOpaque(argv[2],(void *)rotation);
		JS_SetOpaque(argv[3],(void *)scale);
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry jsraymath_funcs[]={
		JS_CFUNC_DEF("Clamp",3,js_Clamp),
		JS_CFUNC_DEF("Lerp",3,js_Lerp),
		JS_CFUNC_DEF("Normalize",3,js_Normalize),
		JS_CFUNC_DEF("Remap",5,js_Remap),
		JS_CFUNC_DEF("Wrap",3,js_Wrap),
		JS_CFUNC_DEF("FloatEquals",2,js_FloatEquals),
		JS_CFUNC_DEF("Vector2Zero",0,js_Vector2Zero),
		JS_CFUNC_DEF("Vector2One",0,js_Vector2One),
		JS_CFUNC_DEF("Vector2Add",2,js_Vector2Add),
		JS_CFUNC_DEF("Vector2AddValue",2,js_Vector2AddValue),
		JS_CFUNC_DEF("Vector2Subtract",2,js_Vector2Subtract),
		JS_CFUNC_DEF("Vector2SubtractValue",2,js_Vector2SubtractValue),
		JS_CFUNC_DEF("Vector2Length",1,js_Vector2Length),
		JS_CFUNC_DEF("Vector2LengthSqr",1,js_Vector2LengthSqr),
		JS_CFUNC_DEF("Vector2DotProduct",2,js_Vector2DotProduct),
		JS_CFUNC_DEF("Vector2CrossProduct",2,js_Vector2CrossProduct),
		JS_CFUNC_DEF("Vector2Distance",2,js_Vector2Distance),
		JS_CFUNC_DEF("Vector2DistanceSqr",2,js_Vector2DistanceSqr),
		JS_CFUNC_DEF("Vector2Angle",2,js_Vector2Angle),
		JS_CFUNC_DEF("Vector2LineAngle",2,js_Vector2LineAngle),
		JS_CFUNC_DEF("Vector2Scale",2,js_Vector2Scale),
		JS_CFUNC_DEF("Vector2Multiply",2,js_Vector2Multiply),
		JS_CFUNC_DEF("Vector2Negate",1,js_Vector2Negate),
		JS_CFUNC_DEF("Vector2Divide",2,js_Vector2Divide),
		JS_CFUNC_DEF("Vector2Normalize",1,js_Vector2Normalize),
		JS_CFUNC_DEF("Vector2Transform",2,js_Vector2Transform),
		JS_CFUNC_DEF("Vector2Lerp",3,js_Vector2Lerp),
		JS_CFUNC_DEF("Vector2Reflect",2,js_Vector2Reflect),
		JS_CFUNC_DEF("Vector2Min",2,js_Vector2Min),
		JS_CFUNC_DEF("Vector2Max",2,js_Vector2Max),
		JS_CFUNC_DEF("Vector2Rotate",2,js_Vector2Rotate),
		JS_CFUNC_DEF("Vector2MoveTowards",3,js_Vector2MoveTowards),
		JS_CFUNC_DEF("Vector2Invert",1,js_Vector2Invert),
		JS_CFUNC_DEF("Vector2Clamp",3,js_Vector2Clamp),
		JS_CFUNC_DEF("Vector2ClampValue",3,js_Vector2ClampValue),
		JS_CFUNC_DEF("Vector2Equals",2,js_Vector2Equals),
		JS_CFUNC_DEF("Vector2Refract",3,js_Vector2Refract),
		JS_CFUNC_DEF("Vector3Zero",0,js_Vector3Zero),
		JS_CFUNC_DEF("Vector3One",0,js_Vector3One),
		JS_CFUNC_DEF("Vector3Add",2,js_Vector3Add),
		JS_CFUNC_DEF("Vector3AddValue",2,js_Vector3AddValue),
		JS_CFUNC_DEF("Vector3Subtract",2,js_Vector3Subtract),
		JS_CFUNC_DEF("Vector3SubtractValue",2,js_Vector3SubtractValue),
		JS_CFUNC_DEF("Vector3Scale",2,js_Vector3Scale),
		JS_CFUNC_DEF("Vector3Multiply",2,js_Vector3Multiply),
		JS_CFUNC_DEF("Vector3CrossProduct",2,js_Vector3CrossProduct),
		JS_CFUNC_DEF("Vector3Perpendicular",1,js_Vector3Perpendicular),
		JS_CFUNC_DEF("Vector3Length",1,js_Vector3Length),
		JS_CFUNC_DEF("Vector3LengthSqr",1,js_Vector3LengthSqr),
		JS_CFUNC_DEF("Vector3DotProduct",2,js_Vector3DotProduct),
		JS_CFUNC_DEF("Vector3Distance",2,js_Vector3Distance),
		JS_CFUNC_DEF("Vector3DistanceSqr",2,js_Vector3DistanceSqr),
		JS_CFUNC_DEF("Vector3Angle",2,js_Vector3Angle),
		JS_CFUNC_DEF("Vector3Negate",1,js_Vector3Negate),
		JS_CFUNC_DEF("Vector3Divide",2,js_Vector3Divide),
		JS_CFUNC_DEF("Vector3Normalize",1,js_Vector3Normalize),
		JS_CFUNC_DEF("Vector3Project",2,js_Vector3Project),
		JS_CFUNC_DEF("Vector3Reject",2,js_Vector3Reject),
		JS_CFUNC_DEF("Vector3OrthoNormalize",2,js_Vector3OrthoNormalize),
		JS_CFUNC_DEF("Vector3Transform",2,js_Vector3Transform),
		JS_CFUNC_DEF("Vector3RotateByQuaternion",2,js_Vector3RotateByQuaternion),
		JS_CFUNC_DEF("Vector3RotateByAxisAngle",3,js_Vector3RotateByAxisAngle),
		JS_CFUNC_DEF("Vector3MoveTowards",3,js_Vector3MoveTowards),
		JS_CFUNC_DEF("Vector3Lerp",3,js_Vector3Lerp),
		JS_CFUNC_DEF("Vector3CubicHermite",5,js_Vector3CubicHermite),
		JS_CFUNC_DEF("Vector3Reflect",2,js_Vector3Reflect),
		JS_CFUNC_DEF("Vector3Min",2,js_Vector3Min),
		JS_CFUNC_DEF("Vector3Max",2,js_Vector3Max),
		JS_CFUNC_DEF("Vector3Barycenter",4,js_Vector3Barycenter),
		JS_CFUNC_DEF("Vector3Unproject",3,js_Vector3Unproject),
		JS_CFUNC_DEF("Vector3ToFloatV",1,js_Vector3ToFloatV),
		JS_CFUNC_DEF("Vector3Invert",1,js_Vector3Invert),
		JS_CFUNC_DEF("Vector3Clamp",3,js_Vector3Clamp),
		JS_CFUNC_DEF("Vector3ClampValue",3,js_Vector3ClampValue),
		JS_CFUNC_DEF("Vector3Equals",2,js_Vector3Equals),
		JS_CFUNC_DEF("Vector3Refract",3,js_Vector3Refract),
		JS_CFUNC_DEF("Vector4Zero",0,js_Vector4Zero),
		JS_CFUNC_DEF("Vector4One",0,js_Vector4One),
		JS_CFUNC_DEF("Vector4Add",2,js_Vector4Add),
		JS_CFUNC_DEF("Vector4AddValue",2,js_Vector4AddValue),
		JS_CFUNC_DEF("Vector4Subtract",2,js_Vector4Subtract),
		JS_CFUNC_DEF("Vector4SubtractValue",2,js_Vector4SubtractValue),
		JS_CFUNC_DEF("Vector4Length",1,js_Vector4Length),
		JS_CFUNC_DEF("Vector4LengthSqr",1,js_Vector4LengthSqr),
		JS_CFUNC_DEF("Vector4DotProduct",2,js_Vector4DotProduct),
		JS_CFUNC_DEF("Vector4Distance",2,js_Vector4Distance),
		JS_CFUNC_DEF("Vector4DistanceSqr",2,js_Vector4DistanceSqr),
		JS_CFUNC_DEF("Vector4Scale",2,js_Vector4Scale),
		JS_CFUNC_DEF("Vector4Multiply",2,js_Vector4Multiply),
		JS_CFUNC_DEF("Vector4Negate",1,js_Vector4Negate),
		JS_CFUNC_DEF("Vector4Divide",2,js_Vector4Divide),
		JS_CFUNC_DEF("Vector4Normalize",1,js_Vector4Normalize),
		JS_CFUNC_DEF("Vector4Min",2,js_Vector4Min),
		JS_CFUNC_DEF("Vector4Max",2,js_Vector4Max),
		JS_CFUNC_DEF("Vector4Lerp",3,js_Vector4Lerp),
		JS_CFUNC_DEF("Vector4MoveTowards",3,js_Vector4MoveTowards),
		JS_CFUNC_DEF("Vector4Invert",1,js_Vector4Invert),
		JS_CFUNC_DEF("Vector4Equals",2,js_Vector4Equals),
		JS_CFUNC_DEF("MatrixDeterminant",1,js_MatrixDeterminant),
		JS_CFUNC_DEF("MatrixTrace",1,js_MatrixTrace),
		JS_CFUNC_DEF("MatrixTranspose",1,js_MatrixTranspose),
		JS_CFUNC_DEF("MatrixInvert",1,js_MatrixInvert),
		JS_CFUNC_DEF("MatrixIdentity",0,js_MatrixIdentity),
		JS_CFUNC_DEF("MatrixAdd",2,js_MatrixAdd),
		JS_CFUNC_DEF("MatrixSubtract",2,js_MatrixSubtract),
		JS_CFUNC_DEF("MatrixMultiply",2,js_MatrixMultiply),
		JS_CFUNC_DEF("MatrixTranslate",3,js_MatrixTranslate),
		JS_CFUNC_DEF("MatrixRotate",2,js_MatrixRotate),
		JS_CFUNC_DEF("MatrixRotateX",1,js_MatrixRotateX),
		JS_CFUNC_DEF("MatrixRotateY",1,js_MatrixRotateY),
		JS_CFUNC_DEF("MatrixRotateZ",1,js_MatrixRotateZ),
		JS_CFUNC_DEF("MatrixRotateXYZ",1,js_MatrixRotateXYZ),
		JS_CFUNC_DEF("MatrixRotateZYX",1,js_MatrixRotateZYX),
		JS_CFUNC_DEF("MatrixScale",3,js_MatrixScale),
		JS_CFUNC_DEF("MatrixFrustum",6,js_MatrixFrustum),
		JS_CFUNC_DEF("MatrixPerspective",4,js_MatrixPerspective),
		JS_CFUNC_DEF("MatrixOrtho",6,js_MatrixOrtho),
		JS_CFUNC_DEF("MatrixLookAt",3,js_MatrixLookAt),
		JS_CFUNC_DEF("MatrixToFloatV",1,js_MatrixToFloatV),
		JS_CFUNC_DEF("QuaternionAdd",2,js_QuaternionAdd),
		JS_CFUNC_DEF("QuaternionAddValue",2,js_QuaternionAddValue),
		JS_CFUNC_DEF("QuaternionSubtract",2,js_QuaternionSubtract),
		JS_CFUNC_DEF("QuaternionSubtractValue",2,js_QuaternionSubtractValue),
		JS_CFUNC_DEF("QuaternionIdentity",0,js_QuaternionIdentity),
		JS_CFUNC_DEF("QuaternionLength",1,js_QuaternionLength),
		JS_CFUNC_DEF("QuaternionNormalize",1,js_QuaternionNormalize),
		JS_CFUNC_DEF("QuaternionInvert",1,js_QuaternionInvert),
		JS_CFUNC_DEF("QuaternionMultiply",2,js_QuaternionMultiply),
		JS_CFUNC_DEF("QuaternionScale",2,js_QuaternionScale),
		JS_CFUNC_DEF("QuaternionDivide",2,js_QuaternionDivide),
		JS_CFUNC_DEF("QuaternionLerp",3,js_QuaternionLerp),
		JS_CFUNC_DEF("QuaternionNlerp",3,js_QuaternionNlerp),
		JS_CFUNC_DEF("QuaternionSlerp",3,js_QuaternionSlerp),
		JS_CFUNC_DEF("QuaternionCubicHermiteSpline",5,js_QuaternionCubicHermiteSpline),
		JS_CFUNC_DEF("QuaternionFromVector3ToVector3",2,js_QuaternionFromVector3ToVector3),
		JS_CFUNC_DEF("QuaternionFromMatrix",1,js_QuaternionFromMatrix),
		JS_CFUNC_DEF("QuaternionToMatrix",1,js_QuaternionToMatrix),
		JS_CFUNC_DEF("QuaternionFromAxisAngle",2,js_QuaternionFromAxisAngle),
		JS_CFUNC_DEF("QuaternionToAxisAngle",3,js_QuaternionToAxisAngle),
		JS_CFUNC_DEF("QuaternionFromEuler",3,js_QuaternionFromEuler),
		JS_CFUNC_DEF("QuaternionToEuler",1,js_QuaternionToEuler),
		JS_CFUNC_DEF("QuaternionTransform",2,js_QuaternionTransform),
		JS_CFUNC_DEF("QuaternionEquals",2,js_QuaternionEquals),
		JS_CFUNC_DEF("MatrixDecompose",4,js_MatrixDecompose)
	};
	
	static int js_raymath_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsraymath_funcs);
		JS_SetModuleExportList(ctx,m,jsraymath_funcs,(int)listcount);
		js_declare_float3(ctx,m);
		JSValue float3_constr=JS_NewCFunction2(ctx,js_float3_constructor,(const char *)"float3",(int)1,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char *)"float3",float3_constr);
		js_declare_float16(ctx,m);
		JSValue float16_constr=JS_NewCFunction2(ctx,js_float16_constructor,(const char *)"float16",(int)1,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char *)"float16",float16_constr);
		JS_SetModuleExport(ctx,m,(const char *)"EPSILON",JS_NewFloat64(ctx,(double)EPSILON));
		return 0;
	}
	
	JSModuleDef * js_init_module_raymath(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_raymath_init);
		if(!m)return NULL;
		size_t listcount=countof(jsraymath_funcs);
		JS_AddModuleExportList(ctx,m,jsraymath_funcs,(int)listcount);
		JS_AddModuleExport(ctx,m,(const char *)"float3");
		JS_AddModuleExport(ctx,m,(const char *)"float16");
		JS_AddModuleExport(ctx,m,(const char *)"EPSILON");
		return m;
	}

#endif //JS_raymath_GUARD