#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <timer.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


int ggT(int a , int b) {
    if (b == 0) {
        return a;
    }
    return ggT(b, a % b);
}


struct Point {
    int x;
    int y;

    bool is_in_bounds(const int size) const {
        return x >= 0 && x < size && y >= 0 && y < size;
    }

    Point shorten() const {
        return {x/ggT(x, y), y/ggT(x, y)};
    }

    Point operator+(const Point& other) const {
        return {x+other.x, y+other.y};
    }
    Point operator-(const Point& other) const {
        return {x-other.x, y-other.y};
    }
    Point operator*(const int m) const {
        return {x*m, y*m};
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
                Point diff = (vec[i] - vec[j]).shorten();

                int m=0;
                while ((vec[i] + diff * m).is_in_bounds(50)) {
                    hai_set.insert(vec[i] + diff * m);
                    m++;
                }
                m=-1;
                while ((vec[j] + diff * m).is_in_bounds(50)) {
                    hai_set.insert(vec[j] + diff * m);
                    m--;
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