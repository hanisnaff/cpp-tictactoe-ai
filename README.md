# Tic-Tac-Toe AI

A small terminal-based Tic-Tac-Toe game written in **C++17**. Play as X against an AI that uses the minimax algorithm.

## What it demonstrates
- Functions, arrays, loops, and input validation
- Separating game state from game logic
- Recursion and the minimax decision algorithm
- A simple human-vs-computer game loop

## Build and run

Requires a C++17 compiler and CMake 3.16+.

```bash
cmake -S . -B build
cmake --build build
./build/tictactoe
```

On Windows, run `build\Debug\tictactoe.exe` or `build\tictactoe.exe`, depending on your generator.

## How to play
Enter a number from 1 to 9 to place X in the corresponding square. The AI plays O.

## Next improvements
- Add difficulty levels
- Add a score tracker
- Add automated tests
