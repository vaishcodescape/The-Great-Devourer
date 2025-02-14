// The Great Devourer Snake Game
// Created by vaishcodescape and sam5506

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <atomic>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

#define MAX_SIZE 1000
const char UP = 'w';
const char DOWN = 's';
const char LEFT = 'a';
const char RIGHT = 'd';
const char SNAKE_CHAR = '*';
const char FOOD_CHAR = 'O';

int screenWidth = 50, screenHeight = 20;
atomic<bool> gameOver(false);
atomic<char> currentDirection(RIGHT);
int highestScore = 0;

#ifdef _WIN32
int getKeyPress() {
    if (_kbhit()) {
        return _getch();
    }
    return -1;
}
#else
int getKeyPress() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void loadingScreen() {
    clearScreen();
    cout << " TTTTT  H   H  EEEEE      GGG   RRRR    EEEEE   AAAAA   TTTTT      DDDD   EEEEE   V     V  OOO   U   U  RRRR    EEEEE   RRRR   \n";
    cout << "   T    H   H  E          G      R   R   E       A   A    T        D   D  E        V   V  O   O  U   U  R   R   E       R   R  \n";
    cout << "   T    HHHHH  EEEE       G  GG  RRRR    EEEE    AAAAA    T        D   D  EEEE       V    O   O  U   U  RRRR    EEEE    RRRR   \n";
    cout << "   T    H   H  E          G   G  R  R    E       A   A    T        D   D  E        V   V  O   O  U   U  R  R    E       R  R   \n";
    cout << "   T    H   H  EEEEE      GGG    R  R    EEEEE   A   A    T        DDDD   EEEEE      V     OOO    UUU   R   R   EEEEE   R   R  \n";
    cout << endl;
    cout << "  ---_ ......._-_--.\n";
    cout << "      (|\\ /      / /| \\  \\  \n";
    cout << "      /  /     .'  -=-'   `.  \n";
    cout << "     /  /    .'             )  \n";
    cout << "   _/  /   .'        _.)   /  \n";
    cout << "  / o   o        _.-' /  .'  \n";
    cout << "  \\          _.-'    / .'*|  \n";
    cout << "   \\______.-'//    .'.' \\*|  \n";
    cout << "    \\|  \\ | //   .'.' _ |*|  \n";
    cout << "     `   \\|//  .'.'_ _ _|*|  \n";
    cout << "      .  .// .'.' | _ _ \\*|  \n";
    cout << "      \\`-|\\_/ /    \\ _ _ \\*\\  \n";
    cout << "       `/'\\__/      \\ _ _ \\*\\  \n";
    cout << "      /^|            \\ _ _ \\*  \n";
    cout << "     '  `             \\ _ _ \\n  \n";
    
    cout << "THE GREAT DEVOURER\n";
    cout << "Snake Game\n";
    cout << "Created by vaishcodescape and sam5506\n\n";

    for (int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
        cout.flush();
    }
    cout << "\n";
    this_thread::sleep_for(chrono::milliseconds(500));

    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush input buffer
    cin.get(); // Wait for Enter key
}

struct Coordinates {
    int x, y;
    Coordinates() {}
    Coordinates(int a, int b) : x(a), y(b) {}
};

class SnakeGame {
    int length;
    Coordinates body[MAX_SIZE];

public:
    SnakeGame(int x, int y) : length(1) {
        body[0] = Coordinates(x, y);
    }

    void updateDirection(char newDir) {
        if ((newDir == UP && currentDirection != DOWN) ||
            (newDir == DOWN && currentDirection != UP) ||
            (newDir == LEFT && currentDirection != RIGHT) ||
            (newDir == RIGHT && currentDirection != LEFT)) {
            currentDirection = newDir;
        }
    }

    bool move(Coordinates &food) {
        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }

        switch (currentDirection.load()) {
            case UP: body[0].y--; break;
            case DOWN: body[0].y++; break;
            case LEFT: body[0].x--; break;
            case RIGHT: body[0].x++; break;
        }

        // Check for collision with walls
        if (body[0].x < 1 || body[0].x >= screenWidth - 1 || body[0].y < 1 || body[0].y >= screenHeight - 1) {
            return false;
        }

        // Check for collision with itself
        for (int i = 1; i < length; i++) {
            if (body[0].x == body[i].x && body[0].y == body[i].y) {
                return false;
            }
        }

        // Check if food is eaten
        if (food.x == body[0].x && food.y == body[0].y) {
            body[length] = body[length - 1];
            length++;
            food = Coordinates(rand() % (screenWidth - 2) + 1, rand() % (screenHeight - 2) + 1);
        }
        return true;
    }

    void render(Coordinates food) {
        clearScreen();
        for (int y = 0; y < screenHeight; y++) {
            for (int x = 0; x < screenWidth; x++) {
                if (x == 0 || x == screenWidth - 1 || y == 0 || y == screenHeight - 1) {
                    cout << "#";
                } else {
                    bool isSnake = false;
                    for (int i = 0; i < length; i++) {
                        if (body[i].x == x && body[i].y == y) {
                            cout << SNAKE_CHAR;
                            isSnake = true;
                            break;
                        }
                    }
                    if (!isSnake) cout << (food.x == x && food.y == y ? FOOD_CHAR : ' ');
                }
            }
            cout << endl;
        }
        cout << "Score: " << length - 1 << " | Highest Score: " << highestScore << endl;
    }

    int getScore() { return length - 1; }
};

void processInput() {
    while (!gameOver) {
        int key = getKeyPress();
        if (key == UP || key == DOWN || key == LEFT || key == RIGHT) {
            currentDirection = key;
        }
    }
}

void runGame() {
    loadingScreen();
    
    do {
        gameOver = false;
        SnakeGame snake(screenWidth / 2, screenHeight / 2);
        Coordinates food(rand() % (screenWidth - 2) + 1, rand() % (screenHeight - 2) + 1);
        thread inputThread(processInput);

        while (!gameOver) {
            if (!snake.move(food)) {
                gameOver = true;
            }
            snake.render(food);
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        inputThread.detach();  // Ensure thread terminates properly
        highestScore = max(highestScore, snake.getScore());
        
        cout << "Game Over! Your Score: " << snake.getScore() << "\n";
        cout << "Press R to restart or any other key to exit.\n";

        char choice;
        cin >> choice;
        if (toupper(choice) != 'R') break;

    } while (true);
}

int main() {
    srand(time(0));
    runGame();
    return 0;
}