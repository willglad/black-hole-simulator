#ifndef VERTEX_H
#define VERTEX_H

class Ray;

struct Vertex{
    float x;
    float y;
    float z;

    void rotateFrame(const Ray& ray);

    void operator+=(const vec3& v);
};

#endif