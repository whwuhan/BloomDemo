#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

class BloomDemoUI
{
public:
    static  GLFWwindow* glfw_window;                // glfw window
    static void init(GLFWwindow* glfw_window);      // 初始化，在渲染循环外
    static void render_demo_ui();                   // 渲染imgui demo
    static void render();                           // 渲染所有的UI
    static void destroy();                          // 清空数据
};