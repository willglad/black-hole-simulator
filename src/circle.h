#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>

#include "vertex.h"
#include "constants.h"

class Circle {
    public:
        Circle(Vertex centre, double mass) : cX{centre.x}, cY{centre.y}, cZ{centre.z}, r_s{2*G*mass / (c * c)} {
            // Normalise to dimensionless -- r_s
            cX /= r_s;
            cY /= r_s;
            cZ /= r_s;
        };

        float cX        = 0.0f;
        float cY        = 0.0f;
        float cZ        = 0.0f;

        double r_s;
        double mass;

        std::vector<Vertex> verticesFilled;
        std::vector<Vertex> verticesCircumference;

        std::vector<Vertex> constructVertices(int nsegments) {
            // Returns a vector of vertices in x y z strides for npts vertices around the circle
            Vertex centre = {cX, cY, cZ};
            float theta_total = 0.0f;
            float dtheta = 2 * M_PI / float(nsegments);
            for (int i = 0; i < nsegments * 2; i++){
                // Add centre
                verticesFilled.push_back(centre);

                // First point in segment
                verticesFilled.push_back({
                    cX + std::sin(theta_total),
                    cY + std::cos(theta_total),
                    0.0f
                });

                // Second point in segment
                verticesFilled.push_back({
                    cX + std::sin(theta_total + dtheta),
                    cY + std::cos(theta_total + dtheta),
                    0.0f
                });

                theta_total += dtheta;
            }
            return verticesFilled;
        }

        std::vector<Vertex> constructCircumference(int npts) {
            // Returns a vector of vertices in x y z -- draws a circumference
            float theta_total = 0.0f;
            float dtheta = 2 * M_PI / float(npts);
            for (int i = 0; i < npts + 1; i++){
                // Add single point
                verticesCircumference.push_back({
                    cX + std::sin(theta_total),
                    cY + std::cos(theta_total),
                    0.0f,
                });
                theta_total += dtheta;
            }
            return verticesCircumference;
        }

};


#endif
