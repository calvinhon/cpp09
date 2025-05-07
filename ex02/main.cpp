#include "PmergeMe.hpp"

int	main(int ac, char** av) {
	if (ac == 1) {
		std::cout << "Input ./PmergeMe [sequence of positive integers]" << std::endl;
		return 1;
	}
	std::vector<int>	vec;
	std::deque<int>		deq;
	PmergeMe::loadContainers(av + 1, ac - 1, vec, deq);
	std::cout << "Before:\t";
	PmergeMe::printContainer(vec);

	std::cout << "After:\t";
	PmergeMe::printContainer(vec);
	std::cout << "\033[34mTime to process a range of " << ac - 1 << " elements with\033[0m" << std::endl;
	std::cout << "std::vector :\t" << "us" << std::endl;
	std::cout << "std::deque  :\t" << "us" << std::endl;
	return 0;
}