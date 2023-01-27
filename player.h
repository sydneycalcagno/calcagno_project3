#ifndef PLAYER_H
#define PLAYER_H

#include "inventory.h"

#include <string>

using namespace std;

class Player{

    public:

		Player();
		Player(int flevel, string pname); 

		string getPlayername();
		void setPlayername(string pname); 

		int getFrustration(); //frustration levels
		void setFrustration(int flevel);

		int getCompHealth();
		void setCompHealth(int);

		int getViruses();
		void setViruses(int);

		bool hasViruses();

		int getHackersDefeated();
		void setHackersDefeated(int);

		Inventory& getInv();



    private:

        int frustrationL; 
        string playerName; 
        int comp_level; //maintenance level. If 0, game over
		int viruses;
		Inventory inv;
		int hackersDefeated;

};

#endif