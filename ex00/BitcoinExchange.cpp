#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src) {}

BitcoinExchange::~BitcoinExchange() {}

std::map<std::string, float> BitcoinExchange::loadDatabase(const std::string& filename) {
	std::map<std::string, float> db;
	std::ifstream file(filename.c_str());
	std::string line;

	std::getline(file, line);
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::string date;
		std::string value;
		if (std::getline(ss, date, ',') && std::getline(ss, value)) {
			db[date] = std::atof(value.c_str());
		}
	}
}

