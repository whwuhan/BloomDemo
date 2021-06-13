#version 330 core
out vec4 frag_color;

in vec2 tex_coords;

uniform sampler2D image;        // 要进行模糊的图像
uniform bool horizontal;        // 是否是横向滤波

// 滤波的权重
// uniform float weight[5] = float[] (
//     0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162
// );

uniform float weight[30] = float[] (
0.00797884567608087, 0.00797725006651193, 0.007972465152089896, 0.00796449667184197, 0.007953354178066974, 0.00793905101725304, 0.007921604303437121, 0.007901034884080787, 0.007877367298557515, 0.00785062972936723, 0.00782085394621381, 0.0077880752431009285, 0.007752332368620549, 0.007713667449626812, 0.00767212590850575, 0.0076277563742682295, 0.007580610587709671, 0.007530743300895394, 0.007478212171244841, 0.0074230776505013465, 0.007365402868886579, 0.0073052535147501724, 0.007242697710035395, 0.007177805881890976, 0.007110650630767252, 0.007041306595341861, 0.006969850314625904, 0.006896360087606277, 0.006820915830783191, 0.006743598933964309
);

void main()
{
    vec2 tex_offset = 1.0 / textureSize(image, 0);              // 获取单个像素的size
    vec3 result = texture(image, tex_coords).rgb * weight[0];
    // 开始滤波
    if(horizontal)  // 先横向
    {
        for(int i = 1; i < 30; ++i)
        {
            result += texture(image, tex_coords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, tex_coords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else   // 再纵向
    {
        for(int i = 1; i < 30; ++i)
        {
            result += texture(image, tex_coords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, tex_coords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    frag_color = vec4(result, 1.0f);
}