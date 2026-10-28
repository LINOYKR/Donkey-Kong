#include "Menu.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>  

using namespace std;
//Colors
constexpr int WHITE = 7;
constexpr int BRED = 12;
constexpr int BWHITE = 15;
constexpr int BBLUE = 11;
//Vol
constexpr int BEEP1 = 500;
constexpr int BEEP2 = 200;

constexpr int SLEEP_DURATION = 500;

//Change text color
void Menu::setTextColor(int color) const {
    if (useColors == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    }
}

//Play sound when moving through menu options
void Menu::playMenuSound() const {
    if (useSound == true) {
        Beep(BEEP1, BEEP2);
    }

}

// Play sound when selecting an option
void Menu::playSelectSound() const {
    if (useSound == true) {
        Beep(BEEP1, BEEP1);
    }
}


// Displaying the menu
void Menu::displayMenu() {
    system("cls"); // Clears the screen
    setTextColor(BRED);
    cout << "=================================================\n";
    setTextColor(BWHITE);
    cout << "   ****    ***  **   **  **   **  *****  **   ** \n";
    cout << "   *****  ***** ***  **  **  **   **      ** ** \n";
    cout << "   ** **  ** ** ** * **  *****    *****    ***  \n";
    cout << "   *****  ***** **  ***  **  **   **       *** \n";
    cout << "   ****    ***  **   **  **   **  *****    *** \n";
    cout << "     \n";
    cout << "         **   **   ***   **   **  ******\n";
    cout << "         **  **   *****  ***  **  **\n";
    cout << "         *****    ** **  ** * **  ** ****\n";
    cout << "         **  **   *****  **  ***  **   **\n";
    cout << "         **   **   ***   **   **  *******\n";
    setTextColor(BRED);
    cout << "=================================================\n";
    cout << "       ==========================\n";
    cout << "              Main Menu\n";
    cout << "       ==========================\n\n";

    for (int i = 0; i < numOptions; ++i) {
        if (i == currentOption) {
            setTextColor(BBLUE); // color for the current option
            cout << "        > " << options[i] << "\n";
        }
        else {
            setTextColor(WHITE); // color for other options
            cout << "          " << options[i] << "\n";
        }
    }

    setTextColor(BRED);
    cout << "\n       ==========================\n";
    setTextColor(WHITE);
}

// Displaying instructions
void Menu::displayInstructions() {
    system("cls");
    setTextColor(BRED); // yellow
    cout << "==============================================================================\n";
    cout << "                            Game Instructions\n";
    cout << "==============================================================================\n\n";

    setTextColor(WHITE); // white
    cout << "Welcome to the game!\n\n";
    setTextColor(BRED);
    cout << "Game Objective:\n";
    setTextColor(WHITE);
    cout << "Rescue Pauline ($) by reaching her position while avoiding barrels (O).\n";

    setTextColor(BRED);
    cout << "Game Elements:\n";
    setTextColor(WHITE);
    cout << " - Mario (@): The hero. Pauline ($): The goal to reach.\n";
    cout << " - Donkey Kong (&): Throws barrels(O) from the top.\n";
    cout << " - Floors (<, >, =): Define movement direction of barrels.\n";
    cout << " - Ladders (H): Connect floors; Mario can climb them.\n";

    setTextColor(BRED);
    cout << "Controls:\n";
    setTextColor(BBLUE); // for keys
    cout << " - LEFT:\t" << "LEFT ARROW or 'a' / 'A'\n";
    cout << " - RIGHT:\t" << "RIGHT ARROW or 'd' / 'D'\n";
    cout << " - UP / JUMP:\t" << "UP ARROW or 'w' / 'W'\n";
    cout << " - DOWN:\t" << "DOWN ARROW or 'x' / 'X'\n";
    cout << " - STAY:\t" << "'s' / 'S'\n";
    cout << " - PAUSE:\t" << "'ESC'\n";

    setTextColor(BRED);
    cout << "Game Rules:\n";
    setTextColor(WHITE);
    cout << "1. Mario starts and moves continuously in the chosen direction.\n";
    cout << "2. Use ladders (H) or jumps to avoid barrels (O).\n";
    cout << "3. If Mario falls 5 lines or more, he loses a life and the stage restarts.\n";
    cout << "4. If a barrel falls 8 lines or more, it explodes. Mario could lose a life.\n";
    cout << "5. The game ends if Mario loses all 3 lives.\n";
    cout << "6. Mario wins by reaching Pauline ($) at the top.\n";
    setTextColor(BRED);
    cout << "==============================================================================\n";
    setTextColor(WHITE);
    cout << "Press any key to return to the main menu.";

    (void)_getch(); // Waits for press and skips the return value
}

