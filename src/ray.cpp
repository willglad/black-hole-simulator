#include "ray.h"
#include "vertex.h"
#include "circle.h"

void Ray::update(Circle& bh, float dt){
    // Calculate the change in position 
    float dtSim = dt;

    // Update the current position based on Schwarzchild BH solution in 2D
    position = langrangianDynamics(dtSim);

    // Add new position to history
    recordHistory();
};

void Ray::recordHistory(){
    // Add previous position to history
    positionHistory.push_back(position);
    velocityHistory.push_back(velocity);

    // If positionHistory is greater than drawLength, then
    if (positionHistory.size() > drawLength){
        positionHistory.erase(positionHistory.begin(),
                             positionHistory.begin()+(positionHistory.size() - drawLength));
    }
    if (velocityHistory.size() > drawLength){
        velocityHistory.erase(velocityHistory.begin(),
                            velocityHistory.begin() + (velocityHistory.size() - drawLength));
    }

};

vec3 Ray::newtonianDynamics(Circle& bh){
    // Calculated change to position based on gravitational acceleration
    vec3 r = position - vec3(bh.cX, bh.cY, bh.cZ);
    return -0.5f / r.length_squared() * unit_vector(r);
};

point3 Ray::langrangianDynamics(float timestep){
    double& b = photonState.b;
    double& u = photonState.u;
    double& phi = photonState.phi;
    double& rho = photonState.rho;
    double rho_squared = rho * rho;

    double du = b*b * ( 1.0f / ( rho*rho_squared ) - 3.0f / (2.0f * rho_squared * rho_squared) ) * timestep;
    double drho = u * timestep;
    double dphi = b / rho_squared * timestep;

    u += du;
    rho += drho;
    phi += dphi;

    // Return cartesian position based on new coords
    return point3(rho * std::cos(phi), rho * std::sin(phi), 0.0f);
}