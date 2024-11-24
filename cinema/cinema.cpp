#include <iostream>
#include <io.h>         // Для _setmode
#include <locale>
#include <fcntl.h>      // Для режима _O_U8TEXT
#include <fstream>
#include <codecvt>      // Для преобразования UTF-8 в wide string
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    // Установим режим wide-string для вывода на консоль (поддержка Unicode)
    _setmode(_fileno(stdout), _O_U16TEXT);

    wcout << L"Заготовка под вывод alt-кода.\n╬†♂\n🥵\n";
    wcout << L"Йоу😶‍🌫️" << endl;
    

    // Работа с файлом в UTF-8
    ofstream fin("example.txt", ios::binary);
    if (fin.is_open()) {
        // Добавляем BOM для UTF-8
        fin.put(0xEF); fin.put(0xBB); fin.put(0xBF);
        /*
        Эти строка кода добавляет BOM (Byte Order Mark) в начало файла, 
        что указывает текстовым редакторам и программам, 
        что файл использует кодировку UTF-8.
        */

        // Записываем строку с эмодзи
        string text = u8"Привет, файл! 🌍🌟";
        fin.write(text.c_str(), text.size());

        fin.close();
        wcout << L"Файл успешно записан.❤ 💕" << endl;
    }
    else {
        wcerr << L"Не удалось открыть файл для записи." << endl;
    }

    wstring fname = L"example.txt";
    wifstream fout(fname,  ios::binary);
    if (!fout.is_open()) {
        wcerr << L"Не удалось открыть файл: " << fname << endl;
        return 1;
    }

    // Настройка локали UTF-8 для файла
    fout.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>));

    // Пропускаем BOM, если он есть
    wchar_t bom;
    fout.get(bom);
    if (bom != 0xFEFF) {
        fout.unget(); // Возвращаем символ, если это не BOM
    }

    // Чтение строк из файла и вывод на консоль
    wstring line;
    while (getline(fout, line)) {
        wcout << line << endl;
    }

    fout.close();
    return 0;
}