#include "hacker.h"
#include "game.h"
#include "store.h"

#include <iostream>
#include <cstdlib>

using namespace std;

Game::Game() {
	game_over = false;
	//player constructor gets called - gets the player's name
	roomNumber = 1;
	visitBestBuy(player, 1, true);
	hackers = nullptr;
	initializeMap();
	Hacker::setCarmensProgress(0);
}

Game::~Game() {//removes hackers from array
	delete [] hackers;
}

Player Game::getPlayer() { 
	return player; 
}

void Game::initializeMap() { //parts from map driver

	hackersDefeated = 0;
    map.spawnBestBuy(getRand(0, 4), getRand(0, 8));

	int numHackers = getRand(1,3), numNPCs = getRand(1, 3);

    for(int i=0; i<numHackers; i++) {
		do {
			if(map.spawnHacker(getRand(0, 4), getRand(0, 8))){//spawn hackers at random
				break;
			}
		} while(true);
	}

	this->numHackers = numHackers;

	if(hackers != nullptr){
		delete [] hackers; //clear hackers from a previous room
	} 
	hackers = new Hacker[numHackers]; //new array

	Hacker::loadHackers(hackers, numHackers, roomNumber);

	for(int i=0; i<numNPCs; i++) {
		do {
			if(map.spawnNPC(getRand(0, 4), getRand(0, 8))){//spawn npc
				break;
			}
		} while(true);
	}
}

int Game::getRand(int min, int max) {
	return min + rand() % (max-min); //random function
}

void Game::statusUpdate() {
	
	Inventory& inv = player.getInv(); //make it so we can use .inv instead of player.getInv()

	cout << endl;
	cout << "Your computer's maintenance level is: " << player.getCompHealth() << endl;
	cout << "You have " << player.getViruses() << " virus(es)." << endl;
	cout << "Your frustration level is " << player.getFrustration() << endl;
	cout << "Carmen's progress is at " << Hacker::getCarmensProgress() << endl;
	cout << "You have defeated " << player.getHackersDefeated() << " hackers so far." << endl;
	cout << endl;
	inv.printInventory();
}

bool Game::isOver() {

	if(game_over) return true;
	string msg = "";//empty message

	if(player.getFrustration() >= 100) {
		game_over = true;
		msg += "OH NO! You have rage quit!\n";//assign message based on what happened
		msg += "Looks like you couldn't handle Carmen's hackers\n";
	}
	else if(player.getCompHealth() <= 0) {
		game_over = true;
		msg += "Unfortunately, your computer has died.\n";
	}
	else if(Hacker::getCarmensProgress() >= 100) {
		game_over = true;
		msg += "Carmen's hacker team succeeded in stealing all of the information!\n";
		msg += "Carmen wins!\n";
	}
	else if(roomNumber >= 5 && hackersDefeated > 0) {
		msg += "You showed those hackers who's boss and defeated Carmen!\n";
		msg += "You win!\n";
		game_over = true;
	}
	gameoverMsg = msg;//gameoverMsg is now what msg was assgined 
	return game_over;
}

std::string Game::getGameoverMsg() { 
	return gameoverMsg; 
}

