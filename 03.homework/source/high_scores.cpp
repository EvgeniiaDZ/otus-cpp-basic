#include "high_scores.h"
#include <iostream>
#include <fstream>
#include <map>

const std::string high_scores_filename = "high_scores.txt";


int high_scores_add (std::string user_name, int attempts_count) {
    // We should open the output file to use position cursor
	std::fstream file{high_scores_filename, std::fstream::in | std::fstream::out \
	 | std::ios_base::in | std::ios_base::out};
	
	if (!file.is_open()) {
		std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
		return -1;
	}	

	std::string user_name_f;
	int high_score = 0;	
	bool is_change_score = false;
	while (true) {
		auto cur_pos = file.tellg();
		// Read the username first
		file >> user_name_f;
		// Read the high score next
		file >> high_score;
		// Ignore the end of line symbol
		file.ignore();
		if (file.fail()) {
			break;
		}
		// If there is such user name and new score is better, it should be overwritten
		if (user_name_f == user_name) {
			if (attempts_count < high_score) {
				file.seekp(cur_pos);
				file << user_name << ' ' << attempts_count << std::endl;
			}			
			is_change_score = true;
			break;
		}
	}
	// If there are no such user name add new score
	if (is_change_score == false) {
		file.clear();
		file << user_name << ' ' << attempts_count << std::endl;
	}
	file.close();
	return 0;
}


int high_scores_print () {

	std::ifstream in_file{high_scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		return -1;
	}

	std::cout << "High scores table:" << std::endl;
	std::string username;
	int high_score = 0;
	while (true) {
		// Read the username first
		in_file >> username;
		// Read the high score next
		in_file >> high_score;
		// Ignore the end of line symbol
		in_file.ignore();

		if (in_file.fail()) {
			break;
		}

		// Print the information to the screen
		std::cout << username << '\t' << high_score << std::endl;
	}
	in_file.close();
	return 0;
}