#ifndef JS_js_rlightmapper_GUARD
#define JS_js_rlightmapper_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <quickjs.h>
#include <rayjs_base.h>
#define RLIGHTMAPPER_IMPLEMENTATION
#include <rlightmapper.h>
#include <raylib.h>

static JSClassID js_Lightmapper_class_id;
static JSClassID js_LightmapperConfig_class_id;
static JSClassID js_Lightmapper_class_id;
static JSClassID js_LightmapperConfig_class_id;

static void js_Lightmapper_finalizer(JSRuntime * rt, JSValue val) {
    Lightmapper* ptr = JS_GetOpaque(val, js_Lightmapper_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Lightmapper_get_w(JSContext* ctx, JSValue this_val) {
    Lightmapper* ptr = JS_GetOpaque2(ctx, this_val, js_Lightmapper_class_id);
    int w = ptr->w;
    JSValue ret = JS_NewInt32(ctx, (long)w);
    return ret;
}

static JSValue js_Lightmapper_get_h(JSContext* ctx, JSValue this_val) {
    Lightmapper* ptr = JS_GetOpaque2(ctx, this_val, js_Lightmapper_class_id);
    int h = ptr->h;
    JSValue ret = JS_NewInt32(ctx, (long)h);
    return ret;
}

static JSValue js_Lightmapper_get_progress(JSContext* ctx, JSValue this_val) {
    Lightmapper* ptr = JS_GetOpaque2(ctx, this_val, js_Lightmapper_class_id);
    float progress = ptr->progress;
    JSValue ret = JS_NewFloat64(ctx, (double)progress);
    return ret;
}

static const JSCFunctionListEntry js_Lightmapper_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Lightmapper", JS_PROP_CONFIGURABLE),
    JS_CGETSET_DEF("w",js_Lightmapper_get_w,NULL),
    JS_CGETSET_DEF("h",js_Lightmapper_get_h,NULL),
    JS_CGETSET_DEF("progress",js_Lightmapper_get_progress,NULL),
};

static int js_declare_Lightmapper(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Lightmapper_class_id);
    JSClassDef js_Lightmapper_def = { .class_name = "Lightmapper", .finalizer = js_Lightmapper_finalizer };
    JS_NewClass(rt, js_Lightmapper_class_id, &js_Lightmapper_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Lightmapper_proto_funcs, countof(js_Lightmapper_proto_funcs));
    JS_SetClassProto(ctx, js_Lightmapper_class_id, proto);
    return 0;
}

