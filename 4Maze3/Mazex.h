#include <iostream>
#include <ctime> 
#include <Windows.h> 
#include <conio.h> 
#include <string>
using namespace std;

enum MazeObject { HALL, WALL, COIN, ENEMY, BORDER };
enum Color { DARKGREEN = 2, YELLOW = 14, RED = 12, BLUE = 9, WHITE = 15, DARKYELLOW = 6, DARKRED = 4 };
enum KeyCode { ENTER = 13, ESCAPE = 27, SPACE = 32, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80 };

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); 

void SetCursor(int x, int y, int color, string text)
{
    COORD position;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, color);
    cout << text;
    
}

void System(const char* str)
{
    system(str);
}

void Console()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100; 
    SetConsoleCursorInfo(h, &info);
}

void Message(LPCSTR text, LPCSTR text2)
{
    MessageBoxA(0, text, text2, MB_OK);
}