#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Screen.h"

//����Ű ����
#define KEY_UP 22
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//���̵� ���
#define EASY 1
#define NORMAL 2
#define HARD 3
#define CHALLENGE 4

//���� ���¸� ���� ����ü
typedef struct 
{
	int score;	//����
	int life;	//������
	int difficulty;	//���̵�
	int correctCount;	//������ ����Ű ��
}GameState;

void initializeGame(GameState* gameState);	//�� �ʱ�ȭ
void selectDifficulty(GameState* gameState);	//���̵� ����
void startGame(GameState* gameState);	//�� ����
void showDirectionKeys(int difficulty);	//����Ű ��� �� �Է� Ȯ��
int getKeyInput();
void gameOver(GameState* gameState);	//�׿��� ó��
void countdown();	//�׽��� ī��Ʈ�ٿ�

#endif