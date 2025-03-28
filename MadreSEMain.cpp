#include "MadreSEMain.h"
#include "Hooks.h"
#include "Networking.h"
#include "PlayerProxy.h"
#include "ChatSystem.h"
#include "GameSync.h"
#include <windows.h>
#include <iostream>

bool g_isConnected = false;

extern "C" __declspec(dllexport) BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitMadreScriptExtender, nullptr, 0, nullptr);
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

void InitMadreScriptExtender()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    std::cout << "[MSE] Madre Script Extender loaded\n";

    HookGame();
    MadreNetworking::Init();
    MadreChat::Init();
    MadreProxy::Init();
    MadreSync::Init();

    g_isConnected = true;
}
