#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <utility>

class PmergeMe {
	public:
		static void loadContainers(char** input, int count, std::vector<int>& vec, std::deque<int>& deq);
		static void sortVector(std::vector<int>& v);
		// static void sortDeque(std::vector<int>& d);
		static void mergeSort(std::vector<int>& v, int left, int right);
		static std::vector<int> genJacobsthal(int n);
		
		template <typename T>
		static void printContainer(const T& cont);

	private:
		PmergeMe();
		PmergeMe(const PmergeMe& src);
		PmergeMe& operator=(const PmergeMe& src);
		~PmergeMe();
};

#endif