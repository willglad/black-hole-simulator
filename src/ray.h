#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "vertex.h"
#include "circle.h"

struct PhotonState{
    double u;
    double phi;
    double rho;
    double b;
};

class Ray {
    public:
        point3 origin;          // Given in dimensionless coords -- 1/r_s
        point3 position;        // Given in dimensionless coords -- 1/r_s
        vec3 velocity;          // Given in dimensionless coords -- 1/c
        vec3 acceleration;      // Given in dimensionless coords -- 1/r_s * c**2

        std::vector<point3> positionHistory;
        std::vector<vec3> velocityHistory;

        float drawLength = 250;

        float alpha_min = 0.1f;
        float alpha_max = 1.0f;

        PhotonState photonState{};

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

                // Set impact parameter
                photonState.b = cross(origin, velocity).length();
                photonState.rho = position.length();
                photonState.phi = std::atan2(origin.y(), origin.x());
                photonState.u = - std::sqrt(1 - (1 - (1 / photonState.rho)) * 
                            photonState.b*photonState.b / (photonState.rho * photonState.rho));
            };

        void update(Circle& bh, float dt);      // Calls all ray updates

        void recordHistory();       // Records position and vertex history

        vec3 newtonianDynamics(Circle& bh);

        point3 langrangianDynamics(Circle& bh, float timestep);
};

inline std::ostream& operator<<(std::ostream& out, const std::vector<point3> v){
    for (auto& i : v){
        out << i;
    }
    return out;
}

#endif