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
		int size = 0;
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
		int getSize();
		void displayList();
		void printReport();

		//linear serach
		LinkedList findMatchingWords(LinkedList& positiveList, LinkedList& negativeList);
		void max();
		void min();

		//merge sort
		WordNode* mergeLists(WordNode* left, WordNode* right);
		WordNode* splitList(WordNode* head);
		WordNode* mergeSort(WordNode* head);
		
		//helper
		bool linearSearch(string word);
		void sortByFrequency();

		// quick sort
		void quickSort();
		void quickSortByFrequency();

		// binary search
		bool binarySearch(string target);
		void resetFrequencies();
		void checkDuped(string word);


		Node* getHead();
		Node* getTail();
		WordNode* getWordHead();
		WordNode* getWordTail();
};
#endif