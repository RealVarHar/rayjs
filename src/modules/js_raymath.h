#ifndef JS_raymath_GUARD
	#define JS_raymath_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <rayjs_generated.h>
	#include <raylib.h>
	#include <raymath.h>
	
	static void js_float3_finalizer(JSRuntime * rt,JSValue val){
		float3 * ptr=(float3 *)JS_GetOpaque(val,js_float3_class_id);
		if(ptr){
			js_free_rt(rt,(void *)ptr);
		}
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
			double double_ret;
			int err_ret=JS_ToFloat64(ctx,&double_ret,set_to);
			if(err_ret<0){
				JS_ThrowTypeError(ctx,(const char *)"set_to is not numeric");
				return -1;
			}
			float ret=((float)double_ret);
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
		float3 * ptr=(float3 *)JS_GetOpaque2(ctx,this_val,js_float3_class_id);
		float * value;
		bool freesrc_value=(bool)false;
		JSValue da_value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(v);
		JSValue src=v;
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			src =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}
		if(JS_IsArray(src)==1){
			value =(float *)jsc_malloc(ctx,3*sizeof(float));
			int i;
			for(i=0;i<3;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				double double_valuei;
				int err_valuei=JS_ToFloat64(ctx,&double_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((float)double_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else if(JS_IsArrayBuffer(src)==1){
			float * js_value=(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,src);
			value =(float *)jsc_malloc(ctx,size_value*sizeof(float *));
			memcpy((void *)value,(const void *)js_value,(size_t)size_value);
		}else{
			JSClassID classid_value=JS_GetClassID(src);
			if(classid_value==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_value;
				da_value =JS_GetTypedArrayBuffer(ctx,src,&offset_value,(size_t *)&size_value,NULL);
				float * js_value=(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,da_value);
				js_value +=offset_value;
				size_value -=offset_value;
				value =(float *)jsc_malloc(ctx,size_value*sizeof(float *));
				memcpy((void *)value,(const void *)js_value,(size_t)size_value);
				JS_FreeValuePtr(ctx,&da_value);
			}else{
				if(freesrc_value){
					JS_FreeValue(ctx,src);
				}
				JS_ThrowTypeError(ctx,(const char *)"v does not match type float *");
				return JS_EXCEPTION;
			}
		}
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
		if(ptr){
			js_free_rt(rt,(void *)ptr);
		}
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
			double double_ret;
			int err_ret=JS_ToFloat64(ctx,&double_ret,set_to);
			if(err_ret<0){
				JS_ThrowTypeError(ctx,(const char *)"set_to is not numeric");
				return -1;
			}
			float ret=((float)double_ret);
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
		float16 * ptr=(float16 *)JS_GetOpaque2(ctx,this_val,js_float16_class_id);
		float * value;
		bool freesrc_value=(bool)false;
		JSValue da_value;
		int64_t size_value;
		JSClassID value_class=JS_GetClassID(v);
		JSValue src=v;
		if(value_class==js_ArrayProxy_class_id){
			void * opaque_value=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_value=((ArrayProxy_class *)opaque_value)[0];
			src =AP_value.values(ctx,AP_value.opaque,(int)0,(bool)false);
			freesrc_value =(bool)true;
		}
		if(JS_IsArray(src)==1){
			value =(float *)jsc_malloc(ctx,16*sizeof(float));
			int i;
			for(i=0;i<16;i++){
				JSValue js_value=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				double double_valuei;
				int err_valuei=JS_ToFloat64(ctx,&double_valuei,js_value);
				if(err_valuei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_value is not numeric");
					return JS_EXCEPTION;
				}
				value[i] =((float)double_valuei);
				JS_FreeValue(ctx,js_value);
			}
		}else if(JS_IsArrayBuffer(src)==1){
			float * js_value=(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,src);
			value =(float *)jsc_malloc(ctx,size_value*sizeof(float *));
			memcpy((void *)value,(const void *)js_value,(size_t)size_value);
		}else{
			JSClassID classid_value=JS_GetClassID(src);
			if(classid_value==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_value;
				da_value =JS_GetTypedArrayBuffer(ctx,src,&offset_value,(size_t *)&size_value,NULL);
				float * js_value=(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_value,da_value);
				js_value +=offset_value;
				size_value -=offset_value;
				value =(float *)jsc_malloc(ctx,size_value*sizeof(float *));
				memcpy((void *)value,(const void *)js_value,(size_t)size_value);
				JS_FreeValuePtr(ctx,&da_value);
			}else{
				if(freesrc_value){
					JS_FreeValue(ctx,src);
				}
				JS_ThrowTypeError(ctx,(const char *)"v does not match type float *");
				return JS_EXCEPTION;
			}
		}
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
		float * v;
		bool freesrc_v=(bool)false;
		JSValue da_v;
		int64_t size_v;
		JSClassID v_class=JS_GetClassID(argv[0]);
		JSValue src=argv[0];
		if(v_class==js_ArrayProxy_class_id){
			void * opaque_v=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_v=((ArrayProxy_class *)opaque_v)[0];
			src =AP_v.values(ctx,AP_v.opaque,(int)0,(bool)false);
			freesrc_v =(bool)true;
		}
		if(JS_IsArray(src)==1){
			v =(float *)js_malloc(ctx,3*sizeof(float));
			int i;
			for(i=0;i<3;i++){
				JSValue js_v=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				double double_vi;
				int err_vi=JS_ToFloat64(ctx,&double_vi,js_v);
				if(err_vi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_v is not numeric");
					return JS_EXCEPTION;
				}
				v[i] =((float)double_vi);
				JS_FreeValue(ctx,js_v);
			}
		}else if(JS_IsArrayBuffer(src)==1){
			v =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_v,src);
		}else{
			JSClassID classid_v=JS_GetClassID(src);
			if(classid_v==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_v;
				da_v =JS_GetTypedArrayBuffer(ctx,src,&offset_v,(size_t *)&size_v,NULL);
				v =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_v,da_v);
				v +=offset_v;
				size_v -=offset_v;
			}else{
				if(freesrc_v){
					JS_FreeValue(ctx,src);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type float *");
				return JS_EXCEPTION;
			}
		}
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
		float * v;
		bool freesrc_v=(bool)false;
		JSValue da_v;
		int64_t size_v;
		JSClassID v_class=JS_GetClassID(argv[0]);
		JSValue src=argv[0];
		if(v_class==js_ArrayProxy_class_id){
			void * opaque_v=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_v=((ArrayProxy_class *)opaque_v)[0];
			src =AP_v.values(ctx,AP_v.opaque,(int)0,(bool)false);
			freesrc_v =(bool)true;
		}
		if(JS_IsArray(src)==1){
			v =(float *)js_malloc(ctx,16*sizeof(float));
			int i;
			for(i=0;i<16;i++){
				JSValue js_v=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				double double_vi;
				int err_vi=JS_ToFloat64(ctx,&double_vi,js_v);
				if(err_vi<0){
					JS_ThrowTypeError(ctx,(const char *)"js_v is not numeric");
					return JS_EXCEPTION;
				}
				v[i] =((float)double_vi);
				JS_FreeValue(ctx,js_v);
			}
		}else if(JS_IsArrayBuffer(src)==1){
			v =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_v,src);
		}else{
			JSClassID classid_v=JS_GetClassID(src);
			if(classid_v==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_v;
				da_v =JS_GetTypedArrayBuffer(ctx,src,&offset_v,(size_t *)&size_v,NULL);
				v =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_v,da_v);
				v +=offset_v;
				size_v -=offset_v;
			}else{
				if(freesrc_v){
					JS_FreeValue(ctx,src);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type float *");
				return JS_EXCEPTION;
			}
		}
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
		double double_value;
		int err_value=JS_ToFloat64(ctx,&double_value,argv[0]);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float value=((float)double_value);
		double double_min;
		int err_min=JS_ToFloat64(ctx,&double_min,argv[1]);
		if(err_min<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float min=((float)double_min);
		double double_max;
		int err_max=JS_ToFloat64(ctx,&double_max,argv[2]);
		if(err_max<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float max=((float)double_max);
		float returnVal=Clamp(value,min,max);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Lerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_start;
		int err_start=JS_ToFloat64(ctx,&double_start,argv[0]);
		if(err_start<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float start=((float)double_start);
		double double_end;
		int err_end=JS_ToFloat64(ctx,&double_end,argv[1]);
		if(err_end<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float end=((float)double_end);
		double double_amount;
		int err_amount=JS_ToFloat64(ctx,&double_amount,argv[2]);
		if(err_amount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float amount=((float)double_amount);
		float returnVal=Lerp(start,end,amount);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Normalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_value;
		int err_value=JS_ToFloat64(ctx,&double_value,argv[0]);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float value=((float)double_value);
		double double_start;
		int err_start=JS_ToFloat64(ctx,&double_start,argv[1]);
		if(err_start<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float start=((float)double_start);
		double double_end;
		int err_end=JS_ToFloat64(ctx,&double_end,argv[2]);
		if(err_end<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float end=((float)double_end);
		float returnVal=Normalize(value,start,end);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Remap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_value;
		int err_value=JS_ToFloat64(ctx,&double_value,argv[0]);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float value=((float)double_value);
		double double_inputStart;
		int err_inputStart=JS_ToFloat64(ctx,&double_inputStart,argv[1]);
		if(err_inputStart<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float inputStart=((float)double_inputStart);
		double double_inputEnd;
		int err_inputEnd=JS_ToFloat64(ctx,&double_inputEnd,argv[2]);
		if(err_inputEnd<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float inputEnd=((float)double_inputEnd);
		double double_outputStart;
		int err_outputStart=JS_ToFloat64(ctx,&double_outputStart,argv[3]);
		if(err_outputStart<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		float outputStart=((float)double_outputStart);
		double double_outputEnd;
		int err_outputEnd=JS_ToFloat64(ctx,&double_outputEnd,argv[4]);
		if(err_outputEnd<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		float outputEnd=((float)double_outputEnd);
		float returnVal=Remap(value,inputStart,inputEnd,outputStart,outputEnd);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Wrap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_value;
		int err_value=JS_ToFloat64(ctx,&double_value,argv[0]);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float value=((float)double_value);
		double double_min;
		int err_min=JS_ToFloat64(ctx,&double_min,argv[1]);
		if(err_min<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float min=((float)double_min);
		double double_max;
		int err_max=JS_ToFloat64(ctx,&double_max,argv[2]);
		if(err_max<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float max=((float)double_max);
		float returnVal=Wrap(value,min,max);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_FloatEquals(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
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
		int returnVal=FloatEquals(x,y);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2Zero(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 returnVal=Vector2Zero();
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2One(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 returnVal=Vector2One();
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Add(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		Vector2 returnVal=Vector2Add(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2AddValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		double double_add;
		int err_add=JS_ToFloat64(ctx,&double_add,argv[1]);
		if(err_add<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float add=((float)double_add);
		Vector2 returnVal=Vector2AddValue(v,add);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Subtract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		Vector2 returnVal=Vector2Subtract(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2SubtractValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		double double_sub;
		int err_sub=JS_ToFloat64(ctx,&double_sub,argv[1]);
		if(err_sub<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float sub=((float)double_sub);
		Vector2 returnVal=Vector2SubtractValue(v,sub);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Length(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		float returnVal=Vector2Length(v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2LengthSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		float returnVal=Vector2LengthSqr(v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2DotProduct(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		float returnVal=Vector2DotProduct(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2CrossProduct(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		float returnVal=Vector2CrossProduct(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2Distance(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		float returnVal=Vector2Distance(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2DistanceSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		float returnVal=Vector2DistanceSqr(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2Angle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		float returnVal=Vector2Angle(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2LineAngle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_start=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_start==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 start=*ptr_start;
		Vector2 * ptr_end=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_end==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 end=*ptr_end;
		float returnVal=Vector2LineAngle(start,end);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2Scale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		double double_scale;
		int err_scale=JS_ToFloat64(ctx,&double_scale,argv[1]);
		if(err_scale<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float scale=((float)double_scale);
		Vector2 returnVal=Vector2Scale(v,scale);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Multiply(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		Vector2 returnVal=Vector2Multiply(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Negate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		Vector2 returnVal=Vector2Negate(v);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Divide(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		Vector2 returnVal=Vector2Divide(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Normalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		Vector2 returnVal=Vector2Normalize(v);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Transform(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		Matrix * ptr_mat=(Matrix *)JS_GetOpaque(argv[1],js_Matrix_class_id);
		if(ptr_mat==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix mat=*ptr_mat;
		Vector2 returnVal=Vector2Transform(v,mat);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Lerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		double double_amount;
		int err_amount=JS_ToFloat64(ctx,&double_amount,argv[2]);
		if(err_amount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float amount=((float)double_amount);
		Vector2 returnVal=Vector2Lerp(v1,v2,amount);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Reflect(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		Vector2 * ptr_normal=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_normal==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 normal=*ptr_normal;
		Vector2 returnVal=Vector2Reflect(v,normal);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Min(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		Vector2 returnVal=Vector2Min(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Max(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v1=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v1=*ptr_v1;
		Vector2 * ptr_v2=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v2=*ptr_v2;
		Vector2 returnVal=Vector2Max(v1,v2);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Rotate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		double double_angle;
		int err_angle=JS_ToFloat64(ctx,&double_angle,argv[1]);
		if(err_angle<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float angle=((float)double_angle);
		Vector2 returnVal=Vector2Rotate(v,angle);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2MoveTowards(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		Vector2 * ptr_target=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_target==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 target=*ptr_target;
		double double_maxDistance;
		int err_maxDistance=JS_ToFloat64(ctx,&double_maxDistance,argv[2]);
		if(err_maxDistance<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float maxDistance=((float)double_maxDistance);
		Vector2 returnVal=Vector2MoveTowards(v,target,maxDistance);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Invert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		Vector2 returnVal=Vector2Invert(v);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Clamp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		Vector2 * ptr_min=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_min==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 min=*ptr_min;
		Vector2 * ptr_max=(Vector2 *)JS_GetOpaque(argv[2],js_Vector2_class_id);
		if(ptr_max==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 max=*ptr_max;
		Vector2 returnVal=Vector2Clamp(v,min,max);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2ClampValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		double double_min;
		int err_min=JS_ToFloat64(ctx,&double_min,argv[1]);
		if(err_min<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float min=((float)double_min);
		double double_max;
		int err_max=JS_ToFloat64(ctx,&double_max,argv[2]);
		if(err_max<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float max=((float)double_max);
		Vector2 returnVal=Vector2ClampValue(v,min,max);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector2Equals(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_p=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_p==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 p=*ptr_p;
		Vector2 * ptr_q=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 q=*ptr_q;
		int returnVal=Vector2Equals(p,q);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_Vector2Refract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector2 * ptr_v=(Vector2 *)JS_GetOpaque(argv[0],js_Vector2_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 v=*ptr_v;
		Vector2 * ptr_n=(Vector2 *)JS_GetOpaque(argv[1],js_Vector2_class_id);
		if(ptr_n==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector2 n=*ptr_n;
		double double_r;
		int err_r=JS_ToFloat64(ctx,&double_r,argv[2]);
		if(err_r<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float r=((float)double_r);
		Vector2 returnVal=Vector2Refract(v,n,r);
		Vector2 * ptr_ret=(Vector2 *)js_malloc(ctx,sizeof(Vector2));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector2_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Zero(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 returnVal=Vector3Zero();
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3One(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 returnVal=Vector3One();
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Add(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		Vector3 returnVal=Vector3Add(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3AddValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		double double_add;
		int err_add=JS_ToFloat64(ctx,&double_add,argv[1]);
		if(err_add<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float add=((float)double_add);
		Vector3 returnVal=Vector3AddValue(v,add);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Subtract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		Vector3 returnVal=Vector3Subtract(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3SubtractValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		double double_sub;
		int err_sub=JS_ToFloat64(ctx,&double_sub,argv[1]);
		if(err_sub<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float sub=((float)double_sub);
		Vector3 returnVal=Vector3SubtractValue(v,sub);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Scale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		double double_scalar;
		int err_scalar=JS_ToFloat64(ctx,&double_scalar,argv[1]);
		if(err_scalar<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float scalar=((float)double_scalar);
		Vector3 returnVal=Vector3Scale(v,scalar);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Multiply(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		Vector3 returnVal=Vector3Multiply(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3CrossProduct(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		Vector3 returnVal=Vector3CrossProduct(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Perpendicular(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		Vector3 returnVal=Vector3Perpendicular(v);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Length(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		float returnVal=Vector3Length((const Vector3)v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3LengthSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		float returnVal=Vector3LengthSqr((const Vector3)v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3DotProduct(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		float returnVal=Vector3DotProduct(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3Distance(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		float returnVal=Vector3Distance(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3DistanceSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		float returnVal=Vector3DistanceSqr(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3Angle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		float returnVal=Vector3Angle(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3Negate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		Vector3 returnVal=Vector3Negate(v);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Divide(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		Vector3 returnVal=Vector3Divide(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Normalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		Vector3 returnVal=Vector3Normalize(v);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Project(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		Vector3 returnVal=Vector3Project(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Reject(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		Vector3 returnVal=Vector3Reject(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3OrthoNormalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Vector3");
			return JS_EXCEPTION;
		}
		Vector3 * v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type Vector3");
			return JS_EXCEPTION;
		}
		Vector3OrthoNormalize(v1,v2);
		JS_SetOpaque(argv[0],(void *)v1);
		JS_SetOpaque(argv[1],(void *)v2);
		return JS_UNDEFINED;
	}
	
	static JSValue js_Vector3Transform(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		Matrix * ptr_mat=(Matrix *)JS_GetOpaque(argv[1],js_Matrix_class_id);
		if(ptr_mat==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix mat=*ptr_mat;
		Vector3 returnVal=Vector3Transform(v,mat);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3RotateByQuaternion(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		Vector3 returnVal=Vector3RotateByQuaternion(v,q);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3RotateByAxisAngle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		Vector3 * ptr_axis=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_axis==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 axis=*ptr_axis;
		double double_angle;
		int err_angle=JS_ToFloat64(ctx,&double_angle,argv[2]);
		if(err_angle<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float angle=((float)double_angle);
		Vector3 returnVal=Vector3RotateByAxisAngle(v,axis,angle);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3MoveTowards(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		Vector3 * ptr_target=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_target==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 target=*ptr_target;
		double double_maxDistance;
		int err_maxDistance=JS_ToFloat64(ctx,&double_maxDistance,argv[2]);
		if(err_maxDistance<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float maxDistance=((float)double_maxDistance);
		Vector3 returnVal=Vector3MoveTowards(v,target,maxDistance);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Lerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		double double_amount;
		int err_amount=JS_ToFloat64(ctx,&double_amount,argv[2]);
		if(err_amount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float amount=((float)double_amount);
		Vector3 returnVal=Vector3Lerp(v1,v2,amount);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3CubicHermite(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_tangent1=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_tangent1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 tangent1=*ptr_tangent1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[2],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		Vector3 * ptr_tangent2=(Vector3 *)JS_GetOpaque(argv[3],js_Vector3_class_id);
		if(ptr_tangent2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 tangent2=*ptr_tangent2;
		double double_amount;
		int err_amount=JS_ToFloat64(ctx,&double_amount,argv[4]);
		if(err_amount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		float amount=((float)double_amount);
		Vector3 returnVal=Vector3CubicHermite(v1,tangent1,v2,tangent2,amount);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Reflect(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		Vector3 * ptr_normal=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_normal==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 normal=*ptr_normal;
		Vector3 returnVal=Vector3Reflect(v,normal);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Min(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		Vector3 returnVal=Vector3Min(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Max(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v1=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v1=*ptr_v1;
		Vector3 * ptr_v2=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v2=*ptr_v2;
		Vector3 returnVal=Vector3Max(v1,v2);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Barycenter(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_p=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_p==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 p=*ptr_p;
		Vector3 * ptr_a=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_a==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 a=*ptr_a;
		Vector3 * ptr_b=(Vector3 *)JS_GetOpaque(argv[2],js_Vector3_class_id);
		if(ptr_b==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 b=*ptr_b;
		Vector3 * ptr_c=(Vector3 *)JS_GetOpaque(argv[3],js_Vector3_class_id);
		if(ptr_c==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 c=*ptr_c;
		Vector3 returnVal=Vector3Barycenter(p,a,b,c);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Unproject(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_source=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_source==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 source=*ptr_source;
		Matrix * ptr_projection=(Matrix *)JS_GetOpaque(argv[1],js_Matrix_class_id);
		if(ptr_projection==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix projection=*ptr_projection;
		Matrix * ptr_view=(Matrix *)JS_GetOpaque(argv[2],js_Matrix_class_id);
		if(ptr_view==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix view=*ptr_view;
		Vector3 returnVal=Vector3Unproject(source,projection,view);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3ToFloatV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		float3 returnVal=Vector3ToFloatV(v);
		float3 * ptr_ret=(float3 *)js_malloc(ctx,sizeof(float3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_float3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Invert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		Vector3 returnVal=Vector3Invert(v);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Clamp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		Vector3 * ptr_min=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_min==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 min=*ptr_min;
		Vector3 * ptr_max=(Vector3 *)JS_GetOpaque(argv[2],js_Vector3_class_id);
		if(ptr_max==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 max=*ptr_max;
		Vector3 returnVal=Vector3Clamp(v,min,max);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3ClampValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		double double_min;
		int err_min=JS_ToFloat64(ctx,&double_min,argv[1]);
		if(err_min<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float min=((float)double_min);
		double double_max;
		int err_max=JS_ToFloat64(ctx,&double_max,argv[2]);
		if(err_max<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float max=((float)double_max);
		Vector3 returnVal=Vector3ClampValue(v,min,max);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector3Equals(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_p=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_p==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 p=*ptr_p;
		Vector3 * ptr_q=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 q=*ptr_q;
		int returnVal=Vector3Equals(p,q);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_Vector3Refract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_v=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 v=*ptr_v;
		Vector3 * ptr_n=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_n==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 n=*ptr_n;
		double double_r;
		int err_r=JS_ToFloat64(ctx,&double_r,argv[2]);
		if(err_r<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float r=((float)double_r);
		Vector3 returnVal=Vector3Refract(v,n,r);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Zero(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 returnVal=Vector4Zero();
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4One(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 returnVal=Vector4One();
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Add(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v1=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v1=*ptr_v1;
		Vector4 * ptr_v2=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v2=*ptr_v2;
		Vector4 returnVal=Vector4Add(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4AddValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v=*ptr_v;
		double double_add;
		int err_add=JS_ToFloat64(ctx,&double_add,argv[1]);
		if(err_add<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float add=((float)double_add);
		Vector4 returnVal=Vector4AddValue(v,add);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Subtract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v1=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v1=*ptr_v1;
		Vector4 * ptr_v2=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v2=*ptr_v2;
		Vector4 returnVal=Vector4Subtract(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4SubtractValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v=*ptr_v;
		double double_add;
		int err_add=JS_ToFloat64(ctx,&double_add,argv[1]);
		if(err_add<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float add=((float)double_add);
		Vector4 returnVal=Vector4SubtractValue(v,add);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Length(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v=*ptr_v;
		float returnVal=Vector4Length(v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector4LengthSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v=*ptr_v;
		float returnVal=Vector4LengthSqr(v);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector4DotProduct(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v1=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v1=*ptr_v1;
		Vector4 * ptr_v2=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v2=*ptr_v2;
		float returnVal=Vector4DotProduct(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector4Distance(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v1=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v1=*ptr_v1;
		Vector4 * ptr_v2=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v2=*ptr_v2;
		float returnVal=Vector4Distance(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector4DistanceSqr(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v1=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v1=*ptr_v1;
		Vector4 * ptr_v2=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v2=*ptr_v2;
		float returnVal=Vector4DistanceSqr(v1,v2);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_Vector4Scale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v=*ptr_v;
		double double_scale;
		int err_scale=JS_ToFloat64(ctx,&double_scale,argv[1]);
		if(err_scale<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float scale=((float)double_scale);
		Vector4 returnVal=Vector4Scale(v,scale);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Multiply(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v1=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v1=*ptr_v1;
		Vector4 * ptr_v2=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v2=*ptr_v2;
		Vector4 returnVal=Vector4Multiply(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Negate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v=*ptr_v;
		Vector4 returnVal=Vector4Negate(v);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Divide(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v1=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v1=*ptr_v1;
		Vector4 * ptr_v2=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v2=*ptr_v2;
		Vector4 returnVal=Vector4Divide(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Normalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v=*ptr_v;
		Vector4 returnVal=Vector4Normalize(v);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Min(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v1=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v1=*ptr_v1;
		Vector4 * ptr_v2=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v2=*ptr_v2;
		Vector4 returnVal=Vector4Min(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Max(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v1=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v1=*ptr_v1;
		Vector4 * ptr_v2=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v2=*ptr_v2;
		Vector4 returnVal=Vector4Max(v1,v2);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Lerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v1=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v1=*ptr_v1;
		Vector4 * ptr_v2=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_v2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v2=*ptr_v2;
		double double_amount;
		int err_amount=JS_ToFloat64(ctx,&double_amount,argv[2]);
		if(err_amount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float amount=((float)double_amount);
		Vector4 returnVal=Vector4Lerp(v1,v2,amount);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4MoveTowards(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v=*ptr_v;
		Vector4 * ptr_target=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_target==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 target=*ptr_target;
		double double_maxDistance;
		int err_maxDistance=JS_ToFloat64(ctx,&double_maxDistance,argv[2]);
		if(err_maxDistance<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float maxDistance=((float)double_maxDistance);
		Vector4 returnVal=Vector4MoveTowards(v,target,maxDistance);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Invert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_v=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_v==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 v=*ptr_v;
		Vector4 returnVal=Vector4Invert(v);
		Vector4 * ptr_ret=(Vector4 *)js_malloc(ctx,sizeof(Vector4));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_Vector4Equals(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector4 * ptr_p=(Vector4 *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_p==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 p=*ptr_p;
		Vector4 * ptr_q=(Vector4 *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector4 q=*ptr_q;
		int returnVal=Vector4Equals(p,q);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_MatrixDeterminant(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_mat=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_mat==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix mat=*ptr_mat;
		float returnVal=MatrixDeterminant(mat);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_MatrixTrace(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_mat=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_mat==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix mat=*ptr_mat;
		float returnVal=MatrixTrace(mat);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_MatrixTranspose(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_mat=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_mat==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix mat=*ptr_mat;
		Matrix returnVal=MatrixTranspose(mat);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixInvert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_mat=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_mat==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix mat=*ptr_mat;
		Matrix returnVal=MatrixInvert(mat);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixIdentity(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix returnVal=MatrixIdentity();
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixAdd(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_left=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_left==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix left=*ptr_left;
		Matrix * ptr_right=(Matrix *)JS_GetOpaque(argv[1],js_Matrix_class_id);
		if(ptr_right==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix right=*ptr_right;
		Matrix returnVal=MatrixAdd(left,right);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixSubtract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_left=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_left==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix left=*ptr_left;
		Matrix * ptr_right=(Matrix *)JS_GetOpaque(argv[1],js_Matrix_class_id);
		if(ptr_right==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix right=*ptr_right;
		Matrix returnVal=MatrixSubtract(left,right);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixMultiply(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_left=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_left==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix left=*ptr_left;
		Matrix * ptr_right=(Matrix *)JS_GetOpaque(argv[1],js_Matrix_class_id);
		if(ptr_right==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix right=*ptr_right;
		Matrix returnVal=MatrixMultiply(left,right);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixTranslate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
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
		Matrix returnVal=MatrixTranslate(x,y,z);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotate(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_axis=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_axis==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 axis=*ptr_axis;
		double double_angle;
		int err_angle=JS_ToFloat64(ctx,&double_angle,argv[1]);
		if(err_angle<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float angle=((float)double_angle);
		Matrix returnVal=MatrixRotate(axis,angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotateX(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_angle;
		int err_angle=JS_ToFloat64(ctx,&double_angle,argv[0]);
		if(err_angle<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float angle=((float)double_angle);
		Matrix returnVal=MatrixRotateX(angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotateY(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_angle;
		int err_angle=JS_ToFloat64(ctx,&double_angle,argv[0]);
		if(err_angle<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float angle=((float)double_angle);
		Matrix returnVal=MatrixRotateY(angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotateZ(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_angle;
		int err_angle=JS_ToFloat64(ctx,&double_angle,argv[0]);
		if(err_angle<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float angle=((float)double_angle);
		Matrix returnVal=MatrixRotateZ(angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotateXYZ(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_angle=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_angle==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 angle=*ptr_angle;
		Matrix returnVal=MatrixRotateXYZ(angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixRotateZYX(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_angle=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_angle==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 angle=*ptr_angle;
		Matrix returnVal=MatrixRotateZYX(angle);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixScale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
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
		Matrix returnVal=MatrixScale(x,y,z);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixFrustum(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
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
		double nearPlane;
		int err_nearPlane=JS_ToFloat64(ctx,&nearPlane,argv[4]);
		if(err_nearPlane<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		double farPlane;
		int err_farPlane=JS_ToFloat64(ctx,&farPlane,argv[5]);
		if(err_farPlane<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		Matrix returnVal=MatrixFrustum(left,right,bottom,top,nearPlane,farPlane);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixPerspective(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double fovY;
		int err_fovY=JS_ToFloat64(ctx,&fovY,argv[0]);
		if(err_fovY<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		double aspect;
		int err_aspect=JS_ToFloat64(ctx,&aspect,argv[1]);
		if(err_aspect<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		double nearPlane;
		int err_nearPlane=JS_ToFloat64(ctx,&nearPlane,argv[2]);
		if(err_nearPlane<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		double farPlane;
		int err_farPlane=JS_ToFloat64(ctx,&farPlane,argv[3]);
		if(err_farPlane<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		Matrix returnVal=MatrixPerspective(fovY,aspect,nearPlane,farPlane);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixOrtho(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
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
		double nearPlane;
		int err_nearPlane=JS_ToFloat64(ctx,&nearPlane,argv[4]);
		if(err_nearPlane<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		double farPlane;
		int err_farPlane=JS_ToFloat64(ctx,&farPlane,argv[5]);
		if(err_farPlane<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		Matrix returnVal=MatrixOrtho(left,right,bottom,top,nearPlane,farPlane);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixLookAt(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_eye=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_eye==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 eye=*ptr_eye;
		Vector3 * ptr_target=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_target==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 target=*ptr_target;
		Vector3 * ptr_up=(Vector3 *)JS_GetOpaque(argv[2],js_Vector3_class_id);
		if(ptr_up==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 up=*ptr_up;
		Matrix returnVal=MatrixLookAt(eye,target,up);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_MatrixToFloatV(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_mat=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_mat==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix mat=*ptr_mat;
		float16 returnVal=MatrixToFloatV(mat);
		float16 * ptr_ret=(float16 *)js_malloc(ctx,sizeof(float16));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_float16_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionAdd(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q1=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q1=*ptr_q1;
		Quaternion * ptr_q2=(Quaternion *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_q2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q2=*ptr_q2;
		Quaternion returnVal=QuaternionAdd(q1,q2);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionAddValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		double double_add;
		int err_add=JS_ToFloat64(ctx,&double_add,argv[1]);
		if(err_add<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float add=((float)double_add);
		Quaternion returnVal=QuaternionAddValue(q,add);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionSubtract(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q1=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q1=*ptr_q1;
		Quaternion * ptr_q2=(Quaternion *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_q2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q2=*ptr_q2;
		Quaternion returnVal=QuaternionSubtract(q1,q2);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionSubtractValue(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		double double_sub;
		int err_sub=JS_ToFloat64(ctx,&double_sub,argv[1]);
		if(err_sub<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float sub=((float)double_sub);
		Quaternion returnVal=QuaternionSubtractValue(q,sub);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionIdentity(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion returnVal=QuaternionIdentity();
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionLength(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		float returnVal=QuaternionLength(q);
		JSValue ret=JS_NewFloat64(ctx,((double)returnVal));
		return ret;
	}
	
	static JSValue js_QuaternionNormalize(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		Quaternion returnVal=QuaternionNormalize(q);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionInvert(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		Quaternion returnVal=QuaternionInvert(q);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionMultiply(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q1=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q1=*ptr_q1;
		Quaternion * ptr_q2=(Quaternion *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_q2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q2=*ptr_q2;
		Quaternion returnVal=QuaternionMultiply(q1,q2);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionScale(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		double double_mul;
		int err_mul=JS_ToFloat64(ctx,&double_mul,argv[1]);
		if(err_mul<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float mul=((float)double_mul);
		Quaternion returnVal=QuaternionScale(q,mul);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionDivide(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q1=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q1=*ptr_q1;
		Quaternion * ptr_q2=(Quaternion *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_q2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q2=*ptr_q2;
		Quaternion returnVal=QuaternionDivide(q1,q2);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionLerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q1=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q1=*ptr_q1;
		Quaternion * ptr_q2=(Quaternion *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_q2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q2=*ptr_q2;
		double double_amount;
		int err_amount=JS_ToFloat64(ctx,&double_amount,argv[2]);
		if(err_amount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float amount=((float)double_amount);
		Quaternion returnVal=QuaternionLerp(q1,q2,amount);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionNlerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q1=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q1=*ptr_q1;
		Quaternion * ptr_q2=(Quaternion *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_q2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q2=*ptr_q2;
		double double_amount;
		int err_amount=JS_ToFloat64(ctx,&double_amount,argv[2]);
		if(err_amount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float amount=((float)double_amount);
		Quaternion returnVal=QuaternionNlerp(q1,q2,amount);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionSlerp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q1=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q1=*ptr_q1;
		Quaternion * ptr_q2=(Quaternion *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_q2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q2=*ptr_q2;
		double double_amount;
		int err_amount=JS_ToFloat64(ctx,&double_amount,argv[2]);
		if(err_amount<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float amount=((float)double_amount);
		Quaternion returnVal=QuaternionSlerp(q1,q2,amount);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionCubicHermiteSpline(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q1=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q1=*ptr_q1;
		Quaternion * ptr_outTangent1=(Quaternion *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_outTangent1==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion outTangent1=*ptr_outTangent1;
		Quaternion * ptr_q2=(Quaternion *)JS_GetOpaque(argv[2],js_Vector4_class_id);
		if(ptr_q2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q2=*ptr_q2;
		Quaternion * ptr_inTangent2=(Quaternion *)JS_GetOpaque(argv[3],js_Vector4_class_id);
		if(ptr_inTangent2==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion inTangent2=*ptr_inTangent2;
		double double_t;
		int err_t=JS_ToFloat64(ctx,&double_t,argv[4]);
		if(err_t<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		float t=((float)double_t);
		Quaternion returnVal=QuaternionCubicHermiteSpline(q1,outTangent1,q2,inTangent2,t);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionFromVector3ToVector3(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_from=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_from==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 from=*ptr_from;
		Vector3 * ptr_to=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(ptr_to==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 to=*ptr_to;
		Quaternion returnVal=QuaternionFromVector3ToVector3(from,to);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionFromMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_mat=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_mat==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix mat=*ptr_mat;
		Quaternion returnVal=QuaternionFromMatrix(mat);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionToMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		Matrix returnVal=QuaternionToMatrix(q);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionFromAxisAngle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Vector3 * ptr_axis=(Vector3 *)JS_GetOpaque(argv[0],js_Vector3_class_id);
		if(ptr_axis==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Vector3 axis=*ptr_axis;
		double double_angle;
		int err_angle=JS_ToFloat64(ctx,&double_angle,argv[1]);
		if(err_angle<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float angle=((float)double_angle);
		Quaternion returnVal=QuaternionFromAxisAngle(axis,angle);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionToAxisAngle(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		memoryNode * memoryHead=(memoryNode *)calloc((size_t)1,sizeof(memoryNode));
		memoryNode * memoryCurrent=memoryHead;
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q==NULL){
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		Vector3 * outAxis;
		int64_t size_outAxis;
		JSClassID outAxis_class=JS_GetClassID(argv[1]);
		JSValue src=argv[1];
		if(outAxis_class==js_ArrayProxy_class_id){
			void * opaque_outAxis=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_outAxis=((ArrayProxy_class *)opaque_outAxis)[0];
			src =AP_outAxis.values(ctx,AP_outAxis.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&src);
		}
		if(JS_IsArray(src)==1){
			if(JS_GetLength(ctx,src,&size_outAxis)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			outAxis =(Vector3 *)js_malloc(ctx,size_outAxis*sizeof(Vector3));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)outAxis);
			int i;
			for(i=0;i<size_outAxis;i++){
				JSValue js_outAxis=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				Vector3 * ptr_outAxisi=(Vector3 *)JS_GetOpaque(js_outAxis,js_Vector3_class_id);
				if(ptr_outAxisi==NULL){
					JS_ThrowTypeError(ctx,(const char *)"js_outAxis does not allow null");
					return JS_EXCEPTION;
				}
				outAxis[i] =*ptr_outAxisi;
				JS_FreeValue(ctx,js_outAxis);
			}
		}else if(JS_IsArrayBuffer(src)==1){
			outAxis =(Vector3 *)JS_GetArrayBuffer(ctx,(size_t *)&size_outAxis,src);
		}else{
			memoryClear(ctx,memoryHead);
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type Vector3 *");
			return JS_EXCEPTION;
		}
		float * outAngle;
		int64_t size_outAngle;
		JSClassID outAngle_class=JS_GetClassID(argv[2]);
		src =argv[2];
		if(outAngle_class==js_ArrayProxy_class_id){
			void * opaque_outAngle=JS_GetOpaque(src,js_ArrayProxy_class_id);
			ArrayProxy_class AP_outAngle=((ArrayProxy_class *)opaque_outAngle)[0];
			src =AP_outAngle.values(ctx,AP_outAngle.opaque,(int)0,(bool)false);
			memoryCurrent =memoryStore(memoryCurrent,JS_FreeValue,(void *)&src);
		}
		if(JS_IsArray(src)==1){
			if(JS_GetLength(ctx,src,&size_outAngle)==-1){
				memoryClear(ctx,memoryHead);
				return JS_EXCEPTION;
			}
			outAngle =(float *)js_malloc(ctx,size_outAngle*sizeof(float));
			memoryCurrent =memoryStore(memoryCurrent,js_free,(void *)outAngle);
			int i;
			for(i=0;i<size_outAngle;i++){
				JSValue js_outAngle=JS_GetPropertyUint32(ctx,src,(uint32_t)i);
				double double_outAnglei;
				int err_outAnglei=JS_ToFloat64(ctx,&double_outAnglei,js_outAngle);
				if(err_outAnglei<0){
					JS_ThrowTypeError(ctx,(const char *)"js_outAngle is not numeric");
					return JS_EXCEPTION;
				}
				outAngle[i] =((float)double_outAnglei);
				JS_FreeValue(ctx,js_outAngle);
			}
		}else if(JS_IsArrayBuffer(src)==1){
			outAngle =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_outAngle,src);
		}else{
			JSClassID classid_outAngle=JS_GetClassID(src);
			if(classid_outAngle==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_outAngle;
				JSValue da_outAngle=JS_GetTypedArrayBuffer(ctx,src,&offset_outAngle,(size_t *)&size_outAngle,NULL);
				outAngle =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_outAngle,da_outAngle);
				outAngle +=offset_outAngle;
				size_outAngle -=offset_outAngle;
				memoryCurrent =memoryStore(memoryCurrent,JS_FreeValuePtr,(void *)&da_outAngle);
			}else{
				memoryClear(ctx,memoryHead);
				JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type float *");
				return JS_EXCEPTION;
			}
		}
		QuaternionToAxisAngle(q,outAxis,outAngle);
		memoryClear(ctx,memoryHead);
		return JS_UNDEFINED;
	}
	
	static JSValue js_QuaternionFromEuler(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		double double_pitch;
		int err_pitch=JS_ToFloat64(ctx,&double_pitch,argv[0]);
		if(err_pitch<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		float pitch=((float)double_pitch);
		double double_yaw;
		int err_yaw=JS_ToFloat64(ctx,&double_yaw,argv[1]);
		if(err_yaw<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float yaw=((float)double_yaw);
		double double_roll;
		int err_roll=JS_ToFloat64(ctx,&double_roll,argv[2]);
		if(err_roll<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float roll=((float)double_roll);
		Quaternion returnVal=QuaternionFromEuler(pitch,yaw,roll);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionToEuler(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		Vector3 returnVal=QuaternionToEuler(q);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionTransform(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		Matrix * ptr_mat=(Matrix *)JS_GetOpaque(argv[1],js_Matrix_class_id);
		if(ptr_mat==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix mat=*ptr_mat;
		Quaternion returnVal=QuaternionTransform(q,mat);
		Quaternion * ptr_ret=(Quaternion *)js_malloc(ctx,sizeof(Quaternion));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector4_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_QuaternionEquals(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Quaternion * ptr_p=(Quaternion *)JS_GetOpaque(argv[0],js_Vector4_class_id);
		if(ptr_p==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion p=*ptr_p;
		Quaternion * ptr_q=(Quaternion *)JS_GetOpaque(argv[1],js_Vector4_class_id);
		if(ptr_q==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not allow null");
			return JS_EXCEPTION;
		}
		Quaternion q=*ptr_q;
		int returnVal=QuaternionEquals(p,q);
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)returnVal));
		return ret;
	}
	
	static JSValue js_MatrixDecompose(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Matrix * ptr_mat=(Matrix *)JS_GetOpaque(argv[0],js_Matrix_class_id);
		if(ptr_mat==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Matrix mat=*ptr_mat;
		Vector3 * translation=(Vector3 *)JS_GetOpaque(argv[1],js_Vector3_class_id);
		if(translation==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type Vector3");
			return JS_EXCEPTION;
		}
		Quaternion * rotation=(Quaternion *)JS_GetOpaque(argv[2],js_Vector4_class_id);
		if(rotation==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not match type Quaternion");
			return JS_EXCEPTION;
		}
		Vector3 * scale=(Vector3 *)JS_GetOpaque(argv[3],js_Vector3_class_id);
		if(scale==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] does not match type Vector3");
			return JS_EXCEPTION;
		}
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
		if(!m){
			return NULL;
		}
		size_t listcount=countof(jsraymath_funcs);
		JS_AddModuleExportList(ctx,m,jsraymath_funcs,(int)listcount);
		JS_AddModuleExport(ctx,m,(const char *)"float3");
		JS_AddModuleExport(ctx,m,(const char *)"float16");
		JS_AddModuleExport(ctx,m,(const char *)"EPSILON");
		return m;
	}

#endif //JS_raymath_GUARD