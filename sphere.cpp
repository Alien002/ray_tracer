#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    TODO;
    //(p-c) . (p-c) - R^2 = 0;
    if(dot(ray.point(part)-sphere.center,ray.point(part)-sphere.center) - pow(sphere.radius,2) == 0){
        //FIXME
    }
    return {0,0,0};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    
    
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
