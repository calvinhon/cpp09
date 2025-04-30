#include "BitcoinExchange.hpp"

int main(int ac, char** av) {
	if (ac != 2) {
		std::cout << "Input ./btc [file.txt]" << std::endl;
		return 1;
	}
	try {
		BitcoinExchange bibycoin;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}