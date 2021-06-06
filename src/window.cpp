#include <iostream>
#include <window.h>
using namespace std;
using namespace glm;

//static变量初始化
GLFWwindow *Window::glfw_window = nullptr;              // glfw window
//窗口大小
unsigned int Window::width = 1200;
unsigned int Window::height = 800;
//相机相关
Camera Window::camera(vec3(0.0f,0.0f,1.0f));            // 相机
float Window::camera_speed_scale = 1.0f;                // 相机移速比例
//渲染相关
bool Window::use_MSAA = true;
int Window::MSAA_level = 8;                             // MSAA采样数量
//镜头操作模式
OPERATE_MODE Window::operate_mode = WOW;                // 默认为WOW的操作模式
//timing
float Window::delta_time = 0.0f;
float Window::last_frame = 0.0f;
//防止模式切换镜头闪烁
bool Window::first_change_to_FPS_mode = true;           // 第一次切换到FPS操作模式
bool Window::first_change_to_WOW_mode = true;           // 第一次切换到WOW操作模式
bool Window::change_operate_mode_key_pressed = false;   // 更换操作模式按键是否被按下
bool Window::mouse_button_right_first_pressed = true;   // 鼠标右键是否第一次被按下
bool Window::mouse_button_right_first_rlease = true;    // 鼠标右键是否是第一次被松开
double Window::cursor_pos_x = Window::width / 2.0f;     // 鼠标位置X
double Window::cursor_pos_y = Window::height / 2.0f;    // 鼠标位置Y

void Window::init_and_run()
{
    //======================glfw glad opengl 初始化======================
    glfwInit(); //初始化GLFW

    //通过glfwWindowHint()函数来设置参数，前面是参数名称，后面是值
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                      //设置主版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                      //设置次版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      //设置使用核心模式
    glfwWindowHint(GLFW_SAMPLES, Window::MSAA_level);                   //MSAA采样数
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //mac用户需要设置，初始化才能有效
#endif
    //创建一个窗口对象
    string window_title = "Bloom Demo";
    //参数依次是长，宽，名称，后两个参数忽略
    Window::glfw_window = glfwCreateWindow(Window::width, Window::height, window_title.c_str(), NULL, NULL);
    
    if (Window::glfw_window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return;
    }
    //将窗口的上下文设置成主线程的上下文
    glfwMakeContextCurrent(Window::glfw_window);
    glfwSwapInterval(1); // Enable vsync 每帧的交换间隔，防止屏幕撕裂
    //注册回调函数，告诉GLFW窗口大小调整时，调用这个回调函数
    glfwSetFramebufferSizeCallback(Window::glfw_window, framebuffer_size_callback);
    //鼠标滚轮监听
    glfwSetScrollCallback(Window::glfw_window, scroll_callback);
    //鼠标点击回调函数
    glfwSetMouseButtonCallback(Window::glfw_window, mouse_button_callback);
    //鼠标移动回调函数 默认模式是WOW风格
    glfwSetCursorPosCallback(Window::glfw_window, nullptr);
    //告诉GLFW选中窗口不显示鼠标
    //glfwSetInputMode(Window::glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //GLAD是用来管理OpenGL的函数指针
    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        //glfwGetProcAddress 根据编译的系统给出了正确的函数
        cout << "Failed to initialize GLAD" << endl;
        return;
    }

    //openGL全局配置
    glEnable(GL_DEPTH_TEST);         // 开启深度测试
    glEnable(GL_MULTISAMPLE);        // 开启MSAA通常都是默认开启的
    glEnable(GL_PROGRAM_POINT_SIZE); // 开启改变点的大小（暂时无用）
    // glPoint_size(25);
    //======================glfw glad opengl 初始化结束======================

    // UI初始化
    BloomDemoUI::init(Window::glfw_window);

    // shader
    Shader sphere_shader
    (
        "shaders/sphere.vs.glsl",
        "shaders/sphere.fs.glsl"
    );
    // end shader


    // test
    // 发光球体渲染
    Sphere sphere;
    sphere.create_sphere();
    Scene::add_sphere("test", sphere);
    // end test

    
    // 渲染循环
    while (!glfwWindowShouldClose(Window::glfw_window))
    {
        // 保证不同帧数下移动速度一致
        float current_frame = glfwGetTime();
        Window::delta_time = current_frame - Window::last_frame;
        Window::last_frame = current_frame;

        // 键盘鼠标事件监听
        process_input(Window::glfw_window);
        
        // 背景颜色
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // 获取投影矩阵和相机矩阵
        mat4 projection = perspective(radians(camera.Zoom), (float)Window::width / (float)Window::height, 0.1f, 100.0f);
        mat4 view = camera.GetViewMatrix();

        // 激活着色器程序
        sphere_shader.use();

        // MVP变换
        sphere_shader.setMat4("projection", projection);
        sphere_shader.setMat4("view", view);
        sphere_shader.setMat4("model", sphere.model);
        sphere_shader.setVec4("color", sphere.color);
        // ==========================场景渲染==========================

        // 渲染所有的球体光源
        for(auto it = Scene::spheres.begin(); it != Scene::spheres.end(); it++)
        {
            Render::render_sphere(it->second);
        }

        // ==========================场景渲染结束=======================

        BloomDemoUI::render_demo_ui();

        // 交换buffer
        glfwSwapBuffers(Window::glfw_window);
        glfwPollEvents();
    }
}// end Window::init_and_run()

