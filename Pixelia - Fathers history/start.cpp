// Pixeliafathershistory.cpp : Defines the entry point for the console application.
#include "header.h"
#include "dirent.h"

int main(int argc, char **argv) {
	string path(argv[0]);
	size_t pos = path.find_last_of("\\/");
	PATH = path.substr(0, pos);
	cout << PATH << endl;
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