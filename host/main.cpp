#include "controller.hpp"
#include <iostream>


int main(int argc, char *argv[])
{
    Controller controller;

    if (!controller.open())
    {
        std::cerr << "error: unable to open controller" << std::endl;
    }

    controller.run();

    controller.close();

    return 0;
}
