// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LinkedList.h"
#include "WordLinkedList.h"
#include "FileHandler.h"


using namespace std;

int main()
{
	class FileHandler fileHandler;

	LinkedList reviewList = fileHandler.readReviewsFromCSV("tripadvisor_hotel_reviews.csv");
	WordLinkedList positiveList = fileHandler.readWordFromText("positive-words.txt");
	WordLinkedList negativeList = fileHandler.readWordFromText("negative-words.txt");


	//reviewList.displayList();
	//positiveList.displayList();
	//negativeList.displayList();
	LinkedList foundList = reviewList.search(positiveList, negativeList);
	foundList.displayList();


	

}

