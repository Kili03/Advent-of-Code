#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <vector>

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

vector<unsigned long long> blink(const unsigned long long stone) {

    if (stone == 0) {
        return {1};
    }
    if (const string stone_s = to_string(stone); stone_s.size() % 2 == 0) {
        return {stoull(stone_s.substr(0, stone_s.size() / 2)), stoull(stone_s.substr(stone_s.size() / 2))};
    }
    return {stone * 2024};
}

unsigned long long build(const unsigned long long stone, const int left, unordered_map<string,unsigned long long>& memo) {
    if (left == 0) {
        return 1;
    }

    const string hash_string = to_string(stone) + ":" + to_string(left);

    if (memo.contains(hash_string)) {
        return memo[hash_string];
    }
    unsigned long long end_length = 0;
    for (const unsigned long long new_stone : blink(stone)) {
        const unsigned long long size = build(new_stone, left - 1, memo);
        end_length += size;
    }
    memo[hash_string] = end_length;
    return end_length;
}

unsigned long long code() {
    ifstream DataFile("Advent-of-Code/Day11/data.txt");
    if (!DataFile.is_open()) {
        cerr << "Couldn't find file" << endl;
    }

    string line;
    getline(DataFile, line);

    // line = "125 17";

    unordered_map<string,unsigned long long> memo;
    // memo.reserve(606479);

    stringstream line_stream(line);

    unsigned long long full_length = 0;
    const int full_blinks = 200;

    unsigned long long stone;
    while (line_stream >> stone) {
        full_length += build(stone, full_blinks, memo);
    }
    cout << "Memo size: " << memo.size() << endl;
    return full_length;
}

int main() {
    Timer timer;
    cout << code() << endl;

    return 0;
}
