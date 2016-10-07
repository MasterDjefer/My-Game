#include <iostream>
#include <conio.h>
#include <cstring>
#include <cstdlib>
using namespace std;

const int n = 10;
const int m = 10;

class Table
{
protected:
    char mass[n][m];
private:
    bool if_show_instruction;
public:
    Table():if_show_instruction(true){}

    void set_null()
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                mass[i][j] = ' ';
    }
    void set_side()
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
    void set_side_level1()
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
        for (int i = 1; i < 9; ++i)
            for (int j = 7; j < 9; ++j)
            {
                mass[i][j] = '#';
                mass[j][i] = '#';
            }
    }
    void set_side_level2()
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                mass[i][j] = '#';
        for (int i = 0; i < 4; ++i)
            for (int j = 6; j < m-1; ++j)
            {
                mass[i][j] = '#';
                mass[j][i] = '#';
            }
        for (int i = 6; i < n-1; ++i)
            for (int j = 6; j < m-1; ++j)
                mass[i][j] = '#';
    }

    void set_side_level3()
    {
        for (int i = 1; i < 9; ++i)
        {
            mass[6][i] = '#';
            mass[7][i] = '#';
            mass[8][i] = '#';
        }
        for (int i = 1; i < 7; ++i)
            mass[i][8] = '#';

        mass[1][1] = '#';
        mass[1][4] = '#';
        mass[1][7] = '#';
        mass[2][7] = '#';
        mass[3][4] = '#';
        mass[5][4] = '#';
        mass[5][1] = '#';
    }
    void show()
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
                cout << mass[i][j];
            cout << endl;
        }
        if (if_show_instruction)
            cout << "Press \'h\' for instriction\n";
        if_show_instruction = false;
    }
};

class Elements : protected Table
{
protected:
    int head_x;
    int head_y;
    int target_x;
    int target_y;
    int number;
    int hand[10];
    int target[10];

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
    void set_elements_level2()
    {
        number = 8;
        head_x = 4;
        head_y = 5;
        hand[0] = 4; hand[1] = 4;
        hand[2] = 5; hand[3] = 3;
        hand[4] = 5; hand[5] = 5;
        hand[6] = 6; hand[7] = 4;
        target[0] = 1; target[1] = 5;
        target[2] = 4; target[3] = 8;
        target[4] = 5; target[5] = 1;
        target[6] = 8; target[7] = 4;
    }
    void set_elements_level3()
    {
        number = 6;
        head_x = 3;
        head_y = 2;
        hand[0] = 2; hand[1] = 4;
        hand[2] = 2; hand[3] = 5;
        hand[4] = 4; hand[5] = 4;
        target[0] = 4; target[1] = 7;
        target[2] = 5; target[3] = 7;
        target[4] = 6; target[5] = 7;
    }
    void set_elements_level_test()
    {
        number = 4;
        head_x = 1;
        head_y = 1;
        hand[0] = 3; hand[1] = 3;
        hand[2] = 3; hand[3] = 4;
        target[0] = 6; target[1] = 6;
        target[2] = 7; target[3] = 6;
    }
    void set_head()
    {
        mass[head_x][head_y] = 'o';
    }
    void set_hand()
    {
        for (int i = 0; i < number; i+=2)
            mass[hand[i]][hand[i+1]] = '@';
    }
    void set_target()
    {
        for (int i = 0; i < number; i+=2)
            mass[target[i]][target[i+1]] = '*';
    }
    void change_hand()
    {
        for (int i = 0; i < number; i+=2)
            for (int j = 0; j < number; j+=2)
                if ((hand[i] == target[j]) && (hand[i+1] == target[j+1]))
                {
                    mass[hand[i]][hand[i+1]] = '+';
                    break;
                }
    }
};

