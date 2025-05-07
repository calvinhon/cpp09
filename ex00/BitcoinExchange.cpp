#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src): _db(src._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src) {
	if (this != &src)
		_db = src._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool	isValidDate(std::string date) {
	int	year = atoi(date.substr(0, 4).c_str());
	int	month = atoi(date.substr(5, 2).c_str());
	int day = atoi(date.substr(8,2).c_str());
	if (month < 1 || month > 12 || day < 1)
		return 0;
	static const int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int maxDay = daysInMonth[month - 1];
	if (month == 2 && (year % 4 == 0 && (year % 100 || !(year % 400))))
		maxDay = 29;
	return day <= maxDay;
}

void BitcoinExchange::loadDatabase() {
	int					line_index = 2;
	std::string 		line;
	double				value;
	std::ifstream		file("data.csv");
	if (!file.is_open())
		throw InvalidDbFile();

	std::getline(file, line);
	if (line != "date,exchange_rate") {
		std::cout << "[CSV 1]: ";
		throw InvalidLineFormat();
	}
	while (std::getline(file, line)) {
		if (line.length() < 12 || line[10] != ',') {
			std::cout << "[CSV " << line_index << "]: ";
			throw InvalidLineFormat();
		}
		std::string date = line.substr(0, 10);
		if (date[4] != '-' || date[7] != '-'
			|| std::count_if(date.begin(), date.end(), isdigit) != 8
			|| !isValidDate(date)) {
			std::cout << "[CSV " << line_index << "]: ";
			throw InvalidDate();
		}
		std::string			value_str = line.substr(11);
		std::istringstream	ss_value(value_str);
		ss_value >> value;
		if (ss_value.fail() || !ss_value.eof() || value < 0) {
			std::cout << "[CSV " << line_index << "]: ";
			throw InvalidValue();
		}
		_db[date] = value;
		line_index++;
	}
}

double	findValue(std::map<std::string, float> _db, std::string date) {
	std::map<std::string, float>::iterator it = _db.lower_bound(date);
	if (it != _db.end() && it->first == date)
		return it->second;
	else if (it != _db.begin()) {
		--it;
		return it->second;
	}
	else
		return -1;
}

void BitcoinExchange::parseInput(char *input) {
	int					line_index = 2;
	std::string 		line;
	std::string 		date;
	std::ifstream		file(input);
	if (!file.is_open())
		throw InvalidInputFile();

	std::getline(file, line);
	if (line != "date | value")
		std::cout << "[Input 1]: " << "invalid line format" << std::endl;
	while (std::getline(file, line)) {
		if (line.length() < 14 || line.substr(10, 3) != " | ")
			std::cout << "[Input " << line_index << "]: " << "invalid line format" << std::endl;
		else {
			date = line.substr(0, 10);
			if (date[4] != '-' || date[7] != '-'
				|| std::count_if(date.begin(), date.end(), isdigit) != 8
				|| !isValidDate(date))
				std::cout << "[Input " << line_index << "]: " << "invalid date" << std::endl;
			else if (line.length() > 13)
			{
				std::string numOfCoins_str = line.substr(13);
				std::istringstream	ss_value(numOfCoins_str);
				double	numOfCoins;
				ss_value >> numOfCoins;
				if (ss_value.fail() || !ss_value.eof())
					std::cout << "[Input " << line_index << "]: " << "invalid value" << std::endl;
				else if (numOfCoins < 0)
					std::cout << "[Input " << line_index << "]: " << "not a positive number" << std::endl;
				else if (numOfCoins > INT_MAX)
					std::cout << "[Input " << line_index << "]: " << "too large a number" << std::endl;
				else {
					double value = findValue(_db, date);
					if (value == -1)
						std::cout << "[Input " << line_index << "]: " << "date precedes earliest date in database" << std::endl;
					else
						std::cout << date << " => " << numOfCoins << " = " << numOfCoins * value << std::endl;;
				}
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
