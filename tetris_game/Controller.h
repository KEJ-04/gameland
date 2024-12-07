#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>

#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

enum boardProperty {
	BoardWidth = 14,
	BoardHeight = 22,
	BoardX = 4,
	BoardY = 3
};

enum Keys {
	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80,
	ARROW = 224,
	SPACEBAR = 32
};

typedef enum gameSpeed {
	easy = 230,
	normal = 170,
	hard = 150
}SPEED;

enum blockProperty {
	BlockSIZE = 4,
	BlockRotate = 4,
	BlockType = 7,
	BlockStartX = 14,
	BlockStartY = 4
};

int nkey;

short curShape;
void CurrentShape();
extern int nexShape;
void NextShape();
short BlockCOL;
short BlockROW;
short prevBlockCOL;
short prevBlockROW;
COORD Cursor;
void deletePrevBlock();
int static score;
void printScore();
short gameLevel;
void newBlock();

boolean IsNextBlock;
short turn;
void RotateBlock();

boolean IsCollision(int shape, int rotate, int curX, int curY);
void blockFixed(int shape, int rotate);

boolean IsMaxLine();
void deleteLine();
boolean IsOverHeight();

COORD previewPoint;
void previewBlock(int shape, int rotate);
void GameProcess();