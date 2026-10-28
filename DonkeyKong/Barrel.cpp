// Represents a barrel entity in the game. Handles barrel-specific behavior such as movement.
//Inherits from Entity
#include "Barrel.h"

//constructor for Barrel class- initializes the board, direction, and starting position
Barrel::Barrel(Board& board, const Point& startPos, FloorDirection initialFloor)
    : Enemy(startPos, ICON, ' '), currentDirection(initialFloor) {
    gBoard = &board; // Set the board pointer

}

/*this method moves the barrel based on its direction.
* if it falls for more than 8 chars it explodes.
* if it goes beyoned the board limits it disappears
*/
void Barrel::move() {

    //if the barrel is destroyed, it doesn't move
    if (isDestroyed) {
        return;
    }

    //check the floor beneath the barrel to determine if it can fall
    char floor = gBoard->getChar(position.getX(), position.getY() + 1);

    //if the floor is empty, the barrel can fall and we update its fall count
    if (floor == ' ') {
        dir = { 0, 1 }; //moves downwards
        fallCount++;
        if (fallCount >= EXPLOSION_THRESHOLD) {
            shouldExplode = false; //dont explode right away if it fell for enpugh chars
        }
    }
    else {
        //if the barrel hits a floor check its direction and change accordingly
        if (floor == '=' || floor == '<' || floor == '>' || floor == 'Q') {
            if (fallCount >= EXPLOSION_THRESHOLD) {
                shouldExplode = true; //trigger explosion once hitting a floor if it fell for enpugh chars

            }
            //change direction based on which floor type was encountered
            currentDirection = (floor == '>' || (floor == '=' && currentDirection == FloorDirection::Right))
                ? FloorDirection::Right : FloorDirection::Left;
            dir = (currentDirection == FloorDirection::Right) ? Direction{ 1, 0 } : Direction{ -1, 0 };
        }
        fallCount = 0; //resets fall count after hitting a floor

    }

    //calculate new position after moving.
    Point newPosition(position.getX() + dir.x, position.getY() + dir.y);

    //if the new position is within bounds, update the barrel's position
    if (isInLimits(newPosition)) {
        prevSquare = gBoard->getChar(newPosition.getX(), newPosition.getY()); //saves the char if we might need it 

        position = newPosition;

    }
    else {
        shouldExplode = true; //explode of going off limits
    }
}


void Barrel::updateDirection(FloorDirection floor) {
    currentDirection = floor;
    dir = (currentDirection == FloorDirection::Right) ? Direction{ 1, 0 } : Direction{ -1, 0 };
}


//checks if the barrel can fall
bool Barrel::canFall() const {
    return gBoard->getChar(position.getX(), position.getY() + 1) == ' ';
}

//checks if the barrel should explode
bool Barrel::isExplosion() const {
    return shouldExplode;
}

//this method handles the barrels explosion
void Barrel::explode(bool isSilent) {

    dir = { 0, 0 }; //stops the barrel while exploding

    //fill the area with a radius of 2 around the explosion location in X
    for (int dx = -2; dx <= 2; ++dx) {
        for (int dy = -2; dy <= 2; ++dy) {
            Point explosionPoint(position.getX() + dx, position.getY() + dy);

            if (isInLimits(explosionPoint) && gBoard->getChar(explosionPoint.getX(), explosionPoint.getY()) == ' ') {
                gotoxy(explosionPoint);
                if (!isSilent) {
                    std::cout << 'X'; //prints'X' as an explosion graphics
                }
            }
        }
    }
    Sleep(100); //delay to simulate explosion effect

    //clears rhe explosion area after effect 
    for (int dx = -2; dx <= 2; ++dx) {
        for (int dy = -2; dy <= 2; ++dy) {
            Point explosionPoint(position.getX() + dx, position.getY() + dy);
            if (isInLimits(explosionPoint) && gBoard->getChar(explosionPoint.getX(), explosionPoint.getY()) != '=') {
                char c = gBoard->getChar(explosionPoint.getX(), explosionPoint.getY());
                if (c != '=' && c != '<' && c != '>' && c != 'H' && c != 'Q')
                {
                    gotoxy(explosionPoint);
                    std::cout << ' ';
                }

            }

        }
    }

    //marks the barrel as destryed after explosion
    isDestroyed = true;
    shouldExplode = false;
    fallCount = 0; //resets
    erase(); //erases from board

}


//resets the barrel to a new position and direction, and clears its state
void Barrel::reset(Point newPosition, FloorDirection newDirection) {
    position = newPosition;
    currentDirection = newDirection;
    fallCount = 0;
    shouldExplode = false;
    isDestroyed = false;
    dir = (currentDirection == FloorDirection::Right) ? Direction{ 1, 0 } : Direction{ -1, 0 };
}
