#include "Hammer.h"

// Draw the hammer using its icon at its position
void Hammer::draw() const {
    if (!isCollected) {
        draw(ICON);
    }
}

// Erase the hammer from the board by drawing a space at its position
void Hammer::erase() {
    if (isCollected) {
        draw(' ');
    }
}

// Check if the player collects the hammer .
bool Hammer::collect(const Point& playerPos) {
    if (!isCollected && position == playerPos) {
        isCollected = true;
        erase();
        return true;
    }
    return false;
}

// Reset the hammer to its original state
void Hammer::reset() {
    isCollected = false;
    draw();
}
