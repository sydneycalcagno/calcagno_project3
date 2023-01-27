#include "player.h"

#include <iostream>

using namespace std;


Player::Player() {
  	frustrationL = 0; 
  	comp_level = 100;
	cout << "What is your name?:";
	getline(cin, playerName);//in case someone puts lots of spaces and words 
	viruses = 0;
	hackersDefeated = 0;
}

Player::Player(int flevel, string pname){

    frustrationL = flevel; 
    playerName = pname; 

}
string Player::getPlayername(){

    return playerName; 

}
void Player::setPlayername(string pname){

    playerName = pname; 
}

int Player::getFrustration(){//frustration levels

    return frustrationL; 

} 
void Player::setFrustration(int flevel){

	if(flevel < 0) {
		flevel = 0;
	}	//stays in bounds
	if(flevel > 100){
		flevel = 100;
	}
    frustrationL = flevel; 

}

int Player::getHackersDefeated() {
	return hackersDefeated;
}

void Player::setHackersDefeated(int count) {
	hackersDefeated = count;
}

int Player::getCompHealth(){

	return comp_level;

}

void Player::setCompHealth(int value) {
	if(value < 0){
		value = 0;
	}					//stays in bounds
	if(value > 100){
	 value = 100;
	}
	comp_level = value; 
}

int Player::getViruses() { 
	return viruses; 
}

void Player::setViruses(int amount) { 
	viruses = amount;
}

Inventory& Player::getInv() { 
	return inv; 
}

