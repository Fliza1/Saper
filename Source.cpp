#include <iostream>
#include <time.h>
//#include <windows.h>
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
#define BOOM 10 //���������� ���� �� ����

//  1
void show_of_mines()
{
    cout << "* ";
}
void print_array_2D(int** Playing_field, bool** open, const int SIZE)
{
    char strLetters[30] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0' };
    cout << " ";
    for (int i = 0; i < SIZE; i++)
    {

        cout << " " << strLetters[i];
    }
    cout << endl;


    for (int x = 0; x <= SIZE; x++)
    {
        if (x < 10)
        {
            cout << x << " |";
        }
        else
        {
            cout << x << "|";
        }
        /////////////////////////////////////   

        for (int y = 0; y < SIZE; y++)
        {
            if (open[x][y])
            {

                if (Playing_field[x][y] == -1)
                {
                    show_of_mines();
                }
                else if (Playing_field[x][y] == 0)
                {
                    cout << "* ";
                }
                else
                {
                    cout << Playing_field[x][y] << " ";
                }
            }
            else
            {
                cout << "& ";
            }
        }
        cout << endl;
    }
}
// ��������� ������ �� ������� (true), ����� �� ������� ������� ���������� false
bool empty(int** Playing_field, int i, int j, const int SIZE)
{
    if ((i >= 0) && (i < SIZE))
    {
        if ((j >= 0) && (j < SIZE))
        {
            if (Playing_field[i][j] == 0) return true;
        }
    }
    return false;
}
// ����������� �������, ������� ��������� ���� � ����� ���������
void clean(int** Playing_field, bool** open, int i, int j, const int SIZE)
{
    // �������� �� ����� �� ������� �������
    if ((i >= 0) && (i < SIZE))
    {
        if ((j >= 0) && (j < SIZE))
        {
            // ��������, �� ���� �� ������� ���� ������
            if (!open[i][j])
            {
                open[i][j] = true;  //�������
                // ���� ���� ������ (=0), ������ ����������� ���� ��� �������
                if (Playing_field[i][j] == 0)
                {
                    clean(Playing_field, open, i - 1, j - 1, SIZE);
                    clean(Playing_field, open, i - 1, j, SIZE);
                    clean(Playing_field, open, i - 1, j + 1, SIZE);
                    clean(Playing_field, open, i, j - 1, SIZE);
                    clean(Playing_field, open, i, j + 1, SIZE);
                    clean(Playing_field, open, i + 1, j - 1, SIZE);
                    clean(Playing_field, open, i + 1, j, SIZE);
                    clean(Playing_field, open, i + 1, j + 1, SIZE);
                }
                // ���� �� ������ (!=0) ��������� ������ ������ (=0) �������
                else
                {
                    if (empty(Playing_field, i - 1, j - 1, SIZE)) clean(Playing_field, open, i - 1, j - 1, SIZE);
                    if (empty(Playing_field, i - 1, j, SIZE)) clean(Playing_field, open, i - 1, j, SIZE);
                    if (empty(Playing_field, i - 1, j + 1, SIZE)) clean(Playing_field, open, i - 1, j + 1, SIZE);
                    if (empty(Playing_field, i, j - 1, SIZE)) clean(Playing_field, open, i, j - 1, SIZE);
                    if (empty(Playing_field, i, j + 1, SIZE)) clean(Playing_field, open, i, j + 1, SIZE);
                    if (empty(Playing_field, i + 1, j - 1, SIZE)) clean(Playing_field, open, i + 1, j - 1, SIZE);
                    if (empty(Playing_field, i + 1, j, SIZE)) clean(Playing_field, open, i + 1, j, SIZE);
                    if (empty(Playing_field, i + 1, j + 1, SIZE)) clean(Playing_field, open, i + 1, j + 1, SIZE);
                }
            }
        }
    }
}

// ��������� ������ �� ���� ; ����� �� ������� ���������� false
bool mine(int** Playing_field, int i, int j, const int SIZE)
{
    if ((i >= 0) && (i < SIZE))
    {
        if ((j >= 0) && (j < SIZE))
        {
            if (Playing_field[i][j] == -1) return true;
        }
    }
    return false;
}

void empty_play_space(int** Playing_field, bool** open, const int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (Playing_field[i][j] == -1)
            {
                open[i][j] = true;
            }
        }
    }
}

bool win_or_lose(int** Playing_field, bool** open, const int SIZE)
{
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            if ((Playing_field[x][y] != -1) && (!open[x][y])) return false;
        }
    }
    return true;
}

// � ������ ��������� ��� ������� ������� ��� ����
void openmines(int** Playing_field, bool** open, const int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (Playing_field[i][j] == -1) open[i][j] = true;
        }
    }
}

