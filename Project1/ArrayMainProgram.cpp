//References
//Krahets. (n.d.-a). 11.5 Quick sort - Hello Algo. Hello Algo. 
//      https://www.hello-algo.com/en/chapter_sorting/quick_sort/

//Krahets. (n.d.-b). 11.6 Merge sort - Hello Algo. Hello Algo. 
//      https://www.hello-algo.com/en/chapter_sorting/merge_sort/


#include <iostream>
#include "Array.hpp"
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;
// Read words from a file and store them in array
void readWordsFromFile(const string& filename, Array<string>& stringArray) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string word;
    while (file >> word) {
        stringArray.insert(word);
    }
    file.close();
}

// Read reviews from a CSV file
void readReviewsFromCSV(const string& filename, Array<pair<string, int>>& hotelReview) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening CSV file: " << filename << endl;
        return;
    }

    string line;
    // Skip header
    getline(file, line);

    int rowCount = 0;
    //Modify here to set how many rows to read
    while (getline(file, line) && rowCount < 300) {
        stringstream ss(line);
        string review;
        int rating;

        int commaPos = line.rfind(',');
        if (commaPos != string::npos) {
            review = line.substr(0, commaPos);
            rating = stoi(line.substr(commaPos + 1));

            hotelReview.insert(make_pair(review, rating));
            rowCount++;
        }
    }
}

// Count positive and negative words in a review
//linear search to search positive word
void linearSearchForWords(Array<string>& words, string& word, int& wordCount, Array<string>& foundWords, bool& isPositive) {
    for (int i = 0; i < words.getSize(); i++) {
        if (word == words.get(i)) {
            wordCount++;
            foundWords.insert(word);
            isPositive = true;
            break;
        }
    }
}

//linear search to search negative word
//void linearSearchForNegativeWords(Array<string>& negativeWords, string& word, int& negativeCount, Array<string>& foundNegativeWords) {
//    for (int i = 0; i < negativeWords.getSize(); i++) {
//        if (word == negativeWords.get(i)) {
//            negativeCount++;
//            foundNegativeWords.insert(word);
//            break;
//        }
//    }
//}

//binary search to search positive word
void binarySearchForWords(Array<string>& words, string& word, int& wordCount, Array<string>& foundWords, bool& isPositive) {
    int low = 0;
    int high = words.getSize() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        string midWord = words.get(mid);
        if (midWord == word) {
            wordCount++;
            foundWords.insert(word);
            isPositive = true;
            break;
        }
        else if (midWord > word) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
}

//binary search to search negative word
//void binarySearchForNegativeWords(Array<string>& negativeWords, string& word, int& negativeCount, Array<string>& foundNegativeWords) {
//    int low = 0;
//    int high = negativeWords.getSize() - 1;
//    while (low <= high) {
//        int mid = (low + high) / 2;
//        string midWord = negativeWords.get(mid);
//        if (midWord == word) {
//            negativeCount++;
//            foundNegativeWords.insert(word);
//            break;
//        }
//        else if (midWord > word) {
//            high = mid - 1;
//        }
//        else {
//            low = mid + 1;
//        }
//    }
//}

void countPositiveNegativeWords(const string& review, Array<string>& positiveWords, Array<string>& negativeWords, int& positiveCount, int& negativeCount, Array<string>& foundPositiveWords, Array<string>& foundNegativeWords) {
    positiveCount = 0;
    negativeCount = 0;

    // Split review into words
    stringstream ss(review);
    string word;
    auto countWordStart = high_resolution_clock::now();
    while (ss >> word) {
        bool isPositive = false;
        // Check if word is in positive or negative words list
        // Call linear search function
        linearSearchForWords(positiveWords, word, positiveCount, foundPositiveWords, isPositive);
        // Call binary search function
        //binarySearchForWords(positiveWords, word, positiveCount, foundPositiveWords, isPositive);
        // Run only if the word is not found in positive, Reduce redundancy
        if (!isPositive) {
            //Call linear search function
            linearSearchForWords(negativeWords, word, negativeCount, foundNegativeWords, isPositive);
            // Call binary search function
            //binarySearchForWords(negativeWords, word, negativeCount, foundNegativeWords, isPositive);
        }
    }

    auto countWordStop = high_resolution_clock::now();
    auto countWordDuration = duration_cast<nanoseconds>(countWordStop - countWordStart);
    cout << "Count Word Execution time: " << countWordDuration.count() << " nano seconds" << endl;
}

