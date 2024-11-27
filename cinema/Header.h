#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>
using namespace std;
// ������������ ���������
namespace Config {
    constexpr int BOX_WIDTH = 6;              // ������ �����
    constexpr int BOX_HEIGHT = 3;             // ������ �����
    constexpr int CHANSE_NOT_FREE_PLACES = 9; // ����������� �������� �����
}

// ��������� ��� ������������� ������ �����
struct Seat {
    string status; // "x" � ������, "0" � ����� ����, ����� � ����� �����
};

// ��������� ��� ����
struct Row {
    vector<Seat> seats;
};

// ��������� ����
struct Hall {
    vector<Row> rows;
};

// ��������� �������
void fullScreen();
void setCursorPosition(int x, int y);
void SetColor(int text, int background);

// �������� � �������������� �����
bool isNumber(const string& str);
int stringToInt(const string& str);

// ������� ���������
void drawBox(int& x, int y, const Seat& seat, int rowNumber);
void drawRow(int y, const Row& row, int rowNumber);

// ��������� ����
void GenerationRoom(Hall& hall, const int rowCount, const int placeCount);

//������� ������ :
void ClearScreen();

void closeWindow();
#endif // HEADER_H
#pragma once
