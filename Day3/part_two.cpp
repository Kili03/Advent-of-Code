#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <regex>
#include <string>

using namespace std;


struct Timer {
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> duration;

    Timer() {
        start = chrono::high_resolution_clock::now();
    }
    ~Timer() {
        end = chrono::high_resolution_clock::now();
        duration = end-start;
        cout << "Time: " << duration.count() << endl;
    }
};


void code() {
    ifstream DataFile("Advent-of-Code/Day3/data.txt");
    if (DataFile.fail()) {
        throw invalid_argument("Could not successfully open file");
    }

    string full_data;
    string line;
    while (getline(DataFile, line)) {
        full_data.append(line);
    }

    // cout << full_data << endl;

    string regex_string = R"(mul\(\d+,\d+\)|don't\(\)|do\(\))";

    regex my_regex(regex_string);

    auto words_begin = sregex_iterator(full_data.begin(), full_data.end(), my_regex);
    auto words_end = sregex_iterator();

    int matches_count = distance(words_begin, words_end);
    cout << matches_count << endl;

    int result = 0;
    bool enabled = true;

    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        string match_str = match.str();
        // cout << match_str << endl;

        if (match_str == "do()") {
            enabled = true;
            continue;
        } else if (match_str == "don't()") {
            enabled = false;
            continue;
        }

        string imp = match_str.substr(4, match_str.size() - 5);

        // cout << imp << endl;

        int number1, number2;
        string number_string;
        stringstream searcher(imp);
        getline(searcher, number_string, ',');
        number1 = stoi(number_string);
        getline(searcher, number_string, ',');
        number2 = stoi(number_string);

        int part_result = number1 * number2;
        result += part_result * enabled;
    }

    cout << result << endl;


}

int main() {
    Timer timer;
    code();

    return 0;
}
