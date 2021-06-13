#include <UI/bloom_demo_ui.h>
using namespace std;
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
float BloomDemoUI::message_box_pos_y        = 3;            //message box距离usage的纵向距离
float BloomDemoUI::right_sidebar_pos_x      = 3;            // 右侧边栏位置的X坐标(距离右侧的距离) 
float BloomDemoUI::right_sidebar_pos_y      = 22;           // 右侧边栏位置的Y坐标
float BloomDemoUI::right_sidebar_width      = 500;          // 右侧边栏宽
float BloomDemoUI::right_sidebar_height     = 650;          // 右侧边栏高

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
    render_message_box();               // 信息框
    render_right_sidebar();             // 右侧sidebar

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
        ImGui::Text(
            "Application average %.3f ms/frame (%.1f FPS)", 
            1000.0f / ImGui::GetIO().Framerate, 
            ImGui::GetIO().Framerate
        );
    }
    ImGui::End();
}

// 渲染有侧边栏
void BloomDemoUI::render_right_sidebar()
{
    //获取glfw window宽高
    int win_width, win_height;
    glfwGetFramebufferSize(Window::glfw_window, &win_width, &win_height);
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    //设置位置
    ImGui::SetNextWindowPos(
        ImVec2(
            main_viewport->WorkPos.x + win_width / 2.0 - BloomDemoUI::right_sidebar_width - BloomDemoUI::right_sidebar_pos_x, 
            main_viewport->WorkPos.y + BloomDemoUI::right_sidebar_pos_y
        ), 
        ImGuiCond_FirstUseEver
    );
    //设置Sidebar大小
    ImGui::SetNextWindowSize(
        ImVec2(BloomDemoUI::right_sidebar_width, BloomDemoUI::right_sidebar_height), 
        ImGuiCond_FirstUseEver
    );

    ImGui::Begin("BloomDemo", &BloomDemoUI::show_right_sidebar, ImGuiWindowFlags_None);
    {
        // 添加photospheres
        ImVec2 button_size(ImGui::GetFontSize() * 8.0f, 0.0f);
        if(ImGui::Button("Add photosphere", button_size))
        {
            Sphere sphere;
            sphere.create_sphere();
            Scene::add_sphere("Photosphere", sphere);
        }

        // 渲染每个球的信息UI
        ImGui::SetNextItemOpen(true, ImGuiCond_Once); // 设置下一个窗口打开（只设置一次）
        if (ImGui::TreeNode("Photospheres:"))
        {
            for(auto it = Scene::spheres.begin(); it != Scene::spheres.end(); it++)
            {
                // 每个发光球的UI
                ImGui::SetNextItemOpen(true, ImGuiCond_Once);
                if (ImGui::TreeNode(it->first.c_str()))
                {
                    // 光球的颜色
                    float photonsphere_color [3] = {
                        it->second.color.x,
                        it->second.color.y,
                        it->second.color.z,
                    };
                    ImGui::ColorEdit3("Color", photonsphere_color);
                    it->second.color.x = photonsphere_color[0];
                    it->second.color.y = photonsphere_color[1];
                    it->second.color.z = photonsphere_color[2];
                    it->second.color.w = 1.0;
                    // cout << it->second.color.x << endl;
                    // cout << color[0] << endl;
                    
                    // 位置和缩放
                    // 平移 
                    ImGui::SetNextItemWidth(80);
                    ImGui::DragFloat("trans_x", &it->second.trans_x, 0.01f);ImGui::SameLine();                        
                    ImGui::SetNextItemWidth(80);
                    ImGui::DragFloat("trans_y", &it->second.trans_y, 0.01f);ImGui::SameLine();
                    ImGui::SetNextItemWidth(80);
                    ImGui::DragFloat("trans_z", &it->second.trans_z, 0.01f);
                    it->second.model = glm::translate(
                        glm::mat4(1.0f),
                        glm::vec3(it->second.trans_x, it->second.trans_y, it->second.trans_z)
                    );
                    
                    // 缩放
                    ImGui::SliderFloat("Scale", &it->second.scale, 0.0f, 10.0f, "Scale = %.3f");
                    it->second.model = glm::scale(it->second.model, glm::vec3(it->second.scale));

                    //delete button 
                    ImVec2 button_size(ImGui::GetFontSize() * 6.0f, 0.0f);
                    if(ImGui::Button("Delete", button_size))
                    {
                        Scene::delete_sphere(it->first);
                        //注意这里删除后要break否则会出现内存错误
                        //猜测是因为map删除元素后，迭代器失效！！！！
                        ImGui::TreePop();
                        break;
                    }
                    ImGui::TreePop();
                } // end Light TreeNode
            }
            ImGui::TreePop();
        } // end Lights TreeNode
        
        
    }
    ImGui::End();//sidebar结束
}

// 清空数据
void BloomDemoUI::destroy()
{

}



