#include "Game.h"

using namespace std;

constexpr int MAX_BARRELS = 20;
constexpr int MAX_GHOSTS = 5;
constexpr int ESC = 27;
constexpr int NEW_BARREL_INTERVAL = 25;
constexpr int SLEEP_DURATION = 50;
constexpr int COLLISION_DISTANCE = 2;
constexpr int GHOST_COLLISION = 1;

//Colors
enum Colors {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	PURPLE = 5,
	YELLOW = 6,
	WHITE = 7,
	GRAY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_PURPLE = 13,
	LIGHT_YELLOW = 14,
	BRIGHT_WHITE = 15
};

Game::~Game() {
	// Delete all dynamically allocated ghosts
	for (Ghost* ghost : ghosts) {
		delete ghost;
	}
	ghosts.clear(); // Clear the vector after deleting
}

//displays if mario saved pauline
void Game::displayVictoryMessage() {
	system("cls"); //clear the console
	board.setTextColors(LIGHT_RED);
	cout << "====================================================\n";
	board.setTextColors(WHITE);
	cout << "       *****   *****  **   **  *****  ****    \n";
	cout << "       **      ** **  **   **  **     *****   \n";
	cout << "        ***    *****  **   **  *****  ** **   \n";
	cout << "          **   ** **  *******  **     *****   \n";
	cout << "       *****   ** **   *****   *****  ****    \n";
	cout << "\n";
	cout << " ****   *****  ** **  **     ***  **   **  *****  \n";
	cout << " ** **  ** **  ** **  **      *   ***  **  **     \n";
	cout << " ****   *****  ** **  **      *   ** * **  *****  \n";
	cout << " **     ** **  *****  **      *   **  ***  **    \n";
	cout << " **     ** **  *****  *****  ***  **   **  ***** \n";
	board.setTextColors(LIGHT_RED);
	cout << "====================================================\n";
	board.setTextColors(LIGHT_CYAN);
	cout << "Congratulations! You saved Pauline!" << endl;
	if (waitForInput) {
		cout << "Press any key to return to the menu..." << endl;
		_getch();
	}
	else {
		Sleep(SLEEP_DURATION * 2);
	}
	board.setTextColors(WHITE);
	return;
}

//displays if mario lost
void Game::displayLossMessage() {
	system("cls"); //clear the console
	board.setTextColors(LIGHT_RED);
	cout << "====================================================\n";
	board.setTextColors(WHITE);
	cout << "               **   **   ***   **   **      \n";
	cout << "                ** **   *****  **   **      \n";
	cout << "                 ***    ** **  **   **      \n";
	cout << "                 ***    *****  *******      \n";
	cout << "                 ***     ***    *****       \n";
	cout << "\n";
	cout << "             **      ***   *****  ******     \n";
	cout << "             **     *****  **     ******     \n";
	cout << "             **     ** **   ***     **       \n";
	cout << "             *****  *****     **    **       \n";
	cout << "             *****   ***   *****    **       \n";
	board.setTextColors(LIGHT_RED);
	cout << "====================================================\n";
	board.setTextColors(LIGHT_CYAN);
	cout << "You lost, Paulina was not saved, try again." << endl;
	if (waitForInput) {
		cout << "Press any key to return to the menu..." << endl;
		_getch();
	}
	else {
		Sleep(SLEEP_DURATION * 2);
	}
	board.setTextColors(WHITE);
	return;
}

//displays end all game and win
void Game::displayEndAllGameWin() {
	system("cls"); //clear the console
	board.setTextColors(LIGHT_RED);
	cout << "====================================================\n";
	board.setTextColors(WHITE);
	cout << "    **       ***       **   ******   **       **    \n";
	cout << "    **      ** **      **   ******   ***      **    \n";
	cout << "    **     **   **     **     **     **  *    **    \n";
	cout << "    **    **     **    **     **     **   *   **    \n";
	cout << "    **   **       **   **     **     **    *  **    \n";
	cout << "    **  **         **  **     **     **     * **    \n";
	cout << "    ** **           ** **   ******   **      ***    \n";
	cout << "    ****             ****   ******   **       **    \n";
	board.setTextColors(LIGHT_RED);
	cout << "====================================================\n";
	board.setTextColors(LIGHT_CYAN);
	cout << "               W I N   A L L   G A M E              \n";
	board.setTextColors(LIGHT_RED);
	cout << "====================================================\n";
	board.setTextColors(LIGHT_CYAN);
	cout << "Congratulations! You won all the levels!\n" << endl;
	if (waitForInput) {
		cout << "Press any key to return to the menu..." << endl;
		_getch();
	}
	else {
		Sleep(SLEEP_DURATION * 2);
	}
	board.setTextColors(WHITE);
	return;
}

