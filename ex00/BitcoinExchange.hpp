#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

class BitcoinExchange {
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& src);
		BitcoinExchange& operator=(const BitcoinExchange& src);
		~BitcoinExchange();

		class InvalidFile: public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class InvalidDate: public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class InvalidValue: public std::exception {
			public:
				virtual const char* what() const throw();
		};

		std::map<std::string, float> loadDatabase(const std::string& filename);

	private:
		std::map<std::string, float> _db;
};

#endif