#pragma once

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <math.h>
#include "ray/ray.h"
#include "hittable/hittable.h"
#include "world.h"

const double maxDistance = 100.0;

Color ColorPixel(const Ray &ray, World &world, int reflections);
Hit CalcNearestHit(const Ray &ray, World &world);
Point randomInUnitSphere();
glm::vec3 randomUnitVector(const glm::vec3 &normal);
Color LambertianDiffuseComponent(const Hit &hit, World &world, int reflections);
Color SpecularComponent(const Hit &hit, World &world, int reflections);
Color ReflectedColor(const Hit &hit, World &world, int reflections);

Color ColorPixel(const Ray &ray, World &world, int reflections)
{
  if (reflections >= 5)
  {
    return Color(0.0, 0.0, 0.0);
  }

  Hit hit = CalcNearestHit(ray, world);
  if (hit.distance < maxDistance)
  {
    Color reflected = LambertianDiffuseComponent(hit, world, reflections);
    vector<Light *>::iterator light;
    for (const auto &light : world.lights) {
      Ray rayToLight = Ray(hit.point, light->point);
      Hit hitToLight = CalcNearestHit(rayToLight, world);
      if (hitToLight.distance == maxDistance)
      { // Direct Ilumination component: multiply by light energy and attenuate by distance^2 
        float dotProd = glm::dot(rayToLight.dir, hit.normal);
        if (dotProd > 0.0)
        {
          float dist = glm::length(light->point - hit.point);
          //  L = Pd * J * dot(N, Li) / (Pi * r^2)
          reflected += hit.material->color * light->energy * dotProd / (dist * dist);
        }
      }
    }
    return reflected;
  }

  return Color(0.0, 0.0, 0.0);
}

Hit CalcNearestHit(const Ray &ray, World &world)
{
  Hit hit;
  Hit nearestHit;
  nearestHit.distance = maxDistance;
  std::vector<Hittable *>::iterator hitObj;
  for (const auto &hitObj : world.objects)
  {
    if (hitObj->IsHitByRay(ray, maxDistance, hit))
    {
      if (hit.distance < nearestHit.distance)
      {
        nearestHit = hit;
      }
    }
  }
  return nearestHit;
}

/**
 * Returns a point in the unitary sphere
 */
Point randomInUnitSphere()
{
  Point randomPoint = glm::vec3(RandomDouble(2.0), RandomDouble(2.0), RandomDouble(2.0));
  if (glm::length(randomPoint) > 1.0)
  {
    return randomInUnitSphere();
  }
  return glm::normalize(randomPoint);
}

glm::vec3 randomUnitVector(const glm::vec3 &normal)
{
  Point unitVector = randomInUnitSphere();
  if (dot(unitVector, normal) > 0.0)
  {
    return unitVector;
  }
  else
  {
    return -unitVector;
  }
}

/**
 * Calculates the reflected color from random direction
 */
Color LambertianDiffuseComponent(const Hit &hit, World &world, int reflections)
{
  Point target = hit.point + randomUnitVector(hit.normal);
  Ray reflectionRay = Ray(hit.point, target);
  Color reflectedLight = ColorPixel(reflectionRay, world, reflections + 1); // / float(2 * M_PI)
  float angleAttenuation = glm::dot(reflectionRay.dir, hit.normal);
  return angleAttenuation * reflectedLight * hit.material->color;   // * float(2 * M_PI)
}

/**
 * Calculates the specular component
*/
Color SpecularComponent(const Hit &hit, World &world, int reflections)
{
  Ray reflectionRay = Ray(hit.point, hit.reflection);
  return hit.material->reflectance * ColorPixel(reflectionRay, world, reflections + 1);
}

Color ReflectedColor(const Hit &hit, World &world, int reflections)
{
  float randomNum = rand() / (RAND_MAX + 1.0);
  if (randomNum > hit.material->reflectance)
  {
    return LambertianDiffuseComponent(hit, world, reflections);
  }
  else
  {
    return SpecularComponent(hit, world, reflections);
  }
}