void final(bool loser, int** Playing_field, bool** open, const int SIZE)
{
    system("cls");
    print_array_2D(Playing_field, open, SIZE);
    if (loser)
    {
        cout << "�� ��������!(";
    }
    else
    {
        cout << "�� ��������!)";
    }
    cout << endl;
}
void inputSize(int& size)   //������ �� ���� �������� ��������� �������
{
    while (true)
    {
        cout << "������� ������ ���� (10):" << endl << endl;
        cin >> size;
        if (cin.fail())
        {
            cout << "������, ������� ������� ��������" << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        else if (size > 0) break;
    }
}

//  2
void rules()
{
    cout << "\t\t\t\t\t\t\t\t�����: ������� � ����� ��������" << endl << endl << endl << endl;
    cout << "\t������� � �������� ����� ������." << endl;
    cout << "\t����� � ������ ����������, ������� ��� ������ ������ ������ ������. ��� ����� ������� ������ ���, ��� ��������� ���������� ������, � ��� ��������� �����." << endl;
    cout << "\t���� ����� � �������� ������� ���� ������ ������, �� ��� ��������� �������������." << endl;
    cout << "\t���� �� ������� ������ � �����, �� ���� ���������." << endl;
    cout << "\t���� � ������ ������� �����, ��� ����������, ������� ��� ������ � ������ ������� ������ ������. ��� ����� �������� ������, ��� ��������� ���������� ������." << endl;
    cout << "\t���� ������������ �� ��� ���, ���� �� �� �������� ��� �� �������������� ������." << endl << endl << endl;
    cout << "\t������� ����!)" << endl << endl << endl << endl << endl << endl;
}







int main()
{
    srand((unsigned int)time(NULL));
    setlocale(LC_ALL, "Russian");

    char choice{};
    while (true)
    {
        system("cls");
        cout << "1 - ������ " << endl;
        cout << "2 - ������� ���� << ����� >> " << endl;
        cout << "0 - �����" << endl << endl << endl;
        cout << "�������� ��� �����:" << endl << endl;
        cin >> choice;
        cout << endl;
        cin.ignore(100, '\n');
        if (choice == '0') break;
        switch (choice)
        {
        case '1':
        {

            int SIZE = 0;
            inputSize(SIZE);
            int** Playing_field = new int* [SIZE];
            bool** open = new bool* [SIZE];

            for (int i = 0; i < SIZE; i++)
            {
                *(Playing_field + i) = new int[SIZE];
            }
            for (int i = 0; i < SIZE; i++)
            {
                *(open + i) = new bool[SIZE];
            }
            int i{};
            int j{};
            for (int c = 0; c < SIZE * 10; c++)
            {
                Playing_field[c / 10][c % 10] = 0;
                open[c / 10][c % 10] = false;
            }
            // ��������� ������ ���� ������
            for (int c = 0; c < BOOM; c++)
            {
                do
                {
                    i = rand() % SIZE;
                    j = rand() % SIZE;
                } while (Playing_field[i][j] != 0);
                Playing_field[i][j] = -1;
            }
            // ��������� ������ ���� �������
            for (i = 0; i < SIZE; i++)
            {
                for (j = 0; j < SIZE; j++)
                {
                    if (Playing_field[i][j] != -1)
                    {
                        int quantity{};
                        if (mine(Playing_field, i - 1, j - 1, SIZE)) quantity++;
                        if (mine(Playing_field, i - 1, j, SIZE)) quantity++;
                        if (mine(Playing_field, i - 1, j + 1, SIZE)) quantity++;
                        if (mine(Playing_field, i, j - 1, SIZE)) quantity++;
                        if (mine(Playing_field, i, j + 1, SIZE)) quantity++;
                        if (mine(Playing_field, i + 1, j - 1, SIZE)) quantity++;
                        if (mine(Playing_field, i + 1, j, SIZE)) quantity++;
                        if (mine(Playing_field, i + 1, j + 1, SIZE)) quantity++;
                        Playing_field[i][j] = quantity;
                    }
                }
            }
            while (true)
            {
                system("cls");
                cout << "*****************************" << endl << endl;
                cout << "* ����� ���������� ���� ��� *" << endl << endl;
                cout << "*****************************" << endl;
                cout << endl << endl;
                print_array_2D(Playing_field, open, SIZE);
                cout << endl;
                // ����������� ���������� �����
                char input_coordinate[4]{ '\0' };
                cout << "������� ���������� ����� (E7): ";
                cin >> input_coordinate;

                if ((input_coordinate[0] >= 65) && (input_coordinate[0] <= 90))
                {
                    j = input_coordinate[0] - 65; // ����� � ���������� �� A �� Z
                }
                else if ((input_coordinate[0] >= 97) && (input_coordinate[0] <= 122))
                {
                    j = input_coordinate[0] - 97; // ����� � ���������� �� a �� z
                }
                else continue; // ���� ������� �������� ��������, ������� � ������ �����
                if ((input_coordinate[1] >= 48) && (input_coordinate[0] <= 57)) //��������� ���������� � �������� ��� �� 0 �� 9
                {
                    i = input_coordinate[1] - 48;
                }
                else continue;
                // ����� ��������� ��� ������ ��������� ����� �� ������ ������ ���������� ����� ����� ���� 
                clean(Playing_field, open, i, j, SIZE);
                if (mine(Playing_field, i, j, SIZE))
                {
                    openmines(Playing_field, open, SIZE);
                    final(true, Playing_field, open, SIZE); break;
                }
                if (win_or_lose(Playing_field, open, SIZE))
                {
                    final(false, Playing_field, open, SIZE); break;
                }
            }
            for (int i = 0; i < SIZE; i++)
            {
                delete[] * (Playing_field + i);
            }
            for (int i = 0; i < SIZE; i++)
            {
                delete[] * (open + i);
            }
            //delete[] Playing_field;
        }
        break;

        case '2':
        {
            rules();
        }
        break;

        default: cout << "������, ���������� ��� ���, ������� ������ <Enter>, ����� ��������� �������" << endl; break;
        }
        system("pause");
    }
    return 0;
}