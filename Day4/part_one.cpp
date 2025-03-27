#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>


using namespace std;

constexpr int SIZE = 140;

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
    grid.reserve(140);
    string file_line;
    vector<char> char_line;
    char_line.reserve(140);
    while (getline(FileData, file_line)) {
        for (char c: file_line) {
            char_line.emplace_back(c);
        }
        grid.emplace_back(char_line);
        char_line.clear();
    }

    int count = 0;
    // horizontal
    for (vector<char> char_line_it : grid) {
        string line = string(char_line_it.begin(), char_line_it.end());
        count += count_xmas(line);
    }

    //vertical
    for (int i=0; i<grid[0].size(); i++) {
        string line;
        for (int j=0; j<grid.size(); j++) {
            // cout << grid[j][i] << endl;
            line += grid[j][i];
        }
        cout << line << endl;
        count += count_xmas(line);
    }

    //top-to-right-diagonal
    for (int i=0; i<SIZE; i++) {
        string line, line2;
        for (int j=0; i+j<SIZE; j++) {
            line += grid[0+j][i+j];
            line2 += grid[i+j][0+j];
        }
        cout << line << endl;
        count += count_xmas(line);
        cout << line2 << endl;
        count += count_xmas(line2);
    }

    for (int i=SIZE-1; i>=0; i--) {
        string line, line2;
        for (int j=SIZE-1; j>=0; j--) {
            line += grid[j][j-1];
            line2 += grid[j-1][j];
        }
        cout << line << endl;
        count += count_xmas(line);
        cout << line2 << endl;
        count += count_xmas(line2);
    }





    cout << count << endl;

}

int main() {
    Timer timer;

    for (int i=0; i < 1; i++) {
        code();
    }

    return 0;
}
