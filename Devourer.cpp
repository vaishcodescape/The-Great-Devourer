#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <windows.h>
#else
#include <ncurses.h>
#endif

using namespace std;

#define MAX_LENGTH 1000

const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

const char GREAT_DEVOURER = '>';
const char FOOD = '*';

int consoleWidth = 50, consoleHeight = 20; // Fixed console dimensions

void initScreen()
{
    #ifdef _WIN32
    // Windows-specific screen initialization
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
    // ncurses initialization for Linux/Mac
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    #endif
}

void printAsciiArt() {
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

    bool move(Point food, Point greatDevourer) {
        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }

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

        for (int i = 1; i < length; i++) {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord) {
                return false;
            }
        }

        if (food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord) {
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
            length++;
        }

        if (greatDevourer.xCoord == body[0].xCoord && greatDevourer.yCoord == body[0].yCoord) {
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
            length += 3;
        }

        if (body[0].xCoord < 0 || body[0].xCoord >= consoleWidth || body[0].yCoord < 0 || body[0].yCoord >= consoleHeight) {
            return false;
        }

        return true;
    }
};

class Board {
    Snake *snake;
    Point food;
    Point greatDevourer;
    int score;

public:
    Board() {
        spawnFood();
        spawnGreatDevourer();
        snake = new Snake(10, 10);
        score = 0;
    }

    ~Board() {
        delete snake;
    }

    int getScore() {
        return score;
    }

    void spawnFood() {
        food = Point(rand() % consoleWidth, rand() % consoleHeight);
    }

    void spawnGreatDevourer() {
        greatDevourer = Point(rand() % consoleWidth, rand() % consoleHeight);
    }

    void displayCurrentScore() {
        #ifdef _WIN32
        gotoxy(consoleWidth / 2, 0);
        cout << "Current Score: " << score;
        #else
        mvprintw(0, consoleWidth / 2, "Current Score: %d", score);
        #endif
    }

    void gotoxy(int x, int y) {
        #ifdef _WIN32
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #else
        move(y, x);
        #endif
    }

    void draw() {
        #ifdef _WIN32
        system("cls");
        #else
        clear();
        #endif

        for (int i = 0; i < snake->getLength(); i++) {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << 'O';
        }

        gotoxy(food.xCoord, food.yCoord);
        cout << FOOD;

        gotoxy(greatDevourer.xCoord, greatDevourer.yCoord);
        cout << GREAT_DEVOURER;

        displayCurrentScore();
    }

    bool update() {
        bool isAlive = snake->move(food, greatDevourer);
        if (!isAlive) return false;

        if (food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord) {
            score++;
            spawnFood();
        }

        if (greatDevourer.xCoord == snake->body[0].xCoord && greatDevourer.yCoord == snake->body[0].yCoord) {
            score += 10;
            spawnGreatDevourer();
        }

        return true;
    }

    void getInput() {
        if (_kbhit()) {
            int key = _getch();
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

int main() {
    srand(time(0));
    initScreen();

    printAsciiArt();

    Board *board = new Board();
    cout << "Welcome to Snake Game!" << endl;
    cout << "Use WASD keys to control the snake." << endl;
    cout << "Press any key to start..." << endl;
    _getch();

   
