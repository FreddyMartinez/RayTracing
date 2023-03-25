#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "camera.h"

using namespace std;

Camera::Camera(Point origin, int viewWidth, int viewHeight)
{
    f = glm::normalize(Point(0.0, 0.0, 0.0) - origin);
    l = glm::normalize(glm::cross(glm::vec3(0.0, 1.0, 0.0), f));
    u = glm::normalize(glm::cross(f, l));
    orig = origin;
    width = viewWidth;
    height = viewHeight;
}

void Camera::setL(glm::vec3 lv)
{
    l = lv;
}

void Camera::setU(glm::vec3 uv)
{
    u = uv;
}

void Camera::setF(glm::vec3 fv) {
    f = fv;
}

glm::mat4 Camera::getTransMatrix()
{
    glm::mat3 rot = glm::mat3(l, u, f);
    glm::mat4 M = glm::mat4(rot);
    M[3][0] = orig.x;
    M[3][1] = orig.y;
    M[3][2] = orig.z;
    return M;
}
