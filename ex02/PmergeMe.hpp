#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>

class PmergeMe {
	public:
		static void loadContainers(char** input, int count, std::vector<int>& vec, std::deque<int>& deq);
		

		template <typename T>
		static void printContainer(const T& cont);

	private:
		PmergeMe();
		PmergeMe(const PmergeMe& src);
		PmergeMe& operator=(const PmergeMe& src);
		~PmergeMe();
};

#endif