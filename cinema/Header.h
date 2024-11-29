#ifndef HEADER_H
#define HEADER_H

#include <windows.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <thread>
#include <locale>

using namespace std;

// Конфигурация программы
namespace Config {
    constexpr int BOX_WIDTH = 6;              // Ширина бокса
    constexpr int BOX_HEIGHT = 3;             // Высота бокса
    constexpr int CHANSE_NOT_FREE_PLACES = 9; // Вероятность занятого места
}
using namespace Config;

// Структура для представления одного места
struct Seat {
    wstring status; // "x" — занято, "0" — номер ряда, число — номер места
};

// Структура для ряда
struct Row {
    vector<Seat> seats;
};

// Структура зала
struct Session {
    vector<Row> rows;
    wstring film_name;
    wstring time_film;
};

//структура Сеанса
struct Day {
    vector<Session> Session_one;
    vector<Session> Session_two;
    vector<Session> Session_three;
};

// Настройка консоли
// Перевод консоли в полноэкранный режим

void fullScreen() {
    COORD coord;
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);
    keybd_event(VK_MENU, 0, 0, 0); // Нажатие Alt
    keybd_event(VK_RETURN, 0, 0, 0); // Нажатие Enter
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); // Отпуск Enter
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); // Отпуск Alt
    this_thread::sleep_for(chrono::milliseconds(100));
}


// Установка позиции курсора
void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Установка цвета текста и фона
void SetColor(int text, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background << 4) | text);
}


// Проверка и преобразование строк
// Проверка, является ли строка числом
bool isNumber(const wstring& str) {
    for (wchar_t c : str) {
        if (!iswdigit(c)) {
            return false;
        }
    }
    return true;
}
// Преобразование строки в число
int stringToInt(const wstring& str) {
    return stoi(str);
}


// Функции отрисовки
// Функция отрисовки занятого места
void drawOccupiedBox(int& x, int y) {
    SetColor(7, 7);
    setCursorPosition(x, y + 1);
    wcout << L"|    |";
    setCursorPosition(x, y + 2);
    wcout << L"| " << L" " << L" " << L" |";
    setCursorPosition(x, y + 3);
    wcout << L"|____|";
    SetColor(15, 0);
    x += BOX_WIDTH + 1;
}

// Функция отрисовки номера ряда
void drawRowNumberBox(int& x, int y, int rowNumber) {
    x += 1;
    setCursorPosition(x, y + 2);
    wcout << L"Row " << rowNumber;
    x += BOX_WIDTH + 1;
}

// Функция отрисовки свободного места
void drawAvailableBox(int& x, int y, const wstring& number) {
    setCursorPosition(x, y);
    wcout << L" ____ ";
    setCursorPosition(x, y + 1);
    wcout << L"|    |";
    setCursorPosition(x, y + 2);
    wcout << L"| " << (stringToInt(number) < 10 ? L" " : L"") << number << L" |";
    setCursorPosition(x, y + 3);
    wcout << L"|____|";
    x += BOX_WIDTH + 1;
}

// Рисуем рамку для конкретного места
void drawBox(int& x, int y, const Seat& seat, int rowNumber) {
    if (isNumber(seat.status) && seat.status != L"0") {
        drawAvailableBox(x, y, seat.status);
    }
    else if (seat.status == L"x") {
        drawOccupiedBox(x, y);
    }
    else if (seat.status == L"0") {
        drawRowNumberBox(x, y, rowNumber);
    }
}

//// Отрисовка ряда
void drawRow(int y, const Row& row, int rowNumber) {
    int x = 0;
    for (const auto& seat : row.seats) {
        drawBox(x, y, seat, rowNumber);
    }
}

wstring utf8ToUtf16(const string& utf8Str) {
    if (utf8Str.empty()) return L"";

    int size_needed = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), (int)utf8Str.size(), NULL, 0);
    wstring utf16Str(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), (int)utf8Str.size(), &utf16Str[0], size_needed);
    return utf16Str;
}

// Генерация зала
void GenerationRoom(Session& session, const int rowCount, const int placeCount, wstring name, wstring time_f) {
    session.rows.resize(rowCount);
    session.film_name = name;
    session.time_film = time_f;
    for (int i = 0; i < rowCount; ++i) {
        session.rows[i].seats.resize(placeCount);
        for (int j = 0; j < placeCount; ++j) {
            if (j == 0 || j == placeCount - 1) {
                session.rows[i].seats[j].status = L"0";
            }
            else {
                int rand_not_free = rand() % CHANSE_NOT_FREE_PLACES;
                session.rows[i].seats[j].status = (rand_not_free == 0) ? L"x" : to_wstring(j);
            }
        }
    }
}

wstring replaceDash(wstring str) {
    replace(str.begin(), str.end(), L'—', L'-');
    return str;
}

// Удаление символа \r из строки
void removeCarriageReturn(std::wstring& line) {
    line.erase(std::remove(line.begin(), line.end(), L'\r'), line.end());
}


