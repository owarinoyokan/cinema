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
#include <windows.h>


using namespace std;    // Пространство имен
using namespace Config;    // Пространство имен


void extranceToCinema(); // Функция входа в кино, предлагает самый первый выбор
void availablePromo(); // Функция для просмотра доспупных акций
void movieSelection(); // Функция выводяшая список фильмов с краткой информацией
void detailedInform(); // Функция выводящая детали фильма
void choosingPlace(); // меню выбора места
wstring fileIn(const string& fname); // Функция для чтения файла с широкими символами
void sessionSelection(int);
int listFilmFromTheDay(int day, int filmNumber);



void extranceToCinema() { // Функция входа в кино, предлагает самый первый выбор
    short int input;
    //wcout << L"\n" << fileIn(" file name ") << endl; // Вывод файла
    wcout << L"Что вы желаете сделать?" << endl;
    wcout << L"Нажмите '1', чтобы выбрать фильм" << endl;
    wcout << L"Нажмите '2', чтобы посмотреть доступные акции" << endl;
    wcout << L"Нажмите '0', чтобы выйти" << endl;
    wcin >> input;
    ClearScreen(); // Очистка консоли
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
        extranceToCinema(); // Возврат назад (к предыдущей функции)
    else {
        // место для функции выводящей подробную информацию про акции
    }
}

