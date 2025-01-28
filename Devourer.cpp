//The-Great-Devourer Snake Game
//Made by: vaishcodescape and sam5506
#include <iostream>
#include <vector>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

#define MAX_LENGTH 1000

const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

void printsnake()
{
    cout << " TTTTT  H   H  EEEEE      GGG   RRRR    EEEEE   AAAAA   TTTTT      DDDD   EEEEE   V     V  OOO   U   U  RRRR    EEEEE   RRRR   \n";
    cout << "   T    H   H  E          G      R   R   E       A   A    T        D   D  E        V   V  O   O  U   U  R   R   E       R   R  \n";
    cout << "   T    HHHHH  EEEE       G  GG  RRRR    EEEE    AAAAA    T        D   D  EEEE       V    O   O  U   U  RRRR    EEEE    RRRR   \n";
    cout << "   T    H   H  E          G   G  R  R    E       A   A    T        D   D  E        V   V  O   O  U   U  R  R    E       R  R   \n";
    cout << "   T    H   H  EEEEE      GGG    R  R    EEEEE   A   A    T        DDDD   EEEEE      V     OOO    UUU   R   R   EEEEE   R   R  \n";

    cout << "Press Enter to Continue.....";
    cin.ignore();
}

int consoleWidth, consoleHeight;

void initScreen()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    consoleWidth = w.ws_col;
    consoleHeight = w.ws_row;
}

struct Point
{
    int xCoord;
    int yCoord;

    Point() : xCoord(0), yCoord(0) {}

    Point(int x, int y) : xCoord(x), yCoord(y) {}
};

class Snake
{
private:
    int length;
    char direction;

public:
    Point body[MAX_LENGTH];

    Snake(int x, int y)
    {
        length = 1;
        body[0] = Point(x, y);
        direction = DIR_RIGHT;
    }

    int getLength()
    {
        return length;
    }

    void changeDirection(char newDirection)
    {
        switch (newDirection)
        {
        case DIR_UP:
            if (direction != DIR_DOWN)
                direction = newDirection;
            break;
        case DIR_DOWN:
            if (direction != DIR_UP)
                direction = newDirection;
            break;
        case DIR_LEFT:
            if (direction != DIR_RIGHT)
                direction = newDirection;
            break;
        case DIR_RIGHT:
            if (direction != DIR_LEFT)
                direction = newDirection;
            break;
        default:
            break;
        }
    }

    bool move(Point food)
    {
        for (int i = length - 1; i > 0; i--)
        {
            body[i] = body[i - 1];
        }

        switch (direction)
        {
        case DIR_UP:
            body[0].yCoord--;
            break;
        case DIR_DOWN:
            body[0].yCoord++;
            break;
        case DIR_LEFT:
            body[0].xCoord--;
            break;
        case DIR_RIGHT:
            body[0].xCoord++;
            break;
        }

        if (body[0].xCoord == food.xCoord && body[0].yCoord == food.yCoord)
        {
            length++;
            return true;
        }

        return false;
    }
};

class Board
{
private:
    Snake *snake;
    Point food;
    int score;

    void gotoxy(int x, int y)
    {
        cout << "\033[" << y << ";" << x << "H";
    }

    void clearScreen()
    {
        cout << "\033[2J\033[H";
    }

public:
    Board()
    {
        spawnFood();
        snake = new Snake(10, 10);
        score = 0;
    }

    ~Board()
    {
        delete snake;
    }

    int getScore()
    {
        return score;
    }

    void spawnFood()
    {
        int x = rand() % consoleWidth;
        int y = rand() % consoleHeight;
        food = Point(x, y);
    }

    void draw()
    {
        clearScreen();
        for (int i = 0; i < snake->getLength(); i++)
        {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << "^";
        }

        gotoxy(food.xCoord, food.yCoord);
        cout << "*";

        gotoxy(0, consoleHeight);
        cout << "Score: " << score << endl;
    }

    void update()
    {
        if (snake->move(food))
        {
            score++;
            spawnFood();
        }
    }
};

int main()
{
    printsnake();
    initScreen();
    Board *board = new Board();

    while (true)
    {
        board->draw();
        usleep(100000); // Delay to control game speed
        board->update();
    }

    delete board;
    return 0;
}
