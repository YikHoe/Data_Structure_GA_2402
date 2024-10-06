#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include "LinkedList.h"

using namespace std;

class FileHandler {
public:

    void readReviewsFromCSV(const string filename, LinkedList& list);
    void readWordFromText(const string filename, LinkedList& wordlist);

};
#endif