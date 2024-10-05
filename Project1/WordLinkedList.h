#include <string>
#if 0

using namespace std;

struct WordNode
{
	string word;
	WordNode* nextAddress;
	WordNode(string word_given);
};

class WordLinkedList
{
private:
	WordNode* head;

public:
	WordLinkedList();
	~WordLinkedList();
	void insertFront(string word_given);
	void insertBack(string word_given);
	void deleteFront();
	void deleteBack();
	void displayList();
	WordNode* getHead() const {
		return head;
	}
};
#endif
