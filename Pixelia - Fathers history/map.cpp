#include "header.h"
#include "dirent.h"

void mapView(int selection[]) {
	const int size = 20;
	int max = 1;
	int mapIndx = 5;
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
		//cout << "Map index: " << mapIndx << endl;
		printHeaderMenu(opt);
		switch (mapIndx) {
		//Header menu takes index 0-4
		case 5: {
			printMapNorth(opt);
			max = offset + 6;
		}break;
		case 6: {
			printMapEast(opt);
			max = offset + 4;
		}break;
		case 7: {
			printMapWest(opt);
			max = offset + 4;
		}break;
		case 8: {
			printMapSouth(opt);
			max = offset + 4;
		}break;
		}
		tempIndx = menuSelect(indx, max);
		opt[indx] = "  ";
		if (tempIndx == -1) {
			if (indx < offset) {
				selection[0] = -1;
				selection[1] = indx;
				mapLoop = false;
			}
			else if (indx >= offset && indx <= (offset + 3)) {
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
	cout << "|   ^          ^^    |       " << opt[5] << " North*                               |" << endl;
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
	cout << "| West " << opt[7] << "                                                   " << opt[6] << " East* |" << endl;
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
	cout << "| West* " << opt[7] << "                                                  " << opt[6] << " East  |" << endl;
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
	cout << "|                            " << opt[8] << " South*                               |" << endl;
	cout << "*--------------------------------------------------------------------*" << endl;
}