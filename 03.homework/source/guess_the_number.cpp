#include "random_value.h"
#include "check_value.h"
#include "high_scores.h"

#include <iostream>

int main() {

    // Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;
    
    int target_value = random_value_get();
    int attempts_count = 0;

    if (check_value(target_value, attempts_count) == -1) {
        return -1;
    }

    high_scores_add(user_name, attempts_count );
    std::cout << std::endl;
    high_scores_print();        
    
    return 0;
}