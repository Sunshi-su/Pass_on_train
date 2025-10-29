#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <algorithm>
#include <regex>
#include <sstream>
#include <random>
#include <chrono>
#include <ctime>

using namespace std;

struct Passenger {
    string Familia;
    string Familia1;
    string Imya;
    string Imya1;
    string Otchestvo;
    string Otchestvo1;
    string passport;
    string passport1;
};

struct Ticket {
    int tN;
    Passenger passenger;
    string pD;
};

int zov;
string direction;
string stantion;
string number;
bool next_func = true;
int kmToStation = 0;//множитель
int price = 1;//переменная для итоговой цены
string trainType;
int typeTrain = 0;//множитель типа поезда 1-обычный, 2-скоростной, 3-высокоскоростной.
string carriage; //Саш, это для билета переменная (тип вагона)
int x = 0;//можитель
int time_train;
//направление казань
const int N = 7, M = 2;
vector<vector<string>> matrix_kazan(M);
//направление сочи
const int C = 7, K = 2;
vector<vector<string>> matrix_sochi(K);
//напрвление питер
const int P = 7, S = 2;
vector<vector<string>> matrix_piter(S);

struct time_arrival_kazan {
    vector<int> time_default_train = { 0,3,4,5,6,7,13 };
    vector<int> time_speed_train = { 0,2,3,4,5,6,10 };
    vector<int> time_more_speed_train = { 0,1,2,3,4,5,8 };
};

struct time_arrival_sochi {
    vector<int> time_default_train = { 0,6,7,18,19,21,23 };
    vector<int> time_speed_train = { 0,5,6,17,18,10,21 };
    vector<int> time_more_speed_train = { 0,2,3,8,9,12,14 };
};

