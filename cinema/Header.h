#ifndef HEADER_H
#define HEADER_H

#include <windows.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <thread>
#include <codecvt>      // Äëÿ ïðåîáðàçîâàíèÿ UTF-16 â wide string
#include <io.h>         // Äëÿ ðàáîòû ñ _setmode
#include <locale>       // Äëÿ ðàáîòû ñ êîäèðîâêàìè
#include <fcntl.h>      // Äëÿ ðåæèìà _O_U16TEXT
#include <map>


using namespace std;

// Конфигурация программы
namespace Config {
	int y = 0;
	constexpr const int BOX_WIDTH = 6;              // Ширина бокса
	constexpr const int BOX_HEIGHT = 3;             // Высота бокса
	constexpr const int CHANSE_NOT_FREE_PLACES = 8; // Вероятность занятого места
	constexpr const int row_distance = 3; // дистанция для генерации дорогих мест для ряда
	constexpr const int column_distance = 5; // дистанция для генерации дорогих мест для мест 
	constexpr const int expensive_place = 450; // стоимость дорогого места
	constexpr const int cheap_place = 350; // стоимость дешёвого места
	const int rowCount = 8; // количества рядов
	const int placeCount = 18;// 16 и 2 для отрисовки номера ряда с двух сторон


}
using namespace Config;

void sessionSelection(int day);

void setCursorPosition(int x, int y) {
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Структура для представления одного места
struct Seat {
	wstring status; // "x" — занято, "0" — номер ряда, число — номер места
	wstring color; // цвет места 
	int cost;
};

// Структура для ряда
struct Row {
	vector<Seat> seats;
};

// Структура зала
struct Session {
	vector<Row> rows;
	wstring film_name;
	wstring time_film;
	wstring genre;
	wstring duration;
};

//структура Сеанса
struct Day {
	vector<Session> Cinema_room_1;
	vector<Session> Cinema_room_2;
	vector<Session> Cinema_room_3;
};
struct TrioDays {
	vector <Day> trio_days;
};



void SetColor(int text, int background) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background << 4) | text);
}

void setMode16() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
}

// Проверка и преобразование строк
// Проверка, является ли строка числом
bool isNumber(const wstring& str) {
	for (wchar_t c : str) {
		if (!iswdigit(c)) {
			return false;
		}
	}
	return true;
}
// Преобразование строки в число
int stringToInt(const wstring& str) {
	return stoi(str);
}


// Функции отрисовки
// Функция отрисовки занятого места
void drawGrayOccupiedBox(int& x, int y) {
	SetColor(8, 8);
	setCursorPosition(x, y + 1);
	wcout << L"|    |";
	setCursorPosition(x, y + 2);
	wcout << L"| " << L" " << L" " << L" |";
	setCursorPosition(x, y + 3);
	wcout << L"|____|";
	SetColor(15, 0);
	x += BOX_WIDTH + 1;
}

void drawVioletOccupiedBox(int& x, int y) {
	SetColor(13, 13);
	setCursorPosition(x, y + 1);
	wcout << L"|    |";
	setCursorPosition(x, y + 2);
	wcout << L"| " << L" " << L" " << L" |";
	setCursorPosition(x, y + 3);
	wcout << L"|____|";
	SetColor(15, 0);
	x += BOX_WIDTH + 1;
}

// Функция отрисовки номера ряда
void drawRowNumberBox(int& x, int y, int rowNumber) {
	x += 1;
	setCursorPosition(x, y + 2);
	wcout << L"Row " << rowNumber;
	x += BOX_WIDTH + 1;
}



// Функция отрисовки дешёвого свободного места
void drawWhiteAvailableBox(int& x, int y, const wstring& number) {
	SetColor(15, 0);

	setCursorPosition(x, y + 1);
	SetColor(0, 15);
	wcout << L"      ";
	setCursorPosition(x, y + 2);
	wcout << L"  " << (stringToInt(number) < 10 ? L" " : L"") << number << L"  ";
	setCursorPosition(x, y + 3);
	wcout << L"      ";
	SetColor(15, 0);
	x += BOX_WIDTH + 1;
}

