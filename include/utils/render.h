#pragma once 
/**
 * 
 * 渲染
 * 
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geometry/sphere.h>

class Render
{
public:
    // 渲染光源球体
    static void render_sphere(const Sphere& sphere);
};// end Render
