// References and sources of adapted codes
// 
// Agarwal, S. (2021, November 11). Binary Search on Linked List. Naukri. 
//		https://www.naukri.com/code360/library/binary-search-on-linked-list
// 
// GeeksforGeeks. (2013, June 28). QuickSort on Singly Linked List. GeeksforGeeks.
//		https://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
// 
// GeeksforGeeks.(2018, March 21). Binary Search on Singly Linked List. GeeksforGeeks. 
//		https://www.geeksforgeeks.org/binary-search-on-singly-linked-list/
// 
// Jump Search Algorithm. (n.d.). 
//		https://www.tutorialspoint.com/data_structures_algorithms/jump_search_algorithm.htm#:~:text=The%20time%20complexity%20of%20the,complexity%20is%20O(1).
// 
// GeeksforGeeks. (2024a, July 31).Search an element in a Linked List(Iterative and Recursive).GeeksforGeeks.
//      https://www.geeksforgeeks.org/search-an-element-in-a-linked-list-iterative-and-recursive/
//
// GeeksforGeeks. (2024b, September 4).Find smallest and largest elements in singly linked list.GeeksforGeeks.
//      https://www.geeksforgeeks.org/find-smallest-largest-elements-singly-linked-list/
// 
// Iyer, S. (2024, September 25). Hoare’s vs. Lomuto’s Partition Scheme in Quicksort. Interview Kickstart LLC. 
//		https://www.interviewkickstart.com/blogs/learn/hoares-vs-lomuto-partition-scheme-quicksort
// 
// Jain, A. (2021, September 7). Linked List | Binary search on Linked List. PrepBytes Blog. 
//		https://www.prepbytes.com/blog/linked-list/binary-search-on-linked-list/
// 
// Jain, D. (2016, March 30). QuickSort Tail Call Optimization (Reducing worst case space to Log n ). GeeksforGeeks. 
//		https://www.geeksforgeeks.org/quicksort-tail-call-optimization-reducing-worst-case-space-log-n/
// 
// Merge Sort a Linked List. (n.d.).Stack Overflow.
//      https://stackoverflow.com/questions/7685/merge-sort-a-linked-list/
// Yadav, B. (2022, December 19). Doubly Linked List Data Structure In C++ - Scaler Topics. Scaler Topics. 
//		https://www.scaler.com/topics/doubly-linked-list-cpp/

#include <iostream>
#include <chrono>
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
	size++;
}

void LinkedList::insertFront(string word) {
	WordNode* newNode = new WordNode(word);
	newNode->nextAddress = word_head;

	if (word_head == nullptr) {
		word_tail = newNode;
	}

	word_head = newNode;
	size++;
}

void LinkedList::insertBack(string review, string rating) {
	Node* newNode = new Node(review, rating);
	if (tail == nullptr) {
		head = tail = newNode;
	}
	else {
		tail->nextAddress = newNode;
		tail = newNode;
	}
	size++;
}

void LinkedList::insertBack(string word) {
	WordNode* newNode = new WordNode(word);
	if (word_tail == nullptr) {
		word_head = word_tail = newNode;
	}
	else {
		word_tail->nextAddress = newNode;
		word_tail = newNode;
	}
	size++;
}

