#include <utils/render.h>
using namespace std;
void Render::render_sphere(const Sphere& sphere)
{
    glBindVertexArray(sphere.VAO);
    // cout << sphere.index_count << endl;
    glDrawElements(GL_TRIANGLE_STRIP, sphere.index_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}