#ifndef JS_js_raylib_GUARD
#define JS_js_raylib_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <quickjs.h>
#include <rayjs_base.h>
#include <raylib.h>

static JSClassID js_Vector2_class_id;
static JSClassID js_Vector3_class_id;
static JSClassID js_Vector4_class_id;
static JSClassID js_Matrix_class_id;
static JSClassID js_Color_class_id;
static JSClassID js_Rectangle_class_id;
static JSClassID js_Image_class_id;
static JSClassID js_Texture_class_id;
static JSClassID js_RenderTexture_class_id;
static JSClassID js_NPatchInfo_class_id;
static JSClassID js_GlyphInfo_class_id;
static JSClassID js_Font_class_id;
static JSClassID js_Camera3D_class_id;
static JSClassID js_Camera2D_class_id;
static JSClassID js_Mesh_class_id;
static JSClassID js_Shader_class_id;
static JSClassID js_MaterialMap_class_id;
static JSClassID js_Material_class_id;
static JSClassID js_Transform_class_id;
static JSClassID js_BoneInfo_class_id;
static JSClassID js_Model_class_id;
static JSClassID js_ModelAnimation_class_id;
static JSClassID js_Ray_class_id;
static JSClassID js_RayCollision_class_id;
static JSClassID js_BoundingBox_class_id;
static JSClassID js_Wave_class_id;
static JSClassID js_rAudioBuffer_class_id;
static JSClassID js_rAudioProcessor_class_id;
static JSClassID js_AudioStream_class_id;
static JSClassID js_Sound_class_id;
static JSClassID js_Music_class_id;
static JSClassID js_VrDeviceInfo_class_id;
static JSClassID js_VrStereoConfig_class_id;
static JSClassID js_FilePathList_class_id;
static JSClassID js_AutomationEvent_class_id;
static JSClassID js_AutomationEventList_class_id;
static JSClassID js_Vector2_class_id;
static JSClassID js_Vector3_class_id;
static JSClassID js_Vector4_class_id;
static JSClassID js_Matrix_class_id;
static JSClassID js_Color_class_id;
static JSClassID js_Rectangle_class_id;
static JSClassID js_Image_class_id;
static JSClassID js_Texture_class_id;
static JSClassID js_RenderTexture_class_id;
static JSClassID js_NPatchInfo_class_id;
static JSClassID js_GlyphInfo_class_id;
static JSClassID js_Font_class_id;
static JSClassID js_Camera3D_class_id;
static JSClassID js_Camera2D_class_id;
static JSClassID js_Mesh_class_id;
static JSClassID js_Shader_class_id;
static JSClassID js_MaterialMap_class_id;
static JSClassID js_Material_class_id;
static JSClassID js_Transform_class_id;
static JSClassID js_BoneInfo_class_id;
static JSClassID js_Model_class_id;
static JSClassID js_ModelAnimation_class_id;
static JSClassID js_Ray_class_id;
static JSClassID js_RayCollision_class_id;
static JSClassID js_BoundingBox_class_id;
static JSClassID js_Wave_class_id;
static JSClassID js_rAudioBuffer_class_id;
static JSClassID js_rAudioProcessor_class_id;
static JSClassID js_AudioStream_class_id;
static JSClassID js_Sound_class_id;
static JSClassID js_Music_class_id;
static JSClassID js_VrDeviceInfo_class_id;
static JSClassID js_VrStereoConfig_class_id;
static JSClassID js_FilePathList_class_id;
static JSClassID js_AutomationEvent_class_id;
static JSClassID js_AutomationEventList_class_id;

static void js_Vector2_finalizer(JSRuntime * rt, JSValue val) {
    Vector2* ptr = JS_GetOpaque(val, js_Vector2_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Vector2_get_x(JSContext* ctx, JSValue this_val) {
    Vector2* ptr = JS_GetOpaque2(ctx, this_val, js_Vector2_class_id);
    float x = ptr->x;
    JSValue ret = JS_NewFloat64(ctx, (double)x);
    return ret;
}

static JSValue js_Vector2_set_x(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector2* ptr = JS_GetOpaque2(ctx, this_val, js_Vector2_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->x = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector2_get_y(JSContext* ctx, JSValue this_val) {
    Vector2* ptr = JS_GetOpaque2(ctx, this_val, js_Vector2_class_id);
    float y = ptr->y;
    JSValue ret = JS_NewFloat64(ctx, (double)y);
    return ret;
}

static JSValue js_Vector2_set_y(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector2* ptr = JS_GetOpaque2(ctx, this_val, js_Vector2_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->y = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Vector2_proto_funcs[] = {
    JS_CGETSET_DEF("x",js_Vector2_get_x,js_Vector2_set_x),
    JS_CGETSET_DEF("y",js_Vector2_get_y,js_Vector2_set_y),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Vector2", JS_PROP_CONFIGURABLE),
};

static int js_declare_Vector2(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Vector2_class_id);
    JSClassDef js_Vector2_def = { .class_name = "Vector2", .finalizer = js_Vector2_finalizer };
    JS_NewClass(rt, js_Vector2_class_id, &js_Vector2_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Vector2_proto_funcs, countof(js_Vector2_proto_funcs));
    JS_SetClassProto(ctx, js_Vector2_class_id, proto);
    return 0;
}

static void js_Vector3_finalizer(JSRuntime * rt, JSValue val) {
    Vector3* ptr = JS_GetOpaque(val, js_Vector3_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Vector3_get_x(JSContext* ctx, JSValue this_val) {
    Vector3* ptr = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    float x = ptr->x;
    JSValue ret = JS_NewFloat64(ctx, (double)x);
    return ret;
}

static JSValue js_Vector3_set_x(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector3* ptr = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->x = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector3_get_y(JSContext* ctx, JSValue this_val) {
    Vector3* ptr = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    float y = ptr->y;
    JSValue ret = JS_NewFloat64(ctx, (double)y);
    return ret;
}

static JSValue js_Vector3_set_y(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector3* ptr = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->y = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector3_get_z(JSContext* ctx, JSValue this_val) {
    Vector3* ptr = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    float z = ptr->z;
    JSValue ret = JS_NewFloat64(ctx, (double)z);
    return ret;
}

static JSValue js_Vector3_set_z(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector3* ptr = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->z = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Vector3_proto_funcs[] = {
    JS_CGETSET_DEF("x",js_Vector3_get_x,js_Vector3_set_x),
    JS_CGETSET_DEF("y",js_Vector3_get_y,js_Vector3_set_y),
    JS_CGETSET_DEF("z",js_Vector3_get_z,js_Vector3_set_z),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Vector3", JS_PROP_CONFIGURABLE),
};

static int js_declare_Vector3(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Vector3_class_id);
    JSClassDef js_Vector3_def = { .class_name = "Vector3", .finalizer = js_Vector3_finalizer };
    JS_NewClass(rt, js_Vector3_class_id, &js_Vector3_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Vector3_proto_funcs, countof(js_Vector3_proto_funcs));
    JS_SetClassProto(ctx, js_Vector3_class_id, proto);
    return 0;
}

static void js_Vector4_finalizer(JSRuntime * rt, JSValue val) {
    Vector4* ptr = JS_GetOpaque(val, js_Vector4_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Vector4_get_x(JSContext* ctx, JSValue this_val) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    float x = ptr->x;
    JSValue ret = JS_NewFloat64(ctx, (double)x);
    return ret;
}

static JSValue js_Vector4_set_x(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->x = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector4_get_y(JSContext* ctx, JSValue this_val) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    float y = ptr->y;
    JSValue ret = JS_NewFloat64(ctx, (double)y);
    return ret;
}

static JSValue js_Vector4_set_y(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->y = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector4_get_z(JSContext* ctx, JSValue this_val) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    float z = ptr->z;
    JSValue ret = JS_NewFloat64(ctx, (double)z);
    return ret;
}

static JSValue js_Vector4_set_z(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->z = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector4_get_w(JSContext* ctx, JSValue this_val) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    float w = ptr->w;
    JSValue ret = JS_NewFloat64(ctx, (double)w);
    return ret;
}

static JSValue js_Vector4_set_w(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->w = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Vector4_proto_funcs[] = {
    JS_CGETSET_DEF("x",js_Vector4_get_x,js_Vector4_set_x),
    JS_CGETSET_DEF("y",js_Vector4_get_y,js_Vector4_set_y),
    JS_CGETSET_DEF("z",js_Vector4_get_z,js_Vector4_set_z),
    JS_CGETSET_DEF("w",js_Vector4_get_w,js_Vector4_set_w),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Vector4", JS_PROP_CONFIGURABLE),
};

static int js_declare_Vector4(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Vector4_class_id);
    JSClassDef js_Vector4_def = { .class_name = "Vector4", .finalizer = js_Vector4_finalizer };
    JS_NewClass(rt, js_Vector4_class_id, &js_Vector4_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Vector4_proto_funcs, countof(js_Vector4_proto_funcs));
    JS_SetClassProto(ctx, js_Vector4_class_id, proto);
    return 0;
}

static void js_Matrix_finalizer(JSRuntime * rt, JSValue val) {
    Matrix* ptr = JS_GetOpaque(val, js_Matrix_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_Matrix_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Matrix", JS_PROP_CONFIGURABLE),
};

static int js_declare_Matrix(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Matrix_class_id);
    JSClassDef js_Matrix_def = { .class_name = "Matrix", .finalizer = js_Matrix_finalizer };
    JS_NewClass(rt, js_Matrix_class_id, &js_Matrix_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Matrix_proto_funcs, countof(js_Matrix_proto_funcs));
    JS_SetClassProto(ctx, js_Matrix_class_id, proto);
    return 0;
}

static void js_Color_finalizer(JSRuntime * rt, JSValue val) {
    Color* ptr = JS_GetOpaque(val, js_Color_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Color_get_r(JSContext* ctx, JSValue this_val) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    unsigned char r = ptr->r;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)r);
    return ret;
}

static JSValue js_Color_set_r(JSContext* ctx, JSValue this_val, JSValue v) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    uint32_t long_value;
    int err_value = JS_ToUint32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    unsigned char value = (unsigned char)long_value;
    ptr->r = value;
    return JS_UNDEFINED;
}

static JSValue js_Color_get_g(JSContext* ctx, JSValue this_val) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    unsigned char g = ptr->g;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)g);
    return ret;
}

static JSValue js_Color_set_g(JSContext* ctx, JSValue this_val, JSValue v) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    uint32_t long_value;
    int err_value = JS_ToUint32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    unsigned char value = (unsigned char)long_value;
    ptr->g = value;
    return JS_UNDEFINED;
}

static JSValue js_Color_get_b(JSContext* ctx, JSValue this_val) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    unsigned char b = ptr->b;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)b);
    return ret;
}

static JSValue js_Color_set_b(JSContext* ctx, JSValue this_val, JSValue v) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    uint32_t long_value;
    int err_value = JS_ToUint32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    unsigned char value = (unsigned char)long_value;
    ptr->b = value;
    return JS_UNDEFINED;
}

static JSValue js_Color_get_a(JSContext* ctx, JSValue this_val) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    unsigned char a = ptr->a;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)a);
    return ret;
}

static JSValue js_Color_set_a(JSContext* ctx, JSValue this_val, JSValue v) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    uint32_t long_value;
    int err_value = JS_ToUint32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    unsigned char value = (unsigned char)long_value;
    ptr->a = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Color_proto_funcs[] = {
    JS_CGETSET_DEF("r",js_Color_get_r,js_Color_set_r),
    JS_CGETSET_DEF("g",js_Color_get_g,js_Color_set_g),
    JS_CGETSET_DEF("b",js_Color_get_b,js_Color_set_b),
    JS_CGETSET_DEF("a",js_Color_get_a,js_Color_set_a),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Color", JS_PROP_CONFIGURABLE),
};

static int js_declare_Color(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Color_class_id);
    JSClassDef js_Color_def = { .class_name = "Color", .finalizer = js_Color_finalizer };
    JS_NewClass(rt, js_Color_class_id, &js_Color_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Color_proto_funcs, countof(js_Color_proto_funcs));
    JS_SetClassProto(ctx, js_Color_class_id, proto);
    return 0;
}

static void js_Rectangle_finalizer(JSRuntime * rt, JSValue val) {
    Rectangle* ptr = JS_GetOpaque(val, js_Rectangle_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Rectangle_get_x(JSContext* ctx, JSValue this_val) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    float x = ptr->x;
    JSValue ret = JS_NewFloat64(ctx, (double)x);
    return ret;
}

static JSValue js_Rectangle_set_x(JSContext* ctx, JSValue this_val, JSValue v) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->x = value;
    return JS_UNDEFINED;
}

static JSValue js_Rectangle_get_y(JSContext* ctx, JSValue this_val) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    float y = ptr->y;
    JSValue ret = JS_NewFloat64(ctx, (double)y);
    return ret;
}

static JSValue js_Rectangle_set_y(JSContext* ctx, JSValue this_val, JSValue v) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->y = value;
    return JS_UNDEFINED;
}

static JSValue js_Rectangle_get_width(JSContext* ctx, JSValue this_val) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    float width = ptr->width;
    JSValue ret = JS_NewFloat64(ctx, (double)width);
    return ret;
}

static JSValue js_Rectangle_set_width(JSContext* ctx, JSValue this_val, JSValue v) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->width = value;
    return JS_UNDEFINED;
}

static JSValue js_Rectangle_get_height(JSContext* ctx, JSValue this_val) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    float height = ptr->height;
    JSValue ret = JS_NewFloat64(ctx, (double)height);
    return ret;
}

static JSValue js_Rectangle_set_height(JSContext* ctx, JSValue this_val, JSValue v) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->height = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Rectangle_proto_funcs[] = {
    JS_CGETSET_DEF("x",js_Rectangle_get_x,js_Rectangle_set_x),
    JS_CGETSET_DEF("y",js_Rectangle_get_y,js_Rectangle_set_y),
    JS_CGETSET_DEF("width",js_Rectangle_get_width,js_Rectangle_set_width),
    JS_CGETSET_DEF("height",js_Rectangle_get_height,js_Rectangle_set_height),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Rectangle", JS_PROP_CONFIGURABLE),
};

static int js_declare_Rectangle(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Rectangle_class_id);
    JSClassDef js_Rectangle_def = { .class_name = "Rectangle", .finalizer = js_Rectangle_finalizer };
    JS_NewClass(rt, js_Rectangle_class_id, &js_Rectangle_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Rectangle_proto_funcs, countof(js_Rectangle_proto_funcs));
    JS_SetClassProto(ctx, js_Rectangle_class_id, proto);
    return 0;
}

static void js_Image_finalizer(JSRuntime * rt, JSValue val) {
    Image* ptr = JS_GetOpaque(val, js_Image_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Image_set_data(JSContext* ctx, JSValue this_val, JSValue v) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    void * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        void * js_value = (void *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (void *)jsc_malloc(ctx, size_value * sizeof(void *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JS_ThrowTypeError(ctx, "v does not match type void *");
        return JS_EXCEPTION;
    }
    if(ptr->data!=NULL) {
        js_free(ctx, ptr->data);
    }
    ptr->data = value;
    return JS_UNDEFINED;
}

static JSValue js_Image_get_width(JSContext* ctx, JSValue this_val) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int width = ptr->width;
    JSValue ret = JS_NewInt32(ctx, (long)width);
    return ret;
}

static JSValue js_Image_set_width(JSContext* ctx, JSValue this_val, JSValue v) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->width = value;
    return JS_UNDEFINED;
}

static JSValue js_Image_get_height(JSContext* ctx, JSValue this_val) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int height = ptr->height;
    JSValue ret = JS_NewInt32(ctx, (long)height);
    return ret;
}

static JSValue js_Image_set_height(JSContext* ctx, JSValue this_val, JSValue v) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->height = value;
    return JS_UNDEFINED;
}

static JSValue js_Image_get_mipmaps(JSContext* ctx, JSValue this_val) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int mipmaps = ptr->mipmaps;
    JSValue ret = JS_NewInt32(ctx, (long)mipmaps);
    return ret;
}

static JSValue js_Image_set_mipmaps(JSContext* ctx, JSValue this_val, JSValue v) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->mipmaps = value;
    return JS_UNDEFINED;
}

static JSValue js_Image_get_format(JSContext* ctx, JSValue this_val) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int format = ptr->format;
    JSValue ret = JS_NewInt32(ctx, (long)format);
    return ret;
}

static JSValue js_Image_set_format(JSContext* ctx, JSValue this_val, JSValue v) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->format = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Image_proto_funcs[] = {
    JS_CGETSET_DEF("data",NULL,js_Image_set_data),
    JS_CGETSET_DEF("width",js_Image_get_width,js_Image_set_width),
    JS_CGETSET_DEF("height",js_Image_get_height,js_Image_set_height),
    JS_CGETSET_DEF("mipmaps",js_Image_get_mipmaps,js_Image_set_mipmaps),
    JS_CGETSET_DEF("format",js_Image_get_format,js_Image_set_format),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Image", JS_PROP_CONFIGURABLE),
};

static int js_declare_Image(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Image_class_id);
    JSClassDef js_Image_def = { .class_name = "Image", .finalizer = js_Image_finalizer };
    JS_NewClass(rt, js_Image_class_id, &js_Image_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Image_proto_funcs, countof(js_Image_proto_funcs));
    JS_SetClassProto(ctx, js_Image_class_id, proto);
    return 0;
}

static void js_Texture_finalizer(JSRuntime * rt, JSValue val) {
    Texture* ptr = JS_GetOpaque(val, js_Texture_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Texture_get_width(JSContext* ctx, JSValue this_val) {
    Texture* ptr = JS_GetOpaque2(ctx, this_val, js_Texture_class_id);
    int width = ptr->width;
    JSValue ret = JS_NewInt32(ctx, (long)width);
    return ret;
}

static JSValue js_Texture_get_height(JSContext* ctx, JSValue this_val) {
    Texture* ptr = JS_GetOpaque2(ctx, this_val, js_Texture_class_id);
    int height = ptr->height;
    JSValue ret = JS_NewInt32(ctx, (long)height);
    return ret;
}

static JSValue js_Texture_get_mipmaps(JSContext* ctx, JSValue this_val) {
    Texture* ptr = JS_GetOpaque2(ctx, this_val, js_Texture_class_id);
    int mipmaps = ptr->mipmaps;
    JSValue ret = JS_NewInt32(ctx, (long)mipmaps);
    return ret;
}

static JSValue js_Texture_get_format(JSContext* ctx, JSValue this_val) {
    Texture* ptr = JS_GetOpaque2(ctx, this_val, js_Texture_class_id);
    int format = ptr->format;
    JSValue ret = JS_NewInt32(ctx, (long)format);
    return ret;
}

static const JSCFunctionListEntry js_Texture_proto_funcs[] = {
    JS_CGETSET_DEF("width",js_Texture_get_width,NULL),
    JS_CGETSET_DEF("height",js_Texture_get_height,NULL),
    JS_CGETSET_DEF("mipmaps",js_Texture_get_mipmaps,NULL),
    JS_CGETSET_DEF("format",js_Texture_get_format,NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Texture", JS_PROP_CONFIGURABLE),
};

static int js_declare_Texture(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Texture_class_id);
    JSClassDef js_Texture_def = { .class_name = "Texture", .finalizer = js_Texture_finalizer };
    JS_NewClass(rt, js_Texture_class_id, &js_Texture_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Texture_proto_funcs, countof(js_Texture_proto_funcs));
    JS_SetClassProto(ctx, js_Texture_class_id, proto);
    return 0;
}

static void js_RenderTexture_finalizer(JSRuntime * rt, JSValue val) {
    RenderTexture* ptr = JS_GetOpaque(val, js_RenderTexture_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_RenderTexture_get_id(JSContext* ctx, JSValue this_val) {
    RenderTexture* ptr = JS_GetOpaque2(ctx, this_val, js_RenderTexture_class_id);
    unsigned int id = ptr->id;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)id);
    return ret;
}

static JSValue js_RenderTexture_get_texture(JSContext* ctx, JSValue this_val) {
    RenderTexture* ptr = JS_GetOpaque2(ctx, this_val, js_RenderTexture_class_id);
    Texture texture = ptr->texture;
    Texture* ptr_ret = (Texture*)js_malloc(ctx, sizeof(Texture));
    *ptr_ret = texture;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_RenderTexture_get_depth(JSContext* ctx, JSValue this_val) {
    RenderTexture* ptr = JS_GetOpaque2(ctx, this_val, js_RenderTexture_class_id);
    Texture depth = ptr->depth;
    Texture* ptr_ret = (Texture*)js_malloc(ctx, sizeof(Texture));
    *ptr_ret = depth;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static const JSCFunctionListEntry js_RenderTexture_proto_funcs[] = {
    JS_CGETSET_DEF("id",js_RenderTexture_get_id,NULL),
    JS_CGETSET_DEF("texture",js_RenderTexture_get_texture,NULL),
    JS_CGETSET_DEF("depth",js_RenderTexture_get_depth,NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","RenderTexture", JS_PROP_CONFIGURABLE),
};

static int js_declare_RenderTexture(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_RenderTexture_class_id);
    JSClassDef js_RenderTexture_def = { .class_name = "RenderTexture", .finalizer = js_RenderTexture_finalizer };
    JS_NewClass(rt, js_RenderTexture_class_id, &js_RenderTexture_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_RenderTexture_proto_funcs, countof(js_RenderTexture_proto_funcs));
    JS_SetClassProto(ctx, js_RenderTexture_class_id, proto);
    return 0;
}

static void js_NPatchInfo_finalizer(JSRuntime * rt, JSValue val) {
    NPatchInfo* ptr = JS_GetOpaque(val, js_NPatchInfo_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_NPatchInfo_get_source(JSContext* ctx, JSValue this_val) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    Rectangle source = ptr->source;
    Rectangle* ptr_ret = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *ptr_ret = source;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_NPatchInfo_set_source(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    Rectangle* ptr_value = (Rectangle*)JS_GetOpaque(v, js_Rectangle_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle value = *ptr_value;
    ptr->source = value;
    return JS_UNDEFINED;
}

static JSValue js_NPatchInfo_get_left(JSContext* ctx, JSValue this_val) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int left = ptr->left;
    JSValue ret = JS_NewInt32(ctx, (long)left);
    return ret;
}

static JSValue js_NPatchInfo_set_left(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->left = value;
    return JS_UNDEFINED;
}

static JSValue js_NPatchInfo_get_top(JSContext* ctx, JSValue this_val) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int top = ptr->top;
    JSValue ret = JS_NewInt32(ctx, (long)top);
    return ret;
}

static JSValue js_NPatchInfo_set_top(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->top = value;
    return JS_UNDEFINED;
}

static JSValue js_NPatchInfo_get_right(JSContext* ctx, JSValue this_val) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int right = ptr->right;
    JSValue ret = JS_NewInt32(ctx, (long)right);
    return ret;
}

static JSValue js_NPatchInfo_set_right(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->right = value;
    return JS_UNDEFINED;
}

static JSValue js_NPatchInfo_get_bottom(JSContext* ctx, JSValue this_val) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int bottom = ptr->bottom;
    JSValue ret = JS_NewInt32(ctx, (long)bottom);
    return ret;
}

static JSValue js_NPatchInfo_set_bottom(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->bottom = value;
    return JS_UNDEFINED;
}

static JSValue js_NPatchInfo_get_layout(JSContext* ctx, JSValue this_val) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int layout = ptr->layout;
    JSValue ret = JS_NewInt32(ctx, (long)layout);
    return ret;
}

static JSValue js_NPatchInfo_set_layout(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->layout = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_NPatchInfo_proto_funcs[] = {
    JS_CGETSET_DEF("source",js_NPatchInfo_get_source,js_NPatchInfo_set_source),
    JS_CGETSET_DEF("left",js_NPatchInfo_get_left,js_NPatchInfo_set_left),
    JS_CGETSET_DEF("top",js_NPatchInfo_get_top,js_NPatchInfo_set_top),
    JS_CGETSET_DEF("right",js_NPatchInfo_get_right,js_NPatchInfo_set_right),
    JS_CGETSET_DEF("bottom",js_NPatchInfo_get_bottom,js_NPatchInfo_set_bottom),
    JS_CGETSET_DEF("layout",js_NPatchInfo_get_layout,js_NPatchInfo_set_layout),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","NPatchInfo", JS_PROP_CONFIGURABLE),
};

static int js_declare_NPatchInfo(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_NPatchInfo_class_id);
    JSClassDef js_NPatchInfo_def = { .class_name = "NPatchInfo", .finalizer = js_NPatchInfo_finalizer };
    JS_NewClass(rt, js_NPatchInfo_class_id, &js_NPatchInfo_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_NPatchInfo_proto_funcs, countof(js_NPatchInfo_proto_funcs));
    JS_SetClassProto(ctx, js_NPatchInfo_class_id, proto);
    return 0;
}

static void js_GlyphInfo_finalizer(JSRuntime * rt, JSValue val) {
    GlyphInfo* ptr = JS_GetOpaque(val, js_GlyphInfo_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_GlyphInfo_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","GlyphInfo", JS_PROP_CONFIGURABLE),
};

static int js_declare_GlyphInfo(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_GlyphInfo_class_id);
    JSClassDef js_GlyphInfo_def = { .class_name = "GlyphInfo", .finalizer = js_GlyphInfo_finalizer };
    JS_NewClass(rt, js_GlyphInfo_class_id, &js_GlyphInfo_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_GlyphInfo_proto_funcs, countof(js_GlyphInfo_proto_funcs));
    JS_SetClassProto(ctx, js_GlyphInfo_class_id, proto);
    return 0;
}

static void js_Font_finalizer(JSRuntime * rt, JSValue val) {
    Font* ptr = JS_GetOpaque(val, js_Font_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Font_get_baseSize(JSContext* ctx, JSValue this_val) {
    Font* ptr = JS_GetOpaque2(ctx, this_val, js_Font_class_id);
    int baseSize = ptr->baseSize;
    JSValue ret = JS_NewInt32(ctx, (long)baseSize);
    return ret;
}

static JSValue js_Font_get_glyphCount(JSContext* ctx, JSValue this_val) {
    Font* ptr = JS_GetOpaque2(ctx, this_val, js_Font_class_id);
    int glyphCount = ptr->glyphCount;
    JSValue ret = JS_NewInt32(ctx, (long)glyphCount);
    return ret;
}

static JSValue js_Font_get_glyphPadding(JSContext* ctx, JSValue this_val) {
    Font* ptr = JS_GetOpaque2(ctx, this_val, js_Font_class_id);
    int glyphPadding = ptr->glyphPadding;
    JSValue ret = JS_NewInt32(ctx, (long)glyphPadding);
    return ret;
}

static JSValue js_Font_get_texture(JSContext* ctx, JSValue this_val) {
    Font* ptr = JS_GetOpaque2(ctx, this_val, js_Font_class_id);
    Texture2D texture = ptr->texture;
    Texture2D* ptr_ret = (Texture2D*)js_malloc(ctx, sizeof(Texture2D));
    *ptr_ret = texture;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static const JSCFunctionListEntry js_Font_proto_funcs[] = {
    JS_CGETSET_DEF("baseSize",js_Font_get_baseSize,NULL),
    JS_CGETSET_DEF("glyphCount",js_Font_get_glyphCount,NULL),
    JS_CGETSET_DEF("glyphPadding",js_Font_get_glyphPadding,NULL),
    JS_CGETSET_DEF("texture",js_Font_get_texture,NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Font", JS_PROP_CONFIGURABLE),
};

static int js_declare_Font(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Font_class_id);
    JSClassDef js_Font_def = { .class_name = "Font", .finalizer = js_Font_finalizer };
    JS_NewClass(rt, js_Font_class_id, &js_Font_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Font_proto_funcs, countof(js_Font_proto_funcs));
    JS_SetClassProto(ctx, js_Font_class_id, proto);
    return 0;
}

static void js_Camera3D_finalizer(JSRuntime * rt, JSValue val) {
    Camera3D* ptr = JS_GetOpaque(val, js_Camera3D_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Camera3D_get_position(JSContext* ctx, JSValue this_val) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    Vector3 position = ptr->position;
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = position;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_Camera3D_set_position(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    Vector3* ptr_value = (Vector3*)JS_GetOpaque(v, js_Vector3_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 value = *ptr_value;
    ptr->position = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera3D_get_target(JSContext* ctx, JSValue this_val) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    Vector3 target = ptr->target;
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = target;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_Camera3D_set_target(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    Vector3* ptr_value = (Vector3*)JS_GetOpaque(v, js_Vector3_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 value = *ptr_value;
    ptr->target = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera3D_set_up(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    Vector3* ptr_value = (Vector3*)JS_GetOpaque(v, js_Vector3_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 value = *ptr_value;
    ptr->up = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera3D_get_fovy(JSContext* ctx, JSValue this_val) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    float fovy = ptr->fovy;
    JSValue ret = JS_NewFloat64(ctx, (double)fovy);
    return ret;
}

static JSValue js_Camera3D_set_fovy(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->fovy = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera3D_get_projection(JSContext* ctx, JSValue this_val) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    int projection = ptr->projection;
    JSValue ret = JS_NewInt32(ctx, (long)projection);
    return ret;
}

static JSValue js_Camera3D_set_projection(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->projection = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Camera3D_proto_funcs[] = {
    JS_CGETSET_DEF("position",js_Camera3D_get_position,js_Camera3D_set_position),
    JS_CGETSET_DEF("target",js_Camera3D_get_target,js_Camera3D_set_target),
    JS_CGETSET_DEF("up",NULL,js_Camera3D_set_up),
    JS_CGETSET_DEF("fovy",js_Camera3D_get_fovy,js_Camera3D_set_fovy),
    JS_CGETSET_DEF("projection",js_Camera3D_get_projection,js_Camera3D_set_projection),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Camera3D", JS_PROP_CONFIGURABLE),
};

static int js_declare_Camera3D(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Camera3D_class_id);
    JSClassDef js_Camera3D_def = { .class_name = "Camera3D", .finalizer = js_Camera3D_finalizer };
    JS_NewClass(rt, js_Camera3D_class_id, &js_Camera3D_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Camera3D_proto_funcs, countof(js_Camera3D_proto_funcs));
    JS_SetClassProto(ctx, js_Camera3D_class_id, proto);
    return 0;
}

static void js_Camera2D_finalizer(JSRuntime * rt, JSValue val) {
    Camera2D* ptr = JS_GetOpaque(val, js_Camera2D_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Camera2D_get_offset(JSContext* ctx, JSValue this_val) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    Vector2 offset = ptr->offset;
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = offset;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_Camera2D_set_offset(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    Vector2* ptr_value = (Vector2*)JS_GetOpaque(v, js_Vector2_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 value = *ptr_value;
    ptr->offset = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera2D_get_target(JSContext* ctx, JSValue this_val) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    Vector2 target = ptr->target;
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = target;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_Camera2D_set_target(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    Vector2* ptr_value = (Vector2*)JS_GetOpaque(v, js_Vector2_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 value = *ptr_value;
    ptr->target = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera2D_get_rotation(JSContext* ctx, JSValue this_val) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    float rotation = ptr->rotation;
    JSValue ret = JS_NewFloat64(ctx, (double)rotation);
    return ret;
}

static JSValue js_Camera2D_set_rotation(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->rotation = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera2D_get_zoom(JSContext* ctx, JSValue this_val) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    float zoom = ptr->zoom;
    JSValue ret = JS_NewFloat64(ctx, (double)zoom);
    return ret;
}

static JSValue js_Camera2D_set_zoom(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->zoom = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Camera2D_proto_funcs[] = {
    JS_CGETSET_DEF("offset",js_Camera2D_get_offset,js_Camera2D_set_offset),
    JS_CGETSET_DEF("target",js_Camera2D_get_target,js_Camera2D_set_target),
    JS_CGETSET_DEF("rotation",js_Camera2D_get_rotation,js_Camera2D_set_rotation),
    JS_CGETSET_DEF("zoom",js_Camera2D_get_zoom,js_Camera2D_set_zoom),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Camera2D", JS_PROP_CONFIGURABLE),
};

static int js_declare_Camera2D(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Camera2D_class_id);
    JSClassDef js_Camera2D_def = { .class_name = "Camera2D", .finalizer = js_Camera2D_finalizer };
    JS_NewClass(rt, js_Camera2D_class_id, &js_Camera2D_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Camera2D_proto_funcs, countof(js_Camera2D_proto_funcs));
    JS_SetClassProto(ctx, js_Camera2D_class_id, proto);
    return 0;
}

static void js_Mesh_finalizer(JSRuntime * rt, JSValue val) {
    Mesh* ptr = JS_GetOpaque(val, js_Mesh_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Mesh_get_vertexCount(JSContext* ctx, JSValue this_val) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    int vertexCount = ptr->vertexCount;
    JSValue ret = JS_NewInt32(ctx, (long)vertexCount);
    return ret;
}

static JSValue js_Mesh_set_vertexCount(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->vertexCount = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_get_triangleCount(JSContext* ctx, JSValue this_val) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    int triangleCount = ptr->triangleCount;
    JSValue ret = JS_NewInt32(ctx, (long)triangleCount);
    return ret;
}

static JSValue js_Mesh_set_triangleCount(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->triangleCount = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_get_vertices(JSContext* ctx, JSValue this_val) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * vertices = ptr->vertices;
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < ptr->vertexCount*3; i0++){
        JSValue js_ret = JS_NewFloat64(ctx, (double)vertices[i0]);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_Mesh_set_vertices(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_valuei0;
            int err_valuei0 = JS_ToFloat64(ctx, &double_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (float)double_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type float *");
            return JS_EXCEPTION;
        }
    }
    if(ptr->vertices!=NULL) {
        js_free(ctx, ptr->vertices);
    }
    ptr->vertices = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_get_texcoords(JSContext* ctx, JSValue this_val) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * texcoords = ptr->texcoords;
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < ptr->vertexCount*2; i0++){
        JSValue js_ret = JS_NewFloat64(ctx, (double)texcoords[i0]);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_Mesh_set_texcoords(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_valuei0;
            int err_valuei0 = JS_ToFloat64(ctx, &double_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (float)double_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type float *");
            return JS_EXCEPTION;
        }
    }
    if(ptr->texcoords!=NULL) {
        js_free(ctx, ptr->texcoords);
    }
    ptr->texcoords = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_texcoords2(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_valuei0;
            int err_valuei0 = JS_ToFloat64(ctx, &double_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (float)double_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type float *");
            return JS_EXCEPTION;
        }
    }
    if(ptr->texcoords2!=NULL) {
        js_free(ctx, ptr->texcoords2);
    }
    ptr->texcoords2 = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_get_normals(JSContext* ctx, JSValue this_val) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * normals = ptr->normals;
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < ptr->vertexCount*3; i0++){
        JSValue js_ret = JS_NewFloat64(ctx, (double)normals[i0]);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_Mesh_set_normals(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_valuei0;
            int err_valuei0 = JS_ToFloat64(ctx, &double_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (float)double_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type float *");
            return JS_EXCEPTION;
        }
    }
    if(ptr->normals!=NULL) {
        js_free(ctx, ptr->normals);
    }
    ptr->normals = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_tangents(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_valuei0;
            int err_valuei0 = JS_ToFloat64(ctx, &double_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (float)double_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type float *");
            return JS_EXCEPTION;
        }
    }
    if(ptr->tangents!=NULL) {
        js_free(ctx, ptr->tangents);
    }
    ptr->tangents = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_colors(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    unsigned char * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (unsigned char *)jsc_malloc(ctx, size_value * sizeof(unsigned char));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            uint32_t long_valuei0;
            int err_valuei0 = JS_ToUint32(ctx, &long_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (unsigned char)long_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        unsigned char * js_value = (unsigned char *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (unsigned char *)jsc_malloc(ctx, size_value * sizeof(unsigned char *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_UINT8_ARRAY || classid_value==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            unsigned char * js_value = (unsigned char *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (unsigned char *)jsc_malloc(ctx, size_value * sizeof(unsigned char *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type unsigned char *");
            return JS_EXCEPTION;
        }
    }
    if(ptr->colors!=NULL) {
        js_free(ctx, ptr->colors);
    }
    ptr->colors = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_indices(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    unsigned short * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (unsigned short *)jsc_malloc(ctx, size_value * sizeof(unsigned short));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            uint32_t long_valuei0;
            int err_valuei0 = JS_ToUint32(ctx, &long_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (unsigned short)long_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        unsigned short * js_value = (unsigned short *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (unsigned short *)jsc_malloc(ctx, size_value * sizeof(unsigned short *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_UINT16_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            unsigned short * js_value = (unsigned short *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (unsigned short *)jsc_malloc(ctx, size_value * sizeof(unsigned short *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type unsigned short *");
            return JS_EXCEPTION;
        }
    }
    if(ptr->indices!=NULL) {
        js_free(ctx, ptr->indices);
    }
    ptr->indices = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_animVertices(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_valuei0;
            int err_valuei0 = JS_ToFloat64(ctx, &double_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (float)double_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type float *");
            return JS_EXCEPTION;
        }
    }
    if(ptr->animVertices!=NULL) {
        js_free(ctx, ptr->animVertices);
    }
    ptr->animVertices = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_animNormals(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_valuei0;
            int err_valuei0 = JS_ToFloat64(ctx, &double_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (float)double_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type float *");
            return JS_EXCEPTION;
        }
    }
    if(ptr->animNormals!=NULL) {
        js_free(ctx, ptr->animNormals);
    }
    ptr->animNormals = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_boneIds(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    unsigned char * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (unsigned char *)jsc_malloc(ctx, size_value * sizeof(unsigned char));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            uint32_t long_valuei0;
            int err_valuei0 = JS_ToUint32(ctx, &long_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (unsigned char)long_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        unsigned char * js_value = (unsigned char *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (unsigned char *)jsc_malloc(ctx, size_value * sizeof(unsigned char *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_UINT8_ARRAY || classid_value==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            unsigned char * js_value = (unsigned char *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (unsigned char *)jsc_malloc(ctx, size_value * sizeof(unsigned char *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type unsigned char *");
            return JS_EXCEPTION;
        }
    }
    if(ptr->boneIds!=NULL) {
        js_free(ctx, ptr->boneIds);
    }
    ptr->boneIds = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_boneWeights(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_valuei0;
            int err_valuei0 = JS_ToFloat64(ctx, &double_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (float)double_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type float *");
            return JS_EXCEPTION;
        }
    }
    if(ptr->boneWeights!=NULL) {
        js_free(ctx, ptr->boneWeights);
    }
    ptr->boneWeights = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Mesh_proto_funcs[] = {
    JS_CGETSET_DEF("vertexCount",js_Mesh_get_vertexCount,js_Mesh_set_vertexCount),
    JS_CGETSET_DEF("triangleCount",js_Mesh_get_triangleCount,js_Mesh_set_triangleCount),
    JS_CGETSET_DEF("vertices",js_Mesh_get_vertices,js_Mesh_set_vertices),
    JS_CGETSET_DEF("texcoords",js_Mesh_get_texcoords,js_Mesh_set_texcoords),
    JS_CGETSET_DEF("texcoords2",NULL,js_Mesh_set_texcoords2),
    JS_CGETSET_DEF("normals",js_Mesh_get_normals,js_Mesh_set_normals),
    JS_CGETSET_DEF("tangents",NULL,js_Mesh_set_tangents),
    JS_CGETSET_DEF("colors",NULL,js_Mesh_set_colors),
    JS_CGETSET_DEF("indices",NULL,js_Mesh_set_indices),
    JS_CGETSET_DEF("animVertices",NULL,js_Mesh_set_animVertices),
    JS_CGETSET_DEF("animNormals",NULL,js_Mesh_set_animNormals),
    JS_CGETSET_DEF("boneIds",NULL,js_Mesh_set_boneIds),
    JS_CGETSET_DEF("boneWeights",NULL,js_Mesh_set_boneWeights),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Mesh", JS_PROP_CONFIGURABLE),
};

static int js_declare_Mesh(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Mesh_class_id);
    JSClassDef js_Mesh_def = { .class_name = "Mesh", .finalizer = js_Mesh_finalizer };
    JS_NewClass(rt, js_Mesh_class_id, &js_Mesh_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Mesh_proto_funcs, countof(js_Mesh_proto_funcs));
    JS_SetClassProto(ctx, js_Mesh_class_id, proto);
    return 0;
}

static void js_Shader_finalizer(JSRuntime * rt, JSValue val) {
    Shader* ptr = JS_GetOpaque(val, js_Shader_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Shader_get_id(JSContext* ctx, JSValue this_val) {
    Shader* ptr = JS_GetOpaque2(ctx, this_val, js_Shader_class_id);
    unsigned int id = ptr->id;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)id);
    return ret;
}

static const JSCFunctionListEntry js_Shader_proto_funcs[] = {
    JS_CGETSET_DEF("id",js_Shader_get_id,NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Shader", JS_PROP_CONFIGURABLE),
};

static int js_declare_Shader(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Shader_class_id);
    JSClassDef js_Shader_def = { .class_name = "Shader", .finalizer = js_Shader_finalizer };
    JS_NewClass(rt, js_Shader_class_id, &js_Shader_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Shader_proto_funcs, countof(js_Shader_proto_funcs));
    JS_SetClassProto(ctx, js_Shader_class_id, proto);
    return 0;
}

static void js_MaterialMap_finalizer(JSRuntime * rt, JSValue val) {
    MaterialMap* ptr = JS_GetOpaque(val, js_MaterialMap_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_MaterialMap_set_texture(JSContext* ctx, JSValue this_val, JSValue v) {
    MaterialMap* ptr = JS_GetOpaque2(ctx, this_val, js_MaterialMap_class_id);
    Texture2D* ptr_value = (Texture2D*)JS_GetOpaque(v, js_Texture_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D value = *ptr_value;
    ptr->texture = value;
    return JS_UNDEFINED;
}

static JSValue js_MaterialMap_get_color(JSContext* ctx, JSValue this_val) {
    MaterialMap* ptr = JS_GetOpaque2(ctx, this_val, js_MaterialMap_class_id);
    Color color = ptr->color;
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = color;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_MaterialMap_set_color(JSContext* ctx, JSValue this_val, JSValue v) {
    MaterialMap* ptr = JS_GetOpaque2(ctx, this_val, js_MaterialMap_class_id);
    Color* ptr_value = (Color*)JS_GetOpaque(v, js_Color_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Color value = *ptr_value;
    ptr->color = value;
    return JS_UNDEFINED;
}

static JSValue js_MaterialMap_get_value(JSContext* ctx, JSValue this_val) {
    MaterialMap* ptr = JS_GetOpaque2(ctx, this_val, js_MaterialMap_class_id);
    float value = ptr->value;
    JSValue ret = JS_NewFloat64(ctx, (double)value);
    return ret;
}

static JSValue js_MaterialMap_set_value(JSContext* ctx, JSValue this_val, JSValue v) {
    MaterialMap* ptr = JS_GetOpaque2(ctx, this_val, js_MaterialMap_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->value = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_MaterialMap_proto_funcs[] = {
    JS_CGETSET_DEF("texture",NULL,js_MaterialMap_set_texture),
    JS_CGETSET_DEF("color",js_MaterialMap_get_color,js_MaterialMap_set_color),
    JS_CGETSET_DEF("value",js_MaterialMap_get_value,js_MaterialMap_set_value),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","MaterialMap", JS_PROP_CONFIGURABLE),
};

static int js_declare_MaterialMap(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_MaterialMap_class_id);
    JSClassDef js_MaterialMap_def = { .class_name = "MaterialMap", .finalizer = js_MaterialMap_finalizer };
    JS_NewClass(rt, js_MaterialMap_class_id, &js_MaterialMap_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_MaterialMap_proto_funcs, countof(js_MaterialMap_proto_funcs));
    JS_SetClassProto(ctx, js_MaterialMap_class_id, proto);
    return 0;
}

static void js_Material_finalizer(JSRuntime * rt, JSValue val) {
    Material* ptr = JS_GetOpaque(val, js_Material_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Material_get_shader(JSContext* ctx, JSValue this_val) {
    Material* ptr = JS_GetOpaque2(ctx, this_val, js_Material_class_id);
    Shader shader = ptr->shader;
    Shader* ptr_ret = (Shader*)js_malloc(ctx, sizeof(Shader));
    *ptr_ret = shader;
    JSValue ret = JS_NewObjectClass(ctx, js_Shader_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_Material_set_shader(JSContext* ctx, JSValue this_val, JSValue v) {
    Material* ptr = JS_GetOpaque2(ctx, this_val, js_Material_class_id);
    Shader* ptr_value = (Shader*)JS_GetOpaque(v, js_Shader_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Shader value = *ptr_value;
    ptr->shader = value;
    return JS_UNDEFINED;
}

static JSValue js_Material_get_maps(JSContext* ctx, JSValue this_val) {
    Material* ptr = JS_GetOpaque2(ctx, this_val, js_Material_class_id);
    MaterialMap * maps = ptr->maps;
    JSValue ret;
    ret = JS_NewArray(ctx);
    MaterialMap* ptr_js_ret0 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret0 = maps[0];
    JSValue js_ret0 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret0, ptr_js_ret0);
    JS_DefinePropertyValueUint32(ctx,ret,0,js_ret0,JS_PROP_C_W_E);
    MaterialMap* ptr_js_ret1 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret1 = maps[1];
    JSValue js_ret1 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret1, ptr_js_ret1);
    JS_DefinePropertyValueUint32(ctx,ret,1,js_ret1,JS_PROP_C_W_E);
    MaterialMap* ptr_js_ret2 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret2 = maps[2];
    JSValue js_ret2 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret2, ptr_js_ret2);
    JS_DefinePropertyValueUint32(ctx,ret,2,js_ret2,JS_PROP_C_W_E);
    MaterialMap* ptr_js_ret3 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret3 = maps[3];
    JSValue js_ret3 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret3, ptr_js_ret3);
    JS_DefinePropertyValueUint32(ctx,ret,3,js_ret3,JS_PROP_C_W_E);
    MaterialMap* ptr_js_ret4 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret4 = maps[4];
    JSValue js_ret4 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret4, ptr_js_ret4);
    JS_DefinePropertyValueUint32(ctx,ret,4,js_ret4,JS_PROP_C_W_E);
    MaterialMap* ptr_js_ret5 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret5 = maps[5];
    JSValue js_ret5 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret5, ptr_js_ret5);
    JS_DefinePropertyValueUint32(ctx,ret,5,js_ret5,JS_PROP_C_W_E);
    MaterialMap* ptr_js_ret6 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret6 = maps[6];
    JSValue js_ret6 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret6, ptr_js_ret6);
    JS_DefinePropertyValueUint32(ctx,ret,6,js_ret6,JS_PROP_C_W_E);
    MaterialMap* ptr_js_ret7 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret7 = maps[7];
    JSValue js_ret7 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret7, ptr_js_ret7);
    JS_DefinePropertyValueUint32(ctx,ret,7,js_ret7,JS_PROP_C_W_E);
    MaterialMap* ptr_js_ret8 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret8 = maps[8];
    JSValue js_ret8 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret8, ptr_js_ret8);
    JS_DefinePropertyValueUint32(ctx,ret,8,js_ret8,JS_PROP_C_W_E);
    MaterialMap* ptr_js_ret9 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret9 = maps[9];
    JSValue js_ret9 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret9, ptr_js_ret9);
    JS_DefinePropertyValueUint32(ctx,ret,9,js_ret9,JS_PROP_C_W_E);
    MaterialMap* ptr_js_ret10 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret10 = maps[10];
    JSValue js_ret10 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret10, ptr_js_ret10);
    JS_DefinePropertyValueUint32(ctx,ret,10,js_ret10,JS_PROP_C_W_E);
    MaterialMap* ptr_js_ret11 = (MaterialMap*)js_malloc(ctx, sizeof(MaterialMap));
    *ptr_js_ret11 = maps[11];
    JSValue js_ret11 = JS_NewObjectClass(ctx, js_MaterialMap_class_id);
    JS_SetOpaque(js_ret11, ptr_js_ret11);
    JS_DefinePropertyValueUint32(ctx,ret,11,js_ret11,JS_PROP_C_W_E);
    return ret;
}

static const JSCFunctionListEntry js_Material_proto_funcs[] = {
    JS_CGETSET_DEF("shader",js_Material_get_shader,js_Material_set_shader),
    JS_CGETSET_DEF("maps",js_Material_get_maps,NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Material", JS_PROP_CONFIGURABLE),
};

static int js_declare_Material(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Material_class_id);
    JSClassDef js_Material_def = { .class_name = "Material", .finalizer = js_Material_finalizer };
    JS_NewClass(rt, js_Material_class_id, &js_Material_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Material_proto_funcs, countof(js_Material_proto_funcs));
    JS_SetClassProto(ctx, js_Material_class_id, proto);
    return 0;
}

static void js_Transform_finalizer(JSRuntime * rt, JSValue val) {
    Transform* ptr = JS_GetOpaque(val, js_Transform_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_Transform_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Transform", JS_PROP_CONFIGURABLE),
};

static int js_declare_Transform(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Transform_class_id);
    JSClassDef js_Transform_def = { .class_name = "Transform", .finalizer = js_Transform_finalizer };
    JS_NewClass(rt, js_Transform_class_id, &js_Transform_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Transform_proto_funcs, countof(js_Transform_proto_funcs));
    JS_SetClassProto(ctx, js_Transform_class_id, proto);
    return 0;
}

static void js_BoneInfo_finalizer(JSRuntime * rt, JSValue val) {
    BoneInfo* ptr = JS_GetOpaque(val, js_BoneInfo_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_BoneInfo_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","BoneInfo", JS_PROP_CONFIGURABLE),
};

static int js_declare_BoneInfo(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_BoneInfo_class_id);
    JSClassDef js_BoneInfo_def = { .class_name = "BoneInfo", .finalizer = js_BoneInfo_finalizer };
    JS_NewClass(rt, js_BoneInfo_class_id, &js_BoneInfo_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_BoneInfo_proto_funcs, countof(js_BoneInfo_proto_funcs));
    JS_SetClassProto(ctx, js_BoneInfo_class_id, proto);
    return 0;
}

static void js_Model_finalizer(JSRuntime * rt, JSValue val) {
    Model* ptr = JS_GetOpaque(val, js_Model_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Model_get_transform(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    Matrix transform = ptr->transform;
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = transform;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_Model_set_transform(JSContext* ctx, JSValue this_val, JSValue v) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    Matrix* ptr_value = (Matrix*)JS_GetOpaque(v, js_Matrix_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Matrix value = *ptr_value;
    ptr->transform = value;
    return JS_UNDEFINED;
}

static JSValue js_Model_get_meshCount(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    int meshCount = ptr->meshCount;
    JSValue ret = JS_NewInt32(ctx, (long)meshCount);
    return ret;
}

static JSValue js_Model_get_materialCount(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    int materialCount = ptr->materialCount;
    JSValue ret = JS_NewInt32(ctx, (long)materialCount);
    return ret;
}

static JSValue js_Model_get_meshes(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    Mesh * meshes = ptr->meshes;
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < ptr->meshCount; i0++){
        Mesh* ptr_js_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
        *ptr_js_ret = meshes[i0];
        JSValue js_ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
        JS_SetOpaque(js_ret, ptr_js_ret);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_Model_set_meshes(JSContext* ctx, JSValue this_val, JSValue v) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    Mesh * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (Mesh *)jsc_malloc(ctx, size_value * sizeof(Mesh));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            Mesh* ptr_valuei0 = (Mesh*)JS_GetOpaque(js_value, js_Mesh_class_id);
            if(ptr_valuei0 == NULL) {
                JS_ThrowTypeError(ctx, "js_value does not allow null");
                return JS_EXCEPTION;
            }
            value[i0] = *ptr_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        Mesh * js_value = (Mesh *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (Mesh *)jsc_malloc(ctx, size_value * sizeof(Mesh *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JS_ThrowTypeError(ctx, "v does not match type Mesh *");
        return JS_EXCEPTION;
    }
    if(ptr->meshes!=NULL) {
        js_free(ctx, ptr->meshes);
    }
    ptr->meshes = value;
    return JS_UNDEFINED;
}

static JSValue js_Model_get_materials(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    Material * materials = ptr->materials;
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < ptr->materialCount; i0++){
        Material* ptr_js_ret = (Material*)js_malloc(ctx, sizeof(Material));
        *ptr_js_ret = materials[i0];
        JSValue js_ret = JS_NewObjectClass(ctx, js_Material_class_id);
        JS_SetOpaque(js_ret, ptr_js_ret);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_Model_set_materials(JSContext* ctx, JSValue this_val, JSValue v) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    Material * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = (Material *)jsc_malloc(ctx, size_value * sizeof(Material));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            Material* ptr_valuei0 = (Material*)JS_GetOpaque(js_value, js_Material_class_id);
            if(ptr_valuei0 == NULL) {
                JS_ThrowTypeError(ctx, "js_value does not allow null");
                return JS_EXCEPTION;
            }
            value[i0] = *ptr_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        Material * js_value = (Material *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (Material *)jsc_malloc(ctx, size_value * sizeof(Material *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JS_ThrowTypeError(ctx, "v does not match type Material *");
        return JS_EXCEPTION;
    }
    if(ptr->materials!=NULL) {
        js_free(ctx, ptr->materials);
    }
    ptr->materials = value;
    return JS_UNDEFINED;
}

static JSValue js_Model_get_meshMaterial(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    int * meshMaterial = ptr->meshMaterial;
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < ptr->meshCount; i0++){
        JSValue js_ret = JS_NewInt32(ctx, (long)meshMaterial[i0]);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_Model_get_boneCount(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    int boneCount = ptr->boneCount;
    JSValue ret = JS_NewInt32(ctx, (long)boneCount);
    return ret;
}

static JSValue js_Model_get_bones(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    BoneInfo * bones = ptr->bones;
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < ptr->boneCount; i0++){
        BoneInfo* ptr_js_ret = (BoneInfo*)js_malloc(ctx, sizeof(BoneInfo));
        *ptr_js_ret = bones[i0];
        JSValue js_ret = JS_NewObjectClass(ctx, js_BoneInfo_class_id);
        JS_SetOpaque(js_ret, ptr_js_ret);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_Model_get_bindPose(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    Transform * bindPose = ptr->bindPose;
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < ptr->boneCount; i0++){
        Transform* ptr_js_ret = (Transform*)js_malloc(ctx, sizeof(Transform));
        *ptr_js_ret = bindPose[i0];
        JSValue js_ret = JS_NewObjectClass(ctx, js_Transform_class_id);
        JS_SetOpaque(js_ret, ptr_js_ret);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    return ret;
}

static const JSCFunctionListEntry js_Model_proto_funcs[] = {
    JS_CGETSET_DEF("transform",js_Model_get_transform,js_Model_set_transform),
    JS_CGETSET_DEF("meshCount",js_Model_get_meshCount,NULL),
    JS_CGETSET_DEF("materialCount",js_Model_get_materialCount,NULL),
    JS_CGETSET_DEF("meshes",js_Model_get_meshes,js_Model_set_meshes),
    JS_CGETSET_DEF("materials",js_Model_get_materials,js_Model_set_materials),
    JS_CGETSET_DEF("meshMaterial",js_Model_get_meshMaterial,NULL),
    JS_CGETSET_DEF("boneCount",js_Model_get_boneCount,NULL),
    JS_CGETSET_DEF("bones",js_Model_get_bones,NULL),
    JS_CGETSET_DEF("bindPose",js_Model_get_bindPose,NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Model", JS_PROP_CONFIGURABLE),
};

static int js_declare_Model(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Model_class_id);
    JSClassDef js_Model_def = { .class_name = "Model", .finalizer = js_Model_finalizer };
    JS_NewClass(rt, js_Model_class_id, &js_Model_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Model_proto_funcs, countof(js_Model_proto_funcs));
    JS_SetClassProto(ctx, js_Model_class_id, proto);
    return 0;
}

static void js_ModelAnimation_finalizer(JSRuntime * rt, JSValue val) {
    ModelAnimation* ptr = JS_GetOpaque(val, js_ModelAnimation_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_ModelAnimation_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","ModelAnimation", JS_PROP_CONFIGURABLE),
};

static int js_declare_ModelAnimation(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_ModelAnimation_class_id);
    JSClassDef js_ModelAnimation_def = { .class_name = "ModelAnimation", .finalizer = js_ModelAnimation_finalizer };
    JS_NewClass(rt, js_ModelAnimation_class_id, &js_ModelAnimation_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_ModelAnimation_proto_funcs, countof(js_ModelAnimation_proto_funcs));
    JS_SetClassProto(ctx, js_ModelAnimation_class_id, proto);
    return 0;
}

static void js_Ray_finalizer(JSRuntime * rt, JSValue val) {
    Ray* ptr = JS_GetOpaque(val, js_Ray_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Ray_set_position(JSContext* ctx, JSValue this_val, JSValue v) {
    Ray* ptr = JS_GetOpaque2(ctx, this_val, js_Ray_class_id);
    Vector3* ptr_value = (Vector3*)JS_GetOpaque(v, js_Vector3_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 value = *ptr_value;
    ptr->position = value;
    return JS_UNDEFINED;
}

static JSValue js_Ray_set_direction(JSContext* ctx, JSValue this_val, JSValue v) {
    Ray* ptr = JS_GetOpaque2(ctx, this_val, js_Ray_class_id);
    Vector3* ptr_value = (Vector3*)JS_GetOpaque(v, js_Vector3_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 value = *ptr_value;
    ptr->direction = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Ray_proto_funcs[] = {
    JS_CGETSET_DEF("position",NULL,js_Ray_set_position),
    JS_CGETSET_DEF("direction",NULL,js_Ray_set_direction),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Ray", JS_PROP_CONFIGURABLE),
};

static int js_declare_Ray(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Ray_class_id);
    JSClassDef js_Ray_def = { .class_name = "Ray", .finalizer = js_Ray_finalizer };
    JS_NewClass(rt, js_Ray_class_id, &js_Ray_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Ray_proto_funcs, countof(js_Ray_proto_funcs));
    JS_SetClassProto(ctx, js_Ray_class_id, proto);
    return 0;
}

static void js_RayCollision_finalizer(JSRuntime * rt, JSValue val) {
    RayCollision* ptr = JS_GetOpaque(val, js_RayCollision_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_RayCollision_get_hit(JSContext* ctx, JSValue this_val) {
    RayCollision* ptr = JS_GetOpaque2(ctx, this_val, js_RayCollision_class_id);
    bool hit = ptr->hit;
    JSValue ret = JS_NewBool(ctx, hit);
    return ret;
}

static JSValue js_RayCollision_get_distance(JSContext* ctx, JSValue this_val) {
    RayCollision* ptr = JS_GetOpaque2(ctx, this_val, js_RayCollision_class_id);
    float distance = ptr->distance;
    JSValue ret = JS_NewFloat64(ctx, (double)distance);
    return ret;
}

static JSValue js_RayCollision_get_point(JSContext* ctx, JSValue this_val) {
    RayCollision* ptr = JS_GetOpaque2(ctx, this_val, js_RayCollision_class_id);
    Vector3 point = ptr->point;
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = point;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_RayCollision_get_normal(JSContext* ctx, JSValue this_val) {
    RayCollision* ptr = JS_GetOpaque2(ctx, this_val, js_RayCollision_class_id);
    Vector3 normal = ptr->normal;
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = normal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static const JSCFunctionListEntry js_RayCollision_proto_funcs[] = {
    JS_CGETSET_DEF("hit",js_RayCollision_get_hit,NULL),
    JS_CGETSET_DEF("distance",js_RayCollision_get_distance,NULL),
    JS_CGETSET_DEF("point",js_RayCollision_get_point,NULL),
    JS_CGETSET_DEF("normal",js_RayCollision_get_normal,NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","RayCollision", JS_PROP_CONFIGURABLE),
};

static int js_declare_RayCollision(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_RayCollision_class_id);
    JSClassDef js_RayCollision_def = { .class_name = "RayCollision", .finalizer = js_RayCollision_finalizer };
    JS_NewClass(rt, js_RayCollision_class_id, &js_RayCollision_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_RayCollision_proto_funcs, countof(js_RayCollision_proto_funcs));
    JS_SetClassProto(ctx, js_RayCollision_class_id, proto);
    return 0;
}

static void js_BoundingBox_finalizer(JSRuntime * rt, JSValue val) {
    BoundingBox* ptr = JS_GetOpaque(val, js_BoundingBox_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_BoundingBox_get_min(JSContext* ctx, JSValue this_val) {
    BoundingBox* ptr = JS_GetOpaque2(ctx, this_val, js_BoundingBox_class_id);
    Vector3 min = ptr->min;
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = min;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_BoundingBox_set_min(JSContext* ctx, JSValue this_val, JSValue v) {
    BoundingBox* ptr = JS_GetOpaque2(ctx, this_val, js_BoundingBox_class_id);
    Vector3* ptr_value = (Vector3*)JS_GetOpaque(v, js_Vector3_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 value = *ptr_value;
    ptr->min = value;
    return JS_UNDEFINED;
}

static JSValue js_BoundingBox_get_max(JSContext* ctx, JSValue this_val) {
    BoundingBox* ptr = JS_GetOpaque2(ctx, this_val, js_BoundingBox_class_id);
    Vector3 max = ptr->max;
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = max;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_BoundingBox_set_max(JSContext* ctx, JSValue this_val, JSValue v) {
    BoundingBox* ptr = JS_GetOpaque2(ctx, this_val, js_BoundingBox_class_id);
    Vector3* ptr_value = (Vector3*)JS_GetOpaque(v, js_Vector3_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 value = *ptr_value;
    ptr->max = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_BoundingBox_proto_funcs[] = {
    JS_CGETSET_DEF("min",js_BoundingBox_get_min,js_BoundingBox_set_min),
    JS_CGETSET_DEF("max",js_BoundingBox_get_max,js_BoundingBox_set_max),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","BoundingBox", JS_PROP_CONFIGURABLE),
};

static int js_declare_BoundingBox(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_BoundingBox_class_id);
    JSClassDef js_BoundingBox_def = { .class_name = "BoundingBox", .finalizer = js_BoundingBox_finalizer };
    JS_NewClass(rt, js_BoundingBox_class_id, &js_BoundingBox_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_BoundingBox_proto_funcs, countof(js_BoundingBox_proto_funcs));
    JS_SetClassProto(ctx, js_BoundingBox_class_id, proto);
    return 0;
}

static void js_Wave_finalizer(JSRuntime * rt, JSValue val) {
    Wave* ptr = JS_GetOpaque(val, js_Wave_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Wave_get_frameCount(JSContext* ctx, JSValue this_val) {
    Wave* ptr = JS_GetOpaque2(ctx, this_val, js_Wave_class_id);
    unsigned int frameCount = ptr->frameCount;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)frameCount);
    return ret;
}

static JSValue js_Wave_get_sampleRate(JSContext* ctx, JSValue this_val) {
    Wave* ptr = JS_GetOpaque2(ctx, this_val, js_Wave_class_id);
    unsigned int sampleRate = ptr->sampleRate;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)sampleRate);
    return ret;
}

static JSValue js_Wave_get_sampleSize(JSContext* ctx, JSValue this_val) {
    Wave* ptr = JS_GetOpaque2(ctx, this_val, js_Wave_class_id);
    unsigned int sampleSize = ptr->sampleSize;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)sampleSize);
    return ret;
}

static JSValue js_Wave_get_channels(JSContext* ctx, JSValue this_val) {
    Wave* ptr = JS_GetOpaque2(ctx, this_val, js_Wave_class_id);
    unsigned int channels = ptr->channels;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)channels);
    return ret;
}

static const JSCFunctionListEntry js_Wave_proto_funcs[] = {
    JS_CGETSET_DEF("frameCount",js_Wave_get_frameCount,NULL),
    JS_CGETSET_DEF("sampleRate",js_Wave_get_sampleRate,NULL),
    JS_CGETSET_DEF("sampleSize",js_Wave_get_sampleSize,NULL),
    JS_CGETSET_DEF("channels",js_Wave_get_channels,NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Wave", JS_PROP_CONFIGURABLE),
};

static int js_declare_Wave(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Wave_class_id);
    JSClassDef js_Wave_def = { .class_name = "Wave", .finalizer = js_Wave_finalizer };
    JS_NewClass(rt, js_Wave_class_id, &js_Wave_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Wave_proto_funcs, countof(js_Wave_proto_funcs));
    JS_SetClassProto(ctx, js_Wave_class_id, proto);
    return 0;
}

static void js_rAudioBuffer_finalizer(JSRuntime * rt, JSValue val) {
    rAudioBuffer* ptr = JS_GetOpaque(val, js_rAudioBuffer_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_rAudioBuffer_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","rAudioBuffer", JS_PROP_CONFIGURABLE),
};

static int js_declare_rAudioBuffer(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_rAudioBuffer_class_id);
    JSClassDef js_rAudioBuffer_def = { .class_name = "rAudioBuffer", .finalizer = js_rAudioBuffer_finalizer };
    JS_NewClass(rt, js_rAudioBuffer_class_id, &js_rAudioBuffer_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_rAudioBuffer_proto_funcs, countof(js_rAudioBuffer_proto_funcs));
    JS_SetClassProto(ctx, js_rAudioBuffer_class_id, proto);
    return 0;
}

static void js_rAudioProcessor_finalizer(JSRuntime * rt, JSValue val) {
    rAudioProcessor* ptr = JS_GetOpaque(val, js_rAudioProcessor_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_rAudioProcessor_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","rAudioProcessor", JS_PROP_CONFIGURABLE),
};

static int js_declare_rAudioProcessor(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_rAudioProcessor_class_id);
    JSClassDef js_rAudioProcessor_def = { .class_name = "rAudioProcessor", .finalizer = js_rAudioProcessor_finalizer };
    JS_NewClass(rt, js_rAudioProcessor_class_id, &js_rAudioProcessor_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_rAudioProcessor_proto_funcs, countof(js_rAudioProcessor_proto_funcs));
    JS_SetClassProto(ctx, js_rAudioProcessor_class_id, proto);
    return 0;
}

static void js_AudioStream_finalizer(JSRuntime * rt, JSValue val) {
    AudioStream* ptr = JS_GetOpaque(val, js_AudioStream_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_AudioStream_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","AudioStream", JS_PROP_CONFIGURABLE),
};

static int js_declare_AudioStream(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_AudioStream_class_id);
    JSClassDef js_AudioStream_def = { .class_name = "AudioStream", .finalizer = js_AudioStream_finalizer };
    JS_NewClass(rt, js_AudioStream_class_id, &js_AudioStream_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_AudioStream_proto_funcs, countof(js_AudioStream_proto_funcs));
    JS_SetClassProto(ctx, js_AudioStream_class_id, proto);
    return 0;
}

static void js_Sound_finalizer(JSRuntime * rt, JSValue val) {
    Sound* ptr = JS_GetOpaque(val, js_Sound_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Sound_get_frameCount(JSContext* ctx, JSValue this_val) {
    Sound* ptr = JS_GetOpaque2(ctx, this_val, js_Sound_class_id);
    unsigned int frameCount = ptr->frameCount;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)frameCount);
    return ret;
}

static const JSCFunctionListEntry js_Sound_proto_funcs[] = {
    JS_CGETSET_DEF("frameCount",js_Sound_get_frameCount,NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Sound", JS_PROP_CONFIGURABLE),
};

static int js_declare_Sound(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Sound_class_id);
    JSClassDef js_Sound_def = { .class_name = "Sound", .finalizer = js_Sound_finalizer };
    JS_NewClass(rt, js_Sound_class_id, &js_Sound_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Sound_proto_funcs, countof(js_Sound_proto_funcs));
    JS_SetClassProto(ctx, js_Sound_class_id, proto);
    return 0;
}

static void js_Music_finalizer(JSRuntime * rt, JSValue val) {
    Music* ptr = JS_GetOpaque(val, js_Music_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Music_get_frameCount(JSContext* ctx, JSValue this_val) {
    Music* ptr = JS_GetOpaque2(ctx, this_val, js_Music_class_id);
    unsigned int frameCount = ptr->frameCount;
    JSValue ret = JS_NewUint32(ctx, (unsigned long)frameCount);
    return ret;
}

static JSValue js_Music_get_looping(JSContext* ctx, JSValue this_val) {
    Music* ptr = JS_GetOpaque2(ctx, this_val, js_Music_class_id);
    bool looping = ptr->looping;
    JSValue ret = JS_NewBool(ctx, looping);
    return ret;
}

static JSValue js_Music_set_looping(JSContext* ctx, JSValue this_val, JSValue v) {
    Music* ptr = JS_GetOpaque2(ctx, this_val, js_Music_class_id);
    int js_value = JS_ToBool(ctx, v);
    if(js_value<0) {
        JS_ThrowTypeError(ctx, "v is not a bool");
        return JS_EXCEPTION;
    }
    bool value = js_value;
    ptr->looping = value;
    return JS_UNDEFINED;
}

static JSValue js_Music_get_ctxType(JSContext* ctx, JSValue this_val) {
    Music* ptr = JS_GetOpaque2(ctx, this_val, js_Music_class_id);
    int ctxType = ptr->ctxType;
    JSValue ret = JS_NewInt32(ctx, (long)ctxType);
    return ret;
}

static const JSCFunctionListEntry js_Music_proto_funcs[] = {
    JS_CGETSET_DEF("frameCount",js_Music_get_frameCount,NULL),
    JS_CGETSET_DEF("looping",js_Music_get_looping,js_Music_set_looping),
    JS_CGETSET_DEF("ctxType",js_Music_get_ctxType,NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Music", JS_PROP_CONFIGURABLE),
};

static int js_declare_Music(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Music_class_id);
    JSClassDef js_Music_def = { .class_name = "Music", .finalizer = js_Music_finalizer };
    JS_NewClass(rt, js_Music_class_id, &js_Music_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Music_proto_funcs, countof(js_Music_proto_funcs));
    JS_SetClassProto(ctx, js_Music_class_id, proto);
    return 0;
}

static void js_VrDeviceInfo_finalizer(JSRuntime * rt, JSValue val) {
    VrDeviceInfo* ptr = JS_GetOpaque(val, js_VrDeviceInfo_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_VrDeviceInfo_get_hResolution(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    int hResolution = ptr->hResolution;
    JSValue ret = JS_NewInt32(ctx, (long)hResolution);
    return ret;
}

static JSValue js_VrDeviceInfo_set_hResolution(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->hResolution = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_vResolution(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    int vResolution = ptr->vResolution;
    JSValue ret = JS_NewInt32(ctx, (long)vResolution);
    return ret;
}

static JSValue js_VrDeviceInfo_set_vResolution(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->vResolution = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_hScreenSize(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float hScreenSize = ptr->hScreenSize;
    JSValue ret = JS_NewFloat64(ctx, (double)hScreenSize);
    return ret;
}

static JSValue js_VrDeviceInfo_set_hScreenSize(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->hScreenSize = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_vScreenSize(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float vScreenSize = ptr->vScreenSize;
    JSValue ret = JS_NewFloat64(ctx, (double)vScreenSize);
    return ret;
}

static JSValue js_VrDeviceInfo_set_vScreenSize(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->vScreenSize = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_eyeToScreenDistance(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float eyeToScreenDistance = ptr->eyeToScreenDistance;
    JSValue ret = JS_NewFloat64(ctx, (double)eyeToScreenDistance);
    return ret;
}

static JSValue js_VrDeviceInfo_set_eyeToScreenDistance(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->eyeToScreenDistance = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_lensSeparationDistance(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float lensSeparationDistance = ptr->lensSeparationDistance;
    JSValue ret = JS_NewFloat64(ctx, (double)lensSeparationDistance);
    return ret;
}

static JSValue js_VrDeviceInfo_set_lensSeparationDistance(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->lensSeparationDistance = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_interpupillaryDistance(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float interpupillaryDistance = ptr->interpupillaryDistance;
    JSValue ret = JS_NewFloat64(ctx, (double)interpupillaryDistance);
    return ret;
}

static JSValue js_VrDeviceInfo_set_interpupillaryDistance(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->interpupillaryDistance = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_lensDistortionValues(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float * lensDistortionValues = ptr->lensDistortionValues;
    JSValue ret;
    ret = JS_NewArray(ctx);
    JSValue js_ret0 = JS_NewFloat64(ctx, (double)lensDistortionValues[0]);
    JS_DefinePropertyValueUint32(ctx,ret,0,js_ret0,JS_PROP_C_W_E);
    JSValue js_ret1 = JS_NewFloat64(ctx, (double)lensDistortionValues[1]);
    JS_DefinePropertyValueUint32(ctx,ret,1,js_ret1,JS_PROP_C_W_E);
    JSValue js_ret2 = JS_NewFloat64(ctx, (double)lensDistortionValues[2]);
    JS_DefinePropertyValueUint32(ctx,ret,2,js_ret2,JS_PROP_C_W_E);
    JSValue js_ret3 = JS_NewFloat64(ctx, (double)lensDistortionValues[3]);
    JS_DefinePropertyValueUint32(ctx,ret,3,js_ret3,JS_PROP_C_W_E);
    return ret;
}

static JSValue js_VrDeviceInfo_set_lensDistortionValues(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        value = (float *)jsc_malloc(ctx, 4 * sizeof(float));
        for(int i0=0; i0 < 4; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_valuei0;
            int err_valuei0 = JS_ToFloat64(ctx, &double_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (float)double_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type float *");
            return JS_EXCEPTION;
        }
    }
    memcpy(ptr->lensDistortionValues, value, 4 * sizeof(float ));
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_chromaAbCorrection(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float * chromaAbCorrection = ptr->chromaAbCorrection;
    JSValue ret;
    ret = JS_NewArray(ctx);
    JSValue js_ret0 = JS_NewFloat64(ctx, (double)chromaAbCorrection[0]);
    JS_DefinePropertyValueUint32(ctx,ret,0,js_ret0,JS_PROP_C_W_E);
    JSValue js_ret1 = JS_NewFloat64(ctx, (double)chromaAbCorrection[1]);
    JS_DefinePropertyValueUint32(ctx,ret,1,js_ret1,JS_PROP_C_W_E);
    JSValue js_ret2 = JS_NewFloat64(ctx, (double)chromaAbCorrection[2]);
    JS_DefinePropertyValueUint32(ctx,ret,2,js_ret2,JS_PROP_C_W_E);
    JSValue js_ret3 = JS_NewFloat64(ctx, (double)chromaAbCorrection[3]);
    JS_DefinePropertyValueUint32(ctx,ret,3,js_ret3,JS_PROP_C_W_E);
    return ret;
}

static JSValue js_VrDeviceInfo_set_chromaAbCorrection(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float * value;
    JSValue da_value;
    int64_t size_value;
    if(JS_IsArray(v) == 1) {
        value = (float *)jsc_malloc(ctx, 4 * sizeof(float));
        for(int i0=0; i0 < 4; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_valuei0;
            int err_valuei0 = JS_ToFloat64(ctx, &double_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (float)double_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        da_value = JS_DupValue(ctx,v);
        size_t size_value;
        float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
        value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
        memcpy(value, js_value, size_value);
        JS_FreeValuePtr(ctx, &da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            float * js_value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            js_value+=offset_value;
            size_value-=offset_value;
            value = (float *)jsc_malloc(ctx, size_value * sizeof(float *));
            memcpy(value, js_value, size_value);
            JS_FreeValuePtr(ctx, &da_value);
        }
        else {
            JS_ThrowTypeError(ctx, "v does not match type float *");
            return JS_EXCEPTION;
        }
    }
    memcpy(ptr->chromaAbCorrection, value, 4 * sizeof(float ));
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_VrDeviceInfo_proto_funcs[] = {
    JS_CGETSET_DEF("hResolution",js_VrDeviceInfo_get_hResolution,js_VrDeviceInfo_set_hResolution),
    JS_CGETSET_DEF("vResolution",js_VrDeviceInfo_get_vResolution,js_VrDeviceInfo_set_vResolution),
    JS_CGETSET_DEF("hScreenSize",js_VrDeviceInfo_get_hScreenSize,js_VrDeviceInfo_set_hScreenSize),
    JS_CGETSET_DEF("vScreenSize",js_VrDeviceInfo_get_vScreenSize,js_VrDeviceInfo_set_vScreenSize),
    JS_CGETSET_DEF("eyeToScreenDistance",js_VrDeviceInfo_get_eyeToScreenDistance,js_VrDeviceInfo_set_eyeToScreenDistance),
    JS_CGETSET_DEF("lensSeparationDistance",js_VrDeviceInfo_get_lensSeparationDistance,js_VrDeviceInfo_set_lensSeparationDistance),
    JS_CGETSET_DEF("interpupillaryDistance",js_VrDeviceInfo_get_interpupillaryDistance,js_VrDeviceInfo_set_interpupillaryDistance),
    JS_CGETSET_DEF("lensDistortionValues",js_VrDeviceInfo_get_lensDistortionValues,js_VrDeviceInfo_set_lensDistortionValues),
    JS_CGETSET_DEF("chromaAbCorrection",js_VrDeviceInfo_get_chromaAbCorrection,js_VrDeviceInfo_set_chromaAbCorrection),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","VrDeviceInfo", JS_PROP_CONFIGURABLE),
};

static int js_declare_VrDeviceInfo(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_VrDeviceInfo_class_id);
    JSClassDef js_VrDeviceInfo_def = { .class_name = "VrDeviceInfo", .finalizer = js_VrDeviceInfo_finalizer };
    JS_NewClass(rt, js_VrDeviceInfo_class_id, &js_VrDeviceInfo_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_VrDeviceInfo_proto_funcs, countof(js_VrDeviceInfo_proto_funcs));
    JS_SetClassProto(ctx, js_VrDeviceInfo_class_id, proto);
    return 0;
}

static void js_VrStereoConfig_finalizer(JSRuntime * rt, JSValue val) {
    VrStereoConfig* ptr = JS_GetOpaque(val, js_VrStereoConfig_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_VrStereoConfig_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","VrStereoConfig", JS_PROP_CONFIGURABLE),
};

static int js_declare_VrStereoConfig(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_VrStereoConfig_class_id);
    JSClassDef js_VrStereoConfig_def = { .class_name = "VrStereoConfig", .finalizer = js_VrStereoConfig_finalizer };
    JS_NewClass(rt, js_VrStereoConfig_class_id, &js_VrStereoConfig_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_VrStereoConfig_proto_funcs, countof(js_VrStereoConfig_proto_funcs));
    JS_SetClassProto(ctx, js_VrStereoConfig_class_id, proto);
    return 0;
}

static void js_FilePathList_finalizer(JSRuntime * rt, JSValue val) {
    FilePathList* ptr = JS_GetOpaque(val, js_FilePathList_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_FilePathList_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","FilePathList", JS_PROP_CONFIGURABLE),
};

static int js_declare_FilePathList(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_FilePathList_class_id);
    JSClassDef js_FilePathList_def = { .class_name = "FilePathList", .finalizer = js_FilePathList_finalizer };
    JS_NewClass(rt, js_FilePathList_class_id, &js_FilePathList_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_FilePathList_proto_funcs, countof(js_FilePathList_proto_funcs));
    JS_SetClassProto(ctx, js_FilePathList_class_id, proto);
    return 0;
}

static void js_AutomationEvent_finalizer(JSRuntime * rt, JSValue val) {
    AutomationEvent* ptr = JS_GetOpaque(val, js_AutomationEvent_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_AutomationEvent_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","AutomationEvent", JS_PROP_CONFIGURABLE),
};

static int js_declare_AutomationEvent(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_AutomationEvent_class_id);
    JSClassDef js_AutomationEvent_def = { .class_name = "AutomationEvent", .finalizer = js_AutomationEvent_finalizer };
    JS_NewClass(rt, js_AutomationEvent_class_id, &js_AutomationEvent_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_AutomationEvent_proto_funcs, countof(js_AutomationEvent_proto_funcs));
    JS_SetClassProto(ctx, js_AutomationEvent_class_id, proto);
    return 0;
}

static void js_AutomationEventList_finalizer(JSRuntime * rt, JSValue val) {
    AutomationEventList* ptr = JS_GetOpaque(val, js_AutomationEventList_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_AutomationEventList_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","AutomationEventList", JS_PROP_CONFIGURABLE),
};

static int js_declare_AutomationEventList(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_AutomationEventList_class_id);
    JSClassDef js_AutomationEventList_def = { .class_name = "AutomationEventList", .finalizer = js_AutomationEventList_finalizer };
    JS_NewClass(rt, js_AutomationEventList_class_id, &js_AutomationEventList_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_AutomationEventList_proto_funcs, countof(js_AutomationEventList_proto_funcs));
    JS_SetClassProto(ctx, js_AutomationEventList_class_id, proto);
    return 0;
}

static trampolineContext * LoadFileDataCallback_callback_arr = NULL;
static unsigned char * LoadFileDataCallback_callback_c(const char * arg_fileName, int * arg_dataSize) {
    JSValue func1;
    trampolineContext tctx = *LoadFileDataCallback_callback_arr;
    JSContext * ctx = tctx.ctx;
    JSValue js0;
    js0 = JS_NewString(ctx, arg_fileName);
    JSValue js1;
    js1 = JS_NewArray(ctx);
    JSValue js_js10 = JS_NewInt32(ctx, (long)arg_dataSize[0]);
    JS_DefinePropertyValueUint32(ctx,js1,0,js_js10,JS_PROP_C_W_E);
    JSValue argv[] = {js0,js1};
    JS_DupContext(ctx);
    JS_DupValue(ctx, tctx.func_obj);
    JSValue js_ret = JS_Call(ctx, tctx.func_obj, JS_UNDEFINED, 2, argv);
    JS_FreeValue(ctx, tctx.func_obj);
    JS_FreeContext(ctx);
    JS_FreeValue(ctx, argv[0]);
    int64_t size_arg_dataSize;
    if(JS_IsArray(js1) == 1) {
        if(JS_GetLength(ctx,js1,&size_arg_dataSize)==-1) {
            JS_FreeValue(ctx, js_ret);
            JS_FreeValue(ctx, argv[1]);
            return NULL;
        }
        if(size_arg_dataSize!=1) {
            JS_FreeValue(ctx, js_ret);
            JS_FreeValue(ctx, argv[1]);
            return NULL;
        }
        for(int i0=0; i0 < size_arg_dataSize; i0++){
            JSValue js_arg_dataSize = JS_GetPropertyUint32(ctx,js1,i0);
            int32_t long_arg_dataSizei0;
            int err_arg_dataSizei0 = JS_ToInt32(ctx, &long_arg_dataSizei0, js_arg_dataSize);
            if(err_arg_dataSizei0<0) {
                JS_ThrowTypeError(ctx, "js_arg_dataSize is not numeric");
                return NULL;
            }
            arg_dataSize[i0] = (int)long_arg_dataSizei0;
            JS_FreeValue(ctx, js_arg_dataSize);
        }
    }
    else {
    }
    unsigned char * resp;
    JSValue da_resp;
    int64_t size_resp;
    if(JS_IsArray(js_ret) == 1) {
        if(JS_GetLength(ctx,js_ret,&size_resp)==-1) {
            JS_FreeValue(ctx, js_ret);
            JS_FreeValue(ctx, argv[1]);
            return NULL;
        }
        resp = (unsigned char *)js_malloc(ctx, size_resp * sizeof(unsigned char));
        for(int i0=0; i0 < size_resp; i0++){
            JSValue js_resp = JS_GetPropertyUint32(ctx,js_ret,i0);
            uint32_t long_respi0;
            int err_respi0 = JS_ToUint32(ctx, &long_respi0, js_resp);
            if(err_respi0<0) {
                JS_ThrowTypeError(ctx, "js_resp is not numeric");
                return NULL;
            }
            resp[i0] = (unsigned char)long_respi0;
            JS_FreeValue(ctx, js_resp);
        }
    }
    else if(JS_IsArrayBuffer(js_ret) == 1) {
        da_resp = JS_DupValue(ctx,js_ret);
        size_t size_resp;
        resp = (unsigned char *)JS_GetArrayBuffer(ctx, &size_resp, da_resp);
    }
    else {
        JSClassID classid_resp = JS_GetClassID(js_ret);
        if(classid_resp==JS_CLASS_UINT8_ARRAY || classid_resp==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_resp;
            size_t size_resp;
            da_resp = JS_GetTypedArrayBuffer(ctx,js_ret,&offset_resp,&size_resp,NULL);
            resp = (unsigned char *)JS_GetArrayBuffer(ctx, &size_resp, da_resp);
            resp+=offset_resp;
            size_resp-=offset_resp;
        }
        else {
            JS_FreeValue(ctx, js_ret);
            JS_FreeValue(ctx, argv[1]);
            JS_ThrowTypeError(ctx, "js_ret does not match type unsigned char *");
            return NULL;
        }
    }
    JS_FreeValue(ctx, js_ret);
    JS_FreeValue(ctx, argv[1]);
    return resp;
}

static trampolineContext * SaveFileDataCallback_callback_arr = NULL;
static bool SaveFileDataCallback_callback_c(const char * arg_fileName, unsigned char * arg_data, int arg_dataSize) {
    JSValue func1;
    trampolineContext tctx = *SaveFileDataCallback_callback_arr;
    JSContext * ctx = tctx.ctx;
    JSValue js0;
    js0 = JS_NewString(ctx, arg_fileName);
    JSValue js1;
    js1 = JS_NewArray(ctx);
    for(int i0=0; i0 < arg_dataSize; i0++){
        JSValue js_js1 = JS_NewUint32(ctx, (unsigned long)arg_data[i0]);
        JS_DefinePropertyValueUint32(ctx,js1,i0,js_js1,JS_PROP_C_W_E);
    }
    JSValue js2 = JS_NewInt32(ctx, (long)arg_dataSize);
    JSValue argv[] = {js0,js1,js2};
    JS_DupContext(ctx);
    JS_DupValue(ctx, tctx.func_obj);
    JSValue js_ret = JS_Call(ctx, tctx.func_obj, JS_UNDEFINED, 3, argv);
    JS_FreeValue(ctx, tctx.func_obj);
    JS_FreeContext(ctx);
    JS_FreeValue(ctx, argv[0]);
    JS_FreeValue(ctx, argv[1]);
    JS_FreeValue(ctx, argv[2]);
    int js_resp = JS_ToBool(ctx, js_ret);
    if(js_resp<0) {
        JS_FreeValue(ctx, js_ret);
        JS_ThrowTypeError(ctx, "js_ret is not a bool");
        return false;
    }
    bool resp = js_resp;
    JS_FreeValue(ctx, js_ret);
    return resp;
}

static trampolineContext * LoadFileTextCallback_callback_arr = NULL;
static char * LoadFileTextCallback_callback_c(const char * arg_fileName) {
    JSValue func1;
    trampolineContext tctx = *LoadFileTextCallback_callback_arr;
    JSContext * ctx = tctx.ctx;
    JSValue js0;
    js0 = JS_NewString(ctx, arg_fileName);
    JSValue argv[] = {js0};
    JS_DupContext(ctx);
    JS_DupValue(ctx, tctx.func_obj);
    JSValue js_ret = JS_Call(ctx, tctx.func_obj, JS_UNDEFINED, 1, argv);
    JS_FreeValue(ctx, tctx.func_obj);
    JS_FreeContext(ctx);
    JS_FreeValue(ctx, argv[0]);
    char * resp;
    JSValue da_resp;
    int64_t size_resp;
    if(JS_IsString(js_ret) == 1) {
        resp = (char *)JS_ToCStringLen(ctx, &size_resp, js_ret);
    }
    else if(JS_IsArrayBuffer(js_ret) == 1) {
        da_resp = JS_DupValue(ctx,js_ret);
        size_t size_resp;
        resp = (char *)JS_GetArrayBuffer(ctx, &size_resp, da_resp);
    }
    else {
        JSClassID classid_resp = JS_GetClassID(js_ret);
        if(classid_resp==JS_CLASS_INT8_ARRAY) {
            size_t offset_resp;
            size_t size_resp;
            da_resp = JS_GetTypedArrayBuffer(ctx,js_ret,&offset_resp,&size_resp,NULL);
            resp = (char *)JS_GetArrayBuffer(ctx, &size_resp, da_resp);
            resp+=offset_resp;
            size_resp-=offset_resp;
        }
        else {
            JS_FreeValue(ctx, js_ret);
            JS_ThrowTypeError(ctx, "js_ret does not match type char *");
            return NULL;
        }
    }
    JS_FreeValue(ctx, js_ret);
    return resp;
}

static trampolineContext * SaveFileTextCallback_callback_arr = NULL;
static bool SaveFileTextCallback_callback_c(const char * arg_fileName, char * arg_text) {
    JSValue func1;
    trampolineContext tctx = *SaveFileTextCallback_callback_arr;
    JSContext * ctx = tctx.ctx;
    JSValue js0;
    js0 = JS_NewString(ctx, arg_fileName);
    JSValue js1;
    js1 = JS_NewString(ctx, arg_text);
    JSValue argv[] = {js0,js1};
    JS_DupContext(ctx);
    JS_DupValue(ctx, tctx.func_obj);
    JSValue js_ret = JS_Call(ctx, tctx.func_obj, JS_UNDEFINED, 2, argv);
    JS_FreeValue(ctx, tctx.func_obj);
    JS_FreeContext(ctx);
    JS_FreeValue(ctx, argv[0]);
    JS_FreeValue(ctx, argv[1]);
    int js_resp = JS_ToBool(ctx, js_ret);
    if(js_resp<0) {
        JS_FreeValue(ctx, js_ret);
        JS_ThrowTypeError(ctx, "js_ret is not a bool");
        return false;
    }
    bool resp = js_resp;
    JS_FreeValue(ctx, js_ret);
    return resp;
}

static trampolineContext * AudioMixedProcessor_processor_arr = NULL;
static JSContext * AudioMixedProcessor_processor_ctx = NULL;
static size_t AudioMixedProcessor_processor_size = 0;
static void AudioMixedProcessor_processor_c(float * arg_bufferData, unsigned int arg_frames) {
    JSValue js0;
    JSValue func1;
    for(int i=0; i < AudioMixedProcessor_processor_size; i++){
        trampolineContext tctx = AudioMixedProcessor_processor_arr[i];
        JSContext * ctx = AudioMixedProcessor_processor_ctx;
        if(i==0) {
            js0 = JS_NewArray(ctx);
            for(int i0=0; i0 < arg_frames*2; i0++){
                JSValue js_js0 = JS_NewFloat64(ctx, (double)arg_bufferData[i0]);
                JS_DefinePropertyValueUint32(ctx,js0,i0,js_js0,JS_PROP_C_W_E);
            }
        }
        JSValue js1 = JS_NewUint32(ctx, (unsigned long)arg_frames);
        JSValue argv[] = {tctx.func_obj,js0,js1};
        JSValue js_ret = js_postMessage(ctx, tctx.thread_id, 3, argv);
        JS_FreeValue(ctx, argv[2]);
        if(i==AudioMixedProcessor_processor_size-1) {
            int64_t size_arg_bufferData;
            if(JS_IsArray(js0) == 1) {
                if(JS_GetLength(ctx,js0,&size_arg_bufferData)==-1) {
                    JS_FreeValue(ctx, js_ret);
                    JS_FreeValue(ctx, argv[1]);
                    return  ;
                }
                if(size_arg_bufferData!=arg_frames*2) {
                    JS_FreeValue(ctx, js_ret);
                    JS_FreeValue(ctx, argv[1]);
                    return  ;
                }
                for(int i0=0; i0 < size_arg_bufferData; i0++){
                    JSValue js_arg_bufferData = JS_GetPropertyUint32(ctx,js0,i0);
                    double double_arg_bufferDatai0;
                    int err_arg_bufferDatai0 = JS_ToFloat64(ctx, &double_arg_bufferDatai0, js_arg_bufferData);
                    if(err_arg_bufferDatai0<0) {
                        JS_ThrowTypeError(ctx, "js_arg_bufferData is not numeric");
                        return  ;
                    }
                    arg_bufferData[i0] = (float)double_arg_bufferDatai0;
                    JS_FreeValue(ctx, js_arg_bufferData);
                }
            }
            else {
                JS_FreeValue(ctx, js_ret);
                JS_FreeValue(ctx, argv[1]);
                JS_ThrowTypeError(ctx, "js0 does not match type float *");
                return  ;
            }
            JS_FreeValue(ctx, js_ret);
            JS_FreeValue(ctx, argv[1]);
        }
    }
}

static JSValue js_Vector2_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        Vector2* ptr__return = (Vector2*)js_calloc(ctx, 1, sizeof(Vector2));
        JSValue _return = JS_NewObjectClass(ctx, js_Vector2_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    double double_x;
    int err_x = JS_ToFloat64(ctx, &double_x, argv[0]);
    if(err_x<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float x = (float)double_x;
    double double_y;
    int err_y = JS_ToFloat64(ctx, &double_y, argv[1]);
    if(err_y<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float y = (float)double_y;
    Vector2 _struct = { x, y };
    Vector2* ptr__return = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_Vector3_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        Vector3* ptr__return = (Vector3*)js_calloc(ctx, 1, sizeof(Vector3));
        JSValue _return = JS_NewObjectClass(ctx, js_Vector3_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    double double_x;
    int err_x = JS_ToFloat64(ctx, &double_x, argv[0]);
    if(err_x<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float x = (float)double_x;
    double double_y;
    int err_y = JS_ToFloat64(ctx, &double_y, argv[1]);
    if(err_y<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float y = (float)double_y;
    double double_z;
    int err_z = JS_ToFloat64(ctx, &double_z, argv[2]);
    if(err_z<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float z = (float)double_z;
    Vector3 _struct = { x, y, z };
    Vector3* ptr__return = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_Vector4_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        Vector4* ptr__return = (Vector4*)js_calloc(ctx, 1, sizeof(Vector4));
        JSValue _return = JS_NewObjectClass(ctx, js_Vector4_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    double double_x;
    int err_x = JS_ToFloat64(ctx, &double_x, argv[0]);
    if(err_x<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float x = (float)double_x;
    double double_y;
    int err_y = JS_ToFloat64(ctx, &double_y, argv[1]);
    if(err_y<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float y = (float)double_y;
    double double_z;
    int err_z = JS_ToFloat64(ctx, &double_z, argv[2]);
    if(err_z<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float z = (float)double_z;
    double double_w;
    int err_w = JS_ToFloat64(ctx, &double_w, argv[3]);
    if(err_w<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float w = (float)double_w;
    Vector4 _struct = { x, y, z, w };
    Vector4* ptr__return = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_Color_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        Color* ptr__return = (Color*)js_calloc(ctx, 1, sizeof(Color));
        JSValue _return = JS_NewObjectClass(ctx, js_Color_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    uint32_t long_r;
    int err_r = JS_ToUint32(ctx, &long_r, argv[0]);
    if(err_r<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned char r = (unsigned char)long_r;
    uint32_t long_g;
    int err_g = JS_ToUint32(ctx, &long_g, argv[1]);
    if(err_g<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned char g = (unsigned char)long_g;
    uint32_t long_b;
    int err_b = JS_ToUint32(ctx, &long_b, argv[2]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned char b = (unsigned char)long_b;
    uint32_t long_a;
    int err_a = JS_ToUint32(ctx, &long_a, argv[3]);
    if(err_a<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned char a = (unsigned char)long_a;
    Color _struct = { r, g, b, a };
    Color* ptr__return = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_Rectangle_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        Rectangle* ptr__return = (Rectangle*)js_calloc(ctx, 1, sizeof(Rectangle));
        JSValue _return = JS_NewObjectClass(ctx, js_Rectangle_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    double double_x;
    int err_x = JS_ToFloat64(ctx, &double_x, argv[0]);
    if(err_x<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float x = (float)double_x;
    double double_y;
    int err_y = JS_ToFloat64(ctx, &double_y, argv[1]);
    if(err_y<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float y = (float)double_y;
    double double_width;
    int err_width = JS_ToFloat64(ctx, &double_width, argv[2]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float width = (float)double_width;
    double double_height;
    int err_height = JS_ToFloat64(ctx, &double_height, argv[3]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float height = (float)double_height;
    Rectangle _struct = { x, y, width, height };
    Rectangle* ptr__return = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_Image_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        Image* ptr__return = (Image*)js_calloc(ctx, 1, sizeof(Image));
        JSValue _return = JS_NewObjectClass(ctx, js_Image_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    Image _struct = {  };
    Image* ptr__return = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_NPatchInfo_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        NPatchInfo* ptr__return = (NPatchInfo*)js_calloc(ctx, 1, sizeof(NPatchInfo));
        JSValue _return = JS_NewObjectClass(ctx, js_NPatchInfo_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    Rectangle* ptr_source = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_source == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle source = *ptr_source;
    int32_t long_left;
    int err_left = JS_ToInt32(ctx, &long_left, argv[1]);
    if(err_left<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int left = (int)long_left;
    int32_t long_top;
    int err_top = JS_ToInt32(ctx, &long_top, argv[2]);
    if(err_top<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int top = (int)long_top;
    int32_t long_right;
    int err_right = JS_ToInt32(ctx, &long_right, argv[3]);
    if(err_right<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int right = (int)long_right;
    int32_t long_bottom;
    int err_bottom = JS_ToInt32(ctx, &long_bottom, argv[4]);
    if(err_bottom<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int bottom = (int)long_bottom;
    int32_t long_layout;
    int err_layout = JS_ToInt32(ctx, &long_layout, argv[5]);
    if(err_layout<0) {
        JS_ThrowTypeError(ctx, "argv[5] is not numeric");
        return JS_EXCEPTION;
    }
    int layout = (int)long_layout;
    NPatchInfo _struct = { source, left, top, right, bottom, layout };
    NPatchInfo* ptr__return = (NPatchInfo*)js_malloc(ctx, sizeof(NPatchInfo));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_NPatchInfo_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_Camera3D_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        Camera3D* ptr__return = (Camera3D*)js_calloc(ctx, 1, sizeof(Camera3D));
        JSValue _return = JS_NewObjectClass(ctx, js_Camera3D_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Vector3* ptr_target = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_target == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 target = *ptr_target;
    Vector3* ptr_up = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_up == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 up = *ptr_up;
    double double_fovy;
    int err_fovy = JS_ToFloat64(ctx, &double_fovy, argv[3]);
    if(err_fovy<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float fovy = (float)double_fovy;
    int32_t long_projection;
    int err_projection = JS_ToInt32(ctx, &long_projection, argv[4]);
    if(err_projection<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int projection = (int)long_projection;
    Camera3D _struct = { position, target, up, fovy, projection };
    Camera3D* ptr__return = (Camera3D*)js_malloc(ctx, sizeof(Camera3D));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Camera3D_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_Camera2D_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        Camera2D* ptr__return = (Camera2D*)js_calloc(ctx, 1, sizeof(Camera2D));
        JSValue _return = JS_NewObjectClass(ctx, js_Camera2D_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    Vector2* ptr_offset = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_offset == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 offset = *ptr_offset;
    Vector2* ptr_target = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_target == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 target = *ptr_target;
    double double_rotation;
    int err_rotation = JS_ToFloat64(ctx, &double_rotation, argv[2]);
    if(err_rotation<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float rotation = (float)double_rotation;
    double double_zoom;
    int err_zoom = JS_ToFloat64(ctx, &double_zoom, argv[3]);
    if(err_zoom<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float zoom = (float)double_zoom;
    Camera2D _struct = { offset, target, rotation, zoom };
    Camera2D* ptr__return = (Camera2D*)js_malloc(ctx, sizeof(Camera2D));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Camera2D_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_Mesh_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        Mesh* ptr__return = (Mesh*)js_calloc(ctx, 1, sizeof(Mesh));
        JSValue _return = JS_NewObjectClass(ctx, js_Mesh_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    Mesh _struct = {  };
    Mesh* ptr__return = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_Ray_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        Ray* ptr__return = (Ray*)js_calloc(ctx, 1, sizeof(Ray));
        JSValue _return = JS_NewObjectClass(ctx, js_Ray_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Vector3* ptr_direction = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_direction == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 direction = *ptr_direction;
    Ray _struct = { position, direction };
    Ray* ptr__return = (Ray*)js_malloc(ctx, sizeof(Ray));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Ray_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_BoundingBox_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        BoundingBox* ptr__return = (BoundingBox*)js_calloc(ctx, 1, sizeof(BoundingBox));
        JSValue _return = JS_NewObjectClass(ctx, js_BoundingBox_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    Vector3* ptr_min = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_min == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 min = *ptr_min;
    Vector3* ptr_max = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_max == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 max = *ptr_max;
    BoundingBox _struct = { min, max };
    BoundingBox* ptr__return = (BoundingBox*)js_malloc(ctx, sizeof(BoundingBox));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_BoundingBox_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_VrDeviceInfo_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    if(argc==0) {
        VrDeviceInfo* ptr__return = (VrDeviceInfo*)js_calloc(ctx, 1, sizeof(VrDeviceInfo));
        JSValue _return = JS_NewObjectClass(ctx, js_VrDeviceInfo_class_id);
        JS_SetOpaque(_return, ptr__return);
        return _return;
    }
    VrDeviceInfo _struct = {  };
    VrDeviceInfo* ptr__return = (VrDeviceInfo*)js_malloc(ctx, sizeof(VrDeviceInfo));
    *ptr__return = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_VrDeviceInfo_class_id);
    JS_SetOpaque(_return, ptr__return);
    return _return;
}

static JSValue js_InitWindow(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    char * title;
    JSValue da_title;
    int64_t size_title;
    if(JS_IsString(argv[2]) == 1) {
        title = (char *)JS_ToCStringLen(ctx, &size_title, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        da_title = JS_DupValue(ctx,argv[2]);
        size_t size_title;
        title = (char *)JS_GetArrayBuffer(ctx, &size_title, da_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[2]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            size_t offset_title;
            size_t size_title;
            da_title = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_title,&size_title,NULL);
            title = (char *)JS_GetArrayBuffer(ctx, &size_title, da_title);
            title+=offset_title;
            size_title-=offset_title;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[2] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    InitWindow(width, height, (const char *)title);
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, title);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, title);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[2]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_title);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_CloseWindow(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    CloseWindow();
    return JS_UNDEFINED;
}

static JSValue js_WindowShouldClose(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = WindowShouldClose();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsWindowReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowReady();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsWindowFullscreen(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowFullscreen();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsWindowHidden(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowHidden();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsWindowMinimized(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowMinimized();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsWindowMaximized(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowMaximized();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsWindowFocused(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowFocused();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsWindowResized(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowResized();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsWindowState(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    uint32_t long_flag;
    int err_flag = JS_ToUint32(ctx, &long_flag, argv[0]);
    if(err_flag<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int flag = (unsigned int)long_flag;
    bool returnVal = IsWindowState(flag);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_SetWindowState(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    uint32_t long_flags;
    int err_flags = JS_ToUint32(ctx, &long_flags, argv[0]);
    if(err_flags<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int flags = (unsigned int)long_flags;
    SetWindowState(flags);
    return JS_UNDEFINED;
}

static JSValue js_ClearWindowState(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    uint32_t long_flags;
    int err_flags = JS_ToUint32(ctx, &long_flags, argv[0]);
    if(err_flags<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int flags = (unsigned int)long_flags;
    ClearWindowState(flags);
    return JS_UNDEFINED;
}

static JSValue js_ToggleFullscreen(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    ToggleFullscreen();
    return JS_UNDEFINED;
}

static JSValue js_ToggleBorderlessWindowed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    ToggleBorderlessWindowed();
    return JS_UNDEFINED;
}

static JSValue js_MaximizeWindow(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    MaximizeWindow();
    return JS_UNDEFINED;
}

static JSValue js_MinimizeWindow(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    MinimizeWindow();
    return JS_UNDEFINED;
}

static JSValue js_RestoreWindow(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    RestoreWindow();
    return JS_UNDEFINED;
}

static JSValue js_SetWindowIcon(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    SetWindowIcon(image);
    return JS_UNDEFINED;
}

static JSValue js_SetWindowTitle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * title;
    JSValue da_title;
    int64_t size_title;
    if(JS_IsString(argv[0]) == 1) {
        title = (char *)JS_ToCStringLen(ctx, &size_title, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_title = JS_DupValue(ctx,argv[0]);
        size_t size_title;
        title = (char *)JS_GetArrayBuffer(ctx, &size_title, da_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[0]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            size_t offset_title;
            size_t size_title;
            da_title = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_title,&size_title,NULL);
            title = (char *)JS_GetArrayBuffer(ctx, &size_title, da_title);
            title+=offset_title;
            size_title-=offset_title;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    SetWindowTitle((const char *)title);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, title);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, title);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[0]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_title);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_SetWindowPosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_x;
    int err_x = JS_ToInt32(ctx, &long_x, argv[0]);
    if(err_x<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int x = (int)long_x;
    int32_t long_y;
    int err_y = JS_ToInt32(ctx, &long_y, argv[1]);
    if(err_y<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int y = (int)long_y;
    SetWindowPosition(x, y);
    return JS_UNDEFINED;
}

static JSValue js_SetWindowMonitor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_monitor;
    int err_monitor = JS_ToInt32(ctx, &long_monitor, argv[0]);
    if(err_monitor<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int monitor = (int)long_monitor;
    SetWindowMonitor(monitor);
    return JS_UNDEFINED;
}

static JSValue js_SetWindowMinSize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    SetWindowMinSize(width, height);
    return JS_UNDEFINED;
}

static JSValue js_SetWindowMaxSize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    SetWindowMaxSize(width, height);
    return JS_UNDEFINED;
}

static JSValue js_SetWindowSize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    SetWindowSize(width, height);
    return JS_UNDEFINED;
}

static JSValue js_SetWindowOpacity(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_opacity;
    int err_opacity = JS_ToFloat64(ctx, &double_opacity, argv[0]);
    if(err_opacity<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float opacity = (float)double_opacity;
    SetWindowOpacity(opacity);
    return JS_UNDEFINED;
}

static JSValue js_SetWindowFocused(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    SetWindowFocused();
    return JS_UNDEFINED;
}

static JSValue js_GetScreenWidth(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetScreenWidth();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetScreenHeight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetScreenHeight();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetRenderWidth(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetRenderWidth();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetRenderHeight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetRenderHeight();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetMonitorCount(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetMonitorCount();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetCurrentMonitor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetCurrentMonitor();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetMonitorPosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_monitor;
    int err_monitor = JS_ToInt32(ctx, &long_monitor, argv[0]);
    if(err_monitor<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int monitor = (int)long_monitor;
    Vector2 returnVal = GetMonitorPosition(monitor);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetMonitorWidth(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_monitor;
    int err_monitor = JS_ToInt32(ctx, &long_monitor, argv[0]);
    if(err_monitor<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int monitor = (int)long_monitor;
    int returnVal = GetMonitorWidth(monitor);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetMonitorHeight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_monitor;
    int err_monitor = JS_ToInt32(ctx, &long_monitor, argv[0]);
    if(err_monitor<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int monitor = (int)long_monitor;
    int returnVal = GetMonitorHeight(monitor);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetMonitorPhysicalWidth(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_monitor;
    int err_monitor = JS_ToInt32(ctx, &long_monitor, argv[0]);
    if(err_monitor<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int monitor = (int)long_monitor;
    int returnVal = GetMonitorPhysicalWidth(monitor);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetMonitorPhysicalHeight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_monitor;
    int err_monitor = JS_ToInt32(ctx, &long_monitor, argv[0]);
    if(err_monitor<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int monitor = (int)long_monitor;
    int returnVal = GetMonitorPhysicalHeight(monitor);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetMonitorRefreshRate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_monitor;
    int err_monitor = JS_ToInt32(ctx, &long_monitor, argv[0]);
    if(err_monitor<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int monitor = (int)long_monitor;
    int returnVal = GetMonitorRefreshRate(monitor);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetWindowPosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetWindowPosition();
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetWindowScaleDPI(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetWindowScaleDPI();
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetMonitorName(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_monitor;
    int err_monitor = JS_ToInt32(ctx, &long_monitor, argv[0]);
    if(err_monitor<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int monitor = (int)long_monitor;
    const char * returnVal = GetMonitorName(monitor);
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_SetClipboardText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    SetClipboardText((const char *)text);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_GetClipboardText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    const char * returnVal = GetClipboardText();
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetClipboardImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image returnVal = GetClipboardImage();
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_EnableEventWaiting(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EnableEventWaiting();
    return JS_UNDEFINED;
}

static JSValue js_DisableEventWaiting(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    DisableEventWaiting();
    return JS_UNDEFINED;
}

static JSValue js_ShowCursor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    ShowCursor();
    return JS_UNDEFINED;
}

static JSValue js_HideCursor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    HideCursor();
    return JS_UNDEFINED;
}

static JSValue js_IsCursorHidden(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsCursorHidden();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_EnableCursor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EnableCursor();
    return JS_UNDEFINED;
}

static JSValue js_DisableCursor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    DisableCursor();
    return JS_UNDEFINED;
}

static JSValue js_IsCursorOnScreen(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsCursorOnScreen();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_ClearBackground(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_color = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ClearBackground(color);
    return JS_UNDEFINED;
}

static JSValue js_BeginDrawing(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    BeginDrawing();
    return JS_UNDEFINED;
}

static JSValue js_EndDrawing(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndDrawing();
    app_update_quickjs(ctx);
    return JS_UNDEFINED;
}

static JSValue js_BeginMode2D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera2D* ptr_camera = (Camera2D*)JS_GetOpaque(argv[0], js_Camera2D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Camera2D camera = *ptr_camera;
    BeginMode2D(camera);
    return JS_UNDEFINED;
}

static JSValue js_EndMode2D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndMode2D();
    return JS_UNDEFINED;
}

static JSValue js_BeginMode3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera3D* ptr_camera = (Camera3D*)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Camera3D camera = *ptr_camera;
    BeginMode3D(camera);
    return JS_UNDEFINED;
}

static JSValue js_EndMode3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndMode3D();
    return JS_UNDEFINED;
}

static JSValue js_BeginTextureMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    RenderTexture2D* ptr_target = (RenderTexture2D*)JS_GetOpaque(argv[0], js_RenderTexture_class_id);
    if(ptr_target == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    RenderTexture2D target = *ptr_target;
    BeginTextureMode(target);
    return JS_UNDEFINED;
}

static JSValue js_EndTextureMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndTextureMode();
    return JS_UNDEFINED;
}

static JSValue js_BeginShaderMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* ptr_shader = (Shader*)JS_GetOpaque(argv[0], js_Shader_class_id);
    if(ptr_shader == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Shader shader = *ptr_shader;
    BeginShaderMode(shader);
    return JS_UNDEFINED;
}

static JSValue js_EndShaderMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndShaderMode();
    return JS_UNDEFINED;
}

static JSValue js_BeginBlendMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_mode;
    int err_mode = JS_ToInt32(ctx, &long_mode, argv[0]);
    if(err_mode<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int mode = (int)long_mode;
    BeginBlendMode(mode);
    return JS_UNDEFINED;
}

static JSValue js_EndBlendMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndBlendMode();
    return JS_UNDEFINED;
}

static JSValue js_BeginScissorMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_x;
    int err_x = JS_ToInt32(ctx, &long_x, argv[0]);
    if(err_x<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int x = (int)long_x;
    int32_t long_y;
    int err_y = JS_ToInt32(ctx, &long_y, argv[1]);
    if(err_y<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int y = (int)long_y;
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[2]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[3]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    BeginScissorMode(x, y, width, height);
    return JS_UNDEFINED;
}

static JSValue js_EndScissorMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndScissorMode();
    return JS_UNDEFINED;
}

static JSValue js_BeginVrStereoMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    VrStereoConfig* ptr_config = (VrStereoConfig*)JS_GetOpaque(argv[0], js_VrStereoConfig_class_id);
    if(ptr_config == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    VrStereoConfig config = *ptr_config;
    BeginVrStereoMode(config);
    return JS_UNDEFINED;
}

static JSValue js_EndVrStereoMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndVrStereoMode();
    return JS_UNDEFINED;
}

static JSValue js_LoadVrStereoConfig(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    VrDeviceInfo* ptr_device = (VrDeviceInfo*)JS_GetOpaque(argv[0], js_VrDeviceInfo_class_id);
    if(ptr_device == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    VrDeviceInfo device = *ptr_device;
    VrStereoConfig returnVal = LoadVrStereoConfig(device);
    VrStereoConfig* ptr_ret = (VrStereoConfig*)js_malloc(ctx, sizeof(VrStereoConfig));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_VrStereoConfig_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_UnloadVrStereoConfig(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    VrStereoConfig* ptr_config = (VrStereoConfig*)JS_GetOpaque(argv[0], js_VrStereoConfig_class_id);
    if(ptr_config == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    VrStereoConfig config = *ptr_config;
    UnloadVrStereoConfig(config);
    return JS_UNDEFINED;
}

static JSValue js_LoadShader(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * vsFileName;
    int64_t size_vsFileName;
    if(JS_IsNull(argv[0]) || JS_IsUndefined(argv[0])) {
        vsFileName = NULL;
    }
    else if(JS_IsString(argv[0]) == 1) {
        vsFileName = (char *)JS_ToCStringLen(ctx, &size_vsFileName, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, vsFileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_vsFileName = JS_DupValue(ctx,argv[0]);
        size_t size_vsFileName;
        vsFileName = (char *)JS_GetArrayBuffer(ctx, &size_vsFileName, da_vsFileName);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_vsFileName);
    }
    else {
        JSClassID classid_vsFileName = JS_GetClassID(argv[0]);
        if(classid_vsFileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_vsFileName;
            size_t size_vsFileName;
            JSValue da_vsFileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_vsFileName,&size_vsFileName,NULL);
            vsFileName = (char *)JS_GetArrayBuffer(ctx, &size_vsFileName, da_vsFileName);
            vsFileName+=offset_vsFileName;
            size_vsFileName-=offset_vsFileName;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_vsFileName);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * fsFileName;
    int64_t size_fsFileName;
    if(JS_IsString(argv[1]) == 1) {
        fsFileName = (char *)JS_ToCStringLen(ctx, &size_fsFileName, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, fsFileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_fsFileName = JS_DupValue(ctx,argv[1]);
        size_t size_fsFileName;
        fsFileName = (char *)JS_GetArrayBuffer(ctx, &size_fsFileName, da_fsFileName);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fsFileName);
    }
    else {
        JSClassID classid_fsFileName = JS_GetClassID(argv[1]);
        if(classid_fsFileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fsFileName;
            size_t size_fsFileName;
            JSValue da_fsFileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fsFileName,&size_fsFileName,NULL);
            fsFileName = (char *)JS_GetArrayBuffer(ctx, &size_fsFileName, da_fsFileName);
            fsFileName+=offset_fsFileName;
            size_fsFileName-=offset_fsFileName;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fsFileName);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Shader returnVal = LoadShader((const char *)vsFileName, (const char *)fsFileName);
    memoryClear(ctx, memoryHead);
    Shader* ptr_ret = (Shader*)js_malloc(ctx, sizeof(Shader));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Shader_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadShaderFromMemory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * vsCode;
    int64_t size_vsCode;
    if(JS_IsString(argv[0]) == 1) {
        vsCode = (char *)JS_ToCStringLen(ctx, &size_vsCode, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, vsCode);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_vsCode = JS_DupValue(ctx,argv[0]);
        size_t size_vsCode;
        vsCode = (char *)JS_GetArrayBuffer(ctx, &size_vsCode, da_vsCode);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_vsCode);
    }
    else {
        JSClassID classid_vsCode = JS_GetClassID(argv[0]);
        if(classid_vsCode==JS_CLASS_INT8_ARRAY) {
            size_t offset_vsCode;
            size_t size_vsCode;
            JSValue da_vsCode = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_vsCode,&size_vsCode,NULL);
            vsCode = (char *)JS_GetArrayBuffer(ctx, &size_vsCode, da_vsCode);
            vsCode+=offset_vsCode;
            size_vsCode-=offset_vsCode;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_vsCode);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * fsCode;
    int64_t size_fsCode;
    if(JS_IsString(argv[1]) == 1) {
        fsCode = (char *)JS_ToCStringLen(ctx, &size_fsCode, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, fsCode);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_fsCode = JS_DupValue(ctx,argv[1]);
        size_t size_fsCode;
        fsCode = (char *)JS_GetArrayBuffer(ctx, &size_fsCode, da_fsCode);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fsCode);
    }
    else {
        JSClassID classid_fsCode = JS_GetClassID(argv[1]);
        if(classid_fsCode==JS_CLASS_INT8_ARRAY) {
            size_t offset_fsCode;
            size_t size_fsCode;
            JSValue da_fsCode = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fsCode,&size_fsCode,NULL);
            fsCode = (char *)JS_GetArrayBuffer(ctx, &size_fsCode, da_fsCode);
            fsCode+=offset_fsCode;
            size_fsCode-=offset_fsCode;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fsCode);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Shader returnVal = LoadShaderFromMemory((const char *)vsCode, (const char *)fsCode);
    memoryClear(ctx, memoryHead);
    Shader* ptr_ret = (Shader*)js_malloc(ctx, sizeof(Shader));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Shader_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_IsShaderValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* ptr_shader = (Shader*)JS_GetOpaque(argv[0], js_Shader_class_id);
    if(ptr_shader == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Shader shader = *ptr_shader;
    bool returnVal = IsShaderValid(shader);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_GetShaderLocation(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* ptr_shader = (Shader*)JS_GetOpaque(argv[0], js_Shader_class_id);
    if(ptr_shader == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Shader shader = *ptr_shader;
    char * uniformName;
    JSValue da_uniformName;
    int64_t size_uniformName;
    if(JS_IsString(argv[1]) == 1) {
        uniformName = (char *)JS_ToCStringLen(ctx, &size_uniformName, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_uniformName = JS_DupValue(ctx,argv[1]);
        size_t size_uniformName;
        uniformName = (char *)JS_GetArrayBuffer(ctx, &size_uniformName, da_uniformName);
    }
    else {
        JSClassID classid_uniformName = JS_GetClassID(argv[1]);
        if(classid_uniformName==JS_CLASS_INT8_ARRAY) {
            size_t offset_uniformName;
            size_t size_uniformName;
            da_uniformName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_uniformName,&size_uniformName,NULL);
            uniformName = (char *)JS_GetArrayBuffer(ctx, &size_uniformName, da_uniformName);
            uniformName+=offset_uniformName;
            size_uniformName-=offset_uniformName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int returnVal = GetShaderLocation(shader, (const char *)uniformName);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, uniformName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, uniformName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_uniformName);
    }
    else {
        JSClassID classid_uniformName = JS_GetClassID(argv[1]);
        if(classid_uniformName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_uniformName);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetShaderLocationAttrib(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* ptr_shader = (Shader*)JS_GetOpaque(argv[0], js_Shader_class_id);
    if(ptr_shader == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Shader shader = *ptr_shader;
    char * attribName;
    JSValue da_attribName;
    int64_t size_attribName;
    if(JS_IsString(argv[1]) == 1) {
        attribName = (char *)JS_ToCStringLen(ctx, &size_attribName, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_attribName = JS_DupValue(ctx,argv[1]);
        size_t size_attribName;
        attribName = (char *)JS_GetArrayBuffer(ctx, &size_attribName, da_attribName);
    }
    else {
        JSClassID classid_attribName = JS_GetClassID(argv[1]);
        if(classid_attribName==JS_CLASS_INT8_ARRAY) {
            size_t offset_attribName;
            size_t size_attribName;
            da_attribName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_attribName,&size_attribName,NULL);
            attribName = (char *)JS_GetArrayBuffer(ctx, &size_attribName, da_attribName);
            attribName+=offset_attribName;
            size_attribName-=offset_attribName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int returnVal = GetShaderLocationAttrib(shader, (const char *)attribName);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, attribName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, attribName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_attribName);
    }
    else {
        JSClassID classid_attribName = JS_GetClassID(argv[1]);
        if(classid_attribName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_attribName);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_SetShaderValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* ptr_shader = (Shader*)JS_GetOpaque(argv[0], js_Shader_class_id);
    if(ptr_shader == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Shader shader = *ptr_shader;
    int32_t long_locIndex;
    int err_locIndex = JS_ToInt32(ctx, &long_locIndex, argv[1]);
    if(err_locIndex<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int locIndex = (int)long_locIndex;
    void * value = NULL;
    JSValue da_value;
    int32_t long_uniformType;
    int err_uniformType = JS_ToInt32(ctx, &long_uniformType, argv[3]);
    if(err_uniformType<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int uniformType = (int)long_uniformType;
    switch(uniformType) {
        case SHADER_UNIFORM_FLOAT:{
            float * val;
            JSValue da_val;
            int64_t size_val;
            if(JS_IsArray(argv[2]) == 1) {
                if(JS_GetLength(ctx,argv[2],&size_val)==-1) {
                    return JS_EXCEPTION;
                }
                val = (float *)js_malloc(ctx, size_val * sizeof(float));
                for(int i0=0; i0 < size_val; i0++){
                    JSValue js_val = JS_GetPropertyUint32(ctx,argv[2],i0);
                    double double_vali0;
                    int err_vali0 = JS_ToFloat64(ctx, &double_vali0, js_val);
                    if(err_vali0<0) {
                        JS_ThrowTypeError(ctx, "js_val is not numeric");
                        return JS_EXCEPTION;
                    }
                    val[i0] = (float)double_vali0;
                    JS_FreeValue(ctx, js_val);
                }
            }
            else if(JS_IsArrayBuffer(argv[2]) == 1) {
                da_val = JS_DupValue(ctx,argv[2]);
                size_t size_val;
                val = (float *)JS_GetArrayBuffer(ctx, &size_val, da_val);
            }
            else {
                JSClassID classid_val = JS_GetClassID(argv[2]);
                if(classid_val==JS_CLASS_FLOAT32_ARRAY) {
                    size_t offset_val;
                    size_t size_val;
                    da_val = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_val,&size_val,NULL);
                    val = (float *)JS_GetArrayBuffer(ctx, &size_val, da_val);
                    val+=offset_val;
                    size_val-=offset_val;
                }
                else {
                    double double_js_val;
                    int err_js_val = JS_ToFloat64(ctx, &double_js_val, argv[2]);
                    if(err_js_val<0) {
                        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
                        return JS_EXCEPTION;
                    }
                    float js_val = (float)double_js_val;
                    val = &js_val;
                }
            }
            value = (void *)val;
            da_value = da_val;
            break;
        }
        case SHADER_UNIFORM_VEC2:{
            float * val;
            JSValue da_val;
            int64_t size_val;
            if(JS_IsArray(argv[2]) == 1) {
                val = (float *)js_malloc(ctx, 2 * sizeof(float));
                for(int i0=0; i0 < 2; i0++){
                    JSValue js_val = JS_GetPropertyUint32(ctx,argv[2],i0);
                    double double_vali0;
                    int err_vali0 = JS_ToFloat64(ctx, &double_vali0, js_val);
                    if(err_vali0<0) {
                        JS_ThrowTypeError(ctx, "js_val is not numeric");
                        return JS_EXCEPTION;
                    }
                    val[i0] = (float)double_vali0;
                    JS_FreeValue(ctx, js_val);
                }
            }
            else if(JS_IsArrayBuffer(argv[2]) == 1) {
                da_val = JS_DupValue(ctx,argv[2]);
                size_t size_val;
                val = (float *)JS_GetArrayBuffer(ctx, &size_val, da_val);
            }
            else {
                JSClassID classid_val = JS_GetClassID(argv[2]);
                if(classid_val==JS_CLASS_FLOAT32_ARRAY) {
                    size_t offset_val;
                    size_t size_val;
                    da_val = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_val,&size_val,NULL);
                    val = (float *)JS_GetArrayBuffer(ctx, &size_val, da_val);
                    val+=offset_val;
                    size_val-=offset_val;
                }
                else {
                    JS_ThrowTypeError(ctx, "argv[2] does not match type float *");
                    return JS_EXCEPTION;
                }
            }
            value = (void *)val;
            da_value = da_val;
            break;
        }
        case SHADER_UNIFORM_VEC3:{
            float * val;
            JSValue da_val;
            int64_t size_val;
            if(JS_IsArray(argv[2]) == 1) {
                val = (float *)js_malloc(ctx, 3 * sizeof(float));
                for(int i0=0; i0 < 3; i0++){
                    JSValue js_val = JS_GetPropertyUint32(ctx,argv[2],i0);
                    double double_vali0;
                    int err_vali0 = JS_ToFloat64(ctx, &double_vali0, js_val);
                    if(err_vali0<0) {
                        JS_ThrowTypeError(ctx, "js_val is not numeric");
                        return JS_EXCEPTION;
                    }
                    val[i0] = (float)double_vali0;
                    JS_FreeValue(ctx, js_val);
                }
            }
            else if(JS_IsArrayBuffer(argv[2]) == 1) {
                da_val = JS_DupValue(ctx,argv[2]);
                size_t size_val;
                val = (float *)JS_GetArrayBuffer(ctx, &size_val, da_val);
            }
            else {
                JSClassID classid_val = JS_GetClassID(argv[2]);
                if(classid_val==JS_CLASS_FLOAT32_ARRAY) {
                    size_t offset_val;
                    size_t size_val;
                    da_val = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_val,&size_val,NULL);
                    val = (float *)JS_GetArrayBuffer(ctx, &size_val, da_val);
                    val+=offset_val;
                    size_val-=offset_val;
                }
                else {
                    JS_ThrowTypeError(ctx, "argv[2] does not match type float *");
                    return JS_EXCEPTION;
                }
            }
            value = (void *)val;
            da_value = da_val;
            break;
        }
        case SHADER_UNIFORM_VEC4:{
            float * val;
            JSValue da_val;
            int64_t size_val;
            if(JS_IsArray(argv[2]) == 1) {
                val = (float *)js_malloc(ctx, 4 * sizeof(float));
                for(int i0=0; i0 < 4; i0++){
                    JSValue js_val = JS_GetPropertyUint32(ctx,argv[2],i0);
                    double double_vali0;
                    int err_vali0 = JS_ToFloat64(ctx, &double_vali0, js_val);
                    if(err_vali0<0) {
                        JS_ThrowTypeError(ctx, "js_val is not numeric");
                        return JS_EXCEPTION;
                    }
                    val[i0] = (float)double_vali0;
                    JS_FreeValue(ctx, js_val);
                }
            }
            else if(JS_IsArrayBuffer(argv[2]) == 1) {
                da_val = JS_DupValue(ctx,argv[2]);
                size_t size_val;
                val = (float *)JS_GetArrayBuffer(ctx, &size_val, da_val);
            }
            else {
                JSClassID classid_val = JS_GetClassID(argv[2]);
                if(classid_val==JS_CLASS_FLOAT32_ARRAY) {
                    size_t offset_val;
                    size_t size_val;
                    da_val = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_val,&size_val,NULL);
                    val = (float *)JS_GetArrayBuffer(ctx, &size_val, da_val);
                    val+=offset_val;
                    size_val-=offset_val;
                }
                else {
                    JS_ThrowTypeError(ctx, "argv[2] does not match type float *");
                    return JS_EXCEPTION;
                }
            }
            value = (void *)val;
            da_value = da_val;
            break;
        }
        case SHADER_UNIFORM_INT:
        case SHADER_UNIFORM_SAMPLER2D:{
            int * val;
            JSValue da_val;
            int64_t size_val;
            if(JS_IsArray(argv[2]) == 1) {
                if(JS_GetLength(ctx,argv[2],&size_val)==-1) {
                    return JS_EXCEPTION;
                }
                val = (int *)js_malloc(ctx, size_val * sizeof(int));
                for(int i0=0; i0 < size_val; i0++){
                    JSValue js_val = JS_GetPropertyUint32(ctx,argv[2],i0);
                    int32_t long_vali0;
                    int err_vali0 = JS_ToInt32(ctx, &long_vali0, js_val);
                    if(err_vali0<0) {
                        JS_ThrowTypeError(ctx, "js_val is not numeric");
                        return JS_EXCEPTION;
                    }
                    val[i0] = (int)long_vali0;
                    JS_FreeValue(ctx, js_val);
                }
            }
            else if(JS_IsArrayBuffer(argv[2]) == 1) {
                da_val = JS_DupValue(ctx,argv[2]);
                size_t size_val;
                val = (int *)JS_GetArrayBuffer(ctx, &size_val, da_val);
            }
            else {
                JSClassID classid_val = JS_GetClassID(argv[2]);
                if(classid_val==JS_CLASS_INT16_ARRAY) {
                    size_t offset_val;
                    size_t size_val;
                    da_val = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_val,&size_val,NULL);
                    val = (int *)JS_GetArrayBuffer(ctx, &size_val, da_val);
                    val+=offset_val;
                    size_val-=offset_val;
                }
                else {
                    int32_t long_js_val;
                    int err_js_val = JS_ToInt32(ctx, &long_js_val, argv[2]);
                    if(err_js_val<0) {
                        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
                        return JS_EXCEPTION;
                    }
                    int js_val = (int)long_js_val;
                    val = &js_val;
                }
            }
            value = (void *)val;
            da_value = da_val;
            break;
        }
        case SHADER_UNIFORM_IVEC2:{
            int * val;
            JSValue da_val;
            int64_t size_val;
            if(JS_IsArray(argv[2]) == 1) {
                val = (int *)js_malloc(ctx, 2 * sizeof(int));
                for(int i0=0; i0 < 2; i0++){
                    JSValue js_val = JS_GetPropertyUint32(ctx,argv[2],i0);
                    int32_t long_vali0;
                    int err_vali0 = JS_ToInt32(ctx, &long_vali0, js_val);
                    if(err_vali0<0) {
                        JS_ThrowTypeError(ctx, "js_val is not numeric");
                        return JS_EXCEPTION;
                    }
                    val[i0] = (int)long_vali0;
                    JS_FreeValue(ctx, js_val);
                }
            }
            else if(JS_IsArrayBuffer(argv[2]) == 1) {
                da_val = JS_DupValue(ctx,argv[2]);
                size_t size_val;
                val = (int *)JS_GetArrayBuffer(ctx, &size_val, da_val);
            }
            else {
                JSClassID classid_val = JS_GetClassID(argv[2]);
                if(classid_val==JS_CLASS_INT16_ARRAY) {
                    size_t offset_val;
                    size_t size_val;
                    da_val = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_val,&size_val,NULL);
                    val = (int *)JS_GetArrayBuffer(ctx, &size_val, da_val);
                    val+=offset_val;
                    size_val-=offset_val;
                }
                else {
                    JS_ThrowTypeError(ctx, "argv[2] does not match type int *");
                    return JS_EXCEPTION;
                }
            }
            value = (void *)val;
            da_value = da_val;
            break;
        }
        case SHADER_UNIFORM_IVEC3:{
            int * val;
            JSValue da_val;
            int64_t size_val;
            if(JS_IsArray(argv[2]) == 1) {
                val = (int *)js_malloc(ctx, 3 * sizeof(int));
                for(int i0=0; i0 < 3; i0++){
                    JSValue js_val = JS_GetPropertyUint32(ctx,argv[2],i0);
                    int32_t long_vali0;
                    int err_vali0 = JS_ToInt32(ctx, &long_vali0, js_val);
                    if(err_vali0<0) {
                        JS_ThrowTypeError(ctx, "js_val is not numeric");
                        return JS_EXCEPTION;
                    }
                    val[i0] = (int)long_vali0;
                    JS_FreeValue(ctx, js_val);
                }
            }
            else if(JS_IsArrayBuffer(argv[2]) == 1) {
                da_val = JS_DupValue(ctx,argv[2]);
                size_t size_val;
                val = (int *)JS_GetArrayBuffer(ctx, &size_val, da_val);
            }
            else {
                JSClassID classid_val = JS_GetClassID(argv[2]);
                if(classid_val==JS_CLASS_INT16_ARRAY) {
                    size_t offset_val;
                    size_t size_val;
                    da_val = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_val,&size_val,NULL);
                    val = (int *)JS_GetArrayBuffer(ctx, &size_val, da_val);
                    val+=offset_val;
                    size_val-=offset_val;
                }
                else {
                    JS_ThrowTypeError(ctx, "argv[2] does not match type int *");
                    return JS_EXCEPTION;
                }
            }
            value = (void *)val;
            da_value = da_val;
            break;
        }
        case SHADER_UNIFORM_IVEC4:{
            int * val;
            JSValue da_val;
            int64_t size_val;
            if(JS_IsArray(argv[2]) == 1) {
                val = (int *)js_malloc(ctx, 4 * sizeof(int));
                for(int i0=0; i0 < 4; i0++){
                    JSValue js_val = JS_GetPropertyUint32(ctx,argv[2],i0);
                    int32_t long_vali0;
                    int err_vali0 = JS_ToInt32(ctx, &long_vali0, js_val);
                    if(err_vali0<0) {
                        JS_ThrowTypeError(ctx, "js_val is not numeric");
                        return JS_EXCEPTION;
                    }
                    val[i0] = (int)long_vali0;
                    JS_FreeValue(ctx, js_val);
                }
            }
            else if(JS_IsArrayBuffer(argv[2]) == 1) {
                da_val = JS_DupValue(ctx,argv[2]);
                size_t size_val;
                val = (int *)JS_GetArrayBuffer(ctx, &size_val, da_val);
            }
            else {
                JSClassID classid_val = JS_GetClassID(argv[2]);
                if(classid_val==JS_CLASS_INT16_ARRAY) {
                    size_t offset_val;
                    size_t size_val;
                    da_val = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_val,&size_val,NULL);
                    val = (int *)JS_GetArrayBuffer(ctx, &size_val, da_val);
                    val+=offset_val;
                    size_val-=offset_val;
                }
                else {
                    JS_ThrowTypeError(ctx, "argv[2] does not match type int *");
                    return JS_EXCEPTION;
                }
            }
            value = (void *)val;
            da_value = da_val;
            break;
        }
        default:{
            JS_ThrowTypeError(ctx, "unknown uniformType");
            return JS_EXCEPTION;
            break;
        }
    }
    SetShaderValue(shader, locIndex, value, uniformType);
    if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_value);
    }
    return JS_UNDEFINED;
}

static JSValue js_SetShaderValueV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* ptr_shader = (Shader*)JS_GetOpaque(argv[0], js_Shader_class_id);
    if(ptr_shader == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Shader shader = *ptr_shader;
    int32_t long_locIndex;
    int err_locIndex = JS_ToInt32(ctx, &long_locIndex, argv[1]);
    if(err_locIndex<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int locIndex = (int)long_locIndex;
    int32_t long_uniformType;
    int err_uniformType = JS_ToInt32(ctx, &long_uniformType, argv[3]);
    if(err_uniformType<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int uniformType = (int)long_uniformType;
    int32_t long_count;
    int err_count = JS_ToInt32(ctx, &long_count, argv[4]);
    if(err_count<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int count = (int)long_count;
    void * value = NULL;
    JSValue da_value;
    switch(uniformType) {
        case SHADER_UNIFORM_FLOAT:
        case SHADER_UNIFORM_VEC2:
        case SHADER_UNIFORM_VEC3:
        case SHADER_UNIFORM_VEC4:{
            float * val;
            JSValue da_val;
            int64_t size_val;
            if(JS_IsArray(argv[2]) == 1) {
                if(JS_GetLength(ctx,argv[2],&size_val)==-1) {
                    return JS_EXCEPTION;
                }
                val = (float *)js_malloc(ctx, size_val * sizeof(float));
                for(int i0=0; i0 < size_val; i0++){
                    JSValue js_val = JS_GetPropertyUint32(ctx,argv[2],i0);
                    double double_vali0;
                    int err_vali0 = JS_ToFloat64(ctx, &double_vali0, js_val);
                    if(err_vali0<0) {
                        JS_ThrowTypeError(ctx, "js_val is not numeric");
                        return JS_EXCEPTION;
                    }
                    val[i0] = (float)double_vali0;
                    JS_FreeValue(ctx, js_val);
                }
            }
            else if(JS_IsArrayBuffer(argv[2]) == 1) {
                da_val = JS_DupValue(ctx,argv[2]);
                size_t size_val;
                val = (float *)JS_GetArrayBuffer(ctx, &size_val, da_val);
            }
            else {
                JSClassID classid_val = JS_GetClassID(argv[2]);
                if(classid_val==JS_CLASS_FLOAT32_ARRAY) {
                    size_t offset_val;
                    size_t size_val;
                    da_val = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_val,&size_val,NULL);
                    val = (float *)JS_GetArrayBuffer(ctx, &size_val, da_val);
                    val+=offset_val;
                    size_val-=offset_val;
                }
                else {
                    JS_ThrowTypeError(ctx, "argv[2] does not match type float *");
                    return JS_EXCEPTION;
                }
            }
            value = (void *)val;
            da_value = da_val;
            break;
        }
        case SHADER_UNIFORM_INT:
        case SHADER_UNIFORM_SAMPLER2D:
        case SHADER_UNIFORM_IVEC2:
        case SHADER_UNIFORM_IVEC3:
        case SHADER_UNIFORM_IVEC4:{
            int * val;
            JSValue da_val;
            int64_t size_val;
            if(JS_IsArray(argv[2]) == 1) {
                if(JS_GetLength(ctx,argv[2],&size_val)==-1) {
                    return JS_EXCEPTION;
                }
                val = (int *)js_malloc(ctx, size_val * sizeof(int));
                for(int i0=0; i0 < size_val; i0++){
                    JSValue js_val = JS_GetPropertyUint32(ctx,argv[2],i0);
                    int32_t long_vali0;
                    int err_vali0 = JS_ToInt32(ctx, &long_vali0, js_val);
                    if(err_vali0<0) {
                        JS_ThrowTypeError(ctx, "js_val is not numeric");
                        return JS_EXCEPTION;
                    }
                    val[i0] = (int)long_vali0;
                    JS_FreeValue(ctx, js_val);
                }
            }
            else if(JS_IsArrayBuffer(argv[2]) == 1) {
                da_val = JS_DupValue(ctx,argv[2]);
                size_t size_val;
                val = (int *)JS_GetArrayBuffer(ctx, &size_val, da_val);
            }
            else {
                JSClassID classid_val = JS_GetClassID(argv[2]);
                if(classid_val==JS_CLASS_INT16_ARRAY) {
                    size_t offset_val;
                    size_t size_val;
                    da_val = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_val,&size_val,NULL);
                    val = (int *)JS_GetArrayBuffer(ctx, &size_val, da_val);
                    val+=offset_val;
                    size_val-=offset_val;
                }
                else {
                    JS_ThrowTypeError(ctx, "argv[2] does not match type int *");
                    return JS_EXCEPTION;
                }
            }
            value = (void*)val;
            da_value = da_val;
            break;
        }
        default:{
            JS_ThrowTypeError(ctx, "unknown uniformType");
            return JS_EXCEPTION;
            break;
        }
    }
    SetShaderValueV(shader, locIndex, value, uniformType, count);
    if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_value);
    }
    return JS_UNDEFINED;
}

static JSValue js_SetShaderValueMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* ptr_shader = (Shader*)JS_GetOpaque(argv[0], js_Shader_class_id);
    if(ptr_shader == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Shader shader = *ptr_shader;
    int32_t long_locIndex;
    int err_locIndex = JS_ToInt32(ctx, &long_locIndex, argv[1]);
    if(err_locIndex<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int locIndex = (int)long_locIndex;
    Matrix* ptr_mat = (Matrix*)JS_GetOpaque(argv[2], js_Matrix_class_id);
    if(ptr_mat == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix mat = *ptr_mat;
    SetShaderValueMatrix(shader, locIndex, mat);
    return JS_UNDEFINED;
}

static JSValue js_SetShaderValueTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* ptr_shader = (Shader*)JS_GetOpaque(argv[0], js_Shader_class_id);
    if(ptr_shader == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Shader shader = *ptr_shader;
    int32_t long_locIndex;
    int err_locIndex = JS_ToInt32(ctx, &long_locIndex, argv[1]);
    if(err_locIndex<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int locIndex = (int)long_locIndex;
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[2], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    SetShaderValueTexture(shader, locIndex, texture);
    return JS_UNDEFINED;
}

static JSValue js_UnloadShader(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* ptr_shader = (Shader*)JS_GetOpaque(argv[0], js_Shader_class_id);
    if(ptr_shader == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Shader shader = *ptr_shader;
    UnloadShader(shader);
    return JS_UNDEFINED;
}

static JSValue js_GetScreenToWorldRay(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    Camera* ptr_camera = (Camera*)JS_GetOpaque(argv[1], js_Camera3D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Camera camera = *ptr_camera;
    Ray returnVal = GetScreenToWorldRay(position, camera);
    Ray* ptr_ret = (Ray*)js_malloc(ctx, sizeof(Ray));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Ray_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetScreenToWorldRayEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    Camera* ptr_camera = (Camera*)JS_GetOpaque(argv[1], js_Camera3D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Camera camera = *ptr_camera;
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[2]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[3]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    Ray returnVal = GetScreenToWorldRayEx(position, camera, width, height);
    Ray* ptr_ret = (Ray*)js_malloc(ctx, sizeof(Ray));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Ray_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetWorldToScreen(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Camera* ptr_camera = (Camera*)JS_GetOpaque(argv[1], js_Camera3D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Camera camera = *ptr_camera;
    Vector2 returnVal = GetWorldToScreen(position, camera);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetWorldToScreenEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Camera* ptr_camera = (Camera*)JS_GetOpaque(argv[1], js_Camera3D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Camera camera = *ptr_camera;
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[2]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[3]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    Vector2 returnVal = GetWorldToScreenEx(position, camera, width, height);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetWorldToScreen2D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    Camera2D* ptr_camera = (Camera2D*)JS_GetOpaque(argv[1], js_Camera2D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Camera2D camera = *ptr_camera;
    Vector2 returnVal = GetWorldToScreen2D(position, camera);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetScreenToWorld2D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    Camera2D* ptr_camera = (Camera2D*)JS_GetOpaque(argv[1], js_Camera2D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Camera2D camera = *ptr_camera;
    Vector2 returnVal = GetScreenToWorld2D(position, camera);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetCameraMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* ptr_camera = (Camera*)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Camera camera = *ptr_camera;
    Matrix returnVal = GetCameraMatrix(camera);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetCameraMatrix2D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera2D* ptr_camera = (Camera2D*)JS_GetOpaque(argv[0], js_Camera2D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Camera2D camera = *ptr_camera;
    Matrix returnVal = GetCameraMatrix2D(camera);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_SetTargetFPS(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_fps;
    int err_fps = JS_ToInt32(ctx, &long_fps, argv[0]);
    if(err_fps<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int fps = (int)long_fps;
    SetTargetFPS(fps);
    return JS_UNDEFINED;
}

static JSValue js_GetFrameTime(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetFrameTime();
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_GetTime(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double returnVal = GetTime();
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_GetFPS(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetFPS();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_SetRandomSeed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    uint32_t long_seed;
    int err_seed = JS_ToUint32(ctx, &long_seed, argv[0]);
    if(err_seed<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int seed = (unsigned int)long_seed;
    SetRandomSeed(seed);
    return JS_UNDEFINED;
}

static JSValue js_GetRandomValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_min;
    int err_min = JS_ToInt32(ctx, &long_min, argv[0]);
    if(err_min<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int min = (int)long_min;
    int32_t long_max;
    int err_max = JS_ToInt32(ctx, &long_max, argv[1]);
    if(err_max<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int max = (int)long_max;
    int returnVal = GetRandomValue(min, max);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_LoadRandomSequence(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    uint32_t long_count;
    int err_count = JS_ToUint32(ctx, &long_count, argv[0]);
    if(err_count<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int count = (unsigned int)long_count;
    int32_t long_min;
    int err_min = JS_ToInt32(ctx, &long_min, argv[1]);
    if(err_min<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int min = (int)long_min;
    int32_t long_max;
    int err_max = JS_ToInt32(ctx, &long_max, argv[2]);
    if(err_max<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int max = (int)long_max;
    int * returnVal = LoadRandomSequence(count, min, max);
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < count; i0++){
        JSValue js_ret = JS_NewInt32(ctx, (long)returnVal[i0]);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    UnloadRandomSequence(returnVal);
    return ret;
}

static JSValue js_TakeScreenshot(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    TakeScreenshot((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_SetConfigFlags(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    uint32_t long_flags;
    int err_flags = JS_ToUint32(ctx, &long_flags, argv[0]);
    if(err_flags<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int flags = (unsigned int)long_flags;
    SetConfigFlags(flags);
    return JS_UNDEFINED;
}

static JSValue js_OpenURL(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * url;
    JSValue da_url;
    int64_t size_url;
    if(JS_IsString(argv[0]) == 1) {
        url = (char *)JS_ToCStringLen(ctx, &size_url, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_url = JS_DupValue(ctx,argv[0]);
        size_t size_url;
        url = (char *)JS_GetArrayBuffer(ctx, &size_url, da_url);
    }
    else {
        JSClassID classid_url = JS_GetClassID(argv[0]);
        if(classid_url==JS_CLASS_INT8_ARRAY) {
            size_t offset_url;
            size_t size_url;
            da_url = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_url,&size_url,NULL);
            url = (char *)JS_GetArrayBuffer(ctx, &size_url, da_url);
            url+=offset_url;
            size_url-=offset_url;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    OpenURL((const char *)url);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, url);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, url);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_url);
    }
    else {
        JSClassID classid_url = JS_GetClassID(argv[0]);
        if(classid_url==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_url);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_TraceLog(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    int32_t long_logLevel;
    int err_logLevel = JS_ToInt32(ctx, &long_logLevel, argv[0]);
    if(err_logLevel<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int logLevel = (int)long_logLevel;
    size_t size_text = argc-1;
    if(size_text>4)size_text=4;
    char * * text = js_malloc(ctx, size_text * sizeof(char *));
    memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, text);
    for(int i0=0; i0 < size_text; i0++){
        int64_t size_texti0;
        if(JS_IsString(argv[i0+1]) == 1) {
            text[i0] = (char *)JS_ToCStringLen(ctx, &size_texti0, argv[i0+1]);
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text[i0]);
        }
        else if(JS_IsArrayBuffer(argv[i0+1]) == 1) {
            JSValue da_texti0 = JS_DupValue(ctx,argv[i0+1]);
            size_t size_texti0;
            text[i0] = (char *)JS_GetArrayBuffer(ctx, &size_texti0, da_texti0);
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_texti0);
        }
        else {
            JSClassID classid_texti0 = JS_GetClassID(argv[i0+1]);
            if(classid_texti0==JS_CLASS_INT8_ARRAY) {
                size_t offset_texti0;
                size_t size_texti0;
                JSValue da_texti0 = JS_GetTypedArrayBuffer(ctx,argv[i0+1],&offset_texti0,&size_texti0,NULL);
                text[i0] = (char *)JS_GetArrayBuffer(ctx, &size_texti0, da_texti0);
                text[i0]+=offset_texti0;
                size_texti0-=offset_texti0;
                memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_texti0);
            }
            else {
                JS_ThrowTypeError(ctx, "argv[i0+1] does not match type char *");
                return JS_EXCEPTION;
            }
        }
    }
    switch(size_text) {
        case 0:{
            return JS_EXCEPTION;
            break;
        }
        case 1:{
            TraceLog(logLevel, (const char *)text[0]);
            break;
        }
        case 2:{
            TraceLog(logLevel, (const char *)text[0], (const char *)text[1]);
            break;
        }
        case 3:{
            TraceLog(logLevel, (const char *)text[0], (const char *)text[1], (const char *)text[2]);
            break;
        }
        case 4:{
            TraceLog(logLevel, (const char *)text[0], (const char *)text[1], (const char *)text[2], (const char *)text[3]);
            break;
        }
    }
    memoryClear(ctx, memoryHead);
    return JS_UNDEFINED;
}

static JSValue js_SetTraceLogLevel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_logLevel;
    int err_logLevel = JS_ToInt32(ctx, &long_logLevel, argv[0]);
    if(err_logLevel<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int logLevel = (int)long_logLevel;
    SetTraceLogLevel(logLevel);
    return JS_UNDEFINED;
}

static JSValue js_SetLoadFileDataCallback(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    trampolineContext ctx_callback;
    ctx_callback.ctx = ctx;
    ctx_callback.func_obj = argv[0];
    if(JS_IsUndefined(argv[0]) || JS_IsNull(argv[0])) {
        JS_FreeValue(LoadFileDataCallback_callback_arr->ctx, LoadFileDataCallback_callback_arr->func_obj);
        JS_FreeContext(LoadFileDataCallback_callback_arr->ctx);
        LoadFileDataCallback_callback_arr = NULL;
    }
    else if(JS_IsFunction(ctx,argv[0])==1) {
        if(LoadFileDataCallback_callback_arr != NULL) {
            JS_FreeValue(LoadFileDataCallback_callback_arr->ctx, LoadFileDataCallback_callback_arr->func_obj);
            JS_FreeContext(LoadFileDataCallback_callback_arr->ctx);
        }
        LoadFileDataCallback_callback_arr = &ctx_callback;
    }
    else {
        return JS_EXCEPTION;
    }
    void * callback;
    if(LoadFileDataCallback_callback_arr == NULL) {
        callback = NULL;
    }
    else {
        callback = LoadFileDataCallback_callback_c;
    }
    JS_DupValue(ctx, argv[0]);
    SetLoadFileDataCallback(callback);
    return JS_UNDEFINED;
}

static JSValue js_SetSaveFileDataCallback(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    trampolineContext ctx_callback;
    ctx_callback.ctx = ctx;
    ctx_callback.func_obj = argv[0];
    if(JS_IsUndefined(argv[0]) || JS_IsNull(argv[0])) {
        JS_FreeValue(SaveFileDataCallback_callback_arr->ctx, SaveFileDataCallback_callback_arr->func_obj);
        JS_FreeContext(SaveFileDataCallback_callback_arr->ctx);
        SaveFileDataCallback_callback_arr = NULL;
    }
    else if(JS_IsFunction(ctx,argv[0])==1) {
        if(SaveFileDataCallback_callback_arr != NULL) {
            JS_FreeValue(SaveFileDataCallback_callback_arr->ctx, SaveFileDataCallback_callback_arr->func_obj);
            JS_FreeContext(SaveFileDataCallback_callback_arr->ctx);
        }
        SaveFileDataCallback_callback_arr = &ctx_callback;
    }
    else {
        return JS_EXCEPTION;
    }
    void * callback;
    if(SaveFileDataCallback_callback_arr == NULL) {
        callback = NULL;
    }
    else {
        callback = SaveFileDataCallback_callback_c;
    }
    JS_DupValue(ctx, argv[0]);
    SetSaveFileDataCallback(callback);
    return JS_UNDEFINED;
}

static JSValue js_SetLoadFileTextCallback(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    trampolineContext ctx_callback;
    ctx_callback.ctx = ctx;
    ctx_callback.func_obj = argv[0];
    if(JS_IsUndefined(argv[0]) || JS_IsNull(argv[0])) {
        JS_FreeValue(LoadFileTextCallback_callback_arr->ctx, LoadFileTextCallback_callback_arr->func_obj);
        JS_FreeContext(LoadFileTextCallback_callback_arr->ctx);
        LoadFileTextCallback_callback_arr = NULL;
    }
    else if(JS_IsFunction(ctx,argv[0])==1) {
        if(LoadFileTextCallback_callback_arr != NULL) {
            JS_FreeValue(LoadFileTextCallback_callback_arr->ctx, LoadFileTextCallback_callback_arr->func_obj);
            JS_FreeContext(LoadFileTextCallback_callback_arr->ctx);
        }
        LoadFileTextCallback_callback_arr = &ctx_callback;
    }
    else {
        return JS_EXCEPTION;
    }
    void * callback;
    if(LoadFileTextCallback_callback_arr == NULL) {
        callback = NULL;
    }
    else {
        callback = LoadFileTextCallback_callback_c;
    }
    JS_DupValue(ctx, argv[0]);
    SetLoadFileTextCallback(callback);
    return JS_UNDEFINED;
}

static JSValue js_SetSaveFileTextCallback(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    trampolineContext ctx_callback;
    ctx_callback.ctx = ctx;
    ctx_callback.func_obj = argv[0];
    if(JS_IsUndefined(argv[0]) || JS_IsNull(argv[0])) {
        JS_FreeValue(SaveFileTextCallback_callback_arr->ctx, SaveFileTextCallback_callback_arr->func_obj);
        JS_FreeContext(SaveFileTextCallback_callback_arr->ctx);
        SaveFileTextCallback_callback_arr = NULL;
    }
    else if(JS_IsFunction(ctx,argv[0])==1) {
        if(SaveFileTextCallback_callback_arr != NULL) {
            JS_FreeValue(SaveFileTextCallback_callback_arr->ctx, SaveFileTextCallback_callback_arr->func_obj);
            JS_FreeContext(SaveFileTextCallback_callback_arr->ctx);
        }
        SaveFileTextCallback_callback_arr = &ctx_callback;
    }
    else {
        return JS_EXCEPTION;
    }
    void * callback;
    if(SaveFileTextCallback_callback_arr == NULL) {
        callback = NULL;
    }
    else {
        callback = SaveFileTextCallback_callback_c;
    }
    JS_DupValue(ctx, argv[0]);
    SetSaveFileTextCallback(callback);
    return JS_UNDEFINED;
}

static JSValue js_LoadFileData(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int * dataSize;
    JSValue da_dataSize;
    int64_t size_dataSize;
    if(JS_IsArray(argv[1]) == 1) {
        if(JS_GetLength(ctx,argv[1],&size_dataSize)==-1) {
            if(JS_IsArray(argv[0]) == 1) {
                js_free(ctx, fileName);
            }
            else if(JS_IsString(argv[0]) == 1) {
                JS_FreeCString(ctx, fileName);
            }
            else if(JS_IsArrayBuffer(argv[0]) == 1) {
                JS_FreeValue(ctx, da_fileName);
            }
            else {
                JSClassID classid_fileName = JS_GetClassID(argv[0]);
                if(classid_fileName==JS_CLASS_INT8_ARRAY) {
                    js_free(ctx, &da_fileName);
                }
            }
            return JS_EXCEPTION;
        }
        dataSize = (int *)js_malloc(ctx, size_dataSize * sizeof(int));
        for(int i0=0; i0 < size_dataSize; i0++){
            JSValue js_dataSize = JS_GetPropertyUint32(ctx,argv[1],i0);
            int32_t long_dataSizei0;
            int err_dataSizei0 = JS_ToInt32(ctx, &long_dataSizei0, js_dataSize);
            if(err_dataSizei0<0) {
                JS_ThrowTypeError(ctx, "js_dataSize is not numeric");
                return JS_EXCEPTION;
            }
            dataSize[i0] = (int)long_dataSizei0;
            JS_FreeValue(ctx, js_dataSize);
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_dataSize = JS_DupValue(ctx,argv[1]);
        size_t size_dataSize;
        dataSize = (int *)JS_GetArrayBuffer(ctx, &size_dataSize, da_dataSize);
    }
    else {
        JSClassID classid_dataSize = JS_GetClassID(argv[1]);
        if(classid_dataSize==JS_CLASS_INT16_ARRAY) {
            size_t offset_dataSize;
            size_t size_dataSize;
            da_dataSize = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_dataSize,&size_dataSize,NULL);
            dataSize = (int *)JS_GetArrayBuffer(ctx, &size_dataSize, da_dataSize);
            dataSize+=offset_dataSize;
            size_dataSize-=offset_dataSize;
        }
        else {
            int32_t long_js_dataSize;
            int err_js_dataSize = JS_ToInt32(ctx, &long_js_dataSize, argv[1]);
            if(err_js_dataSize<0) {
                if(JS_IsArray(argv[0]) == 1) {
                    js_free(ctx, fileName);
                }
                else if(JS_IsString(argv[0]) == 1) {
                    JS_FreeCString(ctx, fileName);
                }
                else if(JS_IsArrayBuffer(argv[0]) == 1) {
                    JS_FreeValue(ctx, da_fileName);
                }
                else {
                    JSClassID classid_fileName = JS_GetClassID(argv[0]);
                    if(classid_fileName==JS_CLASS_INT8_ARRAY) {
                        js_free(ctx, &da_fileName);
                    }
                }
                JS_ThrowTypeError(ctx, "argv[1] is not numeric");
                return JS_EXCEPTION;
            }
            int js_dataSize = (int)long_js_dataSize;
            dataSize = &js_dataSize;
        }
    }
    unsigned char * returnVal = LoadFileData((const char *)fileName, dataSize);
    if(JS_IsArray(argv[1]) == 1) {
        JSValue js_argv1 = JS_NewInt32(ctx, (long)dataSize[0]);
        JS_DefinePropertyValueUint32(ctx,argv[1],0,js_argv1,JS_PROP_C_W_E);
    }
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, dataSize);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_dataSize);
    }
    else {
        JSClassID classid_dataSize = JS_GetClassID(argv[1]);
        if(classid_dataSize==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &da_dataSize);
        }
    }
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < dataSize[0]; i0++){
        JSValue js_ret = JS_NewUint32(ctx, (unsigned long)returnVal[i0]);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    UnloadFileData(returnVal);
    return ret;
}

static JSValue js_SaveFileData(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            JSValue da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileName);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    void * data;
    int64_t size_data;
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_data = JS_DupValue(ctx,argv[1]);
        size_t size_data;
        data = (void *)JS_GetArrayBuffer(ctx, &size_data, da_data);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_data);
    }
    else {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[1] does not match type void *");
        return JS_EXCEPTION;
    }
    int32_t long_dataSize;
    int err_dataSize = JS_ToInt32(ctx, &long_dataSize, argv[2]);
    if(err_dataSize<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int dataSize = (int)long_dataSize;
    bool returnVal = SaveFileData((const char *)fileName, data, dataSize);
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_LoadFileText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * returnVal = LoadFileText((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    UnloadFileText(returnVal);
    return ret;
}

static JSValue js_SaveFileText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            JSValue da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileName);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            JSValue da_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = SaveFileText((const char *)fileName, text);
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_FileExists(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = FileExists((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_DirectoryExists(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * dirPath;
    JSValue da_dirPath;
    int64_t size_dirPath;
    if(JS_IsString(argv[0]) == 1) {
        dirPath = (char *)JS_ToCStringLen(ctx, &size_dirPath, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_dirPath = JS_DupValue(ctx,argv[0]);
        size_t size_dirPath;
        dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, da_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            size_t offset_dirPath;
            size_t size_dirPath;
            da_dirPath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dirPath,&size_dirPath,NULL);
            dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, da_dirPath);
            dirPath+=offset_dirPath;
            size_dirPath-=offset_dirPath;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = DirectoryExists((const char *)dirPath);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, dirPath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, dirPath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_dirPath);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsFileExtension(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            JSValue da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileName);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * ext;
    int64_t size_ext;
    if(JS_IsString(argv[1]) == 1) {
        ext = (char *)JS_ToCStringLen(ctx, &size_ext, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, ext);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_ext = JS_DupValue(ctx,argv[1]);
        size_t size_ext;
        ext = (char *)JS_GetArrayBuffer(ctx, &size_ext, da_ext);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_ext);
    }
    else {
        JSClassID classid_ext = JS_GetClassID(argv[1]);
        if(classid_ext==JS_CLASS_INT8_ARRAY) {
            size_t offset_ext;
            size_t size_ext;
            JSValue da_ext = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_ext,&size_ext,NULL);
            ext = (char *)JS_GetArrayBuffer(ctx, &size_ext, da_ext);
            ext+=offset_ext;
            size_ext-=offset_ext;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_ext);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = IsFileExtension((const char *)fileName, (const char *)ext);
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_GetFileLength(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int returnVal = GetFileLength((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetFileExtension(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = GetFileExtension((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetFileName(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * filePath;
    JSValue da_filePath;
    int64_t size_filePath;
    if(JS_IsString(argv[0]) == 1) {
        filePath = (char *)JS_ToCStringLen(ctx, &size_filePath, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_filePath = JS_DupValue(ctx,argv[0]);
        size_t size_filePath;
        filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, da_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            size_t offset_filePath;
            size_t size_filePath;
            da_filePath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_filePath,&size_filePath,NULL);
            filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, da_filePath);
            filePath+=offset_filePath;
            size_filePath-=offset_filePath;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = GetFileName((const char *)filePath);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, filePath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, filePath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_filePath);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetFileNameWithoutExt(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * filePath;
    JSValue da_filePath;
    int64_t size_filePath;
    if(JS_IsString(argv[0]) == 1) {
        filePath = (char *)JS_ToCStringLen(ctx, &size_filePath, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_filePath = JS_DupValue(ctx,argv[0]);
        size_t size_filePath;
        filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, da_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            size_t offset_filePath;
            size_t size_filePath;
            da_filePath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_filePath,&size_filePath,NULL);
            filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, da_filePath);
            filePath+=offset_filePath;
            size_filePath-=offset_filePath;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = GetFileNameWithoutExt((const char *)filePath);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, filePath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, filePath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_filePath);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetDirectoryPath(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * filePath;
    JSValue da_filePath;
    int64_t size_filePath;
    if(JS_IsString(argv[0]) == 1) {
        filePath = (char *)JS_ToCStringLen(ctx, &size_filePath, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_filePath = JS_DupValue(ctx,argv[0]);
        size_t size_filePath;
        filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, da_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            size_t offset_filePath;
            size_t size_filePath;
            da_filePath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_filePath,&size_filePath,NULL);
            filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, da_filePath);
            filePath+=offset_filePath;
            size_filePath-=offset_filePath;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = GetDirectoryPath((const char *)filePath);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, filePath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, filePath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_filePath);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetPrevDirectoryPath(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * dirPath;
    JSValue da_dirPath;
    int64_t size_dirPath;
    if(JS_IsString(argv[0]) == 1) {
        dirPath = (char *)JS_ToCStringLen(ctx, &size_dirPath, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_dirPath = JS_DupValue(ctx,argv[0]);
        size_t size_dirPath;
        dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, da_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            size_t offset_dirPath;
            size_t size_dirPath;
            da_dirPath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dirPath,&size_dirPath,NULL);
            dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, da_dirPath);
            dirPath+=offset_dirPath;
            size_dirPath-=offset_dirPath;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = GetPrevDirectoryPath((const char *)dirPath);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, dirPath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, dirPath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_dirPath);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetWorkingDirectory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    const char * returnVal = GetWorkingDirectory();
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetApplicationDirectory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    const char * returnVal = GetApplicationDirectory();
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_MakeDirectory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * dirPath;
    JSValue da_dirPath;
    int64_t size_dirPath;
    if(JS_IsString(argv[0]) == 1) {
        dirPath = (char *)JS_ToCStringLen(ctx, &size_dirPath, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_dirPath = JS_DupValue(ctx,argv[0]);
        size_t size_dirPath;
        dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, da_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            size_t offset_dirPath;
            size_t size_dirPath;
            da_dirPath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dirPath,&size_dirPath,NULL);
            dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, da_dirPath);
            dirPath+=offset_dirPath;
            size_dirPath-=offset_dirPath;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int returnVal = MakeDirectory((const char *)dirPath);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, dirPath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, dirPath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_dirPath);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_ChangeDirectory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * dir;
    JSValue da_dir;
    int64_t size_dir;
    if(JS_IsString(argv[0]) == 1) {
        dir = (char *)JS_ToCStringLen(ctx, &size_dir, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_dir = JS_DupValue(ctx,argv[0]);
        size_t size_dir;
        dir = (char *)JS_GetArrayBuffer(ctx, &size_dir, da_dir);
    }
    else {
        JSClassID classid_dir = JS_GetClassID(argv[0]);
        if(classid_dir==JS_CLASS_INT8_ARRAY) {
            size_t offset_dir;
            size_t size_dir;
            da_dir = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dir,&size_dir,NULL);
            dir = (char *)JS_GetArrayBuffer(ctx, &size_dir, da_dir);
            dir+=offset_dir;
            size_dir-=offset_dir;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ChangeDirectory((const char *)dir);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, dir);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, dir);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_dir);
    }
    else {
        JSClassID classid_dir = JS_GetClassID(argv[0]);
        if(classid_dir==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_dir);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsPathFile(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * path;
    JSValue da_path;
    int64_t size_path;
    if(JS_IsString(argv[0]) == 1) {
        path = (char *)JS_ToCStringLen(ctx, &size_path, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_path = JS_DupValue(ctx,argv[0]);
        size_t size_path;
        path = (char *)JS_GetArrayBuffer(ctx, &size_path, da_path);
    }
    else {
        JSClassID classid_path = JS_GetClassID(argv[0]);
        if(classid_path==JS_CLASS_INT8_ARRAY) {
            size_t offset_path;
            size_t size_path;
            da_path = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_path,&size_path,NULL);
            path = (char *)JS_GetArrayBuffer(ctx, &size_path, da_path);
            path+=offset_path;
            size_path-=offset_path;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = IsPathFile((const char *)path);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, path);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, path);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_path);
    }
    else {
        JSClassID classid_path = JS_GetClassID(argv[0]);
        if(classid_path==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_path);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsFileNameValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = IsFileNameValid((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_LoadDirectoryFiles(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * dirPath;
    JSValue da_dirPath;
    int64_t size_dirPath;
    if(JS_IsString(argv[0]) == 1) {
        dirPath = (char *)JS_ToCStringLen(ctx, &size_dirPath, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_dirPath = JS_DupValue(ctx,argv[0]);
        size_t size_dirPath;
        dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, da_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            size_t offset_dirPath;
            size_t size_dirPath;
            da_dirPath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dirPath,&size_dirPath,NULL);
            dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, da_dirPath);
            dirPath+=offset_dirPath;
            size_dirPath-=offset_dirPath;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    FilePathList files = LoadDirectoryFiles(dirPath);
    JSValue ret = JS_NewArray(ctx);
    for(int i=0; i < files.count; i++){
        JS_SetPropertyUint32(ctx, ret, i, JS_NewString(ctx,files.paths[i]));
    }
    UnloadDirectoryFiles(files);
    JS_FreeCString(ctx, dirPath);
    return ret;
}

static JSValue js_LoadDirectoryFilesEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * basePath;
    JSValue da_basePath;
    int64_t size_basePath;
    if(JS_IsString(argv[0]) == 1) {
        basePath = (char *)JS_ToCStringLen(ctx, &size_basePath, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_basePath = JS_DupValue(ctx,argv[0]);
        size_t size_basePath;
        basePath = (char *)JS_GetArrayBuffer(ctx, &size_basePath, da_basePath);
    }
    else {
        JSClassID classid_basePath = JS_GetClassID(argv[0]);
        if(classid_basePath==JS_CLASS_INT8_ARRAY) {
            size_t offset_basePath;
            size_t size_basePath;
            da_basePath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_basePath,&size_basePath,NULL);
            basePath = (char *)JS_GetArrayBuffer(ctx, &size_basePath, da_basePath);
            basePath+=offset_basePath;
            size_basePath-=offset_basePath;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * filter;
    JSValue da_filter;
    int64_t size_filter;
    if(JS_IsString(argv[1]) == 1) {
        filter = (char *)JS_ToCStringLen(ctx, &size_filter, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_filter = JS_DupValue(ctx,argv[1]);
        size_t size_filter;
        filter = (char *)JS_GetArrayBuffer(ctx, &size_filter, da_filter);
    }
    else {
        JSClassID classid_filter = JS_GetClassID(argv[1]);
        if(classid_filter==JS_CLASS_INT8_ARRAY) {
            size_t offset_filter;
            size_t size_filter;
            da_filter = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_filter,&size_filter,NULL);
            filter = (char *)JS_GetArrayBuffer(ctx, &size_filter, da_filter);
            filter+=offset_filter;
            size_filter-=offset_filter;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int js_scanSubdirs = JS_ToBool(ctx, argv[2]);
    if(js_scanSubdirs<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not a bool");
        return JS_EXCEPTION;
    }
    bool scanSubdirs = js_scanSubdirs;
    FilePathList files = LoadDirectoryFilesEx(basePath, filter, scanSubdirs);
    JSValue ret = JS_NewArray(ctx);
    for(int i=0; i < files.count; i++){
        JS_SetPropertyUint32(ctx, ret, i, JS_NewString(ctx,files.paths[i]));
    }
    UnloadDirectoryFiles(files);
    JS_FreeCString(ctx, basePath);
    JS_FreeCString(ctx, filter);
    return ret;
}

static JSValue js_IsFileDropped(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsFileDropped();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_LoadDroppedFiles(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    FilePathList files = LoadDroppedFiles();
    JSValue ret = JS_NewArray(ctx);
    for(int i=0; i < files.count; i++){
        JS_SetPropertyUint32(ctx, ret, i, JS_NewString(ctx,files.paths[i]));
    }
    UnloadDroppedFiles(files);
    return ret;
}

static JSValue js_GetFileModTime(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    long returnVal = GetFileModTime((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_ComputeCRC32(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned char * data;
    JSValue da_data;
    int64_t size_data;
    if(JS_IsArray(argv[0]) == 1) {
        if(JS_GetLength(ctx,argv[0],&size_data)==-1) {
            return JS_EXCEPTION;
        }
        data = (unsigned char *)js_malloc(ctx, size_data * sizeof(unsigned char));
        for(int i0=0; i0 < size_data; i0++){
            JSValue js_data = JS_GetPropertyUint32(ctx,argv[0],i0);
            uint32_t long_datai0;
            int err_datai0 = JS_ToUint32(ctx, &long_datai0, js_data);
            if(err_datai0<0) {
                JS_ThrowTypeError(ctx, "js_data is not numeric");
                return JS_EXCEPTION;
            }
            data[i0] = (unsigned char)long_datai0;
            JS_FreeValue(ctx, js_data);
        }
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_data = JS_DupValue(ctx,argv[0]);
        size_t size_data;
        data = (unsigned char *)JS_GetArrayBuffer(ctx, &size_data, da_data);
    }
    else {
        JSClassID classid_data = JS_GetClassID(argv[0]);
        if(classid_data==JS_CLASS_UINT8_ARRAY || classid_data==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_data;
            size_t size_data;
            da_data = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_data,&size_data,NULL);
            data = (unsigned char *)JS_GetArrayBuffer(ctx, &size_data, da_data);
            data+=offset_data;
            size_data-=offset_data;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type unsigned char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_dataSize;
    int err_dataSize = JS_ToInt32(ctx, &long_dataSize, argv[1]);
    if(err_dataSize<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, data);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_data);
        }
        else {
            JSClassID classid_data = JS_GetClassID(argv[0]);
            if(classid_data==JS_CLASS_UINT8_ARRAY && classid_data==JS_CLASS_UINT8C_ARRAY) {
                js_free(ctx, &da_data);
            }
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int dataSize = (int)long_dataSize;
    unsigned int returnVal = ComputeCRC32(data, dataSize);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, data);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_data);
    }
    else {
        JSClassID classid_data = JS_GetClassID(argv[0]);
        if(classid_data==JS_CLASS_UINT8_ARRAY && classid_data==JS_CLASS_UINT8C_ARRAY) {
            js_free(ctx, &da_data);
        }
    }
    JSValue ret = JS_NewUint32(ctx, (unsigned long)returnVal);
    return ret;
}

static JSValue js_ComputeMD5(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned char * data;
    JSValue da_data;
    int64_t size_data;
    if(JS_IsArray(argv[0]) == 1) {
        if(JS_GetLength(ctx,argv[0],&size_data)==-1) {
            return JS_EXCEPTION;
        }
        data = (unsigned char *)js_malloc(ctx, size_data * sizeof(unsigned char));
        for(int i0=0; i0 < size_data; i0++){
            JSValue js_data = JS_GetPropertyUint32(ctx,argv[0],i0);
            uint32_t long_datai0;
            int err_datai0 = JS_ToUint32(ctx, &long_datai0, js_data);
            if(err_datai0<0) {
                JS_ThrowTypeError(ctx, "js_data is not numeric");
                return JS_EXCEPTION;
            }
            data[i0] = (unsigned char)long_datai0;
            JS_FreeValue(ctx, js_data);
        }
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_data = JS_DupValue(ctx,argv[0]);
        size_t size_data;
        data = (unsigned char *)JS_GetArrayBuffer(ctx, &size_data, da_data);
    }
    else {
        JSClassID classid_data = JS_GetClassID(argv[0]);
        if(classid_data==JS_CLASS_UINT8_ARRAY || classid_data==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_data;
            size_t size_data;
            da_data = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_data,&size_data,NULL);
            data = (unsigned char *)JS_GetArrayBuffer(ctx, &size_data, da_data);
            data+=offset_data;
            size_data-=offset_data;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type unsigned char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_dataSize;
    int err_dataSize = JS_ToInt32(ctx, &long_dataSize, argv[1]);
    if(err_dataSize<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, data);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_data);
        }
        else {
            JSClassID classid_data = JS_GetClassID(argv[0]);
            if(classid_data==JS_CLASS_UINT8_ARRAY && classid_data==JS_CLASS_UINT8C_ARRAY) {
                js_free(ctx, &da_data);
            }
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int dataSize = (int)long_dataSize;
    unsigned int * returnVal = ComputeMD5(data, dataSize);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, data);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_data);
    }
    else {
        JSClassID classid_data = JS_GetClassID(argv[0]);
        if(classid_data==JS_CLASS_UINT8_ARRAY && classid_data==JS_CLASS_UINT8C_ARRAY) {
            js_free(ctx, &da_data);
        }
    }
    JSValue ret;
    ret = JS_NewArray(ctx);
    JSValue js_ret0 = JS_NewUint32(ctx, (unsigned long)returnVal[0]);
    JS_DefinePropertyValueUint32(ctx,ret,0,js_ret0,JS_PROP_C_W_E);
    JSValue js_ret1 = JS_NewUint32(ctx, (unsigned long)returnVal[1]);
    JS_DefinePropertyValueUint32(ctx,ret,1,js_ret1,JS_PROP_C_W_E);
    JSValue js_ret2 = JS_NewUint32(ctx, (unsigned long)returnVal[2]);
    JS_DefinePropertyValueUint32(ctx,ret,2,js_ret2,JS_PROP_C_W_E);
    JSValue js_ret3 = JS_NewUint32(ctx, (unsigned long)returnVal[3]);
    JS_DefinePropertyValueUint32(ctx,ret,3,js_ret3,JS_PROP_C_W_E);
    return ret;
}

static JSValue js_ComputeSHA1(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned char * data;
    JSValue da_data;
    int64_t size_data;
    if(JS_IsArray(argv[0]) == 1) {
        if(JS_GetLength(ctx,argv[0],&size_data)==-1) {
            return JS_EXCEPTION;
        }
        data = (unsigned char *)js_malloc(ctx, size_data * sizeof(unsigned char));
        for(int i0=0; i0 < size_data; i0++){
            JSValue js_data = JS_GetPropertyUint32(ctx,argv[0],i0);
            uint32_t long_datai0;
            int err_datai0 = JS_ToUint32(ctx, &long_datai0, js_data);
            if(err_datai0<0) {
                JS_ThrowTypeError(ctx, "js_data is not numeric");
                return JS_EXCEPTION;
            }
            data[i0] = (unsigned char)long_datai0;
            JS_FreeValue(ctx, js_data);
        }
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_data = JS_DupValue(ctx,argv[0]);
        size_t size_data;
        data = (unsigned char *)JS_GetArrayBuffer(ctx, &size_data, da_data);
    }
    else {
        JSClassID classid_data = JS_GetClassID(argv[0]);
        if(classid_data==JS_CLASS_UINT8_ARRAY || classid_data==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_data;
            size_t size_data;
            da_data = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_data,&size_data,NULL);
            data = (unsigned char *)JS_GetArrayBuffer(ctx, &size_data, da_data);
            data+=offset_data;
            size_data-=offset_data;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type unsigned char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_dataSize;
    int err_dataSize = JS_ToInt32(ctx, &long_dataSize, argv[1]);
    if(err_dataSize<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, data);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_data);
        }
        else {
            JSClassID classid_data = JS_GetClassID(argv[0]);
            if(classid_data==JS_CLASS_UINT8_ARRAY && classid_data==JS_CLASS_UINT8C_ARRAY) {
                js_free(ctx, &da_data);
            }
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int dataSize = (int)long_dataSize;
    unsigned int * returnVal = ComputeSHA1(data, dataSize);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, data);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_data);
    }
    else {
        JSClassID classid_data = JS_GetClassID(argv[0]);
        if(classid_data==JS_CLASS_UINT8_ARRAY && classid_data==JS_CLASS_UINT8C_ARRAY) {
            js_free(ctx, &da_data);
        }
    }
    JSValue ret;
    ret = JS_NewArray(ctx);
    JSValue js_ret0 = JS_NewUint32(ctx, (unsigned long)returnVal[0]);
    JS_DefinePropertyValueUint32(ctx,ret,0,js_ret0,JS_PROP_C_W_E);
    JSValue js_ret1 = JS_NewUint32(ctx, (unsigned long)returnVal[1]);
    JS_DefinePropertyValueUint32(ctx,ret,1,js_ret1,JS_PROP_C_W_E);
    JSValue js_ret2 = JS_NewUint32(ctx, (unsigned long)returnVal[2]);
    JS_DefinePropertyValueUint32(ctx,ret,2,js_ret2,JS_PROP_C_W_E);
    JSValue js_ret3 = JS_NewUint32(ctx, (unsigned long)returnVal[3]);
    JS_DefinePropertyValueUint32(ctx,ret,3,js_ret3,JS_PROP_C_W_E);
    JSValue js_ret4 = JS_NewUint32(ctx, (unsigned long)returnVal[4]);
    JS_DefinePropertyValueUint32(ctx,ret,4,js_ret4,JS_PROP_C_W_E);
    return ret;
}

static JSValue js_LoadAutomationEventList(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    AutomationEventList returnVal = LoadAutomationEventList((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    AutomationEventList* ptr_ret = (AutomationEventList*)js_malloc(ctx, sizeof(AutomationEventList));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_AutomationEventList_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_UnloadAutomationEventList(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AutomationEventList* ptr_list = (AutomationEventList*)JS_GetOpaque(argv[0], js_AutomationEventList_class_id);
    if(ptr_list == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AutomationEventList list = *ptr_list;
    UnloadAutomationEventList(list);
    return JS_UNDEFINED;
}

static JSValue js_ExportAutomationEventList(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AutomationEventList* ptr_list = (AutomationEventList*)JS_GetOpaque(argv[0], js_AutomationEventList_class_id);
    if(ptr_list == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AutomationEventList list = *ptr_list;
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[1]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[1]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ExportAutomationEventList(list, (const char *)fileName);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_SetAutomationEventList(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AutomationEventList * list = (AutomationEventList *)JS_GetOpaque(argv[0], js_AutomationEventList_class_id);
    if(list == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type AutomationEventList");
        return JS_EXCEPTION;
    }
    SetAutomationEventList(list);
    return JS_UNDEFINED;
}

static JSValue js_SetAutomationEventBaseFrame(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_frame;
    int err_frame = JS_ToInt32(ctx, &long_frame, argv[0]);
    if(err_frame<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int frame = (int)long_frame;
    SetAutomationEventBaseFrame(frame);
    return JS_UNDEFINED;
}

static JSValue js_StartAutomationEventRecording(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    StartAutomationEventRecording();
    return JS_UNDEFINED;
}

static JSValue js_StopAutomationEventRecording(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    StopAutomationEventRecording();
    return JS_UNDEFINED;
}

static JSValue js_PlayAutomationEvent(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AutomationEvent* ptr_event = (AutomationEvent*)JS_GetOpaque(argv[0], js_AutomationEvent_class_id);
    if(ptr_event == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AutomationEvent event = *ptr_event;
    PlayAutomationEvent(event);
    return JS_UNDEFINED;
}

static JSValue js_IsKeyPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_key;
    int err_key = JS_ToInt32(ctx, &long_key, argv[0]);
    if(err_key<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int key = (int)long_key;
    bool returnVal = IsKeyPressed(key);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsKeyPressedRepeat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_key;
    int err_key = JS_ToInt32(ctx, &long_key, argv[0]);
    if(err_key<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int key = (int)long_key;
    bool returnVal = IsKeyPressedRepeat(key);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsKeyDown(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_key;
    int err_key = JS_ToInt32(ctx, &long_key, argv[0]);
    if(err_key<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int key = (int)long_key;
    bool returnVal = IsKeyDown(key);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsKeyReleased(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_key;
    int err_key = JS_ToInt32(ctx, &long_key, argv[0]);
    if(err_key<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int key = (int)long_key;
    bool returnVal = IsKeyReleased(key);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsKeyUp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_key;
    int err_key = JS_ToInt32(ctx, &long_key, argv[0]);
    if(err_key<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int key = (int)long_key;
    bool returnVal = IsKeyUp(key);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_GetKeyPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetKeyPressed();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetCharPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetCharPressed();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetKeyName(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_key;
    int err_key = JS_ToInt32(ctx, &long_key, argv[0]);
    if(err_key<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int key = (int)long_key;
    const char * returnVal = GetKeyName(key);
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_SetExitKey(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_key;
    int err_key = JS_ToInt32(ctx, &long_key, argv[0]);
    if(err_key<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int key = (int)long_key;
    SetExitKey(key);
    return JS_UNDEFINED;
}

static JSValue js_IsGamepadAvailable(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_gamepad;
    int err_gamepad = JS_ToInt32(ctx, &long_gamepad, argv[0]);
    if(err_gamepad<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int gamepad = (int)long_gamepad;
    bool returnVal = IsGamepadAvailable(gamepad);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_GetGamepadName(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_gamepad;
    int err_gamepad = JS_ToInt32(ctx, &long_gamepad, argv[0]);
    if(err_gamepad<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int gamepad = (int)long_gamepad;
    const char * returnVal = GetGamepadName(gamepad);
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_IsGamepadButtonPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_gamepad;
    int err_gamepad = JS_ToInt32(ctx, &long_gamepad, argv[0]);
    if(err_gamepad<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int gamepad = (int)long_gamepad;
    int32_t long_button;
    int err_button = JS_ToInt32(ctx, &long_button, argv[1]);
    if(err_button<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int button = (int)long_button;
    bool returnVal = IsGamepadButtonPressed(gamepad, button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsGamepadButtonDown(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_gamepad;
    int err_gamepad = JS_ToInt32(ctx, &long_gamepad, argv[0]);
    if(err_gamepad<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int gamepad = (int)long_gamepad;
    int32_t long_button;
    int err_button = JS_ToInt32(ctx, &long_button, argv[1]);
    if(err_button<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int button = (int)long_button;
    bool returnVal = IsGamepadButtonDown(gamepad, button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsGamepadButtonReleased(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_gamepad;
    int err_gamepad = JS_ToInt32(ctx, &long_gamepad, argv[0]);
    if(err_gamepad<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int gamepad = (int)long_gamepad;
    int32_t long_button;
    int err_button = JS_ToInt32(ctx, &long_button, argv[1]);
    if(err_button<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int button = (int)long_button;
    bool returnVal = IsGamepadButtonReleased(gamepad, button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsGamepadButtonUp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_gamepad;
    int err_gamepad = JS_ToInt32(ctx, &long_gamepad, argv[0]);
    if(err_gamepad<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int gamepad = (int)long_gamepad;
    int32_t long_button;
    int err_button = JS_ToInt32(ctx, &long_button, argv[1]);
    if(err_button<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int button = (int)long_button;
    bool returnVal = IsGamepadButtonUp(gamepad, button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_GetGamepadButtonPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetGamepadButtonPressed();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetGamepadAxisCount(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_gamepad;
    int err_gamepad = JS_ToInt32(ctx, &long_gamepad, argv[0]);
    if(err_gamepad<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int gamepad = (int)long_gamepad;
    int returnVal = GetGamepadAxisCount(gamepad);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetGamepadAxisMovement(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_gamepad;
    int err_gamepad = JS_ToInt32(ctx, &long_gamepad, argv[0]);
    if(err_gamepad<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int gamepad = (int)long_gamepad;
    int32_t long_axis;
    int err_axis = JS_ToInt32(ctx, &long_axis, argv[1]);
    if(err_axis<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int axis = (int)long_axis;
    float returnVal = GetGamepadAxisMovement(gamepad, axis);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_SetGamepadMappings(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * mappings;
    JSValue da_mappings;
    int64_t size_mappings;
    if(JS_IsString(argv[0]) == 1) {
        mappings = (char *)JS_ToCStringLen(ctx, &size_mappings, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_mappings = JS_DupValue(ctx,argv[0]);
        size_t size_mappings;
        mappings = (char *)JS_GetArrayBuffer(ctx, &size_mappings, da_mappings);
    }
    else {
        JSClassID classid_mappings = JS_GetClassID(argv[0]);
        if(classid_mappings==JS_CLASS_INT8_ARRAY) {
            size_t offset_mappings;
            size_t size_mappings;
            da_mappings = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_mappings,&size_mappings,NULL);
            mappings = (char *)JS_GetArrayBuffer(ctx, &size_mappings, da_mappings);
            mappings+=offset_mappings;
            size_mappings-=offset_mappings;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int returnVal = SetGamepadMappings((const char *)mappings);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, mappings);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, mappings);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_mappings);
    }
    else {
        JSClassID classid_mappings = JS_GetClassID(argv[0]);
        if(classid_mappings==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_mappings);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_SetGamepadVibration(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_gamepad;
    int err_gamepad = JS_ToInt32(ctx, &long_gamepad, argv[0]);
    if(err_gamepad<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int gamepad = (int)long_gamepad;
    double double_leftMotor;
    int err_leftMotor = JS_ToFloat64(ctx, &double_leftMotor, argv[1]);
    if(err_leftMotor<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float leftMotor = (float)double_leftMotor;
    double double_rightMotor;
    int err_rightMotor = JS_ToFloat64(ctx, &double_rightMotor, argv[2]);
    if(err_rightMotor<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float rightMotor = (float)double_rightMotor;
    double double_duration;
    int err_duration = JS_ToFloat64(ctx, &double_duration, argv[3]);
    if(err_duration<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float duration = (float)double_duration;
    SetGamepadVibration(gamepad, leftMotor, rightMotor, duration);
    return JS_UNDEFINED;
}

static JSValue js_IsMouseButtonPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_button;
    int err_button = JS_ToInt32(ctx, &long_button, argv[0]);
    if(err_button<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int button = (int)long_button;
    bool returnVal = IsMouseButtonPressed(button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsMouseButtonDown(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_button;
    int err_button = JS_ToInt32(ctx, &long_button, argv[0]);
    if(err_button<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int button = (int)long_button;
    bool returnVal = IsMouseButtonDown(button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsMouseButtonReleased(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_button;
    int err_button = JS_ToInt32(ctx, &long_button, argv[0]);
    if(err_button<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int button = (int)long_button;
    bool returnVal = IsMouseButtonReleased(button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_IsMouseButtonUp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_button;
    int err_button = JS_ToInt32(ctx, &long_button, argv[0]);
    if(err_button<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int button = (int)long_button;
    bool returnVal = IsMouseButtonUp(button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_GetMouseX(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetMouseX();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetMouseY(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetMouseY();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetMousePosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetMousePosition();
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetMouseDelta(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetMouseDelta();
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_SetMousePosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_x;
    int err_x = JS_ToInt32(ctx, &long_x, argv[0]);
    if(err_x<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int x = (int)long_x;
    int32_t long_y;
    int err_y = JS_ToInt32(ctx, &long_y, argv[1]);
    if(err_y<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int y = (int)long_y;
    SetMousePosition(x, y);
    return JS_UNDEFINED;
}

static JSValue js_SetMouseOffset(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_offsetX;
    int err_offsetX = JS_ToInt32(ctx, &long_offsetX, argv[0]);
    if(err_offsetX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int offsetX = (int)long_offsetX;
    int32_t long_offsetY;
    int err_offsetY = JS_ToInt32(ctx, &long_offsetY, argv[1]);
    if(err_offsetY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int offsetY = (int)long_offsetY;
    SetMouseOffset(offsetX, offsetY);
    return JS_UNDEFINED;
}

static JSValue js_SetMouseScale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_scaleX;
    int err_scaleX = JS_ToFloat64(ctx, &double_scaleX, argv[0]);
    if(err_scaleX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float scaleX = (float)double_scaleX;
    double double_scaleY;
    int err_scaleY = JS_ToFloat64(ctx, &double_scaleY, argv[1]);
    if(err_scaleY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float scaleY = (float)double_scaleY;
    SetMouseScale(scaleX, scaleY);
    return JS_UNDEFINED;
}

static JSValue js_GetMouseWheelMove(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetMouseWheelMove();
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_GetMouseWheelMoveV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetMouseWheelMoveV();
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_SetMouseCursor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_cursor;
    int err_cursor = JS_ToInt32(ctx, &long_cursor, argv[0]);
    if(err_cursor<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int cursor = (int)long_cursor;
    SetMouseCursor(cursor);
    return JS_UNDEFINED;
}

static JSValue js_GetTouchX(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetTouchX();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetTouchY(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetTouchY();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetTouchPosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_index;
    int err_index = JS_ToInt32(ctx, &long_index, argv[0]);
    if(err_index<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int index = (int)long_index;
    Vector2 returnVal = GetTouchPosition(index);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetTouchPointId(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_index;
    int err_index = JS_ToInt32(ctx, &long_index, argv[0]);
    if(err_index<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int index = (int)long_index;
    int returnVal = GetTouchPointId(index);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetTouchPointCount(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetTouchPointCount();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_SetGesturesEnabled(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    uint32_t long_flags;
    int err_flags = JS_ToUint32(ctx, &long_flags, argv[0]);
    if(err_flags<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int flags = (unsigned int)long_flags;
    SetGesturesEnabled(flags);
    return JS_UNDEFINED;
}

static JSValue js_IsGestureDetected(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    uint32_t long_gesture;
    int err_gesture = JS_ToUint32(ctx, &long_gesture, argv[0]);
    if(err_gesture<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int gesture = (unsigned int)long_gesture;
    bool returnVal = IsGestureDetected(gesture);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_GetGestureDetected(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetGestureDetected();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetGestureHoldDuration(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetGestureHoldDuration();
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_GetGestureDragVector(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetGestureDragVector();
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetGestureDragAngle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetGestureDragAngle();
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_GetGesturePinchVector(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetGesturePinchVector();
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetGesturePinchAngle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetGesturePinchAngle();
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_UpdateCamera(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    int32_t long_mode;
    int err_mode = JS_ToInt32(ctx, &long_mode, argv[1]);
    if(err_mode<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int mode = (int)long_mode;
    UpdateCamera(camera, mode);
    return JS_UNDEFINED;
}

static JSValue js_UpdateCameraPro(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera * camera = (Camera *)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Camera");
        return JS_EXCEPTION;
    }
    Vector3* ptr_movement = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_movement == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 movement = *ptr_movement;
    Vector3* ptr_rotation = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_rotation == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 rotation = *ptr_rotation;
    double double_zoom;
    int err_zoom = JS_ToFloat64(ctx, &double_zoom, argv[3]);
    if(err_zoom<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float zoom = (float)double_zoom;
    UpdateCameraPro(camera, movement, rotation, zoom);
    return JS_UNDEFINED;
}

static JSValue js_SetShapesTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    Rectangle* ptr_source = (Rectangle*)JS_GetOpaque(argv[1], js_Rectangle_class_id);
    if(ptr_source == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle source = *ptr_source;
    SetShapesTexture(texture, source);
    return JS_UNDEFINED;
}

static JSValue js_GetShapesTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D returnVal = GetShapesTexture();
    Texture2D* ptr_ret = (Texture2D*)js_malloc(ctx, sizeof(Texture2D));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetShapesTextureRectangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle returnVal = GetShapesTextureRectangle();
    Rectangle* ptr_ret = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_DrawPixel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_posX;
    int err_posX = JS_ToInt32(ctx, &long_posX, argv[0]);
    if(err_posX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int posX = (int)long_posX;
    int32_t long_posY;
    int err_posY = JS_ToInt32(ctx, &long_posY, argv[1]);
    if(err_posY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int posY = (int)long_posY;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawPixel(posX, posY, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawPixelV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawPixelV(position, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawLine(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_startPosX;
    int err_startPosX = JS_ToInt32(ctx, &long_startPosX, argv[0]);
    if(err_startPosX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int startPosX = (int)long_startPosX;
    int32_t long_startPosY;
    int err_startPosY = JS_ToInt32(ctx, &long_startPosY, argv[1]);
    if(err_startPosY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int startPosY = (int)long_startPosY;
    int32_t long_endPosX;
    int err_endPosX = JS_ToInt32(ctx, &long_endPosX, argv[2]);
    if(err_endPosX<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int endPosX = (int)long_endPosX;
    int32_t long_endPosY;
    int err_endPosY = JS_ToInt32(ctx, &long_endPosY, argv[3]);
    if(err_endPosY<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int endPosY = (int)long_endPosY;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawLine(startPosX, startPosY, endPosX, endPosY, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawLineV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_startPos = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_startPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 startPos = *ptr_startPos;
    Vector2* ptr_endPos = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_endPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 endPos = *ptr_endPos;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawLineV(startPos, endPos, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawLineEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_startPos = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_startPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 startPos = *ptr_startPos;
    Vector2* ptr_endPos = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_endPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 endPos = *ptr_endPos;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[2]);
    if(err_thick<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawLineEx(startPos, endPos, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawLineBezier(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_startPos = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_startPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 startPos = *ptr_startPos;
    Vector2* ptr_endPos = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_endPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 endPos = *ptr_endPos;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[2]);
    if(err_thick<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawLineBezier(startPos, endPos, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCircle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_centerX;
    int err_centerX = JS_ToInt32(ctx, &long_centerX, argv[0]);
    if(err_centerX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int centerX = (int)long_centerX;
    int32_t long_centerY;
    int err_centerY = JS_ToInt32(ctx, &long_centerY, argv[1]);
    if(err_centerY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int centerY = (int)long_centerY;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCircle(centerX, centerY, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCircleSector(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[1]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    double double_startAngle;
    int err_startAngle = JS_ToFloat64(ctx, &double_startAngle, argv[2]);
    if(err_startAngle<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float startAngle = (float)double_startAngle;
    double double_endAngle;
    int err_endAngle = JS_ToFloat64(ctx, &double_endAngle, argv[3]);
    if(err_endAngle<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float endAngle = (float)double_endAngle;
    int32_t long_segments;
    int err_segments = JS_ToInt32(ctx, &long_segments, argv[4]);
    if(err_segments<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int segments = (int)long_segments;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCircleSectorLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[1]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    double double_startAngle;
    int err_startAngle = JS_ToFloat64(ctx, &double_startAngle, argv[2]);
    if(err_startAngle<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float startAngle = (float)double_startAngle;
    double double_endAngle;
    int err_endAngle = JS_ToFloat64(ctx, &double_endAngle, argv[3]);
    if(err_endAngle<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float endAngle = (float)double_endAngle;
    int32_t long_segments;
    int err_segments = JS_ToInt32(ctx, &long_segments, argv[4]);
    if(err_segments<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int segments = (int)long_segments;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCircleGradient(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_centerX;
    int err_centerX = JS_ToInt32(ctx, &long_centerX, argv[0]);
    if(err_centerX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int centerX = (int)long_centerX;
    int32_t long_centerY;
    int err_centerY = JS_ToInt32(ctx, &long_centerY, argv[1]);
    if(err_centerY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int centerY = (int)long_centerY;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    Color* ptr_inner = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_inner == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color inner = *ptr_inner;
    Color* ptr_outer = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_outer == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color outer = *ptr_outer;
    DrawCircleGradient(centerX, centerY, radius, inner, outer);
    return JS_UNDEFINED;
}

static JSValue js_DrawCircleV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[1]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCircleV(center, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCircleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_centerX;
    int err_centerX = JS_ToInt32(ctx, &long_centerX, argv[0]);
    if(err_centerX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int centerX = (int)long_centerX;
    int32_t long_centerY;
    int err_centerY = JS_ToInt32(ctx, &long_centerY, argv[1]);
    if(err_centerY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int centerY = (int)long_centerY;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCircleLines(centerX, centerY, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCircleLinesV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[1]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCircleLinesV(center, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawEllipse(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_centerX;
    int err_centerX = JS_ToInt32(ctx, &long_centerX, argv[0]);
    if(err_centerX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int centerX = (int)long_centerX;
    int32_t long_centerY;
    int err_centerY = JS_ToInt32(ctx, &long_centerY, argv[1]);
    if(err_centerY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int centerY = (int)long_centerY;
    double double_radiusH;
    int err_radiusH = JS_ToFloat64(ctx, &double_radiusH, argv[2]);
    if(err_radiusH<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radiusH = (float)double_radiusH;
    double double_radiusV;
    int err_radiusV = JS_ToFloat64(ctx, &double_radiusV, argv[3]);
    if(err_radiusV<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float radiusV = (float)double_radiusV;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawEllipse(centerX, centerY, radiusH, radiusV, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawEllipseLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_centerX;
    int err_centerX = JS_ToInt32(ctx, &long_centerX, argv[0]);
    if(err_centerX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int centerX = (int)long_centerX;
    int32_t long_centerY;
    int err_centerY = JS_ToInt32(ctx, &long_centerY, argv[1]);
    if(err_centerY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int centerY = (int)long_centerY;
    double double_radiusH;
    int err_radiusH = JS_ToFloat64(ctx, &double_radiusH, argv[2]);
    if(err_radiusH<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radiusH = (float)double_radiusH;
    double double_radiusV;
    int err_radiusV = JS_ToFloat64(ctx, &double_radiusV, argv[3]);
    if(err_radiusV<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float radiusV = (float)double_radiusV;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawEllipseLines(centerX, centerY, radiusH, radiusV, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRing(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    double double_innerRadius;
    int err_innerRadius = JS_ToFloat64(ctx, &double_innerRadius, argv[1]);
    if(err_innerRadius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float innerRadius = (float)double_innerRadius;
    double double_outerRadius;
    int err_outerRadius = JS_ToFloat64(ctx, &double_outerRadius, argv[2]);
    if(err_outerRadius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float outerRadius = (float)double_outerRadius;
    double double_startAngle;
    int err_startAngle = JS_ToFloat64(ctx, &double_startAngle, argv[3]);
    if(err_startAngle<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float startAngle = (float)double_startAngle;
    double double_endAngle;
    int err_endAngle = JS_ToFloat64(ctx, &double_endAngle, argv[4]);
    if(err_endAngle<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float endAngle = (float)double_endAngle;
    int32_t long_segments;
    int err_segments = JS_ToInt32(ctx, &long_segments, argv[5]);
    if(err_segments<0) {
        JS_ThrowTypeError(ctx, "argv[5] is not numeric");
        return JS_EXCEPTION;
    }
    int segments = (int)long_segments;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[6], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[6] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRingLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    double double_innerRadius;
    int err_innerRadius = JS_ToFloat64(ctx, &double_innerRadius, argv[1]);
    if(err_innerRadius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float innerRadius = (float)double_innerRadius;
    double double_outerRadius;
    int err_outerRadius = JS_ToFloat64(ctx, &double_outerRadius, argv[2]);
    if(err_outerRadius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float outerRadius = (float)double_outerRadius;
    double double_startAngle;
    int err_startAngle = JS_ToFloat64(ctx, &double_startAngle, argv[3]);
    if(err_startAngle<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float startAngle = (float)double_startAngle;
    double double_endAngle;
    int err_endAngle = JS_ToFloat64(ctx, &double_endAngle, argv[4]);
    if(err_endAngle<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float endAngle = (float)double_endAngle;
    int32_t long_segments;
    int err_segments = JS_ToInt32(ctx, &long_segments, argv[5]);
    if(err_segments<0) {
        JS_ThrowTypeError(ctx, "argv[5] is not numeric");
        return JS_EXCEPTION;
    }
    int segments = (int)long_segments;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[6], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[6] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_posX;
    int err_posX = JS_ToInt32(ctx, &long_posX, argv[0]);
    if(err_posX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int posX = (int)long_posX;
    int32_t long_posY;
    int err_posY = JS_ToInt32(ctx, &long_posY, argv[1]);
    if(err_posY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int posY = (int)long_posY;
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[2]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[3]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRectangle(posX, posY, width, height, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    Vector2* ptr_size = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_size == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 size = *ptr_size;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRectangleV(position, size, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRectangleRec(rec, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectanglePro(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    Vector2* ptr_origin = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_origin == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 origin = *ptr_origin;
    double double_rotation;
    int err_rotation = JS_ToFloat64(ctx, &double_rotation, argv[2]);
    if(err_rotation<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float rotation = (float)double_rotation;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRectanglePro(rec, origin, rotation, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleGradientV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_posX;
    int err_posX = JS_ToInt32(ctx, &long_posX, argv[0]);
    if(err_posX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int posX = (int)long_posX;
    int32_t long_posY;
    int err_posY = JS_ToInt32(ctx, &long_posY, argv[1]);
    if(err_posY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int posY = (int)long_posY;
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[2]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[3]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    Color* ptr_top = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_top == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color top = *ptr_top;
    Color* ptr_bottom = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_bottom == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color bottom = *ptr_bottom;
    DrawRectangleGradientV(posX, posY, width, height, top, bottom);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleGradientH(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_posX;
    int err_posX = JS_ToInt32(ctx, &long_posX, argv[0]);
    if(err_posX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int posX = (int)long_posX;
    int32_t long_posY;
    int err_posY = JS_ToInt32(ctx, &long_posY, argv[1]);
    if(err_posY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int posY = (int)long_posY;
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[2]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[3]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    Color* ptr_left = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_left == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color left = *ptr_left;
    Color* ptr_right = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_right == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color right = *ptr_right;
    DrawRectangleGradientH(posX, posY, width, height, left, right);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleGradientEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    Color* ptr_topLeft = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_topLeft == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color topLeft = *ptr_topLeft;
    Color* ptr_bottomLeft = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_bottomLeft == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color bottomLeft = *ptr_bottomLeft;
    Color* ptr_topRight = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_topRight == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color topRight = *ptr_topRight;
    Color* ptr_bottomRight = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_bottomRight == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color bottomRight = *ptr_bottomRight;
    DrawRectangleGradientEx(rec, topLeft, bottomLeft, topRight, bottomRight);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_posX;
    int err_posX = JS_ToInt32(ctx, &long_posX, argv[0]);
    if(err_posX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int posX = (int)long_posX;
    int32_t long_posY;
    int err_posY = JS_ToInt32(ctx, &long_posY, argv[1]);
    if(err_posY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int posY = (int)long_posY;
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[2]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[3]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRectangleLines(posX, posY, width, height, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleLinesEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    double double_lineThick;
    int err_lineThick = JS_ToFloat64(ctx, &double_lineThick, argv[1]);
    if(err_lineThick<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float lineThick = (float)double_lineThick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRectangleLinesEx(rec, lineThick, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleRounded(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    double double_roundness;
    int err_roundness = JS_ToFloat64(ctx, &double_roundness, argv[1]);
    if(err_roundness<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float roundness = (float)double_roundness;
    int32_t long_segments;
    int err_segments = JS_ToInt32(ctx, &long_segments, argv[2]);
    if(err_segments<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int segments = (int)long_segments;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRectangleRounded(rec, roundness, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleRoundedLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    double double_roundness;
    int err_roundness = JS_ToFloat64(ctx, &double_roundness, argv[1]);
    if(err_roundness<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float roundness = (float)double_roundness;
    int32_t long_segments;
    int err_segments = JS_ToInt32(ctx, &long_segments, argv[2]);
    if(err_segments<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int segments = (int)long_segments;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRectangleRoundedLines(rec, roundness, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleRoundedLinesEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    double double_roundness;
    int err_roundness = JS_ToFloat64(ctx, &double_roundness, argv[1]);
    if(err_roundness<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float roundness = (float)double_roundness;
    int32_t long_segments;
    int err_segments = JS_ToInt32(ctx, &long_segments, argv[2]);
    if(err_segments<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int segments = (int)long_segments;
    double double_lineThick;
    int err_lineThick = JS_ToFloat64(ctx, &double_lineThick, argv[3]);
    if(err_lineThick<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float lineThick = (float)double_lineThick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRectangleRoundedLinesEx(rec, roundness, segments, lineThick, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawTriangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v1 = *ptr_v1;
    Vector2* ptr_v2 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v2 = *ptr_v2;
    Vector2* ptr_v3 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_v3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v3 = *ptr_v3;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawTriangle(v1, v2, v3, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawTriangleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v1 = *ptr_v1;
    Vector2* ptr_v2 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v2 = *ptr_v2;
    Vector2* ptr_v3 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_v3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v3 = *ptr_v3;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawTriangleLines(v1, v2, v3, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawPoly(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    int32_t long_sides;
    int err_sides = JS_ToInt32(ctx, &long_sides, argv[1]);
    if(err_sides<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int sides = (int)long_sides;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    double double_rotation;
    int err_rotation = JS_ToFloat64(ctx, &double_rotation, argv[3]);
    if(err_rotation<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float rotation = (float)double_rotation;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawPoly(center, sides, radius, rotation, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawPolyLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    int32_t long_sides;
    int err_sides = JS_ToInt32(ctx, &long_sides, argv[1]);
    if(err_sides<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int sides = (int)long_sides;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    double double_rotation;
    int err_rotation = JS_ToFloat64(ctx, &double_rotation, argv[3]);
    if(err_rotation<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float rotation = (float)double_rotation;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawPolyLines(center, sides, radius, rotation, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawPolyLinesEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    int32_t long_sides;
    int err_sides = JS_ToInt32(ctx, &long_sides, argv[1]);
    if(err_sides<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int sides = (int)long_sides;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    double double_rotation;
    int err_rotation = JS_ToFloat64(ctx, &double_rotation, argv[3]);
    if(err_rotation<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float rotation = (float)double_rotation;
    double double_lineThick;
    int err_lineThick = JS_ToFloat64(ctx, &double_lineThick, argv[4]);
    if(err_lineThick<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float lineThick = (float)double_lineThick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawPolyLinesEx(center, sides, radius, rotation, lineThick, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawSplineLinear(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 * points;
    JSValue da_points;
    int64_t size_points;
    if(JS_IsArray(argv[0]) == 1) {
        if(JS_GetLength(ctx,argv[0],&size_points)==-1) {
            return JS_EXCEPTION;
        }
        points = (Vector2 *)js_malloc(ctx, size_points * sizeof(Vector2));
        for(int i0=0; i0 < size_points; i0++){
            JSValue js_points = JS_GetPropertyUint32(ctx,argv[0],i0);
            Vector2* ptr_pointsi0 = (Vector2*)JS_GetOpaque(js_points, js_Vector2_class_id);
            if(ptr_pointsi0 == NULL) {
                JS_ThrowTypeError(ctx, "js_points does not allow null");
                return JS_EXCEPTION;
            }
            points[i0] = *ptr_pointsi0;
            JS_FreeValue(ctx, js_points);
        }
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_points = JS_DupValue(ctx,argv[0]);
        size_t size_points;
        points = (Vector2 *)JS_GetArrayBuffer(ctx, &size_points, da_points);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Vector2 *");
        return JS_EXCEPTION;
    }
    int32_t long_pointCount;
    int err_pointCount = JS_ToInt32(ctx, &long_pointCount, argv[1]);
    if(err_pointCount<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int pointCount = (int)long_pointCount;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[2]);
    if(err_thick<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSplineLinear((const Vector2 *)points, pointCount, thick, color);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, points);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_points);
    }
    return JS_UNDEFINED;
}

static JSValue js_DrawSplineBasis(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 * points;
    JSValue da_points;
    int64_t size_points;
    if(JS_IsArray(argv[0]) == 1) {
        if(JS_GetLength(ctx,argv[0],&size_points)==-1) {
            return JS_EXCEPTION;
        }
        points = (Vector2 *)js_malloc(ctx, size_points * sizeof(Vector2));
        for(int i0=0; i0 < size_points; i0++){
            JSValue js_points = JS_GetPropertyUint32(ctx,argv[0],i0);
            Vector2* ptr_pointsi0 = (Vector2*)JS_GetOpaque(js_points, js_Vector2_class_id);
            if(ptr_pointsi0 == NULL) {
                JS_ThrowTypeError(ctx, "js_points does not allow null");
                return JS_EXCEPTION;
            }
            points[i0] = *ptr_pointsi0;
            JS_FreeValue(ctx, js_points);
        }
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_points = JS_DupValue(ctx,argv[0]);
        size_t size_points;
        points = (Vector2 *)JS_GetArrayBuffer(ctx, &size_points, da_points);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Vector2 *");
        return JS_EXCEPTION;
    }
    int32_t long_pointCount;
    int err_pointCount = JS_ToInt32(ctx, &long_pointCount, argv[1]);
    if(err_pointCount<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int pointCount = (int)long_pointCount;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[2]);
    if(err_thick<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSplineBasis((const Vector2 *)points, pointCount, thick, color);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, points);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_points);
    }
    return JS_UNDEFINED;
}

static JSValue js_DrawSplineCatmullRom(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 * points;
    JSValue da_points;
    int64_t size_points;
    if(JS_IsArray(argv[0]) == 1) {
        if(JS_GetLength(ctx,argv[0],&size_points)==-1) {
            return JS_EXCEPTION;
        }
        points = (Vector2 *)js_malloc(ctx, size_points * sizeof(Vector2));
        for(int i0=0; i0 < size_points; i0++){
            JSValue js_points = JS_GetPropertyUint32(ctx,argv[0],i0);
            Vector2* ptr_pointsi0 = (Vector2*)JS_GetOpaque(js_points, js_Vector2_class_id);
            if(ptr_pointsi0 == NULL) {
                JS_ThrowTypeError(ctx, "js_points does not allow null");
                return JS_EXCEPTION;
            }
            points[i0] = *ptr_pointsi0;
            JS_FreeValue(ctx, js_points);
        }
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_points = JS_DupValue(ctx,argv[0]);
        size_t size_points;
        points = (Vector2 *)JS_GetArrayBuffer(ctx, &size_points, da_points);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Vector2 *");
        return JS_EXCEPTION;
    }
    int32_t long_pointCount;
    int err_pointCount = JS_ToInt32(ctx, &long_pointCount, argv[1]);
    if(err_pointCount<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int pointCount = (int)long_pointCount;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[2]);
    if(err_thick<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSplineCatmullRom((const Vector2 *)points, pointCount, thick, color);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, points);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_points);
    }
    return JS_UNDEFINED;
}

static JSValue js_DrawSplineBezierQuadratic(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 * points;
    JSValue da_points;
    int64_t size_points;
    if(JS_IsArray(argv[0]) == 1) {
        if(JS_GetLength(ctx,argv[0],&size_points)==-1) {
            return JS_EXCEPTION;
        }
        points = (Vector2 *)js_malloc(ctx, size_points * sizeof(Vector2));
        for(int i0=0; i0 < size_points; i0++){
            JSValue js_points = JS_GetPropertyUint32(ctx,argv[0],i0);
            Vector2* ptr_pointsi0 = (Vector2*)JS_GetOpaque(js_points, js_Vector2_class_id);
            if(ptr_pointsi0 == NULL) {
                JS_ThrowTypeError(ctx, "js_points does not allow null");
                return JS_EXCEPTION;
            }
            points[i0] = *ptr_pointsi0;
            JS_FreeValue(ctx, js_points);
        }
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_points = JS_DupValue(ctx,argv[0]);
        size_t size_points;
        points = (Vector2 *)JS_GetArrayBuffer(ctx, &size_points, da_points);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Vector2 *");
        return JS_EXCEPTION;
    }
    int32_t long_pointCount;
    int err_pointCount = JS_ToInt32(ctx, &long_pointCount, argv[1]);
    if(err_pointCount<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int pointCount = (int)long_pointCount;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[2]);
    if(err_thick<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSplineBezierQuadratic((const Vector2 *)points, pointCount, thick, color);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, points);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_points);
    }
    return JS_UNDEFINED;
}

static JSValue js_DrawSplineBezierCubic(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 * points;
    JSValue da_points;
    int64_t size_points;
    if(JS_IsArray(argv[0]) == 1) {
        if(JS_GetLength(ctx,argv[0],&size_points)==-1) {
            return JS_EXCEPTION;
        }
        points = (Vector2 *)js_malloc(ctx, size_points * sizeof(Vector2));
        for(int i0=0; i0 < size_points; i0++){
            JSValue js_points = JS_GetPropertyUint32(ctx,argv[0],i0);
            Vector2* ptr_pointsi0 = (Vector2*)JS_GetOpaque(js_points, js_Vector2_class_id);
            if(ptr_pointsi0 == NULL) {
                JS_ThrowTypeError(ctx, "js_points does not allow null");
                return JS_EXCEPTION;
            }
            points[i0] = *ptr_pointsi0;
            JS_FreeValue(ctx, js_points);
        }
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_points = JS_DupValue(ctx,argv[0]);
        size_t size_points;
        points = (Vector2 *)JS_GetArrayBuffer(ctx, &size_points, da_points);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Vector2 *");
        return JS_EXCEPTION;
    }
    int32_t long_pointCount;
    int err_pointCount = JS_ToInt32(ctx, &long_pointCount, argv[1]);
    if(err_pointCount<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int pointCount = (int)long_pointCount;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[2]);
    if(err_thick<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSplineBezierCubic((const Vector2 *)points, pointCount, thick, color);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, points);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_points);
    }
    return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentLinear(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_p2 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_p2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p2 = *ptr_p2;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[2]);
    if(err_thick<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSplineSegmentLinear(p1, p2, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentBasis(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_p2 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_p2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p2 = *ptr_p2;
    Vector2* ptr_p3 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_p3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p3 = *ptr_p3;
    Vector2* ptr_p4 = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_p4 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p4 = *ptr_p4;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[4]);
    if(err_thick<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSplineSegmentBasis(p1, p2, p3, p4, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentCatmullRom(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_p2 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_p2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p2 = *ptr_p2;
    Vector2* ptr_p3 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_p3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p3 = *ptr_p3;
    Vector2* ptr_p4 = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_p4 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p4 = *ptr_p4;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[4]);
    if(err_thick<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSplineSegmentCatmullRom(p1, p2, p3, p4, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentBezierQuadratic(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_c2 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_c2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 c2 = *ptr_c2;
    Vector2* ptr_p3 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_p3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p3 = *ptr_p3;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[3]);
    if(err_thick<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSplineSegmentBezierQuadratic(p1, c2, p3, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentBezierCubic(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_c2 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_c2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 c2 = *ptr_c2;
    Vector2* ptr_c3 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_c3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 c3 = *ptr_c3;
    Vector2* ptr_p4 = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_p4 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p4 = *ptr_p4;
    double double_thick;
    int err_thick = JS_ToFloat64(ctx, &double_thick, argv[4]);
    if(err_thick<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float thick = (float)double_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSplineSegmentBezierCubic(p1, c2, c3, p4, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_GetSplinePointLinear(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_startPos = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_startPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 startPos = *ptr_startPos;
    Vector2* ptr_endPos = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_endPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 endPos = *ptr_endPos;
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[2]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    Vector2 returnVal = GetSplinePointLinear(startPos, endPos, t);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetSplinePointBasis(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_p2 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_p2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p2 = *ptr_p2;
    Vector2* ptr_p3 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_p3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p3 = *ptr_p3;
    Vector2* ptr_p4 = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_p4 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p4 = *ptr_p4;
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[4]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    Vector2 returnVal = GetSplinePointBasis(p1, p2, p3, p4, t);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetSplinePointCatmullRom(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_p2 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_p2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p2 = *ptr_p2;
    Vector2* ptr_p3 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_p3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p3 = *ptr_p3;
    Vector2* ptr_p4 = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_p4 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p4 = *ptr_p4;
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[4]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    Vector2 returnVal = GetSplinePointCatmullRom(p1, p2, p3, p4, t);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetSplinePointBezierQuad(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_c2 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_c2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 c2 = *ptr_c2;
    Vector2* ptr_p3 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_p3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p3 = *ptr_p3;
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[3]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    Vector2 returnVal = GetSplinePointBezierQuad(p1, c2, p3, t);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetSplinePointBezierCubic(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_c2 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_c2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 c2 = *ptr_c2;
    Vector2* ptr_c3 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_c3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 c3 = *ptr_c3;
    Vector2* ptr_p4 = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_p4 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p4 = *ptr_p4;
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[4]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    Vector2 returnVal = GetSplinePointBezierCubic(p1, c2, c3, p4, t);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_CheckCollisionRecs(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_rec1 = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_rec1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec1 = *ptr_rec1;
    Rectangle* ptr_rec2 = (Rectangle*)JS_GetOpaque(argv[1], js_Rectangle_class_id);
    if(ptr_rec2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec2 = *ptr_rec2;
    bool returnVal = CheckCollisionRecs(rec1, rec2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_CheckCollisionCircles(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center1 = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center1 = *ptr_center1;
    double double_radius1;
    int err_radius1 = JS_ToFloat64(ctx, &double_radius1, argv[1]);
    if(err_radius1<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius1 = (float)double_radius1;
    Vector2* ptr_center2 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_center2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center2 = *ptr_center2;
    double double_radius2;
    int err_radius2 = JS_ToFloat64(ctx, &double_radius2, argv[3]);
    if(err_radius2<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float radius2 = (float)double_radius2;
    bool returnVal = CheckCollisionCircles(center1, radius1, center2, radius2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_CheckCollisionCircleRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[1]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[2], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    bool returnVal = CheckCollisionCircleRec(center, radius, rec);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_CheckCollisionCircleLine(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[1]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_p2 = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_p2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p2 = *ptr_p2;
    bool returnVal = CheckCollisionCircleLine(center, radius, p1, p2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_CheckCollisionPointRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_point = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_point == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 point = *ptr_point;
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[1], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    bool returnVal = CheckCollisionPointRec(point, rec);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_CheckCollisionPointCircle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_point = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_point == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 point = *ptr_point;
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    bool returnVal = CheckCollisionPointCircle(point, center, radius);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_CheckCollisionPointTriangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_point = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_point == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 point = *ptr_point;
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_p2 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_p2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p2 = *ptr_p2;
    Vector2* ptr_p3 = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_p3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p3 = *ptr_p3;
    bool returnVal = CheckCollisionPointTriangle(point, p1, p2, p3);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_CheckCollisionPointLine(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_point = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_point == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 point = *ptr_point;
    Vector2* ptr_p1 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p1 = *ptr_p1;
    Vector2* ptr_p2 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_p2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p2 = *ptr_p2;
    int32_t long_threshold;
    int err_threshold = JS_ToInt32(ctx, &long_threshold, argv[3]);
    if(err_threshold<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int threshold = (int)long_threshold;
    bool returnVal = CheckCollisionPointLine(point, p1, p2, threshold);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_GetCollisionRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_rec1 = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_rec1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec1 = *ptr_rec1;
    Rectangle* ptr_rec2 = (Rectangle*)JS_GetOpaque(argv[1], js_Rectangle_class_id);
    if(ptr_rec2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec2 = *ptr_rec2;
    Rectangle returnVal = GetCollisionRec(rec1, rec2);
    Rectangle* ptr_ret = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Image returnVal = LoadImage((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadImageRaw(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[1]);
    if(err_width<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, fileName);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, fileName);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_fileName);
        }
        else {
            JSClassID classid_fileName = JS_GetClassID(argv[0]);
            if(classid_fileName==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_fileName);
            }
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[2]);
    if(err_height<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, fileName);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, fileName);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_fileName);
        }
        else {
            JSClassID classid_fileName = JS_GetClassID(argv[0]);
            if(classid_fileName==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_fileName);
            }
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    int32_t long_format;
    int err_format = JS_ToInt32(ctx, &long_format, argv[3]);
    if(err_format<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, fileName);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, fileName);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_fileName);
        }
        else {
            JSClassID classid_fileName = JS_GetClassID(argv[0]);
            if(classid_fileName==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_fileName);
            }
        }
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int format = (int)long_format;
    int32_t long_headerSize;
    int err_headerSize = JS_ToInt32(ctx, &long_headerSize, argv[4]);
    if(err_headerSize<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, fileName);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, fileName);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_fileName);
        }
        else {
            JSClassID classid_fileName = JS_GetClassID(argv[0]);
            if(classid_fileName==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_fileName);
            }
        }
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int headerSize = (int)long_headerSize;
    Image returnVal = LoadImageRaw((const char *)fileName, width, height, format, headerSize);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadImageAnimFromMemory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * fileType;
    int64_t size_fileType;
    if(JS_IsString(argv[0]) == 1) {
        fileType = (char *)JS_ToCStringLen(ctx, &size_fileType, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, fileType);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_fileType = JS_DupValue(ctx,argv[0]);
        size_t size_fileType;
        fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, da_fileType);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[0]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileType;
            size_t size_fileType;
            JSValue da_fileType = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileType,&size_fileType,NULL);
            fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, da_fileType);
            fileType+=offset_fileType;
            size_fileType-=offset_fileType;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileType);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    unsigned char * fileData;
    int64_t size_fileData;
    if(JS_IsArray(argv[1]) == 1) {
        if(JS_GetLength(ctx,argv[1],&size_fileData)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        fileData = (unsigned char *)js_malloc(ctx, size_fileData * sizeof(unsigned char));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, fileData);
        for(int i0=0; i0 < size_fileData; i0++){
            JSValue js_fileData = JS_GetPropertyUint32(ctx,argv[1],i0);
            uint32_t long_fileDatai0;
            int err_fileDatai0 = JS_ToUint32(ctx, &long_fileDatai0, js_fileData);
            if(err_fileDatai0<0) {
                JS_ThrowTypeError(ctx, "js_fileData is not numeric");
                return JS_EXCEPTION;
            }
            fileData[i0] = (unsigned char)long_fileDatai0;
            JS_FreeValue(ctx, js_fileData);
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_fileData = JS_DupValue(ctx,argv[1]);
        size_t size_fileData;
        fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, da_fileData);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileData);
    }
    else {
        JSClassID classid_fileData = JS_GetClassID(argv[1]);
        if(classid_fileData==JS_CLASS_UINT8_ARRAY || classid_fileData==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_fileData;
            size_t size_fileData;
            JSValue da_fileData = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileData,&size_fileData,NULL);
            fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, da_fileData);
            fileData+=offset_fileData;
            size_fileData-=offset_fileData;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileData);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type unsigned char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_dataSize;
    int err_dataSize = JS_ToInt32(ctx, &long_dataSize, argv[2]);
    if(err_dataSize<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int dataSize = (int)long_dataSize;
    int * frames;
    int64_t size_frames;
    if(JS_IsArray(argv[3]) == 1) {
        if(JS_GetLength(ctx,argv[3],&size_frames)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        frames = (int *)js_malloc(ctx, size_frames * sizeof(int));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, frames);
        for(int i0=0; i0 < size_frames; i0++){
            JSValue js_frames = JS_GetPropertyUint32(ctx,argv[3],i0);
            int32_t long_framesi0;
            int err_framesi0 = JS_ToInt32(ctx, &long_framesi0, js_frames);
            if(err_framesi0<0) {
                JS_ThrowTypeError(ctx, "js_frames is not numeric");
                return JS_EXCEPTION;
            }
            frames[i0] = (int)long_framesi0;
            JS_FreeValue(ctx, js_frames);
        }
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        JSValue da_frames = JS_DupValue(ctx,argv[3]);
        size_t size_frames;
        frames = (int *)JS_GetArrayBuffer(ctx, &size_frames, da_frames);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_frames);
    }
    else {
        JSClassID classid_frames = JS_GetClassID(argv[3]);
        if(classid_frames==JS_CLASS_INT16_ARRAY) {
            size_t offset_frames;
            size_t size_frames;
            JSValue da_frames = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_frames,&size_frames,NULL);
            frames = (int *)JS_GetArrayBuffer(ctx, &size_frames, da_frames);
            frames+=offset_frames;
            size_frames-=offset_frames;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_frames);
        }
        else {
            int32_t long_js_frames;
            int err_js_frames = JS_ToInt32(ctx, &long_js_frames, argv[3]);
            if(err_js_frames<0) {
                memoryClear(ctx, memoryHead);
                JS_ThrowTypeError(ctx, "argv[3] is not numeric");
                return JS_EXCEPTION;
            }
            int js_frames = (int)long_js_frames;
            frames = &js_frames;
        }
    }
    Image returnVal = LoadImageAnimFromMemory((const char *)fileType, (const unsigned char *)fileData, dataSize, frames);
    if(JS_IsArray(argv[3]) == 1) {
        JSValue js_argv3 = JS_NewInt32(ctx, (long)frames[0]);
        JS_DefinePropertyValueUint32(ctx,argv[3],0,js_argv3,JS_PROP_C_W_E);
    }
    memoryClear(ctx, memoryHead);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadImageFromMemory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * fileType;
    int64_t size_fileType;
    if(JS_IsString(argv[0]) == 1) {
        fileType = (char *)JS_ToCStringLen(ctx, &size_fileType, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, fileType);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_fileType = JS_DupValue(ctx,argv[0]);
        size_t size_fileType;
        fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, da_fileType);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[0]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileType;
            size_t size_fileType;
            JSValue da_fileType = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileType,&size_fileType,NULL);
            fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, da_fileType);
            fileType+=offset_fileType;
            size_fileType-=offset_fileType;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileType);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    unsigned char * fileData;
    int64_t size_fileData;
    if(JS_IsArray(argv[1]) == 1) {
        if(JS_GetLength(ctx,argv[1],&size_fileData)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        fileData = (unsigned char *)js_malloc(ctx, size_fileData * sizeof(unsigned char));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, fileData);
        for(int i0=0; i0 < size_fileData; i0++){
            JSValue js_fileData = JS_GetPropertyUint32(ctx,argv[1],i0);
            uint32_t long_fileDatai0;
            int err_fileDatai0 = JS_ToUint32(ctx, &long_fileDatai0, js_fileData);
            if(err_fileDatai0<0) {
                JS_ThrowTypeError(ctx, "js_fileData is not numeric");
                return JS_EXCEPTION;
            }
            fileData[i0] = (unsigned char)long_fileDatai0;
            JS_FreeValue(ctx, js_fileData);
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_fileData = JS_DupValue(ctx,argv[1]);
        size_t size_fileData;
        fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, da_fileData);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileData);
    }
    else {
        JSClassID classid_fileData = JS_GetClassID(argv[1]);
        if(classid_fileData==JS_CLASS_UINT8_ARRAY || classid_fileData==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_fileData;
            size_t size_fileData;
            JSValue da_fileData = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileData,&size_fileData,NULL);
            fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, da_fileData);
            fileData+=offset_fileData;
            size_fileData-=offset_fileData;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileData);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type unsigned char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_dataSize;
    int err_dataSize = JS_ToInt32(ctx, &long_dataSize, argv[2]);
    if(err_dataSize<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int dataSize = (int)long_dataSize;
    Image returnVal = LoadImageFromMemory((const char *)fileType, (const unsigned char *)fileData, dataSize);
    memoryClear(ctx, memoryHead);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadImageFromTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    Image returnVal = LoadImageFromTexture(texture);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadImageFromScreen(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image returnVal = LoadImageFromScreen();
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_IsImageValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    bool returnVal = IsImageValid(image);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_UnloadImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    UnloadImage(image);
    return JS_UNDEFINED;
}

static JSValue js_ExportImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[1]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[1]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ExportImage(image, (const char *)fileName);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_ExportImageToMemory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    char * fileType;
    JSValue da_fileType;
    int64_t size_fileType;
    if(JS_IsString(argv[1]) == 1) {
        fileType = (char *)JS_ToCStringLen(ctx, &size_fileType, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_fileType = JS_DupValue(ctx,argv[1]);
        size_t size_fileType;
        fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, da_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[1]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileType;
            size_t size_fileType;
            da_fileType = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileType,&size_fileType,NULL);
            fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, da_fileType);
            fileType+=offset_fileType;
            size_fileType-=offset_fileType;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int * fileSize;
    JSValue da_fileSize;
    int64_t size_fileSize;
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_fileSize)==-1) {
            if(JS_IsArray(argv[1]) == 1) {
                js_free(ctx, fileType);
            }
            else if(JS_IsString(argv[1]) == 1) {
                JS_FreeCString(ctx, fileType);
            }
            else if(JS_IsArrayBuffer(argv[1]) == 1) {
                JS_FreeValue(ctx, da_fileType);
            }
            else {
                JSClassID classid_fileType = JS_GetClassID(argv[1]);
                if(classid_fileType==JS_CLASS_INT8_ARRAY) {
                    js_free(ctx, &da_fileType);
                }
            }
            return JS_EXCEPTION;
        }
        fileSize = (int *)js_malloc(ctx, size_fileSize * sizeof(int));
        for(int i0=0; i0 < size_fileSize; i0++){
            JSValue js_fileSize = JS_GetPropertyUint32(ctx,argv[2],i0);
            int32_t long_fileSizei0;
            int err_fileSizei0 = JS_ToInt32(ctx, &long_fileSizei0, js_fileSize);
            if(err_fileSizei0<0) {
                JS_ThrowTypeError(ctx, "js_fileSize is not numeric");
                return JS_EXCEPTION;
            }
            fileSize[i0] = (int)long_fileSizei0;
            JS_FreeValue(ctx, js_fileSize);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        da_fileSize = JS_DupValue(ctx,argv[2]);
        size_t size_fileSize;
        fileSize = (int *)JS_GetArrayBuffer(ctx, &size_fileSize, da_fileSize);
    }
    else {
        JSClassID classid_fileSize = JS_GetClassID(argv[2]);
        if(classid_fileSize==JS_CLASS_INT16_ARRAY) {
            size_t offset_fileSize;
            size_t size_fileSize;
            da_fileSize = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_fileSize,&size_fileSize,NULL);
            fileSize = (int *)JS_GetArrayBuffer(ctx, &size_fileSize, da_fileSize);
            fileSize+=offset_fileSize;
            size_fileSize-=offset_fileSize;
        }
        else {
            int32_t long_js_fileSize;
            int err_js_fileSize = JS_ToInt32(ctx, &long_js_fileSize, argv[2]);
            if(err_js_fileSize<0) {
                if(JS_IsArray(argv[1]) == 1) {
                    js_free(ctx, fileType);
                }
                else if(JS_IsString(argv[1]) == 1) {
                    JS_FreeCString(ctx, fileType);
                }
                else if(JS_IsArrayBuffer(argv[1]) == 1) {
                    JS_FreeValue(ctx, da_fileType);
                }
                else {
                    JSClassID classid_fileType = JS_GetClassID(argv[1]);
                    if(classid_fileType==JS_CLASS_INT8_ARRAY) {
                        js_free(ctx, &da_fileType);
                    }
                }
                JS_ThrowTypeError(ctx, "argv[2] is not numeric");
                return JS_EXCEPTION;
            }
            int js_fileSize = (int)long_js_fileSize;
            fileSize = &js_fileSize;
        }
    }
    unsigned char * returnVal = ExportImageToMemory(image, (const char *)fileType, fileSize);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewInt32(ctx, (long)fileSize[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, fileType);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileType);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[1]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileType);
        }
    }
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, fileSize);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_fileSize);
    }
    else {
        JSClassID classid_fileSize = JS_GetClassID(argv[2]);
        if(classid_fileSize==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &da_fileSize);
        }
    }
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < fileSize[0]; i0++){
        JSValue js_ret = JS_NewUint32(ctx, (unsigned long)returnVal[i0]);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_GenImageColor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    Image returnVal = GenImageColor(width, height, color);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenImageGradientLinear(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    int32_t long_direction;
    int err_direction = JS_ToInt32(ctx, &long_direction, argv[2]);
    if(err_direction<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int direction = (int)long_direction;
    Color* ptr_start = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_start == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color start = *ptr_start;
    Color* ptr_end = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_end == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color end = *ptr_end;
    Image returnVal = GenImageGradientLinear(width, height, direction, start, end);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenImageGradientRadial(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    double double_density;
    int err_density = JS_ToFloat64(ctx, &double_density, argv[2]);
    if(err_density<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float density = (float)double_density;
    Color* ptr_inner = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_inner == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color inner = *ptr_inner;
    Color* ptr_outer = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_outer == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color outer = *ptr_outer;
    Image returnVal = GenImageGradientRadial(width, height, density, inner, outer);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenImageGradientSquare(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    double double_density;
    int err_density = JS_ToFloat64(ctx, &double_density, argv[2]);
    if(err_density<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float density = (float)double_density;
    Color* ptr_inner = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_inner == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color inner = *ptr_inner;
    Color* ptr_outer = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_outer == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color outer = *ptr_outer;
    Image returnVal = GenImageGradientSquare(width, height, density, inner, outer);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenImageChecked(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    int32_t long_checksX;
    int err_checksX = JS_ToInt32(ctx, &long_checksX, argv[2]);
    if(err_checksX<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int checksX = (int)long_checksX;
    int32_t long_checksY;
    int err_checksY = JS_ToInt32(ctx, &long_checksY, argv[3]);
    if(err_checksY<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int checksY = (int)long_checksY;
    Color* ptr_col1 = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_col1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color col1 = *ptr_col1;
    Color* ptr_col2 = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_col2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color col2 = *ptr_col2;
    Image returnVal = GenImageChecked(width, height, checksX, checksY, col1, col2);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenImageWhiteNoise(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    double double_factor;
    int err_factor = JS_ToFloat64(ctx, &double_factor, argv[2]);
    if(err_factor<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float factor = (float)double_factor;
    Image returnVal = GenImageWhiteNoise(width, height, factor);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenImagePerlinNoise(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    int32_t long_offsetX;
    int err_offsetX = JS_ToInt32(ctx, &long_offsetX, argv[2]);
    if(err_offsetX<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int offsetX = (int)long_offsetX;
    int32_t long_offsetY;
    int err_offsetY = JS_ToInt32(ctx, &long_offsetY, argv[3]);
    if(err_offsetY<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int offsetY = (int)long_offsetY;
    double double_scale;
    int err_scale = JS_ToFloat64(ctx, &double_scale, argv[4]);
    if(err_scale<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float scale = (float)double_scale;
    Image returnVal = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenImageCellular(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    int32_t long_tileSize;
    int err_tileSize = JS_ToInt32(ctx, &long_tileSize, argv[2]);
    if(err_tileSize<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int tileSize = (int)long_tileSize;
    Image returnVal = GenImageCellular(width, height, tileSize);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenImageText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[2]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        da_text = JS_DupValue(ctx,argv[2]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[2]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[2] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Image returnVal = GenImageText(width, height, (const char *)text);
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[2]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ImageCopy(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    Image returnVal = ImageCopy(image);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ImageFromImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[1], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    Image returnVal = ImageFromImage(image, rec);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ImageFromChannel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    int32_t long_selectedChannel;
    int err_selectedChannel = JS_ToInt32(ctx, &long_selectedChannel, argv[1]);
    if(err_selectedChannel<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int selectedChannel = (int)long_selectedChannel;
    Image returnVal = ImageFromChannel(image, selectedChannel);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ImageText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_fontSize;
    int err_fontSize = JS_ToInt32(ctx, &long_fontSize, argv[1]);
    if(err_fontSize<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[0]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int fontSize = (int)long_fontSize;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[0]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    Image returnVal = ImageText((const char *)text, fontSize, color);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ImageTextEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* ptr_font = (Font*)JS_GetOpaque(argv[0], js_Font_class_id);
    if(ptr_font == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Font font = *ptr_font;
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    double double_fontSize;
    int err_fontSize = JS_ToFloat64(ctx, &double_fontSize, argv[2]);
    if(err_fontSize<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float fontSize = (float)double_fontSize;
    double double_spacing;
    int err_spacing = JS_ToFloat64(ctx, &double_spacing, argv[3]);
    if(err_spacing<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float spacing = (float)double_spacing;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_tint == NULL) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    Image returnVal = ImageTextEx(font, (const char *)text, fontSize, spacing, tint);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ImageFormat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_newFormat;
    int err_newFormat = JS_ToInt32(ctx, &long_newFormat, argv[1]);
    if(err_newFormat<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int newFormat = (int)long_newFormat;
    ImageFormat(image, newFormat);
    return JS_UNDEFINED;
}

static JSValue js_ImageToPOT(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Color* ptr_fill = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_fill == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color fill = *ptr_fill;
    ImageToPOT(image, fill);
    return JS_UNDEFINED;
}

static JSValue js_ImageCrop(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Rectangle* ptr_crop = (Rectangle*)JS_GetOpaque(argv[1], js_Rectangle_class_id);
    if(ptr_crop == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle crop = *ptr_crop;
    ImageCrop(image, crop);
    return JS_UNDEFINED;
}

static JSValue js_ImageAlphaCrop(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    double double_threshold;
    int err_threshold = JS_ToFloat64(ctx, &double_threshold, argv[1]);
    if(err_threshold<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float threshold = (float)double_threshold;
    ImageAlphaCrop(image, threshold);
    return JS_UNDEFINED;
}

static JSValue js_ImageAlphaClear(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Color* ptr_color = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    double double_threshold;
    int err_threshold = JS_ToFloat64(ctx, &double_threshold, argv[2]);
    if(err_threshold<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float threshold = (float)double_threshold;
    ImageAlphaClear(image, color, threshold);
    return JS_UNDEFINED;
}

static JSValue js_ImageAlphaMask(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Image* ptr_alphaMask = (Image*)JS_GetOpaque(argv[1], js_Image_class_id);
    if(ptr_alphaMask == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Image alphaMask = *ptr_alphaMask;
    ImageAlphaMask(image, alphaMask);
    return JS_UNDEFINED;
}

static JSValue js_ImageAlphaPremultiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    ImageAlphaPremultiply(image);
    return JS_UNDEFINED;
}

static JSValue js_ImageBlurGaussian(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_blurSize;
    int err_blurSize = JS_ToInt32(ctx, &long_blurSize, argv[1]);
    if(err_blurSize<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int blurSize = (int)long_blurSize;
    ImageBlurGaussian(image, blurSize);
    return JS_UNDEFINED;
}

static JSValue js_ImageKernelConvolution(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    float * kernel;
    JSValue da_kernel;
    int64_t size_kernel;
    if(JS_IsArray(argv[1]) == 1) {
        if(JS_GetLength(ctx,argv[1],&size_kernel)==-1) {
            return JS_EXCEPTION;
        }
        kernel = (float *)js_malloc(ctx, size_kernel * sizeof(float));
        for(int i0=0; i0 < size_kernel; i0++){
            JSValue js_kernel = JS_GetPropertyUint32(ctx,argv[1],i0);
            double double_kerneli0;
            int err_kerneli0 = JS_ToFloat64(ctx, &double_kerneli0, js_kernel);
            if(err_kerneli0<0) {
                JS_ThrowTypeError(ctx, "js_kernel is not numeric");
                return JS_EXCEPTION;
            }
            kernel[i0] = (float)double_kerneli0;
            JS_FreeValue(ctx, js_kernel);
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_kernel = JS_DupValue(ctx,argv[1]);
        size_t size_kernel;
        kernel = (float *)JS_GetArrayBuffer(ctx, &size_kernel, da_kernel);
    }
    else {
        JSClassID classid_kernel = JS_GetClassID(argv[1]);
        if(classid_kernel==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_kernel;
            size_t size_kernel;
            da_kernel = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_kernel,&size_kernel,NULL);
            kernel = (float *)JS_GetArrayBuffer(ctx, &size_kernel, da_kernel);
            kernel+=offset_kernel;
            size_kernel-=offset_kernel;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type float *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_kernelSize;
    int err_kernelSize = JS_ToInt32(ctx, &long_kernelSize, argv[2]);
    if(err_kernelSize<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, kernel);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_kernel);
        }
        else {
            JSClassID classid_kernel = JS_GetClassID(argv[1]);
            if(classid_kernel==JS_CLASS_FLOAT32_ARRAY) {
                js_free(ctx, &da_kernel);
            }
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int kernelSize = (int)long_kernelSize;
    ImageKernelConvolution(image, (const float *)kernel, kernelSize);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, kernel);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_kernel);
    }
    else {
        JSClassID classid_kernel = JS_GetClassID(argv[1]);
        if(classid_kernel==JS_CLASS_FLOAT32_ARRAY) {
            js_free(ctx, &da_kernel);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_ImageResize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_newWidth;
    int err_newWidth = JS_ToInt32(ctx, &long_newWidth, argv[1]);
    if(err_newWidth<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int newWidth = (int)long_newWidth;
    int32_t long_newHeight;
    int err_newHeight = JS_ToInt32(ctx, &long_newHeight, argv[2]);
    if(err_newHeight<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int newHeight = (int)long_newHeight;
    ImageResize(image, newWidth, newHeight);
    return JS_UNDEFINED;
}

static JSValue js_ImageResizeNN(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_newWidth;
    int err_newWidth = JS_ToInt32(ctx, &long_newWidth, argv[1]);
    if(err_newWidth<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int newWidth = (int)long_newWidth;
    int32_t long_newHeight;
    int err_newHeight = JS_ToInt32(ctx, &long_newHeight, argv[2]);
    if(err_newHeight<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int newHeight = (int)long_newHeight;
    ImageResizeNN(image, newWidth, newHeight);
    return JS_UNDEFINED;
}

static JSValue js_ImageResizeCanvas(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_newWidth;
    int err_newWidth = JS_ToInt32(ctx, &long_newWidth, argv[1]);
    if(err_newWidth<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int newWidth = (int)long_newWidth;
    int32_t long_newHeight;
    int err_newHeight = JS_ToInt32(ctx, &long_newHeight, argv[2]);
    if(err_newHeight<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int newHeight = (int)long_newHeight;
    int32_t long_offsetX;
    int err_offsetX = JS_ToInt32(ctx, &long_offsetX, argv[3]);
    if(err_offsetX<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int offsetX = (int)long_offsetX;
    int32_t long_offsetY;
    int err_offsetY = JS_ToInt32(ctx, &long_offsetY, argv[4]);
    if(err_offsetY<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int offsetY = (int)long_offsetY;
    Color* ptr_fill = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_fill == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color fill = *ptr_fill;
    ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, fill);
    return JS_UNDEFINED;
}

static JSValue js_ImageMipmaps(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    ImageMipmaps(image);
    return JS_UNDEFINED;
}

static JSValue js_ImageDither(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_rBpp;
    int err_rBpp = JS_ToInt32(ctx, &long_rBpp, argv[1]);
    if(err_rBpp<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int rBpp = (int)long_rBpp;
    int32_t long_gBpp;
    int err_gBpp = JS_ToInt32(ctx, &long_gBpp, argv[2]);
    if(err_gBpp<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int gBpp = (int)long_gBpp;
    int32_t long_bBpp;
    int err_bBpp = JS_ToInt32(ctx, &long_bBpp, argv[3]);
    if(err_bBpp<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int bBpp = (int)long_bBpp;
    int32_t long_aBpp;
    int err_aBpp = JS_ToInt32(ctx, &long_aBpp, argv[4]);
    if(err_aBpp<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int aBpp = (int)long_aBpp;
    ImageDither(image, rBpp, gBpp, bBpp, aBpp);
    return JS_UNDEFINED;
}

static JSValue js_ImageFlipVertical(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    ImageFlipVertical(image);
    return JS_UNDEFINED;
}

static JSValue js_ImageFlipHorizontal(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    ImageFlipHorizontal(image);
    return JS_UNDEFINED;
}

static JSValue js_ImageRotate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_degrees;
    int err_degrees = JS_ToInt32(ctx, &long_degrees, argv[1]);
    if(err_degrees<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int degrees = (int)long_degrees;
    ImageRotate(image, degrees);
    return JS_UNDEFINED;
}

static JSValue js_ImageRotateCW(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    ImageRotateCW(image);
    return JS_UNDEFINED;
}

static JSValue js_ImageRotateCCW(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    ImageRotateCCW(image);
    return JS_UNDEFINED;
}

static JSValue js_ImageColorTint(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Color* ptr_color = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageColorTint(image, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageColorInvert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    ImageColorInvert(image);
    return JS_UNDEFINED;
}

static JSValue js_ImageColorGrayscale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    ImageColorGrayscale(image);
    return JS_UNDEFINED;
}

static JSValue js_ImageColorContrast(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    double double_contrast;
    int err_contrast = JS_ToFloat64(ctx, &double_contrast, argv[1]);
    if(err_contrast<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float contrast = (float)double_contrast;
    ImageColorContrast(image, contrast);
    return JS_UNDEFINED;
}

static JSValue js_ImageColorBrightness(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_brightness;
    int err_brightness = JS_ToInt32(ctx, &long_brightness, argv[1]);
    if(err_brightness<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int brightness = (int)long_brightness;
    ImageColorBrightness(image, brightness);
    return JS_UNDEFINED;
}

static JSValue js_ImageColorReplace(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * image = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Color* ptr_color = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    Color* ptr_replace = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_replace == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color replace = *ptr_replace;
    ImageColorReplace(image, color, replace);
    return JS_UNDEFINED;
}

static JSValue js_LoadImageColors(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    Color * colors = LoadImageColors(image);
    JSValue retVal = JS_NewArrayBufferCopy(ctx, (const uint8_t*)colors, image.width*image.height*sizeof(Color));
    UnloadImageColors(colors);
    return retVal;
}

static JSValue js_GetImageAlphaBorder(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    double double_threshold;
    int err_threshold = JS_ToFloat64(ctx, &double_threshold, argv[1]);
    if(err_threshold<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float threshold = (float)double_threshold;
    Rectangle returnVal = GetImageAlphaBorder(image, threshold);
    Rectangle* ptr_ret = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetImageColor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    int32_t long_x;
    int err_x = JS_ToInt32(ctx, &long_x, argv[1]);
    if(err_x<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int x = (int)long_x;
    int32_t long_y;
    int err_y = JS_ToInt32(ctx, &long_y, argv[2]);
    if(err_y<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int y = (int)long_y;
    Color returnVal = GetImageColor(image, x, y);
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ImageClearBackground(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Color* ptr_color = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageClearBackground(dst, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawPixel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_posX;
    int err_posX = JS_ToInt32(ctx, &long_posX, argv[1]);
    if(err_posX<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int posX = (int)long_posX;
    int32_t long_posY;
    int err_posY = JS_ToInt32(ctx, &long_posY, argv[2]);
    if(err_posY<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int posY = (int)long_posY;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawPixel(dst, posX, posY, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawPixelV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawPixelV(dst, position, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawLine(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_startPosX;
    int err_startPosX = JS_ToInt32(ctx, &long_startPosX, argv[1]);
    if(err_startPosX<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int startPosX = (int)long_startPosX;
    int32_t long_startPosY;
    int err_startPosY = JS_ToInt32(ctx, &long_startPosY, argv[2]);
    if(err_startPosY<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int startPosY = (int)long_startPosY;
    int32_t long_endPosX;
    int err_endPosX = JS_ToInt32(ctx, &long_endPosX, argv[3]);
    if(err_endPosX<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int endPosX = (int)long_endPosX;
    int32_t long_endPosY;
    int err_endPosY = JS_ToInt32(ctx, &long_endPosY, argv[4]);
    if(err_endPosY<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int endPosY = (int)long_endPosY;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawLine(dst, startPosX, startPosY, endPosX, endPosY, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawLineV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Vector2* ptr_start = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_start == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 start = *ptr_start;
    Vector2* ptr_end = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_end == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 end = *ptr_end;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawLineV(dst, start, end, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawLineEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Vector2* ptr_start = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_start == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 start = *ptr_start;
    Vector2* ptr_end = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_end == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 end = *ptr_end;
    int32_t long_thick;
    int err_thick = JS_ToInt32(ctx, &long_thick, argv[3]);
    if(err_thick<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int thick = (int)long_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawLineEx(dst, start, end, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawCircle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_centerX;
    int err_centerX = JS_ToInt32(ctx, &long_centerX, argv[1]);
    if(err_centerX<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int centerX = (int)long_centerX;
    int32_t long_centerY;
    int err_centerY = JS_ToInt32(ctx, &long_centerY, argv[2]);
    if(err_centerY<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int centerY = (int)long_centerY;
    int32_t long_radius;
    int err_radius = JS_ToInt32(ctx, &long_radius, argv[3]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int radius = (int)long_radius;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawCircle(dst, centerX, centerY, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawCircleV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    int32_t long_radius;
    int err_radius = JS_ToInt32(ctx, &long_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int radius = (int)long_radius;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawCircleV(dst, center, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawCircleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_centerX;
    int err_centerX = JS_ToInt32(ctx, &long_centerX, argv[1]);
    if(err_centerX<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int centerX = (int)long_centerX;
    int32_t long_centerY;
    int err_centerY = JS_ToInt32(ctx, &long_centerY, argv[2]);
    if(err_centerY<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int centerY = (int)long_centerY;
    int32_t long_radius;
    int err_radius = JS_ToInt32(ctx, &long_radius, argv[3]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int radius = (int)long_radius;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawCircleLines(dst, centerX, centerY, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawCircleLinesV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Vector2* ptr_center = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 center = *ptr_center;
    int32_t long_radius;
    int err_radius = JS_ToInt32(ctx, &long_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int radius = (int)long_radius;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawCircleLinesV(dst, center, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawRectangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    int32_t long_posX;
    int err_posX = JS_ToInt32(ctx, &long_posX, argv[1]);
    if(err_posX<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int posX = (int)long_posX;
    int32_t long_posY;
    int err_posY = JS_ToInt32(ctx, &long_posY, argv[2]);
    if(err_posY<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int posY = (int)long_posY;
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[3]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[4]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawRectangle(dst, posX, posY, width, height, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawRectangleV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    Vector2* ptr_size = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_size == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 size = *ptr_size;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawRectangleV(dst, position, size, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawRectangleRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[1], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawRectangleRec(dst, rec, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawRectangleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[1], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    int32_t long_thick;
    int err_thick = JS_ToInt32(ctx, &long_thick, argv[2]);
    if(err_thick<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int thick = (int)long_thick;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawRectangleLines(dst, rec, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawTriangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Vector2* ptr_v1 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v1 = *ptr_v1;
    Vector2* ptr_v2 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v2 = *ptr_v2;
    Vector2* ptr_v3 = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_v3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v3 = *ptr_v3;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawTriangle(dst, v1, v2, v3, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawTriangleEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Vector2* ptr_v1 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v1 = *ptr_v1;
    Vector2* ptr_v2 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v2 = *ptr_v2;
    Vector2* ptr_v3 = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_v3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v3 = *ptr_v3;
    Color* ptr_c1 = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_c1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color c1 = *ptr_c1;
    Color* ptr_c2 = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_c2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color c2 = *ptr_c2;
    Color* ptr_c3 = (Color*)JS_GetOpaque(argv[6], js_Color_class_id);
    if(ptr_c3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[6] does not allow null");
        return JS_EXCEPTION;
    }
    Color c3 = *ptr_c3;
    ImageDrawTriangleEx(dst, v1, v2, v3, c1, c2, c3);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawTriangleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Vector2* ptr_v1 = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v1 = *ptr_v1;
    Vector2* ptr_v2 = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v2 = *ptr_v2;
    Vector2* ptr_v3 = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_v3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v3 = *ptr_v3;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawTriangleLines(dst, v1, v2, v3, color);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawTriangleFan(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Vector2 * points;
    JSValue da_points;
    int64_t size_points;
    if(JS_IsArray(argv[1]) == 1) {
        if(JS_GetLength(ctx,argv[1],&size_points)==-1) {
            return JS_EXCEPTION;
        }
        points = (Vector2 *)js_malloc(ctx, size_points * sizeof(Vector2));
        for(int i0=0; i0 < size_points; i0++){
            JSValue js_points = JS_GetPropertyUint32(ctx,argv[1],i0);
            Vector2* ptr_pointsi0 = (Vector2*)JS_GetOpaque(js_points, js_Vector2_class_id);
            if(ptr_pointsi0 == NULL) {
                JS_ThrowTypeError(ctx, "js_points does not allow null");
                return JS_EXCEPTION;
            }
            points[i0] = *ptr_pointsi0;
            JS_FreeValue(ctx, js_points);
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_points = JS_DupValue(ctx,argv[1]);
        size_t size_points;
        points = (Vector2 *)JS_GetArrayBuffer(ctx, &size_points, da_points);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[1] does not match type Vector2 *");
        return JS_EXCEPTION;
    }
    int32_t long_pointCount;
    int err_pointCount = JS_ToInt32(ctx, &long_pointCount, argv[2]);
    if(err_pointCount<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int pointCount = (int)long_pointCount;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawTriangleFan(dst, points, pointCount, color);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, points);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_points);
    }
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawTriangleStrip(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Vector2 * points;
    JSValue da_points;
    int64_t size_points;
    if(JS_IsArray(argv[1]) == 1) {
        if(JS_GetLength(ctx,argv[1],&size_points)==-1) {
            return JS_EXCEPTION;
        }
        points = (Vector2 *)js_malloc(ctx, size_points * sizeof(Vector2));
        for(int i0=0; i0 < size_points; i0++){
            JSValue js_points = JS_GetPropertyUint32(ctx,argv[1],i0);
            Vector2* ptr_pointsi0 = (Vector2*)JS_GetOpaque(js_points, js_Vector2_class_id);
            if(ptr_pointsi0 == NULL) {
                JS_ThrowTypeError(ctx, "js_points does not allow null");
                return JS_EXCEPTION;
            }
            points[i0] = *ptr_pointsi0;
            JS_FreeValue(ctx, js_points);
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_points = JS_DupValue(ctx,argv[1]);
        size_t size_points;
        points = (Vector2 *)JS_GetArrayBuffer(ctx, &size_points, da_points);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[1] does not match type Vector2 *");
        return JS_EXCEPTION;
    }
    int32_t long_pointCount;
    int err_pointCount = JS_ToInt32(ctx, &long_pointCount, argv[2]);
    if(err_pointCount<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int pointCount = (int)long_pointCount;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, points);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_points);
        }
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawTriangleStrip(dst, points, pointCount, color);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, points);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_points);
    }
    return JS_UNDEFINED;
}

static JSValue js_ImageDraw(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Image* ptr_src = (Image*)JS_GetOpaque(argv[1], js_Image_class_id);
    if(ptr_src == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Image src = *ptr_src;
    Rectangle* ptr_srcRec = (Rectangle*)JS_GetOpaque(argv[2], js_Rectangle_class_id);
    if(ptr_srcRec == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle srcRec = *ptr_srcRec;
    Rectangle* ptr_dstRec = (Rectangle*)JS_GetOpaque(argv[3], js_Rectangle_class_id);
    if(ptr_dstRec == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle dstRec = *ptr_dstRec;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    ImageDraw(dst, src, srcRec, dstRec, tint);
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_posX;
    int err_posX = JS_ToInt32(ctx, &long_posX, argv[2]);
    if(err_posX<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int posX = (int)long_posX;
    int32_t long_posY;
    int err_posY = JS_ToInt32(ctx, &long_posY, argv[3]);
    if(err_posY<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int posY = (int)long_posY;
    int32_t long_fontSize;
    int err_fontSize = JS_ToInt32(ctx, &long_fontSize, argv[4]);
    if(err_fontSize<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int fontSize = (int)long_fontSize;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    ImageDrawText(dst, (const char *)text, posX, posY, fontSize, color);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_ImageDrawTextEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image * dst = (Image *)JS_GetOpaque(argv[0], js_Image_class_id);
    if(dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Image");
        return JS_EXCEPTION;
    }
    Font* ptr_font = (Font*)JS_GetOpaque(argv[1], js_Font_class_id);
    if(ptr_font == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Font font = *ptr_font;
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[2]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        da_text = JS_DupValue(ctx,argv[2]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[2]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[2] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_position == NULL) {
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[2]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[2]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    double double_fontSize;
    int err_fontSize = JS_ToFloat64(ctx, &double_fontSize, argv[4]);
    if(err_fontSize<0) {
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[2]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[2]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float fontSize = (float)double_fontSize;
    double double_spacing;
    int err_spacing = JS_ToFloat64(ctx, &double_spacing, argv[5]);
    if(err_spacing<0) {
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[2]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[2]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[5] is not numeric");
        return JS_EXCEPTION;
    }
    float spacing = (float)double_spacing;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[6], js_Color_class_id);
    if(ptr_tint == NULL) {
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[2]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[2]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[6] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    ImageDrawTextEx(dst, font, (const char *)text, position, fontSize, spacing, tint);
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[2]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_LoadTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Texture2D returnVal = LoadTexture((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    Texture2D* ptr_ret = (Texture2D*)js_malloc(ctx, sizeof(Texture2D));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadTextureFromImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    Texture2D returnVal = LoadTextureFromImage(image);
    Texture2D* ptr_ret = (Texture2D*)js_malloc(ctx, sizeof(Texture2D));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadTextureCubemap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    int32_t long_layout;
    int err_layout = JS_ToInt32(ctx, &long_layout, argv[1]);
    if(err_layout<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int layout = (int)long_layout;
    TextureCubemap returnVal = LoadTextureCubemap(image, layout);
    TextureCubemap* ptr_ret = (TextureCubemap*)js_malloc(ctx, sizeof(TextureCubemap));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadRenderTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    RenderTexture2D returnVal = LoadRenderTexture(width, height);
    RenderTexture2D* ptr_ret = (RenderTexture2D*)js_malloc(ctx, sizeof(RenderTexture2D));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RenderTexture_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_IsTextureValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    bool returnVal = IsTextureValid(texture);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_UnloadTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    UnloadTexture(texture);
    return JS_UNDEFINED;
}

static JSValue js_IsRenderTextureValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    RenderTexture2D* ptr_target = (RenderTexture2D*)JS_GetOpaque(argv[0], js_RenderTexture_class_id);
    if(ptr_target == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    RenderTexture2D target = *ptr_target;
    bool returnVal = IsRenderTextureValid(target);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_UnloadRenderTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    RenderTexture2D* ptr_target = (RenderTexture2D*)JS_GetOpaque(argv[0], js_RenderTexture_class_id);
    if(ptr_target == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    RenderTexture2D target = *ptr_target;
    UnloadRenderTexture(target);
    return JS_UNDEFINED;
}

static JSValue js_UpdateTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    void * pixels;
    JSValue da_pixels;
    int64_t size_pixels;
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_pixels = JS_DupValue(ctx,argv[1]);
        size_t size_pixels;
        pixels = (void *)JS_GetArrayBuffer(ctx, &size_pixels, da_pixels);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[1] does not match type void *");
        return JS_EXCEPTION;
    }
    UpdateTexture(texture, (const void *)pixels);
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_pixels);
    }
    return JS_UNDEFINED;
}

static JSValue js_UpdateTextureRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    Rectangle* ptr_rec = (Rectangle*)JS_GetOpaque(argv[1], js_Rectangle_class_id);
    if(ptr_rec == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle rec = *ptr_rec;
    void * pixels;
    JSValue da_pixels;
    int64_t size_pixels;
    if(JS_IsArrayBuffer(argv[2]) == 1) {
        da_pixels = JS_DupValue(ctx,argv[2]);
        size_t size_pixels;
        pixels = (void *)JS_GetArrayBuffer(ctx, &size_pixels, da_pixels);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[2] does not match type void *");
        return JS_EXCEPTION;
    }
    UpdateTextureRec(texture, rec, (const void *)pixels);
    if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_pixels);
    }
    return JS_UNDEFINED;
}

static JSValue js_GenTextureMipmaps(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D * texture = (Texture2D *)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Texture2D");
        return JS_EXCEPTION;
    }
    GenTextureMipmaps(texture);
    return JS_UNDEFINED;
}

static JSValue js_SetTextureFilter(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    int32_t long_filter;
    int err_filter = JS_ToInt32(ctx, &long_filter, argv[1]);
    if(err_filter<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int filter = (int)long_filter;
    SetTextureFilter(texture, filter);
    return JS_UNDEFINED;
}

static JSValue js_SetTextureWrap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    int32_t long_wrap;
    int err_wrap = JS_ToInt32(ctx, &long_wrap, argv[1]);
    if(err_wrap<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int wrap = (int)long_wrap;
    SetTextureWrap(texture, wrap);
    return JS_UNDEFINED;
}

static JSValue js_DrawTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    int32_t long_posX;
    int err_posX = JS_ToInt32(ctx, &long_posX, argv[1]);
    if(err_posX<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int posX = (int)long_posX;
    int32_t long_posY;
    int err_posY = JS_ToInt32(ctx, &long_posY, argv[2]);
    if(err_posY<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int posY = (int)long_posY;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawTexture(texture, posX, posY, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawTextureV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawTextureV(texture, position, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawTextureEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    double double_rotation;
    int err_rotation = JS_ToFloat64(ctx, &double_rotation, argv[2]);
    if(err_rotation<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float rotation = (float)double_rotation;
    double double_scale;
    int err_scale = JS_ToFloat64(ctx, &double_scale, argv[3]);
    if(err_scale<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float scale = (float)double_scale;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawTextureEx(texture, position, rotation, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawTextureRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    Rectangle* ptr_source = (Rectangle*)JS_GetOpaque(argv[1], js_Rectangle_class_id);
    if(ptr_source == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle source = *ptr_source;
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawTextureRec(texture, source, position, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawTexturePro(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    Rectangle* ptr_source = (Rectangle*)JS_GetOpaque(argv[1], js_Rectangle_class_id);
    if(ptr_source == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle source = *ptr_source;
    Rectangle* ptr_dest = (Rectangle*)JS_GetOpaque(argv[2], js_Rectangle_class_id);
    if(ptr_dest == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle dest = *ptr_dest;
    Vector2* ptr_origin = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_origin == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 origin = *ptr_origin;
    double double_rotation;
    int err_rotation = JS_ToFloat64(ctx, &double_rotation, argv[4]);
    if(err_rotation<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float rotation = (float)double_rotation;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawTexturePro(texture, source, dest, origin, rotation, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawTextureNPatch(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[0], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    NPatchInfo* ptr_nPatchInfo = (NPatchInfo*)JS_GetOpaque(argv[1], js_NPatchInfo_class_id);
    if(ptr_nPatchInfo == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    NPatchInfo nPatchInfo = *ptr_nPatchInfo;
    Rectangle* ptr_dest = (Rectangle*)JS_GetOpaque(argv[2], js_Rectangle_class_id);
    if(ptr_dest == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle dest = *ptr_dest;
    Vector2* ptr_origin = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_origin == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 origin = *ptr_origin;
    double double_rotation;
    int err_rotation = JS_ToFloat64(ctx, &double_rotation, argv[4]);
    if(err_rotation<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float rotation = (float)double_rotation;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawTextureNPatch(texture, nPatchInfo, dest, origin, rotation, tint);
    return JS_UNDEFINED;
}

static JSValue js_ColorIsEqual(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_col1 = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_col1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color col1 = *ptr_col1;
    Color* ptr_col2 = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_col2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color col2 = *ptr_col2;
    bool returnVal = ColorIsEqual(col1, col2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_Fade(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_color = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    double double_alpha;
    int err_alpha = JS_ToFloat64(ctx, &double_alpha, argv[1]);
    if(err_alpha<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float alpha = (float)double_alpha;
    Color returnVal = Fade(color, alpha);
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ColorToInt(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_color = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    int returnVal = ColorToInt(color);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_ColorNormalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_color = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    Vector4 returnVal = ColorNormalize(color);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ColorFromNormalized(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_normalized = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_normalized == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 normalized = *ptr_normalized;
    Color returnVal = ColorFromNormalized(normalized);
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ColorToHSV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_color = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    Vector3 returnVal = ColorToHSV(color);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ColorFromHSV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_hue;
    int err_hue = JS_ToFloat64(ctx, &double_hue, argv[0]);
    if(err_hue<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float hue = (float)double_hue;
    double double_saturation;
    int err_saturation = JS_ToFloat64(ctx, &double_saturation, argv[1]);
    if(err_saturation<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float saturation = (float)double_saturation;
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, argv[2]);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    Color returnVal = ColorFromHSV(hue, saturation, value);
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ColorTint(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_color = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    Color returnVal = ColorTint(color, tint);
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ColorBrightness(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_color = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    double double_factor;
    int err_factor = JS_ToFloat64(ctx, &double_factor, argv[1]);
    if(err_factor<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float factor = (float)double_factor;
    Color returnVal = ColorBrightness(color, factor);
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ColorContrast(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_color = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    double double_contrast;
    int err_contrast = JS_ToFloat64(ctx, &double_contrast, argv[1]);
    if(err_contrast<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float contrast = (float)double_contrast;
    Color returnVal = ColorContrast(color, contrast);
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ColorAlpha(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_color = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    double double_alpha;
    int err_alpha = JS_ToFloat64(ctx, &double_alpha, argv[1]);
    if(err_alpha<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float alpha = (float)double_alpha;
    Color returnVal = ColorAlpha(color, alpha);
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ColorAlphaBlend(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_dst = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_dst == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color dst = *ptr_dst;
    Color* ptr_src = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_src == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color src = *ptr_src;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    Color returnVal = ColorAlphaBlend(dst, src, tint);
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_ColorLerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_color1 = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_color1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color color1 = *ptr_color1;
    Color* ptr_color2 = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_color2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color color2 = *ptr_color2;
    double double_factor;
    int err_factor = JS_ToFloat64(ctx, &double_factor, argv[2]);
    if(err_factor<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float factor = (float)double_factor;
    Color returnVal = ColorLerp(color1, color2, factor);
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetColor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    uint32_t long_hexValue;
    int err_hexValue = JS_ToUint32(ctx, &long_hexValue, argv[0]);
    if(err_hexValue<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int hexValue = (unsigned int)long_hexValue;
    Color returnVal = GetColor(hexValue);
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetPixelDataSize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_width;
    int err_width = JS_ToInt32(ctx, &long_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int width = (int)long_width;
    int32_t long_height;
    int err_height = JS_ToInt32(ctx, &long_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int height = (int)long_height;
    int32_t long_format;
    int err_format = JS_ToInt32(ctx, &long_format, argv[2]);
    if(err_format<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int format = (int)long_format;
    int returnVal = GetPixelDataSize(width, height, format);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetFontDefault(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font returnVal = GetFontDefault();
    Font* ptr_ret = (Font*)js_malloc(ctx, sizeof(Font));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadFont(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Font returnVal = LoadFont((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    Font* ptr_ret = (Font*)js_malloc(ctx, sizeof(Font));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadFontEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            JSValue da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileName);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_fontSize;
    int err_fontSize = JS_ToInt32(ctx, &long_fontSize, argv[1]);
    if(err_fontSize<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int fontSize = (int)long_fontSize;
    int * codepoints;
    int64_t size_codepoints;
    if(JS_IsNull(argv[2]) || JS_IsUndefined(argv[2])) {
        codepoints = NULL;
    }
    else if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_codepoints)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        codepoints = (int *)js_malloc(ctx, size_codepoints * sizeof(int));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, codepoints);
        for(int i0=0; i0 < size_codepoints; i0++){
            JSValue js_codepoints = JS_GetPropertyUint32(ctx,argv[2],i0);
            int32_t long_codepointsi0;
            int err_codepointsi0 = JS_ToInt32(ctx, &long_codepointsi0, js_codepoints);
            if(err_codepointsi0<0) {
                JS_ThrowTypeError(ctx, "js_codepoints is not numeric");
                return JS_EXCEPTION;
            }
            codepoints[i0] = (int)long_codepointsi0;
            JS_FreeValue(ctx, js_codepoints);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JSValue da_codepoints = JS_DupValue(ctx,argv[2]);
        size_t size_codepoints;
        codepoints = (int *)JS_GetArrayBuffer(ctx, &size_codepoints, da_codepoints);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_codepoints);
    }
    else {
        JSClassID classid_codepoints = JS_GetClassID(argv[2]);
        if(classid_codepoints==JS_CLASS_INT16_ARRAY) {
            size_t offset_codepoints;
            size_t size_codepoints;
            JSValue da_codepoints = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_codepoints,&size_codepoints,NULL);
            codepoints = (int *)JS_GetArrayBuffer(ctx, &size_codepoints, da_codepoints);
            codepoints+=offset_codepoints;
            size_codepoints-=offset_codepoints;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_codepoints);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[2] does not match type int *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_codepointCount;
    int err_codepointCount = JS_ToInt32(ctx, &long_codepointCount, argv[3]);
    if(err_codepointCount<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int codepointCount = (int)long_codepointCount;
    Font returnVal = LoadFontEx((const char *)fileName, fontSize, codepoints, codepointCount);
    memoryClear(ctx, memoryHead);
    Font* ptr_ret = (Font*)js_malloc(ctx, sizeof(Font));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadFontFromImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_image = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_image == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image image = *ptr_image;
    Color* ptr_key = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_key == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color key = *ptr_key;
    int32_t long_firstChar;
    int err_firstChar = JS_ToInt32(ctx, &long_firstChar, argv[2]);
    if(err_firstChar<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int firstChar = (int)long_firstChar;
    Font returnVal = LoadFontFromImage(image, key, firstChar);
    Font* ptr_ret = (Font*)js_malloc(ctx, sizeof(Font));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_IsFontValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* ptr_font = (Font*)JS_GetOpaque(argv[0], js_Font_class_id);
    if(ptr_font == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Font font = *ptr_font;
    bool returnVal = IsFontValid(font);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_UnloadFont(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* ptr_font = (Font*)JS_GetOpaque(argv[0], js_Font_class_id);
    if(ptr_font == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Font font = *ptr_font;
    UnloadFont(font);
    return JS_UNDEFINED;
}

static JSValue js_DrawFPS(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_posX;
    int err_posX = JS_ToInt32(ctx, &long_posX, argv[0]);
    if(err_posX<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int posX = (int)long_posX;
    int32_t long_posY;
    int err_posY = JS_ToInt32(ctx, &long_posY, argv[1]);
    if(err_posY<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int posY = (int)long_posY;
    DrawFPS(posX, posY);
    return JS_UNDEFINED;
}

static JSValue js_DrawText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_posX;
    int err_posX = JS_ToInt32(ctx, &long_posX, argv[1]);
    if(err_posX<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[0]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int posX = (int)long_posX;
    int32_t long_posY;
    int err_posY = JS_ToInt32(ctx, &long_posY, argv[2]);
    if(err_posY<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[0]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int posY = (int)long_posY;
    int32_t long_fontSize;
    int err_fontSize = JS_ToInt32(ctx, &long_fontSize, argv[3]);
    if(err_fontSize<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[0]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int fontSize = (int)long_fontSize;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[0]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawText((const char *)text, posX, posY, fontSize, color);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_DrawTextEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* ptr_font = (Font*)JS_GetOpaque(argv[0], js_Font_class_id);
    if(ptr_font == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Font font = *ptr_font;
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_position == NULL) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    double double_fontSize;
    int err_fontSize = JS_ToFloat64(ctx, &double_fontSize, argv[3]);
    if(err_fontSize<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float fontSize = (float)double_fontSize;
    double double_spacing;
    int err_spacing = JS_ToFloat64(ctx, &double_spacing, argv[4]);
    if(err_spacing<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float spacing = (float)double_spacing;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_tint == NULL) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawTextEx(font, (const char *)text, position, fontSize, spacing, tint);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_DrawTextPro(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* ptr_font = (Font*)JS_GetOpaque(argv[0], js_Font_class_id);
    if(ptr_font == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Font font = *ptr_font;
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_position == NULL) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    Vector2* ptr_origin = (Vector2*)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(ptr_origin == NULL) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 origin = *ptr_origin;
    double double_rotation;
    int err_rotation = JS_ToFloat64(ctx, &double_rotation, argv[4]);
    if(err_rotation<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float rotation = (float)double_rotation;
    double double_fontSize;
    int err_fontSize = JS_ToFloat64(ctx, &double_fontSize, argv[5]);
    if(err_fontSize<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[5] is not numeric");
        return JS_EXCEPTION;
    }
    float fontSize = (float)double_fontSize;
    double double_spacing;
    int err_spacing = JS_ToFloat64(ctx, &double_spacing, argv[6]);
    if(err_spacing<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[6] is not numeric");
        return JS_EXCEPTION;
    }
    float spacing = (float)double_spacing;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[7], js_Color_class_id);
    if(ptr_tint == NULL) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[7] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawTextPro(font, (const char *)text, position, origin, rotation, fontSize, spacing, tint);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_DrawTextCodepoint(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* ptr_font = (Font*)JS_GetOpaque(argv[0], js_Font_class_id);
    if(ptr_font == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Font font = *ptr_font;
    int32_t long_codepoint;
    int err_codepoint = JS_ToInt32(ctx, &long_codepoint, argv[1]);
    if(err_codepoint<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int codepoint = (int)long_codepoint;
    Vector2* ptr_position = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 position = *ptr_position;
    double double_fontSize;
    int err_fontSize = JS_ToFloat64(ctx, &double_fontSize, argv[3]);
    if(err_fontSize<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float fontSize = (float)double_fontSize;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawTextCodepoint(font, codepoint, position, fontSize, tint);
    return JS_UNDEFINED;
}

static JSValue js_SetTextLineSpacing(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_spacing;
    int err_spacing = JS_ToInt32(ctx, &long_spacing, argv[0]);
    if(err_spacing<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int spacing = (int)long_spacing;
    SetTextLineSpacing(spacing);
    return JS_UNDEFINED;
}

static JSValue js_MeasureText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_fontSize;
    int err_fontSize = JS_ToInt32(ctx, &long_fontSize, argv[1]);
    if(err_fontSize<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[0]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int fontSize = (int)long_fontSize;
    int returnVal = MeasureText((const char *)text, fontSize);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_MeasureTextEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* ptr_font = (Font*)JS_GetOpaque(argv[0], js_Font_class_id);
    if(ptr_font == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Font font = *ptr_font;
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    double double_fontSize;
    int err_fontSize = JS_ToFloat64(ctx, &double_fontSize, argv[2]);
    if(err_fontSize<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float fontSize = (float)double_fontSize;
    double double_spacing;
    int err_spacing = JS_ToFloat64(ctx, &double_spacing, argv[3]);
    if(err_spacing<0) {
        if(JS_IsArray(argv[1]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[1]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[1]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float spacing = (float)double_spacing;
    Vector2 returnVal = MeasureTextEx(font, (const char *)text, fontSize, spacing);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetGlyphIndex(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* ptr_font = (Font*)JS_GetOpaque(argv[0], js_Font_class_id);
    if(ptr_font == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Font font = *ptr_font;
    int32_t long_codepoint;
    int err_codepoint = JS_ToInt32(ctx, &long_codepoint, argv[1]);
    if(err_codepoint<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int codepoint = (int)long_codepoint;
    int returnVal = GetGlyphIndex(font, codepoint);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GetGlyphAtlasRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* ptr_font = (Font*)JS_GetOpaque(argv[0], js_Font_class_id);
    if(ptr_font == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Font font = *ptr_font;
    int32_t long_codepoint;
    int err_codepoint = JS_ToInt32(ctx, &long_codepoint, argv[1]);
    if(err_codepoint<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int codepoint = (int)long_codepoint;
    Rectangle returnVal = GetGlyphAtlasRec(font, codepoint);
    Rectangle* ptr_ret = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_TextCopy(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * dst;
    int64_t size_dst;
    if(JS_IsString(argv[0]) == 1) {
        dst = (char *)JS_ToCStringLen(ctx, &size_dst, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, dst);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_dst = JS_DupValue(ctx,argv[0]);
        size_t size_dst;
        dst = (char *)JS_GetArrayBuffer(ctx, &size_dst, da_dst);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_dst);
    }
    else {
        JSClassID classid_dst = JS_GetClassID(argv[0]);
        if(classid_dst==JS_CLASS_INT8_ARRAY) {
            size_t offset_dst;
            size_t size_dst;
            JSValue da_dst = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dst,&size_dst,NULL);
            dst = (char *)JS_GetArrayBuffer(ctx, &size_dst, da_dst);
            dst+=offset_dst;
            size_dst-=offset_dst;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_dst);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * src;
    int64_t size_src;
    if(JS_IsString(argv[1]) == 1) {
        src = (char *)JS_ToCStringLen(ctx, &size_src, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, src);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_src = JS_DupValue(ctx,argv[1]);
        size_t size_src;
        src = (char *)JS_GetArrayBuffer(ctx, &size_src, da_src);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_src);
    }
    else {
        JSClassID classid_src = JS_GetClassID(argv[1]);
        if(classid_src==JS_CLASS_INT8_ARRAY) {
            size_t offset_src;
            size_t size_src;
            JSValue da_src = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_src,&size_src,NULL);
            src = (char *)JS_GetArrayBuffer(ctx, &size_src, da_src);
            src+=offset_src;
            size_src-=offset_src;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_src);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int returnVal = TextCopy(dst, (const char *)src);
    if(JS_IsArray(argv[0]) == 1) {
        argv[0] = JS_NewString(ctx, dst);
    }
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_TextIsEqual(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * text1;
    int64_t size_text1;
    if(JS_IsString(argv[0]) == 1) {
        text1 = (char *)JS_ToCStringLen(ctx, &size_text1, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text1);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_text1 = JS_DupValue(ctx,argv[0]);
        size_t size_text1;
        text1 = (char *)JS_GetArrayBuffer(ctx, &size_text1, da_text1);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text1);
    }
    else {
        JSClassID classid_text1 = JS_GetClassID(argv[0]);
        if(classid_text1==JS_CLASS_INT8_ARRAY) {
            size_t offset_text1;
            size_t size_text1;
            JSValue da_text1 = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text1,&size_text1,NULL);
            text1 = (char *)JS_GetArrayBuffer(ctx, &size_text1, da_text1);
            text1+=offset_text1;
            size_text1-=offset_text1;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text1);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * text2;
    int64_t size_text2;
    if(JS_IsString(argv[1]) == 1) {
        text2 = (char *)JS_ToCStringLen(ctx, &size_text2, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text2);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_text2 = JS_DupValue(ctx,argv[1]);
        size_t size_text2;
        text2 = (char *)JS_GetArrayBuffer(ctx, &size_text2, da_text2);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text2);
    }
    else {
        JSClassID classid_text2 = JS_GetClassID(argv[1]);
        if(classid_text2==JS_CLASS_INT8_ARRAY) {
            size_t offset_text2;
            size_t size_text2;
            JSValue da_text2 = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text2,&size_text2,NULL);
            text2 = (char *)JS_GetArrayBuffer(ctx, &size_text2, da_text2);
            text2+=offset_text2;
            size_text2-=offset_text2;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text2);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = TextIsEqual((const char *)text1, (const char *)text2);
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_TextLength(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    unsigned int returnVal = TextLength((const char *)text);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    JSValue ret = JS_NewUint32(ctx, (unsigned long)returnVal);
    return ret;
}

static JSValue js_TextFormat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    size_t char_ptrlen = 10;
    char * char_ptr = (char *)js_calloc(ctx, char_ptrlen, sizeof(char));
    int64_t formatlen;
    if(JS_GetLength(ctx,argv[0],&formatlen)==-1) {
        memoryClear(ctx, memoryHead);
        js_free(ctx, char_ptr);
        return JS_EXCEPTION;
    }
    char * format;
    int64_t size_format;
    if(JS_IsString(argv[0]) == 1) {
        format = (char *)JS_ToCStringLen(ctx, &size_format, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, format);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_format = JS_DupValue(ctx,argv[0]);
        size_t size_format;
        format = (char *)JS_GetArrayBuffer(ctx, &size_format, da_format);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_format);
    }
    else {
        JSClassID classid_format = JS_GetClassID(argv[0]);
        if(classid_format==JS_CLASS_INT8_ARRAY) {
            size_t offset_format;
            size_t size_format;
            JSValue da_format = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_format,&size_format,NULL);
            format = (char *)JS_GetArrayBuffer(ctx, &size_format, da_format);
            format+=offset_format;
            size_format-=offset_format;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_format);
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * subformat = format;
    size_t subformatlen = 0;
    char subformatlenh;
    size_t bufferlen = formatlen*2;
    char * buffer = (char *)js_calloc(ctx, bufferlen, sizeof(char));
    int l = 0;
    int c = 1;
    int ilen = 0;
    for(int i=0; i < formatlen; i++){
        if(format[i]!='%') {
            buffer[l]=format[i];
            l++;
        }
        else {
            int firsth = i+1;
            char har = format[firsth];
            if(har==0) {
                JSValue ret;
                ret = JS_NewString(ctx, buffer);
                memoryClear(ctx, memoryHead);
                js_free(ctx, char_ptr);
                js_free(ctx, buffer);
                return ret;
            }
            while(!(har>=97&&har<=122)&&!(har>=65&&har<=90)&&har!='%'){
                firsth++;
                har=format[firsth];
                if(har==0) {
                    JSValue ret;
                    ret = JS_NewString(ctx, buffer);
                    memoryClear(ctx, memoryHead);
                    js_free(ctx, char_ptr);
                    js_free(ctx, buffer);
                    return ret;
                }
            }
            int lasth = firsth;
            har=format[lasth];
            while(strchr("diuoxXfFeEfFeEgGaAcspn%", har)==NULL){
                lasth++;
                har = format[lasth];
                if(har==0) {
                    JSValue ret;
                    ret = JS_NewString(ctx, buffer);
                    memoryClear(ctx, memoryHead);
                    js_free(ctx, char_ptr);
                    js_free(ctx, buffer);
                    return ret;
                }
            }
            subformatlen = lasth-i+1;
            subformatlenh = format[lasth+1];
            subformat = format+i;
            subformat[subformatlen]=0;
            if(format[lasth]=='%') {
                i = lasth;
                buffer[l]='%';
                l++;
                continue;
            }
            memset(char_ptr,0,ilen * sizeof(char));
            switch(har) {
                case 'd':
                case 'i':{
                    int64_t a;
                    int err_a = JS_ToInt64(ctx, &a, argv[c]);
                    if(err_a<0) {
                        memoryClear(ctx, memoryHead);
                        js_free(ctx, char_ptr);
                        js_free(ctx, buffer);
                        JS_ThrowTypeError(ctx, "argv[c] is not numeric");
                        return JS_EXCEPTION;
                    }
                    if(firsth==lasth) {
                        char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (int)a);
                    }
                    else {
                        switch(format[lasth-1]) {
                            case 'h':{
                                if(subformat[lasth-i-2]=='h') {
                                    char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (signed char)a);
                                }
                                else {
                                    char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (short int)a);
                                }
                                break;
                            }
                            case 'l':{
                                if(subformat[lasth-i-2]=='l') {
                                    char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (long long int)a);
                                }
                                else {
                                    char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (long int)a);
                                }
                                break;
                            }
                            case 'j':{
                                char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (intmax_t)a);
                                break;
                            }
                            case 'z':{
                                char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (size_t)a);
                                break;
                            }
                            case 't':{
                                char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (ptrdiff_t)a);
                                break;
                            }
                        }
                    }
                    break;
                }
                case 'u':
                case 'o':
                case 'x':
                case 'X':{
                    uint32_t a;
                    int err_a = JS_ToUint32(ctx, &a, argv[c]);
                    if(err_a<0) {
                        memoryClear(ctx, memoryHead);
                        js_free(ctx, char_ptr);
                        js_free(ctx, buffer);
                        JS_ThrowTypeError(ctx, "argv[c] is not numeric");
                        return JS_EXCEPTION;
                    }
                    if(firsth==lasth) {
                        char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (unsigned int)a);
                    }
                    else {
                        switch(subformat[lasth-i-1]) {
                            case 'h':{
                                if(subformat[lasth-i-2]=='h') {
                                    char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (unsigned char)a);
                                }
                                else {
                                    char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (unsigned short int)a);
                                }
                                break;
                            }
                            case 'l':{
                                if(subformat[lasth-i-2]=='l') {
                                    char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (unsigned long long int)a);
                                }
                                else {
                                    char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (unsigned long int)a);
                                }
                                break;
                            }
                            case 'j':{
                                char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (uintmax_t)a);
                                break;
                            }
                            case 'z':{
                                char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (size_t)a);
                                break;
                            }
                            case 't':{
                                char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (ptrdiff_t)a);
                                break;
                            }
                        }
                    }
                    break;
                }
                case 'f':
                case 'F':
                case 'e':
                case 'E':
                case 'g':
                case 'G':
                case 'a':
                case 'A':{
                    double a;
                    int err_a = JS_ToFloat64(ctx, &a, argv[c]);
                    if(err_a<0) {
                        memoryClear(ctx, memoryHead);
                        js_free(ctx, char_ptr);
                        js_free(ctx, buffer);
                        JS_ThrowTypeError(ctx, "argv[c] is not numeric");
                        return JS_EXCEPTION;
                    }
                    if(firsth==lasth) {
                        char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (double)a);
                    }
                    else {
                        char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (long double)a);
                    }
                    break;
                }
                case 'c':{
                    int32_t long_a;
                    int err_a = JS_ToInt32(ctx, &long_a, argv[c]);
                    if(err_a<0) {
                        memoryClear(ctx, memoryHead);
                        js_free(ctx, char_ptr);
                        js_free(ctx, buffer);
                        JS_ThrowTypeError(ctx, "argv[c] is not numeric");
                        return JS_EXCEPTION;
                    }
                    int a = (int)long_a;
                    if(firsth==lasth) {
                        char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (int)a);
                    }
                    else {
                        char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (wint_t)a);
                    }
                    break;
                }
                case 's':{
                    if(firsth==lasth) {
                        char * a;
                        int64_t size_a;
                        if(JS_IsString(argv[c]) == 1) {
                            a = (char *)JS_ToCStringLen(ctx, &size_a, argv[c]);
                            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, a);
                        }
                        else if(JS_IsArrayBuffer(argv[c]) == 1) {
                            JSValue da_a = JS_DupValue(ctx,argv[c]);
                            size_t size_a;
                            a = (char *)JS_GetArrayBuffer(ctx, &size_a, da_a);
                            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_a);
                        }
                        else {
                            JSClassID classid_a = JS_GetClassID(argv[c]);
                            if(classid_a==JS_CLASS_INT8_ARRAY) {
                                size_t offset_a;
                                size_t size_a;
                                JSValue da_a = JS_GetTypedArrayBuffer(ctx,argv[c],&offset_a,&size_a,NULL);
                                a = (char *)JS_GetArrayBuffer(ctx, &size_a, da_a);
                                a+=offset_a;
                                size_a-=offset_a;
                                memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_a);
                            }
                            else {
                                memoryClear(ctx, memoryHead);
                                js_free(ctx, char_ptr);
                                js_free(ctx, buffer);
                                JS_ThrowTypeError(ctx, "argv[c] does not match type char *");
                                return JS_EXCEPTION;
                            }
                        }
                        char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, a);
                    }
                    else {
                        wchar_t * a;
                        int64_t size_a;
                        if(JS_IsArray(argv[c]) == 1) {
                            if(JS_GetLength(ctx,argv[c],&size_a)==-1) {
                                memoryClear(ctx, memoryHead);
                                js_free(ctx, char_ptr);
                                js_free(ctx, buffer);
                                return JS_EXCEPTION;
                            }
                            a = (wchar_t *)js_malloc(ctx, size_a * sizeof(wchar_t));
                            memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, a);
                            for(int i0=0; i0 < size_a; i0++){
                                JSValue js_a = JS_GetPropertyUint32(ctx,argv[c],i0);
                                uint32_t long_ai0;
                                int err_ai0 = JS_ToUint32(ctx, &long_ai0, js_a);
                                if(err_ai0<0) {
                                    JS_ThrowTypeError(ctx, "js_a is not numeric");
                                    return JS_EXCEPTION;
                                }
                                a[i0] = (wchar_t)long_ai0;
                                JS_FreeValue(ctx, js_a);
                            }
                        }
                        else if(JS_IsArrayBuffer(argv[c]) == 1) {
                            JSValue da_a = JS_DupValue(ctx,argv[c]);
                            size_t size_a;
                            a = (wchar_t *)JS_GetArrayBuffer(ctx, &size_a, da_a);
                            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_a);
                        }
                        else {
                            JSClassID classid_a = JS_GetClassID(argv[c]);
                            if(classid_a==JS_CLASS_UINT32_ARRAY) {
                                size_t offset_a;
                                size_t size_a;
                                JSValue da_a = JS_GetTypedArrayBuffer(ctx,argv[c],&offset_a,&size_a,NULL);
                                a = (wchar_t *)JS_GetArrayBuffer(ctx, &size_a, da_a);
                                a+=offset_a;
                                size_a-=offset_a;
                                memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_a);
                            }
                            else {
                                memoryClear(ctx, memoryHead);
                                js_free(ctx, char_ptr);
                                js_free(ctx, buffer);
                                JS_ThrowTypeError(ctx, "argv[c] does not match type wchar_t *");
                                return JS_EXCEPTION;
                            }
                        }
                        char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, a);
                    }
                    break;
                }
                case 'p':{
                    char_ptr = asnprintf(ctx, char_ptr, &char_ptrlen, subformat, (void *)&argv[c]);
                    break;
                }
                case 'n':{
                    if(JS_IsArray(argv[c]) == 1) {
                        JSValue js_argvc = JS_NewInt32(ctx, (long)(&l)[0]);
                        JS_DefinePropertyValueUint32(ctx,argv[c],0,js_argvc,JS_PROP_C_W_E);
                    }
                    break;
                }
            }
            subformat[subformatlen]=subformatlenh;
            c++;
            ilen = strlen(char_ptr);
            int maxstrlen = formatlen+l+ilen-lasth;
            if(bufferlen<maxstrlen) {
                buffer = js_realloc(ctx,buffer,maxstrlen);
                memset(buffer+bufferlen, 0, maxstrlen-bufferlen);
                bufferlen = maxstrlen;
            }
            strncpy(buffer+l, char_ptr, ilen);
            l+=ilen;
            i = lasth;
        }
    }
    JSValue js_buffer;
    js_buffer = JS_NewString(ctx, buffer);
    memoryClear(ctx, memoryHead);
    js_free(ctx, char_ptr);
    js_free(ctx, buffer);
    return js_buffer;
}

static JSValue js_TextSubtext(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_position;
    int err_position = JS_ToInt32(ctx, &long_position, argv[1]);
    if(err_position<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[0]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int position = (int)long_position;
    int32_t long_length;
    int err_length = JS_ToInt32(ctx, &long_length, argv[2]);
    if(err_length<0) {
        if(JS_IsArray(argv[0]) == 1) {
            js_free(ctx, text);
        }
        else if(JS_IsString(argv[0]) == 1) {
            JS_FreeCString(ctx, text);
        }
        else if(JS_IsArrayBuffer(argv[0]) == 1) {
            JS_FreeValue(ctx, da_text);
        }
        else {
            JSClassID classid_text = JS_GetClassID(argv[0]);
            if(classid_text==JS_CLASS_INT8_ARRAY) {
                js_free(ctx, &da_text);
            }
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int length = (int)long_length;
    const char * returnVal = TextSubtext((const char *)text, position, length);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextReplace(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            JSValue da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * replace;
    int64_t size_replace;
    if(JS_IsString(argv[1]) == 1) {
        replace = (char *)JS_ToCStringLen(ctx, &size_replace, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, replace);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_replace = JS_DupValue(ctx,argv[1]);
        size_t size_replace;
        replace = (char *)JS_GetArrayBuffer(ctx, &size_replace, da_replace);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_replace);
    }
    else {
        JSClassID classid_replace = JS_GetClassID(argv[1]);
        if(classid_replace==JS_CLASS_INT8_ARRAY) {
            size_t offset_replace;
            size_t size_replace;
            JSValue da_replace = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_replace,&size_replace,NULL);
            replace = (char *)JS_GetArrayBuffer(ctx, &size_replace, da_replace);
            replace+=offset_replace;
            size_replace-=offset_replace;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_replace);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * by;
    int64_t size_by;
    if(JS_IsString(argv[2]) == 1) {
        by = (char *)JS_ToCStringLen(ctx, &size_by, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, by);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JSValue da_by = JS_DupValue(ctx,argv[2]);
        size_t size_by;
        by = (char *)JS_GetArrayBuffer(ctx, &size_by, da_by);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_by);
    }
    else {
        JSClassID classid_by = JS_GetClassID(argv[2]);
        if(classid_by==JS_CLASS_INT8_ARRAY) {
            size_t offset_by;
            size_t size_by;
            JSValue da_by = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_by,&size_by,NULL);
            by = (char *)JS_GetArrayBuffer(ctx, &size_by, da_by);
            by+=offset_by;
            size_by-=offset_by;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_by);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[2] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * returnVal = TextReplace((const char *)text, (const char *)replace, (const char *)by);
    memoryClear(ctx, memoryHead);
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextInsert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            JSValue da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * insert;
    int64_t size_insert;
    if(JS_IsString(argv[1]) == 1) {
        insert = (char *)JS_ToCStringLen(ctx, &size_insert, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, insert);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_insert = JS_DupValue(ctx,argv[1]);
        size_t size_insert;
        insert = (char *)JS_GetArrayBuffer(ctx, &size_insert, da_insert);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_insert);
    }
    else {
        JSClassID classid_insert = JS_GetClassID(argv[1]);
        if(classid_insert==JS_CLASS_INT8_ARRAY) {
            size_t offset_insert;
            size_t size_insert;
            JSValue da_insert = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_insert,&size_insert,NULL);
            insert = (char *)JS_GetArrayBuffer(ctx, &size_insert, da_insert);
            insert+=offset_insert;
            size_insert-=offset_insert;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_insert);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_position;
    int err_position = JS_ToInt32(ctx, &long_position, argv[2]);
    if(err_position<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int position = (int)long_position;
    char * returnVal = TextInsert((const char *)text, (const char *)insert, position);
    memoryClear(ctx, memoryHead);
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextJoin(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * * textList;
    int64_t size_textList;
    if(JS_IsArray(argv[0]) == 1) {
        if(JS_GetLength(ctx,argv[0],&size_textList)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        textList = (char * *)js_malloc(ctx, size_textList * sizeof(char *));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, textList);
        for(int i0=0; i0 < size_textList; i0++){
            JSValue js_textList = JS_GetPropertyUint32(ctx,argv[0],i0);
            int64_t size_textListi0;
            if(JS_IsString(js_textList) == 1) {
                textList[i0] = (char *)JS_ToCStringLen(ctx, &size_textListi0, js_textList);
                memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, textList[i0]);
            }
            else if(JS_IsArrayBuffer(js_textList) == 1) {
                JSValue da_textListi0 = JS_DupValue(ctx,js_textList);
                size_t size_textListi0;
                textList[i0] = (char *)JS_GetArrayBuffer(ctx, &size_textListi0, da_textListi0);
                memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_textListi0);
            }
            else {
                JSClassID classid_textListi0 = JS_GetClassID(js_textList);
                if(classid_textListi0==JS_CLASS_INT8_ARRAY) {
                    size_t offset_textListi0;
                    size_t size_textListi0;
                    JSValue da_textListi0 = JS_GetTypedArrayBuffer(ctx,js_textList,&offset_textListi0,&size_textListi0,NULL);
                    textList[i0] = (char *)JS_GetArrayBuffer(ctx, &size_textListi0, da_textListi0);
                    textList[i0]+=offset_textListi0;
                    size_textListi0-=offset_textListi0;
                    memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_textListi0);
                }
                else {
                    JS_ThrowTypeError(ctx, "js_textList does not match type char *");
                    return JS_EXCEPTION;
                }
            }
            JS_FreeValue(ctx, js_textList);
        }
    }
    else {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[0] does not match type char * *");
        return JS_EXCEPTION;
    }
    int32_t long_count;
    int err_count = JS_ToInt32(ctx, &long_count, argv[1]);
    if(err_count<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int count = (int)long_count;
    char * delimiter;
    int64_t size_delimiter;
    if(JS_IsString(argv[2]) == 1) {
        delimiter = (char *)JS_ToCStringLen(ctx, &size_delimiter, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, delimiter);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JSValue da_delimiter = JS_DupValue(ctx,argv[2]);
        size_t size_delimiter;
        delimiter = (char *)JS_GetArrayBuffer(ctx, &size_delimiter, da_delimiter);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_delimiter);
    }
    else {
        JSClassID classid_delimiter = JS_GetClassID(argv[2]);
        if(classid_delimiter==JS_CLASS_INT8_ARRAY) {
            size_t offset_delimiter;
            size_t size_delimiter;
            JSValue da_delimiter = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_delimiter,&size_delimiter,NULL);
            delimiter = (char *)JS_GetArrayBuffer(ctx, &size_delimiter, da_delimiter);
            delimiter+=offset_delimiter;
            size_delimiter-=offset_delimiter;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_delimiter);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[2] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * returnVal = TextJoin(textList, count, (const char *)delimiter);
    memoryClear(ctx, memoryHead);
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextSplit(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * js_delimiter = (char *)JS_ToCString(ctx, argv[1]);
    char delimiter = (char)js_delimiter[0];
    JS_FreeCString(ctx, js_delimiter);
    int * count;
    JSValue da_count;
    int64_t size_count;
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_count)==-1) {
            if(JS_IsArray(argv[0]) == 1) {
                js_free(ctx, text);
            }
            else if(JS_IsString(argv[0]) == 1) {
                JS_FreeCString(ctx, text);
            }
            else if(JS_IsArrayBuffer(argv[0]) == 1) {
                JS_FreeValue(ctx, da_text);
            }
            else {
                JSClassID classid_text = JS_GetClassID(argv[0]);
                if(classid_text==JS_CLASS_INT8_ARRAY) {
                    js_free(ctx, &da_text);
                }
            }
            return JS_EXCEPTION;
        }
        count = (int *)js_malloc(ctx, size_count * sizeof(int));
        for(int i0=0; i0 < size_count; i0++){
            JSValue js_count = JS_GetPropertyUint32(ctx,argv[2],i0);
            int32_t long_counti0;
            int err_counti0 = JS_ToInt32(ctx, &long_counti0, js_count);
            if(err_counti0<0) {
                JS_ThrowTypeError(ctx, "js_count is not numeric");
                return JS_EXCEPTION;
            }
            count[i0] = (int)long_counti0;
            JS_FreeValue(ctx, js_count);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        da_count = JS_DupValue(ctx,argv[2]);
        size_t size_count;
        count = (int *)JS_GetArrayBuffer(ctx, &size_count, da_count);
    }
    else {
        JSClassID classid_count = JS_GetClassID(argv[2]);
        if(classid_count==JS_CLASS_INT16_ARRAY) {
            size_t offset_count;
            size_t size_count;
            da_count = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_count,&size_count,NULL);
            count = (int *)JS_GetArrayBuffer(ctx, &size_count, da_count);
            count+=offset_count;
            size_count-=offset_count;
        }
        else {
            int32_t long_js_count;
            int err_js_count = JS_ToInt32(ctx, &long_js_count, argv[2]);
            if(err_js_count<0) {
                if(JS_IsArray(argv[0]) == 1) {
                    js_free(ctx, text);
                }
                else if(JS_IsString(argv[0]) == 1) {
                    JS_FreeCString(ctx, text);
                }
                else if(JS_IsArrayBuffer(argv[0]) == 1) {
                    JS_FreeValue(ctx, da_text);
                }
                else {
                    JSClassID classid_text = JS_GetClassID(argv[0]);
                    if(classid_text==JS_CLASS_INT8_ARRAY) {
                        js_free(ctx, &da_text);
                    }
                }
                JS_ThrowTypeError(ctx, "argv[2] is not numeric");
                return JS_EXCEPTION;
            }
            int js_count = (int)long_js_count;
            count = &js_count;
        }
    }
    char * * returnVal = TextSplit((const char *)text, delimiter, count);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewInt32(ctx, (long)count[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, count);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_count);
    }
    else {
        JSClassID classid_count = JS_GetClassID(argv[2]);
        if(classid_count==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &da_count);
        }
    }
    JSValue ret;
    ret = JS_NewArray(ctx);
    size_t size_ret = sizeof(returnVal)/sizeof(char *);
    for(int i0=0; i0 < size_ret; i0++){
        JSValue js_ret;
        js_ret = JS_NewString(ctx, returnVal[i0]);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_TextAppend(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            JSValue da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * append;
    int64_t size_append;
    if(JS_IsString(argv[1]) == 1) {
        append = (char *)JS_ToCStringLen(ctx, &size_append, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, append);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_append = JS_DupValue(ctx,argv[1]);
        size_t size_append;
        append = (char *)JS_GetArrayBuffer(ctx, &size_append, da_append);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_append);
    }
    else {
        JSClassID classid_append = JS_GetClassID(argv[1]);
        if(classid_append==JS_CLASS_INT8_ARRAY) {
            size_t offset_append;
            size_t size_append;
            JSValue da_append = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_append,&size_append,NULL);
            append = (char *)JS_GetArrayBuffer(ctx, &size_append, da_append);
            append+=offset_append;
            size_append-=offset_append;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_append);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int * position;
    int64_t size_position;
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_position)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        position = (int *)js_malloc(ctx, size_position * sizeof(int));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, position);
        for(int i0=0; i0 < size_position; i0++){
            JSValue js_position = JS_GetPropertyUint32(ctx,argv[2],i0);
            int32_t long_positioni0;
            int err_positioni0 = JS_ToInt32(ctx, &long_positioni0, js_position);
            if(err_positioni0<0) {
                JS_ThrowTypeError(ctx, "js_position is not numeric");
                return JS_EXCEPTION;
            }
            position[i0] = (int)long_positioni0;
            JS_FreeValue(ctx, js_position);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JSValue da_position = JS_DupValue(ctx,argv[2]);
        size_t size_position;
        position = (int *)JS_GetArrayBuffer(ctx, &size_position, da_position);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_position);
    }
    else {
        JSClassID classid_position = JS_GetClassID(argv[2]);
        if(classid_position==JS_CLASS_INT16_ARRAY) {
            size_t offset_position;
            size_t size_position;
            JSValue da_position = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_position,&size_position,NULL);
            position = (int *)JS_GetArrayBuffer(ctx, &size_position, da_position);
            position+=offset_position;
            size_position-=offset_position;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_position);
        }
        else {
            int32_t long_js_position;
            int err_js_position = JS_ToInt32(ctx, &long_js_position, argv[2]);
            if(err_js_position<0) {
                memoryClear(ctx, memoryHead);
                JS_ThrowTypeError(ctx, "argv[2] is not numeric");
                return JS_EXCEPTION;
            }
            int js_position = (int)long_js_position;
            position = &js_position;
        }
    }
    TextAppend(text, (const char *)append, position);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewInt32(ctx, (long)position[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
    memoryClear(ctx, memoryHead);
    return JS_UNDEFINED;
}

static JSValue js_TextFindIndex(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            JSValue da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * find;
    int64_t size_find;
    if(JS_IsString(argv[1]) == 1) {
        find = (char *)JS_ToCStringLen(ctx, &size_find, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, find);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_find = JS_DupValue(ctx,argv[1]);
        size_t size_find;
        find = (char *)JS_GetArrayBuffer(ctx, &size_find, da_find);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_find);
    }
    else {
        JSClassID classid_find = JS_GetClassID(argv[1]);
        if(classid_find==JS_CLASS_INT8_ARRAY) {
            size_t offset_find;
            size_t size_find;
            JSValue da_find = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_find,&size_find,NULL);
            find = (char *)JS_GetArrayBuffer(ctx, &size_find, da_find);
            find+=offset_find;
            size_find-=offset_find;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_find);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int returnVal = TextFindIndex((const char *)text, (const char *)find);
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_TextToUpper(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * returnVal = TextToUpper((const char *)text);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextToLower(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * returnVal = TextToLower((const char *)text);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextToPascal(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * returnVal = TextToPascal((const char *)text);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextToSnake(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * returnVal = TextToSnake((const char *)text);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextToCamel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * returnVal = TextToCamel((const char *)text);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextToInteger(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int returnVal = TextToInteger((const char *)text);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_TextToFloat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            da_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    float returnVal = TextToFloat((const char *)text);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_text);
        }
    }
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_DrawLine3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_startPos = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_startPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 startPos = *ptr_startPos;
    Vector3* ptr_endPos = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_endPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 endPos = *ptr_endPos;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawLine3D(startPos, endPos, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawPoint3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawPoint3D(position, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCircle3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_center = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 center = *ptr_center;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[1]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    Vector3* ptr_rotationAxis = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_rotationAxis == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 rotationAxis = *ptr_rotationAxis;
    double double_rotationAngle;
    int err_rotationAngle = JS_ToFloat64(ctx, &double_rotationAngle, argv[3]);
    if(err_rotationAngle<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float rotationAngle = (float)double_rotationAngle;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawTriangle3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v1 = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v1 = *ptr_v1;
    Vector3* ptr_v2 = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v2 = *ptr_v2;
    Vector3* ptr_v3 = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_v3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v3 = *ptr_v3;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawTriangle3D(v1, v2, v3, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCube(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    double double_width;
    int err_width = JS_ToFloat64(ctx, &double_width, argv[1]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float width = (float)double_width;
    double double_height;
    int err_height = JS_ToFloat64(ctx, &double_height, argv[2]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float height = (float)double_height;
    double double_length;
    int err_length = JS_ToFloat64(ctx, &double_length, argv[3]);
    if(err_length<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float length = (float)double_length;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCube(position, width, height, length, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCubeV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Vector3* ptr_size = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_size == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 size = *ptr_size;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCubeV(position, size, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCubeWires(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    double double_width;
    int err_width = JS_ToFloat64(ctx, &double_width, argv[1]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float width = (float)double_width;
    double double_height;
    int err_height = JS_ToFloat64(ctx, &double_height, argv[2]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float height = (float)double_height;
    double double_length;
    int err_length = JS_ToFloat64(ctx, &double_length, argv[3]);
    if(err_length<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float length = (float)double_length;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCubeWires(position, width, height, length, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCubeWiresV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Vector3* ptr_size = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_size == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 size = *ptr_size;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCubeWiresV(position, size, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawSphere(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_centerPos = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_centerPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 centerPos = *ptr_centerPos;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[1]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSphere(centerPos, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawSphereEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_centerPos = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_centerPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 centerPos = *ptr_centerPos;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[1]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    int32_t long_rings;
    int err_rings = JS_ToInt32(ctx, &long_rings, argv[2]);
    if(err_rings<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int rings = (int)long_rings;
    int32_t long_slices;
    int err_slices = JS_ToInt32(ctx, &long_slices, argv[3]);
    if(err_slices<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int slices = (int)long_slices;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSphereEx(centerPos, radius, rings, slices, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawSphereWires(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_centerPos = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_centerPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 centerPos = *ptr_centerPos;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[1]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    int32_t long_rings;
    int err_rings = JS_ToInt32(ctx, &long_rings, argv[2]);
    if(err_rings<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int rings = (int)long_rings;
    int32_t long_slices;
    int err_slices = JS_ToInt32(ctx, &long_slices, argv[3]);
    if(err_slices<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int slices = (int)long_slices;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawSphereWires(centerPos, radius, rings, slices, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCylinder(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    double double_radiusTop;
    int err_radiusTop = JS_ToFloat64(ctx, &double_radiusTop, argv[1]);
    if(err_radiusTop<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radiusTop = (float)double_radiusTop;
    double double_radiusBottom;
    int err_radiusBottom = JS_ToFloat64(ctx, &double_radiusBottom, argv[2]);
    if(err_radiusBottom<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radiusBottom = (float)double_radiusBottom;
    double double_height;
    int err_height = JS_ToFloat64(ctx, &double_height, argv[3]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float height = (float)double_height;
    int32_t long_slices;
    int err_slices = JS_ToInt32(ctx, &long_slices, argv[4]);
    if(err_slices<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int slices = (int)long_slices;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCylinderEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_startPos = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_startPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 startPos = *ptr_startPos;
    Vector3* ptr_endPos = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_endPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 endPos = *ptr_endPos;
    double double_startRadius;
    int err_startRadius = JS_ToFloat64(ctx, &double_startRadius, argv[2]);
    if(err_startRadius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float startRadius = (float)double_startRadius;
    double double_endRadius;
    int err_endRadius = JS_ToFloat64(ctx, &double_endRadius, argv[3]);
    if(err_endRadius<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float endRadius = (float)double_endRadius;
    int32_t long_sides;
    int err_sides = JS_ToInt32(ctx, &long_sides, argv[4]);
    if(err_sides<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int sides = (int)long_sides;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCylinderEx(startPos, endPos, startRadius, endRadius, sides, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCylinderWires(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    double double_radiusTop;
    int err_radiusTop = JS_ToFloat64(ctx, &double_radiusTop, argv[1]);
    if(err_radiusTop<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radiusTop = (float)double_radiusTop;
    double double_radiusBottom;
    int err_radiusBottom = JS_ToFloat64(ctx, &double_radiusBottom, argv[2]);
    if(err_radiusBottom<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radiusBottom = (float)double_radiusBottom;
    double double_height;
    int err_height = JS_ToFloat64(ctx, &double_height, argv[3]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float height = (float)double_height;
    int32_t long_slices;
    int err_slices = JS_ToInt32(ctx, &long_slices, argv[4]);
    if(err_slices<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int slices = (int)long_slices;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCylinderWiresEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_startPos = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_startPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 startPos = *ptr_startPos;
    Vector3* ptr_endPos = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_endPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 endPos = *ptr_endPos;
    double double_startRadius;
    int err_startRadius = JS_ToFloat64(ctx, &double_startRadius, argv[2]);
    if(err_startRadius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float startRadius = (float)double_startRadius;
    double double_endRadius;
    int err_endRadius = JS_ToFloat64(ctx, &double_endRadius, argv[3]);
    if(err_endRadius<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float endRadius = (float)double_endRadius;
    int32_t long_sides;
    int err_sides = JS_ToInt32(ctx, &long_sides, argv[4]);
    if(err_sides<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int sides = (int)long_sides;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCylinderWiresEx(startPos, endPos, startRadius, endRadius, sides, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCapsule(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_startPos = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_startPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 startPos = *ptr_startPos;
    Vector3* ptr_endPos = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_endPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 endPos = *ptr_endPos;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    int32_t long_slices;
    int err_slices = JS_ToInt32(ctx, &long_slices, argv[3]);
    if(err_slices<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int slices = (int)long_slices;
    int32_t long_rings;
    int err_rings = JS_ToInt32(ctx, &long_rings, argv[4]);
    if(err_rings<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int rings = (int)long_rings;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCapsule(startPos, endPos, radius, slices, rings, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawCapsuleWires(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_startPos = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_startPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 startPos = *ptr_startPos;
    Vector3* ptr_endPos = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_endPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 endPos = *ptr_endPos;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    int32_t long_slices;
    int err_slices = JS_ToInt32(ctx, &long_slices, argv[3]);
    if(err_slices<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int slices = (int)long_slices;
    int32_t long_rings;
    int err_rings = JS_ToInt32(ctx, &long_rings, argv[4]);
    if(err_rings<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int rings = (int)long_rings;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawCapsuleWires(startPos, endPos, radius, slices, rings, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawPlane(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_centerPos = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_centerPos == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 centerPos = *ptr_centerPos;
    Vector2* ptr_size = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_size == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 size = *ptr_size;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[2], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawPlane(centerPos, size, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawRay(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ptr_ray = (Ray*)JS_GetOpaque(argv[0], js_Ray_class_id);
    if(ptr_ray == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Ray ray = *ptr_ray;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawRay(ray, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawGrid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_slices;
    int err_slices = JS_ToInt32(ctx, &long_slices, argv[0]);
    if(err_slices<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int slices = (int)long_slices;
    double double_spacing;
    int err_spacing = JS_ToFloat64(ctx, &double_spacing, argv[1]);
    if(err_spacing<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float spacing = (float)double_spacing;
    DrawGrid(slices, spacing);
    return JS_UNDEFINED;
}

static JSValue js_LoadModel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Model returnVal = LoadModel((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    Model* ptr_ret = (Model*)js_malloc(ctx, sizeof(Model));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Model_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadModelFromMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* ptr_mesh = (Mesh*)JS_GetOpaque(argv[0], js_Mesh_class_id);
    if(ptr_mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Mesh mesh = *ptr_mesh;
    Model returnVal = LoadModelFromMesh(mesh);
    Model* ptr_ret = (Model*)js_malloc(ctx, sizeof(Model));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Model_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_IsModelValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* ptr_model = (Model*)JS_GetOpaque(argv[0], js_Model_class_id);
    if(ptr_model == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Model model = *ptr_model;
    bool returnVal = IsModelValid(model);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_UnloadModel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* ptr_model = (Model*)JS_GetOpaque(argv[0], js_Model_class_id);
    if(ptr_model == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Model model = *ptr_model;
    UnloadModel(model);
    return JS_UNDEFINED;
}

static JSValue js_GetModelBoundingBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* ptr_model = (Model*)JS_GetOpaque(argv[0], js_Model_class_id);
    if(ptr_model == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Model model = *ptr_model;
    BoundingBox returnVal = GetModelBoundingBox(model);
    BoundingBox* ptr_ret = (BoundingBox*)js_malloc(ctx, sizeof(BoundingBox));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_BoundingBox_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_DrawModel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* ptr_model = (Model*)JS_GetOpaque(argv[0], js_Model_class_id);
    if(ptr_model == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Model model = *ptr_model;
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    double double_scale;
    int err_scale = JS_ToFloat64(ctx, &double_scale, argv[2]);
    if(err_scale<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float scale = (float)double_scale;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawModel(model, position, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawModelEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* ptr_model = (Model*)JS_GetOpaque(argv[0], js_Model_class_id);
    if(ptr_model == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Model model = *ptr_model;
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Vector3* ptr_rotationAxis = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_rotationAxis == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 rotationAxis = *ptr_rotationAxis;
    double double_rotationAngle;
    int err_rotationAngle = JS_ToFloat64(ctx, &double_rotationAngle, argv[3]);
    if(err_rotationAngle<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float rotationAngle = (float)double_rotationAngle;
    Vector3* ptr_scale = (Vector3*)JS_GetOpaque(argv[4], js_Vector3_class_id);
    if(ptr_scale == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 scale = *ptr_scale;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawModelWires(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* ptr_model = (Model*)JS_GetOpaque(argv[0], js_Model_class_id);
    if(ptr_model == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Model model = *ptr_model;
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    double double_scale;
    int err_scale = JS_ToFloat64(ctx, &double_scale, argv[2]);
    if(err_scale<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float scale = (float)double_scale;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawModelWires(model, position, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawModelWiresEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* ptr_model = (Model*)JS_GetOpaque(argv[0], js_Model_class_id);
    if(ptr_model == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Model model = *ptr_model;
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Vector3* ptr_rotationAxis = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_rotationAxis == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 rotationAxis = *ptr_rotationAxis;
    double double_rotationAngle;
    int err_rotationAngle = JS_ToFloat64(ctx, &double_rotationAngle, argv[3]);
    if(err_rotationAngle<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float rotationAngle = (float)double_rotationAngle;
    Vector3* ptr_scale = (Vector3*)JS_GetOpaque(argv[4], js_Vector3_class_id);
    if(ptr_scale == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 scale = *ptr_scale;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawModelPoints(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* ptr_model = (Model*)JS_GetOpaque(argv[0], js_Model_class_id);
    if(ptr_model == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Model model = *ptr_model;
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    double double_scale;
    int err_scale = JS_ToFloat64(ctx, &double_scale, argv[2]);
    if(err_scale<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float scale = (float)double_scale;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawModelPoints(model, position, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawModelPointsEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* ptr_model = (Model*)JS_GetOpaque(argv[0], js_Model_class_id);
    if(ptr_model == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Model model = *ptr_model;
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Vector3* ptr_rotationAxis = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_rotationAxis == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 rotationAxis = *ptr_rotationAxis;
    double double_rotationAngle;
    int err_rotationAngle = JS_ToFloat64(ctx, &double_rotationAngle, argv[3]);
    if(err_rotationAngle<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float rotationAngle = (float)double_rotationAngle;
    Vector3* ptr_scale = (Vector3*)JS_GetOpaque(argv[4], js_Vector3_class_id);
    if(ptr_scale == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 scale = *ptr_scale;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawModelPointsEx(model, position, rotationAxis, rotationAngle, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawBoundingBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    BoundingBox* ptr_box = (BoundingBox*)JS_GetOpaque(argv[0], js_BoundingBox_class_id);
    if(ptr_box == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    BoundingBox box = *ptr_box;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[1], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    DrawBoundingBox(box, color);
    return JS_UNDEFINED;
}

static JSValue js_DrawBillboard(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* ptr_camera = (Camera*)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Camera camera = *ptr_camera;
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[1], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    double double_scale;
    int err_scale = JS_ToFloat64(ctx, &double_scale, argv[3]);
    if(err_scale<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float scale = (float)double_scale;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawBillboard(camera, texture, position, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawBillboardRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* ptr_camera = (Camera*)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Camera camera = *ptr_camera;
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[1], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    Rectangle* ptr_source = (Rectangle*)JS_GetOpaque(argv[2], js_Rectangle_class_id);
    if(ptr_source == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle source = *ptr_source;
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[3], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Vector2* ptr_size = (Vector2*)JS_GetOpaque(argv[4], js_Vector2_class_id);
    if(ptr_size == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 size = *ptr_size;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[5], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawBillboardRec(camera, texture, source, position, size, tint);
    return JS_UNDEFINED;
}

static JSValue js_DrawBillboardPro(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* ptr_camera = (Camera*)JS_GetOpaque(argv[0], js_Camera3D_class_id);
    if(ptr_camera == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Camera camera = *ptr_camera;
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[1], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    Rectangle* ptr_source = (Rectangle*)JS_GetOpaque(argv[2], js_Rectangle_class_id);
    if(ptr_source == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle source = *ptr_source;
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[3], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Vector3* ptr_up = (Vector3*)JS_GetOpaque(argv[4], js_Vector3_class_id);
    if(ptr_up == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 up = *ptr_up;
    Vector2* ptr_size = (Vector2*)JS_GetOpaque(argv[5], js_Vector2_class_id);
    if(ptr_size == NULL) {
        JS_ThrowTypeError(ctx, "argv[5] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 size = *ptr_size;
    Vector2* ptr_origin = (Vector2*)JS_GetOpaque(argv[6], js_Vector2_class_id);
    if(ptr_origin == NULL) {
        JS_ThrowTypeError(ctx, "argv[6] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 origin = *ptr_origin;
    double double_rotation;
    int err_rotation = JS_ToFloat64(ctx, &double_rotation, argv[7]);
    if(err_rotation<0) {
        JS_ThrowTypeError(ctx, "argv[7] is not numeric");
        return JS_EXCEPTION;
    }
    float rotation = (float)double_rotation;
    Color* ptr_tint = (Color*)JS_GetOpaque(argv[8], js_Color_class_id);
    if(ptr_tint == NULL) {
        JS_ThrowTypeError(ctx, "argv[8] does not allow null");
        return JS_EXCEPTION;
    }
    Color tint = *ptr_tint;
    DrawBillboardPro(camera, texture, source, position, up, size, origin, rotation, tint);
    return JS_UNDEFINED;
}

static JSValue js_UploadMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh * mesh = (Mesh *)JS_GetOpaque(argv[0], js_Mesh_class_id);
    if(mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Mesh");
        return JS_EXCEPTION;
    }
    int js_dynamic = JS_ToBool(ctx, argv[1]);
    if(js_dynamic<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not a bool");
        return JS_EXCEPTION;
    }
    bool dynamic = js_dynamic;
    UploadMesh(mesh, dynamic);
    return JS_UNDEFINED;
}

static JSValue js_UpdateMeshBuffer(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* ptr_mesh = (Mesh*)JS_GetOpaque(argv[0], js_Mesh_class_id);
    if(ptr_mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Mesh mesh = *ptr_mesh;
    int32_t long_index;
    int err_index = JS_ToInt32(ctx, &long_index, argv[1]);
    if(err_index<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int index = (int)long_index;
    void * data;
    JSValue da_data;
    int64_t size_data;
    if(JS_IsArrayBuffer(argv[2]) == 1) {
        da_data = JS_DupValue(ctx,argv[2]);
        size_t size_data;
        data = (void *)JS_GetArrayBuffer(ctx, &size_data, da_data);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[2] does not match type void *");
        return JS_EXCEPTION;
    }
    int32_t long_dataSize;
    int err_dataSize = JS_ToInt32(ctx, &long_dataSize, argv[3]);
    if(err_dataSize<0) {
        if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_data);
        }
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int dataSize = (int)long_dataSize;
    int32_t long_offset;
    int err_offset = JS_ToInt32(ctx, &long_offset, argv[4]);
    if(err_offset<0) {
        if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_data);
        }
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int offset = (int)long_offset;
    UpdateMeshBuffer(mesh, index, (const void *)data, dataSize, offset);
    if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_data);
    }
    return JS_UNDEFINED;
}

static JSValue js_UnloadMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* ptr_mesh = (Mesh*)JS_GetOpaque(argv[0], js_Mesh_class_id);
    if(ptr_mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Mesh mesh = *ptr_mesh;
    UnloadMesh(mesh);
    return JS_UNDEFINED;
}

static JSValue js_DrawMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* ptr_mesh = (Mesh*)JS_GetOpaque(argv[0], js_Mesh_class_id);
    if(ptr_mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Mesh mesh = *ptr_mesh;
    Material* ptr_material = (Material*)JS_GetOpaque(argv[1], js_Material_class_id);
    if(ptr_material == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Material material = *ptr_material;
    Matrix* ptr_transform = (Matrix*)JS_GetOpaque(argv[2], js_Matrix_class_id);
    if(ptr_transform == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix transform = *ptr_transform;
    DrawMesh(mesh, material, transform);
    return JS_UNDEFINED;
}

static JSValue js_DrawMeshInstanced(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* ptr_mesh = (Mesh*)JS_GetOpaque(argv[0], js_Mesh_class_id);
    if(ptr_mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Mesh mesh = *ptr_mesh;
    Material* ptr_material = (Material*)JS_GetOpaque(argv[1], js_Material_class_id);
    if(ptr_material == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Material material = *ptr_material;
    Matrix * transforms;
    JSValue da_transforms;
    int64_t size_transforms;
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_transforms)==-1) {
            return JS_EXCEPTION;
        }
        transforms = (Matrix *)js_malloc(ctx, size_transforms * sizeof(Matrix));
        for(int i0=0; i0 < size_transforms; i0++){
            JSValue js_transforms = JS_GetPropertyUint32(ctx,argv[2],i0);
            Matrix* ptr_transformsi0 = (Matrix*)JS_GetOpaque(js_transforms, js_Matrix_class_id);
            if(ptr_transformsi0 == NULL) {
                JS_ThrowTypeError(ctx, "js_transforms does not allow null");
                return JS_EXCEPTION;
            }
            transforms[i0] = *ptr_transformsi0;
            JS_FreeValue(ctx, js_transforms);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        da_transforms = JS_DupValue(ctx,argv[2]);
        size_t size_transforms;
        transforms = (Matrix *)JS_GetArrayBuffer(ctx, &size_transforms, da_transforms);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[2] does not match type Matrix *");
        return JS_EXCEPTION;
    }
    int32_t long_instances;
    int err_instances = JS_ToInt32(ctx, &long_instances, argv[3]);
    if(err_instances<0) {
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, transforms);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_transforms);
        }
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int instances = (int)long_instances;
    DrawMeshInstanced(mesh, material, (const Matrix *)transforms, instances);
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, transforms);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_transforms);
    }
    return JS_UNDEFINED;
}

static JSValue js_GetMeshBoundingBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* ptr_mesh = (Mesh*)JS_GetOpaque(argv[0], js_Mesh_class_id);
    if(ptr_mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Mesh mesh = *ptr_mesh;
    BoundingBox returnVal = GetMeshBoundingBox(mesh);
    BoundingBox* ptr_ret = (BoundingBox*)js_malloc(ctx, sizeof(BoundingBox));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_BoundingBox_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenMeshTangents(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh * mesh = (Mesh *)JS_GetOpaque(argv[0], js_Mesh_class_id);
    if(mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Mesh");
        return JS_EXCEPTION;
    }
    GenMeshTangents(mesh);
    return JS_UNDEFINED;
}

static JSValue js_ExportMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* ptr_mesh = (Mesh*)JS_GetOpaque(argv[0], js_Mesh_class_id);
    if(ptr_mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Mesh mesh = *ptr_mesh;
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[1]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[1]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ExportMesh(mesh, (const char *)fileName);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_ExportMeshAsCode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* ptr_mesh = (Mesh*)JS_GetOpaque(argv[0], js_Mesh_class_id);
    if(ptr_mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Mesh mesh = *ptr_mesh;
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[1]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[1]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ExportMeshAsCode(mesh, (const char *)fileName);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_GenMeshPoly(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_sides;
    int err_sides = JS_ToInt32(ctx, &long_sides, argv[0]);
    if(err_sides<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int sides = (int)long_sides;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[1]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    Mesh returnVal = GenMeshPoly(sides, radius);
    Mesh* ptr_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenMeshPlane(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_width;
    int err_width = JS_ToFloat64(ctx, &double_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float width = (float)double_width;
    double double_length;
    int err_length = JS_ToFloat64(ctx, &double_length, argv[1]);
    if(err_length<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float length = (float)double_length;
    int32_t long_resX;
    int err_resX = JS_ToInt32(ctx, &long_resX, argv[2]);
    if(err_resX<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int resX = (int)long_resX;
    int32_t long_resZ;
    int err_resZ = JS_ToInt32(ctx, &long_resZ, argv[3]);
    if(err_resZ<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int resZ = (int)long_resZ;
    Mesh returnVal = GenMeshPlane(width, length, resX, resZ);
    Mesh* ptr_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenMeshCube(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_width;
    int err_width = JS_ToFloat64(ctx, &double_width, argv[0]);
    if(err_width<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float width = (float)double_width;
    double double_height;
    int err_height = JS_ToFloat64(ctx, &double_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float height = (float)double_height;
    double double_length;
    int err_length = JS_ToFloat64(ctx, &double_length, argv[2]);
    if(err_length<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float length = (float)double_length;
    Mesh returnVal = GenMeshCube(width, height, length);
    Mesh* ptr_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenMeshSphere(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[0]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    int32_t long_rings;
    int err_rings = JS_ToInt32(ctx, &long_rings, argv[1]);
    if(err_rings<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int rings = (int)long_rings;
    int32_t long_slices;
    int err_slices = JS_ToInt32(ctx, &long_slices, argv[2]);
    if(err_slices<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int slices = (int)long_slices;
    Mesh returnVal = GenMeshSphere(radius, rings, slices);
    Mesh* ptr_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenMeshHemiSphere(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[0]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    int32_t long_rings;
    int err_rings = JS_ToInt32(ctx, &long_rings, argv[1]);
    if(err_rings<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int rings = (int)long_rings;
    int32_t long_slices;
    int err_slices = JS_ToInt32(ctx, &long_slices, argv[2]);
    if(err_slices<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int slices = (int)long_slices;
    Mesh returnVal = GenMeshHemiSphere(radius, rings, slices);
    Mesh* ptr_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenMeshCylinder(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[0]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    double double_height;
    int err_height = JS_ToFloat64(ctx, &double_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float height = (float)double_height;
    int32_t long_slices;
    int err_slices = JS_ToInt32(ctx, &long_slices, argv[2]);
    if(err_slices<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int slices = (int)long_slices;
    Mesh returnVal = GenMeshCylinder(radius, height, slices);
    Mesh* ptr_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenMeshCone(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[0]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    double double_height;
    int err_height = JS_ToFloat64(ctx, &double_height, argv[1]);
    if(err_height<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float height = (float)double_height;
    int32_t long_slices;
    int err_slices = JS_ToInt32(ctx, &long_slices, argv[2]);
    if(err_slices<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int slices = (int)long_slices;
    Mesh returnVal = GenMeshCone(radius, height, slices);
    Mesh* ptr_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenMeshTorus(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[0]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    double double_size;
    int err_size = JS_ToFloat64(ctx, &double_size, argv[1]);
    if(err_size<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float size = (float)double_size;
    int32_t long_radSeg;
    int err_radSeg = JS_ToInt32(ctx, &long_radSeg, argv[2]);
    if(err_radSeg<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int radSeg = (int)long_radSeg;
    int32_t long_sides;
    int err_sides = JS_ToInt32(ctx, &long_sides, argv[3]);
    if(err_sides<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int sides = (int)long_sides;
    Mesh returnVal = GenMeshTorus(radius, size, radSeg, sides);
    Mesh* ptr_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenMeshKnot(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[0]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    double double_size;
    int err_size = JS_ToFloat64(ctx, &double_size, argv[1]);
    if(err_size<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float size = (float)double_size;
    int32_t long_radSeg;
    int err_radSeg = JS_ToInt32(ctx, &long_radSeg, argv[2]);
    if(err_radSeg<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int radSeg = (int)long_radSeg;
    int32_t long_sides;
    int err_sides = JS_ToInt32(ctx, &long_sides, argv[3]);
    if(err_sides<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int sides = (int)long_sides;
    Mesh returnVal = GenMeshKnot(radius, size, radSeg, sides);
    Mesh* ptr_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenMeshHeightmap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_heightmap = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_heightmap == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image heightmap = *ptr_heightmap;
    Vector3* ptr_size = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_size == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 size = *ptr_size;
    Mesh returnVal = GenMeshHeightmap(heightmap, size);
    Mesh* ptr_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GenMeshCubicmap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* ptr_cubicmap = (Image*)JS_GetOpaque(argv[0], js_Image_class_id);
    if(ptr_cubicmap == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Image cubicmap = *ptr_cubicmap;
    Vector3* ptr_cubeSize = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_cubeSize == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 cubeSize = *ptr_cubeSize;
    Mesh returnVal = GenMeshCubicmap(cubicmap, cubeSize);
    Mesh* ptr_ret = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadMaterialDefault(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Material returnVal = LoadMaterialDefault();
    Material* ptr_ret = (Material*)js_malloc(ctx, sizeof(Material));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Material_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_IsMaterialValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Material* ptr_material = (Material*)JS_GetOpaque(argv[0], js_Material_class_id);
    if(ptr_material == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Material material = *ptr_material;
    bool returnVal = IsMaterialValid(material);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_UnloadMaterial(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Material* ptr_material = (Material*)JS_GetOpaque(argv[0], js_Material_class_id);
    if(ptr_material == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Material material = *ptr_material;
    UnloadMaterial(material);
    return JS_UNDEFINED;
}

static JSValue js_SetMaterialTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Material * material = (Material *)JS_GetOpaque(argv[0], js_Material_class_id);
    if(material == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Material");
        return JS_EXCEPTION;
    }
    int32_t long_mapType;
    int err_mapType = JS_ToInt32(ctx, &long_mapType, argv[1]);
    if(err_mapType<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int mapType = (int)long_mapType;
    Texture2D* ptr_texture = (Texture2D*)JS_GetOpaque(argv[2], js_Texture_class_id);
    if(ptr_texture == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Texture2D texture = *ptr_texture;
    SetMaterialTexture(material, mapType, texture);
    return JS_UNDEFINED;
}

static JSValue js_SetModelMeshMaterial(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model * model = (Model *)JS_GetOpaque(argv[0], js_Model_class_id);
    if(model == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Model");
        return JS_EXCEPTION;
    }
    int32_t long_meshId;
    int err_meshId = JS_ToInt32(ctx, &long_meshId, argv[1]);
    if(err_meshId<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int meshId = (int)long_meshId;
    int32_t long_materialId;
    int err_materialId = JS_ToInt32(ctx, &long_materialId, argv[2]);
    if(err_materialId<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int materialId = (int)long_materialId;
    SetModelMeshMaterial(model, meshId, materialId);
    return JS_UNDEFINED;
}

static JSValue js_UpdateModelAnimationBones(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* ptr_model = (Model*)JS_GetOpaque(argv[0], js_Model_class_id);
    if(ptr_model == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Model model = *ptr_model;
    ModelAnimation* ptr_anim = (ModelAnimation*)JS_GetOpaque(argv[1], js_ModelAnimation_class_id);
    if(ptr_anim == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    ModelAnimation anim = *ptr_anim;
    int32_t long_frame;
    int err_frame = JS_ToInt32(ctx, &long_frame, argv[2]);
    if(err_frame<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int frame = (int)long_frame;
    UpdateModelAnimationBones(model, anim, frame);
    return JS_UNDEFINED;
}

static JSValue js_CheckCollisionSpheres(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_center1 = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_center1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 center1 = *ptr_center1;
    double double_radius1;
    int err_radius1 = JS_ToFloat64(ctx, &double_radius1, argv[1]);
    if(err_radius1<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float radius1 = (float)double_radius1;
    Vector3* ptr_center2 = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_center2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 center2 = *ptr_center2;
    double double_radius2;
    int err_radius2 = JS_ToFloat64(ctx, &double_radius2, argv[3]);
    if(err_radius2<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float radius2 = (float)double_radius2;
    bool returnVal = CheckCollisionSpheres(center1, radius1, center2, radius2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_CheckCollisionBoxes(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    BoundingBox* ptr_box1 = (BoundingBox*)JS_GetOpaque(argv[0], js_BoundingBox_class_id);
    if(ptr_box1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    BoundingBox box1 = *ptr_box1;
    BoundingBox* ptr_box2 = (BoundingBox*)JS_GetOpaque(argv[1], js_BoundingBox_class_id);
    if(ptr_box2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    BoundingBox box2 = *ptr_box2;
    bool returnVal = CheckCollisionBoxes(box1, box2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_CheckCollisionBoxSphere(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    BoundingBox* ptr_box = (BoundingBox*)JS_GetOpaque(argv[0], js_BoundingBox_class_id);
    if(ptr_box == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    BoundingBox box = *ptr_box;
    Vector3* ptr_center = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 center = *ptr_center;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    bool returnVal = CheckCollisionBoxSphere(box, center, radius);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_GetRayCollisionSphere(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ptr_ray = (Ray*)JS_GetOpaque(argv[0], js_Ray_class_id);
    if(ptr_ray == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Ray ray = *ptr_ray;
    Vector3* ptr_center = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_center == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 center = *ptr_center;
    double double_radius;
    int err_radius = JS_ToFloat64(ctx, &double_radius, argv[2]);
    if(err_radius<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float radius = (float)double_radius;
    RayCollision returnVal = GetRayCollisionSphere(ray, center, radius);
    RayCollision* ptr_ret = (RayCollision*)js_malloc(ctx, sizeof(RayCollision));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetRayCollisionBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ptr_ray = (Ray*)JS_GetOpaque(argv[0], js_Ray_class_id);
    if(ptr_ray == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Ray ray = *ptr_ray;
    BoundingBox* ptr_box = (BoundingBox*)JS_GetOpaque(argv[1], js_BoundingBox_class_id);
    if(ptr_box == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    BoundingBox box = *ptr_box;
    RayCollision returnVal = GetRayCollisionBox(ray, box);
    RayCollision* ptr_ret = (RayCollision*)js_malloc(ctx, sizeof(RayCollision));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetRayCollisionMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ptr_ray = (Ray*)JS_GetOpaque(argv[0], js_Ray_class_id);
    if(ptr_ray == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Ray ray = *ptr_ray;
    Mesh* ptr_mesh = (Mesh*)JS_GetOpaque(argv[1], js_Mesh_class_id);
    if(ptr_mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Mesh mesh = *ptr_mesh;
    Matrix* ptr_transform = (Matrix*)JS_GetOpaque(argv[2], js_Matrix_class_id);
    if(ptr_transform == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix transform = *ptr_transform;
    RayCollision returnVal = GetRayCollisionMesh(ray, mesh, transform);
    RayCollision* ptr_ret = (RayCollision*)js_malloc(ctx, sizeof(RayCollision));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetRayCollisionTriangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ptr_ray = (Ray*)JS_GetOpaque(argv[0], js_Ray_class_id);
    if(ptr_ray == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Ray ray = *ptr_ray;
    Vector3* ptr_p1 = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 p1 = *ptr_p1;
    Vector3* ptr_p2 = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_p2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 p2 = *ptr_p2;
    Vector3* ptr_p3 = (Vector3*)JS_GetOpaque(argv[3], js_Vector3_class_id);
    if(ptr_p3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 p3 = *ptr_p3;
    RayCollision returnVal = GetRayCollisionTriangle(ray, p1, p2, p3);
    RayCollision* ptr_ret = (RayCollision*)js_malloc(ctx, sizeof(RayCollision));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GetRayCollisionQuad(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ptr_ray = (Ray*)JS_GetOpaque(argv[0], js_Ray_class_id);
    if(ptr_ray == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Ray ray = *ptr_ray;
    Vector3* ptr_p1 = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_p1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 p1 = *ptr_p1;
    Vector3* ptr_p2 = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_p2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 p2 = *ptr_p2;
    Vector3* ptr_p3 = (Vector3*)JS_GetOpaque(argv[3], js_Vector3_class_id);
    if(ptr_p3 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 p3 = *ptr_p3;
    Vector3* ptr_p4 = (Vector3*)JS_GetOpaque(argv[4], js_Vector3_class_id);
    if(ptr_p4 == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 p4 = *ptr_p4;
    RayCollision returnVal = GetRayCollisionQuad(ray, p1, p2, p3, p4);
    RayCollision* ptr_ret = (RayCollision*)js_malloc(ctx, sizeof(RayCollision));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_InitAudioDevice(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    InitAudioDevice();
    return JS_UNDEFINED;
}

static JSValue js_CloseAudioDevice(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    CloseAudioDevice();
    return JS_UNDEFINED;
}

static JSValue js_IsAudioDeviceReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsAudioDeviceReady();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_SetMasterVolume(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_volume;
    int err_volume = JS_ToFloat64(ctx, &double_volume, argv[0]);
    if(err_volume<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float volume = (float)double_volume;
    SetMasterVolume(volume);
    return JS_UNDEFINED;
}

static JSValue js_GetMasterVolume(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetMasterVolume();
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_LoadWave(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Wave returnVal = LoadWave((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    Wave* ptr_ret = (Wave*)js_malloc(ctx, sizeof(Wave));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Wave_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadWaveFromMemory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * fileType;
    int64_t size_fileType;
    if(JS_IsString(argv[0]) == 1) {
        fileType = (char *)JS_ToCStringLen(ctx, &size_fileType, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, fileType);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_fileType = JS_DupValue(ctx,argv[0]);
        size_t size_fileType;
        fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, da_fileType);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[0]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileType;
            size_t size_fileType;
            JSValue da_fileType = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileType,&size_fileType,NULL);
            fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, da_fileType);
            fileType+=offset_fileType;
            size_fileType-=offset_fileType;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileType);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    unsigned char * fileData;
    int64_t size_fileData;
    if(JS_IsArray(argv[1]) == 1) {
        if(JS_GetLength(ctx,argv[1],&size_fileData)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        fileData = (unsigned char *)js_malloc(ctx, size_fileData * sizeof(unsigned char));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, fileData);
        for(int i0=0; i0 < size_fileData; i0++){
            JSValue js_fileData = JS_GetPropertyUint32(ctx,argv[1],i0);
            uint32_t long_fileDatai0;
            int err_fileDatai0 = JS_ToUint32(ctx, &long_fileDatai0, js_fileData);
            if(err_fileDatai0<0) {
                JS_ThrowTypeError(ctx, "js_fileData is not numeric");
                return JS_EXCEPTION;
            }
            fileData[i0] = (unsigned char)long_fileDatai0;
            JS_FreeValue(ctx, js_fileData);
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_fileData = JS_DupValue(ctx,argv[1]);
        size_t size_fileData;
        fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, da_fileData);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileData);
    }
    else {
        JSClassID classid_fileData = JS_GetClassID(argv[1]);
        if(classid_fileData==JS_CLASS_UINT8_ARRAY || classid_fileData==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_fileData;
            size_t size_fileData;
            JSValue da_fileData = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileData,&size_fileData,NULL);
            fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, da_fileData);
            fileData+=offset_fileData;
            size_fileData-=offset_fileData;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileData);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type unsigned char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_dataSize;
    int err_dataSize = JS_ToInt32(ctx, &long_dataSize, argv[2]);
    if(err_dataSize<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int dataSize = (int)long_dataSize;
    Wave returnVal = LoadWaveFromMemory((const char *)fileType, (const unsigned char *)fileData, dataSize);
    memoryClear(ctx, memoryHead);
    Wave* ptr_ret = (Wave*)js_malloc(ctx, sizeof(Wave));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Wave_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_IsWaveValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* ptr_wave = (Wave*)JS_GetOpaque(argv[0], js_Wave_class_id);
    if(ptr_wave == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Wave wave = *ptr_wave;
    bool returnVal = IsWaveValid(wave);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_LoadSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Sound returnVal = LoadSound((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    Sound* ptr_ret = (Sound*)js_malloc(ctx, sizeof(Sound));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Sound_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadSoundFromWave(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* ptr_wave = (Wave*)JS_GetOpaque(argv[0], js_Wave_class_id);
    if(ptr_wave == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Wave wave = *ptr_wave;
    Sound returnVal = LoadSoundFromWave(wave);
    Sound* ptr_ret = (Sound*)js_malloc(ctx, sizeof(Sound));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Sound_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadSoundAlias(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_source = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_source == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound source = *ptr_source;
    Sound returnVal = LoadSoundAlias(source);
    Sound* ptr_ret = (Sound*)js_malloc(ctx, sizeof(Sound));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Sound_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_IsSoundValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_sound = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_sound == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound sound = *ptr_sound;
    bool returnVal = IsSoundValid(sound);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_UpdateSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_sound = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_sound == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound sound = *ptr_sound;
    void * data;
    JSValue da_data;
    int64_t size_data;
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_data = JS_DupValue(ctx,argv[1]);
        size_t size_data;
        data = (void *)JS_GetArrayBuffer(ctx, &size_data, da_data);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[1] does not match type void *");
        return JS_EXCEPTION;
    }
    int32_t long_sampleCount;
    int err_sampleCount = JS_ToInt32(ctx, &long_sampleCount, argv[2]);
    if(err_sampleCount<0) {
        if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_data);
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int sampleCount = (int)long_sampleCount;
    UpdateSound(sound, (const void *)data, sampleCount);
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_data);
    }
    return JS_UNDEFINED;
}

static JSValue js_UnloadWave(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* ptr_wave = (Wave*)JS_GetOpaque(argv[0], js_Wave_class_id);
    if(ptr_wave == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Wave wave = *ptr_wave;
    UnloadWave(wave);
    return JS_UNDEFINED;
}

static JSValue js_UnloadSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_sound = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_sound == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound sound = *ptr_sound;
    UnloadSound(sound);
    return JS_UNDEFINED;
}

static JSValue js_UnloadSoundAlias(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_alias = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_alias == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound alias = *ptr_alias;
    UnloadSoundAlias(alias);
    return JS_UNDEFINED;
}

static JSValue js_ExportWave(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* ptr_wave = (Wave*)JS_GetOpaque(argv[0], js_Wave_class_id);
    if(ptr_wave == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Wave wave = *ptr_wave;
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[1]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[1]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ExportWave(wave, (const char *)fileName);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_PlaySound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_sound = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_sound == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound sound = *ptr_sound;
    PlaySound(sound);
    return JS_UNDEFINED;
}

static JSValue js_StopSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_sound = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_sound == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound sound = *ptr_sound;
    StopSound(sound);
    return JS_UNDEFINED;
}

static JSValue js_PauseSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_sound = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_sound == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound sound = *ptr_sound;
    PauseSound(sound);
    return JS_UNDEFINED;
}

static JSValue js_ResumeSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_sound = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_sound == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound sound = *ptr_sound;
    ResumeSound(sound);
    return JS_UNDEFINED;
}

static JSValue js_IsSoundPlaying(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_sound = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_sound == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound sound = *ptr_sound;
    bool returnVal = IsSoundPlaying(sound);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_SetSoundVolume(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_sound = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_sound == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound sound = *ptr_sound;
    double double_volume;
    int err_volume = JS_ToFloat64(ctx, &double_volume, argv[1]);
    if(err_volume<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float volume = (float)double_volume;
    SetSoundVolume(sound, volume);
    return JS_UNDEFINED;
}

static JSValue js_SetSoundPitch(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_sound = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_sound == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound sound = *ptr_sound;
    double double_pitch;
    int err_pitch = JS_ToFloat64(ctx, &double_pitch, argv[1]);
    if(err_pitch<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float pitch = (float)double_pitch;
    SetSoundPitch(sound, pitch);
    return JS_UNDEFINED;
}

static JSValue js_SetSoundPan(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* ptr_sound = (Sound*)JS_GetOpaque(argv[0], js_Sound_class_id);
    if(ptr_sound == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Sound sound = *ptr_sound;
    double double_pan;
    int err_pan = JS_ToFloat64(ctx, &double_pan, argv[1]);
    if(err_pan<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float pan = (float)double_pan;
    SetSoundPan(sound, pan);
    return JS_UNDEFINED;
}

static JSValue js_WaveCopy(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* ptr_wave = (Wave*)JS_GetOpaque(argv[0], js_Wave_class_id);
    if(ptr_wave == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Wave wave = *ptr_wave;
    Wave returnVal = WaveCopy(wave);
    Wave* ptr_ret = (Wave*)js_malloc(ctx, sizeof(Wave));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Wave_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_WaveCrop(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave * wave = (Wave *)JS_GetOpaque(argv[0], js_Wave_class_id);
    if(wave == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Wave");
        return JS_EXCEPTION;
    }
    int32_t long_initFrame;
    int err_initFrame = JS_ToInt32(ctx, &long_initFrame, argv[1]);
    if(err_initFrame<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int initFrame = (int)long_initFrame;
    int32_t long_finalFrame;
    int err_finalFrame = JS_ToInt32(ctx, &long_finalFrame, argv[2]);
    if(err_finalFrame<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int finalFrame = (int)long_finalFrame;
    WaveCrop(wave, initFrame, finalFrame);
    return JS_UNDEFINED;
}

static JSValue js_WaveFormat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave * wave = (Wave *)JS_GetOpaque(argv[0], js_Wave_class_id);
    if(wave == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Wave");
        return JS_EXCEPTION;
    }
    int32_t long_sampleRate;
    int err_sampleRate = JS_ToInt32(ctx, &long_sampleRate, argv[1]);
    if(err_sampleRate<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int sampleRate = (int)long_sampleRate;
    int32_t long_sampleSize;
    int err_sampleSize = JS_ToInt32(ctx, &long_sampleSize, argv[2]);
    if(err_sampleSize<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int sampleSize = (int)long_sampleSize;
    int32_t long_channels;
    int err_channels = JS_ToInt32(ctx, &long_channels, argv[3]);
    if(err_channels<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int channels = (int)long_channels;
    WaveFormat(wave, sampleRate, sampleSize, channels);
    return JS_UNDEFINED;
}

static JSValue js_LoadWaveSamples(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* ptr_wave = (Wave*)JS_GetOpaque(argv[0], js_Wave_class_id);
    if(ptr_wave == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Wave wave = *ptr_wave;
    float * returnVal = LoadWaveSamples(wave);
    JSValue ret;
    ret = JS_NewArray(ctx);
    for(int i0=0; i0 < wave.frameCount*wave.channels; i0++){
        JSValue js_ret = JS_NewFloat64(ctx, (double)returnVal[i0]);
        JS_DefinePropertyValueUint32(ctx,ret,i0,js_ret,JS_PROP_C_W_E);
    }
    UnloadWaveSamples(returnVal);
    return ret;
}

static JSValue js_UnloadWaveSamples(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float * samples;
    JSValue da_samples;
    int64_t size_samples;
    if(JS_IsArray(argv[0]) == 1) {
        if(JS_GetLength(ctx,argv[0],&size_samples)==-1) {
            return JS_EXCEPTION;
        }
        samples = (float *)js_malloc(ctx, size_samples * sizeof(float));
        for(int i0=0; i0 < size_samples; i0++){
            JSValue js_samples = JS_GetPropertyUint32(ctx,argv[0],i0);
            double double_samplesi0;
            int err_samplesi0 = JS_ToFloat64(ctx, &double_samplesi0, js_samples);
            if(err_samplesi0<0) {
                JS_ThrowTypeError(ctx, "js_samples is not numeric");
                return JS_EXCEPTION;
            }
            samples[i0] = (float)double_samplesi0;
            JS_FreeValue(ctx, js_samples);
        }
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_samples = JS_DupValue(ctx,argv[0]);
        size_t size_samples;
        samples = (float *)JS_GetArrayBuffer(ctx, &size_samples, da_samples);
    }
    else {
        JSClassID classid_samples = JS_GetClassID(argv[0]);
        if(classid_samples==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_samples;
            size_t size_samples;
            da_samples = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_samples,&size_samples,NULL);
            samples = (float *)JS_GetArrayBuffer(ctx, &size_samples, da_samples);
            samples+=offset_samples;
            size_samples-=offset_samples;
        }
        else {
            double double_js_samples;
            int err_js_samples = JS_ToFloat64(ctx, &double_js_samples, argv[0]);
            if(err_js_samples<0) {
                JS_ThrowTypeError(ctx, "argv[0] is not numeric");
                return JS_EXCEPTION;
            }
            float js_samples = (float)double_js_samples;
            samples = &js_samples;
        }
    }
    UnloadWaveSamples(samples);
    if(JS_IsArray(argv[0]) == 1) {
        JSValue js_argv0 = JS_NewFloat64(ctx, (double)samples[0]);
        JS_DefinePropertyValueUint32(ctx,argv[0],0,js_argv0,JS_PROP_C_W_E);
    }
    return JS_UNDEFINED;
}

static JSValue js_LoadMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        da_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            da_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, da_fileName);
            fileName+=offset_fileName;
            size_fileName-=offset_fileName;
        }
        else {
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    Music returnVal = LoadMusicStream((const char *)fileName);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_fileName);
        }
    }
    Music* ptr_ret = (Music*)js_malloc(ctx, sizeof(Music));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Music_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadMusicStreamFromMemory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    char * fileType;
    int64_t size_fileType;
    if(JS_IsString(argv[0]) == 1) {
        fileType = (char *)JS_ToCStringLen(ctx, &size_fileType, argv[0]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, fileType);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JSValue da_fileType = JS_DupValue(ctx,argv[0]);
        size_t size_fileType;
        fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, da_fileType);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[0]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileType;
            size_t size_fileType;
            JSValue da_fileType = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileType,&size_fileType,NULL);
            fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, da_fileType);
            fileType+=offset_fileType;
            size_fileType-=offset_fileType;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_fileType);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    unsigned char * data;
    int64_t size_data;
    if(JS_IsArray(argv[1]) == 1) {
        if(JS_GetLength(ctx,argv[1],&size_data)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        data = (unsigned char *)js_malloc(ctx, size_data * sizeof(unsigned char));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, data);
        for(int i0=0; i0 < size_data; i0++){
            JSValue js_data = JS_GetPropertyUint32(ctx,argv[1],i0);
            uint32_t long_datai0;
            int err_datai0 = JS_ToUint32(ctx, &long_datai0, js_data);
            if(err_datai0<0) {
                JS_ThrowTypeError(ctx, "js_data is not numeric");
                return JS_EXCEPTION;
            }
            data[i0] = (unsigned char)long_datai0;
            JS_FreeValue(ctx, js_data);
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_data = JS_DupValue(ctx,argv[1]);
        size_t size_data;
        data = (unsigned char *)JS_GetArrayBuffer(ctx, &size_data, da_data);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_data);
    }
    else {
        JSClassID classid_data = JS_GetClassID(argv[1]);
        if(classid_data==JS_CLASS_UINT8_ARRAY || classid_data==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_data;
            size_t size_data;
            JSValue da_data = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_data,&size_data,NULL);
            data = (unsigned char *)JS_GetArrayBuffer(ctx, &size_data, da_data);
            data+=offset_data;
            size_data-=offset_data;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_data);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type unsigned char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_dataSize;
    int err_dataSize = JS_ToInt32(ctx, &long_dataSize, argv[2]);
    if(err_dataSize<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int dataSize = (int)long_dataSize;
    Music returnVal = LoadMusicStreamFromMemory((const char *)fileType, (const unsigned char *)data, dataSize);
    memoryClear(ctx, memoryHead);
    Music* ptr_ret = (Music*)js_malloc(ctx, sizeof(Music));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Music_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_IsMusicValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    bool returnVal = IsMusicValid(music);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_UnloadMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    UnloadMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_PlayMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    PlayMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_IsMusicStreamPlaying(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    bool returnVal = IsMusicStreamPlaying(music);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_UpdateMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    UpdateMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_StopMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    StopMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_PauseMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    PauseMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_ResumeMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    ResumeMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_SeekMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    double double_position;
    int err_position = JS_ToFloat64(ctx, &double_position, argv[1]);
    if(err_position<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float position = (float)double_position;
    SeekMusicStream(music, position);
    return JS_UNDEFINED;
}

static JSValue js_SetMusicVolume(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    double double_volume;
    int err_volume = JS_ToFloat64(ctx, &double_volume, argv[1]);
    if(err_volume<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float volume = (float)double_volume;
    SetMusicVolume(music, volume);
    return JS_UNDEFINED;
}

static JSValue js_SetMusicPitch(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    double double_pitch;
    int err_pitch = JS_ToFloat64(ctx, &double_pitch, argv[1]);
    if(err_pitch<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float pitch = (float)double_pitch;
    SetMusicPitch(music, pitch);
    return JS_UNDEFINED;
}

static JSValue js_SetMusicPan(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    double double_pan;
    int err_pan = JS_ToFloat64(ctx, &double_pan, argv[1]);
    if(err_pan<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float pan = (float)double_pan;
    SetMusicPan(music, pan);
    return JS_UNDEFINED;
}

static JSValue js_GetMusicTimeLength(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    float returnVal = GetMusicTimeLength(music);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_GetMusicTimePlayed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* ptr_music = (Music*)JS_GetOpaque(argv[0], js_Music_class_id);
    if(ptr_music == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Music music = *ptr_music;
    float returnVal = GetMusicTimePlayed(music);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_LoadAudioStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    uint32_t long_sampleRate;
    int err_sampleRate = JS_ToUint32(ctx, &long_sampleRate, argv[0]);
    if(err_sampleRate<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int sampleRate = (unsigned int)long_sampleRate;
    uint32_t long_sampleSize;
    int err_sampleSize = JS_ToUint32(ctx, &long_sampleSize, argv[1]);
    if(err_sampleSize<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int sampleSize = (unsigned int)long_sampleSize;
    uint32_t long_channels;
    int err_channels = JS_ToUint32(ctx, &long_channels, argv[2]);
    if(err_channels<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    unsigned int channels = (unsigned int)long_channels;
    AudioStream returnVal = LoadAudioStream(sampleRate, sampleSize, channels);
    AudioStream* ptr_ret = (AudioStream*)js_malloc(ctx, sizeof(AudioStream));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_AudioStream_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_IsAudioStreamValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    bool returnVal = IsAudioStreamValid(stream);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_UnloadAudioStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    UnloadAudioStream(stream);
    return JS_UNDEFINED;
}

static JSValue js_UpdateAudioStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    void * data;
    JSValue da_data;
    int64_t size_data;
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        da_data = JS_DupValue(ctx,argv[1]);
        size_t size_data;
        data = (void *)JS_GetArrayBuffer(ctx, &size_data, da_data);
    }
    else {
        JS_ThrowTypeError(ctx, "argv[1] does not match type void *");
        return JS_EXCEPTION;
    }
    int32_t long_frameCount;
    int err_frameCount = JS_ToInt32(ctx, &long_frameCount, argv[2]);
    if(err_frameCount<0) {
        if(JS_IsArrayBuffer(argv[1]) == 1) {
            JS_FreeValue(ctx, da_data);
        }
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int frameCount = (int)long_frameCount;
    UpdateAudioStream(stream, (const void *)data, frameCount);
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_data);
    }
    return JS_UNDEFINED;
}

static JSValue js_IsAudioStreamProcessed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    bool returnVal = IsAudioStreamProcessed(stream);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_PlayAudioStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    PlayAudioStream(stream);
    return JS_UNDEFINED;
}

static JSValue js_PauseAudioStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    PauseAudioStream(stream);
    return JS_UNDEFINED;
}

static JSValue js_ResumeAudioStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    ResumeAudioStream(stream);
    return JS_UNDEFINED;
}

static JSValue js_IsAudioStreamPlaying(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    bool returnVal = IsAudioStreamPlaying(stream);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_StopAudioStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    StopAudioStream(stream);
    return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamVolume(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    double double_volume;
    int err_volume = JS_ToFloat64(ctx, &double_volume, argv[1]);
    if(err_volume<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float volume = (float)double_volume;
    SetAudioStreamVolume(stream, volume);
    return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamPitch(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    double double_pitch;
    int err_pitch = JS_ToFloat64(ctx, &double_pitch, argv[1]);
    if(err_pitch<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float pitch = (float)double_pitch;
    SetAudioStreamPitch(stream, pitch);
    return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamPan(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AudioStream* ptr_stream = (AudioStream*)JS_GetOpaque(argv[0], js_AudioStream_class_id);
    if(ptr_stream == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    AudioStream stream = *ptr_stream;
    double double_pan;
    int err_pan = JS_ToFloat64(ctx, &double_pan, argv[1]);
    if(err_pan<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float pan = (float)double_pan;
    SetAudioStreamPan(stream, pan);
    return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamBufferSizeDefault(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_size;
    int err_size = JS_ToInt32(ctx, &long_size, argv[0]);
    if(err_size<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int size = (int)long_size;
    SetAudioStreamBufferSizeDefault(size);
    return JS_UNDEFINED;
}

static JSValue js_AttachAudioMixedProcessor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    trampolineContext ctx_processor;
    ctx_processor.ctx = ctx;
    ctx_processor.func_obj = argv[0];
    void * processor = AudioMixedProcessor_processor_c;
    if(argc==0 || (JS_IsString(argv[0]) == 0 && JS_IsNumber(argv[0]) == 0)) {
        JS_ThrowTypeError(ctx, "argv[0] must be string or number");
        return JS_EXCEPTION;
    }
    if(AudioMixedProcessor_processor_size==0) {
        JSRuntime* rt = JS_NewRuntime3();
        if(!rt) {
            return JS_EXCEPTION;
        }
        JS_DupContext(ctx);
        JS_SetMaxStackSize(rt, 0);
        js_std_init_handlers(rt);
        AudioMixedProcessor_processor_ctx = JS_NewCustomContext(rt);
        AudioMixedProcessor_processor_arr = js_malloc(ctx, sizeof(trampolineContext));
    }
    else {
        AudioMixedProcessor_processor_arr = js_realloc(ctx, AudioMixedProcessor_processor_arr, sizeof(trampolineContext) * AudioMixedProcessor_processor_size);
    }
    JS_DupValue(ctx, argv[0]);
    ctx_processor.thread_id = js_copyWorker(ctx, AudioMixedProcessor_processor_ctx);
    AudioMixedProcessor_processor_arr[AudioMixedProcessor_processor_size] = ctx_processor;
    AudioMixedProcessor_processor_size++;
    if(AudioMixedProcessor_processor_size>1) {
        return JS_UNDEFINED;
    }
    AttachAudioMixedProcessor(processor);
    return JS_UNDEFINED;
}

static JSValue js_DetachAudioMixedProcessor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int processor_pos;
    void * processor = AudioMixedProcessor_processor_c;
    void * processor_ptr = argv[0].u.ptr;
    for(int i0=0; i0 < AudioMixedProcessor_processor_size; i0++){
        if(AudioMixedProcessor_processor_arr[i0].func_obj.u.ptr == processor_ptr) {
            JS_FreeValue(ctx, AudioMixedProcessor_processor_arr[i0].func_obj);
            JS_FreeValue(AudioMixedProcessor_processor_arr[i0].ctx, AudioMixedProcessor_processor_arr[i0].func_obj);
            JS_FreeValue(AudioMixedProcessor_processor_arr[i0].ctx, AudioMixedProcessor_processor_arr[i0].thread_id);
            JS_FreeContext(AudioMixedProcessor_processor_arr[i0].ctx);
            for(; i0 < AudioMixedProcessor_processor_size-1; i0++){
                AudioMixedProcessor_processor_arr[i0]=AudioMixedProcessor_processor_arr[i0+1];
            }
            AudioMixedProcessor_processor_size--;
            AudioMixedProcessor_processor_arr = js_realloc(ctx, AudioMixedProcessor_processor_arr, sizeof(void *) * AudioMixedProcessor_processor_size);
            break;
        }
    }
    if(AudioMixedProcessor_processor_size!=0) {
        return JS_UNDEFINED;
    }
    JSRuntime* rt = JS_GetRuntime(AudioMixedProcessor_processor_ctx);
    JS_FreeContext(AudioMixedProcessor_processor_ctx);
    JS_FreeContext(ctx);
    js_std_free_handlers(rt);
    JS_FreeRuntime(rt);
    DetachAudioMixedProcessor(processor);
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_js_raylib_funcs[] = {
    JS_CFUNC_DEF("InitWindow",3,js_InitWindow),
    JS_CFUNC_DEF("CloseWindow",0,js_CloseWindow),
    JS_CFUNC_DEF("WindowShouldClose",0,js_WindowShouldClose),
    JS_CFUNC_DEF("IsWindowReady",0,js_IsWindowReady),
    JS_CFUNC_DEF("IsWindowFullscreen",0,js_IsWindowFullscreen),
    JS_CFUNC_DEF("IsWindowHidden",0,js_IsWindowHidden),
    JS_CFUNC_DEF("IsWindowMinimized",0,js_IsWindowMinimized),
    JS_CFUNC_DEF("IsWindowMaximized",0,js_IsWindowMaximized),
    JS_CFUNC_DEF("IsWindowFocused",0,js_IsWindowFocused),
    JS_CFUNC_DEF("IsWindowResized",0,js_IsWindowResized),
    JS_CFUNC_DEF("IsWindowState",1,js_IsWindowState),
    JS_CFUNC_DEF("SetWindowState",1,js_SetWindowState),
    JS_CFUNC_DEF("ClearWindowState",1,js_ClearWindowState),
    JS_CFUNC_DEF("ToggleFullscreen",0,js_ToggleFullscreen),
    JS_CFUNC_DEF("ToggleBorderlessWindowed",0,js_ToggleBorderlessWindowed),
    JS_CFUNC_DEF("MaximizeWindow",0,js_MaximizeWindow),
    JS_CFUNC_DEF("MinimizeWindow",0,js_MinimizeWindow),
    JS_CFUNC_DEF("RestoreWindow",0,js_RestoreWindow),
    JS_CFUNC_DEF("SetWindowIcon",1,js_SetWindowIcon),
    JS_CFUNC_DEF("SetWindowTitle",1,js_SetWindowTitle),
    JS_CFUNC_DEF("SetWindowPosition",2,js_SetWindowPosition),
    JS_CFUNC_DEF("SetWindowMonitor",1,js_SetWindowMonitor),
    JS_CFUNC_DEF("SetWindowMinSize",2,js_SetWindowMinSize),
    JS_CFUNC_DEF("SetWindowMaxSize",2,js_SetWindowMaxSize),
    JS_CFUNC_DEF("SetWindowSize",2,js_SetWindowSize),
    JS_CFUNC_DEF("SetWindowOpacity",1,js_SetWindowOpacity),
    JS_CFUNC_DEF("SetWindowFocused",0,js_SetWindowFocused),
    JS_CFUNC_DEF("GetScreenWidth",0,js_GetScreenWidth),
    JS_CFUNC_DEF("GetScreenHeight",0,js_GetScreenHeight),
    JS_CFUNC_DEF("GetRenderWidth",0,js_GetRenderWidth),
    JS_CFUNC_DEF("GetRenderHeight",0,js_GetRenderHeight),
    JS_CFUNC_DEF("GetMonitorCount",0,js_GetMonitorCount),
    JS_CFUNC_DEF("GetCurrentMonitor",0,js_GetCurrentMonitor),
    JS_CFUNC_DEF("GetMonitorPosition",1,js_GetMonitorPosition),
    JS_CFUNC_DEF("GetMonitorWidth",1,js_GetMonitorWidth),
    JS_CFUNC_DEF("GetMonitorHeight",1,js_GetMonitorHeight),
    JS_CFUNC_DEF("GetMonitorPhysicalWidth",1,js_GetMonitorPhysicalWidth),
    JS_CFUNC_DEF("GetMonitorPhysicalHeight",1,js_GetMonitorPhysicalHeight),
    JS_CFUNC_DEF("GetMonitorRefreshRate",1,js_GetMonitorRefreshRate),
    JS_CFUNC_DEF("GetWindowPosition",0,js_GetWindowPosition),
    JS_CFUNC_DEF("GetWindowScaleDPI",0,js_GetWindowScaleDPI),
    JS_CFUNC_DEF("GetMonitorName",1,js_GetMonitorName),
    JS_CFUNC_DEF("SetClipboardText",1,js_SetClipboardText),
    JS_CFUNC_DEF("GetClipboardText",0,js_GetClipboardText),
    JS_CFUNC_DEF("GetClipboardImage",0,js_GetClipboardImage),
    JS_CFUNC_DEF("EnableEventWaiting",0,js_EnableEventWaiting),
    JS_CFUNC_DEF("DisableEventWaiting",0,js_DisableEventWaiting),
    JS_CFUNC_DEF("ShowCursor",0,js_ShowCursor),
    JS_CFUNC_DEF("HideCursor",0,js_HideCursor),
    JS_CFUNC_DEF("IsCursorHidden",0,js_IsCursorHidden),
    JS_CFUNC_DEF("EnableCursor",0,js_EnableCursor),
    JS_CFUNC_DEF("DisableCursor",0,js_DisableCursor),
    JS_CFUNC_DEF("IsCursorOnScreen",0,js_IsCursorOnScreen),
    JS_CFUNC_DEF("ClearBackground",1,js_ClearBackground),
    JS_CFUNC_DEF("BeginDrawing",0,js_BeginDrawing),
    JS_CFUNC_DEF("EndDrawing",0,js_EndDrawing),
    JS_CFUNC_DEF("BeginMode2D",1,js_BeginMode2D),
    JS_CFUNC_DEF("EndMode2D",0,js_EndMode2D),
    JS_CFUNC_DEF("BeginMode3D",1,js_BeginMode3D),
    JS_CFUNC_DEF("EndMode3D",0,js_EndMode3D),
    JS_CFUNC_DEF("BeginTextureMode",1,js_BeginTextureMode),
    JS_CFUNC_DEF("EndTextureMode",0,js_EndTextureMode),
    JS_CFUNC_DEF("BeginShaderMode",1,js_BeginShaderMode),
    JS_CFUNC_DEF("EndShaderMode",0,js_EndShaderMode),
    JS_CFUNC_DEF("BeginBlendMode",1,js_BeginBlendMode),
    JS_CFUNC_DEF("EndBlendMode",0,js_EndBlendMode),
    JS_CFUNC_DEF("BeginScissorMode",4,js_BeginScissorMode),
    JS_CFUNC_DEF("EndScissorMode",0,js_EndScissorMode),
    JS_CFUNC_DEF("BeginVrStereoMode",1,js_BeginVrStereoMode),
    JS_CFUNC_DEF("EndVrStereoMode",0,js_EndVrStereoMode),
    JS_CFUNC_DEF("LoadVrStereoConfig",1,js_LoadVrStereoConfig),
    JS_CFUNC_DEF("UnloadVrStereoConfig",1,js_UnloadVrStereoConfig),
    JS_CFUNC_DEF("LoadShader",2,js_LoadShader),
    JS_CFUNC_DEF("LoadShaderFromMemory",2,js_LoadShaderFromMemory),
    JS_CFUNC_DEF("IsShaderValid",1,js_IsShaderValid),
    JS_CFUNC_DEF("GetShaderLocation",2,js_GetShaderLocation),
    JS_CFUNC_DEF("GetShaderLocationAttrib",2,js_GetShaderLocationAttrib),
    JS_CFUNC_DEF("SetShaderValue",4,js_SetShaderValue),
    JS_CFUNC_DEF("SetShaderValueV",5,js_SetShaderValueV),
    JS_CFUNC_DEF("SetShaderValueMatrix",3,js_SetShaderValueMatrix),
    JS_CFUNC_DEF("SetShaderValueTexture",3,js_SetShaderValueTexture),
    JS_CFUNC_DEF("UnloadShader",1,js_UnloadShader),
    JS_CFUNC_DEF("GetScreenToWorldRay",2,js_GetScreenToWorldRay),
    JS_CFUNC_DEF("GetScreenToWorldRayEx",4,js_GetScreenToWorldRayEx),
    JS_CFUNC_DEF("GetWorldToScreen",2,js_GetWorldToScreen),
    JS_CFUNC_DEF("GetWorldToScreenEx",4,js_GetWorldToScreenEx),
    JS_CFUNC_DEF("GetWorldToScreen2D",2,js_GetWorldToScreen2D),
    JS_CFUNC_DEF("GetScreenToWorld2D",2,js_GetScreenToWorld2D),
    JS_CFUNC_DEF("GetCameraMatrix",1,js_GetCameraMatrix),
    JS_CFUNC_DEF("GetCameraMatrix2D",1,js_GetCameraMatrix2D),
    JS_CFUNC_DEF("SetTargetFPS",1,js_SetTargetFPS),
    JS_CFUNC_DEF("GetFrameTime",0,js_GetFrameTime),
    JS_CFUNC_DEF("GetTime",0,js_GetTime),
    JS_CFUNC_DEF("GetFPS",0,js_GetFPS),
    JS_CFUNC_DEF("SetRandomSeed",1,js_SetRandomSeed),
    JS_CFUNC_DEF("GetRandomValue",2,js_GetRandomValue),
    JS_CFUNC_DEF("LoadRandomSequence",3,js_LoadRandomSequence),
    JS_CFUNC_DEF("TakeScreenshot",1,js_TakeScreenshot),
    JS_CFUNC_DEF("SetConfigFlags",1,js_SetConfigFlags),
    JS_CFUNC_DEF("OpenURL",1,js_OpenURL),
    JS_CFUNC_DEF("TraceLog",1,js_TraceLog),
    JS_CFUNC_DEF("SetTraceLogLevel",1,js_SetTraceLogLevel),
    JS_CFUNC_DEF("SetLoadFileDataCallback",1,js_SetLoadFileDataCallback),
    JS_CFUNC_DEF("SetSaveFileDataCallback",1,js_SetSaveFileDataCallback),
    JS_CFUNC_DEF("SetLoadFileTextCallback",1,js_SetLoadFileTextCallback),
    JS_CFUNC_DEF("SetSaveFileTextCallback",1,js_SetSaveFileTextCallback),
    JS_CFUNC_DEF("LoadFileData",2,js_LoadFileData),
    JS_CFUNC_DEF("SaveFileData",3,js_SaveFileData),
    JS_CFUNC_DEF("LoadFileText",1,js_LoadFileText),
    JS_CFUNC_DEF("SaveFileText",2,js_SaveFileText),
    JS_CFUNC_DEF("FileExists",1,js_FileExists),
    JS_CFUNC_DEF("DirectoryExists",1,js_DirectoryExists),
    JS_CFUNC_DEF("IsFileExtension",2,js_IsFileExtension),
    JS_CFUNC_DEF("GetFileLength",1,js_GetFileLength),
    JS_CFUNC_DEF("GetFileExtension",1,js_GetFileExtension),
    JS_CFUNC_DEF("GetFileName",1,js_GetFileName),
    JS_CFUNC_DEF("GetFileNameWithoutExt",1,js_GetFileNameWithoutExt),
    JS_CFUNC_DEF("GetDirectoryPath",1,js_GetDirectoryPath),
    JS_CFUNC_DEF("GetPrevDirectoryPath",1,js_GetPrevDirectoryPath),
    JS_CFUNC_DEF("GetWorkingDirectory",0,js_GetWorkingDirectory),
    JS_CFUNC_DEF("GetApplicationDirectory",0,js_GetApplicationDirectory),
    JS_CFUNC_DEF("MakeDirectory",1,js_MakeDirectory),
    JS_CFUNC_DEF("ChangeDirectory",1,js_ChangeDirectory),
    JS_CFUNC_DEF("IsPathFile",1,js_IsPathFile),
    JS_CFUNC_DEF("IsFileNameValid",1,js_IsFileNameValid),
    JS_CFUNC_DEF("LoadDirectoryFiles",1,js_LoadDirectoryFiles),
    JS_CFUNC_DEF("LoadDirectoryFilesEx",3,js_LoadDirectoryFilesEx),
    JS_CFUNC_DEF("IsFileDropped",0,js_IsFileDropped),
    JS_CFUNC_DEF("LoadDroppedFiles",0,js_LoadDroppedFiles),
    JS_CFUNC_DEF("GetFileModTime",1,js_GetFileModTime),
    JS_CFUNC_DEF("ComputeCRC32",2,js_ComputeCRC32),
    JS_CFUNC_DEF("ComputeMD5",2,js_ComputeMD5),
    JS_CFUNC_DEF("ComputeSHA1",2,js_ComputeSHA1),
    JS_CFUNC_DEF("LoadAutomationEventList",1,js_LoadAutomationEventList),
    JS_CFUNC_DEF("UnloadAutomationEventList",1,js_UnloadAutomationEventList),
    JS_CFUNC_DEF("ExportAutomationEventList",2,js_ExportAutomationEventList),
    JS_CFUNC_DEF("SetAutomationEventList",1,js_SetAutomationEventList),
    JS_CFUNC_DEF("SetAutomationEventBaseFrame",1,js_SetAutomationEventBaseFrame),
    JS_CFUNC_DEF("StartAutomationEventRecording",0,js_StartAutomationEventRecording),
    JS_CFUNC_DEF("StopAutomationEventRecording",0,js_StopAutomationEventRecording),
    JS_CFUNC_DEF("PlayAutomationEvent",1,js_PlayAutomationEvent),
    JS_CFUNC_DEF("IsKeyPressed",1,js_IsKeyPressed),
    JS_CFUNC_DEF("IsKeyPressedRepeat",1,js_IsKeyPressedRepeat),
    JS_CFUNC_DEF("IsKeyDown",1,js_IsKeyDown),
    JS_CFUNC_DEF("IsKeyReleased",1,js_IsKeyReleased),
    JS_CFUNC_DEF("IsKeyUp",1,js_IsKeyUp),
    JS_CFUNC_DEF("GetKeyPressed",0,js_GetKeyPressed),
    JS_CFUNC_DEF("GetCharPressed",0,js_GetCharPressed),
    JS_CFUNC_DEF("GetKeyName",1,js_GetKeyName),
    JS_CFUNC_DEF("SetExitKey",1,js_SetExitKey),
    JS_CFUNC_DEF("IsGamepadAvailable",1,js_IsGamepadAvailable),
    JS_CFUNC_DEF("GetGamepadName",1,js_GetGamepadName),
    JS_CFUNC_DEF("IsGamepadButtonPressed",2,js_IsGamepadButtonPressed),
    JS_CFUNC_DEF("IsGamepadButtonDown",2,js_IsGamepadButtonDown),
    JS_CFUNC_DEF("IsGamepadButtonReleased",2,js_IsGamepadButtonReleased),
    JS_CFUNC_DEF("IsGamepadButtonUp",2,js_IsGamepadButtonUp),
    JS_CFUNC_DEF("GetGamepadButtonPressed",0,js_GetGamepadButtonPressed),
    JS_CFUNC_DEF("GetGamepadAxisCount",1,js_GetGamepadAxisCount),
    JS_CFUNC_DEF("GetGamepadAxisMovement",2,js_GetGamepadAxisMovement),
    JS_CFUNC_DEF("SetGamepadMappings",1,js_SetGamepadMappings),
    JS_CFUNC_DEF("SetGamepadVibration",4,js_SetGamepadVibration),
    JS_CFUNC_DEF("IsMouseButtonPressed",1,js_IsMouseButtonPressed),
    JS_CFUNC_DEF("IsMouseButtonDown",1,js_IsMouseButtonDown),
    JS_CFUNC_DEF("IsMouseButtonReleased",1,js_IsMouseButtonReleased),
    JS_CFUNC_DEF("IsMouseButtonUp",1,js_IsMouseButtonUp),
    JS_CFUNC_DEF("GetMouseX",0,js_GetMouseX),
    JS_CFUNC_DEF("GetMouseY",0,js_GetMouseY),
    JS_CFUNC_DEF("GetMousePosition",0,js_GetMousePosition),
    JS_CFUNC_DEF("GetMouseDelta",0,js_GetMouseDelta),
    JS_CFUNC_DEF("SetMousePosition",2,js_SetMousePosition),
    JS_CFUNC_DEF("SetMouseOffset",2,js_SetMouseOffset),
    JS_CFUNC_DEF("SetMouseScale",2,js_SetMouseScale),
    JS_CFUNC_DEF("GetMouseWheelMove",0,js_GetMouseWheelMove),
    JS_CFUNC_DEF("GetMouseWheelMoveV",0,js_GetMouseWheelMoveV),
    JS_CFUNC_DEF("SetMouseCursor",1,js_SetMouseCursor),
    JS_CFUNC_DEF("GetTouchX",0,js_GetTouchX),
    JS_CFUNC_DEF("GetTouchY",0,js_GetTouchY),
    JS_CFUNC_DEF("GetTouchPosition",1,js_GetTouchPosition),
    JS_CFUNC_DEF("GetTouchPointId",1,js_GetTouchPointId),
    JS_CFUNC_DEF("GetTouchPointCount",0,js_GetTouchPointCount),
    JS_CFUNC_DEF("SetGesturesEnabled",1,js_SetGesturesEnabled),
    JS_CFUNC_DEF("IsGestureDetected",1,js_IsGestureDetected),
    JS_CFUNC_DEF("GetGestureDetected",0,js_GetGestureDetected),
    JS_CFUNC_DEF("GetGestureHoldDuration",0,js_GetGestureHoldDuration),
    JS_CFUNC_DEF("GetGestureDragVector",0,js_GetGestureDragVector),
    JS_CFUNC_DEF("GetGestureDragAngle",0,js_GetGestureDragAngle),
    JS_CFUNC_DEF("GetGesturePinchVector",0,js_GetGesturePinchVector),
    JS_CFUNC_DEF("GetGesturePinchAngle",0,js_GetGesturePinchAngle),
    JS_CFUNC_DEF("UpdateCamera",2,js_UpdateCamera),
    JS_CFUNC_DEF("UpdateCameraPro",4,js_UpdateCameraPro),
    JS_CFUNC_DEF("SetShapesTexture",2,js_SetShapesTexture),
    JS_CFUNC_DEF("GetShapesTexture",0,js_GetShapesTexture),
    JS_CFUNC_DEF("GetShapesTextureRectangle",0,js_GetShapesTextureRectangle),
    JS_CFUNC_DEF("DrawPixel",3,js_DrawPixel),
    JS_CFUNC_DEF("DrawPixelV",2,js_DrawPixelV),
    JS_CFUNC_DEF("DrawLine",5,js_DrawLine),
    JS_CFUNC_DEF("DrawLineV",3,js_DrawLineV),
    JS_CFUNC_DEF("DrawLineEx",4,js_DrawLineEx),
    JS_CFUNC_DEF("DrawLineBezier",4,js_DrawLineBezier),
    JS_CFUNC_DEF("DrawCircle",4,js_DrawCircle),
    JS_CFUNC_DEF("DrawCircleSector",6,js_DrawCircleSector),
    JS_CFUNC_DEF("DrawCircleSectorLines",6,js_DrawCircleSectorLines),
    JS_CFUNC_DEF("DrawCircleGradient",5,js_DrawCircleGradient),
    JS_CFUNC_DEF("DrawCircleV",3,js_DrawCircleV),
    JS_CFUNC_DEF("DrawCircleLines",4,js_DrawCircleLines),
    JS_CFUNC_DEF("DrawCircleLinesV",3,js_DrawCircleLinesV),
    JS_CFUNC_DEF("DrawEllipse",5,js_DrawEllipse),
    JS_CFUNC_DEF("DrawEllipseLines",5,js_DrawEllipseLines),
    JS_CFUNC_DEF("DrawRing",7,js_DrawRing),
    JS_CFUNC_DEF("DrawRingLines",7,js_DrawRingLines),
    JS_CFUNC_DEF("DrawRectangle",5,js_DrawRectangle),
    JS_CFUNC_DEF("DrawRectangleV",3,js_DrawRectangleV),
    JS_CFUNC_DEF("DrawRectangleRec",2,js_DrawRectangleRec),
    JS_CFUNC_DEF("DrawRectanglePro",4,js_DrawRectanglePro),
    JS_CFUNC_DEF("DrawRectangleGradientV",6,js_DrawRectangleGradientV),
    JS_CFUNC_DEF("DrawRectangleGradientH",6,js_DrawRectangleGradientH),
    JS_CFUNC_DEF("DrawRectangleGradientEx",5,js_DrawRectangleGradientEx),
    JS_CFUNC_DEF("DrawRectangleLines",5,js_DrawRectangleLines),
    JS_CFUNC_DEF("DrawRectangleLinesEx",3,js_DrawRectangleLinesEx),
    JS_CFUNC_DEF("DrawRectangleRounded",4,js_DrawRectangleRounded),
    JS_CFUNC_DEF("DrawRectangleRoundedLines",4,js_DrawRectangleRoundedLines),
    JS_CFUNC_DEF("DrawRectangleRoundedLinesEx",5,js_DrawRectangleRoundedLinesEx),
    JS_CFUNC_DEF("DrawTriangle",4,js_DrawTriangle),
    JS_CFUNC_DEF("DrawTriangleLines",4,js_DrawTriangleLines),
    JS_CFUNC_DEF("DrawPoly",5,js_DrawPoly),
    JS_CFUNC_DEF("DrawPolyLines",5,js_DrawPolyLines),
    JS_CFUNC_DEF("DrawPolyLinesEx",6,js_DrawPolyLinesEx),
    JS_CFUNC_DEF("DrawSplineLinear",4,js_DrawSplineLinear),
    JS_CFUNC_DEF("DrawSplineBasis",4,js_DrawSplineBasis),
    JS_CFUNC_DEF("DrawSplineCatmullRom",4,js_DrawSplineCatmullRom),
    JS_CFUNC_DEF("DrawSplineBezierQuadratic",4,js_DrawSplineBezierQuadratic),
    JS_CFUNC_DEF("DrawSplineBezierCubic",4,js_DrawSplineBezierCubic),
    JS_CFUNC_DEF("DrawSplineSegmentLinear",4,js_DrawSplineSegmentLinear),
    JS_CFUNC_DEF("DrawSplineSegmentBasis",6,js_DrawSplineSegmentBasis),
    JS_CFUNC_DEF("DrawSplineSegmentCatmullRom",6,js_DrawSplineSegmentCatmullRom),
    JS_CFUNC_DEF("DrawSplineSegmentBezierQuadratic",5,js_DrawSplineSegmentBezierQuadratic),
    JS_CFUNC_DEF("DrawSplineSegmentBezierCubic",6,js_DrawSplineSegmentBezierCubic),
    JS_CFUNC_DEF("GetSplinePointLinear",3,js_GetSplinePointLinear),
    JS_CFUNC_DEF("GetSplinePointBasis",5,js_GetSplinePointBasis),
    JS_CFUNC_DEF("GetSplinePointCatmullRom",5,js_GetSplinePointCatmullRom),
    JS_CFUNC_DEF("GetSplinePointBezierQuad",4,js_GetSplinePointBezierQuad),
    JS_CFUNC_DEF("GetSplinePointBezierCubic",5,js_GetSplinePointBezierCubic),
    JS_CFUNC_DEF("CheckCollisionRecs",2,js_CheckCollisionRecs),
    JS_CFUNC_DEF("CheckCollisionCircles",4,js_CheckCollisionCircles),
    JS_CFUNC_DEF("CheckCollisionCircleRec",3,js_CheckCollisionCircleRec),
    JS_CFUNC_DEF("CheckCollisionCircleLine",4,js_CheckCollisionCircleLine),
    JS_CFUNC_DEF("CheckCollisionPointRec",2,js_CheckCollisionPointRec),
    JS_CFUNC_DEF("CheckCollisionPointCircle",3,js_CheckCollisionPointCircle),
    JS_CFUNC_DEF("CheckCollisionPointTriangle",4,js_CheckCollisionPointTriangle),
    JS_CFUNC_DEF("CheckCollisionPointLine",4,js_CheckCollisionPointLine),
    JS_CFUNC_DEF("GetCollisionRec",2,js_GetCollisionRec),
    JS_CFUNC_DEF("LoadImage",1,js_LoadImage),
    JS_CFUNC_DEF("LoadImageRaw",5,js_LoadImageRaw),
    JS_CFUNC_DEF("LoadImageAnimFromMemory",4,js_LoadImageAnimFromMemory),
    JS_CFUNC_DEF("LoadImageFromMemory",3,js_LoadImageFromMemory),
    JS_CFUNC_DEF("LoadImageFromTexture",1,js_LoadImageFromTexture),
    JS_CFUNC_DEF("LoadImageFromScreen",0,js_LoadImageFromScreen),
    JS_CFUNC_DEF("IsImageValid",1,js_IsImageValid),
    JS_CFUNC_DEF("UnloadImage",1,js_UnloadImage),
    JS_CFUNC_DEF("ExportImage",2,js_ExportImage),
    JS_CFUNC_DEF("ExportImageToMemory",3,js_ExportImageToMemory),
    JS_CFUNC_DEF("GenImageColor",3,js_GenImageColor),
    JS_CFUNC_DEF("GenImageGradientLinear",5,js_GenImageGradientLinear),
    JS_CFUNC_DEF("GenImageGradientRadial",5,js_GenImageGradientRadial),
    JS_CFUNC_DEF("GenImageGradientSquare",5,js_GenImageGradientSquare),
    JS_CFUNC_DEF("GenImageChecked",6,js_GenImageChecked),
    JS_CFUNC_DEF("GenImageWhiteNoise",3,js_GenImageWhiteNoise),
    JS_CFUNC_DEF("GenImagePerlinNoise",5,js_GenImagePerlinNoise),
    JS_CFUNC_DEF("GenImageCellular",3,js_GenImageCellular),
    JS_CFUNC_DEF("GenImageText",3,js_GenImageText),
    JS_CFUNC_DEF("ImageCopy",1,js_ImageCopy),
    JS_CFUNC_DEF("ImageFromImage",2,js_ImageFromImage),
    JS_CFUNC_DEF("ImageFromChannel",2,js_ImageFromChannel),
    JS_CFUNC_DEF("ImageText",3,js_ImageText),
    JS_CFUNC_DEF("ImageTextEx",5,js_ImageTextEx),
    JS_CFUNC_DEF("ImageFormat",2,js_ImageFormat),
    JS_CFUNC_DEF("ImageToPOT",2,js_ImageToPOT),
    JS_CFUNC_DEF("ImageCrop",2,js_ImageCrop),
    JS_CFUNC_DEF("ImageAlphaCrop",2,js_ImageAlphaCrop),
    JS_CFUNC_DEF("ImageAlphaClear",3,js_ImageAlphaClear),
    JS_CFUNC_DEF("ImageAlphaMask",2,js_ImageAlphaMask),
    JS_CFUNC_DEF("ImageAlphaPremultiply",1,js_ImageAlphaPremultiply),
    JS_CFUNC_DEF("ImageBlurGaussian",2,js_ImageBlurGaussian),
    JS_CFUNC_DEF("ImageKernelConvolution",3,js_ImageKernelConvolution),
    JS_CFUNC_DEF("ImageResize",3,js_ImageResize),
    JS_CFUNC_DEF("ImageResizeNN",3,js_ImageResizeNN),
    JS_CFUNC_DEF("ImageResizeCanvas",6,js_ImageResizeCanvas),
    JS_CFUNC_DEF("ImageMipmaps",1,js_ImageMipmaps),
    JS_CFUNC_DEF("ImageDither",5,js_ImageDither),
    JS_CFUNC_DEF("ImageFlipVertical",1,js_ImageFlipVertical),
    JS_CFUNC_DEF("ImageFlipHorizontal",1,js_ImageFlipHorizontal),
    JS_CFUNC_DEF("ImageRotate",2,js_ImageRotate),
    JS_CFUNC_DEF("ImageRotateCW",1,js_ImageRotateCW),
    JS_CFUNC_DEF("ImageRotateCCW",1,js_ImageRotateCCW),
    JS_CFUNC_DEF("ImageColorTint",2,js_ImageColorTint),
    JS_CFUNC_DEF("ImageColorInvert",1,js_ImageColorInvert),
    JS_CFUNC_DEF("ImageColorGrayscale",1,js_ImageColorGrayscale),
    JS_CFUNC_DEF("ImageColorContrast",2,js_ImageColorContrast),
    JS_CFUNC_DEF("ImageColorBrightness",2,js_ImageColorBrightness),
    JS_CFUNC_DEF("ImageColorReplace",3,js_ImageColorReplace),
    JS_CFUNC_DEF("LoadImageColors",1,js_LoadImageColors),
    JS_CFUNC_DEF("GetImageAlphaBorder",2,js_GetImageAlphaBorder),
    JS_CFUNC_DEF("GetImageColor",3,js_GetImageColor),
    JS_CFUNC_DEF("ImageClearBackground",2,js_ImageClearBackground),
    JS_CFUNC_DEF("ImageDrawPixel",4,js_ImageDrawPixel),
    JS_CFUNC_DEF("ImageDrawPixelV",3,js_ImageDrawPixelV),
    JS_CFUNC_DEF("ImageDrawLine",6,js_ImageDrawLine),
    JS_CFUNC_DEF("ImageDrawLineV",4,js_ImageDrawLineV),
    JS_CFUNC_DEF("ImageDrawLineEx",5,js_ImageDrawLineEx),
    JS_CFUNC_DEF("ImageDrawCircle",5,js_ImageDrawCircle),
    JS_CFUNC_DEF("ImageDrawCircleV",4,js_ImageDrawCircleV),
    JS_CFUNC_DEF("ImageDrawCircleLines",5,js_ImageDrawCircleLines),
    JS_CFUNC_DEF("ImageDrawCircleLinesV",4,js_ImageDrawCircleLinesV),
    JS_CFUNC_DEF("ImageDrawRectangle",6,js_ImageDrawRectangle),
    JS_CFUNC_DEF("ImageDrawRectangleV",4,js_ImageDrawRectangleV),
    JS_CFUNC_DEF("ImageDrawRectangleRec",3,js_ImageDrawRectangleRec),
    JS_CFUNC_DEF("ImageDrawRectangleLines",4,js_ImageDrawRectangleLines),
    JS_CFUNC_DEF("ImageDrawTriangle",5,js_ImageDrawTriangle),
    JS_CFUNC_DEF("ImageDrawTriangleEx",7,js_ImageDrawTriangleEx),
    JS_CFUNC_DEF("ImageDrawTriangleLines",5,js_ImageDrawTriangleLines),
    JS_CFUNC_DEF("ImageDrawTriangleFan",4,js_ImageDrawTriangleFan),
    JS_CFUNC_DEF("ImageDrawTriangleStrip",4,js_ImageDrawTriangleStrip),
    JS_CFUNC_DEF("ImageDraw",5,js_ImageDraw),
    JS_CFUNC_DEF("ImageDrawText",6,js_ImageDrawText),
    JS_CFUNC_DEF("ImageDrawTextEx",7,js_ImageDrawTextEx),
    JS_CFUNC_DEF("LoadTexture",1,js_LoadTexture),
    JS_CFUNC_DEF("LoadTextureFromImage",1,js_LoadTextureFromImage),
    JS_CFUNC_DEF("LoadTextureCubemap",2,js_LoadTextureCubemap),
    JS_CFUNC_DEF("LoadRenderTexture",2,js_LoadRenderTexture),
    JS_CFUNC_DEF("IsTextureValid",1,js_IsTextureValid),
    JS_CFUNC_DEF("UnloadTexture",1,js_UnloadTexture),
    JS_CFUNC_DEF("IsRenderTextureValid",1,js_IsRenderTextureValid),
    JS_CFUNC_DEF("UnloadRenderTexture",1,js_UnloadRenderTexture),
    JS_CFUNC_DEF("UpdateTexture",2,js_UpdateTexture),
    JS_CFUNC_DEF("UpdateTextureRec",3,js_UpdateTextureRec),
    JS_CFUNC_DEF("GenTextureMipmaps",1,js_GenTextureMipmaps),
    JS_CFUNC_DEF("SetTextureFilter",2,js_SetTextureFilter),
    JS_CFUNC_DEF("SetTextureWrap",2,js_SetTextureWrap),
    JS_CFUNC_DEF("DrawTexture",4,js_DrawTexture),
    JS_CFUNC_DEF("DrawTextureV",3,js_DrawTextureV),
    JS_CFUNC_DEF("DrawTextureEx",5,js_DrawTextureEx),
    JS_CFUNC_DEF("DrawTextureRec",4,js_DrawTextureRec),
    JS_CFUNC_DEF("DrawTexturePro",6,js_DrawTexturePro),
    JS_CFUNC_DEF("DrawTextureNPatch",6,js_DrawTextureNPatch),
    JS_CFUNC_DEF("ColorIsEqual",2,js_ColorIsEqual),
    JS_CFUNC_DEF("Fade",2,js_Fade),
    JS_CFUNC_DEF("ColorToInt",1,js_ColorToInt),
    JS_CFUNC_DEF("ColorNormalize",1,js_ColorNormalize),
    JS_CFUNC_DEF("ColorFromNormalized",1,js_ColorFromNormalized),
    JS_CFUNC_DEF("ColorToHSV",1,js_ColorToHSV),
    JS_CFUNC_DEF("ColorFromHSV",3,js_ColorFromHSV),
    JS_CFUNC_DEF("ColorTint",2,js_ColorTint),
    JS_CFUNC_DEF("ColorBrightness",2,js_ColorBrightness),
    JS_CFUNC_DEF("ColorContrast",2,js_ColorContrast),
    JS_CFUNC_DEF("ColorAlpha",2,js_ColorAlpha),
    JS_CFUNC_DEF("ColorAlphaBlend",3,js_ColorAlphaBlend),
    JS_CFUNC_DEF("ColorLerp",3,js_ColorLerp),
    JS_CFUNC_DEF("GetColor",1,js_GetColor),
    JS_CFUNC_DEF("GetPixelDataSize",3,js_GetPixelDataSize),
    JS_CFUNC_DEF("GetFontDefault",0,js_GetFontDefault),
    JS_CFUNC_DEF("LoadFont",1,js_LoadFont),
    JS_CFUNC_DEF("LoadFontEx",4,js_LoadFontEx),
    JS_CFUNC_DEF("LoadFontFromImage",3,js_LoadFontFromImage),
    JS_CFUNC_DEF("IsFontValid",1,js_IsFontValid),
    JS_CFUNC_DEF("UnloadFont",1,js_UnloadFont),
    JS_CFUNC_DEF("DrawFPS",2,js_DrawFPS),
    JS_CFUNC_DEF("DrawText",5,js_DrawText),
    JS_CFUNC_DEF("DrawTextEx",6,js_DrawTextEx),
    JS_CFUNC_DEF("DrawTextPro",8,js_DrawTextPro),
    JS_CFUNC_DEF("DrawTextCodepoint",5,js_DrawTextCodepoint),
    JS_CFUNC_DEF("SetTextLineSpacing",1,js_SetTextLineSpacing),
    JS_CFUNC_DEF("MeasureText",2,js_MeasureText),
    JS_CFUNC_DEF("MeasureTextEx",4,js_MeasureTextEx),
    JS_CFUNC_DEF("GetGlyphIndex",2,js_GetGlyphIndex),
    JS_CFUNC_DEF("GetGlyphAtlasRec",2,js_GetGlyphAtlasRec),
    JS_CFUNC_DEF("TextCopy",2,js_TextCopy),
    JS_CFUNC_DEF("TextIsEqual",2,js_TextIsEqual),
    JS_CFUNC_DEF("TextLength",1,js_TextLength),
    JS_CFUNC_DEF("TextFormat",2,js_TextFormat),
    JS_CFUNC_DEF("TextSubtext",3,js_TextSubtext),
    JS_CFUNC_DEF("TextReplace",3,js_TextReplace),
    JS_CFUNC_DEF("TextInsert",3,js_TextInsert),
    JS_CFUNC_DEF("TextJoin",3,js_TextJoin),
    JS_CFUNC_DEF("TextSplit",3,js_TextSplit),
    JS_CFUNC_DEF("TextAppend",3,js_TextAppend),
    JS_CFUNC_DEF("TextFindIndex",2,js_TextFindIndex),
    JS_CFUNC_DEF("TextToUpper",1,js_TextToUpper),
    JS_CFUNC_DEF("TextToLower",1,js_TextToLower),
    JS_CFUNC_DEF("TextToPascal",1,js_TextToPascal),
    JS_CFUNC_DEF("TextToSnake",1,js_TextToSnake),
    JS_CFUNC_DEF("TextToCamel",1,js_TextToCamel),
    JS_CFUNC_DEF("TextToInteger",1,js_TextToInteger),
    JS_CFUNC_DEF("TextToFloat",1,js_TextToFloat),
    JS_CFUNC_DEF("DrawLine3D",3,js_DrawLine3D),
    JS_CFUNC_DEF("DrawPoint3D",2,js_DrawPoint3D),
    JS_CFUNC_DEF("DrawCircle3D",5,js_DrawCircle3D),
    JS_CFUNC_DEF("DrawTriangle3D",4,js_DrawTriangle3D),
    JS_CFUNC_DEF("DrawCube",5,js_DrawCube),
    JS_CFUNC_DEF("DrawCubeV",3,js_DrawCubeV),
    JS_CFUNC_DEF("DrawCubeWires",5,js_DrawCubeWires),
    JS_CFUNC_DEF("DrawCubeWiresV",3,js_DrawCubeWiresV),
    JS_CFUNC_DEF("DrawSphere",3,js_DrawSphere),
    JS_CFUNC_DEF("DrawSphereEx",5,js_DrawSphereEx),
    JS_CFUNC_DEF("DrawSphereWires",5,js_DrawSphereWires),
    JS_CFUNC_DEF("DrawCylinder",6,js_DrawCylinder),
    JS_CFUNC_DEF("DrawCylinderEx",6,js_DrawCylinderEx),
    JS_CFUNC_DEF("DrawCylinderWires",6,js_DrawCylinderWires),
    JS_CFUNC_DEF("DrawCylinderWiresEx",6,js_DrawCylinderWiresEx),
    JS_CFUNC_DEF("DrawCapsule",6,js_DrawCapsule),
    JS_CFUNC_DEF("DrawCapsuleWires",6,js_DrawCapsuleWires),
    JS_CFUNC_DEF("DrawPlane",3,js_DrawPlane),
    JS_CFUNC_DEF("DrawRay",2,js_DrawRay),
    JS_CFUNC_DEF("DrawGrid",2,js_DrawGrid),
    JS_CFUNC_DEF("LoadModel",1,js_LoadModel),
    JS_CFUNC_DEF("LoadModelFromMesh",1,js_LoadModelFromMesh),
    JS_CFUNC_DEF("IsModelValid",1,js_IsModelValid),
    JS_CFUNC_DEF("UnloadModel",1,js_UnloadModel),
    JS_CFUNC_DEF("GetModelBoundingBox",1,js_GetModelBoundingBox),
    JS_CFUNC_DEF("DrawModel",4,js_DrawModel),
    JS_CFUNC_DEF("DrawModelEx",6,js_DrawModelEx),
    JS_CFUNC_DEF("DrawModelWires",4,js_DrawModelWires),
    JS_CFUNC_DEF("DrawModelWiresEx",6,js_DrawModelWiresEx),
    JS_CFUNC_DEF("DrawModelPoints",4,js_DrawModelPoints),
    JS_CFUNC_DEF("DrawModelPointsEx",6,js_DrawModelPointsEx),
    JS_CFUNC_DEF("DrawBoundingBox",2,js_DrawBoundingBox),
    JS_CFUNC_DEF("DrawBillboard",5,js_DrawBillboard),
    JS_CFUNC_DEF("DrawBillboardRec",6,js_DrawBillboardRec),
    JS_CFUNC_DEF("DrawBillboardPro",9,js_DrawBillboardPro),
    JS_CFUNC_DEF("UploadMesh",2,js_UploadMesh),
    JS_CFUNC_DEF("UpdateMeshBuffer",5,js_UpdateMeshBuffer),
    JS_CFUNC_DEF("UnloadMesh",1,js_UnloadMesh),
    JS_CFUNC_DEF("DrawMesh",3,js_DrawMesh),
    JS_CFUNC_DEF("DrawMeshInstanced",4,js_DrawMeshInstanced),
    JS_CFUNC_DEF("GetMeshBoundingBox",1,js_GetMeshBoundingBox),
    JS_CFUNC_DEF("GenMeshTangents",1,js_GenMeshTangents),
    JS_CFUNC_DEF("ExportMesh",2,js_ExportMesh),
    JS_CFUNC_DEF("ExportMeshAsCode",2,js_ExportMeshAsCode),
    JS_CFUNC_DEF("GenMeshPoly",2,js_GenMeshPoly),
    JS_CFUNC_DEF("GenMeshPlane",4,js_GenMeshPlane),
    JS_CFUNC_DEF("GenMeshCube",3,js_GenMeshCube),
    JS_CFUNC_DEF("GenMeshSphere",3,js_GenMeshSphere),
    JS_CFUNC_DEF("GenMeshHemiSphere",3,js_GenMeshHemiSphere),
    JS_CFUNC_DEF("GenMeshCylinder",3,js_GenMeshCylinder),
    JS_CFUNC_DEF("GenMeshCone",3,js_GenMeshCone),
    JS_CFUNC_DEF("GenMeshTorus",4,js_GenMeshTorus),
    JS_CFUNC_DEF("GenMeshKnot",4,js_GenMeshKnot),
    JS_CFUNC_DEF("GenMeshHeightmap",2,js_GenMeshHeightmap),
    JS_CFUNC_DEF("GenMeshCubicmap",2,js_GenMeshCubicmap),
    JS_CFUNC_DEF("LoadMaterialDefault",0,js_LoadMaterialDefault),
    JS_CFUNC_DEF("IsMaterialValid",1,js_IsMaterialValid),
    JS_CFUNC_DEF("UnloadMaterial",1,js_UnloadMaterial),
    JS_CFUNC_DEF("SetMaterialTexture",3,js_SetMaterialTexture),
    JS_CFUNC_DEF("SetModelMeshMaterial",3,js_SetModelMeshMaterial),
    JS_CFUNC_DEF("UpdateModelAnimationBones",3,js_UpdateModelAnimationBones),
    JS_CFUNC_DEF("CheckCollisionSpheres",4,js_CheckCollisionSpheres),
    JS_CFUNC_DEF("CheckCollisionBoxes",2,js_CheckCollisionBoxes),
    JS_CFUNC_DEF("CheckCollisionBoxSphere",3,js_CheckCollisionBoxSphere),
    JS_CFUNC_DEF("GetRayCollisionSphere",3,js_GetRayCollisionSphere),
    JS_CFUNC_DEF("GetRayCollisionBox",2,js_GetRayCollisionBox),
    JS_CFUNC_DEF("GetRayCollisionMesh",3,js_GetRayCollisionMesh),
    JS_CFUNC_DEF("GetRayCollisionTriangle",4,js_GetRayCollisionTriangle),
    JS_CFUNC_DEF("GetRayCollisionQuad",5,js_GetRayCollisionQuad),
    JS_CFUNC_DEF("InitAudioDevice",0,js_InitAudioDevice),
    JS_CFUNC_DEF("CloseAudioDevice",0,js_CloseAudioDevice),
    JS_CFUNC_DEF("IsAudioDeviceReady",0,js_IsAudioDeviceReady),
    JS_CFUNC_DEF("SetMasterVolume",1,js_SetMasterVolume),
    JS_CFUNC_DEF("GetMasterVolume",0,js_GetMasterVolume),
    JS_CFUNC_DEF("LoadWave",1,js_LoadWave),
    JS_CFUNC_DEF("LoadWaveFromMemory",3,js_LoadWaveFromMemory),
    JS_CFUNC_DEF("IsWaveValid",1,js_IsWaveValid),
    JS_CFUNC_DEF("LoadSound",1,js_LoadSound),
    JS_CFUNC_DEF("LoadSoundFromWave",1,js_LoadSoundFromWave),
    JS_CFUNC_DEF("LoadSoundAlias",1,js_LoadSoundAlias),
    JS_CFUNC_DEF("IsSoundValid",1,js_IsSoundValid),
    JS_CFUNC_DEF("UpdateSound",3,js_UpdateSound),
    JS_CFUNC_DEF("UnloadWave",1,js_UnloadWave),
    JS_CFUNC_DEF("UnloadSound",1,js_UnloadSound),
    JS_CFUNC_DEF("UnloadSoundAlias",1,js_UnloadSoundAlias),
    JS_CFUNC_DEF("ExportWave",2,js_ExportWave),
    JS_CFUNC_DEF("PlaySound",1,js_PlaySound),
    JS_CFUNC_DEF("StopSound",1,js_StopSound),
    JS_CFUNC_DEF("PauseSound",1,js_PauseSound),
    JS_CFUNC_DEF("ResumeSound",1,js_ResumeSound),
    JS_CFUNC_DEF("IsSoundPlaying",1,js_IsSoundPlaying),
    JS_CFUNC_DEF("SetSoundVolume",2,js_SetSoundVolume),
    JS_CFUNC_DEF("SetSoundPitch",2,js_SetSoundPitch),
    JS_CFUNC_DEF("SetSoundPan",2,js_SetSoundPan),
    JS_CFUNC_DEF("WaveCopy",1,js_WaveCopy),
    JS_CFUNC_DEF("WaveCrop",3,js_WaveCrop),
    JS_CFUNC_DEF("WaveFormat",4,js_WaveFormat),
    JS_CFUNC_DEF("LoadWaveSamples",1,js_LoadWaveSamples),
    JS_CFUNC_DEF("UnloadWaveSamples",1,js_UnloadWaveSamples),
    JS_CFUNC_DEF("LoadMusicStream",1,js_LoadMusicStream),
    JS_CFUNC_DEF("LoadMusicStreamFromMemory",3,js_LoadMusicStreamFromMemory),
    JS_CFUNC_DEF("IsMusicValid",1,js_IsMusicValid),
    JS_CFUNC_DEF("UnloadMusicStream",1,js_UnloadMusicStream),
    JS_CFUNC_DEF("PlayMusicStream",1,js_PlayMusicStream),
    JS_CFUNC_DEF("IsMusicStreamPlaying",1,js_IsMusicStreamPlaying),
    JS_CFUNC_DEF("UpdateMusicStream",1,js_UpdateMusicStream),
    JS_CFUNC_DEF("StopMusicStream",1,js_StopMusicStream),
    JS_CFUNC_DEF("PauseMusicStream",1,js_PauseMusicStream),
    JS_CFUNC_DEF("ResumeMusicStream",1,js_ResumeMusicStream),
    JS_CFUNC_DEF("SeekMusicStream",2,js_SeekMusicStream),
    JS_CFUNC_DEF("SetMusicVolume",2,js_SetMusicVolume),
    JS_CFUNC_DEF("SetMusicPitch",2,js_SetMusicPitch),
    JS_CFUNC_DEF("SetMusicPan",2,js_SetMusicPan),
    JS_CFUNC_DEF("GetMusicTimeLength",1,js_GetMusicTimeLength),
    JS_CFUNC_DEF("GetMusicTimePlayed",1,js_GetMusicTimePlayed),
    JS_CFUNC_DEF("LoadAudioStream",3,js_LoadAudioStream),
    JS_CFUNC_DEF("IsAudioStreamValid",1,js_IsAudioStreamValid),
    JS_CFUNC_DEF("UnloadAudioStream",1,js_UnloadAudioStream),
    JS_CFUNC_DEF("UpdateAudioStream",3,js_UpdateAudioStream),
    JS_CFUNC_DEF("IsAudioStreamProcessed",1,js_IsAudioStreamProcessed),
    JS_CFUNC_DEF("PlayAudioStream",1,js_PlayAudioStream),
    JS_CFUNC_DEF("PauseAudioStream",1,js_PauseAudioStream),
    JS_CFUNC_DEF("ResumeAudioStream",1,js_ResumeAudioStream),
    JS_CFUNC_DEF("IsAudioStreamPlaying",1,js_IsAudioStreamPlaying),
    JS_CFUNC_DEF("StopAudioStream",1,js_StopAudioStream),
    JS_CFUNC_DEF("SetAudioStreamVolume",2,js_SetAudioStreamVolume),
    JS_CFUNC_DEF("SetAudioStreamPitch",2,js_SetAudioStreamPitch),
    JS_CFUNC_DEF("SetAudioStreamPan",2,js_SetAudioStreamPan),
    JS_CFUNC_DEF("SetAudioStreamBufferSizeDefault",1,js_SetAudioStreamBufferSizeDefault),
    JS_CFUNC_DEF("AttachAudioMixedProcessor",1,js_AttachAudioMixedProcessor),
    JS_CFUNC_DEF("DetachAudioMixedProcessor",1,js_DetachAudioMixedProcessor),
};

static int js_js_raylib_init(JSContext * ctx, JSModuleDef * m) {
    JS_SetModuleExportList(ctx, m,js_js_raylib_funcs,countof(js_js_raylib_funcs));
    js_declare_Vector2(ctx, m);
    JSValue Vector2_constr = JS_NewCFunction2(ctx, js_Vector2_constructor,"Vector2", 2, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "Vector2", Vector2_constr);
    js_declare_Vector3(ctx, m);
    JSValue Vector3_constr = JS_NewCFunction2(ctx, js_Vector3_constructor,"Vector3", 3, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "Vector3", Vector3_constr);
    js_declare_Vector4(ctx, m);
    JSValue Vector4_constr = JS_NewCFunction2(ctx, js_Vector4_constructor,"Vector4", 4, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "Vector4", Vector4_constr);
    js_declare_Matrix(ctx, m);
    js_declare_Color(ctx, m);
    JSValue Color_constr = JS_NewCFunction2(ctx, js_Color_constructor,"Color", 4, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "Color", Color_constr);
    js_declare_Rectangle(ctx, m);
    JSValue Rectangle_constr = JS_NewCFunction2(ctx, js_Rectangle_constructor,"Rectangle", 4, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "Rectangle", Rectangle_constr);
    js_declare_Image(ctx, m);
    JSValue Image_constr = JS_NewCFunction2(ctx, js_Image_constructor,"Image", 5, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "Image", Image_constr);
    js_declare_Texture(ctx, m);
    js_declare_RenderTexture(ctx, m);
    js_declare_NPatchInfo(ctx, m);
    JSValue NPatchInfo_constr = JS_NewCFunction2(ctx, js_NPatchInfo_constructor,"NPatchInfo", 6, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "NPatchInfo", NPatchInfo_constr);
    js_declare_GlyphInfo(ctx, m);
    js_declare_Font(ctx, m);
    js_declare_Camera3D(ctx, m);
    JSValue Camera3D_constr = JS_NewCFunction2(ctx, js_Camera3D_constructor,"Camera3D", 5, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "Camera3D", Camera3D_constr);
    js_declare_Camera2D(ctx, m);
    JSValue Camera2D_constr = JS_NewCFunction2(ctx, js_Camera2D_constructor,"Camera2D", 4, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "Camera2D", Camera2D_constr);
    js_declare_Mesh(ctx, m);
    JSValue Mesh_constr = JS_NewCFunction2(ctx, js_Mesh_constructor,"Mesh", 17, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "Mesh", Mesh_constr);
    js_declare_Shader(ctx, m);
    js_declare_MaterialMap(ctx, m);
    js_declare_Material(ctx, m);
    js_declare_Transform(ctx, m);
    js_declare_BoneInfo(ctx, m);
    js_declare_Model(ctx, m);
    js_declare_ModelAnimation(ctx, m);
    js_declare_Ray(ctx, m);
    JSValue Ray_constr = JS_NewCFunction2(ctx, js_Ray_constructor,"Ray", 2, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "Ray", Ray_constr);
    js_declare_RayCollision(ctx, m);
    js_declare_BoundingBox(ctx, m);
    JSValue BoundingBox_constr = JS_NewCFunction2(ctx, js_BoundingBox_constructor,"BoundingBox", 2, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "BoundingBox", BoundingBox_constr);
    js_declare_Wave(ctx, m);
    js_declare_rAudioBuffer(ctx, m);
    js_declare_rAudioProcessor(ctx, m);
    js_declare_AudioStream(ctx, m);
    js_declare_Sound(ctx, m);
    js_declare_Music(ctx, m);
    js_declare_VrDeviceInfo(ctx, m);
    JSValue VrDeviceInfo_constr = JS_NewCFunction2(ctx, js_VrDeviceInfo_constructor,"VrDeviceInfo", 9, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "VrDeviceInfo", VrDeviceInfo_constr);
    js_declare_VrStereoConfig(ctx, m);
    js_declare_FilePathList(ctx, m);
    js_declare_AutomationEvent(ctx, m);
    js_declare_AutomationEventList(ctx, m);
    JS_SetModuleExport(ctx, m, "false", JS_NewInt32(ctx, false));
    JS_SetModuleExport(ctx, m, "true", JS_NewInt32(ctx, true));
    JS_SetModuleExport(ctx, m, "FLAG_VSYNC_HINT", JS_NewInt32(ctx, FLAG_VSYNC_HINT));
    JS_SetModuleExport(ctx, m, "FLAG_FULLSCREEN_MODE", JS_NewInt32(ctx, FLAG_FULLSCREEN_MODE));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_RESIZABLE", JS_NewInt32(ctx, FLAG_WINDOW_RESIZABLE));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_UNDECORATED", JS_NewInt32(ctx, FLAG_WINDOW_UNDECORATED));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_HIDDEN", JS_NewInt32(ctx, FLAG_WINDOW_HIDDEN));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_MINIMIZED", JS_NewInt32(ctx, FLAG_WINDOW_MINIMIZED));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_MAXIMIZED", JS_NewInt32(ctx, FLAG_WINDOW_MAXIMIZED));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_UNFOCUSED", JS_NewInt32(ctx, FLAG_WINDOW_UNFOCUSED));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_TOPMOST", JS_NewInt32(ctx, FLAG_WINDOW_TOPMOST));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_ALWAYS_RUN", JS_NewInt32(ctx, FLAG_WINDOW_ALWAYS_RUN));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_TRANSPARENT", JS_NewInt32(ctx, FLAG_WINDOW_TRANSPARENT));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_HIGHDPI", JS_NewInt32(ctx, FLAG_WINDOW_HIGHDPI));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_MOUSE_PASSTHROUGH", JS_NewInt32(ctx, FLAG_WINDOW_MOUSE_PASSTHROUGH));
    JS_SetModuleExport(ctx, m, "FLAG_BORDERLESS_WINDOWED_MODE", JS_NewInt32(ctx, FLAG_BORDERLESS_WINDOWED_MODE));
    JS_SetModuleExport(ctx, m, "FLAG_MSAA_4X_HINT", JS_NewInt32(ctx, FLAG_MSAA_4X_HINT));
    JS_SetModuleExport(ctx, m, "FLAG_INTERLACED_HINT", JS_NewInt32(ctx, FLAG_INTERLACED_HINT));
    JS_SetModuleExport(ctx, m, "LOG_ALL", JS_NewInt32(ctx, LOG_ALL));
    JS_SetModuleExport(ctx, m, "LOG_TRACE", JS_NewInt32(ctx, LOG_TRACE));
    JS_SetModuleExport(ctx, m, "LOG_DEBUG", JS_NewInt32(ctx, LOG_DEBUG));
    JS_SetModuleExport(ctx, m, "LOG_INFO", JS_NewInt32(ctx, LOG_INFO));
    JS_SetModuleExport(ctx, m, "LOG_WARNING", JS_NewInt32(ctx, LOG_WARNING));
    JS_SetModuleExport(ctx, m, "LOG_ERROR", JS_NewInt32(ctx, LOG_ERROR));
    JS_SetModuleExport(ctx, m, "LOG_FATAL", JS_NewInt32(ctx, LOG_FATAL));
    JS_SetModuleExport(ctx, m, "LOG_NONE", JS_NewInt32(ctx, LOG_NONE));
    JS_SetModuleExport(ctx, m, "KEY_NULL", JS_NewInt32(ctx, KEY_NULL));
    JS_SetModuleExport(ctx, m, "KEY_APOSTROPHE", JS_NewInt32(ctx, KEY_APOSTROPHE));
    JS_SetModuleExport(ctx, m, "KEY_COMMA", JS_NewInt32(ctx, KEY_COMMA));
    JS_SetModuleExport(ctx, m, "KEY_MINUS", JS_NewInt32(ctx, KEY_MINUS));
    JS_SetModuleExport(ctx, m, "KEY_PERIOD", JS_NewInt32(ctx, KEY_PERIOD));
    JS_SetModuleExport(ctx, m, "KEY_SLASH", JS_NewInt32(ctx, KEY_SLASH));
    JS_SetModuleExport(ctx, m, "KEY_ZERO", JS_NewInt32(ctx, KEY_ZERO));
    JS_SetModuleExport(ctx, m, "KEY_ONE", JS_NewInt32(ctx, KEY_ONE));
    JS_SetModuleExport(ctx, m, "KEY_TWO", JS_NewInt32(ctx, KEY_TWO));
    JS_SetModuleExport(ctx, m, "KEY_THREE", JS_NewInt32(ctx, KEY_THREE));
    JS_SetModuleExport(ctx, m, "KEY_FOUR", JS_NewInt32(ctx, KEY_FOUR));
    JS_SetModuleExport(ctx, m, "KEY_FIVE", JS_NewInt32(ctx, KEY_FIVE));
    JS_SetModuleExport(ctx, m, "KEY_SIX", JS_NewInt32(ctx, KEY_SIX));
    JS_SetModuleExport(ctx, m, "KEY_SEVEN", JS_NewInt32(ctx, KEY_SEVEN));
    JS_SetModuleExport(ctx, m, "KEY_EIGHT", JS_NewInt32(ctx, KEY_EIGHT));
    JS_SetModuleExport(ctx, m, "KEY_NINE", JS_NewInt32(ctx, KEY_NINE));
    JS_SetModuleExport(ctx, m, "KEY_SEMICOLON", JS_NewInt32(ctx, KEY_SEMICOLON));
    JS_SetModuleExport(ctx, m, "KEY_EQUAL", JS_NewInt32(ctx, KEY_EQUAL));
    JS_SetModuleExport(ctx, m, "KEY_A", JS_NewInt32(ctx, KEY_A));
    JS_SetModuleExport(ctx, m, "KEY_B", JS_NewInt32(ctx, KEY_B));
    JS_SetModuleExport(ctx, m, "KEY_C", JS_NewInt32(ctx, KEY_C));
    JS_SetModuleExport(ctx, m, "KEY_D", JS_NewInt32(ctx, KEY_D));
    JS_SetModuleExport(ctx, m, "KEY_E", JS_NewInt32(ctx, KEY_E));
    JS_SetModuleExport(ctx, m, "KEY_F", JS_NewInt32(ctx, KEY_F));
    JS_SetModuleExport(ctx, m, "KEY_G", JS_NewInt32(ctx, KEY_G));
    JS_SetModuleExport(ctx, m, "KEY_H", JS_NewInt32(ctx, KEY_H));
    JS_SetModuleExport(ctx, m, "KEY_I", JS_NewInt32(ctx, KEY_I));
    JS_SetModuleExport(ctx, m, "KEY_J", JS_NewInt32(ctx, KEY_J));
    JS_SetModuleExport(ctx, m, "KEY_K", JS_NewInt32(ctx, KEY_K));
    JS_SetModuleExport(ctx, m, "KEY_L", JS_NewInt32(ctx, KEY_L));
    JS_SetModuleExport(ctx, m, "KEY_M", JS_NewInt32(ctx, KEY_M));
    JS_SetModuleExport(ctx, m, "KEY_N", JS_NewInt32(ctx, KEY_N));
    JS_SetModuleExport(ctx, m, "KEY_O", JS_NewInt32(ctx, KEY_O));
    JS_SetModuleExport(ctx, m, "KEY_P", JS_NewInt32(ctx, KEY_P));
    JS_SetModuleExport(ctx, m, "KEY_Q", JS_NewInt32(ctx, KEY_Q));
    JS_SetModuleExport(ctx, m, "KEY_R", JS_NewInt32(ctx, KEY_R));
    JS_SetModuleExport(ctx, m, "KEY_S", JS_NewInt32(ctx, KEY_S));
    JS_SetModuleExport(ctx, m, "KEY_T", JS_NewInt32(ctx, KEY_T));
    JS_SetModuleExport(ctx, m, "KEY_U", JS_NewInt32(ctx, KEY_U));
    JS_SetModuleExport(ctx, m, "KEY_V", JS_NewInt32(ctx, KEY_V));
    JS_SetModuleExport(ctx, m, "KEY_W", JS_NewInt32(ctx, KEY_W));
    JS_SetModuleExport(ctx, m, "KEY_X", JS_NewInt32(ctx, KEY_X));
    JS_SetModuleExport(ctx, m, "KEY_Y", JS_NewInt32(ctx, KEY_Y));
    JS_SetModuleExport(ctx, m, "KEY_Z", JS_NewInt32(ctx, KEY_Z));
    JS_SetModuleExport(ctx, m, "KEY_LEFT_BRACKET", JS_NewInt32(ctx, KEY_LEFT_BRACKET));
    JS_SetModuleExport(ctx, m, "KEY_BACKSLASH", JS_NewInt32(ctx, KEY_BACKSLASH));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT_BRACKET", JS_NewInt32(ctx, KEY_RIGHT_BRACKET));
    JS_SetModuleExport(ctx, m, "KEY_GRAVE", JS_NewInt32(ctx, KEY_GRAVE));
    JS_SetModuleExport(ctx, m, "KEY_SPACE", JS_NewInt32(ctx, KEY_SPACE));
    JS_SetModuleExport(ctx, m, "KEY_ESCAPE", JS_NewInt32(ctx, KEY_ESCAPE));
    JS_SetModuleExport(ctx, m, "KEY_ENTER", JS_NewInt32(ctx, KEY_ENTER));
    JS_SetModuleExport(ctx, m, "KEY_TAB", JS_NewInt32(ctx, KEY_TAB));
    JS_SetModuleExport(ctx, m, "KEY_BACKSPACE", JS_NewInt32(ctx, KEY_BACKSPACE));
    JS_SetModuleExport(ctx, m, "KEY_INSERT", JS_NewInt32(ctx, KEY_INSERT));
    JS_SetModuleExport(ctx, m, "KEY_DELETE", JS_NewInt32(ctx, KEY_DELETE));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT", JS_NewInt32(ctx, KEY_RIGHT));
    JS_SetModuleExport(ctx, m, "KEY_LEFT", JS_NewInt32(ctx, KEY_LEFT));
    JS_SetModuleExport(ctx, m, "KEY_DOWN", JS_NewInt32(ctx, KEY_DOWN));
    JS_SetModuleExport(ctx, m, "KEY_UP", JS_NewInt32(ctx, KEY_UP));
    JS_SetModuleExport(ctx, m, "KEY_PAGE_UP", JS_NewInt32(ctx, KEY_PAGE_UP));
    JS_SetModuleExport(ctx, m, "KEY_PAGE_DOWN", JS_NewInt32(ctx, KEY_PAGE_DOWN));
    JS_SetModuleExport(ctx, m, "KEY_HOME", JS_NewInt32(ctx, KEY_HOME));
    JS_SetModuleExport(ctx, m, "KEY_END", JS_NewInt32(ctx, KEY_END));
    JS_SetModuleExport(ctx, m, "KEY_CAPS_LOCK", JS_NewInt32(ctx, KEY_CAPS_LOCK));
    JS_SetModuleExport(ctx, m, "KEY_SCROLL_LOCK", JS_NewInt32(ctx, KEY_SCROLL_LOCK));
    JS_SetModuleExport(ctx, m, "KEY_NUM_LOCK", JS_NewInt32(ctx, KEY_NUM_LOCK));
    JS_SetModuleExport(ctx, m, "KEY_PRINT_SCREEN", JS_NewInt32(ctx, KEY_PRINT_SCREEN));
    JS_SetModuleExport(ctx, m, "KEY_PAUSE", JS_NewInt32(ctx, KEY_PAUSE));
    JS_SetModuleExport(ctx, m, "KEY_F1", JS_NewInt32(ctx, KEY_F1));
    JS_SetModuleExport(ctx, m, "KEY_F2", JS_NewInt32(ctx, KEY_F2));
    JS_SetModuleExport(ctx, m, "KEY_F3", JS_NewInt32(ctx, KEY_F3));
    JS_SetModuleExport(ctx, m, "KEY_F4", JS_NewInt32(ctx, KEY_F4));
    JS_SetModuleExport(ctx, m, "KEY_F5", JS_NewInt32(ctx, KEY_F5));
    JS_SetModuleExport(ctx, m, "KEY_F6", JS_NewInt32(ctx, KEY_F6));
    JS_SetModuleExport(ctx, m, "KEY_F7", JS_NewInt32(ctx, KEY_F7));
    JS_SetModuleExport(ctx, m, "KEY_F8", JS_NewInt32(ctx, KEY_F8));
    JS_SetModuleExport(ctx, m, "KEY_F9", JS_NewInt32(ctx, KEY_F9));
    JS_SetModuleExport(ctx, m, "KEY_F10", JS_NewInt32(ctx, KEY_F10));
    JS_SetModuleExport(ctx, m, "KEY_F11", JS_NewInt32(ctx, KEY_F11));
    JS_SetModuleExport(ctx, m, "KEY_F12", JS_NewInt32(ctx, KEY_F12));
    JS_SetModuleExport(ctx, m, "KEY_LEFT_SHIFT", JS_NewInt32(ctx, KEY_LEFT_SHIFT));
    JS_SetModuleExport(ctx, m, "KEY_LEFT_CONTROL", JS_NewInt32(ctx, KEY_LEFT_CONTROL));
    JS_SetModuleExport(ctx, m, "KEY_LEFT_ALT", JS_NewInt32(ctx, KEY_LEFT_ALT));
    JS_SetModuleExport(ctx, m, "KEY_LEFT_SUPER", JS_NewInt32(ctx, KEY_LEFT_SUPER));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT_SHIFT", JS_NewInt32(ctx, KEY_RIGHT_SHIFT));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT_CONTROL", JS_NewInt32(ctx, KEY_RIGHT_CONTROL));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT_ALT", JS_NewInt32(ctx, KEY_RIGHT_ALT));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT_SUPER", JS_NewInt32(ctx, KEY_RIGHT_SUPER));
    JS_SetModuleExport(ctx, m, "KEY_KB_MENU", JS_NewInt32(ctx, KEY_KB_MENU));
    JS_SetModuleExport(ctx, m, "KEY_KP_0", JS_NewInt32(ctx, KEY_KP_0));
    JS_SetModuleExport(ctx, m, "KEY_KP_1", JS_NewInt32(ctx, KEY_KP_1));
    JS_SetModuleExport(ctx, m, "KEY_KP_2", JS_NewInt32(ctx, KEY_KP_2));
    JS_SetModuleExport(ctx, m, "KEY_KP_3", JS_NewInt32(ctx, KEY_KP_3));
    JS_SetModuleExport(ctx, m, "KEY_KP_4", JS_NewInt32(ctx, KEY_KP_4));
    JS_SetModuleExport(ctx, m, "KEY_KP_5", JS_NewInt32(ctx, KEY_KP_5));
    JS_SetModuleExport(ctx, m, "KEY_KP_6", JS_NewInt32(ctx, KEY_KP_6));
    JS_SetModuleExport(ctx, m, "KEY_KP_7", JS_NewInt32(ctx, KEY_KP_7));
    JS_SetModuleExport(ctx, m, "KEY_KP_8", JS_NewInt32(ctx, KEY_KP_8));
    JS_SetModuleExport(ctx, m, "KEY_KP_9", JS_NewInt32(ctx, KEY_KP_9));
    JS_SetModuleExport(ctx, m, "KEY_KP_DECIMAL", JS_NewInt32(ctx, KEY_KP_DECIMAL));
    JS_SetModuleExport(ctx, m, "KEY_KP_DIVIDE", JS_NewInt32(ctx, KEY_KP_DIVIDE));
    JS_SetModuleExport(ctx, m, "KEY_KP_MULTIPLY", JS_NewInt32(ctx, KEY_KP_MULTIPLY));
    JS_SetModuleExport(ctx, m, "KEY_KP_SUBTRACT", JS_NewInt32(ctx, KEY_KP_SUBTRACT));
    JS_SetModuleExport(ctx, m, "KEY_KP_ADD", JS_NewInt32(ctx, KEY_KP_ADD));
    JS_SetModuleExport(ctx, m, "KEY_KP_ENTER", JS_NewInt32(ctx, KEY_KP_ENTER));
    JS_SetModuleExport(ctx, m, "KEY_KP_EQUAL", JS_NewInt32(ctx, KEY_KP_EQUAL));
    JS_SetModuleExport(ctx, m, "KEY_BACK", JS_NewInt32(ctx, KEY_BACK));
    JS_SetModuleExport(ctx, m, "KEY_MENU", JS_NewInt32(ctx, KEY_MENU));
    JS_SetModuleExport(ctx, m, "KEY_VOLUME_UP", JS_NewInt32(ctx, KEY_VOLUME_UP));
    JS_SetModuleExport(ctx, m, "KEY_VOLUME_DOWN", JS_NewInt32(ctx, KEY_VOLUME_DOWN));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_LEFT", JS_NewInt32(ctx, MOUSE_BUTTON_LEFT));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_RIGHT", JS_NewInt32(ctx, MOUSE_BUTTON_RIGHT));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_MIDDLE", JS_NewInt32(ctx, MOUSE_BUTTON_MIDDLE));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_SIDE", JS_NewInt32(ctx, MOUSE_BUTTON_SIDE));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_EXTRA", JS_NewInt32(ctx, MOUSE_BUTTON_EXTRA));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_FORWARD", JS_NewInt32(ctx, MOUSE_BUTTON_FORWARD));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_BACK", JS_NewInt32(ctx, MOUSE_BUTTON_BACK));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_DEFAULT", JS_NewInt32(ctx, MOUSE_CURSOR_DEFAULT));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_ARROW", JS_NewInt32(ctx, MOUSE_CURSOR_ARROW));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_IBEAM", JS_NewInt32(ctx, MOUSE_CURSOR_IBEAM));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_CROSSHAIR", JS_NewInt32(ctx, MOUSE_CURSOR_CROSSHAIR));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_POINTING_HAND", JS_NewInt32(ctx, MOUSE_CURSOR_POINTING_HAND));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_EW", JS_NewInt32(ctx, MOUSE_CURSOR_RESIZE_EW));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NS", JS_NewInt32(ctx, MOUSE_CURSOR_RESIZE_NS));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NWSE", JS_NewInt32(ctx, MOUSE_CURSOR_RESIZE_NWSE));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NESW", JS_NewInt32(ctx, MOUSE_CURSOR_RESIZE_NESW));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_ALL", JS_NewInt32(ctx, MOUSE_CURSOR_RESIZE_ALL));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_NOT_ALLOWED", JS_NewInt32(ctx, MOUSE_CURSOR_NOT_ALLOWED));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_UNKNOWN", JS_NewInt32(ctx, GAMEPAD_BUTTON_UNKNOWN));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_UP", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_FACE_UP));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_RIGHT", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_FACE_RIGHT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_DOWN", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_FACE_DOWN));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_LEFT", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_FACE_LEFT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_UP", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_FACE_UP));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_DOWN", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_FACE_DOWN));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_LEFT", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_FACE_LEFT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_TRIGGER_1", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_TRIGGER_1));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_TRIGGER_2", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_TRIGGER_2));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_TRIGGER_1", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_TRIGGER_1));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_TRIGGER_2", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_TRIGGER_2));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE_LEFT", JS_NewInt32(ctx, GAMEPAD_BUTTON_MIDDLE_LEFT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE", JS_NewInt32(ctx, GAMEPAD_BUTTON_MIDDLE));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE_RIGHT", JS_NewInt32(ctx, GAMEPAD_BUTTON_MIDDLE_RIGHT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_THUMB", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_THUMB));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_THUMB", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_THUMB));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_X", JS_NewInt32(ctx, GAMEPAD_AXIS_LEFT_X));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_Y", JS_NewInt32(ctx, GAMEPAD_AXIS_LEFT_Y));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_X", JS_NewInt32(ctx, GAMEPAD_AXIS_RIGHT_X));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_Y", JS_NewInt32(ctx, GAMEPAD_AXIS_RIGHT_Y));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_TRIGGER", JS_NewInt32(ctx, GAMEPAD_AXIS_LEFT_TRIGGER));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_TRIGGER", JS_NewInt32(ctx, GAMEPAD_AXIS_RIGHT_TRIGGER));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_ALBEDO", JS_NewInt32(ctx, MATERIAL_MAP_ALBEDO));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_METALNESS", JS_NewInt32(ctx, MATERIAL_MAP_METALNESS));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_NORMAL", JS_NewInt32(ctx, MATERIAL_MAP_NORMAL));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_ROUGHNESS", JS_NewInt32(ctx, MATERIAL_MAP_ROUGHNESS));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_OCCLUSION", JS_NewInt32(ctx, MATERIAL_MAP_OCCLUSION));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_EMISSION", JS_NewInt32(ctx, MATERIAL_MAP_EMISSION));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_HEIGHT", JS_NewInt32(ctx, MATERIAL_MAP_HEIGHT));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_CUBEMAP", JS_NewInt32(ctx, MATERIAL_MAP_CUBEMAP));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_IRRADIANCE", JS_NewInt32(ctx, MATERIAL_MAP_IRRADIANCE));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_PREFILTER", JS_NewInt32(ctx, MATERIAL_MAP_PREFILTER));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_BRDF", JS_NewInt32(ctx, MATERIAL_MAP_BRDF));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_POSITION", JS_NewInt32(ctx, SHADER_LOC_VERTEX_POSITION));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_TEXCOORD01", JS_NewInt32(ctx, SHADER_LOC_VERTEX_TEXCOORD01));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_TEXCOORD02", JS_NewInt32(ctx, SHADER_LOC_VERTEX_TEXCOORD02));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_NORMAL", JS_NewInt32(ctx, SHADER_LOC_VERTEX_NORMAL));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_TANGENT", JS_NewInt32(ctx, SHADER_LOC_VERTEX_TANGENT));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_COLOR", JS_NewInt32(ctx, SHADER_LOC_VERTEX_COLOR));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MATRIX_MVP", JS_NewInt32(ctx, SHADER_LOC_MATRIX_MVP));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MATRIX_VIEW", JS_NewInt32(ctx, SHADER_LOC_MATRIX_VIEW));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MATRIX_PROJECTION", JS_NewInt32(ctx, SHADER_LOC_MATRIX_PROJECTION));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MATRIX_MODEL", JS_NewInt32(ctx, SHADER_LOC_MATRIX_MODEL));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MATRIX_NORMAL", JS_NewInt32(ctx, SHADER_LOC_MATRIX_NORMAL));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VECTOR_VIEW", JS_NewInt32(ctx, SHADER_LOC_VECTOR_VIEW));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_COLOR_DIFFUSE", JS_NewInt32(ctx, SHADER_LOC_COLOR_DIFFUSE));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_COLOR_SPECULAR", JS_NewInt32(ctx, SHADER_LOC_COLOR_SPECULAR));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_COLOR_AMBIENT", JS_NewInt32(ctx, SHADER_LOC_COLOR_AMBIENT));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_ALBEDO", JS_NewInt32(ctx, SHADER_LOC_MAP_ALBEDO));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_METALNESS", JS_NewInt32(ctx, SHADER_LOC_MAP_METALNESS));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_NORMAL", JS_NewInt32(ctx, SHADER_LOC_MAP_NORMAL));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_ROUGHNESS", JS_NewInt32(ctx, SHADER_LOC_MAP_ROUGHNESS));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_OCCLUSION", JS_NewInt32(ctx, SHADER_LOC_MAP_OCCLUSION));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_EMISSION", JS_NewInt32(ctx, SHADER_LOC_MAP_EMISSION));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_HEIGHT", JS_NewInt32(ctx, SHADER_LOC_MAP_HEIGHT));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_CUBEMAP", JS_NewInt32(ctx, SHADER_LOC_MAP_CUBEMAP));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_IRRADIANCE", JS_NewInt32(ctx, SHADER_LOC_MAP_IRRADIANCE));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_PREFILTER", JS_NewInt32(ctx, SHADER_LOC_MAP_PREFILTER));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_BRDF", JS_NewInt32(ctx, SHADER_LOC_MAP_BRDF));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_BONEIDS", JS_NewInt32(ctx, SHADER_LOC_VERTEX_BONEIDS));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_BONEWEIGHTS", JS_NewInt32(ctx, SHADER_LOC_VERTEX_BONEWEIGHTS));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_BONE_MATRICES", JS_NewInt32(ctx, SHADER_LOC_BONE_MATRICES));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_INSTANCE_TX", JS_NewInt32(ctx, SHADER_LOC_VERTEX_INSTANCE_TX));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_FLOAT", JS_NewInt32(ctx, SHADER_UNIFORM_FLOAT));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_VEC2", JS_NewInt32(ctx, SHADER_UNIFORM_VEC2));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_VEC3", JS_NewInt32(ctx, SHADER_UNIFORM_VEC3));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_VEC4", JS_NewInt32(ctx, SHADER_UNIFORM_VEC4));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_INT", JS_NewInt32(ctx, SHADER_UNIFORM_INT));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_IVEC2", JS_NewInt32(ctx, SHADER_UNIFORM_IVEC2));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_IVEC3", JS_NewInt32(ctx, SHADER_UNIFORM_IVEC3));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_IVEC4", JS_NewInt32(ctx, SHADER_UNIFORM_IVEC4));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_UINT", JS_NewInt32(ctx, SHADER_UNIFORM_UINT));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_UIVEC2", JS_NewInt32(ctx, SHADER_UNIFORM_UIVEC2));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_UIVEC3", JS_NewInt32(ctx, SHADER_UNIFORM_UIVEC3));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_UIVEC4", JS_NewInt32(ctx, SHADER_UNIFORM_UIVEC4));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_SAMPLER2D", JS_NewInt32(ctx, SHADER_UNIFORM_SAMPLER2D));
    JS_SetModuleExport(ctx, m, "SHADER_ATTRIB_FLOAT", JS_NewInt32(ctx, SHADER_ATTRIB_FLOAT));
    JS_SetModuleExport(ctx, m, "SHADER_ATTRIB_VEC2", JS_NewInt32(ctx, SHADER_ATTRIB_VEC2));
    JS_SetModuleExport(ctx, m, "SHADER_ATTRIB_VEC3", JS_NewInt32(ctx, SHADER_ATTRIB_VEC3));
    JS_SetModuleExport(ctx, m, "SHADER_ATTRIB_VEC4", JS_NewInt32(ctx, SHADER_ATTRIB_VEC4));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_GRAYSCALE", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_GRAYSCALE));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R5G6B5", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R5G6B5));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R8G8B8", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R8G8B8));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R5G5B5A1", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R5G5B5A1));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R4G4B4A4", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R4G4B4A4));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R8G8B8A8", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R32));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32G32B32", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R32G32B32));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32G32B32A32", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R32G32B32A32));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R16));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16G16B16", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R16G16B16));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16G16B16A16", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R16G16B16A16));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT1_RGB", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_DXT1_RGB));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT1_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_DXT1_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT3_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_DXT3_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT5_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_DXT5_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC1_RGB", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_ETC1_RGB));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC2_RGB", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_ETC2_RGB));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_PVRT_RGB", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_PVRT_RGB));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_PVRT_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_PVRT_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_POINT", JS_NewInt32(ctx, TEXTURE_FILTER_POINT));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_BILINEAR", JS_NewInt32(ctx, TEXTURE_FILTER_BILINEAR));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_TRILINEAR", JS_NewInt32(ctx, TEXTURE_FILTER_TRILINEAR));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_4X", JS_NewInt32(ctx, TEXTURE_FILTER_ANISOTROPIC_4X));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_8X", JS_NewInt32(ctx, TEXTURE_FILTER_ANISOTROPIC_8X));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_16X", JS_NewInt32(ctx, TEXTURE_FILTER_ANISOTROPIC_16X));
    JS_SetModuleExport(ctx, m, "TEXTURE_WRAP_REPEAT", JS_NewInt32(ctx, TEXTURE_WRAP_REPEAT));
    JS_SetModuleExport(ctx, m, "TEXTURE_WRAP_CLAMP", JS_NewInt32(ctx, TEXTURE_WRAP_CLAMP));
    JS_SetModuleExport(ctx, m, "TEXTURE_WRAP_MIRROR_REPEAT", JS_NewInt32(ctx, TEXTURE_WRAP_MIRROR_REPEAT));
    JS_SetModuleExport(ctx, m, "TEXTURE_WRAP_MIRROR_CLAMP", JS_NewInt32(ctx, TEXTURE_WRAP_MIRROR_CLAMP));
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_AUTO_DETECT", JS_NewInt32(ctx, CUBEMAP_LAYOUT_AUTO_DETECT));
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_LINE_VERTICAL", JS_NewInt32(ctx, CUBEMAP_LAYOUT_LINE_VERTICAL));
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_LINE_HORIZONTAL", JS_NewInt32(ctx, CUBEMAP_LAYOUT_LINE_HORIZONTAL));
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR", JS_NewInt32(ctx, CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR));
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE", JS_NewInt32(ctx, CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE));
    JS_SetModuleExport(ctx, m, "FONT_DEFAULT", JS_NewInt32(ctx, FONT_DEFAULT));
    JS_SetModuleExport(ctx, m, "FONT_BITMAP", JS_NewInt32(ctx, FONT_BITMAP));
    JS_SetModuleExport(ctx, m, "FONT_SDF", JS_NewInt32(ctx, FONT_SDF));
    JS_SetModuleExport(ctx, m, "BLEND_ALPHA", JS_NewInt32(ctx, BLEND_ALPHA));
    JS_SetModuleExport(ctx, m, "BLEND_ADDITIVE", JS_NewInt32(ctx, BLEND_ADDITIVE));
    JS_SetModuleExport(ctx, m, "BLEND_MULTIPLIED", JS_NewInt32(ctx, BLEND_MULTIPLIED));
    JS_SetModuleExport(ctx, m, "BLEND_ADD_COLORS", JS_NewInt32(ctx, BLEND_ADD_COLORS));
    JS_SetModuleExport(ctx, m, "BLEND_SUBTRACT_COLORS", JS_NewInt32(ctx, BLEND_SUBTRACT_COLORS));
    JS_SetModuleExport(ctx, m, "BLEND_ALPHA_PREMULTIPLY", JS_NewInt32(ctx, BLEND_ALPHA_PREMULTIPLY));
    JS_SetModuleExport(ctx, m, "BLEND_CUSTOM", JS_NewInt32(ctx, BLEND_CUSTOM));
    JS_SetModuleExport(ctx, m, "BLEND_CUSTOM_SEPARATE", JS_NewInt32(ctx, BLEND_CUSTOM_SEPARATE));
    JS_SetModuleExport(ctx, m, "GESTURE_NONE", JS_NewInt32(ctx, GESTURE_NONE));
    JS_SetModuleExport(ctx, m, "GESTURE_TAP", JS_NewInt32(ctx, GESTURE_TAP));
    JS_SetModuleExport(ctx, m, "GESTURE_DOUBLETAP", JS_NewInt32(ctx, GESTURE_DOUBLETAP));
    JS_SetModuleExport(ctx, m, "GESTURE_HOLD", JS_NewInt32(ctx, GESTURE_HOLD));
    JS_SetModuleExport(ctx, m, "GESTURE_DRAG", JS_NewInt32(ctx, GESTURE_DRAG));
    JS_SetModuleExport(ctx, m, "GESTURE_SWIPE_RIGHT", JS_NewInt32(ctx, GESTURE_SWIPE_RIGHT));
    JS_SetModuleExport(ctx, m, "GESTURE_SWIPE_LEFT", JS_NewInt32(ctx, GESTURE_SWIPE_LEFT));
    JS_SetModuleExport(ctx, m, "GESTURE_SWIPE_UP", JS_NewInt32(ctx, GESTURE_SWIPE_UP));
    JS_SetModuleExport(ctx, m, "GESTURE_SWIPE_DOWN", JS_NewInt32(ctx, GESTURE_SWIPE_DOWN));
    JS_SetModuleExport(ctx, m, "GESTURE_PINCH_IN", JS_NewInt32(ctx, GESTURE_PINCH_IN));
    JS_SetModuleExport(ctx, m, "GESTURE_PINCH_OUT", JS_NewInt32(ctx, GESTURE_PINCH_OUT));
    JS_SetModuleExport(ctx, m, "CAMERA_CUSTOM", JS_NewInt32(ctx, CAMERA_CUSTOM));
    JS_SetModuleExport(ctx, m, "CAMERA_FREE", JS_NewInt32(ctx, CAMERA_FREE));
    JS_SetModuleExport(ctx, m, "CAMERA_ORBITAL", JS_NewInt32(ctx, CAMERA_ORBITAL));
    JS_SetModuleExport(ctx, m, "CAMERA_FIRST_PERSON", JS_NewInt32(ctx, CAMERA_FIRST_PERSON));
    JS_SetModuleExport(ctx, m, "CAMERA_THIRD_PERSON", JS_NewInt32(ctx, CAMERA_THIRD_PERSON));
    JS_SetModuleExport(ctx, m, "CAMERA_PERSPECTIVE", JS_NewInt32(ctx, CAMERA_PERSPECTIVE));
    JS_SetModuleExport(ctx, m, "CAMERA_ORTHOGRAPHIC", JS_NewInt32(ctx, CAMERA_ORTHOGRAPHIC));
    JS_SetModuleExport(ctx, m, "NPATCH_NINE_PATCH", JS_NewInt32(ctx, NPATCH_NINE_PATCH));
    JS_SetModuleExport(ctx, m, "NPATCH_THREE_PATCH_VERTICAL", JS_NewInt32(ctx, NPATCH_THREE_PATCH_VERTICAL));
    JS_SetModuleExport(ctx, m, "NPATCH_THREE_PATCH_HORIZONTAL", JS_NewInt32(ctx, NPATCH_THREE_PATCH_HORIZONTAL));
    JS_SetModuleExport(ctx, m, "RAYLIB_VERSION_MAJOR", JS_NewInt32(ctx, RAYLIB_VERSION_MAJOR));
    JS_SetModuleExport(ctx, m, "RAYLIB_VERSION_MINOR", JS_NewInt32(ctx, RAYLIB_VERSION_MINOR));
    JS_SetModuleExport(ctx, m, "RAYLIB_VERSION_PATCH", JS_NewInt32(ctx, RAYLIB_VERSION_PATCH));
    JS_SetModuleExport(ctx, m, "PI", JS_NewFloat64(ctx, PI));
    Color LIGHTGRAY_struct = { 200, 200, 200, 255 };
    Color* ptr_LIGHTGRAY_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_LIGHTGRAY_js = LIGHTGRAY_struct;
    JSValue LIGHTGRAY_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(LIGHTGRAY_js, ptr_LIGHTGRAY_js);
    JS_SetModuleExport(ctx, m, "LIGHTGRAY", LIGHTGRAY_js);
    Color GRAY_struct = { 130, 130, 130, 255 };
    Color* ptr_GRAY_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_GRAY_js = GRAY_struct;
    JSValue GRAY_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(GRAY_js, ptr_GRAY_js);
    JS_SetModuleExport(ctx, m, "GRAY", GRAY_js);
    Color DARKGRAY_struct = { 80, 80, 80, 255 };
    Color* ptr_DARKGRAY_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_DARKGRAY_js = DARKGRAY_struct;
    JSValue DARKGRAY_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(DARKGRAY_js, ptr_DARKGRAY_js);
    JS_SetModuleExport(ctx, m, "DARKGRAY", DARKGRAY_js);
    Color YELLOW_struct = { 253, 249, 0, 255 };
    Color* ptr_YELLOW_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_YELLOW_js = YELLOW_struct;
    JSValue YELLOW_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(YELLOW_js, ptr_YELLOW_js);
    JS_SetModuleExport(ctx, m, "YELLOW", YELLOW_js);
    Color GOLD_struct = { 255, 203, 0, 255 };
    Color* ptr_GOLD_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_GOLD_js = GOLD_struct;
    JSValue GOLD_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(GOLD_js, ptr_GOLD_js);
    JS_SetModuleExport(ctx, m, "GOLD", GOLD_js);
    Color ORANGE_struct = { 255, 161, 0, 255 };
    Color* ptr_ORANGE_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ORANGE_js = ORANGE_struct;
    JSValue ORANGE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ORANGE_js, ptr_ORANGE_js);
    JS_SetModuleExport(ctx, m, "ORANGE", ORANGE_js);
    Color PINK_struct = { 255, 109, 194, 255 };
    Color* ptr_PINK_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_PINK_js = PINK_struct;
    JSValue PINK_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(PINK_js, ptr_PINK_js);
    JS_SetModuleExport(ctx, m, "PINK", PINK_js);
    Color RED_struct = { 230, 41, 55, 255 };
    Color* ptr_RED_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_RED_js = RED_struct;
    JSValue RED_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(RED_js, ptr_RED_js);
    JS_SetModuleExport(ctx, m, "RED", RED_js);
    Color MAROON_struct = { 190, 33, 55, 255 };
    Color* ptr_MAROON_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_MAROON_js = MAROON_struct;
    JSValue MAROON_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(MAROON_js, ptr_MAROON_js);
    JS_SetModuleExport(ctx, m, "MAROON", MAROON_js);
    Color GREEN_struct = { 0, 228, 48, 255 };
    Color* ptr_GREEN_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_GREEN_js = GREEN_struct;
    JSValue GREEN_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(GREEN_js, ptr_GREEN_js);
    JS_SetModuleExport(ctx, m, "GREEN", GREEN_js);
    Color LIME_struct = { 0, 158, 47, 255 };
    Color* ptr_LIME_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_LIME_js = LIME_struct;
    JSValue LIME_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(LIME_js, ptr_LIME_js);
    JS_SetModuleExport(ctx, m, "LIME", LIME_js);
    Color DARKGREEN_struct = { 0, 117, 44, 255 };
    Color* ptr_DARKGREEN_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_DARKGREEN_js = DARKGREEN_struct;
    JSValue DARKGREEN_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(DARKGREEN_js, ptr_DARKGREEN_js);
    JS_SetModuleExport(ctx, m, "DARKGREEN", DARKGREEN_js);
    Color SKYBLUE_struct = { 102, 191, 255, 255 };
    Color* ptr_SKYBLUE_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_SKYBLUE_js = SKYBLUE_struct;
    JSValue SKYBLUE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(SKYBLUE_js, ptr_SKYBLUE_js);
    JS_SetModuleExport(ctx, m, "SKYBLUE", SKYBLUE_js);
    Color BLUE_struct = { 0, 121, 241, 255 };
    Color* ptr_BLUE_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_BLUE_js = BLUE_struct;
    JSValue BLUE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(BLUE_js, ptr_BLUE_js);
    JS_SetModuleExport(ctx, m, "BLUE", BLUE_js);
    Color DARKBLUE_struct = { 0, 82, 172, 255 };
    Color* ptr_DARKBLUE_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_DARKBLUE_js = DARKBLUE_struct;
    JSValue DARKBLUE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(DARKBLUE_js, ptr_DARKBLUE_js);
    JS_SetModuleExport(ctx, m, "DARKBLUE", DARKBLUE_js);
    Color PURPLE_struct = { 200, 122, 255, 255 };
    Color* ptr_PURPLE_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_PURPLE_js = PURPLE_struct;
    JSValue PURPLE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(PURPLE_js, ptr_PURPLE_js);
    JS_SetModuleExport(ctx, m, "PURPLE", PURPLE_js);
    Color VIOLET_struct = { 135, 60, 190, 255 };
    Color* ptr_VIOLET_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_VIOLET_js = VIOLET_struct;
    JSValue VIOLET_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(VIOLET_js, ptr_VIOLET_js);
    JS_SetModuleExport(ctx, m, "VIOLET", VIOLET_js);
    Color DARKPURPLE_struct = { 112, 31, 126, 255 };
    Color* ptr_DARKPURPLE_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_DARKPURPLE_js = DARKPURPLE_struct;
    JSValue DARKPURPLE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(DARKPURPLE_js, ptr_DARKPURPLE_js);
    JS_SetModuleExport(ctx, m, "DARKPURPLE", DARKPURPLE_js);
    Color BEIGE_struct = { 211, 176, 131, 255 };
    Color* ptr_BEIGE_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_BEIGE_js = BEIGE_struct;
    JSValue BEIGE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(BEIGE_js, ptr_BEIGE_js);
    JS_SetModuleExport(ctx, m, "BEIGE", BEIGE_js);
    Color BROWN_struct = { 127, 106, 79, 255 };
    Color* ptr_BROWN_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_BROWN_js = BROWN_struct;
    JSValue BROWN_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(BROWN_js, ptr_BROWN_js);
    JS_SetModuleExport(ctx, m, "BROWN", BROWN_js);
    Color DARKBROWN_struct = { 76, 63, 47, 255 };
    Color* ptr_DARKBROWN_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_DARKBROWN_js = DARKBROWN_struct;
    JSValue DARKBROWN_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(DARKBROWN_js, ptr_DARKBROWN_js);
    JS_SetModuleExport(ctx, m, "DARKBROWN", DARKBROWN_js);
    Color WHITE_struct = { 255, 255, 255, 255 };
    Color* ptr_WHITE_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_WHITE_js = WHITE_struct;
    JSValue WHITE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(WHITE_js, ptr_WHITE_js);
    JS_SetModuleExport(ctx, m, "WHITE", WHITE_js);
    Color BLACK_struct = { 0, 0, 0, 255 };
    Color* ptr_BLACK_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_BLACK_js = BLACK_struct;
    JSValue BLACK_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(BLACK_js, ptr_BLACK_js);
    JS_SetModuleExport(ctx, m, "BLACK", BLACK_js);
    Color BLANK_struct = { 0, 0, 0, 0 };
    Color* ptr_BLANK_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_BLANK_js = BLANK_struct;
    JSValue BLANK_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(BLANK_js, ptr_BLANK_js);
    JS_SetModuleExport(ctx, m, "BLANK", BLANK_js);
    Color MAGENTA_struct = { 255, 0, 255, 255 };
    Color* ptr_MAGENTA_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_MAGENTA_js = MAGENTA_struct;
    JSValue MAGENTA_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(MAGENTA_js, ptr_MAGENTA_js);
    JS_SetModuleExport(ctx, m, "MAGENTA", MAGENTA_js);
    Color RAYWHITE_struct = { 245, 245, 245, 255 };
    Color* ptr_RAYWHITE_js = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_RAYWHITE_js = RAYWHITE_struct;
    JSValue RAYWHITE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(RAYWHITE_js, ptr_RAYWHITE_js);
    JS_SetModuleExport(ctx, m, "RAYWHITE", RAYWHITE_js);
    JS_SetModuleExport(ctx, m, "MOUSE_LEFT_BUTTON", JS_NewInt32(ctx, MOUSE_LEFT_BUTTON));
    JS_SetModuleExport(ctx, m, "MOUSE_RIGHT_BUTTON", JS_NewInt32(ctx, MOUSE_RIGHT_BUTTON));
    JS_SetModuleExport(ctx, m, "MOUSE_MIDDLE_BUTTON", JS_NewInt32(ctx, MOUSE_MIDDLE_BUTTON));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_DIFFUSE", JS_NewInt32(ctx, MATERIAL_MAP_DIFFUSE));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_SPECULAR", JS_NewInt32(ctx, MATERIAL_MAP_SPECULAR));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_DIFFUSE", JS_NewInt32(ctx, SHADER_LOC_MAP_DIFFUSE));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_SPECULAR", JS_NewInt32(ctx, SHADER_LOC_MAP_SPECULAR));
    return 0;
}

JSModuleDef * js_init_module_js_raylib(JSContext * ctx, const char * module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_js_raylib_init);
    if(!m) return NULL;
    JS_AddModuleExportList(ctx, m, js_js_raylib_funcs, countof(js_js_raylib_funcs));
    JS_AddModuleExport(ctx, m, "Vector2");
    JS_AddModuleExport(ctx, m, "Vector3");
    JS_AddModuleExport(ctx, m, "Vector4");
    JS_AddModuleExport(ctx, m, "Color");
    JS_AddModuleExport(ctx, m, "Rectangle");
    JS_AddModuleExport(ctx, m, "Image");
    JS_AddModuleExport(ctx, m, "NPatchInfo");
    JS_AddModuleExport(ctx, m, "Camera3D");
    JS_AddModuleExport(ctx, m, "Camera2D");
    JS_AddModuleExport(ctx, m, "Mesh");
    JS_AddModuleExport(ctx, m, "Ray");
    JS_AddModuleExport(ctx, m, "BoundingBox");
    JS_AddModuleExport(ctx, m, "VrDeviceInfo");
    JS_AddModuleExport(ctx, m, "false");
    JS_AddModuleExport(ctx, m, "true");
    JS_AddModuleExport(ctx, m, "FLAG_VSYNC_HINT");
    JS_AddModuleExport(ctx, m, "FLAG_FULLSCREEN_MODE");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_RESIZABLE");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_UNDECORATED");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_HIDDEN");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_MINIMIZED");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_MAXIMIZED");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_UNFOCUSED");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_TOPMOST");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_ALWAYS_RUN");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_TRANSPARENT");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_HIGHDPI");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_MOUSE_PASSTHROUGH");
    JS_AddModuleExport(ctx, m, "FLAG_BORDERLESS_WINDOWED_MODE");
    JS_AddModuleExport(ctx, m, "FLAG_MSAA_4X_HINT");
    JS_AddModuleExport(ctx, m, "FLAG_INTERLACED_HINT");
    JS_AddModuleExport(ctx, m, "LOG_ALL");
    JS_AddModuleExport(ctx, m, "LOG_TRACE");
    JS_AddModuleExport(ctx, m, "LOG_DEBUG");
    JS_AddModuleExport(ctx, m, "LOG_INFO");
    JS_AddModuleExport(ctx, m, "LOG_WARNING");
    JS_AddModuleExport(ctx, m, "LOG_ERROR");
    JS_AddModuleExport(ctx, m, "LOG_FATAL");
    JS_AddModuleExport(ctx, m, "LOG_NONE");
    JS_AddModuleExport(ctx, m, "KEY_NULL");
    JS_AddModuleExport(ctx, m, "KEY_APOSTROPHE");
    JS_AddModuleExport(ctx, m, "KEY_COMMA");
    JS_AddModuleExport(ctx, m, "KEY_MINUS");
    JS_AddModuleExport(ctx, m, "KEY_PERIOD");
    JS_AddModuleExport(ctx, m, "KEY_SLASH");
    JS_AddModuleExport(ctx, m, "KEY_ZERO");
    JS_AddModuleExport(ctx, m, "KEY_ONE");
    JS_AddModuleExport(ctx, m, "KEY_TWO");
    JS_AddModuleExport(ctx, m, "KEY_THREE");
    JS_AddModuleExport(ctx, m, "KEY_FOUR");
    JS_AddModuleExport(ctx, m, "KEY_FIVE");
    JS_AddModuleExport(ctx, m, "KEY_SIX");
    JS_AddModuleExport(ctx, m, "KEY_SEVEN");
    JS_AddModuleExport(ctx, m, "KEY_EIGHT");
    JS_AddModuleExport(ctx, m, "KEY_NINE");
    JS_AddModuleExport(ctx, m, "KEY_SEMICOLON");
    JS_AddModuleExport(ctx, m, "KEY_EQUAL");
    JS_AddModuleExport(ctx, m, "KEY_A");
    JS_AddModuleExport(ctx, m, "KEY_B");
    JS_AddModuleExport(ctx, m, "KEY_C");
    JS_AddModuleExport(ctx, m, "KEY_D");
    JS_AddModuleExport(ctx, m, "KEY_E");
    JS_AddModuleExport(ctx, m, "KEY_F");
    JS_AddModuleExport(ctx, m, "KEY_G");
    JS_AddModuleExport(ctx, m, "KEY_H");
    JS_AddModuleExport(ctx, m, "KEY_I");
    JS_AddModuleExport(ctx, m, "KEY_J");
    JS_AddModuleExport(ctx, m, "KEY_K");
    JS_AddModuleExport(ctx, m, "KEY_L");
    JS_AddModuleExport(ctx, m, "KEY_M");
    JS_AddModuleExport(ctx, m, "KEY_N");
    JS_AddModuleExport(ctx, m, "KEY_O");
    JS_AddModuleExport(ctx, m, "KEY_P");
    JS_AddModuleExport(ctx, m, "KEY_Q");
    JS_AddModuleExport(ctx, m, "KEY_R");
    JS_AddModuleExport(ctx, m, "KEY_S");
    JS_AddModuleExport(ctx, m, "KEY_T");
    JS_AddModuleExport(ctx, m, "KEY_U");
    JS_AddModuleExport(ctx, m, "KEY_V");
    JS_AddModuleExport(ctx, m, "KEY_W");
    JS_AddModuleExport(ctx, m, "KEY_X");
    JS_AddModuleExport(ctx, m, "KEY_Y");
    JS_AddModuleExport(ctx, m, "KEY_Z");
    JS_AddModuleExport(ctx, m, "KEY_LEFT_BRACKET");
    JS_AddModuleExport(ctx, m, "KEY_BACKSLASH");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT_BRACKET");
    JS_AddModuleExport(ctx, m, "KEY_GRAVE");
    JS_AddModuleExport(ctx, m, "KEY_SPACE");
    JS_AddModuleExport(ctx, m, "KEY_ESCAPE");
    JS_AddModuleExport(ctx, m, "KEY_ENTER");
    JS_AddModuleExport(ctx, m, "KEY_TAB");
    JS_AddModuleExport(ctx, m, "KEY_BACKSPACE");
    JS_AddModuleExport(ctx, m, "KEY_INSERT");
    JS_AddModuleExport(ctx, m, "KEY_DELETE");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT");
    JS_AddModuleExport(ctx, m, "KEY_LEFT");
    JS_AddModuleExport(ctx, m, "KEY_DOWN");
    JS_AddModuleExport(ctx, m, "KEY_UP");
    JS_AddModuleExport(ctx, m, "KEY_PAGE_UP");
    JS_AddModuleExport(ctx, m, "KEY_PAGE_DOWN");
    JS_AddModuleExport(ctx, m, "KEY_HOME");
    JS_AddModuleExport(ctx, m, "KEY_END");
    JS_AddModuleExport(ctx, m, "KEY_CAPS_LOCK");
    JS_AddModuleExport(ctx, m, "KEY_SCROLL_LOCK");
    JS_AddModuleExport(ctx, m, "KEY_NUM_LOCK");
    JS_AddModuleExport(ctx, m, "KEY_PRINT_SCREEN");
    JS_AddModuleExport(ctx, m, "KEY_PAUSE");
    JS_AddModuleExport(ctx, m, "KEY_F1");
    JS_AddModuleExport(ctx, m, "KEY_F2");
    JS_AddModuleExport(ctx, m, "KEY_F3");
    JS_AddModuleExport(ctx, m, "KEY_F4");
    JS_AddModuleExport(ctx, m, "KEY_F5");
    JS_AddModuleExport(ctx, m, "KEY_F6");
    JS_AddModuleExport(ctx, m, "KEY_F7");
    JS_AddModuleExport(ctx, m, "KEY_F8");
    JS_AddModuleExport(ctx, m, "KEY_F9");
    JS_AddModuleExport(ctx, m, "KEY_F10");
    JS_AddModuleExport(ctx, m, "KEY_F11");
    JS_AddModuleExport(ctx, m, "KEY_F12");
    JS_AddModuleExport(ctx, m, "KEY_LEFT_SHIFT");
    JS_AddModuleExport(ctx, m, "KEY_LEFT_CONTROL");
    JS_AddModuleExport(ctx, m, "KEY_LEFT_ALT");
    JS_AddModuleExport(ctx, m, "KEY_LEFT_SUPER");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT_SHIFT");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT_CONTROL");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT_ALT");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT_SUPER");
    JS_AddModuleExport(ctx, m, "KEY_KB_MENU");
    JS_AddModuleExport(ctx, m, "KEY_KP_0");
    JS_AddModuleExport(ctx, m, "KEY_KP_1");
    JS_AddModuleExport(ctx, m, "KEY_KP_2");
    JS_AddModuleExport(ctx, m, "KEY_KP_3");
    JS_AddModuleExport(ctx, m, "KEY_KP_4");
    JS_AddModuleExport(ctx, m, "KEY_KP_5");
    JS_AddModuleExport(ctx, m, "KEY_KP_6");
    JS_AddModuleExport(ctx, m, "KEY_KP_7");
    JS_AddModuleExport(ctx, m, "KEY_KP_8");
    JS_AddModuleExport(ctx, m, "KEY_KP_9");
    JS_AddModuleExport(ctx, m, "KEY_KP_DECIMAL");
    JS_AddModuleExport(ctx, m, "KEY_KP_DIVIDE");
    JS_AddModuleExport(ctx, m, "KEY_KP_MULTIPLY");
    JS_AddModuleExport(ctx, m, "KEY_KP_SUBTRACT");
    JS_AddModuleExport(ctx, m, "KEY_KP_ADD");
    JS_AddModuleExport(ctx, m, "KEY_KP_ENTER");
    JS_AddModuleExport(ctx, m, "KEY_KP_EQUAL");
    JS_AddModuleExport(ctx, m, "KEY_BACK");
    JS_AddModuleExport(ctx, m, "KEY_MENU");
    JS_AddModuleExport(ctx, m, "KEY_VOLUME_UP");
    JS_AddModuleExport(ctx, m, "KEY_VOLUME_DOWN");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_LEFT");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_RIGHT");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_MIDDLE");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_SIDE");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_EXTRA");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_FORWARD");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_BACK");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_DEFAULT");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_ARROW");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_IBEAM");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_CROSSHAIR");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_POINTING_HAND");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_EW");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NS");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NWSE");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NESW");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_ALL");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_NOT_ALLOWED");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_UNKNOWN");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_UP");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_RIGHT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_DOWN");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_LEFT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_UP");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_DOWN");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_LEFT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_TRIGGER_1");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_TRIGGER_2");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_TRIGGER_1");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_TRIGGER_2");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE_LEFT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE_RIGHT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_THUMB");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_THUMB");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_X");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_Y");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_X");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_Y");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_TRIGGER");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_TRIGGER");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_ALBEDO");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_METALNESS");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_NORMAL");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_ROUGHNESS");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_OCCLUSION");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_EMISSION");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_HEIGHT");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_CUBEMAP");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_IRRADIANCE");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_PREFILTER");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_BRDF");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_POSITION");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_TEXCOORD01");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_TEXCOORD02");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_NORMAL");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_TANGENT");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_COLOR");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MATRIX_MVP");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MATRIX_VIEW");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MATRIX_PROJECTION");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MATRIX_MODEL");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MATRIX_NORMAL");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VECTOR_VIEW");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_COLOR_DIFFUSE");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_COLOR_SPECULAR");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_COLOR_AMBIENT");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_ALBEDO");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_METALNESS");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_NORMAL");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_ROUGHNESS");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_OCCLUSION");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_EMISSION");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_HEIGHT");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_CUBEMAP");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_IRRADIANCE");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_PREFILTER");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_BRDF");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_BONEIDS");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_BONEWEIGHTS");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_BONE_MATRICES");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_INSTANCE_TX");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_FLOAT");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_VEC2");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_VEC3");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_VEC4");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_INT");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_IVEC2");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_IVEC3");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_IVEC4");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_UINT");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_UIVEC2");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_UIVEC3");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_UIVEC4");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_SAMPLER2D");
    JS_AddModuleExport(ctx, m, "SHADER_ATTRIB_FLOAT");
    JS_AddModuleExport(ctx, m, "SHADER_ATTRIB_VEC2");
    JS_AddModuleExport(ctx, m, "SHADER_ATTRIB_VEC3");
    JS_AddModuleExport(ctx, m, "SHADER_ATTRIB_VEC4");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_GRAYSCALE");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R5G6B5");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R8G8B8");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R5G5B5A1");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R4G4B4A4");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R8G8B8A8");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32G32B32");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32G32B32A32");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16G16B16");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16G16B16A16");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT1_RGB");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT1_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT3_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT5_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC1_RGB");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC2_RGB");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_PVRT_RGB");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_PVRT_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_POINT");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_BILINEAR");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_TRILINEAR");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_4X");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_8X");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_16X");
    JS_AddModuleExport(ctx, m, "TEXTURE_WRAP_REPEAT");
    JS_AddModuleExport(ctx, m, "TEXTURE_WRAP_CLAMP");
    JS_AddModuleExport(ctx, m, "TEXTURE_WRAP_MIRROR_REPEAT");
    JS_AddModuleExport(ctx, m, "TEXTURE_WRAP_MIRROR_CLAMP");
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_AUTO_DETECT");
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_LINE_VERTICAL");
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_LINE_HORIZONTAL");
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR");
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE");
    JS_AddModuleExport(ctx, m, "FONT_DEFAULT");
    JS_AddModuleExport(ctx, m, "FONT_BITMAP");
    JS_AddModuleExport(ctx, m, "FONT_SDF");
    JS_AddModuleExport(ctx, m, "BLEND_ALPHA");
    JS_AddModuleExport(ctx, m, "BLEND_ADDITIVE");
    JS_AddModuleExport(ctx, m, "BLEND_MULTIPLIED");
    JS_AddModuleExport(ctx, m, "BLEND_ADD_COLORS");
    JS_AddModuleExport(ctx, m, "BLEND_SUBTRACT_COLORS");
    JS_AddModuleExport(ctx, m, "BLEND_ALPHA_PREMULTIPLY");
    JS_AddModuleExport(ctx, m, "BLEND_CUSTOM");
    JS_AddModuleExport(ctx, m, "BLEND_CUSTOM_SEPARATE");
    JS_AddModuleExport(ctx, m, "GESTURE_NONE");
    JS_AddModuleExport(ctx, m, "GESTURE_TAP");
    JS_AddModuleExport(ctx, m, "GESTURE_DOUBLETAP");
    JS_AddModuleExport(ctx, m, "GESTURE_HOLD");
    JS_AddModuleExport(ctx, m, "GESTURE_DRAG");
    JS_AddModuleExport(ctx, m, "GESTURE_SWIPE_RIGHT");
    JS_AddModuleExport(ctx, m, "GESTURE_SWIPE_LEFT");
    JS_AddModuleExport(ctx, m, "GESTURE_SWIPE_UP");
    JS_AddModuleExport(ctx, m, "GESTURE_SWIPE_DOWN");
    JS_AddModuleExport(ctx, m, "GESTURE_PINCH_IN");
    JS_AddModuleExport(ctx, m, "GESTURE_PINCH_OUT");
    JS_AddModuleExport(ctx, m, "CAMERA_CUSTOM");
    JS_AddModuleExport(ctx, m, "CAMERA_FREE");
    JS_AddModuleExport(ctx, m, "CAMERA_ORBITAL");
    JS_AddModuleExport(ctx, m, "CAMERA_FIRST_PERSON");
    JS_AddModuleExport(ctx, m, "CAMERA_THIRD_PERSON");
    JS_AddModuleExport(ctx, m, "CAMERA_PERSPECTIVE");
    JS_AddModuleExport(ctx, m, "CAMERA_ORTHOGRAPHIC");
    JS_AddModuleExport(ctx, m, "NPATCH_NINE_PATCH");
    JS_AddModuleExport(ctx, m, "NPATCH_THREE_PATCH_VERTICAL");
    JS_AddModuleExport(ctx, m, "NPATCH_THREE_PATCH_HORIZONTAL");
    JS_AddModuleExport(ctx, m, "RAYLIB_VERSION_MAJOR");
    JS_AddModuleExport(ctx, m, "RAYLIB_VERSION_MINOR");
    JS_AddModuleExport(ctx, m, "RAYLIB_VERSION_PATCH");
    JS_AddModuleExport(ctx, m, "PI");
    JS_AddModuleExport(ctx, m, "LIGHTGRAY");
    JS_AddModuleExport(ctx, m, "GRAY");
    JS_AddModuleExport(ctx, m, "DARKGRAY");
    JS_AddModuleExport(ctx, m, "YELLOW");
    JS_AddModuleExport(ctx, m, "GOLD");
    JS_AddModuleExport(ctx, m, "ORANGE");
    JS_AddModuleExport(ctx, m, "PINK");
    JS_AddModuleExport(ctx, m, "RED");
    JS_AddModuleExport(ctx, m, "MAROON");
    JS_AddModuleExport(ctx, m, "GREEN");
    JS_AddModuleExport(ctx, m, "LIME");
    JS_AddModuleExport(ctx, m, "DARKGREEN");
    JS_AddModuleExport(ctx, m, "SKYBLUE");
    JS_AddModuleExport(ctx, m, "BLUE");
    JS_AddModuleExport(ctx, m, "DARKBLUE");
    JS_AddModuleExport(ctx, m, "PURPLE");
    JS_AddModuleExport(ctx, m, "VIOLET");
    JS_AddModuleExport(ctx, m, "DARKPURPLE");
    JS_AddModuleExport(ctx, m, "BEIGE");
    JS_AddModuleExport(ctx, m, "BROWN");
    JS_AddModuleExport(ctx, m, "DARKBROWN");
    JS_AddModuleExport(ctx, m, "WHITE");
    JS_AddModuleExport(ctx, m, "BLACK");
    JS_AddModuleExport(ctx, m, "BLANK");
    JS_AddModuleExport(ctx, m, "MAGENTA");
    JS_AddModuleExport(ctx, m, "RAYWHITE");
    JS_AddModuleExport(ctx, m, "MOUSE_LEFT_BUTTON");
    JS_AddModuleExport(ctx, m, "MOUSE_RIGHT_BUTTON");
    JS_AddModuleExport(ctx, m, "MOUSE_MIDDLE_BUTTON");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_DIFFUSE");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_SPECULAR");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_DIFFUSE");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_SPECULAR");
    return m;
}

#endif // JS_js_raylib_GUARD
