#include "Blocks.h"
#include "Controller.h"
#include "Screen.h"
#include "ConsoleCursor.h"

void main() {
	CursorView(false);
	system("mode con cols = 76  lines = 28 | title 창의실무프로젝트_테트리스 실습");

	while (true) {
		GameTitle();
		GameProcess();
	}
}