// Calculate the normalized sentiment score
float calculateSentimentScore(int positiveCount, int negativeCount) {
    int N = positiveCount + negativeCount;
    int rawScore = positiveCount - negativeCount;
    int minRawScore = -N;
    int maxRawScore = N;

    if (maxRawScore == minRawScore) return 3.0f; // If no range, neutral score

    float normalizedScore = float(rawScore - minRawScore) / (maxRawScore - minRawScore);
    return 1.0f + (4.0f * normalizedScore); // Scale between 1 and 5
}

// Display sentiment summary
void summarizeSentiment(Array<pair<string, int>>& hotelReviews, Array<string>& positiveWords, Array<string>& negativeWords,
    int& totalPositiveWords, int& totalNegativeWords)
{
    int totalPositiveReviews = 0;
    int totalNegativeReviews = 0;
    int totalNeutralReviews = 0;

    for (int i = 0; i < hotelReviews.getSize(); i++) {
        string review = hotelReviews.get(i).first;
        int rating = hotelReviews.get(i).second;

        Array<string> foundPositiveWords;
        Array<string> foundNegativeWords;
        int positiveCount = 0, negativeCount = 0;
        countPositiveNegativeWords(review, positiveWords, negativeWords, positiveCount, negativeCount, foundPositiveWords, foundNegativeWords);
        
        //Update total counts
        totalPositiveWords += positiveCount;
        totalNegativeWords += negativeCount;
        
        //display user review
        cout << "Review " << i + 1 << ":" << review << endl;
        //display positive word count and list
        cout << "Positive words \t\t: " << positiveCount << endl;
        for (int j = 0; j < foundPositiveWords.getSize(); j++) {
            cout << "\t- " << foundPositiveWords.get(j) << endl;
        }

        //display negative word count and list
        cout << "Negative words \t\t: " << negativeCount << endl;
        for (int j = 0; j < foundNegativeWords.getSize(); j++) {
            cout << "\t- " << foundNegativeWords.get(j) << endl;
        }

        cout << endl;
        float sentimentScore = calculateSentimentScore(positiveCount, negativeCount);
        int roundScore = round(sentimentScore);
        // display sentiment score
        cout << "Sentiment score (1-5) \t= " << sentimentScore << ", thus the rating should be equal to " << roundScore << endl;
        // display user rating
        cout << "User Ratings \t\t= " << rating << endl;
        // evaluate the accuracy 
        if (abs(roundScore - rating) < 1.0) {
            cout << "Analysis output: User's subjective evaluation matches the sentiment score provided by the analysis." << endl;
            cout << "There is a consistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment." << endl;
        }
        else {
            cout << "Analysis output: User's subjective evaluation does not match the sentiment score provided by the analysis." << endl;
            cout << "There is an inconsistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment." << endl;
        }
        cout << endl;
    }
}

// Function to concatenate two arrays with initial frequency set to 0
void concatenateArrays(Array<string>& positiveWords, Array<string>& negativeWords, Array<pair<string, int>>& concatenatedWords) {
    // Insert all positive words with frequency 0
    for (int i = 0; i < positiveWords.getSize(); i++) {
        concatenatedWords.insert(make_pair(positiveWords.get(i), 0));  // Set frequency to 0
    }

    // Insert all negative words with frequency 0
    for (int i = 0; i < negativeWords.getSize(); i++) {
        concatenatedWords.insert(make_pair(negativeWords.get(i), 0));  // Set frequency to 0
    }
}

// Count the frequency of positive and negative words in every review
void countWordFrequency(Array<pair<string, int>>& hotelReviews, Array<pair<string, int>>& positiveAndNegativeWords) {
    // Iterate through each review in hotelReviews
    for (int i = 0; i < hotelReviews.getSize(); i++) {
        // Extract the review (first part of the pair)
        stringstream ss(hotelReviews.get(i).first);  // Get the review text
        string word;

        // Split the review into words
        while (ss >> word) {
            bool found = false;

            // Linear search to find if the word already exists in positiveAndNegativeWords
            for (int j = 0; j < positiveAndNegativeWords.getSize(); j++) {
                if (positiveAndNegativeWords.get(j).first == word) {
                    // If the word is found, increment its frequency
                    positiveAndNegativeWords.get(j).second++;
                    found = true;
                    break;
                }
            }

            // If the word is not found in positiveAndNegativeWords, we skip it
            // because it's neither positive nor negative based on the predefined lists
        }
    }
}


void linearSearch(Array<pair<string, int>>& positiveAndNegativeWords, int& targetFreq, Array<string>& words) {

    for (int i = 0; i < positiveAndNegativeWords.getSize(); i++) {
        int wordFreq = positiveAndNegativeWords.get(i).second;
        if (wordFreq == targetFreq) {
            words.insert(positiveAndNegativeWords.get(i).first);
        }
    }
}


