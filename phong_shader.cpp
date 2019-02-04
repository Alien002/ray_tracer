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
    vec3 Ia = color_ambient * world.ambient_intensity * world.ambient_color;
    vec3 Id;
    //vec3 Is;
    
    Ray shadowray;
    Light *current;
    
    
    for(unsigned i = 0; i < world.lights.size(); ++i){
        current = world.lights.at(i);
        double dotA = dot(normal.normalized(), -(intersection_point - (current -> position)).normalized());
        double b = 0.0;
        if(dotA < b){           //max finder function
            b = 0.0;
        }
        else{
            b = dotA;
        }
        
        //shadowray.endpoint = intersection_point;
        //shadowray.direction = (current -> position-intersection_point).normalized();
        
        //if(world.Closest_Intersection(shadowray).object == nullptr || (current -> position - intersection_point < world.Closest_Intersection(shadowray).dist)){
        Id = color_diffuse * current -> Emitted_Light(intersection_point - current -> position) * b;
            //Is = color_specular *
        //}
    }
    
    
    //color = /Ra/ * Emitted_Light(this -> color_ambient) + /Rd/ * Emitted_Light(this -> color_diffuse) * max() + /Rs/ * Emitted_Light(this ->color_specular)
    color = Ia + Id;// + Is;
    
    return color;
}
