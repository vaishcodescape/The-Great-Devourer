# The-Great-Devourer 🐍
The-Great-Devourer is a fun snake game 🐍 made in pure C++
this project was a part of our Data Structure Lab Course IT-206 in 2nd Semester
This is the code for a simple "Snake Game" called "The Great Devourer" written in C++. Here’s an explanation of the various parts of the code:

Overview
This code implements a simple console-based Snake game. The player controls a snake that moves around the screen, eats food, and grows longer. The game ends if the snake collides with itself or the boundaries of the game area.

Key Components
Includes and Preprocessor Directives:

The code includes necessary libraries such as <iostream>, <cstdlib>, <ctime>, <thread>, and <chrono> for input/output, random number generation, and timing.
It uses preprocessor directives to handle platform-specific code for Windows and Unix-like systems.
Constants and Macros:

Constants are defined for directions (UP, DOWN, LEFT, RIGHT), characters representing the snake (SNAKE_CHAR) and food (FOOD_CHAR), and the maximum size of the snake (MAX_SIZE).
The screen dimensions are set with screenWidth and screenHeight.
Key Press Handling:

The getKeyPress() function captures keyboard input. It uses different methods for Windows (_kbhit() and _getch()) and Unix-like systems (using termios).
Screen Management:

The clearScreen() function clears the console screen, using system("cls") for Windows and system("clear") for Unix-like systems.
Title Display:

The displayTitle() function prints the game's title and some ASCII art to the console.
Coordinates Structure:

The Coordinates struct holds the x and y positions of the snake and food on the game board.
SnakeGame Class:

This class manages the snake's state, including its length, direction, and position.
It has methods to update the direction, make moves, and check for collisions with itself or the boundaries.
GameBoard Class:

This class manages the game board, including the snake and food.
It generates food at random positions, displays the score, and renders the game board.
The updateBoard() method updates the game state, checks for collisions, and generates new food when the snake eats.
Main Function:

The main() function initializes the game, displays the title, and starts the game loop.
The loop continues until the snake collides with itself or the boundaries, updating the board and processing user input at regular intervals.
Game Loop
The game loop consists of:
Updating the game state (updateBoard()).
Rendering the game board (renderBoard()).
Processing user input (processInput()).
Sleeping for a short duration to control the game speed.
Game Over
When the game ends, the final score is displayed, and the dynamically allocated GameBoard object is deleted to free memory.
Conclusion
This code provides a complete implementation of a simple Snake game in C++. It demonstrates the use of object-oriented programming principles, such as encapsulation and class design, while also handling platform-specific input and output. The game is interactive and allows for basic user input to control the snake's movement.
