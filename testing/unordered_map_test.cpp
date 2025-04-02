#define LOG(x) cout<<x<<endl

#include <iostream>
#include <unordered_map>

using namespace std;

void code() {
    unordered_map<int, int> dict;

    LOG(dict[0]);
    dict[0] = 10;
    dict[0]++;
    LOG(dict[0]);

    int num = 20;
    dict[0] = num;
    LOG(dict[0]);
    num++;
    LOG(dict[0]);


}

int main() {
    LOG("Hello World!");
    code();
    return 0;
}

