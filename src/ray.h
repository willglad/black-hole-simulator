#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "vertex.h"
#include "circle.h"

class Ray {
    public:
        point3 origin;
        point3 position;
        vec3 velocity;
        vec3 acceleration;

        std::vector<Vertex> vertices;
        std::vector<Vertex> vertexHistory;
        std::vector<point3> positionHistory;

        float perpWidth = 0.0025f;
        float parallelWidth = 0.005f;
        float drawLength = 250;

        float alpha_min = 0.1f;
        float alpha_max = 1.0f;

        float speed = 0.1f;
        bool active = true;

        Ray(point3 orig, vec3 dir, float speed) 
            : origin{orig.x(), orig.y(), orig.z()},
            velocity{dir.x()*speed, dir.y()*speed, dir.z()*speed},
            speed{speed} {
                // Set intial position to origin
                position = origin;         
            };

        void constructVertices();   // Constructs the vertices at the current position

        void update(Circle& bh, float dt);      // Calls all ray updates

        void recordHistory();       // Records position and vertex history

        vec3 newtonianDynamics(Circle& bh);
};

#endif