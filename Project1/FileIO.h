#include <iostream>
#include <fstream>
#include <string>
#include <functional>


using namespace std;

struct File
{
	string fileName;
};

class FileHandler {
    public:

        void readReviewsFromCSV(const string& filename) {
            ifstream file(filename);
            if (!file.is_open()) {
                std::cout << "Error opening CSV file: " << filename << std::endl;
                return;
            }

            string line;

            // Skip the header line
            if (getline(file, line)) {
            
            }

            int reviewCount = 0;
            int maxReviews = 5;
            while (getline(file, line) && reviewCount < maxReviews) {
                sanitize(line);
                reviewCount++;
            }


            file.close();
        }

    private:
        void sanitize(string& line){
            size_t commaPos = line.rfind(',');
            if (commaPos != std::string::npos) {
                string reviewText = line.substr(0, commaPos);
                string rating = line.substr(commaPos + 1);
                cout << reviewText << endl;
                cout << rating << endl;
            }
        }

};