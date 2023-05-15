#pragma once

#include <vector>
#include "obj/obj.h"
#include "hittable/hittable.h"
#include "hittable/sphere.h"
#include "hittable/hittableObj.h"

class Light {
    public:

        Point point;
        float energy;

        Light(Point p, float e): point(p), energy(e) {};
};

class World {
    public: 
        vector<Hittable*> objects;
        vector<Light*> lights;

        void LoadObjects();
        void CreateLights();
        World() {
            LoadObjects();
            CreateLights();
        };
};

void World::CreateLights() {
    Light* mainLight = new Light(Point(-2.0, 10.0, 0.0), 80.0);
    lights.push_back(mainLight);

    Light* secondLight = new Light(Point(2.0, 10.0, 5.0), 60.0);
    lights.push_back(secondLight);
}

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
    Material* basicBlueMat = new Material(Color(0.1, 0.2, 0.9), 0.95);
    Sphere* sphere2 = new Sphere(Point(0, 0.5, 2), 0.5, basicBlueMat);
    objects.push_back(sphere2);
    // add floor
    OBJ plane("./obj/floor.obj");
    plane.scale(20);
    Material* floorMat = new Material(Color(0.7, 0.7, 0.7), 0.0);
    HittableObj* hplane = new HittableObj(plane, floorMat);
    objects.push_back(hplane);

    // add right wall
    OBJ firstWall("./obj/lt_wall.obj");
    firstWall.translate(glm::vec3(0.4, 0.5, 0.0));
    firstWall.scale(10);
    Material *wallMat = new Material(Color(0.2, 0.9, 0.2), 0.1);
    HittableObj *hittableWall = new HittableObj(firstWall, wallMat);
    objects.push_back(hittableWall);
    // add left wall
    OBJ secondWall("./obj/lt_wall.obj");
    secondWall.translate(glm::vec3(-0.4, 0.5, 0.0));
    secondWall.scale(10);
    Material *secondWallMat = new Material(Color(0.8, 0.1, 0.8), 0.1);
    HittableObj *secondHittableWall = new HittableObj(secondWall, secondWallMat);
    objects.push_back(secondHittableWall);
    // add background wall
    OBJ backgroundWall("./obj/bg_wall.obj");
    backgroundWall.translate(glm::vec3(0.0, 0.5, 0.5));
    backgroundWall.scale(10);
    Material *bgWallMat = new Material(Color(1.0, 1.0, 1.0), 0.1);
    HittableObj *bgHittableWall = new HittableObj(backgroundWall, bgWallMat);
    objects.push_back(bgHittableWall);
    
    OBJ frontalWall("./obj/bg_wall.obj");
    frontalWall.translate(glm::vec3(0.0, 0.5, -0.5));
    frontalWall.scale(10);
    HittableObj *fHittableWall = new HittableObj(frontalWall, bgWallMat);
    objects.push_back(fHittableWall);
}