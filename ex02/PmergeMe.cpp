#include "PmergeMe.hpp"

bool isNumber(const char* str) {
	for (size_t i = 0; i < std::strlen(str); ++i) {
		if (!std::isdigit(static_cast<unsigned char>(str[i])))
			return 0;
	}
	return 1;
}

std::vector<int> PmergeMe::genJacobsthal(int n) {
	std::vector<int> jacobsthal;
	
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	jacobsthal.push_back(1);
	for (int i = 3; jacobsthal[i - 1] < n; ++i) {
		jacobsthal.push_back(jacobsthal[i - 1] + 2 * jacobsthal[i - 2]);
	}
	return jacobsthal;
}

void merge(std::vector<int>& v, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<int> L(n1), R(n2);
	for (int i = 0; i < n1; ++i)
		L[i] = v[left + i];
	for (int j = 0; j < n2; ++j)
		R[j] = v[mid + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			v[k] = L[i];
			i++;
		} else {
			v[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		v[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		v[k] = R[j];
		j++;
		k++;
	}
}

void binaryInsertionSort(std::vector<int>& v, int i) {
	
}

void PmergeMe::mergeSort(std::vector<int>& v, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(v, left, mid);
		mergeSort(v, mid + 1, right);
		merge(v, left, mid, right);
	}
}

void PmergeMe::loadContainers(char** input, int count, std::vector<int>& vec, std::deque<int>& deq) {
	for (int i = 0; i < count; ++i) {
		double value = std::atof(input[i]);
		if (value > INT_MAX || value < 0 || !isNumber(input[i])) {
			std::cerr << "Error: Value out of range" << std::endl;
			exit(EXIT_FAILURE);
		}
		vec.push_back(value);
		deq.push_back(value);
	}
}

std::vector<std::pair<int, int> > sortPairs(std::vector<int>& v) {
	std::vector<std::pair<int, int> > result;

	std::vector<int>::iterator it = v.begin();
	for (; it + 1 < v.end(); it += 2) {
		if (*(it + 1) > *it)
			std::iter_swap(it, it + 1);
	}
	for (size_t i = 0; i + 1 < v.size(); i += 2) {
		result.push_back(std::make_pair(v[i], v[i + 1]));
	}
	if (v.size() % 2)
		result.push_back(std::make_pair(-1, v[v.size() - 1]));
	return result;
}

// void mergeSort(std::vector<int>& v) {

// }

void PmergeMe::sortVector(std::vector<int>& v) {
	std::vector<std::pair<int, int> > pairedV = sortPairs(v);
}

// static void sortDeque(std::vector<int>& d) {

// }

template <typename T>
void PmergeMe::printContainer(const T& cont) {
	typename T::const_iterator it;
	for (it = cont.begin(); it != cont.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}
template void PmergeMe::printContainer<std::vector<int> >(const std::vector<int>&);
template void PmergeMe::printContainer<std::deque<int> >(const std::deque<int>&);

