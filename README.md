# ❌ General Tic-Tac-Toe ⭕

> A robust C++ implementation of an expanded Tic-Tac-Toe engine supporting dynamic board sizes, multiple players, and advanced game state tracking.

## 🎮 How to Play
*   **Setup**: Enter the number of players (3–7) and their full names; the system automatically formats them (e.g., "John Doe").
*   **Grid Customization**: Choose a unique board size for each game, ranging from a minimum of **4x4** up to **10x15**.
*   **Controls**: On your turn, enter a row letter and column number (e.g., **A5** or **j12**) to place your unique piece (`z`, `y`, `x`, etc.).
*   **Winning**: Align **three pieces** horizontally, vertically, or diagonally to win; winning pieces will highlight in **UPPERCASE**.
*   **Rotation & Stats**: After each game, view a detailed win/loss/draw table; the starting player rotates automatically for the next round.

## ✨ Features
- **Dynamic Multiplayer**: Support for 3 to 7 human players with automatic piece assignment (`z` through `t`).
- **Customizable Grid**: Play on any board size from **4x4 up to 10x15**.
- **Smart Turn Rotation**: Implements a round-robin sequence that adapts based on game outcomes (winners move to the end of the queue).
- **Win Detection**: Algorithms to detect 3-in-a-row horizontally, vertically, or diagonally.
- **Visual Feedback**: Winning configurations are automatically highlighted in **UPPERCASE** on the final board.
- **Session Analytics**: Tracks wins, losses, and draws for up to 1,000 games in a formatted statistical table.
- **Robust Validation**: Full error handling for player names (Alpha only) and move coordinates (e.g., `A5`, `j12`).

## 🛠️ Tech Stack
- **Language**: C++
- **Dependencies**: Standard I/O and String handling libraries only.
- **Input Format**: 
    - **Names**: `First Last` (automatically formatted to Title Case).
    - **Moves**: `[Row Letter][Column Number]` (e.g., `B4`, `d10`).

## 🚀 Quick Start

### Compilation
If you have the files locally and the g++ compiler, first navigate to the file location and just run `g++ gtttFunctions.cpp gtttDriver.cpp -o [your_desired_file_name].exe`.

To clone and run locally:
```bash
git clone https://github.com
cd tic-tac-toe
