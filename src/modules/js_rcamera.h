#ifndef JS_rcamera_GUARD
	#define JS_rcamera_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <raylib.h>
	#include <rcamera.h>
	
	static Camera * js_getCamera_ptr(JSContext * ctx,JSValue src,bool * error);
	
	static float js_getfloat(JSContext * ctx,JSValue src,bool * error);
	
	static bool js_getbool(JSContext * ctx,JSValue src,bool * error);
	
	static JSValue js_GetCameraForward(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=GetCameraForward(camera);
		JS_SetOpaque(argv[0],(void *)camera);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetCameraUp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=GetCameraUp(camera);
		JS_SetOpaque(argv[0],(void *)camera);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetCameraRight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Vector3 returnVal=GetCameraRight(camera);
		JS_SetOpaque(argv[0],(void *)camera);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_CameraMoveForward(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float distance=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool moveInWorldPlane=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		CameraMoveForward(camera,distance,moveInWorldPlane);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraMoveUp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float distance=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		CameraMoveUp(camera,distance);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraMoveRight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float distance=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool moveInWorldPlane=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		CameraMoveRight(camera,distance,moveInWorldPlane);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraMoveToTarget(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float delta=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		CameraMoveToTarget(camera,delta);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraYaw(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float angle=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		bool rotateAroundTarget=js_getbool(ctx,argv[2],&error);
		if(error==1)return JS_EXCEPTION;
		CameraYaw(camera,angle,rotateAroundTarget);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraPitch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
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
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraRoll(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float angle=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		CameraRoll(camera,angle);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetCameraViewMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=GetCameraViewMatrix(camera);
		JS_SetOpaque(argv[0],(void *)camera);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetCameraProjectionMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		bool error=(bool)0;
		Camera * camera=js_getCamera_ptr(ctx,argv[0],&error);
		if(error==1)return JS_EXCEPTION;
		float aspect=js_getfloat(ctx,argv[1],&error);
		if(error==1)return JS_EXCEPTION;
		Matrix returnVal=GetCameraProjectionMatrix(camera,aspect);
		JS_SetOpaque(argv[0],(void *)camera);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
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