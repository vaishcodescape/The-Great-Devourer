//The-Great-Devourer Snake Game
//Made by: vaishcodescape and sam5506
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>

using namespace std;

#define MAX_LENGTH 1000

// Directions
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

int consoleWidth = 40, consoleHeight = 20;  // Console dimensions

// Point structure
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// Snake class
class Snake {
    char direction;
public:
    vector<Point> body;

    Snake(int x, int y) {
        body.push_back(Point(x, y));
        direction = DIR_RIGHT;
    }

    void changeDirection(char newDirection) {
        if ((newDirection == DIR_UP && direction != DIR_DOWN) ||
            (newDirection == DIR_DOWN && direction != DIR_UP) ||
            (newDirection == DIR_LEFT && direction != DIR_RIGHT) ||
            (newDirection == DIR_RIGHT && direction != DIR_LEFT)) {
            direction = newDirection;
        }
    }

    bool move(Point food) {
        Point newHead = body[0];

        // Update head position
        switch (direction) {
            case DIR_UP: newHead.y--; break;
            case DIR_DOWN: newHead.y++; break;
            case DIR_LEFT: newHead.x--; break;
            case DIR_RIGHT: newHead.x++; break;
        }

        // Check for self-collision
        for (const auto& segment : body) {
            if (segment.x == newHead.x && segment.y == newHead.y) {
                return false;
            }
        }

        body.insert(body.begin(), newHead);

        // Check for food
        if (newHead.x == food.x && newHead.y == food.y) {
            return true;  // Food eaten, don't remove tail
        }

        body.pop_back();  // Remove tail if food not eaten
        return true;
    }
};

// Board class
class Board {
    Snake snake;
    Point food;
    int score;

    void gotoxy(int x, int y) {
        cout << "\033[" << y + 1 << ";" << x + 1 << "H";
    }

    void clearScreen() {
        cout << "\033[2J\033[H";
    }

    void spawnFood() {
        bool valid = false;
        while (!valid) {
            int x = rand() % consoleWidth;
            int y = rand() % consoleHeight;
            valid = true;

            // Ensure food doesn't spawn inside the snake
            for (const auto& segment : snake.body) {
                if (segment.x == x && segment.y == y) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                food = Point(x, y);
            }
        }
    }

public:
    Board() : snake(consoleWidth / 2, consoleHeight / 2), score(0) {
        spawnFood();
    }

    void draw() {
        clearScreen();

        // Draw snake
        for (const auto& segment : snake.body) {
            gotoxy(segment.x, segment.y);
            cout << "O";
        }

        // Draw food
        gotoxy(food.x, food.y);
        cout << "o";

        // Display score
        gotoxy(0, consoleHeight);
        cout << "Score: " << score;
    }

    bool update() {
        if (!snake.move(food)) {
            return false;
        }

        // Check if food is eaten
        if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
            score++;
            spawnFood();
        }

        return true;
    }

    void getInput() {
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        char key;
        if (read(STDIN_FILENO, &key, 1) == 1) {
            if (key == 'w') snake.changeDirection(DIR_UP);
            else if (key == 'a') snake.changeDirection(DIR_LEFT);
            else if (key == 's') snake.changeDirection(DIR_DOWN);
            else if (key == 'd') snake.changeDirection(DIR_RIGHT);
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }

    int getScore() const {
        return score;
    }
};

// Main function
int main() {
    srand(time(0));
    Board board;

    while (true) {
        board.draw();
        if (!board.update()) {
            break;
        }
        board.getInput();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    cout << "Game Over! Final Score: " << board.getScore() << endl;
    return 0;
}
