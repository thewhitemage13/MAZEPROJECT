#include "Mazex.h" 
using namespace std; // раскрытие пространства имён, в котором объявлены cin и cout

// прототипы функций:
void systemname();
void options();    // настройка размеров и расположения окна, установка заголовка, скрытие мигающего курсора
void MoveWindow();
void menu(); // три пункта меню
void letter(int x, int y, int forecolor, int backcolor, char symb); // рисование квадрата с буквой для заставки
void text_effect(int x, int y, int forecolor, int backcolor, const char* symb, int len, int pause); // показ "ленты" текста
void exit(); // быстрый выход из приложения
void the_end(); // концовка с пожеланием удачи
void stand(int x, int y, int k, const char* str); // вспомогательная функция по установке курсора в нужную позцию + окрашивание
void help(); // открытие файла справки
void game(); // основной игровой процесс

// точка входа в приложение
void main()
{
	options();
	menu();
}

void letter(int x, int y, short forecolor, int backcolor, char symb) // функция вывода квадратика с буквой (стилизация под клавиатуру)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int sizeX = 9; // размер квадрата по ширине
	int sizeY = 7; // по высоте
	// отрисовка квадрата двойным циклом
	for (int j = 0; j < sizeY; j++)
	{
		for (int i = 0; i < sizeX; i++)
		{
			COORD temp = { x + i, y + j }; // назначение координат
			SetConsoleCursorPosition(h, temp); // установка координат
			SetConsoleTextAttribute(h, backcolor * 16 + forecolor); // окрашивание
			cout << " "; // рисуем пробелы определённого цвета, из которых состоят квадраты
		}
	}

	// пишем букву в центре квадрата
	COORD temp = { x + sizeX / 2, y + sizeY / 2 };
	SetConsoleCursorPosition(h, temp);
	cout << symb;
}

void systemname()
{
	system("title Keyboard simulator");
	system("mode con cols=130 lines=50");
}

void options()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	// размер окна - 130х50 символов
	CONSOLE_CURSOR_INFO ci; // скрытие курсора
	ci.bVisible = false; // курсор не видно
	ci.dwSize = 100; // на самом деле, не важно что сюда писать - подходит любое значение от 1 до 100 (рамер курсора в процентах относительно клетки)
	SetConsoleCursorInfo(h, &ci); // применить настройки
}

void MoveWindow()
{
	MoveWindow(GetConsoleWindow(), 50, 50, 2000, 2000, true); // двигаем окно: консольное окно ставится в точку 50 пикселей по иксу и 50 по игреку относительно рабочего стола
	// 2000х2000 - максимальные размеры окна, тру - перерисовка (обычно это имеет значение для приложений под виндовс)
}

// побуквенный показ переданного текста:
// x y - начальные координаты показа, фор и бэк калар - цвет текста и фона, текст - указатель на строку текста, лен - длина этого текста, пауз - время в мс перед показом следующей буквы текста
void text_effect(int x, int y, int forecolor, int backcolor, const char* text, int len, int pause)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < len; i++)
	{
		COORD temp = { x + i, y }; // будем ставить курсор в определённые координаты
		SetConsoleCursorPosition(h, temp); // ставим
		SetConsoleTextAttribute(h, backcolor * 16 + forecolor); // применяем цвет
		cout << text[i]; // рисуем букву
		Sleep(pause); // ждём
	}
}

void exit()
{ // делаем цвет текста чёрным - чтобы пользователь не увидел никаких надписей
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 0);
	system("taskkill -im cmd.exe"); // закрываем все процессы по имени cmd - это все консольные окна
}

void the_end()
{
	text_effect(5, 2, 12, 0, "Thank you for playing!", 30, 20); // красным цветом благодарим за игру
	text_effect(5, 4, 7, 0, "Press Enter to exit", 24, 15); // белым цветом выводим просьбу нажать на энтер

	while (_getch() != 13); // до тех пор, пока пользователь не нажмёт на энтер - у него код 13
	exit(); // выходим
}

void stand(int x, int y, int k, const char* str)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c{ x, y };
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, k);
	cout << str << "\n";
}

