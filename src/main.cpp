#include <iostream>
#include <sstream>
#include <fstream>

#include "include.h"

int main() {
   
    Engine engine;

    if (!engine.init()){
        return -1;
    }

    Circle c0({-0.25f, 0.25f, 0.0f}, 0.25f);
    c0.constructVertices(50);
    engine.addCircle(c0);

    Circle c1({0.25f, -0.25f, 0.0f}, 0.25f);
    c1.constructVertices(50);
    engine.addCircle(c1);

    std::cout << engine.aspectRatio << std::endl;

    if (!engine.buffers()){
        return -1;
    }

    engine.run();

    engine.cleanup();

    return 0;

}