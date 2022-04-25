#include "high_scores.h"
#include <iostream>
#include <fstream>
#include <map>

const std::string high_scores_filename = "high_scores.txt";


int high_scores_add (std::string user_name, int attempts_count) {
    // We should open the output file in the append mode - we don't want
	// to erase previous results.
	std::ofstream out_file{high_scores_filename, std::ios_base::app};
	if (!out_file.is_open()) {
		std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
		return -1;
	}

	// Append new results to the table:
	out_file << user_name << ' ';
	out_file << attempts_count;
	out_file << std::endl;

	out_file.close();
	return 0;
}


int high_scores_print () {

	std::ifstream in_file{high_scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		return -1;
	}

	std::cout << "High scores table:" << std::endl;

	std::map <std::string, int> score_table;
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

		auto it = score_table.find(username);
		if (it != score_table.end()) {
			if (it->second > high_score) {
				score_table[username] = high_score; 
			}
		}
		else {
			score_table[username] = high_score;
		}
	}
	in_file.close();
	for (auto it = score_table.begin(); it != score_table.end(); ++it) {
		std::cout << it->first << '\t' << it->second << std::endl;
	}
	return 0;
}