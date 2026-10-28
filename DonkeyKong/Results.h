#pragma once

#include <list>

class Results
{
public:
	enum ResultValue { lostLife, finished, noResult };
private:
	std::list<std::tuple<size_t, ResultValue,size_t>> results; // pair: iteration, result
public:
	static Results loadResults(const std::string& filename); //A function that loads the results from a file and returns a Results object with the results that were read.
	void saveResults(const std::string& filename) const;   //A function that saves all results to a file.
	//Adds a new result to the list.
	void addResult(size_t iteration, ResultValue result, size_t score) {
		results.push_back({ iteration, result,score });
	}
	//A function that removes the first result in a list and returns the pair (iteration, result).
	std::tuple<size_t, ResultValue, size_t> popResult() {
		if (results.empty()) return { 0, Results::noResult,0 };
		auto result = results.front();
		results.pop_front();
		return result;
	}
	//Checks whether the last result in the list refers to the iteration completed up to the given iteration. If the list is empty, the function returns true.
	bool isFinishedBy(size_t iteration) const {
		return results.empty() || std::get<0>(results.back()) <= iteration;
	}
	//The function that returns the iteration where Mario lost a life
	size_t getNextLostLifeIteration() const;

	void clear() {
		results.clear();
	}
};

