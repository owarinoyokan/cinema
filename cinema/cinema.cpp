#include <iostream>     // Для работы потока ввода и вывода
#include <io.h>         // Для работы с _setmode
#include <locale>       // Для работы с кодировками
#include <fcntl.h>      // Для режима _O_U8TEXT
#include <fstream>      // Для работы с файлами
#include <codecvt>      // Для преобразования UTF-8 в wide string
#include <string>       // Для работы с строками
#include <sstream>      // Для работы с строковыми потоками

using namespace std;    // Пространство имен


// Запись текста в файл с поддержкой широких символов (UTF-16)
void fileOut(string filename) {

    // Запрос текста у пользователя
    wstring input;
    wcout << L"Введите текст: ";
    getline(wcin, input); // Читаем строку (включая пробелы)

    // Открываем файл в бинарном режиме
    ofstream fout(filename, ios::binary);
    if (!fout.is_open()) {
        wcerr << L"Ошибка открытия файла для записи." << endl;
        return;
    }

    // Преобразуем wstring в UTF-16LE и записываем
    wstring_convert<codecvt_utf8_utf16<wchar_t, 0x10FFFF, little_endian>> converter;
    string utf16_text = converter.to_bytes(input);
    fout.write(utf16_text.c_str(), utf16_text.size());
        
    fout.close();
    wcout << L"Ваш текст успешно записан." << endl;
}


// Функция для чтения файла с широкими символами
wstring fileIn(const string& fname) {
    ifstream fin(fname, ios::binary);
    if (!fin.is_open()) {
        wcerr << L"Не удалось открыть файл для чтения." << endl;
        return L"";
    }

    // Читаем остальное содержимое файла
    string utf16_content((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    fin.close();

    wstring_convert<codecvt_utf8_utf16<wchar_t, 0x10FFFF, little_endian>> converter;
    return converter.from_bytes(utf16_content);
}


int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Установим режим wide-string для вывода на консоль (поддержка Unicode)
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    wcout << L"Проект кинотеатра.🎬" << endl;
    
    // Запись в файл
    fileOut("example.txt");

    // Чтение файла
    wstring content = fileIn("example.txt");
    if (!content.empty())
        wcout << L"Содержимое файла: " << content << endl;

    wstring content1 = fileIn("check.txt");
    if (!content.empty())
        wcout << L"\n" << content1 << endl;
    return 0;
}