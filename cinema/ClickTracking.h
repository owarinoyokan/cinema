#ifndef clk_track
#define clk_track

#include <iostream>     // Для работы потока ввода и вывода
#include <io.h>         // Для работы с _setmode 
#include <locale>       // Для работы с кодировками
#include <fcntl.h>      // Для режима _O_U16TEXT
#include <fstream>      // Для работы с файлами
#include <codecvt>      // Для преобразования UTF-16 в wide string
#include <string>       // Для работы с строками
#include <sstream>      // Для работы с строковыми потоками
#include <vector>       // Сами знаете
#include <map>
#include <windows.h>

char keyTracing() {
    while (true) {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // Проверяем, нажата ли клавиша влево
            return 'l';
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) { // Проверяем, нажата ли клавиша вверх
            return 'u';
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // Проверяем, нажата ли клавиша вправо
            return 'r';
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Проверяем, нажата ли клавиша вниз
            return 'd';
        }
        else if (GetAsyncKeyState(VK_BACK) & 0x8000) { // Проверяем, нажата ли клавиша Backspace
            return 'b';
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // Проверяем, нажата ли клавиша Пробел
            return 's';
        }
    }
}

void tracingUD(short int& c) { // Проверка на нажатие вверх и вниз
    char a = keyTracing();
    Sleep(200); // Задержка (0.2 сек), иначе за 1 нажатие будет выполнено много раз
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

void tracingLR(short int& c) { // Проверка на нажатие лево и право
    char a = keyTracing();
    Sleep(200); // Задержка (0.2 сек), иначе за 1 нажатие будет выполнено много раз
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