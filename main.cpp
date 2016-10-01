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
    int target_x;
    int target_y;
    static const int number = 8;
    int hand[number];
    int target[number];
protected:
    void set_head(char mass[n][m])
    {
        head_x = 1;
        head_y = 1;
        mass[head_x][head_y] = 'o';
    }
    void set_hand(char mass[n][m])
    {
        hand[0] = 3; hand[1] = 2;
        hand[2] = 8; hand[3] = 8;
        hand[4] = 6; hand[5] = 8;
        hand[6] = n-3; hand[7] = m-5;

        for (int i = 0; i < number; i+=2)
            mass[hand[i]][hand[i+1]] = '@';
    }
    void set_target(char mass[n][m])
    {
        target[0] = 3; target[1] = 4;
        target[2] = 3; target[3] = 5;
        target[4] = 3; target[5] = 6;
        target[6] = 3; target[7] = 7;

        for (int i = 0; i < number; i+=2)
            mass[target[i]][target[i+1]] = '*';
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

        char choice = _getch();

        switch(choice)
        {
            case 27:
                return;
            case 'd':
                if (mass[head_x][head_y + 1] == ' ' || mass[head_x][head_y + 1] == '*')
                {
                    mass[head_x][head_y + 1] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_y++;
                }
                else
                if (mass[head_x][head_y + 1] == '@')
                {
                    int temp = search(head_x, head_y + 1);

                    if (mass[hand[temp]][hand[temp + 1] + 1] != '#' && mass[hand[temp]][hand[temp + 1] + 1] != '@')
                    {
                        mass[hand[temp]][hand[temp + 1] + 1] = '@';
                        hand[temp + 1]++;

                        mass[head_x][head_y + 1] = 'o';
                        mass[head_x][head_y] = ' ';
                        head_y++;
                    }
                }
                break;
            case 'a':
                if (mass[head_x][head_y - 1] == ' ' || mass[head_x][head_y - 1] == '*')
                {
                    mass[head_x][head_y - 1] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_y--;
                }
                else
                if (mass[head_x][head_y - 1] == '@')
                {
                    int temp = search(head_x, head_y - 1);

                    if (mass[hand[temp]][hand[temp + 1] - 1] != '#' && mass[hand[temp]][hand[temp + 1] - 1] != '@')
                    {
                        mass[hand[temp]][hand[temp + 1] - 1] = '@';
                        hand[temp + 1]--;

                        mass[head_x][head_y - 1] = 'o';
                        mass[head_x][head_y] = ' ';
                        head_y--;
                    }
                }
                break;
            case 'w':
                if (mass[head_x - 1][head_y] == ' ' || mass[head_x - 1][head_y] == '*')
                {
                    mass[head_x - 1][head_y] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_x--;
                }
                else
                if (mass[head_x - 1][head_y] == '@')
                {
                    int temp = search(head_x -1, head_y);

                    if (mass[hand[temp] - 1][hand[temp + 1]] != '#' && mass[hand[temp] - 1][hand[temp + 1]] != '@')
                    {
                        mass[hand[temp] - 1][hand[temp + 1]] = '@';
                        hand[temp]--;

                        mass[head_x - 1][head_y] = 'o';
                        mass[head_x][head_y] = ' ';
                        head_x--;
                    }
                }
                break;
            case 's':
                if (mass[head_x + 1][head_y] == ' ' || mass[head_x + 1][head_y] == '*')
                {
                    mass[head_x + 1][head_y] = 'o';
                    mass[head_x][head_y] = ' ';
                    head_x++;
                }
                else
                if (mass[head_x + 1][head_y] == '@')
                {
                    int temp = search(head_x + 1, head_y);

                    if (mass[hand[temp] + 1][hand[temp + 1]] != '#' && mass[hand[temp] + 1][hand[temp + 1]] != '@')
                    {
                        mass[hand[temp] + 1][hand[temp + 1]] = '@';
                        hand[temp]++;

                        mass[head_x + 1][head_y] = 'o';
                        mass[head_x][head_y] = ' ';
                        head_x++;
                    }
                }
                break;
        }
        for (int i = 0; i < number; i+=2)
        {
            if (mass[target[i]][target[i + 1]] == ' ')
                mass[target[i]][target[i + 1]] = '*';
        }

        menu();
    }

    int search(int a, int b)
    {
        for (int i = 0; i < n; i+=2)
            if (hand[i] == a && hand[i+1] == b)
                return i;
    }
};



int main()
{
    Move my;
    my.menu();

    return 0;
}