// Функция отрисовки дорогого свободного места
void drawYellowAvailableBox(int& x, int y, const wstring& number) {
	setCursorPosition(x, y + 1);
	SetColor(0, 14);
	wcout << L"      ";
	setCursorPosition(x, y + 2);
	wcout << L"  " << (stringToInt(number) < 10 ? L" " : L"") << number << L"  ";
	setCursorPosition(x, y + 3);
	wcout << L"      ";
	SetColor(15, 0);
	x += BOX_WIDTH + 1;
}

// Рисуем рамку для конкретного места
void drawBox(int& x, int y, const Seat& seat, int rowNumber) {
	if (isNumber(seat.status) && seat.status != L"0" && seat.color == L"white") {
		drawWhiteAvailableBox(x, y, seat.status);
	}
	else if (seat.status == L"x") {
		if (seat.color == L"red") {
			drawGrayOccupiedBox(x, y);
		}
		else if (seat.color == L"violet") {
			drawVioletOccupiedBox(x, y);
		}
	}
	else if (seat.status == L"0") {
		drawRowNumberBox(x, y, rowNumber);
	}
	else if (isNumber(seat.status) && seat.status != L"0" && seat.color == L"yellow") {
		drawYellowAvailableBox(x, y, seat.status);
	}
}

//// Отрисовка ряда
void drawRow(int y, const Row& row, int rowNumber) {
	int x = 2;
	for (const auto& seat : row.seats) {
		drawBox(x, y, seat, rowNumber);
	}
}

/// <summary>
/// Эта функция отрисовывает весь зал
/// </summary>
/// <param name="session">сеанс</param>
/// <param name="rowCount"> количество рядов</param>
/// <param name="placeCount">количество мест</param>
void DrawSession(Session& session, int rowCount, int placeCount) {
	wcout << setw(65) << session.time_film << endl;
	++y;
	wcout << setw(67) << session.film_name << endl;
	++y;
	setCursorPosition(1, y);
	for (int line = 1; line < 129; ++line) { wcout << L"_"; }
	++y;
	wcout << L"\n|";
	for (int i = session.rows.size() - 1; i >= 0; --i) {
		setCursorPosition(1, y - 1);
		for (int ozer_line = 0; ozer_line < 4; ++ozer_line) { setCursorPosition(0, ++y); wcout << L"|"; }
		y -= 4;
		//wcout << L"|\n|\n|\n|\n|\n";
		if (i > rowCount - 1) {

		}
		else {
			drawRow(y, session.rows[i], i + 1);
		}
		--y;
		for (int ozer_line = 0; ozer_line < 5; ++ozer_line) { setCursorPosition(129, ++y); wcout << L"|"; }
		y -= 5;
		y += BOX_HEIGHT + 2;
	}
	setCursorPosition(1, y);
	for (int line = 0; line < 128; ++line) { wcout << L"_"; }
	++y;
	setCursorPosition(0, y);

}

// Генерация зала
void GenerationRoom(Session& session, const int rowCount, const int placeCount, wstring name, wstring time_f, wstring genre, wstring duration) {
	session.rows.resize(rowCount);
	session.film_name = name;
	session.time_film = time_f;
	session.genre = genre;
	session.duration = duration;
	for (int i = 0; i < rowCount; ++i) {
		session.rows[i].seats.resize(placeCount);
		for (int j = 0; j < placeCount; ++j) {
			if (j == 0 || j == placeCount - 1) {
				session.rows[i].seats[j].status = L"0";
			}
			else {
				int rand_not_free = rand() % CHANSE_NOT_FREE_PLACES; // шанс что место уже занято 
				if (rand_not_free == 0) {
					session.rows[i].seats[j].status = L"x"; // сохранение состояния текущего места
					session.rows[i].seats[j].color = L"red"; // установка цвета текущего места
				}
				else {
					session.rows[i].seats[j].status = to_wstring(j); // сохранение состояния текущего места

					if ((i <= (rowCount - row_distance) && i >= (row_distance - 1)) && (j >= column_distance && j <= (placeCount - column_distance - 1))) {
						session.rows[i].seats[j].color = L"yellow"; // установка цвета текущего места
						session.rows[i].seats[j].cost = expensive_place; //установка цены текущего места
					}
					else {
						session.rows[i].seats[j].color = L"white"; // установка цвета текущего места
						session.rows[i].seats[j].cost = cheap_place; //установка цены текущего места
					}
				}

			}
		}
	}
}

