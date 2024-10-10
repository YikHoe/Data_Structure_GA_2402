//References
//Krahets. (n.d.-a). 11.5 Quick sort - Hello Algo. Hello Algo. 
//      https://www.hello-algo.com/en/chapter_sorting/quick_sort/

//Krahets. (n.d.-b). 11.6 Merge sort - Hello Algo. Hello Algo. 
//      https://www.hello-algo.com/en/chapter_sorting/merge_sort/

//AHIRLABS. (n.d.).Recursive Binary Search in Cpp Programming – AHIRLABS.
//      https://www.ahirlabs.com/programing/cpp-programming/recursive-binary-search/ 

// BEKOAIL, P. F. (2019, November 13). Binary search a left/right most element when there are duplicates. Stack Overflow. 
//      https://stackoverflow.com/a/58838379

// Jump Search Algorithm | Studytonight. (n.d.).
//      https://www.studytonight.com/data-structures/jump-search-algorithm

#include <iostream>
#include "Array.hpp"
#include "customArrayMap.hpp"
#include <string>
#include <fstream>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

// Tokenize and seperate the word
void tokenize(string review, Array<string>& list) {
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
            // If we reach a non-alphanumeric character and have a valid word, insert it
            if (!word.empty()) {
                list.insert(word);
                word = ""; // Clear the word after inserting
            }
        }
    }
    // Insert the last word if there's one remaining
    if (!word.empty()) {
        list.insert(word);
    }
}

// Read words from a file and store them in array
void readWordsFromFile(const string& filename, Array<string>& stringArray) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string word;
    while (file >> word) {
        //Store the word into array
        stringArray.insert(word);
    }
    file.close();
}

// Read reviews from a CSV file
void readReviewsFromCSV(const string& filename, customArrayMap<string, int>& hotelReview) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening CSV file: " << filename << endl;
        return;
    }

    string line;
    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        string review;
        int rating;

        int commaPos = line.rfind(',');
        if (commaPos != string::npos) {
            review = line.substr(0, commaPos);
            rating = stoi(line.substr(commaPos + 1));
            hotelReview.insert(review, rating);
        }
    }
}

//Adapted from (Jump Search Algorithm | Studytonight, n.d.)
void jumpSearchForWords(Array<string>& words, string& word, int& wordCount, Array<string>& foundWords, 
    bool& isPositive, customArrayMap<string, int>& wordFreq) {
    int n = words.getSize();  // Get size of the array
    int step = sqrt(n);       // Block size for jumping (√n)
    int prev = 0;

    // Jump in blocks until we find a block that may contain the word
    while (words.get(min(step, n) - 1) < word) {
        prev = step;          // Update the previous block starting point
        step += sqrt(n);      // Move to the next block
        if (prev >= n)        // If we've gone past the array's bounds, exit
            return;
    }

    // Perform linear search within the block starting from 'prev'
    for (int i = prev; i < min(step, n); ++i) {
        if (words.get(i) == word) {
            // Add the word count and insert the word into foundWords array
            wordCount++;
            foundWords.insert(word);

            if (wordFreq.containsKey(word)) {
                // Add freq in wordFreq array
                wordFreq.addFreqByKey(word);
            }
            else {
                wordFreq.insert(word, 1);
            }

            // Set positive status to true to avoid repeat searching
            isPositive = true;
            break;  // We can stop after finding the word
        }
    }
}

