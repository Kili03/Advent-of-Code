#include <deque>
#include <fstream>
#include <iostream>
#include <timer.h>

using namespace std;


struct FileOrEmpty {
    int number_of_blocks;

    explicit FileOrEmpty(const int blocks) : number_of_blocks(blocks) {}
};

struct File: FileOrEmpty {
    int id;
    bool moved;
    File(const int blocks, const int id) : FileOrEmpty(blocks), id(id) {
        moved = false;
    }

    [[nodiscard]] int empty() const {
        return number_of_blocks == 0;
    }

    [[nodiscard]] string get_string() const {
        string s;
        for (int i=0; i<number_of_blocks; i++) {
            s.append(to_string(id));
        }
        return s;
    }

    [[nodiscard]] unsigned long long get_checksum(int& index) const {
        unsigned long long sum = 0;
        for (int i=0; i<number_of_blocks; i++) {
            sum += id * index;
            index++;
        }
        return sum;
    }

    bool operator==(const File& other) const {
        return id == other.id;
    }
};

struct Empty: FileOrEmpty {
    vector<File> contained_files;

    explicit Empty(const int blocks) : FileOrEmpty(blocks) {}

    void add_file(File f) {
        contained_files.emplace_back(f);
        number_of_blocks -= f.number_of_blocks;
    }

    [[nodiscard]] string get_string() const {
        string s;
        for (File f : contained_files) {
            s.append(f.get_string());
        }
        s.append(string(number_of_blocks, '.'));
        return s;
    }

    [[nodiscard]] unsigned long long get_checksum(int& index) const {
        unsigned long long sum = 0;
        for (File f : contained_files) {
            sum += f.get_checksum(index);
        }
        index += number_of_blocks;
        return sum;
    }
};


unsigned long long calculate_checksum(deque<File>& files, deque<Empty>& frees) {
    // cout << "Length of files: " << files.size() << endl;
    // cout << "Length of frees: " << frees.size() << endl;

    int index = 0;
    unsigned long long checksum = 0;
    // string check;


    for (int i=static_cast<int>(files.size()) - 1; i>=0; i--) {
        File& current_file = files[i];

        for (int j=0; j<i; j++) {
            Empty& free = frees[j];
            if (free.number_of_blocks >= current_file.number_of_blocks) {
                free.add_file(current_file);
                current_file.moved = true;
                break;
            }
        }
    }

    while (!files.empty()) {
        const File& now = files.front();

        if (now.moved) {
            index += now.number_of_blocks;
            // check.append(string(now.number_of_blocks, '.'));
        } else {
            // check.append(now.get_string());
            checksum += now.get_checksum(index);
        }
        files.pop_front();

        if (frees.empty()) {
            break;
        }
        const Empty& now2 = frees.front();

        // check.append(now2.get_string());
        checksum += now2.get_checksum(index);

        frees.pop_front();
    }

    // cout << check << endl;
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