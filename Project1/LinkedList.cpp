#include <iostream>
#include <chrono>
#include "LinkedList.h"

using namespace std::chrono;

Node::Node(string review_string, string rating_given) : review(review_string), rating(rating_given), nextAddress(nullptr) {}
WordNode::WordNode(string word_string) : word(word_string), frequency(0), nextAddress(nullptr) {}

LinkedList::LinkedList() : head(nullptr),tail(nullptr), word_head(nullptr), word_tail(nullptr) {}

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


    head = tail = nullptr;
    word_head = word_tail = nullptr;
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
    if (word_tail == nullptr) { // List is empty
        word_head = word_tail = newNode;
    }
    else {
        word_tail->nextAddress = newNode;
        word_tail = newNode;
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
        cout << word_temp->word << endl;
        word_temp = word_temp->nextAddress;
    }

    cout << endl << endl << endl;
}

void LinkedList::printReport() {
    WordNode* word_temp = word_head;

    while (word_temp != nullptr) {
        if (word_temp->frequency != 0) {
            cout << word_temp->word << " = " << word_temp->frequency << endl;
        }

        word_temp = word_temp->nextAddress;
    }

    cout << endl << endl << endl;
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

void LinkedList::linearFindmax() {
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

void LinkedList::linearFindmin() {
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
            string temp = current->word;
            current->word = previous->word;
            previous->word = temp;
        }

        // Move current to the next node
        current = current->nextAddress;
    }

    string temp = pivot->word;
    pivot->word = previous->word;
    previous->word = temp;

    return previous; // new pivot
}

WordNode* LinkedList::partitionByFrequency(WordNode* head, WordNode* tail) {
    if (head == tail) {
        return head;
    }

    int pivot_freq = head->frequency;
    string pivot_word = head->word;
    WordNode* pre = head;
    WordNode* current = head->nextAddress;

    while (current != tail->nextAddress) {
        if (current->frequency < pivot_freq || (current->frequency == pivot_freq && current->word < pivot_word)) {
            pre = pre->nextAddress;

            string word_temp = pre->word;
            int freq_temp = pre->frequency;

            pre->word = current->word;
            pre->frequency = current->frequency;
            current->word = word_temp;
            current->frequency = freq_temp;
        }
        current = current->nextAddress;
    }
    
    string word_temp = head->word;
    int freq_temp = head->frequency;

    head->word = pre->word;
    head->frequency = pre->frequency;
    pre->word = word_temp;
    pre->frequency = freq_temp;

    return pre; // new pivot
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
    if (head == nullptr || head == tail) {
        return;
    }

    WordNode* pivot = partitionByFrequency(head, tail);

    // Recursively sort the left partition
    if (pivot != head) {
        WordNode* temp = head;
        while (temp->nextAddress != pivot) {
            temp = temp->nextAddress;
        }
        sortRecurByFrequency(head, temp);
    }

    // Recursively sort the right partition
    if (pivot->nextAddress != nullptr && pivot->nextAddress != tail->nextAddress) {
        sortRecurByFrequency(pivot->nextAddress, tail);
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
    if (head == nullptr || head == tail) {
        return head;
    }

    WordNode* slow = head;
    WordNode* fast = head->nextAddress;

    while (fast != tail && fast->nextAddress != tail) {
        slow = slow->nextAddress;
        fast = fast->nextAddress->nextAddress;
    }

    return slow;
}

bool LinkedList::binarySearch(string target) {
    WordNode* start = word_head;
    WordNode* end = nullptr;

    while (start != end) {
        WordNode* mid = getMiddle(start, end);
        if (mid == nullptr) {
            break;
        }

        if (mid->word == target) {
            mid->frequency += 1;
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

// max_or_max serve as flag to determine find max or find min
// FIND MAX : 0 | false
// FIND MIN : 1 | true
void LinkedList::binaryFindAll(WordNode* start, WordNode* end, int frequency, bool max_or_min) {
    // * terminate process if linked list is null * //
    if (start == end || start == nullptr) {
        return;
    }

    WordNode* mid = getMiddle(start, end);

    // * terminate process if linked list has only 1 node * //
    if (mid == nullptr) {
        return;
    }

    if (mid->frequency == frequency) {
        cout << mid->word << ", ";
    }

    // search left of the list
    if (max_or_min == true && mid->frequency >= frequency) {
        binaryFindAll(start, mid, frequency, max_or_min);
    }
    else if (max_or_min == false && mid->frequency <= frequency) {
        binaryFindAll(start, mid, frequency, max_or_min);
    }
    
    // search right of the list
    binaryFindAll(mid->nextAddress, end, frequency, max_or_min);

}

void LinkedList::binaryFindMax() {
    if (word_tail == nullptr) {
        return;
    }

    // Find the maximum frequency (in your case, it's at word_tail)
    int maxWordCount = word_tail->frequency;

    cout << "Maximum used word in the reviews : ";

    // Start binary search for all words with maximum frequency
    WordNode* start = word_head;
    WordNode* end = nullptr;

    binaryFindAll(start, end, maxWordCount, 0);
    
    cout << endl << endl;
}

void LinkedList::binaryFindMin() {
    if (word_tail == nullptr) {
        return;
    }

    int minWordCount = word_head->frequency;
    cout << "Minimum used word in the reviews : ";

    WordNode* current = word_head;

    while (current != nullptr) {
        if (current->frequency < minWordCount) {
            minWordCount = current->frequency;
        }
        current = current->nextAddress;
    }

    // Now perform a binary search to find all nodes with that minimum frequency
    WordNode* start = word_head;
    WordNode* end = nullptr;

    binaryFindAll(start, end, minWordCount, 1);

    cout << endl << endl;
}

void LinkedList::resetFrequencies() {
    WordNode* current = word_head;
    while (current != nullptr) {
        current->frequency = 0; // Reset frequency count
        current = current->nextAddress;
    }
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




