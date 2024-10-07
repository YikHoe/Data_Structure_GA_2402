<<<<<<< HEAD
#include <iostream>

=======
#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
>>>>>>> yikhoe
using namespace std;

struct Node
{
	string review, rating;
	Node* nextAddress;
<<<<<<< HEAD
	Node(string review_string, string rating_given) : review(review_string), rating(rating_given), nextAddress(nullptr) {}
=======
	Node(string review_string, string rating_given);
};

struct WordNode
{
	string word;
	int frequency;
	WordNode* nextAddress;
	WordNode(string word_string);
>>>>>>> yikhoe
};

class LinkedList
{
	private:
<<<<<<< HEAD
		Node* head;

	public:
		LinkedList() : head(nullptr) {}

		~LinkedList() {
			Node* current = head;
			while (current != nullptr) {
				Node* temp = current;
				current = current->nextAddress;
				delete temp;
			}
		}

		void insertFront(string review, string rating) {
			Node* newNode = new Node(review, rating);
			newNode->nextAddress = head;
			head = newNode;
		}

		void insertBack(string review, string rating) {
			Node* newNode = new Node(review, rating);
			Node* current = head;
			
			while (current->nextAddress != nullptr) {
				current = current->nextAddress;
			}

			current->nextAddress = newNode;
		}

		void deleteFront() {
			if (head == nullptr) {
				return;
			}

			Node* current = head;
			head = head->nextAddress;
			delete current;

		}

		void deleteBack() {
			if (head == nullptr) {
				return;
			}

			Node* current = head;
			Node* prev = nullptr;

			while (current->nextAddress != nullptr) {
				prev = current;
				current = current->nextAddress;
			}

			if (prev == nullptr) {
				head = nullptr;
			}
			else {
				prev->nextAddress = nullptr;
			}

			delete current;
		}

		void displayList() {
			Node* temp = head;

			while (temp != nullptr) {
				cout << "Review: " << temp->review << endl;
				cout << "Rating: " << temp->rating << endl << endl;
				temp = temp->nextAddress;
			}

			cout << string(10, '=') << " END OF LIST " << string(10, '=') << endl;
		}
};
=======
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
		void resetFrequencies();
		void checkDuped(string word);

		//void calculateFrequency();
		//void removeDuplicates();

		Node* getHead();
		Node* getTail();
		WordNode* getWordHead();
		WordNode* getWordTail();

};
#endif
>>>>>>> yikhoe
