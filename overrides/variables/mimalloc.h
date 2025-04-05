// Add mimalloc
#ifndef RL_MALLOC
    #include <mimalloc.h>
    #define RL_MALLOC(sz)       mi_malloc(sz)
    #define RL_CALLOC(n,sz)     mi_calloc(n,sz)
    #define RL_REALLOC(ptr,sz)  mi_realloc(ptr,sz)
    #define RL_FREE(ptr)        mi_free(ptr)
#endif