#ifndef CLICKTRACKING_H
#define CLICKTRACKING_H

#include "Header.h"
void setMode16();

#include <iostream>     // Äëÿ ðàáîòû ïîòîêà ââîäà è âûâîäà
#include <io.h>         // Äëÿ ðàáîòû ñ _setmode 
#include <locale>       // Äëÿ ðàáîòû ñ êîäèðîâêàìè
#include <fcntl.h>      // Äëÿ ðåæèìà _O_U16TEXT
#include <fstream>      // Äëÿ ðàáîòû ñ ôàéëàìè
#include <codecvt>      // Äëÿ ïðåîáðàçîâàíèÿ UTF-16 â wide string
#include <string>       // Äëÿ ðàáîòû ñ ñòðîêàìè
#include <sstream>      // Äëÿ ðàáîòû ñ ñòðîêîâûìè ïîòîêàìè
#include <vector>       // Ñàìè çíàåòå
#include <map>
#include <windows.h>

char keyTracing() {
    while (true) {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // Ïðîâåðÿåì, íàæàòà ëè êëàâèøà âëåâî
            return L'l';
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) { // Ïðîâåðÿåì, íàæàòà ëè êëàâèøà ââåðõ
            return L'u';
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // Ïðîâåðÿåì, íàæàòà ëè êëàâèøà âïðàâî
            return L'r';
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Ïðîâåðÿåì, íàæàòà ëè êëàâèøà âíèç
            return L'd';
        }
        else if (GetAsyncKeyState(VK_BACK) & 0x8000) { // Ïðîâåðÿåì, íàæàòà ëè êëàâèøà Backspace
            return L'b';
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // Ïðîâåðÿåì, íàæàòà ëè êëàâèøà Ïðîáåë
            return L's';
        }
    }
}

void tracingUD(short int& c) { // Ïðîâåðêà íà íàæàòèå ââåðõ è âíèç
    char a = keyTracing();
    Sleep(200); // Çàäåðæêà (0.2 ñåê), èíà÷å çà 1 íàæàòèå áóäåò âûïîëíåíî ìíîãî ðàç
    switch (a) {
    case L'u':
        c += 1;
        break;
    case L'd':
        c -= 1;
        break;
    case L's':
        c = 200;
        break;
    default:
        break;
    }
}

void tracingLR(short int& c) { // Ïðîâåðêà íà íàæàòèå ëåâî è ïðàâî
    wchar_t a = keyTracing();
    Sleep(200); // Çàäåðæêà (0.2 ñåê), èíà÷å çà 1 íàæàòèå áóäåò âûïîëíåíî ìíîãî ðàç
    switch (a) {
    case L'r':
        c += 1;
        break;
    case L'l':
        c -= 1;
        break;
    case L's':
        c = 200;
        break;
    default:
        break;
    }
}

#endif // CLICKTRACKING_H