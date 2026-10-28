#include "GameEntity.h"

void GameEntity::draw() const {
	draw(icon);
}

void GameEntity::erase() {
	draw(prevSquare);
}

Point GameEntity::getPosition() const {
	return position;
}
