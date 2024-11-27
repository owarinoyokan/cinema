#include "Header.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;
using namespace Config;

// ������� ��� �������� ����� �����
bool correctInput(int& number) {
    string input;
    getline(cin, input); // ������ ������
    if (input.empty()) {
        return false; // �������� �� ������ ����
    }
    try {
        size_t pos;
        number = stoi(input, &pos); // ������� ������������� ������ � �����
        if (pos != input.size()) {
            return false; // ���� ���� ������ �������
        }
    }
    catch (const invalid_argument&) {
        return false; // ���� �������������� �� �������
    }
    catch (const out_of_range&) {
        return false; // ���� ����� ������� �� �������
    }
    return true; // �����
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

void waitForInput() {
    cout << "������� Enter, ����� �����..." << endl;
    cin.get();
}

//�������� ������ void choosingPlace()
void changePlaces(Hall& hall, int row, int place) {
    row -= 1;  // ��������� ������� ����  
    if (hall.rows[row].seats[place].status == "0" || hall.rows[row].seats[place].status == "x")
        cout << "����� ��� ������, �������� ���������� ������ �����\n";
    else {
        ClearScreen();
        cout << "����� ������������\n";
        hall.rows[row].seats[place].status.clear();
        hall.rows[row].seats[place].status = "x";
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0));
    const int rowCount = 8;
    const int placeCount = 18;// 16 � 2 ��� ��������� ������ ���� � ���� ������

    Hall hall;
    GenerationRoom(hall, rowCount, placeCount);
    initializeConsole();
    DrawHall(hall, rowCount, placeCount);

    ///������ ������ ������������ ����� ��� �������� �������
    /* int changeRow, changePalace;
    cout << "������� ����� ����: ";
    cin >> changeRow;
    cout << "\n������� ����� �����: ";
    cin >> changePalace;
    changePlaces(hall, changeRow, changePalace);
    DrawHall(hall, rowCount, placeCount);*/


    waitForInput();
    //closeWindow();
    return 0;
}
