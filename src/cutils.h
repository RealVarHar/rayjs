typedef int BOOL;

#ifndef FALSE
enum {
    FALSE = 0,
    TRUE = 1,
};
#endif

int has_suffix(const char *str, const char *suffix);
static inline size_t js__malloc_usable_size(const void *ptr)
{
#if defined(__APPLE__)
    return malloc_size(ptr);
#elif defined(_WIN32)
    return _msize((void *)ptr);
#elif defined(__linux__) || defined(__ANDROID__) || defined(__CYGWIN__) || defined(__FreeBSD__)
    return malloc_usable_size((void *)ptr);
#else
    return 0;
#endif
}