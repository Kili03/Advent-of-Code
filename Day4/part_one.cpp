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
    int o_i = 0;
    int occ = 0;
    while (o_i != string::npos) {
        o_i = s.find(o, o_i+4);
        occ++;
    }
    return occ - 1;
}

int count_xmas(const string &text) {
    return count_occ(text, "XMAS") + count_occ(text, "SAMX");
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

    int count = 0;
    // horizontal
    for (vector<char> char_line : grid) {
        string line = string(char_line.begin(), char_line.end());
        count += count_xmas(line);
    }

    cout << count << endl;





}

int main() {
    Timer timer;
    string text = "MMMMMMAMXMXSSMXAXAXAMASXMMMAXXXAMAMASXSXMASXAAXAAAAXMMMMXAMSXSAMASXMASAMXMMXSMMMSXMASXMAMMSSMXMAXAASMMSXSAXAXSSMAXAXMASXMXMAMMSMXMASMXSMMXMS";
    cout << count_xmas(text) << endl;
    code();

    return 0;
}
