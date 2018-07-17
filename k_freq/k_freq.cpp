#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

struct NumFreq {
    int num = 0;
    int freq = 0;
};

vector<int> get_freq(const vector<int>& array, int k)
{
    vector<int> result;
    priority_queue<NumFreq*, cmp> queue;
    unordered_map<int, int> freq;
    for (auto num: array) {
        queue.push(make_pair(num, 1));
    }
}

int main(int argc, char** argv)
{
    vector<int> input = {5, 4, 1, 4, 5, 6, 6, 6};
    auto res = get_freq(input, 3);
    for (auto n: res) {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}
