#include <iostream>
#include <fstream>
#include "FileHandler.h"


void FileHandler::readReviewsFromCSV(const string filename, LinkedList& list) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening CSV file: " << filename << endl;
        return;
    }

    string line;

    // Skip the header line
    if (getline(file, line)) {

    }

    //int reviewCount = 0; int maxReviews = 10;
    while (getline(file, line)/* && reviewCount < maxReview*/) {
        size_t commaPos = line.rfind(',');
        if (commaPos != string::npos) {
            string reviewText = line.substr(0, commaPos);
            string rating = line.substr(commaPos + 1);
            list.insertFront(reviewText, rating);
        }
        //reviewCount++;
    }

    file.close();
}

void FileHandler::readWordFromText(const string filename, LinkedList& wordlist) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening CSV file: " << filename << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        wordlist.insertFront(line);
    }

    file.close();
}