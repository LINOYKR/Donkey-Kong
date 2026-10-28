#include "Enemy.h"

// Checks if the Enemy collides with Mario by comparing the enemy's position with Mario's position (marioPosition) and a given distance (dist).
bool Enemy::checkCollisionWithMario(const Point& marioPosition, int dist) const {
	int dx = position.getX() - marioPosition.getX();
	int dy = position.getY() - marioPosition.getY();
	double distance = std::sqrt(dx * dx + dy * dy);

	//if the distance is less than 1, they are close enough to be considered "colliding"
	return distance <= dist;
}
