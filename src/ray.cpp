#include "ray.h"
#include "vertex.h"
#include "circle.h"

void Ray::update(Circle& bh, float dt){
    // Calculate the change in position 
    float dtSim = dt;

    acceleration = newtonianDynamics(bh);
    velocity += acceleration * dtSim;
    position += velocity * dtSim; 

    // Add new position to history
    recordHistory();
};

void Ray::recordHistory(){
    // Add previous position to history
    positionHistory.push_back(position);

    // If positionHistory is greater than drawLength, then
    if (positionHistory.size() > drawLength){
        positionHistory.erase(positionHistory.begin(),
                             positionHistory.begin()+(positionHistory.size() - drawLength));
    }
};

vec3 Ray::newtonianDynamics(Circle& bh){
    // Calculated change to position based on gravitational acceleration
    vec3 r = position - vec3(bh.cX, bh.cY, bh.cZ);
    return -0.5f / r.length_squared() * unit_vector(r);
};