void fullScreen() {
	COORD coord;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);
	keybd_event(VK_MENU, 0, 0, 0); // Нажатие Alt
	keybd_event(VK_RETURN, 0, 0, 0); // Нажатие Enter
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); // Отпуск Enter
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); // Отпуск Alt
	this_thread::sleep_for(chrono::milliseconds(100));
}

wstring replaceDash(wstring str) {
	replace(str.begin(), str.end(), L'—', L'-');
	return str;
}

// Удаление символа \r из строки
void removeCarriageReturn(std::wstring& line) {
	line.erase(std::remove(line.begin(), line.end(), L'\r'), line.end());
}


// Генерация дня с чтением из файла
void GenerationDay(Day& day, wstring filename, int rowCount, int placeCount) {
	wstringstream stream(filename);
	wstring line;
	vector<Session>* currentSessionGroup = nullptr;

	while (getline(stream, line)) {
		removeCarriageReturn(line);
		line = replaceDash(line);
		if (line.empty()) {
			continue;
		}

		if (line == L"Cinema room 1") {
			currentSessionGroup = &day.Cinema_room_1;
		}
		else if (line == L"Cinema room 2") {
			currentSessionGroup = &day.Cinema_room_2;
		}
		else if (line == L"Cinema room 3") {
			currentSessionGroup = &day.Cinema_room_3;
		}
		else if (currentSessionGroup && !line.empty() && iswdigit(line[0])) {
			int sessionCount = 0;
			try {
				sessionCount = stoi(line);
				currentSessionGroup->resize(sessionCount);
			}
			catch (const exception&) {
				wcerr << L"Ошибка: Некорректное количество сеансов." << endl;
				return;
			}

			for (int i = 0; i < sessionCount; ++i) {
				wstring timeRange, filmName, genre, duration;

				if (!getline(stream, timeRange) || timeRange.empty()) {
					wcerr << L"Ошибка: Некорректное или отсутствует время фильма." << endl;
					return;
				}

				if (!getline(stream, filmName) || filmName.empty()) {
					wcerr << L"Ошибка: Некорректное или отсутствует название фильма." << endl;
					return;
				}

				if (!getline(stream, genre) || genre.empty()) {
					wcerr << L"Ошибка: Некорректный или отсутствует жанр фильма." << endl;
					return;
				}

				if (!getline(stream, duration) || duration.empty()) {
					wcerr << L"Ошибка: Некорректная или отсутствует продолжительность фильма." << endl;
					return;
				}

				(*currentSessionGroup)[i].film_name = filmName;
				(*currentSessionGroup)[i].time_film = timeRange;
				(*currentSessionGroup)[i].genre = genre;
				(*currentSessionGroup)[i].duration = duration;

				GenerationRoom((*currentSessionGroup)[i], rowCount, placeCount, filmName, timeRange, genre, duration);
			}
		}
		else {
			wcerr << L"Ошибка: Неизвестная строка в файле." << endl;
			return;
		}
	}
}




//Очистка экрана :
void ClearScreen() {
	y = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count, cellCount;
	COORD homeCoords = { 0, 0 };

	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		cellCount = csbi.dwSize.X * csbi.dwSize.Y; // Исправлено
		FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
		SetConsoleCursorPosition(hConsole, homeCoords);
	}
}


/// <summary>
/// Очистка экрана с определённой позиции и доконца
/// </summary>
/// <param name="startX">Позиция Х</param>
/// <param name="startY">Позиция Y</param>
void ClearScreenFromPosition(int startX, int startY) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count, cellCount;
	COORD startCoord = { (SHORT)startX, (SHORT)startY };

	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		// Вычисляем количество ячеек, которые нужно очистить
		cellCount = (csbi.dwSize.X - startX) * (csbi.dwSize.Y - startY);

		// Заполняем пространство пробелами
		FillConsoleOutputCharacter(hConsole, ' ', cellCount, startCoord, &count);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, startCoord, &count);

		// Устанавливаем курсор в начальную позицию
		setCursorPosition(startX, startY);
	}
}

