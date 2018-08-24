#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>

/*void CelsiusToFahrenheit() {
	float celsius = 78;
	float Fahrenheit = celsius * 9/5 + 32;
	std::cout << "---------- Celsius to Fahrenheit -------------\n";
	std::cout << "Celsius: " << celsius << "\n";
	std::cout << "Fahrenheit: " << Fahrenheit << "\n";
	return;
}
void AreaOfRectangle() {
	float retWidth = 0.0f;
	float rectHeight = 0.0f;
	float rectArea = 0.0f;



}
*/
char playerTurn = 'X';
void GoToXY(int column, int line)
{
	// Create a COORD structure and fill in its members.
	// This specifies the new position of the cursor that we will set.
	COORD coord;
	coord.X = column;
	coord.Y = line;

	// Obtain a handle to the console screen buffer.
	// (You're just using the standard console, so you can use STD_OUTPUT_HANDLE
	// in conjunction with the GetStdHandle() to retrieve the handle.)
	// Note that because it is a standard handle, we don't need to close it.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Finally, call the SetConsoleCursorPosition function.
	if (!SetConsoleCursorPosition(hConsole, coord)){ //TODO handel error
		// Uh-oh! The function call failed, so you need to handle the error.
		// You can call GetLastError() to get a more specific error code.
		// ...
	}
}
void endGame(int con) { //con = 0 = tie, con = 1 = current player wins;
	GoToXY(0, 1);
	switch (con) {
	case 0:
		std::cout << "GAME OVER: CATS GAME                              ";
		break;
	case 1:
		std::cout << "GAME OVER: " << playerTurn << " WINS                                 ";
		break;
	}
}
bool rowCheck(int row, char board[3][3]) {
	if (board[row][1] != ' ' &&
		(board[row][0] == board[row][1] && board[row][0] == board[row][2])) {
		return true;
	}
	return false;
}
bool collumCheck(int col, char board[3][3]) {
	if (board[0][col] != ' ' &&
		(board[0][col] == board[1][col] && board[0][col] == board[2][col])) {
		return true;
	}
	return false;
}
bool centerCheck(char board[3][3]) {
	if (board[1][1] != ' ' &&
		(board[1][1] == board[0][0] && board[1][1] == board[2][2]
			||
			board[1][1] == board[0][2] && board[1][1] == board[2][0])) {
		return true;
	}
	return false;
}
bool checkGame(char board[3][3], int x, int y) { //returns true when game is over
	if (x + y == 1 || x + y == 3) { //edge
		if (rowCheck(x, board)) { endGame(1); return true; }
		if (collumCheck(y, board)) { endGame(1); return true; }
		return false;
	}
	// middle && corners
	if (rowCheck(x, board))    { endGame(1); return true; }
	if (collumCheck(y, board)) { endGame(1); return true; }
	if (centerCheck(board))    { endGame(1); return true; }
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
				return false;
			}
		}
	}
	endGame(0);
	return true;
}

bool turn(int x, int y, char board[3][3]) {
	if (board[x][y] != ' ') { return false; }
	board[x][y] = playerTurn;
	if (checkGame(board, x, y)) return true;
	if (playerTurn == 'X') {
		playerTurn = 'O';
	} else {
		playerTurn = 'X';
	}
	return false;
}

bool update(char board[3][3], int &x, int &y, bool &keyA, bool &keyS, bool &keyD, bool &keyW)
{
	bool gameRunning = true;
	bool isAnyKey = false;
	int tempX = x;
	int tempY = y;
	if ((GetKeyState('A') & 0x8000) && !keyA) { keyA = true; x--; isAnyKey = true; }
	if ((GetKeyState('S') & 0x8000) && !keyS) { keyS = true; y++; isAnyKey = true; }
	if ((GetKeyState('D') & 0x8000) && !keyD) { keyD = true; x++; isAnyKey = true; }
	if ((GetKeyState('W') & 0x8000) && !keyW) { keyW = true; y--; isAnyKey = true; }

	if (isAnyKey) {
		GoToXY(tempX * 3, tempY + 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
		std::cout << "[" << board[tempX][tempY] << "]";
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!(GetKeyState('A') & 0x8000)) { keyA = false; }
	if (!(GetKeyState('S') & 0x8000)) { keyS = false; }
	if (!(GetKeyState('D') & 0x8000)) { keyD = false; }
	if (!(GetKeyState('W') & 0x8000)) { keyW = false; }

	if (GetKeyState('\x1B') & 0x8000) { return false; } //ESC

	if (GetKeyState('\x0D') & 0x8000) if (turn(x, y, board)) { gameRunning = false; }; //Enter

	if (x > 2) { x = 0;	}
	if (x < 0) { x = 2;	}
	if (y > 2) { y = 0;	}
	if (y < 0) { y = 2;	}
	GoToXY(x*3, y+2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x70);
	
	std::cout << "[" << board[x][y] << "]\b\b\b";

	return gameRunning;
}

int main() {
	/*while(true){
		std::cout << ">";
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		std::cout << "\b";
		std::cout << " ";
		std::cout << "\b";
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
	//14
	int numberA = 5;

	numberA = 9;
	numberA = 11;
	numberA = 14;

	std::cout << "A) " << numberA << std::endl;
	/*int a = 57;
	int b = 22;
	std::cout << "a: " << a << "\n";
	std::cout << "b: " << b << "\n";
	std::cout << "swap\n";
	std::tie(b, a) = std::make_tuple(a, b);
	std::cout << "a: " << a << "\n";
	std::cout << "b: " << b << "\n";*/
	int x = 0;
	int y = 0;
	char board[3][3] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };
	std::cout <<
		"This is Tic Tak Toe\n"
		"Current Turn: ";
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);
	int turnScreenPosX = cbsi.dwCursorPosition.X;
	int turnScreenPosY = cbsi.dwCursorPosition.Y;
	std::cout << "X";
	std::cout << "\n[ ][ ][ ]\n[ ][ ][ ]\n[ ][ ][ ]\n";
	bool keyA, keyS, keyD, keyW;
	keyA = keyS = keyD = keyW = false;
	while (update(board, x, y, keyA, keyS, keyD, keyW)) {
		if (playerTurn == 'X') {
			GoToXY(turnScreenPosX, turnScreenPosY);
			std::cout << "X";
		} else {
			GoToXY(turnScreenPosX, turnScreenPosY);
			std::cout << "O";
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
	}
	while (!(GetKeyState('\x1B') & 0x8000))std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
	return 0;

}