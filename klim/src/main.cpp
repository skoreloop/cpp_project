#include "window/window.hpp"
#include <iostream>

int main()
{
    std::cout << "Program started" << std::endl;
    window::run();
    std::cout << "Program finished" << std::endl;
    return 0;
}