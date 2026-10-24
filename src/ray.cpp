#include "ray.h"
#include "vertex.h"

void Ray::constructVertices(){
        // Clear vertices
        vertices.clear();

        // Draw a thin retangle aligned with the unit direction
        float nwidth = 0.005f;
        float mwidth = 0.0025f;

        // Vertex coordinates in ray frame
        float x_left = - nwidth;
        float x_right = nwidth;
        float y_bottom = - mwidth;
        float y_top = mwidth;

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

void Ray::update(float dt){
    // Add previous position to history
    positionHistory.push_back(position);
    vertexHistory.insert(vertexHistory.end(), vertices.begin(), vertices.end());

    // If the vertexHistory is greater than 14 * 6, then 
    if (vertexHistory.size() > 1000 * 6){
        vertexHistory.erase(vertexHistory.begin(), vertexHistory.begin() + 6);
    }

    // Update position of ray
    position += unit_direction * speed * dt;
};
