#include "rayjs_base.h"

static JSValue js_gc(JSContext *ctx, JSValue this_val,int argc, JSValue *argv){
    JS_RunGC(JS_GetRuntime(ctx));
    return JS_UNDEFINED;
}

static JSValue js_navigator_get_userAgent(JSContext *ctx, JSValue this_val){
    char version[32];
    snprintf(version, sizeof(version), "quickjs-ng/%s", JS_GetVersion());
    return JS_NewString(ctx, version);
}

static const JSCFunctionListEntry navigator_proto_funcs[] = {
    JS_CGETSET_DEF2("userAgent", js_navigator_get_userAgent, NULL, JS_PROP_CONFIGURABLE | JS_PROP_ENUMERABLE),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Navigator", JS_PROP_CONFIGURABLE),
};

static const JSCFunctionListEntry global_obj[] = {
    JS_CFUNC_DEF("gc", 0, js_gc),
};


#ifdef QJS_USE_MIMALLOC
#include <mimalloc.h>
static void * jsc_malloc(JSContext *ctx, size_t sz ){ return mi_malloc(sz); }
static void * jsc_calloc(JSContext *ctx, size_t n, size_t sz ){ return mi_calloc(n,sz); }
static void * jsc_realloc(JSContext *ctx, void * ptr, size_t sz ){ return mi_realloc(ptr,sz); }
static void jsc_free(JSContext *ctx, void * ptr ){ mi_free(ptr); }
static void *js_mi_calloc(void *opaque, size_t count, size_t size){
    return mi_calloc(count, size);
}

static void *js_mi_malloc(void *opaque, size_t size){
    return mi_malloc(size);
}

static void js_mi_free(void *opaque, void *ptr){
    if (!ptr)
        return;
    mi_free(ptr);
}

static void *js_mi_realloc(void *opaque, void *ptr, size_t size){
    return mi_realloc(ptr, size);
}
static const JSMallocFunctions mi_mf = {
    js_mi_calloc,
    js_mi_malloc,
    js_mi_free,
    js_mi_realloc,
    mi_malloc_usable_size
};
#else
static void * jsc_malloc(JSContext *ctx, size_t sz ){ return malloc(sz); }
static void * jsc_calloc(JSContext *ctx, size_t n, size_t sz ){ return calloc(n,sz); }
static void * jsc_realloc(JSContext *ctx, void * ptr, size_t sz ){ return realloc(ptr,sz); }
static void jsc_free(JSContext *ctx, void * ptr ){ free(ptr); }
#endif

static JSValue app_update_finish(JSContext *ctx,int argc, JSValue *argv){
    JSValue resolve = argv[0];
    JSValue ret = JS_Call(ctx, resolve, JS_UNDEFINED,0,NULL);// resolve()
    //js_promise_resolve_function_call 0 argc is ok
    JS_FreeValue(ctx, ret);
    return JS_UNDEFINED;
}

static int app_update_quickjs(JSContext *ctx){
    //We need to call pool to allow async processing between frames
    //This basically runs await setTimeout(0)
    JSValue resolving_funcs[2];//dont set to JS_UNDEFINED, see js_promise_executor_new
    JSValue args[1];
    JSValue promise = JS_NewPromiseCapability(ctx, resolving_funcs);
    if (JS_IsException(promise)){
        return 0;
    }
    args[0]=resolving_funcs[0];
    JS_EnqueueJob(ctx, app_update_finish, 1, args);
    JSValue val = js_std_await(ctx, promise);
    if (JS_IsException(val)){
        js_std_dump_error(ctx);
    }
    JS_FreeValue(ctx, val);
    JS_FreeValue(ctx, resolving_funcs[0]);
    JS_FreeValue(ctx, resolving_funcs[1]);
    return 1;
}

static void js_declare_ArrayProxy(JSContext * ctx);
static void js_declare_ArrayProxy_RT(JSRuntime * rt);