// Copy constructor
Menu::Menu(string optionsArray[], int size) {
    numOptions = size;
    options = new string[size]; // Allocate memory to an array
    for (int i = 0; i < size; ++i) {
        options[i] = optionsArray[i]; // Copy the values
    }
    currentOption = 0; // Starting from the first option
}

// Destructor
Menu::~Menu() {
    delete[] options; // Release the allocated memory
}

//Copy Constructor
Menu::Menu(const Menu& other) {
    numOptions = other.numOptions;
    options = new string[numOptions];
    for (int i = 0; i < numOptions; ++i) {
        options[i] = other.options[i];
    }
    currentOption = other.currentOption;
    useColors = other.useColors;
    useSound = other.useSound;
}

// Assignment operator
Menu& Menu::operator=(const Menu& other) {
    if (this != &other) {
        delete[] options;
        numOptions = other.numOptions;
        options = new string[numOptions];
        for (int i = 0; i < numOptions; ++i) {
            options[i] = other.options[i];
        }
        currentOption = other.currentOption;
        useColors = other.useColors;
        useSound = other.useSound;
    }
    return *this;
}

// Activating the menu
void Menu::run(int argc, char** argv) {
    Sleep(SLEEP_DURATION);
    char input;
    bool running = true;
    bool isSave = argc > 1 && std::string(argv[1]) == "-save";
    bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
    bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
    if (isLoad) {
        LoadGame loadGame;
        loadGame.setWaitForInput();
        if (isSilent) {
            loadGame.setSilentMode();
        }
        loadGame.runGame(useColors, useTimer);
    }
    else {
        do {
            Game game;
            SaveGame saveGame;

            displayMenu();

            input = _getch(); // Read a character without having to press Enter

            // Handling user input
            switch (input) {
            case '1': // Start game
                playSelectSound();
                setTextColor(BBLUE);
                clearScreen();
                if (isSave) {
                    saveGame.runGame(useColors, useTimer);
                }
                else {
                    game.runGame(useColors, useTimer);
                }
                displayMenu();

            case '8': // Show instructions
                playSelectSound();
                displayInstructions();
                break;
            case '9': // Exit
                playSelectSound();
                cout << "Goodbye!\n";
                Sleep(1000);
                running = false;
                break;
            case '2': // Without or with color
                useColors = !useColors;
                playSelectSound();
                displayMenu();
                break;
            case '3': // Without or with sound
                useSound = !useSound;
                playSelectSound();
                displayMenu();
                break;
            case '4': // Without or with sound
                useTimer = !useTimer;;
                playSelectSound();
                displayMenu();
                break;

            case 72: // Up 
                playMenuSound(); // Sound when moving up in the menu
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case 80: // Down 
                playMenuSound(); // Sound when moving down in the menu
                currentOption = (currentOption + 1) % numOptions;
                break;
            case 13: // Enter
                if (currentOption == 0) {
                    playSelectSound();
                    setTextColor(BBLUE);
                    clearScreen();
                    if (isSave) {
                        saveGame.runGame(useColors, useTimer);
                    }
                    else {
                        game.runGame(useColors, useTimer);
                    }
                    displayMenu();
                }
                else if (currentOption == 1) {
                    playSelectSound();
                    displayInstructions();
                }
                else if (currentOption == 2) {
                    playSelectSound();
                    cout << "Goodbye!\n";
                    Sleep(1000);
                    running = false;
                    break;
                }
                else if (currentOption == 3) {
                    useColors = !useColors;
                    playSelectSound();
                    displayMenu();
                }
                else if (currentOption == 4) {
                    useSound = !useSound;
                    playSelectSound();
                    displayMenu();
                }
                else if (currentOption == 5) {
                    useTimer = !useTimer;
                    playSelectSound();
                    displayMenu();
                }

                break;
            default:
                break;
            }

        } while (running); // Always ongoing until one returns
    }
}
