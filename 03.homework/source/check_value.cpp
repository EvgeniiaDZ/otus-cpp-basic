#include "check_value.h"
#include <iostream>


int check_value (const int& target_value, int& attempts_count) {
	
	int current_value = 0;
	attempts_count = 0;
	
	std::cout << "Enter your guess:" << std::endl;

	do {
		std::cin >> current_value;
     	if (std::cin.fail()) {
			std::cout << "Bad value!" << std::endl;
			return -1;
		}
		
		++attempts_count;
		
		if (current_value > target_value) {
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value < target_value) {
			std::cout << "greater than " << current_value << std::endl;
		}
		else {
			std::cout << "you win!" << " " << "attempts = " << attempts_count << std::endl;
			break;
		}

	} while(true);

	return 0;
}