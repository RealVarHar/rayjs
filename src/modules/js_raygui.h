#ifndef JS_js_raygui_GUARD
#define JS_js_raygui_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <quickjs.h>
#include <rayjs_base.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <raylib.h>

static JSClassID js_GuiStyleProp_class_id;
static JSClassID js_GuiStyleProp_class_id;

static void js_GuiStyleProp_finalizer(JSRuntime * rt, JSValue val) {
    GuiStyleProp* ptr = JS_GetOpaque(val, js_GuiStyleProp_class_id);
    if(ptr) {
        js_free_rt(rt, ptr);
    }
}

static const JSCFunctionListEntry js_GuiStyleProp_proto_funcs[] = {
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","GuiStyleProp", JS_PROP_CONFIGURABLE),
};

static int js_declare_GuiStyleProp(JSContext * ctx, JSModuleDef * m) {
    JSRuntime * rt = JS_GetRuntime(ctx);
    JS_NewClassID(rt, &js_GuiStyleProp_class_id);
    JSClassDef js_GuiStyleProp_def = { .class_name = "GuiStyleProp", .finalizer = js_GuiStyleProp_finalizer };
    JS_NewClass(rt, js_GuiStyleProp_class_id, &js_GuiStyleProp_def);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_GuiStyleProp_proto_funcs, countof(js_GuiStyleProp_proto_funcs));
    JS_SetClassProto(ctx, js_GuiStyleProp_class_id, proto);
    return 0;
}

static JSValue js_GuiEnable(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiEnable();
    return JS_UNDEFINED;
}

static JSValue js_GuiDisable(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiDisable();
    return JS_UNDEFINED;
}

static JSValue js_GuiLock(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiLock();
    return JS_UNDEFINED;
}

static JSValue js_GuiUnlock(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiUnlock();
    return JS_UNDEFINED;
}

static JSValue js_GuiIsLocked(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    bool returnVal = GuiIsLocked();
    JSValue ret = JS_NewBool(ctx, returnVal);
    return ret;
}

