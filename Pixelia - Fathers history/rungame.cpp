#include "header.h"
#include "dirent.h"

void runGame(string saveName, Player* player) {
	bool gameRunning = true;
	int indx = 0;
	int selection[2];
	do {
		mapView(selection);
		//Header menu options
		if (selection[0] == -1) {
			switch (selection[1]) {
			case 0: {
				//Inventory
				inventoryView(player);
			}break;
			case 1: {
				//Character
			}break;
			case 2: {
				//Quests
			}break;
			case 3: {
				//Save Game
				saveGame(saveName, player);
			}break;
			case 4: {
				//Save & Exit
				gameRunning = false;
			}break;
			}
		}
		else {
			//Header menu takes index 0-4
			switch (selection[0]) { //mapIndx;
			case 5: { //North
				switch (selection[1]) { //selectionIndx;
				//(offset + North,East,South,West) --> X
				case 9: {
					fishing(player);
				}break;
				case 10: {
					mineIron(player);
				}break;
				}
			}break;
			case 6: { //East

			}break;
			case 7: { //West

			}break;
			case 8: { //South

			}break;
			}
		}
	} while (gameRunning);
}

void fishing(Player* player) {
	int rndNum = (rand() % 3); //0-3
	system("cls");
	//cout << "Your change (%) was " << rndNum << endl;
	if (rndNum > 0) {
		Item fish = { "Fish", "ingredient", rndNum, 100, 0.3, 25, "heal", 10 };
		addToInventory(fish, player);
		cout << "You catch " << rndNum << " fish/es!" << endl;
	}
	else {
		cout << "You got nothing." << endl;
	}
	Sleep(1000);
}

void mineIron(Player* player) {
	int rndNum = (rand() % 3); //0-3
	system("cls");
	//cout << "Your change (%) was " << rndNum << endl;
	if (rndNum > 0) {
		Item ironOre = { "Iron Ore", "material", rndNum, 100, 0.3, 110, "none", 0 };
		addToInventory(ironOre, player);
		cout << "You mine " << rndNum << " ore/s!" << endl;
	}
	else {
		cout << "You got nothing." << endl;
	}
	Sleep(1000);

}

void addToInventory(Item item, Player* player) {
	typedef list<Item> Cont;
	bool exists = false;
	if ((player->inventory).size() > 0) {
		for (Cont::iterator i = (player->inventory).begin(); i != (player->inventory).end(); ++i) {
			Item &elem(*i);
			if (elem.name == item.name) {
				if (elem.count + item.count <= 0) {
					(player->inventory).erase(i);
				}
				else {
					elem.count += item.count;
				}
				exists = true;
				break;
			}
		}
	}
	if (!exists) {
		(player->inventory).push_back(item);
	}
}

void inventoryView(Player* player) {
	int max = (static_cast<int>((player->inventory).size())) + 1; //Exit takes 1. index
	string * opt;
	opt = new (nothrow) string[max];
	bool invLoop = true;
	int indx = 0, tempIndx, a = 0, removeCount;
	string * tempItems;
	tempItems = new (nothrow) string[max];

	for (int i = 0; i < max; i++) {
		opt[i] = "  ";
	}
	do {
		system("cls");
		opt[indx] = " <--";
		cout << "Exit" << opt[0] << endl;
		if (max > 1) {
			a = 0;
			for (Item item : (player->inventory)) {
				cout << "Name: " << item.name << " | Count: " << item.count << " " << opt[a + 1] << endl;
				tempItems[a++] = item.name;
			}
		} else {
			cout << "Inventory is empty..." << endl;
		}
		tempIndx = menuSelect(indx, max);
		opt[indx] = "    ";
		if (tempIndx == -1) {
			switch (indx) {
			case 0: {
				invLoop = false;
			}break;
			default: {
				cout << "How many you want to drop? (0 or less --> exit)" << endl;
				cin >> removeCount;
				if (removeCount > 0) {
					Item decreaseItem = { tempItems[indx - 1], "", (removeCount*(-1)), 0, 0, 0, "", 0 };
					addToInventory(decreaseItem, player);
					max = (static_cast<int>((player->inventory).size())) + 1;
					//If inventory is empty after drop
					if (max == 1 || indx >= max) {
						indx = max - 1;
					}
				}
			}
			}
		} else {
			indx = tempIndx;
		}
	} while (invLoop);
	delete[] tempItems, opt;
}