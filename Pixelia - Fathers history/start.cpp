// Pixeliafathershistory.cpp : Defines the entry point for the console application.
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <list>

#include <sys/types.h>
#include "dirent.h"

using namespace std;
using namespace System;

struct Item {
	string name;
	string type;
	int count;
	int durability;
	double weight;
	double price;
	string effect;
	int effect_amount;
};

/*-----Console-Initialize-----*/
void setWindowStyle();
void setWindowSize();
/*-----Select-Menu-----*/
int menuSelect(int, int);
/*-----Main-Menu-----*/
void mainMenu();
void printLogo();
void printMainMenu(string []);
/*-----Load-Menu-----*/
void loadMenu();
void printLoadMenu(string [], vector <string>);
/*-----Saves-----*/
vector <string> listSaves();
void createSave(vector <string>);
bool saveExists(string, vector <string>);
/*-----Save-&-Load-----*/
void loadGame(string);
void saveGame(string);
/*-----In-Game-----*/
//Run Game
void runGame(string);
//Header Menu
void printHeaderMenu(string[]);
//Maps
void mapView(int []);
void printMapNorth(string []);
void printMapEast(string []);
void printMapSouth(string []);
void printMapWest(string []);
//Inventory
void inventoryView();
void addToInventory(Item);
//Fishing
void fishing();
//Mine Iron
void mineIron();

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

string PATH;
list <Item> INVENTORY;

int main(int argc, char **argv)
{
	string path(argv[0]);
	size_t pos = path.find_last_of("\\/");
	PATH = path.substr(0, pos);
	//cout << PATH << endl;
	/*size_type pos = string(buffer).find_last_of("\\/");
	string(buffer).substr(0, pos);*/
	//cout << argv[0] << endl;
	//cin.get();
	cout << "Starting game..." << endl;
	Sleep(500);
	cout << "Setting window size..." << endl;
	Sleep(500);
	setWindowSize();
	Sleep(500);
	cout << "Disabling resize..." << endl;
	setWindowStyle();
	Sleep(1000);
	mainMenu();
}

void setWindowStyle() {
	HWND hwnd = GetConsoleWindow();
	LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
	lStyle &= ~(WS_THICKFRAME); //Disable resize
	SetWindowLong(hwnd, GWL_STYLE, lStyle);
}

void setWindowSize(){
	HWND hwnd = GetConsoleWindow();
	RECT rect = { 100 /*top*/, 400 /*left*/, 550 /*top2*/, 1000 /*left2*/ };
	MoveWindow(hwnd, rect.top, rect.left, rect.bottom - rect.top, rect.right - rect.left, TRUE);
	cout << "Window width: " << (rect.right - rect.left) << endl;
	cout << "Window height: " << (rect.bottom - rect.top) << endl;
}

int menuSelect(int indx, int max) {
	int c = 0;
	do {
		Sleep(200); //For input lag
		c = _getch();
		//for detect the function\arrow keys 
		//we must call the getch() again
		//testing if a is '0' or '0xE0'
		if (c == 0 || c == 0xE0) {
			c = _getch();
		}
		switch (c) {
		case KEY_UP: {
			indx -= 1;
			if (indx < 0) {
				indx = (max - 1);
			}
			return indx;
		}break;
		case KEY_LEFT: {
			indx -= 1;
			if (indx < 0) {
				indx = (max - 1);
			}
			return indx;
		}break;
		case KEY_DOWN: {
			indx += 1;
			if (indx == max) {
				indx = 0;
			}
			return indx;
		}break;
		case KEY_RIGHT: {
			indx += 1;
			if (indx == max) {
				indx = 0;
			}
			return indx;
		}break;
		case KEY_ENTER: {
			return -1;
		}break;
		}
	} while (true);
	return indx;
}

