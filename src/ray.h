#ifndef RAY_H
#define RAY_H

#include "include.h"

class Ray {
    public:
        point3 origin;
        point3 position;
        vec3 unit_direction;

        std::vector<Vertex> vertices;

        float width = 0.05f;

        float speed;
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
            // Get the vertices for a square at the current location
            float x_left = position.x() - width / 2.0f;
            float x_right = position.x() + width / 2.0f;
            float y_top = position.y() + width / 2.0f;
            float y_bottom = position.y() - width / 2.0f;

            // Draw both triangles
            Vertex A = {x_left, y_bottom, 0.0f};
            Vertex B = {x_left, y_top, 0.0f};
            Vertex C = {x_right, y_top, 0.0f};
            Vertex D = {x_right, y_bottom, 0.0f};

            vertices.push_back(A);
            vertices.push_back(B);
            vertices.push_back(D);
            vertices.push_back(B);
            vertices.push_back(C);
            vertices.push_back(D);
            return;
        } 

};

#endif