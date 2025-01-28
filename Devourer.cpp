//THE GREAT DEVOURER SNAKE GAME
//Made by vaishcodescape and sam5506

#include <bits/stdc++.h>
#include <conio.h> // key press kbhit
#include <windows.h>

using namespace std;

// Maximum length of the snake
#define MAX_LENGTH 1000

// Direction constants for the snake
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

// Special characters for the Great Devourer and food
const char GREAT_DEVOURER = '->';
const char FOOD = '*';

// The size of the console screen
int consoleWidth, consoleHeight;

// Function to initialize screen dimensions
void initScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Function to print the ASCII art pattern
void printAsciiArt() {
    cout << "*****  *   *   ****  ****   *****  *****  *****     ****   *****  *   *  ***  *   *  ****   *****  ****  " << endl;
    cout << "  *    *   *  *      *   *  *      *   *    *       *   *  *      *   * *   * *   *  *   *  *      *   * " << endl;
    cout << "  *    *****  *  **  ****   ****   *****    *       *   *  ****   *   * *   * *   *  ****   ****   ****  " << endl;
    cout << "  *    *   *  *   *  *  *   *      *   *    *       *   *  *      *   * *   * *   *  *  *   *      *  *  " << endl;
    cout << "  *    *   *   ****  *   *  *****  *   *    *       ****   *****  * * *  ***   ***   *   *  *****  *   * " << endl;
}

// Structure to represent a point (x, y) on the board
struct Point {
    int xCoord;
    int yCoord;

    // Default constructor
    Point() {}

    // Parameterized constructor to initialize coordinates
    Point(int x, int y) {
        xCoord = x;
        yCoord = y;
    }
};

// Snake class responsible for controlling the snake's state and movement
class Snake {
    int length;   // The length of the snake
    char direction;  // The current direction of the snake

public:
    Point body[MAX_LENGTH];  // Array to store the body of the snake

    // Constructor to initialize the snake at a given starting position
    Snake(int x, int y) {
        length = 1;
        body[0] = Point(x, y);
        direction = DIR_RIGHT; // Initial direction to the right
    }

    // Get the current length of the snake
    int getLength() {
        return length;
    }

    // Change the direction of the snake (ensures it doesn't go in the opposite direction)
    void changeDirection(char newDirection) {
        switch (newDirection) {
            case DIR_UP:
                if (direction != DIR_DOWN) direction = DIR_UP;
                break;
            case DIR_DOWN:
                if (direction != DIR_UP) direction = DIR_DOWN;
                break;
            case DIR_LEFT:
                if (direction != DIR_RIGHT) direction = DIR_LEFT;
                break;
            case DIR_RIGHT:
                if (direction != DIR_LEFT) direction = DIR_RIGHT;
                break;
        }
    }

    // Move the snake based on the current direction
    bool move(Point food, Point greatDevourer) {
        // Move each segment of the snake's body
        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }

        // Update the head of the snake based on the direction
        switch (direction) {
            case DIR_UP:
                body[0].yCoord--;
                break;
            case DIR_DOWN:
                body[0].yCoord++;
                break;
            case DIR_RIGHT:
                body[0].xCoord++;
                break;
            case DIR_LEFT:
                body[0].xCoord--;
                break;
        }

        // Check if the snake bites itself (collides with its own body)
        for (int i = 1; i < length; i++) {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord) {
                return false; // Game over if it bites itself
            }
        }

        // Check if the snake eats food (grows in length)
        if (food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord) {
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord); // Add new segment
            length++;  // Increase the length of the snake
        }

        // Check if the snake eats the Great Devourer
        if (greatDevourer.xCoord == body[0].xCoord && greatDevourer.yCoord == body[0].yCoord) {
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord); // Add multiple segments
            length += 3;  // Increase the length of the snake by more segments
        }

        return true;  // Return true if the snake is still alive
    }
};

