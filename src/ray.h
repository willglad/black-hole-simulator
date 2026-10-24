#ifndef RAY_H
#define RAY_H

#include "include.h"

class Ray {
    public:
        point3 origin;
        point3 position;
        vec3 unit_direction;

        std::vector<Vertex> vertices;

        float width = 0.005f;

        float speed = 1e-1;
        bool active = true;

        int nPath = 15;             // Number of points to keep in path vector
        std::vector<point3> path;

        Ray(point3 orig, vec3 dir) 
            : origin{orig.x(), orig.y(), orig.z()},
            unit_direction{dir.x(), dir.y(), dir.z()} {
                // Set intial position to origin, and add to path
                position = origin;
                path.push_back(origin);
            };

        void constructVertices(){
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
        }

        void update(float dt){
            // Update position of ray
            position += unit_direction * speed * dt;
        }

};

#endif