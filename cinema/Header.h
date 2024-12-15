#ifndef HEADER_H
#define HEADER_H

#include "ClickTracking.h"

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
#include <codecvt>      
#include <io.h>         
#include <locale>       
#include <fcntl.h>      
#include <map>
#include <cctype>

void selectionDay(int day);
void displayFilmDescription(const std::wstring& filmName);
void extranceToCinema();

using namespace std;

// Конфигурация программы
namespace Config {
	int y = 0;
	constexpr const int BOX_WIDTH = 6;              // Ширина бокса
	constexpr const int BOX_HEIGHT = 3;             // Высота бокса
	constexpr const int CHANSE_NOT_FREE_PLACES = 5; // Вероятность занятого места
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

	int max_count_free_places_in_one_row() { // работает пока не так как я задумал (должно быть максимальное количество свободных мест подряд)
		int max = -1;
		int number_max_row = 0;
		int number_row = 0;
		for (const auto& row : rows) {
			int cnt_free_places = cnt_free_places_in_row(row);
			++number_row;
			if (max < cnt_free_places)
				max = cnt_free_places;
		}
		return max;
	}

	/// <summary>
	/// количество свободных мест в ряду
	/// </summary>
	/// <param name="row">Ряд</param>
	/// <returns></returns>
	int cnt_free_places_in_row(Row row) {
		int free_count_places_in_row = 0;
		for (const auto& seat : row.seats) {
			if (seat.status != L"x" && seat.status != L"0")
				++free_count_places_in_row;
		}
		return free_count_places_in_row;
	}
	/// <summary>
	/// количество свободных мест в зале 
	/// </summary>
	/// <returns></returns>
	int cnt_free_places_in_session() {
		int free_count_places = 0;
		for (const auto& row : rows) {
			free_count_places += cnt_free_places_in_row(row);
		}
		return free_count_places;
	}
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

void  rendering_the_cost_of_tickets(int start_y)
{
	int x_box = 150;
	int temp_y = start_y;
	int temp_y_2 = start_y;
	for (int ozer_line = 0; ozer_line < 17; ++ozer_line) { setCursorPosition(x_box, ++temp_y); wcout << L"│"; }
	setCursorPosition(x_box, start_y);
	wcout << L"┌";
	++start_y;
	for (int line = 0; line < 53; ++line) { wcout << L"─"; }
	wcout << L"┐\n";
	x_box += 2;
	++y;


	drawYellowAvailableBox(x_box, start_y, L"1");
	setCursorPosition(x_box + 3, start_y + BOX_HEIGHT - 1);
	wcout << L"Цена места такого цвета равна " << expensive_place;
	x_box = 152;
	start_y += BOX_HEIGHT + 1;
	drawWhiteAvailableBox(x_box, start_y, L"2");
	setCursorPosition(x_box + 3, start_y + BOX_HEIGHT - 1);
	wcout << L"Цена места такого цвета равна " << cheap_place;
	start_y += BOX_HEIGHT + 1;
	x_box = 152;
	drawGrayOccupiedBox(x_box, start_y);
	setCursorPosition(x_box + 3, start_y + BOX_HEIGHT - 1);
	wcout << L"Места отмеченные этим цветом - заняты";
	start_y += BOX_HEIGHT + 1;
	x_box = 152;
	drawVioletOccupiedBox(x_box, start_y);
	setCursorPosition(x_box + 3, start_y + BOX_HEIGHT - 1);
	wcout << L"Место отмеченные этим цветом выбраны вами";
	start_y += BOX_HEIGHT + 2;
	x_box = 150;

	setCursorPosition(x_box, start_y);
	wcout << L"└";

	for (int ozer_line = 0; ozer_line < 17; ++ozer_line) { setCursorPosition(x_box + 54, ++temp_y_2); wcout << L"│"; }
	setCursorPosition(++x_box, start_y);
	for (int line = 1; line < 54; ++line) { wcout << L"─"; }
	wcout << L"┘\n";
	x_box += 2;
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
	int start_y = y;
	setCursorPosition(0, y);
	wcout << L"┌";

	for (int line = 1; line < 129; ++line) { wcout << L"─"; }
	wcout << L"┐\n";
	setCursorPosition(0, y + 1);
	wcout << L"│";
	++y;
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
	setCursorPosition(0, y);
	wcout << L"└";
	for (int line = 0; line < 128; ++line) { wcout << L"─"; }
	wcout << L"┘";

	rendering_the_cost_of_tickets(start_y);

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

void EnterClear() {
	keybd_event(VK_NEXT, 0, 0, 0); // Нажатие Page Down
	keybd_event(VK_NEXT, 0, KEYEVENTF_KEYUP, 0); // Отпуск Page Down
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

void cleanString(wstring& str) {
	// Удаляем переносы строк и другие невидимые символы
	str.erase(remove(str.begin(), str.end(), L'\r'), str.end());
	str.erase(remove(str.begin(), str.end(), L'\n'), str.end());
	str.erase(remove_if(str.begin(), str.end(), [](wchar_t c) {
		return iswspace(c) && c != L' ';
		}), str.end());
}

// Функция для удаления "\r" последующей очистки данных
void removeCarriageReturn(wstring& line) {
	line.erase(remove(line.begin(), line.end(), L'\r'), line.end());
	cleanString(line); // Чистим строку после удаления символов
}


/// <summary>
/// Генерация данных для сеансов кино на основе данных из файла.
/// Считывает информацию о залах, сеансах и их деталях из файла и загружает их в структуру данных.
/// </summary>
/// <param name="day">Структура данных, содержащая информацию о всех сеансах в трех залах</param>
/// <param name="filename">Имя файла, содержащего данные о сеансах</param>
/// <param name="rowCount">Количество рядов в зале (используется для размещения мест)</param>
/// <param name="placeCount">Количество мест в ряду (используется для размещения мест)</param>
void GenerationDay(Day& day, const wstring& filename, int rowCount, int placeCount) {
	wstringstream file(filename);


	// Устанавливаем кодировку UTF-8
	file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

	wstring line;
	vector<Session>* currentSessionGroup = nullptr;

	wcout << L"Содержимое файла:\n";
	while (getline(file, line)) {
		removeCarriageReturn(line);
		line = replaceDash(line);

		if (line.empty()) continue;

		// Обработка залов
		if (line.find(L"Cinema room 1") != wstring::npos) {
			currentSessionGroup = &day.Cinema_room_1;
			continue;
		}
		if (line.find(L"Cinema room 2") != wstring::npos) {
			currentSessionGroup = &day.Cinema_room_2;
			continue;
		}
		if (line.find(L"Cinema room 3") != wstring::npos) {
			currentSessionGroup = &day.Cinema_room_3;
			continue;
		}

		// Обработка количества сеансов
		if (currentSessionGroup && iswdigit(line[0])) {
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
				Session session;

				if (!getline(file, session.time_film) || session.time_film.empty()) {
					wcerr << L"Ошибка: Некорректное или отсутствует время фильма." << endl;
					return;
				}

				if (!getline(file, session.film_name) || session.film_name.empty()) {
					wcerr << L"Ошибка: Некорректное или отсутствует название фильма." << endl;
					return;
				}

				if (!getline(file, session.genre) || session.genre.empty()) {
					wcerr << L"Ошибка: Некорректный или отсутствует жанр фильма." << endl;
					return;
				}

				if (!getline(file, session.duration) || session.duration.empty()) {
					wcerr << L"Ошибка: Некорректная или отсутствует продолжительность фильма." << endl;
					return;
				}

				cleanString(session.time_film);
				cleanString(session.film_name);
				cleanString(session.genre);
				cleanString(session.duration);

				GenerationRoom(session, rowCount, placeCount, session.film_name, session.time_film, session.genre, session.duration);
				(*currentSessionGroup)[i] = session;
			}
		}
	}
}



void ClearScreen() {
	y = 0;
	//// Получаем дескриптор консоли
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_SCREEN_BUFFER_INFO csbi;
	//DWORD count, cellCount;
	//COORD homeCoords = { 0, 0 }; // Координаты для верхнего левого угла

	//// Получаем информацию о буфере консоли
	//if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
	//	cellCount = csbi.dwSize.X * csbi.dwSize.Y; // Общее количество ячеек

	//	// Заполняем буфер пробелами
	//	FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
	//	// Устанавливаем предыдущие атрибуты для очищенных ячеек
	//	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
	//	// Перемещаем курсор обратно в верхний левый угол
	//	SetConsoleCursorPosition(hConsole, homeCoords);
	//}
	system("cls");
}


/// <summary>
/// Очистка экрана с определённой позиции и до конца
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

// функиция смены масштаба (-)
void PressCtrlMinus(int count) {
	// Эмуляция нажатия клавиши Ctrl
	keybd_event(VK_CONTROL, 0, 0, 0);
	// Эмуляция нажатия клавиши "-"
	keybd_event(VK_OEM_MINUS, 0, 0, 0);
	// Эмуляция отпускания клавиши "-"
	keybd_event(VK_OEM_MINUS, 0, KEYEVENTF_KEYUP, 0);
	// Эмуляция отпускания клавиши Ctrl
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

	count--;
	if (count > 0)
		PressCtrlMinus(count);
}

// функиция смены масштаба (+)
void PressCtrlPlus(int count) {
	// Эмуляция нажатия клавиши Ctrl
	keybd_event(VK_CONTROL, 0, 0, 0);
	// Эмуляция нажатия клавиши "-"
	keybd_event(VK_OEM_PLUS, 0, 0, 0);
	// Эмуляция отпускания клавиши "-"
	keybd_event(VK_OEM_PLUS, 0, KEYEVENTF_KEYUP, 0);
	// Эмуляция отпускания клавиши Ctrl
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

	count--;
	if (count > 0)
		PressCtrlPlus(count);
}

void waitForInput() {
	system("pause");
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); 
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


/// <summary>
/// Функция фильтрует сеансы кинотеатра по запросу пользователя, предоставляя возможность 
/// многократного использования фильтра через интерактивный интерфейс.
/// </summary>
/// <param name="trio_days">Ссылка на объект TrioDays, содержащий данные о сеансах за три дня.</param>
/// <remarks>
/// Пользователь вводит ключевое слово (например, часть названия фильма или жанра), 
/// а функция ищет совпадения среди всех доступных сеансов. Результаты отображаются с указанием 
/// дня, зала, времени, названия и других данных о сеансе.
/// После каждой фильтрации пользователю предлагается возможность повторить поиск или завершить фильтрацию.
/// </remarks>
void filterSessions(TrioDays& trio_days) {
	bool repeatFiltering = true;

	while (repeatFiltering) {
		ClearScreen();
		wcout << L"Введите ключевое слово для поиска (например, название фильма или жанр): ";
		wstring query;
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

		getline(wcin, query);

		if (query.empty()) {
			wcout << L"Ошибка: ключевое слово не может быть пустым. Попробуйте снова.\n";
			wcout << L"Нажмите Enter для продолжения...";
			wcin.ignore();
			continue;
		}

		// Преобразуем запрос в нижний регистр
		locale loc("ru_RU.UTF-8");
		transform(query.begin(), query.end(), query.begin(),
			[&loc](wchar_t c) { return tolower(c, loc); });

		vector<wstring> foundFilms;
		vector<wstring> foundFilmNames;

		// Перебираем все сеансы для поиска совпадений
		for (size_t dayIndex = 0; dayIndex < trio_days.trio_days.size(); ++dayIndex) {
			const Day& day = trio_days.trio_days[dayIndex];
			vector<vector<Session>> allRooms = { day.Cinema_room_1, day.Cinema_room_2, day.Cinema_room_3 };

			for (size_t roomIndex = 0; roomIndex < allRooms.size(); ++roomIndex) {
				const vector<Session>& room = allRooms[roomIndex];
				for (const auto& session : room) {
					// Преобразуем название фильма и жанр в нижний регистр
					wstring sessionFilmLower = session.film_name;
					wstring sessionGenreLower = session.genre;
					cleanString(sessionFilmLower);
					cleanString(sessionGenreLower);
					transform(sessionFilmLower.begin(), sessionFilmLower.end(), sessionFilmLower.begin(),
						[&loc](wchar_t c) { return tolower(c, loc); });
					transform(sessionGenreLower.begin(), sessionGenreLower.end(), sessionGenreLower.begin(),
						[&loc](wchar_t c) { return tolower(c, loc); });

					// Проверка на совпадения с запросом
					if (sessionFilmLower.find(query) != wstring::npos || sessionGenreLower.find(query) != wstring::npos) {
						foundFilms.push_back(L"День: " + to_wstring(dayIndex + 1) +
							L", Зал: " + to_wstring(roomIndex + 1) +
							L", Название: " + session.film_name +
							L", Жанр: " + session.genre +
							L", Время: " + session.time_film +
							L", Продолжительность: " + session.duration);
						foundFilmNames.push_back(session.film_name);  // Добавляем название фильма
					}
				}
			}
		}

		// Если совпадения найдены, выводим все найденные фильмы
		if (!foundFilms.empty()) {
			wcout << L"Найдено совпадений:\n";
			for (size_t i = 0; i < foundFilms.size(); ++i) {
				wcout << L"[" << i + 1 << L"] " << foundFilms[i] << L"\n";
			}

			/*wcout << L"\nЧто вы хотите сделать дальше?\n";
			wcout << L"1. Перейти к описанию найденного фильма\n";
			wcout << L"2. Заново воспользоваться фильтром\n";
			wcout << L"3. Вернуться в меню\n";
			wcout << L"Введите ваш выбор (1-3): ";*/

			wcout << L"\nЧто вы хотите сделать дальше?\n";
			wcout << L"Перейти к описанию найденного фильма <---\n";
			wcout << L"Заново воспользоваться фильтром\n";
			wcout << L"Вернуться в меню\n";
			wcout << L"Используйте стрелочки, для выбора нажмите SPACE";
			//int choice = -1;
			short int choice = 3, prevChoice;
			bool flag = true;
			while (flag) {
				prevChoice = choice;
				tracingUD(choice);
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				switch (choice) {
				case 200:
					choice = prevChoice;
					flag = false;
					wcout << L"" << choice << endl;
					break;
				case 3:
					ClearScreen();
					wcout << L"Найдено совпадений:\n";
					for (size_t i = 0; i < foundFilms.size(); ++i) {
						wcout << L"[" << i + 1 << L"] " << foundFilms[i] << L"\n";
					}
					wcout << L"\nЧто вы хотите сделать дальше?\n";
					wcout << L"Перейти к описанию найденного фильма <---\n";
					wcout << L"Заново воспользоваться фильтром\n";
					wcout << L"Вернуться в меню\n";
					wcout << L"Используйте стрелочки, для выбора нажмите SPACE";
					wcout << L"" << choice << endl;
					break;
				case 2:
					ClearScreen();
					wcout << L"Найдено совпадений:\n";
					for (size_t i = 0; i < foundFilms.size(); ++i) {
						wcout << L"[" << i + 1 << L"] " << foundFilms[i] << L"\n";
					}
					wcout << L"\nЧто вы хотите сделать дальше?\n";
					wcout << L"Перейти к описанию найденного фильма\n";
					wcout << L"Заново воспользоваться фильтром <---\n";
					wcout << L"Вернуться в меню\n";
					wcout << L"Используйте стрелочки, для выбора нажмите SPACE";
					wcout << L"" << choice << endl;
					break;
				case 1:
					ClearScreen();
					wcout << L"Найдено совпадений:\n";
					for (size_t i = 0; i < foundFilms.size(); ++i) {
						wcout << L"[" << i + 1 << L"] " << foundFilms[i] << L"\n";
					}
					wcout << L"\nЧто вы хотите сделать дальше?\n";
					wcout << L"Перейти к описанию найденного фильма\n";
					wcout << L"Заново воспользоваться фильтром\n";
					wcout << L"Вернуться в меню <---\n";
					wcout << L"Используйте стрелочки, для выбора нажмите SPACE";
					wcout << L"" << choice << endl;
					break;
				default:
					ClearScreen();
					choice = 3;
					wcout << L"Найдено совпадений:\n";
					for (size_t i = 0; i < foundFilms.size(); ++i) {
						wcout << L"[" << i + 1 << L"] " << foundFilms[i] << L"\n";
					}
					wcout << L"\nВведено неверное значение\n";
					wcout << L"Что вы хотите сделать дальше?\n";
					wcout << L"Перейти к описанию найденного фильма <---\n";
					wcout << L"Заново воспользоваться фильтром\n";
					wcout << L"Вернуться в меню\n";
					wcout << L"Используйте стрелочки, для выбора нажмите SPACE";
					wcout << L"" << choice << endl;
					break;
				}
			}

			//while (choice != 1 && choice != 2 && choice != 3) {
			//	wstring input;
			//	getline(wcin, input);

			//	// Проверка, является ли введенное число числом и находится ли оно в допустимом диапазоне
			//	if (isNumber(input)) {
			//		choice = std::stoi(input);  // Преобразуем строку в число
			//		if (choice != 1 && choice != 2 && choice != 3) {
			//			wcout << L"Некорректный выбор. Пожалуйста, выберите 1, 2 или 3.\n";
			//		}
			//	}
			//	else {
			//		wcout << L"Ошибка: необходимо ввести число. Пожалуйста, выберите 1, 2 или 3.\n";
			//	}
			//}
				ClearScreen();
				for (size_t i = 0; i < foundFilms.size(); ++i) {
					wcout << L"[" << i + 1 << L"] " << foundFilms[i] << L"\n";
				}

			switch (choice) {	
			case 3: {
				// Пользователь выбрал перейти к описанию фильма
				wcout << L"Введите номер фильма для получения описания: ";
				int filmIndex = -1;
				while (filmIndex < 1 || filmIndex > foundFilms.size()) {
					wstring input;
					getline(wcin, input);

					// Проверка
					if (isNumber(input)) {
						filmIndex = std::stoi(input);
						if (filmIndex < 1 || filmIndex > foundFilms.size()) {
							wcout << L"Некорректный номер фильма. Введите число от 1 до " << foundFilms.size() << L".\n";
						}
					}
					else {
						wcout << L"Ошибка: необходимо ввести число. Пожалуйста, введите номер фильма от 1 до " << foundFilms.size() << L".\n";
					}
				}

				// Вызываем функцию для отображения описания выбранного фильма
				displayFilmDescription(foundFilmNames[filmIndex - 1]);
				extranceToCinema();
				break;
			}
			case 2:
				// Повторить фильтрацию
				continue;
			case 1:
				// Вернуться в меню
				repeatFiltering = false;
				break;
			}
		}
		else {
			wcout << L"Совпадений не найдено.\n";
		}
	}
}


//авто выбор мест
bool autoChoosingPlace(Session& session, int cnt_places, int& bookedRow, vector<int>& bookedRows, vector<int>& bookedPlaces, double& totalCost) {
	int all_free_places = session.cnt_free_places_in_session(); // Количество всех свободных мест

	// Если запрошено больше мест, чем свободно, сразу возвращаем false
	if (cnt_places > all_free_places) {
		return false;
	}

	// Приоритет 1: искать подряд свободные места в одном ряду, начиная с центра зала
	int mid_row = session.rows.size() / 2;
	for (int offset = 0; offset <= mid_row; ++offset) {
		for (int i : {mid_row - offset, mid_row + offset}) {
			if (i < 0 || i >= session.rows.size()) continue;

			int cnt = 0;  // Счётчик свободных мест подряд
			int start_index = -1; // Индекс начала первого подходящего участка

			for (int j = 1; j < session.rows[i].seats.size() - 1; ++j) { // Проход от 1 до предпоследнего индекса
				if (session.rows[i].seats[j].status != L"x" && session.rows[i].seats[j].status != L"0") {
					if (cnt == 0) start_index = j; // Устанавливаем начало участка
					++cnt;

					if (cnt == cnt_places) { // Если нашли подходящий участок
						// Помечаем места как занятые
						for (int k = start_index; k < start_index + cnt_places; ++k) {
							session.rows[i].seats[k].status = L"x";
							session.rows[i].seats[k].color = L"violet";
							bookedRows.push_back(i);
							bookedPlaces.push_back(k);
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
					cnt = 0; // Сбрасываем счётчик
					start_index = -1;
				}
			}
		}
	}

	// Приоритет 1 (часть 2): Разбиваем по разным рядам, если не удалось найти подряд
	vector<pair<int, int>> selected_seats; // Пара (ряд, место)
	int total_found = 0;

	for (int offset = 0; offset <= mid_row && total_found < cnt_places; ++offset) {
		for (int i : {mid_row - offset, mid_row + offset}) {
			if (i < 0 || i >= session.rows.size()) continue;

			for (int j = 1; j < session.rows[i].seats.size() - 1 && total_found < cnt_places; ++j) {
				if (session.rows[i].seats[j].status != L"x" && session.rows[i].seats[j].status != L"0") {
					selected_seats.emplace_back(i, j);
					total_found++;
				}
			}
		}
	}

	if (total_found == cnt_places) {
		for (const auto& seat : selected_seats) {
			int row = seat.first;
			int place = seat.second;
			session.rows[row].seats[place].status = L"x";
			session.rows[row].seats[place].color = L"violet";
			bookedRows.push_back(row);
			bookedPlaces.push_back(place);
			totalCost += session.rows[row].seats[place].cost;
		}
		ClearScreen();
		DrawSession(session, session.rows.size(), session.rows[0].seats.size());
		for (const auto& seat : selected_seats) {
			session.rows[seat.first].seats[seat.second].color = L"gray";
		}
		return true;
	}

	// Приоритет 2: искать места ближе к центру ряда
	for (int offset = 0; offset <= mid_row; ++offset) {
		for (int i : {mid_row - offset, mid_row + offset}) {
			if (i < 0 || i >= session.rows.size()) continue;

			int center = session.rows[i].seats.size() / 2;
			vector<int> free_indices;

			for (int offset_c = 0; offset_c <= center; ++offset_c) {
				if (center - offset_c >= 1 && session.rows[i].seats[center - offset_c].status != L"x" && session.rows[i].seats[center - offset_c].status != L"0") {
					free_indices.push_back(center - offset_c);
				}
				if (center + offset_c < session.rows[i].seats.size() - 1 && session.rows[i].seats[center + offset_c].status != L"x" && session.rows[i].seats[center + offset_c].status != L"0") {
					free_indices.push_back(center + offset_c);
				}
				if (free_indices.size() >= cnt_places) break;
			}

			if (free_indices.size() >= cnt_places) {
				for (int k = 0; k < cnt_places; ++k) {
					int place = free_indices[k];
					session.rows[i].seats[place].status = L"x";
					session.rows[i].seats[place].color = L"violet";
					bookedRows.push_back(i);
					bookedPlaces.push_back(place);
					totalCost += session.rows[i].seats[place].cost;
				}
				ClearScreen();
				DrawSession(session, session.rows.size(), session.rows[0].seats.size());
				for (int k = 0; k < cnt_places; ++k) {
					session.rows[i].seats[free_indices[k]].color = L"gray";
				}
				return true;
			}
		}
	}

	return false; // Если не удалось найти подходящих мест
}







// Функция для вывода всех деталей билета
void printTicketDetails(const vector<int>& bookedRows, const vector<int>& bookedPlaces, int cnt_places, double totalTicketCost, const wstring& filmName, const wstring& filmTime, const wstring& genre, const wstring& duration) {
	// Формируем строку для отображения мест и рядов
	wstring places;
	wstring rows;
	for (size_t i = 0; i < bookedPlaces.size(); ++i) {
		rows += to_wstring(bookedRows[i] + 1);
		places += to_wstring(bookedPlaces[i] + 1);
		if (i < bookedPlaces.size() - 1) {
			rows += L", ";
			places += L", ";
		}
	}
	// Красивый и объёмный формат без рамок
	wcout << L"===========================================\n";
	wcout << L"               ВАШ БИЛЕТ                   \n";
	wcout << L"===========================================\n\n";

	wcout << L" Кинотеатр:    Имени \"6104\"\n";
	wcout << L" -----------------------------------------\n";
	wcout << L" Фильм:        " << filmName << L"\n";
	wcout << L" Жанр:         " << genre << L"\n";
	wcout << L" Время:        " << filmTime << L"\n";
	wcout << L" Длительность: " << duration << L"\n";
	wcout << L" -----------------------------------------\n";

	wcout << L" Ваши места: \n";
	wcout << L" -----------------------------------------\n";
	wcout << L" Ряды:        " << rows << L"\n";
	wcout << L" Места:       " << places << L"\n";
	wcout << L" -----------------------------------------\n";

	wcout << L" Количество билетов: " << cnt_places << L"\n";
	wcout << L" Итого к оплате:     " << totalTicketCost << L"₽\n";
	wcout << L" -----------------------------------------\n";

	wcout << L"===========================================\n";
	wcout << L"       Спасибо за ваш выбор!              \n";
	wcout << L"     Желаем приятного просмотра!         \n";
	wcout << L"===========================================\n";
}

void displayMenuFromFile(const wstring& menuFile) {
	wifstream file(menuFile, ios::binary);
	if (!file.is_open()) {
		wcout << L"Ошибка: Не удалось открыть файл меню " << menuFile << L".\n";
		return;
	}

	file.imbue(locale(locale::empty(), new codecvt_utf8_utf16<wchar_t>()));
	wstring line;

	// Чтение и вывод меню из файла
	while (getline(file, line)) {
		wcout << line << endl;
	}

	file.close();
}

bool correctInputQuantity(int& quantity) {
	wstring input;
	wcin >> input;

	try {
		quantity = stoi(input);  // Преобразуем введенную строку в количество
		return quantity >= 1;  // Количество должно быть хотя бы 1
	}
	catch (...) {
		return false;  // Если не удается преобразовать или количество меньше 1, возвращаем false
	}
}
void loadAndShowBuffetMenu(double& totalBuffetCost) {
	// Визуальная часть меню выводится из файла
	displayMenuFromFile(L"menu.txt");
	map<int, pair<wstring, double>> menuOptions = {
		{1, {L"Вода (0.5 л)", 30.0}},
		{2, {L"Газ. вода (0.5 л)", 35.0}},
		{3, {L"Сок (0,5 л)", 50.0}},
		{4, {L"Кола (0,5 л)", 60.0}},
		{5, {L"Кофе (300 мл)", 100.0}},
		{6, {L"Чай (300 мл)", 50.0}},
		{7, {L"Малый попкорн", 150.0}},
		{8, {L"Средний попкорн", 200.0}},
		{9, {L"Большой попкорн", 250.0}},
		{10, {L"Шоколадный батончик", 50.0}},
		{11, {L"Мороженое стаканчик", 60.0}},
		{12, {L"Тортик", 150.0}},
		{13, {L"Орешки в шоколаде", 100.0}},
		{14, {L"Хот-дог", 150.0}},
		{15, {L"Бургер", 200.0}},
		{16, {L"Начос с сыром", 200.0}},
		{17, {L"Чипсы", 100.0}},
		{18, {L"Попкорн (мал) + сок/кола", 180.0}},
		{19, {L"Попкорн (сред) + сок/кола", 230.0}},
		{20, {L"Хот-дог + сок/кола + чипсы", 280.0}}
	};

	// Заранее определенные пункты меню и их стоимость


	// Логика обработки выбора пользователя
	while (true) {
		// Снова выводим меню
		int choice;
		wcout << L"Введите номер вашего выбора (0 для завершения): ";

		// Проверка на корректный ввод
		while (!correctInput(choice) || choice > 20) {
			ClearScreenFromPosition(0, 49);
			wcout << L"Некорректный ввод. Попробуйте снова.\n";
		}

		// Проверка на завершение выбора
		if (choice == 0) {
			wcout << L"Завершение выбора.\n";
			return;
		}

		// Проверяем, что выбранный пункт существует
		auto it = menuOptions.find(choice);
		if (it != menuOptions.end()) {
			int quantity;
			wcout << L"Введите количество: ";

			// Проверка на корректный ввод количества
			while (!correctInput(quantity)) {
				ClearScreenFromPosition(0, 50);
				wcout << L"Некорректное количество. Попробуйте снова.\n";
				wcin.clear();               // Очищаем флаг ошибки ввода
			}

			// Добавляем стоимость в общий заказ с учетом количества
			totalBuffetCost += it->second.second * quantity;
			ClearScreenFromPosition(0, 50);
			wcout << L"Вы добавили " << quantity << L" шт. '" << it->second.first << L"' на сумму " << it->second.second * quantity << L" рублей.\n";
		}
		else {
			wcout << L"Некорректный выбор. Попробуйте снова.\n";
		}
	}
}
// Функция для выбора способа оплаты
void choosePaymentMethod(double totalTicketCost, int cnt_places, double& totalBuffetCost) {
	int paymentChoice;
	wstring promoCode;
	double summ = totalTicketCost + totalBuffetCost;
	map<wstring, double> promoCodes = {
		{L"DIRECTOR80", 0.80}, // Промокод на скидку 80%
		{L"LUCKY10", 0.10},    // Промокод из игры (10%)
		{L"BIGGROUP25", 0.25}, // Промокод из игры (25% на 5 билетов)
		{L"BEST35", 0.35}      // Промокод из игры (35% на 1 билет)
	};

	// Ввод промокода
	while (true) {
		wcout << L"--- Промокод ---\n";
		wcout << L"Если у вас есть промокод, введите его. Иначе нажмите Enter: ";
		getline(wcin, promoCode);

		// Применение промокода
		if (!promoCode.empty()) {
			// Проверка на корректность промокода
			if (promoCodes.find(promoCode) != promoCodes.end()) {
				double discount = promoCodes[promoCode];

				if (promoCode == L"BIGGROUP25") {
					// Проверка на количество билетов
					if (cnt_places == 5) {
						double discountAmount = totalTicketCost * discount;
						totalTicketCost -= discountAmount;
						wcout << L"Промокод BIGGROUP25 принят! Скидка: " << discountAmount << L" рублей.\n";
						wcout << L"Итоговая сумма с учётом скидки: " << totalTicketCost + totalBuffetCost << L" рублей.\n";
					}
					else {
						wcout << L"Промокод BIGGROUP25 применим только при покупке 5 билетов.\n";
						continue;
					}
				}
				else if (promoCode == L"BEST35") {
					// Скидка на каждый билет
					double discountAmountPerTicket = totalTicketCost * discount / cnt_places;
					double totalDiscountAmount = discountAmountPerTicket * cnt_places;
					totalTicketCost -= totalDiscountAmount;

					wcout << L"Промокод BEST35 принят! Скидка на каждый билет: " << discountAmountPerTicket << L" рублей.\n";
					wcout << L"Итоговая сумма с учётом скидки: " << totalTicketCost + totalBuffetCost << L" рублей.\n";
				}
				else {
					double discountAmount = summ * discount;
					summ -= discountAmount;
					wcout << L"Промокод принят! Скидка: " << discountAmount << L" рублей.\n";
					wcout << L"Итоговая сумма с учётом скидки: " << summ << L" рублей.\n";
				}
				break; // Выход из цикла, если промокод принят
			}
			else {
				wcout << L"Некорректный промокод. Попробуйте снова.\n";
			}
		}
		else {
			wcout << L"Промокод не введён. Сумма без изменений.\n";
			break; // Выход из цикла, если промокод не введён
		}

		// Запрос на повторный ввод
		wcout << L"Хотите ввести промокод ещё раз? (y/n): ";
		wchar_t choice;
		wcin >> choice;
		wcin.ignore(INT_MAX, L'\n'); // Очищаем оставшиеся символы после ввода
		ClearScreenFromPosition(0, 12);

		if (choice != L'y' && choice != L'Y') {
			wcout << L"Применение промокода завершено. Сумма без изменений.\n";
			break; // Выход из цикла, если пользователь не хочет вводить промокод
		}
	}

	// Выбор способа оплаты
	while (true) {
		wcout << L"--- Способы оплаты ---\n";
		wcout << L"1. Наличными\n";
		wcout << L"2. Картой\n";
		wcout << L"3. Электронный кошелёк\n";
		wcout << L"Введите номер выбранного способа оплаты: ";

		while (!correctInput(paymentChoice) || paymentChoice < 1 || paymentChoice > 3) {
			ClearScreenFromPosition(0, 20);
			wcout << L"Некорректный ввод. Попробуйте снова.\n";
		}

		// Если ввод корректный, очищаем сообщения об ошибке
		switch (paymentChoice) {
		case 1:
			wcout << L"Вы выбрали оплату наличными. Общая сумма: " << summ << L" рублей.\n";
			break;
		case 2:
			wcout << L"Вы выбрали оплату картой. Общая сумма: " << summ << L" рублей.\n";
			break;
		case 3:
			wcout << L"Вы выбрали оплату электронным кошельком. Общая сумма: " << summ << L" рублей.\n";
			break;
		}
		break;
	}

	wcout << L"Спасибо за ваш выбор! Транзакция завершена.\n";
}


//выбор места
void choosingPlace(Session& session, int day) {
	DrawSession(session, session.rows.size(), session.rows[0].seats.size());
	setCursorPosition(0, y);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	int choice;
	int cnt_error_messeg = 0;
	double totalTicketCost = 0;
	double totalBuffetCost = 0;
	// Выбор способа бронирования
	//int max_free_row = session.max_count_free_places_in_one_row();
	int all_free_places = session.cnt_free_places_in_session();
	wcout << L"Количество свобоных мест в зале равно: " << all_free_places << "\n";
	//wcout << L"Максимальное количество свободных мест в ряду: " << max_free_row <<"\n"; // посчёст мест не подряд
	wcout << L"Выберите способ бронирования мест:\n";
	wcout << L"1. Автоподбор мест\n";
	wcout << L"2. Ручной выбор мест\n";
	wcout << L"0. Вернуться назад\n";
	wcout << L"Введите ваш выбор: ";
	while (true) {

		if (cnt_error_messeg >= 3) {
			ClearScreenFromPosition(19, 41);
			cnt_error_messeg = 0;
			continue;
		}
		

		if (!correctInput(choice) || (choice != 1 && choice != 2 && choice != 0)) {
			if (choice != 1 && choice != 2) {
				cnt_error_messeg += 3;
				wcout << L"Некорректный ввод. Введите 1 или 2.\n";
				continue;
			}
			continue;
		}

		if (choice == 0) {
			ClearScreen();
			selectionDay(day);
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
				wcout << L"Введите количество мест (меньше "<< all_free_places << L"): ";

				if (!correctInput(cnt_places)) {
					++cnt_error_messeg;
					wcout << L"Некорректный ввод. Введите количество мест заново.\n";
					continue;
				}

				if (cnt_places <= 0 || cnt_places > all_free_places) {
					++cnt_error_messeg;
					wcout << L"Количество мест вне диапазона. Пожалуйста, введите корректное количество.\n";
					continue;
				}

				if (!autoChoosingPlace(session, cnt_places, bookedRow, bookedRows, bookedPlaces, totalTicketCost)) {
					wcout << L"К сожалению, не удалось найти " << cnt_places << L" свободных рядом мест.\n";
					++cnt_error_messeg;
					continue;
				}


				wcout << L"Места успешно забронированы.\n";
				waitForInput();
				//Sleep(1000);  // Задержка в 2000 миллисекунд (2 секунды)
				system("cls");

				// Вывод всех деталей билета
				loadAndShowBuffetMenu(totalBuffetCost);
				Sleep(1000);  // Задержка в 2000 миллисекунд (2 секунды)
				system("cls");
				printTicketDetails(bookedRows, bookedPlaces, cnt_places, totalTicketCost, session.film_name, session.time_film, session.genre, session.duration);
				choosePaymentMethod(totalTicketCost, cnt_places, totalBuffetCost);
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
						totalTicketCost += session.rows[row].seats[place].cost;
						bookedRows.push_back(row);
						bookedPlaces.push_back(place);
						break;
					}
				}
				Sleep(1000);  // Задержка в 2000 миллисекунд (2 секунды)
				system("cls");
				loadAndShowBuffetMenu(totalBuffetCost);
				Sleep(1000);
				system("cls");
				printTicketDetails(bookedRows, bookedPlaces, cnt_places, totalTicketCost, session.film_name, session.time_film, session.genre, session.duration);
				choosePaymentMethod(totalTicketCost,cnt_places,totalBuffetCost);
				break;
			}
			break;// завершение программы.
		}
	}
}

#endif // HEADER_H