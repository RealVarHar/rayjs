#ifndef JS_js_rlightmapper_GUARD
	#define JS_js_rlightmapper_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <rayjs_generated.h>
	#include <raylib.h>
#define RLIGHTMAPPER_IMPLEMENTATION ;
	#include <rlightmapper.h>
	
	static void js_Lightmapper_finalizer(JSRuntime * rt,JSValue val){
		Lightmapper * ptr=(Lightmapper *)JS_GetOpaque(val,js_Lightmapper_class_id);
		if(ptr){
			js_free_rt(rt,(void *)ptr);
		}
	}
	
	static JSValue js_Lightmapper_data_values(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Lightmapper * ptr=(Lightmapper *)ptr_u;
		JSValue ret;
		ret =JS_NewArray(ctx);
		int i;
		for(i=0;i<ptr[0].w*ptr[0].h*4;i++){
			JSValue js_ret=JS_NewFloat64(ctx,((double)ptr[0].data[i]));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,js_ret,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Lightmapper_data_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Lightmapper * ptr=(Lightmapper *)ptr_u;
		int length=(int)ptr[0].w*ptr[0].h*4;
		keys[0] =(JSPropertyEnum *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		int i;
		for(i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Lightmapper_data_get(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Lightmapper * ptr=(Lightmapper *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				JSValue ret=JS_NewInt32(ctx,(int32_t)ptr[0].w*ptr[0].h*((long)4));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}else{
			if(property>=0&&property<ptr[0].w*ptr[0].h*4){
				float src=ptr[0].data[property];
				JSValue ret=JS_NewFloat64(ctx,((double)src));
				return ret;
			}else{
				return JS_UNDEFINED;
			}
		}
	}
	
	static int js_Lightmapper_data_set(JSContext * ctx,void * ptr_u,JSValue set_to,int property,bool as_sting){
		Lightmapper * ptr=(Lightmapper *)ptr_u;
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
			ptr[0].data[property] =ret;
		}
		return true;
	}
	
	static int js_Lightmapper_data_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Lightmapper * ptr=(Lightmapper *)ptr_u;
		if(as_sting==true){
			if(property==JS_ATOM_length){
				return true;
			}else{
				return false;
			}
		}else{
			if(property>=0&&property<ptr[0].w*ptr[0].h*4){
				return true;
			}else{
				return false;
			}
		}
	}
	
	static JSValue js_Lightmapper_get_data(JSContext * ctx,JSValue this_val){
		Lightmapper * ptr=(Lightmapper *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = this_val,.opaque = ptr,.values = js_Lightmapper_data_values,.keys = js_Lightmapper_data_keys,.get = js_Lightmapper_data_get,.set = js_Lightmapper_data_set,.has = js_Lightmapper_data_has});
		return ret;
	}
	
	static JSValue js_Lightmapper_set_data(JSContext * ctx,JSValue this_val,JSValue v){
		Lightmapper * ptr=(Lightmapper *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
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
		}
		if(JS_IsArray(v)==1){
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
		if(ptr[0].data!=NULL){
			jsc_free(ctx,(void *)ptr[0].data);
		}
		ptr[0].data =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Lightmapper_get_w(JSContext * ctx,JSValue this_val){
		Lightmapper * ptr=(Lightmapper *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		int w=ptr[0].w;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)w));
		return ret;
	}
	
	static JSValue js_Lightmapper_set_w(JSContext * ctx,JSValue this_val,JSValue v){
		Lightmapper * ptr=(Lightmapper *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].w=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Lightmapper_get_h(JSContext * ctx,JSValue this_val){
		Lightmapper * ptr=(Lightmapper *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		int h=ptr[0].h;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)h));
		return ret;
	}
	
	static JSValue js_Lightmapper_set_h(JSContext * ctx,JSValue this_val,JSValue v){
		Lightmapper * ptr=(Lightmapper *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].h=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Lightmapper_get_progress(JSContext * ctx,JSValue this_val){
		Lightmapper * ptr=(Lightmapper *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		float progress=ptr[0].progress;
		JSValue ret=JS_NewFloat64(ctx,((double)progress));
		return ret;
	}
	
	static JSValue js_Lightmapper_set_progress(JSContext * ctx,JSValue this_val,JSValue v){
		Lightmapper * ptr=(Lightmapper *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		double double_value;
		int err_value=JS_ToFloat64(ctx,&double_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		float value=((float)double_value);
		ptr[0].progress=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Lightmapper_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Lightmapper", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("lm_handle",NULL,NULL),
		JS_CGETSET_DEF("data",js_Lightmapper_get_data,js_Lightmapper_set_data),
		JS_CGETSET_DEF("w",js_Lightmapper_get_w,js_Lightmapper_set_w),
		JS_CGETSET_DEF("h",js_Lightmapper_get_h,js_Lightmapper_set_h),
		JS_CGETSET_DEF("progress",js_Lightmapper_get_progress,js_Lightmapper_set_progress)
	};
	
	static int js_declare_Lightmapper(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Lightmapper_class_id);
		JSClassDef js_Lightmapper_def={ .class_name = "Lightmapper", .finalizer = js_Lightmapper_finalizer };
		JS_NewClass(rt,js_Lightmapper_class_id,(const JSClassDef *)&js_Lightmapper_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Lightmapper_proto_funcs,(int)countof(js_Lightmapper_proto_funcs));
		JS_SetClassProto(ctx,js_Lightmapper_class_id,proto);
		return 0;
	}
	
	static void js_LightmapperConfig_finalizer(JSRuntime * rt,JSValue val){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque(val,js_LightmapperConfig_class_id);
		if(ptr){
			js_free_rt(rt,(void *)ptr);
		}
	}
	
	static JSValue js_LightmapperConfig_get_hemisphereSize(JSContext * ctx,JSValue this_val){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		int hemisphereSize=ptr[0].hemisphereSize;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)hemisphereSize));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_hemisphereSize(JSContext * ctx,JSValue this_val,JSValue v){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].hemisphereSize=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_zNear(JSContext * ctx,JSValue this_val){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		float zNear=ptr[0].zNear;
		JSValue ret=JS_NewFloat64(ctx,((double)zNear));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_zNear(JSContext * ctx,JSValue this_val,JSValue v){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		double double_value;
		int err_value=JS_ToFloat64(ctx,&double_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		float value=((float)double_value);
		ptr[0].zNear=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_zFar(JSContext * ctx,JSValue this_val){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		float zFar=ptr[0].zFar;
		JSValue ret=JS_NewFloat64(ctx,((double)zFar));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_zFar(JSContext * ctx,JSValue this_val,JSValue v){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		double double_value;
		int err_value=JS_ToFloat64(ctx,&double_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		float value=((float)double_value);
		ptr[0].zFar=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_backgroundColor(JSContext * ctx,JSValue this_val){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		Color backgroundColor=ptr[0].backgroundColor;
		Color * ptr_ret=(Color *)js_malloc(ctx,sizeof(Color));
		ptr_ret[0]=backgroundColor;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Color_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_backgroundColor(JSContext * ctx,JSValue this_val,JSValue v){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		Color * ptr_value=(Color *)JS_GetOpaque(v,js_Color_class_id);
		if(ptr_value==NULL){
			JS_ThrowTypeError(ctx,(const char *)"v does not allow null");
			return JS_EXCEPTION;
		}
		Color value=*ptr_value;
		ptr[0].backgroundColor=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_interpolationPasses(JSContext * ctx,JSValue this_val){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		int interpolationPasses=ptr[0].interpolationPasses;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)interpolationPasses));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_interpolationPasses(JSContext * ctx,JSValue this_val,JSValue v){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		int32_t long_value;
		int err_value=JS_ToInt32(ctx,&long_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		int value=((int)long_value);
		ptr[0].interpolationPasses=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_interpolationThreshold(JSContext * ctx,JSValue this_val){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		float interpolationThreshold=ptr[0].interpolationThreshold;
		JSValue ret=JS_NewFloat64(ctx,((double)interpolationThreshold));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_interpolationThreshold(JSContext * ctx,JSValue this_val,JSValue v){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		double double_value;
		int err_value=JS_ToFloat64(ctx,&double_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		float value=((float)double_value);
		ptr[0].interpolationThreshold=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_cameraToSurfaceDistanceModifier(JSContext * ctx,JSValue this_val){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		float cameraToSurfaceDistanceModifier=ptr[0].cameraToSurfaceDistanceModifier;
		JSValue ret=JS_NewFloat64(ctx,((double)cameraToSurfaceDistanceModifier));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_cameraToSurfaceDistanceModifier(JSContext * ctx,JSValue this_val,JSValue v){
		LightmapperConfig * ptr=(LightmapperConfig *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		double double_value;
		int err_value=JS_ToFloat64(ctx,&double_value,v);
		if(err_value<0){
			JS_ThrowTypeError(ctx,(const char *)"v is not numeric");
			return JS_EXCEPTION;
		}
		float value=((float)double_value);
		ptr[0].cameraToSurfaceDistanceModifier=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_LightmapperConfig_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","LightmapperConfig", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("hemisphereSize",js_LightmapperConfig_get_hemisphereSize,js_LightmapperConfig_set_hemisphereSize),
		JS_CGETSET_DEF("zNear",js_LightmapperConfig_get_zNear,js_LightmapperConfig_set_zNear),
		JS_CGETSET_DEF("zFar",js_LightmapperConfig_get_zFar,js_LightmapperConfig_set_zFar),
		JS_CGETSET_DEF("backgroundColor",js_LightmapperConfig_get_backgroundColor,js_LightmapperConfig_set_backgroundColor),
		JS_CGETSET_DEF("interpolationPasses",js_LightmapperConfig_get_interpolationPasses,js_LightmapperConfig_set_interpolationPasses),
		JS_CGETSET_DEF("interpolationThreshold",js_LightmapperConfig_get_interpolationThreshold,js_LightmapperConfig_set_interpolationThreshold),
		JS_CGETSET_DEF("cameraToSurfaceDistanceModifier",js_LightmapperConfig_get_cameraToSurfaceDistanceModifier,js_LightmapperConfig_set_cameraToSurfaceDistanceModifier)
	};
	
	static int js_declare_LightmapperConfig(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_LightmapperConfig_class_id);
		JSClassDef js_LightmapperConfig_def={ .class_name = "LightmapperConfig", .finalizer = js_LightmapperConfig_finalizer };
		JS_NewClass(rt,js_LightmapperConfig_class_id,(const JSClassDef *)&js_LightmapperConfig_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_LightmapperConfig_proto_funcs,(int)countof(js_LightmapperConfig_proto_funcs));
		JS_SetClassProto(ctx,js_LightmapperConfig_class_id,proto);
		return 0;
	}
	
	static JSValue js_Lightmapper_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			Lightmapper * ptr__return=(Lightmapper *)js_calloc(ctx,(size_t)1,sizeof(Lightmapper));
			JSValue _return=JS_NewObjectClass(ctx,(int)js_Lightmapper_class_id);
			JS_SetOpaque(_return,(void *)ptr__return);
			return _return;
		}
		void * lm_handle;
		int64_t size_lm_handle;
		if(JS_IsArrayBuffer(argv[0])==1){
			lm_handle =(void *)JS_GetArrayBuffer(ctx,(size_t *)&size_lm_handle,argv[0]);
		}else{
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type void *");
			return JS_EXCEPTION;
		}
		float * data;
		bool freesrc_data=(bool)false;
		JSValue da_data;
		int64_t size_data;
		JSClassID data_class=JS_GetClassID(argv[1]);
		if(data_class==js_ArrayProxy_class_id){
			void * opaque_data=JS_GetOpaque(argv[1],js_ArrayProxy_class_id);
			ArrayProxy_class AP_data=((ArrayProxy_class *)opaque_data)[0];
			argv[1] =AP_data.values(ctx,AP_data.opaque,(int)0,(bool)false);
			freesrc_data =(bool)true;
		}
		if(JS_IsArray(argv[1])==1){
			if(JS_GetLength(ctx,argv[1],&size_data)==-1){
				return JS_EXCEPTION;
			}
			data =(float *)js_malloc(ctx,size_data*sizeof(float));
			int i;
			for(i=0;i<size_data;i++){
				JSValue js_data=JS_GetPropertyUint32(ctx,argv[1],(uint32_t)i);
				double double_datai;
				int err_datai=JS_ToFloat64(ctx,&double_datai,js_data);
				if(err_datai<0){
					JS_ThrowTypeError(ctx,(const char *)"js_data is not numeric");
					return JS_EXCEPTION;
				}
				data[i] =((float)double_datai);
				JS_FreeValue(ctx,js_data);
			}
		}else if(JS_IsArrayBuffer(argv[1])==1){
			data =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_data,argv[1]);
		}else{
			JSClassID classid_data=JS_GetClassID(argv[1]);
			if(classid_data==JS_CLASS_FLOAT32_ARRAY){
				size_t offset_data;
				da_data =JS_GetTypedArrayBuffer(ctx,argv[1],&offset_data,(size_t *)&size_data,NULL);
				data =(float *)JS_GetArrayBuffer(ctx,(size_t *)&size_data,da_data);
				data +=offset_data;
				size_data -=offset_data;
			}else{
				if(freesrc_data){
					JS_FreeValue(ctx,argv[1]);
				}
				JS_ThrowTypeError(ctx,(const char *)"argv[1] does not match type float *");
				return JS_EXCEPTION;
			}
		}
		int32_t long_w;
		int err_w=JS_ToInt32(ctx,&long_w,argv[2]);
		if(err_w<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		int w=((int)long_w);
		int32_t long_h;
		int err_h=JS_ToInt32(ctx,&long_h,argv[3]);
		if(err_h<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not numeric");
			return JS_EXCEPTION;
		}
		int h=((int)long_h);
		double double_progress;
		int err_progress=JS_ToFloat64(ctx,&double_progress,argv[4]);
		if(err_progress<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		float progress=((float)double_progress);
		Lightmapper _struct={
			lm_handle,
			data,
			w,
			h,
			progress
		};
		Lightmapper * ptr__return=(Lightmapper *)js_malloc(ctx,sizeof(Lightmapper));
		ptr__return[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,(int)js_Lightmapper_class_id);
		JS_SetOpaque(_return,(void *)ptr__return);
		return _return;
	}
	
	static JSValue js_LightmapperConfig_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			LightmapperConfig * ptr__return=(LightmapperConfig *)js_calloc(ctx,(size_t)1,sizeof(LightmapperConfig));
			JSValue _return=JS_NewObjectClass(ctx,(int)js_LightmapperConfig_class_id);
			JS_SetOpaque(_return,(void *)ptr__return);
			return _return;
		}
		int32_t long_hemisphereSize;
		int err_hemisphereSize=JS_ToInt32(ctx,&long_hemisphereSize,argv[0]);
		if(err_hemisphereSize<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int hemisphereSize=((int)long_hemisphereSize);
		double double_zNear;
		int err_zNear=JS_ToFloat64(ctx,&double_zNear,argv[1]);
		if(err_zNear<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float zNear=((float)double_zNear);
		double double_zFar;
		int err_zFar=JS_ToFloat64(ctx,&double_zFar,argv[2]);
		if(err_zFar<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not numeric");
			return JS_EXCEPTION;
		}
		float zFar=((float)double_zFar);
		Color * ptr_backgroundColor=(Color *)JS_GetOpaque(argv[3],js_Color_class_id);
		if(ptr_backgroundColor==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] does not allow null");
			return JS_EXCEPTION;
		}
		Color backgroundColor=*ptr_backgroundColor;
		int32_t long_interpolationPasses;
		int err_interpolationPasses=JS_ToInt32(ctx,&long_interpolationPasses,argv[4]);
		if(err_interpolationPasses<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not numeric");
			return JS_EXCEPTION;
		}
		int interpolationPasses=((int)long_interpolationPasses);
		double double_interpolationThreshold;
		int err_interpolationThreshold=JS_ToFloat64(ctx,&double_interpolationThreshold,argv[5]);
		if(err_interpolationThreshold<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[5] is not numeric");
			return JS_EXCEPTION;
		}
		float interpolationThreshold=((float)double_interpolationThreshold);
		double double_cameraToSurfaceDistanceModifier;
		int err_cameraToSurfaceDistanceModifier=JS_ToFloat64(ctx,&double_cameraToSurfaceDistanceModifier,argv[6]);
		if(err_cameraToSurfaceDistanceModifier<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[6] is not numeric");
			return JS_EXCEPTION;
		}
		float cameraToSurfaceDistanceModifier=((float)double_cameraToSurfaceDistanceModifier);
		LightmapperConfig _struct={
			hemisphereSize,
			zNear,
			zFar,
			backgroundColor,
			interpolationPasses,
			interpolationThreshold,
			cameraToSurfaceDistanceModifier
		};
		LightmapperConfig * ptr__return=(LightmapperConfig *)js_malloc(ctx,sizeof(LightmapperConfig));
		ptr__return[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,(int)js_LightmapperConfig_class_id);
		JS_SetOpaque(_return,(void *)ptr__return);
		return _return;
	}
	
	static JSValue js_GetDefaultLightmapperConfig(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		LightmapperConfig returnVal=GetDefaultLightmapperConfig();
		LightmapperConfig * ptr_ret=(LightmapperConfig *)js_malloc(ctx,sizeof(LightmapperConfig));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_LightmapperConfig_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadLightmapper(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		int32_t long_w;
		int err_w=JS_ToInt32(ctx,&long_w,argv[0]);
		if(err_w<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] is not numeric");
			return JS_EXCEPTION;
		}
		int w=((int)long_w);
		int32_t long_h;
		int err_h=JS_ToInt32(ctx,&long_h,argv[1]);
		if(err_h<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		int h=((int)long_h);
		Mesh * ptr_mesh=(Mesh *)JS_GetOpaque(argv[2],js_Mesh_class_id);
		if(ptr_mesh==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] does not allow null");
			return JS_EXCEPTION;
		}
		Mesh mesh=*ptr_mesh;
		LightmapperConfig * ptr_cfg=(LightmapperConfig *)JS_GetOpaque(argv[3],js_LightmapperConfig_class_id);
		if(ptr_cfg==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] does not allow null");
			return JS_EXCEPTION;
		}
		LightmapperConfig cfg=*ptr_cfg;
		Lightmapper returnVal=LoadLightmapper(w,h,mesh,cfg);
		Lightmapper * ptr_ret=(Lightmapper *)js_malloc(ctx,sizeof(Lightmapper));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Lightmapper_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadMaterialLightmapper(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Color * ptr_emissiveColor=(Color *)JS_GetOpaque(argv[0],js_Color_class_id);
		if(ptr_emissiveColor==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Color emissiveColor=*ptr_emissiveColor;
		double double_intensity;
		int err_intensity=JS_ToFloat64(ctx,&double_intensity,argv[1]);
		if(err_intensity<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float intensity=((float)double_intensity);
		Material returnVal=LoadMaterialLightmapper(emissiveColor,intensity);
		Material * ptr_ret=(Material *)js_malloc(ctx,sizeof(Material));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Material_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_UnloadLightmapper(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Lightmapper * ptr_lm=(Lightmapper *)JS_GetOpaque(argv[0],js_Lightmapper_class_id);
		if(ptr_lm==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Lightmapper lm=*ptr_lm;
		UnloadLightmapper(lm);
		return JS_UNDEFINED;
	}
	
	static JSValue js_BeginLightmap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		BeginLightmap();
		return JS_UNDEFINED;
	}
	
	static JSValue js_EndLightmap(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		EndLightmap();
		return JS_UNDEFINED;
	}
	
	static JSValue js_BeginLightmapFragment(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Lightmapper * lm=(Lightmapper *)JS_GetOpaque(argv[0],js_Lightmapper_class_id);
		if(lm==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Lightmapper");
			return JS_EXCEPTION;
		}
		bool returnVal=BeginLightmapFragment(lm);
		JS_SetOpaque(argv[0],(void *)lm);
		JSValue ret=JS_NewBool(ctx,returnVal);
		return ret;
	}
	
	static JSValue js_EndLightmapFragment(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Lightmapper * lm=(Lightmapper *)JS_GetOpaque(argv[0],js_Lightmapper_class_id);
		if(lm==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Lightmapper");
			return JS_EXCEPTION;
		}
		EndLightmapFragment(lm);
		JS_SetOpaque(argv[0],(void *)lm);
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadImageFromLightmapper(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Lightmapper * ptr_lm=(Lightmapper *)JS_GetOpaque(argv[0],js_Lightmapper_class_id);
		if(ptr_lm==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not allow null");
			return JS_EXCEPTION;
		}
		Lightmapper lm=*ptr_lm;
		Image returnVal=LoadImageFromLightmapper(lm);
		Image * ptr_ret=(Image *)js_malloc(ctx,sizeof(Image));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Image_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	static const JSCFunctionListEntry jsrlightmapper_funcs[]={
		JS_CFUNC_DEF("GetDefaultLightmapperConfig",0,js_GetDefaultLightmapperConfig),
		JS_CFUNC_DEF("LoadLightmapper",4,js_LoadLightmapper),
		JS_CFUNC_DEF("LoadMaterialLightmapper",2,js_LoadMaterialLightmapper),
		JS_CFUNC_DEF("UnloadLightmapper",1,js_UnloadLightmapper),
		JS_CFUNC_DEF("BeginLightmap",0,js_BeginLightmap),
		JS_CFUNC_DEF("EndLightmap",0,js_EndLightmap),
		JS_CFUNC_DEF("BeginLightmapFragment",1,js_BeginLightmapFragment),
		JS_CFUNC_DEF("EndLightmapFragment",1,js_EndLightmapFragment),
		JS_CFUNC_DEF("LoadImageFromLightmapper",1,js_LoadImageFromLightmapper)
	};
	
	static int js_js_rlightmapper_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsrlightmapper_funcs);
		JS_SetModuleExportList(ctx,m,jsrlightmapper_funcs,(int)listcount);
		js_declare_Lightmapper(ctx,m);
		JSValue Lightmapper_constr=JS_NewCFunction2(ctx,js_Lightmapper_constructor,(const char *)"Lightmapper",(int)5,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char *)"Lightmapper",Lightmapper_constr);
		js_declare_LightmapperConfig(ctx,m);
		JSValue LightmapperConfig_constr=JS_NewCFunction2(ctx,js_LightmapperConfig_constructor,(const char *)"LightmapperConfig",(int)7,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char *)"LightmapperConfig",LightmapperConfig_constr);
		return 0;
	}
	
	JSModuleDef * js_init_module_js_rlightmapper(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_js_rlightmapper_init);
		if(!m){
			return NULL;
		}
		size_t listcount=countof(jsrlightmapper_funcs);
		JS_AddModuleExportList(ctx,m,jsrlightmapper_funcs,(int)listcount);
		JS_AddModuleExport(ctx,m,(const char *)"Lightmapper");
		JS_AddModuleExport(ctx,m,(const char *)"LightmapperConfig");
		return m;
	}

#endif //JS_js_rlightmapper_GUARD