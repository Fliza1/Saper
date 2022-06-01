#include <iostream>
#include <Windows.h>
#include <vector>
#include <ctime>
#include <conio.h>

using namespace std;

void gotoxy(int x, int y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

// устанавливает цвет текста и подложки в консоли
void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

class Map {
private:
	const int BORDER = 100; // граница пол€
	const int EMPTY_CELL = 0; // пуста€ €чейка 
	const int MINE = 10; // мина
	int size; // размер пол€ включа€ границы
	vector <vector<int>> map;	
	vector <vector<int>> mask;
public:
Map() {
		size = 10;
	}
      
    int openCell(int x, int y) {
		int result = 1;
		mask[x][y] = 1;
		if (map[x][y] == MINE) {
			result = 0;
		}
		show();

		return result;
}

	bool isBorder(int x, int y) {

		if (x < 0 || x >= size)
			return false;

		if (y < 0 || y >= size)
			return false;

		if (map[x][y] == BORDER) {
			return true;
		}
		return false;
	}

	void initVec(vector <vector<int>> & vec) {
		for (int i = 0; i < size; i++) {
			vector <int> temp;
			for (int j = 0; j < size; j++) {
				if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
					temp.push_back(BORDER);
				else
					temp.push_back(EMPTY_CELL);
			}
			vec.push_back(temp);
		}
	}

	void initMap() {
		initVec(map);
	}
	
	void initMask() {
		initVec(mask);
	}

	void coutColor(char ch, int color) {
		SetColor(LightGreen, Black);
		cout << ch;
		SetColor(White, Black);
	}

	void show() {
		gotoxy(0, 0);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {

				if (mask[j][i] == EMPTY_CELL) {
					cout << ".";
					continue;
				}
				if (map[j][i] == BORDER) {
					coutColor('#', LightGreen);
				}
				else if (map[j][i] == EMPTY_CELL)
					cout << " ";
				else if (map[j][i] == MINE)
					cout << "*";
				else if (map[j][i] == 1) {
					SetColor(LightCyan, Black);
					cout << map[j][i];
					SetColor(White, Black);
				}
				else if (map[j][i] == 2) {
					SetColor(LightMagenta, Black);
					cout << map[j][i];
					SetColor(White, Black);
				}
				else if (map[j][i] == 3) {
					SetColor(Yellow, Black);
					cout << map[j][i];
					SetColor(White, Black);
				}
				else if (map[j][i] == 4) {
					SetColor(LightBlue, Black);
					cout << map[j][i];
					SetColor(White, Black);
				}
				else if (map[j][i] == 5) {
					SetColor(Magenta, Black);
					cout << map[j][i];
					SetColor(White, Black);
				}
				else if (map[j][i] == 6) {
					SetColor(Brown, Black);
					cout << map[j][i];
					SetColor(White, Black);
				}
				else if (map[j][i] == 7) {
					SetColor(LightRed, Black);
					cout << map[j][i];
					SetColor(White, Black);
				}
				else if (map[j][i] == 8) {
					SetColor(Red, Black);
					cout << map[j][i];
					SetColor(White, Black);
				}
			}
			cout << endl;
		}
	}

	// случайна€ расстановка мин
	void SetRandMines(int numMines) {

		// контроль количества мин, которые можно установить на поле
		if (numMines >= (size - 2) * (size - 2)) {
			cout << "Too many mines" << endl;
			return;
		}

		for (int i = 0; i < numMines; i++) {
			int x = 0;
			int y = 0;
			// поиск пустой €чейки, не зан€той миной
			do {
				x = rand() % (size - 2) + 1;
				y = rand() % (size - 2) + 1;
			} while (map[x][y] == MINE);

			map[x][y] = MINE;
		}
	}

	// растановка чисел на игровом поле
	void SetDigits() {
		int d = 0;
		for (int i = 1; i < size - 1; i++) {
			for (int j = 1; j < size - 1; j++) {
				if (map[j][i] == MINE)
					continue;
				if (map[j][i + 1] == MINE)
					d++;
				if (map[j][i - 1] == MINE)
					d++;
				if (map[j + 1][i + 1] == MINE)
					d++;
				if (map[j + 1][i - 1] == MINE)
					d++;
				if (map[j - 1][i + 1] == MINE)
					d++;
				if (map[j - 1][i - 1] == MINE)
					d++;
				if (map[j + 1][i] == MINE)
					d++;
				if (map[j - 1][i] == MINE)
					d++;
				map[j][i] = d;
				d = 0;
			}

		}
	}
};

class Keyboard {

private:
	int ch = 0;

public:	
	
	Keyboard() {
		ch = 0;
	}

	void waitKey() {
		ch = _getch();
	}

	int getKey() {
		return ch;
	}
};

class Cursor {
private:	

	int x = 1;
	int y = 1;

	int tx = 1;
	int ty = 1;

public:

	void save() {
		tx = x;
		ty = y;
	}

	void undo() {
		x = tx;
		y = ty;
	}

	void incX() {
		x++;
	}

	void decX() {
		x--;
	}
	
	void incY() {
		y++;
	}

	void decY() {
		y--;
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	void move() {
		gotoxy(x, y);
	}
};

class Game {
public:

	void gameOver() {
		gotoxy(40, 9);
		cout << "Game over";
		Sleep(2000);
		gotoxy(0, 15);
		system("pause");
	}

	void run() {
		Map map;
		map.initMap();
		map.initMask();
		map.SetRandMines(29);
		map.SetDigits();
		map.show();

		Keyboard kb;
		Cursor cs;

		cs.move();

		bool exit = false;

		while (!exit) {
			kb.waitKey();

			cs.save();

			switch (kb.getKey()) {
			case 77: cs.incX(); break; // право
			case 80: cs.incY(); break; // вниз
			case 75: cs.decX(); break; // влево
			case 72: cs.decY(); break; // вверх
			case 13:
				if (map.openCell(cs.getX(), cs.getY()) == 0) {
					gameOver();
					exit = true;
					system("cls");
				}
			break; // вверх
			}


			if (map.isBorder(cs.getX(), cs.getY())) {
				cs.undo();
			}

			cs.move();
		}
	}
};
int main() {

	srand(time(0));
	Game game;
	game.run();
}