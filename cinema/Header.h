#ifndef HEADER_H
#define HEADER_H

#include <windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
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
    string status; // "x" — занято, "0" — номер ряда, число — номер места
};

// Структура для ряда
struct Row {
    vector<Seat> seats;
};

// Структура зала
struct Hall {
    vector<Row> rows;
};

    // Настройка консоли
// Перевод консоли в полноэкранный режим
void fullScreen() {
    COORD coord;
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);
    keybd_event(VK_MENU, 0x38, 0, 0); // нажимается Alt
    keybd_event(VK_RETURN, 0x1c, 0, 0); // нажимается Enthe
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0); //отпускается Alt
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); //отпускается Enther
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
bool isNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

// Преобразование строки в число
int stringToInt(const string& str) {
    return stoi(str);
}


    // Функции отрисовки
// Функция отрисовки занятого места
void drawOccupiedBox(int& x, int y) {
    SetColor(7, 7);
    setCursorPosition(x, y + 1);
    cout << "|    |";
    setCursorPosition(x, y + 2);
    cout << "| " << " " << " " << " |";
    setCursorPosition(x, y + 3);
    cout << "|____|";
    SetColor(15, 0);
    x += BOX_WIDTH + 1;
}

// Функция отрисовки номера ряда
void drawRowNumberBox(int& x, int y, int rowNumber) {
    x += 1;
    setCursorPosition(x, y + 2);
    cout << "Row " << rowNumber;
    x += BOX_WIDTH + 1;
}

// Функция отрисовки свободного места
void drawAvailableBox(int& x, int y, const string& number) {
    setCursorPosition(x, y);
    cout << " ____ ";
    setCursorPosition(x, y + 1);
    cout << "|    |";
    setCursorPosition(x, y + 2);
    cout << "| " << (stringToInt(number) < 10 ? " " : "") << number << " |";
    setCursorPosition(x, y + 3);
    cout << "|____|";
    x += BOX_WIDTH + 1;
}

// Рисуем рамку для конкретного места
void drawBox(int& x, int y, const Seat& seat, int rowNumber) {
    if (isNumber(seat.status) && seat.status != "0") {
        drawAvailableBox(x, y, seat.status);
    }
    else if (seat.status == "x") {
        drawOccupiedBox(x, y);
    }
    else if (seat.status == "0") {
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

// Генерация зала
void GenerationRoom(Hall& hall, const int rowCount, const int placeCount) {
    hall.rows.resize(rowCount);
    for (int i = 0; i < rowCount; ++i) {
        hall.rows[i].seats.resize(placeCount);
        for (int j = 0; j < placeCount; ++j) {
            if (j == 0 || j == placeCount - 1) {
                hall.rows[i].seats[j].status = "0";
            }
            else {
                int rand_not_free = rand() % CHANSE_NOT_FREE_PLACES;
                hall.rows[i].seats[j].status = (rand_not_free == 0) ? "x" : to_string(j);
            }
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


// Kino pmi
void waitForInput() {
    cout << "Нажмите Enter, чтобы выйти..." << endl;
    cin.get();
}

void initializeConsole() {
    fullScreen();
    this_thread::sleep_for(chrono::milliseconds(100));
    srand(static_cast<unsigned>(time(nullptr)));
    this_thread::sleep_for(chrono::milliseconds(100));
}

void DrawHall(Hall& hall, int rowCount, int placeCount) {
    int y = 0;
    for (size_t i = 0; i < hall.rows.size(); ++i) {
        drawRow(y, hall.rows[i], i + 1);
        y += BOX_HEIGHT + 2;
    }
    setCursorPosition(0, y);
}
#endif // HEADER_H
#pragma once