# Project Z - 2D Space Shooter

A 2D space shooting game made in C++ with SFML.

### Assets
- `spaceShip.png` - Player ship
- `attack*.PNG`, `bestAttack.PNG` - Attacks
- `flame1.png`, `flair.PNG` - Effects

### Requirements
- CMake 3.20+
- C++17 Compiler (MSVC / GCC / Clang)
- Git

SFML is **not** required to be installed manually. CMake will handle it.

### How to Build (For Anyone)

**Option 1: Visual Studio (Windows) - Easiest**
1. Clone the repo
2. Open folder in Visual Studio (Open a local folder)
3. VS will run CMake automatically
4. Press Build -> Build All
5. Run

**Option 2: Command Line**
```bash
git clone https://github.com/tatsatojha89-crypto/project-z.git
cd project-z
mkdir build
cd build
cmake ..
cmake --build . --config Release