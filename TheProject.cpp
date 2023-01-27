#include "game.h"
#include <fstream>
#include <iostream> 
#include <cstdlib>
#include <ctime>

using namespace std;

void printFinalStats(ostream& out, Game& game);

int main() {
	srand(time(0)); //seed the random number generator to the system clock
	
	Game game; 

	while(!game.isOver()) //run do turn until game is over 
	{
		game.doTurn();
	}

	cout << "Game over!" << endl;
	printFinalStats(cout, game); //shows your stats after game has ended
	
	ofstream outFile("results.txt"); //shows what hackers you've defeated, ect
	printFinalStats(outFile, game);

	return 0;
}

void printFinalStats(ostream& out, Game& game) {//use ostream so we use out

	Player player = game.getPlayer(); //find player
	out << game.getGameoverMsg();//depending outcome of game over

	out << "Player:" << player.getPlayername() << endl; // stats
	out << "Hackers defeated:" << player.getHackersDefeated() << endl;
	out << "Dogecoin:" << player.getInv().getDogeCoins() << endl;

}