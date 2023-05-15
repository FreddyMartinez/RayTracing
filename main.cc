#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include "ray/ray.h"
#include "camera/camera.h"
#include "png/png.h"
#include "hittable/hittable.h"
#include "world.h"
#include "color.h"

using namespace std;

void Draw(vector<Ray> &rayVector, World &world);
Color GetMultiSampledColor(const Ray &ray, World &world);

const int width = 500;
const int height = 500;

const int numOfSamples = 100;
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

    unsigned t0 = clock();

    // definir posición de la cámara
    Camera camera(glm::vec3(xpos, ypos, zpos), width, height);
    // generar rayos
    vector<Ray> rayVector = CreateRayVector(camera, numOfSamples);

    // cargar el(los) objeto(s)
    World world = World();

    // pintar escena
    Draw(rayVector, world);

    unsigned t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;
    return 0;
}

void Draw(vector<Ray> &rayVector, World &world)
{
    PNG png(width, height);
    #pragma omp parallel for
    for (int i = 0; i < rayVector.size(); i++)
    {
        Color color = GetMultiSampledColor(rayVector[i], world);
        png.set(rayVector[i].x, rayVector[i].y, color.x, color.y, color.z);
    }
    png.save("TestImg.png");
}

Color GetMultiSampledColor(const Ray &ray, World &world)
{
    Color color = ColorPixel(ray, world, 1);
    for (const auto randRay : ray.randomRayVector)
    {
        color += ColorPixel(randRay, world, 1);
    }
    return float(1.0 / (numOfSamples + 1)) * color;
}
