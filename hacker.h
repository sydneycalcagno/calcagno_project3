#ifndef HACKER_H
#define HACKER_H

#include <string>
#include "player.h"

class Hacker {

public:

    Hacker();
	Hacker(std::string name, int room);
	static int getCarmensProgress();
	static void setCarmensProgress(int);
	//Load hackers into an array of size count from the hacker.txt file
	static void loadHackers(Hacker* hackers, int count, int room);
	int getRoom();
	void setRoom(int);
	std::string getName();
	void setName(string);
	bool fight(Player& player); //returns true on player win

private:

	static int carmenProgress; 
	std::string name;
	int room;
	

};

#endif