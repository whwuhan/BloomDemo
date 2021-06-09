#version 330 core
out vec4 frag_color;

in vec2 tex_coords;

uniform sampler2D image;        // 要进行模糊的图像
uniform bool horizontal;        // 是否是横向滤波

// 滤波的权重
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
    vec2 tex_offset = 1.0 / textureSize(image, 0);              // 获取单个像素的size
    vec3 result = texture(image, tex_coords).rgb * weight[0];
    // 开始滤波
    if(horizontal)  // 先横向
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, tex_coords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, tex_coords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else   // 再纵向
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, tex_coords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, tex_coords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    frag_color = vec4(result, 1.0f);
}