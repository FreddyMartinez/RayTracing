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
#include "world.h"

using namespace std;

void Draw(vector<Ray> &rayVector, World &world);
Color ColorPixel(const Ray &ray, World &world);
Color GetMultiSampledColor(const Ray &ray, World &world);

const int width = 500;
const int height = 500;

const double maxDistance = 100.0;
const int numOfSamples = 5.0;
const int maxNumOfRebounds = 3;

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
    World world = World(Point(0.0, 50.0, 0.0));

    // pintar escena
    Draw(rayVector, world);

    return 0;
}

void Draw(vector<Ray> &rayVector, World &world)
{
    PNG png(width, height);
    for (int i = 0; i < rayVector.size(); i++)
    {
        Color color = GetMultiSampledColor(rayVector[i], world);
        png.set(rayVector[i].x, rayVector[i].y, color.x, color.y, color.z);
    }
    png.save("TestImg.png");
}

Color GetMultiSampledColor(const Ray &ray, World &world)
{
    Color color = ColorPixel(ray, world);
    for (const auto randRay : ray.randomRayVector)
    {
        color += ColorPixel(randRay, world);
    }
    return float(1.0 / (numOfSamples + 1)) * color;
}

Color ColorPixel(const Ray &ray, World &world)
{
    Hit hit;
    Hit nearestHit;
    nearestHit.distance = maxDistance;
    std::vector<Hittable*>::iterator hitObj;
    for (const auto& hitObj : world.objects) {
        if (hitObj->IsHitByRay(ray, maxDistance, hit))
        {
            if (hit.distance < nearestHit.distance)
            {
                nearestHit = hit;
            }
        }
    }
    if (nearestHit.distance < maxDistance)
    {
        return float(0.5) * glm::vec3(nearestHit.normal.x + 1, nearestHit.normal.y + 1, nearestHit.normal.z + 1);
    }

    float t = ray.dir.y + 1.0;
    return float(1.0 - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
}
