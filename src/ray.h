#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "vertex.h"
#include "circle.h"

class Ray {
    public:
        point3 origin;          // Given in dimensionless coords -- 1/r_s
        point3 position;        // Given in dimensionless coords -- 1/r_s
        vec3 velocity;          // Given in dimensionless coords -- 1/c
        vec3 acceleration;      // Given in dimensionless coords -- 1/r_s * c**2

        std::vector<point3> positionHistory;

        float drawLength = 250;

        float alpha_min = 0.1f;
        float alpha_max = 1.0f;

        float speed = 0.1f;
        float r_s;
        bool active = true;

        Ray(point3 orig, vec3 dir, float r_s) 
            : origin{orig.x()/r_s, orig.y()/r_s, orig.z()/r_s},
            velocity{dir.x(), dir.y(), dir.z()},
            speed{c},
            r_s{r_s} {
                // Set intial position to origin
                position = origin;

                std::cout << position << " -- " << velocity << '\n';
            };

        void update(Circle& bh, float dt);      // Calls all ray updates

        void recordHistory();       // Records position and vertex history

        vec3 newtonianDynamics(Circle& bh);
};

inline std::ostream& operator<<(std::ostream& out, const std::vector<point3> v){
    for (auto& i : v){
        out << i;
    }
    return out;
}

#endif