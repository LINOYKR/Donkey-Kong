#include "ClimbingGhost.h"

// Constructor for ClimbingGhost
ClimbingGhost::ClimbingGhost(Board& board, const Point& startPos, Direction initialDir)
    : Ghost(board, startPos, initialDir, 'X') {
} // Use 'X' to differentiate climbing ghosts

// Override the move function to include ladder climbing
void ClimbingGhost::move(const std::vector<Ghost*>& ghosts) {
    if (!isAlive) {
        return;
    }

    char current = gBoard->getChar(position.getX(), position.getY());

    bool marioInRange = (std::abs(marioPos.getX() - position.getX()) <= CHASE_RANGE &&
        std::abs(marioPos.getY() - position.getY()) <= CHASE_RANGE);

    if (marioInRange) {
        if (isOnLadder()) {
            climbLadder(ghosts, marioPos);
            return;
        }

        int dx = (marioPos.getX() > position.getX()) ? 1 : -1;
        Point newPos = position;

        newPos.setX(position.getX() + dx);

        char floorBelowNext = gBoard->getChar(newPos.getX(), newPos.getY() + 1);
        if (floorBelowNext == ' ') {
            dir = (dir == Direction::Left) ? Direction::Right : Direction::Left;
            return;
        }

        char below = gBoard->getChar(position.getX(), position.getY() + 1);

        if (isFloor(below) && !checkCollisionWithOtherGhosts(newPos, ghosts)) {
            prevSquare = gBoard->getChar(newPos.getX(), newPos.getY());
            position = newPos;
            return;
        }
    }

    else {
        // Check for ladder climbing behavior
        if (isOnLadder()) {
            climbRandomly(ghosts); // Perform ladder-specific movement
            return;
        }

        // Otherwise, use the basic movement logic from the Ghost class
        basicMove(ghosts); // Call the inherited Ghost function
    }
}


// Check if the ghost is next to or on a ladder
bool ClimbingGhost::isOnLadder() const {
    char currentSquare = gBoard->getChar(position.getX(), position.getY());
    char twoBelowSquare = gBoard->getChar(position.getX(), position.getY() + 2);
    char belowSquare = gBoard->getChar(position.getX(), position.getY() + 1);

    return (currentSquare == 'H' || (isFloor(belowSquare) && twoBelowSquare == 'H'));
}


// Handle climbing logic
void ClimbingGhost::climbLadder(const std::vector<Ghost*>& ghosts, Point& marioPos) {
    char current = gBoard->getChar(position.getX(), position.getY());
    char above = gBoard->getChar(position.getX(), position.getY() - 1);
    char below = gBoard->getChar(position.getX(), position.getY() + 1);
    char twoBelow = gBoard->getChar(position.getX(), position.getY() + 2);

    bool marioInRange = (std::abs(marioPos.getX() - position.getX()) <= CHASE_RANGE &&
        std::abs(marioPos.getY() - position.getY()) <= CHASE_RANGE);

    Point newPos = position;

    if (marioPos.getY() < position.getY() && (isFloor(above) || current == 'H')) {
        if (above == 'H') {
            newPos.setY(newPos.getY() - 1);
        }
        else if (isFloor(above)) {
            newPos.setY(newPos.getY() - 2);
        }
    }
    else if (marioPos.getY() > position.getY() && (below == 'H' || twoBelow == 'H')) {
        if (below == 'H') {
            newPos.setY(newPos.getY() + 1);
        }
        else if (isFloor(below)) {
            newPos.setY(newPos.getY() + 2);
        }
    }
    else {
        basicMove(ghosts);
        return;
    }

    if (!checkCollisionWithOtherGhosts(newPos, ghosts)) {
        prevSquare = gBoard->getChar(newPos.getX(), newPos.getY());
        position = newPos;
    }

}


void ClimbingGhost::climbRandomly(const std::vector<Ghost*>& ghosts) {

    char current = gBoard->getChar(position.getX(), position.getY());
    char above = gBoard->getChar(position.getX(), position.getY() - 1);
    char below = gBoard->getChar(position.getX(), position.getY() + 1);
    char twoBelow = gBoard->getChar(position.getX(), position.getY() + 2);

    Point newPos = position;

    // If ghost is on a ladder
    if (current == 'H') {
        // Randomly decide to climb up, down, or step off
        int decision = rand() % 3;

        if (decision == 0) {
            // Climb up
            if (above == 'H') {
                newPos.setY(newPos.getY() - 1);

            }
            else if (isFloor(above)) {
                newPos.setY(newPos.getY() - 2);
            }
            if (!checkCollisionWithOtherGhosts(newPos, ghosts)) {
                prevSquare = gBoard->getChar(newPos.getX(), newPos.getY());
                position = newPos;
            }
        }
        else if (decision == 1 && below == 'H') {
            // Climb down
            newPos.setY(newPos.getY() + 1);
            if (!checkCollisionWithOtherGhosts(newPos, ghosts)) {
                prevSquare = gBoard->getChar(newPos.getX(), newPos.getY());
                position = newPos;
            }
        }
        else if (decision == 2 && isFloor(below)) {
            // Step off
            basicMove(ghosts);
        }
    }
    else if ((isFloor(below) && twoBelow == 'H')) {
        // Start climbing down
        if (rand() % 2 == 0) {
            newPos.setY(newPos.getY() + 2);
            if (!checkCollisionWithOtherGhosts(newPos, ghosts)) {
                prevSquare = gBoard->getChar(newPos.getX(), newPos.getY());
                position = newPos;
            }
        }
        else {
            basicMove(ghosts);
        }
    }
}

