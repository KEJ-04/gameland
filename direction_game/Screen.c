#include "Screen.h"
#include <stdlib.h>

//화면 지우기
void clearScreen() {
	system("cls");
}

//겜시작화면
void showStartScreen() {
	printf("게임 시작 : A\n");
	printf("게임 설명 : B\n");
	printf("종료 : Q\n");
}