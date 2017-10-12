#include "utils.h"
#include <windows.h>

//typedef unsigned short int usint;

void clearScreen()
{
	COORD upperLeftCorner = { 0, 0 };
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);
}


unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int  max)
{

	unsigned short int option;
	bool notready = true;
	
	do
	{
		if (cin >> option)
		{
			if (option >= min && option <= max)
			{
				notready = false; //desnecessario
				return option;
			}
			else {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\nFora do limite. Tente outra vez: ";
			}
		}
		else {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalido. Tente outra vez: ";
		}

	} while (notready);

}

unsigned int leInteiro(unsigned int min, unsigned int max)
{

	unsigned int option;
	bool notready = true;

	do
	{
		if (cin >> option)
		{
			if (option >= min && option <= max)
			{
				notready = false; //desnecessario
				return option;
			}
			else {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\nFora do limite. Tente outra vez: ";
			}
		}
		else {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalido. Tente outra vez: ";
		}

	} while (notready);

}

void startScreen()
{
	printf("	 __     __  ________  __    __  _______   ________                     \n");
	Sleep(100);
	printf("	|  \\   |  \\|        \\|  \\  |  \\|       \\ |        \\ __                 \n");
	Sleep(100);
	printf("	| $$   | $$| $$$$$$$$| $$\\ | $$| $$$$$$$\\| $$$$$$$$|  \\      |  \\      \n");
	Sleep(100);
	printf("	| $$   | $$| $$__    | $$$\\| $$| $$  | $$| $$__  __| $$__  __| $$__    \n");
	Sleep(100);
	printf("	 \\$$\\ /  $$| $$  \\   | $$$$\\ $$| $$  | $$| $$  \\|    $$  \\|    $$  \\   \n");
	Sleep(100);
	printf("	  \\$$\\  $$ | $$$$$   | $$\\$$ $$| $$  | $$| $$$$$ \\$$$$$$$$ \\$$$$$$$$   \n");
	Sleep(100);
	printf("	   \\$$ $$  | $$_____ | $$ \\$$$$| $$__/ $$| $$_____ | $$      | $$      \n");
	Sleep(100);
	printf("	    \\$$$   | $$     \\| $$  \\$$$| $$    $$| $$     \\ \\$$       \\$$      \n");
	Sleep(100);
	printf("	     \\$     \\$$$$$$$$ \\$$   \\$$ \\$$$$$$$  \\$$$$$$$$                    \n");
	Sleep(100);
	printf("	                 UM SUPERMERCARDO PERTO DE SI                          \n");
	Sleep(100);

	cout << TAB_BIG << "                                                      Joao Mendes" << endl;
	Sleep(200);
	cout << TAB_BIG << "                                                     Nuno Pereira" << endl;
	Sleep(200);

}