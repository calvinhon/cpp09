#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <utility>
#include <sys/time.h>

template <typename T>
void printContainer(const T& cont) {
	typename T::const_iterator it;
	for (it = cont.begin(); it != cont.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template <typename T>
T min(T a, T b) {
	return (a < b) ? a : b;
}

void parseInput(char** input, int count);

class VectorSort {
	public:
		static void sortVector(char** input, int elements);
		static void loadContainers(char** input, int count, std::vector<int>& vec);
		static std::vector<std::pair<int, int> > sortPairs(std::vector<int>& v);
		static void mergeSort(std::vector<std::pair<int, int> >& v, int left, int right);
		static void merge(std::vector<std::pair<int, int> >& v, int left, int mid, int right);
		static std::vector<size_t> genJacobsthal(size_t n);
		static void binaryInsertionSort(std::vector<int>& mainChain, std::vector<int>& pend);

	private:
		VectorSort();
		VectorSort(const VectorSort& src);
		VectorSort& operator=(const VectorSort& src);
		~VectorSort();
};


class ListSort {
	public:
		static void sortList(char** input, int elements);
		static void loadContainers(char** input, int count, std::list<int>& vec);
		static std::list<std::pair<int, int> > sortPairs(std::list<int>& v);
		static void mergeSort(std::list<std::pair<int, int> >& v, int left, int right);
		static void merge(std::list<std::pair<int, int> >& v, int left, int mid, int right);
		static std::list<int> genJacobsthal(int n);
		static void binaryInsertionSort(std::list<int>& mainChain, std::list<int>& pend);

	private:
		ListSort();
		ListSort(const ListSort& src);
		ListSort& operator=(const ListSort& src);
		~ListSort();
};

#endif