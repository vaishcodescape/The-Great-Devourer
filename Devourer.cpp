// The Great Devourer Snake Game

// Including necessary libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>  // For _kbhit() and _getch() on Windows
#else
#include <termios.h>   // For terminal I/O on Unix-based systems
#include <unistd.h>    // For STDIN_FILENO on Unix-based systems
#endif

using namespace std;

// Defining constants for the game
#define MAX_SIZE 1000  // Maximum size of the snake
const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';
const char SNAKE_CHAR = '*';
const char FOOD_CHAR = 'O';

// Screen dimensions
int screenWidth = 50, screenHeight = 20;  

#ifdef _WIN32
// Function to get keyboard input on Windows
int getKeyPress() {
    if (_kbhit()) {
        return _getch();
    }
    return -1;  
}
#else
// Function to get keyboard input on Unix-based systems
int getKeyPress() {
    struct termios old, current;
    int character;
    tcgetattr(STDIN_FILENO, &old);  // Get current terminal attributes
    current = old;
    current.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &current);  // Set new terminal attributes
    character = getchar();  // Get a character from the terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &old);  // Restore old terminal attributes
    return character;
}
#endif

// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls");  // Clear screen on Windows
#else
    system("clear");  // Clear screen on Unix-based systems
#endif
}

// Function to display the game title
void displayTitle() {
    cout << " TTTTT  H   H  EEEEE      GGG   RRRR    EEEEE   AAAAA   TTTTT      DDDD   EEEEE   V     V  OOO   U   U  RRRR    EEEEE   RRRR   \n";
    cout << "   T    H   H  E          G      R   R   E       A   A    T        D   D  E        V   V  O   O  U   U  R   R   E       R   R  \n";
    cout << "   T    HHHHH  EEEE       G  GG  RRRR    EEEE    AAAAA    T        D   D  EEEE       V    O   O  U   U  RRRR    EEEE    RRRR   \n";
    cout << "   T    H   H  E          G   G  R  R    E       A   A    T        D   D  E        V   V  O   O  U   U  R  R    E       R  R   \n";
    cout << "   T    H   H  EEEEE      GGG    R  R    EEEEE   A   A    T        DDDD   EEEEE      V     OOO    UUU   R   R   EEEEE   R   R  \n";
    cout << endl;
    
    cout << "  ---_ ......._-_--.\n";
    cout << "      (|\\ /      / /| \\  \\\n";
    cout << "      /  /     .'  -=-'   `.\n";
    cout << "     /  /    .'             )\n";
    cout << "   _/  /   .'        _.)   /\n";
    cout << "  / o   o        _.-' /  .'\n";
    cout << "  \\          _.-'    / .'*|\n";
    cout << "   \\______.-'//    .'.' \\*|\n";
    cout << "    \\|  \\ | //   .'.' _ |*|\n";
    cout << "     `   \\|//  .'.'_ _ _|*|\n";
    cout << "      .  .// .'.' | _ _ \\*|\n";
    cout << "      \\`-|\\_/ /    \\ _ _ \\*\\\n";
    cout << "       `/'\\__/      \\ _ _ \\*\\\n";
    cout << "      /^|            \\ _ _ \\*\n";
    cout << "     '  `             \\ _ _ \\n";
    
    cout << endl;
    cout << "THE GREAT DEVOURER" << endl;
    cout << "Snake Game" << endl;
    cout << "Created by vaishcodescape and sam5506"<< endl;
}

// Structure to represent coordinates (x, y)
struct Coordinates {
    int x;
    int y;

    Coordinates() {}

    Coordinates(int a, int b) {
        x = a;
        y = b;
    }
};

// Class to represent the snake game
class SnakeGame {
    int currentLength;  // Current length of the snake
    char currentDirection;  // Current direction of the snake

public:
    Coordinates body[MAX_SIZE];  // Array to store the snake's body coordinates

    // Constructor to initialize the snake's position and direction
    SnakeGame(int x, int y) {
        currentLength = 1;
        body[0] = Coordinates(x, y);
        currentDirection = RIGHT;
    }

    // Function to get the current length of the snake
    int getCurrentLength() {
        return currentLength;
    }

    // Function to update the snake's direction based on user input
    void updateDirection(char newDir) {
        switch (newDir) {
            case UP:
                if (currentDirection != DOWN) currentDirection = UP;
                break;
            case DOWN:
                if (currentDirection != UP) currentDirection = DOWN;
                break;
            case LEFT:
                if (currentDirection != RIGHT) currentDirection = LEFT;
                break;
            case RIGHT:
                if (currentDirection != LEFT) currentDirection = RIGHT;
                break;
        }
    }

