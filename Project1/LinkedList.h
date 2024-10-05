#include <iostream>

using namespace std;

struct Node
{
	string review, rating;
	Node* nextAddress;
	Node(string review_string, string rating_given) : review(review_string), rating(rating_given), nextAddress(nullptr) {}
};

class LinkedList
{
	private:
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