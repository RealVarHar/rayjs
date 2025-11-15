#ifndef JS_rcamera_GUARD
	#define JS_rcamera_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <raylib.h>
	#include <rcamera.h>
	
	static Camera * js_getCamera_ptr(JSContext * ctx,JSValue src,bool * error,bool * isptr);
	
	static float js_getfloat(JSContext * ctx,JSValue src,bool * error);
	
	static bool js_getbool(JSContext * ctx,JSValue src,bool * error);
	
	static JSValue js_GetCameraForward(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=GetCameraForward(camera);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector3));
		Vector3 * ptr2_ret=((Vector3 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetCameraUp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=GetCameraUp(camera);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector3));
		Vector3 * ptr2_ret=((Vector3 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetCameraRight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=GetCameraRight(camera);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Vector3));
		Vector3 * ptr2_ret=((Vector3 *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Vector3_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_CameraMoveForward(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		float distance=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool moveInWorldPlane=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		CameraMoveForward(camera,distance,moveInWorldPlane);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraMoveUp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		float distance=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		CameraMoveUp(camera,distance);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraMoveRight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		float distance=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool moveInWorldPlane=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		CameraMoveRight(camera,distance,moveInWorldPlane);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraMoveToTarget(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		float delta=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		CameraMoveToTarget(camera,delta);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraYaw(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		float angle=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool rotateAroundTarget=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		CameraYaw(camera,angle,rotateAroundTarget);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraPitch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		float angle=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool lockView=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		bool rotateAroundTarget=js_getbool(ctx,argv[3],&error);
		if(error==1)return JS_EXCEPTION;
		bool rotateUp=js_getbool(ctx,argv[4],&error);
		if(error==1)return JS_EXCEPTION;
		CameraPitch(camera,angle,lockView,rotateAroundTarget,rotateUp);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraRoll(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		float angle=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		CameraRoll(camera,angle);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetCameraViewMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=GetCameraViewMatrix(camera);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Matrix));
		Matrix * ptr2_ret=((Matrix *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetCameraProjectionMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		bool camera_isptr=(bool)false;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error,&camera_isptr);
		if(error==1)return JS_EXCEPTION;
		float aspect=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=GetCameraProjectionMatrix(camera,aspect);
		if(camera_isptr==0){
			opaqueShadow * ptr_src=create_shadow_with_data(sizeof(Camera));
			Camera * ptr2_src=((Camera *)(ptr_src+1));
			ptr2_src[0]=camera[0];
			JSValue src=JS_NewObjectClass(ctx,js_Camera3D_class_id);
			JS_SetOpaque(src,(void  *)ptr_src);
			JS_SetPropertyUint32(ctx,argv[0],(uint32_t)0,src);
		}
		opaqueShadow * ptr_ret=create_shadow_with_data(sizeof(Matrix));
		Matrix * ptr2_ret=((Matrix *)(ptr_ret+1));
		ptr2_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,js_Matrix_class_id);
		JS_SetOpaque(ret,(void  *)ptr_ret);
		return ret;
	}
	static const JSCFunctionListEntry jsrcamera_funcs[]={
		JS_CFUNC_DEF("GetCameraForward",1,js_GetCameraForward),
		JS_CFUNC_DEF("GetCameraUp",1,js_GetCameraUp),
		JS_CFUNC_DEF("GetCameraRight",1,js_GetCameraRight),
		JS_CFUNC_DEF("CameraMoveForward",3,js_CameraMoveForward),
		JS_CFUNC_DEF("CameraMoveUp",2,js_CameraMoveUp),
		JS_CFUNC_DEF("CameraMoveRight",3,js_CameraMoveRight),
		JS_CFUNC_DEF("CameraMoveToTarget",2,js_CameraMoveToTarget),
		JS_CFUNC_DEF("CameraYaw",3,js_CameraYaw),
		JS_CFUNC_DEF("CameraPitch",5,js_CameraPitch),
		JS_CFUNC_DEF("CameraRoll",2,js_CameraRoll),
		JS_CFUNC_DEF("GetCameraViewMatrix",1,js_GetCameraViewMatrix),
		JS_CFUNC_DEF("GetCameraProjectionMatrix",2,js_GetCameraProjectionMatrix)
	};
	
	static int js_rcamera_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsrcamera_funcs);
		JS_SetModuleExportList(ctx,m,jsrcamera_funcs,(int)listcount);
		return 0;
	}
	
	JSModuleDef * js_init_module_rcamera(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_rcamera_init);
		if(!m)return NULL;
		size_t listcount=countof(jsrcamera_funcs);
		JS_AddModuleExportList(ctx,m,jsrcamera_funcs,(int)listcount);
		return m;
	}

#endif //JS_rcamera_GUARD