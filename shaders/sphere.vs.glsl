#version 330 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_tex_coords;

// 传递给fs的数据
out VsOut
{
    vec3 frag_pos;                      // 将顶点在世界坐标系中的位置传递给片段着色器
    vec3 normal;                        // 顶点的法线（注意是经过model矩阵移动过后的顶点法线）
    vec2 tex_coords;                    // 顶点的纹理坐标
} vs_out;

// uniform
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vs_out.frag_pos = a_pos;
    vs_out.normal = a_normal;
    vs_out.tex_coords = a_tex_coords;
    gl_Position = projection * view * model * vec4(a_pos, 1.0f);
}