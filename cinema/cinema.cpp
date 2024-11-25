#include <iostream>     // Для работы потока ввда и вывода
#include <io.h>         // Для работы с _setmode
#include <locale>       // Для работы с кодировками
#include <fcntl.h>      // Для режима _O_U8TEXT
#include <fstream>      // Для работы с файлами
#include <codecvt>      // Для преобразования UTF-8 в wide string
#include <string>       // Для работы с строками
#include <sstream>      // Для работы с строковыми потоками

using namespace std;    // Пространство имен


// Запись текста в файл с поддержкой широких символов (UTF-8)
void fileOut(string filename, const wstring& txt) {
    ofstream fout(filename, ios::binary);
    if (fout.is_open()) {
        // Записываем BOM для UTF-8
        unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
        fout.write(reinterpret_cast<const char*>(bom), sizeof(bom));

        // Преобразуем wstring в UTF-8 и записываем
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        string utf8_text = converter.to_bytes(txt);
        fout.write(utf8_text.c_str(), utf8_text.size());

        fout.close();
        wcout << L"Ваш текст был успешно записан.❤" << endl;
    }
    else {
        wcerr << L"Не удалось открыть файл для записи.😔" << endl;
    }
}


// Функция для чтения файла с широкими символами
wstring fileIn(const string& fname) {
    ifstream fin(fname, ios::binary);
    if (!fin.is_open()) {
        wcerr << L"Не удалось открыть файл для чтения." << endl;
        return L"";
    }

    // Проверяем наличие BOM
    char bom[3];
    fin.read(bom, 3);
    if (bom[0] != (char)0xEF || bom[1] != (char)0xBB || bom[2] != (char)0xBF) {
        // Если BOM нет, перемещаемся в начало файла
        fin.seekg(0);
    }

    // Читаем остальное содержимое файла
    string utf8_content((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    fin.close();

    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(utf8_content);
}


int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Установим режим wide-string для вывода на консоль (поддержка Unicode)
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    wcout << L"Проект кинотеатра." << endl;


    // Запрос текста у пользователя
    wstring input;
    wcout << L"Введите текст: ";
    getline(wcin, input); // Читаем строку (включая пробелы)

    // Запись в файл
    fileOut("example.txt", input);

    // Чтение файла
    wstring content = fileIn("example.txt");
    if (!content.empty())
        wcout << L"Содержимое файла: " << content << endl;
    return 0;
}