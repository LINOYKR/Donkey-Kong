#pragma once
#include "Barrel.h"
#include "Ghost.h"
#include "GameEntity.h"
#include <vector>
class Player : public GameEntity {

private:

    static constexpr int MAX_Y = 25;

    static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' }; //keys pressed
    static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
    static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} }; //the directions array order is exactly the same as the keys array so it matches
    Direction dir{ 0, 0 }; //current direction: dir.x, dir.y

    bool noFloor = false; //says if the player is on a floor char
    bool isLadder = false; //says if the player is on a ladder
    bool goDown = false; //says if the player goes down
    bool isFalling = false; //says if the player falls
    bool hasHammer = false;

    bool isSilent = false;

    bool isJumping = false; //says if the player jumps
    int jumpHeight = 0; //jumo height in chars
    int highDown = 0;
    const int MAX_JUMP_HEIGHT = 2; //player can jump to 2 chars top
    Direction jumpDirection{ 0, 0 }; //upwards or sideways


    bool pauline = false; //says if mario reached Pauline
    size_t score = 0;

public:
    bool loseLives = false;//says if mario should lose a life

    Player() : GameEntity(Point(3, 23), '@', '@') {};

    void resetPosition(const Point& startPos); //resets marios position
    void startJump(); //starts the jump
    void continueJump();//continues jump

    bool isPauline();//returnes if mario has reached Pauline (and the user wins)
    void keyPressed(char key, std::vector<Barrel>& barrels, std::vector<Ghost*>& ghosts); //gets the key
    void move();//moves mario
    void setBoard(Board& board);//sets the board
    void collectHammer();// Updates if collected a hammer.
    bool canUseHammer() const;// Checks if the player can use the hammer.
    void useHammer(std::vector<Barrel>& barrels, std::vector<Ghost*>& ghosts); // Use the hammer to destroy barrels or ghosts.

    int getScore() { return score; } // Returns the player's current score.
    void setIsSilent(bool silent) {
        isSilent = silent;
    }

};
