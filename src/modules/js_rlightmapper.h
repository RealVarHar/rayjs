#ifndef JS_rlightmapper_GUARD
	#define JS_rlightmapper_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <raylib.h>
#define RLIGHTMAPPER_IMPLEMENTATION ;
	#include <rlightmapper.h>
	
	static float js_getfloat(JSContext * ctx,JSValue src,bool * error);
	
	static float * js_getfloat_arrnc(JSContext * ctx,JSValue src,bool * error);
	
	static int js_getint(JSContext * ctx,JSValue src,bool * error);
	
	static Lightmapper js_getLightmapper(JSContext * ctx,JSValue src,bool * error){
		Lightmapper ret;
		if(JS_GetClassID(src)==js_Lightmapper_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Lightmapper_class_id);
			ret =*(Lightmapper *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Lightmapper");
			error[0]=(bool)1;
			return (Lightmapper){0};
		}
		return ret;
	}
	
	static void * js_getvoid_arr(JSContext * ctx,JSValue src,bool * error);
	
	static Color js_getColor(JSContext * ctx,JSValue src,bool * error);
	
	static LightmapperConfig js_getLightmapperConfig(JSContext * ctx,JSValue src,bool * error){
		LightmapperConfig ret;
		if(JS_GetClassID(src)==js_LightmapperConfig_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_LightmapperConfig_class_id);
			ret =*(LightmapperConfig *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type LightmapperConfig");
			error[0]=(bool)1;
			return (LightmapperConfig){0};
		}
		return ret;
	}
	
	static Mesh js_getMesh(JSContext * ctx,JSValue src,bool * error);
	
	static Lightmapper * js_getLightmapper_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr){
		Lightmapper * ret;
		if(js_IsArrayLength(ctx,src,(int64_t)1)){
			int64_t size_ret=(int64_t)1;
			JSValue src0=JS_GetPropertyUint32(ctx,src,(uint32_t)0);
			JS_FreeValue(ctx,src0);
			if(JS_GetClassID(src0)==js_Lightmapper_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src0,js_Lightmapper_class_id);
				ret =(Lightmapper  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src0 does not match type Lightmapper *");
				error[0]=(bool)1;
				return NULL;
			}
		}else if(JS_GetClassID(src)==js_Lightmapper_class_id){
			isptr[0]=(bool)true;
			if(JS_GetClassID(src)==js_Lightmapper_class_id){
				opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Lightmapper_class_id);
				ret =(Lightmapper  *)tmpshadow[0].ptr;
			}else{
				JS_ThrowTypeError(ctx,(const char  *)"src does not match type Lightmapper *");
				error[0]=(bool)1;
				return NULL;
			}
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Lightmapper *");
			error[0]=(bool)1;
			return NULL;
		}
		return ret;
	}
	
	static void js_Lightmapper_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Lightmapper_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Lightmapper_data_values(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Lightmapper * ptr=(Lightmapper  *)ptr_u;
		JSValue ret=JS_NewArray(ctx);
		for(int i=0;i<ptr[0].w*ptr[0].h*4;i++){
			float src0=ptr[0].data[i];
			JSValue ret1=JS_NewFloat64(ctx,((double)src0));
			JS_DefinePropertyValueUint32(ctx,ret,(uint32_t)i,ret1,JS_PROP_C_W_E);
		}
		if(as_sting==true){
			ret =JS_JSONStringify(ctx,ret,JS_UNDEFINED,JS_UNDEFINED);
		}
		return ret;
	}
	
	static int js_Lightmapper_data_keys(JSContext * ctx,void * ptr_u,JSPropertyEnum * * keys){
		Lightmapper * ptr=(Lightmapper  *)ptr_u;
		int length=(int)ptr[0].w*ptr[0].h*4;
		keys[0] =(JSPropertyEnum  *)js_malloc(ctx,(length+1)*sizeof(JSPropertyEnum));
		for(int i=0;i<length;i++){
			keys[0][i] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_NewAtomUInt32(ctx,i)};
		}
		keys[0][length] =(JSPropertyEnum){.is_enumerable=false, .atom=JS_ATOM_length};
		return true;
	}
	
	static JSValue js_Lightmapper_data_get(JSContext * ctx,JSValue anchor,void * ptr_u,int property,bool as_sting){
		Lightmapper * ptr=(Lightmapper  *)ptr_u;
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
		Lightmapper * ptr=(Lightmapper  *)ptr_u;
		if(as_sting==true){
			return false;
		}else{
			if(property>=0&&property<ptr[0].w*ptr[0].h*4){
				bool error=(bool)0;
				local_memlock=(bool)true;
				float ret=js_getfloat(ctx,set_to,&error);
				if(error==1)return 0;
				local_memlock=(bool)false;
				ptr[0].data[property]=ret;
				return true;
			}else{
				return false;
			}
		}
		return true;
	}
	
	static int js_Lightmapper_data_has(JSContext * ctx,void * ptr_u,int property,bool as_sting){
		Lightmapper * ptr=(Lightmapper  *)ptr_u;
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
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		Lightmapper * ptr=(Lightmapper  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		JSValue ret=js_NewArrayProxy(ctx,(ArrayProxy_class){.anchor = anchor,.opaque = ptr,.values = js_Lightmapper_data_values,.keys = js_Lightmapper_data_keys,.get = js_Lightmapper_data_get,.set = js_Lightmapper_data_set,.has = js_Lightmapper_data_has});
		return ret;
	}
	
	static JSValue js_Lightmapper_set_data(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		Lightmapper * ptr=(Lightmapper  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float * value=js_getfloat_arrnc(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		if(ptr[0].data!=NULL)jsc_free(ctx,(void  *)ptr[0].data);
		ptr[0].data =value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Lightmapper_get_w(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		Lightmapper * ptr=(Lightmapper  *)shadow[0].ptr;
		int w=ptr[0].w;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)w));
		return ret;
	}
	
	static JSValue js_Lightmapper_set_w(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		Lightmapper * ptr=(Lightmapper  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].w=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Lightmapper_get_h(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		Lightmapper * ptr=(Lightmapper  *)shadow[0].ptr;
		int h=ptr[0].h;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)h));
		return ret;
	}
	
	static JSValue js_Lightmapper_set_h(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		Lightmapper * ptr=(Lightmapper  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].h=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Lightmapper_get_progress(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		Lightmapper * ptr=(Lightmapper  *)shadow[0].ptr;
		float progress=ptr[0].progress;
		JSValue ret=JS_NewFloat64(ctx,((double)progress));
		return ret;
	}
	
	static JSValue js_Lightmapper_set_progress(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Lightmapper_class_id);
		Lightmapper * ptr=(Lightmapper  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
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
		JS_NewClass(rt,js_Lightmapper_class_id,(const JSClassDef  *)&js_Lightmapper_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Lightmapper_proto_funcs,(int)countof(js_Lightmapper_proto_funcs));
		JS_SetClassProto(ctx,js_Lightmapper_class_id,proto);
		return 0;
	}
	
	static void js_LightmapperConfig_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_LightmapperConfig_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_LightmapperConfig_get_hemisphereSize(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		int hemisphereSize=ptr[0].hemisphereSize;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)hemisphereSize));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_hemisphereSize(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].hemisphereSize=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_zNear(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		float zNear=ptr[0].zNear;
		JSValue ret=JS_NewFloat64(ctx,((double)zNear));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_zNear(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].zNear=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_zFar(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		float zFar=ptr[0].zFar;
		JSValue ret=JS_NewFloat64(ctx,((double)zFar));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_zFar(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].zFar=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_backgroundColor(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		JSValue anchor;
		if(JS_IsUndefined(shadow[0].anchor)||JS_IsNull(shadow[0].anchor)){
			anchor=this_val;
		}else{
			anchor=shadow[0].anchor;
		}
		Color * backgroundColor=&ptr[0].backgroundColor;
		JS_DupValue(ctx,anchor);
		opaqueShadow * ptr_ret=create_shadow_with_external((void  *)backgroundColor,anchor);
		JSValue ret=JS_NewObjectClass(ctx,js_Color_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_backgroundColor(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Color value=js_getColor(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].backgroundColor=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_interpolationPasses(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		int interpolationPasses=ptr[0].interpolationPasses;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)interpolationPasses));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_interpolationPasses(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].interpolationPasses=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_interpolationThreshold(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		float interpolationThreshold=ptr[0].interpolationThreshold;
		JSValue ret=JS_NewFloat64(ctx,((double)interpolationThreshold));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_interpolationThreshold(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].interpolationThreshold=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_LightmapperConfig_get_cameraToSurfaceDistanceModifier(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		float cameraToSurfaceDistanceModifier=ptr[0].cameraToSurfaceDistanceModifier;
		JSValue ret=JS_NewFloat64(ctx,((double)cameraToSurfaceDistanceModifier));
		return ret;
	}
	
	static JSValue js_LightmapperConfig_set_cameraToSurfaceDistanceModifier(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_LightmapperConfig_class_id);
		LightmapperConfig * ptr=(LightmapperConfig  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
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
		JS_NewClass(rt,js_LightmapperConfig_class_id,(const JSClassDef  *)&js_LightmapperConfig_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_LightmapperConfig_proto_funcs,(int)countof(js_LightmapperConfig_proto_funcs));
		JS_SetClassProto(ctx,js_LightmapperConfig_class_id,proto);
		return 0;
	}
	
	static JSValue js_Lightmapper_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Lightmapper));
			JSValue _return=JS_NewObjectClass(ctx,js_Lightmapper_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Lightmapper _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Lightmapper_class_id){
			Lightmapper ptr=js_getLightmapper(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
		}else{
			void * lm_handle=js_getvoid_arr(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			float * data=js_getfloat_arrnc(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			int w=js_getint(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			int h=js_getint(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			float progress=js_getfloat(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Lightmapper){
				lm_handle,
				data,
				w,
				h,
				progress
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Lightmapper));
		Lightmapper * _returnptr=((Lightmapper *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Lightmapper_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_LightmapperConfig_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(LightmapperConfig));
			JSValue _return=JS_NewObjectClass(ctx,js_LightmapperConfig_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		LightmapperConfig _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_LightmapperConfig_class_id){
			LightmapperConfig ptr=js_getLightmapperConfig(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			int hemisphereSize=js_getint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			float zNear=js_getfloat(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			float zFar=js_getfloat(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			Color backgroundColor=js_getColor(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			int interpolationPasses=js_getint(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			float interpolationThreshold=js_getfloat(ctx,argv[5],&error);
			if(error==1)return JS_EXCEPTION;
			float cameraToSurfaceDistanceModifier=js_getfloat(ctx,argv[6],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(LightmapperConfig){
				hemisphereSize,
				zNear,
				zFar,
				backgroundColor,
				interpolationPasses,
				interpolationThreshold,
				cameraToSurfaceDistanceModifier
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(LightmapperConfig));
		LightmapperConfig * _returnptr=((LightmapperConfig *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_LightmapperConfig_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_GetDefaultLightmapperConfig(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		LightmapperConfig returnVal=GetDefaultLightmapperConfig();
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(LightmapperConfig));
		LightmapperConfig * ptr2_ret=((LightmapperConfig *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_LightmapperConfig_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadLightmapper(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int w=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		int h=js_getint(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Mesh mesh=js_getMesh(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		LightmapperConfig cfg=js_getLightmapperConfig(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Lightmapper returnVal=LoadLightmapper(w,h,mesh,cfg);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Lightmapper));
		Lightmapper * ptr2_ret=((Lightmapper *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Lightmapper_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_LoadMaterialLightmapper(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Color emissiveColor=js_getColor(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float intensity=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Material returnVal=LoadMaterialLightmapper(emissiveColor,intensity);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Material));
		Material * ptr2_ret=((Material *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Material_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_UnloadLightmapper(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Lightmapper lm=js_getLightmapper(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
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
		bool error=(bool)0;
		bool lm_isptr=(bool)false;
		Lightmapper * lm=js_getLightmapper_ptr(ctx,argv[0],&error,&lm_isptr);
		if(error==1)return JS_EXCEPTION;
		bool returnVal=BeginLightmapFragment(lm);
		if(lm_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Lightmapper));
			Lightmapper * ptr2_src=((Lightmapper *)(ptr_src+1));
			ptr2_src[0]=lm[0];
			JSValue src=JS_NewObjectClass(ctx,js_Lightmapper_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		JSValue ret=JS_NewBool(ctx,returnVal);
		memoryClear(ctx);
		return ret;
	}
	
	static JSValue js_EndLightmapFragment(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool lm_isptr=(bool)false;
		Lightmapper * lm=js_getLightmapper_ptr(ctx,argv[0],&error,&lm_isptr);
		if(error==1)return JS_EXCEPTION;
		EndLightmapFragment(lm);
		if(lm_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Lightmapper));
			Lightmapper * ptr2_src=((Lightmapper *)(ptr_src+1));
			ptr2_src[0]=lm[0];
			JSValue src=JS_NewObjectClass(ctx,js_Lightmapper_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		memoryClear(ctx);
		return JS_UNDEFINED;
	}
	
	static JSValue js_LoadImageFromLightmapper(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Lightmapper lm=js_getLightmapper(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Image returnVal=LoadImageFromLightmapper(lm);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Image));
		Image * ptr2_ret=((Image *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Image_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
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
	
	static int js_rlightmapper_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsrlightmapper_funcs);
		JS_SetModuleExportList(ctx,m,jsrlightmapper_funcs,(int)listcount);
		js_declare_Lightmapper(ctx,m);
		JSValue Lightmapper_constr=JS_NewCFunction2(ctx,js_Lightmapper_constructor,(const char  *)"Lightmapper",(int)5,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Lightmapper",Lightmapper_constr);
		js_declare_LightmapperConfig(ctx,m);
		JSValue LightmapperConfig_constr=JS_NewCFunction2(ctx,js_LightmapperConfig_constructor,(const char  *)"LightmapperConfig",(int)7,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"LightmapperConfig",LightmapperConfig_constr);
		return 0;
	}
	
	JSModuleDef * js_init_module_rlightmapper(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_rlightmapper_init);
		if(!m)return NULL;
		size_t listcount=countof(jsrlightmapper_funcs);
		JS_AddModuleExportList(ctx,m,jsrlightmapper_funcs,(int)listcount);
		JS_AddModuleExport(ctx,m,(const char  *)"Lightmapper");
		JS_AddModuleExport(ctx,m,(const char  *)"LightmapperConfig");
		return m;
	}

#endif //JS_rlightmapper_GUARD