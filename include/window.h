#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utils/camera.h>
#include <utils/render.h>
#include <utils/shader.h>
#include <geometry/sphere.h>
#include <components/scene.h>
// 两种操作模式FPS风格和WOW风格
enum OPERATE_MODE 
{
    WOW,
    FPS
};
class Window
{
public:
    // Window();                                    // 默认构造函数
    static GLFWwindow *glfw_window;                 // glfw window
    // 窗口大小
    static unsigned int width;                      // window 宽
    static unsigned int height;                     // window 高
    // 相机相关
    static Camera camera;                           // 相机
    static float camera_speed_scale;                // 相机移速比例
    // 渲染相关
    static bool use_MSAA;                           // 是否使用MSAA抗锯齿
    static int MSAA_level;                          // 抗锯齿级别
    // 镜头操作模式
    static OPERATE_MODE operate_mode;
    // timing
    static float delta_time;
    static float last_frame;

    // 防止镜头闪烁
    static bool first_change_to_FPS_mode;           // 第一次切换到FPS操作模式
    static bool first_change_to_WOW_mode;           // 第一次切换到WOW操作模式
    static double cursor_pos_x;                     // 鼠标位置X
    static double cursor_pos_y;                     // 鼠标位置Y
    static bool change_operate_mode_key_pressed;    // 更换操作模式按键是否被按下
    static bool mouse_button_right_first_rlease;    // 鼠标右键是否第一次松开
    static bool mouse_button_right_first_pressed;   // 鼠标右键是否第一次按下

    // 静态方法
    static void init_and_run();                     // 初始化glfw glad并运行窗口(包含渲染循环)
};

// 回调函数声明，更改窗口大小的时候，更改视口大小
void framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height);
// 键盘操作
void process_input(GLFWwindow *glfw_window);
void change_operate_mode(GLFWwindow *glfw_window);                                      // 修改操作模式
// 鼠标滚轮操作
void scroll_callback(GLFWwindow *glfw_window, double xoffset, double yoffset);
// 鼠标点击回调函数
void mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods);
// 鼠标移动
void FPS_mode_mouse_callback(GLFWwindow* glfw_window, double xpos, double ypos);        // 移动模式下的鼠标移动回调函数 类似FPS游戏
void WOW_mode_mouse_callback(GLFWwindow* glfw_window, double xpos, double ypos);        // 鼠标模式下的鼠标移动回调函数 类似WOW
// 获取鼠标位置
void get_cursor_pos(GLFWwindow* glfw_window, double xpos, double ypos);