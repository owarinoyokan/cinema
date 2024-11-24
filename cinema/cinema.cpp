#include <iostream>
#include <io.h>         // Для _setmode
#include <locale>       // Для работы с кодировками
#include <fcntl.h>      // Для режима _O_U8TEXT
#include <fstream>
#include <codecvt>      // Для преобразования UTF-8 в wide string
#include <string>
#include <vector>
#include <sstream>      // Для раюооты с строковыми потоками

using namespace std;

void fileIn(string filename, string txt) {
    // Работа с файлом в UTF-8
    ofstream fin(filename, ios::binary);
    if (fin.is_open()) {
        // Записываем строку с эмодзи
        string text = txt;
        fin.write(text.c_str(), text.size());

        fin.close();
        wcout << L"Файл успешно записан.❤ 💕" << endl;
    }
    else {
        wcerr << L"Не удалось открыть файл для записи." << endl;
    }
}

// Функция для чтения файла с широкими символами
wstring fileOut(const string& fname) {
    // Чтение файла с широкими символами
    wifstream fout(fname, ios::binary); // Используем wifstream вместо ifstream
    if (!fout.is_open()) {
        wcout << L"Не удалось открыть файл" << endl;
        return L""; // Возвращаем пустую строку в случае ошибки
    }

    // Устанавливаем локаль UTF-8 (зависит от вашей ОС и среды)
    fout.imbue(locale("en_US.UTF-8"));

    wstringstream buffer;
    buffer << fout.rdbuf();
    return buffer.str();
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    // Установим режим wide-string для вывода на консоль (поддержка Unicode)
    _setmode(_fileno(stdout), _O_U8TEXT);

    wcout << L"Проект кинотеатра." << endl;

    // Запись в файл
    fileIn("example.txt", u8"Тестовый запуск.─|♀▄");
    // Чтение файла
    wstring content = fileOut("example.txt");
    if (!content.empty())
        wcout << L"Содержимое файла: " << content << endl;
    return 0;
}