//displays Error Message
void Game::displayErrorMessage(const std::string& errorDetails) {
	system("cls"); //clear the console
	board.setTextColors(RED);
	cout << "====================================================\n";
	cout << "              Error: The board file             \n";
	cout << "====================================================\n";
	cout << "====================================================\n";
	board.setTextColors(WHITE);
	cout << "Details: " << errorDetails << "\n"; // Add the specific error
	board.setTextColors(RED);
	cout << "====================================================\n";
	board.setTextColors(WHITE);
	cout << "Press any key to return to the menu..." << endl;

	char input = _getch(); //wait for user input
	return;
}

//resets the level to the beginning
void Game::BackToBeginning() {
	system("cls");
	std::cout.flush();
	board.reset();
	if (!isSilent) {
		board.print();
	}
	for (auto& barrel : barrels) {
		if (!isSilent) {
			barrel.erase();
		}
	}
	barrels.clear();

	frameCount = 0;
	activeBarrels = 0;
	mario.resetPosition(board.getMarioStartPos());

	for (auto& ghost : ghosts) {
		if (!isSilent) {
			ghost->erase();
		}
	}

	if (board.isHammerAvailable()) {
		hammer = Hammer(board.getHammerPosition());
		if (!isSilent) {
			hammer.draw();
		}
	}


	mario.resetPosition(board.getMarioStartPos());
	mario.setBoard(board);
	if (!isSilent) {
		mario.draw();
	}
	resetGhosts();
	if (board.checkTopRightFree() && useTimer) {
		levelTimer.reset();
		levelTimer.start();
	}


}

// Displays the timer on the game screen
void Game::displayTimer() {
	Point timerPos = Point(68, 0);
	gotoxy(timerPos); // Set cursor to a fixed position on the screen
	long long seconds = levelTimer.elapsedSeconds();
	long long minutes = seconds / 60;
	seconds %= 60;
	if (!isSilent) {
		std::cout << "Time: " << minutes << "m " << seconds << "s" << std::flush;

	}
}

// Checks if time limit has been reached
void Game::checkTimeLimit() {
	if (levelTimer.elapsedSeconds() >= LEVEL_TIME_LIMIT) {
		system("cls"); // Clear the screen
		std::cout << "Time's up! You failed to complete the level in time." << std::endl;
		lives--;
		Sleep(3000); // Pause to let the player read the message
		BackToBeginning(); // Reset the level
	}
}

// Resets and prepares the game state for the next level, e.g., clearing objects or resetting positions.
void Game::endLevel(const std::string& filename) {

	board.reset();
	for (auto& barrel : barrels) {
		if (!isSilent) {
			barrel.erase();
		}
	}
	barrels.clear();
	frameCount = 0;
	activeBarrels = 0;
	if (!isSilent) {
		mario.erase();

		for (auto& ghost : ghosts) {
			ghost->erase();
		}
	}
	ghosts.clear();
	board.resetGhostCount();
	if (!isSilent) {
		hammer.erase();
		mario.erase();
	}
	system("cls");
	std::cout.flush();
	if (board.isHammerAvailable() && useTimer) {
		board.resetHammer();
	}
}

// Sets up the game at the beginning of a level. This includes resetting Mario's position, initializing barrels, ghosts, and other elements like the hammer.
void Game::initializeGame(const std::string& filename) {

	position1 = Point(board.getLegendPos());
	gotoxy(position1); //move cursor to the position
	if (!isSilent) {
		board.setTextColors(LIGHT_CYAN);
		std::cout << " Lives: " << lives << "  Score: " << mario.getScore() << std::flush;
	}

	mario.resetPosition(board.getMarioStartPos());
	mario.setBoard(board); //set board for mario
	barrels.reserve(MAX_BARRELS); //save space for barrels
	ghosts.reserve(MAX_GHOSTS);

	// Reset and draw the hammer
	if (board.isHammerAvailable()) {

		hammer = Hammer(board.getHammerPosition());
		if (!isSilent) { hammer.draw(); }
	}
	resetGhosts();
	if (board.checkTopRightFree() && useTimer) {
		levelTimer.start();
	}
	board.setTextColors(WHITE);
}

