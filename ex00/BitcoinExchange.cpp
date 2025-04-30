#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src): _db(src._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src) {
	if (this != &src)
		_db = src._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::map<std::string, float> BitcoinExchange::loadDatabase(const std::string& filename) {
	std::map<std::string, float> db;
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw InvalidFile();
	std::string line;

	std::getline(file, line);
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::string date;
		std::string value;
		int			len = value.size();
		if (!std::getline(ss, date, ',') || date.length() != 10
			|| date[4] != '-' || date[7] != '-'
			|| std::count_if(date.begin(), date.end(), isdigit) != 8)
			throw InvalidDate();
		if (!std::getline(ss, value)
			|| (std::count(value.begin(), value.end(), '.') == 1
				&& std::count_if(value.begin(), value.end(), isdigit) != len - 1)
			|| std::count_if(value.begin(), value.end(), isdigit) != len)
			throw InvalidValue();
		db[date] = std::atof(value.c_str());
	}
	return db;
}

const char* BitcoinExchange::InvalidFile::what() const throw() {
	return "File is invalid";
}

const char* BitcoinExchange::InvalidDate::what() const throw() {
	return "Date is invalid";
}

const char* BitcoinExchange::InvalidValue::what() const throw() {
	return "Value is invalid";
}
