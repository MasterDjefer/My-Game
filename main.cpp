#include <iostream>
#include <conio.h>
#include <cstdlib>
#define n 8
#define m 8
using namespace std;

class Table
{
protected:
    void set_null(char mass[][m])
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
    void set_side_level1(char mass[n][m])
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
        for (int i = 1; i < 4; ++i)
            for (int j = 1; j < 3; ++j)
                mass[i][j] = '#';
        for (int i = 1; i < 3; ++i)
            for (int j = 4; j < 7; ++j)
                mass[i][j] = '#';
        for (int i = 5; i < 7; ++i)
            for (int j = 1; j < 4; ++j)
                mass[i][j] = '#';
        for (int i = 4; i < 7; ++i)
            for (int j = 5; j < 7; ++j)
                mass[i][j] = '#';

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
    int number;
    int hand[100];
    int target[100];
protected:
    void set_elements_level1()
    {
        number = 8;
        head_x = 4;
        head_y = 4;
        hand[0] = 3; hand[1] = 3;
        hand[2] = 3; hand[3] = 5;
        hand[4] = 4; hand[5] = 3;
        hand[6] = 5; hand[7] = 4;
        target[0] = 1; target[1] = 3;
        target[2] = 3; target[3] = 6;
        target[4] = 4; target[5] = 1;
        target[6] = 6; target[7] = 4;
    }
    void set_head(char mass[n][m])
    {        
        mass[head_x][head_y] = 'o';
    }
    void set_hand(char mass[n][m])
    {
        for (int i = 0; i < number; i+=2)
            mass[hand[i]][hand[i+1]] = '@';
    }
    void set_target(char mass[n][m])
    {
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
        set_side_level1(mass);
        set_elements_level1();
        set_head(mass);
        set_hand(mass);
        set_target(mass);
    }    
    int search(int a, int b)
    {
        for (int i = 0; i < n; i+=2)
            if (hand[i] == a && hand[i+1] == b)
                return i;
    }
    bool check_finish()
    {
        int count = 0;
        for (int i = 0; i < number; i+=2)
        {
            for (int j = 0; j < number; j+=2)
            {
                if ((hand[i] == target[j]) && (hand[i+1] == target[j+1]))
                {
                    count++;
                    break;
                }
            }
        }
        if (count == number / 2)
            return true;
        else
            return false;
    }
    void menu()
    {
        system("cls");
        show(mass);
        if (check_finish())
        {
            cout << "You won!\n";
            return;
        }
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
};


int main()
{
    Move my;
    my.menu();

    return 0;
}
