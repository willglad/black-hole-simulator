#include "include.h"
#include "circle.h"
#include "ray.h"
#include "vec3.h"
#include "engine.h"

int main() {
   
    Engine engine;

    if (!engine.init()){
        return -1;
    }

    Circle c0({0.0f, 0.0f, 0.0f}, 0.1f);
    c0.constructVertices(50);
    c0.mass = 1e11;
    engine.addCircle(c0);

    Ray r0({0.0f, 0.4f, 0.0f},{1.0f, 0.0f, 0.0f}, 4.0f);
    engine.submitRay(r0);   

    std::cout << engine.aspectRatio << std::endl;

    engine.run();

    engine.cleanup();

    return 0;

}