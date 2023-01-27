#include <iostream>
#include <fstream>
#include <cstdlib>
#include "game.h"
#include "hacker.h"
#include "player.h"
#include "inventory.h"
#include "split.h"

int Hacker::carmenProgress = 0;//start at 0

using namespace std;

Hacker::Hacker() {
	string name = ""; //constructor
	room = 1;
}

Hacker::Hacker(string name, int room) {
	this->name = name; //the name from private = copy name
	this->room = room;
}
   
int Hacker::getCarmensProgress() {
	return Hacker::carmenProgress;
}

void Hacker::setCarmensProgress(int prog) { 
	Hacker::carmenProgress = prog;
}

int Hacker::getRoom() { 
	return room;
}

void Hacker::setRoom(int rm){
	room = rm; 
}

void Hacker::setName(string hName) {
	name = hName;
}

string Hacker::getName() { 
	return name; 
}

void Hacker::loadHackers(Hacker* hackers, int count, int rm) {
	/* Pseudocode:
		open file
		int i = 0
		while reading (hackerName, roomNo) from file:
			if roomNo matches room:
				hackers[i].setRoom(roomNo)
				hackers[i].setName(hackerName)
				i++
				if(i >= count) break;
	*/
	
	ifstream myFile;
    myFile.open("hacker.txt");
    string line = "";
    string Hackers[2];
       
    //int split(string s, char sep, string words[], int max_words);
	int i = 0; 
    while(getline(myFile, line)){

    	split(line, ',', Hackers, 2);
    
     	string hackerName = Hackers[0];//assign name to hacker
    	string roomNo = Hackers[1];//assign room number to hacker

		if(stoi(roomNo) == rm){ //if match

			hackers[i].setRoom(rm); //set them
			hackers[i].setName(hackerName);

			i++;
		}
		if(i >= count){
			break; 
		}
    }
}

bool Hacker::fight(Player& player) {


		// Calculate the following variables:
		// o i = internet provider level that the user owns
		// o v = # of VPNs the player owns
		// o c = the room number of the hacker
		// o r1 = random number from 1 to 6
		// o r2 = random number from 1 to 6 (independent of r1)

		// If the result of the equation is greater than 0, the player wins the battle. If the result is
		// less than or equal to 0, the player loses
	int ipl = player.getInv().getIPlvl(); 
	int nVPN = player.getInv().getVPNs();
	int r1 = Game::getRand(1, 6);
	int r2 = Game::getRand(1, 6);

	double outcome = 0; 

	outcome = (r1 * ipl) - ((r2 * room) * (1/nVPN)); //equation for attack

	if(outcome > 0){//win!
		//player won- player gets 50 coins
		cout << "Good Job! You beat hacker: " << name << endl;
		cout << "You have been rewarded 50 Doge Coins!" << endl;
		player.getInv().setDogeCoins(player.getInv().getDogeCoins() + 50);//get 50
		player.setHackersDefeated(player.getHackersDefeated()+1);
	}
	else if(outcome <= 0){//lose
		//player lose- player loses 20 of their computer maintenance level and computer also has a 10% chance of being infected with a virus
		cout << "Better Luck Next Time..."<< endl; 
		cout << endl; 
		cout <<"You have lost 20 of your computers maintenance level" << endl; 
		player.setCompHealth(player.getCompHealth() - 20);
		if(Game::getRand(1, 10) <= 2) {//randomize

			cout << "You were also infected with a virus!" << endl;
			player.setViruses(player.getViruses()+1); //get a virus

		}
		Hacker::carmenProgress += 25;//add level
	}
	//After every battle, the player loses a computer part in the aftermath.
	if(room != 5) {//if it's not room 5...
	
		//And there is a 30% chance to lose 10 hp
		if(Game::getRand(0, 10) < 3) {
			cout << "You lost 10 computer maintenance level!" << endl;
			player.setCompHealth(player.getCompHealth() - 10);
		}
		int part = player.getInv().loseRandomPart();
		if(part != -1) {
			
			cout << "You lost a " << PART_NAMES[part] << "!" << endl;

			if(player.getInv().computerParts() < 1){
				cout << "You have no computer parts left!" << endl;
			}
		}
	}
	
	return outcome > 0;
}