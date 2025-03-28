#include "Networking.h"

#include "websocketpp/config/asio_no_tls_client.hpp"
#include "websocketpp/client.hpp"
#include "websocketpp/json.hpp"
#include <boost/version.hpp>
#include <boost/align.hpp>
#include <boost/system/error_code.hpp>


#include "websocketpp/json.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <functional>

using json = nlohmann::json;
using client = websocketpp::client<websocketpp::config::asio_client>;
using MessagePayload = std::unordered_map<std::string, std::string>;
using MessageHandler = std::function<void(const MessagePayload&)>;

namespace MadreNetworking
{
    static client wsClient;
    static websocketpp::connection_hdl wsConnection;
    static std::unordered_map<std::string, MessageHandler> handlers;
    static std::mutex queueMutex;
    static std::queue<std::pair<std::string, MessagePayload>> messageQueue;
    static bool connected = false;

    void on_open(websocketpp::connection_hdl hdl)
    {
        std::cout << "[Networking] Connected to server.\n";
        wsConnection = hdl;
        connected = true;
    }

    void on_close(websocketpp::connection_hdl hdl)
    {
        std::cout << "[Networking] Disconnected from server.\n";
        connected = false;
    }

    void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg)
    {
        try {
            auto payload = msg->get_payload();
            auto parsed = json::parse(payload);
            MessagePayload data;

            for (auto& [key, value] : parsed.items()) {
                data[key] = value;
            }

            auto type = data["type"];
            std::lock_guard<std::mutex> lock(queueMutex);
            messageQueue.emplace(type, data);
        }
        catch (const std::exception& e) {
            std::cout << "[Networking] JSON parse error: " << e.what() << "\n";
        }
    }

    void Init(const std::string& uri = "ws://localhost:7777")
    {
        try {
            wsClient.init_asio();
            wsClient.set_open_handler(&on_open);
            wsClient.set_close_handler(&on_close);
            wsClient.set_message_handler(&on_message);

            websocketpp::lib::error_code ec;
            auto con = wsClient.get_connection(uri, ec);
            if (ec) {
                std::cout << "[Networking] Connection failed: " << ec.message() << "\n";
                return;
            }

            wsClient.connect(con);
            std::thread([&]() { wsClient.run(); }).detach();
        }
        catch (const std::exception& e) {
            std::cout << "[Networking] Exception: " << e.what() << "\n";
        }
    }

    void Shutdown()
    {
        if (connected) {
            websocketpp::lib::error_code ec;
            wsClient.close(wsConnection, websocketpp::close::status::going_away, "", ec);
            if (ec) std::cout << "[Networking] Close Error: " << ec.message() << "\n";
            connected = false;
        }
    }

    void Send(const std::string& type, const MessagePayload& data)
    {
        if (!connected) return;

        json j;
        j["type"] = type;
        for (const auto& [k, v] : data) j[k] = v;

        websocketpp::lib::error_code ec;
        wsClient.send(wsConnection, j.dump(), websocketpp::frame::opcode::text, ec);
        if (ec) std::cout << "[Networking] Send Error: " << ec.message() << "\n";
    }

    void RegisterHandler(const std::string& type, MessageHandler handler)
    {
        handlers[type] = std::move(handler);
    }

    void Update()
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        while (!messageQueue.empty())
        {
            auto [type, data] = messageQueue.front();
            messageQueue.pop();

            auto it = handlers.find(type);
            if (it != handlers.end()) {
                it->second(data);
            } else {
                std::cout << "[Networking] No handler for: " << type << "\n";
            }
        }
    }
}
