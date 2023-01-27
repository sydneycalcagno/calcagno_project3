#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

const std::string PART_NAMES[6] = {"CPU", "GPU", "Power supply unit", "Computer case", "Internet card", "Keyboard and mouse"};//array of part names

class Inventory {
	public:
		Inventory();
		//returns number of total computer parts
		int computerParts();

		int gainRandomPart(); //returns partType (0..6) lost, or -1 if nothing gained
		int loseRandomPart(); //returns partType (0..6) lost, or -1 if nothing lost
		
		int getAntivirus();
		void setAntivirus(int); 

		int getDogeCoins();
		int getIPlvl();
		int getVPNs();
		int getPart(int); //getPart i from parts array as listed below
		int getComputers();

		void setDogeCoins(int);
		void setIPlvl(int);
		void setVPNs(int);
		void setPart(int i, int count);
		void setComputers(int);

		void printInventory();
		
	private:
		//Order of parts array: CPU, GPU, PSU, CC, IC, KBM
		int parts[6];
		int computers, dogecoins, IPlvl, VPNs, USB;
};

#endif