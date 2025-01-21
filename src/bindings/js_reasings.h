#ifndef JS_js_reasings_GUARD
#define JS_js_reasings_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <quickjs.h>
#include <rayjs_base.h>
#include <reasings.h>


static JSValue js_easeLinearNone(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeLinearIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeLinearOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeLinearInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeSineIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeSineOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeSineInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeCircIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeCircOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeCircInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeCubicIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeCubicOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeCubicInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeQuadIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeQuadOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeQuadInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeExpoIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeExpoOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeExpoInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeBackIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeBackOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeBackInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeBounceOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeBounceIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeBounceInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeElasticIn(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeElasticOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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

static JSValue js_easeElasticInOut(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
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
    JS_CFUNC_DEF("easeBackOut",4,js_easeBackOut),
    JS_CFUNC_DEF("easeBackInOut",4,js_easeBackInOut),
    JS_CFUNC_DEF("easeBounceOut",4,js_easeBounceOut),
    JS_CFUNC_DEF("easeBounceIn",4,js_easeBounceIn),
    JS_CFUNC_DEF("easeBounceInOut",4,js_easeBounceInOut),
    JS_CFUNC_DEF("easeElasticIn",4,js_easeElasticIn),
    JS_CFUNC_DEF("easeElasticOut",4,js_easeElasticOut),
    JS_CFUNC_DEF("easeElasticInOut",4,js_easeElasticInOut),
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
