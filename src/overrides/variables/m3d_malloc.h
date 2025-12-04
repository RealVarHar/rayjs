#ifndef M3D_MALLOC
# define M3D_MALLOC(sz)     mi_malloc(sz)
#endif
#ifndef M3D_REALLOC
# define M3D_REALLOC(p,nsz) mi_realloc(p,nsz)
#endif
#ifndef M3D_FREE
# define M3D_FREE(p)        mi_free(p)
#endif