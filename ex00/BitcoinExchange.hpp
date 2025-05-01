#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <climits>

class BitcoinExchange {
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& src);
		BitcoinExchange& operator=(const BitcoinExchange& src);
		~BitcoinExchange();

		class InvalidDbFile: public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class InvalidInputFile: public std::exception {
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

		class InvalidLineFormat: public std::exception {
			public:
				virtual const char* what() const throw();
		};

	void	parseFile(std::string filename, int filetype);
	void	loadDatabase();
	void	parseInput(char *input);
	void	checkValue(std::string value);

	private:
		std::map<std::string, float> _db;
};

#endif