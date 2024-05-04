#include <iostream>
#include <array>
#include <functional>

#include "Config.h"

/// @brief program entry point
/// @return code of execution result
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        // report version
        std::cout << argv[0] << " Version " << OptLib_VERSION_MAJOR << "."
                  << OptLib_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
    }

    return 0;
}