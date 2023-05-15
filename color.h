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
    Color reflected = ReflectedColor(hit, world, reflections);
    Ray rayToLight = Ray(hit.point, world.light);
    Hit hitToLight = CalcNearestHit(rayToLight, world);
    if (hitToLight.distance == maxDistance)
    { // Direct Ilumination component: multiply by light energy and attenuate by distance^2 
      float dotProd = glm::dot(rayToLight.dir, hit.normal);
      if (dotProd > 0.0)
      {
        float dist = glm::length(world.light - hit.point);
        //  L = Pd * J * dot(N, Li) / (Pi * r^2)
        return reflected + dotProd * world.lightEnergy * hit.material->color / (dist * dist);
      }
    }
    return reflected;
  }

  float t = 0.5 * (ray.dir.y + 1.0);
  return float(1.0 - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
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
  Color reflectedColor = float(0.3) * ColorPixel(reflectionRay, world, reflections + 1);
  return (reflectedColor + hit.material->color) / float(2.0);
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
