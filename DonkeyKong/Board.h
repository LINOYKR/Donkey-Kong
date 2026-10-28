#pragma once
#include <cstring>
#include <iostream>
#include <string>
#include <windows.h>

#include "Point.h"
class Board
{

public:
	struct GhostData {
		Point position;
		char type; // 'x' for BasicGhost, 'X' for ClimbingGhost
	};

private:
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	static constexpr int GHOSTS = 5;


	char originalBoard[MAX_Y][MAX_X + 1];
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
	//Saving locations
	Point marioStartPos{ 0,0 };
	Point barrelStartPosLeft{ 0,0 };
	Point barrelStartPosRight{ 0,0 };
	Point legendPos{ 0,0 };
	Point donkeyPos{ 0,0 };
	Point paulinaPos{ 0,0 };
	Point hammerPos;
	Point h;
	GhostData posGhost[GHOSTS];
	int legendPosX = 0;
	int legendPosY = 0;
	int countGhost = 0;

	std::string errorMessage = "Error: No level files found.";

	bool hammerEx = false;
	bool invalidboard = false;
	bool useColorsBoard = true;

	bool checkMarioFloor();// Check if current position under Mario is ground
	bool checkPaulineFloor();// Check if Pauline is on the floor
	void checkGhostsFloor();// Check if ghosts are only below the ground
	bool checkCharacters(bool marioFound, bool donkeyKongFound, bool paulineFound);//Checks for characters
	void CompletingLines(int curr_row, int curr_col);//Completes rows that end before the maximum
	bool isValidChar(char c);//Checks for unacceptable characters

public:

	void setTextColors(int color) const;

	//Returns positions of elements in a panel
	const Point getMarioStartPos() const { return marioStartPos; }
	const Point getbarrelStartPosLeft() const { return  barrelStartPosLeft; }
	const Point getbarrelStartPosRight() const { return barrelStartPosRight; }
	const Point getLegendPos() const { return legendPos; }
	const GhostData* getGhostPositions() const { return posGhost; }
	Point getHammerPosition() const { return hammerPos; }
	const int getLegendPosX() const { return legendPosX; }
	const int getLegendPosY() const { return legendPosY; }
	int numberGhosts() const { return countGhost; }
	bool isHammerAvailable() const { return hammerEx; }

	char getChar(int x, int y) const { return currentBoard[y][x]; }//gets the char on the board according to its location


	void resetGhostCount() { countGhost = 0; }//reset to zero number of spirits
	void resetHammer() { hammerEx = false; }//reset hammer

	const bool getInvalidbord() const { return invalidboard; }//If that invalid board
	const std::string getErrorMessage() const { return errorMessage; }//Invalid board message

	//Loading a game board
	void load(const std::string& filename, const bool colors);

	//resets bord
	void reset();

	//prints bord
	void print() const;

	//Checking a location for a timer
	bool checkTopRightFree();

};


