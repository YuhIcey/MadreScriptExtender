#pragma once

#include <string>
#include <Windows.h>
#include <cstdint>
#include <vector>

enum class ChatType
{
	Local,
	Global,
	System
};

struct PlayerInfo
{
	std::string username;
	uint32_t playerId;
	float posX;
	float posY;
	float posZ;
	bool isAdmin = false;
};

struct ChatMessage
{
	std::string sender;
	std::string message;
	ChatType type;
};

struct GameTime
{
	int hour;
	int day;
	int month;
	int year;
};

struct ConnectionInfo
{
	std::string ipAddress;
	uint16_t port;
	bool isConnected = false;
};

// Handy macro for byte patching
#define PATCH_SIZE_5 5
#define NOP 0x90

// Easy logging tag
#define LOG_TAG "[MSE] "
