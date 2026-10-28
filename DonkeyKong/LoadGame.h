#include "Game.h"
#include "Steps.h"
#include "Results.h"

class LoadGame : public Game {


private:
    Steps steps;
    Results results;
    long random_seed;

    std::string filename_prefix;
    std::string stepsFilename;
    std::string resultsFilename;

    size_t iteration = 0;
    size_t score = 0;

    size_t nextlostLifeIteration = 0;
    bool unmatching_result_found = false;


protected:

    virtual void initializeGame(const std::string& filename);	// Sets up the game at the beginning of a level
    bool getKey(char* k);// Handles key presses during the game.
    bool updateMario(const std::string& filename);// Updates Mario's position.
    void endLevel(const std::string& filename);//resets end level
    size_t chooseStartingLevel(const std::vector<std::string>& fileNames);//Choose the starting level
public:

    LoadGame();

};