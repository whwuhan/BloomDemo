#version 330 core
// MRT Multiple Render Target
layout (location = 0) out vec4 frag_color;          // 正常渲染场景
layout (location = 1) out vec4 bright_color;        // 场景中高亮的部分

in VsOut
{
    vec3 frag_pos;                      // 将顶点在世界坐标系中的位置传递给片段着色器
    vec3 normal;                        // 顶点的法线（注意是经过model矩阵移动过后的顶点法线）
    vec2 tex_coords;                    // 顶点的纹理坐标
} fs_in;

// uniform vec3 view_pos;                  // 视线的位置
uniform vec4 light_color;               // 发光球体的颜色

void main()
{
    // float dis = length(fs_in - view_pos);
    vec4 result = light_color;
    float brightness = dot(vec3(light_color), vec3(0.2126, 0.7152, 0.0722));    // 光照强度
    if(brightness > 1)
    {
        bright_color = result;                                      // 高亮部分就是原有的颜色
    }
    else
    {
        bright_color = vec4(0.0, 0.0, 0.0, 1.0);                // 非高亮部分就是纯黑色
    }
    frag_color = result;
}

