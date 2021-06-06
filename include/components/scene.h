#pragma once
#include <map>
#include <glm/glm.hpp>
#include <geometry/sphere.h>
class Scene
{
public:
    Scene();

    static unsigned int sphere_count;                                                  // 发光球体数量

    // 给场景添加物体
    static void add_sphere(const std::string& sphere_name, const Sphere& sphere);       // 添加发光球体

    // 删除场景中的物体
    static void delete_sphere(const std::string& sphere_name);                          // 删除发光球体

    static std::map<std::string, Sphere> spheres;                                       // 场景中的发光球体
};// end class Scene
