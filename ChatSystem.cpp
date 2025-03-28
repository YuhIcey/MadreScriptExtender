#include "ChatSystem.h"
#include <iostream>

namespace MadreChat
{
    void Init()
    {
        std::cout << "[ChatSystem] Initialized\n";
    }

    void Shutdown()
    {
        std::cout << "[ChatSystem] Shutdown\n";
    }
}
