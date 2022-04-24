#include "random_value.h"
#include "check_value.h"
#include "high_scores.h"

#include <iostream>
#include <string>


int argument_check_parameter_value(int argc, char** argv, int& value) {
    // Check arguments count.
    if (argc < 3) {
        std::cout << "Wrong usage! The argument requires some value!" << std::endl;
        return -1;
    }  
    if (argc >= 4) {
        std::cout << "Too much arguments!" << std::endl;
        return -1;
    }    
    // Parse the string to the int value.
    try {
        value = std::stoi(argv[2]);
    }
    catch(std::invalid_argument const& ex) {
        std::cout << "Error! Invalid_argument: " << argv[2] << " " << "should be a number" << '\n';
        return -1;
    }
    return 0;
}


int main (int argc, char** argv) {

    int target_value_max = 100;  // By default target max value is 100.

    // Check input parameters.
	if (argc >= 2) {
        std::string arg1_value{ argv[1] };
        if (arg1_value == "-max") { // Argument '-max' must have a value after itself.
            if (argument_check_parameter_value(argc, argv, target_value_max) != 0) {
                return -1;
            }
        }        
        else {
            std::cout << "Error! Invalid Parameter: " << "\'" <<argv[1] << "\'" << std::endl;
            return -1;
        }
    }

    // Start game.
    // Ask about name.
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;
    // Get random value.
    int target_value = random_value_get(target_value_max);
    int attempts_count = 0;

    if (check_value(target_value, attempts_count) != 0) {
        return -1;
    }

    if (high_scores_add(user_name, attempts_count ) != 0) {
        return -1;
    }

    std::cout << std::endl;
    if (high_scores_print() != 0) {
        return -1;
    }        
    
    return 0;
}