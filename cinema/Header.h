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
		if (seat.color == L"gray") {
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
/// <summary>
/// Эта функция отрисовывает весь зал
/// </summary>
/// <param name="session">сеанс</param>
/// <param name="rowCount"> количество рядов</param>
/// <param name="placeCount">количество мест</param>
void DrawSession(Session& session, int rowCount, int placeCount) {
	wcout << setw((130 / 2) + (session.time_film.size() / 2)) << session.time_film << endl;
	++y;
	wcout << setw((130 / 2) + (session.film_name.size() / 2)) << session.film_name << endl;
	++y;
	setCursorPosition(0, y);
	wcout << L"│";
	for (int line = 1; line < 129; ++line) { wcout << L"─"; }
	++y;
	wcout << L"│\n│";
	for (int i = session.rows.size() - 1; i >= 0; --i) {
		setCursorPosition(1, y - 1);
		for (int ozer_line = 0; ozer_line < 4; ++ozer_line) { setCursorPosition(0, ++y); wcout << L"│"; }
		y -= 4;

		drawRow(y, session.rows[i], i + 1);

		--y;
		for (int ozer_line = 0; ozer_line < 5; ++ozer_line) { setCursorPosition(129, ++y); wcout << L"│"; }
		y -= 5;
		y += BOX_HEIGHT + 2;
	}
	setCursorPosition(1, y);
	for (int line = 0; line < 128; ++line) { wcout << L"─"; }
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
					session.rows[i].seats[j].color = L"gray"; // установка цвета текущего места
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
//void ClearScreen() {
//	y = 0;
//	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	CONSOLE_SCREEN_BUFFER_INFO csbi;
//	DWORD count, cellCount;
//	COORD homeCoords = { 0, 0 };
//
//	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
//		cellCount = csbi.dwSize.X * csbi.dwSize.Y; // Исправлено
//		FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
//		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
//		SetConsoleCursorPosition(hConsole, homeCoords);
//	}
//}
void ClearScreen() {
	y = 0;
	// Получаем дескриптор консоли
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count, cellCount;
	COORD homeCoords = { 0, 0 }; // Координаты для верхнего левого угла

	// Получаем информацию о буфере консоли
	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		cellCount = csbi.dwSize.X * csbi.dwSize.Y; // Общее количество ячеек

		// Заполняем буфер пробелами
		FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
		// Устанавливаем предыдущие атрибуты для очищенных ячеек
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
		// Перемещаем курсор обратно в верхний левый угол
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
}

bool correctInput(int& number) {
	wstring input;

	// Читаем всю строку ввода
	getline(wcin, input); // Используем getline для получения всей строки

	// Проверяем на пустую строку и строку, состоящую только из пробелов
	if (input.empty() || input.find_first_not_of(L" \n\r\t") == wstring::npos) {
		return false; // Ввод не может быть пустым
	}

	// Создаем wstringstream для преобразования строки в число
	wstringstream ss(input);
	ss >> number; // Пробуем прочитать целое число из wstringstream

	// Проверяем, успешно ли было преобразование
	if (ss.fail() || !ss.eof()) { // Исправлено: добавлен оператор ||
		return false; // Если преобразование не удалось или остались лишние символы
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
						session.rows[i].seats[k].color = L"gray";
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
	bool moreItems = true; // Флаг для продолжения выбора товаров
	std::vector<std::wstring> selectedItems; // Список выбранных товаров

	while (moreItems) {
		int categoryChoice;
		wcout << L"--- Выберите категорию ---\n";
		wcout << L"1. Напитки\n";
		wcout << L"2. Попкорн\n";
		wcout << L"3. Сладости\n";
		wcout << L"4. Закуски\n";
		wcout << L"5. Десерты\n";
		wcout << L"6. Наборы\n";
		wcout << L"7. Завершить выбор\n";
		wcout << L"Введите номер выбранной категории: ";

		if (!correctInput(categoryChoice) || categoryChoice < 1 || categoryChoice > 7) {
			wcout << L"Некорректный ввод. Попробуйте снова.\n";
			continue;
		}

		if (categoryChoice == 7) { // Завершение выбора
			wcout << L"Вы завершили выбор дополнительных товаров.\n";
			break;
		}

		bool backToCategory = false; // Флаг возврата в меню категорий
		while (!backToCategory) {
			int itemChoice;
			switch (categoryChoice) {
			case 1: // Напитки
				wcout << L"--- Напитки ---\n";
				wcout << L"1. Вода (0.5 л) - 30 рублей\n";
				wcout << L"2. Газированная вода (0.5 л) - 35 рублей\n";
				wcout << L"3. Сок (0.5 л) - 60 рублей\n";
				wcout << L"4. Кола (0.5 л) - 60 рублей\n";
				wcout << L"5. Кофе (300 мл) - 100 рублей\n";
				wcout << L"6. Чай (300 мл) - 50 рублей\n";
				wcout << L"7. Вернуться назад\n";
				wcout << L"Введите номер выбранного товара: ";
				if (!correctInput(itemChoice) || itemChoice < 1 || itemChoice > 7) {
					wcout << L"Некорректный выбор. Попробуйте снова.\n";
					continue;
				}
				if (itemChoice == 7) { // Возврат в меню категорий
					backToCategory = true;
					break;
				}
				switch (itemChoice) {
				case 1: totalAmount += 30; selectedItems.push_back(L"Вода (0.5 л)"); break;
				case 2: totalAmount += 35; selectedItems.push_back(L"Газированная вода (0.5 л)"); break;
				case 3: totalAmount += 60; selectedItems.push_back(L"Сок (0.5 л)"); break;
				case 4: totalAmount += 60; selectedItems.push_back(L"Кола (0.5 л)"); break;
				case 5: totalAmount += 100; selectedItems.push_back(L"Кофе (300 мл)"); break;
				case 6: totalAmount += 50; selectedItems.push_back(L"Чай (300 мл)"); break;
				}
				break;

			case 2: // Попкорн
				wcout << L"--- Попкорн ---\n";
				wcout << L"1. Малый попкорн - 150 рублей\n";
				wcout << L"2. Средний попкорн - 200 рублей\n";
				wcout << L"3. Большой попкорн - 250 рублей\n";
				wcout << L"4. Вернуться назад\n";
				wcout << L"Введите номер выбранного товара: ";
				if (!correctInput(itemChoice) || itemChoice < 1 || itemChoice > 4) {
					wcout << L"Некорректный выбор. Попробуйте снова.\n";
					continue;
				}
				if (itemChoice == 4) { // Возврат в меню категорий
					backToCategory = true;
					break;
				}
				switch (itemChoice) {
				case 1: totalAmount += 150; selectedItems.push_back(L"Малый попкорн"); break;
				case 2: totalAmount += 200; selectedItems.push_back(L"Средний попкорн"); break;
				case 3: totalAmount += 250; selectedItems.push_back(L"Большой попкорн"); break;
				}
				break;

			case 3: // Сладости
				wcout << L"--- Сладости ---\n";
				wcout << L"1. Шоколадный батончик - 50 рублей\n";
				wcout << L"2. Чипсы - 100 рублей\n";
				wcout << L"3. Орешки (150 г) - 150 рублей\n";
				wcout << L"4. Вернуться назад\n";
				wcout << L"Введите номер выбранного товара: ";
				if (!correctInput(itemChoice) || itemChoice < 1 || itemChoice > 4) {
					wcout << L"Некорректный выбор. Попробуйте снова.\n";
					continue;
				}
				if (itemChoice == 4) { // Возврат в меню категорий
					backToCategory = true;
					break;
				}
				switch (itemChoice) {
				case 1: totalAmount += 50; selectedItems.push_back(L"Шоколадный батончик"); break;
				case 2: totalAmount += 100; selectedItems.push_back(L"Чипсы"); break;
				case 3: totalAmount += 150; selectedItems.push_back(L"Орешки (150 г)"); break;
				}
				break;

			case 4: // Закуски
				wcout << L"--- Закуски ---\n";
				wcout << L"1. Хот-дог - 150 рублей\n";
				wcout << L"2. Бургер - 200 рублей\n";
				wcout << L"3. Начос с сыром - 200 рублей\n";
				wcout << L"4. Вернуться назад\n";
				wcout << L"Введите номер выбранного товара: ";
				if (!correctInput(itemChoice) || itemChoice < 1 || itemChoice > 4) {
					wcout << L"Некорректный выбор. Попробуйте снова.\n";
					continue;
				}
				if (itemChoice == 4) { // Возврат в меню категорий
					backToCategory = true;
					break;
				}
				switch (itemChoice) {
				case 1: totalAmount += 150; selectedItems.push_back(L"Хот-дог"); break;
				case 2: totalAmount += 200; selectedItems.push_back(L"Бургер"); break;
				case 3: totalAmount += 200; selectedItems.push_back(L"Начос с сыром"); break;
				}
				break;

			case 5: // Десерты
				wcout << L"--- Десерты ---\n";
				wcout << L"1. Мороженое - 120 рублей\n";
				wcout << L"2. Тортик - 150 рублей\n";
				wcout << L"3. Печенье (2 шт) - 70 рублей\n";
				wcout << L"4. Вернуться назад\n";
				wcout << L"Введите номер выбранного товара: ";
				if (!correctInput(itemChoice) || itemChoice < 1 || itemChoice > 4) {
					wcout << L"Некорректный выбор. Попробуйте снова.\n";
					continue;
				}
				if (itemChoice == 4) { // Возврат в меню категорий
					backToCategory = true;
					break;
				}
				switch (itemChoice) {
				case 1: totalAmount += 120; selectedItems.push_back(L"Мороженое"); break;
				case 2: totalAmount += 150; selectedItems.push_back(L"Тортик"); break;
				case 3: totalAmount += 70; selectedItems.push_back(L"Печенье (2 шт)"); break;
				}
				break;

			case 6: // Наборы
				wcout << L"--- Наборы ---\n";
				wcout << L"1. Попкорн (малый) + сок/кола - 180 рублей\n";
				wcout << L"2. Попкорн (средний) + сок/кола - 230 рублей\n";
				wcout << L"3. Хот-дог + сок/кола + чипсы - 280 рублей\n";
				wcout << L"4. Вернуться назад\n";
				wcout << L"Введите номер выбранного товара: ";
				if (!correctInput(itemChoice) || itemChoice < 1 || itemChoice > 4) {
					wcout << L"Некорректный выбор. Попробуйте снова.\n";
					continue;
				}
				if (itemChoice == 4) { // Возврат в меню категорий
					backToCategory = true;
					break;
				}
				switch (itemChoice) {
				case 1: totalAmount += 180; selectedItems.push_back(L"Попкорн (малый) + сок/кола"); break;
				case 2: totalAmount += 230; selectedItems.push_back(L"Попкорн (средний) + сок/кола"); break;
				case 3: totalAmount += 280; selectedItems.push_back(L"Хот-дог + сок/кола + чипсы"); break;
				}
				break;
			}

			if (backToCategory) break; // Возвращаемся к выбору категории
		}
	}
	wcout << L"\nВы выбрали:\n";
	for (const auto& item : selectedItems) {
		wcout << L"- " << item << L"\n";
	}
	wcout << L"Общая сумма с учётом выбранных товаров: " << totalAmount << L" рублей.\n";
}









// Функция для выбора способа оплаты
void choosePaymentMethod(double totalAmount) {
	int paymentChoice;
	wstring promoCode;
	map<wstring, double> promoCodes = {
		{L"DISCOUNT10", 0.10}, // Промокод на скидку 10%
		{L"DISCOUNT20", 0.20}, // Промокод на скидку 20%
		{L"FREESNACK", 0.15}   // Промокод на скидку 15%
	};

	// Ввод промокода
	wcout << L"--- Промокод ---\n";
	wcout << L"Если у вас есть промокод, введите его. Иначе нажмите Enter: ";
	getline(wcin, promoCode);

	// Применение промокода
	if (!promoCode.empty()) {
		if (promoCodes.find(promoCode) != promoCodes.end()) {
			double discount = promoCodes[promoCode];
			double discountAmount = totalAmount * discount;
			totalAmount -= discountAmount;
			wcout << L"Промокод принят! Скидка: " << discountAmount << L" рублей.\n";
			wcout << L"Итоговая сумма с учётом скидки: " << totalAmount << L" рублей.\n";
		}
		else {
			wcout << L"Некорректный промокод. Сумма без изменений.\n";
		}
	}
	else {
		wcout << L"Промокод не введён. Сумма без изменений.\n";
	}

	// Выбор способа оплаты
	while (true) {
		wcout << L"--- Способы оплаты ---\n";
		wcout << L"1. Наличными\n";
		wcout << L"2. Картой\n";
		wcout << L"3. Электронный кошелёк\n";
		wcout << L"Введите номер выбранного способа оплаты: ";

		if (!correctInput(paymentChoice) || paymentChoice < 1 || paymentChoice > 3) {
			wcout << L"Некорректный ввод. Попробуйте снова.\n";
			continue;
		}

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
		}
		break;
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