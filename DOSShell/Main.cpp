#include "Tree.h";
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void UserProfile() {
	cout << "M. Asim Ali Murtaza, 2022-CS-175, Section D" << endl;
	cout << "Microwave Door [10.0.6321.4720]" << endl;
	cout << "(c) Microwave Corporation. All rights reserved." << endl;
	cout << "Type help for a list of commands" << endl;
	cout << endl;
	cout << endl;
}

void help() {
	cout << "cd	<folder name>			- change directory" << endl;
	cout << "cd ..						- go to parent directory" << endl;
	cout << "mkdir	<folder name>		- create a new folder" << endl;
	cout << "attrib	<folder name> <r/h> - set folder attribute to read-only or hidden" << endl;
	cout << "dir						- list all files and folders in current directory" << endl;
	cout << "ren <old name> <new name>  - rename a file or folder" << endl;
	cout << "type <file name>			- display the contents of a file" << endl;
	cout << "copy <file name> <des>		- copy a file to a destination" << endl;
	cout << "del <file name>		    - delete a file" << endl;
	cout << "rmdir <folder name>		- delete a folder" << endl;
	cout << "cls						- clear the screen" << endl;
	cout << "exit						- exit the program" << endl;
	cout << "help						- display a list of commands" << endl;
	cout << "ver						- display the version of the command prompt" << endl;
	cout << "tree						- display the folder structure" << endl;
	cout << "format						- format the drive" << endl;
	cout << "find <file name>			- find a file in the current directory" << endl;
	cout << "findf <file name> <string> - find a string in a file" << endl;
	cout << "findstr <string>			- find a string in all files" << endl;
	cout << "convert <old extn> <new extn> - convert the extension of all files" << endl;
	cout << "print <file name>			- print a file" << endl;
	cout << "pprint <file name>			- print a file in priority order" << endl;
	cout << "queue						- display the queue" << endl;
	cout << "pqueue						- display the priority queue" << endl;
	cout << endl;
}

int main() {

	bool exit = false;
	UserProfile();
	Directory* directory = new Directory();

	while (!exit) {

		string command;

		cout <<"V:" << directory->current->getPath() << ">";
		getline(cin, command);

		if (command == "help") {
			help();
		}
		else if (command == "exit") {
			exit = true;
		}
		else {
			stringstream ss(command);
			string token;
			vector<string> tokens;
			

			while (getline(ss, token, ' ')) {
				tokens.push_back(token);
			}
			if (tokens[0] == "mkdir") {
				directory->createFolder(tokens[1]);
			}
			else if (tokens[0] == "create") {
				string content;
				for (int i = 2; i < tokens.size(); i++) {
					content = content + " " + tokens[i];
				}
				directory->createFile(tokens[1], content);
			}
			else if (tokens[0] == "find") {
				directory->find(tokens[1]);
			}
			else if (tokens[0] == "findf") {
				string content;
				for (int i = 2; i < tokens.size(); i++) {
					content += tokens[i];
				}
				directory->findString(tokens[1], tokens[2]);
			}
			else if (tokens[0] == "findstr") {
				string content;
				for (int i = 2; i < tokens.size(); i++) {
					content = content + " " + tokens[i];
				}
				directory->findStringInAllFiles(content);
			}
			else if (tokens[0] == "cd") {
				if (tokens[1] == "..") {
					directory->cdDotDot();
				}
				if (tokens[1] == "\\") {
					directory->cdSlash();
				}
				if (tokens[1] == ".") {
					directory->printCurrentDirectory();
				}
				else {
					directory->changeDirectory(tokens[1]);
				}
			}
			else if (tokens[0] == "attrib") {
				directory->getFileAttributes(tokens[1]);
			}
			else if (tokens[0] == "dir") {
				directory->dir();
			}
			else if (tokens[0] == "ren") {
				directory->rename(tokens[1], tokens[2]);
			}
			else if (tokens[0] == "copy") {
				directory->copy(tokens[1], tokens[2]);
			}
			else if (tokens[0] == "move") {
				directory->move(tokens[1], tokens[2]);
			}
			else if (tokens[0] == "del") {
				directory->deleteFile(tokens[1]);
			}
			else if (tokens[0] == "rmdir") {
				directory->rmdir(tokens[1]);
			}
			else if (tokens[0] == "disp") {
				directory->displayFileContent(tokens[1]);
			}
			else if (tokens[0] == "ver") {
				cout << "Command Prompt Version [10.01.47b433]" << endl;
			}
			else if (tokens[0] == "tree") {
				directory->tree();
			}
			else if (tokens[0] == "convert") {
				directory->convertExtensionOfFiles(tokens[1], tokens[2]);
			}
			else if (tokens[0] == "format") {
				directory->format();
			}
			else if (tokens[0] == "print") {
				directory->Print(tokens[1]);
			}
			else if (tokens[0] == "pprint") {
				directory->PPrint(tokens[1]);
			}
			else if (tokens[0] == "queue") {
				directory->Queue();
			}
			else if (tokens[0] == "pqueue") {
				directory->PQueue();
			}
			else if (tokens[0] == "cls") {
				system("cls");
			}	
			else {
				cout << "Invalid command" << endl;
			}
			tokens.clear();
		}
	}
	return 0;
}