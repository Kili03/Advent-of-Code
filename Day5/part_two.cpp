#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>


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

void print_vector(const vector<int>& vec) {
    for (int e: vec) {
        cout << e << " ";
    }
    cout << endl;
}

void print_dict(const unordered_map<int, int>& dict) {
    for (const auto& [key, value]: dict) {
        cout << key << ": " << value << endl;
    }
}


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

vector<int> topsort_middle(const vector<int>& elements, const unordered_map<int, int>& indices, const unordered_map<int, vector<int>>& rules) {
    unordered_map<int, int> in_degree;
    vector<int> in_degree_0;
    for (const auto& [lt, gt]: rules) {
        if (ranges::find(elements, lt) == elements.end()) {
            continue;
        }
        for (int in: gt) {
            if (ranges::find(elements, in) != elements.end()) {
                in_degree[in] += 1;
            }
        }
    }
    for (int e: elements) {
        if (in_degree[e] == 0) {
            in_degree_0.emplace_back(e);
        }
    }

    vector<int> topsort;
    while (!in_degree_0.empty()) {
        const int k = in_degree_0.back();
        in_degree_0.pop_back();
        topsort.emplace_back(k);

        for (int e: rules.at(k)) {
            in_degree[e] -= 1;
            if (in_degree[e] == 0) {
                in_degree_0.emplace_back(e);
            }
        }
    }

    return topsort;

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
                j++;
            }
            int middle = check_validity(elements, indices, rules);
            if (middle == 0) {
                vector<int> topsort = topsort_middle(elements, indices, rules);
                //print_vector(elements);
                //print_dict(indices);
                //print_vector(topsort);
                int k = 0;
                for (int e: topsort) {
                    indices[e] = k;
                    k++;
                }
                //print_dict(indices);
                middle = check_validity(topsort, indices, rules);
                if (middle == 0) {
                    cout << "Failed" << endl;
                } else {
                    sum += middle;
                }
                //cout << endl;
            }
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
