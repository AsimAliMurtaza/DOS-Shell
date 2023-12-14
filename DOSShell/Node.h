#pragma once
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

class Node {
public:
    string nameOfFile;
    string type;
    string size;
    time_t priority;
    bool readOnly;
    bool hidden;
    string content;
    string owner;
    string created;
    string modified;
    string path;

    Node(string nameOfFile, string content, string owner, string path) {
        this->nameOfFile = nameOfFile;
        this->content = content;
        this->owner = owner;
        this->path = path;
        this->readOnly = false;
        this->hidden = false;
        this->type = ".txt";
        this->created = setTime();
        this->priority = time(0);
    }

    bool operator<(const Node& other) const {
        return priority > other.priority;
    }

    string setTime() {
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
            return formattedDateTime.str();
        }
    }

    void rename(string newName) {
        nameOfFile = newName;
        modified = setTime();
    }
};
