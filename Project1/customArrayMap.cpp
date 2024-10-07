#include "customArrayMap.hpp"
#include <stdexcept>
using namespace std;

// Constructor
template<class K, class V>
customArrayMap<K, V>::customArrayMap() : mapData() {}

// Insert key-value pair
template<class K, class V>
void customArrayMap<K, V>::insert(K key, V value)
{
    if (containsKey(key)) {
        throw invalid_argument("Key already exists.");
    }
    mapData.insert(KeyValuePair<K, V>(key, value));
}

// Remove key-value pair by key
template<class K, class V>
void customArrayMap<K, V>::remove(K key)
{
    for (int i = 0; i < mapData.getSize(); ++i) {
        if (mapData.get(i).getKey() == key) {  // Use the getter method
            mapData.remove(i);
            return;
        }
    }
    throw out_of_range("Key not found.");
}

// Update value by key
template<class K, class V>
void customArrayMap<K, V>::update(K key, V value)
{
    for (int i = 0; i < mapData.getSize(); ++i) {
        if (mapData.get(i).getKey() == key) {  // Use the getter method
            mapData.get(i).value = value; // Direct access to value is still okay here
            return;
        }
    }
    throw out_of_range("Key not found.");
}

// Add frequency to 1 by key 
template<class K, class V>
void customArrayMap<K, V>::addFreqByKey(K key)
{
    for (int i = 0; i < mapData.getSize(); ++i) {
        if (mapData.get(i).getKey() == key) {  // Use the getter method
            mapData.get(i).value++; // Increment the frequency by 1
            return;
        }
    }
    throw out_of_range("Key not found.");
}

// Get value by key
template<class K, class V>
V customArrayMap<K, V>::get(K key)
{
    for (int i = 0; i < mapData.getSize(); ++i) {
        if (mapData.get(i).getKey() == key) {  // Use the getter method
            return mapData.get(i).getValue(); // Use the getter method
        }
    }
    throw out_of_range("Key not found.");
}

// Check if key exists
template<class K, class V>
bool customArrayMap<K, V>::containsKey(K key)
{
    for (int i = 0; i < mapData.getSize(); ++i) {
        if (mapData.get(i).getKey() == key) {  // Use the getter method
            return true;
        }
    }
    return false;
}

// Get current size of map
template<class K, class V>
int customArrayMap<K, V>::getSize()
{
    return mapData.getSize();
}

// Get KeyValuePair by index
template<class K, class V>
KeyValuePair<K, V>& customArrayMap<K, V>::getByIndex(int index) {
    if (index < 0 || index >= mapData.getSize()) {
        throw out_of_range("Index is out of range");
    }
    return mapData.get(index); // Use the existing get method from Array
}

// Destructor
template<class K, class V>
customArrayMap<K, V>::~customArrayMap() {}

template class customArrayMap<string, int>; // Add specific instantiation as needed