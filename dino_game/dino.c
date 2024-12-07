﻿#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define DINO_BOTTOM_Y 17
#define CACTUS_BOTTOM_Y 25
#define CACTUS_BOTTOM_X 45

void ClearDino(int dinoY);
void ClearCactus(int cactusX);

void CursorView(char show);
void SetColor(unsigned short text);
void SetConsoleView();
void DrawDino(int dinoY);
void GotoXY(int x, int y);
void DrawCactus(int cactusX);
int IsCollision(const int cactusX, const int dinoY);
int GetKeyDown();
void DrawGameOver(const int score);

//색상
enum {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VOILET,
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};

int main() {
	SetConsoleView();
	while (true) {
		int isJumping = false;
		int isBottom = true;
		const int gravity = 3;

		int dinoY = DINO_BOTTOM_Y;
		int cactusX = CACTUS_BOTTOM_X;

		int score = 0;
		clock_t start, curr;
		start = clock();

		while (true) {
			if (IsCollision(cactusX, dinoY))
				break;
			
			if (GetKeyDown() == ' ' && isBottom) {
				isJumping = true;
				isBottom = false;
			}

			if (isJumping)	dinoY -= gravity;
			else dinoY += gravity;

			if (dinoY >= DINO_BOTTOM_Y) {
				dinoY = DINO_BOTTOM_Y;
				isBottom = true;
			}

			if (dinoY <= 3)	isJumping = false;

			cactusX -= 2;
			if (cactusX <= 0)	cactusX = CACTUS_BOTTOM_X;

			DrawDino(dinoY);
			DrawCactus(cactusX);

			curr = clock();
			if (((curr - start) / CLOCKS_PER_SEC) >= 1) {
				score++;
				start = clock();
			}

			Sleep(60);
			ClearDino(dinoY);
			ClearCactus(cactusX);

			SetColor(WHITE);
			GotoXY(22, 0);	printf("Score : %d", score);
			GotoXY(20, 2);	printf("점프 : Space Key");
		}
		DrawGameOver(score);
	}
}

void SetColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void GotoXY(int x, int y) {
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKeyDown() {
	if (_kbhit() != 0)	return _getch();
	return false;
}

int IsCollision(const int cactusX, const int dinoY) {
	GotoXY(0, 0);
	printf("cactusX : %2d, dinoY : %2d", cactusX, dinoY);
	if (cactusX <= 8 && cactusX >= 2 && dinoY > 12)	return true;
	return false;
}

//선인장
void DrawCactus(int cactusX) {
	SetColor(GREEN);
	GotoXY(cactusX, CACTUS_BOTTOM_Y);
	printf("  $");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 1);
	printf("$ $  ");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 2);
	printf("$ $ $");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 3);
	printf("$$$$$");
	GotoXY(cactusX, CACTUS_BOTTOM_Y + 4);
	printf("  $  ");
}

//공룡
void DrawDino(int dinoY) {
	SetColor(SKYBLUE);
	GotoXY(0, dinoY);
	static int legFlag = true;
	printf("        $$$$$$$ \n");		// 8, 7, 1
	printf("       $$ $$$$$$\n");		// 7, 2, 1, 6
	printf("       $$$$$$$$$\n");		// 7, 9
	printf("$      $$$      \n");		// 1, 6, 3, 6
	printf("$$     $$$$$$$  \n");		// 2, 5, 7, 2
	printf("$$$   $$$$$     \n");		// 3, 3, 5, 5
	printf(" $$  $$$$$$$$$$ \n");		// 1, 2, 2, 10, 1
	printf(" $$");									// 1, 2
	SetColor(BLUE);
	printf("원광대");
	SetColor(SKYBLUE);
	printf("$$$    \n");						// 3, 4
	printf("  $$$");								// 2, 3
	SetColor(RED);
	printf("컴소공");
	SetColor(SKYBLUE);
	printf("$    \n");							// 1, 4
	printf("    $$$$$$$$    \n");		// 4, 8, 4
	printf("     $$$$$$     \n");		// 5, 6, 5
	//다리 움직이는거 출력
	if (legFlag) {
		printf("     $    $$$   \n");		// 5, 1, 4, 3, 3
		printf("     $$         ");			// 5, 2, 9
		legFlag = false;
	}
	else
	{
		printf("     $$$  $     \n");
		printf("          $$    ");
		legFlag = true;
	}
}

void CursorView(char show) {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), & ConsoleCursor);
}

//콘솔창 이름 보이기
void SetConsoleView() {
	system("mode con:cols = 120  lines = 30");
	system("title 창의실무프로젝트 구글 공룡 게임 [By. 교수님]");
	CursorView(false);
}

//게임오버화면
void DrawGameOver(const int score) {
	system("cls");	SetColor(YELLOW);
	int x = 22, y = 8;
	GotoXY(x, y);

	printf("============================");
	GotoXY(x, y + 1);
	printf("======G A M E O V E R=======");
	GotoXY(x, y + 2);
	printf("============================");
	GotoXY(x, y + 5);
	printf("SCORE : %d", score);
	
	printf("\n\n\n\n\n\n\n\n\n");
	system("pause");
	system("cls");
}

void ClearDino(int dinoY) {
	GotoXY(0, dinoY);
	for (int i = 0; i < 12; i++)	printf("                \n");
	printf("                ");
}

void ClearCactus(int cactusX) {
	for (int i = 0; i < 5; i++) {
		GotoXY(cactusX, CACTUS_BOTTOM_Y + i);
		printf("     ");
	}
}