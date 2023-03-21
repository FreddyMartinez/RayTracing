#pragma once

#include <glm/gtx/intersect.hpp>
#include "hittable.h"
#include "obj.h"

class HittableObj : public Hittable {
    public:
        HittableObj() {}
        HittableObj(OBJ object) : obj(object) {};
        
        virtual bool IsHitByRay(
            const Ray& ray, double maxDistance, Hit& hit) const override;

    public:
        OBJ obj;
        Point pos;
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
            if (distance > epsilon && distance < hit.distance) { // TODO: verificar que es el más cercano
                hit.distance = distance;
                hit.point = ray.CalcPointAt(distance);
                hit.normal = glm::normalize(glm::cross(vertices[i+1] - vertices[i], vertices[i+2] - vertices[i]));
                thereIsHit = true;
            }
        }
    }
    return thereIsHit;
}