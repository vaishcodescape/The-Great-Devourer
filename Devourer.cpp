#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>  // Windows specific for non-buffered input
#else
#include <termios.h>  // macOS/Linux specific for terminal control
#include <unistd.h>   // For sleep function
#endif

using namespace std;

#define MAX_LENGTH 1000

const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

const char SNAKE_BODY = '*';
const char FOOD = 'O';

int consoleWidth = 50, consoleHeight = 20; // Fixed console dimensions

// Platform-specific functions for getting raw input
#ifdef _WIN32
// Windows platform
int getKey() {
    if (_kbhit()) {
        return _getch();
    }
    return -1; // No key pressed
}
#else
// macOS/Linux platform
int getKey() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt); // Get the terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set the terminal to raw mode
    ch = getchar(); // Read character
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore terminal settings
    return ch;
}
#endif

void initScreen() {
#ifdef _WIN32
    system("cls"); // Clear screen (Windows)
#else
    system("clear"); // Clear screen (macOS/Linux)
#endif
}

void printAsciiArt() {
    cout << " TTTTT  H   H  EEEEE      GGG   RRRR    EEEEE   AAAAA   TTTTT      DDDD   EEEEE   V     V  OOO   U   U  RRRR    EEEEE   RRRR   \n";
    cout << "   T    H   H  E          G      R   R   E       A   A    T        D   D  E        V   V  O   O  U   U  R   R   E       R   R  \n";
    cout << "   T    HHHHH  EEEE       G  GG  RRRR    EEEE    AAAAA    T        D   D  EEEE       V    O   O  U   U  RRRR    EEEE    RRRR   \n";
    cout << "   T    H   H  E          G   G  R  R    E       A   A    T        D   D  E        V   V  O   O  U   U  R  R    E       R  R   \n";
    cout << "   T    H   H  EEEEE      GGG    R  R    EEEEE   A   A    T        DDDD   EEEEE      V     OOO    UUU   R   R   EEEEE   R   R  \n";
    cout << endl;
    cout << "THE GREAT DEVOURER" << endl;
    cout << "Snake Game" << endl;
    cout << "Made by vaishcodescape and sam5506";
}

struct Point {
    int xCoord;
    int yCoord;

    Point() {}

    Point(int x, int y) {
        xCoord = x;
        yCoord = y;
    }
};

class Snake {
    int length;
    char direction;

public:
    Point body[MAX_LENGTH];

    Snake(int x, int y) {
        length = 1;
        body[0] = Point(x, y);
        direction = DIR_RIGHT;
    }

    int getLength() {
        return length;
    }

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

    bool move(Point food) {
        // Move the body of the snake
        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1]; // Shift body parts
        }

        // Move the head of the snake based on direction
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

        // Check if snake collides with itself
        for (int i = 1; i < length; i++) {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord) {
                return false; // Snake collides with itself
            }
        }

        // Check if the snake eats food
        if (food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord) {
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord); // Add new segment to the tail
            length++; // Increase length
        }

        // Check if snake collides with the borders
        if (body[0].xCoord < 0 || body[0].xCoord >= consoleWidth || body[0].yCoord < 0 || body[0].yCoord >= consoleHeight) {
            return false; // Snake hits border
        }

        return true;
    }
};
class Board {
    Snake *snake;
    Point food;
    int score;

public:
    Board() {
        spawnFood();  // Spawn the first food item
        // Place snake in the center of the screen
        snake = new Snake(consoleWidth / 2, consoleHeight / 2);
        score = 0;
    }

    ~Board() {
        delete snake;
    }

    int getScore() {
        return score;
    }

    void spawnFood() {
        // Randomly place the food in the game area
        food = Point(rand() % (consoleWidth - 2) + 1, rand() % (consoleHeight - 2) + 1);
    }

    void displayCurrentScore() {
        cout << "Current Score: " << score << endl; // Display score at the top
    }

    void draw() {
        initScreen();  // Clear the screen

        // Draw the border
        for (int i = 0; i < consoleWidth + 2; i++) {
            cout << "#";
        }
        cout << endl;

        // Draw the game area with border
        for (int y = 0; y < consoleHeight; y++) {
            for (int x = 0; x < consoleWidth; x++) {
                if (x == 0 || x == consoleWidth - 1) {
                    cout << "#"; // Left and right border
                } else if (y == 0 || y == consoleHeight - 1) {
                    cout << "#"; // Top and bottom border
                } else {
                    bool snakePrinted = false;
                    for (int i = 0; i < snake->getLength(); i++) {
                        if (snake->body[i].xCoord == x && snake->body[i].yCoord == y) {
                            cout << SNAKE_BODY; // Snake body
                            snakePrinted = true;
                            break;
                        }
                    }
                    if (!snakePrinted) {
                        if (food.xCoord == x && food.yCoord == y) {
                            cout << FOOD; // Food
                        } else {
                            cout << " "; // Empty space
                        }
                    }
                }
            }
            cout << endl;
        }

        // Draw the border bottom
        for (int i = 0; i < consoleWidth + 2; i++) {
            cout << "#";
        }
        cout << endl;

        displayCurrentScore();
    }

    bool update() {
        bool isAlive = snake->move(food);
        if (!isAlive) return false;

        // If the snake eats food, increase the score and spawn a new food item
        if (food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord) {
            score++;  // Increase score
            spawnFood();  // Spawn a new food item at a random location
        }

        return true;
    }

    void getInput() {
        int key = getKey();
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
};

int main() {
    srand(time(0));
    initScreen();

    printAsciiArt();

    Board *board = new Board();
    cout << "Welcome to Snake Game!" << endl;
    cout << "Use WASD keys to control the snake." << endl;
    cout << "Press any key to start..." << endl;
    getKey(); // Wait for input to start

    while (board->update()) {
        board->draw();
        board->getInput();
        this_thread::sleep_for(chrono::milliseconds(100)); // Control game speed
    }

    cout << "Game Over! Final Score: " << board->getScore() << endl;
    delete board;
    return 0;
}