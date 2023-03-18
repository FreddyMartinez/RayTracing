#include <vector>
#include <iostream>
#include "ray.h"
#include "camera.h"
#include "obj.h"
#include "png.h"

using namespace std;

void Draw(vector<Ray> &rayVector);
glm::vec3 ColorPixel(const Ray &ray);
float HitSphere(const Point &center, double radius, const Ray &r);

const int width = 500;
const int height = 500;

int main(int argc, char *argv[])
{
    // definir posición de la cámara
    Camera camera(glm::vec3(0.0f, 0.0f, -2.0f));
    // generar rayos
    vector<Ray> rayVector = CreateRayVector(camera, width, height);

    // cargar el(los) objeto(s)
    OBJ obj;
    obj.load("./obj/cube.obj");

    // calcular intersecciones
    // punto = camara + rayo*distancia

    // pintar escena
    Draw(rayVector);

    return 0;
}

void Draw(vector<Ray> &rayVector)
{
    PNG png(width, height);
    for (int i = 0; i < rayVector.size(); i++)
    {
        glm::vec3 color = ColorPixel(rayVector[i]);
        png.set(rayVector[i].x, rayVector[i].y, color.x, color.y, color.z);
    }
    png.save("TestImg.png");
}

glm::vec3 ColorPixel(const Ray &ray)
{
    float t = HitSphere(Point(0, 0, -1), 0.5, ray);
    if (t > 0.0)
    {
        glm::vec3 N = glm::normalize(ray.orig + t*ray.dir - glm::vec3(0, 0, -1));
        return float(0.5) * glm::vec3(N.x + 1, N.y + 1, N.z + 1);
    }

    t = ray.dir.y + 1.0;
    return float(1.0 - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
}

float HitSphere(const Point &center, double radius, const Ray &r)
{
    glm::vec3 oc = r.orig - center;
    auto a = glm::dot(r.dir, r.dir);
    auto b = 2.0 * dot(oc, r.dir);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    return (-b - sqrt(discriminant)) / (2.0 * a);
}
