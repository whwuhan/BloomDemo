#include <utils/render.h>
using namespace std;

void Render::render_sphere(const Sphere& sphere)
{
    glBindVertexArray(sphere.VAO);
    // cout << sphere.index_count << endl;
    glDrawElements(GL_TRIANGLE_STRIP, sphere.index_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Render::render_quad(const Quad& quad)
{
    glBindVertexArray(quad.VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}