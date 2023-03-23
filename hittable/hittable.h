/**
 * Inspired by https://raytracing.github.io/books/RayTracingInOneWeekend.html
*/

#pragma once

#include "../ray/ray.h"

const float epsilon = 0.01;

struct Hit {
    Point point;
    glm::vec3 normal;
    double distance;
};

class Hittable {
    public:
        virtual bool IsHitByRay(const Ray& ray, double maxDistance, Hit& hit) const = 0;
};
