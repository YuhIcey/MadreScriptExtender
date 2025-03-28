#include "pch.h"
#include "HookUtils.h"
#include <windows.h>
#include <psapi.h>

namespace HookUtils
{
    void PatchMemory(uintptr_t address, const void* data, size_t size)
    {
        DWORD oldProtect;
        VirtualProtect(reinterpret_cast<void*>(address), size, PAGE_EXECUTE_READWRITE, &oldProtect);
        memcpy(reinterpret_cast<void*>(address), data, size);
        VirtualProtect(reinterpret_cast<void*>(address), size, oldProtect, &oldProtect);
    }

    void PatchJmp(uintptr_t src, uintptr_t dst, size_t len)
    {
        if (len < 5) return;

        DWORD oldProtect;
        VirtualProtect(reinterpret_cast<void*>(src), len, PAGE_EXECUTE_READWRITE, &oldProtect);

        *(uint8_t*)src = 0xE9; // JMP opcode
        *(uint32_t*)(src + 1) = (uint32_t)(dst - src - 5);

        for (size_t i = 5; i < len; ++i)
            *(uint8_t*)(src + i) = 0x90; // NOP

        VirtualProtect(reinterpret_cast<void*>(src), len, oldProtect, &oldProtect);
    }

    void NopBytes(uintptr_t address, size_t length)
    {
        DWORD oldProtect;
        VirtualProtect(reinterpret_cast<void*>(address), length, PAGE_EXECUTE_READWRITE, &oldProtect);
        memset(reinterpret_cast<void*>(address), 0x90, length);
        VirtualProtect(reinterpret_cast<void*>(address), length, oldProtect, &oldProtect);
    }

    uintptr_t FindPattern(const char* module, const char* pattern, const char* mask)
    {
        MODULEINFO mInfo = {};
        HMODULE hModule = GetModuleHandleA(module);
        if (!hModule) return 0;

        GetModuleInformation(GetCurrentProcess(), hModule, &mInfo, sizeof(MODULEINFO));

        uintptr_t base = reinterpret_cast<uintptr_t>(mInfo.lpBaseOfDll);
        size_t size = mInfo.SizeOfImage;

        for (size_t i = 0; i < size; ++i)
        {
            bool found = true;
            for (size_t j = 0; mask[j]; ++j)
            {
                if (mask[j] != '?' && pattern[j] != *(char*)(base + i + j))
                {
                    found = false;
                    break;
                }
            }

            if (found) return base + i;
        }

        return 0;
    }
}
