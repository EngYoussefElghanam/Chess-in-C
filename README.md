# Chess Game - CS221 Project

## Team Members
- [Youssef Diaa Abdelmohsen Mahmoud Elghannam]
- [Youssef Shaaban Abdelwahed Mohammed Taha]

## Description
A terminal-based chess game implemented in C for CS221 Computer Programming 1.

## How to Compile
```
make
```

## How to Run
```
./chess
```

## Features
- [ ] Basic board display
- [ ] Move validation for all pieces
- [ ] Check/Checkmate/Stalemate detection
- [ ] Undo/Redo
- [ ] Save/Load game
- [ ] Promotion

## Project Structure
- `src/` - Source files (.c)
- `include/` - Header files (.h)
- `saves/` - Saved game files

## Requirements
- GCC compiler
# Chess Game - CS221 Project

# ♟️ Chess Engine in C

A fully-featured, professional chess engine implementation in C with complete rule validation, special moves, draw detection, and advanced game management features.

![C](https://img.shields.io/badge/language-C-blue.svg)
![Version](https://img.shields.io/badge/version-1.0.0-green.svg)
![License](https://img.shields.io/badge/license-MIT-orange.svg)

## 📋 Table of Contents

- [Features](#-features)
- [Project Structure](#-project-structure)
- [Installation](#-installation)
- [Usage](#-usage)
- [Game Commands](#-game-commands)
- [Architecture](#-architecture)
- [Implementation Details](#-implementation-details)
- [Development](#-development)
- [Contributors](#-contributors)
- [License](#-license)

## ✨ Features

### Complete Chess Rules Implementation
- ✅ **All Standard Moves** - Pawns, Knights, Bishops, Rooks, Queens, Kings
- ✅ **Special Moves**
  - Castling (kingside and queenside)
  - En Passant captures
  - Pawn Promotion (to Queen, Rook, Bishop, or Knight)
- ✅ **Move Validation** - Prevents illegal moves and self-check
- ✅ **Check & Checkmate Detection**
- ✅ **Stalemate Detection**

### Draw Conditions
- 🤝 **Threefold Repetition** - Tracks position history (claimable)
- 🤝 **50-Move Rule** - Automatic draw after 50 moves without captures or pawn moves
- 🤝 **Insufficient Material** - King vs King, King+Knight vs King, King+Bishop vs King
- 🤝 **Draw by Agreement** - Players can offer and accept draws

### Game Management
- 💾 **Save/Load System** - Save games to files and resume later
- ↩️ **Unlimited Undo/Redo** - Step backward and forward through game history
- 📊 **Captured Pieces Tracking** - Visual display of captured pieces
- 🎨 **Clean Terminal Interface** - Clear board display with algebraic notation
- 🔔 **Turn Indicators** - Clear indication of current player and check warnings

## 📁 Project Structure

```
chess-engine/
├── src/
│   ├── main.c              # Main game loop and integration
│   ├── board.c             # Board management and piece execution
│   ├── moves.c             # Move validation for all piece types
│   ├── game.c              # Game state management and rules
│   ├── input.c             # User input handling and commands
│   ├── display.c           # Board and UI rendering
│   ├── file_io.c           # Save/load functionality
│   └── history.c           # Undo/redo system
├── include/
│   ├── board.h
│   ├── moves.h
│   ├── game.h
│   ├── input.h
│   ├── display.h
│   ├── file_io.h
│   ├── history.h
│   └── types.h             # Data structure definitions
├── saves/                  # Directory for saved games
├── Makefile                # Build automation
└── README.md
```

## 🚀 Installation

### Prerequisites
- GCC compiler (supporting C11 standard)
- Make build tool
- Unix-like environment (Linux, macOS, WSL on Windows)

### Build Instructions

1. **Clone the repository**
   ```bash
   git clone https://github.com/EngYoussefElghanam/Chess-in-C.git
   cd chess
   ```

2. **Create saves directory**
   ```bash
   mkdir -p saves
   ```

3. **Compile the project**
   ```bash
   make
   ```

4. **Run the game**
   ```bash
   ./chess
   # or
   make run
   ```

### Makefile Targets

| Command | Description |
|---------|-------------|
| `make` or `make all` | Compile the entire project |
| `make clean` | Remove all object files and executable |
| `make run` | Compile and run the game |
| `make re` | Clean and rebuild from scratch |

## 🎮 Usage

### Starting a Game

When you run the game, you'll see the chess board displayed with:
- Column labels (A-H)
- Row numbers (1-8)
- Pieces represented as characters:
  - **White pieces**: lowercase (p, n, b, r, q, k)
  - **Black pieces**: uppercase (P, N, B, R, Q, K)
  - **Empty squares**: `-` (light) and `.` (dark)

### Making Moves

Enter moves in **algebraic notation** using four characters:
```
E2E4    # Move piece from E2 to E4
G1F3    # Move Knight from G1 to F3
E7E8Q   # Pawn promotion (you'll be prompted for piece)
```

Input is **case-insensitive** and whitespace is automatically handled.

### Example Game Flow

```
	A  B  C  D  E  F  G  H  

8	R  N  B  Q  K  B  N  R  	8
7	P  P  P  P  P  P  P  P  	7
6	.  -  .  -  .  -  .  -  	6
5	-  .  -  .  -  .  -  .  	5
4	.  -  .  -  .  -  .  -  	4
3	-  .  -  .  -  .  -  .  	3
2	p  p  p  p  p  p  p  p  	2
1	r  n  b  q  k  b  n  r  	1

	A  B  C  D  E  F  G  H  

White's turn. Enter your move (e.g., 'e2e4'), or command: e2e4
```

## 📜 Game Commands

| Command | Description |
|---------|-------------|
| `SAVE` | Save the current game state to a file |
| `LOAD` | Load a previously saved game |
| `UNDO` | Undo the last move |
| `REDO` | Redo a previously undone move |
| `DRAW` | Offer a draw to your opponent |
| `RESIGN` | Resign from the game |
| `QUIT` | Exit the game immediately |

### Command Examples

**Saving a Game:**
```
White's turn. Enter your move: SAVE
Enter the file name to save
> my_game.txt
GAME SAVED
```

**Loading a Game:**
```
White's turn. Enter your move: LOAD
Enter the saved file name to be loaded
> my_game.txt
GAME LOADED
```

**Undo/Redo:**
```
White's turn. Enter your move: UNDO
Undo GAME
[Board reverts to previous state]

Black's turn. Enter your move: REDO
Redo GAME
[Board returns to latest state]
```

## 🏗️ Architecture

### Core Data Structures

#### `game_state` - Central State Manager
```c
typedef struct {
    char board[8][8];                    // 8x8 chess board
    int is_white_turn;                   // Current turn
    int white_king_moved;                // Castling rights
    int black_king_moved;
    int white_rook_a_moved;
    int white_rook_h_moved;
    int black_rook_a_moved;
    int black_rook_h_moved;
    last_move *last_move;                // En passant tracking
    position_hash position_history[500]; // Repetition detection
    int position_count;
    int halfmove_clock;                  // 50-move rule
} game_state;
```

#### `last_move` - Move Tracking
```c
typedef struct {
    int from_row;
    int from_col;
    int to_row;
    int to_col;
    char piece_moved;
} last_move;
```

#### `position_hash` - Position Tracking for Draws
```c
typedef struct {
    char board_state[64];    // Flattened board
    int castling_rights;     // Encoded rights (4 bits)
    int en_passant_col;      // En passant possibility
    int is_white_turn;       // Turn information
} position_hash;
```

### Module Responsibilities

| Module | Responsibility |
|--------|---------------|
| **board** | Board initialization, piece placement, move execution |
| **moves** | Piece-specific movement validation, path clearance |
| **game** | Check/checkmate detection, draw conditions, game rules |
| **input** | Command parsing, move input, promotion handling |
| **display** | Board rendering, captured pieces display, turn indicators |
| **file_io** | Save/load game states to/from files |
| **history** | Undo/redo functionality, state history management |

## 🔧 Implementation Details

### Move Validation System

The engine uses a **two-tier validation approach**:

1. **`is_valid_move_no_check()`** - Basic movement validation
   - Checks piece-specific movement rules
   - Validates boundaries and path clearance
   - Prevents friendly fire

2. **`is_valid_move()`** - Full validation with check prevention
   - Calls basic validation first
   - Simulates the move
   - Verifies king is not left in check
   - Restores board state

This separation prevents infinite recursion during check detection.

### Special Move Implementation

#### Castling
- Validates king and rook haven't moved
- Checks path clearance between pieces
- Ensures no squares are under attack
- Supports all four castling types

#### En Passant
- Tracks `last_move` struct
- Validates two-square pawn advance
- Confirms capturing pawn on correct rank
- Removes captured pawn from actual position

#### Pawn Promotion
- Detects pawn reaching final rank
- Prompts user for piece selection (Q/R/B/N)
- Validates choice and updates board

### Draw Detection Algorithms

#### Threefold Repetition
- Uses position hashing to encode board state
- Stores up to 500 positions in history
- Compares current position with all previous
- Player can claim draw when detected

#### 50-Move Rule
- Tracks `halfmove_clock` counter
- Resets on pawn moves or captures
- Automatic draw at 100 halfmoves (50 full moves)

#### Insufficient Material
- Counts remaining pieces on board
- Validates only kings or king + minor piece remain
- Automatically declares draw

### File Format

Game states are stored in a compact **97-byte format**:
- **64 bytes**: Board state (8×8 characters)
- **32 bytes**: Captured pieces (2×16 characters)
- **1 byte**: Current turn (0 or 1)

This fixed-size format enables efficient file seeking for undo/redo.

## 🛠️ Development

### Compiler Flags
```makefile
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
```
- `-Wall -Wextra`: Enable all warnings
- `-Werror`: Treat warnings as errors (enforces clean code)
- `-std=c11`: Use C11 standard
- `-g`: Include debugging symbols

### Code Style Guidelines
- **Naming**: Snake_case for functions and variables
- **Indentation**: Consistent spacing (4 spaces)
- **Comments**: Explain complex logic and algorithms
- **Modularity**: Each module handles specific functionality

### Testing Recommendations
- Test all piece movements
- Verify special moves (castling, en passant, promotion)
- Test endgame conditions (checkmate, stalemate, draws)
- Validate undo/redo functionality
- Test save/load with various game states

## 👥 Contributors

This project was collaboratively developed by:

- **[Youssef Diaa Abdelmohsen Elghanam]** - Core game logic, move validation, data structures, build system
- **[Youssef Shaaban Abdelwahed Taha]** - User interface, input handling, file I/O, history system

### Contribution Breakdown

**Core Engine:**
- Board management and piece execution
- Movement validation for all piece types
- Game state management and rule enforcement
- Special moves implementation
- Data structure design

**User Interface & Features:**
- Display system and board rendering
- Input processing and command handling
- Save/load functionality
- Undo/redo system
- Game history management

**Collaborative Work:**
- Main game loop integration
- Testing and debugging
- Documentation
- Git workflow and version control

## 📄 License

This project is licensed under the MIT License - see below for details:

```
MIT License

Copyright (c) 2024 [Your Names]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## 🎯 Future Enhancements

Potential features for future versions:

- [ ] AI opponent with minimax algorithm
- [ ] PGN (Portable Game Notation) import/export
- [ ] Move history display in algebraic notation
- [ ] Timer support for timed games
- [ ] Network multiplayer support
- [ ] GUI interface using SDL or ncurses
- [ ] Opening book database
- [ ] Move hints and suggestions
- [ ] Game analysis and evaluation

## 🐛 Known Issues

- None currently reported

## 📞 Contact

For questions, suggestions, or bug reports, please open an issue on GitHub or contact the contributors.

---

**Enjoy playing chess!** ♟️👑
