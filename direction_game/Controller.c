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

//�� �ʱ�ȭ
void initializeGame(GameState* gameState) {
	gameState->score = 0;
	gameState->life = 3;
	gameState->correctCount = 0;
}

//���̵� ����
void selectDifficulty(GameState* gameState) {
	clearScreen();
	//�ܼ� ũ�� ��������
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
		"���̵� ���� : ",
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

	//ȭ�� ��� ���
	int verticalStart = (rows - numLines) / 2;
	int horizontalStart = (columns - maxLineWidth) / 2;

	//���ٷ� ���� ���� �߰�
	for (int i = 0; i < verticalStart; i++) {
		printf("\n");
	}

	//�� �� ���
	for (int i = 0; i < numLines; i++) {
		printf("%s%s\n", horizontalStart, "", lines[i]);
	}

	//���̵� ���� �Է� ó��
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

//���� ���� ī��Ʈ�ٿ�
void countdown() {
	clearScreen();
	for (int i = 3; i > 0; i--) {
		printf("���� ���� %d\n", i);
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

	srand(time(0));	//�õ� �ʱ�ȭ
	int* directions = (int*)malloc(numKeys * sizeof(int));	//�����޸��Ҵ�
	for (int i = 0; i < numKeys; i++) {
		directions[i] = rand() % 4 + 1;	//1~4 ������ ���� ��
	}
	clearScreen();

	for (int i = 0; i < numKeys; i++) {
		switch (directions[i]) {
		case 1:
			printf("  ��");
			break;
		case 2:
			printf("  ��");
			break;
		case 3:
			printf("  ��");
			break;
		case 4:
			printf("  ��");
			break;
		}
	}

	printf("\n\n���ѽð� : %d��\n", timeLimit);
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
				printf("\n�߸��� ����Ű�� �������ϴ�!\n");
				break;
			}
		}
		if (correct == numKeys) {
			printf("\n���� ����\n");
			break;
		}
	}
	free(directions);	//�����޸�����
}

//Ű �Է� ó��
int getKeyInput() {
	if (_kbhit()) {
		int ch = _getch();
		if (ch == 224) {	//����Ű�� ���۵Ǵ� Ű �ڵ�
			ch = _getch();	//���� ����Ű �ڵ� �޾ƿ��°�
		}
		return ch;
	}
	return 0;
}

//���� ���� ó��
void gameOver(GameState* gameState) {
	clearScreen();
	printf("GAME OVER\n");
	printf("���� : %d\n", gameState->score);
	printf("������ ���� : %d\n", gameState->correctCount);
	printf("�ٽ� �ϱ� : R\n");
	printf("���� : Q\n");
}

//���� ���� �Լ�
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