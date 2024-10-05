#include <iostream>
#include <fstream>
#include "FileHandler.h"


LinkedList FileHandler::readReviewsFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening CSV file: " << filename << endl;
        return reviewList;
    }

    string line;

    // Skip the header line
    if (getline(file, line)) {

    }

    int reviewCount = 0; int maxReviews = 5;
    while (getline(file, line) && reviewCount < maxReviews) {
        sanitize(line);
        reviewCount++;
    }

    file.close();
    return reviewList;
}

LinkedList FileHandler::readWordFromText(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening CSV file: " << filename << endl;
        return wordList;
    }

    string line;

    while (getline(file, line)) {
        wordList.insertFront(line);
    }

    file.close();
    return wordList;
}


void FileHandler::sanitize(string& line) {
    size_t commaPos = line.rfind(',');
    if (commaPos != string::npos) {
        string reviewText = line.substr(0, commaPos);
        string rating = line.substr(commaPos + 1);
        reviewList.insertFront(reviewText, rating);
    }

}