void binarySearch(Array<pair<string, int>>& positiveAndNegativeWords, int low, int high, int targetFreq, Array<bool>& visited, Array<string>& words) {
    if (low <= high) {
        int mid = (low + high) / 2;
        int wordFreq = positiveAndNegativeWords.get(mid).second;

        //make sure the wordFreq is not visited
        if (wordFreq == targetFreq && !visited.get(mid)){
            // insert founded word into list
            words.insert(positiveAndNegativeWords.get(mid).first);
            //Mark the index as visited
            visited.update(mid, true);

            //Continue search in diff direction 
            binarySearch(positiveAndNegativeWords, low, mid - 1, targetFreq, visited, words);
            binarySearch(positiveAndNegativeWords, mid + 1, high, targetFreq, visited, words);
        }
        else if (wordFreq < targetFreq) {
            // Search the right half
            binarySearch(positiveAndNegativeWords, mid + 1, high, targetFreq, visited, words);
        }
        else {
            // Search the left half
            binarySearch(positiveAndNegativeWords, low, mid - 1, targetFreq, visited, words);
        }
    }
}

// Binary search for max and min word 
void searchAlgo(Array<pair<string, int>>& positiveAndNegativeWords, Array<string>& minWords, Array<string>& maxWords) {
    int lowInd = 0;
    int highInd = positiveAndNegativeWords.getSize() - 1;
    int maxFreq = INT_MIN;
    int minFreq = INT_MAX;
    Array<bool> visited(positiveAndNegativeWords.getSize(), false);

    //get maxFreq and minFreq
    for (int i = 0; i < positiveAndNegativeWords.getSize(); i++) {
        if (positiveAndNegativeWords.get(i).second > 0) {
            int currentFreq = positiveAndNegativeWords.get(i).second;
            if (currentFreq > maxFreq) {
                maxFreq = currentFreq;
            }
            if (currentFreq < minFreq) {
                minFreq = currentFreq;
            }
        }
    }

    // Store the leftmost and rightmost
    int maxResult[2] = { INT_MAX, INT_MIN };
    int minResult[2] = { INT_MAX, INT_MIN }; // {leftmost, rightmost}
        
    // start timing
    auto linearStart = high_resolution_clock::now(); 

    //Binary Search for Max Words
    //binarySearch(positiveAndNegativeWords, lowInd, highInd, maxFreq, visited, maxWords);

    //Linear Search for Max Words
    linearSearch(positiveAndNegativeWords, maxFreq, maxWords);

    //reset visited array ind for Binary search
    for (int i = 0; i < visited.getSize(); i++) {
        visited.update(i, false);
    }

    //Binary Search for Min Words
    //binarySearch(positiveAndNegativeWords, 0, highInd, minFreq, visited, minWords);

    //Linear Search for Min Words
    linearSearch(positiveAndNegativeWords, minFreq, minWords);

    //stop timing
    auto linearStop = high_resolution_clock::now(); 
    auto linearDuration = duration_cast<nanoseconds>(linearStop - linearStart);
    cout << "Search Execution time: " << linearDuration.count() << " nano seconds" << endl;
}

void displayMinMaxWord(Array<string>& minWords, Array<string>& maxWords) {
    cout << "Max Frequency Words: ";
    for (int i = 0; i < maxWords.getSize(); i++) {
        cout << maxWords.get(i) << " ";
    }
    cout << endl;

    cout << "Min Frequency Words: ";
    for (int i = 0; i < minWords.getSize(); i++) {
        cout << minWords.get(i) << " ";
    }
    cout << endl;
}

// Helper function to merge two subarrays, adapted from Krahets (n.d.-b)
void merge(Array<pair<string, int>>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //Create temporary left and right array
    Array<pair<string, int>> Left, Right;

    //Copy elements from main array to left and right temporary array
    for (int i = 0; i < n1; i++)
        Left.insert(arr.get(left + i));
    for (int j = 0; j < n2; j++)
        Right.insert(arr.get(mid + 1 + j));

    //Loop both left and right array at the same time
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (Left.get(i).second <= Right.get(j).second) {
            //If If the current element in Left is less than or equal to the current element in Right,
            //the element from Left is copied to the original array arr at the current merging index k.
            arr.update(k, Left.get(i));
            i++;
        }
        else {
            //Otherwise, the element from Right is copied to arr at index k.
            arr.update(k, Right.get(j));
            j++;
        }
        k++;
    }
    //Copy remaining elements:

    //After the main merging loop, if there are any remaining elements in either Left or Right, 
    //they are copied to arr at the appropriate indices.
    while (i < n1) {
        arr.update(k, Left.get(i));
        i++;
        k++;
    }

    while (j < n2) {
        arr.update(k, Right.get(j));
        j++;
        k++;
    }
}

