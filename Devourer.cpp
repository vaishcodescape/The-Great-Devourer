//The-Great-Devourer Snake Game
//Made by: vaishcodescape and sam5506

#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

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
    cin >>;
}

int consoleWidth, consoleHeight;

void initScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

struct coord{
    int xcoord;
    int ycoord;
    Point()
    {

    }
    Point(int x, int y){
        xcoord = x;
        ycoord = y;

    }

};

class Snake{
    private:
    int length;
    char direction;

    public:
    Point body[MAX_LENGTH];
    Snake(int x,int y)
    {
        length = 1;
        body[0] = Point(x,y);
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
            {
                direction = newDirection;
            }
            break;

        case DIR_DOWN:
            if (direction != DIR_UP)
            {
                direction = newDirection;
            }
            break;

        case DIR_LEFT:
            if (direction != DIR_RIGHT)
            {
                direction = newDirection;
            }
            break;

        case DIR_RIGHT:
            if (direction != DIR_LEFT)
            {
                direction = newDirection;
            }
            break;

        default:
            
            break;
    }
    bool move(Point food)
    {
        for(int i = length -1 ;i>0;i--)
        {
            body[i] = body[i-1];
            
        }

    }
}
};

class Board{
    private:
    Snake *snake;
    const char SNAKE_BODY = "^";
    Point food;
    const char FOOD = "*"
    int score;

    public:
    Board(){
        spawnFood();
        snake = new Snake(10,10);
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
        food = Point(x,y);

    }

    void gotoxy(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPostion(GetStdHandle(STD_OUTPUT_HANDLE),coord);

    }

     void draw(){
        system("cls");
        for(int i=0;i<snake->getLength();i++)
        {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout<<SNAKE_BODY;
        }

        gotoxy(food.xCoord, food.yCoord);
        cout<<FOOD;

        displayCurrentScore();
    }



};
int main()
{
    printsnake();
    initScreen();
    Board *board = new Board();
    return 0;
}
