#ifndef JS_rlights_GUARD
	#define JS_rlights_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <raylib.h>
#define RLIGHTS_IMPLEMENTATION ;
	#include <rlights.h>
	
	static int js_getint(JSContext * ctx,JSValue src,bool * error);
	
	static bool js_getbool(JSContext * ctx,JSValue src,bool * error);
	
	static Vector3 js_getVector3(JSContext * ctx,JSValue src,bool * error);
	
	static Color js_getColor(JSContext * ctx,JSValue src,bool * error);
	
	static float js_getfloat(JSContext * ctx,JSValue src,bool * error);
	
	static Light js_getLight(JSContext * ctx,JSValue src,bool * error){
		Light ret;
		if(JS_GetClassID(src)==js_Light_class_id){
			opaqueShadow * tmpshadow=(opaqueShadow  *)JS_GetOpaque(src,js_Light_class_id);
			ret =*(Light *)tmpshadow[0].ptr;
		}else{
			JS_ThrowTypeError(ctx,(const char  *)"src does not match type Light");
			error[0]=(bool)1;
			return (Light){0};
		}
		return ret;
	}
	
	static Shader js_getShader(JSContext * ctx,JSValue src,bool * error);
	
	static void js_Light_finalizer(JSRuntime * rt,JSValue val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque(val,js_Light_class_id);
		deallocate_shadow(rt,shadow);
	}
	
	static JSValue js_Light_get_type(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		int type=ptr[0].type;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)type));
		return ret;
	}
	
	static JSValue js_Light_set_type(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].type=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Light_get_enabled(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		bool enabled=ptr[0].enabled;
		JSValue ret=JS_NewBool(ctx,enabled);
		return ret;
	}
	
	static JSValue js_Light_set_enabled(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		bool value=js_getbool(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].enabled=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Light_get_position(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
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
	
	static JSValue js_Light_set_position(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].position=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Light_get_target(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
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
	
	static JSValue js_Light_set_target(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Vector3 value=js_getVector3(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].target=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Light_get_color(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
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
	
	static JSValue js_Light_set_color(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		Color value=js_getColor(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].color=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Light_get_attenuation(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		float attenuation=ptr[0].attenuation;
		JSValue ret=JS_NewFloat64(ctx,((double)attenuation));
		return ret;
	}
	
	static JSValue js_Light_set_attenuation(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		float value=js_getfloat(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].attenuation=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Light_get_enabledLoc(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		int enabledLoc=ptr[0].enabledLoc;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)enabledLoc));
		return ret;
	}
	
	static JSValue js_Light_set_enabledLoc(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].enabledLoc=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Light_get_typeLoc(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		int typeLoc=ptr[0].typeLoc;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)typeLoc));
		return ret;
	}
	
	static JSValue js_Light_set_typeLoc(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].typeLoc=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Light_get_positionLoc(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		int positionLoc=ptr[0].positionLoc;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)positionLoc));
		return ret;
	}
	
	static JSValue js_Light_set_positionLoc(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].positionLoc=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Light_get_targetLoc(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		int targetLoc=ptr[0].targetLoc;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)targetLoc));
		return ret;
	}
	
	static JSValue js_Light_set_targetLoc(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].targetLoc=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Light_get_colorLoc(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		int colorLoc=ptr[0].colorLoc;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)colorLoc));
		return ret;
	}
	
	static JSValue js_Light_set_colorLoc(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].colorLoc=value;
		return JS_UNDEFINED;
	}
	
	static JSValue js_Light_get_attenuationLoc(JSContext * ctx,JSValue this_val){
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		int attenuationLoc=ptr[0].attenuationLoc;
		JSValue ret=JS_NewInt32(ctx,(int32_t)((long)attenuationLoc));
		return ret;
	}
	
	static JSValue js_Light_set_attenuationLoc(JSContext * ctx,JSValue this_val,JSValue v){
		bool error=(bool)0;
		opaqueShadow * shadow=(opaqueShadow  *)JS_GetOpaque2(ctx,this_val,js_Light_class_id);
		Light * ptr=(Light  *)shadow[0].ptr;
		local_memlock=(bool)true;
		int value=js_getint(ctx,v,&error);
		if(error==1)return JS_EXCEPTION;
		local_memlock=(bool)false;
		ptr[0].attenuationLoc=value;
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry js_Light_proto_funcs[]={
		JS_PROP_STRING_DEF("[Symbol.toStringTag]","Light", JS_PROP_CONFIGURABLE),
		JS_CGETSET_DEF("type",js_Light_get_type,js_Light_set_type),
		JS_CGETSET_DEF("enabled",js_Light_get_enabled,js_Light_set_enabled),
		JS_CGETSET_DEF("position",js_Light_get_position,js_Light_set_position),
		JS_CGETSET_DEF("target",js_Light_get_target,js_Light_set_target),
		JS_CGETSET_DEF("color",js_Light_get_color,js_Light_set_color),
		JS_CGETSET_DEF("attenuation",js_Light_get_attenuation,js_Light_set_attenuation),
		JS_CGETSET_DEF("enabledLoc",js_Light_get_enabledLoc,js_Light_set_enabledLoc),
		JS_CGETSET_DEF("typeLoc",js_Light_get_typeLoc,js_Light_set_typeLoc),
		JS_CGETSET_DEF("positionLoc",js_Light_get_positionLoc,js_Light_set_positionLoc),
		JS_CGETSET_DEF("targetLoc",js_Light_get_targetLoc,js_Light_set_targetLoc),
		JS_CGETSET_DEF("colorLoc",js_Light_get_colorLoc,js_Light_set_colorLoc),
		JS_CGETSET_DEF("attenuationLoc",js_Light_get_attenuationLoc,js_Light_set_attenuationLoc)
	};
	
	static int js_declare_Light(JSContext * ctx,JSModuleDef * m){
		JSRuntime * rt=JS_GetRuntime(ctx);
		JS_NewClassID(rt,&js_Light_class_id);
		JSClassDef js_Light_def={ .class_name = "Light", .finalizer = js_Light_finalizer };
		JS_NewClass(rt,js_Light_class_id,(const JSClassDef  *)&js_Light_def);
		JSValue proto=JS_NewObject(ctx);
		JS_SetPropertyFunctionList(ctx,proto,js_Light_proto_funcs,(int)countof(js_Light_proto_funcs));
		JS_SetClassProto(ctx,js_Light_class_id,proto);
		return 0;
	}
	
	static JSValue js_Light_constructor(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		if(argc==0){
			opaqueShadow * ptr__return=create_shadow_with_data0(sizeof(Light));
			JSValue _return=JS_NewObjectClass(ctx,js_Light_class_id);
			JS_SetOpaque(_return,(void  *)ptr__return);
			return _return;
		}
		bool error=(bool)0;
		local_memlock=(bool)true;
		Light _struct;
		if(argc==1&&JS_GetClassID(argv[0])==js_Light_class_id){
			Light ptr=js_getLight(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =ptr;
		}else{
			int type=js_getint(ctx,argv[0],&error);
			if(error==1)return JS_EXCEPTION;
			bool enabled=js_getbool(ctx,argv[1],&error);
			if(error==1)return JS_EXCEPTION;
			Vector3 position=js_getVector3(ctx,argv[2],&error);
			if(error==1)return JS_EXCEPTION;
			Vector3 target=js_getVector3(ctx,argv[3],&error);
			if(error==1)return JS_EXCEPTION;
			Color color=js_getColor(ctx,argv[4],&error);
			if(error==1)return JS_EXCEPTION;
			float attenuation=js_getfloat(ctx,argv[5],&error);
			if(error==1)return JS_EXCEPTION;
			int enabledLoc=js_getint(ctx,argv[6],&error);
			if(error==1)return JS_EXCEPTION;
			int typeLoc=js_getint(ctx,argv[7],&error);
			if(error==1)return JS_EXCEPTION;
			int positionLoc=js_getint(ctx,argv[8],&error);
			if(error==1)return JS_EXCEPTION;
			int targetLoc=js_getint(ctx,argv[9],&error);
			if(error==1)return JS_EXCEPTION;
			int colorLoc=js_getint(ctx,argv[10],&error);
			if(error==1)return JS_EXCEPTION;
			int attenuationLoc=js_getint(ctx,argv[11],&error);
			if(error==1)return JS_EXCEPTION;
			_struct =(Light){
				type,
				enabled,
				position,
				target,
				color,
				attenuation,
				enabledLoc,
				typeLoc,
				positionLoc,
				targetLoc,
				colorLoc,
				attenuationLoc
			};
		}
		opaqueShadow * _structShadow=create_shadow_with_data(sizeof(Light));
		Light * _returnptr=((Light *)(_structShadow+1));
		_returnptr[0]=_struct;
		JSValue _return=JS_NewObjectClass(ctx,js_Light_class_id);
		JS_SetOpaque(_return,(void  *)_structShadow);
		local_memlock=(bool)false;
		return _return;
	}
	
	static JSValue js_CreateLight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		int type=js_getint(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 position=js_getVector3(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 target=js_getVector3(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		Color color=js_getColor(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		Shader shader=js_getShader(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		Light returnVal=CreateLight(type,position,target,color,shader);
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Light));
		Light * ptr2_ret=((Light *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Light_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_UpdateLightValues(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Shader shader=js_getShader(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Light light=js_getLight(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		UpdateLightValues(shader,light);
		return JS_UNDEFINED;
	}
	static const JSCFunctionListEntry jsrlights_funcs[]={
		JS_CFUNC_DEF("CreateLight",5,js_CreateLight),
		JS_CFUNC_DEF("UpdateLightValues",2,js_UpdateLightValues)
	};
	
	static int js_rlights_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsrlights_funcs);
		JS_SetModuleExportList(ctx,m,jsrlights_funcs,(int)listcount);
		js_declare_Light(ctx,m);
		JSValue Light_constr=JS_NewCFunction2(ctx,js_Light_constructor,(const char  *)"Light",(int)12,(JSCFunctionEnum)JS_CFUNC_constructor,(int)0);
		JS_SetModuleExport(ctx,m,(const char  *)"Light",Light_constr);
		JS_SetModuleExport(ctx,m,(const char  *)"LIGHT_DIRECTIONAL",JS_NewInt32(ctx,(int32_t)LIGHT_DIRECTIONAL));
		JS_SetModuleExport(ctx,m,(const char  *)"LIGHT_POINT",JS_NewInt32(ctx,(int32_t)LIGHT_POINT));
		JS_SetModuleExport(ctx,m,(const char  *)"MAX_LIGHTS",JS_NewInt32(ctx,(int32_t)MAX_LIGHTS));
		return 0;
	}
	
	JSModuleDef * js_init_module_rlights(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_rlights_init);
		if(!m)return NULL;
		size_t listcount=countof(jsrlights_funcs);
		JS_AddModuleExportList(ctx,m,jsrlights_funcs,(int)listcount);
		JS_AddModuleExport(ctx,m,(const char  *)"Light");
		JS_AddModuleExport(ctx,m,(const char  *)"LIGHT_DIRECTIONAL");
		JS_AddModuleExport(ctx,m,(const char  *)"LIGHT_POINT");
		JS_AddModuleExport(ctx,m,(const char  *)"MAX_LIGHTS");
		return m;
	}

#endif //JS_rlights_GUARD