/* also used to initialize the worker context */
static JSContext *JS_NewCustomContext(JSRuntime *rt){
    JSContext *ctx;
    ctx = JS_NewContext(rt);
    if (!ctx){
        return NULL;
    }
    /* system modules */
    js_declare_ArrayProxy(ctx);
    js_init_module_std(ctx, "qjs:std");
    js_init_module_os(ctx, "qjs:os");
    js_init_module_bjson(ctx, "qjs:bjson");
    js_init_module_raylib(ctx, "rayjs:raylib");
    js_init_module_raymath(ctx, "rayjs:raymath");
    js_init_module_rcamera(ctx, "rayjs:rcamera");
    js_init_module_raygui(ctx, "rayjs:raygui");
    js_init_module_rlights(ctx, "rayjs:rlights");
    js_init_module_reasings(ctx, "rayjs:reasings");
    js_init_module_rlgl(ctx, "rayjs:rlgl");
    js_init_module_rlightmapper(ctx, "rayjs:rlightmapper");

    JSValue global = JS_GetGlobalObject(ctx);
    JS_SetPropertyFunctionList(ctx, global, global_obj, countof(global_obj));
    JSValue args = JS_NewArray(ctx);
    int i;
    for(i = 0; i < qjs__argc; i++) {
        JS_SetPropertyUint32(ctx, args, i, JS_NewString(ctx, qjs__argv[i]));
    }
    JS_SetPropertyStr(ctx, global, "execArgv", args);
    JS_SetPropertyStr(ctx, global, "argv0", JS_NewString(ctx, qjs__argv[0]));
    JSValue navigator_proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, navigator_proto, navigator_proto_funcs, countof(navigator_proto_funcs));
    JSValue navigator = JS_NewObjectProto(ctx, navigator_proto);
    JS_DefinePropertyValueStr(ctx, global, "navigator", navigator, JS_PROP_CONFIGURABLE | JS_PROP_ENUMERABLE);
    JS_FreeValue(ctx, global);
    JS_FreeValue(ctx, navigator_proto);

    return ctx;
}

