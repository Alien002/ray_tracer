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
    //std::cout<<"Closest_Intersection called!!!!!!" <<std::endl;

    double min_t = std::numeric_limits<double>::max();
    
    Hit closest_hit = {nullptr, 0, 0};
    //Hit temp;
    
    //closest_hit.dist = min_t;                                       //set closest_hit to largest value at first.
    
    
    for(unsigned i = 0; i < objects.size(); ++i){                            //loop for each object
      //  std::cout<<"Closest_Intersection for called!!!!!!" <<std::endl;

        Hit temp = objects.at(i)->Intersection(ray, -1);
        if(temp.object && temp.dist < min_t && temp.dist > small_t){        //if intersect & temp.dist < small_t
            closest_hit = temp;
            min_t = closest_hit.dist;
        }
    }
    return closest_hit;
 
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)  //
{
    //TODO; // set up the initial view ray here
    Ray ray;
    
    ray.endpoint = camera.position;
    ray.direction = (camera.World_Position(pixel_index) - ray.endpoint).normalized();  //sets ray direction
    
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
    
    vec3 background;//placeholder vector
    
    vec3 normal;
    
    Ray temp;
    
    Hit closest_intersect = this -> Closest_Intersection(ray);

    vec3 intersection_point;
    
    
    if(closest_intersect.object != nullptr && recursion_depth <= recursion_depth_limit){
        intersection_point = ray.Point(closest_intersect.dist);
        normal = closest_intersect.object -> Normal(intersection_point, closest_intersect.part);

        color = closest_intersect.object -> material_shader -> Shade_Surface(ray, intersection_point, normal, recursion_depth);
        

    }// determine the color here
    else{
        //background shader

        color = background_shader -> Shade_Surface(ray, ray.direction, ray.direction, recursion_depth);
        

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
