#include <iostream>
#include "QuickSort.h"

using namespace std;

Node* QuickSort::partition(Node* start, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node* prev = nullptr;
    Node* curr = start;
    Node* tail = pivot;

    // After partition, 'newHead' will point to the head of the list,
    // and 'newEnd' will point to the last node in the list.
    *newHead = nullptr;
    *newEnd = nullptr;

    while (curr != pivot) {
        if (curr->data < pivot->words) {
            // Insert this node into the 'newHead' part
            if (*newHead == nullptr) {
                *newHead = curr;
            }
            prev = curr;
            curr = curr->nextAddress;
        }
        else {
            // Move the node to the end of the list
            if (prev != nullptr)
                prev->nextAddress = curr->nextAddress;
            Node* temp = curr->nextAddress;
            curr->nextAddress = nullptr;
            tail->nextAddress = curr;
            tail = curr;
            curr = temp;
        }
    }

    // If the pivot is the smallest element, newHead will be pivot
    if (*newHead == nullptr) {
        *newHead = pivot;
    }

    *newEnd = tail;
    return pivot;
}