#include <iostream>
#include <fstream>
#include <sstream>

#include "timer.h"

bool check(const unsigned long long& product_sum, const unsigned long long& subtotal, const int& index, const vector<int> &numbers) {
    if (subtotal > product_sum) {
        return false;
    }
    if (index == numbers.size()) {
        return subtotal == product_sum;
    }

    const int now = numbers[index];
    const unsigned long long concatenated = stoull(to_string(subtotal) + to_string(now));

    return check(product_sum, subtotal + now, index + 1, numbers)
        || check(product_sum, subtotal * now, index + 1, numbers)
        || check(product_sum, concatenated, index + 1, numbers);
}

unsigned long long code() {
    fstream DataFile("Advent-of-Code/Day7/data.txt");

    if (!DataFile.is_open()) {
        throw invalid_argument("File not found");
    }

    unsigned long long sum = 0;

    string line;
    while (getline(DataFile, line)) {
        unsigned long long product_sum;
        char delimiter;
        stringstream stringStream(line);
        stringStream >> product_sum >> delimiter;


        vector<int> numbers;
        int number;
        while (stringStream >> number) {
            numbers.emplace_back(number);
        }

        sum += product_sum * check(product_sum, numbers[0], 1, numbers);
    }

    return sum;
}


int main() {
    Timer timer;
    cout << code() << endl;
    // code();

    return 0;
}

