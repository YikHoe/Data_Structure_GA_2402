#include <iostream>
#include <sstream>
#include "WordLinkedList.h"


WordNode::WordNode(string word_given) : word(word_given), nextAddress(nullptr) {}

WordLinkedList::WordLinkedList() : head(nullptr) {}


WordLinkedList::~WordLinkedList() {
	WordNode* current = head;
	while (current != nullptr) {
		WordNode* temp = current;
		current = current->nextAddress;
		delete temp;
	}


}

void WordLinkedList::insertFront(string word) {
	WordNode* newNode = new WordNode(word);
	newNode->nextAddress = head;
	head = newNode;
}

void WordLinkedList::insertBack(string word) {
	WordNode* newNode = new WordNode(word);
	WordNode* current = head;

	while (current->nextAddress != nullptr) {
		current = current->nextAddress;
	}

	current->nextAddress = newNode;
}

void WordLinkedList::deleteFront() {
	if (head == nullptr) {
		return;
	}

	WordNode* current = head;
	head = head->nextAddress;
	delete current;

}

void  WordLinkedList::deleteBack() {
	if (head == nullptr) {
		return;
	}

	WordNode* current = head;
	WordNode* prev = nullptr;

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

void WordLinkedList::displayList() {
	WordNode* temp = head;

	while (temp != nullptr) {
		cout << "Word: " << temp->word << endl;
		temp = temp->nextAddress;
	}

	cout << string(10, '=') << " END OF LIST " << string(10, '=') << endl;
}




