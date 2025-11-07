cmake_minimum_required(VERSION 3.31)
project(GOL LANGUAGES C CXX)
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(OPENGL_INCLUDE_DIR )

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
)
FetchContent_MakeAvailable(raylib)

file(GLOB SRC CONFIGURE_DEPENDS "src/*.c")
add_executable(app ${SRC})
target_compile_options(app PRIVATE -O2 -std=c2x -Wall -Wextra -Wpedantic -Wconversion -Wno-override-init -Wno-pointer-arith -Wno-newline-eof -Wno-nullability-extension -Werror -Wfatal-errors)
target_compile_definitions(app PRIVATE GLFW_INCLUDE_VULKAN CGLM_FORCE_DEPTH_ZERO_TO_ONE)
target_include_directories(app PRIVATE "src")
target_link_libraries(app PRIVATE raylib)