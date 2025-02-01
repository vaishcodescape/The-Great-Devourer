# The-Great-Devourer 🐍
The-Great-Devourer is a fun snake game 🐍 made in pure C++
this project was a part of our Data Structure Lab Course IT-206 in 2nd Semester
This is the code for a simple "Snake Game" called "The Great Devourer" written in C++. Here’s an explanation of the various parts of the code:

1. Includes and Libraries
#include <iostream>, #include <cstdlib>, #include <ctime>, #include <thread>, and #include <chrono>: These libraries provide functionalities for input/output, random number generation, time manipulation, and thread control (for controlling game speed).
#ifdef _WIN32: This ensures that platform-specific code is compiled based on the operating system. If Windows is detected (_WIN32), it includes <conio.h> (to capture key presses). For Unix-like systems (Linux, macOS), it uses terminal functions (<termios.h> and <unistd.h>) to capture key presses.
2. Constants and Definitions
#define MAX_SIZE 1000: Defines the maximum possible length for the snake’s body.
Constants like UP, DOWN, LEFT, RIGHT: Represent directions that the snake can move.
SNAKE_CHAR and FOOD_CHAR: Represent characters used to display the snake and food on the game screen.
3. Utility Functions
getKeyPress(): A function that waits for a key press. It handles different ways of capturing key input based on the platform (Windows vs Unix-based).
clearScreen(): Clears the console screen. It uses cls on Windows and clear on Unix-like systems.
displayTitle(): Displays the title, "The Great Devourer" along with an ASCII art representation of a snake and some introductory text.
4. Game Logic
The game uses object-oriented programming with three main classes:

Coordinates: A simple struct that represents a point in the 2D game space (with x and y coordinates).

SnakeGame Class:

It manages the snake's body and movement.
It keeps track of the snake’s current length and direction.
It provides methods to update the snake’s position, grow when it eats food, and check for collisions (with the walls or itself).
GameBoard Class:

Manages the snake and the food.
Handles the rendering of the game screen.
Tracks the score and generates food at random positions.
Handles user input (WASD keys) for changing the snake's direction.
Updates the game state after each move (checking if the snake collides with itself or with the walls, and updating the score if the snake eats food).
5. Main Function (main)
Initializes the game by calling displayTitle(), generating the initial game state, and displaying the instructions.
The game loop starts, where:
The game board is updated (updateBoard()).
The game state is rendered (renderBoard()).
The user’s input is processed (processInput()).
The game is paused briefly between each update using this_thread::sleep_for().
If the snake collides with itself or the walls, the game ends, and the final score is displayed.
Key Features:
Snake Movement: The snake moves in four possible directions (up, down, left, right) based on user input (WASD keys).
Snake Growth: Each time the snake eats food (represented by 'O'), it grows longer, and the score increases.
Game Over: The game ends if the snake hits the walls or collides with itself.
Rendering: The game is rendered in a text-based grid with the snake and food displayed on the screen using ASCII characters.
Gameplay Instructions:
WASD: Control the snake’s movement (W = up, A = left, S = down, D = right).
Start the game: Press any key to start after seeing the title screen.
Game Over: The game ends when the snake collides with its body or the walls.
Summary:
The code implements a terminal-based snake game with basic functionality:

You control a snake that moves around the screen, eating food and growing longer.
The goal is to score as many points as possible by eating food, while avoiding collisions.


