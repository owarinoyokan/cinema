#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>
using namespace std;
// Конфигурация программы
namespace Config {
    constexpr int BOX_WIDTH = 6;              // Ширина бокса
    constexpr int BOX_HEIGHT = 3;             // Высота бокса
    constexpr int CHANSE_NOT_FREE_PLACES = 9; // Вероятность занятого места
}

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
void fullScreen();
void setCursorPosition(int x, int y);
void SetColor(int text, int background);

// Проверка и преобразование строк
bool isNumber(const string& str);
int stringToInt(const string& str);

// Функции отрисовки
void drawBox(int& x, int y, const Seat& seat, int rowNumber);
void drawRow(int y, const Row& row, int rowNumber);

// Генерация зала
void GenerationRoom(Hall& hall, const int rowCount, const int placeCount);

//Очистка экрана :
void ClearScreen();

void closeWindow();
#endif // HEADER_H
#pragma once
