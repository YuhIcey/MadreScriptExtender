#pragma once

#include <cstdint>

// Simple macro for patching memory
#define HOOK_JMP(src, dest, len) HookUtils::PatchJmp((uintptr_t)(src), (uintptr_t)(dest), len)

namespace HookUtils
{
    void PatchMemory(uintptr_t address, const void* data, size_t size);
    void PatchJmp(uintptr_t src, uintptr_t dst, size_t len);
    void NopBytes(uintptr_t address, size_t length);

    // Optional utility: signature scanning
    uintptr_t FindPattern(const char* module, const char* pattern, const char* mask);
}