void mainMenu() {
	const int max = 2;
	string opt[max];
	bool menuLoop = true;
	int indx = 0, tempIndx;
	for (int i = 0; i < max; i++) {
		opt[i] = "  ";
	}
	do {
		opt[indx] = "<>";
		printMainMenu(opt);
		tempIndx = menuSelect(indx, max);
		opt[indx] = "  ";
		if (tempIndx == -1) {
			if (indx == 0) {
				loadMenu();
			} else {
				menuLoop = false;
			}
		} else {
			indx = tempIndx;
		}
	} while (menuLoop);
}

void printLogo() {
cout <<
R"abcd(*--------------------------------------------------------------------*
|   ________   __  ___     ___  _______   __        __   _________   |
|  |  ____  | |  | \  \   /  / |  _____| |  |      |  | |   ___   |  |
|  |  |__|  | |  |  \  \_/  /  |  |____  |  |      |  | |  |___|  |  |
|  |  ______| |  |   \     /   |  _____| |  |      |  | |  ____   |  |
|  |  |       |  |   /  /\  \  |  |____  |  |____  |  | |  |   |  |  |
|  |__|       |__|  /__/  \__\ |_______| |_______| |__| |__|   |__|  |
|                                                                    |
|                    *** MY FATHER'S HISTORY ***                     |
|                                                                    |
|                                                                    |)abcd" << endl;
}

void printMainMenu(string opt[]) {
	system("cls");
	printLogo();
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                             "
		<< opt[0] << " PLAY " << opt[0]
		<< "                             |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                             "
		<< opt[1] << " EXIT " << opt[1]
		<< "                             |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "*--------------------------------------------------------------------*" << endl;
}

void loadMenu() {
	vector <string> saves =	listSaves();
	int max = (static_cast<int>(saves.size())) + 2;
	string * opt;
	string newSave;
	opt = new (nothrow) string[max];
	bool menuLoop = true;
	int indx = 0, tempIndx;

	for (int i = 0; i < max; i++) {
		opt[i] = "  ";
	}
	do {
		opt[indx] = " <--";
		printLoadMenu(opt, saves);
		tempIndx = menuSelect(indx, max);
		opt[indx] = "    ";		
		if (tempIndx == -1) {
			switch (indx) {
				case 0: {
					menuLoop = false;
				}break;
				case 1: {
					createSave(saves);
					max += 1;
					//Update saves list
					saves.clear();
					saves = listSaves();
					delete[] opt;
					opt = new (nothrow) string[max];
				}break;
				default: {
					loadGame(saves[indx - 2]); //indx-2 because Exit = 0, Create new save = 1 but first saves index = 0;
					menuLoop = false;
				}
			}
		} else {
			indx = tempIndx;
		}
	} while (menuLoop);
	delete[] opt;
	//createSave();
	/*loadSaves();
	listSaves();*/
}

void printLoadMenu(string opt[], vector <string> saves) {
	system("cls");
	int size = static_cast<int>(saves.size());
	cout << "- Exit " << opt[0] << endl;
	cout << "- Create new save " << opt[1] << endl;
	cout << "Saves:" << endl;
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			cout << "- " << saves[i] << opt[i + 2] << endl;
		}
	} else {
		cout << "No saves exist..." << endl;
	}
}

vector <string> listSaves() {
	DIR *dp;
	struct dirent *dirp;
	dp = opendir(PATH.c_str());
	vector <string> files;
	while ((dirp = readdir(dp)) != NULL) {
		string file = dirp->d_name;
		if (file.find(".sav") != string::npos) {
			files.push_back(dirp->d_name);
		}
	}
	return files;
}

void createSave(vector <string> saves) {
	string saveName = "";
	bool setName = true;
	do {
		system("cls");
		cout << "Create new save" << endl;
		cout << "Empty name will take you back..." << endl;
		cout << "Give a name:" << endl;
		getline(cin, saveName);
		replace(saveName.begin(), saveName.end(), ' ', '_');
		if (saveName != "") {
			saveName += ".sav";
			if (!saveExists(saveName, saves)) {
				ofstream file(PATH + "/" + saveName);
				file << "New save" << endl;
				file.close();
				cout << saveName << " created." << endl;
				setName = false;
			} else {
				cout << "Name already exists!" << endl;
			}
			Sleep(1000);
		} else {
			setName = false;
		}
	} while (setName);
}

