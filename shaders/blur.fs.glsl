#version 330 core
out vec4 frag_color;

in vec2 tex_coords;

uniform sampler2D image;        // 要进行模糊的图像
uniform bool horizontal;        // 是否是横向滤波

// 滤波的权重
// uniform float weight[5] = float[] (
//     0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162
// );

uniform float weight[20] = float[] (
0.019947114190202175
,
0.019922195874656212
,
0.0198476275431326
,
0.019723966713621744
,
0.019552134865534525
,
0.019333406005038637
,
0.019069390935670574
,
0.01876201750586965
,
0.01841350717221645
,
0.01802634827683057
,
0.01760326648835465
,
0.017147192897218982
,
0.016661230286694955
,
0.016148618121128576
,
0.01561269680150001
,
0.01505687173616149
,
0.014484577761614267
,
0.013899244425097598
,
0.013304262608410866
,
0.012702952931803959
);

void main()
{
    vec2 tex_offset = 1.0 / textureSize(image, 0);              // 获取单个像素的size
    vec3 result = texture(image, tex_coords).rgb * weight[0];
    // 开始滤波
    if(horizontal)  // 先横向
    {
        for(int i = 1; i < 20; ++i)
        {
            result += texture(image, tex_coords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, tex_coords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else   // 再纵向
    {
        for(int i = 1; i < 20; ++i)
        {
            result += texture(image, tex_coords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, tex_coords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    frag_color = vec4(result, 1.0f);
}