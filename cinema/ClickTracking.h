#ifndef CLICKTRACKING_H
#define CLICKTRACKING_H

#include "Header.h"
void setMode16();

#include <iostream>     
#include <io.h>         
#include <locale>       
#include <fcntl.h>      
#include <fstream>      
#include <codecvt>      
#include <string>       
#include <sstream>      
#include <vector>       
#include <map>
#include <windows.h>

char keyTracingArrow() {
    while (true) {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // Отслеживание нажатия клавиши Влево
            return L'l';
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) { // Вверх
            return L'u';
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // Вправо
            return L'r';
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Вниз
            return L'd';
        }
        else if (GetAsyncKeyState(VK_BACK) & 0x8000) { // BACKSPACE
            return L'b';
        }
        else if (GetAsyncKeyState(VK_RETURN) & 0x8000) { // ENTER
            return L'e';
        }
    }
}

char keyTracing() {
    while (true) {
        for (int i = 49; i <= 57; ++i) { // Цифры от 1 до 9
            if (GetAsyncKeyState(i) & 0x8000)
                return char(i);
        }
        if (GetAsyncKeyState(VK_BACK) & 0x8000) // Backspace
            return L'b';
        else if (GetAsyncKeyState(VK_RETURN) & 0x8000) // Enter
            return L'e';
    }
}

short int tracing(short int c) { // принимает максимальное количество чисел для выбора и возращает выбранное число или 0 в случае выхода
    char a = keyTracing();
    Sleep(200);
    switch (a) {
    case '1':
        if (1 <= c)
            return 1;
        break;
    case '2':
        if (2 <= c)
            return 2;
        break;
    case '3':
        if (3 <= c)
            return 3;
        break;
    case '4':
        if (4 <= c)
            return 4;
        break;
    case '5':
        if (5 <= c)
            return 5;
        break;
    case '6':
        if (6 <= c)
            return 6;
        break;
    case '7':
        if (7 <= c)
            return 7;
        break;
    case '8':
        if (8 <= c)
            return 8;
        break;
    case '9':
        if (9 <= c)
            return 9;
        break;
    case 'b':
        return 0;
        break;
    }
    tracing(c);
}

void tracingLR(short int& c) {
    wchar_t a = keyTracingArrow();
    Sleep(200);
    switch (a) {
    case L'r':
        c += 1;
        break;
    case L'l':
        c -= 1;
        break;
    case L'e':
        c = 200;
        break;
    default:
        break;
    }
}

#endif 