#include <vector>
#include <iostream>
#include "ray.h"
#include "obj.h"
#include "png.h"

using namespace std;

void Draw(vector<Ray>& rayVector);
glm::vec3 ColorPixel(const glm::vec3& ray);

const int width = 2;
const int height = 6;

int main(int argc,char* argv[])
{
    // definir posición de la cámara
    const glm::vec3 camera(0.0f, 0.0f, -2.0f);
    // generar rayos
    vector<Ray> rayVector = CreateRayVector(camera, width, height);

    // cargar el(los) objeto(s)
    OBJ	obj;
    obj.load("./obj/cube.obj");

    // calcular intersecciones
    // punto = camara + rayo*distancia

    // pintar escena
    Draw(rayVector);

    return 0;
}

void Draw(vector<Ray>& rayVector) {
    PNG png(width, height);
    for (int i=0; i<rayVector.size(); i++) {
        cout << i << endl;
        glm::vec3 color = ColorPixel(rayVector[i].dir);
        cout << rayVector[i].x << ", " << rayVector[i].y << " [" << color.x << ", " << color.y << ", " << color.z << "] ";
        png.set(rayVector[i].x, rayVector[i].y, color.x, color.y, color.z);
    }
    png.save("TestImg.png");
    cout << "Debe dibujar!!" << endl;
}

glm::vec3 ColorPixel(const glm::vec3& ray) {
    if(ray.y > 0){
        return glm::vec3(255.0, 0, 0);
    }
    return glm::vec3(255.0, 255.0, 255.0);
}
