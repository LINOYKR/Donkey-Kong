#include "LoadGame.h"


void reportResultError(const std::string& message, const std::string& filename, size_t iteration) {
	system("cls");
	std::cout << "Screen " << filename << " - " << message << '\n';
	std::cout << "Iteration: " << iteration << '\n';
	std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	_getch();
}


// Sets up the game at the beginning of a level. This includes resetting Mario's position, initializing barrels, ghosts, and other elements like the hammer.
void LoadGame::initializeGame(const std::string& filename) {

	filename_prefix = filename.substr(0, filename.find_last_of('.'));
	stepsFilename = filename_prefix + ".steps";
	resultsFilename = filename_prefix + ".result";

	steps = Steps::loadSteps(stepsFilename);
	random_seed = steps.getRandomSeed();
	results = Results::loadResults(resultsFilename);
	score = getMario().getScore();
	srand(random_seed);

	Game::initializeGame(filename);
}

// Handles key presses during the game.
bool LoadGame::getKey(char* key) {
	iteration++;
	if (steps.isNextStepOnIteration(iteration)) {
		getMario().keyPressed(steps.popStep(), getBarrels(), getGhosts());
	}
	return true;
}

// Updates Mario's position.
bool LoadGame::updateMario(const std::string& filename) {
	score = getMario().getScore();
	if (!Game::updateMario(filename)) {
		// check if the result is correct
		if (results.popResult() != std::tuple{ iteration, Results::lostLife,score }) {
			reportResultError("Results file doesn't match lost life event!", filename, iteration);
			unmatching_result_found = true;
		}
		nextlostLifeIteration = results.getNextLostLifeIteration();
	}
	else {
		// we didn't lost life, so we check if the result is correct
		if (iteration == nextlostLifeIteration) {
			reportResultError("Results file has a lost life event that didn't happen!", filename, iteration);
			unmatching_result_found = true;
		}
	}

	return true;
}

// Resets and prepares the game state for the next level, e.g., clearing objects or resetting positions.
void LoadGame::endLevel(const std::string& filename) {

	Game::endLevel(filename);
	// check if the result is correct, but only if we didn't find an unmatching result already
	score = getMario().getScore();
	if (!unmatching_result_found) {
		if (results.popResult() != std::tuple{ iteration, Results::finished , score}) {
			reportResultError("Results file doesn't match finished event!", filename, iteration);
			unmatching_result_found = true;
		}
		if (std::get<1>(results.popResult()) != Results::noResult) {
			reportResultError("Results file has additional events after finish event!", filename, iteration);
			unmatching_result_found = true;
		}
	}

	iteration = 0;
}

// Displays a menu for the player to choose the starting level and returns the chosen level's index.
size_t LoadGame::chooseStartingLevel(const std::vector<std::string>& fileNames) {
	system("cls");
	size_t choice = 0;

	return choice;
}



LoadGame::LoadGame()
	: steps(), results(), iteration(0), score(0){
Game:Game();
}


