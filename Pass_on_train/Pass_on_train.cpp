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
string direction;
int kmToStation = 0;//множитель
int prise = 1;//переменная для итоговой цены
string trainType;
int typeTrain = 0;//множитель
string carriage; //Саш, это для билета переменная (тип вагона)
int x = 0;//можитель

void vivod() {
	cout << "_____________________________________________________________________________________________________________________" << endl;
	cout << "Номер" << "  " << "Откуда" << "  " << "Куда" << "            " << "Отпр." << "   " << "Приб." << "     " << "Кол-во" << "  " << "Тип поезда" << endl;
}
void spisok() {
	fstream tablo;
	tablo.open("../trains.txt", ios::in);
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

void type_ot_train() {
	cout << "-----------------Доступные поезда -------------------------------------------------------------------------------------" << endl;
	fstream tablo;
	string s;
	int confirmation=0;
	tablo.open("../trains.txt", ios::in);
	if (!tablo) {
		cout << "Error input file" << endl;
	}
	vivod();
	while (tablo){
		if (getline(tablo, s)) {
			if (s.find(direction) != string::npos)
			{
				cout << s << endl;
			}
		}
	}
	tablo.clear();
	tablo.seekg(0);
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;

	string number;
	
	do {
		cout << "=== Укажите номер поезда ===" << endl;
		cin >> number;
		tablo.clear();
		tablo.seekg(0);
		while (tablo) {
			if (getline(tablo, s)) {
				if (s.find(number) != string::npos)
				{
					cout << "=== Выбранный поезд: ===" << endl;
					cout << s << endl;
					cout << "=== Подтвердить выбор поезда? ===" << endl;
					cout << "1 - подтвердить" << endl;
					cout << "2 - вернуться к выбору поездов" << endl;
					cin >> confirmation;
				}
			}
		}
	}while (confirmation !=1);

	tablo.clear();
	tablo.seekg(0);
	if (s.find("скоростной") != string::npos) {
		trainType = "Cкоростной";
		typeTrain = 2;
	}
	if (s.find("высокоскоростной") != string::npos) {
		trainType = "Высокоскоростной";
		typeTrain = 3;
	}
	if (s.find("обычный") != string::npos) {
		trainType = "Обычный";
		typeTrain = 1;
	}

	tablo.close();
}

void direction_train() {

	bool found = false;
	fstream Dir;
	cout << "______________________________________________________" << endl;
	cout << "===Выбирите направление:===" << endl;
	cout << "Поиск: ";
	
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


				int stationIndex = -1;

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
		direction = "Казань";
	}

	else if(direction == "сочи") {
		Dir.open("../Сочи.txt");
		if (!Dir)
		{
			cout << "Error input file" << endl;
		}
		string n;
		string stantion;
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

				int stationIndex = -1;

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
		direction = "Сочи";
	}

	else if (direction == "питер" || direction == "санкт-петербург" || direction == "санкт петербург") {
		Dir.open("../Питер.txt");
		if (!Dir)
		{
			cout << "Error input file" << endl;
		}
		string n;
		string stantion;
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
				cout << "Станция: " << endl;
				cin >> stantion;
				stantion.erase(0, stantion.find_first_not_of(" "));
				stantion.erase(stantion.find_last_not_of(" ") + 1);

				
				int stationIndex = -1;

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
			direction = "Санкт-Петербург";
		}
		Dir.close();
	}

	else 
	{
		cout << "Станция отсутствует в списке!" << endl;
		found = false;
	}
	
	if (found == true)
	{
		type_ot_train();
	}
}

void train_carriage() {
	do {
		cout << "=== Выберете тип вагона ===" << endl;
		cout << "1 - Плацкарт" << endl;
		cout << "2 - Купе" << endl;
		cout << "3 - СВ" << endl;
		int num;
		cin >> num;
		switch (num) {
		case 1:
			x = 1;
			carriage = "Плацкарт";
			break;
		case 2:
			x = 2;
			carriage = "Купе";
			break;
		case 3:
			x = 3;
			carriage = "СВ";
			break;
		default:
			cout << "Такой вариант отсутствует!" << endl;
		}
	} while (x == 0);

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
			train_carriage();

			break;

		case 3:
			break;

		default:
			cout << "Такого варианта нет!!!" << endl;

		}

		cout << "_____________________________________________________________________________________________________________________" << endl;
	} while (zov != 3);

}

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	start();
	return 0;
}

