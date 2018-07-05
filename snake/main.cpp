#include <iostream>
#include <conio.h>

using std::cin;
using std::cout;
using std::endl;

typedef const int cint;

class SnakeGame {
private:
	bool gameOver = false;

	cint width  = 20;
	cint height = 20;

	int snakeX = width  /  2 - 1;
	int snakeY = height /  2 - 1;
	int appleX = rand() %  width;
	int appleY = rand() % height;

	int trailX[100], trailY[100],
		score				 = 0, 
		trailCounter		 = 0;

	enum eMovements { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eMovements eMov = STOP;

public:	
	bool getGameOver() { return gameOver; }

	void drawGrid() {
		system("cls");

		for (int i = 0; i < width + 1; i++)
			cout << '#';
		cout << endl;

		for (int i = 0; i < height; i++) {
			for (int j= 0; j < width; j++) {
				if (j == 0 || j == width - 1)
					cout << '#';
				if (i == snakeY && j == snakeX)
					cout << '0';
				else if (i == appleY && j == appleX)
					cout << 'A';
				else {
					bool trailPrint = false;

					for (int k(0); k < trailCounter; k++) {
						if (trailX[k] == j && trailY[k] == i) {
							trailPrint = true;
							cout << 'o';
						}
					}

					if (!trailPrint)
						cout << ' ';
				}
			}
			cout << endl;
		}

		for (int i = 0; i < width + 1; i++)
			cout << '#';

		cout << endl;

		cout << "Score: " << score << endl;
	}
	void userInput() {
		cin.clear();

		if (_kbhit()) {
			switch (_getch()) {
				case 'a': 
					eMov = LEFT;		break;
				case 'd': 
					eMov = RIGHT;		break;
				case 'w': 
					eMov = UP;			break;
				case 's': 
					eMov = DOWN;		break;
				case 'x': 
					gameOver = true;	break;
			}
		}
	}
	void gameLogic() {
		int prevTX = trailX[0];
		int prevTY = trailY[0];
		int prev2X,		prev2Y;

		trailX[0] = snakeX;
		trailY[0] = snakeY;
		
		for (int i(1); i < trailCounter; i++) {
			prev2X = trailX[i];
			prev2Y = trailY[i];

			trailX[i] = prevTX;
			trailY[i] = prevTY;

			prevTX = prev2X;
			prevTY = prev2Y;
		}

		switch (eMov) {
			case LEFT:	
				snakeX--; break;
			case RIGHT: 
				snakeX++; break;
			case UP:	
				snakeY--; break;
			case DOWN:	
				snakeY++; break;
		}

		if (snakeX >= width - 1)
			snakeX = 0;
		else if (snakeX < 0)
			snakeX = width - 2;

		if (snakeY >= width)
			snakeY = 0;
		else if (snakeY < 0)
			snakeY = height - 1;
		
		for (int i = 0; i < trailCounter; i++)	
			if (trailX[i] == snakeX && trailY[i] == snakeY)
				gameOver = true;

		if (snakeX == appleX && snakeY == appleY) {
			appleX = rand() % width; 
			appleY = rand() % height;

			score++; 
			trailCounter++;
		}
	}
};

int main() {
	SnakeGame SG;

	while (!SG.getGameOver()) {
		SG.drawGrid ();
		SG.userInput();
		SG.gameLogic();
	}
}