#include<fstream>

#include "Board.h"

#define _CRT_SECURE_NO_WARNINGS //to allow strcpy

//Colors
enum Colors {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	PURPLE = 5,
	YELLOW = 6,
	WHITE = 7,
	GRAY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_PURPLE = 13,
	LIGHT_YELLOW = 14,
	BRIGHT_WHITE = 15
};


// Check if current position under Mario is ground
bool Board::checkMarioFloor() {
	if (marioStartPos.getY() + 1 < MAX_Y && originalBoard[marioStartPos.getY() + 1][marioStartPos.getX()] == ' ') {
		errorMessage = "Mario must have floor beneath.";
		invalidboard = true;
		return true;
	}
	return false;
}

// Check if Pauline is on the floor
bool Board::checkPaulineFloor() {
	if (paulinaPos.getY() + 1 < MAX_Y && originalBoard[paulinaPos.getY() + 1][paulinaPos.getX()] == ' ') {
		errorMessage = "Pauline must have floor beneath.";
		invalidboard = true;
		return true;
	}
	return false;
}

// Ensure that ghosts are only below the ground
void Board::checkGhostsFloor() {
	for (int i = 0; i < countGhost; ++i) {
		int ghostX = posGhost[i].position.getX();
		int ghostY = posGhost[i].position.getY();

		if (ghostY + 1 >= MAX_Y || originalBoard[ghostY + 1][ghostX] == ' ') {
			errorMessage = "Ghost must have floor beneath.";
			invalidboard = true;
		}
	}
	return;
}

// Check the conditions after reading the entire file
bool Board::checkCharacters(bool marioFound, bool donkeyKongFound, bool paulineFound) {
	if (!marioFound || !donkeyKongFound || !paulineFound) {
		if (!marioFound) {
			errorMessage = "Missing Mario (@).";
		}
		else if (!donkeyKongFound) {
			errorMessage = "Missing Donkey Kong (&).";
		}
		else {
			errorMessage = "Missing Pauline ($).";
		}
		invalidboard = true;
		return true;
	}
	return false;
}

// Completing lines that don't have enough characters
void Board::CompletingLines(int curr_row, int curr_col) {
	for (int row = curr_row; row < MAX_Y; ++row) {
		for (int col = curr_col; col < MAX_X; ++col) {
			char& cell = this->originalBoard[row][col];
			if (cell != '=' && cell != '>' && cell != '<' && cell != 'Q') {
				cell = '=';
			}
		}
	}
}

// Function to check if the character is valid
bool Board::isValidChar(char c) {
	return c == '@' || c == '&' || c == 'P' || c == 'L' || c == '$' ||
		c == ' ' || c == '=' || c == '>' || c == '<' || c == 'Q' || c == 'H';
}

//Change text color
void Board::setTextColors(int color) const {
	if (useColorsBoard == true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

//Loading a game board
void Board::load(const std::string& filename, const bool colors)
{
	useColorsBoard = colors;
	std::ifstream screen_file(filename);
	//File opening test
	if (!screen_file.is_open()) {
		errorMessage = "Can't open the file.";
		invalidboard = true;
		return;
	}
	countGhost = 0;
	int curr_row = 0, curr_col = 0;
	char c;
	bool marioFound = false, donkeyKongFound = false, paulineFound = false, legendFound = false;

	while (!screen_file.get(c).eof() && curr_row < MAX_Y) {

		if (c == '\n') {
			if (curr_col < MAX_X)
			{
				//Dealing with a line that is too short
#pragma warning (suppress :4996)
				strcpy(originalBoard[curr_row] + curr_col, std::string(MAX_X - curr_col, ' ').c_str());
			}
			++curr_row;
			curr_col = 0;
			continue;
		}
		if (curr_col < MAX_X) {
			if (c == '@') {
				if (marioFound) {
					errorMessage = "Too many Mario characters (@).";
					invalidboard = true;
					return;
				}
				marioStartPos = Point(curr_col, curr_row);
				originalBoard[curr_row][curr_col++] = ' ';
				marioFound = true;
			}
			else if (c == 'x' || c == 'X') {
				if (countGhost < GHOSTS) {
					posGhost[countGhost] = { Point(curr_col, curr_row), c }; // Store type too
					originalBoard[curr_row][curr_col++] = ' ';
					countGhost++;
				}
				else {
					errorMessage = "Too many Ghost characters (x/X), allowed up to 5 in each level.";
					invalidboard = true;
				}
			}
			else if (c == 'p') {
				hammerPos = Point(curr_col, curr_row);
				hammerEx = true;
				originalBoard[curr_row][curr_col++] = ' ';
			}
			else if (c == 'L') {

				if (legendFound) {
					errorMessage = "Too many legend characters (L).";
					invalidboard = true;
					return;
				}
				legendPos = Point(curr_col, curr_row);
				legendPosX = curr_col;
				legendPosY = curr_row;
				originalBoard[curr_row][curr_col++] = ' ';
				legendFound = true;
			}
			else
			{
				if (c == '$') {
					if (paulineFound) {
						errorMessage = "Too many Pauline characters ($).";
						invalidboard = true;  // More than one Pauline
						return;
					}
					paulinaPos = Point(curr_col, curr_row);
					paulineFound = true;
				}
				else if (c == '&') {
					if (curr_col == 0) {
						barrelStartPosLeft = Point(curr_col - 1, curr_row);
					}
					else if (curr_col == MAX_X)
					{
						barrelStartPosRight = Point(curr_col + 1, curr_row);
					}
					barrelStartPosLeft = Point(curr_col - 1, curr_row);
					barrelStartPosRight = Point(curr_col + 1, curr_row);
					donkeyKongFound = true;
					donkeyPos = Point(curr_col, curr_row);
				}
				if (!isValidChar(c)) {
					if (curr_col < MAX_X) {
						errorMessage = "Invalid character found: " + std::string(1, c);
						invalidboard = true;
					}
					return;
				}
				originalBoard[curr_row][curr_col++] = c;
			}

		}
	}

	CompletingLines(curr_row, curr_col);

	if (checkCharacters(marioFound, donkeyKongFound, paulineFound)) {
		return;
	}
	else if (checkMarioFloor()) {
		return;
	}
	else if (checkPaulineFloor()) {
		return;
	}
	else {
		checkGhostsFloor();
	}

}

//resets the board
void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X);
	}

}

//prints board
void Board::print() const {

	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			if (donkeyPos.getX() == x && donkeyPos.getY() == y) {
				setTextColors(LIGHT_RED);
				std::cout << '&';
			}
			else if (paulinaPos.getX() == x && paulinaPos.getY() == y) {
				setTextColors(LIGHT_PURPLE);
				std::cout << '$';
			}
			else {
				setTextColors(WHITE);
				std::cout << currentBoard[y][x];
			}
			setTextColors(WHITE);
		}
	}
}

// Checks the 12 locations on the top right to see if there is room for a timer
bool Board::checkTopRightFree() {
	int row = 0;
	for (int col = MAX_X - 12; col < MAX_X; ++col) {
		if (originalBoard[row][col] != ' ') {
			return false;
		}
	}
	return true;
}
