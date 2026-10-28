#include "Utils.h"

//move the cursor to a specific (Point) position in the console
void gotoxy(const Point& position) {
    std::cout.flush();
    COORD coord = { 0,0 }; // Create a COORD structure 
    coord.X = position.getX(); // Set the X coordinate 
    coord.Y = position.getY(); // Set the Y coordinate 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}

//controls the visibility of the console cursor
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Function to clear the console screen
void clearScreen() {
    system("CLS");  // Works for Windows; for other platforms, use appropriate code
}

// Function to set the console color
void setColor(int colorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

// Function to print a message centered in the console
void printCentered(const std::string& message) {
    // Assuming a console width of 80 characters
    int x = (80 - static_cast<int>(message.length())) / 2;  // Calculate the starting X position for centering
    int y = 12;  // Default Y position; can be adjusted as needed
    Point point(x, y);
    gotoxy(point);  // Use the Point class
    std::cout << message;
}


// Function to check if the position (Point) is within bounds (e.g., 80x25 screen)
bool isInLimits(const Point& point) {
    // Assuming the screen dimensions are 80 columns x 25 rows
    return (point.getX() >= 0 && point.getX() < 80 && point.getY() >= 0 && point.getY() < 25);
}

bool isFloor(char c) {
    return (c == '>' || c == '=' || c == '<' || c == 'Q');
}
