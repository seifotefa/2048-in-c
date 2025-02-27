
# EvenMatch! A 2048 Clone - C Implementation

## Introduction
This is a command-line implementation of the popular 2048 game written in C. The game involves sliding numbered tiles on a 4x4 grid to combine them and reach the 2048 tile.

## Features
- Fully functional 2048 gameplay
- Keyboard controls for movement (`w`, `a`, `s`, `d`)
- Random tile generation after each move
- Game-over detection
- Simple terminal-based interface

## Requirements
- A UNIX-based operating system (Linux/macOS) or a compatible terminal emulator on Windows
- A C compiler (such as `gcc`)

## Installation & Compilation
To compile the game, run the following command in the project directory:

```sh
make
```

This will generate an executable file named `game2048`.

## How to Play
1. Run the game using:
   ```sh
   ./game2048
   ```
2. Use the following keys to move the tiles:
   - `w` → Move Up
   - `s` → Move Down
   - `a` → Move Left
   - `d` → Move Right
3. Press `q` to quit the game.
4. The game ends when no more moves are possible.

## Cleaning Up
To remove compiled files, use:
```sh
make clean
```

## File Structure
- `game2048.c` - Contains the main game loop and logic.
- `utility.c` - Implements helper functions for board manipulation.
- `utility.h` - Header file containing function prototypes and constants.
- `Makefile` - Defines compilation rules.

## License
This project is open-source and available for educational purposes.

## Author
Seif Otefa - Note: This project was created as an assignement for the COMPSCI 1XC3 course at McMaster University.

## Next Steps
I am currently planning on implementing a GUI for this game using GIMP Toolkit (GTK) stay tuned!

