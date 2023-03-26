#pragma once

#include <glm/gtx/intersect.hpp>
#include "hittable.h"
#include "../obj/obj.h"

class HittableObj : public Hittable {
    public:
        HittableObj(OBJ object, Material *mat) : obj(object), material(mat) {};
        
        virtual bool IsHitByRay(
            const Ray& ray, double maxDistance, Hit& hit) const override;

    public:
        OBJ obj;
        Material *material;
};

bool HittableObj::IsHitByRay(const Ray& ray, double maxDistance, Hit& hit) const {
    vector<Point> vertices = obj.faces();
    hit.distance = maxDistance;
    bool thereIsHit = false;
    for (int i = 0; i < vertices.size(); i+=3)
    {
        glm::vec2 baryPosition;

        float distance;
        if (glm::intersectRayTriangle(ray.orig, ray.dir, vertices[i], vertices[i+1], vertices[i+2], baryPosition, distance)) {
            if (distance > epsilon && distance < hit.distance) {
                hit.distance = distance;
                hit.point = ray.CalcPointAt(distance);
                glm::vec3 tempNormal = glm::normalize(glm::cross(vertices[i+1] - vertices[i], vertices[i+2] - vertices[i]));
                hit.setNormal(ray, tempNormal);
                hit.material = material;
                thereIsHit = true;
            }
        }
    }
    return thereIsHit;
}