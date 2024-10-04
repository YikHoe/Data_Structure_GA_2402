#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "WordLinkedList.h"
using namespace std;

struct Node
{
	string review, rating, word;
	Node* nextAddress;
	Node(string review_string, string rating_given, string word_founded);
	Node();
};

class LinkedList
{
	private:
		Node* head;

	public:
		LinkedList();
		~LinkedList();
		void insertFront(string review_string, string rating_given, string word_founded);
		void insertBack(string review, string rating, string word_founded);
		void deleteFront();
		void deleteBack();
		void displayList();
		LinkedList search(const WordLinkedList& positiveList£¬, const WordLinkedList& negativeList);
};
#endif
