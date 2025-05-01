#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src): _db(src._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src) {
	if (this != &src)
		_db = src._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void printLineIndex(int filetype, int line_index) {
	if (!filetype)
		std::cout << "[CSV ";
	else
		std::cout << "[Input ";
	std::cout << line_index << "]: ";
}

void BitcoinExchange::loadDatabase() {
	int					line_index = 2;
	std::string 		line;
	std::string 		date;
	std::string			value_str;
	float				value;
	std::ifstream		file("data.csv");
	if (!file.is_open())
		throw InvalidDbFile();

	std::getline(file, line);
	if (line != "date,exchange_rate") {
		printLineIndex(0, line_index);
		throw InvalidLineFormat();
	}
	while (std::getline(file, line)) {
		if (line.length() < 12 || line[10] != ',') {
			printLineIndex(0, line_index);
			throw InvalidLineFormat();
		}
		date = line.substr(0, 10);
		if (date[4] != '-' || date[7] != '-'
			|| std::count_if(date.begin(), date.end(), isdigit) != 8) {
			printLineIndex(0, line_index);
			throw InvalidDate();
		}
		value_str = line.substr(11);
		std::istringstream	ss_value(value_str);
		ss_value >> value;
		if (ss_value.fail() || !ss_value.eof()) {
			printLineIndex(0, line_index);
			throw InvalidValue();
		}
		_db[date] = value;
		line_index++;
	}
}

void BitcoinExchange::parseInput(char *input) {
	int					line_index = 2;
	std::string 		line;
	std::string 		date;
	std::string			numOfCoins_str;
	float				numOfCoins;
	std::ifstream		file(input);
	if (!file.is_open())
		throw InvalidInputFile();

	std::getline(file, line);
	if (line != "date | value") {
		printLineIndex(1, line_index);
		std::cout << "invalid line format" << std::endl;
	}
	while (std::getline(file, line)) {
		if (line.length() < 14 || line.substr(10, 3) != " | ") {
			printLineIndex(1, line_index);
			std::cout << "invalid line format" << std::endl;
		}
		else {
			date = line.substr(0, 10);
			if (date[4] != '-' || date[7] != '-'
				|| std::count_if(date.begin(), date.end(), isdigit) != 8) {
				printLineIndex(1, line_index);
				std::cout << "invalid date" << std::endl;
			}
			else if (line.length() > 13)
			{
				numOfCoins_str = line.substr(13);
				std::istringstream	ss_value(numOfCoins_str);
				ss_value >> numOfCoins;
				if (ss_value.fail() || !ss_value.eof()) {
					printLineIndex(1, line_index);
					std::cout << "invalid value" << std::endl;
				}
				else if (numOfCoins < 0) {
					printLineIndex(1, line_index);
					std::cout << "not a positive number" << std::endl;
				}
				else if (numOfCoins > INT_MAX) {
					printLineIndex(1, line_index);
					std::cout << "too large a number" << std::endl;
				}
				else
					std::cout << date << " => " << numOfCoins << " = " << numOfCoins << std::endl;;
			}
		}
		line_index++;
	}
}

const char* BitcoinExchange::InvalidDbFile::what() const throw() {
	return "Database file can't be opened or found";
}

const char* BitcoinExchange::InvalidInputFile::what() const throw() {
	return "Input file can't be opened or found";
}

const char* BitcoinExchange::InvalidDate::what() const throw() {
	return "invalid date";
}

const char* BitcoinExchange::InvalidValue::what() const throw() {
	return "invalid value";
}

const char* BitcoinExchange::InvalidLineFormat::what() const throw() {
	return "line format is invalid";
}
