#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    cout << "Hello World" << endl;

    ifstream file("data.txt");

    vector<vector<int>> lines;
    string line;
    while (getline(file, line)) {
        // cout << line << endl;
        stringstream lineStream(line);

        vector<int> numbers;
        int number;
        while (lineStream >> number) {
            numbers.push_back(number);
            // cout << number << " ";
        }
        lines.push_back(numbers);
        // cout << endl;

    }

    for (vector<int> int_line : lines) {
        for (int num : int_line) {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << "Hi";

    return 0;
}