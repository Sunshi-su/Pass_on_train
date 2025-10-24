#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <algorithm>
#include <regex>
#include <sstream>

using namespace std;

struct Passenger {
	string Familia;
	string Imya;
	string Otchestvo;
	string passport;
};

int zov;

void spisok() {
	fstream tablo;
	tablo.open("../c=3.txt", ios::in);
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
	cout << "Номер" << "   " << "Откуда" << "  " << "Куда" << "            " << "Отпр." << "  " << "Приб." << "     " << "Кол-во" << endl;
}


void direction_train() {

	fstream Dir;
	cout << "______________________________________________________" << endl;
	cout << "===Выбирите направление:===" << endl;
	cout << "Поиск: ";
	string direction;
	cin >> direction;
	transform(direction.begin(), direction.end(), direction.begin(), ::tolower); //Устойчивость к регистру направления

	if (direction == "казань")
	{
		Dir.open("../Казань.txt");
		if (!Dir) 
		{
			cout << "Error input file" << endl;
		}
		string n;
		string stantion;
		int index;
		const int N = 7, M =2;
		vector<vector<string>> matrix_str(M);

		while (Dir) 
		{
			if (getline(Dir, n)){

				stringstream ss(n);
				string segment;

				// Разделяем по "->"
				while (getline(ss, segment, '-')) {
					if (segment == ">") continue; // пропустить ">" если попадётся

					// Убираем лишние пробелы
					segment.erase(0, segment.find_first_not_of(" >"));
					segment.erase(segment.find_last_not_of(" >") + 1);

					// Используем регулярное выражение для выделения названия и расстояния
					smatch match;
					regex re(R"((.+?)(?:\((\d+)\))?$)"); // название(число)
					if (regex_match(segment, match, re)) {
						string name = match[1];
						string dist = match[2].matched ? match[2].str() : "0";
						matrix_str[0].push_back(name);
						matrix_str[1].push_back(dist);
					}
				}



				cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "=== Доступные остановки по данному направлению ===" << endl;
				cout << " " << endl;
				cout << n << endl;
				cout << " " << endl;
				cout << "-----------------Выберите станцию --------------------------------------------------------------------------------------" << endl;
				cout << "Станция: ";
				cin >> stantion;
				stantion.erase(0, stantion.find_first_not_of(" "));
				stantion.erase(stantion.find_last_not_of(" ") + 1);

				bool found = false;
				int stationIndex = -1;
				int kmToStation = 0;

				for (int i = 0; i < matrix_str[0].size(); ++i) {
					if (matrix_str[0][i] == stantion) {
						found = true;
						stationIndex = i;
						stringstream ss(matrix_str[1][i]);
						ss >> kmToStation;
						break;
					}
				}
			}
				
		}
		Dir.close();

	}

	else if(direction == "сочи") {
		Dir.open("../Сочи.txt");
		if (!Dir)
		{
			cout << "Error input file" << endl;
		}
		string n;
		string stantion;
		int index;
		const int N = 7, M = 2;
		vector<vector<string>> matrix_str(M);

		while (Dir)
		{
			if (getline(Dir, n)) {

				stringstream ss(n);
				string segment;

				
				while (getline(ss, segment, '-')) {
					if (segment == ">") continue;

					segment.erase(0, segment.find_first_not_of(" >"));
					segment.erase(segment.find_last_not_of(" >") + 1);

					smatch match;
					regex re(R"((.+?)(?:\((\d+)\))?$)"); // название(число)
					if (regex_match(segment, match, re)) {
						string name = match[1];
						string dist = match[2].matched ? match[2].str() : "0";
						matrix_str[0].push_back(name);
						matrix_str[1].push_back(dist);
					}
				}



				cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "=== Доступные остановки по данному направлению ===" << endl;
				cout << " " << endl;
				cout << n << endl;
				cout << " " << endl;
				cout << "-----------------Выберите станцию --------------------------------------------------------------------------------------" << endl;
				cout << "Станция: ";
				cin >> stantion;
				stantion.erase(0, stantion.find_first_not_of(" "));
				stantion.erase(stantion.find_last_not_of(" ") + 1);

				bool found = false;
				int stationIndex = -1;
				int kmToStation = 0;

				for (int i = 0; i < matrix_str[0].size(); ++i) {
					if (matrix_str[0][i] == stantion) {
						found = true;
						stationIndex = i;
						stringstream ss(matrix_str[1][i]);
						ss >> kmToStation;
						break;
					}
				}
			}

		}
		Dir.close();
	}


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

void start() {

	do {
		cout << "\n=== РЖД ===\n" << endl;
		cout << "1. Показать доступные поезда" << endl;
		cout << "2. Купить билет" << endl;
		cout << "3. Выход" << endl;
		cout << "Выберите действие (1-3): ";
		cin >> zov;

		switch (zov) {
		case 1: 
			vivod();
			spisok();
			break;

		case 2:
			direction_train();

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
	start();
	return 0;
}

