#pragma once

#include <vector>
#include "obj/obj.h"
#include "hittable/hittable.h"
#include "hittable/sphere.h"
#include "hittable/hittableObj.h"

class World {
    public: 
        vector<Hittable*> objects;
        Point light;

        void LoadObjects();
        World(Point globalLight): light(globalLight) {
            LoadObjects();
        };
};

void World::LoadObjects() {
    Material* basicRedMat = new Material(Color(0.9, 0.2, 0.2), 0.2);
    // add cube
    OBJ cube("./obj/cube.obj");
    cube.translate(glm::vec3(1.0, 0.5, 0.0));
    HittableObj* hcube = new HittableObj(cube, basicRedMat);
    objects.push_back(hcube);
    // add sphere
    Sphere* sphere = new Sphere(Point(-0.8, 0.5, 0), 0.5, basicRedMat);
    objects.push_back(sphere);
    // second sphere
    Material* basicBlueMat = new Material(Color(0.1, 0.2, 0.9), 0.2);
    Sphere* sphere2 = new Sphere(Point(0, 0.5, 2), 0.5, basicBlueMat);
    objects.push_back(sphere2);
    // add floor
    OBJ plane("./obj/floor.obj");
    plane.scale(20);
    Material* floorMat = new Material(Color(0.7, 0.7, 0.7), 0.8);
    HittableObj* hplane = new HittableObj(plane, floorMat);
    objects.push_back(hplane);
}