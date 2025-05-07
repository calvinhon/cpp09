#include "RPN.hpp"

double RPN::calculate(double a, double b, std::string op) {
	double value;

	if (op == "+") value = a + b;
	else if (op == "-") value = a - b;
	else if (op == "/") {
		if (!b) throw DivisionByZero();
		value = a / b;
	}
	else value = a * b;
	if (value > DBL_MAX || value < -DBL_MAX) throw ResultOutOfBounds();
	return value;
}

void RPN::execute(char *expr) {
	static std::stack<double> _s;
	std::istringstream iss(expr);
	std::string token;

	while (iss >> token) {
		if (!(token == "+" || token == "-" || token == "/" || token == "*")) {
			std::istringstream num(token);
			double value;
			if (num >> value) _s.push(value);
			else throw InvalidOperator();
		}
		else {
			if (_s.size() < 2) throw InvalidOperand();
			double b = _s.top(); _s.pop();
			double a = _s.top(); _s.pop();
			_s.push(calculate(a, b, token));
		}
	}
	if (_s.size() != 1)
		throw InvalidLength();
	std::cout << _s.top() << std::endl;
}

const char* RPN::InvalidLength::what() const throw() {
	return "Expression has an invalid length";
}

const char* RPN::InvalidOperand::what() const throw() {
	return "Expression has an invalid operand";
}

const char* RPN::InvalidOperator::what() const throw() {
	return "Expression has an invalid operator";
}

const char* RPN::DivisionByZero::what() const throw() {
	return "Expression has a division by zero";
}

const char* RPN::ResultOutOfBounds::what() const throw() {
	return "Expression has a result that is out of bounds for a double";
}
