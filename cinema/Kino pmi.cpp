#include "Header.h"

using namespace std;
using namespace Config;

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
void changePlaces(Hall& hall, int row, int place) {
    row -= 1;  // коррекция индекса ряда  
    if (hall.rows[row].seats[place].status == "0" || hall.rows[row].seats[place].status == "x")
        cout << "Место уже занято, выберите пожалуйста другое место\n";
    else {
        ClearScreen();
        cout << "Выбор зафиксирован\n";
        hall.rows[row].seats[place].status.clear();
        hall.rows[row].seats[place].status = "x";
    }
}

//int main() {
//    setlocale(LC_ALL, "RU");
//    srand(time(0));
//    const int rowCount = 8;
//    const int placeCount = 18;// 16 и 2 для отрисовки номера ряда с двух сторон
//
//    Hall hall;
//    GenerationRoom(hall, rowCount, placeCount);
//    initializeConsole();
//    DrawHall(hall, rowCount, placeCount);
//
//    ///пример замены сущесвующего места без проверок индекса
//    /* int changeRow, changePalace;
//    cout << "Введите номер ряда: ";
//    cin >> changeRow;
//    cout << "\nВведите номер места: ";
//    cin >> changePalace;
//    changePlaces(hall, changeRow, changePalace);
//    DrawHall(hall, rowCount, placeCount);*/
//
//
//    waitForInput();
//    //closeWindow();
//    return 0;
//}