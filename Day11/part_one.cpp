#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

#include "timer.h"

using namespace std;


void print_queue(queue<unsigned long long> q) {
    const int size = static_cast<int>(q.size());
    for (int i = 0; i < size; i++) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

queue<unsigned long long> blink(queue<unsigned long long>& old_stones) {
    queue<unsigned long long> new_stones;

    while (!old_stones.empty()) {
        const unsigned long long stone = old_stones.front();
        if (stone == 0) {
            new_stones.emplace(1);
        } else if (const string stone_s = to_string(stone); stone_s.size() % 2 == 0) {
            new_stones.emplace(stoull(stone_s.substr(0, stone_s.size() / 2)));
            new_stones.emplace(stoull(stone_s.substr(stone_s.size() / 2)));
        } else {
            new_stones.emplace(stone * 2024);
        }
        old_stones.pop();
    }
    return new_stones;
}

int code() {
    ifstream DataFile("Advent-of-Code/Day11/data.txt");
    if (!DataFile.is_open()) {
        cerr << "Couldn't find file" << endl;
    }

    string line;
    getline(DataFile, line);

    // line = "125 17";

    queue<unsigned long long> stones;

    stringstream line_stream(line);

    int stone;
    while (line_stream >> stone) {
        stones.emplace(stone);
    }

    print_queue(stones);

    int full_blinks = 25;

    for (int i = 0; i < full_blinks; i++) {
        stones = blink(stones);
        // print_queue(stones);
        cout << i+1 << " " << stones.size() << endl;
    }
    return static_cast<int>(stones.size());
}

int main() {
    Timer timer;
    cout << code() << endl;

    return 0;
}
