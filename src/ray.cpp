#include "ray.h"
#include "vertex.h"
#include "circle.h"

float G = 6.67e-11;

void Ray::constructVertices(){
        // Clear vertices
        vertices.clear();

        // Draw a thin retangle aligned with the unit direction
        // Vertex coordinates in ray frame
        float x_left = - parallelWidth;
        float x_right = parallelWidth;
        float y_bottom = - perpWidth;
        float y_top = perpWidth;

        // Draw both triangles
        Vertex A = {x_left, y_bottom, 0.0f};
        Vertex B = {x_left, y_top, 0.0f};
        Vertex C = {x_right, y_top, 0.0f};
        Vertex D = {x_right, y_bottom, 0.0f};

        // Rotate each vertex by R(theta)
        A.rotateFrame(*this);
        B.rotateFrame(*this);
        C.rotateFrame(*this);
        D.rotateFrame(*this);

        // Add the position
        A += position;
        B += position;
        C += position;
        D += position;

        vertices.push_back(A);
        vertices.push_back(B);
        vertices.push_back(D);
        vertices.push_back(B);
        vertices.push_back(C);
        vertices.push_back(D);
        return;
};

void Ray::update(Circle& bh, float dt){
    // Calculate the change in position 
    acceleration = newtonianDynamics(bh);
    velocity += acceleration * dt;
    position += velocity * dt; 

    constructVertices();

    // Add new position to history
    recordHistory();
};

void Ray::recordHistory(){
    // Add previous position to history
    positionHistory.push_back(position);
    vertexHistory.insert(vertexHistory.end(), vertices.begin(), vertices.end());

    // If the vertexHistory is greater than 14 * 6, then 
    if (vertexHistory.size() > drawLength * 6){
        vertexHistory.erase(vertexHistory.begin(), vertexHistory.begin() + 6);
    }
};

vec3 Ray::newtonianDynamics(Circle& bh){
    // Calculated change to position based on gravitational acceleration
    vec3 r = position - vec3(bh.cX, bh.cY, bh.cZ);
    return -G * bh.mass / r.length_squared() * unit_vector(r);
};