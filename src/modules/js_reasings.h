#ifndef JS_js_reasings_GUARD
#define JS_js_reasings_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <quickjs.h>
#include <rayjs_base.h>
#include <reasings.h>


static JSValue js_EaseLinearNone(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseLinearNone(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseLinearIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseLinearIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseLinearOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseLinearOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseLinearInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseLinearInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseSineIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseSineIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseSineOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseSineOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseSineInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseSineInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseCircIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseCircIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseCircOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseCircOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseCircInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseCircInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseCubicIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseCubicIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseCubicOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseCubicOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseCubicInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseCubicInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseQuadIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseQuadIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseQuadOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseQuadOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseQuadInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseQuadInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseExpoIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseExpoIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseExpoOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseExpoOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseExpoInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseExpoInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseBackIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseBackIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseBackOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseBackOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseBackInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseBackInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseBounceOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseBounceOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseBounceIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseBounceIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseBounceInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseBounceInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseElasticIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseElasticIn(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseElasticOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseElasticOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static JSValue js_EaseElasticInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_t;
    int err_t = JS_ToFloat64(ctx, &double_t, argv[0]);
    if(err_t<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float t = (float)double_t;
    double double_b;
    int err_b = JS_ToFloat64(ctx, &double_b, argv[1]);
    if(err_b<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    float b = (float)double_b;
    double double_c;
    int err_c = JS_ToFloat64(ctx, &double_c, argv[2]);
    if(err_c<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    float c = (float)double_c;
    double double_d;
    int err_d = JS_ToFloat64(ctx, &double_d, argv[3]);
    if(err_d<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    float d = (float)double_d;
    float returnVal = EaseElasticInOut(t, b, c, d);
    JSValue ret = JS_NewFloat64(ctx, (double)returnVal);
    return ret;
}

static const JSCFunctionListEntry js_js_reasings_funcs[] = {
    JS_CFUNC_DEF("EaseLinearNone",4,js_EaseLinearNone),
    JS_CFUNC_DEF("EaseLinearIn",4,js_EaseLinearIn),
    JS_CFUNC_DEF("EaseLinearOut",4,js_EaseLinearOut),
    JS_CFUNC_DEF("EaseLinearInOut",4,js_EaseLinearInOut),
    JS_CFUNC_DEF("EaseSineIn",4,js_EaseSineIn),
    JS_CFUNC_DEF("EaseSineOut",4,js_EaseSineOut),
    JS_CFUNC_DEF("EaseSineInOut",4,js_EaseSineInOut),
    JS_CFUNC_DEF("EaseCircIn",4,js_EaseCircIn),
    JS_CFUNC_DEF("EaseCircOut",4,js_EaseCircOut),
    JS_CFUNC_DEF("EaseCircInOut",4,js_EaseCircInOut),
    JS_CFUNC_DEF("EaseCubicIn",4,js_EaseCubicIn),
    JS_CFUNC_DEF("EaseCubicOut",4,js_EaseCubicOut),
    JS_CFUNC_DEF("EaseCubicInOut",4,js_EaseCubicInOut),
    JS_CFUNC_DEF("EaseQuadIn",4,js_EaseQuadIn),
    JS_CFUNC_DEF("EaseQuadOut",4,js_EaseQuadOut),
    JS_CFUNC_DEF("EaseQuadInOut",4,js_EaseQuadInOut),
    JS_CFUNC_DEF("EaseExpoIn",4,js_EaseExpoIn),
    JS_CFUNC_DEF("EaseExpoOut",4,js_EaseExpoOut),
    JS_CFUNC_DEF("EaseExpoInOut",4,js_EaseExpoInOut),
    JS_CFUNC_DEF("EaseBackIn",4,js_EaseBackIn),
    JS_CFUNC_DEF("EaseBackOut",4,js_EaseBackOut),
    JS_CFUNC_DEF("EaseBackInOut",4,js_EaseBackInOut),
    JS_CFUNC_DEF("EaseBounceOut",4,js_EaseBounceOut),
    JS_CFUNC_DEF("EaseBounceIn",4,js_EaseBounceIn),
    JS_CFUNC_DEF("EaseBounceInOut",4,js_EaseBounceInOut),
    JS_CFUNC_DEF("EaseElasticIn",4,js_EaseElasticIn),
    JS_CFUNC_DEF("EaseElasticOut",4,js_EaseElasticOut),
    JS_CFUNC_DEF("EaseElasticInOut",4,js_EaseElasticInOut),
};

static int js_js_reasings_init(JSContext * ctx, JSModuleDef * m) {
    JS_SetModuleExportList(ctx, m,js_js_reasings_funcs,countof(js_js_reasings_funcs));
    return 0;
}

JSModuleDef * js_init_module_js_reasings(JSContext * ctx, const char * module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_js_reasings_init);
    if(!m) return NULL;
    JS_AddModuleExportList(ctx, m, js_js_reasings_funcs, countof(js_js_reasings_funcs));
    return m;
}

#endif // JS_js_reasings_GUARD
