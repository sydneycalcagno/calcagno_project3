#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>
#include <vector>

const std::string PUZZLE_FILE = "puzzles.txt"; //name the txt to be used
const std::string ANSWER_FILE = "answers.txt";

class Puzzle {
	
	public:
		Puzzle();
		bool doPuzzle();
	private:
		std::vector<std::string> puzzles;//std because didn't use using namespace
		std::vector<std::string> answers;

};

#endif