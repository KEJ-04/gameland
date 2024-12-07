#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Screen.h"

//방향키 정의
#define KEY_UP 22
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//난이도 상수
#define EASY 1
#define NORMAL 2
#define HARD 3
#define CHALLENGE 4

//게임 상태를 위한 구조체
typedef struct 
{
	int score;	//점수
	int life;	//라이프
	int difficulty;	//난이도
	int correctCount;	//성공한 방향키 수
}GameState;

void initializeGame(GameState* gameState);	//겜 초기화
void selectDifficulty(GameState* gameState);	//난이도 선택
void startGame(GameState* gameState);	//겜 시작
void showDirectionKeys(int difficulty);	//방향키 출력 및 입력 확인
int getKeyInput();
void gameOver(GameState* gameState);	//겜오버 처리
void countdown();	//겜시작 카운트다운

#endif