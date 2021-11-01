#include <iostream>
#include <string>
#include <fstream>
#include <vector>

const size_t numOfTabs = 12;

int main()
{
    std::string firstHash[numOfTabs];
    std::ifstream file;
    for (short i = 0; i < numOfTabs; ++i) {
        file.open("md5_rainbow_table_part_" + std::to_string(i + 1) + ".csv");
        if (!file.is_open()) {
            return -1;
        }
        std::getline(file, firstHash[i]);
        size_t first = firstHash[i].find('"'), second = firstHash[i].find('"', first + 1);
        firstHash[i] = firstHash[i].substr(first + 1, second - 1 - first);
        file.close();
    }
    while (true) {
        std::string hashValue;
        std::cin >> hashValue;
        short i = 0;
        for (; (i < numOfTabs) && (hashValue.compare(firstHash[i]) >= 0); ++i) {}
        --i;
        std::vector<std::string> hashes, values;
        file.open("md5_rainbow_table_part_" + std::to_string(i + 1) + ".csv");
        if (!file.is_open()) {
            return -1;
        }
        std::string readingString;
        while (std::getline(file, readingString)) {
            size_t first = readingString.find('"'),
                   second = readingString.find('"', first + 1),
                   third = readingString.find('"', second + 1),
                   fourth = readingString.find('"', third + 1);
            hashes.push_back(readingString.substr(first + 1, second - 1 - first));
            values.push_back(readingString.substr(third + 1, fourth - 1 - third));
        }
        size_t left = 0,
               right = hashes.size() - 1,
               mid = (left + right) / 2;
        while ((left != mid) && (right != mid)) {
            if (hashValue == hashes[mid]) {
                break;
            }
            else if (hashValue > hashes[mid]) {
                left = mid;
            }
            else {
                right = mid;
            }
            mid = (left + right) / 2;
        }
        if (hashValue == hashes[mid]) {
            std::cout << values[mid] << std::endl;
        }
        else {
            std::cout << "There is no such hash" << std::endl;
        }
        file.close();
    }
    return 0;
}
