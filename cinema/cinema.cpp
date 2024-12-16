#include "Header.h"
#include "game.h"
#include "ClickTracking.h"  // навигация

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
#include <limits>
#include <windows.h>


using namespace std;    // Пространство имен
using namespace Config;    // Пространство имен


TrioDays Days; //глобальная переменная дней

void returnSessions(int day, int input);
void extranceToCinema(); // Функция входа в кино, предлагает самый первый выбор
void availablePromo(); // Функция для просмотра доспупных акций
void movieSelection(); // Функция выводяшая список фильмов с краткой информацией
void detailedInform(); // Функция выводящая детали фильма
void filterSessions( TrioDays& trio_days); // Функция фильтра фильмов по названию или жанру
void displayFilmDescription(const wstring& filmName); // Функция для отображения описания
//void choosingPlace(); // меню выбора места
wstring fileIn(const string& fname); // Функция для чтения файла с широкими символами
void sessionSelection(int);
int listFilmFromTheDay(int day, int filmNumber);
void selectionDay(int day);


void extranceToCinema() { // Функция входа в кино, предлагает самый первый выбор
    short int input;
    ::Days;
    ClearScreen();
    wcout << fileIn("CINEWAVE.txt") << endl;
    wcout << L"Что вы желаете сделать? Для выбора нажмите ENTER" << endl;
    wcout << L"Нажимайте на стелочки" << endl;
    wcout << L"1. выбрать фильм" << endl;
    wcout << L"Нажмите BACKSPACE чтобы вернуться назад" << endl;
    input = tracing(1);
    switch (input) {
    case 1:
        movieSelection();
        break;
    case 0:
        closeWindow();
        break;
    }
}

void availablePromo() { // Функция для просмотра доспупных акций
    ClearScreen();
    short int input;
    short int prevInput;
    wcout << L"\n" << fileIn("Actions.txt") << endl; // Вывод файла
    wcout << L"Список доступных акций ... " << endl;
    wcout << L"1. чтобы испытать удачу в игре" << endl;
    wcout << L"Нажмите BACKSPACE чтобы вернуться назад" << endl;
    input = tracing(1);
    switch (input) {
    case 1:
        TheActionGame();
        break;
    case 0:
        movieSelection();
        break;
    }
}

void displayFilmDescription(const wstring& filmName) {
    map<wstring, int> filmDescriptions = {
        {L"Унесённые сессией", 1001},
        {L"Шрек и болото багов", 1002},
        {L"Назад к компилятору", 1003},
        {L"А дедлайны здесь жесткие", 1004},
        {L"Властелин лаб: Возвращение сеньора", 1005},
        {L"Титаник: крах программы", 1006},
        {L"Дебаггер 2: Судный день компиляции", 1007},
        {L"Гарри Кодер и С++", 1008},
        {L"Матрица данных", 1009},
        {L"Пятый алгоритм", 1010},
        {L"Люди в Черных пикселях", 1011},
        {L"Лабные войны: Эпизод 5 - Питон наносит ответный удар", 1012}
    };

    // Поиск фильма в map
    auto it = filmDescriptions.find(filmName);
    if (it != filmDescriptions.end()) {
        // Передаём день недели и ID фильма
        int day = 1; // По умолчанию используем первый день (или запрашиваем его отдельно)
        ClearScreen();
        returnSessions(day, it->second);
    }
    else {
        wcout << L"Фильм не найден: " << filmName << endl;
    }
}

//void displayFilmDescription(const wstring& filmName) {
//    map<wstring, string> filmDescriptions = {
//        {L"Шрек и болото багов", "Shrek.txt"},
//        {L"Унесённые сессией", "Gone with the session.txt"},
//        {L"Назад к компилятору", "Back to the compiler.txt"},
//        {L"А дедлайны здесь жесткие", "And deadlines are tight.txt"},
//        {L"Властелин лаб: Возвращение сеньора", "Lord of the Lab.txt"},
//        {L"Титаник: крах программы", "Titanic.txt"},
//        {L"Дебаггер 2: Судный день компиляции", "Debagger 2.txt"},
//        {L"Гарри Кодер и С++", "Garry Coder.txt"},
//        {L"Матрица данных", "Matrix.txt"},
//        {L"Пятый алгоритм", "Fifth algorithm.txt"},
//        {L"Люди в Черных пикселях", "People in black pixels.txt"},
//        {L"Лабные войны: Эпизод 5 - Питон наносит ответный удар", "Lab Wars.txt"}
//    };
//
//    // Преобразуем введенное название фильма в нижний регистр
//    locale loc("ru_RU.UTF-8");
//    wstring formattedFilmName = filmName;
//    transform(formattedFilmName.begin(), formattedFilmName.end(), formattedFilmName.begin(),
//        [&loc](wchar_t c) { return tolower(c, loc); });
//    removeCarriageReturn(formattedFilmName); // Убираем лишние символы
//
//    bool found = false;
//
//    for (const auto& pair : filmDescriptions) {
//        // Преобразуем название фильма из map в нижний регистр
//        wstring filmInMap = pair.first;
//        transform(filmInMap.begin(), filmInMap.end(), filmInMap.begin(),
//            [&loc](wchar_t c) { return tolower(c, loc); });
//        removeCarriageReturn(filmInMap);
//
//        if (filmInMap == formattedFilmName) {
//            wcout << L"\nОписание фильма:\n";
//            wcout << fileIn(pair.second) << endl;
//            found = true;
//        }
//    }
//
//    if (!found)
//        wcout << L"Описание для выбранного фильма не найдено.\n";
//
//    // Пауза перед возвратом в меню
//    wcout << L"\nНажмите Enter, чтобы продолжить...";
//    wcin.ignore();
//    wcin.get();
//}

