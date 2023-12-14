#pragma once
#include <fstream>
#include <Windows.h>
#include "Folder.h";
#include <queue>
using namespace std;


class Directory {
public:
	Folder* root;
	Folder* current;
	priority_queue<Node*> pq;
	queue<Node*> q;

	Directory() { root = current = new Folder("Asim", "V", "\\", root); }

	void createFolder(string nameOfFolder) {
		Folder* newFolder = new Folder("Asim", nameOfFolder, current->getPath() + nameOfFolder + "\\", current);
		current->addFolder(newFolder);
	};

	void createFile(string nameOfFile, string content) {
		Node* newFile = new Node(nameOfFile, content, "Asim", current->getPath() + nameOfFile);
		current->addFile(newFile);
	};

	void changeDirectory(string nameOfFolder) {
		for (auto subFolder : current->subFolders) {
			if (subFolder->nameOfFolder == nameOfFolder) {
				current = subFolder;
				break;
			}
		}
	};
	
	void mkdir(string nameOfFolder) { createFolder(nameOfFolder); }
	void getFileAttributes(string nameOfFile) {
		for (auto file : current->files) {
			if (file->nameOfFile == nameOfFile) {
				if (file->readOnly) {
					cout << "r" << endl;
				}
				else {
					cout << "h" << endl;
				}
				break;
			}
		}
	};
	void fileAttributes(string nameOfFile, string attribute) {
		if (attribute == "r") {
			for (auto file : current->files) {
				if (file->nameOfFile == nameOfFile) {
					file->readOnly = true;
					break;
				}
			}
		}
		else if (attribute == "h") {
			for (auto file : current->files) {
				if (file->nameOfFile == nameOfFile) {
					file->readOnly = false;
					break;
				}
			}
		}
		else {
			cout << "Invalid attribute" << endl;
		}
	};
	void attrib(string nameOfFolder, string attribute) {
		if (attribute == "r") {
			for (auto subFolder : current->subFolders) {
				if (subFolder->nameOfFolder == nameOfFolder) {
					subFolder->readOnly = true;
					break;
				}
			}
		}
		else if (attribute == "h") {
			for (auto subFolder : current->subFolders) {
				if (subFolder->nameOfFolder == nameOfFolder) {
					subFolder->readOnly = false;
					break;
				}
			}
		}
		else {
			cout << "Invalid attribute" << endl;
		}
	};

	void cdDotDot() {
		if (current->parent != nullptr) {
			current = current->parent;
		}
	};

	void printCurrentDirectory() {
		cout << current->getPath() << endl;
	}

	void cdSlash() {
		current = root;
	};

	void dir() {
		cout << "Date Created                     Type        Name" << endl;
		for (auto subFolder : current->subFolders) {
			cout << subFolder->created <<"             <DIR>       " << subFolder->nameOfFolder << endl;
		}
		for (auto file : current->files) {
			cout << file->created << "                         " << file->nameOfFile << endl;
		}
		cout << "\t" << current->files.size() << " File(s)" << endl;
		cout << "\t" << current->subFolders.size() << " Dir(s)" << endl;
	};
	
	void displayTree(Folder* folder, int level) {
		for (int i = 0; i < level; i++) {
			cout << "   ";
		}
		cout << folder->nameOfFolder << endl;
		for (auto subFolder : folder->subFolders) {
			displayTree(subFolder, level + 1);
		}
	};

	void copy(string nameOfFile, string fullPath) {
		Node* file = current->FindFile(nameOfFile);
		if (file != nullptr) {

			Node* newFile = new Node(file->nameOfFile, file->content, file->owner, fullPath + '\\');
			stringstream ss(fullPath);
			string token;
			queue<string> tokens;

			while (getline(ss, token, '\\')) {
				tokens.push(token);
			}

			Folder* temp = root;
			tokens.pop();
			while(tokens.size()>0) {
				for (auto subFolder : temp->subFolders) {
					if (subFolder->nameOfFolder == tokens.front()) {
						temp = subFolder;
						tokens.pop();
						break;
					}
				}
				
			}
			temp->addFile(newFile);
		}
		else {
			cout << "File not found" << endl;
		}
	};

