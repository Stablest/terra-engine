#include <iostream>
#include "core/engine/engine.hpp"

// TODO -> Get correct parameters of engine initialization
int main() {
    try {
        Engine engine { 800, 600, "Terra engine"};
    } catch (std::runtime_error& error) {
        // TODO -> Handle exceptions
        std::cerr << error.what() << std::endl;
        std::exit(0);
    }
    return 0;
}