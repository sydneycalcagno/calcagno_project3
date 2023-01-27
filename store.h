#ifndef STORE_H
#define STORE_H

#include "player.h"

//Order of array: CPU, GPU, PSU, CC, IC, KBM, PC
const int PART_COST[7] = {10, 20, 5, 15, 5, 10, 100};

void visitBestBuy(Player& player, int room, bool firstVisit = false); 

#endif