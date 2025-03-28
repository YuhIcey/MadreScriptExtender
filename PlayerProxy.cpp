#include "PlayerProxy.h"
#include <iostream>

namespace MadreProxy
{
    void Init()
    {
        std::cout << "[PlayerProxy] Initialized\n";
    }

    void Shutdown()
    {
        std::cout << "[PlayerProxy] Shutdown\n";
    }
}
