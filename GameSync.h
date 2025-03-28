#pragma once

#include <string>

namespace MadreSync
{
    void Init();
    void Shutdown();

    void Update();  // Called every tick or frame
    void SyncPlayerPosition(float x, float y, float z, float rot);
    void HandleRemotePlayerSync(const std::string& id, float x, float y, float z, float rot);
}
