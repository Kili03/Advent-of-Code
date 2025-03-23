#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;


struct Timer {
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> duration;

    Timer() {
        start = chrono::high_resolution_clock::now();
    }
    ~Timer() {
        end = chrono::high_resolution_clock::now();
        duration = end-start;
        cout << "Time: " << duration.count() << endl;
    }
};


bool check(const vector<int> &number_line) {
    bool is_increasing = number_line[0] < number_line[1];

    for (int i=0; i < number_line.size() - 1; i++) {
        const int front = number_line[i];
        const int back = number_line[i+1];
        const int dist = abs(front - back);
        if ((front < back) != is_increasing || dist < 1 || dist > 3) {
            return false;
        }
    }
    return true;

}

void code() {
    ifstream DataFile("Advent-of-Code/Day2/data.txt");
    if (DataFile.fail()) {
        throw invalid_argument("Could not successfully open file");
    }

    int safe_number = 0;
    string line;

    while (getline(DataFile, line)) {
        // cout << line << endl;
        stringstream line_stream(line);

        vector<int> number_line;
        int value;

        while (line_stream >> value) {
            // cout << value << endl;
            number_line.emplace_back(value);
        }

        safe_number += check(number_line);
    }

    cout << safe_number << endl;

}

int main() {
    Timer timer;
    code();

    return 0;
}
