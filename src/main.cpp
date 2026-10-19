#include "include.h"
#include "ray.h"
#include "vec3.h"

int main() {
   
    Engine engine;

    if (!engine.init()){
        return -1;
    }

    Circle c0({0.0f, 0.0f, 0.0f}, 0.1f);
    c0.constructVertices(50);
    engine.addCircle(c0);

    Ray r0({-0.9f, 0.4f, 0.0f},{1.0f, 0.0f, 0.0f});
    r0.constructVertices();
    engine.submitRay(r0);   

    Ray r1({-0.9f, 0.2f, 0.0f},unit_vector({0.5f, -0.5f, 0.0f}));
    r1.constructVertices();
    engine.submitRay(r1);
    
    std::cout << engine.aspectRatio << std::endl;

    engine.run();

    engine.cleanup();

    return 0;

}