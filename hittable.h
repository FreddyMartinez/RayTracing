/**
 * Inspired by https://raytracing.github.io/books/RayTracingInOneWeekend.html
*/

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

const float epsilon = 0.01;

struct Hit {
    Point p;
    glm::vec3 normal;
    double distance;
};

class Hittable {
    public:
        virtual bool CalculateHit(const Ray& ray, double maxDistance, Hit& hit) const = 0;
};

#endif