// Генерация дня с чтением из файла
void GenerationDay(Day& day, const string& filename, int rowCount, int placeCount) {
    // Читаем файл в строку
    ifstream fin(filename, ios::binary);
    if (!fin) {
        wcerr << L"Ошибка: Не удалось открыть файл." << endl;
        return;
    }

    // Читаем содержимое файла
    ostringstream buffer;
    buffer << fin.rdbuf();
    string utf8Content = buffer.str();
    fin.close();

    // Конвертация из UTF-8 в UTF-16
    wstring fileContent = utf8ToUtf16(utf8Content);

    if (fileContent.empty()) {
        wcerr << L"Ошибка: Файл пуст." << endl;
        return;
    }
    // Обработка содержимого файла
    wstringstream stream(fileContent);
    wstring line;
    vector<Session>* currentSessionGroup = nullptr;

    while (getline(stream, line)) {
        removeCarriageReturn(line); // Удаляем \r из строки

        line = replaceDash(line);  // Замена длинных дефисов
        if (line.empty()) {
            continue; // Игнорируем пустые строки
        }


        if (line == L"Cinema room 1") {
            currentSessionGroup = &day.Session_one;
        }
        else if (line == L"Cinema room 2") {
            currentSessionGroup = &day.Session_two;
        }
        else if (line == L"Cinema room 3 ") {
            currentSessionGroup = &day.Session_three;
        }
        else if (currentSessionGroup && !line.empty() && iswdigit(line[0])) {
            int sessionCount = 0;
            try {
                sessionCount = stoi(line); // Преобразуем строку в число
                currentSessionGroup->resize(sessionCount);
            }
            catch (const exception&) {
                wcerr << L"Ошибка: Некорректное количество сеансов." << endl;
                return;
            }

            for (int i = 0; i < sessionCount; ++i) {
                wstring timeRange, filmName;

                if (!getline(stream, timeRange) || timeRange.empty()) {
                    wcerr << L"Ошибка: Некорректное или отсутствует время фильма." << endl;
                    return;
                }

                if (!getline(stream, filmName) || filmName.empty()) {
                    wcerr << L"Ошибка: Некорректное или отсутствует название фильма." << endl;
                    return;
                }

                (*currentSessionGroup)[i].film_name = filmName;
                (*currentSessionGroup)[i].time_film = timeRange;

                GenerationRoom((*currentSessionGroup)[i], rowCount, placeCount, filmName, timeRange);
            }
        }
        else {
            wcerr << L"Ошибка: Неизвестная строка в файле." << endl;
            return;
        }
    }
}


//Очистка экрана :
void ClearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count, cellCount;
    COORD homeCoords = { 0, 0 };

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        cellCount = csbi.dwSize.X * csbi.dwSize.Y; // Исправлено
        FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
        SetConsoleCursorPosition(hConsole, homeCoords);
    }
}

void closeWindow() {
    // Нажимаем Alt
    keybd_event(VK_MENU, 0x38, 0, 0);
    // Нажимаем F4
    keybd_event(VK_F4, 0x3E, 0, 0);
    // Отпускаем F4
    keybd_event(VK_F4, 0x3E, KEYEVENTF_KEYUP, 0);
    // Отпускаем Alt
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}


void waitForInput() {
    system("pause");
}

void DrawSession(Session& session, int rowCount, int placeCount) {
    int y = 0;
    wcout << setw(65) << session.time_film << endl;
    ++y;
    wcout << setw(67) << session.film_name << endl;
    ++y;
    for (size_t i = 0; i < session.rows.size(); ++i) {
        drawRow(y, session.rows[i], i + 1);
        y += BOX_HEIGHT + 2;
    }
    setCursorPosition(0, y);
}

// Функция для проверки ввода числа
bool correctInput(int& number) {
    string input;
    getline(cin, input); // Читаем строку
    if (input.empty()) {
        return false; // Проверка на пустой ввод
    }
    try {
        size_t pos;
        number = stoi(input, &pos); // Пробуем преобразовать строку в число
        if (pos != input.size()) {
            return false; // Если есть лишние символы
        }
    }
    catch (const invalid_argument&) {
        return false; // Если преобразование не удалось
    }
    catch (const out_of_range&) {
        return false; // Если число выходит за пределы
    }
    return true; // Успех
}


//черновая версия void choosingPlace()
void changePlaces(Session& session, int row, int place) {
    --row; // Приведение к 0-индексации
    --place; // Приведение к 0-индексации
    if (row < 0 || row >= session.rows.size() || place < 0 || place >= session.rows[row].seats.size()) {
        wcout << L"Некорректный выбор места.\n";
        return;
    }

    if (session.rows[row].seats[place].status == L"x" || session.rows[row].seats[place].status == L"0") {
        wcout << L"Место занято, выберите другое.\n";
    }
    else {
        ClearScreen();
        wcout << L"Место успешно забронировано.\n";
        session.rows[row].seats[place].status = L"x";
    }
}

#endif // HEADER_H