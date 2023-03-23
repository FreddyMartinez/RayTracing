#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "ray.h"
#include "../camera/camera.h"

using namespace std;

Ray::Ray(Point origin, Point point) {
    orig = origin;
    glm::vec3 nonNorm = point - origin;
    dir = glm::normalize(nonNorm);
}

void Ray::setPosition(int i, int j){
    x = i;
    y = j;
}

vector<Ray> CreateRayVector(Camera& camera)
{
    vector<Ray> rayVector;
    // crea puntos en espacio de cámara [-1,1] 
    double dx = 2 / float(camera.width);
    double dy = 2 / float(camera.height);

    glm::mat4 M = camera.getTransMatrix();
    
    for (int i = 0; i < camera.width; i++)
    {
        double xpos = dx / 2 + i * dx -1 ;
        for (int j = 0; j < camera.height; j++)
        {
            double ypos = 1 - (dy / 2 + j * dy); // flip vertically
            glm::vec4 p(xpos, ypos, 1, 1);
            glm::vec4 transformed = M * p;
            Ray ray = Ray(camera.orig, glm::vec3(transformed));
            ray.setPosition(i,j);
            rayVector.push_back(ray);
        }
    }
    return rayVector;
}

