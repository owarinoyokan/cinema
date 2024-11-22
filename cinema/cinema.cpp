#include <iostream>
#include <io.h>
#include <fcntl.h>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    int old_mode = _setmode(_fileno(stdout), _O_U16TEXT);


    // Выполняем Unicode-вывод
    wcout << L"Йоу, ╬†♂\n";
    // Возвращаем исходный режим
    _setmode(_fileno(stdout), old_mode);


    cout << "Йоу" << endl;
}