	void move(string nameOfFile, string fullPath) {
		Node* file = current->FindFile(nameOfFile);
		if (file != nullptr) {

			Node* newFile = new Node(file->nameOfFile, file->content, file->owner, fullPath + '\\');
			stringstream ss(fullPath);
			string token;
			queue<string> tokens;

			while (getline(ss, token, '\\')) {
				tokens.push(token);
			}

			Folder* temp = root;
			tokens.pop();
			while (tokens.size() > 0) {
				for (auto subFolder : temp->subFolders) {
					if (subFolder->nameOfFolder == tokens.front()) {
						temp = subFolder;
						tokens.pop();
						break;
					}
				}

			}
			temp->addFile(newFile);
			current->removeFile(nameOfFile);
		}
		else {
			cout << "File not found" << endl;
		}
	};

	void deleteFile(string nameOfFile) {
		current->removeFile(nameOfFile);
	};

	void find(string nameOfFile) {
		Node* file = current->FindFile(nameOfFile);
		if (file != nullptr) {
			cout << file->nameOfFile << endl;
		}
		else {
			cout << "File not found" << endl;
		}
	};

	void findStringInAllFiles(string content) {
		for (auto file : current->files) {
			if (file->content.find(content) != string::npos) {
				cout << file->nameOfFile << endl;
			}
		}
	};

	void findString(string nameOfFile, string content) {
		Node* file = current->FindFile(nameOfFile);
		if (file != nullptr) {
			if (file->content.find(content) != string::npos) {
				cout << "String found in " << file->nameOfFile << endl;
			}
			else {
				cout << "String not found" << endl;
			}
		}
		else {
			cout << "File not found" << endl;
		}
	};

	void displayFileContent(string nameOfFile) {
		for (auto file : current->files) {
			if (file->nameOfFile == nameOfFile) {
				cout << file->content << endl;
			}
		}
	}

	void format() {
		current->EmptyDirectory();
		current->subFolders.clear();
		current->files.clear();
	};

	void rmdir(string nameOfFolder) {
		current->removeFolder(nameOfFolder);
	};

	void rename(string nameOfFile, string newName) {
		Node* file = current->FindFile(nameOfFile);
		if (file != nullptr) {
			file->rename(newName);
		}
		else {
			cout << "File not found" << endl;
		}
	};

	void convertExtensionOfFiles(string OldExtension, string newExtension) {
		for (auto file : current->files) {
			if (file->type == OldExtension) {
				file->type = newExtension;
			}
		}
	};

	void version() {
		cout << "DOS Shell Version 1.0" << endl;
	};

	void tree() {
		displayTree(root, 0);
	};

	void cls() {
		system("cls");
	};

	void saveTreeInTxtFile(Folder* folder, int level, ofstream& file) {
		for (int i = 0; i < level; i++) {
			file << "   ";
		}
		file << folder->nameOfFolder << endl;
		for (auto subFolder : folder->subFolders) {
			saveTreeInTxtFile(subFolder, level + 1, file);
		}
	};

	void PPrint(string fileName) {
		for (auto file : current->files) {
			if (file->nameOfFile == fileName) {
				pq.push(file);
			}
		}
	};

	void Print(string fileName) {
		for (auto file : current->files) {
			if (file->nameOfFile == fileName) {
				q.push(file);
			}
		}
	
	};

	void PQueue() {
		while (!pq.empty()) {
			cout << pq.top()->nameOfFile << " Time left: " << pq.top()->priority << endl;
			pq.pop();
		}
	};

	void Queue() {
		while (!q.empty()) {
			cout << q.front()->nameOfFile << " Time left: " << q.front()->priority <<  endl;
			q.pop();
		}
	};

	

};