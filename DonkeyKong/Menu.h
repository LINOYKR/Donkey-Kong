#pragma once
#include "Game.h"
#include "SaveGame.h"
#include "LoadGame.h"

#include "Timer.h"
#include "Utils.h"
#include <string>
using namespace std;

class Menu {
private:
    string* options;   // The options array
    int numOptions;    //number of options in the menu
    int currentOption; //current option selected
    bool useColors = true;
    bool useSound = false;
    bool useTimer = false;

    void setTextColor(int color) const;       //change text color
    void playMenuSound() const;               //play sound when moving through menu options
    void playSelectSound() const;                   //play sound when selecting an option
    void displayMenu();                       //displays the menu
    void displayInstructions();               //displays game instructions

public:
    Menu(string optionsArray[], int size);  //constructor
    ~Menu();                                //destructor
    Menu(const Menu& other);                // Copy constructor
    Menu& operator=(const Menu& other);     // Assignment operator
    void run(int argc, char** argv);                             //activates menu
};
