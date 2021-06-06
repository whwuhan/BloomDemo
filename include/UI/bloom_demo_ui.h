#pragma once
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

class BloomDemoUI
{
public:
    static GLFWwindow* glfw_window;                // glfw window
    static void init(GLFWwindow* glfw_window);      // 初始化，在渲染循环外
    static void render_demo_ui();                   // 渲染imgui demo
    static void render();                           // 渲染所有的UI
    static void destroy();                          // 清空数据

private:
    static float font_size;//字体大小
    static float global_scale;//整体的字体缩放
    static float window_rounding;//窗口的圆角
    static float frame_rounding;//内部图标的圆角

    static bool show_usage;//显示操作手册
    static bool show_right_sidebar;//显示右边Sidebar
    static bool show_message_box;//信息窗口
    static int style;//UI风格
};