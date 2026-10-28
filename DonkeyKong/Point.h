#pragma once
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

class Point {
private:
    int x;
    int y;

public:

    //constructor
    Point(int x = 0, int y = 0);

    //getter functions for x and y
    int getX() const;
    int getY() const;

    //setter functions for x and y
    void setX(int newX);
    void setY(int newY);


    //move by delta values
    void move(int dx, int dy);

    //check equality of points
    bool equals(const Point& other) const;

    //calculate distance between two points
    double distanceTo(const Point& other) const;

    //print point for debugging
    void print() const;


    bool operator==(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }

};

#endif  // POINT_H
