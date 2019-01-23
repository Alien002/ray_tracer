#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    //TODO;
    //int t = part;
    
    //x1, normal
    
    //std::cout<<"plane intersect called!!!!!!" <<std::endl;

    
    Hit hit;
    vec3 vec = this -> x1 - ray.endpoint;            //Q-E
    vec3 u = ray.direction;
    
    
    double t = dot(vec,this -> normal)/ dot(u,this -> normal);
    
    
    if(dot(vec,this -> normal) != 0){
        if (t > 0){
            return {this, t, part};
        }
        else{
            return {nullptr, 0, part};
        }
    }
    
    return {nullptr, 0, part};
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    //std::cout<<"Normal if called!!!!!!" <<std::endl;

    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
