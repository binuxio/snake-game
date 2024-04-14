#pragma once

#include <iostream>
using namespace std;
#include <iomanip>
#include <Windows.h>
#include <string>
#include <conio.h>

#define SpeedY 20 // standard 80
#define SpeedX 0
#define SnakeHead 'O'
#define FOOD 'X'
#define Height 20 // Height alway even Number, else Frame does not fit with Snake movement
#define Width (2 * Height + 10)
#define ArrSizeY (Height + 2)
#define ArrSizeX (Width + 2)
#define ClearDisplay system("cls")
static int r = 1;
static int Score = 0;
static bool GameOver = false;

class Snake
{
private:
    int FoodX = 24;
    int FoodY = 10;

public:
    int SnakeX = 1;
    int SnakeY = 1;
    static int BodyID;
    Snake *NextBody = nullptr;
    char ScreenArr[ArrSizeX][ArrSizeY];
    char FrameArr[ArrSizeX][ArrSizeY];
    Snake() { ++BodyID; }
    Snake(int x, int y) : SnakeX{x}, SnakeY{y}, NextBody{nullptr} { ++BodyID; }

    void run(Snake *);
    int get_FoodX() { return FoodX; }
    int get_FoodY() { return FoodY; }
    void set_FoodX(int x) { FoodX = x; }
    void set_FoodY(int y) { FoodY = y; }
    int get_SnakeX() { return SnakeX; }
    int get_SnakeY() { return SnakeY; }
    void set_SnakeX(int x) { SnakeX = x; }
    void set_SnakeY(int y) { SnakeY = y; }
    void set_next(Snake *n) { NextBody = n; }
    void drawFrame();
    Snake *get_next() { return NextBody; }
};

void SetBodyPos(Snake *&, char[][Height + 2], char);
void SetPositions();
void NewBody(Snake *&);
void SetFood(Snake *);
bool AteFood(Snake *);
void draw(Snake *);
int GetRandomX();
int GetRandomY();
int Bodylenght(Snake *);
Snake *BodyAt(Snake *, int);
#pragma region oldCode
// for (int y = 0; y <= Height; y++)
// {
//     if (!(y == 0 || y == Height))
//         Screen += '|' + std::string(Width - 2, ' ') + '|';
//     else
//     {
//         if (y == 0)
//         {
//             // Screen += " " + Frame(Width - 2, '_', 0xB);
//             // SetConsoleTextAttribute(FRAME, 2);
//             Screen += " " + std::string(Width - 2, '_');
//         }
//         else
//             Screen += std::string(Width, 'Z');
//     }
//     Screen += '\n';
// }

// void Snake::draw(Snake *HEAD)
// {
//     ClearDisplay;
//     Snake *head = HEAD;
//     std::string Screen = "";
//     std::cout << "\tWidth: " << Width << endl;
//     std::cout << "\tHeight: " << Height << endl
//               << endl;
//     std::cout << "\tSnakeX: " << head->SnakeX << endl;
//     std::cout << "\tSnakeY: " << head->SnakeY << endl;

//     if (head->SnakeX == Width)
//         head->SnakeX = 1;
//     else if (head->SnakeX == -1)
//         head->SnakeX = Width - 2;

//     if (head->SnakeY == Height)
//         head->SnakeY = 1;
//     else if (head->SnakeY == 0)
//         head->SnakeY = Height - 1;

//     for (int y = 0; y <= Height; y++)
//     {
//         SetConsoleTextAttribute(text, 0xF);
//         Screen += "\t";
//         if (!(y == 0 || y == Height))
//         {
//             Screen += '|';
//             if (y == head->FoodY)
//             {
//                 for (int x = 1; x <= Width - strlen(SnakeHead) - 1; x++)
//                 {
//                     if (x != head->SnakeX)
//                         Screen += ' ';
//                     else
//                         Screen += FOOD;
//                 }
//             }

//             if (y == head->SnakeY)
//             {
//                 // Storage Body
//                 for (int x = 1; x <= Width - strlen(SnakeHead) - 1; x++)
//                 {
//                     if (x != head->SnakeX)
//                         Screen += ' ';
//                     else
//                         Screen += SnakeHead;
//                 }
//             }
//             else
//                 Screen += std::string(Width - 2, ' ');
//             Screen += '|';
//         }
//         else
//         {
//             if (y == 0)
//             {
//                 // Screen += " " + Frame(Width - 2, '_', 0xB);
//                 SetConsoleTextAttribute(FRAME, 2);
//                 Screen += " " + std::string(Width - 2, '_');
//             }
//             else
//                 Screen += std::string(Width, 'Z');
//         }
//         Screen += '\n';
//     }
//     std::cout << Screen << '\n';
// }

// for (int y = 1; y < Height; y++)
// {
//     for (int x = 1; x < Width; x++)
//     {
//         // if (x == HEAD->FoodX && y == HEAD->FoodY)
//         //     Screen[x * (y - 1) + x] = FOOD;

//         if (x == head->SnakeX && y == head->SnakeY)
//             Screen[x * y + x] = SnakeHead;
//     }
// }

// do
//         {
//             do
//             {
//                 srand(time(0));
//                 int x = rand() % (Width - 2) + 1;
//                 if (x % 2 == 0)
//                     x++;
//                 HEAD->set_FoodX(x);
//                 int y = rand() % Height + 1;
//                 HEAD->set_FoodY(y);
//                 cout << "x " << x << " y " << y << std::endl;
//             } while (!(head->get_FoodX() == head->get_SnakeX() && head->get_FoodX() == head->get_SnakeY()));
//             head = head->NextBody;
//         } while (head->NextBody != nullptr);

// while (head->NextBody != nullptr)
// {

//     head = head->NextBody;
//     head->set_SnakeX(prevhead->get_SnakeX());
//     head->set_SnakeY(prevhead->get_SnakeY() + 1);
//     cout << "While(ptr != 0): " << head->NextBody << " x: "
//          << " y: " << head->BodyID << std::endl;
//     prevhead = prevhead->NextBody;
// }
#pragma endregion
