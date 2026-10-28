#pragma once
#include "Ghost.h"

class BasicGhost : public Ghost {
public:
    BasicGhost(Board& board, const Point& startPos, Direction initialDir)
        : Ghost(board, startPos, initialDir, 'x') {
    }

private:
    void move(const std::vector<Ghost*>& ghosts) override;

};
