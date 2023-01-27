#include "game.h"
#include "puzzle.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Puzzle::Puzzle() {

	ifstream inFile(PUZZLE_FILE);
	string line, puzzle = "";

	while(getline(inFile, line)) {
		if(line == "---") {//when the puzzles split up
			puzzles.push_back(puzzle);//put puzzle in array
			puzzle = "";
		}
		else {
			puzzle += line + '\n';
		}
	}
	inFile.close();
	inFile.open(ANSWER_FILE);

	while(getline(inFile, line)) {
		if(line != "---") { //get answer
			answers.push_back(line);
		}
	}
	inFile.close();
}

bool Puzzle::doPuzzle() {

	if(puzzles.size() < 1){
		return true;
	} 
	int puzzle = Game::getRand(0, puzzles.size());

	cout << puzzles[puzzle] << endl;//show puzzle in puzzle array
	cout << "Your choice:";
	string answer;
	getline(cin, answer);//get the answer

	if(answers[puzzle] == answer) { //if textfile answer and players answer matches
		cout << "You are correct!" << endl;//correct and true for bool (depending npc or stack overflow)
		return true;
	}
	cout << "Sorry, that is not the answer!" << endl;
	return false;
}