#include "rayjs_base.h"

static JSValue js_navigator_get_userAgent(JSContext *ctx, JSValue this_val){
    char version[32];
    snprintf(version, sizeof(version), "quickjs-ng/%s", JS_GetVersion());
    return JS_NewString(ctx, version);
}

static const JSCFunctionListEntry navigator_proto_funcs[] = {
    JS_CGETSET_DEF2("userAgent", js_navigator_get_userAgent, NULL, JS_PROP_CONFIGURABLE | JS_PROP_ENUMERABLE),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Navigator", JS_PROP_CONFIGURABLE),
};

static JSValue js_gc(JSContext *ctx, JSValue this_val,int argc, JSValue *argv){
    JS_RunGC(JS_GetRuntime(ctx));
    return JS_UNDEFINED;
}

static const JSCFunctionListEntry global_obj[] = {
    JS_CFUNC_DEF("gc", 0, js_gc),
#if defined(__ASAN__) || defined(__UBSAN__)
    JS_PROP_INT32_DEF("__running_with_sanitizer__", 1, JS_PROP_C_W_E ),
#endif
};

#ifdef QJS_USE_MIMALLOC
#include <mimalloc.h>
static void * jsc_malloc(JSContext *ctx, size_t sz ){ return mi_malloc(sz); }
static void * jsc_calloc(JSContext *ctx, size_t n, size_t sz ){ return mi_calloc(n,sz); }
static void * jsc_realloc(JSContext *ctx, void * ptr, size_t sz ){ return mi_realloc(ptr,sz); }
static void jsc_free(JSContext *ctx, void * ptr ){ mi_free(ptr); }
#else
static void * jsc_malloc(JSContext *ctx, size_t sz ){ return malloc(sz); }
static void * jsc_calloc(JSContext *ctx, size_t n, size_t sz ){ return calloc(n,sz); }
static void * jsc_realloc(JSContext *ctx, void * ptr, size_t sz ){ return realloc(ptr,sz); }
static void jsc_free(JSContext *ctx, void * ptr ){ free(ptr); }
#endif

/* also used to initialize the worker context */
static JSContext *JS_NewCustomContext(JSRuntime *rt){
    JSContext *ctx;
    ctx = JS_NewContext(rt);
    if (!ctx){
        printf("CANT ALLOC CTX");
        return NULL;
    }
    /* system modules */
    js_init_module_std(ctx, "qjs:std");
    js_init_module_os(ctx, "qjs:os");
    js_init_module_bjson(ctx, "qjs:bjson");
    js_init_module_js_raylib(ctx, "rayjs:raylib");
    js_init_module_js_raymath(ctx, "rayjs:raymath");
    js_init_module_js_rcamera(ctx, "rayjs:rcamera");
    js_init_module_js_raygui(ctx, "rayjs:raygui");
    js_init_module_js_rlights(ctx, "rayjs:rlights");
    js_init_module_js_reasings(ctx, "rayjs:reasings");
    js_init_module_js_rlgl(ctx, "rayjs:rlgl");
    js_init_module_js_rlightmapper(ctx, "rayjs:rlightmapper");

    JSValue global = JS_GetGlobalObject(ctx);
    JS_SetPropertyFunctionList(ctx, global, global_obj, countof(global_obj));
    JS_SetPropertyFunctionList(ctx, global, &argv0, 1);
    JSValue navigator_proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, navigator_proto, navigator_proto_funcs, countof(navigator_proto_funcs));
    JSValue navigator = JS_NewObjectProto(ctx, navigator_proto);
    JS_DefinePropertyValueStr(ctx, global, "navigator", navigator, JS_PROP_CONFIGURABLE | JS_PROP_ENUMERABLE);
    JS_FreeValue(ctx, global);
    JS_FreeValue(ctx, navigator_proto);

    return ctx;
}
static JSValue copyFunction(JSContext *from_ctx, JSContext *to_ctx, JSValue fn){

    //Create (function)ObjectProtoClass from c function
    //JSValue JS_NewCFunctionData(JSContext *ctx, JSCFunctionData *func,int length, int magic, int data_len,JSValue *data)
    //ReadObject can be used to create a function in ctx from data
    //WHAT can be used to write data from JSValue function?
}
//define store function
static memoryNode* memoryStore(memoryNode *current, void * clarfunc, void * memoryptr) {
   // Saves memory for de-allocation
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
//define clear function
static void memoryClear(JSContext * ctx, memoryNode *head) {
    memoryNode * prev_node;
    while (head != NULL) {
        for (int i = 0; i < head->length; i += 2) {
            void (*free_func) (JSContext *,void *) = head->pointers[i];
            void * ptr_to_free = head->pointers[i + 1];
            free_func(ctx, ptr_to_free);
        }
        prev_node = head;
        head = head->next;
        free(prev_node);
    }
}
//define a proxy for FreeValue
static void JS_FreeValuePtr(JSContext *ctx, JSValue * v){
    JS_FreeValue(ctx,*v);
}
//Define printf dedicated for js
static char * asnprintf(JSContext * ctx, char * buffer, size_t * maxsize, const char * format, ...){
    va_list args;
    va_start(args, format);
    int len=vsnprintf(buffer,*maxsize,format,args);
    if(len>*maxsize){
        len++;
        buffer=js_realloc(ctx,buffer,len * sizeof(char));
        memset(buffer+*maxsize,0,len-*maxsize);
        maxsize[0]=len;
        len=vsnprintf(buffer,len,format,args);
    }
    va_end(args);
    return buffer;
};