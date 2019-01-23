#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    
    //int t = part;
    
    
    Hit hit;
    vec3 vec = ray.endpoint - this -> center;            //E - C
    vec3 u = ray.direction;
    
    
    double a = dot(u,u);                                  //a = (E - C)(E - C)
    double b = 2 * dot(vec, u);                           //b = 2(E - C)u
    double c = dot(vec,vec) - pow(this -> radius,2);       //c = (X - C)(X - C) - r^2
    
    
    double det = pow(b,2)-4*a*c;
    double t1,t2;
    
    
    if(det > 0){
        t1 = (-b + sqrt(det)) / (2*a);
        t2 = (-b - sqrt(det)) / (2*a);
        
        if(t1 >= small_t){                                  //t1 >= small_t registered as hit
            hit.dist = t1;
            hit.object = this;
            hit.part = part;

        }
        else if(t2 >= small_t){                             //t2 registered as hit
            hit.dist = t2;
            hit.object = this;
            hit.part = part;
        }
        else{
            hit.dist = 0;
            hit.object = 0;
            hit.part = 0;
        }
    }
    else if(det == 0){
        t1 = -b / (2*a);
        t2 = 0;
        
        if(t1 >= small_t){
            hit.dist = t1;
            hit.object = this;
            hit.part = part;
        }
        else{
            hit.dist = 0;
            hit.object = 0;
            hit.part = 0;
        }
    }
    else{       //det < 0
        hit.dist = 0;
        //do nothing, no hit
    }
    
    return hit;
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
