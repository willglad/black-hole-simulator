#include "include.h"
#include "circle.h"
#include "ray.h"
#include "vec3.h"
#include "engine.h"
#include "constants.h"

int main() {
   
    Engine engine;

    if (!engine.init()){
        return -1;
    }

    float mass_BH = 100 * solarMass;
    Circle c0({0.0f, 0.0f, 0.0f}, mass_BH);
    c0.constructCircumference(50);
    engine.submitCircle(c0);

    Ray r1({0.0f, c0.r_s * 0.75, 0.0f},{1.0f, 0.0f, 0.0f}, c0.r_s);
    engine.submitRay(r1);   

    engine.run();

    engine.cleanup();

    return 0;

}