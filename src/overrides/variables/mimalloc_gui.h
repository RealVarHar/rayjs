// Add mimalloc
#ifndef RAYGUI_MALLOC
    #include <mimalloc.h>
    #define RAYGUI_MALLOC(sz)       mi_malloc(sz)
    #define RAYGUI_CALLOC(n,sz)     mi_calloc(n,sz)
    #define RAYGUI_REALLOC(ptr,sz)  mi_realloc(ptr,sz)
    #define RAYGUI_FREE(ptr)        mi_free(ptr)
#endif