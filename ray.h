#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

using namespace std;

using Point = glm::vec3;  
using Color = glm::vec3;

class Ray {
    public:
        glm::vec3 dir;
        Point orig;
        int x;
        int y;

        Ray(Point origin, Point p);
        void setPosition(int x, int y);
};

glm::vec4 Transform(glm::vec4 vector, glm::mat4 Matrix);
vector<Ray> CreateRayVector(glm::vec3 camera, int width, int height);
