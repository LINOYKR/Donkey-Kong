#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Barrel.h"
#include "Board.h"
#include "Hammer.h"
#include "Timer.h"
#include "BasicGhost.h"
#include "ClimbingGhost.h"

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <filesystem>



class Game {
private:
	static const long long LEVEL_TIME_LIMIT = 5 * 60; // 5 minutes in seconds
	Player mario;
	Board board;
	Point Pauline;
	Point position1;
	Hammer hammer;
	Timer levelTimer;
	bool isPaused;
	bool isGameOver = false;
	bool useTimer = true;
	bool useColorsInGame;
	int lives = 3;
	int frameCount = 0;
	int activeBarrels = 0;
	std::vector<Barrel> barrels;
	std::vector<Ghost*> ghosts;
	bool waitForInput = true;
	bool isSilent = false;


	void displayVictoryMessage();//displays victory screen
	void displayLossMessage();//displays loss screen
	void displayEndAllGameWin();//displays end all game win
	void displayErrorMessage(const std::string& errorDetails);//displays Error load Message

	void BackToBeginning();//restarts the level after losing a life

	void displayTimer();  // Displays the timer on the game screen
	void checkTimeLimit(); // Checks if time limit has been reached


	void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);//Get all level files


	void updateBarrels();// Moves all active barrels.
	void updateGhosts();// Moves all ghosts.
	void addBarrel();// Adds to the game new barrel.
	void resetGhosts();// Resets all ghosts.

	void updateHammer();//// Updates the hammer.

protected:
	virtual bool updateMario(const std::string& filename);// Updates Mario's position.
	virtual bool getKey(char* key);// Handles key presses during the game.
	virtual void initializeGame(const std::string& filename);	// Sets up the game at the beginning of a level
	virtual void endLevel(const std::string& filename);//resets end level
	virtual size_t chooseStartingLevel(const std::vector<std::string>& fileNames);//Choose the starting level

	Player& getMario() {
		return mario;
	}
	std::vector<Barrel>& getBarrels() { return barrels; }
	std::vector<Ghost*>& getGhosts() { return ghosts; }
	// Getter for isPaused
	bool getIsPaused() const {
		return isPaused;
	}

	// Setter for isPaused
	void setIsPaused(bool paused) {
		isPaused = paused;
	}

public:
	Game();
	~Game();

	//runs game
	void runGame(bool colors, bool timer);
	void setWaitForInput() { waitForInput = false; }
	void setSilentMode() { isSilent = true; }

};

#endif