static JSRuntime* JS_NewRuntime3(){
    JSRuntime* rt;
    #ifdef QJS_USE_MIMALLOC
        rt = JS_NewRuntime2(&mi_mf, NULL);
    #else
        rt = JS_NewRuntime();
    #endif
    if(!rt)return rt;
    if (default_dump != 0)
        JS_SetDumpFlags(rt, default_dump);
    js_declare_ArrayProxy_RT(rt);
    return rt;
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
static char * asnprintf(JSContext * ctx, char * buffer, size_t * maxsize, const char * format, int skip_args, ...){
    va_list args;
    //start va_list and skip first int arguments if width, precision is not required
    va_start(args, skip_args);
    for (int i = 0; i < skip_args; i++) {
        va_arg(args, int);
    }

    int len=vsnprintf(buffer,*maxsize,format,args);
    va_end(args);
    //If reallocations are needed
    if(len>*maxsize){
        len++;//add last character \0
        //reset arguments eaten by vsnprintf
        va_start(args, skip_args);
        for (int i = 0; i < skip_args; i++) {
            va_arg(args, int);
        }
        buffer=js_realloc(ctx,buffer,len * sizeof(char));
        memset(buffer+*maxsize,0,len-*maxsize);
        maxsize[0]=len;
        vsnprintf(buffer,len,format,args);
        va_end(args);
    }
    return buffer;
};

//The iterated objet has to have setProperty JS_CLASS_ARRAY_ITERATOR:
//exists, is {obj:{},idx:int,kind:<>} where obj is not undefined
//obj is typed array or
//obj has property JS_ATOM_length
//where idx is 0..length
//when idx==length idx->obj is freed
//idx is being autoincremented
//where kind is JS_ITERATOR_KIND_KEY or JS_ITERATOR_KIND_VALUE or or JS_ITERATOR_KIND_KEY_VALUE (using magic?)
//
//all this happens in js_create_array_iterator if JS_ToObject succedes.
//If it cant, modify the code to something that works
//TODO: register js_ArrayProxy_class_id globally

//JSIteratorKindEnum, JSArrayIteratorData is qjs internal, do not expose in .h
typedef enum JSIteratorKindEnum {
    JS_ITERATOR_KIND_KEY,
    JS_ITERATOR_KIND_VALUE,
    JS_ITERATOR_KIND_KEY_AND_VALUE,
} JSIteratorKindEnum;

typedef struct JSArrayIteratorData {
    JSValue obj;
    JSIteratorKindEnum kind;
    uint32_t idx;
} JSArrayIteratorData;

static JSValue js_create_ArrayProxy_iterator(JSContext * ctx, JSValueConst this_val,int argc, JSValue * argv, int magic){
    JSValue enum_obj, arr;
    JSArrayIteratorData *it;
    JSIteratorKindEnum kind;
    int class_id;

    kind = magic & 3;

    ArrayProxy_class AP = *(ArrayProxy_class *)JS_GetOpaque2(ctx, this_val, js_ArrayProxy_class_id);
    if (magic & 4) {
        /* string iterator case */
        arr = AP.values(ctx,AP.opaque,0,true);
        class_id = JS_CLASS_STRING_ITERATOR;
    } else {
        arr = AP.values(ctx,AP.opaque,0,false);
        class_id = JS_CLASS_ARRAY_ITERATOR;
    }
    if (JS_IsException(arr))
        goto fail;
    enum_obj = JS_NewObjectClass(ctx, class_id);
    if (JS_IsException(enum_obj))
        goto fail;
    it = js_malloc(ctx, sizeof(*it));
    if (!it)
        goto fail1;
    it->obj = arr;
    it->kind = kind;
    it->idx = 0;
    JS_ForceSetOpaque(enum_obj, it);
    return enum_obj;
 fail1:
    JS_FreeValue(ctx, enum_obj);
 fail:
    JS_FreeValue(ctx, arr);
    return JS_EXCEPTION;
}

static void js_ArrayProxy_finalizer(JSRuntime * rt, JSValue val) {
    void * opaque = JS_GetOpaque(val, js_ArrayProxy_class_id);
    ArrayProxy_class AP = *(ArrayProxy_class *)opaque;
    JS_FreeValueRT(rt, AP.anchor);
    js_free_rt(rt, opaque);
}
//js_ArrayProxy_get_length
#define JS_ATOM_TAG_INT (1U << 31)
#define JS_ATOM_MAX_INT (JS_ATOM_TAG_INT - 1)
#define JS_ATOM_MAX     ((1U << 30) - 1)
static inline bool JS_AtomIsTaggedInt(JSAtom v){return (v & JS_ATOM_TAG_INT) != 0;}
static inline uint32_t JS_AtomToUInt32(JSAtom atom){return atom & ~JS_ATOM_TAG_INT;}

static JSValue js_ArrayProxy_get(JSContext *ctx, JSValue obj, JSAtom atom, JSValue receiver){
    ArrayProxy_class AP = *(ArrayProxy_class *)JS_GetOpaque2(ctx, obj, js_ArrayProxy_class_id);
    if (JS_AtomIsTaggedInt(atom)) {
        return AP.get(ctx,AP.opaque,JS_AtomToUInt32(atom),false);
    }else{
        if(atom==JS_ATOM_Symbol_iterator){
            return JS_NewCFunctionMagic(ctx,js_create_ArrayProxy_iterator,"values",0,JS_CFUNC_generic_magic,JS_ITERATOR_KIND_VALUE);
        }
        return AP.get(ctx,AP.opaque,(uint32_t)atom,true);
    }

}

static int js_ArrayProxy_set(JSContext *ctx, JSValue obj, JSAtom atom, JSValue value, JSValue receiver, int flags){
    ArrayProxy_class AP = *(ArrayProxy_class *)JS_GetOpaque2(ctx, obj, js_ArrayProxy_class_id);
    if (JS_AtomIsTaggedInt(atom)) {
        return AP.set(ctx,AP.opaque, value,JS_AtomToUInt32(atom),false);
    }else{
        return AP.set(ctx,AP.opaque, value,(uint32_t)atom,true);
    }
}

static int js_ArrayProxy_has(JSContext *ctx, JSValue obj, JSAtom atom){
    ArrayProxy_class AP = *(ArrayProxy_class *)JS_GetOpaque2(ctx, obj, js_ArrayProxy_class_id);
    if (JS_AtomIsTaggedInt(atom)) {
        return AP.has(ctx,AP.opaque,JS_AtomToUInt32(atom),false);
    }else{
        return AP.has(ctx,AP.opaque,(uint32_t)atom,true);
    }
}

static int js_ArrayProxy_delete_property(JSContext *ctx, JSValue obj, JSAtom atom){
    return js_ArrayProxy_set(ctx,obj,atom,JS_UNDEFINED,JS_UNDEFINED,0);
}

static JSValue js_ArrayProxy_get_length(JSContext * ctx, JSValue this_val){
    return js_ArrayProxy_get(ctx,this_val,JS_ATOM_length,JS_UNDEFINED);
}

static int js_ArrayProxy_keys(JSContext *ctx, JSPropertyEnum **ptab, uint32_t *plen, JSValue obj){
    ArrayProxy_class AP = *(ArrayProxy_class *)JS_GetOpaque2(ctx, obj, js_ArrayProxy_class_id);
    *plen = AP.keys(ctx, AP.opaque, ptab);
    if(*plen<0)return -1;
    return true;
}

static JSClassExoticMethods js_ArrayProxy_exotic_methods = {
    //.get_own_property = js_proxy_get_own_property, //needed? see js_obj_to_desc
    .get_own_property_names = js_ArrayProxy_keys,
    .delete_property = js_ArrayProxy_delete_property,
    //.define_own_property = js_proxy_define_own_property,
    .has_property = js_ArrayProxy_has,
    .get_property = js_ArrayProxy_get,
    .set_property = js_ArrayProxy_set,
};

static const JSCFunctionListEntry js_ArrayProxy_proto_funcs[] = {
    JS_CGETSET_DEF("length", js_ArrayProxy_get_length, NULL ),
    //JS_CFUNC_DEF("at", 1, js_typed_array_at ),
    //JS_CFUNC_DEF("with", 2, js_typed_array_with ),
    //JS_CGETSET_DEF("buffer", js_typed_array_get_buffer, NULL ),
    //JS_CGETSET_DEF("byteLength", js_typed_array_get_byteLength, NULL ),
    //JS_CGETSET_DEF("byteOffset", js_typed_array_get_byteOffset, NULL ),
    //use exotic! JS_CFUNC_DEF("get", 1, js_ArrayProxy_get ),
    //use exotic! JS_CFUNC_DEF("set", 1, js_ArrayProxy_set ),
    JS_CFUNC_MAGIC_DEF("values", 0, js_create_ArrayProxy_iterator, JS_ITERATOR_KIND_VALUE ),
    JS_ALIAS_DEF("[Symbol.iterator]", "values" ),
    JS_CFUNC_MAGIC_DEF("keys", 0, js_create_ArrayProxy_iterator, JS_ITERATOR_KIND_KEY ),
    JS_CFUNC_MAGIC_DEF("entries", 0, js_create_ArrayProxy_iterator, JS_ITERATOR_KIND_KEY_AND_VALUE ),
    //JS_CFUNC_DEF("copyWithin", 2, js_typed_array_copyWithin ),
    //JS_CFUNC_MAGIC_DEF("every", 1, js_array_every, special_every | special_TA ),
    //JS_CFUNC_MAGIC_DEF("some", 1, js_array_every, special_some | special_TA ),
    //JS_CFUNC_MAGIC_DEF("forEach", 1, js_array_every, special_forEach | special_TA ),
    //JS_CFUNC_MAGIC_DEF("map", 1, js_array_every, special_map | special_TA ),
    //JS_CFUNC_MAGIC_DEF("filter", 1, js_array_every, special_filter | special_TA ),
    //JS_CFUNC_MAGIC_DEF("reduce", 1, js_array_reduce, special_reduce | special_TA ),
    //JS_CFUNC_MAGIC_DEF("reduceRight", 1, js_array_reduce, special_reduceRight | special_TA ),
    //JS_CFUNC_DEF("fill", 1, js_typed_array_fill ),
    //JS_CFUNC_MAGIC_DEF("find", 1, js_typed_array_find, ArrayFind ),
    //JS_CFUNC_MAGIC_DEF("findIndex", 1, js_typed_array_find, ArrayFindIndex ),
    //JS_CFUNC_MAGIC_DEF("findLast", 1, js_typed_array_find, ArrayFindLast ),
    //JS_CFUNC_MAGIC_DEF("findLastIndex", 1, js_typed_array_find, ArrayFindLastIndex ),
    //JS_CFUNC_DEF("reverse", 0, js_typed_array_reverse ),
    //JS_CFUNC_DEF("toReversed", 0, js_typed_array_toReversed ),
    //JS_CFUNC_DEF("slice", 2, js_typed_array_slice ),
    //JS_CFUNC_DEF("subarray", 2, js_typed_array_subarray ),
    //JS_CFUNC_DEF("sort", 1, js_typed_array_sort ),
    //JS_CFUNC_DEF("toSorted", 1, js_typed_array_toSorted ),
    //JS_CFUNC_MAGIC_DEF("join", 1, js_typed_array_join, 0 ),
    //JS_CFUNC_MAGIC_DEF("toLocaleString", 0, js_typed_array_join, 1 ),
    //JS_CFUNC_MAGIC_DEF("indexOf", 1, js_typed_array_indexOf, special_indexOf ),
    //JS_CFUNC_MAGIC_DEF("lastIndexOf", 1, js_typed_array_indexOf, special_lastIndexOf ),
    //JS_CFUNC_MAGIC_DEF("includes", 1, js_typed_array_indexOf, special_includes ),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]","js_ArrayProxy", JS_PROP_CONFIGURABLE),
};

static void js_declare_ArrayProxy_RT(JSRuntime * rt) {
    int ArrayProxy_class_id = 0;//classid must be 0 for allocation in rt
    JS_NewClassID(rt, &ArrayProxy_class_id);
    js_ArrayProxy_class_id = ArrayProxy_class_id;//After compilation this shall be unchanging
    JSClassDef js_ArrayProxy_def = {
        .class_name = "ArrayProxy",
        .finalizer = js_ArrayProxy_finalizer,
        .exotic = &js_ArrayProxy_exotic_methods
    };
    JS_NewClass(rt, js_ArrayProxy_class_id, &js_ArrayProxy_def);
}

static void js_declare_ArrayProxy(JSContext * ctx) {
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_ArrayProxy_proto_funcs, countof(js_ArrayProxy_proto_funcs));
    JS_SetClassProto(ctx, js_ArrayProxy_class_id, proto);
}