// Merge sort function, adapted from Krahets (n.d.-b)
void mergeSort(Array<pair<string, int>>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Utility function to swap two elements
void swap(pair<string, int>& a, pair<string, int>& b) {
    pair<string, int> temp = a;
    a = b;
    b = temp;
}

// Partition function, adapted from Krahets (n.d.-a)
int partition(Array<pair<string, int>>& arr, int low, int high) {
    pair<string, int> pivot = arr.get(high); // Choose the last element as pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j < high; j++) {
        if (arr.get(j).second < pivot.second) { // Compare based on frequency
            i++; // Increment index of smaller element
            swap(arr.get(i), arr.get(j)); // Swap
        }
    }
    swap(arr.get(i + 1), arr.get(high)); // Move pivot to correct position
    return (i + 1);
}

// Tail Recursive QuickSort, adapted from Krahets (n.d.-a)
void quickSortTailRecursive(Array<pair<string, int>>& arr, int low, int high) {
    while (low < high) {
        int pi = partition(arr, low, high); // Partitioning index

        // Recursively sort the left partition
        // Instead of making recursive call for the right side,
        // use a loop for it to reduce stack depth
        if (pi - low < high - pi) {
            quickSortTailRecursive(arr, low, pi - 1); // Sort left
            low = pi + 1; // Prepare to sort right
        }
        else {
            quickSortTailRecursive(arr, pi + 1, high); // Sort right
            high = pi - 1; // Prepare to sort left
        }
    }
}

void displayFrequencies(int totalReviews, int totalPositiveWords, int totalNegativeWords) {
    cout << "Total Reviews = " << totalReviews << endl;
    cout << "Total Counts of Positive Words = " << totalPositiveWords << endl;
    cout << "Total Counts of Negative Words = " << totalNegativeWords << endl;
}

void displaySortedFrequencies(Array<pair<string, int>>& positiveAndNegativeWords) {
    cout << "Frequency of each word used in overall reviews, listed in ascending order based on frequency (words which has frequency greater than 0 is shown only): " << endl;

    // Iterate through the positiveAndNegativeWords array
    for (int i = 0; i < positiveAndNegativeWords.getSize(); i++) {
        // Check if the frequency is greater than 0
        if (positiveAndNegativeWords.get(i).second > 0) {
            // Only display words with a frequency greater than 0
            cout << positiveAndNegativeWords.get(i).first << " = "
                << positiveAndNegativeWords.get(i).second << " times" << endl;
        }
    }
}

int main()
{
    Array<string> positiveWords, negativeWords;
    Array<pair<string, int>> hotelReviews;
    Array<string> minWords, maxWords;
    readWordsFromFile("positive-words.txt", positiveWords);
    readWordsFromFile("negative-words.txt", negativeWords);
    //NOTE: You can adjust the number of reviews to be read in the readReviewsFromCSV function at the while loop line
    //It was set to 300 by default
    readReviewsFromCSV("tripadvisor_hotel_reviews.csv", hotelReviews);

    int totalPositiveWords = 0;  // Initialize variables to store totals
    int totalNegativeWords = 0;

    summarizeSentiment(hotelReviews, positiveWords, negativeWords, totalPositiveWords, totalNegativeWords);
    displayFrequencies(hotelReviews.getSize(), totalPositiveWords, totalNegativeWords);
    
    Array<pair<string, int>> positiveAndNegativeWords;
    concatenateArrays(positiveWords, negativeWords, positiveAndNegativeWords);
    countWordFrequency(hotelReviews, positiveAndNegativeWords);

    
    auto startSort = high_resolution_clock::now(); //start the timer

    //Choose sorting algorithm by comment/uncomment the line below that has the merge/quick sort function
    //mergeSort(positiveAndNegativeWords, 0, positiveAndNegativeWords.getSize() - 1);
    quickSortTailRecursive(positiveAndNegativeWords, 0, positiveAndNegativeWords.getSize() - 1);

    auto stopSort = high_resolution_clock::now(); //stop the timer

    displaySortedFrequencies(positiveAndNegativeWords);
    //calculate the time used
	auto duration = duration_cast<microseconds>(stopSort-startSort);
	cout << "Time execution for sorting: " << duration.count() << " microseconds. " << endl;
    //linearSearch(positiveAndNegativeWords, maxMinWords);
    searchAlgo(positiveAndNegativeWords, minWords, maxWords);
    displayMinMaxWord(minWords, maxWords);
    return 0;
}