bool saveExists(string saveName, vector <string> saves) {
	size_t size = saves.size();
	for (int i = 0; i < size; i++) {
		if (saves[i] == saveName) {
			return true;
		}
	}
	return false;
}

void loadGame(string saveName) {
	system("cls");
	cout << saveName << " loaded!" << endl;
	Sleep(500);
	runGame(saveName);
	saveGame(saveName);
}

void runGame(string saveName) {
	bool gameRunning = true;
	int indx = 0;
	int selection[2];
	do {
		mapView(selection);
		//Oma switch headerin valikolle!
		/*case 0: {
			inventoryView();
		}break;*/
		if (selection[0] == -1) {
			switch (selection[1]) {
				case 0: {
					inventoryView();
				}break;
				case 1: {
					//Character
				}break;
				case 2: {
					//Quests
				}break;
				case 3: {
					saveGame(saveName);
				}break;
				case 4: {
					gameRunning = false;
				}break;
			}

		} else {
			switch (selection[0]) { //mapIndx;
				case 0: { //North
					switch (selection[1]) { //selectionIndx;
						//(offset + North,East,South,West) --> X
						case 9: {
							fishing();
						}break;
						case 10: {
							mineIron();
						}break;
					}
				}break;
				case 1: { //East
				
				}break;
				case 2: { //West

				}break;
				case 3: { //South

				}break;
			}
		}
	} while (gameRunning);
}

void fishing() {
	int rndNum = (rand() % 3); //0-3
	system("cls");
	cout << "Your change (%) was " << rndNum << endl;
	if (rndNum > 0) {
		Item fish = { "Fish", "ingredient", rndNum, 100, 0.3, 25, "heal", 10 };
		addToInventory(fish);
		cout << "You catch " << rndNum << " fish/es!" << endl;
	} else {
		cout << "You got nothing." << endl;
	}
	Sleep(1000);
}

void mineIron() {
	int rndNum = (rand() % 3); //0-3
	system("cls");
	cout << "Your change (%) was " << rndNum << endl;
	if (rndNum > 0) {
		Item ironOre = { "Iron Ore", "material", rndNum, 100, 0.3, 110, "none", 0 };
		addToInventory(ironOre);
		cout << "You mine " << rndNum << " ore/s!" << endl;
	} else {
		cout << "You got nothing." << endl;
	}
	Sleep(1000);
	
}

void addToInventory(Item item) {
	typedef list<Item> Cont;
	bool exists = false;
	if (INVENTORY.size() > 0) {
		for (Cont::iterator i = INVENTORY.begin(); i != INVENTORY.end(); ++i) {
			Item &elem(*i);
			if (elem.name == item.name) {
				if (elem.count + item.count <= 0) {
					INVENTORY.erase(i);
				} else {
					elem.count += item.count;
				}
				exists = true;
				break;
			}
		}
	}
	if (!exists) {
		INVENTORY.push_back(item);
	}
	//INVENTORY.sort();
}

