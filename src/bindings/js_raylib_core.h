#ifndef JS_raylib_core_GUARD
#define JS_raylib_core_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <quickjs.h>
#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#define RLIGHTS_IMPLEMENTATION
#include <rlights.h>
#include <reasings.h>
#define RLIGHTMAPPER_IMPLEMENTATION
#include <rlightmapper.h>

#ifndef countof
#define countof(x) (sizeof(x) / sizeof((x)[0]))
#endif
#ifndef dynamidMemoryAlloc
#define dynamidMemoryAlloc
typedef struct memoryNode{
    int length;
    void * pointers[6];
    struct memoryNode * next;
} memoryNode;
memoryNode* memoryStore(memoryNode *current, void * clarfunc, void * memoryptr) {
   // Saves memory fo de-allocation
   if(current->length < 6) {
        current->pointers[current->length] = clarfunc;
        current->pointers[current->length + 1] = memoryptr;
        current->length += 2;
        return current;
   } else {
        // This one is full, write to a new one
        memoryNode *new_node = (memoryNode *)malloc(sizeof(memoryNode));
        new_node->length = 2;
        new_node->pointers[0] = clarfunc;
        new_node->pointers[1] = memoryptr;
        new_node->next = NULL;
        current->next = new_node;
        return new_node;
   }
}
void memoryClear(memoryNode *head) {
    memoryNode * prev_node;
    while (head != NULL) {
        for (int i = 0; i < head->length; i += 2) {
            void (*free_func) (void *) = head->pointers[i];
            void * ptr_to_free = head->pointers[i + 1];
            free_func(ptr_to_free);
        prev_node = head;
        head = head->next;
        free(prev_node);
        }
    }
}
enum {
    /* classid tag        */    /* union usage   | properties */
    JS_CLASS_OBJECT = 1,        /* must be first */
    JS_CLASS_ARRAY,             /* u.array       | length */
    JS_CLASS_ERROR,
    JS_CLASS_NUMBER,            /* u.object_data */
    JS_CLASS_STRING,            /* u.object_data */
    JS_CLASS_BOOLEAN,           /* u.object_data */
    JS_CLASS_SYMBOL,            /* u.object_data */
    JS_CLASS_ARGUMENTS,         /* u.array       | length */
    JS_CLASS_MAPPED_ARGUMENTS,  /*               | length */
    JS_CLASS_DATE,              /* u.object_data */
    JS_CLASS_MODULE_NS,
    JS_CLASS_C_FUNCTION,        /* u.cfunc */
    JS_CLASS_BYTECODE_FUNCTION, /* u.func */
    JS_CLASS_BOUND_FUNCTION,    /* u.bound_function */
    JS_CLASS_C_FUNCTION_DATA,   /* u.c_function_data_record */
    JS_CLASS_GENERATOR_FUNCTION, /* u.func */
    JS_CLASS_FOR_IN_ITERATOR,   /* u.for_in_iterator */
    JS_CLASS_REGEXP,            /* u.regexp */
    JS_CLASS_ARRAY_BUFFER,      /* u.array_buffer */
    JS_CLASS_SHARED_ARRAY_BUFFER, /* u.array_buffer */
    JS_CLASS_UINT8C_ARRAY,      /* u.array (typed_array) */
    JS_CLASS_INT8_ARRAY,        /* u.array (typed_array) */
    JS_CLASS_UINT8_ARRAY,       /* u.array (typed_array) */
    JS_CLASS_INT16_ARRAY,       /* u.array (typed_array) */
    JS_CLASS_UINT16_ARRAY,      /* u.array (typed_array) */
    JS_CLASS_INT32_ARRAY,       /* u.array (typed_array) */
    JS_CLASS_UINT32_ARRAY,      /* u.array (typed_array) */
    JS_CLASS_BIG_INT64_ARRAY,   /* u.array (typed_array) */
    JS_CLASS_BIG_UINT64_ARRAY,  /* u.array (typed_array) */
    JS_CLASS_FLOAT16_ARRAY,     /* u.array (typed_array) */
    JS_CLASS_FLOAT32_ARRAY,     /* u.array (typed_array) */
    JS_CLASS_FLOAT64_ARRAY,     /* u.array (typed_array) */
    JS_CLASS_DATAVIEW,          /* u.typed_array */
    JS_CLASS_BIG_INT,           /* u.object_data */
    JS_CLASS_MAP,               /* u.map_state */
    JS_CLASS_SET,               /* u.map_state */
    JS_CLASS_WEAKMAP,           /* u.map_state */
    JS_CLASS_WEAKSET,           /* u.map_state */
    JS_CLASS_ITERATOR,
    JS_CLASS_MAP_ITERATOR,      /* u.map_iterator_data */
    JS_CLASS_SET_ITERATOR,      /* u.map_iterator_data */
    JS_CLASS_ARRAY_ITERATOR,    /* u.array_iterator_data */
    JS_CLASS_STRING_ITERATOR,   /* u.array_iterator_data */
    JS_CLASS_REGEXP_STRING_ITERATOR,   /* u.regexp_string_iterator_data */
    JS_CLASS_GENERATOR,         /* u.generator_data */
    JS_CLASS_PROXY,             /* u.proxy_data */
    JS_CLASS_PROMISE,           /* u.promise_data */
    JS_CLASS_PROMISE_RESOLVE_FUNCTION,  /* u.promise_function_data */
    JS_CLASS_PROMISE_REJECT_FUNCTION,   /* u.promise_function_data */
    JS_CLASS_ASYNC_FUNCTION,            /* u.func */
    JS_CLASS_ASYNC_FUNCTION_RESOLVE,    /* u.async_function_data */
    JS_CLASS_ASYNC_FUNCTION_REJECT,     /* u.async_function_data */
    JS_CLASS_ASYNC_FROM_SYNC_ITERATOR,  /* u.async_from_sync_iterator_data */
    JS_CLASS_ASYNC_GENERATOR_FUNCTION,  /* u.func */
    JS_CLASS_ASYNC_GENERATOR,   /* u.async_generator_data */
    JS_CLASS_WEAK_REF,
    JS_CLASS_FINALIZATION_REGISTRY,
    JS_CLASS_CALL_SITE,

    JS_CLASS_INIT_COUNT, /* last entry for predefined classes */
};
#endif

static char textbuffer[4096];
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
static JSClassID js_AudioStream_class_id;
static JSClassID js_Sound_class_id;
static JSClassID js_Music_class_id;
static JSClassID js_VrDeviceInfo_class_id;
static JSClassID js_VrStereoConfig_class_id;
static JSClassID js_FilePathList_class_id;
static JSClassID js_AutomationEvent_class_id;
static JSClassID js_AutomationEventList_class_id;
static JSClassID js_Light_class_id;
static JSClassID js_Lightmapper_class_id;
static JSClassID js_LightmapperConfig_class_id;

static void js_Vector2_finalizer(JSRuntime * rt, JSValue val) {
    Vector2* ptr = JS_GetOpaque(val, js_Vector2_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Vector2_get_x(JSContext* ctx, JSValue this_val) {
    Vector2* ptr = JS_GetOpaque2(ctx, this_val, js_Vector2_class_id);
    float x = ptr->x;
    JSValue ret = JS_NewFloat64(ctx, x);
    return ret;
}

static JSValue js_Vector2_set_x(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector2* ptr = JS_GetOpaque2(ctx, this_val, js_Vector2_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->x = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector2_get_y(JSContext* ctx, JSValue this_val) {
    Vector2* ptr = JS_GetOpaque2(ctx, this_val, js_Vector2_class_id);
    float y = ptr->y;
    JSValue ret = JS_NewFloat64(ctx, y);
    return ret;
}

static JSValue js_Vector2_set_y(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector2* ptr = JS_GetOpaque2(ctx, this_val, js_Vector2_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
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
    JSValue ret = JS_NewFloat64(ctx, x);
    return ret;
}

static JSValue js_Vector3_set_x(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector3* ptr = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->x = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector3_get_y(JSContext* ctx, JSValue this_val) {
    Vector3* ptr = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    float y = ptr->y;
    JSValue ret = JS_NewFloat64(ctx, y);
    return ret;
}

static JSValue js_Vector3_set_y(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector3* ptr = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->y = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector3_get_z(JSContext* ctx, JSValue this_val) {
    Vector3* ptr = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    float z = ptr->z;
    JSValue ret = JS_NewFloat64(ctx, z);
    return ret;
}

static JSValue js_Vector3_set_z(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector3* ptr = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
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
    JSValue ret = JS_NewFloat64(ctx, x);
    return ret;
}

static JSValue js_Vector4_set_x(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->x = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector4_get_y(JSContext* ctx, JSValue this_val) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    float y = ptr->y;
    JSValue ret = JS_NewFloat64(ctx, y);
    return ret;
}

static JSValue js_Vector4_set_y(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->y = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector4_get_z(JSContext* ctx, JSValue this_val) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    float z = ptr->z;
    JSValue ret = JS_NewFloat64(ctx, z);
    return ret;
}

static JSValue js_Vector4_set_z(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->z = value;
    return JS_UNDEFINED;
}

static JSValue js_Vector4_get_w(JSContext* ctx, JSValue this_val) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    float w = ptr->w;
    JSValue ret = JS_NewFloat64(ctx, w);
    return ret;
}

static JSValue js_Vector4_set_w(JSContext* ctx, JSValue this_val, JSValue v) {
    Vector4* ptr = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
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
    JSValue ret = JS_NewUint32(ctx, r);
    return ret;
}

static JSValue js_Color_set_r(JSContext* ctx, JSValue this_val, JSValue v) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    unsigned int _int_value;
    JS_ToUint32(ctx, &_int_value, v);
    unsigned char value = (unsigned char)_int_value;
    ptr->r = value;
    return JS_UNDEFINED;
}

static JSValue js_Color_get_g(JSContext* ctx, JSValue this_val) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    unsigned char g = ptr->g;
    JSValue ret = JS_NewUint32(ctx, g);
    return ret;
}

static JSValue js_Color_set_g(JSContext* ctx, JSValue this_val, JSValue v) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    unsigned int _int_value;
    JS_ToUint32(ctx, &_int_value, v);
    unsigned char value = (unsigned char)_int_value;
    ptr->g = value;
    return JS_UNDEFINED;
}

static JSValue js_Color_get_b(JSContext* ctx, JSValue this_val) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    unsigned char b = ptr->b;
    JSValue ret = JS_NewUint32(ctx, b);
    return ret;
}

static JSValue js_Color_set_b(JSContext* ctx, JSValue this_val, JSValue v) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    unsigned int _int_value;
    JS_ToUint32(ctx, &_int_value, v);
    unsigned char value = (unsigned char)_int_value;
    ptr->b = value;
    return JS_UNDEFINED;
}

static JSValue js_Color_get_a(JSContext* ctx, JSValue this_val) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    unsigned char a = ptr->a;
    JSValue ret = JS_NewUint32(ctx, a);
    return ret;
}

static JSValue js_Color_set_a(JSContext* ctx, JSValue this_val, JSValue v) {
    Color* ptr = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    unsigned int _int_value;
    JS_ToUint32(ctx, &_int_value, v);
    unsigned char value = (unsigned char)_int_value;
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
    JSValue ret = JS_NewFloat64(ctx, x);
    return ret;
}

static JSValue js_Rectangle_set_x(JSContext* ctx, JSValue this_val, JSValue v) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->x = value;
    return JS_UNDEFINED;
}

static JSValue js_Rectangle_get_y(JSContext* ctx, JSValue this_val) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    float y = ptr->y;
    JSValue ret = JS_NewFloat64(ctx, y);
    return ret;
}

static JSValue js_Rectangle_set_y(JSContext* ctx, JSValue this_val, JSValue v) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->y = value;
    return JS_UNDEFINED;
}

static JSValue js_Rectangle_get_width(JSContext* ctx, JSValue this_val) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    float width = ptr->width;
    JSValue ret = JS_NewFloat64(ctx, width);
    return ret;
}

static JSValue js_Rectangle_set_width(JSContext* ctx, JSValue this_val, JSValue v) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->width = value;
    return JS_UNDEFINED;
}

static JSValue js_Rectangle_get_height(JSContext* ctx, JSValue this_val) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    float height = ptr->height;
    JSValue ret = JS_NewFloat64(ctx, height);
    return ret;
}

static JSValue js_Rectangle_set_height(JSContext* ctx, JSValue this_val, JSValue v) {
    Rectangle* ptr = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
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
    JSValue js_value;
    if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (void *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        return JS_EXCEPTION;
    }
    ptr->data = value;
    return JS_UNDEFINED;
}

static JSValue js_Image_get_width(JSContext* ctx, JSValue this_val) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int width = ptr->width;
    JSValue ret = JS_NewInt32(ctx, width);
    return ret;
}

static JSValue js_Image_set_width(JSContext* ctx, JSValue this_val, JSValue v) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->width = value;
    return JS_UNDEFINED;
}

static JSValue js_Image_get_height(JSContext* ctx, JSValue this_val) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int height = ptr->height;
    JSValue ret = JS_NewInt32(ctx, height);
    return ret;
}

static JSValue js_Image_set_height(JSContext* ctx, JSValue this_val, JSValue v) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->height = value;
    return JS_UNDEFINED;
}

static JSValue js_Image_get_mipmaps(JSContext* ctx, JSValue this_val) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int mipmaps = ptr->mipmaps;
    JSValue ret = JS_NewInt32(ctx, mipmaps);
    return ret;
}

static JSValue js_Image_set_mipmaps(JSContext* ctx, JSValue this_val, JSValue v) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->mipmaps = value;
    return JS_UNDEFINED;
}

static JSValue js_Image_get_format(JSContext* ctx, JSValue this_val) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int format = ptr->format;
    JSValue ret = JS_NewInt32(ctx, format);
    return ret;
}

static JSValue js_Image_set_format(JSContext* ctx, JSValue this_val, JSValue v) {
    Image* ptr = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
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
    JSValue ret = JS_NewInt32(ctx, width);
    return ret;
}

static JSValue js_Texture_get_height(JSContext* ctx, JSValue this_val) {
    Texture* ptr = JS_GetOpaque2(ctx, this_val, js_Texture_class_id);
    int height = ptr->height;
    JSValue ret = JS_NewInt32(ctx, height);
    return ret;
}

static JSValue js_Texture_get_mipmaps(JSContext* ctx, JSValue this_val) {
    Texture* ptr = JS_GetOpaque2(ctx, this_val, js_Texture_class_id);
    int mipmaps = ptr->mipmaps;
    JSValue ret = JS_NewInt32(ctx, mipmaps);
    return ret;
}

static JSValue js_Texture_get_format(JSContext* ctx, JSValue this_val) {
    Texture* ptr = JS_GetOpaque2(ctx, this_val, js_Texture_class_id);
    int format = ptr->format;
    JSValue ret = JS_NewInt32(ctx, format);
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
    JSValue ret = JS_NewUint32(ctx, id);
    return ret;
}

static JSValue js_RenderTexture_get_texture(JSContext* ctx, JSValue this_val) {
    RenderTexture* ptr = JS_GetOpaque2(ctx, this_val, js_RenderTexture_class_id);
    Texture texture = ptr->texture;
    Texture* ret_ptr = (Texture*)js_malloc(ctx, sizeof(Texture));
    *ret_ptr = texture;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_RenderTexture_get_depth(JSContext* ctx, JSValue this_val) {
    RenderTexture* ptr = JS_GetOpaque2(ctx, this_val, js_RenderTexture_class_id);
    Texture depth = ptr->depth;
    Texture* ret_ptr = (Texture*)js_malloc(ctx, sizeof(Texture));
    *ret_ptr = depth;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ret_ptr);
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
    Rectangle* ret_ptr = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *ret_ptr = source;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_NPatchInfo_set_source(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    Rectangle* value_ptr = (Rectangle*)JS_GetOpaque2(ctx, v, js_Rectangle_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Rectangle value = *value_ptr;
    ptr->source = value;
    return JS_UNDEFINED;
}

static JSValue js_NPatchInfo_get_left(JSContext* ctx, JSValue this_val) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int left = ptr->left;
    JSValue ret = JS_NewInt32(ctx, left);
    return ret;
}

static JSValue js_NPatchInfo_set_left(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->left = value;
    return JS_UNDEFINED;
}

static JSValue js_NPatchInfo_get_top(JSContext* ctx, JSValue this_val) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int top = ptr->top;
    JSValue ret = JS_NewInt32(ctx, top);
    return ret;
}

static JSValue js_NPatchInfo_set_top(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->top = value;
    return JS_UNDEFINED;
}

static JSValue js_NPatchInfo_get_right(JSContext* ctx, JSValue this_val) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int right = ptr->right;
    JSValue ret = JS_NewInt32(ctx, right);
    return ret;
}

static JSValue js_NPatchInfo_set_right(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->right = value;
    return JS_UNDEFINED;
}

static JSValue js_NPatchInfo_get_bottom(JSContext* ctx, JSValue this_val) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int bottom = ptr->bottom;
    JSValue ret = JS_NewInt32(ctx, bottom);
    return ret;
}

static JSValue js_NPatchInfo_set_bottom(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->bottom = value;
    return JS_UNDEFINED;
}

static JSValue js_NPatchInfo_get_layout(JSContext* ctx, JSValue this_val) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int layout = ptr->layout;
    JSValue ret = JS_NewInt32(ctx, layout);
    return ret;
}

static JSValue js_NPatchInfo_set_layout(JSContext* ctx, JSValue this_val, JSValue v) {
    NPatchInfo* ptr = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
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
    JSValue ret = JS_NewInt32(ctx, baseSize);
    return ret;
}

static JSValue js_Font_get_glyphCount(JSContext* ctx, JSValue this_val) {
    Font* ptr = JS_GetOpaque2(ctx, this_val, js_Font_class_id);
    int glyphCount = ptr->glyphCount;
    JSValue ret = JS_NewInt32(ctx, glyphCount);
    return ret;
}

static JSValue js_Font_get_glyphPadding(JSContext* ctx, JSValue this_val) {
    Font* ptr = JS_GetOpaque2(ctx, this_val, js_Font_class_id);
    int glyphPadding = ptr->glyphPadding;
    JSValue ret = JS_NewInt32(ctx, glyphPadding);
    return ret;
}

static JSValue js_Font_get_texture(JSContext* ctx, JSValue this_val) {
    Font* ptr = JS_GetOpaque2(ctx, this_val, js_Font_class_id);
    Texture2D texture = ptr->texture;
    Texture2D* ret_ptr = (Texture2D*)js_malloc(ctx, sizeof(Texture2D));
    *ret_ptr = texture;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ret_ptr);
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
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = position;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_Camera3D_set_position(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    Vector3* value_ptr = (Vector3*)JS_GetOpaque2(ctx, v, js_Vector3_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Vector3 value = *value_ptr;
    ptr->position = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera3D_get_target(JSContext* ctx, JSValue this_val) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    Vector3 target = ptr->target;
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = target;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_Camera3D_set_target(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    Vector3* value_ptr = (Vector3*)JS_GetOpaque2(ctx, v, js_Vector3_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Vector3 value = *value_ptr;
    ptr->target = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera3D_set_up(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    Vector3* value_ptr = (Vector3*)JS_GetOpaque2(ctx, v, js_Vector3_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Vector3 value = *value_ptr;
    ptr->up = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera3D_get_fovy(JSContext* ctx, JSValue this_val) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    float fovy = ptr->fovy;
    JSValue ret = JS_NewFloat64(ctx, fovy);
    return ret;
}

static JSValue js_Camera3D_set_fovy(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->fovy = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera3D_get_projection(JSContext* ctx, JSValue this_val) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    int projection = ptr->projection;
    JSValue ret = JS_NewInt32(ctx, projection);
    return ret;
}

static JSValue js_Camera3D_set_projection(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera3D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
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
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = offset;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_Camera2D_set_offset(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    Vector2* value_ptr = (Vector2*)JS_GetOpaque2(ctx, v, js_Vector2_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Vector2 value = *value_ptr;
    ptr->offset = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera2D_get_target(JSContext* ctx, JSValue this_val) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    Vector2 target = ptr->target;
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = target;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_Camera2D_set_target(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    Vector2* value_ptr = (Vector2*)JS_GetOpaque2(ctx, v, js_Vector2_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Vector2 value = *value_ptr;
    ptr->target = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera2D_get_rotation(JSContext* ctx, JSValue this_val) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    float rotation = ptr->rotation;
    JSValue ret = JS_NewFloat64(ctx, rotation);
    return ret;
}

static JSValue js_Camera2D_set_rotation(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->rotation = value;
    return JS_UNDEFINED;
}

static JSValue js_Camera2D_get_zoom(JSContext* ctx, JSValue this_val) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    float zoom = ptr->zoom;
    JSValue ret = JS_NewFloat64(ctx, zoom);
    return ret;
}

static JSValue js_Camera2D_set_zoom(JSContext* ctx, JSValue this_val, JSValue v) {
    Camera2D* ptr = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
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
    JSValue ret = JS_NewInt32(ctx, vertexCount);
    return ret;
}

static JSValue js_Mesh_set_vertexCount(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->vertexCount = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_get_triangleCount(JSContext* ctx, JSValue this_val) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    int triangleCount = ptr->triangleCount;
    JSValue ret = JS_NewInt32(ctx, triangleCount);
    return ret;
}

static JSValue js_Mesh_set_triangleCount(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->triangleCount = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_vertices(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,v) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    ptr->vertices = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_texcoords(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,v) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    ptr->texcoords = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_texcoords2(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,v) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    ptr->texcoords2 = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_normals(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,v) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    ptr->normals = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_tangents(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,v) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    ptr->tangents = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_colors(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    unsigned char * value;
    JSValue js_value;
    if(JS_IsArray(ctx,v) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(unsigned char));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            unsigned int _int_value[i0];
            JS_ToUint32(ctx, &_int_value[i0], js_value);
            value[i0] = (unsigned char)_int_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (unsigned char *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_UINT8_ARRAY && classid_value==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            value = (unsigned char *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    ptr->colors = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_indices(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    unsigned short * value;
    JSValue js_value;
    if(JS_IsArray(ctx,v) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(unsigned short));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            unsigned int _int_value[i0];
            JS_ToUint32(ctx, &_int_value[i0], js_value);
            value[i0] = (unsigned short)_int_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (unsigned short *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            value = (unsigned short *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    ptr->indices = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_animVertices(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,v) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    ptr->animVertices = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_animNormals(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,v) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    ptr->animNormals = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_boneIds(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    unsigned char * value;
    JSValue js_value;
    if(JS_IsArray(ctx,v) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(unsigned char));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            unsigned int _int_value[i0];
            JS_ToUint32(ctx, &_int_value[i0], js_value);
            value[i0] = (unsigned char)_int_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (unsigned char *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_UINT8_ARRAY && classid_value==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            value = (unsigned char *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    ptr->boneIds = value;
    return JS_UNDEFINED;
}

static JSValue js_Mesh_set_boneWeights(JSContext* ctx, JSValue this_val, JSValue v) {
    Mesh* ptr = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,v) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,v,&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,v,i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(v) == 1) {
        js_value = JS_DupValue(ctx,v);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(v);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,v,&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    ptr->boneWeights = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Mesh_proto_funcs[] = {
    JS_CGETSET_DEF("vertexCount",js_Mesh_get_vertexCount,js_Mesh_set_vertexCount),
    JS_CGETSET_DEF("triangleCount",js_Mesh_get_triangleCount,js_Mesh_set_triangleCount),
    JS_CGETSET_DEF("vertices",NULL,js_Mesh_set_vertices),
    JS_CGETSET_DEF("texcoords",NULL,js_Mesh_set_texcoords),
    JS_CGETSET_DEF("texcoords2",NULL,js_Mesh_set_texcoords2),
    JS_CGETSET_DEF("normals",NULL,js_Mesh_set_normals),
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
    JSValue ret = JS_NewUint32(ctx, id);
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
    Texture2D* value_ptr = (Texture2D*)JS_GetOpaque2(ctx, v, js_Texture_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Texture2D value = *value_ptr;
    ptr->texture = value;
    return JS_UNDEFINED;
}

static JSValue js_MaterialMap_get_color(JSContext* ctx, JSValue this_val) {
    MaterialMap* ptr = JS_GetOpaque2(ctx, this_val, js_MaterialMap_class_id);
    Color color = ptr->color;
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = color;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_MaterialMap_set_color(JSContext* ctx, JSValue this_val, JSValue v) {
    MaterialMap* ptr = JS_GetOpaque2(ctx, this_val, js_MaterialMap_class_id);
    Color* value_ptr = (Color*)JS_GetOpaque2(ctx, v, js_Color_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Color value = *value_ptr;
    ptr->color = value;
    return JS_UNDEFINED;
}

static JSValue js_MaterialMap_get_value(JSContext* ctx, JSValue this_val) {
    MaterialMap* ptr = JS_GetOpaque2(ctx, this_val, js_MaterialMap_class_id);
    float value = ptr->value;
    JSValue ret = JS_NewFloat64(ctx, value);
    return ret;
}

static JSValue js_MaterialMap_set_value(JSContext* ctx, JSValue this_val, JSValue v) {
    MaterialMap* ptr = JS_GetOpaque2(ctx, this_val, js_MaterialMap_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
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
    Shader* ret_ptr = (Shader*)js_malloc(ctx, sizeof(Shader));
    *ret_ptr = shader;
    JSValue ret = JS_NewObjectClass(ctx, js_Shader_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_Material_set_shader(JSContext* ctx, JSValue this_val, JSValue v) {
    Material* ptr = JS_GetOpaque2(ctx, this_val, js_Material_class_id);
    Shader* value_ptr = (Shader*)JS_GetOpaque2(ctx, v, js_Shader_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Shader value = *value_ptr;
    ptr->shader = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_Material_proto_funcs[] = {
    JS_CGETSET_DEF("shader",js_Material_get_shader,js_Material_set_shader),
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
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = transform;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_Model_set_transform(JSContext* ctx, JSValue this_val, JSValue v) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    Matrix* value_ptr = (Matrix*)JS_GetOpaque2(ctx, v, js_Matrix_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Matrix value = *value_ptr;
    ptr->transform = value;
    return JS_UNDEFINED;
}

static JSValue js_Model_get_meshCount(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    int meshCount = ptr->meshCount;
    JSValue ret = JS_NewInt32(ctx, meshCount);
    return ret;
}

static JSValue js_Model_get_materialCount(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    int materialCount = ptr->materialCount;
    JSValue ret = JS_NewInt32(ctx, materialCount);
    return ret;
}

static JSValue js_Model_get_boneCount(JSContext* ctx, JSValue this_val) {
    Model* ptr = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    int boneCount = ptr->boneCount;
    JSValue ret = JS_NewInt32(ctx, boneCount);
    return ret;
}

static const JSCFunctionListEntry js_Model_proto_funcs[] = {
    JS_CGETSET_DEF("transform",js_Model_get_transform,js_Model_set_transform),
    JS_CGETSET_DEF("meshCount",js_Model_get_meshCount,NULL),
    JS_CGETSET_DEF("materialCount",js_Model_get_materialCount,NULL),
    JS_CGETSET_DEF("boneCount",js_Model_get_boneCount,NULL),
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
    Vector3* value_ptr = (Vector3*)JS_GetOpaque2(ctx, v, js_Vector3_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Vector3 value = *value_ptr;
    ptr->position = value;
    return JS_UNDEFINED;
}

static JSValue js_Ray_set_direction(JSContext* ctx, JSValue this_val, JSValue v) {
    Ray* ptr = JS_GetOpaque2(ctx, this_val, js_Ray_class_id);
    Vector3* value_ptr = (Vector3*)JS_GetOpaque2(ctx, v, js_Vector3_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Vector3 value = *value_ptr;
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
    JSValue ret = JS_NewFloat64(ctx, distance);
    return ret;
}

static JSValue js_RayCollision_get_point(JSContext* ctx, JSValue this_val) {
    RayCollision* ptr = JS_GetOpaque2(ctx, this_val, js_RayCollision_class_id);
    Vector3 point = ptr->point;
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = point;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_RayCollision_get_normal(JSContext* ctx, JSValue this_val) {
    RayCollision* ptr = JS_GetOpaque2(ctx, this_val, js_RayCollision_class_id);
    Vector3 normal = ptr->normal;
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = normal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
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
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = min;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_BoundingBox_set_min(JSContext* ctx, JSValue this_val, JSValue v) {
    BoundingBox* ptr = JS_GetOpaque2(ctx, this_val, js_BoundingBox_class_id);
    Vector3* value_ptr = (Vector3*)JS_GetOpaque2(ctx, v, js_Vector3_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Vector3 value = *value_ptr;
    ptr->min = value;
    return JS_UNDEFINED;
}

static JSValue js_BoundingBox_get_max(JSContext* ctx, JSValue this_val) {
    BoundingBox* ptr = JS_GetOpaque2(ctx, this_val, js_BoundingBox_class_id);
    Vector3 max = ptr->max;
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = max;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_BoundingBox_set_max(JSContext* ctx, JSValue this_val, JSValue v) {
    BoundingBox* ptr = JS_GetOpaque2(ctx, this_val, js_BoundingBox_class_id);
    Vector3* value_ptr = (Vector3*)JS_GetOpaque2(ctx, v, js_Vector3_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Vector3 value = *value_ptr;
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
    JSValue ret = JS_NewUint32(ctx, frameCount);
    return ret;
}

static JSValue js_Wave_get_sampleRate(JSContext* ctx, JSValue this_val) {
    Wave* ptr = JS_GetOpaque2(ctx, this_val, js_Wave_class_id);
    unsigned int sampleRate = ptr->sampleRate;
    JSValue ret = JS_NewUint32(ctx, sampleRate);
    return ret;
}

static JSValue js_Wave_get_sampleSize(JSContext* ctx, JSValue this_val) {
    Wave* ptr = JS_GetOpaque2(ctx, this_val, js_Wave_class_id);
    unsigned int sampleSize = ptr->sampleSize;
    JSValue ret = JS_NewUint32(ctx, sampleSize);
    return ret;
}

static JSValue js_Wave_get_channels(JSContext* ctx, JSValue this_val) {
    Wave* ptr = JS_GetOpaque2(ctx, this_val, js_Wave_class_id);
    unsigned int channels = ptr->channels;
    JSValue ret = JS_NewUint32(ctx, channels);
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
    JSValue ret = JS_NewUint32(ctx, frameCount);
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
    JSValue ret = JS_NewUint32(ctx, frameCount);
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
    bool value = JS_ToBool(ctx, v);
    ptr->looping = value;
    return JS_UNDEFINED;
}

static JSValue js_Music_get_ctxType(JSContext* ctx, JSValue this_val) {
    Music* ptr = JS_GetOpaque2(ctx, this_val, js_Music_class_id);
    int ctxType = ptr->ctxType;
    JSValue ret = JS_NewInt32(ctx, ctxType);
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
    JSValue ret = JS_NewInt32(ctx, hResolution);
    return ret;
}

static JSValue js_VrDeviceInfo_set_hResolution(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->hResolution = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_vResolution(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    int vResolution = ptr->vResolution;
    JSValue ret = JS_NewInt32(ctx, vResolution);
    return ret;
}

static JSValue js_VrDeviceInfo_set_vResolution(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->vResolution = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_hScreenSize(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float hScreenSize = ptr->hScreenSize;
    JSValue ret = JS_NewFloat64(ctx, hScreenSize);
    return ret;
}

static JSValue js_VrDeviceInfo_set_hScreenSize(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->hScreenSize = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_vScreenSize(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float vScreenSize = ptr->vScreenSize;
    JSValue ret = JS_NewFloat64(ctx, vScreenSize);
    return ret;
}

static JSValue js_VrDeviceInfo_set_vScreenSize(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->vScreenSize = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_eyeToScreenDistance(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float eyeToScreenDistance = ptr->eyeToScreenDistance;
    JSValue ret = JS_NewFloat64(ctx, eyeToScreenDistance);
    return ret;
}

static JSValue js_VrDeviceInfo_set_eyeToScreenDistance(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->eyeToScreenDistance = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_lensSeparationDistance(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float lensSeparationDistance = ptr->lensSeparationDistance;
    JSValue ret = JS_NewFloat64(ctx, lensSeparationDistance);
    return ret;
}

static JSValue js_VrDeviceInfo_set_lensSeparationDistance(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->lensSeparationDistance = value;
    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_get_interpupillaryDistance(JSContext* ctx, JSValue this_val) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    float interpupillaryDistance = ptr->interpupillaryDistance;
    JSValue ret = JS_NewFloat64(ctx, interpupillaryDistance);
    return ret;
}

static JSValue js_VrDeviceInfo_set_interpupillaryDistance(JSContext* ctx, JSValue this_val, JSValue v) {
    VrDeviceInfo* ptr = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->interpupillaryDistance = value;
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

static void js_Light_finalizer(JSRuntime * rt, JSValue val) {
    Light* ptr = JS_GetOpaque(val, js_Light_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Light_get_type(JSContext* ctx, JSValue this_val) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    int type = ptr->type;
    JSValue ret = JS_NewInt32(ctx, type);
    return ret;
}

static JSValue js_Light_set_type(JSContext* ctx, JSValue this_val, JSValue v) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
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
    bool value = JS_ToBool(ctx, v);
    ptr->enabled = value;
    return JS_UNDEFINED;
}

static JSValue js_Light_get_position(JSContext* ctx, JSValue this_val) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Vector3 position = ptr->position;
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = position;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_Light_set_position(JSContext* ctx, JSValue this_val, JSValue v) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Vector3* value_ptr = (Vector3*)JS_GetOpaque2(ctx, v, js_Vector3_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Vector3 value = *value_ptr;
    ptr->position = value;
    return JS_UNDEFINED;
}

static JSValue js_Light_get_target(JSContext* ctx, JSValue this_val) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Vector3 target = ptr->target;
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = target;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_Light_set_target(JSContext* ctx, JSValue this_val, JSValue v) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Vector3* value_ptr = (Vector3*)JS_GetOpaque2(ctx, v, js_Vector3_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Vector3 value = *value_ptr;
    ptr->target = value;
    return JS_UNDEFINED;
}

static JSValue js_Light_get_color(JSContext* ctx, JSValue this_val) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Color color = ptr->color;
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = color;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_Light_set_color(JSContext* ctx, JSValue this_val, JSValue v) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    Color* value_ptr = (Color*)JS_GetOpaque2(ctx, v, js_Color_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Color value = *value_ptr;
    ptr->color = value;
    return JS_UNDEFINED;
}

static JSValue js_Light_get_attenuation(JSContext* ctx, JSValue this_val) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    float attenuation = ptr->attenuation;
    JSValue ret = JS_NewFloat64(ctx, attenuation);
    return ret;
}

static JSValue js_Light_set_attenuation(JSContext* ctx, JSValue this_val, JSValue v) {
    Light* ptr = JS_GetOpaque2(ctx, this_val, js_Light_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
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

static void js_Lightmapper_finalizer(JSRuntime * rt, JSValue val) {
    Lightmapper* ptr = JS_GetOpaque(val, js_Lightmapper_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static JSValue js_Lightmapper_get_w(JSContext* ctx, JSValue this_val) {
    Lightmapper* ptr = JS_GetOpaque2(ctx, this_val, js_Lightmapper_class_id);
    int w = ptr->w;
    JSValue ret = JS_NewInt32(ctx, w);
    return ret;
}

static JSValue js_Lightmapper_get_h(JSContext* ctx, JSValue this_val) {
    Lightmapper* ptr = JS_GetOpaque2(ctx, this_val, js_Lightmapper_class_id);
    int h = ptr->h;
    JSValue ret = JS_NewInt32(ctx, h);
    return ret;
}

static JSValue js_Lightmapper_get_progress(JSContext* ctx, JSValue this_val) {
    Lightmapper* ptr = JS_GetOpaque2(ctx, this_val, js_Lightmapper_class_id);
    float progress = ptr->progress;
    JSValue ret = JS_NewFloat64(ctx, progress);
    return ret;
}

static const JSCFunctionListEntry js_Lightmapper_proto_funcs[] = {
    JS_CGETSET_DEF("w",js_Lightmapper_get_w,NULL),
    JS_CGETSET_DEF("h",js_Lightmapper_get_h,NULL),
    JS_CGETSET_DEF("progress",js_Lightmapper_get_progress,NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","Lightmapper", JS_PROP_CONFIGURABLE),
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
    JSValue ret = JS_NewInt32(ctx, hemisphereSize);
    return ret;
}

static JSValue js_LightmapperConfig_set_hemisphereSize(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->hemisphereSize = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_zNear(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    float zNear = ptr->zNear;
    JSValue ret = JS_NewFloat64(ctx, zNear);
    return ret;
}

static JSValue js_LightmapperConfig_set_zNear(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->zNear = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_zFar(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    float zFar = ptr->zFar;
    JSValue ret = JS_NewFloat64(ctx, zFar);
    return ret;
}

static JSValue js_LightmapperConfig_set_zFar(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->zFar = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_backgroundColor(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    Color backgroundColor = ptr->backgroundColor;
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = backgroundColor;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_LightmapperConfig_set_backgroundColor(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    Color* value_ptr = (Color*)JS_GetOpaque2(ctx, v, js_Color_class_id);
    if(value_ptr == NULL) return JS_EXCEPTION;
    Color value = *value_ptr;
    ptr->backgroundColor = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_interpolationPasses(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    int interpolationPasses = ptr->interpolationPasses;
    JSValue ret = JS_NewInt32(ctx, interpolationPasses);
    return ret;
}

static JSValue js_LightmapperConfig_set_interpolationPasses(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    int value;
    JS_ToInt32(ctx, &value, v);
    ptr->interpolationPasses = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_interpolationThreshold(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    float interpolationThreshold = ptr->interpolationThreshold;
    JSValue ret = JS_NewFloat64(ctx, interpolationThreshold);
    return ret;
}

static JSValue js_LightmapperConfig_set_interpolationThreshold(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->interpolationThreshold = value;
    return JS_UNDEFINED;
}

static JSValue js_LightmapperConfig_get_cameraToSurfaceDistanceModifier(JSContext* ctx, JSValue this_val) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    float cameraToSurfaceDistanceModifier = ptr->cameraToSurfaceDistanceModifier;
    JSValue ret = JS_NewFloat64(ctx, cameraToSurfaceDistanceModifier);
    return ret;
}

static JSValue js_LightmapperConfig_set_cameraToSurfaceDistanceModifier(JSContext* ctx, JSValue this_val, JSValue v) {
    LightmapperConfig* ptr = JS_GetOpaque2(ctx, this_val, js_LightmapperConfig_class_id);
    double double_value;
    JS_ToFloat64(ctx, &double_value, v);
    float value = (float)double_value;
    ptr->cameraToSurfaceDistanceModifier = value;
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_LightmapperConfig_proto_funcs[] = {
    JS_CGETSET_DEF("hemisphereSize",js_LightmapperConfig_get_hemisphereSize,js_LightmapperConfig_set_hemisphereSize),
    JS_CGETSET_DEF("zNear",js_LightmapperConfig_get_zNear,js_LightmapperConfig_set_zNear),
    JS_CGETSET_DEF("zFar",js_LightmapperConfig_get_zFar,js_LightmapperConfig_set_zFar),
    JS_CGETSET_DEF("backgroundColor",js_LightmapperConfig_get_backgroundColor,js_LightmapperConfig_set_backgroundColor),
    JS_CGETSET_DEF("interpolationPasses",js_LightmapperConfig_get_interpolationPasses,js_LightmapperConfig_set_interpolationPasses),
    JS_CGETSET_DEF("interpolationThreshold",js_LightmapperConfig_get_interpolationThreshold,js_LightmapperConfig_set_interpolationThreshold),
    JS_CGETSET_DEF("cameraToSurfaceDistanceModifier",js_LightmapperConfig_get_cameraToSurfaceDistanceModifier,js_LightmapperConfig_set_cameraToSurfaceDistanceModifier),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","LightmapperConfig", JS_PROP_CONFIGURABLE),
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

static JSValue js_Vector2_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_x;
    JS_ToFloat64(ctx, &double_x, argv[0]);
    float x = (float)double_x;
    double double_y;
    JS_ToFloat64(ctx, &double_y, argv[1]);
    float y = (float)double_y;
    Vector2 _struct = { x, y };
    Vector2* _return_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_Vector3_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_x;
    JS_ToFloat64(ctx, &double_x, argv[0]);
    float x = (float)double_x;
    double double_y;
    JS_ToFloat64(ctx, &double_y, argv[1]);
    float y = (float)double_y;
    double double_z;
    JS_ToFloat64(ctx, &double_z, argv[2]);
    float z = (float)double_z;
    Vector3 _struct = { x, y, z };
    Vector3* _return_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_Vector4_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_x;
    JS_ToFloat64(ctx, &double_x, argv[0]);
    float x = (float)double_x;
    double double_y;
    JS_ToFloat64(ctx, &double_y, argv[1]);
    float y = (float)double_y;
    double double_z;
    JS_ToFloat64(ctx, &double_z, argv[2]);
    float z = (float)double_z;
    double double_w;
    JS_ToFloat64(ctx, &double_w, argv[3]);
    float w = (float)double_w;
    Vector4 _struct = { x, y, z, w };
    Vector4* _return_ptr = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_Color_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned int _int_r;
    JS_ToUint32(ctx, &_int_r, argv[0]);
    unsigned char r = (unsigned char)_int_r;
    unsigned int _int_g;
    JS_ToUint32(ctx, &_int_g, argv[1]);
    unsigned char g = (unsigned char)_int_g;
    unsigned int _int_b;
    JS_ToUint32(ctx, &_int_b, argv[2]);
    unsigned char b = (unsigned char)_int_b;
    unsigned int _int_a;
    JS_ToUint32(ctx, &_int_a, argv[3]);
    unsigned char a = (unsigned char)_int_a;
    Color _struct = { r, g, b, a };
    Color* _return_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_Rectangle_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_x;
    JS_ToFloat64(ctx, &double_x, argv[0]);
    float x = (float)double_x;
    double double_y;
    JS_ToFloat64(ctx, &double_y, argv[1]);
    float y = (float)double_y;
    double double_width;
    JS_ToFloat64(ctx, &double_width, argv[2]);
    float width = (float)double_width;
    double double_height;
    JS_ToFloat64(ctx, &double_height, argv[3]);
    float height = (float)double_height;
    Rectangle _struct = { x, y, width, height };
    Rectangle* _return_ptr = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_Image_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image _struct = {  };
    Image* _return_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_NPatchInfo_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* source_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(source_ptr == NULL) return JS_EXCEPTION;
    Rectangle source = *source_ptr;
    int left;
    JS_ToInt32(ctx, &left, argv[1]);
    int top;
    JS_ToInt32(ctx, &top, argv[2]);
    int right;
    JS_ToInt32(ctx, &right, argv[3]);
    int bottom;
    JS_ToInt32(ctx, &bottom, argv[4]);
    int layout;
    JS_ToInt32(ctx, &layout, argv[5]);
    NPatchInfo _struct = { source, left, top, right, bottom, layout };
    NPatchInfo* _return_ptr = (NPatchInfo*)js_malloc(ctx, sizeof(NPatchInfo));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_NPatchInfo_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_Camera3D_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Vector3* target_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(target_ptr == NULL) return JS_EXCEPTION;
    Vector3 target = *target_ptr;
    Vector3* up_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(up_ptr == NULL) return JS_EXCEPTION;
    Vector3 up = *up_ptr;
    double double_fovy;
    JS_ToFloat64(ctx, &double_fovy, argv[3]);
    float fovy = (float)double_fovy;
    int projection;
    JS_ToInt32(ctx, &projection, argv[4]);
    Camera3D _struct = { position, target, up, fovy, projection };
    Camera3D* _return_ptr = (Camera3D*)js_malloc(ctx, sizeof(Camera3D));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Camera3D_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_Camera2D_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* offset_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(offset_ptr == NULL) return JS_EXCEPTION;
    Vector2 offset = *offset_ptr;
    Vector2* target_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(target_ptr == NULL) return JS_EXCEPTION;
    Vector2 target = *target_ptr;
    double double_rotation;
    JS_ToFloat64(ctx, &double_rotation, argv[2]);
    float rotation = (float)double_rotation;
    double double_zoom;
    JS_ToFloat64(ctx, &double_zoom, argv[3]);
    float zoom = (float)double_zoom;
    Camera2D _struct = { offset, target, rotation, zoom };
    Camera2D* _return_ptr = (Camera2D*)js_malloc(ctx, sizeof(Camera2D));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Camera2D_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_Mesh_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh _struct = {  };
    Mesh* _return_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_Ray_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Vector3* direction_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(direction_ptr == NULL) return JS_EXCEPTION;
    Vector3 direction = *direction_ptr;
    Ray _struct = { position, direction };
    Ray* _return_ptr = (Ray*)js_malloc(ctx, sizeof(Ray));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_Ray_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_BoundingBox_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* min_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(min_ptr == NULL) return JS_EXCEPTION;
    Vector3 min = *min_ptr;
    Vector3* max_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(max_ptr == NULL) return JS_EXCEPTION;
    Vector3 max = *max_ptr;
    BoundingBox _struct = { min, max };
    BoundingBox* _return_ptr = (BoundingBox*)js_malloc(ctx, sizeof(BoundingBox));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_BoundingBox_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_VrDeviceInfo_constructor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    VrDeviceInfo _struct = {  };
    VrDeviceInfo* _return_ptr = (VrDeviceInfo*)js_malloc(ctx, sizeof(VrDeviceInfo));
    *_return_ptr = _struct;
    JSValue _return = JS_NewObjectClass(ctx, js_VrDeviceInfo_class_id);
    JS_SetOpaque(_return, _return_ptr);
    return _return;
}

static JSValue js_initWindow(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    char * title;
    JSValue js_title;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_title;
        if(JS_GetLength(ctx,argv[2],&size_title)==-1) {
            return JS_EXCEPTION;
        }
        title = js_malloc(ctx, size_title * sizeof(char));
        for(int i0=0; i0 < size_title; i0++){
            JSValue js_title = JS_GetPropertyUint32(ctx,argv[2],i0);
            title[i0] = (char)((char *)JS_ToCString(ctx, js_title))[0];
        }
    }
    else if(JS_IsString(argv[2]) == 1) {
        title = (char *)JS_ToCString(ctx, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_title = JS_DupValue(ctx,argv[2]);
        size_t size_title;
        title = (char *)JS_GetArrayBuffer(ctx, &size_title, js_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[2]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            size_t offset_title;
            size_t size_title;
            js_title = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_title,&size_title,NULL);
            title = (char *)JS_GetArrayBuffer(ctx, &size_title, js_title);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    InitWindow(width, height, (const char *)title);
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, title);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, title);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[2]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_title);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_closeWindow(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    CloseWindow();
    return JS_UNDEFINED;
}

static JSValue js_windowShouldClose(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = WindowShouldClose();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isWindowReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowReady();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isWindowFullscreen(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowFullscreen();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isWindowHidden(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowHidden();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isWindowMinimized(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowMinimized();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isWindowMaximized(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowMaximized();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isWindowFocused(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowFocused();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isWindowResized(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsWindowResized();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isWindowState(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned int flag;
    JS_ToUint32(ctx, &flag, argv[0]);
    bool returnVal = IsWindowState(flag);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_setWindowState(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned int flags;
    JS_ToUint32(ctx, &flags, argv[0]);
    SetWindowState(flags);
    return JS_UNDEFINED;
}

static JSValue js_clearWindowState(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned int flags;
    JS_ToUint32(ctx, &flags, argv[0]);
    ClearWindowState(flags);
    return JS_UNDEFINED;
}

static JSValue js_toggleFullscreen(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    ToggleFullscreen();
    return JS_UNDEFINED;
}

static JSValue js_toggleBorderlessWindowed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    ToggleBorderlessWindowed();
    return JS_UNDEFINED;
}

static JSValue js_maximizeWindow(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    MaximizeWindow();
    return JS_UNDEFINED;
}

static JSValue js_minimizeWindow(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    MinimizeWindow();
    return JS_UNDEFINED;
}

static JSValue js_restoreWindow(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    RestoreWindow();
    return JS_UNDEFINED;
}

static JSValue js_setWindowIcon(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    SetWindowIcon(image);
    return JS_UNDEFINED;
}

static JSValue js_setWindowTitle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * title;
    JSValue js_title;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_title;
        if(JS_GetLength(ctx,argv[0],&size_title)==-1) {
            return JS_EXCEPTION;
        }
        title = js_malloc(ctx, size_title * sizeof(char));
        for(int i0=0; i0 < size_title; i0++){
            JSValue js_title = JS_GetPropertyUint32(ctx,argv[0],i0);
            title[i0] = (char)((char *)JS_ToCString(ctx, js_title))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        title = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_title = JS_DupValue(ctx,argv[0]);
        size_t size_title;
        title = (char *)JS_GetArrayBuffer(ctx, &size_title, js_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[0]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            size_t offset_title;
            size_t size_title;
            js_title = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_title,&size_title,NULL);
            title = (char *)JS_GetArrayBuffer(ctx, &size_title, js_title);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    SetWindowTitle((const char *)title);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, title);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, title);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[0]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_title);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_setWindowPosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int x;
    JS_ToInt32(ctx, &x, argv[0]);
    int y;
    JS_ToInt32(ctx, &y, argv[1]);
    SetWindowPosition(x, y);
    return JS_UNDEFINED;
}

static JSValue js_setWindowMonitor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int monitor;
    JS_ToInt32(ctx, &monitor, argv[0]);
    SetWindowMonitor(monitor);
    return JS_UNDEFINED;
}

static JSValue js_setWindowMinSize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    SetWindowMinSize(width, height);
    return JS_UNDEFINED;
}

static JSValue js_setWindowMaxSize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    SetWindowMaxSize(width, height);
    return JS_UNDEFINED;
}

static JSValue js_setWindowSize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    SetWindowSize(width, height);
    return JS_UNDEFINED;
}

static JSValue js_setWindowOpacity(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_opacity;
    JS_ToFloat64(ctx, &double_opacity, argv[0]);
    float opacity = (float)double_opacity;
    SetWindowOpacity(opacity);
    return JS_UNDEFINED;
}

static JSValue js_setWindowFocused(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    SetWindowFocused();
    return JS_UNDEFINED;
}

static JSValue js_getScreenWidth(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetScreenWidth();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getScreenHeight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetScreenHeight();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getRenderWidth(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetRenderWidth();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getRenderHeight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetRenderHeight();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getMonitorCount(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetMonitorCount();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getCurrentMonitor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetCurrentMonitor();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getMonitorPosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int monitor;
    JS_ToInt32(ctx, &monitor, argv[0]);
    Vector2 returnVal = GetMonitorPosition(monitor);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getMonitorWidth(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int monitor;
    JS_ToInt32(ctx, &monitor, argv[0]);
    int returnVal = GetMonitorWidth(monitor);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getMonitorHeight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int monitor;
    JS_ToInt32(ctx, &monitor, argv[0]);
    int returnVal = GetMonitorHeight(monitor);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getMonitorPhysicalWidth(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int monitor;
    JS_ToInt32(ctx, &monitor, argv[0]);
    int returnVal = GetMonitorPhysicalWidth(monitor);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getMonitorPhysicalHeight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int monitor;
    JS_ToInt32(ctx, &monitor, argv[0]);
    int returnVal = GetMonitorPhysicalHeight(monitor);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getMonitorRefreshRate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int monitor;
    JS_ToInt32(ctx, &monitor, argv[0]);
    int returnVal = GetMonitorRefreshRate(monitor);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getWindowPosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetWindowPosition();
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getWindowScaleDPI(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetWindowScaleDPI();
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getMonitorName(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int monitor;
    JS_ToInt32(ctx, &monitor, argv[0]);
    const char * returnVal = GetMonitorName(monitor);
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_setClipboardText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    SetClipboardText((const char *)text);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_getClipboardText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    const char * returnVal = GetClipboardText();
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_enableEventWaiting(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EnableEventWaiting();
    return JS_UNDEFINED;
}

static JSValue js_disableEventWaiting(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    DisableEventWaiting();
    return JS_UNDEFINED;
}

static JSValue js_showCursor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    ShowCursor();
    return JS_UNDEFINED;
}

static JSValue js_hideCursor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    HideCursor();
    return JS_UNDEFINED;
}

static JSValue js_isCursorHidden(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsCursorHidden();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_enableCursor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EnableCursor();
    return JS_UNDEFINED;
}

static JSValue js_disableCursor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    DisableCursor();
    return JS_UNDEFINED;
}

static JSValue js_isCursorOnScreen(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsCursorOnScreen();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_clearBackground(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ClearBackground(color);
    return JS_UNDEFINED;
}

static JSValue js_beginDrawing(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    BeginDrawing();
    return JS_UNDEFINED;
}

static JSValue js_endDrawing(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndDrawing();
    app_update_quickjs(ctx);
    return JS_UNDEFINED;
}

static JSValue js_beginMode2D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera2D* camera_ptr = (Camera2D*)JS_GetOpaque2(ctx, argv[0], js_Camera2D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera2D camera = *camera_ptr;
    BeginMode2D(camera);
    return JS_UNDEFINED;
}

static JSValue js_endMode2D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndMode2D();
    return JS_UNDEFINED;
}

static JSValue js_beginMode3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera3D* camera_ptr = (Camera3D*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera3D camera = *camera_ptr;
    BeginMode3D(camera);
    return JS_UNDEFINED;
}

static JSValue js_endMode3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndMode3D();
    return JS_UNDEFINED;
}

static JSValue js_beginTextureMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    RenderTexture2D* target_ptr = (RenderTexture2D*)JS_GetOpaque2(ctx, argv[0], js_RenderTexture_class_id);
    if(target_ptr == NULL) return JS_EXCEPTION;
    RenderTexture2D target = *target_ptr;
    BeginTextureMode(target);
    return JS_UNDEFINED;
}

static JSValue js_endTextureMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndTextureMode();
    return JS_UNDEFINED;
}

static JSValue js_beginShaderMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* shader_ptr = (Shader*)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
    if(shader_ptr == NULL) return JS_EXCEPTION;
    Shader shader = *shader_ptr;
    BeginShaderMode(shader);
    return JS_UNDEFINED;
}

static JSValue js_endShaderMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndShaderMode();
    return JS_UNDEFINED;
}

static JSValue js_beginBlendMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int mode;
    JS_ToInt32(ctx, &mode, argv[0]);
    BeginBlendMode(mode);
    return JS_UNDEFINED;
}

static JSValue js_endBlendMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndBlendMode();
    return JS_UNDEFINED;
}

static JSValue js_beginScissorMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int x;
    JS_ToInt32(ctx, &x, argv[0]);
    int y;
    JS_ToInt32(ctx, &y, argv[1]);
    int width;
    JS_ToInt32(ctx, &width, argv[2]);
    int height;
    JS_ToInt32(ctx, &height, argv[3]);
    BeginScissorMode(x, y, width, height);
    return JS_UNDEFINED;
}

static JSValue js_endScissorMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndScissorMode();
    return JS_UNDEFINED;
}

static JSValue js_beginVrStereoMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    VrStereoConfig* config_ptr = (VrStereoConfig*)JS_GetOpaque2(ctx, argv[0], js_VrStereoConfig_class_id);
    if(config_ptr == NULL) return JS_EXCEPTION;
    VrStereoConfig config = *config_ptr;
    BeginVrStereoMode(config);
    return JS_UNDEFINED;
}

static JSValue js_endVrStereoMode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndVrStereoMode();
    return JS_UNDEFINED;
}

static JSValue js_loadVrStereoConfig(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    VrDeviceInfo* device_ptr = (VrDeviceInfo*)JS_GetOpaque2(ctx, argv[0], js_VrDeviceInfo_class_id);
    if(device_ptr == NULL) return JS_EXCEPTION;
    VrDeviceInfo device = *device_ptr;
    VrStereoConfig returnVal = LoadVrStereoConfig(device);
    VrStereoConfig* ret_ptr = (VrStereoConfig*)js_malloc(ctx, sizeof(VrStereoConfig));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_VrStereoConfig_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_unloadVrStereoConfig(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    VrStereoConfig* config_ptr = (VrStereoConfig*)JS_GetOpaque2(ctx, argv[0], js_VrStereoConfig_class_id);
    if(config_ptr == NULL) return JS_EXCEPTION;
    VrStereoConfig config = *config_ptr;
    UnloadVrStereoConfig(config);
    return JS_UNDEFINED;
}

static JSValue js_loadShader(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * vsFileName;
    JSValue js_vsFileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_vsFileName;
        if(JS_GetLength(ctx,argv[0],&size_vsFileName)==-1) {
            return JS_EXCEPTION;
        }
        vsFileName = js_malloc(ctx, size_vsFileName * sizeof(char));
        for(int i0=0; i0 < size_vsFileName; i0++){
            JSValue js_vsFileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            vsFileName[i0] = (char)((char *)JS_ToCString(ctx, js_vsFileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        vsFileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_vsFileName = JS_DupValue(ctx,argv[0]);
        size_t size_vsFileName;
        vsFileName = (char *)JS_GetArrayBuffer(ctx, &size_vsFileName, js_vsFileName);
    }
    else {
        JSClassID classid_vsFileName = JS_GetClassID(argv[0]);
        if(classid_vsFileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_vsFileName;
            size_t size_vsFileName;
            js_vsFileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_vsFileName,&size_vsFileName,NULL);
            vsFileName = (char *)JS_GetArrayBuffer(ctx, &size_vsFileName, js_vsFileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * fsFileName;
    JSValue js_fsFileName;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_fsFileName;
        if(JS_GetLength(ctx,argv[1],&size_fsFileName)==-1) {
            return JS_EXCEPTION;
        }
        fsFileName = js_malloc(ctx, size_fsFileName * sizeof(char));
        for(int i0=0; i0 < size_fsFileName; i0++){
            JSValue js_fsFileName = JS_GetPropertyUint32(ctx,argv[1],i0);
            fsFileName[i0] = (char)((char *)JS_ToCString(ctx, js_fsFileName))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        fsFileName = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_fsFileName = JS_DupValue(ctx,argv[1]);
        size_t size_fsFileName;
        fsFileName = (char *)JS_GetArrayBuffer(ctx, &size_fsFileName, js_fsFileName);
    }
    else {
        JSClassID classid_fsFileName = JS_GetClassID(argv[1]);
        if(classid_fsFileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fsFileName;
            size_t size_fsFileName;
            js_fsFileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fsFileName,&size_fsFileName,NULL);
            fsFileName = (char *)JS_GetArrayBuffer(ctx, &size_fsFileName, js_fsFileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Shader returnVal = LoadShader((const char *)vsFileName, (const char *)fsFileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, vsFileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, vsFileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_vsFileName);
    }
    else {
        JSClassID classid_vsFileName = JS_GetClassID(argv[0]);
        if(classid_vsFileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_vsFileName);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, fsFileName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fsFileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_fsFileName);
    }
    else {
        JSClassID classid_fsFileName = JS_GetClassID(argv[1]);
        if(classid_fsFileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fsFileName);
        }
    }
    Shader* ret_ptr = (Shader*)js_malloc(ctx, sizeof(Shader));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Shader_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadShaderFromMemory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * vsCode;
    JSValue js_vsCode;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_vsCode;
        if(JS_GetLength(ctx,argv[0],&size_vsCode)==-1) {
            return JS_EXCEPTION;
        }
        vsCode = js_malloc(ctx, size_vsCode * sizeof(char));
        for(int i0=0; i0 < size_vsCode; i0++){
            JSValue js_vsCode = JS_GetPropertyUint32(ctx,argv[0],i0);
            vsCode[i0] = (char)((char *)JS_ToCString(ctx, js_vsCode))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        vsCode = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_vsCode = JS_DupValue(ctx,argv[0]);
        size_t size_vsCode;
        vsCode = (char *)JS_GetArrayBuffer(ctx, &size_vsCode, js_vsCode);
    }
    else {
        JSClassID classid_vsCode = JS_GetClassID(argv[0]);
        if(classid_vsCode==JS_CLASS_INT8_ARRAY) {
            size_t offset_vsCode;
            size_t size_vsCode;
            js_vsCode = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_vsCode,&size_vsCode,NULL);
            vsCode = (char *)JS_GetArrayBuffer(ctx, &size_vsCode, js_vsCode);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * fsCode;
    JSValue js_fsCode;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_fsCode;
        if(JS_GetLength(ctx,argv[1],&size_fsCode)==-1) {
            return JS_EXCEPTION;
        }
        fsCode = js_malloc(ctx, size_fsCode * sizeof(char));
        for(int i0=0; i0 < size_fsCode; i0++){
            JSValue js_fsCode = JS_GetPropertyUint32(ctx,argv[1],i0);
            fsCode[i0] = (char)((char *)JS_ToCString(ctx, js_fsCode))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        fsCode = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_fsCode = JS_DupValue(ctx,argv[1]);
        size_t size_fsCode;
        fsCode = (char *)JS_GetArrayBuffer(ctx, &size_fsCode, js_fsCode);
    }
    else {
        JSClassID classid_fsCode = JS_GetClassID(argv[1]);
        if(classid_fsCode==JS_CLASS_INT8_ARRAY) {
            size_t offset_fsCode;
            size_t size_fsCode;
            js_fsCode = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fsCode,&size_fsCode,NULL);
            fsCode = (char *)JS_GetArrayBuffer(ctx, &size_fsCode, js_fsCode);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Shader returnVal = LoadShaderFromMemory((const char *)vsCode, (const char *)fsCode);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, vsCode);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, vsCode);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_vsCode);
    }
    else {
        JSClassID classid_vsCode = JS_GetClassID(argv[0]);
        if(classid_vsCode==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_vsCode);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, fsCode);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fsCode);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_fsCode);
    }
    else {
        JSClassID classid_fsCode = JS_GetClassID(argv[1]);
        if(classid_fsCode==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fsCode);
        }
    }
    Shader* ret_ptr = (Shader*)js_malloc(ctx, sizeof(Shader));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Shader_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_isShaderReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* shader_ptr = (Shader*)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
    if(shader_ptr == NULL) return JS_EXCEPTION;
    Shader shader = *shader_ptr;
    bool returnVal = IsShaderReady(shader);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_getShaderLocation(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* shader_ptr = (Shader*)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
    if(shader_ptr == NULL) return JS_EXCEPTION;
    Shader shader = *shader_ptr;
    char * uniformName;
    JSValue js_uniformName;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_uniformName;
        if(JS_GetLength(ctx,argv[1],&size_uniformName)==-1) {
            return JS_EXCEPTION;
        }
        uniformName = js_malloc(ctx, size_uniformName * sizeof(char));
        for(int i0=0; i0 < size_uniformName; i0++){
            JSValue js_uniformName = JS_GetPropertyUint32(ctx,argv[1],i0);
            uniformName[i0] = (char)((char *)JS_ToCString(ctx, js_uniformName))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        uniformName = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_uniformName = JS_DupValue(ctx,argv[1]);
        size_t size_uniformName;
        uniformName = (char *)JS_GetArrayBuffer(ctx, &size_uniformName, js_uniformName);
    }
    else {
        JSClassID classid_uniformName = JS_GetClassID(argv[1]);
        if(classid_uniformName==JS_CLASS_INT8_ARRAY) {
            size_t offset_uniformName;
            size_t size_uniformName;
            js_uniformName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_uniformName,&size_uniformName,NULL);
            uniformName = (char *)JS_GetArrayBuffer(ctx, &size_uniformName, js_uniformName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GetShaderLocation(shader, (const char *)uniformName);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, uniformName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, uniformName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_uniformName);
    }
    else {
        JSClassID classid_uniformName = JS_GetClassID(argv[1]);
        if(classid_uniformName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_uniformName);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getShaderLocationAttrib(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* shader_ptr = (Shader*)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
    if(shader_ptr == NULL) return JS_EXCEPTION;
    Shader shader = *shader_ptr;
    char * attribName;
    JSValue js_attribName;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_attribName;
        if(JS_GetLength(ctx,argv[1],&size_attribName)==-1) {
            return JS_EXCEPTION;
        }
        attribName = js_malloc(ctx, size_attribName * sizeof(char));
        for(int i0=0; i0 < size_attribName; i0++){
            JSValue js_attribName = JS_GetPropertyUint32(ctx,argv[1],i0);
            attribName[i0] = (char)((char *)JS_ToCString(ctx, js_attribName))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        attribName = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_attribName = JS_DupValue(ctx,argv[1]);
        size_t size_attribName;
        attribName = (char *)JS_GetArrayBuffer(ctx, &size_attribName, js_attribName);
    }
    else {
        JSClassID classid_attribName = JS_GetClassID(argv[1]);
        if(classid_attribName==JS_CLASS_INT8_ARRAY) {
            size_t offset_attribName;
            size_t size_attribName;
            js_attribName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_attribName,&size_attribName,NULL);
            attribName = (char *)JS_GetArrayBuffer(ctx, &size_attribName, js_attribName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GetShaderLocationAttrib(shader, (const char *)attribName);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, attribName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, attribName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_attribName);
    }
    else {
        JSClassID classid_attribName = JS_GetClassID(argv[1]);
        if(classid_attribName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_attribName);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_setShaderValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* shader_ptr = (Shader*)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
    if(shader_ptr == NULL) return JS_EXCEPTION;
    Shader shader = *shader_ptr;
    int locIndex;
    JS_ToInt32(ctx, &locIndex, argv[1]);
    void * value = NULL;
    float valueFloat;
    int valueInt;
    int uniformType;
    JS_ToInt32(ctx, &uniformType, argv[3]);
    switch(uniformType) {
        case SHADER_UNIFORM_FLOAT:{
            double double_valueFloat;
            JS_ToFloat64(ctx, &double_valueFloat, argv[2]);
            float valueFloat = (float)double_valueFloat;
            value = (void *)&valueFloat;
            break;
        }
        case SHADER_UNIFORM_VEC2:{
            Vector2* valueV2 = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
            if(valueV2 == NULL) return JS_EXCEPTION;
            value = (void*)valueV2;
            break;
        }
        case SHADER_UNIFORM_VEC3:{
            Vector3* valueV3 = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
            if(valueV3 == NULL) return JS_EXCEPTION;
            value = (void*)valueV3;
            break;
        }
        case SHADER_UNIFORM_VEC4:{
            Vector4* valueV4 = (Vector4*)JS_GetOpaque2(ctx, argv[2], js_Vector4_class_id);
            if(valueV4 == NULL) return JS_EXCEPTION;
            value = (void*)valueV4;
            break;
        }
        case SHADER_UNIFORM_INT:{
            JS_ToInt32(ctx, &valueInt, argv[2]);
            value = (void*)&valueInt;
            break;
        }
        default:{
            return JS_EXCEPTION;
            break;
        }
    }
    SetShaderValue(shader, locIndex, value, uniformType);
    return JS_UNDEFINED;
}

static JSValue js_setShaderValueMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* shader_ptr = (Shader*)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
    if(shader_ptr == NULL) return JS_EXCEPTION;
    Shader shader = *shader_ptr;
    int locIndex;
    JS_ToInt32(ctx, &locIndex, argv[1]);
    Matrix* mat_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[2], js_Matrix_class_id);
    if(mat_ptr == NULL) return JS_EXCEPTION;
    Matrix mat = *mat_ptr;
    SetShaderValueMatrix(shader, locIndex, mat);
    return JS_UNDEFINED;
}

static JSValue js_setShaderValueTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* shader_ptr = (Shader*)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
    if(shader_ptr == NULL) return JS_EXCEPTION;
    Shader shader = *shader_ptr;
    int locIndex;
    JS_ToInt32(ctx, &locIndex, argv[1]);
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[2], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    SetShaderValueTexture(shader, locIndex, texture);
    return JS_UNDEFINED;
}

static JSValue js_unloadShader(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* shader_ptr = (Shader*)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
    if(shader_ptr == NULL) return JS_EXCEPTION;
    Shader shader = *shader_ptr;
    UnloadShader(shader);
    return JS_UNDEFINED;
}

static JSValue js_getScreenToWorldRay(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    Camera* camera_ptr = (Camera*)JS_GetOpaque2(ctx, argv[1], js_Camera3D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera camera = *camera_ptr;
    Ray returnVal = GetScreenToWorldRay(position, camera);
    Ray* ret_ptr = (Ray*)js_malloc(ctx, sizeof(Ray));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Ray_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getScreenToWorldRayEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    Camera* camera_ptr = (Camera*)JS_GetOpaque2(ctx, argv[1], js_Camera3D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera camera = *camera_ptr;
    int width;
    JS_ToInt32(ctx, &width, argv[2]);
    int height;
    JS_ToInt32(ctx, &height, argv[3]);
    Ray returnVal = GetScreenToWorldRayEx(position, camera, width, height);
    Ray* ret_ptr = (Ray*)js_malloc(ctx, sizeof(Ray));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Ray_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getWorldToScreen(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Camera* camera_ptr = (Camera*)JS_GetOpaque2(ctx, argv[1], js_Camera3D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera camera = *camera_ptr;
    Vector2 returnVal = GetWorldToScreen(position, camera);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getWorldToScreenEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Camera* camera_ptr = (Camera*)JS_GetOpaque2(ctx, argv[1], js_Camera3D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera camera = *camera_ptr;
    int width;
    JS_ToInt32(ctx, &width, argv[2]);
    int height;
    JS_ToInt32(ctx, &height, argv[3]);
    Vector2 returnVal = GetWorldToScreenEx(position, camera, width, height);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getWorldToScreen2D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    Camera2D* camera_ptr = (Camera2D*)JS_GetOpaque2(ctx, argv[1], js_Camera2D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera2D camera = *camera_ptr;
    Vector2 returnVal = GetWorldToScreen2D(position, camera);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getScreenToWorld2D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    Camera2D* camera_ptr = (Camera2D*)JS_GetOpaque2(ctx, argv[1], js_Camera2D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera2D camera = *camera_ptr;
    Vector2 returnVal = GetScreenToWorld2D(position, camera);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getCameraMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera_ptr = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera camera = *camera_ptr;
    Matrix returnVal = GetCameraMatrix(camera);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getCameraMatrix2D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera2D* camera_ptr = (Camera2D*)JS_GetOpaque2(ctx, argv[0], js_Camera2D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera2D camera = *camera_ptr;
    Matrix returnVal = GetCameraMatrix2D(camera);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_setTargetFPS(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int fps;
    JS_ToInt32(ctx, &fps, argv[0]);
    SetTargetFPS(fps);
    return JS_UNDEFINED;
}

static JSValue js_getFrameTime(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetFrameTime();
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_getTime(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double returnVal = GetTime();
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_getFPS(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetFPS();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_setRandomSeed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned int seed;
    JS_ToUint32(ctx, &seed, argv[0]);
    SetRandomSeed(seed);
    return JS_UNDEFINED;
}

static JSValue js_getRandomValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int min;
    JS_ToInt32(ctx, &min, argv[0]);
    int max;
    JS_ToInt32(ctx, &max, argv[1]);
    int returnVal = GetRandomValue(min, max);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_loadRandomSequence(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned int count;
    JS_ToUint32(ctx, &count, argv[0]);
    int min;
    JS_ToInt32(ctx, &min, argv[1]);
    int max;
    JS_ToInt32(ctx, &max, argv[2]);
    int * returnVal = LoadRandomSequence(count, min, max);
    size_t ret_size = sizeof(returnVal);
    JSValue ret = JS_NewArray(ctx);
    for(int i=0; i < ret_size; i++){
        JSValue reti = JS_NewInt32(ctx, returnVal[i]);
        JS_DefinePropertyValue(ctx,ret,'i',reti,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_unloadRandomSequence(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int * sequence;
    JSValue js_sequence;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_sequence;
        if(JS_GetLength(ctx,argv[0],&size_sequence)==-1) {
            return JS_EXCEPTION;
        }
        sequence = js_malloc(ctx, size_sequence * sizeof(int));
        for(int i0=0; i0 < size_sequence; i0++){
            JSValue js_sequence = JS_GetPropertyUint32(ctx,argv[0],i0);
            JS_ToInt32(ctx, &sequence[i0], js_sequence);
        }
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_sequence = JS_DupValue(ctx,argv[0]);
        size_t size_sequence;
        sequence = (int *)JS_GetArrayBuffer(ctx, &size_sequence, js_sequence);
    }
    else {
        JSClassID classid_sequence = JS_GetClassID(argv[0]);
        if(classid_sequence==JS_CLASS_INT16_ARRAY) {
            size_t offset_sequence;
            size_t size_sequence;
            js_sequence = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_sequence,&size_sequence,NULL);
            sequence = (int *)JS_GetArrayBuffer(ctx, &size_sequence, js_sequence);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    UnloadRandomSequence(sequence);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, sequence);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_sequence);
    }
    else {
        JSClassID classid_sequence = JS_GetClassID(argv[0]);
        if(classid_sequence==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &js_sequence);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_takeScreenshot(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    TakeScreenshot((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_setConfigFlags(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned int flags;
    JS_ToUint32(ctx, &flags, argv[0]);
    SetConfigFlags(flags);
    return JS_UNDEFINED;
}

static JSValue js_openURL(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * url;
    JSValue js_url;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_url;
        if(JS_GetLength(ctx,argv[0],&size_url)==-1) {
            return JS_EXCEPTION;
        }
        url = js_malloc(ctx, size_url * sizeof(char));
        for(int i0=0; i0 < size_url; i0++){
            JSValue js_url = JS_GetPropertyUint32(ctx,argv[0],i0);
            url[i0] = (char)((char *)JS_ToCString(ctx, js_url))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        url = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_url = JS_DupValue(ctx,argv[0]);
        size_t size_url;
        url = (char *)JS_GetArrayBuffer(ctx, &size_url, js_url);
    }
    else {
        JSClassID classid_url = JS_GetClassID(argv[0]);
        if(classid_url==JS_CLASS_INT8_ARRAY) {
            size_t offset_url;
            size_t size_url;
            js_url = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_url,&size_url,NULL);
            url = (char *)JS_GetArrayBuffer(ctx, &size_url, js_url);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    OpenURL((const char *)url);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, url);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, url);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_url);
    }
    else {
        JSClassID classid_url = JS_GetClassID(argv[0]);
        if(classid_url==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_url);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_traceLog(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int logLevel;
    JS_ToInt32(ctx, &logLevel, argv[0]);
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    TraceLog(logLevel, (const char *)text);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_setTraceLogLevel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int logLevel;
    JS_ToInt32(ctx, &logLevel, argv[0]);
    SetTraceLogLevel(logLevel);
    return JS_UNDEFINED;
}

static JSValue js_loadFileData(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    unsigned int bytesRead;
    unsigned char * retVal = LoadFileData(fileName, &bytesRead);
    JSValue buffer = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, bytesRead);
    UnloadFileData(retVal);
    JS_FreeCString(ctx, fileName);
    return buffer;
}

static JSValue js_saveFileData(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    void * data;
    JSValue js_data;
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_data = JS_DupValue(ctx,argv[1]);
        size_t size_data;
        data = (void *)JS_GetArrayBuffer(ctx, &size_data, js_data);
    }
    else {
        return JS_EXCEPTION;
    }
    int dataSize;
    JS_ToInt32(ctx, &dataSize, argv[2]);
    bool returnVal = SaveFileData((const char *)fileName, data, dataSize);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_data);
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_loadFileText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * returnVal = LoadFileText((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    UnloadFileText(returnVal);
    return ret;
}

static JSValue js_saveFileText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = SaveFileText((const char *)fileName, text);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_fileExists(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = FileExists((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_directoryExists(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * dirPath;
    JSValue js_dirPath;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_dirPath;
        if(JS_GetLength(ctx,argv[0],&size_dirPath)==-1) {
            return JS_EXCEPTION;
        }
        dirPath = js_malloc(ctx, size_dirPath * sizeof(char));
        for(int i0=0; i0 < size_dirPath; i0++){
            JSValue js_dirPath = JS_GetPropertyUint32(ctx,argv[0],i0);
            dirPath[i0] = (char)((char *)JS_ToCString(ctx, js_dirPath))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        dirPath = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_dirPath = JS_DupValue(ctx,argv[0]);
        size_t size_dirPath;
        dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, js_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            size_t offset_dirPath;
            size_t size_dirPath;
            js_dirPath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dirPath,&size_dirPath,NULL);
            dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, js_dirPath);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = DirectoryExists((const char *)dirPath);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, dirPath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, dirPath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_dirPath);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isFileExtension(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * ext;
    JSValue js_ext;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_ext;
        if(JS_GetLength(ctx,argv[1],&size_ext)==-1) {
            return JS_EXCEPTION;
        }
        ext = js_malloc(ctx, size_ext * sizeof(char));
        for(int i0=0; i0 < size_ext; i0++){
            JSValue js_ext = JS_GetPropertyUint32(ctx,argv[1],i0);
            ext[i0] = (char)((char *)JS_ToCString(ctx, js_ext))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        ext = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_ext = JS_DupValue(ctx,argv[1]);
        size_t size_ext;
        ext = (char *)JS_GetArrayBuffer(ctx, &size_ext, js_ext);
    }
    else {
        JSClassID classid_ext = JS_GetClassID(argv[1]);
        if(classid_ext==JS_CLASS_INT8_ARRAY) {
            size_t offset_ext;
            size_t size_ext;
            js_ext = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_ext,&size_ext,NULL);
            ext = (char *)JS_GetArrayBuffer(ctx, &size_ext, js_ext);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = IsFileExtension((const char *)fileName, (const char *)ext);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, ext);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, ext);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_ext);
    }
    else {
        JSClassID classid_ext = JS_GetClassID(argv[1]);
        if(classid_ext==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_ext);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_getFileLength(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GetFileLength((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getFileExtension(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = GetFileExtension((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_getFileName(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * filePath;
    JSValue js_filePath;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_filePath;
        if(JS_GetLength(ctx,argv[0],&size_filePath)==-1) {
            return JS_EXCEPTION;
        }
        filePath = js_malloc(ctx, size_filePath * sizeof(char));
        for(int i0=0; i0 < size_filePath; i0++){
            JSValue js_filePath = JS_GetPropertyUint32(ctx,argv[0],i0);
            filePath[i0] = (char)((char *)JS_ToCString(ctx, js_filePath))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        filePath = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_filePath = JS_DupValue(ctx,argv[0]);
        size_t size_filePath;
        filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, js_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            size_t offset_filePath;
            size_t size_filePath;
            js_filePath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_filePath,&size_filePath,NULL);
            filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, js_filePath);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = GetFileName((const char *)filePath);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, filePath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, filePath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_filePath);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_getFileNameWithoutExt(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * filePath;
    JSValue js_filePath;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_filePath;
        if(JS_GetLength(ctx,argv[0],&size_filePath)==-1) {
            return JS_EXCEPTION;
        }
        filePath = js_malloc(ctx, size_filePath * sizeof(char));
        for(int i0=0; i0 < size_filePath; i0++){
            JSValue js_filePath = JS_GetPropertyUint32(ctx,argv[0],i0);
            filePath[i0] = (char)((char *)JS_ToCString(ctx, js_filePath))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        filePath = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_filePath = JS_DupValue(ctx,argv[0]);
        size_t size_filePath;
        filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, js_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            size_t offset_filePath;
            size_t size_filePath;
            js_filePath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_filePath,&size_filePath,NULL);
            filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, js_filePath);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = GetFileNameWithoutExt((const char *)filePath);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, filePath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, filePath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_filePath);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_getDirectoryPath(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * filePath;
    JSValue js_filePath;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_filePath;
        if(JS_GetLength(ctx,argv[0],&size_filePath)==-1) {
            return JS_EXCEPTION;
        }
        filePath = js_malloc(ctx, size_filePath * sizeof(char));
        for(int i0=0; i0 < size_filePath; i0++){
            JSValue js_filePath = JS_GetPropertyUint32(ctx,argv[0],i0);
            filePath[i0] = (char)((char *)JS_ToCString(ctx, js_filePath))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        filePath = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_filePath = JS_DupValue(ctx,argv[0]);
        size_t size_filePath;
        filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, js_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            size_t offset_filePath;
            size_t size_filePath;
            js_filePath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_filePath,&size_filePath,NULL);
            filePath = (char *)JS_GetArrayBuffer(ctx, &size_filePath, js_filePath);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = GetDirectoryPath((const char *)filePath);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, filePath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, filePath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_filePath);
    }
    else {
        JSClassID classid_filePath = JS_GetClassID(argv[0]);
        if(classid_filePath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_filePath);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_getPrevDirectoryPath(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * dirPath;
    JSValue js_dirPath;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_dirPath;
        if(JS_GetLength(ctx,argv[0],&size_dirPath)==-1) {
            return JS_EXCEPTION;
        }
        dirPath = js_malloc(ctx, size_dirPath * sizeof(char));
        for(int i0=0; i0 < size_dirPath; i0++){
            JSValue js_dirPath = JS_GetPropertyUint32(ctx,argv[0],i0);
            dirPath[i0] = (char)((char *)JS_ToCString(ctx, js_dirPath))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        dirPath = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_dirPath = JS_DupValue(ctx,argv[0]);
        size_t size_dirPath;
        dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, js_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            size_t offset_dirPath;
            size_t size_dirPath;
            js_dirPath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dirPath,&size_dirPath,NULL);
            dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, js_dirPath);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = GetPrevDirectoryPath((const char *)dirPath);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, dirPath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, dirPath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_dirPath);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_getWorkingDirectory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    const char * returnVal = GetWorkingDirectory();
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_getApplicationDirectory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    const char * returnVal = GetApplicationDirectory();
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_makeDirectory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * dirPath;
    JSValue js_dirPath;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_dirPath;
        if(JS_GetLength(ctx,argv[0],&size_dirPath)==-1) {
            return JS_EXCEPTION;
        }
        dirPath = js_malloc(ctx, size_dirPath * sizeof(char));
        for(int i0=0; i0 < size_dirPath; i0++){
            JSValue js_dirPath = JS_GetPropertyUint32(ctx,argv[0],i0);
            dirPath[i0] = (char)((char *)JS_ToCString(ctx, js_dirPath))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        dirPath = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_dirPath = JS_DupValue(ctx,argv[0]);
        size_t size_dirPath;
        dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, js_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            size_t offset_dirPath;
            size_t size_dirPath;
            js_dirPath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dirPath,&size_dirPath,NULL);
            dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, js_dirPath);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = MakeDirectory((const char *)dirPath);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, dirPath);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, dirPath);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_dirPath);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_changeDirectory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * dir;
    JSValue js_dir;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_dir;
        if(JS_GetLength(ctx,argv[0],&size_dir)==-1) {
            return JS_EXCEPTION;
        }
        dir = js_malloc(ctx, size_dir * sizeof(char));
        for(int i0=0; i0 < size_dir; i0++){
            JSValue js_dir = JS_GetPropertyUint32(ctx,argv[0],i0);
            dir[i0] = (char)((char *)JS_ToCString(ctx, js_dir))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        dir = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_dir = JS_DupValue(ctx,argv[0]);
        size_t size_dir;
        dir = (char *)JS_GetArrayBuffer(ctx, &size_dir, js_dir);
    }
    else {
        JSClassID classid_dir = JS_GetClassID(argv[0]);
        if(classid_dir==JS_CLASS_INT8_ARRAY) {
            size_t offset_dir;
            size_t size_dir;
            js_dir = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dir,&size_dir,NULL);
            dir = (char *)JS_GetArrayBuffer(ctx, &size_dir, js_dir);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ChangeDirectory((const char *)dir);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, dir);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, dir);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_dir);
    }
    else {
        JSClassID classid_dir = JS_GetClassID(argv[0]);
        if(classid_dir==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_dir);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isPathFile(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * path;
    JSValue js_path;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_path;
        if(JS_GetLength(ctx,argv[0],&size_path)==-1) {
            return JS_EXCEPTION;
        }
        path = js_malloc(ctx, size_path * sizeof(char));
        for(int i0=0; i0 < size_path; i0++){
            JSValue js_path = JS_GetPropertyUint32(ctx,argv[0],i0);
            path[i0] = (char)((char *)JS_ToCString(ctx, js_path))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        path = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_path = JS_DupValue(ctx,argv[0]);
        size_t size_path;
        path = (char *)JS_GetArrayBuffer(ctx, &size_path, js_path);
    }
    else {
        JSClassID classid_path = JS_GetClassID(argv[0]);
        if(classid_path==JS_CLASS_INT8_ARRAY) {
            size_t offset_path;
            size_t size_path;
            js_path = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_path,&size_path,NULL);
            path = (char *)JS_GetArrayBuffer(ctx, &size_path, js_path);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = IsPathFile((const char *)path);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, path);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, path);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_path);
    }
    else {
        JSClassID classid_path = JS_GetClassID(argv[0]);
        if(classid_path==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_path);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isFileNameValid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = IsFileNameValid((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_loadDirectoryFiles(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * dirPath;
    JSValue js_dirPath;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_dirPath;
        if(JS_GetLength(ctx,argv[0],&size_dirPath)==-1) {
            return JS_EXCEPTION;
        }
        dirPath = js_malloc(ctx, size_dirPath * sizeof(char));
        for(int i0=0; i0 < size_dirPath; i0++){
            JSValue js_dirPath = JS_GetPropertyUint32(ctx,argv[0],i0);
            dirPath[i0] = (char)((char *)JS_ToCString(ctx, js_dirPath))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        dirPath = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_dirPath = JS_DupValue(ctx,argv[0]);
        size_t size_dirPath;
        dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, js_dirPath);
    }
    else {
        JSClassID classid_dirPath = JS_GetClassID(argv[0]);
        if(classid_dirPath==JS_CLASS_INT8_ARRAY) {
            size_t offset_dirPath;
            size_t size_dirPath;
            js_dirPath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dirPath,&size_dirPath,NULL);
            dirPath = (char *)JS_GetArrayBuffer(ctx, &size_dirPath, js_dirPath);
        }
        else {
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

static JSValue js_loadDirectoryFilesEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * basePath;
    JSValue js_basePath;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_basePath;
        if(JS_GetLength(ctx,argv[0],&size_basePath)==-1) {
            return JS_EXCEPTION;
        }
        basePath = js_malloc(ctx, size_basePath * sizeof(char));
        for(int i0=0; i0 < size_basePath; i0++){
            JSValue js_basePath = JS_GetPropertyUint32(ctx,argv[0],i0);
            basePath[i0] = (char)((char *)JS_ToCString(ctx, js_basePath))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        basePath = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_basePath = JS_DupValue(ctx,argv[0]);
        size_t size_basePath;
        basePath = (char *)JS_GetArrayBuffer(ctx, &size_basePath, js_basePath);
    }
    else {
        JSClassID classid_basePath = JS_GetClassID(argv[0]);
        if(classid_basePath==JS_CLASS_INT8_ARRAY) {
            size_t offset_basePath;
            size_t size_basePath;
            js_basePath = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_basePath,&size_basePath,NULL);
            basePath = (char *)JS_GetArrayBuffer(ctx, &size_basePath, js_basePath);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * filter;
    JSValue js_filter;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_filter;
        if(JS_GetLength(ctx,argv[1],&size_filter)==-1) {
            return JS_EXCEPTION;
        }
        filter = js_malloc(ctx, size_filter * sizeof(char));
        for(int i0=0; i0 < size_filter; i0++){
            JSValue js_filter = JS_GetPropertyUint32(ctx,argv[1],i0);
            filter[i0] = (char)((char *)JS_ToCString(ctx, js_filter))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        filter = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_filter = JS_DupValue(ctx,argv[1]);
        size_t size_filter;
        filter = (char *)JS_GetArrayBuffer(ctx, &size_filter, js_filter);
    }
    else {
        JSClassID classid_filter = JS_GetClassID(argv[1]);
        if(classid_filter==JS_CLASS_INT8_ARRAY) {
            size_t offset_filter;
            size_t size_filter;
            js_filter = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_filter,&size_filter,NULL);
            filter = (char *)JS_GetArrayBuffer(ctx, &size_filter, js_filter);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool scanSubdirs = JS_ToBool(ctx, argv[2]);
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

static JSValue js_isFileDropped(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsFileDropped();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_loadDroppedFiles(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    FilePathList files = LoadDroppedFiles();
    JSValue ret = JS_NewArray(ctx);
    for(int i=0; i < files.count; i++){
        JS_SetPropertyUint32(ctx, ret, i, JS_NewString(ctx,files.paths[i]));
    }
    UnloadDroppedFiles(files);
    return ret;
}

static JSValue js_getFileModTime(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    long returnVal = GetFileModTime((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_loadAutomationEventList(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    AutomationEventList returnVal = LoadAutomationEventList((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    AutomationEventList* ret_ptr = (AutomationEventList*)js_malloc(ctx, sizeof(AutomationEventList));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_AutomationEventList_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_unloadAutomationEventList(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AutomationEventList* list_ptr = (AutomationEventList*)JS_GetOpaque2(ctx, argv[0], js_AutomationEventList_class_id);
    if(list_ptr == NULL) return JS_EXCEPTION;
    AutomationEventList list = *list_ptr;
    UnloadAutomationEventList(list);
    return JS_UNDEFINED;
}

static JSValue js_exportAutomationEventList(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AutomationEventList* list_ptr = (AutomationEventList*)JS_GetOpaque2(ctx, argv[0], js_AutomationEventList_class_id);
    if(list_ptr == NULL) return JS_EXCEPTION;
    AutomationEventList list = *list_ptr;
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[1],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[1],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[1]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ExportAutomationEventList(list, (const char *)fileName);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_setAutomationEventList(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AutomationEventList* list = (AutomationEventList*)JS_GetOpaque2(ctx, argv[0], js_AutomationEventList_class_id);
    if(list == NULL) return JS_EXCEPTION;
    SetAutomationEventList(list);
    return JS_UNDEFINED;
}

static JSValue js_setAutomationEventBaseFrame(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int frame;
    JS_ToInt32(ctx, &frame, argv[0]);
    SetAutomationEventBaseFrame(frame);
    return JS_UNDEFINED;
}

static JSValue js_startAutomationEventRecording(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    StartAutomationEventRecording();
    return JS_UNDEFINED;
}

static JSValue js_stopAutomationEventRecording(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    StopAutomationEventRecording();
    return JS_UNDEFINED;
}

static JSValue js_playAutomationEvent(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    AutomationEvent* event_ptr = (AutomationEvent*)JS_GetOpaque2(ctx, argv[0], js_AutomationEvent_class_id);
    if(event_ptr == NULL) return JS_EXCEPTION;
    AutomationEvent event = *event_ptr;
    PlayAutomationEvent(event);
    return JS_UNDEFINED;
}

static JSValue js_isKeyPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int key;
    JS_ToInt32(ctx, &key, argv[0]);
    bool returnVal = IsKeyPressed(key);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isKeyPressedRepeat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int key;
    JS_ToInt32(ctx, &key, argv[0]);
    bool returnVal = IsKeyPressedRepeat(key);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isKeyDown(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int key;
    JS_ToInt32(ctx, &key, argv[0]);
    bool returnVal = IsKeyDown(key);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isKeyReleased(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int key;
    JS_ToInt32(ctx, &key, argv[0]);
    bool returnVal = IsKeyReleased(key);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isKeyUp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int key;
    JS_ToInt32(ctx, &key, argv[0]);
    bool returnVal = IsKeyUp(key);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_getKeyPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetKeyPressed();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getCharPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetCharPressed();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_setExitKey(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int key;
    JS_ToInt32(ctx, &key, argv[0]);
    SetExitKey(key);
    return JS_UNDEFINED;
}

static JSValue js_isGamepadAvailable(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int gamepad;
    JS_ToInt32(ctx, &gamepad, argv[0]);
    bool returnVal = IsGamepadAvailable(gamepad);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_getGamepadName(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int gamepad;
    JS_ToInt32(ctx, &gamepad, argv[0]);
    const char * returnVal = GetGamepadName(gamepad);
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_isGamepadButtonPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int gamepad;
    JS_ToInt32(ctx, &gamepad, argv[0]);
    int button;
    JS_ToInt32(ctx, &button, argv[1]);
    bool returnVal = IsGamepadButtonPressed(gamepad, button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isGamepadButtonDown(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int gamepad;
    JS_ToInt32(ctx, &gamepad, argv[0]);
    int button;
    JS_ToInt32(ctx, &button, argv[1]);
    bool returnVal = IsGamepadButtonDown(gamepad, button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isGamepadButtonReleased(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int gamepad;
    JS_ToInt32(ctx, &gamepad, argv[0]);
    int button;
    JS_ToInt32(ctx, &button, argv[1]);
    bool returnVal = IsGamepadButtonReleased(gamepad, button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isGamepadButtonUp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int gamepad;
    JS_ToInt32(ctx, &gamepad, argv[0]);
    int button;
    JS_ToInt32(ctx, &button, argv[1]);
    bool returnVal = IsGamepadButtonUp(gamepad, button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_getGamepadButtonPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetGamepadButtonPressed();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getGamepadAxisCount(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int gamepad;
    JS_ToInt32(ctx, &gamepad, argv[0]);
    int returnVal = GetGamepadAxisCount(gamepad);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getGamepadAxisMovement(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int gamepad;
    JS_ToInt32(ctx, &gamepad, argv[0]);
    int axis;
    JS_ToInt32(ctx, &axis, argv[1]);
    float returnVal = GetGamepadAxisMovement(gamepad, axis);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_setGamepadMappings(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * mappings;
    JSValue js_mappings;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_mappings;
        if(JS_GetLength(ctx,argv[0],&size_mappings)==-1) {
            return JS_EXCEPTION;
        }
        mappings = js_malloc(ctx, size_mappings * sizeof(char));
        for(int i0=0; i0 < size_mappings; i0++){
            JSValue js_mappings = JS_GetPropertyUint32(ctx,argv[0],i0);
            mappings[i0] = (char)((char *)JS_ToCString(ctx, js_mappings))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        mappings = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_mappings = JS_DupValue(ctx,argv[0]);
        size_t size_mappings;
        mappings = (char *)JS_GetArrayBuffer(ctx, &size_mappings, js_mappings);
    }
    else {
        JSClassID classid_mappings = JS_GetClassID(argv[0]);
        if(classid_mappings==JS_CLASS_INT8_ARRAY) {
            size_t offset_mappings;
            size_t size_mappings;
            js_mappings = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_mappings,&size_mappings,NULL);
            mappings = (char *)JS_GetArrayBuffer(ctx, &size_mappings, js_mappings);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = SetGamepadMappings((const char *)mappings);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, mappings);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, mappings);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_mappings);
    }
    else {
        JSClassID classid_mappings = JS_GetClassID(argv[0]);
        if(classid_mappings==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_mappings);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_setGamepadVibration(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int gamepad;
    JS_ToInt32(ctx, &gamepad, argv[0]);
    double double_leftMotor;
    JS_ToFloat64(ctx, &double_leftMotor, argv[1]);
    float leftMotor = (float)double_leftMotor;
    double double_rightMotor;
    JS_ToFloat64(ctx, &double_rightMotor, argv[2]);
    float rightMotor = (float)double_rightMotor;
    SetGamepadVibration(gamepad, leftMotor, rightMotor);
    return JS_UNDEFINED;
}

static JSValue js_isMouseButtonPressed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int button;
    JS_ToInt32(ctx, &button, argv[0]);
    bool returnVal = IsMouseButtonPressed(button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isMouseButtonDown(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int button;
    JS_ToInt32(ctx, &button, argv[0]);
    bool returnVal = IsMouseButtonDown(button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isMouseButtonReleased(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int button;
    JS_ToInt32(ctx, &button, argv[0]);
    bool returnVal = IsMouseButtonReleased(button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_isMouseButtonUp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int button;
    JS_ToInt32(ctx, &button, argv[0]);
    bool returnVal = IsMouseButtonUp(button);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_getMouseX(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetMouseX();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getMouseY(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetMouseY();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getMousePosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetMousePosition();
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getMouseDelta(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetMouseDelta();
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_setMousePosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int x;
    JS_ToInt32(ctx, &x, argv[0]);
    int y;
    JS_ToInt32(ctx, &y, argv[1]);
    SetMousePosition(x, y);
    return JS_UNDEFINED;
}

static JSValue js_setMouseOffset(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int offsetX;
    JS_ToInt32(ctx, &offsetX, argv[0]);
    int offsetY;
    JS_ToInt32(ctx, &offsetY, argv[1]);
    SetMouseOffset(offsetX, offsetY);
    return JS_UNDEFINED;
}

static JSValue js_setMouseScale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_scaleX;
    JS_ToFloat64(ctx, &double_scaleX, argv[0]);
    float scaleX = (float)double_scaleX;
    double double_scaleY;
    JS_ToFloat64(ctx, &double_scaleY, argv[1]);
    float scaleY = (float)double_scaleY;
    SetMouseScale(scaleX, scaleY);
    return JS_UNDEFINED;
}

static JSValue js_getMouseWheelMove(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetMouseWheelMove();
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_getMouseWheelMoveV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetMouseWheelMoveV();
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_setMouseCursor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int cursor;
    JS_ToInt32(ctx, &cursor, argv[0]);
    SetMouseCursor(cursor);
    return JS_UNDEFINED;
}

static JSValue js_getTouchX(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetTouchX();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getTouchY(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetTouchY();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getTouchPosition(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int index;
    JS_ToInt32(ctx, &index, argv[0]);
    Vector2 returnVal = GetTouchPosition(index);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getTouchPointId(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int index;
    JS_ToInt32(ctx, &index, argv[0]);
    int returnVal = GetTouchPointId(index);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getTouchPointCount(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetTouchPointCount();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_setGesturesEnabled(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned int flags;
    JS_ToUint32(ctx, &flags, argv[0]);
    SetGesturesEnabled(flags);
    return JS_UNDEFINED;
}

static JSValue js_isGestureDetected(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned int gesture;
    JS_ToUint32(ctx, &gesture, argv[0]);
    bool returnVal = IsGestureDetected(gesture);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_getGestureDetected(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GetGestureDetected();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getGestureHoldDuration(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetGestureHoldDuration();
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_getGestureDragVector(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetGestureDragVector();
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getGestureDragAngle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetGestureDragAngle();
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_getGesturePinchVector(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = GetGesturePinchVector();
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getGesturePinchAngle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetGesturePinchAngle();
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_updateCamera(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    int mode;
    JS_ToInt32(ctx, &mode, argv[1]);
    UpdateCamera(camera, mode);
    return JS_UNDEFINED;
}

static JSValue js_updateCameraPro(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    Vector3* movement_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(movement_ptr == NULL) return JS_EXCEPTION;
    Vector3 movement = *movement_ptr;
    Vector3* rotation_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(rotation_ptr == NULL) return JS_EXCEPTION;
    Vector3 rotation = *rotation_ptr;
    double double_zoom;
    JS_ToFloat64(ctx, &double_zoom, argv[3]);
    float zoom = (float)double_zoom;
    UpdateCameraPro(camera, movement, rotation, zoom);
    return JS_UNDEFINED;
}

static JSValue js_setShapesTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    Rectangle* source_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
    if(source_ptr == NULL) return JS_EXCEPTION;
    Rectangle source = *source_ptr;
    SetShapesTexture(texture, source);
    return JS_UNDEFINED;
}

static JSValue js_getShapesTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D returnVal = GetShapesTexture();
    Texture2D* ret_ptr = (Texture2D*)js_malloc(ctx, sizeof(Texture2D));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getShapesTextureRectangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle returnVal = GetShapesTextureRectangle();
    Rectangle* ret_ptr = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_drawPixel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int posX;
    JS_ToInt32(ctx, &posX, argv[0]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[1]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawPixel(posX, posY, color);
    return JS_UNDEFINED;
}

static JSValue js_drawPixelV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawPixelV(position, color);
    return JS_UNDEFINED;
}

static JSValue js_drawLine(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int startPosX;
    JS_ToInt32(ctx, &startPosX, argv[0]);
    int startPosY;
    JS_ToInt32(ctx, &startPosY, argv[1]);
    int endPosX;
    JS_ToInt32(ctx, &endPosX, argv[2]);
    int endPosY;
    JS_ToInt32(ctx, &endPosY, argv[3]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawLine(startPosX, startPosY, endPosX, endPosY, color);
    return JS_UNDEFINED;
}

static JSValue js_drawLineV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* startPos_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(startPos_ptr == NULL) return JS_EXCEPTION;
    Vector2 startPos = *startPos_ptr;
    Vector2* endPos_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(endPos_ptr == NULL) return JS_EXCEPTION;
    Vector2 endPos = *endPos_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawLineV(startPos, endPos, color);
    return JS_UNDEFINED;
}

static JSValue js_drawLineEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* startPos_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(startPos_ptr == NULL) return JS_EXCEPTION;
    Vector2 startPos = *startPos_ptr;
    Vector2* endPos_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(endPos_ptr == NULL) return JS_EXCEPTION;
    Vector2 endPos = *endPos_ptr;
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[2]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawLineEx(startPos, endPos, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawLineBezier(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* startPos_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(startPos_ptr == NULL) return JS_EXCEPTION;
    Vector2 startPos = *startPos_ptr;
    Vector2* endPos_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(endPos_ptr == NULL) return JS_EXCEPTION;
    Vector2 endPos = *endPos_ptr;
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[2]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawLineBezier(startPos, endPos, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCircle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int centerX;
    JS_ToInt32(ctx, &centerX, argv[0]);
    int centerY;
    JS_ToInt32(ctx, &centerY, argv[1]);
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[2]);
    float radius = (float)double_radius;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCircle(centerX, centerY, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCircleSector(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[1]);
    float radius = (float)double_radius;
    double double_startAngle;
    JS_ToFloat64(ctx, &double_startAngle, argv[2]);
    float startAngle = (float)double_startAngle;
    double double_endAngle;
    JS_ToFloat64(ctx, &double_endAngle, argv[3]);
    float endAngle = (float)double_endAngle;
    int segments;
    JS_ToInt32(ctx, &segments, argv[4]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCircleSectorLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[1]);
    float radius = (float)double_radius;
    double double_startAngle;
    JS_ToFloat64(ctx, &double_startAngle, argv[2]);
    float startAngle = (float)double_startAngle;
    double double_endAngle;
    JS_ToFloat64(ctx, &double_endAngle, argv[3]);
    float endAngle = (float)double_endAngle;
    int segments;
    JS_ToInt32(ctx, &segments, argv[4]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCircleGradient(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int centerX;
    JS_ToInt32(ctx, &centerX, argv[0]);
    int centerY;
    JS_ToInt32(ctx, &centerY, argv[1]);
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[2]);
    float radius = (float)double_radius;
    Color* inner_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(inner_ptr == NULL) return JS_EXCEPTION;
    Color inner = *inner_ptr;
    Color* outer_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(outer_ptr == NULL) return JS_EXCEPTION;
    Color outer = *outer_ptr;
    DrawCircleGradient(centerX, centerY, radius, inner, outer);
    return JS_UNDEFINED;
}

static JSValue js_drawCircleV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[1]);
    float radius = (float)double_radius;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCircleV(center, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCircleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int centerX;
    JS_ToInt32(ctx, &centerX, argv[0]);
    int centerY;
    JS_ToInt32(ctx, &centerY, argv[1]);
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[2]);
    float radius = (float)double_radius;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCircleLines(centerX, centerY, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCircleLinesV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[1]);
    float radius = (float)double_radius;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCircleLinesV(center, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_drawEllipse(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int centerX;
    JS_ToInt32(ctx, &centerX, argv[0]);
    int centerY;
    JS_ToInt32(ctx, &centerY, argv[1]);
    double double_radiusH;
    JS_ToFloat64(ctx, &double_radiusH, argv[2]);
    float radiusH = (float)double_radiusH;
    double double_radiusV;
    JS_ToFloat64(ctx, &double_radiusV, argv[3]);
    float radiusV = (float)double_radiusV;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawEllipse(centerX, centerY, radiusH, radiusV, color);
    return JS_UNDEFINED;
}

static JSValue js_drawEllipseLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int centerX;
    JS_ToInt32(ctx, &centerX, argv[0]);
    int centerY;
    JS_ToInt32(ctx, &centerY, argv[1]);
    double double_radiusH;
    JS_ToFloat64(ctx, &double_radiusH, argv[2]);
    float radiusH = (float)double_radiusH;
    double double_radiusV;
    JS_ToFloat64(ctx, &double_radiusV, argv[3]);
    float radiusV = (float)double_radiusV;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawEllipseLines(centerX, centerY, radiusH, radiusV, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRing(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    double double_innerRadius;
    JS_ToFloat64(ctx, &double_innerRadius, argv[1]);
    float innerRadius = (float)double_innerRadius;
    double double_outerRadius;
    JS_ToFloat64(ctx, &double_outerRadius, argv[2]);
    float outerRadius = (float)double_outerRadius;
    double double_startAngle;
    JS_ToFloat64(ctx, &double_startAngle, argv[3]);
    float startAngle = (float)double_startAngle;
    double double_endAngle;
    JS_ToFloat64(ctx, &double_endAngle, argv[4]);
    float endAngle = (float)double_endAngle;
    int segments;
    JS_ToInt32(ctx, &segments, argv[5]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[6], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRingLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    double double_innerRadius;
    JS_ToFloat64(ctx, &double_innerRadius, argv[1]);
    float innerRadius = (float)double_innerRadius;
    double double_outerRadius;
    JS_ToFloat64(ctx, &double_outerRadius, argv[2]);
    float outerRadius = (float)double_outerRadius;
    double double_startAngle;
    JS_ToFloat64(ctx, &double_startAngle, argv[3]);
    float startAngle = (float)double_startAngle;
    double double_endAngle;
    JS_ToFloat64(ctx, &double_endAngle, argv[4]);
    float endAngle = (float)double_endAngle;
    int segments;
    JS_ToInt32(ctx, &segments, argv[5]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[6], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRectangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int posX;
    JS_ToInt32(ctx, &posX, argv[0]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[1]);
    int width;
    JS_ToInt32(ctx, &width, argv[2]);
    int height;
    JS_ToInt32(ctx, &height, argv[3]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRectangle(posX, posY, width, height, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRectangleV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    Vector2* size_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(size_ptr == NULL) return JS_EXCEPTION;
    Vector2 size = *size_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRectangleV(position, size, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRectangleRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRectangleRec(rec, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRectanglePro(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    Vector2* origin_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(origin_ptr == NULL) return JS_EXCEPTION;
    Vector2 origin = *origin_ptr;
    double double_rotation;
    JS_ToFloat64(ctx, &double_rotation, argv[2]);
    float rotation = (float)double_rotation;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRectanglePro(rec, origin, rotation, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRectangleGradientV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int posX;
    JS_ToInt32(ctx, &posX, argv[0]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[1]);
    int width;
    JS_ToInt32(ctx, &width, argv[2]);
    int height;
    JS_ToInt32(ctx, &height, argv[3]);
    Color* top_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(top_ptr == NULL) return JS_EXCEPTION;
    Color top = *top_ptr;
    Color* bottom_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(bottom_ptr == NULL) return JS_EXCEPTION;
    Color bottom = *bottom_ptr;
    DrawRectangleGradientV(posX, posY, width, height, top, bottom);
    return JS_UNDEFINED;
}

static JSValue js_drawRectangleGradientH(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int posX;
    JS_ToInt32(ctx, &posX, argv[0]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[1]);
    int width;
    JS_ToInt32(ctx, &width, argv[2]);
    int height;
    JS_ToInt32(ctx, &height, argv[3]);
    Color* left_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(left_ptr == NULL) return JS_EXCEPTION;
    Color left = *left_ptr;
    Color* right_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(right_ptr == NULL) return JS_EXCEPTION;
    Color right = *right_ptr;
    DrawRectangleGradientH(posX, posY, width, height, left, right);
    return JS_UNDEFINED;
}

static JSValue js_drawRectangleGradientEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    Color* topLeft_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(topLeft_ptr == NULL) return JS_EXCEPTION;
    Color topLeft = *topLeft_ptr;
    Color* bottomLeft_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(bottomLeft_ptr == NULL) return JS_EXCEPTION;
    Color bottomLeft = *bottomLeft_ptr;
    Color* topRight_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(topRight_ptr == NULL) return JS_EXCEPTION;
    Color topRight = *topRight_ptr;
    Color* bottomRight_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(bottomRight_ptr == NULL) return JS_EXCEPTION;
    Color bottomRight = *bottomRight_ptr;
    DrawRectangleGradientEx(rec, topLeft, bottomLeft, topRight, bottomRight);
    return JS_UNDEFINED;
}

static JSValue js_drawRectangleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int posX;
    JS_ToInt32(ctx, &posX, argv[0]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[1]);
    int width;
    JS_ToInt32(ctx, &width, argv[2]);
    int height;
    JS_ToInt32(ctx, &height, argv[3]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRectangleLines(posX, posY, width, height, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRectangleLinesEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    double double_lineThick;
    JS_ToFloat64(ctx, &double_lineThick, argv[1]);
    float lineThick = (float)double_lineThick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRectangleLinesEx(rec, lineThick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRectangleRounded(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    double double_roundness;
    JS_ToFloat64(ctx, &double_roundness, argv[1]);
    float roundness = (float)double_roundness;
    int segments;
    JS_ToInt32(ctx, &segments, argv[2]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRectangleRounded(rec, roundness, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRectangleRoundedLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    double double_roundness;
    JS_ToFloat64(ctx, &double_roundness, argv[1]);
    float roundness = (float)double_roundness;
    int segments;
    JS_ToInt32(ctx, &segments, argv[2]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRectangleRoundedLines(rec, roundness, segments, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRectangleRoundedLinesEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    double double_roundness;
    JS_ToFloat64(ctx, &double_roundness, argv[1]);
    float roundness = (float)double_roundness;
    int segments;
    JS_ToInt32(ctx, &segments, argv[2]);
    double double_lineThick;
    JS_ToFloat64(ctx, &double_lineThick, argv[3]);
    float lineThick = (float)double_lineThick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRectangleRoundedLinesEx(rec, roundness, segments, lineThick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawTriangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    Vector2* v3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(v3_ptr == NULL) return JS_EXCEPTION;
    Vector2 v3 = *v3_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawTriangle(v1, v2, v3, color);
    return JS_UNDEFINED;
}

static JSValue js_drawTriangleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    Vector2* v3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(v3_ptr == NULL) return JS_EXCEPTION;
    Vector2 v3 = *v3_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawTriangleLines(v1, v2, v3, color);
    return JS_UNDEFINED;
}

static JSValue js_drawPoly(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    int sides;
    JS_ToInt32(ctx, &sides, argv[1]);
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[2]);
    float radius = (float)double_radius;
    double double_rotation;
    JS_ToFloat64(ctx, &double_rotation, argv[3]);
    float rotation = (float)double_rotation;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawPoly(center, sides, radius, rotation, color);
    return JS_UNDEFINED;
}

static JSValue js_drawPolyLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    int sides;
    JS_ToInt32(ctx, &sides, argv[1]);
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[2]);
    float radius = (float)double_radius;
    double double_rotation;
    JS_ToFloat64(ctx, &double_rotation, argv[3]);
    float rotation = (float)double_rotation;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawPolyLines(center, sides, radius, rotation, color);
    return JS_UNDEFINED;
}

static JSValue js_drawPolyLinesEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    int sides;
    JS_ToInt32(ctx, &sides, argv[1]);
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[2]);
    float radius = (float)double_radius;
    double double_rotation;
    JS_ToFloat64(ctx, &double_rotation, argv[3]);
    float rotation = (float)double_rotation;
    double double_lineThick;
    JS_ToFloat64(ctx, &double_lineThick, argv[4]);
    float lineThick = (float)double_lineThick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawPolyLinesEx(center, sides, radius, rotation, lineThick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSplineLinear(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* points = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(points == NULL) return JS_EXCEPTION;
    int pointCount;
    JS_ToInt32(ctx, &pointCount, argv[1]);
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[2]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSplineLinear((const Vector2 *)points, pointCount, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSplineBasis(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* points = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(points == NULL) return JS_EXCEPTION;
    int pointCount;
    JS_ToInt32(ctx, &pointCount, argv[1]);
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[2]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSplineBasis((const Vector2 *)points, pointCount, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSplineCatmullRom(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* points = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(points == NULL) return JS_EXCEPTION;
    int pointCount;
    JS_ToInt32(ctx, &pointCount, argv[1]);
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[2]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSplineCatmullRom((const Vector2 *)points, pointCount, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSplineBezierQuadratic(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* points = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(points == NULL) return JS_EXCEPTION;
    int pointCount;
    JS_ToInt32(ctx, &pointCount, argv[1]);
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[2]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSplineBezierQuadratic((const Vector2 *)points, pointCount, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSplineBezierCubic(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* points = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(points == NULL) return JS_EXCEPTION;
    int pointCount;
    JS_ToInt32(ctx, &pointCount, argv[1]);
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[2]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSplineBezierCubic((const Vector2 *)points, pointCount, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSplineSegmentLinear(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* p2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(p2_ptr == NULL) return JS_EXCEPTION;
    Vector2 p2 = *p2_ptr;
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[2]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSplineSegmentLinear(p1, p2, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSplineSegmentBasis(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* p2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(p2_ptr == NULL) return JS_EXCEPTION;
    Vector2 p2 = *p2_ptr;
    Vector2* p3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(p3_ptr == NULL) return JS_EXCEPTION;
    Vector2 p3 = *p3_ptr;
    Vector2* p4_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(p4_ptr == NULL) return JS_EXCEPTION;
    Vector2 p4 = *p4_ptr;
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[4]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSplineSegmentBasis(p1, p2, p3, p4, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSplineSegmentCatmullRom(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* p2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(p2_ptr == NULL) return JS_EXCEPTION;
    Vector2 p2 = *p2_ptr;
    Vector2* p3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(p3_ptr == NULL) return JS_EXCEPTION;
    Vector2 p3 = *p3_ptr;
    Vector2* p4_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(p4_ptr == NULL) return JS_EXCEPTION;
    Vector2 p4 = *p4_ptr;
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[4]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSplineSegmentCatmullRom(p1, p2, p3, p4, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSplineSegmentBezierQuadratic(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* c2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(c2_ptr == NULL) return JS_EXCEPTION;
    Vector2 c2 = *c2_ptr;
    Vector2* p3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(p3_ptr == NULL) return JS_EXCEPTION;
    Vector2 p3 = *p3_ptr;
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[3]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSplineSegmentBezierQuadratic(p1, c2, p3, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSplineSegmentBezierCubic(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* c2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(c2_ptr == NULL) return JS_EXCEPTION;
    Vector2 c2 = *c2_ptr;
    Vector2* c3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(c3_ptr == NULL) return JS_EXCEPTION;
    Vector2 c3 = *c3_ptr;
    Vector2* p4_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(p4_ptr == NULL) return JS_EXCEPTION;
    Vector2 p4 = *p4_ptr;
    double double_thick;
    JS_ToFloat64(ctx, &double_thick, argv[4]);
    float thick = (float)double_thick;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSplineSegmentBezierCubic(p1, c2, c3, p4, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_getSplinePointLinear(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* startPos_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(startPos_ptr == NULL) return JS_EXCEPTION;
    Vector2 startPos = *startPos_ptr;
    Vector2* endPos_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(endPos_ptr == NULL) return JS_EXCEPTION;
    Vector2 endPos = *endPos_ptr;
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[2]);
    float t = (float)double_t;
    Vector2 returnVal = GetSplinePointLinear(startPos, endPos, t);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getSplinePointBasis(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* p2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(p2_ptr == NULL) return JS_EXCEPTION;
    Vector2 p2 = *p2_ptr;
    Vector2* p3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(p3_ptr == NULL) return JS_EXCEPTION;
    Vector2 p3 = *p3_ptr;
    Vector2* p4_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(p4_ptr == NULL) return JS_EXCEPTION;
    Vector2 p4 = *p4_ptr;
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[4]);
    float t = (float)double_t;
    Vector2 returnVal = GetSplinePointBasis(p1, p2, p3, p4, t);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getSplinePointCatmullRom(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* p2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(p2_ptr == NULL) return JS_EXCEPTION;
    Vector2 p2 = *p2_ptr;
    Vector2* p3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(p3_ptr == NULL) return JS_EXCEPTION;
    Vector2 p3 = *p3_ptr;
    Vector2* p4_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(p4_ptr == NULL) return JS_EXCEPTION;
    Vector2 p4 = *p4_ptr;
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[4]);
    float t = (float)double_t;
    Vector2 returnVal = GetSplinePointCatmullRom(p1, p2, p3, p4, t);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getSplinePointBezierQuad(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* c2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(c2_ptr == NULL) return JS_EXCEPTION;
    Vector2 c2 = *c2_ptr;
    Vector2* p3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(p3_ptr == NULL) return JS_EXCEPTION;
    Vector2 p3 = *p3_ptr;
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[3]);
    float t = (float)double_t;
    Vector2 returnVal = GetSplinePointBezierQuad(p1, c2, p3, t);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getSplinePointBezierCubic(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* c2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(c2_ptr == NULL) return JS_EXCEPTION;
    Vector2 c2 = *c2_ptr;
    Vector2* c3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(c3_ptr == NULL) return JS_EXCEPTION;
    Vector2 c3 = *c3_ptr;
    Vector2* p4_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(p4_ptr == NULL) return JS_EXCEPTION;
    Vector2 p4 = *p4_ptr;
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[4]);
    float t = (float)double_t;
    Vector2 returnVal = GetSplinePointBezierCubic(p1, c2, c3, p4, t);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_checkCollisionRecs(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* rec1_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(rec1_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec1 = *rec1_ptr;
    Rectangle* rec2_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
    if(rec2_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec2 = *rec2_ptr;
    bool returnVal = CheckCollisionRecs(rec1, rec2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_checkCollisionCircles(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center1_ptr == NULL) return JS_EXCEPTION;
    Vector2 center1 = *center1_ptr;
    double double_radius1;
    JS_ToFloat64(ctx, &double_radius1, argv[1]);
    float radius1 = (float)double_radius1;
    Vector2* center2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(center2_ptr == NULL) return JS_EXCEPTION;
    Vector2 center2 = *center2_ptr;
    double double_radius2;
    JS_ToFloat64(ctx, &double_radius2, argv[3]);
    float radius2 = (float)double_radius2;
    bool returnVal = CheckCollisionCircles(center1, radius1, center2, radius2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_checkCollisionCircleRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[1]);
    float radius = (float)double_radius;
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    bool returnVal = CheckCollisionCircleRec(center, radius, rec);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_checkCollisionPointRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* point_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(point_ptr == NULL) return JS_EXCEPTION;
    Vector2 point = *point_ptr;
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    bool returnVal = CheckCollisionPointRec(point, rec);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_checkCollisionPointCircle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* point_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(point_ptr == NULL) return JS_EXCEPTION;
    Vector2 point = *point_ptr;
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[2]);
    float radius = (float)double_radius;
    bool returnVal = CheckCollisionPointCircle(point, center, radius);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_checkCollisionPointTriangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* point_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(point_ptr == NULL) return JS_EXCEPTION;
    Vector2 point = *point_ptr;
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* p2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(p2_ptr == NULL) return JS_EXCEPTION;
    Vector2 p2 = *p2_ptr;
    Vector2* p3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(p3_ptr == NULL) return JS_EXCEPTION;
    Vector2 p3 = *p3_ptr;
    bool returnVal = CheckCollisionPointTriangle(point, p1, p2, p3);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_checkCollisionPointLine(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* point_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(point_ptr == NULL) return JS_EXCEPTION;
    Vector2 point = *point_ptr;
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* p2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(p2_ptr == NULL) return JS_EXCEPTION;
    Vector2 p2 = *p2_ptr;
    int threshold;
    JS_ToInt32(ctx, &threshold, argv[3]);
    bool returnVal = CheckCollisionPointLine(point, p1, p2, threshold);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_checkCollisionCircleLine(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[1]);
    float radius = (float)double_radius;
    Vector2* p1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector2 p1 = *p1_ptr;
    Vector2* p2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(p2_ptr == NULL) return JS_EXCEPTION;
    Vector2 p2 = *p2_ptr;
    bool returnVal = CheckCollisionCircleLine(center, radius, p1, p2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_getCollisionRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* rec1_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(rec1_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec1 = *rec1_ptr;
    Rectangle* rec2_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
    if(rec2_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec2 = *rec2_ptr;
    Rectangle returnVal = GetCollisionRec(rec1, rec2);
    Rectangle* ret_ptr = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Image returnVal = LoadImage((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadImageRaw(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int width;
    JS_ToInt32(ctx, &width, argv[1]);
    int height;
    JS_ToInt32(ctx, &height, argv[2]);
    int format;
    JS_ToInt32(ctx, &format, argv[3]);
    int headerSize;
    JS_ToInt32(ctx, &headerSize, argv[4]);
    Image returnVal = LoadImageRaw((const char *)fileName, width, height, format, headerSize);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadImageSvg(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileNameOrString;
    JSValue js_fileNameOrString;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileNameOrString;
        if(JS_GetLength(ctx,argv[0],&size_fileNameOrString)==-1) {
            return JS_EXCEPTION;
        }
        fileNameOrString = js_malloc(ctx, size_fileNameOrString * sizeof(char));
        for(int i0=0; i0 < size_fileNameOrString; i0++){
            JSValue js_fileNameOrString = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileNameOrString[i0] = (char)((char *)JS_ToCString(ctx, js_fileNameOrString))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileNameOrString = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileNameOrString = JS_DupValue(ctx,argv[0]);
        size_t size_fileNameOrString;
        fileNameOrString = (char *)JS_GetArrayBuffer(ctx, &size_fileNameOrString, js_fileNameOrString);
    }
    else {
        JSClassID classid_fileNameOrString = JS_GetClassID(argv[0]);
        if(classid_fileNameOrString==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileNameOrString;
            size_t size_fileNameOrString;
            js_fileNameOrString = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileNameOrString,&size_fileNameOrString,NULL);
            fileNameOrString = (char *)JS_GetArrayBuffer(ctx, &size_fileNameOrString, js_fileNameOrString);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int width;
    JS_ToInt32(ctx, &width, argv[1]);
    int height;
    JS_ToInt32(ctx, &height, argv[2]);
    Image returnVal = LoadImageSvg((const char *)fileNameOrString, width, height);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileNameOrString);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileNameOrString);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileNameOrString);
    }
    else {
        JSClassID classid_fileNameOrString = JS_GetClassID(argv[0]);
        if(classid_fileNameOrString==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileNameOrString);
        }
    }
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadImageAnimFromMemory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileType;
    JSValue js_fileType;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileType;
        if(JS_GetLength(ctx,argv[0],&size_fileType)==-1) {
            return JS_EXCEPTION;
        }
        fileType = js_malloc(ctx, size_fileType * sizeof(char));
        for(int i0=0; i0 < size_fileType; i0++){
            JSValue js_fileType = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileType[i0] = (char)((char *)JS_ToCString(ctx, js_fileType))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileType = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileType = JS_DupValue(ctx,argv[0]);
        size_t size_fileType;
        fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, js_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[0]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileType;
            size_t size_fileType;
            js_fileType = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileType,&size_fileType,NULL);
            fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, js_fileType);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    unsigned char * fileData;
    JSValue js_fileData;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_fileData;
        if(JS_GetLength(ctx,argv[1],&size_fileData)==-1) {
            return JS_EXCEPTION;
        }
        fileData = js_malloc(ctx, size_fileData * sizeof(unsigned char));
        for(int i0=0; i0 < size_fileData; i0++){
            JSValue js_fileData = JS_GetPropertyUint32(ctx,argv[1],i0);
            unsigned int _int_fileData[i0];
            JS_ToUint32(ctx, &_int_fileData[i0], js_fileData);
            fileData[i0] = (unsigned char)_int_fileData[i0];
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_fileData = JS_DupValue(ctx,argv[1]);
        size_t size_fileData;
        fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, js_fileData);
    }
    else {
        JSClassID classid_fileData = JS_GetClassID(argv[1]);
        if(classid_fileData==JS_CLASS_UINT8_ARRAY && classid_fileData==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_fileData;
            size_t size_fileData;
            js_fileData = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileData,&size_fileData,NULL);
            fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, js_fileData);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int dataSize;
    JS_ToInt32(ctx, &dataSize, argv[2]);
    int * frames;
    JSValue js_frames;
    if(JS_IsArray(ctx,argv[3]) == 1) {
        size_t size_frames;
        if(JS_GetLength(ctx,argv[3],&size_frames)==-1) {
            return JS_EXCEPTION;
        }
        frames = js_malloc(ctx, size_frames * sizeof(int));
        for(int i0=0; i0 < size_frames; i0++){
            JSValue js_frames = JS_GetPropertyUint32(ctx,argv[3],i0);
            JS_ToInt32(ctx, &frames[i0], js_frames);
        }
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_frames = JS_DupValue(ctx,argv[3]);
        size_t size_frames;
        frames = (int *)JS_GetArrayBuffer(ctx, &size_frames, js_frames);
    }
    else {
        JSClassID classid_frames = JS_GetClassID(argv[3]);
        if(classid_frames==JS_CLASS_INT16_ARRAY) {
            size_t offset_frames;
            size_t size_frames;
            js_frames = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_frames,&size_frames,NULL);
            frames = (int *)JS_GetArrayBuffer(ctx, &size_frames, js_frames);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Image returnVal = LoadImageAnimFromMemory((const char *)fileType, (const unsigned char *)fileData, dataSize, frames);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileType);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileType);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[0]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileType);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, fileData);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_fileData);
    }
    else {
        JSClassID classid_fileData = JS_GetClassID(argv[1]);
        if(classid_fileData==JS_CLASS_UINT8_ARRAY && classid_fileData==JS_CLASS_UINT8C_ARRAY) {
            js_free(ctx, &js_fileData);
        }
    }
    if(JS_IsArray(ctx,argv[3]) == 1) {
        js_free(ctx, frames);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_free(ctx, &js_frames);
    }
    else {
        JSClassID classid_frames = JS_GetClassID(argv[3]);
        if(classid_frames==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &js_frames);
        }
    }
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadImageFromMemory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileType;
    JSValue js_fileType;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileType;
        if(JS_GetLength(ctx,argv[0],&size_fileType)==-1) {
            return JS_EXCEPTION;
        }
        fileType = js_malloc(ctx, size_fileType * sizeof(char));
        for(int i0=0; i0 < size_fileType; i0++){
            JSValue js_fileType = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileType[i0] = (char)((char *)JS_ToCString(ctx, js_fileType))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileType = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileType = JS_DupValue(ctx,argv[0]);
        size_t size_fileType;
        fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, js_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[0]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileType;
            size_t size_fileType;
            js_fileType = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileType,&size_fileType,NULL);
            fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, js_fileType);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    unsigned char * fileData;
    JSValue js_fileData;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_fileData;
        if(JS_GetLength(ctx,argv[1],&size_fileData)==-1) {
            return JS_EXCEPTION;
        }
        fileData = js_malloc(ctx, size_fileData * sizeof(unsigned char));
        for(int i0=0; i0 < size_fileData; i0++){
            JSValue js_fileData = JS_GetPropertyUint32(ctx,argv[1],i0);
            unsigned int _int_fileData[i0];
            JS_ToUint32(ctx, &_int_fileData[i0], js_fileData);
            fileData[i0] = (unsigned char)_int_fileData[i0];
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_fileData = JS_DupValue(ctx,argv[1]);
        size_t size_fileData;
        fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, js_fileData);
    }
    else {
        JSClassID classid_fileData = JS_GetClassID(argv[1]);
        if(classid_fileData==JS_CLASS_UINT8_ARRAY && classid_fileData==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_fileData;
            size_t size_fileData;
            js_fileData = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileData,&size_fileData,NULL);
            fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, js_fileData);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int dataSize;
    JS_ToInt32(ctx, &dataSize, argv[2]);
    Image returnVal = LoadImageFromMemory((const char *)fileType, (const unsigned char *)fileData, dataSize);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileType);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileType);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[0]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileType);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, fileData);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_fileData);
    }
    else {
        JSClassID classid_fileData = JS_GetClassID(argv[1]);
        if(classid_fileData==JS_CLASS_UINT8_ARRAY && classid_fileData==JS_CLASS_UINT8C_ARRAY) {
            js_free(ctx, &js_fileData);
        }
    }
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadImageFromTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    Image returnVal = LoadImageFromTexture(texture);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadImageFromScreen(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image returnVal = LoadImageFromScreen();
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_isImageReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    bool returnVal = IsImageReady(image);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_unloadImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    UnloadImage(image);
    return JS_UNDEFINED;
}

static JSValue js_exportImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[1],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[1],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[1]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ExportImage(image, (const char *)fileName);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_exportImageToMemory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    char * fileType;
    JSValue js_fileType;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_fileType;
        if(JS_GetLength(ctx,argv[1],&size_fileType)==-1) {
            return JS_EXCEPTION;
        }
        fileType = js_malloc(ctx, size_fileType * sizeof(char));
        for(int i0=0; i0 < size_fileType; i0++){
            JSValue js_fileType = JS_GetPropertyUint32(ctx,argv[1],i0);
            fileType[i0] = (char)((char *)JS_ToCString(ctx, js_fileType))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        fileType = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_fileType = JS_DupValue(ctx,argv[1]);
        size_t size_fileType;
        fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, js_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[1]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileType;
            size_t size_fileType;
            js_fileType = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileType,&size_fileType,NULL);
            fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, js_fileType);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int * fileSize;
    JSValue js_fileSize;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_fileSize;
        if(JS_GetLength(ctx,argv[2],&size_fileSize)==-1) {
            return JS_EXCEPTION;
        }
        fileSize = js_malloc(ctx, size_fileSize * sizeof(int));
        for(int i0=0; i0 < size_fileSize; i0++){
            JSValue js_fileSize = JS_GetPropertyUint32(ctx,argv[2],i0);
            JS_ToInt32(ctx, &fileSize[i0], js_fileSize);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_fileSize = JS_DupValue(ctx,argv[2]);
        size_t size_fileSize;
        fileSize = (int *)JS_GetArrayBuffer(ctx, &size_fileSize, js_fileSize);
    }
    else {
        JSClassID classid_fileSize = JS_GetClassID(argv[2]);
        if(classid_fileSize==JS_CLASS_INT16_ARRAY) {
            size_t offset_fileSize;
            size_t size_fileSize;
            js_fileSize = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_fileSize,&size_fileSize,NULL);
            fileSize = (int *)JS_GetArrayBuffer(ctx, &size_fileSize, js_fileSize);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    unsigned char * returnVal = ExportImageToMemory(image, (const char *)fileType, fileSize);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, fileType);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileType);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[1]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileType);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, fileSize);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_fileSize);
    }
    else {
        JSClassID classid_fileSize = JS_GetClassID(argv[2]);
        if(classid_fileSize==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &js_fileSize);
        }
    }
    size_t ret_size = sizeof(returnVal);
    JSValue ret = JS_NewArray(ctx);
    for(int i=0; i < ret_size; i++){
        JSValue reti = JS_NewUint32(ctx, returnVal[i]);
        JS_DefinePropertyValue(ctx,ret,'i',reti,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_genImageColor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    Image returnVal = GenImageColor(width, height, color);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genImageGradientLinear(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    int direction;
    JS_ToInt32(ctx, &direction, argv[2]);
    Color* start_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(start_ptr == NULL) return JS_EXCEPTION;
    Color start = *start_ptr;
    Color* end_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(end_ptr == NULL) return JS_EXCEPTION;
    Color end = *end_ptr;
    Image returnVal = GenImageGradientLinear(width, height, direction, start, end);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genImageGradientRadial(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    double double_density;
    JS_ToFloat64(ctx, &double_density, argv[2]);
    float density = (float)double_density;
    Color* inner_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(inner_ptr == NULL) return JS_EXCEPTION;
    Color inner = *inner_ptr;
    Color* outer_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(outer_ptr == NULL) return JS_EXCEPTION;
    Color outer = *outer_ptr;
    Image returnVal = GenImageGradientRadial(width, height, density, inner, outer);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genImageGradientSquare(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    double double_density;
    JS_ToFloat64(ctx, &double_density, argv[2]);
    float density = (float)double_density;
    Color* inner_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(inner_ptr == NULL) return JS_EXCEPTION;
    Color inner = *inner_ptr;
    Color* outer_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(outer_ptr == NULL) return JS_EXCEPTION;
    Color outer = *outer_ptr;
    Image returnVal = GenImageGradientSquare(width, height, density, inner, outer);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genImageChecked(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    int checksX;
    JS_ToInt32(ctx, &checksX, argv[2]);
    int checksY;
    JS_ToInt32(ctx, &checksY, argv[3]);
    Color* col1_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(col1_ptr == NULL) return JS_EXCEPTION;
    Color col1 = *col1_ptr;
    Color* col2_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(col2_ptr == NULL) return JS_EXCEPTION;
    Color col2 = *col2_ptr;
    Image returnVal = GenImageChecked(width, height, checksX, checksY, col1, col2);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genImageWhiteNoise(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    double double_factor;
    JS_ToFloat64(ctx, &double_factor, argv[2]);
    float factor = (float)double_factor;
    Image returnVal = GenImageWhiteNoise(width, height, factor);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genImagePerlinNoise(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    int offsetX;
    JS_ToInt32(ctx, &offsetX, argv[2]);
    int offsetY;
    JS_ToInt32(ctx, &offsetY, argv[3]);
    double double_scale;
    JS_ToFloat64(ctx, &double_scale, argv[4]);
    float scale = (float)double_scale;
    Image returnVal = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genImageCellular(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    int tileSize;
    JS_ToInt32(ctx, &tileSize, argv[2]);
    Image returnVal = GenImageCellular(width, height, tileSize);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genImageText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[2],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[2],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[2]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_text = JS_DupValue(ctx,argv[2]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[2]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Image returnVal = GenImageText(width, height, (const char *)text);
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[2]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_imageCopy(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    Image returnVal = ImageCopy(image);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_imageFromImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    Image returnVal = ImageFromImage(image, rec);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_imageFromChannel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    int selectedChannel;
    JS_ToInt32(ctx, &selectedChannel, argv[1]);
    Image returnVal = ImageFromChannel(image, selectedChannel);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_imageText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int fontSize;
    JS_ToInt32(ctx, &fontSize, argv[1]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    Image returnVal = ImageText((const char *)text, fontSize, color);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_imageTextEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* font_ptr = (Font*)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
    if(font_ptr == NULL) return JS_EXCEPTION;
    Font font = *font_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    double double_fontSize;
    JS_ToFloat64(ctx, &double_fontSize, argv[2]);
    float fontSize = (float)double_fontSize;
    double double_spacing;
    JS_ToFloat64(ctx, &double_spacing, argv[3]);
    float spacing = (float)double_spacing;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    Image returnVal = ImageTextEx(font, (const char *)text, fontSize, spacing, tint);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_imageFormat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    int newFormat;
    JS_ToInt32(ctx, &newFormat, argv[1]);
    ImageFormat(image, newFormat);
    return JS_UNDEFINED;
}

static JSValue js_imageToPOT(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    Color* fill_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(fill_ptr == NULL) return JS_EXCEPTION;
    Color fill = *fill_ptr;
    ImageToPOT(image, fill);
    return JS_UNDEFINED;
}

static JSValue js_imageCrop(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    Rectangle* crop_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
    if(crop_ptr == NULL) return JS_EXCEPTION;
    Rectangle crop = *crop_ptr;
    ImageCrop(image, crop);
    return JS_UNDEFINED;
}

static JSValue js_imageAlphaCrop(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    double double_threshold;
    JS_ToFloat64(ctx, &double_threshold, argv[1]);
    float threshold = (float)double_threshold;
    ImageAlphaCrop(image, threshold);
    return JS_UNDEFINED;
}

static JSValue js_imageAlphaClear(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    double double_threshold;
    JS_ToFloat64(ctx, &double_threshold, argv[2]);
    float threshold = (float)double_threshold;
    ImageAlphaClear(image, color, threshold);
    return JS_UNDEFINED;
}

static JSValue js_imageAlphaMask(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    Image* alphaMask_ptr = (Image*)JS_GetOpaque2(ctx, argv[1], js_Image_class_id);
    if(alphaMask_ptr == NULL) return JS_EXCEPTION;
    Image alphaMask = *alphaMask_ptr;
    ImageAlphaMask(image, alphaMask);
    return JS_UNDEFINED;
}

static JSValue js_imageAlphaPremultiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    ImageAlphaPremultiply(image);
    return JS_UNDEFINED;
}

static JSValue js_imageBlurGaussian(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    int blurSize;
    JS_ToInt32(ctx, &blurSize, argv[1]);
    ImageBlurGaussian(image, blurSize);
    return JS_UNDEFINED;
}

static JSValue js_imageKernelConvolution(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    float * kernel;
    JSValue js_kernel;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_kernel;
        if(JS_GetLength(ctx,argv[1],&size_kernel)==-1) {
            return JS_EXCEPTION;
        }
        kernel = js_malloc(ctx, size_kernel * sizeof(float));
        for(int i0=0; i0 < size_kernel; i0++){
            JSValue js_kernel = JS_GetPropertyUint32(ctx,argv[1],i0);
            double double_kernel[i0];
            JS_ToFloat64(ctx, &double_kernel[i0], js_kernel);
            kernel[i0] = (float)double_kernel[i0];
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_kernel = JS_DupValue(ctx,argv[1]);
        size_t size_kernel;
        kernel = (float *)JS_GetArrayBuffer(ctx, &size_kernel, js_kernel);
    }
    else {
        JSClassID classid_kernel = JS_GetClassID(argv[1]);
        if(classid_kernel==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_kernel;
            size_t size_kernel;
            js_kernel = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_kernel,&size_kernel,NULL);
            kernel = (float *)JS_GetArrayBuffer(ctx, &size_kernel, js_kernel);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int kernelSize;
    JS_ToInt32(ctx, &kernelSize, argv[2]);
    ImageKernelConvolution(image, (const float *)kernel, kernelSize);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, kernel);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_kernel);
    }
    else {
        JSClassID classid_kernel = JS_GetClassID(argv[1]);
        if(classid_kernel==JS_CLASS_FLOAT32_ARRAY) {
            js_free(ctx, &js_kernel);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_imageResize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    int newWidth;
    JS_ToInt32(ctx, &newWidth, argv[1]);
    int newHeight;
    JS_ToInt32(ctx, &newHeight, argv[2]);
    ImageResize(image, newWidth, newHeight);
    return JS_UNDEFINED;
}

static JSValue js_imageResizeNN(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    int newWidth;
    JS_ToInt32(ctx, &newWidth, argv[1]);
    int newHeight;
    JS_ToInt32(ctx, &newHeight, argv[2]);
    ImageResizeNN(image, newWidth, newHeight);
    return JS_UNDEFINED;
}

static JSValue js_imageResizeCanvas(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    int newWidth;
    JS_ToInt32(ctx, &newWidth, argv[1]);
    int newHeight;
    JS_ToInt32(ctx, &newHeight, argv[2]);
    int offsetX;
    JS_ToInt32(ctx, &offsetX, argv[3]);
    int offsetY;
    JS_ToInt32(ctx, &offsetY, argv[4]);
    Color* fill_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(fill_ptr == NULL) return JS_EXCEPTION;
    Color fill = *fill_ptr;
    ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, fill);
    return JS_UNDEFINED;
}

static JSValue js_imageMipmaps(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    ImageMipmaps(image);
    return JS_UNDEFINED;
}

static JSValue js_imageDither(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    int rBpp;
    JS_ToInt32(ctx, &rBpp, argv[1]);
    int gBpp;
    JS_ToInt32(ctx, &gBpp, argv[2]);
    int bBpp;
    JS_ToInt32(ctx, &bBpp, argv[3]);
    int aBpp;
    JS_ToInt32(ctx, &aBpp, argv[4]);
    ImageDither(image, rBpp, gBpp, bBpp, aBpp);
    return JS_UNDEFINED;
}

static JSValue js_imageFlipVertical(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    ImageFlipVertical(image);
    return JS_UNDEFINED;
}

static JSValue js_imageFlipHorizontal(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    ImageFlipHorizontal(image);
    return JS_UNDEFINED;
}

static JSValue js_imageRotate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    int degrees;
    JS_ToInt32(ctx, &degrees, argv[1]);
    ImageRotate(image, degrees);
    return JS_UNDEFINED;
}

static JSValue js_imageRotateCW(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    ImageRotateCW(image);
    return JS_UNDEFINED;
}

static JSValue js_imageRotateCCW(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    ImageRotateCCW(image);
    return JS_UNDEFINED;
}

static JSValue js_imageColorTint(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageColorTint(image, color);
    return JS_UNDEFINED;
}

static JSValue js_imageColorInvert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    ImageColorInvert(image);
    return JS_UNDEFINED;
}

static JSValue js_imageColorGrayscale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    ImageColorGrayscale(image);
    return JS_UNDEFINED;
}

static JSValue js_imageColorContrast(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    double double_contrast;
    JS_ToFloat64(ctx, &double_contrast, argv[1]);
    float contrast = (float)double_contrast;
    ImageColorContrast(image, contrast);
    return JS_UNDEFINED;
}

static JSValue js_imageColorBrightness(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    int brightness;
    JS_ToInt32(ctx, &brightness, argv[1]);
    ImageColorBrightness(image, brightness);
    return JS_UNDEFINED;
}

static JSValue js_imageColorReplace(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    Color* replace_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(replace_ptr == NULL) return JS_EXCEPTION;
    Color replace = *replace_ptr;
    ImageColorReplace(image, color, replace);
    return JS_UNDEFINED;
}

static JSValue js_loadImageColors(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    Color * colors = LoadImageColors(image);
    JSValue retVal = JS_NewArrayBufferCopy(ctx, (const uint8_t*)colors, image.width*image.height*sizeof(Color));
    UnloadImageColors(colors);
    return retVal;
}

static JSValue js_getImageAlphaBorder(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    double double_threshold;
    JS_ToFloat64(ctx, &double_threshold, argv[1]);
    float threshold = (float)double_threshold;
    Rectangle returnVal = GetImageAlphaBorder(image, threshold);
    Rectangle* ret_ptr = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getImageColor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    int x;
    JS_ToInt32(ctx, &x, argv[1]);
    int y;
    JS_ToInt32(ctx, &y, argv[2]);
    Color returnVal = GetImageColor(image, x, y);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_imageClearBackground(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageClearBackground(dst, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawPixel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    int posX;
    JS_ToInt32(ctx, &posX, argv[1]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[2]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawPixel(dst, posX, posY, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawPixelV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawPixelV(dst, position, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawLine(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    int startPosX;
    JS_ToInt32(ctx, &startPosX, argv[1]);
    int startPosY;
    JS_ToInt32(ctx, &startPosY, argv[2]);
    int endPosX;
    JS_ToInt32(ctx, &endPosX, argv[3]);
    int endPosY;
    JS_ToInt32(ctx, &endPosY, argv[4]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawLine(dst, startPosX, startPosY, endPosX, endPosY, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawLineV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Vector2* start_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(start_ptr == NULL) return JS_EXCEPTION;
    Vector2 start = *start_ptr;
    Vector2* end_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(end_ptr == NULL) return JS_EXCEPTION;
    Vector2 end = *end_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawLineV(dst, start, end, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawLineEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Vector2* start_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(start_ptr == NULL) return JS_EXCEPTION;
    Vector2 start = *start_ptr;
    Vector2* end_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(end_ptr == NULL) return JS_EXCEPTION;
    Vector2 end = *end_ptr;
    int thick;
    JS_ToInt32(ctx, &thick, argv[3]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawLineEx(dst, start, end, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawCircle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    int centerX;
    JS_ToInt32(ctx, &centerX, argv[1]);
    int centerY;
    JS_ToInt32(ctx, &centerY, argv[2]);
    int radius;
    JS_ToInt32(ctx, &radius, argv[3]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawCircle(dst, centerX, centerY, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawCircleV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    int radius;
    JS_ToInt32(ctx, &radius, argv[2]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawCircleV(dst, center, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawCircleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    int centerX;
    JS_ToInt32(ctx, &centerX, argv[1]);
    int centerY;
    JS_ToInt32(ctx, &centerY, argv[2]);
    int radius;
    JS_ToInt32(ctx, &radius, argv[3]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawCircleLines(dst, centerX, centerY, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawCircleLinesV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Vector2* center_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector2 center = *center_ptr;
    int radius;
    JS_ToInt32(ctx, &radius, argv[2]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawCircleLinesV(dst, center, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawRectangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    int posX;
    JS_ToInt32(ctx, &posX, argv[1]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[2]);
    int width;
    JS_ToInt32(ctx, &width, argv[3]);
    int height;
    JS_ToInt32(ctx, &height, argv[4]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawRectangle(dst, posX, posY, width, height, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawRectangleV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    Vector2* size_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(size_ptr == NULL) return JS_EXCEPTION;
    Vector2 size = *size_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawRectangleV(dst, position, size, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawRectangleRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawRectangleRec(dst, rec, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawRectangleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    int thick;
    JS_ToInt32(ctx, &thick, argv[2]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawRectangleLines(dst, rec, thick, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawTriangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    Vector2* v3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(v3_ptr == NULL) return JS_EXCEPTION;
    Vector2 v3 = *v3_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawTriangle(dst, v1, v2, v3, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawTriangleEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    Vector2* v3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(v3_ptr == NULL) return JS_EXCEPTION;
    Vector2 v3 = *v3_ptr;
    Color* c1_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(c1_ptr == NULL) return JS_EXCEPTION;
    Color c1 = *c1_ptr;
    Color* c2_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(c2_ptr == NULL) return JS_EXCEPTION;
    Color c2 = *c2_ptr;
    Color* c3_ptr = (Color*)JS_GetOpaque2(ctx, argv[6], js_Color_class_id);
    if(c3_ptr == NULL) return JS_EXCEPTION;
    Color c3 = *c3_ptr;
    ImageDrawTriangleEx(dst, v1, v2, v3, c1, c2, c3);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawTriangleLines(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    Vector2* v3_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(v3_ptr == NULL) return JS_EXCEPTION;
    Vector2 v3 = *v3_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawTriangleLines(dst, v1, v2, v3, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawTriangleFan(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Vector2* points = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(points == NULL) return JS_EXCEPTION;
    int pointCount;
    JS_ToInt32(ctx, &pointCount, argv[2]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawTriangleFan(dst, points, pointCount, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawTriangleStrip(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Vector2* points = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(points == NULL) return JS_EXCEPTION;
    int pointCount;
    JS_ToInt32(ctx, &pointCount, argv[2]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawTriangleStrip(dst, points, pointCount, color);
    return JS_UNDEFINED;
}

static JSValue js_imageDraw(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Image* src_ptr = (Image*)JS_GetOpaque2(ctx, argv[1], js_Image_class_id);
    if(src_ptr == NULL) return JS_EXCEPTION;
    Image src = *src_ptr;
    Rectangle* srcRec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
    if(srcRec_ptr == NULL) return JS_EXCEPTION;
    Rectangle srcRec = *srcRec_ptr;
    Rectangle* dstRec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[3], js_Rectangle_class_id);
    if(dstRec_ptr == NULL) return JS_EXCEPTION;
    Rectangle dstRec = *dstRec_ptr;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    ImageDraw(dst, src, srcRec, dstRec, tint);
    return JS_UNDEFINED;
}

static JSValue js_imageDrawText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int posX;
    JS_ToInt32(ctx, &posX, argv[2]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[3]);
    int fontSize;
    JS_ToInt32(ctx, &fontSize, argv[4]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    ImageDrawText(dst, (const char *)text, posX, posY, fontSize, color);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_imageDrawTextEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* dst = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(dst == NULL) return JS_EXCEPTION;
    Font* font_ptr = (Font*)JS_GetOpaque2(ctx, argv[1], js_Font_class_id);
    if(font_ptr == NULL) return JS_EXCEPTION;
    Font font = *font_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[2],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[2],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[2]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_text = JS_DupValue(ctx,argv[2]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[2]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    double double_fontSize;
    JS_ToFloat64(ctx, &double_fontSize, argv[4]);
    float fontSize = (float)double_fontSize;
    double double_spacing;
    JS_ToFloat64(ctx, &double_spacing, argv[5]);
    float spacing = (float)double_spacing;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[6], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    ImageDrawTextEx(dst, font, (const char *)text, position, fontSize, spacing, tint);
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[2]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_loadTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Texture2D returnVal = LoadTexture((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    Texture2D* ret_ptr = (Texture2D*)js_malloc(ctx, sizeof(Texture2D));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadTextureFromImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    Texture2D returnVal = LoadTextureFromImage(image);
    Texture2D* ret_ptr = (Texture2D*)js_malloc(ctx, sizeof(Texture2D));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadTextureCubemap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    int layout;
    JS_ToInt32(ctx, &layout, argv[1]);
    TextureCubemap returnVal = LoadTextureCubemap(image, layout);
    TextureCubemap* ret_ptr = (TextureCubemap*)js_malloc(ctx, sizeof(TextureCubemap));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadRenderTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    RenderTexture2D returnVal = LoadRenderTexture(width, height);
    RenderTexture2D* ret_ptr = (RenderTexture2D*)js_malloc(ctx, sizeof(RenderTexture2D));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RenderTexture_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_isTextureReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    bool returnVal = IsTextureReady(texture);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_unloadTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    UnloadTexture(texture);
    return JS_UNDEFINED;
}

static JSValue js_isRenderTextureReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    RenderTexture2D* target_ptr = (RenderTexture2D*)JS_GetOpaque2(ctx, argv[0], js_RenderTexture_class_id);
    if(target_ptr == NULL) return JS_EXCEPTION;
    RenderTexture2D target = *target_ptr;
    bool returnVal = IsRenderTextureReady(target);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_unloadRenderTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    RenderTexture2D* target_ptr = (RenderTexture2D*)JS_GetOpaque2(ctx, argv[0], js_RenderTexture_class_id);
    if(target_ptr == NULL) return JS_EXCEPTION;
    RenderTexture2D target = *target_ptr;
    UnloadRenderTexture(target);
    return JS_UNDEFINED;
}

static JSValue js_updateTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    void * pixels;
    JSValue js_pixels;
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_pixels = JS_DupValue(ctx,argv[1]);
        size_t size_pixels;
        pixels = (void *)JS_GetArrayBuffer(ctx, &size_pixels, js_pixels);
    }
    else {
        return JS_EXCEPTION;
    }
    UpdateTexture(texture, (const void *)pixels);
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_pixels);
    }
    return JS_UNDEFINED;
}

static JSValue js_updateTextureRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    Rectangle* rec_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
    if(rec_ptr == NULL) return JS_EXCEPTION;
    Rectangle rec = *rec_ptr;
    void * pixels;
    JSValue js_pixels;
    if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_pixels = JS_DupValue(ctx,argv[2]);
        size_t size_pixels;
        pixels = (void *)JS_GetArrayBuffer(ctx, &size_pixels, js_pixels);
    }
    else {
        return JS_EXCEPTION;
    }
    UpdateTextureRec(texture, rec, (const void *)pixels);
    if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_pixels);
    }
    return JS_UNDEFINED;
}

static JSValue js_genTextureMipmaps(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture == NULL) return JS_EXCEPTION;
    GenTextureMipmaps(texture);
    return JS_UNDEFINED;
}

static JSValue js_setTextureFilter(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    int filter;
    JS_ToInt32(ctx, &filter, argv[1]);
    SetTextureFilter(texture, filter);
    return JS_UNDEFINED;
}

static JSValue js_setTextureWrap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    int wrap;
    JS_ToInt32(ctx, &wrap, argv[1]);
    SetTextureWrap(texture, wrap);
    return JS_UNDEFINED;
}

static JSValue js_drawTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    int posX;
    JS_ToInt32(ctx, &posX, argv[1]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[2]);
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawTexture(texture, posX, posY, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawTextureV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawTextureV(texture, position, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawTextureEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    double double_rotation;
    JS_ToFloat64(ctx, &double_rotation, argv[2]);
    float rotation = (float)double_rotation;
    double double_scale;
    JS_ToFloat64(ctx, &double_scale, argv[3]);
    float scale = (float)double_scale;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawTextureEx(texture, position, rotation, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawTextureRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    Rectangle* source_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
    if(source_ptr == NULL) return JS_EXCEPTION;
    Rectangle source = *source_ptr;
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawTextureRec(texture, source, position, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawTexturePro(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    Rectangle* source_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
    if(source_ptr == NULL) return JS_EXCEPTION;
    Rectangle source = *source_ptr;
    Rectangle* dest_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
    if(dest_ptr == NULL) return JS_EXCEPTION;
    Rectangle dest = *dest_ptr;
    Vector2* origin_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(origin_ptr == NULL) return JS_EXCEPTION;
    Vector2 origin = *origin_ptr;
    double double_rotation;
    JS_ToFloat64(ctx, &double_rotation, argv[4]);
    float rotation = (float)double_rotation;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawTexturePro(texture, source, dest, origin, rotation, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawTextureNPatch(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    NPatchInfo* nPatchInfo_ptr = (NPatchInfo*)JS_GetOpaque2(ctx, argv[1], js_NPatchInfo_class_id);
    if(nPatchInfo_ptr == NULL) return JS_EXCEPTION;
    NPatchInfo nPatchInfo = *nPatchInfo_ptr;
    Rectangle* dest_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
    if(dest_ptr == NULL) return JS_EXCEPTION;
    Rectangle dest = *dest_ptr;
    Vector2* origin_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(origin_ptr == NULL) return JS_EXCEPTION;
    Vector2 origin = *origin_ptr;
    double double_rotation;
    JS_ToFloat64(ctx, &double_rotation, argv[4]);
    float rotation = (float)double_rotation;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawTextureNPatch(texture, nPatchInfo, dest, origin, rotation, tint);
    return JS_UNDEFINED;
}

static JSValue js_colorIsEqual(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* col1_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(col1_ptr == NULL) return JS_EXCEPTION;
    Color col1 = *col1_ptr;
    Color* col2_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(col2_ptr == NULL) return JS_EXCEPTION;
    Color col2 = *col2_ptr;
    bool returnVal = ColorIsEqual(col1, col2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_fade(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    double double_alpha;
    JS_ToFloat64(ctx, &double_alpha, argv[1]);
    float alpha = (float)double_alpha;
    Color returnVal = Fade(color, alpha);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_colorToInt(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    int returnVal = ColorToInt(color);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_colorNormalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    Vector4 returnVal = ColorNormalize(color);
    Vector4* ret_ptr = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_colorFromNormalized(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* normalized_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(normalized_ptr == NULL) return JS_EXCEPTION;
    Vector4 normalized = *normalized_ptr;
    Color returnVal = ColorFromNormalized(normalized);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_colorToHSV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    Vector3 returnVal = ColorToHSV(color);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_colorFromHSV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_hue;
    JS_ToFloat64(ctx, &double_hue, argv[0]);
    float hue = (float)double_hue;
    double double_saturation;
    JS_ToFloat64(ctx, &double_saturation, argv[1]);
    float saturation = (float)double_saturation;
    double double_value;
    JS_ToFloat64(ctx, &double_value, argv[2]);
    float value = (float)double_value;
    Color returnVal = ColorFromHSV(hue, saturation, value);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_colorTint(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    Color returnVal = ColorTint(color, tint);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_colorBrightness(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    double double_factor;
    JS_ToFloat64(ctx, &double_factor, argv[1]);
    float factor = (float)double_factor;
    Color returnVal = ColorBrightness(color, factor);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_colorContrast(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    double double_contrast;
    JS_ToFloat64(ctx, &double_contrast, argv[1]);
    float contrast = (float)double_contrast;
    Color returnVal = ColorContrast(color, contrast);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_colorAlpha(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    double double_alpha;
    JS_ToFloat64(ctx, &double_alpha, argv[1]);
    float alpha = (float)double_alpha;
    Color returnVal = ColorAlpha(color, alpha);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_colorAlphaBlend(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* dst_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(dst_ptr == NULL) return JS_EXCEPTION;
    Color dst = *dst_ptr;
    Color* src_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(src_ptr == NULL) return JS_EXCEPTION;
    Color src = *src_ptr;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    Color returnVal = ColorAlphaBlend(dst, src, tint);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_colorLerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* color1_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(color1_ptr == NULL) return JS_EXCEPTION;
    Color color1 = *color1_ptr;
    Color* color2_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(color2_ptr == NULL) return JS_EXCEPTION;
    Color color2 = *color2_ptr;
    double double_factor;
    JS_ToFloat64(ctx, &double_factor, argv[2]);
    float factor = (float)double_factor;
    Color returnVal = ColorLerp(color1, color2, factor);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getColor(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    unsigned int hexValue;
    JS_ToUint32(ctx, &hexValue, argv[0]);
    Color returnVal = GetColor(hexValue);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getPixelDataSize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int width;
    JS_ToInt32(ctx, &width, argv[0]);
    int height;
    JS_ToInt32(ctx, &height, argv[1]);
    int format;
    JS_ToInt32(ctx, &format, argv[2]);
    int returnVal = GetPixelDataSize(width, height, format);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getFontDefault(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font returnVal = GetFontDefault();
    Font* ret_ptr = (Font*)js_malloc(ctx, sizeof(Font));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadFont(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Font returnVal = LoadFont((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    Font* ret_ptr = (Font*)js_malloc(ctx, sizeof(Font));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadFontEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int fontSize;
    JS_ToInt32(ctx, &fontSize, argv[1]);
    int * codepoints;
    JSValue js_codepoints;
    if(JS_IsNull(argv[2]) || JS_IsUndefined(argv[2])) {
        codepoints = NULL;
    }
    else if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_codepoints;
        if(JS_GetLength(ctx,argv[2],&size_codepoints)==-1) {
            return JS_EXCEPTION;
        }
        codepoints = js_malloc(ctx, size_codepoints * sizeof(int));
        for(int i0=0; i0 < size_codepoints; i0++){
            JSValue js_codepoints = JS_GetPropertyUint32(ctx,argv[2],i0);
            JS_ToInt32(ctx, &codepoints[i0], js_codepoints);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_codepoints = JS_DupValue(ctx,argv[2]);
        size_t size_codepoints;
        codepoints = (int *)JS_GetArrayBuffer(ctx, &size_codepoints, js_codepoints);
    }
    else {
        JSClassID classid_codepoints = JS_GetClassID(argv[2]);
        if(classid_codepoints==JS_CLASS_INT16_ARRAY) {
            size_t offset_codepoints;
            size_t size_codepoints;
            js_codepoints = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_codepoints,&size_codepoints,NULL);
            codepoints = (int *)JS_GetArrayBuffer(ctx, &size_codepoints, js_codepoints);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int codepointCount;
    JS_ToInt32(ctx, &codepointCount, argv[3]);
    Font returnVal = LoadFontEx((const char *)fileName, fontSize, codepoints, codepointCount);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    if(JS_IsNull(argv[2]) || JS_IsUndefined(argv[2])) {
    }
    else if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, codepoints);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_codepoints);
    }
    else {
        JSClassID classid_codepoints = JS_GetClassID(argv[2]);
        if(classid_codepoints==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &js_codepoints);
        }
    }
    Font* ret_ptr = (Font*)js_malloc(ctx, sizeof(Font));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadFontFromImage(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image_ptr == NULL) return JS_EXCEPTION;
    Image image = *image_ptr;
    Color* key_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(key_ptr == NULL) return JS_EXCEPTION;
    Color key = *key_ptr;
    int firstChar;
    JS_ToInt32(ctx, &firstChar, argv[2]);
    Font returnVal = LoadFontFromImage(image, key, firstChar);
    Font* ret_ptr = (Font*)js_malloc(ctx, sizeof(Font));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_isFontReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* font_ptr = (Font*)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
    if(font_ptr == NULL) return JS_EXCEPTION;
    Font font = *font_ptr;
    bool returnVal = IsFontReady(font);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_unloadFont(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* font_ptr = (Font*)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
    if(font_ptr == NULL) return JS_EXCEPTION;
    Font font = *font_ptr;
    UnloadFont(font);
    return JS_UNDEFINED;
}

static JSValue js_drawFPS(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int posX;
    JS_ToInt32(ctx, &posX, argv[0]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[1]);
    DrawFPS(posX, posY);
    return JS_UNDEFINED;
}

static JSValue js_drawText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int posX;
    JS_ToInt32(ctx, &posX, argv[1]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[2]);
    int fontSize;
    JS_ToInt32(ctx, &fontSize, argv[3]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawText((const char *)text, posX, posY, fontSize, color);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_drawTextEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* font_ptr = (Font*)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
    if(font_ptr == NULL) return JS_EXCEPTION;
    Font font = *font_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    double double_fontSize;
    JS_ToFloat64(ctx, &double_fontSize, argv[3]);
    float fontSize = (float)double_fontSize;
    double double_spacing;
    JS_ToFloat64(ctx, &double_spacing, argv[4]);
    float spacing = (float)double_spacing;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawTextEx(font, (const char *)text, position, fontSize, spacing, tint);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_drawTextPro(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* font_ptr = (Font*)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
    if(font_ptr == NULL) return JS_EXCEPTION;
    Font font = *font_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    Vector2* origin_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(origin_ptr == NULL) return JS_EXCEPTION;
    Vector2 origin = *origin_ptr;
    double double_rotation;
    JS_ToFloat64(ctx, &double_rotation, argv[4]);
    float rotation = (float)double_rotation;
    double double_fontSize;
    JS_ToFloat64(ctx, &double_fontSize, argv[5]);
    float fontSize = (float)double_fontSize;
    double double_spacing;
    JS_ToFloat64(ctx, &double_spacing, argv[6]);
    float spacing = (float)double_spacing;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[7], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawTextPro(font, (const char *)text, position, origin, rotation, fontSize, spacing, tint);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_drawTextCodepoint(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* font_ptr = (Font*)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
    if(font_ptr == NULL) return JS_EXCEPTION;
    Font font = *font_ptr;
    int codepoint;
    JS_ToInt32(ctx, &codepoint, argv[1]);
    Vector2* position_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector2 position = *position_ptr;
    double double_fontSize;
    JS_ToFloat64(ctx, &double_fontSize, argv[3]);
    float fontSize = (float)double_fontSize;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawTextCodepoint(font, codepoint, position, fontSize, tint);
    return JS_UNDEFINED;
}

static JSValue js_setTextLineSpacing(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int spacing;
    JS_ToInt32(ctx, &spacing, argv[0]);
    SetTextLineSpacing(spacing);
    return JS_UNDEFINED;
}

static JSValue js_measureText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int fontSize;
    JS_ToInt32(ctx, &fontSize, argv[1]);
    int returnVal = MeasureText((const char *)text, fontSize);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_measureTextEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* font_ptr = (Font*)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
    if(font_ptr == NULL) return JS_EXCEPTION;
    Font font = *font_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    double double_fontSize;
    JS_ToFloat64(ctx, &double_fontSize, argv[2]);
    float fontSize = (float)double_fontSize;
    double double_spacing;
    JS_ToFloat64(ctx, &double_spacing, argv[3]);
    float spacing = (float)double_spacing;
    Vector2 returnVal = MeasureTextEx(font, (const char *)text, fontSize, spacing);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getGlyphIndex(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* font_ptr = (Font*)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
    if(font_ptr == NULL) return JS_EXCEPTION;
    Font font = *font_ptr;
    int codepoint;
    JS_ToInt32(ctx, &codepoint, argv[1]);
    int returnVal = GetGlyphIndex(font, codepoint);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_getGlyphAtlasRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* font_ptr = (Font*)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
    if(font_ptr == NULL) return JS_EXCEPTION;
    Font font = *font_ptr;
    int codepoint;
    JS_ToInt32(ctx, &codepoint, argv[1]);
    Rectangle returnVal = GetGlyphAtlasRec(font, codepoint);
    Rectangle* ret_ptr = (Rectangle*)js_malloc(ctx, sizeof(Rectangle));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_textCopy(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * dst;
    JSValue js_dst;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_dst;
        if(JS_GetLength(ctx,argv[0],&size_dst)==-1) {
            return JS_EXCEPTION;
        }
        dst = js_malloc(ctx, size_dst * sizeof(char));
        for(int i0=0; i0 < size_dst; i0++){
            JSValue js_dst = JS_GetPropertyUint32(ctx,argv[0],i0);
            dst[i0] = (char)((char *)JS_ToCString(ctx, js_dst))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        dst = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_dst = JS_DupValue(ctx,argv[0]);
        size_t size_dst;
        dst = (char *)JS_GetArrayBuffer(ctx, &size_dst, js_dst);
    }
    else {
        JSClassID classid_dst = JS_GetClassID(argv[0]);
        if(classid_dst==JS_CLASS_INT8_ARRAY) {
            size_t offset_dst;
            size_t size_dst;
            js_dst = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_dst,&size_dst,NULL);
            dst = (char *)JS_GetArrayBuffer(ctx, &size_dst, js_dst);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * src;
    JSValue js_src;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_src;
        if(JS_GetLength(ctx,argv[1],&size_src)==-1) {
            return JS_EXCEPTION;
        }
        src = js_malloc(ctx, size_src * sizeof(char));
        for(int i0=0; i0 < size_src; i0++){
            JSValue js_src = JS_GetPropertyUint32(ctx,argv[1],i0);
            src[i0] = (char)((char *)JS_ToCString(ctx, js_src))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        src = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_src = JS_DupValue(ctx,argv[1]);
        size_t size_src;
        src = (char *)JS_GetArrayBuffer(ctx, &size_src, js_src);
    }
    else {
        JSClassID classid_src = JS_GetClassID(argv[1]);
        if(classid_src==JS_CLASS_INT8_ARRAY) {
            size_t offset_src;
            size_t size_src;
            js_src = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_src,&size_src,NULL);
            src = (char *)JS_GetArrayBuffer(ctx, &size_src, js_src);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = TextCopy(dst, (const char *)src);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, dst);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, dst);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_dst);
    }
    else {
        JSClassID classid_dst = JS_GetClassID(argv[0]);
        if(classid_dst==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_dst);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, src);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, src);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_src);
    }
    else {
        JSClassID classid_src = JS_GetClassID(argv[1]);
        if(classid_src==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_src);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_textIsEqual(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text1;
    JSValue js_text1;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text1;
        if(JS_GetLength(ctx,argv[0],&size_text1)==-1) {
            return JS_EXCEPTION;
        }
        text1 = js_malloc(ctx, size_text1 * sizeof(char));
        for(int i0=0; i0 < size_text1; i0++){
            JSValue js_text1 = JS_GetPropertyUint32(ctx,argv[0],i0);
            text1[i0] = (char)((char *)JS_ToCString(ctx, js_text1))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text1 = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text1 = JS_DupValue(ctx,argv[0]);
        size_t size_text1;
        text1 = (char *)JS_GetArrayBuffer(ctx, &size_text1, js_text1);
    }
    else {
        JSClassID classid_text1 = JS_GetClassID(argv[0]);
        if(classid_text1==JS_CLASS_INT8_ARRAY) {
            size_t offset_text1;
            size_t size_text1;
            js_text1 = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text1,&size_text1,NULL);
            text1 = (char *)JS_GetArrayBuffer(ctx, &size_text1, js_text1);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * text2;
    JSValue js_text2;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text2;
        if(JS_GetLength(ctx,argv[1],&size_text2)==-1) {
            return JS_EXCEPTION;
        }
        text2 = js_malloc(ctx, size_text2 * sizeof(char));
        for(int i0=0; i0 < size_text2; i0++){
            JSValue js_text2 = JS_GetPropertyUint32(ctx,argv[1],i0);
            text2[i0] = (char)((char *)JS_ToCString(ctx, js_text2))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text2 = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text2 = JS_DupValue(ctx,argv[1]);
        size_t size_text2;
        text2 = (char *)JS_GetArrayBuffer(ctx, &size_text2, js_text2);
    }
    else {
        JSClassID classid_text2 = JS_GetClassID(argv[1]);
        if(classid_text2==JS_CLASS_INT8_ARRAY) {
            size_t offset_text2;
            size_t size_text2;
            js_text2 = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text2,&size_text2,NULL);
            text2 = (char *)JS_GetArrayBuffer(ctx, &size_text2, js_text2);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = TextIsEqual((const char *)text1, (const char *)text2);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text1);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text1);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text1);
    }
    else {
        JSClassID classid_text1 = JS_GetClassID(argv[0]);
        if(classid_text1==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text1);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text2);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text2);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text2);
    }
    else {
        JSClassID classid_text2 = JS_GetClassID(argv[1]);
        if(classid_text2==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text2);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_textLength(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    unsigned int returnVal = TextLength((const char *)text);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewUint32(ctx, returnVal);
    return ret;
}

static JSValue js_textFormat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;;
    size_t size_text = argc;
    if(size_text>4)size_text=4;
    char * * text = js_malloc(ctx, size_text * sizeof(char *));
    for(int i0=0; i0 < size_text; i0++){
        if(JS_IsArray(ctx,argv[i0]) == 1) {
            size_t size_texti0;
            if(JS_GetLength(ctx,argv[i0],&size_texti0)==-1) {
                return JS_EXCEPTION;
            }
            text[i0] = js_malloc(ctx, size_texti0 * sizeof(char));
            memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, text[i0]);
            for(int i1=0; i1 < size_texti0; i1++){
                JSValue js_texti0 = JS_GetPropertyUint32(ctx,argv[i0],i1);
                text[i0][i1] = (char)((char *)JS_ToCString(ctx, js_texti0))[0];
            }
        }
        else if(JS_IsString(argv[i0]) == 1) {
            text[i0] = (char *)JS_ToCString(ctx, argv[i0]);
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text[i0]);
        }
        else if(JS_IsArrayBuffer(argv[i0]) == 1) {
            JSValue js_texti0 = JS_DupValue(ctx,argv[i0]);
            memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, &js_texti0);
            size_t size_texti0;
            text[i0] = (char *)JS_GetArrayBuffer(ctx, &size_texti0, js_texti0);
        }
        else {
            JSClassID classid_texti0 = JS_GetClassID(argv[i0]);
            if(classid_texti0==JS_CLASS_INT8_ARRAY) {
                size_t offset_texti0;
                size_t size_texti0;
                JSValue js_texti0 = JS_GetTypedArrayBuffer(ctx,argv[i0],&offset_texti0,&size_texti0,NULL);
                memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, &js_texti0);
                text[i0] = (char *)JS_GetArrayBuffer(ctx, &size_texti0, js_texti0);
            }
            else {
                return JS_EXCEPTION;
            }
        }
    }
    const char * returnVal;
    switch(size_text) {
        case 0:{
             returnVal = TextFormat((const char *)text, (const char *)text[0]);
            break;
        }
        case 1:{
             returnVal = TextFormat((const char *)text, (const char *)text[0], (const char *)text[1]);
            break;
        }
        case 2:{
             returnVal = TextFormat((const char *)text, (const char *)text[0], (const char *)text[1], (const char *)text[2]);
            break;
        }
        case 3:{
             returnVal = TextFormat((const char *)text, (const char *)text[0], (const char *)text[1], (const char *)text[2], (const char *)text[3]);
            break;
        }
    }
    memoryClear(memoryHead);
    js_free(ctx, text);
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_textSubtext(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int position;
    JS_ToInt32(ctx, &position, argv[1]);
    int length;
    JS_ToInt32(ctx, &length, argv[2]);
    const char * returnVal = TextSubtext((const char *)text, position, length);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_textReplace(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * replace;
    JSValue js_replace;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_replace;
        if(JS_GetLength(ctx,argv[1],&size_replace)==-1) {
            return JS_EXCEPTION;
        }
        replace = js_malloc(ctx, size_replace * sizeof(char));
        for(int i0=0; i0 < size_replace; i0++){
            JSValue js_replace = JS_GetPropertyUint32(ctx,argv[1],i0);
            replace[i0] = (char)((char *)JS_ToCString(ctx, js_replace))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        replace = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_replace = JS_DupValue(ctx,argv[1]);
        size_t size_replace;
        replace = (char *)JS_GetArrayBuffer(ctx, &size_replace, js_replace);
    }
    else {
        JSClassID classid_replace = JS_GetClassID(argv[1]);
        if(classid_replace==JS_CLASS_INT8_ARRAY) {
            size_t offset_replace;
            size_t size_replace;
            js_replace = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_replace,&size_replace,NULL);
            replace = (char *)JS_GetArrayBuffer(ctx, &size_replace, js_replace);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * by;
    JSValue js_by;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_by;
        if(JS_GetLength(ctx,argv[2],&size_by)==-1) {
            return JS_EXCEPTION;
        }
        by = js_malloc(ctx, size_by * sizeof(char));
        for(int i0=0; i0 < size_by; i0++){
            JSValue js_by = JS_GetPropertyUint32(ctx,argv[2],i0);
            by[i0] = (char)((char *)JS_ToCString(ctx, js_by))[0];
        }
    }
    else if(JS_IsString(argv[2]) == 1) {
        by = (char *)JS_ToCString(ctx, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_by = JS_DupValue(ctx,argv[2]);
        size_t size_by;
        by = (char *)JS_GetArrayBuffer(ctx, &size_by, js_by);
    }
    else {
        JSClassID classid_by = JS_GetClassID(argv[2]);
        if(classid_by==JS_CLASS_INT8_ARRAY) {
            size_t offset_by;
            size_t size_by;
            js_by = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_by,&size_by,NULL);
            by = (char *)JS_GetArrayBuffer(ctx, &size_by, js_by);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * returnVal = TextReplace((const char *)text, (const char *)replace, (const char *)by);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, replace);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, replace);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_replace);
    }
    else {
        JSClassID classid_replace = JS_GetClassID(argv[1]);
        if(classid_replace==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_replace);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, by);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, by);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_by);
    }
    else {
        JSClassID classid_by = JS_GetClassID(argv[2]);
        if(classid_by==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_by);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_textInsert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * insert;
    JSValue js_insert;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_insert;
        if(JS_GetLength(ctx,argv[1],&size_insert)==-1) {
            return JS_EXCEPTION;
        }
        insert = js_malloc(ctx, size_insert * sizeof(char));
        for(int i0=0; i0 < size_insert; i0++){
            JSValue js_insert = JS_GetPropertyUint32(ctx,argv[1],i0);
            insert[i0] = (char)((char *)JS_ToCString(ctx, js_insert))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        insert = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_insert = JS_DupValue(ctx,argv[1]);
        size_t size_insert;
        insert = (char *)JS_GetArrayBuffer(ctx, &size_insert, js_insert);
    }
    else {
        JSClassID classid_insert = JS_GetClassID(argv[1]);
        if(classid_insert==JS_CLASS_INT8_ARRAY) {
            size_t offset_insert;
            size_t size_insert;
            js_insert = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_insert,&size_insert,NULL);
            insert = (char *)JS_GetArrayBuffer(ctx, &size_insert, js_insert);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int position;
    JS_ToInt32(ctx, &position, argv[2]);
    char * returnVal = TextInsert((const char *)text, (const char *)insert, position);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, insert);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, insert);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_insert);
    }
    else {
        JSClassID classid_insert = JS_GetClassID(argv[1]);
        if(classid_insert==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_insert);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_textJoin(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;;
    char * * textList;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_textList;
        if(JS_GetLength(ctx,argv[0],&size_textList)==-1) {
            return JS_EXCEPTION;
        }
        textList = js_malloc(ctx, size_textList * sizeof(char *));
        for(int i0=0; i0 < size_textList; i0++){
            JSValue js_textList = JS_GetPropertyUint32(ctx,argv[0],i0);
            if(JS_IsArray(ctx,js_textList) == 1) {
                size_t size_textListi0;
                if(JS_GetLength(ctx,js_textList,&size_textListi0)==-1) {
                    return JS_EXCEPTION;
                }
                textList[i0] = js_malloc(ctx, size_textListi0 * sizeof(char));
                memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, textList[i0]);
                for(int i1=0; i1 < size_textListi0; i1++){
                    JSValue js_textListi0 = JS_GetPropertyUint32(ctx,js_textList,i1);
                    textList[i0][i1] = (char)((char *)JS_ToCString(ctx, js_textListi0))[0];
                }
            }
            else if(JS_IsString(js_textList) == 1) {
                textList[i0] = (char *)JS_ToCString(ctx, js_textList);
                memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, textList[i0]);
            }
            else if(JS_IsArrayBuffer(js_textList) == 1) {
                JSValue js_textListi0 = JS_DupValue(ctx,js_textList);
                memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, &js_textListi0);
                size_t size_textListi0;
                textList[i0] = (char *)JS_GetArrayBuffer(ctx, &size_textListi0, js_textListi0);
            }
            else {
                JSClassID classid_textListi0 = JS_GetClassID(js_textList);
                if(classid_textListi0==JS_CLASS_INT8_ARRAY) {
                    size_t offset_textListi0;
                    size_t size_textListi0;
                    JSValue js_textListi0 = JS_GetTypedArrayBuffer(ctx,js_textList,&offset_textListi0,&size_textListi0,NULL);
                    memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, &js_textListi0);
                    textList[i0] = (char *)JS_GetArrayBuffer(ctx, &size_textListi0, js_textListi0);
                }
                else {
                    return JS_EXCEPTION;
                }
            }
        }
    }
    else {
        return JS_EXCEPTION;
    }
    int count;
    JS_ToInt32(ctx, &count, argv[1]);
    char * delimiter;
    JSValue js_delimiter;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_delimiter;
        if(JS_GetLength(ctx,argv[2],&size_delimiter)==-1) {
            return JS_EXCEPTION;
        }
        delimiter = js_malloc(ctx, size_delimiter * sizeof(char));
        for(int i0=0; i0 < size_delimiter; i0++){
            JSValue js_delimiter = JS_GetPropertyUint32(ctx,argv[2],i0);
            delimiter[i0] = (char)((char *)JS_ToCString(ctx, js_delimiter))[0];
        }
    }
    else if(JS_IsString(argv[2]) == 1) {
        delimiter = (char *)JS_ToCString(ctx, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_delimiter = JS_DupValue(ctx,argv[2]);
        size_t size_delimiter;
        delimiter = (char *)JS_GetArrayBuffer(ctx, &size_delimiter, js_delimiter);
    }
    else {
        JSClassID classid_delimiter = JS_GetClassID(argv[2]);
        if(classid_delimiter==JS_CLASS_INT8_ARRAY) {
            size_t offset_delimiter;
            size_t size_delimiter;
            js_delimiter = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_delimiter,&size_delimiter,NULL);
            delimiter = (char *)JS_GetArrayBuffer(ctx, &size_delimiter, js_delimiter);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = TextJoin((const char * *)textList, count, (const char *)delimiter);
    memoryClear(memoryHead);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, textList);
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, delimiter);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, delimiter);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_delimiter);
    }
    else {
        JSClassID classid_delimiter = JS_GetClassID(argv[2]);
        if(classid_delimiter==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_delimiter);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_textSplit(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char delimiter = (char)((char *)JS_ToCString(ctx, argv[1]))[0];
    int * count;
    JSValue js_count;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_count;
        if(JS_GetLength(ctx,argv[2],&size_count)==-1) {
            return JS_EXCEPTION;
        }
        count = js_malloc(ctx, size_count * sizeof(int));
        for(int i0=0; i0 < size_count; i0++){
            JSValue js_count = JS_GetPropertyUint32(ctx,argv[2],i0);
            JS_ToInt32(ctx, &count[i0], js_count);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_count = JS_DupValue(ctx,argv[2]);
        size_t size_count;
        count = (int *)JS_GetArrayBuffer(ctx, &size_count, js_count);
    }
    else {
        JSClassID classid_count = JS_GetClassID(argv[2]);
        if(classid_count==JS_CLASS_INT16_ARRAY) {
            size_t offset_count;
            size_t size_count;
            js_count = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_count,&size_count,NULL);
            count = (int *)JS_GetArrayBuffer(ctx, &size_count, js_count);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char ** returnVal = TextSplit((const char *)text, delimiter, count);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, count);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_count);
    }
    else {
        JSClassID classid_count = JS_GetClassID(argv[2]);
        if(classid_count==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &js_count);
        }
    }
    size_t ret_size = sizeof(returnVal);
    JSValue ret = JS_NewArray(ctx);
    for(int i=0; i < ret_size; i++){
        JSValue reti = JS_NewString(ctx, returnVal[i]);
        JS_DefinePropertyValue(ctx,ret,'i',reti,JS_PROP_C_W_E);
    }
    return ret;
}

static JSValue js_textAppend(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * append;
    JSValue js_append;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_append;
        if(JS_GetLength(ctx,argv[1],&size_append)==-1) {
            return JS_EXCEPTION;
        }
        append = js_malloc(ctx, size_append * sizeof(char));
        for(int i0=0; i0 < size_append; i0++){
            JSValue js_append = JS_GetPropertyUint32(ctx,argv[1],i0);
            append[i0] = (char)((char *)JS_ToCString(ctx, js_append))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        append = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_append = JS_DupValue(ctx,argv[1]);
        size_t size_append;
        append = (char *)JS_GetArrayBuffer(ctx, &size_append, js_append);
    }
    else {
        JSClassID classid_append = JS_GetClassID(argv[1]);
        if(classid_append==JS_CLASS_INT8_ARRAY) {
            size_t offset_append;
            size_t size_append;
            js_append = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_append,&size_append,NULL);
            append = (char *)JS_GetArrayBuffer(ctx, &size_append, js_append);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int * position;
    JSValue js_position;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_position;
        if(JS_GetLength(ctx,argv[2],&size_position)==-1) {
            return JS_EXCEPTION;
        }
        position = js_malloc(ctx, size_position * sizeof(int));
        for(int i0=0; i0 < size_position; i0++){
            JSValue js_position = JS_GetPropertyUint32(ctx,argv[2],i0);
            JS_ToInt32(ctx, &position[i0], js_position);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_position = JS_DupValue(ctx,argv[2]);
        size_t size_position;
        position = (int *)JS_GetArrayBuffer(ctx, &size_position, js_position);
    }
    else {
        JSClassID classid_position = JS_GetClassID(argv[2]);
        if(classid_position==JS_CLASS_INT16_ARRAY) {
            size_t offset_position;
            size_t size_position;
            js_position = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_position,&size_position,NULL);
            position = (int *)JS_GetArrayBuffer(ctx, &size_position, js_position);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    TextAppend(text, (const char *)append, position);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, append);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, append);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_append);
    }
    else {
        JSClassID classid_append = JS_GetClassID(argv[1]);
        if(classid_append==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_append);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, position);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_position);
    }
    else {
        JSClassID classid_position = JS_GetClassID(argv[2]);
        if(classid_position==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &js_position);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_textFindIndex(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * find;
    JSValue js_find;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_find;
        if(JS_GetLength(ctx,argv[1],&size_find)==-1) {
            return JS_EXCEPTION;
        }
        find = js_malloc(ctx, size_find * sizeof(char));
        for(int i0=0; i0 < size_find; i0++){
            JSValue js_find = JS_GetPropertyUint32(ctx,argv[1],i0);
            find[i0] = (char)((char *)JS_ToCString(ctx, js_find))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        find = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_find = JS_DupValue(ctx,argv[1]);
        size_t size_find;
        find = (char *)JS_GetArrayBuffer(ctx, &size_find, js_find);
    }
    else {
        JSClassID classid_find = JS_GetClassID(argv[1]);
        if(classid_find==JS_CLASS_INT8_ARRAY) {
            size_t offset_find;
            size_t size_find;
            js_find = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_find,&size_find,NULL);
            find = (char *)JS_GetArrayBuffer(ctx, &size_find, js_find);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = TextFindIndex((const char *)text, (const char *)find);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, find);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, find);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_find);
    }
    else {
        JSClassID classid_find = JS_GetClassID(argv[1]);
        if(classid_find==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_find);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_textToUpper(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = TextToUpper((const char *)text);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_textToLower(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = TextToLower((const char *)text);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_textToPascal(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = TextToPascal((const char *)text);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_textToSnake(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = TextToSnake((const char *)text);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_textToCamel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = TextToCamel((const char *)text);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_textToInteger(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = TextToInteger((const char *)text);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_textToFloat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[0],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[0],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_text = JS_DupValue(ctx,argv[0]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    float returnVal = TextToFloat((const char *)text);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[0]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_drawLine3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* startPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(startPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 startPos = *startPos_ptr;
    Vector3* endPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(endPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 endPos = *endPos_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawLine3D(startPos, endPos, color);
    return JS_UNDEFINED;
}

static JSValue js_drawPoint3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawPoint3D(position, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCircle3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* center_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector3 center = *center_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[1]);
    float radius = (float)double_radius;
    Vector3* rotationAxis_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(rotationAxis_ptr == NULL) return JS_EXCEPTION;
    Vector3 rotationAxis = *rotationAxis_ptr;
    double double_rotationAngle;
    JS_ToFloat64(ctx, &double_rotationAngle, argv[3]);
    float rotationAngle = (float)double_rotationAngle;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
    return JS_UNDEFINED;
}

static JSValue js_drawTriangle3D(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    Vector3* v3_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(v3_ptr == NULL) return JS_EXCEPTION;
    Vector3 v3 = *v3_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawTriangle3D(v1, v2, v3, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCube(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    double double_width;
    JS_ToFloat64(ctx, &double_width, argv[1]);
    float width = (float)double_width;
    double double_height;
    JS_ToFloat64(ctx, &double_height, argv[2]);
    float height = (float)double_height;
    double double_length;
    JS_ToFloat64(ctx, &double_length, argv[3]);
    float length = (float)double_length;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCube(position, width, height, length, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCubeV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Vector3* size_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(size_ptr == NULL) return JS_EXCEPTION;
    Vector3 size = *size_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCubeV(position, size, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCubeWires(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    double double_width;
    JS_ToFloat64(ctx, &double_width, argv[1]);
    float width = (float)double_width;
    double double_height;
    JS_ToFloat64(ctx, &double_height, argv[2]);
    float height = (float)double_height;
    double double_length;
    JS_ToFloat64(ctx, &double_length, argv[3]);
    float length = (float)double_length;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCubeWires(position, width, height, length, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCubeWiresV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Vector3* size_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(size_ptr == NULL) return JS_EXCEPTION;
    Vector3 size = *size_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCubeWiresV(position, size, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSphere(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* centerPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(centerPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 centerPos = *centerPos_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[1]);
    float radius = (float)double_radius;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSphere(centerPos, radius, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSphereEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* centerPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(centerPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 centerPos = *centerPos_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[1]);
    float radius = (float)double_radius;
    int rings;
    JS_ToInt32(ctx, &rings, argv[2]);
    int slices;
    JS_ToInt32(ctx, &slices, argv[3]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSphereEx(centerPos, radius, rings, slices, color);
    return JS_UNDEFINED;
}

static JSValue js_drawSphereWires(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* centerPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(centerPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 centerPos = *centerPos_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[1]);
    float radius = (float)double_radius;
    int rings;
    JS_ToInt32(ctx, &rings, argv[2]);
    int slices;
    JS_ToInt32(ctx, &slices, argv[3]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawSphereWires(centerPos, radius, rings, slices, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCylinder(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    double double_radiusTop;
    JS_ToFloat64(ctx, &double_radiusTop, argv[1]);
    float radiusTop = (float)double_radiusTop;
    double double_radiusBottom;
    JS_ToFloat64(ctx, &double_radiusBottom, argv[2]);
    float radiusBottom = (float)double_radiusBottom;
    double double_height;
    JS_ToFloat64(ctx, &double_height, argv[3]);
    float height = (float)double_height;
    int slices;
    JS_ToInt32(ctx, &slices, argv[4]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCylinderEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* startPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(startPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 startPos = *startPos_ptr;
    Vector3* endPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(endPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 endPos = *endPos_ptr;
    double double_startRadius;
    JS_ToFloat64(ctx, &double_startRadius, argv[2]);
    float startRadius = (float)double_startRadius;
    double double_endRadius;
    JS_ToFloat64(ctx, &double_endRadius, argv[3]);
    float endRadius = (float)double_endRadius;
    int sides;
    JS_ToInt32(ctx, &sides, argv[4]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCylinderEx(startPos, endPos, startRadius, endRadius, sides, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCylinderWires(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    double double_radiusTop;
    JS_ToFloat64(ctx, &double_radiusTop, argv[1]);
    float radiusTop = (float)double_radiusTop;
    double double_radiusBottom;
    JS_ToFloat64(ctx, &double_radiusBottom, argv[2]);
    float radiusBottom = (float)double_radiusBottom;
    double double_height;
    JS_ToFloat64(ctx, &double_height, argv[3]);
    float height = (float)double_height;
    int slices;
    JS_ToInt32(ctx, &slices, argv[4]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCylinderWiresEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* startPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(startPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 startPos = *startPos_ptr;
    Vector3* endPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(endPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 endPos = *endPos_ptr;
    double double_startRadius;
    JS_ToFloat64(ctx, &double_startRadius, argv[2]);
    float startRadius = (float)double_startRadius;
    double double_endRadius;
    JS_ToFloat64(ctx, &double_endRadius, argv[3]);
    float endRadius = (float)double_endRadius;
    int sides;
    JS_ToInt32(ctx, &sides, argv[4]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCylinderWiresEx(startPos, endPos, startRadius, endRadius, sides, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCapsule(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* startPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(startPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 startPos = *startPos_ptr;
    Vector3* endPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(endPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 endPos = *endPos_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[2]);
    float radius = (float)double_radius;
    int slices;
    JS_ToInt32(ctx, &slices, argv[3]);
    int rings;
    JS_ToInt32(ctx, &rings, argv[4]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCapsule(startPos, endPos, radius, slices, rings, color);
    return JS_UNDEFINED;
}

static JSValue js_drawCapsuleWires(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* startPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(startPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 startPos = *startPos_ptr;
    Vector3* endPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(endPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 endPos = *endPos_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[2]);
    float radius = (float)double_radius;
    int slices;
    JS_ToInt32(ctx, &slices, argv[3]);
    int rings;
    JS_ToInt32(ctx, &rings, argv[4]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawCapsuleWires(startPos, endPos, radius, slices, rings, color);
    return JS_UNDEFINED;
}

static JSValue js_drawPlane(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* centerPos_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(centerPos_ptr == NULL) return JS_EXCEPTION;
    Vector3 centerPos = *centerPos_ptr;
    Vector2* size_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(size_ptr == NULL) return JS_EXCEPTION;
    Vector2 size = *size_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawPlane(centerPos, size, color);
    return JS_UNDEFINED;
}

static JSValue js_drawRay(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ray_ptr = (Ray*)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
    if(ray_ptr == NULL) return JS_EXCEPTION;
    Ray ray = *ray_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawRay(ray, color);
    return JS_UNDEFINED;
}

static JSValue js_drawGrid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int slices;
    JS_ToInt32(ctx, &slices, argv[0]);
    double double_spacing;
    JS_ToFloat64(ctx, &double_spacing, argv[1]);
    float spacing = (float)double_spacing;
    DrawGrid(slices, spacing);
    return JS_UNDEFINED;
}

static JSValue js_loadModel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Model returnVal = LoadModel((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    Model* ret_ptr = (Model*)js_malloc(ctx, sizeof(Model));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Model_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadModelFromMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* mesh_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(mesh_ptr == NULL) return JS_EXCEPTION;
    Mesh mesh = *mesh_ptr;
    Model returnVal = LoadModelFromMesh(mesh);
    Model* ret_ptr = (Model*)js_malloc(ctx, sizeof(Model));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Model_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_isModelReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model_ptr = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model_ptr == NULL) return JS_EXCEPTION;
    Model model = *model_ptr;
    bool returnVal = IsModelReady(model);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_unloadModel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model_ptr = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model_ptr == NULL) return JS_EXCEPTION;
    Model model = *model_ptr;
    UnloadModel(model);
    return JS_UNDEFINED;
}

static JSValue js_getModelBoundingBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model_ptr = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model_ptr == NULL) return JS_EXCEPTION;
    Model model = *model_ptr;
    BoundingBox returnVal = GetModelBoundingBox(model);
    BoundingBox* ret_ptr = (BoundingBox*)js_malloc(ctx, sizeof(BoundingBox));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_BoundingBox_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_drawModel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model_ptr = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model_ptr == NULL) return JS_EXCEPTION;
    Model model = *model_ptr;
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    double double_scale;
    JS_ToFloat64(ctx, &double_scale, argv[2]);
    float scale = (float)double_scale;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawModel(model, position, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawModelEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model_ptr = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model_ptr == NULL) return JS_EXCEPTION;
    Model model = *model_ptr;
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Vector3* rotationAxis_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(rotationAxis_ptr == NULL) return JS_EXCEPTION;
    Vector3 rotationAxis = *rotationAxis_ptr;
    double double_rotationAngle;
    JS_ToFloat64(ctx, &double_rotationAngle, argv[3]);
    float rotationAngle = (float)double_rotationAngle;
    Vector3* scale_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[4], js_Vector3_class_id);
    if(scale_ptr == NULL) return JS_EXCEPTION;
    Vector3 scale = *scale_ptr;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawModelWires(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model_ptr = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model_ptr == NULL) return JS_EXCEPTION;
    Model model = *model_ptr;
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    double double_scale;
    JS_ToFloat64(ctx, &double_scale, argv[2]);
    float scale = (float)double_scale;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawModelWires(model, position, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawModelWiresEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model_ptr = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model_ptr == NULL) return JS_EXCEPTION;
    Model model = *model_ptr;
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Vector3* rotationAxis_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(rotationAxis_ptr == NULL) return JS_EXCEPTION;
    Vector3 rotationAxis = *rotationAxis_ptr;
    double double_rotationAngle;
    JS_ToFloat64(ctx, &double_rotationAngle, argv[3]);
    float rotationAngle = (float)double_rotationAngle;
    Vector3* scale_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[4], js_Vector3_class_id);
    if(scale_ptr == NULL) return JS_EXCEPTION;
    Vector3 scale = *scale_ptr;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawModelPoints(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model_ptr = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model_ptr == NULL) return JS_EXCEPTION;
    Model model = *model_ptr;
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    double double_scale;
    JS_ToFloat64(ctx, &double_scale, argv[2]);
    float scale = (float)double_scale;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawModelPoints(model, position, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawModelPointsEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model_ptr = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model_ptr == NULL) return JS_EXCEPTION;
    Model model = *model_ptr;
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Vector3* rotationAxis_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(rotationAxis_ptr == NULL) return JS_EXCEPTION;
    Vector3 rotationAxis = *rotationAxis_ptr;
    double double_rotationAngle;
    JS_ToFloat64(ctx, &double_rotationAngle, argv[3]);
    float rotationAngle = (float)double_rotationAngle;
    Vector3* scale_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[4], js_Vector3_class_id);
    if(scale_ptr == NULL) return JS_EXCEPTION;
    Vector3 scale = *scale_ptr;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawModelPointsEx(model, position, rotationAxis, rotationAngle, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawBoundingBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    BoundingBox* box_ptr = (BoundingBox*)JS_GetOpaque2(ctx, argv[0], js_BoundingBox_class_id);
    if(box_ptr == NULL) return JS_EXCEPTION;
    BoundingBox box = *box_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    DrawBoundingBox(box, color);
    return JS_UNDEFINED;
}

static JSValue js_drawBillboard(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera_ptr = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera camera = *camera_ptr;
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[1], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    double double_scale;
    JS_ToFloat64(ctx, &double_scale, argv[3]);
    float scale = (float)double_scale;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawBillboard(camera, texture, position, scale, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawBillboardRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera_ptr = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera camera = *camera_ptr;
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[1], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    Rectangle* source_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
    if(source_ptr == NULL) return JS_EXCEPTION;
    Rectangle source = *source_ptr;
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Vector2* size_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[4], js_Vector2_class_id);
    if(size_ptr == NULL) return JS_EXCEPTION;
    Vector2 size = *size_ptr;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawBillboardRec(camera, texture, source, position, size, tint);
    return JS_UNDEFINED;
}

static JSValue js_drawBillboardPro(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera_ptr = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera_ptr == NULL) return JS_EXCEPTION;
    Camera camera = *camera_ptr;
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[1], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    Rectangle* source_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
    if(source_ptr == NULL) return JS_EXCEPTION;
    Rectangle source = *source_ptr;
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Vector3* up_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[4], js_Vector3_class_id);
    if(up_ptr == NULL) return JS_EXCEPTION;
    Vector3 up = *up_ptr;
    Vector2* size_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[5], js_Vector2_class_id);
    if(size_ptr == NULL) return JS_EXCEPTION;
    Vector2 size = *size_ptr;
    Vector2* origin_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[6], js_Vector2_class_id);
    if(origin_ptr == NULL) return JS_EXCEPTION;
    Vector2 origin = *origin_ptr;
    double double_rotation;
    JS_ToFloat64(ctx, &double_rotation, argv[7]);
    float rotation = (float)double_rotation;
    Color* tint_ptr = (Color*)JS_GetOpaque2(ctx, argv[8], js_Color_class_id);
    if(tint_ptr == NULL) return JS_EXCEPTION;
    Color tint = *tint_ptr;
    DrawBillboardPro(camera, texture, source, position, up, size, origin, rotation, tint);
    return JS_UNDEFINED;
}

static JSValue js_uploadMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* mesh = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(mesh == NULL) return JS_EXCEPTION;
    bool dynamic = JS_ToBool(ctx, argv[1]);
    UploadMesh(mesh, dynamic);
    return JS_UNDEFINED;
}

static JSValue js_updateMeshBuffer(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* mesh_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(mesh_ptr == NULL) return JS_EXCEPTION;
    Mesh mesh = *mesh_ptr;
    int index;
    JS_ToInt32(ctx, &index, argv[1]);
    void * data;
    JSValue js_data;
    if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_data = JS_DupValue(ctx,argv[2]);
        size_t size_data;
        data = (void *)JS_GetArrayBuffer(ctx, &size_data, js_data);
    }
    else {
        return JS_EXCEPTION;
    }
    int dataSize;
    JS_ToInt32(ctx, &dataSize, argv[3]);
    int offset;
    JS_ToInt32(ctx, &offset, argv[4]);
    UpdateMeshBuffer(mesh, index, (const void *)data, dataSize, offset);
    if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_data);
    }
    return JS_UNDEFINED;
}

static JSValue js_unloadMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* mesh_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(mesh_ptr == NULL) return JS_EXCEPTION;
    Mesh mesh = *mesh_ptr;
    UnloadMesh(mesh);
    return JS_UNDEFINED;
}

static JSValue js_drawMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* mesh_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(mesh_ptr == NULL) return JS_EXCEPTION;
    Mesh mesh = *mesh_ptr;
    Material* material_ptr = (Material*)JS_GetOpaque2(ctx, argv[1], js_Material_class_id);
    if(material_ptr == NULL) return JS_EXCEPTION;
    Material material = *material_ptr;
    Matrix* transform_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[2], js_Matrix_class_id);
    if(transform_ptr == NULL) return JS_EXCEPTION;
    Matrix transform = *transform_ptr;
    DrawMesh(mesh, material, transform);
    return JS_UNDEFINED;
}

static JSValue js_drawMeshInstanced(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* mesh_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(mesh_ptr == NULL) return JS_EXCEPTION;
    Mesh mesh = *mesh_ptr;
    Material* material_ptr = (Material*)JS_GetOpaque2(ctx, argv[1], js_Material_class_id);
    if(material_ptr == NULL) return JS_EXCEPTION;
    Material material = *material_ptr;
    Matrix* transforms = (Matrix*)JS_GetOpaque2(ctx, argv[2], js_Matrix_class_id);
    if(transforms == NULL) return JS_EXCEPTION;
    int instances;
    JS_ToInt32(ctx, &instances, argv[3]);
    DrawMeshInstanced(mesh, material, (const Matrix *)transforms, instances);
    return JS_UNDEFINED;
}

static JSValue js_getMeshBoundingBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* mesh_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(mesh_ptr == NULL) return JS_EXCEPTION;
    Mesh mesh = *mesh_ptr;
    BoundingBox returnVal = GetMeshBoundingBox(mesh);
    BoundingBox* ret_ptr = (BoundingBox*)js_malloc(ctx, sizeof(BoundingBox));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_BoundingBox_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genMeshTangents(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* mesh = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(mesh == NULL) return JS_EXCEPTION;
    GenMeshTangents(mesh);
    return JS_UNDEFINED;
}

static JSValue js_exportMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* mesh_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(mesh_ptr == NULL) return JS_EXCEPTION;
    Mesh mesh = *mesh_ptr;
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[1],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[1],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[1]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ExportMesh(mesh, (const char *)fileName);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_exportMeshAsCode(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* mesh_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(mesh_ptr == NULL) return JS_EXCEPTION;
    Mesh mesh = *mesh_ptr;
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[1],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[1],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[1]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ExportMeshAsCode(mesh, (const char *)fileName);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_genMeshPoly(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int sides;
    JS_ToInt32(ctx, &sides, argv[0]);
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[1]);
    float radius = (float)double_radius;
    Mesh returnVal = GenMeshPoly(sides, radius);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genMeshPlane(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_width;
    JS_ToFloat64(ctx, &double_width, argv[0]);
    float width = (float)double_width;
    double double_length;
    JS_ToFloat64(ctx, &double_length, argv[1]);
    float length = (float)double_length;
    int resX;
    JS_ToInt32(ctx, &resX, argv[2]);
    int resZ;
    JS_ToInt32(ctx, &resZ, argv[3]);
    Mesh returnVal = GenMeshPlane(width, length, resX, resZ);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genMeshCube(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_width;
    JS_ToFloat64(ctx, &double_width, argv[0]);
    float width = (float)double_width;
    double double_height;
    JS_ToFloat64(ctx, &double_height, argv[1]);
    float height = (float)double_height;
    double double_length;
    JS_ToFloat64(ctx, &double_length, argv[2]);
    float length = (float)double_length;
    Mesh returnVal = GenMeshCube(width, height, length);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genMeshSphere(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[0]);
    float radius = (float)double_radius;
    int rings;
    JS_ToInt32(ctx, &rings, argv[1]);
    int slices;
    JS_ToInt32(ctx, &slices, argv[2]);
    Mesh returnVal = GenMeshSphere(radius, rings, slices);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genMeshHemiSphere(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[0]);
    float radius = (float)double_radius;
    int rings;
    JS_ToInt32(ctx, &rings, argv[1]);
    int slices;
    JS_ToInt32(ctx, &slices, argv[2]);
    Mesh returnVal = GenMeshHemiSphere(radius, rings, slices);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genMeshCylinder(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[0]);
    float radius = (float)double_radius;
    double double_height;
    JS_ToFloat64(ctx, &double_height, argv[1]);
    float height = (float)double_height;
    int slices;
    JS_ToInt32(ctx, &slices, argv[2]);
    Mesh returnVal = GenMeshCylinder(radius, height, slices);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genMeshCone(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[0]);
    float radius = (float)double_radius;
    double double_height;
    JS_ToFloat64(ctx, &double_height, argv[1]);
    float height = (float)double_height;
    int slices;
    JS_ToInt32(ctx, &slices, argv[2]);
    Mesh returnVal = GenMeshCone(radius, height, slices);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genMeshTorus(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[0]);
    float radius = (float)double_radius;
    double double_size;
    JS_ToFloat64(ctx, &double_size, argv[1]);
    float size = (float)double_size;
    int radSeg;
    JS_ToInt32(ctx, &radSeg, argv[2]);
    int sides;
    JS_ToInt32(ctx, &sides, argv[3]);
    Mesh returnVal = GenMeshTorus(radius, size, radSeg, sides);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genMeshKnot(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[0]);
    float radius = (float)double_radius;
    double double_size;
    JS_ToFloat64(ctx, &double_size, argv[1]);
    float size = (float)double_size;
    int radSeg;
    JS_ToInt32(ctx, &radSeg, argv[2]);
    int sides;
    JS_ToInt32(ctx, &sides, argv[3]);
    Mesh returnVal = GenMeshKnot(radius, size, radSeg, sides);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genMeshHeightmap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* heightmap_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(heightmap_ptr == NULL) return JS_EXCEPTION;
    Image heightmap = *heightmap_ptr;
    Vector3* size_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(size_ptr == NULL) return JS_EXCEPTION;
    Vector3 size = *size_ptr;
    Mesh returnVal = GenMeshHeightmap(heightmap, size);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_genMeshCubicmap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* cubicmap_ptr = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(cubicmap_ptr == NULL) return JS_EXCEPTION;
    Image cubicmap = *cubicmap_ptr;
    Vector3* cubeSize_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(cubeSize_ptr == NULL) return JS_EXCEPTION;
    Vector3 cubeSize = *cubeSize_ptr;
    Mesh returnVal = GenMeshCubicmap(cubicmap, cubeSize);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadMaterialDefault(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Material returnVal = LoadMaterialDefault();
    Material* ret_ptr = (Material*)js_malloc(ctx, sizeof(Material));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Material_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_isMaterialReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Material* material_ptr = (Material*)JS_GetOpaque2(ctx, argv[0], js_Material_class_id);
    if(material_ptr == NULL) return JS_EXCEPTION;
    Material material = *material_ptr;
    bool returnVal = IsMaterialReady(material);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_unloadMaterial(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Material* material_ptr = (Material*)JS_GetOpaque2(ctx, argv[0], js_Material_class_id);
    if(material_ptr == NULL) return JS_EXCEPTION;
    Material material = *material_ptr;
    UnloadMaterial(material);
    return JS_UNDEFINED;
}

static JSValue js_setMaterialTexture(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Material* material = (Material*)JS_GetOpaque2(ctx, argv[0], js_Material_class_id);
    if(material == NULL) return JS_EXCEPTION;
    int mapType;
    JS_ToInt32(ctx, &mapType, argv[1]);
    Texture2D* texture_ptr = (Texture2D*)JS_GetOpaque2(ctx, argv[2], js_Texture_class_id);
    if(texture_ptr == NULL) return JS_EXCEPTION;
    Texture2D texture = *texture_ptr;
    SetMaterialTexture(material, mapType, texture);
    return JS_UNDEFINED;
}

static JSValue js_setModelMeshMaterial(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model == NULL) return JS_EXCEPTION;
    int meshId;
    JS_ToInt32(ctx, &meshId, argv[1]);
    int materialId;
    JS_ToInt32(ctx, &materialId, argv[2]);
    SetModelMeshMaterial(model, meshId, materialId);
    return JS_UNDEFINED;
}

static JSValue js_updateModelAnimationBoneMatrices(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model_ptr = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model_ptr == NULL) return JS_EXCEPTION;
    Model model = *model_ptr;
    ModelAnimation* anim_ptr = (ModelAnimation*)JS_GetOpaque2(ctx, argv[1], js_ModelAnimation_class_id);
    if(anim_ptr == NULL) return JS_EXCEPTION;
    ModelAnimation anim = *anim_ptr;
    int frame;
    JS_ToInt32(ctx, &frame, argv[2]);
    UpdateModelAnimationBoneMatrices(model, anim, frame);
    return JS_UNDEFINED;
}

static JSValue js_checkCollisionSpheres(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* center1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(center1_ptr == NULL) return JS_EXCEPTION;
    Vector3 center1 = *center1_ptr;
    double double_radius1;
    JS_ToFloat64(ctx, &double_radius1, argv[1]);
    float radius1 = (float)double_radius1;
    Vector3* center2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(center2_ptr == NULL) return JS_EXCEPTION;
    Vector3 center2 = *center2_ptr;
    double double_radius2;
    JS_ToFloat64(ctx, &double_radius2, argv[3]);
    float radius2 = (float)double_radius2;
    bool returnVal = CheckCollisionSpheres(center1, radius1, center2, radius2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_checkCollisionBoxes(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    BoundingBox* box1_ptr = (BoundingBox*)JS_GetOpaque2(ctx, argv[0], js_BoundingBox_class_id);
    if(box1_ptr == NULL) return JS_EXCEPTION;
    BoundingBox box1 = *box1_ptr;
    BoundingBox* box2_ptr = (BoundingBox*)JS_GetOpaque2(ctx, argv[1], js_BoundingBox_class_id);
    if(box2_ptr == NULL) return JS_EXCEPTION;
    BoundingBox box2 = *box2_ptr;
    bool returnVal = CheckCollisionBoxes(box1, box2);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_checkCollisionBoxSphere(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    BoundingBox* box_ptr = (BoundingBox*)JS_GetOpaque2(ctx, argv[0], js_BoundingBox_class_id);
    if(box_ptr == NULL) return JS_EXCEPTION;
    BoundingBox box = *box_ptr;
    Vector3* center_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector3 center = *center_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[2]);
    float radius = (float)double_radius;
    bool returnVal = CheckCollisionBoxSphere(box, center, radius);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_getRayCollisionSphere(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ray_ptr = (Ray*)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
    if(ray_ptr == NULL) return JS_EXCEPTION;
    Ray ray = *ray_ptr;
    Vector3* center_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(center_ptr == NULL) return JS_EXCEPTION;
    Vector3 center = *center_ptr;
    double double_radius;
    JS_ToFloat64(ctx, &double_radius, argv[2]);
    float radius = (float)double_radius;
    RayCollision returnVal = GetRayCollisionSphere(ray, center, radius);
    RayCollision* ret_ptr = (RayCollision*)js_malloc(ctx, sizeof(RayCollision));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getRayCollisionBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ray_ptr = (Ray*)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
    if(ray_ptr == NULL) return JS_EXCEPTION;
    Ray ray = *ray_ptr;
    BoundingBox* box_ptr = (BoundingBox*)JS_GetOpaque2(ctx, argv[1], js_BoundingBox_class_id);
    if(box_ptr == NULL) return JS_EXCEPTION;
    BoundingBox box = *box_ptr;
    RayCollision returnVal = GetRayCollisionBox(ray, box);
    RayCollision* ret_ptr = (RayCollision*)js_malloc(ctx, sizeof(RayCollision));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getRayCollisionMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ray_ptr = (Ray*)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
    if(ray_ptr == NULL) return JS_EXCEPTION;
    Ray ray = *ray_ptr;
    Mesh* mesh_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[1], js_Mesh_class_id);
    if(mesh_ptr == NULL) return JS_EXCEPTION;
    Mesh mesh = *mesh_ptr;
    Matrix* transform_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[2], js_Matrix_class_id);
    if(transform_ptr == NULL) return JS_EXCEPTION;
    Matrix transform = *transform_ptr;
    RayCollision returnVal = GetRayCollisionMesh(ray, mesh, transform);
    RayCollision* ret_ptr = (RayCollision*)js_malloc(ctx, sizeof(RayCollision));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getRayCollisionTriangle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ray_ptr = (Ray*)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
    if(ray_ptr == NULL) return JS_EXCEPTION;
    Ray ray = *ray_ptr;
    Vector3* p1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector3 p1 = *p1_ptr;
    Vector3* p2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(p2_ptr == NULL) return JS_EXCEPTION;
    Vector3 p2 = *p2_ptr;
    Vector3* p3_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
    if(p3_ptr == NULL) return JS_EXCEPTION;
    Vector3 p3 = *p3_ptr;
    RayCollision returnVal = GetRayCollisionTriangle(ray, p1, p2, p3);
    RayCollision* ret_ptr = (RayCollision*)js_malloc(ctx, sizeof(RayCollision));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getRayCollisionQuad(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Ray* ray_ptr = (Ray*)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
    if(ray_ptr == NULL) return JS_EXCEPTION;
    Ray ray = *ray_ptr;
    Vector3* p1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(p1_ptr == NULL) return JS_EXCEPTION;
    Vector3 p1 = *p1_ptr;
    Vector3* p2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(p2_ptr == NULL) return JS_EXCEPTION;
    Vector3 p2 = *p2_ptr;
    Vector3* p3_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
    if(p3_ptr == NULL) return JS_EXCEPTION;
    Vector3 p3 = *p3_ptr;
    Vector3* p4_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[4], js_Vector3_class_id);
    if(p4_ptr == NULL) return JS_EXCEPTION;
    Vector3 p4 = *p4_ptr;
    RayCollision returnVal = GetRayCollisionQuad(ray, p1, p2, p3, p4);
    RayCollision* ret_ptr = (RayCollision*)js_malloc(ctx, sizeof(RayCollision));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_initAudioDevice(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    InitAudioDevice();
    return JS_UNDEFINED;
}

static JSValue js_closeAudioDevice(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    CloseAudioDevice();
    return JS_UNDEFINED;
}

static JSValue js_isAudioDeviceReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = IsAudioDeviceReady();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_setMasterVolume(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_volume;
    JS_ToFloat64(ctx, &double_volume, argv[0]);
    float volume = (float)double_volume;
    SetMasterVolume(volume);
    return JS_UNDEFINED;
}

static JSValue js_getMasterVolume(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    float returnVal = GetMasterVolume();
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_loadWave(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Wave returnVal = LoadWave((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    Wave* ret_ptr = (Wave*)js_malloc(ctx, sizeof(Wave));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Wave_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadWaveFromMemory(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileType;
    JSValue js_fileType;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileType;
        if(JS_GetLength(ctx,argv[0],&size_fileType)==-1) {
            return JS_EXCEPTION;
        }
        fileType = js_malloc(ctx, size_fileType * sizeof(char));
        for(int i0=0; i0 < size_fileType; i0++){
            JSValue js_fileType = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileType[i0] = (char)((char *)JS_ToCString(ctx, js_fileType))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileType = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileType = JS_DupValue(ctx,argv[0]);
        size_t size_fileType;
        fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, js_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[0]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileType;
            size_t size_fileType;
            js_fileType = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileType,&size_fileType,NULL);
            fileType = (char *)JS_GetArrayBuffer(ctx, &size_fileType, js_fileType);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    unsigned char * fileData;
    JSValue js_fileData;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_fileData;
        if(JS_GetLength(ctx,argv[1],&size_fileData)==-1) {
            return JS_EXCEPTION;
        }
        fileData = js_malloc(ctx, size_fileData * sizeof(unsigned char));
        for(int i0=0; i0 < size_fileData; i0++){
            JSValue js_fileData = JS_GetPropertyUint32(ctx,argv[1],i0);
            unsigned int _int_fileData[i0];
            JS_ToUint32(ctx, &_int_fileData[i0], js_fileData);
            fileData[i0] = (unsigned char)_int_fileData[i0];
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_fileData = JS_DupValue(ctx,argv[1]);
        size_t size_fileData;
        fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, js_fileData);
    }
    else {
        JSClassID classid_fileData = JS_GetClassID(argv[1]);
        if(classid_fileData==JS_CLASS_UINT8_ARRAY && classid_fileData==JS_CLASS_UINT8C_ARRAY) {
            size_t offset_fileData;
            size_t size_fileData;
            js_fileData = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileData,&size_fileData,NULL);
            fileData = (unsigned char *)JS_GetArrayBuffer(ctx, &size_fileData, js_fileData);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int dataSize;
    JS_ToInt32(ctx, &dataSize, argv[2]);
    Wave returnVal = LoadWaveFromMemory((const char *)fileType, (const unsigned char *)fileData, dataSize);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileType);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileType);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileType);
    }
    else {
        JSClassID classid_fileType = JS_GetClassID(argv[0]);
        if(classid_fileType==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileType);
        }
    }
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, fileData);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_fileData);
    }
    else {
        JSClassID classid_fileData = JS_GetClassID(argv[1]);
        if(classid_fileData==JS_CLASS_UINT8_ARRAY && classid_fileData==JS_CLASS_UINT8C_ARRAY) {
            js_free(ctx, &js_fileData);
        }
    }
    Wave* ret_ptr = (Wave*)js_malloc(ctx, sizeof(Wave));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Wave_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_isWaveReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* wave_ptr = (Wave*)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
    if(wave_ptr == NULL) return JS_EXCEPTION;
    Wave wave = *wave_ptr;
    bool returnVal = IsWaveReady(wave);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_loadSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Sound returnVal = LoadSound((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    Sound* ret_ptr = (Sound*)js_malloc(ctx, sizeof(Sound));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Sound_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadSoundFromWave(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* wave_ptr = (Wave*)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
    if(wave_ptr == NULL) return JS_EXCEPTION;
    Wave wave = *wave_ptr;
    Sound returnVal = LoadSoundFromWave(wave);
    Sound* ret_ptr = (Sound*)js_malloc(ctx, sizeof(Sound));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Sound_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadSoundAlias(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* source_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(source_ptr == NULL) return JS_EXCEPTION;
    Sound source = *source_ptr;
    Sound returnVal = LoadSoundAlias(source);
    Sound* ret_ptr = (Sound*)js_malloc(ctx, sizeof(Sound));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Sound_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_isSoundReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* sound_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(sound_ptr == NULL) return JS_EXCEPTION;
    Sound sound = *sound_ptr;
    bool returnVal = IsSoundReady(sound);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_updateSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* sound_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(sound_ptr == NULL) return JS_EXCEPTION;
    Sound sound = *sound_ptr;
    void * data;
    JSValue js_data;
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_data = JS_DupValue(ctx,argv[1]);
        size_t size_data;
        data = (void *)JS_GetArrayBuffer(ctx, &size_data, js_data);
    }
    else {
        return JS_EXCEPTION;
    }
    int sampleCount;
    JS_ToInt32(ctx, &sampleCount, argv[2]);
    UpdateSound(sound, (const void *)data, sampleCount);
    if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_data);
    }
    return JS_UNDEFINED;
}

static JSValue js_unloadWave(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* wave_ptr = (Wave*)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
    if(wave_ptr == NULL) return JS_EXCEPTION;
    Wave wave = *wave_ptr;
    UnloadWave(wave);
    return JS_UNDEFINED;
}

static JSValue js_unloadSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* sound_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(sound_ptr == NULL) return JS_EXCEPTION;
    Sound sound = *sound_ptr;
    UnloadSound(sound);
    return JS_UNDEFINED;
}

static JSValue js_unloadSoundAlias(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* alias_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(alias_ptr == NULL) return JS_EXCEPTION;
    Sound alias = *alias_ptr;
    UnloadSoundAlias(alias);
    return JS_UNDEFINED;
}

static JSValue js_exportWave(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* wave_ptr = (Wave*)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
    if(wave_ptr == NULL) return JS_EXCEPTION;
    Wave wave = *wave_ptr;
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[1],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[1],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[1]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool returnVal = ExportWave(wave, (const char *)fileName);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[1]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_playSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* sound_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(sound_ptr == NULL) return JS_EXCEPTION;
    Sound sound = *sound_ptr;
    PlaySound(sound);
    return JS_UNDEFINED;
}

static JSValue js_stopSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* sound_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(sound_ptr == NULL) return JS_EXCEPTION;
    Sound sound = *sound_ptr;
    StopSound(sound);
    return JS_UNDEFINED;
}

static JSValue js_pauseSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* sound_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(sound_ptr == NULL) return JS_EXCEPTION;
    Sound sound = *sound_ptr;
    PauseSound(sound);
    return JS_UNDEFINED;
}

static JSValue js_resumeSound(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* sound_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(sound_ptr == NULL) return JS_EXCEPTION;
    Sound sound = *sound_ptr;
    ResumeSound(sound);
    return JS_UNDEFINED;
}

static JSValue js_isSoundPlaying(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* sound_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(sound_ptr == NULL) return JS_EXCEPTION;
    Sound sound = *sound_ptr;
    bool returnVal = IsSoundPlaying(sound);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_setSoundVolume(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* sound_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(sound_ptr == NULL) return JS_EXCEPTION;
    Sound sound = *sound_ptr;
    double double_volume;
    JS_ToFloat64(ctx, &double_volume, argv[1]);
    float volume = (float)double_volume;
    SetSoundVolume(sound, volume);
    return JS_UNDEFINED;
}

static JSValue js_setSoundPitch(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* sound_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(sound_ptr == NULL) return JS_EXCEPTION;
    Sound sound = *sound_ptr;
    double double_pitch;
    JS_ToFloat64(ctx, &double_pitch, argv[1]);
    float pitch = (float)double_pitch;
    SetSoundPitch(sound, pitch);
    return JS_UNDEFINED;
}

static JSValue js_setSoundPan(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Sound* sound_ptr = (Sound*)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
    if(sound_ptr == NULL) return JS_EXCEPTION;
    Sound sound = *sound_ptr;
    double double_pan;
    JS_ToFloat64(ctx, &double_pan, argv[1]);
    float pan = (float)double_pan;
    SetSoundPan(sound, pan);
    return JS_UNDEFINED;
}

static JSValue js_waveCopy(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* wave_ptr = (Wave*)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
    if(wave_ptr == NULL) return JS_EXCEPTION;
    Wave wave = *wave_ptr;
    Wave returnVal = WaveCopy(wave);
    Wave* ret_ptr = (Wave*)js_malloc(ctx, sizeof(Wave));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Wave_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_waveCrop(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* wave = (Wave*)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
    if(wave == NULL) return JS_EXCEPTION;
    int initFrame;
    JS_ToInt32(ctx, &initFrame, argv[1]);
    int finalFrame;
    JS_ToInt32(ctx, &finalFrame, argv[2]);
    WaveCrop(wave, initFrame, finalFrame);
    return JS_UNDEFINED;
}

static JSValue js_waveFormat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Wave* wave = (Wave*)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
    if(wave == NULL) return JS_EXCEPTION;
    int sampleRate;
    JS_ToInt32(ctx, &sampleRate, argv[1]);
    int sampleSize;
    JS_ToInt32(ctx, &sampleSize, argv[2]);
    int channels;
    JS_ToInt32(ctx, &channels, argv[3]);
    WaveFormat(wave, sampleRate, sampleSize, channels);
    return JS_UNDEFINED;
}

static JSValue js_loadMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Music returnVal = LoadMusicStream((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    Music* ret_ptr = (Music*)js_malloc(ctx, sizeof(Music));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Music_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_isMusicReady(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    bool returnVal = IsMusicReady(music);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_unloadMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    UnloadMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_playMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    PlayMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_isMusicStreamPlaying(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    bool returnVal = IsMusicStreamPlaying(music);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_updateMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    UpdateMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_stopMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    StopMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_pauseMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    PauseMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_resumeMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    ResumeMusicStream(music);
    return JS_UNDEFINED;
}

static JSValue js_seekMusicStream(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    double double_position;
    JS_ToFloat64(ctx, &double_position, argv[1]);
    float position = (float)double_position;
    SeekMusicStream(music, position);
    return JS_UNDEFINED;
}

static JSValue js_setMusicVolume(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    double double_volume;
    JS_ToFloat64(ctx, &double_volume, argv[1]);
    float volume = (float)double_volume;
    SetMusicVolume(music, volume);
    return JS_UNDEFINED;
}

static JSValue js_setMusicPitch(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    double double_pitch;
    JS_ToFloat64(ctx, &double_pitch, argv[1]);
    float pitch = (float)double_pitch;
    SetMusicPitch(music, pitch);
    return JS_UNDEFINED;
}

static JSValue js_setMusicPan(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    double double_pan;
    JS_ToFloat64(ctx, &double_pan, argv[1]);
    float pan = (float)double_pan;
    SetMusicPan(music, pan);
    return JS_UNDEFINED;
}

static JSValue js_getMusicTimeLength(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    float returnVal = GetMusicTimeLength(music);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_getMusicTimePlayed(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Music* music_ptr = (Music*)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
    if(music_ptr == NULL) return JS_EXCEPTION;
    Music music = *music_ptr;
    float returnVal = GetMusicTimePlayed(music);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_clamp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_value;
    JS_ToFloat64(ctx, &double_value, argv[0]);
    float value = (float)double_value;
    double double_min;
    JS_ToFloat64(ctx, &double_min, argv[1]);
    float min = (float)double_min;
    double double_max;
    JS_ToFloat64(ctx, &double_max, argv[2]);
    float max = (float)double_max;
    float returnVal = Clamp(value, min, max);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_lerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_start;
    JS_ToFloat64(ctx, &double_start, argv[0]);
    float start = (float)double_start;
    double double_end;
    JS_ToFloat64(ctx, &double_end, argv[1]);
    float end = (float)double_end;
    double double_amount;
    JS_ToFloat64(ctx, &double_amount, argv[2]);
    float amount = (float)double_amount;
    float returnVal = Lerp(start, end, amount);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_normalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_value;
    JS_ToFloat64(ctx, &double_value, argv[0]);
    float value = (float)double_value;
    double double_start;
    JS_ToFloat64(ctx, &double_start, argv[1]);
    float start = (float)double_start;
    double double_end;
    JS_ToFloat64(ctx, &double_end, argv[2]);
    float end = (float)double_end;
    float returnVal = Normalize(value, start, end);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_remap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_value;
    JS_ToFloat64(ctx, &double_value, argv[0]);
    float value = (float)double_value;
    double double_inputStart;
    JS_ToFloat64(ctx, &double_inputStart, argv[1]);
    float inputStart = (float)double_inputStart;
    double double_inputEnd;
    JS_ToFloat64(ctx, &double_inputEnd, argv[2]);
    float inputEnd = (float)double_inputEnd;
    double double_outputStart;
    JS_ToFloat64(ctx, &double_outputStart, argv[3]);
    float outputStart = (float)double_outputStart;
    double double_outputEnd;
    JS_ToFloat64(ctx, &double_outputEnd, argv[4]);
    float outputEnd = (float)double_outputEnd;
    float returnVal = Remap(value, inputStart, inputEnd, outputStart, outputEnd);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_wrap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_value;
    JS_ToFloat64(ctx, &double_value, argv[0]);
    float value = (float)double_value;
    double double_min;
    JS_ToFloat64(ctx, &double_min, argv[1]);
    float min = (float)double_min;
    double double_max;
    JS_ToFloat64(ctx, &double_max, argv[2]);
    float max = (float)double_max;
    float returnVal = Wrap(value, min, max);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_floatEquals(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_x;
    JS_ToFloat64(ctx, &double_x, argv[0]);
    float x = (float)double_x;
    double double_y;
    JS_ToFloat64(ctx, &double_y, argv[1]);
    float y = (float)double_y;
    int returnVal = FloatEquals(x, y);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_vector2Zero(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = Vector2Zero();
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2One(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = Vector2One();
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Add(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    Vector2 returnVal = Vector2Add(v1, v2);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2AddValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    double double_add;
    JS_ToFloat64(ctx, &double_add, argv[1]);
    float add = (float)double_add;
    Vector2 returnVal = Vector2AddValue(v, add);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Subtract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    Vector2 returnVal = Vector2Subtract(v1, v2);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2SubtractValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    double double_sub;
    JS_ToFloat64(ctx, &double_sub, argv[1]);
    float sub = (float)double_sub;
    Vector2 returnVal = Vector2SubtractValue(v, sub);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Length(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    float returnVal = Vector2Length(v);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector2LengthSqr(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    float returnVal = Vector2LengthSqr(v);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector2DotProduct(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    float returnVal = Vector2DotProduct(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector2Distance(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    float returnVal = Vector2Distance(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector2DistanceSqr(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    float returnVal = Vector2DistanceSqr(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector2Angle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    float returnVal = Vector2Angle(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector2LineAngle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* start_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(start_ptr == NULL) return JS_EXCEPTION;
    Vector2 start = *start_ptr;
    Vector2* end_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(end_ptr == NULL) return JS_EXCEPTION;
    Vector2 end = *end_ptr;
    float returnVal = Vector2LineAngle(start, end);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector2Scale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    double double_scale;
    JS_ToFloat64(ctx, &double_scale, argv[1]);
    float scale = (float)double_scale;
    Vector2 returnVal = Vector2Scale(v, scale);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Multiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    Vector2 returnVal = Vector2Multiply(v1, v2);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Negate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    Vector2 returnVal = Vector2Negate(v);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Divide(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    Vector2 returnVal = Vector2Divide(v1, v2);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Normalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    Vector2 returnVal = Vector2Normalize(v);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Transform(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    Matrix* mat_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[1], js_Matrix_class_id);
    if(mat_ptr == NULL) return JS_EXCEPTION;
    Matrix mat = *mat_ptr;
    Vector2 returnVal = Vector2Transform(v, mat);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Lerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    double double_amount;
    JS_ToFloat64(ctx, &double_amount, argv[2]);
    float amount = (float)double_amount;
    Vector2 returnVal = Vector2Lerp(v1, v2, amount);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Reflect(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    Vector2* normal_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(normal_ptr == NULL) return JS_EXCEPTION;
    Vector2 normal = *normal_ptr;
    Vector2 returnVal = Vector2Reflect(v, normal);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Min(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    Vector2 returnVal = Vector2Min(v1, v2);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Max(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v1_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector2 v1 = *v1_ptr;
    Vector2* v2_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector2 v2 = *v2_ptr;
    Vector2 returnVal = Vector2Max(v1, v2);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Rotate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    double double_angle;
    JS_ToFloat64(ctx, &double_angle, argv[1]);
    float angle = (float)double_angle;
    Vector2 returnVal = Vector2Rotate(v, angle);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2MoveTowards(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    Vector2* target_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(target_ptr == NULL) return JS_EXCEPTION;
    Vector2 target = *target_ptr;
    double double_maxDistance;
    JS_ToFloat64(ctx, &double_maxDistance, argv[2]);
    float maxDistance = (float)double_maxDistance;
    Vector2 returnVal = Vector2MoveTowards(v, target, maxDistance);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Invert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    Vector2 returnVal = Vector2Invert(v);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Clamp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    Vector2* min_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(min_ptr == NULL) return JS_EXCEPTION;
    Vector2 min = *min_ptr;
    Vector2* max_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
    if(max_ptr == NULL) return JS_EXCEPTION;
    Vector2 max = *max_ptr;
    Vector2 returnVal = Vector2Clamp(v, min, max);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2ClampValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    double double_min;
    JS_ToFloat64(ctx, &double_min, argv[1]);
    float min = (float)double_min;
    double double_max;
    JS_ToFloat64(ctx, &double_max, argv[2]);
    float max = (float)double_max;
    Vector2 returnVal = Vector2ClampValue(v, min, max);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector2Equals(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* p_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(p_ptr == NULL) return JS_EXCEPTION;
    Vector2 p = *p_ptr;
    Vector2* q_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Vector2 q = *q_ptr;
    int returnVal = Vector2Equals(p, q);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_vector2Refract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* v_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector2 v = *v_ptr;
    Vector2* n_ptr = (Vector2*)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
    if(n_ptr == NULL) return JS_EXCEPTION;
    Vector2 n = *n_ptr;
    double double_r;
    JS_ToFloat64(ctx, &double_r, argv[2]);
    float r = (float)double_r;
    Vector2 returnVal = Vector2Refract(v, n, r);
    Vector2* ret_ptr = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Zero(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3 returnVal = Vector3Zero();
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3One(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3 returnVal = Vector3One();
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Add(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    Vector3 returnVal = Vector3Add(v1, v2);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3AddValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    double double_add;
    JS_ToFloat64(ctx, &double_add, argv[1]);
    float add = (float)double_add;
    Vector3 returnVal = Vector3AddValue(v, add);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Subtract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    Vector3 returnVal = Vector3Subtract(v1, v2);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3SubtractValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    double double_sub;
    JS_ToFloat64(ctx, &double_sub, argv[1]);
    float sub = (float)double_sub;
    Vector3 returnVal = Vector3SubtractValue(v, sub);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Scale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    double double_scalar;
    JS_ToFloat64(ctx, &double_scalar, argv[1]);
    float scalar = (float)double_scalar;
    Vector3 returnVal = Vector3Scale(v, scalar);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Multiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    Vector3 returnVal = Vector3Multiply(v1, v2);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3CrossProduct(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    Vector3 returnVal = Vector3CrossProduct(v1, v2);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Perpendicular(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    Vector3 returnVal = Vector3Perpendicular(v);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Length(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    float returnVal = Vector3Length((const Vector3)v);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector3LengthSqr(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    float returnVal = Vector3LengthSqr((const Vector3)v);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector3DotProduct(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    float returnVal = Vector3DotProduct(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector3Distance(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    float returnVal = Vector3Distance(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector3DistanceSqr(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    float returnVal = Vector3DistanceSqr(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector3Angle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    float returnVal = Vector3Angle(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector3Negate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    Vector3 returnVal = Vector3Negate(v);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Divide(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    Vector3 returnVal = Vector3Divide(v1, v2);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Normalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    Vector3 returnVal = Vector3Normalize(v);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Project(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    Vector3 returnVal = Vector3Project(v1, v2);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Reject(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    Vector3 returnVal = Vector3Reject(v1, v2);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Transform(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    Matrix* mat_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[1], js_Matrix_class_id);
    if(mat_ptr == NULL) return JS_EXCEPTION;
    Matrix mat = *mat_ptr;
    Vector3 returnVal = Vector3Transform(v, mat);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3RotateByQuaternion(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    Quaternion* q_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Quaternion q = *q_ptr;
    Vector3 returnVal = Vector3RotateByQuaternion(v, q);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3RotateByAxisAngle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    Vector3* axis_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(axis_ptr == NULL) return JS_EXCEPTION;
    Vector3 axis = *axis_ptr;
    double double_angle;
    JS_ToFloat64(ctx, &double_angle, argv[2]);
    float angle = (float)double_angle;
    Vector3 returnVal = Vector3RotateByAxisAngle(v, axis, angle);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3MoveTowards(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    Vector3* target_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(target_ptr == NULL) return JS_EXCEPTION;
    Vector3 target = *target_ptr;
    double double_maxDistance;
    JS_ToFloat64(ctx, &double_maxDistance, argv[2]);
    float maxDistance = (float)double_maxDistance;
    Vector3 returnVal = Vector3MoveTowards(v, target, maxDistance);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Lerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    double double_amount;
    JS_ToFloat64(ctx, &double_amount, argv[2]);
    float amount = (float)double_amount;
    Vector3 returnVal = Vector3Lerp(v1, v2, amount);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3CubicHermite(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* tangent1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(tangent1_ptr == NULL) return JS_EXCEPTION;
    Vector3 tangent1 = *tangent1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    Vector3* tangent2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
    if(tangent2_ptr == NULL) return JS_EXCEPTION;
    Vector3 tangent2 = *tangent2_ptr;
    double double_amount;
    JS_ToFloat64(ctx, &double_amount, argv[4]);
    float amount = (float)double_amount;
    Vector3 returnVal = Vector3CubicHermite(v1, tangent1, v2, tangent2, amount);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Reflect(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    Vector3* normal_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(normal_ptr == NULL) return JS_EXCEPTION;
    Vector3 normal = *normal_ptr;
    Vector3 returnVal = Vector3Reflect(v, normal);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Min(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    Vector3 returnVal = Vector3Min(v1, v2);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Max(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v1_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector3 v1 = *v1_ptr;
    Vector3* v2_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector3 v2 = *v2_ptr;
    Vector3 returnVal = Vector3Max(v1, v2);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Barycenter(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* p_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(p_ptr == NULL) return JS_EXCEPTION;
    Vector3 p = *p_ptr;
    Vector3* a_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(a_ptr == NULL) return JS_EXCEPTION;
    Vector3 a = *a_ptr;
    Vector3* b_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(b_ptr == NULL) return JS_EXCEPTION;
    Vector3 b = *b_ptr;
    Vector3* c_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
    if(c_ptr == NULL) return JS_EXCEPTION;
    Vector3 c = *c_ptr;
    Vector3 returnVal = Vector3Barycenter(p, a, b, c);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Unproject(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* source_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(source_ptr == NULL) return JS_EXCEPTION;
    Vector3 source = *source_ptr;
    Matrix* projection_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[1], js_Matrix_class_id);
    if(projection_ptr == NULL) return JS_EXCEPTION;
    Matrix projection = *projection_ptr;
    Matrix* view_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[2], js_Matrix_class_id);
    if(view_ptr == NULL) return JS_EXCEPTION;
    Matrix view = *view_ptr;
    Vector3 returnVal = Vector3Unproject(source, projection, view);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Invert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    Vector3 returnVal = Vector3Invert(v);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Clamp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    Vector3* min_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(min_ptr == NULL) return JS_EXCEPTION;
    Vector3 min = *min_ptr;
    Vector3* max_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(max_ptr == NULL) return JS_EXCEPTION;
    Vector3 max = *max_ptr;
    Vector3 returnVal = Vector3Clamp(v, min, max);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3ClampValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    double double_min;
    JS_ToFloat64(ctx, &double_min, argv[1]);
    float min = (float)double_min;
    double double_max;
    JS_ToFloat64(ctx, &double_max, argv[2]);
    float max = (float)double_max;
    Vector3 returnVal = Vector3ClampValue(v, min, max);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector3Equals(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* p_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(p_ptr == NULL) return JS_EXCEPTION;
    Vector3 p = *p_ptr;
    Vector3* q_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Vector3 q = *q_ptr;
    int returnVal = Vector3Equals(p, q);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_vector3Refract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* v_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector3 v = *v_ptr;
    Vector3* n_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(n_ptr == NULL) return JS_EXCEPTION;
    Vector3 n = *n_ptr;
    double double_r;
    JS_ToFloat64(ctx, &double_r, argv[2]);
    float r = (float)double_r;
    Vector3 returnVal = Vector3Refract(v, n, r);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector4Distance(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* v1_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector4 v1 = *v1_ptr;
    Vector4* v2_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector4 v2 = *v2_ptr;
    float returnVal = Vector4Distance(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector4DistanceSqr(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* v1_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector4 v1 = *v1_ptr;
    Vector4* v2_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector4 v2 = *v2_ptr;
    float returnVal = Vector4DistanceSqr(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_vector4Multiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* v1_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector4 v1 = *v1_ptr;
    Vector4* v2_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector4 v2 = *v2_ptr;
    Vector4 returnVal = Vector4Multiply(v1, v2);
    Vector4* ret_ptr = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector4Negate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* v_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector4 v = *v_ptr;
    Vector4 returnVal = Vector4Negate(v);
    Vector4* ret_ptr = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector4Divide(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* v1_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector4 v1 = *v1_ptr;
    Vector4* v2_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector4 v2 = *v2_ptr;
    Vector4 returnVal = Vector4Divide(v1, v2);
    Vector4* ret_ptr = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector4Normalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* v_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector4 v = *v_ptr;
    Vector4 returnVal = Vector4Normalize(v);
    Vector4* ret_ptr = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector4Min(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* v1_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector4 v1 = *v1_ptr;
    Vector4* v2_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector4 v2 = *v2_ptr;
    Vector4 returnVal = Vector4Min(v1, v2);
    Vector4* ret_ptr = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector4Max(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* v1_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector4 v1 = *v1_ptr;
    Vector4* v2_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector4 v2 = *v2_ptr;
    Vector4 returnVal = Vector4Max(v1, v2);
    Vector4* ret_ptr = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector4Lerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* v1_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(v1_ptr == NULL) return JS_EXCEPTION;
    Vector4 v1 = *v1_ptr;
    Vector4* v2_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(v2_ptr == NULL) return JS_EXCEPTION;
    Vector4 v2 = *v2_ptr;
    double double_amount;
    JS_ToFloat64(ctx, &double_amount, argv[2]);
    float amount = (float)double_amount;
    Vector4 returnVal = Vector4Lerp(v1, v2, amount);
    Vector4* ret_ptr = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector4MoveTowards(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* v_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector4 v = *v_ptr;
    Vector4* target_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(target_ptr == NULL) return JS_EXCEPTION;
    Vector4 target = *target_ptr;
    double double_maxDistance;
    JS_ToFloat64(ctx, &double_maxDistance, argv[2]);
    float maxDistance = (float)double_maxDistance;
    Vector4 returnVal = Vector4MoveTowards(v, target, maxDistance);
    Vector4* ret_ptr = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector4Invert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* v_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(v_ptr == NULL) return JS_EXCEPTION;
    Vector4 v = *v_ptr;
    Vector4 returnVal = Vector4Invert(v);
    Vector4* ret_ptr = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_vector4Equals(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* p_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(p_ptr == NULL) return JS_EXCEPTION;
    Vector4 p = *p_ptr;
    Vector4* q_ptr = (Vector4*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Vector4 q = *q_ptr;
    int returnVal = Vector4Equals(p, q);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_matrixDeterminant(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* mat_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[0], js_Matrix_class_id);
    if(mat_ptr == NULL) return JS_EXCEPTION;
    Matrix mat = *mat_ptr;
    float returnVal = MatrixDeterminant(mat);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_matrixTrace(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* mat_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[0], js_Matrix_class_id);
    if(mat_ptr == NULL) return JS_EXCEPTION;
    Matrix mat = *mat_ptr;
    float returnVal = MatrixTrace(mat);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_matrixTranspose(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* mat_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[0], js_Matrix_class_id);
    if(mat_ptr == NULL) return JS_EXCEPTION;
    Matrix mat = *mat_ptr;
    Matrix returnVal = MatrixTranspose(mat);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixInvert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* mat_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[0], js_Matrix_class_id);
    if(mat_ptr == NULL) return JS_EXCEPTION;
    Matrix mat = *mat_ptr;
    Matrix returnVal = MatrixInvert(mat);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixIdentity(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix returnVal = MatrixIdentity();
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixAdd(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* left_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[0], js_Matrix_class_id);
    if(left_ptr == NULL) return JS_EXCEPTION;
    Matrix left = *left_ptr;
    Matrix* right_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[1], js_Matrix_class_id);
    if(right_ptr == NULL) return JS_EXCEPTION;
    Matrix right = *right_ptr;
    Matrix returnVal = MatrixAdd(left, right);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixSubtract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* left_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[0], js_Matrix_class_id);
    if(left_ptr == NULL) return JS_EXCEPTION;
    Matrix left = *left_ptr;
    Matrix* right_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[1], js_Matrix_class_id);
    if(right_ptr == NULL) return JS_EXCEPTION;
    Matrix right = *right_ptr;
    Matrix returnVal = MatrixSubtract(left, right);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixMultiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* left_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[0], js_Matrix_class_id);
    if(left_ptr == NULL) return JS_EXCEPTION;
    Matrix left = *left_ptr;
    Matrix* right_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[1], js_Matrix_class_id);
    if(right_ptr == NULL) return JS_EXCEPTION;
    Matrix right = *right_ptr;
    Matrix returnVal = MatrixMultiply(left, right);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixTranslate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_x;
    JS_ToFloat64(ctx, &double_x, argv[0]);
    float x = (float)double_x;
    double double_y;
    JS_ToFloat64(ctx, &double_y, argv[1]);
    float y = (float)double_y;
    double double_z;
    JS_ToFloat64(ctx, &double_z, argv[2]);
    float z = (float)double_z;
    Matrix returnVal = MatrixTranslate(x, y, z);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixRotate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* axis_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(axis_ptr == NULL) return JS_EXCEPTION;
    Vector3 axis = *axis_ptr;
    double double_angle;
    JS_ToFloat64(ctx, &double_angle, argv[1]);
    float angle = (float)double_angle;
    Matrix returnVal = MatrixRotate(axis, angle);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixRotateX(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_angle;
    JS_ToFloat64(ctx, &double_angle, argv[0]);
    float angle = (float)double_angle;
    Matrix returnVal = MatrixRotateX(angle);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixRotateY(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_angle;
    JS_ToFloat64(ctx, &double_angle, argv[0]);
    float angle = (float)double_angle;
    Matrix returnVal = MatrixRotateY(angle);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixRotateZ(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_angle;
    JS_ToFloat64(ctx, &double_angle, argv[0]);
    float angle = (float)double_angle;
    Matrix returnVal = MatrixRotateZ(angle);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixRotateXYZ(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* angle_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(angle_ptr == NULL) return JS_EXCEPTION;
    Vector3 angle = *angle_ptr;
    Matrix returnVal = MatrixRotateXYZ(angle);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixRotateZYX(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* angle_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(angle_ptr == NULL) return JS_EXCEPTION;
    Vector3 angle = *angle_ptr;
    Matrix returnVal = MatrixRotateZYX(angle);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixScale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_x;
    JS_ToFloat64(ctx, &double_x, argv[0]);
    float x = (float)double_x;
    double double_y;
    JS_ToFloat64(ctx, &double_y, argv[1]);
    float y = (float)double_y;
    double double_z;
    JS_ToFloat64(ctx, &double_z, argv[2]);
    float z = (float)double_z;
    Matrix returnVal = MatrixScale(x, y, z);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixFrustum(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double left;
    JS_ToFloat64(ctx, &left, argv[0]);
    double right;
    JS_ToFloat64(ctx, &right, argv[1]);
    double bottom;
    JS_ToFloat64(ctx, &bottom, argv[2]);
    double top;
    JS_ToFloat64(ctx, &top, argv[3]);
    double nearPlane;
    JS_ToFloat64(ctx, &nearPlane, argv[4]);
    double farPlane;
    JS_ToFloat64(ctx, &farPlane, argv[5]);
    Matrix returnVal = MatrixFrustum(left, right, bottom, top, nearPlane, farPlane);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixPerspective(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double fovY;
    JS_ToFloat64(ctx, &fovY, argv[0]);
    double aspect;
    JS_ToFloat64(ctx, &aspect, argv[1]);
    double nearPlane;
    JS_ToFloat64(ctx, &nearPlane, argv[2]);
    double farPlane;
    JS_ToFloat64(ctx, &farPlane, argv[3]);
    Matrix returnVal = MatrixPerspective(fovY, aspect, nearPlane, farPlane);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixOrtho(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double left;
    JS_ToFloat64(ctx, &left, argv[0]);
    double right;
    JS_ToFloat64(ctx, &right, argv[1]);
    double bottom;
    JS_ToFloat64(ctx, &bottom, argv[2]);
    double top;
    JS_ToFloat64(ctx, &top, argv[3]);
    double nearPlane;
    JS_ToFloat64(ctx, &nearPlane, argv[4]);
    double farPlane;
    JS_ToFloat64(ctx, &farPlane, argv[5]);
    Matrix returnVal = MatrixOrtho(left, right, bottom, top, nearPlane, farPlane);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_matrixLookAt(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* eye_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(eye_ptr == NULL) return JS_EXCEPTION;
    Vector3 eye = *eye_ptr;
    Vector3* target_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(target_ptr == NULL) return JS_EXCEPTION;
    Vector3 target = *target_ptr;
    Vector3* up_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(up_ptr == NULL) return JS_EXCEPTION;
    Vector3 up = *up_ptr;
    Matrix returnVal = MatrixLookAt(eye, target, up);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionAdd(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q1_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q1_ptr == NULL) return JS_EXCEPTION;
    Quaternion q1 = *q1_ptr;
    Quaternion* q2_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(q2_ptr == NULL) return JS_EXCEPTION;
    Quaternion q2 = *q2_ptr;
    Quaternion returnVal = QuaternionAdd(q1, q2);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionAddValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Quaternion q = *q_ptr;
    double double_add;
    JS_ToFloat64(ctx, &double_add, argv[1]);
    float add = (float)double_add;
    Quaternion returnVal = QuaternionAddValue(q, add);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionSubtract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q1_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q1_ptr == NULL) return JS_EXCEPTION;
    Quaternion q1 = *q1_ptr;
    Quaternion* q2_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(q2_ptr == NULL) return JS_EXCEPTION;
    Quaternion q2 = *q2_ptr;
    Quaternion returnVal = QuaternionSubtract(q1, q2);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionSubtractValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Quaternion q = *q_ptr;
    double double_sub;
    JS_ToFloat64(ctx, &double_sub, argv[1]);
    float sub = (float)double_sub;
    Quaternion returnVal = QuaternionSubtractValue(q, sub);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionIdentity(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion returnVal = QuaternionIdentity();
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionLength(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Quaternion q = *q_ptr;
    float returnVal = QuaternionLength(q);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_quaternionNormalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Quaternion q = *q_ptr;
    Quaternion returnVal = QuaternionNormalize(q);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionInvert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Quaternion q = *q_ptr;
    Quaternion returnVal = QuaternionInvert(q);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionMultiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q1_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q1_ptr == NULL) return JS_EXCEPTION;
    Quaternion q1 = *q1_ptr;
    Quaternion* q2_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(q2_ptr == NULL) return JS_EXCEPTION;
    Quaternion q2 = *q2_ptr;
    Quaternion returnVal = QuaternionMultiply(q1, q2);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionScale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Quaternion q = *q_ptr;
    double double_mul;
    JS_ToFloat64(ctx, &double_mul, argv[1]);
    float mul = (float)double_mul;
    Quaternion returnVal = QuaternionScale(q, mul);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionDivide(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q1_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q1_ptr == NULL) return JS_EXCEPTION;
    Quaternion q1 = *q1_ptr;
    Quaternion* q2_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(q2_ptr == NULL) return JS_EXCEPTION;
    Quaternion q2 = *q2_ptr;
    Quaternion returnVal = QuaternionDivide(q1, q2);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionLerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q1_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q1_ptr == NULL) return JS_EXCEPTION;
    Quaternion q1 = *q1_ptr;
    Quaternion* q2_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(q2_ptr == NULL) return JS_EXCEPTION;
    Quaternion q2 = *q2_ptr;
    double double_amount;
    JS_ToFloat64(ctx, &double_amount, argv[2]);
    float amount = (float)double_amount;
    Quaternion returnVal = QuaternionLerp(q1, q2, amount);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionNlerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q1_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q1_ptr == NULL) return JS_EXCEPTION;
    Quaternion q1 = *q1_ptr;
    Quaternion* q2_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(q2_ptr == NULL) return JS_EXCEPTION;
    Quaternion q2 = *q2_ptr;
    double double_amount;
    JS_ToFloat64(ctx, &double_amount, argv[2]);
    float amount = (float)double_amount;
    Quaternion returnVal = QuaternionNlerp(q1, q2, amount);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionSlerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q1_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q1_ptr == NULL) return JS_EXCEPTION;
    Quaternion q1 = *q1_ptr;
    Quaternion* q2_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(q2_ptr == NULL) return JS_EXCEPTION;
    Quaternion q2 = *q2_ptr;
    double double_amount;
    JS_ToFloat64(ctx, &double_amount, argv[2]);
    float amount = (float)double_amount;
    Quaternion returnVal = QuaternionSlerp(q1, q2, amount);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionCubicHermiteSpline(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q1_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q1_ptr == NULL) return JS_EXCEPTION;
    Quaternion q1 = *q1_ptr;
    Quaternion* outTangent1_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(outTangent1_ptr == NULL) return JS_EXCEPTION;
    Quaternion outTangent1 = *outTangent1_ptr;
    Quaternion* q2_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[2], js_Vector4_class_id);
    if(q2_ptr == NULL) return JS_EXCEPTION;
    Quaternion q2 = *q2_ptr;
    Quaternion* inTangent2_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[3], js_Vector4_class_id);
    if(inTangent2_ptr == NULL) return JS_EXCEPTION;
    Quaternion inTangent2 = *inTangent2_ptr;
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[4]);
    float t = (float)double_t;
    Quaternion returnVal = QuaternionCubicHermiteSpline(q1, outTangent1, q2, inTangent2, t);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionFromVector3ToVector3(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* from_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(from_ptr == NULL) return JS_EXCEPTION;
    Vector3 from = *from_ptr;
    Vector3* to_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(to_ptr == NULL) return JS_EXCEPTION;
    Vector3 to = *to_ptr;
    Quaternion returnVal = QuaternionFromVector3ToVector3(from, to);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionFromMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* mat_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[0], js_Matrix_class_id);
    if(mat_ptr == NULL) return JS_EXCEPTION;
    Matrix mat = *mat_ptr;
    Quaternion returnVal = QuaternionFromMatrix(mat);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionToMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Quaternion q = *q_ptr;
    Matrix returnVal = QuaternionToMatrix(q);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionFromAxisAngle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* axis_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
    if(axis_ptr == NULL) return JS_EXCEPTION;
    Vector3 axis = *axis_ptr;
    double double_angle;
    JS_ToFloat64(ctx, &double_angle, argv[1]);
    float angle = (float)double_angle;
    Quaternion returnVal = QuaternionFromAxisAngle(axis, angle);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionFromEuler(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_pitch;
    JS_ToFloat64(ctx, &double_pitch, argv[0]);
    float pitch = (float)double_pitch;
    double double_yaw;
    JS_ToFloat64(ctx, &double_yaw, argv[1]);
    float yaw = (float)double_yaw;
    double double_roll;
    JS_ToFloat64(ctx, &double_roll, argv[2]);
    float roll = (float)double_roll;
    Quaternion returnVal = QuaternionFromEuler(pitch, yaw, roll);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionToEuler(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Quaternion q = *q_ptr;
    Vector3 returnVal = QuaternionToEuler(q);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionTransform(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* q_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Quaternion q = *q_ptr;
    Matrix* mat_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[1], js_Matrix_class_id);
    if(mat_ptr == NULL) return JS_EXCEPTION;
    Matrix mat = *mat_ptr;
    Quaternion returnVal = QuaternionTransform(q, mat);
    Quaternion* ret_ptr = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_quaternionEquals(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* p_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
    if(p_ptr == NULL) return JS_EXCEPTION;
    Quaternion p = *p_ptr;
    Quaternion* q_ptr = (Quaternion*)JS_GetOpaque2(ctx, argv[1], js_Vector4_class_id);
    if(q_ptr == NULL) return JS_EXCEPTION;
    Quaternion q = *q_ptr;
    int returnVal = QuaternionEquals(p, q);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_matrixDecompose(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* mat_ptr = (Matrix*)JS_GetOpaque2(ctx, argv[0], js_Matrix_class_id);
    if(mat_ptr == NULL) return JS_EXCEPTION;
    Matrix mat = *mat_ptr;
    Vector3* translation = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(translation == NULL) return JS_EXCEPTION;
    Quaternion* rotation = (Quaternion*)JS_GetOpaque2(ctx, argv[2], js_Vector4_class_id);
    if(rotation == NULL) return JS_EXCEPTION;
    Vector3* scale = (Vector3*)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
    if(scale == NULL) return JS_EXCEPTION;
    MatrixDecompose(mat, translation, rotation, scale);
    return JS_UNDEFINED;
}

static JSValue js_getCameraForward(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    Vector3 returnVal = GetCameraForward(camera);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getCameraUp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    Vector3 returnVal = GetCameraUp(camera);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getCameraRight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    Vector3 returnVal = GetCameraRight(camera);
    Vector3* ret_ptr = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_cameraMoveForward(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    double double_distance;
    JS_ToFloat64(ctx, &double_distance, argv[1]);
    float distance = (float)double_distance;
    bool moveInWorldPlane = JS_ToBool(ctx, argv[2]);
    CameraMoveForward(camera, distance, moveInWorldPlane);
    return JS_UNDEFINED;
}

static JSValue js_cameraMoveUp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    double double_distance;
    JS_ToFloat64(ctx, &double_distance, argv[1]);
    float distance = (float)double_distance;
    CameraMoveUp(camera, distance);
    return JS_UNDEFINED;
}

static JSValue js_cameraMoveRight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    double double_distance;
    JS_ToFloat64(ctx, &double_distance, argv[1]);
    float distance = (float)double_distance;
    bool moveInWorldPlane = JS_ToBool(ctx, argv[2]);
    CameraMoveRight(camera, distance, moveInWorldPlane);
    return JS_UNDEFINED;
}

static JSValue js_cameraMoveToTarget(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    double double_delta;
    JS_ToFloat64(ctx, &double_delta, argv[1]);
    float delta = (float)double_delta;
    CameraMoveToTarget(camera, delta);
    return JS_UNDEFINED;
}

static JSValue js_cameraYaw(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    double double_angle;
    JS_ToFloat64(ctx, &double_angle, argv[1]);
    float angle = (float)double_angle;
    bool rotateAroundTarget = JS_ToBool(ctx, argv[2]);
    CameraYaw(camera, angle, rotateAroundTarget);
    return JS_UNDEFINED;
}

static JSValue js_cameraPitch(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    double double_angle;
    JS_ToFloat64(ctx, &double_angle, argv[1]);
    float angle = (float)double_angle;
    bool lockView = JS_ToBool(ctx, argv[2]);
    bool rotateAroundTarget = JS_ToBool(ctx, argv[3]);
    bool rotateUp = JS_ToBool(ctx, argv[4]);
    CameraPitch(camera, angle, lockView, rotateAroundTarget, rotateUp);
    return JS_UNDEFINED;
}

static JSValue js_cameraRoll(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    double double_angle;
    JS_ToFloat64(ctx, &double_angle, argv[1]);
    float angle = (float)double_angle;
    CameraRoll(camera, angle);
    return JS_UNDEFINED;
}

static JSValue js_getCameraViewMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    Matrix returnVal = GetCameraViewMatrix(camera);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getCameraProjectionMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Camera* camera = (Camera*)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    if(camera == NULL) return JS_EXCEPTION;
    double double_aspect;
    JS_ToFloat64(ctx, &double_aspect, argv[1]);
    float aspect = (float)double_aspect;
    Matrix returnVal = GetCameraProjectionMatrix(camera, aspect);
    Matrix* ret_ptr = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_guiEnable(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiEnable();
    return JS_UNDEFINED;
}

static JSValue js_guiDisable(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiDisable();
    return JS_UNDEFINED;
}

static JSValue js_guiLock(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiLock();
    return JS_UNDEFINED;
}

static JSValue js_guiUnlock(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiUnlock();
    return JS_UNDEFINED;
}

static JSValue js_guiIsLocked(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = GuiIsLocked();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_guiSetAlpha(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_alpha;
    JS_ToFloat64(ctx, &double_alpha, argv[0]);
    float alpha = (float)double_alpha;
    GuiSetAlpha(alpha);
    return JS_UNDEFINED;
}

static JSValue js_guiSetState(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int state;
    JS_ToInt32(ctx, &state, argv[0]);
    GuiSetState(state);
    return JS_UNDEFINED;
}

static JSValue js_guiGetState(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GuiGetState();
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiSetFont(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* font_ptr = (Font*)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
    if(font_ptr == NULL) return JS_EXCEPTION;
    Font font = *font_ptr;
    GuiSetFont(font);
    return JS_UNDEFINED;
}

static JSValue js_guiGetFont(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font returnVal = GuiGetFont();
    Font* ret_ptr = (Font*)js_malloc(ctx, sizeof(Font));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_guiSetStyle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int control;
    JS_ToInt32(ctx, &control, argv[0]);
    int property;
    JS_ToInt32(ctx, &property, argv[1]);
    int value;
    JS_ToInt32(ctx, &value, argv[2]);
    GuiSetStyle(control, property, value);
    return JS_UNDEFINED;
}

static JSValue js_guiGetStyle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int control;
    JS_ToInt32(ctx, &control, argv[0]);
    int property;
    JS_ToInt32(ctx, &property, argv[1]);
    int returnVal = GuiGetStyle(control, property);
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiLoadStyle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    JSValue js_fileName;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_fileName;
        if(JS_GetLength(ctx,argv[0],&size_fileName)==-1) {
            return JS_EXCEPTION;
        }
        fileName = js_malloc(ctx, size_fileName * sizeof(char));
        for(int i0=0; i0 < size_fileName; i0++){
            JSValue js_fileName = JS_GetPropertyUint32(ctx,argv[0],i0);
            fileName[i0] = (char)((char *)JS_ToCString(ctx, js_fileName))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_fileName = JS_DupValue(ctx,argv[0]);
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            size_t offset_fileName;
            size_t size_fileName;
            js_fileName = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_fileName,&size_fileName,NULL);
            fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, js_fileName);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    GuiLoadStyle((const char *)fileName);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, fileName);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, fileName);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_fileName);
    }
    else {
        JSClassID classid_fileName = JS_GetClassID(argv[0]);
        if(classid_fileName==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_fileName);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_guiLoadStyleDefault(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiLoadStyleDefault();
    return JS_UNDEFINED;
}

static JSValue js_guiEnableTooltip(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiEnableTooltip();
    return JS_UNDEFINED;
}

static JSValue js_guiDisableTooltip(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiDisableTooltip();
    return JS_UNDEFINED;
}

static JSValue js_guiSetTooltip(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * tooltip;
    JSValue js_tooltip;
    if(JS_IsArray(ctx,argv[0]) == 1) {
        size_t size_tooltip;
        if(JS_GetLength(ctx,argv[0],&size_tooltip)==-1) {
            return JS_EXCEPTION;
        }
        tooltip = js_malloc(ctx, size_tooltip * sizeof(char));
        for(int i0=0; i0 < size_tooltip; i0++){
            JSValue js_tooltip = JS_GetPropertyUint32(ctx,argv[0],i0);
            tooltip[i0] = (char)((char *)JS_ToCString(ctx, js_tooltip))[0];
        }
    }
    else if(JS_IsString(argv[0]) == 1) {
        tooltip = (char *)JS_ToCString(ctx, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_tooltip = JS_DupValue(ctx,argv[0]);
        size_t size_tooltip;
        tooltip = (char *)JS_GetArrayBuffer(ctx, &size_tooltip, js_tooltip);
    }
    else {
        JSClassID classid_tooltip = JS_GetClassID(argv[0]);
        if(classid_tooltip==JS_CLASS_INT8_ARRAY) {
            size_t offset_tooltip;
            size_t size_tooltip;
            js_tooltip = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_tooltip,&size_tooltip,NULL);
            tooltip = (char *)JS_GetArrayBuffer(ctx, &size_tooltip, js_tooltip);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    GuiSetTooltip((const char *)tooltip);
    if(JS_IsArray(ctx,argv[0]) == 1) {
        js_free(ctx, tooltip);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, tooltip);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        js_free(ctx, &js_tooltip);
    }
    else {
        JSClassID classid_tooltip = JS_GetClassID(argv[0]);
        if(classid_tooltip==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_tooltip);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_guiIconText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int iconId;
    JS_ToInt32(ctx, &iconId, argv[0]);
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    const char * returnVal = GuiIconText(iconId, (const char *)text);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_guiSetIconScale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int scale;
    JS_ToInt32(ctx, &scale, argv[0]);
    GuiSetIconScale(scale);
    return JS_UNDEFINED;
}

static JSValue js_guiDrawIcon(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int iconId;
    JS_ToInt32(ctx, &iconId, argv[0]);
    int posX;
    JS_ToInt32(ctx, &posX, argv[1]);
    int posY;
    JS_ToInt32(ctx, &posY, argv[2]);
    int pixelSize;
    JS_ToInt32(ctx, &pixelSize, argv[3]);
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    GuiDrawIcon(iconId, posX, posY, pixelSize, color);
    return JS_UNDEFINED;
}

static JSValue js_guiWindowBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * title;
    JSValue js_title;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_title;
        if(JS_GetLength(ctx,argv[1],&size_title)==-1) {
            return JS_EXCEPTION;
        }
        title = js_malloc(ctx, size_title * sizeof(char));
        for(int i0=0; i0 < size_title; i0++){
            JSValue js_title = JS_GetPropertyUint32(ctx,argv[1],i0);
            title[i0] = (char)((char *)JS_ToCString(ctx, js_title))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        title = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_title = JS_DupValue(ctx,argv[1]);
        size_t size_title;
        title = (char *)JS_GetArrayBuffer(ctx, &size_title, js_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[1]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            size_t offset_title;
            size_t size_title;
            js_title = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_title,&size_title,NULL);
            title = (char *)JS_GetArrayBuffer(ctx, &size_title, js_title);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiWindowBox(bounds, (const char *)title);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, title);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, title);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[1]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_title);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiGroupBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiGroupBox(bounds, (const char *)text);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiLine(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiLine(bounds, (const char *)text);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiPanel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiPanel(bounds, (const char *)text);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiScrollPanel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Rectangle* content_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
    if(content_ptr == NULL) return JS_EXCEPTION;
    Rectangle content = *content_ptr;
    Vector2* scroll = (Vector2*)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    if(scroll == NULL) return JS_EXCEPTION;
    Rectangle* view = (Rectangle*)JS_GetOpaque2(ctx, argv[4], js_Rectangle_class_id);
    if(view == NULL) return JS_EXCEPTION;
    int returnVal = GuiScrollPanel(bounds, (const char *)text, content, scroll, view);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiLabel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiLabel(bounds, (const char *)text);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiButton(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiButton(bounds, (const char *)text);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiLabelButton(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiLabelButton(bounds, (const char *)text);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiToggle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool * active;
    JSValue js_active;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_active;
        if(JS_GetLength(ctx,argv[2],&size_active)==-1) {
            return JS_EXCEPTION;
        }
        active = js_malloc(ctx, size_active * sizeof(bool));
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[2],i0);
            active[i0] = JS_ToBool(ctx, js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_active = JS_DupValue(ctx,argv[2]);
        size_t size_active;
        active = (bool *)JS_GetArrayBuffer(ctx, &size_active, js_active);
    }
    else {
        return JS_EXCEPTION;
    }
    int returnVal = GuiToggle(bounds, (const char *)text, active);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, active);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_active);
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiToggleGroup(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int * active;
    JSValue js_active;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_active;
        if(JS_GetLength(ctx,argv[2],&size_active)==-1) {
            return JS_EXCEPTION;
        }
        active = js_malloc(ctx, size_active * sizeof(int));
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[2],i0);
            JS_ToInt32(ctx, &active[i0], js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_active = JS_DupValue(ctx,argv[2]);
        size_t size_active;
        active = (int *)JS_GetArrayBuffer(ctx, &size_active, js_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            size_t offset_active;
            size_t size_active;
            js_active = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_active,&size_active,NULL);
            active = (int *)JS_GetArrayBuffer(ctx, &size_active, js_active);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiToggleGroup(bounds, (const char *)text, active);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, active);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &js_active);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiToggleSlider(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int * active;
    JSValue js_active;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_active;
        if(JS_GetLength(ctx,argv[2],&size_active)==-1) {
            return JS_EXCEPTION;
        }
        active = js_malloc(ctx, size_active * sizeof(int));
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[2],i0);
            JS_ToInt32(ctx, &active[i0], js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_active = JS_DupValue(ctx,argv[2]);
        size_t size_active;
        active = (int *)JS_GetArrayBuffer(ctx, &size_active, js_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            size_t offset_active;
            size_t size_active;
            js_active = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_active,&size_active,NULL);
            active = (int *)JS_GetArrayBuffer(ctx, &size_active, js_active);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiToggleSlider(bounds, (const char *)text, active);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, active);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &js_active);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiCheckBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool * checked;
    JSValue js_checked;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_checked;
        if(JS_GetLength(ctx,argv[2],&size_checked)==-1) {
            return JS_EXCEPTION;
        }
        checked = js_malloc(ctx, size_checked * sizeof(bool));
        for(int i0=0; i0 < size_checked; i0++){
            JSValue js_checked = JS_GetPropertyUint32(ctx,argv[2],i0);
            checked[i0] = JS_ToBool(ctx, js_checked);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_checked = JS_DupValue(ctx,argv[2]);
        size_t size_checked;
        checked = (bool *)JS_GetArrayBuffer(ctx, &size_checked, js_checked);
    }
    else {
        return JS_EXCEPTION;
    }
    int returnVal = GuiCheckBox(bounds, (const char *)text, checked);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, checked);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_checked);
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiComboBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int * active;
    JSValue js_active;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_active;
        if(JS_GetLength(ctx,argv[2],&size_active)==-1) {
            return JS_EXCEPTION;
        }
        active = js_malloc(ctx, size_active * sizeof(int));
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[2],i0);
            JS_ToInt32(ctx, &active[i0], js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_active = JS_DupValue(ctx,argv[2]);
        size_t size_active;
        active = (int *)JS_GetArrayBuffer(ctx, &size_active, js_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            size_t offset_active;
            size_t size_active;
            js_active = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_active,&size_active,NULL);
            active = (int *)JS_GetArrayBuffer(ctx, &size_active, js_active);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiComboBox(bounds, (const char *)text, active);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, active);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &js_active);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiDropdownBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int * active = NULL;
    int active_out;
    if(!JS_IsNull(argv[2])) {
        active = &active_out;
        JSValue active_js = JS_GetPropertyStr(ctx, argv[2], "active");
        JS_ToInt32(ctx, active, active_js);
    }
    bool editMode = JS_ToBool(ctx, argv[3]);
    int returnVal = GuiDropdownBox(bounds, (const char *)text, active, editMode);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(!JS_IsNull(argv[2])) {
        JS_SetPropertyStr(ctx, argv[2], "active", JS_NewInt32(ctx,active_out));
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiSpinner(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int * value = NULL;
    int value_out;
    if(!JS_IsNull(argv[2])) {
        value = &value_out;
        JSValue value_js = JS_GetPropertyStr(ctx, argv[2], "value");
        JS_ToInt32(ctx, value, value_js);
    }
    int minValue;
    JS_ToInt32(ctx, &minValue, argv[3]);
    int maxValue;
    JS_ToInt32(ctx, &maxValue, argv[4]);
    bool editMode = JS_ToBool(ctx, argv[5]);
    int returnVal = GuiSpinner(bounds, (const char *)text, value, minValue, maxValue, editMode);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(!JS_IsNull(argv[2])) {
        JS_SetPropertyStr(ctx, argv[2], "value", JS_NewInt32(ctx,value_out));
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiValueBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int * value = NULL;
    int value_out;
    if(!JS_IsNull(argv[2])) {
        value = &value_out;
        JSValue value_js = JS_GetPropertyStr(ctx, argv[2], "value");
        JS_ToInt32(ctx, value, value_js);
    }
    int minValue;
    JS_ToInt32(ctx, &minValue, argv[3]);
    int maxValue;
    JS_ToInt32(ctx, &maxValue, argv[4]);
    bool editMode = JS_ToBool(ctx, argv[5]);
    int returnVal = GuiValueBox(bounds, (const char *)text, value, minValue, maxValue, editMode);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(!JS_IsNull(argv[2])) {
        JS_SetPropertyStr(ctx, argv[2], "value", JS_NewInt32(ctx,value_out));
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiValueBoxFloat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * textValue;
    JSValue js_textValue;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_textValue;
        if(JS_GetLength(ctx,argv[2],&size_textValue)==-1) {
            return JS_EXCEPTION;
        }
        textValue = js_malloc(ctx, size_textValue * sizeof(char));
        for(int i0=0; i0 < size_textValue; i0++){
            JSValue js_textValue = JS_GetPropertyUint32(ctx,argv[2],i0);
            textValue[i0] = (char)((char *)JS_ToCString(ctx, js_textValue))[0];
        }
    }
    else if(JS_IsString(argv[2]) == 1) {
        textValue = (char *)JS_ToCString(ctx, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_textValue = JS_DupValue(ctx,argv[2]);
        size_t size_textValue;
        textValue = (char *)JS_GetArrayBuffer(ctx, &size_textValue, js_textValue);
    }
    else {
        JSClassID classid_textValue = JS_GetClassID(argv[2]);
        if(classid_textValue==JS_CLASS_INT8_ARRAY) {
            size_t offset_textValue;
            size_t size_textValue;
            js_textValue = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textValue,&size_textValue,NULL);
            textValue = (char *)JS_GetArrayBuffer(ctx, &size_textValue, js_textValue);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,argv[3]) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,argv[3],&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[3],i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_value = JS_DupValue(ctx,argv[3]);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    bool editMode = JS_ToBool(ctx, argv[4]);
    int returnVal = GuiValueBoxFloat(bounds, (const char *)text, textValue, value, editMode);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, textValue);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, textValue);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_textValue);
    }
    else {
        JSClassID classid_textValue = JS_GetClassID(argv[2]);
        if(classid_textValue==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_textValue);
        }
    }
    if(JS_IsArray(ctx,argv[3]) == 1) {
        js_free(ctx, value);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_free(ctx, &js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            js_free(ctx, &js_value);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiTextBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    JSValue text_js = JS_GetPropertyStr(ctx, argv[1], "text");
    size_t text_len;
    const char * text_val = JS_ToCStringLen(ctx, &text_len, text_js);
    memcpy((void *)textbuffer, text_val, text_len);
    textbuffer[text_len] = 0;
    char * text = textbuffer;
    int textSize = 4096;
    bool editMode = JS_ToBool(ctx, argv[2]);
    int returnVal = GuiTextBox(bounds, text, textSize, editMode);
    JS_FreeCString(ctx, text_val);
    JS_SetPropertyStr(ctx, argv[1], "text", JS_NewString(ctx,text));
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiSlider(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * textLeft;
    JSValue js_textLeft;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_textLeft;
        if(JS_GetLength(ctx,argv[1],&size_textLeft)==-1) {
            return JS_EXCEPTION;
        }
        textLeft = js_malloc(ctx, size_textLeft * sizeof(char));
        for(int i0=0; i0 < size_textLeft; i0++){
            JSValue js_textLeft = JS_GetPropertyUint32(ctx,argv[1],i0);
            textLeft[i0] = (char)((char *)JS_ToCString(ctx, js_textLeft))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        textLeft = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_textLeft = JS_DupValue(ctx,argv[1]);
        size_t size_textLeft;
        textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, js_textLeft);
    }
    else {
        JSClassID classid_textLeft = JS_GetClassID(argv[1]);
        if(classid_textLeft==JS_CLASS_INT8_ARRAY) {
            size_t offset_textLeft;
            size_t size_textLeft;
            js_textLeft = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_textLeft,&size_textLeft,NULL);
            textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, js_textLeft);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * textRight;
    JSValue js_textRight;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_textRight;
        if(JS_GetLength(ctx,argv[2],&size_textRight)==-1) {
            return JS_EXCEPTION;
        }
        textRight = js_malloc(ctx, size_textRight * sizeof(char));
        for(int i0=0; i0 < size_textRight; i0++){
            JSValue js_textRight = JS_GetPropertyUint32(ctx,argv[2],i0);
            textRight[i0] = (char)((char *)JS_ToCString(ctx, js_textRight))[0];
        }
    }
    else if(JS_IsString(argv[2]) == 1) {
        textRight = (char *)JS_ToCString(ctx, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_textRight = JS_DupValue(ctx,argv[2]);
        size_t size_textRight;
        textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, js_textRight);
    }
    else {
        JSClassID classid_textRight = JS_GetClassID(argv[2]);
        if(classid_textRight==JS_CLASS_INT8_ARRAY) {
            size_t offset_textRight;
            size_t size_textRight;
            js_textRight = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textRight,&size_textRight,NULL);
            textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, js_textRight);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,argv[3]) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,argv[3],&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[3],i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_value = JS_DupValue(ctx,argv[3]);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    double double_minValue;
    JS_ToFloat64(ctx, &double_minValue, argv[4]);
    float minValue = (float)double_minValue;
    double double_maxValue;
    JS_ToFloat64(ctx, &double_maxValue, argv[5]);
    float maxValue = (float)double_maxValue;
    int returnVal = GuiSlider(bounds, (const char *)textLeft, (const char *)textRight, value, minValue, maxValue);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, textLeft);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, textLeft);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_textLeft);
    }
    else {
        JSClassID classid_textLeft = JS_GetClassID(argv[1]);
        if(classid_textLeft==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_textLeft);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, textRight);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, textRight);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_textRight);
    }
    else {
        JSClassID classid_textRight = JS_GetClassID(argv[2]);
        if(classid_textRight==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_textRight);
        }
    }
    if(JS_IsArray(ctx,argv[3]) == 1) {
        js_free(ctx, value);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_free(ctx, &js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            js_free(ctx, &js_value);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiSliderBar(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * textLeft;
    JSValue js_textLeft;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_textLeft;
        if(JS_GetLength(ctx,argv[1],&size_textLeft)==-1) {
            return JS_EXCEPTION;
        }
        textLeft = js_malloc(ctx, size_textLeft * sizeof(char));
        for(int i0=0; i0 < size_textLeft; i0++){
            JSValue js_textLeft = JS_GetPropertyUint32(ctx,argv[1],i0);
            textLeft[i0] = (char)((char *)JS_ToCString(ctx, js_textLeft))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        textLeft = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_textLeft = JS_DupValue(ctx,argv[1]);
        size_t size_textLeft;
        textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, js_textLeft);
    }
    else {
        JSClassID classid_textLeft = JS_GetClassID(argv[1]);
        if(classid_textLeft==JS_CLASS_INT8_ARRAY) {
            size_t offset_textLeft;
            size_t size_textLeft;
            js_textLeft = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_textLeft,&size_textLeft,NULL);
            textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, js_textLeft);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * textRight;
    JSValue js_textRight;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_textRight;
        if(JS_GetLength(ctx,argv[2],&size_textRight)==-1) {
            return JS_EXCEPTION;
        }
        textRight = js_malloc(ctx, size_textRight * sizeof(char));
        for(int i0=0; i0 < size_textRight; i0++){
            JSValue js_textRight = JS_GetPropertyUint32(ctx,argv[2],i0);
            textRight[i0] = (char)((char *)JS_ToCString(ctx, js_textRight))[0];
        }
    }
    else if(JS_IsString(argv[2]) == 1) {
        textRight = (char *)JS_ToCString(ctx, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_textRight = JS_DupValue(ctx,argv[2]);
        size_t size_textRight;
        textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, js_textRight);
    }
    else {
        JSClassID classid_textRight = JS_GetClassID(argv[2]);
        if(classid_textRight==JS_CLASS_INT8_ARRAY) {
            size_t offset_textRight;
            size_t size_textRight;
            js_textRight = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textRight,&size_textRight,NULL);
            textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, js_textRight);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,argv[3]) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,argv[3],&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[3],i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_value = JS_DupValue(ctx,argv[3]);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    double double_minValue;
    JS_ToFloat64(ctx, &double_minValue, argv[4]);
    float minValue = (float)double_minValue;
    double double_maxValue;
    JS_ToFloat64(ctx, &double_maxValue, argv[5]);
    float maxValue = (float)double_maxValue;
    int returnVal = GuiSliderBar(bounds, (const char *)textLeft, (const char *)textRight, value, minValue, maxValue);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, textLeft);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, textLeft);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_textLeft);
    }
    else {
        JSClassID classid_textLeft = JS_GetClassID(argv[1]);
        if(classid_textLeft==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_textLeft);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, textRight);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, textRight);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_textRight);
    }
    else {
        JSClassID classid_textRight = JS_GetClassID(argv[2]);
        if(classid_textRight==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_textRight);
        }
    }
    if(JS_IsArray(ctx,argv[3]) == 1) {
        js_free(ctx, value);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_free(ctx, &js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            js_free(ctx, &js_value);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiProgressBar(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * textLeft;
    JSValue js_textLeft;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_textLeft;
        if(JS_GetLength(ctx,argv[1],&size_textLeft)==-1) {
            return JS_EXCEPTION;
        }
        textLeft = js_malloc(ctx, size_textLeft * sizeof(char));
        for(int i0=0; i0 < size_textLeft; i0++){
            JSValue js_textLeft = JS_GetPropertyUint32(ctx,argv[1],i0);
            textLeft[i0] = (char)((char *)JS_ToCString(ctx, js_textLeft))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        textLeft = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_textLeft = JS_DupValue(ctx,argv[1]);
        size_t size_textLeft;
        textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, js_textLeft);
    }
    else {
        JSClassID classid_textLeft = JS_GetClassID(argv[1]);
        if(classid_textLeft==JS_CLASS_INT8_ARRAY) {
            size_t offset_textLeft;
            size_t size_textLeft;
            js_textLeft = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_textLeft,&size_textLeft,NULL);
            textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, js_textLeft);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * textRight;
    JSValue js_textRight;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_textRight;
        if(JS_GetLength(ctx,argv[2],&size_textRight)==-1) {
            return JS_EXCEPTION;
        }
        textRight = js_malloc(ctx, size_textRight * sizeof(char));
        for(int i0=0; i0 < size_textRight; i0++){
            JSValue js_textRight = JS_GetPropertyUint32(ctx,argv[2],i0);
            textRight[i0] = (char)((char *)JS_ToCString(ctx, js_textRight))[0];
        }
    }
    else if(JS_IsString(argv[2]) == 1) {
        textRight = (char *)JS_ToCString(ctx, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_textRight = JS_DupValue(ctx,argv[2]);
        size_t size_textRight;
        textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, js_textRight);
    }
    else {
        JSClassID classid_textRight = JS_GetClassID(argv[2]);
        if(classid_textRight==JS_CLASS_INT8_ARRAY) {
            size_t offset_textRight;
            size_t size_textRight;
            js_textRight = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textRight,&size_textRight,NULL);
            textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, js_textRight);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,argv[3]) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,argv[3],&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[3],i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_value = JS_DupValue(ctx,argv[3]);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    double double_minValue;
    JS_ToFloat64(ctx, &double_minValue, argv[4]);
    float minValue = (float)double_minValue;
    double double_maxValue;
    JS_ToFloat64(ctx, &double_maxValue, argv[5]);
    float maxValue = (float)double_maxValue;
    int returnVal = GuiProgressBar(bounds, (const char *)textLeft, (const char *)textRight, value, minValue, maxValue);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, textLeft);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, textLeft);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_textLeft);
    }
    else {
        JSClassID classid_textLeft = JS_GetClassID(argv[1]);
        if(classid_textLeft==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_textLeft);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, textRight);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, textRight);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_textRight);
    }
    else {
        JSClassID classid_textRight = JS_GetClassID(argv[2]);
        if(classid_textRight==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_textRight);
        }
    }
    if(JS_IsArray(ctx,argv[3]) == 1) {
        js_free(ctx, value);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_free(ctx, &js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            js_free(ctx, &js_value);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiStatusBar(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiStatusBar(bounds, (const char *)text);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiDummyRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiDummyRec(bounds, (const char *)text);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiGrid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    double double_spacing;
    JS_ToFloat64(ctx, &double_spacing, argv[2]);
    float spacing = (float)double_spacing;
    int subdivs;
    JS_ToInt32(ctx, &subdivs, argv[3]);
    Vector2* mouseCell = (Vector2*)JS_GetOpaque2(ctx, argv[4], js_Vector2_class_id);
    if(mouseCell == NULL) return JS_EXCEPTION;
    int returnVal = GuiGrid(bounds, (const char *)text, spacing, subdivs, mouseCell);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiListView(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int * scrollIndex = NULL;
    int scrollIndex_out;
    if(!JS_IsNull(argv[2])) {
        scrollIndex = &scrollIndex_out;
        JSValue scrollIndex_js = JS_GetPropertyStr(ctx, argv[2], "scrollIndex");
        JS_ToInt32(ctx, scrollIndex, scrollIndex_js);
    }
    int * active;
    JSValue js_active;
    if(JS_IsArray(ctx,argv[3]) == 1) {
        size_t size_active;
        if(JS_GetLength(ctx,argv[3],&size_active)==-1) {
            return JS_EXCEPTION;
        }
        active = js_malloc(ctx, size_active * sizeof(int));
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[3],i0);
            JS_ToInt32(ctx, &active[i0], js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_active = JS_DupValue(ctx,argv[3]);
        size_t size_active;
        active = (int *)JS_GetArrayBuffer(ctx, &size_active, js_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[3]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            size_t offset_active;
            size_t size_active;
            js_active = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_active,&size_active,NULL);
            active = (int *)JS_GetArrayBuffer(ctx, &size_active, js_active);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiListView(bounds, (const char *)text, scrollIndex, active);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(!JS_IsNull(argv[2])) {
        JS_SetPropertyStr(ctx, argv[2], "scrollIndex", JS_NewInt32(ctx,scrollIndex_out));
    }
    if(JS_IsArray(ctx,argv[3]) == 1) {
        js_free(ctx, active);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_free(ctx, &js_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[3]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &js_active);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiMessageBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * title;
    JSValue js_title;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_title;
        if(JS_GetLength(ctx,argv[1],&size_title)==-1) {
            return JS_EXCEPTION;
        }
        title = js_malloc(ctx, size_title * sizeof(char));
        for(int i0=0; i0 < size_title; i0++){
            JSValue js_title = JS_GetPropertyUint32(ctx,argv[1],i0);
            title[i0] = (char)((char *)JS_ToCString(ctx, js_title))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        title = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_title = JS_DupValue(ctx,argv[1]);
        size_t size_title;
        title = (char *)JS_GetArrayBuffer(ctx, &size_title, js_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[1]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            size_t offset_title;
            size_t size_title;
            js_title = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_title,&size_title,NULL);
            title = (char *)JS_GetArrayBuffer(ctx, &size_title, js_title);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * message;
    JSValue js_message;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_message;
        if(JS_GetLength(ctx,argv[2],&size_message)==-1) {
            return JS_EXCEPTION;
        }
        message = js_malloc(ctx, size_message * sizeof(char));
        for(int i0=0; i0 < size_message; i0++){
            JSValue js_message = JS_GetPropertyUint32(ctx,argv[2],i0);
            message[i0] = (char)((char *)JS_ToCString(ctx, js_message))[0];
        }
    }
    else if(JS_IsString(argv[2]) == 1) {
        message = (char *)JS_ToCString(ctx, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_message = JS_DupValue(ctx,argv[2]);
        size_t size_message;
        message = (char *)JS_GetArrayBuffer(ctx, &size_message, js_message);
    }
    else {
        JSClassID classid_message = JS_GetClassID(argv[2]);
        if(classid_message==JS_CLASS_INT8_ARRAY) {
            size_t offset_message;
            size_t size_message;
            js_message = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_message,&size_message,NULL);
            message = (char *)JS_GetArrayBuffer(ctx, &size_message, js_message);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * buttons;
    JSValue js_buttons;
    if(JS_IsArray(ctx,argv[3]) == 1) {
        size_t size_buttons;
        if(JS_GetLength(ctx,argv[3],&size_buttons)==-1) {
            return JS_EXCEPTION;
        }
        buttons = js_malloc(ctx, size_buttons * sizeof(char));
        for(int i0=0; i0 < size_buttons; i0++){
            JSValue js_buttons = JS_GetPropertyUint32(ctx,argv[3],i0);
            buttons[i0] = (char)((char *)JS_ToCString(ctx, js_buttons))[0];
        }
    }
    else if(JS_IsString(argv[3]) == 1) {
        buttons = (char *)JS_ToCString(ctx, argv[3]);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_buttons = JS_DupValue(ctx,argv[3]);
        size_t size_buttons;
        buttons = (char *)JS_GetArrayBuffer(ctx, &size_buttons, js_buttons);
    }
    else {
        JSClassID classid_buttons = JS_GetClassID(argv[3]);
        if(classid_buttons==JS_CLASS_INT8_ARRAY) {
            size_t offset_buttons;
            size_t size_buttons;
            js_buttons = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_buttons,&size_buttons,NULL);
            buttons = (char *)JS_GetArrayBuffer(ctx, &size_buttons, js_buttons);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiMessageBox(bounds, (const char *)title, (const char *)message, (const char *)buttons);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, title);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, title);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[1]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_title);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, message);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, message);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_message);
    }
    else {
        JSClassID classid_message = JS_GetClassID(argv[2]);
        if(classid_message==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_message);
        }
    }
    if(JS_IsArray(ctx,argv[3]) == 1) {
        js_free(ctx, buttons);
    }
    else if(JS_IsString(argv[3]) == 1) {
        JS_FreeCString(ctx, buttons);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_free(ctx, &js_buttons);
    }
    else {
        JSClassID classid_buttons = JS_GetClassID(argv[3]);
        if(classid_buttons==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_buttons);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiTextInputBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * title;
    JSValue js_title;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_title;
        if(JS_GetLength(ctx,argv[1],&size_title)==-1) {
            return JS_EXCEPTION;
        }
        title = js_malloc(ctx, size_title * sizeof(char));
        for(int i0=0; i0 < size_title; i0++){
            JSValue js_title = JS_GetPropertyUint32(ctx,argv[1],i0);
            title[i0] = (char)((char *)JS_ToCString(ctx, js_title))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        title = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_title = JS_DupValue(ctx,argv[1]);
        size_t size_title;
        title = (char *)JS_GetArrayBuffer(ctx, &size_title, js_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[1]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            size_t offset_title;
            size_t size_title;
            js_title = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_title,&size_title,NULL);
            title = (char *)JS_GetArrayBuffer(ctx, &size_title, js_title);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * message;
    JSValue js_message;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_message;
        if(JS_GetLength(ctx,argv[2],&size_message)==-1) {
            return JS_EXCEPTION;
        }
        message = js_malloc(ctx, size_message * sizeof(char));
        for(int i0=0; i0 < size_message; i0++){
            JSValue js_message = JS_GetPropertyUint32(ctx,argv[2],i0);
            message[i0] = (char)((char *)JS_ToCString(ctx, js_message))[0];
        }
    }
    else if(JS_IsString(argv[2]) == 1) {
        message = (char *)JS_ToCString(ctx, argv[2]);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_message = JS_DupValue(ctx,argv[2]);
        size_t size_message;
        message = (char *)JS_GetArrayBuffer(ctx, &size_message, js_message);
    }
    else {
        JSClassID classid_message = JS_GetClassID(argv[2]);
        if(classid_message==JS_CLASS_INT8_ARRAY) {
            size_t offset_message;
            size_t size_message;
            js_message = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_message,&size_message,NULL);
            message = (char *)JS_GetArrayBuffer(ctx, &size_message, js_message);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    char * buttons;
    JSValue js_buttons;
    if(JS_IsArray(ctx,argv[3]) == 1) {
        size_t size_buttons;
        if(JS_GetLength(ctx,argv[3],&size_buttons)==-1) {
            return JS_EXCEPTION;
        }
        buttons = js_malloc(ctx, size_buttons * sizeof(char));
        for(int i0=0; i0 < size_buttons; i0++){
            JSValue js_buttons = JS_GetPropertyUint32(ctx,argv[3],i0);
            buttons[i0] = (char)((char *)JS_ToCString(ctx, js_buttons))[0];
        }
    }
    else if(JS_IsString(argv[3]) == 1) {
        buttons = (char *)JS_ToCString(ctx, argv[3]);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_buttons = JS_DupValue(ctx,argv[3]);
        size_t size_buttons;
        buttons = (char *)JS_GetArrayBuffer(ctx, &size_buttons, js_buttons);
    }
    else {
        JSClassID classid_buttons = JS_GetClassID(argv[3]);
        if(classid_buttons==JS_CLASS_INT8_ARRAY) {
            size_t offset_buttons;
            size_t size_buttons;
            js_buttons = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_buttons,&size_buttons,NULL);
            buttons = (char *)JS_GetArrayBuffer(ctx, &size_buttons, js_buttons);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    JSValue text_js = JS_GetPropertyStr(ctx, argv[4], "text");
    size_t text_len;
    const char * text_val = JS_ToCStringLen(ctx, &text_len, text_js);
    memcpy((void *)textbuffer, text_val, text_len);
    textbuffer[text_len] = 0;
    char * text = textbuffer;
    int textMaxSize = 4096;
    bool * secretViewActive = NULL;
    bool secretViewActive_out;
    if(!JS_IsNull(argv[5])) {
        secretViewActive = &secretViewActive_out;
        JSValue secretViewActive_js = JS_GetPropertyStr(ctx, argv[5], "secretViewActive");
        JS_ToBool(ctx, secretViewActive_js);
    }
    int returnVal = GuiTextInputBox(bounds, (const char *)title, (const char *)message, (const char *)buttons, text, textMaxSize, secretViewActive);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, title);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, title);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[1]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_title);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, message);
    }
    else if(JS_IsString(argv[2]) == 1) {
        JS_FreeCString(ctx, message);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_message);
    }
    else {
        JSClassID classid_message = JS_GetClassID(argv[2]);
        if(classid_message==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_message);
        }
    }
    if(JS_IsArray(ctx,argv[3]) == 1) {
        js_free(ctx, buttons);
    }
    else if(JS_IsString(argv[3]) == 1) {
        JS_FreeCString(ctx, buttons);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        js_free(ctx, &js_buttons);
    }
    else {
        JSClassID classid_buttons = JS_GetClassID(argv[3]);
        if(classid_buttons==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_buttons);
        }
    }
    JS_FreeCString(ctx, text_val);
    JS_SetPropertyStr(ctx, argv[4], "text", JS_NewString(ctx,text));
    if(!JS_IsNull(argv[5])) {
        JS_SetPropertyStr(ctx, argv[5], "secretViewActive", JS_NewBool(ctx,secretViewActive_out));
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiColorPicker(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Color* color = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color == NULL) return JS_EXCEPTION;
    int returnVal = GuiColorPicker(bounds, (const char *)text, color);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiColorPanel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Color* color = (Color*)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
    if(color == NULL) return JS_EXCEPTION;
    int returnVal = GuiColorPanel(bounds, (const char *)text, color);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiColorBarAlpha(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    float * alpha;
    JSValue js_alpha;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_alpha;
        if(JS_GetLength(ctx,argv[2],&size_alpha)==-1) {
            return JS_EXCEPTION;
        }
        alpha = js_malloc(ctx, size_alpha * sizeof(float));
        for(int i0=0; i0 < size_alpha; i0++){
            JSValue js_alpha = JS_GetPropertyUint32(ctx,argv[2],i0);
            double double_alpha[i0];
            JS_ToFloat64(ctx, &double_alpha[i0], js_alpha);
            alpha[i0] = (float)double_alpha[i0];
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_alpha = JS_DupValue(ctx,argv[2]);
        size_t size_alpha;
        alpha = (float *)JS_GetArrayBuffer(ctx, &size_alpha, js_alpha);
    }
    else {
        JSClassID classid_alpha = JS_GetClassID(argv[2]);
        if(classid_alpha==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_alpha;
            size_t size_alpha;
            js_alpha = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_alpha,&size_alpha,NULL);
            alpha = (float *)JS_GetArrayBuffer(ctx, &size_alpha, js_alpha);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiColorBarAlpha(bounds, (const char *)text, alpha);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, alpha);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_alpha);
    }
    else {
        JSClassID classid_alpha = JS_GetClassID(argv[2]);
        if(classid_alpha==JS_CLASS_FLOAT32_ARRAY) {
            js_free(ctx, &js_alpha);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiColorBarHue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    float * value;
    JSValue js_value;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        size_t size_value;
        if(JS_GetLength(ctx,argv[2],&size_value)==-1) {
            return JS_EXCEPTION;
        }
        value = js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[2],i0);
            double double_value[i0];
            JS_ToFloat64(ctx, &double_value[i0], js_value);
            value[i0] = (float)double_value[i0];
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_value = JS_DupValue(ctx,argv[2]);
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[2]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            js_value = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, js_value);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiColorBarHue(bounds, (const char *)text, value);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    if(JS_IsArray(ctx,argv[2]) == 1) {
        js_free(ctx, value);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        js_free(ctx, &js_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[2]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            js_free(ctx, &js_value);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiColorPickerHSV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Vector3* colorHsv = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(colorHsv == NULL) return JS_EXCEPTION;
    int returnVal = GuiColorPickerHSV(bounds, (const char *)text, colorHsv);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_guiColorPanelHSV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* bounds_ptr = (Rectangle*)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
    if(bounds_ptr == NULL) return JS_EXCEPTION;
    Rectangle bounds = *bounds_ptr;
    char * text;
    JSValue js_text;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        size_t size_text;
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            return JS_EXCEPTION;
        }
        text = js_malloc(ctx, size_text * sizeof(char));
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            text[i0] = (char)((char *)JS_ToCString(ctx, js_text))[0];
        }
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCString(ctx, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_text = JS_DupValue(ctx,argv[1]);
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            js_text = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, js_text);
        }
        else {
            return JS_EXCEPTION;
        }
    }
    Vector3* colorHsv = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(colorHsv == NULL) return JS_EXCEPTION;
    int returnVal = GuiColorPanelHSV(bounds, (const char *)text, colorHsv);
    if(JS_IsArray(ctx,argv[1]) == 1) {
        js_free(ctx, text);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        js_free(ctx, &js_text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[1]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &js_text);
        }
    }
    JSValue ret = JS_NewInt32(ctx, returnVal);
    return ret;
}

static JSValue js_createLight(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int type;
    JS_ToInt32(ctx, &type, argv[0]);
    Vector3* position_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
    if(position_ptr == NULL) return JS_EXCEPTION;
    Vector3 position = *position_ptr;
    Vector3* target_ptr = (Vector3*)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
    if(target_ptr == NULL) return JS_EXCEPTION;
    Vector3 target = *target_ptr;
    Color* color_ptr = (Color*)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
    if(color_ptr == NULL) return JS_EXCEPTION;
    Color color = *color_ptr;
    Shader* shader_ptr = (Shader*)JS_GetOpaque2(ctx, argv[4], js_Shader_class_id);
    if(shader_ptr == NULL) return JS_EXCEPTION;
    Shader shader = *shader_ptr;
    Light returnVal = CreateLight(type, position, target, color, shader);
    Light* ret_ptr = (Light*)js_malloc(ctx, sizeof(Light));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Light_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_updateLightValues(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* shader_ptr = (Shader*)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
    if(shader_ptr == NULL) return JS_EXCEPTION;
    Shader shader = *shader_ptr;
    Light* light_ptr = (Light*)JS_GetOpaque2(ctx, argv[1], js_Light_class_id);
    if(light_ptr == NULL) return JS_EXCEPTION;
    Light light = *light_ptr;
    UpdateLightValues(shader, light);
    return JS_UNDEFINED;
}

static JSValue js_easeLinearNone(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseLinearNone(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeLinearIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseLinearIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeLinearOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseLinearOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeLinearInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseLinearInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeSineIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseSineIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeSineOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseSineOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeSineInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseSineInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeCircIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseCircIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeCircOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseCircOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeCircInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseCircInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeCubicIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseCubicIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeCubicOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseCubicOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeCubicInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseCubicInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeQuadIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseQuadIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeQuadOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseQuadOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeQuadInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseQuadInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeExpoIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseExpoIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeExpoOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseExpoOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeExpoInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseExpoInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeBackIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseBackIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeBounceOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseBounceOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeBounceInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseBounceInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_easeElasticIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    JS_ToFloat64(ctx, &double_t, argv[0]);
    float t = (float)double_t;
    double double_b;
    JS_ToFloat64(ctx, &double_b, argv[1]);
    float b = (float)double_b;
    double double_c;
    JS_ToFloat64(ctx, &double_c, argv[2]);
    float c = (float)double_c;
    double double_d;
    JS_ToFloat64(ctx, &double_d, argv[3]);
    float d = (float)double_d;
    float returnVal = EaseElasticIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, returnVal);
    return ret;
}

static JSValue js_getDefaultLightmapperConfig(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    LightmapperConfig returnVal = GetDefaultLightmapperConfig();
    LightmapperConfig* ret_ptr = (LightmapperConfig*)js_malloc(ctx, sizeof(LightmapperConfig));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_LightmapperConfig_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadLightmapper(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int w;
    JS_ToInt32(ctx, &w, argv[0]);
    int h;
    JS_ToInt32(ctx, &h, argv[1]);
    Mesh* mesh_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[2], js_Mesh_class_id);
    if(mesh_ptr == NULL) return JS_EXCEPTION;
    Mesh mesh = *mesh_ptr;
    LightmapperConfig* cfg_ptr = (LightmapperConfig*)JS_GetOpaque2(ctx, argv[3], js_LightmapperConfig_class_id);
    if(cfg_ptr == NULL) return JS_EXCEPTION;
    LightmapperConfig cfg = *cfg_ptr;
    Lightmapper returnVal = LoadLightmapper(w, h, mesh, cfg);
    Lightmapper* ret_ptr = (Lightmapper*)js_malloc(ctx, sizeof(Lightmapper));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Lightmapper_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_loadMaterialLightmapper(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Color* emissiveColor_ptr = (Color*)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
    if(emissiveColor_ptr == NULL) return JS_EXCEPTION;
    Color emissiveColor = *emissiveColor_ptr;
    double double_intensity;
    JS_ToFloat64(ctx, &double_intensity, argv[1]);
    float intensity = (float)double_intensity;
    Material returnVal = LoadMaterialLightmapper(emissiveColor, intensity);
    Material* ret_ptr = (Material*)js_malloc(ctx, sizeof(Material));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Material_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_unloadLightmapper(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Lightmapper* lm_ptr = (Lightmapper*)JS_GetOpaque2(ctx, argv[0], js_Lightmapper_class_id);
    if(lm_ptr == NULL) return JS_EXCEPTION;
    Lightmapper lm = *lm_ptr;
    UnloadLightmapper(lm);
    return JS_UNDEFINED;
}

static JSValue js_beginLightmap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    BeginLightmap();
    return JS_UNDEFINED;
}

static JSValue js_endLightmap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    EndLightmap();
    return JS_UNDEFINED;
}

static JSValue js_beginLightmapFragment(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Lightmapper* lm = (Lightmapper*)JS_GetOpaque2(ctx, argv[0], js_Lightmapper_class_id);
    if(lm == NULL) return JS_EXCEPTION;
    bool returnVal = BeginLightmapFragment(lm);
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_endLightmapFragment(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Lightmapper* lm = (Lightmapper*)JS_GetOpaque2(ctx, argv[0], js_Lightmapper_class_id);
    if(lm == NULL) return JS_EXCEPTION;
    EndLightmapFragment(lm);
    return JS_UNDEFINED;
}

static JSValue js_loadImageFromLightmapper(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Lightmapper* lm_ptr = (Lightmapper*)JS_GetOpaque2(ctx, argv[0], js_Lightmapper_class_id);
    if(lm_ptr == NULL) return JS_EXCEPTION;
    Lightmapper lm = *lm_ptr;
    Image returnVal = LoadImageFromLightmapper(lm);
    Image* ret_ptr = (Image*)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_setModelMaterial(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model == NULL) return JS_EXCEPTION;
    int materialIndex;
    JS_ToInt32(ctx, &materialIndex, argv[1]);
    Material* material_ptr = (Material*)JS_GetOpaque2(ctx, argv[2], js_Material_class_id);
    if(material_ptr == NULL) return JS_EXCEPTION;
    Material material = *material_ptr;
    SetModelMaterial(model, materialIndex, material);
    return JS_UNDEFINED;
}

static JSValue js_getModelMaterial(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model == NULL) return JS_EXCEPTION;
    int materialIndex;
    JS_ToInt32(ctx, &materialIndex, argv[1]);
    Material returnVal = GetModelMaterial(model, materialIndex);
    Material* ret_ptr = (Material*)js_malloc(ctx, sizeof(Material));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Material_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_getModelMesh(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Model* model = (Model*)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
    if(model == NULL) return JS_EXCEPTION;
    int meshIndex;
    JS_ToInt32(ctx, &meshIndex, argv[1]);
    Mesh returnVal = GetModelMesh(model, meshIndex);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_setShaderLocation(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Shader* shader = (Shader*)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
    if(shader == NULL) return JS_EXCEPTION;
    int constant;
    JS_ToInt32(ctx, &constant, argv[1]);
    int location;
    JS_ToInt32(ctx, &location, argv[2]);
    SetShaderLocation(shader, constant, location);
    return JS_UNDEFINED;
}

static JSValue js_imageReadPixel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Image* image = (Image*)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
    if(image == NULL) return JS_EXCEPTION;
    int x;
    JS_ToInt32(ctx, &x, argv[1]);
    int y;
    JS_ToInt32(ctx, &y, argv[2]);
    Color returnVal = ImageReadPixel(image, x, y);
    Color* ret_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_meshCopy(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* mesh_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(mesh_ptr == NULL) return JS_EXCEPTION;
    Mesh mesh = *mesh_ptr;
    Mesh returnVal = MeshCopy(mesh);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static JSValue js_meshMerge(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Mesh* a_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
    if(a_ptr == NULL) return JS_EXCEPTION;
    Mesh a = *a_ptr;
    Mesh* b_ptr = (Mesh*)JS_GetOpaque2(ctx, argv[1], js_Mesh_class_id);
    if(b_ptr == NULL) return JS_EXCEPTION;
    Mesh b = *b_ptr;
    Mesh returnVal = MeshMerge(a, b);
    Mesh* ret_ptr = (Mesh*)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

static const JSCFunctionListEntry js_raylib_core_funcs[] = {
    JS_CFUNC_DEF("initWindow",3,js_initWindow),
    JS_CFUNC_DEF("closeWindow",0,js_closeWindow),
    JS_CFUNC_DEF("windowShouldClose",0,js_windowShouldClose),
    JS_CFUNC_DEF("isWindowReady",0,js_isWindowReady),
    JS_CFUNC_DEF("isWindowFullscreen",0,js_isWindowFullscreen),
    JS_CFUNC_DEF("isWindowHidden",0,js_isWindowHidden),
    JS_CFUNC_DEF("isWindowMinimized",0,js_isWindowMinimized),
    JS_CFUNC_DEF("isWindowMaximized",0,js_isWindowMaximized),
    JS_CFUNC_DEF("isWindowFocused",0,js_isWindowFocused),
    JS_CFUNC_DEF("isWindowResized",0,js_isWindowResized),
    JS_CFUNC_DEF("isWindowState",1,js_isWindowState),
    JS_CFUNC_DEF("setWindowState",1,js_setWindowState),
    JS_CFUNC_DEF("clearWindowState",1,js_clearWindowState),
    JS_CFUNC_DEF("toggleFullscreen",0,js_toggleFullscreen),
    JS_CFUNC_DEF("toggleBorderlessWindowed",0,js_toggleBorderlessWindowed),
    JS_CFUNC_DEF("maximizeWindow",0,js_maximizeWindow),
    JS_CFUNC_DEF("minimizeWindow",0,js_minimizeWindow),
    JS_CFUNC_DEF("restoreWindow",0,js_restoreWindow),
    JS_CFUNC_DEF("setWindowIcon",1,js_setWindowIcon),
    JS_CFUNC_DEF("setWindowTitle",1,js_setWindowTitle),
    JS_CFUNC_DEF("setWindowPosition",2,js_setWindowPosition),
    JS_CFUNC_DEF("setWindowMonitor",1,js_setWindowMonitor),
    JS_CFUNC_DEF("setWindowMinSize",2,js_setWindowMinSize),
    JS_CFUNC_DEF("setWindowMaxSize",2,js_setWindowMaxSize),
    JS_CFUNC_DEF("setWindowSize",2,js_setWindowSize),
    JS_CFUNC_DEF("setWindowOpacity",1,js_setWindowOpacity),
    JS_CFUNC_DEF("setWindowFocused",0,js_setWindowFocused),
    JS_CFUNC_DEF("getScreenWidth",0,js_getScreenWidth),
    JS_CFUNC_DEF("getScreenHeight",0,js_getScreenHeight),
    JS_CFUNC_DEF("getRenderWidth",0,js_getRenderWidth),
    JS_CFUNC_DEF("getRenderHeight",0,js_getRenderHeight),
    JS_CFUNC_DEF("getMonitorCount",0,js_getMonitorCount),
    JS_CFUNC_DEF("getCurrentMonitor",0,js_getCurrentMonitor),
    JS_CFUNC_DEF("getMonitorPosition",1,js_getMonitorPosition),
    JS_CFUNC_DEF("getMonitorWidth",1,js_getMonitorWidth),
    JS_CFUNC_DEF("getMonitorHeight",1,js_getMonitorHeight),
    JS_CFUNC_DEF("getMonitorPhysicalWidth",1,js_getMonitorPhysicalWidth),
    JS_CFUNC_DEF("getMonitorPhysicalHeight",1,js_getMonitorPhysicalHeight),
    JS_CFUNC_DEF("getMonitorRefreshRate",1,js_getMonitorRefreshRate),
    JS_CFUNC_DEF("getWindowPosition",0,js_getWindowPosition),
    JS_CFUNC_DEF("getWindowScaleDPI",0,js_getWindowScaleDPI),
    JS_CFUNC_DEF("getMonitorName",1,js_getMonitorName),
    JS_CFUNC_DEF("setClipboardText",1,js_setClipboardText),
    JS_CFUNC_DEF("getClipboardText",0,js_getClipboardText),
    JS_CFUNC_DEF("enableEventWaiting",0,js_enableEventWaiting),
    JS_CFUNC_DEF("disableEventWaiting",0,js_disableEventWaiting),
    JS_CFUNC_DEF("showCursor",0,js_showCursor),
    JS_CFUNC_DEF("hideCursor",0,js_hideCursor),
    JS_CFUNC_DEF("isCursorHidden",0,js_isCursorHidden),
    JS_CFUNC_DEF("enableCursor",0,js_enableCursor),
    JS_CFUNC_DEF("disableCursor",0,js_disableCursor),
    JS_CFUNC_DEF("isCursorOnScreen",0,js_isCursorOnScreen),
    JS_CFUNC_DEF("clearBackground",1,js_clearBackground),
    JS_CFUNC_DEF("beginDrawing",0,js_beginDrawing),
    JS_CFUNC_DEF("endDrawing",0,js_endDrawing),
    JS_CFUNC_DEF("beginMode2D",1,js_beginMode2D),
    JS_CFUNC_DEF("endMode2D",0,js_endMode2D),
    JS_CFUNC_DEF("beginMode3D",1,js_beginMode3D),
    JS_CFUNC_DEF("endMode3D",0,js_endMode3D),
    JS_CFUNC_DEF("beginTextureMode",1,js_beginTextureMode),
    JS_CFUNC_DEF("endTextureMode",0,js_endTextureMode),
    JS_CFUNC_DEF("beginShaderMode",1,js_beginShaderMode),
    JS_CFUNC_DEF("endShaderMode",0,js_endShaderMode),
    JS_CFUNC_DEF("beginBlendMode",1,js_beginBlendMode),
    JS_CFUNC_DEF("endBlendMode",0,js_endBlendMode),
    JS_CFUNC_DEF("beginScissorMode",4,js_beginScissorMode),
    JS_CFUNC_DEF("endScissorMode",0,js_endScissorMode),
    JS_CFUNC_DEF("beginVrStereoMode",1,js_beginVrStereoMode),
    JS_CFUNC_DEF("endVrStereoMode",0,js_endVrStereoMode),
    JS_CFUNC_DEF("loadVrStereoConfig",1,js_loadVrStereoConfig),
    JS_CFUNC_DEF("unloadVrStereoConfig",1,js_unloadVrStereoConfig),
    JS_CFUNC_DEF("loadShader",2,js_loadShader),
    JS_CFUNC_DEF("loadShaderFromMemory",2,js_loadShaderFromMemory),
    JS_CFUNC_DEF("isShaderReady",1,js_isShaderReady),
    JS_CFUNC_DEF("getShaderLocation",2,js_getShaderLocation),
    JS_CFUNC_DEF("getShaderLocationAttrib",2,js_getShaderLocationAttrib),
    JS_CFUNC_DEF("setShaderValue",4,js_setShaderValue),
    JS_CFUNC_DEF("setShaderValueMatrix",3,js_setShaderValueMatrix),
    JS_CFUNC_DEF("setShaderValueTexture",3,js_setShaderValueTexture),
    JS_CFUNC_DEF("unloadShader",1,js_unloadShader),
    JS_CFUNC_DEF("getScreenToWorldRay",2,js_getScreenToWorldRay),
    JS_CFUNC_DEF("getScreenToWorldRayEx",4,js_getScreenToWorldRayEx),
    JS_CFUNC_DEF("getWorldToScreen",2,js_getWorldToScreen),
    JS_CFUNC_DEF("getWorldToScreenEx",4,js_getWorldToScreenEx),
    JS_CFUNC_DEF("getWorldToScreen2D",2,js_getWorldToScreen2D),
    JS_CFUNC_DEF("getScreenToWorld2D",2,js_getScreenToWorld2D),
    JS_CFUNC_DEF("getCameraMatrix",1,js_getCameraMatrix),
    JS_CFUNC_DEF("getCameraMatrix2D",1,js_getCameraMatrix2D),
    JS_CFUNC_DEF("setTargetFPS",1,js_setTargetFPS),
    JS_CFUNC_DEF("getFrameTime",0,js_getFrameTime),
    JS_CFUNC_DEF("getTime",0,js_getTime),
    JS_CFUNC_DEF("getFPS",0,js_getFPS),
    JS_CFUNC_DEF("setRandomSeed",1,js_setRandomSeed),
    JS_CFUNC_DEF("getRandomValue",2,js_getRandomValue),
    JS_CFUNC_DEF("loadRandomSequence",3,js_loadRandomSequence),
    JS_CFUNC_DEF("unloadRandomSequence",1,js_unloadRandomSequence),
    JS_CFUNC_DEF("takeScreenshot",1,js_takeScreenshot),
    JS_CFUNC_DEF("setConfigFlags",1,js_setConfigFlags),
    JS_CFUNC_DEF("openURL",1,js_openURL),
    JS_CFUNC_DEF("traceLog",2,js_traceLog),
    JS_CFUNC_DEF("setTraceLogLevel",1,js_setTraceLogLevel),
    JS_CFUNC_DEF("loadFileData",1,js_loadFileData),
    JS_CFUNC_DEF("saveFileData",3,js_saveFileData),
    JS_CFUNC_DEF("loadFileText",1,js_loadFileText),
    JS_CFUNC_DEF("saveFileText",2,js_saveFileText),
    JS_CFUNC_DEF("fileExists",1,js_fileExists),
    JS_CFUNC_DEF("directoryExists",1,js_directoryExists),
    JS_CFUNC_DEF("isFileExtension",2,js_isFileExtension),
    JS_CFUNC_DEF("getFileLength",1,js_getFileLength),
    JS_CFUNC_DEF("getFileExtension",1,js_getFileExtension),
    JS_CFUNC_DEF("getFileName",1,js_getFileName),
    JS_CFUNC_DEF("getFileNameWithoutExt",1,js_getFileNameWithoutExt),
    JS_CFUNC_DEF("getDirectoryPath",1,js_getDirectoryPath),
    JS_CFUNC_DEF("getPrevDirectoryPath",1,js_getPrevDirectoryPath),
    JS_CFUNC_DEF("getWorkingDirectory",0,js_getWorkingDirectory),
    JS_CFUNC_DEF("getApplicationDirectory",0,js_getApplicationDirectory),
    JS_CFUNC_DEF("makeDirectory",1,js_makeDirectory),
    JS_CFUNC_DEF("changeDirectory",1,js_changeDirectory),
    JS_CFUNC_DEF("isPathFile",1,js_isPathFile),
    JS_CFUNC_DEF("isFileNameValid",1,js_isFileNameValid),
    JS_CFUNC_DEF("loadDirectoryFiles",1,js_loadDirectoryFiles),
    JS_CFUNC_DEF("loadDirectoryFilesEx",3,js_loadDirectoryFilesEx),
    JS_CFUNC_DEF("isFileDropped",0,js_isFileDropped),
    JS_CFUNC_DEF("loadDroppedFiles",0,js_loadDroppedFiles),
    JS_CFUNC_DEF("getFileModTime",1,js_getFileModTime),
    JS_CFUNC_DEF("loadAutomationEventList",1,js_loadAutomationEventList),
    JS_CFUNC_DEF("unloadAutomationEventList",1,js_unloadAutomationEventList),
    JS_CFUNC_DEF("exportAutomationEventList",2,js_exportAutomationEventList),
    JS_CFUNC_DEF("setAutomationEventList",1,js_setAutomationEventList),
    JS_CFUNC_DEF("setAutomationEventBaseFrame",1,js_setAutomationEventBaseFrame),
    JS_CFUNC_DEF("startAutomationEventRecording",0,js_startAutomationEventRecording),
    JS_CFUNC_DEF("stopAutomationEventRecording",0,js_stopAutomationEventRecording),
    JS_CFUNC_DEF("playAutomationEvent",1,js_playAutomationEvent),
    JS_CFUNC_DEF("isKeyPressed",1,js_isKeyPressed),
    JS_CFUNC_DEF("isKeyPressedRepeat",1,js_isKeyPressedRepeat),
    JS_CFUNC_DEF("isKeyDown",1,js_isKeyDown),
    JS_CFUNC_DEF("isKeyReleased",1,js_isKeyReleased),
    JS_CFUNC_DEF("isKeyUp",1,js_isKeyUp),
    JS_CFUNC_DEF("getKeyPressed",0,js_getKeyPressed),
    JS_CFUNC_DEF("getCharPressed",0,js_getCharPressed),
    JS_CFUNC_DEF("setExitKey",1,js_setExitKey),
    JS_CFUNC_DEF("isGamepadAvailable",1,js_isGamepadAvailable),
    JS_CFUNC_DEF("getGamepadName",1,js_getGamepadName),
    JS_CFUNC_DEF("isGamepadButtonPressed",2,js_isGamepadButtonPressed),
    JS_CFUNC_DEF("isGamepadButtonDown",2,js_isGamepadButtonDown),
    JS_CFUNC_DEF("isGamepadButtonReleased",2,js_isGamepadButtonReleased),
    JS_CFUNC_DEF("isGamepadButtonUp",2,js_isGamepadButtonUp),
    JS_CFUNC_DEF("getGamepadButtonPressed",0,js_getGamepadButtonPressed),
    JS_CFUNC_DEF("getGamepadAxisCount",1,js_getGamepadAxisCount),
    JS_CFUNC_DEF("getGamepadAxisMovement",2,js_getGamepadAxisMovement),
    JS_CFUNC_DEF("setGamepadMappings",1,js_setGamepadMappings),
    JS_CFUNC_DEF("setGamepadVibration",3,js_setGamepadVibration),
    JS_CFUNC_DEF("isMouseButtonPressed",1,js_isMouseButtonPressed),
    JS_CFUNC_DEF("isMouseButtonDown",1,js_isMouseButtonDown),
    JS_CFUNC_DEF("isMouseButtonReleased",1,js_isMouseButtonReleased),
    JS_CFUNC_DEF("isMouseButtonUp",1,js_isMouseButtonUp),
    JS_CFUNC_DEF("getMouseX",0,js_getMouseX),
    JS_CFUNC_DEF("getMouseY",0,js_getMouseY),
    JS_CFUNC_DEF("getMousePosition",0,js_getMousePosition),
    JS_CFUNC_DEF("getMouseDelta",0,js_getMouseDelta),
    JS_CFUNC_DEF("setMousePosition",2,js_setMousePosition),
    JS_CFUNC_DEF("setMouseOffset",2,js_setMouseOffset),
    JS_CFUNC_DEF("setMouseScale",2,js_setMouseScale),
    JS_CFUNC_DEF("getMouseWheelMove",0,js_getMouseWheelMove),
    JS_CFUNC_DEF("getMouseWheelMoveV",0,js_getMouseWheelMoveV),
    JS_CFUNC_DEF("setMouseCursor",1,js_setMouseCursor),
    JS_CFUNC_DEF("getTouchX",0,js_getTouchX),
    JS_CFUNC_DEF("getTouchY",0,js_getTouchY),
    JS_CFUNC_DEF("getTouchPosition",1,js_getTouchPosition),
    JS_CFUNC_DEF("getTouchPointId",1,js_getTouchPointId),
    JS_CFUNC_DEF("getTouchPointCount",0,js_getTouchPointCount),
    JS_CFUNC_DEF("setGesturesEnabled",1,js_setGesturesEnabled),
    JS_CFUNC_DEF("isGestureDetected",1,js_isGestureDetected),
    JS_CFUNC_DEF("getGestureDetected",0,js_getGestureDetected),
    JS_CFUNC_DEF("getGestureHoldDuration",0,js_getGestureHoldDuration),
    JS_CFUNC_DEF("getGestureDragVector",0,js_getGestureDragVector),
    JS_CFUNC_DEF("getGestureDragAngle",0,js_getGestureDragAngle),
    JS_CFUNC_DEF("getGesturePinchVector",0,js_getGesturePinchVector),
    JS_CFUNC_DEF("getGesturePinchAngle",0,js_getGesturePinchAngle),
    JS_CFUNC_DEF("updateCamera",2,js_updateCamera),
    JS_CFUNC_DEF("updateCameraPro",4,js_updateCameraPro),
    JS_CFUNC_DEF("setShapesTexture",2,js_setShapesTexture),
    JS_CFUNC_DEF("getShapesTexture",0,js_getShapesTexture),
    JS_CFUNC_DEF("getShapesTextureRectangle",0,js_getShapesTextureRectangle),
    JS_CFUNC_DEF("drawPixel",3,js_drawPixel),
    JS_CFUNC_DEF("drawPixelV",2,js_drawPixelV),
    JS_CFUNC_DEF("drawLine",5,js_drawLine),
    JS_CFUNC_DEF("drawLineV",3,js_drawLineV),
    JS_CFUNC_DEF("drawLineEx",4,js_drawLineEx),
    JS_CFUNC_DEF("drawLineBezier",4,js_drawLineBezier),
    JS_CFUNC_DEF("drawCircle",4,js_drawCircle),
    JS_CFUNC_DEF("drawCircleSector",6,js_drawCircleSector),
    JS_CFUNC_DEF("drawCircleSectorLines",6,js_drawCircleSectorLines),
    JS_CFUNC_DEF("drawCircleGradient",5,js_drawCircleGradient),
    JS_CFUNC_DEF("drawCircleV",3,js_drawCircleV),
    JS_CFUNC_DEF("drawCircleLines",4,js_drawCircleLines),
    JS_CFUNC_DEF("drawCircleLinesV",3,js_drawCircleLinesV),
    JS_CFUNC_DEF("drawEllipse",5,js_drawEllipse),
    JS_CFUNC_DEF("drawEllipseLines",5,js_drawEllipseLines),
    JS_CFUNC_DEF("drawRing",7,js_drawRing),
    JS_CFUNC_DEF("drawRingLines",7,js_drawRingLines),
    JS_CFUNC_DEF("drawRectangle",5,js_drawRectangle),
    JS_CFUNC_DEF("drawRectangleV",3,js_drawRectangleV),
    JS_CFUNC_DEF("drawRectangleRec",2,js_drawRectangleRec),
    JS_CFUNC_DEF("drawRectanglePro",4,js_drawRectanglePro),
    JS_CFUNC_DEF("drawRectangleGradientV",6,js_drawRectangleGradientV),
    JS_CFUNC_DEF("drawRectangleGradientH",6,js_drawRectangleGradientH),
    JS_CFUNC_DEF("drawRectangleGradientEx",5,js_drawRectangleGradientEx),
    JS_CFUNC_DEF("drawRectangleLines",5,js_drawRectangleLines),
    JS_CFUNC_DEF("drawRectangleLinesEx",3,js_drawRectangleLinesEx),
    JS_CFUNC_DEF("drawRectangleRounded",4,js_drawRectangleRounded),
    JS_CFUNC_DEF("drawRectangleRoundedLines",4,js_drawRectangleRoundedLines),
    JS_CFUNC_DEF("drawRectangleRoundedLinesEx",5,js_drawRectangleRoundedLinesEx),
    JS_CFUNC_DEF("drawTriangle",4,js_drawTriangle),
    JS_CFUNC_DEF("drawTriangleLines",4,js_drawTriangleLines),
    JS_CFUNC_DEF("drawPoly",5,js_drawPoly),
    JS_CFUNC_DEF("drawPolyLines",5,js_drawPolyLines),
    JS_CFUNC_DEF("drawPolyLinesEx",6,js_drawPolyLinesEx),
    JS_CFUNC_DEF("drawSplineLinear",4,js_drawSplineLinear),
    JS_CFUNC_DEF("drawSplineBasis",4,js_drawSplineBasis),
    JS_CFUNC_DEF("drawSplineCatmullRom",4,js_drawSplineCatmullRom),
    JS_CFUNC_DEF("drawSplineBezierQuadratic",4,js_drawSplineBezierQuadratic),
    JS_CFUNC_DEF("drawSplineBezierCubic",4,js_drawSplineBezierCubic),
    JS_CFUNC_DEF("drawSplineSegmentLinear",4,js_drawSplineSegmentLinear),
    JS_CFUNC_DEF("drawSplineSegmentBasis",6,js_drawSplineSegmentBasis),
    JS_CFUNC_DEF("drawSplineSegmentCatmullRom",6,js_drawSplineSegmentCatmullRom),
    JS_CFUNC_DEF("drawSplineSegmentBezierQuadratic",5,js_drawSplineSegmentBezierQuadratic),
    JS_CFUNC_DEF("drawSplineSegmentBezierCubic",6,js_drawSplineSegmentBezierCubic),
    JS_CFUNC_DEF("getSplinePointLinear",3,js_getSplinePointLinear),
    JS_CFUNC_DEF("getSplinePointBasis",5,js_getSplinePointBasis),
    JS_CFUNC_DEF("getSplinePointCatmullRom",5,js_getSplinePointCatmullRom),
    JS_CFUNC_DEF("getSplinePointBezierQuad",4,js_getSplinePointBezierQuad),
    JS_CFUNC_DEF("getSplinePointBezierCubic",5,js_getSplinePointBezierCubic),
    JS_CFUNC_DEF("checkCollisionRecs",2,js_checkCollisionRecs),
    JS_CFUNC_DEF("checkCollisionCircles",4,js_checkCollisionCircles),
    JS_CFUNC_DEF("checkCollisionCircleRec",3,js_checkCollisionCircleRec),
    JS_CFUNC_DEF("checkCollisionPointRec",2,js_checkCollisionPointRec),
    JS_CFUNC_DEF("checkCollisionPointCircle",3,js_checkCollisionPointCircle),
    JS_CFUNC_DEF("checkCollisionPointTriangle",4,js_checkCollisionPointTriangle),
    JS_CFUNC_DEF("checkCollisionPointLine",4,js_checkCollisionPointLine),
    JS_CFUNC_DEF("checkCollisionCircleLine",4,js_checkCollisionCircleLine),
    JS_CFUNC_DEF("getCollisionRec",2,js_getCollisionRec),
    JS_CFUNC_DEF("loadImage",1,js_loadImage),
    JS_CFUNC_DEF("loadImageRaw",5,js_loadImageRaw),
    JS_CFUNC_DEF("loadImageSvg",3,js_loadImageSvg),
    JS_CFUNC_DEF("loadImageAnimFromMemory",4,js_loadImageAnimFromMemory),
    JS_CFUNC_DEF("loadImageFromMemory",3,js_loadImageFromMemory),
    JS_CFUNC_DEF("loadImageFromTexture",1,js_loadImageFromTexture),
    JS_CFUNC_DEF("loadImageFromScreen",0,js_loadImageFromScreen),
    JS_CFUNC_DEF("isImageReady",1,js_isImageReady),
    JS_CFUNC_DEF("unloadImage",1,js_unloadImage),
    JS_CFUNC_DEF("exportImage",2,js_exportImage),
    JS_CFUNC_DEF("exportImageToMemory",3,js_exportImageToMemory),
    JS_CFUNC_DEF("genImageColor",3,js_genImageColor),
    JS_CFUNC_DEF("genImageGradientLinear",5,js_genImageGradientLinear),
    JS_CFUNC_DEF("genImageGradientRadial",5,js_genImageGradientRadial),
    JS_CFUNC_DEF("genImageGradientSquare",5,js_genImageGradientSquare),
    JS_CFUNC_DEF("genImageChecked",6,js_genImageChecked),
    JS_CFUNC_DEF("genImageWhiteNoise",3,js_genImageWhiteNoise),
    JS_CFUNC_DEF("genImagePerlinNoise",5,js_genImagePerlinNoise),
    JS_CFUNC_DEF("genImageCellular",3,js_genImageCellular),
    JS_CFUNC_DEF("genImageText",3,js_genImageText),
    JS_CFUNC_DEF("imageCopy",1,js_imageCopy),
    JS_CFUNC_DEF("imageFromImage",2,js_imageFromImage),
    JS_CFUNC_DEF("imageFromChannel",2,js_imageFromChannel),
    JS_CFUNC_DEF("imageText",3,js_imageText),
    JS_CFUNC_DEF("imageTextEx",5,js_imageTextEx),
    JS_CFUNC_DEF("imageFormat",2,js_imageFormat),
    JS_CFUNC_DEF("imageToPOT",2,js_imageToPOT),
    JS_CFUNC_DEF("imageCrop",2,js_imageCrop),
    JS_CFUNC_DEF("imageAlphaCrop",2,js_imageAlphaCrop),
    JS_CFUNC_DEF("imageAlphaClear",3,js_imageAlphaClear),
    JS_CFUNC_DEF("imageAlphaMask",2,js_imageAlphaMask),
    JS_CFUNC_DEF("imageAlphaPremultiply",1,js_imageAlphaPremultiply),
    JS_CFUNC_DEF("imageBlurGaussian",2,js_imageBlurGaussian),
    JS_CFUNC_DEF("imageKernelConvolution",3,js_imageKernelConvolution),
    JS_CFUNC_DEF("imageResize",3,js_imageResize),
    JS_CFUNC_DEF("imageResizeNN",3,js_imageResizeNN),
    JS_CFUNC_DEF("imageResizeCanvas",6,js_imageResizeCanvas),
    JS_CFUNC_DEF("imageMipmaps",1,js_imageMipmaps),
    JS_CFUNC_DEF("imageDither",5,js_imageDither),
    JS_CFUNC_DEF("imageFlipVertical",1,js_imageFlipVertical),
    JS_CFUNC_DEF("imageFlipHorizontal",1,js_imageFlipHorizontal),
    JS_CFUNC_DEF("imageRotate",2,js_imageRotate),
    JS_CFUNC_DEF("imageRotateCW",1,js_imageRotateCW),
    JS_CFUNC_DEF("imageRotateCCW",1,js_imageRotateCCW),
    JS_CFUNC_DEF("imageColorTint",2,js_imageColorTint),
    JS_CFUNC_DEF("imageColorInvert",1,js_imageColorInvert),
    JS_CFUNC_DEF("imageColorGrayscale",1,js_imageColorGrayscale),
    JS_CFUNC_DEF("imageColorContrast",2,js_imageColorContrast),
    JS_CFUNC_DEF("imageColorBrightness",2,js_imageColorBrightness),
    JS_CFUNC_DEF("imageColorReplace",3,js_imageColorReplace),
    JS_CFUNC_DEF("loadImageColors",1,js_loadImageColors),
    JS_CFUNC_DEF("getImageAlphaBorder",2,js_getImageAlphaBorder),
    JS_CFUNC_DEF("getImageColor",3,js_getImageColor),
    JS_CFUNC_DEF("imageClearBackground",2,js_imageClearBackground),
    JS_CFUNC_DEF("imageDrawPixel",4,js_imageDrawPixel),
    JS_CFUNC_DEF("imageDrawPixelV",3,js_imageDrawPixelV),
    JS_CFUNC_DEF("imageDrawLine",6,js_imageDrawLine),
    JS_CFUNC_DEF("imageDrawLineV",4,js_imageDrawLineV),
    JS_CFUNC_DEF("imageDrawLineEx",5,js_imageDrawLineEx),
    JS_CFUNC_DEF("imageDrawCircle",5,js_imageDrawCircle),
    JS_CFUNC_DEF("imageDrawCircleV",4,js_imageDrawCircleV),
    JS_CFUNC_DEF("imageDrawCircleLines",5,js_imageDrawCircleLines),
    JS_CFUNC_DEF("imageDrawCircleLinesV",4,js_imageDrawCircleLinesV),
    JS_CFUNC_DEF("imageDrawRectangle",6,js_imageDrawRectangle),
    JS_CFUNC_DEF("imageDrawRectangleV",4,js_imageDrawRectangleV),
    JS_CFUNC_DEF("imageDrawRectangleRec",3,js_imageDrawRectangleRec),
    JS_CFUNC_DEF("imageDrawRectangleLines",4,js_imageDrawRectangleLines),
    JS_CFUNC_DEF("imageDrawTriangle",5,js_imageDrawTriangle),
    JS_CFUNC_DEF("imageDrawTriangleEx",7,js_imageDrawTriangleEx),
    JS_CFUNC_DEF("imageDrawTriangleLines",5,js_imageDrawTriangleLines),
    JS_CFUNC_DEF("imageDrawTriangleFan",4,js_imageDrawTriangleFan),
    JS_CFUNC_DEF("imageDrawTriangleStrip",4,js_imageDrawTriangleStrip),
    JS_CFUNC_DEF("imageDraw",5,js_imageDraw),
    JS_CFUNC_DEF("imageDrawText",6,js_imageDrawText),
    JS_CFUNC_DEF("imageDrawTextEx",7,js_imageDrawTextEx),
    JS_CFUNC_DEF("loadTexture",1,js_loadTexture),
    JS_CFUNC_DEF("loadTextureFromImage",1,js_loadTextureFromImage),
    JS_CFUNC_DEF("loadTextureCubemap",2,js_loadTextureCubemap),
    JS_CFUNC_DEF("loadRenderTexture",2,js_loadRenderTexture),
    JS_CFUNC_DEF("isTextureReady",1,js_isTextureReady),
    JS_CFUNC_DEF("unloadTexture",1,js_unloadTexture),
    JS_CFUNC_DEF("isRenderTextureReady",1,js_isRenderTextureReady),
    JS_CFUNC_DEF("unloadRenderTexture",1,js_unloadRenderTexture),
    JS_CFUNC_DEF("updateTexture",2,js_updateTexture),
    JS_CFUNC_DEF("updateTextureRec",3,js_updateTextureRec),
    JS_CFUNC_DEF("genTextureMipmaps",1,js_genTextureMipmaps),
    JS_CFUNC_DEF("setTextureFilter",2,js_setTextureFilter),
    JS_CFUNC_DEF("setTextureWrap",2,js_setTextureWrap),
    JS_CFUNC_DEF("drawTexture",4,js_drawTexture),
    JS_CFUNC_DEF("drawTextureV",3,js_drawTextureV),
    JS_CFUNC_DEF("drawTextureEx",5,js_drawTextureEx),
    JS_CFUNC_DEF("drawTextureRec",4,js_drawTextureRec),
    JS_CFUNC_DEF("drawTexturePro",6,js_drawTexturePro),
    JS_CFUNC_DEF("drawTextureNPatch",6,js_drawTextureNPatch),
    JS_CFUNC_DEF("colorIsEqual",2,js_colorIsEqual),
    JS_CFUNC_DEF("fade",2,js_fade),
    JS_CFUNC_DEF("colorToInt",1,js_colorToInt),
    JS_CFUNC_DEF("colorNormalize",1,js_colorNormalize),
    JS_CFUNC_DEF("colorFromNormalized",1,js_colorFromNormalized),
    JS_CFUNC_DEF("colorToHSV",1,js_colorToHSV),
    JS_CFUNC_DEF("colorFromHSV",3,js_colorFromHSV),
    JS_CFUNC_DEF("colorTint",2,js_colorTint),
    JS_CFUNC_DEF("colorBrightness",2,js_colorBrightness),
    JS_CFUNC_DEF("colorContrast",2,js_colorContrast),
    JS_CFUNC_DEF("colorAlpha",2,js_colorAlpha),
    JS_CFUNC_DEF("colorAlphaBlend",3,js_colorAlphaBlend),
    JS_CFUNC_DEF("colorLerp",3,js_colorLerp),
    JS_CFUNC_DEF("getColor",1,js_getColor),
    JS_CFUNC_DEF("getPixelDataSize",3,js_getPixelDataSize),
    JS_CFUNC_DEF("getFontDefault",0,js_getFontDefault),
    JS_CFUNC_DEF("loadFont",1,js_loadFont),
    JS_CFUNC_DEF("loadFontEx",4,js_loadFontEx),
    JS_CFUNC_DEF("loadFontFromImage",3,js_loadFontFromImage),
    JS_CFUNC_DEF("isFontReady",1,js_isFontReady),
    JS_CFUNC_DEF("unloadFont",1,js_unloadFont),
    JS_CFUNC_DEF("drawFPS",2,js_drawFPS),
    JS_CFUNC_DEF("drawText",5,js_drawText),
    JS_CFUNC_DEF("drawTextEx",6,js_drawTextEx),
    JS_CFUNC_DEF("drawTextPro",8,js_drawTextPro),
    JS_CFUNC_DEF("drawTextCodepoint",5,js_drawTextCodepoint),
    JS_CFUNC_DEF("setTextLineSpacing",1,js_setTextLineSpacing),
    JS_CFUNC_DEF("measureText",2,js_measureText),
    JS_CFUNC_DEF("measureTextEx",4,js_measureTextEx),
    JS_CFUNC_DEF("getGlyphIndex",2,js_getGlyphIndex),
    JS_CFUNC_DEF("getGlyphAtlasRec",2,js_getGlyphAtlasRec),
    JS_CFUNC_DEF("textCopy",2,js_textCopy),
    JS_CFUNC_DEF("textIsEqual",2,js_textIsEqual),
    JS_CFUNC_DEF("textLength",1,js_textLength),
    JS_CFUNC_DEF("textFormat",0,js_textFormat),
    JS_CFUNC_DEF("textSubtext",3,js_textSubtext),
    JS_CFUNC_DEF("textReplace",3,js_textReplace),
    JS_CFUNC_DEF("textInsert",3,js_textInsert),
    JS_CFUNC_DEF("textJoin",3,js_textJoin),
    JS_CFUNC_DEF("textSplit",3,js_textSplit),
    JS_CFUNC_DEF("textAppend",3,js_textAppend),
    JS_CFUNC_DEF("textFindIndex",2,js_textFindIndex),
    JS_CFUNC_DEF("textToUpper",1,js_textToUpper),
    JS_CFUNC_DEF("textToLower",1,js_textToLower),
    JS_CFUNC_DEF("textToPascal",1,js_textToPascal),
    JS_CFUNC_DEF("textToSnake",1,js_textToSnake),
    JS_CFUNC_DEF("textToCamel",1,js_textToCamel),
    JS_CFUNC_DEF("textToInteger",1,js_textToInteger),
    JS_CFUNC_DEF("textToFloat",1,js_textToFloat),
    JS_CFUNC_DEF("drawLine3D",3,js_drawLine3D),
    JS_CFUNC_DEF("drawPoint3D",2,js_drawPoint3D),
    JS_CFUNC_DEF("drawCircle3D",5,js_drawCircle3D),
    JS_CFUNC_DEF("drawTriangle3D",4,js_drawTriangle3D),
    JS_CFUNC_DEF("drawCube",5,js_drawCube),
    JS_CFUNC_DEF("drawCubeV",3,js_drawCubeV),
    JS_CFUNC_DEF("drawCubeWires",5,js_drawCubeWires),
    JS_CFUNC_DEF("drawCubeWiresV",3,js_drawCubeWiresV),
    JS_CFUNC_DEF("drawSphere",3,js_drawSphere),
    JS_CFUNC_DEF("drawSphereEx",5,js_drawSphereEx),
    JS_CFUNC_DEF("drawSphereWires",5,js_drawSphereWires),
    JS_CFUNC_DEF("drawCylinder",6,js_drawCylinder),
    JS_CFUNC_DEF("drawCylinderEx",6,js_drawCylinderEx),
    JS_CFUNC_DEF("drawCylinderWires",6,js_drawCylinderWires),
    JS_CFUNC_DEF("drawCylinderWiresEx",6,js_drawCylinderWiresEx),
    JS_CFUNC_DEF("drawCapsule",6,js_drawCapsule),
    JS_CFUNC_DEF("drawCapsuleWires",6,js_drawCapsuleWires),
    JS_CFUNC_DEF("drawPlane",3,js_drawPlane),
    JS_CFUNC_DEF("drawRay",2,js_drawRay),
    JS_CFUNC_DEF("drawGrid",2,js_drawGrid),
    JS_CFUNC_DEF("loadModel",1,js_loadModel),
    JS_CFUNC_DEF("loadModelFromMesh",1,js_loadModelFromMesh),
    JS_CFUNC_DEF("isModelReady",1,js_isModelReady),
    JS_CFUNC_DEF("unloadModel",1,js_unloadModel),
    JS_CFUNC_DEF("getModelBoundingBox",1,js_getModelBoundingBox),
    JS_CFUNC_DEF("drawModel",4,js_drawModel),
    JS_CFUNC_DEF("drawModelEx",6,js_drawModelEx),
    JS_CFUNC_DEF("drawModelWires",4,js_drawModelWires),
    JS_CFUNC_DEF("drawModelWiresEx",6,js_drawModelWiresEx),
    JS_CFUNC_DEF("drawModelPoints",4,js_drawModelPoints),
    JS_CFUNC_DEF("drawModelPointsEx",6,js_drawModelPointsEx),
    JS_CFUNC_DEF("drawBoundingBox",2,js_drawBoundingBox),
    JS_CFUNC_DEF("drawBillboard",5,js_drawBillboard),
    JS_CFUNC_DEF("drawBillboardRec",6,js_drawBillboardRec),
    JS_CFUNC_DEF("drawBillboardPro",9,js_drawBillboardPro),
    JS_CFUNC_DEF("uploadMesh",2,js_uploadMesh),
    JS_CFUNC_DEF("updateMeshBuffer",5,js_updateMeshBuffer),
    JS_CFUNC_DEF("unloadMesh",1,js_unloadMesh),
    JS_CFUNC_DEF("drawMesh",3,js_drawMesh),
    JS_CFUNC_DEF("drawMeshInstanced",4,js_drawMeshInstanced),
    JS_CFUNC_DEF("getMeshBoundingBox",1,js_getMeshBoundingBox),
    JS_CFUNC_DEF("genMeshTangents",1,js_genMeshTangents),
    JS_CFUNC_DEF("exportMesh",2,js_exportMesh),
    JS_CFUNC_DEF("exportMeshAsCode",2,js_exportMeshAsCode),
    JS_CFUNC_DEF("genMeshPoly",2,js_genMeshPoly),
    JS_CFUNC_DEF("genMeshPlane",4,js_genMeshPlane),
    JS_CFUNC_DEF("genMeshCube",3,js_genMeshCube),
    JS_CFUNC_DEF("genMeshSphere",3,js_genMeshSphere),
    JS_CFUNC_DEF("genMeshHemiSphere",3,js_genMeshHemiSphere),
    JS_CFUNC_DEF("genMeshCylinder",3,js_genMeshCylinder),
    JS_CFUNC_DEF("genMeshCone",3,js_genMeshCone),
    JS_CFUNC_DEF("genMeshTorus",4,js_genMeshTorus),
    JS_CFUNC_DEF("genMeshKnot",4,js_genMeshKnot),
    JS_CFUNC_DEF("genMeshHeightmap",2,js_genMeshHeightmap),
    JS_CFUNC_DEF("genMeshCubicmap",2,js_genMeshCubicmap),
    JS_CFUNC_DEF("loadMaterialDefault",0,js_loadMaterialDefault),
    JS_CFUNC_DEF("isMaterialReady",1,js_isMaterialReady),
    JS_CFUNC_DEF("unloadMaterial",1,js_unloadMaterial),
    JS_CFUNC_DEF("setMaterialTexture",3,js_setMaterialTexture),
    JS_CFUNC_DEF("setModelMeshMaterial",3,js_setModelMeshMaterial),
    JS_CFUNC_DEF("updateModelAnimationBoneMatrices",3,js_updateModelAnimationBoneMatrices),
    JS_CFUNC_DEF("checkCollisionSpheres",4,js_checkCollisionSpheres),
    JS_CFUNC_DEF("checkCollisionBoxes",2,js_checkCollisionBoxes),
    JS_CFUNC_DEF("checkCollisionBoxSphere",3,js_checkCollisionBoxSphere),
    JS_CFUNC_DEF("getRayCollisionSphere",3,js_getRayCollisionSphere),
    JS_CFUNC_DEF("getRayCollisionBox",2,js_getRayCollisionBox),
    JS_CFUNC_DEF("getRayCollisionMesh",3,js_getRayCollisionMesh),
    JS_CFUNC_DEF("getRayCollisionTriangle",4,js_getRayCollisionTriangle),
    JS_CFUNC_DEF("getRayCollisionQuad",5,js_getRayCollisionQuad),
    JS_CFUNC_DEF("initAudioDevice",0,js_initAudioDevice),
    JS_CFUNC_DEF("closeAudioDevice",0,js_closeAudioDevice),
    JS_CFUNC_DEF("isAudioDeviceReady",0,js_isAudioDeviceReady),
    JS_CFUNC_DEF("setMasterVolume",1,js_setMasterVolume),
    JS_CFUNC_DEF("getMasterVolume",0,js_getMasterVolume),
    JS_CFUNC_DEF("loadWave",1,js_loadWave),
    JS_CFUNC_DEF("loadWaveFromMemory",3,js_loadWaveFromMemory),
    JS_CFUNC_DEF("isWaveReady",1,js_isWaveReady),
    JS_CFUNC_DEF("loadSound",1,js_loadSound),
    JS_CFUNC_DEF("loadSoundFromWave",1,js_loadSoundFromWave),
    JS_CFUNC_DEF("loadSoundAlias",1,js_loadSoundAlias),
    JS_CFUNC_DEF("isSoundReady",1,js_isSoundReady),
    JS_CFUNC_DEF("updateSound",3,js_updateSound),
    JS_CFUNC_DEF("unloadWave",1,js_unloadWave),
    JS_CFUNC_DEF("unloadSound",1,js_unloadSound),
    JS_CFUNC_DEF("unloadSoundAlias",1,js_unloadSoundAlias),
    JS_CFUNC_DEF("exportWave",2,js_exportWave),
    JS_CFUNC_DEF("playSound",1,js_playSound),
    JS_CFUNC_DEF("stopSound",1,js_stopSound),
    JS_CFUNC_DEF("pauseSound",1,js_pauseSound),
    JS_CFUNC_DEF("resumeSound",1,js_resumeSound),
    JS_CFUNC_DEF("isSoundPlaying",1,js_isSoundPlaying),
    JS_CFUNC_DEF("setSoundVolume",2,js_setSoundVolume),
    JS_CFUNC_DEF("setSoundPitch",2,js_setSoundPitch),
    JS_CFUNC_DEF("setSoundPan",2,js_setSoundPan),
    JS_CFUNC_DEF("waveCopy",1,js_waveCopy),
    JS_CFUNC_DEF("waveCrop",3,js_waveCrop),
    JS_CFUNC_DEF("waveFormat",4,js_waveFormat),
    JS_CFUNC_DEF("loadMusicStream",1,js_loadMusicStream),
    JS_CFUNC_DEF("isMusicReady",1,js_isMusicReady),
    JS_CFUNC_DEF("unloadMusicStream",1,js_unloadMusicStream),
    JS_CFUNC_DEF("playMusicStream",1,js_playMusicStream),
    JS_CFUNC_DEF("isMusicStreamPlaying",1,js_isMusicStreamPlaying),
    JS_CFUNC_DEF("updateMusicStream",1,js_updateMusicStream),
    JS_CFUNC_DEF("stopMusicStream",1,js_stopMusicStream),
    JS_CFUNC_DEF("pauseMusicStream",1,js_pauseMusicStream),
    JS_CFUNC_DEF("resumeMusicStream",1,js_resumeMusicStream),
    JS_CFUNC_DEF("seekMusicStream",2,js_seekMusicStream),
    JS_CFUNC_DEF("setMusicVolume",2,js_setMusicVolume),
    JS_CFUNC_DEF("setMusicPitch",2,js_setMusicPitch),
    JS_CFUNC_DEF("setMusicPan",2,js_setMusicPan),
    JS_CFUNC_DEF("getMusicTimeLength",1,js_getMusicTimeLength),
    JS_CFUNC_DEF("getMusicTimePlayed",1,js_getMusicTimePlayed),
    JS_CFUNC_DEF("clamp",3,js_clamp),
    JS_CFUNC_DEF("lerp",3,js_lerp),
    JS_CFUNC_DEF("normalize",3,js_normalize),
    JS_CFUNC_DEF("remap",5,js_remap),
    JS_CFUNC_DEF("wrap",3,js_wrap),
    JS_CFUNC_DEF("floatEquals",2,js_floatEquals),
    JS_CFUNC_DEF("vector2Zero",0,js_vector2Zero),
    JS_CFUNC_DEF("vector2One",0,js_vector2One),
    JS_CFUNC_DEF("vector2Add",2,js_vector2Add),
    JS_CFUNC_DEF("vector2AddValue",2,js_vector2AddValue),
    JS_CFUNC_DEF("vector2Subtract",2,js_vector2Subtract),
    JS_CFUNC_DEF("vector2SubtractValue",2,js_vector2SubtractValue),
    JS_CFUNC_DEF("vector2Length",1,js_vector2Length),
    JS_CFUNC_DEF("vector2LengthSqr",1,js_vector2LengthSqr),
    JS_CFUNC_DEF("vector2DotProduct",2,js_vector2DotProduct),
    JS_CFUNC_DEF("vector2Distance",2,js_vector2Distance),
    JS_CFUNC_DEF("vector2DistanceSqr",2,js_vector2DistanceSqr),
    JS_CFUNC_DEF("vector2Angle",2,js_vector2Angle),
    JS_CFUNC_DEF("vector2LineAngle",2,js_vector2LineAngle),
    JS_CFUNC_DEF("vector2Scale",2,js_vector2Scale),
    JS_CFUNC_DEF("vector2Multiply",2,js_vector2Multiply),
    JS_CFUNC_DEF("vector2Negate",1,js_vector2Negate),
    JS_CFUNC_DEF("vector2Divide",2,js_vector2Divide),
    JS_CFUNC_DEF("vector2Normalize",1,js_vector2Normalize),
    JS_CFUNC_DEF("vector2Transform",2,js_vector2Transform),
    JS_CFUNC_DEF("vector2Lerp",3,js_vector2Lerp),
    JS_CFUNC_DEF("vector2Reflect",2,js_vector2Reflect),
    JS_CFUNC_DEF("vector2Min",2,js_vector2Min),
    JS_CFUNC_DEF("vector2Max",2,js_vector2Max),
    JS_CFUNC_DEF("vector2Rotate",2,js_vector2Rotate),
    JS_CFUNC_DEF("vector2MoveTowards",3,js_vector2MoveTowards),
    JS_CFUNC_DEF("vector2Invert",1,js_vector2Invert),
    JS_CFUNC_DEF("vector2Clamp",3,js_vector2Clamp),
    JS_CFUNC_DEF("vector2ClampValue",3,js_vector2ClampValue),
    JS_CFUNC_DEF("vector2Equals",2,js_vector2Equals),
    JS_CFUNC_DEF("vector2Refract",3,js_vector2Refract),
    JS_CFUNC_DEF("vector3Zero",0,js_vector3Zero),
    JS_CFUNC_DEF("vector3One",0,js_vector3One),
    JS_CFUNC_DEF("vector3Add",2,js_vector3Add),
    JS_CFUNC_DEF("vector3AddValue",2,js_vector3AddValue),
    JS_CFUNC_DEF("vector3Subtract",2,js_vector3Subtract),
    JS_CFUNC_DEF("vector3SubtractValue",2,js_vector3SubtractValue),
    JS_CFUNC_DEF("vector3Scale",2,js_vector3Scale),
    JS_CFUNC_DEF("vector3Multiply",2,js_vector3Multiply),
    JS_CFUNC_DEF("vector3CrossProduct",2,js_vector3CrossProduct),
    JS_CFUNC_DEF("vector3Perpendicular",1,js_vector3Perpendicular),
    JS_CFUNC_DEF("vector3Length",1,js_vector3Length),
    JS_CFUNC_DEF("vector3LengthSqr",1,js_vector3LengthSqr),
    JS_CFUNC_DEF("vector3DotProduct",2,js_vector3DotProduct),
    JS_CFUNC_DEF("vector3Distance",2,js_vector3Distance),
    JS_CFUNC_DEF("vector3DistanceSqr",2,js_vector3DistanceSqr),
    JS_CFUNC_DEF("vector3Angle",2,js_vector3Angle),
    JS_CFUNC_DEF("vector3Negate",1,js_vector3Negate),
    JS_CFUNC_DEF("vector3Divide",2,js_vector3Divide),
    JS_CFUNC_DEF("vector3Normalize",1,js_vector3Normalize),
    JS_CFUNC_DEF("vector3Project",2,js_vector3Project),
    JS_CFUNC_DEF("vector3Reject",2,js_vector3Reject),
    JS_CFUNC_DEF("vector3Transform",2,js_vector3Transform),
    JS_CFUNC_DEF("vector3RotateByQuaternion",2,js_vector3RotateByQuaternion),
    JS_CFUNC_DEF("vector3RotateByAxisAngle",3,js_vector3RotateByAxisAngle),
    JS_CFUNC_DEF("vector3MoveTowards",3,js_vector3MoveTowards),
    JS_CFUNC_DEF("vector3Lerp",3,js_vector3Lerp),
    JS_CFUNC_DEF("vector3CubicHermite",5,js_vector3CubicHermite),
    JS_CFUNC_DEF("vector3Reflect",2,js_vector3Reflect),
    JS_CFUNC_DEF("vector3Min",2,js_vector3Min),
    JS_CFUNC_DEF("vector3Max",2,js_vector3Max),
    JS_CFUNC_DEF("vector3Barycenter",4,js_vector3Barycenter),
    JS_CFUNC_DEF("vector3Unproject",3,js_vector3Unproject),
    JS_CFUNC_DEF("vector3Invert",1,js_vector3Invert),
    JS_CFUNC_DEF("vector3Clamp",3,js_vector3Clamp),
    JS_CFUNC_DEF("vector3ClampValue",3,js_vector3ClampValue),
    JS_CFUNC_DEF("vector3Equals",2,js_vector3Equals),
    JS_CFUNC_DEF("vector3Refract",3,js_vector3Refract),
    JS_CFUNC_DEF("vector4Distance",2,js_vector4Distance),
    JS_CFUNC_DEF("vector4DistanceSqr",2,js_vector4DistanceSqr),
    JS_CFUNC_DEF("vector4Multiply",2,js_vector4Multiply),
    JS_CFUNC_DEF("vector4Negate",1,js_vector4Negate),
    JS_CFUNC_DEF("vector4Divide",2,js_vector4Divide),
    JS_CFUNC_DEF("vector4Normalize",1,js_vector4Normalize),
    JS_CFUNC_DEF("vector4Min",2,js_vector4Min),
    JS_CFUNC_DEF("vector4Max",2,js_vector4Max),
    JS_CFUNC_DEF("vector4Lerp",3,js_vector4Lerp),
    JS_CFUNC_DEF("vector4MoveTowards",3,js_vector4MoveTowards),
    JS_CFUNC_DEF("vector4Invert",1,js_vector4Invert),
    JS_CFUNC_DEF("vector4Equals",2,js_vector4Equals),
    JS_CFUNC_DEF("matrixDeterminant",1,js_matrixDeterminant),
    JS_CFUNC_DEF("matrixTrace",1,js_matrixTrace),
    JS_CFUNC_DEF("matrixTranspose",1,js_matrixTranspose),
    JS_CFUNC_DEF("matrixInvert",1,js_matrixInvert),
    JS_CFUNC_DEF("matrixIdentity",0,js_matrixIdentity),
    JS_CFUNC_DEF("matrixAdd",2,js_matrixAdd),
    JS_CFUNC_DEF("matrixSubtract",2,js_matrixSubtract),
    JS_CFUNC_DEF("matrixMultiply",2,js_matrixMultiply),
    JS_CFUNC_DEF("matrixTranslate",3,js_matrixTranslate),
    JS_CFUNC_DEF("matrixRotate",2,js_matrixRotate),
    JS_CFUNC_DEF("matrixRotateX",1,js_matrixRotateX),
    JS_CFUNC_DEF("matrixRotateY",1,js_matrixRotateY),
    JS_CFUNC_DEF("matrixRotateZ",1,js_matrixRotateZ),
    JS_CFUNC_DEF("matrixRotateXYZ",1,js_matrixRotateXYZ),
    JS_CFUNC_DEF("matrixRotateZYX",1,js_matrixRotateZYX),
    JS_CFUNC_DEF("matrixScale",3,js_matrixScale),
    JS_CFUNC_DEF("matrixFrustum",6,js_matrixFrustum),
    JS_CFUNC_DEF("matrixPerspective",4,js_matrixPerspective),
    JS_CFUNC_DEF("matrixOrtho",6,js_matrixOrtho),
    JS_CFUNC_DEF("matrixLookAt",3,js_matrixLookAt),
    JS_CFUNC_DEF("quaternionAdd",2,js_quaternionAdd),
    JS_CFUNC_DEF("quaternionAddValue",2,js_quaternionAddValue),
    JS_CFUNC_DEF("quaternionSubtract",2,js_quaternionSubtract),
    JS_CFUNC_DEF("quaternionSubtractValue",2,js_quaternionSubtractValue),
    JS_CFUNC_DEF("quaternionIdentity",0,js_quaternionIdentity),
    JS_CFUNC_DEF("quaternionLength",1,js_quaternionLength),
    JS_CFUNC_DEF("quaternionNormalize",1,js_quaternionNormalize),
    JS_CFUNC_DEF("quaternionInvert",1,js_quaternionInvert),
    JS_CFUNC_DEF("quaternionMultiply",2,js_quaternionMultiply),
    JS_CFUNC_DEF("quaternionScale",2,js_quaternionScale),
    JS_CFUNC_DEF("quaternionDivide",2,js_quaternionDivide),
    JS_CFUNC_DEF("quaternionLerp",3,js_quaternionLerp),
    JS_CFUNC_DEF("quaternionNlerp",3,js_quaternionNlerp),
    JS_CFUNC_DEF("quaternionSlerp",3,js_quaternionSlerp),
    JS_CFUNC_DEF("quaternionCubicHermiteSpline",5,js_quaternionCubicHermiteSpline),
    JS_CFUNC_DEF("quaternionFromVector3ToVector3",2,js_quaternionFromVector3ToVector3),
    JS_CFUNC_DEF("quaternionFromMatrix",1,js_quaternionFromMatrix),
    JS_CFUNC_DEF("quaternionToMatrix",1,js_quaternionToMatrix),
    JS_CFUNC_DEF("quaternionFromAxisAngle",2,js_quaternionFromAxisAngle),
    JS_CFUNC_DEF("quaternionFromEuler",3,js_quaternionFromEuler),
    JS_CFUNC_DEF("quaternionToEuler",1,js_quaternionToEuler),
    JS_CFUNC_DEF("quaternionTransform",2,js_quaternionTransform),
    JS_CFUNC_DEF("quaternionEquals",2,js_quaternionEquals),
    JS_CFUNC_DEF("matrixDecompose",4,js_matrixDecompose),
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
    JS_CFUNC_DEF("guiEnable",0,js_guiEnable),
    JS_CFUNC_DEF("guiDisable",0,js_guiDisable),
    JS_CFUNC_DEF("guiLock",0,js_guiLock),
    JS_CFUNC_DEF("guiUnlock",0,js_guiUnlock),
    JS_CFUNC_DEF("guiIsLocked",0,js_guiIsLocked),
    JS_CFUNC_DEF("guiSetAlpha",1,js_guiSetAlpha),
    JS_CFUNC_DEF("guiSetState",1,js_guiSetState),
    JS_CFUNC_DEF("guiGetState",0,js_guiGetState),
    JS_CFUNC_DEF("guiSetFont",1,js_guiSetFont),
    JS_CFUNC_DEF("guiGetFont",0,js_guiGetFont),
    JS_CFUNC_DEF("guiSetStyle",3,js_guiSetStyle),
    JS_CFUNC_DEF("guiGetStyle",2,js_guiGetStyle),
    JS_CFUNC_DEF("guiLoadStyle",1,js_guiLoadStyle),
    JS_CFUNC_DEF("guiLoadStyleDefault",0,js_guiLoadStyleDefault),
    JS_CFUNC_DEF("guiEnableTooltip",0,js_guiEnableTooltip),
    JS_CFUNC_DEF("guiDisableTooltip",0,js_guiDisableTooltip),
    JS_CFUNC_DEF("guiSetTooltip",1,js_guiSetTooltip),
    JS_CFUNC_DEF("guiIconText",2,js_guiIconText),
    JS_CFUNC_DEF("guiSetIconScale",1,js_guiSetIconScale),
    JS_CFUNC_DEF("guiDrawIcon",5,js_guiDrawIcon),
    JS_CFUNC_DEF("guiWindowBox",2,js_guiWindowBox),
    JS_CFUNC_DEF("guiGroupBox",2,js_guiGroupBox),
    JS_CFUNC_DEF("guiLine",2,js_guiLine),
    JS_CFUNC_DEF("guiPanel",2,js_guiPanel),
    JS_CFUNC_DEF("guiScrollPanel",5,js_guiScrollPanel),
    JS_CFUNC_DEF("guiLabel",2,js_guiLabel),
    JS_CFUNC_DEF("guiButton",2,js_guiButton),
    JS_CFUNC_DEF("guiLabelButton",2,js_guiLabelButton),
    JS_CFUNC_DEF("guiToggle",3,js_guiToggle),
    JS_CFUNC_DEF("guiToggleGroup",3,js_guiToggleGroup),
    JS_CFUNC_DEF("guiToggleSlider",3,js_guiToggleSlider),
    JS_CFUNC_DEF("guiCheckBox",3,js_guiCheckBox),
    JS_CFUNC_DEF("guiComboBox",3,js_guiComboBox),
    JS_CFUNC_DEF("guiDropdownBox",4,js_guiDropdownBox),
    JS_CFUNC_DEF("guiSpinner",6,js_guiSpinner),
    JS_CFUNC_DEF("guiValueBox",6,js_guiValueBox),
    JS_CFUNC_DEF("guiValueBoxFloat",5,js_guiValueBoxFloat),
    JS_CFUNC_DEF("guiTextBox",3,js_guiTextBox),
    JS_CFUNC_DEF("guiSlider",6,js_guiSlider),
    JS_CFUNC_DEF("guiSliderBar",6,js_guiSliderBar),
    JS_CFUNC_DEF("guiProgressBar",6,js_guiProgressBar),
    JS_CFUNC_DEF("guiStatusBar",2,js_guiStatusBar),
    JS_CFUNC_DEF("guiDummyRec",2,js_guiDummyRec),
    JS_CFUNC_DEF("guiGrid",5,js_guiGrid),
    JS_CFUNC_DEF("guiListView",4,js_guiListView),
    JS_CFUNC_DEF("guiMessageBox",4,js_guiMessageBox),
    JS_CFUNC_DEF("guiTextInputBox",6,js_guiTextInputBox),
    JS_CFUNC_DEF("guiColorPicker",3,js_guiColorPicker),
    JS_CFUNC_DEF("guiColorPanel",3,js_guiColorPanel),
    JS_CFUNC_DEF("guiColorBarAlpha",3,js_guiColorBarAlpha),
    JS_CFUNC_DEF("guiColorBarHue",3,js_guiColorBarHue),
    JS_CFUNC_DEF("guiColorPickerHSV",3,js_guiColorPickerHSV),
    JS_CFUNC_DEF("guiColorPanelHSV",3,js_guiColorPanelHSV),
    JS_CFUNC_DEF("createLight",5,js_createLight),
    JS_CFUNC_DEF("updateLightValues",2,js_updateLightValues),
    JS_CFUNC_DEF("easeLinearNone",4,js_easeLinearNone),
    JS_CFUNC_DEF("easeLinearIn",4,js_easeLinearIn),
    JS_CFUNC_DEF("easeLinearOut",4,js_easeLinearOut),
    JS_CFUNC_DEF("easeLinearInOut",4,js_easeLinearInOut),
    JS_CFUNC_DEF("easeSineIn",4,js_easeSineIn),
    JS_CFUNC_DEF("easeSineOut",4,js_easeSineOut),
    JS_CFUNC_DEF("easeSineInOut",4,js_easeSineInOut),
    JS_CFUNC_DEF("easeCircIn",4,js_easeCircIn),
    JS_CFUNC_DEF("easeCircOut",4,js_easeCircOut),
    JS_CFUNC_DEF("easeCircInOut",4,js_easeCircInOut),
    JS_CFUNC_DEF("easeCubicIn",4,js_easeCubicIn),
    JS_CFUNC_DEF("easeCubicOut",4,js_easeCubicOut),
    JS_CFUNC_DEF("easeCubicInOut",4,js_easeCubicInOut),
    JS_CFUNC_DEF("easeQuadIn",4,js_easeQuadIn),
    JS_CFUNC_DEF("easeQuadOut",4,js_easeQuadOut),
    JS_CFUNC_DEF("easeQuadInOut",4,js_easeQuadInOut),
    JS_CFUNC_DEF("easeExpoIn",4,js_easeExpoIn),
    JS_CFUNC_DEF("easeExpoOut",4,js_easeExpoOut),
    JS_CFUNC_DEF("easeExpoInOut",4,js_easeExpoInOut),
    JS_CFUNC_DEF("easeBackIn",4,js_easeBackIn),
    JS_CFUNC_DEF("easeBounceOut",4,js_easeBounceOut),
    JS_CFUNC_DEF("easeBounceInOut",4,js_easeBounceInOut),
    JS_CFUNC_DEF("easeElasticIn",4,js_easeElasticIn),
    JS_CFUNC_DEF("getDefaultLightmapperConfig",0,js_getDefaultLightmapperConfig),
    JS_CFUNC_DEF("loadLightmapper",4,js_loadLightmapper),
    JS_CFUNC_DEF("loadMaterialLightmapper",2,js_loadMaterialLightmapper),
    JS_CFUNC_DEF("unloadLightmapper",1,js_unloadLightmapper),
    JS_CFUNC_DEF("beginLightmap",0,js_beginLightmap),
    JS_CFUNC_DEF("endLightmap",0,js_endLightmap),
    JS_CFUNC_DEF("beginLightmapFragment",1,js_beginLightmapFragment),
    JS_CFUNC_DEF("endLightmapFragment",1,js_endLightmapFragment),
    JS_CFUNC_DEF("loadImageFromLightmapper",1,js_loadImageFromLightmapper),
    JS_CFUNC_DEF("setModelMaterial",3,js_setModelMaterial),
    JS_CFUNC_DEF("getModelMaterial",2,js_getModelMaterial),
    JS_CFUNC_DEF("getModelMesh",2,js_getModelMesh),
    JS_CFUNC_DEF("setShaderLocation",3,js_setShaderLocation),
    JS_CFUNC_DEF("imageReadPixel",3,js_imageReadPixel),
    JS_CFUNC_DEF("meshCopy",1,js_meshCopy),
    JS_CFUNC_DEF("meshMerge",2,js_meshMerge),
};

static int js_raylib_core_init(JSContext * ctx, JSModuleDef * m) {
    JS_SetModuleExportList(ctx, m,js_raylib_core_funcs,countof(js_raylib_core_funcs));
    JS_SetModuleExport(ctx, m, "DEG2RAD", JS_NewFloat64(ctx, DEG2RAD));
    JS_SetModuleExport(ctx, m, "RAD2DEG", JS_NewFloat64(ctx, RAD2DEG));
    js_declare_Vector2(ctx, m);
    JSValue Vector2_constr = JS_NewCFunction2(ctx, js_Vector2_constructor,"Vector2)", 2, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "Vector2", Vector2_constr);
    js_declare_Vector3(ctx, m);
    JSValue Vector3_constr = JS_NewCFunction2(ctx, js_Vector3_constructor,"Vector3)", 3, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "Vector3", Vector3_constr);
    js_declare_Vector4(ctx, m);
    JSValue Vector4_constr = JS_NewCFunction2(ctx, js_Vector4_constructor,"Vector4)", 4, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "Vector4", Vector4_constr);
    js_declare_Matrix(ctx, m);
    js_declare_Color(ctx, m);
    JSValue Color_constr = JS_NewCFunction2(ctx, js_Color_constructor,"Color)", 4, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "Color", Color_constr);
    js_declare_Rectangle(ctx, m);
    JSValue Rectangle_constr = JS_NewCFunction2(ctx, js_Rectangle_constructor,"Rectangle)", 4, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "Rectangle", Rectangle_constr);
    js_declare_Image(ctx, m);
    JSValue Image_constr = JS_NewCFunction2(ctx, js_Image_constructor,"Image)", 5, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "Image", Image_constr);
    js_declare_Texture(ctx, m);
    js_declare_RenderTexture(ctx, m);
    js_declare_NPatchInfo(ctx, m);
    JSValue NPatchInfo_constr = JS_NewCFunction2(ctx, js_NPatchInfo_constructor,"NPatchInfo)", 6, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "NPatchInfo", NPatchInfo_constr);
    js_declare_GlyphInfo(ctx, m);
    js_declare_Font(ctx, m);
    js_declare_Camera3D(ctx, m);
    JSValue Camera3D_constr = JS_NewCFunction2(ctx, js_Camera3D_constructor,"Camera3D)", 5, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "Camera3D", Camera3D_constr);
    js_declare_Camera2D(ctx, m);
    JSValue Camera2D_constr = JS_NewCFunction2(ctx, js_Camera2D_constructor,"Camera2D)", 4, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "Camera2D", Camera2D_constr);
    js_declare_Mesh(ctx, m);
    JSValue Mesh_constr = JS_NewCFunction2(ctx, js_Mesh_constructor,"Mesh)", 17, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "Mesh", Mesh_constr);
    js_declare_Shader(ctx, m);
    js_declare_MaterialMap(ctx, m);
    js_declare_Material(ctx, m);
    js_declare_Transform(ctx, m);
    js_declare_BoneInfo(ctx, m);
    js_declare_Model(ctx, m);
    js_declare_ModelAnimation(ctx, m);
    js_declare_Ray(ctx, m);
    JSValue Ray_constr = JS_NewCFunction2(ctx, js_Ray_constructor,"Ray)", 2, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "Ray", Ray_constr);
    js_declare_RayCollision(ctx, m);
    js_declare_BoundingBox(ctx, m);
    JSValue BoundingBox_constr = JS_NewCFunction2(ctx, js_BoundingBox_constructor,"BoundingBox)", 2, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "BoundingBox", BoundingBox_constr);
    js_declare_Wave(ctx, m);
    js_declare_AudioStream(ctx, m);
    js_declare_Sound(ctx, m);
    js_declare_Music(ctx, m);
    js_declare_VrDeviceInfo(ctx, m);
    JSValue VrDeviceInfo_constr = JS_NewCFunction2(ctx, js_VrDeviceInfo_constructor,"VrDeviceInfo)", 9, JS_CFUNC_constructor_or_func, 0);
    JS_SetModuleExport(ctx, m, "VrDeviceInfo", VrDeviceInfo_constr);
    js_declare_VrStereoConfig(ctx, m);
    js_declare_FilePathList(ctx, m);
    js_declare_AutomationEvent(ctx, m);
    js_declare_AutomationEventList(ctx, m);
    js_declare_Light(ctx, m);
    js_declare_Lightmapper(ctx, m);
    js_declare_LightmapperConfig(ctx, m);
    Color LIGHTGRAY_struct = { 200, 200, 200, 255 };
    Color* LIGHTGRAY_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *LIGHTGRAY_js_ptr = LIGHTGRAY_struct;
    JSValue LIGHTGRAY_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(LIGHTGRAY_js, LIGHTGRAY_js_ptr);
    JS_SetModuleExport(ctx, m, "LIGHTGRAY", LIGHTGRAY_js);
    Color GRAY_struct = { 130, 130, 130, 255 };
    Color* GRAY_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *GRAY_js_ptr = GRAY_struct;
    JSValue GRAY_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(GRAY_js, GRAY_js_ptr);
    JS_SetModuleExport(ctx, m, "GRAY", GRAY_js);
    Color DARKGRAY_struct = { 80, 80, 80, 255 };
    Color* DARKGRAY_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *DARKGRAY_js_ptr = DARKGRAY_struct;
    JSValue DARKGRAY_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(DARKGRAY_js, DARKGRAY_js_ptr);
    JS_SetModuleExport(ctx, m, "DARKGRAY", DARKGRAY_js);
    Color YELLOW_struct = { 253, 249, 0, 255 };
    Color* YELLOW_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *YELLOW_js_ptr = YELLOW_struct;
    JSValue YELLOW_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(YELLOW_js, YELLOW_js_ptr);
    JS_SetModuleExport(ctx, m, "YELLOW", YELLOW_js);
    Color GOLD_struct = { 255, 203, 0, 255 };
    Color* GOLD_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *GOLD_js_ptr = GOLD_struct;
    JSValue GOLD_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(GOLD_js, GOLD_js_ptr);
    JS_SetModuleExport(ctx, m, "GOLD", GOLD_js);
    Color ORANGE_struct = { 255, 161, 0, 255 };
    Color* ORANGE_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *ORANGE_js_ptr = ORANGE_struct;
    JSValue ORANGE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ORANGE_js, ORANGE_js_ptr);
    JS_SetModuleExport(ctx, m, "ORANGE", ORANGE_js);
    Color PINK_struct = { 255, 109, 194, 255 };
    Color* PINK_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *PINK_js_ptr = PINK_struct;
    JSValue PINK_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(PINK_js, PINK_js_ptr);
    JS_SetModuleExport(ctx, m, "PINK", PINK_js);
    Color RED_struct = { 230, 41, 55, 255 };
    Color* RED_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *RED_js_ptr = RED_struct;
    JSValue RED_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(RED_js, RED_js_ptr);
    JS_SetModuleExport(ctx, m, "RED", RED_js);
    Color MAROON_struct = { 190, 33, 55, 255 };
    Color* MAROON_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *MAROON_js_ptr = MAROON_struct;
    JSValue MAROON_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(MAROON_js, MAROON_js_ptr);
    JS_SetModuleExport(ctx, m, "MAROON", MAROON_js);
    Color GREEN_struct = { 0, 228, 48, 255 };
    Color* GREEN_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *GREEN_js_ptr = GREEN_struct;
    JSValue GREEN_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(GREEN_js, GREEN_js_ptr);
    JS_SetModuleExport(ctx, m, "GREEN", GREEN_js);
    Color LIME_struct = { 0, 158, 47, 255 };
    Color* LIME_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *LIME_js_ptr = LIME_struct;
    JSValue LIME_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(LIME_js, LIME_js_ptr);
    JS_SetModuleExport(ctx, m, "LIME", LIME_js);
    Color DARKGREEN_struct = { 0, 117, 44, 255 };
    Color* DARKGREEN_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *DARKGREEN_js_ptr = DARKGREEN_struct;
    JSValue DARKGREEN_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(DARKGREEN_js, DARKGREEN_js_ptr);
    JS_SetModuleExport(ctx, m, "DARKGREEN", DARKGREEN_js);
    Color SKYBLUE_struct = { 102, 191, 255, 255 };
    Color* SKYBLUE_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *SKYBLUE_js_ptr = SKYBLUE_struct;
    JSValue SKYBLUE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(SKYBLUE_js, SKYBLUE_js_ptr);
    JS_SetModuleExport(ctx, m, "SKYBLUE", SKYBLUE_js);
    Color BLUE_struct = { 0, 121, 241, 255 };
    Color* BLUE_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *BLUE_js_ptr = BLUE_struct;
    JSValue BLUE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(BLUE_js, BLUE_js_ptr);
    JS_SetModuleExport(ctx, m, "BLUE", BLUE_js);
    Color DARKBLUE_struct = { 0, 82, 172, 255 };
    Color* DARKBLUE_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *DARKBLUE_js_ptr = DARKBLUE_struct;
    JSValue DARKBLUE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(DARKBLUE_js, DARKBLUE_js_ptr);
    JS_SetModuleExport(ctx, m, "DARKBLUE", DARKBLUE_js);
    Color PURPLE_struct = { 200, 122, 255, 255 };
    Color* PURPLE_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *PURPLE_js_ptr = PURPLE_struct;
    JSValue PURPLE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(PURPLE_js, PURPLE_js_ptr);
    JS_SetModuleExport(ctx, m, "PURPLE", PURPLE_js);
    Color VIOLET_struct = { 135, 60, 190, 255 };
    Color* VIOLET_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *VIOLET_js_ptr = VIOLET_struct;
    JSValue VIOLET_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(VIOLET_js, VIOLET_js_ptr);
    JS_SetModuleExport(ctx, m, "VIOLET", VIOLET_js);
    Color DARKPURPLE_struct = { 112, 31, 126, 255 };
    Color* DARKPURPLE_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *DARKPURPLE_js_ptr = DARKPURPLE_struct;
    JSValue DARKPURPLE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(DARKPURPLE_js, DARKPURPLE_js_ptr);
    JS_SetModuleExport(ctx, m, "DARKPURPLE", DARKPURPLE_js);
    Color BEIGE_struct = { 211, 176, 131, 255 };
    Color* BEIGE_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *BEIGE_js_ptr = BEIGE_struct;
    JSValue BEIGE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(BEIGE_js, BEIGE_js_ptr);
    JS_SetModuleExport(ctx, m, "BEIGE", BEIGE_js);
    Color BROWN_struct = { 127, 106, 79, 255 };
    Color* BROWN_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *BROWN_js_ptr = BROWN_struct;
    JSValue BROWN_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(BROWN_js, BROWN_js_ptr);
    JS_SetModuleExport(ctx, m, "BROWN", BROWN_js);
    Color DARKBROWN_struct = { 76, 63, 47, 255 };
    Color* DARKBROWN_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *DARKBROWN_js_ptr = DARKBROWN_struct;
    JSValue DARKBROWN_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(DARKBROWN_js, DARKBROWN_js_ptr);
    JS_SetModuleExport(ctx, m, "DARKBROWN", DARKBROWN_js);
    Color WHITE_struct = { 255, 255, 255, 255 };
    Color* WHITE_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *WHITE_js_ptr = WHITE_struct;
    JSValue WHITE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(WHITE_js, WHITE_js_ptr);
    JS_SetModuleExport(ctx, m, "WHITE", WHITE_js);
    Color BLACK_struct = { 0, 0, 0, 255 };
    Color* BLACK_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *BLACK_js_ptr = BLACK_struct;
    JSValue BLACK_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(BLACK_js, BLACK_js_ptr);
    JS_SetModuleExport(ctx, m, "BLACK", BLACK_js);
    Color BLANK_struct = { 0, 0, 0, 0 };
    Color* BLANK_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *BLANK_js_ptr = BLANK_struct;
    JSValue BLANK_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(BLANK_js, BLANK_js_ptr);
    JS_SetModuleExport(ctx, m, "BLANK", BLANK_js);
    Color MAGENTA_struct = { 255, 0, 255, 255 };
    Color* MAGENTA_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *MAGENTA_js_ptr = MAGENTA_struct;
    JSValue MAGENTA_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(MAGENTA_js, MAGENTA_js_ptr);
    JS_SetModuleExport(ctx, m, "MAGENTA", MAGENTA_js);
    Color RAYWHITE_struct = { 245, 245, 245, 255 };
    Color* RAYWHITE_js_ptr = (Color*)js_malloc(ctx, sizeof(Color));
    *RAYWHITE_js_ptr = RAYWHITE_struct;
    JSValue RAYWHITE_js = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(RAYWHITE_js, RAYWHITE_js_ptr);
    JS_SetModuleExport(ctx, m, "RAYWHITE", RAYWHITE_js);
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
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_FLOAT", JS_NewInt32(ctx, SHADER_UNIFORM_FLOAT));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_VEC2", JS_NewInt32(ctx, SHADER_UNIFORM_VEC2));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_VEC3", JS_NewInt32(ctx, SHADER_UNIFORM_VEC3));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_VEC4", JS_NewInt32(ctx, SHADER_UNIFORM_VEC4));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_INT", JS_NewInt32(ctx, SHADER_UNIFORM_INT));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_IVEC2", JS_NewInt32(ctx, SHADER_UNIFORM_IVEC2));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_IVEC3", JS_NewInt32(ctx, SHADER_UNIFORM_IVEC3));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_IVEC4", JS_NewInt32(ctx, SHADER_UNIFORM_IVEC4));
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
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_PANORAMA", JS_NewInt32(ctx, CUBEMAP_LAYOUT_PANORAMA));
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
    JS_SetModuleExport(ctx, m, "STATE_NORMAL", JS_NewInt32(ctx, STATE_NORMAL));
    JS_SetModuleExport(ctx, m, "STATE_FOCUSED", JS_NewInt32(ctx, STATE_FOCUSED));
    JS_SetModuleExport(ctx, m, "STATE_PRESSED", JS_NewInt32(ctx, STATE_PRESSED));
    JS_SetModuleExport(ctx, m, "STATE_DISABLED", JS_NewInt32(ctx, STATE_DISABLED));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_LEFT", JS_NewInt32(ctx, TEXT_ALIGN_LEFT));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_CENTER", JS_NewInt32(ctx, TEXT_ALIGN_CENTER));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_RIGHT", JS_NewInt32(ctx, TEXT_ALIGN_RIGHT));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_TOP", JS_NewInt32(ctx, TEXT_ALIGN_TOP));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_MIDDLE", JS_NewInt32(ctx, TEXT_ALIGN_MIDDLE));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_BOTTOM", JS_NewInt32(ctx, TEXT_ALIGN_BOTTOM));
    JS_SetModuleExport(ctx, m, "TEXT_WRAP_NONE", JS_NewInt32(ctx, TEXT_WRAP_NONE));
    JS_SetModuleExport(ctx, m, "TEXT_WRAP_CHAR", JS_NewInt32(ctx, TEXT_WRAP_CHAR));
    JS_SetModuleExport(ctx, m, "TEXT_WRAP_WORD", JS_NewInt32(ctx, TEXT_WRAP_WORD));
    JS_SetModuleExport(ctx, m, "DEFAULT", JS_NewInt32(ctx, DEFAULT));
    JS_SetModuleExport(ctx, m, "LABEL", JS_NewInt32(ctx, LABEL));
    JS_SetModuleExport(ctx, m, "BUTTON", JS_NewInt32(ctx, BUTTON));
    JS_SetModuleExport(ctx, m, "TOGGLE", JS_NewInt32(ctx, TOGGLE));
    JS_SetModuleExport(ctx, m, "SLIDER", JS_NewInt32(ctx, SLIDER));
    JS_SetModuleExport(ctx, m, "PROGRESSBAR", JS_NewInt32(ctx, PROGRESSBAR));
    JS_SetModuleExport(ctx, m, "CHECKBOX", JS_NewInt32(ctx, CHECKBOX));
    JS_SetModuleExport(ctx, m, "COMBOBOX", JS_NewInt32(ctx, COMBOBOX));
    JS_SetModuleExport(ctx, m, "DROPDOWNBOX", JS_NewInt32(ctx, DROPDOWNBOX));
    JS_SetModuleExport(ctx, m, "TEXTBOX", JS_NewInt32(ctx, TEXTBOX));
    JS_SetModuleExport(ctx, m, "VALUEBOX", JS_NewInt32(ctx, VALUEBOX));
    JS_SetModuleExport(ctx, m, "SPINNER", JS_NewInt32(ctx, SPINNER));
    JS_SetModuleExport(ctx, m, "LISTVIEW", JS_NewInt32(ctx, LISTVIEW));
    JS_SetModuleExport(ctx, m, "COLORPICKER", JS_NewInt32(ctx, COLORPICKER));
    JS_SetModuleExport(ctx, m, "SCROLLBAR", JS_NewInt32(ctx, SCROLLBAR));
    JS_SetModuleExport(ctx, m, "STATUSBAR", JS_NewInt32(ctx, STATUSBAR));
    JS_SetModuleExport(ctx, m, "BORDER_COLOR_NORMAL", JS_NewInt32(ctx, BORDER_COLOR_NORMAL));
    JS_SetModuleExport(ctx, m, "BASE_COLOR_NORMAL", JS_NewInt32(ctx, BASE_COLOR_NORMAL));
    JS_SetModuleExport(ctx, m, "TEXT_COLOR_NORMAL", JS_NewInt32(ctx, TEXT_COLOR_NORMAL));
    JS_SetModuleExport(ctx, m, "BORDER_COLOR_FOCUSED", JS_NewInt32(ctx, BORDER_COLOR_FOCUSED));
    JS_SetModuleExport(ctx, m, "BASE_COLOR_FOCUSED", JS_NewInt32(ctx, BASE_COLOR_FOCUSED));
    JS_SetModuleExport(ctx, m, "TEXT_COLOR_FOCUSED", JS_NewInt32(ctx, TEXT_COLOR_FOCUSED));
    JS_SetModuleExport(ctx, m, "BORDER_COLOR_PRESSED", JS_NewInt32(ctx, BORDER_COLOR_PRESSED));
    JS_SetModuleExport(ctx, m, "BASE_COLOR_PRESSED", JS_NewInt32(ctx, BASE_COLOR_PRESSED));
    JS_SetModuleExport(ctx, m, "TEXT_COLOR_PRESSED", JS_NewInt32(ctx, TEXT_COLOR_PRESSED));
    JS_SetModuleExport(ctx, m, "BORDER_COLOR_DISABLED", JS_NewInt32(ctx, BORDER_COLOR_DISABLED));
    JS_SetModuleExport(ctx, m, "BASE_COLOR_DISABLED", JS_NewInt32(ctx, BASE_COLOR_DISABLED));
    JS_SetModuleExport(ctx, m, "TEXT_COLOR_DISABLED", JS_NewInt32(ctx, TEXT_COLOR_DISABLED));
    JS_SetModuleExport(ctx, m, "BORDER_WIDTH", JS_NewInt32(ctx, BORDER_WIDTH));
    JS_SetModuleExport(ctx, m, "TEXT_PADDING", JS_NewInt32(ctx, TEXT_PADDING));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGNMENT", JS_NewInt32(ctx, TEXT_ALIGNMENT));
    JS_SetModuleExport(ctx, m, "TEXT_SIZE", JS_NewInt32(ctx, TEXT_SIZE));
    JS_SetModuleExport(ctx, m, "TEXT_SPACING", JS_NewInt32(ctx, TEXT_SPACING));
    JS_SetModuleExport(ctx, m, "LINE_COLOR", JS_NewInt32(ctx, LINE_COLOR));
    JS_SetModuleExport(ctx, m, "BACKGROUND_COLOR", JS_NewInt32(ctx, BACKGROUND_COLOR));
    JS_SetModuleExport(ctx, m, "TEXT_LINE_SPACING", JS_NewInt32(ctx, TEXT_LINE_SPACING));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGNMENT_VERTICAL", JS_NewInt32(ctx, TEXT_ALIGNMENT_VERTICAL));
    JS_SetModuleExport(ctx, m, "TEXT_WRAP_MODE", JS_NewInt32(ctx, TEXT_WRAP_MODE));
    JS_SetModuleExport(ctx, m, "GROUP_PADDING", JS_NewInt32(ctx, GROUP_PADDING));
    JS_SetModuleExport(ctx, m, "SLIDER_WIDTH", JS_NewInt32(ctx, SLIDER_WIDTH));
    JS_SetModuleExport(ctx, m, "SLIDER_PADDING", JS_NewInt32(ctx, SLIDER_PADDING));
    JS_SetModuleExport(ctx, m, "PROGRESS_PADDING", JS_NewInt32(ctx, PROGRESS_PADDING));
    JS_SetModuleExport(ctx, m, "ARROWS_SIZE", JS_NewInt32(ctx, ARROWS_SIZE));
    JS_SetModuleExport(ctx, m, "ARROWS_VISIBLE", JS_NewInt32(ctx, ARROWS_VISIBLE));
    JS_SetModuleExport(ctx, m, "SCROLL_SLIDER_PADDING", JS_NewInt32(ctx, SCROLL_SLIDER_PADDING));
    JS_SetModuleExport(ctx, m, "SCROLL_SLIDER_SIZE", JS_NewInt32(ctx, SCROLL_SLIDER_SIZE));
    JS_SetModuleExport(ctx, m, "SCROLL_PADDING", JS_NewInt32(ctx, SCROLL_PADDING));
    JS_SetModuleExport(ctx, m, "SCROLL_SPEED", JS_NewInt32(ctx, SCROLL_SPEED));
    JS_SetModuleExport(ctx, m, "CHECK_PADDING", JS_NewInt32(ctx, CHECK_PADDING));
    JS_SetModuleExport(ctx, m, "COMBO_BUTTON_WIDTH", JS_NewInt32(ctx, COMBO_BUTTON_WIDTH));
    JS_SetModuleExport(ctx, m, "COMBO_BUTTON_SPACING", JS_NewInt32(ctx, COMBO_BUTTON_SPACING));
    JS_SetModuleExport(ctx, m, "ARROW_PADDING", JS_NewInt32(ctx, ARROW_PADDING));
    JS_SetModuleExport(ctx, m, "DROPDOWN_ITEMS_SPACING", JS_NewInt32(ctx, DROPDOWN_ITEMS_SPACING));
    JS_SetModuleExport(ctx, m, "DROPDOWN_ARROW_HIDDEN", JS_NewInt32(ctx, DROPDOWN_ARROW_HIDDEN));
    JS_SetModuleExport(ctx, m, "DROPDOWN_ROLL_UP", JS_NewInt32(ctx, DROPDOWN_ROLL_UP));
    JS_SetModuleExport(ctx, m, "TEXT_READONLY", JS_NewInt32(ctx, TEXT_READONLY));
    JS_SetModuleExport(ctx, m, "SPIN_BUTTON_WIDTH", JS_NewInt32(ctx, SPIN_BUTTON_WIDTH));
    JS_SetModuleExport(ctx, m, "SPIN_BUTTON_SPACING", JS_NewInt32(ctx, SPIN_BUTTON_SPACING));
    JS_SetModuleExport(ctx, m, "LIST_ITEMS_HEIGHT", JS_NewInt32(ctx, LIST_ITEMS_HEIGHT));
    JS_SetModuleExport(ctx, m, "LIST_ITEMS_SPACING", JS_NewInt32(ctx, LIST_ITEMS_SPACING));
    JS_SetModuleExport(ctx, m, "SCROLLBAR_WIDTH", JS_NewInt32(ctx, SCROLLBAR_WIDTH));
    JS_SetModuleExport(ctx, m, "SCROLLBAR_SIDE", JS_NewInt32(ctx, SCROLLBAR_SIDE));
    JS_SetModuleExport(ctx, m, "LIST_ITEMS_BORDER_WIDTH", JS_NewInt32(ctx, LIST_ITEMS_BORDER_WIDTH));
    JS_SetModuleExport(ctx, m, "COLOR_SELECTOR_SIZE", JS_NewInt32(ctx, COLOR_SELECTOR_SIZE));
    JS_SetModuleExport(ctx, m, "HUEBAR_WIDTH", JS_NewInt32(ctx, HUEBAR_WIDTH));
    JS_SetModuleExport(ctx, m, "HUEBAR_PADDING", JS_NewInt32(ctx, HUEBAR_PADDING));
    JS_SetModuleExport(ctx, m, "HUEBAR_SELECTOR_HEIGHT", JS_NewInt32(ctx, HUEBAR_SELECTOR_HEIGHT));
    JS_SetModuleExport(ctx, m, "HUEBAR_SELECTOR_OVERFLOW", JS_NewInt32(ctx, HUEBAR_SELECTOR_OVERFLOW));
    JS_SetModuleExport(ctx, m, "ICON_NONE", JS_NewInt32(ctx, ICON_NONE));
    JS_SetModuleExport(ctx, m, "ICON_FOLDER_FILE_OPEN", JS_NewInt32(ctx, ICON_FOLDER_FILE_OPEN));
    JS_SetModuleExport(ctx, m, "ICON_FILE_SAVE_CLASSIC", JS_NewInt32(ctx, ICON_FILE_SAVE_CLASSIC));
    JS_SetModuleExport(ctx, m, "ICON_FOLDER_OPEN", JS_NewInt32(ctx, ICON_FOLDER_OPEN));
    JS_SetModuleExport(ctx, m, "ICON_FOLDER_SAVE", JS_NewInt32(ctx, ICON_FOLDER_SAVE));
    JS_SetModuleExport(ctx, m, "ICON_FILE_OPEN", JS_NewInt32(ctx, ICON_FILE_OPEN));
    JS_SetModuleExport(ctx, m, "ICON_FILE_SAVE", JS_NewInt32(ctx, ICON_FILE_SAVE));
    JS_SetModuleExport(ctx, m, "ICON_FILE_EXPORT", JS_NewInt32(ctx, ICON_FILE_EXPORT));
    JS_SetModuleExport(ctx, m, "ICON_FILE_ADD", JS_NewInt32(ctx, ICON_FILE_ADD));
    JS_SetModuleExport(ctx, m, "ICON_FILE_DELETE", JS_NewInt32(ctx, ICON_FILE_DELETE));
    JS_SetModuleExport(ctx, m, "ICON_FILETYPE_TEXT", JS_NewInt32(ctx, ICON_FILETYPE_TEXT));
    JS_SetModuleExport(ctx, m, "ICON_FILETYPE_AUDIO", JS_NewInt32(ctx, ICON_FILETYPE_AUDIO));
    JS_SetModuleExport(ctx, m, "ICON_FILETYPE_IMAGE", JS_NewInt32(ctx, ICON_FILETYPE_IMAGE));
    JS_SetModuleExport(ctx, m, "ICON_FILETYPE_PLAY", JS_NewInt32(ctx, ICON_FILETYPE_PLAY));
    JS_SetModuleExport(ctx, m, "ICON_FILETYPE_VIDEO", JS_NewInt32(ctx, ICON_FILETYPE_VIDEO));
    JS_SetModuleExport(ctx, m, "ICON_FILETYPE_INFO", JS_NewInt32(ctx, ICON_FILETYPE_INFO));
    JS_SetModuleExport(ctx, m, "ICON_FILE_COPY", JS_NewInt32(ctx, ICON_FILE_COPY));
    JS_SetModuleExport(ctx, m, "ICON_FILE_CUT", JS_NewInt32(ctx, ICON_FILE_CUT));
    JS_SetModuleExport(ctx, m, "ICON_FILE_PASTE", JS_NewInt32(ctx, ICON_FILE_PASTE));
    JS_SetModuleExport(ctx, m, "ICON_CURSOR_HAND", JS_NewInt32(ctx, ICON_CURSOR_HAND));
    JS_SetModuleExport(ctx, m, "ICON_CURSOR_POINTER", JS_NewInt32(ctx, ICON_CURSOR_POINTER));
    JS_SetModuleExport(ctx, m, "ICON_CURSOR_CLASSIC", JS_NewInt32(ctx, ICON_CURSOR_CLASSIC));
    JS_SetModuleExport(ctx, m, "ICON_PENCIL", JS_NewInt32(ctx, ICON_PENCIL));
    JS_SetModuleExport(ctx, m, "ICON_PENCIL_BIG", JS_NewInt32(ctx, ICON_PENCIL_BIG));
    JS_SetModuleExport(ctx, m, "ICON_BRUSH_CLASSIC", JS_NewInt32(ctx, ICON_BRUSH_CLASSIC));
    JS_SetModuleExport(ctx, m, "ICON_BRUSH_PAINTER", JS_NewInt32(ctx, ICON_BRUSH_PAINTER));
    JS_SetModuleExport(ctx, m, "ICON_WATER_DROP", JS_NewInt32(ctx, ICON_WATER_DROP));
    JS_SetModuleExport(ctx, m, "ICON_COLOR_PICKER", JS_NewInt32(ctx, ICON_COLOR_PICKER));
    JS_SetModuleExport(ctx, m, "ICON_RUBBER", JS_NewInt32(ctx, ICON_RUBBER));
    JS_SetModuleExport(ctx, m, "ICON_COLOR_BUCKET", JS_NewInt32(ctx, ICON_COLOR_BUCKET));
    JS_SetModuleExport(ctx, m, "ICON_TEXT_T", JS_NewInt32(ctx, ICON_TEXT_T));
    JS_SetModuleExport(ctx, m, "ICON_TEXT_A", JS_NewInt32(ctx, ICON_TEXT_A));
    JS_SetModuleExport(ctx, m, "ICON_SCALE", JS_NewInt32(ctx, ICON_SCALE));
    JS_SetModuleExport(ctx, m, "ICON_RESIZE", JS_NewInt32(ctx, ICON_RESIZE));
    JS_SetModuleExport(ctx, m, "ICON_FILTER_POINT", JS_NewInt32(ctx, ICON_FILTER_POINT));
    JS_SetModuleExport(ctx, m, "ICON_FILTER_BILINEAR", JS_NewInt32(ctx, ICON_FILTER_BILINEAR));
    JS_SetModuleExport(ctx, m, "ICON_CROP", JS_NewInt32(ctx, ICON_CROP));
    JS_SetModuleExport(ctx, m, "ICON_CROP_ALPHA", JS_NewInt32(ctx, ICON_CROP_ALPHA));
    JS_SetModuleExport(ctx, m, "ICON_SQUARE_TOGGLE", JS_NewInt32(ctx, ICON_SQUARE_TOGGLE));
    JS_SetModuleExport(ctx, m, "ICON_SYMMETRY", JS_NewInt32(ctx, ICON_SYMMETRY));
    JS_SetModuleExport(ctx, m, "ICON_SYMMETRY_HORIZONTAL", JS_NewInt32(ctx, ICON_SYMMETRY_HORIZONTAL));
    JS_SetModuleExport(ctx, m, "ICON_SYMMETRY_VERTICAL", JS_NewInt32(ctx, ICON_SYMMETRY_VERTICAL));
    JS_SetModuleExport(ctx, m, "ICON_LENS", JS_NewInt32(ctx, ICON_LENS));
    JS_SetModuleExport(ctx, m, "ICON_LENS_BIG", JS_NewInt32(ctx, ICON_LENS_BIG));
    JS_SetModuleExport(ctx, m, "ICON_EYE_ON", JS_NewInt32(ctx, ICON_EYE_ON));
    JS_SetModuleExport(ctx, m, "ICON_EYE_OFF", JS_NewInt32(ctx, ICON_EYE_OFF));
    JS_SetModuleExport(ctx, m, "ICON_FILTER_TOP", JS_NewInt32(ctx, ICON_FILTER_TOP));
    JS_SetModuleExport(ctx, m, "ICON_FILTER", JS_NewInt32(ctx, ICON_FILTER));
    JS_SetModuleExport(ctx, m, "ICON_TARGET_POINT", JS_NewInt32(ctx, ICON_TARGET_POINT));
    JS_SetModuleExport(ctx, m, "ICON_TARGET_SMALL", JS_NewInt32(ctx, ICON_TARGET_SMALL));
    JS_SetModuleExport(ctx, m, "ICON_TARGET_BIG", JS_NewInt32(ctx, ICON_TARGET_BIG));
    JS_SetModuleExport(ctx, m, "ICON_TARGET_MOVE", JS_NewInt32(ctx, ICON_TARGET_MOVE));
    JS_SetModuleExport(ctx, m, "ICON_CURSOR_MOVE", JS_NewInt32(ctx, ICON_CURSOR_MOVE));
    JS_SetModuleExport(ctx, m, "ICON_CURSOR_SCALE", JS_NewInt32(ctx, ICON_CURSOR_SCALE));
    JS_SetModuleExport(ctx, m, "ICON_CURSOR_SCALE_RIGHT", JS_NewInt32(ctx, ICON_CURSOR_SCALE_RIGHT));
    JS_SetModuleExport(ctx, m, "ICON_CURSOR_SCALE_LEFT", JS_NewInt32(ctx, ICON_CURSOR_SCALE_LEFT));
    JS_SetModuleExport(ctx, m, "ICON_UNDO", JS_NewInt32(ctx, ICON_UNDO));
    JS_SetModuleExport(ctx, m, "ICON_REDO", JS_NewInt32(ctx, ICON_REDO));
    JS_SetModuleExport(ctx, m, "ICON_REREDO", JS_NewInt32(ctx, ICON_REREDO));
    JS_SetModuleExport(ctx, m, "ICON_MUTATE", JS_NewInt32(ctx, ICON_MUTATE));
    JS_SetModuleExport(ctx, m, "ICON_ROTATE", JS_NewInt32(ctx, ICON_ROTATE));
    JS_SetModuleExport(ctx, m, "ICON_REPEAT", JS_NewInt32(ctx, ICON_REPEAT));
    JS_SetModuleExport(ctx, m, "ICON_SHUFFLE", JS_NewInt32(ctx, ICON_SHUFFLE));
    JS_SetModuleExport(ctx, m, "ICON_EMPTYBOX", JS_NewInt32(ctx, ICON_EMPTYBOX));
    JS_SetModuleExport(ctx, m, "ICON_TARGET", JS_NewInt32(ctx, ICON_TARGET));
    JS_SetModuleExport(ctx, m, "ICON_TARGET_SMALL_FILL", JS_NewInt32(ctx, ICON_TARGET_SMALL_FILL));
    JS_SetModuleExport(ctx, m, "ICON_TARGET_BIG_FILL", JS_NewInt32(ctx, ICON_TARGET_BIG_FILL));
    JS_SetModuleExport(ctx, m, "ICON_TARGET_MOVE_FILL", JS_NewInt32(ctx, ICON_TARGET_MOVE_FILL));
    JS_SetModuleExport(ctx, m, "ICON_CURSOR_MOVE_FILL", JS_NewInt32(ctx, ICON_CURSOR_MOVE_FILL));
    JS_SetModuleExport(ctx, m, "ICON_CURSOR_SCALE_FILL", JS_NewInt32(ctx, ICON_CURSOR_SCALE_FILL));
    JS_SetModuleExport(ctx, m, "ICON_CURSOR_SCALE_RIGHT_FILL", JS_NewInt32(ctx, ICON_CURSOR_SCALE_RIGHT_FILL));
    JS_SetModuleExport(ctx, m, "ICON_CURSOR_SCALE_LEFT_FILL", JS_NewInt32(ctx, ICON_CURSOR_SCALE_LEFT_FILL));
    JS_SetModuleExport(ctx, m, "ICON_UNDO_FILL", JS_NewInt32(ctx, ICON_UNDO_FILL));
    JS_SetModuleExport(ctx, m, "ICON_REDO_FILL", JS_NewInt32(ctx, ICON_REDO_FILL));
    JS_SetModuleExport(ctx, m, "ICON_REREDO_FILL", JS_NewInt32(ctx, ICON_REREDO_FILL));
    JS_SetModuleExport(ctx, m, "ICON_MUTATE_FILL", JS_NewInt32(ctx, ICON_MUTATE_FILL));
    JS_SetModuleExport(ctx, m, "ICON_ROTATE_FILL", JS_NewInt32(ctx, ICON_ROTATE_FILL));
    JS_SetModuleExport(ctx, m, "ICON_REPEAT_FILL", JS_NewInt32(ctx, ICON_REPEAT_FILL));
    JS_SetModuleExport(ctx, m, "ICON_SHUFFLE_FILL", JS_NewInt32(ctx, ICON_SHUFFLE_FILL));
    JS_SetModuleExport(ctx, m, "ICON_EMPTYBOX_SMALL", JS_NewInt32(ctx, ICON_EMPTYBOX_SMALL));
    JS_SetModuleExport(ctx, m, "ICON_BOX", JS_NewInt32(ctx, ICON_BOX));
    JS_SetModuleExport(ctx, m, "ICON_BOX_TOP", JS_NewInt32(ctx, ICON_BOX_TOP));
    JS_SetModuleExport(ctx, m, "ICON_BOX_TOP_RIGHT", JS_NewInt32(ctx, ICON_BOX_TOP_RIGHT));
    JS_SetModuleExport(ctx, m, "ICON_BOX_RIGHT", JS_NewInt32(ctx, ICON_BOX_RIGHT));
    JS_SetModuleExport(ctx, m, "ICON_BOX_BOTTOM_RIGHT", JS_NewInt32(ctx, ICON_BOX_BOTTOM_RIGHT));
    JS_SetModuleExport(ctx, m, "ICON_BOX_BOTTOM", JS_NewInt32(ctx, ICON_BOX_BOTTOM));
    JS_SetModuleExport(ctx, m, "ICON_BOX_BOTTOM_LEFT", JS_NewInt32(ctx, ICON_BOX_BOTTOM_LEFT));
    JS_SetModuleExport(ctx, m, "ICON_BOX_LEFT", JS_NewInt32(ctx, ICON_BOX_LEFT));
    JS_SetModuleExport(ctx, m, "ICON_BOX_TOP_LEFT", JS_NewInt32(ctx, ICON_BOX_TOP_LEFT));
    JS_SetModuleExport(ctx, m, "ICON_BOX_CENTER", JS_NewInt32(ctx, ICON_BOX_CENTER));
    JS_SetModuleExport(ctx, m, "ICON_BOX_CIRCLE_MASK", JS_NewInt32(ctx, ICON_BOX_CIRCLE_MASK));
    JS_SetModuleExport(ctx, m, "ICON_POT", JS_NewInt32(ctx, ICON_POT));
    JS_SetModuleExport(ctx, m, "ICON_ALPHA_MULTIPLY", JS_NewInt32(ctx, ICON_ALPHA_MULTIPLY));
    JS_SetModuleExport(ctx, m, "ICON_ALPHA_CLEAR", JS_NewInt32(ctx, ICON_ALPHA_CLEAR));
    JS_SetModuleExport(ctx, m, "ICON_DITHERING", JS_NewInt32(ctx, ICON_DITHERING));
    JS_SetModuleExport(ctx, m, "ICON_MIPMAPS", JS_NewInt32(ctx, ICON_MIPMAPS));
    JS_SetModuleExport(ctx, m, "ICON_BOX_GRID", JS_NewInt32(ctx, ICON_BOX_GRID));
    JS_SetModuleExport(ctx, m, "ICON_GRID", JS_NewInt32(ctx, ICON_GRID));
    JS_SetModuleExport(ctx, m, "ICON_BOX_CORNERS_SMALL", JS_NewInt32(ctx, ICON_BOX_CORNERS_SMALL));
    JS_SetModuleExport(ctx, m, "ICON_BOX_CORNERS_BIG", JS_NewInt32(ctx, ICON_BOX_CORNERS_BIG));
    JS_SetModuleExport(ctx, m, "ICON_FOUR_BOXES", JS_NewInt32(ctx, ICON_FOUR_BOXES));
    JS_SetModuleExport(ctx, m, "ICON_GRID_FILL", JS_NewInt32(ctx, ICON_GRID_FILL));
    JS_SetModuleExport(ctx, m, "ICON_BOX_MULTISIZE", JS_NewInt32(ctx, ICON_BOX_MULTISIZE));
    JS_SetModuleExport(ctx, m, "ICON_ZOOM_SMALL", JS_NewInt32(ctx, ICON_ZOOM_SMALL));
    JS_SetModuleExport(ctx, m, "ICON_ZOOM_MEDIUM", JS_NewInt32(ctx, ICON_ZOOM_MEDIUM));
    JS_SetModuleExport(ctx, m, "ICON_ZOOM_BIG", JS_NewInt32(ctx, ICON_ZOOM_BIG));
    JS_SetModuleExport(ctx, m, "ICON_ZOOM_ALL", JS_NewInt32(ctx, ICON_ZOOM_ALL));
    JS_SetModuleExport(ctx, m, "ICON_ZOOM_CENTER", JS_NewInt32(ctx, ICON_ZOOM_CENTER));
    JS_SetModuleExport(ctx, m, "ICON_BOX_DOTS_SMALL", JS_NewInt32(ctx, ICON_BOX_DOTS_SMALL));
    JS_SetModuleExport(ctx, m, "ICON_BOX_DOTS_BIG", JS_NewInt32(ctx, ICON_BOX_DOTS_BIG));
    JS_SetModuleExport(ctx, m, "ICON_BOX_CONCENTRIC", JS_NewInt32(ctx, ICON_BOX_CONCENTRIC));
    JS_SetModuleExport(ctx, m, "ICON_BOX_GRID_BIG", JS_NewInt32(ctx, ICON_BOX_GRID_BIG));
    JS_SetModuleExport(ctx, m, "ICON_OK_TICK", JS_NewInt32(ctx, ICON_OK_TICK));
    JS_SetModuleExport(ctx, m, "ICON_CROSS", JS_NewInt32(ctx, ICON_CROSS));
    JS_SetModuleExport(ctx, m, "ICON_ARROW_LEFT", JS_NewInt32(ctx, ICON_ARROW_LEFT));
    JS_SetModuleExport(ctx, m, "ICON_ARROW_RIGHT", JS_NewInt32(ctx, ICON_ARROW_RIGHT));
    JS_SetModuleExport(ctx, m, "ICON_ARROW_DOWN", JS_NewInt32(ctx, ICON_ARROW_DOWN));
    JS_SetModuleExport(ctx, m, "ICON_ARROW_UP", JS_NewInt32(ctx, ICON_ARROW_UP));
    JS_SetModuleExport(ctx, m, "ICON_ARROW_LEFT_FILL", JS_NewInt32(ctx, ICON_ARROW_LEFT_FILL));
    JS_SetModuleExport(ctx, m, "ICON_ARROW_RIGHT_FILL", JS_NewInt32(ctx, ICON_ARROW_RIGHT_FILL));
    JS_SetModuleExport(ctx, m, "ICON_ARROW_DOWN_FILL", JS_NewInt32(ctx, ICON_ARROW_DOWN_FILL));
    JS_SetModuleExport(ctx, m, "ICON_ARROW_UP_FILL", JS_NewInt32(ctx, ICON_ARROW_UP_FILL));
    JS_SetModuleExport(ctx, m, "ICON_AUDIO", JS_NewInt32(ctx, ICON_AUDIO));
    JS_SetModuleExport(ctx, m, "ICON_FX", JS_NewInt32(ctx, ICON_FX));
    JS_SetModuleExport(ctx, m, "ICON_WAVE", JS_NewInt32(ctx, ICON_WAVE));
    JS_SetModuleExport(ctx, m, "ICON_WAVE_SINUS", JS_NewInt32(ctx, ICON_WAVE_SINUS));
    JS_SetModuleExport(ctx, m, "ICON_WAVE_SQUARE", JS_NewInt32(ctx, ICON_WAVE_SQUARE));
    JS_SetModuleExport(ctx, m, "ICON_WAVE_TRIANGULAR", JS_NewInt32(ctx, ICON_WAVE_TRIANGULAR));
    JS_SetModuleExport(ctx, m, "ICON_CROSS_SMALL", JS_NewInt32(ctx, ICON_CROSS_SMALL));
    JS_SetModuleExport(ctx, m, "ICON_PLAYER_PREVIOUS", JS_NewInt32(ctx, ICON_PLAYER_PREVIOUS));
    JS_SetModuleExport(ctx, m, "ICON_PLAYER_PLAY_BACK", JS_NewInt32(ctx, ICON_PLAYER_PLAY_BACK));
    JS_SetModuleExport(ctx, m, "ICON_PLAYER_PLAY", JS_NewInt32(ctx, ICON_PLAYER_PLAY));
    JS_SetModuleExport(ctx, m, "ICON_PLAYER_PAUSE", JS_NewInt32(ctx, ICON_PLAYER_PAUSE));
    JS_SetModuleExport(ctx, m, "ICON_PLAYER_STOP", JS_NewInt32(ctx, ICON_PLAYER_STOP));
    JS_SetModuleExport(ctx, m, "ICON_PLAYER_NEXT", JS_NewInt32(ctx, ICON_PLAYER_NEXT));
    JS_SetModuleExport(ctx, m, "ICON_PLAYER_RECORD", JS_NewInt32(ctx, ICON_PLAYER_RECORD));
    JS_SetModuleExport(ctx, m, "ICON_MAGNET", JS_NewInt32(ctx, ICON_MAGNET));
    JS_SetModuleExport(ctx, m, "ICON_LOCK_CLOSE", JS_NewInt32(ctx, ICON_LOCK_CLOSE));
    JS_SetModuleExport(ctx, m, "ICON_LOCK_OPEN", JS_NewInt32(ctx, ICON_LOCK_OPEN));
    JS_SetModuleExport(ctx, m, "ICON_CLOCK", JS_NewInt32(ctx, ICON_CLOCK));
    JS_SetModuleExport(ctx, m, "ICON_TOOLS", JS_NewInt32(ctx, ICON_TOOLS));
    JS_SetModuleExport(ctx, m, "ICON_GEAR", JS_NewInt32(ctx, ICON_GEAR));
    JS_SetModuleExport(ctx, m, "ICON_GEAR_BIG", JS_NewInt32(ctx, ICON_GEAR_BIG));
    JS_SetModuleExport(ctx, m, "ICON_BIN", JS_NewInt32(ctx, ICON_BIN));
    JS_SetModuleExport(ctx, m, "ICON_HAND_POINTER", JS_NewInt32(ctx, ICON_HAND_POINTER));
    JS_SetModuleExport(ctx, m, "ICON_LASER", JS_NewInt32(ctx, ICON_LASER));
    JS_SetModuleExport(ctx, m, "ICON_COIN", JS_NewInt32(ctx, ICON_COIN));
    JS_SetModuleExport(ctx, m, "ICON_EXPLOSION", JS_NewInt32(ctx, ICON_EXPLOSION));
    JS_SetModuleExport(ctx, m, "ICON_1UP", JS_NewInt32(ctx, ICON_1UP));
    JS_SetModuleExport(ctx, m, "ICON_PLAYER", JS_NewInt32(ctx, ICON_PLAYER));
    JS_SetModuleExport(ctx, m, "ICON_PLAYER_JUMP", JS_NewInt32(ctx, ICON_PLAYER_JUMP));
    JS_SetModuleExport(ctx, m, "ICON_KEY", JS_NewInt32(ctx, ICON_KEY));
    JS_SetModuleExport(ctx, m, "ICON_DEMON", JS_NewInt32(ctx, ICON_DEMON));
    JS_SetModuleExport(ctx, m, "ICON_TEXT_POPUP", JS_NewInt32(ctx, ICON_TEXT_POPUP));
    JS_SetModuleExport(ctx, m, "ICON_GEAR_EX", JS_NewInt32(ctx, ICON_GEAR_EX));
    JS_SetModuleExport(ctx, m, "ICON_CRACK", JS_NewInt32(ctx, ICON_CRACK));
    JS_SetModuleExport(ctx, m, "ICON_CRACK_POINTS", JS_NewInt32(ctx, ICON_CRACK_POINTS));
    JS_SetModuleExport(ctx, m, "ICON_STAR", JS_NewInt32(ctx, ICON_STAR));
    JS_SetModuleExport(ctx, m, "ICON_DOOR", JS_NewInt32(ctx, ICON_DOOR));
    JS_SetModuleExport(ctx, m, "ICON_EXIT", JS_NewInt32(ctx, ICON_EXIT));
    JS_SetModuleExport(ctx, m, "ICON_MODE_2D", JS_NewInt32(ctx, ICON_MODE_2D));
    JS_SetModuleExport(ctx, m, "ICON_MODE_3D", JS_NewInt32(ctx, ICON_MODE_3D));
    JS_SetModuleExport(ctx, m, "ICON_CUBE", JS_NewInt32(ctx, ICON_CUBE));
    JS_SetModuleExport(ctx, m, "ICON_CUBE_FACE_TOP", JS_NewInt32(ctx, ICON_CUBE_FACE_TOP));
    JS_SetModuleExport(ctx, m, "ICON_CUBE_FACE_LEFT", JS_NewInt32(ctx, ICON_CUBE_FACE_LEFT));
    JS_SetModuleExport(ctx, m, "ICON_CUBE_FACE_FRONT", JS_NewInt32(ctx, ICON_CUBE_FACE_FRONT));
    JS_SetModuleExport(ctx, m, "ICON_CUBE_FACE_BOTTOM", JS_NewInt32(ctx, ICON_CUBE_FACE_BOTTOM));
    JS_SetModuleExport(ctx, m, "ICON_CUBE_FACE_RIGHT", JS_NewInt32(ctx, ICON_CUBE_FACE_RIGHT));
    JS_SetModuleExport(ctx, m, "ICON_CUBE_FACE_BACK", JS_NewInt32(ctx, ICON_CUBE_FACE_BACK));
    JS_SetModuleExport(ctx, m, "ICON_CAMERA", JS_NewInt32(ctx, ICON_CAMERA));
    JS_SetModuleExport(ctx, m, "ICON_SPECIAL", JS_NewInt32(ctx, ICON_SPECIAL));
    JS_SetModuleExport(ctx, m, "ICON_LINK_NET", JS_NewInt32(ctx, ICON_LINK_NET));
    JS_SetModuleExport(ctx, m, "ICON_LINK_BOXES", JS_NewInt32(ctx, ICON_LINK_BOXES));
    JS_SetModuleExport(ctx, m, "ICON_LINK_MULTI", JS_NewInt32(ctx, ICON_LINK_MULTI));
    JS_SetModuleExport(ctx, m, "ICON_LINK", JS_NewInt32(ctx, ICON_LINK));
    JS_SetModuleExport(ctx, m, "ICON_LINK_BROKE", JS_NewInt32(ctx, ICON_LINK_BROKE));
    JS_SetModuleExport(ctx, m, "ICON_TEXT_NOTES", JS_NewInt32(ctx, ICON_TEXT_NOTES));
    JS_SetModuleExport(ctx, m, "ICON_NOTEBOOK", JS_NewInt32(ctx, ICON_NOTEBOOK));
    JS_SetModuleExport(ctx, m, "ICON_SUITCASE", JS_NewInt32(ctx, ICON_SUITCASE));
    JS_SetModuleExport(ctx, m, "ICON_SUITCASE_ZIP", JS_NewInt32(ctx, ICON_SUITCASE_ZIP));
    JS_SetModuleExport(ctx, m, "ICON_MAILBOX", JS_NewInt32(ctx, ICON_MAILBOX));
    JS_SetModuleExport(ctx, m, "ICON_MONITOR", JS_NewInt32(ctx, ICON_MONITOR));
    JS_SetModuleExport(ctx, m, "ICON_PRINTER", JS_NewInt32(ctx, ICON_PRINTER));
    JS_SetModuleExport(ctx, m, "ICON_PHOTO_CAMERA", JS_NewInt32(ctx, ICON_PHOTO_CAMERA));
    JS_SetModuleExport(ctx, m, "ICON_PHOTO_CAMERA_FLASH", JS_NewInt32(ctx, ICON_PHOTO_CAMERA_FLASH));
    JS_SetModuleExport(ctx, m, "ICON_HOUSE", JS_NewInt32(ctx, ICON_HOUSE));
    JS_SetModuleExport(ctx, m, "ICON_HEART", JS_NewInt32(ctx, ICON_HEART));
    JS_SetModuleExport(ctx, m, "ICON_CORNER", JS_NewInt32(ctx, ICON_CORNER));
    JS_SetModuleExport(ctx, m, "ICON_VERTICAL_BARS", JS_NewInt32(ctx, ICON_VERTICAL_BARS));
    JS_SetModuleExport(ctx, m, "ICON_VERTICAL_BARS_FILL", JS_NewInt32(ctx, ICON_VERTICAL_BARS_FILL));
    JS_SetModuleExport(ctx, m, "ICON_LIFE_BARS", JS_NewInt32(ctx, ICON_LIFE_BARS));
    JS_SetModuleExport(ctx, m, "ICON_INFO", JS_NewInt32(ctx, ICON_INFO));
    JS_SetModuleExport(ctx, m, "ICON_CROSSLINE", JS_NewInt32(ctx, ICON_CROSSLINE));
    JS_SetModuleExport(ctx, m, "ICON_HELP", JS_NewInt32(ctx, ICON_HELP));
    JS_SetModuleExport(ctx, m, "ICON_FILETYPE_ALPHA", JS_NewInt32(ctx, ICON_FILETYPE_ALPHA));
    JS_SetModuleExport(ctx, m, "ICON_FILETYPE_HOME", JS_NewInt32(ctx, ICON_FILETYPE_HOME));
    JS_SetModuleExport(ctx, m, "ICON_LAYERS_VISIBLE", JS_NewInt32(ctx, ICON_LAYERS_VISIBLE));
    JS_SetModuleExport(ctx, m, "ICON_LAYERS", JS_NewInt32(ctx, ICON_LAYERS));
    JS_SetModuleExport(ctx, m, "ICON_WINDOW", JS_NewInt32(ctx, ICON_WINDOW));
    JS_SetModuleExport(ctx, m, "ICON_HIDPI", JS_NewInt32(ctx, ICON_HIDPI));
    JS_SetModuleExport(ctx, m, "ICON_FILETYPE_BINARY", JS_NewInt32(ctx, ICON_FILETYPE_BINARY));
    JS_SetModuleExport(ctx, m, "ICON_HEX", JS_NewInt32(ctx, ICON_HEX));
    JS_SetModuleExport(ctx, m, "ICON_SHIELD", JS_NewInt32(ctx, ICON_SHIELD));
    JS_SetModuleExport(ctx, m, "ICON_FILE_NEW", JS_NewInt32(ctx, ICON_FILE_NEW));
    JS_SetModuleExport(ctx, m, "ICON_FOLDER_ADD", JS_NewInt32(ctx, ICON_FOLDER_ADD));
    JS_SetModuleExport(ctx, m, "ICON_ALARM", JS_NewInt32(ctx, ICON_ALARM));
    JS_SetModuleExport(ctx, m, "ICON_CPU", JS_NewInt32(ctx, ICON_CPU));
    JS_SetModuleExport(ctx, m, "ICON_ROM", JS_NewInt32(ctx, ICON_ROM));
    JS_SetModuleExport(ctx, m, "ICON_STEP_OVER", JS_NewInt32(ctx, ICON_STEP_OVER));
    JS_SetModuleExport(ctx, m, "ICON_STEP_INTO", JS_NewInt32(ctx, ICON_STEP_INTO));
    JS_SetModuleExport(ctx, m, "ICON_STEP_OUT", JS_NewInt32(ctx, ICON_STEP_OUT));
    JS_SetModuleExport(ctx, m, "ICON_RESTART", JS_NewInt32(ctx, ICON_RESTART));
    JS_SetModuleExport(ctx, m, "ICON_BREAKPOINT_ON", JS_NewInt32(ctx, ICON_BREAKPOINT_ON));
    JS_SetModuleExport(ctx, m, "ICON_BREAKPOINT_OFF", JS_NewInt32(ctx, ICON_BREAKPOINT_OFF));
    JS_SetModuleExport(ctx, m, "ICON_BURGER_MENU", JS_NewInt32(ctx, ICON_BURGER_MENU));
    JS_SetModuleExport(ctx, m, "ICON_CASE_SENSITIVE", JS_NewInt32(ctx, ICON_CASE_SENSITIVE));
    JS_SetModuleExport(ctx, m, "ICON_REG_EXP", JS_NewInt32(ctx, ICON_REG_EXP));
    JS_SetModuleExport(ctx, m, "ICON_FOLDER", JS_NewInt32(ctx, ICON_FOLDER));
    JS_SetModuleExport(ctx, m, "ICON_FILE", JS_NewInt32(ctx, ICON_FILE));
    JS_SetModuleExport(ctx, m, "ICON_SAND_TIMER", JS_NewInt32(ctx, ICON_SAND_TIMER));
    JS_SetModuleExport(ctx, m, "ICON_WARNING", JS_NewInt32(ctx, ICON_WARNING));
    JS_SetModuleExport(ctx, m, "ICON_HELP_BOX", JS_NewInt32(ctx, ICON_HELP_BOX));
    JS_SetModuleExport(ctx, m, "ICON_INFO_BOX", JS_NewInt32(ctx, ICON_INFO_BOX));
    JS_SetModuleExport(ctx, m, "ICON_PRIORITY", JS_NewInt32(ctx, ICON_PRIORITY));
    JS_SetModuleExport(ctx, m, "ICON_LAYERS_ISO", JS_NewInt32(ctx, ICON_LAYERS_ISO));
    JS_SetModuleExport(ctx, m, "ICON_LAYERS2", JS_NewInt32(ctx, ICON_LAYERS2));
    JS_SetModuleExport(ctx, m, "ICON_MLAYERS", JS_NewInt32(ctx, ICON_MLAYERS));
    JS_SetModuleExport(ctx, m, "ICON_MAPS", JS_NewInt32(ctx, ICON_MAPS));
    JS_SetModuleExport(ctx, m, "ICON_HOT", JS_NewInt32(ctx, ICON_HOT));
    JS_SetModuleExport(ctx, m, "ICON_229", JS_NewInt32(ctx, ICON_229));
    JS_SetModuleExport(ctx, m, "ICON_230", JS_NewInt32(ctx, ICON_230));
    JS_SetModuleExport(ctx, m, "ICON_231", JS_NewInt32(ctx, ICON_231));
    JS_SetModuleExport(ctx, m, "ICON_232", JS_NewInt32(ctx, ICON_232));
    JS_SetModuleExport(ctx, m, "ICON_233", JS_NewInt32(ctx, ICON_233));
    JS_SetModuleExport(ctx, m, "ICON_234", JS_NewInt32(ctx, ICON_234));
    JS_SetModuleExport(ctx, m, "ICON_235", JS_NewInt32(ctx, ICON_235));
    JS_SetModuleExport(ctx, m, "ICON_236", JS_NewInt32(ctx, ICON_236));
    JS_SetModuleExport(ctx, m, "ICON_237", JS_NewInt32(ctx, ICON_237));
    JS_SetModuleExport(ctx, m, "ICON_238", JS_NewInt32(ctx, ICON_238));
    JS_SetModuleExport(ctx, m, "ICON_239", JS_NewInt32(ctx, ICON_239));
    JS_SetModuleExport(ctx, m, "ICON_240", JS_NewInt32(ctx, ICON_240));
    JS_SetModuleExport(ctx, m, "ICON_241", JS_NewInt32(ctx, ICON_241));
    JS_SetModuleExport(ctx, m, "ICON_242", JS_NewInt32(ctx, ICON_242));
    JS_SetModuleExport(ctx, m, "ICON_243", JS_NewInt32(ctx, ICON_243));
    JS_SetModuleExport(ctx, m, "ICON_244", JS_NewInt32(ctx, ICON_244));
    JS_SetModuleExport(ctx, m, "ICON_245", JS_NewInt32(ctx, ICON_245));
    JS_SetModuleExport(ctx, m, "ICON_246", JS_NewInt32(ctx, ICON_246));
    JS_SetModuleExport(ctx, m, "ICON_247", JS_NewInt32(ctx, ICON_247));
    JS_SetModuleExport(ctx, m, "ICON_248", JS_NewInt32(ctx, ICON_248));
    JS_SetModuleExport(ctx, m, "ICON_249", JS_NewInt32(ctx, ICON_249));
    JS_SetModuleExport(ctx, m, "ICON_250", JS_NewInt32(ctx, ICON_250));
    JS_SetModuleExport(ctx, m, "ICON_251", JS_NewInt32(ctx, ICON_251));
    JS_SetModuleExport(ctx, m, "ICON_252", JS_NewInt32(ctx, ICON_252));
    JS_SetModuleExport(ctx, m, "ICON_253", JS_NewInt32(ctx, ICON_253));
    JS_SetModuleExport(ctx, m, "ICON_254", JS_NewInt32(ctx, ICON_254));
    JS_SetModuleExport(ctx, m, "ICON_255", JS_NewInt32(ctx, ICON_255));
    JS_SetModuleExport(ctx, m, "LIGHT_DIRECTIONAL", JS_NewInt32(ctx, LIGHT_DIRECTIONAL));
    JS_SetModuleExport(ctx, m, "LIGHT_POINT", JS_NewInt32(ctx, LIGHT_POINT));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_DIFFUSE", JS_NewInt32(ctx, MATERIAL_MAP_DIFFUSE));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_SPECULAR", JS_NewInt32(ctx, MATERIAL_MAP_SPECULAR));
    return 0;
}

JSModuleDef * js_init_module_raylib_core(JSContext * ctx, const char * module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_raylib_core_init);
    if(!m) return NULL;
    JS_AddModuleExportList(ctx, m, js_raylib_core_funcs, countof(js_raylib_core_funcs));
    JS_AddModuleExport(ctx, m, "DEG2RAD");
    JS_AddModuleExport(ctx, m, "RAD2DEG");
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
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_FLOAT");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_VEC2");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_VEC3");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_VEC4");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_INT");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_IVEC2");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_IVEC3");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_IVEC4");
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
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_PANORAMA");
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
    JS_AddModuleExport(ctx, m, "STATE_NORMAL");
    JS_AddModuleExport(ctx, m, "STATE_FOCUSED");
    JS_AddModuleExport(ctx, m, "STATE_PRESSED");
    JS_AddModuleExport(ctx, m, "STATE_DISABLED");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_LEFT");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_CENTER");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_RIGHT");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_TOP");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_MIDDLE");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_BOTTOM");
    JS_AddModuleExport(ctx, m, "TEXT_WRAP_NONE");
    JS_AddModuleExport(ctx, m, "TEXT_WRAP_CHAR");
    JS_AddModuleExport(ctx, m, "TEXT_WRAP_WORD");
    JS_AddModuleExport(ctx, m, "DEFAULT");
    JS_AddModuleExport(ctx, m, "LABEL");
    JS_AddModuleExport(ctx, m, "BUTTON");
    JS_AddModuleExport(ctx, m, "TOGGLE");
    JS_AddModuleExport(ctx, m, "SLIDER");
    JS_AddModuleExport(ctx, m, "PROGRESSBAR");
    JS_AddModuleExport(ctx, m, "CHECKBOX");
    JS_AddModuleExport(ctx, m, "COMBOBOX");
    JS_AddModuleExport(ctx, m, "DROPDOWNBOX");
    JS_AddModuleExport(ctx, m, "TEXTBOX");
    JS_AddModuleExport(ctx, m, "VALUEBOX");
    JS_AddModuleExport(ctx, m, "SPINNER");
    JS_AddModuleExport(ctx, m, "LISTVIEW");
    JS_AddModuleExport(ctx, m, "COLORPICKER");
    JS_AddModuleExport(ctx, m, "SCROLLBAR");
    JS_AddModuleExport(ctx, m, "STATUSBAR");
    JS_AddModuleExport(ctx, m, "BORDER_COLOR_NORMAL");
    JS_AddModuleExport(ctx, m, "BASE_COLOR_NORMAL");
    JS_AddModuleExport(ctx, m, "TEXT_COLOR_NORMAL");
    JS_AddModuleExport(ctx, m, "BORDER_COLOR_FOCUSED");
    JS_AddModuleExport(ctx, m, "BASE_COLOR_FOCUSED");
    JS_AddModuleExport(ctx, m, "TEXT_COLOR_FOCUSED");
    JS_AddModuleExport(ctx, m, "BORDER_COLOR_PRESSED");
    JS_AddModuleExport(ctx, m, "BASE_COLOR_PRESSED");
    JS_AddModuleExport(ctx, m, "TEXT_COLOR_PRESSED");
    JS_AddModuleExport(ctx, m, "BORDER_COLOR_DISABLED");
    JS_AddModuleExport(ctx, m, "BASE_COLOR_DISABLED");
    JS_AddModuleExport(ctx, m, "TEXT_COLOR_DISABLED");
    JS_AddModuleExport(ctx, m, "BORDER_WIDTH");
    JS_AddModuleExport(ctx, m, "TEXT_PADDING");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGNMENT");
    JS_AddModuleExport(ctx, m, "TEXT_SIZE");
    JS_AddModuleExport(ctx, m, "TEXT_SPACING");
    JS_AddModuleExport(ctx, m, "LINE_COLOR");
    JS_AddModuleExport(ctx, m, "BACKGROUND_COLOR");
    JS_AddModuleExport(ctx, m, "TEXT_LINE_SPACING");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGNMENT_VERTICAL");
    JS_AddModuleExport(ctx, m, "TEXT_WRAP_MODE");
    JS_AddModuleExport(ctx, m, "GROUP_PADDING");
    JS_AddModuleExport(ctx, m, "SLIDER_WIDTH");
    JS_AddModuleExport(ctx, m, "SLIDER_PADDING");
    JS_AddModuleExport(ctx, m, "PROGRESS_PADDING");
    JS_AddModuleExport(ctx, m, "ARROWS_SIZE");
    JS_AddModuleExport(ctx, m, "ARROWS_VISIBLE");
    JS_AddModuleExport(ctx, m, "SCROLL_SLIDER_PADDING");
    JS_AddModuleExport(ctx, m, "SCROLL_SLIDER_SIZE");
    JS_AddModuleExport(ctx, m, "SCROLL_PADDING");
    JS_AddModuleExport(ctx, m, "SCROLL_SPEED");
    JS_AddModuleExport(ctx, m, "CHECK_PADDING");
    JS_AddModuleExport(ctx, m, "COMBO_BUTTON_WIDTH");
    JS_AddModuleExport(ctx, m, "COMBO_BUTTON_SPACING");
    JS_AddModuleExport(ctx, m, "ARROW_PADDING");
    JS_AddModuleExport(ctx, m, "DROPDOWN_ITEMS_SPACING");
    JS_AddModuleExport(ctx, m, "DROPDOWN_ARROW_HIDDEN");
    JS_AddModuleExport(ctx, m, "DROPDOWN_ROLL_UP");
    JS_AddModuleExport(ctx, m, "TEXT_READONLY");
    JS_AddModuleExport(ctx, m, "SPIN_BUTTON_WIDTH");
    JS_AddModuleExport(ctx, m, "SPIN_BUTTON_SPACING");
    JS_AddModuleExport(ctx, m, "LIST_ITEMS_HEIGHT");
    JS_AddModuleExport(ctx, m, "LIST_ITEMS_SPACING");
    JS_AddModuleExport(ctx, m, "SCROLLBAR_WIDTH");
    JS_AddModuleExport(ctx, m, "SCROLLBAR_SIDE");
    JS_AddModuleExport(ctx, m, "LIST_ITEMS_BORDER_WIDTH");
    JS_AddModuleExport(ctx, m, "COLOR_SELECTOR_SIZE");
    JS_AddModuleExport(ctx, m, "HUEBAR_WIDTH");
    JS_AddModuleExport(ctx, m, "HUEBAR_PADDING");
    JS_AddModuleExport(ctx, m, "HUEBAR_SELECTOR_HEIGHT");
    JS_AddModuleExport(ctx, m, "HUEBAR_SELECTOR_OVERFLOW");
    JS_AddModuleExport(ctx, m, "ICON_NONE");
    JS_AddModuleExport(ctx, m, "ICON_FOLDER_FILE_OPEN");
    JS_AddModuleExport(ctx, m, "ICON_FILE_SAVE_CLASSIC");
    JS_AddModuleExport(ctx, m, "ICON_FOLDER_OPEN");
    JS_AddModuleExport(ctx, m, "ICON_FOLDER_SAVE");
    JS_AddModuleExport(ctx, m, "ICON_FILE_OPEN");
    JS_AddModuleExport(ctx, m, "ICON_FILE_SAVE");
    JS_AddModuleExport(ctx, m, "ICON_FILE_EXPORT");
    JS_AddModuleExport(ctx, m, "ICON_FILE_ADD");
    JS_AddModuleExport(ctx, m, "ICON_FILE_DELETE");
    JS_AddModuleExport(ctx, m, "ICON_FILETYPE_TEXT");
    JS_AddModuleExport(ctx, m, "ICON_FILETYPE_AUDIO");
    JS_AddModuleExport(ctx, m, "ICON_FILETYPE_IMAGE");
    JS_AddModuleExport(ctx, m, "ICON_FILETYPE_PLAY");
    JS_AddModuleExport(ctx, m, "ICON_FILETYPE_VIDEO");
    JS_AddModuleExport(ctx, m, "ICON_FILETYPE_INFO");
    JS_AddModuleExport(ctx, m, "ICON_FILE_COPY");
    JS_AddModuleExport(ctx, m, "ICON_FILE_CUT");
    JS_AddModuleExport(ctx, m, "ICON_FILE_PASTE");
    JS_AddModuleExport(ctx, m, "ICON_CURSOR_HAND");
    JS_AddModuleExport(ctx, m, "ICON_CURSOR_POINTER");
    JS_AddModuleExport(ctx, m, "ICON_CURSOR_CLASSIC");
    JS_AddModuleExport(ctx, m, "ICON_PENCIL");
    JS_AddModuleExport(ctx, m, "ICON_PENCIL_BIG");
    JS_AddModuleExport(ctx, m, "ICON_BRUSH_CLASSIC");
    JS_AddModuleExport(ctx, m, "ICON_BRUSH_PAINTER");
    JS_AddModuleExport(ctx, m, "ICON_WATER_DROP");
    JS_AddModuleExport(ctx, m, "ICON_COLOR_PICKER");
    JS_AddModuleExport(ctx, m, "ICON_RUBBER");
    JS_AddModuleExport(ctx, m, "ICON_COLOR_BUCKET");
    JS_AddModuleExport(ctx, m, "ICON_TEXT_T");
    JS_AddModuleExport(ctx, m, "ICON_TEXT_A");
    JS_AddModuleExport(ctx, m, "ICON_SCALE");
    JS_AddModuleExport(ctx, m, "ICON_RESIZE");
    JS_AddModuleExport(ctx, m, "ICON_FILTER_POINT");
    JS_AddModuleExport(ctx, m, "ICON_FILTER_BILINEAR");
    JS_AddModuleExport(ctx, m, "ICON_CROP");
    JS_AddModuleExport(ctx, m, "ICON_CROP_ALPHA");
    JS_AddModuleExport(ctx, m, "ICON_SQUARE_TOGGLE");
    JS_AddModuleExport(ctx, m, "ICON_SYMMETRY");
    JS_AddModuleExport(ctx, m, "ICON_SYMMETRY_HORIZONTAL");
    JS_AddModuleExport(ctx, m, "ICON_SYMMETRY_VERTICAL");
    JS_AddModuleExport(ctx, m, "ICON_LENS");
    JS_AddModuleExport(ctx, m, "ICON_LENS_BIG");
    JS_AddModuleExport(ctx, m, "ICON_EYE_ON");
    JS_AddModuleExport(ctx, m, "ICON_EYE_OFF");
    JS_AddModuleExport(ctx, m, "ICON_FILTER_TOP");
    JS_AddModuleExport(ctx, m, "ICON_FILTER");
    JS_AddModuleExport(ctx, m, "ICON_TARGET_POINT");
    JS_AddModuleExport(ctx, m, "ICON_TARGET_SMALL");
    JS_AddModuleExport(ctx, m, "ICON_TARGET_BIG");
    JS_AddModuleExport(ctx, m, "ICON_TARGET_MOVE");
    JS_AddModuleExport(ctx, m, "ICON_CURSOR_MOVE");
    JS_AddModuleExport(ctx, m, "ICON_CURSOR_SCALE");
    JS_AddModuleExport(ctx, m, "ICON_CURSOR_SCALE_RIGHT");
    JS_AddModuleExport(ctx, m, "ICON_CURSOR_SCALE_LEFT");
    JS_AddModuleExport(ctx, m, "ICON_UNDO");
    JS_AddModuleExport(ctx, m, "ICON_REDO");
    JS_AddModuleExport(ctx, m, "ICON_REREDO");
    JS_AddModuleExport(ctx, m, "ICON_MUTATE");
    JS_AddModuleExport(ctx, m, "ICON_ROTATE");
    JS_AddModuleExport(ctx, m, "ICON_REPEAT");
    JS_AddModuleExport(ctx, m, "ICON_SHUFFLE");
    JS_AddModuleExport(ctx, m, "ICON_EMPTYBOX");
    JS_AddModuleExport(ctx, m, "ICON_TARGET");
    JS_AddModuleExport(ctx, m, "ICON_TARGET_SMALL_FILL");
    JS_AddModuleExport(ctx, m, "ICON_TARGET_BIG_FILL");
    JS_AddModuleExport(ctx, m, "ICON_TARGET_MOVE_FILL");
    JS_AddModuleExport(ctx, m, "ICON_CURSOR_MOVE_FILL");
    JS_AddModuleExport(ctx, m, "ICON_CURSOR_SCALE_FILL");
    JS_AddModuleExport(ctx, m, "ICON_CURSOR_SCALE_RIGHT_FILL");
    JS_AddModuleExport(ctx, m, "ICON_CURSOR_SCALE_LEFT_FILL");
    JS_AddModuleExport(ctx, m, "ICON_UNDO_FILL");
    JS_AddModuleExport(ctx, m, "ICON_REDO_FILL");
    JS_AddModuleExport(ctx, m, "ICON_REREDO_FILL");
    JS_AddModuleExport(ctx, m, "ICON_MUTATE_FILL");
    JS_AddModuleExport(ctx, m, "ICON_ROTATE_FILL");
    JS_AddModuleExport(ctx, m, "ICON_REPEAT_FILL");
    JS_AddModuleExport(ctx, m, "ICON_SHUFFLE_FILL");
    JS_AddModuleExport(ctx, m, "ICON_EMPTYBOX_SMALL");
    JS_AddModuleExport(ctx, m, "ICON_BOX");
    JS_AddModuleExport(ctx, m, "ICON_BOX_TOP");
    JS_AddModuleExport(ctx, m, "ICON_BOX_TOP_RIGHT");
    JS_AddModuleExport(ctx, m, "ICON_BOX_RIGHT");
    JS_AddModuleExport(ctx, m, "ICON_BOX_BOTTOM_RIGHT");
    JS_AddModuleExport(ctx, m, "ICON_BOX_BOTTOM");
    JS_AddModuleExport(ctx, m, "ICON_BOX_BOTTOM_LEFT");
    JS_AddModuleExport(ctx, m, "ICON_BOX_LEFT");
    JS_AddModuleExport(ctx, m, "ICON_BOX_TOP_LEFT");
    JS_AddModuleExport(ctx, m, "ICON_BOX_CENTER");
    JS_AddModuleExport(ctx, m, "ICON_BOX_CIRCLE_MASK");
    JS_AddModuleExport(ctx, m, "ICON_POT");
    JS_AddModuleExport(ctx, m, "ICON_ALPHA_MULTIPLY");
    JS_AddModuleExport(ctx, m, "ICON_ALPHA_CLEAR");
    JS_AddModuleExport(ctx, m, "ICON_DITHERING");
    JS_AddModuleExport(ctx, m, "ICON_MIPMAPS");
    JS_AddModuleExport(ctx, m, "ICON_BOX_GRID");
    JS_AddModuleExport(ctx, m, "ICON_GRID");
    JS_AddModuleExport(ctx, m, "ICON_BOX_CORNERS_SMALL");
    JS_AddModuleExport(ctx, m, "ICON_BOX_CORNERS_BIG");
    JS_AddModuleExport(ctx, m, "ICON_FOUR_BOXES");
    JS_AddModuleExport(ctx, m, "ICON_GRID_FILL");
    JS_AddModuleExport(ctx, m, "ICON_BOX_MULTISIZE");
    JS_AddModuleExport(ctx, m, "ICON_ZOOM_SMALL");
    JS_AddModuleExport(ctx, m, "ICON_ZOOM_MEDIUM");
    JS_AddModuleExport(ctx, m, "ICON_ZOOM_BIG");
    JS_AddModuleExport(ctx, m, "ICON_ZOOM_ALL");
    JS_AddModuleExport(ctx, m, "ICON_ZOOM_CENTER");
    JS_AddModuleExport(ctx, m, "ICON_BOX_DOTS_SMALL");
    JS_AddModuleExport(ctx, m, "ICON_BOX_DOTS_BIG");
    JS_AddModuleExport(ctx, m, "ICON_BOX_CONCENTRIC");
    JS_AddModuleExport(ctx, m, "ICON_BOX_GRID_BIG");
    JS_AddModuleExport(ctx, m, "ICON_OK_TICK");
    JS_AddModuleExport(ctx, m, "ICON_CROSS");
    JS_AddModuleExport(ctx, m, "ICON_ARROW_LEFT");
    JS_AddModuleExport(ctx, m, "ICON_ARROW_RIGHT");
    JS_AddModuleExport(ctx, m, "ICON_ARROW_DOWN");
    JS_AddModuleExport(ctx, m, "ICON_ARROW_UP");
    JS_AddModuleExport(ctx, m, "ICON_ARROW_LEFT_FILL");
    JS_AddModuleExport(ctx, m, "ICON_ARROW_RIGHT_FILL");
    JS_AddModuleExport(ctx, m, "ICON_ARROW_DOWN_FILL");
    JS_AddModuleExport(ctx, m, "ICON_ARROW_UP_FILL");
    JS_AddModuleExport(ctx, m, "ICON_AUDIO");
    JS_AddModuleExport(ctx, m, "ICON_FX");
    JS_AddModuleExport(ctx, m, "ICON_WAVE");
    JS_AddModuleExport(ctx, m, "ICON_WAVE_SINUS");
    JS_AddModuleExport(ctx, m, "ICON_WAVE_SQUARE");
    JS_AddModuleExport(ctx, m, "ICON_WAVE_TRIANGULAR");
    JS_AddModuleExport(ctx, m, "ICON_CROSS_SMALL");
    JS_AddModuleExport(ctx, m, "ICON_PLAYER_PREVIOUS");
    JS_AddModuleExport(ctx, m, "ICON_PLAYER_PLAY_BACK");
    JS_AddModuleExport(ctx, m, "ICON_PLAYER_PLAY");
    JS_AddModuleExport(ctx, m, "ICON_PLAYER_PAUSE");
    JS_AddModuleExport(ctx, m, "ICON_PLAYER_STOP");
    JS_AddModuleExport(ctx, m, "ICON_PLAYER_NEXT");
    JS_AddModuleExport(ctx, m, "ICON_PLAYER_RECORD");
    JS_AddModuleExport(ctx, m, "ICON_MAGNET");
    JS_AddModuleExport(ctx, m, "ICON_LOCK_CLOSE");
    JS_AddModuleExport(ctx, m, "ICON_LOCK_OPEN");
    JS_AddModuleExport(ctx, m, "ICON_CLOCK");
    JS_AddModuleExport(ctx, m, "ICON_TOOLS");
    JS_AddModuleExport(ctx, m, "ICON_GEAR");
    JS_AddModuleExport(ctx, m, "ICON_GEAR_BIG");
    JS_AddModuleExport(ctx, m, "ICON_BIN");
    JS_AddModuleExport(ctx, m, "ICON_HAND_POINTER");
    JS_AddModuleExport(ctx, m, "ICON_LASER");
    JS_AddModuleExport(ctx, m, "ICON_COIN");
    JS_AddModuleExport(ctx, m, "ICON_EXPLOSION");
    JS_AddModuleExport(ctx, m, "ICON_1UP");
    JS_AddModuleExport(ctx, m, "ICON_PLAYER");
    JS_AddModuleExport(ctx, m, "ICON_PLAYER_JUMP");
    JS_AddModuleExport(ctx, m, "ICON_KEY");
    JS_AddModuleExport(ctx, m, "ICON_DEMON");
    JS_AddModuleExport(ctx, m, "ICON_TEXT_POPUP");
    JS_AddModuleExport(ctx, m, "ICON_GEAR_EX");
    JS_AddModuleExport(ctx, m, "ICON_CRACK");
    JS_AddModuleExport(ctx, m, "ICON_CRACK_POINTS");
    JS_AddModuleExport(ctx, m, "ICON_STAR");
    JS_AddModuleExport(ctx, m, "ICON_DOOR");
    JS_AddModuleExport(ctx, m, "ICON_EXIT");
    JS_AddModuleExport(ctx, m, "ICON_MODE_2D");
    JS_AddModuleExport(ctx, m, "ICON_MODE_3D");
    JS_AddModuleExport(ctx, m, "ICON_CUBE");
    JS_AddModuleExport(ctx, m, "ICON_CUBE_FACE_TOP");
    JS_AddModuleExport(ctx, m, "ICON_CUBE_FACE_LEFT");
    JS_AddModuleExport(ctx, m, "ICON_CUBE_FACE_FRONT");
    JS_AddModuleExport(ctx, m, "ICON_CUBE_FACE_BOTTOM");
    JS_AddModuleExport(ctx, m, "ICON_CUBE_FACE_RIGHT");
    JS_AddModuleExport(ctx, m, "ICON_CUBE_FACE_BACK");
    JS_AddModuleExport(ctx, m, "ICON_CAMERA");
    JS_AddModuleExport(ctx, m, "ICON_SPECIAL");
    JS_AddModuleExport(ctx, m, "ICON_LINK_NET");
    JS_AddModuleExport(ctx, m, "ICON_LINK_BOXES");
    JS_AddModuleExport(ctx, m, "ICON_LINK_MULTI");
    JS_AddModuleExport(ctx, m, "ICON_LINK");
    JS_AddModuleExport(ctx, m, "ICON_LINK_BROKE");
    JS_AddModuleExport(ctx, m, "ICON_TEXT_NOTES");
    JS_AddModuleExport(ctx, m, "ICON_NOTEBOOK");
    JS_AddModuleExport(ctx, m, "ICON_SUITCASE");
    JS_AddModuleExport(ctx, m, "ICON_SUITCASE_ZIP");
    JS_AddModuleExport(ctx, m, "ICON_MAILBOX");
    JS_AddModuleExport(ctx, m, "ICON_MONITOR");
    JS_AddModuleExport(ctx, m, "ICON_PRINTER");
    JS_AddModuleExport(ctx, m, "ICON_PHOTO_CAMERA");
    JS_AddModuleExport(ctx, m, "ICON_PHOTO_CAMERA_FLASH");
    JS_AddModuleExport(ctx, m, "ICON_HOUSE");
    JS_AddModuleExport(ctx, m, "ICON_HEART");
    JS_AddModuleExport(ctx, m, "ICON_CORNER");
    JS_AddModuleExport(ctx, m, "ICON_VERTICAL_BARS");
    JS_AddModuleExport(ctx, m, "ICON_VERTICAL_BARS_FILL");
    JS_AddModuleExport(ctx, m, "ICON_LIFE_BARS");
    JS_AddModuleExport(ctx, m, "ICON_INFO");
    JS_AddModuleExport(ctx, m, "ICON_CROSSLINE");
    JS_AddModuleExport(ctx, m, "ICON_HELP");
    JS_AddModuleExport(ctx, m, "ICON_FILETYPE_ALPHA");
    JS_AddModuleExport(ctx, m, "ICON_FILETYPE_HOME");
    JS_AddModuleExport(ctx, m, "ICON_LAYERS_VISIBLE");
    JS_AddModuleExport(ctx, m, "ICON_LAYERS");
    JS_AddModuleExport(ctx, m, "ICON_WINDOW");
    JS_AddModuleExport(ctx, m, "ICON_HIDPI");
    JS_AddModuleExport(ctx, m, "ICON_FILETYPE_BINARY");
    JS_AddModuleExport(ctx, m, "ICON_HEX");
    JS_AddModuleExport(ctx, m, "ICON_SHIELD");
    JS_AddModuleExport(ctx, m, "ICON_FILE_NEW");
    JS_AddModuleExport(ctx, m, "ICON_FOLDER_ADD");
    JS_AddModuleExport(ctx, m, "ICON_ALARM");
    JS_AddModuleExport(ctx, m, "ICON_CPU");
    JS_AddModuleExport(ctx, m, "ICON_ROM");
    JS_AddModuleExport(ctx, m, "ICON_STEP_OVER");
    JS_AddModuleExport(ctx, m, "ICON_STEP_INTO");
    JS_AddModuleExport(ctx, m, "ICON_STEP_OUT");
    JS_AddModuleExport(ctx, m, "ICON_RESTART");
    JS_AddModuleExport(ctx, m, "ICON_BREAKPOINT_ON");
    JS_AddModuleExport(ctx, m, "ICON_BREAKPOINT_OFF");
    JS_AddModuleExport(ctx, m, "ICON_BURGER_MENU");
    JS_AddModuleExport(ctx, m, "ICON_CASE_SENSITIVE");
    JS_AddModuleExport(ctx, m, "ICON_REG_EXP");
    JS_AddModuleExport(ctx, m, "ICON_FOLDER");
    JS_AddModuleExport(ctx, m, "ICON_FILE");
    JS_AddModuleExport(ctx, m, "ICON_SAND_TIMER");
    JS_AddModuleExport(ctx, m, "ICON_WARNING");
    JS_AddModuleExport(ctx, m, "ICON_HELP_BOX");
    JS_AddModuleExport(ctx, m, "ICON_INFO_BOX");
    JS_AddModuleExport(ctx, m, "ICON_PRIORITY");
    JS_AddModuleExport(ctx, m, "ICON_LAYERS_ISO");
    JS_AddModuleExport(ctx, m, "ICON_LAYERS2");
    JS_AddModuleExport(ctx, m, "ICON_MLAYERS");
    JS_AddModuleExport(ctx, m, "ICON_MAPS");
    JS_AddModuleExport(ctx, m, "ICON_HOT");
    JS_AddModuleExport(ctx, m, "ICON_229");
    JS_AddModuleExport(ctx, m, "ICON_230");
    JS_AddModuleExport(ctx, m, "ICON_231");
    JS_AddModuleExport(ctx, m, "ICON_232");
    JS_AddModuleExport(ctx, m, "ICON_233");
    JS_AddModuleExport(ctx, m, "ICON_234");
    JS_AddModuleExport(ctx, m, "ICON_235");
    JS_AddModuleExport(ctx, m, "ICON_236");
    JS_AddModuleExport(ctx, m, "ICON_237");
    JS_AddModuleExport(ctx, m, "ICON_238");
    JS_AddModuleExport(ctx, m, "ICON_239");
    JS_AddModuleExport(ctx, m, "ICON_240");
    JS_AddModuleExport(ctx, m, "ICON_241");
    JS_AddModuleExport(ctx, m, "ICON_242");
    JS_AddModuleExport(ctx, m, "ICON_243");
    JS_AddModuleExport(ctx, m, "ICON_244");
    JS_AddModuleExport(ctx, m, "ICON_245");
    JS_AddModuleExport(ctx, m, "ICON_246");
    JS_AddModuleExport(ctx, m, "ICON_247");
    JS_AddModuleExport(ctx, m, "ICON_248");
    JS_AddModuleExport(ctx, m, "ICON_249");
    JS_AddModuleExport(ctx, m, "ICON_250");
    JS_AddModuleExport(ctx, m, "ICON_251");
    JS_AddModuleExport(ctx, m, "ICON_252");
    JS_AddModuleExport(ctx, m, "ICON_253");
    JS_AddModuleExport(ctx, m, "ICON_254");
    JS_AddModuleExport(ctx, m, "ICON_255");
    JS_AddModuleExport(ctx, m, "LIGHT_DIRECTIONAL");
    JS_AddModuleExport(ctx, m, "LIGHT_POINT");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_DIFFUSE");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_SPECULAR");
    return m;
}

#endif // JS_raylib_core_GUARD