// Board class to manage the game state, including snake, food, scoring, and Great Devourer
class Board {
    Snake *snake;  // Snake object representing the player
    Point food;  // The food's position
    Point greatDevourer;  // The position of the Great Devourer
    int score;  // The player's score

public:
    // Constructor to initialize the board, snake, food, and spawn Great Devourer
    Board() {
        spawnFood();
        spawnGreatDevourer();
        snake = new Snake(10, 10);  // Initial snake position
        score = 0;
    }

    // Destructor to clean up memory
    ~Board() {
        delete snake;
    }

    // Get the current score
    int getScore() {
        return score;
    }

    // Spawn food at a random position on the board
    void spawnFood() {
        int x = rand() % consoleWidth;
        int y = rand() % consoleHeight;

        food = Point(x, y);
    }

    // Spawn the Great Devourer at a random position
    void spawnGreatDevourer() {
        int x = rand() % consoleWidth;
        int y = rand() % consoleHeight;

        greatDevourer = Point(x, y);
    }

    // Display the current score at the top of the screen
    void displayCurrentScore() {
        gotoxy(consoleWidth / 2, 0);
        cout << "Current Score: " << score;
    }

    // Move the cursor to a specific position on the console
    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    // Draw the current state of the board, including the snake, food, and Great Devourer
    void draw() {
        system("cls");  // Clear the screen

        // Draw the snake
        for (int i = 0; i < snake->getLength(); i++) {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << 'O';  // Snake body part
        }

        // Draw the food
        gotoxy(food.xCoord, food.yCoord);
        cout << FOOD;

        // Draw the Great Devourer
        gotoxy(greatDevourer.xCoord, greatDevourer.yCoord);
        cout << GREAT_DEVOURER;

        // Display the current score
        displayCurrentScore();
    }

    // Update the game state (move the snake, check for collisions, and update the score)
    bool update() {
        bool isAlive = snake->move(food, greatDevourer);  // Move the snake and check if alive
        if (!isAlive) return false;  // If the snake is dead, return false

        // If the snake eats the food, increase the score and spawn new food
        if (food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord) {
            score++;
            spawnFood();  // Spawn new food
        }

        // If the snake eats the Great Devourer, increase the score and spawn a new Great Devourer
        if (greatDevourer.xCoord == snake->body[0].xCoord && greatDevourer.yCoord == snake->body[0].yCoord) {
            score += 10;  // Increase score significantly for eating Great Devourer
            spawnGreatDevourer();  // Spawn a new Great Devourer
        }

        return true;  // Return true if the game is still ongoing
    }

    // Handle user input (keyboard controls)
    void getInput() {
        if (kbhit()) {
            int key = getch();
            switch (key) {
                case 'w': case 'W':
                    snake->changeDirection(DIR_UP);
                    break;
                case 'a': case 'A':
                    snake->changeDirection(DIR_LEFT);
                    break;
                case 's': case 'S':
                    snake->changeDirection(DIR_DOWN);
                    break;
                case 'd': case 'D':
                    snake->changeDirection(DIR_RIGHT);
                    break;
            }
        }
    }
};

// Main function to run the game
int main() {
    srand(time(0));  // Initialize random seed
    initScreen();  // Set up console screen dimensions

    // Print ASCII art before the game starts
    printAsciiArt();

    Board *board = new Board();  // Create the game board
    cout << "Welcome to Snake Game!" << endl;
    cout << "Use WASD keys to control the snake." << endl;
    cout << "Press any key to start..." << endl;
    getch();  // Wait for user to press a key to start the game

    // Main game loop
    while (board->update()) {
        board->getInput();  // Get user input for direction
        board->draw();  // Draw the updated game state
        Sleep(100);  // Pause to control the game speed
    }

    // Game over message
    cout << "\nGame Over!" << endl;
    cout << "Final score: " << board->getScore() << endl;

    delete board;  // Clean up dynamically allocated memory
    return 0;
}
