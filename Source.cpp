#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

void gotoxy(int x, int y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

class Map {
private:
	int size;
	vector < vector<int>> map;
public:
	Map() {
		size = 10;
	}
	void initMap() {
		for (int i = 0; i < size; i++) {
			vector<int > temp;
			for (int j = 0; j < size; j++) {
				if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
					temp.push_back(100);
				else
					temp.push_back(0);
			}
			map.push_back(temp);
		}
	}
	void show() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if(map[i][j] == 100)
					cout << "#";
				else if (map[i][j] == 0)
					cout << " ";
			}
			cout << endl;
		}
	}
};

class Game {
private:
	void showLogo() {
		gotoxy(40, 9);
		cout << "Saper" << endl;
		Sleep(2000);
		system("cls");
	}
public:
	void run() {
		void showLogo();
		Map map;
		map.initMap();
		map.show();
	}
};
int main() {
	Game game;
	game.run();
}