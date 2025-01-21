#ifndef JS_js_raymath_GUARD
#define JS_js_raymath_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <quickjs.h>
#include <rayjs_base.h>
#include <raymath.h>
#include <raylib.h>

static JSClassID js_float3_class_id;
static JSClassID js_float16_class_id;
static JSClassID js_float3_class_id;
static JSClassID js_float16_class_id;

static void js_float3_finalizer(JSRuntime * rt, JSValue val) {
    float3* ptr = JS_GetOpaque(val, js_float3_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_float3_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","float3", JS_PROP_CONFIGURABLE),
};

static int js_declare_float3(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_float3_class_id);
    JSClassDef js_float3_def = { .class_name = "float3", .finalizer = js_float3_finalizer };
    JS_NewClass(rt, js_float3_class_id, &js_float3_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_float3_proto_funcs, countof(js_float3_proto_funcs));
    JS_SetClassProto(ctx, js_float3_class_id, proto);
    return 0;
}

static void js_float16_finalizer(JSRuntime * rt, JSValue val) {
    float16* ptr = JS_GetOpaque(val, js_float16_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_float16_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","float16", JS_PROP_CONFIGURABLE),
};

static int js_declare_float16(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_float16_class_id);
    JSClassDef js_float16_def = { .class_name = "float16", .finalizer = js_float16_finalizer };
    JS_NewClass(rt, js_float16_class_id, &js_float16_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_float16_proto_funcs, countof(js_float16_proto_funcs));
    JS_SetClassProto(ctx, js_float16_class_id, proto);
    return 0;
}

