#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
using namespace std;


bool GameOver;
const int Width = 30;
const int Height = 20;
int x,y, FruitX, FruitY, score;
int TailX[100], TailY[100];
int nTail;
enum eDirecton { Stop = 0, Left, Right, Up, Down};
eDirecton dir;

void Setup()
{
    srand(time(NULL));
    GameOver = false;
    dir = Stop;
    x = Width / 2;
    y = Height / 2;
    FruitX = rand() % Width;
    FruitY = rand() % Height;
    score = 0;
    nTail = 0;
}
void Draw()
{
    system("cls");
    // cout << "First game with c++ without a game engine :)" << endl;
    cout << "Score: " << score << endl;
    for (int i = 0; i < Width+2; i++)
        cout << "#";
        cout << endl;
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            if (j == 0)
            
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == FruitY && j == FruitX)
                cout << "A";    
             else
             {

                bool Print = false;

                for (int k = 0; k < nTail; k++)
                {
                    if (TailX[k] == j && TailY[k] == i)
                     {
                        cout << "o";
                        Print = true;
                    }
                }         

                if (!Print)
                    {
                        cout << " ";
                    }
             }
        
            if (j == Width - 1)
            
                cout << "#";
        }
        cout << endl;
    }
    
    for (int i = 0; i < Width+2; i++)
        cout << "#";
        cout << endl;
    
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
         case 'w':
            dir = Up;
            break;
         case 'a':
            dir = Left;
            break;
         case 's':
            dir = Down;
            break;
         case 'd':
            dir = Right;
            break; 
         case 'x':
            GameOver = true;
            break;
         default:
            break;
        }
    }
}
void Logic()
{

    int PrevX = TailX[0];
    int PrevY = TailY[0];
    int Prev2X, Prev2Y;
    TailX[0] = x;
    TailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        Prev2X = TailX[i];
        Prev2Y = TailY[i];
        TailX[i] = PrevX;
        TailY[i] = PrevY;
        PrevX = Prev2X;
        PrevY = Prev2Y;
    }
    

    switch (dir)
    {
        case Left:
            x--;
            break;
        case Right:
            x++;
            break;
        case Up:
            y--;
            break;        
        case Down:
            y++;
            break;
        default:
            break;
    }
    if (x > Width || x < 0 || y > Height || y < 0)
    {
        GameOver = true;
    }

    for (int i = 0; i < nTail; i++)
    {
        if (TailX[i] == x && TailY[i] == y)
        {
            GameOver = true;
        }
    }
    
    if (x == FruitX && y == FruitY)
    {
        score += 10;
        FruitX = rand() % Width;
        FruitY = rand() % Height;
        nTail++;
    }
    
}

void PlayGame()
{

    Setup();

    while (!GameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }

}

int main()
{
    
    bool PlayAgain = true;
    while (PlayAgain)
    {
        PlayGame();

        cout << "\nYour score was: " << score;
        cout << "\nPlay again? (y/n)\n";
        char answer;
        cin >> answer;
        if (tolower(answer) == 'y')
        {
            PlayGame();
        }

        else if (tolower(answer) != 'y')
        {
            PlayAgain = false;
        }

    }
    
    return 0;
}
