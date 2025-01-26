//The-Great-Devourer Snake Game
//Made by: Vaishcodescape and sam5506
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
    cout << " TTTTT H   H  EEEEE      GGG   RRRR    EEEEE   AAAAA  TTTTT       DDDD   EEEEE   V     V  OOO   U   U  RRRR    EEEEE   RRRR   \n";
    cout << "   T    H   H  E          G      R   R   E       A   A    T        D   D  E        V   V  O   O  U   U  R   R   E       R   R  \n";
    cout << "   T    HHHHH  EEEE       G  GG  RRRR    EEEE    AAAAA    T        D   D  EEEE       V    O   O  U   U  RRRR    EEEE    RRRR   \n";
    cout << "   T    H   H  E          G   G  R  R    E       A   A    T        D   D  E        V   V  O   O  U   U  R  R    E       R  R   \n";
    cout << "   T    H   H  EEEEE      GGG    R  R    EEEEE   A   A    T        DDDD   EEEEE      V     OOO    UUU   R   R   EEEEE   R   R  \n";

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

int main()
{
    printsnake();
    initScreen();
    return 0;
}