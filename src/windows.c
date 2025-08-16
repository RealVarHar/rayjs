/**
 * This file is a part of cutils.h that is separated to avoid name mangling with other project files
 */
#if defined(__APPLE__)
#include <malloc/malloc.h>
#elif defined(__linux__) || defined(__ANDROID__) || defined(__CYGWIN__)
#include <malloc.h>
#elif defined(__FreeBSD__)
#include <malloc_np.h>
#elif defined(_WIN32)
#include <windows.h>
#endif
