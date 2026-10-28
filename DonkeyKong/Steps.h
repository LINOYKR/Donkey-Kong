#pragma once

#include <list>

class Steps
{
	long randomSeed = 0;
	std::list<std::pair<size_t, char>> steps; // pair: iteration, step
public:
	static Steps loadSteps(const std::string& filename);  //A function that will load the steps from a file.
	void saveSteps(const std::string& filename) const;
	long getRandomSeed() const {
		return randomSeed;
	}
	void setRandomSeed(long seed) {
		randomSeed = seed;
	}
	//Adding a new step to the list
	void addStep(size_t iteration, char step) {
		steps.push_back({ iteration, step });
	}
	//Checks if the next step in the list belongs to a particular iteration
	bool isNextStepOnIteration(size_t iteration) const {
		return !steps.empty() && steps.front().first == iteration;
	}
	//Removes the first step in the list and returns the step value (which is a character)
	char popStep() {
		char step = steps.front().second;
		steps.pop_front();
		return step;
	}

	void clear() {
		steps.clear();
	}
};






