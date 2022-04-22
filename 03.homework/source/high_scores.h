#pragma once

#include <string>

// Write new high score to the records table
int high_scores_add (std::string user_name, int attempts_count);


// Read the high score file and print all results
int high_scores_print();