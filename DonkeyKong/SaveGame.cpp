#include "SaveGame.h"

// Sets up the game at the beginning of a level. This includes resetting Mario's position, initializing barrels, ghosts, and other elements like the hammer.
void SaveGame::initializeGame(const std::string& filename) {

	filename_prefix = filename.substr(0, filename.find_last_of('.'));
	stepsFilename = filename_prefix + ".steps";
	resultsFilename = filename_prefix + ".result";
	iteration = 0;
	random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
	steps.setRandomSeed(random_seed);
	srand(random_seed);
	score = getMario().getScore();
	Game::initializeGame(filename);
}

// Handles key presses during the game.
bool SaveGame::getKey(char* key) {
	char k;
	iteration++;
	if (Game::getKey(&k)) {
		steps.addStep(iteration, k);
	}
	return true;
}

// Updates Mario's position.
bool SaveGame::updateMario(const std::string& filename) {
	if (!Game::updateMario(filename))
	{
		score = getMario().getScore();
		results.addResult(iteration, Results::lostLife,score);
	}
	return true;
}
// Resets and prepares the game state for the next level, e.g., clearing objects or resetting positions.
void SaveGame::endLevel(const std::string& filename) {

	Game::endLevel(filename);
	score = getMario().getScore();
	results.addResult(iteration, Results::finished,score);
	steps.saveSteps(stepsFilename);
	results.saveResults(resultsFilename);
	iteration = 0;
	steps.clear();
	results.clear();
}


SaveGame::SaveGame()
	: steps(), results(), iteration(0), score(0){
Game:Game();
}

