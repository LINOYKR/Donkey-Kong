#pragma once

#include "Ghost.h"

class ClimbingGhost : public Ghost {
private:

    const int CHASE_RANGE = 15;

    // Helper function to determine if the ghost is next to or on a ladder
    bool isOnLadder() const;

    // Helper function to handle ladder climbing behavior
    void climbLadder(const std::vector<Ghost*>& ghosts, Point& pos);

    void climbRandomly(const std::vector<Ghost*>& ghosts);

public:
    // Constructor for ClimbingGhost
    ClimbingGhost(Board& board, const Point& startPos, Direction initialDir);

    // Override the move function to include ladder climbing
    void move(const std::vector<Ghost*>& ghosts) override;


};