static JSValue js_NewArrayProxy(JSContext * ctx,ArrayProxy_class AP){
    ArrayProxy_class * ptr__return = (ArrayProxy_class*)js_malloc(ctx, sizeof(ArrayProxy_class));
    *ptr__return = AP;
    JSValue _return = JS_NewObjectClass(ctx, js_ArrayProxy_class_id);
    JS_PreventExtensions(ctx, _return);
    JS_SetOpaque(_return, ptr__return);
    JS_DupValue(ctx,AP.anchor);
    return _return;
}

static int64_t js_IsArrayLength(JSContext * ctx, JSValueConst obj, int64_t len){
    if(!JS_IsArray(obj))return false;
    int64_t ret;
    JS_GetLength(ctx,obj, &ret);
    if(ret<0)return false;
    return ret==len;
}
/*
Target will be just parent, and handle is called:

s = get_proxy_method(ctx, &method, obj /*the_proxy_itself/, JS_ATOM_get);
//JS_GetProperty(ctx, s->handler, name)
//So, handler is object with setProperty: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Proxy
//We use: JS_ATOM_get, JS_ATOM_set found using JS_NewAtom
args[0] = s->target;
args[1] = atom_val;
args[2] = receiver;
//When called, proxy handler has access to self, so, obj handler can store additional data using setProperty
ret = JS_CallFree(ctx, method, s->handler, 3, args);

*/