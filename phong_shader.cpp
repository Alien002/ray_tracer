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
    //  = Ra * La + Rd * Ld * max(n . 1, 0) + Rs * Ls * max(v . r, 0)^a
    //Emitted_Light(const vec3& vector_to_light)
    vec3 Ia = color_ambient * world.ambient_intensity * world.ambient_color;
    //vec3 Id = {0,0,0};
    //vec3 Is = {0,0,0};
    
    
    //color = /Ra/ * Emitted_Light(this -> color_ambient) + /Rd/ * Emitted_Light(this -> color_diffuse) * max() + /Rs/ * Emitted_Light(this ->color_specular)
    color = Ia;// + Id + Is;
    
    return color;
}
