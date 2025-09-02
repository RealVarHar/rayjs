#include <quickjs.h>

#ifndef BASETOOLS_IMPLEMENTATION
#define BASETOOLS_IMPLEMENTATION

//define atoms to init properties without atom search
enum {
    __JS_ATOM_NULL = JS_ATOM_NULL,
#define DEF(name, str) JS_ATOM_ ## name,
#include "quickjs-atom.h"
#undef DEF
    JS_ATOM_END,
};

//define an allocation linked list
typedef struct memoryNode{
    int length;
    void * pointers[6];
    struct memoryNode * next;
} memoryNode;
//Define a struct to store in a trampoline
typedef struct trampolineContext {
    JSContext * ctx;
    JSValue func_obj;
    JSValue thread_id;
} trampolineContext;

static JSClassID js_ArrayProxy_class_id;
typedef int (*ArrayProxy_has)(JSContext *,void *,int,bool);// (ctx,opaque,set_to,property,as_sting?)
typedef JSValue (*ArrayProxy_get)(JSContext *,void *,int,bool);// (ctx,opaque,property,is_sting?)
typedef int (*ArrayProxy_set)(JSContext *,void *,JSValue,int,bool);// (ctx,opaque,set_to,property,as_sting?)
typedef int (*ArrayProxy_keys)(JSContext *,void *,JSPropertyEnum **);// (ctx,opaque,set_to,&(* JSPropertyEnum))
typedef struct ArrayProxy_class {
    JSValue anchor;//js_value to attach lifetime to
    void * opaque;//Pointer to custom data
    ArrayProxy_get values;//converting opaque to js_array (ctx,opaque,0,to_string?)
    ArrayProxy_keys keys;//(cnt,opaque,&(* JSPropertyEnum))=>length,&(* JSPropertyEnum)
    ArrayProxy_get get;//get property (ctx,opaque,0..n or atom,using_atom?)
    ArrayProxy_set set;//set property (ctx,opaque,set_to,0..n or atom,using_atom?)
    ArrayProxy_has has;//property (ctx,opaque,NULL,0..n or atom,using_atom?)
} ArrayProxy_class;


#include "rayjs_generated.c"
#endif

#include <string.h>
#include <stdarg.h>
#include "modules/quickjs-libc.h"

extern JSModuleDef * js_init_module_raylib(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_raymath(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_rcamera(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_raygui(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_rlights(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_reasings(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_rlgl(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_rlightmapper(JSContext * ctx, const char * module_name);
static JSCFunctionListEntry argv0;

#ifndef countof
#define countof(x) (sizeof(x) / sizeof((x)[0]))
#endif

static int qjs__argc;
static char **qjs__argv;
static int default_dump;

static JSValue js_navigator_get_userAgent(JSContext *ctx, JSValue this_val);

static const JSCFunctionListEntry navigator_proto_funcs[];

static JSValue js_gc(JSContext *ctx, JSValue this_val,int argc, JSValue *argv);

static const JSCFunctionListEntry global_obj[];

#ifdef QJS_USE_MIMALLOC
static void * jsc_malloc(JSContext *ctx, size_t sz );
static void * jsc_calloc(JSContext *ctx, size_t n, size_t sz );
static void * jsc_realloc(JSContext *ctx, void * ptr, size_t sz );
static void jsc_free(JSContext *ctx, void * ptr );
#ifndef RL_MALLOC
#define RL_MALLOC(sz)       mi_malloc(sz)
#define RL_CALLOC(n,sz)     mi_calloc(n,sz)
#define RL_REALLOC(ptr,sz)  mi_recalloc(ptr,sz)
#define RL_FREE(ptr)        mi_free(ptr)
#endif
#else
static void * jsc_malloc(JSContext *ctx, size_t sz );
static void * jsc_calloc(JSContext *ctx, size_t n, size_t sz );
static void * jsc_realloc(JSContext *ctx, void * ptr, size_t sz );
static void jsc_free(JSContext *ctx, void * ptr );
#ifndef RL_MALLOC
#define RL_MALLOC(sz)       malloc(sz)
#define RL_CALLOC(n,sz)     calloc(n,sz)
#define RL_REALLOC(ptr,sz)  recalloc(ptr,sz)
#define RL_FREE(ptr)        free(ptr)
#endif
#endif

static int app_update_quickjs(JSContext *ctx);

/* also used to initialize the worker context */
static JSContext *JS_NewCustomContext(JSRuntime *rt);
static JSValue copyFunction(JSContext *from_ctx, JSContext *to_ctx, JSValue fn);
static memoryNode* memoryStore(memoryNode *current, void * clarfunc, void * memoryptr);
static void memoryClear(JSContext * ctx, memoryNode *head);
static void JS_FreeValuePtr(JSContext *ctx, JSValue * v);
static char * asnprintf(JSContext * ctx, char * buffer, size_t * maxsize, const char * format, int skip_args, ...);
static JSValue js_NewArrayProxy(JSContext * ctx,ArrayProxy_class AP);