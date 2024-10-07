#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include "LinkedList.h"

using namespace std;

void readReviewsFromCSV(string filename, LinkedList& list);
void readWordFromText(string filename, LinkedList& wordlist);
#endif
