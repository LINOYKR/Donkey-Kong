#include "Player.h"
#include "Board.h"

//some of the code in this class was taken from Amir's movingPoint class he showed us.

//Reset mario
void Player::resetPosition(const Point& startPos) {
    position = startPos;
    dir = { 0, 0 };
    isJumping = false;
    jumpHeight = 0;
    highDown = 0;
    pauline = false;
    isFalling = false;
    hasHammer = false;
    icon = '@';
}

// Initiate a jump sequence for Mario
void Player::startJump() {
    isJumping = true; // Set jumping state to true
    jumpHeight = 0; // Reset jump height counter
    jumpDirection = dir; // Store current horizontal direction
    dir = { dir.x, -1 }; // Start moving up
}

// Continue the jump sequence by updating Mario's position
void Player::continueJump() {

    if (jumpHeight < MAX_JUMP_HEIGHT) {
        // Moving up
        jumpHeight++;
        dir = { jumpDirection.x, -1 };
    }
    else if (jumpHeight < MAX_JUMP_HEIGHT * 2) {
        // Moving down
        Point newPos = Point(position.getX() + jumpDirection.x, position.getY() + 1);
        char nextSquare = gBoard->getChar(newPos.getX(), newPos.getY());

        if (isFloor(nextSquare)) {
            dir = { 0, 0 };
        }
        else {
            dir = { jumpDirection.x, 1 };
        }
        jumpHeight++;

    }
    else {

        // Finished jumping
        isJumping = false;
        dir = { jumpDirection.x, 0 };
    }
}

// Returns true if the player has reached Pauline (win condition).
bool Player::isPauline() {
    return pauline;
}

//handle key presses for Mario's movement
void Player::keyPressed(char key, std::vector<Barrel>& barrels, std::vector<Ghost*>& ghosts) {

    if (std::tolower(key) == 'p' && hasHammer) {
        useHammer(barrels, ghosts);
        return;
    }

    Point newPos = Point(position.getX() + dir.x, position.getY() + dir.y);
    // Check if the next character is 'Q'
    if (gBoard->getChar(newPos.getX(), newPos.getY()) == 'Q') {
        dir = { 0, 0 };
        return;
    }
    //loop through the predefined keys (e.g., movement keys)
    for (size_t i = 0; i < numKeys; i++) {
        if (std::tolower(key) == keys[i]) {
            if (i == 0 && !isJumping && !isLadder) { // 'w' key and not already jumping
                startJump();
            }
            else if (i == 2) { // 'x' key (down)
                char belowSquare = gBoard->getChar(position.getX(), position.getY() + 1);
                char belowSquare2 = gBoard->getChar(position.getX(), position.getY() + 2);

                // Allow downward movement if on a ladder or there's empty space below
                if ((isLadder && belowSquare == 'H') || belowSquare == ' ') {
                    dir = directions[i];
                }
                else if (isFloor(belowSquare) && belowSquare2 == 'H')
                {
                    dir = directions[i];
                }
                else if (isFloor(belowSquare2)) {
                    dir = { 0, 0 };  //stop movement if theres no valid space
                }
            }
            else {
                // Update direction for other movement keys
                dir = directions[i];
            }
            return;
        }
    }
}

