// Pixeliafathershistory.cpp : Defines the entry point for the console application.
#include <iostream>
#include <windows.h>
using namespace std;
using namespace System;

void SetWindowSize();

int main()
{
	cout << "Starting game..." << endl;
	Sleep(500);
	cout << "Setting window size..." << endl;
	cout << "Disabling resize..." << endl;
	Sleep(500);
	SetWindowSize();
	Sleep(2000);
	system("cls");
	cout << "*--------------------------------------------------*" << endl;
	cout << "|                                                  |" << endl;
}

void SetWindowSize(){
	int newWidth;
	int newHeight;
	newWidth = 85;
	newHeight = 40;
	Console::SetWindowSize(newWidth, newHeight);
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE));
	cout << "Window width: " << newWidth << endl;
	cout << "Window height: " << newHeight << endl;
}
