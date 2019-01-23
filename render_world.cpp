#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    //TODO;
    std::cout<<"Closest_Intersection called!!!!!!" <<std::endl;

    int min_t = std::numeric_limits<int>::max();
    
    Hit closest_hit;
    Hit temp;
    
    closest_hit.dist = min_t;                                       //set closest_hit to largest value at first.
    
    
    for(unsigned i = 0; i < objects.size(); ++i){                            //loop for each object
        std::cout<<"Closest_Intersection for called!!!!!!" <<std::endl;

        temp = objects.at(i)->Intersection(ray, -1);
        if(temp.dist < closest_hit.dist && temp.dist > small_t){        //if intersect & temp.dist < small_t
            closest_hit.dist = temp.dist;
            closest_hit.object = temp.object;
            closest_hit.part = temp.part;                       //closest obj = obj
        }
    }
    return closest_hit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)  //
{
    //TODO; // set up the initial view ray here
    vec3 end_point = camera.position;
    vec3 direction = (end_point - camera.World_Position(pixel_index)).normalized();
    Ray ray;
    
    ray.endpoint = end_point;
    ray.direction = direction;  //sets ray direction
    
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    std::cout<<"Cast_Ray called!!!!!!" <<std::endl;
    
    vec3 color;
    
    vec3 background;                                    //placeholder vector
    
    Hit closest_intersect = this -> Closest_Intersection(ray);

    vec3 intersection_point = ray.Point(closest_intersect.dist);
    
    
    std::cout<<"Cast_Ray before normal called!!!!!!" <<std::endl;

    vec3 normal = closest_intersect.object -> Normal(intersection_point, -1);           //seg faults here

    std::cout<<"Cast_Ray after normal called!!!!!!" <<std::endl;

    
    if(closest_intersect.dist > 0){
      //  std::cout<<"Cast_Ray if called!!!!!!" <<std::endl;
        std::cout<<"if before color called!!!!!!" <<std::endl;

        color = closest_intersect.object -> material_shader -> Shade_Surface(ray, intersection_point, normal, recursion_depth);
        
        std::cout<<"if after color called!!!!!!" <<std::endl;

    }// determine the color here
    else{
        //background shader
        //std::cout<<"Cast_Ray else called!!!!!!" <<std::endl;
        std::cout<<"else before color called!!!!!!" <<std::endl;

        this -> background_shader -> Shade_Surface(ray, background, background, recursion_depth);
        
        std::cout<<"else after color called!!!!!!" <<std::endl;

        //color = closest_intersect.object -> material_shader -> background_shader;
        //background shader???
    }
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    //TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