void help()
{

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 10);
	system("type spravka.txt"); // стандартная команда виндовс по распечатке файла (файл лежит в папке с проектом!)

	while (true)
	{
		int n = _getch();
		if (n == 27 || n == 'n') menu();
	}
}
void game()
{
	System("title Maze");
	Console();
	srand(time(0)); // запуск алгоритма генерации СЧ

	const int width = 60; // ширина лабиринта
	const int height = 15; // высота лабиринта
	int maze[height][width]; // заготовка для лабиринта в виде двумерного массива, заполненного нулями
	int two = 0;//создал переменную для посчета кол-ва монет 

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			maze[y][x] = rand() % 5; // 0 1 2 3

			// установка стен по бокам (делаем рамки)
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
				maze[y][x] = 1; // стенка слева

			// определение точки входа и выхода из лабиринта
			if (x == 0 && y == 2 || x == 1 && y == 2 || x == 2 && y == 2 ||
				x == width - 1 && y == height - 3)
				maze[y][x] = 0;

			// если текущий элемент 2д-массива - это враг,
			// то ниже код, который уменьшает их количество
			// условно, произойдёт жеребьёвка (или же подбрасывание монетки)

			if (maze[y][x] == 3)
			{
				int r = rand() % 10; // 0...9
				// если выпадает 0 - враг остаётся (10% случаев)
				if (r != 0) // если выпадает не 0 (а число от 1 до 9) - врага убираем (вероятность 90%)
				{
					maze[y][x] = 0; // убираем врага
				}
			}
			if (maze[y][x] == 4)
			{
				int a = rand() % 10; // 0...9
				// если выпадает 0 - аптечка остаётся (10% случаев)
				if (a != 0) // если выпадает не 0 (а число от 1 до 9) - врага убираем (вероятность 90%)
				{
					maze[y][x] = 0; // убираем аптечку 
				}

			}
			if (maze[y][x] == 2)
			{
				two++;//считаем кол-во монет на карте
			}
			if (maze[y][x] == 0)//коридор
			{
				SetCursor(x, y, 0, " ");
			}
			else if (maze[y][x] == 1)//стена
			{
				SetCursor(x, y, 3, "");
				cout << (char)178;
			}
			else if (maze[y][x] == 2)//монетки
			{
				SetCursor(x, y, 14, ".");
			}
			else if (maze[y][x] == 3)//враг
			{
				SetCursor(x, y, 12, "");
				cout << (char)2;
			}
			else if (maze[y][x] == 4)//аптечка
			{
				SetCursor(x, y, 12, "");
				cout << (char)3;
			}
			else
			{
				cout << maze[y][x];
			}
		}
		cout << "\n";
	}

	// пример установки курсора в любые координаты консоли
	COORD position;
	position.X = 0;
	position.Y = 2;
	SetCursor(0, 2, 13, "");

	// cout << "O";
	int coins = 0;
	int health = 100;
	int health2 = 100;
	int money = two;

	cout << (char)1;

	// начинаем интерактив (польщователь управляет смайликом с помощью клавиатуры)
	while (true)
	{
		if (_kbhit())
		{
			int code = _getch(); // get character - получение кода нажатой клавиши
			if (code == 224) // если была нажата какая-то стрелка
			{
				code = _getch();
			}

			// после того, как клавиша стрелки была нажата, программа уже знает, куда побежит смайлик
			// можно стереть смайлик в его текущей позиции
			SetCursor(position.X, position.Y, 0, " ");

			if (code == RIGHT and maze[position.Y][position.X + 1] != 1) // right
			{
				position.X++; // изменение позиции ГГ вправо на 1 по иксу
			}
			else if (code == LEFT and maze[position.Y][position.X - 1] != 1)
			{
				position.X--;
			}
			else if (code == UP and maze[position.Y - 1][position.X] != 1)
			{
				position.Y--;
			}
			else if (code == DOWN and maze[position.Y + 1][position.X] != 1)
			{
				position.Y++;
			}

			// ПРАКТИКА1: сделать перемещение вниз и вверх!
			// скинуть в телеграм только длва элс-ифа на перемещение вверх-вниз

			// показываем смайлик в новых координатах
			SetCursor(position.X, position.Y, 13, "");

			cout << (char)1;


			///////////////////////////////////////////////////////////////////
			//проверка на выход из лаберинта 

			//////////////////////////////////////////////////////////////////
			//выводжу кол-монет
			COORD money_info;
			money_info.X = width + 1;
			money_info.Y = 1;
			SetConsoleCursorPosition(h, money_info); // установка курсора в новые координаты
			SetConsoleTextAttribute(h, 10);
			cout << "The number of coins in the gaim : " << money;

			if (position.X == width - 1 and position.Y == height - 3)
			{
				MessageBoxA(0, "You found your way out of the maze!!!!", "You win!!!", MB_OK);
				break;
			}
			////////////////////////////////////////////////////////////////////
			//ПРОВЕРКА НА ПОДБОР МОНЕТКИ
			if (maze[position.Y][position.X] == 2)
			{
				coins++;
				maze[position.Y][position.X] = 0;
				COORD coins_info;
				coins_info.X = width + 1;
				coins_info.Y = 2;

				SetConsoleCursorPosition(h, coins_info); // установка курсора в новые координаты
				SetConsoleTextAttribute(h, 14);
				cout << "Number of coins picked up: " << coins;

			}



			if (coins == two)//если мы собрали все монеты,то игра заканчивается выигрышом

			{
				Message("You have collected all the coins!!! ", "You win!!!");
				break;
			}

			if (maze[position.Y][position.X] == 3)
			{
				health -= 20;

				maze[position.Y][position.X] = 0;
				COORD health_info;

				health_info.X = width + 1;
				health_info.Y = 3;
				SetConsoleCursorPosition(h, health_info); // установка курсора в новые координаты
				SetConsoleTextAttribute(h, 13);

				cout << "Hit points: " << health;
				cout << "\n";
			}

			if (maze[position.Y][position.X] == 4 and health < 100)
			{

				health += 20;

				maze[position.Y][position.X] = 0;
				COORD health_info;
				health_info.X = width + 1;
				health_info.Y = 3;

				SetConsoleCursorPosition(h, health_info); // установка курсора в новые координаты
				SetConsoleTextAttribute(h, 13);


				cout << "Hit points: " << health;

				cout << "\n";
			}

			if (health == 0)
			{
				Message("You have run out of health!!!!", "You are dead!!!!");
				break;
			}
		}

		else // нажатия не было, двигаем врагов
		{
			Sleep(20);
			///////////////////////////////////////////////////////////////
			// движение врагов
			COORD enemy_positions[100]; // массив который хранит координаты врагов
			int enemy_count = 0; // реальное количество врагов на данный момент после шага ГГ

			// перебор всех ячеек которые есть в лабиринте
			for (int y = 0; y < height; y++) // перебор строк
			{
				for (int x = 0; x < width; x++) // перебор столбцов
				{
					// если очередная ячейка - это враг
					if (maze[y][x] == MazeObject::ENEMY)
					{
						enemy_positions[enemy_count].X = x;
						enemy_positions[enemy_count].Y = y;
						enemy_count++;
					}
				}
			}

			// перебор всех врагов
			for (int i = 0; i < enemy_count; i++)
			{
				int r = rand() % 100; // 0-left, 1-right, 2-up, 3-down
				if (r == LEFT &&
					maze[enemy_positions[i].Y][enemy_positions[i].X - 1] != MazeObject::WALL &&
					maze[enemy_positions[i].Y][enemy_positions[i].X - 1] != MazeObject::BORDER &&
					maze[enemy_positions[i].Y][enemy_positions[i].X - 1] != MazeObject::ENEMY)
				{
					// стирание врага в старой позиции
					COORD temp = enemy_positions[i];
					SetConsoleCursorPosition(h, temp);
					cout << " ";
					maze[enemy_positions[i].Y][enemy_positions[i].X] = MazeObject::HALL;

					// перемещаем врага в новую позицию
					temp.X = enemy_positions[i].X - 1;
					temp.Y = enemy_positions[i].Y;
					SetConsoleCursorPosition(h, temp);
					SetConsoleTextAttribute(h, Color::RED);
					cout << (char)2;
					maze[enemy_positions[i].Y][enemy_positions[i].X - 1] = MazeObject::ENEMY;
				}
				else if (r == RIGHT &&
					maze[enemy_positions[i].Y][enemy_positions[i].X + 1] != MazeObject::WALL &&
					maze[enemy_positions[i].Y][enemy_positions[i].X + 1] != MazeObject::BORDER &&
					maze[enemy_positions[i].Y][enemy_positions[i].X + 1] != MazeObject::ENEMY)
				{
					// стирание врага в старой позиции
					COORD temp = enemy_positions[i];
					SetConsoleCursorPosition(h, temp);
					cout << " ";
					maze[enemy_positions[i].Y][enemy_positions[i].X] = MazeObject::HALL;

					// перемещаем врага в новую позицию
					temp.X = enemy_positions[i].X + 1;
					temp.Y = enemy_positions[i].Y;
					SetConsoleCursorPosition(h, temp);
					SetConsoleTextAttribute(h, Color::RED);
					cout << (char)2;
					maze[enemy_positions[i].Y][enemy_positions[i].X + 1] = MazeObject::ENEMY;
				}

				else if (r == UP &&
					maze[enemy_positions[i].Y - 1][enemy_positions[i].X] != MazeObject::WALL &&
					maze[enemy_positions[i].Y - 1][enemy_positions[i].X] != MazeObject::BORDER &&
					maze[enemy_positions[i].Y - 1][enemy_positions[i].X] != MazeObject::ENEMY)
				{
					// стирание врага в старой позиции
					COORD temp = enemy_positions[i];
					SetConsoleCursorPosition(h, temp);
					cout << " ";
					maze[enemy_positions[i].Y][enemy_positions[i].X] = MazeObject::HALL;

					// перемещаем врага в новую позицию
					temp.X = enemy_positions[i].X;
					temp.Y = enemy_positions[i].Y - 1;
					SetConsoleCursorPosition(h, temp);
					SetConsoleTextAttribute(h, Color::RED);
					cout << (char)2;
					maze[enemy_positions[i].Y - 1][enemy_positions[i].X] = MazeObject::ENEMY;
				}
				else if (r == DOWN &&
					maze[enemy_positions[i].Y + 1][enemy_positions[i].X] != MazeObject::WALL &&
					maze[enemy_positions[i].Y + 1][enemy_positions[i].X] != MazeObject::BORDER &&
					maze[enemy_positions[i].Y + 1][enemy_positions[i].X] != MazeObject::ENEMY)
				{
					// стирание врага в старой позиции
					COORD temp = enemy_positions[i];
					SetConsoleCursorPosition(h, temp);
					cout << " ";
					maze[enemy_positions[i].Y][enemy_positions[i].X] = MazeObject::HALL;

					// перемещаем врага в новую позицию
					temp.X = enemy_positions[i].X;
					temp.Y = enemy_positions[i].Y + 1;
					SetConsoleCursorPosition(h, temp);
					SetConsoleTextAttribute(h, Color::RED);
					cout << (char)2;
					maze[enemy_positions[i].Y + 1][enemy_positions[i].X] = MazeObject::ENEMY;
				}
			}
		}
	}
}

