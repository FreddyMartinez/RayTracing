#include <vector>
#include <iostream>
#include <string>
#include "ray.h"
#include "camera.h"
#include "obj.h"
#include "png.h"
#include <glm/gtx/intersect.hpp>
#include "hittable.h"

using namespace std;

void Draw(vector<Ray> &rayVector);
glm::vec3 ColorPixel(const Ray &ray);
float HitSphere(const Point &center, double radius, const Ray &r);
float HitObj(const Ray &ray, const OBJ &obj);

const int width = 500;
const int height = 500;

OBJ obj;

int main(int argc, char *argv[])
{
    if(argc < 4) {
        cout << "Not enough params, camera position required";
        return 0;
    }

    float xpos = std::stof(argv[1]);
    float ypos = std::stof(argv[2]);
    float zpos = std::stof(argv[3]);

    // definir posición de la cámara
    Camera camera(glm::vec3(xpos, ypos, zpos));
    // generar rayos
    vector<Ray> rayVector = CreateRayVector(camera, width, height);

    // cargar el(los) objeto(s)
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
    float t = HitSphere(Point(-0.8, 0, -1), 0.5, ray);
    if (t > 0.0)
    {
        glm::vec3 N = glm::normalize(ray.CalcPointAt(t) - glm::vec3(0, 0, -1));
        return float(0.5) * glm::vec3(N.x + 1, N.y + 1, N.z + 1);
    }

    t = HitObj(ray, obj);
    if (t > 0.0) {
        return float(0.5) * glm::vec3(1, 1, 1);
    }

    t = ray.dir.y + 1.0;
    return float(1.0 - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
}

float HitSphere(const Point &center, double radius, const Ray &r)
{
    glm::vec3 oc = r.orig - center;
    auto b = 2.0 * glm::dot(oc, r.dir);
    auto c = glm::dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * c; // a = 1 because r.dir is unitary
    if (discriminant < 0)
    {
        return -1.0;
    }
    return (-b + sqrt(discriminant)) / (2.0);
}

float HitObj(const Ray &ray, const OBJ &obj) {
    vector<Point> vertices = obj.faces();
    for (int i = 0; i < vertices.size(); i+=3)
    {
        glm::vec2 baryPosition;
        float distance;

        if (glm::intersectRayTriangle(ray.orig, ray.dir, vertices[i], vertices[i+1], vertices[i+2], baryPosition, distance)) {
            return distance;
        }
    }
    return -1.0;
}
