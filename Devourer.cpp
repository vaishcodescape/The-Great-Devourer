//The Great Devourer Snake Game
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>  
#else
#include <termios.h>   
#include <unistd.h>    
#endif

using namespace std;

#define MAX_SIZE 1000

const char UP = 'U';
const char DOWN = 'D';
const char LEFT = 'L';
const char RIGHT = 'R';

const char SNAKE_CHAR = '*';
const char FOOD_CHAR = 'O';

int screenWidth = 50, screenHeight = 20;  

#ifdef _WIN32
int getKeyPress() {
    if (_kbhit()) {
        return _getch();
    }
    return -1;  
}
#else
int getKeyPress() {
    struct termios old, current;
    int character;
    tcgetattr(STDIN_FILENO, &old);  
    current = old;
    current.c_lflag &= ~(ICANON | ECHO);  
    tcsetattr(STDIN_FILENO, TCSANOW, &current);  
    character = getchar();  
    tcsetattr(STDIN_FILENO, TCSANOW, &old);  
    return character;
}
#endif

void clearScreen() {
#ifdef _WIN32
    system("cls");  
#else
    system("clear");  
#endif
}

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
    cout << "Created by vaishcodescape and sam5506";
}

struct Coordinates {
    int x;
    int y;

    Coordinates() {}

    Coordinates(int a, int b) {
        x = a;
        y = b;
    }
};

class SnakeGame {
    int currentLength;
    char currentDirection;

public:
    Coordinates body[MAX_SIZE];

    SnakeGame(int x, int y) {
        currentLength = 1;
        body[0] = Coordinates(x, y);
        currentDirection = RIGHT;
    }

    int getCurrentLength() {
        return currentLength;
    }

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

    bool makeMove(Coordinates food) {
        for (int i = currentLength - 1; i > 0; i--) {
            body[i] = body[i - 1];  
        }

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

        for (int i = 1; i < currentLength; i++) {
            if (body[0].x == body[i].x && body[0].y == body[i].y) {
                return false;
            }
        }

        if (food.x == body[0].x && food.y == body[0].y) {
            body[currentLength] = Coordinates(body[currentLength - 1].x, body[currentLength - 1].y);
            currentLength++;
        }

        if (body[0].x < 0 || body[0].x >= screenWidth || body[0].y < 0 || body[0].y >= screenHeight) {
            return false;
        }

        return true;
    }
};

class GameBoard {
    SnakeGame *snake;
    Coordinates foodItem;
    int scoreCount;

public:
    GameBoard() {
        generateFood();  
        snake = new SnakeGame(screenWidth / 2, screenHeight / 2);
        scoreCount = 0;
    }

    ~GameBoard() {
        delete snake;
    }

    int getCurrentScore() {
        return scoreCount;
    }

    void generateFood() {
        foodItem = Coordinates(rand() % (screenWidth - 2) + 1, rand() % (screenHeight - 2) + 1);
    }

    void displayScore() {
        cout << "Score: " << scoreCount << endl;
    }

    void renderBoard() {
        clearScreen();  

        for (int i = 0; i < screenWidth + 2; i++) {
            cout << "#";
        }
        cout << endl;

        for (int y = 0; y < screenHeight; y++) {
            for (int x = 0; x < screenWidth; x++) {
                if (x == 0 || x == screenWidth - 1) {
                    cout << "#"; 
                } else if (y == 0 || y == screenHeight - 1) {
                    cout << "#"; 
                } else {
                    bool isSnakePrinted = false;
                    for (int i = 0; i < snake->getCurrentLength(); i++) {
                        if (snake->body[i].x == x && snake->body[i].y == y) {
                            cout << SNAKE_CHAR; 
                            isSnakePrinted = true;
                            break;
                        }
                    }
                    if (!isSnakePrinted) {
                        if (foodItem.x == x && foodItem.y == y) {
                            cout << FOOD_CHAR; 
                        } else {
                            cout << " "; 
                        }
                    }
                }
            }
            cout << endl;
        }

        for (int i = 0; i < screenWidth + 2; i++) {
            cout << "#";
        }
        cout << endl;

        displayScore();
    }

    bool updateBoard() {
        bool alive = snake->makeMove(foodItem);
        if (!alive) return false;

        if (foodItem.x == snake->body[0].x && foodItem.y == snake->body[0].y) {
            scoreCount++;
            generateFood();
        }

        return true;
    }

    void processInput() {
        int keyPress = getKeyPress();
        switch (keyPress) {
            case 'w': case 'W':
                snake->updateDirection(UP);
                break;
            case 'a': case 'A':
                snake->updateDirection(LEFT);
                break;
            case 's': case 'S':
                snake->updateDirection(DOWN);
                break;
            case 'd': case 'D':
                snake->updateDirection(RIGHT);
                break;
        }
    }
};

int main() {
    srand(time(0));
    clearScreen();

    displayTitle();

    GameBoard *game = new GameBoard();
    cout << "Snake Game: Use AWSD to play." << endl;
    cout << "Press any key to begin..." << endl;
    getKeyPress();  

    while (game->updateBoard()) {
        game->renderBoard();
        game->processInput();
        this_thread::sleep_for(chrono::milliseconds(100)); 
    }

    cout << "Game Over! Final Score: " << game->getCurrentScore() << endl;
    delete game;
    return 0;
}
