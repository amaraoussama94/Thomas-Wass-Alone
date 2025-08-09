<p align="center">
  <img src="https://github.com/amaraoussama94/Thomas-Wass-Alone/blob/main/game_pic.png" alt="Thomas Wass Alone Screenshot">
</p>

# Thomas Wass Alone 🎮

A minimalist 2D platformer inspired by *Thomas Was Alone*, built in C++ using SFML 2.5.1. This project explores cooperative gameplay, time-based challenges, and modular level design—all wrapped in a clean, extensible engine.

## 🧠 General Info

- **Game Name**: Thomas Wass Alone  
- **Version**: 0.8  
- **Genre**: Puzzle Platformer  
- **Players**: Single or Cooperative (Split-screen toggle)  

## 🎮 Controls

| Action                  | Key                |
|-------------------------|--------------------|
| Quit                    | `Escape`           |
| Pause / Start           | `Enter`            |
| Split Screen Toggle     | `E`                |
| Switch Character        | `Tab`              |
| Thomas - Jump           | `Z`                |
| Thomas - Move           | `Q` / `D`          |
| Bob - Jump              | `Up Arrow`         |
| Bob - Move              | `Left` / `Right`   |

---
## 🧩 Project Structure

The codebase is organized for clarity, modularity, and ease of extension. Here's a breakdown of the main directories and files:

Thomas-Wass-Alone/ 
├── src/ # Core source files 
│ ├── Engine/ # Game engine modules (input, rendering, physics) 
│ ├── Entities/ # Player classes (Thomas, Bob) and shared logic 
│ ├── Levels/ # Level loading, parsing, and management 
│ ├── UI/ # HUD, menus, and screen transitions 
│ └── main.cpp # Entry point 
├── assets/ # Textures, sounds, fonts 
├── images/ # Character and environment sprites 
├── audio/ # Sound effects and music 
└── levels/ # Text-based level files 
├── include/ # Header files 
├── Makefile # Build instructions for Linux/windows 
├── CMakeLists.txt # Optional CMake build config 
├── README.md # Project documentation 
└── LICENSE # MIT License
---

## 🚀 Getting Started

### 🔧 Prerequisites

- **C++17-compatible compiler**
- **CMake ≥ 3.24**
- **SFML 3.0.0** (included as a submodule)

### 🛠️ Build Instructions

#### 🐧 Linux

```bash
sudo apt install build-essential cmake libx11-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libgl1-mesa-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libfreetype6-dev
git clone --recurse-submodules https://github.com/yourusername/Thomas-Wass-Alone.git
cd Thomas-Wass-Alone
make
./bin/Thomas_was_Alone
```
### 🪟 Windows Build Instructions

#### Option 1: Using MinGW (GCC)

1. ✅ Install [MinGW-w64](https://www.mingw-w64.org/) with GCC 14.2.0 or compatible
2. ✅ Download the **SFML 3.0.0 MinGW package** from [SFML Downloads](https://www.sfml-dev.org/download/sfml/3.0.0/)
3. ✅ Extract SFML and place it in your project directory (e.g., `external/SFML`)
4. ✅ Add SFML's `include/` and `lib/` paths to your Makefile or compile command

Example compile command:
```bash
g++ src/*.cpp -Iexternal/SFML/include -Lexternal/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio-o Thomas_was_Alone.exe
```
## 🧩 Features of Thomas Was Late

- A clock that counts down from a time appropriate to the challenge of the level.  
- Fire pits that emit a roar relative to the position of the player and respawn the player at the start if they fall in.  
- Water pits have the same effect but without the directional sound effects.  
- Cooperative gameplay: both players must reach the goal within the allotted time.  
  - Bob (shorter, lower-jumping) will often need to stand on Thomas' head to progress.  
- Option to switch between full and split-screen so players can control both characters themselves.  
- Each level is designed in and loaded from a text file, allowing easy creation of varied and numerous levels.

## 🧱 Structuring the Thomas Was Late Engine Code

<p align="center">
  <img src="https://github.com/amaraoussama94/Thomas-Wass-Alone/blob/main/UML%20Engine.png" width="400" height="400" alt="Engine UML Diagram">
</p>
The engine is modular, with separate classes for input, rendering, physics, and game state. This makes it easy to extend or refactor without disrupting core logic.

## 📜 License
This project is licensed under the MIT License. See LICENSE for details.
