#include <iostream>
#include "LinkedList.h"

Node::Node(string review_string, string rating_given) : review(review_string), rating(rating_given), nextAddress(nullptr) {}
WordNode::WordNode(string word_string) : word(word_string), frequency(0), nextAddress(nullptr) {}

LinkedList::LinkedList() : head(nullptr),tail(nullptr), word_head(nullptr), word_tail(nullptr) {}

Node* LinkedList::getHead() {
	return head;
}

WordNode* LinkedList::getWordHead() {
	return word_head;
}

LinkedList LinkedList::findMatchingWords(LinkedList& positiveList, LinkedList& negativeList) {
	LinkedList foundedList;

	WordNode* currentWordNode = word_head;  // Start from the head of the word list

	while (currentWordNode != nullptr) {  // Traverse the wordList
		// Check if the word exists in positiveList or negativeList
		if (positiveList.linearSearch(currentWordNode->word) || negativeList.linearSearch(currentWordNode->word)) {
			// If the word is found in either list, insert it into the foundedList
			foundedList.insertFront(currentWordNode->word);
		}
		currentWordNode = currentWordNode->nextAddress;  // Move to the next word
	}

	return foundedList;  // Return the list containing matching words
}

void LinkedList::max() {
	if (word_tail == nullptr) {
		return;
	}
	cout << "Maximum used word in the reviews : ";
	int max = word_tail->frequency;
	WordNode* current = word_tail;
	while (current != nullptr) {
		if (current->frequency == max) {
			cout << current->word << ", ";
		}
		else {
			break;
		}
		current = current->nextAddress; 
	}
	cout << endl;

}

void LinkedList::min() {
	if (word_tail == nullptr) {
		return;
	}
	cout << "Minimum used word in the reviews : ";
	int min = word_head->frequency;
	WordNode* current = word_head;
	while (current != nullptr) {
		if (current->frequency == min) {
			cout << current->word << ", ";
		}
		else {
			break;
		}
		current = current->nextAddress;
	}
	cout << endl;
}



bool LinkedList::linearSearch(string word){
	WordNode* current = word_head;  // Start at the head of the list
	while (current != nullptr) {
		if (current->word == word) {
			return true;  // Word found in the list
		}
		current = current->nextAddress;
	}
	return false;  // Word not found in the list
}


WordNode* LinkedList::splitList(WordNode* head) {
	if (head == nullptr || head->nextAddress == nullptr) {
		return head;
	}
	WordNode* slow = head;
	WordNode* fast = head->nextAddress;

	while (fast != nullptr && fast->nextAddress != nullptr) {
		slow = slow->nextAddress;
		fast = fast->nextAddress->nextAddress;
	}

	WordNode* middle = slow->nextAddress;
	slow->nextAddress = nullptr;

	return middle;
}


WordNode* LinkedList::mergeSort(WordNode* head) {
	// Base case: If the list is empty or has only one node
	if (head == nullptr || head->nextAddress == nullptr) {
		return head;
	}

	// Split the list into halves
	WordNode* middle = splitList(head);
	WordNode* left = mergeSort(head);
	WordNode* right = mergeSort(middle);

	// Merge the sorted halves
	return mergeLists(left, right);
}

WordNode* LinkedList::mergeLists(WordNode* left, WordNode* right) {
	// Create a dummy node to simplify merging
	WordNode dummy("");
	WordNode* tail = &dummy;

	while (left != nullptr && right != nullptr) {
		if (left->frequency < right->frequency) {
			tail->nextAddress = left;
			left = left->nextAddress;
		}
		else if (left->frequency > right->frequency) {
			tail->nextAddress = right;
			right = right->nextAddress;
		}
		else {
			// If frequencies are equal, sort lexicographically
			if (left->word <= right->word) {
				tail->nextAddress = left;
				left = left->nextAddress;
			}
			else {
				tail->nextAddress = right;
				right = right->nextAddress;
			}
		}
		tail = tail->nextAddress; // Move the tail pointer
	}

	tail->nextAddress = left ? left : right;
	return dummy.nextAddress;

}


