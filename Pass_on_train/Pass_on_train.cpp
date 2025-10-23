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

void spisok() {
	ifstream tablo;
	tablo.open("C:/Users/243557/Desktop/c=3.txt", ios::in);
	if (!tablo) {
		cout << "Error input file" << endl;
	}
	string t;

	while (tablo) {
		if (getline(tablo, t))
			cout << t << endl;

	}


	tablo.close();
}

void vivod() {
	cout << "______________________________________________________" << endl;
	cout<< "Номер" <<"   " << "Откуда" << "  " << "Куда" << "            " << "Отпр" << "  " << "Приб" << "     " << "Кол-во" << endl;

}

Passenger inputPassengerData() {
	Passenger passenger;
	cout << "\n=== ДАННЫЕ ПАССАЖИРА ===" << endl;
	cout << "Введите фамилию: ";
	cin >> passenger.Familia;
	cout << "Введите имя: ";
	cin >> passenger.Imya;
	cout << "Введите отчество: ";
	cin >> passenger.Otchestvo;
	cout << "Введите номер паспорта: ";
	cin >> passenger.passport;

	return passenger;
}

void nachalo() {



	do {
		cout << "\n=== КЖД ===" << endl;
		cout << "1. Показать доступные поезда" << endl;
		cout << "2. Купить билет" << endl;
		cout << "3. Выход" << endl;
		cout << "Выберите действие (1-3): ";
		cin >> zov;

		switch (zov) {
		case 1: vivod();
			spisok();





			break;
		case 2: 






			break;






		case 3:
			break;

		default:
			cout << "Такого варианта нет!!!" << endl;

		}

		cout << "______________________________________________________" << endl;
	} while (zov != 3);






}

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	nachalo();




	return 0;


}
