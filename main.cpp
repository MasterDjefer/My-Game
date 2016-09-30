#include <iostream>
#include <conio.h>
#include <cstdlib>
#define n 11
#define m 15
using namespace std;


class Table
{
protected:
    void set_null(char mass[n][m])
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                mass[i][j] = ' ';
    }
    void set_side(char mass[n][m])
    {
        for (int i = 0; i < n; ++i)
        {
            mass[i][0] = '#';
            mass[i][m-1] = '#';
        }
        for (int i = 0; i < m; ++i)
        {
            mass[0][i] = '#';
            mass[n-1][i] = '#';
        }
    }
    void show(char mass[n][m])
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
                cout << mass[i][j];
            cout << endl;
        }
    }
};

class Elements
{
protected:
    int head_x;
    int head_y;
    int hand_x;
    int hand_y;
    int target_x;
    int target_y;
protected:
    void set_head(char mass[n][m])
    {
        head_x = 1;
        head_y = 1;
        mass[head_x][head_y] = 'o';
    }

    void set_hand(char mass[n][m])
    {
        hand_x = 5;
        hand_y = 5;
        mass[hand_x][hand_y] = '@';
    }

    void set_target(char mass[n][m])
    {
        target_x = 7;
        target_y = 7;
        mass[target_x][target_y] = '*';
    }
};

class Move : Elements, Table
{
private:
    char mass[n][m];
public:
    Move()
    {
        set_null(mass);
        set_side(mass);
        set_head(mass);
        set_hand(mass);
        set_target(mass);
    }

    void menu()
    {
        system("cls");
        show(mass);

        if (hand_x == target_x && hand_y == target_y)
        {
            cout << "You won!\nPress any key to exit";
            _getch();
            return;
        }

        char choice = _getch();

        switch(choice)
        {
            case 27:
                return;
            case 'd':
                if (mass[head_x][head_y + 1] == ' ')
                {
                    mass[head_x][head_y + 1] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_y++;
                }
                else
                if (mass[head_x][head_y + 1] == '@' && mass[hand_x][hand_y + 1] != '#')
                {
                    mass[hand_x][hand_y + 1] = '@';
                    hand_y++;

                    mass[head_x][head_y + 1] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_y++;
                }
                break;
            case 'a':
                if (mass[head_x][head_y - 1] == ' ')
                {
                    mass[head_x][head_y - 1] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_y--;
                }
                else
                if (mass[head_x][head_y - 1] == '@' && mass[hand_x][hand_y - 1] != '#')
                {
                    mass[hand_x][hand_y - 1] = '@';
                    hand_y--;

                    mass[head_x][head_y - 1] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_y--;
                }
                break;
            case 'w':
                if (mass[head_x - 1][head_y] == ' ')
                {
                    mass[head_x - 1][head_y] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_x--;
                }
                else
                if (mass[head_x - 1][head_y] == '@' && mass[hand_x - 1][hand_y] != '#')
                {
                    mass[hand_x - 1][hand_y] = '@';
                    hand_x--;

                    mass[head_x - 1][head_y] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_x--;
                }
                break;
            case 's':
                if (mass[head_x + 1][head_y] == ' ')
                {
                    mass[head_x + 1][head_y] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_x++;
                }
                else
                if (mass[head_x + 1][head_y] == '@' && mass[hand_x + 1][hand_y] != '#')
                {
                    mass[hand_x + 1][hand_y] = '@';
                    hand_x++;

                    mass[head_x + 1][head_y] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_x++;
                }
                break;
        }
        menu();
    }
};



int main()
{
    Move my;
    my.menu();

    return 0;
}
