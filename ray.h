#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "camera.h"

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

vector<Ray> CreateRayVector(Camera& camera, int width, int height);