static JSValue js_clamp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, argv[0]);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    double double_min;
    int err_min = JS_ToFloat64(ctx, &double_min, argv[1]);
    if(err_min<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float min = (float)double_min;
    double double_max;
    int err_max = JS_ToFloat64(ctx, &double_max, argv[2]);
    if(err_max<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float max = (float)double_max;
    float returnVal = Clamp(value, min, max);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_lerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_start;
    int err_start = JS_ToFloat64(ctx, &double_start, argv[0]);
    if(err_start<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float start = (float)double_start;
    double double_end;
    int err_end = JS_ToFloat64(ctx, &double_end, argv[1]);
    if(err_end<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float end = (float)double_end;
    double double_amount;
    int err_amount = JS_ToFloat64(ctx, &double_amount, argv[2]);
    if(err_amount<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float amount = (float)double_amount;
    float returnVal = Lerp(start, end, amount);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_normalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, argv[0]);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    double double_start;
    int err_start = JS_ToFloat64(ctx, &double_start, argv[1]);
    if(err_start<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float start = (float)double_start;
    double double_end;
    int err_end = JS_ToFloat64(ctx, &double_end, argv[2]);
    if(err_end<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float end = (float)double_end;
    float returnVal = Normalize(value, start, end);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_remap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, argv[0]);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    double double_inputStart;
    int err_inputStart = JS_ToFloat64(ctx, &double_inputStart, argv[1]);
    if(err_inputStart<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float inputStart = (float)double_inputStart;
    double double_inputEnd;
    int err_inputEnd = JS_ToFloat64(ctx, &double_inputEnd, argv[2]);
    if(err_inputEnd<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float inputEnd = (float)double_inputEnd;
    double double_outputStart;
    int err_outputStart = JS_ToFloat64(ctx, &double_outputStart, argv[3]);
    if(err_outputStart<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float outputStart = (float)double_outputStart;
    double double_outputEnd;
    int err_outputEnd = JS_ToFloat64(ctx, &double_outputEnd, argv[4]);
    if(err_outputEnd<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float outputEnd = (float)double_outputEnd;
    float returnVal = Remap(value, inputStart, inputEnd, outputStart, outputEnd);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_wrap(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_value;
    int err_value = JS_ToFloat64(ctx, &double_value, argv[0]);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float value = (float)double_value;
    double double_min;
    int err_min = JS_ToFloat64(ctx, &double_min, argv[1]);
    if(err_min<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float min = (float)double_min;
    double double_max;
    int err_max = JS_ToFloat64(ctx, &double_max, argv[2]);
    if(err_max<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float max = (float)double_max;
    float returnVal = Wrap(value, min, max);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_floatEquals(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    int returnVal = FloatEquals(x, y);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_vector2Zero(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = Vector2Zero();
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2One(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2 returnVal = Vector2One();
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Add(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector2 returnVal = Vector2Add(v1, v2);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2AddValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    double double_add;
    int err_add = JS_ToFloat64(ctx, &double_add, argv[1]);
    if(err_add<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float add = (float)double_add;
    Vector2 returnVal = Vector2AddValue(v, add);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Subtract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector2 returnVal = Vector2Subtract(v1, v2);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2SubtractValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    double double_sub;
    int err_sub = JS_ToFloat64(ctx, &double_sub, argv[1]);
    if(err_sub<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float sub = (float)double_sub;
    Vector2 returnVal = Vector2SubtractValue(v, sub);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Length(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    float returnVal = Vector2Length(v);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector2LengthSqr(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    float returnVal = Vector2LengthSqr(v);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector2DotProduct(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    float returnVal = Vector2DotProduct(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector2CrossProduct(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    float returnVal = Vector2CrossProduct(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector2Distance(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    float returnVal = Vector2Distance(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector2DistanceSqr(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    float returnVal = Vector2DistanceSqr(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector2Angle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    float returnVal = Vector2Angle(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector2LineAngle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_start = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_start == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 start = *ptr_start;
    Vector2* ptr_end = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_end == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 end = *ptr_end;
    float returnVal = Vector2LineAngle(start, end);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector2Scale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    double double_scale;
    int err_scale = JS_ToFloat64(ctx, &double_scale, argv[1]);
    if(err_scale<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float scale = (float)double_scale;
    Vector2 returnVal = Vector2Scale(v, scale);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Multiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector2 returnVal = Vector2Multiply(v1, v2);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Negate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    Vector2 returnVal = Vector2Negate(v);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Divide(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector2 returnVal = Vector2Divide(v1, v2);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Normalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    Vector2 returnVal = Vector2Normalize(v);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Transform(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    Matrix* ptr_mat = (Matrix*)JS_GetOpaque(argv[1], js_Matrix_class_id);
    if(ptr_mat == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix mat = *ptr_mat;
    Vector2 returnVal = Vector2Transform(v, mat);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Lerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    double double_amount;
    int err_amount = JS_ToFloat64(ctx, &double_amount, argv[2]);
    if(err_amount<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float amount = (float)double_amount;
    Vector2 returnVal = Vector2Lerp(v1, v2, amount);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Reflect(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    Vector2* ptr_normal = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_normal == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 normal = *ptr_normal;
    Vector2 returnVal = Vector2Reflect(v, normal);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Min(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector2 returnVal = Vector2Min(v1, v2);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Max(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector2 returnVal = Vector2Max(v1, v2);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Rotate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    double double_angle;
    int err_angle = JS_ToFloat64(ctx, &double_angle, argv[1]);
    if(err_angle<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float angle = (float)double_angle;
    Vector2 returnVal = Vector2Rotate(v, angle);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2MoveTowards(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    Vector2* ptr_target = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_target == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 target = *ptr_target;
    double double_maxDistance;
    int err_maxDistance = JS_ToFloat64(ctx, &double_maxDistance, argv[2]);
    if(err_maxDistance<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float maxDistance = (float)double_maxDistance;
    Vector2 returnVal = Vector2MoveTowards(v, target, maxDistance);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Invert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    Vector2 returnVal = Vector2Invert(v);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Clamp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    Vector2* ptr_min = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_min == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 min = *ptr_min;
    Vector2* ptr_max = (Vector2*)JS_GetOpaque(argv[2], js_Vector2_class_id);
    if(ptr_max == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 max = *ptr_max;
    Vector2 returnVal = Vector2Clamp(v, min, max);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2ClampValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    double double_min;
    int err_min = JS_ToFloat64(ctx, &double_min, argv[1]);
    if(err_min<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float min = (float)double_min;
    double double_max;
    int err_max = JS_ToFloat64(ctx, &double_max, argv[2]);
    if(err_max<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float max = (float)double_max;
    Vector2 returnVal = Vector2ClampValue(v, min, max);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector2Equals(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_p = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_p == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 p = *ptr_p;
    Vector2* ptr_q = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 q = *ptr_q;
    int returnVal = Vector2Equals(p, q);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_vector2Refract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector2* ptr_v = (Vector2*)JS_GetOpaque(argv[0], js_Vector2_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 v = *ptr_v;
    Vector2* ptr_n = (Vector2*)JS_GetOpaque(argv[1], js_Vector2_class_id);
    if(ptr_n == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector2 n = *ptr_n;
    double double_r;
    int err_r = JS_ToFloat64(ctx, &double_r, argv[2]);
    if(err_r<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float r = (float)double_r;
    Vector2 returnVal = Vector2Refract(v, n, r);
    Vector2* ptr_ret = (Vector2*)js_malloc(ctx, sizeof(Vector2));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Zero(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3 returnVal = Vector3Zero();
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3One(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3 returnVal = Vector3One();
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Add(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector3 returnVal = Vector3Add(v1, v2);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3AddValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    double double_add;
    int err_add = JS_ToFloat64(ctx, &double_add, argv[1]);
    if(err_add<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float add = (float)double_add;
    Vector3 returnVal = Vector3AddValue(v, add);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Subtract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector3 returnVal = Vector3Subtract(v1, v2);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3SubtractValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    double double_sub;
    int err_sub = JS_ToFloat64(ctx, &double_sub, argv[1]);
    if(err_sub<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float sub = (float)double_sub;
    Vector3 returnVal = Vector3SubtractValue(v, sub);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Scale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    double double_scalar;
    int err_scalar = JS_ToFloat64(ctx, &double_scalar, argv[1]);
    if(err_scalar<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float scalar = (float)double_scalar;
    Vector3 returnVal = Vector3Scale(v, scalar);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Multiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector3 returnVal = Vector3Multiply(v1, v2);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3CrossProduct(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector3 returnVal = Vector3CrossProduct(v1, v2);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Perpendicular(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    Vector3 returnVal = Vector3Perpendicular(v);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Length(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    float returnVal = Vector3Length((const Vector3)v);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector3LengthSqr(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    float returnVal = Vector3LengthSqr((const Vector3)v);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector3DotProduct(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    float returnVal = Vector3DotProduct(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector3Distance(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    float returnVal = Vector3Distance(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector3DistanceSqr(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    float returnVal = Vector3DistanceSqr(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector3Angle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    float returnVal = Vector3Angle(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector3Negate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    Vector3 returnVal = Vector3Negate(v);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Divide(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector3 returnVal = Vector3Divide(v1, v2);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Normalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    Vector3 returnVal = Vector3Normalize(v);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Project(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector3 returnVal = Vector3Project(v1, v2);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Reject(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector3 returnVal = Vector3Reject(v1, v2);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3OrthoNormalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3 * v1 = (Vector3 *)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not match type Vector3");
        return JS_EXCEPTION;
    }
    Vector3 * v2 = (Vector3 *)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not match type Vector3");
        return JS_EXCEPTION;
    }
    Vector3OrthoNormalize(v1, v2);
    return JS_UNDEFINED;
}

static JSValue js_vector3Transform(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    Matrix* ptr_mat = (Matrix*)JS_GetOpaque(argv[1], js_Matrix_class_id);
    if(ptr_mat == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix mat = *ptr_mat;
    Vector3 returnVal = Vector3Transform(v, mat);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3RotateByQuaternion(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    Vector3 returnVal = Vector3RotateByQuaternion(v, q);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3RotateByAxisAngle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    Vector3* ptr_axis = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_axis == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 axis = *ptr_axis;
    double double_angle;
    int err_angle = JS_ToFloat64(ctx, &double_angle, argv[2]);
    if(err_angle<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float angle = (float)double_angle;
    Vector3 returnVal = Vector3RotateByAxisAngle(v, axis, angle);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3MoveTowards(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    Vector3* ptr_target = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_target == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 target = *ptr_target;
    double double_maxDistance;
    int err_maxDistance = JS_ToFloat64(ctx, &double_maxDistance, argv[2]);
    if(err_maxDistance<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float maxDistance = (float)double_maxDistance;
    Vector3 returnVal = Vector3MoveTowards(v, target, maxDistance);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Lerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    double double_amount;
    int err_amount = JS_ToFloat64(ctx, &double_amount, argv[2]);
    if(err_amount<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float amount = (float)double_amount;
    Vector3 returnVal = Vector3Lerp(v1, v2, amount);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3CubicHermite(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v1 = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v1 = *ptr_v1;
    Vector3* ptr_tangent1 = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_tangent1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 tangent1 = *ptr_tangent1;
    Vector3* ptr_v2 = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v2 = *ptr_v2;
    Vector3* ptr_tangent2 = (Vector3*)JS_GetOpaque(argv[3], js_Vector3_class_id);
    if(ptr_tangent2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 tangent2 = *ptr_tangent2;
    double double_amount;
    int err_amount = JS_ToFloat64(ctx, &double_amount, argv[4]);
    if(err_amount<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float amount = (float)double_amount;
    Vector3 returnVal = Vector3CubicHermite(v1, tangent1, v2, tangent2, amount);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Reflect(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    Vector3* ptr_normal = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_normal == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 normal = *ptr_normal;
    Vector3 returnVal = Vector3Reflect(v, normal);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Min(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector3 returnVal = Vector3Min(v1, v2);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Max(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Vector3 returnVal = Vector3Max(v1, v2);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Barycenter(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_p = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_p == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 p = *ptr_p;
    Vector3* ptr_a = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_a == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 a = *ptr_a;
    Vector3* ptr_b = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_b == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 b = *ptr_b;
    Vector3* ptr_c = (Vector3*)JS_GetOpaque(argv[3], js_Vector3_class_id);
    if(ptr_c == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 c = *ptr_c;
    Vector3 returnVal = Vector3Barycenter(p, a, b, c);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Unproject(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_source = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_source == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 source = *ptr_source;
    Matrix* ptr_projection = (Matrix*)JS_GetOpaque(argv[1], js_Matrix_class_id);
    if(ptr_projection == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix projection = *ptr_projection;
    Matrix* ptr_view = (Matrix*)JS_GetOpaque(argv[2], js_Matrix_class_id);
    if(ptr_view == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix view = *ptr_view;
    Vector3 returnVal = Vector3Unproject(source, projection, view);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Invert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    Vector3 returnVal = Vector3Invert(v);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Clamp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    Vector3* ptr_min = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_min == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 min = *ptr_min;
    Vector3* ptr_max = (Vector3*)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(ptr_max == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 max = *ptr_max;
    Vector3 returnVal = Vector3Clamp(v, min, max);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3ClampValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    double double_min;
    int err_min = JS_ToFloat64(ctx, &double_min, argv[1]);
    if(err_min<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float min = (float)double_min;
    double double_max;
    int err_max = JS_ToFloat64(ctx, &double_max, argv[2]);
    if(err_max<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float max = (float)double_max;
    Vector3 returnVal = Vector3ClampValue(v, min, max);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector3Equals(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_p = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_p == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 p = *ptr_p;
    Vector3* ptr_q = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 q = *ptr_q;
    int returnVal = Vector3Equals(p, q);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_vector3Refract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_v = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 v = *ptr_v;
    Vector3* ptr_n = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_n == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 n = *ptr_n;
    double double_r;
    int err_r = JS_ToFloat64(ctx, &double_r, argv[2]);
    if(err_r<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float r = (float)double_r;
    Vector3 returnVal = Vector3Refract(v, n, r);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Zero(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4 returnVal = Vector4Zero();
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4One(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4 returnVal = Vector4One();
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Add(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v1 = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v1 = *ptr_v1;
    Vector4* ptr_v2 = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v2 = *ptr_v2;
    Vector4 returnVal = Vector4Add(v1, v2);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4AddValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v = *ptr_v;
    double double_add;
    int err_add = JS_ToFloat64(ctx, &double_add, argv[1]);
    if(err_add<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float add = (float)double_add;
    Vector4 returnVal = Vector4AddValue(v, add);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Subtract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v1 = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v1 = *ptr_v1;
    Vector4* ptr_v2 = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v2 = *ptr_v2;
    Vector4 returnVal = Vector4Subtract(v1, v2);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4SubtractValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v = *ptr_v;
    double double_add;
    int err_add = JS_ToFloat64(ctx, &double_add, argv[1]);
    if(err_add<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float add = (float)double_add;
    Vector4 returnVal = Vector4SubtractValue(v, add);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Length(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v = *ptr_v;
    float returnVal = Vector4Length(v);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector4LengthSqr(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v = *ptr_v;
    float returnVal = Vector4LengthSqr(v);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector4DotProduct(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v1 = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v1 = *ptr_v1;
    Vector4* ptr_v2 = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v2 = *ptr_v2;
    float returnVal = Vector4DotProduct(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector4Distance(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v1 = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v1 = *ptr_v1;
    Vector4* ptr_v2 = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v2 = *ptr_v2;
    float returnVal = Vector4Distance(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector4DistanceSqr(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v1 = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v1 = *ptr_v1;
    Vector4* ptr_v2 = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v2 = *ptr_v2;
    float returnVal = Vector4DistanceSqr(v1, v2);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_vector4Scale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v = *ptr_v;
    double double_scale;
    int err_scale = JS_ToFloat64(ctx, &double_scale, argv[1]);
    if(err_scale<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float scale = (float)double_scale;
    Vector4 returnVal = Vector4Scale(v, scale);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Multiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v1 = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v1 = *ptr_v1;
    Vector4* ptr_v2 = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v2 = *ptr_v2;
    Vector4 returnVal = Vector4Multiply(v1, v2);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Negate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v = *ptr_v;
    Vector4 returnVal = Vector4Negate(v);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Divide(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v1 = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v1 = *ptr_v1;
    Vector4* ptr_v2 = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v2 = *ptr_v2;
    Vector4 returnVal = Vector4Divide(v1, v2);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Normalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v = *ptr_v;
    Vector4 returnVal = Vector4Normalize(v);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Min(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v1 = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v1 = *ptr_v1;
    Vector4* ptr_v2 = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v2 = *ptr_v2;
    Vector4 returnVal = Vector4Min(v1, v2);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Max(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v1 = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v1 = *ptr_v1;
    Vector4* ptr_v2 = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v2 = *ptr_v2;
    Vector4 returnVal = Vector4Max(v1, v2);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Lerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v1 = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v1 = *ptr_v1;
    Vector4* ptr_v2 = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_v2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v2 = *ptr_v2;
    double double_amount;
    int err_amount = JS_ToFloat64(ctx, &double_amount, argv[2]);
    if(err_amount<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float amount = (float)double_amount;
    Vector4 returnVal = Vector4Lerp(v1, v2, amount);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4MoveTowards(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v = *ptr_v;
    Vector4* ptr_target = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_target == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 target = *ptr_target;
    double double_maxDistance;
    int err_maxDistance = JS_ToFloat64(ctx, &double_maxDistance, argv[2]);
    if(err_maxDistance<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float maxDistance = (float)double_maxDistance;
    Vector4 returnVal = Vector4MoveTowards(v, target, maxDistance);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Invert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_v = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_v == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 v = *ptr_v;
    Vector4 returnVal = Vector4Invert(v);
    Vector4* ptr_ret = (Vector4*)js_malloc(ctx, sizeof(Vector4));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_vector4Equals(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector4* ptr_p = (Vector4*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_p == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 p = *ptr_p;
    Vector4* ptr_q = (Vector4*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector4 q = *ptr_q;
    int returnVal = Vector4Equals(p, q);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_matrixDeterminant(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* ptr_mat = (Matrix*)JS_GetOpaque(argv[0], js_Matrix_class_id);
    if(ptr_mat == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix mat = *ptr_mat;
    float returnVal = MatrixDeterminant(mat);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_matrixTrace(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* ptr_mat = (Matrix*)JS_GetOpaque(argv[0], js_Matrix_class_id);
    if(ptr_mat == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix mat = *ptr_mat;
    float returnVal = MatrixTrace(mat);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_matrixTranspose(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* ptr_mat = (Matrix*)JS_GetOpaque(argv[0], js_Matrix_class_id);
    if(ptr_mat == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix mat = *ptr_mat;
    Matrix returnVal = MatrixTranspose(mat);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixInvert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* ptr_mat = (Matrix*)JS_GetOpaque(argv[0], js_Matrix_class_id);
    if(ptr_mat == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix mat = *ptr_mat;
    Matrix returnVal = MatrixInvert(mat);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixIdentity(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix returnVal = MatrixIdentity();
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixAdd(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* ptr_left = (Matrix*)JS_GetOpaque(argv[0], js_Matrix_class_id);
    if(ptr_left == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix left = *ptr_left;
    Matrix* ptr_right = (Matrix*)JS_GetOpaque(argv[1], js_Matrix_class_id);
    if(ptr_right == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix right = *ptr_right;
    Matrix returnVal = MatrixAdd(left, right);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixSubtract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* ptr_left = (Matrix*)JS_GetOpaque(argv[0], js_Matrix_class_id);
    if(ptr_left == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix left = *ptr_left;
    Matrix* ptr_right = (Matrix*)JS_GetOpaque(argv[1], js_Matrix_class_id);
    if(ptr_right == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix right = *ptr_right;
    Matrix returnVal = MatrixSubtract(left, right);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixMultiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* ptr_left = (Matrix*)JS_GetOpaque(argv[0], js_Matrix_class_id);
    if(ptr_left == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix left = *ptr_left;
    Matrix* ptr_right = (Matrix*)JS_GetOpaque(argv[1], js_Matrix_class_id);
    if(ptr_right == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix right = *ptr_right;
    Matrix returnVal = MatrixMultiply(left, right);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixTranslate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Matrix returnVal = MatrixTranslate(x, y, z);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixRotate(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_axis = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_axis == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 axis = *ptr_axis;
    double double_angle;
    int err_angle = JS_ToFloat64(ctx, &double_angle, argv[1]);
    if(err_angle<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float angle = (float)double_angle;
    Matrix returnVal = MatrixRotate(axis, angle);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixRotateX(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_angle;
    int err_angle = JS_ToFloat64(ctx, &double_angle, argv[0]);
    if(err_angle<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float angle = (float)double_angle;
    Matrix returnVal = MatrixRotateX(angle);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixRotateY(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_angle;
    int err_angle = JS_ToFloat64(ctx, &double_angle, argv[0]);
    if(err_angle<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float angle = (float)double_angle;
    Matrix returnVal = MatrixRotateY(angle);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixRotateZ(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_angle;
    int err_angle = JS_ToFloat64(ctx, &double_angle, argv[0]);
    if(err_angle<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float angle = (float)double_angle;
    Matrix returnVal = MatrixRotateZ(angle);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixRotateXYZ(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_angle = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_angle == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 angle = *ptr_angle;
    Matrix returnVal = MatrixRotateXYZ(angle);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixRotateZYX(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_angle = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_angle == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 angle = *ptr_angle;
    Matrix returnVal = MatrixRotateZYX(angle);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixScale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    Matrix returnVal = MatrixScale(x, y, z);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixFrustum(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double left;
    int err_left = JS_ToFloat64(ctx, &left, argv[0]);
    if(err_left<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    double right;
    int err_right = JS_ToFloat64(ctx, &right, argv[1]);
    if(err_right<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    double bottom;
    int err_bottom = JS_ToFloat64(ctx, &bottom, argv[2]);
    if(err_bottom<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    double top;
    int err_top = JS_ToFloat64(ctx, &top, argv[3]);
    if(err_top<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    double nearPlane;
    int err_nearPlane = JS_ToFloat64(ctx, &nearPlane, argv[4]);
    if(err_nearPlane<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    double farPlane;
    int err_farPlane = JS_ToFloat64(ctx, &farPlane, argv[5]);
    if(err_farPlane<0) {
        JS_ThrowTypeError(ctx, "argv[5] is not numeric");
        return JS_EXCEPTION;
    }
    Matrix returnVal = MatrixFrustum(left, right, bottom, top, nearPlane, farPlane);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixPerspective(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double fovY;
    int err_fovY = JS_ToFloat64(ctx, &fovY, argv[0]);
    if(err_fovY<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    double aspect;
    int err_aspect = JS_ToFloat64(ctx, &aspect, argv[1]);
    if(err_aspect<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    double nearPlane;
    int err_nearPlane = JS_ToFloat64(ctx, &nearPlane, argv[2]);
    if(err_nearPlane<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    double farPlane;
    int err_farPlane = JS_ToFloat64(ctx, &farPlane, argv[3]);
    if(err_farPlane<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    Matrix returnVal = MatrixPerspective(fovY, aspect, nearPlane, farPlane);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixOrtho(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double left;
    int err_left = JS_ToFloat64(ctx, &left, argv[0]);
    if(err_left<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    double right;
    int err_right = JS_ToFloat64(ctx, &right, argv[1]);
    if(err_right<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    double bottom;
    int err_bottom = JS_ToFloat64(ctx, &bottom, argv[2]);
    if(err_bottom<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    double top;
    int err_top = JS_ToFloat64(ctx, &top, argv[3]);
    if(err_top<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    double nearPlane;
    int err_nearPlane = JS_ToFloat64(ctx, &nearPlane, argv[4]);
    if(err_nearPlane<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    double farPlane;
    int err_farPlane = JS_ToFloat64(ctx, &farPlane, argv[5]);
    if(err_farPlane<0) {
        JS_ThrowTypeError(ctx, "argv[5] is not numeric");
        return JS_EXCEPTION;
    }
    Matrix returnVal = MatrixOrtho(left, right, bottom, top, nearPlane, farPlane);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_matrixLookAt(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_eye = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_eye == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 eye = *ptr_eye;
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
    Matrix returnVal = MatrixLookAt(eye, target, up);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionAdd(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q1 = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q1 = *ptr_q1;
    Quaternion* ptr_q2 = (Quaternion*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_q2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q2 = *ptr_q2;
    Quaternion returnVal = QuaternionAdd(q1, q2);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionAddValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    double double_add;
    int err_add = JS_ToFloat64(ctx, &double_add, argv[1]);
    if(err_add<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float add = (float)double_add;
    Quaternion returnVal = QuaternionAddValue(q, add);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionSubtract(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q1 = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q1 = *ptr_q1;
    Quaternion* ptr_q2 = (Quaternion*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_q2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q2 = *ptr_q2;
    Quaternion returnVal = QuaternionSubtract(q1, q2);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionSubtractValue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    double double_sub;
    int err_sub = JS_ToFloat64(ctx, &double_sub, argv[1]);
    if(err_sub<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float sub = (float)double_sub;
    Quaternion returnVal = QuaternionSubtractValue(q, sub);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionIdentity(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion returnVal = QuaternionIdentity();
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionLength(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    float returnVal = QuaternionLength(q);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_quaternionNormalize(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    Quaternion returnVal = QuaternionNormalize(q);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionInvert(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    Quaternion returnVal = QuaternionInvert(q);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionMultiply(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q1 = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q1 = *ptr_q1;
    Quaternion* ptr_q2 = (Quaternion*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_q2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q2 = *ptr_q2;
    Quaternion returnVal = QuaternionMultiply(q1, q2);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionScale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    double double_mul;
    int err_mul = JS_ToFloat64(ctx, &double_mul, argv[1]);
    if(err_mul<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float mul = (float)double_mul;
    Quaternion returnVal = QuaternionScale(q, mul);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionDivide(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q1 = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q1 = *ptr_q1;
    Quaternion* ptr_q2 = (Quaternion*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_q2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q2 = *ptr_q2;
    Quaternion returnVal = QuaternionDivide(q1, q2);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionLerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q1 = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q1 = *ptr_q1;
    Quaternion* ptr_q2 = (Quaternion*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_q2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q2 = *ptr_q2;
    double double_amount;
    int err_amount = JS_ToFloat64(ctx, &double_amount, argv[2]);
    if(err_amount<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float amount = (float)double_amount;
    Quaternion returnVal = QuaternionLerp(q1, q2, amount);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionNlerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q1 = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q1 = *ptr_q1;
    Quaternion* ptr_q2 = (Quaternion*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_q2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q2 = *ptr_q2;
    double double_amount;
    int err_amount = JS_ToFloat64(ctx, &double_amount, argv[2]);
    if(err_amount<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float amount = (float)double_amount;
    Quaternion returnVal = QuaternionNlerp(q1, q2, amount);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionSlerp(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q1 = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q1 = *ptr_q1;
    Quaternion* ptr_q2 = (Quaternion*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_q2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q2 = *ptr_q2;
    double double_amount;
    int err_amount = JS_ToFloat64(ctx, &double_amount, argv[2]);
    if(err_amount<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float amount = (float)double_amount;
    Quaternion returnVal = QuaternionSlerp(q1, q2, amount);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionCubicHermiteSpline(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q1 = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q1 = *ptr_q1;
    Quaternion* ptr_outTangent1 = (Quaternion*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_outTangent1 == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion outTangent1 = *ptr_outTangent1;
    Quaternion* ptr_q2 = (Quaternion*)JS_GetOpaque(argv[2], js_Vector4_class_id);
    if(ptr_q2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q2 = *ptr_q2;
    Quaternion* ptr_inTangent2 = (Quaternion*)JS_GetOpaque(argv[3], js_Vector4_class_id);
    if(ptr_inTangent2 == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion inTangent2 = *ptr_inTangent2;
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[4]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    Quaternion returnVal = QuaternionCubicHermiteSpline(q1, outTangent1, q2, inTangent2, t);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionFromVector3ToVector3(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_from = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_from == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 from = *ptr_from;
    Vector3* ptr_to = (Vector3*)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(ptr_to == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 to = *ptr_to;
    Quaternion returnVal = QuaternionFromVector3ToVector3(from, to);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionFromMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* ptr_mat = (Matrix*)JS_GetOpaque(argv[0], js_Matrix_class_id);
    if(ptr_mat == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix mat = *ptr_mat;
    Quaternion returnVal = QuaternionFromMatrix(mat);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionToMatrix(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    Matrix returnVal = QuaternionToMatrix(q);
    Matrix* ptr_ret = (Matrix*)js_malloc(ctx, sizeof(Matrix));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionFromAxisAngle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Vector3* ptr_axis = (Vector3*)JS_GetOpaque(argv[0], js_Vector3_class_id);
    if(ptr_axis == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Vector3 axis = *ptr_axis;
    double double_angle;
    int err_angle = JS_ToFloat64(ctx, &double_angle, argv[1]);
    if(err_angle<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float angle = (float)double_angle;
    Quaternion returnVal = QuaternionFromAxisAngle(axis, angle);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionToAxisAngle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    Vector3 * outAxis;
    int64_t size_outAxis;
    if(JS_IsArray(ctx,argv[1]) == 1) {
        if(JS_GetLength(ctx,argv[1],&size_outAxis)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        outAxis = (Vector3 *)js_malloc(ctx, size_outAxis * sizeof(Vector3));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, outAxis);
        for(int i0=0; i0 < size_outAxis; i0++){
            JSValue js_outAxis = JS_GetPropertyUint32(ctx,argv[1],i0);
            Vector3* ptr_outAxisi0 = (Vector3*)JS_GetOpaque(js_outAxis, js_Vector3_class_id);
            if(ptr_outAxisi0 == NULL) {
                JS_ThrowTypeError(ctx, "js_outAxis does not allow null");
                return JS_EXCEPTION;
            }
            outAxis[i0] = *ptr_outAxisi0;
            JS_FreeValue(ctx, js_outAxis);
        }
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JSValue da_outAxis = JS_DupValue(ctx,argv[1]);
        size_t size_outAxis;
        outAxis = (Vector3 *)JS_GetArrayBuffer(ctx, &size_outAxis, da_outAxis);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_outAxis);
    }
    else {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[1] does not match type Vector3 *");
        return JS_EXCEPTION;
    }
    float * outAngle;
    int64_t size_outAngle;
    if(JS_IsArray(ctx,argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_outAngle)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        outAngle = (float *)js_malloc(ctx, size_outAngle * sizeof(float));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, outAngle);
        for(int i0=0; i0 < size_outAngle; i0++){
            JSValue js_outAngle = JS_GetPropertyUint32(ctx,argv[2],i0);
            double double_outAnglei0;
            int err_outAnglei0 = JS_ToFloat64(ctx, &double_outAnglei0, js_outAngle);
            if(err_outAnglei0<0) {
                JS_ThrowTypeError(ctx, "js_outAngle is not numeric");
                return JS_EXCEPTION;
            }
            outAngle[i0] = (float)double_outAnglei0;
            JS_FreeValue(ctx, js_outAngle);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JSValue da_outAngle = JS_DupValue(ctx,argv[2]);
        size_t size_outAngle;
        outAngle = (float *)JS_GetArrayBuffer(ctx, &size_outAngle, da_outAngle);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_outAngle);
    }
    else {
        JSClassID classid_outAngle = JS_GetClassID(argv[2]);
        if(classid_outAngle==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_outAngle;
            size_t size_outAngle;
            JSValue da_outAngle = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_outAngle,&size_outAngle,NULL);
            outAngle = (float *)JS_GetArrayBuffer(ctx, &size_outAngle, da_outAngle);
            outAngle+=offset_outAngle;
            size_outAngle-=offset_outAngle;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_outAngle);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[2] does not match type float *");
            return JS_EXCEPTION;
        }
    }
    QuaternionToAxisAngle(q, outAxis, outAngle);
    memoryClear(ctx, memoryHead);
    return JS_UNDEFINED;
}

static JSValue js_quaternionFromEuler(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_pitch;
    int err_pitch = JS_ToFloat64(ctx, &double_pitch, argv[0]);
    if(err_pitch<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float pitch = (float)double_pitch;
    double double_yaw;
    int err_yaw = JS_ToFloat64(ctx, &double_yaw, argv[1]);
    if(err_yaw<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float yaw = (float)double_yaw;
    double double_roll;
    int err_roll = JS_ToFloat64(ctx, &double_roll, argv[2]);
    if(err_roll<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float roll = (float)double_roll;
    Quaternion returnVal = QuaternionFromEuler(pitch, yaw, roll);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionToEuler(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    Vector3 returnVal = QuaternionToEuler(q);
    Vector3* ptr_ret = (Vector3*)js_malloc(ctx, sizeof(Vector3));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionTransform(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    Matrix* ptr_mat = (Matrix*)JS_GetOpaque(argv[1], js_Matrix_class_id);
    if(ptr_mat == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix mat = *ptr_mat;
    Quaternion returnVal = QuaternionTransform(q, mat);
    Quaternion* ptr_ret = (Quaternion*)js_malloc(ctx, sizeof(Quaternion));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_quaternionEquals(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Quaternion* ptr_p = (Quaternion*)JS_GetOpaque(argv[0], js_Vector4_class_id);
    if(ptr_p == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion p = *ptr_p;
    Quaternion* ptr_q = (Quaternion*)JS_GetOpaque(argv[1], js_Vector4_class_id);
    if(ptr_q == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not allow null");
        return JS_EXCEPTION;
    }
    Quaternion q = *ptr_q;
    int returnVal = QuaternionEquals(p, q);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_matrixDecompose(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Matrix* ptr_mat = (Matrix*)JS_GetOpaque(argv[0], js_Matrix_class_id);
    if(ptr_mat == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Matrix mat = *ptr_mat;
    Vector3 * translation = (Vector3 *)JS_GetOpaque(argv[1], js_Vector3_class_id);
    if(translation == NULL) {
        JS_ThrowTypeError(ctx, "argv[1] does not match type Vector3");
        return JS_EXCEPTION;
    }
    Quaternion * rotation = (Quaternion *)JS_GetOpaque(argv[2], js_Vector4_class_id);
    if(rotation == NULL) {
        JS_ThrowTypeError(ctx, "argv[2] does not match type Quaternion");
        return JS_EXCEPTION;
    }
    Vector3 * scale = (Vector3 *)JS_GetOpaque(argv[3], js_Vector3_class_id);
    if(scale == NULL) {
        JS_ThrowTypeError(ctx, "argv[3] does not match type Vector3");
        return JS_EXCEPTION;
    }
    MatrixDecompose(mat, translation, rotation, scale);
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry js_js_raymath_funcs[] = {
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
    JS_CFUNC_DEF("vector2CrossProduct",2,js_vector2CrossProduct),
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
    JS_CFUNC_DEF("vector3OrthoNormalize",2,js_vector3OrthoNormalize),
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
    JS_CFUNC_DEF("vector4Zero",0,js_vector4Zero),
    JS_CFUNC_DEF("vector4One",0,js_vector4One),
    JS_CFUNC_DEF("vector4Add",2,js_vector4Add),
    JS_CFUNC_DEF("vector4AddValue",2,js_vector4AddValue),
    JS_CFUNC_DEF("vector4Subtract",2,js_vector4Subtract),
    JS_CFUNC_DEF("vector4SubtractValue",2,js_vector4SubtractValue),
    JS_CFUNC_DEF("vector4Length",1,js_vector4Length),
    JS_CFUNC_DEF("vector4LengthSqr",1,js_vector4LengthSqr),
    JS_CFUNC_DEF("vector4DotProduct",2,js_vector4DotProduct),
    JS_CFUNC_DEF("vector4Distance",2,js_vector4Distance),
    JS_CFUNC_DEF("vector4DistanceSqr",2,js_vector4DistanceSqr),
    JS_CFUNC_DEF("vector4Scale",2,js_vector4Scale),
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
    JS_CFUNC_DEF("quaternionToAxisAngle",3,js_quaternionToAxisAngle),
    JS_CFUNC_DEF("quaternionFromEuler",3,js_quaternionFromEuler),
    JS_CFUNC_DEF("quaternionToEuler",1,js_quaternionToEuler),
    JS_CFUNC_DEF("quaternionTransform",2,js_quaternionTransform),
    JS_CFUNC_DEF("quaternionEquals",2,js_quaternionEquals),
    JS_CFUNC_DEF("matrixDecompose",4,js_matrixDecompose),
};

static int js_js_raymath_init(JSContext * ctx, JSModuleDef * m) {
    JS_SetModuleExportList(ctx, m,js_js_raymath_funcs,countof(js_js_raymath_funcs));
    js_declare_float3(ctx, m);
    js_declare_float16(ctx, m);
    JS_SetModuleExport(ctx, m, "EPSILON", JS_NewFloat64(ctx, EPSILON));
    return 0;
}

JSModuleDef * js_init_module_js_raymath(JSContext * ctx, const char * module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_js_raymath_init);
    if(!m) return NULL;
    JS_AddModuleExportList(ctx, m, js_js_raymath_funcs, countof(js_js_raymath_funcs));
    JS_AddModuleExport(ctx, m, "EPSILON");
    return m;
}

#endif // JS_js_raymath_GUARD
