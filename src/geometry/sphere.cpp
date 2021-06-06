#include <geometry/sphere.h>
using namespace std;
using namespace glm;
Sphere::Sphere():
VAO(0),
VBO(0),
EBO(0),
radius(0.05),
index_count(0),
x_segments(50),
y_segments(50),
color(0.06f, 0.729f, 0.941f, 1.0f),
model(1.0f),
scale(1.0f),
trans_x(0.0f),
trans_y(0.0f),
trans_z(0.0f)
{}

//产生球的mesh,返回VAO
void Sphere::create_sphere()
{
    if(0 == VAO)
    {
        glGenVertexArrays(1, &VAO);

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        vector<vec3> positions; // 球面上的点
        vector<vec2> uv;        //球面上的uv坐标
        vector<vec3> normals;   //球面上的点法线
        vector<unsigned int> indices;

        //生成球的坐标信息
        float PI = 3.14159265359;
        for (unsigned int y = 0; y <= y_segments; ++y)
        {
            for (unsigned int x = 0; x <= x_segments; ++x)
            {
                // 绘制球面上的点
                float x_segment = (float)x / (float)x_segments;
                float y_segment = (float)y / (float)y_segments;
                float x_pos = cos(x_segment * 2.0f * PI) * sin(y_segment * PI) * radius;
                float y_pos = cos(y_segment * PI) * radius;
                float z_pos = sin(x_segment * 2.0f * PI) * sin(y_segment * PI) * radius;

                positions.push_back(vec3(x_pos, y_pos, z_pos));
                uv.push_back(vec2(x_segment, y_segment));
                normals.push_back(vec3(x_pos, y_pos, z_pos));
            }
        }

        //生成EBO
        // 将三个点绘制成一个面
        bool odd_row = false; //是否是奇数行
        for (unsigned int y = 0; y < y_segments; ++y)
        {
            if (!odd_row) 
            {
                // even rows: y == 0, y == 2; and so on
                for (unsigned int x = 0; x <= x_segments; ++x)
                {
                    indices.push_back(y * (x_segments + 1) + x);
                    indices.push_back((y + 1) * (x_segments + 1) + x);
                }
            }
            else
            {
                for (int x = x_segments; x >= 0; --x) 
                {// 注意这里是int类型而不是unsigned int 如果是unsigned int会陷入死循环，因为无符号数不会小于0
                    indices.push_back((y + 1) * (x_segments + 1) + x);
                    indices.push_back(y * (x_segments + 1) + x);
                }
            }
            odd_row = !odd_row;
        }
        index_count = indices.size();

        // 将点的坐标 法线 uv坐标放到一起（放入data内）
        vector<float> data;
        for (unsigned int i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x);
            data.push_back(positions[i].y);
            data.push_back(positions[i].z);
            if (uv.size() > 0)
            {
                data.push_back(uv[i].x);
                data.push_back(uv[i].y);
            }
            if (normals.size() > 0)
            {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
        }
        // VAO VBO EBO 传输球的顶点数据
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        float stride = (3 + 2 + 3) * sizeof(float); // 第一个3 position.xyz 第二个2 uv.xy 第三个3 normal.xyz
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void *)(5 * sizeof(float)));
    }
    //绘制组成球面的三角形
    // glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLE_STRIP, index_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    return ;
}

//根据point_size设置球的半径和分割数量
void Sphere::set_radius_segments_by_point_size(float point_size)
{
    //先删VBO EBO VAO
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    //重置VBO VAO EBO
    VBO = 0;
    EBO = 0;
    VAO = 0;
    //设置球的参数
    radius = point_size * 0.05;
    x_segments = 10 + point_size;
    y_segments = 10 + point_size;
    //打印球的细分程度
    // cout << "x_segments : " << x_segments << endl;
    // cout << "y_segments : " << y_segments << endl;
    create_sphere();
}