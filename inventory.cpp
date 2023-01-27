#include "game.h"
#include "inventory.h"
#include <iostream>

using namespace std; 
Inventory::Inventory() {
	dogecoins = 200;
	computers = 1;
	IPlvl = 1;
	VPNs = 1;
	USB = 0; 
	for(int i=0; i<6; i++){
		parts[i] = 0;
	}
}

int Inventory::getDogeCoins() {
	return dogecoins;
}

int Inventory::getIPlvl() {
	return IPlvl;
}

int Inventory::getVPNs() {
	return VPNs;
}

int Inventory::getPart(int i) {
	return parts[i];
}

void Inventory::setDogeCoins(int coins) {
	dogecoins = coins; 
}

void Inventory::setIPlvl(int lvl) { 
	IPlvl = lvl; 
}

void Inventory::setVPNs(int vpns) { 
	VPNs = vpns; 
}

void Inventory::setPart(int i, int count) {
	parts[i] = count;
}

int Inventory::computerParts() {
	int count = 0;

	for(int i=0; i<6; i++){ //refers to part array
		count += parts[i];//sees how many parts there are
	}
	
	return count;
}

int Inventory::gainRandomPart() {
	if(computerParts() >= 18){
		return -1;//use -1 for other parts of code when using fucntion
	}
	int part;
	//Loop until found a part that is not capped
	do {
		part = Game::getRand(0, 6);

	} while(getPart(part) >= 3);

	setPart(part, getPart(part)+1); //add another part of part (ex gpu was at one and now two)
	return part;

}

int Inventory::loseRandomPart() {
	if(computerParts() < 1){
		return -1;
	}
	int part;
	do {

		part = Game::getRand(0, 6);

	} while(getPart(part) <= 0); //randomize until found exists

	setPart(part, getPart(part)-1);//lose a part from that certain part (ex gpu was at one and now zero)
	return part;
}

int Inventory::getComputers() {
	return computers; 
}

void Inventory::setComputers(int comps) { 
	computers = comps; 
}
int Inventory::getAntivirus(){
	return USB; 
}
void Inventory::setAntivirus(int usb){
	USB = usb; 
}

void Inventory::printInventory() {
	using namespace std;
	
	cout << "You have " << getComputers() << " computer(s), "; //computers 
	cout << computerParts() << " computer part(s), "; //computer PARTS
	cout << getAntivirus() << " antivirus software USB stick(s), "; // antivirus softwares
	cout << getVPNs() << " VPN(s), "; //vpns
	cout << "level "<<getIPlvl() << " internet provider, "; //level of internet provider
	cout << getDogeCoins() << " dogecoins";// money (doge coins)
	//cout << "level " << player.getFrustration() << " of frustration." <<endl; 
	cout << endl; 
}