// Handles key presses during the game.
bool Game::getKey(char* key) {
	if (_kbhit()) {
		char key1 = _getch();
		if (key1 == ESC) {
			// If the game is paused
			if (!isPaused) {
				isPaused = true;
				system("cls");
				std::cout << "The game has been paused. Press ESC again to continue." << std::endl;

				while (_getch() != ESC) {

				}
				system("cls");
				board.print();
				isPaused = false;

			}
		}
		else {
			mario.keyPressed(key1, barrels, ghosts);
			*key = key1;
			return true;
		}
		return false;

	}

}

// Populates the given vector with the names of level files (e.g., ".screen" files) in the current directory.
void Game::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) {

	namespace fs = std::filesystem;

	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 6) == "dkong_" && filename.extension() == ".screen") {
			vec_to_fill.push_back(filenameStr);

		}
	}

	return;
}

// Displays a menu for the player to choose the starting level and returns the chosen level's index.
size_t Game::chooseStartingLevel(const std::vector<std::string>& fileNames) {
	system("cls");
	std::cout << "Select the starting level:\n";
	for (size_t i = 0; i < fileNames.size(); ++i) {
		std::cout << i + 1 << ". " << fileNames[i] << "\n";
	}

	size_t choice = 0;
	while (true) {
		std::cout << "Enter a number (1-" << fileNames.size() << "): ";
		std::cin >> choice;
		if (choice >= 1 && choice <= fileNames.size()) {
			system("cls");
			break;
		}
		std::cout << "Invalid choice. Please try again.\n";
	}
	return choice - 1;
}


// Moves all active barrels, handles collisions with Mario, and removes exploded barrels.
void Game::updateBarrels() {
	for (auto& barrel : barrels) {
		if (!isSilent) {
			barrel.erase();
		}

		barrel.move();
		if (barrel.isExplosion()) {
			barrel.explode(isSilent);
			if (barrel.checkCollisionWithMario(mario.getPosition(), COLLISION_DISTANCE)) {
				lives--; //reduce lives if barrel collides with Mario
				BackToBeginning();
				break;
			}
			// remove the barrel after explosion
			for (auto it = barrels.begin(); it != barrels.end(); ++it) {
				if (&(*it) == &barrel) {  //compare the object address
					barrels.erase(it);    //if we found the barrel, we will delete it
					activeBarrels--;      //update the number of active barrels
					break;
				}
			}
			if (!isSilent) {
				barrel.erase();
			}
		}
		else {
			if (!isSilent) {
				board.setTextColors(LIGHT_RED);
				barrel.draw();
			}
			board.setTextColors(WHITE);
			//handle collision with Mario
			if (barrel.checkCollisionWithMario(mario.getPosition(), 1)) {
				lives--;
				BackToBeginning();
				break;

			}
		}
		//checks if mario is dead and therefore lost
		if (lives <= 0)
		{
			if (!isSilent) {
				displayLossMessage();
			}
			return;
		}


	}

}

// Moves all ghosts, handles collisions with Mario, and redraws them in their new positions.
void Game::updateGhosts() {
	for (auto& ghost : ghosts) {
		if (!isSilent) {
			ghost->erase();
		}
		ghost->move(ghosts);
		
		board.setTextColors(LIGHT_BLUE);
		ghost->setMarioPos(mario.getPosition());
			if (!isSilent) {
				ghost->draw();
			}
		board.setTextColors(WHITE);
		// Handle collision with Mario
		if (ghost->checkCollisionWithMario(mario.getPosition(), GHOST_COLLISION)) {
			lives--;
			BackToBeginning();
			break;
		}

	}
}

// Adds to the game new barrel.
void Game::addBarrel() {
	if (frameCount % NEW_BARREL_INTERVAL == 0 && activeBarrels < MAX_BARRELS) {
		Barrel::FloorDirection direction = (frameCount % 2 == 0) ? Barrel::FloorDirection::Left : Barrel::FloorDirection::Right;
		Point startPosition;
		if (direction == Barrel::FloorDirection::Left) {
			startPosition = board.getbarrelStartPosLeft();
		}
		else {
			startPosition = board.getbarrelStartPosRight();
		}

		barrels.emplace_back(board, startPosition, direction); //adds new barrel
		activeBarrels++; //increase active barrel count
	}
}

