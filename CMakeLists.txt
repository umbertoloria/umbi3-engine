cmake_minimum_required(VERSION 3.12)
project(OTEngine)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(dependencies/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(dependencies/glfw-3.3)

add_subdirectory(engine)
add_subdirectory(platform)
add_subdirectory(renderer)

add_executable(OTEngine
		main.cpp MyLayer.h
		dependencies/src/glad.c
		${ENGINE_SOURCES}
		${PLATFORM_SOURCES}
		${RENDERER_SOURCES})

target_link_libraries(OTEngine glfw)
