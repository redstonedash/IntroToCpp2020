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
	if (!SetConsoleCursorPosition(hConsole, coord))
	{
		// Uh-oh! The function call failed, so you need to handle the error.
		// You can call GetLastError() to get a more specific error code.
		// ...
	}
}
void endGame() {

}
void turn(char &winner, int x, int y, int board[3][3]) {

}
bool update(int board[3][3], int &x, int &y, bool &keyA, bool &keyS, bool &keyD, bool &keyW)
{

	std::cout << "\b \b";
	if ((GetKeyState('A') & 0x8000) && !keyA) { keyA = true; x--; }
	if ((GetKeyState('S') & 0x8000) && !keyA) { keyS = true; y++; }
	if ((GetKeyState('D') & 0x8000) && !keyA) { keyD = true; x++; }
	if ((GetKeyState('W') & 0x8000) && !keyA) { keyW = true; y--; }
/////////////////////////////////////////////////////////////////////////////
	if (!GetKeyState('A') & 0x8000) keyA = false;
	if (!GetKeyState('S') & 0x8000) keyS = false;
	if (!GetKeyState('D') & 0x8000) keyD = false;
	if (!GetKeyState('W') & 0x8000) keyW = false;
	if (GetKeyState('\x0D') & 0x8000) return false;
	if (GetKeyState('\x1B') & 0x8000) return false;
	GoToXY(x%3*3, y%3+2);
	std::cout << "#";
	return true;
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
	int board[3][3] = { 0,0,0,0,0,0,0,0,0 };
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
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
	}
	return 0;

}