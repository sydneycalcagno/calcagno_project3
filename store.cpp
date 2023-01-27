#include <iostream>
#include "store.h"
#include "player.h"
#include "inventory.h"
using namespace std;

void visitBestBuy(Player& player, int room, bool firstVisit) {

	Inventory& inv = player.getInv();

	inv.printInventory(); //show inventory
	
	
	float priceIncrease = 0;
	if(room == 2) priceIncrease = 0.1;
	else if(room == 3) priceIncrease = 0.2;
	else if(room == 4) priceIncrease = 0.25;
	else if(room == 5) priceIncrease = 0.3;

	if(firstVisit == true){ // if first time show text
		
		cout << "You will need to spend the rest of your money on the following items:" << endl;

		cout << "\t- COMPUTER PARTS. If your computer breaks, you need 5 computer parts to make a new one.\n\t-ANTIVIRUS SOFTWARE. If your computer is infected with a virus, use the antivirus software to get rid of it.\n\t- VIRTUAL PRIVATE NETWORK (VPN). The more VPNs you have the harder it is for a hacker to infect your computer with a virus.\n\t- INTERNET PROVIDER. The better the internet provider, the more reliable your hacking will be."<<endl;

	}

	if(firstVisit == true){
		cout << "\nYou can spend all of your money here before you start your journey, or you can save some to spend on a different electronics site along the way. But beware, some of the websites online are shady, and they won’t always give you a fair price..." << endl;
	}
	
	//menu
	cout << endl;
	cout << "Select a number to purchase the following:" << endl; 
	cout << endl; 
	cout << "1. Computer Parts" << endl; 
	cout << "2. Antivirus Software" << endl;
	cout << "3. Virtual Private Network (VPN)" << endl;
	cout << "4. Internet Provider" << endl;
	cout << "5. Back to Map" << endl;
	int selection;
	cin >> selection;
	cin.ignore(256, '\n'); 
	cout << endl;
	
	
	switch (selection) {

		case 1: { //comp parts

			cout << endl; 
			cout << "Best Buy recommends that the player should purchase at least 1 of each computer part in case your main computer breaks. You can have a maximum of 3 of each computer part and 1 extra premade computer. These are the different parts:" << endl;
			//parts in our cart, corresponds to the same array numbers as the costs 
			int cart[7];
			for(int i=0; i < 7; i++){
				cart[i] = 0;
			}
			bool partsShopping = true;
			bool done = false;
			int totalPrice = 0;

			int partCosts[6];

			for(int i=0; i<6; i++){//filling cost parts array
				partCosts[i] = PART_COST[i] + PART_COST[i]*priceIncrease;
			}
			while(partsShopping == true) { //when you are shopping is true

				bool isValidChoice[7]; //checking if valid choice

				for(int i=0; i<7; i++){
					isValidChoice[i] = false;
				} 

				if(totalPrice + PART_COST[0] <= inv.getDogeCoins() && inv.getPart(0) + cart[0] < 3){ //part array correseponds to cpu, gpu, ect if the player has 3 parts of a certain part they can't get anymore
					isValidChoice[0] = true;
					cout << "1. CPU: 10 Dogecoins" << endl; 
				}
				if(totalPrice + PART_COST[1] <= inv.getDogeCoins() && inv.getPart(1) + cart[1] < 3){
					isValidChoice[1] = true;
					cout << "2. GPU: 20 Dogecoins" << endl; 
				}
				if(totalPrice + PART_COST[2] <= inv.getDogeCoins() && inv.getPart(2) + cart[2] < 3){
					isValidChoice[2] = true;
					cout << "3. Power Supply Unit: 5 Dogecoins" << endl; 
				}
				if(totalPrice + PART_COST[3] <= inv.getDogeCoins() && inv.getPart(3) + cart[3] < 3){
					isValidChoice[3] = true;
					cout << "4. Computer Case: 15 Dogecoins" << endl; 
				}
				if(totalPrice + PART_COST[4] <= inv.getDogeCoins() && inv.getPart(4) + cart[4] < 3){
					isValidChoice[4] = true;
					cout << "5. An Internet Card: 5 Dogecoins" << endl; 
				}
				if(totalPrice + PART_COST[5] <= inv.getDogeCoins() && inv.getPart(5) + cart[5] < 3){
					isValidChoice[5] = true;
					cout << "6. Keyboard and mouse: 10 Dogecoins" << endl; 
				}
				if(totalPrice + PART_COST[6] <= inv.getDogeCoins() && inv.getComputers() + cart[6] < 2){
					isValidChoice[6] = true;
					cout << "7. premade computer: 100 Dogecoins" << endl; 
				}

				cout << endl;
				int cartCount = 0;

				for(int i=0; i<6; i++) { //finds how much is in cart
					cartCount += cart[i];
				}
				cout << "You have " << inv.getDogeCoins()-totalPrice << " Dogecoins left to spend with consideration to the " << cartCount << " items in your cart" << endl;

				cout << "Enter the number(s) regarding the computer parts you'd like to purchase. Type 0 when you are ready for your end total." << endl; 
				int partNum;
				cin >> partNum;

				if(isValidChoice[partNum-1] == true && partNum >= 1 && partNum <= 7) {//if the choise is valid then
					cart[partNum-1]++; // add count to part, ex cpu (1-1)= 0, add one to cpu
					totalPrice += PART_COST[partNum-1];//find cost and add it to total price
				}
				else if(partNum == 0) {
					//This shouldn't happen because we don't display things you can't afford as a choice, but just in case...
					if(inv.getDogeCoins() < totalPrice) {

						cout << "You can't afford that transaction!" << endl;
						for(int i=0; i<7; i++){
							cart[i] = 0;//empties cart
						}
						totalPrice = 0;//sets price back to 0
						cout << "Your cart has been cleared." << endl; 
					}
					else {
						//prompt buy y/n?
						cout << totalPrice << endl; 
						string confirm; 
						cout << "Are you sure you would like to purchase? (y/n):";
						cin >> confirm; 

						if(confirm == "y" || confirm == "Y") {
							if(inv.getDogeCoins() >= totalPrice) { //have enough money

								cout << "The purchase was successful, thank you!" << endl;
								inv.setDogeCoins(inv.getDogeCoins() - totalPrice);//updates coins
								cout << "You now have a balance of " << inv.getDogeCoins() << " dogecoins" <<endl; 
								
								for(int i=0; i<6; i++) {//sets part numbers based on store visit
									inv.setPart(i, inv.getPart(i) + cart[i]);
								}
								inv.setComputers(inv.getComputers() + cart[6]);//sets computers
								
								done = true;//we are done so true
					
							}
						}
						else if(confirm == "n"||confirm == "N"){//if don't want to buy we are done
							done = true;
						}
						else {
							cout << "Please type the character y or n." << endl; //makes them type y or n
						}
						if(done == true){ //if done then parts shopping is false, end loop
							partsShopping=false;
						}
					}
				}
				
				else {
					cout << "Invalid selection." << endl;
				}
			}
			// back to menu of things to buy
			cout << endl; 
			visitBestBuy(player, firstVisit);
			return;
		}
	

		case 2:{

			while(true){

				/*One USB stick of antivirus software costs 10 Dogecoins and will give you a one-time use
				to get rid of any viruses on your computer.
				b. Ask the player how many antivirus USB sticks they would like to purchase.*/ 
				int numbUsb;
				cout << endl; 
				cout<< "One USB stick of antivirus software costs 10 Dogecoins and will give you a one-time use to get rid of any viruses on your computer." << endl; 

				cout << "Enter the number of how many antivirus USB sticks you would like the purchase: " << endl; 
				cin >> numbUsb; 

				int totalPrice = 0;

				totalPrice = numbUsb * 10; //one stick is 10

				
				if(inv.getDogeCoins() < totalPrice) {//dont have enough coins

					cout << "You can't afford that transaction!" << endl;

				}
				else{

					cout << totalPrice << endl; 
					string confirm; 
					cout << "Are you sure you would like to purchase? (y/n):";//y or n
					cin >> confirm; 

					if(confirm == "y" || confirm == "Y") {
						if(inv.getDogeCoins() >= totalPrice) {

							cout << "The purchase was successful, thank you!" << endl;
							inv.setDogeCoins(inv.getDogeCoins() - totalPrice);
							cout << "You now have a balance of " << inv.getDogeCoins() << " dogecoins" <<endl;

							inv.setAntivirus(inv.getAntivirus() + numbUsb); //set number of antivirus
							
						}
					}
					else if(confirm == "n"||confirm == "N"){
							
						}
					else if(confirm != "n" && confirm != "N" && confirm != "y" && confirm != "Y" ){
						cout << "Please type the character y or n." << endl;
					}

				}

				visitBestBuy(player, firstVisit);
				return;
			}
			
		}

		case 3:{

			while(true){ //make infinite loop to be broke in future

				int numbVPN; 

				cout << endl; 
				cout << "A VPN costs 20 Dogecoins each. VPNs reduce your chances of getting hacked by preventing hackers from tracking down your main computer. The increase in security maxes out at 2 VPNs." <<endl; 
				cout << endl; 
				cout << "How many VPNs would you like to purchase?"<<endl;
				cin >> numbVPN; 
				
				int totalPrice = 0;

				totalPrice = numbVPN * 20; 

				
				if(inv.getDogeCoins() < totalPrice) {

					cout << "You can't afford that transaction!" << endl;

				}
				else{

					cout << totalPrice << endl; 
					string confirm; 
					cout << "Are you sure you would like to purchase? (y/n):";//check to buy
					cin >> confirm; 

					if(confirm == "y" || confirm == "Y") {
						if(inv.getDogeCoins() >= totalPrice) {

							cout << "The purchase was successful, thank you!" << endl;
							inv.setDogeCoins(inv.getDogeCoins() - totalPrice);
							cout << "You now have a balance of " << inv.getDogeCoins() << " dogecoins" <<endl;

							inv.setVPNs(inv.getVPNs() + numbVPN); 
							
						}
					}
					else if(confirm == "n"||confirm == "N"){
							
						}
					else if(confirm != "n" && confirm != "N" && confirm != "y" && confirm != "Y" ){ //if not what to type then prompt what to type
						cout << "Please type the character y or n." << endl;
					}
					
					

				}

				visitBestBuy(player, firstVisit);
				return;
			}
		}

		case 4:{
			if(inv.getIPlvl() == 5) { // if at 5 then you can't get higher
				cout << "You already own the highest level internet provider!" << endl;
				visitBestBuy(player, firstVisit);
				return;
			}
			while(true){

				/*a.Internet provider level 2 costs 10 Dogecoins
				b. Internet provider level 3 costs 25 Dogecoins
				c. Internet provider level 4 costs 40 Dogecoins
				d. Internet provider level 5 costs 50 Dogecoins
				*/	
				int levelNumb_t; 
				cout << "What level internet provider would you like to buy?"<<endl;
				cout << "Having a better internet provider increases the player’s chances of winning a hacker battle"<<endl;
				cout << endl;

				bool isValidChoice[4]; //[0] corresponds to iplvl 2

				for(int i=0; i<4; i++){
					isValidChoice[i] = false;
				}
				const int LVL_COSTS[5] = {0, 10, 25, 40, 50}; //cost of level

				int upgradeValue = LVL_COSTS[inv.getIPlvl()-1]; //How much player has spent on previous ip upgrades
				for(int i=1; i<5; i++) {
					if(inv.getIPlvl()-1 < i) {
						isValidChoice[i] = true;
						cout << "Internet provider level " << i+1 << " costs ";
						cout << LVL_COSTS[i]-upgradeValue << " Dogecoins" << endl; //spending same amount each time by -upgradevalue
					}
				}

				cout << "Please enter a number regarding the level you would like to buy: "<< endl;
				cin >> levelNumb_t; 
				cin.ignore(256, '\n');

				if(levelNumb_t < 2 || levelNumb_t > 5 || !isValidChoice[levelNumb_t-1]){//not valid
					cout << "Invalid Selection." << endl; 
				}

				int totalPrice = LVL_COSTS[levelNumb_t-1]-upgradeValue;
				cout << "The cost is " << totalPrice << endl; 

				string confirm; 
				cout << "Are you sure you would like to purchase? (y/n):";
				cin >> confirm; 

				if(confirm == "y" || confirm == "Y") {
					if(inv.getDogeCoins() >= totalPrice) {
						cout << "The purchase was successful, thank you!" << endl;
						inv.setDogeCoins(inv.getDogeCoins() - totalPrice);//set coins
						cout << "You now have a balance of " << inv.getDogeCoins() << " dogecoins" <<endl;
						inv.setIPlvl(levelNumb_t);//update level
							
						
					}
				}
				else if(confirm == "n"||confirm == "N"){
					//nothing happens if n
				}
				else if(confirm != "n" && confirm != "N" && confirm != "y" && confirm != "Y" ){
					cout << "Please type the character y or n." << endl;
				}

				visitBestBuy(player, firstVisit);
				return;
			}
		}

		case 5:{

			//go back to displaying current map
			break;
			
		}
		default: {
			cout << "Invalid option." << endl;
			visitBestBuy(player, firstVisit);
			return;
		}






	}
	

}



