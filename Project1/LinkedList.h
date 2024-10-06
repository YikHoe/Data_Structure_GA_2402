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
	Node* head;
	int size = 0;
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
	//linear serach
	LinkedList search(LinkedList& wordList, LinkedList& positiveList, LinkedList& negativeList);
	LinkedList search(LinkedList& wordList);
	//merge sort
	WordNode* mergeLists(WordNode* left, WordNode* right, LinkedList& positiveList, LinkedList& negativeList);
	WordNode* mergeLists(WordNode* left, WordNode* right);
	WordNode* splitList(WordNode* head);
	WordNode* mergeSort(WordNode* head, LinkedList& positiveList, LinkedList& negativeList);
	WordNode* mergeSort(WordNode* head);
	//helper
	bool contains(const string& word) const;
	bool isPositive(const string& word, LinkedList& positiveList);
	bool isNegative(const string& word, LinkedList& positiveList);
	void tokenize(string review);
	void countFrequency();
	void removeDuplicates();
	void sortByPosNeg(LinkedList& positiveList, LinkedList& negativeList);
	void sortByFrequency();
	int getSize();
	Node* getHead();
	WordNode* getWordHead();
	void setWordHead(WordNode* node);

};
#endif