class Move : private Elements
{
public:
    Move()
    {
        set_null();
        set_side();
        choose_level();
    }
private:
    void choose_level()
    {
        cout << "Enter your level(1-4): ";
        string c = "";
        char choice = 0;
        cin >> c;
        if (c.size() == 1) choice = c.at(0);
        system("cls");
        switch (choice)
        {
            case '1':
                set_side_level1();
                set_elements_level1();
                break;
            case '2':
                set_side_level2();
                set_elements_level2();
                break;
            case '3':
                set_side_level3();
                set_elements_level3();
                break;
            case '4':
                set_elements_level_test();
                break;
            default:
                cout << "Bad inputing or this level doesn\'t exist!\n";
                choose_level();
        }
        set_head();
        set_hand();
        set_target();
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
    void instruction()
    {
        cout << "\'w\' - move up\n";
        cout << "\'s\' - move down\n";
        cout << "\'a\' - move left\n";
        cout << "\'d\' - move right\n\n";

        cout << "\'o\' - it\'s you. You can move and move blocks\n";
        cout << "\'#\' - it\'s wall. You can\'t go throw it\n";
        cout << "\'@\' - it\'s block. You must move it to \'*\'\n";
        cout << "\'*\' - it\'s platform. You must cover it by \'@\'\n";

        cout << "Press any key to continue\n";
        _getch();
    }
public:
    void menu()
    {
        system("cls");
        show();

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

                    if (mass[hand[temp]][hand[temp + 1] + 1] != '#' && mass[hand[temp]][hand[temp + 1] + 1] != '@' && mass[hand[temp]][hand[temp + 1] + 1] != '+')
                    {
                        mass[hand[temp]][hand[temp + 1] + 1] = '@';
                        hand[temp + 1]++;

                        mass[head_x][head_y + 1] = 'o';
                        mass[head_x][head_y] = ' ';
                        head_y++;
                    }
                }
                else
                if (mass[head_x][head_y + 1] == '+')
                {
                    int temp = search(head_x, head_y + 1);

                    if (mass[hand[temp]][hand[temp + 1] + 1] != '#' && mass[hand[temp]][hand[temp + 1] + 1] != '@' && mass[hand[temp]][hand[temp + 1] + 1] != '+')
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

                    if (mass[hand[temp]][hand[temp + 1] - 1] != '#' && mass[hand[temp]][hand[temp + 1] - 1] != '@' && mass[hand[temp]][hand[temp + 1] - 1] != '+')
                    {
                        mass[hand[temp]][hand[temp + 1] - 1] = '@';
                        hand[temp + 1]--;

                        mass[head_x][head_y - 1] = 'o';
                        mass[head_x][head_y] = ' ';
                        head_y--;
                    }
                }
                else
                if (mass[head_x][head_y - 1] == '+')
                {
                    int temp = search(head_x, head_y - 1);

                    if (mass[hand[temp]][hand[temp + 1] - 1] != '#' && mass[hand[temp]][hand[temp + 1] - 1] != '@' && mass[hand[temp]][hand[temp + 1] - 1] != '+')
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
                    int temp = search(head_x - 1, head_y);

                    if (mass[hand[temp] - 1][hand[temp + 1]] != '#' && mass[hand[temp] - 1][hand[temp + 1]] != '@' && mass[hand[temp] - 1][hand[temp + 1]] != '+')
                    {
                        mass[hand[temp] - 1][hand[temp + 1]] = '@';
                        hand[temp]--;

                        mass[head_x - 1][head_y] = 'o';
                        mass[head_x][head_y] = ' ';
                        head_x--;
                    }
                }
                else
                if (mass[head_x - 1][head_y] == '+')
                {
                    int temp = search(head_x - 1, head_y);

                    if (mass[hand[temp] - 1][hand[temp + 1]] != '#' && mass[hand[temp] - 1][hand[temp + 1]] != '@' && mass[hand[temp] - 1][hand[temp + 1]] != '+')
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

                    if (mass[hand[temp] + 1][hand[temp + 1]] != '#' && mass[hand[temp] + 1][hand[temp + 1]] != '@' && mass[hand[temp] + 1][hand[temp + 1]] != '+')
                    {
                        mass[hand[temp] + 1][hand[temp + 1]] = '@';
                        hand[temp]++;

                        mass[head_x + 1][head_y] = 'o';
                        mass[head_x][head_y] = ' ';
                        head_x++;
                    }
                }
                else
                if (mass[head_x + 1][head_y] == '+')
                {
                    int temp = search(head_x + 1, head_y);

                    if (mass[hand[temp] + 1][hand[temp + 1]] != '#' && mass[hand[temp] + 1][hand[temp + 1]] != '@' && mass[hand[temp] + 1][hand[temp + 1]] != '+')
                    {
                        mass[hand[temp] + 1][hand[temp + 1]] = '@';
                        hand[temp]++;

                        mass[head_x + 1][head_y] = 'o';
                        mass[head_x][head_y] = ' ';
                        head_x++;
                    }
                }
                break;
            case 'h':
                instruction();
                break;
        }
        for (int i = 0; i < number; i+=2)
        {
            if (mass[target[i]][target[i + 1]] == ' ')
                mass[target[i]][target[i + 1]] = '*';
        }
        change_hand();

        menu();
    }
};


int main()
{
    Move my;
    my.menu();

    return 0;
}