    // Function to move the snake and check for collisions
    bool makeMove(Coordinates food) {
        // Move the body segments
        for (int i = currentLength - 1; i > 0; i--) {
            body[i] = body[i - 1];  
        }

        // Move the head in the current direction
        switch (currentDirection) {
            case UP:
                body[0].y--;
                break;
            case DOWN:
                body[0].y++;
                break;
            case RIGHT:
                body[0].x++;
                break;
            case LEFT:
                body[0].x--;
                break;
        }

        // Check for collision with the body
        for (int i = 1; i < currentLength; i++) {
            if (body[0].x == body[i].x && body[0].y == body[i].y) {
                return false;
            }
        }

        // Check if the snake has eaten the food
        if (food.x == body[0].x && food.y == body[0].y) {
            body[currentLength] = Coordinates(body[currentLength - 1].x, body[currentLength - 1].y);
            currentLength++;
        }

        // Check for collision with the wall
        if (body[0].x < 0 || body[0].x >= screenWidth || body[0].y < 0 || body[0].y >= screenHeight) {
            return false;
        }

        return true;  // Move is valid
    }
};

// Class to represent the game board
class GameBoard {
    SnakeGame *snake;  // Pointer to the snake game
    Coordinates foodItem;  // Coordinates of the food item
    int scoreCount;  // Current score

public:
    // Constructor to initialize the game board
    GameBoard() {
        generateFood();  
        snake = new SnakeGame(screenWidth / 2, screenHeight / 2);
        scoreCount = 0;
    }

    // Destructor to clean up the snake game
    ~GameBoard() {
        delete snake;
    }

    // Function to get the current score
    int getCurrentScore() {
        return scoreCount;
    }

    // Function to generate new food at random coordinates
    void generateFood() {
        foodItem = Coordinates(rand() % (screenWidth - 2) + 1, rand() % (screenHeight - 2) + 1);
    }

    // Function to display the current score
    void displayScore() {
        cout << "Score: " << scoreCount << endl;
    }

    // Function to render the game board
    void renderBoard() {
        clearScreen();  // Clear the screen

        // Draw the top border
        for (int i = 0; i < screenWidth + 2; i++) {
            cout << "#";
        }
        cout << endl;

        // Draw the game area
        for (int y = 0; y < screenHeight; y++) {
            for (int x = 0; x < screenWidth; x++) {
                if (x == 0 || x == screenWidth - 1) {
                    cout << "#";  // Draw the side borders
                } else if (y == 0 || y == screenHeight - 1) {
                    cout << "#";  // Draw the top and bottom borders
                } else {
                    bool isSnakePrinted = false;
                    for (int i = 0; i < snake->getCurrentLength(); i++) {
                        if (snake->body[i].x == x && snake->body[i].y == y) {
                            cout << SNAKE_CHAR;  // Draw the snake
                            isSnakePrinted = true;
                            break;
                        }
                    }
                    if (!isSnakePrinted) {
                        if (foodItem.x == x && foodItem.y == y) {
                            cout << FOOD_CHAR;  // Draw the food
                        } else {
                            cout << " ";  // Draw empty space
                        }
                    }
                }
            }
            cout << endl;
        }

        // Draw the bottom border
        for (int i = 0; i < screenWidth + 2; i++) {
            cout << "#";
        }
        cout << endl;

        displayScore();  // Display the current score
    }

    // Function to update the game board
    bool updateBoard() {
        bool alive = snake->makeMove(foodItem);  // Move the snake
        if (!alive) return false;

        // Check if the snake has eaten the food
        if (foodItem.x == snake->body[0].x && foodItem.y == snake->body[0].y) {
            scoreCount++;
            generateFood();  // Generate new food
        }

        return true;
    }

    // Function to process user input
    void processInput() {
        int keyPress = getKeyPress();  // Get the key pressed by the user
        switch (keyPress) {
            case 'a': case 'A':
                snake->updateDirection(LEFT);  // Move left
                break;
            case 'w': case 'W':
                snake->updateDirection(UP);  // Move up
                break;
            case 's': case 'S':
                snake->updateDirection(DOWN);  // Move down
                break;
            case 'd': case 'D':
                snake->updateDirection(RIGHT);  // Move right
                break;
        }
    }
};

// Main function to run the game
int main() {
    srand(time(0));  // Seed the random number generator
    clearScreen();  // Clear the screen

    displayTitle();  // Display the game title

    GameBoard *game = new GameBoard();  // Create a new game board
    cout << "Snake Game: Use AWSD to play." << endl;
    cout << "Press any key to begin..." << endl;
    getKeyPress();  // Wait for the user to press a key

    // Game loop
    while (game->updateBoard()) {
        game->renderBoard();  // Render the game board
        game->processInput();  // Process user input
        this_thread::sleep_for(chrono::milliseconds(100));  // Wait for a short period
    }

    cout << "Game Over! Final Score: " << game->getCurrentScore() << endl;
    delete game;  // Clean up the game board
    return 0;
}
