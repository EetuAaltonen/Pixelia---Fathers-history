// Pixeliafathershistory.cpp : Defines the entry point for the console application.
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <vector>

#include <sys/types.h>
#include "dirent.h"

using namespace std;
using namespace System;

void setWindowStyle();
void setWindowSize();

int menuSelect(int, int);

void mainMenu();
void printMainMenu(string [], int);

void loadMenu();
void printLoadMenu(string opt[], vector <string>);

vector <string> listSaves();
void createSave(vector <string>);
bool saveExists(string, vector <string>);

void saveGame();
void loadGame(string);

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

void printLogo();
void printMainMenu(string [], int);

string PATH;

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
		case KEY_DOWN: {
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
		printMainMenu(opt, max);
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
|                                                                    |)abcd";
}

void printMainMenu(string opt[], int) {
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
					//Update saves
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
		}
		else {
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
				ofstream outfile(PATH + "/" + saveName);
				outfile << "New save" << endl;
				outfile.close();
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

void saveGame() {

}

void loadGame(string saveName) {
	system("cls");
	cout << saveName << " loaded!" << endl;
	Sleep(500);
}