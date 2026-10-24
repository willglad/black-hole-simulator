#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>

#include "vertex.h"

class Circle {
    public:
        Circle(Vertex centre, float radius){
            cX = centre.x;
            cY = centre.y;
            cZ = centre.z;
            r = radius;
        }

        float r         = 1e4;
        float cX        = 0.0f;
        float cY        = 0.0f;
        float cZ        = 0.0f;
        
        float mass = 1e8;

        std::vector<Vertex> vertices;

        std::vector<Vertex> constructVertices(int nsegments) {
            // Returns a vector of vertices in x y z strides for npts vertices around the circle
            Vertex centre = {cX, cY, cZ};

            float theta_total = 0.0f;
            float dtheta = 2 * M_PI / float(nsegments);
            for (int i = 0; i < nsegments * 2; i++){
                // Add centre
                vertices.push_back(centre);

                // First point in segment
                vertices.push_back({
                    cX + r * std::sin(theta_total),
                    cY + r * std::cos(theta_total),
                    0.0f
                });

                // Second point in segment
                vertices.push_back({
                    cX + r * std::sin(theta_total + dtheta),
                    cY + r * std::cos(theta_total + dtheta),
                    0.0f
                });

                theta_total += dtheta;
            }
            return vertices;
        }

};

#endif
