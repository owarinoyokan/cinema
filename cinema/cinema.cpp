#include <iostream>
#include <io.h>
#include <fcntl.h>
using namespace std;

//Функция для вывода alt-кода (широкие символы типа wchar_t)
void Wout() {
    int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);
    // Выполняем Unicode-вывод
    wcout << L"Заготовка под вывод alt-кода.\n╬†♂\n";
    // Возвращаем исходный режим
    _setmode(_fileno(stdout), old_mode);
}

int main() {
    setlocale(LC_ALL, "ru");
    
    Wout();

    cout << "\nЙоу" << endl;
    cout << "\nПобеда" << endl;
}