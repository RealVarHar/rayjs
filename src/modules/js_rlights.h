#ifndef JS_js_rlights_GUARD
#define JS_js_rlights_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <quickjs.h>
#include <rayjs_base.h>
#define RLIGHTS_IMPLEMENTATION
#include <rlights.h>
#include <raylib.h>

static JSClassID js_Light_class_id;
static JSClassID js_Light_class_id;

static void js_Light_finalizer(JSRuntime * rt, JSValue val) {
    Light* ptr = JS_GetOpaque(val, js_Light_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Light_get_type(JSContext* ctx, JSValue this_val) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    int type = ptr->type;
    JSValue ret = JS_NewInt32(ctx, (long)type);
    return ret;
}

static JSValue js_Light_set_type(JSContext* ctx, JSValue this_val, JSValue v) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    ptr->type = value;
    return JS_UNDEFINED;
}

static JSValue js_Light_get_enabled(JSContext* ctx, JSValue this_val) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    bool enabled = ptr->enabled;
    JSValue ret = JS_NewBool(ctx, enabled);
    return ret;
}

static JSValue js_Light_set_enabled(JSContext* ctx, JSValue this_val, JSValue v) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    int js_value = JS_ToBool(ctx, v);
    if(js_value<0) {
        JS_ThrowTypeError(ctx, "v is not a bool");
        return JS_EXCEPTION;
    }
    bool value = js_value;
    ptr->enabled = value;
    return JS_UNDEFINED;
}

static JSValue js_Light_get_position(JSContext* ctx, JSValue this_val) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Vector3 position = ptr->position;
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = position;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_Light_set_position(JSContext* ctx, JSValue this_val, JSValue v) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Vector3* ptr_value = (Vector3*)JS_GetOpaque(v, js_Vector3_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 value = *ptr_value;
    ptr->position = value;
    return JS_UNDEFINED;
}

static JSValue js_Light_get_target(JSContext* ctx, JSValue this_val) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Vector3 target = ptr->target;
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = target;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_Light_set_target(JSContext* ctx, JSValue this_val, JSValue v) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Vector3* ptr_value = (Vector3*)JS_GetOpaque(v, js_Vector3_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 value = *ptr_value;
    ptr->target = value;
    return JS_UNDEFINED;
}

static JSValue js_Light_get_color(JSContext* ctx, JSValue this_val) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Color color = ptr->color;
    Color* ptr_ret = (Color*)js_malloc(ctx, sizeof(Color));
    *ptr_ret = color;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_Light_set_color(JSContext* ctx, JSValue this_val, JSValue v) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Color* ptr_value = (Color*)JS_GetOpaque(v, js_Color_class_id);
    if(ptr_value == NULL) {
        JS_ThrowTypeError(ctx, "v does not allow null");
        return JS_EXCEPTION;
    }
    Color value = *ptr_value;
    ptr->color = value;
    return JS_UNDEFINED;
}

static JSValue js_Light_get_attenuation(JSContext* ctx, JSValue this_val) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    float attenuation = ptr->attenuation;
    JSValue ret = JS_NewFloat64(ctx, (double)attenuation);
    return ret;
}

static JSValue js_Light_set_attenuation(JSContext* ctx, JSValue this_val, JSValue v) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, v);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "v is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    ptr->attenuation = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Light_proto_funcs[] = {
    JS_CGETSET_DEF("type",js_Light_get_type,js_Light_set_type),
    JS_CGETSET_DEF("enabled",js_Light_get_enabled,js_Light_set_enabled),
    JS_CGETSET_DEF("position",js_Light_get_position,js_Light_set_position),
    JS_CGETSET_DEF("target",js_Light_get_target,js_Light_set_target),
    JS_CGETSET_DEF("color",js_Light_get_color,js_Light_set_color),
    JS_CGETSET_DEF("attenuation",js_Light_get_attenuation,js_Light_set_attenuation),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Light", JS_PROP_CONFIGURABLE),
};

static int js_declare_Light(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_Light_class_id);
    JSClassDef js_Light_def = { .class_name = "Light", .finalizer = js_Light_finalizer };
    JS_NewClass(rt, js_Light_class_id, &js_Light_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Light_proto_funcs, countof(js_Light_proto_funcs));
    JS_SetClassProto(ctx, js_Light_class_id, proto);
    return 0;
}

static JSValue js_CreateLight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_type;
    int err_type = JS_ToInt32(ctx, &long_type, argv[0]);
    if(err_type<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int type = (int)long_type;
    Vector3* ptr_position = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_position == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 position = *ptr_position;
    Vector3* ptr_target = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_target == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 target = *ptr_target;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[3], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    Shader* ptr_shader = (Shader*)JS_GetOpaque(argv[4], js_Shader_class_id);
    if(ptr_shader == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Shader shader = *ptr_shader;
    Light returnVal = CreateLight(type, position, target, color, shader);
    Light* ptr_ret = (Light*)js_malloc(ctx, sizeof(Light));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Light_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_UpdateLightValues(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* ptr_shader = (Shader*)JS_GetOpaque(argv[0], js_Shader_class_id);
    if(ptr_shader == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Shader shader = *ptr_shader;
    Light* ptr_light = (Light*)JS_GetOpaque(argv[1], js_Light_class_id);
    if(ptr_light == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Light light = *ptr_light;
    UpdateLightValues(shader, light);
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_js_rlights_funcs[] = {
    JS_CFUNC_DEF("CreateLight",5,js_CreateLight),
    JS_CFUNC_DEF("UpdateLightValues",2,js_UpdateLightValues),
};

static int js_js_rlights_init(JSContext * ctx, JSModuleDef * m) {
    JS_SetModuleExportList(ctx, m,js_js_rlights_funcs,countof(js_js_rlights_funcs));
    js_declare_Light(ctx, m);
    JS_SetModuleExport(ctx, m, "LIGHT_DIRECTIONAL", JS_NewInt32(ctx, LIGHT_DIRECTIONAL));
    JS_SetModuleExport(ctx, m, "LIGHT_POINT", JS_NewInt32(ctx, LIGHT_POINT));
    JS_SetModuleExport(ctx, m, "MAX_LIGHTS", JS_NewInt32(ctx, MAX_LIGHTS));
    return 0;
}

JSModuleDef * js_init_module_js_rlights(JSContext * ctx, const char * module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_js_rlights_init);
    if(!m) return NULL;
    JS_AddModuleExportList(ctx, m, js_js_rlights_funcs, countof(js_js_rlights_funcs));
    JS_AddModuleExport(ctx, m, "LIGHT_DIRECTIONAL");
    JS_AddModuleExport(ctx, m, "LIGHT_POINT");
    JS_AddModuleExport(ctx, m, "MAX_LIGHTS");
    return m;
}

#endif // JS_js_rlights_GUARD