static JSValue js_GuiSetAlpha(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    double double_alpha;
    int err_alpha = JS_ToFloat64(ctx, &double_alpha, argv[0]);
    if(err_alpha<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    float alpha = (float)double_alpha;
    GuiSetAlpha(alpha);
    return JS_UNDEFINED;
}

static JSValue js_GuiSetState(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_state;
    int err_state = JS_ToInt32(ctx, &long_state, argv[0]);
    if(err_state<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int state = (int)long_state;
    GuiSetState(state);
    return JS_UNDEFINED;
}

static JSValue js_GuiGetState(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int returnVal = GuiGetState();
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiSetFont(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font* ptr_font = (Font*)JS_GetOpaque(argv[0], js_Font_class_id);
    if(ptr_font == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Font font = *ptr_font;
    GuiSetFont(font);
    return JS_UNDEFINED;
}

static JSValue js_GuiGetFont(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Font returnVal = GuiGetFont();
    Font* ptr_ret = (Font*)js_malloc(ctx, sizeof(Font));
    *ptr_ret = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ptr_ret);
    return ret;
}

static JSValue js_GuiSetStyle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_control;
    int err_control = JS_ToInt32(ctx, &long_control, argv[0]);
    if(err_control<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int control = (int)long_control;
    int32_t long_property;
    int err_property = JS_ToInt32(ctx, &long_property, argv[1]);
    if(err_property<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int property = (int)long_property;
    int32_t long_value;
    int err_value = JS_ToInt32(ctx, &long_value, argv[2]);
    if(err_value<0) {
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int value = (int)long_value;
    GuiSetStyle(control, property, value);
    return JS_UNDEFINED;
}

static JSValue js_GuiGetStyle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_control;
    int err_control = JS_ToInt32(ctx, &long_control, argv[0]);
    if(err_control<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int control = (int)long_control;
    int32_t long_property;
    int err_property = JS_ToInt32(ctx, &long_property, argv[1]);
    if(err_property<0) {
        JS_ThrowTypeError(ctx, "argv[1] is not numeric");
        return JS_EXCEPTION;
    }
    int property = (int)long_property;
    int returnVal = GuiGetStyle(control, property);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiLoadStyle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * fileName;
    bool freesrc_fileName = false;
    JSValue da_fileName;
    int64_t size_fileName;
    if(JS_IsString(argv[0]) == 1) {
        fileName = (char *)JS_ToCStringLen(ctx, &size_fileName, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        size_t size_fileName;
        fileName = (char *)JS_GetArrayBuffer(ctx, &size_fileName, argv[0]);
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
            if(freesrc_fileName) {
                JS_FreeValue(ctx, argv[0]);
            }
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_fileName) {
            JS_FreeValue(ctx, argv[0]);
        }
    }
    GuiLoadStyle((const char *)fileName);
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

static JSValue js_GuiLoadStyleDefault(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiLoadStyleDefault();
    return JS_UNDEFINED;
}

static JSValue js_GuiEnableTooltip(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiEnableTooltip();
    return JS_UNDEFINED;
}

static JSValue js_GuiDisableTooltip(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    GuiDisableTooltip();
    return JS_UNDEFINED;
}

static JSValue js_GuiSetTooltip(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    char * tooltip;
    bool freesrc_tooltip = false;
    JSValue da_tooltip;
    int64_t size_tooltip;
    if(JS_IsString(argv[0]) == 1) {
        tooltip = (char *)JS_ToCStringLen(ctx, &size_tooltip, argv[0]);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        size_t size_tooltip;
        tooltip = (char *)JS_GetArrayBuffer(ctx, &size_tooltip, argv[0]);
    }
    else {
        JSClassID classid_tooltip = JS_GetClassID(argv[0]);
        if(classid_tooltip==JS_CLASS_INT8_ARRAY) {
            size_t offset_tooltip;
            size_t size_tooltip;
            da_tooltip = JS_GetTypedArrayBuffer(ctx,argv[0],&offset_tooltip,&size_tooltip,NULL);
            tooltip = (char *)JS_GetArrayBuffer(ctx, &size_tooltip, da_tooltip);
            tooltip+=offset_tooltip;
            size_tooltip-=offset_tooltip;
        }
        else {
            if(freesrc_tooltip) {
                JS_FreeValue(ctx, argv[0]);
            }
            JS_ThrowTypeError(ctx, "argv[0] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_tooltip) {
            JS_FreeValue(ctx, argv[0]);
        }
    }
    GuiSetTooltip((const char *)tooltip);
    if(JS_IsArray(argv[0]) == 1) {
        js_free(ctx, tooltip);
    }
    else if(JS_IsString(argv[0]) == 1) {
        JS_FreeCString(ctx, tooltip);
    }
    else if(JS_IsArrayBuffer(argv[0]) == 1) {
        JS_FreeValue(ctx, da_tooltip);
    }
    else {
        JSClassID classid_tooltip = JS_GetClassID(argv[0]);
        if(classid_tooltip==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_tooltip);
        }
    }
    return JS_UNDEFINED;
}

static JSValue js_GuiIconText(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_iconId;
    int err_iconId = JS_ToInt32(ctx, &long_iconId, argv[0]);
    if(err_iconId<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int iconId = (int)long_iconId;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    const char * returnVal = GuiIconText(iconId, (const char *)text);
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
    JSValue ret;
    ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GuiSetIconScale(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_scale;
    int err_scale = JS_ToInt32(ctx, &long_scale, argv[0]);
    if(err_scale<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int scale = (int)long_scale;
    GuiSetIconScale(scale);
    return JS_UNDEFINED;
}

static JSValue js_GuiDrawIcon(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    int32_t long_iconId;
    int err_iconId = JS_ToInt32(ctx, &long_iconId, argv[0]);
    if(err_iconId<0) {
        JS_ThrowTypeError(ctx, "argv[0] is not numeric");
        return JS_EXCEPTION;
    }
    int iconId = (int)long_iconId;
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
    int32_t long_pixelSize;
    int err_pixelSize = JS_ToInt32(ctx, &long_pixelSize, argv[3]);
    if(err_pixelSize<0) {
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int pixelSize = (int)long_pixelSize;
    Color* ptr_color = (Color*)JS_GetOpaque(argv[4], js_Color_class_id);
    if(ptr_color == NULL) {
        JS_ThrowTypeError(ctx, "argv[4] does not allow null");
        return JS_EXCEPTION;
    }
    Color color = *ptr_color;
    GuiDrawIcon(iconId, posX, posY, pixelSize, color);
    return JS_UNDEFINED;
}

static JSValue js_GuiWindowBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * title;
    bool freesrc_title = false;
    JSValue da_title;
    int64_t size_title;
    if(JS_IsString(argv[1]) == 1) {
        title = (char *)JS_ToCStringLen(ctx, &size_title, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_title;
        title = (char *)JS_GetArrayBuffer(ctx, &size_title, argv[1]);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[1]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            size_t offset_title;
            size_t size_title;
            da_title = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_title,&size_title,NULL);
            title = (char *)JS_GetArrayBuffer(ctx, &size_title, da_title);
            title+=offset_title;
            size_title-=offset_title;
        }
        else {
            if(freesrc_title) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_title) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int returnVal = GuiWindowBox(bounds, (const char *)title);
    if(JS_IsArray(argv[1]) == 1) {
        js_free(ctx, title);
    }
    else if(JS_IsString(argv[1]) == 1) {
        JS_FreeCString(ctx, title);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        JS_FreeValue(ctx, da_title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[1]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            js_free(ctx, &da_title);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiGroupBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int returnVal = GuiGroupBox(bounds, (const char *)text);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiLine(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int returnVal = GuiLine(bounds, (const char *)text);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiPanel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int returnVal = GuiPanel(bounds, (const char *)text);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiScrollPanel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        text = NULL;
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    Rectangle* ptr_content = (Rectangle*)JS_GetOpaque(argv[2], js_Rectangle_class_id);
    if(ptr_content == NULL) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
    Rectangle content = *ptr_content;
    Vector2 * scroll = (Vector2 *)JS_GetOpaque(argv[3], js_Vector2_class_id);
    if(scroll == NULL) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
        JS_ThrowTypeError(ctx, "argv[3] does not match type Vector2");
        return JS_EXCEPTION;
    }
    Rectangle * view = (Rectangle *)JS_GetOpaque(argv[4], js_Rectangle_class_id);
    if(view == NULL) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
        JS_ThrowTypeError(ctx, "argv[4] does not match type Rectangle");
        return JS_EXCEPTION;
    }
    int returnVal = GuiScrollPanel(bounds, (const char *)text, content, scroll, view);
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
    }
    else if(JS_IsArray(argv[1]) == 1) {
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiLabel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int returnVal = GuiLabel(bounds, (const char *)text);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiButton(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int returnVal = GuiButton(bounds, (const char *)text);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiLabelButton(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int returnVal = GuiLabelButton(bounds, (const char *)text);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiToggle(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    bool * active;
    bool freesrc_active = false;
    JSValue da_active;
    int64_t size_active;
    if(JS_GetClassID(argv[2]) == js_ArrayProxy_class_id) {
        void * opaque_active = JS_GetOpaque(argv[2], js_ArrayProxy_class_id);
        ArrayProxy_class AP_active = *(ArrayProxy_class *)opaque_active;
        argv[2] = AP_active.values(ctx, AP_active.opaque, 0, false);
        freesrc_active = true;
    }
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_active)==-1) {
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
            return JS_EXCEPTION;
        }
        active = (bool *)js_malloc(ctx, size_active * sizeof(bool));
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[2],i0);
            int js_activei0 = JS_ToBool(ctx, js_active);
            if(js_activei0<0) {
                JS_ThrowTypeError(ctx, "js_active is not a bool");
                return JS_EXCEPTION;
            }
            active[i0] = js_activei0;
            JS_FreeValue(ctx, js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_active;
        active = (bool *)JS_GetArrayBuffer(ctx, &size_active, argv[2]);
    }
    else {
        int js_js_active = JS_ToBool(ctx, argv[2]);
        if(js_js_active<0) {
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
            JS_ThrowTypeError(ctx, "argv[2] is not a bool");
            return JS_EXCEPTION;
        }
        bool js_active = js_js_active;
        active = &js_active;
    }
    int returnVal = GuiToggle(bounds, (const char *)text, active);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewBool(ctx, active[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
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
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, active);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_active);
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiToggleGroup(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int * active;
    bool freesrc_active = false;
    JSValue da_active;
    int64_t size_active;
    if(JS_GetClassID(argv[2]) == js_ArrayProxy_class_id) {
        void * opaque_active = JS_GetOpaque(argv[2], js_ArrayProxy_class_id);
        ArrayProxy_class AP_active = *(ArrayProxy_class *)opaque_active;
        argv[2] = AP_active.values(ctx, AP_active.opaque, 0, false);
        freesrc_active = true;
    }
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_active)==-1) {
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
            return JS_EXCEPTION;
        }
        active = (int *)js_malloc(ctx, size_active * sizeof(int));
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[2],i0);
            int32_t long_activei0;
            int err_activei0 = JS_ToInt32(ctx, &long_activei0, js_active);
            if(err_activei0<0) {
                JS_ThrowTypeError(ctx, "js_active is not numeric");
                return JS_EXCEPTION;
            }
            active[i0] = (int)long_activei0;
            JS_FreeValue(ctx, js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_active;
        active = (int *)JS_GetArrayBuffer(ctx, &size_active, argv[2]);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            size_t offset_active;
            size_t size_active;
            da_active = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_active,&size_active,NULL);
            active = (int *)JS_GetArrayBuffer(ctx, &size_active, da_active);
            active+=offset_active;
            size_active-=offset_active;
        }
        else {
            int32_t long_js_active;
            int err_js_active = JS_ToInt32(ctx, &long_js_active, argv[2]);
            if(err_js_active<0) {
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
            int js_active = (int)long_js_active;
            active = &js_active;
        }
    }
    int returnVal = GuiToggleGroup(bounds, (const char *)text, active);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewInt32(ctx, (long)active[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
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
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, active);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &da_active);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiToggleSlider(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int * active;
    bool freesrc_active = false;
    JSValue da_active;
    int64_t size_active;
    if(JS_GetClassID(argv[2]) == js_ArrayProxy_class_id) {
        void * opaque_active = JS_GetOpaque(argv[2], js_ArrayProxy_class_id);
        ArrayProxy_class AP_active = *(ArrayProxy_class *)opaque_active;
        argv[2] = AP_active.values(ctx, AP_active.opaque, 0, false);
        freesrc_active = true;
    }
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_active)==-1) {
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
            return JS_EXCEPTION;
        }
        active = (int *)js_malloc(ctx, size_active * sizeof(int));
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[2],i0);
            int32_t long_activei0;
            int err_activei0 = JS_ToInt32(ctx, &long_activei0, js_active);
            if(err_activei0<0) {
                JS_ThrowTypeError(ctx, "js_active is not numeric");
                return JS_EXCEPTION;
            }
            active[i0] = (int)long_activei0;
            JS_FreeValue(ctx, js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_active;
        active = (int *)JS_GetArrayBuffer(ctx, &size_active, argv[2]);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            size_t offset_active;
            size_t size_active;
            da_active = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_active,&size_active,NULL);
            active = (int *)JS_GetArrayBuffer(ctx, &size_active, da_active);
            active+=offset_active;
            size_active-=offset_active;
        }
        else {
            int32_t long_js_active;
            int err_js_active = JS_ToInt32(ctx, &long_js_active, argv[2]);
            if(err_js_active<0) {
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
            int js_active = (int)long_js_active;
            active = &js_active;
        }
    }
    int returnVal = GuiToggleSlider(bounds, (const char *)text, active);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewInt32(ctx, (long)active[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
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
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, active);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &da_active);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiCheckBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    bool * checked;
    bool freesrc_checked = false;
    JSValue da_checked;
    int64_t size_checked;
    if(JS_GetClassID(argv[2]) == js_ArrayProxy_class_id) {
        void * opaque_checked = JS_GetOpaque(argv[2], js_ArrayProxy_class_id);
        ArrayProxy_class AP_checked = *(ArrayProxy_class *)opaque_checked;
        argv[2] = AP_checked.values(ctx, AP_checked.opaque, 0, false);
        freesrc_checked = true;
    }
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_checked)==-1) {
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
            return JS_EXCEPTION;
        }
        checked = (bool *)js_malloc(ctx, size_checked * sizeof(bool));
        for(int i0=0; i0 < size_checked; i0++){
            JSValue js_checked = JS_GetPropertyUint32(ctx,argv[2],i0);
            int js_checkedi0 = JS_ToBool(ctx, js_checked);
            if(js_checkedi0<0) {
                JS_ThrowTypeError(ctx, "js_checked is not a bool");
                return JS_EXCEPTION;
            }
            checked[i0] = js_checkedi0;
            JS_FreeValue(ctx, js_checked);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_checked;
        checked = (bool *)JS_GetArrayBuffer(ctx, &size_checked, argv[2]);
    }
    else {
        int js_js_checked = JS_ToBool(ctx, argv[2]);
        if(js_js_checked<0) {
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
            JS_ThrowTypeError(ctx, "argv[2] is not a bool");
            return JS_EXCEPTION;
        }
        bool js_checked = js_js_checked;
        checked = &js_checked;
    }
    int returnVal = GuiCheckBox(bounds, (const char *)text, checked);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewBool(ctx, checked[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
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
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, checked);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_checked);
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiComboBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int * active;
    bool freesrc_active = false;
    JSValue da_active;
    int64_t size_active;
    if(JS_GetClassID(argv[2]) == js_ArrayProxy_class_id) {
        void * opaque_active = JS_GetOpaque(argv[2], js_ArrayProxy_class_id);
        ArrayProxy_class AP_active = *(ArrayProxy_class *)opaque_active;
        argv[2] = AP_active.values(ctx, AP_active.opaque, 0, false);
        freesrc_active = true;
    }
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_active)==-1) {
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
            return JS_EXCEPTION;
        }
        active = (int *)js_malloc(ctx, size_active * sizeof(int));
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[2],i0);
            int32_t long_activei0;
            int err_activei0 = JS_ToInt32(ctx, &long_activei0, js_active);
            if(err_activei0<0) {
                JS_ThrowTypeError(ctx, "js_active is not numeric");
                return JS_EXCEPTION;
            }
            active[i0] = (int)long_activei0;
            JS_FreeValue(ctx, js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_active;
        active = (int *)JS_GetArrayBuffer(ctx, &size_active, argv[2]);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            size_t offset_active;
            size_t size_active;
            da_active = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_active,&size_active,NULL);
            active = (int *)JS_GetArrayBuffer(ctx, &size_active, da_active);
            active+=offset_active;
            size_active-=offset_active;
        }
        else {
            int32_t long_js_active;
            int err_js_active = JS_ToInt32(ctx, &long_js_active, argv[2]);
            if(err_js_active<0) {
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
            int js_active = (int)long_js_active;
            active = &js_active;
        }
    }
    int returnVal = GuiComboBox(bounds, (const char *)text, active);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewInt32(ctx, (long)active[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
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
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, active);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &da_active);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiDropdownBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int * active;
    bool freesrc_active = false;
    JSValue da_active;
    int64_t size_active;
    if(JS_GetClassID(argv[2]) == js_ArrayProxy_class_id) {
        void * opaque_active = JS_GetOpaque(argv[2], js_ArrayProxy_class_id);
        ArrayProxy_class AP_active = *(ArrayProxy_class *)opaque_active;
        argv[2] = AP_active.values(ctx, AP_active.opaque, 0, false);
        freesrc_active = true;
    }
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_active)==-1) {
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
            return JS_EXCEPTION;
        }
        active = (int *)js_malloc(ctx, size_active * sizeof(int));
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[2],i0);
            int32_t long_activei0;
            int err_activei0 = JS_ToInt32(ctx, &long_activei0, js_active);
            if(err_activei0<0) {
                JS_ThrowTypeError(ctx, "js_active is not numeric");
                return JS_EXCEPTION;
            }
            active[i0] = (int)long_activei0;
            JS_FreeValue(ctx, js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_active;
        active = (int *)JS_GetArrayBuffer(ctx, &size_active, argv[2]);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            size_t offset_active;
            size_t size_active;
            da_active = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_active,&size_active,NULL);
            active = (int *)JS_GetArrayBuffer(ctx, &size_active, da_active);
            active+=offset_active;
            size_active-=offset_active;
        }
        else {
            int32_t long_js_active;
            int err_js_active = JS_ToInt32(ctx, &long_js_active, argv[2]);
            if(err_js_active<0) {
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
            int js_active = (int)long_js_active;
            active = &js_active;
        }
    }
    int js_editMode = JS_ToBool(ctx, argv[3]);
    if(js_editMode<0) {
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
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, active);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_active);
        }
        else {
            JSClassID classid_active = JS_GetClassID(argv[2]);
            if(classid_active==JS_CLASS_INT16_ARRAY) {
                js_free(ctx, &da_active);
            }
        }
        JS_ThrowTypeError(ctx, "argv[3] is not a bool");
        return JS_EXCEPTION;
    }
    bool editMode = js_editMode;
    int returnVal = GuiDropdownBox(bounds, (const char *)text, active, editMode);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewInt32(ctx, (long)active[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
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
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, active);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[2]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &da_active);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiSpinner(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        text = NULL;
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int * value;
    bool freesrc_value = false;
    JSValue da_value;
    int64_t size_value;
    if(JS_GetClassID(argv[2]) == js_ArrayProxy_class_id) {
        void * opaque_value = JS_GetOpaque(argv[2], js_ArrayProxy_class_id);
        ArrayProxy_class AP_value = *(ArrayProxy_class *)opaque_value;
        argv[2] = AP_value.values(ctx, AP_value.opaque, 0, false);
        freesrc_value = true;
    }
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_value)==-1) {
            if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
            }
            else if(JS_IsArray(argv[1]) == 1) {
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
            return JS_EXCEPTION;
        }
        value = (int *)js_malloc(ctx, size_value * sizeof(int));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[2],i0);
            int32_t long_valuei0;
            int err_valuei0 = JS_ToInt32(ctx, &long_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (int)long_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_value;
        value = (int *)JS_GetArrayBuffer(ctx, &size_value, argv[2]);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[2]);
        if(classid_value==JS_CLASS_INT16_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_value,&size_value,NULL);
            value = (int *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            value+=offset_value;
            size_value-=offset_value;
        }
        else {
            int32_t long_js_value;
            int err_js_value = JS_ToInt32(ctx, &long_js_value, argv[2]);
            if(err_js_value<0) {
                if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
                }
                else if(JS_IsArray(argv[1]) == 1) {
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
            int js_value = (int)long_js_value;
            value = &js_value;
        }
    }
    int32_t long_minValue;
    int err_minValue = JS_ToInt32(ctx, &long_minValue, argv[3]);
    if(err_minValue<0) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, value);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_value);
        }
        else {
            JSClassID classid_value = JS_GetClassID(argv[2]);
            if(classid_value==JS_CLASS_INT16_ARRAY) {
                js_free(ctx, &da_value);
            }
        }
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int minValue = (int)long_minValue;
    int32_t long_maxValue;
    int err_maxValue = JS_ToInt32(ctx, &long_maxValue, argv[4]);
    if(err_maxValue<0) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, value);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_value);
        }
        else {
            JSClassID classid_value = JS_GetClassID(argv[2]);
            if(classid_value==JS_CLASS_INT16_ARRAY) {
                js_free(ctx, &da_value);
            }
        }
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int maxValue = (int)long_maxValue;
    int js_editMode = JS_ToBool(ctx, argv[5]);
    if(js_editMode<0) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, value);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_value);
        }
        else {
            JSClassID classid_value = JS_GetClassID(argv[2]);
            if(classid_value==JS_CLASS_INT16_ARRAY) {
                js_free(ctx, &da_value);
            }
        }
        JS_ThrowTypeError(ctx, "argv[5] is not a bool");
        return JS_EXCEPTION;
    }
    bool editMode = js_editMode;
    int returnVal = GuiSpinner(bounds, (const char *)text, value, minValue, maxValue, editMode);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewInt32(ctx, (long)value[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
    }
    else if(JS_IsArray(argv[1]) == 1) {
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
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, value);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[2]);
        if(classid_value==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &da_value);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiValueBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        text = NULL;
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int * value;
    bool freesrc_value = false;
    JSValue da_value;
    int64_t size_value;
    if(JS_GetClassID(argv[2]) == js_ArrayProxy_class_id) {
        void * opaque_value = JS_GetOpaque(argv[2], js_ArrayProxy_class_id);
        ArrayProxy_class AP_value = *(ArrayProxy_class *)opaque_value;
        argv[2] = AP_value.values(ctx, AP_value.opaque, 0, false);
        freesrc_value = true;
    }
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_value)==-1) {
            if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
            }
            else if(JS_IsArray(argv[1]) == 1) {
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
            return JS_EXCEPTION;
        }
        value = (int *)js_malloc(ctx, size_value * sizeof(int));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[2],i0);
            int32_t long_valuei0;
            int err_valuei0 = JS_ToInt32(ctx, &long_valuei0, js_value);
            if(err_valuei0<0) {
                JS_ThrowTypeError(ctx, "js_value is not numeric");
                return JS_EXCEPTION;
            }
            value[i0] = (int)long_valuei0;
            JS_FreeValue(ctx, js_value);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_value;
        value = (int *)JS_GetArrayBuffer(ctx, &size_value, argv[2]);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[2]);
        if(classid_value==JS_CLASS_INT16_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_value,&size_value,NULL);
            value = (int *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            value+=offset_value;
            size_value-=offset_value;
        }
        else {
            int32_t long_js_value;
            int err_js_value = JS_ToInt32(ctx, &long_js_value, argv[2]);
            if(err_js_value<0) {
                if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
                }
                else if(JS_IsArray(argv[1]) == 1) {
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
            int js_value = (int)long_js_value;
            value = &js_value;
        }
    }
    int32_t long_minValue;
    int err_minValue = JS_ToInt32(ctx, &long_minValue, argv[3]);
    if(err_minValue<0) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, value);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_value);
        }
        else {
            JSClassID classid_value = JS_GetClassID(argv[2]);
            if(classid_value==JS_CLASS_INT16_ARRAY) {
                js_free(ctx, &da_value);
            }
        }
        JS_ThrowTypeError(ctx, "argv[3] is not numeric");
        return JS_EXCEPTION;
    }
    int minValue = (int)long_minValue;
    int32_t long_maxValue;
    int err_maxValue = JS_ToInt32(ctx, &long_maxValue, argv[4]);
    if(err_maxValue<0) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, value);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_value);
        }
        else {
            JSClassID classid_value = JS_GetClassID(argv[2]);
            if(classid_value==JS_CLASS_INT16_ARRAY) {
                js_free(ctx, &da_value);
            }
        }
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    int maxValue = (int)long_maxValue;
    int js_editMode = JS_ToBool(ctx, argv[5]);
    if(js_editMode<0) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
        if(JS_IsArray(argv[2]) == 1) {
            js_free(ctx, value);
        }
        else if(JS_IsArrayBuffer(argv[2]) == 1) {
            JS_FreeValue(ctx, da_value);
        }
        else {
            JSClassID classid_value = JS_GetClassID(argv[2]);
            if(classid_value==JS_CLASS_INT16_ARRAY) {
                js_free(ctx, &da_value);
            }
        }
        JS_ThrowTypeError(ctx, "argv[5] is not a bool");
        return JS_EXCEPTION;
    }
    bool editMode = js_editMode;
    int returnVal = GuiValueBox(bounds, (const char *)text, value, minValue, maxValue, editMode);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewInt32(ctx, (long)value[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
    }
    else if(JS_IsArray(argv[1]) == 1) {
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
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, value);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[2]);
        if(classid_value==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &da_value);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiValueBoxFloat(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, text);
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
    char * textValue;
    int64_t size_textValue;
    if(JS_IsString(argv[2]) == 1) {
        textValue = (char *)JS_ToCStringLen(ctx, &size_textValue, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, textValue);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_textValue;
        textValue = (char *)JS_GetArrayBuffer(ctx, &size_textValue, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, textValue);
    }
    else {
        JSClassID classid_textValue = JS_GetClassID(argv[2]);
        if(classid_textValue==JS_CLASS_INT8_ARRAY) {
            size_t offset_textValue;
            size_t size_textValue;
            JSValue da_textValue = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textValue,&size_textValue,NULL);
            textValue = (char *)JS_GetArrayBuffer(ctx, &size_textValue, da_textValue);
            textValue+=offset_textValue;
            size_textValue-=offset_textValue;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_textValue);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[2] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    float * value;
    int64_t size_value;
    if(JS_GetClassID(argv[3]) == js_ArrayProxy_class_id) {
        void * opaque_value = JS_GetOpaque(argv[3], js_ArrayProxy_class_id);
        ArrayProxy_class AP_value = *(ArrayProxy_class *)opaque_value;
        argv[3] = AP_value.values(ctx, AP_value.opaque, 0, false);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValue, &argv[3]);
    }
    if(JS_IsArray(argv[3]) == 1) {
        if(JS_GetLength(ctx,argv[3],&size_value)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        value = (float *)js_malloc(ctx, size_value * sizeof(float));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, value);
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[3],i0);
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
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, argv[3]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            JSValue da_value = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            value+=offset_value;
            size_value-=offset_value;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_value);
        }
        else {
            double double_js_value;
            int err_js_value = JS_ToFloat64(ctx, &double_js_value, argv[3]);
            if(err_js_value<0) {
                memoryClear(ctx, memoryHead);
                JS_ThrowTypeError(ctx, "argv[3] is not numeric");
                return JS_EXCEPTION;
            }
            float js_value = (float)double_js_value;
            value = &js_value;
        }
    }
    int js_editMode = JS_ToBool(ctx, argv[4]);
    if(js_editMode<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[4] is not a bool");
        return JS_EXCEPTION;
    }
    bool editMode = js_editMode;
    int returnVal = GuiValueBoxFloat(bounds, (const char *)text, textValue, value, editMode);
    if(JS_IsArray(argv[3]) == 1) {
        JSValue js_argv3 = JS_NewFloat64(ctx, (double)value[0]);
        JS_DefinePropertyValueUint32(ctx,argv[3],0,js_argv3,JS_PROP_C_W_E);
    }
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiTextBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int32_t long_textSize;
    int err_textSize = JS_ToInt32(ctx, &long_textSize, argv[2]);
    if(err_textSize<0) {
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
    int textSize = (int)long_textSize;
    int js_editMode = JS_ToBool(ctx, argv[3]);
    if(js_editMode<0) {
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
        JS_ThrowTypeError(ctx, "argv[3] is not a bool");
        return JS_EXCEPTION;
    }
    bool editMode = js_editMode;
    int returnVal = GuiTextBox(bounds, text, textSize, editMode);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiSlider(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * textLeft;
    int64_t size_textLeft;
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        textLeft = NULL;
    }
    else if(JS_IsString(argv[1]) == 1) {
        textLeft = (char *)JS_ToCStringLen(ctx, &size_textLeft, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, textLeft);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_textLeft;
        textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, textLeft);
    }
    else {
        JSClassID classid_textLeft = JS_GetClassID(argv[1]);
        if(classid_textLeft==JS_CLASS_INT8_ARRAY) {
            size_t offset_textLeft;
            size_t size_textLeft;
            JSValue da_textLeft = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_textLeft,&size_textLeft,NULL);
            textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, da_textLeft);
            textLeft+=offset_textLeft;
            size_textLeft-=offset_textLeft;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_textLeft);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * textRight;
    int64_t size_textRight;
    if(JS_IsString(argv[2]) == 1) {
        textRight = (char *)JS_ToCStringLen(ctx, &size_textRight, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, textRight);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_textRight;
        textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, textRight);
    }
    else {
        JSClassID classid_textRight = JS_GetClassID(argv[2]);
        if(classid_textRight==JS_CLASS_INT8_ARRAY) {
            size_t offset_textRight;
            size_t size_textRight;
            JSValue da_textRight = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textRight,&size_textRight,NULL);
            textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, da_textRight);
            textRight+=offset_textRight;
            size_textRight-=offset_textRight;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_textRight);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[2] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    float * value;
    int64_t size_value;
    if(JS_GetClassID(argv[3]) == js_ArrayProxy_class_id) {
        void * opaque_value = JS_GetOpaque(argv[3], js_ArrayProxy_class_id);
        ArrayProxy_class AP_value = *(ArrayProxy_class *)opaque_value;
        argv[3] = AP_value.values(ctx, AP_value.opaque, 0, false);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValue, &argv[3]);
    }
    if(JS_IsArray(argv[3]) == 1) {
        if(JS_GetLength(ctx,argv[3],&size_value)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        value = (float *)js_malloc(ctx, size_value * sizeof(float));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, value);
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[3],i0);
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
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, argv[3]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            JSValue da_value = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            value+=offset_value;
            size_value-=offset_value;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_value);
        }
        else {
            double double_js_value;
            int err_js_value = JS_ToFloat64(ctx, &double_js_value, argv[3]);
            if(err_js_value<0) {
                memoryClear(ctx, memoryHead);
                JS_ThrowTypeError(ctx, "argv[3] is not numeric");
                return JS_EXCEPTION;
            }
            float js_value = (float)double_js_value;
            value = &js_value;
        }
    }
    double double_minValue;
    int err_minValue = JS_ToFloat64(ctx, &double_minValue, argv[4]);
    if(err_minValue<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float minValue = (float)double_minValue;
    double double_maxValue;
    int err_maxValue = JS_ToFloat64(ctx, &double_maxValue, argv[5]);
    if(err_maxValue<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[5] is not numeric");
        return JS_EXCEPTION;
    }
    float maxValue = (float)double_maxValue;
    int returnVal = GuiSlider(bounds, (const char *)textLeft, (const char *)textRight, value, minValue, maxValue);
    if(JS_IsArray(argv[3]) == 1) {
        JSValue js_argv3 = JS_NewFloat64(ctx, (double)value[0]);
        JS_DefinePropertyValueUint32(ctx,argv[3],0,js_argv3,JS_PROP_C_W_E);
    }
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiSliderBar(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * textLeft;
    int64_t size_textLeft;
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        textLeft = NULL;
    }
    else if(JS_IsString(argv[1]) == 1) {
        textLeft = (char *)JS_ToCStringLen(ctx, &size_textLeft, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, textLeft);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_textLeft;
        textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, textLeft);
    }
    else {
        JSClassID classid_textLeft = JS_GetClassID(argv[1]);
        if(classid_textLeft==JS_CLASS_INT8_ARRAY) {
            size_t offset_textLeft;
            size_t size_textLeft;
            JSValue da_textLeft = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_textLeft,&size_textLeft,NULL);
            textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, da_textLeft);
            textLeft+=offset_textLeft;
            size_textLeft-=offset_textLeft;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_textLeft);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * textRight;
    int64_t size_textRight;
    if(JS_IsString(argv[2]) == 1) {
        textRight = (char *)JS_ToCStringLen(ctx, &size_textRight, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, textRight);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_textRight;
        textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, textRight);
    }
    else {
        JSClassID classid_textRight = JS_GetClassID(argv[2]);
        if(classid_textRight==JS_CLASS_INT8_ARRAY) {
            size_t offset_textRight;
            size_t size_textRight;
            JSValue da_textRight = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textRight,&size_textRight,NULL);
            textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, da_textRight);
            textRight+=offset_textRight;
            size_textRight-=offset_textRight;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_textRight);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[2] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    float * value;
    int64_t size_value;
    if(JS_GetClassID(argv[3]) == js_ArrayProxy_class_id) {
        void * opaque_value = JS_GetOpaque(argv[3], js_ArrayProxy_class_id);
        ArrayProxy_class AP_value = *(ArrayProxy_class *)opaque_value;
        argv[3] = AP_value.values(ctx, AP_value.opaque, 0, false);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValue, &argv[3]);
    }
    if(JS_IsArray(argv[3]) == 1) {
        if(JS_GetLength(ctx,argv[3],&size_value)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        value = (float *)js_malloc(ctx, size_value * sizeof(float));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, value);
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[3],i0);
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
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, argv[3]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            JSValue da_value = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            value+=offset_value;
            size_value-=offset_value;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_value);
        }
        else {
            double double_js_value;
            int err_js_value = JS_ToFloat64(ctx, &double_js_value, argv[3]);
            if(err_js_value<0) {
                memoryClear(ctx, memoryHead);
                JS_ThrowTypeError(ctx, "argv[3] is not numeric");
                return JS_EXCEPTION;
            }
            float js_value = (float)double_js_value;
            value = &js_value;
        }
    }
    double double_minValue;
    int err_minValue = JS_ToFloat64(ctx, &double_minValue, argv[4]);
    if(err_minValue<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float minValue = (float)double_minValue;
    double double_maxValue;
    int err_maxValue = JS_ToFloat64(ctx, &double_maxValue, argv[5]);
    if(err_maxValue<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[5] is not numeric");
        return JS_EXCEPTION;
    }
    float maxValue = (float)double_maxValue;
    int returnVal = GuiSliderBar(bounds, (const char *)textLeft, (const char *)textRight, value, minValue, maxValue);
    if(JS_IsArray(argv[3]) == 1) {
        JSValue js_argv3 = JS_NewFloat64(ctx, (double)value[0]);
        JS_DefinePropertyValueUint32(ctx,argv[3],0,js_argv3,JS_PROP_C_W_E);
    }
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiProgressBar(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * textLeft;
    int64_t size_textLeft;
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        textLeft = NULL;
    }
    else if(JS_IsString(argv[1]) == 1) {
        textLeft = (char *)JS_ToCStringLen(ctx, &size_textLeft, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, textLeft);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_textLeft;
        textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, textLeft);
    }
    else {
        JSClassID classid_textLeft = JS_GetClassID(argv[1]);
        if(classid_textLeft==JS_CLASS_INT8_ARRAY) {
            size_t offset_textLeft;
            size_t size_textLeft;
            JSValue da_textLeft = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_textLeft,&size_textLeft,NULL);
            textLeft = (char *)JS_GetArrayBuffer(ctx, &size_textLeft, da_textLeft);
            textLeft+=offset_textLeft;
            size_textLeft-=offset_textLeft;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_textLeft);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * textRight;
    int64_t size_textRight;
    if(JS_IsString(argv[2]) == 1) {
        textRight = (char *)JS_ToCStringLen(ctx, &size_textRight, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, textRight);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_textRight;
        textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, textRight);
    }
    else {
        JSClassID classid_textRight = JS_GetClassID(argv[2]);
        if(classid_textRight==JS_CLASS_INT8_ARRAY) {
            size_t offset_textRight;
            size_t size_textRight;
            JSValue da_textRight = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_textRight,&size_textRight,NULL);
            textRight = (char *)JS_GetArrayBuffer(ctx, &size_textRight, da_textRight);
            textRight+=offset_textRight;
            size_textRight-=offset_textRight;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_textRight);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[2] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    float * value;
    int64_t size_value;
    if(JS_GetClassID(argv[3]) == js_ArrayProxy_class_id) {
        void * opaque_value = JS_GetOpaque(argv[3], js_ArrayProxy_class_id);
        ArrayProxy_class AP_value = *(ArrayProxy_class *)opaque_value;
        argv[3] = AP_value.values(ctx, AP_value.opaque, 0, false);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValue, &argv[3]);
    }
    if(JS_IsArray(argv[3]) == 1) {
        if(JS_GetLength(ctx,argv[3],&size_value)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        value = (float *)js_malloc(ctx, size_value * sizeof(float));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, value);
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[3],i0);
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
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, argv[3]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[3]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            JSValue da_value = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            value+=offset_value;
            size_value-=offset_value;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_value);
        }
        else {
            double double_js_value;
            int err_js_value = JS_ToFloat64(ctx, &double_js_value, argv[3]);
            if(err_js_value<0) {
                memoryClear(ctx, memoryHead);
                JS_ThrowTypeError(ctx, "argv[3] is not numeric");
                return JS_EXCEPTION;
            }
            float js_value = (float)double_js_value;
            value = &js_value;
        }
    }
    double double_minValue;
    int err_minValue = JS_ToFloat64(ctx, &double_minValue, argv[4]);
    if(err_minValue<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[4] is not numeric");
        return JS_EXCEPTION;
    }
    float minValue = (float)double_minValue;
    double double_maxValue;
    int err_maxValue = JS_ToFloat64(ctx, &double_maxValue, argv[5]);
    if(err_maxValue<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[5] is not numeric");
        return JS_EXCEPTION;
    }
    float maxValue = (float)double_maxValue;
    int returnVal = GuiProgressBar(bounds, (const char *)textLeft, (const char *)textRight, value, minValue, maxValue);
    if(JS_IsArray(argv[3]) == 1) {
        JSValue js_argv3 = JS_NewFloat64(ctx, (double)value[0]);
        JS_DefinePropertyValueUint32(ctx,argv[3],0,js_argv3,JS_PROP_C_W_E);
    }
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiStatusBar(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int returnVal = GuiStatusBar(bounds, (const char *)text);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiDummyRec(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int returnVal = GuiDummyRec(bounds, (const char *)text);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiGrid(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        text = NULL;
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    double double_spacing;
    int err_spacing = JS_ToFloat64(ctx, &double_spacing, argv[2]);
    if(err_spacing<0) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
    float spacing = (float)double_spacing;
    int32_t long_subdivs;
    int err_subdivs = JS_ToInt32(ctx, &long_subdivs, argv[3]);
    if(err_subdivs<0) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
    int subdivs = (int)long_subdivs;
    Vector2 * mouseCell = (Vector2 *)JS_GetOpaque(argv[4], js_Vector2_class_id);
    if(mouseCell == NULL) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
        JS_ThrowTypeError(ctx, "argv[4] does not match type Vector2");
        return JS_EXCEPTION;
    }
    int returnVal = GuiGrid(bounds, (const char *)text, spacing, subdivs, mouseCell);
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
    }
    else if(JS_IsArray(argv[1]) == 1) {
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiListView(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    int * scrollIndex;
    bool freesrc_scrollIndex = false;
    JSValue da_scrollIndex;
    int64_t size_scrollIndex;
    if(JS_GetClassID(argv[2]) == js_ArrayProxy_class_id) {
        void * opaque_scrollIndex = JS_GetOpaque(argv[2], js_ArrayProxy_class_id);
        ArrayProxy_class AP_scrollIndex = *(ArrayProxy_class *)opaque_scrollIndex;
        argv[2] = AP_scrollIndex.values(ctx, AP_scrollIndex.opaque, 0, false);
        freesrc_scrollIndex = true;
    }
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_scrollIndex)==-1) {
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
            return JS_EXCEPTION;
        }
        scrollIndex = (int *)js_malloc(ctx, size_scrollIndex * sizeof(int));
        for(int i0=0; i0 < size_scrollIndex; i0++){
            JSValue js_scrollIndex = JS_GetPropertyUint32(ctx,argv[2],i0);
            int32_t long_scrollIndexi0;
            int err_scrollIndexi0 = JS_ToInt32(ctx, &long_scrollIndexi0, js_scrollIndex);
            if(err_scrollIndexi0<0) {
                JS_ThrowTypeError(ctx, "js_scrollIndex is not numeric");
                return JS_EXCEPTION;
            }
            scrollIndex[i0] = (int)long_scrollIndexi0;
            JS_FreeValue(ctx, js_scrollIndex);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_scrollIndex;
        scrollIndex = (int *)JS_GetArrayBuffer(ctx, &size_scrollIndex, argv[2]);
    }
    else {
        JSClassID classid_scrollIndex = JS_GetClassID(argv[2]);
        if(classid_scrollIndex==JS_CLASS_INT16_ARRAY) {
            size_t offset_scrollIndex;
            size_t size_scrollIndex;
            da_scrollIndex = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_scrollIndex,&size_scrollIndex,NULL);
            scrollIndex = (int *)JS_GetArrayBuffer(ctx, &size_scrollIndex, da_scrollIndex);
            scrollIndex+=offset_scrollIndex;
            size_scrollIndex-=offset_scrollIndex;
        }
        else {
            int32_t long_js_scrollIndex;
            int err_js_scrollIndex = JS_ToInt32(ctx, &long_js_scrollIndex, argv[2]);
            if(err_js_scrollIndex<0) {
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
            int js_scrollIndex = (int)long_js_scrollIndex;
            scrollIndex = &js_scrollIndex;
        }
    }
    int * active;
    bool freesrc_active = false;
    JSValue da_active;
    int64_t size_active;
    if(JS_GetClassID(argv[3]) == js_ArrayProxy_class_id) {
        void * opaque_active = JS_GetOpaque(argv[3], js_ArrayProxy_class_id);
        ArrayProxy_class AP_active = *(ArrayProxy_class *)opaque_active;
        argv[3] = AP_active.values(ctx, AP_active.opaque, 0, false);
        freesrc_active = true;
    }
    if(JS_IsArray(argv[3]) == 1) {
        if(JS_GetLength(ctx,argv[3],&size_active)==-1) {
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
            if(JS_IsArray(argv[2]) == 1) {
                js_free(ctx, scrollIndex);
            }
            else if(JS_IsArrayBuffer(argv[2]) == 1) {
                JS_FreeValue(ctx, da_scrollIndex);
            }
            else {
                JSClassID classid_scrollIndex = JS_GetClassID(argv[2]);
                if(classid_scrollIndex==JS_CLASS_INT16_ARRAY) {
                    js_free(ctx, &da_scrollIndex);
                }
            }
            return JS_EXCEPTION;
        }
        active = (int *)js_malloc(ctx, size_active * sizeof(int));
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[3],i0);
            int32_t long_activei0;
            int err_activei0 = JS_ToInt32(ctx, &long_activei0, js_active);
            if(err_activei0<0) {
                JS_ThrowTypeError(ctx, "js_active is not numeric");
                return JS_EXCEPTION;
            }
            active[i0] = (int)long_activei0;
            JS_FreeValue(ctx, js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        size_t size_active;
        active = (int *)JS_GetArrayBuffer(ctx, &size_active, argv[3]);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[3]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            size_t offset_active;
            size_t size_active;
            da_active = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_active,&size_active,NULL);
            active = (int *)JS_GetArrayBuffer(ctx, &size_active, da_active);
            active+=offset_active;
            size_active-=offset_active;
        }
        else {
            int32_t long_js_active;
            int err_js_active = JS_ToInt32(ctx, &long_js_active, argv[3]);
            if(err_js_active<0) {
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
                if(JS_IsArray(argv[2]) == 1) {
                    js_free(ctx, scrollIndex);
                }
                else if(JS_IsArrayBuffer(argv[2]) == 1) {
                    JS_FreeValue(ctx, da_scrollIndex);
                }
                else {
                    JSClassID classid_scrollIndex = JS_GetClassID(argv[2]);
                    if(classid_scrollIndex==JS_CLASS_INT16_ARRAY) {
                        js_free(ctx, &da_scrollIndex);
                    }
                }
                JS_ThrowTypeError(ctx, "argv[3] is not numeric");
                return JS_EXCEPTION;
            }
            int js_active = (int)long_js_active;
            active = &js_active;
        }
    }
    int returnVal = GuiListView(bounds, (const char *)text, scrollIndex, active);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewInt32(ctx, (long)scrollIndex[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
    if(JS_IsArray(argv[3]) == 1) {
        JSValue js_argv3 = JS_NewInt32(ctx, (long)active[0]);
        JS_DefinePropertyValueUint32(ctx,argv[3],0,js_argv3,JS_PROP_C_W_E);
    }
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
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, scrollIndex);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_scrollIndex);
    }
    else {
        JSClassID classid_scrollIndex = JS_GetClassID(argv[2]);
        if(classid_scrollIndex==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &da_scrollIndex);
        }
    }
    if(JS_IsArray(argv[3]) == 1) {
        js_free(ctx, active);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        JS_FreeValue(ctx, da_active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[3]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            js_free(ctx, &da_active);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiListViewEx(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * * text;
    int64_t size_text;
    if(JS_GetClassID(argv[1]) == js_ArrayProxy_class_id) {
        void * opaque_text = JS_GetOpaque(argv[1], js_ArrayProxy_class_id);
        ArrayProxy_class AP_text = *(ArrayProxy_class *)opaque_text;
        argv[1] = AP_text.values(ctx, AP_text.opaque, 0, false);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValue, &argv[1]);
    }
    if(JS_IsArray(argv[1]) == 1) {
        if(JS_GetLength(ctx,argv[1],&size_text)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        text = (char * *)js_malloc(ctx, size_text * sizeof(char *));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, text);
        for(int i0=0; i0 < size_text; i0++){
            JSValue js_text = JS_GetPropertyUint32(ctx,argv[1],i0);
            int64_t size_texti0;
            if(JS_IsString(js_text) == 1) {
                text[i0] = (char *)JS_ToCStringLen(ctx, &size_texti0, js_text);
                memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text[i0]);
            }
            else if(JS_IsArrayBuffer(js_text) == 1) {
                size_t size_texti0;
                text[i0] = (char *)JS_GetArrayBuffer(ctx, &size_texti0, js_text);
                memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, text[i0]);
            }
            else {
                JSClassID classid_texti0 = JS_GetClassID(js_text);
                if(classid_texti0==JS_CLASS_INT8_ARRAY) {
                    size_t offset_texti0;
                    size_t size_texti0;
                    JSValue da_texti0 = JS_GetTypedArrayBuffer(ctx,js_text,&offset_texti0,&size_texti0,NULL);
                    text[i0] = (char *)JS_GetArrayBuffer(ctx, &size_texti0, da_texti0);
                    text[i0]+=offset_texti0;
                    size_texti0-=offset_texti0;
                    memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_texti0);
                }
                else {
                    JS_ThrowTypeError(ctx, "js_text does not match type char *");
                    return JS_EXCEPTION;
                }
            }
            JS_FreeValue(ctx, js_text);
        }
    }
    else {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[1] does not match type char * *");
        return JS_EXCEPTION;
    }
    int32_t long_count;
    int err_count = JS_ToInt32(ctx, &long_count, argv[2]);
    if(err_count<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[2] is not numeric");
        return JS_EXCEPTION;
    }
    int count = (int)long_count;
    int * scrollIndex;
    int64_t size_scrollIndex;
    if(JS_GetClassID(argv[3]) == js_ArrayProxy_class_id) {
        void * opaque_scrollIndex = JS_GetOpaque(argv[3], js_ArrayProxy_class_id);
        ArrayProxy_class AP_scrollIndex = *(ArrayProxy_class *)opaque_scrollIndex;
        argv[3] = AP_scrollIndex.values(ctx, AP_scrollIndex.opaque, 0, false);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValue, &argv[3]);
    }
    if(JS_IsArray(argv[3]) == 1) {
        if(JS_GetLength(ctx,argv[3],&size_scrollIndex)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        scrollIndex = (int *)js_malloc(ctx, size_scrollIndex * sizeof(int));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, scrollIndex);
        for(int i0=0; i0 < size_scrollIndex; i0++){
            JSValue js_scrollIndex = JS_GetPropertyUint32(ctx,argv[3],i0);
            int32_t long_scrollIndexi0;
            int err_scrollIndexi0 = JS_ToInt32(ctx, &long_scrollIndexi0, js_scrollIndex);
            if(err_scrollIndexi0<0) {
                JS_ThrowTypeError(ctx, "js_scrollIndex is not numeric");
                return JS_EXCEPTION;
            }
            scrollIndex[i0] = (int)long_scrollIndexi0;
            JS_FreeValue(ctx, js_scrollIndex);
        }
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        size_t size_scrollIndex;
        scrollIndex = (int *)JS_GetArrayBuffer(ctx, &size_scrollIndex, argv[3]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, scrollIndex);
    }
    else {
        JSClassID classid_scrollIndex = JS_GetClassID(argv[3]);
        if(classid_scrollIndex==JS_CLASS_INT16_ARRAY) {
            size_t offset_scrollIndex;
            size_t size_scrollIndex;
            JSValue da_scrollIndex = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_scrollIndex,&size_scrollIndex,NULL);
            scrollIndex = (int *)JS_GetArrayBuffer(ctx, &size_scrollIndex, da_scrollIndex);
            scrollIndex+=offset_scrollIndex;
            size_scrollIndex-=offset_scrollIndex;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_scrollIndex);
        }
        else {
            int32_t long_js_scrollIndex;
            int err_js_scrollIndex = JS_ToInt32(ctx, &long_js_scrollIndex, argv[3]);
            if(err_js_scrollIndex<0) {
                memoryClear(ctx, memoryHead);
                JS_ThrowTypeError(ctx, "argv[3] is not numeric");
                return JS_EXCEPTION;
            }
            int js_scrollIndex = (int)long_js_scrollIndex;
            scrollIndex = &js_scrollIndex;
        }
    }
    int * active;
    int64_t size_active;
    if(JS_GetClassID(argv[4]) == js_ArrayProxy_class_id) {
        void * opaque_active = JS_GetOpaque(argv[4], js_ArrayProxy_class_id);
        ArrayProxy_class AP_active = *(ArrayProxy_class *)opaque_active;
        argv[4] = AP_active.values(ctx, AP_active.opaque, 0, false);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValue, &argv[4]);
    }
    if(JS_IsArray(argv[4]) == 1) {
        if(JS_GetLength(ctx,argv[4],&size_active)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        active = (int *)js_malloc(ctx, size_active * sizeof(int));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, active);
        for(int i0=0; i0 < size_active; i0++){
            JSValue js_active = JS_GetPropertyUint32(ctx,argv[4],i0);
            int32_t long_activei0;
            int err_activei0 = JS_ToInt32(ctx, &long_activei0, js_active);
            if(err_activei0<0) {
                JS_ThrowTypeError(ctx, "js_active is not numeric");
                return JS_EXCEPTION;
            }
            active[i0] = (int)long_activei0;
            JS_FreeValue(ctx, js_active);
        }
    }
    else if(JS_IsArrayBuffer(argv[4]) == 1) {
        size_t size_active;
        active = (int *)JS_GetArrayBuffer(ctx, &size_active, argv[4]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, active);
    }
    else {
        JSClassID classid_active = JS_GetClassID(argv[4]);
        if(classid_active==JS_CLASS_INT16_ARRAY) {
            size_t offset_active;
            size_t size_active;
            JSValue da_active = JS_GetTypedArrayBuffer(ctx,argv[4],&offset_active,&size_active,NULL);
            active = (int *)JS_GetArrayBuffer(ctx, &size_active, da_active);
            active+=offset_active;
            size_active-=offset_active;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_active);
        }
        else {
            int32_t long_js_active;
            int err_js_active = JS_ToInt32(ctx, &long_js_active, argv[4]);
            if(err_js_active<0) {
                memoryClear(ctx, memoryHead);
                JS_ThrowTypeError(ctx, "argv[4] is not numeric");
                return JS_EXCEPTION;
            }
            int js_active = (int)long_js_active;
            active = &js_active;
        }
    }
    int * focus;
    int64_t size_focus;
    if(JS_GetClassID(argv[5]) == js_ArrayProxy_class_id) {
        void * opaque_focus = JS_GetOpaque(argv[5], js_ArrayProxy_class_id);
        ArrayProxy_class AP_focus = *(ArrayProxy_class *)opaque_focus;
        argv[5] = AP_focus.values(ctx, AP_focus.opaque, 0, false);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValue, &argv[5]);
    }
    if(JS_IsArray(argv[5]) == 1) {
        if(JS_GetLength(ctx,argv[5],&size_focus)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        focus = (int *)js_malloc(ctx, size_focus * sizeof(int));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, focus);
        for(int i0=0; i0 < size_focus; i0++){
            JSValue js_focus = JS_GetPropertyUint32(ctx,argv[5],i0);
            int32_t long_focusi0;
            int err_focusi0 = JS_ToInt32(ctx, &long_focusi0, js_focus);
            if(err_focusi0<0) {
                JS_ThrowTypeError(ctx, "js_focus is not numeric");
                return JS_EXCEPTION;
            }
            focus[i0] = (int)long_focusi0;
            JS_FreeValue(ctx, js_focus);
        }
    }
    else if(JS_IsArrayBuffer(argv[5]) == 1) {
        size_t size_focus;
        focus = (int *)JS_GetArrayBuffer(ctx, &size_focus, argv[5]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, focus);
    }
    else {
        JSClassID classid_focus = JS_GetClassID(argv[5]);
        if(classid_focus==JS_CLASS_INT16_ARRAY) {
            size_t offset_focus;
            size_t size_focus;
            JSValue da_focus = JS_GetTypedArrayBuffer(ctx,argv[5],&offset_focus,&size_focus,NULL);
            focus = (int *)JS_GetArrayBuffer(ctx, &size_focus, da_focus);
            focus+=offset_focus;
            size_focus-=offset_focus;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_focus);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[5] does not match type int *");
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiListViewEx(bounds, (const char * *)text, count, scrollIndex, active, focus);
    if(JS_IsArray(argv[3]) == 1) {
        JSValue js_argv3 = JS_NewInt32(ctx, (long)scrollIndex[0]);
        JS_DefinePropertyValueUint32(ctx,argv[3],0,js_argv3,JS_PROP_C_W_E);
    }
    if(JS_IsArray(argv[4]) == 1) {
        JSValue js_argv4 = JS_NewInt32(ctx, (long)active[0]);
        JS_DefinePropertyValueUint32(ctx,argv[4],0,js_argv4,JS_PROP_C_W_E);
    }
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiMessageBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * title;
    int64_t size_title;
    if(JS_IsString(argv[1]) == 1) {
        title = (char *)JS_ToCStringLen(ctx, &size_title, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, title);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_title;
        title = (char *)JS_GetArrayBuffer(ctx, &size_title, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[1]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            size_t offset_title;
            size_t size_title;
            JSValue da_title = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_title,&size_title,NULL);
            title = (char *)JS_GetArrayBuffer(ctx, &size_title, da_title);
            title+=offset_title;
            size_title-=offset_title;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_title);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * message;
    int64_t size_message;
    if(JS_IsString(argv[2]) == 1) {
        message = (char *)JS_ToCStringLen(ctx, &size_message, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, message);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_message;
        message = (char *)JS_GetArrayBuffer(ctx, &size_message, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, message);
    }
    else {
        JSClassID classid_message = JS_GetClassID(argv[2]);
        if(classid_message==JS_CLASS_INT8_ARRAY) {
            size_t offset_message;
            size_t size_message;
            JSValue da_message = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_message,&size_message,NULL);
            message = (char *)JS_GetArrayBuffer(ctx, &size_message, da_message);
            message+=offset_message;
            size_message-=offset_message;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_message);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[2] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * buttons;
    int64_t size_buttons;
    if(JS_IsString(argv[3]) == 1) {
        buttons = (char *)JS_ToCStringLen(ctx, &size_buttons, argv[3]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, buttons);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        size_t size_buttons;
        buttons = (char *)JS_GetArrayBuffer(ctx, &size_buttons, argv[3]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, buttons);
    }
    else {
        JSClassID classid_buttons = JS_GetClassID(argv[3]);
        if(classid_buttons==JS_CLASS_INT8_ARRAY) {
            size_t offset_buttons;
            size_t size_buttons;
            JSValue da_buttons = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_buttons,&size_buttons,NULL);
            buttons = (char *)JS_GetArrayBuffer(ctx, &size_buttons, da_buttons);
            buttons+=offset_buttons;
            size_buttons-=offset_buttons;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_buttons);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[3] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int returnVal = GuiMessageBox(bounds, (const char *)title, (const char *)message, (const char *)buttons);
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiTextInputBox(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    memoryNode * memoryHead = (memoryNode *)calloc(1,sizeof(memoryNode));
    memoryNode * memoryCurrent = memoryHead;
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * title;
    int64_t size_title;
    if(JS_IsString(argv[1]) == 1) {
        title = (char *)JS_ToCStringLen(ctx, &size_title, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, title);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_title;
        title = (char *)JS_GetArrayBuffer(ctx, &size_title, argv[1]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, title);
    }
    else {
        JSClassID classid_title = JS_GetClassID(argv[1]);
        if(classid_title==JS_CLASS_INT8_ARRAY) {
            size_t offset_title;
            size_t size_title;
            JSValue da_title = JS_GetTypedArrayBuffer(ctx,argv[1],&offset_title,&size_title,NULL);
            title = (char *)JS_GetArrayBuffer(ctx, &size_title, da_title);
            title+=offset_title;
            size_title-=offset_title;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_title);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * message;
    int64_t size_message;
    if(JS_IsString(argv[2]) == 1) {
        message = (char *)JS_ToCStringLen(ctx, &size_message, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, message);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_message;
        message = (char *)JS_GetArrayBuffer(ctx, &size_message, argv[2]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, message);
    }
    else {
        JSClassID classid_message = JS_GetClassID(argv[2]);
        if(classid_message==JS_CLASS_INT8_ARRAY) {
            size_t offset_message;
            size_t size_message;
            JSValue da_message = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_message,&size_message,NULL);
            message = (char *)JS_GetArrayBuffer(ctx, &size_message, da_message);
            message+=offset_message;
            size_message-=offset_message;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_message);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[2] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * buttons;
    int64_t size_buttons;
    if(JS_IsString(argv[3]) == 1) {
        buttons = (char *)JS_ToCStringLen(ctx, &size_buttons, argv[3]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, buttons);
    }
    else if(JS_IsArrayBuffer(argv[3]) == 1) {
        size_t size_buttons;
        buttons = (char *)JS_GetArrayBuffer(ctx, &size_buttons, argv[3]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, buttons);
    }
    else {
        JSClassID classid_buttons = JS_GetClassID(argv[3]);
        if(classid_buttons==JS_CLASS_INT8_ARRAY) {
            size_t offset_buttons;
            size_t size_buttons;
            JSValue da_buttons = JS_GetTypedArrayBuffer(ctx,argv[3],&offset_buttons,&size_buttons,NULL);
            buttons = (char *)JS_GetArrayBuffer(ctx, &size_buttons, da_buttons);
            buttons+=offset_buttons;
            size_buttons-=offset_buttons;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_buttons);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[3] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    char * text;
    int64_t size_text;
    if(JS_IsString(argv[4]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[4]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeCString, text);
    }
    else if(JS_IsArrayBuffer(argv[4]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[4]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, text);
    }
    else {
        JSClassID classid_text = JS_GetClassID(argv[4]);
        if(classid_text==JS_CLASS_INT8_ARRAY) {
            size_t offset_text;
            size_t size_text;
            JSValue da_text = JS_GetTypedArrayBuffer(ctx,argv[4],&offset_text,&size_text,NULL);
            text = (char *)JS_GetArrayBuffer(ctx, &size_text, da_text);
            text+=offset_text;
            size_text-=offset_text;
            memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, &da_text);
        }
        else {
            memoryClear(ctx, memoryHead);
            JS_ThrowTypeError(ctx, "argv[4] does not match type char *");
            return JS_EXCEPTION;
        }
    }
    int32_t long_textMaxSize;
    int err_textMaxSize = JS_ToInt32(ctx, &long_textMaxSize, argv[5]);
    if(err_textMaxSize<0) {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[5] is not numeric");
        return JS_EXCEPTION;
    }
    int textMaxSize = (int)long_textMaxSize;
    bool * secretViewActive;
    int64_t size_secretViewActive;
    if(JS_IsNull(argv[6]) || JS_IsUndefined(argv[6])) {
        secretViewActive = NULL;
    }
    else if(JS_GetClassID(argv[6]) == js_ArrayProxy_class_id) {
        void * opaque_secretViewActive = JS_GetOpaque(argv[6], js_ArrayProxy_class_id);
        ArrayProxy_class AP_secretViewActive = *(ArrayProxy_class *)opaque_secretViewActive;
        argv[6] = AP_secretViewActive.values(ctx, AP_secretViewActive.opaque, 0, false);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValue, &argv[6]);
    }
    else if(JS_IsArray(argv[6]) == 1) {
        if(JS_GetLength(ctx,argv[6],&size_secretViewActive)==-1) {
            memoryClear(ctx, memoryHead);
            return JS_EXCEPTION;
        }
        secretViewActive = (bool *)js_malloc(ctx, size_secretViewActive * sizeof(bool));
        memoryCurrent = memoryStore(memoryCurrent, (void *)js_free, secretViewActive);
        for(int i0=0; i0 < size_secretViewActive; i0++){
            JSValue js_secretViewActive = JS_GetPropertyUint32(ctx,argv[6],i0);
            int js_secretViewActivei0 = JS_ToBool(ctx, js_secretViewActive);
            if(js_secretViewActivei0<0) {
                JS_ThrowTypeError(ctx, "js_secretViewActive is not a bool");
                return JS_EXCEPTION;
            }
            secretViewActive[i0] = js_secretViewActivei0;
            JS_FreeValue(ctx, js_secretViewActive);
        }
    }
    else if(JS_IsArrayBuffer(argv[6]) == 1) {
        size_t size_secretViewActive;
        secretViewActive = (bool *)JS_GetArrayBuffer(ctx, &size_secretViewActive, argv[6]);
        memoryCurrent = memoryStore(memoryCurrent, (void *)JS_FreeValuePtr, secretViewActive);
    }
    else {
        memoryClear(ctx, memoryHead);
        JS_ThrowTypeError(ctx, "argv[6] does not match type bool *");
        return JS_EXCEPTION;
    }
    int returnVal = GuiTextInputBox(bounds, (const char *)title, (const char *)message, (const char *)buttons, text, textMaxSize, secretViewActive);
    memoryClear(ctx, memoryHead);
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiColorPicker(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        text = NULL;
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    Color * color = (Color *)JS_GetOpaque(argv[2], js_Color_class_id);
    if(color == NULL) {
        if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        }
        else if(JS_IsArray(argv[1]) == 1) {
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
        JS_ThrowTypeError(ctx, "argv[2] does not match type Color");
        return JS_EXCEPTION;
    }
    int returnVal = GuiColorPicker(bounds, (const char *)text, color);
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
    }
    else if(JS_IsArray(argv[1]) == 1) {
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiColorPanel(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    Color * color = (Color *)JS_GetOpaque(argv[2], js_Color_class_id);
    if(color == NULL) {
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
        JS_ThrowTypeError(ctx, "argv[2] does not match type Color");
        return JS_EXCEPTION;
    }
    int returnVal = GuiColorPanel(bounds, (const char *)text, color);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiColorBarAlpha(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
        text = NULL;
    }
    else if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    float * alpha;
    bool freesrc_alpha = false;
    JSValue da_alpha;
    int64_t size_alpha;
    if(JS_GetClassID(argv[2]) == js_ArrayProxy_class_id) {
        void * opaque_alpha = JS_GetOpaque(argv[2], js_ArrayProxy_class_id);
        ArrayProxy_class AP_alpha = *(ArrayProxy_class *)opaque_alpha;
        argv[2] = AP_alpha.values(ctx, AP_alpha.opaque, 0, false);
        freesrc_alpha = true;
    }
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_alpha)==-1) {
            if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
            }
            else if(JS_IsArray(argv[1]) == 1) {
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
            return JS_EXCEPTION;
        }
        alpha = (float *)js_malloc(ctx, size_alpha * sizeof(float));
        for(int i0=0; i0 < size_alpha; i0++){
            JSValue js_alpha = JS_GetPropertyUint32(ctx,argv[2],i0);
            double double_alphai0;
            int err_alphai0 = JS_ToFloat64(ctx, &double_alphai0, js_alpha);
            if(err_alphai0<0) {
                JS_ThrowTypeError(ctx, "js_alpha is not numeric");
                return JS_EXCEPTION;
            }
            alpha[i0] = (float)double_alphai0;
            JS_FreeValue(ctx, js_alpha);
        }
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_alpha;
        alpha = (float *)JS_GetArrayBuffer(ctx, &size_alpha, argv[2]);
    }
    else {
        JSClassID classid_alpha = JS_GetClassID(argv[2]);
        if(classid_alpha==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_alpha;
            size_t size_alpha;
            da_alpha = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_alpha,&size_alpha,NULL);
            alpha = (float *)JS_GetArrayBuffer(ctx, &size_alpha, da_alpha);
            alpha+=offset_alpha;
            size_alpha-=offset_alpha;
        }
        else {
            double double_js_alpha;
            int err_js_alpha = JS_ToFloat64(ctx, &double_js_alpha, argv[2]);
            if(err_js_alpha<0) {
                if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
                }
                else if(JS_IsArray(argv[1]) == 1) {
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
            float js_alpha = (float)double_js_alpha;
            alpha = &js_alpha;
        }
    }
    int returnVal = GuiColorBarAlpha(bounds, (const char *)text, alpha);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewFloat64(ctx, (double)alpha[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
    if(JS_IsNull(argv[1]) || JS_IsUndefined(argv[1])) {
    }
    else if(JS_IsArray(argv[1]) == 1) {
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
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, alpha);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_alpha);
    }
    else {
        JSClassID classid_alpha = JS_GetClassID(argv[2]);
        if(classid_alpha==JS_CLASS_FLOAT32_ARRAY) {
            js_free(ctx, &da_alpha);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiColorBarHue(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    float * value;
    bool freesrc_value = false;
    JSValue da_value;
    int64_t size_value;
    if(JS_GetClassID(argv[2]) == js_ArrayProxy_class_id) {
        void * opaque_value = JS_GetOpaque(argv[2], js_ArrayProxy_class_id);
        ArrayProxy_class AP_value = *(ArrayProxy_class *)opaque_value;
        argv[2] = AP_value.values(ctx, AP_value.opaque, 0, false);
        freesrc_value = true;
    }
    if(JS_IsArray(argv[2]) == 1) {
        if(JS_GetLength(ctx,argv[2],&size_value)==-1) {
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
            return JS_EXCEPTION;
        }
        value = (float *)js_malloc(ctx, size_value * sizeof(float));
        for(int i0=0; i0 < size_value; i0++){
            JSValue js_value = JS_GetPropertyUint32(ctx,argv[2],i0);
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
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        size_t size_value;
        value = (float *)JS_GetArrayBuffer(ctx, &size_value, argv[2]);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[2]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            size_t offset_value;
            size_t size_value;
            da_value = JS_GetTypedArrayBuffer(ctx,argv[2],&offset_value,&size_value,NULL);
            value = (float *)JS_GetArrayBuffer(ctx, &size_value, da_value);
            value+=offset_value;
            size_value-=offset_value;
        }
        else {
            double double_js_value;
            int err_js_value = JS_ToFloat64(ctx, &double_js_value, argv[2]);
            if(err_js_value<0) {
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
            float js_value = (float)double_js_value;
            value = &js_value;
        }
    }
    int returnVal = GuiColorBarHue(bounds, (const char *)text, value);
    if(JS_IsArray(argv[2]) == 1) {
        JSValue js_argv2 = JS_NewFloat64(ctx, (double)value[0]);
        JS_DefinePropertyValueUint32(ctx,argv[2],0,js_argv2,JS_PROP_C_W_E);
    }
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
    if(JS_IsArray(argv[2]) == 1) {
        js_free(ctx, value);
    }
    else if(JS_IsArrayBuffer(argv[2]) == 1) {
        JS_FreeValue(ctx, da_value);
    }
    else {
        JSClassID classid_value = JS_GetClassID(argv[2]);
        if(classid_value==JS_CLASS_FLOAT32_ARRAY) {
            js_free(ctx, &da_value);
        }
    }
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiColorPickerHSV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    Vector3 * colorHsv = (Vector3 *)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(colorHsv == NULL) {
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
        JS_ThrowTypeError(ctx, "argv[2] does not match type Vector3");
        return JS_EXCEPTION;
    }
    int returnVal = GuiColorPickerHSV(bounds, (const char *)text, colorHsv);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static JSValue js_GuiColorPanelHSV(JSContext * ctx, JSValue this_val, int argc, JSValue * argv) {
    Rectangle* ptr_bounds = (Rectangle*)JS_GetOpaque(argv[0], js_Rectangle_class_id);
    if(ptr_bounds == NULL) {
        JS_ThrowTypeError(ctx, "argv[0] does not allow null");
        return JS_EXCEPTION;
    }
    Rectangle bounds = *ptr_bounds;
    char * text;
    bool freesrc_text = false;
    JSValue da_text;
    int64_t size_text;
    if(JS_IsString(argv[1]) == 1) {
        text = (char *)JS_ToCStringLen(ctx, &size_text, argv[1]);
    }
    else if(JS_IsArrayBuffer(argv[1]) == 1) {
        size_t size_text;
        text = (char *)JS_GetArrayBuffer(ctx, &size_text, argv[1]);
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
            if(freesrc_text) {
                JS_FreeValue(ctx, argv[1]);
            }
            JS_ThrowTypeError(ctx, "argv[1] does not match type char *");
            return JS_EXCEPTION;
        }
        if(freesrc_text) {
            JS_FreeValue(ctx, argv[1]);
        }
    }
    Vector3 * colorHsv = (Vector3 *)JS_GetOpaque(argv[2], js_Vector3_class_id);
    if(colorHsv == NULL) {
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
        JS_ThrowTypeError(ctx, "argv[2] does not match type Vector3");
        return JS_EXCEPTION;
    }
    int returnVal = GuiColorPanelHSV(bounds, (const char *)text, colorHsv);
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
    JSValue ret = JS_NewInt32(ctx, (long)returnVal);
    return ret;
}

static const JSCFunctionListEntry js_js_raygui_funcs[] = {
    JS_CFUNC_DEF("GuiEnable",0,js_GuiEnable),
    JS_CFUNC_DEF("GuiDisable",0,js_GuiDisable),
    JS_CFUNC_DEF("GuiLock",0,js_GuiLock),
    JS_CFUNC_DEF("GuiUnlock",0,js_GuiUnlock),
    JS_CFUNC_DEF("GuiIsLocked",0,js_GuiIsLocked),
    JS_CFUNC_DEF("GuiSetAlpha",1,js_GuiSetAlpha),
    JS_CFUNC_DEF("GuiSetState",1,js_GuiSetState),
    JS_CFUNC_DEF("GuiGetState",0,js_GuiGetState),
    JS_CFUNC_DEF("GuiSetFont",1,js_GuiSetFont),
    JS_CFUNC_DEF("GuiGetFont",0,js_GuiGetFont),
    JS_CFUNC_DEF("GuiSetStyle",3,js_GuiSetStyle),
    JS_CFUNC_DEF("GuiGetStyle",2,js_GuiGetStyle),
    JS_CFUNC_DEF("GuiLoadStyle",1,js_GuiLoadStyle),
    JS_CFUNC_DEF("GuiLoadStyleDefault",0,js_GuiLoadStyleDefault),
    JS_CFUNC_DEF("GuiEnableTooltip",0,js_GuiEnableTooltip),
    JS_CFUNC_DEF("GuiDisableTooltip",0,js_GuiDisableTooltip),
    JS_CFUNC_DEF("GuiSetTooltip",1,js_GuiSetTooltip),
    JS_CFUNC_DEF("GuiIconText",2,js_GuiIconText),
    JS_CFUNC_DEF("GuiSetIconScale",1,js_GuiSetIconScale),
    JS_CFUNC_DEF("GuiDrawIcon",5,js_GuiDrawIcon),
    JS_CFUNC_DEF("GuiWindowBox",2,js_GuiWindowBox),
    JS_CFUNC_DEF("GuiGroupBox",2,js_GuiGroupBox),
    JS_CFUNC_DEF("GuiLine",2,js_GuiLine),
    JS_CFUNC_DEF("GuiPanel",2,js_GuiPanel),
    JS_CFUNC_DEF("GuiScrollPanel",5,js_GuiScrollPanel),
    JS_CFUNC_DEF("GuiLabel",2,js_GuiLabel),
    JS_CFUNC_DEF("GuiButton",2,js_GuiButton),
    JS_CFUNC_DEF("GuiLabelButton",2,js_GuiLabelButton),
    JS_CFUNC_DEF("GuiToggle",3,js_GuiToggle),
    JS_CFUNC_DEF("GuiToggleGroup",3,js_GuiToggleGroup),
    JS_CFUNC_DEF("GuiToggleSlider",3,js_GuiToggleSlider),
    JS_CFUNC_DEF("GuiCheckBox",3,js_GuiCheckBox),
    JS_CFUNC_DEF("GuiComboBox",3,js_GuiComboBox),
    JS_CFUNC_DEF("GuiDropdownBox",4,js_GuiDropdownBox),
    JS_CFUNC_DEF("GuiSpinner",6,js_GuiSpinner),
    JS_CFUNC_DEF("GuiValueBox",6,js_GuiValueBox),
    JS_CFUNC_DEF("GuiValueBoxFloat",5,js_GuiValueBoxFloat),
    JS_CFUNC_DEF("GuiTextBox",4,js_GuiTextBox),
    JS_CFUNC_DEF("GuiSlider",6,js_GuiSlider),
    JS_CFUNC_DEF("GuiSliderBar",6,js_GuiSliderBar),
    JS_CFUNC_DEF("GuiProgressBar",6,js_GuiProgressBar),
    JS_CFUNC_DEF("GuiStatusBar",2,js_GuiStatusBar),
    JS_CFUNC_DEF("GuiDummyRec",2,js_GuiDummyRec),
    JS_CFUNC_DEF("GuiGrid",5,js_GuiGrid),
    JS_CFUNC_DEF("GuiListView",4,js_GuiListView),
    JS_CFUNC_DEF("GuiListViewEx",6,js_GuiListViewEx),
    JS_CFUNC_DEF("GuiMessageBox",4,js_GuiMessageBox),
    JS_CFUNC_DEF("GuiTextInputBox",7,js_GuiTextInputBox),
    JS_CFUNC_DEF("GuiColorPicker",3,js_GuiColorPicker),
    JS_CFUNC_DEF("GuiColorPanel",3,js_GuiColorPanel),
    JS_CFUNC_DEF("GuiColorBarAlpha",3,js_GuiColorBarAlpha),
    JS_CFUNC_DEF("GuiColorBarHue",3,js_GuiColorBarHue),
    JS_CFUNC_DEF("GuiColorPickerHSV",3,js_GuiColorPickerHSV),
    JS_CFUNC_DEF("GuiColorPanelHSV",3,js_GuiColorPanelHSV),
};

static int js_js_raygui_init(JSContext * ctx, JSModuleDef * m) {
    JS_SetModuleExportList(ctx, m,js_js_raygui_funcs,countof(js_js_raygui_funcs));
    js_declare_GuiStyleProp(ctx, m);
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
    JS_SetModuleExport(ctx, m, "CONTROL11", JS_NewInt32(ctx, CONTROL11));
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
    JS_SetModuleExport(ctx, m, "SPINNER_BUTTON_WIDTH", JS_NewInt32(ctx, SPINNER_BUTTON_WIDTH));
    JS_SetModuleExport(ctx, m, "SPINNER_BUTTON_SPACING", JS_NewInt32(ctx, SPINNER_BUTTON_SPACING));
    JS_SetModuleExport(ctx, m, "LIST_ITEMS_HEIGHT", JS_NewInt32(ctx, LIST_ITEMS_HEIGHT));
    JS_SetModuleExport(ctx, m, "LIST_ITEMS_SPACING", JS_NewInt32(ctx, LIST_ITEMS_SPACING));
    JS_SetModuleExport(ctx, m, "SCROLLBAR_WIDTH", JS_NewInt32(ctx, SCROLLBAR_WIDTH));
    JS_SetModuleExport(ctx, m, "SCROLLBAR_SIDE", JS_NewInt32(ctx, SCROLLBAR_SIDE));
    JS_SetModuleExport(ctx, m, "LIST_ITEMS_BORDER_NORMAL", JS_NewInt32(ctx, LIST_ITEMS_BORDER_NORMAL));
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
    JS_SetModuleExport(ctx, m, "ICON_LABEL", JS_NewInt32(ctx, ICON_LABEL));
    JS_SetModuleExport(ctx, m, "ICON_NAME_ID", JS_NewInt32(ctx, ICON_NAME_ID));
    JS_SetModuleExport(ctx, m, "ICON_SLICING", JS_NewInt32(ctx, ICON_SLICING));
    JS_SetModuleExport(ctx, m, "ICON_MANUAL_CONTROL", JS_NewInt32(ctx, ICON_MANUAL_CONTROL));
    JS_SetModuleExport(ctx, m, "ICON_COLLISION", JS_NewInt32(ctx, ICON_COLLISION));
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
    JS_SetModuleExport(ctx, m, "RAYGUI_VERSION_MAJOR", JS_NewInt32(ctx, RAYGUI_VERSION_MAJOR));
    JS_SetModuleExport(ctx, m, "RAYGUI_VERSION_MINOR", JS_NewInt32(ctx, RAYGUI_VERSION_MINOR));
    JS_SetModuleExport(ctx, m, "RAYGUI_VERSION_PATCH", JS_NewInt32(ctx, RAYGUI_VERSION_PATCH));
    JS_SetModuleExport(ctx, m, "SCROLLBAR_LEFT_SIDE", JS_NewInt32(ctx, SCROLLBAR_LEFT_SIDE));
    JS_SetModuleExport(ctx, m, "SCROLLBAR_RIGHT_SIDE", JS_NewInt32(ctx, SCROLLBAR_RIGHT_SIDE));
    return 0;
}

JSModuleDef * js_init_module_js_raygui(JSContext * ctx, const char * module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_js_raygui_init);
    if(!m) return NULL;
    JS_AddModuleExportList(ctx, m, js_js_raygui_funcs, countof(js_js_raygui_funcs));
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
    JS_AddModuleExport(ctx, m, "CONTROL11");
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
    JS_AddModuleExport(ctx, m, "SPINNER_BUTTON_WIDTH");
    JS_AddModuleExport(ctx, m, "SPINNER_BUTTON_SPACING");
    JS_AddModuleExport(ctx, m, "LIST_ITEMS_HEIGHT");
    JS_AddModuleExport(ctx, m, "LIST_ITEMS_SPACING");
    JS_AddModuleExport(ctx, m, "SCROLLBAR_WIDTH");
    JS_AddModuleExport(ctx, m, "SCROLLBAR_SIDE");
    JS_AddModuleExport(ctx, m, "LIST_ITEMS_BORDER_NORMAL");
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
    JS_AddModuleExport(ctx, m, "ICON_LABEL");
    JS_AddModuleExport(ctx, m, "ICON_NAME_ID");
    JS_AddModuleExport(ctx, m, "ICON_SLICING");
    JS_AddModuleExport(ctx, m, "ICON_MANUAL_CONTROL");
    JS_AddModuleExport(ctx, m, "ICON_COLLISION");
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
    JS_AddModuleExport(ctx, m, "RAYGUI_VERSION_MAJOR");
    JS_AddModuleExport(ctx, m, "RAYGUI_VERSION_MINOR");
    JS_AddModuleExport(ctx, m, "RAYGUI_VERSION_PATCH");
    JS_AddModuleExport(ctx, m, "SCROLLBAR_LEFT_SIDE");
    JS_AddModuleExport(ctx, m, "SCROLLBAR_RIGHT_SIDE");
    return m;
}

#endif // JS_js_raygui_GUARD
