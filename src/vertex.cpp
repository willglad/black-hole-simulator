#include "vertex.h"
#include "vec3.h"
#include "ray.h"

void Vertex::rotateFrame(const Ray& ray){
    // Trasform from the ray frame into comp frame
    vec3 u = ray.unit_direction;

    float cos_theta = u.x();
    float sin_theta = u.y();

    float oldx = x;
    float oldy = y;

    x = cos_theta * oldx - sin_theta * oldy;
    y = sin_theta * oldx + cos_theta * oldy;

};

void Vertex::operator+=(const vec3& v){
            x += v.e[0];
            y += v.e[1];
            z += v.e[2];
            return;
};
