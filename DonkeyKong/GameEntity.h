#pragma once

#include "Point.h"
#include "Board.h"
#include "Utils.h"

class GameEntity {
protected:
	Point position;
	Board* gBoard;
	char icon;
	char prevSquare;
	struct Direction { int x, y; };

	void draw(char c) const {
		gotoxy(position);
		std::cout << c;
	}

public:


	GameEntity(Point startPos, char symbol, char prev) : position(startPos), icon(symbol), prevSquare(prev) {} // Constructor .

	void draw() const;//Draws the current entity on the screen using its defined icon.

	void erase();//Erases the entity from the screen by drawing the character from its previous

	Point getPosition() const; //Retrieves the current position of the entity(position).

};
