#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    //TODO; //determine the color
    
    /*Render_World& world_input,
    const vec3& color_ambient,
    const vec3& color_diffuse,
    const vec3& color_specular,
    double specular_power)
    /*/
    //I = Ia + Id + Is
    //  = (Ra * La) + (Rd * Ld * max(n . l, 0)) + (Rs * Ls * max(v . r, 0)^a)
    //Emitted_Light(const vec3& vector_to_light)
    
    vec3 Ia = Ia + color_ambient * world.ambient_intensity * world.ambient_color;
    vec3 Id;
    vec3 Is;
    
    vec3 shadowRay;
    vec3 viewRay;
    vec3 reflectRay;
    
    Light* current;
    Ray shadowRay_ray;
    
    Hit intersect;
    
    for(unsigned i = 0; i < world.lights.size(); ++i){
        current = world.lights.at(i);
        
        shadowRay = current -> position - intersection_point;
        shadowRay_ray.endpoint = intersection_point;
        shadowRay_ray.direction = (current -> position - intersection_point).normalized();
       
        viewRay = ray.endpoint - intersection_point;
        
        reflectRay = 2 * dot(shadowRay, normal) * normal - shadowRay;
        
        intersect = world.Closest_Intersection(shadowRay_ray);
        
        double diffMax = std::max(dot(normal.normalized(), -(intersection_point - (current -> position)).normalized()),0.0);
        
        vec3 L = current -> position - intersection_point;
        
        double specMax = pow(std::max(dot((intersection_point - ray.endpoint).normalized(), (L - 2 * dot(L,normal) * normal).normalized() ), 0.0), specular_power);
        
        //shadowray.endpoint = intersection_point;
        //shadowray.direction = (current -> position-intersection_point).normalized();
        
        //if(world.Closest_Intersection(shadowray).object == nullptr || (current -> position - intersection_point < world.Closest_Intersection(shadowray).dist)){
        if(!world.enable_shadows || (world.enable_shadows && (!intersect.object || intersect.dist >= shadowRay.magnitude()))){
            
            Id = Id + color_diffuse * current -> Emitted_Light(intersection_point - current -> position) * diffMax;
            Is = Is + color_specular * current -> Emitted_Light(intersection_point - current -> position) * specMax;//RsLsmax(v.r,0)^a
        }
    }
    
    //color ;
    
    return color = Ia + Id + Is;
}
