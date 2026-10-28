//pretty ordinary point class
#include "Point.h"


//constructor
Point::Point(int x, int y) : x(x), y(y) {}

//getter for the X coordinate
int Point::getX() const {
    return x;
}

//getter for the Y coordinate
int Point::getY() const {
    return y;
}

//setter for the X coordinate
void Point::setX(int newX) {
    x = newX;
}

//setter for the Y coordinate
void Point::setY(int newY) {
    y = newY;
}



//move by delta values
void Point::move(int dx, int dy) {
    x += dx;
    y += dy;
}

//check equality of points
bool Point::equals(const Point& other) const {
    return x == other.x && y == other.y;
}

//calculate distance between two points
double Point::distanceTo(const Point& other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

//print point for debugging
void Point::print() const {
    std::cout << "(" << x << ", " << y << ")" << std::endl;
}
