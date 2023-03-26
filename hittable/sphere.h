#pragma once

#include "hittable.h"

class Sphere : public Hittable {
    public:
        Sphere(Point cen, double r, Material *mat) : center(cen), radius(r), material(mat){};

        virtual bool IsHitByRay(
            const Ray& ray, double maxDistance, Hit& rec) const override;

    public:
        Point center;
        double radius;
        Material *material;
};

/**
 * Hits for the sphere are found solving the cuadratic equation (P-C)^2 = r^2
 * (ray.orig + t*ray.dir - C)^2 = r^2
*/
bool Sphere::IsHitByRay(const Ray& ray, double maxDistance, Hit& hit) const {
    glm::vec3 oc = ray.orig - center;
    double b = 2.0 * glm::dot(oc, ray.dir);
    double c = glm::dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * c; // a = 1 because r.dir is unitary
    if (discriminant < 0)
    {
        return false;
    }
    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    float root = (-b - sqrtd) / 2.0;
    if (root < epsilon || maxDistance < root) {
        root = (-b + sqrtd) / 2.0;
        if (root < epsilon || maxDistance < root)
            return false;
    }

    hit.distance = root;
    hit.point = ray.CalcPointAt(root);
    hit.setNormal(ray, glm::normalize(hit.point - center));
    hit.material = material;

    return true;
}
