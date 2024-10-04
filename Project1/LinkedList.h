#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "WordLinkedList.h"
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
	WordNode* nextAddress;
	WordNode(string word_string);
};

class LinkedList
{
	private:
		Node* head;
		WordNode* word_head;

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
		//LinkedList search(const WordLinkedList& positiveList&, const WordLinkedList& negativeList);
};
#endif
