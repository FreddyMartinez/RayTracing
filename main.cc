#include <vector>
#include <iostream>
#include <string>
#include "ray/ray.h"
#include "camera/camera.h"
#include "obj/obj.h"
#include "png/png.h"
#include "hittable/hittable.h"
#include "hittable/sphere.h"
#include "hittable/hittableObj.h"

using namespace std;

void Draw(vector<Ray> &rayVector, vector<Hittable*> &world);
glm::vec3 ColorPixel(const Ray &ray, vector<Hittable*> &world);
glm::vec3 GetMultiSampledColor(const Ray &ray, vector<Hittable*> &world);
vector<Hittable*> CreateWorld();

const int width = 500;
const int height = 500;

const double maxDistance = 100.0;
const int numOfSamples = 5.0;

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
    Camera camera(glm::vec3(xpos, ypos, zpos), width, height);
    // generar rayos
    vector<Ray> rayVector = CreateRayVector(camera, numOfSamples);

    // cargar el(los) objeto(s)
    vector<Hittable*> world = CreateWorld();

    // pintar escena
    Draw(rayVector, world);

    return 0;
}

void Draw(vector<Ray> &rayVector, vector<Hittable*> &world)
{
    PNG png(width, height);
    for (int i = 0; i < rayVector.size(); i++)
    {
        glm::vec3 color = GetMultiSampledColor(rayVector[i], world);
        png.set(rayVector[i].x, rayVector[i].y, color.x, color.y, color.z);
    }
    png.save("TestImg.png");
}

glm::vec3 GetMultiSampledColor(const Ray &ray, vector<Hittable *> &world)
{
    glm::vec3 color = ColorPixel(ray, world);
    for (const auto randRay : ray.randomRayVector)
    {
        color += ColorPixel(randRay, world);
    }
    return float(1.0 / (numOfSamples + 1)) * color;
}

glm::vec3 ColorPixel(const Ray &ray, vector<Hittable*> &world)
{
    Hit hit;
    std::vector<Hittable*>::iterator hitObj;
    for (const auto& hitObj : world) {
        if (hitObj->IsHitByRay(ray, maxDistance, hit))
        {
            return float(0.5) * glm::vec3(hit.normal.x + 1, hit.normal.y + 1, hit.normal.z + 1);
        }
    }

    float t = ray.dir.y + 1.0;
    return float(1.0 - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
}


vector<Hittable*> CreateWorld() {
    vector<Hittable*> world;
    // add cube
    OBJ cube("./obj/cube.obj");
    HittableObj* hcube = new HittableObj(cube);
    world.push_back(hcube);
    // add sphere
    Sphere* sphere = new Sphere(Point(-0.8, 0.5, 0), 0.5);
    world.push_back(sphere);
    // add floor
    OBJ plane("./obj/floor.obj");
    plane.scale(20);
    HittableObj* hplane = new HittableObj(plane);
    world.push_back(hplane);
    return world;
}