void movieSelection() { // Функция выводяшая список фильмов с краткой информацией
    short int input;
    wcout << L"\n" << fileIn("cinema_info.txt") << endl; // Вывод файла
    wcout << L"Нажмите '1', чтобы выбрать сеанс" << endl;
    wcout << L"Нажмите '2', чтобы посмотреть детали" << endl; // Возможно это не стоит показывать отдельно 
                                                                // а показывать принудительно после выбора сеанса

    wcout << L"Нажмите '3', чтобы использовать фильтр" << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcin >> input;
    ClearScreen();
    switch (input) {
    case 1:
        //choosingPlace(); // выбор сеанса >> меню выбора места >> после выбора мест использовать функцию оплаты
        sessionSelection(1);
        break;
    case 21:
        wcout << L"\n" << fileIn("Gone with the session.txt") << endl; // Унесённые сессией        
        //detailedInform(); // Функция выводящая детали фильма
        break;
    case 22:
        wcout << L"\n" << fileIn("Back to the compiler.txt") << endl; // Назад к компилятору      
        //detailedInform(); // Функция выводящая детали фильма
        break;
    case 23:
        wcout << L"\n" << fileIn("And deadlines are tight.txt") << endl; // А дедлайны здесь жесткие      
        //detailedInform(); // Функция выводящая детали фильма
        break;
    case 24:
        wcout << L"\n" << fileIn("Lord of the Lab.txt") << endl; // Властелин лаб: возвращение сеньора       
        //detailedInform(); // Функция выводящая детали фильма
        break;
    case 25:
        wcout << L"\n" << fileIn("Titanic.txt") << endl; // Титаник: крах программы        
        //detailedInform(); // Функция выводящая детали фильма
        break;
    case 26:
        wcout << L"\n" << fileIn("Debagger 2.txt") << endl; // Дебаггер 2: Судный день компиляции      
        //detailedInform(); // Функция выводящая детали фильма
        break;
    case 27:
        wcout << L"\n" << fileIn("Garry Coder.txt") << endl; // Гарри Кодер и C++       
        //detailedInform(); // Функция выводящая детали фильма
        break;
    case 28:
        wcout << L"\n" << fileIn("Matrix.txt") << endl; // Матрица данных        
        //detailedInform(); // Функция выводящая детали фильма
        break;
    case 29:
        wcout << L"\n" << fileIn("Fifth algorithm.txt") << endl; // Пятый алгоритм      
        //detailedInform(); // Функция выводящая детали фильма
        break;
    case 210:
        wcout << L"\n" << fileIn("People in black pixels.txt") << endl; // Люди в Черных пикселях      
        //detailedInform(); // Функция выводящая детали фильма
        break;
    case 211:
        wcout << L"\n" << fileIn("Lab Wars.txt") << endl; // Лабные Войны: Эпизод 5        
        //detailedInform(); // Функция выводящая детали фильма
        break;
    case 212:
        wcout << L"\n" << fileIn("Shrek.txt") << endl; // Шрек и болото багов        
        //detailedInform(); // Функция выводящая детали фильма
        break;
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


void choosingPlace() { // меню выбора места << после выбора мест использовать функцию оплаты
    short int input;
    wcout << L"\n" << fileIn("places.txt") << endl; // Вывод файла
    wcout << L"Выберите место" << endl;
    wcout << L"Нажмите '1', чтобы выбрать одно место" << endl;
    wcout << L"Нажмите '2', чтобы выбрать сразу несколько мест" << endl;
    wcout << L"Нажмите '3', для автоматического подбора места" << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcin >> input;
    ClearScreen();
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

void sessionSelection(int day) { // Выбор сеанса
    //wcout << L"\n" << fileIn("cimema_info.txt") << endl; 
    short int input;

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
    wcout << L"Введите 111 чтобы посмотреть расписание на следующий день" << endl;
    wcout << L"Введите 222 чтобы посмотреть расписание на следующий день" << endl;
    //wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcin >> input;
    if (input == 111) {
        ClearScreen();
        sessionSelection(day + 1);
    }
    else if (input == 222) {
        ClearScreen();
        sessionSelection(day - 1);
    }
    input = listFilmFromTheDay(day, input); // возвращаяем номер фильма зная день и его номер в расписании дня


    ClearScreen();


    switch (input) { // выводим все сеансы на данный фильм
    case 1001:
        wcout << L"\n" << fileIn("Gone with the session.txt") << endl; // Унесённые сессией 
        break;
    case 1002:
        wcout << L"\n" << fileIn("Back to the compiler.txt") << endl; // Назад к компилятору 
        break;
    case 1003:
        wcout << L"\n" << fileIn("And deadlines are tight.txt") << endl; // А дедлайны здесь жесткие
        break;
    case 1004:
        wcout << L"\n" << fileIn("Lord of the Lab.txt") << endl; // Властелин лаб: возвращение сеньора
        break;
    case 1005:
        wcout << L"\n" << fileIn("Titanic.txt") << endl; // Титаник: крах программы
        break;
    case 1006:
        wcout << L"\n" << fileIn("Debagger 2.txt") << endl; // Дебаггер 2: Судный день компиляции
        break;
    case 1007:
        wcout << L"\n" << fileIn("Garry Coder.txt") << endl; // Гарри Кодер и C++ 
        break;
    case 1008:
        wcout << L"\n" << fileIn("Matrix.txt") << endl; // Матрица данных 
        break;
    case 1009:
        wcout << L"\n" << fileIn("Fifth algorithm.txt") << endl; // Пятый алгоритм
        break;
    case 1010:
        wcout << L"\n" << fileIn("People in black pixels.txt") << endl; // Люди в Черных пикселях 
        break;
    case 1011:
        wcout << L"\n" << fileIn("Lab Wars.txt") << endl; // Лабные Войны: Эпизод 5 
        break;
    case 1012:
        wcout << L"\n" << fileIn("Shrek.txt") << endl; // Шрек и болото багов 
        break;
    }



    wcout << L"Введите номер сеанса, на который хотите пойти" << endl << endl;
    wcout << L"Нажмите '0', чтобы вернуться назад" << endl;
    wcin >> input;
    ClearScreen();
    if (input == 0) {
        movieSelection();
    }
    else {

        // переносит в функцию с залом для выбора места в зависсимости от выбранного сеанса
    }

}

int listFilmFromTheDay(int day, int filmNumber) { // выводит номер фильма от его номера в таблице и от дня
    switch (day) {
    case 1:
        switch (filmNumber) {
        case 1:
            return (1012); // Шрек и болото багов 
            break;
        case 2:
            return (1006); // Дебаггер 2: Судный день компиляции
            break;
        case 3:
            return (1004); // Властелин лаб: возвращение сеньора
            break;
        case 4:
            return (1007); // Гарри Кодер и C++ 
            break;
        case 5:
            return (1008); // Матрица данных
            break;
        case 6:
            return (1001); // Унесённые сессией
            break;
        case 7:
            return (1005); // Титаник: крах программы
            break;
        case 8:
            return (1004); // Властелин лаб: возвращение сеньора
            break;
        case 9:
            return (1009); // Пятый алгоритм
            break;
        case 10:
            return (1010); // Люди в Черных пикселях
            break;
        case 11:
            return (1008); // Матрица данных
            break;
        case 12:
            return (1003); // А дедлайны здесь жесткие
            break;
        }
        break;

    case 2:
        switch (filmNumber) {
        case 1:
            return (1009); // Пятый алгоритм
            break;
        case 2:
            return (1005); // Титаник: крах программы
            break;
        case 3:
            return (1003); // А дедлайны здесь жесткие
            break;
        case 4:
            return (1004); // Властелин лаб: возвращение сеньора
            break;
        case 5:
            return (1012); // Шрек и болото багов 
            break;
        case 6:
            return (1002); // Назад к компилятору 
            break;
        case 7:
            return (1006); // Дебаггер 2: Судный день компиляции
            break;
        case 8:
            return (1008); // Матрица данных
            break;
        case 9:
            return (1001); // Унесённые сессией
            break;
        case 10:
            return (1007); // Гарри Кодер и C++
            break;
        case 11:
            return (1011); // Лабные Войны: Эпизод 5 
            break;
        }
        break;

    case 3:
        switch (filmNumber) {
        case 1:
            return (1010); // Люди в Черных пикселях
            break;
        case 2:
            return (1002); // Назад к компилятору 
            break;
        case 3:
            return (1003); // А дедлайны здесь жесткие
            break;
        case 4:
            return (1011); // Лабные Войны: Эпизод 5 
            break;
        case 5:
            return (1006); // Дебаггер 2: Судный день компиляции
            break;
        case 6:
            return (1012); // Шрек и болото багов
            break;
        case 7:
            return (1005); // Титаник: крах программы
            break;
        case 8:
            return (1007); // Гарри Кодер и C++
            break;
        case 9:
            return (1010); // Люди в Черных пикселях
            break;
        case 10:
            return (1007); // Гарри Кодер и C++
            break;
        case 11:
            return (1004); // Властелин лаб: возвращение сеньора
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

// вывод всех сеансов ввиде зала  //для понимания кода 
void demoVis_All_sessions(Day& day_one, const int rowCount, const int placeCount) {
    fullScreen();
    for (int i = 0; i < day_one.Session_one.size(); ++i) {
        DrawSession(day_one.Session_one[i], rowCount, placeCount);
        waitForInput();
        ClearScreen();

    }

    for (int i = 0; i < day_one.Session_two.size(); ++i) {
        DrawSession(day_one.Session_two[i], rowCount, placeCount);
        waitForInput();
        ClearScreen();
    }

    for (int i = 0; i < day_one.Session_three.size(); ++i) {
        DrawSession(day_one.Session_three[i], rowCount, placeCount);
        waitForInput();
        ClearScreen();
    }
}

bool aoutoChoosingPlace(Session& session, int cnt_places, int& bookedRow, vector<int>& bookedRows, vector<int>& bookedPlaces) {
    for (int i = 0; i < session.rows.size(); ++i) {
        int cnt = 0;  // Счётчик свободных мест подряд
        int start_index = -1; // Индекс начала первого подходящего участка

        for (int j = 1; j < session.rows[i].seats.size() - 1; ++j) { // Проход от 1 до предпоследнего индекса
            if (session.rows[i].seats[j].status != L"x") {
                // Если место свободно, увеличиваем счётчик
                if (cnt == 0) start_index = j; // Устанавливаем начало участка
                ++cnt;

                if (cnt == cnt_places) { // Если нашли подходящий участок
                    // Помечаем места как занятые
                    for (int k = start_index; k < start_index + cnt_places; ++k) {
                        session.rows[i].seats[k].status = L"x";
                        session.rows[i].seats[k].color = L"violet";
                        bookedRows.push_back(i); // Добавляем ряд в список забронированных
                        bookedPlaces.push_back(k); // Добавляем место в список забронированных
                    }
                    ClearScreen();
                    DrawSession(session, session.rows.size(), session.rows[0].seats.size());
                    for (int k = start_index; k < start_index + cnt_places; ++k) {
                        session.rows[i].seats[k].color = L"red";
                    }
                    return true; // Возвращаем успех
                }
            }
            else {
                // Если место занято, сбрасываем счётчик
                cnt = 0;
                start_index = -1;
            }
        }
    }
    return false; // Если ни одного подходящего участка не найдено
}
// Функция для вывода всех деталей билета
void printTicketDetails(const vector<int>& bookedRows, const vector<int>& bookedPlaces, int cnt_places, double totalCost) {
    wcout << L"\n---------- Билет ----------\n";

    wcout << L"Забронированные места:\n";
    for (size_t i = 0; i < bookedRows.size(); ++i) {
        wcout << L"Ряд: " << bookedRows[i] + 1  // Приведение к человеческому виду
            << L", Место: " << bookedPlaces[i]; // Приведение к человеческому виду
        if (i < bookedRows.size() - 1) {
            wcout << L" | "; // Разделяем места
        }
    }

    wcout << L"\nКоличество билетов: " << cnt_places << L"\n";
    wcout << L"Общая стоимость: " << totalCost << L" рублей.\n"; // Здесь можно изменить валюту по необходимости
    wcout << L"--------------------------------\n";
}

void chooseAdditionalItems(double& totalAmount) {
    short int itemChoice;
    bool moreItems = true; // Флаг для продолжения выбора товаров

    while (moreItems) {
        wcout << L"--- Дополнительные товары ---\n";
        wcout << L"1. Кола (150 рублей)\n";
        wcout << L"2. Попкорн (100 рублей)\n";
        wcout << L"3. Чипсы (120 рублей)\n";
        wcout << L"4. Соки (130 рублей)\n";
        wcout << L"5. Нет, спасибо\n";
        wcout << L"Введите номер выбранного товара: ";
        wcin >> itemChoice;

        switch (itemChoice) {
        case 1:
            wcout << L"Вы выбрали Кола.\n";
            totalAmount += 150.0;
            break;
        case 2:
            wcout << L"Вы выбрали Попкорн.\n";
            totalAmount += 100.0;
            break;
        case 3:
            wcout << L"Вы выбрали Чипсы.\n";
            totalAmount += 120.0;
            break;
        case 4:
            wcout << L"Вы выбрали Соки.\n";
            totalAmount += 130.0;
            break;
        case 5:
            wcout << L"Вы выбрали пропустить этот шаг.\n";
            moreItems = false; // Заканчиваем выбор товаров
            break;
        default:
            wcout << L"Некорректный выбор. Пожалуйста, попробуйте снова.\n";
            continue;
        }

        // Запрос о продолжении выбора
        if (itemChoice != 5) { // Пропускаем вопрос, если выбрано "Нет, спасибо"
            wstring addMore;
            wcout << L"Хотите добавить ещё товары? (Y/N): ";
            wcin >> addMore;
            if (addMore != L"Yes" && addMore != L"yes") {
                moreItems = false; // Заканчиваем выбор товаров
            }
        }

        wcout << L"Общая сумма с учетом выбранных товаров: " << totalAmount << L" рублей.\n";
    }
}


// Функция для выбора способа оплаты
void choosePaymentMethod(double totalAmount) {
    int paymentChoice;
    wcout << L"--- Способы оплаты ---\n";
    wcout << L"1. Наличными\n";
    wcout << L"2. Картой\n";
    wcout << L"3. Электронный кошелёк\n";
    wcout << L"Введите номер выбранного способа оплаты: ";
    wcin >> paymentChoice;

    switch (paymentChoice) {
    case 1:
        wcout << L"Вы выбрали оплату наличными. Общая сумма: " << totalAmount << L" рублей.\n";
        break;
    case 2:
        wcout << L"Вы выбрали оплату картой. Общая сумма: " << totalAmount << L" рублей.\n";
        break;
    case 3:
        wcout << L"Вы выбрали оплату электронным кошельком. Общая сумма: " << totalAmount << L" рублей.\n";
        break;
    default:
        wcout << L"Некорректный выбор. Пожалуйста, попробуйте снова.\n";
        choosePaymentMethod(totalAmount);
        return;
    }

    wcout << L"Спасибо за ваш выбор! Транзакция завершена.\n";
}

void choosingPlace(Session& session) {
    DrawSession(session, session.rows.size(), session.rows[0].seats.size());
    setCursorPosition(0, y);

    int choice = 0;
    int cnt_error_messeg = 0;

    // Выбор способа бронирования
    while (true) {
        if (cnt_error_messeg > 3) {
            ClearScreenFromPosition(0, 42);
            cnt_error_messeg = 0;
            continue;
        }
        wcout << L"Выберите способ бронирования мест:\n";
        wcout << L"1. Автоподбор мест\n";
        wcout << L"2. Ручной выбор мест\n";
        wcout << L"Введите ваш выбор: ";

        if (!correctInput(choice) || (choice != 1 && choice != 2)) {
            cnt_error_messeg += 3;
            wcout << L"Некорректный ввод. Введите 1 или 2.\n";
            continue;
        }

        if (choice == 1) { // Автоподбор мест
            int cnt_places, bookedRow;
            vector<int> bookedRows; // Список забронированных рядов
            vector<int> bookedPlaces; // Список забронированных мест
            while (true) {
                if (cnt_error_messeg > 3) {
                    ClearScreenFromPosition(0, 42);
                    cnt_error_messeg = 0;
                    continue;
                }
                wcout << L"Введите количество мест (меньше 16): ";

                if (!correctInput(cnt_places)) {
                    ++cnt_error_messeg;
                    wcout << L"Некорректный ввод. Введите количество мест заново.\n";
                    continue;
                }

                if (cnt_places <= 0 || cnt_places > 16) {
                    ++cnt_error_messeg;
                    wcout << L"Количество мест вне диапазона. Пожалуйста, введите корректное количество.\n";
                    continue;
                }

                if (!aoutoChoosingPlace(session, cnt_places, bookedRow, bookedRows, bookedPlaces)) {
                    wcout << L"К сожалению, не удалось найти " << cnt_places << L" свободных рядом мест.\n";
                    ++cnt_error_messeg;
                    continue;
                }


                wcout << L"Места успешно забронированы.\n";
                double totalCost = cnt_places * 100;

                // Вывод всех деталей билета
                printTicketDetails(bookedRows, bookedPlaces, cnt_places, totalCost);
                chooseAdditionalItems(totalCost);
                choosePaymentMethod(totalCost);
                break;
            }
            break;

        }
        else if (choice == 2) { // Ручной выбор мест
            int cnt_places, row, place;
            vector<int> bookedRows; // Список забронированных рядов
            vector<int> bookedPlaces; // Список забронированных мест
            while (true) {
                if (cnt_error_messeg > 3) {
                    ClearScreenFromPosition(0, 42);
                    cnt_error_messeg = 0;
                    continue;
                }
                wcout << L"Сколько мест вы хотите купить? ";
                if (!correctInput(cnt_places)) {
                    ++cnt_error_messeg;
                    wcout << L"Некорректный ввод. Введите количество мест заново.\n";
                    continue;
                }

                if (cnt_places <= 0 || cnt_places > 16) {
                    ++cnt_error_messeg;
                    wcout << L"Количество мест вне диапазона. Пожалуйста, введите корректное количество.\n";
                    continue;
                }
                double totalCost = cnt_places * 100;
                for (int i = 0; i < cnt_places; ++i) {
                    while (true) {
                        if (cnt_error_messeg > 3) {
                            ClearScreenFromPosition(0, 42);
                            cnt_error_messeg = 0;
                            continue;
                        }
                        wcout << L"Введите номер ряда: ";
                        if (!correctInput(row)) {
                            ++cnt_error_messeg;
                            wcout << L"Некорректный ввод. Введите номер ряда заново.\n";
                            continue;
                        }

                        --row; // Приведение к индексации с 0
                        if (row < 0 || row >= session.rows.size()) {
                            ++cnt_error_messeg;
                            wcout << L"Номер ряда вне диапазона. Введите корректный номер ряда.\n";
                            continue;
                        }

                        wcout << L"Введите номер места: ";
                        if (!correctInput(place)) {
                            ++cnt_error_messeg;
                            wcout << L"Некорректный ввод. Введите номер места заново.\n";
                            continue;
                        }

                        if (place <= 0 || place >= session.rows[row].seats.size() - 1) {
                            ++cnt_error_messeg;
                            wcout << L"Номер места вне диапазона. Введите корректный номер места.\n";
                            continue;
                        }

                        if (session.rows[row].seats[place].status == L"x" || session.rows[row].seats[place].status == L"0") {
                            ++cnt_error_messeg;
                            wcout << L"Место занято, выберите другое.\n";
                            continue;
                        }
                        ClearScreen();
                        // Если место свободно, бронируем его
                        session.rows[row].seats[place].status = L"x";
                        session.rows[row].seats[place].color = L"violet";
                        DrawSession(session, session.rows.size(), session.rows[0].seats.size());
                        wcout << L"Место успешно забронировано.\n";
                        session.rows[row].seats[place].color = L"red";
                        bookedRows.push_back(row);
                        bookedPlaces.push_back(place);
                        break;
                    }
                }
                printTicketDetails(bookedRows, bookedPlaces, cnt_places, totalCost);
                chooseAdditionalItems(totalCost);
                choosePaymentMethod(totalCost);
                break;
            }
            break;// завершение программы.
        }
    }
}










int main() {
    // Настройка широких символов для потока вывода
    setMode16();

    ClearScreen();      // Очистка консоли

    srand(time(0));
    const int rowCount = 8;
    const int placeCount = 18;// 16 и 2 для отрисовки номера ряда с двух сторон

    Day day_one;
    GenerationDay(day_one, fileIn("schedule.txt"), rowCount, placeCount); // генерация всех сеансов первого дня

    /*demoVis_All_sessions(day_one, rowCount, placeCount); ///вывод всех сеансов ввиде зала
    waitForInput();*/
    fullScreen();
    choosingPlace(day_one.Session_one[0]);
    waitForInput();
    ClearScreen();
    wcout << fileIn("check.txt") << endl;

    wcout << L"Проект кинотеатра.🎬" << endl;
    wcout << L"Тестовый запуск" << endl;


    extranceToCinema(); // Функция входа в кино, предлагает самый первый выбор

    ///пример замены сущесвующего места без проверок индекса
    /* int changeRow, changePalace;
    cout << "Введите номер ряда: ";
    cin >> changeRow;
    cout << "\nВведите номер места: ";
    cin >> changePalace;
    changePlaces(hall, changeRow, changePalace);
    DrawHall(hall, rowCount, placeCount);*/

    waitForInput();
    closeWindow();



    // Запись в файл
    //fileOut("example.txt");

    // Чтение файла
    //wcout << L"Содержимое файла: " << fileIn("example.txt") << endl;

    return 0;
}