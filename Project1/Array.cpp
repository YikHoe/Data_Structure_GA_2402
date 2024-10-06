#include "Array.hpp"
using namespace std;

template <class T>
Array<T>::Array()
{
	size = 0;
	//The initialized array can store 10 elements at the beginning
	arrayCapacity = 10;
	//Memory allocation
	data = new T[arrayCapacity];
}

template <class T>
Array<T>::Array(int initialSize, T defaultValue) {
    size = initialSize;
    arrayCapacity = initialSize > 10 ? initialSize : 10; // Ensure at least a capacity of 10
    data = new T[arrayCapacity];

    // Initialize all elements with the default value
    for (int i = 0; i < initialSize; i++) {
        data[i] = defaultValue;
    }
}

template <class T>
void Array<T>::insert(T value)
{
	//Resize array if the array capacity is not enough
	if (size >= arrayCapacity)
	{
		resizeArray();
	}
	//Insert the new element at the end of array
	data[size] = value;
	size++;
}

template <class T>
void Array<T>::clear() {
	// Simply reset the size to 0, so no elements are considered present
	size = 0;
}

//template <class T>
//bool Array<T>::isEmpty() {
//	return size == 0;
//}

template <class T>
T Array<T>::remove(int index)
{
	if (index >= 0 && index < size)
	{
		//Shift elements to the left
		for (int i = index; i < size - 1; i++)
		{
			data[i] = data[i + 1];
		}
		//Decrease the size after removing a element
		size--;
	}
	else
	{
		//Throw an exception if index is out of bound
		throw out_of_range("Index is out of range");
	}
}

template <class T>
void Array<T>::update(int index, T value)
{
	if (index >= 0 && index < size)
	{
		//Update the element value if the index is found
		data[index] = value;
	}
	else
	{
		//Throw an exception if index is out of bound
		throw out_of_range("Index is out of range");
	}
}

template <class T>
T& Array<T>::get(int index)
{
	if (index >= 0 && index < size)
	{
		//Return the element if it is found
		return data[index];
	}
	else
	{
		//Throw an exception if index is out of bound
		throw out_of_range("Index is out of range");
	}
}

template <class T>
size_t Array<T>::getSize()
{
	return size;
}

template <class T>
size_t Array<T>::getCapacity()
{
	return arrayCapacity;
}

template <class T>
void Array<T>::resizeArray()
{
	//Double the capacity size
	int newCapacity = arrayCapacity * 2;
	//Create new array with new capacity
	T* temp = new T[newCapacity];
	//Copy elements from old array to new array
	for (int i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}
	//Delete old array after copying
	delete[] data;
	//Point to new array and update capacity
	data = temp;
	arrayCapacity = newCapacity;
}

template <class T>
Array<T>::~Array()
{
	delete[] data;
}

template class Array<string>;
template class Array<int>;
template class Array<float>;
template class Array<short>;
template class Array<long>;
template class Array<long long>;
template class Array<unsigned int>;
template class Array<unsigned short>;
template class Array<unsigned long>;
template class Array<unsigned long long>;
template class Array<double>;
template class Array<long double>;
template class Array<char>;
template class Array<unsigned char>;
template class Array<wchar_t>;
template class Array<char16_t>;
template class Array<char32_t>;
template class Array<bool>;
template class Array<pair<string, int>>;