void LinkedList::sortByFrequency() {
	// Sort the linked list by frequency
	word_head = mergeSort(word_head); // Update head after sorting

	// Update the tail pointer if the list is not empty
	if (word_head == nullptr) {
		word_tail = nullptr; // List is empty
	}
	else {
		// Find the new tail of the sorted list
		WordNode* temp = word_head;
		while (temp->nextAddress != nullptr) {
			temp = temp->nextAddress;
		}
		word_tail = temp; // Update the tail
	}
}


LinkedList::~LinkedList() {
	Node* current = head;
	while (current != nullptr) {
		Node* temp = current;
		current = current->nextAddress;
		delete temp;
	}

	WordNode* currentWord = word_head;
	while (currentWord != nullptr) {
		WordNode* temp = currentWord;
		currentWord = currentWord->nextAddress;
		delete temp;
	}


}

void LinkedList::insertFront(string review, string rating) {
	Node* newNode = new Node(review, rating);
	newNode->nextAddress = head;
	head = newNode;
}

void LinkedList::insertFront(string word) {
	WordNode* newNode = new WordNode(word);
	newNode->nextAddress = word_head;
	word_head = newNode;
}

void LinkedList::insertBack(string review, string rating) {
	Node* newNode = new Node(review, rating);
	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* current = head;
		while (current->nextAddress != nullptr) {
			current = current->nextAddress;
		}
		current->nextAddress = newNode;
	}
}

void LinkedList::insertBack(string word) {
	WordNode* newNode = new WordNode(word);
	if (word_head == nullptr) {
		word_head = newNode;
	}
	else {
		WordNode* temp = word_head;
		while (temp->nextAddress != nullptr) {
			temp = temp->nextAddress;
		}
		temp->nextAddress = newNode;
	}
}


void LinkedList::deleteFront() {
	if (head == nullptr && word_head == nullptr) {
		return;
	}

	if (head != nullptr) {
		Node* current = head;
		head = head->nextAddress;
		delete current;
	}
	else {
		WordNode* current = word_head;
		word_head = word_head->nextAddress;
		delete current;
	}


}

void  LinkedList::deleteBack() {
	if (head == nullptr) {
		return;
	}

	if (head != nullptr) {
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
	else {
		WordNode* current = word_head;
		WordNode* prev = nullptr;

		while (current->nextAddress != nullptr) {
			prev = current;
			current = current->nextAddress;
		}

		if (prev == nullptr) {
			word_head = nullptr;
		}
		else {
			prev->nextAddress = nullptr;
		}

		delete current;
	}


}

void LinkedList::displayList() {
	Node* temp = head;
	WordNode* word_temp = word_head;

	while (temp != nullptr) {
		cout << "Review: " << temp->review << endl;
		cout << "Rating: " << temp->rating << endl << endl;
		temp = temp->nextAddress;
	}

	while (word_temp != nullptr) {
		cout << word_temp->word << " = " << word_temp->frequency << endl;
		word_temp = word_temp->nextAddress;
	}

	cout << string(120, '=') << endl;
}


int LinkedList::getSize() {
	WordNode* word_temp = word_head;
	while (word_temp != nullptr) {
		size++;
		word_temp = word_temp->nextAddress;
	}

	return size;

}


void LinkedList::checkDuped(string word) {
	WordNode* current = word_head;

	while (current != nullptr) {
		if (current->word == word) {
			current->frequency += 1;
			return;
		}

		current = current->nextAddress;
	}

	WordNode* newNode = new WordNode(word);
	newNode->nextAddress = word_head;
	newNode->frequency += 1;

	if (word_head == nullptr) {
		word_tail = newNode;
	}

	word_head = newNode;
}





