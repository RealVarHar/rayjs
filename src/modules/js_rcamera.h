#ifndef JS_js_rcamera_GUARD
	#define JS_js_rcamera_GUARD
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <rayjs_base.h>
	#include <config.h>
	#include <rayjs_generated.h>
	#include <rcamera.h>
	
	static JSValue js_GetCameraForward(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		Vector3 returnVal=GetCameraForward(camera);
		JS_SetOpaque(argv[0],(void *)camera);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetCameraUp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		Vector3 returnVal=GetCameraUp(camera);
		JS_SetOpaque(argv[0],(void *)camera);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetCameraRight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		Vector3 returnVal=GetCameraRight(camera);
		JS_SetOpaque(argv[0],(void *)camera);
		Vector3 * ptr_ret=(Vector3 *)js_malloc(ctx,sizeof(Vector3));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Vector3_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_CameraMoveForward(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		double double_distance;
		int err_distance=JS_ToFloat64(ctx,&double_distance,argv[1]);
		if(err_distance<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float distance=((float)double_distance);
		int js_moveInWorldPlane=JS_ToBool(ctx,argv[2]);
		if(js_moveInWorldPlane<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not a bool");
			return JS_EXCEPTION;
		}
		bool moveInWorldPlane=(bool)js_moveInWorldPlane;
		CameraMoveForward(camera,distance,moveInWorldPlane);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraMoveUp(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		double double_distance;
		int err_distance=JS_ToFloat64(ctx,&double_distance,argv[1]);
		if(err_distance<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float distance=((float)double_distance);
		CameraMoveUp(camera,distance);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraMoveRight(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		double double_distance;
		int err_distance=JS_ToFloat64(ctx,&double_distance,argv[1]);
		if(err_distance<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float distance=((float)double_distance);
		int js_moveInWorldPlane=JS_ToBool(ctx,argv[2]);
		if(js_moveInWorldPlane<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not a bool");
			return JS_EXCEPTION;
		}
		bool moveInWorldPlane=(bool)js_moveInWorldPlane;
		CameraMoveRight(camera,distance,moveInWorldPlane);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraMoveToTarget(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		double double_delta;
		int err_delta=JS_ToFloat64(ctx,&double_delta,argv[1]);
		if(err_delta<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float delta=((float)double_delta);
		CameraMoveToTarget(camera,delta);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraYaw(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		double double_angle;
		int err_angle=JS_ToFloat64(ctx,&double_angle,argv[1]);
		if(err_angle<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float angle=((float)double_angle);
		int js_rotateAroundTarget=JS_ToBool(ctx,argv[2]);
		if(js_rotateAroundTarget<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not a bool");
			return JS_EXCEPTION;
		}
		bool rotateAroundTarget=(bool)js_rotateAroundTarget;
		CameraYaw(camera,angle,rotateAroundTarget);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraPitch(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		double double_angle;
		int err_angle=JS_ToFloat64(ctx,&double_angle,argv[1]);
		if(err_angle<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float angle=((float)double_angle);
		int js_lockView=JS_ToBool(ctx,argv[2]);
		if(js_lockView<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[2] is not a bool");
			return JS_EXCEPTION;
		}
		bool lockView=(bool)js_lockView;
		int js_rotateAroundTarget=JS_ToBool(ctx,argv[3]);
		if(js_rotateAroundTarget<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[3] is not a bool");
			return JS_EXCEPTION;
		}
		bool rotateAroundTarget=(bool)js_rotateAroundTarget;
		int js_rotateUp=JS_ToBool(ctx,argv[4]);
		if(js_rotateUp<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[4] is not a bool");
			return JS_EXCEPTION;
		}
		bool rotateUp=(bool)js_rotateUp;
		CameraPitch(camera,angle,lockView,rotateAroundTarget,rotateUp);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_CameraRoll(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		double double_angle;
		int err_angle=JS_ToFloat64(ctx,&double_angle,argv[1]);
		if(err_angle<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float angle=((float)double_angle);
		CameraRoll(camera,angle);
		JS_SetOpaque(argv[0],(void *)camera);
		return JS_UNDEFINED;
	}
	
	static JSValue js_GetCameraViewMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		Matrix returnVal=GetCameraViewMatrix(camera);
		JS_SetOpaque(argv[0],(void *)camera);
		Matrix * ptr_ret=(Matrix *)js_malloc(ctx,sizeof(Matrix));
		ptr_ret[0]=returnVal;
		JSValue ret=JS_NewObjectClass(ctx,(int)js_Matrix_class_id);
		JS_SetOpaque(ret,(void *)ptr_ret);
		return ret;
	}
	
	static JSValue js_GetCameraProjectionMatrix(JSContext * ctx,JSValue this_val,int argc,JSValue * argv){
		Camera * camera=(Camera *)JS_GetOpaque(argv[0],js_Camera3D_class_id);
		if(camera==NULL){
			JS_ThrowTypeError(ctx,(const char *)"argv[0] does not match type Camera");
			return JS_EXCEPTION;
		}
		double double_aspect;
		int err_aspect=JS_ToFloat64(ctx,&double_aspect,argv[1]);
		if(err_aspect<0){
			JS_ThrowTypeError(ctx,(const char *)"argv[1] is not numeric");
			return JS_EXCEPTION;
		}
		float aspect=((float)double_aspect);
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
	
	static int js_js_rcamera_init(JSContext * ctx,JSModuleDef * m){
		size_t listcount=countof(jsrcamera_funcs);
		JS_SetModuleExportList(ctx,m,jsrcamera_funcs,(int)listcount);
		return 0;
	}
	
	JSModuleDef * js_init_module_js_rcamera(JSContext * ctx,const char * module_name){
		JSModuleDef * m=JS_NewCModule(ctx,module_name,js_js_rcamera_init);
		if(!m){
			return NULL;
		}
		size_t listcount=countof(jsrcamera_funcs);
		JS_AddModuleExportList(ctx,m,jsrcamera_funcs,(int)listcount);
		return m;
	}

#endif //JS_js_rcamera_GUARD