void Game::doTurn() {

	
	cout << endl;
	//status update
	cout << "Player:" << player.getPlayername() << endl;
	cout << "Server room:" << roomNumber << endl;
	cout << "Hackers defeated:" << player.getHackersDefeated() << endl;
	cout << "Hackers defeated in this room:" << hackersDefeated << endl;
	cout << "Carmen's progress:" << Hacker::getCarmensProgress() << endl;
	cout << "Dogecoin:" << player.getInv().getDogeCoins() << endl;
	cout << endl;

	map.displayMap();//show map

	//Display options
	bool validOption[9];

	for(int i=0; i<6; i++){
		validOption[i] = false;
	} 
	//only pops up as needed
	if(map.isNPCLocation()) {
		cout << "1. Speak to the NPC" << endl;
		validOption[0] = true;
	}
	if(map.isBestBuyLocation()) {
		cout << "2. Enter Best Buy" << endl;
		validOption[1] = true;
	}
	if(player.getInv().computerParts() >= 1 && player.getCompHealth() < 100) {
		cout << "3. Repair your Computer" << endl;
		validOption[2] = true;
	}
	if(player.getViruses() > 0 && player.getInv().getAntivirus() > 0) {
		cout << "4. Use Antivirus" << endl;
		validOption[3] = true;
	}
	if(hackersDefeated > 0) {
		cout << "5. Move to next server room" << endl;
		validOption[4] = true;
	}
	//always here
	cout << "6. Move around" << endl;
	cout << "7. Visit StackOverflow" << endl;
	cout << "8. View your status" << endl;
	cout << "9. Quit game" << endl;

	//Loop until choice is valid
	//Status and quit are always valid
	char choice;
	do {
		cin >> choice;
		int choiceN = choice - '0'; //makes choice into an int
		if(choiceN < 1 || choiceN > 9 || (choiceN < 6 && !validOption[choiceN-1])) {
			cin.ignore(256, '\n');
			cout << "Invalid option! Please pick again:";
			cin.clear();
		}
		else {
			cin.ignore(256, '\n');
			break;
		}
	} while(true);

	switch(choice) {
		case '1': {
			speakToNPC();
			break;
		}
		case '2': {
			visitBestBuy(player, roomNumber);
			break;
		}
		case '3': {
			repairComputer();
			break;
		}
		case '4': {
			useAntivirus();
			break;
		}
		case '5': {

			roomNumber++;//new room level/number
			map.resetMap();//new map because new room
			initializeMap();
			break;

		}
		case '6': {
			moveAround();
			break;
		}
		case '7': {
			visitStackOverflow();
			break;
		}
		case '8': {
			statusUpdate();
			break;
		}
		case '9': {
			game_over = true;
			//cout << "You give up!" << endl;
			gameoverMsg = "You quit!\n";
			return;
		}
		default: {
			cout << "Invalid option. You skip your turn." << endl;
			return;
		}
	}
	//40% chance of misfortune on turn end
	if(getRand(0, 10) <= 4) {
		misfortune();
	}
	//Each menu option, your frustration level increases by 2
	player.setFrustration(player.getFrustration()+2);
	//Each menu option, you lose health if you have viruses
	player.setCompHealth(player.getCompHealth() - player.getViruses()*10);
}

void Game::moveAround() {
	char move;
	for(int i = 0; i < 3; i++) {

        map.displayMap();  // pretty print map_data in terminal

        cout << "Valid moves are: " << endl; 
        map.displayMoves();  // give user a menu of valid moves to pick from
        
        cout << "Input a move: ";
        cin >> move;
		cin.ignore(256, '\n');
        cout << endl;
        map.executeMove(move);  // move the player on map based on user input

		//Player gets 5 doge plus 5 per additional GPU
		player.getInv().setDogeCoins(player.getInv().getDogeCoins() + 5 + player.getInv().getPart(1)*5);

		//30% chance each step that a misfortune occurs
		if(getRand(0, 10) <= 3) {
			misfortune();
		}

        if (map.isHackerLocation() && numHackers > 0) {
            cout << "You've encountered a Hacker!" << endl;
			
			cout << "1. Fight" << endl;
			cout << "2. Forfeit" << endl;
			char choice2;
			do {
				cin >> choice2;
				cin.ignore(256, '\n');
				if(choice2 < '1' || choice2 > '2') {

					cout << "You must fight or forfeit!" << endl;

				} 
				else {
					break;
				}

			} while(true);
			int hacker = getRandomHacker();

			if(choice2 == '1'){
				if(fightHacker(hacker)) {
					hackersDefeated++;//add to defeated hacker number
					//Remove this hacker.
					//If there are more hackers left, recreate the array with the hacker we just fought removed
					if(numHackers > 1) {
						Hacker* newHackersArray = new Hacker[numHackers-1];
						int j = 0;
						//Loop through old array while keeping track of index of new array as j
						//E.g. we just fought hackers[2]
						//0[a] 1[b] 2[c] 3[d]
						//old array[i]: 0:a 1:b ~skipped 2~ 3:d
						//new array[j]: 0:a 1:b 2:d
						for(int i=0; i<numHackers; i++) {
							if(i == hacker){
								continue;
							}
							newHackersArray[j++] = hackers[i];
						}
						delete [] hackers;//delete hacker
						hackers = newHackersArray;//update array
						numHackers--;//less hackers now
					}
					//The hacker we just fought is the last hacker, so just delete the array
					else {
						delete [] hackers;
						hackers = nullptr;
						numHackers--;
					}
					map.removeHacker();
				}
			} 
			else { 
				forfeitHacker(hacker);
			}
            continue; 
        }
	}
}

