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
	ifstream tablo;
	tablo.open("C:/Users/Александр/Desktop/812/c=3.txt", ios::in);
	if (!tablo) {
		cout << "Error input file" << endl;
	}

	string t;
	do {
		cout << "\n=== КЖД ===" << endl;
		cout << "1. Показать доступные поезда" << endl;
		cout << "2. Купить билет" << endl;
		cout << "3. Выход" << endl;
		cout << "Выберите действие (1-3): ";
		cin >> zov;

		switch (zov) {
		case 1:while (tablo) {
			if (getline(tablo, t))
				cout << t << endl;
		}




			  break;
		case 2: inputPassengerData();






			break;






		case 3:
			break;

		default:
			cout << "Такого варианта нет!!!" << endl;

		}

		cout << "__________________________________________" << endl;
	} while (zov != 3);





	tablo.close();
}

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	nachalo();




	return 0;


}
