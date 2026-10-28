#include <iostream>
#include <conio.h>
#include "Menu.h"

int main(int argc, char** argv) {

    string options[] = { "Start a new game (1)", "Present instructions and keys (8)", "Exit (9)", "Without or with color (2)", "Without or with sound (3)", "Without or with timer (4)" };
    const int numOptions = sizeof(options) / sizeof(options[0]);

    Menu menu(options, numOptions);
    menu.run(argc, argv);

    clearScreen();
}

