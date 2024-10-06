#include <iostream>
#include <sstream>
#include "LinkedList.h"

Node::Node(string review_string, string rating_given) : review(review_string), rating(rating_given), nextAddress(nullptr) {}
WordNode::WordNode(string word_string) : word(word_string), frequency(0), nextAddress(nullptr) {}

LinkedList::LinkedList() : head(nullptr), tail(nullptr), word_head(nullptr), word_tail(nullptr), size(0) {}

LinkedList::~LinkedList() {
	Node* current = head;
	while (current != nullptr) {
		Node* temp = current;
		current = current->nextAddress;
		delete temp;
	}

    WordNode* current_word = word_head;
    while (current_word != nullptr) {
        WordNode* temp_word = current_word;
        current_word = current_word->nextAddress;
        delete temp_word;
    }
}

void LinkedList::insertFront(string review, string rating) {
	Node* newNode = new Node(review, rating);
	newNode->nextAddress = head;

    if (head == nullptr) {
        tail = newNode;
    }

	head = newNode;
}

void LinkedList::insertFront(string word) {
    WordNode* newNode = new WordNode(word);
    newNode->nextAddress = word_head;

    if (word_head == nullptr) {
        word_tail = newNode;
    }

    word_head = newNode;
}

void LinkedList::insertBack(string review, string rating) {
	Node* newNode = new Node(review, rating);
	Node* current = head;

	while (current->nextAddress != nullptr) {
		current = current->nextAddress;
	}

	current->nextAddress = newNode;
}

void LinkedList::insertBack(string word) {
    WordNode* newNode = new WordNode(word);
    WordNode* current = word_head;

    while (current->nextAddress != nullptr) {
        current = current->nextAddress;
    }

    current->nextAddress = newNode;
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
        cout << word_temp->word << endl;
        word_temp = word_temp->nextAddress;
    }

    cout << endl << endl << endl;
}

void LinkedList::printReport() {
    WordNode* word_temp = word_head;

    while (word_temp != nullptr) {
        cout << word_temp->word << " = " << word_temp->frequency << endl;
        word_temp = word_temp->nextAddress;
    }

    cout << endl << string(10, '=') << " END OF PROGRAM " << string(10, '=') << endl;
}

// Quick sort
WordNode* LinkedList::partition(WordNode* head, WordNode* tail) {

    // Select the first node as the pivot node
    WordNode* pivot = head;

    // 'pre' and 'curr' are used to shift all 
     // smaller nodes' data to the left side of the pivot node
    WordNode* previous = head;
    WordNode* current = head;

    // Traverse the list until you reach the node after the tail
    while (current != tail->nextAddress) {

        if (current->word < pivot->word) {
            previous = previous->nextAddress;
            swap(current->word, previous->word);
        }

        // Move current to the next node
        current = current->nextAddress;
    }

    swap(pivot->word, previous->word);

    return previous; // new pivot
}

WordNode* LinkedList::partitionByFrequency(WordNode* head, WordNode* tail) {

    // Select the first node as the pivot node
    WordNode* pivot = head;

    // 'pre' and 'curr' are used to shift all 
    // smaller nodes' data to the left side of the pivot node
    WordNode* previous = head;
    WordNode* current = head;

    // Traverse the list until you reach the node after the tail
    while (current != tail->nextAddress) {

        if (current->frequency < pivot->frequency) {
            previous = previous->nextAddress;
            swap(current->frequency, previous->frequency);
        }

        // Move current to the next node
        current = current->nextAddress;
    }

    swap(pivot->frequency, previous->frequency);

    return previous; // new pivot
}

void LinkedList::sortRecur(WordNode* head, WordNode* tail) {
    while (head != nullptr && head != tail) {
        // Call partition to find the pivot node
        WordNode* pivot = partition(head, tail);

        // Recursively sort the smaller part first
        if (pivot != head) {
            sortRecur(head, pivot);
        }

        // Update the head for the next iteration, 
        // effectively tail-recursing on the right partition.
        head = pivot->nextAddress;
    }
}

void LinkedList::sortRecurByFrequency(WordNode* head, WordNode* tail) {
    while (head != nullptr && head != tail) {
        // Call partition to find the pivot node
        WordNode* pivot = partitionByFrequency(head, tail);

        // Recursively sort the smaller part first
        if (pivot != head) {
            partitionByFrequency(head, pivot);
        }

        // Update the head for the next iteration, 
        // effectively tail-recursing on the right partition.
        head = pivot->nextAddress;
    }
}

void LinkedList::quickSort() {
    sortRecur(word_head, word_tail);
}

void LinkedList::quickSortByFrequency() {
    sortRecurByFrequency(word_head, word_tail);
}

// Binary search
WordNode* LinkedList::getMiddle(WordNode* head, WordNode* tail) {
    if (head == nullptr)
        return nullptr;

    WordNode* slow = head;
    WordNode* fast = head->nextAddress;

    while (fast != tail) {
        fast = fast->nextAddress;
        if (fast != tail) {
            slow = slow->nextAddress;
            fast = fast->nextAddress;
        }
    }

    return slow;
}

//void LinkedList::calculateFrequency() {
//    WordNode* current = word_head;
//
//    while (current != nullptr) {
//        WordNode* temp = word_head;
//        while (temp != nullptr) {
//            if (temp->word == current->word) {
//                current->frequency++; // Increment frequency count
//            }
//            temp = temp->nextAddress;
//        }
//        current = current->nextAddress;
//    }
//}

bool LinkedList::binarySearch(string target) {
    WordNode* start = word_head;
    WordNode* end = word_tail;

    while (start != nullptr && end != nullptr && start->word != end->word) {
        WordNode* mid = getMiddle(start, end);
        if (mid == nullptr)
            break;

        if (mid->word == target) {
            return true;
        }
        else if (mid->word < target) {
            start = mid->nextAddress;
        }
        else {
            end = mid;
        }

    }

    return false;
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

Node* LinkedList::getHead() {
    return head;
}

Node* LinkedList::getTail() {
    return tail;
}

WordNode* LinkedList::getWordHead() {
    return word_head;
}

WordNode* LinkedList::getWordTail() {
    return word_tail;
}




