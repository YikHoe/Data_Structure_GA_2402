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

	//LinkedList reviewList = fileHandler.readReviewsFromCSV("tripadvisor_hotel_reviews.csv");
	//WordLinkedList positiveList = fileHandler.readWordFromText("positive-words.txt");
	//WordLinkedList negativeList = fileHandler.readWordFromText("negative-words.txt");

	LinkedList reviewsList =  fileHandler.readReviewsFromCSV("tripadvisor_hotel_reviews.csv");
	LinkedList positiveList = fileHandler.readWordFromText("positive-words.txt");
	LinkedList negativeList = fileHandler.readWordFromText("negative-words.txt");

	reviewsList.displayList();
	positiveList.displayList();
}

