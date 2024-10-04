#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include "LinkedList.h"

using namespace std;

struct File
{
	string fileName;
};

class FileHandler {
    public:

        LinkedList readReviewsFromCSV(const string& filename);
        LinkedList readWordFromText(const string& filename);


    private:
        LinkedList reviewList, wordList;
        void sanitize(string& line);

};
#endif