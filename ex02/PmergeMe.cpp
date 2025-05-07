#include "PmergeMe.hpp"

void PmergeMe::loadContainers(char** input, int count, std::vector<int>& vec, std::deque<int>& deq) {
	for (int i = 0; i < count; ++i) {
		double value = std::atof(input[i]);
		if (value > INT_MAX || value < 0) {
			std::cerr << "Error: Value out of range" << std::endl;
			exit(EXIT_FAILURE);
		}
		vec.push_back(value);
		deq.push_back(value);
	}
}

template <typename T>
void PmergeMe::printContainer(const T& cont) {
	typename T::const_iterator it;
	for (it = cont.begin(); it != cont.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}
template void PmergeMe::printContainer<std::vector<int> >(const std::vector<int>&);
template void PmergeMe::printContainer<std::deque<int> >(const std::deque<int>&);

