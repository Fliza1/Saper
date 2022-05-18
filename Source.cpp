#include <iostream>
#include <time.h>
//#include <windows.h>
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
#define BOOM 10 //количество бомб на поле

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
// проверяет ячейку на пустоту (true), выход за пределы массива возвращает false
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
// рекурсивная функция, которая открывает поля в точке попадания
void clean(int** Playing_field, bool** open, int i, int j, const int SIZE)
{
    // проверим на выход за пределы массива
    if ((i >= 0) && (i < SIZE))
    {
        if ((j >= 0) && (j < SIZE))
        {
            // проверим, не было ли открыто поле раньше
            if (!open[i][j])
            {
                open[i][j] = true;  //откроем
                // если поле пустое (=0), просто пооткрываем всех его соседей
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
                // если не пустое (!=0) открываем только пустых (=0) соседей
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

// проверяет ячейку на мину ; выход за пределы возвращает false
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

// в случае проигрыша эта функция откроет все мины
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
        cout << "ВЫ ПРОИРАЛИ!(";
    }
    else
    {
        cout << "ВЫ ВЫИГРАЛИ!)";
    }
    cout << endl;
}
void inputSize(int& size)   //запрос на ввод колиство элементов массива
{
    while (true)
    {
        cout << "ВВЕДИТЕ РАЗМЕР ПОЛЯ (10):" << endl << endl;
        cin >> size;
        if (cin.fail())
        {
            cout << "ОШИБКА, ВВЕДИТЕ МЕНЬШЕЕ ЗНАЧЕНИЕ" << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        else if (size > 0) break;
    }
}

//  2
void rules()
{
    cout << "\t\t\t\t\t\t\t\tСАПЕР: ПРАВИЛА И ОБЩИЕ СВЕДЕНИЯ" << endl << endl << endl << endl;
    cout << "\tНачните с открытия одной ячейки." << endl;
    cout << "\tЧисло в ячейке показывает, сколько мин скрыто вокруг данной ячейки. Это число поможет понять вам, где находятся безопасные ячейки, а где находятся бомбы." << endl;
    cout << "\tЕсли рядом с открытой ячейкой есть пустая ячейка, то она откроется автоматически." << endl;
    cout << "\tЕсли вы открыли ячейку с миной, то игра проиграна." << endl;
    cout << "\tЕсли в ячейке указано число, оно показывает, сколько мин скрыто в восьми ячейках вокруг данной. Это число помогает понять, где находятся безопасные ячейки." << endl;
    cout << "\tИгра продолжается до тех пор, пока вы не откроете все не заминированные ячейки." << endl << endl << endl;
    cout << "\tУдачной игры!)" << endl << endl << endl << endl << endl << endl;
}







int main()
{
    srand((unsigned int)time(NULL));
    setlocale(LC_ALL, "Russian");

    char choice{};
    while (true)
    {
        system("cls");
        cout << "1 - ИГРАТЬ " << endl;
        cout << "2 - ПРАВИЛА ИГРЫ << САПЕР >> " << endl;
        cout << "0 - ВЫХОД" << endl << endl << endl;
        cout << "СДЕЛАЙТЕ ВАШ ВЫБОР:" << endl << endl;
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
            // заполняем массив поля минами
            for (int c = 0; c < BOOM; c++)
            {
                do
                {
                    i = rand() % SIZE;
                    j = rand() % SIZE;
                } while (Playing_field[i][j] != 0);
                Playing_field[i][j] = -1;
            }
            // заполняем массив поля цифрами
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
                cout << "* САПЕР ОШИБАЕТЬСЯ ОДИН РАЗ *" << endl << endl;
                cout << "*****************************" << endl;
                cout << endl << endl;
                print_array_2D(Playing_field, open, SIZE);
                cout << endl;
                // запрашиваем координаты удара
                char input_coordinate[4]{ '\0' };
                cout << "Введите координаты удара (E7): ";
                cin >> input_coordinate;

                if ((input_coordinate[0] >= 65) && (input_coordinate[0] <= 90))
                {
                    j = input_coordinate[0] - 65; // буква в промежутке от A до Z
                }
                else if ((input_coordinate[0] >= 97) && (input_coordinate[0] <= 122))
                {
                    j = input_coordinate[0] - 97; // буква в промежутке от a до z
                }
                else continue; // если введены неверные значения, возврат в начало цикла
                if ((input_coordinate[1] >= 48) && (input_coordinate[0] <= 57)) //переводим координаты в цифровой вид от 0 до 9
                {
                    i = input_coordinate[1] - 48;
                }
                else continue;
                // далее проверяем все восемь окрестных полей на пустые клетки показываем некий кусок поля 
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

        default: cout << "Ошибка, попробуйте еще раз, нажмите кнопку <Enter>, чтобы повторить попытку" << endl; break;
        }
        system("pause");
    }
    return 0;
}