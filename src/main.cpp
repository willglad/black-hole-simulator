#include <iostream>
#include <sstream>
#include <fstream>

#include "include.h"

int main() {
   
    Engine engine;

    if (!engine.init()){
        return -1;
    }

    engine.run();

    engine.cleanup();

    return 0;

}