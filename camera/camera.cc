#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "camera.h"

using namespace std;

Camera::Camera(Point origin)
{
    l = glm::vec3(1.0f, 0.0f, 0.0f);
    u = glm::vec3(0.0f, 1.0f, 0.0f);
    f = glm::vec3(0.0f, 0.0f, 1.0f);
    orig = origin;
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
    glm::mat4 extended = glm::mat4(rot);
    glm::mat4 M = glm::translate(extended, orig);
    return M;
}
