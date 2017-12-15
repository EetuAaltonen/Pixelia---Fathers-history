#include "header.h"
#include "dirent.h"

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
			}
			else {
				menuLoop = false;
			}
		}
		else {
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
	vector <string> saves = listSaves();
	int max = (static_cast<int>(saves.size())) + 2; //Exit and Create takes 2 first index
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
		}
		else {
			indx = tempIndx;
		}
	} while (menuLoop);
	delete[] opt;
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
	}
	else {
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