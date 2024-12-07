#pragma once
#include "Blocks.h"
#include "Controller.h"

//»ö»ó
typedef enum Color {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VIOLET,
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
}COLOR;

int static level;

void InGameFrame();
void ShowNextBlock();
void DeleteNextBlock();

int NextBlock[6][6];
int static Rotation = 0;

void EndGameFrame();
void GameTitle();
void addBlock(int shape, int rotate);
void deleteBlock();

void createBoards();
int board[BoardHeight][BoardWidth];
void printBoards();
void textcolor(int color_number);