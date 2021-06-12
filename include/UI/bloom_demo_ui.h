#pragma once
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <window.h>
#include <components/scene.h>
#include <geometry/sphere.h>

class BloomDemoUI
{
public:
    static GLFWwindow* glfw_window;                 // glfw window
    static void init(GLFWwindow* glfw_window);      // 初始化，在渲染循环外
    static void render_demo_ui();                   // 渲染imgui demo
    static void render();                           // 渲染所有的UI
    static void render_message_box();               // 渲染信息框
    static void render_right_sidebar();             // 渲染右侧框
    static void destroy();                          // 清空数据

private:
    static float font_size;                         // 字体大小
    static float global_scale;                      // 整体的字体缩放
    static float window_rounding;                   // 窗口的圆角
    static float frame_rounding;                    // 内部图标的圆角

    static bool show_usage;                         // 显示操作手册
    static bool show_right_sidebar;                 // 显示右边Sidebar
    static bool show_message_box;                   // 信息窗口
    static int style;                               // UI风格

    static float message_box_pos_x;                 // messagebox的x轴
    static float message_box_pos_y;                 // messagebox的y轴
    static float right_sidebar_pos_x;               // 右侧边栏位置的X坐标(距离右侧的距离) 
    static float right_sidebar_pos_y;               // 右侧边栏位置的Y坐标
    static float right_sidebar_width;               // 右侧边栏宽
    static float right_sidebar_height;              // 右侧边栏高
};