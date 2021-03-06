#include<components/scene.h>
using namespace std;

unsigned int Scene::sphere_count = 0;                                              // 发光球体数量
map<string, Sphere> Scene::spheres;                                                 // 场景中的发光球体

Scene::Scene(){}

// 给场景添加物体
void Scene::add_sphere(const std::string& sphere_name, const Sphere& sphere)       // 添加发光球体
{
    string name = sphere_name + "_" + to_string(sphere_count++);       // 重命名
    spheres[name] = sphere;
    cout << "Add Sphere: "<< name <<" successfully." << endl;
}

// 删除场景中的物体
void Scene::delete_sphere(const std::string& sphere_name)                          // 删除发光球体
{
    spheres.erase(sphere_name);
    cout << "Delete Sphere:" << sphere_name << " successfully." << endl;
}


