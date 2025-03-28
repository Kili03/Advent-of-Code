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

vector<vector<char>> get_grid(const string& filename) {
    ifstream FileData(filename);
    if (!FileData.is_open()) {
        throw invalid_argument("Could not open file correctly");
    }

    vector<vector<char>> grid;
    grid.reserve(140);
    string file_line;
    while (getline(FileData, file_line)) {
        grid.emplace_back(file_line.begin(), file_line.end());
    }
    return grid;
}


bool found_x_mas(const vector<vector<char>>& grid, const int x, const int y) {
    if (x == 0 || y == 0 || x == SIZE-1 || y == SIZE-1) {
        return false;
    }
    char tl = grid[x-1][y-1];
    char tr = grid[x-1][y+1];
    char bl = grid[x+1][y-1];
    char br = grid[x+1][y+1];

    if (!(tl == 'M' && br == 'S' || tl == 'S' && br == 'M')) {
        return false;
    }
    if (!(bl == 'M' && tr == 'S' || bl == 'S' && tr == 'M')) {
        return false;
    }
    return true;
}


int code() {
    const vector<vector<char>> grid = get_grid("Advent-of-Code/Day4/data.txt");

    int count = 0;

    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            if (grid[i][j] == 'A') {
                count += found_x_mas(grid, i, j);
            }
        }
    }

    return count;

}

int main() {
    Timer timer;

    for (int i=0; i < 1; i++) {
        const int result = code();
        cout << result << endl;
    }

    return 0;
}
