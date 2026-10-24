#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "vertex.h"

class Ray {
    public:
        point3 origin;
        point3 position;
        vec3 unit_direction;

        std::vector<Vertex> vertices;
        std::vector<Vertex> vertexHistory;
        std::vector<point3> positionHistory;

        float width = 0.005f;

        float speed = 1e-1;
        bool active = true;

        Ray(point3 orig, vec3 dir) 
            : origin{orig.x(), orig.y(), orig.z()},
            unit_direction{dir.x(), dir.y(), dir.z()} {
                // Set intial position to origin, and add to path
                position = origin;
                
            };

        void constructVertices();   // Constructs the vertices at the current position

        void update(float dt);      // Adds position history to history, clips history, updates position
};

#endif