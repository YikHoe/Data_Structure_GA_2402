#pragma once
#ifndef CUSTOMARRAYMAP_HPP
#define CUSTOMARRAYMAP_HPP

#include "Array.hpp"

// Define KeyValuePair as a struct
template <class K, class V>
struct KeyValuePair
{
    K key;
    V value;

    // Default constructor
    KeyValuePair() {}

    // Parameterized constructor
    KeyValuePair(K k, V v) : key(k), value(v) {}

    // Getter for key
    K getKey() {
        return key;
    }

    // Getter for value
    V& getValue() {
        return value;
    }

    // Comparison operator to compare keys
    bool operator==(const K& k) const {
        return key == k;
    }
};

// Template class for custom Array Map using KeyValuePair struct
template <class K, class V>
class customArrayMap
{
private:
    // Using the existing Array structure to store KeyValuePair objects
    Array<KeyValuePair<K, V>> mapData;

public:
    // Constructor
    customArrayMap();

    // Insert key-value pair
    void insert(K key, V value);

    // Remove key-value pair by key
    void remove(K key);

    // Update value by key
    void update(K key, V value);

    // Add frequency to 1 by key 
    void addFreqByKey(K key);

    // Get value by key
    V get(K key);

    // Check if key exists
    bool containsKey(K key);

    // Get current size
    int getSize();

    // Get KeyValuePair by index
    KeyValuePair<K, V>& getByIndex(int index);

    // Destructor
    ~customArrayMap();
};

#endif // CUSTOMARRAYMAP_HPP
