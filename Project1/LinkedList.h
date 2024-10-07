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
	Node* head, *tail;
	int size = 0;
	WordNode* word_head, *word_tail;

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
	//linear serach
	LinkedList search(LinkedList& wordList, LinkedList& positiveList, LinkedList& negativeList);
	//merge sort
	WordNode* mergeLists(WordNode* left, WordNode* right);
	WordNode* splitList(WordNode* head);
	WordNode* mergeSort(WordNode* head);
	//helper
	bool linearSearch(string word);
	void countFrequency();
	void removeDuplicates();
	void sortByFrequency();
	int getSize();
	Node* getHead();
	WordNode* getWordHead();
	void checkDuped(string word);

};
#endif