// Resets all ghosts to their starting positions and directions for a new level.
void Game::resetGhosts() {
	// Clear existing ghosts
	for (Ghost* ghost : ghosts) {
		delete ghost;
	}
	ghosts.clear();

	for (int i = 0; i < board.numberGhosts(); i++) {
		Board::GhostData ghostData = board.getGhostPositions()[i]; // Read both position and type

		if (ghostData.type == 'x') {
			ghosts.push_back(new BasicGhost(board, ghostData.position, Ghost::Direction::Left));
		}
		else if (ghostData.type == 'X') {
			ghosts.push_back(new ClimbingGhost(board, ghostData.position, Ghost::Direction::Left));
		}
	}
}



// Updates Mario's position.
bool Game::updateMario(const std::string& filename) {
	if (!isSilent) {
		mario.erase();
	}
	mario.move();
	if (mario.loseLives)
	{
		lives--;
		BackToBeginning();
		if (lives <= 0)
		{
			if (!isSilent) {
				displayLossMessage();
			}
			return false;
		}
		mario.loseLives = false; //resets
		return false;
	}
	return true;
}

// Updates the hammer state, checks if Mario collects it, and redraws it if necessary.
void Game::updateHammer() {
	// Draw the hammer if not collected
	if (!hammer.collect(mario.getPosition())) {
		if (!isSilent) {
			board.setTextColors(BLUE);
			hammer.draw();
		}

	}
	else {
		// Mario collects the hammer
		mario.collectHammer();

		hammer.erase();
	}
	board.setTextColors(WHITE);
}


Game::Game()
	: mario(), board(), hammer(Point(20, 23)), lives(3), isPaused(false), isGameOver(false), frameCount(0), activeBarrels(0), position1(0, 0) {
	// Initialize other member variables or data structures here if needed
	barrels.reserve(MAX_BARRELS);
	ghosts.reserve(MAX_GHOSTS);
}

//main game loop
void Game::runGame(const bool colors, const bool Timer) {
	mario.setIsSilent(isSilent);
	useColorsInGame = colors;
	useTimer = Timer;
	//continues while mario still have lives
	while (lives > 0)
	{
		board.setTextColors(WHITE);
		ShowConsoleCursor(false);
		std::vector<std::string> fileNames;

		getAllBoardFileNames(fileNames);
		if (fileNames.empty()) {
			displayErrorMessage(board.getErrorMessage());
			return;
		}
		size_t startLevel = chooseStartingLevel(fileNames);

		for (size_t i = startLevel; i < fileNames.size(); ++i) {
			board.load(fileNames[i], colors);
			if (board.getInvalidbord()) {
				displayErrorMessage(board.getErrorMessage());
				return;
			}
			board.reset();
			if (!isSilent) { board.print(); }
			Board* gBoard = nullptr;

			//initialize the board and position for Mario and other game eleme
			initializeGame(fileNames[i]);

			//start of game loop
			while (true) {

				//victory
				if (mario.isPauline()) {
					if (!isSilent) {
						displayVictoryMessage();
					}
					break;
				}
				if (board.checkTopRightFree() && useTimer) {
					board.setTextColors(LIGHT_CYAN);
					displayTimer();  // Display the timer on the screen
					checkTimeLimit(); // Check if the level time is exceeded
					board.setTextColors(WHITE);
				}

				if (!isSilent) {
					board.setTextColors(LIGHT_YELLOW);
					mario.draw();
				}
				board.setTextColors(WHITE);
				//pause
				char key;
				getKey(&key);

				if (board.isHammerAvailable()) {

					updateHammer();
				}

				//move and draw existing barrels

				updateBarrels();

				updateGhosts();

				// Check if Mario is dead and therefore lost
				if (lives <= 0) {
					if (!isSilent) {
						displayLossMessage();
					}
					return;
				}

				// Add new barrel every NEW_BARREL_INTERVAL frames
				addBarrel();


				frameCount++;
				if (!isSilent) {
					Sleep(SLEEP_DURATION); //delay 
				}
				// Mario update
				updateMario(fileNames[i]);
				// Update life number
				board.setTextColors(LIGHT_CYAN);
				gotoxy(position1);
				if (!isSilent) {
					std::cout << " Lives: " << lives << "  Score: " << mario.getScore() << std::flush;
				}
				board.setTextColors(WHITE);


			}
			if (!isSilent) {
				Sleep(SLEEP_DURATION);
			}
			endLevel(fileNames[i]);


			if (i == fileNames.size() - 1) {
				// This is the last level, exit to menu
				if (!isSilent) {
					system("cls");
					displayEndAllGameWin();
				}
				return;  // Exit the game and go back to menu
			}
		}
	}

}
