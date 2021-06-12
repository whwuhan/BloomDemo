#include <UI/bloom_demo_ui.h>

// 初始化
GLFWwindow* BloomDemoUI::glfw_window        = nullptr;      // glfw window
float BloomDemoUI::font_size                = 18.0;         // 字体大小
float BloomDemoUI::global_scale             = 1.0;          // 整体的字体缩放
float BloomDemoUI::window_rounding          = 6.0;          // 窗口的圆角
float BloomDemoUI::frame_rounding           = 3.0;          // 内部图标的圆角
bool BloomDemoUI::show_usage                = true;         // 显示操作手册
bool BloomDemoUI::show_right_sidebar        = true;         // 显示右边Sidebar
bool BloomDemoUI::show_message_box          = true;         // 信息窗口
int BloomDemoUI::style                      = 0;            // UI风格
float BloomDemoUI::message_box_pos_x        = 3;            //message box距离左边距离
float BloomDemoUI::message_box_pos_y        = 3;          //message box距离usage的纵向距离


void BloomDemoUI::init(GLFWwindow* glfw_window)             // 初始化，在渲染循环外
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //io
    ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
    io.FontGlobalScale = global_scale;//设置字体的缩放大小
    // io.Fonts->AddFontFromFileTTF("fonts/Cousine-Regular.ttf", font_size);//设置字体
    // io.Fonts->AddFontFromFileTTF("fonts/DroidSans.ttf", font_size);//设置字体
    // io.Fonts->AddFontFromFileTTF("fonts/Karla-Regular.ttf", font_size);//设置字体
    // io.Fonts->AddFontFromFileTTF("fonts/ProggyClean.ttf", font_size);//设置字体
    //io.Fonts->AddFontFromFileTTF("fonts/ProggyTiny.ttf", font_size);//设置字体
    io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", BloomDemoUI::font_size);//设置字体
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = frame_rounding; //设置frame的圆角
    style.WindowRounding = window_rounding;//设置window的圆角
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

// 渲染imgui demo
void BloomDemoUI::render_demo_ui()
{
    // imgui初始化
    bool show = true;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGui::ShowDemoWindow(&show);
    
    // imgui渲染
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// 渲染所有的UI
void BloomDemoUI::render()
{
    // 初始化imgui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");
    
    // 渲染所有的UI
    render_message_box();

    // imgui渲染
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// 渲染信息框
void BloomDemoUI::render_message_box()
{
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    //获取glfw window宽高
    int win_width, win_height;
    glfwGetFramebufferSize(Window::glfw_window, &win_width, &win_height);
    //设置大小
    // ImGui::SetNextWindowSize
    // (
    //     ImVec2(CoolenderUI::messageBoxWidth, CoolenderUI::messageBoxHeight), 
    //     ImGuiCond_FirstUseEver
    // );

    //设置位置
    ImGui::SetNextWindowPos(
        ImVec2(   
            // 注意FramebufferSize是窗口实际长度的2倍(?????)
            main_viewport->WorkPos.x + BloomDemoUI::message_box_pos_x, 
            main_viewport->WorkPos.y + BloomDemoUI::message_box_pos_y
        ), 
        ImGuiCond_FirstUseEver
    );

    //Message box
    ImGui::Begin("Message Box", &BloomDemoUI::show_message_box, ImGuiWindowFlags_AlwaysAutoResize);
    {   
        //显示帧数
        ImGui::Text
        (
            "Application average %.3f ms/frame (%.1f FPS)", 
            1000.0f / ImGui::GetIO().Framerate, 
            ImGui::GetIO().Framerate
        );
    }
    ImGui::End();
}

// 清空数据
void BloomDemoUI::destroy()
{

}



