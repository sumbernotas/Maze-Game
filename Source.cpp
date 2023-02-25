#include <iostream>
#include <string>
#include <time.h>
#include <conio.h>

using namespace std;

void DisplayInstructions();
void DrawMap(char* pHeightTimesWidth);
int GetIndexAtCoordinates(int x, int y, int width);
void DrawToScreen(char* pHeightTimesWidth);
void DrawPlayer(char* pHeightTimesWidth, int x, int y);
void DrawExit(char* pHeightTimesWidth, int x, int y);

constexpr int kMapWidth = 27;
constexpr int kMapHeight = 15;

char g_gameMap[]{ '.', '.', '#', '#','#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#','#', '#', '#', '#', '#','#', '#', '#', '#', '#',
				'#', '.', '#', '.','#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#','#', '#', '#', '#', '#','#', '#', '#', '#', '#',
				'#', '.', '#', '.','.', '#', '#', '#', '.', '.', '.', '.','.', '#', '#', '#', '#','#', '#', '#', '#', '#','#', '#', '#', '#', '#',
				'#', '.', '.', '.','#', '#', '.', '.', '.', '#', '#', '#','.', '#', '#', '#', '#','.', '.', '.', '#', '#','.', '.', '.', '#', '#',
				'#', '.', '#', '.','#', '#', '.', '#', '.', '#', '#', '#','.', '#', '#', '#', '#','.', '#', '.', '#', '#','.', '#', '.', '.', '#',
				'#', '.', '#', '.','.', '.', '.', '#', '.', '#', '#', '#','.', '#', '#', '#', '#','.', '#', '.', '.', '.','.', '#', '.', '.', '#',
				'#', '.', '#', '#','#', '#', '#', '#', '.', '#', '#', '.','.', '.', '.', '#', '#','.', '#', '.', '#', '#','#', '#', '.', '#', '#',
				'#', '.', '#', '#','#', '#', '#', '#', '.', '#', '.', '.','#', '#', '.', '#', '#','.', '#', '.', '#', '#','#', '#', '.', '#', '#',
				'#', '.', '#', '#','.', '.', '.', '.', '.', '#', '.', '#','#', '#', '.', '#', '#','.', '#', '.', '#', '#','#', '#', '#', '#', '#',
				'#', '.', '.', '.','.', '#', '#', '#', '#', '#', '.', '#','#', '#', '.', '#', '#','.', '#', '.', '#', '#','#', '#', '#', '#', '#',
				'#', '#', '.', '#','#', '#', '#', '#', '#', '#', '.', '#','#', '#', '.', '.', '.','.', '#', '.', '#', '#','#', '#', '#', '#', '#',
				'#', '#', '.', '#','#', '#', '#', '#', '#', '#', '.', '#','#', '#', '#', '#', '#','#', '#', '.', '#', '#','.', '.', '.', '#', '#',
				'#', '#', '.', '.','.', '.', '.', '.', '.', '.', '.', '#','#', '#', '.', '.', '.','.', '.', '.', '#', '#','.', '#', '#', '#', '#',
				'#', '#', '#', '#','#', '#', '#', '#', '#', '.', '.', '#','#', '#', '.', '#', '#','#', '#', '.', '.', '.','.', '#', '#', '#', '#',
				'#', '#', '#', '#','#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#','#', '#', '#', '#', '#','#', '#', '#', '#', '#' };

int main()
{
	char* pHeightTimesWidth = new char[kMapWidth * kMapHeight];
	int playerX = 0;     // player position stored in X and Y
	int playerY = 0;
	int exitX = 24;     // exit position stored in X and Y
	int exitY = 12;

	while (true)      //  game loop, while the console is running, this will loop until told otherwise
	{
		system("cls");

		DrawMap(pHeightTimesWidth);
		DrawExit(pHeightTimesWidth, exitX, exitY);                                   //// these functions will first draw the map (into the background)
		DrawPlayer(pHeightTimesWidth, playerX, playerY);                             //// then place the exit and then place the player where it's current position has been calculated
		DrawToScreen(pHeightTimesWidth);                                             //// this will then hold all of that information (of exit & player) and print it onto the console

		int index = GetIndexAtCoordinates(playerX, playerY, kMapWidth);
		char wall = g_gameMap[index];
		char input = _getch();            // takes in players input and holds it in the background (without pressing enter)

		if (_getch() == 'q')
		{
			break;                        // will quit the game when 'q' is pressed
		}

		switch (input)                     
		{                                    // the switch statements will take in the players input (using WASD)
		case 'a':                        // and will determine how the players position will change if the player wants to go up, down, left, or right

			if (wall == '#')
			{
				playerX = 0;
				playerY = 0;
				break;
			}
			else
			{
				--playerX;
			}

			break;
		case 'd':

			if (wall == '#')
			{
				playerX = 0;
				playerY = 0;
				break;
			}
			else
			{
				++playerX;
			}

			break;
		case 'w':

			if (wall == '#')
			{
				playerX = 0;
				playerY = 0;
				break;
			}
			else
			{
				--playerY;
			}

			break;
		case 's':

			if (wall == '#')
			{
				playerX = 0;
				playerY = 0;
				break;
			}
			else
			{
				++playerY;
			}

			break;
		}

		if (playerX == exitX && playerY == exitY)               // if the player reaches the 'X', they win the maze and the game quits
		{
			system("cls");
			cout << "You escaped the maze!!" << endl;
			break;
		}
	}

	return 0;
}

/////////////////////////////////////////
//// This generates the x and y postions on the array 
/////////////////////////////////////////
int GetIndexAtCoordinates(int x, int y, int width)
{
	return x + y * width;
}

/////////////////////////////////////////
//// This function builds the map array into the background of the console, it creates a 15 x 27 grid
/////////////////////////////////////////
void DrawMap(char* pHeightTimesWidth)
{
	for (int y = 0; y < kMapHeight; ++y)
	{
		for (int x = 0; x < kMapWidth; ++x)
		{
			int index = GetIndexAtCoordinates(x, y, kMapWidth);
			pHeightTimesWidth[index] = g_gameMap[index];
		}
	}
}

/////////////////////////////////////////
//// this takes in the width and height (multiplied), and actually prints the map onto the screen,
//// with the same grid as above, this is so that every time the player moves, it will output that move
/////////////////////////////////////////
void DrawToScreen(char* pHeightTimesWidth)
{
	for (int y = 0; y < kMapHeight; ++y)
	{
		for (int x = 0; x < kMapWidth; ++x)
		{
			int index = GetIndexAtCoordinates(x, y, kMapWidth);
			cout << pHeightTimesWidth[index];
		}
		cout << endl;
	}
}

/////////////////////////////////////////
//// This function sets the position of the player
/////////////////////////////////////////
void DrawPlayer(char* pHeightTimesWidth, int x, int y)
{
	int index = GetIndexAtCoordinates(x, y, kMapWidth);
	pHeightTimesWidth[index] = '@';
}

/////////////////////////////////////////
//// this function sets the position of the maps exit 
/////////////////////////////////////////
void DrawExit(char* pHeightTimesWidth, int x, int y)
{
	int index = GetIndexAtCoordinates(x, y, kMapWidth);
	pHeightTimesWidth[index] = 'X';
}