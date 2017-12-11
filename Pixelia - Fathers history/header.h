#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <list>
#include <sstream>

#include <sys/types.h>
#include "dirent.h"

using namespace std;
using namespace System;

struct Skill {
	string name;
	int level;
};

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

struct Player {
	string name;
	string clss;

	vector <Skill> skills;
	list <string> spells;
	list <Item> inventory;

	string activeQuest;
	list <string> incompletedQuests;
	list <string> completedQuests;
	list <string> factions;

	int health;
	int stamina;
	int mana;
	int bounty;
};

/*-----Console-Initialize-----*/
void setWindowStyle();
void setWindowSize();
/*-----Select-Menu-----*/
int menuSelect(int, int);
/*-----Main-Menu-----*/
void mainMenu();
void printLogo();
void printMainMenu(string[]);
/*-----Load-Menu-----*/
void loadMenu();
void printLoadMenu(string[], vector <string>);
/*-----Saves-----*/
vector <string> listSaves();
void createSave(vector <string>);
bool saveExists(string, vector <string>);
/*-----Save-&-Load-----*/
void loadGame(string);
void saveGame(string, Player*);
/*-----In-Game-----*/
//Run Game
void runGame(string, Player*);
//Header Menu
void printHeaderMenu(string[]);
//Maps
void mapView(int[]);
void printMapNorth(string[]);
void printMapEast(string[]);
void printMapSouth(string[]);
void printMapWest(string[]);
//Inventory
void inventoryView(Player*);
void addToInventory(Item, Player*);
//Fishing
void fishing(Player*);
//Mine Iron
void mineIron(Player*);

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

extern string PATH;
extern string DATASTRUCTURE[];