//binary search to count word
void binarySearchForWords(Array<string>& words, string& word, int& wordCount, Array<string>& foundWords, bool& isPositive, customArrayMap<string, int>& wordFreq) {
    // Set the low Index, high Index
    int low = 0;
    int high = words.getSize() - 1;
    while (low <= high) {
        // Calculate the middle index
        int mid = (low + high) / 2;
        string midWord = words.get(mid);

        // If the middle word is the correct word
        if (midWord == word) {
            //Add the word count and insert the word into foundWords array
            wordCount++;
            foundWords.insert(word);
			if (wordFreq.containsKey(word)) {
				//add freq in wordFreq array        
				wordFreq.addFreqByKey(word);
			}
			else {
				wordFreq.insert(word, 1);
			}
            // Set positive status to true to avoid repeat searching
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

// Count the positive and negative word for each review
void countPositiveNegativeWords(const string& review, Array<string>& positiveWords, Array<string>& negativeWords,
    int& positiveCount, int& negativeCount, Array<string>& foundPositiveWords, Array<string>& foundNegativeWords, int& i, 
    customArrayMap<string, int>& wordFreq, milliseconds& totalSearchDuration, bool& jSearch) {

    // Reset the positive and negative word count for each review
    positiveCount = 0;
    negativeCount = 0;

    // Split review into words
    Array<string> splitWord;
    tokenize(review, splitWord); // Assuming 'tokenize' splits the review into words and stores them in splitWord

    // Start Timing
    auto countWordStart = high_resolution_clock::now();

    // Iterate through the splitWord array
    for (int j = 0; j < splitWord.getSize(); j++) {
        string word = splitWord.get(j); // Get the word at index j

        bool isPositive = false;

        if (jSearch) {
            jumpSearchForWords(positiveWords, word, positiveCount, foundPositiveWords, isPositive, wordFreq);
        }
        else {
            binarySearchForWords(positiveWords, word, positiveCount, foundPositiveWords, isPositive, wordFreq);
        }

        // Run only if the word is not found in positive
        if (!isPositive) {
            if (jSearch) {
                jumpSearchForWords(negativeWords, word, negativeCount, foundNegativeWords, isPositive, wordFreq);
            }
            else {
                binarySearchForWords(negativeWords, word, negativeCount, foundNegativeWords, isPositive, wordFreq);
            }
        }
    }

    // Stop Timing
    auto countWordStop = high_resolution_clock::now();
    auto countWordDuration = duration_cast<milliseconds>(countWordStop - countWordStart);
    cout << "Count Word Execution time for Review " << i + 1 << ": " << countWordDuration.count() << " milliseconds" << endl;
    totalSearchDuration += countWordDuration;
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
void summarizeSentiment(customArrayMap<string, int>& hotelReviews, Array<string>& positiveWords, Array<string>& negativeWords,
    int& totalPositiveWords, int& totalNegativeWords, Array<int>& reviewRate, float& matchEvaluation, float& unmatchEvaluation, customArrayMap<string, int>& wordFreq,
    milliseconds& totalSearchDuration, bool& jSearch)
{
    for (int i = 0; i < hotelReviews.getSize(); i++) {
        string review = hotelReviews.getByIndex(i).getKey();
        int rating = hotelReviews.getByIndex(i).getValue();

        Array<string> foundPositiveWords;
        Array<string> foundNegativeWords;
        int positiveCount = 0, negativeCount = 0;
        countPositiveNegativeWords(review, positiveWords, negativeWords, positiveCount, negativeCount, foundPositiveWords, foundNegativeWords, i, wordFreq, totalSearchDuration, jSearch);
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
        //calculate positive, negative and neutral review
        switch (roundScore) {
            case 1:
            case 2:  // When the round score is 1-2
                reviewRate.get(2)++;
                break;  // Break ensures the next case doesn't execute

            case 3:
                reviewRate.get(1)++;
                break;

            case 4:
            case 5:  // When the round score is 4-5
                reviewRate.get(0)++;
                break;

            default:
                // Handle unexpected values of roundScore
                break;
        }

        // display sentiment score
        cout << "Sentiment score (1-5) \t= " << sentimentScore << ", thus the rating should be equal to " << roundScore << endl;
        // display user rating
        cout << "User Ratings \t\t= " << rating << endl;
        // evaluate the accuracy 
        if (abs(roundScore - rating) < 1.0) {
            matchEvaluation++;
            cout << "Analysis output: User's subjective evaluation matches the sentiment score provided by the analysis." << endl;
            cout << "There is a consistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment." << endl;
        }
        else {
            unmatchEvaluation++;
            cout << "Analysis output: User's subjective evaluation does not match the sentiment score provided by the analysis." << endl;
            cout << "There is an inconsistency between the sentiment score generated by the analysis and the user's evaluation of the sentiment." << endl;
        }
        cout << endl;
    }
}

//Jump search for word frequency, adapted from (Jump Search Algorithm | Studytonight, n.d.)
void jumpSearch(customArrayMap<string, int>& wordFrequency, int& targetFreq, Array<string>& words) {
    int n = wordFrequency.getSize();  // Get size of the map
    int step = sqrt(n);               // Block size for jumping (√n)
    int prev = 0;

    // Jump in blocks until we find the block where targetFreq could be
    while (wordFrequency.getByIndex(min(step, n) - 1).getValue() < targetFreq) {
        prev = step;          // Update the previous block starting point
        step += sqrt(n);      // Move to the next block
        if (prev >= n)        // If we've gone past the array's bounds, exit
            return;
    }

    // Perform linear search within the block starting from 'prev'
    //for (int i = prev; i < min(step, n); ++i) {
    for (int i = prev; i < n; ++i) {
        int wordFreq = wordFrequency.getByIndex(i).getValue();
        if (wordFreq == targetFreq) {
            words.insert(wordFrequency.getByIndex(i).getKey());
        }
        else if (wordFreq >= targetFreq) {
            break;
        }
    }
}

//Recursive Binary Searching, adapt from (Recursive Binary Search in Cpp Programming – AHIRLABS, n.d.)
//Mark visited array index to avoid repeating, adapted from (Binary Search a Left/Right Most Element When There Are Duplicates, n.d.)
void binarySearch(customArrayMap<string, int>& wordFrequency, int low, int high, int targetFreq, Array<bool>& visited, Array<string>& words) {
    if (low <= high) {
        int mid = (low + high) / 2;
        int wordFreq = wordFrequency.getByIndex(mid).getValue();

        //make sure the wordFreq is not visited
        if (wordFreq == targetFreq && !visited.get(mid)){
            // insert founded word into list
            words.insert(wordFrequency.getByIndex(mid).getKey());
            //Mark the index as visited
            visited.update(mid, true);

            //Continue search in diff direction 
            binarySearch(wordFrequency, low, mid - 1, targetFreq, visited, words);
            binarySearch(wordFrequency, mid + 1, high, targetFreq, visited, words);
        }
        else if (wordFreq < targetFreq) {
            // Search the right half
            binarySearch(wordFrequency, mid + 1, high, targetFreq, visited, words);
        }
        else {
            // Search the left half
            binarySearch(wordFrequency, low, mid - 1, targetFreq, visited, words);
        }
    }
}

// Search Algorithm for Maximum and Minimum word
void searchAlgo(customArrayMap<string, int>& wordFrequency, Array<string>& minWords, Array<string>& maxWords, bool& jSearch) {
    int lowInd = 0;
    int highInd = wordFrequency.getSize() - 1;
    int maxFreq = INT_MIN;
    int minFreq = INT_MAX;
    string searchUsed;
    Array<bool> visited(wordFrequency.getSize(), false);

    //get maxFreq and minFreq
    for (int i = 0; i < wordFrequency.getSize(); i++) {
        if (wordFrequency.getByIndex(i).getValue() > 0) {
            int currentFreq = wordFrequency.getByIndex(i).getValue();
            if (currentFreq > maxFreq) {
                maxFreq = currentFreq;
            }
            if (currentFreq < minFreq) {
                minFreq = currentFreq;
            }
        }
    }
        
    //Start timing
    auto searchStart = high_resolution_clock::now(); 
    //Jump Search for Max Words
    if (jSearch) {
        jumpSearch(wordFrequency, maxFreq, maxWords);

        //Jump Search for Min Words
        jumpSearch(wordFrequency, minFreq, minWords);
        searchUsed = "Jump Search";
    }
    else {
        //Binary Search for Max Words
        binarySearch(wordFrequency, lowInd, highInd, maxFreq, visited, maxWords);

        //reset visited array ind for Binary search
        for (int i = 0; i < visited.getSize(); i++) {
            visited.update(i, false);
        }

        //Binary Search for Min Words
        binarySearch(wordFrequency, 0, highInd, minFreq, visited, minWords);
        searchUsed = "Binary Search";
    }
    //Stop timing
    auto searchStop = high_resolution_clock::now(); 

    //Calculate Search Time
    auto searchDuration = duration_cast<microseconds>(searchStop - searchStart);
    cout << searchUsed << " Execution time for Maximum and Minimum Word : " << searchDuration.count() << " microseconds" << endl;
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
void merge(customArrayMap<string, int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary maps for the left and right parts
    customArrayMap<string, int> Left, Right;

    // Copy data to temporary maps Left[] and Right[]
    for (int i = 0; i < n1; i++) {
        auto kv = arr.getByIndex(left + i);  // Extract key-value pair from the main array
        Left.insert(kv.key, kv.value);  // Insert into Left map
    }
    for (int j = 0; j < n2; j++) {
        auto kv = arr.getByIndex(mid + 1 + j);  // Extract key-value pair for Right
        Right.insert(kv.key, kv.value);  // Insert into Right map
    }

    // Initial indexes of first and second subarrays
    int i = 0, j = 0;
    int k = left;  // Initial index of merged subarray

    // Merge the temp maps back into arr
    while (i < n1 && j < n2) {
        // Compare the values and merge the smaller one into arr
        if (Left.getByIndex(i).value <= Right.getByIndex(j).value) {
            // Update the original array with Left's key-value pair if its value is smaller
            arr.updateByIndex(k, Left.getByIndex(i).key, Left.getByIndex(i).value);
            i++;
        }
        else {
            // Update the original array with Right's key-value pair
            arr.updateByIndex(k, Right.getByIndex(j).key, Right.getByIndex(j).value);
            j++;
        }
        k++;
    }

    // Copy the remaining elements of Left[], if any
    while (i < n1) {
        arr.updateByIndex(k, Left.getByIndex(i).key, Left.getByIndex(i).value);
        i++;
        k++;
    }

    // Copy the remaining elements of Right[], if any
    while (j < n2) {
        arr.updateByIndex(k, Right.getByIndex(j).key, Right.getByIndex(j).value);
        j++;
        k++;
    }
}

// Merge sort function, adapted from Krahets (n.d.-b)
void mergeSort(customArrayMap<string, int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Utility function to swap two elements
void swap(customArrayMap<string, int>& a, customArrayMap<string, int>& b) {
    customArrayMap<string, int> temp = a;
    a = b;
    b = temp;
}

// Partition function, adapted from Krahets (n.d.-a)
int partition(customArrayMap<string, int>& arr, int low, int high) {
	auto pivot = arr.getByIndex(high); // Choose the last element as pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j < high; j++) {
		if (arr.getByIndex(j).getValue() < pivot.getValue()) { // Compare based on frequency
            i++; // Increment index of smaller element
            swap(arr.getByIndex(i), arr.getByIndex(j)); // Swap
        }
    }
    swap(arr.getByIndex(i + 1), arr.getByIndex(high)); // Move pivot to correct position
    return (i + 1);
}

// Tail Recursive QuickSort, adapted from Krahets (n.d.-a)
void quickSortTailRecursive(customArrayMap<string, int>& arr, int low, int high) {
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

void displaySortedFrequencies(customArrayMap<string, int>& wordFrequency) {
    cout << "Frequency of each word used in overall reviews, listed in ascending order based on frequency (words which has frequency greater than 0 is shown only): " << endl;

    // Iterate through the positiveAndNegativeWords array
    for (int i = 0; i < wordFrequency.getSize(); i++) {
        // Check if the frequency is greater than 0
        if (wordFrequency.getByIndex(i).getValue() > 0) {
            // Only display words with a frequency greater than 0
            cout << wordFrequency.getByIndex(i).getKey() << " = "
                << wordFrequency.getByIndex(i).getValue() << " times" << endl;
        }
    }
}

void displaySummary(Array<int>& reviewRate, float& matchEvaluation, float& unmatchEvaluation) {
    int positiveReview = reviewRate.get(0);
    int neutralReview = reviewRate.get(1);
    int negativeReview = reviewRate.get(2);
    float evaluationAccuracy = (matchEvaluation / (matchEvaluation + unmatchEvaluation)) * 100;
    cout << "----------------------------Final Summary--------------------------------" << endl;
    cout << "Total Positive Review \t: " << positiveReview << endl;
    cout << "Total Neutral Review \t: " << neutralReview << endl;
    cout << "Total Negative Review \t: " << negativeReview << endl;
    cout << "Total Matching Review \t: " << matchEvaluation << endl;
    cout << "Total Unmatch Review \t: " << unmatchEvaluation << endl;
    cout << "Overall Evaluation Accuracy \t: " << evaluationAccuracy << "%" << endl;
}

// Function to display the menu
void displayMenu() {
    cout << "Please choose an option to analyze the hotel review using array with different sorting and searching algorithm: " << endl;
    cout << "1. Merge Sort + Binary Search" << endl;
    cout << "2. Merge Sort + Jump Search" << endl;
    cout << "3. Quick Sort + Binary Search" << endl;
    cout << "4. Quick Sort + Jump Search" << endl;
    cout << "5. Exit" << endl;
    cout << "Your choice: ";
}

// Function declarations for options 1-4
void mergeSortAndBinarySearch() {
    Array<int> reviewRate(3, 0);
    Array<string> positiveWords, negativeWords;
    customArrayMap<string, int> hotelReviews;
    customArrayMap<string, int> wordFrequency;
    Array<string> minWords, maxWords;
    bool jSearch = false;
    // Initialize totalSearchDuration as 0 microseconds
    milliseconds totalSearchDuration = milliseconds(0);
    auto startProgram = high_resolution_clock::now(); //start the timer
    readWordsFromFile("positive-words.txt", positiveWords);
    readWordsFromFile("negative-words.txt", negativeWords);
    readReviewsFromCSV("tripadvisor_hotel_reviews.csv", hotelReviews);

    float matchEvaluation = 0;
    float unmatchEvaluation = 0;
    int totalPositiveWords = 0;  // Initialize variables to store totals
    int totalNegativeWords = 0;
    summarizeSentiment(hotelReviews, positiveWords, negativeWords, totalPositiveWords, totalNegativeWords, reviewRate,
        matchEvaluation, unmatchEvaluation, wordFrequency, totalSearchDuration, jSearch);
    displayFrequencies(hotelReviews.getSize(), totalPositiveWords, totalNegativeWords);

    auto startSort = high_resolution_clock::now(); //start the timer

    mergeSort(wordFrequency, 0, wordFrequency.getSize() - 1);

    auto stopSort = high_resolution_clock::now(); //stop the timer

    displaySortedFrequencies(wordFrequency);
    //calculate the time used
    auto duration = duration_cast<microseconds>(stopSort - startSort);
    cout << "Time execution for sorting using merge sort: " << duration.count() << " microseconds. " << endl;
    searchAlgo(wordFrequency, minWords, maxWords, jSearch);
    displayMinMaxWord(minWords, maxWords);
    displaySummary(reviewRate, matchEvaluation, unmatchEvaluation);
    auto stopProgram = high_resolution_clock::now();
    auto programDuration = duration_cast<seconds>(stopProgram - startProgram);
    if (jSearch){ 
        cout << "Total Search time using Jump Search:" << totalSearchDuration.count() << "milli seconds" << endl; 
    }
    else{ 
        cout << "Total Search time using Binary Search:" << totalSearchDuration.count() << "milli seconds" << endl; 
    }
    
    cout << "Program Execution time:" << programDuration.count() << "seconds" << endl;
}

void mergeSortAndJumpSearch() {
    Array<int> reviewRate(3, 0);
    Array<string> positiveWords, negativeWords;
    customArrayMap<string, int> hotelReviews;
    customArrayMap<string, int> wordFrequency;
    Array<string> minWords, maxWords;
    bool jSearch = true;
    // Initialize totalSearchDuration as 0 microseconds
    milliseconds totalSearchDuration = milliseconds(0);
    auto startProgram = high_resolution_clock::now(); //start the timer
    readWordsFromFile("positive-words.txt", positiveWords);
    readWordsFromFile("negative-words.txt", negativeWords);
    readReviewsFromCSV("tripadvisor_hotel_reviews.csv", hotelReviews);

    float matchEvaluation = 0;
    float unmatchEvaluation = 0;
    int totalPositiveWords = 0;  // Initialize variables to store totals
    int totalNegativeWords = 0;
    summarizeSentiment(hotelReviews, positiveWords, negativeWords, totalPositiveWords, totalNegativeWords, reviewRate,
        matchEvaluation, unmatchEvaluation, wordFrequency, totalSearchDuration, jSearch);
    displayFrequencies(hotelReviews.getSize(), totalPositiveWords, totalNegativeWords);

    auto startSort = high_resolution_clock::now(); //start the timer

    mergeSort(wordFrequency, 0, wordFrequency.getSize() - 1);

    auto stopSort = high_resolution_clock::now(); //stop the timer

    displaySortedFrequencies(wordFrequency);
    //calculate the time used
    auto duration = duration_cast<microseconds>(stopSort - startSort);
    cout << "Time execution for sorting using merge sort: " << duration.count() << " microseconds. " << endl;
    searchAlgo(wordFrequency, minWords, maxWords, jSearch);
    displayMinMaxWord(minWords, maxWords);
    displaySummary(reviewRate, matchEvaluation, unmatchEvaluation);
    auto stopProgram = high_resolution_clock::now();
    auto programDuration = duration_cast<seconds>(stopProgram - startProgram);
    if (jSearch) {
        cout << "Total Search time using Jump Search:" << totalSearchDuration.count() << "milli seconds" << endl;
    }
    else {
        cout << "Total Search time using Binary Search:" << totalSearchDuration.count() << "milli seconds" << endl;
    }
    cout << "Program Execution time:" << programDuration.count() << "seconds" << endl;
}

void quickSortAndBinarySearch() {
    Array<int> reviewRate(3, 0);
    Array<string> positiveWords, negativeWords;
    customArrayMap<string, int> hotelReviews;
    customArrayMap<string, int> wordFrequency;
    Array<string> minWords, maxWords;
    bool jSearch = false;
    // Initialize totalSearchDuration as 0 microseconds
    milliseconds totalSearchDuration = milliseconds(0);
    auto startProgram = high_resolution_clock::now(); //start the timer
    readWordsFromFile("positive-words.txt", positiveWords);
    readWordsFromFile("negative-words.txt", negativeWords);
    readReviewsFromCSV("tripadvisor_hotel_reviews.csv", hotelReviews);

    float matchEvaluation = 0;
    float unmatchEvaluation = 0;
    int totalPositiveWords = 0;  // Initialize variables to store totals
    int totalNegativeWords = 0;
    summarizeSentiment(hotelReviews, positiveWords, negativeWords, totalPositiveWords, totalNegativeWords, reviewRate,
        matchEvaluation, unmatchEvaluation, wordFrequency, totalSearchDuration, jSearch);
    displayFrequencies(hotelReviews.getSize(), totalPositiveWords, totalNegativeWords);

    auto startSort = high_resolution_clock::now(); //start the timer

    quickSortTailRecursive(wordFrequency, 0, wordFrequency.getSize() - 1);

    auto stopSort = high_resolution_clock::now(); //stop the timer

    displaySortedFrequencies(wordFrequency);
    //calculate the time used
    auto duration = duration_cast<microseconds>(stopSort - startSort);
    cout << "Time execution for sorting using quick sort: " << duration.count() << " microseconds. " << endl;
    searchAlgo(wordFrequency, minWords, maxWords, jSearch);
    displayMinMaxWord(minWords, maxWords);
    displaySummary(reviewRate, matchEvaluation, unmatchEvaluation);
    auto stopProgram = high_resolution_clock::now();
    auto programDuration = duration_cast<seconds>(stopProgram - startProgram);
    if (jSearch) {
        cout << "Total Search time using Jump Search:" << totalSearchDuration.count() << "milli seconds" << endl;
    }
    else {
        cout << "Total Search time using Binary Search:" << totalSearchDuration.count() << "milli seconds" << endl;
    }
    cout << "Program Execution time:" << programDuration.count() << "seconds" << endl;
}

void quickSortAndJumpSearch() {
    Array<int> reviewRate(3, 0);
    Array<string> positiveWords, negativeWords;
    customArrayMap<string, int> hotelReviews;
    customArrayMap<string, int> wordFrequency;
    Array<string> minWords, maxWords;
    bool jSearch = true;
    // Initialize totalSearchDuration as 0 microseconds
    milliseconds totalSearchDuration = milliseconds(0);
    auto startProgram = high_resolution_clock::now(); //start the timer
    readWordsFromFile("positive-words.txt", positiveWords);
    readWordsFromFile("negative-words.txt", negativeWords);
    readReviewsFromCSV("tripadvisor_hotel_reviews.csv", hotelReviews);

    float matchEvaluation = 0;
    float unmatchEvaluation = 0;
    int totalPositiveWords = 0;  // Initialize variables to store totals
    int totalNegativeWords = 0;
    summarizeSentiment(hotelReviews, positiveWords, negativeWords, totalPositiveWords, totalNegativeWords, reviewRate,
        matchEvaluation, unmatchEvaluation, wordFrequency, totalSearchDuration, jSearch);
    displayFrequencies(hotelReviews.getSize(), totalPositiveWords, totalNegativeWords);

    auto startSort = high_resolution_clock::now(); //start the timer

    quickSortTailRecursive(wordFrequency, 0, wordFrequency.getSize() - 1);

    auto stopSort = high_resolution_clock::now(); //stop the timer

    displaySortedFrequencies(wordFrequency);
    //calculate the time used
    auto duration = duration_cast<microseconds>(stopSort - startSort);
    cout << "Time execution for sorting using quick sort: " << duration.count() << " microseconds. " << endl;
    searchAlgo(wordFrequency, minWords, maxWords, jSearch);
    displayMinMaxWord(minWords, maxWords);
    displaySummary(reviewRate, matchEvaluation, unmatchEvaluation);
    auto stopProgram = high_resolution_clock::now();
    auto programDuration = duration_cast<seconds>(stopProgram - startProgram);
    if (jSearch) {
        cout << "Total Search time using Jump Search:" << totalSearchDuration.count() << "milli seconds" << endl;
    }
    else {
        cout << "Total Search time using Binary Search:" << totalSearchDuration.count() << "milli seconds" << endl;
    }
    cout << "Program Execution time:" << programDuration.count() << "seconds" << endl;
}

int main() 
{
    int choice;

    displayMenu();  // Show the menu
    cin >> choice;  // Get the user's choice

    // Validate input
    if (cin.fail()) {
        cin.clear();  // Clear input buffer to restore cin to a usable state
        cin.ignore(INT_MAX, '\n');  // Ignore last input
        cout << "Invalid input! Please enter a number between 1 and 5." << endl;
        return 1;  // Exit the program on invalid input
    }

    // Switch case to handle user's choice
    switch (choice) {
        case 1:
            mergeSortAndBinarySearch();
            break;
        case 2:
            mergeSortAndJumpSearch();
            break;
        case 3:
            quickSortAndBinarySearch();
            break;
        case 4:
            quickSortAndJumpSearch();
            break;
        case 5:
            cout << "Exiting program..." << endl;
            return 0;  // End the program
        default:
            cout << "Invalid choice! Please choose between 1 and 5." << endl;
            return 1;  // Exit the program on invalid choice
    }
    return 0;  // End the program after executing the selected option
}