void Game::misfortune() {
	// the player loses a random computer part. If they don’t have any computer parts, their computer maintenance level is dropped by 10.
	
	int numb = getRand(1, 15);

	if(player.getInv().computerParts() > 0 && numb >= 1 && numb <= 5){
		//lose a part
		cout << "OH NO! You were robbed by Carmen’s dastardly hackers!" << endl;
		//Pick part to lose randomly
		int part = player.getInv().loseRandomPart();
		cout << "You lost a " << PART_NAMES[part] << "!" << endl;

		if(player.getInv().computerParts() < 1){
			cout << "You have no computer parts left!" << endl;
		}
	}
	else if(player.getInv().computerParts() < 0){
		if(numb > 5 && numb <= 8){
			//Reduce the computer’s maintenance level to 10 
			cout << "OH NO! Your computer was damaged! You now are at level 10 computer maintenance!" << endl; 
			player.setCompHealth(10);
		}
		else{
			//increase frustration
			cout << "OH NO! Why won’t your code work!!!!" << endl; 
			player.setFrustration(player.getFrustration()+10); 
			cout << "You now have a frustration level of "<< player.getFrustration() << "." << endl; 
		}
	}
	

}

void Game::repairComputer() {
	int count = 0;//number of parts you want to use
	bool repair = true; 
	int cart[6]; 
	bool isValidChoice[6];

	for(int i=0; i < 6; i++){
		cart[i] = 0;
	}
	
	if(player.getViruses() >= 1){//has to have 0 viruses
		cout << "You may not repair your computer because it has a virus, to get rid of a virus you can use an antivirus stick!" << endl; 
		repair = false; 
	}
	while(repair == true){//loop through until done

		for(int i=0; i<6; i++){
			isValidChoice[i] = false;
		} 
		cout << endl; 
		cout << "Parts you can use to repair: " << endl; 
		
		if(player.getInv().getPart(0) - cart[0] > 0){//subtract 
			isValidChoice[0] = true;
			cout << "1. CPU: "<< player.getInv().getPart(0) - cart[0]<< endl;
		}

		if(player.getInv().getPart(1) - cart[1] > 0){
			isValidChoice[1] = true;
			cout << "2. GPU: "<<player.getInv().getPart(1) - cart[1] << endl; 
		}

		if(player.getInv().getPart(2) - cart[2] > 0){
			isValidChoice[2] = true;
			cout << "3. Power Supply Unit: "<< player.getInv().getPart(2) - cart[2] << endl; 
		}

		if(player.getInv().getPart(3) - cart[3] > 0){
			isValidChoice[3] = true;
			cout << "4. Computer Case: "<< player.getInv().getPart(3) - cart[3] << endl;
		}

		if(player.getInv().getPart(4) - cart[4] > 0){
			isValidChoice[4] = true;
			cout << "5. An Internet Card: "<< player.getInv().getPart(4) - cart[4] << endl;
		}

		if(player.getInv().getPart(5) - cart[5] > 0){
			isValidChoice[5] = true;
			cout << "6. Keyboard and mouse: "<< player.getInv().getPart(5) - cart[5] << endl; 
		}
		

		cout << endl;
		cout << "Enter the number(s) regarding the computer parts you'd like to use. Type 0 when you are ready to use the part you selected. You can select up to 5 parts." << endl; 


		
		int partNum;
		
		cin >> partNum;
		
		//char choice;
	
		//partNum = choice - '0';//makes into int
		//cin.ignore(256, '\n');
		
		if(partNum >= 1 && partNum <= 6  && isValidChoice[partNum-1] == true) {//valid
			cart[partNum-1]++;
			count ++; //keep track of number of parts being used
			
		}
		else if(partNum == 0 ||count >= 5 || player.getCompHealth() + 20*count >= 100) {

			string confirm = ""; 
			cout << "You will be using " << count << " computer parts."<< endl; 
			cout << "Are you sure you would like to purchase? (y/n):";

			do {
				cin >> confirm; 

				if(confirm == "y"|| confirm == "Y"){

					player.setCompHealth(player.getCompHealth() + 20*count);//upgrade comphealth

					for(int i=0; i<6; i++){
						player.getInv().setPart(i, player.getInv().getPart(i) - cart[i]);//subtract part
					}
					cout << "Your computer's maintenance level is now at " << player.getCompHealth() << endl; //show level
					repair = false; 
					break;

				}
				else if(confirm == "n"||confirm == "N"){
					repair = false;
					for(int i=0; i<6; i++) {
						cart[i] = 0;//cart is empty
						isValidChoice[i] = false;
					}
					break;
				}
				else{
					cout << "Please type the character y or n." << endl;
				}
			} while(true);
		}
		
		 
	}//end of while loop
	return;
}//end of repair function



void Game::useAntivirus() {

	string choice = "";
	cout << "Would you like to use your antivirus USB stick? (y/n)"<<endl; 
	cin >> choice; //get choice

	if(choice == "y"||choice == "Y"){
		if(player.getInv().getAntivirus() > 0){

			player.setViruses(0);//if stick used all viruses leave 
			player.getInv().setAntivirus(player.getInv().getAntivirus()-1);//one less usb stick

		}
		else{
			cout << "You do not have any antivirus USB sticks to use!" << endl; 
		}
	}
	else if(choice == "n"|| choice == "N"){
		//back to map
	}
	else{
		cout << "Invalid choice, please type y or n." << endl; 
	}
	cout << "You have " << player.getViruses() << " viruses." << endl; 
}


