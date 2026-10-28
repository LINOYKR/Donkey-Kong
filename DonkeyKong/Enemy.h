//Inherits from GameEntity
#pragma once
#include "GameEntity.h"
class Enemy : public GameEntity {
protected:
	struct Direction { int x, y; };

public:
	bool checkCollisionWithMario(const Point& marioPosition, int dist) const; //Collision test with Mario

	Enemy(const Point& startPos, char symbol, char prev)//Constructor 
		: GameEntity(startPos, symbol, prev) {
	}
};