// Вспомогательная функция фильтра
void filterMenu() {
    filterSessions(Days);
    ClearScreen();
    movieSelection();
}

void movieSelection() { // Функция выводяшая список фильмов с краткой информацией
    ::Days;
    ClearScreen();
    short int input;
    wcout << L"\n" << fileIn("cinema_info.txt") << endl; // Вывод файла
    wcout << L"Что вы желаете сделать? Для выбора нажмите ENTER" << endl;
    wcout << L"1. чтобы выбрать сеанс" << endl;
    wcout << L"2. чтобы посмотреть доступные акции" << endl;
    wcout << L"3. чтобы использовать фильтр" << endl;
    wcout << L"Нажмите BACKSPACE чтобы вернуться назад" << endl;

    input = tracing(3);
    switch (input) {
    case 1:
        selectionDay(1);
        break;
    case 2:
        availablePromo();
        break;
    case 3:
        filterMenu();
        break;
    case 0:
        extranceToCinema();
        break;
    }
}

void detailedInform() { // Функция выводящая детали фильма
    short int input;
    wcout << L"\n" << fileIn("film_info.txt") << endl; // Вывод файла
    wcout << L"Детальная информация про фильм ... " << endl;
    wcout << L"Нажмите BACKSPACE чтобы вернуться назад" << endl;
    wcin >> input;
    ClearScreen();
    movieSelection(); // Возврат назад (к предыдущей функции)
}

void selectionDay(int day) {
    ::Days;
    short int prevInput, inp = 0;
    ClearScreen();
    wcout << L"\n" << fileIn("AllMovDay_1.txt") << endl;
    wcout << L"Нажимайте на стрелочки <- ->, чтобы выбрать день. Нажмите ENTER, чтобы зафиксировать день" << endl;
    while (true) {
        prevInput = inp;
        tracingLR(inp);
        switch (inp) {
        case 200:

            sessionSelection(prevInput + 1);
        case 2:
            ClearScreen();
            //wcout << L"День 3" << endl;
            wcout << L"\n" << fileIn("AllMovDay_3.txt") << endl;
            wcout << L"Нажимайте на стрелочки, чтобы выбрать день. Нажмите ENTER, чтобы зафиксировать день" << endl;
            break;
        case 1:
            ClearScreen();
            //wcout << L"День 2" << endl;
            wcout << L"\n" << fileIn("AllMovDay_2.txt") << endl;
            wcout << L"Нажимайте на стрелочки, чтобы выбрать день. Нажмите ENTER, чтобы зафиксировать день" << endl;
            break;
        case 0:
            ClearScreen();
            //wcout << L"День 1" << endl;
            wcout << L"\n" << fileIn("AllMovDay_1.txt") << endl;
            wcout << L"Нажимайте на стрелочки, чтобы выбрать день. Нажмите ENTER, чтобы зафиксировать день" << endl;
            break;
        default:
            ClearScreen();
            wcout << L"\n" << fileIn("AllMovDay_1.txt") << endl;
            wcout << L"Нажимайте на стрелочки, чтобы выбрать день. Нажмите ENTER, чтобы зафиксировать день" << endl;
            inp = 0;
            break;

        }
    }
}

