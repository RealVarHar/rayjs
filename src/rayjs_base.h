#include <quickjs.h>

#ifndef BASETOOLS_IMPLEMENTATION
#define BASETOOLS_IMPLEMENTATION
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
} trampolineContext;
#include "rayjs_generated.c"
#endif

#include <string.h>
#include <stdarg.h>
#include "modules/quickjs-libc.h"

extern JSModuleDef * js_init_module_js_raylib(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_js_raymath(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_js_rcamera(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_js_raygui(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_js_rlights(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_js_reasings(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_js_rlgl(JSContext * ctx, const char * module_name);
extern JSModuleDef * js_init_module_js_rlightmapper(JSContext * ctx, const char * module_name);
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

/* also used to initialize the worker context */
static JSContext *JS_NewCustomContext(JSRuntime *rt);
static JSValue copyFunction(JSContext *from_ctx, JSContext *to_ctx, JSValue fn);
static memoryNode* memoryStore(memoryNode *current, void * clarfunc, void * memoryptr);
static void memoryClear(JSContext * ctx, memoryNode *head);
static void JS_FreeValuePtr(JSContext *ctx, JSValue * v);
static char * asnprintf(JSContext * ctx, char * buffer, size_t * maxsize, const char * format, ...);