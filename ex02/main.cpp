#include "PmergeMe.hpp"

int	main(int ac, char** av) {
	if (ac == 1) {
		std::cout << "Input ./PmergeMe [sequence of positive integers]" << std::endl;
		return 1;
	}
	parseInput(av + 1, ac - 1);
	std::cout << "Before:\t";
	int i = 0;
	while (av[++i])
		std::cout << av[i] << " ";
	std::cout << std::endl;
	VectorSort::sortVector(av + 1, ac - 1);
	ListSort::sortList(av + 1, ac - 1);
	return 0;
}