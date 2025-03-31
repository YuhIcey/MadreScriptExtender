# Sierra Madre Online (MSE Framework for Fallout: New Vegas)

A C++ networking extension that enables multiplayer functionality through WebSocket communication and game engine hooks for Fallout: New Vegas.

## Overview

The MSE Framework functions as a lightweight middleware layer within Fallout: New Vegas, enabling runtime integration of custom logic and networked behavior without altering the base game code. It operates by dynamically injecting into the game process, establishing function hooks at key engine points—such as scripting interfaces, player updates, and network I/O.

Once initialized, the hook captures game state changes and routes relevant events through custom plugin handlers or sends them over WebSocket to remote servers for multiplayer coordination or real-time mod control.

## Components

### MadreBrowser.exe (Windows) / MadreBrowser (Linux/macOS) - Modifiable NOT THE REAL RELEASE

MadreBrowser is the launcher for Sierra Madre Online. It provides a streamlined interface for:

- **Server Browsing**: Connects to the Sierra Madre Online API to retrieve available servers
- **Discord Authentication**: Verifies player identity and enables social features
- **Game Launching**: Supports both single-player and multiplayer modes
- **Save Management**: Imports and exports special multiplayer save files (user-specific only, no sharing)
- **Game Verification**: Ensures legal ownership through Steam SDK

### MSENetwork.dll (Windows) / libMSENetwork.so (Linux) / libMSENetwork.dylib (macOS)

This is the core networking component injected into the game process. It handles:

- **WebSocket Communication**: Real-time network messaging with the game server
- **Game State Synchronization**: Coordinates player positions, inventory, and actions
- **Chat System**: Manages local and global chat channels
- **Memory Hooks**: Dynamically hooks into the game's memory

## Features

- **Game Engine Hooks**: Intercepts key game functions for player movement, health, NPC interactions, and more
- **WebSocket Communication**: Enables real-time communication with a multiplayer server
- **Plugin System**: Allows third-party developers to extend functionality
- **Low-Level Memory Access**: Efficiently interacts with the game's memory
- **Event System**: Propagates game events to plugins and network
- **Command Interface**: Provides in-game command execution
- **Discord Integration**: Authenticate with Discord and manage user-specific save files
- **Server Browser**: Browse and connect to available multiplayer servers
- **Chat System**: Communicate with other players using local (200m range) and global chat channels

## Requirements

### Runtime Requirements
- Fallout: New Vegas (legally purchased, latest patch)
- Windows 10/11 (64-bit recommended), Linux, or macOS
- Microsoft Visual C++ Redistributable 2015-2022 (Windows only)
- Discord (for authentication)
- Steam (for game ownership verification)

### Build Requirements
- CMake 3.10 or newer
- C++17 compatible compiler (MSVC 2019+, GCC 7+, or Clang 5+)
- Git

## Building from Source

### Windows (Visual Studio)

1. Clone the repository:
   ```
   git clone https://github.com/sierramadre/mse-framework.git
   cd mse-framework
   ```

2. Configure the build with CMake:
   ```
   mkdir build
   cd build
   cmake -G "Visual Studio 17 2022" -A Win32 ..
   ```

3. Build the solution:
   ```
   cmake --build . --config Release
   ```

4. The output files will be in `build/bin/Release/`:
   - MSENetwork.dll
   - MadreBrowser.exe

### Linux

1. Clone the repository:
   ```
   git clone https://github.com/sierramadre/mse-framework.git
   cd mse-framework
   ```

2. Configure and build:
   ```
   mkdir build && cd build
   cmake -DCMAKE_BUILD_TYPE=Release ..
   make
   ```

3. The output files will be in `build/bin/`:
   - libMSENetwork.so
   - MadreBrowser

### macOS

1. Clone the repository:
   ```
   git clone https://github.com/sierramadre/mse-framework.git
   cd mse-framework
   ```

2. Configure and build:
   ```
   mkdir build && cd build
   cmake -DCMAKE_BUILD_TYPE=Release ..
   make
   ```

3. The output files will be in `build/bin/`:
   - libMSENetwork.dylib
   - MadreBrowser

## Installation

### Pre-built Binaries

1. Download the latest release from [sierramadre.online](https://sierramadre.online/download)
2. Run the installer and follow the prompts
3. Start the game using MadreBrowser

### Manual Installation

1. Copy MSENetwork.dll (or libMSENetwork.so/dylib) to your Fallout: New Vegas game directory
2. Copy MadreBrowser to a location of your choice
3. Run MadreBrowser to start the game

## Using MadreBrowser

### Playing Single-Player

1. Launch MadreBrowser
2. Click "Play Single-Player"
3. The game will launch normally without multiplayer features

### Connecting to a Server

1. Launch MadreBrowser
2. Click "Browse Servers"
3. Select a server from the list
4. Click "Connect"
5. If prompted, authenticate with Discord
6. The game will launch and connect to the selected server

### Using the Chat System

- Press T to open the chat interface
- Type your message and press Enter to send a local message (only players within 200 meters will see it)
- Type // followed by your message to send a global message (all players on the server will see it)

## Sierra Madre Online Server Connection Process

1. MadreBrowser launches the game
2. The game process is suspended
3. MSENetwork is injected into the game process
4. The game process is resumed
5. MSENetwork handshakes with Sierra Madre Online servers
6. Available servers are discovered and presented to the user
7. Upon server selection, the connection is established

## User-Specific Save System

Sierra Madre Online uses a custom save system (.fos files) that:
- Stores saves in a user-specific directory
- Prevents sharing saves with other users
- Clearly indicates that save sharing is disabled
- Ensures secure and personalized gameplay

## Development and Extension

The MSE Framework provides a plugin API for developers to extend functionality:

1. Include the PluginAPI.h header in your project
2. Implement the required plugin interface
3. Build your plugin as a DLL/shared library
4. Place your plugin in the "plugins" directory

For API documentation, see the [Developer Wiki](https://discord.gg/3tYExRPH3F).
