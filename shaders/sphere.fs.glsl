#version 330 core
out vec4 frag_color;

in VsOut
{
    vec3 frag_pos;                      // 将顶点在世界坐标系中的位置传递给片段着色器
    vec3 normal;                        // 顶点的法线（注意是经过model矩阵移动过后的顶点法线）
    vec2 tex_coords;                    // 顶点的纹理坐标
} fs_in;

// uniform
uniform vec4 color;

void main()
{
    frag_color = color;
}