cmake_minimum_required(VERSION 3.10.0)
project(RGE VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD  20)
set(CMAKE_CXX_STANDARD_REQUIRED  true)

add_executable(RGE 
${CMAKE_SOURCE_DIR}/Deps/GLAD/src/glad.c
Main.cpp
Windowing/Windowing.cpp
Windowing/Windowing.hpp
Renderer/IRenderer.hpp
Renderer/Backend/OpenGlRenderer.hpp
Renderer/Backend/wrapper/OpenGl.hpp
Renderer/Renderer.hpp
)

target_compile_definitions(RGE PRIVATE
DEBUG_OPENGLBACKEND
)

target_include_directories(RGE PRIVATE
${CMAKE_SOURCE_DIR}/Deps/GLAD/include
${CMAKE_SOURCE_DIR}/Deps/GLFW/include/
${CMAKE_SOURCE_DIR}Deps/GLM/
${CMAKE_SOURCE_DIR}/Debug/
)

target_link_directories(RGE PRIVATE
${CMAKE_SOURCE_DIR}/Deps/GLFW/lib-vc2026/
)

target_link_libraries(RGE PRIVATE
glfw3
)