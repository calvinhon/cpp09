#include "PmergeMe.hpp"

bool isNumber(const char* str) {
	for (size_t i = 0; i < std::strlen(str); ++i) {
		if (!std::isdigit(static_cast<unsigned char>(str[i])))
			return 0;
	}
	return 1;
}

void parseInput(char** input, int count) {
	for (int i = 0; i < count; ++i) {
		double value = std::atof(input[i]);
		if (value > INT_MAX || value <= 0 || !isNumber(input[i])) {
			std::cerr << "Error: Value out of range" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

// Vector Class
std::vector<size_t> VectorSort::genJacobsthal(size_t n) {
	std::vector<size_t> jacobsthal;
	
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	jacobsthal.push_back(1);
	for (int i = 3; jacobsthal[i - 1] < n; ++i) {
		jacobsthal.push_back(jacobsthal[i - 1] + 2 * jacobsthal[i - 2]);
	}
	return jacobsthal;
}

void VectorSort::binaryInsertionSort(std::vector<int>& mainChain, std::vector<int>& pend) {
	size_t	pendSize = pend.size();
	size_t	pendElementsAdded = 0;
	std::vector<size_t> Jacobsthal = genJacobsthal(pend.size());
	size_t	indexJ = 2;
	size_t	indexP = min(pendSize - 1, Jacobsthal[indexJ] - 1);
	while (pendElementsAdded != pendSize) {
		size_t	low = 0;
		size_t	high = mainChain.size();
		while (low < high) {
		size_t	mid = low + (high - low) / 2;
			if (pend[indexP] < mainChain[mid])
				high = mid;
			else
				low = mid + 1;
		}
		mainChain.insert(mainChain.begin() + low, pend[indexP]);
		if (indexP > 0 && indexP > Jacobsthal[indexJ - 1])
			indexP--;
		else {
			indexJ++;
			indexP = min(pendSize - 1, Jacobsthal[indexJ] - 1);
		}
		pendElementsAdded++;
	}
}

void VectorSort::merge(std::vector<std::pair<int, int> >& v, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<std::pair<int, int> > L(n1), R(n2);
	for (int i = 0; i < n1; ++i)
		L[i] = v[left + i];
	for (int j = 0; j < n2; ++j)
		R[j] = v[mid + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			v[k] = L[i];
			i++;
		}
		else {
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

void VectorSort::mergeSort(std::vector<std::pair<int, int> >& v, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(v, left, mid);
		mergeSort(v, mid + 1, right);
		merge(v, left, mid, right);
	}
}

std::vector<std::pair<int, int> > VectorSort::sortPairs(std::vector<int>& v) {
	std::vector<std::pair<int, int> > result;

	std::vector<int>::iterator it = v.begin();
	for (; it + 1 < v.end(); it += 2) {
		if (*(it + 1) > *it)
			std::iter_swap(it, it + 1);
	}
	for (size_t i = 0; i + 1 < v.size(); i += 2) {
		result.push_back(std::make_pair(v[i], v[i + 1]));
	}
	return result;
}

void VectorSort::loadContainers(char** input, int count, std::vector<int>& v) {
	for (int i = 0; i < count; ++i) {
		double value = std::atof(input[i]);
		v.push_back(value);
	}
}

void VectorSort::sortVector(char** input, int elements) {
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::vector<int> v;
	VectorSort::loadContainers(input, elements, v);
	std::vector<std::pair<int, int> > pairedV = sortPairs(v);
	mergeSort(pairedV, 0, pairedV.size() - 1);
	std::vector<int> mainChain, pend;
	for (size_t i = 0; i < pairedV.size(); ++i) {
		mainChain.push_back(pairedV[i].first);
		pend.push_back(pairedV[i].second);
	}
	if (v.size() % 2)
		pend.push_back(v[v.size() - 1]);
	binaryInsertionSort(mainChain, pend);
	gettimeofday(&end, NULL);
	std::cout << "After:\t";
	printContainer(mainChain);
	long duration_us = (end.tv_sec - start.tv_sec) * 1000000L +
                   (end.tv_usec - start.tv_usec);
	std::cout << "Time to process a range of " << elements << " elements with ";
	std::cout << "std::vector : " << duration_us << " us" << std::endl;
}

// List Class
size_t getNodeValue(std::list<int>::iterator it, int nodeChange) {
	if (nodeChange < 0)	
		while (nodeChange < 0) {
			--it;
			++nodeChange;
		}
	else 	
		while (nodeChange > 0) {
			++it;
			--nodeChange;
		}
	return *it;
}

std::list<int>::iterator getNode(std::list<int>::iterator it, int nodeChange) {
	if (nodeChange < 0)	
		while (nodeChange < 0) {
			--it;
			++nodeChange;
		}
	else 	
		while (nodeChange > 0) {
			++it;
			--nodeChange;
		}
	return it;
}

std::list<int> ListSort::genJacobsthal(int n) {
	std::list<int> jacobsthal;
	
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	jacobsthal.push_back(1);
	for (int i = 3; *(--jacobsthal.end()) < n; ++i) {
		std::list<int>::iterator it1 = --jacobsthal.end();
		std::list<int>::iterator it2 = --jacobsthal.end();
		--it2;
		jacobsthal.push_back(*it1 + 2 * *it2);
	}
	return jacobsthal;
}

void ListSort::binaryInsertionSort(std::list<int>& mainChain, std::list<int>& pend) {
	size_t	pendSize = pend.size();
	size_t	pendElementsAdded = 0;
	std::list<int> Jacobsthal = genJacobsthal(pend.size());
	size_t	indexJ = 2;
	size_t	itJ = getNodeValue(Jacobsthal.begin(), 2);
	size_t	indexP = min(pendSize - 1, itJ - 1);
	while (pendElementsAdded != pendSize) {
		size_t	low = 0;
		size_t	high = mainChain.size();
		while (low < high) {
		size_t	mid = low + (high - low) / 2;
			if (getNodeValue(pend.begin(), indexP) < getNodeValue(mainChain.begin(), mid))
				high = mid;
			else
				low = mid + 1;
		}
		mainChain.insert(getNode(mainChain.begin(), low), getNodeValue(pend.begin(), indexP));
		if (indexP > 0 && indexP > getNodeValue(Jacobsthal.begin(), indexJ - 1))
			indexP--;
		else {
			indexJ++;
			indexP = min(pendSize - 1, getNodeValue(Jacobsthal.begin(), indexJ) - 1);
		}
		pendElementsAdded++;
	}
}

void ListSort::merge(std::list<std::pair<int, int> >& v, int left, int mid, int right) {
	std::list<std::pair<int, int> >::iterator itL = v.begin();
	for (int i = 0; i < left; ++i)
		++itL;
	std::list<std::pair<int, int> >::iterator itR = v.begin();
	for (int i = 0; i < mid + 1; ++i)
		++itR;

	std::list<std::pair<int, int> > L, R;
	for (int i = 0; i < mid - left + 1; ++i) {
		L.push_back(*itL);
		++itL;
	}
	for (int i = 0; i < right - mid; ++i) {
		R.push_back(*itR);
		++itR;
	}

	std::list<std::pair<int, int> >::iterator itV = v.begin();
	for (int i = 0; i < left; ++i)
		++itV;

	std::list<std::pair<int, int> >::iterator itL2 = L.begin();
	std::list<std::pair<int, int> >::iterator itR2 = R.begin();
	while (itL2 != L.end() && itR2 != R.end()) {
		if (*itL2 <= *itR2) {
			*itV = *itL2;
			++itL2;
		} else {
			*itV = *itR2;
			++itR2;
		}
		++itV;
	}
	while (itL2 != L.end()) {
		*itV = *itL2;
		++itV;
		++itL2;
	}
	while (itR2 != R.end()) {
		*itV = *itR2;
		++itV;
		++itR2;
	}
}

void ListSort::mergeSort(std::list<std::pair<int, int> >& v, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(v, left, mid);
		mergeSort(v, mid + 1, right);
		merge(v, left, mid, right);
	}
}

std::list<std::pair<int, int> > ListSort::sortPairs(std::list<int>& v) {
	std::list<std::pair<int, int> > result;

	std::list<int>::iterator it = v.begin();
	while (getNode(it, 1) != v.end()) {
		if (getNodeValue(it, 1) > static_cast<size_t>(*it))
			std::iter_swap(it, getNode(it, 1));
		++it;
		++it;
		if (getNode(it, 0) == v.end())
			break ;
	}
	it = v.begin();
	for (size_t i = 0; i + 1 < v.size(); i += 2)
		result.push_back(std::make_pair(getNodeValue(it, i), getNodeValue(it, i + 1)));
	return result;
}

void ListSort::loadContainers(char** input, int count, std::list<int>& v) {
	for (int i = 0; i < count; ++i) {
		double value = std::atof(input[i]);
		v.push_back(value);
	}
}

void ListSort::sortList(char** input, int elements) {
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::list<int> v;
	ListSort::loadContainers(input, elements, v);
	std::list<std::pair<int, int> > pairedV = sortPairs(v);
	mergeSort(pairedV, 0, pairedV.size() - 1);
	std::list<int> mainChain, pend;
	std::list<std::pair<int, int> >::iterator it = pairedV.begin();
	for (size_t i = 0; i < pairedV.size(); ++i) {
		mainChain.push_back(it->first);
		pend.push_back(it->second);
		++it;
	}
	if (v.size() % 2) {
		std::list<int>::iterator it = v.begin();
		pend.push_back(getNodeValue(it, v.size() - 1));
	}
	binaryInsertionSort(mainChain, pend);
	gettimeofday(&end, NULL);
	long duration_us = (end.tv_sec - start.tv_sec) * 1000000L +
                   (end.tv_usec - start.tv_usec);
	std::cout << "Time to process a range of " << elements << " elements with ";
	std::cout << "std::list   : " << duration_us << " us" << std::endl;
}
