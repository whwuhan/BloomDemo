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
0.03989422838040435, 0.0396952550862652, 0.03910426973106905, 0.03813878187134115, 0.0368270143444329, 0.0352065329767093, 0.03332246057338991, 0.03122539360300002, 0.028969155523228533, 0.02660852521682173, 0.024197072658293114, 0.02178521788906293, 0.019418605663944145, 0.017136859350942387, 0.014972746691278247, 0.012951759677055773, 0.01109208356255083, 0.009404907817903907, 0.00789501589742664, 0.006561581533431916, 0.005399096697368135, 0.004398359635556682, 0.0035474593148797097, 0.002832703798320476, 0.002239453048584765, 0.0017528300643068824, 0.0013582969349535856, 0.0010420934903303586, 0.0007915451650491488, 0.0005952532470545482
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