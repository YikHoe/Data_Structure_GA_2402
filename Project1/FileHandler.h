#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include "LinkedList.h"
#include "WordLinkedList.h"

using namespace std;

struct File
{
	string fileName;
};

class FileHandler {
    public:

        LinkedList readReviewsFromCSV(const string& filename);
        WordLinkedList readWordFromText(const string& filename);


    private:
        LinkedList reviewList;
        WordLinkedList wordList;
        void sanitize(string& line);

};
#endif