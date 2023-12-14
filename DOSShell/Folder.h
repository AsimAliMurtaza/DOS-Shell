#pragma once
#include <string>
#include <iostream>
#include <ctime>
#include <list>
#include <sstream>
#include <chrono>
#include "Node.h"
using namespace std;

class Folder {
public:
    string owner;
    string nameOfFolder;
    string path;
    string created;
    time_t modified;
    Folder* parent;
    bool readOnly;
    list<Folder*> subFolders;
    list<Node*> files;
    

    Folder(string owner, string nameOfFolder, string path, Folder* parent) {
        this->owner = owner;
        this->nameOfFolder = nameOfFolder;
        this->path = path;
        this->parent = parent;
        this->modified = time(0);
        this->readOnly = false;
        setTime();
    }
    void setTime() {
        time_t currentTime;
        time(&currentTime);
        tm localTimeInfo;

        if (localtime_s(&localTimeInfo, &currentTime) == 0) {
            stringstream formattedDateTime;
            formattedDateTime << localTimeInfo.tm_year + 1900 << "-"  // Year is years since 1900
                << localTimeInfo.tm_mon + 1 << "/"       // Month is 0-11, so add 1
                << localTimeInfo.tm_mday << " "
                << localTimeInfo.tm_hour - 12 << ":"
                << localTimeInfo.tm_min << ":"
                << localTimeInfo.tm_sec;
            this->created = formattedDateTime.str();
        }
    }

    string getPath() { return path; }

    void rename(string newName) {
        nameOfFolder = newName;
        modified = time(0);
    }

    void addFolder(Folder* subFolder) { subFolders.push_back(subFolder); }

    void addFile(Node* file) { files.push_back(file); }

    void removeFolder(string folderName) {
        for (auto subFolder : subFolders) {
            if (subFolder->nameOfFolder == folderName) {
				subFolders.remove(subFolder);
				delete subFolder;
				break;
			}
		}
	}

    void removeFile(string fileName) {
        for (auto file : files) {
            if (file->nameOfFile == fileName) {
                files.remove(file);
                delete file;
                break;
            }
        }
    }

    void EmptyDirectory() {
        for (auto subFolder : subFolders) {
            delete subFolder;
        }
        for (auto file : files) {
            delete file;
        }
    }

    Node* FindFile(string fileName) {
        for (auto file : files) {
            if (file->nameOfFile == fileName) {
                return file;
            }
        }
        return nullptr;
    }

    Folder* FindFolder(string folderName) {
        for (auto subFolder : subFolders) {
            if (subFolder->nameOfFolder == folderName) {
                return subFolder;
            }
        }
        return nullptr;
    }

    void print() {
        for (auto subFolder : subFolders) {
            cout << "             <DIR>       " << subFolder->nameOfFolder << endl;
        }
        for (auto File : files) {
            cout << "                         " << File->nameOfFile << endl;
        }
    }
};