void menu()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	system("title Keyboard simulator");
	int start_y = 3;
	system("cls"); // очистка экрана
	stand(5, start_y, 10, "Help");
	stand(5, start_y + 2, 2, "Game");
	stand(5, start_y + 4, 2, "Exit");

	int k;	// код клавиши
	int cur = 1;	// какой пункт выбран сейчас
	while (true)
	{
		k = _getch();
		if (k == 80) // если нажата курсорная клавиша вниз
		{
			if (cur < 3)
			{
				cur++;
				if (cur == 2)
				{
					stand(5, start_y, 2, "Help"); // 2 - это тёмно-зелёный цвет
					stand(5, start_y + 2, 10, "Game"); // 10 - ярко-зелёный
				}
				else if (cur == 3) {
					stand(5, start_y + 2, 2, "Game");
					stand(5, start_y + 4, 10, "Exit");
				}
			}
		}
		else if (k == 72) // если нажали вверх
		{
			if (cur > 1)
			{
				cur--;
				if (cur == 2)
				{
					stand(5, start_y + 2, 10, "Game");
					stand(5, start_y + 4, 2, "Exit");
				}
				else if (cur == 1)
				{
					stand(5, start_y, 10, "Help");
					stand(5, start_y + 2, 2, "Game");
				}
			}
		}
		else if (k == 13) // если нажали на энтер - выбираем пункт меню!
		{
			system("cls");
			SetConsoleTextAttribute(h, 12);
			if (cur == 1)
				help();
			else if (cur == 2)
				game();
			else if (cur == 3)
				the_end();
			
			exit(0);
		}
	}
}