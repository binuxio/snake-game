#include <iostream>
#include "SnakeClass.h"
using namespace std;

int main()
{
    Snake *HEAD = new Snake(Width / 2, Height / 2);
    HEAD->run(HEAD);
    cin.get();
    return 0;
}