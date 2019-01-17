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
    int min_t = std::numeric_limits.max();
    Hit closest_hit.dist = min_t;                                       //set closest_hit to largest value at first.
    Hit temp;
    for(int i = 0; i < objects.size(); ++i){                            //loop for each object
        temp = objects.at(i)->Intersection(ray, -1);
        if(temp.dist < closest_hit.dist && temp.dist > small_t){        //if intersect & temp.dist < small_t
            closest_hit = temp;                                         //closest obj = obj
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
    vec3 color;
    Hit closest_intersect = Closest_Intersection(ray);
    
    if(Closest_Intersection(ray)){
        color = Shade_Surface(ray, intersection_point, Normal( , ), recursion_depth);
    }// determine the color here
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
