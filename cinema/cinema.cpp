#include <iostream>     // Для работы потока ввода и вывода
#include <io.h>         // Для работы с _setmode
#include <locale>       // Для работы с кодировками
#include <fcntl.h>      // Для режима _O_U16TEXT
#include <fstream>      // Для работы с файлами
#include <codecvt>      // Для преобразования UTF-8 в wide string
#include <string>       // Для работы с строками
#include <sstream>      // Для работы с строковыми потоками
#include <vector>       // Сами знаете

using namespace std;    // Пространство имен


void extranceToCinema(); // Функция входа в кино, предлагает самый первый выбор
void availablePromo(); // Функция для просмотра доспупных акций
void movieSelection(); // Функция выводяшая список фильмов с краткой информацией
void detailedInform(); // Функция выводящая детали фильма
void choosingPlace(); // меню выбора места
wstring fileIn(const string& fname); // Функция для чтения файла с широкими символами
void sessionSelection();


void extranceToCinema() { // Функция входа в кино, предлагает самый первый выбор
    short int input;
    //wcout << L"\n" << fileIn(" file name ") << endl; // Вывод файла
    wcout << L"Что вы желаете сделать?" << endl;
    wcout << L"Нажмите '1', чтобы выбрать фильм" << endl;
    wcout << L"Нажмите '2', чтобы посмотреть доступные акции" << endl;
    wcout << L"Нажмите '0', чтобы выйти" << endl;
    wcin >> input;
    system("cls"); // Очистка консоли
    switch (input) {
    case 1:
        movieSelection(); // Функция выводяшая список фильмов с краткой информацией
        break;
    case 2:
        availablePromo(); // Функция для просмотра доспупных акций
        break;
    case 3:
        // место под ф-ю буфета
        break;
    case 0:
        // что-то для выхода
        break;
    }
}

void availablePromo() { // Функция для просмотра доспупных акций
    short int input;
    //wcout << L"\n" << fileIn(" file name ") << endl; // Вывод файла
    wcout << L"Список доступных акций ... " << endl;
    wcout << L"Введите номер акции, чтобы посмотреть подробное описание" << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcin >> input;
    system("cls");
    if (input == 0)
        extranceToCinema(); // Возврат назад (к предыдущей функции)
    else {
        // место для функции выводящей подробную информацию про акции
    }
}

void movieSelection() { // Функция выводяшая список фильмов с краткой информацией
    short int input;
    wcout << L"\n" << fileIn("cimema_info.txt") << endl; // Вывод файла
    //wcout << L"Список фильмов с краткой информацией ... " << endl;
    wcout << L"Нажмите '1', чтобы выбрать сеанс" << endl;
    //wcout << L"Нажмите '2', чтобы посмотреть детали" << endl; // Возможно это не стоит показывать отдельно 
                                                                // а показывать принудительно после выбора сеанса

    wcout << L"Нажмите '3', чтобы использовать фильтр" << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcin >> input;
    system("cls");
    switch (input) {
    case 1:
        //choosingPlace(); // выбор сеанса >> меню выбора места >> после выбора мест использовать функцию оплаты
        sessionSelection();
        break;
    //case 2:
    //    detailedInform(); // Функция выводящая детали фильма
    //    break;
    case 3:
        // место для функции фильтра
        break;
    case 0:
        extranceToCinema(); // Возврат назад (к предыдущей функции)
        break;
    }
}

void sessionSelection() { // Выбор сеанса >> после выбора следует выбор мест
    wcout << L"\n" << fileIn("cimema_info.txt") << endl; // В таком случае отдельная функция не нужна
    short int input;
    //wcout << L"\n" << fileIn("cimema_info.txt") << endl; // Вывод файла
    wcout << L"Выберите фильм который хотите посмотреть" << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcin >> input;
    system("cls");
    // Сюда вставить функцию выводящую кинозал по выбору пользователя >> она будет вести на choosingPlace()
    if (input == 0)
        movieSelection();
}

void detailedInform() { // Функция выводящая детали фильма
    short int input;
    wcout << L"\n" << fileIn("film_info.txt") << endl; // Вывод файла
    wcout << L"Детальная информация про фильм ... " << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcin >> input;
    system("cls");
    movieSelection(); // Возврат назад (к предыдущей функции)
}

void choosingPlace() { // меню выбора места << после выбора мест использовать функцию оплаты
    short int input;
    wcout << L"\n" << fileIn("places.txt") << endl; // Вывод файла
    wcout << L"Выберите место" << endl;
    wcout << L"Нажмите '1', чтобы выбрать одно место" << endl;
    wcout << L"Нажмите '2', чтобы выбрать сразу несколько мест" << endl;
    wcout << L"Нажмите '3', для автоматического подбора места" << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcin >> input;
    system("cls");
    switch (input) {
    case 1:
        // место для функции выбора места
        break;
    case 2:
        // место для функции выбора нескольких мест ( можно объединить с 1 )
        break;
    case 3:
        // место для функции авт подбора места 
        break;
    case 0:
        //movieSelection(); // Возврат назад (к предыдущей функции)

        break;
    }
}

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
    // Установим режим wide-string для вывода на консоль (поддержка Unicode)
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    system("cls");      // Очистка консоли

    wcout << L"Проект кинотеатра.🎬" << endl;

    // Запись в файл
    fileOut("example.txt");

    // Чтение файла
    wcout << L"Содержимое файла: " << fileIn("example.txt") << endl;

    extranceToCinema(); // Функция входа в кино, предлагает самый первый выбор

    return 0;
}