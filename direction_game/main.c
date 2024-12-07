#include "Controller.h"
#include "Screen.h"

int main() {
	GameState gameState;
	initializeGame(&gameState);

	showStartScreen();
	while (1) {
		int input = getKeyInput();
		if (input == 'A' || input == 'a') {
			//겜시작
			selectDifficulty(&gameState);
			startGame(&gameState);
		}
		else if (input == 'B' || input == 'b') {
			//겜설명
		}
		else if (input == 'Q' || input == 'q') {
			//겜종료
			break;
		}
	}
	return 0;
}