// Pixeliafathershistory.cpp : Defines the entry point for the console application.
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
using namespace std;
using namespace System;

void SetWindowStyle();
void SetWindowSize();
void MenuOption();
void DrawMenu(int);

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

void printLogo();
void printMenu(string [], int);

int main()
{
	cout << "Starting game..." << endl;
	Sleep(500);
	cout << "Setting window size..." << endl;
	Sleep(500);
	SetWindowSize();
	Sleep(500);
	cout << "Disabling resize..." << endl;
	SetWindowStyle();
	Sleep(1000);
	MenuOption();
}

void SetWindowStyle() {
	HWND hwnd = GetConsoleWindow();
	LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
	lStyle &= ~(WS_THICKFRAME); //Disable resize
	SetWindowLong(hwnd, GWL_STYLE, lStyle);
}

void SetWindowSize(){
	HWND hwnd = GetConsoleWindow();
	RECT rect = { 100 /*top*/, 400 /*left*/, 550 /*top2*/, 1000 /*left2*/ };
	MoveWindow(hwnd, rect.top, rect.left, rect.bottom - rect.top, rect.right - rect.left, TRUE);
	cout << "Window width: " << (rect.right - rect.left) << endl;
	cout << "Window height: " << (rect.bottom - rect.top) << endl;
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

void printMenu(string opt[], int size) {
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

void MenuOption() {
	const int max = 2;
	string opt[max];
	int indx = 0;
	string temp;
	int c = 0;
	for (int i = 0; i < max; i++) {
		opt[i] = "  ";
	}
	do {
		opt[indx] = "<>";
		system("cls");
		printMenu(opt, max);
		opt[indx] = "  ";
		Sleep(500);
		switch ((c = _getch())) {
			case KEY_UP: {
				indx -= 1;
				if (indx < 0) {
					indx = (max - 1);
				}
			}break;
			case KEY_DOWN: {
				indx += 1;
				if (indx == max) {
					indx = 0;
				}
			}break;
			case KEY_ENTER: {
				cout << "Enter pressed!" << endl;  // not arrow
			}break;
			default: {
				cout << "null" << endl;  // not arrow
			}break;
		}
		/*if (GetAsyncKeyState(VK_UP) & 0x8000 && indx > 0) {
		indx += 1;
		} else if (GetAsyncKeyState(VK_UP) & 0x8000 && indx == 0) {
		indx = (max-1);
		} else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && indx < (max-1)) {
		indx -= 1;
		} else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && indx == (max-1)) {
		indx = 0;
		} else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		break;
		}*/
		
		/*if (opt[1] == "<>") {
		break;
		}*/
	} while (true);
}