#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
using namespace std;

struct Node
{
	string review, rating;
	Node* nextAddress;
	Node(string review_string, string rating_given);
};

struct WordNode
{
	string word;
	int frequency;
	WordNode* nextAddress;
	WordNode(string word_string);
};

class LinkedList
{
	private:
		Node* head, * tail;
		WordNode* word_head, * word_tail;
		int size;

		// quick sort algorithm
		WordNode* partition(WordNode* head, WordNode* tail);
		WordNode* partitionByFrequency(WordNode* head, WordNode* tail);
		void sortRecur(WordNode* head, WordNode* tail);
		void sortRecurByFrequency(WordNode* head, WordNode* tail);

		// binary search alogorithm
		WordNode* getMiddle(WordNode* head, WordNode* tail);

	public:
		LinkedList();
		~LinkedList();
		void insertFront(string review_string, string rating_given);
		void insertFront(string word);
		void insertBack(string review, string rating);
		void insertBack(string word);
		void deleteFront();
		void deleteBack();
		void displayList();
		void printReport();

		// quick sort
		void quickSort();
		void quickSortByFrequency();

		// binary search
		bool binarySearch(string target);

		void checkDuped(string word);

		//void calculateFrequency();
		//void removeDuplicates();

		Node* getHead();
		Node* getTail();
		WordNode* getWordHead();
		WordNode* getWordTail();

};
#endif
