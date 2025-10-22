#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <windows.h>

using namespace std;

struct Passenger {
	string Familia;
	string Imya;
	string Otchestvo;
	string passport;
};

int zov;

void hachalo() {
	ifstream tablo;
	tablo.open("Dis.txt", ios::in);
	string t;
	do {
		cout << "\n=== КЖД ===" << endl;
		cout << "1. Показать доступные поезда" << endl;
		cout << "2. Купить билет" << endl;
		cout << "Выберите действие (1-2): ";
		cin >> zov;

		switch (zov) {
		case 1:while (tablo) {
			if (getline(tablo, t))
				cout << t << endl;
		}




			  break;
		case 2:
			break;


		default:
			cout << "Такого варианта нет!!!" << endl;

		}

		cout << "__________________________________________" << endl;
	} while (zov);





}








int main() {
	setlocale(LC_ALL, "RUS");
	cout.imbue(locale("rus_rus.866"));
	cin.imbue(locale("rus_rus.866"));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	hachalo();




	return 0;


}
