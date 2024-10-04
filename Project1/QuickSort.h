#pragma once
#include <iostream>

using namespace std;

struct Node {
	string words;
	Node* nextAddress;
	Node(string word_list) : words(word_list), nextAddress(nullptr) {}
};

class QuickSort
{
private:
	Node* partition(Node* start, Node* end, Node** newHead, Node** newEnd);

public:
	QuickSort();
	void sort(Node* start, Node* end);
};