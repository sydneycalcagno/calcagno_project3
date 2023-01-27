#ifndef GAME_H
#define GAME_H

#include "puzzle.h"
#include "Map.h"
#include "player.h"
#include "hacker.h"

#include <string>

class Game {

public:
	Game();
	~Game(); // deconstructor
	
	//Spawns hackers and NPCs and a Best Buy
	void initializeMap();
	//Get a random number between min and max, both inclusive
	static int getRand(int min, int max);
	void misfortune();
	bool isOver();
	void statusUpdate();
	void doTurn();
	void moveAround();
	void repairComputer();
	void useAntivirus();
	void visitStackOverflow();
	void speakToNPC();

	int getRandomHacker();
	bool fightHacker(int hackerToFight);
	void forfeitHacker(int hackerToFight);

	std::string getGameoverMsg();

	Player getPlayer();

private:
	Player player;
	Map map;
	Puzzle puzzle;
	int roomNumber; //Which server room we are in
	int hackersDefeated;
	bool game_over;
	Hacker* hackers; //List of hackers (array) in the room we're in
	int numHackers;
	string gameoverMsg; //Reason for game over

};

#endif