void inventoryView() {
	int max = (static_cast<int>(INVENTORY.size())) + 1;
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
			for (Item item : INVENTORY) {
				cout << "Name: " << item.name << " | Count: " << item.count << " " << opt[a + 1] << endl;
				tempItems[a++] = item.name;
			}
			cout << "Selection index: " << indx << endl;
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
						addToInventory(decreaseItem);
						max = (static_cast<int>(INVENTORY.size())) + 1;
						//If inventory is empty after drop
						if (max == 1 || indx >= max) {
							indx = max-1;
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

void saveGame(string saveName) {
	system("cls");
	cout << "Auto save..." << endl;
	ofstream file(PATH + "/" + saveName);
	//Basic Info
	file << "path: " << PATH << endl;
	file << "name: " << saveName << endl;
	//Character Name
	file << "characterName: " << "Dragonborn" << endl;
	file << "class: " << "Nord" << endl;
	//Skills
	file << "skills: " << "empty" << endl;
	//Inventory
	file << "inventory: " << "empty" << endl;
	//Quests
	file << "activeQuest: " << "empty" << endl;
	file << "incompletedQuests: " << "empty" << endl;
	file << "completedQuests: " << "empty" << endl;
	file.close();
	cout << saveName << " saved." << endl;
	Sleep(1000);
}

void mapView(int selection[]) {
	const int size = 20;
	int max = 1;
	int mapIndx = 0;
	string opt[size];
	bool mapLoop = true;
	int indx = 0, tempIndx;
	int offset = 5;

	for (int i = 0; i < size; i++) {
		opt[i] = "  ";
	}
	do {
		system("cls");
		opt[indx] = "<>";
		printHeaderMenu(opt);
		switch (mapIndx) {
			case 0: {
				printMapNorth(opt);
				max = offset+6;
			}break;
			case 1: {
				cout << "East" << endl;
				cin.get();
				printMapEast(opt);
				max = offset+4;
			}break;
			case 2: {
				printMapWest(opt);
				max = offset+4;
			}break;
			case 3: {
				printMapSouth(opt);
				max = offset+4;
			}break;
		}
		tempIndx = menuSelect(indx, max);
		opt[indx] = "  ";
		if (tempIndx == -1) {
			if (indx <= offset) {
				selection[0] = -1;
				selection[1] = indx;
				mapLoop = false;
			} else if (indx > offset && indx <= (offset + 3)) {
				mapIndx = indx;
			} else {
				selection[0] = mapIndx;
				selection[1] = indx;
				mapLoop = false;
			}
		} else {
			indx = tempIndx;
		}
	} while (mapLoop);
}

void printHeaderMenu(string opt[]) {
	cout << "| " << opt[0] << " Inventory  | " << opt[1] << " Character  | " << opt[2] << " Quests  | " << opt[3] << " Save  | " << opt[4] << " Exit    |" << endl;
}

//R"abcd( ... )abcd";

void printMapNorth(string opt[]) {
	cout << "*--------------------------------------------------------------------*" << endl;
	cout << "|   ^          ^^    |       " << opt[5] << " North                                |" << endl;
	cout << 
	  R"abcd(|        ^           \                                               |)abcd" << endl;
	cout << "|                     |                                              |" << endl;
	cout << "|    ^       ^^      /   Lake " << opt[9] << "                                     |" << endl;
	cout << "|              _____/                         _____                  |" << endl;
	cout <<
	  R"abcd(|  ^^  _______/                              / ___ \                 |)abcd" << endl;
	cout <<
	  R"abcd(|_____/                                     /__|||__\                |)abcd" << endl;
	cout << "|                                           Iron Mine " << opt[10] << "             |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "| West " << opt[7] << "                                                   " << opt[6] << " East  |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                            " << opt[8] << " South                                |" << endl;
	cout << "*--------------------------------------------------------------------*" << endl;
}

void printMapEast(string opt[]) {
	cout << "*--------------------------------------------------------------------*" << endl;
	cout << "|                            " << opt[5] << " North                                |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "| West " << opt[7] << "                                                   " << opt[6] << " East  |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                            " << opt[8] << " South                                |" << endl;
	cout << "*--------------------------------------------------------------------*" << endl;
	cout << "East printed" << endl;
	cin.get();
}

void printMapWest(string opt[]) {
	cout << "*--------------------------------------------------------------------*" << endl;
	cout << "|                            " << opt[5] << " North                                |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "| West " << opt[7] << "                                                   " << opt[6] << " East  |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                            " << opt[8] << " South                                |" << endl;
	cout << "*--------------------------------------------------------------------*" << endl;
}

void printMapSouth(string opt[]) {
	cout << "*--------------------------------------------------------------------*" << endl;
	cout << "|                            " << opt[5] << " North                                |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "| West " << opt[7] << "                                                   " << opt[6] << " East  |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                                                                    |" << endl;
	cout << "|                            " << opt[8] << " South                                |" << endl;
	cout << "*--------------------------------------------------------------------*" << endl;
}