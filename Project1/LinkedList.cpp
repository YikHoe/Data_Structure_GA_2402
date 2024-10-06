    #include <iostream>
    #include <sstream>
    #include "LinkedList.h"

    Node::Node(string review_string, string rating_given) : review(review_string), rating(rating_given), nextAddress(nullptr) {}
    WordNode::WordNode(string word_string) : word(word_string),frequency(1),nextAddress(nullptr) {}

    LinkedList::LinkedList() : head(nullptr), word_head(nullptr) {}

    Node* LinkedList::getHead() {
        return head;
    }

    WordNode* LinkedList::getWordHead() {
        return word_head;
    }

    void LinkedList::setWordHead(WordNode* node) {
        word_head = node;
    }

    LinkedList LinkedList::search(LinkedList& wordList, LinkedList& positiveList, LinkedList& negativeList) {
        LinkedList foundedList;

        WordNode* currentWordNode = wordList.getWordHead();  // Start from the head of the word list

        while (currentWordNode != nullptr) {  // Traverse the wordList
            // Check if the word exists in positiveList or negativeList
            if (positiveList.contains(currentWordNode->word) || negativeList.contains(currentWordNode->word)) {
                // If the word is found in either list, insert it into the foundedList
                foundedList.insertFront(currentWordNode->word);
            }
            currentWordNode = currentWordNode->nextAddress;  // Move to the next word
        }

        return foundedList;  // Return the list containing matching words
    }

    LinkedList LinkedList::search(LinkedList& wordList) {
        LinkedList maxList;  // List to store all nodes with the max value

        WordNode* current = wordList.getWordHead();  // Start from the head of the list
        string maxValue = current->word;  // Initialize the max value to the first node's word

        // First, find the maximum value
        while (current != nullptr) {
            if (current->word > maxValue) {
                maxValue = current->word;  // Update the max value if the current word is greater
            }
            current = current->nextAddress;  // Move to the next node
        }

        // Second, collect all nodes with the max value
        current = wordList.getWordHead();  // Start again from the head of the list
        while (current != nullptr) {
            if (current->word == maxValue) {
                maxList.insertFront(current->word);  // Insert the word with max value to the maxList
            }
            current = current->nextAddress;  // Move to the next node
        }

        return maxList;  // Return the list containing all nodes with the max value
    }


    bool LinkedList::contains(const string& word) const {
        WordNode* current = word_head;  // Start at the head of the list
        while (current != nullptr) {
            if (current->word == word) {
                return true;  // Word found in the list
            }
            current = current->nextAddress;
        }
        return false;  // Word not found in the list
    }

    bool LinkedList::isPositive(const string& word, LinkedList& positiveList) {
        return positiveList.contains(word);
    }

    bool LinkedList::isNegative(const string& word, LinkedList& negativeList) {
        return negativeList.contains(word);
    }


    WordNode* LinkedList::mergeLists(WordNode* left, WordNode* right, LinkedList& positiveList, LinkedList& negativeList) {
        if (left == nullptr) return right;
        if (right == nullptr) return left;

        WordNode* result = nullptr;

        // Modularized positive/negative check
        if (isPositive(left->word, positiveList) && !isPositive(right->word, positiveList)) {
            result = left;
            result->nextAddress = mergeLists(left->nextAddress, right, positiveList, negativeList);
        }
        else if (!isPositive(left->word, positiveList) && isPositive(right->word, positiveList)) {
            result = right;
            result->nextAddress = mergeLists(left, right->nextAddress, positiveList, negativeList);
        }
        else if (isNegative(left->word, negativeList) && !isNegative(right->word, negativeList)) {
            result = right;
            result->nextAddress = mergeLists(left, right->nextAddress, positiveList, negativeList);
        }
        else if (!isNegative(left->word, negativeList) && isNegative(right->word, negativeList)) {
            result = left;
            result->nextAddress = mergeLists(left->nextAddress, right, positiveList, negativeList);
        }
        else {
            // If both are positive or both are negative, merge by word comparison
            if (left->word <= right->word) {
                result = left;
                result->nextAddress = mergeLists(left->nextAddress, right, positiveList, negativeList);
            }
            else {
                result = right;
                result->nextAddress = mergeLists(left, right->nextAddress, positiveList, negativeList);
            }
        }

        return result;
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

    WordNode* LinkedList::mergeSort(WordNode* head, LinkedList& positiveList, LinkedList& negativeList) {
        if (head == nullptr || head->nextAddress == nullptr) {
            return head;
        }

        // Split the list into two halves
        WordNode* middle = splitList(head);

        // Recursively sort the two halves
        WordNode* left = mergeSort(head, positiveList, negativeList);
        WordNode* right = mergeSort(middle, positiveList, negativeList);

        // Merge the sorted halves based on positive/negative logic
        return mergeLists(left, right, positiveList, negativeList);
    }

    void LinkedList::sortByPosNeg(LinkedList& positiveList, LinkedList& negativeList) {
        word_head = mergeSort(word_head, positiveList, negativeList);
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

        cout << string(10, '=') << " END OF LIST " << string(10, '=') << endl;
    }

    int LinkedList::getSize() {
        WordNode* word_temp = word_head;
        while (word_temp != nullptr) {
            size++;
            word_temp = word_temp->nextAddress;
        }

        return size;

    }

    void LinkedList::countFrequency() {
        WordNode* current = word_head;

        // Reset the frequency for all words first (in case this is called multiple times)
        while (current != nullptr) {
            current->frequency = 0;
            current = current->nextAddress;
        }

        // Traverse the list and count frequency of each word
        current = word_head;
        while (current != nullptr) {
            WordNode* temp = word_head;
            while (temp != nullptr) {
                if (temp->word == current->word) {
                    current->frequency++; // Increment frequency count
                }
                temp = temp->nextAddress;
            }
            current = current->nextAddress;
        }
    }

    WordNode* LinkedList::mergeLists(WordNode* left, WordNode* right) {
        if (left == nullptr) return right;
        if (right == nullptr) return left;

        WordNode* result = nullptr;

        // Sort by frequency in ascending order
        if (left->frequency < right->frequency) {
            result = left;
            result->nextAddress = mergeLists(left->nextAddress, right);
        }
        else if (left->frequency > right->frequency) {
            result = right;
            result->nextAddress = mergeLists(left, right->nextAddress);
        }
        else {
            // If frequencies are equal, sort lexicographically
            if (left->word <= right->word) {
                result = left;
                result->nextAddress = mergeLists(left->nextAddress, right);
            }
            else {
                result = right;
                result->nextAddress = mergeLists(left, right->nextAddress);
            }
        }

        return result;
    }

    WordNode* LinkedList::mergeSort(WordNode* head) {
        if (head == nullptr || head->nextAddress == nullptr) {
            return head;
        }

        // Split the list into two halves
        WordNode* middle = splitList(head);

        // Recursively sort the two halves
        WordNode* left = mergeSort(head);
        WordNode* right = mergeSort(middle);

        // Merge the sorted halves based on frequency
        return mergeLists(left, right);
    }

    void LinkedList::sortByFrequency() {
        countFrequency(); // Make sure frequencies are updated before sorting
        word_head = mergeSort(word_head); // Now sort based on frequency
    }

    void LinkedList::removeDuplicates() {
        if (word_head == nullptr || word_head->nextAddress == nullptr) {
            // List is empty or contains only one element, no duplicates to remove
            return;
        }

        WordNode* current = word_head;

        // Traverse the sorted list and remove adjacent nodes with duplicate words
        while (current != nullptr && current->nextAddress != nullptr) {
            // If the current word is the same as the next word
            if (current->word == current->nextAddress->word) {
                // Save the next node
                WordNode* duplicate = current->nextAddress;
                // Bypass the duplicate node
                current->nextAddress = current->nextAddress->nextAddress;
                // Free the memory of the duplicate node (if necessary)
                delete duplicate;
            }
            else {
                // Move to the next node only if no duplicate was found
                current = current->nextAddress;
            }
        }
    }


    void LinkedList::tokenize(string review) {
        string word = "";
        for (char c : review) {
            // Manually check if the character is alphanumeric
            if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                // Manually convert to lowercase if it's an uppercase letter
                if (c >= 'A' && c <= 'Z') {
                    c = c + 32; // Convert to lowercase by adding ASCII offset
                }
                word += c;
            }
            else {
                if (!word.empty()) {
                    insertFront(word);
                    word = "";
                }
            }
        }

        if (!word.empty()) {
            insertFront(word);
        }
    }




