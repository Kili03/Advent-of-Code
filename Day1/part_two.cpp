#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
#include <unordered_map>

using namespace std;

void code() {
    ifstream DataFile("Advent-of-Code/Day1/data.txt");

    int left[1000] = {};
    unordered_map<int, int> counter;

    string d1, d2;

    int similarity = 0;
    int i = 0;

    while (DataFile >> d1 >> d2) {
        left[i] = stoi(d1);
        counter[stoi(d2)]++;

        i++;
    }

    for (int e: left) {
        similarity += e * counter[e];
    }
    cout << similarity << endl;
    DataFile.close();
}

int main() {
    const auto begin = chrono::high_resolution_clock::now();
    code();
    const auto end = chrono::high_resolution_clock::now();
    const chrono::duration<double> duration = end-begin;
    cout << "Time: " << duration.count() << endl;
    // this_thread::sleep_for(chrono::seconds(20));
    return 0;
}


