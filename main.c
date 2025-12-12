#include "snake.h"
int main() {
	SetConsoleOutputCP(65001);
	HideCursor();
	StartGame();
	RunGame();
	EndGame();
	return 0;
}
void Welcome() {
	SetConsoleTitle(L"Snake Game");
	system("mode con cols=100 lines=30");
	SetCursorPosition(40, 8);
	printf("WELCOME TO SNAKE GAME!\n");
	SetCursorPosition(38, 10);
	printf("Press any key to start the game...\n");
	SetCursorPosition(42, 12);
	printf("Powered by nullptr\n");
	system("pause");
	system("cls");
}
void StartGame() {
	Welcome();
	CreateMap();
	InitSnake();
	CreateFood();
}
void CreateMap() {
	for (int i = 0; i < 58; i += 2) {
		SetCursorPosition(i, 0);
		printf("\xF0\x9F\xA4\xA3");
		SetCursorPosition(i, 26);
		printf("\xF0\x9F\xA4\xA3");
	}
	for (int i = 0; i < 26; i++) {
		SetCursorPosition(0, i);
		printf("\xF0\x9F\xA4\xA3");
		SetCursorPosition(56, i);
		printf("\xF0\x9F\xA4\xA3");
	}
	for (int i = 2; i < 58; i += 2) {
		SetCursorPosition(i, 26);
		printf("\xF0\x9F\xA4\xA3");
	}
	SetCursorPosition(60, 8);
	printf("Score:%d", g_score);
	SetCursorPosition(60, 10);
	printf("Speed:%d", g_speed);
	SetCursorPosition(60, 12);
	printf("Note: Snakes cannot pass through walls or bite themselves");
	SetCursorPosition(60, 14);
	printf("Press \xE2\x86\x91 \xE2\x86\x93 \xE2\x86\x90 \xE2\x86\x92 to control the snake's movement");
	SetCursorPosition(60, 28);
}
void SetCursorPosition(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hConsole, pos);
}
void InitSnake() {
	g_pSnake = (Snake*)malloc(sizeof(Snake));
	g_pSnake->x = 20;
	g_pSnake->y = 13;
	g_pSnake->next = NULL;
	for (int i = 1; i <= 3; ++i) {
		Snake* p = (Snake*)malloc(sizeof(Snake));
		p->x = 20 + 2 * i;
		p->y = 13;
		p->next = NULL;
		p->next = g_pSnake;
		g_pSnake = p;
	}
	Snake* temp = g_pSnake;
	while (temp) {

		SetCursorPosition(temp->x, temp->y);
		printf("\xF0\x9F\x90\x8D");
		temp = temp->next;
	}
	SetCursorPosition(60, 28);
}
void RunGame() {
	char ch = 77;
	while (1) {
		if (_kbhit()) {
			_getch();
			ch = _getch();
		}

		MoveSnake(ch);
		if (isDie() == 1) {
			SetCursorPosition(60, 28);
			break;
		}
		EatFood();
		Sleep(310 - g_speed);
	}
}
void MoveSnake(char direction) {
	Snake* head = malloc(sizeof(Snake));
	switch (direction)
	{
	case 72:
		head->x = g_pSnake->x;
		head->y = g_pSnake->y - 1;
		break;
	case 80:
		head->x = g_pSnake->x;
		head->y = g_pSnake->y + 1;
		break;
	case 75:
		head->x = g_pSnake->x - 2;
		head->y = g_pSnake->y;
		break;
	case 77:
		head->x = g_pSnake->x + 2;
		head->y = g_pSnake->y;
		break;
	}
	head->next = g_pSnake;
	g_pSnake = head;
	SetCursorPosition(g_pSnake->x, g_pSnake->y);
	printf("\xF0\x9F\x90\x8D");
	if (g_pSnake == NULL || g_pSnake->next == NULL) return;
	Snake* p = g_pSnake;
	while (p->next->next && p->next) {
		p = p->next;
	}
	if (p->next) {
		SetCursorPosition(p->next->x, p->next->y);
		printf(" ");
		free(p->next);
		p->next = NULL;
	}
}
void CreateFood() {
	srand((unsigned int)time(NULL));
	while (1) {
		int n = rand() % 53 + 2;
		g_food.x = (n % 2) ? n - 1 : n;
		g_food.y = rand() % 24 + 1;
		Snake* p = g_pSnake;
		while (p) {
			if (g_food.x == p->x && g_food.y == p->y) break;
			p = p->next;
		}
		if (p == NULL) break;

	}
	SetCursorPosition(g_food.x, g_food.y);
	printf("\xF0\x9F\xA5\xA0");
}
void EatFood() {
	if (g_food.x == g_pSnake->x && g_food.y == g_pSnake->y) {
		Snake* snake = (Snake*)malloc(sizeof(Snake));
		snake->x = g_food.x;
		snake->y = g_food.y;
		snake->next = g_pSnake;
		g_pSnake = snake;
		g_score += 10;
		g_speed += 10;
		if (g_speed >= 210) g_speed = 210;
		SetCursorPosition(60, 8);
		printf("Score:%05d", g_score);
		SetCursorPosition(60, 10);
		printf("Speed:%05d", g_speed);
		CreateFood();
	}
}
int isDie() {
	if (g_pSnake->x <= 0 || g_pSnake->x >= 56 || g_pSnake->y <= 0 || g_pSnake->y >= 25) return 1;
	Snake* p = g_pSnake->next;
	while (p) {
		if (p->x == g_pSnake->x && p->y == g_pSnake->y) return 1;
		p = p->next;
	}
	return 0;
}
void EndGame() {
	SetCursorPosition(20, 13);
	printf("GAME OVER! YOUR SCORE IS %d\n", g_score);
	SetCursorPosition(60, 28);
	system("pause");
}
void HideCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hConsole, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cci);
}