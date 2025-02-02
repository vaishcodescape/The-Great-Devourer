# The-Great-Devourer 🐍
## made by vaishcodescape(Aditya Vaish) and sam5506(Samyak Shah)

The-Great-Devourer is a fun snake game 🐍 made in pure C++
this project was a part of our Data Structure Lab Course IT-206 in 2nd Semester of B.Tech(Engineering) 
# The Great Devourer Snake Game

This is a simple implementation of the classic Snake game in C++ called "The Great Devourer." The game allows you to control a snake that grows longer as it eats food, with the goal of achieving the highest possible score while avoiding collisions with walls and the snake's own body.

## Features

- **Snake Movement**: Use the `W`, `A`, `S`, `D` keys to control the snake's direction (Up, Left, Down, Right).
- **Growing Snake**: Each time the snake eats food (represented by "O"), it grows longer.
- **Game Over**: The game ends if the snake collides with the walls or its own body.
- **Score**: Your score increases as the snake eats food.

## Requirements

- C++ compiler (e.g., GCC, Clang)
- A terminal or console to run the game
- Windows, Linux, or macOS environment 

## How to Play

1. **Clone the repository**:
   ```bash
   git clone https://github.com/vaishcodescape/TheGreatDevourerSnakeGame.git
   
2. **Copy**:
   ```bash
   cd TheGreatDevourerSnakeGame
   
3. **Compile the code**:
   ```bash
   g++ -o snake_game main.cpp

4. **Run the game**:
   ```bash
   ./snake_game
## Controls:
- **W** or **w**: Move up
- **A** or **a**: Move left
- **S** or **s**: Move down
- **D** or **d**: Move right

## Objective:
Eat the food (represented by `O`) to grow the snake and score points. Avoid colliding with the walls or the snake's own body.

---

## Code Overview
The game is written in **C++** and follows an object-oriented design. Here’s a breakdown of the core components:

### 1. Classes and Structs
- **Coordinates**: A simple structure representing a 2D point (`x`, `y`) on the game board. It’s used for both the snake's body and food.
- **SnakeGame**: This class manages the snake's state, including its body and direction. It provides methods for updating the snake's movement, checking for collisions, and handling food consumption.
- **GameBoard**: This class manages the game logic, including the snake, food, and score. It handles rendering the game board, processing user input, and updating the game state each frame.

### 2. Game Logic
- **Movement**: The snake moves in one of four directions, based on user input. Each time the snake moves, its body is updated accordingly.
- **Collisions**: The game checks if the snake collides with the walls or its own body. If a collision occurs, the game ends.
- **Food**: The snake eats food to grow longer and gain points. After eating, new food is generated at a random position on the board.

### 3. Cross-Platform Compatibility
- **Windows**: The game uses `conio.h` for keypress detection.
- **Linux/macOS**: The game uses `termios.h` to configure terminal settings and read keypresses.

### 4. Rendering the Game
The game uses a text-based interface, drawing the snake and food on the screen using ASCII characters. The game board is rendered within the terminal, with the snake represented by `*` and food by `O`.

### 5. Game Loop
The main game loop runs continuously, updating the game state (snake position, food, collisions) and rendering the board at regular intervals (every 100 milliseconds). The game ends when the snake collides with the walls or itself.

---

## Code Structure
- **main.cpp**: Contains the game’s main logic, including the game loop, input handling, and rendering.
- **Platform-specific code**: Handles keypress input differently based on the operating system (Windows vs Linux/macOS).

---
Example Output
When you start the game, the console will display the game board, showing the snake (`*`) and food (`O`). Here’s an example of what it might look like:
![My Image](https://github.com/vaishcodescape/The-Great-Devourer/blob/main/images/Screenshot%202025-02-02%20at%2010.11.27%E2%80%AFPM.png)
---
## Credits
Created by [vaishcodescape](https://github.com/vaishcodescape) and [sam5506](https://github.com/sam5506).

Enjoy playing **The Great Devourer**!