void returnSessions(int day, int input)
{
    ::Days;
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

    std::vector<std::reference_wrapper<Session>> sessions_film; // сеансы выбранного фильма

    switch (input) {
    case 1001:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_2[1]);
        sessions_film.push_back(::Days.trio_days[1].Cinema_room_3[1]);
        break;
    case 1002:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_1[0]);
        sessions_film.push_back(::Days.trio_days[1].Cinema_room_2[0]);
        sessions_film.push_back(::Days.trio_days[2].Cinema_room_2[1]);
        break;
    case 1003:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[1].Cinema_room_2[1]);
        sessions_film.push_back(::Days.trio_days[2].Cinema_room_1[2]);
        break;
    case 1004:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_3[3]);
        sessions_film.push_back(::Days.trio_days[1].Cinema_room_1[2]);
        sessions_film.push_back(::Days.trio_days[2].Cinema_room_1[2]);
        break;
    case 1005:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_1[2]);
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_2[3]);
        sessions_film.push_back(::Days.trio_days[1].Cinema_room_1[3]);
        sessions_film.push_back(::Days.trio_days[2].Cinema_room_3[2]);
        break;
    case 1006:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_2[2]);
        sessions_film.push_back(::Days.trio_days[1].Cinema_room_1[1]);
        sessions_film.push_back(::Days.trio_days[2].Cinema_room_2[2]);
        break;
    case 1007:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_1[1]);
        sessions_film.push_back(::Days.trio_days[1].Cinema_room_2[2]);
        sessions_film.push_back(::Days.trio_days[2].Cinema_room_2[0]);
        break;
    case 1008:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_1[3]);
        sessions_film.push_back(::Days.trio_days[1].Cinema_room_3[2]);
        sessions_film.push_back(::Days.trio_days[2].Cinema_room_2[3]);
        sessions_film.push_back(::Days.trio_days[2].Cinema_room_3[1]);
        break;
    case 1009:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_2[0]);
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_3[2]);
        sessions_film.push_back(::Days.trio_days[1].Cinema_room_3[0]);
        break;
    case 1010:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_3[0]);
        sessions_film.push_back(::Days.trio_days[1].Cinema_room_1[0]);
        break;
    case 1011:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[0].Cinema_room_3[1]);
        sessions_film.push_back(::Days.trio_days[2].Cinema_room_1[0]);
        sessions_film.push_back(::Days.trio_days[2].Cinema_room_3[0]);
        break;
    case 1012:
        sessions_film.clear();
        sessions_film.push_back(::Days.trio_days[1].Cinema_room_3[3]);
        sessions_film.push_back(::Days.trio_days[2].Cinema_room_1[3]);
        break;
    }



    // Проверяем, есть ли input в map
    if (sessionFiles.find(input) != sessionFiles.end()) {
        wcout << L"\n" << fileIn(sessionFiles[input]) << endl; // Выводим содержимое файла
        setCursorPosition(0, 33);
        wcout << L"Выберите сеанс введите число от 1 до " << sessions_film.size() << " \n";
        //wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
        wcout << L"Нажмите BACKSPACE, чтобы вернуться назад" << endl;
        short int input;
        input = tracing(sessions_film.size());
        switch (input) {
        case 0:
            ClearScreen();
            movieSelection();
            break;
        default:
            ClearScreen();
            choosingPlace(sessions_film[input - 1], day);
            break;
        }

        /*int input_2;
        while (!correctInput(input_2)) {
            wcout << L"Некорректный ввод. Попробуйте снова.\n";
            ClearScreenFromPosition(0, 35);
        }*/
        /*if (input_2 == 0) {
            ClearScreen();
            selectionDay(day);
        }*/
        /*if (input_2 > 0 && input_2 <= sessions_film.size()) {
            ClearScreen();
            choosingPlace(sessions_film[input_2 - 1], day);
        }*/
    }

    else {
        wcout << L"Сеанс не найден." << endl; // Обработка случая, если input не найден
    }
}

void sessionSelection(int day) { // Выбор сеанса
    ::Days;
    wcout << L"Введите номер сеанса, на который хотите пойти" << endl << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    int cnt_error_messege = 0;
    
    int input;
    while (true) {
        if (cnt_error_messege > 0) {
            cnt_error_messege = 0;
            ClearScreenFromPosition(0, 43);
        }
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        if (correctInput(input) && ((day == 1 && input <= 12) || (day != 1 && input <= 11) || input == 0 || input == 111 || input == 222 || input == 333))
            break;
        wcout << L"Ошибка ввода попробуйте ещё раз\n";
        ++cnt_error_messege;
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
    input = listFilmFromTheDay(day, input); // возвращаяем номер фильма зная день и его номер в расписании дня
    returnSessions(day, input);
   
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

void ConsoleMode() {
    ResizeConsoleWindow(20, 60);
    // открытие консоли в полном экране
    fullScreen();

    // Настройка широких символов для потока вывода
    setMode16();

    // Название для консоли
    SetConsoleTitle(L"Кинотеатр \"6104\"");

    // Масштаб -1
    PressCtrlMinus(1);
    
}

int main() {
    // Установка параметров консоли
    ConsoleMode();
    srand(time(0));
    generationTrioDays(Days); // генерация всех 3х дней

    extranceToCinema(); // Функция входа в кино, предлагает самый первый выбор

    return 0;
}