// 回调函数
//回调函数声明，更改窗口大小的时候，更改视口大小
void framebuffer_size_callback(GLFWwindow *glfw_window, int width, int height)
{
    Window::width = width;
    Window::height = height;
    glViewport(0, 0, width, height);
}

// 声明输入函数，判断是否按下键盘
void process_input(GLFWwindow *glfw_window)
{
    //退出
    if (glfwGetKey(glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfw_window, true);

    //按Q切换操作模式
    if 
    (
        glfwGetKey(glfw_window, GLFW_KEY_Q) == GLFW_PRESS && 
        !Window::change_operate_mode_key_pressed && 
        glfwGetMouseButton(glfw_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE
    )
    {
        Window::change_operate_mode_key_pressed = true;
        change_operate_mode(Window::glfw_window);
    }
    if (glfwGetKey(glfw_window, GLFW_KEY_Q) == GLFW_RELEASE)
    {
        Window::change_operate_mode_key_pressed = false;
    }

    //键盘监听
    //相机移动
    //向前
    if (glfwGetKey(glfw_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(FORWARD, Window::delta_time * Window::camera_speed_scale);
    }
    //向后
    if (glfwGetKey(glfw_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(BACKWARD, Window::delta_time * Window::camera_speed_scale);
    }
    //向左
    if (glfwGetKey(glfw_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(LEFT, Window::delta_time * Window::camera_speed_scale);
    }
    //向右
    if (glfwGetKey(glfw_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Window::camera.ProcessKeyboard(RIGHT, Window::delta_time * Window::camera_speed_scale);
    }
    //向上
    if (glfwGetKey(glfw_window, GLFW_KEY_SPACE))
    {
        Window::camera.ProcessKeyboard(UPWARD, Window::delta_time * Window::camera_speed_scale);
    }
}

//修改操作模式
void change_operate_mode(GLFWwindow *glfw_window)
{
    switch(Window::operate_mode)
    {
    //注意设置的顺序
    case WOW:
        //切换为FPS风格
        Window::first_change_to_FPS_mode = true;
        Window::operate_mode = FPS;
        glfwSetMouseButtonCallback(glfw_window, nullptr);                //禁用鼠标按键监听
        glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏鼠标
        glfwSetCursorPosCallback(glfw_window, FPS_mode_mouse_callback);     //设置鼠标的移动模式为FPS mode
        break;
    case FPS:
        //切换为WOW风格
        Window::first_change_to_WOW_mode = true;
        Window::operate_mode = WOW;
        glfwSetMouseButtonCallback(glfw_window, mouse_button_callback);    //启动鼠标按键监听
        glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  //显示鼠标
        glfwSetCursorPosCallback(glfw_window, WOW_mode_mouse_callback);     //设置鼠标的移动模式为WOW mode
        break;
    default:
        cerr << "Wrong operate mode!" << endl;
        exit(0);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *winglfwWindowdow, double xoffset, double yoffset)
{
    Window::camera.ProcessMouseScroll(yoffset);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
//移动模式下的鼠标移动回调函数 类似FPS游戏
void FPS_mode_mouse_callback(GLFWwindow *glfw_window, double xpos, double ypos)
{   
    //防止镜头抖动
    if (Window::first_change_to_FPS_mode)
    {
        Window::cursor_pos_x = xpos;
        Window::cursor_pos_y = ypos;
        Window::first_change_to_FPS_mode = false;
    }

    float xoffset = xpos - Window::cursor_pos_x;
    float yoffset = Window::cursor_pos_y - ypos; // reversed since y-coordinates go from bottom to top

    Window::cursor_pos_x = xpos;
    Window::cursor_pos_y = ypos;

    Window::camera.ProcessMouseMovement(xoffset, yoffset);
}

//鼠标点击回调函数
void mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods)
{
    //===============WOW操作风格下的鼠标按键监听===============
    //监听鼠标右键按下
    if (action == GLFW_PRESS && Window::operate_mode == WOW)
    {
        switch(button)
        {
        case GLFW_MOUSE_BUTTON_RIGHT:
            if(Window::mouse_button_right_first_pressed){
                glfwSetCursorPosCallback(glfw_window, nullptr);                  //先禁用鼠标移动监听
                Window::mouse_button_right_first_pressed = false;
                Window::mouse_button_right_first_rlease = true;
                Window::first_change_to_WOW_mode = true;
                glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏鼠标
                glfwSetCursorPosCallback(glfw_window, WOW_mode_mouse_callback);     //设置为WOW操作模式
            }
            break;
        }
    }
    //监听鼠标右键释放
    if(action == GLFW_RELEASE && Window::operate_mode == WOW)
    {
        switch(button)
        {
        case GLFW_MOUSE_BUTTON_RIGHT:
            if(Window::mouse_button_right_first_rlease)
            {
                glfwSetCursorPosCallback(glfw_window, nullptr);                  //先禁用鼠标移动监听
                Window::mouse_button_right_first_pressed = true;
                Window::mouse_button_right_first_rlease = false;
                glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);//显示鼠标
                // Window::first_change_to_WOW_mode = true;
            }
            // Window::mouse_button_right_first_rlease = true;
            break;
        }
    }//WOW操作模式下的鼠标监听结束
}

//鼠标模式下的鼠标移动回调函数 类似WOW
void WOW_mode_mouse_callback(GLFWwindow* glfw_window, double xpos, double ypos)
{
    if (glfwGetMouseButton(glfw_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    { 
        //防止镜头抖动
        if (Window::first_change_to_WOW_mode)
        {
            Window::cursor_pos_x = xpos;
            Window::cursor_pos_y = ypos;
            Window::first_change_to_WOW_mode = false;
        }
        float xoffset = xpos - Window::cursor_pos_x;
        float yoffset = Window::cursor_pos_y - ypos; // reversed since y-coordinates go from bottom to top

        Window::cursor_pos_x = xpos;
        Window::cursor_pos_y = ypos;

        Window::camera.ProcessMouseMovement(xoffset, yoffset); 
    }
}

//获取当前指针的位置
void get_cursor_pos(GLFWwindow *glfw_window, double xpos, double ypos)
{
    Window::cursor_pos_x = xpos;
    Window::cursor_pos_y = ypos;
}

