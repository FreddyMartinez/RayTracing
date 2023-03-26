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
    glm::vec3 reflection;

    inline void setNormal(const Ray& r, const glm::vec3& tempNormal) {
        bool normalPointsOut = glm::dot(r.dir, tempNormal) < 0;
        normal = normalPointsOut ? tempNormal : float(-1.0) * tempNormal;

        reflection = r.dir - float(2.0) * glm::dot(r.dir, normal) * normal;
        if(dot(reflection, normal) < 0 ) cout << "va para adentro" << endl;
    }
};

class Hittable {
    public:
        virtual bool IsHitByRay(const Ray& ray, double maxDistance, Hit& hit) const = 0;
};
