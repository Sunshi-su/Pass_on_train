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
	cout << "Номер" << "   " << "Откуда" << "  " << "Куда" << "            " << "Отпр" << "  " << "Приб" << "     " << "Кол-во" << endl;

}


void kyda() {
	ifstream bablo;
	bablo.open("C:/Users/243557/Desktop/Москва-Питер.txt", ios::in);
	if (!bablo) {
		cout << "Error input file" << endl;
	}
	cout << "______________________________________________________" << endl;
	cout << "===Выбирите направление:===" << endl;
	char k;
	cin >> k;
	cout << k << endl;

}
Passenger inputPassengerData() {
	Passenger passenger;
	cout << "\n=== ДАННЫЕ ПАССАЖИРА ===\n" << endl;
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

void tiket() {
	cout << "------------------------------------------------------------" << endl;
	cout << "| Номер билета: " << setw(41) << " " << left << " " << " |" << endl;
	cout << "| Поезд: №" << setw(30) << left << " " << "Дата: " << setw(12) << left << " " << " |" << endl;
	cout << "| Время отправления: " << setw(36) << " " << left << " " << " |" << endl;
	cout << "| Время прибытия: " << setw(39) << " " << left << " " << " |" << endl;
	cout << "| Маршрут: " << setw(46) << " " << left << " " << " |" << endl;
	cout << "| Тип поезда: " << setw(43) << " " << left << " " << " |" << endl;
	cout << "| Тип вагона: " << setw(43) << " " << left << " " << " |" << endl;
	cout << "| Пассажир: " << setw(46) << left << " " << " |" << endl;
	cout << "| Место: " << setw(30) << left << " "
		<< " Стоимость: " << setw(7) << left << "  " << " |" << endl;
	cout << "------------------------------------------------------------" << endl;





}

void nachalo() {



	do {
		cout << "\n=== РЖД ===\n" << endl;
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
			kyda();





			break;






		case 3:
			break;

		default:
			cout << "Такого варианта нет!!!" << endl;

		}

		cout << "_____________________________________________________" << endl;
	} while (zov != 3);






}

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	nachalo();




	return 0;


}
