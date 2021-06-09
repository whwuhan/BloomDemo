#version 330 core
out vec4 frag_color;
in vec2 tex_coords;

uniform sampler2D tex;            // 原始场景

void main()
{
    frag_color = vec4(texture(tex, tex_coords).rgb, 1.0f);
    // frag_color = vec4(1.0f, 0.2f, 0.1f, 1.0f);
}