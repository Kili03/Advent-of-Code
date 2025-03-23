**C++ Useful Functionalities Reference**

### Measuring Time

```c++
#include <chrono>
const auto begin = chrono::high_resolution_clock::now();
code();
const auto end = chrono::high_resolution_clock::now();
const chrono::duration<double> duration = end-begin;
cout << "Time: " << duration.count() << endl;
```

### Sorting
```c++
#include <algorithm>
Iterable a; // For example Array or Vector
sort(begin(a), end(a));
```

### Reading from file
```c++
#include <fstream>
ifstream DataFile("Advent-of-Code/Day1/data.txt");
string destination;

// Reads full line into destination
getLine(DataFile, destination);


// Extracts into these variables, separated by whitespaces
DataFile >> variable1 >> variable2 >> variable3;

DataFile.close();
```
### Converting String to int
```c++
string num_str = "1234";
int number = stoi(num_str);
```

### Dictionary / Hash-Map / Unordered-Map
```c++
#include <unordered_map>

unordered_map<key_type, value_type> counter;
counter["Hi"] = 5; // 5
counter["Hi"]++; // 6
counter["Hai"]++; // 1
```
Default values for integers are 0.

### Timer Struct
```c++
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
```

