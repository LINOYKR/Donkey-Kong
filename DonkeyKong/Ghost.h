#pragma once
#include "Point.h"
#include "Board.h"
#include <random>
#include <cmath> 
#include <iostream>
#include "Utils.h"
#include "Enemy.h"

class Ghost : public Enemy {
public:
	enum class Direction { Left, Right };

protected:
	//static constexpr char ICON = 'x';
	Direction dir;
	bool isAlive = true;
	Point marioPos;


public:
	Ghost(Board& board, const Point& startPos, Direction initialDir, char icon)
		:Enemy(startPos, icon, ' '), dir(initialDir)
	{
		gBoard = &board; // Set the board pointer
	}
	void basicMove(const std::vector<Ghost*>& ghosts);// Function to move the Ghost based on its current direction
	virtual void move(const std::vector<Ghost*>& ghosts) = 0;
	void reset(const Point& newPos, Direction newDir);// Function to reset the Ghost's position and direction
	bool alive() const;// Function to check if the Ghost is alive
	bool checkCollisionWithOtherGhosts(const Point& newPos, const std::vector<Ghost*>& ghosts);
	void setAlive(bool set) { isAlive = set; }
	void setMarioPos(const Point& newMarioPos) { marioPos = newMarioPos; }

};
