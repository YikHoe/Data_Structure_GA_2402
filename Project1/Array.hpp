#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>
#include <string>  // Include string support
using namespace std;
template<class T>
class Array
{
private:
	T* data; //Pointer to store the array
	int size; //Current number of elements in array
	int arrayCapacity; //Max size of array

	void resizeArray();

public:
	//Constructor
	Array();

	//Constructor with size, defaul value
	Array(int initialSize, T defaultValue);

	//Insert element to the end method
	void insert(T value);

	//Clear the element in the array
	void clear();

	//Check if the array is empty
	//bool isEmpty();

	//Delete an element at a given index
	T remove(int index);

	//Update an element at a given index
	void update(int index, T value);

	//Get element in the array by index
	T& get(int index);

	//Get the current number of elements in the array
	size_t getSize();

	//Get the current size of the array
	size_t getCapacity();

	//Destructor
	~Array();
};

#endif // ARRAY_HPP