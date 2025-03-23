#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
using namespace std;

void code() {
    ifstream DataFile("Advent-of-Code/Day1/data.txt");

    int left[1000] = {};
    int right[1000] = {};

    string d1, d2;

    int diff = 0;
    int i = 0;

    while (DataFile >> d1 >> d2) {
        left[i] = stoi(d1);
        right[i] = stoi(d2);

        i++;
    }

    sort(begin(left), end(left));
    sort(begin(right), end(right));

    for (int j=0; j<1000; j++) {
        diff += abs(left[j] - right[j]);
    }
    cout << diff << endl;
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


