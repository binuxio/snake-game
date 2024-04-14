#include "SnakeClass.h"
#include <random>
#include <time.h>

static int GameSpeed = 1;
int Snake::BodyID = 0;

void Snake::run(Snake *HEAD)
{
    Snake::drawFrame();
    // SetFood(HEAD);
    draw(HEAD);
    char Eing = 's';
    char LastEing = Eing;

#pragma region Loop
    while (!GameOver)
    {
        draw(HEAD);
        if (_kbhit())
        {
            Eing = getch();
            if (!(Eing == 'w' || Eing == 's' || Eing == 'd' || Eing == 'a'))
            {
                Eing = LastEing;
                cout << '\a';
            }
        }

        if (Eing == 'w')
        {
            --HEAD->SnakeY;
            GameSpeed = SpeedY;
        }
        else if (Eing == 's')
        {
            ++HEAD->SnakeY;
            GameSpeed = SpeedY;
        }
        if (Eing == 'd')
        {
            ++HEAD->SnakeX;
            GameSpeed = SpeedX;
        }
        else if (Eing == 'a')
        {
            --HEAD->SnakeX;
            GameSpeed = SpeedX;
        }
        SetBodyPos(HEAD, ScreenArr, Eing);
        LastEing = Eing;
    }
#pragma endregion Loop
}

void draw(Snake *HEAD)
{
    for (int y = 0; y <= Height; y++)
    {
        for (int x = 0; x <= Width + 1; x++)
            HEAD->ScreenArr[x][y] = HEAD->FrameArr[x][y];
    }

    HEAD->ScreenArr[HEAD->get_FoodX()][HEAD->get_FoodY()] = FOOD;
    HEAD->ScreenArr[HEAD->get_SnakeX()][HEAD->get_SnakeY()] = SnakeHead;
    Snake *head = HEAD;
    while (head->NextBody != nullptr)
    {
        head = head->NextBody;
        cout << "draw SnakeX: " << head->SnakeX << endl;
        cout << "draw SnakeY: " << head->SnakeY << endl;
        // head->ScreenArr[head->get_SnakeX()][head->get_SnakeY()] = SnakeHead;
    }

    std::string Screen = "";
    for (int y = 0; y <= Height; y++)
    {
        for (int x = 0; x <= Width + 1; x++)
            Screen += HEAD->ScreenArr[x][y];
    }

    Sleep(GameSpeed);
    ClearDisplay;
    std::cout << "Score: " << Score << std::endl;
    std::cout << "Width: " << Width << std::endl;
    std::cout << "Height: " << Height << std::endl
              << std::endl;
    std::cout << "SnakeX: " << HEAD->get_SnakeX() << std::endl;
    std::cout << "SnakeY: " << HEAD->get_SnakeY() << std::endl;
    std::cout << "FOODX: " << HEAD->get_FoodX() << std::endl;
    std::cout << "FOODY: " << HEAD->get_FoodY() << std::endl
              << std::endl;
    std::cout << Screen;
}

Snake *BodyAt(Snake *HEAD, int pos)
{
    for (int p = 1; p < pos; p++)
        HEAD = HEAD->NextBody;
    return HEAD;
}

void SetPositions(Snake *HEAD)
{
    int BodyL = Bodylenght(HEAD);
    while (HEAD->NextBody != nullptr)
    {
        Snake *head = BodyAt(HEAD, BodyL--);
        std::cout << head->NextBody << std::endl;
        // head->NextBody->SnakeX = head->SnakeX;
        std::cout << "headSnakeposX: " << head << std::endl;
        HEAD = head;
    }
    cout << "SetPositons - finish" << endl;
}

void SetBodyPos(Snake *&HEAD, char ScreenArr[][Height + 2], char Eing)
{
    if (HEAD->get_SnakeX() == Width)
        HEAD->set_SnakeX(1);
    else if (HEAD->get_SnakeX() == 0)
        HEAD->set_SnakeX(Width - 1);
    if (HEAD->get_SnakeY() == Height)
        HEAD->set_SnakeY(1);
    else if (HEAD->get_SnakeY() == 0)
        HEAD->set_SnakeY(Height - 1);

    if (AteFood(HEAD))
    {
        NewBody(HEAD);
        SetFood(HEAD);
    }

    SetPositions(HEAD);

    cout << "SetBodyPos" << endl;
}

void NewBody(Snake *&HEAD)
{
    if (HEAD->NextBody != nullptr)
    {
        Snake *head = HEAD;
        do
        {
            head = head->NextBody;
            std::cout << "NewBodyStart" << endl;
        } while (head->NextBody != nullptr);
        Snake *NewBody = new Snake;
        head->NextBody = NewBody;
        std::cout << "NewBodyCreated" << endl;
    }
    else
    {
        Snake *NewBody = new Snake;
        HEAD->NextBody = NewBody;
        std::cout << "first newBody\n";
    }
}

int Bodylenght(Snake *HEAD)
{
    int i = 0;
    while (HEAD != nullptr)
    {
        HEAD = HEAD->NextBody;
        ++i;
    }
    return i;
}

int GetRandomX()
{
    srand(time(0) + r++);
    int n = rand() % (Width - 1) + 1;
    return n;
}
int GetRandomY()
{
    srand(time(0) + r++);
    int n = rand() % (Height - 1) + 1;
    return n;
}

void SetFood(Snake *HEAD)
{
    if (HEAD->NextBody != nullptr)
    {
    SetAgainX:
        Snake *headX = HEAD;
        int x = GetRandomX();
        while (headX->NextBody != nullptr)
        {
            if (headX->get_SnakeX() == x)
                goto SetAgainX;
            headX = headX->NextBody;
        }
        HEAD->set_FoodX(x);
    SetAgainY:
        Snake *headY = HEAD;
        int y = GetRandomY();
        while (headY->NextBody != nullptr)
        {
            if (headY->get_SnakeY() == y)
                goto SetAgainY;
            headY = headY->NextBody;
        }
        HEAD->set_FoodY(y);
        cout << "NewFoodSet x y: " << x << "  " << y << endl;
    }
    else
    {
        // SetAgainX1:
        //     int x = GetRandomX();
        //     if (HEAD->get_SnakeX() == x)
        //         goto SetAgainX1;
        //     HEAD->set_FoodX(x);
        // SetAgainY1:
        //     int y = GetRandomY();
        //     if (HEAD->get_SnakeY() == y)
        //         goto SetAgainY1;
        //     HEAD->set_FoodY(y);

        cout << "First Rondomly Food Set" << std::endl;
    }
}

void Snake::drawFrame()
{
    for (int y = 0; y <= Height; y++)
    {
        if (!(y == 0 || y == Height))
        {
            FrameArr[0][y] = '|';
            for (int x = 1; x < Width; x++)
                FrameArr[x][y] = ' ';
            FrameArr[Width][y] = '|';
            FrameArr[Width + 1][y] = '\n';
        }
        else
        {
            if (y == 0)
            {
                for (int x = 0; x <= Width; x++)
                    FrameArr[x][y] = '_';
                FrameArr[Width + 1][y] = '\n';
            }
            else
            {
                for (int x = 0; x <= Width; x++)
                {
                    FrameArr[x][y] = 'Z';
                }
                FrameArr[Width + 1][y] = '\n';
            }
        }
    }

    cout << "Frame drawed" << endl;
}

bool AteFood(Snake *HEAD)
{
    if (!(HEAD->get_SnakeX() == HEAD->get_FoodX() && HEAD->get_SnakeY() == HEAD->get_FoodY()))
        return false;
    else
    {
        return true;
        ++Score;
    }
}