void Game::visitStackOverflow() { 

	cout << "You're browsing Stack Overflow. Do you want to:" << endl;
	bool browsing = true;

	while(browsing) {//loop until done

		cout << "1. Solve a puzzle" << endl;
		cout << "2. Play Rock Paper Scissors" << endl;
		cout << "3. Leave" << endl;
		char choice;

		do {
			cin >> choice;
			cin.ignore(256, '\n');
			if(choice != '1' && choice != '2' && choice != '3') {//valid until valid
				cout << "Please choose between 1 and 3." << endl;
			} 
			else {
				break;
			}

		} while(true);

		switch(choice) {
			case '1': {
				if(puzzle.doPuzzle()) {
					cout << "You lose 5 frustration!" << endl; //if you win puzzle 
					player.setFrustration(player.getFrustration()-5);// -5 frustration
				}
				break;
			}
			case '2': {
				cout << "Choose R, P, or S:";
				char rps;
				do {
					cin >> rps;
					cin.ignore(256, '\n');

					if(rps != 'R' && rps != 'P' && rps != 'S') {// until valid
						cout << "Please choose R, P, or S:";
					}
					else {
						break;
					}

				} while(true);

				string win[3] = {"Scissors", "Rock", "Paper"};//win array
				string lose[3] = {"Paper", "Scissors", "Rock"};//lose array

				int rpsID = 0;//where in array use based on input

				if(rps == 'P'){
					rpsID = 1;
				} 
				else if(rps == 'S'){ 
					rpsID = 2;
				}

				int rpsRand = getRand(1, 100);//1/3 chance of winning

				if(rpsRand <= 33) {//you win so win array
					cout << "The opponent chose " << win[rpsID] << endl;
					cout << "You won!" << endl;
					cout << "You lose 5 frustration levels!" << endl;
					player.setFrustration(player.getFrustration()-5);//lose 5 frustration
				}
				else if(rpsRand <= 66) {//lose array
					cout << "The opponent chose " << lose[rpsID] << endl;
					cout << "You lost!" << endl;
				}
				else {
					cout << "The opponent also chose " << rps << endl;
					cout << "You draw!" << endl;
				}
				break;
			}
			case '3':
				default:
				cout << "You stop browsing Stack Overflow." << endl;
				browsing = false;
				return;
		}
	}
}

int Game::getRandomHacker() {
	return getRand(0, numHackers);
}

bool Game::fightHacker(int hacker) {
	return hackers[hacker].fight(player);
}

void Game::forfeitHacker(int hacker) {
	cout << "You forfeit to " << hackers[hacker].getName() << "!" << endl;
	cout << "You give up all your spare computer parts!" << endl;

	for(int i=0; i<6; i++){
		player.getInv().setPart(i, 0);//all parts gone
	}
}

void Game::speakToNPC() {
	cout << "Hello compture science genius! Do you wish to complete one of my puzzles?" << endl;
	cout << "1. Do a puzzle" << endl;
	cout << "2. Take your chances (33% friend - get a part; 33% enemy - lose a part)" << endl;
	char choice;
	cin.clear();
	do {
		cin >> choice;
		if(choice != '1' && choice != '2') {
			cout << "You must choose 1 or 2!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else {
			cin.ignore(256, '\n');
			break;
		}
	} while(true);
	//Do a puzzle
	if(choice == '1') {
		if(puzzle.doPuzzle()) {
			int part = player.getInv().gainRandomPart();//random part gained
			if(part != -1){//if not -1 from function
				cout << "You won a " << PART_NAMES[part] << "!" << endl;
			}
		}
	}
	//Take your chances
	else {
		int chance = getRand(0, 100);//friend npc
		if(chance < 33) {
			cout << "It's dangerous to go alone! Take this!" << endl;
			int part = player.getInv().gainRandomPart();

			if(part != -1){
				cout << "You got a " << PART_NAMES[part] << "!" << endl;
			}
			else{
				cout << "Just kidding, you're full up on parts!" << endl;
			}
		}
		else if(chance <= 66) {//neutral
			cout << "Be careful out there!" << endl;
		}
		else {//enemy npc
			int part = player.getInv().loseRandomPart();
			if(part != -1){
				cout << "Uh oh! They stole a " << PART_NAMES[part] << "!" << endl;
			}
			else{
				cout << "Your lucky you had no parts to steal!" << endl;
			}
		}
	}
}