struct time_arrival_piter {
    vector<int> time_default_train = { 0,1,3,4,5,6,8 };
    vector<int> time_speed_train = { 0,1,2,3,4,5,7 };
    vector<int> time_more_speed_train = { 0,1,1,2,3,4,6 };
};

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
    int confirmation = 0;
    tablo.open("../trains.txt", ios::in);
    if (!tablo) {
        cout << "Error input file" << endl;
    }
    vivod();
    while (tablo) {
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
    } while (confirmation != 1);

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
    else {
        next_func = false;
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

        while (Dir)
        {
            if (getline(Dir, n)) {

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
                        matrix_kazan[0].push_back(name);
                        matrix_kazan[1].push_back(dist);
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

                for (int i = 0; i < matrix_kazan[0].size(); ++i) {
                    if (matrix_kazan[0][i] == stantion) {
                        found = true;
                        stationIndex = i;
                        stringstream ss(matrix_kazan[1][i]);
                        ss >> kmToStation;
                        break;
                    }
                }
            }

        }
        Dir.close();
        direction = "Казань";
    }

    else if (direction == "сочи") {
        Dir.open("../Сочи.txt");
        if (!Dir)
        {
            cout << "Error input file" << endl;
        }
        string n;

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
                        matrix_sochi[0].push_back(name);
                        matrix_sochi[1].push_back(dist);
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

                for (int i = 0; i < matrix_sochi[0].size(); ++i) {
                    if (matrix_sochi[0][i] == stantion) {
                        found = true;
                        stationIndex = i;
                        stringstream ss(matrix_sochi[1][i]);
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
                        matrix_piter[0].push_back(name);
                        matrix_piter[1].push_back(dist);
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

                for (int i = 0; i < matrix_piter[0].size(); ++i) {
                    if (matrix_piter[0][i] == stantion) {
                        found = true;
                        stationIndex = i;
                        stringstream ss(matrix_piter[1][i]);
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
    if (next_func) {
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
}

void price_ticket() {
    cout << "=== Итоговая стоимость билета: ===" << endl;
    price = typeTrain * x * kmToStation * 30;
    cout << price << "₽" << endl;
    cout << "Подтвердить покупку?" << endl;
    cout << "1 - подтвердить" << endl;
    cout << "2 - выйти" << endl;
    int dalee;
    cin >> dalee;
    if (dalee == 1) {
        cout << "Покупка произведена успешно!" << endl;
    }
    else {
        next_func = false;
    }
}

Passenger inputPassengerData() {
    Passenger passenger;
    cout << "\n=== ДАННЫЕ ПАССАЖИРА ===\n" << endl;
    cout << "Введите фамилию: ";
    cin >> passenger.Familia;
    passenger.Familia1 = passenger.Familia.substr(0, 20); // Исправлено присваивание
    cout << "Введите имя: ";
    cin >> passenger.Imya;
    passenger.Imya1 = passenger.Imya.substr(0, 15); // Исправлено присваивание
    cout << "Введите отчество: ";
    cin >> passenger.Otchestvo;
    passenger.Otchestvo1 = passenger.Otchestvo.substr(0, 20); // Исправлено присваивание
    cout << "Введите номер паспорта: ";
    cin >> passenger.passport;
    passenger.passport1 = passenger.passport.substr(0, 10); // Исправлено присваивание
    return passenger;
}

int gen() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(1000, 9999);

    return dis(gen);
}

string vremya() {
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);

    char buffer[100];
    tm time_info;

    // Кроссплатформенное получение локального времени
#ifdef _WIN32
    localtime_s(&time_info, &time);
#else
    localtime_r(&time, &time_info);
#endif

    strftime(buffer, sizeof(buffer), "%d.%m.%Y", &time_info);
    return string(buffer);
}

void time_arrival() {
    if (trainType == "обычный") {
        // Реализация функции времени прибытия
    }
}

Ticket purchaseTicket() {
    Ticket ticket;

    // Генерируем номер билета
    ticket.tN = gen();

    // Вводим данные пассажира
    ticket.passenger = inputPassengerData();

    // Устанавливаем дату покупки
    ticket.pD = vremya();

    return ticket;
}

void tiket(const Ticket& ticket) {
    ofstream out_file;
    out_file.open("../билеты.txt", ios::app);
    if (!out_file) {
        cout << "Error output file" << endl;
        exit(1);
    }

    // Форматирование вывода для корректного отображения
    string fullName = ticket.passenger.Familia1 + " " + ticket.passenger.Imya1 + " " + ticket.passenger.Otchestvo1;
    string passportInfo = "Паспорт: " + ticket.passenger.passport1;

    cout << "------------------------------------------------------------" << endl;
    cout << "| Номер билета: " << ticket.tN << setw(38) << left << " " << " |" << endl;
    cout << "| Поезд: №" << number << setw(27) << left << " " << "Дата: " << ticket.pD << setw(2) << left << " " << " |" << endl;
    cout << "| Время отправления: " << setw(36) << " " << left << " " << " |" << endl;
    cout << "| Время прибытия: " << setw(39) << " " << left << " " << " |" << endl;
    cout << "| Маршрут: Москва -> " << stantion << setw(46 - (stantion.length() + 11)) << " " << left << " " << " |" << endl;
    cout << "| Тип поезда: " << trainType << setw(43 - trainType.length()) << " " << left << " " << " |" << endl;
    cout << "| Тип вагона: " << carriage << setw(43 - carriage.length()) << " " << left << " " << " |" << endl;
    cout << "| Пассажир: " << fullName << setw(45 - fullName.length()) << " " << left << " " << " |" << endl;
    cout << "| " << passportInfo << setw(55 - passportInfo.length()) << " " << left << " " << " |" << endl;
    cout << "| Место: " << setw(30) << left << " " << " Стоимость: " << price << setw(7) << left << "  " << " |" << endl;
    cout << "------------------------------------------------------------" << endl;

    // Запись в файл
    out_file << "------------------------------------------------------------" << endl;
    out_file << "| Номер билета: " << ticket.tN << setw(38) << left << " " << " |" << endl;
    out_file << "| Поезд: №" << number << setw(27) << left << " " << "Дата: " << ticket.pD << setw(2) << left << " " << " |" << endl;
    out_file << "| Время отправления: " << setw(36) << " " << left << " " << " |" << endl;
    out_file << "| Время прибытия: " << setw(39) << " " << left << " " << " |" << endl;
    out_file << "| Маршрут: Москва -> " << stantion << setw(46 - (stantion.length() + 11)) << " " << left << " " << " |" << endl;
    out_file << "| Тип поезда: " << trainType << setw(43 - trainType.length()) << " " << left << " " << " |" << endl;
    out_file << "| Тип вагона: " << carriage << setw(43 - carriage.length()) << " " << left << " " << " |" << endl;
    out_file << "| Пассажир: " << fullName << setw(45 - fullName.length()) << " " << left << " " << " |" << endl;
    out_file << "| " << passportInfo << setw(55 - passportInfo.length()) << " " << left << " " << " |" << endl;
    out_file << "| Место: " << setw(30) << left << " " << " Стоимость: " << price << setw(7) << left << "  " << " |" << endl;
    out_file << "------------------------------------------------------------" << endl;

    out_file.close();
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
            price_ticket();
            if (next_func) {
                Ticket ticket = purchaseTicket();
                tiket(ticket);
            }
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
