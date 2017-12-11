#include "header.h"
#include "dirent.h"

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
				file << "New empty save" << endl;
				file.close();
				cout << saveName << " created." << endl;
				setName = false;
			}
			else {
				cout << "Name already exists!" << endl;
			}
			Sleep(1000);
		}
		else {
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

void saveGame(string saveName, Player * player) {
	string tmpName;
	system("cls");
	cout << "Saving..." << endl;
	ofstream file(PATH + "/" + saveName);
	//Character Name
	file << "name:" << "Dragonborn" << endl;
	file << "clss:" << "Nord" << endl;
	//Skills
	file << "skills:" << "empty" << endl;
	//Spells
	//file << "spells:" << endl;
	//file << "/spells" << endl;
	//Inventory
	file << "inventory:" << endl;
	for (Item item : (player->inventory)) {
		tmpName = item.name;
		replace(tmpName.begin(), tmpName.end(), ' ', '_');
		file << tmpName << "," << item.type << "," << item.count << "," << item.durability << ","
			<< item.weight << "," << item.price << "," << item.effect << "," << item.effect_amount << endl;
	}
	file << "/inventory" << endl;
	/*
	Item {
	string name;
	string type;
	int count;
	int durability;
	double weight;
	double price;
	string effect;
	int effect_amount;
	};
	*/
	//Quests
	file << "activeQuest:" << "empty" << endl;
	file << "incompletedQuests:" << "empty" << endl;
	file << "completedQuests: " << "empty" << endl;
	file.close();
	cout << saveName << " saved." << endl;
	Sleep(1000);
}

void loadGame(string saveName) {
	int indx = 0;
	vector <string> data;
	size_t pos;
	string line = "";
	Player *player = new Player();
	Item item;
	system("cls");
	ifstream file;
	file.open(PATH + "/" + saveName);
	while (!file.eof()) {
		getline(file, line);
		replace(line.begin(), line.end(), '_', ' ');
		pos = line.find(DATASTRUCTURE[indx]);
		if (pos != string::npos) {
			if (line != DATASTRUCTURE[indx]) {
				line.replace(pos, DATASTRUCTURE[indx].length(), "");
				replace(line.begin(), line.end(), ' ', '_');
				//cout << line << endl;
			}
			indx++;
		} else if (DATASTRUCTURE[indx] == "/spells") {
			if (line != DATASTRUCTURE[indx]) {
				//cout << "Spell found!" << endl;
			} else {
				indx++;
			}
		} else if (DATASTRUCTURE[indx] == "/inventory") {
			if (line != DATASTRUCTURE[indx]) {
				string value;
				istringstream substring(line);
				while (getline(substring, value, ',')) {
					data.push_back(value);
					//cout << value << endl;
				}
				item.name = data[0];
				item.type = data[1];
				item.count = stoi(data[2]);
				item.durability = stoi(data[3]);
				item.weight = stod(data[4]);
				item.price = stod(data[5]);
				item.effect = data[6];
				item.effect_amount = stoi(data[7]);
				addToInventory(item, player);
				data.clear();
			} else {
				indx++;
			}
		} else if (line == "") {
			//cout << "NULL" << endl;
			indx++;
		}
	}
	file.close();
	cout << saveName << " loaded!" << endl;
	//cin.get();
	Sleep(500);
	runGame(saveName, player);
	saveGame(saveName, player);
}