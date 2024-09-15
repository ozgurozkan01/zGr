#include "engine/include/engine.h"
#include <exception>
#include <iostream>

int main()
{
    zgr::engine engine;

    try
    {
        std::cout << "Engine is started!!\n";
        engine.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Engine throws error during start : " << e.what() << std::endl;
        EXIT_FAILURE;
    }

    std::cout << "Engine shut down!!\n";

    EXIT_SUCCESS;
}