void closeWindow() {
	// Нажимаем Alt
	keybd_event(VK_MENU, 0x38, 0, 0);
	// Нажимаем F4
	keybd_event(VK_F4, 0x3E, 0, 0);
	// Отпускаем F4
	keybd_event(VK_F4, 0x3E, KEYEVENTF_KEYUP, 0);
	// Отпускаем Alt
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

// функиция смены масштаба
void PressCtrlMinus() {
	// Эмуляция нажатия клавиши Ctrl
	keybd_event(VK_CONTROL, 0, 0, 0);
	// Эмуляция нажатия клавиши "-"
	keybd_event(VK_OEM_MINUS, 0, 0, 0);
	// Эмуляция отпускания клавиши "-"
	keybd_event(VK_OEM_MINUS, 0, KEYEVENTF_KEYUP, 0);
	// Эмуляция отпускания клавиши Ctrl
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}

void waitForInput() {
	system("pause");
	cin.clear();
}

bool correctInput(int& number) {
	wstring input;
	getline(wcin, input); // Читаем строку из wcin
	if (input.empty()) {
		return false; // Проверка на пустой ввод
	}
	try {
		size_t pos;
		number = stoi(input, &pos); // Пробуем преобразовать строку в число
		if (pos != input.size()) {
			return false; // Если есть лишние символы
		}
	}
	catch (const invalid_argument&) {
		return false; // Если преобразование не удалось
	}
	catch (const out_of_range&) {
		return false; // Если число выходит за пределы
	}
	return true; // Успех
}




bool aoutoChoosingPlace(Session& session, int cnt_places, int& bookedRow, vector<int>& bookedRows, vector<int>& bookedPlaces, double& totalCost) {
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
						totalCost += session.rows[i].seats[k].cost;
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
void printTicketDetails(const vector<int>& bookedRows, const vector<int>& bookedPlaces, int cnt_places, double totalCost, const wstring& filmName, const wstring& filmTime, const wstring& genre, const wstring& duration) {
	wcout << L"\n---------- Билет ----------\n";
	wcout << L"Фильм: " << filmName << L"\n";
	wcout << L"Жанр: " << genre << L"\n";
	wcout << L"Сеанс: " << filmTime << L"\n";
	wcout << L"Продолжительность: " << duration << L"\n\n";

	wcout << L"Забронированные места:\n";
	for (size_t i = 0; i < bookedRows.size(); ++i) {
		wcout << L"Ряд: " << bookedRows[i] + 1
			<< L", Место: " << bookedPlaces[i];
		if (i < bookedRows.size() - 1) {
			wcout << L" | ";
		}
	}

	wcout << L"\nКоличество билетов: " << cnt_places << L"\n";
	wcout << L"Общая стоимость: " << totalCost << L" рублей.\n";
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

void choosingPlace(Session& session, int day) {
	DrawSession(session, session.rows.size(), session.rows[0].seats.size());
	setCursorPosition(0, y);

	int choice;
	int cnt_error_messeg = 0;
	double totalCost = 0;
	// Выбор способа бронирования
	while (true) {

		if (cnt_error_messeg >= 3) {
			ClearScreenFromPosition(0, 42);
			cnt_error_messeg = 0;
			continue;
		}
		wcout << L"Выберите способ бронирования мест:\n";
		wcout << L"1. Автоподбор мест\n";
		wcout << L"2. Ручной выбор мест\n";
		wcout << L"0 Вернуться назад\n";
		wcout << L"Введите ваш выбор: ";

		if (!correctInput(choice)) {
			if (choice != 1 && choice != 2) {
				cnt_error_messeg += 3;
				wcout << L"Некорректный ввод. Введите 1 или 2.\n";
			}
			continue;
		}

		if (choice == 0)
			sessionSelection(day);

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

				if (!aoutoChoosingPlace(session, cnt_places, bookedRow, bookedRows, bookedPlaces, totalCost)) {
					wcout << L"К сожалению, не удалось найти " << cnt_places << L" свободных рядом мест.\n";
					++cnt_error_messeg;
					continue;
				}


				wcout << L"Места успешно забронированы.\n";

				// Вывод всех деталей билета
				printTicketDetails(bookedRows, bookedPlaces, cnt_places, totalCost, session.film_name, session.time_film, session.genre, session.duration);
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
						session.rows[row].seats[place].color = L"gray";
						totalCost += session.rows[row].seats[place].cost;
						bookedRows.push_back(row);
						bookedPlaces.push_back(place);
						break;
					}
				}
				printTicketDetails(bookedRows, bookedPlaces, cnt_places, totalCost, session.film_name, session.time_film, session.genre, session.duration);
				chooseAdditionalItems(totalCost);
				choosePaymentMethod(totalCost);
				break;
			}
			break;// завершение программы.
		}
	}
}

#endif // HEADER_H