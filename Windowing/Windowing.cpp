#include <iostream>
#include "Windowing.hpp"

void Windowing::Init()
{
    if (!glfwInit())
    {
        std::cout << "WINDOWING::INIT::FAILED" << std::endl;
    };
}
void Windowing::SetOpenGlProfile(OpenGlProfile &profile)
{
    glfwWindowHint(GLFW_VERSION_MAJOR, profile.version_major);
    glfwWindowHint(GLFW_VERSION_MINOR, profile.version_minor);
    glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
bool Windowing::CreateWindow(Window &window)
{
    window.handle = glfwCreateWindow(window.width, window.height, window.title.c_str(), nullptr, nullptr);

    if (!window.handle)
    {
        std::cout << "WINDOWING::CREATEWINDOW::FAILED" << std::endl;
        return false;
    }
    return true;
}
void Windowing::DestroyWindow(Window &window)
{
    glfwDestroyWindow(window.handle);
}

void Windowing::SetContext(Window &window)
{
    glfwMakeContextCurrent(window.handle);
}
bool Windowing::WindowActive(Window &window)
{
    return !glfwWindowShouldClose(window.handle);
}
void Windowing::SwapBuffers(Window &window)
{
    glfwSwapBuffers(window.handle);
}
void Windowing::PollEvent()
{
    glfwPollEvents();
}

void Windowing::Quit()
{
    glfwTerminate();
}