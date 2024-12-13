#ifndef clk_track
#define clk_track

#include <iostream>     // ��� ������ ������ ����� � ������
#include <io.h>         // ��� ������ � _setmode 
#include <locale>       // ��� ������ � �����������
#include <fcntl.h>      // ��� ������ _O_U16TEXT
#include <fstream>      // ��� ������ � �������
#include <codecvt>      // ��� �������������� UTF-16 � wide string
#include <string>       // ��� ������ � ��������
#include <sstream>      // ��� ������ � ���������� ��������
#include <vector>       // ���� ������
#include <map>
#include <windows.h>

char keyTracing() {
    while (true) {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // ���������, ������ �� ������� �����
            return 'l';
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) { // ���������, ������ �� ������� �����
            return 'u';
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // ���������, ������ �� ������� ������
            return 'r';
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // ���������, ������ �� ������� ����
            return 'd';
        }
        else if (GetAsyncKeyState(VK_BACK) & 0x8000) { // ���������, ������ �� ������� Backspace
            return 'b';
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // ���������, ������ �� ������� ������
            return 's';
        }
    }
}

void tracingUD(short int& c) { // �������� �� ������� ����� � ����
    char a = keyTracing();
    Sleep(200); // �������� (0.2 ���), ����� �� 1 ������� ����� ��������� ����� ���
    switch (a) {
    case 'u':
        c += 1;
        break;
    case 'd':
        c -= 1;
        break;
    case 's':
        c = 200;
        break;
    default:
        break;
    }
}

void tracingLR(short int& c) { // �������� �� ������� ���� � �����
    char a = keyTracing();
    Sleep(200); // �������� (0.2 ���), ����� �� 1 ������� ����� ��������� ����� ���
    switch (a) {
    case 'r':
        c += 1;
        break;
    case 'l':
        c -= 1;
        break;
    case 's':
        c = 200;
        break;
    default:
        break;
    }
}

#endif 