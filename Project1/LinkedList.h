#pragma once
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

		void insertFront() {

		}

		void insertBack() {

		}
};