static void js_LightmapperConfig_finalizer(JSRuntime * rt, JSValue val) {
    LightmapperConfig* ptr = JS_GetOpaque(val, js_LightmapperConfig_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_LightmapperConfig_get_hemisphereSize(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    int hemisphereSize = ptr->hemisphereSize;
    JSValue ret = JS_NewInt32(ctx, (long)hemisphereSize);
    return ret;
}

static JSValue js_LightmapperConfig_set_hemisphereSize(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->hemisphereSize = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_zNear(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    float zNear = ptr->zNear;
    JSValue ret = JS_NewFloat64(ctx, (double)zNear);
    return ret;
}

static JSValue js_LightmapperConfig_set_zNear(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->zNear = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_zFar(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    float zFar = ptr->zFar;
    JSValue ret = JS_NewFloat64(ctx, (double)zFar);
    return ret;
}

static JSValue js_LightmapperConfig_set_zFar(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->zFar = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_backgroundColor(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    Color backgroundColor = ptr->backgroundColor;
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = backgroundColor;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LightmapperConfig_set_backgroundColor(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    Color* ptr_value = (Color*)JS_GetOpaque(v, js_Color_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Color value = *ptr_value;
    ptr->backgroundColor = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_interpolationPasses(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    int interpolationPasses = ptr->interpolationPasses;
    JSValue ret = JS_NewInt32(ctx, (long)interpolationPasses);
    return ret;
}

static JSValue js_LightmapperConfig_set_interpolationPasses(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->interpolationPasses = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_interpolationThreshold(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    float interpolationThreshold = ptr->interpolationThreshold;
    JSValue ret = JS_NewFloat64(ctx, (double)interpolationThreshold);
    return ret;
}

static JSValue js_LightmapperConfig_set_interpolationThreshold(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->interpolationThreshold = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_cameraToSurfaceDistanceModifier(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    float cameraToSurfaceDistanceModifier = ptr->cameraToSurfaceDistanceModifier;
    JSValue ret = JS_NewFloat64(ctx, (double)cameraToSurfaceDistanceModifier);
    return ret;
}

static JSValue js_LightmapperConfig_set_cameraToSurfaceDistanceModifier(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->cameraToSurfaceDistanceModifier = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_LightmapperConfig_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","LightmapperConfig", JS_PROP_CONFIGURABLE),
    JS_CGETSET_DEF("hemisphereSize",js_LightmapperConfig_get_hemisphereSize,js_LightmapperConfig_set_hemisphereSize),
    JS_CGETSET_DEF("zNear",js_LightmapperConfig_get_zNear,js_LightmapperConfig_set_zNear),
    JS_CGETSET_DEF("zFar",js_LightmapperConfig_get_zFar,js_LightmapperConfig_set_zFar),
    JS_CGETSET_DEF("backgroundColor",js_LightmapperConfig_get_backgroundColor,js_LightmapperConfig_set_backgroundColor),
    JS_CGETSET_DEF("interpolationPasses",js_LightmapperConfig_get_interpolationPasses,js_LightmapperConfig_set_interpolationPasses),
    JS_CGETSET_DEF("interpolationThreshold",js_LightmapperConfig_get_interpolationThreshold,js_LightmapperConfig_set_interpolationThreshold),
    JS_CGETSET_DEF("cameraToSurfaceDistanceModifier",js_LightmapperConfig_get_cameraToSurfaceDistanceModifier,js_LightmapperConfig_set_cameraToSurfaceDistanceModifier),
};

static int js_declare_LightmapperConfig(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_LightmapperConfig_class_id);
    JSClassDef js_LightmapperConfig_def = { .class_name = "LightmapperConfig", .finalizer = js_LightmapperConfig_finalizer };
    JS_NewClass(rt, js_LightmapperConfig_class_id, &js_LightmapperConfig_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_LightmapperConfig_proto_funcs, countof(js_LightmapperConfig_proto_funcs));
    JS_SetClassProto(ctx, js_LightmapperConfig_class_id, proto);
    return 0;
}

static JSValue js_GetDefaultLightmapperConfig(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    LightmapperConfig returnVal = GetDefaultLightmapperConfig();
    LightmapperConfig* ptr_ret = (LightmapperConfig*)js_malloc(ctx, sizeof(LightmapperConfig));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_LightmapperConfig_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadLightmapper(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_w;
    int err_w = JS_ToInt32(ctx, &long_w, argv[0]);
    if(err_w<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int w = (int)long_w;
    int32_t long_h;
    int err_h = JS_ToInt32(ctx, &long_h, argv[1]);
    if(err_h<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int h = (int)long_h;
    Mesh* ptr_mesh = (Mesh*)JS_GetOpaque(argv[2], js_Mesh_class_id);
    if(ptr_mesh == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Mesh mesh = *ptr_mesh;
    LightmapperConfig* ptr_cfg = (LightmapperConfig*)JS_GetOpaque(argv[3], js_LightmapperConfig_class_id);
    if(ptr_cfg == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    LightmapperConfig cfg = *ptr_cfg;
    Lightmapper returnVal = LoadLightmapper(w, h, mesh, cfg);
    Lightmapper* ptr_ret = (Lightmapper*)js_malloc(ctx, sizeof(Lightmapper));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Lightmapper_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_LoadMaterialLightmapper(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* ptr_emissiveColor = (Color*)JS_GetOpaque(argv[0], js_Color_class_id);
    if(ptr_emissiveColor == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Color emissiveColor = *ptr_emissiveColor;
    double double_intensity;
    int err_intensity = JS_ToFloat64(ctx, &double_intensity, argv[1]);
    if(err_intensity<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float intensity = (float)double_intensity;
    Material returnVal = LoadMaterialLightmapper(emissiveColor, intensity);
    Material* ptr_ret = (Material*)js_malloc(ctx, sizeof(Material));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Material_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_UnloadLightmapper(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Lightmapper* ptr_lm = (Lightmapper*)JS_GetOpaque(argv[0], js_Lightmapper_class_id);
    if(ptr_lm == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Lightmapper lm = *ptr_lm;
    UnloadLightmapper(lm);
    return JS_UNDEFINED;
}

static JSValue js_BeginLightmap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    BeginLightmap();
    return JS_UNDEFINED;
}

static JSValue js_EndLightmap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndLightmap();
    return JS_UNDEFINED;
}

static JSValue js_BeginLightmapFragment(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Lightmapper * lm = (Lightmapper *)JS_GetOpaque(argv[0], js_Lightmapper_class_id);
    if(lm == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Lightmapper");
        return JS_EXCEPTION;
    }
    bool returnVal = BeginLightmapFragment(lm);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_EndLightmapFragment(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Lightmapper * lm = (Lightmapper *)JS_GetOpaque(argv[0], js_Lightmapper_class_id);
    if(lm == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Lightmapper");
        return JS_EXCEPTION;
    }
    EndLightmapFragment(lm);
    return JS_UNDEFINED;
}

static JSValue js_LoadImageFromLightmapper(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Lightmapper* ptr_lm = (Lightmapper*)JS_GetOpaque(argv[0], js_Lightmapper_class_id);
    if(ptr_lm == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Lightmapper lm = *ptr_lm;
    Image returnVal = LoadImageFromLightmapper(lm);
    Image* ptr_ret = (Image*)js_malloc(ctx, sizeof(Image));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static const JSCFunctionListEntry js_js_rlightmapper_funcs[] = {
    JS_CFUNC_DEF("GetDefaultLightmapperConfig",0,js_GetDefaultLightmapperConfig),
    JS_CFUNC_DEF("LoadLightmapper",4,js_LoadLightmapper),
    JS_CFUNC_DEF("LoadMaterialLightmapper",2,js_LoadMaterialLightmapper),
    JS_CFUNC_DEF("UnloadLightmapper",1,js_UnloadLightmapper),
    JS_CFUNC_DEF("BeginLightmap",0,js_BeginLightmap),
    JS_CFUNC_DEF("EndLightmap",0,js_EndLightmap),
    JS_CFUNC_DEF("BeginLightmapFragment",1,js_BeginLightmapFragment),
    JS_CFUNC_DEF("EndLightmapFragment",1,js_EndLightmapFragment),
    JS_CFUNC_DEF("LoadImageFromLightmapper",1,js_LoadImageFromLightmapper),
};

static int js_js_rlightmapper_init(JSContext * ctx, JSModuleDef * m) {
    JS_SetModuleExportList(ctx, m,js_js_rlightmapper_funcs,countof(js_js_rlightmapper_funcs));
    js_declare_Lightmapper(ctx, m);
    js_declare_LightmapperConfig(ctx, m);
    return 0;
}

JSModuleDef * js_init_module_js_rlightmapper(JSContext * ctx, const char * module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_js_rlightmapper_init);
    if(!m) return NULL;
    JS_AddModuleExportList(ctx, m, js_js_rlightmapper_funcs, countof(js_js_rlightmapper_funcs));
    return m;
}

#endif // JS_js_rlightmapper_GUARD
