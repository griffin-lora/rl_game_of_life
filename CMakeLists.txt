cmake_minimum_required(VERSION 3.31)
project(GOL LANGUAGES C CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/build/conan_toolchain.cmake)
set(CMAKE_BUILD_TYPE Release)

find_package(raylib REQUIRED)

file(GLOB SRC CONFIGURE_DEPENDS "src/*.c")
add_executable(app ${SRC})
target_compile_options(app PRIVATE -O2 -std=c2x -Wall -Wextra -Wpedantic -Wconversion -Wno-override-init -Wno-pointer-arith -Wno-newline-eof -Wno-nullability-extension -Werror -Wfatal-errors)
target_compile_definitions(app PRIVATE GLFW_INCLUDE_VULKAN CGLM_FORCE_DEPTH_ZERO_TO_ONE)
target_include_directories(app PRIVATE "src")
target_link_libraries(app PRIVATE raylib)