// Update Mario's position based on current direction and handle game mechanics
void Player::move() {


    // If jumping, update jump state
    if (isJumping) {
        continueJump();
    }
    Point newPos = Point(position.getX() + dir.x, position.getY() + dir.y);
    Point belowMe(position.getX(), position.getY() + 2); //under the floor below me



    // Get characters at different positions
    char nextSquare = gBoard->getChar(newPos.getX(), newPos.getY());
    char belowSquare = gBoard->getChar(position.getX(), position.getY() + 1);
    char aboveSquare = gBoard->getChar(position.getX(), position.getY() - 1);


    // Prevent movement outside the board boundaries
    if (!isInLimits(newPos)) {
        dir = { 0, 0 };
        return;
    }
    if (nextSquare == 'Q') {
        dir = { 0, 0 };
        return;
    }
    //if reached pauline
    if (nextSquare == '$') {
        pauline = true;
    }

    if (nextSquare == 'p') {
        collectHammer();
    }
    if (position.getY() == MAX_Y - 1) {
        if (isFloor(nextSquare)) {
            dir = { 0, 0 };
            return;
        }
    }

    // Check if on a ladder
    isLadder = ((nextSquare == 'H') || (isFloor(nextSquare) && (belowSquare == 'H')));

    //handle upward movement on a ladder
    if (isLadder && aboveSquare != 'H' && isFloor(aboveSquare) && dir.y == -1) {
        // Reached top of ladder
        newPos.setY(position.getY() - 2);  // Place Mario on top of the floor
        isLadder = false;
        dir = { 0, 0 };  // Stop movement
    }


    // Handle downward movement
    if (dir.y > 0 && !isJumping && !isFalling) {
        // Check if there's a floor below
        if (isInLimits(belowMe)) {
            char belowChar = gBoard->getChar(belowMe.getX(), belowMe.getY());
            if (belowChar == 'H') {
                // Move to just above the ladder
                newPos.setY(belowMe.getY() - 1);
            }
            else {
                dir.y = 0; // Stop downward movement if not on a ladder
            }
        }
        else {
            dir.y = 0; // Prevent moving down out of bounds
        }

    }


    //check for falling
    if (!isJumping && !isLadder)
    {
        char belowChar = gBoard->getChar(belowMe.getX(), belowMe.getY());
        if (belowSquare == ' ') {
            newPos.setY(belowMe.getY() - 1);
            isFalling = true;
            highDown++;

        }
        else if ((isFalling) && (isFloor(belowSquare) || position.getY() == MAX_Y - 1))
        {


            // Check for fall damage
            if (highDown >= 5) {
                // Implement life loss and stage restart here
                loseLives = true;
            }
            dir.y = 0;
            isFalling = false;
            jumpHeight = 0;
        }
    }

    // Update position
    position = newPos;



    prevSquare = nextSquare;

}

// Sets the reference to the game board for the player.
void Player::setBoard(Board& board) {
    gBoard = &board;
}

// Updates the player's state to indicate that they have collected a hammer.
void Player::collectHammer() {
    hasHammer = true;
    icon = '%';
}

// Checks if the player can use the hammer.
bool Player::canUseHammer() const {
    return hasHammer;
}

// Allows the player to use the hammer to destroy barrels or ghosts.
void Player::useHammer(std::vector<Barrel>& barrels, std::vector<Ghost*>& ghosts) {
    if (!hasHammer) return;

    // Calculate the two positions in the hammer range
    Point hammerRange1 = position; // First position
    Point hammerRange2 = position; // Second position

    if (dir.x == 0 && dir.y == 0) {
        // Default to facing right if Mario is stationary
        hammerRange1.setX(hammerRange1.getX() + 1);
        hammerRange2.setX(hammerRange2.getX() + 2);
    }
    else {
        // Extend in the direction Mario is facing
        hammerRange1.setX(hammerRange1.getX() + dir.x);
        hammerRange1.setY(hammerRange1.getY() + dir.y);
        hammerRange2.setX(hammerRange2.getX() + (2 * dir.x));
        hammerRange2.setY(hammerRange2.getY() + (2 * dir.y));
    }

    // Remove barrels within hammer range
    barrels.erase(std::remove_if(barrels.begin(), barrels.end(),
        [&](const Barrel& b) {
            if (b.getPosition() == hammerRange1 || b.getPosition() == hammerRange2) {
                score += 5;  // Add score for barrels
                return true; // Remove barrel
            }
            return false;
        }), barrels.end());

    // Remove ghosts within hammer range
    for (auto& g : ghosts) {
        if (g->alive() && g->getPosition() == hammerRange1 || g->getPosition() == hammerRange2) {
            g->setAlive(false);
            g->erase();
            score += 10;
        }
    }
    ghosts.erase(remove_if(ghosts.begin(), ghosts.end(),
        [](const Ghost* gh) {return !gh->alive(); }), ghosts.end());

     
    // Display hammer effect at both positions
    if (!isSilent) {
        gotoxy(hammerRange1);
        std::cout << '*';
        gotoxy(hammerRange2);
        std::cout << '*';
        Sleep(100);
    }
    char nextPos1 = gBoard->getChar(hammerRange1.getX(), hammerRange1.getY());
    char nextPos2 = gBoard->getChar(hammerRange2.getX(), hammerRange2.getY());
    // Clear the hammer effect
    gotoxy(hammerRange1);
    std::cout << nextPos1;
    gotoxy(hammerRange2);
    std::cout << nextPos2;
}


