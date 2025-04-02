#include <deque>
#include <fstream>
#include <iostream>
#include <timer.h>

using namespace std;


struct FileOrEmpty {
    int number_of_blocks;

    explicit FileOrEmpty(const int blocks) : number_of_blocks(blocks) {}
};

struct Empty: FileOrEmpty {
    explicit Empty(const int blocks) : FileOrEmpty(blocks) {}
};

struct File: FileOrEmpty {
    int id;
    File(const int blocks, const int id) : FileOrEmpty(blocks), id(id) {}

    [[nodiscard]] int empty() const {
        return number_of_blocks == 0;
    }
    int remove_block() {
        number_of_blocks --;
        return id;
    }
};


unsigned long long calculate_checksum(deque<File>& files, deque<Empty>& frees) {
    cout << "Length of files: " << files.size() << endl;
    cout << "Length of frees: " << frees.size() << endl;
    int index = 0;
    unsigned long long checksum = 0;

    string check;


    while (!files.empty()) {
        const File current_file = files.front();
        for (int j=0; j < current_file.number_of_blocks; j++) {
            checksum += current_file.id * index;
            check.append(to_string(current_file.id));
            index++;
        }
        files.pop_front();

        for (int j=0; j < frees.front().number_of_blocks; j++) {
            if (files.back().empty()) {
                files.pop_back();
            }
            if (files.empty()) {
                break;
            }
            const int id = files.back().remove_block();
            checksum += id * index;
            check.append(to_string(id));
            index++;
        }
        frees.pop_front();
    }

    // cout << check << endl;;

    return checksum;
}


unsigned long long code() {
    ifstream DataFile("Advent-of-Code/Day9/data.txt");

    deque<Empty> frees{};
    deque<File> files{};

    string line;
    DataFile >> line;

    // cout << line << endl;

    int id = 0;
    bool is_file = true;

    for (const char c: line) {
        int number_of_blocks = c - '0';
        if (is_file) {
            files.emplace_back(number_of_blocks, id);
            id++;
        } else {
            frees.emplace_back(number_of_blocks);
        }
        is_file = !is_file;
    }


    return calculate_checksum(files, frees);
}

int main() {
    Timer timer;
    cout << code() << endl;;

    return 0;
}