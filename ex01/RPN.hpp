#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <iostream>
#include <cfloat>
#include <sstream>

class RPN {
	public:
		static void		execute(char *expr);
		static double	calculate(double a, double b, std::string op);

		class InvalidLength: public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class InvalidOperand: public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class InvalidOperator: public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class DivisionByZero: public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class ResultOutOfBounds: public std::exception {
			public:
				virtual const char* what() const throw();
		};

	private:
		RPN();
		RPN(const RPN& src);
		RPN& operator=(const RPN& src);
		~RPN();	
};

#endif