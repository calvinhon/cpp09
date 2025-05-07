#include "RPN.hpp"

int main(int ac, char** av) {
	if (ac != 2) {
		std::cout << "Input ./RPN [mathematical expression]" << std::endl;
		return 1;
	}
	try {
		RPN::execute(av[1]);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}