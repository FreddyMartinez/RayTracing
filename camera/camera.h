#pragma once

#include <glm/glm.hpp>

using namespace std;

using Point = glm::vec3;  
using Color = glm::vec3;

class Camera {
    public:
        Point orig;
        glm::vec3 u;
        glm::vec3 l;
        glm::vec3 f;
        int width;
        int height;

        Camera(Point origin, int viewWidth, int viewHeight);
        void setU(glm::vec3 uv);
        void setL(glm::vec3 lv);
        void setF(glm::vec3 fv);
        glm::mat4 getTransMatrix();
};

