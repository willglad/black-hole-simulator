#include <iostream>
#include <sstream>
#include <fstream>

#include "include.h"

int main() {
   
    Engine engine;

    if (!engine.init()){
        return -1;
    }

    float v1[] = {-0.5f, -0.5f, 0.0f};
    float v2[] = {0.5f, -0.5f, 0.0f};
    float v3[] = {0.0f, 0.5f, 0.0f};
    engine.addVertex(v1[0], v1[1], v1[2]);
    engine.addVertex(v2[0], v2[1], v2[2]);
    engine.addVertex(v3[0], v3[1], v3[2]);

    if (!engine.buffers()){
        return -1;
    }

    engine.run();

    engine.cleanup();

    return 0;

}