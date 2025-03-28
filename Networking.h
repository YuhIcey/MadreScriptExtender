#pragma once

#include <string>
#include <unordered_map>
#include <functional>

namespace MadreNetworking
{
    using MessagePayload = std::unordered_map<std::string, std::string>;
    using MessageHandler = std::function<void(const MessagePayload&)>;

    void Init();
    void Shutdown();
    void Update();

    void Send(const std::string& type, const MessagePayload& data);
    void RegisterHandler(const std::string& type, MessageHandler handler);
}
