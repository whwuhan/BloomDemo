#pragma once
class Sphere
{
public:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;                                           // Element Buffer Object
    double radius;                                              // 半径
    unsigned int index_count;                                   //坐标的数量
    unsigned int x_segments;                                    //x轴上的分割数量
    unsigned int y_segments;                                    //y轴上的分割数量

    Sphere();
    void create_sphere();                                       // 生成一个球
    void set_radius_segments_by_point_size(float point_size);   // 根据point size设置球的半径和分割数量
};// end Sphere