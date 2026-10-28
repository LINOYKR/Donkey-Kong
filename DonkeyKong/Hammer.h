#pragma once
#include "Point.h"
#include "Board.h"
#include "Utils.h"
#include "Player.h"
class Hammer
{
private:
	Point position;
	bool isCollected = false;
	static const char ICON = 'p';

	void draw(char c) const {
		gotoxy(position);
		std::cout << c;
	}

public:
	Hammer(const Point& pos) : position(pos) {}
	void draw() const;// Draw the hammer using its icon at its position
	void erase();// Erase the hammer from the board by drawing a space at its position
	bool collect(const Point& playerPos);// Check if the player collects the hammer .
	void reset();// Reset the hammer to its original state

};