void LinkedList::deleteFront() {
	if (head == nullptr && word_head == nullptr) {
		return;
	}

	if (head != nullptr) { // delete from node linked list
		Node* current = head;
		head = head->nextAddress;
		delete current;
	}
	else { // delete from word node linked list
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

Node* LinkedList::getReview(int id) {
	if (size == 0) {
		return nullptr;
	}
	
	Node* current = head;
	int sizeCnt = 0;
	while (sizeCnt < id && current != nullptr) {
		current = current->nextAddress;
		sizeCnt++;
	}

	return current;
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
		if (word_temp->frequency != 0) {
			cout << "\t - " << word_temp->word << " = " << word_temp->frequency << endl;
		}

		word_temp = word_temp->nextAddress;
	}

	cout << endl << endl << endl;
}

//Jump Search
//Helper for Jump Search adapted from Jump Search Algorithm. (n.d.)
WordNode* LinkedList::jumpByBlockSize(int blockSize, WordNode* startNode) {
	WordNode* current = startNode;
	for (int i = 0; i < blockSize && current != nullptr; i++) {
		current = current->nextAddress;
	}
	return current;
}

//Jump Search Algorithm adapted from Jump Search Algorithm. (n.d.)
bool LinkedList::jumpSearch(string word) {
	// Set a fixed block size for jumping
	int listSize = getSize();
	int blockSize = round(sqrt(listSize));
	WordNode* current = word_head;
	WordNode* prev = nullptr;

	while (current != nullptr && current->word < word) {
		prev = current;
		current = jumpByBlockSize(blockSize, current);
	}

	// Perform linear search within the block
	current = prev;
	while (current != nullptr && current->word <= word) {
		// Word found in the list
		if (current->word == word) {
			current->frequency++;
			return true;
		}
		current = current->nextAddress;
	}

	// Word not found in the list
	return false;
}
// Helper function to jump ahead in blocks to find the target frequency
WordNode* LinkedList::jumpList(int frequency, bool isMaxSearch) {
	int listSize = getSize();
	int blockSize = sqrt(listSize);  // Calculate block size
	WordNode* current = word_head;
	WordNode* prev = nullptr;

	// Jump ahead in blocks
	while (current != nullptr && ((isMaxSearch && current->frequency < frequency) ||
		(!isMaxSearch && current->frequency > frequency))) {
		prev = current;
		for (int i = 0; i < blockSize && current != nullptr; ++i) {
			current = current->nextAddress;
		}
	}

	// Return the start of the block where the frequency might be found
	return (prev == nullptr) ? word_head : prev;
}

// Jump Search for Maximum Frequency Word
void LinkedList::jumpFindMax() {
	if (word_head == nullptr) {
		return;
	}

	int maxFrequency = word_tail->frequency; // Since tail holds max frequency
	WordNode* blockStart = jumpList(maxFrequency, true); // Jump search for max

	// Now, linear search in the identified block for max frequency
	cout << "Maximum used word in the reviews: ";
	displayMinMaxWord(blockStart, maxFrequency);
}

// Jump Search for Minimum Frequency Word
void LinkedList::jumpFindMin() {
	if (word_head == nullptr) {
		return;
	}

	int minFrequency = word_head->frequency; // Since head holds min frequency
	WordNode* blockStart = jumpList(minFrequency, false); // Jump search for min

	// Now, linear search in the identified block for min frequency
	cout << "Minimum used word in the reviews: ";
	displayMinMaxWord(blockStart, minFrequency);
}

// Dislay words matching the given frequency in the identified block
void LinkedList::displayMinMaxWord(WordNode* start, int frequency) {
	WordNode* current = start;

	while (current != nullptr) {
		if (current->frequency == frequency) {
			cout << current->word << ", ";
		}
		current = current->nextAddress;
	}
	cout << endl;
}

//Merge Sort
//Split List Function adpated from (Merge Sort a Linked List, n.d.)
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

//Merge List Function adapted from (Merge Sort a Linked List, n.d.)
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

//Merge Sort Function adapted from (Merge Sort a Linked List, n.d.)
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

void LinkedList::mergeSortByFrequency() {
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

// Quicksort algorithms adapted and referenced from GeeksforGeeks (2013), Iyer (2024), Jain (2016)
// Quick sort
WordNode* LinkedList::partition(WordNode* head, WordNode* tail) {
	if (head == tail) {
		return head;
	}

	int pivot_freq = head->frequency;
	string pivot_word = head->word;
	WordNode* pre = head;
	WordNode* current = head->nextAddress;

	while (current != tail->nextAddress) {
		// First check frequency of word, sort by frequency
		// if same frequency then sort by alphabetical order
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

	// Swapping nodes
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

void LinkedList::quickSort() {
	sortRecur(word_head, word_tail);
}

// Binary search algorithms adapted and referenced from Agarwal (2021), GeeksforGeeks (2018), Jain (2021)
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
	//Timer timer;
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

	int maxWordCount = word_tail->frequency;
	cout << "Maximum used word in the reviews : ";

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
// END of binary search algorithms

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
			current->frequency++;
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
	size++;
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

int LinkedList::getSize() {
	return size;
}

