#include "../../engine/include/engine.h"
#include <exception>
#include <iostream>

int main()
{
    zgr::engine engine;

    try
    {
        engine.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        EXIT_FAILURE;
    }

    EXIT_SUCCESS;
}
