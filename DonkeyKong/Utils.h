#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <windows.h>
#include <iostream>
#include <string>

#include "Point.h"


//move the cursor to a specific (Point) position in the console
void gotoxy(const Point& position);

//controls the visibility of the console cursor
void ShowConsoleCursor(bool showFlag);

//clear the console screen
void clearScreen();

//set the console text color
void setColor(int colorCode);

//print a message centered in the console
void printCentered(const std::string& message);

//pause the game and wait for user input
void pause();

//check if the position (Point) is within screen limits (e.g., 80x25)
bool isInLimits(const Point& point);

//checks if a char is a floor
bool isFloor(char c);

#endif  // UTILS_H
