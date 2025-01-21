#ifndef JS_js_rcamera_GUARD
#define JS_js_rcamera_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <quickjs.h>
#include <rayjs_base.h>
#include <rcamera.h>
#include <raylib.h>


static JSValue js_getCameraForward(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    Vector3 returnVal = GetCameraForward(camera);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_getCameraUp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    Vector3 returnVal = GetCameraUp(camera);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_getCameraRight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    Vector3 returnVal = GetCameraRight(camera);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_cameraMoveForward(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    double double_distance;
    int err_distance = JS_ToFloat64(ctx, &double_distance, argv[1]);
    if(err_distance<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float distance = (float)double_distance;
    int js_moveInWorldPlane = JS_ToBool(ctx, argv[2]);
    if(js_moveInWorldPlane<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not a bool");
        return JS_EXCEPTION;
    }
    bool moveInWorldPlane = js_moveInWorldPlane;
    CameraMoveForward(camera, distance, moveInWorldPlane);
    return JS_UNDEFINED;
}

static JSValue js_cameraMoveUp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    double double_distance;
    int err_distance = JS_ToFloat64(ctx, &double_distance, argv[1]);
    if(err_distance<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float distance = (float)double_distance;
    CameraMoveUp(camera, distance);
    return JS_UNDEFINED;
}

static JSValue js_cameraMoveRight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    double double_distance;
    int err_distance = JS_ToFloat64(ctx, &double_distance, argv[1]);
    if(err_distance<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float distance = (float)double_distance;
    int js_moveInWorldPlane = JS_ToBool(ctx, argv[2]);
    if(js_moveInWorldPlane<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not a bool");
        return JS_EXCEPTION;
    }
    bool moveInWorldPlane = js_moveInWorldPlane;
    CameraMoveRight(camera, distance, moveInWorldPlane);
    return JS_UNDEFINED;
}

static JSValue js_cameraMoveToTarget(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    double double_delta;
    int err_delta = JS_ToFloat64(ctx, &double_delta, argv[1]);
    if(err_delta<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float delta = (float)double_delta;
    CameraMoveToTarget(camera, delta);
    return JS_UNDEFINED;
}

static JSValue js_cameraYaw(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    double double_angle;
    int err_angle = JS_ToFloat64(ctx, &double_angle, argv[1]);
    if(err_angle<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float angle = (float)double_angle;
    int js_rotateAroundTarget = JS_ToBool(ctx, argv[2]);
    if(js_rotateAroundTarget<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not a bool");
        return JS_EXCEPTION;
    }
    bool rotateAroundTarget = js_rotateAroundTarget;
    CameraYaw(camera, angle, rotateAroundTarget);
    return JS_UNDEFINED;
}

static JSValue js_cameraPitch(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    double double_angle;
    int err_angle = JS_ToFloat64(ctx, &double_angle, argv[1]);
    if(err_angle<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float angle = (float)double_angle;
    int js_lockView = JS_ToBool(ctx, argv[2]);
    if(js_lockView<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not a bool");
        return JS_EXCEPTION;
    }
    bool lockView = js_lockView;
    int js_rotateAroundTarget = JS_ToBool(ctx, argv[3]);
    if(js_rotateAroundTarget<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not a bool");
        return JS_EXCEPTION;
    }
    bool rotateAroundTarget = js_rotateAroundTarget;
    int js_rotateUp = JS_ToBool(ctx, argv[4]);
    if(js_rotateUp<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not a bool");
        return JS_EXCEPTION;
    }
    bool rotateUp = js_rotateUp;
    CameraPitch(camera, angle, lockView, rotateAroundTarget, rotateUp);
    return JS_UNDEFINED;
}

static JSValue js_cameraRoll(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    double double_angle;
    int err_angle = JS_ToFloat64(ctx, &double_angle, argv[1]);
    if(err_angle<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float angle = (float)double_angle;
    CameraRoll(camera, angle);
    return JS_UNDEFINED;
}

static JSValue js_getCameraViewMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    Matrix returnVal = GetCameraViewMatrix(camera);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_getCameraProjectionMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    double double_aspect;
    int err_aspect = JS_ToFloat64(ctx, &double_aspect, argv[1]);
    if(err_aspect<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float aspect = (float)double_aspect;
    Matrix returnVal = GetCameraProjectionMatrix(camera, aspect);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static const JSCFunctionListEntry js_js_rcamera_funcs[] = {
    JS_CFUNC_DEF("getCameraForward",1,js_getCameraForward),
    JS_CFUNC_DEF("getCameraUp",1,js_getCameraUp),
    JS_CFUNC_DEF("getCameraRight",1,js_getCameraRight),
    JS_CFUNC_DEF("cameraMoveForward",3,js_cameraMoveForward),
    JS_CFUNC_DEF("cameraMoveUp",2,js_cameraMoveUp),
    JS_CFUNC_DEF("cameraMoveRight",3,js_cameraMoveRight),
    JS_CFUNC_DEF("cameraMoveToTarget",2,js_cameraMoveToTarget),
    JS_CFUNC_DEF("cameraYaw",3,js_cameraYaw),
    JS_CFUNC_DEF("cameraPitch",5,js_cameraPitch),
    JS_CFUNC_DEF("cameraRoll",2,js_cameraRoll),
    JS_CFUNC_DEF("getCameraViewMatrix",1,js_getCameraViewMatrix),
    JS_CFUNC_DEF("getCameraProjectionMatrix",2,js_getCameraProjectionMatrix),
};

static int js_js_rcamera_init(JSContext * ctx, JSModuleDef * m) {
    JS_SetModuleExportList(ctx, m,js_js_rcamera_funcs,countof(js_js_rcamera_funcs));
    return 0;
}

JSModuleDef * js_init_module_js_rcamera(JSContext * ctx, const char * module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_js_rcamera_init);
    if(!m) return NULL;
    JS_AddModuleExportList(ctx, m, js_js_rcamera_funcs, countof(js_js_rcamera_funcs));
    return m;
}

#endif // JS_js_rcamera_GUARD
