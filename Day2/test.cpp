#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

bool check(vector<int> line) {
    if (line.size() == 1) {
        return true;
    }
    int first = line.at(0);
    int second = line.at(1);
    bool increasing = first < second;

    // cout << "size: " << line.size() << " elements: ";
    for (int i = 0; i < line.size() - 1; i++) {
        cout << line[i+1] << " ";
        if (line[i] == line[i + 1]) {
            return false;
        }
        if ((line[i] < line[i + 1]) != increasing) {
            return false;
        }
        int diff = abs(line[i] - line[i + 1]);
        if (diff < 1 or diff > 3) {
            return false;
        }
    }
    cout << endl;
    return true;
}

int main()
{
    cout << "Hello World" << endl;

    ifstream file("data.txt");

    vector<vector<int>> lines;
    string line;
    int count = 0;
    int all = 0;

    while (getline(file, line)) {
        // cout << line << endl;
        stringstream lineStream(line);

        vector<int> numbers;
        int number;test.cpp
        while (lineStream >> number) {
            numbers.push_back(number);
            // cout << number << " ";
        }
        if (check(numbers)) {
            count++;
            cout << "valid" << endl;
        } else {
            cout << "invalid" << endl;
        }
        all++;
        lines.push_back(numbers);
        // cout << endl;

    }

    /*for (vector<int> int_line : lines) {
        for (int num : int_line) {
            cout << num << " ";
        }
        cout << endl;
    }*/
    cout << "Hi" << endl;
    cout << count << endl;
    cout << all << endl;

    /*int hallotest;
    cout << hallotest;*/

    return 0;
}