#ifndef STBTT_malloc
#include <mimalloc.h>
#define STBTT_malloc(x,u)  ((void)(u),mi_malloc(x))
#define STBTT_free(x,u)    ((void)(u),mi_free(x))
#endif