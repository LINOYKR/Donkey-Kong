
#pragma once
#include "Enemy.h"

class Barrel : public Enemy {
public:
    enum class FloorDirection { Left, Right, Neutral };

private:
    static constexpr char ICON = 'O';
    static constexpr int EXPLOSION_THRESHOLD = 8;
    bool isDestroyed = false;
    char prevChar = ' ';  // Store the character that was at the barrel's position

    int fallCount = 0;
    bool shouldExplode = false;
    FloorDirection currentDirection;

    Direction dir = { 0,0 };

    void updateDirection(FloorDirection floor);

public:
    Barrel(Board& board, const Point& startPos, FloorDirection initialFloor);//Constructor. Initializes the barrel with default values.

    void move(); //moves the barrels
    bool canFall() const;//checks if the barrel can fall
    bool isExplosion() const; //checks if the barrel needs to explode
    void explode(bool isSilent); //explodes the barrel
    void reset(Point newPosition, FloorDirection newDirection); //resets the barrel new position and direction & clears its state


};
