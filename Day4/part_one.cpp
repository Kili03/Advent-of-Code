#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>


using namespace std;

constexpr int SIZE = 140;

struct Timer {
    chrono::time_point<chrono::system_clock> start, end;

    Timer() {
        start = chrono::high_resolution_clock::now();
    }
    ~Timer() {
        end = chrono::high_resolution_clock::now();
        const chrono::duration<double> duration = end-start;
        cout << "Time: " << duration.count() << endl;
    }
};

int count_occ(const string &s, const string &o) {
    size_t o_i = 0;
    int occ = 0;
    o_i = s.find(o, 0);
    while (o_i != string::npos) {
        occ++;
        o_i = s.find(o, o_i+1);
    }

    return occ;
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
    while (getline(FileData, file_line)) {
        grid.emplace_back(file_line.begin(), file_line.end());
    }

    int count = 0;

    // horizontal
    for (vector<char> char_line_it : grid) {
        auto line = string(char_line_it.begin(), char_line_it.end());
        count += count_xmas(line);
    }

    //vertical
    for (int i=0; i<SIZE; i++) {
        string line;
        for (int j=0; j<SIZE; j++) {
            line += grid[j][i];
        }
        count += count_xmas(line);
    }

    // diagonal
    for (int i=0; i<SIZE; i++) {
        string line, line2, line3, line4;
        for (int j=0; j<SIZE-i; j++) {
            line += grid[j][i+j];
            line2 += grid[i+j][j];

            line3 += grid[j][SIZE-1-j-i];
            line4 += grid[j+i][SIZE-1-j];
        }
        count += count_xmas(line);
        count += count_xmas(line3);
        if (i > 0) {
            count += count_xmas(line2);
            count += count_xmas(line4);
        }
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
