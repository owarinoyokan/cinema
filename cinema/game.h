#ifndef GAME_H
#define GAME_H

#include "Header.h"

#include <iostream>
#include <string>
#include <chrono>
#include <Thread>
#include <windows.h>
#include <random>

using namespace std;

void setMode16();
void availablePromo();

int countMove = 0;
bool lucky = false;

void what_is_action(int res_user) {
    switch (res_user) {
    case 1: {
        wcout << L"Возможно вам повезет в следующий раз... \n\n";
        break;
    }
    case 2: {
        wcout << L"Возможно вам повезет в следующий раз... \n\n";
        break;
    }
    case 3: {
        wcout << L"Возможно вам повезет в следующий раз... \n\n";
        break;
    }
    case 4: {
        wcout << L"Вам выпала акция \"Хорошая\":\n";
        wcout << L"При покупке скидка 10% на весь чек.\n\n";
        lucky = true;
        break;
    }
    case 5: {
        wcout << L"Вам выпала акция \"Большая компания\":\n";
        wcout << L"При покупке пяти билетов скидка на каждый билет 25%\n\n";
        lucky = true;
        break;
    }
    case 6: {
        wcout << L"Вам выпала акция \"ЛУЧШАЯ АКЦИЯ\"!:\n";
        wcout << L"При покупке билета скидка 35%.\n\n";
        lucky = true;
        break;
    }
    }
}

int rando()
{
    static random_device rd;						// Генератор чисел
    static default_random_engine re(rd());			// Генератор неповтояющихся чисел на основе rd
    uniform_int_distribution<int> nums(1, 7);	// Подбор чисел в диапозоне от min до max

    return nums(re); // Генерация случайного числа
}

void PrintDiceFace(int number) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            // Условия для разных граней кубика
            if ((number == 1 && i == 3 && j == 3) || // Центр для "1"
                (number == 2 && ((i == 1 && j == 1) || (i == 5 && j == 5))) || // Диагональ для "2"
                (number == 3 && ((i == 1 && j == 1) || (i == 3 && j == 3) || (i == 5 && j == 5))) || // Диагональ + центр для "3"
                (number == 4 && ((i == 1 && j == 1) || (i == 1 && j == 5) || (i == 5 && j == 1) || (i == 5 && j == 5))) || // Углы для "4"
                (number == 5 && ((i == 1 && j == 1) || (i == 1 && j == 5) || (i == 3 && j == 3) || (i == 5 && j == 1) || (i == 5 && j == 5))) || // Углы + центр для "5"
                (number == 6 && ((i == 1 || i == 3 || i == 5) && (j == 1 || j == 5)))) { // Линии для "6"

                SetColor(0, 0); // Чёрные точки на белом фоне
                wcout << L"  ";
                SetColor(15, 0);
            }
            else {
                SetColor(8, 8); // Серый текст на сером фоне (пустое пространство)
                wcout << L"  ";
                SetColor(15, 0);
            }
        }
        wcout << endl;
    }
    SetColor(15, 0); // Сброс к стандартным цветам
    wcout << endl;
}


void TheActionGame() {
    ClearScreen();
    srand(time(0));

    if (countMove == 3 && lucky == true) {
        ClearScreen();
        PressCtrlPlus(16);
        wcout << L"Поздравляем с победой!!!" << endl;
        waitForInput();
        PressCtrlMinus(16);
        availablePromo();
    }
    else if (countMove == 3 && lucky == false) {
        ClearScreen();
        PressCtrlPlus(16);
        wcout << L"Повезет в следующий раз." << endl;
        waitForInput();
        PressCtrlMinus(16);
        availablePromo();
    }

    wcout << L"Бросайте кубик, чтобы выиграть акцию. У вас есть всего 3 попытки." << endl;
    wcout << L"Если выпадет число больше 3, то вы победили!" << endl << endl;

    while (countMove != 3 && lucky == false) {
        int rounds = 1;

        int res_user = 0;
        for (int i = 0; i < rounds; ++i) {
            int user_now = rando();

            wcout << L"Нажмите 'Enter' чтобы бросить кубик.\n";
            waitForInput();

            this_thread::sleep_for(std::chrono::milliseconds(300));
            PrintDiceFace(user_now);
            res_user += user_now;
            countMove++;

            this_thread::sleep_for(std::chrono::milliseconds(300));
            what_is_action(res_user);

            if (countMove == 3 || lucky == true) {
                ClearScreen();

                PrintDiceFace(user_now);
                what_is_action(res_user);

                PressCtrlPlus(16);

                wcout << L"Поздравляем с победой!!!" << endl;

                waitForInput();
                PressCtrlMinus(16);

                availablePromo();
            }
        }
    }
}

#endif // GAME_H