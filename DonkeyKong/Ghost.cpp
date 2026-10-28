//Represents a ghost entity in the game. Includes behavior specific to ghosts.
//Inherits from Entity
#include "Ghost.h"


// Function to move the Ghost based on its current direction
void Ghost::basicMove(const std::vector<Ghost*>& ghosts) {
	if (!isAlive) {
		return;
	}

	double randomVal = static_cast<double>(rand()) / RAND_MAX;
	if (randomVal < 0.05) {
		dir = (dir == Direction::Left) ? Direction::Right : Direction::Left;
	}

	Point newPos = position;
	int deltaX = (dir == Direction::Left) ? -1 : 1;
	newPos.setX(position.getX() + deltaX);

	if (checkCollisionWithOtherGhosts(newPos, ghosts)) {
		// Reverse direction if collision detected
		dir = (dir == Direction::Left) ? Direction::Right : Direction::Left;
		return;
	}


	char floorBelowNext = gBoard->getChar(newPos.getX(), newPos.getY() + 1);
	if (floorBelowNext == ' ') {
		dir = (dir == Direction::Left) ? Direction::Right : Direction::Left;
		return;
	}

	if (isInLimits(newPos)) {
		prevSquare = gBoard->getChar(newPos.getX(), newPos.getY());
		position = newPos;
	}
	else {
		dir = (dir == Direction::Left) ? Direction::Right : Direction::Left;
	}

}


// Function to reset the Ghost's position and direction
void Ghost::reset(const Point& newPos, Direction newDir) {
	position = newPos;
	dir = newDir;
	isAlive = true;
}

// Function to check if the Ghost is alive
bool Ghost::alive() const {
	return isAlive;
}

// Function to check for collisions with another Ghost
bool Ghost::checkCollisionWithOtherGhosts(const Point& newPos, const std::vector<Ghost*>& ghosts) {
	for (const auto& ghost : ghosts) {
		if (ghost != this && ghost->getPosition() == newPos) {
			return true;
		}
	}
	return false;
}
