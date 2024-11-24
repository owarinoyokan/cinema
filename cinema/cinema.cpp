#include <iostream>
#include <io.h>         // Для _setmode
#include <locale>
#include <fcntl.h>      // Для режима _O_U8TEXT
#include <fstream>
#include <codecvt>      // Для преобразования UTF-8 в wide string
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    // Установим режим wide-string для вывода на консоль (поддержка Unicode)
    _setmode(_fileno(stdout), _O_U8TEXT);

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
        string text = u8"Привет, файл! ╓♀";
        fin.write(text.c_str(), text.size());

        fin.close();
        wcout << L"Файл успешно записан.❤ 💕" << endl;
    }
    else {
        wcerr << L"Не удалось открыть файл для записи." << endl;
    }

    wstring fname = L"example.txt";
    ifstream fout(fname, ios::out | ios::binary);
    if (!fout.is_open()) {
        wcerr << L"Не удалось открыть файл: " << fname << endl;
        return 1;
    }

    // Настройка локали UTF-8 для файла
    fout.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>));

    // Чтение первых трёх байтов для проверки на наличие BOM
    char bom[3] = { 0 };
    fout.read(bom, 3);
    // Проверяем, есть ли BOM
    if (!(bom[0] == '\xEF' && bom[1] == '\xBB' && bom[2] == '\xBF')) {
        // Если BOM отсутствует, возвращаем указатель в начало файла
        fout.seekg(0);
    }

    // Чтение всего содержимого файла в строку (в UTF-8)
    string content((istreambuf_iterator<char>(fout)), istreambuf_iterator<char>());

    // Конвертируем строку UTF-8 в wide string (wchar_t)
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    wstring wide_content = converter.from_bytes(content);

    // Вывод эмодзи на консоль
    wcout << L"Эмодзи из файла: " << wide_content << endl;

    fout.close();
    return 0;
}