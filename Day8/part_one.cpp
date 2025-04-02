#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <timer.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;

    bool is_in_bounds(const int size) const {
        return x >= 0 && x < size && y >= 0 && y < size;
    }

    Point operator+(const Point& other) const {
        return {x+other.x, y+other.y};
    }
    Point operator-(const Point& other) const {
        return {x-other.x, y-other.y};
    }
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        return hash<int>()(p.x) ^ hash<int>()(p.y);
    }
};

int calculate(const unordered_map<char, vector<Point>>& map, int size) {
    unordered_set<Point, PointHash> hai_set{};

    for (const vector<Point>& vec: views::values(map)) {
        for (int i=0; i<vec.size(); i++) {
            for (int j=i+1; j<vec.size(); j++) {
                Point diff = vec[i] - vec[j];
                Point pos_out1 = vec[i] + diff;
                Point pos_out2 = vec[j] - diff;

                if (pos_out1.is_in_bounds(size)) {
                    hai_set.insert(pos_out1);
                }
                if (pos_out2.is_in_bounds(size)) {
                    hai_set.insert(pos_out2);
                }
            }
        }
    }
    return static_cast<int>(hai_set.size());
}

int code() {
    ifstream DataFile("Advent-of-Code/Day8/data.txt");
    string line;

    unordered_map<char, vector<Point>> map;

    int i = 0;
    while (getline(DataFile, line)) {
        stringstream stringStream(line);
        int j = 0;
        char c;
        while (stringStream >> c) {
            if (c != '.') {
                map[c].emplace_back(j, i);
            }
            j++;
        }
        i++;
    }
    return calculate(map, i);
}

int main() {
    Timer timer;
    cout << code() << endl;

    return 0;
}