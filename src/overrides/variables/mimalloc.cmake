# Add mimalloc
message("=== Configure mimalloc ===")
	set(MI_BUILD_OBJECT OFF CACHE BOOL "Build object library" FORCE)
	set(MI_BUILD_TESTS OFF CACHE BOOL "Build test executables" FORCE)
	set(MI_BUILD_SHARED OFF CACHE BOOL "Build test executables" FORCE)
	#set(MI_SECURE ON CACHE BOOL "Use full security mitigations" FORCE)
	set(MI_WIN_REDIRECT OFF CACHE BOOL "Use redirection module ('mimalloc-redirect') on Windows if compiling mimalloc as a DLL" FORCE)
	add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/mimalloc mimalloc-static EXCLUDE_FROM_ALL)
set(LIBS_PRIVATE mimalloc-static ${LIBS_PRIVATE})