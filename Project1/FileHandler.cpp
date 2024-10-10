#include <iostream>
#include <fstream>
#include "FileHandler.h"


void readReviewsFromCSV(string filename, LinkedList& list) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening CSV file: " << filename << endl;
        return;
    }

    string line;

    // Skip the header line
    getline(file, line);

    while (getline(file, line)) {
        size_t commaPos = line.rfind(',');
        if (commaPos != string::npos) {
            string reviewText = line.substr(0, commaPos);
            string rating = line.substr(commaPos + 1);
            list.insertFront(reviewText, rating);
        }
    }

    file.close();
}

void readWordFromText(string filename, LinkedList& wordlist) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening CSV file: " << filename << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        wordlist.insertBack(line);
    }

    file.close();
}