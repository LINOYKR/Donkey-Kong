#include <limits>
#include <fstream>

#include "Results.h"

//This function is responsible for loading the results from a file and constructing a Results object that contains the results.
Results Results::loadResults(const std::string& filename) {
	std::ifstream results_file(filename);
	Results results;
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		size_t score;
		results_file >> iteration >> result >> score;
		results.addResult(iteration, static_cast<ResultValue>(result), score);
	}
	return results;
}

//This function is responsible for saving the results to a file.
void Results::saveResults(const std::string& filename) const {
	std::ofstream results_file(filename);
	results_file << results.size();
	for (const auto& result : results) {
		results_file << '\n'
			<< std::get<0>(result) << ' '    // iteration
			<< std::get<1>(result) << ' '    // result
			<< std::get<2>(result);          // another_value
	}
	results_file.close();
}

//This function searches for the iteration in which the result lostLife occurred.
size_t Results::getNextLostLifeIteration() const {
	if (!results.empty() && std::get<1>(results.front()) == lostLife) {
		return std::get<0>(results.front());
	}
	else return std::numeric_limits<size_t>::max(); // a big number we will never reach
}
