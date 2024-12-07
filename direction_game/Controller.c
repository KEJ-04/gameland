#include "Controller.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>

typedef enum 
{
	COLOR_DEFAULT,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_YELLOW
}TextColor;

void setTextColor(TextColor color) {
	switch (color) {

	}
}

//겜 초기화
void initializeGame(GameState* gameState) {
	gameState->score = 0;
	gameState->life = 3;
	gameState->correctCount = 0;
}

//난이도 선택
void selectDifficulty(GameState* gameState) {
	clearScreen();
	//콘솔 크기 가져오기
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}
	else {
		columns = 80;
		rows = 25;
	}

	const char* lines[] = {
		"난이도 선택 : ",
		"1. EASY",
		"2. NORMAL",
		"3. HARD",
		"4. CHALLENGE"
	};
	int numLines = sizeof(lines) / sizeof(lines[0]);
	int maxLineWidth = 0;

	for (int i = 0; i < numLines; i++) {
		int lineWidth = srtlen(lines[i]);
		if (lineWidth > maxLineWidth) {
			maxLineWidth = lineWidth;
		}
	}

	//화면 가운데 계산
	int verticalStart = (rows - numLines) / 2;
	int horizontalStart = (columns - maxLineWidth) / 2;

	//빈줄로 위쪽 여백 추가
	for (int i = 0; i < verticalStart; i++) {
		printf("\n");
	}

	//각 줄 출력
	for (int i = 0; i < numLines; i++) {
		printf("%s%s\n", horizontalStart, "", lines[i]);
	}

	//난이도 선택 입력 처리
	int choice = 0;
	while (1) {
		choice = getKeyInput();
		if (choice == '1') {
			gameState->difficulty = EASY;
			break;
		}
		else if (choice == '2') {
			gameState->difficulty = NORMAL;
			break;
		}
		else if (choice == '3') {
			gameState->difficulty = HARD;
			break;
		}
		else if (choice == '4') {
			gameState->difficulty = CHALLENGE;
			break;
		}
	}
}

//게임 시작 카운트다운
void countdown() {
	clearScreen();
	for (int i = 3; i > 0; i--) {
		printf("게임 시작 %d\n", i);
		Sleep(1000);
	}
	clearScreen();
}

void showDirectionKeys(int difficulty) {
	int numKeys = 0;
	int timeLimit = 0;

	if (difficulty == EASY) {
		numKeys = 6;
		timeLimit = 15;
	}
	else if (difficulty == NORMAL) {
		numKeys = 8;
		timeLimit = 10;
	}
	else if (difficulty == HARD) {
		numKeys = 10;
		timeLimit = 7;
	}
	else if (difficulty == CHALLENGE) {
		numKeys = 10;
		timeLimit = 5;
	}

	srand(time(0));	//시드 초기화
	int* directions = (int*)malloc(numKeys * sizeof(int));	//동적메모리할당
	for (int i = 0; i < numKeys; i++) {
		directions[i] = rand() % 4 + 1;	//1~4 사이의 랜덤 값
	}
	clearScreen();

	for (int i = 0; i < numKeys; i++) {
		switch (directions[i]) {
		case 1:
			printf("  ▲");
			break;
		case 2:
			printf("  ▼");
			break;
		case 3:
			printf("  ◀");
			break;
		case 4:
			printf("  ▶");
			break;
		}
	}

	printf("\n\n제한시간 : %d초\n", timeLimit);
	int correct = 0;
	time_t startTime = time(NULL);
	while (1) {
		if (difftime(time(NULL), startTime) > timeLimit) {
			printf("\nTIEM OVER\n");
			break;
		}

		int input = getKeyInput();
		if (input == KEY_UP || input == KEY_DOWN || input == KEY_LEFT || input == KEY_RIGHT) {
			int directionPressed = 0;
			if (input == KEY_UP)
				directionPressed = 1;
			if (input == KEY_DOWN)
				directionPressed = 2;
			if (input == KEY_LEFT)
				directionPressed = 3;
			if (input == KEY_RIGHT)
				directionPressed = 4;

			if (correct < numKeys && directions[correct] == directionPressed) {
				correct++;
			}
			else
			{
				printf("\n잘못된 방향키를 눌렀습니다!\n");
				break;
			}
		}
		if (correct == numKeys) {
			printf("\n게임 성공\n");
			break;
		}
	}
	free(directions);	//동적메모리해제
}

//키 입력 처리
int getKeyInput() {
	if (_kbhit()) {
		int ch = _getch();
		if (ch == 224) {	//방향키가 시작되는 키 코드
			ch = _getch();	//실제 방향키 코드 받아오는거
		}
		return ch;
	}
	return 0;
}

//게임 오버 처리
void gameOver(GameState* gameState) {
	clearScreen();
	printf("GAME OVER\n");
	printf("점수 : %d\n", gameState->score);
	printf("성공한 개수 : %d\n", gameState->correctCount);
	printf("다시 하기 : R\n");
	printf("종료 : Q\n");
}

//게임 시작 함수
void startGame(GameState* gameState) {
	countdown();
	while (gameState->life > 0) {
		showDirectionKeys(gameState->difficulty);
		if (gameState->life == 0) {
			gameOver(gameState);
			break;
		}
	}
}