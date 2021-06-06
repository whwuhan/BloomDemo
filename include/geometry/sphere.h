#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <vector>
#include <iostream>
class Sphere
{
public:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;                                           // Element Buffer Object
    double radius;                                              // 半径，影响顶点到球心的距离
    unsigned int index_count;                                   // 坐标的数量
    unsigned int x_segments;                                    // x轴上的分割数量
    unsigned int y_segments;                                    // y轴上的分割数量
    glm::mat4 model;                                            // model矩阵
    glm::vec4 color;                                            // 颜色
    float scale;                                                // 缩放大小
    float trans_x;                                              // X轴的位移
    float trans_y;                                              // Y轴的位移
    float trans_z;                                              // Z轴的位移
    Sphere();
    void create_sphere();                                       // 根据x_segments和y_segments生成球
    void set_radius_segments_by_point_size(float point_size);   // 根据point size设置球的半径和分割数量
};// end Sphere