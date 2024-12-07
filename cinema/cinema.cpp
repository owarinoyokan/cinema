#include "Header.h"
#include <iostream>     // Для работы потока ввода и вывода
#include <io.h>         // Для работы с _setmode 
#include <locale>       // Для работы с кодировками
#include <fcntl.h>      // Для режима _O_U16TEXT
#include <fstream>      // Для работы с файлами
#include <codecvt>      // Для преобразования UTF-16 в wide string
#include <string>       // Для работы с строками
#include <sstream>      // Для работы с строковыми потоками
#include <vector>       // Сами знаете
#include <map>
#include <windows.h>




using namespace std;    // Пространство имен
using namespace Config;    // Пространство имен

TrioDays Days; //глобальная переменная дней

void extranceToCinema(); // Функция входа в кино, предлагает самый первый выбор
void availablePromo(); // Функция для просмотра доспупных акций
void movieSelection(); // Функция выводяшая список фильмов с краткой информацией
void detailedInform(); // Функция выводящая детали фильма
//void choosingPlace(); // меню выбора места
wstring fileIn(const string& fname); // Функция для чтения файла с широкими символами
void sessionSelection(int);
int listFilmFromTheDay(int day, int filmNumber);

void extranceToCinema() { // Функция входа в кино, предлагает самый первый выбор
    short int input;
    //wcout << L"\n" << fileIn(" file name ") << endl; // Вывод файла
    wcout << L"Что вы желаете сделать?" << endl;
    wcout << L"Нажмите '1', чтобы выбрать фильм" << endl;
    wcout << L"Нажмите '0', чтобы выйти" << endl;
    wcin >> input;

    ClearScreen(); // Очистка консоли


    switch (input) {
    case 1:
        movieSelection(); // Функция выводяшая список фильмов с краткой информацией
        break;
    case 3:
        // место под ф-ю буфета
        break;
    case 0:
        closeWindow();
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
    ClearScreen();
    if (input == 0)
        movieSelection(); // Возврат назад (к предыдущей функции)
    else {
        // место для функции выводящей подробную информацию про акции
    }
}

void movieSelection() { // Функция выводяшая список фильмов с краткой информацией

    short int input;
    wcout << L"\n" << fileIn("cinema_info.txt") << endl; // Вывод файла
    wcout << L"Нажмите '1', чтобы выбрать сеанс" << endl;
    wcout << L"Нажмите '2', чтобы посмотреть доступные акции" << endl;
    wcout << L"Нажмите '3', чтобы использовать фильтр" << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcin >> input;
    ClearScreen();
    switch (input) {
    case 1:
        //choosingPlace(); // выбор сеанса >> меню выбора места >> после выбора мест использовать функцию оплаты

        sessionSelection(1);
        break;
    case 2:
        availablePromo(); // Функция для просмотра доспупных акций
        break;
        //case 21:
        //    wcout << L"\n" << fileIn("Gone with the session.txt") << endl; // Унесённые сессией        
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
        //case 22:
        //    wcout << L"\n" << fileIn("Back to the compiler.txt") << endl; // Назад к компилятору      
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
        //case 23:
        //    wcout << L"\n" << fileIn("And deadlines are tight.txt") << endl; // А дедлайны здесь жесткие      
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
        //case 24:
        //    wcout << L"\n" << fileIn("Lord of the Lab.txt") << endl; // Властелин лаб: возвращение сеньора       
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
        //case 25:
        //    wcout << L"\n" << fileIn("Titanic.txt") << endl; // Титаник: крах программы        
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
        //case 26:
        //    wcout << L"\n" << fileIn("Debagger 2.txt") << endl; // Дебаггер 2: Судный день компиляции      
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
        //case 27:
        //    wcout << L"\n" << fileIn("Garry Coder.txt") << endl; // Гарри Кодер и C++       
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
        //case 28:
        //    wcout << L"\n" << fileIn("Matrix.txt") << endl; // Матрица данных        
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
        //case 29:
        //    wcout << L"\n" << fileIn("Fifth algorithm.txt") << endl; // Пятый алгоритм      
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
        //case 210:
        //    wcout << L"\n" << fileIn("People in black pixels.txt") << endl; // Люди в Черных пикселях      
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
        //case 211:
        //    wcout << L"\n" << fileIn("Lab Wars.txt") << endl; // Лабные Войны: Эпизод 5        
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
        //case 212:
        //    wcout << L"\n" << fileIn("Shrek.txt") << endl; // Шрек и болото багов        
        //    //detailedInform(); // Функция выводящая детали фильма
        //    break;
    case 3:
        // место для функции фильтра
        break;
    case 0:
        extranceToCinema(); // Возврат назад (к предыдущей функции)
        break;
    }
}

void detailedInform() { // Функция выводящая детали фильма
    short int input;
    wcout << L"\n" << fileIn("film_info.txt") << endl; // Вывод файла
    wcout << L"Детальная информация про фильм ... " << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcin >> input;
    ClearScreen();
    movieSelection(); // Возврат назад (к предыдущей функции)
}


void sessionSelection(int day) { // Выбор сеанса
    //wcout << L"\n" << fileIn("cimema_info.txt") << endl;
    ClearScreen();


    switch (day) { // изменение расписания в зависсимости от дня (сейчас ничего не меняется)
    case 1:
        wcout << L"\n" << fileIn("AllMovDay_1.txt") << endl;
        break;
    case 2:
        wcout << L"\n" << fileIn("AllMovDay_2.txt") << endl;
        break;
    case 3:
        wcout << L"\n" << fileIn("AllMovDay_3.txt") << endl;
        break;
    }

    wcout << L"Выберите фильм который хотите посмотреть" << endl;
    wcout << L"Введите 111 чтобы посмотреть расписание на 1 день" << endl;
    wcout << L"Введите 222 чтобы посмотреть расписание на 2 день" << endl;
    wcout << L"Введите 333 чтобы посмотреть расписание на 3 день" << endl;
    //wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcout << L"Введите номер сеанса, на который хотите пойти" << endl << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    //wcin >> input;

    int input;
    while (true) {
        if (correctInput(input) && input >= 0 && input <= 333)
            break;
        wcout << L"Ошибка ввода попробуйте ещё раз\n";
    }
    ClearScreen();
    if (input == 0) {
        movieSelection();
    }
    if (input == 111) {
        ClearScreen();
        day = 1;
        sessionSelection(day);

    }
    else if (input == 222) {
        ClearScreen();
        day = 2;
        sessionSelection(day);

    }
    else if (input == 333) {
        ClearScreen();
        day = 3;
        sessionSelection(day);

    }
    else {
        int numbers_1_day = Days.trio_days[day - 1].Cinema_room_1.size();
        int numbers_2_day = Days.trio_days[day - 1].Cinema_room_2.size() + Days.trio_days[day - 1].Cinema_room_1.size();
        int numbers_3_day = Days.trio_days[day - 1].Cinema_room_3.size() + Days.trio_days[day - 1].Cinema_room_2.size() + Days.trio_days[day - 1].Cinema_room_1.size();
        if (input <= numbers_1_day) {
            choosingPlace(Days.trio_days[day - 1].Cinema_room_1[input - 1], day);
        }
        else if (input > numbers_1_day && input <= numbers_2_day)
            choosingPlace(Days.trio_days[day - 1].Cinema_room_2[input - numbers_1_day - 1], day);

        else if (input > numbers_2_day && input <= numbers_3_day)
            choosingPlace(Days.trio_days[day - 1].Cinema_room_3[input - numbers_2_day - 1], day);
    }



    /* input = listFilmFromTheDay(day, input); // возвращаяем номер фильма зная день и его номер в расписании дня


     ClearScreen();


     //switch (input) { // выводим все сеансы на данный фильм
     //case 1001:
     //    wcout << L"\n" << fileIn("Gone with the session.txt") << endl; // Унесённые сессией
     //    break;
     //case 1002:
     //    wcout << L"\n" << fileIn("Shrek.txt") << endl; // Шрек и болото багов
     //    break;
     //case 1003:
     //    wcout << L"\n" << fileIn("Back to the compiler.txt") << endl; // Назад к компилятору
     //    break;
     //case 1004:
     //    wcout << L"\n" << fileIn("And deadlines are tight.txt") << endl; // А дедлайны здесь жесткие
     //    break;
     //case 1005:
     //    wcout << L"\n" << fileIn("Lord of the Lab.txt") << endl; // Властелин лаб: возвращение сеньора
     //    break;
     //case 1006:
     //    wcout << L"\n" << fileIn("Titanic.txt") << endl; // Титаник: крах программы
     //    break;
     //case 1007:
     //    wcout << L"\n" << fileIn("Debagger 2.txt") << endl; // Дебаггер 2: Судный день компиляции
     //    break;
     //case 1008:
     //    wcout << L"\n" << fileIn("Garry Coder.txt") << endl; // Гарри Кодер и C++
     //    break;
     //case 1009:
     //    wcout << L"\n" << fileIn("Matrix.txt") << endl; // Матрица данных
     //    break;
     //case 1010:
     //    wcout << L"\n" << fileIn("Fifth algorithm.txt") << endl; // Пятый алгоритм
     //    break;
     //case 1011:
     //    wcout << L"\n" << fileIn("People in black pixels.txt") << endl; // Люди в Черных пикселях
     //    break;
     //case 1012:
     //    wcout << L"\n" << fileIn("Lab Wars.txt") << endl; // Лабные Войны: Эпизод 5
     //    break;
     //}


     // Создаем map для соответствия между номерами сеансов и именами файлов
     map<int, string> sessionFiles = {
         {1001, "Gone with the session.txt"},
         {1002, "Shrek.txt"},
         {1003, "Back to the compiler.txt"},
         {1004, "And deadlines are tight.txt"},
         {1005, "Lord of the Lab.txt"},
         {1006, "Titanic.txt"},
         {1007, "Debagger 2.txt"},
         {1008, "Garry Coder.txt"},
         {1009, "Matrix.txt"},
         {1010, "Fifth algorithm.txt"},
         {1011, "People in black pixels.txt"},
         {1012, "Lab Wars.txt"}
     };

     // Проверяем, есть ли input в map
     if (sessionFiles.find(input) != sessionFiles.end()) {
         wcout << L"\n" << fileIn(sessionFiles[input]) << endl; // Выводим содержимое файла
     }
     else {
         wcout << L"Сеанс не найден." << endl; // Обработка случая, если input не найден
     }*/



}

int listFilmFromTheDay(int day, int filmNumber) { // выводит номер фильма от его номера в таблице и от дня
    switch (day) {
    case 1:
        switch (filmNumber) {
        case 1:
            return (1002); // Шрек и болото багов 
            break;
        case 2:
            return (1007); // Дебаггер 2: Судный день компиляции
            break;
        case 3:
            return (1005); // Властелин лаб: возвращение сеньора
            break;
        case 4:
            return (1008); // Гарри Кодер и C++ 
            break;
        case 5:
            return (1009); // Матрица данных
            break;
        case 6:
            return (1001); // Унесённые сессией
            break;
        case 7:
            return (1006); // Титаник: крах программы
            break;
        case 8:
            return (1005); // Властелин лаб: возвращение сеньора
            break;
        case 9:
            return (1010); // Пятый алгоритм
            break;
        case 10:
            return (1011); // Люди в Черных пикселях
            break;
        case 11:
            return (1009); // Матрица данных
            break;
        case 12:
            return (1004); // А дедлайны здесь жесткие
            break;
        }
        break;

    case 2:
        switch (filmNumber) {
        case 1:
            return (1010); // Пятый алгоритм
            break;
        case 2:
            return (1006); // Титаник: крах программы
            break;
        case 3:
            return (1004); // А дедлайны здесь жесткие
            break;
        case 4:
            return (1005); // Властелин лаб: возвращение сеньора
            break;
        case 5:
            return (1002); // Шрек и болото багов 
            break;
        case 6:
            return (1003); // Назад к компилятору 
            break;
        case 7:
            return (1007); // Дебаггер 2: Судный день компиляции
            break;
        case 8:
            return (1009); // Матрица данных
            break;
        case 9:
            return (1001); // Унесённые сессией
            break;
        case 10:
            return (1008); // Гарри Кодер и C++
            break;
        case 11:
            return (1012); // Лабные Войны: Эпизод 5 
            break;
        }
        break;

    case 3:
        switch (filmNumber) {
        case 1:
            return (1011); // Люди в Черных пикселях
            break;
        case 2:
            return (1003); // Назад к компилятору 
            break;
        case 3:
            return (1004); // А дедлайны здесь жесткие
            break;
        case 4:
            return (1012); // Лабные Войны: Эпизод 5 
            break;
        case 5:
            return (1007); // Дебаггер 2: Судный день компиляции
            break;
        case 6:
            return (1002); // Шрек и болото багов
            break;
        case 7:
            return (1006); // Титаник: крах программы
            break;
        case 8:
            return (1008); // Гарри Кодер и C++
            break;
        case 9:
            return (1011); // Люди в Черных пикселях
            break;
        case 10:
            return (1008); // Гарри Кодер и C++
            break;
        case 11:
            return (1005); // Властелин лаб: возвращение сеньора
            break;
        }
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




void generationTrioDays(TrioDays& trio)
{
    Day day_one, day_two, day_three;
    GenerationDay(day_one, fileIn("sessions_day_one.txt"), rowCount, placeCount); // генерация всех сеансов первого дня
    GenerationDay(day_two, fileIn("sessions_day_two.txt"), rowCount, placeCount); // генерация всех сеансов второго дня
    GenerationDay(day_three, fileIn("sessions_day_three.txt"), rowCount, placeCount); // генерация всех сеансов третьего дня
    trio.trio_days.push_back(day_one);
    trio.trio_days.push_back(day_two);
    trio.trio_days.push_back(day_three);
}



int main() {    // commit
    // Настройка широких символов для потока вывода
    setMode16();
    fullScreen();
    for (int i = 0; i < 2; i++) {
        PressCtrlMinus();
    }

    wcout << fileIn("6104.txt") << endl;
    
    system("pause");

    ClearScreen();      // Очистка консоли

    srand(time(0));

    generationTrioDays(Days); // генерация всех 3х дней


    ///*demoVis_All_sessions(day_one, rowCount, placeCount); ///вывод всех сеансов ввиде зала
    //waitForInput();*/
    /*
    choosingPlace(Days.day_one.Cinema_room_1[0]);*/
    //waitForInput();


    wcout << L"Проект кинотеатра.🎬" << endl;
    wcout << L"Тестовый запуск" << endl;

    extranceToCinema(); // Функция входа в кино, предлагает самый первый выбор



    //waitForInput();
    //closeWindow();



    // Запись в файл
    //fileOut("example.txt");

    // Чтение файла
    //wcout << L"Содержимое файла: " << fileIn("example.txt") << endl;

    return 0;
}