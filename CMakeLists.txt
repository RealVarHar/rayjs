cmake_minimum_required(VERSION 3.1)
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

include(CheckCCompilerFlag)
include(GNUInstallDirs)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD 11)

message("=== Configure raylib ===")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib EXCLUDE_FROM_ALL)

message("=== Configure QuickJS ===")
# add quickjs
set(quickjs_version 2024-09-28)
set(quickjs_sources_root ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/quickjs)
set(quickjs_sources
	${quickjs_sources_root}/quickjs.h
	${quickjs_sources_root}/quickjs-libc.h
	${quickjs_sources_root}/quickjs.c
	${quickjs_sources_root}/libregexp.c
	${quickjs_sources_root}/libunicode.c
	${quickjs_sources_root}/libbf.c
	${quickjs_sources_root}/cutils.c
	${quickjs_sources_root}/quickjs-libc.c
)
add_library(quickjs STATIC
	${quickjs_sources}
)
target_compile_definitions(quickjs
	PRIVATE
		CONFIG_VERSION="${quickjs_version}"
)
target_include_directories(quickjs PRIVATE ${quickjs_sources_root})

add_library(lightmapper INTERFACE)
target_include_directories(lightmapper INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lightmapper)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB files src/*.c)
#add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE ${files})
add_executable(${CMAKE_PROJECT_NAME} ${files})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${quickjs_sources_root})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE thirdparty/raygui/src)
target_link_libraries(${CMAKE_PROJECT_NAME} quickjs raylib lightmapper)
