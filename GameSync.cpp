#include "GameSync.h"
#include "Networking.h"
#include <iostream>
#include <unordered_map>

struct RemotePlayerState
{
    float x, y, z;
    float rot;
};

static std::unordered_map<std::string, RemotePlayerState> remotePlayers;

namespace MadreSync
{
    void Init()
    {
        std::cout << "[GameSync] Initialized\n";

        MadreNetworking::RegisterHandler("PlayerSync", [](const MadreNetworking::MessagePayload& data)
        {
            std::string id = data.at("id");
            float x = std::stof(data.at("x"));
            float y = std::stof(data.at("y"));
            float z = std::stof(data.at("z"));
            float rot = std::stof(data.at("rot"));

            HandleRemotePlayerSync(id, x, y, z, rot);
        });
    }

    void Shutdown()
    {
        remotePlayers.clear();
    }

    void Update()
    {
        // This would typically be called every frame to sync your player
        // Example stub (replace with real in-game player values):
        float myX = 0.0f, myY = 0.0f, myZ = 0.0f, myRot = 0.0f;

        SyncPlayerPosition(myX, myY, myZ, myRot);
    }

    void SyncPlayerPosition(float x, float y, float z, float rot)
    {
        MadreNetworking::MessagePayload payload = {
            { "id", "localPlayer" }, // Replace with actual session ID
            { "x", std::to_string(x) },
            { "y", std::to_string(y) },
            { "z", std::to_string(z) },
            { "rot", std::to_string(rot) }
        };

        MadreNetworking::Send("PlayerSync", payload);
    }

    void HandleRemotePlayerSync(const std::string& id, float x, float y, float z, float rot)
    {
        remotePlayers[id] = { x, y, z, rot };
        std::cout << "[GameSync] Updated remote player " << id << " to position: (" 
                  << x << ", " << y << ", " << z << ") rot: " << rot << "\n";
    }
}
