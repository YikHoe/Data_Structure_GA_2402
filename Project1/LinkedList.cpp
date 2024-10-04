#include <iostream>
#include <sstream>
#include "LinkedList.h"
#include "WordLinkedList.h"

Node::Node(string review_string, string rating_given, string word_founded) : review(review_string), rating(rating_given), word(word_founded), nextAddress(nullptr) {}

Node::Node() {}

LinkedList::LinkedList() : head(nullptr) {}

LinkedList LinkedList::search(const WordLinkedList& positiveList, const WordLinkedList& negativeList) {
    Node* resultHead = nullptr;   // Head of the result linked list
    Node* resultTail = nullptr;   // Tail to keep track of where to add new nodes
    Node* current = head;
    LinkedList reviewList;

    while (current != nullptr) {
        stringstream ss(current->review);  // Tokenize the review
        string word;
        string positiveWordList;  // List to store found positive words
        string negativeWordList;  // List to store found negative words
        int positiveCount = 0;    // Counter for positive words
        int negativeCount = 0;    // Counter for negative words
        bool matchFound = false;

        // Tokenize the review and check for positive and negative words
        while (ss >> word) {
            // Check for positive words
            WordNode* positiveCurrent = positiveList.getHead();
            while (positiveCurrent != nullptr) {
                if (word == positiveCurrent->word) {
                    positiveWordList += "- " + word + "\n";  // Add matching positive word to the list
                    positiveCount++;  // Increment positive word count
                    matchFound = true;
                    break;  // No need to keep searching once a match is found
                }
                positiveCurrent = positiveCurrent->nextAddress;
            }

            // Check for negative words
            WordNode* negativeCurrent = negativeList.getHead();
            while (negativeCurrent != nullptr) {
                if (word == negativeCurrent->word) {
                    negativeWordList += "- " + word + "\n";  // Add matching negative word to the list
                    negativeCount++;  // Increment negative word count
                    matchFound = true;
                    break;  // No need to keep searching once a match is found
                }
                negativeCurrent = negativeCurrent->nextAddress;
            }
        }

        if (matchFound) {
            // Build the formatted result string
            string wordList = "Positive Words = " + to_string(positiveCount) + ":\n";
            wordList += positiveWordList;  // Add positive words list

            wordList += "Negative Words = " + to_string(negativeCount) + ":\n";
            wordList += negativeWordList;  // Add negative words list

            // Insert the formatted result into the review list
            reviewList.insertFront(current->review, current->rating, wordList);
        }

        current = current->nextAddress;
    }

    return reviewList;  // Return the list containing matching reviews
}



LinkedList::~LinkedList() {
	Node* current = head;
	while (current != nullptr) {
		Node* temp = current;
		current = current->nextAddress;
		delete temp;
	}


}

void LinkedList::insertFront(string review, string rating, string word) {
	Node* newNode = new Node(review, rating, word);
	newNode->nextAddress = head;
	head = newNode;
}

void LinkedList::insertBack(string review, string rating, string word) {
	Node* newNode = new Node(review, rating, word);
	Node* current = head;

	while (current->nextAddress != nullptr) {
		current = current->nextAddress;
	}

	current->nextAddress = newNode;
}

void LinkedList::deleteFront() {
	if (head == nullptr) {
		return;
	}

	Node* current = head;
	head = head->nextAddress;
	delete current;

}

void  LinkedList::deleteBack() {
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

void LinkedList::displayList() {
	Node* temp = head;

	while (temp != nullptr) {
		cout << "Review: " << temp->review << endl;
		cout << temp->word << endl;
		cout << "Rating: " << temp->rating << endl << endl;
		temp = temp->nextAddress;
	}

	cout << string(10, '=') << " END OF LIST " << string(10, '=') << endl;
}





