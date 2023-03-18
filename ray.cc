#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "ray.h"

using namespace std;

Ray::Ray(glm::vec3 origin, glm::vec3 point) {
    orig = origin;
    glm::vec3 nonNorm = point - origin;
    dir = glm::normalize(nonNorm);
}

void Ray::setPosition(int i, int j){
    x = i;
    y = j;
}

glm::vec4 Transform(glm::vec4 vector, glm::mat4 Matrix)
{
    return Matrix * vector;
}

vector<Ray> CreateRayVector(glm::vec3 camera, int width, int height)
{
    vector<Ray> rayVector;
    // crea puntos en espacio de cámara [-1,1] 
    double dx = 2 / float(width);
    double dy = 2 / float(height);

    glm::mat4 M = glm::translate(glm::mat4(1.0f), camera);
    // cout << glm::to_string(M) << endl;
    
    // TODO: recorrer solo de 0 a 1 
    for (int i = 0; i < width; i++)
    {
        double xpos = dx / 2 + i * dx -1 ;
        for (int j = 0; j < height; j++)
        {
            double ypos = dy / 2 + j * dy -1 ;
            glm::vec4 p(xpos, ypos, 1, 1);
            // cout << "[" << p.x << ", " << p.y << ", " << p.z << "] ";
            glm::vec4 transformed = Transform(p, M);
            Ray ray = Ray(camera, glm::vec3(transformed));
            ray.setPosition(i,j);
            // cout << "[" << ray.dir.x << ", " << ray.dir.y << ", " << ray.dir.z << "] ";
            rayVector.push_back(ray);
        }
        cout << endl;
    }
    cout << rayVector.size();
    return rayVector;
}

