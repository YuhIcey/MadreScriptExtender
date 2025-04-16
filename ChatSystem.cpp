#include "ChatSystem.h"
#include <iostream>
#include <unordered_map>
#include <string>

namespace MadreChat
{
    // Storage for private messages
    std::unordered_map<std::string, std::vector<std::string>> privateMessages;

    void Init()
    {
        std::cout << "[ChatSystem] Initialized\n";
    }

    void Shutdown()
    {
        std::cout << "[ChatSystem] Shutdown\n";
    }

    void SendMessage(const std::string& user, const std::string& message)
    {
        std::cout << user << ": " << message << "\n";
    }

    void SendPrivateMessage(const std::string& fromUser, const std::string& toUser, const std::string& message)
    {
        std::string formattedMessage = "[Private] " + fromUser + " -> " + toUser + ": " + message;
        std::cout << formattedMessage << "\n";
        privateMessages[toUser].push_back(formattedMessage);
    }

    void ListCommands()
    {
        std::cout << "Available Commands:\n";
        std::cout << "/help - Show available commands\n";
        std::cout << "/whisper <user> <message> - Send a private message\n";
    }
}
