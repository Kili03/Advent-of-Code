#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>
#include <sstream>


using namespace std;

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


int check_validity(const vector<int>& elements, const unordered_map<int, int>& indices, const unordered_map<int, vector<int>>& rules) {
    const int middle = elements[(int)elements.size()/2];
    for (int num: elements) {
        auto it = rules.find(num);
        vector<int> to_check = (it != rules.end()) ? it->second : vector<int>();
        for (int check: to_check) {
            if (indices.contains(check) && indices.at(num) >= indices.at(check)) {
                return 0;
            }
        }
    }
    return middle;
}


int code() {
    const int number_of_rules = 1176;

    ifstream FileData("Advent-of-Code/Day5/data.txt");
    if (!FileData.is_open()) {
        throw invalid_argument("Could not open file correctly");
    }

    unordered_map<int, vector<int>> rules;

    string file_line;
    int sum = 0;
    int i = 0;
    while (getline(FileData, file_line)) {
        stringstream searcher(file_line);
        if (i <= number_of_rules) {
            int number1, number2;
            char delimiter;
            searcher >> number1 >> delimiter >> number2;

            rules[number1].emplace_back(number2);
        } else {
            unordered_map<int, int> indices;
            vector<int> elements;
            int j = 0;
            string number_string;
            while (getline(searcher, number_string, ',')) {
                indices[stoi(number_string)] = j;
                elements.emplace_back(stoi(number_string));
                //cout << stoi(number_string) << endl;
                j++;
            }
            //cout << j << endl;
            sum += check_validity(elements, indices, rules);
        }
        i++;
    }
    return sum;
}

int main() {
    Timer timer;

    for (int i=0; i < 1; i++) {
        const int result = code();
        cout << result << endl;
    }

    return 0;
}
