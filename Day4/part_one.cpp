#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>

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

int count_occ(const string &s, const string &o) {
    int start_index = 0;
    int o_i = s.find(o);
    return 0;
}

void code() {
    ifstream FileData("Advent-of-Code/Day4/data.txt");
    if (!FileData.is_open()) {
        throw invalid_argument("Could not open file correctly");
    }

    vector<vector<char>> grid;
    string line;
    while (getline(FileData, line)) {
        vector<char> char_line;
        for (char c: line) {
            char_line.emplace_back(c);
        }
        grid.emplace_back(char_line);
    }




}

int main() {
    Timer timer;
    string s1 = "hai";
    string s2 = "r";
    cout << s1.find(s2, 0) << endl;
    code();

    return 0;
}
