cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0063 NEW)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "" FORCE)

# Workaround for windows to prevent static linking of pthread
IF (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
ENDIF()
if (UNIX)
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC -DCONFIG_BIGNUM")
	set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fPIC -DCONFIG_BIGNUM")
endif (UNIX)

project(rayjs LANGUAGES C)
#Inherit some compiler flags
include(CheckCCompilerFlag)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD 11)
macro(xcheck_add_c_compiler_flag FLAG)
    string(REPLACE "-" "" FLAG_NO_HYPHEN ${FLAG})
    check_c_compiler_flag(${FLAG} COMPILER_SUPPORTS_${FLAG_NO_HYPHEN})
    if(COMPILER_SUPPORTS_${FLAG_NO_HYPHEN})
        add_compile_options(${FLAG})
    endif()
endmacro()

xcheck_add_c_compiler_flag(-Wno-implicit-fallthrough)
xcheck_add_c_compiler_flag(-Wno-sign-compare)
xcheck_add_c_compiler_flag(-Wno-missing-field-initializers)
xcheck_add_c_compiler_flag(-Wno-unused-parameter)
xcheck_add_c_compiler_flag(-Wno-unused-but-set-variable)
xcheck_add_c_compiler_flag(-Wno-array-bounds)
xcheck_add_c_compiler_flag(-Wno-format-truncation)
xcheck_add_c_compiler_flag(-funsigned-char)
#Inherit some compiler flags

include(CheckCCompilerFlag)
include(GNUInstallDirs)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD 11)

option(RAYJS_USE_MIMALLOC "Use mimalloc as the memory allocator" OFF)
#if(RAYJS_USE_MIMALLOC)
#	message("=== Configure mimalloc ===")
#	set(MI_BUILD_OBJECT OFF CACHE BOOL "Build object library" FORCE)
#	set(MI_BUILD_TESTS OFF CACHE BOOL "Build test executables" FORCE)
#	set(MI_BUILD_SHARED OFF CACHE BOOL "Build test executables" FORCE)
#	#set(MI_SECURE ON CACHE BOOL "Use full security mitigations" FORCE)
#	set(MI_WIN_REDIRECT OFF CACHE BOOL "Use redirection module ('mimalloc-redirect') on Windows if compiling mimalloc as a DLL" FORCE)
#	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/mimalloc EXCLUDE_FROM_ALL)
#endif()

message("=== Configure QuickJS ===")
# add quickjs
set(quickjs_version 2024-09-28)
set(quickjs_sources_root ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/quickjs)
set(quickjs_sources
	${quickjs_sources_root}/quickjs.h
	${quickjs_sources_root}/quickjs-atom.h
	${quickjs_sources_root}/quickjs.c
	${quickjs_sources_root}/libregexp.c
	${quickjs_sources_root}/libunicode.c
	${quickjs_sources_root}/xsum.c
	${quickjs_sources_root}/cutils.c
	${quickjs_sources_root}/cutils.h
	${quickjs_sources_root}/gen/repl.c
	${quickjs_sources_root}/gen/standalone.c
)
add_library(quickjs STATIC
	${quickjs_sources}
)
target_compile_definitions(quickjs PRIVATE CONFIG_VERSION=${quickjs_version} )
if(RAYJS_USE_MIMALLOC)
	target_compile_definitions(quickjs PUBLIC QJS_USE_MIMALLOC )
	file(READ "${CMAKE_CURRENT_SOURCE_DIR}/src/overrides/variables/mimalloc.cmake" mimalloc.cmake)
	file(READ "${CMAKE_CURRENT_SOURCE_DIR}/src/overrides/variables/mimalloc.h" mimalloc.h)
	file(READ "${CMAKE_CURRENT_SOURCE_DIR}/src/overrides/variables/stb_mimalloc.h" stb_mimalloc.h)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/overrides/raylib/src/CMakeLists.txt ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/src/CMakeLists.txt @ONLY)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/overrides/raylib/src/raylib.h ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/src/raylib.h @ONLY)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/overrides/raylib/src/stb_truetype.h ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/src/external/stb_truetype.h @ONLY)
endif()
target_include_directories(quickjs PRIVATE ${quickjs_sources_root})
target_link_libraries(quickjs)


add_library(lightmapper INTERFACE)
target_include_directories(lightmapper INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lightmapper)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


message("=== Configure raylib ===")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib EXCLUDE_FROM_ALL)
#target_link_libraries(raylib PUBLIC mimalloc)

add_library(expose_system STATIC src/windows.c)

message("=== Bind files together ===")
file(GLOB files src/*.c)
add_executable(${CMAKE_PROJECT_NAME} ${files})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/examples/shaders)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/examples/others)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/src/external)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raygui/src)
set_target_properties(${CMAKE_PROJECT_NAME}
    PROPERTIES
    COMPILE_DEFINITIONS GRAPHICS_API_OPENGL_33=1
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${quickjs_sources_root})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src)

set(RAYJS_LINK_LIBRARIES "quickjs" "expose_system")
if(RAYJS_USE_MIMALLOC)
	set(RAYJS_LINK_LIBRARIES "${RAYJS_LINK_LIBRARIES}" "mimalloc-static")
endif()
set(RAYJS_LINK_LIBRARIES "${RAYJS_LINK_LIBRARIES}" "raylib" "lightmapper")
target_link_libraries(${CMAKE_PROJECT_NAME} ${RAYJS_LINK_LIBRARIES})