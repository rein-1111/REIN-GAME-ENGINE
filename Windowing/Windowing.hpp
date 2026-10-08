#include <GLFW/glfw3.h>
#include <string>

struct Window
{
    GLFWwindow *handle;
    int width;
    int height;
    std::string title;
};
struct OpenGlProfile
{
    int version_major;
    int version_minor;
};
class Windowing
{
private:
public:
    static void Init();
    static void SetOpenGlProfile(OpenGlProfile &profile);
    static bool CreateWindow(Window &window);
    static void DestroyWindow(Window &window);
    static void SetContext(Window &window);
    static bool WindowActive(Window &window);
    static void SwapBuffers(Window &window);
    static void PollEvent();

    static void Quit();
};